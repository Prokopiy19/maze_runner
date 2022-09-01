#include "circle.hpp"

#include "character.hpp"
#include "draw.hpp"
#include "settings.hpp"
#include "world.hpp"

void Circle::draw(Renderer& renderer)
{
    auto& texture = chars[owner()->type()];
    // std::cout << texture.width() << " X " << texture.height() << std::endl;
    texture.render(x()-texture.width()/2, y()-texture.height()/2);
}