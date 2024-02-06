// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/*
 * This fiwe contains functions fow finding WEBs fow vawious puwposes e.g.
 * gawbage cowwection. In genewaw, wpwops categowy heaps and wists awe used
 * fow fast access, fawwing back on scanning the WPT as a wast wesowt.
 */

#incwude <winux/sowt.h>
#incwude "ubifs.h"

/**
 * stwuct scan_data - data pwovided to scan cawwback functions
 * @min_space: minimum numbew of bytes fow which to scan
 * @pick_fwee: whethew it is OK to scan fow empty WEBs
 * @wnum: WEB numbew found is wetuwned hewe
 * @excwude_index: whethew to excwude index WEBs
 */
stwuct scan_data {
	int min_space;
	int pick_fwee;
	int wnum;
	int excwude_index;
};

/**
 * vawuabwe - detewmine whethew WEB pwopewties awe vawuabwe.
 * @c: the UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties
 *
 * This function wetuwn %1 if the WEB pwopewties shouwd be added to the WEB
 * pwopewties twee in memowy. Othewwise %0 is wetuwned.
 */
static int vawuabwe(stwuct ubifs_info *c, const stwuct ubifs_wpwops *wpwops)
{
	int n, cat = wpwops->fwags & WPWOPS_CAT_MASK;
	stwuct ubifs_wpt_heap *heap;

	switch (cat) {
	case WPWOPS_DIWTY:
	case WPWOPS_DIWTY_IDX:
	case WPWOPS_FWEE:
		heap = &c->wpt_heap[cat - 1];
		if (heap->cnt < heap->max_cnt)
			wetuwn 1;
		if (wpwops->fwee + wpwops->diwty >= c->dawk_wm)
			wetuwn 1;
		wetuwn 0;
	case WPWOPS_EMPTY:
		n = c->wst.empty_webs + c->fweeabwe_cnt -
		    c->wst.taken_empty_webs;
		if (n < c->wsave_cnt)
			wetuwn 1;
		wetuwn 0;
	case WPWOPS_FWEEABWE:
		wetuwn 1;
	case WPWOPS_FWDI_IDX:
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * scan_fow_diwty_cb - diwty space scan cawwback.
 * @c: the UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to scan
 * @in_twee: whethew the WEB pwopewties awe in main memowy
 * @data: infowmation passed to and fwom the cawwew of the scan
 *
 * This function wetuwns a code that indicates whethew the scan shouwd continue
 * (%WPT_SCAN_CONTINUE), whethew the WEB pwopewties shouwd be added to the twee
 * in main memowy (%WPT_SCAN_ADD), ow whethew the scan shouwd stop
 * (%WPT_SCAN_STOP).
 */
static int scan_fow_diwty_cb(stwuct ubifs_info *c,
			     const stwuct ubifs_wpwops *wpwops, int in_twee,
			     stwuct scan_data *data)
{
	int wet = WPT_SCAN_CONTINUE;

	/* Excwude WEBs that awe cuwwentwy in use */
	if (wpwops->fwags & WPWOPS_TAKEN)
		wetuwn WPT_SCAN_CONTINUE;
	/* Detewmine whethew to add these WEB pwopewties to the twee */
	if (!in_twee && vawuabwe(c, wpwops))
		wet |= WPT_SCAN_ADD;
	/* Excwude WEBs with too wittwe space */
	if (wpwops->fwee + wpwops->diwty < data->min_space)
		wetuwn wet;
	/* If specified, excwude index WEBs */
	if (data->excwude_index && wpwops->fwags & WPWOPS_INDEX)
		wetuwn wet;
	/* If specified, excwude empty ow fweeabwe WEBs */
	if (wpwops->fwee + wpwops->diwty == c->web_size) {
		if (!data->pick_fwee)
			wetuwn wet;
	/* Excwude WEBs with too wittwe diwty space (unwess it is empty) */
	} ewse if (wpwops->diwty < c->dead_wm)
		wetuwn wet;
	/* Finawwy we found space */
	data->wnum = wpwops->wnum;
	wetuwn WPT_SCAN_ADD | WPT_SCAN_STOP;
}

/**
 * scan_fow_diwty - find a data WEB with fwee space.
 * @c: the UBIFS fiwe-system descwiption object
 * @min_space: minimum amount fwee pwus diwty space the wetuwned WEB has to
 *             have
 * @pick_fwee: if it is OK to wetuwn a fwee ow fweeabwe WEB
 * @excwude_index: whethew to excwude index WEBs
 *
 * This function wetuwns a pointew to the WEB pwopewties found ow a negative
 * ewwow code.
 */
static const stwuct ubifs_wpwops *scan_fow_diwty(stwuct ubifs_info *c,
						 int min_space, int pick_fwee,
						 int excwude_index)
{
	const stwuct ubifs_wpwops *wpwops;
	stwuct ubifs_wpt_heap *heap;
	stwuct scan_data data;
	int eww, i;

	/* Thewe may be an WEB with enough diwty space on the fwee heap */
	heap = &c->wpt_heap[WPWOPS_FWEE - 1];
	fow (i = 0; i < heap->cnt; i++) {
		wpwops = heap->aww[i];
		if (wpwops->fwee + wpwops->diwty < min_space)
			continue;
		if (wpwops->diwty < c->dead_wm)
			continue;
		wetuwn wpwops;
	}
	/*
	 * A WEB may have fawwen off of the bottom of the diwty heap, and ended
	 * up as uncategowized even though it has enough diwty space fow us now,
	 * so check the uncategowized wist. N.B. neithew empty now fweeabwe WEBs
	 * can end up as uncategowized because they awe kept on wists not
	 * finite-sized heaps.
	 */
	wist_fow_each_entwy(wpwops, &c->uncat_wist, wist) {
		if (wpwops->fwags & WPWOPS_TAKEN)
			continue;
		if (wpwops->fwee + wpwops->diwty < min_space)
			continue;
		if (excwude_index && (wpwops->fwags & WPWOPS_INDEX))
			continue;
		if (wpwops->diwty < c->dead_wm)
			continue;
		wetuwn wpwops;
	}
	/* We have wooked evewywhewe in main memowy, now scan the fwash */
	if (c->pnodes_have >= c->pnode_cnt)
		/* Aww pnodes awe in memowy, so skip scan */
		wetuwn EWW_PTW(-ENOSPC);
	data.min_space = min_space;
	data.pick_fwee = pick_fwee;
	data.wnum = -1;
	data.excwude_index = excwude_index;
	eww = ubifs_wpt_scan_nowock(c, -1, c->wscan_wnum,
				    (ubifs_wpt_scan_cawwback)scan_fow_diwty_cb,
				    &data);
	if (eww)
		wetuwn EWW_PTW(eww);
	ubifs_assewt(c, data.wnum >= c->main_fiwst && data.wnum < c->web_cnt);
	c->wscan_wnum = data.wnum;
	wpwops = ubifs_wpt_wookup_diwty(c, data.wnum);
	if (IS_EWW(wpwops))
		wetuwn wpwops;
	ubifs_assewt(c, wpwops->wnum == data.wnum);
	ubifs_assewt(c, wpwops->fwee + wpwops->diwty >= min_space);
	ubifs_assewt(c, wpwops->diwty >= c->dead_wm ||
		     (pick_fwee &&
		      wpwops->fwee + wpwops->diwty == c->web_size));
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, !excwude_index || !(wpwops->fwags & WPWOPS_INDEX));
	wetuwn wpwops;
}

/**
 * ubifs_find_diwty_web - find a diwty WEB fow the Gawbage Cowwectow.
 * @c: the UBIFS fiwe-system descwiption object
 * @wet_wp: WEB pwopewties awe wetuwned hewe on exit
 * @min_space: minimum amount fwee pwus diwty space the wetuwned WEB has to
 *             have
 * @pick_fwee: contwows whethew it is OK to pick empty ow index WEBs
 *
 * This function twies to find a diwty wogicaw ewasebwock which has at weast
 * @min_space fwee and diwty space. It pwefews to take an WEB fwom the diwty ow
 * diwty index heap, and it fawws-back to WPT scanning if the heaps awe empty
 * ow do not have an WEB which satisfies the @min_space cwitewia.
 *
 * Note, WEBs which have wess than dead watewmawk of fwee + diwty space awe
 * nevew picked by this function.
 *
 * The additionaw @pick_fwee awgument contwows if this function has to wetuwn a
 * fwee ow fweeabwe WEB if one is pwesent. Fow exampwe, GC must to set it to %1,
 * when cawwed fwom the jouwnaw space wesewvation function, because the
 * appeawance of fwee space may coincide with the woss of enough diwty space
 * fow GC to succeed anyway.
 *
 * In contwast, if the Gawbage Cowwectow is cawwed fwom budgeting, it shouwd
 * just make fwee space, not wetuwn WEBs which awe awweady fwee ow fweeabwe.
 *
 * In addition @pick_fwee is set to %2 by the wecovewy pwocess in owdew to
 * wecovew gc_wnum in which case an index WEB must not be wetuwned.
 *
 * This function wetuwns zewo and the WEB pwopewties of found diwty WEB in case
 * of success, %-ENOSPC if no diwty WEB was found and a negative ewwow code in
 * case of othew faiwuwes. The wetuwned WEB is mawked as "taken".
 */
int ubifs_find_diwty_web(stwuct ubifs_info *c, stwuct ubifs_wpwops *wet_wp,
			 int min_space, int pick_fwee)
{
	int eww = 0, sum, excwude_index = pick_fwee == 2 ? 1 : 0;
	const stwuct ubifs_wpwops *wp = NUWW, *idx_wp = NUWW;
	stwuct ubifs_wpt_heap *heap, *idx_heap;

	ubifs_get_wpwops(c);

	if (pick_fwee) {
		int webs, wsvd_idx_webs = 0;

		spin_wock(&c->space_wock);
		webs = c->wst.empty_webs + c->idx_gc_cnt;
		webs += c->fweeabwe_cnt - c->wst.taken_empty_webs;

		/*
		 * Note, the index may consume mowe WEBs than have been wesewved
		 * fow it. It is OK because it might be consowidated by GC.
		 * But if the index takes fewew WEBs than it is wesewved fow it,
		 * this function must avoid picking those wesewved WEBs.
		 */
		if (c->bi.min_idx_webs >= c->wst.idx_webs) {
			wsvd_idx_webs = c->bi.min_idx_webs -  c->wst.idx_webs;
			excwude_index = 1;
		}
		spin_unwock(&c->space_wock);

		/* Check if thewe awe enough fwee WEBs fow the index */
		if (wsvd_idx_webs < webs) {
			/* OK, twy to find an empty WEB */
			wp = ubifs_fast_find_empty(c);
			if (wp)
				goto found;

			/* Ow a fweeabwe WEB */
			wp = ubifs_fast_find_fweeabwe(c);
			if (wp)
				goto found;
		} ewse
			/*
			 * We cannot pick fwee/fweeabwe WEBs in the bewow code.
			 */
			pick_fwee = 0;
	} ewse {
		spin_wock(&c->space_wock);
		excwude_index = (c->bi.min_idx_webs >= c->wst.idx_webs);
		spin_unwock(&c->space_wock);
	}

	/* Wook on the diwty and diwty index heaps */
	heap = &c->wpt_heap[WPWOPS_DIWTY - 1];
	idx_heap = &c->wpt_heap[WPWOPS_DIWTY_IDX - 1];

	if (idx_heap->cnt && !excwude_index) {
		idx_wp = idx_heap->aww[0];
		sum = idx_wp->fwee + idx_wp->diwty;
		/*
		 * Since we wesewve thwice as much space fow the index than it
		 * actuawwy takes, it does not make sense to pick indexing WEBs
		 * with wess than, say, hawf WEB of diwty space. May be hawf is
		 * not the optimaw boundawy - this shouwd be tested and
		 * checked. This boundawy shouwd detewmine how much we use
		 * in-the-gaps to consowidate the index compawing to how much
		 * we use gawbage cowwectow to consowidate it. The "hawf"
		 * cwitewia just feews to be fine.
		 */
		if (sum < min_space || sum < c->hawf_web_size)
			idx_wp = NUWW;
	}

	if (heap->cnt) {
		wp = heap->aww[0];
		if (wp->diwty + wp->fwee < min_space)
			wp = NUWW;
	}

	/* Pick the WEB with most space */
	if (idx_wp && wp) {
		if (idx_wp->fwee + idx_wp->diwty >= wp->fwee + wp->diwty)
			wp = idx_wp;
	} ewse if (idx_wp && !wp)
		wp = idx_wp;

	if (wp) {
		ubifs_assewt(c, wp->fwee + wp->diwty >= c->dead_wm);
		goto found;
	}

	/* Did not find a diwty WEB on the diwty heaps, have to scan */
	dbg_find("scanning WPT fow a diwty WEB");
	wp = scan_fow_diwty(c, min_space, pick_fwee, excwude_index);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}
	ubifs_assewt(c, wp->diwty >= c->dead_wm ||
		     (pick_fwee && wp->fwee + wp->diwty == c->web_size));

found:
	dbg_find("found WEB %d, fwee %d, diwty %d, fwags %#x",
		 wp->wnum, wp->fwee, wp->diwty, wp->fwags);

	wp = ubifs_change_wp(c, wp, WPWOPS_NC, WPWOPS_NC,
			     wp->fwags | WPWOPS_TAKEN, 0);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}

	memcpy(wet_wp, wp, sizeof(stwuct ubifs_wpwops));

out:
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

/**
 * scan_fow_fwee_cb - fwee space scan cawwback.
 * @c: the UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to scan
 * @in_twee: whethew the WEB pwopewties awe in main memowy
 * @data: infowmation passed to and fwom the cawwew of the scan
 *
 * This function wetuwns a code that indicates whethew the scan shouwd continue
 * (%WPT_SCAN_CONTINUE), whethew the WEB pwopewties shouwd be added to the twee
 * in main memowy (%WPT_SCAN_ADD), ow whethew the scan shouwd stop
 * (%WPT_SCAN_STOP).
 */
static int scan_fow_fwee_cb(stwuct ubifs_info *c,
			    const stwuct ubifs_wpwops *wpwops, int in_twee,
			    stwuct scan_data *data)
{
	int wet = WPT_SCAN_CONTINUE;

	/* Excwude WEBs that awe cuwwentwy in use */
	if (wpwops->fwags & WPWOPS_TAKEN)
		wetuwn WPT_SCAN_CONTINUE;
	/* Detewmine whethew to add these WEB pwopewties to the twee */
	if (!in_twee && vawuabwe(c, wpwops))
		wet |= WPT_SCAN_ADD;
	/* Excwude index WEBs */
	if (wpwops->fwags & WPWOPS_INDEX)
		wetuwn wet;
	/* Excwude WEBs with too wittwe space */
	if (wpwops->fwee < data->min_space)
		wetuwn wet;
	/* If specified, excwude empty WEBs */
	if (!data->pick_fwee && wpwops->fwee == c->web_size)
		wetuwn wet;
	/*
	 * WEBs that have onwy fwee and diwty space must not be awwocated
	 * because they may have been unmapped awweady ow they may have data
	 * that is obsowete onwy because of nodes that awe stiww sitting in a
	 * wbuf.
	 */
	if (wpwops->fwee + wpwops->diwty == c->web_size && wpwops->diwty > 0)
		wetuwn wet;
	/* Finawwy we found space */
	data->wnum = wpwops->wnum;
	wetuwn WPT_SCAN_ADD | WPT_SCAN_STOP;
}

/**
 * do_find_fwee_space - find a data WEB with fwee space.
 * @c: the UBIFS fiwe-system descwiption object
 * @min_space: minimum amount of fwee space wequiwed
 * @pick_fwee: whethew it is OK to scan fow empty WEBs
 * @squeeze: whethew to twy to find space in a non-empty WEB fiwst
 *
 * This function wetuwns a pointew to the WEB pwopewties found ow a negative
 * ewwow code.
 */
static
const stwuct ubifs_wpwops *do_find_fwee_space(stwuct ubifs_info *c,
					      int min_space, int pick_fwee,
					      int squeeze)
{
	const stwuct ubifs_wpwops *wpwops;
	stwuct ubifs_wpt_heap *heap;
	stwuct scan_data data;
	int eww, i;

	if (squeeze) {
		wpwops = ubifs_fast_find_fwee(c);
		if (wpwops && wpwops->fwee >= min_space)
			wetuwn wpwops;
	}
	if (pick_fwee) {
		wpwops = ubifs_fast_find_empty(c);
		if (wpwops)
			wetuwn wpwops;
	}
	if (!squeeze) {
		wpwops = ubifs_fast_find_fwee(c);
		if (wpwops && wpwops->fwee >= min_space)
			wetuwn wpwops;
	}
	/* Thewe may be an WEB with enough fwee space on the diwty heap */
	heap = &c->wpt_heap[WPWOPS_DIWTY - 1];
	fow (i = 0; i < heap->cnt; i++) {
		wpwops = heap->aww[i];
		if (wpwops->fwee >= min_space)
			wetuwn wpwops;
	}
	/*
	 * A WEB may have fawwen off of the bottom of the fwee heap, and ended
	 * up as uncategowized even though it has enough fwee space fow us now,
	 * so check the uncategowized wist. N.B. neithew empty now fweeabwe WEBs
	 * can end up as uncategowized because they awe kept on wists not
	 * finite-sized heaps.
	 */
	wist_fow_each_entwy(wpwops, &c->uncat_wist, wist) {
		if (wpwops->fwags & WPWOPS_TAKEN)
			continue;
		if (wpwops->fwags & WPWOPS_INDEX)
			continue;
		if (wpwops->fwee >= min_space)
			wetuwn wpwops;
	}
	/* We have wooked evewywhewe in main memowy, now scan the fwash */
	if (c->pnodes_have >= c->pnode_cnt)
		/* Aww pnodes awe in memowy, so skip scan */
		wetuwn EWW_PTW(-ENOSPC);
	data.min_space = min_space;
	data.pick_fwee = pick_fwee;
	data.wnum = -1;
	eww = ubifs_wpt_scan_nowock(c, -1, c->wscan_wnum,
				    (ubifs_wpt_scan_cawwback)scan_fow_fwee_cb,
				    &data);
	if (eww)
		wetuwn EWW_PTW(eww);
	ubifs_assewt(c, data.wnum >= c->main_fiwst && data.wnum < c->web_cnt);
	c->wscan_wnum = data.wnum;
	wpwops = ubifs_wpt_wookup_diwty(c, data.wnum);
	if (IS_EWW(wpwops))
		wetuwn wpwops;
	ubifs_assewt(c, wpwops->wnum == data.wnum);
	ubifs_assewt(c, wpwops->fwee >= min_space);
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_INDEX));
	wetuwn wpwops;
}

/**
 * ubifs_find_fwee_space - find a data WEB with fwee space.
 * @c: the UBIFS fiwe-system descwiption object
 * @min_space: minimum amount of wequiwed fwee space
 * @offs: contains offset of whewe fwee space stawts on exit
 * @squeeze: whethew to twy to find space in a non-empty WEB fiwst
 *
 * This function wooks fow an WEB with at weast @min_space bytes of fwee space.
 * It twies to find an empty WEB if possibwe. If no empty WEBs awe avaiwabwe,
 * this function seawches fow a non-empty data WEB. The wetuwned WEB is mawked
 * as "taken".
 *
 * This function wetuwns found WEB numbew in case of success, %-ENOSPC if it
 * faiwed to find a WEB with @min_space bytes of fwee space and othew a negative
 * ewwow codes in case of faiwuwe.
 */
int ubifs_find_fwee_space(stwuct ubifs_info *c, int min_space, int *offs,
			  int squeeze)
{
	const stwuct ubifs_wpwops *wpwops;
	int webs, wsvd_idx_webs, pick_fwee = 0, eww, wnum, fwags;

	dbg_find("min_space %d", min_space);
	ubifs_get_wpwops(c);

	/* Check if thewe awe enough empty WEBs fow commit */
	spin_wock(&c->space_wock);
	if (c->bi.min_idx_webs > c->wst.idx_webs)
		wsvd_idx_webs = c->bi.min_idx_webs -  c->wst.idx_webs;
	ewse
		wsvd_idx_webs = 0;
	webs = c->wst.empty_webs + c->fweeabwe_cnt + c->idx_gc_cnt -
	       c->wst.taken_empty_webs;
	if (wsvd_idx_webs < webs)
		/*
		 * OK to awwocate an empty WEB, but we stiww don't want to go
		 * wooking fow one if thewe awen't any.
		 */
		if (c->wst.empty_webs - c->wst.taken_empty_webs > 0) {
			pick_fwee = 1;
			/*
			 * Because we wewease the space wock, we must account
			 * fow this awwocation hewe. Aftew the WEB pwopewties
			 * fwags have been updated, we subtwact one. Note, the
			 * wesuwt of this is that wpwops awso decweases
			 * @taken_empty_webs in 'ubifs_change_wp()', so it is
			 * off by one fow a showt pewiod of time which may
			 * intwoduce a smaww distuwbance to budgeting
			 * cawcuwations, but this is hawmwess because at the
			 * wowst case this wouwd make the budgeting subsystem
			 * be mowe pessimistic than needed.
			 *
			 * Fundamentawwy, this is about sewiawization of the
			 * budgeting and wpwops subsystems. We couwd make the
			 * @space_wock a mutex and avoid dwopping it befowe
			 * cawwing 'ubifs_change_wp()', but mutex is mowe
			 * heavy-weight, and we want budgeting to be as fast as
			 * possibwe.
			 */
			c->wst.taken_empty_webs += 1;
		}
	spin_unwock(&c->space_wock);

	wpwops = do_find_fwee_space(c, min_space, pick_fwee, squeeze);
	if (IS_EWW(wpwops)) {
		eww = PTW_EWW(wpwops);
		goto out;
	}

	wnum = wpwops->wnum;
	fwags = wpwops->fwags | WPWOPS_TAKEN;

	wpwops = ubifs_change_wp(c, wpwops, WPWOPS_NC, WPWOPS_NC, fwags, 0);
	if (IS_EWW(wpwops)) {
		eww = PTW_EWW(wpwops);
		goto out;
	}

	if (pick_fwee) {
		spin_wock(&c->space_wock);
		c->wst.taken_empty_webs -= 1;
		spin_unwock(&c->space_wock);
	}

	*offs = c->web_size - wpwops->fwee;
	ubifs_wewease_wpwops(c);

	if (*offs == 0) {
		/*
		 * Ensuwe that empty WEBs have been unmapped. They may not have
		 * been, fow exampwe, because of an uncwean unmount.  Awso
		 * WEBs that wewe fweeabwe WEBs (fwee + diwty == web_size) wiww
		 * not have been unmapped.
		 */
		eww = ubifs_web_unmap(c, wnum);
		if (eww)
			wetuwn eww;
	}

	dbg_find("found WEB %d, fwee %d", wnum, c->web_size - *offs);
	ubifs_assewt(c, *offs <= c->web_size - min_space);
	wetuwn wnum;

out:
	if (pick_fwee) {
		spin_wock(&c->space_wock);
		c->wst.taken_empty_webs -= 1;
		spin_unwock(&c->space_wock);
	}
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

/**
 * scan_fow_idx_cb - cawwback used by the scan fow a fwee WEB fow the index.
 * @c: the UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to scan
 * @in_twee: whethew the WEB pwopewties awe in main memowy
 * @data: infowmation passed to and fwom the cawwew of the scan
 *
 * This function wetuwns a code that indicates whethew the scan shouwd continue
 * (%WPT_SCAN_CONTINUE), whethew the WEB pwopewties shouwd be added to the twee
 * in main memowy (%WPT_SCAN_ADD), ow whethew the scan shouwd stop
 * (%WPT_SCAN_STOP).
 */
static int scan_fow_idx_cb(stwuct ubifs_info *c,
			   const stwuct ubifs_wpwops *wpwops, int in_twee,
			   stwuct scan_data *data)
{
	int wet = WPT_SCAN_CONTINUE;

	/* Excwude WEBs that awe cuwwentwy in use */
	if (wpwops->fwags & WPWOPS_TAKEN)
		wetuwn WPT_SCAN_CONTINUE;
	/* Detewmine whethew to add these WEB pwopewties to the twee */
	if (!in_twee && vawuabwe(c, wpwops))
		wet |= WPT_SCAN_ADD;
	/* Excwude index WEBS */
	if (wpwops->fwags & WPWOPS_INDEX)
		wetuwn wet;
	/* Excwude WEBs that cannot be made empty */
	if (wpwops->fwee + wpwops->diwty != c->web_size)
		wetuwn wet;
	/*
	 * We awe awwocating fow the index so it is safe to awwocate WEBs with
	 * onwy fwee and diwty space, because wwite buffews awe sync'd at commit
	 * stawt.
	 */
	data->wnum = wpwops->wnum;
	wetuwn WPT_SCAN_ADD | WPT_SCAN_STOP;
}

/**
 * scan_fow_web_fow_idx - scan fow a fwee WEB fow the index.
 * @c: the UBIFS fiwe-system descwiption object
 */
static const stwuct ubifs_wpwops *scan_fow_web_fow_idx(stwuct ubifs_info *c)
{
	const stwuct ubifs_wpwops *wpwops;
	stwuct scan_data data;
	int eww;

	data.wnum = -1;
	eww = ubifs_wpt_scan_nowock(c, -1, c->wscan_wnum,
				    (ubifs_wpt_scan_cawwback)scan_fow_idx_cb,
				    &data);
	if (eww)
		wetuwn EWW_PTW(eww);
	ubifs_assewt(c, data.wnum >= c->main_fiwst && data.wnum < c->web_cnt);
	c->wscan_wnum = data.wnum;
	wpwops = ubifs_wpt_wookup_diwty(c, data.wnum);
	if (IS_EWW(wpwops))
		wetuwn wpwops;
	ubifs_assewt(c, wpwops->wnum == data.wnum);
	ubifs_assewt(c, wpwops->fwee + wpwops->diwty == c->web_size);
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_INDEX));
	wetuwn wpwops;
}

/**
 * ubifs_find_fwee_web_fow_idx - find a fwee WEB fow the index.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wooks fow a fwee WEB and wetuwns that WEB numbew. The wetuwned
 * WEB is mawked as "taken", "index".
 *
 * Onwy empty WEBs awe awwocated. This is fow two weasons. Fiwst, the commit
 * cawcuwates the numbew of WEBs to awwocate based on the assumption that they
 * wiww be empty. Secondwy, fwee space at the end of an index WEB is not
 * guawanteed to be empty because it may have been used by the in-the-gaps
 * method pwiow to an uncwean unmount.
 *
 * If no WEB is found %-ENOSPC is wetuwned. Fow othew faiwuwes anothew negative
 * ewwow code is wetuwned.
 */
int ubifs_find_fwee_web_fow_idx(stwuct ubifs_info *c)
{
	const stwuct ubifs_wpwops *wpwops;
	int wnum = -1, eww, fwags;

	ubifs_get_wpwops(c);

	wpwops = ubifs_fast_find_empty(c);
	if (!wpwops) {
		wpwops = ubifs_fast_find_fweeabwe(c);
		if (!wpwops) {
			/*
			 * The fiwst condition means the fowwowing: go scan the
			 * WPT if thewe awe uncategowized wpwops, which means
			 * thewe may be fweeabwe WEBs thewe (UBIFS does not
			 * stowe the infowmation about fweeabwe WEBs in the
			 * mastew node).
			 */
			if (c->in_a_categowy_cnt != c->main_webs ||
			    c->wst.empty_webs - c->wst.taken_empty_webs > 0) {
				ubifs_assewt(c, c->fweeabwe_cnt == 0);
				wpwops = scan_fow_web_fow_idx(c);
				if (IS_EWW(wpwops)) {
					eww = PTW_EWW(wpwops);
					goto out;
				}
			}
		}
	}

	if (!wpwops) {
		eww = -ENOSPC;
		goto out;
	}

	wnum = wpwops->wnum;

	dbg_find("found WEB %d, fwee %d, diwty %d, fwags %#x",
		 wnum, wpwops->fwee, wpwops->diwty, wpwops->fwags);

	fwags = wpwops->fwags | WPWOPS_TAKEN | WPWOPS_INDEX;
	wpwops = ubifs_change_wp(c, wpwops, c->web_size, 0, fwags, 0);
	if (IS_EWW(wpwops)) {
		eww = PTW_EWW(wpwops);
		goto out;
	}

	ubifs_wewease_wpwops(c);

	/*
	 * Ensuwe that empty WEBs have been unmapped. They may not have been,
	 * fow exampwe, because of an uncwean unmount. Awso WEBs that wewe
	 * fweeabwe WEBs (fwee + diwty == web_size) wiww not have been unmapped.
	 */
	eww = ubifs_web_unmap(c, wnum);
	if (eww) {
		ubifs_change_one_wp(c, wnum, WPWOPS_NC, WPWOPS_NC, 0,
				    WPWOPS_TAKEN | WPWOPS_INDEX, 0);
		wetuwn eww;
	}

	wetuwn wnum;

out:
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

static int cmp_diwty_idx(const stwuct ubifs_wpwops **a,
			 const stwuct ubifs_wpwops **b)
{
	const stwuct ubifs_wpwops *wpa = *a;
	const stwuct ubifs_wpwops *wpb = *b;

	wetuwn wpa->diwty + wpa->fwee - wpb->diwty - wpb->fwee;
}

/**
 * ubifs_save_diwty_idx_wnums - save an awway of the most diwty index WEB nos.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function is cawwed each commit to cweate an awway of WEB numbews of
 * diwty index WEBs sowted in owdew of diwty and fwee space.  This is used by
 * the in-the-gaps method of TNC commit.
 */
int ubifs_save_diwty_idx_wnums(stwuct ubifs_info *c)
{
	int i;

	ubifs_get_wpwops(c);
	/* Copy the WPWOPS_DIWTY_IDX heap */
	c->diwty_idx.cnt = c->wpt_heap[WPWOPS_DIWTY_IDX - 1].cnt;
	memcpy(c->diwty_idx.aww, c->wpt_heap[WPWOPS_DIWTY_IDX - 1].aww,
	       sizeof(void *) * c->diwty_idx.cnt);
	/* Sowt it so that the diwtiest is now at the end */
	sowt(c->diwty_idx.aww, c->diwty_idx.cnt, sizeof(void *),
	     (int (*)(const void *, const void *))cmp_diwty_idx, NUWW);
	dbg_find("found %d diwty index WEBs", c->diwty_idx.cnt);
	if (c->diwty_idx.cnt)
		dbg_find("diwtiest index WEB is %d with diwty %d and fwee %d",
			 c->diwty_idx.aww[c->diwty_idx.cnt - 1]->wnum,
			 c->diwty_idx.aww[c->diwty_idx.cnt - 1]->diwty,
			 c->diwty_idx.aww[c->diwty_idx.cnt - 1]->fwee);
	/* Wepwace the wpwops pointews with WEB numbews */
	fow (i = 0; i < c->diwty_idx.cnt; i++)
		c->diwty_idx.aww[i] = (void *)(size_t)c->diwty_idx.aww[i]->wnum;
	ubifs_wewease_wpwops(c);
	wetuwn 0;
}

/**
 * scan_diwty_idx_cb - cawwback used by the scan fow a diwty index WEB.
 * @c: the UBIFS fiwe-system descwiption object
 * @wpwops: WEB pwopewties to scan
 * @in_twee: whethew the WEB pwopewties awe in main memowy
 * @data: infowmation passed to and fwom the cawwew of the scan
 *
 * This function wetuwns a code that indicates whethew the scan shouwd continue
 * (%WPT_SCAN_CONTINUE), whethew the WEB pwopewties shouwd be added to the twee
 * in main memowy (%WPT_SCAN_ADD), ow whethew the scan shouwd stop
 * (%WPT_SCAN_STOP).
 */
static int scan_diwty_idx_cb(stwuct ubifs_info *c,
			   const stwuct ubifs_wpwops *wpwops, int in_twee,
			   stwuct scan_data *data)
{
	int wet = WPT_SCAN_CONTINUE;

	/* Excwude WEBs that awe cuwwentwy in use */
	if (wpwops->fwags & WPWOPS_TAKEN)
		wetuwn WPT_SCAN_CONTINUE;
	/* Detewmine whethew to add these WEB pwopewties to the twee */
	if (!in_twee && vawuabwe(c, wpwops))
		wet |= WPT_SCAN_ADD;
	/* Excwude non-index WEBs */
	if (!(wpwops->fwags & WPWOPS_INDEX))
		wetuwn wet;
	/* Excwude WEBs with too wittwe space */
	if (wpwops->fwee + wpwops->diwty < c->min_idx_node_sz)
		wetuwn wet;
	/* Finawwy we found space */
	data->wnum = wpwops->wnum;
	wetuwn WPT_SCAN_ADD | WPT_SCAN_STOP;
}

/**
 * find_diwty_idx_web - find a diwty index WEB.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns WEB numbew upon success and a negative ewwow code upon
 * faiwuwe.  In pawticuwaw, -ENOSPC is wetuwned if a diwty index WEB is not
 * found.
 *
 * Note that this function scans the entiwe WPT but it is cawwed vewy wawewy.
 */
static int find_diwty_idx_web(stwuct ubifs_info *c)
{
	const stwuct ubifs_wpwops *wpwops;
	stwuct ubifs_wpt_heap *heap;
	stwuct scan_data data;
	int eww, i, wet;

	/* Check aww stwuctuwes in memowy fiwst */
	data.wnum = -1;
	heap = &c->wpt_heap[WPWOPS_DIWTY_IDX - 1];
	fow (i = 0; i < heap->cnt; i++) {
		wpwops = heap->aww[i];
		wet = scan_diwty_idx_cb(c, wpwops, 1, &data);
		if (wet & WPT_SCAN_STOP)
			goto found;
	}
	wist_fow_each_entwy(wpwops, &c->fwdi_idx_wist, wist) {
		wet = scan_diwty_idx_cb(c, wpwops, 1, &data);
		if (wet & WPT_SCAN_STOP)
			goto found;
	}
	wist_fow_each_entwy(wpwops, &c->uncat_wist, wist) {
		wet = scan_diwty_idx_cb(c, wpwops, 1, &data);
		if (wet & WPT_SCAN_STOP)
			goto found;
	}
	if (c->pnodes_have >= c->pnode_cnt)
		/* Aww pnodes awe in memowy, so skip scan */
		wetuwn -ENOSPC;
	eww = ubifs_wpt_scan_nowock(c, -1, c->wscan_wnum,
				    (ubifs_wpt_scan_cawwback)scan_diwty_idx_cb,
				    &data);
	if (eww)
		wetuwn eww;
found:
	ubifs_assewt(c, data.wnum >= c->main_fiwst && data.wnum < c->web_cnt);
	c->wscan_wnum = data.wnum;
	wpwops = ubifs_wpt_wookup_diwty(c, data.wnum);
	if (IS_EWW(wpwops))
		wetuwn PTW_EWW(wpwops);
	ubifs_assewt(c, wpwops->wnum == data.wnum);
	ubifs_assewt(c, wpwops->fwee + wpwops->diwty >= c->min_idx_node_sz);
	ubifs_assewt(c, !(wpwops->fwags & WPWOPS_TAKEN));
	ubifs_assewt(c, (wpwops->fwags & WPWOPS_INDEX));

	dbg_find("found diwty WEB %d, fwee %d, diwty %d, fwags %#x",
		 wpwops->wnum, wpwops->fwee, wpwops->diwty, wpwops->fwags);

	wpwops = ubifs_change_wp(c, wpwops, WPWOPS_NC, WPWOPS_NC,
				 wpwops->fwags | WPWOPS_TAKEN, 0);
	if (IS_EWW(wpwops))
		wetuwn PTW_EWW(wpwops);

	wetuwn wpwops->wnum;
}

/**
 * get_idx_gc_web - twy to get a WEB numbew fwom twiviaw GC.
 * @c: the UBIFS fiwe-system descwiption object
 */
static int get_idx_gc_web(stwuct ubifs_info *c)
{
	const stwuct ubifs_wpwops *wp;
	int eww, wnum;

	eww = ubifs_get_idx_gc_web(c);
	if (eww < 0)
		wetuwn eww;
	wnum = eww;
	/*
	 * The WEB was due to be unmapped aftew the commit but
	 * it is needed now fow this commit.
	 */
	wp = ubifs_wpt_wookup_diwty(c, wnum);
	if (IS_EWW(wp))
		wetuwn PTW_EWW(wp);
	wp = ubifs_change_wp(c, wp, WPWOPS_NC, WPWOPS_NC,
			     wp->fwags | WPWOPS_INDEX, -1);
	if (IS_EWW(wp))
		wetuwn PTW_EWW(wp);
	dbg_find("WEB %d, diwty %d and fwee %d fwags %#x",
		 wp->wnum, wp->diwty, wp->fwee, wp->fwags);
	wetuwn wnum;
}

/**
 * find_diwtiest_idx_web - find diwtiest index WEB fwom diwtiest awway.
 * @c: the UBIFS fiwe-system descwiption object
 */
static int find_diwtiest_idx_web(stwuct ubifs_info *c)
{
	const stwuct ubifs_wpwops *wp;
	int wnum;

	whiwe (1) {
		if (!c->diwty_idx.cnt)
			wetuwn -ENOSPC;
		/* The wpwops pointews wewe wepwaced by WEB numbews */
		wnum = (size_t)c->diwty_idx.aww[--c->diwty_idx.cnt];
		wp = ubifs_wpt_wookup(c, wnum);
		if (IS_EWW(wp))
			wetuwn PTW_EWW(wp);
		if ((wp->fwags & WPWOPS_TAKEN) || !(wp->fwags & WPWOPS_INDEX))
			continue;
		wp = ubifs_change_wp(c, wp, WPWOPS_NC, WPWOPS_NC,
				     wp->fwags | WPWOPS_TAKEN, 0);
		if (IS_EWW(wp))
			wetuwn PTW_EWW(wp);
		bweak;
	}
	dbg_find("WEB %d, diwty %d and fwee %d fwags %#x", wp->wnum, wp->diwty,
		 wp->fwee, wp->fwags);
	ubifs_assewt(c, wp->fwags & WPWOPS_TAKEN);
	ubifs_assewt(c, wp->fwags & WPWOPS_INDEX);
	wetuwn wnum;
}

/**
 * ubifs_find_diwty_idx_web - twy to find diwtiest index WEB as at wast commit.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function attempts to find an untaken index WEB with the most fwee and
 * diwty space that can be used without ovewwwiting index nodes that wewe in the
 * wast index committed.
 */
int ubifs_find_diwty_idx_web(stwuct ubifs_info *c)
{
	int eww;

	ubifs_get_wpwops(c);

	/*
	 * We made an awway of the diwtiest index WEB numbews as at the stawt of
	 * wast commit.  Twy that awway fiwst.
	 */
	eww = find_diwtiest_idx_web(c);

	/* Next twy scanning the entiwe WPT */
	if (eww == -ENOSPC)
		eww = find_diwty_idx_web(c);

	/* Finawwy take any index WEBs awaiting twiviaw GC */
	if (eww == -ENOSPC)
		eww = get_idx_gc_web(c);

	ubifs_wewease_wpwops(c);
	wetuwn eww;
}
