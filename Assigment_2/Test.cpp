#include "FrameSequence.h"
#include <iostream>
#include <string>

using namespace tswlun002;
int main(int argc, char*argv[]){
      
    FrameSequence frameSequence= FrameSequence();
    //std::cout<< argv[2][1]<<std::endl;
    if(argv[2][1]=='t'){
        std::cout<< argv[2]<<std::endl;
        frameSequence.setStartToEnd(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]),atoi(argv[6]));
        std::cout<<"Setted"<<std::endl;
    }
    if(argv[7][1]=='s'){
        frameSequence.setFrameSize(atoi(argv[8]),atoi(argv[9]));
        frameSequence.readFile(argv[1]);
        
    }
     return 0;
}
