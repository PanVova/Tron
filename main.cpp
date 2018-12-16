#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
using namespace sf;
using namespace std;

#define WIDTH 2000
#define HEIGHT 1300
#define SPEED 4
wbool field[WIDTH][HEIGHT] = { 0 };

class Player {
	int x, y, direction;
	Color color;
public :	
	int getX() 
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	void setDirection(int direction) 
	{
		this->direction = direction;
	}
	Color getColor() 
	{
		return color;
	}
	Player(Color color)
	{
		this->color = color;
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		direction = rand() % 4;
	}

	void move()
	{
		if (direction == 0) y += 1; //up
		if (direction == 1) x -= 1; // left
		if (direction == 2) x += 1; //right
		if (direction == 3) y -= 1; //down

		if (x >= WIDTH) x = 0;  if (x<0) x = WIDTH - 1; // borders
		if (y >= HEIGHT) y = 0;  if (y<0) y = HEIGHT - 1; //borders
	}
};

int color = 0;
int WinMain() 
{

	Font font;

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Tron(Panasenko Vova)");
	window.setFramerateLimit(60);
	Player  p1(Color::Blue);
	Player  p2(Color::Red);
	bool Game = 1;
	Texture texture;
	Sprite sBackground;
	Sprite sprite;
	RenderTexture t;
	t.create(WIDTH, HEIGHT);
	sprite.setTexture(t.getTexture());
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))  p1.setDirection(1);
		if (Keyboard::isKeyPressed(Keyboard::Right)) p1.setDirection(2);
		if (Keyboard::isKeyPressed(Keyboard::Up))	 p1.setDirection(3);
		if (Keyboard::isKeyPressed(Keyboard::Down))  p1.setDirection(0);

		if (Keyboard::isKeyPressed(Keyboard::A))  p2.setDirection(1);
		if (Keyboard::isKeyPressed(Keyboard::D))  p2.setDirection(2);
		if (Keyboard::isKeyPressed(Keyboard::W))  p2.setDirection(3);
		if (Keyboard::isKeyPressed(Keyboard::S))  p2.setDirection(0);

		if (!Game)
		{
			
			
			t.clear();
			window.clear();
			Text t1;
			
			t1.setCharacterSize(24);
			//t1.setFont(MyFont);
	
			t1.setFillColor(Color::Cyan);
			
			if (color == 1)
			{
				t1.setFillColor(Color::Blue);
			}
			else
			{
				t1.setFillColor(Color::Red);
			}
			t1.setString("You won");
			t1.setPosition(200, 200);
			//break;
			
			cout << "You win";
			if (color == 1)
			{
				cout << "Blue";
				window.close();
			}
			else
			{
				cout << "Red";
				window.close();
			}
			
			window.draw(t1);
			window.display();
			//break;
			
		}

		if (Game)
		{
			for (int i = 0; i < SPEED; i++)
			{
				p1.move(); p2.move();
				if (field[p1.getX()][p1.getY()] == 1) Game = 0; color = 2;
				if (field[p2.getX()][p2.getY()] == 1) Game = 0; color = 1;
				field[p1.getX()][p1.getY()] = 1;
				field[p2.getX()][p2.getY()] = 1;

				CircleShape c(3);
				c.setPosition(p1.getX(), p1.getY()); c.setFillColor(p1.getColor());	t.draw(c);
				c.setPosition(p2.getX(), p2.getY()); c.setFillColor(p2.getColor());	t.draw(c);
				t.display();
			}
			window.clear();
			window.draw(sprite);
			window.display();
		}
	}
}