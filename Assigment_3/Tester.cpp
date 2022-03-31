#include "PGMimageProcessor.h"

using namespace tswlun002;

int main(int argc, char* argv[]){
       PGMimageProcessor object;
    for(int i=0; i<argc; i++){
        if(i==1){
         object = PGMimageProcessor(argv[i]);

        }
    }
    object.readFile();
    object.extractComponents(180,3);
    println("Done");
    return 0;
}