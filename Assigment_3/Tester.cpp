#include "PGMimageProcessor.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#define println(x) std::cout << x << std::endl;
using namespace tswlun002;
 PGMimageProcessor object = PGMimageProcessor("chess.pgm");

/**
 * @brief print information about method extractComponents
 */
int testExtract(int threshold, int minSize,PGMimageProcessor &object){
    int number = object.extractComponents(threshold,minSize);
    
    println("Number components at threshold of "+std::to_string(threshold)+
    " and minimum size of "+std::to_string(minSize)+":  "+std::to_string(number));

   // println("After filter = "+std::to_string(object.filterComponentsBySize(3,608*502)));
    return number;
  

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
 * @brief  Display true if success full write file else false
 */
bool writeFile(const std::string& name, PGMimageProcessor & object){
    bool value = object.writeComponents(name);
    std::string ans = (value>0? "true":"false");
    println("Filename is successful created ? : "+ans);
    return value;
}
/**
 * @brief Test extractComponents with different threshold and minimum size
 * 
 */
 TEST_CASE("Test extractComponents"){
    object.readFile();
    println("\nTest extractComponents:");
    /*REQUIRE(testExtract(1,3,object)==1);
    REQUIRE(testExtract(50,3,object)==1);
    REQUIRE(testExtract(128,400,object)==1);
    REQUIRE(testExtract(150,455,object)==1);
    REQUIRE(testExtract(180,500,object)==6);
    REQUIRE(testExtract(200,50,object)==6);*/
    REQUIRE(testExtract(220,100,object)==6);
    //REQUIRE(testExtract(250,3,object)==2);
    //REQUIRE(testExtract(255,3,object)==0);
        
}
/**
 * @brief Test filterComponentsBySize with different threshold and minimum size
 * 
 */
 TEST_CASE("Test filterComponentsBySize"){
    println("\nTest filterComponentsBySize:")
    //REQUIRE(testExtract(220,100,object)==6);
    //REQUIRE(testFilterBySize(3,1,object)==0);
    REQUIRE(testFilterBySize(100,6500,object)==3);
    /**REQUIRE(testFilterBySize(50,608*502,object)==0);
    REQUIRE(testFilterBySize(100,608*502,object)==6);
    REQUIRE(testFilterBySize(180,2000,object)==5);
    REQUIRE(testFilterBySize(200,2000,object)==5);
    REQUIRE(testFilterBySize(200,700,object)==4);
    REQUIRE(testFilterBySize(200,600,object)==3);
    REQUIRE(testFilterBySize(200,500,object)==1);*/
        
}
/**
 * @brief Test write to file
 */
TEST_CASE("Test writeComponent"){
    println("\nTest WriteComponent:");
    REQUIRE(writeFile("NN",object)==1);
}
int testGetComponentCount(PGMimageProcessor &object){
    int value = object.getComponentCount();
    println("Final components count =" +std::to_string(value));
    return value;
}

/**
 * @brief test getComponentCount
 * 
 */
TEST_CASE(" test getComponentCount"){
    println("\nTest getComponentCount:");
    REQUIRE(testGetComponentCount(object)==3);
}
int testgetLargestSize(PGMimageProcessor &object){
    int value = object.getLargestSize();
    println("Large components size = " +std::to_string(value));
    return value;
}
/**
 * @brief test getComponentCount
 * 
 */
TEST_CASE(" test getLargestSize"){
    println("\nTest getLargestSize:");
    REQUIRE(testgetLargestSize(object)< 6500);
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
 * 
 */
TEST_CASE("Test getSmallestSize"){
    println("\nTest getSmallestSize:");
    REQUIRE(testgetSmallestSize(object)< 5000);
}

TEST_CASE("test printComponentData"){
    println("\nTest printComponentData  :");
    ConnectedComponent  connectedComponent;
    connectedComponent.setComponentIdentifier(3);
    object.printComponentData(connectedComponent);
}