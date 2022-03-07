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
        void readFile(std::string file,FrameSequence frameSequenceObj);
        /**
         * @brief Set the Image frame into image sequence vector
         * @param imageFrame - 2-d array which has store pixels of the image
         */
        void setImageSequence(unsigned char ** imageFrame);
        /**
         * @brief Get the Image Sequence object
         * @return std::vector<unsigned char **>  image Sequence
         */
        std::vector<unsigned char **> getImageSequence();

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

         
    };
    

}
#endif //FRAMESEQUENCE_H