#ifndef _MEM_ALLOCTYPES_H_
#define _MEM_ALLOCTYPES_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>
#include "board.h"

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

typedef uint8_t* Mem_ReturnType_t;
typedef uint8_t* Mem_Uint8PtrType_t;
typedef uint32_t Mem_SizeType_t;

typedef struct _MemHandlerType{
	Mem_Uint8PtrType_t memStart;
	Mem_Uint8PtrType_t memEnd;
	Mem_Uint8PtrType_t currAddr;
	Mem_SizeType_t freeBytes;
} MemHandlerType;


#ifdef __cplusplus
 }
#endif

#endif /* #ifndef _MEM_ALLOCTYPES_H_ */