#pragma once
#include "../components/combat.h"
#include "../../ecs/event_bus.h"

class CombatSystem {
    ecs::Manager& manager;
public:
    CombatSystem(ecs::Manager &mManager): manager(mManager) {
        EventBus.on(EWEvents::Hit, [this]() {
            printf("OnHit\n");
            // Entity* attacker = manager.getEntity(ev.attacker);
            /*
            Entity* receiver = manager.getEntity(ev.reciever);
            Health& h = receiver->getComponent<Health>();
            // TODO: defense
            int damage = ev.damage;
            h.hitPoint -= damage;
             */
        });

        EventBus.on(EWEvents::ActionAttack, [this]() {
            printf("OnAttack\n");
        });
    }

    void update()
    {
        manager.each<MeeleAttack>([&](Entity &e, MeeleAttack &attack) {
            if (attack.attacking)
            {
                if (++attack.frame == attack.hitFrame)
                {
                    // on entity hit.
                    EventBus.emit(EWEvents::Hit);
                }
                if (attack.frame >= attack.frames)
                {
                    attack.frame = 0;
                }
            }
        });
    }
};
