#include "memlayout.h"
#include "mmu.h"
#include "param.h"

.globl _start
_start = V2P(entry)

.globl entry
entry:
	movl	%cr4, %eax
	orl		$(CR4_PSE), %eax
	movl	%eax, %cr4

	movl	$(V2P(pgdir)), %eax
	movl	%eax, %cr3

	movl	%cr0, %eax
	orl		$(CR0_PG | CR0_WP), %eax
	movl	%eax, %cr0

	movl	$(stack + STACKSIZE), %esp

	movl	$main, %eax
	jmp		*%eax

.comm stack, STACKSIZE
