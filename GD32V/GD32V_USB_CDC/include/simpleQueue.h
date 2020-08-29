#ifndef __SIMPLEQUEUE_H
#define __SIMPLEQUEUE_H

#include <stdint.h>

#define SIMPLEQUEUE8(name, type, size) struct {type buffer[size]; uint8_t wIndex; uint8_t rIndex; uint8_t sz;}name={.wIndex=0,.rIndex=0,.sz=size};
#define SIMPLEQUEUE16(name, type, size) struct {type buffer[size]; uint16_t wIndex; uint16_t rIndex; uint16_t sz = size;}name={.wIndex=0,.rIndex=0,.sz=size};

#define SIMPLEQUEUE_ISFULL(name)            (name.rIndex==(name.wIndex+1)%name.sz)
#define SIMPLEQUEUE_ISEMPTY(name)           (name.wIndex==name.rIndex)
#define SIMPLEQUEUE_ENQUEUE(name, data)     {name.buffer[name.wIndex++]=data;if(name.wIndex>=name.sz)name.wIndex=0;}
#define SIMPLEQUEUE_DEQUEUE(name)           (name.buffer[name.rIndex++]);if(name.rIndex>=name.sz)name.rIndex=0;

#endif