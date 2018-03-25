;;;;;; Produced by COMP


;;;;;; COMP Helper Macros

;;;
; Saves the working registers. Call this as the first thing in your subprogram.
;;;
PROTECT_REGS MACRO
	push AX
	push BX
	push CX
	push DX
#EM


;;;
; Restores the working registers previously protected by PROTECT_REGS.
; Call this as the last thing before ret in your subprogram.
; The stack must be clean, i.e., it must be as it was when PROTECT_REGS
; was called.
;;;
RESTORE_REGS MACRO
	pop DX
	pop CX
	pop BX
	pop AX
#EM


;;;
; Restores the registers and returns.
;;;
RESTORE_RET MACRO
	RESTORE_REGS
	ret
#EM

DATA SEGMENT

POW_DWORD_VAR_L DW ?
POW_DWORD_VAR_H DW ?
compxh0 DW ?
compxl0 DW ?
compxh1 DW ?
compxl1 DW ?
compxh2 DW ?
compxl2 DW ?
compxh3 DW ?
compxl3 DW ?
compxh4 DW ?
compxl4 DW ?
compxh5 DW ?
compxl5 DW ?
compxh6 DW ?
compxl6 DW ?
compxh7 DW ?
compxl7 DW ?


CODE SEGMENT
ORG	100H ; we are producing .com file


;;;;;; Actual Code
ds mov [compxh0], 0
ds mov [compxl0], 0
ds mov [compxh1], 0
ds mov [compxl1], 0
ds mov [compxh2], 0
ds mov [compxl2], 0
ds mov [compxh3], 0
ds mov [compxl3], 0
ds mov [compxh4], 0
ds mov [compxl4], 0
ds mov [compxh5], 0
ds mov [compxl5], 0
ds mov [compxh6], 0
ds mov [compxl6], 0
ds mov [compxh7], 0
ds mov [compxl7], 0
push 1
push 0
pop BX
pop AX
ds mov [compxl0], AX
ds mov [compxh0], BX
push 2
push 0
pop BX
pop AX
ds mov [compxl1], AX
ds mov [compxh1], BX
ds push [compxl0]
ds push [compxh0]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl0]
ds push [compxh0]
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
pop BX
pop AX
ds mov [compxl0], AX
ds mov [compxh0], BX
ds push [compxl1]
ds push [compxh1]
push 1
push 0
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
pop BX
pop AX
ds mov [compxl1], AX
ds mov [compxh1], BX
ds push [compxl0]
ds push [compxh0]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl0]
ds push [compxh0]
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
pop BX
pop AX
ds mov [compxl0], AX
ds mov [compxh0], BX
ds push [compxl1]
ds push [compxh1]
push 1
push 0
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
pop BX
pop AX
ds mov [compxl1], AX
ds mov [compxh1], BX
ds push [compxl0]
ds push [compxh0]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl0]
ds push [compxh0]
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
pop BX
pop AX
ds mov [compxl0], AX
ds mov [compxh0], BX
ds push [compxl1]
ds push [compxh1]
push 1
push 0
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
pop BX
pop AX
ds mov [compxl1], AX
ds mov [compxh1], BX
ds push [compxl0]
ds push [compxh0]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
ds push [compxl0]
ds push [compxh0]
ds push [compxl1]
ds push [compxh1]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
pop BX
pop AX
ds mov [compxl0], AX
ds mov [compxh0], BX
ds push [compxl0]
ds push [compxh0]
push 0
push 0
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
push 0
push 0
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
push 0
push 0
ds push [compxl2]
ds push [compxh2]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
ds push [compxl3]
ds push [compxh3]
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
ds push [compxl4]
ds push [compxh4]
ds push [compxl5]
ds push [compxh5]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
ds push [compxl6]
ds push [compxh6]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
ds push [compxl7]
ds push [compxh7]
pop BX
pop AX
pop DX
pop CX
call MUL_DWORD
push AX
push BX
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
ds push [compxl7]
ds push [compxh7]
pop BX
pop AX
pop DX
pop CX
call ADD_DWORD
push AX
push BX
push 2
push 0
push 2
push 0
pop BX
pop AX
pop DX
pop CX
call POW_DWORD
push AX
push BX
pop BX
pop AX
pop DX
pop CX
call POW_DWORD
push AX
push BX
pop BX
pop AX
mov DX, BX
mov CX, AX
call PRINT_DWORD
call PRINT_CLRF
call EXIT


;;;;;; COMP Assembly Internal Helpers

;;;
; Adds the DWORDS BX AX and DX CX, writing the result to BX AX.
;;;
ADD_DWORD:
	push CX
	push DX

	add AX, CX
	adc BX, DX ; Use the carry from AX + CX

	pop DX
	pop CX
	ret


;;;
; Multiplies the DWORDS BX AX and DX CX, writing the result to BX AX.
;
; Caution: This is a 32-bit multiplier, in other words, the output must
; fit in 32 bits. This implies either BX or DX is 0. Furthermore, BX*CX
; and AX*DX must fit in 16 bits. Hence, these are an assumption of this
; subprogram.
;;;
MUL_DWORD:
	push CX
	push DX

	; make sure DX is 0
	cmp BX, 0
	if Z xchg BX, DX
	if Z xchg AX, CX

	; prepare the low word
	mul CX

	; prepare the high word
	push AX
	push DX

	mov AX, BX
	mul CX
	mov BX, AX

	pop DX
	add BX, DX
	pop AX

	pop DX
	pop CX
	ret


;;;
; Sets the ZF to 1 if the DWORD BX AX is 0, to 0 if not.
;;;
CMP_ZERO_DWORD:
	cmp BX, AX
	if Z cmp BX, 0

	ret


;;;
; Places (DX CX)^(BX AX) into BX AX.
;
; Obviously, this is a 32-bit operation. Hence, the result is correct
; only if it fits into 32-bits.
;;;
POW_DWORD:
	push CX
	push DX

	; POW_DWORD_VAR will be the running multiplication result
	ds mov [POW_DWORD_VAR_L], 1
	ds mov [POW_DWORD_VAR_H], 0

	POW_DWORD__LOOP:
	call CMP_ZERO_DWORD
	je POW_DWORD__END

	call IS_ODD
	jne POW_DWORD__LOOP__NOT_ODD

	push AX
	push BX

	ds mov AX, [POW_DWORD_VAR_L]
	ds mov BX, [POW_DWORD_VAR_H]

	call MUL_DWORD

	ds mov [POW_DWORD_VAR_L], AX
	ds mov [POW_DWORD_VAR_H], BX

	pop BX
	pop AX

	POW_DWORD__LOOP__NOT_ODD:
	push AX
	push BX

	mov AX, CX
	mov BX, DX
	call MUL_DWORD
	mov CX, AX
	mov DX, BX

	pop BX
	pop AX

	call SHR_DWORD ; Integral division by two
	jmp POW_DWORD__LOOP

	POW_DWORD__END:

	ds mov BX, [POW_DWORD_VAR_H]
	ds mov AX, [POW_DWORD_VAR_L]

	pop DX
	pop CX
	ret


;;;
;	Sets ZF to 1 if AX is odd, to 0 if it is even.
;;;
IS_ODD:
	PROTECT_REGS

	and AX, 1
	cmp AX, 1

	RESTORE_RET

;;;
; Shifts the DWORD BX AX one bit right, placing the result to BX AX.
;;;
SHR_DWORD:
	push CX

	shr AX, 1
	shr BX, 1

	; LSB of BX will be MSB of AX
	jae SHR_DWORD__L1
	jb SHR_DWORD__L2

	SHR_DWORD__L1:
	and AH, 07fh
	jmp SHR_DWORD__END

	SHR_DWORD__L2:
	or AH, 080h

	SHR_DWORD__END:
	pop CX
	ret

;;;
; Prints the dword given as BX AX
;;;
PRINT_DWORD:
	PROTECT_REGS

	mov DH, BH
	call PRINT_BYTE

	mov DH, BL
	call PRINT_BYTE

	mov DH, AH
	call PRINT_BYTE

	mov DH, AL
	call PRINT_BYTE

	RESTORE_RET


;;;
; Prints the byte stored at DH
;;;
PRINT_BYTE:
	PROTECT_REGS

	mov DL, DH
	and DL, 0Fh
	and DH, 0F0h
	shr DH, 4

	mov CL, DL
	mov BX, HEX_DIGIT_CHAR_ARRAY
	mov AH, 0
	mov AL, DH
	add BX, AX
	ds mov DL, [BX]
	call PRINT_CHAR
	mov DL, CL

	mov BX, HEX_DIGIT_CHAR_ARRAY
	mov AH, 0
	mov AL, DL
	add BX, AX
	ds mov DL, [BX]
	call PRINT_CHAR

	RESTORE_RET


;;;
; Moves the cursor to the beginning of the next line
;;;
PRINT_CLRF:
	PROTECT_REGS

	mov DX, STRING_CLRF
	call PRINT_STR

	RESTORE_RET


;;;
; Prints the $-terminated string at the address DS:DX
;;;
PRINT_STR:
	PROTECT_REGS

	mov AH, 9h
	int 21h

	RESTORE_RET


;;;
; Prints the character with the ASCII code stored at DL
;;;
PRINT_CHAR:
	PROTECT_REGS

	mov AH, 2h
	int 21h

	RESTORE_RET


;;;
; Exits the program
;;;
EXIT:
	mov	AX, 4C00h
	int	21h

	ret


;;;;;; Internal variables and constants
STRING_CLRF: DB 0dh, 0ah, '$'
HEX_DIGIT_CHAR_ARRAY: DB '0123456789abcdef'

;;;;;; Variables
