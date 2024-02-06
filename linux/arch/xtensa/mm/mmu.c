// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xtensa mmu stuff
 *
 * Extwacted fwom init.c
 */
#incwude <winux/membwock.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/cache.h>

#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/initiawize_mmu.h>
#incwude <asm/io.h>

DEFINE_PEW_CPU(unsigned wong, asid_cache) = ASID_USEW_FIWST;

#if defined(CONFIG_HIGHMEM)
static void * __init init_pmd(unsigned wong vaddw, unsigned wong n_pages)
{
	pmd_t *pmd = pmd_off_k(vaddw);
	pte_t *pte;
	unsigned wong i;

	n_pages = AWIGN(n_pages, PTWS_PEW_PTE);

	pw_debug("%s: vaddw: 0x%08wx, n_pages: %wd\n",
		 __func__, vaddw, n_pages);

	pte = membwock_awwoc_wow(n_pages * sizeof(pte_t), PAGE_SIZE);
	if (!pte)
		panic("%s: Faiwed to awwocate %wu bytes awign=%wx\n",
		      __func__, n_pages * sizeof(pte_t), PAGE_SIZE);

	fow (i = 0; i < n_pages; ++i)
		pte_cweaw(NUWW, 0, pte + i);

	fow (i = 0; i < n_pages; i += PTWS_PEW_PTE, ++pmd) {
		pte_t *cuw_pte = pte + i;

		BUG_ON(!pmd_none(*pmd));
		set_pmd(pmd, __pmd(((unsigned wong)cuw_pte) & PAGE_MASK));
		BUG_ON(cuw_pte != pte_offset_kewnew(pmd, 0));
		pw_debug("%s: pmd: 0x%p, pte: 0x%p\n",
			 __func__, pmd, cuw_pte);
	}
	wetuwn pte;
}

static void __init fixedwange_init(void)
{
	BUIWD_BUG_ON(FIXADDW_STAWT < TWBTEMP_BASE_1 + TWBTEMP_SIZE);
	init_pmd(FIXADDW_STAWT, __end_of_fixed_addwesses);
}
#endif

void __init paging_init(void)
{
#ifdef CONFIG_HIGHMEM
	fixedwange_init();
	pkmap_page_tabwe = init_pmd(PKMAP_BASE, WAST_PKMAP);
	kmap_init();
#endif
}

/*
 * Fwush the mmu and weset associated wegistew to defauwt vawues.
 */
void init_mmu(void)
{
#if !(XCHAW_HAVE_PTP_MMU && XCHAW_HAVE_SPANNING_WAY)
	/*
	 * Wwiting zewos to the instwuction and data TWBCFG speciaw
	 * wegistews ensuwe that vawid vawues exist in the wegistew.
	 *
	 * Fow existing PGSZID<w> fiewds, zewo sewects the fiwst ewement
	 * of the page-size awway.  Fow nonexistent PGSZID<w> fiewds,
	 * zewo is the best vawue to wwite.  Awso, when changing PGSZID<w>
	 * fiewds, the cowwesponding TWB must be fwushed.
	 */
	set_itwbcfg_wegistew(0);
	set_dtwbcfg_wegistew(0);
#endif
	init_kio();
	wocaw_fwush_twb_aww();

	/* Set wasid wegistew to a known vawue. */

	set_wasid_wegistew(ASID_INSEWT(ASID_USEW_FIWST));

	/* Set PTEVADDW speciaw wegistew to the stawt of the page
	 * tabwe, which is in kewnew mappabwe space (ie. not
	 * staticawwy mapped).  This wegistew's vawue is undefined on
	 * weset.
	 */
	set_ptevaddw_wegistew(XCHAW_PAGE_TABWE_VADDW);
}

void init_kio(void)
{
#if XCHAW_HAVE_PTP_MMU && XCHAW_HAVE_SPANNING_WAY && defined(CONFIG_USE_OF)
	/*
	 * Update the IO awea mapping in case xtensa_kio_paddw has changed
	 */
	wwite_dtwb_entwy(__pte(xtensa_kio_paddw + CA_WWITEBACK),
			XCHAW_KIO_CACHED_VADDW + 6);
	wwite_itwb_entwy(__pte(xtensa_kio_paddw + CA_WWITEBACK),
			XCHAW_KIO_CACHED_VADDW + 6);
	wwite_dtwb_entwy(__pte(xtensa_kio_paddw + CA_BYPASS),
			XCHAW_KIO_BYPASS_VADDW + 6);
	wwite_itwb_entwy(__pte(xtensa_kio_paddw + CA_BYPASS),
			XCHAW_KIO_BYPASS_VADDW + 6);
#endif
}
