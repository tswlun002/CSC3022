#ifndef FRAMESEQUENCE_H
#define FRAMESEQUENCE_H
#include <string>
#include <vector>
namespace tswlun002{

    class FrameSequence
    {
    public:
        /**
         * @brief private field to store data
         * imageSequence is the vector to store 2-D image frames
         * start_x - x co-ordinate where we start to store frame at x-axis
         * start_y - y co-ordinate where we start to store frame at y-axis
         * end_x - x co-ordinate where we stop to store frame at x-axis
         * end_y - y co-ordinate where we stop to store frame at y-axis
         * Width - distance between start_x to end_x
         * height - distance between start_y to end_y
         */
        std::vector<unsigned char **> imageSequence;
        int start_x,start_y,end_x,end_y, width,height;
        std::string motion,ouputFileName;

    
        /**
         * @brief Construct a new Frame Sequence object
         * 
         */
        FrameSequence(void);
        /**
         * @brief Destroy the Frame Sequence object
         * 
         */
         ~FrameSequence();
        
        /**
         * @brief Read the bpm file 
         * Get dimensions of the file
         * Get intensity of file
         * 
         * @param file name of file we will use or read
         */
        void readFile(std::string file);

        /**
         * @brief Set the Start To End image frame
         * @param x_start - start x-axis 
         * @param y_start - start y-axis
         * @param x_end   - end x-axis
         * @param y_end   - end y-axis
         */
        void setStartToEnd(int x_start,int y_start,int x_end,int y_end);
        /**
         * @brief Set the Frame Size object
         * @param width - width of image frame
         * @param height - height of image frame
         */
        void setFrameSize(int width, int height);
        /**
         * @brief Set the Image frame into image sequence vector
         * @param imageFrame - 2-d array which has store pixels of the image
         */
        
        /**
         * @brief Set the Motion
         * Motion can be horizontal, backwards , vertical,reverse,inverted, revinverted, invert
         * @param movement is the motion of the video
         */
        void setMotion(std::string movement);
        /**
         * @brief Set the Output File Name 
         * 
         * @param name  of the ouput images
         */
        void setOutputFileName(std::string name);
        /**
         * @brief Store binary data into 2-Dimension pointer from 1-Dimention
         * 
         * @param binaryData_oneDimension  is the 1-dimensional pointer
         * @param num_of_rows is the number of rows of the image
         * @param  number_of_cols is the number of columns of the image
         */
        void toTwoDimension(unsigned char* binaryData_oneDimension,int num_of_rows,int num_of_cols);
        
        /**
         * @brief Extarct  binary data for imageFrames from large image 
         * 
         * @param binaryData_oneDimension  is the 2-dimensional pointer of the large image
         * @param imageFrame - pointer array to store pixels image frame
         * @param num_of_rows is the number of rows of the image
         * @param  number_of_cols is the number of columns of the image
         * @param x is the  x-coordinate
         * @param y is the  y-coordinate
         */
        void ExtractImageFrame(unsigned char** binaryData_oneDimension,unsigned char ** imageFrame, int num_of_rows, int num_of_cols,int x, int y);
        /**
         * @brief Store image frame into vector
         * @param binaryData_twoDimension  is the 2-dimensional pointer of the large image
         * @param imageFrame - pointer array to store pixels image frame
         * @param size_row    width image frame
         * @param size_col    height image frame
         * @param x  is the  start x-coordinate of the image frame
         * @param y  is the  start y-coordinate of the image frame
         */
        void storeImageFrame(unsigned char** binaryData_twoDimension,unsigned char ** imageFrame , int size_row, int size_col, int x, int y);
        /**
         * @brief write image frame to file to make pgm images
         * @param imageSequence is the vector of image frames
         */
        void writeToFile(std::vector<unsigned char **> imageSequence);
        
        /**
         * @brief make image frames with none process 
         */
          void none();
        /**
         * @brief invert pixels of the image frames to produce  new inverted images
         * we use 255-v  to invert pixels, where v unsigned char pixel 
         */
        void invert();
        /**
         * @brief Reverse pixels of image frames  to make new image
         */
        void reverse();
        
        /**
         * @brief invert pixels then reverse them
         * 
         */
        void revinvert();

        void setImageSequence(unsigned char ** imageFrame);
        /**
         * @brief Get the Image Sequence object
         * @return std::vector<unsigned char **>  image Sequence
         */
        std::vector<unsigned char **> getImageSequence();  
    };

    

}
#endif //FRAMESEQUENCE_H