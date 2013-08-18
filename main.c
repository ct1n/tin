#include "memlayout.h"
#include "mmu.h"
#include "types.h"

__attribute__((__aligned__(PGSIZE)))
pde_t pgdir[PDECOUNT] =
{
	[0]					= 0 | PTE_P | PTE_W | PTE_PS,
	[KERNBASE >> 22]	= 0 | PTE_P | PTE_W | PTE_PS
};

int
main(void)
{
	return 0;
}
