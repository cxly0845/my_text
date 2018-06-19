#ifndef __DataManager_H__
#define __DataManager_H__
#include<iostream>

class DataManager

{
public:
	static DataManager * getInstance();
	void getHighestScore();
	int _rankScore[6];
	int _currentScore;			//目前分数
	int _currentDistance;		//目前距离
	bool isBlink;
private:
	DataManager();



};


#endif