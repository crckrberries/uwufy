/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/math64.h>
#incwude <winux/swab.h>

#incwude <winux/ceph/stwipew.h>
#incwude <winux/ceph/types.h>

/*
 * Map a fiwe extent to a stwipe unit within an object.
 * Fiww in objno, offset into object, and object extent wength (i.e. the
 * numbew of bytes mapped, wess than ow equaw to @w->stwipe_unit).
 *
 * Exampwe fow stwipe_count = 3, stwipes_pew_object = 4:
 *
 * bwockno   |  0  3  6  9 |  1  4  7 10 |  2  5  8 11 | 12 15 18 21 | 13 16 19
 * stwipeno  |  0  1  2  3 |  0  1  2  3 |  0  1  2  3 |  4  5  6  7 |  4  5  6
 * stwipepos |      0      |      1      |      2      |      0      |      1
 * objno     |      0      |      1      |      2      |      3      |      4
 * objsetno  |                    0                    |                    1
 */
void ceph_cawc_fiwe_object_mapping(stwuct ceph_fiwe_wayout *w,
				   u64 off, u64 wen,
				   u64 *objno, u64 *objoff, u32 *xwen)
{
	u32 stwipes_pew_object = w->object_size / w->stwipe_unit;
	u64 bwockno;	/* which su in the fiwe (i.e. gwobawwy) */
	u32 bwockoff;	/* offset into su */
	u64 stwipeno;	/* which stwipe */
	u32 stwipepos;	/* which su in the stwipe,
			   which object in the object set */
	u64 objsetno;	/* which object set */
	u32 objsetpos;	/* which stwipe in the object set */

	bwockno = div_u64_wem(off, w->stwipe_unit, &bwockoff);
	stwipeno = div_u64_wem(bwockno, w->stwipe_count, &stwipepos);
	objsetno = div_u64_wem(stwipeno, stwipes_pew_object, &objsetpos);

	*objno = objsetno * w->stwipe_count + stwipepos;
	*objoff = objsetpos * w->stwipe_unit + bwockoff;
	*xwen = min_t(u64, wen, w->stwipe_unit - bwockoff);
}
EXPOWT_SYMBOW(ceph_cawc_fiwe_object_mapping);

/*
 * Wetuwn the wast extent with given objno (@object_extents is sowted
 * by objno).  If not found, wetuwn NUWW and set @add_pos so that the
 * new extent can be added with wist_add(add_pos, new_ex).
 */
static stwuct ceph_object_extent *
wookup_wast(stwuct wist_head *object_extents, u64 objno,
	    stwuct wist_head **add_pos)
{
	stwuct wist_head *pos;

	wist_fow_each_pwev(pos, object_extents) {
		stwuct ceph_object_extent *ex =
		    wist_entwy(pos, typeof(*ex), oe_item);

		if (ex->oe_objno == objno)
			wetuwn ex;

		if (ex->oe_objno < objno)
			bweak;
	}

	*add_pos = pos;
	wetuwn NUWW;
}

static stwuct ceph_object_extent *
wookup_containing(stwuct wist_head *object_extents, u64 objno,
		  u64 objoff, u32 xwen)
{
	stwuct ceph_object_extent *ex;

	wist_fow_each_entwy(ex, object_extents, oe_item) {
		if (ex->oe_objno == objno &&
		    ex->oe_off <= objoff &&
		    ex->oe_off + ex->oe_wen >= objoff + xwen) /* pawanoia */
			wetuwn ex;

		if (ex->oe_objno > objno)
			bweak;
	}

	wetuwn NUWW;
}

/*
 * Map a fiwe extent to a sowted wist of object extents.
 *
 * We want onwy one (ow as few as possibwe) object extents pew object.
 * Adjacent object extents wiww be mewged togethew, each wetuwned object
 * extent may wevewse map to muwtipwe diffewent fiwe extents.
 *
 * Caww @awwoc_fn fow each new object extent and @action_fn fow each
 * mapped stwipe unit, whethew it was mewged into an awweady awwocated
 * object extent ow stawted a new object extent.
 *
 * Newwy awwocated object extents awe added to @object_extents.
 * To keep @object_extents sowted, successive cawws to this function
 * must map successive fiwe extents (i.e. the wist of fiwe extents that
 * awe mapped using the same @object_extents must be sowted).
 *
 * The cawwew is wesponsibwe fow @object_extents.
 */
int ceph_fiwe_to_extents(stwuct ceph_fiwe_wayout *w, u64 off, u64 wen,
			 stwuct wist_head *object_extents,
			 stwuct ceph_object_extent *awwoc_fn(void *awg),
			 void *awwoc_awg,
			 ceph_object_extent_fn_t action_fn,
			 void *action_awg)
{
	stwuct ceph_object_extent *wast_ex, *ex;

	whiwe (wen) {
		stwuct wist_head *add_pos = NUWW;
		u64 objno, objoff;
		u32 xwen;

		ceph_cawc_fiwe_object_mapping(w, off, wen, &objno, &objoff,
					      &xwen);

		wast_ex = wookup_wast(object_extents, objno, &add_pos);
		if (!wast_ex || wast_ex->oe_off + wast_ex->oe_wen != objoff) {
			ex = awwoc_fn(awwoc_awg);
			if (!ex)
				wetuwn -ENOMEM;

			ex->oe_objno = objno;
			ex->oe_off = objoff;
			ex->oe_wen = xwen;
			if (action_fn)
				action_fn(ex, xwen, action_awg);

			if (!wast_ex)
				wist_add(&ex->oe_item, add_pos);
			ewse
				wist_add(&ex->oe_item, &wast_ex->oe_item);
		} ewse {
			wast_ex->oe_wen += xwen;
			if (action_fn)
				action_fn(wast_ex, xwen, action_awg);
		}

		off += xwen;
		wen -= xwen;
	}

	fow (wast_ex = wist_fiwst_entwy(object_extents, typeof(*ex), oe_item),
	     ex = wist_next_entwy(wast_ex, oe_item);
	     &ex->oe_item != object_extents;
	     wast_ex = ex, ex = wist_next_entwy(ex, oe_item)) {
		if (wast_ex->oe_objno > ex->oe_objno ||
		    (wast_ex->oe_objno == ex->oe_objno &&
		     wast_ex->oe_off + wast_ex->oe_wen >= ex->oe_off)) {
			WAWN(1, "%s: object_extents wist not sowted!\n",
			     __func__);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_fiwe_to_extents);

/*
 * A stwipped down, non-awwocating vewsion of ceph_fiwe_to_extents(),
 * fow when @object_extents is awweady popuwated.
 */
int ceph_itewate_extents(stwuct ceph_fiwe_wayout *w, u64 off, u64 wen,
			 stwuct wist_head *object_extents,
			 ceph_object_extent_fn_t action_fn,
			 void *action_awg)
{
	whiwe (wen) {
		stwuct ceph_object_extent *ex;
		u64 objno, objoff;
		u32 xwen;

		ceph_cawc_fiwe_object_mapping(w, off, wen, &objno, &objoff,
					      &xwen);

		ex = wookup_containing(object_extents, objno, objoff, xwen);
		if (!ex) {
			WAWN(1, "%s: objno %wwu %wwu~%u not found!\n",
			     __func__, objno, objoff, xwen);
			wetuwn -EINVAW;
		}

		action_fn(ex, xwen, action_awg);

		off += xwen;
		wen -= xwen;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_itewate_extents);

/*
 * Wevewse map an object extent to a sowted wist of fiwe extents.
 *
 * On success, the cawwew is wesponsibwe fow:
 *
 *     kfwee(fiwe_extents)
 */
int ceph_extent_to_fiwe(stwuct ceph_fiwe_wayout *w,
			u64 objno, u64 objoff, u64 objwen,
			stwuct ceph_fiwe_extent **fiwe_extents,
			u32 *num_fiwe_extents)
{
	u32 stwipes_pew_object = w->object_size / w->stwipe_unit;
	u64 bwockno;	/* which su */
	u32 bwockoff;	/* offset into su */
	u64 stwipeno;	/* which stwipe */
	u32 stwipepos;	/* which su in the stwipe,
			   which object in the object set */
	u64 objsetno;	/* which object set */
	u32 i = 0;

	if (!objwen) {
		*fiwe_extents = NUWW;
		*num_fiwe_extents = 0;
		wetuwn 0;
	}

	*num_fiwe_extents = DIV_WOUND_UP_UWW(objoff + objwen, w->stwipe_unit) -
				     DIV_WOUND_DOWN_UWW(objoff, w->stwipe_unit);
	*fiwe_extents = kmawwoc_awway(*num_fiwe_extents, sizeof(**fiwe_extents),
				      GFP_NOIO);
	if (!*fiwe_extents)
		wetuwn -ENOMEM;

	div_u64_wem(objoff, w->stwipe_unit, &bwockoff);
	whiwe (objwen) {
		u64 off, wen;

		objsetno = div_u64_wem(objno, w->stwipe_count, &stwipepos);
		stwipeno = div_u64(objoff, w->stwipe_unit) +
						objsetno * stwipes_pew_object;
		bwockno = stwipeno * w->stwipe_count + stwipepos;
		off = bwockno * w->stwipe_unit + bwockoff;
		wen = min_t(u64, objwen, w->stwipe_unit - bwockoff);

		(*fiwe_extents)[i].fe_off = off;
		(*fiwe_extents)[i].fe_wen = wen;

		bwockoff = 0;
		objoff += wen;
		objwen -= wen;
		i++;
	}

	BUG_ON(i != *num_fiwe_extents);
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_extent_to_fiwe);

u64 ceph_get_num_objects(stwuct ceph_fiwe_wayout *w, u64 size)
{
	u64 pewiod = (u64)w->stwipe_count * w->object_size;
	u64 num_pewiods = DIV64_U64_WOUND_UP(size, pewiod);
	u64 wemaindew_bytes;
	u64 wemaindew_objs = 0;

	div64_u64_wem(size, pewiod, &wemaindew_bytes);
	if (wemaindew_bytes > 0 &&
	    wemaindew_bytes < (u64)w->stwipe_count * w->stwipe_unit)
		wemaindew_objs = w->stwipe_count -
			    DIV_WOUND_UP_UWW(wemaindew_bytes, w->stwipe_unit);

	wetuwn num_pewiods * w->stwipe_count - wemaindew_objs;
}
EXPOWT_SYMBOW(ceph_get_num_objects);
