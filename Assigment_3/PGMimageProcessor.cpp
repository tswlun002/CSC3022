#include "PGMimageProcessor.h"
#include <cstring>
#include <sstream>
#include <fstream>
#include <cmath>
#include <queue>
#define MAX_COMPONENT_SIZE(w,h) w*h
#define MIN_COMPONENT_SIZE 3
#define DEFAULTED_INTESITY 128
#define print(x) std::cout << x
#define println(x) std::cout << x << std::endl
using namespace tswlun002;

/**
 * @brief Construct a new PGMimageProcessor object
 * 
 */
PGMimageProcessor::PGMimageProcessor(){}
/**
 * @brief Construct a new PGMimageProcessor object
 * @param _filename -to initialise filename data field
 */
PGMimageProcessor::PGMimageProcessor(const std::string & _filename): filename(_filename){}
/**
 * copy constructor for class
 * @param other
 */ 
PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other):
filename(other.filename),threshold_detection(other.threshold_detection),
minimumComponent_Size(other.minimumComponent_Size),maximumComponent_Size(other.maximumComponent_Size)
,width(other.width),height(other.height){}

/**
 * move constructor
 * @param other
 */ 
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor && other):
filename(other.filename),threshold_detection(other.threshold_detection),
minimumComponent_Size(other.minimumComponent_Size),maximumComponent_Size(other.maximumComponent_Size)
,width(other.width),height(other.height){}

/**
 * copy operator
 * @return PGMimageProcessor
 */ 
PGMimageProcessor& PGMimageProcessor::operator = (const PGMimageProcessor & other)
{
    if(this != &other){
    this->filename     = other.filename;
     this->minimumComponent_Size = other.minimumComponent_Size;
     this->maximumComponent_Size = other.maximumComponent_Size;
     this->threshold_detection   = other.threshold_detection;
     this->width  = other.width;
     this->height = other.height;
    }
    return *this;
}

/**
 * move operator 
 * @return PGMimageProcessor
 */ 
PGMimageProcessor& PGMimageProcessor::operator = (PGMimageProcessor && other)
{
    if(this != &other){
     this->filename     = other.filename;
     this->minimumComponent_Size = other.minimumComponent_Size;
     this->maximumComponent_Size = other.maximumComponent_Size;
     this->threshold_detection   = other.threshold_detection;
     this->width  = other.width;
     this->height = other.height;
    }
    return *this;
}
/**
 * @brief Reads image file (only pgm formated file)
 */
void PGMimageProcessor::readFile(){
    std::ifstream infile(filename, std::ios::binary);
    std::string inputLine;
    int maxIntensity, num_of_rows,num_of_cols;
    bool right_file =false;
    std::vector<int> flags;
    int numberChars =0;
    
    
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
                   iss>> num_of_cols >>std::ws>>num_of_rows;  //get rows and column
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
                std::shared_ptr<unsigned char[]> data(new unsigned char[numberPixels]);
            
                infile.seekg(numberChars+3,std::ios::beg);
                int size = infile.tellg();
                infile.read(reinterpret_cast<char*>(data.get()), (numberPixels)*sizeof(unsigned char));
                if(infile){
                    setDimenstions(num_of_cols, num_of_rows);
                    std::cout<<num_of_cols<<" "<< num_of_rows<<std::endl;
                     toTwoDimenstio(data.get());
                    //writeToFile(data.get());
                    //extractAllComponent(data.get());
                }
                else{
                    std::cout<<"Error at "<<infile.gcount()<<std::endl;
                }
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
 * @brief Set the Dimenstions object
 * @param _width  of the image
 * @param _height of the image
 */
void PGMimageProcessor::setDimenstions(int _width, int _height){
    width=_width;
    height=_height;
}
/**
 * @brief set bound of the valid component 
 * @param minSize - minimum size of the valid component
 * @param maxSize - maximum size of the valid component
 */
 void PGMimageProcessor::setComponentSize(int minSize, int maxSize){
     minimumComponent_Size=minSize;
     maximumComponent_Size=maxSize;
 }
/**
 * @brief Set the Treshold object
 */
void PGMimageProcessor::setTreshold(int threshold=128){
    threshold_detection=threshold;
}
/**
 * @brief convert one-Dimension pointer array to two Dimenstion
 * 
 * @param data_oneD 
 */
 void PGMimageProcessor::toTwoDimenstio(const unsigned char *data_oneD){
     allData = std::vector(height, std::vector<unsigned char>(width));
     for(int row=0; row<height; row++){
         for(int column=0; column<width; column++){
            allData[row][column] =data_oneD[row*width+column];
         }
      }
      //extractAllComponent(temp_data.get()->get());
      println("Hey, its done");
 }
 /**
 * @brief Destroy the PGMimageProcessor object
 */
PGMimageProcessor::~PGMimageProcessor(){
}

/**
 * @brief  process the input image to extract all the connected components,
 * based on the supplied threshold (0...255) and excluding any components
 * of less than the minValidSize. The final number of components that
 * store in your container (after discarding undersized one)are returned.
 * @param threshold  - minimum threshold for pixels
 * @param minValidSize  - minimum size connect components
 * @return int  final number of components that store in your container
 */

int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize){
    valid_data = std::vector(height, std::vector<unsigned char>(width));
    extractOnThreshHoldComponent(threshold, valid_data);
    
    ConnectedComponent connectedComponent;
    
    findComponent(valid_data,threshold,minValidSize,connectedComponent);
     writeToFile(valid_data);
    
    println("size = "+std::to_string(connectedComponent.getPixelCordinates().size()));

    /* for(int i=0; i<connectedComponent.getNumberPixelComponent(); i++){
           //println(xy1[i].size());
           for(int j=0; j<connectedComponent.getPixelCordinates()[i].size(); j++){
                print(connectedComponent.getPixelCordinates()[i][j].first);
                print(connectedComponent.getPixelCordinates()[i][j].second);
                println("");
           }
    }*/
    return connectedComponent.getPixelCordinates().size();

}
/**
 * @brief process the input image to extract all the connected components,
 * based on the supplied threshold (0...255) 
 * @param data- data of image we use to check and change pixels that meet intesity threshold
 */
void  PGMimageProcessor::extractOnThreshHoldComponent(int threshold_detection,_2D_vector& data){
 
   
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            ((int)allData[i][j] >=threshold_detection)? data[i][j]=255:data[i][j]=0;
        }
    }
    std::cout<<width<<" "<< height<<std::endl;
   

}
 /**
  * @brief find components that meet intesity threshold and minimum 
  * number of compoonents
  * Loop through all pixels using dimensions width and height
  * Use helping method floodFill which implement FloodFill algorith 
  * to find connected components co-ordinated and number components
  * If components meet minimum size , its information is store 
  * which identifier , number connected component and co-ordinates of the connected component
  * @param data  is the data in 2-dimension vector with int type. It contain zero and 255 value
  * @param threshold  - intensity threshold of connected components
  * @param minimumSize  - minimum number of connected components
  * @param connectedComponent  - Object which store all the information of the component 
  */
void PGMimageProcessor::findComponent(_2D_vector& data,const int threshold,const int minimumSize,ConnectedComponent &connectedComponent){
     std::vector<std::pair<int,int>>coOrdinate_component;
     
     int count =0;
    for (int i=0; i<height; i++) 
    { 
        for (int j=0; j<width; j++){
            int currentPixel = data[i][j]; 
    
            if(currentPixel>=threshold){
                //println(currentPixel);
                int numberComponents=floodFill(data, j, i, currentPixel,0,coOrdinate_component, 0);
                 //println(numberComponents) ;
                if(numberComponents>=minimumSize){
                    connectedComponent.setComponentIdentifier(count);
                    ++count;
                    connectedComponent.setPixelCordinates(coOrdinate_component);
                    connectedComponent.setNumberPixelComponent(numberComponents);
                    coOrdinate_component.clear();
                }
               // xy1.push_back(coOrdinate_component);
                coOrdinate_component.clear();
                
            }
        }
    } 
    //println(connectedComponent.getPixelCordinates().size()) ;

}/**
 * @brief  use flood fill algorithm to find & store co-ordinates of the connected components
 * and count the connected components
 * First check if x and y are out of bound , if true, return count
 * check if data at (x,y) less 255, if true, return count
 * check if data at (x,y) equals to current pixel(which is always zero), if true, return count
 * Else, we replace data at (x,y) by zero  to not its visited
 * Store co-ordinate x,y and increment count
 * Get right connected component by recursive
 * Get left connected component by recursive
 * Get up connected component by recursive
 * Get down connected component by recursive
 * return total connect components for forground pixel
 * @param data  data use to store connected components
 * @param x  - coordinate
 * @param y  - coordinate
 * @param currColor 
 * @param currePixel - pixel use to replace visited pixel
 * @param coOrdinates - co-ordinate of pixel
 * @param count - number pixel connect  for each forground pixel
 * @return int  total of connectect  for each forground pixels
 */
   
 int PGMimageProcessor::floodFill(_2D_vector& data,int x, int y, int currColor, int currePixel, std::vector<std::pair<int,int>>&coOrdinates,int count){
 // Base cases 
    if (x < 0 || x >= width || y < 0 || y >= height){ 
         return count;
    }
    if (data[y][x]<255) {
         return count;
    } 
    if (data[y][x] == currePixel) {
          return count;
    }
    
    else{
    
        data[y][x] = currePixel; 
       
        coOrdinates.push_back(std::make_pair(x,y));
        count++;
        // Recursively call for north, east, south and west 
        int r= floodFill(data, x+1, y, currColor, currePixel, coOrdinates,count);  count=0;
        int l=floodFill(data, x-1, y, currColor, currePixel,coOrdinates,count);    count=0;
        int u= floodFill(data, x, y+1, currColor, currePixel,coOrdinates,count);  count=0;
        int d= floodFill(data, x, y-1, currColor, currePixel,coOrdinates,count); count=0;
       return r+l+u+d;
    }
    

 }

 /**
 * @brief Write pixels to file  to make image frame for vidoe
 * Convert 2-D image frames to 1-D pointer and write data to files
 * delete 1-D buffer 
 * @param imageSequence  vector of 2-D pointer  of image frames
 */
void PGMimageProcessor::writeToFile(_2D_vector data){
    std::shared_ptr<unsigned char[]> buffer(new unsigned char[width*height]);
    int n = width*height;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            buffer[i*width+j]=data[i][j];
        }
    }
   
    std::ofstream infile("Okay1.pgm",std::ios::binary);
    infile<<"P5\n";
    infile<<width<<" "<<height<<"\n";
    infile<<255<<"\n";
    
    infile.write( reinterpret_cast<char *>(buffer.get()),(n)*sizeof(unsigned char));
    if(!infile){
        std::cout<<"Error in file"<<std::endl;
    }
    infile.close();
    

    
    
}


