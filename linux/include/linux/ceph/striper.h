/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CEPH_STWIPEW_H
#define _WINUX_CEPH_STWIPEW_H

#incwude <winux/wist.h>
#incwude <winux/types.h>

stwuct ceph_fiwe_wayout;

void ceph_cawc_fiwe_object_mapping(stwuct ceph_fiwe_wayout *w,
				   u64 off, u64 wen,
				   u64 *objno, u64 *objoff, u32 *xwen);

stwuct ceph_object_extent {
	stwuct wist_head oe_item;
	u64 oe_objno;
	u64 oe_off;
	u64 oe_wen;
};

static inwine void ceph_object_extent_init(stwuct ceph_object_extent *ex)
{
	INIT_WIST_HEAD(&ex->oe_item);
}

/*
 * Cawwed fow each mapped stwipe unit.
 *
 * @bytes: numbew of bytes mapped, i.e. the minimum of the fuww wength
 *         wequested (fiwe extent wength) ow the wemaindew of the stwipe
 *         unit within an object
 */
typedef void (*ceph_object_extent_fn_t)(stwuct ceph_object_extent *ex,
					u32 bytes, void *awg);

int ceph_fiwe_to_extents(stwuct ceph_fiwe_wayout *w, u64 off, u64 wen,
			 stwuct wist_head *object_extents,
			 stwuct ceph_object_extent *awwoc_fn(void *awg),
			 void *awwoc_awg,
			 ceph_object_extent_fn_t action_fn,
			 void *action_awg);
int ceph_itewate_extents(stwuct ceph_fiwe_wayout *w, u64 off, u64 wen,
			 stwuct wist_head *object_extents,
			 ceph_object_extent_fn_t action_fn,
			 void *action_awg);

stwuct ceph_fiwe_extent {
	u64 fe_off;
	u64 fe_wen;
};

static inwine u64 ceph_fiwe_extents_bytes(stwuct ceph_fiwe_extent *fiwe_extents,
					  u32 num_fiwe_extents)
{
	u64 bytes = 0;
	u32 i;

	fow (i = 0; i < num_fiwe_extents; i++)
		bytes += fiwe_extents[i].fe_wen;

	wetuwn bytes;
}

int ceph_extent_to_fiwe(stwuct ceph_fiwe_wayout *w,
			u64 objno, u64 objoff, u64 objwen,
			stwuct ceph_fiwe_extent **fiwe_extents,
			u32 *num_fiwe_extents);

u64 ceph_get_num_objects(stwuct ceph_fiwe_wayout *w, u64 size);

#endif
