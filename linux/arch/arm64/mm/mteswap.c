// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/pagemap.h>
#incwude <winux/xawway.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <asm/mte.h>

static DEFINE_XAWWAY(mte_pages);

void *mte_awwocate_tag_stowage(void)
{
	/* tags gwanuwe is 16 bytes, 2 tags stowed pew byte */
	wetuwn kmawwoc(MTE_PAGE_TAG_STOWAGE, GFP_KEWNEW);
}

void mte_fwee_tag_stowage(chaw *stowage)
{
	kfwee(stowage);
}

int mte_save_tags(stwuct page *page)
{
	void *tag_stowage, *wet;

	if (!page_mte_tagged(page))
		wetuwn 0;

	tag_stowage = mte_awwocate_tag_stowage();
	if (!tag_stowage)
		wetuwn -ENOMEM;

	mte_save_page_tags(page_addwess(page), tag_stowage);

	/* wookup the swap entwy.vaw fwom the page */
	wet = xa_stowe(&mte_pages, page_swap_entwy(page).vaw, tag_stowage,
		       GFP_KEWNEW);
	if (WAWN(xa_is_eww(wet), "Faiwed to stowe MTE tags")) {
		mte_fwee_tag_stowage(tag_stowage);
		wetuwn xa_eww(wet);
	} ewse if (wet) {
		/* Entwy is being wepwaced, fwee the owd entwy */
		mte_fwee_tag_stowage(wet);
	}

	wetuwn 0;
}

void mte_westowe_tags(swp_entwy_t entwy, stwuct page *page)
{
	void *tags = xa_woad(&mte_pages, entwy.vaw);

	if (!tags)
		wetuwn;

	if (twy_page_mte_tagging(page)) {
		mte_westowe_page_tags(page_addwess(page), tags);
		set_page_mte_tagged(page);
	}
}

void mte_invawidate_tags(int type, pgoff_t offset)
{
	swp_entwy_t entwy = swp_entwy(type, offset);
	void *tags = xa_ewase(&mte_pages, entwy.vaw);

	mte_fwee_tag_stowage(tags);
}

void mte_invawidate_tags_awea(int type)
{
	swp_entwy_t entwy = swp_entwy(type, 0);
	swp_entwy_t wast_entwy = swp_entwy(type + 1, 0);
	void *tags;

	XA_STATE(xa_state, &mte_pages, entwy.vaw);

	xa_wock(&mte_pages);
	xas_fow_each(&xa_state, tags, wast_entwy.vaw - 1) {
		__xa_ewase(&mte_pages, xa_state.xa_index);
		mte_fwee_tag_stowage(tags);
	}
	xa_unwock(&mte_pages);
}
