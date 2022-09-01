#include "ai.hpp"

#include <array>
#include <random>
#include <utility>
#include <vector>

#include "entities.hpp"
#include "world.hpp"

#include <iostream> //debug

namespace {

const std::array<std::pair<int, int>, 4> directions = {{{1, 0}, {0, -1}, {-1, 0}, {0, 1}}};

} //namespace

void ai_update(std::random_device& rd)
{
    for (auto& entity : entities)
    {
        auto pcollider = entity.collider();
        
        // std::cout << pcollider->ai_state() << std::endl;

        switch (pcollider->ai_state()) {
            case Collider::STILL: {
                int i = pcollider->get_i();
                int j = pcollider->get_j();
                std::vector<int> ways;
                for (int id = 0; id < directions.size(); ++id) {
                    auto [x, y] = directions[id];
                    if (pcollider->prev_state() != Collider::STILL
                        && id == (pcollider->prev_state() + 2)%4) {
                        continue;
                    }
                    if (can_pass(i+x, j+y))
                        ways.push_back(id);
                }
                Collider::AiState new_state = Collider::STILL;
                if (ways.size() > 0) {
                    int way = std::uniform_int_distribution<>(0, ways.size()-1)(rd);
                    new_state = static_cast<Collider::AiState>(ways[way]);
                }
                else if (pcollider->prev_state() != Collider::STILL) {
                    new_state = static_cast<Collider::AiState>((pcollider->prev_state() + 2)%4); // opposite direction
                }
                pcollider->set_ai_state(new_state);
                auto [x, y] = directions[new_state];
                pcollider->set_vel_x(x);
                pcollider->set_vel_y(y);
                pcollider->set_dest(i + 2*x, j + 2*y);
                // std::cout << "dest: " << i + 2*x << ' ' << j + 2*y << std::endl;
                break;
            }
            default: {
                pcollider->set_vel_x(directions[pcollider->ai_state()].first);
                pcollider->set_vel_y(directions[pcollider->ai_state()].second);
                if (pcollider->pass_dest()) {
                    pcollider->set_ai_state(Collider::STILL);
                    pcollider->set_vel_x(0.f);
                    pcollider->set_vel_y(0.f);
                }
                break;
            }
        }
    }
}