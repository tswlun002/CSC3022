/**
 * @file Tester.cpp
 * @author Lunga Tsewu (tswlun002@myuct.ac.za)
 * @brief  Test class PGMimageProcessor
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "PGMimageProcessor.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#define println(x) std::cout << x << std::endl;
using namespace tswlun002;
PGMimageProcessor object ;

/**
 * @brief print information about method extractComponents
 */
int testExtract(int threshold, int minSize,PGMimageProcessor &object){
    int number = object.extractComponents(threshold,minSize);
    println("Number components at threshold of "+std::to_string(threshold)+
    " and minimum size of "+std::to_string(minSize)+":  "+std::to_string(number));
    return number;
  

}

/**
 * @brief Test extractComponents with different threshold and minimum size
 * 
 */
 TEST_CASE("Test extractComponents"){
    int chessImageTest[13][3] ={
        {1,2,1},{1,3,1},{50,3,1},{128,400,1},{150,455,1},{180,500,6},
        {180,500,6},{200,50,6},{220,100,6},{250,3,2},{255,3,0},{255,2,0},{255,1,2}
        };
    int testImage[15][3] ={
        {1,2,1},{1,3,1},{50,3,1},{128,400,1},{150,455,1},{180,500,1},
        {190,500,3},{200,50,3},{245,100,3},{247,3,0},{250,3,0},{245,6000,3},{245,7000,2},{245,10000,1},{245,12000,0}
        };
    int test1Image[10][3] ={
        {1,2,1},{1,3,1},{150,10000,1},{200,10000,1},{215,455,3},{220,500,7},
        {245,500,5},{247,50,3},{250,3,0},{220,1000,6}
        };
   
    println("\nTest extractComponents:");
    for(int i=0; i<13; i++){
        object = std::move(PGMimageProcessor("chess.pgm"));
        object.readFile();
        REQUIRE(testExtract(chessImageTest[i][0],chessImageTest[i][1],object)==chessImageTest[i][2]);

    }
    for(int i=0; i<15; i++){
        object = std::move(PGMimageProcessor("test.pgm"));
        object.readFile();
        REQUIRE(testExtract(testImage[i][0],testImage[i][1],object)==testImage[i][2]);

    }
    for(int i=0; i<10; i++){
        object = std::move(PGMimageProcessor("test1.pgm"));
        object.readFile();
        REQUIRE(testExtract(test1Image[i][0],test1Image[i][1],object)==test1Image[i][2]);
        object.writeComponents("Noways");

    }
        
}

/**
 * @brief print information about method filterComponentsBySize
 */
int testFilterBySize(int min, int maxSize,PGMimageProcessor &object){
    
    int number = object.filterComponentsBySize(min,maxSize);
    println("Number components at minimum size of "+std::to_string(min)+
    " and maxmum size of "+std::to_string(maxSize)+":  "+std::to_string(number));
    return number;
}
/**
 * @brief Test filterComponentsBySize with different threshold and minimum size
 * 
 */
 TEST_CASE("Test filterComponentsBySize"){
    println("\nTest filterComponentsBySize:")

    int testList[15][3] ={
        {3,1,0},{100,300,0},{300,4900,1},{4000,5800,2},{4000,6500,2},
        {4000,6900,3},{4000,7200,4},{4000,7700,5},{4000,8000,5},
        {4000,8500,6},{5000,8500,5},{6000,8500,4},{6700,8500,3},{7800,8500,1},{8100,8500,0}
    };
    int testImage[12][3] ={
        {1,2,0},{100,500,0},{1000,5000,0},{5000,6500,1},{6000,7000,1},
        {6000,7800,2},{6000,10000,2},{6000,11000,2},{6000,11600,3},{6500,11600,2},{7800,11600,1},{11600,20000,0}
        };
    int test1Image[8][3] ={
        {1,2,0},{5000,10000,0},{10000,11100,1},{10000,18000,2},{10000,50000,3},{11100,50000,2},
        {18000,50000,1},{50000,100000,0}
        };
    for(int i=0; i<15; i++){
        object = std::move(PGMimageProcessor("chess.pgm"));
        object.readFile();
        object.extractComponents(180,500);
        REQUIRE(testFilterBySize(testList[i][0],testList[i][1],object)==testList[i][2]);
    }
     for(int i=0; i<12; i++){
         
        object = std::move(PGMimageProcessor("test.pgm"));
        object.readFile();
        object.extractComponents(245,500);
        REQUIRE(testFilterBySize(testImage[i][0],testImage[i][1],object)==testImage[i][2]);

    }
    for(int i=0; i<8; i++){
        object = std::move(PGMimageProcessor("test1.pgm"));
        object.readFile();
        object.extractComponents(215,500);
        REQUIRE(testFilterBySize(test1Image[i][0],test1Image[i][1],object)==test1Image[i][2]);
        //object.writeComponents("Noways");

    }
    
}
/**
 * @brief  Display true if success full write file else false
 */
bool writeFile(const std::string& name, PGMimageProcessor & object){
   
    
    bool value = object.writeComponents(name);
    std::string ans = (value>0? "true":"false");
    println("Filename is successful created ? : "+ans);
    return value;
}
/**
 * @brief  test writeComponent
* extractTestList[i][0] is minimum size of component
 * extractTestList[i][1] is maximum size of component
 * extractTestList[i][2] is expected output
 * All outputfile are named by range size of components like minSize-maxSize.pgm
 */
TEST_CASE("test writeComponent"){
     int extractTestList[15][3] ={
        {3,1,0},{100,300,0},{300,4900,1},{4000,5800,2},{4000,6500,2},
        {4000,6900,3},{4000,7200,4},{4000,7700,5},{4000,8000,5},{4000,8500,6},{5000,8500,5},
        {6000,8500,4},{6700,8500,2},{7800,8500,1},{8100,8500,0}
    };
     int testImage[12][3] ={
        {1,2,0},{100,500,0},{1000,5000,0},{5000,6500,1},{6000,7000,1},
        {6000,7800,2},{6000,10000,2},{6000,11000,2},{6000,11600,3},{6500,11600,2},{7800,11600,1},{11600,20000,0}
        };
    int test1Image[8][3] ={
        {1,2,0},{5000,10000,0},{10000,11100,1},{10000,18000,2},{10000,50000,3},{11100,50000,2},
        {18000,50000,1},{50000,100000,0}
        };
    for(int i=0; i<16; i++){
        object = std::move(PGMimageProcessor("chess.pgm"));
        object.readFile();
        object.extractComponents(180,500);
        object.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(object.writeComponents("chess-"+std::to_string(extractTestList[i][0])+"-"+std::to_string(extractTestList[i][1]))==true);
    }

    for(int i=0; i<12; i++){
         
        object = std::move(PGMimageProcessor("test.pgm"));
        object.readFile();
        object.extractComponents(245,500);
        object.filterComponentsBySize(testImage[i][0],testImage[i][1]);
        REQUIRE(object.writeComponents("test-"+std::to_string(testImage[i][0])+"-"+std::to_string(testImage[i][1]))==true);


    }
    for(int i=0; i<8; i++){
        object = std::move(PGMimageProcessor("test1.pgm"));
        object.readFile();
        object.extractComponents(215,500);
        object.filterComponentsBySize(test1Image[i][0],test1Image[i][1]);
        REQUIRE(object.writeComponents("test1-"+std::to_string(test1Image[i][0])+"-"+std::to_string(test1Image[i][1]))==true);
    }
   
   

}
/**
 * @brief helper method for testGetComponentCount
 */
int testGetComponentCount(PGMimageProcessor &object){
    int value = object.getComponentCount();
    println("Final components count =" +std::to_string(value));
    return value;
}

/**
 * @brief test getComponentCount
 * extractTestList[i][0] is minimum size of component
 * extractTestList[i][1] is maximum size of component
 * extractTestList[i][2] is expected output
 */
TEST_CASE(" test getComponentCount"){
    println("\nTest getComponentCount:");

    int extractTestList[16][3] ={
        {3,1,0},{100,300,0},{300,4900,1},{4000,5800,2},{4000,6500,2},
        {4000,6900,3},{4000,7200,4},{4000,7700,5},{4000,8000,5},{4000,8500,6},{5000,8500,5},
        {6000,8500,4},{6700,8500,3},{7800,8500,1},{8100,8500,0}
    };
 
    for(int i=0; i<16; i++){
        object = std::move(PGMimageProcessor("chess.pgm"));
        object.readFile();
        object.extractComponents(180,500);
        object.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(testGetComponentCount(object)==extractTestList[i][2]);
    }
   
}
int testgetLargestSize(PGMimageProcessor &object){
    int value = object.getLargestSize();
    println("Large components size = " +std::to_string(value));
    return value;
}
/**
 * @brief test getComponentCount
 * extractTestList[i][0] is minimum size of component
 * extractTestList[i][1] is maximum size of component
 * extractTestList[i][2] is expected output
 */
TEST_CASE(" test getLargestSize"){
    println("\nTest getLargestSize:");
    int extractTestList[16][3] ={
        {3,1,0},{100,300,0},{300,4900,5000},{4000,5800,5800},{4000,6500,6500},
        {4000,6900,6800},{4000,7200,7190},{4000,7700,7690},{4000,8000,7999},{4000,8500,8100},{5000,8500,8100},
        {6000,8500,8100},{6700,8500,8100},{7800,8500,8050},{8100,8500,0}
    };
 
    for(int i=0; i<16; i++){
        object = std::move(PGMimageProcessor("chess.pgm"));
        object.readFile();
        object.extractComponents(180,500);
        object.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(testgetLargestSize(object)<= extractTestList[i][2]);
    }
   
}
/**
 * @brief get small size component 
 */
int testgetSmallestSize(PGMimageProcessor &object){
    int value = object.getSmallestSize();
    println("Small components size = " +std::to_string(value));
    return value;
}
/**
 * @brief test getSmallestSize
 * extractTestList[i][0] is minimum size of component
 * extractTestList[i][1] is maximum size of component
 * extractTestList[i][2] is expected output
 */
TEST_CASE("Test getSmallestSize"){
    println("\nTest getSmallestSize:");
      
     int extractTestList[16][3] ={
        {3,1,0},{100,300,0},{300,4900,4300},{4000,5800,4300},{4000,6500,4300},
        {4000,6900,4300},{4000,7200,4300},{4000,7700,4300},{4000,8000,4300},{4000,8500,4300},{5000,8500,5730},
        {6000,8500,6500},{6700,8500,7100},{7800,8500,7600},{8100,8500,0}
    };
 
    for(int i=0; i<16; i++){
        object = std::move(PGMimageProcessor("chess.pgm"));
        object.readFile();
        object.extractComponents(180,500);
    
        object.filterComponentsBySize(extractTestList[i][0],extractTestList[i][1]);
        REQUIRE(testgetSmallestSize(object)>= extractTestList[i][2]);
    }
}
/**
 * @brief Just print out data, we will test using identifier of 3 but with no data
 * 
 */
TEST_CASE("test printComponentData"){
    println("\nTest printComponentData  :");
    ConnectedComponent  connectedComponent;
    connectedComponent.setComponentIdentifier(3);
    object.printComponentData(connectedComponent);
}