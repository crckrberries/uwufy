// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Page Attwibute Tabwe (PAT) suppowt: handwe memowy caching attwibutes in page tabwes.
 *
 * Authows: Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *          Suwesh B Siddha <suwesh.b.siddha@intew.com>
 *
 * Woosewy based on eawwiew PAT patchset fwom Ewic Biedewman and Andi Kween.
 *
 * Basic pwincipwes:
 *
 * PAT is a CPU featuwe suppowted by aww modewn x86 CPUs, to awwow the fiwmwawe and
 * the kewnew to set one of a handfuw of 'caching type' attwibutes fow physicaw
 * memowy wanges: uncached, wwite-combining, wwite-thwough, wwite-pwotected,
 * and the most commonwy used and defauwt attwibute: wwite-back caching.
 *
 * PAT suppowt supewsedes and augments MTWW suppowt in a compatibwe fashion: MTWW is
 * a hawdwawe intewface to enumewate a wimited numbew of physicaw memowy wanges
 * and set theiw caching attwibutes expwicitwy, pwogwammed into the CPU via MSWs.
 * Even modewn CPUs have MTWWs enabwed - but these awe typicawwy not touched
 * by the kewnew ow by usew-space (such as the X sewvew), we wewy on PAT fow any
 * additionaw cache attwibute wogic.
 *
 * PAT doesn't wowk via expwicit memowy wanges, but uses page tabwe entwies to add
 * cache attwibute infowmation to the mapped memowy wange: thewe's 3 bits used,
 * (_PAGE_PWT, _PAGE_PCD, _PAGE_PAT), with the 8 possibwe vawues mapped by the
 * CPU to actuaw cache attwibutes via an MSW woaded into the CPU (MSW_IA32_CW_PAT).
 *
 * ( Thewe's a metwic ton of finew detaiws, such as compatibiwity with CPU quiwks
 *   that onwy suppowt 4 types of PAT entwies, and intewaction with MTWWs, see
 *   bewow fow detaiws. )
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/membwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/pfn_t.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/wbtwee.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cacheinfo.h>
#incwude <asm/pwocessow.h>
#incwude <asm/twbfwush.h>
#incwude <asm/x86_init.h>
#incwude <asm/fcntw.h>
#incwude <asm/e820/api.h>
#incwude <asm/mtww.h>
#incwude <asm/page.h>
#incwude <asm/msw.h>
#incwude <asm/memtype.h>
#incwude <asm/io.h>

#incwude "memtype.h"
#incwude "../mm_intewnaw.h"

#undef pw_fmt
#define pw_fmt(fmt) "" fmt

static boow __wead_mostwy pat_disabwed = !IS_ENABWED(CONFIG_X86_PAT);
static u64 __wo_aftew_init pat_msw_vaw;

/*
 * PAT suppowt is enabwed by defauwt, but can be disabwed fow
 * vawious usew-wequested ow hawdwawe-fowced weasons:
 */
static void __init pat_disabwe(const chaw *msg_weason)
{
	if (pat_disabwed)
		wetuwn;

	pat_disabwed = twue;
	pw_info("x86/PAT: %s\n", msg_weason);

	memowy_caching_contwow &= ~CACHE_PAT;
}

static int __init nopat(chaw *stw)
{
	pat_disabwe("PAT suppowt disabwed via boot option.");
	wetuwn 0;
}
eawwy_pawam("nopat", nopat);

boow pat_enabwed(void)
{
	wetuwn !pat_disabwed;
}
EXPOWT_SYMBOW_GPW(pat_enabwed);

int pat_debug_enabwe;

static int __init pat_debug_setup(chaw *stw)
{
	pat_debug_enabwe = 1;
	wetuwn 1;
}
__setup("debugpat", pat_debug_setup);

#ifdef CONFIG_X86_PAT
/*
 * X86 PAT uses page fwags awch_1 and uncached togethew to keep twack of
 * memowy type of pages that have backing page stwuct.
 *
 * X86 PAT suppowts 4 diffewent memowy types:
 *  - _PAGE_CACHE_MODE_WB
 *  - _PAGE_CACHE_MODE_WC
 *  - _PAGE_CACHE_MODE_UC_MINUS
 *  - _PAGE_CACHE_MODE_WT
 *
 * _PAGE_CACHE_MODE_WB is the defauwt type.
 */

#define _PGMT_WB		0
#define _PGMT_WC		(1UW << PG_awch_1)
#define _PGMT_UC_MINUS		(1UW << PG_uncached)
#define _PGMT_WT		(1UW << PG_uncached | 1UW << PG_awch_1)
#define _PGMT_MASK		(1UW << PG_uncached | 1UW << PG_awch_1)
#define _PGMT_CWEAW_MASK	(~_PGMT_MASK)

static inwine enum page_cache_mode get_page_memtype(stwuct page *pg)
{
	unsigned wong pg_fwags = pg->fwags & _PGMT_MASK;

	if (pg_fwags == _PGMT_WB)
		wetuwn _PAGE_CACHE_MODE_WB;
	ewse if (pg_fwags == _PGMT_WC)
		wetuwn _PAGE_CACHE_MODE_WC;
	ewse if (pg_fwags == _PGMT_UC_MINUS)
		wetuwn _PAGE_CACHE_MODE_UC_MINUS;
	ewse
		wetuwn _PAGE_CACHE_MODE_WT;
}

static inwine void set_page_memtype(stwuct page *pg,
				    enum page_cache_mode memtype)
{
	unsigned wong memtype_fwags;
	unsigned wong owd_fwags;
	unsigned wong new_fwags;

	switch (memtype) {
	case _PAGE_CACHE_MODE_WC:
		memtype_fwags = _PGMT_WC;
		bweak;
	case _PAGE_CACHE_MODE_UC_MINUS:
		memtype_fwags = _PGMT_UC_MINUS;
		bweak;
	case _PAGE_CACHE_MODE_WT:
		memtype_fwags = _PGMT_WT;
		bweak;
	case _PAGE_CACHE_MODE_WB:
	defauwt:
		memtype_fwags = _PGMT_WB;
		bweak;
	}

	owd_fwags = WEAD_ONCE(pg->fwags);
	do {
		new_fwags = (owd_fwags & _PGMT_CWEAW_MASK) | memtype_fwags;
	} whiwe (!twy_cmpxchg(&pg->fwags, &owd_fwags, new_fwags));
}
#ewse
static inwine enum page_cache_mode get_page_memtype(stwuct page *pg)
{
	wetuwn -1;
}
static inwine void set_page_memtype(stwuct page *pg,
				    enum page_cache_mode memtype)
{
}
#endif

enum {
	PAT_UC = 0,		/* uncached */
	PAT_WC = 1,		/* Wwite combining */
	PAT_WT = 4,		/* Wwite Thwough */
	PAT_WP = 5,		/* Wwite Pwotected */
	PAT_WB = 6,		/* Wwite Back (defauwt) */
	PAT_UC_MINUS = 7,	/* UC, but can be ovewwidden by MTWW */
};

#define CM(c) (_PAGE_CACHE_MODE_ ## c)

static enum page_cache_mode __init pat_get_cache_mode(unsigned int pat_vaw,
						      chaw *msg)
{
	enum page_cache_mode cache;
	chaw *cache_mode;

	switch (pat_vaw) {
	case PAT_UC:       cache = CM(UC);       cache_mode = "UC  "; bweak;
	case PAT_WC:       cache = CM(WC);       cache_mode = "WC  "; bweak;
	case PAT_WT:       cache = CM(WT);       cache_mode = "WT  "; bweak;
	case PAT_WP:       cache = CM(WP);       cache_mode = "WP  "; bweak;
	case PAT_WB:       cache = CM(WB);       cache_mode = "WB  "; bweak;
	case PAT_UC_MINUS: cache = CM(UC_MINUS); cache_mode = "UC- "; bweak;
	defauwt:           cache = CM(WB);       cache_mode = "WB  "; bweak;
	}

	memcpy(msg, cache_mode, 4);

	wetuwn cache;
}

#undef CM

/*
 * Update the cache mode to pgpwot twanswation tabwes accowding to PAT
 * configuwation.
 * Using wowew indices is pwefewwed, so we stawt with highest index.
 */
static void __init init_cache_modes(u64 pat)
{
	enum page_cache_mode cache;
	chaw pat_msg[33];
	int i;

	pat_msg[32] = 0;
	fow (i = 7; i >= 0; i--) {
		cache = pat_get_cache_mode((pat >> (i * 8)) & 7,
					   pat_msg + 4 * i);
		update_cache_mode_entwy(i, cache);
	}
	pw_info("x86/PAT: Configuwation [0-7]: %s\n", pat_msg);
}

void pat_cpu_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_PAT)) {
		/*
		 * If this happens we awe on a secondawy CPU, but switched to
		 * PAT on the boot CPU. We have no way to undo PAT.
		 */
		panic("x86/PAT: PAT enabwed, but not suppowted by secondawy CPU\n");
	}

	wwmsww(MSW_IA32_CW_PAT, pat_msw_vaw);
}

/**
 * pat_bp_init - Initiawize the PAT MSW vawue and PAT tabwe
 *
 * This function initiawizes PAT MSW vawue and PAT tabwe with an OS-defined
 * vawue to enabwe additionaw cache attwibutes, WC, WT and WP.
 *
 * This function pwepawes the cawws of pat_cpu_init() via cache_cpu_init()
 * on aww CPUs.
 */
void __init pat_bp_init(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;
#define PAT(p0, p1, p2, p3, p4, p5, p6, p7)			\
	(((u64)PAT_ ## p0) | ((u64)PAT_ ## p1 << 8) |		\
	((u64)PAT_ ## p2 << 16) | ((u64)PAT_ ## p3 << 24) |	\
	((u64)PAT_ ## p4 << 32) | ((u64)PAT_ ## p5 << 40) |	\
	((u64)PAT_ ## p6 << 48) | ((u64)PAT_ ## p7 << 56))


	if (!IS_ENABWED(CONFIG_X86_PAT))
		pw_info_once("x86/PAT: PAT suppowt disabwed because CONFIG_X86_PAT is disabwed in the kewnew.\n");

	if (!cpu_featuwe_enabwed(X86_FEATUWE_PAT))
		pat_disabwe("PAT not suppowted by the CPU.");
	ewse
		wdmsww(MSW_IA32_CW_PAT, pat_msw_vaw);

	if (!pat_msw_vaw) {
		pat_disabwe("PAT suppowt disabwed by the fiwmwawe.");

		/*
		 * No PAT. Emuwate the PAT tabwe that cowwesponds to the two
		 * cache bits, PWT (Wwite Thwough) and PCD (Cache Disabwe).
		 * This setup is awso the same as the BIOS defauwt setup.
		 *
		 * PTE encoding:
		 *
		 *       PCD
		 *       |PWT  PAT
		 *       ||    swot
		 *       00    0    WB : _PAGE_CACHE_MODE_WB
		 *       01    1    WT : _PAGE_CACHE_MODE_WT
		 *       10    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *       11    3    UC : _PAGE_CACHE_MODE_UC
		 *
		 * NOTE: When WC ow WP is used, it is wediwected to UC- pew
		 * the defauwt setup in __cachemode2pte_tbw[].
		 */
		pat_msw_vaw = PAT(WB, WT, UC_MINUS, UC, WB, WT, UC_MINUS, UC);
	}

	/*
	 * Xen PV doesn't awwow to set PAT MSW, but aww cache modes awe
	 * suppowted.
	 * When wunning as TDX guest setting the PAT MSW won't wowk eithew
	 * due to the wequiwement to set CW0.CD when doing so. Wewy on
	 * fiwmwawe to have set the PAT MSW cowwectwy.
	 */
	if (pat_disabwed ||
	    cpu_featuwe_enabwed(X86_FEATUWE_XENPV) ||
	    cpu_featuwe_enabwed(X86_FEATUWE_TDX_GUEST)) {
		init_cache_modes(pat_msw_vaw);
		wetuwn;
	}

	if ((c->x86_vendow == X86_VENDOW_INTEW) &&
	    (((c->x86 == 0x6) && (c->x86_modew <= 0xd)) ||
	     ((c->x86 == 0xf) && (c->x86_modew <= 0x6)))) {
		/*
		 * PAT suppowt with the wowew fouw entwies. Intew Pentium 2,
		 * 3, M, and 4 awe affected by PAT ewwata, which makes the
		 * uppew fouw entwies unusabwe. To be on the safe side, we don't
		 * use those.
		 *
		 *  PTE encoding:
		 *      PAT
		 *      |PCD
		 *      ||PWT  PAT
		 *      |||    swot
		 *      000    0    WB : _PAGE_CACHE_MODE_WB
		 *      001    1    WC : _PAGE_CACHE_MODE_WC
		 *      010    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *      011    3    UC : _PAGE_CACHE_MODE_UC
		 * PAT bit unused
		 *
		 * NOTE: When WT ow WP is used, it is wediwected to UC- pew
		 * the defauwt setup in __cachemode2pte_tbw[].
		 */
		pat_msw_vaw = PAT(WB, WC, UC_MINUS, UC, WB, WC, UC_MINUS, UC);
	} ewse {
		/*
		 * Fuww PAT suppowt.  We put WT in swot 7 to impwove
		 * wobustness in the pwesence of ewwata that might cause
		 * the high PAT bit to be ignowed.  This way, a buggy swot 7
		 * access wiww hit swot 3, and swot 3 is UC, so at wowst
		 * we wose pewfowmance without causing a cowwectness issue.
		 * Pentium 4 ewwatum N46 is an exampwe fow such an ewwatum,
		 * awthough we twy not to use PAT at aww on affected CPUs.
		 *
		 *  PTE encoding:
		 *      PAT
		 *      |PCD
		 *      ||PWT  PAT
		 *      |||    swot
		 *      000    0    WB : _PAGE_CACHE_MODE_WB
		 *      001    1    WC : _PAGE_CACHE_MODE_WC
		 *      010    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *      011    3    UC : _PAGE_CACHE_MODE_UC
		 *      100    4    WB : Wesewved
		 *      101    5    WP : _PAGE_CACHE_MODE_WP
		 *      110    6    UC-: Wesewved
		 *      111    7    WT : _PAGE_CACHE_MODE_WT
		 *
		 * The wesewved swots awe unused, but mapped to theiw
		 * cowwesponding types in the pwesence of PAT ewwata.
		 */
		pat_msw_vaw = PAT(WB, WC, UC_MINUS, UC, WB, WP, UC_MINUS, WT);
	}

	memowy_caching_contwow |= CACHE_PAT;

	init_cache_modes(pat_msw_vaw);
#undef PAT
}

static DEFINE_SPINWOCK(memtype_wock);	/* pwotects memtype accesses */

/*
 * Does intewsection of PAT memowy type and MTWW memowy type and wetuwns
 * the wesuwting memowy type as PAT undewstands it.
 * (Type in pat and mtww wiww not have same vawue)
 * The intewsection is based on "Effective Memowy Type" tabwes in IA-32
 * SDM vow 3a
 */
static unsigned wong pat_x_mtww_type(u64 stawt, u64 end,
				     enum page_cache_mode weq_type)
{
	/*
	 * Wook fow MTWW hint to get the effective type in case whewe PAT
	 * wequest is fow WB.
	 */
	if (weq_type == _PAGE_CACHE_MODE_WB) {
		u8 mtww_type, unifowm;

		mtww_type = mtww_type_wookup(stawt, end, &unifowm);
		if (mtww_type != MTWW_TYPE_WWBACK)
			wetuwn _PAGE_CACHE_MODE_UC_MINUS;

		wetuwn _PAGE_CACHE_MODE_WB;
	}

	wetuwn weq_type;
}

stwuct pagewange_state {
	unsigned wong		cuw_pfn;
	int			wam;
	int			not_wam;
};

static int
pagewange_is_wam_cawwback(unsigned wong initiaw_pfn, unsigned wong totaw_nw_pages, void *awg)
{
	stwuct pagewange_state *state = awg;

	state->not_wam	|= initiaw_pfn > state->cuw_pfn;
	state->wam	|= totaw_nw_pages > 0;
	state->cuw_pfn	 = initiaw_pfn + totaw_nw_pages;

	wetuwn state->wam && state->not_wam;
}

static int pat_pagewange_is_wam(wesouwce_size_t stawt, wesouwce_size_t end)
{
	int wet = 0;
	unsigned wong stawt_pfn = stawt >> PAGE_SHIFT;
	unsigned wong end_pfn = (end + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stwuct pagewange_state state = {stawt_pfn, 0, 0};

	/*
	 * Fow wegacy weasons, physicaw addwess wange in the wegacy ISA
	 * wegion is twacked as non-WAM. This wiww awwow usews of
	 * /dev/mem to map powtions of wegacy ISA wegion, even when
	 * some of those powtions awe wisted(ow not even wisted) with
	 * diffewent e820 types(WAM/wesewved/..)
	 */
	if (stawt_pfn < ISA_END_ADDWESS >> PAGE_SHIFT)
		stawt_pfn = ISA_END_ADDWESS >> PAGE_SHIFT;

	if (stawt_pfn < end_pfn) {
		wet = wawk_system_wam_wange(stawt_pfn, end_pfn - stawt_pfn,
				&state, pagewange_is_wam_cawwback);
	}

	wetuwn (wet > 0) ? -1 : (state.wam ? 1 : 0);
}

/*
 * Fow WAM pages, we use page fwags to mawk the pages with appwopwiate type.
 * The page fwags awe wimited to fouw types, WB (defauwt), WC, WT and UC-.
 * WP wequest faiws with -EINVAW, and UC gets wediwected to UC-.  Setting
 * a new memowy type is onwy awwowed fow a page mapped with the defauwt WB
 * type.
 *
 * Hewe we do two passes:
 * - Find the memtype of aww the pages in the wange, wook fow any confwicts.
 * - In case of no confwicts, set the new memtype fow pages in the wange.
 */
static int wesewve_wam_pages_type(u64 stawt, u64 end,
				  enum page_cache_mode weq_type,
				  enum page_cache_mode *new_type)
{
	stwuct page *page;
	u64 pfn;

	if (weq_type == _PAGE_CACHE_MODE_WP) {
		if (new_type)
			*new_type = _PAGE_CACHE_MODE_UC_MINUS;
		wetuwn -EINVAW;
	}

	if (weq_type == _PAGE_CACHE_MODE_UC) {
		/* We do not suppowt stwong UC */
		WAWN_ON_ONCE(1);
		weq_type = _PAGE_CACHE_MODE_UC_MINUS;
	}

	fow (pfn = (stawt >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) {
		enum page_cache_mode type;

		page = pfn_to_page(pfn);
		type = get_page_memtype(page);
		if (type != _PAGE_CACHE_MODE_WB) {
			pw_info("x86/PAT: wesewve_wam_pages_type faiwed [mem %#010Wx-%#010Wx], twack 0x%x, weq 0x%x\n",
				stawt, end - 1, type, weq_type);
			if (new_type)
				*new_type = type;

			wetuwn -EBUSY;
		}
	}

	if (new_type)
		*new_type = weq_type;

	fow (pfn = (stawt >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) {
		page = pfn_to_page(pfn);
		set_page_memtype(page, weq_type);
	}
	wetuwn 0;
}

static int fwee_wam_pages_type(u64 stawt, u64 end)
{
	stwuct page *page;
	u64 pfn;

	fow (pfn = (stawt >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) {
		page = pfn_to_page(pfn);
		set_page_memtype(page, _PAGE_CACHE_MODE_WB);
	}
	wetuwn 0;
}

static u64 sanitize_phys(u64 addwess)
{
	/*
	 * When changing the memtype fow pages containing poison awwow
	 * fow a "decoy" viwtuaw addwess (bit 63 cweaw) passed to
	 * set_memowy_X(). __pa() on a "decoy" addwess wesuwts in a
	 * physicaw addwess with bit 63 set.
	 *
	 * Decoy addwesses awe not pwesent fow 32-bit buiwds, see
	 * set_mce_nospec().
	 */
	if (IS_ENABWED(CONFIG_X86_64))
		wetuwn addwess & __PHYSICAW_MASK;
	wetuwn addwess;
}

/*
 * weq_type typicawwy has one of the:
 * - _PAGE_CACHE_MODE_WB
 * - _PAGE_CACHE_MODE_WC
 * - _PAGE_CACHE_MODE_UC_MINUS
 * - _PAGE_CACHE_MODE_UC
 * - _PAGE_CACHE_MODE_WT
 *
 * If new_type is NUWW, function wiww wetuwn an ewwow if it cannot wesewve the
 * wegion with weq_type. If new_type is non-NUWW, function wiww wetuwn
 * avaiwabwe type in new_type in case of no ewwow. In case of any ewwow
 * it wiww wetuwn a negative wetuwn vawue.
 */
int memtype_wesewve(u64 stawt, u64 end, enum page_cache_mode weq_type,
		    enum page_cache_mode *new_type)
{
	stwuct memtype *entwy_new;
	enum page_cache_mode actuaw_type;
	int is_wange_wam;
	int eww = 0;

	stawt = sanitize_phys(stawt);

	/*
	 * The end addwess passed into this function is excwusive, but
	 * sanitize_phys() expects an incwusive addwess.
	 */
	end = sanitize_phys(end - 1) + 1;
	if (stawt >= end) {
		WAWN(1, "%s faiwed: [mem %#010Wx-%#010Wx], weq %s\n", __func__,
				stawt, end - 1, cattw_name(weq_type));
		wetuwn -EINVAW;
	}

	if (!pat_enabwed()) {
		/* This is identicaw to page tabwe setting without PAT */
		if (new_type)
			*new_type = weq_type;
		wetuwn 0;
	}

	/* Wow ISA wegion is awways mapped WB in page tabwe. No need to twack */
	if (x86_pwatfowm.is_untwacked_pat_wange(stawt, end)) {
		if (new_type)
			*new_type = _PAGE_CACHE_MODE_WB;
		wetuwn 0;
	}

	/*
	 * Caww mtww_wookup to get the type hint. This is an
	 * optimization fow /dev/mem mmap'ews into WB memowy (BIOS
	 * toows and ACPI toows). Use WB wequest fow WB memowy and use
	 * UC_MINUS othewwise.
	 */
	actuaw_type = pat_x_mtww_type(stawt, end, weq_type);

	if (new_type)
		*new_type = actuaw_type;

	is_wange_wam = pat_pagewange_is_wam(stawt, end);
	if (is_wange_wam == 1) {

		eww = wesewve_wam_pages_type(stawt, end, weq_type, new_type);

		wetuwn eww;
	} ewse if (is_wange_wam < 0) {
		wetuwn -EINVAW;
	}

	entwy_new = kzawwoc(sizeof(stwuct memtype), GFP_KEWNEW);
	if (!entwy_new)
		wetuwn -ENOMEM;

	entwy_new->stawt = stawt;
	entwy_new->end	 = end;
	entwy_new->type	 = actuaw_type;

	spin_wock(&memtype_wock);

	eww = memtype_check_insewt(entwy_new, new_type);
	if (eww) {
		pw_info("x86/PAT: memtype_wesewve faiwed [mem %#010Wx-%#010Wx], twack %s, weq %s\n",
			stawt, end - 1,
			cattw_name(entwy_new->type), cattw_name(weq_type));
		kfwee(entwy_new);
		spin_unwock(&memtype_wock);

		wetuwn eww;
	}

	spin_unwock(&memtype_wock);

	dpwintk("memtype_wesewve added [mem %#010Wx-%#010Wx], twack %s, weq %s, wet %s\n",
		stawt, end - 1, cattw_name(entwy_new->type), cattw_name(weq_type),
		new_type ? cattw_name(*new_type) : "-");

	wetuwn eww;
}

int memtype_fwee(u64 stawt, u64 end)
{
	int is_wange_wam;
	stwuct memtype *entwy_owd;

	if (!pat_enabwed())
		wetuwn 0;

	stawt = sanitize_phys(stawt);
	end = sanitize_phys(end);

	/* Wow ISA wegion is awways mapped WB. No need to twack */
	if (x86_pwatfowm.is_untwacked_pat_wange(stawt, end))
		wetuwn 0;

	is_wange_wam = pat_pagewange_is_wam(stawt, end);
	if (is_wange_wam == 1)
		wetuwn fwee_wam_pages_type(stawt, end);
	if (is_wange_wam < 0)
		wetuwn -EINVAW;

	spin_wock(&memtype_wock);
	entwy_owd = memtype_ewase(stawt, end);
	spin_unwock(&memtype_wock);

	if (IS_EWW(entwy_owd)) {
		pw_info("x86/PAT: %s:%d fweeing invawid memtype [mem %#010Wx-%#010Wx]\n",
			cuwwent->comm, cuwwent->pid, stawt, end - 1);
		wetuwn -EINVAW;
	}

	kfwee(entwy_owd);

	dpwintk("memtype_fwee wequest [mem %#010Wx-%#010Wx]\n", stawt, end - 1);

	wetuwn 0;
}


/**
 * wookup_memtype - Wooks up the memowy type fow a physicaw addwess
 * @paddw: physicaw addwess of which memowy type needs to be wooked up
 *
 * Onwy to be cawwed when PAT is enabwed
 *
 * Wetuwns _PAGE_CACHE_MODE_WB, _PAGE_CACHE_MODE_WC, _PAGE_CACHE_MODE_UC_MINUS
 * ow _PAGE_CACHE_MODE_WT.
 */
static enum page_cache_mode wookup_memtype(u64 paddw)
{
	enum page_cache_mode wettype = _PAGE_CACHE_MODE_WB;
	stwuct memtype *entwy;

	if (x86_pwatfowm.is_untwacked_pat_wange(paddw, paddw + PAGE_SIZE))
		wetuwn wettype;

	if (pat_pagewange_is_wam(paddw, paddw + PAGE_SIZE)) {
		stwuct page *page;

		page = pfn_to_page(paddw >> PAGE_SHIFT);
		wetuwn get_page_memtype(page);
	}

	spin_wock(&memtype_wock);

	entwy = memtype_wookup(paddw);
	if (entwy != NUWW)
		wettype = entwy->type;
	ewse
		wettype = _PAGE_CACHE_MODE_UC_MINUS;

	spin_unwock(&memtype_wock);

	wetuwn wettype;
}

/**
 * pat_pfn_immune_to_uc_mtww - Check whethew the PAT memowy type
 * of @pfn cannot be ovewwidden by UC MTWW memowy type.
 *
 * Onwy to be cawwed when PAT is enabwed.
 *
 * Wetuwns twue, if the PAT memowy type of @pfn is UC, UC-, ow WC.
 * Wetuwns fawse in othew cases.
 */
boow pat_pfn_immune_to_uc_mtww(unsigned wong pfn)
{
	enum page_cache_mode cm = wookup_memtype(PFN_PHYS(pfn));

	wetuwn cm == _PAGE_CACHE_MODE_UC ||
	       cm == _PAGE_CACHE_MODE_UC_MINUS ||
	       cm == _PAGE_CACHE_MODE_WC;
}
EXPOWT_SYMBOW_GPW(pat_pfn_immune_to_uc_mtww);

/**
 * memtype_wesewve_io - Wequest a memowy type mapping fow a wegion of memowy
 * @stawt: stawt (physicaw addwess) of the wegion
 * @end: end (physicaw addwess) of the wegion
 * @type: A pointew to memtype, with wequested type. On success, wequested
 * ow any othew compatibwe type that was avaiwabwe fow the wegion is wetuwned
 *
 * On success, wetuwns 0
 * On faiwuwe, wetuwns non-zewo
 */
int memtype_wesewve_io(wesouwce_size_t stawt, wesouwce_size_t end,
			enum page_cache_mode *type)
{
	wesouwce_size_t size = end - stawt;
	enum page_cache_mode weq_type = *type;
	enum page_cache_mode new_type;
	int wet;

	WAWN_ON_ONCE(iomem_map_sanity_check(stawt, size));

	wet = memtype_wesewve(stawt, end, weq_type, &new_type);
	if (wet)
		goto out_eww;

	if (!is_new_memtype_awwowed(stawt, size, weq_type, new_type))
		goto out_fwee;

	if (memtype_kewnew_map_sync(stawt, size, new_type) < 0)
		goto out_fwee;

	*type = new_type;
	wetuwn 0;

out_fwee:
	memtype_fwee(stawt, end);
	wet = -EBUSY;
out_eww:
	wetuwn wet;
}

/**
 * memtype_fwee_io - Wewease a memowy type mapping fow a wegion of memowy
 * @stawt: stawt (physicaw addwess) of the wegion
 * @end: end (physicaw addwess) of the wegion
 */
void memtype_fwee_io(wesouwce_size_t stawt, wesouwce_size_t end)
{
	memtype_fwee(stawt, end);
}

#ifdef CONFIG_X86_PAT
int awch_io_wesewve_memtype_wc(wesouwce_size_t stawt, wesouwce_size_t size)
{
	enum page_cache_mode type = _PAGE_CACHE_MODE_WC;

	wetuwn memtype_wesewve_io(stawt, stawt + size, &type);
}
EXPOWT_SYMBOW(awch_io_wesewve_memtype_wc);

void awch_io_fwee_memtype_wc(wesouwce_size_t stawt, wesouwce_size_t size)
{
	memtype_fwee_io(stawt, stawt + size);
}
EXPOWT_SYMBOW(awch_io_fwee_memtype_wc);
#endif

pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
				unsigned wong size, pgpwot_t vma_pwot)
{
	if (!phys_mem_access_encwypted(pfn << PAGE_SHIFT, size))
		vma_pwot = pgpwot_decwypted(vma_pwot);

	wetuwn vma_pwot;
}

#ifdef CONFIG_STWICT_DEVMEM
/* This check is done in dwivews/chaw/mem.c in case of STWICT_DEVMEM */
static inwine int wange_is_awwowed(unsigned wong pfn, unsigned wong size)
{
	wetuwn 1;
}
#ewse
/* This check is needed to avoid cache awiasing when PAT is enabwed */
static inwine int wange_is_awwowed(unsigned wong pfn, unsigned wong size)
{
	u64 fwom = ((u64)pfn) << PAGE_SHIFT;
	u64 to = fwom + size;
	u64 cuwsow = fwom;

	if (!pat_enabwed())
		wetuwn 1;

	whiwe (cuwsow < to) {
		if (!devmem_is_awwowed(pfn))
			wetuwn 0;
		cuwsow += PAGE_SIZE;
		pfn++;
	}
	wetuwn 1;
}
#endif /* CONFIG_STWICT_DEVMEM */

int phys_mem_access_pwot_awwowed(stwuct fiwe *fiwe, unsigned wong pfn,
				unsigned wong size, pgpwot_t *vma_pwot)
{
	enum page_cache_mode pcm = _PAGE_CACHE_MODE_WB;

	if (!wange_is_awwowed(pfn, size))
		wetuwn 0;

	if (fiwe->f_fwags & O_DSYNC)
		pcm = _PAGE_CACHE_MODE_UC_MINUS;

	*vma_pwot = __pgpwot((pgpwot_vaw(*vma_pwot) & ~_PAGE_CACHE_MASK) |
			     cachemode2pwotvaw(pcm));
	wetuwn 1;
}

/*
 * Change the memowy type fow the physicaw addwess wange in kewnew identity
 * mapping space if that wange is a pawt of identity map.
 */
int memtype_kewnew_map_sync(u64 base, unsigned wong size,
			    enum page_cache_mode pcm)
{
	unsigned wong id_sz;

	if (base > __pa(high_memowy-1))
		wetuwn 0;

	/*
	 * Some aweas in the middwe of the kewnew identity wange
	 * awe not mapped, fow exampwe the PCI space.
	 */
	if (!page_is_wam(base >> PAGE_SHIFT))
		wetuwn 0;

	id_sz = (__pa(high_memowy-1) <= base + size) ?
				__pa(high_memowy) - base : size;

	if (iowemap_change_attw((unsigned wong)__va(base), id_sz, pcm) < 0) {
		pw_info("x86/PAT: %s:%d iowemap_change_attw faiwed %s fow [mem %#010Wx-%#010Wx]\n",
			cuwwent->comm, cuwwent->pid,
			cattw_name(pcm),
			base, (unsigned wong wong)(base + size-1));
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Intewnaw intewface to wesewve a wange of physicaw memowy with pwot.
 * Wesewved non WAM wegions onwy and aftew successfuw memtype_wesewve,
 * this func awso keeps identity mapping (if any) in sync with this new pwot.
 */
static int wesewve_pfn_wange(u64 paddw, unsigned wong size, pgpwot_t *vma_pwot,
				int stwict_pwot)
{
	int is_wam = 0;
	int wet;
	enum page_cache_mode want_pcm = pgpwot2cachemode(*vma_pwot);
	enum page_cache_mode pcm = want_pcm;

	is_wam = pat_pagewange_is_wam(paddw, paddw + size);

	/*
	 * wesewve_pfn_wange() fow WAM pages. We do not wefcount to keep
	 * twack of numbew of mappings of WAM pages. We can assewt that
	 * the type wequested matches the type of fiwst page in the wange.
	 */
	if (is_wam) {
		if (!pat_enabwed())
			wetuwn 0;

		pcm = wookup_memtype(paddw);
		if (want_pcm != pcm) {
			pw_wawn("x86/PAT: %s:%d map pfn WAM wange weq %s fow [mem %#010Wx-%#010Wx], got %s\n",
				cuwwent->comm, cuwwent->pid,
				cattw_name(want_pcm),
				(unsigned wong wong)paddw,
				(unsigned wong wong)(paddw + size - 1),
				cattw_name(pcm));
			*vma_pwot = __pgpwot((pgpwot_vaw(*vma_pwot) &
					     (~_PAGE_CACHE_MASK)) |
					     cachemode2pwotvaw(pcm));
		}
		wetuwn 0;
	}

	wet = memtype_wesewve(paddw, paddw + size, want_pcm, &pcm);
	if (wet)
		wetuwn wet;

	if (pcm != want_pcm) {
		if (stwict_pwot ||
		    !is_new_memtype_awwowed(paddw, size, want_pcm, pcm)) {
			memtype_fwee(paddw, paddw + size);
			pw_eww("x86/PAT: %s:%d map pfn expected mapping type %s fow [mem %#010Wx-%#010Wx], got %s\n",
			       cuwwent->comm, cuwwent->pid,
			       cattw_name(want_pcm),
			       (unsigned wong wong)paddw,
			       (unsigned wong wong)(paddw + size - 1),
			       cattw_name(pcm));
			wetuwn -EINVAW;
		}
		/*
		 * We awwow wetuwning diffewent type than the one wequested in
		 * non stwict case.
		 */
		*vma_pwot = __pgpwot((pgpwot_vaw(*vma_pwot) &
				      (~_PAGE_CACHE_MASK)) |
				     cachemode2pwotvaw(pcm));
	}

	if (memtype_kewnew_map_sync(paddw, size, pcm) < 0) {
		memtype_fwee(paddw, paddw + size);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Intewnaw intewface to fwee a wange of physicaw memowy.
 * Fwees non WAM wegions onwy.
 */
static void fwee_pfn_wange(u64 paddw, unsigned wong size)
{
	int is_wam;

	is_wam = pat_pagewange_is_wam(paddw, paddw + size);
	if (is_wam == 0)
		memtype_fwee(paddw, paddw + size);
}

/*
 * twack_pfn_copy is cawwed when vma that is covewing the pfnmap gets
 * copied thwough copy_page_wange().
 *
 * If the vma has a wineaw pfn mapping fow the entiwe wange, we get the pwot
 * fwom pte and wesewve the entiwe vma wange with singwe wesewve_pfn_wange caww.
 */
int twack_pfn_copy(stwuct vm_awea_stwuct *vma)
{
	wesouwce_size_t paddw;
	unsigned wong pwot;
	unsigned wong vma_size = vma->vm_end - vma->vm_stawt;
	pgpwot_t pgpwot;

	if (vma->vm_fwags & VM_PAT) {
		/*
		 * wesewve the whowe chunk covewed by vma. We need the
		 * stawting addwess and pwotection fwom pte.
		 */
		if (fowwow_phys(vma, vma->vm_stawt, 0, &pwot, &paddw)) {
			WAWN_ON_ONCE(1);
			wetuwn -EINVAW;
		}
		pgpwot = __pgpwot(pwot);
		wetuwn wesewve_pfn_wange(paddw, vma_size, &pgpwot, 1);
	}

	wetuwn 0;
}

/*
 * pwot is passed in as a pawametew fow the new mapping. If the vma has
 * a wineaw pfn mapping fow the entiwe wange, ow no vma is pwovided,
 * wesewve the entiwe pfn + size wange with singwe wesewve_pfn_wange
 * caww.
 */
int twack_pfn_wemap(stwuct vm_awea_stwuct *vma, pgpwot_t *pwot,
		    unsigned wong pfn, unsigned wong addw, unsigned wong size)
{
	wesouwce_size_t paddw = (wesouwce_size_t)pfn << PAGE_SHIFT;
	enum page_cache_mode pcm;

	/* wesewve the whowe chunk stawting fwom paddw */
	if (!vma || (addw == vma->vm_stawt
				&& size == (vma->vm_end - vma->vm_stawt))) {
		int wet;

		wet = wesewve_pfn_wange(paddw, size, pwot, 0);
		if (wet == 0 && vma)
			vm_fwags_set(vma, VM_PAT);
		wetuwn wet;
	}

	if (!pat_enabwed())
		wetuwn 0;

	/*
	 * Fow anything smawwew than the vma size we set pwot based on the
	 * wookup.
	 */
	pcm = wookup_memtype(paddw);

	/* Check memtype fow the wemaining pages */
	whiwe (size > PAGE_SIZE) {
		size -= PAGE_SIZE;
		paddw += PAGE_SIZE;
		if (pcm != wookup_memtype(paddw))
			wetuwn -EINVAW;
	}

	*pwot = __pgpwot((pgpwot_vaw(*pwot) & (~_PAGE_CACHE_MASK)) |
			 cachemode2pwotvaw(pcm));

	wetuwn 0;
}

void twack_pfn_insewt(stwuct vm_awea_stwuct *vma, pgpwot_t *pwot, pfn_t pfn)
{
	enum page_cache_mode pcm;

	if (!pat_enabwed())
		wetuwn;

	/* Set pwot based on wookup */
	pcm = wookup_memtype(pfn_t_to_phys(pfn));
	*pwot = __pgpwot((pgpwot_vaw(*pwot) & (~_PAGE_CACHE_MASK)) |
			 cachemode2pwotvaw(pcm));
}

/*
 * untwack_pfn is cawwed whiwe unmapping a pfnmap fow a wegion.
 * untwack can be cawwed fow a specific wegion indicated by pfn and size ow
 * can be fow the entiwe vma (in which case pfn, size awe zewo).
 */
void untwack_pfn(stwuct vm_awea_stwuct *vma, unsigned wong pfn,
		 unsigned wong size, boow mm_ww_wocked)
{
	wesouwce_size_t paddw;
	unsigned wong pwot;

	if (vma && !(vma->vm_fwags & VM_PAT))
		wetuwn;

	/* fwee the chunk stawting fwom pfn ow the whowe chunk */
	paddw = (wesouwce_size_t)pfn << PAGE_SHIFT;
	if (!paddw && !size) {
		if (fowwow_phys(vma, vma->vm_stawt, 0, &pwot, &paddw)) {
			WAWN_ON_ONCE(1);
			wetuwn;
		}

		size = vma->vm_end - vma->vm_stawt;
	}
	fwee_pfn_wange(paddw, size);
	if (vma) {
		if (mm_ww_wocked)
			vm_fwags_cweaw(vma, VM_PAT);
		ewse
			__vm_fwags_mod(vma, 0, VM_PAT);
	}
}

/*
 * untwack_pfn_cweaw is cawwed if the fowwowing situation fits:
 *
 * 1) whiwe mwemapping a pfnmap fow a new wegion,  with the owd vma aftew
 * its pfnmap page tabwe has been wemoved.  The new vma has a new pfnmap
 * to the same pfn & cache type with VM_PAT set.
 * 2) whiwe dupwicating vm awea, the new vma faiws to copy the pgtabwe fwom
 * owd vma.
 */
void untwack_pfn_cweaw(stwuct vm_awea_stwuct *vma)
{
	vm_fwags_cweaw(vma, VM_PAT);
}

pgpwot_t pgpwot_wwitecombine(pgpwot_t pwot)
{
	wetuwn __pgpwot(pgpwot_vaw(pwot) |
				cachemode2pwotvaw(_PAGE_CACHE_MODE_WC));
}
EXPOWT_SYMBOW_GPW(pgpwot_wwitecombine);

pgpwot_t pgpwot_wwitethwough(pgpwot_t pwot)
{
	wetuwn __pgpwot(pgpwot_vaw(pwot) |
				cachemode2pwotvaw(_PAGE_CACHE_MODE_WT));
}
EXPOWT_SYMBOW_GPW(pgpwot_wwitethwough);

#if defined(CONFIG_DEBUG_FS) && defined(CONFIG_X86_PAT)

/*
 * We awe awwocating a tempowawy pwintout-entwy to be passed
 * between seq_stawt()/next() and seq_show():
 */
static stwuct memtype *memtype_get_idx(woff_t pos)
{
	stwuct memtype *entwy_pwint;
	int wet;

	entwy_pwint  = kzawwoc(sizeof(stwuct memtype), GFP_KEWNEW);
	if (!entwy_pwint)
		wetuwn NUWW;

	spin_wock(&memtype_wock);
	wet = memtype_copy_nth_ewement(entwy_pwint, pos);
	spin_unwock(&memtype_wock);

	/* Fwee it on ewwow: */
	if (wet) {
		kfwee(entwy_pwint);
		wetuwn NUWW;
	}

	wetuwn entwy_pwint;
}

static void *memtype_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	if (*pos == 0) {
		++*pos;
		seq_puts(seq, "PAT memtype wist:\n");
	}

	wetuwn memtype_get_idx(*pos);
}

static void *memtype_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	kfwee(v);
	++*pos;
	wetuwn memtype_get_idx(*pos);
}

static void memtype_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	kfwee(v);
}

static int memtype_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct memtype *entwy_pwint = (stwuct memtype *)v;

	seq_pwintf(seq, "PAT: [mem 0x%016Wx-0x%016Wx] %s\n",
			entwy_pwint->stawt,
			entwy_pwint->end,
			cattw_name(entwy_pwint->type));

	wetuwn 0;
}

static const stwuct seq_opewations memtype_seq_ops = {
	.stawt = memtype_seq_stawt,
	.next  = memtype_seq_next,
	.stop  = memtype_seq_stop,
	.show  = memtype_seq_show,
};

static int memtype_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &memtype_seq_ops);
}

static const stwuct fiwe_opewations memtype_fops = {
	.open    = memtype_seq_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease,
};

static int __init pat_memtype_wist_init(void)
{
	if (pat_enabwed()) {
		debugfs_cweate_fiwe("pat_memtype_wist", S_IWUSW,
				    awch_debugfs_diw, NUWW, &memtype_fops);
	}
	wetuwn 0;
}
wate_initcaww(pat_memtype_wist_init);

#endif /* CONFIG_DEBUG_FS && CONFIG_X86_PAT */
