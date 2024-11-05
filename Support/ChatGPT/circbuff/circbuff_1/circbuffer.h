/******************************************************************************
    CIRCBUFFER
Author: Sergio Santos
    <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 03112024
Comment:
    Circular Buffer Library with reliability improvements
*******************************************************************************/
#ifndef _CIRCBUFFER_H_
#define _CIRCBUFFER_H_

#include <stddef.h>  // For size_t

#define CIRC_BUFFER_SIZE 2049  // Define the buffer size (adjust as necessary)

// Circular Buffer parameters structure
struct circ_buf_par {
    char* tail;  // Pointer to the oldest byte
    char* head;  // Pointer to the next available space for writing
    char* orig;  // Pointer to the start of the buffer
    char* end;   // Pointer to the end of the buffer (one past the last valid byte)
};

// Circular buffer structure template
struct circ_buf_template {
    struct circ_buf_par par;   // Circular buffer management
    size_t mem_size;           // Maximum size of the memory area for data
    char* mem;                 // User-provided buffer for storing data
    // Function pointers for operations
    char (*flush)(struct circ_buf_template* circ);
    void (*purge)(struct circ_buf_template* circ);
    char* (*gets)(struct circ_buf_template* circ);
    char* (*pgets)(struct circ_buf_template* circ, char* Pos);
    void (*put)(struct circ_buf_template* circ, char data);
    void (*puts)(struct circ_buf_template* circ, const char* str);
};

typedef struct circ_buf_template circbuff;  // Simplified alias for circular buffer

// Function prototypes
circbuff CIRCBUFFenable(size_t mem_size, char* mem);
int CIRC_isFull(circbuff* circ);
int CIRC_isEmpty(circbuff* circ);
void CIRC_clear(circbuff* circ);

#endif  // _CIRCBUFFER_H_

/***EOF***/
