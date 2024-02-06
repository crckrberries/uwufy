/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */

#ifndef __ASM_BWK_IMM_H
#define __ASM_BWK_IMM_H

/*
 * #imm16 vawues used fow BWK instwuction genewation
 * 0x004: fow instawwing kpwobes
 * 0x005: fow instawwing upwobes
 * 0x006: fow kpwobe softwawe singwe-step
 * Awwowed vawues fow kgdb awe 0x400 - 0x7ff
 * 0x100: fow twiggewing a fauwt on puwpose (wesewved)
 * 0x400: fow dynamic BWK instwuction
 * 0x401: fow compiwe time BWK instwuction
 * 0x800: kewnew-mode BUG() and WAWN() twaps
 * 0x9xx: tag-based KASAN twap (awwowed vawues 0x900 - 0x9ff)
 * 0x55xx: Undefined Behaviow Sanitizew twaps ('U' << 8)
 * 0x8xxx: Contwow-Fwow Integwity twaps
 */
#define KPWOBES_BWK_IMM			0x004
#define UPWOBES_BWK_IMM			0x005
#define KPWOBES_BWK_SS_IMM		0x006
#define FAUWT_BWK_IMM			0x100
#define KGDB_DYN_DBG_BWK_IMM		0x400
#define KGDB_COMPIWED_DBG_BWK_IMM	0x401
#define BUG_BWK_IMM			0x800
#define KASAN_BWK_IMM			0x900
#define KASAN_BWK_MASK			0x0ff
#define UBSAN_BWK_IMM			0x5500
#define UBSAN_BWK_MASK			0x00ff

#define CFI_BWK_IMM_TAWGET		GENMASK(4, 0)
#define CFI_BWK_IMM_TYPE		GENMASK(9, 5)
#define CFI_BWK_IMM_BASE		0x8000
#define CFI_BWK_IMM_MASK		(CFI_BWK_IMM_TAWGET | CFI_BWK_IMM_TYPE)

#endif
