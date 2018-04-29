#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Color.hpp>

struct RenderView
{
    sf::Color clearColor;
    sf::View camera;
};

#endif // RENDERVIEW_H
