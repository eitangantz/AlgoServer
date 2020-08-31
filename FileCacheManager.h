/*
 * FileCacheManager.h
 *
 *  Created on: 14 Jan 2020
 *      Author: eitan
 */

#ifndef FILECACHEMANAGER_H_
#define FILECACHEMANAGER_H_
#include "CacheManager.h"
class FileCacheManager : public CacheManager<string,string> {
typedef std::list<string> LRUList;
typedef std::unordered_map<string, std::pair< string, typename std::list<string>::iterator> > UnorderedCache;
private:
LRUList lruList;
UnorderedCache cache;
int capacity;
public:
	FileCacheManager(int capa);
	virtual ~FileCacheManager();
	 bool isFileExist(string & filename);
	 string getSoultion(string problem);
	 void insertSulotion(string problem, string sulotion);
	 bool isSinTheCache(string problem);
};

#endif /* FILECACHEMANAGER_H_ */
