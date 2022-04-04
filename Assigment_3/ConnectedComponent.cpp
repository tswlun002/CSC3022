/**
 * @file ConnectedComponent.cpp
 * @author Lunga Tsewu (tswlun002@myuct.ac.za)
 * @brief  Header the  ConnectedComponent .Encapsulates information about a connected component
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ConnectedComponent.h"
using namespace tswlun002;
/**
 * @brief Construct a new Connected Component:: Connected Component object
 */
ConnectedComponent::ConnectedComponent(): numberPixels_component(0),component_identifier(0){
        pixels_coordinates.clear();
}
/**
 * @brief Construct a new Connected Component:: Connected Component object
 */
ConnectedComponent::ConnectedComponent(int numberPixels, int identifier): numberPixels_component(numberPixels),
component_identifier(identifier){
    pixels_coordinates.clear();
}
/**
 * @brief copy Connected Component object
 */
ConnectedComponent::ConnectedComponent(const ConnectedComponent& other):
numberPixels_component(other.numberPixels_component),component_identifier(0)
{
    pixels_coordinates.clear();
    if(other.component_identifier!=0){
        component_identifier = other.component_identifier;
    }
}
/**
 * @brief move constructf for Connected Component object
 */
ConnectedComponent::ConnectedComponent(ConnectedComponent&& other):numberPixels_component(other.numberPixels_component),
component_identifier(other.component_identifier),pixels_coordinates(std::move(other.pixels_coordinates))
{
    other.component_identifier=0;
    other.numberPixels_component=0;

}
/**
 * @brief Copy assignemt 
 * i used not equals to zero because in  my code i  made identifier start at one instead of zero
 * If identifier is zero , then there  is no component
 * @param other  other object we want to assign from
 * @return ConnectedComponent& 
 */
ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other  ){
    if(this!= &other){
        this->numberPixels_component=other.numberPixels_component;
        this->pixels_coordinates=other.pixels_coordinates;
        if(this->component_identifier !=0){
            this->component_identifier =0;
        }
        if(other.component_identifier !=0){
            this->component_identifier = other.component_identifier;
            
        }    
    }

    return *this;
}
/**
 * @brief Move assignement 
 * @param other  other object we want to move from
 * @return ConnectedComponent& 
 */
ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other){
    if(this != &other){
        this->numberPixels_component=other.numberPixels_component;
        this->pixels_coordinates=other.pixels_coordinates;
        if(this->component_identifier !=0){
            this->component_identifier =0;
        }
        if(other.component_identifier !=0){
            this->component_identifier = other.component_identifier;
            other.pixels_coordinates.clear();
            other.numberPixels_component=0;
            other.component_identifier=0;
            
        }
    }

    return *this;
}
/**
 * @brief Set the Pixel Cordinates object
 * @param y - co-ordinate
 * @param x - co-ordinate 
 */
void  ConnectedComponent::setPixelCordinates(const std::vector<std::pair<int,int>>coOrdinate_component){
    pixels_coordinates = std::move(coOrdinate_component);
}
/**
 * @brief Get the Pixel Cordinates object
 * 
 * @return std::vector<std::pair<int, int>> 
 */
std::vector<std::pair<int,int>> ConnectedComponent::getPixelCordinates()const{
    return pixels_coordinates;
}

/**
 * @brief Set the Number Pixel Component object
 * @param value - int number of pixels 
 */
void  ConnectedComponent::setNumberPixelComponent(const int value){
    numberPixels_component=value;
}
/**
 * @brief Get the Number Pixel Component object
 * @return int number connent pixels for the component
 */
int  ConnectedComponent::getNumberPixelComponent()const{
    return numberPixels_component;
}

/**
 * @brief Set the Component Identifier object
 * @param id - int identifier
 */
void ConnectedComponent::setComponentIdentifier(const int id){
    component_identifier= id;
}
/**
 * @brief Get the Identifier object
 * @return int identifier 
 */
int ConnectedComponent::getIdentifier()const{
    return component_identifier;
}
/**
 * @brief Overload cout 
 
void ConnectedComponent::operator<<(std::ostream& print){
}*/
/**
 * @brief Destroy the Connected Component object
 */
ConnectedComponent::~ConnectedComponent(){
 
}