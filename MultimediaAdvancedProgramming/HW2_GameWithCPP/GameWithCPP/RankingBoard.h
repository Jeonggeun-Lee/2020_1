#ifndef __RANKING_BOARD_H__
#define __RANKING_BOARD_H__

#include <iostream>
#include <fstream>
#include "FileException.h"
using namespace std;
#define NUM_MVP 5 // 최대 랭킹 기록 수

struct PlayInfo
{						// 게임 정보 클래스
	string name;		// 게이머의 이름
	int nItem;			// 획득한 아이템의 수
	double itemPerMove; // 이동 거리당 아이템 수
	PlayInfo(string na = "NewPlayer", int ni = 0, double ipm = 0.0) // 등록 기록이 없을 경우의 초기 값을 입력
		: name(na), nItem(ni), itemPerMove(ipm) {}
};

class RankingBoard
{ // 랭킹 관리 클래스
	string filename;
	PlayInfo MVP[NUM_MVP];
	int nMVP = NUM_MVP;

public:
	RankingBoard(string filename) : filename(filename) {}

	// 주어진 파일의 데이터를 읽어온다. 파일이 없는 경우 예외 처리를 한다.
	void load() throw(FileException)
	{
		ifstream is;
		is.open(filename);
		
		if(is.is_open() == false)
		{
			FileException e(filename, true);
			throw e;
		}
		
		int i = 0;
		string str;
		char n[100];
		while(!is.eof())
		{	
			getline(is,str);
			sscanf(str.c_str(),"%s %d %lf", n, &MVP[i].nItem, &MVP[i].itemPerMove);
			MVP[i].name = n;
			if(i>=NUM_MVP-1) break;
			++i;
		}
		
		is.close();
	}

	// 랭킹 리스트를 저장한다.
	void store()
	{
		ofstream os;
		string str;
		char arr[100];
		os.open(filename);
		for(int i=0; i<NUM_MVP; ++i)
		{
			sprintf(arr,"%s %d %f\n", MVP[i].name.c_str(), MVP[i].nItem, MVP[i].itemPerMove);
			str = arr;
			os.write(str.c_str(),str.size());
		}
		os.close();
	}

	// 랭킹 리스트를 1위부터 순서대로 출력한다.
	void print(string title = "Game Ranking")
	{
		cout << endl;
		cout << title << endl << endl;
		for(int i=0; i<NUM_MVP; ++i)
		{
			printf("[Rank %d] %-10s %10d %10lf\n",i+1, MVP[i].name.c_str(), MVP[i].nItem, MVP[i].itemPerMove);
		}

		cout << endl << "Press [ENTER] key..." << endl << endl;
		getchar();
	}

	// 게임이 끝난 후 플레이어의 기록을 입력한다.
	// nItem : 아이템 획득 수, ipm : 이동거리당 아이템 획득 비율 (아이템 획득 수 / 총 이동 거리)
	// 입력시 현재 기록과 비교하여 5위 이내인 경우 기록을 위한 이름을 받는다.
	void add(int nItem, double ipm)
	{
		if(nItem > MVP[NUM_MVP-1].nItem)
		{
			int i,j;
			for(i=0; i<NUM_MVP; ++i)
			{
				if(nItem > MVP[i].nItem) break;
			}
			cout << "[Rank " << i+1 <<"] ";
			char newPlayer[30];
			cout << "Insert Name: ";
			cin >> newPlayer;
			
			for(j=NUM_MVP-1; j>i; --j)
			{
				MVP[j].name = MVP[j-1].name;
				MVP[j].nItem = MVP[j-1].nItem;
				MVP[j].itemPerMove = MVP[j-1].itemPerMove;
			}
			MVP[i].name = newPlayer;
			MVP[i].nItem = nItem;
			MVP[i].itemPerMove = ipm;
			getchar();
		}
	}
};

#endif