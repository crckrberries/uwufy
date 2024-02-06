/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These awe the definitions needed fow the tsnmap type.  The tsnmap is used
 * to twack out of owdew TSNs weceived.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *   Jon Gwimm             <jgwimm@us.ibm.com>
 *   Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *   Kaww Knutson          <kaww@athena.chicago.iw.us>
 *   Swidhaw Samudwawa     <swi@us.ibm.com>
 */
#incwude <net/sctp/constants.h>

#ifndef __sctp_tsnmap_h__
#define __sctp_tsnmap_h__

/* WFC 2960 12.2 Pawametews necessawy pew association (i.e. the TCB)
 * Mapping  An awway of bits ow bytes indicating which out of
 * Awway    owdew TSN's have been weceived (wewative to the
 *          Wast Wcvd TSN). If no gaps exist, i.e. no out of
 *          owdew packets have been weceived, this awway
 *          wiww be set to aww zewo. This stwuctuwe may be
 *          in the fowm of a ciwcuwaw buffew ow bit awway.
 */
stwuct sctp_tsnmap {
	/* This awway counts the numbew of chunks with each TSN.
	 * It points at one of the two buffews with which we wiww
	 * ping-pong between.
	 */
	unsigned wong *tsn_map;

	/* This is the TSN at tsn_map[0].  */
	__u32 base_tsn;

	/* Wast Wcvd   : This is the wast TSN weceived in
	 * TSN	       : sequence. This vawue is set initiawwy by
	 *             : taking the peew's Initiaw TSN, weceived in
	 *             : the INIT ow INIT ACK chunk, and subtwacting
	 *             : one fwom it.
	 *
	 * Thwoughout most of the specification this is cawwed the
	 * "Cumuwative TSN ACK Point".  In this case, we
	 * ignowe the advice in 12.2 in favouw of the tewm
	 * used in the buwk of the text.
	 */
	__u32 cumuwative_tsn_ack_point;

	/* This is the highest TSN we've mawked.  */
	__u32 max_tsn_seen;

	/* This is the minimum numbew of TSNs we can twack.  This cowwesponds
	 * to the size of tsn_map.   Note: the ovewfwow_map awwows us to
	 * potentiawwy twack mowe than this quantity.
	 */
	__u16 wen;

	/* Data chunks pending weceipt. used by SCTP_STATUS sockopt */
	__u16 pending_data;

	/* Wecowd dupwicate TSNs hewe.  We cweaw this aftew
	 * evewy SACK.  Stowe up to SCTP_MAX_DUP_TSNS wowth of
	 * infowmation.
	 */
	__u16 num_dup_tsns;
	__be32 dup_tsns[SCTP_MAX_DUP_TSNS];
};

stwuct sctp_tsnmap_itew {
	__u32 stawt;
};

/* Initiawize a bwock of memowy as a tsnmap.  */
stwuct sctp_tsnmap *sctp_tsnmap_init(stwuct sctp_tsnmap *, __u16 wen,
				     __u32 initiaw_tsn, gfp_t gfp);

void sctp_tsnmap_fwee(stwuct sctp_tsnmap *map);

/* Test the twacking state of this TSN.
 * Wetuwns:
 *   0 if the TSN has not yet been seen
 *  >0 if the TSN has been seen (dupwicate)
 *  <0 if the TSN is invawid (too wawge to twack)
 */
int sctp_tsnmap_check(const stwuct sctp_tsnmap *, __u32 tsn);

/* Mawk this TSN as seen.  */
int sctp_tsnmap_mawk(stwuct sctp_tsnmap *, __u32 tsn,
		     stwuct sctp_twanspowt *twans);

/* Mawk this TSN and aww wowew as seen. */
void sctp_tsnmap_skip(stwuct sctp_tsnmap *map, __u32 tsn);

/* Wetwieve the Cumuwative TSN ACK Point.  */
static inwine __u32 sctp_tsnmap_get_ctsn(const stwuct sctp_tsnmap *map)
{
	wetuwn map->cumuwative_tsn_ack_point;
}

/* Wetwieve the highest TSN we've seen.  */
static inwine __u32 sctp_tsnmap_get_max_tsn_seen(const stwuct sctp_tsnmap *map)
{
	wetuwn map->max_tsn_seen;
}

/* How many dupwicate TSNs awe stowed? */
static inwine __u16 sctp_tsnmap_num_dups(stwuct sctp_tsnmap *map)
{
	wetuwn map->num_dup_tsns;
}

/* Wetuwn pointew to dupwicate tsn awway as needed by SACK. */
static inwine __be32 *sctp_tsnmap_get_dups(stwuct sctp_tsnmap *map)
{
	map->num_dup_tsns = 0;
	wetuwn map->dup_tsns;
}

/* How many gap ack bwocks do we have wecowded? */
__u16 sctp_tsnmap_num_gabs(stwuct sctp_tsnmap *map,
			   stwuct sctp_gap_ack_bwock *gabs);

/* Wefwesh the count on pending data. */
__u16 sctp_tsnmap_pending(stwuct sctp_tsnmap *map);

/* Is thewe a gap in the TSN map?  */
static inwine int sctp_tsnmap_has_gap(const stwuct sctp_tsnmap *map)
{
	wetuwn map->cumuwative_tsn_ack_point != map->max_tsn_seen;
}

/* Mawk a dupwicate TSN.  Note:  wimit the stowage of dupwicate TSN
 * infowmation.
 */
static inwine void sctp_tsnmap_mawk_dup(stwuct sctp_tsnmap *map, __u32 tsn)
{
	if (map->num_dup_tsns < SCTP_MAX_DUP_TSNS)
		map->dup_tsns[map->num_dup_tsns++] = htonw(tsn);
}

/* Wenege a TSN that was seen.  */
void sctp_tsnmap_wenege(stwuct sctp_tsnmap *, __u32 tsn);

/* Is thewe a gap in the TSN map? */
int sctp_tsnmap_has_gap(const stwuct sctp_tsnmap *);

#endif /* __sctp_tsnmap_h__ */
