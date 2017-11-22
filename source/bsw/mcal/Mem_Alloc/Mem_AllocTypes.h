#ifndef _MEM_ALLOCTYPES_H_
#define _MEM_ALLOCTYPES_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

typedef uint8_t* Mem_ReturnType;
typedef uint8_t* Mem_Uint8PtrType;
typedef uint16_t Mem_SizeType;

typedef struct _MemHandlerType{
	Mem_Uint8PtrType memStart;
	Mem_Uint8PtrType memEnd;
	Mem_Uint8PtrType currAddr;
	uint16_t freeBytes;
} MemHandlerType;


#ifdef __cplusplus
 }
#endif

#endif /* #ifndef _MEM_ALLOCTYPES_H_ */