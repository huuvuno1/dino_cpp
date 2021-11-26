#include<iostream>
#include<windows.h>
#include <conio.h>
using namespace std;
const int Y = 22;

void gotoxy(int x, int y)
{
    static HANDLE  h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x,y};
    SetConsoleCursorPosition(h,c);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

class Base 
{
	protected:
		int x;
		int y;
	public:
		int getX() 
		{
			return this->x;
		}
		int getY()
		{
			return this->y;
		}
};

class Dino : public Base
{
	private:
		
		void clearDraw() 
		{
			gotoxy(this->x, this->y);
			cout << "   ";
			gotoxy(this->x, this->y + 1);
			cout << "   ";
			gotoxy(this->x, this->y + 2);
			cout << "   ";
			Dino();
		}
	public:
		Dino() 
		{
			// init positon
			this->x = 20;
			this->y = 22;
		}
		
		void drawStand()
		{
			clearDraw();
			this->x = x;
			this->y = y;
			gotoxy(this->x, this->y);
			cout << " o \n";
			gotoxy(this->x, this->y + 1);
			cout << "/|\\\n";
			gotoxy(this->x, this->y + 2);
			cout << "/ \\";
		}
		
		void draw() 
		{
			if (this->y < Y) {
				clearDraw();
				this->y++;
				gotoxy(this->x, this->y);
				cout << "_o\n";
				gotoxy(this->x, this->y + 1);
				cout << " |\\\n";
				gotoxy(this->x, this->y + 2);
				cout << "/ >";
			}
			else
				drawStand();
		}
		
		void draw(int x, int y) 
		{
			clearDraw();
			this->x = x;
			this->y = y;
			gotoxy(this->x, this->y);
			cout << "_o\n";
			gotoxy(this->x, this->y + 1);
			cout << " |\\\n";
			gotoxy(this->x, this->y + 2);
			cout << "/ >";
		}
		
		void jump(int n) 
		{
			if (this->y == Y || this->y == Y - 1)
				draw(this->x, this->y - n);
		}
		
};

class Arrow : public Base
{
	private:
		void clearDraw()
		{
			
			if (this->x >= 0 && this->x <= 117) 
			{
				gotoxy(this->x, this->y);
				cout << "   ";
			}
				
		}
		
	public:
		Arrow() 
		{
			this->x = 118;
			this->y = 22;
		}
		
		void draw() 
		{
			clearDraw();
			if (this->x <= 2)
				this->x = 120;
			draw(this->x - 2, this->y);
		}
		
		void draw(int x, int y)
		{
			clearDraw();
			this->x = x;
			this->y = y;
			gotoxy(this->x, this->y);
			if (this->x <= 117)
				cout << "<--";
		}
};

void drawGround() {
	gotoxy(0, Y+3);
	for (int i = 0; i < 120; i++)
		cout << char(164);
}

void updatePoint(int point)
{
	gotoxy(100, 8);
	cout << "Point: " << point;
}

void startGame() 
{
	int point = 0;
	updatePoint(0);
	drawGround();
	
	Dino *dino = new Dino();
	dino->drawStand();
	Arrow *arrow = new Arrow();
	arrow->draw(116, 23);
	Arrow *arrow_2 = new Arrow();
	arrow_2->draw(116 + 40, 24);
	Arrow *arrow_3 = new Arrow();
	arrow_3->draw(116 + 80, 22);
	while (true) 
	{
		if (kbhit()) {
			int key = getch();
			if (key == 32) {
				dino->jump(9);
			}
		}
		
		if ((arrow->getX() == dino->getX() + 2 && dino->getY() >= 19)
			|| (arrow_2->getX() == dino->getX() + 2 && dino->getY() >= 19)
			|| (arrow_3->getX() == dino->getX() + 2 && dino->getY() >= 19))
			return;
		
		if (arrow->getX() == dino->getX() - 2 || 
			arrow_2->getX() == dino->getX() - 2 || 
			arrow_3->getX() == dino->getX() - 2)
		{
			point++;
			updatePoint(point);
		}
		
		arrow->draw();
		arrow_2->draw();
		arrow_3->draw();
		dino->draw();
		Sleep(50);
	}
	
	delete arrow;
	delete arrow_2;
	delete arrow_3;
	delete dino;
}

int main()
{
	hidecursor();
	startGame();
	return 0;
}
