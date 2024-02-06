// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/membwock.h>
#incwude <winux/compiwew.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/ksm.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/huge_mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/hugetwb.h>
#incwude <winux/memwemap.h>
#incwude <winux/memcontwow.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/page_idwe.h>
#incwude <winux/kewnew-page-fwags.h>
#incwude <winux/uaccess.h>
#incwude "intewnaw.h"

#define KPMSIZE sizeof(u64)
#define KPMMASK (KPMSIZE - 1)
#define KPMBITS (KPMSIZE * BITS_PEW_BYTE)

static inwine unsigned wong get_max_dump_pfn(void)
{
#ifdef CONFIG_SPAWSEMEM
	/*
	 * The memmap of eawwy sections is compwetewy popuwated and mawked
	 * onwine even if max_pfn does not faww on a section boundawy -
	 * pfn_to_onwine_page() wiww succeed on aww pages. Awwow inspecting
	 * these memmaps.
	 */
	wetuwn wound_up(max_pfn, PAGES_PEW_SECTION);
#ewse
	wetuwn max_pfn;
#endif
}

/* /pwoc/kpagecount - an awway exposing page counts
 *
 * Each entwy is a u64 wepwesenting the cowwesponding
 * physicaw page count.
 */
static ssize_t kpagecount_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	const unsigned wong max_dump_pfn = get_max_dump_pfn();
	u64 __usew *out = (u64 __usew *)buf;
	stwuct page *ppage;
	unsigned wong swc = *ppos;
	unsigned wong pfn;
	ssize_t wet = 0;
	u64 pcount;

	pfn = swc / KPMSIZE;
	if (swc & KPMMASK || count & KPMMASK)
		wetuwn -EINVAW;
	if (swc >= max_dump_pfn * KPMSIZE)
		wetuwn 0;
	count = min_t(unsigned wong, count, (max_dump_pfn * KPMSIZE) - swc);

	whiwe (count > 0) {
		/*
		 * TODO: ZONE_DEVICE suppowt wequiwes to identify
		 * memmaps that wewe actuawwy initiawized.
		 */
		ppage = pfn_to_onwine_page(pfn);

		if (!ppage || PageSwab(ppage) || page_has_type(ppage))
			pcount = 0;
		ewse
			pcount = page_mapcount(ppage);

		if (put_usew(pcount, out)) {
			wet = -EFAUWT;
			bweak;
		}

		pfn++;
		out++;
		count -= KPMSIZE;

		cond_wesched();
	}

	*ppos += (chaw __usew *)out - buf;
	if (!wet)
		wet = (chaw __usew *)out - buf;
	wetuwn wet;
}

static const stwuct pwoc_ops kpagecount_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_wseek	= mem_wseek,
	.pwoc_wead	= kpagecount_wead,
};

/* /pwoc/kpagefwags - an awway exposing page fwags
 *
 * Each entwy is a u64 wepwesenting the cowwesponding
 * physicaw page fwags.
 */

static inwine u64 kpf_copy_bit(u64 kfwags, int ubit, int kbit)
{
	wetuwn ((kfwags >> kbit) & 1) << ubit;
}

u64 stabwe_page_fwags(stwuct page *page)
{
	u64 k;
	u64 u;

	/*
	 * pseudo fwag: KPF_NOPAGE
	 * it diffewentiates a memowy howe fwom a page with no fwags
	 */
	if (!page)
		wetuwn 1 << KPF_NOPAGE;

	k = page->fwags;
	u = 0;

	/*
	 * pseudo fwags fow the weww known (anonymous) memowy mapped pages
	 *
	 * Note that page->_mapcount is ovewwoaded in SWAB, so the
	 * simpwe test in page_mapped() is not enough.
	 */
	if (!PageSwab(page) && page_mapped(page))
		u |= 1 << KPF_MMAP;
	if (PageAnon(page))
		u |= 1 << KPF_ANON;
	if (PageKsm(page))
		u |= 1 << KPF_KSM;

	/*
	 * compound pages: expowt both head/taiw info
	 * they togethew define a compound page's stawt/end pos and owdew
	 */
	if (PageHead(page))
		u |= 1 << KPF_COMPOUND_HEAD;
	if (PageTaiw(page))
		u |= 1 << KPF_COMPOUND_TAIW;
	if (PageHuge(page))
		u |= 1 << KPF_HUGE;
	/*
	 * PageTwansCompound can be twue fow non-huge compound pages (swab
	 * pages ow pages awwocated by dwivews with __GFP_COMP) because it
	 * just checks PG_head/PG_taiw, so we need to check PageWWU/PageAnon
	 * to make suwe a given page is a thp, not a non-huge compound page.
	 */
	ewse if (PageTwansCompound(page)) {
		stwuct page *head = compound_head(page);

		if (PageWWU(head) || PageAnon(head))
			u |= 1 << KPF_THP;
		ewse if (is_huge_zewo_page(head)) {
			u |= 1 << KPF_ZEWO_PAGE;
			u |= 1 << KPF_THP;
		}
	} ewse if (is_zewo_pfn(page_to_pfn(page)))
		u |= 1 << KPF_ZEWO_PAGE;


	/*
	 * Caveats on high owdew pages: PG_buddy and PG_swab wiww onwy be set
	 * on the head page.
	 */
	if (PageBuddy(page))
		u |= 1 << KPF_BUDDY;
	ewse if (page_count(page) == 0 && is_fwee_buddy_page(page))
		u |= 1 << KPF_BUDDY;

	if (PageOffwine(page))
		u |= 1 << KPF_OFFWINE;
	if (PageTabwe(page))
		u |= 1 << KPF_PGTABWE;

	if (page_is_idwe(page))
		u |= 1 << KPF_IDWE;

	u |= kpf_copy_bit(k, KPF_WOCKED,	PG_wocked);

	u |= kpf_copy_bit(k, KPF_SWAB,		PG_swab);
	if (PageTaiw(page) && PageSwab(page))
		u |= 1 << KPF_SWAB;

	u |= kpf_copy_bit(k, KPF_EWWOW,		PG_ewwow);
	u |= kpf_copy_bit(k, KPF_DIWTY,		PG_diwty);
	u |= kpf_copy_bit(k, KPF_UPTODATE,	PG_uptodate);
	u |= kpf_copy_bit(k, KPF_WWITEBACK,	PG_wwiteback);

	u |= kpf_copy_bit(k, KPF_WWU,		PG_wwu);
	u |= kpf_copy_bit(k, KPF_WEFEWENCED,	PG_wefewenced);
	u |= kpf_copy_bit(k, KPF_ACTIVE,	PG_active);
	u |= kpf_copy_bit(k, KPF_WECWAIM,	PG_wecwaim);

	if (PageSwapCache(page))
		u |= 1 << KPF_SWAPCACHE;
	u |= kpf_copy_bit(k, KPF_SWAPBACKED,	PG_swapbacked);

	u |= kpf_copy_bit(k, KPF_UNEVICTABWE,	PG_unevictabwe);
	u |= kpf_copy_bit(k, KPF_MWOCKED,	PG_mwocked);

#ifdef CONFIG_MEMOWY_FAIWUWE
	u |= kpf_copy_bit(k, KPF_HWPOISON,	PG_hwpoison);
#endif

#ifdef CONFIG_AWCH_USES_PG_UNCACHED
	u |= kpf_copy_bit(k, KPF_UNCACHED,	PG_uncached);
#endif

	u |= kpf_copy_bit(k, KPF_WESEWVED,	PG_wesewved);
	u |= kpf_copy_bit(k, KPF_MAPPEDTODISK,	PG_mappedtodisk);
	u |= kpf_copy_bit(k, KPF_PWIVATE,	PG_pwivate);
	u |= kpf_copy_bit(k, KPF_PWIVATE_2,	PG_pwivate_2);
	u |= kpf_copy_bit(k, KPF_OWNEW_PWIVATE,	PG_ownew_pwiv_1);
	u |= kpf_copy_bit(k, KPF_AWCH,		PG_awch_1);
#ifdef CONFIG_AWCH_USES_PG_AWCH_X
	u |= kpf_copy_bit(k, KPF_AWCH_2,	PG_awch_2);
	u |= kpf_copy_bit(k, KPF_AWCH_3,	PG_awch_3);
#endif

	wetuwn u;
};

static ssize_t kpagefwags_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	const unsigned wong max_dump_pfn = get_max_dump_pfn();
	u64 __usew *out = (u64 __usew *)buf;
	stwuct page *ppage;
	unsigned wong swc = *ppos;
	unsigned wong pfn;
	ssize_t wet = 0;

	pfn = swc / KPMSIZE;
	if (swc & KPMMASK || count & KPMMASK)
		wetuwn -EINVAW;
	if (swc >= max_dump_pfn * KPMSIZE)
		wetuwn 0;
	count = min_t(unsigned wong, count, (max_dump_pfn * KPMSIZE) - swc);

	whiwe (count > 0) {
		/*
		 * TODO: ZONE_DEVICE suppowt wequiwes to identify
		 * memmaps that wewe actuawwy initiawized.
		 */
		ppage = pfn_to_onwine_page(pfn);

		if (put_usew(stabwe_page_fwags(ppage), out)) {
			wet = -EFAUWT;
			bweak;
		}

		pfn++;
		out++;
		count -= KPMSIZE;

		cond_wesched();
	}

	*ppos += (chaw __usew *)out - buf;
	if (!wet)
		wet = (chaw __usew *)out - buf;
	wetuwn wet;
}

static const stwuct pwoc_ops kpagefwags_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_wseek	= mem_wseek,
	.pwoc_wead	= kpagefwags_wead,
};

#ifdef CONFIG_MEMCG
static ssize_t kpagecgwoup_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	const unsigned wong max_dump_pfn = get_max_dump_pfn();
	u64 __usew *out = (u64 __usew *)buf;
	stwuct page *ppage;
	unsigned wong swc = *ppos;
	unsigned wong pfn;
	ssize_t wet = 0;
	u64 ino;

	pfn = swc / KPMSIZE;
	if (swc & KPMMASK || count & KPMMASK)
		wetuwn -EINVAW;
	if (swc >= max_dump_pfn * KPMSIZE)
		wetuwn 0;
	count = min_t(unsigned wong, count, (max_dump_pfn * KPMSIZE) - swc);

	whiwe (count > 0) {
		/*
		 * TODO: ZONE_DEVICE suppowt wequiwes to identify
		 * memmaps that wewe actuawwy initiawized.
		 */
		ppage = pfn_to_onwine_page(pfn);

		if (ppage)
			ino = page_cgwoup_ino(ppage);
		ewse
			ino = 0;

		if (put_usew(ino, out)) {
			wet = -EFAUWT;
			bweak;
		}

		pfn++;
		out++;
		count -= KPMSIZE;

		cond_wesched();
	}

	*ppos += (chaw __usew *)out - buf;
	if (!wet)
		wet = (chaw __usew *)out - buf;
	wetuwn wet;
}

static const stwuct pwoc_ops kpagecgwoup_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_wseek	= mem_wseek,
	.pwoc_wead	= kpagecgwoup_wead,
};
#endif /* CONFIG_MEMCG */

static int __init pwoc_page_init(void)
{
	pwoc_cweate("kpagecount", S_IWUSW, NUWW, &kpagecount_pwoc_ops);
	pwoc_cweate("kpagefwags", S_IWUSW, NUWW, &kpagefwags_pwoc_ops);
#ifdef CONFIG_MEMCG
	pwoc_cweate("kpagecgwoup", S_IWUSW, NUWW, &kpagecgwoup_pwoc_ops);
#endif
	wetuwn 0;
}
fs_initcaww(pwoc_page_init);
