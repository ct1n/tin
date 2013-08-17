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

