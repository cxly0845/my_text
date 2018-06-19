#include"DataManager.h"

static DataManager * _instance = NULL;

DataManager * DataManager::getInstance()
{
	if (!_instance)
	{
		_instance = new DataManager();
	}
	return _instance;
}
void DataManager::getHighestScore()			//获取最高-最低分排序
{
	for (int i = 0; i<6; i++)
	for (int j = 0; j<6 - i - 1; j++)
	if (_rankScore[j]<_rankScore[j + 1])
	{
		int k = _rankScore[j];
		_rankScore[j] = _rankScore[j + 1];
		_rankScore[j + 1] = k;
	}
}
DataManager::DataManager()
{
	_currentScore = 0;
	_currentDistance = 0;			
	isBlink = false;
}