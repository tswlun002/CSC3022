#include "ConnectedComponent.h"
using namespace tswlun002;
ConnectedComponent::ConnectedComponent(): numberPixels_component(0),component_identifier(nullptr){
        pixels_coordinates.clear();
}
ConnectedComponent::ConnectedComponent(int numberPixels, int identifier): numberPixels_component(numberPixels),
component_identifier(new int(identifier)){
    pixels_coordinates.clear();
}

ConnectedComponent::ConnectedComponent(const ConnectedComponent& other):
numberPixels_component(other.numberPixels_component),component_identifier(nullptr)
{
    pixels_coordinates.clear();
    if(other.component_identifier!=nullptr){
        component_identifier = new int(*other.component_identifier);
    }
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
        this->pixels_coordinates=other.pixels_coordinates;
        if(this->component_identifier !=nullptr){
            delete this->component_identifier;
            this->component_identifier =nullptr;
        }
        if(other.component_identifier !=nullptr){
            this->component_identifier = new int(*other.component_identifier);
            
        }    
    }

    return *this;
}
ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other){
    if(this != &other){
        this->numberPixels_component=other.numberPixels_component;
        this->pixels_coordinates=other.pixels_coordinates;
        if(this->component_identifier !=nullptr){
            delete this->component_identifier;
            this->component_identifier =nullptr;
        }
        if(other.component_identifier !=nullptr){
            this->component_identifier = other.component_identifier;
            other.pixels_coordinates.clear();
            other.numberPixels_component=0;
            other.component_identifier=nullptr;
            
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
    pixels_coordinates.push_back(coOrdinate_component);
}
/**
 * @brief Get the Pixel Cordinates object
 * 
 * @return std::vector<std::pair<int, int>> 
 */
std::vector<std::vector<std::pair<int,int>>> ConnectedComponent::getPixelCordinates()const{
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
    component_identifier= new int(id);
}
/**
 * @brief Get the Identifier object
 * @return int identifier 
 */
int* ConnectedComponent::getIdentifier()const{
    return component_identifier;
}
/**
 * @brief Destroy the Connected Component object
 */
ConnectedComponent::~ConnectedComponent(){
    if(this->component_identifier!=nullptr)
        delete this->component_identifier;
}