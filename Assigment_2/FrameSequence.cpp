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
 */
void FrameSequence::readFile(std::string filename){
    //frameSequence =frameSequenceObj;
    std::ifstream infile(filename, std::ios::binary);
    std::string inputLine;
    int maxIntensity, num_of_rows,num_of_cols;
    bool right_file =false;
    std::vector<int> flags;
    int numberChars =0;
    unsigned char * binaryData_oneDimension;
    
    if(infile.is_open())
    {  
        //std::cout<<"Reading.... "<<std::endl;
       while(getline(infile,inputLine)){
                //check if it has P5 and start with P5
         
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
                //std::cout<<"Read binary data .." <<std::endl;
              
                int numberPixels =num_of_cols*num_of_rows;
                binaryData_oneDimension =  new unsigned char[numberPixels];
                
                infile.seekg(numberChars+3,std::ios::beg);
                int size = infile.tellg();
                
                infile.read(reinterpret_cast<char *> (binaryData_oneDimension), (numberPixels)*sizeof(unsigned char));
                
                if(infile){
                    //std::cout<<"Done Reading file.Processing image frames..."<<std::endl;
                    frameSequence.toTwoDimension(binaryData_oneDimension,num_of_rows,num_of_cols);
                    
                }
                else{
                    std::cout<<"Error at "<<infile.gcount()<<std::endl;
                }
                
                delete [] binaryData_oneDimension;
                std::cout<<"Done! "<<std::endl;
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
void FrameSequence::toTwoDimension(unsigned char* binaryData_oneDimension,const int &num_of_rows,const int &num_of_cols){
    unsigned char ** binaryData_twoDimension;
  
    binaryData_twoDimension =  new unsigned char *[num_of_rows];
    for (int i =0 ; i<num_of_rows; i++){
        binaryData_twoDimension[i] =  new unsigned char[num_of_cols];
        for(int j=0 ; j<num_of_cols; j++){
            binaryData_twoDimension[i][j]=binaryData_oneDimension[i*num_of_cols+j];
        }
    }
    unsigned char ** imageFrame; 
    ExtractImageFrame(binaryData_twoDimension,imageFrame,num_of_rows,num_of_cols,frameSequence.start_x,frameSequence.start_y);
    std::cout<<"Number of image frames = "<<frameSequence.imageSequence.size()<<std::endl;
    writeToFile();
    /*for(int j=0 ; j<frameSequence.width; j++){
        delete[] imageFrame[j]; 
    }
    delete[] imageFrame;*/
    for(int j=0 ; j<num_of_rows; j++){
            delete[] binaryData_twoDimension[j]; 
        }
    delete[] binaryData_twoDimension;
   
  
} 
void FrameSequence::writeToFile(){
     
    int size = frameSequence.imageSequence.size();
    int n =frameSequence.width*frameSequence.height;
    for(int x=0; x<size;x++){

        unsigned char * buffer = new unsigned char[n];

        for (int i =0 ; i<frameSequence.height; i++){
            for(int j=0 ; j<frameSequence.width; j++){
               // std::cout<<i<<"; "<<j<<" "<<(i*frameSequence.height+j)<<" "<<(frameSequence.imageSequence[x]==nullptr)<<std::endl;
                buffer[i*frameSequence.width+j]=frameSequence.imageSequence[x][i][j];
            }
        }
    
        std::ofstream infile(std::to_string(x)+".pgm",std::ios::binary);
        infile<<"P5\n";
        infile<<frameSequence.width<<" "<<frameSequence.height<<"\n";
        infile<<255<<"\n";
        
        infile.write(  reinterpret_cast<char *>(buffer),n);
        if(infile){
            //std::cout<<"Done writing file"<<x<<std::endl;
        }
        else{
            std::cout<<"Error in file"<<x<<std::endl;
        }
        infile.close();
        //delete[] buffer;

    }
    
}

/**
 * @brief Extarct  binary data for imageFrames from large image 
 * Get width image frame by adding width plus start x-axis
 * Get height image frame by adding width plus start y-axis
 * if start x-axis is less equals to end x-axis & start y-axis is less equals to end y-axis & x, y, size_row,size_col are still tha dimension large image
 * Store last image frame into vector
 * Else ,Start storing image frames using for loops
 * Store image frame into vector
 * Increment x and y coordinates for start to store another image frame
 * @param binaryData_oneDimension  is the 2-dimensional pointer of the large image
 * @param num_of_rows is the number of rows of the original large image
 * @param  number_of_cols is the number of columns of the original large image
 * @param x is the  start x-coordinate of the image frame
 * @param y is the  y-coordinate of the image frame
 */
void FrameSequence::ExtractImageFrame(unsigned char** binaryData_twoDimension,unsigned char ** imageFrame, int num_of_rows, int num_of_cols,int x, int y){
    //std::cout<<x<<"; "<<y<<std::endl;
     int size_row = frameSequence.width+y;
     int size_col = frameSequence.height+x;
     if ( y>=num_of_rows || x>=num_of_cols||x>frameSequence.end_x || y>frameSequence.end_y||size_row>=num_of_rows || size_col>=num_of_cols ){
         return;
     }
     else if(x==frameSequence.end_x && y==frameSequence.end_y &&frameSequence.end_y<num_of_rows &&frameSequence.end_x<num_of_cols ){
    
        storeImageFrame(binaryData_twoDimension,imageFrame, frameSequence.height, frameSequence.width,x,y);
        return;
    }
    else{
        storeImageFrame(binaryData_twoDimension,imageFrame, frameSequence.height, frameSequence.width,x,y);
        return ExtractImageFrame(binaryData_twoDimension,imageFrame,num_of_rows,num_of_cols,++x,++y);
    }

}
/**
 * @brief Start storing image frames using for loops
 * Store image frame into vector
 * Delete allocate space for store image frame 
 * @param binaryData_twoDimension  is the 2-dimensional pointer of the large image
 * @param size_row    width image frame
 * @param size_col    height image frame
 * @param x  is the  start x-coordinate of the image frame
 * @param y  is the  start y-coordinate of the image frame
 */
void FrameSequence::storeImageFrame(unsigned char** binaryData_twoDimension,unsigned char ** imageFrame, int size_row, int size_col,int x, int y){
    
    //std::cout<<x<<"; "<<y<<" "<<size_row<<" "<<size_col<<std::endl;
    imageFrame = new unsigned char*[size_row];
    for(int i=0; i<size_row;i++){
        imageFrame[i] = new unsigned char[size_col];
        for(int j=0; j<size_col;j++){
            imageFrame[i][j]=binaryData_twoDimension[x+i][y+j];
        }
    }
    
    frameSequence.imageSequence.push_back(imageFrame);
     

    /*for(int j=0 ; j<size_row; j++){
        delete[] imageFrame[j]; 
    }
    delete[] imageFrame;*/
    //std::cout<<"Number of image frames = "<<frameSequence.imageSequence[0][0][0]<<std::endl;
}



/**f[numberPixels/8]=0;
                std::fstream file;
                file.open("tag.txt",std::ios::out);
                file<<f;
                file.close();*/

