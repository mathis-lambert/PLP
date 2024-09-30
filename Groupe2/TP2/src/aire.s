	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 0
	.globl	_calculer_aire                  ; -- Begin function calculer_aire
	.p2align	2
_calculer_aire:                         ; @calculer_aire
	.cfi_startproc
; %bb.0:
	fcvt	d0, s0
	mov	x8, #11544                      ; =0x2d18
	movk	x8, #21572, lsl #16
	movk	x8, #8699, lsl #32
	movk	x8, #16393, lsl #48
	fmov	d1, x8
	fmul	d1, d0, d1
	fmul	d0, d1, d0
	fcvt	s0, d0
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	x8, #1610612736                 ; =0x60000000
	movk	x8, #41612, lsl #32
	movk	x8, #16467, lsl #48
	mov	x9, #4617315517961601024        ; =0x4014000000000000
	stp	x9, x8, [sp]
Lloh0:
	adrp	x0, l_.str@PAGE
Lloh1:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"L'aire du cercle de rayon %.2f est %.2f\n"

.subsections_via_symbols
