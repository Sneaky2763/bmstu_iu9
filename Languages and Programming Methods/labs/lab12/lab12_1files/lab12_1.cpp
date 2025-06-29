#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

DIR* opendir ( const char *name );
int lstat ( const char *path, struct stat *buf);
struct dirent *readdir (DIR* dirp);
int closedir (DIR *dirp);

int main(int argc, char **argv){
    DIR* directory=opendir(argv[1]);
    dirent* file;

    while(1){
        file=readdir(directory);
        if(!file){
            break;
        }
        string filename=file->d_name;
        if(filename.length()>5 && filename.substr(filename.length()-5, filename.length())==".html"){
            ifstream f (filename);
            vector<string> data;
            string line;
            int script_count=0;
            while (getline(f,line)){

                string to_add="";
                for(int i=0; i<line.length(); ++i){
                    if(line[i]=='<'){
                        while(line[i]!='>'){
                            ++i;
                        }
                        ++i;
                    }
                    if(i>=line.length()){
                        break;
                    }

                    if(i<line.length()-3){
                        string next3=line.substr(i, 3);
                        if(next3=="&lt"){
                            to_add+="<";
                            i+=2;
                            continue;
                        }
                        if(next3=="&gt"){
                            to_add+=">";
                            i+=2;
                            continue;
                        }
                    }

                    to_add+=line[i];
                }

                if(to_add.length()>0){
                    data.emplace_back(to_add);
                }

            }

            ofstream o (filename.substr(0, filename.length()-5)+".txt");
            for(auto s: data){
                o << s << endl;
            }
        }
    }

    closedir(directory);
    return 0;
} 