#include <iostream>
#include <cmath>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

void bezierCurve(std::vector<float> & xCoords, std::vector<float> & yCoords, sf::VertexArray & vertices)
{
    // p = (1-t)^3 *P0 + 3*t*(1-t)^2*P1 + 3*t^2*(1-t)*P2 + t^3*P3
    // p = (1-t)^2 *P0 + 2*(1-t)*t*P1 + t*t*P2
    int size = 0;
    int n = xCoords.size() - 1;
    float xc = 0;
    float yc = 0;

    for (float t = 0.0; t <= 1.0; t += 0.0001)
    {
        switch (xCoords.size())
        {
        case 3:
            xc = std::pow(1 - t, 3) * xCoords.at(0) + 2 * (1 - t) * t * xCoords.at(1) + t * t * xCoords.at(2);
            yc = std::pow(1 - t, 3) * yCoords.at(0) + 2 * (1 - t) * t * yCoords.at(1) + t * t * yCoords.at(2);
            break;

        case 6:
            xc = std::pow(1 - t, 3) * xCoords.at(0) + 2 * (1 - t) * t * xCoords.at(1) + t * t * xCoords.at(2)
                +std::pow(1 - t, 3) * xCoords.at(3) + 2 * (1 - t) * t * xCoords.at(4) + t * t * xCoords.at(5);

            yc = std::pow(1 - t, 3) * yCoords.at(0) + 2 * (1 - t) * t * yCoords.at(1) + t * t * yCoords.at(2)
                +std::pow(1 - t, 3) * yCoords.at(3) + 2 * (1 - t) * t * yCoords.at(4) + t * t * yCoords.at(5);
            break;

        case 9:
            xc = std::pow(1 - t, 3) * xCoords.at(0) + 2 * (1 - t) * t * xCoords.at(1) + t * t * xCoords.at(2)
                +std::pow(1 - t, 3) * xCoords.at(3) + 2 * (1 - t) * t * xCoords.at(4) + t * t * xCoords.at(5)
                +std::pow(1 - t, 3) * xCoords.at(6) + 2 * (1 - t) * t * xCoords.at(7) + t * t * xCoords.at(8);

            yc = std::pow(1 - t, 3) * yCoords.at(0) + 2 * (1 - t) * t * yCoords.at(1) + t * t * yCoords.at(2)
                +std::pow(1 - t, 3) * yCoords.at(3) + 2 * (1 - t) * t * yCoords.at(4) + t * t * yCoords.at(5)
                +std::pow(1 - t, 3) * yCoords.at(6) + 2 * (1 - t) * t * yCoords.at(7) + t * t * yCoords.at(8);
            break;

        case 12:
            xc = std::pow(1 - t, 3) * xCoords.at(0) + 2 * (1 - t) * t * xCoords.at(1) + t * t * xCoords.at(2)
                +std::pow(1 - t, 3) * xCoords.at(3) + 2 * (1 - t) * t * xCoords.at(4) + t * t * xCoords.at(5)
                +std::pow(1 - t, 3) * xCoords.at(6) + 2 * (1 - t) * t * xCoords.at(7) + t * t * xCoords.at(8)
                +std::pow(1 - t, 3) * xCoords.at(9) + 2 * (1 - t) * t * xCoords.at(10) + t * t * xCoords.at(11);

            yc = std::pow(1 - t, 3) * yCoords.at(0) + 2 * (1 - t) * t * yCoords.at(1) + t * t * yCoords.at(2)
                +std::pow(1 - t, 3) * yCoords.at(3) + 2 * (1 - t) * t * yCoords.at(4) + t * t * yCoords.at(5)
                +std::pow(1 - t, 3) * yCoords.at(6) + 2 * (1 - t) * t * yCoords.at(7) + t * t * yCoords.at(8)
                +std::pow(1 - t, 3) * yCoords.at(9) + 2 * (1 - t) * t * yCoords.at(10) + t * t * yCoords.at(11);
            break;
        
        default:
            break;
        }

        size++;
        vertices.resize(size);
        vertices.append(sf::Vertex({xc, yc}, sf::Color::White));
        xc = 0;
        yc = 0;
    }
}

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Circle");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::VertexArray brezierPoints(sf::Points);

    std::vector<float> xCoords = {100, 200, 300};
    std::vector<float> yCoords = {100, 200, 300};

    int size = xCoords.size();

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

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Bezier linija");
        ImGui::Text("Var zimet");
        for (int i = 0; i < size; ++i)
        {
            ImGui::SliderFloat(std::string("x" + std::to_string(i + 1) + " : ").c_str(), &xCoords.at(i), 0.0f, 800.0f);
            ImGui::SliderFloat(std::string("y" + std::to_string(i + 1) + " : ").c_str(), &yCoords.at(i), 0.0f, 800.0f);
        }
        if (ImGui::SliderInt("Point numbers", &size, 3, 12))
        {
            if (size > 3 && size < 7)
                size = 6;
            else if (size > 6 && size < 10)
                size = 9;
            else if (size > 9 && size < 12)
                size = 12;
            else 
                size = 3;
            
            for (int i = 0; i < size; ++i)
            {
                if (xCoords.size() < size)
                    xCoords.push_back(400);
                else if (xCoords.size() > size)
                    xCoords.pop_back();

                if (yCoords.size() < size)
                    yCoords.push_back(400);
                else if (yCoords.size() > size)
                    yCoords.pop_back();
            }
        }

        if(ImGui::Button("Zimet"))
            bezierCurve(xCoords, yCoords, brezierPoints);
        
        if(ImGui::Button("Dzest"))
            brezierPoints.resize(0);
        ImGui::End();

        window.clear();
        window.draw(brezierPoints);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
