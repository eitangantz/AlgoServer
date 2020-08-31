/*
 * CacheManager.h
 *
 *  Created on: 14 Jan 2020
 *      Author: eitan
 */

#ifndef CACHEMANAGER_H_
#define CACHEMANAGER_H_

#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
template<class P, class S>
class CacheManager {
public:
	CacheManager(){}
	virtual ~CacheManager(){}
	virtual bool isFileExist(string & filename) = 0;
	virtual S getSoultion(P problem) = 0;
	virtual void insertSulotion(P problem, S sulotion) = 0;
	virtual bool isSinTheCache(P problem) = 0;
};

#endif /* CACHEMANAGER_H_ */
