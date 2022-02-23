#include "TagStruct.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace tswlun002;

#pragma region  DECLARE METHOD FOR THIS CLASS ONLY

void clear(void); // clear shell command

#pragma endregion


int main(){

    std::string argv;
    for(;;){
        
        std::cout<<"Enter an option (r, p, d, l) or c to clear shell command or q to quit, and  press ENTER"<<std::endl;
        std::getline(std::cin,argv);

        if(argv[0]=='r' && argv[2]!=' ' ){
            std::fstream file;
            //
            std::string filename = argv.substr(2);
            std::cout<<filename<<std::endl;

            //open file for reading
            file.open(filename,std::ios::in);
            
            //check if open
            if(file.is_open()){
            std::string line;

            //read line of the file and put it into variable line
            while(getline(file,line)){
                tswlun002::storeTagName(line,0);
                //tswlun002:: storeTagText(line);
            
            }
            //close file
            file.close();
            
            //store data
           tswlun002::storeTagData();
            }
        }
        //print out tag names and data
        if(argv[0]=='p'){
            
            tswlun002::toString();
        }
         // write data to file
        if(argv[0]=='d'){
            tswlun002::writeToFile();
        }
        //search tag name data
        else if(argv[0]=='l' && argv[2]!=' '){
            tswlun002::searchTag(argv.substr(2));
        }
        // clear shell command
        else if (argv[0]=='c'){
            clear();
        }
        //quit programme
        else if (argv[0]=='q'){
             break;
        }
        
    }

}
/**
 * @brief clear shell command 
 * 
 */
void clear(void){
    system("clear");
}



