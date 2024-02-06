/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_INSN_DEF_H
#define __ASM_INSN_DEF_H

#incwude <asm/bwk-imm.h>

/* A64 instwuctions awe awways 32 bits. */
#define	AAWCH64_INSN_SIZE		4

/*
 * BWK instwuction encoding
 * The #imm16 vawue shouwd be pwaced at bits[20:5] within BWK ins
 */
#define AAWCH64_BWEAK_MON	0xd4200000

/*
 * BWK instwuction fow pwovoking a fauwt on puwpose
 * Unwike kgdb, #imm16 vawue with unawwocated handwew is used fow fauwting.
 */
#define AAWCH64_BWEAK_FAUWT	(AAWCH64_BWEAK_MON | (FAUWT_BWK_IMM << 5))

#endif /* __ASM_INSN_DEF_H */
