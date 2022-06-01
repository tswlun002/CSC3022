#ifndef TSEWU_H
#define TSEWU_H
#include <string>
#include <iostream>

class Tsewu
{
private:
    /* data */
    std::string* name;
public:
    Tsewu(/* args */);
    Tsewu(std::string &&name);
    Tsewu(const Tsewu &tsew);
    const bool operator !=(const Tsewu& other_tsewu);
    Tsewu& operator=(const Tsewu& tsewu);
    friend std::ostream& operator<<(std::ostream &print, const Tsewu &tsewu);
    friend const bool  operator<(const Tsewu &tsewu, const Tsewu &Othe_tsewu);
    Tsewu& operator[](const int index);
    Tsewu& operator()(const int index);

    std::string getName() {
        return *name;
    }

    const Tsewu & min(const Tsewu & lhs, const Tsewu & rhs);


    ~Tsewu();
};

Tsewu::Tsewu(/* args */)
{
    this->name = new std::string;
        *(this->name)= "Wanga";
}
Tsewu::Tsewu(const Tsewu &tsewu){
    
    
    if(*this != tsewu){

        delete this->name;

        this->name = new std::string;
        *(this->name)= *(tsewu.name);
    }
   

}

Tsewu& Tsewu::operator=(const Tsewu& tsewu){

    if(*this != tsewu){
        delete this->name;
        this->name = new std::string;
        *(this->name)= *(tsewu.name);
    }

    return *this;

}
Tsewu& Tsewu::operator[](const int index){

    return *(this+index);
}
Tsewu& Tsewu::operator()(const int index){
    return *(this+index);
}

const bool Tsewu::operator!=(const Tsewu& other_tsewu){
   
    return (*(other_tsewu.name) != *(this->name) )? true : false;
}

std::ostream& operator<<( std::ostream &print, const Tsewu &tsewu){
    print<<"Tsewu "+*(tsewu.name)<<std::endl;
    return print;
}

Tsewu::Tsewu(std::string &&name):name(new std::string(name))
{
}
const Tsewu & Tsewu::min(const Tsewu & lhs, const Tsewu & rhs)
// requires can instead be here
{
    return lhs < rhs ? lhs : rhs;
}
const bool operator<(const Tsewu &tsewu, const Tsewu &Othe_tsewu)
{  
   return  ( tsewu.name->length() < Othe_tsewu.name->length() ) ?  true:  false;
}
Tsewu::~Tsewu()
{
    delete  name;
}

#endif