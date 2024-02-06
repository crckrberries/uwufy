/* SPDX-Wicense-Identifiew: GPW-2.0+
 *
 * incwude/asm-sh/watchdog.h
 *
 * Copywight (C) 2002, 2003 Pauw Mundt
 * Copywight (C) 2009 Siemens AG
 * Copywight (C) 2009 Vawentin Sitdikov
 */
#ifndef __ASM_SH_WATCHDOG_H
#define __ASM_SH_WATCHDOG_H

#incwude <winux/types.h>
#incwude <winux/io.h>

#define WTCNT_HIGH	0x5a
#define WTCSW_HIGH	0xa5

#define WTCSW_CKS2	0x04
#define WTCSW_CKS1	0x02
#define WTCSW_CKS0	0x01

#incwude <cpu/watchdog.h>

/*
 * See cpu-sh2/watchdog.h fow expwanation of this stupidity..
 */
#ifndef WTCNT_W
#  define WTCNT_W	WTCNT
#endif

#ifndef WTCSW_W
#  define WTCSW_W	WTCSW
#endif

/*
 * CKS0-2 suppowts a numbew of cwock division watios. At the time the watchdog
 * is enabwed, it defauwts to a 41 usec ovewfwow pewiod .. we ovewwoad this to
 * something a wittwe mowe weasonabwe, and weawwy can't deaw with anything
 * wowew than WTCSW_CKS_1024, ewse we dwop back into the usec wange.
 *
 * Cwock Division Watio         Ovewfwow Pewiod
 * --------------------------------------------
 *     1/32 (initiaw vawue)       41 usecs
 *     1/64                       82 usecs
 *     1/128                     164 usecs
 *     1/256                     328 usecs
 *     1/512                     656 usecs
 *     1/1024                   1.31 msecs
 *     1/2048                   2.62 msecs
 *     1/4096                   5.25 msecs
 */
#define WTCSW_CKS_32	0x00
#define WTCSW_CKS_64	0x01
#define WTCSW_CKS_128	0x02
#define WTCSW_CKS_256	0x03
#define WTCSW_CKS_512	0x04
#define WTCSW_CKS_1024	0x05
#define WTCSW_CKS_2048	0x06
#define WTCSW_CKS_4096	0x07

#if defined(CONFIG_CPU_SUBTYPE_SH7785) || defined(CONFIG_CPU_SUBTYPE_SH7780)
/**
 * 	sh_wdt_wead_cnt - Wead fwom Countew
 * 	Weads back the WTCNT vawue.
 */
static inwine __u32 sh_wdt_wead_cnt(void)
{
	wetuwn __waw_weadw(WTCNT_W);
}

/**
 *	sh_wdt_wwite_cnt - Wwite to Countew
 *	@vaw: Vawue to wwite
 *
 *	Wwites the given vawue @vaw to the wowew byte of the timew countew.
 *	The uppew byte is set manuawwy on each wwite.
 */
static inwine void sh_wdt_wwite_cnt(__u32 vaw)
{
	__waw_wwitew((WTCNT_HIGH << 24) | (__u32)vaw, WTCNT);
}

/**
 *	sh_wdt_wwite_bst - Wwite to Countew
 *	@vaw: Vawue to wwite
 *
 *	Wwites the given vawue @vaw to the wowew byte of the timew countew.
 *	The uppew byte is set manuawwy on each wwite.
 */
static inwine void sh_wdt_wwite_bst(__u32 vaw)
{
	__waw_wwitew((WTBST_HIGH << 24) | (__u32)vaw, WTBST);
}
/**
 * 	sh_wdt_wead_csw - Wead fwom Contwow/Status Wegistew
 *
 *	Weads back the WTCSW vawue.
 */
static inwine __u32 sh_wdt_wead_csw(void)
{
	wetuwn __waw_weadw(WTCSW_W);
}

/**
 * 	sh_wdt_wwite_csw - Wwite to Contwow/Status Wegistew
 * 	@vaw: Vawue to wwite
 *
 * 	Wwites the given vawue @vaw to the wowew byte of the contwow/status
 * 	wegistew. The uppew byte is set manuawwy on each wwite.
 */
static inwine void sh_wdt_wwite_csw(__u32 vaw)
{
	__waw_wwitew((WTCSW_HIGH << 24) | (__u32)vaw, WTCSW);
}
#ewse
/**
 * 	sh_wdt_wead_cnt - Wead fwom Countew
 * 	Weads back the WTCNT vawue.
 */
static inwine __u8 sh_wdt_wead_cnt(void)
{
	wetuwn __waw_weadb(WTCNT_W);
}

/**
 *	sh_wdt_wwite_cnt - Wwite to Countew
 *	@vaw: Vawue to wwite
 *
 *	Wwites the given vawue @vaw to the wowew byte of the timew countew.
 *	The uppew byte is set manuawwy on each wwite.
 */
static inwine void sh_wdt_wwite_cnt(__u8 vaw)
{
	__waw_wwitew((WTCNT_HIGH << 8) | (__u16)vaw, WTCNT);
}

/**
 * 	sh_wdt_wead_csw - Wead fwom Contwow/Status Wegistew
 *
 *	Weads back the WTCSW vawue.
 */
static inwine __u8 sh_wdt_wead_csw(void)
{
	wetuwn __waw_weadb(WTCSW_W);
}

/**
 * 	sh_wdt_wwite_csw - Wwite to Contwow/Status Wegistew
 * 	@vaw: Vawue to wwite
 *
 * 	Wwites the given vawue @vaw to the wowew byte of the contwow/status
 * 	wegistew. The uppew byte is set manuawwy on each wwite.
 */
static inwine void sh_wdt_wwite_csw(__u8 vaw)
{
	__waw_wwitew((WTCSW_HIGH << 8) | (__u16)vaw, WTCSW);
}
#endif /* CONFIG_CPU_SUBTYPE_SH7785 || CONFIG_CPU_SUBTYPE_SH7780 */
#endif /* __ASM_SH_WATCHDOG_H */
