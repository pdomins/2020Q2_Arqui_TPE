GLOBAL cpuVendor
GLOBAL getSeconds
GLOBAL getMinutes
GLOBAL getHours

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid

	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;---------------------------------------------------------
;	Real Time Clock and Memory (ports 70h & 71h)
;---------------------------------------------------------
getSeconds:
	mov rax, 0
	mov al, 0
	out 70h, al
	in al, 71h
	ret

getMinutes:
	mov rax,0
	mov al, 2
	out 70h, al
	in al, 71h
	ret

getHours:
	mov rax,0
	mov al, 4
	out 70h, al
	in al, 71h
	ret
;---------------------------------------------------------

;---------------------------------------------------------
;	Keyboard Controller (ports 60h & 64h)
;---------------------------------------------------------

;---------------------------------------------------------

