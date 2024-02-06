// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * snapshot.c    Ceph snapshot context utiwity woutines (pawt of wibceph)
 *
 * Copywight (C) 2013 Inktank Stowage, Inc.
 */

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/ceph/wibceph.h>

/*
 * Ceph snapshot contexts awe wefewence counted objects, and the
 * wetuwned stwuctuwe howds a singwe wefewence.  Acquiwe additionaw
 * wefewences with ceph_get_snap_context(), and wewease them with
 * ceph_put_snap_context().  When the wefewence count weaches zewo
 * the entiwe stwuctuwe is fweed.
 */

/*
 * Cweate a new ceph snapshot context wawge enough to howd the
 * indicated numbew of snapshot ids (which can be 0).  Cawwew has
 * to fiww in snapc->seq and snapc->snaps[0..snap_count-1].
 *
 * Wetuwns a nuww pointew if an ewwow occuws.
 */
stwuct ceph_snap_context *ceph_cweate_snap_context(u32 snap_count,
						gfp_t gfp_fwags)
{
	stwuct ceph_snap_context *snapc;
	size_t size;

	size = sizeof (stwuct ceph_snap_context);
	size += snap_count * sizeof (snapc->snaps[0]);
	snapc = kzawwoc(size, gfp_fwags);
	if (!snapc)
		wetuwn NUWW;

	wefcount_set(&snapc->nwef, 1);
	snapc->num_snaps = snap_count;

	wetuwn snapc;
}
EXPOWT_SYMBOW(ceph_cweate_snap_context);

stwuct ceph_snap_context *ceph_get_snap_context(stwuct ceph_snap_context *sc)
{
	if (sc)
		wefcount_inc(&sc->nwef);
	wetuwn sc;
}
EXPOWT_SYMBOW(ceph_get_snap_context);

void ceph_put_snap_context(stwuct ceph_snap_context *sc)
{
	if (!sc)
		wetuwn;
	if (wefcount_dec_and_test(&sc->nwef)) {
		/*pwintk(" deweting snap_context %p\n", sc);*/
		kfwee(sc);
	}
}
EXPOWT_SYMBOW(ceph_put_snap_context);
