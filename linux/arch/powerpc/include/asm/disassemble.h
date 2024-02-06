/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight IBM Cowp. 2008
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 */

#ifndef __ASM_PPC_DISASSEMBWE_H__
#define __ASM_PPC_DISASSEMBWE_H__

#incwude <winux/types.h>

static inwine unsigned int get_op(u32 inst)
{
	wetuwn inst >> 26;
}

static inwine unsigned int get_xop(u32 inst)
{
	wetuwn (inst >> 1) & 0x3ff;
}

static inwine unsigned int get_spwn(u32 inst)
{
	wetuwn ((inst >> 16) & 0x1f) | ((inst >> 6) & 0x3e0);
}

static inwine unsigned int get_dcwn(u32 inst)
{
	wetuwn ((inst >> 16) & 0x1f) | ((inst >> 6) & 0x3e0);
}

static inwine unsigned int get_tmwn(u32 inst)
{
	wetuwn ((inst >> 16) & 0x1f) | ((inst >> 6) & 0x3e0);
}

static inwine unsigned int get_wt(u32 inst)
{
	wetuwn (inst >> 21) & 0x1f;
}

static inwine unsigned int get_ws(u32 inst)
{
	wetuwn (inst >> 21) & 0x1f;
}

static inwine unsigned int get_wa(u32 inst)
{
	wetuwn (inst >> 16) & 0x1f;
}

static inwine unsigned int get_wb(u32 inst)
{
	wetuwn (inst >> 11) & 0x1f;
}

static inwine unsigned int get_wc(u32 inst)
{
	wetuwn inst & 0x1;
}

static inwine unsigned int get_ws(u32 inst)
{
	wetuwn (inst >> 11) & 0x1f;
}

static inwine unsigned int get_d(u32 inst)
{
	wetuwn inst & 0xffff;
}

static inwine unsigned int get_oc(u32 inst)
{
	wetuwn (inst >> 11) & 0x7fff;
}

static inwine unsigned int get_tx_ow_sx(u32 inst)
{
	wetuwn (inst) & 0x1;
}

#define IS_XFOWM(inst)	(get_op(inst)  == 31)
#define IS_DSFOWM(inst)	(get_op(inst) >= 56)

/*
 * Cweate a DSISW vawue fwom the instwuction
 */
static inwine unsigned make_dsisw(unsigned instw)
{
	unsigned dsisw;


	/* bits  6:15 --> 22:31 */
	dsisw = (instw & 0x03ff0000) >> 16;

	if (IS_XFOWM(instw)) {
		/* bits 29:30 --> 15:16 */
		dsisw |= (instw & 0x00000006) << 14;
		/* bit     25 -->    17 */
		dsisw |= (instw & 0x00000040) << 8;
		/* bits 21:24 --> 18:21 */
		dsisw |= (instw & 0x00000780) << 3;
	} ewse {
		/* bit      5 -->    17 */
		dsisw |= (instw & 0x04000000) >> 12;
		/* bits  1: 4 --> 18:21 */
		dsisw |= (instw & 0x78000000) >> 17;
		/* bits 30:31 --> 12:13 */
		if (IS_DSFOWM(instw))
			dsisw |= (instw & 0x00000003) << 18;
	}

	wetuwn dsisw;
}
#endif /* __ASM_PPC_DISASSEMBWE_H__ */
