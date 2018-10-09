// https://www.cnblogs.com/largerthanlife/p/7602925.html

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<assert.h>
#include<ArrayFloat.h>

// defination of ArrayFloat
//typedef struct ArrayFloat
//{
//    float* head;        // 数组头指针
//    int size;           // 数组的大小
//    int capacity;       // 数组分配的空间
//}ArrayFloat;

// init ArrayFloat
void initial(ArrayFloat *pArray)
{  
    (*pArray).head = NULL;
    (*pArray).size = 0;
    (*pArray).capacity = 0;
}

void init(ArrayFloat *pArray, int capacity)
{  
    (*pArray).size = 0;
    (*pArray).capacity = capacity;
    float* buffer = NULL;
    buffer= (float*) realloc(buffer, sizeof(float) * capacity);
    (*pArray).head = buffer;   // 头指针指向数组的起始地址
}

ArrayFloat new(int capacity)
{  
    ArrayFloat array;
    array.size = 0;
    array.capacity = capacity;
    float* buffer = NULL;
    buffer= (float*) realloc(buffer, sizeof(float) * capacity);
    array.head = buffer;   // 头指针指向数组的起始地址
    return array;
}

// extend capacity
void recap(ArrayFloat *pArray,int capacity)
{
    int i = 0;
    (*pArray).capacity = capacity;
    (*pArray).size = (*pArray).size > capacity ? capacity : (*pArray).size;
    
    float* buffer = NULL;
    buffer= (float*) realloc(buffer, sizeof(float) * capacity); // 将buffer所指向的内存块大小修改为sizeof(float) * capacity，并将新的内存指针返回。
                                                                // 若buffer为null,相当于调用 malloc(size),若sizeof(float) * capacity为0，相当于调用free(ptr)
    for (i = 0; i < (*pArray).size; i++)
    {
        buffer[i] = (*pArray).head[i];  // 将旧值复制到新的内存空间
        // printf("value = %.6f\n",buffer[i]);
    } 
    free((*pArray).head);
    (*pArray).head = buffer;   // 头指针指向数组的起始地址
}

// get capacity
int capacity(ArrayFloat* pArray)
{
    return (*pArray).capacity; 
}

// append value to array
void append(ArrayFloat* pArray, float value)
{
    if ((*pArray).size+1 > (*pArray).capacity)
    {
        recap(pArray, (*pArray).size+1);
    }
    (*pArray).head[(*pArray).size++] = value;
    // printf("array_append size = %d, value = %0.6f\n",(*pArray).size-1,value);
}

// get array size
int size(ArrayFloat* pArray)
{
    return (*pArray).size;
}

// copy array
void copy(ArrayFloat* a, ArrayFloat* b)
{
    int i;
    recap(b, (*a).capacity);
    for (i = 0; i < (*a).size; i++)
	{
		(*b).head[i] = (*a).head[i];
	}
    (*b).size = (*a).size;
}

// insert value to array
void insert(ArrayFloat* pArray, int num, float value)
{   
    if(num == 0)
    {
        printf("num cannot equal 0 ");
        return;
    }
    if(num > (*pArray).capacity)
    {
        printf("Cannot insert, the num is larger than capacity, check out in array_insert().\n");
        exit(0);
    }
    else
    {
        int i;
        recap(pArray, (*pArray).capacity + 1);
        for (i = (*pArray).capacity - 1; i >= num; i--)
        {
            (*pArray).head[i] = (*pArray).head[i - 1];
        }
        (*pArray).head[num - 1] = value;

        (*pArray).size += 1;
    }
}

// update array, capacity and size of the array is constant
void addQue(ArrayFloat* pArray,float value)
{   
    if(0 == (*pArray).capacity)
    {
        printf("array capacity is zero!\n");
        return;
    }
    if ((*pArray).size+1 <= (*pArray).capacity)
    {
        append(pArray, value);
    }else
    {   
        int i;
        for (i = 0; i < (*pArray).capacity-1; i++)
        {
            (*pArray).head[i] = (*pArray).head[i + 1];
        }
        (*pArray).head[i] = value;
    }
}

// release memory
void destroy(ArrayFloat* pArray)
{
    free((*pArray).head);
    (*pArray).head = NULL;
    (*pArray).capacity = 0;
    (*pArray).size = 0;
}

// clear
void clear(ArrayFloat* pArray)
{   
    if((*pArray).size == 0)
    {
        return;
    }
    (*pArray).size = 0;
    int capacity = (*pArray).capacity;
    float* buffer = NULL;
    buffer = (float*) realloc(buffer, sizeof(float) * capacity);
    free((*pArray).head);
    (*pArray).head = buffer;   // 头指针指向数组的起始地址
    
}







