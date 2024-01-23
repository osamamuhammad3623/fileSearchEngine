#include "fileSearchEngine.h"


void FileSearchEngine::setKeyword(string newKeyword){
    if(newKeyword.empty() || (newKeyword.size() == 1) ){
        keywordFlag = Status_NOK;
    }else{
        keyword = newKeyword;
        keywordFlag = Status_OK;
    }
}

string FileSearchEngine::getKeyword(void){
    return keyword;
}

void FileSearchEngine::setDirPath(string newDirPath){
    if(getEntryType(newDirPath) == EntryType_Dir){
        dirPath = newDirPath;
        dirPathFlag = Status_OK;
    }else{
        dirPathFlag = Status_NOK;
    }
}

string FileSearchEngine::getDirPath(void){
    return dirPath;
}

Status FileSearchEngine::getStatus(void){
    return status;
}

void FileSearchEngine::setFilters(EngineSearchFilters newFilters){
    int flag=0;
    flag += newFilters.directoryName +
            newFilters.fileName +
            newFilters.infile +
            newFilters.caseSensitive +
            newFilters.recursive +
            newFilters.headerfile +
            newFilters.cPlusPlus +
            newFilters.python +
            newFilters.txt;

    if(flag > 0){
        filters = newFilters;
        filtersFlag = Status_OK;
    }else{
        filtersFlag = Status_NOK;
    }

}

vector<tuple<string,string,string>> FileSearchEngine::getResult(void){
//    sort(result.begin(), result.end());
//    auto last_it = unique(result.begin(), result.end());
//    result.erase(last_it, result.end());
    return result;
}

void FileSearchEngine::search(void){
    int flags = keywordFlag + dirPathFlag + filtersFlag;

    if(flags == 0){
        result.clear();
        vector<fs::directory_entry> content{};
        if(filters.recursive == 1){
            for(auto entry: fs::recursive_directory_iterator(dirPath)){
                content.push_back(entry);
            }
        }else{
            for(auto entry: fs::directory_iterator(dirPath)){
                content.push_back(entry);
            }
        }

        for(auto &entry: content){
            string entryFilename = entry.path().filename().u8string();
            string entryPath= entry.path().u8string();
            string entryExtension = entry.path().extension().u8string();

            if((fs::is_directory(entry) == 1) && (filters.directoryName == 1)){

                if(findKeyword(entryFilename)){
                    result.push_back(make_tuple(entryFilename, "Directory name",entryPath));
                }

            }else if (fs::is_regular_file(entry) == 1){

                if(filters.fileName == 1){
                    if(findKeyword(entryFilename)){
                        result.push_back(make_tuple(entryFilename, "File name",entryPath));
                    }
                }

                if(filters.infile == 1){
                    string data = readFile(entryPath);
                    if(findKeyword(data)){
                        result.push_back(make_tuple(entryFilename, "In-file search",entryPath));
                    }
                }

                if((filters.headerfile == 1)  && (entryExtension == ".h")){
                    if(findKeyword(entryFilename)){
                        result.push_back(make_tuple(entryFilename, ".h extension",entryPath));
                    }
                }

                if((filters.cPlusPlus == 1)   && ((entryExtension == ".cpp") || (entryExtension == ".c"))){
                    if(findKeyword(entryFilename)){
                        result.push_back(make_tuple(entryFilename, ".c/cpp extension",entryPath));
                    }

                }

                if((filters.python == 1) && (entryExtension == ".py")){
                    if(findKeyword(entryFilename)){
                        result.push_back(make_tuple(entryFilename,".py extension", entryPath));
                    }

                }

                if((filters.txt == 1) && (entryExtension == ".txt")){
                    if(findKeyword(entryFilename)){
                        result.push_back(make_tuple(entryFilename, ".txt extension",entryPath));
                    }
                }

            }
        }
        status = Status_Search_Completed;

    }else{
        status = Status_NOK;
    }
}

EntryType FileSearchEngine::getEntryType(string path){
    if(fs::is_directory(path) == 1){
        return EntryType_Dir;

    }else if(fs::is_regular_file(path) == 1){
        return EntryType_File;

    }else{
        return EntryType_Invalid;
    }
}

string FileSearchEngine::toLowerCase(string str){
    string result = str;
    for(int i=0; i< str.size(); i++){
        result[i] = tolower(str[i]);
    }

    return result;
}

bool FileSearchEngine::findKeyword(string data){
    int found=0;
    if(filters.caseSensitive == 1){
        found = data.find(keyword);
        if(found != string::npos){
            // keyword found
            return true;
        }else{
            return false;
        }

    }else{
        string loweredKeyword = toLowerCase(keyword);
        string loweredData = toLowerCase(data);

        found = loweredData.find(loweredKeyword);
        if(found != string::npos){
            // keyword found
            return true;
        }else{
            return false;
        }
    }
}

string FileSearchEngine::readFile(string path){
    string result = "";
    if(getEntryType(path) == EntryType_File){
        fstream fileStream;
        fileStream.open(path);
        if(fileStream.is_open()){
            string line;
            while(getline(fileStream, line)){
                result += line;
            }
        }
    }

    return result;
}
