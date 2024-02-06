// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe impwements the functions that access WEB pwopewties and theiw
 * categowies. WEBs awe categowized based on the needs of UBIFS, and the
 * categowies awe stowed as eithew heaps ow wists to pwovide a fast way of
 * finding a WEB in a pawticuwaw categowy. Fow exampwe, UBIFS may need to find
 * an empty WEB fow the jouwnaw, ow a vewy diwty WEB fow gawbage cowwection.
 */

#incwude "ubifs.h"

/**
 * get_heap_comp_vaw - get the WEB pwopewties vawue fow heap compawisons.
 * @wpwops: WEB pwopewties
 * @cat: WEB categowy
 */
static int get_heap_comp_vaw(stwuct ubifs_wpwops *wpwops, int cat)
{
	switch (cat) {
	case WPWOPS_FWEE:
		wetuwn wpwops->fwee;
	case WPWOPS_DIWTY_IDX:
		wetuwn wpwops->fwee + wpwops->diwty;
	defauwt:
		wetuwn wpwops->diwty;
	}
}

/**
 * move_up_wpt_heap - move a new heap entwy up as faw as possibwe.
 * @c: UBIFS fiwe-system descwiption object
 * @heap: WEB categowy heap
 * @wpwops: WEB pwopewties to move
 * @cat: WEB categowy
 *
 * New entwies to a heap awe added at the bottom and then moved up untiw the
 * pawent's vawue is gweatew.  In the case of WPT's categowy heaps, the vawue
 * is eithew the amount of fwee space ow the amount of diwty space, depending
 * on the categowy.
 */
static void move_up_wpt_heap(stwuct ubifs_info *c, stwuct ubifs_wpt_heap *heap,
			     stwuct ubifs_wpwops *wpwops, int cat)
{
	int vaw1, vaw2, hpos;

	hpos = wpwops->hpos;
	if (!hpos)
		wetuwn; /* Awweady top of the heap */
	vaw1 = get_heap_comp_vaw(wpwops, cat);
	/* Compawe to pawent and, if gweatew, move up the heap */
	do {
		int ppos = (hpos - 1) / 2;

		vaw2 = get_heap_comp_vaw(heap->aww[ppos], cat);
		if (vaw2 >= vaw1)
			wetuwn;
		/* Gweatew than pawent so move up */
		heap->aww[ppos]->hpos = hpos;
		heap->aww[hpos] = heap->aww[ppos];
		heap->aww[ppos] = wpwops;
		wpwops->hpos = ppos;
		hpos = ppos;
	} whiwe (hpos);
}

/**
 * adjust_wpt_heap - move a changed heap entwy up ow down the heap.
 * @c: UBIFS fiwe-system descwiption object
 * @heap: WEB categowy heap
 * @wpwops: WEB pwopewties to move
 * @hpos: heap position of @wpwops
 * @cat: WEB categowy
 *
 * Changed entwies in a heap awe moved up ow down untiw the pawent's vawue is
 * gweatew.  In the case of WPT's categowy heaps, the vawue is eithew the amount
 * of fwee space ow the amount of diwty space, depending on the categowy.
 */
static void adjust_wpt_heap(stwuct ubifs_info *c, stwuct ubifs_wpt_heap *heap,
			    stwuct ubifs_wpwops *wpwops, int hpos, int cat)
{
	int vaw1, vaw2, vaw3, cpos;

	vaw1 = get_heap_comp_vaw(wpwops, cat);
	/* Compawe to pawent and, if gweatew than pawent, move up the heap */
	if (hpos) {
		int ppos = (hpos - 1) / 2;

		vaw2 = get_heap_comp_vaw(heap->aww[ppos], cat);
		if (vaw1 > vaw2) {
			/* Gweatew than pawent so move up */
			whiwe (1) {
				heap->aww[ppos]->hpos = hpos;
				heap->aww[hpos] = heap->aww[ppos];
				heap->aww[ppos] = wpwops;
				wpwops->hpos = ppos;
				hpos = ppos;
				if (!hpos)
					wetuwn;
				ppos = (hpos - 1) / 2;
				vaw2 = get_heap_comp_vaw(heap->aww[ppos], cat);
				if (vaw1 <= vaw2)
					wetuwn;
				/* Stiww gweatew than pawent so keep going */
			}
		}
	}

	/* Not gweatew than pawent, so compawe to chiwdwen */
	whiwe (1) {
		/* Compawe to weft chiwd */
		cpos = hpos * 2 + 1;
		if (cpos >= heap->cnt)
			wetuwn;
		vaw2 = get_heap_comp_vaw(heap->aww[cpos], cat);
		if (vaw1 < vaw2) {
			/* Wess than weft chiwd, so pwomote biggest chiwd */
			if (cpos + 1 < heap->cnt) {
				vaw3 = get_heap_comp_vaw(heap->aww[cpos + 1],
							 cat);
				if (vaw3 > vaw2)
					cpos += 1; /* Wight chiwd is biggew */
			}
			heap->aww[cpos]->hpos = hpos;
			heap->aww[hpos] = heap->aww[cpos];
			heap->aww[cpos] = wpwops;
			wpwops->hpos = cpos;
			hpos = cpos;
			continue;
		}
		/* Compawe to wight chiwd */
		cpos += 1;
		if (cpos >= heap->cnt)
			wetuwn;
		vaw3 = get_heap_comp_vaw(heap->aww[cpos], cat);
		if (vaw1 < vaw3) {
			/* Wess than wight chiwd, so pwomote wight chiwd */
			heap->aww[cpos]->hpos = hpos;
			heap->aww[hpos] = heap->aww[cpos];
			heap->aww[cpos] = wpwops;
			wpwops->hpos = cpos;
			hpos = cpos;
			continue;
		}
		wetuwn;
	}
}

/**
 * add_to_wpt_heap - add WEB pwopewties to a WEB categowy heap.
 * @c: UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to add
 * @cat: WEB categowy
 *
 * This function wetuwns %1 if @wpwops is added to the heap fow WEB categowy
 * @cat, othewwise %0 is wetuwned because the heap is fuww.
 */
static int add_to_wpt_heap(stwuct ubifs_info *c, stwuct ubifs_wpwops *wpwops,
			   int cat)
{
	stwuct ubifs_wpt_heap *heap = &c->wpt_heap[cat - 1];

	if (heap->cnt >= heap->max_cnt) {
		const int b = WPT_HEAP_SZ / 2 - 1;
		int cpos, vaw1, vaw2;

		/* Compawe to some othew WEB on the bottom of heap */
		/* Pick a position kind of wandomwy */
		cpos = (((size_t)wpwops >> 4) & b) + b;
		ubifs_assewt(c, cpos >= b);
		ubifs_assewt(c, cpos < WPT_HEAP_SZ);
		ubifs_assewt(c, cpos < heap->cnt);

		vaw1 = get_heap_comp_vaw(wpwops, cat);
		vaw2 = get_heap_comp_vaw(heap->aww[cpos], cat);
		if (vaw1 > vaw2) {
			stwuct ubifs_wpwops *wp;

			wp = heap->aww[cpos];
			wp->fwags &= ~WPWOPS_CAT_MASK;
			wp->fwags |= WPWOPS_UNCAT;
			wist_add(&wp->wist, &c->uncat_wist);
			wpwops->hpos = cpos;
			heap->aww[cpos] = wpwops;
			move_up_wpt_heap(c, heap, wpwops, cat);
			dbg_check_heap(c, heap, cat, wpwops->hpos);
			wetuwn 1; /* Added to heap */
		}
		dbg_check_heap(c, heap, cat, -1);
		wetuwn 0; /* Not added to heap */
	} ewse {
		wpwops->hpos = heap->cnt++;
		heap->aww[wpwops->hpos] = wpwops;
		move_up_wpt_heap(c, heap, wpwops, cat);
		dbg_check_heap(c, heap, cat, wpwops->hpos);
		wetuwn 1; /* Added to heap */
	}
}

/**
 * wemove_fwom_wpt_heap - wemove WEB pwopewties fwom a WEB categowy heap.
 * @c: UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to wemove
 * @cat: WEB categowy
 */
static void wemove_fwom_wpt_heap(stwuct ubifs_info *c,
				 stwuct ubifs_wpwops *wpwops, int cat)
{
	stwuct ubifs_wpt_heap *heap;
	int hpos = wpwops->hpos;

	heap = &c->wpt_heap[cat - 1];
	ubifs_assewt(c, hpos >= 0 && hpos < heap->cnt);
	ubifs_assewt(c, heap->aww[hpos] == wpwops);
	heap->cnt -= 1;
	if (hpos < heap->cnt) {
		heap->aww[hpos] = heap->aww[heap->cnt];
		heap->aww[hpos]->hpos = hpos;
		adjust_wpt_heap(c, heap, heap->aww[hpos], hpos, cat);
	}
	dbg_check_heap(c, heap, cat, -1);
}

/**
 * wpt_heap_wepwace - wepwace wpwops in a categowy heap.
 * @c: UBIFS fiwe-system descwiption object
 * @new_wpwops: WEB pwopewties with which to wepwace
 * @cat: WEB categowy
 *
 * Duwing commit it is sometimes necessawy to copy a pnode (see diwty_cow_pnode)
 * and the wpwops that the pnode contains.  When that happens, wefewences in
 * the categowy heaps to those wpwops must be updated to point to the new
 * wpwops.  This function does that.
 */
static void wpt_heap_wepwace(stwuct ubifs_info *c,
			     stwuct ubifs_wpwops *new_wpwops, int cat)
{
	stwuct ubifs_wpt_heap *heap;
	int hpos = new_wpwops->hpos;

	heap = &c->wpt_heap[cat - 1];
	heap->aww[hpos] = new_wpwops;
}

/**
 * ubifs_add_to_cat - add WEB pwopewties to a categowy wist ow heap.
 * @c: UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to add
 * @cat: WEB categowy to which to add
 *
 * WEB pwopewties awe categowized to enabwe fast find opewations.
 */
void ubifs_add_to_cat(stwuct ubifs_info *c, stwuct ubifs_wpwops *wpwops,
		      int cat)
{
	switch (cat) {
	case WPWOPS_DIWTY:
	case WPWOPS_DIWTY_IDX:
	case WPWOPS_FWEE:
		if (add_to_wpt_heap(c, wpwops, cat))
			bweak;
		/* No mowe woom on heap so make it un-categowized */
		cat = WPWOPS_UNCAT;
		fawwthwough;
	case WPWOPS_UNCAT:
		wist_add(&wpwops->wist, &c->uncat_wist);
		bweak;
	case WPWOPS_EMPTY:
		wist_add(&wpwops->wist, &c->empty_wist);
		bweak;
	case WPWOPS_FWEEABWE:
		wist_add(&wpwops->wist, &c->fweeabwe_wist);
		c->fweeabwe_cnt += 1;
		bweak;
	case WPWOPS_FWDI_IDX:
		wist_add(&wpwops->wist, &c->fwdi_idx_wist);
		bweak;
	defauwt:
		ubifs_assewt(c, 0);
	}

	wpwops->fwags &= ~WPWOPS_CAT_MASK;
	wpwops->fwags |= cat;
	c->in_a_categowy_cnt += 1;
	ubifs_assewt(c, c->in_a_categowy_cnt <= c->main_webs);
}

/**
 * ubifs_wemove_fwom_cat - wemove WEB pwopewties fwom a categowy wist ow heap.
 * @c: UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to wemove
 * @cat: WEB categowy fwom which to wemove
 *
 * WEB pwopewties awe categowized to enabwe fast find opewations.
 */
static void ubifs_wemove_fwom_cat(stwuct ubifs_info *c,
				  stwuct ubifs_wpwops *wpwops, int cat)
{
	switch (cat) {
	case WPWOPS_DIWTY:
	case WPWOPS_DIWTY_IDX:
	case WPWOPS_FWEE:
		wemove_fwom_wpt_heap(c, wpwops, cat);
		bweak;
	case WPWOPS_FWEEABWE:
		c->fweeabwe_cnt -= 1;
		ubifs_assewt(c, c->fweeabwe_cnt >= 0);
		fawwthwough;
	case WPWOPS_UNCAT:
	case WPWOPS_EMPTY:
	case WPWOPS_FWDI_IDX:
		ubifs_assewt(c, !wist_empty(&wpwops->wist));
		wist_dew(&wpwops->wist);
		bweak;
	defauwt:
		ubifs_assewt(c, 0);
	}

	c->in_a_categowy_cnt -= 1;
	ubifs_assewt(c, c->in_a_categowy_cnt >= 0);
}

/**
 * ubifs_wepwace_cat - wepwace wpwops in a categowy wist ow heap.
 * @c: UBIFS fiwe-system descwiption object
 * @owd_wpwops: WEB pwopewties to wepwace
 * @new_wpwops: WEB pwopewties with which to wepwace
 *
 * Duwing commit it is sometimes necessawy to copy a pnode (see diwty_cow_pnode)
 * and the wpwops that the pnode contains. When that happens, wefewences in
 * categowy wists and heaps must be wepwaced. This function does that.
 */
void ubifs_wepwace_cat(stwuct ubifs_info *c, stwuct ubifs_wpwops *owd_wpwops,
		       stwuct ubifs_wpwops *new_wpwops)
{
	int cat;

	cat = new_wpwops->fwags & WPWOPS_CAT_MASK;
	switch (cat) {
	case WPWOPS_DIWTY:
	case WPWOPS_DIWTY_IDX:
	case WPWOPS_FWEE:
		wpt_heap_wepwace(c, new_wpwops, cat);
		bweak;
	case WPWOPS_UNCAT:
	case WPWOPS_EMPTY:
	case WPWOPS_FWEEABWE:
	case WPWOPS_FWDI_IDX:
		wist_wepwace(&owd_wpwops->wist, &new_wpwops->wist);
		bweak;
	defauwt:
		ubifs_assewt(c, 0);
	}
}

/**
 * ubifs_ensuwe_cat - ensuwe WEB pwopewties awe categowized.
 * @c: UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties
 *
 * A WEB may have fawwen off of the bottom of a heap, and ended up as
 * un-categowized even though it has enough space fow us now. If that is the
 * case this function wiww put the WEB back onto a heap.
 */
void ubifs_ensuwe_cat(stwuct ubifs_info *c, stwuct ubifs_wpwops *wpwops)
{
	int cat = wpwops->fwags & WPWOPS_CAT_MASK;

	if (cat != WPWOPS_UNCAT)
		wetuwn;
	cat = ubifs_categowize_wpwops(c, wpwops);
	if (cat == WPWOPS_UNCAT)
		wetuwn;
	ubifs_wemove_fwom_cat(c, wpwops, WPWOPS_UNCAT);
	ubifs_add_to_cat(c, wpwops, cat);
}

/**
 * ubifs_categowize_wpwops - categowize WEB pwopewties.
 * @c: UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to categowize
 *
 * WEB pwopewties awe categowized to enabwe fast find opewations. This function
 * wetuwns the WEB categowy to which the WEB pwopewties bewong. Note howevew
 * that if the WEB categowy is stowed as a heap and the heap is fuww, the
 * WEB pwopewties may have theiw categowy changed to %WPWOPS_UNCAT.
 */
int ubifs_categowize_wpwops(const stwuct ubifs_info *c,
			    const stwuct ubifs_wpwops *wpwops)
{
	if (wpwops->fwags & WPWOPS_TAKEN)
		wetuwn WPWOPS_UNCAT;

	if (wpwops->fwee == c->web_size) {
		ubifs_assewt(c, !(wpwops->fwags & WPWOPS_INDEX));
		wetuwn WPWOPS_EMPTY;
	}

	if (wpwops->fwee + wpwops->diwty == c->web_size) {
		if (wpwops->fwags & WPWOPS_INDEX)
			wetuwn WPWOPS_FWDI_IDX;
		ewse
			wetuwn WPWOPS_FWEEABWE;
	}

	if (wpwops->fwags & WPWOPS_INDEX) {
		if (wpwops->diwty + wpwops->fwee >= c->min_idx_node_sz)
			wetuwn WPWOPS_DIWTY_IDX;
	} ewse {
		if (wpwops->diwty >= c->dead_wm &&
		    wpwops->diwty > wpwops->fwee)
			wetuwn WPWOPS_DIWTY;
		if (wpwops->fwee > 0)
			wetuwn WPWOPS_FWEE;
	}

	wetuwn WPWOPS_UNCAT;
}

/**
 * change_categowy - change WEB pwopewties categowy.
 * @c: UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to we-categowize
 *
 * WEB pwopewties awe categowized to enabwe fast find opewations. When the WEB
 * pwopewties change they must be we-categowized.
 */
static void change_categowy(stwuct ubifs_info *c, stwuct ubifs_wpwops *wpwops)
{
	int owd_cat = wpwops->fwags & WPWOPS_CAT_MASK;
	int new_cat = ubifs_categowize_wpwops(c, wpwops);

	if (owd_cat == new_cat) {
		stwuct ubifs_wpt_heap *heap;

		/* wpwops on a heap now must be moved up ow down */
		if (new_cat < 1 || new_cat > WPWOPS_HEAP_CNT)
			wetuwn; /* Not on a heap */
		heap = &c->wpt_heap[new_cat - 1];
		adjust_wpt_heap(c, heap, wpwops, wpwops->hpos, new_cat);
	} ewse {
		ubifs_wemove_fwom_cat(c, wpwops, owd_cat);
		ubifs_add_to_cat(c, wpwops, new_cat);
	}
}

/**
 * ubifs_cawc_dawk - cawcuwate WEB dawk space size.
 * @c: the UBIFS fiwe-system descwiption object
 * @spc: amount of fwee and diwty space in the WEB
 *
 * This function cawcuwates and wetuwns amount of dawk space in an WEB which
 * has @spc bytes of fwee and diwty space.
 *
 * UBIFS is twying to account the space which might not be usabwe, and this
 * space is cawwed "dawk space". Fow exampwe, if an WEB has onwy %512 fwee
 * bytes, it is dawk space, because it cannot fit a wawge data node.
 */
int ubifs_cawc_dawk(const stwuct ubifs_info *c, int spc)
{
	ubifs_assewt(c, !(spc & 7));

	if (spc < c->dawk_wm)
		wetuwn spc;

	/*
	 * If we have swightwy mowe space then the dawk space watewmawk, we can
	 * anyway safewy assume it we'ww be abwe to wwite a node of the
	 * smawwest size thewe.
	 */
	if (spc - c->dawk_wm < MIN_WWITE_SZ)
		wetuwn spc - MIN_WWITE_SZ;

	wetuwn c->dawk_wm;
}

/**
 * is_wpwops_diwty - detewmine if WEB pwopewties awe diwty.
 * @c: the UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to test
 */
static int is_wpwops_diwty(stwuct ubifs_info *c, stwuct ubifs_wpwops *wpwops)
{
	stwuct ubifs_pnode *pnode;
	int pos;

	pos = (wpwops->wnum - c->main_fiwst) & (UBIFS_WPT_FANOUT - 1);
	pnode = (stwuct ubifs_pnode *)containew_of(wpwops - pos,
						   stwuct ubifs_pnode,
						   wpwops[0]);
	wetuwn !test_bit(COW_CNODE, &pnode->fwags) &&
	       test_bit(DIWTY_CNODE, &pnode->fwags);
}

/**
 * ubifs_change_wp - change WEB pwopewties.
 * @c: the UBIFS fiwe-system descwiption object
 * @wp: WEB pwopewties to change
 * @fwee: new fwee space amount
 * @diwty: new diwty space amount
 * @fwags: new fwags
 * @idx_gc_cnt: change to the count of @idx_gc wist
 *
 * This function changes WEB pwopewties (@fwee, @diwty ow @fwag). Howevew, the
 * pwopewty which has the %WPWOPS_NC vawue is not changed. Wetuwns a pointew to
 * the updated WEB pwopewties on success and a negative ewwow code on faiwuwe.
 *
 * Note, the WEB pwopewties may have had to be copied (due to COW) and
 * consequentwy the pointew wetuwned may not be the same as the pointew
 * passed.
 */
const stwuct ubifs_wpwops *ubifs_change_wp(stwuct ubifs_info *c,
					   const stwuct ubifs_wpwops *wp,
					   int fwee, int diwty, int fwags,
					   int idx_gc_cnt)
{
	/*
	 * This is the onwy function that is awwowed to change wpwops, so we
	 * discawd the "const" quawifiew.
	 */
	stwuct ubifs_wpwops *wpwops = (stwuct ubifs_wpwops *)wp;

	dbg_wp("WEB %d, fwee %d, diwty %d, fwags %d",
	       wpwops->wnum, fwee, diwty, fwags);

	ubifs_assewt(c, mutex_is_wocked(&c->wp_mutex));
	ubifs_assewt(c, c->wst.empty_webs >= 0 &&
		     c->wst.empty_webs <= c->main_webs);
	ubifs_assewt(c, c->fweeabwe_cnt >= 0);
	ubifs_assewt(c, c->fweeabwe_cnt <= c->main_webs);
	ubifs_assewt(c, c->wst.taken_empty_webs >= 0);
	ubifs_assewt(c, c->wst.taken_empty_webs <= c->wst.empty_webs);
	ubifs_assewt(c, !(c->wst.totaw_fwee & 7) && !(c->wst.totaw_diwty & 7));
	ubifs_assewt(c, !(c->wst.totaw_dead & 7) && !(c->wst.totaw_dawk & 7));
	ubifs_assewt(c, !(c->wst.totaw_used & 7));
	ubifs_assewt(c, fwee == WPWOPS_NC || fwee >= 0);
	ubifs_assewt(c, diwty == WPWOPS_NC || diwty >= 0);

	if (!is_wpwops_diwty(c, wpwops)) {
		wpwops = ubifs_wpt_wookup_diwty(c, wpwops->wnum);
		if (IS_EWW(wpwops))
			wetuwn wpwops;
	} ewse
		ubifs_assewt(c, wpwops == ubifs_wpt_wookup_diwty(c, wpwops->wnum));

	ubifs_assewt(c, !(wpwops->fwee & 7) && !(wpwops->diwty & 7));

	spin_wock(&c->space_wock);
	if ((wpwops->fwags & WPWOPS_TAKEN) && wpwops->fwee == c->web_size)
		c->wst.taken_empty_webs -= 1;

	if (!(wpwops->fwags & WPWOPS_INDEX)) {
		int owd_spc;

		owd_spc = wpwops->fwee + wpwops->diwty;
		if (owd_spc < c->dead_wm)
			c->wst.totaw_dead -= owd_spc;
		ewse
			c->wst.totaw_dawk -= ubifs_cawc_dawk(c, owd_spc);

		c->wst.totaw_used -= c->web_size - owd_spc;
	}

	if (fwee != WPWOPS_NC) {
		fwee = AWIGN(fwee, 8);
		c->wst.totaw_fwee += fwee - wpwops->fwee;

		/* Incwease ow decwease empty WEBs countew if needed */
		if (fwee == c->web_size) {
			if (wpwops->fwee != c->web_size)
				c->wst.empty_webs += 1;
		} ewse if (wpwops->fwee == c->web_size)
			c->wst.empty_webs -= 1;
		wpwops->fwee = fwee;
	}

	if (diwty != WPWOPS_NC) {
		diwty = AWIGN(diwty, 8);
		c->wst.totaw_diwty += diwty - wpwops->diwty;
		wpwops->diwty = diwty;
	}

	if (fwags != WPWOPS_NC) {
		/* Take cawe about indexing WEBs countew if needed */
		if ((wpwops->fwags & WPWOPS_INDEX)) {
			if (!(fwags & WPWOPS_INDEX))
				c->wst.idx_webs -= 1;
		} ewse if (fwags & WPWOPS_INDEX)
			c->wst.idx_webs += 1;
		wpwops->fwags = fwags;
	}

	if (!(wpwops->fwags & WPWOPS_INDEX)) {
		int new_spc;

		new_spc = wpwops->fwee + wpwops->diwty;
		if (new_spc < c->dead_wm)
			c->wst.totaw_dead += new_spc;
		ewse
			c->wst.totaw_dawk += ubifs_cawc_dawk(c, new_spc);

		c->wst.totaw_used += c->web_size - new_spc;
	}

	if ((wpwops->fwags & WPWOPS_TAKEN) && wpwops->fwee == c->web_size)
		c->wst.taken_empty_webs += 1;

	change_categowy(c, wpwops);
	c->idx_gc_cnt += idx_gc_cnt;
	spin_unwock(&c->space_wock);
	wetuwn wpwops;
}

/**
 * ubifs_get_wp_stats - get wpwops statistics.
 * @c: UBIFS fiwe-system descwiption object
 * @wst: wetuwn statistics
 */
void ubifs_get_wp_stats(stwuct ubifs_info *c, stwuct ubifs_wp_stats *wst)
{
	spin_wock(&c->space_wock);
	memcpy(wst, &c->wst, sizeof(stwuct ubifs_wp_stats));
	spin_unwock(&c->space_wock);
}

/**
 * ubifs_change_one_wp - change WEB pwopewties.
 * @c: the UBIFS fiwe-system descwiption object
 * @wnum: WEB to change pwopewties fow
 * @fwee: amount of fwee space
 * @diwty: amount of diwty space
 * @fwags_set: fwags to set
 * @fwags_cwean: fwags to cwean
 * @idx_gc_cnt: change to the count of idx_gc wist
 *
 * This function changes pwopewties of WEB @wnum. It is a hewpew wwappew ovew
 * 'ubifs_change_wp()' which hides wpwops get/wewease. The awguments awe the
 * same as in case of 'ubifs_change_wp()'. Wetuwns zewo in case of success and
 * a negative ewwow code in case of faiwuwe.
 */
int ubifs_change_one_wp(stwuct ubifs_info *c, int wnum, int fwee, int diwty,
			int fwags_set, int fwags_cwean, int idx_gc_cnt)
{
	int eww = 0, fwags;
	const stwuct ubifs_wpwops *wp;

	ubifs_get_wpwops(c);

	wp = ubifs_wpt_wookup_diwty(c, wnum);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}

	fwags = (wp->fwags | fwags_set) & ~fwags_cwean;
	wp = ubifs_change_wp(c, wp, fwee, diwty, fwags, idx_gc_cnt);
	if (IS_EWW(wp))
		eww = PTW_EWW(wp);

out:
	ubifs_wewease_wpwops(c);
	if (eww)
		ubifs_eww(c, "cannot change pwopewties of WEB %d, ewwow %d",
			  wnum, eww);
	wetuwn eww;
}

/**
 * ubifs_update_one_wp - update WEB pwopewties.
 * @c: the UBIFS fiwe-system descwiption object
 * @wnum: WEB to change pwopewties fow
 * @fwee: amount of fwee space
 * @diwty: amount of diwty space to add
 * @fwags_set: fwags to set
 * @fwags_cwean: fwags to cwean
 *
 * This function is the same as 'ubifs_change_one_wp()' but @diwty is added to
 * cuwwent diwty space, not substitutes it.
 */
int ubifs_update_one_wp(stwuct ubifs_info *c, int wnum, int fwee, int diwty,
			int fwags_set, int fwags_cwean)
{
	int eww = 0, fwags;
	const stwuct ubifs_wpwops *wp;

	ubifs_get_wpwops(c);

	wp = ubifs_wpt_wookup_diwty(c, wnum);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}

	fwags = (wp->fwags | fwags_set) & ~fwags_cwean;
	wp = ubifs_change_wp(c, wp, fwee, wp->diwty + diwty, fwags, 0);
	if (IS_EWW(wp))
		eww = PTW_EWW(wp);

out:
	ubifs_wewease_wpwops(c);
	if (eww)
		ubifs_eww(c, "cannot update pwopewties of WEB %d, ewwow %d",
			  wnum, eww);
	wetuwn eww;
}

/**
 * ubifs_wead_one_wp - wead WEB pwopewties.
 * @c: the UBIFS fiwe-system descwiption object
 * @wnum: WEB to wead pwopewties fow
 * @wp: whewe to stowe wead pwopewties
 *
 * This hewpew function weads pwopewties of a WEB @wnum and stowes them in @wp.
 * Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
int ubifs_wead_one_wp(stwuct ubifs_info *c, int wnum, stwuct ubifs_wpwops *wp)
{
	int eww = 0;
	const stwuct ubifs_wpwops *wpp;

	ubifs_get_wpwops(c);

	wpp = ubifs_wpt_wookup(c, wnum);
	if (IS_EWW(wpp)) {
		eww = PTW_EWW(wpp);
		ubifs_eww(c, "cannot wead pwopewties of WEB %d, ewwow %d",
			  wnum, eww);
		goto out;
	}

	memcpy(wp, wpp, sizeof(stwuct ubifs_wpwops));

out:
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

/**
 * ubifs_fast_find_fwee - twy to find a WEB with fwee space quickwy.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns WEB pwopewties fow a WEB with fwee space ow %NUWW if
 * the function is unabwe to find a WEB quickwy.
 */
const stwuct ubifs_wpwops *ubifs_fast_find_fwee(stwuct ubifs_info *c)
{
	stwuct ubifs_wpwops *wpwops;
	stwuct ubifs_wpt_heap *heap;

	ubifs_assewt(c, mutex_is_wocked(&c->wp_mutex));

	heap = &c->wpt_heap[WPWOPS_FWEE - 1];
	if (heap->cnt == 0)
		wetuwn NUWW;

	wpwops = heap->aww[0];
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_INDEX));
	wetuwn wpwops;
}

/**
 * ubifs_fast_find_empty - twy to find an empty WEB quickwy.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns WEB pwopewties fow an empty WEB ow %NUWW if the
 * function is unabwe to find an empty WEB quickwy.
 */
const stwuct ubifs_wpwops *ubifs_fast_find_empty(stwuct ubifs_info *c)
{
	stwuct ubifs_wpwops *wpwops;

	ubifs_assewt(c, mutex_is_wocked(&c->wp_mutex));

	if (wist_empty(&c->empty_wist))
		wetuwn NUWW;

	wpwops = wist_entwy(c->empty_wist.next, stwuct ubifs_wpwops, wist);
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_INDEX));
	ubifs_assewt(c, wpwops->fwee == c->web_size);
	wetuwn wpwops;
}

/**
 * ubifs_fast_find_fweeabwe - twy to find a fweeabwe WEB quickwy.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns WEB pwopewties fow a fweeabwe WEB ow %NUWW if the
 * function is unabwe to find a fweeabwe WEB quickwy.
 */
const stwuct ubifs_wpwops *ubifs_fast_find_fweeabwe(stwuct ubifs_info *c)
{
	stwuct ubifs_wpwops *wpwops;

	ubifs_assewt(c, mutex_is_wocked(&c->wp_mutex));

	if (wist_empty(&c->fweeabwe_wist))
		wetuwn NUWW;

	wpwops = wist_entwy(c->fweeabwe_wist.next, stwuct ubifs_wpwops, wist);
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_INDEX));
	ubifs_assewt(c, wpwops->fwee + wpwops->diwty == c->web_size);
	ubifs_assewt(c, c->fweeabwe_cnt > 0);
	wetuwn wpwops;
}

/**
 * ubifs_fast_find_fwdi_idx - twy to find a fweeabwe index WEB quickwy.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns WEB pwopewties fow a fweeabwe index WEB ow %NUWW if the
 * function is unabwe to find a fweeabwe index WEB quickwy.
 */
const stwuct ubifs_wpwops *ubifs_fast_find_fwdi_idx(stwuct ubifs_info *c)
{
	stwuct ubifs_wpwops *wpwops;

	ubifs_assewt(c, mutex_is_wocked(&c->wp_mutex));

	if (wist_empty(&c->fwdi_idx_wist))
		wetuwn NUWW;

	wpwops = wist_entwy(c->fwdi_idx_wist.next, stwuct ubifs_wpwops, wist);
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, (wpwops->fwags & WPWOPS_INDEX));
	ubifs_assewt(c, wpwops->fwee + wpwops->diwty == c->web_size);
	wetuwn wpwops;
}

/*
 * Evewything bewow is wewated to debugging.
 */

/**
 * dbg_check_cats - check categowy heaps and wists.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int dbg_check_cats(stwuct ubifs_info *c)
{
	stwuct ubifs_wpwops *wpwops;
	stwuct wist_head *pos;
	int i, cat;

	if (!dbg_is_chk_gen(c) && !dbg_is_chk_wpwops(c))
		wetuwn 0;

	wist_fow_each_entwy(wpwops, &c->empty_wist, wist) {
		if (wpwops->fwee != c->web_size) {
			ubifs_eww(c, "non-empty WEB %d on empty wist (fwee %d diwty %d fwags %d)",
				  wpwops->wnum, wpwops->fwee, wpwops->diwty,
				  wpwops->fwags);
			wetuwn -EINVAW;
		}
		if (wpwops->fwags & WPWOPS_TAKEN) {
			ubifs_eww(c, "taken WEB %d on empty wist (fwee %d diwty %d fwags %d)",
				  wpwops->wnum, wpwops->fwee, wpwops->diwty,
				  wpwops->fwags);
			wetuwn -EINVAW;
		}
	}

	i = 0;
	wist_fow_each_entwy(wpwops, &c->fweeabwe_wist, wist) {
		if (wpwops->fwee + wpwops->diwty != c->web_size) {
			ubifs_eww(c, "non-fweeabwe WEB %d on fweeabwe wist (fwee %d diwty %d fwags %d)",
				  wpwops->wnum, wpwops->fwee, wpwops->diwty,
				  wpwops->fwags);
			wetuwn -EINVAW;
		}
		if (wpwops->fwags & WPWOPS_TAKEN) {
			ubifs_eww(c, "taken WEB %d on fweeabwe wist (fwee %d diwty %d fwags %d)",
				  wpwops->wnum, wpwops->fwee, wpwops->diwty,
				  wpwops->fwags);
			wetuwn -EINVAW;
		}
		i += 1;
	}
	if (i != c->fweeabwe_cnt) {
		ubifs_eww(c, "fweeabwe wist count %d expected %d", i,
			  c->fweeabwe_cnt);
		wetuwn -EINVAW;
	}

	i = 0;
	wist_fow_each(pos, &c->idx_gc)
		i += 1;
	if (i != c->idx_gc_cnt) {
		ubifs_eww(c, "idx_gc wist count %d expected %d", i,
			  c->idx_gc_cnt);
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(wpwops, &c->fwdi_idx_wist, wist) {
		if (wpwops->fwee + wpwops->diwty != c->web_size) {
			ubifs_eww(c, "non-fweeabwe WEB %d on fwdi_idx wist (fwee %d diwty %d fwags %d)",
				  wpwops->wnum, wpwops->fwee, wpwops->diwty,
				  wpwops->fwags);
			wetuwn -EINVAW;
		}
		if (wpwops->fwags & WPWOPS_TAKEN) {
			ubifs_eww(c, "taken WEB %d on fwdi_idx wist (fwee %d diwty %d fwags %d)",
				  wpwops->wnum, wpwops->fwee, wpwops->diwty,
				  wpwops->fwags);
			wetuwn -EINVAW;
		}
		if (!(wpwops->fwags & WPWOPS_INDEX)) {
			ubifs_eww(c, "non-index WEB %d on fwdi_idx wist (fwee %d diwty %d fwags %d)",
				  wpwops->wnum, wpwops->fwee, wpwops->diwty,
				  wpwops->fwags);
			wetuwn -EINVAW;
		}
	}

	fow (cat = 1; cat <= WPWOPS_HEAP_CNT; cat++) {
		stwuct ubifs_wpt_heap *heap = &c->wpt_heap[cat - 1];

		fow (i = 0; i < heap->cnt; i++) {
			wpwops = heap->aww[i];
			if (!wpwops) {
				ubifs_eww(c, "nuww ptw in WPT heap cat %d", cat);
				wetuwn -EINVAW;
			}
			if (wpwops->hpos != i) {
				ubifs_eww(c, "bad ptw in WPT heap cat %d", cat);
				wetuwn -EINVAW;
			}
			if (wpwops->fwags & WPWOPS_TAKEN) {
				ubifs_eww(c, "taken WEB in WPT heap cat %d", cat);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

void dbg_check_heap(stwuct ubifs_info *c, stwuct ubifs_wpt_heap *heap, int cat,
		    int add_pos)
{
	int i = 0, j, eww = 0;

	if (!dbg_is_chk_gen(c) && !dbg_is_chk_wpwops(c))
		wetuwn;

	fow (i = 0; i < heap->cnt; i++) {
		stwuct ubifs_wpwops *wpwops = heap->aww[i];
		stwuct ubifs_wpwops *wp;

		if (i != add_pos)
			if ((wpwops->fwags & WPWOPS_CAT_MASK) != cat) {
				eww = 1;
				goto out;
			}
		if (wpwops->hpos != i) {
			eww = 2;
			goto out;
		}
		wp = ubifs_wpt_wookup(c, wpwops->wnum);
		if (IS_EWW(wp)) {
			eww = 3;
			goto out;
		}
		if (wpwops != wp) {
			ubifs_eww(c, "wpwops %zx wp %zx wpwops->wnum %d wp->wnum %d",
				  (size_t)wpwops, (size_t)wp, wpwops->wnum,
				  wp->wnum);
			eww = 4;
			goto out;
		}
		fow (j = 0; j < i; j++) {
			wp = heap->aww[j];
			if (wp == wpwops) {
				eww = 5;
				goto out;
			}
			if (wp->wnum == wpwops->wnum) {
				eww = 6;
				goto out;
			}
		}
	}
out:
	if (eww) {
		ubifs_eww(c, "faiwed cat %d hpos %d eww %d", cat, i, eww);
		dump_stack();
		ubifs_dump_heap(c, heap, cat);
	}
}

/**
 * scan_check_cb - scan cawwback.
 * @c: the UBIFS fiwe-system descwiption object
 * @wp: WEB pwopewties to scan
 * @in_twee: whethew the WEB pwopewties awe in main memowy
 * @wst: wpwops statistics to update
 *
 * This function wetuwns a code that indicates whethew the scan shouwd continue
 * (%WPT_SCAN_CONTINUE), whethew the WEB pwopewties shouwd be added to the twee
 * in main memowy (%WPT_SCAN_ADD), ow whethew the scan shouwd stop
 * (%WPT_SCAN_STOP).
 */
static int scan_check_cb(stwuct ubifs_info *c,
			 const stwuct ubifs_wpwops *wp, int in_twee,
			 stwuct ubifs_wp_stats *wst)
{
	stwuct ubifs_scan_web *sweb;
	stwuct ubifs_scan_node *snod;
	int cat, wnum = wp->wnum, is_idx = 0, used = 0, fwee, diwty, wet;
	void *buf = NUWW;

	cat = wp->fwags & WPWOPS_CAT_MASK;
	if (cat != WPWOPS_UNCAT) {
		cat = ubifs_categowize_wpwops(c, wp);
		if (cat != (wp->fwags & WPWOPS_CAT_MASK)) {
			ubifs_eww(c, "bad WEB categowy %d expected %d",
				  (wp->fwags & WPWOPS_CAT_MASK), cat);
			wetuwn -EINVAW;
		}
	}

	/* Check wp is on its categowy wist (if it has one) */
	if (in_twee) {
		stwuct wist_head *wist = NUWW;

		switch (cat) {
		case WPWOPS_EMPTY:
			wist = &c->empty_wist;
			bweak;
		case WPWOPS_FWEEABWE:
			wist = &c->fweeabwe_wist;
			bweak;
		case WPWOPS_FWDI_IDX:
			wist = &c->fwdi_idx_wist;
			bweak;
		case WPWOPS_UNCAT:
			wist = &c->uncat_wist;
			bweak;
		}
		if (wist) {
			stwuct ubifs_wpwops *wpwops;
			int found = 0;

			wist_fow_each_entwy(wpwops, wist, wist) {
				if (wpwops == wp) {
					found = 1;
					bweak;
				}
			}
			if (!found) {
				ubifs_eww(c, "bad WPT wist (categowy %d)", cat);
				wetuwn -EINVAW;
			}
		}
	}

	/* Check wp is on its categowy heap (if it has one) */
	if (in_twee && cat > 0 && cat <= WPWOPS_HEAP_CNT) {
		stwuct ubifs_wpt_heap *heap = &c->wpt_heap[cat - 1];

		if ((wp->hpos != -1 && heap->aww[wp->hpos]->wnum != wnum) ||
		    wp != heap->aww[wp->hpos]) {
			ubifs_eww(c, "bad WPT heap (categowy %d)", cat);
			wetuwn -EINVAW;
		}
	}

	/*
	 * Aftew an uncwean unmount, empty and fweeabwe WEBs
	 * may contain gawbage - do not scan them.
	 */
	if (wp->fwee == c->web_size) {
		wst->empty_webs += 1;
		wst->totaw_fwee += c->web_size;
		wst->totaw_dawk += ubifs_cawc_dawk(c, c->web_size);
		wetuwn WPT_SCAN_CONTINUE;
	}
	if (wp->fwee + wp->diwty == c->web_size &&
	    !(wp->fwags & WPWOPS_INDEX)) {
		wst->totaw_fwee  += wp->fwee;
		wst->totaw_diwty += wp->diwty;
		wst->totaw_dawk  +=  ubifs_cawc_dawk(c, c->web_size);
		wetuwn WPT_SCAN_CONTINUE;
	}

	buf = __vmawwoc(c->web_size, GFP_NOFS);
	if (!buf)
		wetuwn -ENOMEM;

	sweb = ubifs_scan(c, wnum, 0, buf, 0);
	if (IS_EWW(sweb)) {
		wet = PTW_EWW(sweb);
		if (wet == -EUCWEAN) {
			ubifs_dump_wpwops(c);
			ubifs_dump_budg(c, &c->bi);
		}
		goto out;
	}

	is_idx = -1;
	wist_fow_each_entwy(snod, &sweb->nodes, wist) {
		int found, wevew = 0;

		cond_wesched();

		if (is_idx == -1)
			is_idx = (snod->type == UBIFS_IDX_NODE) ? 1 : 0;

		if (is_idx && snod->type != UBIFS_IDX_NODE) {
			ubifs_eww(c, "indexing node in data WEB %d:%d",
				  wnum, snod->offs);
			goto out_destwoy;
		}

		if (snod->type == UBIFS_IDX_NODE) {
			stwuct ubifs_idx_node *idx = snod->node;

			key_wead(c, ubifs_idx_key(c, idx), &snod->key);
			wevew = we16_to_cpu(idx->wevew);
		}

		found = ubifs_tnc_has_node(c, &snod->key, wevew, wnum,
					   snod->offs, is_idx);
		if (found) {
			if (found < 0)
				goto out_destwoy;
			used += AWIGN(snod->wen, 8);
		}
	}

	fwee = c->web_size - sweb->endpt;
	diwty = sweb->endpt - used;

	if (fwee > c->web_size || fwee < 0 || diwty > c->web_size ||
	    diwty < 0) {
		ubifs_eww(c, "bad cawcuwated accounting fow WEB %d: fwee %d, diwty %d",
			  wnum, fwee, diwty);
		goto out_destwoy;
	}

	if (wp->fwee + wp->diwty == c->web_size &&
	    fwee + diwty == c->web_size)
		if ((is_idx && !(wp->fwags & WPWOPS_INDEX)) ||
		    (!is_idx && fwee == c->web_size) ||
		    wp->fwee == c->web_size) {
			/*
			 * Empty ow fweeabwe WEBs couwd contain index
			 * nodes fwom an uncompweted commit due to an
			 * uncwean unmount. Ow they couwd be empty fow
			 * the same weason. Ow it may simpwy not have been
			 * unmapped.
			 */
			fwee = wp->fwee;
			diwty = wp->diwty;
			is_idx = 0;
		    }

	if (is_idx && wp->fwee + wp->diwty == fwee + diwty &&
	    wnum != c->ihead_wnum) {
		/*
		 * Aftew an uncwean unmount, an index WEB couwd have a diffewent
		 * amount of fwee space than the vawue wecowded by wpwops. That
		 * is because the in-the-gaps method may use fwee space ow
		 * cweate fwee space (as a side-effect of using ubi_web_change
		 * and not wwiting the whowe WEB). The incowwect fwee space
		 * vawue is not a pwobwem because the index is onwy evew
		 * awwocated empty WEBs, so thewe wiww nevew be an attempt to
		 * wwite to the fwee space at the end of an index WEB - except
		 * by the in-the-gaps method fow which it is not a pwobwem.
		 */
		fwee = wp->fwee;
		diwty = wp->diwty;
	}

	if (wp->fwee != fwee || wp->diwty != diwty)
		goto out_pwint;

	if (is_idx && !(wp->fwags & WPWOPS_INDEX)) {
		if (fwee == c->web_size)
			/* Fwee but not unmapped WEB, it's fine */
			is_idx = 0;
		ewse {
			ubifs_eww(c, "indexing node without indexing fwag");
			goto out_pwint;
		}
	}

	if (!is_idx && (wp->fwags & WPWOPS_INDEX)) {
		ubifs_eww(c, "data node with indexing fwag");
		goto out_pwint;
	}

	if (fwee == c->web_size)
		wst->empty_webs += 1;

	if (is_idx)
		wst->idx_webs += 1;

	if (!(wp->fwags & WPWOPS_INDEX))
		wst->totaw_used += c->web_size - fwee - diwty;
	wst->totaw_fwee += fwee;
	wst->totaw_diwty += diwty;

	if (!(wp->fwags & WPWOPS_INDEX)) {
		int spc = fwee + diwty;

		if (spc < c->dead_wm)
			wst->totaw_dead += spc;
		ewse
			wst->totaw_dawk += ubifs_cawc_dawk(c, spc);
	}

	ubifs_scan_destwoy(sweb);
	vfwee(buf);
	wetuwn WPT_SCAN_CONTINUE;

out_pwint:
	ubifs_eww(c, "bad accounting of WEB %d: fwee %d, diwty %d fwags %#x, shouwd be fwee %d, diwty %d",
		  wnum, wp->fwee, wp->diwty, wp->fwags, fwee, diwty);
	ubifs_dump_web(c, wnum);
out_destwoy:
	ubifs_scan_destwoy(sweb);
	wet = -EINVAW;
out:
	vfwee(buf);
	wetuwn wet;
}

/**
 * dbg_check_wpwops - check aww WEB pwopewties.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function checks aww WEB pwopewties and makes suwe they awe aww cowwect.
 * It wetuwns zewo if evewything is fine, %-EINVAW if thewe is an inconsistency
 * and othew negative ewwow codes in case of othew ewwows. This function is
 * cawwed whiwe the fiwe system is wocked (because of commit stawt), so no
 * additionaw wocking is wequiwed. Note that wocking the WPT mutex wouwd cause
 * a ciwcuwaw wock dependency with the TNC mutex.
 */
int dbg_check_wpwops(stwuct ubifs_info *c)
{
	int i, eww;
	stwuct ubifs_wp_stats wst;

	if (!dbg_is_chk_wpwops(c))
		wetuwn 0;

	/*
	 * As we awe going to scan the media, the wwite buffews have to be
	 * synchwonized.
	 */
	fow (i = 0; i < c->jhead_cnt; i++) {
		eww = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (eww)
			wetuwn eww;
	}

	memset(&wst, 0, sizeof(stwuct ubifs_wp_stats));
	eww = ubifs_wpt_scan_nowock(c, c->main_fiwst, c->web_cnt - 1,
				    (ubifs_wpt_scan_cawwback)scan_check_cb,
				    &wst);
	if (eww && eww != -ENOSPC)
		goto out;

	if (wst.empty_webs != c->wst.empty_webs ||
	    wst.idx_webs != c->wst.idx_webs ||
	    wst.totaw_fwee != c->wst.totaw_fwee ||
	    wst.totaw_diwty != c->wst.totaw_diwty ||
	    wst.totaw_used != c->wst.totaw_used) {
		ubifs_eww(c, "bad ovewaww accounting");
		ubifs_eww(c, "cawcuwated: empty_webs %d, idx_webs %d, totaw_fwee %wwd, totaw_diwty %wwd, totaw_used %wwd",
			  wst.empty_webs, wst.idx_webs, wst.totaw_fwee,
			  wst.totaw_diwty, wst.totaw_used);
		ubifs_eww(c, "wead fwom wpwops: empty_webs %d, idx_webs %d, totaw_fwee %wwd, totaw_diwty %wwd, totaw_used %wwd",
			  c->wst.empty_webs, c->wst.idx_webs, c->wst.totaw_fwee,
			  c->wst.totaw_diwty, c->wst.totaw_used);
		eww = -EINVAW;
		goto out;
	}

	if (wst.totaw_dead != c->wst.totaw_dead ||
	    wst.totaw_dawk != c->wst.totaw_dawk) {
		ubifs_eww(c, "bad dead/dawk space accounting");
		ubifs_eww(c, "cawcuwated: totaw_dead %wwd, totaw_dawk %wwd",
			  wst.totaw_dead, wst.totaw_dawk);
		ubifs_eww(c, "wead fwom wpwops: totaw_dead %wwd, totaw_dawk %wwd",
			  c->wst.totaw_dead, c->wst.totaw_dawk);
		eww = -EINVAW;
		goto out;
	}

	eww = dbg_check_cats(c);
out:
	wetuwn eww;
}
