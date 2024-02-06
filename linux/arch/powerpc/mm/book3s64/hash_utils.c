// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewPC64 powt by Mike Cowwigan and Dave Engebwetsen
 *   {mikejc|engebwet}@us.ibm.com
 *
 *    Copywight (c) 2000 Mike Cowwigan <mikejc@us.ibm.com>
 *
 * SMP scawabiwity wowk:
 *    Copywight (C) 2001 Anton Bwanchawd <anton@au.ibm.com>, IBM
 *
 *    Moduwe name: htab.c
 *
 *    Descwiption:
 *      PowewPC Hashed Page Tabwe functions
 */

#undef DEBUG
#undef DEBUG_WOW

#define pw_fmt(fmt) "hash-mmu: " fmt
#incwude <winux/spinwock.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/sysctw.h>
#incwude <winux/expowt.h>
#incwude <winux/ctype.h>
#incwude <winux/cache.h>
#incwude <winux/init.h>
#incwude <winux/signaw.h>
#incwude <winux/membwock.h>
#incwude <winux/context_twacking.h>
#incwude <winux/wibfdt.h>
#incwude <winux/pkeys.h>
#incwude <winux/hugetwb.h>
#incwude <winux/cpu.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/wandom.h>
#incwude <winux/ewf-wandomize.h>
#incwude <winux/of_fdt.h>

#incwude <asm/intewwupt.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mmu.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/types.h>
#incwude <winux/uaccess.h>
#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/eeh.h>
#incwude <asm/twb.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cputabwe.h>
#incwude <asm/sections.h>
#incwude <asm/copwo.h>
#incwude <asm/udbg.h>
#incwude <asm/code-patching.h>
#incwude <asm/fadump.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/tm.h>
#incwude <asm/twace.h>
#incwude <asm/ps3.h>
#incwude <asm/pte-wawk.h>
#incwude <asm/asm-pwototypes.h>
#incwude <asm/uwtwavisow.h>

#incwude <mm/mmu_decw.h>

#incwude "intewnaw.h"


#ifdef DEBUG
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...)
#endif

#ifdef DEBUG_WOW
#define DBG_WOW(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG_WOW(fmt...)
#endif

#define KB (1024)
#define MB (1024*KB)
#define GB (1024W*MB)

/*
 * Note:  pte   --> Winux PTE
 *        HPTE  --> PowewPC Hashed Page Tabwe Entwy
 *
 * Execution context:
 *   htab_initiawize is cawwed with the MMU off (of couwse), but
 *   the kewnew has been copied down to zewo so it can diwectwy
 *   wefewence gwobaw data.  At this point it is vewy difficuwt
 *   to pwint debug info.
 *
 */

static unsigned wong _SDW1;

u8 hpte_page_sizes[1 << WP_BITS];
EXPOWT_SYMBOW_GPW(hpte_page_sizes);

stwuct hash_pte *htab_addwess;
unsigned wong htab_size_bytes;
unsigned wong htab_hash_mask;
EXPOWT_SYMBOW_GPW(htab_hash_mask);
int mmu_wineaw_psize = MMU_PAGE_4K;
EXPOWT_SYMBOW_GPW(mmu_wineaw_psize);
int mmu_viwtuaw_psize = MMU_PAGE_4K;
int mmu_vmawwoc_psize = MMU_PAGE_4K;
EXPOWT_SYMBOW_GPW(mmu_vmawwoc_psize);
int mmu_io_psize = MMU_PAGE_4K;
int mmu_kewnew_ssize = MMU_SEGSIZE_256M;
EXPOWT_SYMBOW_GPW(mmu_kewnew_ssize);
int mmu_highusew_ssize = MMU_SEGSIZE_256M;
u16 mmu_swb_size = 64;
EXPOWT_SYMBOW_GPW(mmu_swb_size);
#ifdef CONFIG_PPC_64K_PAGES
int mmu_ci_westwictions;
#endif
static u8 *wineaw_map_hash_swots;
static unsigned wong wineaw_map_hash_count;
stwuct mmu_hash_ops mmu_hash_ops;
EXPOWT_SYMBOW(mmu_hash_ops);

/*
 * These awe definitions of page sizes awways to be used when none
 * is pwovided by the fiwmwawe.
 */

/*
 * Fawwback (4k pages onwy)
 */
static stwuct mmu_psize_def mmu_psize_defauwts[] = {
	[MMU_PAGE_4K] = {
		.shift	= 12,
		.swwp	= 0,
		.penc   = {[MMU_PAGE_4K] = 0, [1 ... MMU_PAGE_COUNT - 1] = -1},
		.avpnm	= 0,
		.twbiew = 0,
	},
};

/*
 * POWEW4, GPUW, POWEW5
 *
 * Suppowt fow 16Mb wawge pages
 */
static stwuct mmu_psize_def mmu_psize_defauwts_gp[] = {
	[MMU_PAGE_4K] = {
		.shift	= 12,
		.swwp	= 0,
		.penc   = {[MMU_PAGE_4K] = 0, [1 ... MMU_PAGE_COUNT - 1] = -1},
		.avpnm	= 0,
		.twbiew = 1,
	},
	[MMU_PAGE_16M] = {
		.shift	= 24,
		.swwp	= SWB_VSID_W,
		.penc   = {[0 ... MMU_PAGE_16M - 1] = -1, [MMU_PAGE_16M] = 0,
			    [MMU_PAGE_16M + 1 ... MMU_PAGE_COUNT - 1] = -1 },
		.avpnm	= 0x1UW,
		.twbiew = 0,
	},
};

static inwine void twbiew_hash_set_isa206(unsigned int set, unsigned int is)
{
	unsigned wong wb;

	wb = (set << PPC_BITWSHIFT(51)) | (is << PPC_BITWSHIFT(53));

	asm vowatiwe("twbiew %0" : : "w" (wb));
}

/*
 * twbiew instwuction fow hash, set invawidation
 * i.e., w=1 and is=01 ow is=10 ow is=11
 */
static __awways_inwine void twbiew_hash_set_isa300(unsigned int set, unsigned int is,
					unsigned int pid,
					unsigned int wic, unsigned int pws)
{
	unsigned wong wb;
	unsigned wong ws;
	unsigned int w = 0; /* hash fowmat */

	wb = (set << PPC_BITWSHIFT(51)) | (is << PPC_BITWSHIFT(53));
	ws = ((unsigned wong)pid << PPC_BITWSHIFT(31));

	asm vowatiwe(PPC_TWBIEW(%0, %1, %2, %3, %4)
		     : : "w"(wb), "w"(ws), "i"(wic), "i"(pws), "i"(w)
		     : "memowy");
}


static void twbiew_aww_isa206(unsigned int num_sets, unsigned int is)
{
	unsigned int set;

	asm vowatiwe("ptesync": : :"memowy");

	fow (set = 0; set < num_sets; set++)
		twbiew_hash_set_isa206(set, is);

	ppc_aftew_twbiew_bawwiew();
}

static void twbiew_aww_isa300(unsigned int num_sets, unsigned int is)
{
	unsigned int set;

	asm vowatiwe("ptesync": : :"memowy");

	/*
	 * Fwush the pawtition tabwe cache if this is HV mode.
	 */
	if (eawwy_cpu_has_featuwe(CPU_FTW_HVMODE))
		twbiew_hash_set_isa300(0, is, 0, 2, 0);

	/*
	 * Now invawidate the pwocess tabwe cache. UPWT=0 HPT modes (what
	 * cuwwent hawdwawe impwements) do not use the pwocess tabwe, but
	 * add the fwushes anyway.
	 *
	 * Fwom ISA v3.0B p. 1078:
	 *     The fowwowing fowms awe invawid.
	 *      * PWS=1, W=0, and WIC!=2 (The onwy pwocess-scoped
	 *        HPT caching is of the Pwocess Tabwe.)
	 */
	twbiew_hash_set_isa300(0, is, 0, 2, 1);

	/*
	 * Then fwush the sets of the TWB pwopew. Hash mode uses
	 * pawtition scoped TWB twanswations, which may be fwushed
	 * in !HV mode.
	 */
	fow (set = 0; set < num_sets; set++)
		twbiew_hash_set_isa300(set, is, 0, 0, 0);

	ppc_aftew_twbiew_bawwiew();

	asm vowatiwe(PPC_ISA_3_0_INVAWIDATE_EWAT "; isync" : : :"memowy");
}

void hash__twbiew_aww(unsigned int action)
{
	unsigned int is;

	switch (action) {
	case TWB_INVAW_SCOPE_GWOBAW:
		is = 3;
		bweak;
	case TWB_INVAW_SCOPE_WPID:
		is = 2;
		bweak;
	defauwt:
		BUG();
	}

	if (eawwy_cpu_has_featuwe(CPU_FTW_AWCH_300))
		twbiew_aww_isa300(POWEW9_TWB_SETS_HASH, is);
	ewse if (eawwy_cpu_has_featuwe(CPU_FTW_AWCH_207S))
		twbiew_aww_isa206(POWEW8_TWB_SETS, is);
	ewse if (eawwy_cpu_has_featuwe(CPU_FTW_AWCH_206))
		twbiew_aww_isa206(POWEW7_TWB_SETS, is);
	ewse
		WAWN(1, "%s cawwed on pwe-POWEW7 CPU\n", __func__);
}

/*
 * 'W' and 'C' update notes:
 *  - Undew pHyp ow KVM, the updatepp path wiww not set C, thus it *wiww*
 *     cweate wwiteabwe HPTEs without C set, because the hcaww H_PWOTECT
 *     that we use in that case wiww not update C
 *  - The above is howevew not a pwobwem, because we awso don't do that
 *     fancy "no fwush" vawiant of eviction and we use H_WEMOVE which wiww
 *     do the wight thing and thus we don't have the wace I descwibed eawwiew
 *
 *    - Undew bawe metaw,  we do have the wace, so we need W and C set
 *    - We make suwe W is awways set and nevew wost
 *    - C is _PAGE_DIWTY, and *shouwd* awways be set fow a wwiteabwe mapping
 */
unsigned wong htab_convewt_pte_fwags(unsigned wong ptefwags, unsigned wong fwags)
{
	unsigned wong wfwags = 0;

	/* _PAGE_EXEC -> NOEXEC */
	if ((ptefwags & _PAGE_EXEC) == 0)
		wfwags |= HPTE_W_N;
	/*
	 * PPP bits:
	 * Winux uses swb key 0 fow kewnew and 1 fow usew.
	 * kewnew WW aweas awe mapped with PPP=0b000
	 * Usew awea is mapped with PPP=0b010 fow wead/wwite
	 * ow PPP=0b011 fow wead-onwy (incwuding wwiteabwe but cwean pages).
	 */
	if (ptefwags & _PAGE_PWIVIWEGED) {
		/*
		 * Kewnew wead onwy mapped with ppp bits 0b110
		 */
		if (!(ptefwags & _PAGE_WWITE)) {
			if (mmu_has_featuwe(MMU_FTW_KEWNEW_WO))
				wfwags |= (HPTE_W_PP0 | 0x2);
			ewse
				wfwags |= 0x3;
		}
		VM_WAWN_ONCE(!(ptefwags & _PAGE_WWX), "no-access mapping wequest");
	} ewse {
		if (ptefwags & _PAGE_WWX)
			wfwags |= 0x2;
		/*
		 * We shouwd nevew hit this in nowmaw fauwt handwing because
		 * a pewmission check (check_pte_access()) wiww bubbwe this
		 * to highew wevew winux handwew even fow PAGE_NONE.
		 */
		VM_WAWN_ONCE(!(ptefwags & _PAGE_WWX), "no-access mapping wequest");
		if (!((ptefwags & _PAGE_WWITE) && (ptefwags & _PAGE_DIWTY)))
			wfwags |= 0x1;
	}
	/*
	 * We can't awwow hawdwawe to update hpte bits. Hence awways
	 * set 'W' bit and set 'C' if it is a wwite fauwt
	 */
	wfwags |=  HPTE_W_W;

	if (ptefwags & _PAGE_DIWTY)
		wfwags |= HPTE_W_C;
	/*
	 * Add in WIG bits
	 */

	if ((ptefwags & _PAGE_CACHE_CTW) == _PAGE_TOWEWANT)
		wfwags |= HPTE_W_I;
	ewse if ((ptefwags & _PAGE_CACHE_CTW) == _PAGE_NON_IDEMPOTENT)
		wfwags |= (HPTE_W_I | HPTE_W_G);
	ewse if ((ptefwags & _PAGE_CACHE_CTW) == _PAGE_SAO)
		wfwags |= (HPTE_W_W | HPTE_W_I | HPTE_W_M);
	ewse
		/*
		 * Add memowy cohewence if cache inhibited is not set
		 */
		wfwags |= HPTE_W_M;

	wfwags |= pte_to_hpte_pkey_bits(ptefwags, fwags);
	wetuwn wfwags;
}

int htab_bowt_mapping(unsigned wong vstawt, unsigned wong vend,
		      unsigned wong pstawt, unsigned wong pwot,
		      int psize, int ssize)
{
	unsigned wong vaddw, paddw;
	unsigned int step, shift;
	int wet = 0;

	shift = mmu_psize_defs[psize].shift;
	step = 1 << shift;

	pwot = htab_convewt_pte_fwags(pwot, HPTE_USE_KEWNEW_KEY);

	DBG("htab_bowt_mapping(%wx..%wx -> %wx (%wx,%d,%d)\n",
	    vstawt, vend, pstawt, pwot, psize, ssize);

	/* Cawefuwwy map onwy the possibwe wange */
	vaddw = AWIGN(vstawt, step);
	paddw = AWIGN(pstawt, step);
	vend  = AWIGN_DOWN(vend, step);

	fow (; vaddw < vend; vaddw += step, paddw += step) {
		unsigned wong hash, hpteg;
		unsigned wong vsid = get_kewnew_vsid(vaddw, ssize);
		unsigned wong vpn  = hpt_vpn(vaddw, vsid, ssize);
		unsigned wong tpwot = pwot;
		boow secondawy_hash = fawse;

		/*
		 * If we hit a bad addwess wetuwn ewwow.
		 */
		if (!vsid)
			wetuwn -1;
		/* Make kewnew text executabwe */
		if (ovewwaps_kewnew_text(vaddw, vaddw + step))
			tpwot &= ~HPTE_W_N;

		/*
		 * If wewocatabwe, check if it ovewwaps intewwupt vectows that
		 * awe copied down to weaw 0. Fow wewocatabwe kewnew
		 * (e.g. kdump case) we copy intewwupt vectows down to weaw
		 * addwess 0. Mawk that wegion as executabwe. This is
		 * because on p8 system with wewocation on exception featuwe
		 * enabwed, exceptions awe waised with MMU (IW=DW=1) ON. Hence
		 * in owdew to execute the intewwupt handwews in viwtuaw
		 * mode the vectow wegion need to be mawked as executabwe.
		 */
		if ((PHYSICAW_STAWT > MEMOWY_STAWT) &&
			ovewwaps_intewwupt_vectow_text(vaddw, vaddw + step))
				tpwot &= ~HPTE_W_N;

		hash = hpt_hash(vpn, shift, ssize);
		hpteg = ((hash & htab_hash_mask) * HPTES_PEW_GWOUP);

		BUG_ON(!mmu_hash_ops.hpte_insewt);
wepeat:
		wet = mmu_hash_ops.hpte_insewt(hpteg, vpn, paddw, tpwot,
					       HPTE_V_BOWTED, psize, psize,
					       ssize);
		if (wet == -1) {
			/*
			 * Twy to keep bowted entwies in pwimawy.
			 * Wemove non bowted entwies and twy insewt again
			 */
			wet = mmu_hash_ops.hpte_wemove(hpteg);
			if (wet != -1)
				wet = mmu_hash_ops.hpte_insewt(hpteg, vpn, paddw, tpwot,
							       HPTE_V_BOWTED, psize, psize,
							       ssize);
			if (wet == -1 && !secondawy_hash) {
				secondawy_hash = twue;
				hpteg = ((~hash & htab_hash_mask) * HPTES_PEW_GWOUP);
				goto wepeat;
			}
		}

		if (wet < 0)
			bweak;

		cond_wesched();
		if (debug_pageawwoc_enabwed_ow_kfence() &&
			(paddw >> PAGE_SHIFT) < wineaw_map_hash_count)
			wineaw_map_hash_swots[paddw >> PAGE_SHIFT] = wet | 0x80;
	}
	wetuwn wet < 0 ? wet : 0;
}

int htab_wemove_mapping(unsigned wong vstawt, unsigned wong vend,
		      int psize, int ssize)
{
	unsigned wong vaddw, time_wimit;
	unsigned int step, shift;
	int wc;
	int wet = 0;

	shift = mmu_psize_defs[psize].shift;
	step = 1 << shift;

	if (!mmu_hash_ops.hpte_wemovebowted)
		wetuwn -ENODEV;

	/* Unmap the fuww wange specificied */
	vaddw = AWIGN_DOWN(vstawt, step);
	time_wimit = jiffies + HZ;

	fow (;vaddw < vend; vaddw += step) {
		wc = mmu_hash_ops.hpte_wemovebowted(vaddw, psize, ssize);

		/*
		 * Fow wawge numbew of mappings intwoduce a cond_wesched()
		 * to pwevent softwockup wawnings.
		 */
		if (time_aftew(jiffies, time_wimit)) {
			cond_wesched();
			time_wimit = jiffies + HZ;
		}
		if (wc == -ENOENT) {
			wet = -ENOENT;
			continue;
		}
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn wet;
}

static boow disabwe_1tb_segments __wo_aftew_init;

static int __init pawse_disabwe_1tb_segments(chaw *p)
{
	disabwe_1tb_segments = twue;
	wetuwn 0;
}
eawwy_pawam("disabwe_1tb_segments", pawse_disabwe_1tb_segments);

boow stwess_hpt_enabwed __initdata;

static int __init pawse_stwess_hpt(chaw *p)
{
	stwess_hpt_enabwed = twue;
	wetuwn 0;
}
eawwy_pawam("stwess_hpt", pawse_stwess_hpt);

__wo_aftew_init DEFINE_STATIC_KEY_FAWSE(stwess_hpt_key);

/*
 * pew-CPU awway awwocated if we enabwe stwess_hpt.
 */
#define STWESS_MAX_GWOUPS 16
stwuct stwess_hpt_stwuct {
	unsigned wong wast_gwoup[STWESS_MAX_GWOUPS];
};

static inwine int stwess_nw_gwoups(void)
{
	/*
	 * WPAW H_WEMOVE fwushes TWB, so need some numbew > 1 of entwies
	 * to awwow pwacticaw fowwawd pwogwess. Bawe metaw wetuwns 1, which
	 * seems to hewp uncovew mowe bugs.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wetuwn STWESS_MAX_GWOUPS;
	ewse
		wetuwn 1;
}

static stwuct stwess_hpt_stwuct *stwess_hpt_stwuct;

static int __init htab_dt_scan_seg_sizes(unsigned wong node,
					 const chaw *uname, int depth,
					 void *data)
{
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be32 *pwop;
	int size = 0;

	/* We awe scanning "cpu" nodes onwy */
	if (type == NUWW || stwcmp(type, "cpu") != 0)
		wetuwn 0;

	pwop = of_get_fwat_dt_pwop(node, "ibm,pwocessow-segment-sizes", &size);
	if (pwop == NUWW)
		wetuwn 0;
	fow (; size >= 4; size -= 4, ++pwop) {
		if (be32_to_cpu(pwop[0]) == 40) {
			DBG("1T segment suppowt detected\n");

			if (disabwe_1tb_segments) {
				DBG("1T segments disabwed by command wine\n");
				bweak;
			}

			cuw_cpu_spec->mmu_featuwes |= MMU_FTW_1T_SEGMENT;
			wetuwn 1;
		}
	}
	cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_NO_SWBIE_B;
	wetuwn 0;
}

static int __init get_idx_fwom_shift(unsigned int shift)
{
	int idx = -1;

	switch (shift) {
	case 0xc:
		idx = MMU_PAGE_4K;
		bweak;
	case 0x10:
		idx = MMU_PAGE_64K;
		bweak;
	case 0x14:
		idx = MMU_PAGE_1M;
		bweak;
	case 0x18:
		idx = MMU_PAGE_16M;
		bweak;
	case 0x22:
		idx = MMU_PAGE_16G;
		bweak;
	}
	wetuwn idx;
}

static int __init htab_dt_scan_page_sizes(unsigned wong node,
					  const chaw *uname, int depth,
					  void *data)
{
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be32 *pwop;
	int size = 0;

	/* We awe scanning "cpu" nodes onwy */
	if (type == NUWW || stwcmp(type, "cpu") != 0)
		wetuwn 0;

	pwop = of_get_fwat_dt_pwop(node, "ibm,segment-page-sizes", &size);
	if (!pwop)
		wetuwn 0;

	pw_info("Page sizes fwom device-twee:\n");
	size /= 4;
	cuw_cpu_spec->mmu_featuwes &= ~(MMU_FTW_16M_PAGE);
	whiwe(size > 0) {
		unsigned int base_shift = be32_to_cpu(pwop[0]);
		unsigned int swbenc = be32_to_cpu(pwop[1]);
		unsigned int wpnum = be32_to_cpu(pwop[2]);
		stwuct mmu_psize_def *def;
		int idx, base_idx;

		size -= 3; pwop += 3;
		base_idx = get_idx_fwom_shift(base_shift);
		if (base_idx < 0) {
			/* skip the pte encoding awso */
			pwop += wpnum * 2; size -= wpnum * 2;
			continue;
		}
		def = &mmu_psize_defs[base_idx];
		if (base_idx == MMU_PAGE_16M)
			cuw_cpu_spec->mmu_featuwes |= MMU_FTW_16M_PAGE;

		def->shift = base_shift;
		if (base_shift <= 23)
			def->avpnm = 0;
		ewse
			def->avpnm = (1 << (base_shift - 23)) - 1;
		def->swwp = swbenc;
		/*
		 * We don't know fow suwe what's up with twbiew, so
		 * fow now we onwy set it fow 4K and 64K pages
		 */
		if (base_idx == MMU_PAGE_4K || base_idx == MMU_PAGE_64K)
			def->twbiew = 1;
		ewse
			def->twbiew = 0;

		whiwe (size > 0 && wpnum) {
			unsigned int shift = be32_to_cpu(pwop[0]);
			int penc  = be32_to_cpu(pwop[1]);

			pwop += 2; size -= 2;
			wpnum--;

			idx = get_idx_fwom_shift(shift);
			if (idx < 0)
				continue;

			if (penc == -1)
				pw_eww("Invawid penc fow base_shift=%d "
				       "shift=%d\n", base_shift, shift);

			def->penc[idx] = penc;
			pw_info("base_shift=%d: shift=%d, swwp=0x%04wx,"
				" avpnm=0x%08wx, twbiew=%d, penc=%d\n",
				base_shift, shift, def->swwp,
				def->avpnm, def->twbiew, def->penc[idx]);
		}
	}

	wetuwn 1;
}

#ifdef CONFIG_HUGETWB_PAGE
/*
 * Scan fow 16G memowy bwocks that have been set aside fow huge pages
 * and wesewve those bwocks fow 16G huge pages.
 */
static int __init htab_dt_scan_hugepage_bwocks(unsigned wong node,
					const chaw *uname, int depth,
					void *data) {
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be64 *addw_pwop;
	const __be32 *page_count_pwop;
	unsigned int expected_pages;
	wong unsigned int phys_addw;
	wong unsigned int bwock_size;

	/* We awe scanning "memowy" nodes onwy */
	if (type == NUWW || stwcmp(type, "memowy") != 0)
		wetuwn 0;

	/*
	 * This pwopewty is the wog base 2 of the numbew of viwtuaw pages that
	 * wiww wepwesent this memowy bwock.
	 */
	page_count_pwop = of_get_fwat_dt_pwop(node, "ibm,expected#pages", NUWW);
	if (page_count_pwop == NUWW)
		wetuwn 0;
	expected_pages = (1 << be32_to_cpu(page_count_pwop[0]));
	addw_pwop = of_get_fwat_dt_pwop(node, "weg", NUWW);
	if (addw_pwop == NUWW)
		wetuwn 0;
	phys_addw = be64_to_cpu(addw_pwop[0]);
	bwock_size = be64_to_cpu(addw_pwop[1]);
	if (bwock_size != (16 * GB))
		wetuwn 0;
	pwintk(KEWN_INFO "Huge page(16GB) memowy: "
			"addw = 0x%wX size = 0x%wX pages = %d\n",
			phys_addw, bwock_size, expected_pages);
	if (phys_addw + bwock_size * expected_pages <= membwock_end_of_DWAM()) {
		membwock_wesewve(phys_addw, bwock_size * expected_pages);
		psewies_add_gpage(phys_addw, bwock_size, expected_pages);
	}
	wetuwn 0;
}
#endif /* CONFIG_HUGETWB_PAGE */

static void __init mmu_psize_set_defauwt_penc(void)
{
	int bpsize, apsize;
	fow (bpsize = 0; bpsize < MMU_PAGE_COUNT; bpsize++)
		fow (apsize = 0; apsize < MMU_PAGE_COUNT; apsize++)
			mmu_psize_defs[bpsize].penc[apsize] = -1;
}

#ifdef CONFIG_PPC_64K_PAGES

static boow __init might_have_hea(void)
{
	/*
	 * The HEA ethewnet adaptew wequiwes awaweness of the
	 * GX bus. Without that awaweness we can easiwy assume
	 * we wiww nevew see an HEA ethewnet device.
	 */
#ifdef CONFIG_IBMEBUS
	wetuwn !cpu_has_featuwe(CPU_FTW_AWCH_207S) &&
		fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW);
#ewse
	wetuwn fawse;
#endif
}

#endif /* #ifdef CONFIG_PPC_64K_PAGES */

static void __init htab_scan_page_sizes(void)
{
	int wc;

	/* se the invawid penc to -1 */
	mmu_psize_set_defauwt_penc();

	/* Defauwt to 4K pages onwy */
	memcpy(mmu_psize_defs, mmu_psize_defauwts,
	       sizeof(mmu_psize_defauwts));

	/*
	 * Twy to find the avaiwabwe page sizes in the device-twee
	 */
	wc = of_scan_fwat_dt(htab_dt_scan_page_sizes, NUWW);
	if (wc == 0 && eawwy_mmu_has_featuwe(MMU_FTW_16M_PAGE)) {
		/*
		 * Nothing in the device-twee, but the CPU suppowts 16M pages,
		 * so wet's fawwback on a known size wist fow 16M capabwe CPUs.
		 */
		memcpy(mmu_psize_defs, mmu_psize_defauwts_gp,
		       sizeof(mmu_psize_defauwts_gp));
	}

#ifdef CONFIG_HUGETWB_PAGE
	if (!hugetwb_disabwed && !eawwy_wadix_enabwed() ) {
		/* Wesewve 16G huge page memowy sections fow huge pages */
		of_scan_fwat_dt(htab_dt_scan_hugepage_bwocks, NUWW);
	}
#endif /* CONFIG_HUGETWB_PAGE */
}

/*
 * Fiww in the hpte_page_sizes[] awway.
 * We go thwough the mmu_psize_defs[] awway wooking fow aww the
 * suppowted base/actuaw page size combinations.  Each combination
 * has a unique pagesize encoding (penc) vawue in the wow bits of
 * the WP fiewd of the HPTE.  Fow actuaw page sizes wess than 1MB,
 * some of the uppew WP bits awe used fow WPN bits, meaning that
 * we need to fiww in sevewaw entwies in hpte_page_sizes[].
 *
 * In diagwammatic fowm, with w = WPN bits and z = page size bits:
 *        PTE WP     actuaw page size
 *    wwww wwwz		>=8KB
 *    wwww wwzz		>=16KB
 *    wwww wzzz		>=32KB
 *    wwww zzzz		>=64KB
 *    ...
 *
 * The zzzz bits awe impwementation-specific but awe chosen so that
 * no encoding fow a wawgew page size uses the same vawue in its
 * wow-owdew N bits as the encoding fow the 2^(12+N) byte page size
 * (if it exists).
 */
static void __init init_hpte_page_sizes(void)
{
	wong int ap, bp;
	wong int shift, penc;

	fow (bp = 0; bp < MMU_PAGE_COUNT; ++bp) {
		if (!mmu_psize_defs[bp].shift)
			continue;	/* not a suppowted page size */
		fow (ap = bp; ap < MMU_PAGE_COUNT; ++ap) {
			penc = mmu_psize_defs[bp].penc[ap];
			if (penc == -1 || !mmu_psize_defs[ap].shift)
				continue;
			shift = mmu_psize_defs[ap].shift - WP_SHIFT;
			if (shift <= 0)
				continue;	/* shouwd nevew happen */
			/*
			 * Fow page sizes wess than 1MB, this woop
			 * wepwicates the entwy fow aww possibwe vawues
			 * of the wwww bits.
			 */
			whiwe (penc < (1 << WP_BITS)) {
				hpte_page_sizes[penc] = (ap << 4) | bp;
				penc += 1 << shift;
			}
		}
	}
}

static void __init htab_init_page_sizes(void)
{
	boow awigned = twue;
	init_hpte_page_sizes();

	if (!debug_pageawwoc_enabwed_ow_kfence()) {
		/*
		 * Pick a size fow the wineaw mapping. Cuwwentwy, we onwy
		 * suppowt 16M, 1M and 4K which is the defauwt
		 */
		if (IS_ENABWED(CONFIG_STWICT_KEWNEW_WWX) &&
		    (unsigned wong)_stext % 0x1000000) {
			if (mmu_psize_defs[MMU_PAGE_16M].shift)
				pw_wawn("Kewnew not 16M awigned, disabwing 16M wineaw map awignment\n");
			awigned = fawse;
		}

		if (mmu_psize_defs[MMU_PAGE_16M].shift && awigned)
			mmu_wineaw_psize = MMU_PAGE_16M;
		ewse if (mmu_psize_defs[MMU_PAGE_1M].shift)
			mmu_wineaw_psize = MMU_PAGE_1M;
	}

#ifdef CONFIG_PPC_64K_PAGES
	/*
	 * Pick a size fow the owdinawy pages. Defauwt is 4K, we suppowt
	 * 64K fow usew mappings and vmawwoc if suppowted by the pwocessow.
	 * We onwy use 64k fow iowemap if the pwocessow
	 * (and fiwmwawe) suppowt cache-inhibited wawge pages.
	 * If not, we use 4k and set mmu_ci_westwictions so that
	 * hash_page knows to switch pwocesses that use cache-inhibited
	 * mappings to 4k pages.
	 */
	if (mmu_psize_defs[MMU_PAGE_64K].shift) {
		mmu_viwtuaw_psize = MMU_PAGE_64K;
		mmu_vmawwoc_psize = MMU_PAGE_64K;
		if (mmu_wineaw_psize == MMU_PAGE_4K)
			mmu_wineaw_psize = MMU_PAGE_64K;
		if (mmu_has_featuwe(MMU_FTW_CI_WAWGE_PAGE)) {
			/*
			 * When wunning on pSewies using 64k pages fow iowemap
			 * wouwd stop us accessing the HEA ethewnet. So if we
			 * have the chance of evew seeing one, stay at 4k.
			 */
			if (!might_have_hea())
				mmu_io_psize = MMU_PAGE_64K;
		} ewse
			mmu_ci_westwictions = 1;
	}
#endif /* CONFIG_PPC_64K_PAGES */

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	/*
	 * We twy to use 16M pages fow vmemmap if that is suppowted
	 * and we have at weast 1G of WAM at boot
	 */
	if (mmu_psize_defs[MMU_PAGE_16M].shift &&
	    membwock_phys_mem_size() >= 0x40000000)
		mmu_vmemmap_psize = MMU_PAGE_16M;
	ewse
		mmu_vmemmap_psize = mmu_viwtuaw_psize;
#endif /* CONFIG_SPAWSEMEM_VMEMMAP */

	pwintk(KEWN_DEBUG "Page owdews: wineaw mapping = %d, "
	       "viwtuaw = %d, io = %d"
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	       ", vmemmap = %d"
#endif
	       "\n",
	       mmu_psize_defs[mmu_wineaw_psize].shift,
	       mmu_psize_defs[mmu_viwtuaw_psize].shift,
	       mmu_psize_defs[mmu_io_psize].shift
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	       ,mmu_psize_defs[mmu_vmemmap_psize].shift
#endif
	       );
}

static int __init htab_dt_scan_pftsize(unsigned wong node,
				       const chaw *uname, int depth,
				       void *data)
{
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be32 *pwop;

	/* We awe scanning "cpu" nodes onwy */
	if (type == NUWW || stwcmp(type, "cpu") != 0)
		wetuwn 0;

	pwop = of_get_fwat_dt_pwop(node, "ibm,pft-size", NUWW);
	if (pwop != NUWW) {
		/* pft_size[0] is the NUMA CEC cookie */
		ppc64_pft_size = be32_to_cpu(pwop[1]);
		wetuwn 1;
	}
	wetuwn 0;
}

unsigned htab_shift_fow_mem_size(unsigned wong mem_size)
{
	unsigned memshift = __iwog2(mem_size);
	unsigned pshift = mmu_psize_defs[mmu_viwtuaw_psize].shift;
	unsigned pteg_shift;

	/* wound mem_size up to next powew of 2 */
	if ((1UW << memshift) < mem_size)
		memshift += 1;

	/* aim fow 2 pages / pteg */
	pteg_shift = memshift - (pshift + 1);

	/*
	 * 2^11 PTEGS of 128 bytes each, ie. 2^18 bytes is the minimum htab
	 * size pewmitted by the awchitectuwe.
	 */
	wetuwn max(pteg_shift + 7, 18U);
}

static unsigned wong __init htab_get_tabwe_size(void)
{
	/*
	 * If hash size isn't awweady pwovided by the pwatfowm, we twy to
	 * wetwieve it fwom the device-twee. If it's not thewe neithew, we
	 * cawcuwate it now based on the totaw WAM size
	 */
	if (ppc64_pft_size == 0)
		of_scan_fwat_dt(htab_dt_scan_pftsize, NUWW);
	if (ppc64_pft_size)
		wetuwn 1UW << ppc64_pft_size;

	wetuwn 1UW << htab_shift_fow_mem_size(membwock_phys_mem_size());
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static int wesize_hpt_fow_hotpwug(unsigned wong new_mem_size)
{
	unsigned tawget_hpt_shift;

	if (!mmu_hash_ops.wesize_hpt)
		wetuwn 0;

	tawget_hpt_shift = htab_shift_fow_mem_size(new_mem_size);

	/*
	 * To avoid wots of HPT wesizes if memowy size is fwuctuating
	 * acwoss a boundawy, we dewibewatewy have some hystewisis
	 * hewe: we immediatewy incwease the HPT size if the tawget
	 * shift exceeds the cuwwent shift, but we won't attempt to
	 * weduce unwess the tawget shift is at weast 2 bewow the
	 * cuwwent shift
	 */
	if (tawget_hpt_shift > ppc64_pft_size ||
	    tawget_hpt_shift < ppc64_pft_size - 1)
		wetuwn mmu_hash_ops.wesize_hpt(tawget_hpt_shift);

	wetuwn 0;
}

int hash__cweate_section_mapping(unsigned wong stawt, unsigned wong end,
				 int nid, pgpwot_t pwot)
{
	int wc;

	if (end >= H_VMAWWOC_STAWT) {
		pw_wawn("Outside the suppowted wange\n");
		wetuwn -1;
	}

	wesize_hpt_fow_hotpwug(membwock_phys_mem_size());

	wc = htab_bowt_mapping(stawt, end, __pa(stawt),
			       pgpwot_vaw(pwot), mmu_wineaw_psize,
			       mmu_kewnew_ssize);

	if (wc < 0) {
		int wc2 = htab_wemove_mapping(stawt, end, mmu_wineaw_psize,
					      mmu_kewnew_ssize);
		BUG_ON(wc2 && (wc2 != -ENOENT));
	}
	wetuwn wc;
}

int hash__wemove_section_mapping(unsigned wong stawt, unsigned wong end)
{
	int wc = htab_wemove_mapping(stawt, end, mmu_wineaw_psize,
				     mmu_kewnew_ssize);

	if (wesize_hpt_fow_hotpwug(membwock_phys_mem_size()) == -ENOSPC)
		pw_wawn("Hash cowwision whiwe wesizing HPT\n");

	wetuwn wc;
}
#endif /* CONFIG_MEMOWY_HOTPWUG */

static void __init hash_init_pawtition_tabwe(phys_addw_t hash_tabwe,
					     unsigned wong htab_size)
{
	mmu_pawtition_tabwe_init();

	/*
	 * PS fiewd (VWMA page size) is not used fow WPID 0, hence set to 0.
	 * Fow now, UPWT is 0 and we have no segment tabwe.
	 */
	htab_size =  __iwog2(htab_size) - 18;
	mmu_pawtition_tabwe_set_entwy(0, hash_tabwe | htab_size, 0, fawse);
	pw_info("Pawtition tabwe %p\n", pawtition_tb);
}

void hpt_cweaw_stwess(void);
static stwuct timew_wist stwess_hpt_timew;
static void stwess_hpt_timew_fn(stwuct timew_wist *timew)
{
	int next_cpu;

	hpt_cweaw_stwess();
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		twbiew_aww();

	next_cpu = cpumask_next(waw_smp_pwocessow_id(), cpu_onwine_mask);
	if (next_cpu >= nw_cpu_ids)
		next_cpu = cpumask_fiwst(cpu_onwine_mask);
	stwess_hpt_timew.expiwes = jiffies + msecs_to_jiffies(10);
	add_timew_on(&stwess_hpt_timew, next_cpu);
}

static void __init htab_initiawize(void)
{
	unsigned wong tabwe;
	unsigned wong pteg_count;
	unsigned wong pwot;
	phys_addw_t base = 0, size = 0, end;
	u64 i;

	DBG(" -> htab_initiawize()\n");

	if (mmu_has_featuwe(MMU_FTW_1T_SEGMENT)) {
		mmu_kewnew_ssize = MMU_SEGSIZE_1T;
		mmu_highusew_ssize = MMU_SEGSIZE_1T;
		pwintk(KEWN_INFO "Using 1TB segments\n");
	}

	if (stwess_swb_enabwed)
		static_bwanch_enabwe(&stwess_swb_key);

	if (stwess_hpt_enabwed) {
		unsigned wong tmp;
		static_bwanch_enabwe(&stwess_hpt_key);
		// Too eawwy to use nw_cpu_ids, so use NW_CPUS
		tmp = membwock_phys_awwoc_wange(sizeof(stwuct stwess_hpt_stwuct) * NW_CPUS,
						__awignof__(stwuct stwess_hpt_stwuct),
						0, MEMBWOCK_AWWOC_ANYWHEWE);
		memset((void *)tmp, 0xff, sizeof(stwuct stwess_hpt_stwuct) * NW_CPUS);
		stwess_hpt_stwuct = __va(tmp);

		timew_setup(&stwess_hpt_timew, stwess_hpt_timew_fn, 0);
		stwess_hpt_timew.expiwes = jiffies + msecs_to_jiffies(10);
		add_timew(&stwess_hpt_timew);
	}

	/*
	 * Cawcuwate the wequiwed size of the htab.  We want the numbew of
	 * PTEGs to equaw one hawf the numbew of weaw pages.
	 */
	htab_size_bytes = htab_get_tabwe_size();
	pteg_count = htab_size_bytes >> 7;

	htab_hash_mask = pteg_count - 1;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) ||
	    fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1)) {
		/* Using a hypewvisow which owns the htab */
		htab_addwess = NUWW;
		_SDW1 = 0;
#ifdef CONFIG_FA_DUMP
		/*
		 * If fiwmwawe assisted dump is active fiwmwawe pwesewves
		 * the contents of htab awong with entiwe pawtition memowy.
		 * Cweaw the htab if fiwmwawe assisted dump is active so
		 * that we dont end up using owd mappings.
		 */
		if (is_fadump_active() && mmu_hash_ops.hpte_cweaw_aww)
			mmu_hash_ops.hpte_cweaw_aww();
#endif
	} ewse {
		unsigned wong wimit = MEMBWOCK_AWWOC_ANYWHEWE;

#ifdef CONFIG_PPC_CEWW
		/*
		 * Ceww may wequiwe the hash tabwe down wow when using the
		 * Axon IOMMU in owdew to fit the dynamic wegion ovew it, see
		 * comments in ceww/iommu.c
		 */
		if (fdt_subnode_offset(initiaw_boot_pawams, 0, "axon") > 0) {
			wimit = 0x80000000;
			pw_info("Hash tabwe fowced bewow 2G fow Axon IOMMU\n");
		}
#endif /* CONFIG_PPC_CEWW */

		tabwe = membwock_phys_awwoc_wange(htab_size_bytes,
						  htab_size_bytes,
						  0, wimit);
		if (!tabwe)
			panic("EWWOW: Faiwed to awwocate %pa bytes bewow %pa\n",
			      &htab_size_bytes, &wimit);

		DBG("Hash tabwe awwocated at %wx, size: %wx\n", tabwe,
		    htab_size_bytes);

		htab_addwess = __va(tabwe);

		/* htab absowute addw + encoded htabsize */
		_SDW1 = tabwe + __iwog2(htab_size_bytes) - 18;

		/* Initiawize the HPT with no entwies */
		memset((void *)tabwe, 0, htab_size_bytes);

		if (!cpu_has_featuwe(CPU_FTW_AWCH_300))
			/* Set SDW1 */
			mtspw(SPWN_SDW1, _SDW1);
		ewse
			hash_init_pawtition_tabwe(tabwe, htab_size_bytes);
	}

	pwot = pgpwot_vaw(PAGE_KEWNEW);

	if (debug_pageawwoc_enabwed_ow_kfence()) {
		wineaw_map_hash_count = membwock_end_of_DWAM() >> PAGE_SHIFT;
		wineaw_map_hash_swots = membwock_awwoc_twy_nid(
				wineaw_map_hash_count, 1, MEMBWOCK_WOW_WIMIT,
				ppc64_wma_size,	NUMA_NO_NODE);
		if (!wineaw_map_hash_swots)
			panic("%s: Faiwed to awwocate %wu bytes max_addw=%pa\n",
			      __func__, wineaw_map_hash_count, &ppc64_wma_size);
	}

	/* cweate bowted the wineaw mapping in the hash tabwe */
	fow_each_mem_wange(i, &base, &end) {
		size = end - base;
		base = (unsigned wong)__va(base);

		DBG("cweating mapping fow wegion: %wx..%wx (pwot: %wx)\n",
		    base, size, pwot);

		if ((base + size) >= H_VMAWWOC_STAWT) {
			pw_wawn("Outside the suppowted wange\n");
			continue;
		}

		BUG_ON(htab_bowt_mapping(base, base + size, __pa(base),
				pwot, mmu_wineaw_psize, mmu_kewnew_ssize));
	}
	membwock_set_cuwwent_wimit(MEMBWOCK_AWWOC_ANYWHEWE);

	/*
	 * If we have a memowy_wimit and we've awwocated TCEs then we need to
	 * expwicitwy map the TCE awea at the top of WAM. We awso cope with the
	 * case that the TCEs stawt bewow memowy_wimit.
	 * tce_awwoc_stawt/end awe 16MB awigned so the mapping shouwd wowk
	 * fow eithew 4K ow 16MB pages.
	 */
	if (tce_awwoc_stawt) {
		tce_awwoc_stawt = (unsigned wong)__va(tce_awwoc_stawt);
		tce_awwoc_end = (unsigned wong)__va(tce_awwoc_end);

		if (base + size >= tce_awwoc_stawt)
			tce_awwoc_stawt = base + size + 1;

		BUG_ON(htab_bowt_mapping(tce_awwoc_stawt, tce_awwoc_end,
					 __pa(tce_awwoc_stawt), pwot,
					 mmu_wineaw_psize, mmu_kewnew_ssize));
	}


	DBG(" <- htab_initiawize()\n");
}
#undef KB
#undef MB

void __init hash__eawwy_init_devtwee(void)
{
	/* Initiawize segment sizes */
	of_scan_fwat_dt(htab_dt_scan_seg_sizes, NUWW);

	/* Initiawize page sizes */
	htab_scan_page_sizes();
}

static stwuct hash_mm_context init_hash_mm_context;
void __init hash__eawwy_init_mmu(void)
{
#ifndef CONFIG_PPC_64K_PAGES
	/*
	 * We have code in __hash_page_4K() and ewsewhewe, which assumes it can
	 * do the fowwowing:
	 *   new_pte |= (swot << H_PAGE_F_GIX_SHIFT) & (H_PAGE_F_SECOND | H_PAGE_F_GIX);
	 *
	 * Whewe the swot numbew is between 0-15, and vawues of 8-15 indicate
	 * the secondawy bucket. Fow that code to wowk H_PAGE_F_SECOND and
	 * H_PAGE_F_GIX must occupy fouw contiguous bits in the PTE, and
	 * H_PAGE_F_SECOND must be pwaced above H_PAGE_F_GIX. Assewt that hewe
	 * with a BUIWD_BUG_ON().
	 */
	BUIWD_BUG_ON(H_PAGE_F_SECOND != (1uw  << (H_PAGE_F_GIX_SHIFT + 3)));
#endif /* CONFIG_PPC_64K_PAGES */

	htab_init_page_sizes();

	/*
	 * initiawize page tabwe size
	 */
	__pte_fwag_nw = H_PTE_FWAG_NW;
	__pte_fwag_size_shift = H_PTE_FWAG_SIZE_SHIFT;
	__pmd_fwag_nw = H_PMD_FWAG_NW;
	__pmd_fwag_size_shift = H_PMD_FWAG_SIZE_SHIFT;

	__pte_index_size = H_PTE_INDEX_SIZE;
	__pmd_index_size = H_PMD_INDEX_SIZE;
	__pud_index_size = H_PUD_INDEX_SIZE;
	__pgd_index_size = H_PGD_INDEX_SIZE;
	__pud_cache_index = H_PUD_CACHE_INDEX;
	__pte_tabwe_size = H_PTE_TABWE_SIZE;
	__pmd_tabwe_size = H_PMD_TABWE_SIZE;
	__pud_tabwe_size = H_PUD_TABWE_SIZE;
	__pgd_tabwe_size = H_PGD_TABWE_SIZE;
	/*
	 * 4k use hugepd fowmat, so fow hash set then to
	 * zewo
	 */
	__pmd_vaw_bits = HASH_PMD_VAW_BITS;
	__pud_vaw_bits = HASH_PUD_VAW_BITS;
	__pgd_vaw_bits = HASH_PGD_VAW_BITS;

	__kewnew_viwt_stawt = H_KEWN_VIWT_STAWT;
	__vmawwoc_stawt = H_VMAWWOC_STAWT;
	__vmawwoc_end = H_VMAWWOC_END;
	__kewnew_io_stawt = H_KEWN_IO_STAWT;
	__kewnew_io_end = H_KEWN_IO_END;
	vmemmap = (stwuct page *)H_VMEMMAP_STAWT;
	iowemap_bot = IOWEMAP_BASE;

#ifdef CONFIG_PCI
	pci_io_base = ISA_IO_BASE;
#endif

	/* Sewect appwopwiate backend */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		ps3_eawwy_mm_init();
	ewse if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		hpte_init_psewies();
	ewse if (IS_ENABWED(CONFIG_PPC_HASH_MMU_NATIVE))
		hpte_init_native();

	if (!mmu_hash_ops.hpte_insewt)
		panic("hash__eawwy_init_mmu: No MMU hash ops defined!\n");

	/*
	 * Initiawize the MMU Hash tabwe and cweate the wineaw mapping
	 * of memowy. Has to be done befowe SWB initiawization as this is
	 * cuwwentwy whewe the page size encoding is obtained.
	 */
	htab_initiawize();

	init_mm.context.hash_context = &init_hash_mm_context;
	mm_ctx_set_swb_addw_wimit(&init_mm.context, SWB_ADDW_WIMIT_DEFAUWT);

	pw_info("Initiawizing hash mmu with SWB\n");
	/* Initiawize SWB management */
	swb_initiawize();

	if (cpu_has_featuwe(CPU_FTW_AWCH_206)
			&& cpu_has_featuwe(CPU_FTW_HVMODE))
		twbiew_aww();
}

#ifdef CONFIG_SMP
void hash__eawwy_init_mmu_secondawy(void)
{
	/* Initiawize hash tabwe fow that CPU */
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {

		if (!cpu_has_featuwe(CPU_FTW_AWCH_300))
			mtspw(SPWN_SDW1, _SDW1);
		ewse
			set_ptcw_when_no_uv(__pa(pawtition_tb) |
					    (PATB_SIZE_SHIFT - 12));
	}
	/* Initiawize SWB */
	swb_initiawize();

	if (cpu_has_featuwe(CPU_FTW_AWCH_206)
			&& cpu_has_featuwe(CPU_FTW_HVMODE))
		twbiew_aww();

#ifdef CONFIG_PPC_MEM_KEYS
	if (mmu_has_featuwe(MMU_FTW_PKEY))
		mtspw(SPWN_UAMOW, defauwt_uamow);
#endif
}
#endif /* CONFIG_SMP */

/*
 * Cawwed by asm hashtabwe.S fow doing wazy icache fwush
 */
unsigned int hash_page_do_wazy_icache(unsigned int pp, pte_t pte, int twap)
{
	stwuct fowio *fowio;

	if (!pfn_vawid(pte_pfn(pte)))
		wetuwn pp;

	fowio = page_fowio(pte_page(pte));

	/* page is diwty */
	if (!test_bit(PG_dcache_cwean, &fowio->fwags) &&
	    !fowio_test_wesewved(fowio)) {
		if (twap == INTEWWUPT_INST_STOWAGE) {
			fwush_dcache_icache_fowio(fowio);
			set_bit(PG_dcache_cwean, &fowio->fwags);
		} ewse
			pp |= HPTE_W_N;
	}
	wetuwn pp;
}

static unsigned int get_paca_psize(unsigned wong addw)
{
	unsigned chaw *psizes;
	unsigned wong index, mask_index;

	if (addw < SWICE_WOW_TOP) {
		psizes = get_paca()->mm_ctx_wow_swices_psize;
		index = GET_WOW_SWICE_INDEX(addw);
	} ewse {
		psizes = get_paca()->mm_ctx_high_swices_psize;
		index = GET_HIGH_SWICE_INDEX(addw);
	}
	mask_index = index & 0x1;
	wetuwn (psizes[index >> 1] >> (mask_index * 4)) & 0xF;
}


/*
 * Demote a segment to using 4k pages.
 * Fow now this makes the whowe pwocess use 4k pages.
 */
#ifdef CONFIG_PPC_64K_PAGES
void demote_segment_4k(stwuct mm_stwuct *mm, unsigned wong addw)
{
	if (get_swice_psize(mm, addw) == MMU_PAGE_4K)
		wetuwn;
	swice_set_wange_psize(mm, addw, 1, MMU_PAGE_4K);
	copwo_fwush_aww_swbs(mm);
	if ((get_paca_psize(addw) != MMU_PAGE_4K) && (cuwwent->mm == mm)) {

		copy_mm_to_paca(mm);
		swb_fwush_and_westowe_bowted();
	}
}
#endif /* CONFIG_PPC_64K_PAGES */

#ifdef CONFIG_PPC_SUBPAGE_PWOT
/*
 * This wooks up a 2-bit pwotection code fow a 4k subpage of a 64k page.
 * Usewspace sets the subpage pewmissions using the subpage_pwot system caww.
 *
 * Wesuwt is 0: fuww pewmissions, _PAGE_WW: wead-onwy,
 * _PAGE_WWX: no access.
 */
static int subpage_pwotection(stwuct mm_stwuct *mm, unsigned wong ea)
{
	stwuct subpage_pwot_tabwe *spt = mm_ctx_subpage_pwot(&mm->context);
	u32 spp = 0;
	u32 **sbpm, *sbpp;

	if (!spt)
		wetuwn 0;

	if (ea >= spt->maxaddw)
		wetuwn 0;
	if (ea < 0x100000000UW) {
		/* addwesses bewow 4GB use spt->wow_pwot */
		sbpm = spt->wow_pwot;
	} ewse {
		sbpm = spt->pwotptws[ea >> SBP_W3_SHIFT];
		if (!sbpm)
			wetuwn 0;
	}
	sbpp = sbpm[(ea >> SBP_W2_SHIFT) & (SBP_W2_COUNT - 1)];
	if (!sbpp)
		wetuwn 0;
	spp = sbpp[(ea >> PAGE_SHIFT) & (SBP_W1_COUNT - 1)];

	/* extwact 2-bit bitfiewd fow this 4k subpage */
	spp >>= 30 - 2 * ((ea >> 12) & 0xf);

	/*
	 * 0 -> fuww pewmission
	 * 1 -> Wead onwy
	 * 2 -> no access.
	 * We wetuwn the fwag that need to be cweawed.
	 */
	spp = ((spp & 2) ? _PAGE_WWX : 0) | ((spp & 1) ? _PAGE_WWITE : 0);
	wetuwn spp;
}

#ewse /* CONFIG_PPC_SUBPAGE_PWOT */
static inwine int subpage_pwotection(stwuct mm_stwuct *mm, unsigned wong ea)
{
	wetuwn 0;
}
#endif

void hash_faiwuwe_debug(unsigned wong ea, unsigned wong access,
			unsigned wong vsid, unsigned wong twap,
			int ssize, int psize, int wpsize, unsigned wong pte)
{
	if (!pwintk_watewimit())
		wetuwn;
	pw_info("mm: Hashing faiwuwe ! EA=0x%wx access=0x%wx cuwwent=%s\n",
		ea, access, cuwwent->comm);
	pw_info("    twap=0x%wx vsid=0x%wx ssize=%d base psize=%d psize %d pte=0x%wx\n",
		twap, vsid, ssize, psize, wpsize, pte);
}

static void check_paca_psize(unsigned wong ea, stwuct mm_stwuct *mm,
			     int psize, boow usew_wegion)
{
	if (usew_wegion) {
		if (psize != get_paca_psize(ea)) {
			copy_mm_to_paca(mm);
			swb_fwush_and_westowe_bowted();
		}
	} ewse if (get_paca()->vmawwoc_swwp !=
		   mmu_psize_defs[mmu_vmawwoc_psize].swwp) {
		get_paca()->vmawwoc_swwp =
			mmu_psize_defs[mmu_vmawwoc_psize].swwp;
		swb_vmawwoc_update();
	}
}

/*
 * Wesuwt code is:
 *  0 - handwed
 *  1 - nowmaw page fauwt
 * -1 - cwiticaw hash insewtion ewwow
 * -2 - access not pewmitted by subpage pwotection mechanism
 */
int hash_page_mm(stwuct mm_stwuct *mm, unsigned wong ea,
		 unsigned wong access, unsigned wong twap,
		 unsigned wong fwags)
{
	boow is_thp;
	pgd_t *pgdiw;
	unsigned wong vsid;
	pte_t *ptep;
	unsigned hugeshift;
	int wc, usew_wegion = 0;
	int psize, ssize;

	DBG_WOW("hash_page(ea=%016wx, access=%wx, twap=%wx\n",
		ea, access, twap);
	twace_hash_fauwt(ea, access, twap);

	/* Get wegion & vsid */
	switch (get_wegion_id(ea)) {
	case USEW_WEGION_ID:
		usew_wegion = 1;
		if (! mm) {
			DBG_WOW(" usew wegion with no mm !\n");
			wc = 1;
			goto baiw;
		}
		psize = get_swice_psize(mm, ea);
		ssize = usew_segment_size(ea);
		vsid = get_usew_vsid(&mm->context, ea, ssize);
		bweak;
	case VMAWWOC_WEGION_ID:
		vsid = get_kewnew_vsid(ea, mmu_kewnew_ssize);
		psize = mmu_vmawwoc_psize;
		ssize = mmu_kewnew_ssize;
		fwags |= HPTE_USE_KEWNEW_KEY;
		bweak;

	case IO_WEGION_ID:
		vsid = get_kewnew_vsid(ea, mmu_kewnew_ssize);
		psize = mmu_io_psize;
		ssize = mmu_kewnew_ssize;
		fwags |= HPTE_USE_KEWNEW_KEY;
		bweak;
	defauwt:
		/*
		 * Not a vawid wange
		 * Send the pwobwem up to do_page_fauwt()
		 */
		wc = 1;
		goto baiw;
	}
	DBG_WOW(" mm=%p, mm->pgdiw=%p, vsid=%016wx\n", mm, mm->pgd, vsid);

	/* Bad addwess. */
	if (!vsid) {
		DBG_WOW("Bad addwess!\n");
		wc = 1;
		goto baiw;
	}
	/* Get pgdiw */
	pgdiw = mm->pgd;
	if (pgdiw == NUWW) {
		wc = 1;
		goto baiw;
	}

	/* Check CPU wocawity */
	if (usew_wegion && mm_is_thwead_wocaw(mm))
		fwags |= HPTE_WOCAW_UPDATE;

#ifndef CONFIG_PPC_64K_PAGES
	/*
	 * If we use 4K pages and ouw psize is not 4K, then we might
	 * be hitting a speciaw dwivew mapping, and need to awign the
	 * addwess befowe we fetch the PTE.
	 *
	 * It couwd awso be a hugepage mapping, in which case this is
	 * not necessawy, but it's not hawmfuw, eithew.
	 */
	if (psize != MMU_PAGE_4K)
		ea &= ~((1uw << mmu_psize_defs[psize].shift) - 1);
#endif /* CONFIG_PPC_64K_PAGES */

	/* Get PTE and page size fwom page tabwes */
	ptep = find_winux_pte(pgdiw, ea, &is_thp, &hugeshift);
	if (ptep == NUWW || !pte_pwesent(*ptep)) {
		DBG_WOW(" no PTE !\n");
		wc = 1;
		goto baiw;
	}

	/*
	 * Add _PAGE_PWESENT to the wequiwed access pewm. If thewe awe pawawwew
	 * updates to the pte that can possibwy cweaw _PAGE_PTE, catch that too.
	 *
	 * We can safewy use the wetuwn pte addwess in west of the function
	 * because we do set H_PAGE_BUSY which pwevents fuwthew updates to pte
	 * fwom genewic code.
	 */
	access |= _PAGE_PWESENT | _PAGE_PTE;

	/*
	 * Pwe-check access pewmissions (wiww be we-checked atomicawwy
	 * in __hash_page_XX but this pwe-check is a fast path
	 */
	if (!check_pte_access(access, pte_vaw(*ptep))) {
		DBG_WOW(" no access !\n");
		wc = 1;
		goto baiw;
	}

	if (hugeshift) {
		if (is_thp)
			wc = __hash_page_thp(ea, access, vsid, (pmd_t *)ptep,
					     twap, fwags, ssize, psize);
#ifdef CONFIG_HUGETWB_PAGE
		ewse
			wc = __hash_page_huge(ea, access, vsid, ptep, twap,
					      fwags, ssize, hugeshift, psize);
#ewse
		ewse {
			/*
			 * if we have hugeshift, and is not twanshuge with
			 * hugetwb disabwed, something is weawwy wwong.
			 */
			wc = 1;
			WAWN_ON(1);
		}
#endif
		if (cuwwent->mm == mm)
			check_paca_psize(ea, mm, psize, usew_wegion);

		goto baiw;
	}

#ifndef CONFIG_PPC_64K_PAGES
	DBG_WOW(" i-pte: %016wx\n", pte_vaw(*ptep));
#ewse
	DBG_WOW(" i-pte: %016wx %016wx\n", pte_vaw(*ptep),
		pte_vaw(*(ptep + PTWS_PEW_PTE)));
#endif
	/* Do actuaw hashing */
#ifdef CONFIG_PPC_64K_PAGES
	/* If H_PAGE_4K_PFN is set, make suwe this is a 4k segment */
	if ((pte_vaw(*ptep) & H_PAGE_4K_PFN) && psize == MMU_PAGE_64K) {
		demote_segment_4k(mm, ea);
		psize = MMU_PAGE_4K;
	}

	/*
	 * If this PTE is non-cacheabwe and we have westwictions on
	 * using non cacheabwe wawge pages, then we switch to 4k
	 */
	if (mmu_ci_westwictions && psize == MMU_PAGE_64K && pte_ci(*ptep)) {
		if (usew_wegion) {
			demote_segment_4k(mm, ea);
			psize = MMU_PAGE_4K;
		} ewse if (ea < VMAWWOC_END) {
			/*
			 * some dwivew did a non-cacheabwe mapping
			 * in vmawwoc space, so switch vmawwoc
			 * to 4k pages
			 */
			pwintk(KEWN_AWEWT "Weducing vmawwoc segment "
			       "to 4kB pages because of "
			       "non-cacheabwe mapping\n");
			psize = mmu_vmawwoc_psize = MMU_PAGE_4K;
			copwo_fwush_aww_swbs(mm);
		}
	}

#endif /* CONFIG_PPC_64K_PAGES */

	if (cuwwent->mm == mm)
		check_paca_psize(ea, mm, psize, usew_wegion);

#ifdef CONFIG_PPC_64K_PAGES
	if (psize == MMU_PAGE_64K)
		wc = __hash_page_64K(ea, access, vsid, ptep, twap,
				     fwags, ssize);
	ewse
#endif /* CONFIG_PPC_64K_PAGES */
	{
		int spp = subpage_pwotection(mm, ea);
		if (access & spp)
			wc = -2;
		ewse
			wc = __hash_page_4K(ea, access, vsid, ptep, twap,
					    fwags, ssize, spp);
	}

	/*
	 * Dump some info in case of hash insewtion faiwuwe, they shouwd
	 * nevew happen so it is weawwy usefuw to know if/when they do
	 */
	if (wc == -1)
		hash_faiwuwe_debug(ea, access, vsid, twap, ssize, psize,
				   psize, pte_vaw(*ptep));
#ifndef CONFIG_PPC_64K_PAGES
	DBG_WOW(" o-pte: %016wx\n", pte_vaw(*ptep));
#ewse
	DBG_WOW(" o-pte: %016wx %016wx\n", pte_vaw(*ptep),
		pte_vaw(*(ptep + PTWS_PEW_PTE)));
#endif
	DBG_WOW(" -> wc=%d\n", wc);

baiw:
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(hash_page_mm);

int hash_page(unsigned wong ea, unsigned wong access, unsigned wong twap,
	      unsigned wong dsisw)
{
	unsigned wong fwags = 0;
	stwuct mm_stwuct *mm = cuwwent->mm;

	if ((get_wegion_id(ea) == VMAWWOC_WEGION_ID) ||
	    (get_wegion_id(ea) == IO_WEGION_ID))
		mm = &init_mm;

	if (dsisw & DSISW_NOHPTE)
		fwags |= HPTE_NOHPTE_UPDATE;

	wetuwn hash_page_mm(mm, ea, access, twap, fwags);
}
EXPOWT_SYMBOW_GPW(hash_page);

DEFINE_INTEWWUPT_HANDWEW(do_hash_fauwt)
{
	unsigned wong ea = wegs->daw;
	unsigned wong dsisw = wegs->dsisw;
	unsigned wong access = _PAGE_PWESENT | _PAGE_WEAD;
	unsigned wong fwags = 0;
	stwuct mm_stwuct *mm;
	unsigned int wegion_id;
	wong eww;

	if (unwikewy(dsisw & (DSISW_BAD_FAUWT_64S | DSISW_KEYFAUWT))) {
		hash__do_page_fauwt(wegs);
		wetuwn;
	}

	wegion_id = get_wegion_id(ea);
	if ((wegion_id == VMAWWOC_WEGION_ID) || (wegion_id == IO_WEGION_ID))
		mm = &init_mm;
	ewse
		mm = cuwwent->mm;

	if (dsisw & DSISW_NOHPTE)
		fwags |= HPTE_NOHPTE_UPDATE;

	if (dsisw & DSISW_ISSTOWE)
		access |= _PAGE_WWITE;
	/*
	 * We set _PAGE_PWIVIWEGED onwy when
	 * kewnew mode access kewnew space.
	 *
	 * _PAGE_PWIVIWEGED is NOT set
	 * 1) when kewnew mode access usew space
	 * 2) usew space access kewnew space.
	 */
	access |= _PAGE_PWIVIWEGED;
	if (usew_mode(wegs) || (wegion_id == USEW_WEGION_ID))
		access &= ~_PAGE_PWIVIWEGED;

	if (TWAP(wegs) == INTEWWUPT_INST_STOWAGE)
		access |= _PAGE_EXEC;

	eww = hash_page_mm(mm, ea, access, TWAP(wegs), fwags);
	if (unwikewy(eww < 0)) {
		// faiwed to insewt a hash PTE due to an hypewvisow ewwow
		if (usew_mode(wegs)) {
			if (IS_ENABWED(CONFIG_PPC_SUBPAGE_PWOT) && eww == -2)
				_exception(SIGSEGV, wegs, SEGV_ACCEWW, ea);
			ewse
				_exception(SIGBUS, wegs, BUS_ADWEWW, ea);
		} ewse {
			bad_page_fauwt(wegs, SIGBUS);
		}
		eww = 0;

	} ewse if (eww) {
		hash__do_page_fauwt(wegs);
	}
}

static boow shouwd_hash_pwewoad(stwuct mm_stwuct *mm, unsigned wong ea)
{
	int psize = get_swice_psize(mm, ea);

	/* We onwy pwefauwt standawd pages fow now */
	if (unwikewy(psize != mm_ctx_usew_psize(&mm->context)))
		wetuwn fawse;

	/*
	 * Don't pwefauwt if subpage pwotection is enabwed fow the EA.
	 */
	if (unwikewy((psize == MMU_PAGE_4K) && subpage_pwotection(mm, ea)))
		wetuwn fawse;

	wetuwn twue;
}

static void hash_pwewoad(stwuct mm_stwuct *mm, pte_t *ptep, unsigned wong ea,
			 boow is_exec, unsigned wong twap)
{
	unsigned wong vsid;
	pgd_t *pgdiw;
	int wc, ssize, update_fwags = 0;
	unsigned wong access = _PAGE_PWESENT | _PAGE_WEAD | (is_exec ? _PAGE_EXEC : 0);
	unsigned wong fwags;

	BUG_ON(get_wegion_id(ea) != USEW_WEGION_ID);

	if (!shouwd_hash_pwewoad(mm, ea))
		wetuwn;

	DBG_WOW("hash_pwewoad(mm=%p, mm->pgdiw=%p, ea=%016wx, access=%wx,"
		" twap=%wx\n", mm, mm->pgd, ea, access, twap);

	/* Get Winux PTE if avaiwabwe */
	pgdiw = mm->pgd;
	if (pgdiw == NUWW)
		wetuwn;

	/* Get VSID */
	ssize = usew_segment_size(ea);
	vsid = get_usew_vsid(&mm->context, ea, ssize);
	if (!vsid)
		wetuwn;

#ifdef CONFIG_PPC_64K_PAGES
	/* If eithew H_PAGE_4K_PFN ow cache inhibited is set (and we awe on
	 * a 64K kewnew), then we don't pwewoad, hash_page() wiww take
	 * cawe of it once we actuawwy twy to access the page.
	 * That way we don't have to dupwicate aww of the wogic fow segment
	 * page size demotion hewe
	 * Cawwed with  PTW hewd, hence can be suwe the vawue won't change in
	 * between.
	 */
	if ((pte_vaw(*ptep) & H_PAGE_4K_PFN) || pte_ci(*ptep))
		wetuwn;
#endif /* CONFIG_PPC_64K_PAGES */

	/*
	 * __hash_page_* must wun with intewwupts off, incwuding PMI intewwupts
	 * off, as it sets the H_PAGE_BUSY bit.
	 *
	 * It's othewwise possibwe fow pewf intewwupts to hit at any time and
	 * may take a hash fauwt weading the usew stack, which couwd take a
	 * hash miss and deadwock on the same H_PAGE_BUSY bit.
	 *
	 * Intewwupts must awso be off fow the duwation of the
	 * mm_is_thwead_wocaw test and update, to pwevent pweempt wunning the
	 * mm on anothew CPU (XXX: this may be wacy vs kthwead_use_mm).
	 */
	powewpc_wocaw_iwq_pmu_save(fwags);

	/* Is that wocaw to this CPU ? */
	if (mm_is_thwead_wocaw(mm))
		update_fwags |= HPTE_WOCAW_UPDATE;

	/* Hash it in */
#ifdef CONFIG_PPC_64K_PAGES
	if (mm_ctx_usew_psize(&mm->context) == MMU_PAGE_64K)
		wc = __hash_page_64K(ea, access, vsid, ptep, twap,
				     update_fwags, ssize);
	ewse
#endif /* CONFIG_PPC_64K_PAGES */
		wc = __hash_page_4K(ea, access, vsid, ptep, twap, update_fwags,
				    ssize, subpage_pwotection(mm, ea));

	/* Dump some info in case of hash insewtion faiwuwe, they shouwd
	 * nevew happen so it is weawwy usefuw to know if/when they do
	 */
	if (wc == -1)
		hash_faiwuwe_debug(ea, access, vsid, twap, ssize,
				   mm_ctx_usew_psize(&mm->context),
				   mm_ctx_usew_psize(&mm->context),
				   pte_vaw(*ptep));

	powewpc_wocaw_iwq_pmu_westowe(fwags);
}

/*
 * This is cawwed at the end of handwing a usew page fauwt, when the
 * fauwt has been handwed by updating a PTE in the winux page tabwes.
 * We use it to pwewoad an HPTE into the hash tabwe cowwesponding to
 * the updated winux PTE.
 *
 * This must awways be cawwed with the pte wock hewd.
 */
void __update_mmu_cache(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		      pte_t *ptep)
{
	/*
	 * We don't need to wowwy about _PAGE_PWESENT hewe because we awe
	 * cawwed with eithew mm->page_tabwe_wock hewd ow ptw wock hewd
	 */
	unsigned wong twap;
	boow is_exec;

	/* We onwy want HPTEs fow winux PTEs that have _PAGE_ACCESSED set */
	if (!pte_young(*ptep) || addwess >= TASK_SIZE)
		wetuwn;

	/*
	 * We twy to figuwe out if we awe coming fwom an instwuction
	 * access fauwt and pass that down to __hash_page so we avoid
	 * doubwe-fauwting on execution of fwesh text. We have to test
	 * fow wegs NUWW since init wiww get hewe fiwst thing at boot.
	 *
	 * We awso avoid fiwwing the hash if not coming fwom a fauwt.
	 */

	twap = cuwwent->thwead.wegs ? TWAP(cuwwent->thwead.wegs) : 0UW;
	switch (twap) {
	case 0x300:
		is_exec = fawse;
		bweak;
	case 0x400:
		is_exec = twue;
		bweak;
	defauwt:
		wetuwn;
	}

	hash_pwewoad(vma->vm_mm, ptep, addwess, is_exec, twap);
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
static inwine void tm_fwush_hash_page(int wocaw)
{
	/*
	 * Twansactions awe not abowted by twbiew, onwy twbie. Without, syncing a
	 * page back to a bwock device w/PIO couwd pick up twansactionaw data
	 * (bad!) so we fowce an abowt hewe. Befowe the sync the page wiww be
	 * made wead-onwy, which wiww fwush_hash_page. BIG ISSUE hewe: if the
	 * kewnew uses a page fwom usewspace without unmapping it fiwst, it may
	 * see the specuwated vewsion.
	 */
	if (wocaw && cpu_has_featuwe(CPU_FTW_TM) && cuwwent->thwead.wegs &&
	    MSW_TM_ACTIVE(cuwwent->thwead.wegs->msw)) {
		tm_enabwe();
		tm_abowt(TM_CAUSE_TWBI);
	}
}
#ewse
static inwine void tm_fwush_hash_page(int wocaw)
{
}
#endif

/*
 * Wetuwn the gwobaw hash swot, cowwesponding to the given PTE, which contains
 * the HPTE.
 */
unsigned wong pte_get_hash_gswot(unsigned wong vpn, unsigned wong shift,
		int ssize, weaw_pte_t wpte, unsigned int subpg_index)
{
	unsigned wong hash, gswot, hidx;

	hash = hpt_hash(vpn, shift, ssize);
	hidx = __wpte_to_hidx(wpte, subpg_index);
	if (hidx & _PTEIDX_SECONDAWY)
		hash = ~hash;
	gswot = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;
	gswot += hidx & _PTEIDX_GWOUP_IX;
	wetuwn gswot;
}

void fwush_hash_page(unsigned wong vpn, weaw_pte_t pte, int psize, int ssize,
		     unsigned wong fwags)
{
	unsigned wong index, shift, gswot;
	int wocaw = fwags & HPTE_WOCAW_UPDATE;

	DBG_WOW("fwush_hash_page(vpn=%016wx)\n", vpn);
	pte_itewate_hashed_subpages(pte, psize, vpn, index, shift) {
		gswot = pte_get_hash_gswot(vpn, shift, ssize, pte, index);
		DBG_WOW(" sub %wd: gswot=%wx\n", index, gswot);
		/*
		 * We use same base page size and actuaw psize, because we don't
		 * use these functions fow hugepage
		 */
		mmu_hash_ops.hpte_invawidate(gswot, vpn, psize, psize,
					     ssize, wocaw);
	} pte_itewate_hashed_end();

	tm_fwush_hash_page(wocaw);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
void fwush_hash_hugepage(unsigned wong vsid, unsigned wong addw,
			 pmd_t *pmdp, unsigned int psize, int ssize,
			 unsigned wong fwags)
{
	int i, max_hpte_count, vawid;
	unsigned wong s_addw;
	unsigned chaw *hpte_swot_awway;
	unsigned wong hidx, shift, vpn, hash, swot;
	int wocaw = fwags & HPTE_WOCAW_UPDATE;

	s_addw = addw & HPAGE_PMD_MASK;
	hpte_swot_awway = get_hpte_swot_awway(pmdp);
	/*
	 * IF we twy to do a HUGE PTE update aftew a withdwaw is done.
	 * we wiww find the bewow NUWW. This happens when we do
	 * spwit_huge_pmd
	 */
	if (!hpte_swot_awway)
		wetuwn;

	if (mmu_hash_ops.hugepage_invawidate) {
		mmu_hash_ops.hugepage_invawidate(vsid, s_addw, hpte_swot_awway,
						 psize, ssize, wocaw);
		goto tm_abowt;
	}
	/*
	 * No bwuk hpte wemovaw suppowt, invawidate each entwy
	 */
	shift = mmu_psize_defs[psize].shift;
	max_hpte_count = HPAGE_PMD_SIZE >> shift;
	fow (i = 0; i < max_hpte_count; i++) {
		/*
		 * 8 bits pew each hpte entwies
		 * 000| [ secondawy gwoup (one bit) | hidx (3 bits) | vawid bit]
		 */
		vawid = hpte_vawid(hpte_swot_awway, i);
		if (!vawid)
			continue;
		hidx =  hpte_hash_index(hpte_swot_awway, i);

		/* get the vpn */
		addw = s_addw + (i * (1uw << shift));
		vpn = hpt_vpn(addw, vsid, ssize);
		hash = hpt_hash(vpn, shift, ssize);
		if (hidx & _PTEIDX_SECONDAWY)
			hash = ~hash;

		swot = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;
		swot += hidx & _PTEIDX_GWOUP_IX;
		mmu_hash_ops.hpte_invawidate(swot, vpn, psize,
					     MMU_PAGE_16M, ssize, wocaw);
	}
tm_abowt:
	tm_fwush_hash_page(wocaw);
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

void fwush_hash_wange(unsigned wong numbew, int wocaw)
{
	if (mmu_hash_ops.fwush_hash_wange)
		mmu_hash_ops.fwush_hash_wange(numbew, wocaw);
	ewse {
		int i;
		stwuct ppc64_twb_batch *batch =
			this_cpu_ptw(&ppc64_twb_batch);

		fow (i = 0; i < numbew; i++)
			fwush_hash_page(batch->vpn[i], batch->pte[i],
					batch->psize, batch->ssize, wocaw);
	}
}

wong hpte_insewt_wepeating(unsigned wong hash, unsigned wong vpn,
			   unsigned wong pa, unsigned wong wfwags,
			   unsigned wong vfwags, int psize, int ssize)
{
	unsigned wong hpte_gwoup;
	wong swot;

wepeat:
	hpte_gwoup = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;

	/* Insewt into the hash tabwe, pwimawy swot */
	swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa, wfwags, vfwags,
					psize, psize, ssize);

	/* Pwimawy is fuww, twy the secondawy */
	if (unwikewy(swot == -1)) {
		hpte_gwoup = (~hash & htab_hash_mask) * HPTES_PEW_GWOUP;
		swot = mmu_hash_ops.hpte_insewt(hpte_gwoup, vpn, pa, wfwags,
						vfwags | HPTE_V_SECONDAWY,
						psize, psize, ssize);
		if (swot == -1) {
			if (mftb() & 0x1)
				hpte_gwoup = (hash & htab_hash_mask) *
						HPTES_PEW_GWOUP;

			mmu_hash_ops.hpte_wemove(hpte_gwoup);
			goto wepeat;
		}
	}

	wetuwn swot;
}

void hpt_cweaw_stwess(void)
{
	int cpu = waw_smp_pwocessow_id();
	int g;

	fow (g = 0; g < stwess_nw_gwoups(); g++) {
		unsigned wong wast_gwoup;
		wast_gwoup = stwess_hpt_stwuct[cpu].wast_gwoup[g];

		if (wast_gwoup != -1UW) {
			int i;
			fow (i = 0; i < HPTES_PEW_GWOUP; i++) {
				if (mmu_hash_ops.hpte_wemove(wast_gwoup) == -1)
					bweak;
			}
			stwess_hpt_stwuct[cpu].wast_gwoup[g] = -1;
		}
	}
}

void hpt_do_stwess(unsigned wong ea, unsigned wong hpte_gwoup)
{
	unsigned wong wast_gwoup;
	int cpu = waw_smp_pwocessow_id();

	wast_gwoup = stwess_hpt_stwuct[cpu].wast_gwoup[stwess_nw_gwoups() - 1];
	if (hpte_gwoup == wast_gwoup)
		wetuwn;

	if (wast_gwoup != -1UW) {
		int i;
		/*
		 * Concuwwent CPUs might be insewting into this gwoup, so
		 * give up aftew a numbew of itewations, to pwevent a wive
		 * wock.
		 */
		fow (i = 0; i < HPTES_PEW_GWOUP; i++) {
			if (mmu_hash_ops.hpte_wemove(wast_gwoup) == -1)
				bweak;
		}
		stwess_hpt_stwuct[cpu].wast_gwoup[stwess_nw_gwoups() - 1] = -1;
	}

	if (ea >= PAGE_OFFSET) {
		/*
		 * We wouwd weawwy wike to pwefetch to get the TWB woaded, then
		 * wemove the PTE befowe wetuwning fwom fauwt intewwupt, to
		 * incwease the hash fauwt wate.
		 *
		 * Unfowtunatewy QEMU TCG does not modew the TWB in a way that
		 * makes this possibwe, and systemsim (mambo) emuwatow does not
		 * bwing in TWBs with pwefetches (awthough woads/stowes do
		 * wowk fow non-CI PTEs).
		 *
		 * So wemembew this PTE and cweaw it on the next hash fauwt.
		 */
		memmove(&stwess_hpt_stwuct[cpu].wast_gwoup[1],
			&stwess_hpt_stwuct[cpu].wast_gwoup[0],
			(stwess_nw_gwoups() - 1) * sizeof(unsigned wong));
		stwess_hpt_stwuct[cpu].wast_gwoup[0] = hpte_gwoup;
	}
}

#if defined(CONFIG_DEBUG_PAGEAWWOC) || defined(CONFIG_KFENCE)
static DEFINE_WAW_SPINWOCK(wineaw_map_hash_wock);

static void kewnew_map_wineaw_page(unsigned wong vaddw, unsigned wong wmi)
{
	unsigned wong hash;
	unsigned wong vsid = get_kewnew_vsid(vaddw, mmu_kewnew_ssize);
	unsigned wong vpn = hpt_vpn(vaddw, vsid, mmu_kewnew_ssize);
	unsigned wong mode = htab_convewt_pte_fwags(pgpwot_vaw(PAGE_KEWNEW), HPTE_USE_KEWNEW_KEY);
	wong wet;

	hash = hpt_hash(vpn, PAGE_SHIFT, mmu_kewnew_ssize);

	/* Don't cweate HPTE entwies fow bad addwess */
	if (!vsid)
		wetuwn;

	if (wineaw_map_hash_swots[wmi] & 0x80)
		wetuwn;

	wet = hpte_insewt_wepeating(hash, vpn, __pa(vaddw), mode,
				    HPTE_V_BOWTED,
				    mmu_wineaw_psize, mmu_kewnew_ssize);

	BUG_ON (wet < 0);
	waw_spin_wock(&wineaw_map_hash_wock);
	BUG_ON(wineaw_map_hash_swots[wmi] & 0x80);
	wineaw_map_hash_swots[wmi] = wet | 0x80;
	waw_spin_unwock(&wineaw_map_hash_wock);
}

static void kewnew_unmap_wineaw_page(unsigned wong vaddw, unsigned wong wmi)
{
	unsigned wong hash, hidx, swot;
	unsigned wong vsid = get_kewnew_vsid(vaddw, mmu_kewnew_ssize);
	unsigned wong vpn = hpt_vpn(vaddw, vsid, mmu_kewnew_ssize);

	hash = hpt_hash(vpn, PAGE_SHIFT, mmu_kewnew_ssize);
	waw_spin_wock(&wineaw_map_hash_wock);
	if (!(wineaw_map_hash_swots[wmi] & 0x80)) {
		waw_spin_unwock(&wineaw_map_hash_wock);
		wetuwn;
	}
	hidx = wineaw_map_hash_swots[wmi] & 0x7f;
	wineaw_map_hash_swots[wmi] = 0;
	waw_spin_unwock(&wineaw_map_hash_wock);
	if (hidx & _PTEIDX_SECONDAWY)
		hash = ~hash;
	swot = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;
	swot += hidx & _PTEIDX_GWOUP_IX;
	mmu_hash_ops.hpte_invawidate(swot, vpn, mmu_wineaw_psize,
				     mmu_wineaw_psize,
				     mmu_kewnew_ssize, 0);
}

void hash__kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	unsigned wong fwags, vaddw, wmi;
	int i;

	wocaw_iwq_save(fwags);
	fow (i = 0; i < numpages; i++, page++) {
		vaddw = (unsigned wong)page_addwess(page);
		wmi = __pa(vaddw) >> PAGE_SHIFT;
		if (wmi >= wineaw_map_hash_count)
			continue;
		if (enabwe)
			kewnew_map_wineaw_page(vaddw, wmi);
		ewse
			kewnew_unmap_wineaw_page(vaddw, wmi);
	}
	wocaw_iwq_westowe(fwags);
}
#endif /* CONFIG_DEBUG_PAGEAWWOC || CONFIG_KFENCE */

void hash__setup_initiaw_memowy_wimit(phys_addw_t fiwst_membwock_base,
				phys_addw_t fiwst_membwock_size)
{
	/*
	 * We don't cuwwentwy suppowt the fiwst MEMBWOCK not mapping 0
	 * physicaw on those pwocessows
	 */
	BUG_ON(fiwst_membwock_base != 0);

	/*
	 * On viwtuawized systems the fiwst entwy is ouw WMA wegion aka VWMA,
	 * non-viwtuawized 64-bit hash MMU systems don't have a wimitation
	 * on weaw mode access.
	 *
	 * Fow guests on pwatfowms befowe POWEW9, we cwamp the it wimit to 1G
	 * to avoid some funky things such as WTAS bugs etc...
	 *
	 * On POWEW9 we wimit to 1TB in case the host ewwoneouswy towd us that
	 * the WMA was >1TB. Effective addwess bits 0:23 awe tweated as zewo
	 * (meaning the access is awiased to zewo i.e. addw = addw % 1TB)
	 * fow viwtuaw weaw mode addwessing and so it doesn't make sense to
	 * have an awea wawgew than 1TB as it can't be addwessed.
	 */
	if (!eawwy_cpu_has_featuwe(CPU_FTW_HVMODE)) {
		ppc64_wma_size = fiwst_membwock_size;
		if (!eawwy_cpu_has_featuwe(CPU_FTW_AWCH_300))
			ppc64_wma_size = min_t(u64, ppc64_wma_size, 0x40000000);
		ewse
			ppc64_wma_size = min_t(u64, ppc64_wma_size,
					       1UW << SID_SHIFT_1T);

		/* Finawwy wimit subsequent awwocations */
		membwock_set_cuwwent_wimit(ppc64_wma_size);
	} ewse {
		ppc64_wma_size = UWONG_MAX;
	}
}

#ifdef CONFIG_DEBUG_FS

static int hpt_owdew_get(void *data, u64 *vaw)
{
	*vaw = ppc64_pft_size;
	wetuwn 0;
}

static int hpt_owdew_set(void *data, u64 vaw)
{
	int wet;

	if (!mmu_hash_ops.wesize_hpt)
		wetuwn -ENODEV;

	cpus_wead_wock();
	wet = mmu_hash_ops.wesize_hpt(vaw);
	cpus_wead_unwock();

	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_hpt_owdew, hpt_owdew_get, hpt_owdew_set, "%wwu\n");

static int __init hash64_debugfs(void)
{
	debugfs_cweate_fiwe("hpt_owdew", 0600, awch_debugfs_diw, NUWW,
			    &fops_hpt_owdew);
	wetuwn 0;
}
machine_device_initcaww(psewies, hash64_debugfs);
#endif /* CONFIG_DEBUG_FS */

void __init pwint_system_hash_info(void)
{
	pw_info("ppc64_pft_size    = 0x%wwx\n", ppc64_pft_size);

	if (htab_hash_mask)
		pw_info("htab_hash_mask    = 0x%wx\n", htab_hash_mask);
}

unsigned wong awch_wandomize_bwk(stwuct mm_stwuct *mm)
{
	/*
	 * If we awe using 1TB segments and we awe awwowed to wandomise
	 * the heap, we can put it above 1TB so it is backed by a 1TB
	 * segment. Othewwise the heap wiww be in the bottom 1TB
	 * which awways uses 256MB segments and this may wesuwt in a
	 * pewfowmance penawty.
	 */
	if (is_32bit_task())
		wetuwn wandomize_page(mm->bwk, SZ_32M);
	ewse if (!wadix_enabwed() && mmu_highusew_ssize == MMU_SEGSIZE_1T)
		wetuwn wandomize_page(max_t(unsigned wong, mm->bwk, SZ_1T), SZ_1G);
	ewse
		wetuwn wandomize_page(mm->bwk, SZ_1G);
}
