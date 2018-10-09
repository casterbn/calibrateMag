// https://www.cnblogs.com/largerthanlife/p/7602925.html
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<assert.h>

// defination of ArrayFloat
typedef struct arrFloat
{
    float* head;        // 数组头指针
    int size;           // 数组的大小
    int capacity;       // 数组分配的空间
}ArrayFloat;

// init ArrayFloat
void initial(ArrayFloat *pArray);

void init(ArrayFloat *pArray, int capacity);

ArrayFloat new(int capacity);

// extend capacity
void recap(ArrayFloat *pArray,int capacity);

// get capacity
int capacity(ArrayFloat* pArray);

// append value to array
void append(ArrayFloat* pArray, float value);

// get array size
int size(ArrayFloat* pArray);

// copy array
void copy(ArrayFloat* a, ArrayFloat* b);

// insert value to array
void insert(ArrayFloat* pArray, int num, float value);

// update array, capacity and size of the array is constant
void addQue(ArrayFloat* pArray,float value);

// release memory
void destroy(ArrayFloat* pArray);

// clear
void clear(ArrayFloat* pArray);

#endif





