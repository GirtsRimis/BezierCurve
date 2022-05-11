#include <iostream>
#include <cmath>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

void moveShape(float matrix[], std::vector<sf::Vector2f> & shapeCoords)
{
    for (int i = 0; i < shapeCoords.size(); ++i)
    {
        shapeCoords.at(i).x += matrix[6];
        shapeCoords.at(i).y += matrix[7];
    }
}

void biggerShape(float matrix[], std::vector<sf::Vector2f> & shapeCoords)
{
    for (int i = 0; i < shapeCoords.size(); ++i)
    {
        shapeCoords.at(i).x *= matrix[2];
        shapeCoords.at(i).y *= matrix[5];
    }
}

void smallerShape(float matrix[], std::vector<sf::Vector2f> & shapeCoords)
{
    for (int i = 0; i < shapeCoords.size(); ++i)
    {
        shapeCoords.at(i).x /= matrix[2];
        shapeCoords.at(i).y /= matrix[5];
    }
}

void rotateShape(float matrix[], std::vector<sf::Vector2f> & shapeCoords, sf::Vector2f & rotationPoint)
{
    // angle - theta, ox/oy - rotation point
    // p'x = cos(theta) * (px-ox) - sin(theta) * (py-oy) + ox
    // p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy

    for (int i = 0; i < shapeCoords.size(); ++i)
    {
        shapeCoords.at(i).x = matrix[0] * (shapeCoords.at(i).x - rotationPoint.x) - matrix[1] * (shapeCoords.at(i).y - rotationPoint.y) + rotationPoint.x;
        shapeCoords.at(i).y = matrix[3] * (shapeCoords.at(i).x - rotationPoint.x) + matrix[4] * (shapeCoords.at(i).y - rotationPoint.y) + rotationPoint.y;
    }
}

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "2d transformacija");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    float degrees = 60.f;

    float transfromMatrix[] =
    {
        0.f, 0.f, 2.f,
        0.f, 0.f, 2.f,
        10.f, 10.f, 0.f,
    };


    transfromMatrix[0] = std::cos(degrees);
    transfromMatrix[1] = std::sin(degrees);
    transfromMatrix[3] = std::sin(degrees);
    transfromMatrix[4] = std::cos(degrees);

    int size = 3;

    sf::ConvexShape convexShape;
    convexShape.setPointCount(size);
    convexShape.setFillColor(sf::Color::Cyan);

    std::vector<sf::Vector2f> shapeCoords;
    shapeCoords.resize(size);

    shapeCoords.at(0) = sf::Vector2f(100.f, 100.f);
    shapeCoords.at(1) = sf::Vector2f(100.f, 200.f);
    shapeCoords.at(2) = sf::Vector2f(200.f, 100.f);

    convexShape.setPoint(0, shapeCoords.at(0));
    convexShape.setPoint(1, shapeCoords.at(1));
    convexShape.setPoint(2, shapeCoords.at(2));

    sf::Vector2f rotationPoint(0.f, 0.f);

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

        ImGui::Begin("Zimet apli");
        ImGui::SliderFloat("x ass", &transfromMatrix[6], -100.0f, 100.0f);
        ImGui::SliderFloat("y ass", &transfromMatrix[7], -100.0f, 100.0f);
        ImGui::SliderFloat("rotacijas punkts x", &rotationPoint.x, 0.0f, 600.0f);
        ImGui::SliderFloat("rotacijas punkts y", &rotationPoint.y, 0.0f, 800.0f);
        if (ImGui::SliderFloat("rotacijas lenkis", &degrees, 0.0f, 360.0f))
        {
            transfromMatrix[0] = std::cos(degrees);
            transfromMatrix[1] = std::sin(degrees);
            transfromMatrix[3] = std::sin(degrees);
            transfromMatrix[4] = std::cos(degrees);
        }

        if (ImGui::SliderInt("Punktu skaits", &size, 3, 11))
        {
            convexShape.setPointCount(size);
            shapeCoords.resize(size);
        }

        for (int i = 0; i < size; ++i)
        {
            ImGui::SliderFloat(std::string("x" + std::to_string(i + 1) + " coords").c_str(), &shapeCoords.at(i).x, 0.0f, 600.0f);
            ImGui::SliderFloat(std::string("y" + std::to_string(i + 1) + " coords").c_str(), &shapeCoords.at(i).y, 0.0f, 800.0f);

            convexShape.setPoint(i, shapeCoords.at(i));
        }

        if(ImGui::Button("Parvietot"))
            moveShape(transfromMatrix, shapeCoords);
        if(ImGui::Button("Palielinat"))
            biggerShape(transfromMatrix, shapeCoords);
        if(ImGui::Button("Samazinat"))
            smallerShape(transfromMatrix, shapeCoords);
        if(ImGui::Button("Pagriezt"))
            rotateShape(transfromMatrix, shapeCoords, rotationPoint);
        if(ImGui::Button("Reset"))
        {
            convexShape.setPointCount(size);
            shapeCoords.resize(size);

            shapeCoords.at(0) = sf::Vector2f(100.f, 100.f);
            shapeCoords.at(1) = sf::Vector2f(100.f, 200.f);
            shapeCoords.at(2) = sf::Vector2f(200.f, 100.f);

            convexShape.setPoint(0, shapeCoords.at(0));
            convexShape.setPoint(1, shapeCoords.at(1));
            convexShape.setPoint(2, shapeCoords.at(2));
        }
        ImGui::End();

        window.clear();
        window.draw(convexShape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
