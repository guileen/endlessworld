//  https://www.youtube.com/watch?v=QAmtgvwHInM
#ifndef _ECS_H_
#define _ECS_H_
#pragma once
#include <assert.h>
#include <vector>
#include <bitset>
#include <array>
#include <map>

namespace ecs {

// ECS config
constexpr uint32_t maxComponents = 32;
typedef uint32_t CID;
typedef uint32_t EID;
constexpr uint32_t maxGroups = 32;
typedef size_t Group;
// end ECS config

// help function.
namespace Internal {
    inline CID getComponentUniqueID() {
        static CID lastID = 0;
        return lastID++;
    }

    inline EID getEntityID() {
        static EID lastID = 0;
        return lastID++;
    }

    inline bool all_is_true(bool v) {
        return v;
    }

    template <typename... B>
    inline bool all_is_true(bool b0, B... v) {
        return b0 && all_is_true(v...);
    }
}

template <typename T> inline CID getComponentTypeID() noexcept {
    static CID typeID = Internal::getComponentUniqueID();
    return typeID;
}

struct Component{
    virtual ~Component() {}
};

class Manager;

class Entity {
  private:
    EID id;
    Manager* manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    std::array<Component*, maxComponents> componentArray;
    std::bitset<maxComponents> componentBitSet;
    std::bitset<maxGroups> groupBitSet;

  public:
    Entity(Manager* mManager) :manager(mManager){
        id = Internal::getEntityID();
    };

    bool isActive() const { return active; }
    void destroy() { active = false; }
    
    EID getId() {return id;};

    template <typename ...ComponentType> bool hasComponent() const {
        return Internal::all_is_true(componentBitSet[getComponentTypeID<ComponentType>()]...);
    }

    bool hasGroup(Group group) const noexcept {
        return groupBitSet[group];
    }
    void addGroup(Group group) noexcept;
    void delGroup(Group group) noexcept {
        groupBitSet[group] = false;
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        assert(!hasComponent<T>());

        T* c(new T(std::forward<TArgs>(mArgs)...));
        // c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        return *c;
    }

    template<typename T> T& getComponent() const {
        assert(hasComponent<T>());

        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupEntities;
    std::map<EID, Entity*> entityMap;
    Entity* player;
public:
    friend void Entity::addGroup(Group) noexcept;

    Entity& addEntity() {
        Entity* e = new Entity(this);
        std::unique_ptr<Entity> p{e};
        entities.emplace_back(std::move(p));
        entityMap[e->getId()] = e;
        return *e;
    }

    Entity *getEntity(EID id) {
        return entityMap[id];
    }

    void setPlayer(Entity* e) {
        player = e;
    }

    Entity& getPlayer() {
        assert(player);
        return *player;
    }

    template<typename Func>
    void eachOfGroup(Group g, Func func) {
        for(auto& e: groupEntities[g]) {
            func(*e);
        }
    }

    template<typename ...T, typename Func>
    void eachOfGroup(Group g, Func func) {
        for(auto& e: groupEntities[g]) {
            if(e->hasComponent<T...>()) func(*e, e->getComponent<T>()...);
        }
    }

    template<typename Func>
    void each(Func func) {
        for(auto& e: entities) {
            func(*e);
        }
    }

    template<typename ...T, typename Func>
    void each(Func func) {
        for(auto& e: entities) {
            if(e->hasComponent<T...>()) func(*e, e->getComponent<T>()...);
        }
    }

    void refresh() {
        for(auto i=0;i<maxGroups;i++) {
            auto& v = groupEntities[i];
            v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* e) {
                return !e->isActive() || !e->hasGroup(i);
            }), std::end(v));
        }
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity) {
                return !mEntity->isActive();
        }), std::end(entities));
        for(auto &p: entityMap) {
            if(!p.second->isActive()) {
                entityMap.erase(p.first);
            }
        }
    }
};

void Entity::addGroup(Group g) noexcept{
    groupBitSet[g] = true;
    manager->groupEntities[g].emplace_back(this);
}

}
#endif //_ECS_H_
