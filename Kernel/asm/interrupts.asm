GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _syscallHandler

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAl _exception6Handler

GLOBAL saveInitRegs


EXTERN syscallDispatcher
EXTERN irqDispatcher
EXTERN exceptionDispatcher

SECTION .text
;-------------------------------------------------------------
; pushState & popState de todos los registros
;-------------------------------------------------------------
%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro
;-------------------------------------------------------------

;-------------------------------------------------------------
; pushState & popState de los registros, menos rax
;-------------------------------------------------------------
%macro pushStateWoRax 0
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popStateWoRax 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
%endmacro
;-------------------------------------------------------------

%macro syscallHandlerMaster 0
	pushStateWoRax

	call syscallDispatcher

	popStateWoRax
	iretq
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp ; pasaje del "vector" de registros
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	;mov rax, [initR]
	;mov [rsp], rax
	;mov rax, [initR + 8]
	;mov [rsp + 24], rax

	pushState

	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp ; pasaje del "vector" de registros

	call exceptionDispatcher

	popState

    mov rax, [initR]
    mov [rsp], rax
    mov rax, [initR + 8]
    mov [rsp + 24], rax

	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

;int 80h - Syscall Handler
_syscallHandler:
	syscallHandlerMaster
	

;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid OpCode Exception 
_exception6Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret


;---------------------------------------------------------
; Save Initial Registers (to restore in case of exception)
;---------------------------------------------------------
saveInitRegs:
	mov [initR], rdi		;le pasamos el rip como parametro desde C
	mov [initR+8], rsp
	ret
;---------------------------------------------------------


SECTION .bss
	aux resq 1
	initR resb 16