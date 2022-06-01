#ifndef CONCEPT_H
#define CONCEPT_H
#include <string>
#include <iostream>

namespace my_concepts{
    /**
     * @brief Concepts check whether interface(printable or sortable, comparable etc) of typename or class T is provided 
     * Syntax 
     * template< template parameter list>
     * concept concept_name -  constrain-expression;
     * requires   - allow userm to define their own contrain
     */
    template<typename T> 
    concept Printable = requires(std::ostream& print, const T & object){
        {print<<object};
    };
    template<typename T> 
    concept Equals_or_NotEquals = requires( const T & object_a, const T & object_b){
        {object_a==object_b || object_a!=object_b};
    };
    template<typename T> 
    concept LessThanComparable = requires( const T & object_a, const T & object_b){
        {object_a<object_b};
    };
    template<typename T> 
    concept greaterThanComparable = requires( const T & object_a, const T & object_b){
        {object_a>object_b};
    };

    template<typename T> 
    concept Square_Mutable = requires(T & object_a, int index){
        {object_a[index]=object_a };
    };
    template<typename T> 
    concept Round_Mutable = requires(T & object_a, int index){
        {object_a(index)=object_a };
    };
    template<typename T> 
    concept Insert_Mutable = requires(T & object_a, int index){
        {Round_Mutable<T> && Square_Mutable<T>};
    };

};


using namespace my_concepts;

template<typename T, int size>
class Template
{
private:
    /* data */
    T* elements;
    
    
public:
    Template(/* args */);
    Template(T & elements);
    Template(Template<T,size>& object)requires Equals_or_NotEquals<T>;
    T& operator=(Template<T,size> & object)requires Equals_or_NotEquals<T>;
    T& operator[](const int index) requires Square_Mutable<T>;
    T& operator()(const int index)requires Round_Mutable<T>  ;
    const bool operator!=(Template<T,size> & object)requires Equals_or_NotEquals<T>;
    void operator()(const int index, const T& element) requires Insert_Mutable<T> ;
    T* getElements();

    const T & min(const T & lhs, const T & rhs)requires LessThanComparable<T>;

    template<typename T_, int size_>
    friend std::ostream& operator<<(std::ostream & print,  Template<T_,size_> & object) requires Printable<T_>;
    ~Template();
};
template<typename T, int size>
Template<T, size>::Template(/* args */):elements(new T[size])
{
}

template <typename T, int size> 
const T & Template < T, size>::min(const T & lhs, const T & rhs)
requires LessThanComparable<T>
{
    return lhs < rhs ? lhs : rhs;
}

template<typename T, int size> 
Template<T, size>::Template(T & element){
    elements =new T[size];
    elements[0]= element;
}
template<typename T, int size>

Template<T, size>::Template(Template<T,size>& object)requires Equals_or_NotEquals<T>:elements(new T[size]){
    if(*this != object){
        if(*this->elements != nullptr)
            delete [] elements ;

        for(int i=0; i<size; i++){
            elements[i] = new T(object.elements[i]);
        }
    }
        
    
}
template<typename T, int size>
T& Template<T, size>::operator=(Template<T,size> & object)requires Equals_or_NotEquals<T>{
    
     if(*this == object)
        return this;
    delete [] elements ;
    for(int i=0; i<size; i++){
        elements[i] = new T(object.elements[i]);
    }

}

template<typename T, int size>
const bool Template< T,  size>::operator!=(Template<T,size> & object)requires Equals_or_NotEquals<T>{
   return (*this != object)? true:false;
}

template<typename T, int size>
T& Template<T, size>::operator[](const int index) requires Square_Mutable<T>{

    return elements[index];
}
template<typename T, int size>
T& Template<T, size>::operator()(const int index) requires Round_Mutable<T> {
    return elements[index];
}
template<typename T, int size>
void Template<T, size>::operator()(const int index, const T& element) requires Insert_Mutable<T>{
     elements[index] = element;
}

template<typename T, int size>
T* Template<T,size>::getElements() {
    return elements;
}
template<typename T, int size> 
std::ostream& operator<<(std::ostream & print,  Template<T,size> & object)
requires Printable<T>
{
    
     for(int i=0; i<size; i++){
        print<<object.getElements()[i];
    }
    return print;
}

template<typename T, int size>
Template<T, size>::~Template()
{
    delete [] elements;
}

#endif 