;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module OSAL_App
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _tasksCnt
	.globl _tasksArr
	.globl _Application_ProcessEvent
	.globl _tasksEvents
	.globl _osalInitTasks
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
_tasksEvents::
	.ds 2
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)

; default segment ordering for linker
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area CONST
	.area INITIALIZER
	.area CODE

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	./src/OSAL_App.c: 5: uint16 Application_ProcessEvent( uint8 task_id, uint16 events )
;	-----------------------------------------
;	 function Application_ProcessEvent
;	-----------------------------------------
_Application_ProcessEvent:
;	./src/OSAL_App.c: 7: return 0;
	clrw	x
;	./src/OSAL_App.c: 8: }
	ret
;	./src/OSAL_App.c: 20: void osalInitTasks( void )
;	-----------------------------------------
;	 function osalInitTasks
;	-----------------------------------------
_osalInitTasks:
;	./src/OSAL_App.c: 22: }
	ret
	.area CODE
	.area CONST
_tasksArr:
	.dw _Application_ProcessEvent
_tasksCnt:
	.db #0x01	; 1
	.area INITIALIZER
	.area CABS (ABS)
