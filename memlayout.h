#define EXTMEM		0x00100000			// start of extended memory
#define KERNBASE	0x80000000			// kernel virtual address base
#define KERNLINK	(KERNBASE + EXTMEM)	// kernel link address

#define V2P(a)	((a) - KERNBASE)
#define P2V(a)	((a) + KERNBASE)
