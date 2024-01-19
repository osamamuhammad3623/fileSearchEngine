#include <string>
#include <vector>
using namespace std;

#ifndef FileSearchEngine_H
#define FileSearchEngine_H

struct SearchFilters{
    bool dirName = false;
    bool fileName = false;
    bool infile = false;
    bool caseSensitive = false;
    bool recursive = false;

    // file extensions
    bool header = false;
    bool cPlusPlus = false;
    bool py = false;
    bool txt = false;

};



class FileSearchEngine{

public:
    string keyword;
    string dirPath;
    string status;
    SearchFilters configs;
    vector<pair<string,string>> result;

    void search(void);
};

#endif /*FileSearchEngine_H*/
