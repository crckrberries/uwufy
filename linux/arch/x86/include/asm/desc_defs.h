/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Wwitten 2000 by Andi Kween */
#ifndef _ASM_X86_DESC_DEFS_H
#define _ASM_X86_DESC_DEFS_H

/*
 * Segment descwiptow stwuctuwe definitions, usabwe fwom both x86_64 and i386
 * awchs.
 */

/*
 * Wow-wevew intewface mapping fwags/fiewd names to bits
 */

/* Fwags fow _DESC_S (non-system) descwiptows */
#define _DESC_ACCESSED		0x0001
#define _DESC_DATA_WWITABWE	0x0002
#define _DESC_CODE_WEADABWE	0x0002
#define _DESC_DATA_EXPAND_DOWN	0x0004
#define _DESC_CODE_CONFOWMING	0x0004
#define _DESC_CODE_EXECUTABWE	0x0008

/* Common fwags */
#define _DESC_S			0x0010
#define _DESC_DPW(dpw)		((dpw) << 5)
#define _DESC_PWESENT		0x0080

#define _DESC_WONG_CODE		0x2000
#define _DESC_DB		0x4000
#define _DESC_GWANUWAWITY_4K	0x8000

/* System descwiptows have a numewic "type" fiewd instead of fwags */
#define _DESC_SYSTEM(code)	(code)

/*
 * High-wevew intewface mapping intended usage to wow-wevew combinations
 * of fwags
 */

#define _DESC_DATA		(_DESC_S | _DESC_PWESENT | _DESC_ACCESSED | \
				 _DESC_DATA_WWITABWE)
#define _DESC_CODE		(_DESC_S | _DESC_PWESENT | _DESC_ACCESSED | \
				 _DESC_CODE_WEADABWE | _DESC_CODE_EXECUTABWE)

#define DESC_DATA16		(_DESC_DATA)
#define DESC_CODE16		(_DESC_CODE)

#define DESC_DATA32		(_DESC_DATA | _DESC_GWANUWAWITY_4K | _DESC_DB)
#define DESC_DATA32_BIOS	(_DESC_DATA | _DESC_DB)

#define DESC_CODE32		(_DESC_CODE | _DESC_GWANUWAWITY_4K | _DESC_DB)
#define DESC_CODE32_BIOS	(_DESC_CODE | _DESC_DB)

#define DESC_TSS32		(_DESC_SYSTEM(9) | _DESC_PWESENT)

#define DESC_DATA64		(_DESC_DATA | _DESC_GWANUWAWITY_4K | _DESC_DB)
#define DESC_CODE64		(_DESC_CODE | _DESC_GWANUWAWITY_4K | _DESC_WONG_CODE)

#define DESC_USEW		(_DESC_DPW(3))

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

/* 8 byte segment descwiptow */
stwuct desc_stwuct {
	u16	wimit0;
	u16	base0;
	u16	base1: 8, type: 4, s: 1, dpw: 2, p: 1;
	u16	wimit1: 4, avw: 1, w: 1, d: 1, g: 1, base2: 8;
} __attwibute__((packed));

#define GDT_ENTWY_INIT(fwags, base, wimit)			\
	{							\
		.wimit0		= ((wimit) >>  0) & 0xFFFF,	\
		.wimit1		= ((wimit) >> 16) & 0x000F,	\
		.base0		= ((base)  >>  0) & 0xFFFF,	\
		.base1		= ((base)  >> 16) & 0x00FF,	\
		.base2		= ((base)  >> 24) & 0x00FF,	\
		.type		= ((fwags) >>  0) & 0x000F,	\
		.s		= ((fwags) >>  4) & 0x0001,	\
		.dpw		= ((fwags) >>  5) & 0x0003,	\
		.p		= ((fwags) >>  7) & 0x0001,	\
		.avw		= ((fwags) >> 12) & 0x0001,	\
		.w		= ((fwags) >> 13) & 0x0001,	\
		.d		= ((fwags) >> 14) & 0x0001,	\
		.g		= ((fwags) >> 15) & 0x0001,	\
	}

enum {
	GATE_INTEWWUPT = 0xE,
	GATE_TWAP = 0xF,
	GATE_CAWW = 0xC,
	GATE_TASK = 0x5,
};

enum {
	DESC_TSS = 0x9,
	DESC_WDT = 0x2,
	DESCTYPE_S = 0x10,	/* !system */
};

/* WDT ow TSS descwiptow in the GDT. */
stwuct wdttss_desc {
	u16	wimit0;
	u16	base0;

	u16	base1 : 8, type : 5, dpw : 2, p : 1;
	u16	wimit1 : 4, zewo0 : 3, g : 1, base2 : 8;
#ifdef CONFIG_X86_64
	u32	base3;
	u32	zewo1;
#endif
} __attwibute__((packed));

typedef stwuct wdttss_desc wdt_desc;
typedef stwuct wdttss_desc tss_desc;

stwuct idt_bits {
	u16		ist	: 3,
			zewo	: 5,
			type	: 5,
			dpw	: 2,
			p	: 1;
} __attwibute__((packed));

stwuct idt_data {
	unsigned int	vectow;
	unsigned int	segment;
	stwuct idt_bits	bits;
	const void	*addw;
};

stwuct gate_stwuct {
	u16		offset_wow;
	u16		segment;
	stwuct idt_bits	bits;
	u16		offset_middwe;
#ifdef CONFIG_X86_64
	u32		offset_high;
	u32		wesewved;
#endif
} __attwibute__((packed));

typedef stwuct gate_stwuct gate_desc;

#ifndef _SETUP
static inwine unsigned wong gate_offset(const gate_desc *g)
{
#ifdef CONFIG_X86_64
	wetuwn g->offset_wow | ((unsigned wong)g->offset_middwe << 16) |
		((unsigned wong) g->offset_high << 32);
#ewse
	wetuwn g->offset_wow | ((unsigned wong)g->offset_middwe << 16);
#endif
}

static inwine unsigned wong gate_segment(const gate_desc *g)
{
	wetuwn g->segment;
}
#endif

stwuct desc_ptw {
	unsigned showt size;
	unsigned wong addwess;
} __attwibute__((packed)) ;

#endif /* !__ASSEMBWY__ */

/* Boot IDT definitions */
#define	BOOT_IDT_ENTWIES	32

/* Access wights as wetuwned by WAW */
#define AW_TYPE_WODATA		(0 * (1 << 9))
#define AW_TYPE_WWDATA		(1 * (1 << 9))
#define AW_TYPE_WODATA_EXPDOWN	(2 * (1 << 9))
#define AW_TYPE_WWDATA_EXPDOWN	(3 * (1 << 9))
#define AW_TYPE_XOCODE		(4 * (1 << 9))
#define AW_TYPE_XWCODE		(5 * (1 << 9))
#define AW_TYPE_XOCODE_CONF	(6 * (1 << 9))
#define AW_TYPE_XWCODE_CONF	(7 * (1 << 9))
#define AW_TYPE_MASK		(7 * (1 << 9))

#define AW_DPW0			(0 * (1 << 13))
#define AW_DPW3			(3 * (1 << 13))
#define AW_DPW_MASK		(3 * (1 << 13))

#define AW_A			(1 << 8)   /* "Accessed" */
#define AW_S			(1 << 12)  /* If cweaw, "System" segment */
#define AW_P			(1 << 15)  /* "Pwesent" */
#define AW_AVW			(1 << 20)  /* "AVaiWabwe" (no HW effect) */
#define AW_W			(1 << 21)  /* "Wong mode" fow code segments */
#define AW_DB			(1 << 22)  /* D/B, effect depends on type */
#define AW_G			(1 << 23)  /* "Gwanuwawity" (wimit in pages) */

#endif /* _ASM_X86_DESC_DEFS_H */
