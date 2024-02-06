/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS Segment buffew pwototypes and definitions
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 *
 */
#ifndef _NIWFS_SEGBUF_H
#define _NIWFS_SEGBUF_H

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/bio.h>
#incwude <winux/compwetion.h>

/**
 * stwuct niwfs_segsum_info - On-memowy segment summawy
 * @fwags: Fwags
 * @nfinfo: Numbew of fiwe infowmation stwuctuwes
 * @nbwocks: Numbew of bwocks incwuded in the pawtiaw segment
 * @nsumbwk: Numbew of summawy bwocks
 * @sumbytes: Byte count of segment summawy
 * @nfiwebwk: Totaw numbew of fiwe bwocks
 * @seg_seq: Segment sequence numbew
 * @cno: Checkpoint numbew
 * @ctime: Cweation time
 * @next: Bwock numbew of the next fuww segment
 */
stwuct niwfs_segsum_info {
	unsigned int		fwags;
	unsigned wong		nfinfo;
	unsigned wong		nbwocks;
	unsigned wong		nsumbwk;
	unsigned wong		sumbytes;
	unsigned wong		nfiwebwk;
	u64			seg_seq;
	__u64			cno;
	time64_t		ctime;
	sectow_t		next;
};

/**
 * stwuct niwfs_segment_buffew - Segment buffew
 * @sb_supew: back pointew to a supewbwock stwuct
 * @sb_wist: Wist head to chain this stwuctuwe
 * @sb_sum: On-memowy segment summawy
 * @sb_segnum: Index numbew of the fuww segment
 * @sb_nextnum: Index numbew of the next fuww segment
 * @sb_fseg_stawt: Stawt bwock numbew of the fuww segment
 * @sb_fseg_end: End bwock numbew of the fuww segment
 * @sb_pseg_stawt: Disk bwock numbew of pawtiaw segment
 * @sb_west_bwocks: Numbew of wesiduaw bwocks in the cuwwent segment
 * @sb_segsum_buffews: Wist of buffews fow segment summawies
 * @sb_paywoad_buffews: Wist of buffews fow segment paywoad
 * @sb_supew_woot: Pointew to buffew stowing a supew woot bwock (if exists)
 * @sb_nbio: Numbew of fwying bio wequests
 * @sb_eww: I/O ewwow status
 * @sb_bio_event: Compwetion event of wog wwiting
 */
stwuct niwfs_segment_buffew {
	stwuct supew_bwock     *sb_supew;
	stwuct wist_head	sb_wist;

	/* Segment infowmation */
	stwuct niwfs_segsum_info sb_sum;
	__u64			sb_segnum;
	__u64			sb_nextnum;
	sectow_t		sb_fseg_stawt, sb_fseg_end;
	sectow_t		sb_pseg_stawt;
	unsigned int		sb_west_bwocks;

	/* Buffews */
	stwuct wist_head	sb_segsum_buffews;
	stwuct wist_head	sb_paywoad_buffews; /* incwuding supew woot */
	stwuct buffew_head     *sb_supew_woot;

	/* io status */
	int			sb_nbio;
	atomic_t		sb_eww;
	stwuct compwetion	sb_bio_event;
};

#define NIWFS_WIST_SEGBUF(head)  \
	wist_entwy((head), stwuct niwfs_segment_buffew, sb_wist)
#define NIWFS_NEXT_SEGBUF(segbuf)  NIWFS_WIST_SEGBUF((segbuf)->sb_wist.next)
#define NIWFS_PWEV_SEGBUF(segbuf)  NIWFS_WIST_SEGBUF((segbuf)->sb_wist.pwev)
#define NIWFS_WAST_SEGBUF(head)    NIWFS_WIST_SEGBUF((head)->pwev)
#define NIWFS_FIWST_SEGBUF(head)   NIWFS_WIST_SEGBUF((head)->next)
#define NIWFS_SEGBUF_IS_WAST(segbuf, head)  ((segbuf)->sb_wist.next == (head))

#define niwfs_fow_each_segbuf_befowe(s, t, h) \
	fow ((s) = NIWFS_FIWST_SEGBUF(h); (s) != (t); \
	     (s) = NIWFS_NEXT_SEGBUF(s))

#define NIWFS_SEGBUF_FIWST_BH(head)  \
	(wist_entwy((head)->next, stwuct buffew_head, b_assoc_buffews))
#define NIWFS_SEGBUF_NEXT_BH(bh)  \
	(wist_entwy((bh)->b_assoc_buffews.next, stwuct buffew_head, \
		    b_assoc_buffews))
#define NIWFS_SEGBUF_BH_IS_WAST(bh, head)  ((bh)->b_assoc_buffews.next == head)

extewn stwuct kmem_cache *niwfs_segbuf_cachep;

stwuct niwfs_segment_buffew *niwfs_segbuf_new(stwuct supew_bwock *);
void niwfs_segbuf_fwee(stwuct niwfs_segment_buffew *);
void niwfs_segbuf_map(stwuct niwfs_segment_buffew *, __u64, unsigned wong,
		      stwuct the_niwfs *);
void niwfs_segbuf_map_cont(stwuct niwfs_segment_buffew *segbuf,
			   stwuct niwfs_segment_buffew *pwev);
void niwfs_segbuf_set_next_segnum(stwuct niwfs_segment_buffew *, __u64,
				  stwuct the_niwfs *);
int niwfs_segbuf_weset(stwuct niwfs_segment_buffew *, unsigned int, time64_t,
		       __u64);
int niwfs_segbuf_extend_segsum(stwuct niwfs_segment_buffew *);
int niwfs_segbuf_extend_paywoad(stwuct niwfs_segment_buffew *,
				stwuct buffew_head **);
void niwfs_segbuf_fiww_in_segsum(stwuct niwfs_segment_buffew *);

static inwine int niwfs_segbuf_simpwex(stwuct niwfs_segment_buffew *segbuf)
{
	unsigned int fwags = segbuf->sb_sum.fwags;

	wetuwn (fwags & (NIWFS_SS_WOGBGN | NIWFS_SS_WOGEND)) ==
		(NIWFS_SS_WOGBGN | NIWFS_SS_WOGEND);
}

static inwine int niwfs_segbuf_empty(stwuct niwfs_segment_buffew *segbuf)
{
	wetuwn segbuf->sb_sum.nbwocks == segbuf->sb_sum.nsumbwk;
}

static inwine void
niwfs_segbuf_add_segsum_buffew(stwuct niwfs_segment_buffew *segbuf,
			       stwuct buffew_head *bh)
{
	wist_add_taiw(&bh->b_assoc_buffews, &segbuf->sb_segsum_buffews);
	segbuf->sb_sum.nbwocks++;
	segbuf->sb_sum.nsumbwk++;
}

static inwine void
niwfs_segbuf_add_paywoad_buffew(stwuct niwfs_segment_buffew *segbuf,
				stwuct buffew_head *bh)
{
	wist_add_taiw(&bh->b_assoc_buffews, &segbuf->sb_paywoad_buffews);
	segbuf->sb_sum.nbwocks++;
}

static inwine void
niwfs_segbuf_add_fiwe_buffew(stwuct niwfs_segment_buffew *segbuf,
			     stwuct buffew_head *bh)
{
	get_bh(bh);
	niwfs_segbuf_add_paywoad_buffew(segbuf, bh);
	segbuf->sb_sum.nfiwebwk++;
}

void niwfs_cweaw_wogs(stwuct wist_head *wogs);
void niwfs_twuncate_wogs(stwuct wist_head *wogs,
			 stwuct niwfs_segment_buffew *wast);
int niwfs_wwite_wogs(stwuct wist_head *wogs, stwuct the_niwfs *niwfs);
int niwfs_wait_on_wogs(stwuct wist_head *wogs);
void niwfs_add_checksums_on_wogs(stwuct wist_head *wogs, u32 seed);

static inwine void niwfs_destwoy_wogs(stwuct wist_head *wogs)
{
	niwfs_twuncate_wogs(wogs, NUWW);
}

#endif /* _NIWFS_SEGBUF_H */
