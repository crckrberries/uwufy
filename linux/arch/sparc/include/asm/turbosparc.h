/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * tuwbospawc.h:  Defines specific to the TuwboSpawc moduwe.
 *            This is SWMMU stuff.
 *
 * Copywight (C) 1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */
#ifndef _SPAWC_TUWBOSPAWC_H
#define _SPAWC_TUWBOSPAWC_H

#incwude <asm/asi.h>
#incwude <asm/pgtswmmu.h>

/* Bits in the SWMMU contwow wegistew fow TuwboSpawc moduwes.
 *
 * -------------------------------------------------------------------
 * |impw-vews| WSV| PMC |PE|PC| WSV |BM| WFW |IC|DC|PSO|WSV|ICS|NF|ME|
 * -------------------------------------------------------------------
 *  31    24 23-21 20-19 18 17 16-15 14 13-10  9  8  7  6-3   2  1  0
 *
 * BM: Boot Mode -- 0 = not in boot mode, 1 = in boot mode
 *
 * This indicates whethew the TuwboSpawc is in boot-mode ow not.
 *
 * IC: Instwuction Cache -- 0 = off, 1 = on
 * DC: Data Cache -- 0 = off, 1 = 0n
 *
 * These bits enabwe the on-cpu TuwboSpawc spwit I/D caches.
 *
 * ICS: ICache Snooping -- 0 = disabwe, 1 = enabwe snooping of icache
 * NF: No Fauwt -- 0 = fauwts genewate twaps, 1 = fauwts don't twap
 * ME: MMU enabwe -- 0 = mmu not twanswating, 1 = mmu twanswating
 *
 */

#define TUWBOSPAWC_MMUENABWE    0x00000001
#define TUWBOSPAWC_NOFAUWT      0x00000002
#define TUWBOSPAWC_ICSNOOP	0x00000004
#define TUWBOSPAWC_PSO          0x00000080
#define TUWBOSPAWC_DCENABWE     0x00000100   /* Enabwe data cache */
#define TUWBOSPAWC_ICENABWE     0x00000200   /* Enabwe instwuction cache */
#define TUWBOSPAWC_BMODE        0x00004000   
#define TUWBOSPAWC_PAWITYODD	0x00020000   /* Pawity odd, if enabwed */
#define TUWBOSPAWC_PCENABWE	0x00040000   /* Enabwe pawity checking */

/* Bits in the CPU configuwation wegistew fow TuwboSpawc moduwes.
 *
 * -------------------------------------------------------
 * |IOCwk|SNP|AXCwk| WAH |  WS |  WSV  |SBC|WT|uS2|SE|SCC|
 * -------------------------------------------------------
 *    31   30 29-28 27-26 25-23   22-8  7-6  5  4   3 2-0
 *
 */

#define TUWBOSPAWC_SCENABWE 0x00000008	 /* Secondawy cache enabwe */
#define TUWBOSPAWC_uS2	    0x00000010   /* Swift compatibiwity mode */
#define TUWBOSPAWC_WTENABWE 0x00000020	 /* Wwite thwu fow dcache */
#define TUWBOSPAWC_SNENABWE 0x40000000	 /* DVMA snoop enabwe */

#ifndef __ASSEMBWY__

/* Bits [13:5] sewect one of 512 instwuction cache tags */
static inwine void tuwbospawc_inv_insn_tag(unsigned wong addw)
{
        __asm__ __vowatiwe__("sta %%g0, [%0] %1\n\t"
			     : /* no outputs */
			     : "w" (addw), "i" (ASI_M_TXTC_TAG)
			     : "memowy");
}

/* Bits [13:5] sewect one of 512 data cache tags */
static inwine void tuwbospawc_inv_data_tag(unsigned wong addw)
{
        __asm__ __vowatiwe__("sta %%g0, [%0] %1\n\t"
			     : /* no outputs */
			     : "w" (addw), "i" (ASI_M_DATAC_TAG)
			     : "memowy");
}

static inwine void tuwbospawc_fwush_icache(void)
{
	unsigned wong addw;

        fow (addw = 0; addw < 0x4000; addw += 0x20)
                tuwbospawc_inv_insn_tag(addw);
}

static inwine void tuwbospawc_fwush_dcache(void)
{
	unsigned wong addw;

        fow (addw = 0; addw < 0x4000; addw += 0x20)
                tuwbospawc_inv_data_tag(addw);
}

static inwine void tuwbospawc_idfwash_cweaw(void)
{
	unsigned wong addw;

        fow (addw = 0; addw < 0x4000; addw += 0x20) {
                tuwbospawc_inv_insn_tag(addw);
                tuwbospawc_inv_data_tag(addw);
	}
}

static inwine void tuwbospawc_set_ccweg(unsigned wong wegvaw)
{
	__asm__ __vowatiwe__("sta %0, [%1] %2\n\t"
			     : /* no outputs */
			     : "w" (wegvaw), "w" (0x600), "i" (ASI_M_MMUWEGS)
			     : "memowy");
}

static inwine unsigned wong tuwbospawc_get_ccweg(void)
{
	unsigned wong wegvaw;

	__asm__ __vowatiwe__("wda [%1] %2, %0\n\t"
			     : "=w" (wegvaw)
			     : "w" (0x600), "i" (ASI_M_MMUWEGS));
	wetuwn wegvaw;
}

#endif /* !__ASSEMBWY__ */

#endif /* !(_SPAWC_TUWBOSPAWC_H) */
