	.file	"MWI.c"
	.intel_syntax noprefix
	.section .rdata,"dr"
LC0:
	.ascii "couldnt open file\0"
LC1:
	.ascii "%i\0"
	.text
.globl _getNextData
	.def	_getNextData;	.scl	2;	.type	32;	.endef
_getNextData:
	push	ebp
	mov	ebp, esp
	sub	esp, 40
	mov	DWORD PTR [ebp-12], 0
	cmp	DWORD PTR [ebp+8], 0
	jne	L2
	mov	DWORD PTR [esp], OFFSET FLAT:LC0
	call	_printf
	mov	eax, 0
	jmp	L3
L2:
	lea	eax, [ebp-12]
	mov	DWORD PTR [esp+8], eax
	mov	DWORD PTR [esp+4], OFFSET FLAT:LC1
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_fscanf
	mov	eax, DWORD PTR [ebp-12]
L3:
	leave
	ret
.globl _movingWindowIntegration
	.def	_movingWindowIntegration;	.scl	2;	.type	32;	.endef
_movingWindowIntegration:
	push	ebp
	mov	ebp, esp
	push	esi
	push	ebx
	sub	esp, 16
	mov	DWORD PTR [ebp-12], 0
	mov	DWORD PTR [ebp-16], 0
	mov	DWORD PTR [ebp-12], 30
	jmp	L5
L6:
	mov	eax, DWORD PTR [ebp+16]
	sal	eax, 2
	mov	ebx, eax
	add	ebx, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [ebp+16]
	sal	eax, 2
	add	eax, DWORD PTR [ebp+12]
	mov	esi, DWORD PTR [eax]
	mov	eax, DWORD PTR [ebp-12]
	sub	eax, 30
	add	eax, DWORD PTR [ebp+16]
	sal	eax, 2
	add	eax, DWORD PTR [ebp+8]
	mov	ecx, DWORD PTR [eax]
	mov	edx, -2004318071
	mov	eax, ecx
	imul	edx
	lea	eax, [edx+ecx]
	mov	edx, eax
	sar	edx, 4
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	eax, ecx
	lea	eax, [esi+eax]
	mov	DWORD PTR [ebx], eax
	sub	DWORD PTR [ebp-12], 1
L5:
	cmp	DWORD PTR [ebp-12], 0
	jg	L6
	mov	eax, DWORD PTR [ebp+16]
	sal	eax, 2
	add	eax, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [eax]
	add	esp, 16
	pop	ebx
	pop	esi
	pop	ebp
	ret
	.section .rdata,"dr"
LC2:
	.ascii "r\0"
	.align 4
LC3:
	.ascii "Error in line %d.\12Value was supposed to be %d, but was %d\12\0"
	.align 4
LC4:
	.ascii "\12If no errors were found, everything's good.\12\0"
	.text
.globl _testMWI
	.def	_testMWI;	.scl	2;	.type	32;	.endef
_testMWI:
	push	ebp
	mov	ebp, esp
	mov	eax, 36040
	call	___chkstk
	mov	DWORD PTR [ebp-16], 0
	mov	DWORD PTR [esp+4], OFFSET FLAT:LC2
	mov	DWORD PTR [esp], OFFSET FLAT:_filename.2034
	call	_fopen
	mov	DWORD PTR [ebp-16], eax
	mov	DWORD PTR [ebp-20], 0
	mov	DWORD PTR [esp+4], OFFSET FLAT:LC2
	mov	DWORD PTR [esp], OFFSET FLAT:_filename2.2036
	call	_fopen
	mov	DWORD PTR [ebp-20], eax
	lea	eax, [ebp-12020]
	mov	edx, 12000
	mov	DWORD PTR [esp+8], edx
	mov	DWORD PTR [esp+4], 0
	mov	DWORD PTR [esp], eax
	call	_memset
	lea	eax, [ebp-24020]
	mov	edx, 12000
	mov	DWORD PTR [esp+8], edx
	mov	DWORD PTR [esp+4], 0
	mov	DWORD PTR [esp], eax
	call	_memset
	lea	eax, [ebp-36020]
	mov	edx, 12000
	mov	DWORD PTR [esp+8], edx
	mov	DWORD PTR [esp+4], 0
	mov	DWORD PTR [esp], eax
	call	_memset
	mov	DWORD PTR [ebp-12], 0
	mov	DWORD PTR [ebp-12], 0
	jmp	L8
L9:
	mov	eax, DWORD PTR [ebp-16]
	mov	DWORD PTR [esp], eax
	call	_getNextData
	mov	edx, DWORD PTR [ebp-12]
	mov	DWORD PTR [ebp-12020+edx*4], eax
	mov	eax, DWORD PTR [ebp-20]
	mov	DWORD PTR [esp], eax
	call	_getNextData
	mov	edx, DWORD PTR [ebp-12]
	mov	DWORD PTR [ebp-36020+edx*4], eax
	mov	eax, DWORD PTR [ebp-12]
	mov	DWORD PTR [esp+8], eax
	lea	eax, [ebp-24020]
	mov	DWORD PTR [esp+4], eax
	lea	eax, [ebp-12020]
	mov	DWORD PTR [esp], eax
	call	_movingWindowIntegration
	mov	edx, DWORD PTR [ebp-12]
	mov	DWORD PTR [ebp-24020+edx*4], eax
	add	DWORD PTR [ebp-12], 1
L8:
	cmp	DWORD PTR [ebp-12], 2999
	jle	L9
	mov	DWORD PTR [ebp-12], 0
	jmp	L10
L12:
	mov	eax, DWORD PTR [ebp-12]
	mov	edx, DWORD PTR [ebp-36020+eax*4]
	mov	eax, DWORD PTR [ebp-12]
	mov	eax, DWORD PTR [ebp-24020+eax*4]
	cmp	edx, eax
	je	L11
	mov	eax, DWORD PTR [ebp-12]
	mov	edx, DWORD PTR [ebp-24020+eax*4]
	mov	eax, DWORD PTR [ebp-12]
	mov	eax, DWORD PTR [ebp-36020+eax*4]
	mov	DWORD PTR [esp+12], edx
	mov	DWORD PTR [esp+8], eax
	mov	eax, DWORD PTR [ebp-12]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:LC3
	call	_printf
L11:
	add	DWORD PTR [ebp-12], 1
L10:
	cmp	DWORD PTR [ebp-12], 2999
	jle	L12
	mov	DWORD PTR [esp], OFFSET FLAT:LC4
	call	_puts
	mov	eax, DWORD PTR [ebp-16]
	mov	DWORD PTR [esp], eax
	call	_fclose
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	push	ebp
	mov	ebp, esp
	and	esp, -16
	call	___main
	call	_testMWI
	mov	esp, ebp
	pop	ebp
	ret
	.section .rdata,"dr"
_filename.2034:
	.ascii "x_sqr.txt\0"
_filename2.2036:
	.ascii "x_mwi.txt\0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fscanf;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
