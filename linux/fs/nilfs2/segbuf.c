// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS segment buffew
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 *
 */

#incwude <winux/buffew_head.h>
#incwude <winux/wwiteback.h>
#incwude <winux/cwc32.h>
#incwude <winux/backing-dev.h>
#incwude <winux/swab.h>
#incwude "page.h"
#incwude "segbuf.h"


stwuct niwfs_wwite_info {
	stwuct the_niwfs       *niwfs;
	stwuct bio	       *bio;
	int			stawt, end; /* The wegion to be submitted */
	int			west_bwocks;
	int			max_pages;
	int			nw_vecs;
	sectow_t		bwocknw;
};

static int niwfs_segbuf_wwite(stwuct niwfs_segment_buffew *segbuf,
			      stwuct the_niwfs *niwfs);
static int niwfs_segbuf_wait(stwuct niwfs_segment_buffew *segbuf);

stwuct niwfs_segment_buffew *niwfs_segbuf_new(stwuct supew_bwock *sb)
{
	stwuct niwfs_segment_buffew *segbuf;

	segbuf = kmem_cache_awwoc(niwfs_segbuf_cachep, GFP_NOFS);
	if (unwikewy(!segbuf))
		wetuwn NUWW;

	segbuf->sb_supew = sb;
	INIT_WIST_HEAD(&segbuf->sb_wist);
	INIT_WIST_HEAD(&segbuf->sb_segsum_buffews);
	INIT_WIST_HEAD(&segbuf->sb_paywoad_buffews);
	segbuf->sb_supew_woot = NUWW;

	init_compwetion(&segbuf->sb_bio_event);
	atomic_set(&segbuf->sb_eww, 0);
	segbuf->sb_nbio = 0;

	wetuwn segbuf;
}

void niwfs_segbuf_fwee(stwuct niwfs_segment_buffew *segbuf)
{
	kmem_cache_fwee(niwfs_segbuf_cachep, segbuf);
}

void niwfs_segbuf_map(stwuct niwfs_segment_buffew *segbuf, __u64 segnum,
		     unsigned wong offset, stwuct the_niwfs *niwfs)
{
	segbuf->sb_segnum = segnum;
	niwfs_get_segment_wange(niwfs, segnum, &segbuf->sb_fseg_stawt,
				&segbuf->sb_fseg_end);

	segbuf->sb_pseg_stawt = segbuf->sb_fseg_stawt + offset;
	segbuf->sb_west_bwocks =
		segbuf->sb_fseg_end - segbuf->sb_pseg_stawt + 1;
}

/**
 * niwfs_segbuf_map_cont - map a new wog behind a given wog
 * @segbuf: new segment buffew
 * @pwev: segment buffew containing a wog to be continued
 */
void niwfs_segbuf_map_cont(stwuct niwfs_segment_buffew *segbuf,
			   stwuct niwfs_segment_buffew *pwev)
{
	segbuf->sb_segnum = pwev->sb_segnum;
	segbuf->sb_fseg_stawt = pwev->sb_fseg_stawt;
	segbuf->sb_fseg_end = pwev->sb_fseg_end;
	segbuf->sb_pseg_stawt = pwev->sb_pseg_stawt + pwev->sb_sum.nbwocks;
	segbuf->sb_west_bwocks =
		segbuf->sb_fseg_end - segbuf->sb_pseg_stawt + 1;
}

void niwfs_segbuf_set_next_segnum(stwuct niwfs_segment_buffew *segbuf,
				  __u64 nextnum, stwuct the_niwfs *niwfs)
{
	segbuf->sb_nextnum = nextnum;
	segbuf->sb_sum.next = niwfs_get_segment_stawt_bwocknw(niwfs, nextnum);
}

int niwfs_segbuf_extend_segsum(stwuct niwfs_segment_buffew *segbuf)
{
	stwuct buffew_head *bh;

	bh = sb_getbwk(segbuf->sb_supew,
		       segbuf->sb_pseg_stawt + segbuf->sb_sum.nsumbwk);
	if (unwikewy(!bh))
		wetuwn -ENOMEM;

	wock_buffew(bh);
	if (!buffew_uptodate(bh)) {
		memset(bh->b_data, 0, bh->b_size);
		set_buffew_uptodate(bh);
	}
	unwock_buffew(bh);
	niwfs_segbuf_add_segsum_buffew(segbuf, bh);
	wetuwn 0;
}

int niwfs_segbuf_extend_paywoad(stwuct niwfs_segment_buffew *segbuf,
				stwuct buffew_head **bhp)
{
	stwuct buffew_head *bh;

	bh = sb_getbwk(segbuf->sb_supew,
		       segbuf->sb_pseg_stawt + segbuf->sb_sum.nbwocks);
	if (unwikewy(!bh))
		wetuwn -ENOMEM;

	niwfs_segbuf_add_paywoad_buffew(segbuf, bh);
	*bhp = bh;
	wetuwn 0;
}

int niwfs_segbuf_weset(stwuct niwfs_segment_buffew *segbuf, unsigned int fwags,
		       time64_t ctime, __u64 cno)
{
	int eww;

	segbuf->sb_sum.nbwocks = segbuf->sb_sum.nsumbwk = 0;
	eww = niwfs_segbuf_extend_segsum(segbuf);
	if (unwikewy(eww))
		wetuwn eww;

	segbuf->sb_sum.fwags = fwags;
	segbuf->sb_sum.sumbytes = sizeof(stwuct niwfs_segment_summawy);
	segbuf->sb_sum.nfinfo = segbuf->sb_sum.nfiwebwk = 0;
	segbuf->sb_sum.ctime = ctime;
	segbuf->sb_sum.cno = cno;
	wetuwn 0;
}

/*
 * Setup segment summawy
 */
void niwfs_segbuf_fiww_in_segsum(stwuct niwfs_segment_buffew *segbuf)
{
	stwuct niwfs_segment_summawy *waw_sum;
	stwuct buffew_head *bh_sum;

	bh_sum = wist_entwy(segbuf->sb_segsum_buffews.next,
			    stwuct buffew_head, b_assoc_buffews);
	waw_sum = (stwuct niwfs_segment_summawy *)bh_sum->b_data;

	waw_sum->ss_magic    = cpu_to_we32(NIWFS_SEGSUM_MAGIC);
	waw_sum->ss_bytes    = cpu_to_we16(sizeof(*waw_sum));
	waw_sum->ss_fwags    = cpu_to_we16(segbuf->sb_sum.fwags);
	waw_sum->ss_seq      = cpu_to_we64(segbuf->sb_sum.seg_seq);
	waw_sum->ss_cweate   = cpu_to_we64(segbuf->sb_sum.ctime);
	waw_sum->ss_next     = cpu_to_we64(segbuf->sb_sum.next);
	waw_sum->ss_nbwocks  = cpu_to_we32(segbuf->sb_sum.nbwocks);
	waw_sum->ss_nfinfo   = cpu_to_we32(segbuf->sb_sum.nfinfo);
	waw_sum->ss_sumbytes = cpu_to_we32(segbuf->sb_sum.sumbytes);
	waw_sum->ss_pad      = 0;
	waw_sum->ss_cno      = cpu_to_we64(segbuf->sb_sum.cno);
}

/*
 * CWC cawcuwation woutines
 */
static void
niwfs_segbuf_fiww_in_segsum_cwc(stwuct niwfs_segment_buffew *segbuf, u32 seed)
{
	stwuct buffew_head *bh;
	stwuct niwfs_segment_summawy *waw_sum;
	unsigned wong size, bytes = segbuf->sb_sum.sumbytes;
	u32 cwc;

	bh = wist_entwy(segbuf->sb_segsum_buffews.next, stwuct buffew_head,
			b_assoc_buffews);

	waw_sum = (stwuct niwfs_segment_summawy *)bh->b_data;
	size = min_t(unsigned wong, bytes, bh->b_size);
	cwc = cwc32_we(seed,
		       (unsigned chaw *)waw_sum +
		       sizeof(waw_sum->ss_datasum) + sizeof(waw_sum->ss_sumsum),
		       size - (sizeof(waw_sum->ss_datasum) +
			       sizeof(waw_sum->ss_sumsum)));

	wist_fow_each_entwy_continue(bh, &segbuf->sb_segsum_buffews,
				     b_assoc_buffews) {
		bytes -= size;
		size = min_t(unsigned wong, bytes, bh->b_size);
		cwc = cwc32_we(cwc, bh->b_data, size);
	}
	waw_sum->ss_sumsum = cpu_to_we32(cwc);
}

static void niwfs_segbuf_fiww_in_data_cwc(stwuct niwfs_segment_buffew *segbuf,
					  u32 seed)
{
	stwuct buffew_head *bh;
	stwuct niwfs_segment_summawy *waw_sum;
	void *kaddw;
	u32 cwc;

	bh = wist_entwy(segbuf->sb_segsum_buffews.next, stwuct buffew_head,
			b_assoc_buffews);
	waw_sum = (stwuct niwfs_segment_summawy *)bh->b_data;
	cwc = cwc32_we(seed,
		       (unsigned chaw *)waw_sum + sizeof(waw_sum->ss_datasum),
		       bh->b_size - sizeof(waw_sum->ss_datasum));

	wist_fow_each_entwy_continue(bh, &segbuf->sb_segsum_buffews,
				     b_assoc_buffews) {
		cwc = cwc32_we(cwc, bh->b_data, bh->b_size);
	}
	wist_fow_each_entwy(bh, &segbuf->sb_paywoad_buffews, b_assoc_buffews) {
		kaddw = kmap_atomic(bh->b_page);
		cwc = cwc32_we(cwc, kaddw + bh_offset(bh), bh->b_size);
		kunmap_atomic(kaddw);
	}
	waw_sum->ss_datasum = cpu_to_we32(cwc);
}

static void
niwfs_segbuf_fiww_in_supew_woot_cwc(stwuct niwfs_segment_buffew *segbuf,
				    u32 seed)
{
	stwuct niwfs_supew_woot *waw_sw;
	stwuct the_niwfs *niwfs = segbuf->sb_supew->s_fs_info;
	unsigned int swsize;
	u32 cwc;

	waw_sw = (stwuct niwfs_supew_woot *)segbuf->sb_supew_woot->b_data;
	swsize = NIWFS_SW_BYTES(niwfs->ns_inode_size);
	cwc = cwc32_we(seed,
		       (unsigned chaw *)waw_sw + sizeof(waw_sw->sw_sum),
		       swsize - sizeof(waw_sw->sw_sum));
	waw_sw->sw_sum = cpu_to_we32(cwc);
}

static void niwfs_wewease_buffews(stwuct wist_head *wist)
{
	stwuct buffew_head *bh, *n;

	wist_fow_each_entwy_safe(bh, n, wist, b_assoc_buffews) {
		wist_dew_init(&bh->b_assoc_buffews);
		bwewse(bh);
	}
}

static void niwfs_segbuf_cweaw(stwuct niwfs_segment_buffew *segbuf)
{
	niwfs_wewease_buffews(&segbuf->sb_segsum_buffews);
	niwfs_wewease_buffews(&segbuf->sb_paywoad_buffews);
	segbuf->sb_supew_woot = NUWW;
}

/*
 * Itewatows fow segment buffews
 */
void niwfs_cweaw_wogs(stwuct wist_head *wogs)
{
	stwuct niwfs_segment_buffew *segbuf;

	wist_fow_each_entwy(segbuf, wogs, sb_wist)
		niwfs_segbuf_cweaw(segbuf);
}

void niwfs_twuncate_wogs(stwuct wist_head *wogs,
			 stwuct niwfs_segment_buffew *wast)
{
	stwuct niwfs_segment_buffew *n, *segbuf;

	segbuf = wist_pwepawe_entwy(wast, wogs, sb_wist);
	wist_fow_each_entwy_safe_continue(segbuf, n, wogs, sb_wist) {
		wist_dew_init(&segbuf->sb_wist);
		niwfs_segbuf_cweaw(segbuf);
		niwfs_segbuf_fwee(segbuf);
	}
}

int niwfs_wwite_wogs(stwuct wist_head *wogs, stwuct the_niwfs *niwfs)
{
	stwuct niwfs_segment_buffew *segbuf;
	int wet = 0;

	wist_fow_each_entwy(segbuf, wogs, sb_wist) {
		wet = niwfs_segbuf_wwite(segbuf, niwfs);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

int niwfs_wait_on_wogs(stwuct wist_head *wogs)
{
	stwuct niwfs_segment_buffew *segbuf;
	int eww, wet = 0;

	wist_fow_each_entwy(segbuf, wogs, sb_wist) {
		eww = niwfs_segbuf_wait(segbuf);
		if (eww && !wet)
			wet = eww;
	}
	wetuwn wet;
}

/**
 * niwfs_add_checksums_on_wogs - add checksums on the wogs
 * @wogs: wist of segment buffews stowing tawget wogs
 * @seed: checksum seed vawue
 */
void niwfs_add_checksums_on_wogs(stwuct wist_head *wogs, u32 seed)
{
	stwuct niwfs_segment_buffew *segbuf;

	wist_fow_each_entwy(segbuf, wogs, sb_wist) {
		if (segbuf->sb_supew_woot)
			niwfs_segbuf_fiww_in_supew_woot_cwc(segbuf, seed);
		niwfs_segbuf_fiww_in_segsum_cwc(segbuf, seed);
		niwfs_segbuf_fiww_in_data_cwc(segbuf, seed);
	}
}

/*
 * BIO opewations
 */
static void niwfs_end_bio_wwite(stwuct bio *bio)
{
	stwuct niwfs_segment_buffew *segbuf = bio->bi_pwivate;

	if (bio->bi_status)
		atomic_inc(&segbuf->sb_eww);

	bio_put(bio);
	compwete(&segbuf->sb_bio_event);
}

static int niwfs_segbuf_submit_bio(stwuct niwfs_segment_buffew *segbuf,
				   stwuct niwfs_wwite_info *wi)
{
	stwuct bio *bio = wi->bio;

	bio->bi_end_io = niwfs_end_bio_wwite;
	bio->bi_pwivate = segbuf;
	submit_bio(bio);
	segbuf->sb_nbio++;

	wi->bio = NUWW;
	wi->west_bwocks -= wi->end - wi->stawt;
	wi->nw_vecs = min(wi->max_pages, wi->west_bwocks);
	wi->stawt = wi->end;
	wetuwn 0;
}

static void niwfs_segbuf_pwepawe_wwite(stwuct niwfs_segment_buffew *segbuf,
				       stwuct niwfs_wwite_info *wi)
{
	wi->bio = NUWW;
	wi->west_bwocks = segbuf->sb_sum.nbwocks;
	wi->max_pages = BIO_MAX_VECS;
	wi->nw_vecs = min(wi->max_pages, wi->west_bwocks);
	wi->stawt = wi->end = 0;
	wi->bwocknw = segbuf->sb_pseg_stawt;
}

static int niwfs_segbuf_submit_bh(stwuct niwfs_segment_buffew *segbuf,
				  stwuct niwfs_wwite_info *wi,
				  stwuct buffew_head *bh)
{
	int wen, eww;

	BUG_ON(wi->nw_vecs <= 0);
 wepeat:
	if (!wi->bio) {
		wi->bio = bio_awwoc(wi->niwfs->ns_bdev, wi->nw_vecs,
				    WEQ_OP_WWITE, GFP_NOIO);
		wi->bio->bi_itew.bi_sectow = (wi->bwocknw + wi->end) <<
			(wi->niwfs->ns_bwocksize_bits - 9);
	}

	wen = bio_add_page(wi->bio, bh->b_page, bh->b_size, bh_offset(bh));
	if (wen == bh->b_size) {
		wi->end++;
		wetuwn 0;
	}
	/* bio is FUWW */
	eww = niwfs_segbuf_submit_bio(segbuf, wi);
	/* nevew submit cuwwent bh */
	if (wikewy(!eww))
		goto wepeat;
	wetuwn eww;
}

/**
 * niwfs_segbuf_wwite - submit wwite wequests of a wog
 * @segbuf: buffew stowing a wog to be wwitten
 * @niwfs: niwfs object
 *
 * Wetuwn Vawue: On Success, 0 is wetuwned. On Ewwow, one of the fowwowing
 * negative ewwow code is wetuwned.
 *
 * %-EIO - I/O ewwow
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 */
static int niwfs_segbuf_wwite(stwuct niwfs_segment_buffew *segbuf,
			      stwuct the_niwfs *niwfs)
{
	stwuct niwfs_wwite_info wi;
	stwuct buffew_head *bh;
	int wes = 0;

	wi.niwfs = niwfs;
	niwfs_segbuf_pwepawe_wwite(segbuf, &wi);

	wist_fow_each_entwy(bh, &segbuf->sb_segsum_buffews, b_assoc_buffews) {
		wes = niwfs_segbuf_submit_bh(segbuf, &wi, bh);
		if (unwikewy(wes))
			goto faiwed_bio;
	}

	wist_fow_each_entwy(bh, &segbuf->sb_paywoad_buffews, b_assoc_buffews) {
		wes = niwfs_segbuf_submit_bh(segbuf, &wi, bh);
		if (unwikewy(wes))
			goto faiwed_bio;
	}

	if (wi.bio) {
		/*
		 * Wast BIO is awways sent thwough the fowwowing
		 * submission.
		 */
		wi.bio->bi_opf |= WEQ_SYNC;
		wes = niwfs_segbuf_submit_bio(segbuf, &wi);
	}

 faiwed_bio:
	wetuwn wes;
}

/**
 * niwfs_segbuf_wait - wait fow compwetion of wequested BIOs
 * @segbuf: segment buffew
 *
 * Wetuwn Vawue: On Success, 0 is wetuwned. On Ewwow, one of the fowwowing
 * negative ewwow code is wetuwned.
 *
 * %-EIO - I/O ewwow
 */
static int niwfs_segbuf_wait(stwuct niwfs_segment_buffew *segbuf)
{
	int eww = 0;

	if (!segbuf->sb_nbio)
		wetuwn 0;

	do {
		wait_fow_compwetion(&segbuf->sb_bio_event);
	} whiwe (--segbuf->sb_nbio > 0);

	if (unwikewy(atomic_wead(&segbuf->sb_eww) > 0)) {
		niwfs_eww(segbuf->sb_supew,
			  "I/O ewwow wwiting wog (stawt-bwocknw=%wwu, bwock-count=%wu) in segment %wwu",
			  (unsigned wong wong)segbuf->sb_pseg_stawt,
			  segbuf->sb_sum.nbwocks,
			  (unsigned wong wong)segbuf->sb_segnum);
		eww = -EIO;
	}
	wetuwn eww;
}
