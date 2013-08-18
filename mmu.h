#define PGSIZE		4096	// page size
#define PDECOUNT	1024	// number of page directory entries

#define CR0_PE	0x00000001	// protection enable
#define CR0_MP	0x00000002	// monitor coprocessor
#define CR0_EM	0x00000004	// emulation
#define CR0_TS	0x00000008	// task switched
#define CR0_ET	0x00000010	// extension type
#define CR0_NE	0x00000020	// numeric error
#define CR0_WP	0x00010000	// write protect
#define CR0_AM	0x00040000	// alignment mask
#define CR0_NW	0x20000000	// not writethrough
#define CR0_CD	0x40000000	// cache disable
#define CR0_PG	0x80000000	// paging

#define CR4_PSE	0x00000010	// page size extension

#define PTE_P	0x0001	// present
#define PTE_W	0x0002	// writeable
#define PTE_U	0x0004	// user
#define PTE_PWT	0x0008	// write-through
#define PTE_PCD	0x0010	// cache-disable
#define PTE_A	0x0020	// accessed
#define PTE_D	0x0040	// dirty
#define PTE_PS	0x0080	// page size
#define PTE_MBZ	0x0180	// bits must be zero
