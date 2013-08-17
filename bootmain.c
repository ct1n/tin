#include "types.h"
#include "elf.h"
#include "x86.h"

#define SECTSZ	512

void read(uchar*, uint, uint);

void
bootmain(void)
{
	Elfhdr	*elf;
	Proghdr	*ph, *eph;
	void (*entry)(void);
	uchar	*pa;

	elf = (Elfhdr*)0x10000;

	read((uchar*)elf, 4096, 0);

	if (elf->magic != ELF_MAGIC)
		return;

	ph = (Proghdr*)((uchar*)elf + elf->phoff);
	eph = ph + elf->phnum;
	for (; ph < eph; ph++) {
		pa = (uchar*)ph->paddr;
		read(pa, ph->filesz, ph->off);
		if (ph->memsz > ph->filesz)
			stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
	}

	entry = (void(*)(void))elf->entry;
	entry();
}

void
waitdisk(void)
{
	while((inb(0x1F7) & 0xC0) != 0x40)
		;
}

void
readsect(void *dst, uint offset)
{
	waitdisk();
	outb(0x1F2, 1);	// count
	outb(0x1F3, offset);
	outb(0x1F4, offset >> 8);
	outb(0x1F5, offset >> 16);
	outb(0x1F6, (offset >> 24) | 0xE0);
	outb(0x1F7, 0x20);	// cmd 0x20 - read sectors

	waitdisk();
	insl(0x1F0, dst, SECTSZ / 4);
}

void
read(uchar *pa, uint n, uint offset)
{
	uchar *epa;

	epa = pa + n;
	pa -= offset % SECTSZ;
	offset = (offset / SECTSZ) + 1;	// kernel starts at sector 1

	for (; pa < epa; pa += SECTSZ, offset++)
		readsect(pa, offset);
}
