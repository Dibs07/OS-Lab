// Write a c program to implement to Reader-writer problem. (Using semaphore)
#include <stdio.h>

int mutex=1,write=1,readcount=0;