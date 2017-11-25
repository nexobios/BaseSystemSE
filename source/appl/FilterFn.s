.syntax unified
.thumb                   
.extern ptrScaled
.extern ptrOriginal
.extern vvmul
.global FilterFn
.type FilterFn, %function

FilterFn:

	cpsid	i			/* Disable interrupts */
  /* R0, R1, R2, R3, R12, LR, PC and xPSR are already stored into the Stack due to the Exception Frame Saving by the NVIC */
  
    push      %ptrScaled
    ldr       r4, ptrOriginal 
    ldr       r5, =vvmul
    vldr.32   s13,[r3]  /*s12 scalled, s13 original, s14 vvmul*/
    vldr.32   s14,[r4]  /*s12 scalled, s13 original, s14 vvmul*/
    vldr.32   s15,[r5]  /*s12 scalled, s13 original, s14 vvmul*/
   /* vmul.32      s13,s14,s15      */
    vstr.32   s13,[r3]         
    
   

    mrs r0, psp         /* We save the PSP address into the R0 Register */
    subs    r0, #16     /* Substract 16 bytes to the Original Address making space to 4x32bit registers  */
    stmia   r0!,{r4-r7} /* We save the R4-R7 registers in the consecutive addresses to the one in R0 */
    mov r4, r8          /* We move the R8 to R4 */
    mov r5, r9          /* We move the R9 to R5 */
    mov r6, r10         /* We move the R10 to R6 */
    mov r7, r11         /* We move the R11 to R7 */
    subs    r0, #32     /* Substract 32 bytes to the Original Address (4x32bits to R4-R7 and 4x32bits to make room to the other registers) */
    stmia   r0!,{r4-r7} /* We save the current values of R4-R7 (R8-R11) */
    subs    r0, #16     /* We substract 16 bytes to leave the R0 register in the bottom */

	/* Save current task's SP: */
/*	ldr	r2, =u32CurrentTask      */
	ldr	r1, [r2]
	str	r0, [r1]

	/* Load next task's SP: */
/*	ldr	r2, =u32NextTask     */
	ldr	r1, [r2]
	ldr	r0, [r1]

	ldmia	r0!,{r4-r7}
	mov	r8, r4
	mov	r9, r5
	mov	r10, r6
	mov	r11, r7
	ldmia	r0!,{r4-r7}
	msr	psp, r0

	ldr r0, =0xFFFFFFFD /* Thread mode with PSP: */

	cpsie	i /* Enable interrupts: */
	bx	r0

.size FilterFn, .-FilterFn