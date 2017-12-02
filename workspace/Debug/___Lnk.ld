/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2014, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

INPUT (C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\dbg_console.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\board_lowlevel.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\board_memories.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\exceptions.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\pio.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\mpu.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\pmc.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\uart.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\wdt.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\pio_it.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\supc.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\tc.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\xdma_hardware_interface.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\xdmac.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\xdmad.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\afec.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\afe_dma.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\pwmc.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\ecg_data.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\source\libraries\libm.a 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_bitreversal.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_bitreversal2.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_cfft_f32.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_cfft_radix8_f32.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_cmplx_mag_f32.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_common_tables.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_const_structs.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_fft_bin_data.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_max_f32.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\arm_rfft_fast_f32.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\fft_float.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\source\libraries\libarm_cortexM7lfdp_math.a 
C:\Users\DIMMU\Documents\BaseSystemSE_2\source\libraries\libarm_cortexM7lfsp_math.a 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\fpu.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\syscalls.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\system_sam.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\timetick.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\app_scheduler.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\Tasks.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\led.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\main.o 
C:\Users\DIMMU\Documents\BaseSystemSE_2\workspace\Debug\startup_sam.o)

/*------------------------------------------------------------------------------
 *      Linker script for running in internal FLASH on the ATSAMV71Q21
 *----------------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SEARCH_DIR(.)

/* Memory Spaces Definitions */
MEMORY
{
  rom (rx)  :      ORIGIN = 0x00400000, LENGTH = 0x00200000
  ram (rwx) :      ORIGIN = 0x20400000, LENGTH = 0x00050000
  ram_heap (rwx) : ORIGIN = 0x20450000, LENGTH = 0x00010000
  sdram(rwx): ORIGIN = 0x70000000, LENGTH = 0x00200000
}

/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x2000;

/* The heapsize used by the application. NOTE: you need to adjust according to your application. */
HEAP_SIZE = DEFINED(HEAP_SIZE) ? HEAP_SIZE : 0x1000;

MY_HEAP_SIZE = DEFINED(MY_HEAP_SIZE) ? MY_HEAP_SIZE : 0x10000;

INCLUDE ..\source\infrastructure\toolset\gcc\sam_flash.ld
INCLUDE ..\source\infrastructure\toolset\gcc\sam_sdram.ld
