#include "prim.hpp"

#include <iterator>
#include <memory>
#include <list>
#include <utility>
#include <vector>

#include "random_int.hpp"
#include "world.hpp"

namespace {

struct Edge {

    struct Coord {
        int x = 0, y = 0;
    };

    Coord from, to;
};

class Queue {
public:
    Queue(std::shared_ptr<Maze> sp_maze) : sp_maze_{sp_maze} {}

    using size_type = std::vector<std::pair<int, int>>::size_type;

    void add_neighbors(int x, int y);

    Edge get_and_remove(RandomInt&);

    bool empty() const { return data_.empty(); }


private:
    void add(const Edge& e);
    
    std::list<Edge> data_;
    std::shared_ptr<Maze> sp_maze_;
};

void Queue::add_neighbors(int x, int y)
{
    add(Edge{ .from = { x, y }, .to = { x+2, y } });
    add(Edge{ .from = { x, y }, .to = { x-2, y } });
    add(Edge{ .from = { x, y }, .to = { x, y+2 } });
    add(Edge{ .from = { x, y }, .to = { x, y-2 } });
}

void Queue::add(const Edge& e)
{
    auto [x_size, y_size] = get_size(*sp_maze_);

    if (   0 <= e.to.x && e.to.x < x_size
        && 0 <= e.to.y && e.to.y < y_size
        && (*sp_maze_)[e.to.x][e.to.y] == Cell::kWall) {
        data_.emplace_back(e);
    }
}

Edge Queue::get_and_remove(RandomInt& random_int)
{
    int dist = random_int(data_.size());

    auto it = data_.cbegin();

    std::advance(it, dist);

    Edge e = *it;

    data_.erase(it);

    return e;
}

} //namespace

Maze prim(int w, int h)
{
    auto sp_maze = std::make_shared<Maze>(w, std::vector<Cell>(h, Cell::kWall));

    RandomInt random_int;

    int x = 2 * random_int(w/2);
    int y = 2 * random_int(h/2);

    (*sp_maze)[x][y] = Cell::kPass;

    Queue queue{sp_maze};

    queue.add_neighbors(x, y);

    while (!queue.empty()) {
        Edge e = queue.get_and_remove(random_int);
        
        if ((*sp_maze)[e.to.x][e.to.y] == Cell::kPass)
            continue;
        
        (*sp_maze)[e.to.x][e.to.y] = Cell::kPass;

        int x_mid = (e.from.x + e.to.x) / 2;
        int y_mid = (e.from.y + e.to.y) / 2;

        (*sp_maze)[x_mid][y_mid] = Cell::kPass;

        queue.add_neighbors(e.to.x, e.to.y);
    }

    return *sp_maze;
}

namespace {

void check_way(int i, int j, int x, int y, int& ways, std::vector<std::pair<int, int>>& walls)
{
    if (inside(i+2*x, j+2*y)) {
        if (!can_pass(i+x, j+y)) {
            walls.push_back({i+x, j+y});
        }
        else
            ++ways;
    }
}

} //namespace

void add_loops(std::random_device& rd)
{
    auto [m, n] = get_size(maze);
    for (int i = 0; i < m; i += 2)
        for (int j = 0; j < n; j += 2) {
            int ways = 0;
            std::vector<std::pair<int, int>> walls;
            check_way(i, j, 1, 0, ways, walls);
            check_way(i, j, 0,-1, ways, walls);
            check_way(i, j,-1, 0, ways, walls);
            check_way(i, j, 0, 1, ways, walls);
            if (ways > 1) {
                continue;
            }
            int r = std::uniform_int_distribution<>(0, walls.size()-1)(rd);
            auto [bi, bj] = walls[r];
            maze[bi][bj] = Cell::kPass;
        }
}


namespace {

void make_point(World& world, int x, int y)
{
    int x_size = world.size();
    int y_size = world[0].size();

    if (   0 <= x && x < x_size
        && 0 <= y && y < y_size)
        world[x][y] = 1;
}

void apply_cell_to_world(World& world, int x, int y, int gap)
{
    for (int xx = x*gap; xx < (x+1)*gap; ++xx)
        for (int yy = y*gap; yy < (y+1)*gap; ++yy)
            make_point(world, xx, yy);
}

} //namespace

void apply_maze_to_world(const Maze& maze, World& world, int gap)
{
    auto [x_size, y_size] = get_size(maze);

    for (int x = 0; x != x_size; ++x)
        for (int y = 0; y != y_size; ++y)
            if (maze[x][y] == Cell::kPass) {
                apply_cell_to_world(world, x, y, gap);
            }
}
