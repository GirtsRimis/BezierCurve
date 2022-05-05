#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

void midPointCircleDraw(float x_centre, float y_centre, float r, sf::VertexArray & vertices)
{
    float x = r;
    float y = 0;
    int size = 4;
     
    vertices.resize(size);
    
    vertices.append(sf::Vertex({x_centre, y_centre}, sf::Color::White));
     
    if (r > 0)
    {
        vertices.append(sf::Vertex({ x + x_centre, -y + y_centre}, sf::Color::White));
        vertices.append(sf::Vertex({ y + x_centre,  x + y_centre}, sf::Color::White));
        vertices.append(sf::Vertex({-y + x_centre,  x + y_centre}, sf::Color::White));
    }
     
    float P = 1 - r;
    while (x > y)
    {
        size += 8;
        vertices.resize(size);

        y++;
         
        if (P <= 0)
            P = P + 2*y + 1;
        else
        {
            x--;
            P = P + 2*y - 2*x + 1;
        }
         
        if (x < y)
            break;
         
        vertices.append(sf::Vertex({ x + x_centre,  y + y_centre}, sf::Color::White));
        vertices.append(sf::Vertex({-x + x_centre,  y + y_centre}, sf::Color::White));
        vertices.append(sf::Vertex({ x + x_centre, -y + y_centre}, sf::Color::White));
        vertices.append(sf::Vertex({-x + x_centre, -y + y_centre}, sf::Color::White));

         
        if (x != y)
        {
            vertices.append(sf::Vertex({ y + x_centre,  x + y_centre}, sf::Color::White));
            vertices.append(sf::Vertex({-y + x_centre,  x + y_centre}, sf::Color::White));
            vertices.append(sf::Vertex({ y + x_centre, -x + y_centre}, sf::Color::White));
            vertices.append(sf::Vertex({-y + x_centre, -x + y_centre}, sf::Color::White));
        }
    }
}

void midPointEllipse(float rx, float ry, float xc, float yc, sf::VertexArray & vertices)
{
    int size = 0;
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;
 
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;
 
    while (dx < dy)
    {
        size += 4;
        vertices.resize(size);

        vertices.append(sf::Vertex({ x + xc,  y + yc}, sf::Color::White));
        vertices.append(sf::Vertex({-x + xc,  y + yc}, sf::Color::White));
        vertices.append(sf::Vertex({ x + xc, -y + yc}, sf::Color::White));
        vertices.append(sf::Vertex({-x + xc, -y + yc}, sf::Color::White));

        // std::cout << "(" <<  x + xc << ", " <<  y + yc << ")\n";
        // std::cout << "(" << -x + xc << ", " <<  y + yc << ")\n";
        // std::cout << "(" <<  x + xc << ", " << -y + yc << ")\n";
        // std::cout << "(" << -x + xc << ", " << -y + yc << ")\n";
 
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }
 
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
          (rx * rx * ry * ry);
 
    while (y >= 0)
    {
        size += 4;
        vertices.resize(size);

        vertices.append(sf::Vertex({ x + xc,  y + yc}, sf::Color::White));
        vertices.append(sf::Vertex({-x + xc,  y + yc}, sf::Color::White));
        vertices.append(sf::Vertex({ x + xc, -y + yc}, sf::Color::White));
        vertices.append(sf::Vertex({-x + xc, -y + yc}, sf::Color::White));

        // std::cout << "(" <<  x + xc << ", " <<  y + yc << ")\n";
        // std::cout << "(" << -x + xc << ", " <<  y + yc << ")\n";
        // std::cout << "(" <<  x + xc << ", " << -y + yc << ")\n";
        // std::cout << "(" << -x + xc << ", " << -y + yc << ")\n";

        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }

    // std::cout << "vertex count: " << vertices.getVertexCount() << "\n";
}

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Circle");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::VertexArray circlePoints(sf::Points);
    sf::VertexArray ellipsePoints(sf::Points);

    float xc = 400;
    float yc = 300;
    float r = 100;

    float rx = 100;
    float ry = 100;
    float xcellipse = 400;
    float ycellipse = 300;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            xc = localPosition.x;
            yc = localPosition.y;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            xcellipse = localPosition.x;
            ycellipse = localPosition.y;
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Zimet apli");
        ImGui::Text("Var noteikt centru ar labo peles pogu");
        ImGui::SliderFloat("x ass", &xc, 0.0f, 800.0f);
        ImGui::SliderFloat("y ass", &yc, 0.0f, 600.0f);
        ImGui::SliderFloat("radius", &r, 0.0f, 300.0f);
        if(ImGui::Button("Zimet"))
            midPointCircleDraw(xc, yc, r, circlePoints);
        if(ImGui::Button("Dzest"))
            circlePoints.resize(0);
        ImGui::End();

        ImGui::Begin("Zimet elipsi");
        ImGui::Text("Var noteikt centru ar space taustinu");
        ImGui::SliderFloat("x ass", &xcellipse, 0.0f, 800.0f);
        ImGui::SliderFloat("y ass", &ycellipse, 0.0f, 600.0f);
        ImGui::SliderFloat("rx", &rx, 0.0f, 300.0f);
        ImGui::SliderFloat("ry", &ry, 0.0f, 300.0f);
        if(ImGui::Button("Zimet"))
            midPointEllipse(rx, ry, xcellipse, ycellipse, ellipsePoints);
        if(ImGui::Button("Dzest"))
            ellipsePoints.resize(0);
        ImGui::End();

        window.clear();
        window.draw(circlePoints);
        window.draw(ellipsePoints);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    // return 0;
}
