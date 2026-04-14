// ring.cc
//	Routines to implement a ring buffer for producer and consumer 
//      problem.
//	
// Copyright (c) 1995 The Regents of the University of Southern Queensland.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

extern "C" {
#include <stdio.h>
extern int exit(int st);
}

#include "ring.h"

//----------------------------------------------------------------------
// slot::slot
// 	The constructor for the slot class.  
//----------------------------------------------------------------------

slot::slot(int id, int number)
{
    thread_id = id;
    value = number;
}



//----------------------------------------------------------------------
// Ring::Ring
// 	The constructor for the Ring class.  Note that it doesn't have a
// 	return type.
//
// 	"sz" -- maximum number of elements in the ring buffer at any time
//----------------------------------------------------------------------

Ring::Ring(int sz)
{
    // 根据代码内容，Ring应该是一个环形队列

    // 如果缓冲区太小（小于1）会报错，并退出
    if (sz < 1) {
	fprintf(stderr, "Error: Ring: size %d too small\n", sz);
	exit(1);
    }
    // 初始化环形缓冲区
    // Initialize the data members of the ring object.
    size = sz;
    in = 0;
    out = 0;
    buffer = new slot[size]; //allocate an array of slots.
}

//----------------------------------------------------------------------
// Ring::~Ring
// 	The destructor for the Ring class.  Just get rid of the array we
// 	allocated in the constructor.
//----------------------------------------------------------------------

Ring::~Ring()
{
    // Some compilers and books tell you to write this as:
    //     delete [size] stack;
    // but apparently G++ doesn't like that.

    delete [] buffer;
}

//----------------------------------------------------------------------
// Ring::Put
// 	Put a message into the next available empty slot. We assume the
//       caller has done necesaary synchronization.
//
//	"message" -- the message to be put in the buffer
//----------------------------------------------------------------------

void
Ring::Put(slot *message)
{
    // slot：生产它的线程的id；它的值
    // 先填值再移动 in指针指的是下一个空的缓冲区 in 作为队列尾部
    buffer[in].thread_id = message->thread_id;
    buffer[in].value = message->value;
    in = (in + 1) % size;
}

//----------------------------------------------------------------------
// Ring::Get
// 	Get a message from the next full slot. We assume the
//       caller has done necesaary synchronization.
//
//	"message" -- the message from  the buffer
//----------------------------------------------------------------------

void
Ring::Get(slot *message)
{
    // out是指针，指示队列头 从队列头弹出信息
    message->thread_id = buffer[out].thread_id;
    message->value = buffer[out].value;
    out = (out + 1) % size;
}

int
Ring::Empty()
{
// to be implemented
    // 头指针和尾指针指向同一个位置时，环形队列为空
}

int
Ring::Full()
{
// to be implemented
    // 头指针指向的是一个空的位置 如果这个空的位置
    // 的下一个位置就是队列尾，队列就满了
}


