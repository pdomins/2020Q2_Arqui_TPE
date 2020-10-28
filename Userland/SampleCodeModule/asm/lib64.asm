GLOBAL sysTime
GLOBAL sysRead
GLOBAL sysWrite

;------------------------------------------------------------
;                       WONDERLAND
;------------------------------------------------------------

; NIIIIIIIIIIIISAN
section .text
;------------------------------------------------------------
; void sysTime(char* time_array)
; devuelve la hora y la fecha local dentro de un struct
;------------------------------------------------------------
sysTime:
    mov rsi, rdi
    mov rdi, 10     ;system call get time
    int 80h
    ret
;------------------------------------------------------------


;------------------------------------------------------------
; void sysRead(int length, char* time_array)
; lee un string de entrada estándar
;------------------------------------------------------------
sysRead:
    mov rdx, rsi    ;paso el vector a rdx
    mov rsi, rdi    ; paso la longitud a rsi
    mov rdi, 0
    int 80h
    ret
    
;------------------------------------------------------------
; void sysWrite(int length, char* time_array)
; escribe un string en salida estándar
;------------------------------------------------------------
sysWrite:
    mov rdx, rsi    ;paso el vector a rdx
    mov rsi, rdi    ; paso la longitud a rsi
    mov rdi, 1
    int 80h
    ret
;------------------------------------------------------------
