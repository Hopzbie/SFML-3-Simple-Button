// library
#include <SFML/Graphics.hpp>
#include <iostream>

// main program
int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Title");

    // create shape of button
    sf::RectangleShape shape({200.f, 100.f});
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition({400.f, 300.f});

    // state of button
    bool isOver = false;
    bool isPressedInside = false;

    // state of mouse
    bool isMousePressed = false;

    // while window is still open
    while (window.isOpen())
    {
        // handle events
        while (std::optional event = window.pollEvent())
        {
            // when close button is clicked
            if (event->is<sf::Event::Closed>())
            {
                // close window
                window.close();
            }
            
            // when window is resized
            else if (event->is<sf::Event::Resized>())
            {
                // update view
                window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
            }
        }

        // mouse position
        auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

        // state of mouse
        bool onMousePress   = false;
        bool onMouseRelease = false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (not isMousePressed)
                onMousePress = true;
            isMousePressed = true;
        }
        else
        {
            if (isMousePressed)
                onMouseRelease = true;
            isMousePressed = false;
        }

        // when mouse is over button
        if (shape.getGlobalBounds().contains(mouse_position))
        {
            // on mouse enter
            if (not isOver)
                std::cout << "Enter\n";

            // on mouse press
            if (onMousePress)
            {
                std::cout << "Press\n";

                // set pressed inside
                isPressedInside = true;
            }

            // on mouse release
            if (onMouseRelease and isPressedInside)
                std::cout << "Release\n";

            // when mouse is pressed
            if (isMousePressed and isPressedInside)
                shape.setFillColor(sf::Color::Yellow);
            else
                shape.setFillColor(sf::Color(0, 170, 255));

            // set state
            isOver = true;
        }
        else
        {
            shape.setFillColor(sf::Color::White);

            // on mouse leave
            if (isOver)
                std::cout << "Leave\n";

            // reset state
            isOver = false;
        }
        // reset pressed inside
        if (not isMousePressed)
            isPressedInside = false;

        // fill window with color
        window.clear(sf::Color(64, 64, 64));

        // draw button
        window.draw(shape);

        // display
        window.display();
    }
    
    // program end successfully
    return 0;
}