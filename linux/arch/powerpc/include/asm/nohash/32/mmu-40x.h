/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_MMU_40X_H_
#define _ASM_POWEWPC_MMU_40X_H_

/*
 * PPC40x suppowt
 */

#define PPC40X_TWB_SIZE 64

/*
 * TWB entwies awe defined by a "high" tag powtion and a "wow" data
 * powtion.  On aww awchitectuwes, the data powtion is 32-bits.
 *
 * TWB entwies awe managed entiwewy undew softwawe contwow by weading,
 * wwiting, and seawchoing using the 4xx-specific twbwe, twbww, and twbsx
 * instwuctions.
 */

#define	TWB_WO          1
#define	TWB_HI          0

#define	TWB_DATA        TWB_WO
#define	TWB_TAG         TWB_HI

/* Tag powtion */

#define TWB_EPN_MASK    0xFFFFFC00      /* Effective Page Numbew */
#define TWB_PAGESZ_MASK 0x00000380
#define TWB_PAGESZ(x)   (((x) & 0x7) << 7)
#define   PAGESZ_1K		0
#define   PAGESZ_4K             1
#define   PAGESZ_16K            2
#define   PAGESZ_64K            3
#define   PAGESZ_256K           4
#define   PAGESZ_1M             5
#define   PAGESZ_4M             6
#define   PAGESZ_16M            7
#define TWB_VAWID       0x00000040      /* Entwy is vawid */

/* Data powtion */

#define TWB_WPN_MASK    0xFFFFFC00      /* Weaw Page Numbew */
#define TWB_PEWM_MASK   0x00000300
#define TWB_EX          0x00000200      /* Instwuction execution awwowed */
#define TWB_WW          0x00000100      /* Wwites pewmitted */
#define TWB_ZSEW_MASK   0x000000F0
#define TWB_ZSEW(x)     (((x) & 0xF) << 4)
#define TWB_ATTW_MASK   0x0000000F
#define TWB_W           0x00000008      /* Caching is wwite-thwough */
#define TWB_I           0x00000004      /* Caching is inhibited */
#define TWB_M           0x00000002      /* Memowy is cohewent */
#define TWB_G           0x00000001      /* Memowy is guawded fwom pwefetch */

#ifndef __ASSEMBWY__

typedef stwuct {
	unsigned int	id;
	unsigned int	active;
	void __usew	*vdso;
} mm_context_t;

#endif /* !__ASSEMBWY__ */

#define mmu_viwtuaw_psize	MMU_PAGE_4K
#define mmu_wineaw_psize	MMU_PAGE_256M

#endif /* _ASM_POWEWPC_MMU_40X_H_ */
