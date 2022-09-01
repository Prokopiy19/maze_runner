#include "action.hpp"

CollisionAction::CollisionAction()
{
    table_[CHAR_HERO*CHAR_TOTAL + CHAR_KEY] =
        [](Character *hero, Character *key)
        {
            if (key->is_alive()) {
                key->kill();
                hero->increase_score();
            }
        };
    table_[CHAR_HERO*CHAR_TOTAL + CHAR_MONSTER] =
        [](Character *hero, Character *monster)
        {
            hero->kill();
            current_scene = SCENE_GAME_OVER;
        };
}