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

void Mem_init ( void );
Mem_ReturnType Mem_Alloc ( Mem_SizeType Size );



#ifdef __cplusplus
 }
#endif

#endif /* #ifndef _MEM_ALLOC_H_ */