;/*
; * File      : start_rvds.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2012, RT-Thread Development Team
; *
; * The license and distribution terms for this file may be
; * found in the file LICENSE in this distribution or at
; * http://www.rt-thread.org/license/LICENSE
; *
; * Change Logs:
; * Date           Author       Notes
; * 2011-09-16     Bernard      first version
; * 2012-05-06     Bernard      fixed the issue caused by incorrectly set CPSR;
; */

; TI AM1808 startup file for ARMCC
; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled

;----------------------- Stack and Heap Definitions ----------------------------

UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000100
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000100
USR_Stack_Size  EQU     0x00000100

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 FIQ_Stack_Size + IRQ_Stack_Size)

        AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top


Heap_Size       EQU     0x00000000

        AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

;----------------------- CODE --------------------------------------------------

        PRESERVE8

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

        AREA    RESET, CODE, READONLY
        ARM

; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

        EXPORT Entry_Point
Entry_Point
Vectors
        LDR     PC, Reset_Addr
        LDR     PC, Undef_Addr
        LDR     PC, SWI_Addr
        LDR     PC, PAbt_Addr
        LDR     PC, DAbt_Addr
        NOP
        LDR     PC, IRQ_Addr
        LDR     PC, FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                   ; Reserved Address
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

;Undef_Handler   B       Undef_Handler
SWI_Handler     B       SWI_Handler
;PAbt_Handler    B       PAbt_Handler
;DAbt_Handler    B       DAbt_Handler
FIQ_Handler     B       FIQ_Handler

;*
;*************************************************************************
;*
;* Interrupt handling
;*
;*************************************************************************
;*
                IMPORT rt_hw_trap_udef
Undef_Handler
        SUB     SP, SP, #72
        STMIA   SP, {R0 - R12}          ;/* Calling r0-r12                  */
        ADD     R8, SP, #60
        STMDB   R8, {SP, LR}            ;/* Calling SP, LR                  */
        STR     LR, [R8, #0]            ;/* Save calling PC                 */
        MRS     R6, SPSR
        STR     R6, [R8, #4]            ;/* Save CPSR                       */
        STR     R0, [R8, #8]            ;/* Save OLD_R0                     */
        MOV     R0, SP

        BL      rt_hw_trap_udef
                
                IMPORT rt_hw_trap_pabt
PAbt_Handler
        SUB     SP, SP, #72
        STMIA   SP, {R0 - R12}          ;/* Calling r0-r12                  */
        ADD     R8, SP, #60
        STMDB   R8, {SP, LR}            ;/* Calling SP, LR                  */
        STR     LR, [R8, #0]            ;/* Save calling PC                 */
        MRS     R6, SPSR
        STR     R6, [R8, #4]            ;/* Save CPSR                       */
        STR     R0, [R8, #8]            ;/* Save OLD_R0                     */
        MOV     R0, SP

        BL      rt_hw_trap_pabt
        
                IMPORT rt_hw_trap_dabt
DAbt_Handler
        SUB     SP, SP, #72
        STMIA   SP, {R0 - R12}          ;/* Calling r0-r12                  */
        ADD     R8, SP, #60
        STMDB   R8, {SP, LR}            ;/* Calling SP, LR                  */
        STR     LR, [R8, #0]            ;/* Save calling PC                 */
        MRS     R6, SPSR
        STR     R6, [R8, #4]            ;/* Save CPSR                       */
        STR     R0, [R8, #8]            ;/* Save OLD_R0                     */
        MOV     R0, SP

        BL      rt_hw_trap_dabt

;##########################################
; Reset Handler

        EXPORT  Reset_Handler
Reset_Handler

; Setup Stack for each mode ----------------------------------------------------

        LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
        MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
        MOV     SP, R0
        SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
        MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
        MOV     SP, R0
        SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
        MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
        MOV     SP, R0
        SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
        MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
        MOV     SP, R0
        SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
        MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
        MOV     SP, R0
        SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
        ; MSR     CPSR_c, #Mode_USR
        MOV     SP, R0
        SUB     SL, SP, #USR_Stack_Size

; Enter the C code -------------------------------------------------------------

        IMPORT  __main
        LDR     R0, =__main
        BX      R0

        IMPORT rt_interrupt_enter
        IMPORT rt_interrupt_leave
        IMPORT rt_thread_switch_interrupt_flag
        IMPORT rt_interrupt_from_thread
        IMPORT rt_interrupt_to_thread
        IMPORT rt_hw_trap_irq

IRQ_Handler     PROC
        EXPORT IRQ_Handler
        STMFD   sp!, {r0-r12,lr}
        BL  rt_interrupt_enter
        BL  rt_hw_trap_irq
        BL  rt_interrupt_leave

        ; if rt_thread_switch_interrupt_flag set, jump to
        ; rt_hw_context_switch_interrupt_do and don't return
        LDR r0, =rt_thread_switch_interrupt_flag
        LDR r1, [r0]
        CMP r1, #1
        BEQ rt_hw_context_switch_interrupt_do

        LDMFD   sp!, {r0-r12,lr}
        SUBS    pc, lr, #4
        ENDP

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
rt_hw_context_switch_interrupt_do   PROC
        EXPORT rt_hw_context_switch_interrupt_do
        MOV     r1,  #0         ; clear flag
        STR     r1,  [r0]

        LDMFD   sp!, {r0-r12,lr}; reload saved registers
        STMFD   sp!, {r0-r3}    ; save r0-r3
        MOV     r1,  sp
        ADD     sp,  sp, #16    ; restore sp
        SUB     r2,  lr, #4     ; save old task's pc to r2

        MRS     r3,  spsr       ; get cpsr of interrupt thread

        ; switch to SVC mode and no interrupt
        MSR     cpsr_c, #I_Bit:OR:F_Bit:OR:Mode_SVC

        STMFD   sp!, {r2}       ; push old task's pc
        STMFD   sp!, {r4-r12,lr}; push old task's lr,r12-r4
        MOV     r4,  r1         ; Special optimised code below
        MOV     r5,  r3
        LDMFD   r4!, {r0-r3}
        STMFD   sp!, {r0-r3}    ; push old task's r3-r0
        STMFD   sp!, {r5}       ; push old task's cpsr

        LDR     r4,  =rt_interrupt_from_thread
        LDR     r5,  [r4]
        STR     sp,  [r5]       ; store sp in preempted tasks's TCB

        LDR     r6,  =rt_interrupt_to_thread
        LDR     r6,  [r6]
        LDR     sp,  [r6]       ; get new task's stack pointer

        LDMFD   sp!, {r4}       ; pop new task's cpsr to spsr
        MSR     spsr_cxsf, r4

        LDMFD   sp!, {r0-r12,lr,pc}^ ; pop new task's r0-r12,lr & pc, copy spsr to cpsr
        ENDP

        IF      :DEF:__MICROLIB

        EXPORT  __heap_base
        EXPORT  __heap_limit

        ELSE
; User Initial Stack & Heap
        AREA    |.text|, CODE, READONLY

        IMPORT  __use_two_region_memory
        EXPORT  __user_initial_stackheap
__user_initial_stackheap

        LDR     R0, =  Heap_Mem
        LDR     R1, =(Stack_Mem + USR_Stack_Size)
        LDR     R2, = (Heap_Mem +      Heap_Size)
        LDR     R3, = Stack_Mem
        BX      LR
        ENDIF

        END
