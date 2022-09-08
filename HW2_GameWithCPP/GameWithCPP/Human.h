#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "Monster.h"

// hint (_getch(), _kbhit()) 함수를 가지고 있는 헤더파일
#ifdef _WIN32
#include <conio.h>
#else
#include "Keyboard.h"
#endif

enum Direction
{
	Left = 97,    // a
	Right = 100,  // d
	Up = 119,     // w
	Down = 115    // s
};

// 사용자가 조작 할 수 있는 Player
class Human : public Monster
{
public:
	Human(string n = "Player", string i = "H", int px = 0, int py = 0)
		: Monster(n, i, px, py) {}
	~Human() { cout << " Player"; }

	// 키보드 입력이 있는지 감지하여 사용자를 움직여준다. 플레이어의 경우에는 쉬지않고 계속 움직일 수 있다.
	void move(vector<vector<int> > &map, int maxx, int maxy)
	{
		q = p;
		if(_kbhit())
		{
			char dir = _getch();
			if(dir=='w') p += Point(0,-1);
			else if(dir=='s') p += Point(0,1);
			else if(dir=='a') p += Point(-1,0);
			else if(dir=='d') p += Point(1,0);
			clip(maxx, maxy);
		}
		eat(map,false);
	}
};

#endif