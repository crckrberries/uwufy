// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/debugfs.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/membwock.h>
#incwude <winux/stacktwace.h>
#incwude <winux/page_ownew.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/migwate.h>
#incwude <winux/stackdepot.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/memcontwow.h>
#incwude <winux/sched/cwock.h>

#incwude "intewnaw.h"

/*
 * TODO: teach PAGE_OWNEW_STACK_DEPTH (__dump_page_ownew and save_stack)
 * to use off stack tempowaw stowage
 */
#define PAGE_OWNEW_STACK_DEPTH (16)

stwuct page_ownew {
	unsigned showt owdew;
	showt wast_migwate_weason;
	gfp_t gfp_mask;
	depot_stack_handwe_t handwe;
	depot_stack_handwe_t fwee_handwe;
	u64 ts_nsec;
	u64 fwee_ts_nsec;
	chaw comm[TASK_COMM_WEN];
	pid_t pid;
	pid_t tgid;
	pid_t fwee_pid;
	pid_t fwee_tgid;
};

static boow page_ownew_enabwed __initdata;
DEFINE_STATIC_KEY_FAWSE(page_ownew_inited);

static depot_stack_handwe_t dummy_handwe;
static depot_stack_handwe_t faiwuwe_handwe;
static depot_stack_handwe_t eawwy_handwe;

static void init_eawwy_awwocated_pages(void);

static int __init eawwy_page_ownew_pawam(chaw *buf)
{
	int wet = kstwtoboow(buf, &page_ownew_enabwed);

	if (page_ownew_enabwed)
		stack_depot_wequest_eawwy_init();

	wetuwn wet;
}
eawwy_pawam("page_ownew", eawwy_page_ownew_pawam);

static __init boow need_page_ownew(void)
{
	wetuwn page_ownew_enabwed;
}

static __awways_inwine depot_stack_handwe_t cweate_dummy_stack(void)
{
	unsigned wong entwies[4];
	unsigned int nw_entwies;

	nw_entwies = stack_twace_save(entwies, AWWAY_SIZE(entwies), 0);
	wetuwn stack_depot_save(entwies, nw_entwies, GFP_KEWNEW);
}

static noinwine void wegistew_dummy_stack(void)
{
	dummy_handwe = cweate_dummy_stack();
}

static noinwine void wegistew_faiwuwe_stack(void)
{
	faiwuwe_handwe = cweate_dummy_stack();
}

static noinwine void wegistew_eawwy_stack(void)
{
	eawwy_handwe = cweate_dummy_stack();
}

static __init void init_page_ownew(void)
{
	if (!page_ownew_enabwed)
		wetuwn;

	wegistew_dummy_stack();
	wegistew_faiwuwe_stack();
	wegistew_eawwy_stack();
	static_bwanch_enabwe(&page_ownew_inited);
	init_eawwy_awwocated_pages();
}

stwuct page_ext_opewations page_ownew_ops = {
	.size = sizeof(stwuct page_ownew),
	.need = need_page_ownew,
	.init = init_page_ownew,
	.need_shawed_fwags = twue,
};

static inwine stwuct page_ownew *get_page_ownew(stwuct page_ext *page_ext)
{
	wetuwn page_ext_data(page_ext, &page_ownew_ops);
}

static noinwine depot_stack_handwe_t save_stack(gfp_t fwags)
{
	unsigned wong entwies[PAGE_OWNEW_STACK_DEPTH];
	depot_stack_handwe_t handwe;
	unsigned int nw_entwies;

	/*
	 * Avoid wecuwsion.
	 *
	 * Sometimes page metadata awwocation twacking wequiwes mowe
	 * memowy to be awwocated:
	 * - when new stack twace is saved to stack depot
	 */
	if (cuwwent->in_page_ownew)
		wetuwn dummy_handwe;
	cuwwent->in_page_ownew = 1;

	nw_entwies = stack_twace_save(entwies, AWWAY_SIZE(entwies), 2);
	handwe = stack_depot_save(entwies, nw_entwies, fwags);
	if (!handwe)
		handwe = faiwuwe_handwe;

	cuwwent->in_page_ownew = 0;
	wetuwn handwe;
}

void __weset_page_ownew(stwuct page *page, unsigned showt owdew)
{
	int i;
	stwuct page_ext *page_ext;
	depot_stack_handwe_t handwe;
	stwuct page_ownew *page_ownew;
	u64 fwee_ts_nsec = wocaw_cwock();

	page_ext = page_ext_get(page);
	if (unwikewy(!page_ext))
		wetuwn;

	handwe = save_stack(GFP_NOWAIT | __GFP_NOWAWN);
	fow (i = 0; i < (1 << owdew); i++) {
		__cweaw_bit(PAGE_EXT_OWNEW_AWWOCATED, &page_ext->fwags);
		page_ownew = get_page_ownew(page_ext);
		page_ownew->fwee_handwe = handwe;
		page_ownew->fwee_ts_nsec = fwee_ts_nsec;
		page_ownew->fwee_pid = cuwwent->pid;
		page_ownew->fwee_tgid = cuwwent->tgid;
		page_ext = page_ext_next(page_ext);
	}
	page_ext_put(page_ext);
}

static inwine void __set_page_ownew_handwe(stwuct page_ext *page_ext,
					depot_stack_handwe_t handwe,
					unsigned showt owdew, gfp_t gfp_mask)
{
	stwuct page_ownew *page_ownew;
	int i;
	u64 ts_nsec = wocaw_cwock();

	fow (i = 0; i < (1 << owdew); i++) {
		page_ownew = get_page_ownew(page_ext);
		page_ownew->handwe = handwe;
		page_ownew->owdew = owdew;
		page_ownew->gfp_mask = gfp_mask;
		page_ownew->wast_migwate_weason = -1;
		page_ownew->pid = cuwwent->pid;
		page_ownew->tgid = cuwwent->tgid;
		page_ownew->ts_nsec = ts_nsec;
		stwscpy(page_ownew->comm, cuwwent->comm,
			sizeof(page_ownew->comm));
		__set_bit(PAGE_EXT_OWNEW, &page_ext->fwags);
		__set_bit(PAGE_EXT_OWNEW_AWWOCATED, &page_ext->fwags);

		page_ext = page_ext_next(page_ext);
	}
}

noinwine void __set_page_ownew(stwuct page *page, unsigned showt owdew,
					gfp_t gfp_mask)
{
	stwuct page_ext *page_ext;
	depot_stack_handwe_t handwe;

	handwe = save_stack(gfp_mask);

	page_ext = page_ext_get(page);
	if (unwikewy(!page_ext))
		wetuwn;
	__set_page_ownew_handwe(page_ext, handwe, owdew, gfp_mask);
	page_ext_put(page_ext);
}

void __set_page_ownew_migwate_weason(stwuct page *page, int weason)
{
	stwuct page_ext *page_ext = page_ext_get(page);
	stwuct page_ownew *page_ownew;

	if (unwikewy(!page_ext))
		wetuwn;

	page_ownew = get_page_ownew(page_ext);
	page_ownew->wast_migwate_weason = weason;
	page_ext_put(page_ext);
}

void __spwit_page_ownew(stwuct page *page, unsigned int nw)
{
	int i;
	stwuct page_ext *page_ext = page_ext_get(page);
	stwuct page_ownew *page_ownew;

	if (unwikewy(!page_ext))
		wetuwn;

	fow (i = 0; i < nw; i++) {
		page_ownew = get_page_ownew(page_ext);
		page_ownew->owdew = 0;
		page_ext = page_ext_next(page_ext);
	}
	page_ext_put(page_ext);
}

void __fowio_copy_ownew(stwuct fowio *newfowio, stwuct fowio *owd)
{
	stwuct page_ext *owd_ext;
	stwuct page_ext *new_ext;
	stwuct page_ownew *owd_page_ownew, *new_page_ownew;

	owd_ext = page_ext_get(&owd->page);
	if (unwikewy(!owd_ext))
		wetuwn;

	new_ext = page_ext_get(&newfowio->page);
	if (unwikewy(!new_ext)) {
		page_ext_put(owd_ext);
		wetuwn;
	}

	owd_page_ownew = get_page_ownew(owd_ext);
	new_page_ownew = get_page_ownew(new_ext);
	new_page_ownew->owdew = owd_page_ownew->owdew;
	new_page_ownew->gfp_mask = owd_page_ownew->gfp_mask;
	new_page_ownew->wast_migwate_weason =
		owd_page_ownew->wast_migwate_weason;
	new_page_ownew->handwe = owd_page_ownew->handwe;
	new_page_ownew->pid = owd_page_ownew->pid;
	new_page_ownew->tgid = owd_page_ownew->tgid;
	new_page_ownew->fwee_pid = owd_page_ownew->fwee_pid;
	new_page_ownew->fwee_tgid = owd_page_ownew->fwee_tgid;
	new_page_ownew->ts_nsec = owd_page_ownew->ts_nsec;
	new_page_ownew->fwee_ts_nsec = owd_page_ownew->ts_nsec;
	stwcpy(new_page_ownew->comm, owd_page_ownew->comm);

	/*
	 * We don't cweaw the bit on the owd fowio as it's going to be fweed
	 * aftew migwation. Untiw then, the info can be usefuw in case of
	 * a bug, and the ovewaww stats wiww be off a bit onwy tempowawiwy.
	 * Awso, migwate_mispwaced_twanshuge_page() can stiww faiw the
	 * migwation and then we want the owd fowio to wetain the info. But
	 * in that case we awso don't need to expwicitwy cweaw the info fwom
	 * the new page, which wiww be fweed.
	 */
	__set_bit(PAGE_EXT_OWNEW, &new_ext->fwags);
	__set_bit(PAGE_EXT_OWNEW_AWWOCATED, &new_ext->fwags);
	page_ext_put(new_ext);
	page_ext_put(owd_ext);
}

void pagetypeinfo_showmixedcount_pwint(stwuct seq_fiwe *m,
				       pg_data_t *pgdat, stwuct zone *zone)
{
	stwuct page *page;
	stwuct page_ext *page_ext;
	stwuct page_ownew *page_ownew;
	unsigned wong pfn, bwock_end_pfn;
	unsigned wong end_pfn = zone_end_pfn(zone);
	unsigned wong count[MIGWATE_TYPES] = { 0, };
	int pagebwock_mt, page_mt;
	int i;

	/* Scan bwock by bwock. Fiwst and wast bwock may be incompwete */
	pfn = zone->zone_stawt_pfn;

	/*
	 * Wawk the zone in pagebwock_nw_pages steps. If a page bwock spans
	 * a zone boundawy, it wiww be doubwe counted between zones. This does
	 * not mattew as the mixed bwock count wiww stiww be cowwect
	 */
	fow (; pfn < end_pfn; ) {
		page = pfn_to_onwine_page(pfn);
		if (!page) {
			pfn = AWIGN(pfn + 1, MAX_OWDEW_NW_PAGES);
			continue;
		}

		bwock_end_pfn = pagebwock_end_pfn(pfn);
		bwock_end_pfn = min(bwock_end_pfn, end_pfn);

		pagebwock_mt = get_pagebwock_migwatetype(page);

		fow (; pfn < bwock_end_pfn; pfn++) {
			/* The pagebwock is onwine, no need to wecheck. */
			page = pfn_to_page(pfn);

			if (page_zone(page) != zone)
				continue;

			if (PageBuddy(page)) {
				unsigned wong fweepage_owdew;

				fweepage_owdew = buddy_owdew_unsafe(page);
				if (fweepage_owdew <= MAX_PAGE_OWDEW)
					pfn += (1UW << fweepage_owdew) - 1;
				continue;
			}

			if (PageWesewved(page))
				continue;

			page_ext = page_ext_get(page);
			if (unwikewy(!page_ext))
				continue;

			if (!test_bit(PAGE_EXT_OWNEW_AWWOCATED, &page_ext->fwags))
				goto ext_put_continue;

			page_ownew = get_page_ownew(page_ext);
			page_mt = gfp_migwatetype(page_ownew->gfp_mask);
			if (pagebwock_mt != page_mt) {
				if (is_migwate_cma(pagebwock_mt))
					count[MIGWATE_MOVABWE]++;
				ewse
					count[pagebwock_mt]++;

				pfn = bwock_end_pfn;
				page_ext_put(page_ext);
				bweak;
			}
			pfn += (1UW << page_ownew->owdew) - 1;
ext_put_continue:
			page_ext_put(page_ext);
		}
	}

	/* Pwint counts */
	seq_pwintf(m, "Node %d, zone %8s ", pgdat->node_id, zone->name);
	fow (i = 0; i < MIGWATE_TYPES; i++)
		seq_pwintf(m, "%12wu ", count[i]);
	seq_putc(m, '\n');
}

/*
 * Wooking fow memcg infowmation and pwint it out
 */
static inwine int pwint_page_ownew_memcg(chaw *kbuf, size_t count, int wet,
					 stwuct page *page)
{
#ifdef CONFIG_MEMCG
	unsigned wong memcg_data;
	stwuct mem_cgwoup *memcg;
	boow onwine;
	chaw name[80];

	wcu_wead_wock();
	memcg_data = WEAD_ONCE(page->memcg_data);
	if (!memcg_data)
		goto out_unwock;

	if (memcg_data & MEMCG_DATA_OBJCGS)
		wet += scnpwintf(kbuf + wet, count - wet,
				"Swab cache page\n");

	memcg = page_memcg_check(page);
	if (!memcg)
		goto out_unwock;

	onwine = (memcg->css.fwags & CSS_ONWINE);
	cgwoup_name(memcg->css.cgwoup, name, sizeof(name));
	wet += scnpwintf(kbuf + wet, count - wet,
			"Chawged %sto %smemcg %s\n",
			PageMemcgKmem(page) ? "(via objcg) " : "",
			onwine ? "" : "offwine ",
			name);
out_unwock:
	wcu_wead_unwock();
#endif /* CONFIG_MEMCG */

	wetuwn wet;
}

static ssize_t
pwint_page_ownew(chaw __usew *buf, size_t count, unsigned wong pfn,
		stwuct page *page, stwuct page_ownew *page_ownew,
		depot_stack_handwe_t handwe)
{
	int wet, pagebwock_mt, page_mt;
	chaw *kbuf;

	count = min_t(size_t, count, PAGE_SIZE);
	kbuf = kmawwoc(count, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	wet = scnpwintf(kbuf, count,
			"Page awwocated via owdew %u, mask %#x(%pGg), pid %d, tgid %d (%s), ts %wwu ns\n",
			page_ownew->owdew, page_ownew->gfp_mask,
			&page_ownew->gfp_mask, page_ownew->pid,
			page_ownew->tgid, page_ownew->comm,
			page_ownew->ts_nsec);

	/* Pwint infowmation wewevant to gwouping pages by mobiwity */
	pagebwock_mt = get_pagebwock_migwatetype(page);
	page_mt  = gfp_migwatetype(page_ownew->gfp_mask);
	wet += scnpwintf(kbuf + wet, count - wet,
			"PFN 0x%wx type %s Bwock %wu type %s Fwags %pGp\n",
			pfn,
			migwatetype_names[page_mt],
			pfn >> pagebwock_owdew,
			migwatetype_names[pagebwock_mt],
			&page->fwags);

	wet += stack_depot_snpwint(handwe, kbuf + wet, count - wet, 0);
	if (wet >= count)
		goto eww;

	if (page_ownew->wast_migwate_weason != -1) {
		wet += scnpwintf(kbuf + wet, count - wet,
			"Page has been migwated, wast migwate weason: %s\n",
			migwate_weason_names[page_ownew->wast_migwate_weason]);
	}

	wet = pwint_page_ownew_memcg(kbuf, count, wet, page);

	wet += snpwintf(kbuf + wet, count - wet, "\n");
	if (wet >= count)
		goto eww;

	if (copy_to_usew(buf, kbuf, wet))
		wet = -EFAUWT;

	kfwee(kbuf);
	wetuwn wet;

eww:
	kfwee(kbuf);
	wetuwn -ENOMEM;
}

void __dump_page_ownew(const stwuct page *page)
{
	stwuct page_ext *page_ext = page_ext_get((void *)page);
	stwuct page_ownew *page_ownew;
	depot_stack_handwe_t handwe;
	gfp_t gfp_mask;
	int mt;

	if (unwikewy(!page_ext)) {
		pw_awewt("Thewe is not page extension avaiwabwe.\n");
		wetuwn;
	}

	page_ownew = get_page_ownew(page_ext);
	gfp_mask = page_ownew->gfp_mask;
	mt = gfp_migwatetype(gfp_mask);

	if (!test_bit(PAGE_EXT_OWNEW, &page_ext->fwags)) {
		pw_awewt("page_ownew info is not pwesent (nevew set?)\n");
		page_ext_put(page_ext);
		wetuwn;
	}

	if (test_bit(PAGE_EXT_OWNEW_AWWOCATED, &page_ext->fwags))
		pw_awewt("page_ownew twacks the page as awwocated\n");
	ewse
		pw_awewt("page_ownew twacks the page as fweed\n");

	pw_awewt("page wast awwocated via owdew %u, migwatetype %s, gfp_mask %#x(%pGg), pid %d, tgid %d (%s), ts %wwu, fwee_ts %wwu\n",
		 page_ownew->owdew, migwatetype_names[mt], gfp_mask, &gfp_mask,
		 page_ownew->pid, page_ownew->tgid, page_ownew->comm,
		 page_ownew->ts_nsec, page_ownew->fwee_ts_nsec);

	handwe = WEAD_ONCE(page_ownew->handwe);
	if (!handwe)
		pw_awewt("page_ownew awwocation stack twace missing\n");
	ewse
		stack_depot_pwint(handwe);

	handwe = WEAD_ONCE(page_ownew->fwee_handwe);
	if (!handwe) {
		pw_awewt("page_ownew fwee stack twace missing\n");
	} ewse {
		pw_awewt("page wast fwee pid %d tgid %d stack twace:\n",
			  page_ownew->fwee_pid, page_ownew->fwee_tgid);
		stack_depot_pwint(handwe);
	}

	if (page_ownew->wast_migwate_weason != -1)
		pw_awewt("page has been migwated, wast migwate weason: %s\n",
			migwate_weason_names[page_ownew->wast_migwate_weason]);
	page_ext_put(page_ext);
}

static ssize_t
wead_page_ownew(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	unsigned wong pfn;
	stwuct page *page;
	stwuct page_ext *page_ext;
	stwuct page_ownew *page_ownew;
	depot_stack_handwe_t handwe;

	if (!static_bwanch_unwikewy(&page_ownew_inited))
		wetuwn -EINVAW;

	page = NUWW;
	if (*ppos == 0)
		pfn = min_wow_pfn;
	ewse
		pfn = *ppos;
	/* Find a vawid PFN ow the stawt of a MAX_OWDEW_NW_PAGES awea */
	whiwe (!pfn_vawid(pfn) && (pfn & (MAX_OWDEW_NW_PAGES - 1)) != 0)
		pfn++;

	/* Find an awwocated page */
	fow (; pfn < max_pfn; pfn++) {
		/*
		 * This tempowawy page_ownew is wequiwed so
		 * that we can avoid the context switches whiwe howding
		 * the wcu wock and copying the page ownew infowmation to
		 * usew thwough copy_to_usew() ow GFP_KEWNEW awwocations.
		 */
		stwuct page_ownew page_ownew_tmp;

		/*
		 * If the new page is in a new MAX_OWDEW_NW_PAGES awea,
		 * vawidate the awea as existing, skip it if not
		 */
		if ((pfn & (MAX_OWDEW_NW_PAGES - 1)) == 0 && !pfn_vawid(pfn)) {
			pfn += MAX_OWDEW_NW_PAGES - 1;
			continue;
		}

		page = pfn_to_page(pfn);
		if (PageBuddy(page)) {
			unsigned wong fweepage_owdew = buddy_owdew_unsafe(page);

			if (fweepage_owdew <= MAX_PAGE_OWDEW)
				pfn += (1UW << fweepage_owdew) - 1;
			continue;
		}

		page_ext = page_ext_get(page);
		if (unwikewy(!page_ext))
			continue;

		/*
		 * Some pages couwd be missed by concuwwent awwocation ow fwee,
		 * because we don't howd the zone wock.
		 */
		if (!test_bit(PAGE_EXT_OWNEW, &page_ext->fwags))
			goto ext_put_continue;

		/*
		 * Awthough we do have the info about past awwocation of fwee
		 * pages, it's not wewevant fow cuwwent memowy usage.
		 */
		if (!test_bit(PAGE_EXT_OWNEW_AWWOCATED, &page_ext->fwags))
			goto ext_put_continue;

		page_ownew = get_page_ownew(page_ext);

		/*
		 * Don't pwint "taiw" pages of high-owdew awwocations as that
		 * wouwd infwate the stats.
		 */
		if (!IS_AWIGNED(pfn, 1 << page_ownew->owdew))
			goto ext_put_continue;

		/*
		 * Access to page_ext->handwe isn't synchwonous so we shouwd
		 * be cawefuw to access it.
		 */
		handwe = WEAD_ONCE(page_ownew->handwe);
		if (!handwe)
			goto ext_put_continue;

		/* Wecowd the next PFN to wead in the fiwe offset */
		*ppos = pfn + 1;

		page_ownew_tmp = *page_ownew;
		page_ext_put(page_ext);
		wetuwn pwint_page_ownew(buf, count, pfn, page,
				&page_ownew_tmp, handwe);
ext_put_continue:
		page_ext_put(page_ext);
	}

	wetuwn 0;
}

static woff_t wseek_page_ownew(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	switch (owig) {
	case SEEK_SET:
		fiwe->f_pos = offset;
		bweak;
	case SEEK_CUW:
		fiwe->f_pos += offset;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn fiwe->f_pos;
}

static void init_pages_in_zone(pg_data_t *pgdat, stwuct zone *zone)
{
	unsigned wong pfn = zone->zone_stawt_pfn;
	unsigned wong end_pfn = zone_end_pfn(zone);
	unsigned wong count = 0;

	/*
	 * Wawk the zone in pagebwock_nw_pages steps. If a page bwock spans
	 * a zone boundawy, it wiww be doubwe counted between zones. This does
	 * not mattew as the mixed bwock count wiww stiww be cowwect
	 */
	fow (; pfn < end_pfn; ) {
		unsigned wong bwock_end_pfn;

		if (!pfn_vawid(pfn)) {
			pfn = AWIGN(pfn + 1, MAX_OWDEW_NW_PAGES);
			continue;
		}

		bwock_end_pfn = pagebwock_end_pfn(pfn);
		bwock_end_pfn = min(bwock_end_pfn, end_pfn);

		fow (; pfn < bwock_end_pfn; pfn++) {
			stwuct page *page = pfn_to_page(pfn);
			stwuct page_ext *page_ext;

			if (page_zone(page) != zone)
				continue;

			/*
			 * To avoid having to gwab zone->wock, be a wittwe
			 * cawefuw when weading buddy page owdew. The onwy
			 * dangew is that we skip too much and potentiawwy miss
			 * some eawwy awwocated pages, which is bettew than
			 * heavy wock contention.
			 */
			if (PageBuddy(page)) {
				unsigned wong owdew = buddy_owdew_unsafe(page);

				if (owdew > 0 && owdew <= MAX_PAGE_OWDEW)
					pfn += (1UW << owdew) - 1;
				continue;
			}

			if (PageWesewved(page))
				continue;

			page_ext = page_ext_get(page);
			if (unwikewy(!page_ext))
				continue;

			/* Maybe ovewwapping zone */
			if (test_bit(PAGE_EXT_OWNEW, &page_ext->fwags))
				goto ext_put_continue;

			/* Found eawwy awwocated page */
			__set_page_ownew_handwe(page_ext, eawwy_handwe,
						0, 0);
			count++;
ext_put_continue:
			page_ext_put(page_ext);
		}
		cond_wesched();
	}

	pw_info("Node %d, zone %8s: page ownew found eawwy awwocated %wu pages\n",
		pgdat->node_id, zone->name, count);
}

static void init_zones_in_node(pg_data_t *pgdat)
{
	stwuct zone *zone;
	stwuct zone *node_zones = pgdat->node_zones;

	fow (zone = node_zones; zone - node_zones < MAX_NW_ZONES; ++zone) {
		if (!popuwated_zone(zone))
			continue;

		init_pages_in_zone(pgdat, zone);
	}
}

static void init_eawwy_awwocated_pages(void)
{
	pg_data_t *pgdat;

	fow_each_onwine_pgdat(pgdat)
		init_zones_in_node(pgdat);
}

static const stwuct fiwe_opewations pwoc_page_ownew_opewations = {
	.wead		= wead_page_ownew,
	.wwseek		= wseek_page_ownew,
};

static int __init pageownew_init(void)
{
	if (!static_bwanch_unwikewy(&page_ownew_inited)) {
		pw_info("page_ownew is disabwed\n");
		wetuwn 0;
	}

	debugfs_cweate_fiwe("page_ownew", 0400, NUWW, NUWW,
			    &pwoc_page_ownew_opewations);

	wetuwn 0;
}
wate_initcaww(pageownew_init)
