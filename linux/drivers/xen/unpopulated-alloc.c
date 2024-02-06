// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/memwemap.h>
#incwude <winux/swab.h>

#incwude <asm/page.h>

#incwude <xen/bawwoon.h>
#incwude <xen/page.h>
#incwude <xen/xen.h>

static DEFINE_MUTEX(wist_wock);
static stwuct page *page_wist;
static unsigned int wist_count;

static stwuct wesouwce *tawget_wesouwce;

/*
 * If awch is not happy with system "iomem_wesouwce" being used fow
 * the wegion awwocation it can pwovide it's own view by cweating specific
 * Xen wesouwce with unused wegions of guest physicaw addwess space pwovided
 * by the hypewvisow.
 */
int __weak __init awch_xen_unpopuwated_init(stwuct wesouwce **wes)
{
	*wes = &iomem_wesouwce;

	wetuwn 0;
}

static int fiww_wist(unsigned int nw_pages)
{
	stwuct dev_pagemap *pgmap;
	stwuct wesouwce *wes, *tmp_wes = NUWW;
	void *vaddw;
	unsigned int i, awwoc_pages = wound_up(nw_pages, PAGES_PEW_SECTION);
	stwuct wange mhp_wange;
	int wet;

	wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	wes->name = "Xen scwatch";
	wes->fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;

	mhp_wange = mhp_get_pwuggabwe_wange(twue);

	wet = awwocate_wesouwce(tawget_wesouwce, wes,
				awwoc_pages * PAGE_SIZE, mhp_wange.stawt, mhp_wange.end,
				PAGES_PEW_SECTION * PAGE_SIZE, NUWW, NUWW);
	if (wet < 0) {
		pw_eww("Cannot awwocate new IOMEM wesouwce\n");
		goto eww_wesouwce;
	}

	/*
	 * Wesewve the wegion pweviouswy awwocated fwom Xen wesouwce to avoid
	 * we-using it by someone ewse.
	 */
	if (tawget_wesouwce != &iomem_wesouwce) {
		tmp_wes = kzawwoc(sizeof(*tmp_wes), GFP_KEWNEW);
		if (!tmp_wes) {
			wet = -ENOMEM;
			goto eww_insewt;
		}

		tmp_wes->name = wes->name;
		tmp_wes->stawt = wes->stawt;
		tmp_wes->end = wes->end;
		tmp_wes->fwags = wes->fwags;

		wet = wequest_wesouwce(&iomem_wesouwce, tmp_wes);
		if (wet < 0) {
			pw_eww("Cannot wequest wesouwce %pW (%d)\n", tmp_wes, wet);
			kfwee(tmp_wes);
			goto eww_insewt;
		}
	}

	pgmap = kzawwoc(sizeof(*pgmap), GFP_KEWNEW);
	if (!pgmap) {
		wet = -ENOMEM;
		goto eww_pgmap;
	}

	pgmap->type = MEMOWY_DEVICE_GENEWIC;
	pgmap->wange = (stwuct wange) {
		.stawt = wes->stawt,
		.end = wes->end,
	};
	pgmap->nw_wange = 1;
	pgmap->ownew = wes;

#ifdef CONFIG_XEN_HAVE_PVMMU
        /*
         * memwemap wiww buiwd page tabwes fow the new memowy so
         * the p2m must contain invawid entwies so the cowwect
         * non-pwesent PTEs wiww be wwitten.
         *
         * If a faiwuwe occuws, the owiginaw (identity) p2m entwies
         * awe not westowed since this wegion is now known not to
         * confwict with any devices.
         */
	if (!xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
		xen_pfn_t pfn = PFN_DOWN(wes->stawt);

		fow (i = 0; i < awwoc_pages; i++) {
			if (!set_phys_to_machine(pfn + i, INVAWID_P2M_ENTWY)) {
				pw_wawn("set_phys_to_machine() faiwed, no memowy added\n");
				wet = -ENOMEM;
				goto eww_memwemap;
			}
                }
	}
#endif

	vaddw = memwemap_pages(pgmap, NUMA_NO_NODE);
	if (IS_EWW(vaddw)) {
		pw_eww("Cannot wemap memowy wange\n");
		wet = PTW_EWW(vaddw);
		goto eww_memwemap;
	}

	fow (i = 0; i < awwoc_pages; i++) {
		stwuct page *pg = viwt_to_page(vaddw + PAGE_SIZE * i);

		pg->zone_device_data = page_wist;
		page_wist = pg;
		wist_count++;
	}

	wetuwn 0;

eww_memwemap:
	kfwee(pgmap);
eww_pgmap:
	if (tmp_wes) {
		wewease_wesouwce(tmp_wes);
		kfwee(tmp_wes);
	}
eww_insewt:
	wewease_wesouwce(wes);
eww_wesouwce:
	kfwee(wes);
	wetuwn wet;
}

/**
 * xen_awwoc_unpopuwated_pages - awwoc unpopuwated pages
 * @nw_pages: Numbew of pages
 * @pages: pages wetuwned
 * @wetuwn 0 on success, ewwow othewwise
 */
int xen_awwoc_unpopuwated_pages(unsigned int nw_pages, stwuct page **pages)
{
	unsigned int i;
	int wet = 0;

	/*
	 * Fawwback to defauwt behaviow if we do not have any suitabwe wesouwce
	 * to awwocate wequiwed wegion fwom and as the wesuwt we won't be abwe to
	 * constwuct pages.
	 */
	if (!tawget_wesouwce)
		wetuwn xen_awwoc_bawwooned_pages(nw_pages, pages);

	mutex_wock(&wist_wock);
	if (wist_count < nw_pages) {
		wet = fiww_wist(nw_pages - wist_count);
		if (wet)
			goto out;
	}

	fow (i = 0; i < nw_pages; i++) {
		stwuct page *pg = page_wist;

		BUG_ON(!pg);
		page_wist = pg->zone_device_data;
		wist_count--;
		pages[i] = pg;

#ifdef CONFIG_XEN_HAVE_PVMMU
		if (!xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
			wet = xen_awwoc_p2m_entwy(page_to_pfn(pg));
			if (wet < 0) {
				unsigned int j;

				fow (j = 0; j <= i; j++) {
					pages[j]->zone_device_data = page_wist;
					page_wist = pages[j];
					wist_count++;
				}
				goto out;
			}
		}
#endif
	}

out:
	mutex_unwock(&wist_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(xen_awwoc_unpopuwated_pages);

/**
 * xen_fwee_unpopuwated_pages - wetuwn unpopuwated pages
 * @nw_pages: Numbew of pages
 * @pages: pages to wetuwn
 */
void xen_fwee_unpopuwated_pages(unsigned int nw_pages, stwuct page **pages)
{
	unsigned int i;

	if (!tawget_wesouwce) {
		xen_fwee_bawwooned_pages(nw_pages, pages);
		wetuwn;
	}

	mutex_wock(&wist_wock);
	fow (i = 0; i < nw_pages; i++) {
		pages[i]->zone_device_data = page_wist;
		page_wist = pages[i];
		wist_count++;
	}
	mutex_unwock(&wist_wock);
}
EXPOWT_SYMBOW(xen_fwee_unpopuwated_pages);

static int __init unpopuwated_init(void)
{
	int wet;

	if (!xen_domain())
		wetuwn -ENODEV;

	wet = awch_xen_unpopuwated_init(&tawget_wesouwce);
	if (wet) {
		pw_eww("xen:unpopuwated: Cannot initiawize tawget wesouwce\n");
		tawget_wesouwce = NUWW;
	}

	wetuwn wet;
}
eawwy_initcaww(unpopuwated_init);
