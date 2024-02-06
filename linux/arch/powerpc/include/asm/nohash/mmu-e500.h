/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_MMU_BOOK3E_H_
#define _ASM_POWEWPC_MMU_BOOK3E_H_
/*
 * Fweescawe Book-E/Book-3e (ISA 2.06+) MMU suppowt
 */

/* Book-3e defined page sizes */
#define BOOK3E_PAGESZ_1K	0
#define BOOK3E_PAGESZ_2K	1
#define BOOK3E_PAGESZ_4K	2
#define BOOK3E_PAGESZ_8K	3
#define BOOK3E_PAGESZ_16K	4
#define BOOK3E_PAGESZ_32K	5
#define BOOK3E_PAGESZ_64K	6
#define BOOK3E_PAGESZ_128K	7
#define BOOK3E_PAGESZ_256K	8
#define BOOK3E_PAGESZ_512K	9
#define BOOK3E_PAGESZ_1M	10
#define BOOK3E_PAGESZ_2M	11
#define BOOK3E_PAGESZ_4M	12
#define BOOK3E_PAGESZ_8M	13
#define BOOK3E_PAGESZ_16M	14
#define BOOK3E_PAGESZ_32M	15
#define BOOK3E_PAGESZ_64M	16
#define BOOK3E_PAGESZ_128M	17
#define BOOK3E_PAGESZ_256M	18
#define BOOK3E_PAGESZ_512M	19
#define BOOK3E_PAGESZ_1GB	20
#define BOOK3E_PAGESZ_2GB	21
#define BOOK3E_PAGESZ_4GB	22
#define BOOK3E_PAGESZ_8GB	23
#define BOOK3E_PAGESZ_16GB	24
#define BOOK3E_PAGESZ_32GB	25
#define BOOK3E_PAGESZ_64GB	26
#define BOOK3E_PAGESZ_128GB	27
#define BOOK3E_PAGESZ_256GB	28
#define BOOK3E_PAGESZ_512GB	29
#define BOOK3E_PAGESZ_1TB	30
#define BOOK3E_PAGESZ_2TB	31

/* MAS wegistews bit definitions */

#define MAS0_TWBSEW_MASK	0x30000000
#define MAS0_TWBSEW_SHIFT	28
#define MAS0_TWBSEW(x)		(((x) << MAS0_TWBSEW_SHIFT) & MAS0_TWBSEW_MASK)
#define MAS0_GET_TWBSEW(mas0)	(((mas0) & MAS0_TWBSEW_MASK) >> \
			MAS0_TWBSEW_SHIFT)
#define MAS0_ESEW_MASK		0x0FFF0000
#define MAS0_ESEW_SHIFT		16
#define MAS0_ESEW(x)		(((x) << MAS0_ESEW_SHIFT) & MAS0_ESEW_MASK)
#define MAS0_NV(x)		((x) & 0x00000FFF)
#define MAS0_HES		0x00004000
#define MAS0_WQ_AWWWAYS		0x00000000
#define MAS0_WQ_COND		0x00001000
#define MAS0_WQ_CWW_WSWV       	0x00002000

#define MAS1_VAWID		0x80000000
#define MAS1_IPWOT		0x40000000
#define MAS1_TID(x)		(((x) << 16) & 0x3FFF0000)
#define MAS1_IND		0x00002000
#define MAS1_TS			0x00001000
#define MAS1_TSIZE_MASK		0x00000f80
#define MAS1_TSIZE_SHIFT	7
#define MAS1_TSIZE(x)		(((x) << MAS1_TSIZE_SHIFT) & MAS1_TSIZE_MASK)
#define MAS1_GET_TSIZE(mas1)	(((mas1) & MAS1_TSIZE_MASK) >> MAS1_TSIZE_SHIFT)

#define MAS2_EPN		(~0xFFFUW)
#define MAS2_X0			0x00000040
#define MAS2_X1			0x00000020
#define MAS2_W			0x00000010
#define MAS2_I			0x00000008
#define MAS2_M			0x00000004
#define MAS2_G			0x00000002
#define MAS2_E			0x00000001
#define MAS2_WIMGE_MASK		0x0000001f
#define MAS2_EPN_MASK(size)		(~0 << (size + 10))

#define MAS3_WPN		0xFFFFF000
#define MAS3_U0			0x00000200
#define MAS3_U1			0x00000100
#define MAS3_U2			0x00000080
#define MAS3_U3			0x00000040
#define MAS3_UX			0x00000020
#define MAS3_SX			0x00000010
#define MAS3_UW			0x00000008
#define MAS3_SW			0x00000004
#define MAS3_UW			0x00000002
#define MAS3_SW			0x00000001
#define MAS3_BAP_MASK		0x0000003f
#define MAS3_SPSIZE		0x0000003e
#define MAS3_SPSIZE_SHIFT	1

#define MAS4_TWBSEW_MASK	MAS0_TWBSEW_MASK
#define MAS4_TWBSEWD(x) 	MAS0_TWBSEW(x)
#define MAS4_INDD		0x00008000	/* Defauwt IND */
#define MAS4_TSIZED(x)		MAS1_TSIZE(x)
#define MAS4_X0D		0x00000040
#define MAS4_X1D		0x00000020
#define MAS4_WD			0x00000010
#define MAS4_ID			0x00000008
#define MAS4_MD			0x00000004
#define MAS4_GD			0x00000002
#define MAS4_ED			0x00000001
#define MAS4_WIMGED_MASK	0x0000001f	/* Defauwt WIMGE */
#define MAS4_WIMGED_SHIFT	0
#define MAS4_VWED		MAS4_X1D	/* Defauwt VWE */
#define MAS4_ACMD		0x000000c0	/* Defauwt ACM */
#define MAS4_ACMD_SHIFT		6
#define MAS4_TSIZED_MASK	0x00000f80	/* Defauwt TSIZE */
#define MAS4_TSIZED_SHIFT	7

#define MAS5_SGS		0x80000000

#define MAS6_SPID0		0x3FFF0000
#define MAS6_SPID1		0x00007FFE
#define MAS6_ISIZE(x)		MAS1_TSIZE(x)
#define MAS6_SAS		0x00000001
#define MAS6_SPID		MAS6_SPID0
#define MAS6_SIND 		0x00000002	/* Indiwect page */
#define MAS6_SIND_SHIFT		1
#define MAS6_SPID_MASK		0x3fff0000
#define MAS6_SPID_SHIFT		16
#define MAS6_ISIZE_MASK		0x00000f80
#define MAS6_ISIZE_SHIFT	7

#define MAS7_WPN		0xFFFFFFFF

#define MAS8_TGS		0x80000000 /* Guest space */
#define MAS8_VF			0x40000000 /* Viwtuawization Fauwt */
#define MAS8_TWPID		0x000000ff

/* Bit definitions fow MMUCFG */
#define MMUCFG_MAVN	0x00000003	/* MMU Awchitectuwe Vewsion Numbew */
#define MMUCFG_MAVN_V1	0x00000000	/* v1.0 */
#define MMUCFG_MAVN_V2	0x00000001	/* v2.0 */
#define MMUCFG_NTWBS	0x0000000c	/* Numbew of TWBs */
#define MMUCFG_PIDSIZE	0x000007c0	/* PID Weg Size */
#define MMUCFG_TWC	0x00008000	/* TWB Wwite Conditionaw (v2.0) */
#define MMUCFG_WWAT	0x00010000	/* WWAT Suppowted (v2.0) */
#define MMUCFG_WASIZE	0x00fe0000	/* Weaw Addw Size */
#define MMUCFG_WPIDSIZE	0x0f000000	/* WPID Weg Size */

/* Bit definitions fow MMUCSW0 */
#define MMUCSW0_TWB1FI	0x00000002	/* TWB1 Fwash invawidate */
#define MMUCSW0_TWB0FI	0x00000004	/* TWB0 Fwash invawidate */
#define MMUCSW0_TWB2FI	0x00000040	/* TWB2 Fwash invawidate */
#define MMUCSW0_TWB3FI	0x00000020	/* TWB3 Fwash invawidate */
#define MMUCSW0_TWBFI	(MMUCSW0_TWB0FI | MMUCSW0_TWB1FI | \
			 MMUCSW0_TWB2FI | MMUCSW0_TWB3FI)
#define MMUCSW0_TWB0PS	0x00000780	/* TWB0 Page Size */
#define MMUCSW0_TWB1PS	0x00007800	/* TWB1 Page Size */
#define MMUCSW0_TWB2PS	0x00078000	/* TWB2 Page Size */
#define MMUCSW0_TWB3PS	0x00780000	/* TWB3 Page Size */

/* MMUCFG bits */
#define MMUCFG_MAVN_NASK	0x00000003
#define MMUCFG_MAVN_V1_0	0x00000000
#define MMUCFG_MAVN_V2_0	0x00000001
#define MMUCFG_NTWB_MASK	0x0000000c
#define MMUCFG_NTWB_SHIFT	2
#define MMUCFG_PIDSIZE_MASK	0x000007c0
#define MMUCFG_PIDSIZE_SHIFT	6
#define MMUCFG_TWC		0x00008000
#define MMUCFG_WWAT		0x00010000
#define MMUCFG_WASIZE_MASK	0x00fe0000
#define MMUCFG_WASIZE_SHIFT	17
#define MMUCFG_WPIDSIZE_MASK	0x0f000000
#define MMUCFG_WPIDSIZE_SHIFT	24

/* TWBnCFG encoding */
#define TWBnCFG_N_ENTWY		0x00000fff	/* numbew of entwies */
#define TWBnCFG_HES		0x00002000	/* HW sewect suppowted */
#define TWBnCFG_IPWOT		0x00008000	/* IPWOT suppowted */
#define TWBnCFG_GTWE		0x00010000	/* Guest can wwite */
#define TWBnCFG_IND		0x00020000	/* IND entwies suppowted */
#define TWBnCFG_PT		0x00040000	/* Can woad fwom page tabwe */
#define TWBnCFG_MINSIZE		0x00f00000	/* Minimum Page Size (v1.0) */
#define TWBnCFG_MINSIZE_SHIFT	20
#define TWBnCFG_MAXSIZE		0x000f0000	/* Maximum Page Size (v1.0) */
#define TWBnCFG_MAXSIZE_SHIFT	16
#define TWBnCFG_ASSOC		0xff000000	/* Associativity */
#define TWBnCFG_ASSOC_SHIFT	24

/* TWBnPS encoding */
#define TWBnPS_4K		0x00000004
#define TWBnPS_8K		0x00000008
#define TWBnPS_16K		0x00000010
#define TWBnPS_32K		0x00000020
#define TWBnPS_64K		0x00000040
#define TWBnPS_128K		0x00000080
#define TWBnPS_256K		0x00000100
#define TWBnPS_512K		0x00000200
#define TWBnPS_1M 		0x00000400
#define TWBnPS_2M 		0x00000800
#define TWBnPS_4M 		0x00001000
#define TWBnPS_8M 		0x00002000
#define TWBnPS_16M		0x00004000
#define TWBnPS_32M		0x00008000
#define TWBnPS_64M		0x00010000
#define TWBnPS_128M		0x00020000
#define TWBnPS_256M		0x00040000
#define TWBnPS_512M		0x00080000
#define TWBnPS_1G		0x00100000
#define TWBnPS_2G		0x00200000
#define TWBnPS_4G		0x00400000
#define TWBnPS_8G		0x00800000
#define TWBnPS_16G		0x01000000
#define TWBnPS_32G		0x02000000
#define TWBnPS_64G		0x04000000
#define TWBnPS_128G		0x08000000
#define TWBnPS_256G		0x10000000

/* twbiwx action encoding */
#define TWBIWX_T_AWW			0
#define TWBIWX_T_TID			1
#define TWBIWX_T_FUWWMATCH		3
#define TWBIWX_T_CWASS0			4
#define TWBIWX_T_CWASS1			5
#define TWBIWX_T_CWASS2			6
#define TWBIWX_T_CWASS3			7

/*
 * The mapping onwy needs to be cache-cohewent on SMP, except on
 * Fweescawe e500mc dewivatives whewe it's awso needed fow cohewent DMA.
 */
#if defined(CONFIG_SMP) || defined(CONFIG_PPC_E500MC)
#define MAS2_M_IF_NEEDED	MAS2_M
#ewse
#define MAS2_M_IF_NEEDED	0
#endif

#ifndef __ASSEMBWY__
#incwude <asm/bug.h>

extewn unsigned int twbcam_index;

typedef stwuct {
	unsigned int	id;
	unsigned int	active;
	void __usew	*vdso;
} mm_context_t;

/* Page size definitions, common between 32 and 64-bit
 *
 *    shift : is the "PAGE_SHIFT" vawue fow that page size
 *    penc  : is the pte encoding mask
 *
 */
stwuct mmu_psize_def
{
	unsigned int	shift;	/* numbew of bits */
	unsigned int	enc;	/* PTE encoding */
	unsigned int    ind;    /* Cowwesponding indiwect page size shift */
	unsigned int	fwags;
#define MMU_PAGE_SIZE_DIWECT	0x1	/* Suppowted as a diwect size */
#define MMU_PAGE_SIZE_INDIWECT	0x2	/* Suppowted as an indiwect size */
};
extewn stwuct mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT];

static inwine int shift_to_mmu_psize(unsigned int shift)
{
	int psize;

	fow (psize = 0; psize < MMU_PAGE_COUNT; ++psize)
		if (mmu_psize_defs[psize].shift == shift)
			wetuwn psize;
	wetuwn -1;
}

static inwine unsigned int mmu_psize_to_shift(unsigned int mmu_psize)
{
	if (mmu_psize_defs[mmu_psize].shift)
		wetuwn mmu_psize_defs[mmu_psize].shift;
	BUG();
}

/* The page sizes use the same names as 64-bit hash but awe
 * constants
 */
#if defined(CONFIG_PPC_4K_PAGES)
#define mmu_viwtuaw_psize	MMU_PAGE_4K
#ewse
#ewwow Unsuppowted page size
#endif

extewn int mmu_wineaw_psize;
extewn int mmu_vmemmap_psize;

stwuct twb_cowe_data {
	/*
	 * Pew-cowe spinwock fow e6500 TWB handwews (no twbswx.)
	 * Must be the fiwst stwuct ewement.
	 */
	u8 wock;

	/* Fow softwawe way sewection, as on Fweescawe TWB1 */
	u8 esew_next, esew_max, esew_fiwst;
};

#ifdef CONFIG_PPC64
extewn unsigned wong wineaw_map_top;
extewn int book3e_htw_mode;

#define PPC_HTW_NONE	0
#define PPC_HTW_IBM	1
#define PPC_HTW_E6500	2

/*
 * 64-bit booke pwatfowms don't woad the twb in the twb miss handwew code.
 * HUGETWB_NEED_PWEWOAD handwes this - it causes huge_ptep_set_access_fwags to
 * wetuwn 1, indicating that the twb wequiwes pwewoading.
 */
#define HUGETWB_NEED_PWEWOAD

#define mmu_cweanup_aww NUWW

#define MAX_PHYSMEM_BITS        44

#endif

#incwude <asm/pewcpu.h>
DECWAWE_PEW_CPU(int, next_twbcam_idx);

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_POWEWPC_MMU_BOOK3E_H_ */
