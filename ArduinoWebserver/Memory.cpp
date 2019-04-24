/*
 * Memory.cpp
 *
 * Created: 22/04/2019 21:20:53
 *  Author: Marlon Abeln
 */ 
#include "Memory.h"
void* operator new(size_t objsize) 
{
	if(objsize ==0)
	objsize = 1;
	return malloc(objsize);
}
void operator delete(void *obj) 
{
	if(obj)
		free(obj);
}
void* operator new[](size_t objsize)
{
	return ::operator new(objsize);
}
void operator delete[](void *obj)
{
	if(obj)
		free(obj);
}
