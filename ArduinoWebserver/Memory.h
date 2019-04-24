/*
 * Memory.h
 *
 * Created: 21/04/2019 13:29:53
 *  Author: Marlon Abeln
 */ 


#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdlib.h>
void* operator new(size_t objsize);
void operator delete(void* obj);
void* operator new[](size_t objsize);
void operator delete[](void * obj);

#endif /* MEMORY_H_ */