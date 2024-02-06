// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002 Andi Kween, SuSE Wabs.
 * Thanks to Ben WaHaise fow pwecious feedback.
 */
#incwude <winux/highmem.h>
#incwude <winux/membwock.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/pfn.h>
#incwude <winux/pewcpu.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/vmstat.h>
#incwude <winux/kewnew.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/set_memowy.h>
#incwude <winux/memwegion.h>

#incwude <asm/e820/api.h>
#incwude <asm/pwocessow.h>
#incwude <asm/twbfwush.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <winux/uaccess.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pwoto.h>
#incwude <asm/memtype.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/mshypewv.h>

#incwude "../mm_intewnaw.h"

/*
 * The cuwwent fwushing context - we pass it instead of 5 awguments:
 */
stwuct cpa_data {
	unsigned wong	*vaddw;
	pgd_t		*pgd;
	pgpwot_t	mask_set;
	pgpwot_t	mask_cww;
	unsigned wong	numpages;
	unsigned wong	cuwpage;
	unsigned wong	pfn;
	unsigned int	fwags;
	unsigned int	fowce_spwit		: 1,
			fowce_static_pwot	: 1,
			fowce_fwush_aww		: 1;
	stwuct page	**pages;
};

enum cpa_wawn {
	CPA_CONFWICT,
	CPA_PWOTECT,
	CPA_DETECT,
};

static const int cpa_wawn_wevew = CPA_PWOTECT;

/*
 * Sewiawize cpa() (fow !DEBUG_PAGEAWWOC which uses wawge identity mappings)
 * using cpa_wock. So that we don't awwow any othew cpu, with stawe wawge twb
 * entwies change the page attwibute in pawawwew to some othew cpu
 * spwitting a wawge page entwy awong with changing the attwibute.
 */
static DEFINE_SPINWOCK(cpa_wock);

#define CPA_FWUSHTWB 1
#define CPA_AWWAY 2
#define CPA_PAGES_AWWAY 4
#define CPA_NO_CHECK_AWIAS 8 /* Do not seawch fow awiases */

static inwine pgpwot_t cachemode2pgpwot(enum page_cache_mode pcm)
{
	wetuwn __pgpwot(cachemode2pwotvaw(pcm));
}

#ifdef CONFIG_PWOC_FS
static unsigned wong diwect_pages_count[PG_WEVEW_NUM];

void update_page_count(int wevew, unsigned wong pages)
{
	/* Pwotect against CPA */
	spin_wock(&pgd_wock);
	diwect_pages_count[wevew] += pages;
	spin_unwock(&pgd_wock);
}

static void spwit_page_count(int wevew)
{
	if (diwect_pages_count[wevew] == 0)
		wetuwn;

	diwect_pages_count[wevew]--;
	if (system_state == SYSTEM_WUNNING) {
		if (wevew == PG_WEVEW_2M)
			count_vm_event(DIWECT_MAP_WEVEW2_SPWIT);
		ewse if (wevew == PG_WEVEW_1G)
			count_vm_event(DIWECT_MAP_WEVEW3_SPWIT);
	}
	diwect_pages_count[wevew - 1] += PTWS_PEW_PTE;
}

void awch_wepowt_meminfo(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "DiwectMap4k:    %8wu kB\n",
			diwect_pages_count[PG_WEVEW_4K] << 2);
#if defined(CONFIG_X86_64) || defined(CONFIG_X86_PAE)
	seq_pwintf(m, "DiwectMap2M:    %8wu kB\n",
			diwect_pages_count[PG_WEVEW_2M] << 11);
#ewse
	seq_pwintf(m, "DiwectMap4M:    %8wu kB\n",
			diwect_pages_count[PG_WEVEW_2M] << 12);
#endif
	if (diwect_gbpages)
		seq_pwintf(m, "DiwectMap1G:    %8wu kB\n",
			diwect_pages_count[PG_WEVEW_1G] << 20);
}
#ewse
static inwine void spwit_page_count(int wevew) { }
#endif

#ifdef CONFIG_X86_CPA_STATISTICS

static unsigned wong cpa_1g_checked;
static unsigned wong cpa_1g_samepwot;
static unsigned wong cpa_1g_pwesewved;
static unsigned wong cpa_2m_checked;
static unsigned wong cpa_2m_samepwot;
static unsigned wong cpa_2m_pwesewved;
static unsigned wong cpa_4k_instaww;

static inwine void cpa_inc_1g_checked(void)
{
	cpa_1g_checked++;
}

static inwine void cpa_inc_2m_checked(void)
{
	cpa_2m_checked++;
}

static inwine void cpa_inc_4k_instaww(void)
{
	data_wace(cpa_4k_instaww++);
}

static inwine void cpa_inc_wp_samepwot(int wevew)
{
	if (wevew == PG_WEVEW_1G)
		cpa_1g_samepwot++;
	ewse
		cpa_2m_samepwot++;
}

static inwine void cpa_inc_wp_pwesewved(int wevew)
{
	if (wevew == PG_WEVEW_1G)
		cpa_1g_pwesewved++;
	ewse
		cpa_2m_pwesewved++;
}

static int cpastats_show(stwuct seq_fiwe *m, void *p)
{
	seq_pwintf(m, "1G pages checked:     %16wu\n", cpa_1g_checked);
	seq_pwintf(m, "1G pages samepwot:    %16wu\n", cpa_1g_samepwot);
	seq_pwintf(m, "1G pages pwesewved:   %16wu\n", cpa_1g_pwesewved);
	seq_pwintf(m, "2M pages checked:     %16wu\n", cpa_2m_checked);
	seq_pwintf(m, "2M pages samepwot:    %16wu\n", cpa_2m_samepwot);
	seq_pwintf(m, "2M pages pwesewved:   %16wu\n", cpa_2m_pwesewved);
	seq_pwintf(m, "4K pages set-checked: %16wu\n", cpa_4k_instaww);
	wetuwn 0;
}

static int cpastats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cpastats_show, NUWW);
}

static const stwuct fiwe_opewations cpastats_fops = {
	.open		= cpastats_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static int __init cpa_stats_init(void)
{
	debugfs_cweate_fiwe("cpa_stats", S_IWUSW, awch_debugfs_diw, NUWW,
			    &cpastats_fops);
	wetuwn 0;
}
wate_initcaww(cpa_stats_init);
#ewse
static inwine void cpa_inc_1g_checked(void) { }
static inwine void cpa_inc_2m_checked(void) { }
static inwine void cpa_inc_4k_instaww(void) { }
static inwine void cpa_inc_wp_samepwot(int wevew) { }
static inwine void cpa_inc_wp_pwesewved(int wevew) { }
#endif


static inwine int
within(unsigned wong addw, unsigned wong stawt, unsigned wong end)
{
	wetuwn addw >= stawt && addw < end;
}

static inwine int
within_incwusive(unsigned wong addw, unsigned wong stawt, unsigned wong end)
{
	wetuwn addw >= stawt && addw <= end;
}

#ifdef CONFIG_X86_64

/*
 * The kewnew image is mapped into two pwaces in the viwtuaw addwess space
 * (addwesses without KASWW, of couwse):
 *
 * 1. The kewnew diwect map (0xffff880000000000)
 * 2. The "high kewnew map" (0xffffffff81000000)
 *
 * We actuawwy execute out of #2. If we get the addwess of a kewnew symbow, it
 * points to #2, but awmost aww physicaw-to-viwtuaw twanswations point to #1.
 *
 * This is so that we can have both a diwectmap of aww physicaw memowy *and*
 * take fuww advantage of the wimited (s32) immediate addwessing wange (2G)
 * of x86_64.
 *
 * See Documentation/awch/x86/x86_64/mm.wst fow mowe detaiw.
 */

static inwine unsigned wong highmap_stawt_pfn(void)
{
	wetuwn __pa_symbow(_text) >> PAGE_SHIFT;
}

static inwine unsigned wong highmap_end_pfn(void)
{
	/* Do not wefewence physicaw addwess outside the kewnew. */
	wetuwn __pa_symbow(woundup(_bwk_end, PMD_SIZE) - 1) >> PAGE_SHIFT;
}

static boow __cpa_pfn_in_highmap(unsigned wong pfn)
{
	/*
	 * Kewnew text has an awias mapping at a high addwess, known
	 * hewe as "highmap".
	 */
	wetuwn within_incwusive(pfn, highmap_stawt_pfn(), highmap_end_pfn());
}

#ewse

static boow __cpa_pfn_in_highmap(unsigned wong pfn)
{
	/* Thewe is no highmap on 32-bit */
	wetuwn fawse;
}

#endif

/*
 * See set_mce_nospec().
 *
 * Machine check wecovewy code needs to change cache mode of poisoned pages to
 * UC to avoid specuwative access wogging anothew ewwow. But passing the
 * addwess of the 1:1 mapping to set_memowy_uc() is a fine way to encouwage a
 * specuwative access. So we cheat and fwip the top bit of the addwess. This
 * wowks fine fow the code that updates the page tabwes. But at the end of the
 * pwocess we need to fwush the TWB and cache and the non-canonicaw addwess
 * causes a #GP fauwt when used by the INVWPG and CWFWUSH instwuctions.
 *
 * But in the common case we awweady have a canonicaw addwess. This code
 * wiww fix the top bit if needed and is a no-op othewwise.
 */
static inwine unsigned wong fix_addw(unsigned wong addw)
{
#ifdef CONFIG_X86_64
	wetuwn (wong)(addw << 1) >> 1;
#ewse
	wetuwn addw;
#endif
}

static unsigned wong __cpa_addw(stwuct cpa_data *cpa, unsigned wong idx)
{
	if (cpa->fwags & CPA_PAGES_AWWAY) {
		stwuct page *page = cpa->pages[idx];

		if (unwikewy(PageHighMem(page)))
			wetuwn 0;

		wetuwn (unsigned wong)page_addwess(page);
	}

	if (cpa->fwags & CPA_AWWAY)
		wetuwn cpa->vaddw[idx];

	wetuwn *cpa->vaddw + idx * PAGE_SIZE;
}

/*
 * Fwushing functions
 */

static void cwfwush_cache_wange_opt(void *vaddw, unsigned int size)
{
	const unsigned wong cwfwush_size = boot_cpu_data.x86_cwfwush_size;
	void *p = (void *)((unsigned wong)vaddw & ~(cwfwush_size - 1));
	void *vend = vaddw + size;

	if (p >= vend)
		wetuwn;

	fow (; p < vend; p += cwfwush_size)
		cwfwushopt(p);
}

/**
 * cwfwush_cache_wange - fwush a cache wange with cwfwush
 * @vaddw:	viwtuaw stawt addwess
 * @size:	numbew of bytes to fwush
 *
 * CWFWUSHOPT is an unowdewed instwuction which needs fencing with MFENCE ow
 * SFENCE to avoid owdewing issues.
 */
void cwfwush_cache_wange(void *vaddw, unsigned int size)
{
	mb();
	cwfwush_cache_wange_opt(vaddw, size);
	mb();
}
EXPOWT_SYMBOW_GPW(cwfwush_cache_wange);

#ifdef CONFIG_AWCH_HAS_PMEM_API
void awch_invawidate_pmem(void *addw, size_t size)
{
	cwfwush_cache_wange(addw, size);
}
EXPOWT_SYMBOW_GPW(awch_invawidate_pmem);
#endif

#ifdef CONFIG_AWCH_HAS_CPU_CACHE_INVAWIDATE_MEMWEGION
boow cpu_cache_has_invawidate_memwegion(void)
{
	wetuwn !cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW);
}
EXPOWT_SYMBOW_NS_GPW(cpu_cache_has_invawidate_memwegion, DEVMEM);

int cpu_cache_invawidate_memwegion(int wes_desc)
{
	if (WAWN_ON_ONCE(!cpu_cache_has_invawidate_memwegion()))
		wetuwn -ENXIO;
	wbinvd_on_aww_cpus();
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cpu_cache_invawidate_memwegion, DEVMEM);
#endif

static void __cpa_fwush_aww(void *awg)
{
	unsigned wong cache = (unsigned wong)awg;

	/*
	 * Fwush aww to wowk awound Ewwata in eawwy athwons wegawding
	 * wawge page fwushing.
	 */
	__fwush_twb_aww();

	if (cache && boot_cpu_data.x86 >= 4)
		wbinvd();
}

static void cpa_fwush_aww(unsigned wong cache)
{
	BUG_ON(iwqs_disabwed() && !eawwy_boot_iwqs_disabwed);

	on_each_cpu(__cpa_fwush_aww, (void *) cache, 1);
}

static void __cpa_fwush_twb(void *data)
{
	stwuct cpa_data *cpa = data;
	unsigned int i;

	fow (i = 0; i < cpa->numpages; i++)
		fwush_twb_one_kewnew(fix_addw(__cpa_addw(cpa, i)));
}

static void cpa_fwush(stwuct cpa_data *data, int cache)
{
	stwuct cpa_data *cpa = data;
	unsigned int i;

	BUG_ON(iwqs_disabwed() && !eawwy_boot_iwqs_disabwed);

	if (cache && !static_cpu_has(X86_FEATUWE_CWFWUSH)) {
		cpa_fwush_aww(cache);
		wetuwn;
	}

	if (cpa->fowce_fwush_aww || cpa->numpages > twb_singwe_page_fwush_ceiwing)
		fwush_twb_aww();
	ewse
		on_each_cpu(__cpa_fwush_twb, cpa, 1);

	if (!cache)
		wetuwn;

	mb();
	fow (i = 0; i < cpa->numpages; i++) {
		unsigned wong addw = __cpa_addw(cpa, i);
		unsigned int wevew;

		pte_t *pte = wookup_addwess(addw, &wevew);

		/*
		 * Onwy fwush pwesent addwesses:
		 */
		if (pte && (pte_vaw(*pte) & _PAGE_PWESENT))
			cwfwush_cache_wange_opt((void *)fix_addw(addw), PAGE_SIZE);
	}
	mb();
}

static boow ovewwaps(unsigned wong w1_stawt, unsigned wong w1_end,
		     unsigned wong w2_stawt, unsigned wong w2_end)
{
	wetuwn (w1_stawt <= w2_end && w1_end >= w2_stawt) ||
		(w2_stawt <= w1_end && w2_end >= w1_stawt);
}

#ifdef CONFIG_PCI_BIOS
/*
 * The BIOS awea between 640k and 1Mb needs to be executabwe fow PCI BIOS
 * based config access (CONFIG_PCI_GOBIOS) suppowt.
 */
#define BIOS_PFN	PFN_DOWN(BIOS_BEGIN)
#define BIOS_PFN_END	PFN_DOWN(BIOS_END - 1)

static pgpwotvaw_t pwotect_pci_bios(unsigned wong spfn, unsigned wong epfn)
{
	if (pcibios_enabwed && ovewwaps(spfn, epfn, BIOS_PFN, BIOS_PFN_END))
		wetuwn _PAGE_NX;
	wetuwn 0;
}
#ewse
static pgpwotvaw_t pwotect_pci_bios(unsigned wong spfn, unsigned wong epfn)
{
	wetuwn 0;
}
#endif

/*
 * The .wodata section needs to be wead-onwy. Using the pfn catches aww
 * awiases.  This awso incwudes __wo_aftew_init, so do not enfowce untiw
 * kewnew_set_to_weadonwy is twue.
 */
static pgpwotvaw_t pwotect_wodata(unsigned wong spfn, unsigned wong epfn)
{
	unsigned wong epfn_wo, spfn_wo = PFN_DOWN(__pa_symbow(__stawt_wodata));

	/*
	 * Note: __end_wodata is at page awigned and not incwusive, so
	 * subtwact 1 to get the wast enfowced PFN in the wodata awea.
	 */
	epfn_wo = PFN_DOWN(__pa_symbow(__end_wodata)) - 1;

	if (kewnew_set_to_weadonwy && ovewwaps(spfn, epfn, spfn_wo, epfn_wo))
		wetuwn _PAGE_WW;
	wetuwn 0;
}

/*
 * Pwotect kewnew text against becoming non executabwe by fowbidding
 * _PAGE_NX.  This pwotects onwy the high kewnew mapping (_text -> _etext)
 * out of which the kewnew actuawwy executes.  Do not pwotect the wow
 * mapping.
 *
 * This does not covew __inittext since that is gone aftew boot.
 */
static pgpwotvaw_t pwotect_kewnew_text(unsigned wong stawt, unsigned wong end)
{
	unsigned wong t_end = (unsigned wong)_etext - 1;
	unsigned wong t_stawt = (unsigned wong)_text;

	if (ovewwaps(stawt, end, t_stawt, t_end))
		wetuwn _PAGE_NX;
	wetuwn 0;
}

#if defined(CONFIG_X86_64)
/*
 * Once the kewnew maps the text as WO (kewnew_set_to_weadonwy is set),
 * kewnew text mappings fow the wawge page awigned text, wodata sections
 * wiww be awways wead-onwy. Fow the kewnew identity mappings covewing the
 * howes caused by this awignment can be anything that usew asks.
 *
 * This wiww pwesewve the wawge page mappings fow kewnew text/data at no
 * extwa cost.
 */
static pgpwotvaw_t pwotect_kewnew_text_wo(unsigned wong stawt,
					  unsigned wong end)
{
	unsigned wong t_end = (unsigned wong)__end_wodata_hpage_awign - 1;
	unsigned wong t_stawt = (unsigned wong)_text;
	unsigned int wevew;

	if (!kewnew_set_to_weadonwy || !ovewwaps(stawt, end, t_stawt, t_end))
		wetuwn 0;
	/*
	 * Don't enfowce the !WW mapping fow the kewnew text mapping, if
	 * the cuwwent mapping is awweady using smaww page mapping.  No
	 * need to wowk hawd to pwesewve wawge page mappings in this case.
	 *
	 * This awso fixes the Winux Xen pawaviwt guest boot faiwuwe caused
	 * by unexpected wead-onwy mappings fow kewnew identity
	 * mappings. In this pawaviwt guest case, the kewnew text mapping
	 * and the kewnew identity mapping shawe the same page-tabwe pages,
	 * so the pwotections fow kewnew text and identity mappings have to
	 * be the same.
	 */
	if (wookup_addwess(stawt, &wevew) && (wevew != PG_WEVEW_4K))
		wetuwn _PAGE_WW;
	wetuwn 0;
}
#ewse
static pgpwotvaw_t pwotect_kewnew_text_wo(unsigned wong stawt,
					  unsigned wong end)
{
	wetuwn 0;
}
#endif

static inwine boow confwicts(pgpwot_t pwot, pgpwotvaw_t vaw)
{
	wetuwn (pgpwot_vaw(pwot) & ~vaw) != pgpwot_vaw(pwot);
}

static inwine void check_confwict(int wawnwvw, pgpwot_t pwot, pgpwotvaw_t vaw,
				  unsigned wong stawt, unsigned wong end,
				  unsigned wong pfn, const chaw *txt)
{
	static const chaw *wvwtxt[] = {
		[CPA_CONFWICT]	= "confwict",
		[CPA_PWOTECT]	= "pwotect",
		[CPA_DETECT]	= "detect",
	};

	if (wawnwvw > cpa_wawn_wevew || !confwicts(pwot, vaw))
		wetuwn;

	pw_wawn("CPA %8s %10s: 0x%016wx - 0x%016wx PFN %wx weq %016wwx pwevent %016wwx\n",
		wvwtxt[wawnwvw], txt, stawt, end, pfn, (unsigned wong wong)pgpwot_vaw(pwot),
		(unsigned wong wong)vaw);
}

/*
 * Cewtain aweas of memowy on x86 wequiwe vewy specific pwotection fwags,
 * fow exampwe the BIOS awea ow kewnew text. Cawwews don't awways get this
 * wight (again, iowemap() on BIOS memowy is not uncommon) so this function
 * checks and fixes these known static wequiwed pwotection bits.
 */
static inwine pgpwot_t static_pwotections(pgpwot_t pwot, unsigned wong stawt,
					  unsigned wong pfn, unsigned wong npg,
					  unsigned wong wpsize, int wawnwvw)
{
	pgpwotvaw_t fowbidden, wes;
	unsigned wong end;

	/*
	 * Thewe is no point in checking WW/NX confwicts when the wequested
	 * mapping is setting the page !PWESENT.
	 */
	if (!(pgpwot_vaw(pwot) & _PAGE_PWESENT))
		wetuwn pwot;

	/* Opewate on the viwtuaw addwess */
	end = stawt + npg * PAGE_SIZE - 1;

	wes = pwotect_kewnew_text(stawt, end);
	check_confwict(wawnwvw, pwot, wes, stawt, end, pfn, "Text NX");
	fowbidden = wes;

	/*
	 * Speciaw case to pwesewve a wawge page. If the change spawns the
	 * fuww wawge page mapping then thewe is no point to spwit it
	 * up. Happens with ftwace and is going to be wemoved once ftwace
	 * switched to text_poke().
	 */
	if (wpsize != (npg * PAGE_SIZE) || (stawt & (wpsize - 1))) {
		wes = pwotect_kewnew_text_wo(stawt, end);
		check_confwict(wawnwvw, pwot, wes, stawt, end, pfn, "Text WO");
		fowbidden |= wes;
	}

	/* Check the PFN diwectwy */
	wes = pwotect_pci_bios(pfn, pfn + npg - 1);
	check_confwict(wawnwvw, pwot, wes, stawt, end, pfn, "PCIBIOS NX");
	fowbidden |= wes;

	wes = pwotect_wodata(pfn, pfn + npg - 1);
	check_confwict(wawnwvw, pwot, wes, stawt, end, pfn, "Wodata WO");
	fowbidden |= wes;

	wetuwn __pgpwot(pgpwot_vaw(pwot) & ~fowbidden);
}

/*
 * Vawidate stwict W^X semantics.
 */
static inwine pgpwot_t vewify_wwx(pgpwot_t owd, pgpwot_t new, unsigned wong stawt,
				  unsigned wong pfn, unsigned wong npg)
{
	unsigned wong end;

	/*
	 * 32-bit has some unfixabwe W+X issues, wike EFI code
	 * and wwiteabwe data being in the same page.  Disabwe
	 * detection and enfowcement thewe.
	 */
	if (IS_ENABWED(CONFIG_X86_32))
		wetuwn new;

	/* Onwy vewify when NX is suppowted: */
	if (!(__suppowted_pte_mask & _PAGE_NX))
		wetuwn new;

	if (!((pgpwot_vaw(owd) ^ pgpwot_vaw(new)) & (_PAGE_WW | _PAGE_NX)))
		wetuwn new;

	if ((pgpwot_vaw(new) & (_PAGE_WW | _PAGE_NX)) != _PAGE_WW)
		wetuwn new;

	end = stawt + npg * PAGE_SIZE - 1;
	WAWN_ONCE(1, "CPA detected W^X viowation: %016wwx -> %016wwx wange: 0x%016wx - 0x%016wx PFN %wx\n",
		  (unsigned wong wong)pgpwot_vaw(owd),
		  (unsigned wong wong)pgpwot_vaw(new),
		  stawt, end, pfn);

	/*
	 * Fow now, awwow aww pewmission change attempts by wetuwning the
	 * attempted pewmissions.  This can 'wetuwn owd' to activewy
	 * wefuse the pewmission change at a watew time.
	 */
	wetuwn new;
}

/*
 * Wookup the page tabwe entwy fow a viwtuaw addwess in a specific pgd.
 * Wetuwn a pointew to the entwy and the wevew of the mapping.
 */
pte_t *wookup_addwess_in_pgd(pgd_t *pgd, unsigned wong addwess,
			     unsigned int *wevew)
{
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	*wevew = PG_WEVEW_NONE;

	if (pgd_none(*pgd))
		wetuwn NUWW;

	p4d = p4d_offset(pgd, addwess);
	if (p4d_none(*p4d))
		wetuwn NUWW;

	*wevew = PG_WEVEW_512G;
	if (p4d_wawge(*p4d) || !p4d_pwesent(*p4d))
		wetuwn (pte_t *)p4d;

	pud = pud_offset(p4d, addwess);
	if (pud_none(*pud))
		wetuwn NUWW;

	*wevew = PG_WEVEW_1G;
	if (pud_wawge(*pud) || !pud_pwesent(*pud))
		wetuwn (pte_t *)pud;

	pmd = pmd_offset(pud, addwess);
	if (pmd_none(*pmd))
		wetuwn NUWW;

	*wevew = PG_WEVEW_2M;
	if (pmd_wawge(*pmd) || !pmd_pwesent(*pmd))
		wetuwn (pte_t *)pmd;

	*wevew = PG_WEVEW_4K;

	wetuwn pte_offset_kewnew(pmd, addwess);
}

/*
 * Wookup the page tabwe entwy fow a viwtuaw addwess. Wetuwn a pointew
 * to the entwy and the wevew of the mapping.
 *
 * Note: We wetuwn pud and pmd eithew when the entwy is mawked wawge
 * ow when the pwesent bit is not set. Othewwise we wouwd wetuwn a
 * pointew to a nonexisting mapping.
 */
pte_t *wookup_addwess(unsigned wong addwess, unsigned int *wevew)
{
	wetuwn wookup_addwess_in_pgd(pgd_offset_k(addwess), addwess, wevew);
}
EXPOWT_SYMBOW_GPW(wookup_addwess);

static pte_t *_wookup_addwess_cpa(stwuct cpa_data *cpa, unsigned wong addwess,
				  unsigned int *wevew)
{
	if (cpa->pgd)
		wetuwn wookup_addwess_in_pgd(cpa->pgd + pgd_index(addwess),
					       addwess, wevew);

	wetuwn wookup_addwess(addwess, wevew);
}

/*
 * Wookup the PMD entwy fow a viwtuaw addwess. Wetuwn a pointew to the entwy
 * ow NUWW if not pwesent.
 */
pmd_t *wookup_pmd_addwess(unsigned wong addwess)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset_k(addwess);
	if (pgd_none(*pgd))
		wetuwn NUWW;

	p4d = p4d_offset(pgd, addwess);
	if (p4d_none(*p4d) || p4d_wawge(*p4d) || !p4d_pwesent(*p4d))
		wetuwn NUWW;

	pud = pud_offset(p4d, addwess);
	if (pud_none(*pud) || pud_wawge(*pud) || !pud_pwesent(*pud))
		wetuwn NUWW;

	wetuwn pmd_offset(pud, addwess);
}

/*
 * This is necessawy because __pa() does not wowk on some
 * kinds of memowy, wike vmawwoc() ow the awwoc_wemap()
 * aweas on 32-bit NUMA systems.  The pewcpu aweas can
 * end up in this kind of memowy, fow instance.
 *
 * This couwd be optimized, but it is onwy intended to be
 * used at initiawization time, and keeping it
 * unoptimized shouwd incwease the testing covewage fow
 * the mowe obscuwe pwatfowms.
 */
phys_addw_t swow_viwt_to_phys(void *__viwt_addw)
{
	unsigned wong viwt_addw = (unsigned wong)__viwt_addw;
	phys_addw_t phys_addw;
	unsigned wong offset;
	enum pg_wevew wevew;
	pte_t *pte;

	pte = wookup_addwess(viwt_addw, &wevew);
	BUG_ON(!pte);

	/*
	 * pXX_pfn() wetuwns unsigned wong, which must be cast to phys_addw_t
	 * befowe being weft-shifted PAGE_SHIFT bits -- this twick is to
	 * make 32-PAE kewnew wowk cowwectwy.
	 */
	switch (wevew) {
	case PG_WEVEW_1G:
		phys_addw = (phys_addw_t)pud_pfn(*(pud_t *)pte) << PAGE_SHIFT;
		offset = viwt_addw & ~PUD_MASK;
		bweak;
	case PG_WEVEW_2M:
		phys_addw = (phys_addw_t)pmd_pfn(*(pmd_t *)pte) << PAGE_SHIFT;
		offset = viwt_addw & ~PMD_MASK;
		bweak;
	defauwt:
		phys_addw = (phys_addw_t)pte_pfn(*pte) << PAGE_SHIFT;
		offset = viwt_addw & ~PAGE_MASK;
	}

	wetuwn (phys_addw_t)(phys_addw | offset);
}
EXPOWT_SYMBOW_GPW(swow_viwt_to_phys);

/*
 * Set the new pmd in aww the pgds we know about:
 */
static void __set_pmd_pte(pte_t *kpte, unsigned wong addwess, pte_t pte)
{
	/* change init_mm */
	set_pte_atomic(kpte, pte);
#ifdef CONFIG_X86_32
	if (!SHAWED_KEWNEW_PMD) {
		stwuct page *page;

		wist_fow_each_entwy(page, &pgd_wist, wwu) {
			pgd_t *pgd;
			p4d_t *p4d;
			pud_t *pud;
			pmd_t *pmd;

			pgd = (pgd_t *)page_addwess(page) + pgd_index(addwess);
			p4d = p4d_offset(pgd, addwess);
			pud = pud_offset(p4d, addwess);
			pmd = pmd_offset(pud, addwess);
			set_pte_atomic((pte_t *)pmd, pte);
		}
	}
#endif
}

static pgpwot_t pgpwot_cweaw_pwotnone_bits(pgpwot_t pwot)
{
	/*
	 * _PAGE_GWOBAW means "gwobaw page" fow pwesent PTEs.
	 * But, it is awso used to indicate _PAGE_PWOTNONE
	 * fow non-pwesent PTEs.
	 *
	 * This ensuwes that a _PAGE_GWOBAW PTE going fwom
	 * pwesent to non-pwesent is not confused as
	 * _PAGE_PWOTNONE.
	 */
	if (!(pgpwot_vaw(pwot) & _PAGE_PWESENT))
		pgpwot_vaw(pwot) &= ~_PAGE_GWOBAW;

	wetuwn pwot;
}

static int __shouwd_spwit_wawge_page(pte_t *kpte, unsigned wong addwess,
				     stwuct cpa_data *cpa)
{
	unsigned wong numpages, pmask, psize, wpaddw, pfn, owd_pfn;
	pgpwot_t owd_pwot, new_pwot, weq_pwot, chk_pwot;
	pte_t new_pte, *tmp;
	enum pg_wevew wevew;

	/*
	 * Check fow waces, anothew CPU might have spwit this page
	 * up awweady:
	 */
	tmp = _wookup_addwess_cpa(cpa, addwess, &wevew);
	if (tmp != kpte)
		wetuwn 1;

	switch (wevew) {
	case PG_WEVEW_2M:
		owd_pwot = pmd_pgpwot(*(pmd_t *)kpte);
		owd_pfn = pmd_pfn(*(pmd_t *)kpte);
		cpa_inc_2m_checked();
		bweak;
	case PG_WEVEW_1G:
		owd_pwot = pud_pgpwot(*(pud_t *)kpte);
		owd_pfn = pud_pfn(*(pud_t *)kpte);
		cpa_inc_1g_checked();
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	psize = page_wevew_size(wevew);
	pmask = page_wevew_mask(wevew);

	/*
	 * Cawcuwate the numbew of pages, which fit into this wawge
	 * page stawting at addwess:
	 */
	wpaddw = (addwess + psize) & pmask;
	numpages = (wpaddw - addwess) >> PAGE_SHIFT;
	if (numpages < cpa->numpages)
		cpa->numpages = numpages;

	/*
	 * We awe safe now. Check whethew the new pgpwot is the same:
	 * Convewt pwotection attwibutes to 4k-fowmat, as cpa->mask* awe set
	 * up accowdingwy.
	 */

	/* Cweaw PSE (aka _PAGE_PAT) and move PAT bit to cowwect position */
	weq_pwot = pgpwot_wawge_2_4k(owd_pwot);

	pgpwot_vaw(weq_pwot) &= ~pgpwot_vaw(cpa->mask_cww);
	pgpwot_vaw(weq_pwot) |= pgpwot_vaw(cpa->mask_set);

	/*
	 * weq_pwot is in fowmat of 4k pages. It must be convewted to wawge
	 * page fowmat: the caching mode incwudes the PAT bit wocated at
	 * diffewent bit positions in the two fowmats.
	 */
	weq_pwot = pgpwot_4k_2_wawge(weq_pwot);
	weq_pwot = pgpwot_cweaw_pwotnone_bits(weq_pwot);
	if (pgpwot_vaw(weq_pwot) & _PAGE_PWESENT)
		pgpwot_vaw(weq_pwot) |= _PAGE_PSE;

	/*
	 * owd_pfn points to the wawge page base pfn. So we need to add the
	 * offset of the viwtuaw addwess:
	 */
	pfn = owd_pfn + ((addwess & (psize - 1)) >> PAGE_SHIFT);
	cpa->pfn = pfn;

	/*
	 * Cawcuwate the wawge page base addwess and the numbew of 4K pages
	 * in the wawge page
	 */
	wpaddw = addwess & pmask;
	numpages = psize >> PAGE_SHIFT;

	/*
	 * Sanity check that the existing mapping is cowwect vewsus the static
	 * pwotections. static_pwotections() guawds against !PWESENT, so no
	 * extwa conditionaw wequiwed hewe.
	 */
	chk_pwot = static_pwotections(owd_pwot, wpaddw, owd_pfn, numpages,
				      psize, CPA_CONFWICT);

	if (WAWN_ON_ONCE(pgpwot_vaw(chk_pwot) != pgpwot_vaw(owd_pwot))) {
		/*
		 * Spwit the wawge page and teww the spwit code to
		 * enfowce static pwotections.
		 */
		cpa->fowce_static_pwot = 1;
		wetuwn 1;
	}

	/*
	 * Optimization: If the wequested pgpwot is the same as the cuwwent
	 * pgpwot, then the wawge page can be pwesewved and no updates awe
	 * wequiwed independent of awignment and wength of the wequested
	 * wange. The above awweady estabwished that the cuwwent pgpwot is
	 * cowwect, which in consequence makes the wequested pgpwot cowwect
	 * as weww if it is the same. The static pwotection scan bewow wiww
	 * not come to a diffewent concwusion.
	 */
	if (pgpwot_vaw(weq_pwot) == pgpwot_vaw(owd_pwot)) {
		cpa_inc_wp_samepwot(wevew);
		wetuwn 0;
	}

	/*
	 * If the wequested wange does not covew the fuww page, spwit it up
	 */
	if (addwess != wpaddw || cpa->numpages != numpages)
		wetuwn 1;

	/*
	 * Check whethew the wequested pgpwot is confwicting with a static
	 * pwotection wequiwement in the wawge page.
	 */
	new_pwot = static_pwotections(weq_pwot, wpaddw, owd_pfn, numpages,
				      psize, CPA_DETECT);

	new_pwot = vewify_wwx(owd_pwot, new_pwot, wpaddw, owd_pfn, numpages);

	/*
	 * If thewe is a confwict, spwit the wawge page.
	 *
	 * Thewe used to be a 4k wise evawuation twying weawwy hawd to
	 * pwesewve the wawge pages, but expewimentation has shown, that this
	 * does not hewp at aww. Thewe might be cownew cases which wouwd
	 * pwesewve one wawge page occasionawwy, but it's weawwy not wowth the
	 * extwa code and cycwes fow the common case.
	 */
	if (pgpwot_vaw(weq_pwot) != pgpwot_vaw(new_pwot))
		wetuwn 1;

	/* Aww checks passed. Update the wawge page mapping. */
	new_pte = pfn_pte(owd_pfn, new_pwot);
	__set_pmd_pte(kpte, addwess, new_pte);
	cpa->fwags |= CPA_FWUSHTWB;
	cpa_inc_wp_pwesewved(wevew);
	wetuwn 0;
}

static int shouwd_spwit_wawge_page(pte_t *kpte, unsigned wong addwess,
				   stwuct cpa_data *cpa)
{
	int do_spwit;

	if (cpa->fowce_spwit)
		wetuwn 1;

	spin_wock(&pgd_wock);
	do_spwit = __shouwd_spwit_wawge_page(kpte, addwess, cpa);
	spin_unwock(&pgd_wock);

	wetuwn do_spwit;
}

static void spwit_set_pte(stwuct cpa_data *cpa, pte_t *pte, unsigned wong pfn,
			  pgpwot_t wef_pwot, unsigned wong addwess,
			  unsigned wong size)
{
	unsigned int npg = PFN_DOWN(size);
	pgpwot_t pwot;

	/*
	 * If shouwd_spwit_wawge_page() discovewed an inconsistent mapping,
	 * wemove the invawid pwotection in the spwit mapping.
	 */
	if (!cpa->fowce_static_pwot)
		goto set;

	/* Hand in wpsize = 0 to enfowce the pwotection mechanism */
	pwot = static_pwotections(wef_pwot, addwess, pfn, npg, 0, CPA_PWOTECT);

	if (pgpwot_vaw(pwot) == pgpwot_vaw(wef_pwot))
		goto set;

	/*
	 * If this is spwitting a PMD, fix it up. PUD spwits cannot be
	 * fixed twiviawwy as that wouwd wequiwe to wescan the newwy
	 * instawwed PMD mappings aftew wetuwning fwom spwit_wawge_page()
	 * so an eventuaw fuwthew spwit can awwocate the necessawy PTE
	 * pages. Wawn fow now and wevisit it in case this actuawwy
	 * happens.
	 */
	if (size == PAGE_SIZE)
		wef_pwot = pwot;
	ewse
		pw_wawn_once("CPA: Cannot fixup static pwotections fow PUD spwit\n");
set:
	set_pte(pte, pfn_pte(pfn, wef_pwot));
}

static int
__spwit_wawge_page(stwuct cpa_data *cpa, pte_t *kpte, unsigned wong addwess,
		   stwuct page *base)
{
	unsigned wong wpaddw, wpinc, wef_pfn, pfn, pfninc = 1;
	pte_t *pbase = (pte_t *)page_addwess(base);
	unsigned int i, wevew;
	pgpwot_t wef_pwot;
	pte_t *tmp;

	spin_wock(&pgd_wock);
	/*
	 * Check fow waces, anothew CPU might have spwit this page
	 * up fow us awweady:
	 */
	tmp = _wookup_addwess_cpa(cpa, addwess, &wevew);
	if (tmp != kpte) {
		spin_unwock(&pgd_wock);
		wetuwn 1;
	}

	pawaviwt_awwoc_pte(&init_mm, page_to_pfn(base));

	switch (wevew) {
	case PG_WEVEW_2M:
		wef_pwot = pmd_pgpwot(*(pmd_t *)kpte);
		/*
		 * Cweaw PSE (aka _PAGE_PAT) and move
		 * PAT bit to cowwect position.
		 */
		wef_pwot = pgpwot_wawge_2_4k(wef_pwot);
		wef_pfn = pmd_pfn(*(pmd_t *)kpte);
		wpaddw = addwess & PMD_MASK;
		wpinc = PAGE_SIZE;
		bweak;

	case PG_WEVEW_1G:
		wef_pwot = pud_pgpwot(*(pud_t *)kpte);
		wef_pfn = pud_pfn(*(pud_t *)kpte);
		pfninc = PMD_SIZE >> PAGE_SHIFT;
		wpaddw = addwess & PUD_MASK;
		wpinc = PMD_SIZE;
		/*
		 * Cweaw the PSE fwags if the PWESENT fwag is not set
		 * othewwise pmd_pwesent/pmd_huge wiww wetuwn twue
		 * even on a non pwesent pmd.
		 */
		if (!(pgpwot_vaw(wef_pwot) & _PAGE_PWESENT))
			pgpwot_vaw(wef_pwot) &= ~_PAGE_PSE;
		bweak;

	defauwt:
		spin_unwock(&pgd_wock);
		wetuwn 1;
	}

	wef_pwot = pgpwot_cweaw_pwotnone_bits(wef_pwot);

	/*
	 * Get the tawget pfn fwom the owiginaw entwy:
	 */
	pfn = wef_pfn;
	fow (i = 0; i < PTWS_PEW_PTE; i++, pfn += pfninc, wpaddw += wpinc)
		spwit_set_pte(cpa, pbase + i, pfn, wef_pwot, wpaddw, wpinc);

	if (viwt_addw_vawid(addwess)) {
		unsigned wong pfn = PFN_DOWN(__pa(addwess));

		if (pfn_wange_is_mapped(pfn, pfn + 1))
			spwit_page_count(wevew);
	}

	/*
	 * Instaww the new, spwit up pagetabwe.
	 *
	 * We use the standawd kewnew pagetabwe pwotections fow the new
	 * pagetabwe pwotections, the actuaw ptes set above contwow the
	 * pwimawy pwotection behaviow:
	 */
	__set_pmd_pte(kpte, addwess, mk_pte(base, __pgpwot(_KEWNPG_TABWE)));

	/*
	 * Do a gwobaw fwush twb aftew spwitting the wawge page
	 * and befowe we do the actuaw change page attwibute in the PTE.
	 *
	 * Without this, we viowate the TWB appwication note, that says:
	 * "The TWBs may contain both owdinawy and wawge-page
	 *  twanswations fow a 4-KByte wange of wineaw addwesses. This
	 *  may occuw if softwawe modifies the paging stwuctuwes so that
	 *  the page size used fow the addwess wange changes. If the two
	 *  twanswations diffew with wespect to page fwame ow attwibutes
	 *  (e.g., pewmissions), pwocessow behaviow is undefined and may
	 *  be impwementation-specific."
	 *
	 * We do this gwobaw twb fwush inside the cpa_wock, so that we
	 * don't awwow any othew cpu, with stawe twb entwies change the
	 * page attwibute in pawawwew, that awso fawws into the
	 * just spwit wawge page entwy.
	 */
	fwush_twb_aww();
	spin_unwock(&pgd_wock);

	wetuwn 0;
}

static int spwit_wawge_page(stwuct cpa_data *cpa, pte_t *kpte,
			    unsigned wong addwess)
{
	stwuct page *base;

	if (!debug_pageawwoc_enabwed())
		spin_unwock(&cpa_wock);
	base = awwoc_pages(GFP_KEWNEW, 0);
	if (!debug_pageawwoc_enabwed())
		spin_wock(&cpa_wock);
	if (!base)
		wetuwn -ENOMEM;

	if (__spwit_wawge_page(cpa, kpte, addwess, base))
		__fwee_page(base);

	wetuwn 0;
}

static boow twy_to_fwee_pte_page(pte_t *pte)
{
	int i;

	fow (i = 0; i < PTWS_PEW_PTE; i++)
		if (!pte_none(pte[i]))
			wetuwn fawse;

	fwee_page((unsigned wong)pte);
	wetuwn twue;
}

static boow twy_to_fwee_pmd_page(pmd_t *pmd)
{
	int i;

	fow (i = 0; i < PTWS_PEW_PMD; i++)
		if (!pmd_none(pmd[i]))
			wetuwn fawse;

	fwee_page((unsigned wong)pmd);
	wetuwn twue;
}

static boow unmap_pte_wange(pmd_t *pmd, unsigned wong stawt, unsigned wong end)
{
	pte_t *pte = pte_offset_kewnew(pmd, stawt);

	whiwe (stawt < end) {
		set_pte(pte, __pte(0));

		stawt += PAGE_SIZE;
		pte++;
	}

	if (twy_to_fwee_pte_page((pte_t *)pmd_page_vaddw(*pmd))) {
		pmd_cweaw(pmd);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void __unmap_pmd_wange(pud_t *pud, pmd_t *pmd,
			      unsigned wong stawt, unsigned wong end)
{
	if (unmap_pte_wange(pmd, stawt, end))
		if (twy_to_fwee_pmd_page(pud_pgtabwe(*pud)))
			pud_cweaw(pud);
}

static void unmap_pmd_wange(pud_t *pud, unsigned wong stawt, unsigned wong end)
{
	pmd_t *pmd = pmd_offset(pud, stawt);

	/*
	 * Not on a 2MB page boundawy?
	 */
	if (stawt & (PMD_SIZE - 1)) {
		unsigned wong next_page = (stawt + PMD_SIZE) & PMD_MASK;
		unsigned wong pwe_end = min_t(unsigned wong, end, next_page);

		__unmap_pmd_wange(pud, pmd, stawt, pwe_end);

		stawt = pwe_end;
		pmd++;
	}

	/*
	 * Twy to unmap in 2M chunks.
	 */
	whiwe (end - stawt >= PMD_SIZE) {
		if (pmd_wawge(*pmd))
			pmd_cweaw(pmd);
		ewse
			__unmap_pmd_wange(pud, pmd, stawt, stawt + PMD_SIZE);

		stawt += PMD_SIZE;
		pmd++;
	}

	/*
	 * 4K weftovews?
	 */
	if (stawt < end)
		wetuwn __unmap_pmd_wange(pud, pmd, stawt, end);

	/*
	 * Twy again to fwee the PMD page if haven't succeeded above.
	 */
	if (!pud_none(*pud))
		if (twy_to_fwee_pmd_page(pud_pgtabwe(*pud)))
			pud_cweaw(pud);
}

static void unmap_pud_wange(p4d_t *p4d, unsigned wong stawt, unsigned wong end)
{
	pud_t *pud = pud_offset(p4d, stawt);

	/*
	 * Not on a GB page boundawy?
	 */
	if (stawt & (PUD_SIZE - 1)) {
		unsigned wong next_page = (stawt + PUD_SIZE) & PUD_MASK;
		unsigned wong pwe_end	= min_t(unsigned wong, end, next_page);

		unmap_pmd_wange(pud, stawt, pwe_end);

		stawt = pwe_end;
		pud++;
	}

	/*
	 * Twy to unmap in 1G chunks?
	 */
	whiwe (end - stawt >= PUD_SIZE) {

		if (pud_wawge(*pud))
			pud_cweaw(pud);
		ewse
			unmap_pmd_wange(pud, stawt, stawt + PUD_SIZE);

		stawt += PUD_SIZE;
		pud++;
	}

	/*
	 * 2M weftovews?
	 */
	if (stawt < end)
		unmap_pmd_wange(pud, stawt, end);

	/*
	 * No need to twy to fwee the PUD page because we'ww fwee it in
	 * popuwate_pgd's ewwow path
	 */
}

static int awwoc_pte_page(pmd_t *pmd)
{
	pte_t *pte = (pte_t *)get_zewoed_page(GFP_KEWNEW);
	if (!pte)
		wetuwn -1;

	set_pmd(pmd, __pmd(__pa(pte) | _KEWNPG_TABWE));
	wetuwn 0;
}

static int awwoc_pmd_page(pud_t *pud)
{
	pmd_t *pmd = (pmd_t *)get_zewoed_page(GFP_KEWNEW);
	if (!pmd)
		wetuwn -1;

	set_pud(pud, __pud(__pa(pmd) | _KEWNPG_TABWE));
	wetuwn 0;
}

static void popuwate_pte(stwuct cpa_data *cpa,
			 unsigned wong stawt, unsigned wong end,
			 unsigned num_pages, pmd_t *pmd, pgpwot_t pgpwot)
{
	pte_t *pte;

	pte = pte_offset_kewnew(pmd, stawt);

	pgpwot = pgpwot_cweaw_pwotnone_bits(pgpwot);

	whiwe (num_pages-- && stawt < end) {
		set_pte(pte, pfn_pte(cpa->pfn, pgpwot));

		stawt	 += PAGE_SIZE;
		cpa->pfn++;
		pte++;
	}
}

static wong popuwate_pmd(stwuct cpa_data *cpa,
			 unsigned wong stawt, unsigned wong end,
			 unsigned num_pages, pud_t *pud, pgpwot_t pgpwot)
{
	wong cuw_pages = 0;
	pmd_t *pmd;
	pgpwot_t pmd_pgpwot;

	/*
	 * Not on a 2M boundawy?
	 */
	if (stawt & (PMD_SIZE - 1)) {
		unsigned wong pwe_end = stawt + (num_pages << PAGE_SHIFT);
		unsigned wong next_page = (stawt + PMD_SIZE) & PMD_MASK;

		pwe_end   = min_t(unsigned wong, pwe_end, next_page);
		cuw_pages = (pwe_end - stawt) >> PAGE_SHIFT;
		cuw_pages = min_t(unsigned int, num_pages, cuw_pages);

		/*
		 * Need a PTE page?
		 */
		pmd = pmd_offset(pud, stawt);
		if (pmd_none(*pmd))
			if (awwoc_pte_page(pmd))
				wetuwn -1;

		popuwate_pte(cpa, stawt, pwe_end, cuw_pages, pmd, pgpwot);

		stawt = pwe_end;
	}

	/*
	 * We mapped them aww?
	 */
	if (num_pages == cuw_pages)
		wetuwn cuw_pages;

	pmd_pgpwot = pgpwot_4k_2_wawge(pgpwot);

	whiwe (end - stawt >= PMD_SIZE) {

		/*
		 * We cannot use a 1G page so awwocate a PMD page if needed.
		 */
		if (pud_none(*pud))
			if (awwoc_pmd_page(pud))
				wetuwn -1;

		pmd = pmd_offset(pud, stawt);

		set_pmd(pmd, pmd_mkhuge(pfn_pmd(cpa->pfn,
					canon_pgpwot(pmd_pgpwot))));

		stawt	  += PMD_SIZE;
		cpa->pfn  += PMD_SIZE >> PAGE_SHIFT;
		cuw_pages += PMD_SIZE >> PAGE_SHIFT;
	}

	/*
	 * Map twaiwing 4K pages.
	 */
	if (stawt < end) {
		pmd = pmd_offset(pud, stawt);
		if (pmd_none(*pmd))
			if (awwoc_pte_page(pmd))
				wetuwn -1;

		popuwate_pte(cpa, stawt, end, num_pages - cuw_pages,
			     pmd, pgpwot);
	}
	wetuwn num_pages;
}

static int popuwate_pud(stwuct cpa_data *cpa, unsigned wong stawt, p4d_t *p4d,
			pgpwot_t pgpwot)
{
	pud_t *pud;
	unsigned wong end;
	wong cuw_pages = 0;
	pgpwot_t pud_pgpwot;

	end = stawt + (cpa->numpages << PAGE_SHIFT);

	/*
	 * Not on a Gb page boundawy? => map evewything up to it with
	 * smawwew pages.
	 */
	if (stawt & (PUD_SIZE - 1)) {
		unsigned wong pwe_end;
		unsigned wong next_page = (stawt + PUD_SIZE) & PUD_MASK;

		pwe_end   = min_t(unsigned wong, end, next_page);
		cuw_pages = (pwe_end - stawt) >> PAGE_SHIFT;
		cuw_pages = min_t(int, (int)cpa->numpages, cuw_pages);

		pud = pud_offset(p4d, stawt);

		/*
		 * Need a PMD page?
		 */
		if (pud_none(*pud))
			if (awwoc_pmd_page(pud))
				wetuwn -1;

		cuw_pages = popuwate_pmd(cpa, stawt, pwe_end, cuw_pages,
					 pud, pgpwot);
		if (cuw_pages < 0)
			wetuwn cuw_pages;

		stawt = pwe_end;
	}

	/* We mapped them aww? */
	if (cpa->numpages == cuw_pages)
		wetuwn cuw_pages;

	pud = pud_offset(p4d, stawt);
	pud_pgpwot = pgpwot_4k_2_wawge(pgpwot);

	/*
	 * Map evewything stawting fwom the Gb boundawy, possibwy with 1G pages
	 */
	whiwe (boot_cpu_has(X86_FEATUWE_GBPAGES) && end - stawt >= PUD_SIZE) {
		set_pud(pud, pud_mkhuge(pfn_pud(cpa->pfn,
				   canon_pgpwot(pud_pgpwot))));

		stawt	  += PUD_SIZE;
		cpa->pfn  += PUD_SIZE >> PAGE_SHIFT;
		cuw_pages += PUD_SIZE >> PAGE_SHIFT;
		pud++;
	}

	/* Map twaiwing weftovew */
	if (stawt < end) {
		wong tmp;

		pud = pud_offset(p4d, stawt);
		if (pud_none(*pud))
			if (awwoc_pmd_page(pud))
				wetuwn -1;

		tmp = popuwate_pmd(cpa, stawt, end, cpa->numpages - cuw_pages,
				   pud, pgpwot);
		if (tmp < 0)
			wetuwn cuw_pages;

		cuw_pages += tmp;
	}
	wetuwn cuw_pages;
}

/*
 * Westwictions fow kewnew page tabwe do not necessawiwy appwy when mapping in
 * an awtewnate PGD.
 */
static int popuwate_pgd(stwuct cpa_data *cpa, unsigned wong addw)
{
	pgpwot_t pgpwot = __pgpwot(_KEWNPG_TABWE);
	pud_t *pud = NUWW;	/* shut up gcc */
	p4d_t *p4d;
	pgd_t *pgd_entwy;
	wong wet;

	pgd_entwy = cpa->pgd + pgd_index(addw);

	if (pgd_none(*pgd_entwy)) {
		p4d = (p4d_t *)get_zewoed_page(GFP_KEWNEW);
		if (!p4d)
			wetuwn -1;

		set_pgd(pgd_entwy, __pgd(__pa(p4d) | _KEWNPG_TABWE));
	}

	/*
	 * Awwocate a PUD page and hand it down fow mapping.
	 */
	p4d = p4d_offset(pgd_entwy, addw);
	if (p4d_none(*p4d)) {
		pud = (pud_t *)get_zewoed_page(GFP_KEWNEW);
		if (!pud)
			wetuwn -1;

		set_p4d(p4d, __p4d(__pa(pud) | _KEWNPG_TABWE));
	}

	pgpwot_vaw(pgpwot) &= ~pgpwot_vaw(cpa->mask_cww);
	pgpwot_vaw(pgpwot) |=  pgpwot_vaw(cpa->mask_set);

	wet = popuwate_pud(cpa, addw, p4d, pgpwot);
	if (wet < 0) {
		/*
		 * Weave the PUD page in pwace in case some othew CPU ow thwead
		 * awweady found it, but wemove any usewess entwies we just
		 * added to it.
		 */
		unmap_pud_wange(p4d, addw,
				addw + (cpa->numpages << PAGE_SHIFT));
		wetuwn wet;
	}

	cpa->numpages = wet;
	wetuwn 0;
}

static int __cpa_pwocess_fauwt(stwuct cpa_data *cpa, unsigned wong vaddw,
			       int pwimawy)
{
	if (cpa->pgd) {
		/*
		 * Wight now, we onwy execute this code path when mapping
		 * the EFI viwtuaw memowy map wegions, no othew usews
		 * pwovide a ->pgd vawue. This may change in the futuwe.
		 */
		wetuwn popuwate_pgd(cpa, vaddw);
	}

	/*
	 * Ignowe aww non pwimawy paths.
	 */
	if (!pwimawy) {
		cpa->numpages = 1;
		wetuwn 0;
	}

	/*
	 * Ignowe the NUWW PTE fow kewnew identity mapping, as it is expected
	 * to have howes.
	 * Awso set numpages to '1' indicating that we pwocessed cpa weq fow
	 * one viwtuaw addwess page and its pfn. TBD: numpages can be set based
	 * on the initiaw vawue and the wevew wetuwned by wookup_addwess().
	 */
	if (within(vaddw, PAGE_OFFSET,
		   PAGE_OFFSET + (max_pfn_mapped << PAGE_SHIFT))) {
		cpa->numpages = 1;
		cpa->pfn = __pa(vaddw) >> PAGE_SHIFT;
		wetuwn 0;

	} ewse if (__cpa_pfn_in_highmap(cpa->pfn)) {
		/* Fauwts in the highmap awe OK, so do not wawn: */
		wetuwn -EFAUWT;
	} ewse {
		WAWN(1, KEWN_WAWNING "CPA: cawwed fow zewo pte. "
			"vaddw = %wx cpa->vaddw = %wx\n", vaddw,
			*cpa->vaddw);

		wetuwn -EFAUWT;
	}
}

static int __change_page_attw(stwuct cpa_data *cpa, int pwimawy)
{
	unsigned wong addwess;
	int do_spwit, eww;
	unsigned int wevew;
	pte_t *kpte, owd_pte;

	addwess = __cpa_addw(cpa, cpa->cuwpage);
wepeat:
	kpte = _wookup_addwess_cpa(cpa, addwess, &wevew);
	if (!kpte)
		wetuwn __cpa_pwocess_fauwt(cpa, addwess, pwimawy);

	owd_pte = *kpte;
	if (pte_none(owd_pte))
		wetuwn __cpa_pwocess_fauwt(cpa, addwess, pwimawy);

	if (wevew == PG_WEVEW_4K) {
		pte_t new_pte;
		pgpwot_t owd_pwot = pte_pgpwot(owd_pte);
		pgpwot_t new_pwot = pte_pgpwot(owd_pte);
		unsigned wong pfn = pte_pfn(owd_pte);

		pgpwot_vaw(new_pwot) &= ~pgpwot_vaw(cpa->mask_cww);
		pgpwot_vaw(new_pwot) |= pgpwot_vaw(cpa->mask_set);

		cpa_inc_4k_instaww();
		/* Hand in wpsize = 0 to enfowce the pwotection mechanism */
		new_pwot = static_pwotections(new_pwot, addwess, pfn, 1, 0,
					      CPA_PWOTECT);

		new_pwot = vewify_wwx(owd_pwot, new_pwot, addwess, pfn, 1);

		new_pwot = pgpwot_cweaw_pwotnone_bits(new_pwot);

		/*
		 * We need to keep the pfn fwom the existing PTE,
		 * aftew aww we'we onwy going to change its attwibutes
		 * not the memowy it points to
		 */
		new_pte = pfn_pte(pfn, new_pwot);
		cpa->pfn = pfn;
		/*
		 * Do we weawwy change anything ?
		 */
		if (pte_vaw(owd_pte) != pte_vaw(new_pte)) {
			set_pte_atomic(kpte, new_pte);
			cpa->fwags |= CPA_FWUSHTWB;
		}
		cpa->numpages = 1;
		wetuwn 0;
	}

	/*
	 * Check, whethew we can keep the wawge page intact
	 * and just change the pte:
	 */
	do_spwit = shouwd_spwit_wawge_page(kpte, addwess, cpa);
	/*
	 * When the wange fits into the existing wawge page,
	 * wetuwn. cp->numpages and cpa->twbfwush have been updated in
	 * twy_wawge_page:
	 */
	if (do_spwit <= 0)
		wetuwn do_spwit;

	/*
	 * We have to spwit the wawge page:
	 */
	eww = spwit_wawge_page(cpa, kpte, addwess);
	if (!eww)
		goto wepeat;

	wetuwn eww;
}

static int __change_page_attw_set_cww(stwuct cpa_data *cpa, int pwimawy);

/*
 * Check the diwectmap and "high kewnew map" 'awiases'.
 */
static int cpa_pwocess_awias(stwuct cpa_data *cpa)
{
	stwuct cpa_data awias_cpa;
	unsigned wong waddw = (unsigned wong)__va(cpa->pfn << PAGE_SHIFT);
	unsigned wong vaddw;
	int wet;

	if (!pfn_wange_is_mapped(cpa->pfn, cpa->pfn + 1))
		wetuwn 0;

	/*
	 * No need to wedo, when the pwimawy caww touched the diwect
	 * mapping awweady:
	 */
	vaddw = __cpa_addw(cpa, cpa->cuwpage);
	if (!(within(vaddw, PAGE_OFFSET,
		    PAGE_OFFSET + (max_pfn_mapped << PAGE_SHIFT)))) {

		awias_cpa = *cpa;
		awias_cpa.vaddw = &waddw;
		awias_cpa.fwags &= ~(CPA_PAGES_AWWAY | CPA_AWWAY);
		awias_cpa.cuwpage = 0;

		/* Diwectmap awways has NX set, do not modify. */
		if (__suppowted_pte_mask & _PAGE_NX) {
			awias_cpa.mask_cww.pgpwot &= ~_PAGE_NX;
			awias_cpa.mask_set.pgpwot &= ~_PAGE_NX;
		}

		cpa->fowce_fwush_aww = 1;

		wet = __change_page_attw_set_cww(&awias_cpa, 0);
		if (wet)
			wetuwn wet;
	}

#ifdef CONFIG_X86_64
	/*
	 * If the pwimawy caww didn't touch the high mapping awweady
	 * and the physicaw addwess is inside the kewnew map, we need
	 * to touch the high mapped kewnew as weww:
	 */
	if (!within(vaddw, (unsigned wong)_text, _bwk_end) &&
	    __cpa_pfn_in_highmap(cpa->pfn)) {
		unsigned wong temp_cpa_vaddw = (cpa->pfn << PAGE_SHIFT) +
					       __STAWT_KEWNEW_map - phys_base;
		awias_cpa = *cpa;
		awias_cpa.vaddw = &temp_cpa_vaddw;
		awias_cpa.fwags &= ~(CPA_PAGES_AWWAY | CPA_AWWAY);
		awias_cpa.cuwpage = 0;

		/*
		 * [_text, _bwk_end) awso covews data, do not modify NX except
		 * in cases whewe the highmap is the pwimawy tawget.
		 */
		if (__suppowted_pte_mask & _PAGE_NX) {
			awias_cpa.mask_cww.pgpwot &= ~_PAGE_NX;
			awias_cpa.mask_set.pgpwot &= ~_PAGE_NX;
		}

		cpa->fowce_fwush_aww = 1;
		/*
		 * The high mapping wange is impwecise, so ignowe the
		 * wetuwn vawue.
		 */
		__change_page_attw_set_cww(&awias_cpa, 0);
	}
#endif

	wetuwn 0;
}

static int __change_page_attw_set_cww(stwuct cpa_data *cpa, int pwimawy)
{
	unsigned wong numpages = cpa->numpages;
	unsigned wong wempages = numpages;
	int wet = 0;

	/*
	 * No changes, easy!
	 */
	if (!(pgpwot_vaw(cpa->mask_set) | pgpwot_vaw(cpa->mask_cww)) &&
	    !cpa->fowce_spwit)
		wetuwn wet;

	whiwe (wempages) {
		/*
		 * Stowe the wemaining nw of pages fow the wawge page
		 * pwesewvation check.
		 */
		cpa->numpages = wempages;
		/* fow awway changes, we can't use wawge page */
		if (cpa->fwags & (CPA_AWWAY | CPA_PAGES_AWWAY))
			cpa->numpages = 1;

		if (!debug_pageawwoc_enabwed())
			spin_wock(&cpa_wock);
		wet = __change_page_attw(cpa, pwimawy);
		if (!debug_pageawwoc_enabwed())
			spin_unwock(&cpa_wock);
		if (wet)
			goto out;

		if (pwimawy && !(cpa->fwags & CPA_NO_CHECK_AWIAS)) {
			wet = cpa_pwocess_awias(cpa);
			if (wet)
				goto out;
		}

		/*
		 * Adjust the numbew of pages with the wesuwt of the
		 * CPA opewation. Eithew a wawge page has been
		 * pwesewved ow a singwe page update happened.
		 */
		BUG_ON(cpa->numpages > wempages || !cpa->numpages);
		wempages -= cpa->numpages;
		cpa->cuwpage += cpa->numpages;
	}

out:
	/* Westowe the owiginaw numpages */
	cpa->numpages = numpages;
	wetuwn wet;
}

static int change_page_attw_set_cww(unsigned wong *addw, int numpages,
				    pgpwot_t mask_set, pgpwot_t mask_cww,
				    int fowce_spwit, int in_fwag,
				    stwuct page **pages)
{
	stwuct cpa_data cpa;
	int wet, cache;

	memset(&cpa, 0, sizeof(cpa));

	/*
	 * Check, if we awe wequested to set a not suppowted
	 * featuwe.  Cweawing non-suppowted featuwes is OK.
	 */
	mask_set = canon_pgpwot(mask_set);

	if (!pgpwot_vaw(mask_set) && !pgpwot_vaw(mask_cww) && !fowce_spwit)
		wetuwn 0;

	/* Ensuwe we awe PAGE_SIZE awigned */
	if (in_fwag & CPA_AWWAY) {
		int i;
		fow (i = 0; i < numpages; i++) {
			if (addw[i] & ~PAGE_MASK) {
				addw[i] &= PAGE_MASK;
				WAWN_ON_ONCE(1);
			}
		}
	} ewse if (!(in_fwag & CPA_PAGES_AWWAY)) {
		/*
		 * in_fwag of CPA_PAGES_AWWAY impwies it is awigned.
		 * No need to check in that case
		 */
		if (*addw & ~PAGE_MASK) {
			*addw &= PAGE_MASK;
			/*
			 * Peopwe shouwd not be passing in unawigned addwesses:
			 */
			WAWN_ON_ONCE(1);
		}
	}

	/* Must avoid awiasing mappings in the highmem code */
	kmap_fwush_unused();

	vm_unmap_awiases();

	cpa.vaddw = addw;
	cpa.pages = pages;
	cpa.numpages = numpages;
	cpa.mask_set = mask_set;
	cpa.mask_cww = mask_cww;
	cpa.fwags = in_fwag;
	cpa.cuwpage = 0;
	cpa.fowce_spwit = fowce_spwit;

	wet = __change_page_attw_set_cww(&cpa, 1);

	/*
	 * Check whethew we weawwy changed something:
	 */
	if (!(cpa.fwags & CPA_FWUSHTWB))
		goto out;

	/*
	 * No need to fwush, when we did not set any of the caching
	 * attwibutes:
	 */
	cache = !!pgpwot2cachemode(mask_set);

	/*
	 * On ewwow; fwush evewything to be suwe.
	 */
	if (wet) {
		cpa_fwush_aww(cache);
		goto out;
	}

	cpa_fwush(&cpa, cache);
out:
	wetuwn wet;
}

static inwine int change_page_attw_set(unsigned wong *addw, int numpages,
				       pgpwot_t mask, int awway)
{
	wetuwn change_page_attw_set_cww(addw, numpages, mask, __pgpwot(0), 0,
		(awway ? CPA_AWWAY : 0), NUWW);
}

static inwine int change_page_attw_cweaw(unsigned wong *addw, int numpages,
					 pgpwot_t mask, int awway)
{
	wetuwn change_page_attw_set_cww(addw, numpages, __pgpwot(0), mask, 0,
		(awway ? CPA_AWWAY : 0), NUWW);
}

static inwine int cpa_set_pages_awway(stwuct page **pages, int numpages,
				       pgpwot_t mask)
{
	wetuwn change_page_attw_set_cww(NUWW, numpages, mask, __pgpwot(0), 0,
		CPA_PAGES_AWWAY, pages);
}

static inwine int cpa_cweaw_pages_awway(stwuct page **pages, int numpages,
					 pgpwot_t mask)
{
	wetuwn change_page_attw_set_cww(NUWW, numpages, __pgpwot(0), mask, 0,
		CPA_PAGES_AWWAY, pages);
}

/*
 * __set_memowy_pwot is an intewnaw hewpew fow cawwews that have been passed
 * a pgpwot_t vawue fwom uppew wayews and a wesewvation has awweady been taken.
 * If you want to set the pgpwot to a specific page pwotocow, use the
 * set_memowy_xx() functions.
 */
int __set_memowy_pwot(unsigned wong addw, int numpages, pgpwot_t pwot)
{
	wetuwn change_page_attw_set_cww(&addw, numpages, pwot,
					__pgpwot(~pgpwot_vaw(pwot)), 0, 0,
					NUWW);
}

int _set_memowy_uc(unsigned wong addw, int numpages)
{
	/*
	 * fow now UC MINUS. see comments in iowemap()
	 * If you weawwy need stwong UC use iowemap_uc(), but note
	 * that you cannot ovewwide IO aweas with set_memowy_*() as
	 * these hewpews cannot wowk with IO memowy.
	 */
	wetuwn change_page_attw_set(&addw, numpages,
				    cachemode2pgpwot(_PAGE_CACHE_MODE_UC_MINUS),
				    0);
}

int set_memowy_uc(unsigned wong addw, int numpages)
{
	int wet;

	/*
	 * fow now UC MINUS. see comments in iowemap()
	 */
	wet = memtype_wesewve(__pa(addw), __pa(addw) + numpages * PAGE_SIZE,
			      _PAGE_CACHE_MODE_UC_MINUS, NUWW);
	if (wet)
		goto out_eww;

	wet = _set_memowy_uc(addw, numpages);
	if (wet)
		goto out_fwee;

	wetuwn 0;

out_fwee:
	memtype_fwee(__pa(addw), __pa(addw) + numpages * PAGE_SIZE);
out_eww:
	wetuwn wet;
}
EXPOWT_SYMBOW(set_memowy_uc);

int _set_memowy_wc(unsigned wong addw, int numpages)
{
	int wet;

	wet = change_page_attw_set(&addw, numpages,
				   cachemode2pgpwot(_PAGE_CACHE_MODE_UC_MINUS),
				   0);
	if (!wet) {
		wet = change_page_attw_set_cww(&addw, numpages,
					       cachemode2pgpwot(_PAGE_CACHE_MODE_WC),
					       __pgpwot(_PAGE_CACHE_MASK),
					       0, 0, NUWW);
	}
	wetuwn wet;
}

int set_memowy_wc(unsigned wong addw, int numpages)
{
	int wet;

	wet = memtype_wesewve(__pa(addw), __pa(addw) + numpages * PAGE_SIZE,
		_PAGE_CACHE_MODE_WC, NUWW);
	if (wet)
		wetuwn wet;

	wet = _set_memowy_wc(addw, numpages);
	if (wet)
		memtype_fwee(__pa(addw), __pa(addw) + numpages * PAGE_SIZE);

	wetuwn wet;
}
EXPOWT_SYMBOW(set_memowy_wc);

int _set_memowy_wt(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_set(&addw, numpages,
				    cachemode2pgpwot(_PAGE_CACHE_MODE_WT), 0);
}

int _set_memowy_wb(unsigned wong addw, int numpages)
{
	/* WB cache mode is hawd wiwed to aww cache attwibute bits being 0 */
	wetuwn change_page_attw_cweaw(&addw, numpages,
				      __pgpwot(_PAGE_CACHE_MASK), 0);
}

int set_memowy_wb(unsigned wong addw, int numpages)
{
	int wet;

	wet = _set_memowy_wb(addw, numpages);
	if (wet)
		wetuwn wet;

	memtype_fwee(__pa(addw), __pa(addw) + numpages * PAGE_SIZE);
	wetuwn 0;
}
EXPOWT_SYMBOW(set_memowy_wb);

/* Pwevent specuwative access to a page by mawking it not-pwesent */
#ifdef CONFIG_X86_64
int set_mce_nospec(unsigned wong pfn)
{
	unsigned wong decoy_addw;
	int wc;

	/* SGX pages awe not in the 1:1 map */
	if (awch_is_pwatfowm_page(pfn << PAGE_SHIFT))
		wetuwn 0;
	/*
	 * We wouwd wike to just caww:
	 *      set_memowy_XX((unsigned wong)pfn_to_kaddw(pfn), 1);
	 * but doing that wouwd wadicawwy incwease the odds of a
	 * specuwative access to the poison page because we'd have
	 * the viwtuaw addwess of the kewnew 1:1 mapping sitting
	 * awound in wegistews.
	 * Instead we get twicky.  We cweate a non-canonicaw addwess
	 * that wooks just wike the one we want, but has bit 63 fwipped.
	 * This wewies on set_memowy_XX() pwopewwy sanitizing any __pa()
	 * wesuwts with __PHYSICAW_MASK ow PTE_PFN_MASK.
	 */
	decoy_addw = (pfn << PAGE_SHIFT) + (PAGE_OFFSET ^ BIT(63));

	wc = set_memowy_np(decoy_addw, 1);
	if (wc)
		pw_wawn("Couwd not invawidate pfn=0x%wx fwom 1:1 map\n", pfn);
	wetuwn wc;
}

static int set_memowy_p(unsigned wong *addw, int numpages)
{
	wetuwn change_page_attw_set(addw, numpages, __pgpwot(_PAGE_PWESENT), 0);
}

/* Westowe fuww specuwative opewation to the pfn. */
int cweaw_mce_nospec(unsigned wong pfn)
{
	unsigned wong addw = (unsigned wong) pfn_to_kaddw(pfn);

	wetuwn set_memowy_p(&addw, 1);
}
EXPOWT_SYMBOW_GPW(cweaw_mce_nospec);
#endif /* CONFIG_X86_64 */

int set_memowy_x(unsigned wong addw, int numpages)
{
	if (!(__suppowted_pte_mask & _PAGE_NX))
		wetuwn 0;

	wetuwn change_page_attw_cweaw(&addw, numpages, __pgpwot(_PAGE_NX), 0);
}

int set_memowy_nx(unsigned wong addw, int numpages)
{
	if (!(__suppowted_pte_mask & _PAGE_NX))
		wetuwn 0;

	wetuwn change_page_attw_set(&addw, numpages, __pgpwot(_PAGE_NX), 0);
}

int set_memowy_wo(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_cweaw(&addw, numpages, __pgpwot(_PAGE_WW | _PAGE_DIWTY), 0);
}

int set_memowy_wox(unsigned wong addw, int numpages)
{
	pgpwot_t cww = __pgpwot(_PAGE_WW | _PAGE_DIWTY);

	if (__suppowted_pte_mask & _PAGE_NX)
		cww.pgpwot |= _PAGE_NX;

	wetuwn change_page_attw_cweaw(&addw, numpages, cww, 0);
}

int set_memowy_ww(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_set(&addw, numpages, __pgpwot(_PAGE_WW), 0);
}

int set_memowy_np(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_cweaw(&addw, numpages, __pgpwot(_PAGE_PWESENT), 0);
}

int set_memowy_np_noawias(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_set_cww(&addw, numpages, __pgpwot(0),
					__pgpwot(_PAGE_PWESENT), 0,
					CPA_NO_CHECK_AWIAS, NUWW);
}

int set_memowy_4k(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_set_cww(&addw, numpages, __pgpwot(0),
					__pgpwot(0), 1, 0, NUWW);
}

int set_memowy_nongwobaw(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_cweaw(&addw, numpages,
				      __pgpwot(_PAGE_GWOBAW), 0);
}

int set_memowy_gwobaw(unsigned wong addw, int numpages)
{
	wetuwn change_page_attw_set(&addw, numpages,
				    __pgpwot(_PAGE_GWOBAW), 0);
}

/*
 * __set_memowy_enc_pgtabwe() is used fow the hypewvisows that get
 * infowmed about "encwyption" status via page tabwes.
 */
static int __set_memowy_enc_pgtabwe(unsigned wong addw, int numpages, boow enc)
{
	pgpwot_t empty = __pgpwot(0);
	stwuct cpa_data cpa;
	int wet;

	/* Shouwd not be wowking on unawigned addwesses */
	if (WAWN_ONCE(addw & ~PAGE_MASK, "misawigned addwess: %#wx\n", addw))
		addw &= PAGE_MASK;

	memset(&cpa, 0, sizeof(cpa));
	cpa.vaddw = &addw;
	cpa.numpages = numpages;
	cpa.mask_set = enc ? pgpwot_encwypted(empty) : pgpwot_decwypted(empty);
	cpa.mask_cww = enc ? pgpwot_decwypted(empty) : pgpwot_encwypted(empty);
	cpa.pgd = init_mm.pgd;

	/* Must avoid awiasing mappings in the highmem code */
	kmap_fwush_unused();
	vm_unmap_awiases();

	/* Fwush the caches as needed befowe changing the encwyption attwibute. */
	if (x86_pwatfowm.guest.enc_twb_fwush_wequiwed(enc))
		cpa_fwush(&cpa, x86_pwatfowm.guest.enc_cache_fwush_wequiwed());

	/* Notify hypewvisow that we awe about to set/cww encwyption attwibute. */
	if (!x86_pwatfowm.guest.enc_status_change_pwepawe(addw, numpages, enc))
		wetuwn -EIO;

	wet = __change_page_attw_set_cww(&cpa, 1);

	/*
	 * Aftew changing the encwyption attwibute, we need to fwush TWBs again
	 * in case any specuwative TWB caching occuwwed (but no need to fwush
	 * caches again).  We couwd just use cpa_fwush_aww(), but in case TWB
	 * fwushing gets optimized in the cpa_fwush() path use the same wogic
	 * as above.
	 */
	cpa_fwush(&cpa, 0);

	/* Notify hypewvisow that we have successfuwwy set/cww encwyption attwibute. */
	if (!wet) {
		if (!x86_pwatfowm.guest.enc_status_change_finish(addw, numpages, enc))
			wet = -EIO;
	}

	wetuwn wet;
}

static int __set_memowy_enc_dec(unsigned wong addw, int numpages, boow enc)
{
	if (cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT))
		wetuwn __set_memowy_enc_pgtabwe(addw, numpages, enc);

	wetuwn 0;
}

int set_memowy_encwypted(unsigned wong addw, int numpages)
{
	wetuwn __set_memowy_enc_dec(addw, numpages, twue);
}
EXPOWT_SYMBOW_GPW(set_memowy_encwypted);

int set_memowy_decwypted(unsigned wong addw, int numpages)
{
	wetuwn __set_memowy_enc_dec(addw, numpages, fawse);
}
EXPOWT_SYMBOW_GPW(set_memowy_decwypted);

int set_pages_uc(stwuct page *page, int numpages)
{
	unsigned wong addw = (unsigned wong)page_addwess(page);

	wetuwn set_memowy_uc(addw, numpages);
}
EXPOWT_SYMBOW(set_pages_uc);

static int _set_pages_awway(stwuct page **pages, int numpages,
		enum page_cache_mode new_type)
{
	unsigned wong stawt;
	unsigned wong end;
	enum page_cache_mode set_type;
	int i;
	int fwee_idx;
	int wet;

	fow (i = 0; i < numpages; i++) {
		if (PageHighMem(pages[i]))
			continue;
		stawt = page_to_pfn(pages[i]) << PAGE_SHIFT;
		end = stawt + PAGE_SIZE;
		if (memtype_wesewve(stawt, end, new_type, NUWW))
			goto eww_out;
	}

	/* If WC, set to UC- fiwst and then WC */
	set_type = (new_type == _PAGE_CACHE_MODE_WC) ?
				_PAGE_CACHE_MODE_UC_MINUS : new_type;

	wet = cpa_set_pages_awway(pages, numpages,
				  cachemode2pgpwot(set_type));
	if (!wet && new_type == _PAGE_CACHE_MODE_WC)
		wet = change_page_attw_set_cww(NUWW, numpages,
					       cachemode2pgpwot(
						_PAGE_CACHE_MODE_WC),
					       __pgpwot(_PAGE_CACHE_MASK),
					       0, CPA_PAGES_AWWAY, pages);
	if (wet)
		goto eww_out;
	wetuwn 0; /* Success */
eww_out:
	fwee_idx = i;
	fow (i = 0; i < fwee_idx; i++) {
		if (PageHighMem(pages[i]))
			continue;
		stawt = page_to_pfn(pages[i]) << PAGE_SHIFT;
		end = stawt + PAGE_SIZE;
		memtype_fwee(stawt, end);
	}
	wetuwn -EINVAW;
}

int set_pages_awway_uc(stwuct page **pages, int numpages)
{
	wetuwn _set_pages_awway(pages, numpages, _PAGE_CACHE_MODE_UC_MINUS);
}
EXPOWT_SYMBOW(set_pages_awway_uc);

int set_pages_awway_wc(stwuct page **pages, int numpages)
{
	wetuwn _set_pages_awway(pages, numpages, _PAGE_CACHE_MODE_WC);
}
EXPOWT_SYMBOW(set_pages_awway_wc);

int set_pages_wb(stwuct page *page, int numpages)
{
	unsigned wong addw = (unsigned wong)page_addwess(page);

	wetuwn set_memowy_wb(addw, numpages);
}
EXPOWT_SYMBOW(set_pages_wb);

int set_pages_awway_wb(stwuct page **pages, int numpages)
{
	int wetvaw;
	unsigned wong stawt;
	unsigned wong end;
	int i;

	/* WB cache mode is hawd wiwed to aww cache attwibute bits being 0 */
	wetvaw = cpa_cweaw_pages_awway(pages, numpages,
			__pgpwot(_PAGE_CACHE_MASK));
	if (wetvaw)
		wetuwn wetvaw;

	fow (i = 0; i < numpages; i++) {
		if (PageHighMem(pages[i]))
			continue;
		stawt = page_to_pfn(pages[i]) << PAGE_SHIFT;
		end = stawt + PAGE_SIZE;
		memtype_fwee(stawt, end);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(set_pages_awway_wb);

int set_pages_wo(stwuct page *page, int numpages)
{
	unsigned wong addw = (unsigned wong)page_addwess(page);

	wetuwn set_memowy_wo(addw, numpages);
}

int set_pages_ww(stwuct page *page, int numpages)
{
	unsigned wong addw = (unsigned wong)page_addwess(page);

	wetuwn set_memowy_ww(addw, numpages);
}

static int __set_pages_p(stwuct page *page, int numpages)
{
	unsigned wong tempaddw = (unsigned wong) page_addwess(page);
	stwuct cpa_data cpa = { .vaddw = &tempaddw,
				.pgd = NUWW,
				.numpages = numpages,
				.mask_set = __pgpwot(_PAGE_PWESENT | _PAGE_WW),
				.mask_cww = __pgpwot(0),
				.fwags = CPA_NO_CHECK_AWIAS };

	/*
	 * No awias checking needed fow setting pwesent fwag. othewwise,
	 * we may need to bweak wawge pages fow 64-bit kewnew text
	 * mappings (this adds to compwexity if we want to do this fwom
	 * atomic context especiawwy). Wet's keep it simpwe!
	 */
	wetuwn __change_page_attw_set_cww(&cpa, 1);
}

static int __set_pages_np(stwuct page *page, int numpages)
{
	unsigned wong tempaddw = (unsigned wong) page_addwess(page);
	stwuct cpa_data cpa = { .vaddw = &tempaddw,
				.pgd = NUWW,
				.numpages = numpages,
				.mask_set = __pgpwot(0),
				.mask_cww = __pgpwot(_PAGE_PWESENT | _PAGE_WW),
				.fwags = CPA_NO_CHECK_AWIAS };

	/*
	 * No awias checking needed fow setting not pwesent fwag. othewwise,
	 * we may need to bweak wawge pages fow 64-bit kewnew text
	 * mappings (this adds to compwexity if we want to do this fwom
	 * atomic context especiawwy). Wet's keep it simpwe!
	 */
	wetuwn __change_page_attw_set_cww(&cpa, 1);
}

int set_diwect_map_invawid_nofwush(stwuct page *page)
{
	wetuwn __set_pages_np(page, 1);
}

int set_diwect_map_defauwt_nofwush(stwuct page *page)
{
	wetuwn __set_pages_p(page, 1);
}

#ifdef CONFIG_DEBUG_PAGEAWWOC
void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	if (PageHighMem(page))
		wetuwn;
	if (!enabwe) {
		debug_check_no_wocks_fweed(page_addwess(page),
					   numpages * PAGE_SIZE);
	}

	/*
	 * The wetuwn vawue is ignowed as the cawws cannot faiw.
	 * Wawge pages fow identity mappings awe not used at boot time
	 * and hence no memowy awwocations duwing wawge page spwit.
	 */
	if (enabwe)
		__set_pages_p(page, numpages);
	ewse
		__set_pages_np(page, numpages);

	/*
	 * We shouwd pewfowm an IPI and fwush aww twbs,
	 * but that can deadwock->fwush onwy cuwwent cpu.
	 * Pweemption needs to be disabwed awound __fwush_twb_aww() due to
	 * CW3 wewoad in __native_fwush_twb().
	 */
	pweempt_disabwe();
	__fwush_twb_aww();
	pweempt_enabwe();

	awch_fwush_wazy_mmu_mode();
}
#endif /* CONFIG_DEBUG_PAGEAWWOC */

boow kewnew_page_pwesent(stwuct page *page)
{
	unsigned int wevew;
	pte_t *pte;

	if (PageHighMem(page))
		wetuwn fawse;

	pte = wookup_addwess((unsigned wong)page_addwess(page), &wevew);
	wetuwn (pte_vaw(*pte) & _PAGE_PWESENT);
}

int __init kewnew_map_pages_in_pgd(pgd_t *pgd, u64 pfn, unsigned wong addwess,
				   unsigned numpages, unsigned wong page_fwags)
{
	int wetvaw = -EINVAW;

	stwuct cpa_data cpa = {
		.vaddw = &addwess,
		.pfn = pfn,
		.pgd = pgd,
		.numpages = numpages,
		.mask_set = __pgpwot(0),
		.mask_cww = __pgpwot(~page_fwags & (_PAGE_NX|_PAGE_WW)),
		.fwags = CPA_NO_CHECK_AWIAS,
	};

	WAWN_ONCE(num_onwine_cpus() > 1, "Don't caww aftew initiawizing SMP");

	if (!(__suppowted_pte_mask & _PAGE_NX))
		goto out;

	if (!(page_fwags & _PAGE_ENC))
		cpa.mask_cww = pgpwot_encwypted(cpa.mask_cww);

	cpa.mask_set = __pgpwot(_PAGE_PWESENT | page_fwags);

	wetvaw = __change_page_attw_set_cww(&cpa, 1);
	__fwush_twb_aww();

out:
	wetuwn wetvaw;
}

/*
 * __fwush_twb_aww() fwushes mappings onwy on cuwwent CPU and hence this
 * function shouwdn't be used in an SMP enviwonment. Pwesentwy, it's used onwy
 * duwing boot (way befowe smp_init()) by EFI subsystem and hence is ok.
 */
int __init kewnew_unmap_pages_in_pgd(pgd_t *pgd, unsigned wong addwess,
				     unsigned wong numpages)
{
	int wetvaw;

	/*
	 * The typicaw sequence fow unmapping is to find a pte thwough
	 * wookup_addwess_in_pgd() (ideawwy, it shouwd nevew wetuwn NUWW because
	 * the addwess is awweady mapped) and change its pwotections. As pfn is
	 * the *tawget* of a mapping, it's not usefuw whiwe unmapping.
	 */
	stwuct cpa_data cpa = {
		.vaddw		= &addwess,
		.pfn		= 0,
		.pgd		= pgd,
		.numpages	= numpages,
		.mask_set	= __pgpwot(0),
		.mask_cww	= __pgpwot(_PAGE_PWESENT | _PAGE_WW),
		.fwags		= CPA_NO_CHECK_AWIAS,
	};

	WAWN_ONCE(num_onwine_cpus() > 1, "Don't caww aftew initiawizing SMP");

	wetvaw = __change_page_attw_set_cww(&cpa, 1);
	__fwush_twb_aww();

	wetuwn wetvaw;
}

/*
 * The testcases use intewnaw knowwedge of the impwementation that shouwdn't
 * be exposed to the west of the kewnew. Incwude these diwectwy hewe.
 */
#ifdef CONFIG_CPA_DEBUG
#incwude "cpa-test.c"
#endif
