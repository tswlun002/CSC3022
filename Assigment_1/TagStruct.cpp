#include "TagStruct.h"
#include <iostream>
#include <list>
#include <regex>
#include <fstream>
#define CLOSING_TAG(tagName)   "</"+tagName+">"   //closing  tag
#define OPEN_TAG(tagName)       "<"+tagName+">"   //opening  tag
#define INDEXES(yes)             (yes==1) ? 1 : 0  //
using namespace tswlun002;                        //namespace



/**
 * @brief  struct object to store  data (tag name, number of tag and tag text(s))
 */
TagStruct tagStruct;


/**
 * @brief  Store tag names from the given string line
 * first check if line is  not empty 
 * Then check if the first char of line is open arrow and second char of line is not slash forward
 * Exclude the open arrow and initialise tagName from TagStruct
 * Then extract chars of tag name and we concatenate them 
 * until char is equals to close arrow ('>')
 * Then break the loop 
 * 
 * Befor store tag name ,first check if there was clossing arrow and if tag name is not duplicate
 * If true, store the tag name 
 * 
 * @param line : string line where extract tag name 
 */
void tswlun002::storeTagName(std::string line){
     if(!line.empty()){

       tagStruct.openArrow = line[0];
       char forwardSlash = line[1];

       if(tagStruct.openArrow=="<" && forwardSlash!='/'){

            std::string newLine  = line.substr(1); //exclude "<"
            tagStruct.tagName="";    //init

            for (char c:newLine ) {
                if(c != '>'){
                    tagStruct.tagName = tagStruct.tagName+c;
                }
                else
                {
                   tagStruct.closingArrow=">";
                   //tagStruct.openArrow="";
                   break; 
                } 
            }
            if(tagStruct.closingArrow==">"  && !checkExists(0)){
                tagStruct.tagNames.push_back(tagStruct.tagName); 
               
            }  
        }
    }
}

/**
 * @brief Get vector of tag names
 * @return vector<string>  of tag names
 */
std::vector<std::string> tswlun002::getTagName(){
    return tagStruct.tagNames;
}

/**
 * @brief check if the Tag name is already stored using recursion
 * If tag names is empty or tag name does not exits i the vector, number equal to one
 * Else if already exists , increament current number of tag pair by one 
 * @param index : position check is the tag name alread exists
 * @return true if tag name already exists
 * @return false  if tag name is not stored yet
 */
bool tswlun002::checkExists(int index){
    if(tagStruct.tagNames.empty() || index==tagStruct.tagNames.size()){
        tagStruct.numberTagPairs.push_back(1);
        return false;
    }
    else if(tagStruct.tagNames[index]==tagStruct.tagName){
        tagStruct.numberTagPairs[index] = tagStruct.numberTagPairs[index]+1;
        return true;
    }
    else{
       return checkExists(++index);
    }
}

/**
 * @brief get vector of number of tag pairs
 * @return std::vector<int> of number of tag pairs
 */
std::vector<int> tswlun002::getNumberTagPair(){
  return tagStruct.numberTagPairs;
}

/**
 * @brief  store the extracted tag text  into a vector from string line
 * If the tag is duplicate , concatenate its tag text and seperate it by semi-colon
 * @param line   string line 
 */
void tswlun002::storeTagText(std::string line){
    
    if(!line.empty()){

        std::string text = extractTagText(line);
        if(!text.empty()){
            int index  = getIndex(0);

            text = trim(text);
            
            if( (tagStruct.tagTexts.size() ==0 )  && !text.empty()){
                tagStruct.tagTexts.push_back(text.substr(0,text.size()-(INDEXES(checkTags(line)))));
            }
            else{

                if( tagStruct.numberTagPairs[index]==1 &&  tagStruct.tagTexts.size()==index ){
                    tagStruct.tagTexts.push_back(text.substr(0,text.size()-(INDEXES(checkTags(line)))));
                }else{

                    std::string newText  = tagStruct.tagTexts[index];

                    //concatenate 
                    newText+=" : "+text.substr(0,text.size()-(INDEXES(checkTags(line))));
                
                    //insert back
                    tagStruct.tagTexts.insert(tagStruct.tagTexts.begin()+index,newText);

                    //erase next element after insertion
                    tagStruct.tagTexts.erase(tagStruct.tagTexts.begin()+(index+1));
                }
            }
        }
    }
    
}

/**
 * @brief extract tag text in a string line 
 * @param line  is the string 
 * @return string  tag text 
 */

std::string tswlun002::extractTagText(std::string line){

    std::string text ="";
    if(checkTags(line)==1){

        char prev_char = line[0];
        char last_char = line[line.size()-1];
        std::string newLine = line.substr(1);
        std::list<char> chars(newLine.begin(), newLine.end());
        
    
        for (char current_char: chars) {

            std::string s {prev_char,current_char};
            std::string closeTag = s+tagStruct.tagName+last_char;
            
            if(closeTag==CLOSING_TAG(tagStruct.tagName)){
                break;
            }
            else
            { 
                text= text+current_char;
                prev_char=current_char;
            }
        }
        int size = ("<"+tagStruct.tagName+">").size();
        text = text.substr(text.find_last_of(">")+1);
    }
    else
    {
        text+=line;
    }
    return text;
}

/**
 * @brief Get the Index tag name in the vector
 * @param index  index of the tag name 
 * @return int  index of tage name
 */

int tswlun002::getIndex( int index){
    if(tagStruct.tagNames.empty() || index==tagStruct.tagNames.size()){
        return 0;
    }
    else if(tagStruct.tagNames[index]==tagStruct.tagName){
        return index;
    }
    else{
       return getIndex(++index);
    }
}

/**
 * @brief  check if string line contains openning or closing tag
 * 
 * @param line is the string line we check if contain tags
 * @return true  if contains open or close  tag
 * @return false if not contains open or close  tag
 */
bool tswlun002::checkTags(std::string line){
    int value =(line.find(OPEN_TAG(tagStruct.tagName)) )!=std::string::npos;
    int value1 =(line.find(CLOSING_TAG(tagStruct.tagName)) )!=std::string::npos;

    //std::cout<<line<<", "<<value<<value1<<", "<< OPEN_TAG(tagStruct.tagName)<<std::endl;
    return (value==1 || value1==1) ? true : false;
}

/**
 * @brief removes leading and trailing  spaces in a string
 * @param parameter-line string to be trimed
 * @return trimed string 
 */
std::string tswlun002::trim(std::string line){
    line = std::regex_replace(line, std::regex("^ +"), " ");
    line = std::regex_replace(line, std::regex(" +$"), " ");
    return line;
}

/**
 * @brief Store formated tag data 
 * formart: tag name : number tag pairs : tag texts
 */
void tswlun002::storeTagData(){
    for(int i=0; i<tagStruct.tagNames.size(); i++){
        std::string data  =tagStruct.tagNames[i]+", "+std::to_string(tagStruct.numberTagPairs[i])+", "+tagStruct.tagTexts[i];
        tagStruct.tagData.push_back(data);
    }
}
/**
* @brief Write tags and its data to file 
*/
void tswlun002::writeToFile(){
    std::fstream file;
    file.open("tag.txt",std::ios::out);
    for(int i=0; i<tagStruct.tagData.size(); i++){
        file<<tagStruct.tagData[i]+"\n";
    }
    file.close();
}
    
/**
* @brief Search tag name and print tag with its data
* @param tagName  searched and print its data
*/
void tswlun002::searchTag(std::string tagName){
    for(int i=0; i<tagStruct.tagData.size(); i++){
      if(tagStruct.tagData[i].substr(0,tagStruct.tagData[i].find_first_of(','))==tagName)
      {
          std::cout<<tagStruct.tagData[i]<<std::endl;
          break;
      }  
    }  
}
      

/**
 * @brief Print tag struct in format of tag name, number tag pair, text(s) of tag
 */
void tswlun002::toString(){
    for(int i=0; i<tagStruct.tagData.size(); i++){
        std::cout<<tagStruct.tagData[i] <<std::endl;
    }
}