#ifndef __DataManager_H__
#define __DataManager_H__
#include<iostream>

class DataManager

{
public:
	static DataManager * getInstance();
	void getHighestScore();
	int _rankScore[6];
	int _currentScore;			//Ŀǰ����
	int _currentDistance;		//Ŀǰ����
	bool isBlink;
private:
	DataManager();



};


#endif