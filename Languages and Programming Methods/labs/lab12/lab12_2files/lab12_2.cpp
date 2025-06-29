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
                if(line.find("<script>")!=string::npos){
                    script_count++;
                }
                if(script_count==0){
                    data.emplace_back(line);
                }
                if(line.find("</script>")!=string::npos){
                    script_count--;
                }
            }

            ofstream o (filename);
            for(auto s: data){
                o << s << endl;
            }
        }
    }

    closedir(directory);
    return 0;
} 