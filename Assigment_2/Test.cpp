#include "FrameSequence.h"
#include <iostream>
#include <string>
using namespace tswlun002;

int main(int argc, char*argv[]){
    
    ///initialise object of the class
    FrameSequence frameSequence= FrameSequence();
    
    //vector for process names
    std::vector<std::string> processesNames;
    bool onPath;
    int n ;
    //store path or start-End
    std::vector<int> path;

    //initialise  motion
    frameSequence.setMotion(argv[argc-1]);
    
    //If  contains t , we use start to start - End  coordinates
    if(argv[2][1]=='t'){ 
        onPath =false;
        n=2;
    }

    //if contain p , we use Path points (polyline)
    if(argv[2][1]=='p'){
            onPath =true;
            n  = std::atoi(argv[3]);
        }
    
    //if we use path( master work), start after index to store path points
    //Else start at 3
    int index =0;
    if(onPath){ 
        index=4;
    }
    else{
        index=3; 
    }
    
    //Loop per number of path points or start-end system
    int jump=0;
    for(int i=0; i<n;){
        
        /**After s, initialise size of image frames
        *If we use path points, we use first points as initial points ans next  until XnYn
        *Else use start-end points
        */
        if(argv[n*2+index][1]=='s'){
            frameSequence.setFrameSize(atoi(argv[n*2+index+1]),atoi(argv[n*2+index+2]));
            if(onPath){
                frameSequence.setStartToEnd(atoi(argv[4+jump]), atoi(argv[5+jump]),atoi(argv[6+jump]),atoi(argv[7+jump])); 
            }
            else{
                frameSequence.setStartToEnd(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]),atoi(argv[6])); 
            } 
            frameSequence.readFile(argv[1]);
            jump=jump+2;
            
        }
        //store process and their names 
        std::vector<std::string> processes;
        for(int x=1; x<argc-(n*2+index+2);){
            int v =n*2+index+2+x;
            processes.push_back(argv[v+1]);
            processesNames.push_back(argv[v+2]);
            x=x+3;
        }
        //Loop through process, invoke methods accordingly if they are present on the vector
        for( int count =0;count<processes.size();count++){
            int v =n*2+index+3;
            if(argv[v][1]=='w'&& processes[count]=="none"){
                std::cout<<"Okay lunga"<<std::endl;
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.none();
            }
            else if(argv[v][1]=='w'&& processes[count]=="invert"){
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.invert();
            }
            else if(argv[v][1]=='w'&& processes[count]=="reverse"){
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.reverse();
            }
            else if(argv[v][1]=='w'&& processes[count]=="revinvert"){
                frameSequence.setOutputFileName(processesNames[count]);
                frameSequence.revinvert();
            }
        }
        // if we use path point, increment i of the loop by 1 
        // Else break because it we use start-end points which defaulted to 1
        if(onPath)
            i++;
        else
            break;
    }
    return 0;
}