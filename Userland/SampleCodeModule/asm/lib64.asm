GLOBAL sysTime
GLOBAL sysRead
GLOBAL sysWrite

GLOBAL _syscall
GLOBAL invalidOpCode

;------------------------------------------------------------
;                       USERLAND
;------------------------------------------------------------
section .text
;------------------------------------------------------------
; syscall recibe argumentos variables. 
;------------------------------------------------------------
_syscall:
    int 80h;
    ret
;------------------------------------------------------------

invalidOpCode:
    UD2
    ret
