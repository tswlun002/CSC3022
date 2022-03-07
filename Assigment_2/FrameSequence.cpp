#include "FrameSequence.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#define ROW
#define COLUMN
using namespace tswlun002;
/**
 * @brief initialise object of FrameSequence
 * 
 */
FrameSequence frameSequence;
/**
 * @brief Construct a new Frame Sequence:: Frame Sequence object
 * initialise x_start,y_start,end_x,y_end,width,height to zero;
 * initialise vector imageframe to empty by clearing it
 * initialise width and height to zero
 */
FrameSequence::FrameSequence(void){
    frameSequence.start_x=0;
    frameSequence.start_y=0;
    frameSequence.end_x=0;
    frameSequence.end_y=0;
    frameSequence.width=0;
    frameSequence.height=0;
    frameSequence.imageSequence.clear();
}
/**
 * @brief initialise start and end of frame
 * 
 * @param x_start  - start at x-axis
 * @param y_start  - start at -y-axis
 * @param x_end    - end at x-axis
 * @param y_end    - end at y-axix
 */
void  FrameSequence::setStartToEnd(int x_start,int y_start,int x_end,int y_end){
    frameSequence.start_x=x_start;
    frameSequence.start_y=y_start;
    frameSequence.end_x=x_end;
    frameSequence.end_y=y_end;
}

/**
 * @brief initialise dimension of frame image
 * 
 * @param width  - image frame
 * @param height - image frame
 */
void FrameSequence::setFrameSize(int width, int height){
    frameSequence.width=width;
    frameSequence.height=height;
}

/**
 * @brief Destroy the Frame Sequence:: Frame Sequence object
 *  vector imageframe to empty by clearing it
 */
FrameSequence::~FrameSequence(){
    frameSequence.imageSequence.clear();
}

/**
 * @brief Reads binary file and initialise FrameSequence object
 * We have vector which store for flags(1's) 
 * First check if the file has flag P5 in the file  in the first line, if yes then its right pgm file, increment numberChars by length line and push flag to vector Flags
 * If line start with # then that line is a comment,increment numberChars by length line
 * If flags vector size is equals to 1 and first char of line is not # the we read dimensions and push flag to vector Flags,increment numberChars by length line
 * If flag vector size is equals to 2 and line equals 255 then read intensity and push flag to vector Flags,increment numberChars by length line
 * If line empty , do nothing
 * If Flags vector size equals to 3 , we done reading information about data , we begin reading binary data from numberChars+3
 * 
 * @param filename 
 * @param frameSequenceObj 
 */
void FrameSequence::readFile(std::string filename, FrameSequence frameSequenceObj){
    frameSequence =frameSequenceObj;
    std::ifstream infile(filename, std::ios::binary);
    std::string inputLine;
    int maxIntensity, num_of_rows,num_of_cols;
    bool right_file =false;
    std::vector<int> flags;
    int numberChars =0;
    if(infile.is_open())
    {  

       while(getline(infile,inputLine)){
                //check if it has P5 and start with P5
            if(inputLine.length()==2 && inputLine== "P5" && flags.size()==0){
                right_file=true;

                numberChars += inputLine.length();
                flags.push_back(1);


            }
            else if( inputLine[0]!='#' && right_file && inputLine!="255"&& flags.size()==1 )
            { 
                std::istringstream iss (inputLine);
                while(!iss.eof()){
                   iss>> num_of_rows >>std::ws>>num_of_cols;  //get rows and columns

                }

                numberChars +=inputLine.length();
                flags.push_back(1);
            }
            else if(inputLine=="255"  && right_file==true && flags.size()==2)
            {   
                   maxIntensity = atoi(inputLine.c_str());   //get intensity
                   numberChars +=inputLine.length();
                   flags.push_back(1);

            }
            else if(inputLine[0]=='#'){
                    numberChars +=inputLine.length();  //get comment number

            }
            
            else if(flags.size()==3)
            {   
               
              
                int num_char =num_of_cols*num_of_rows;
                char f[num_char/8];
                infile.seekg(numberChars+3,std::ios::beg);
                int size = infile.tellg();
                infile.read(f,num_char/8);
                f[num_char/8]=0;
                std::fstream file;
                file.open("tag.txt",std::ios::out);
                file<<f;
                file.close();
                break;
            }
        }

    }

    else
    {
        std::cout<<"File Can not be found, enter correct name of the file"<< std::endl;     //if file does not open or exists,or entered wrong name
    }
    infile.close();
}

