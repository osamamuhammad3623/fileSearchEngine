#include <string>
#include <vector>
#include "engineDefinitions.h"
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace std;

#ifndef FILESEARCHENGINE
#define FILESEARCHENGINE


class FileSearchEngine{
private:
    string keyword;
    string dirPath;
    string status;
    EngineSearchFilters filters;
    vector<pair<string,string>> result;


public:
    void setKeyword(string newKeyword);
    string getKeyword(void);

    void setDirPath(string newDirPath);
    string getDirPath(void);

    string getStatus(void);

    void setFilters(EngineSearchFilters newFilters);

    vector<pair<string,string>> getResult(void);

    void search(void);

    EntryType getEntryType(string path);

    bool findKeyword(string data);

    string readFile(string path);
};

#endif /*FILESEARCHENGINE*/
