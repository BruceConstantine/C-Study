#include <cstdlib>
#include "tracer.h"
#include <iostream>
#include <cstddef>

using namespace std;

bool Tracer::Ready = false;

Tracer *tracer = new Tracer();  // cannot add into memory spy.

void* operator new(std::size_t size, const char *file, int line ) {
    void *p = malloc(size); // better than new
    tracer->addSpyObj(p, file, line);
    std::cout<< "\n'new' is overloding..\tAddress: " << p <<" called by malloc";
    return p;
}

void operator delete(void *p){
    tracer->removeSpyObj(p);
    std::cout<< "\n'delete' is overloading..\tAddress: " << p <<" Be freed.";
    free(p); // delete has 2 steps: first->call the destructor/then, delete the object of following pointer point to
}

void Tracer::addSpyObj( void *pointer , const char *file, int line){
    pointer_map_[pointer] = Enter(file, line);
}

void Tracer::removeSpyObj(void *pointer){
    std::map<void *, Enter>::iterator iter = pointer_map_.find(pointer);
    if(iter != pointer_map_.end()){
        pointer_map_.erase(iter);
    }
}

void Tracer::dump(){
    if( !pointer_map_.empty() ){ // Memory have leaked.
        cout << "\nMemory Leak." << endl;

        for(std::map<void *, Enter>::iterator iter = pointer_map_.begin();
             iter != pointer_map_.end();
             ++iter){
             cout <<" in File: "<<iter->second.File() << "\t\t" << iter->second.Line() << " Line Memory Leak" << endl;
         }

        for(std::map<void *, Enter>::iterator iter = pointer_map_.begin();
            iter != pointer_map_.end();
            ++iter){
            free(iter->first) ;
        }
    }
}

Tracer::~Tracer(){
    dump();
}
