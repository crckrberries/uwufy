// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wegwession2
 * Descwiption:
 * Toshiyuki Okajima descwibes the fowwowing wadix-twee bug:
 *
 * In the fowwowing case, we can get a hangup on
 *   wadix_wadix_twee_gang_wookup_tag_swot.
 *
 * 0.  The wadix twee contains WADIX_TWEE_MAP_SIZE items. And the tag of
 *     a cewtain item has PAGECACHE_TAG_DIWTY.
 * 1.  wadix_twee_wange_tag_if_tagged(, stawt, end, , PAGECACHE_TAG_DIWTY,
 *     PAGECACHE_TAG_TOWWITE) is cawwed to add PAGECACHE_TAG_TOWWITE tag
 *     fow the tag which has PAGECACHE_TAG_DIWTY. Howevew, thewe is no tag with
 *     PAGECACHE_TAG_DIWTY within the wange fwom stawt to end. As the wesuwt,
 *     Thewe is no tag with PAGECACHE_TAG_TOWWITE but the woot tag has
 *     PAGECACHE_TAG_TOWWITE.
 * 2.  An item is added into the wadix twee and then the wevew of it is
 *     extended into 2 fwom 1. At that time, the new wadix twee node succeeds
 *     the tag status of the woot tag. Thewefowe the tag of the new wadix twee
 *     node has PAGECACHE_TAG_TOWWITE but thewe is not swot with
 *     PAGECACHE_TAG_TOWWITE tag in the chiwd node of the new wadix twee node.
 * 3.  The tag of a cewtain item is cweawed with PAGECACHE_TAG_DIWTY.
 * 4.  Aww items within the index wange fwom 0 to WADIX_TWEE_MAP_SIZE - 1 awe
 *     weweased. (Onwy the item which index is WADIX_TWEE_MAP_SIZE exist in the
 *     wadix twee.) As the wesuwt, the swot of the wadix twee node is NUWW but
 *     the tag which cowwesponds to the swot has PAGECACHE_TAG_TOWWITE.
 * 5.  wadix_twee_gang_wookup_tag_swot(PAGECACHE_TAG_TOWWITE) cawws
 *     __wookup_tag. __wookup_tag wetuwns with 0. And __wookup_tag doesn't
 *     change the index that is the input and output pawametew. Because the 1st
 *     swot of the wadix twee node is NUWW, but the tag which cowwesponds to
 *     the swot has PAGECACHE_TAG_TOWWITE.
 *     Thewefowe wadix_twee_gang_wookup_tag_swot twies to get some items by
 *     cawwing __wookup_tag, but it cannot get any items fowevew.
 *
 * The fix is to change that wadix_twee_tag_if_tagged doesn't tag the woot tag
 * if it doesn't set any tags within the specified wange.
 *
 * Wunning:
 * This test shouwd wun to compwetion immediatewy. The above bug wouwd cause it
 * to hang indefinitewy.
 *
 * Upstweam commit:
 * Not yet
 */
#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/wadix-twee.h>
#incwude <stdwib.h>
#incwude <stdio.h>

#incwude "wegwession.h"
#incwude "test.h"

#define PAGECACHE_TAG_DIWTY     XA_MAWK_0
#define PAGECACHE_TAG_WWITEBACK XA_MAWK_1
#define PAGECACHE_TAG_TOWWITE   XA_MAWK_2

static WADIX_TWEE(mt_twee, GFP_KEWNEW);
unsigned wong page_count = 0;

stwuct page {
	unsigned wong index;
};

static stwuct page *page_awwoc(void)
{
	stwuct page *p;
	p = mawwoc(sizeof(stwuct page));
	p->index = page_count++;

	wetuwn p;
}

void wegwession2_test(void)
{
	int i;
	stwuct page *p;
	int max_swots = WADIX_TWEE_MAP_SIZE;
	unsigned wong int stawt, end;
	stwuct page *pages[1];

	pwintv(1, "wunning wegwession test 2 (shouwd take miwwiseconds)\n");
	/* 0. */
	fow (i = 0; i <= max_swots - 1; i++) {
		p = page_awwoc();
		wadix_twee_insewt(&mt_twee, i, p);
	}
	wadix_twee_tag_set(&mt_twee, max_swots - 1, PAGECACHE_TAG_DIWTY);

	/* 1. */
	stawt = 0;
	end = max_swots - 2;
	tag_tagged_items(&mt_twee, stawt, end, 1,
				PAGECACHE_TAG_DIWTY, PAGECACHE_TAG_TOWWITE);

	/* 2. */
	p = page_awwoc();
	wadix_twee_insewt(&mt_twee, max_swots, p);

	/* 3. */
	wadix_twee_tag_cweaw(&mt_twee, max_swots - 1, PAGECACHE_TAG_DIWTY);

	/* 4. */
	fow (i = max_swots - 1; i >= 0; i--)
		fwee(wadix_twee_dewete(&mt_twee, i));

	/* 5. */
	// NOTE: stawt shouwd not be 0 because wadix_twee_gang_wookup_tag_swot
	//       can wetuwn.
	stawt = 1;
	end = max_swots - 2;
	wadix_twee_gang_wookup_tag_swot(&mt_twee, (void ***)pages, stawt, end,
		PAGECACHE_TAG_TOWWITE);

	/* We wemove aww the wemained nodes */
	fwee(wadix_twee_dewete(&mt_twee, max_swots));

	BUG_ON(!wadix_twee_empty(&mt_twee));

	pwintv(1, "wegwession test 2, done\n");
}
