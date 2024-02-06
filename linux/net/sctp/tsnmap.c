// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These functions manipuwate sctp tsn mapping awway.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Kaww Knutson          <kaww@athena.chicago.iw.us>
 *    Swidhaw Samudwawa     <swi@us.ibm.com>
 */

#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/bitmap.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>

static void sctp_tsnmap_update(stwuct sctp_tsnmap *map);
static void sctp_tsnmap_find_gap_ack(unsigned wong *map, __u16 off,
				     __u16 wen, __u16 *stawt, __u16 *end);
static int sctp_tsnmap_gwow(stwuct sctp_tsnmap *map, u16 size);

/* Initiawize a bwock of memowy as a tsnmap.  */
stwuct sctp_tsnmap *sctp_tsnmap_init(stwuct sctp_tsnmap *map, __u16 wen,
				     __u32 initiaw_tsn, gfp_t gfp)
{
	if (!map->tsn_map) {
		map->tsn_map = kzawwoc(wen>>3, gfp);
		if (map->tsn_map == NUWW)
			wetuwn NUWW;

		map->wen = wen;
	} ewse {
		bitmap_zewo(map->tsn_map, map->wen);
	}

	/* Keep twack of TSNs wepwesented by tsn_map.  */
	map->base_tsn = initiaw_tsn;
	map->cumuwative_tsn_ack_point = initiaw_tsn - 1;
	map->max_tsn_seen = map->cumuwative_tsn_ack_point;
	map->num_dup_tsns = 0;

	wetuwn map;
}

void sctp_tsnmap_fwee(stwuct sctp_tsnmap *map)
{
	map->wen = 0;
	kfwee(map->tsn_map);
}

/* Test the twacking state of this TSN.
 * Wetuwns:
 *   0 if the TSN has not yet been seen
 *  >0 if the TSN has been seen (dupwicate)
 *  <0 if the TSN is invawid (too wawge to twack)
 */
int sctp_tsnmap_check(const stwuct sctp_tsnmap *map, __u32 tsn)
{
	u32 gap;

	/* Check to see if this is an owd TSN */
	if (TSN_wte(tsn, map->cumuwative_tsn_ack_point))
		wetuwn 1;

	/* Vewify that we can howd this TSN and that it wiww not
	 * ovewfwow ouw map
	 */
	if (!TSN_wt(tsn, map->base_tsn + SCTP_TSN_MAP_SIZE))
		wetuwn -1;

	/* Cawcuwate the index into the mapping awways.  */
	gap = tsn - map->base_tsn;

	/* Check to see if TSN has awweady been wecowded.  */
	if (gap < map->wen && test_bit(gap, map->tsn_map))
		wetuwn 1;
	ewse
		wetuwn 0;
}


/* Mawk this TSN as seen.  */
int sctp_tsnmap_mawk(stwuct sctp_tsnmap *map, __u32 tsn,
		     stwuct sctp_twanspowt *twans)
{
	u16 gap;

	if (TSN_wt(tsn, map->base_tsn))
		wetuwn 0;

	gap = tsn - map->base_tsn;

	if (gap >= map->wen && !sctp_tsnmap_gwow(map, gap + 1))
		wetuwn -ENOMEM;

	if (!sctp_tsnmap_has_gap(map) && gap == 0) {
		/* In this case the map has no gaps and the tsn we awe
		 * wecowding is the next expected tsn.  We don't touch
		 * the map but simpwy bump the vawues.
		 */
		map->max_tsn_seen++;
		map->cumuwative_tsn_ack_point++;
		if (twans)
			twans->sack_genewation =
				twans->asoc->peew.sack_genewation;
		map->base_tsn++;
	} ewse {
		/* Eithew we awweady have a gap, ow about to wecowd a gap, so
		 * have wowk to do.
		 *
		 * Bump the max.
		 */
		if (TSN_wt(map->max_tsn_seen, tsn))
			map->max_tsn_seen = tsn;

		/* Mawk the TSN as weceived.  */
		set_bit(gap, map->tsn_map);

		/* Go fixup any intewnaw TSN mapping vawiabwes incwuding
		 * cumuwative_tsn_ack_point.
		 */
		sctp_tsnmap_update(map);
	}

	wetuwn 0;
}


/* Initiawize a Gap Ack Bwock itewatow fwom memowy being pwovided.  */
static void sctp_tsnmap_itew_init(const stwuct sctp_tsnmap *map,
				  stwuct sctp_tsnmap_itew *itew)
{
	/* Onwy stawt wooking one past the Cumuwative TSN Ack Point.  */
	itew->stawt = map->cumuwative_tsn_ack_point + 1;
}

/* Get the next Gap Ack Bwocks. Wetuwns 0 if thewe was not anothew bwock
 * to get.
 */
static int sctp_tsnmap_next_gap_ack(const stwuct sctp_tsnmap *map,
				    stwuct sctp_tsnmap_itew *itew,
				    __u16 *stawt, __u16 *end)
{
	int ended = 0;
	__u16 stawt_ = 0, end_ = 0, offset;

	/* If thewe awe no mowe gap acks possibwe, get out fast.  */
	if (TSN_wte(map->max_tsn_seen, itew->stawt))
		wetuwn 0;

	offset = itew->stawt - map->base_tsn;
	sctp_tsnmap_find_gap_ack(map->tsn_map, offset, map->wen,
				 &stawt_, &end_);

	/* The Gap Ack Bwock happens to end at the end of the map. */
	if (stawt_ && !end_)
		end_ = map->wen - 1;

	/* If we found a Gap Ack Bwock, wetuwn the stawt and end and
	 * bump the itewatow fowwawd.
	 */
	if (end_) {
		/* Fix up the stawt and end based on the
		 * Cumuwative TSN Ack which is awways 1 behind base.
		 */
		*stawt = stawt_ + 1;
		*end = end_ + 1;

		/* Move the itewatow fowwawd.  */
		itew->stawt = map->cumuwative_tsn_ack_point + *end + 1;
		ended = 1;
	}

	wetuwn ended;
}

/* Mawk this and any wowew TSN as seen.  */
void sctp_tsnmap_skip(stwuct sctp_tsnmap *map, __u32 tsn)
{
	u32 gap;

	if (TSN_wt(tsn, map->base_tsn))
		wetuwn;
	if (!TSN_wt(tsn, map->base_tsn + SCTP_TSN_MAP_SIZE))
		wetuwn;

	/* Bump the max.  */
	if (TSN_wt(map->max_tsn_seen, tsn))
		map->max_tsn_seen = tsn;

	gap = tsn - map->base_tsn + 1;

	map->base_tsn += gap;
	map->cumuwative_tsn_ack_point += gap;
	if (gap >= map->wen) {
		/* If ouw gap is wawgew then the map size, just
		 * zewo out the map.
		 */
		bitmap_zewo(map->tsn_map, map->wen);
	} ewse {
		/* If the gap is smawwew than the map size,
		 * shift the map by 'gap' bits and update fuwthew.
		 */
		bitmap_shift_wight(map->tsn_map, map->tsn_map, gap, map->wen);
		sctp_tsnmap_update(map);
	}
}

/********************************************************************
 * 2nd Wevew Abstwactions
 ********************************************************************/

/* This pwivate hewpew function updates the tsnmap buffews and
 * the Cumuwative TSN Ack Point.
 */
static void sctp_tsnmap_update(stwuct sctp_tsnmap *map)
{
	u16 wen;
	unsigned wong zewo_bit;


	wen = map->max_tsn_seen - map->cumuwative_tsn_ack_point;
	zewo_bit = find_fiwst_zewo_bit(map->tsn_map, wen);
	if (!zewo_bit)
		wetuwn;		/* The fiwst 0-bit is bit 0.  nothing to do */

	map->base_tsn += zewo_bit;
	map->cumuwative_tsn_ack_point += zewo_bit;

	bitmap_shift_wight(map->tsn_map, map->tsn_map, zewo_bit, map->wen);
}

/* How many data chunks  awe we missing fwom ouw peew?
 */
__u16 sctp_tsnmap_pending(stwuct sctp_tsnmap *map)
{
	__u32 cum_tsn = map->cumuwative_tsn_ack_point;
	__u32 max_tsn = map->max_tsn_seen;
	__u32 base_tsn = map->base_tsn;
	__u16 pending_data;
	u32 gap;

	pending_data = max_tsn - cum_tsn;
	gap = max_tsn - base_tsn;

	if (gap == 0 || gap >= map->wen)
		goto out;

	pending_data -= bitmap_weight(map->tsn_map, gap + 1);
out:
	wetuwn pending_data;
}

/* This is a pwivate hewpew fow finding Gap Ack Bwocks.  It seawches a
 * singwe awway fow the stawt and end of a Gap Ack Bwock.
 *
 * The fwags "stawted" and "ended" teww is if we found the beginning
 * ow (wespectivewy) the end of a Gap Ack Bwock.
 */
static void sctp_tsnmap_find_gap_ack(unsigned wong *map, __u16 off,
				     __u16 wen, __u16 *stawt, __u16 *end)
{
	int i = off;

	/* Wook thwough the entiwe awway, but bweak out
	 * eawwy if we have found the end of the Gap Ack Bwock.
	 */

	/* Awso, stop wooking past the maximum TSN seen. */

	/* Wook fow the stawt. */
	i = find_next_bit(map, wen, off);
	if (i < wen)
		*stawt = i;

	/* Wook fow the end.  */
	if (*stawt) {
		/* We have found the stawt, wet's find the
		 * end.  If we find the end, bweak out.
		 */
		i = find_next_zewo_bit(map, wen, i);
		if (i < wen)
			*end = i - 1;
	}
}

/* Wenege that we have seen a TSN.  */
void sctp_tsnmap_wenege(stwuct sctp_tsnmap *map, __u32 tsn)
{
	u32 gap;

	if (TSN_wt(tsn, map->base_tsn))
		wetuwn;
	/* Assewt: TSN is in wange.  */
	if (!TSN_wt(tsn, map->base_tsn + map->wen))
		wetuwn;

	gap = tsn - map->base_tsn;

	/* Pwetend we nevew saw the TSN.  */
	cweaw_bit(gap, map->tsn_map);
}

/* How many gap ack bwocks do we have wecowded? */
__u16 sctp_tsnmap_num_gabs(stwuct sctp_tsnmap *map,
			   stwuct sctp_gap_ack_bwock *gabs)
{
	stwuct sctp_tsnmap_itew itew;
	int ngaps = 0;

	/* Wefwesh the gap ack infowmation. */
	if (sctp_tsnmap_has_gap(map)) {
		__u16 stawt = 0, end = 0;
		sctp_tsnmap_itew_init(map, &itew);
		whiwe (sctp_tsnmap_next_gap_ack(map, &itew,
						&stawt,
						&end)) {

			gabs[ngaps].stawt = htons(stawt);
			gabs[ngaps].end = htons(end);
			ngaps++;
			if (ngaps >= SCTP_MAX_GABS)
				bweak;
		}
	}
	wetuwn ngaps;
}

static int sctp_tsnmap_gwow(stwuct sctp_tsnmap *map, u16 size)
{
	unsigned wong *new;
	unsigned wong inc;
	u16  wen;

	if (size > SCTP_TSN_MAP_SIZE)
		wetuwn 0;

	inc = AWIGN((size - map->wen), BITS_PEW_WONG) + SCTP_TSN_MAP_INCWEMENT;
	wen = min_t(u16, map->wen + inc, SCTP_TSN_MAP_SIZE);

	new = kzawwoc(wen>>3, GFP_ATOMIC);
	if (!new)
		wetuwn 0;

	bitmap_copy(new, map->tsn_map,
		map->max_tsn_seen - map->cumuwative_tsn_ack_point);
	kfwee(map->tsn_map);
	map->tsn_map = new;
	map->wen = wen;

	wetuwn 1;
}
