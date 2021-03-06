//ИСПОЛЬЗОВАТЬ ООП!
//
//
//Реализовать анимиррованное движение змейки в консоли на 2 минуты
//С каждыми 15тью секундами - ей в хвост добавляется случайного цвета шарик
//Движение должно происходить прижатым к сторонам консоли по часовой стрелке

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <ctime>
#include <windows.h>

#define TRUE_RANDOM srand(time(0));
#define RANDOMIZE_COLOR (rand()%4+0)

using namespace sf;
using namespace std;

enum currentState {
	UP, RIGTH, DOWN, LEFT
};

enum collor {
	red, blue, green, cyan, magneta
};

class Sanke
{
private:
	const int maxSize = 30;
	const float moveSpeed = 0.2;
	int snakeLength;
	float snakeRadius;
	CircleShape* circleList;
	currentState* elList;

public:
	Sanke();

	void movment();
	int getSnakeLenght();
	void addTail();
	~Sanke();

	CircleShape* getCircleList() {
		return circleList;

	}


};

Sanke::Sanke()
{
	snakeLength = 1;
	snakeRadius = 12;
	circleList = new CircleShape[maxSize];
	elList = new currentState[maxSize];


	CircleShape tempSnake;
	tempSnake.setRadius(snakeRadius);
	tempSnake.setPosition(0, 0);
	circleList[0] = tempSnake;
	elList[0] = UP;
}

void Sanke::movment()
{
	for (int i = 0; i < snakeLength; i++) {
		if (elList[i] == UP) {
			circleList[i].move(moveSpeed, 0);

			if (circleList[i].getPosition().y <= 0 && circleList[i].getPosition().x + snakeRadius * 2 > 500) {
				elList[i] = RIGTH;
			}
		}
		else if (elList[i] == RIGTH) {
			circleList[i].move(0, moveSpeed);

			if (circleList[i].getPosition().y + snakeRadius * 2 > 500) {
				elList[i] = DOWN;
			}
		}
		else if (elList[i] == DOWN) {
			circleList[i].move(-moveSpeed, 0);
			if (circleList[i].getPosition().x <= 0) {
				elList[i] = LEFT;
			}
		}
		else if (elList[i] == LEFT) {
			circleList[i].move(0, -moveSpeed);
			if (circleList[i].getPosition().y <= 0) {
				elList[i] = UP;
			}
		}

	}
}

int Sanke::getSnakeLenght()
{
	return snakeLength;
}

void Sanke::addTail()
{
	CircleShape tempSnake;
	tempSnake.setRadius(snakeRadius);


	if (elList[snakeLength - 1] == UP) {
		tempSnake.setPosition(circleList[snakeLength - 1].getPosition().x - snakeRadius * 2, circleList[snakeLength - 1].getPosition().y);
		elList[snakeLength] = UP;
		tempSnake.setFillColor(sf::Color::Blue);
	}
	if (elList[snakeLength - 1] == RIGTH) {
		tempSnake.setPosition(circleList[snakeLength - 1].getPosition().x, circleList[snakeLength - 1].getPosition().y - snakeRadius * 2);
		elList[snakeLength] = RIGTH;
		tempSnake.setFillColor(sf::Color::Green);
	}
	if (elList[snakeLength - 1] == DOWN) {
		tempSnake.setPosition(circleList[snakeLength - 1].getPosition().x + snakeRadius * 2, circleList[snakeLength - 1].getPosition().y);
		elList[snakeLength] = DOWN;
		tempSnake.setFillColor(sf::Color::Cyan);
	}
	if (elList[snakeLength - 1] == LEFT) {
		tempSnake.setPosition(circleList[snakeLength - 1].getPosition().x, circleList[snakeLength - 1].getPosition().y + snakeRadius * 2);
		elList[snakeLength] = LEFT;
		tempSnake.setFillColor(sf::Color::Red);
	}

	circleList[snakeLength] = tempSnake;
	snakeLength++;
}




Sanke::~Sanke()
{
}



int main()
{
	const float RADIUS = 25;
	RenderWindow window(VideoMode(500, 500), "Game");
	Event event;

	Clock clock;

	Sanke snakesList;



	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		if (clock.getElapsedTime().asSeconds() > 3) {
			snakesList.addTail();
			clock.restart();
		}
		window.clear();
		snakesList.movment();
		for (int i = 0; i < snakesList.getSnakeLenght(); i++) {
			window.draw(snakesList.getCircleList()[i]);
		}

		window.display();
	}

	return 0;
}

;