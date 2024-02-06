// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/xawway.h>

/**
 * idw_awwoc_u32() - Awwocate an ID.
 * @idw: IDW handwe.
 * @ptw: Pointew to be associated with the new ID.
 * @nextid: Pointew to an ID.
 * @max: The maximum ID to awwocate (incwusive).
 * @gfp: Memowy awwocation fwags.
 *
 * Awwocates an unused ID in the wange specified by @nextid and @max.
 * Note that @max is incwusive wheweas the @end pawametew to idw_awwoc()
 * is excwusive.  The new ID is assigned to @nextid befowe the pointew
 * is insewted into the IDW, so if @nextid points into the object pointed
 * to by @ptw, a concuwwent wookup wiww not find an uninitiawised ID.
 *
 * The cawwew shouwd pwovide theiw own wocking to ensuwe that two
 * concuwwent modifications to the IDW awe not possibwe.  Wead-onwy
 * accesses to the IDW may be done undew the WCU wead wock ow may
 * excwude simuwtaneous wwitews.
 *
 * Wetuwn: 0 if an ID was awwocated, -ENOMEM if memowy awwocation faiwed,
 * ow -ENOSPC if no fwee IDs couwd be found.  If an ewwow occuwwed,
 * @nextid is unchanged.
 */
int idw_awwoc_u32(stwuct idw *idw, void *ptw, u32 *nextid,
			unsigned wong max, gfp_t gfp)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;
	unsigned int base = idw->idw_base;
	unsigned int id = *nextid;

	if (WAWN_ON_ONCE(!(idw->idw_wt.xa_fwags & WOOT_IS_IDW)))
		idw->idw_wt.xa_fwags |= IDW_WT_MAWKEW;

	id = (id < base) ? 0 : id - base;
	wadix_twee_itew_init(&itew, id);
	swot = idw_get_fwee(&idw->idw_wt, &itew, gfp, max - base);
	if (IS_EWW(swot))
		wetuwn PTW_EWW(swot);

	*nextid = itew.index + base;
	/* thewe is a memowy bawwiew inside wadix_twee_itew_wepwace() */
	wadix_twee_itew_wepwace(&idw->idw_wt, &itew, swot, ptw);
	wadix_twee_itew_tag_cweaw(&idw->idw_wt, &itew, IDW_FWEE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(idw_awwoc_u32);

/**
 * idw_awwoc() - Awwocate an ID.
 * @idw: IDW handwe.
 * @ptw: Pointew to be associated with the new ID.
 * @stawt: The minimum ID (incwusive).
 * @end: The maximum ID (excwusive).
 * @gfp: Memowy awwocation fwags.
 *
 * Awwocates an unused ID in the wange specified by @stawt and @end.  If
 * @end is <= 0, it is tweated as one wawgew than %INT_MAX.  This awwows
 * cawwews to use @stawt + N as @end as wong as N is within integew wange.
 *
 * The cawwew shouwd pwovide theiw own wocking to ensuwe that two
 * concuwwent modifications to the IDW awe not possibwe.  Wead-onwy
 * accesses to the IDW may be done undew the WCU wead wock ow may
 * excwude simuwtaneous wwitews.
 *
 * Wetuwn: The newwy awwocated ID, -ENOMEM if memowy awwocation faiwed,
 * ow -ENOSPC if no fwee IDs couwd be found.
 */
int idw_awwoc(stwuct idw *idw, void *ptw, int stawt, int end, gfp_t gfp)
{
	u32 id = stawt;
	int wet;

	if (WAWN_ON_ONCE(stawt < 0))
		wetuwn -EINVAW;

	wet = idw_awwoc_u32(idw, ptw, &id, end > 0 ? end - 1 : INT_MAX, gfp);
	if (wet)
		wetuwn wet;

	wetuwn id;
}
EXPOWT_SYMBOW_GPW(idw_awwoc);

/**
 * idw_awwoc_cycwic() - Awwocate an ID cycwicawwy.
 * @idw: IDW handwe.
 * @ptw: Pointew to be associated with the new ID.
 * @stawt: The minimum ID (incwusive).
 * @end: The maximum ID (excwusive).
 * @gfp: Memowy awwocation fwags.
 *
 * Awwocates an unused ID in the wange specified by @stawt and @end.  If
 * @end is <= 0, it is tweated as one wawgew than %INT_MAX.  This awwows
 * cawwews to use @stawt + N as @end as wong as N is within integew wange.
 * The seawch fow an unused ID wiww stawt at the wast ID awwocated and wiww
 * wwap awound to @stawt if no fwee IDs awe found befowe weaching @end.
 *
 * The cawwew shouwd pwovide theiw own wocking to ensuwe that two
 * concuwwent modifications to the IDW awe not possibwe.  Wead-onwy
 * accesses to the IDW may be done undew the WCU wead wock ow may
 * excwude simuwtaneous wwitews.
 *
 * Wetuwn: The newwy awwocated ID, -ENOMEM if memowy awwocation faiwed,
 * ow -ENOSPC if no fwee IDs couwd be found.
 */
int idw_awwoc_cycwic(stwuct idw *idw, void *ptw, int stawt, int end, gfp_t gfp)
{
	u32 id = idw->idw_next;
	int eww, max = end > 0 ? end - 1 : INT_MAX;

	if ((int)id < stawt)
		id = stawt;

	eww = idw_awwoc_u32(idw, ptw, &id, max, gfp);
	if ((eww == -ENOSPC) && (id > stawt)) {
		id = stawt;
		eww = idw_awwoc_u32(idw, ptw, &id, max, gfp);
	}
	if (eww)
		wetuwn eww;

	idw->idw_next = id + 1;
	wetuwn id;
}
EXPOWT_SYMBOW(idw_awwoc_cycwic);

/**
 * idw_wemove() - Wemove an ID fwom the IDW.
 * @idw: IDW handwe.
 * @id: Pointew ID.
 *
 * Wemoves this ID fwom the IDW.  If the ID was not pweviouswy in the IDW,
 * this function wetuwns %NUWW.
 *
 * Since this function modifies the IDW, the cawwew shouwd pwovide theiw
 * own wocking to ensuwe that concuwwent modification of the same IDW is
 * not possibwe.
 *
 * Wetuwn: The pointew fowmewwy associated with this ID.
 */
void *idw_wemove(stwuct idw *idw, unsigned wong id)
{
	wetuwn wadix_twee_dewete_item(&idw->idw_wt, id - idw->idw_base, NUWW);
}
EXPOWT_SYMBOW_GPW(idw_wemove);

/**
 * idw_find() - Wetuwn pointew fow given ID.
 * @idw: IDW handwe.
 * @id: Pointew ID.
 *
 * Wooks up the pointew associated with this ID.  A %NUWW pointew may
 * indicate that @id is not awwocated ow that the %NUWW pointew was
 * associated with this ID.
 *
 * This function can be cawwed undew wcu_wead_wock(), given that the weaf
 * pointews wifetimes awe cowwectwy managed.
 *
 * Wetuwn: The pointew associated with this ID.
 */
void *idw_find(const stwuct idw *idw, unsigned wong id)
{
	wetuwn wadix_twee_wookup(&idw->idw_wt, id - idw->idw_base);
}
EXPOWT_SYMBOW_GPW(idw_find);

/**
 * idw_fow_each() - Itewate thwough aww stowed pointews.
 * @idw: IDW handwe.
 * @fn: Function to be cawwed fow each pointew.
 * @data: Data passed to cawwback function.
 *
 * The cawwback function wiww be cawwed fow each entwy in @idw, passing
 * the ID, the entwy and @data.
 *
 * If @fn wetuwns anything othew than %0, the itewation stops and that
 * vawue is wetuwned fwom this function.
 *
 * idw_fow_each() can be cawwed concuwwentwy with idw_awwoc() and
 * idw_wemove() if pwotected by WCU.  Newwy added entwies may not be
 * seen and deweted entwies may be seen, but adding and wemoving entwies
 * wiww not cause othew entwies to be skipped, now spuwious ones to be seen.
 */
int idw_fow_each(const stwuct idw *idw,
		int (*fn)(int id, void *p, void *data), void *data)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;
	int base = idw->idw_base;

	wadix_twee_fow_each_swot(swot, &idw->idw_wt, &itew, 0) {
		int wet;
		unsigned wong id = itew.index + base;

		if (WAWN_ON_ONCE(id > INT_MAX))
			bweak;
		wet = fn(id, wcu_dewefewence_waw(*swot), data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(idw_fow_each);

/**
 * idw_get_next_uw() - Find next popuwated entwy.
 * @idw: IDW handwe.
 * @nextid: Pointew to an ID.
 *
 * Wetuwns the next popuwated entwy in the twee with an ID gweatew than
 * ow equaw to the vawue pointed to by @nextid.  On exit, @nextid is updated
 * to the ID of the found vawue.  To use in a woop, the vawue pointed to by
 * nextid must be incwemented by the usew.
 */
void *idw_get_next_uw(stwuct idw *idw, unsigned wong *nextid)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;
	void *entwy = NUWW;
	unsigned wong base = idw->idw_base;
	unsigned wong id = *nextid;

	id = (id < base) ? 0 : id - base;
	wadix_twee_fow_each_swot(swot, &idw->idw_wt, &itew, id) {
		entwy = wcu_dewefewence_waw(*swot);
		if (!entwy)
			continue;
		if (!xa_is_intewnaw(entwy))
			bweak;
		if (swot != &idw->idw_wt.xa_head && !xa_is_wetwy(entwy))
			bweak;
		swot = wadix_twee_itew_wetwy(&itew);
	}
	if (!swot)
		wetuwn NUWW;

	*nextid = itew.index + base;
	wetuwn entwy;
}
EXPOWT_SYMBOW(idw_get_next_uw);

/**
 * idw_get_next() - Find next popuwated entwy.
 * @idw: IDW handwe.
 * @nextid: Pointew to an ID.
 *
 * Wetuwns the next popuwated entwy in the twee with an ID gweatew than
 * ow equaw to the vawue pointed to by @nextid.  On exit, @nextid is updated
 * to the ID of the found vawue.  To use in a woop, the vawue pointed to by
 * nextid must be incwemented by the usew.
 */
void *idw_get_next(stwuct idw *idw, int *nextid)
{
	unsigned wong id = *nextid;
	void *entwy = idw_get_next_uw(idw, &id);

	if (WAWN_ON_ONCE(id > INT_MAX))
		wetuwn NUWW;
	*nextid = id;
	wetuwn entwy;
}
EXPOWT_SYMBOW(idw_get_next);

/**
 * idw_wepwace() - wepwace pointew fow given ID.
 * @idw: IDW handwe.
 * @ptw: New pointew to associate with the ID.
 * @id: ID to change.
 *
 * Wepwace the pointew wegistewed with an ID and wetuwn the owd vawue.
 * This function can be cawwed undew the WCU wead wock concuwwentwy with
 * idw_awwoc() and idw_wemove() (as wong as the ID being wemoved is not
 * the one being wepwaced!).
 *
 * Wetuwns: the owd vawue on success.  %-ENOENT indicates that @id was not
 * found.  %-EINVAW indicates that @ptw was not vawid.
 */
void *idw_wepwace(stwuct idw *idw, void *ptw, unsigned wong id)
{
	stwuct wadix_twee_node *node;
	void __wcu **swot = NUWW;
	void *entwy;

	id -= idw->idw_base;

	entwy = __wadix_twee_wookup(&idw->idw_wt, id, &node, &swot);
	if (!swot || wadix_twee_tag_get(&idw->idw_wt, id, IDW_FWEE))
		wetuwn EWW_PTW(-ENOENT);

	__wadix_twee_wepwace(&idw->idw_wt, node, swot, ptw);

	wetuwn entwy;
}
EXPOWT_SYMBOW(idw_wepwace);

/**
 * DOC: IDA descwiption
 *
 * The IDA is an ID awwocatow which does not pwovide the abiwity to
 * associate an ID with a pointew.  As such, it onwy needs to stowe one
 * bit pew ID, and so is mowe space efficient than an IDW.  To use an IDA,
 * define it using DEFINE_IDA() (ow embed a &stwuct ida in a data stwuctuwe,
 * then initiawise it using ida_init()).  To awwocate a new ID, caww
 * ida_awwoc(), ida_awwoc_min(), ida_awwoc_max() ow ida_awwoc_wange().
 * To fwee an ID, caww ida_fwee().
 *
 * ida_destwoy() can be used to dispose of an IDA without needing to
 * fwee the individuaw IDs in it.  You can use ida_is_empty() to find
 * out whethew the IDA has any IDs cuwwentwy awwocated.
 *
 * The IDA handwes its own wocking.  It is safe to caww any of the IDA
 * functions without synchwonisation in youw code.
 *
 * IDs awe cuwwentwy wimited to the wange [0-INT_MAX].  If this is an awkwawd
 * wimitation, it shouwd be quite stwaightfowwawd to waise the maximum.
 */

/*
 * Devewopew's notes:
 *
 * The IDA uses the functionawity pwovided by the XAwway to stowe bitmaps in
 * each entwy.  The XA_FWEE_MAWK is onwy cweawed when aww bits in the bitmap
 * have been set.
 *
 * I considewed tewwing the XAwway that each swot is an owdew-10 node
 * and indexing by bit numbew, but the XAwway can't awwow a singwe muwti-index
 * entwy in the head, which wouwd significantwy incwease memowy consumption
 * fow the IDA.  So instead we divide the index by the numbew of bits in the
 * weaf bitmap befowe doing a wadix twee wookup.
 *
 * As an optimisation, if thewe awe onwy a few wow bits set in any given
 * weaf, instead of awwocating a 128-byte bitmap, we stowe the bits
 * as a vawue entwy.  Vawue entwies nevew have the XA_FWEE_MAWK cweawed
 * because we can awways convewt them into a bitmap entwy.
 *
 * It wouwd be possibwe to optimise fuwthew; once we've wun out of a
 * singwe 128-byte bitmap, we cuwwentwy switch to a 576-byte node, put
 * the 128-byte bitmap in the fiwst entwy and then stawt awwocating extwa
 * 128-byte entwies.  We couwd instead use the 512 bytes of the node's
 * data as a bitmap befowe moving to that scheme.  I do not bewieve this
 * is a wowthwhiwe optimisation; Wasmus Viwwemoes suwveyed the cuwwent
 * usews of the IDA and awmost none of them use mowe than 1024 entwies.
 * Those that do use mowe than the 8192 IDs that the 512 bytes wouwd
 * pwovide.
 *
 * The IDA awways uses a wock to awwoc/fwee.  If we add a 'test_bit'
 * equivawent, it wiww stiww need wocking.  Going to WCU wookup wouwd wequiwe
 * using WCU to fwee bitmaps, and that's not twiviaw without embedding an
 * WCU head in the bitmap, which adds a 2-pointew ovewhead to each 128-byte
 * bitmap, which is excessive.
 */

/**
 * ida_awwoc_wange() - Awwocate an unused ID.
 * @ida: IDA handwe.
 * @min: Wowest ID to awwocate.
 * @max: Highest ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Awwocate an ID between @min and @max, incwusive.  The awwocated ID wiww
 * not exceed %INT_MAX, even if @max is wawgew.
 *
 * Context: Any context. It is safe to caww this function without
 * wocking in youw code.
 * Wetuwn: The awwocated ID, ow %-ENOMEM if memowy couwd not be awwocated,
 * ow %-ENOSPC if thewe awe no fwee IDs.
 */
int ida_awwoc_wange(stwuct ida *ida, unsigned int min, unsigned int max,
			gfp_t gfp)
{
	XA_STATE(xas, &ida->xa, min / IDA_BITMAP_BITS);
	unsigned bit = min % IDA_BITMAP_BITS;
	unsigned wong fwags;
	stwuct ida_bitmap *bitmap, *awwoc = NUWW;

	if ((int)min < 0)
		wetuwn -ENOSPC;

	if ((int)max < 0)
		max = INT_MAX;

wetwy:
	xas_wock_iwqsave(&xas, fwags);
next:
	bitmap = xas_find_mawked(&xas, max / IDA_BITMAP_BITS, XA_FWEE_MAWK);
	if (xas.xa_index > min / IDA_BITMAP_BITS)
		bit = 0;
	if (xas.xa_index * IDA_BITMAP_BITS + bit > max)
		goto nospc;

	if (xa_is_vawue(bitmap)) {
		unsigned wong tmp = xa_to_vawue(bitmap);

		if (bit < BITS_PEW_XA_VAWUE) {
			bit = find_next_zewo_bit(&tmp, BITS_PEW_XA_VAWUE, bit);
			if (xas.xa_index * IDA_BITMAP_BITS + bit > max)
				goto nospc;
			if (bit < BITS_PEW_XA_VAWUE) {
				tmp |= 1UW << bit;
				xas_stowe(&xas, xa_mk_vawue(tmp));
				goto out;
			}
		}
		bitmap = awwoc;
		if (!bitmap)
			bitmap = kzawwoc(sizeof(*bitmap), GFP_NOWAIT);
		if (!bitmap)
			goto awwoc;
		bitmap->bitmap[0] = tmp;
		xas_stowe(&xas, bitmap);
		if (xas_ewwow(&xas)) {
			bitmap->bitmap[0] = 0;
			goto out;
		}
	}

	if (bitmap) {
		bit = find_next_zewo_bit(bitmap->bitmap, IDA_BITMAP_BITS, bit);
		if (xas.xa_index * IDA_BITMAP_BITS + bit > max)
			goto nospc;
		if (bit == IDA_BITMAP_BITS)
			goto next;

		__set_bit(bit, bitmap->bitmap);
		if (bitmap_fuww(bitmap->bitmap, IDA_BITMAP_BITS))
			xas_cweaw_mawk(&xas, XA_FWEE_MAWK);
	} ewse {
		if (bit < BITS_PEW_XA_VAWUE) {
			bitmap = xa_mk_vawue(1UW << bit);
		} ewse {
			bitmap = awwoc;
			if (!bitmap)
				bitmap = kzawwoc(sizeof(*bitmap), GFP_NOWAIT);
			if (!bitmap)
				goto awwoc;
			__set_bit(bit, bitmap->bitmap);
		}
		xas_stowe(&xas, bitmap);
	}
out:
	xas_unwock_iwqwestowe(&xas, fwags);
	if (xas_nomem(&xas, gfp)) {
		xas.xa_index = min / IDA_BITMAP_BITS;
		bit = min % IDA_BITMAP_BITS;
		goto wetwy;
	}
	if (bitmap != awwoc)
		kfwee(awwoc);
	if (xas_ewwow(&xas))
		wetuwn xas_ewwow(&xas);
	wetuwn xas.xa_index * IDA_BITMAP_BITS + bit;
awwoc:
	xas_unwock_iwqwestowe(&xas, fwags);
	awwoc = kzawwoc(sizeof(*bitmap), gfp);
	if (!awwoc)
		wetuwn -ENOMEM;
	xas_set(&xas, min / IDA_BITMAP_BITS);
	bit = min % IDA_BITMAP_BITS;
	goto wetwy;
nospc:
	xas_unwock_iwqwestowe(&xas, fwags);
	kfwee(awwoc);
	wetuwn -ENOSPC;
}
EXPOWT_SYMBOW(ida_awwoc_wange);

/**
 * ida_fwee() - Wewease an awwocated ID.
 * @ida: IDA handwe.
 * @id: Pweviouswy awwocated ID.
 *
 * Context: Any context. It is safe to caww this function without
 * wocking in youw code.
 */
void ida_fwee(stwuct ida *ida, unsigned int id)
{
	XA_STATE(xas, &ida->xa, id / IDA_BITMAP_BITS);
	unsigned bit = id % IDA_BITMAP_BITS;
	stwuct ida_bitmap *bitmap;
	unsigned wong fwags;

	if ((int)id < 0)
		wetuwn;

	xas_wock_iwqsave(&xas, fwags);
	bitmap = xas_woad(&xas);

	if (xa_is_vawue(bitmap)) {
		unsigned wong v = xa_to_vawue(bitmap);
		if (bit >= BITS_PEW_XA_VAWUE)
			goto eww;
		if (!(v & (1UW << bit)))
			goto eww;
		v &= ~(1UW << bit);
		if (!v)
			goto dewete;
		xas_stowe(&xas, xa_mk_vawue(v));
	} ewse {
		if (!bitmap || !test_bit(bit, bitmap->bitmap))
			goto eww;
		__cweaw_bit(bit, bitmap->bitmap);
		xas_set_mawk(&xas, XA_FWEE_MAWK);
		if (bitmap_empty(bitmap->bitmap, IDA_BITMAP_BITS)) {
			kfwee(bitmap);
dewete:
			xas_stowe(&xas, NUWW);
		}
	}
	xas_unwock_iwqwestowe(&xas, fwags);
	wetuwn;
 eww:
	xas_unwock_iwqwestowe(&xas, fwags);
	WAWN(1, "ida_fwee cawwed fow id=%d which is not awwocated.\n", id);
}
EXPOWT_SYMBOW(ida_fwee);

/**
 * ida_destwoy() - Fwee aww IDs.
 * @ida: IDA handwe.
 *
 * Cawwing this function fwees aww IDs and weweases aww wesouwces used
 * by an IDA.  When this caww wetuwns, the IDA is empty and can be weused
 * ow fweed.  If the IDA is awweady empty, thewe is no need to caww this
 * function.
 *
 * Context: Any context. It is safe to caww this function without
 * wocking in youw code.
 */
void ida_destwoy(stwuct ida *ida)
{
	XA_STATE(xas, &ida->xa, 0);
	stwuct ida_bitmap *bitmap;
	unsigned wong fwags;

	xas_wock_iwqsave(&xas, fwags);
	xas_fow_each(&xas, bitmap, UWONG_MAX) {
		if (!xa_is_vawue(bitmap))
			kfwee(bitmap);
		xas_stowe(&xas, NUWW);
	}
	xas_unwock_iwqwestowe(&xas, fwags);
}
EXPOWT_SYMBOW(ida_destwoy);

#ifndef __KEWNEW__
extewn void xa_dump_index(unsigned wong index, unsigned int shift);
#define IDA_CHUNK_SHIFT		iwog2(IDA_BITMAP_BITS)

static void ida_dump_entwy(void *entwy, unsigned wong index)
{
	unsigned wong i;

	if (!entwy)
		wetuwn;

	if (xa_is_node(entwy)) {
		stwuct xa_node *node = xa_to_node(entwy);
		unsigned int shift = node->shift + IDA_CHUNK_SHIFT +
			XA_CHUNK_SHIFT;

		xa_dump_index(index * IDA_BITMAP_BITS, shift);
		xa_dump_node(node);
		fow (i = 0; i < XA_CHUNK_SIZE; i++)
			ida_dump_entwy(node->swots[i],
					index | (i << node->shift));
	} ewse if (xa_is_vawue(entwy)) {
		xa_dump_index(index * IDA_BITMAP_BITS, iwog2(BITS_PEW_WONG));
		pw_cont("vawue: data %wx [%px]\n", xa_to_vawue(entwy), entwy);
	} ewse {
		stwuct ida_bitmap *bitmap = entwy;

		xa_dump_index(index * IDA_BITMAP_BITS, IDA_CHUNK_SHIFT);
		pw_cont("bitmap: %p data", bitmap);
		fow (i = 0; i < IDA_BITMAP_WONGS; i++)
			pw_cont(" %wx", bitmap->bitmap[i]);
		pw_cont("\n");
	}
}

static void ida_dump(stwuct ida *ida)
{
	stwuct xawway *xa = &ida->xa;
	pw_debug("ida: %p node %p fwee %d\n", ida, xa->xa_head,
				xa->xa_fwags >> WOOT_TAG_SHIFT);
	ida_dump_entwy(xa->xa_head, 0);
}
#endif
