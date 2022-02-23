#ifndef TAGSTRUCT_H
#define TAGSTRUCT_H
#include <string>
#include <vector>
namespace tswlun002{
    /**
     * @brief struct to store data of the xml file ,tag name, number tag appearence and tag text
     */
    struct TagStruct
    {
        /* data */
        std::string openArrow,closingArrow;
        std::string tagName;
        std::vector<std::string> tagNames;
        std::vector<int> numberTagPairs;
        std::vector<std::string> tagTexts;
        std::vector<std::string> tagData;
    };
    /**
     * @brief function to store tag name into vector TagName
     */
    int storeTagName(std::string line,int index);
    /**
     * @brief Get the Tag Name object
     * @return vector<int> tag name
     */
    std::vector<std::string> getTagName();
    
    /**
     * @brief Get the Number Tag Pair object
     * @return vectore of number tag pair
     */
    std::vector<int> getNumberTagPair();
    /**
     * @brief  store tag text into vector tagTexts
     */
    void storeTagText(std::string line);
    /**
     * @brief Get the Tag Text object
     * @return std::string text of the tag
     */
    std::string getTagText();
    
    
    /**
     * @brief check tag name if is in a vector of tag names
     * 
     * @param index  start index when search for tag name in a vector
     * @return true  if vector contains tag name
     * @return false if vector does not contains tag name
     */
    bool checkExists(int index);

    /**
    * @brief extract tag text in a string line 
    * @param line  is the string 
    * @return string  tag text 
    */
    std::string extractTagText(std::string line); 

    /**
     * @brief Get the Index tag name in a vector
     * 
     * @param index start index 
     * @return int index of the tag name
     */
    int getIndex(int index); 
    
    /**
     * @brief chek if string line contains closing tag or opening tag
     * @param line  string line 
     * @return true if string line contains closing or openning tag
     * @return false if string line does not contains closing or openning tag
     */
    bool checkTags(std::string line); 
    
    /**
     * @brief Store formated tag data 
     * formart: tag name : number tag pairs : tag texts
     */
     void storeTagData();
    
    /**
     * @brief Write tags and its data to file 
     */
    void writeToFile();
    
    /**
     * @brief Search tag name and print tag with its data
     * @param tagName  searched and print its data
     */
    void searchTag(std::string tagName);
    
    /**
     * @brief Store nested tag name from string line
     * @param line string line 
     */
    void storeNestedTag(std::string line);
      
    /**
     * @brief print out data of the tagStruct (tag name, number tag pair and text(s))
     */
    void toString();
    


}
#endif  