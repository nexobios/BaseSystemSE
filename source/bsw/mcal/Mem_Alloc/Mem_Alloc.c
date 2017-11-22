/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "Mem_AllocTypes.h"
#include "Mem_Alloc.h"

/* 
This function initializes the HEAP content to zero.
Memory start address memStart, memory end address memEnd, memory current address currAddr and
available memory bytes indicator freeBytes are also initialized.
 */
void Mem_init(){

}

/*
- Mem_Alloc returns the initial address of the new allocated memory space.
- Current Address currAddr are updated according to the requested size.
- After allocating a new area, Mem_Alloc assures that the current address is aligned with 32bit address.
- The available memory in the HEAP freeBytes is updated accordingly.
- Mem_Alloc returns a NULL pointer and the requested memory allocation size exceeds the available memory in the HEAP.
*/

Mem_ReturnType Mem_Alloc ( Mem_SizeType Size ){


}