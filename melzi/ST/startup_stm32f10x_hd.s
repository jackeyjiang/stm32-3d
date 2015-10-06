;******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
;* File Name          : startup_stm32f10x_hd.s
;* Author             : MCD Application Team
;* Version            : V3.5.0
;* Date               : 11-March-2011
;* Description        : STM32F10x High Density Devices vector table for MDK-ARM 
;*                      toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system and also configure the external 
;*                        SRAM mounted on STM3210E-EVAL board to be used as data 
;*                        memory (optional, to be enabled by user)
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM3 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>    
;*******************************************************************************
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
; AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
; INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
; CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
; INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*******************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000800

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               		; Top of Stack
                DCD     __exc_reset              			; Reset Handler
                DCD     __exc_nmi                			; NMI Handler
                DCD     __exc_hardfault          			; Hard Fault Handler
                DCD     __exc_memmanage          			; MPU Fault Handler
                DCD     __exc_busfault           			; Bus Fault Handler
                DCD     __exc_usagefault         			; Usage Fault Handler
                DCD     __stm32reservedexception7     ; Reserved
                DCD     __stm32reservedexception8     ; Reserved
                DCD     __stm32reservedexception9     ; Reserved
                DCD     __stm32reservedexception10    ; Reserved
                DCD     SVC_Handler                		; SVCall Handler
                DCD     __exc_debug_monitor           ; Debug Monitor Handler
                DCD     __stm32reservedexception13    ; Reserved
                DCD     PendSV_Handler             		; PendSV Handler
                DCD     SysTick_Handler             	; SysTick Handler

                ; External Interrupts
                DCD     __irq_wwdg            				; Window Watchdog
                DCD     __irq_pvd             				; PVD through EXTI Line detect
                DCD     __irq_tamper          				; Tamper
                DCD     __irq_rtc             				; RTC
                DCD     __irq_flash           				; Flash
                DCD     __irq_rcc             				; RCC
                DCD     __irq_exti0           				; EXTI Line 0
                DCD     __irq_exti1           				; EXTI Line 1
                DCD     __irq_exti2           				; EXTI Line 2
                DCD     __irq_exti3           				; EXTI Line 3
                DCD     __irq_exti4           				; EXTI Line 4
                DCD     __irq_dma1_channel1   				; DMA1 Channel 1
                DCD     __irq_dma1_channel2   				; DMA1 Channel 2
                DCD     __irq_dma1_channel3   				; DMA1 Channel 3
                DCD     __irq_dma1_channel4   				; DMA1 Channel 4
                DCD     __irq_dma1_channel5   				; DMA1 Channel 5
                DCD     __irq_dma1_channel6   				; DMA1 Channel 6
                DCD     __irq_dma1_channel7   				; DMA1 Channel 7
                DCD     __irq_adc          						; ADC1_2
                DCD     __irq_usb_hp_can_tx  					; USB High Priority or CAN1 TX
                DCD     __irq_usb_lp_can_rx0 					; USB Low  Priority or CAN1 RX0
                DCD     __irq_can1_rx1        				; CAN1 RX1
                DCD     __irq_can1_sce        				; CAN1 SCE
                DCD     __irq_exti9_5         				; EXTI Line 9..5
                DCD     __irq_tim1_brk       					; TIM1 Break
                DCD     __irq_tim1_up       					; TIM1 Update
                DCD     __irq_tim1_trg_com  					; TIM1 Trigger and Commutation
                DCD     __irq_tim1_cc         				; TIM1 Capture Compare
                DCD     __irq_tim2            				; TIM2
                DCD     __irq_tim3            				; TIM3
                DCD     __irq_tim4            				; TIM4
                DCD     __irq_i2c1_ev         				; I2C1 Event
                DCD     __irq_i2c1_er         				; I2C1 Error
                DCD     __irq_i2c2_ev         				; I2C2 Event
                DCD     __irq_i2c2_er         				; I2C2 Error
                DCD     __irq_spi1            				; SPI1
                DCD     __irq_spi2            				; SPI2
                DCD     __irq_usart1          				; USART1
                DCD     __irq_usart2          				; USART2
                DCD     __irq_usart3          				; USART3
                DCD     __irq_exti15_10       				; EXTI Line 15..10
                DCD     __irq_rtc_alarm        				; RTC Alarm through EXTI Line
                DCD     __irq_usbwakeup    						; USB Wakeup from suspend
                DCD     __irq_tim8_brk       					; TIM8 Break
                DCD     __irq_tim8_up       					; TIM8 Update
                DCD     __irq_tim8_trg_com  					; TIM8 Trigger and Commutation
                DCD     __irq_tim8_cc         				; TIM8 Capture Compare
                DCD     __irq_adc3          					; ADC3
                DCD     __irq_fsmc         						;	fsmc
                DCD     __irq_sdio          					; sdio
                DCD     __irq_tim5         						;	TIM5
                DCD     __irq_spi3          					; SPI3 
                DCD     __irq_usart4       						; USART4
                DCD     __irq_usart5       						; USART5
                DCD     __irq_tim6         						;	TIM6
                DCD     __irq_tim7         						;	TIM7
                DCD     __irq_dma2_channel1 					; DMA2 Channel 1
                DCD     __irq_dma2_channel2 					; DMA2 Channel 2
                DCD     __irq_dma2_channel3 					; DMA2 Channel 3
                DCD     __irq_dma2_channel4_5 				; DMA2 Channel 4_5
				
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
__exc_reset    PROC
                 EXPORT  __exc_reset             [WEAK]
     IMPORT  __main
     IMPORT  SystemInit
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

__exc_nmi     	PROC
                EXPORT  __exc_nmi                [WEAK]
                B       .
                ENDP
__exc_hardfault\
                PROC
                EXPORT  __exc_hardfault          [WEAK]
                B       .
                ENDP
__exc_memmanage\
                PROC
                EXPORT  __exc_memmanage          [WEAK]
                B       .
                ENDP
__exc_busfault\
                PROC
                EXPORT  __exc_busfault           [WEAK]
                B       .
                ENDP
__exc_usagefault\
                PROC
                EXPORT  __exc_usagefault         [WEAK]
                B       .
                ENDP
__stm32reservedexception7\
                PROC
                EXPORT  __stm32reservedexception7         	[WEAK]
                B       .
                ENDP
__stm32reservedexception8\
                PROC
                EXPORT  __stm32reservedexception8         	[WEAK]
                B       .
                ENDP
__stm32reservedexception9\
                PROC
                EXPORT  __stm32reservedexception9         	[WEAK]
                B       .
                ENDP
__stm32reservedexception10\
                PROC
                EXPORT  __stm32reservedexception10         	[WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                					[WEAK]
                B       .
                ENDP
__exc_debug_monitor\
                PROC
                EXPORT  __exc_debug_monitor           			[WEAK]
                B       .
                ENDP
__stm32reservedexception13\
                PROC
                EXPORT  __stm32reservedexception13    			[WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             					[WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            					[WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  __irq_wwdg            [WEAK]
                EXPORT  __irq_pvd             [WEAK]
                EXPORT  __irq_tamper      		[WEAK]
                EXPORT  __irq_rtc        			[WEAK]
                EXPORT  __irq_flash           [WEAK]
                EXPORT  __irq_rcc             [WEAK]
                EXPORT  __irq_exti0           [WEAK]
                EXPORT  __irq_exti1           [WEAK]
                EXPORT  __irq_exti2           [WEAK]
                EXPORT  __irq_exti3           [WEAK]
                EXPORT  __irq_exti4           [WEAK]
                EXPORT  __irq_dma1_channel1 	[WEAK]
                EXPORT  __irq_dma1_channel2  	[WEAK]
                EXPORT  __irq_dma1_channel3  	[WEAK]
                EXPORT  __irq_dma1_channel4 	[WEAK]
                EXPORT  __irq_dma1_channel5  	[WEAK]
                EXPORT  __irq_dma1_channel6 	[WEAK]
                EXPORT  __irq_dma1_channel7 	[WEAK]
                EXPORT  __irq_adc          		[WEAK]
                EXPORT  __irq_usb_hp_can_tx 	[WEAK]
                EXPORT  __irq_usb_lp_can_rx0 	[WEAK]
                EXPORT  __irq_can1_rx1        [WEAK]
                EXPORT  __irq_can1_sce        [WEAK]
                EXPORT  __irq_exti9_5         [WEAK]
                EXPORT  __irq_tim1_brk      	[WEAK]
                EXPORT  __irq_tim1_up      		[WEAK]
                EXPORT  __irq_tim1_trg_com   	[WEAK]
                EXPORT  __irq_tim1_cc         [WEAK]
                EXPORT  __irq_tim2            [WEAK]
                EXPORT  __irq_tim3            [WEAK]
                EXPORT  __irq_tim4            [WEAK]
                EXPORT  __irq_i2c1_ev         [WEAK]
                EXPORT  __irq_i2c1_er         [WEAK]
                EXPORT  __irq_i2c2_ev      		[WEAK]
                EXPORT  __irq_i2c2_er    			[WEAK]
                EXPORT  __irq_spi1        		[WEAK]
                EXPORT  __irq_spi2         		[WEAK]
                EXPORT  __irq_usart1       		[WEAK]
                EXPORT  __irq_usart2       		[WEAK]
                EXPORT  __irq_usart3        	[WEAK]
                EXPORT  __irq_exti15_10   		[WEAK]
                EXPORT  __irq_rtc_alarm     	[WEAK]
                EXPORT  __irq_usbwakeup				[WEAK]
                EXPORT  __irq_tim8_brk     		[WEAK]
                EXPORT  __irq_tim8_up    			[WEAK]
                EXPORT  __irq_tim8_trg_com   	[WEAK]
                EXPORT  __irq_tim8_cc         [WEAK]
                EXPORT  __irq_adc3         		[WEAK]
                EXPORT  __irq_fsmc         		[WEAK]
                EXPORT  __irq_sdio         		[WEAK] 
                EXPORT  __irq_tim5         		[WEAK] 
                EXPORT  __irq_spi3         		[WEAK] 
                EXPORT  __irq_usart4       		[WEAK]
                EXPORT  __irq_usart5       		[WEAK]
                EXPORT  __irq_tim6         		[WEAK]
                EXPORT  __irq_tim7         		[WEAK]
                EXPORT  __irq_dma2_channel1 	[WEAK]
                EXPORT  __irq_dma2_channel2 	[WEAK]
                EXPORT  __irq_dma2_channel3 	[WEAK]
                EXPORT  __irq_dma2_channel4_5 [WEAK]
                         
__irq_wwdg
__irq_pvd
__irq_tamper
__irq_rtc
__irq_flash
__irq_rcc
__irq_exti0
__irq_exti1
__irq_exti2
__irq_exti3
__irq_exti4
__irq_dma1_channel1
__irq_dma1_channel2
__irq_dma1_channel3
__irq_dma1_channel4
__irq_dma1_channel5
__irq_dma1_channel6
__irq_dma1_channel7
__irq_adc
__irq_usb_hp_can_tx
__irq_usb_lp_can_rx0
__irq_can1_rx1
__irq_can1_sce
__irq_exti9_5
__irq_tim1_brk
__irq_tim1_up
__irq_tim1_trg_com
__irq_tim1_cc
__irq_tim2
__irq_tim3
__irq_tim4
__irq_i2c1_ev
__irq_i2c1_er
__irq_i2c2_ev
__irq_i2c2_er
__irq_spi1
__irq_spi2
__irq_usart1
__irq_usart2
__irq_usart3
__irq_exti15_10
__irq_rtc_alarm
__irq_usbwakeup
__irq_tim8_brk        	
__irq_tim8_up         	
__irq_tim8_trg_com    	
__irq_tim8_cc 
__irq_adc3  
__irq_fsmc
__irq_sdio  
__irq_tim5
__irq_spi3
__irq_usart4       		
__irq_usart5       		
__irq_tim6         		
__irq_tim7         		
__irq_dma2_channel1
__irq_dma2_channel2 	
__irq_dma2_channel3 	
__irq_dma2_channel4_5 

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB           
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE*****
