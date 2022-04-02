/**
 * @file Driver.cpp
 * @author Lunga Tsewu (tswlun002@myuct.ac.za)
 * @brief  file to take user commands or inputs
 * @version 0.1
 * @date 2022-03-29
 * @copyright Copyright (c) 2022
 * 
 */
#include "PGMimageProcessor.h"
#include<iostream>
#define println(x)	std::cout<<x<<std::endl; 
using namespace tswlun002;

int main(int argc, char *argv[]){
    int min=3;int max; int threshold=128;
    std::string outputFilename, inputfilename;
    bool printAll=false;
    bool sizeGiven= false;
    bool thresholdGive= false;
    bool ouputfileNameGiven=false;
    for(int i=0; i<argc; i++){
       
        if(i==1){
            inputfilename=argv[i];
        }
        if(argv[i][1]=='s'){
            min=std::atoi(argv[i+1]); 
            max=std::atoi(argv[i+2]);
            sizeGiven= true;
        } 
        if(argv[i][1]=='t'){
            threshold=std::atoi(argv[i+1]);
            thresholdGive= true;
        }
        if(argv[i][1]=='p'){
            printAll=true;
        }
        if(argv[i][1]=='w'){
            ouputfileNameGiven=true;
            outputFilename=argv[i+1];
           
        }
    }
    
    PGMimageProcessor object(inputfilename);
    object.readFile();

    if(!sizeGiven){
        max = object.defualtedMaxSize();
    }
    if(!thresholdGive){
        threshold=128;
    } 
    //set size and threhold
    object.setComponentSize(min, max);
    object.setTreshold(threshold);

    //if  p commands given else use defualted size and threshold
    if(printAll){
        object.extractComponents(threshold, min);
        object.filterComponentsBySize(min, max);
        println("Total number of components = "+std::to_string(object.getComponentCount()));
        println("Component smallest size = "+std::to_string(object.getSmallestSize()));
        println("Component Largest size = "+std::to_string(object.getLargestSize()));
    }else{
       object.extractComponents(threshold, min);
       object.filterComponentsBySize(min, max);
    }

    //if no ouput name given
    if(!ouputfileNameGiven){
        outputFilename="NNN";
    }

    object.writeComponents(outputFilename);
    return 0;
}

