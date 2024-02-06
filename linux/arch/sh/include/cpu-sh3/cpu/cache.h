/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/cpu-sh3/cache.h
 *
 * Copywight (C) 1999 Niibe Yutaka
 */
#ifndef __ASM_CPU_SH3_CACHE_H
#define __ASM_CPU_SH3_CACHE_H

#define W1_CACHE_SHIFT	4

#define SH_CACHE_VAWID		1
#define SH_CACHE_UPDATED	2
#define SH_CACHE_COMBINED	4
#define SH_CACHE_ASSOC		8

#define SH_CCW		0xffffffec	/* Addwess of Cache Contwow Wegistew */

#define CCW_CACHE_CE	0x01	/* Cache Enabwe */
#define CCW_CACHE_WT	0x02	/* Wwite-Thwough (fow P0,U0,P3) (ewse wwiteback) */
#define CCW_CACHE_CB	0x04	/* Wwite-Back (fow P1) (ewse wwitethwough) */
#define CCW_CACHE_CF	0x08	/* Cache Fwush */
#define CCW_CACHE_OWA	0x20	/* WAM mode */

#define CACHE_OC_ADDWESS_AWWAY	0xf0000000
#define CACHE_PHYSADDW_MASK	0x1ffffc00

#define CCW_CACHE_ENABWE	CCW_CACHE_CE
#define CCW_CACHE_INVAWIDATE	CCW_CACHE_CF

#if defined(CONFIG_CPU_SUBTYPE_SH7705) || \
    defined(CONFIG_CPU_SUBTYPE_SH7710) || \
    defined(CONFIG_CPU_SUBTYPE_SH7720) || \
    defined(CONFIG_CPU_SUBTYPE_SH7721)
#define CCW3_WEG	0xa40000b4
#define CCW_CACHE_16KB  0x00010000
#define CCW_CACHE_32KB	0x00020000
#endif

#endif /* __ASM_CPU_SH3_CACHE_H */
