/**
 * @file PGMimageProcessor.cpp
 * @author Lunga Tsewu (tswlun002@myuct.ac.za)
 * @brief  Image processing class that can extract all the connected components 
 * for the image,given some user-supplied threshold,, minimum size and maximum size 
 * @version 0.1
 * @date 2022-03-29
 * @copyright Copyright (c) 2022
 * 
 */
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
 */
PGMimageProcessor::PGMimageProcessor():filename(""),width(0),height(0),minimumComponent_Size(3),
 maximumComponent_Size(width*height),threshold_detection(128){
     valid_data.clear();
     componetsList.clear();
 }
/**
 * @brief Construct a new PGMimageProcessor object
 * @param _filename -to initialise filename data field
 */
PGMimageProcessor::PGMimageProcessor(const std::string & _filename): filename(_filename),width(0),height(0),minimumComponent_Size(3),
 maximumComponent_Size(width*height),threshold_detection(128){
     valid_data.clear();
     componetsList.clear();
 }
/**
 * @brief  constructor for class
 * Use for loop because Component are store unique pointer
 * @param other is other PGMimageProcessor object
 */ 
PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other):
filename(other.filename),threshold_detection(other.threshold_detection),
minimumComponent_Size(other.minimumComponent_Size),maximumComponent_Size(other.maximumComponent_Size)
,width(other.width),height(other.height),valid_data(other.valid_data){
    this->componetsList.clear();
     for(int i=0; i< other.componetsList.size(); i++){
         this->componetsList[i].get()->setComponentIdentifier(other.componetsList[i].get()->getIdentifier());
         this->componetsList[i].get()->setNumberPixelComponent(other.componetsList[i].get()->getNumberPixelComponent());
         this->componetsList[i].get()->setPixelCordinates(other.componetsList[i].get()->getPixelCordinates());
    }
}

/**
 * move constructor
 * @param other
 */ 
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor && other):
filename(other.filename),threshold_detection(other.threshold_detection),
minimumComponent_Size(other.minimumComponent_Size),maximumComponent_Size(other.maximumComponent_Size)
,width(other.width),height(other.height){
    valid_data =std::move(other.valid_data);
    componetsList =std::move(other.componetsList);
}

/**
 * @brief copy assignment 
 * Use for loop because Component are store unique pointer
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
     this->valid_data =other.valid_data;
     this->componetsList.clear();
     for(int i=0; i< other.componetsList.size(); i++){
         this->componetsList[i].get()->setComponentIdentifier(other.componetsList[i].get()->getIdentifier());
         this->componetsList[i].get()->setNumberPixelComponent(other.componetsList[i].get()->getNumberPixelComponent());
         this->componetsList[i].get()->setPixelCordinates(other.componetsList[i].get()->getPixelCordinates());
     }

    }
    return *this;
}

/**
 * move assigment  
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
     this->valid_data =std::move(other.valid_data);
     this->componetsList =std::move(other.componetsList);
    }
    return *this;
}
/**
 * @brief Reads image file (only pgm formated file)
 */
bool PGMimageProcessor::readFile(){
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
                bool readSuccessful =true;
                if(infile){
                    setDimenstions(num_of_cols, num_of_rows);
                    //std::cout<<num_of_cols<<" "<< num_of_rows<<std::endl;
                     toTwoDimenstio(data.get());
                    
                }
                else{
                    std::cout<<"Error at "<<infile.gcount()<<std::endl;
                    readSuccessful=false;
                }
                return readSuccessful;
            }
        }
    }
    else
    {
        std::cout<<"File Can not be found, enter correct name of the file"<< std::endl;
        return false; 
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
 * @brief Get the Max Size object
 */
int PGMimageProcessor::defualtedMaxSize()const{
   int max =height*width;
   return max;
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
 }
 /**
 * @brief Destroy the PGMimageProcessor object
 */
PGMimageProcessor::~PGMimageProcessor(){}

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
    //println((int)threshold);
    valid_data = std::move(std::vector(height, std::vector<int>(width)));
    extractOnThreshHoldComponent(threshold, valid_data);
    findComponent(valid_data,threshold,minValidSize,width*height);

    return componetsList.size();

}
/**
 * @brief process the input image to extract all the connected components,
 * based on the supplied threshold (0...255) 
 * @param data- data of image we use to check and change pixels that meet intesity threshold
 */
void  PGMimageProcessor::extractOnThreshHoldComponent(unsigned char threshold_detection,two_d_vector& data){
 
   
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if( ((int)allData[i][j]) >= ((int)threshold_detection) ){
                
                data[i][j]=255;
            }
            else{
                data[i][j]=0;
            }
        }
    }
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
void PGMimageProcessor::findComponent(two_d_vector& data,const unsigned char threshold,const int minimumSize, int maxSize){
     std::vector<std::pair<int,int>>coOrdinate_component;
     two_d_vector data1=data;
     int count =1;
     int count1 =1;
    for (int i=0; i<height; i++) 
    { 
        for (int j=0; j<width; j++){
            int currentPixel = data1[i][j]; 
            
            if((int)currentPixel>=(int)threshold){
                 
                int numberComponents=floodFill(data1, j, i, currentPixel,0,coOrdinate_component, 0);
                
                if(numberComponents>=minimumSize && numberComponents<=maxSize){
                    std::unique_ptr<ConnectedComponent>component ( new ConnectedComponent());
                    component->setComponentIdentifier(count);
                    component->setPixelCordinates(coOrdinate_component);
                    component->setNumberPixelComponent(numberComponents);
                    componetsList.push_back(std::move(component));
                    
                    ++count;
                    
                }
                else{
                    for(int j=0; j<coOrdinate_component.size(); j++){
                        int x  = coOrdinate_component[j].first;
                        int y =coOrdinate_component[j].second;
                        data[y][x]=0;
                    }
                }
                coOrdinate_component.clear();
                
            }
        }
    } 

}

/**
 * @brief  use flood fill algorithm to find & store co-ordinates of the connected components
 * and count the connected components
 * Make Queue and store forground pixel
 * while Queue is not empty
 * check if x and y are not out of bound
 * and check if data at (x,y) not equals to current pixel(which is always zero), if true
 * we replace data at (x,y) by zero  to not its visited
 * Store co-ordinate x,y and increment count
 * Get and store right connected component by recursive
 * Get and store left connected component by recursive
 * Get and store up connected component by recursive
 * Get and store down connected component by recursive
 * Else pop out 
 * return total connect components for forground pixel
 * @param data  data use to store connected components
 * @param x  - coordinate
 * @param y  - coordinate
 * @param currColor 
 * @param visitedPixel - pixel use to replace visited pixel
 * @param coOrdinates - co-ordinate of pixel
 * @param count - number pixel connect  for each forground pixel
 * @return int  total of connectect  for each forground pixels
 */
   
 int PGMimageProcessor::floodFill(two_d_vector& data,int x, int y, int currColor, int visitedPixel,
  std::vector<std::pair<int,int>>&coOrdinates,int count)
  {
    std::queue<std::pair<int,int>> Queue;

    Queue.push(std::make_pair(x,y));
    
    while(!Queue.empty()){
        
        x =Queue.front().first;
        y =Queue.front().second;
        if( x >= 0 && x < width && y >= 0 && y < height && data[y][x] != visitedPixel){
            data[y][x] = visitedPixel;
            coOrdinates.push_back(std::make_pair(x,y));
            ++count;
            Queue.push(std::make_pair(x+1,y));
            Queue.push(std::make_pair(x-1,y));
            Queue.push(std::make_pair(x,y+1));
            Queue.push(std::make_pair(x,y-1));
           
        }
        else{
            Queue.pop();
        }
    }
    return count;
 }

/** @brief  with an iterator - though your container of connected
 * components and filter out (remove) all the components which do not
 * obey the size criteria pass as arguments. The number remaining
 * after this operation should be returned.
 * @param minSize - minimum bound number of component connected 
 * @param maxSize - maximum bound number of component connected 
 * @return int number connected components meet bounds 
 */
int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
    
    std::vector<std::unique_ptr<ConnectedComponent>> componets =std::move(componetsList);

    int size =componets.size();
  
    for(int i=0; i<size; i++){
        
       if(componets[i]->getNumberPixelComponent()>=minSize && componets[i]->getNumberPixelComponent()<=maxSize){
           
           componets[i]->setComponentIdentifier(i+1);
           componets[i]->setPixelCordinates(componets[i].get()->getPixelCordinates());
           componets[i]->setNumberPixelComponent(componets[i].get()->getNumberPixelComponent());
           componetsList.push_back(std::move(componets[i]));
       }else{
           std::vector<std::pair<int,int>> componets1  =componets[i]->getPixelCordinates();
         
           for(int j=0; j<componets1.size(); j++){
                 int x  = componets1[j].first;
                 int y = componets1[j].second;
                 valid_data[y][x]=0;
           }
       }
   }
   return componetsList.size();
}


/**
 * @brief create a new PGM file which contains all current components
 * 255=component pixel, 0 otherwise) and write this to outFileName as a
 * valid PGM. the return value indicates success of operation  
 * @param outFileName - name of the pgm file
 * @return true  if successful created image
 * @return false  if image not succeful created
 */
bool PGMimageProcessor::writeComponents(const std::string & outFileName){
    std::shared_ptr<unsigned char[]> buffer(new unsigned char[width*height]);
    int n = width*height;
    
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            buffer[i*width+j]=valid_data[i][j];
        }
    }
   
    std::ofstream infile(outFileName+".pgm",std::ios::binary);
    infile<<"P5\n";
    infile<<width<<" "<<height<<"\n";
    infile<<255<<"\n";
    
    infile.write( reinterpret_cast<char *>(buffer.get()),(n)*sizeof(unsigned char));
    if(!infile){
        std::cout<<"Error in file"<<std::endl;
        return false;
    }
    else{
        return true;
    }
    infile.close();

}

/**
 * @brief Get the Component Count 
 */
int PGMimageProcessor::getComponentCount(void) const{
    return componetsList.size();
}
/**
 * @brief  return number of pixels in largest component
 */
int PGMimageProcessor::getLargestSize(void) const{
    if(!componetsList.empty()){
        int prev_componentsize  = componetsList[0]->getNumberPixelComponent();
        for(int i=1; i<componetsList.size();i++){
            int next_componentSize=componetsList[i]->getNumberPixelComponent();
            if(prev_componentsize<next_componentSize)
                prev_componentsize=next_componentSize;
            else
                prev_componentsize=prev_componentsize;
        }
        return prev_componentsize;

    }
    else
        return 0;
}

/**
 * @return  number of pixels in smallest component
 */
int PGMimageProcessor::getSmallestSize(void) const{
    if(!componetsList.empty()){
        int prev_componentsize  = componetsList[0]->getNumberPixelComponent();
        for(int i=1; i<componetsList.size();i++){
            int next_componentSize=componetsList[i]->getNumberPixelComponent();
            if(prev_componentsize<next_componentSize)
                prev_componentsize=prev_componentsize;
            else
                prev_componentsize=next_componentSize;
        }
        return prev_componentsize;

    }
    else
        return 0;
}
/** 
 * @brief  the data for a component to std::cout
 * see ConnectedComponent class;
 * print out to std::cout: component ID, number of pixels
*/
void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const{
    std::cout<<theComponent;
}


