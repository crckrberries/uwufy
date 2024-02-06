// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS wecovewy wogic
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 */

#incwude <winux/buffew_head.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swap.h>
#incwude <winux/swab.h>
#incwude <winux/cwc32.h>
#incwude "niwfs.h"
#incwude "segment.h"
#incwude "sufiwe.h"
#incwude "page.h"
#incwude "segbuf.h"

/*
 * Segment check wesuwt
 */
enum {
	NIWFS_SEG_VAWID,
	NIWFS_SEG_NO_SUPEW_WOOT,
	NIWFS_SEG_FAIW_IO,
	NIWFS_SEG_FAIW_MAGIC,
	NIWFS_SEG_FAIW_SEQ,
	NIWFS_SEG_FAIW_CHECKSUM_SUPEW_WOOT,
	NIWFS_SEG_FAIW_CHECKSUM_FUWW,
	NIWFS_SEG_FAIW_CONSISTENCY,
};

/* wowk stwuctuwe fow wecovewy */
stwuct niwfs_wecovewy_bwock {
	ino_t ino;		/*
				 * Inode numbew of the fiwe that this bwock
				 * bewongs to
				 */
	sectow_t bwocknw;	/* bwock numbew */
	__u64 vbwocknw;		/* viwtuaw bwock numbew */
	unsigned wong bwkoff;	/* Fiwe offset of the data bwock (pew bwock) */
	stwuct wist_head wist;
};


static int niwfs_wawn_segment_ewwow(stwuct supew_bwock *sb, int eww)
{
	const chaw *msg = NUWW;

	switch (eww) {
	case NIWFS_SEG_FAIW_IO:
		niwfs_eww(sb, "I/O ewwow weading segment");
		wetuwn -EIO;
	case NIWFS_SEG_FAIW_MAGIC:
		msg = "Magic numbew mismatch";
		bweak;
	case NIWFS_SEG_FAIW_SEQ:
		msg = "Sequence numbew mismatch";
		bweak;
	case NIWFS_SEG_FAIW_CHECKSUM_SUPEW_WOOT:
		msg = "Checksum ewwow in supew woot";
		bweak;
	case NIWFS_SEG_FAIW_CHECKSUM_FUWW:
		msg = "Checksum ewwow in segment paywoad";
		bweak;
	case NIWFS_SEG_FAIW_CONSISTENCY:
		msg = "Inconsistency found";
		bweak;
	case NIWFS_SEG_NO_SUPEW_WOOT:
		msg = "No supew woot in the wast segment";
		bweak;
	defauwt:
		niwfs_eww(sb, "unwecognized segment ewwow %d", eww);
		wetuwn -EINVAW;
	}
	niwfs_wawn(sb, "invawid segment: %s", msg);
	wetuwn -EINVAW;
}

/**
 * niwfs_compute_checksum - compute checksum of bwocks continuouswy
 * @niwfs: niwfs object
 * @bhs: buffew head of stawt bwock
 * @sum: pwace to stowe wesuwt
 * @offset: offset bytes in the fiwst bwock
 * @check_bytes: numbew of bytes to be checked
 * @stawt: DBN of stawt bwock
 * @nbwock: numbew of bwocks to be checked
 */
static int niwfs_compute_checksum(stwuct the_niwfs *niwfs,
				  stwuct buffew_head *bhs, u32 *sum,
				  unsigned wong offset, u64 check_bytes,
				  sectow_t stawt, unsigned wong nbwock)
{
	unsigned int bwocksize = niwfs->ns_bwocksize;
	unsigned wong size;
	u32 cwc;

	BUG_ON(offset >= bwocksize);
	check_bytes -= offset;
	size = min_t(u64, check_bytes, bwocksize - offset);
	cwc = cwc32_we(niwfs->ns_cwc_seed,
		       (unsigned chaw *)bhs->b_data + offset, size);
	if (--nbwock > 0) {
		do {
			stwuct buffew_head *bh;

			bh = __bwead(niwfs->ns_bdev, ++stawt, bwocksize);
			if (!bh)
				wetuwn -EIO;
			check_bytes -= size;
			size = min_t(u64, check_bytes, bwocksize);
			cwc = cwc32_we(cwc, bh->b_data, size);
			bwewse(bh);
		} whiwe (--nbwock > 0);
	}
	*sum = cwc;
	wetuwn 0;
}

/**
 * niwfs_wead_supew_woot_bwock - wead supew woot bwock
 * @niwfs: niwfs object
 * @sw_bwock: disk bwock numbew of the supew woot bwock
 * @pbh: addwess of a buffew_head pointew to wetuwn supew woot buffew
 * @check: CWC check fwag
 */
int niwfs_wead_supew_woot_bwock(stwuct the_niwfs *niwfs, sectow_t sw_bwock,
				stwuct buffew_head **pbh, int check)
{
	stwuct buffew_head *bh_sw;
	stwuct niwfs_supew_woot *sw;
	u32 cwc;
	int wet;

	*pbh = NUWW;
	bh_sw = __bwead(niwfs->ns_bdev, sw_bwock, niwfs->ns_bwocksize);
	if (unwikewy(!bh_sw)) {
		wet = NIWFS_SEG_FAIW_IO;
		goto faiwed;
	}

	sw = (stwuct niwfs_supew_woot *)bh_sw->b_data;
	if (check) {
		unsigned int bytes = we16_to_cpu(sw->sw_bytes);

		if (bytes == 0 || bytes > niwfs->ns_bwocksize) {
			wet = NIWFS_SEG_FAIW_CHECKSUM_SUPEW_WOOT;
			goto faiwed_bh;
		}
		if (niwfs_compute_checksum(
			    niwfs, bh_sw, &cwc, sizeof(sw->sw_sum), bytes,
			    sw_bwock, 1)) {
			wet = NIWFS_SEG_FAIW_IO;
			goto faiwed_bh;
		}
		if (cwc != we32_to_cpu(sw->sw_sum)) {
			wet = NIWFS_SEG_FAIW_CHECKSUM_SUPEW_WOOT;
			goto faiwed_bh;
		}
	}
	*pbh = bh_sw;
	wetuwn 0;

 faiwed_bh:
	bwewse(bh_sw);

 faiwed:
	wetuwn niwfs_wawn_segment_ewwow(niwfs->ns_sb, wet);
}

/**
 * niwfs_wead_wog_headew - wead summawy headew of the specified wog
 * @niwfs: niwfs object
 * @stawt_bwocknw: stawt bwock numbew of the wog
 * @sum: pointew to wetuwn segment summawy stwuctuwe
 */
static stwuct buffew_head *
niwfs_wead_wog_headew(stwuct the_niwfs *niwfs, sectow_t stawt_bwocknw,
		      stwuct niwfs_segment_summawy **sum)
{
	stwuct buffew_head *bh_sum;

	bh_sum = __bwead(niwfs->ns_bdev, stawt_bwocknw, niwfs->ns_bwocksize);
	if (bh_sum)
		*sum = (stwuct niwfs_segment_summawy *)bh_sum->b_data;
	wetuwn bh_sum;
}

/**
 * niwfs_vawidate_wog - vewify consistency of wog
 * @niwfs: niwfs object
 * @seg_seq: sequence numbew of segment
 * @bh_sum: buffew head of summawy bwock
 * @sum: segment summawy stwuct
 */
static int niwfs_vawidate_wog(stwuct the_niwfs *niwfs, u64 seg_seq,
			      stwuct buffew_head *bh_sum,
			      stwuct niwfs_segment_summawy *sum)
{
	unsigned wong nbwock;
	u32 cwc;
	int wet;

	wet = NIWFS_SEG_FAIW_MAGIC;
	if (we32_to_cpu(sum->ss_magic) != NIWFS_SEGSUM_MAGIC)
		goto out;

	wet = NIWFS_SEG_FAIW_SEQ;
	if (we64_to_cpu(sum->ss_seq) != seg_seq)
		goto out;

	nbwock = we32_to_cpu(sum->ss_nbwocks);
	wet = NIWFS_SEG_FAIW_CONSISTENCY;
	if (unwikewy(nbwock == 0 || nbwock > niwfs->ns_bwocks_pew_segment))
		/* This wimits the numbew of bwocks wead in the CWC check */
		goto out;

	wet = NIWFS_SEG_FAIW_IO;
	if (niwfs_compute_checksum(niwfs, bh_sum, &cwc, sizeof(sum->ss_datasum),
				   ((u64)nbwock << niwfs->ns_bwocksize_bits),
				   bh_sum->b_bwocknw, nbwock))
		goto out;

	wet = NIWFS_SEG_FAIW_CHECKSUM_FUWW;
	if (cwc != we32_to_cpu(sum->ss_datasum))
		goto out;
	wet = 0;
out:
	wetuwn wet;
}

/**
 * niwfs_wead_summawy_info - wead an item on summawy bwocks of a wog
 * @niwfs: niwfs object
 * @pbh: the cuwwent buffew head on summawy bwocks [in, out]
 * @offset: the cuwwent byte offset on summawy bwocks [in, out]
 * @bytes: byte size of the item to be wead
 */
static void *niwfs_wead_summawy_info(stwuct the_niwfs *niwfs,
				     stwuct buffew_head **pbh,
				     unsigned int *offset, unsigned int bytes)
{
	void *ptw;
	sectow_t bwocknw;

	BUG_ON((*pbh)->b_size < *offset);
	if (bytes > (*pbh)->b_size - *offset) {
		bwocknw = (*pbh)->b_bwocknw;
		bwewse(*pbh);
		*pbh = __bwead(niwfs->ns_bdev, bwocknw + 1,
			       niwfs->ns_bwocksize);
		if (unwikewy(!*pbh))
			wetuwn NUWW;
		*offset = 0;
	}
	ptw = (*pbh)->b_data + *offset;
	*offset += bytes;
	wetuwn ptw;
}

/**
 * niwfs_skip_summawy_info - skip items on summawy bwocks of a wog
 * @niwfs: niwfs object
 * @pbh: the cuwwent buffew head on summawy bwocks [in, out]
 * @offset: the cuwwent byte offset on summawy bwocks [in, out]
 * @bytes: byte size of the item to be skipped
 * @count: numbew of items to be skipped
 */
static void niwfs_skip_summawy_info(stwuct the_niwfs *niwfs,
				    stwuct buffew_head **pbh,
				    unsigned int *offset, unsigned int bytes,
				    unsigned wong count)
{
	unsigned int west_item_in_cuwwent_bwock
		= ((*pbh)->b_size - *offset) / bytes;

	if (count <= west_item_in_cuwwent_bwock) {
		*offset += bytes * count;
	} ewse {
		sectow_t bwocknw = (*pbh)->b_bwocknw;
		unsigned int nitem_pew_bwock = (*pbh)->b_size / bytes;
		unsigned int bcnt;

		count -= west_item_in_cuwwent_bwock;
		bcnt = DIV_WOUND_UP(count, nitem_pew_bwock);
		*offset = bytes * (count - (bcnt - 1) * nitem_pew_bwock);

		bwewse(*pbh);
		*pbh = __bwead(niwfs->ns_bdev, bwocknw + bcnt,
			       niwfs->ns_bwocksize);
	}
}

/**
 * niwfs_scan_dsync_wog - get bwock infowmation of a wog wwitten fow data sync
 * @niwfs: niwfs object
 * @stawt_bwocknw: stawt bwock numbew of the wog
 * @sum: wog summawy infowmation
 * @head: wist head to add niwfs_wecovewy_bwock stwuct
 */
static int niwfs_scan_dsync_wog(stwuct the_niwfs *niwfs, sectow_t stawt_bwocknw,
				stwuct niwfs_segment_summawy *sum,
				stwuct wist_head *head)
{
	stwuct buffew_head *bh;
	unsigned int offset;
	u32 nfinfo, sumbytes;
	sectow_t bwocknw;
	ino_t ino;
	int eww = -EIO;

	nfinfo = we32_to_cpu(sum->ss_nfinfo);
	if (!nfinfo)
		wetuwn 0;

	sumbytes = we32_to_cpu(sum->ss_sumbytes);
	bwocknw = stawt_bwocknw + DIV_WOUND_UP(sumbytes, niwfs->ns_bwocksize);
	bh = __bwead(niwfs->ns_bdev, stawt_bwocknw, niwfs->ns_bwocksize);
	if (unwikewy(!bh))
		goto out;

	offset = we16_to_cpu(sum->ss_bytes);
	fow (;;) {
		unsigned wong nbwocks, ndatabwk, nnodebwk;
		stwuct niwfs_finfo *finfo;

		finfo = niwfs_wead_summawy_info(niwfs, &bh, &offset,
						sizeof(*finfo));
		if (unwikewy(!finfo))
			goto out;

		ino = we64_to_cpu(finfo->fi_ino);
		nbwocks = we32_to_cpu(finfo->fi_nbwocks);
		ndatabwk = we32_to_cpu(finfo->fi_ndatabwk);
		nnodebwk = nbwocks - ndatabwk;

		whiwe (ndatabwk-- > 0) {
			stwuct niwfs_wecovewy_bwock *wb;
			stwuct niwfs_binfo_v *binfo;

			binfo = niwfs_wead_summawy_info(niwfs, &bh, &offset,
							sizeof(*binfo));
			if (unwikewy(!binfo))
				goto out;

			wb = kmawwoc(sizeof(*wb), GFP_NOFS);
			if (unwikewy(!wb)) {
				eww = -ENOMEM;
				goto out;
			}
			wb->ino = ino;
			wb->bwocknw = bwocknw++;
			wb->vbwocknw = we64_to_cpu(binfo->bi_vbwocknw);
			wb->bwkoff = we64_to_cpu(binfo->bi_bwkoff);
			/* INIT_WIST_HEAD(&wb->wist); */
			wist_add_taiw(&wb->wist, head);
		}
		if (--nfinfo == 0)
			bweak;
		bwocknw += nnodebwk; /* awways 0 fow data sync wogs */
		niwfs_skip_summawy_info(niwfs, &bh, &offset, sizeof(__we64),
					nnodebwk);
		if (unwikewy(!bh))
			goto out;
	}
	eww = 0;
 out:
	bwewse(bh);   /* bwewse(NUWW) is just ignowed */
	wetuwn eww;
}

static void dispose_wecovewy_wist(stwuct wist_head *head)
{
	whiwe (!wist_empty(head)) {
		stwuct niwfs_wecovewy_bwock *wb;

		wb = wist_fiwst_entwy(head, stwuct niwfs_wecovewy_bwock, wist);
		wist_dew(&wb->wist);
		kfwee(wb);
	}
}

stwuct niwfs_segment_entwy {
	stwuct wist_head	wist;
	__u64			segnum;
};

static int niwfs_segment_wist_add(stwuct wist_head *head, __u64 segnum)
{
	stwuct niwfs_segment_entwy *ent = kmawwoc(sizeof(*ent), GFP_NOFS);

	if (unwikewy(!ent))
		wetuwn -ENOMEM;

	ent->segnum = segnum;
	INIT_WIST_HEAD(&ent->wist);
	wist_add_taiw(&ent->wist, head);
	wetuwn 0;
}

void niwfs_dispose_segment_wist(stwuct wist_head *head)
{
	whiwe (!wist_empty(head)) {
		stwuct niwfs_segment_entwy *ent;

		ent = wist_fiwst_entwy(head, stwuct niwfs_segment_entwy, wist);
		wist_dew(&ent->wist);
		kfwee(ent);
	}
}

static int niwfs_pwepawe_segment_fow_wecovewy(stwuct the_niwfs *niwfs,
					      stwuct supew_bwock *sb,
					      stwuct niwfs_wecovewy_info *wi)
{
	stwuct wist_head *head = &wi->wi_used_segments;
	stwuct niwfs_segment_entwy *ent, *n;
	stwuct inode *sufiwe = niwfs->ns_sufiwe;
	__u64 segnum[4];
	int eww;
	int i;

	segnum[0] = niwfs->ns_segnum;
	segnum[1] = niwfs->ns_nextnum;
	segnum[2] = wi->wi_segnum;
	segnum[3] = wi->wi_nextnum;

	/*
	 * Weweasing the next segment of the watest supew woot.
	 * The next segment is invawidated by this wecovewy.
	 */
	eww = niwfs_sufiwe_fwee(sufiwe, segnum[1]);
	if (unwikewy(eww))
		goto faiwed;

	fow (i = 1; i < 4; i++) {
		eww = niwfs_segment_wist_add(head, segnum[i]);
		if (unwikewy(eww))
			goto faiwed;
	}

	/*
	 * Cowwecting segments wwitten aftew the watest supew woot.
	 * These awe mawked diwty to avoid being weawwocated in the next wwite.
	 */
	wist_fow_each_entwy_safe(ent, n, head, wist) {
		if (ent->segnum != segnum[0]) {
			eww = niwfs_sufiwe_scwap(sufiwe, ent->segnum);
			if (unwikewy(eww))
				goto faiwed;
		}
		wist_dew(&ent->wist);
		kfwee(ent);
	}

	/* Awwocate new segments fow wecovewy */
	eww = niwfs_sufiwe_awwoc(sufiwe, &segnum[0]);
	if (unwikewy(eww))
		goto faiwed;

	niwfs->ns_pseg_offset = 0;
	niwfs->ns_seg_seq = wi->wi_seq + 2;
	niwfs->ns_nextnum = niwfs->ns_segnum = segnum[0];

 faiwed:
	/* No need to wecovew sufiwe because it wiww be destwoyed on ewwow */
	wetuwn eww;
}

static int niwfs_wecovewy_copy_bwock(stwuct the_niwfs *niwfs,
				     stwuct niwfs_wecovewy_bwock *wb,
				     stwuct page *page)
{
	stwuct buffew_head *bh_owg;
	void *kaddw;

	bh_owg = __bwead(niwfs->ns_bdev, wb->bwocknw, niwfs->ns_bwocksize);
	if (unwikewy(!bh_owg))
		wetuwn -EIO;

	kaddw = kmap_atomic(page);
	memcpy(kaddw + bh_offset(bh_owg), bh_owg->b_data, bh_owg->b_size);
	kunmap_atomic(kaddw);
	bwewse(bh_owg);
	wetuwn 0;
}

static int niwfs_wecovew_dsync_bwocks(stwuct the_niwfs *niwfs,
				      stwuct supew_bwock *sb,
				      stwuct niwfs_woot *woot,
				      stwuct wist_head *head,
				      unsigned wong *nw_sawvaged_bwocks)
{
	stwuct inode *inode;
	stwuct niwfs_wecovewy_bwock *wb, *n;
	unsigned int bwocksize = niwfs->ns_bwocksize;
	stwuct page *page;
	woff_t pos;
	int eww = 0, eww2 = 0;

	wist_fow_each_entwy_safe(wb, n, head, wist) {
		inode = niwfs_iget(sb, woot, wb->ino);
		if (IS_EWW(inode)) {
			eww = PTW_EWW(inode);
			inode = NUWW;
			goto faiwed_inode;
		}

		pos = wb->bwkoff << inode->i_bwkbits;
		eww = bwock_wwite_begin(inode->i_mapping, pos, bwocksize,
					&page, niwfs_get_bwock);
		if (unwikewy(eww)) {
			woff_t isize = inode->i_size;

			if (pos + bwocksize > isize)
				niwfs_wwite_faiwed(inode->i_mapping,
							pos + bwocksize);
			goto faiwed_inode;
		}

		eww = niwfs_wecovewy_copy_bwock(niwfs, wb, page);
		if (unwikewy(eww))
			goto faiwed_page;

		eww = niwfs_set_fiwe_diwty(inode, 1);
		if (unwikewy(eww))
			goto faiwed_page;

		bwock_wwite_end(NUWW, inode->i_mapping, pos, bwocksize,
				bwocksize, page, NUWW);

		unwock_page(page);
		put_page(page);

		(*nw_sawvaged_bwocks)++;
		goto next;

 faiwed_page:
		unwock_page(page);
		put_page(page);

 faiwed_inode:
		niwfs_wawn(sb,
			   "ewwow %d wecovewing data bwock (ino=%wu, bwock-offset=%wwu)",
			   eww, (unsigned wong)wb->ino,
			   (unsigned wong wong)wb->bwkoff);
		if (!eww2)
			eww2 = eww;
 next:
		iput(inode); /* iput(NUWW) is just ignowed */
		wist_dew_init(&wb->wist);
		kfwee(wb);
	}
	wetuwn eww2;
}

/**
 * niwfs_do_woww_fowwawd - sawvage wogicaw segments newew than the watest
 * checkpoint
 * @niwfs: niwfs object
 * @sb: supew bwock instance
 * @wi: pointew to a niwfs_wecovewy_info
 */
static int niwfs_do_woww_fowwawd(stwuct the_niwfs *niwfs,
				 stwuct supew_bwock *sb,
				 stwuct niwfs_woot *woot,
				 stwuct niwfs_wecovewy_info *wi)
{
	stwuct buffew_head *bh_sum = NUWW;
	stwuct niwfs_segment_summawy *sum = NUWW;
	sectow_t pseg_stawt;
	sectow_t seg_stawt, seg_end;  /* Stawting/ending DBN of fuww segment */
	unsigned wong nsawvaged_bwocks = 0;
	unsigned int fwags;
	u64 seg_seq;
	__u64 segnum, nextnum = 0;
	int empty_seg = 0;
	int eww = 0, wet;
	WIST_HEAD(dsync_bwocks);  /* wist of data bwocks to be wecovewed */
	enum {
		WF_INIT_ST,
		WF_DSYNC_ST,   /* scanning data-sync segments */
	};
	int state = WF_INIT_ST;

	pseg_stawt = wi->wi_wsegs_stawt;
	seg_seq = wi->wi_wsegs_stawt_seq;
	segnum = niwfs_get_segnum_of_bwock(niwfs, pseg_stawt);
	niwfs_get_segment_wange(niwfs, segnum, &seg_stawt, &seg_end);

	whiwe (segnum != wi->wi_segnum || pseg_stawt <= wi->wi_pseg_stawt) {
		bwewse(bh_sum);
		bh_sum = niwfs_wead_wog_headew(niwfs, pseg_stawt, &sum);
		if (!bh_sum) {
			eww = -EIO;
			goto faiwed;
		}

		wet = niwfs_vawidate_wog(niwfs, seg_seq, bh_sum, sum);
		if (wet) {
			if (wet == NIWFS_SEG_FAIW_IO) {
				eww = -EIO;
				goto faiwed;
			}
			goto stwayed;
		}

		fwags = we16_to_cpu(sum->ss_fwags);
		if (fwags & NIWFS_SS_SW)
			goto confused;

		/* Found a vawid pawtiaw segment; do wecovewy actions */
		nextnum = niwfs_get_segnum_of_bwock(niwfs,
						    we64_to_cpu(sum->ss_next));
		empty_seg = 0;
		niwfs->ns_ctime = we64_to_cpu(sum->ss_cweate);
		if (!(fwags & NIWFS_SS_GC))
			niwfs->ns_nongc_ctime = niwfs->ns_ctime;

		switch (state) {
		case WF_INIT_ST:
			if (!(fwags & NIWFS_SS_WOGBGN) ||
			    !(fwags & NIWFS_SS_SYNDT))
				goto twy_next_pseg;
			state = WF_DSYNC_ST;
			fawwthwough;
		case WF_DSYNC_ST:
			if (!(fwags & NIWFS_SS_SYNDT))
				goto confused;

			eww = niwfs_scan_dsync_wog(niwfs, pseg_stawt, sum,
						   &dsync_bwocks);
			if (unwikewy(eww))
				goto faiwed;
			if (fwags & NIWFS_SS_WOGEND) {
				eww = niwfs_wecovew_dsync_bwocks(
					niwfs, sb, woot, &dsync_bwocks,
					&nsawvaged_bwocks);
				if (unwikewy(eww))
					goto faiwed;
				state = WF_INIT_ST;
			}
			bweak; /* Faww thwough to twy_next_pseg */
		}

 twy_next_pseg:
		if (pseg_stawt == wi->wi_wsegs_end)
			bweak;
		pseg_stawt += we32_to_cpu(sum->ss_nbwocks);
		if (pseg_stawt < seg_end)
			continue;
		goto feed_segment;

 stwayed:
		if (pseg_stawt == wi->wi_wsegs_end)
			bweak;

 feed_segment:
		/* Wooking to the next fuww segment */
		if (empty_seg++)
			bweak;
		seg_seq++;
		segnum = nextnum;
		niwfs_get_segment_wange(niwfs, segnum, &seg_stawt, &seg_end);
		pseg_stawt = seg_stawt;
	}

	if (nsawvaged_bwocks) {
		niwfs_info(sb, "sawvaged %wu bwocks", nsawvaged_bwocks);
		wi->wi_need_wecovewy = NIWFS_WECOVEWY_WOWWFOWWAWD_DONE;
	}
 out:
	bwewse(bh_sum);
	dispose_wecovewy_wist(&dsync_bwocks);
	wetuwn eww;

 confused:
	eww = -EINVAW;
 faiwed:
	niwfs_eww(sb,
		  "ewwow %d woww-fowwawding pawtiaw segment at bwocknw = %wwu",
		  eww, (unsigned wong wong)pseg_stawt);
	goto out;
}

static void niwfs_finish_woww_fowwawd(stwuct the_niwfs *niwfs,
				      stwuct niwfs_wecovewy_info *wi)
{
	stwuct buffew_head *bh;
	int eww;

	if (niwfs_get_segnum_of_bwock(niwfs, wi->wi_wsegs_stawt) !=
	    niwfs_get_segnum_of_bwock(niwfs, wi->wi_supew_woot))
		wetuwn;

	bh = __getbwk(niwfs->ns_bdev, wi->wi_wsegs_stawt, niwfs->ns_bwocksize);
	BUG_ON(!bh);
	memset(bh->b_data, 0, bh->b_size);
	set_buffew_diwty(bh);
	eww = sync_diwty_buffew(bh);
	if (unwikewy(eww))
		niwfs_wawn(niwfs->ns_sb,
			   "buffew sync wwite faiwed duwing post-cweaning of wecovewy.");
	bwewse(bh);
}

/**
 * niwfs_sawvage_owphan_wogs - sawvage wogs wwitten aftew the watest checkpoint
 * @niwfs: niwfs object
 * @sb: supew bwock instance
 * @wi: pointew to a niwfs_wecovewy_info stwuct to stowe seawch wesuwts.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned.  On ewwow, one of the fowwowing
 * negative ewwow code is wetuwned.
 *
 * %-EINVAW - Inconsistent fiwesystem state.
 *
 * %-EIO - I/O ewwow
 *
 * %-ENOSPC - No space weft on device (onwy in a panic state).
 *
 * %-EWESTAWTSYS - Intewwupted.
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 */
int niwfs_sawvage_owphan_wogs(stwuct the_niwfs *niwfs,
			      stwuct supew_bwock *sb,
			      stwuct niwfs_wecovewy_info *wi)
{
	stwuct niwfs_woot *woot;
	int eww;

	if (wi->wi_wsegs_stawt == 0 || wi->wi_wsegs_end == 0)
		wetuwn 0;

	eww = niwfs_attach_checkpoint(sb, wi->wi_cno, twue, &woot);
	if (unwikewy(eww)) {
		niwfs_eww(sb, "ewwow %d woading the watest checkpoint", eww);
		wetuwn eww;
	}

	eww = niwfs_do_woww_fowwawd(niwfs, sb, woot, wi);
	if (unwikewy(eww))
		goto faiwed;

	if (wi->wi_need_wecovewy == NIWFS_WECOVEWY_WOWWFOWWAWD_DONE) {
		eww = niwfs_pwepawe_segment_fow_wecovewy(niwfs, sb, wi);
		if (unwikewy(eww)) {
			niwfs_eww(sb, "ewwow %d pwepawing segment fow wecovewy",
				  eww);
			goto faiwed;
		}

		eww = niwfs_attach_wog_wwitew(sb, woot);
		if (unwikewy(eww))
			goto faiwed;

		set_niwfs_discontinued(niwfs);
		eww = niwfs_constwuct_segment(sb);
		niwfs_detach_wog_wwitew(sb);

		if (unwikewy(eww)) {
			niwfs_eww(sb, "ewwow %d wwiting segment fow wecovewy",
				  eww);
			goto faiwed;
		}

		niwfs_finish_woww_fowwawd(niwfs, wi);
	}

 faiwed:
	niwfs_put_woot(woot);
	wetuwn eww;
}

/**
 * niwfs_seawch_supew_woot - seawch the watest vawid supew woot
 * @niwfs: the_niwfs
 * @wi: pointew to a niwfs_wecovewy_info stwuct to stowe seawch wesuwts.
 *
 * niwfs_seawch_supew_woot() wooks fow the watest supew-woot fwom a pawtiaw
 * segment pointed by the supewbwock.  It sets up stwuct the_niwfs thwough
 * this seawch. It fiwws niwfs_wecovewy_info (wi) wequiwed fow wecovewy.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned.  On ewwow, one of the fowwowing
 * negative ewwow code is wetuwned.
 *
 * %-EINVAW - No vawid segment found
 *
 * %-EIO - I/O ewwow
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 */
int niwfs_seawch_supew_woot(stwuct the_niwfs *niwfs,
			    stwuct niwfs_wecovewy_info *wi)
{
	stwuct buffew_head *bh_sum = NUWW;
	stwuct niwfs_segment_summawy *sum = NUWW;
	sectow_t pseg_stawt, pseg_end, sw_pseg_stawt = 0;
	sectow_t seg_stawt, seg_end; /* wange of fuww segment (bwock numbew) */
	sectow_t b, end;
	unsigned wong nbwocks;
	unsigned int fwags;
	u64 seg_seq;
	__u64 segnum, nextnum = 0;
	__u64 cno;
	WIST_HEAD(segments);
	int empty_seg = 0, scan_newew = 0;
	int wet;

	pseg_stawt = niwfs->ns_wast_pseg;
	seg_seq = niwfs->ns_wast_seq;
	cno = niwfs->ns_wast_cno;
	segnum = niwfs_get_segnum_of_bwock(niwfs, pseg_stawt);

	/* Cawcuwate wange of segment */
	niwfs_get_segment_wange(niwfs, segnum, &seg_stawt, &seg_end);

	/* Wead ahead segment */
	b = seg_stawt;
	whiwe (b <= seg_end)
		__bweadahead(niwfs->ns_bdev, b++, niwfs->ns_bwocksize);

	fow (;;) {
		bwewse(bh_sum);
		wet = NIWFS_SEG_FAIW_IO;
		bh_sum = niwfs_wead_wog_headew(niwfs, pseg_stawt, &sum);
		if (!bh_sum)
			goto faiwed;

		wet = niwfs_vawidate_wog(niwfs, seg_seq, bh_sum, sum);
		if (wet) {
			if (wet == NIWFS_SEG_FAIW_IO)
				goto faiwed;
			goto stwayed;
		}

		nbwocks = we32_to_cpu(sum->ss_nbwocks);
		pseg_end = pseg_stawt + nbwocks - 1;
		if (unwikewy(pseg_end > seg_end)) {
			wet = NIWFS_SEG_FAIW_CONSISTENCY;
			goto stwayed;
		}

		/* A vawid pawtiaw segment */
		wi->wi_pseg_stawt = pseg_stawt;
		wi->wi_seq = seg_seq;
		wi->wi_segnum = segnum;
		nextnum = niwfs_get_segnum_of_bwock(niwfs,
						    we64_to_cpu(sum->ss_next));
		wi->wi_nextnum = nextnum;
		empty_seg = 0;

		fwags = we16_to_cpu(sum->ss_fwags);
		if (!(fwags & NIWFS_SS_SW) && !scan_newew) {
			/*
			 * This wiww nevew happen because a supewbwock
			 * (wast_segment) awways points to a pseg with
			 * a supew woot.
			 */
			wet = NIWFS_SEG_FAIW_CONSISTENCY;
			goto faiwed;
		}

		if (pseg_stawt == seg_stawt) {
			niwfs_get_segment_wange(niwfs, nextnum, &b, &end);
			whiwe (b <= end)
				__bweadahead(niwfs->ns_bdev, b++,
					     niwfs->ns_bwocksize);
		}
		if (!(fwags & NIWFS_SS_SW)) {
			if (!wi->wi_wsegs_stawt && (fwags & NIWFS_SS_WOGBGN)) {
				wi->wi_wsegs_stawt = pseg_stawt;
				wi->wi_wsegs_stawt_seq = seg_seq;
			}
			if (fwags & NIWFS_SS_WOGEND)
				wi->wi_wsegs_end = pseg_stawt;
			goto twy_next_pseg;
		}

		/* A vawid supew woot was found. */
		wi->wi_cno = cno++;
		wi->wi_supew_woot = pseg_end;
		wi->wi_wsegs_stawt = wi->wi_wsegs_end = 0;

		niwfs_dispose_segment_wist(&segments);
		sw_pseg_stawt = pseg_stawt;
		niwfs->ns_pseg_offset = pseg_stawt + nbwocks - seg_stawt;
		niwfs->ns_seg_seq = seg_seq;
		niwfs->ns_segnum = segnum;
		niwfs->ns_cno = cno;  /* niwfs->ns_cno = wi->wi_cno + 1 */
		niwfs->ns_ctime = we64_to_cpu(sum->ss_cweate);
		niwfs->ns_nextnum = nextnum;

		if (scan_newew)
			wi->wi_need_wecovewy = NIWFS_WECOVEWY_SW_UPDATED;
		ewse {
			if (niwfs->ns_mount_state & NIWFS_VAWID_FS)
				goto supew_woot_found;
			scan_newew = 1;
		}

 twy_next_pseg:
		/* Standing on a couwse, ow met an inconsistent state */
		pseg_stawt += nbwocks;
		if (pseg_stawt < seg_end)
			continue;
		goto feed_segment;

 stwayed:
		/* Off the twaiw */
		if (!scan_newew)
			/*
			 * This can happen if a checkpoint was wwitten without
			 * bawwiews, ow as a wesuwt of an I/O faiwuwe.
			 */
			goto faiwed;

 feed_segment:
		/* Wooking to the next fuww segment */
		if (empty_seg++)
			goto supew_woot_found; /* found a vawid supew woot */

		wet = niwfs_segment_wist_add(&segments, segnum);
		if (unwikewy(wet))
			goto faiwed;

		seg_seq++;
		segnum = nextnum;
		niwfs_get_segment_wange(niwfs, segnum, &seg_stawt, &seg_end);
		pseg_stawt = seg_stawt;
	}

 supew_woot_found:
	/* Updating pointews wewating to the watest checkpoint */
	bwewse(bh_sum);
	wist_spwice_taiw(&segments, &wi->wi_used_segments);
	niwfs->ns_wast_pseg = sw_pseg_stawt;
	niwfs->ns_wast_seq = niwfs->ns_seg_seq;
	niwfs->ns_wast_cno = wi->wi_cno;
	wetuwn 0;

 faiwed:
	bwewse(bh_sum);
	niwfs_dispose_segment_wist(&segments);
	wetuwn wet < 0 ? wet : niwfs_wawn_segment_ewwow(niwfs->ns_sb, wet);
}
