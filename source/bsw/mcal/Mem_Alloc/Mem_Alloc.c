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
	/* Heap memory init */
	uint32_t *ptr_start = &_MEM_HEAP_START;
	uint32_t *ptr_end 	= &_MEM_HEAP_END;

	while(ptr_start <= ptr_end){
		*ptr_start = (uint32_t)0;
		ptr_start++;
	}

	/* Structure init */
	psMemoryHandler = (MemHandlerType *)malloc(sizeof(MemHandlerType));

	/* Data init */
	psMemoryHandler->memStart 	= (Mem_Uint8PtrType_t) 	&_MEM_HEAP_START;
	psMemoryHandler->memEnd 	= (Mem_Uint8PtrType_t) 	&_MEM_HEAP_END;
	psMemoryHandler->currAddr 	= (Mem_Uint8PtrType_t) 	&_MEM_HEAP_END;
	psMemoryHandler->freeBytes 	= HEAP_ALLOC_SIZE;

}

/*
- Mem_Alloc returns the initial address of the new allocated memory space.
- Current Address currAddr are updated according to the requested size.
- After allocating a new area, Mem_Alloc assures that the current address is aligned with 32bit address.
- The available memory in the HEAP freeBytes is updated accordingly.
- Mem_Alloc returns a NULL pointer and the requested memory allocation size exceeds the available memory in the HEAP.
*/

Mem_ReturnType_t Mem_Alloc ( Mem_SizeType_t Size ){
	/* Return value */
	Mem_ReturnType_t ptr_ret = NULL;

	/* Validate requested size */
	if( Size <= psMemoryHandler->freeBytes ){

		/* Allocate memory */
		Mem_Uint8PtrType_t tmp_ptr = psMemoryHandler->currAddr;
		tmp_ptr = (Mem_Uint8PtrType_t)malloc(Size*sizeof(uint32_t));

		/* Align size */
		Mem_SizeType_t mAdjSize = ((Size % 4) == 0) ? Size : (Size + (4 - (Size % 4)));

		/* Update MemHdlr values */
		psMemoryHandler->freeBytes -= mAdjSize;
		ptr_ret = (Mem_ReturnType_t) tmp_ptr;
		psMemoryHandler->currAddr += mAdjSize;
	}
	return ptr_ret;
}