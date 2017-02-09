#ifndef REDEFINENEWKEYWORD_H
#define REDEFINENEWKEYWORD_H
#include "tracer.h"

#ifdef new
#undef new
#endif

extern void * operator new(std::size_t size, const char *file, int line ) ;
extern void operator delete(void *p);
extern void * operator new(std::size_t size, void *p);

#ifndef new
#define new new(__FILE__, __LINE__)
#endif

#endif // REDEFINENEWKEYWORD_H

