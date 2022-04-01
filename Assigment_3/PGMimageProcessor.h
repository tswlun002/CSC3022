#ifndef PGMIMAGEPROCESSOR_H
#define PGMIMAGEPROCESSOR_H
#include "ConnectedComponent.h"
#include<string>
#include <memory>
#include <iostream>
//#define print(x) std::cout << x;
//#define println(x) std::cout << x << std::endl;

namespace tswlun002
{
    class PGMimageProcessor
    {
        typedef std::unique_ptr<std::unique_ptr<unsigned char[]>[]> _2DUnique_prt;
        typedef std::vector<std::vector<unsigned char>>  _2D_vector;
    private:

        /* data */
        std::string  filename;
        int width,height;
        int minimumComponent_Size, maximumComponent_Size;
        int threshold_detection;
        _2D_vector allData,valid_data;
        std::vector<_2DUnique_prt> data;
        ConnectedComponent connectedComponent;
        std::vector<std::vector<std::pair<int,int>>> componetsList;
    

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
        void findComponent(_2D_vector &data,const int threshold,const int minimumSize,ConnectedComponent &connectedComponent);
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
    };
    
    
} // namespace tswlun002

#endif