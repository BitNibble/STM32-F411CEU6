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
#include <stdio.h>
#include "circbuffer.h"

static char CIRC_buffer[CIRC_BUFFER_SIZE] = {0};  // Static buffer to hold data
const unsigned int circ_buffer_size = CIRC_BUFFER_SIZE - 1; // Buffer size excluding one position

/******************************************************************************/
// Check if the buffer is full
int CIRC_isFull(circbuff* circ) {
    // If the next position after head is the tail, the buffer is full
    return ((circ->par.head + 1 == circ->par.tail) ||
            (circ->par.head == circ->par.end && circ->par.tail == circ->par.orig));
}

/******************************************************************************/
// Check if the buffer is empty
int CIRC_isEmpty(circbuff* circ) {
    return (circ->par.head == circ->par.tail);
}

/******************************************************************************/
// Clear the buffer (reset pointers to initial state)
void CIRC_clear(circbuff* circ) {
    circ->par.head = circ->par.tail = circ->par.orig;  // Reset pointers
}

/******************************************************************************/
// Flush (remove) one byte from the buffer
char CIRC_flush(circbuff* circ) {
    // If the buffer is empty, return 0 (indicating no data)
    if (CIRC_isEmpty(circ)) {
        return 0;
    }
    
    // Retrieve byte from the tail and increment the tail pointer
    char value = *circ->par.tail;
    circ->par.tail++;
    
    // Wrap around the tail if necessary
    if (circ->par.tail == circ->par.end) {
        circ->par.tail = circ->par.orig;
    }
    
    return value;
}

/******************************************************************************/
// Purge all data from the circular buffer
void CIRC_purge(circbuff* circ) {
    while (!CIRC_isEmpty(circ)) {
        CIRC_flush(circ);  // Keep flushing until the buffer is empty
    }
}

/******************************************************************************/
// Get a string from the circular buffer (up to max buffer size or end)
char* CIRC_gets(circbuff* circ) {
    if (CIRC_isEmpty(circ)) {
        circ->mem[0] = 0;  // Return empty string if buffer is empty
        return circ->mem;
    }
    
    // Read data starting from the tail
    char* pos = circ->par.tail;
    unsigned int index = 0;
    
    // Loop until the head is reached or max memory size is exceeded
    while (pos != circ->par.head && index < circ->mem_size) {
        circ->mem[index++] = *pos;
        pos++;
        
        // Wrap around if necessary
        if (pos == circ->par.end) {
            pos = circ->par.orig;
        }
    }
    
    circ->mem[index] = 0;  // Null-terminate the string
    return circ->mem;
}

/******************************************************************************/
// Get a string from a specified position in the buffer
char* CIRC_pgets(circbuff* circ, char* pos) {
    unsigned int index = 0;
    circ->mem[circ->mem_size] = 0;  // Null-terminate the string
    
    // Loop until head is reached or max buffer size is reached
    while (pos != circ->par.head && index < circ_buffer_size) {
        circ->mem[index++] = *pos;
        pos++;
        
        // Wrap around if necessary
        if (pos == circ->par.end) {
            pos = circ->par.orig;
        }
    }
    
    circ->mem[index] = 0;  // Null-terminate the string
    return circ->mem;
}

/******************************************************************************/
// Put a byte into the circular buffer (write)
void CIRC_put(circbuff* circ, char data) {
    if (CIRC_isFull(circ)) {
        return;  // Do nothing if the buffer is full
    }
    
    // Write data to the head and move the head pointer
    *circ->par.head = data;
    
    // Increment head pointer
    circ->par.head++;
    
    // Wrap around if necessary
    if (circ->par.head == circ->par.end) {
        circ->par.head = circ->par.orig;
    }
}

/******************************************************************************/
// Put a string into the circular buffer
void CIRC_puts(circbuff* circ, const char* str) {
    while (*str) {
        CIRC_put(circ, *str++);  // Put each character into the buffer
    }
}

/******************************************************************************/
// Initialize the circular buffer with given memory and size
circbuff CIRCBUFFenable(size_t mem_size, char* mem) {
    struct circ_buf_template circ = {0};  // Zero-initialize the structure
    
    // Initialize circular buffer parameters
    circ.par.tail = circ.par.head = CIRC_buffer;  // Start head and tail at the buffer start
    circ.par.orig = CIRC_buffer;  // Original pointer to the start of the buffer
    circ.par.end = CIRC_buffer + CIRC_BUFFER_SIZE;  // Pointer to the buffer's end
    circ.mem = mem;
    circ.mem_size = (CIRC_BUFFER_SIZE < mem_size) ? (CIRC_BUFFER_SIZE - 1) : (mem_size - 1);
    
    // Assign function pointers for buffer operations
    circ.flush = CIRC_flush;
    circ.purge = CIRC_purge;
    circ.gets = CIRC_gets;
    circ.pgets = CIRC_pgets;
    circ.put = CIRC_put;
    circ.puts = CIRC_puts;
    
    return circ;  // Return the initialized circular buffer
}

/***EOF***/
