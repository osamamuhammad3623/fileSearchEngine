#ifndef ENGINEDEFINITIONS_H
#define ENGINEDEFINITIONS_H

typedef enum{
    EntryType_File,
    EntryType_Dir
}EntryType;

typedef struct{
    bool directoryName= false;
    bool fileName= false;
    bool infile= false;
    bool caseSensitive= false;
    bool recursive= false;

    /* File Extensions */
    bool headerfile= false;
    bool cPlusPlus= false;
    bool python= false;
    bool txt= false;
}EngineSearchFilters;

#endif // ENGINEDEFINITIONS_H
