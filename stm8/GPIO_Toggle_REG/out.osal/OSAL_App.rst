                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module OSAL_App
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _tasksCnt
                                     12 	.globl _tasksArr
                                     13 	.globl _Application_ProcessEvent
                                     14 	.globl _tasksEvents
                                     15 	.globl _osalInitTasks
                                     16 ;--------------------------------------------------------
                                     17 ; ram data
                                     18 ;--------------------------------------------------------
                                     19 	.area DATA
      000003                         20 _tasksEvents::
      000003                         21 	.ds 2
                                     22 ;--------------------------------------------------------
                                     23 ; ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area INITIALIZED
                                     26 ;--------------------------------------------------------
                                     27 ; absolute external ram data
                                     28 ;--------------------------------------------------------
                                     29 	.area DABS (ABS)
                                     30 
                                     31 ; default segment ordering for linker
                                     32 	.area HOME
                                     33 	.area GSINIT
                                     34 	.area GSFINAL
                                     35 	.area CONST
                                     36 	.area INITIALIZER
                                     37 	.area CODE
                                     38 
                                     39 ;--------------------------------------------------------
                                     40 ; global & static initialisations
                                     41 ;--------------------------------------------------------
                                     42 	.area HOME
                                     43 	.area GSINIT
                                     44 	.area GSFINAL
                                     45 	.area GSINIT
                                     46 ;--------------------------------------------------------
                                     47 ; Home
                                     48 ;--------------------------------------------------------
                                     49 	.area HOME
                                     50 	.area HOME
                                     51 ;--------------------------------------------------------
                                     52 ; code
                                     53 ;--------------------------------------------------------
                                     54 	.area CODE
                                     55 ;	./src/OSAL_App.c: 5: uint16 Application_ProcessEvent( uint8 task_id, uint16 events )
                                     56 ;	-----------------------------------------
                                     57 ;	 function Application_ProcessEvent
                                     58 ;	-----------------------------------------
      008427                         59 _Application_ProcessEvent:
                                     60 ;	./src/OSAL_App.c: 7: return 0;
      008427 5F               [ 1]   61 	clrw	x
                                     62 ;	./src/OSAL_App.c: 8: }
      008428 81               [ 4]   63 	ret
                                     64 ;	./src/OSAL_App.c: 20: void osalInitTasks( void )
                                     65 ;	-----------------------------------------
                                     66 ;	 function osalInitTasks
                                     67 ;	-----------------------------------------
      008429                         68 _osalInitTasks:
                                     69 ;	./src/OSAL_App.c: 22: }
      008429 81               [ 4]   70 	ret
                                     71 	.area CODE
                                     72 	.area CONST
      008024                         73 _tasksArr:
      008024 84 27                   74 	.dw _Application_ProcessEvent
      008026                         75 _tasksCnt:
      008026 01                      76 	.db #0x01	; 1
                                     77 	.area INITIALIZER
                                     78 	.area CABS (ABS)
