#ifndef _MEM_ALLOC_H_
#define _MEM_ALLOC_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>
#include "Mem_AllocTypes.h"

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

extern uint32_t HEAP_ALLOC_SIZE;
extern void* _MEM_HEAP_START;
extern void* _MEM_HEAP_END;

MemHandlerType *psMemoryHandler;

void Mem_init ( void );
Mem_ReturnType_t Mem_Alloc ( Mem_SizeType_t Size );



#ifdef __cplusplus
 }
#endif

#endif /* #ifndef _MEM_ALLOC_H_ */