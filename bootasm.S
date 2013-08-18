#include "asm.h"
#include "mmu.h"

.code16
.globl start
start:
	cli

	xorw	%ax, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss

seta20_1:
	inb		$0x64, %al
	testb	$0x02, %al
	jnz		seta20_1

	movb	$0xd1, %al
	outb	%al, $0x64

seta20_2:
	inb		$0x64, %al
	testb	$0x02, %al
	jnz		seta20_2

	movb	$0xdf, %al
	outb	%al, $0x60

	lgdt	gdtdesc
	movl	%cr0, %eax
	orl		$CR0_PE, %eax
	movl	%eax, %cr0

	ljmp	$8, $start32

.code32
start32:
	movw	$16, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	xorw	%ax, %ax
	movw	%ax, %fs
	movw	%ax, %gs

	movl	$start, %esp
	call	bootmain

spin:
	jmp		spin

.p2align 2
gdt:
	SEG_NULLASM
	SEG_ASM(STA_X | STA_R, 0x00, 0xFFFFFFFF)	// code seg
	SEG_ASM(STA_W, 0x00, 0xFFFFFFFF)			// data seg
gdtdesc:
	.word	(gdtdesc - gdt - 1)
	.long	gdt
