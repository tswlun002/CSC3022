/**
 * @file ConnectedComponent.h
 * @author Lunga Tsewu (tswlun002@myuct.ac.za)
 * @brief  Implementation the  ConnectedComponent .Encapsulates information about a connected component
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H
#include <vector>
#include <ostream>
namespace tswlun002{
     
     class ConnectedComponent
     {
     private:
         /* data */
         int numberPixels_component;
         int component_identifier;
         //std::vector<std::pair<int, int>> setOfNumberComponent;
         std::vector<std::pair<int,int>> pixels_coordinates;
     public:
         /**
          * @brief Default construct
          */
         ConnectedComponent(/* args */);
         /**
          * @brief Construct a new Connected Component object
          */
         ConnectedComponent(const int numberPixels, const int identifier);
         /**
          * @brief copy Construct for Connected Component object
          */
         ConnectedComponent(const ConnectedComponent& other_ConnectedComponent);
         /**
          * @brief move Construct for Connected Component object
          */
         ConnectedComponent(ConnectedComponent&& other_ConnectedComponent);
         /**
          * @brief  copy assigment  for Connected component object
          */
         ConnectedComponent& operator=(const ConnectedComponent& other_ConnectedComponent);
         /**
          * @brief move assignment for Connected component object
          */
         ConnectedComponent& operator=(ConnectedComponent&& other_ConnectedComponent);
         /**
          * @brief Set the Pixel Cordinates object
          * @param y - co-ordinate
          * @param x - co-ordinate 
          */
        void  setPixelCordinates(const std::vector<std::pair<int,int>>coOrdinate_component);
        /**
         * @brief Set the Number Component object
         * 
         * @param numberComponents is the  identifier's component  and  number of pixels 
         
        /**
         * @brief Get the Pixel Cordinates object
         * @return std::vector<std::pair<int, int>>  pixel co-ordinates
         */
         std::vector<std::pair<int,int>> getPixelCordinates()const;
         /**
          * @brief Set the Number Pixel Component object
          */
         void setNumberPixelComponent(const int value);
         /**
          * @brief Get the Number Pixel Component object
          */
         int getNumberPixelComponent()const;
         /**
          * @brief Set the Component Identifier object
          */
         void setComponentIdentifier(const int id);
         /**
          * @brief Get the Identifier object
          */
         int getIdentifier()const;
          /**
           * @brief Overload cout to print out id and number pixels of the component
           */
         friend std::ostream& operator<<(std::ostream& print , const ConnectedComponent& object){
            print<<"Component ID is: "<<object.getIdentifier()<<" number of pixels: "<<object.getNumberPixelComponent()<<std::endl;
            return print;
         }

         friend bool operator<( const ConnectedComponent& object1 , const ConnectedComponent& object2){
            
            return object1.getNumberPixelComponent()<object2.getNumberPixelComponent()? true:false ;
         }

         /**
          * @brief Destroy the Connected Component object
          */
         ~ConnectedComponent();
     };
}
#endif