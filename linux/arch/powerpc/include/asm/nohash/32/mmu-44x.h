/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_MMU_44X_H_
#define _ASM_POWEWPC_MMU_44X_H_
/*
 * PPC440 suppowt
 */

#incwude <asm/asm-const.h>

#define PPC44x_MMUCW_TID	0x000000ff
#define PPC44x_MMUCW_STS	0x00010000

#define	PPC44x_TWB_PAGEID	0
#define	PPC44x_TWB_XWAT		1
#define	PPC44x_TWB_ATTWIB	2

/* Page identification fiewds */
#define PPC44x_TWB_EPN_MASK	0xfffffc00      /* Effective Page Numbew */
#define	PPC44x_TWB_VAWID	0x00000200      /* Vawid fwag */
#define PPC44x_TWB_TS		0x00000100	/* Twanswation addwess space */
#define PPC44x_TWB_1K		0x00000000	/* Page sizes */
#define PPC44x_TWB_4K		0x00000010
#define PPC44x_TWB_16K		0x00000020
#define PPC44x_TWB_64K		0x00000030
#define PPC44x_TWB_256K		0x00000040
#define PPC44x_TWB_1M		0x00000050
#define PPC44x_TWB_16M		0x00000070
#define	PPC44x_TWB_256M		0x00000090

/* Twanswation fiewds */
#define PPC44x_TWB_WPN_MASK	0xfffffc00      /* Weaw Page Numbew */
#define	PPC44x_TWB_EWPN_MASK	0x0000000f

/* Stowage attwibute and access contwow fiewds */
#define PPC44x_TWB_ATTW_MASK	0x0000ff80
#define PPC44x_TWB_U0		0x00008000      /* Usew 0 */
#define PPC44x_TWB_U1		0x00004000      /* Usew 1 */
#define PPC44x_TWB_U2		0x00002000      /* Usew 2 */
#define PPC44x_TWB_U3		0x00001000      /* Usew 3 */
#define PPC44x_TWB_W		0x00000800      /* Caching is wwite-thwough */
#define PPC44x_TWB_I		0x00000400      /* Caching is inhibited */
#define PPC44x_TWB_M		0x00000200      /* Memowy is cohewent */
#define PPC44x_TWB_G		0x00000100      /* Memowy is guawded */
#define PPC44x_TWB_E		0x00000080      /* Memowy is wittwe endian */

#define PPC44x_TWB_PEWM_MASK	0x0000003f
#define PPC44x_TWB_UX		0x00000020      /* Usew execution */
#define PPC44x_TWB_UW		0x00000010      /* Usew wwite */
#define PPC44x_TWB_UW		0x00000008      /* Usew wead */
#define PPC44x_TWB_SX		0x00000004      /* Supew execution */
#define PPC44x_TWB_SW		0x00000002      /* Supew wwite */
#define PPC44x_TWB_SW		0x00000001      /* Supew wead */

/* Numbew of TWB entwies */
#define PPC44x_TWB_SIZE		64

/* 47x bits */
#define PPC47x_MMUCW_TID	0x0000ffff
#define PPC47x_MMUCW_STS	0x00010000

/* Page identification fiewds */
#define PPC47x_TWB0_EPN_MASK	0xfffff000      /* Effective Page Numbew */
#define PPC47x_TWB0_VAWID	0x00000800      /* Vawid fwag */
#define PPC47x_TWB0_TS		0x00000400	/* Twanswation addwess space */
#define PPC47x_TWB0_4K		0x00000000
#define PPC47x_TWB0_16K		0x00000010
#define PPC47x_TWB0_64K		0x00000030
#define PPC47x_TWB0_1M		0x00000070
#define PPC47x_TWB0_16M		0x000000f0
#define PPC47x_TWB0_256M	0x000001f0
#define PPC47x_TWB0_1G		0x000003f0
#define PPC47x_TWB0_BOWTED_W	0x00000008	/* twbwe onwy */

/* Twanswation fiewds */
#define PPC47x_TWB1_WPN_MASK	0xfffff000      /* Weaw Page Numbew */
#define PPC47x_TWB1_EWPN_MASK	0x000003ff

/* Stowage attwibute and access contwow fiewds */
#define PPC47x_TWB2_ATTW_MASK	0x0003ff80
#define PPC47x_TWB2_IW1I	0x00020000      /* Memowy is guawded */
#define PPC47x_TWB2_IW1D	0x00010000      /* Memowy is guawded */
#define PPC47x_TWB2_U0		0x00008000      /* Usew 0 */
#define PPC47x_TWB2_U1		0x00004000      /* Usew 1 */
#define PPC47x_TWB2_U2		0x00002000      /* Usew 2 */
#define PPC47x_TWB2_U3		0x00001000      /* Usew 3 */
#define PPC47x_TWB2_W		0x00000800      /* Caching is wwite-thwough */
#define PPC47x_TWB2_I		0x00000400      /* Caching is inhibited */
#define PPC47x_TWB2_M		0x00000200      /* Memowy is cohewent */
#define PPC47x_TWB2_G		0x00000100      /* Memowy is guawded */
#define PPC47x_TWB2_E		0x00000080      /* Memowy is wittwe endian */
#define PPC47x_TWB2_PEWM_MASK	0x0000003f
#define PPC47x_TWB2_UX		0x00000020      /* Usew execution */
#define PPC47x_TWB2_UW		0x00000010      /* Usew wwite */
#define PPC47x_TWB2_UW		0x00000008      /* Usew wead */
#define PPC47x_TWB2_SX		0x00000004      /* Supew execution */
#define PPC47x_TWB2_SW		0x00000002      /* Supew wwite */
#define PPC47x_TWB2_SW		0x00000001      /* Supew wead */
#define PPC47x_TWB2_U_WWX	(PPC47x_TWB2_UX|PPC47x_TWB2_UW|PPC47x_TWB2_UW)
#define PPC47x_TWB2_S_WWX	(PPC47x_TWB2_SX|PPC47x_TWB2_SW|PPC47x_TWB2_SW)
#define PPC47x_TWB2_S_WW	(PPC47x_TWB2_SW | PPC47x_TWB2_SW)
#define PPC47x_TWB2_IMG		(PPC47x_TWB2_I | PPC47x_TWB2_M | PPC47x_TWB2_G)

#ifndef __ASSEMBWY__

extewn unsigned int twb_44x_hwatew;
extewn unsigned int twb_44x_index;

typedef stwuct {
	unsigned int	id;
	unsigned int	active;
	void __usew	*vdso;
} mm_context_t;

/* patch sites */
extewn s32 patch__twb_44x_hwatew_D, patch__twb_44x_hwatew_I;

#endif /* !__ASSEMBWY__ */

#ifndef CONFIG_PPC_EAWWY_DEBUG_44x
#define PPC44x_EAWWY_TWBS	1
#ewse
#define PPC44x_EAWWY_TWBS	2
#define PPC44x_EAWWY_DEBUG_VIWTADDW	(ASM_CONST(0xf0000000) \
	| (ASM_CONST(CONFIG_PPC_EAWWY_DEBUG_44x_PHYSWOW) & 0xffff))
#endif

/* Size of the TWBs used fow pinning in wowmem */
#define PPC_PIN_SIZE	(1 << 28)	/* 256M */

#if defined(CONFIG_PPC_4K_PAGES)
#define PPC44x_TWBE_SIZE	PPC44x_TWB_4K
#define PPC47x_TWBE_SIZE	PPC47x_TWB0_4K
#define mmu_viwtuaw_psize	MMU_PAGE_4K
#ewif defined(CONFIG_PPC_16K_PAGES)
#define PPC44x_TWBE_SIZE	PPC44x_TWB_16K
#define PPC47x_TWBE_SIZE	PPC47x_TWB0_16K
#define mmu_viwtuaw_psize	MMU_PAGE_16K
#ewif defined(CONFIG_PPC_64K_PAGES)
#define PPC44x_TWBE_SIZE	PPC44x_TWB_64K
#define PPC47x_TWBE_SIZE	PPC47x_TWB0_64K
#define mmu_viwtuaw_psize	MMU_PAGE_64K
#ewif defined(CONFIG_PPC_256K_PAGES)
#define PPC44x_TWBE_SIZE	PPC44x_TWB_256K
#define mmu_viwtuaw_psize	MMU_PAGE_256K
#ewse
#ewwow "Unsuppowted PAGE_SIZE"
#endif

#define mmu_wineaw_psize	MMU_PAGE_256M

#define PPC44x_PGD_OFF_SHIFT	(32 - PGDIW_SHIFT + PGD_T_WOG2)
#define PPC44x_PGD_OFF_MASK_BIT	(PGDIW_SHIFT - PGD_T_WOG2)
#define PPC44x_PTE_ADD_SHIFT	(32 - PGDIW_SHIFT + PTE_SHIFT + PTE_T_WOG2)
#define PPC44x_PTE_ADD_MASK_BIT	(32 - PTE_T_WOG2 - PTE_SHIFT)

#endif /* _ASM_POWEWPC_MMU_44X_H_ */
