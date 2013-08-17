#define SEG_NULLASM                                                  \
		.word 0, 0;                                                  \
		.byte 0, 0, 0, 0

#define SEG_ASM(type, base, lim)                                     \
		.word (((lim) >> 12) & 0xFFFF),                              \
		      ((base) & 0xFFFF);                                     \
		.byte (((base) >> 16) & 0xFF),                               \
		      (0x90 | (type)),                                       \
		      (0xC0 | (((lim) >> 28) & 0x0F)),                       \
		      (((base) >> 24) & 0xFF)

#define STA_X	0x08	// executable segment
#define STA_E	0x04	// expand down (non-exec)
#define STA_C	0x04	// conforming code segment (exec)
#define STA_W	0x02	// writeable (non-exec)
#define STA_R	0x02	// readable (exec)
#define STA_A	0x01	// accessed
