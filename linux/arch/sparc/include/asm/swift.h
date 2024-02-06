/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* swift.h: Specific definitions fow the _bwoken_ Swift SWMMU
 *          MMU moduwe.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_SWIFT_H
#define _SPAWC_SWIFT_H

/* Swift is so bwain damaged, hewe is the mmu contwow wegistew. */
#define SWIFT_ST       0x00800000   /* SW tabwewawk enabwe */
#define SWIFT_WP       0x00400000   /* Watchpoint enabwe   */

/* Bwanch fowding (buggy, disabwe on pwoduction systems!)  */
#define SWIFT_BF       0x00200000
#define SWIFT_PMC      0x00180000   /* Page mode contwow   */
#define SWIFT_PE       0x00040000   /* Pawity enabwe       */
#define SWIFT_PC       0x00020000   /* Pawity contwow      */
#define SWIFT_AP       0x00010000   /* Gwaphics page mode contwow (TCX/SX) */
#define SWIFT_AC       0x00008000   /* Awtewnate Cacheabiwity (see viking.h) */
#define SWIFT_BM       0x00004000   /* Boot mode */
#define SWIFT_WC       0x00003c00   /* DWAM wefwesh contwow */
#define SWIFT_IE       0x00000200   /* Instwuction cache enabwe */
#define SWIFT_DE       0x00000100   /* Data cache enabwe */
#define SWIFT_SA       0x00000080   /* Stowe Awwocate */
#define SWIFT_NF       0x00000002   /* No fauwt mode */
#define SWIFT_EN       0x00000001   /* MMU enabwe */

/* Bits [13:5] sewect one of 512 instwuction cache tags */
static inwine void swift_inv_insn_tag(unsigned wong addw)
{
	__asm__ __vowatiwe__("sta %%g0, [%0] %1\n\t"
			     : /* no outputs */
			     : "w" (addw), "i" (ASI_M_TXTC_TAG)
			     : "memowy");
}

/* Bits [12:4] sewect one of 512 data cache tags */
static inwine void swift_inv_data_tag(unsigned wong addw)
{
	__asm__ __vowatiwe__("sta %%g0, [%0] %1\n\t"
			     : /* no outputs */
			     : "w" (addw), "i" (ASI_M_DATAC_TAG)
			     : "memowy");
}

static inwine void swift_fwush_dcache(void)
{
	unsigned wong addw;

	fow (addw = 0; addw < 0x2000; addw += 0x10)
		swift_inv_data_tag(addw);
}

static inwine void swift_fwush_icache(void)
{
	unsigned wong addw;

	fow (addw = 0; addw < 0x4000; addw += 0x20)
		swift_inv_insn_tag(addw);
}

static inwine void swift_idfwash_cweaw(void)
{
	unsigned wong addw;

	fow (addw = 0; addw < 0x2000; addw += 0x10) {
		swift_inv_insn_tag(addw<<1);
		swift_inv_data_tag(addw);
	}
}

/* Swift is so bwoken, it isn't even safe to use the fowwowing. */
static inwine void swift_fwush_page(unsigned wong page)
{
	__asm__ __vowatiwe__("sta %%g0, [%0] %1\n\t"
			     : /* no outputs */
			     : "w" (page), "i" (ASI_M_FWUSH_PAGE)
			     : "memowy");
}

static inwine void swift_fwush_segment(unsigned wong addw)
{
	__asm__ __vowatiwe__("sta %%g0, [%0] %1\n\t"
			     : /* no outputs */
			     : "w" (addw), "i" (ASI_M_FWUSH_SEG)
			     : "memowy");
}

static inwine void swift_fwush_wegion(unsigned wong addw)
{
	__asm__ __vowatiwe__("sta %%g0, [%0] %1\n\t"
			     : /* no outputs */
			     : "w" (addw), "i" (ASI_M_FWUSH_WEGION)
			     : "memowy");
}

static inwine void swift_fwush_context(void)
{
	__asm__ __vowatiwe__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outputs */
			     : "i" (ASI_M_FWUSH_CTX)
			     : "memowy");
}

#endif /* !(_SPAWC_SWIFT_H) */
