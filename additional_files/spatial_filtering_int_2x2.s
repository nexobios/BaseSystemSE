;******************************************************************************************************************
; File:         spatial_filtering_int_2x2.s
; Brief:        Spatial filtering based on convolution optimized for SPE (Signal Processing Engine)
;               of MPC55xx family of microcontrollers
;
; Parameters:   UINT8   *pu8Image       -> pointer to input image (UINT8 elements)
;               UINT16  u16rows         -> number of Image rows (even number)
;               UINT16  u16cols         -> number of Image columns (even number)
;               Float   *pfMask         -> pointer to convolution mask (single precision floating point elements)
;               UINT8   *pu8ConvImage   -> pointer to convoulution output image (UINT8 elements)
;
; History:      Ver.    Date               Comments
;               0.1     April 24th,2008  -> Initial Release (Tezmol Otero Abraham)
;
;******************************************************************************************************************

.globl spatial_filt_int_2x2

.text

;---------------------------------------------------------------------------------------
spatial_filt_int_2x2:

    stwu      1 ,   -152(1)         ; Save stack
    evstdd    31    , 144(1)        ; Save non-volatile registers
    evstdd    30    , 136(1)
    evstdd    29    , 128(1)
    evstdd    28    , 120(1)
    evstdd    27    , 112(1)
    evstdd    26    , 104(1)
    evstdd    25    , 96(1)
    evstdd    24    , 88(1)
    evstdd    23    , 80(1)
    evstdd    22    , 72(1)
    evstdd    21    , 64(1)
    evstdd    20    , 56(1)
    evstdd    19    , 48(1)
    evstdd    18    , 40(1)
    evstdd    17    , 32(1)
    evstdd    16    , 24(1)
    evstdd    15    , 16(1)
    evstdd    14    , 8(1)
    ;----------------------------- Input parameters definition ---------------------------
    .set Image          , 3
    .set rows           , 4
    .set cols           , 5
    .set Mask           , 6
    .set filt_image     , 7
    ;----------------------------- Working registers definition --------------------------
    .set Pixel_0        , 8
    .set Pixel_1        , 9
    .set Mask_0         , 15
    .set Mask_1         , 16
    .set accum_0        , 21
    .set accum_1        , 22
    .set a_offset       , 24
    .set b_offset       , 25
    .set row_index      , 26
    .set col_index      , 27
    .set float_scl      , 28

    ;----------------------------- Initialization -------------------------------------
    lis		float_scl,1             ; load float_scl = 2^16
    subi        row_index,rows,0        ; index = # of image rows - mask rows + 1
    subi        col_index,cols,0        ; index = # of image cols - mask cols
    mtspr       9,row_index             ; load Count Register SPR9 = # of rows
    evmergelo   float_scl,float_scl,float_scl;
    evfscfsi    float_scl,float_scl     ; convert from signed integer to float and store in lsb portion

    li          a_offset,0              ; initialize mask indexes
    evldwx      Mask_0,Mask,a_offset    ; Mask = Mask[0][0] | Mask[0][1]
    addi        a_offset,a_offset,8     ; update mask indexes
    evlddx      Mask_1,Mask,a_offset    ; Mask = Mask[1][0] | Mask[1][1]
    evfsmul     Mask_0,Mask_0,float_scl ; Scale-up mask (in floating-point representation)
    li          a_offset,0              ; initialize source index
    evfsmul     Mask_1,Mask_1,float_scl ;
    addi        b_offset,a_offset,0         ; initialize destination index
    evfsctsi    Mask_0,Mask_0           ; Convert mask to integer representation once it has been scaled-up
    evfsctsi    Mask_1,Mask_1           ;

    mftbl       r31                     ; moves TBL and TBU values to SPRG5
    mtsprg5     r31                     ; code required to measure performance

    ;------------------------- Convolution operation ----------------------------------------
    Main_Loop:
    li          Pixel_0,0               ; Load zeros to Pixel_0 and Pixel_1
    evmergelo   Pixel_0,Pixel_0,Pixel_0 ;
    evmr        Pixel_1,Pixel_0         ;
    mfspr       row_index,9             ; Backup current value of row index
    mtspr       9,col_index             ; load Count Register SPR9 = # of cols
    ;~~~~~~~~~~~~~~~~~~~~~~~~~~ Convolution core ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Sub_Loop:
    lbz         Pixel_0,0(Image)  	; Load new pixel
    lbzx        Pixel_1,Image,cols  	; Load new pixel
    addi	Image, Image, 1
    evmwlumia   accum_0,Pixel_0,Mask_0  ;
    evmwlssiaaw accum_1,Pixel_1,Mask_1  ;
    evmergelo   Pixel_0,Pixel_0,Pixel_0 ; Pixel_n = Image[i+0][j+1] | Image[i+0][j+1]
    evmergelo   Pixel_1,Pixel_1,Pixel_1 ; Pixel_n = Image[i+1][j+1] | Image[i+1][j+1]
    evmergelohi accum_0,accum_1,accum_1 ;
    evaddw      accum_0,accum_0,accum_1 ;
    evsrwiu     accum_0,accum_0,16      ; scale-down final result
    stbx        accum_0,filt_image,b_offset; store resulting pixel
    addi        b_offset,b_offset,1     ; point to next location in output image
    bdnz        Sub_Loop
    ;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    mtspr       9,row_index             ; restore current value of row index
    bdnz        Main_Loop
    ;---------------------------------------------------------------------------------------
    mftbl    r31                        ; moves TBL and TBU values to SPRG6
    mtsprg6  r31                        ; code required to measure performance

    evldd    31 , 144(1)                ; Restore non-volatile registers
    evldd    30 , 136(1)
    evldd    29 , 128(1)
    evldd    28 , 120(1)
    evldd    27 , 112(1)
    evldd    26 , 104(1)
    evldd    25 , 96(1)
    evldd    24 , 88(1)
    evldd    23 , 80(1)
    evldd    22 , 72(1)
    evldd    21 , 64(1)
    evldd    20 , 56(1)
    evldd    19 , 48(1)
    evldd    18 , 40(1)
    evldd    17 , 32(1)
    evldd    16 , 24(1)
    evldd    15 , 16(1)
    evldd    14 , 8(1)
    addi     1  , 1,152         ; Restore stack
    blr
;=========================================================================================
