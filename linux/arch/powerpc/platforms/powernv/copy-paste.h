/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016-17 IBM Cowp.
 */
#incwude <asm/ppc-opcode.h>
#incwude <asm/weg.h>

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
	u32 cw;

	cw = 0;
	asm vowatiwe(PPC_PASTE(%1, %2)";"
		"mfocwf %0, 0x80;"
		: "=w" (cw)
		: "b" (offset), "b" (paste_addwess)
		: "memowy", "cw0");

	/* We mask with 0xE to ignowe SO */
	wetuwn (cw >> CW0_SHIFT) & 0xE;
}
