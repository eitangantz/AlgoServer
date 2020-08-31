/*
 * FileCacheManager.cpp
 *
 *  Created on: 14 Jan 2020
 *      Author: eitan
 */

#include "FileCacheManager.h"

FileCacheManager::FileCacheManager(int capa) {
	capacity = capa;
}

FileCacheManager::~FileCacheManager() {
	// TODO Auto-generated destructor stub
}

void FileCacheManager::insertSulotion(string problem,string sulotion){
	if(cache.find(problem) == cache.end()) {  //if the problem is not in the cache.
		if(lruList.size() == capacity) { //if cache is full. make place by deleting lru front.
		       const typename UnorderedCache::iterator it = cache.find(lruList.front());
		        cache.erase(it);
		        lruList.pop_front();
		}
		auto itr = lruList.insert(lruList.end(), problem); //(list<P>::iterator -- auto)
		cache.insert(make_pair(problem, make_pair(sulotion,itr)));
		//////////////////////////////////////////////////***
		string filename = problem;
		ofstream file;
		file.open(filename, ios::trunc | ios::binary);
		file<<sulotion;
		 //////////////////////////////////////////////////***
	} else {  // key is in the cache.
		lruList.erase((cache.find(problem)->second).second);
		cache.erase(problem);
		auto itr = lruList.insert(lruList.end(), problem);   //(list<P>::iterator -- auto)
		cache.insert(make_pair(problem, make_pair(sulotion,itr)));
		//////////////////////////////////////////////////***
		string filename = problem;
		ofstream file;
		file.open(filename, ios::trunc | ios::binary);
		file<<sulotion;
		 //////////////////////////////////////////////////***
	}
}
string FileCacheManager::getSoultion(string problem) {

	if(cache.find(problem) == cache.end()) { // key is not in the cache.
		//**********************************************

			string filename = problem;
			if(isFileExist(filename)) {

				     ifstream file;
				     file.open(filename, ios::binary);
				     string sulotion;
				     sulotion.assign(istreambuf_iterator<char>(file),istreambuf_iterator<char>());
				     //file.read((char *)&sulotion, sizeof(sulotion));

				 if(lruList.size() == capacity) {
			     const typename UnorderedCache::iterator it = cache.find(lruList.front());
			     cache.erase(it);
			     lruList.pop_front();
			     auto itr = lruList.insert(lruList.end(), problem);
			     cache.insert(make_pair(problem, make_pair(sulotion,itr)));
			     return (cache.find(problem)->second).first;
				} else {
				     auto itr = lruList.insert(lruList.end(), problem);
				     cache.insert(make_pair(problem, make_pair(sulotion,itr)));
				     return (cache.find(problem)->second).first;
				}
			} else {
				throw "Error- can't find the object";
			}

		 //**************************************************
	} else {
		string sulotion = (cache.find(problem)->second).first;
		lruList.erase((cache.find(problem)->second).second);
		cache.erase(problem);
		auto itr = lruList.insert(lruList.end(), problem);
		cache.insert(make_pair(problem, make_pair(sulotion,itr)));
		return sulotion;
	}

}
bool FileCacheManager::isFileExist(string & filename) {
    if (FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}
bool FileCacheManager::isSinTheCache(string problem) {
	return !(cache.find(problem) == cache.end());
}
