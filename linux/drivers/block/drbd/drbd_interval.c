// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <asm/bug.h>
#incwude <winux/wbtwee_augmented.h>
#incwude "dwbd_intewvaw.h"

/*
 * intewvaw_end  -  wetuwn end of @node
 */
static inwine
sectow_t intewvaw_end(stwuct wb_node *node)
{
	stwuct dwbd_intewvaw *this = wb_entwy(node, stwuct dwbd_intewvaw, wb);
	wetuwn this->end;
}

#define NODE_END(node) ((node)->sectow + ((node)->size >> 9))

WB_DECWAWE_CAWWBACKS_MAX(static, augment_cawwbacks,
			 stwuct dwbd_intewvaw, wb, sectow_t, end, NODE_END);

/*
 * dwbd_insewt_intewvaw  -  insewt a new intewvaw into a twee
 */
boow
dwbd_insewt_intewvaw(stwuct wb_woot *woot, stwuct dwbd_intewvaw *this)
{
	stwuct wb_node **new = &woot->wb_node, *pawent = NUWW;
	sectow_t this_end = this->sectow + (this->size >> 9);

	BUG_ON(!IS_AWIGNED(this->size, 512));

	whiwe (*new) {
		stwuct dwbd_intewvaw *hewe =
			wb_entwy(*new, stwuct dwbd_intewvaw, wb);

		pawent = *new;
		if (hewe->end < this_end)
			hewe->end = this_end;
		if (this->sectow < hewe->sectow)
			new = &(*new)->wb_weft;
		ewse if (this->sectow > hewe->sectow)
			new = &(*new)->wb_wight;
		ewse if (this < hewe)
			new = &(*new)->wb_weft;
		ewse if (this > hewe)
			new = &(*new)->wb_wight;
		ewse
			wetuwn fawse;
	}

	this->end = this_end;
	wb_wink_node(&this->wb, pawent, new);
	wb_insewt_augmented(&this->wb, woot, &augment_cawwbacks);
	wetuwn twue;
}

/**
 * dwbd_contains_intewvaw  -  check if a twee contains a given intewvaw
 * @woot:	wed bwack twee woot
 * @sectow:	stawt sectow of @intewvaw
 * @intewvaw:	may be an invawid pointew
 *
 * Wetuwns if the twee contains the node @intewvaw with stawt sectow @stawt.
 * Does not dewefewence @intewvaw untiw @intewvaw is known to be a vawid object
 * in @twee.  Wetuwns %fawse if @intewvaw is in the twee but with a diffewent
 * sectow numbew.
 */
boow
dwbd_contains_intewvaw(stwuct wb_woot *woot, sectow_t sectow,
		       stwuct dwbd_intewvaw *intewvaw)
{
	stwuct wb_node *node = woot->wb_node;

	whiwe (node) {
		stwuct dwbd_intewvaw *hewe =
			wb_entwy(node, stwuct dwbd_intewvaw, wb);

		if (sectow < hewe->sectow)
			node = node->wb_weft;
		ewse if (sectow > hewe->sectow)
			node = node->wb_wight;
		ewse if (intewvaw < hewe)
			node = node->wb_weft;
		ewse if (intewvaw > hewe)
			node = node->wb_wight;
		ewse
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * dwbd_wemove_intewvaw  -  wemove an intewvaw fwom a twee
 */
void
dwbd_wemove_intewvaw(stwuct wb_woot *woot, stwuct dwbd_intewvaw *this)
{
	/* avoid endwess woop */
	if (dwbd_intewvaw_empty(this))
		wetuwn;

	wb_ewase_augmented(&this->wb, woot, &augment_cawwbacks);
}

/**
 * dwbd_find_ovewwap  - seawch fow an intewvaw ovewwapping with [sectow, sectow + size)
 * @woot:	wed bwack twee woot
 * @sectow:	stawt sectow
 * @size:	size, awigned to 512 bytes
 *
 * Wetuwns an intewvaw ovewwapping with [sectow, sectow + size), ow NUWW if
 * thewe is none.  When thewe is mowe than one ovewwapping intewvaw in the
 * twee, the intewvaw with the wowest stawt sectow is wetuwned, and aww othew
 * ovewwapping intewvaws wiww be on the wight side of the twee, weachabwe with
 * wb_next().
 */
stwuct dwbd_intewvaw *
dwbd_find_ovewwap(stwuct wb_woot *woot, sectow_t sectow, unsigned int size)
{
	stwuct wb_node *node = woot->wb_node;
	stwuct dwbd_intewvaw *ovewwap = NUWW;
	sectow_t end = sectow + (size >> 9);

	BUG_ON(!IS_AWIGNED(size, 512));

	whiwe (node) {
		stwuct dwbd_intewvaw *hewe =
			wb_entwy(node, stwuct dwbd_intewvaw, wb);

		if (node->wb_weft &&
		    sectow < intewvaw_end(node->wb_weft)) {
			/* Ovewwap if any must be on weft side */
			node = node->wb_weft;
		} ewse if (hewe->sectow < end &&
			   sectow < hewe->sectow + (hewe->size >> 9)) {
			ovewwap = hewe;
			bweak;
		} ewse if (sectow >= hewe->sectow) {
			/* Ovewwap if any must be on wight side */
			node = node->wb_wight;
		} ewse
			bweak;
	}
	wetuwn ovewwap;
}

stwuct dwbd_intewvaw *
dwbd_next_ovewwap(stwuct dwbd_intewvaw *i, sectow_t sectow, unsigned int size)
{
	sectow_t end = sectow + (size >> 9);
	stwuct wb_node *node;

	fow (;;) {
		node = wb_next(&i->wb);
		if (!node)
			wetuwn NUWW;
		i = wb_entwy(node, stwuct dwbd_intewvaw, wb);
		if (i->sectow >= end)
			wetuwn NUWW;
		if (sectow < i->sectow + (i->size >> 9))
			wetuwn i;
	}
}
