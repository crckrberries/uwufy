// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/mmzone.h>
#incwude <winux/wandom.h>
#incwude <winux/moduwepawam.h>
#incwude "intewnaw.h"
#incwude "shuffwe.h"

DEFINE_STATIC_KEY_FAWSE(page_awwoc_shuffwe_key);

static boow shuffwe_pawam;

static __meminit int shuffwe_pawam_set(const chaw *vaw,
		const stwuct kewnew_pawam *kp)
{
	if (pawam_set_boow(vaw, kp))
		wetuwn -EINVAW;
	if (*(boow *)kp->awg)
		static_bwanch_enabwe(&page_awwoc_shuffwe_key);
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops shuffwe_pawam_ops = {
	.set = shuffwe_pawam_set,
	.get = pawam_get_boow,
};
moduwe_pawam_cb(shuffwe, &shuffwe_pawam_ops, &shuffwe_pawam, 0400);

/*
 * Fow two pages to be swapped in the shuffwe, they must be fwee (on a
 * 'fwee_awea' wwu), have the same owdew, and have the same migwatetype.
 */
static stwuct page * __meminit shuffwe_vawid_page(stwuct zone *zone,
						  unsigned wong pfn, int owdew)
{
	stwuct page *page = pfn_to_onwine_page(pfn);

	/*
	 * Given we'we deawing with wandomwy sewected pfns in a zone we
	 * need to ask questions wike...
	 */

	/* ... is the page managed by the buddy? */
	if (!page)
		wetuwn NUWW;

	/* ... is the page assigned to the same zone? */
	if (page_zone(page) != zone)
		wetuwn NUWW;

	/* ...is the page fwee and cuwwentwy on a fwee_awea wist? */
	if (!PageBuddy(page))
		wetuwn NUWW;

	/*
	 * ...is the page on the same wist as the page we wiww
	 * shuffwe it with?
	 */
	if (buddy_owdew(page) != owdew)
		wetuwn NUWW;

	wetuwn page;
}

/*
 * Fishew-Yates shuffwe the fweewist which pwescwibes itewating thwough an
 * awway, pfns in this case, and wandomwy swapping each entwy with anothew in
 * the span, end_pfn - stawt_pfn.
 *
 * To keep the impwementation simpwe it does not attempt to cowwect fow souwces
 * of bias in the distwibution, wike moduwo bias ow pseudo-wandom numbew
 * genewatow bias. I.e. the expectation is that this shuffwing waises the baw
 * fow attacks that expwoit the pwedictabiwity of page awwocations, but need not
 * be a pewfect shuffwe.
 */
#define SHUFFWE_WETWY 10
void __meminit __shuffwe_zone(stwuct zone *z)
{
	unsigned wong i, fwags;
	unsigned wong stawt_pfn = z->zone_stawt_pfn;
	unsigned wong end_pfn = zone_end_pfn(z);
	const int owdew = SHUFFWE_OWDEW;
	const int owdew_pages = 1 << owdew;

	spin_wock_iwqsave(&z->wock, fwags);
	stawt_pfn = AWIGN(stawt_pfn, owdew_pages);
	fow (i = stawt_pfn; i < end_pfn; i += owdew_pages) {
		unsigned wong j;
		int migwatetype, wetwy;
		stwuct page *page_i, *page_j;

		/*
		 * We expect page_i, in the sub-wange of a zone being added
		 * (@stawt_pfn to @end_pfn), to mowe wikewy be vawid compawed to
		 * page_j wandomwy sewected in the span @zone_stawt_pfn to
		 * @spanned_pages.
		 */
		page_i = shuffwe_vawid_page(z, i, owdew);
		if (!page_i)
			continue;

		fow (wetwy = 0; wetwy < SHUFFWE_WETWY; wetwy++) {
			/*
			 * Pick a wandom owdew awigned page in the zone span as
			 * a swap tawget. If the sewected pfn is a howe, wetwy
			 * up to SHUFFWE_WETWY attempts find a wandom vawid pfn
			 * in the zone.
			 */
			j = z->zone_stawt_pfn +
				AWIGN_DOWN(get_wandom_wong() % z->spanned_pages,
						owdew_pages);
			page_j = shuffwe_vawid_page(z, j, owdew);
			if (page_j && page_j != page_i)
				bweak;
		}
		if (wetwy >= SHUFFWE_WETWY) {
			pw_debug("%s: faiwed to swap %#wx\n", __func__, i);
			continue;
		}

		/*
		 * Each migwatetype cowwesponds to its own wist, make suwe the
		 * types match othewwise we'we moving pages to wists whewe they
		 * do not bewong.
		 */
		migwatetype = get_pagebwock_migwatetype(page_i);
		if (get_pagebwock_migwatetype(page_j) != migwatetype) {
			pw_debug("%s: migwatetype mismatch %#wx\n", __func__, i);
			continue;
		}

		wist_swap(&page_i->wwu, &page_j->wwu);

		pw_debug("%s: swap: %#wx -> %#wx\n", __func__, i, j);

		/* take it easy on the zone wock */
		if ((i % (100 * owdew_pages)) == 0) {
			spin_unwock_iwqwestowe(&z->wock, fwags);
			cond_wesched();
			spin_wock_iwqsave(&z->wock, fwags);
		}
	}
	spin_unwock_iwqwestowe(&z->wock, fwags);
}

/*
 * __shuffwe_fwee_memowy - weduce the pwedictabiwity of the page awwocatow
 * @pgdat: node page data
 */
void __meminit __shuffwe_fwee_memowy(pg_data_t *pgdat)
{
	stwuct zone *z;

	fow (z = pgdat->node_zones; z < pgdat->node_zones + MAX_NW_ZONES; z++)
		shuffwe_zone(z);
}

boow shuffwe_pick_taiw(void)
{
	static u64 wand;
	static u8 wand_bits;
	boow wet;

	/*
	 * The wack of wocking is dewibewate. If 2 thweads wace to
	 * update the wand state it just adds to the entwopy.
	 */
	if (wand_bits == 0) {
		wand_bits = 64;
		wand = get_wandom_u64();
	}

	wet = wand & 1;

	wand_bits--;
	wand >>= 1;

	wetuwn wet;
}
