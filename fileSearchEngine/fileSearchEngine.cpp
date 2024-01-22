#include "fileSearchEngine.h"


void FileSearchEngine::setKeyword(string newKeyword){
    if(newKeyword.empty() || (newKeyword.size() == 1) ){
        status = Status_NOK;
    }else{
        keyword = newKeyword;
        status = (Status) (status | Status_OK);
    }
}

string FileSearchEngine::getKeyword(void){
    return keyword;
}

void FileSearchEngine::setDirPath(string newDirPath){
    if(getEntryType(newDirPath) == EntryType_Dir){
        dirPath = newDirPath;
        status = (Status) (status | Status_OK);
    }else{
        status = Status_NOK;
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
        status = (Status) (status | Status_OK);
    }else{
        status = Status_NOK;
    }

}

vector<pair<string,string>> FileSearchEngine::getResult(void){
    return result;
}

void FileSearchEngine::search(void){
    if(status == Status_OK){

        vector<fs::directory_entry> content;
        if(filters.recursive == 1){
            for(auto entry: fs::recursive_directory_iterator(dirPath)){
                content.push_back(entry);
            }
        }else{
            for(auto entry: fs::directory_iterator(dirPath)){
                content.push_back(entry);
            }
        }

        for(auto entry: content){

            if((fs::is_directory(entry) == 1) && (filters.directoryName == 1)){

                if(findKeyword(entry.path().filename().u8string())){
                    result.push_back(make_pair(entry.path().filename().u8string(), entry.path().u8string()));
                }

            }else if (fs::is_regular_file(entry) == 1){

                if(filters.fileName == 1){
                    if(findKeyword(entry.path().filename().u8string())){
                        result.push_back(make_pair(entry.path().filename().u8string(), entry.path().u8string()));
                    }
                }

                if(filters.infile == 1){
                    string data = readFile(entry.path().u8string());
                    if(findKeyword(data)){
                        result.push_back(make_pair(entry.path().filename().u8string(), entry.path().u8string()));
                    }
                }

                if((filters.headerfile == 1)  && (entry.path().extension() == ".h")){
                    if(findKeyword(entry.path().filename().u8string())){
                        result.push_back(make_pair(entry.path().filename().u8string(), entry.path().u8string()));
                    }
                }

                if((filters.cPlusPlus == 1)   && ((entry.path().extension() == ".cpp") || (entry.path().extension() == ".c"))){
                    if(findKeyword(entry.path().filename().u8string())){
                        result.push_back(make_pair(entry.path().filename().u8string(), entry.path().u8string()));
                    }

                }

                if((filters.python == 1) && (entry.path().extension() == ".py")){
                    if(findKeyword(entry.path().filename().u8string())){
                        result.push_back(make_pair(entry.path().filename().u8string(), entry.path().u8string()));
                    }

                }

                if((filters.txt == 1) && (entry.path().extension() == ".txt")){
                    if(findKeyword(entry.path().filename().u8string())){
                        result.push_back(make_pair(entry.path().filename().u8string(), entry.path().u8string()));
                    }
                }

            }
        }

        status = Status_Search_Completed;
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
