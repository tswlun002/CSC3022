#include "ConnectedComponent.h"
using namespace tswlun002;
 ConnectedComponent::ConnectedComponent(): numberPixels_component(0),component_identifier(0){
            pixels_coordinates.clear();
    }
    ConnectedComponent::ConnectedComponent(int numberPixels, int identifier): numberPixels_component(numberPixels),
    component_identifier(identifier){
        pixels_coordinates.clear();
    }

    ConnectedComponent::ConnectedComponent(const ConnectedComponent& other):
    numberPixels_component(other.numberPixels_component),component_identifier(other.component_identifier)
    {
        pixels_coordinates.clear();
    }
ConnectedComponent::ConnectedComponent(ConnectedComponent&& other):numberPixels_component(other.numberPixels_component),
component_identifier(other.component_identifier),pixels_coordinates(std::move(other.pixels_coordinates))
{
    other.component_identifier=0;
    other.numberPixels_component=0;

}
ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other  ){
    if(this!= &other){
        this->numberPixels_component=other.numberPixels_component;
        this->component_identifier=other.component_identifier;
        this->pixels_coordinates=other.pixels_coordinates;
    }

    return *this;
}
ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other){
    if(this != &other){
            this->numberPixels_component=other.numberPixels_component;
            this->component_identifier=other.component_identifier;
            other.component_identifier=0;
            other.numberPixels_component=0;
        if(!this->pixels_coordinates.empty()){
            this->pixels_coordinates.clear();
        }

        if(!other.pixels_coordinates.empty()){
            this->pixels_coordinates= std::move(other.pixels_coordinates);
            other.pixels_coordinates.clear();
            
        }
    }

    return *this;
}
/**
 * @brief Set the Pixel Cordinates object
 * @param y - co-ordinate
 * @param x - co-ordinate 
 */
void  ConnectedComponent::setPixelCordinates(int y, int x){
    pixels_coordinates.push_back(std::pair(x,y));
}
/**
 * @brief Get the Pixel Cordinates object
 * 
 * @return std::vector<std::pair<int, int>> 
 */
std::vector<std::pair<int, int>> ConnectedComponent::getPixelCordinates(){
    return pixels_coordinates;
}

/**
 * @brief Set the Number Pixel Component object
 * @param value - int number of pixels 
 */
void  ConnectedComponent::setNumberPixelComponent(int value){
    numberPixels_component=value;
}
/**
 * @brief Get the Number Pixel Component object
 * @return int number connent pixels for the component
 */
int  ConnectedComponent::getNumberPixelComponent(){
    return numberPixels_component;
}

/**
 * @brief Set the Component Identifier object
 * @param id - int identifier
 */
void ConnectedComponent::setComponentIdentifier(int id){
    component_identifier=id;
}
/**
 * @brief Get the Identifier object
 * @return int identifier 
 */
int ConnectedComponent::getIdentifier(){
    return component_identifier;
}