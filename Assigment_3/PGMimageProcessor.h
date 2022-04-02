#ifndef PGMIMAGEPROCESSOR_H
#define PGMIMAGEPROCESSOR_H
#include "ConnectedComponent.h"
#include<string>
#include <memory>
#include <iostream>
namespace tswlun002
{
    class PGMimageProcessor
    {
    typedef std::vector<std::vector<unsigned char>>  _2D_vector;
        
    private:

        /* data */
        std::string  filename;
        int width,height;
        int minimumComponent_Size, maximumComponent_Size;
        int threshold_detection;
        _2D_vector allData,valid_data;
        std::vector<std::unique_ptr<ConnectedComponent>> componetsList;
    
    

    public:
        
         /**
          * @brief Construct a new PGMimageProcessor object
          * 
          */
         PGMimageProcessor();
        /**
         * @brief Construct a new PGMimageProcessor object
         * @param _filename -to initialise filename data field
         */
        PGMimageProcessor(const std::string & _filename);
        /**
         * copy constructor for class
         * @param other
         */ 
        PGMimageProcessor(const PGMimageProcessor& other);
        /**
         * move constructor
         * @param other
         */ 
        PGMimageProcessor(PGMimageProcessor && other);
        /**
         * copy operator
         * @return PGMimageProcessor
         */ 
        PGMimageProcessor& operator = (const PGMimageProcessor & other);
        /**
         * move operator 
         * @return PGMimageProcessor
         */ 
        PGMimageProcessor& operator = (PGMimageProcessor && other);
        /**
         * @brief Reads image file (only pgm formated file)
         */
        void readFile();
        /**
         * @brief Set the Dimenstions object
         */
        void setDimenstions(int _width, int _height);
        /**
         * @brief Set the Component Size object
         */
        void setComponentSize(int min, int max);
        /**
         * @brief Set the Treshold object
         */
        void setTreshold(int treshold);
        /**
         * @brief strauct data to dimension pointer array
         * 
         */
        void toTwoDimenstio(const unsigned char *data_oneD);
         /**
          * @brief Store componets 
          */
         void storeComponents();
        /**
         * @brief process the input image to extract all the connected components,
         * based on the supplied threshold (0...255) and excluding any components
         * less than the minValidSize
         */
        int extractComponents(unsigned char threshold, int minValidSize);
        /**
         * @brief extract all components 
         */
        void  extractOnThreshHoldComponent(int threshold,_2D_vector& data);
        /**
         * @brief  find components that meet intesity threshold and minimum 
         * number of compoonents 
         */
        void findComponent(_2D_vector &data,const int threshold,const int minimumSize);
     /**
      * @brief implement floodfill algorithm to get connected components
      */
        int floodFill(_2D_vector &data,int x, int y, int currColor,
         int currePixel, std::vector<std::pair<int,int>>&data1,int count);

        /** iterate - with an iterator - though your container of connected
         * components and filter out (remove) all the components which do not
         * obey the size criteria pass as arguments. The number remaining
         * after this operation should be returned.
        */
        int filterComponentsBySize(int minSize, int maxSize);
        /**
         * @brief Destroy the PGMimageProcessor object
         */
        ~PGMimageProcessor();
        /**
         * @brief create a new PGM file which contains all current components
         * 255=component pixel, 0 otherwise) and write this to outFileName as a
         * valid PGM. the return value indicates success of operation 
         */
        bool writeComponents(const std::string & outFileName);
        /**
         * @brief Get the Component Count 
         */
        int getComponentCount(void) const;

        /**
         * @brief  return number of pixels in largest component
         */
        int getLargestSize(void) const;
        /**
         * @return  number of pixels in smallest component
         */
        int getSmallestSize(void) const;

        /** 
         * @brief  the data for a component to std::cout
         * see ConnectedComponent class;
         * print out to std::cout: component ID, number of pixels
        */
        void printComponentData(const ConnectedComponent & theComponent) const;
    };
    
    
} // namespace tswlun002

#endif