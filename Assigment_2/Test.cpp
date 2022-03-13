#include "FrameSequence.h"
#include <iostream>
#include <string>

using namespace tswlun002;
int main(int argc, char*argv[]){
      
    FrameSequence frameSequence= FrameSequence();
     std::vector<std::string> processesNames;
    
         std::cout<< argv[2]<<std::endl;
        frameSequence.setMotion(argv[argc-1]);
        if(argv[2][1]=='t'){ 
        std::cout<< argv[2]<<std::endl;
        frameSequence.setStartToEnd(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]),atoi(argv[6]));
        std::cout<<"Setted"<<std::endl;
        }
        if(argv[7][1]=='s'){
            frameSequence.setFrameSize(atoi(argv[8]),atoi(argv[9]));
            frameSequence.readFile(argv[1]);
            
        }
        std::vector<std::string> processes;
        
        for(int i=1; i<argc-10;){
            processes.push_back(argv[10+i]);
            if(argc>13)
                processesNames.push_back(argv[10+i+1]);
            else
                processesNames.push_back("");
            i=i+3;
        }
        
        for( int count =0;count<processes.size();count++){
             //std::cout<<"Pkay "<<processes[count]<<" "<<processesNames[count]<<std::endl;
            if(argv[10][1]=='w'&& processes[count]=="none"){
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.none();
            
                
            }
            else if(processes[count]=="invert"){
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.invert();
                
                
            }
            else if(processes[count]=="reverse"){
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.reverse();
                
                
            }
            else if(processes[count]=="revinvert"){
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.revinvert();
                
            }
        }

    
   
    
     return 0;
}