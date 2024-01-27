#ifndef ENGINEDEFINITIONS_H
#define ENGINEDEFINITIONS_H

typedef enum{
    EntryType_File,
    EntryType_Dir,
    EntryType_Invalid
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

    /* Excluded File Extensions */
    bool exc_headerfile= false;
    bool exc_cPlusPlus= false;
    bool exc_python= false;
    bool exc_txt= false;

}EngineSearchFilters;

typedef enum{
    Status_OK = 0,
    Status_NOK = 1,
    Status_Search_Completed
}Status;


#endif // ENGINEDEFINITIONS_H
