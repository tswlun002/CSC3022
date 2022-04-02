#include "PGMimageProcessor.h"
#include<iostream>
#define println(x)	std::cout<<x<<std::endl;
using namespace tswlun002;

int main(int argc, char *argv[]){
    int min=3;int max; int threshold=128;
    std::string outputFilename, inputfilename;
    bool p=false;
    for(int i=0; i<argc; i++){
       
        if(i==1){
            inputfilename=argv[i];
        }
        if(argv[i][1]=='s'){
            min=std::atoi(argv[i+1]); 
            max=std::atoi(argv[i+2]);
        } 
        if(argv[i][1]=='t'){
            threshold=std::atoi(argv[i+1]);
        }
        if(argv[i][1]=='p'){
            p=true;
        }
        if(argv[i][1]=='w'){
            outputFilename=argv[i+1];
           
        }
    }
    
    PGMimageProcessor object(inputfilename);
    object.readFile();
    object.setComponentSize(min, max);
    object.setTreshold(threshold);
    if(p){
        object.extractComponents(threshold, min);
        object.filterComponentsBySize(min, max);
        println("Total number of components = "+std::to_string(object.getComponentCount()));
        println("Component smallest size = "+std::to_string(object.getSmallestSize()));
        println("Component Largest size = "+std::to_string(object.getLargestSize()));
    }
    object.writeComponents(outputFilename);
    return 0;
}

