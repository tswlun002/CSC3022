#include "FrameSequence.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cmath>
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
    //std::cout<<frameSequence.start_x<<"; "<<frameSequence.start_y<<std::endl;
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
 * @brief Set the Motion
 * Motion can be horizontal, backwards , vertical,reverse,inverted, revinverted, invert
 * @param movement is the motion of the video
 */
void FrameSequence::setMotion(std::string movement){
    frameSequence.motion=movement;
}
/**
 * @brief set name of the output images
 * @param name name of the files 
 */
void FrameSequence::setOutputFileName(std::string name){
    frameSequence.ouputFileName=name;
}
/**
 * @brief Destroy the Frame Sequence:: Frame Sequence object
 *  vector imageframe to empty by clearing it
 */
FrameSequence::~FrameSequence(){
    int size = frameSequence.imageSequence.size();
     for(int x=0 ;x<size;x++){
        for (int i =0 ; i<frameSequence.height; i++){
            delete[] frameSequence.imageSequence[x][i];
        }
        delete[] frameSequence.imageSequence[x];
    }
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
 */
void FrameSequence::readFile(std::string filename){
    std::ifstream infile(filename, std::ios::binary);
    std::string inputLine;
    int maxIntensity, num_of_rows,num_of_cols;
    bool right_file =false;
    std::vector<int> flags;
    int numberChars =0;
    unsigned char * binaryData_oneDimension;
    
    if(infile.is_open())
    {  
        
       while(getline(infile,inputLine)){
               
            if( inputLine== "P5" && flags.size()==0){
                right_file=true;

                numberChars += inputLine.length();
                flags.push_back(1);


            }
            else if( inputLine[0]!='#' && right_file && inputLine!="255"&& flags.size()==1 )
            { 
                std::istringstream iss (inputLine);
                while(!iss.eof()){
                   iss>> num_of_cols >>std::ws>>num_of_rows;  //get rows and columns

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
                int numberPixels =num_of_cols*num_of_rows;
                binaryData_oneDimension =  new unsigned char[numberPixels];
                
                infile.seekg(numberChars+3,std::ios::beg);
                int size = infile.tellg();
                
                infile.read(reinterpret_cast<char *> (binaryData_oneDimension), (numberPixels)*sizeof(unsigned char));
                
                if(infile){
                   std::cout<<num_of_rows<<" "<< num_of_cols<<std::endl;
                    frameSequence.toTwoDimension(binaryData_oneDimension,num_of_rows,num_of_cols);
                    
                }
                else{
                    std::cout<<"Error at "<<infile.gcount()<<std::endl;
                }
                
                delete [] binaryData_oneDimension;
    
                break;
                
            }
        }

    }

    else
    {
        std::cout<<"File Can not be found, enter correct name of the file"<< std::endl; 
    }
    infile.close();
}
/**
 * @brief Store binary data into 2-Dimension pointer from 1-Dimention 
 * Store imageframe into vector imageSequence
 * And delete dynamical allocated space of the original image
 * @param binaryData_oneDimension  is the 1-dimensional pointer
 * @param num_of_rows is the number of rows of the image
 * @param  number_of_cols is the number of columns of the image
 */
void FrameSequence::toTwoDimension(unsigned char* binaryData_oneDimension,int num_of_rows,int num_of_cols){
    unsigned char ** binaryData_twoDimension;
  
    binaryData_twoDimension =  new unsigned char *[num_of_rows];
    for (int i =0 ; i<num_of_rows; i++){
        binaryData_twoDimension[i] =  new unsigned char[num_of_cols];
        for(int j=0 ; j<num_of_cols; j++){
            binaryData_twoDimension[i][j]=binaryData_oneDimension[i*num_of_cols+j];
        }
    }
    unsigned char ** imageFrame; 
    frameSequence.imageSequence.reserve(num_of_rows-(frameSequence.height-frameSequence.end_y));
    
    ExtractImageFrame(binaryData_twoDimension,imageFrame,num_of_rows,num_of_cols,frameSequence.start_x,frameSequence.start_y);

    for(int j=0 ; j<num_of_rows; j++){
            delete[] binaryData_twoDimension[j]; 
        }
    delete[] binaryData_twoDimension;
} 
/**
 * @brief Make image frame of no modification of data by
 * just writing frame Images pixels at it is to file
 */
void FrameSequence::none(){
    writeToFile(frameSequence.imageSequence);
}

void FrameSequence::invert(){
    int size = frameSequence.imageSequence.size();
    int n =frameSequence.width*frameSequence.height;
    unsigned char ** invertedFrames;
    std::vector<unsigned char **> invertedImageSequence;
    invertedImageSequence.reserve(size);

    for(int x=0 ;x<size;x++){
        invertedFrames =  new unsigned char *[frameSequence.height];
        for (int i =0 ; i<frameSequence.height; i++){
            invertedFrames[i] =  new unsigned char[frameSequence.width];
            for(int j=0 ; j<frameSequence.width; j++){
                invertedFrames[i][j]= 255-frameSequence.imageSequence[x][i][j];
            }
        }
        invertedImageSequence.push_back(invertedFrames);
    }

    writeToFile(invertedImageSequence);

    for(int x=0 ;x<size;x++){
        for (int i =0 ; i<frameSequence.height; i++){
            delete[] invertedImageSequence[x][i];
        }
        delete[] invertedImageSequence[x];
    }

}
/**
 * @brief Reverse pixels of image frames  to make new image
 * Read pointer array from last index to first index
 * Write make images by invoking writeTofile method
 * Delete temporay  dynamical allocated pointer called  invertedFrames
 */
void FrameSequence::reverse(){
    int size = frameSequence.imageSequence.size();
    int n =frameSequence.width*frameSequence.height;
    unsigned char ** invertedFrames;
    std::vector<unsigned char **> invertedImageSequence;
    invertedImageSequence.reserve(size);

    for(int x=size-1 ;x>=0;--x){
        invertedFrames =  new unsigned char *[frameSequence.height];
        for (int i =frameSequence.height-1; i>=0; --i){
            invertedFrames[i] =  new unsigned char[frameSequence.width];
            for(int j=frameSequence.width-1 ; j>=0; --j){
                
                invertedFrames[i][j]= frameSequence.imageSequence[x][i][j];
            }
          
        }
        invertedImageSequence.push_back(invertedFrames);
    }

    writeToFile(invertedImageSequence);

    for(int x=0 ;x<size;x++){
        for (int i =0 ; i<frameSequence.height; i++){
            delete[] invertedImageSequence[x][i];
        }
        delete[] invertedImageSequence[x];
    }

}

/**
 * @brief invert pixels then reverse them
 * to invert , Subtract 255 to each pixel 
 * to Reverse, read from last fram start from last pixel to first pixel of each frame
 * Write to file 
 * Delete dynamic allocated space 
 */
void FrameSequence::revinvert(){
    int size = frameSequence.imageSequence.size();
    int n =frameSequence.width*frameSequence.height;
    unsigned char ** revInvertedFrames;
    std::vector<unsigned char **> revInvertedImageSequence;
    revInvertedImageSequence.reserve(size);

    for(int x=size-1 ;x>=0;--x){
        revInvertedFrames =  new unsigned char *[frameSequence.height];
        for (int i =frameSequence.height-1; i>=0; --i){
            revInvertedFrames[i] =  new unsigned char[frameSequence.width];
            for(int j=frameSequence.width-1 ; j>=0; --j){
                revInvertedFrames[i][j]= 255-frameSequence.imageSequence[x][i][j];
            }
        }
        revInvertedImageSequence.push_back(revInvertedFrames);
    }

     writeToFile(revInvertedImageSequence);

    for(int x=0 ;x<size;x++){
        for (int i =0 ; i<frameSequence.height; i++){
            delete[] revInvertedImageSequence[x][i];
        }
        delete[] revInvertedImageSequence[x];
    }
    
}


/**
 * @brief Write pixels to file  to make image frame for vidoe
 * Convert 2-D image frames to 1-D pointer and write data to files
 * delete 1-D buffer 
 * @param imageSequence  vector of 2-D pointer  of image frames
 */
void FrameSequence::writeToFile(std::vector<unsigned char **> imageSequence){
    int size = imageSequence.size();
    int n =frameSequence.width*frameSequence.height;
    
    for(int x=0; x<size;x++){

        unsigned char * buffer = new unsigned char[n];

        for (int i =0 ; i<frameSequence.height; i++){
            for(int j=0;j<frameSequence.width; j++){
                buffer[i*frameSequence.width+j]=imageSequence[x][i][j];
            }
        }
    
        std::ofstream infile(frameSequence.ouputFileName +"-"+std::to_string(x)+".pgm",std::ios::binary);
        infile<<"P5\n";
        infile<<frameSequence.width<<" "<<frameSequence.height<<"\n";
        infile<<255<<"\n";
        
        infile.write( reinterpret_cast<char *>(buffer),(n)*sizeof(unsigned char));
        if(!infile){
            std::cout<<"Error in file"<<x<<std::endl;
        }
        infile.close();
        delete[] buffer;

    }
    
}

/**
 * @brief Extarct  binary data for imageFrames from large image 
 * Get width image frame by adding width plus start x-axis
 * Get height image frame by adding width plus start y-axis
 * if start or end is out bound by negetive, we let it to be zero
 * if start x-axis is less equals to end x-axis & start y-axis is less equals to end y-axis & x, y, size_row,size_col are still tha dimension large image
 * Store last image frame into vector
 * Else ,Start storing image frames using for loops
 * Store image frame into vector
 * Increment or decrement x and y coordinates for start to store another image frame
 * @param binaryData_oneDimension  is the 2-dimensional pointer of the large image
 * @param num_of_rows is the number of rows of the original large image
 * @param  number_of_cols is the number of columns of the original large image
 * @param x is the  start x-coordinate of the image frame
 * @param y is the  y-coordinate of the image frame
 */
void FrameSequence::ExtractImageFrame(unsigned char** binaryData_twoDimension,unsigned char ** imageFrame, int num_of_rows, int num_of_cols,int x, int y){
      if(x<0){
          x=0;
      }
      if(y<0){
           y=0;
      }
      if(frameSequence.end_x<0){
          frameSequence.end_x=0;
      }
      if(frameSequence.end_y<0){
          frameSequence.end_y=0;
      }
      

     int size_row = frameSequence.height+y;
     int size_col = frameSequence.width+x;
     if ( y>=num_of_rows || x>=num_of_cols || size_row>=num_of_rows|| size_col>= num_of_cols ){
         return;
     }
    else if( (frameSequence.start_x!=frameSequence.end_x ||frameSequence.start_y!=frameSequence.end_y)  && (x==frameSequence.end_x && y==frameSequence.end_y) ){
        return;
    }
    else if(frameSequence.start_x==frameSequence.end_x &&frameSequence.start_y==frameSequence.end_y){
        storeImageFrame(binaryData_twoDimension,imageFrame, num_of_rows, num_of_cols,x,y);
        return;
    }
    else{

        storeImageFrame(binaryData_twoDimension,imageFrame,num_of_rows, num_of_cols,x,y);


        if(x<frameSequence.end_x&&frameSequence.start_x<frameSequence.end_x){
            ++x;
        }else if(frameSequence.start_x==frameSequence.end_x&& x==frameSequence.end_x){
            x=frameSequence.end_x;
        }
        else if( frameSequence.start_x>frameSequence.end_x&&x>frameSequence.end_x) {
            --x;
        }
        if(y<frameSequence.end_y  &&frameSequence.start_y<frameSequence.end_y){
            ++y;
            
        }
        else if(frameSequence.start_y==frameSequence.end_y && y==frameSequence.end_y){
            y=frameSequence.end_y;
        }
        else if( frameSequence.start_y>frameSequence.end_y&&y>frameSequence.end_y) {
            --y;
        }
        
        return ExtractImageFrame(binaryData_twoDimension,imageFrame,num_of_rows,num_of_cols,x,y);
    }

}
/**
 * @brief Start storing image frames using for loops
 * Store image frame into vector
 * Delete allocate space for store image frame 
 * If diference in y1-y2 is  0 , accelerate on the y-axis
 * If diference in x1-x2 is 0, accelerate on the x-axis
 * Else accelerate both axis
 * @param binaryData_twoDimension  is the 2-dimensional pointer of the large image
 * @param row    width image frame
 * @param col     height image frame
 * @param x  is the  start x-coordinate of the image frame
 * @param y  is the  start y-coordinate of the image frame
 */
void FrameSequence::storeImageFrame(unsigned char** binaryData_twoDimension,unsigned char ** imageFrame, int rows, int column,int x, int y){
    
    
    imageFrame = new unsigned char*[frameSequence.height];
    

    int temporalAcceleration = accelerateframes();
    for(int i=0; i<frameSequence.height;i++){
        imageFrame[i] = new unsigned char[frameSequence.width];
        for(int j=0; j<frameSequence.width;j++){
            
            if(y+i+temporalAcceleration<column&&frameSequence.start_x-frameSequence.end_x==0 && frameSequence.start_y != frameSequence.end_y)
                imageFrame[i][j]=binaryData_twoDimension[y+i+temporalAcceleration][x+j];
            else if(x+j+temporalAcceleration<column&&frameSequence.start_x!=frameSequence.end_x && frameSequence.start_y == frameSequence.end_y)
                imageFrame[i][j]=binaryData_twoDimension[y+i][x+j+temporalAcceleration];
            else{
                    if(x+j+temporalAcceleration<column && y+i+temporalAcceleration<rows)
                    imageFrame[i][j]=binaryData_twoDimension[y+i+temporalAcceleration][x+j+temporalAcceleration];
            }
        }
    }
    
    frameSequence.imageSequence.push_back(imageFrame);

    
}
/**
 * @brief initialise the maximum acceleration
 * 
 * @param MaxAccelaretion is the maximum acceleration and defaulted at zero
 */
void FrameSequence::setAccelarationFrames(int MaxAccelaretion=0){
    frameSequence.acceleration=0;
    if(MaxAccelaretion>0){
        frameSequence.maxAcceleration=MaxAccelaretion;
         
    }
    else{
        frameSequence.maxAcceleration=0;
    }
}
/**
 * @brief Calculate acceleration of the video
 * If maximum acceleration is not reached , we increment acceleration by 4
 * Else if we reached maximum acceleration , decrease by 4 until 2
 * @return int acceleration calculated
 */
int FrameSequence::accelerateframes(){
    if(frameSequence.maxAcceleration>0 && (frameSequence.acceleration<frameSequence.maxAcceleration ||frameSequence.acceleration<2)){
        frameSequence.acceleration+=4; 
    }
    else if(frameSequence.maxAcceleration>0 && frameSequence.acceleration<frameSequence.maxAcceleration){
        frameSequence.acceleration-=4;
    } 
    return frameSequence.acceleration;

}





