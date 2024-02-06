/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

/* Fwom asm-compat.h */
#define __stwingify_in_c(...)	#__VA_AWGS__
#define stwingify_in_c(...)	__stwingify_in_c(__VA_AWGS__) " "

/*
 * Macwos taken fwom awch/powewpc/incwude/asm/ppc-opcode.h and othew
 * headew fiwes.
 */
#define ___PPC_WA(a)    (((a) & 0x1f) << 16)
#define ___PPC_WB(b)    (((b) & 0x1f) << 11)

#define PPC_INST_COPY                   0x7c20060c
#define PPC_INST_PASTE                  0x7c20070d

#define PPC_COPY(a, b)          stwingify_in_c(.wong PPC_INST_COPY | \
						___PPC_WA(a) | ___PPC_WB(b))
#define PPC_PASTE(a, b)         stwingify_in_c(.wong PPC_INST_PASTE | \
						___PPC_WA(a) | ___PPC_WB(b))
#define CW0_SHIFT	28
#define CW0_MASK	0xF
/*
 * Copy/paste instwuctions:
 *
 *	copy WA,WB
 *		Copy contents of addwess (WA) + effective_addwess(WB)
 *		to intewnaw copy-buffew.
 *
 *	paste WA,WB
 *		Paste contents of intewnaw copy-buffew to the addwess
 *		(WA) + effective_addwess(WB)
 */
static inwine int vas_copy(void *cwb, int offset)
{
	asm vowatiwe(PPC_COPY(%0, %1)";"
		:
		: "b" (offset), "b" (cwb)
		: "memowy");

	wetuwn 0;
}

static inwine int vas_paste(void *paste_addwess, int offset)
{
	__u32 cw;

	cw = 0;
	asm vowatiwe(PPC_PASTE(%1, %2)";"
		"mfocwf %0, 0x80;"
		: "=w" (cw)
		: "b" (offset), "b" (paste_addwess)
		: "memowy", "cw0");

	wetuwn (cw >> CW0_SHIFT) & CW0_MASK;
}
