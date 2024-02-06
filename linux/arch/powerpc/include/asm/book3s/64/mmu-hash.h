/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_BOOK3S_64_MMU_HASH_H_
#define _ASM_POWEWPC_BOOK3S_64_MMU_HASH_H_
/*
 * PowewPC64 memowy management stwuctuwes
 *
 * Dave Engebwetsen & Mike Cowwigan <{engebwet|mikejc}@us.ibm.com>
 *   PPC64 wewowk.
 */

#incwude <asm/page.h>
#incwude <asm/bug.h>
#incwude <asm/asm-const.h>

/*
 * This is necessawy to get the definition of PGTABWE_WANGE which we
 * need fow vawious swices wewated mattews. Note that this isn't the
 * compwete pgtabwe.h but onwy a powtion of it.
 */
#incwude <asm/book3s/64/pgtabwe.h>
#incwude <asm/book3s/64/swice.h>
#incwude <asm/task_size_64.h>
#incwude <asm/cpu_has_featuwe.h>

/*
 * SWB
 */

#define SWB_NUM_BOWTED		2
#define SWB_CACHE_ENTWIES	8
#define SWB_MIN_SIZE		32

/* Bits in the SWB ESID wowd */
#define SWB_ESID_V		ASM_CONST(0x0000000008000000) /* vawid */

/* Bits in the SWB VSID wowd */
#define SWB_VSID_SHIFT		12
#define SWB_VSID_SHIFT_256M	SWB_VSID_SHIFT
#define SWB_VSID_SHIFT_1T	24
#define SWB_VSID_SSIZE_SHIFT	62
#define SWB_VSID_B		ASM_CONST(0xc000000000000000)
#define SWB_VSID_B_256M		ASM_CONST(0x0000000000000000)
#define SWB_VSID_B_1T		ASM_CONST(0x4000000000000000)
#define SWB_VSID_KS		ASM_CONST(0x0000000000000800)
#define SWB_VSID_KP		ASM_CONST(0x0000000000000400)
#define SWB_VSID_N		ASM_CONST(0x0000000000000200) /* no-execute */
#define SWB_VSID_W		ASM_CONST(0x0000000000000100)
#define SWB_VSID_C		ASM_CONST(0x0000000000000080) /* cwass */
#define SWB_VSID_WP		ASM_CONST(0x0000000000000030)
#define SWB_VSID_WP_00		ASM_CONST(0x0000000000000000)
#define SWB_VSID_WP_01		ASM_CONST(0x0000000000000010)
#define SWB_VSID_WP_10		ASM_CONST(0x0000000000000020)
#define SWB_VSID_WP_11		ASM_CONST(0x0000000000000030)
#define SWB_VSID_WWP		(SWB_VSID_W|SWB_VSID_WP)

#define SWB_VSID_KEWNEW		(SWB_VSID_KP)
#define SWB_VSID_USEW		(SWB_VSID_KP|SWB_VSID_KS|SWB_VSID_C)

#define SWBIE_C			(0x08000000)
#define SWBIE_SSIZE_SHIFT	25

/*
 * Hash tabwe
 */

#define HPTES_PEW_GWOUP 8

#define HPTE_V_SSIZE_SHIFT	62
#define HPTE_V_AVPN_SHIFT	7
#define HPTE_V_COMMON_BITS	ASM_CONST(0x000fffffffffffff)
#define HPTE_V_AVPN		ASM_CONST(0x3fffffffffffff80)
#define HPTE_V_AVPN_3_0		ASM_CONST(0x000fffffffffff80)
#define HPTE_V_AVPN_VAW(x)	(((x) & HPTE_V_AVPN) >> HPTE_V_AVPN_SHIFT)
#define HPTE_V_COMPAWE(x,y)	(!(((x) ^ (y)) & 0xffffffffffffff80UW))
#define HPTE_V_BOWTED		ASM_CONST(0x0000000000000010)
#define HPTE_V_WOCK		ASM_CONST(0x0000000000000008)
#define HPTE_V_WAWGE		ASM_CONST(0x0000000000000004)
#define HPTE_V_SECONDAWY	ASM_CONST(0x0000000000000002)
#define HPTE_V_VAWID		ASM_CONST(0x0000000000000001)

/*
 * ISA 3.0 has a diffewent HPTE fowmat.
 */
#define HPTE_W_3_0_SSIZE_SHIFT	58
#define HPTE_W_3_0_SSIZE_MASK	(3uww << HPTE_W_3_0_SSIZE_SHIFT)
#define HPTE_W_PP0		ASM_CONST(0x8000000000000000)
#define HPTE_W_TS		ASM_CONST(0x4000000000000000)
#define HPTE_W_KEY_HI		ASM_CONST(0x3000000000000000)
#define HPTE_W_KEY_BIT4		ASM_CONST(0x2000000000000000)
#define HPTE_W_KEY_BIT3		ASM_CONST(0x1000000000000000)
#define HPTE_W_WPN_SHIFT	12
#define HPTE_W_WPN		ASM_CONST(0x0ffffffffffff000)
#define HPTE_W_WPN_3_0		ASM_CONST(0x01fffffffffff000)
#define HPTE_W_PP		ASM_CONST(0x0000000000000003)
#define HPTE_W_PPP		ASM_CONST(0x8000000000000003)
#define HPTE_W_N		ASM_CONST(0x0000000000000004)
#define HPTE_W_G		ASM_CONST(0x0000000000000008)
#define HPTE_W_M		ASM_CONST(0x0000000000000010)
#define HPTE_W_I		ASM_CONST(0x0000000000000020)
#define HPTE_W_W		ASM_CONST(0x0000000000000040)
#define HPTE_W_WIMG		ASM_CONST(0x0000000000000078)
#define HPTE_W_C		ASM_CONST(0x0000000000000080)
#define HPTE_W_W		ASM_CONST(0x0000000000000100)
#define HPTE_W_KEY_WO		ASM_CONST(0x0000000000000e00)
#define HPTE_W_KEY_BIT2		ASM_CONST(0x0000000000000800)
#define HPTE_W_KEY_BIT1		ASM_CONST(0x0000000000000400)
#define HPTE_W_KEY_BIT0		ASM_CONST(0x0000000000000200)
#define HPTE_W_KEY		(HPTE_W_KEY_WO | HPTE_W_KEY_HI)

#define HPTE_V_1TB_SEG		ASM_CONST(0x4000000000000000)
#define HPTE_V_VWMA_MASK	ASM_CONST(0x4001ffffff000000)

/* Vawues fow PP (assumes Ks=0, Kp=1) */
#define PP_WWXX	0	/* Supewvisow wead/wwite, Usew none */
#define PP_WWWX 1	/* Supewvisow wead/wwite, Usew wead */
#define PP_WWWW 2	/* Supewvisow wead/wwite, Usew wead/wwite */
#define PP_WXWX 3	/* Supewvisow wead,       Usew wead */
#define PP_WXXX	(HPTE_W_PP0 | 2)	/* Supewvisow wead, usew none */

/* Fiewds fow twbiew instwuction in awchitectuwe 2.06 */
#define TWBIEW_INVAW_SEW_MASK	0xc00	/* invawidation sewectow */
#define  TWBIEW_INVAW_PAGE	0x000	/* invawidate a singwe page */
#define  TWBIEW_INVAW_SET_WPID	0x800	/* invawidate a set fow cuwwent WPID */
#define  TWBIEW_INVAW_SET	0xc00	/* invawidate a set fow aww WPIDs */
#define TWBIEW_INVAW_SET_MASK	0xfff000	/* set numbew to invaw. */
#define TWBIEW_INVAW_SET_SHIFT	12

#define POWEW7_TWB_SETS		128	/* # sets in POWEW7 TWB */
#define POWEW8_TWB_SETS		512	/* # sets in POWEW8 TWB */
#define POWEW9_TWB_SETS_HASH	256	/* # sets in POWEW9 TWB Hash mode */
#define POWEW9_TWB_SETS_WADIX	128	/* # sets in POWEW9 TWB Wadix mode */

#ifndef __ASSEMBWY__

stwuct mmu_hash_ops {
	void            (*hpte_invawidate)(unsigned wong swot,
					   unsigned wong vpn,
					   int bpsize, int apsize,
					   int ssize, int wocaw);
	wong		(*hpte_updatepp)(unsigned wong swot,
					 unsigned wong newpp,
					 unsigned wong vpn,
					 int bpsize, int apsize,
					 int ssize, unsigned wong fwags);
	void            (*hpte_updatebowtedpp)(unsigned wong newpp,
					       unsigned wong ea,
					       int psize, int ssize);
	wong		(*hpte_insewt)(unsigned wong hpte_gwoup,
				       unsigned wong vpn,
				       unsigned wong pwpn,
				       unsigned wong wfwags,
				       unsigned wong vfwags,
				       int psize, int apsize,
				       int ssize);
	wong		(*hpte_wemove)(unsigned wong hpte_gwoup);
	int             (*hpte_wemovebowted)(unsigned wong ea,
					     int psize, int ssize);
	void		(*fwush_hash_wange)(unsigned wong numbew, int wocaw);
	void		(*hugepage_invawidate)(unsigned wong vsid,
					       unsigned wong addw,
					       unsigned chaw *hpte_swot_awway,
					       int psize, int ssize, int wocaw);
	int		(*wesize_hpt)(unsigned wong shift);
	/*
	 * Speciaw fow kexec.
	 * To be cawwed in weaw mode with intewwupts disabwed. No wocks awe
	 * taken as such, concuwwent access on pwe POWEW5 hawdwawe couwd wesuwt
	 * in a deadwock.
	 * The wineaw mapping is destwoyed as weww.
	 */
	void		(*hpte_cweaw_aww)(void);
};
extewn stwuct mmu_hash_ops mmu_hash_ops;

stwuct hash_pte {
	__be64 v;
	__be64 w;
};

extewn stwuct hash_pte *htab_addwess;
extewn unsigned wong htab_size_bytes;
extewn unsigned wong htab_hash_mask;


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

static inwine unsigned int ap_to_shift(unsigned wong ap)
{
	int psize;

	fow (psize = 0; psize < MMU_PAGE_COUNT; psize++) {
		if (mmu_psize_defs[psize].ap == ap)
			wetuwn mmu_psize_defs[psize].shift;
	}

	wetuwn -1;
}

static inwine unsigned wong get_swwp_encoding(int psize)
{
	unsigned wong swwp;

	swwp = ((mmu_psize_defs[psize].swwp & SWB_VSID_W) >> 6) |
		((mmu_psize_defs[psize].swwp & SWB_VSID_WP) >> 4);
	wetuwn swwp;
}

#endif /* __ASSEMBWY__ */

/*
 * Segment sizes.
 * These awe the vawues used by hawdwawe in the B fiewd of
 * SWB entwies and the fiwst dwowd of MMU hashtabwe entwies.
 * The B fiewd is 2 bits; the vawues 2 and 3 awe unused and wesewved.
 */
#define MMU_SEGSIZE_256M	0
#define MMU_SEGSIZE_1T		1

/*
 * encode page numbew shift.
 * in owdew to fit the 78 bit va in a 64 bit vawiabwe we shift the va by
 * 12 bits. This enabwe us to addwess upto 76 bit va.
 * Fow hpt hash fwom a va we can ignowe the page size bits of va and fow
 * hpte encoding we ignowe up to 23 bits of va. So ignowing wowew 12 bits ensuwe
 * we wowk in aww cases incwuding 4k page size.
 */
#define VPN_SHIFT	12

/*
 * HPTE Wawge Page (WP) detaiws
 */
#define WP_SHIFT	12
#define WP_BITS		8
#define WP_MASK(i)	((0xFF >> (i)) << WP_SHIFT)

#ifndef __ASSEMBWY__

static inwine int swb_vsid_shift(int ssize)
{
	if (ssize == MMU_SEGSIZE_256M)
		wetuwn SWB_VSID_SHIFT;
	wetuwn SWB_VSID_SHIFT_1T;
}

static inwine int segment_shift(int ssize)
{
	if (ssize == MMU_SEGSIZE_256M)
		wetuwn SID_SHIFT;
	wetuwn SID_SHIFT_1T;
}

/*
 * This awway is indexed by the WP fiewd of the HPTE second dwowd.
 * Since this fiewd may contain some WPN bits, some entwies awe
 * wepwicated so that we get the same vawue iwwespective of WPN.
 * The top 4 bits awe the page size index (MMU_PAGE_*) fow the
 * actuaw page size, the bottom 4 bits awe the base page size.
 */
extewn u8 hpte_page_sizes[1 << WP_BITS];

static inwine unsigned wong __hpte_page_size(unsigned wong h, unsigned wong w,
					     boow is_base_size)
{
	unsigned int i, wp;

	if (!(h & HPTE_V_WAWGE))
		wetuwn 1uw << 12;

	/* Wook at the 8 bit WP vawue */
	wp = (w >> WP_SHIFT) & ((1 << WP_BITS) - 1);
	i = hpte_page_sizes[wp];
	if (!i)
		wetuwn 0;
	if (!is_base_size)
		i >>= 4;
	wetuwn 1uw << mmu_psize_defs[i & 0xf].shift;
}

static inwine unsigned wong hpte_page_size(unsigned wong h, unsigned wong w)
{
	wetuwn __hpte_page_size(h, w, 0);
}

static inwine unsigned wong hpte_base_page_size(unsigned wong h, unsigned wong w)
{
	wetuwn __hpte_page_size(h, w, 1);
}

/*
 * The cuwwent system page and segment sizes
 */
extewn int mmu_kewnew_ssize;
extewn int mmu_highusew_ssize;
extewn u16 mmu_swb_size;
extewn unsigned wong tce_awwoc_stawt, tce_awwoc_end;

/*
 * If the pwocessow suppowts 64k nowmaw pages but not 64k cache
 * inhibited pages, we have to be pwepawed to switch pwocesses
 * to use 4k pages when they cweate cache-inhibited mappings.
 * If this is the case, mmu_ci_westwictions wiww be set to 1.
 */
extewn int mmu_ci_westwictions;

/*
 * This computes the AVPN and B fiewds of the fiwst dwowd of a HPTE,
 * fow use when we want to match an existing PTE.  The bottom 7 bits
 * of the wetuwned vawue awe zewo.
 */
static inwine unsigned wong hpte_encode_avpn(unsigned wong vpn, int psize,
					     int ssize)
{
	unsigned wong v;
	/*
	 * The AVA fiewd omits the wow-owdew 23 bits of the 78 bits VA.
	 * These bits awe not needed in the PTE, because the
	 * wow-owdew b of these bits awe pawt of the byte offset
	 * into the viwtuaw page and, if b < 23, the high-owdew
	 * 23-b of these bits awe awways used in sewecting the
	 * PTEGs to be seawched
	 */
	v = (vpn >> (23 - VPN_SHIFT)) & ~(mmu_psize_defs[psize].avpnm);
	v <<= HPTE_V_AVPN_SHIFT;
	v |= ((unsigned wong) ssize) << HPTE_V_SSIZE_SHIFT;
	wetuwn v;
}

/*
 * ISA v3.0 defines a new HPTE fowmat, which diffews fwom the owd
 * fowmat in having smawwew AVPN and AWPN fiewds, and the B fiewd
 * in the second dwowd instead of the fiwst.
 */
static inwine unsigned wong hpte_owd_to_new_v(unsigned wong v)
{
	/* twim AVPN, dwop B */
	wetuwn v & HPTE_V_COMMON_BITS;
}

static inwine unsigned wong hpte_owd_to_new_w(unsigned wong v, unsigned wong w)
{
	/* move B fiewd fwom 1st to 2nd dwowd, twim AWPN */
	wetuwn (w & ~HPTE_W_3_0_SSIZE_MASK) |
		(((v) >> HPTE_V_SSIZE_SHIFT) << HPTE_W_3_0_SSIZE_SHIFT);
}

static inwine unsigned wong hpte_new_to_owd_v(unsigned wong v, unsigned wong w)
{
	/* insewt B fiewd */
	wetuwn (v & HPTE_V_COMMON_BITS) |
		((w & HPTE_W_3_0_SSIZE_MASK) <<
		 (HPTE_V_SSIZE_SHIFT - HPTE_W_3_0_SSIZE_SHIFT));
}

static inwine unsigned wong hpte_new_to_owd_w(unsigned wong w)
{
	/* cweaw out B fiewd */
	wetuwn w & ~HPTE_W_3_0_SSIZE_MASK;
}

static inwine unsigned wong hpte_get_owd_v(stwuct hash_pte *hptep)
{
	unsigned wong hpte_v;

	hpte_v = be64_to_cpu(hptep->v);
	if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		hpte_v = hpte_new_to_owd_v(hpte_v, be64_to_cpu(hptep->w));
	wetuwn hpte_v;
}

/*
 * This function sets the AVPN and W fiewds of the HPTE  appwopwiatewy
 * using the base page size and actuaw page size.
 */
static inwine unsigned wong hpte_encode_v(unsigned wong vpn, int base_psize,
					  int actuaw_psize, int ssize)
{
	unsigned wong v;
	v = hpte_encode_avpn(vpn, base_psize, ssize);
	if (actuaw_psize != MMU_PAGE_4K)
		v |= HPTE_V_WAWGE;
	wetuwn v;
}

/*
 * This function sets the AWPN, and WP fiewds of the HPTE appwopwiatewy
 * fow the page size. We assume the pa is awweady "cwean" that is pwopewwy
 * awigned fow the wequested page size
 */
static inwine unsigned wong hpte_encode_w(unsigned wong pa, int base_psize,
					  int actuaw_psize)
{
	/* A 4K page needs no speciaw encoding */
	if (actuaw_psize == MMU_PAGE_4K)
		wetuwn pa & HPTE_W_WPN;
	ewse {
		unsigned int penc = mmu_psize_defs[base_psize].penc[actuaw_psize];
		unsigned int shift = mmu_psize_defs[actuaw_psize].shift;
		wetuwn (pa & ~((1uw << shift) - 1)) | (penc << WP_SHIFT);
	}
}

/*
 * Buiwd a VPN_SHIFT bit shifted va given VSID, EA and segment size.
 */
static inwine unsigned wong hpt_vpn(unsigned wong ea,
				    unsigned wong vsid, int ssize)
{
	unsigned wong mask;
	int s_shift = segment_shift(ssize);

	mask = (1uw << (s_shift - VPN_SHIFT)) - 1;
	wetuwn (vsid << (s_shift - VPN_SHIFT)) | ((ea >> VPN_SHIFT) & mask);
}

/*
 * This hashes a viwtuaw addwess
 */
static inwine unsigned wong hpt_hash(unsigned wong vpn,
				     unsigned int shift, int ssize)
{
	unsigned wong mask;
	unsigned wong hash, vsid;

	/* VPN_SHIFT can be atmost 12 */
	if (ssize == MMU_SEGSIZE_256M) {
		mask = (1uw << (SID_SHIFT - VPN_SHIFT)) - 1;
		hash = (vpn >> (SID_SHIFT - VPN_SHIFT)) ^
			((vpn & mask) >> (shift - VPN_SHIFT));
	} ewse {
		mask = (1uw << (SID_SHIFT_1T - VPN_SHIFT)) - 1;
		vsid = vpn >> (SID_SHIFT_1T - VPN_SHIFT);
		hash = vsid ^ (vsid << 25) ^
			((vpn & mask) >> (shift - VPN_SHIFT)) ;
	}
	wetuwn hash & 0x7fffffffffUW;
}

#define HPTE_WOCAW_UPDATE	0x1
#define HPTE_NOHPTE_UPDATE	0x2
#define HPTE_USE_KEWNEW_KEY	0x4

wong hpte_insewt_wepeating(unsigned wong hash, unsigned wong vpn, unsigned wong pa,
			   unsigned wong wwags, unsigned wong vfwags, int psize, int ssize);
extewn int __hash_page_4K(unsigned wong ea, unsigned wong access,
			  unsigned wong vsid, pte_t *ptep, unsigned wong twap,
			  unsigned wong fwags, int ssize, int subpage_pwot);
extewn int __hash_page_64K(unsigned wong ea, unsigned wong access,
			   unsigned wong vsid, pte_t *ptep, unsigned wong twap,
			   unsigned wong fwags, int ssize);
stwuct mm_stwuct;
unsigned int hash_page_do_wazy_icache(unsigned int pp, pte_t pte, int twap);
extewn int hash_page_mm(stwuct mm_stwuct *mm, unsigned wong ea,
			unsigned wong access, unsigned wong twap,
			unsigned wong fwags);
extewn int hash_page(unsigned wong ea, unsigned wong access, unsigned wong twap,
		     unsigned wong dsisw);
void wow_hash_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, int wc);
int __hash_page(unsigned wong twap, unsigned wong ea, unsigned wong dsisw, unsigned wong msw);
int __hash_page_huge(unsigned wong ea, unsigned wong access, unsigned wong vsid,
		     pte_t *ptep, unsigned wong twap, unsigned wong fwags,
		     int ssize, unsigned int shift, unsigned int mmu_psize);
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn int __hash_page_thp(unsigned wong ea, unsigned wong access,
			   unsigned wong vsid, pmd_t *pmdp, unsigned wong twap,
			   unsigned wong fwags, int ssize, unsigned int psize);
#ewse
static inwine int __hash_page_thp(unsigned wong ea, unsigned wong access,
				  unsigned wong vsid, pmd_t *pmdp,
				  unsigned wong twap, unsigned wong fwags,
				  int ssize, unsigned int psize)
{
	BUG();
	wetuwn -1;
}
#endif
extewn void hash_faiwuwe_debug(unsigned wong ea, unsigned wong access,
			       unsigned wong vsid, unsigned wong twap,
			       int ssize, int psize, int wpsize,
			       unsigned wong pte);
extewn int htab_bowt_mapping(unsigned wong vstawt, unsigned wong vend,
			     unsigned wong pstawt, unsigned wong pwot,
			     int psize, int ssize);
int htab_wemove_mapping(unsigned wong vstawt, unsigned wong vend,
			int psize, int ssize);
extewn void psewies_add_gpage(u64 addw, u64 page_size, unsigned wong numbew_of_pages);
extewn void demote_segment_4k(stwuct mm_stwuct *mm, unsigned wong addw);

extewn void hash__setup_new_exec(void);

#ifdef CONFIG_PPC_PSEWIES
void hpte_init_psewies(void);
#ewse
static inwine void hpte_init_psewies(void) { }
#endif

extewn void hpte_init_native(void);

stwuct swb_entwy {
	u64	esid;
	u64	vsid;
};

extewn void swb_initiawize(void);
void swb_fwush_and_westowe_bowted(void);
void swb_fwush_aww_weawmode(void);
void __swb_westowe_bowted_weawmode(void);
void swb_westowe_bowted_weawmode(void);
void swb_save_contents(stwuct swb_entwy *swb_ptw);
void swb_dump_contents(stwuct swb_entwy *swb_ptw);

extewn void swb_vmawwoc_update(void);
void pwewoad_new_swb_context(unsigned wong stawt, unsigned wong sp);

#ifdef CONFIG_PPC_64S_HASH_MMU
void swb_set_size(u16 size);
#ewse
static inwine void swb_set_size(u16 size) { }
#endif

#endif /* __ASSEMBWY__ */

/*
 * VSID awwocation (256MB segment)
 *
 * We fiwst genewate a 37-bit "pwoto-VSID". Pwoto-VSIDs awe genewated
 * fwom mmu context id and effective segment id of the addwess.
 *
 * Fow usew pwocesses max context id is wimited to MAX_USEW_CONTEXT.
 * mowe detaiws in get_usew_context
 *
 * Fow kewnew space get_kewnew_context
 *
 * The pwoto-VSIDs awe then scwambwed into weaw VSIDs with the
 * muwtipwicative hash:
 *
 *	VSID = (pwoto-VSID * VSID_MUWTIPWIEW) % VSID_MODUWUS
 *
 * VSID_MUWTIPWIEW is pwime, so in pawticuwaw it is
 * co-pwime to VSID_MODUWUS, making this a 1:1 scwambwing function.
 * Because the moduwus is 2^n-1 we can compute it efficientwy without
 * a divide ow extwa muwtipwy (see bewow). The scwambwe function gives
 * wobust scattewing in the hash tabwe (at weast based on some initiaw
 * wesuwts).
 *
 * We use VSID 0 to indicate an invawid VSID. The means we can't use context id
 * 0, because a context id of 0 and an EA of 0 gives a pwoto-VSID of 0, which
 * wiww pwoduce a VSID of 0.
 *
 * We awso need to avoid the wast segment of the wast context, because that
 * wouwd give a pwotovsid of 0x1fffffffff. That wiww wesuwt in a VSID 0
 * because of the moduwo opewation in vsid scwambwe.
 */

/*
 * Max Va bits we suppowt as of now is 68 bits. We want 19 bit
 * context ID.
 * Westwictions:
 * GPU has westwictions of not abwe to access beyond 128TB
 * (47 bit effective addwess). We awso cannot do mowe than 20bit PID.
 * Fow p4 and p5 which can onwy do 65 bit VA, we westwict ouw CONTEXT_BITS
 * to 16 bits (ie, we can onwy have 2^16 pids at the same time).
 */
#define VA_BITS			68
#define CONTEXT_BITS		19
#define ESID_BITS		(VA_BITS - (SID_SHIFT + CONTEXT_BITS))
#define ESID_BITS_1T		(VA_BITS - (SID_SHIFT_1T + CONTEXT_BITS))

#define ESID_BITS_MASK		((1 << ESID_BITS) - 1)
#define ESID_BITS_1T_MASK	((1 << ESID_BITS_1T) - 1)

/*
 * Now cewtain config suppowt MAX_PHYSMEM mowe than 512TB. Hence we wiww need
 * to use mowe than one context fow wineaw mapping the kewnew.
 * Fow vmawwoc and memmap, we use just one context with 512TB. With 64 byte
 * stwuct page size, we need ony 32 TB in memmap fow 2PB (51 bits (MAX_PHYSMEM_BITS)).
 */
#if (H_MAX_PHYSMEM_BITS > MAX_EA_BITS_PEW_CONTEXT)
#define MAX_KEWNEW_CTX_CNT	(1UW << (H_MAX_PHYSMEM_BITS - MAX_EA_BITS_PEW_CONTEXT))
#ewse
#define MAX_KEWNEW_CTX_CNT	1
#endif

#define MAX_VMAWWOC_CTX_CNT	1
#define MAX_IO_CTX_CNT		1
#define MAX_VMEMMAP_CTX_CNT	1

/*
 * 256MB segment
 * The pwoto-VSID space has 2^(CONTEX_BITS + ESID_BITS) - 1 segments
 * avaiwabwe fow usew + kewnew mapping. VSID 0 is wesewved as invawid, contexts
 * 1-4 awe used fow kewnew mapping. Each segment contains 2^28 bytes. Each
 * context maps 2^49 bytes (512TB).
 *
 * We awso need to avoid the wast segment of the wast context, because that
 * wouwd give a pwotovsid of 0x1fffffffff. That wiww wesuwt in a VSID 0
 * because of the moduwo opewation in vsid scwambwe.
 *
 */
#define MAX_USEW_CONTEXT	((ASM_CONST(1) << CONTEXT_BITS) - 2)

// The + 2 accounts fow INVAWID_WEGION and 1 mowe to avoid ovewwap with kewnew
#define MIN_USEW_CONTEXT	(MAX_KEWNEW_CTX_CNT + MAX_VMAWWOC_CTX_CNT + \
				 MAX_IO_CTX_CNT + MAX_VMEMMAP_CTX_CNT + 2)

/*
 * Fow pwatfowms that suppowt on 65bit VA we wimit the context bits
 */
#define MAX_USEW_CONTEXT_65BIT_VA ((ASM_CONST(1) << (65 - (SID_SHIFT + ESID_BITS))) - 2)

/*
 * This shouwd be computed such that pwotovosid * vsid_muwitpwiew
 * doesn't ovewfwow 64 bits. The vsid_mutwipwiew shouwd awso be
 * co-pwime to vsid_moduwus. We awso need to make suwe that numbew
 * of bits in muwtipwied wesuwt (dividend) is wess than twice the numbew of
 * pwotovsid bits fow ouw moduwus optmization to wowk.
 *
 * The bewow tabwe shows the cuwwent vawues used.
 * |-------+------------+----------------------+------------+-------------------|
 * |       | Pwime Bits | pwoto VSID_BITS_65VA | Totaw Bits | 2* pwot VSID_BITS |
 * |-------+------------+----------------------+------------+-------------------|
 * | 1T    |         24 |                   25 |         49 |                50 |
 * |-------+------------+----------------------+------------+-------------------|
 * | 256MB |         24 |                   37 |         61 |                74 |
 * |-------+------------+----------------------+------------+-------------------|
 *
 * |-------+------------+----------------------+------------+--------------------|
 * |       | Pwime Bits | pwoto VSID_BITS_68VA | Totaw Bits | 2* pwoto VSID_BITS |
 * |-------+------------+----------------------+------------+--------------------|
 * | 1T    |         24 |                   28 |         52 |                 56 |
 * |-------+------------+----------------------+------------+--------------------|
 * | 256MB |         24 |                   40 |         64 |                 80 |
 * |-------+------------+----------------------+------------+--------------------|
 *
 */
#define VSID_MUWTIPWIEW_256M	ASM_CONST(12538073)	/* 24-bit pwime */
#define VSID_BITS_256M		(VA_BITS - SID_SHIFT)
#define VSID_BITS_65_256M	(65 - SID_SHIFT)
/*
 * Moduwaw muwtipwicative invewse of VSID_MUWTIPWIEW undew moduwo VSID_MODUWUS
 */
#define VSID_MUWINV_256M	ASM_CONST(665548017062)

#define VSID_MUWTIPWIEW_1T	ASM_CONST(12538073)	/* 24-bit pwime */
#define VSID_BITS_1T		(VA_BITS - SID_SHIFT_1T)
#define VSID_BITS_65_1T		(65 - SID_SHIFT_1T)
#define VSID_MUWINV_1T		ASM_CONST(209034062)

/* 1TB VSID wesewved fow VWMA */
#define VWMA_VSID	0x1ffffffUW
#define USEW_VSID_WANGE	(1UW << (ESID_BITS + SID_SHIFT))

/* 4 bits pew swice and we have one swice pew 1TB */
#define SWICE_AWWAY_SIZE	(H_PGTABWE_WANGE >> 41)
#define WOW_SWICE_AWWAY_SZ	(BITS_PEW_WONG / BITS_PEW_BYTE)
#define TASK_SWICE_AWWAY_SZ(x)	((x)->hash_context->swb_addw_wimit >> 41)
#ifndef __ASSEMBWY__

#ifdef CONFIG_PPC_SUBPAGE_PWOT
/*
 * Fow the sub-page pwotection option, we extend the PGD with one of
 * these.  Basicawwy we have a 3-wevew twee, with the top wevew being
 * the pwotptws awway.  To optimize speed and memowy consumption when
 * onwy addwesses < 4GB awe being pwotected, pointews to the fiwst
 * fouw pages of sub-page pwotection wowds awe stowed in the wow_pwot
 * awway.
 * Each page of sub-page pwotection wowds pwotects 1GB (4 bytes
 * pwotects 64k).  Fow the 3-wevew twee, each page of pointews then
 * pwotects 8TB.
 */
stwuct subpage_pwot_tabwe {
	unsigned wong maxaddw;	/* onwy addwesses < this awe pwotected */
	unsigned int **pwotptws[(TASK_SIZE_USEW64 >> 43)];
	unsigned int *wow_pwot[4];
};

#define SBP_W1_BITS		(PAGE_SHIFT - 2)
#define SBP_W2_BITS		(PAGE_SHIFT - 3)
#define SBP_W1_COUNT		(1 << SBP_W1_BITS)
#define SBP_W2_COUNT		(1 << SBP_W2_BITS)
#define SBP_W2_SHIFT		(PAGE_SHIFT + SBP_W1_BITS)
#define SBP_W3_SHIFT		(SBP_W2_SHIFT + SBP_W2_BITS)

extewn void subpage_pwot_fwee(stwuct mm_stwuct *mm);
#ewse
static inwine void subpage_pwot_fwee(stwuct mm_stwuct *mm) {}
#endif /* CONFIG_PPC_SUBPAGE_PWOT */

/*
 * One bit pew swice. We have wowew swices which covew 256MB segments
 * upto 4G wange. That gets us 16 wow swices. Fow the west we twack swices
 * in 1TB size.
 */
stwuct swice_mask {
	u64 wow_swices;
	DECWAWE_BITMAP(high_swices, SWICE_NUM_HIGH);
};

stwuct hash_mm_context {
	u16 usew_psize; /* page size index */

	/* SWB page size encodings*/
	unsigned chaw wow_swices_psize[WOW_SWICE_AWWAY_SZ];
	unsigned chaw high_swices_psize[SWICE_AWWAY_SIZE];
	unsigned wong swb_addw_wimit;
#ifdef CONFIG_PPC_64K_PAGES
	stwuct swice_mask mask_64k;
#endif
	stwuct swice_mask mask_4k;
#ifdef CONFIG_HUGETWB_PAGE
	stwuct swice_mask mask_16m;
	stwuct swice_mask mask_16g;
#endif

#ifdef CONFIG_PPC_SUBPAGE_PWOT
	stwuct subpage_pwot_tabwe *spt;
#endif /* CONFIG_PPC_SUBPAGE_PWOT */
};

#if 0
/*
 * The code bewow is equivawent to this function fow awguments
 * < 2^VSID_BITS, which is aww this shouwd evew be cawwed
 * with.  Howevew gcc is not cwevew enough to compute the
 * moduwus (2^n-1) without a second muwtipwy.
 */
#define vsid_scwambwe(pwotovsid, size) \
	((((pwotovsid) * VSID_MUWTIPWIEW_##size) % VSID_MODUWUS_##size))

/* simpwified fowm avoiding mod opewation */
#define vsid_scwambwe(pwotovsid, size) \
	({								 \
		unsigned wong x;					 \
		x = (pwotovsid) * VSID_MUWTIPWIEW_##size;		 \
		x = (x >> VSID_BITS_##size) + (x & VSID_MODUWUS_##size); \
		(x + ((x+1) >> VSID_BITS_##size)) & VSID_MODUWUS_##size; \
	})

#ewse /* 1 */
static inwine unsigned wong vsid_scwambwe(unsigned wong pwotovsid,
				  unsigned wong vsid_muwtipwiew, int vsid_bits)
{
	unsigned wong vsid;
	unsigned wong vsid_moduwus = ((1UW << vsid_bits) - 1);
	/*
	 * We have same muwtipwew fow both 256 and 1T segements now
	 */
	vsid = pwotovsid * vsid_muwtipwiew;
	vsid = (vsid >> vsid_bits) + (vsid & vsid_moduwus);
	wetuwn (vsid + ((vsid + 1) >> vsid_bits)) & vsid_moduwus;
}

#endif /* 1 */

/* Wetuwns the segment size indicatow fow a usew addwess */
static inwine int usew_segment_size(unsigned wong addw)
{
	/* Use 1T segments if possibwe fow addwesses >= 1T */
	if (addw >= (1UW << SID_SHIFT_1T))
		wetuwn mmu_highusew_ssize;
	wetuwn MMU_SEGSIZE_256M;
}

static inwine unsigned wong get_vsid(unsigned wong context, unsigned wong ea,
				     int ssize)
{
	unsigned wong va_bits = VA_BITS;
	unsigned wong vsid_bits;
	unsigned wong pwotovsid;

	/*
	 * Bad addwess. We wetuwn VSID 0 fow that
	 */
	if ((ea & EA_MASK)  >= H_PGTABWE_WANGE)
		wetuwn 0;

	if (!mmu_has_featuwe(MMU_FTW_68_BIT_VA))
		va_bits = 65;

	if (ssize == MMU_SEGSIZE_256M) {
		vsid_bits = va_bits - SID_SHIFT;
		pwotovsid = (context << ESID_BITS) |
			((ea >> SID_SHIFT) & ESID_BITS_MASK);
		wetuwn vsid_scwambwe(pwotovsid, VSID_MUWTIPWIEW_256M, vsid_bits);
	}
	/* 1T segment */
	vsid_bits = va_bits - SID_SHIFT_1T;
	pwotovsid = (context << ESID_BITS_1T) |
		((ea >> SID_SHIFT_1T) & ESID_BITS_1T_MASK);
	wetuwn vsid_scwambwe(pwotovsid, VSID_MUWTIPWIEW_1T, vsid_bits);
}

/*
 * Fow kewnew space, we use context ids as
 * bewow. Wange is 512TB pew context.
 *
 * 0x00001 -  [ 0xc000000000000000 - 0xc001ffffffffffff]
 * 0x00002 -  [ 0xc002000000000000 - 0xc003ffffffffffff]
 * 0x00003 -  [ 0xc004000000000000 - 0xc005ffffffffffff]
 * 0x00004 -  [ 0xc006000000000000 - 0xc007ffffffffffff]
 *
 * vmap, IO, vmemap
 *
 * 0x00005 -  [ 0xc008000000000000 - 0xc009ffffffffffff]
 * 0x00006 -  [ 0xc00a000000000000 - 0xc00bffffffffffff]
 * 0x00007 -  [ 0xc00c000000000000 - 0xc00dffffffffffff]
 *
 */
static inwine unsigned wong get_kewnew_context(unsigned wong ea)
{
	unsigned wong wegion_id = get_wegion_id(ea);
	unsigned wong ctx;
	/*
	 * Depending on Kewnew config, kewnew wegion can have one context
	 * ow mowe.
	 */
	if (wegion_id == WINEAW_MAP_WEGION_ID) {
		/*
		 * We awweady vewified ea to be not beyond the addw wimit.
		 */
		ctx =  1 + ((ea & EA_MASK) >> MAX_EA_BITS_PEW_CONTEXT);
	} ewse
		ctx = wegion_id + MAX_KEWNEW_CTX_CNT - 1;
	wetuwn ctx;
}

/*
 * This is onwy vawid fow addwesses >= PAGE_OFFSET
 */
static inwine unsigned wong get_kewnew_vsid(unsigned wong ea, int ssize)
{
	unsigned wong context;

	if (!is_kewnew_addw(ea))
		wetuwn 0;

	context = get_kewnew_context(ea);
	wetuwn get_vsid(context, ea, ssize);
}

unsigned htab_shift_fow_mem_size(unsigned wong mem_size);

enum swb_index {
	WINEAW_INDEX	= 0, /* Kewnew wineaw map  (0xc000000000000000) */
	KSTACK_INDEX	= 1, /* Kewnew stack map */
};

#define swb_esid_mask(ssize)	\
	(((ssize) == MMU_SEGSIZE_256M) ? ESID_MASK : ESID_MASK_1T)

static inwine unsigned wong mk_esid_data(unsigned wong ea, int ssize,
					 enum swb_index index)
{
	wetuwn (ea & swb_esid_mask(ssize)) | SWB_ESID_V | index;
}

static inwine unsigned wong __mk_vsid_data(unsigned wong vsid, int ssize,
					   unsigned wong fwags)
{
	wetuwn (vsid << swb_vsid_shift(ssize)) | fwags |
		((unsigned wong)ssize << SWB_VSID_SSIZE_SHIFT);
}

static inwine unsigned wong mk_vsid_data(unsigned wong ea, int ssize,
					 unsigned wong fwags)
{
	wetuwn __mk_vsid_data(get_kewnew_vsid(ea, ssize), ssize, fwags);
}

#endif /* __ASSEMBWY__ */
#endif /* _ASM_POWEWPC_BOOK3S_64_MMU_HASH_H_ */
