#include "Template.h"
#include  "Tsewu.h"
#include <iostream>


int main(){
     


    Tsewu lu("Lu");
    Tsewu wanga;
    Tsewu Bonile("Bonile");
    Template<Tsewu, 3>template_lu(lu);
    std::cout<<template_lu;
    std::cout<<template_lu.min(lu, wanga);
    std::cout<<template_lu.min(lu, Bonile);
    
    template_lu[0]=lu;
    template_lu(1)=wanga;
    template_lu(2)=Bonile;
    Tsewu sizwe("Sizwe");
    template_lu(1,sizwe);
    std::cout<<template_lu;

    return 0;
}