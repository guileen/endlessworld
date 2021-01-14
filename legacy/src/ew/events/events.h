#pragma once

struct HitEvent {
    EID attacker;
    EID reciever;
    int damage;
};

enum class EWEvents
{
    Quit,
    ActionAttack,
    Hit
};
