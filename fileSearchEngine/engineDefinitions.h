#include <vector>
#include <string>
using namespace std;

#ifndef ENGINEDEFINITIONS_H
#define ENGINEDEFINITIONS_H

typedef enum{
    EntryType_File,
    EntryType_Dir,
    EntryType_Invalid
}EntryType;

typedef struct{
    bool regex_enabled= false;

    bool directoryName= false;
    bool fileName= false;
    bool infile= false;
    bool caseSensitive= false;
    bool recursive= false;

    /* Excluded File Extensions */
    vector<string> excludedExtensions{};

}EngineSearchFilters;

typedef enum{
    Status_OK = 0,
    Status_NOK = 1,
    Status_Search_Completed
}Status;


#endif // ENGINEDEFINITIONS_H
