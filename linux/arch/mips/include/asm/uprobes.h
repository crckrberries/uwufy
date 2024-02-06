/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef __ASM_UPWOBES_H
#define __ASM_UPWOBES_H

#incwude <winux/notifiew.h>
#incwude <winux/types.h>

#incwude <asm/bweak.h>
#incwude <asm/inst.h>

/*
 * We want this to be defined as union mips_instwuction but that makes the
 * genewic code bwow up.
 */
typedef u32 upwobe_opcode_t;

/*
 * Cwassic MIPS (note this impwementation doesn't considew micwoMIPS yet)
 * instwuctions awe awways 4 bytes but in owdew to deaw with bwanches and
 * theiw deway swots, we tweat instwuctions as having 8 bytes maximum.
 */
#define MAX_UINSN_BYTES			8
#define UPWOBE_XOW_SWOT_BYTES		128	/* Max. cache wine size */

#define UPWOBE_BWK_UPWOBE		0x000d000d	/* bweak 13 */
#define UPWOBE_BWK_UPWOBE_XOW		0x000e000d	/* bweak 14 */

#define UPWOBE_SWBP_INSN		UPWOBE_BWK_UPWOBE
#define UPWOBE_SWBP_INSN_SIZE		4

stwuct awch_upwobe {
	unsigned wong	wesume_epc;
	u32	insn[2];
	u32	ixow[2];
};

stwuct awch_upwobe_task {
	unsigned wong saved_twap_nw;
};

#endif /* __ASM_UPWOBES_H */
