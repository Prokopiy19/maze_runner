#include <algorithm>
#include <random>
#include <iostream>

#include "ai.hpp"
#include "app.hpp"
#include "char_types.hpp"
#include "collisions.hpp"
#include "draw.hpp"
#include "entities.hpp"
#include "input.hpp"
#include "prim.hpp"
#include "world.hpp"

#include "settings.hpp"

void generate_maze_and_apply(World& world)
{
    int w = (kWidth + gap - 1) / gap;
    int h = (kHeight + gap - 1) / gap;

    maze = prim(w, h);
    
    std::random_device rd;
    add_loops(rd);

    apply_maze_to_world(maze, world, gap);
}

World generate_world()
{
    World world;

    generate_maze_and_apply(world);

    return world;
}

int main(int argc, char* args[])
{
    {
        world = generate_world();

        draw_world(world);
    }

    build_scenes();
	
	CollisionDetection colliders;
	
	colliders.add(hero.collider());
	colliders.add(key.collider());

    std::random_device rd;

    int cnt = 5;
    while (cnt > 0)
        cnt -= spawn(CHAR_MONSTER, colliders, rd);

    float spawn_timer = 0.;

    key.kill();

    while(app.running()) {
        handle_events();
		
		colliders.find_collisions();

        prepare_scene(app.renderer());

        ai_update(rd);

        colliders.move();
        
        app.renderer().present();
        app.tick();

        spawn_timer += app.delta();
        if (spawn_timer > SPAWN_TIME) {
            spawn_timer -= spawn(CHAR_MONSTER, colliders, rd) * SPAWN_TIME;
        }

        if (!key.is_alive()) {
            std::cout << "score: " << hero.score() << std::endl;;
            key_respawn(rd);
        }

        // std::cout << hero.collider()->get_i() << ' ' << hero.collider()->get_j() << std::endl;

        if (!hero.is_alive()) {
            app.pause();
        }
        
        // std::cout << app.fps() << " " << app.avg_fps() << std::endl;
    }

    free_textures();

    return 0;
}