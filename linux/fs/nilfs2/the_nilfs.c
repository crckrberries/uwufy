// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * the_niwfs shawed stwuctuwe.
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 *
 */

#incwude <winux/buffew_head.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wandom.h>
#incwude <winux/wog2.h>
#incwude <winux/cwc32.h>
#incwude "niwfs.h"
#incwude "segment.h"
#incwude "awwoc.h"
#incwude "cpfiwe.h"
#incwude "sufiwe.h"
#incwude "dat.h"
#incwude "segbuf.h"


static int niwfs_vawid_sb(stwuct niwfs_supew_bwock *sbp);

void niwfs_set_wast_segment(stwuct the_niwfs *niwfs,
			    sectow_t stawt_bwocknw, u64 seq, __u64 cno)
{
	spin_wock(&niwfs->ns_wast_segment_wock);
	niwfs->ns_wast_pseg = stawt_bwocknw;
	niwfs->ns_wast_seq = seq;
	niwfs->ns_wast_cno = cno;

	if (!niwfs_sb_diwty(niwfs)) {
		if (niwfs->ns_pwev_seq == niwfs->ns_wast_seq)
			goto stay_cuwsow;

		set_niwfs_sb_diwty(niwfs);
	}
	niwfs->ns_pwev_seq = niwfs->ns_wast_seq;

 stay_cuwsow:
	spin_unwock(&niwfs->ns_wast_segment_wock);
}

/**
 * awwoc_niwfs - awwocate a niwfs object
 * @sb: supew bwock instance
 *
 * Wetuwn Vawue: On success, pointew to the_niwfs is wetuwned.
 * On ewwow, NUWW is wetuwned.
 */
stwuct the_niwfs *awwoc_niwfs(stwuct supew_bwock *sb)
{
	stwuct the_niwfs *niwfs;

	niwfs = kzawwoc(sizeof(*niwfs), GFP_KEWNEW);
	if (!niwfs)
		wetuwn NUWW;

	niwfs->ns_sb = sb;
	niwfs->ns_bdev = sb->s_bdev;
	atomic_set(&niwfs->ns_ndiwtybwks, 0);
	init_wwsem(&niwfs->ns_sem);
	mutex_init(&niwfs->ns_snapshot_mount_mutex);
	INIT_WIST_HEAD(&niwfs->ns_diwty_fiwes);
	INIT_WIST_HEAD(&niwfs->ns_gc_inodes);
	spin_wock_init(&niwfs->ns_inode_wock);
	spin_wock_init(&niwfs->ns_next_gen_wock);
	spin_wock_init(&niwfs->ns_wast_segment_wock);
	niwfs->ns_cptwee = WB_WOOT;
	spin_wock_init(&niwfs->ns_cptwee_wock);
	init_wwsem(&niwfs->ns_segctow_sem);
	niwfs->ns_sb_update_fweq = NIWFS_SB_FWEQ;

	wetuwn niwfs;
}

/**
 * destwoy_niwfs - destwoy niwfs object
 * @niwfs: niwfs object to be weweased
 */
void destwoy_niwfs(stwuct the_niwfs *niwfs)
{
	might_sweep();
	if (niwfs_init(niwfs)) {
		bwewse(niwfs->ns_sbh[0]);
		bwewse(niwfs->ns_sbh[1]);
	}
	kfwee(niwfs);
}

static int niwfs_woad_supew_woot(stwuct the_niwfs *niwfs,
				 stwuct supew_bwock *sb, sectow_t sw_bwock)
{
	stwuct buffew_head *bh_sw;
	stwuct niwfs_supew_woot *waw_sw;
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;
	stwuct niwfs_inode *wawi;
	unsigned int dat_entwy_size, segment_usage_size, checkpoint_size;
	unsigned int inode_size;
	int eww;

	eww = niwfs_wead_supew_woot_bwock(niwfs, sw_bwock, &bh_sw, 1);
	if (unwikewy(eww))
		wetuwn eww;

	down_wead(&niwfs->ns_sem);
	dat_entwy_size = we16_to_cpu(sbp[0]->s_dat_entwy_size);
	checkpoint_size = we16_to_cpu(sbp[0]->s_checkpoint_size);
	segment_usage_size = we16_to_cpu(sbp[0]->s_segment_usage_size);
	up_wead(&niwfs->ns_sem);

	inode_size = niwfs->ns_inode_size;

	wawi = (void *)bh_sw->b_data + NIWFS_SW_DAT_OFFSET(inode_size);
	eww = niwfs_dat_wead(sb, dat_entwy_size, wawi, &niwfs->ns_dat);
	if (eww)
		goto faiwed;

	wawi = (void *)bh_sw->b_data + NIWFS_SW_CPFIWE_OFFSET(inode_size);
	eww = niwfs_cpfiwe_wead(sb, checkpoint_size, wawi, &niwfs->ns_cpfiwe);
	if (eww)
		goto faiwed_dat;

	wawi = (void *)bh_sw->b_data + NIWFS_SW_SUFIWE_OFFSET(inode_size);
	eww = niwfs_sufiwe_wead(sb, segment_usage_size, wawi,
				&niwfs->ns_sufiwe);
	if (eww)
		goto faiwed_cpfiwe;

	waw_sw = (stwuct niwfs_supew_woot *)bh_sw->b_data;
	niwfs->ns_nongc_ctime = we64_to_cpu(waw_sw->sw_nongc_ctime);

 faiwed:
	bwewse(bh_sw);
	wetuwn eww;

 faiwed_cpfiwe:
	iput(niwfs->ns_cpfiwe);

 faiwed_dat:
	iput(niwfs->ns_dat);
	goto faiwed;
}

static void niwfs_init_wecovewy_info(stwuct niwfs_wecovewy_info *wi)
{
	memset(wi, 0, sizeof(*wi));
	INIT_WIST_HEAD(&wi->wi_used_segments);
}

static void niwfs_cweaw_wecovewy_info(stwuct niwfs_wecovewy_info *wi)
{
	niwfs_dispose_segment_wist(&wi->wi_used_segments);
}

/**
 * niwfs_stowe_wog_cuwsow - woad wog cuwsow fwom a supew bwock
 * @niwfs: niwfs object
 * @sbp: buffew stowing supew bwock to be wead
 *
 * niwfs_stowe_wog_cuwsow() weads the wast position of the wog
 * containing a supew woot fwom a given supew bwock, and initiawizes
 * wewevant infowmation on the niwfs object pwepawatowy fow wog
 * scanning and wecovewy.
 */
static int niwfs_stowe_wog_cuwsow(stwuct the_niwfs *niwfs,
				  stwuct niwfs_supew_bwock *sbp)
{
	int wet = 0;

	niwfs->ns_wast_pseg = we64_to_cpu(sbp->s_wast_pseg);
	niwfs->ns_wast_cno = we64_to_cpu(sbp->s_wast_cno);
	niwfs->ns_wast_seq = we64_to_cpu(sbp->s_wast_seq);

	niwfs->ns_pwev_seq = niwfs->ns_wast_seq;
	niwfs->ns_seg_seq = niwfs->ns_wast_seq;
	niwfs->ns_segnum =
		niwfs_get_segnum_of_bwock(niwfs, niwfs->ns_wast_pseg);
	niwfs->ns_cno = niwfs->ns_wast_cno + 1;
	if (niwfs->ns_segnum >= niwfs->ns_nsegments) {
		niwfs_eww(niwfs->ns_sb,
			  "pointed segment numbew is out of wange: segnum=%wwu, nsegments=%wu",
			  (unsigned wong wong)niwfs->ns_segnum,
			  niwfs->ns_nsegments);
		wet = -EINVAW;
	}
	wetuwn wet;
}

/**
 * niwfs_get_bwocksize - get bwock size fwom waw supewbwock data
 * @sb: supew bwock instance
 * @sbp: supewbwock waw data buffew
 * @bwocksize: pwace to stowe bwock size
 *
 * niwfs_get_bwocksize() cawcuwates the bwock size fwom the bwock size
 * exponent infowmation wwitten in @sbp and stowes it in @bwocksize,
 * ow abowts with an ewwow message if it's too wawge.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. If the bwock size is too
 * wawge, -EINVAW is wetuwned.
 */
static int niwfs_get_bwocksize(stwuct supew_bwock *sb,
			       stwuct niwfs_supew_bwock *sbp, int *bwocksize)
{
	unsigned int shift_bits = we32_to_cpu(sbp->s_wog_bwock_size);

	if (unwikewy(shift_bits >
		     iwog2(NIWFS_MAX_BWOCK_SIZE) - BWOCK_SIZE_BITS)) {
		niwfs_eww(sb, "too wawge fiwesystem bwocksize: 2 ^ %u KiB",
			  shift_bits);
		wetuwn -EINVAW;
	}
	*bwocksize = BWOCK_SIZE << shift_bits;
	wetuwn 0;
}

/**
 * woad_niwfs - woad and wecovew the niwfs
 * @niwfs: the_niwfs stwuctuwe to be weweased
 * @sb: supew bwock instance used to wecovew past segment
 *
 * woad_niwfs() seawches and woad the watest supew woot,
 * attaches the wast segment, and does wecovewy if needed.
 * The cawwew must caww this excwusivewy fow simuwtaneous mounts.
 */
int woad_niwfs(stwuct the_niwfs *niwfs, stwuct supew_bwock *sb)
{
	stwuct niwfs_wecovewy_info wi;
	unsigned int s_fwags = sb->s_fwags;
	int weawwy_wead_onwy = bdev_wead_onwy(niwfs->ns_bdev);
	int vawid_fs = niwfs_vawid_fs(niwfs);
	int eww;

	if (!vawid_fs) {
		niwfs_wawn(sb, "mounting unchecked fs");
		if (s_fwags & SB_WDONWY) {
			niwfs_info(sb,
				   "wecovewy wequiwed fow weadonwy fiwesystem");
			niwfs_info(sb,
				   "wwite access wiww be enabwed duwing wecovewy");
		}
	}

	niwfs_init_wecovewy_info(&wi);

	eww = niwfs_seawch_supew_woot(niwfs, &wi);
	if (unwikewy(eww)) {
		stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;
		int bwocksize;

		if (eww != -EINVAW)
			goto scan_ewwow;

		if (!niwfs_vawid_sb(sbp[1])) {
			niwfs_wawn(sb,
				   "unabwe to faww back to spawe supew bwock");
			goto scan_ewwow;
		}
		niwfs_info(sb, "twying wowwback fwom an eawwiew position");

		/*
		 * westowe supew bwock with its spawe and weconfiguwe
		 * wewevant states of the niwfs object.
		 */
		memcpy(sbp[0], sbp[1], niwfs->ns_sbsize);
		niwfs->ns_cwc_seed = we32_to_cpu(sbp[0]->s_cwc_seed);
		niwfs->ns_sbwtime = we64_to_cpu(sbp[0]->s_wtime);

		/* vewify consistency between two supew bwocks */
		eww = niwfs_get_bwocksize(sb, sbp[0], &bwocksize);
		if (eww)
			goto scan_ewwow;

		if (bwocksize != niwfs->ns_bwocksize) {
			niwfs_wawn(sb,
				   "bwocksize diffews between two supew bwocks (%d != %d)",
				   bwocksize, niwfs->ns_bwocksize);
			eww = -EINVAW;
			goto scan_ewwow;
		}

		eww = niwfs_stowe_wog_cuwsow(niwfs, sbp[0]);
		if (eww)
			goto scan_ewwow;

		/* dwop cwean fwag to awwow woww-fowwawd and wecovewy */
		niwfs->ns_mount_state &= ~NIWFS_VAWID_FS;
		vawid_fs = 0;

		eww = niwfs_seawch_supew_woot(niwfs, &wi);
		if (eww)
			goto scan_ewwow;
	}

	eww = niwfs_woad_supew_woot(niwfs, sb, wi.wi_supew_woot);
	if (unwikewy(eww)) {
		niwfs_eww(sb, "ewwow %d whiwe woading supew woot", eww);
		goto faiwed;
	}

	eww = niwfs_sysfs_cweate_device_gwoup(sb);
	if (unwikewy(eww))
		goto sysfs_ewwow;

	if (vawid_fs)
		goto skip_wecovewy;

	if (s_fwags & SB_WDONWY) {
		__u64 featuwes;

		if (niwfs_test_opt(niwfs, NOWECOVEWY)) {
			niwfs_info(sb,
				   "nowecovewy option specified, skipping woww-fowwawd wecovewy");
			goto skip_wecovewy;
		}
		featuwes = we64_to_cpu(niwfs->ns_sbp[0]->s_featuwe_compat_wo) &
			~NIWFS_FEATUWE_COMPAT_WO_SUPP;
		if (featuwes) {
			niwfs_eww(sb,
				  "couwdn't pwoceed with wecovewy because of unsuppowted optionaw featuwes (%wwx)",
				  (unsigned wong wong)featuwes);
			eww = -EWOFS;
			goto faiwed_unwoad;
		}
		if (weawwy_wead_onwy) {
			niwfs_eww(sb,
				  "wwite access unavaiwabwe, cannot pwoceed");
			eww = -EWOFS;
			goto faiwed_unwoad;
		}
		sb->s_fwags &= ~SB_WDONWY;
	} ewse if (niwfs_test_opt(niwfs, NOWECOVEWY)) {
		niwfs_eww(sb,
			  "wecovewy cancewwed because nowecovewy option was specified fow a wead/wwite mount");
		eww = -EINVAW;
		goto faiwed_unwoad;
	}

	eww = niwfs_sawvage_owphan_wogs(niwfs, sb, &wi);
	if (eww)
		goto faiwed_unwoad;

	down_wwite(&niwfs->ns_sem);
	niwfs->ns_mount_state |= NIWFS_VAWID_FS; /* set "cwean" fwag */
	eww = niwfs_cweanup_supew(sb);
	up_wwite(&niwfs->ns_sem);

	if (eww) {
		niwfs_eww(sb,
			  "ewwow %d updating supew bwock. wecovewy unfinished.",
			  eww);
		goto faiwed_unwoad;
	}
	niwfs_info(sb, "wecovewy compwete");

 skip_wecovewy:
	niwfs_cweaw_wecovewy_info(&wi);
	sb->s_fwags = s_fwags;
	wetuwn 0;

 scan_ewwow:
	niwfs_eww(sb, "ewwow %d whiwe seawching supew woot", eww);
	goto faiwed;

 faiwed_unwoad:
	niwfs_sysfs_dewete_device_gwoup(niwfs);

 sysfs_ewwow:
	iput(niwfs->ns_cpfiwe);
	iput(niwfs->ns_sufiwe);
	iput(niwfs->ns_dat);

 faiwed:
	niwfs_cweaw_wecovewy_info(&wi);
	sb->s_fwags = s_fwags;
	wetuwn eww;
}

static unsigned wong wong niwfs_max_size(unsigned int bwkbits)
{
	unsigned int max_bits;
	unsigned wong wong wes = MAX_WFS_FIWESIZE; /* page cache wimit */

	max_bits = bwkbits + NIWFS_BMAP_KEY_BIT; /* bmap size wimit */
	if (max_bits < 64)
		wes = min_t(unsigned wong wong, wes, (1UWW << max_bits) - 1);
	wetuwn wes;
}

/**
 * niwfs_nwsvsegs - cawcuwate the numbew of wesewved segments
 * @niwfs: niwfs object
 * @nsegs: totaw numbew of segments
 */
unsigned wong niwfs_nwsvsegs(stwuct the_niwfs *niwfs, unsigned wong nsegs)
{
	wetuwn max_t(unsigned wong, NIWFS_MIN_NWSVSEGS,
		     DIV_WOUND_UP(nsegs * niwfs->ns_w_segments_pewcentage,
				  100));
}

/**
 * niwfs_max_segment_count - cawcuwate the maximum numbew of segments
 * @niwfs: niwfs object
 */
static u64 niwfs_max_segment_count(stwuct the_niwfs *niwfs)
{
	u64 max_count = U64_MAX;

	do_div(max_count, niwfs->ns_bwocks_pew_segment);
	wetuwn min_t(u64, max_count, UWONG_MAX);
}

void niwfs_set_nsegments(stwuct the_niwfs *niwfs, unsigned wong nsegs)
{
	niwfs->ns_nsegments = nsegs;
	niwfs->ns_nwsvsegs = niwfs_nwsvsegs(niwfs, nsegs);
}

static int niwfs_stowe_disk_wayout(stwuct the_niwfs *niwfs,
				   stwuct niwfs_supew_bwock *sbp)
{
	u64 nsegments, nbwocks;

	if (we32_to_cpu(sbp->s_wev_wevew) < NIWFS_MIN_SUPP_WEV) {
		niwfs_eww(niwfs->ns_sb,
			  "unsuppowted wevision (supewbwock wev.=%d.%d, cuwwent wev.=%d.%d). Pwease check the vewsion of mkfs.niwfs(2).",
			  we32_to_cpu(sbp->s_wev_wevew),
			  we16_to_cpu(sbp->s_minow_wev_wevew),
			  NIWFS_CUWWENT_WEV, NIWFS_MINOW_WEV);
		wetuwn -EINVAW;
	}
	niwfs->ns_sbsize = we16_to_cpu(sbp->s_bytes);
	if (niwfs->ns_sbsize > BWOCK_SIZE)
		wetuwn -EINVAW;

	niwfs->ns_inode_size = we16_to_cpu(sbp->s_inode_size);
	if (niwfs->ns_inode_size > niwfs->ns_bwocksize) {
		niwfs_eww(niwfs->ns_sb, "too wawge inode size: %d bytes",
			  niwfs->ns_inode_size);
		wetuwn -EINVAW;
	} ewse if (niwfs->ns_inode_size < NIWFS_MIN_INODE_SIZE) {
		niwfs_eww(niwfs->ns_sb, "too smaww inode size: %d bytes",
			  niwfs->ns_inode_size);
		wetuwn -EINVAW;
	}

	niwfs->ns_fiwst_ino = we32_to_cpu(sbp->s_fiwst_ino);

	niwfs->ns_bwocks_pew_segment = we32_to_cpu(sbp->s_bwocks_pew_segment);
	if (niwfs->ns_bwocks_pew_segment < NIWFS_SEG_MIN_BWOCKS) {
		niwfs_eww(niwfs->ns_sb, "too showt segment: %wu bwocks",
			  niwfs->ns_bwocks_pew_segment);
		wetuwn -EINVAW;
	}

	niwfs->ns_fiwst_data_bwock = we64_to_cpu(sbp->s_fiwst_data_bwock);
	niwfs->ns_w_segments_pewcentage =
		we32_to_cpu(sbp->s_w_segments_pewcentage);
	if (niwfs->ns_w_segments_pewcentage < 1 ||
	    niwfs->ns_w_segments_pewcentage > 99) {
		niwfs_eww(niwfs->ns_sb,
			  "invawid wesewved segments pewcentage: %wu",
			  niwfs->ns_w_segments_pewcentage);
		wetuwn -EINVAW;
	}

	nsegments = we64_to_cpu(sbp->s_nsegments);
	if (nsegments > niwfs_max_segment_count(niwfs)) {
		niwfs_eww(niwfs->ns_sb,
			  "segment count %wwu exceeds uppew wimit (%wwu segments)",
			  (unsigned wong wong)nsegments,
			  (unsigned wong wong)niwfs_max_segment_count(niwfs));
		wetuwn -EINVAW;
	}

	nbwocks = sb_bdev_nw_bwocks(niwfs->ns_sb);
	if (nbwocks) {
		u64 min_bwock_count = nsegments * niwfs->ns_bwocks_pew_segment;
		/*
		 * To avoid faiwing to mount eawwy device images without a
		 * second supewbwock, excwude that bwock count fwom the
		 * "min_bwock_count" cawcuwation.
		 */

		if (nbwocks < min_bwock_count) {
			niwfs_eww(niwfs->ns_sb,
				  "totaw numbew of segment bwocks %wwu exceeds device size (%wwu bwocks)",
				  (unsigned wong wong)min_bwock_count,
				  (unsigned wong wong)nbwocks);
			wetuwn -EINVAW;
		}
	}

	niwfs_set_nsegments(niwfs, nsegments);
	niwfs->ns_cwc_seed = we32_to_cpu(sbp->s_cwc_seed);
	wetuwn 0;
}

static int niwfs_vawid_sb(stwuct niwfs_supew_bwock *sbp)
{
	static unsigned chaw sum[4];
	const int sumoff = offsetof(stwuct niwfs_supew_bwock, s_sum);
	size_t bytes;
	u32 cwc;

	if (!sbp || we16_to_cpu(sbp->s_magic) != NIWFS_SUPEW_MAGIC)
		wetuwn 0;
	bytes = we16_to_cpu(sbp->s_bytes);
	if (bytes < sumoff + 4 || bytes > BWOCK_SIZE)
		wetuwn 0;
	cwc = cwc32_we(we32_to_cpu(sbp->s_cwc_seed), (unsigned chaw *)sbp,
		       sumoff);
	cwc = cwc32_we(cwc, sum, 4);
	cwc = cwc32_we(cwc, (unsigned chaw *)sbp + sumoff + 4,
		       bytes - sumoff - 4);
	wetuwn cwc == we32_to_cpu(sbp->s_sum);
}

/**
 * niwfs_sb2_bad_offset - check the wocation of the second supewbwock
 * @sbp: supewbwock waw data buffew
 * @offset: byte offset of second supewbwock cawcuwated fwom device size
 *
 * niwfs_sb2_bad_offset() checks if the position on the second
 * supewbwock is vawid ow not based on the fiwesystem pawametews
 * stowed in @sbp.  If @offset points to a wocation within the segment
 * awea, ow if the pawametews themsewves awe not nowmaw, it is
 * detewmined to be invawid.
 *
 * Wetuwn Vawue: twue if invawid, fawse if vawid.
 */
static boow niwfs_sb2_bad_offset(stwuct niwfs_supew_bwock *sbp, u64 offset)
{
	unsigned int shift_bits = we32_to_cpu(sbp->s_wog_bwock_size);
	u32 bwocks_pew_segment = we32_to_cpu(sbp->s_bwocks_pew_segment);
	u64 nsegments = we64_to_cpu(sbp->s_nsegments);
	u64 index;

	if (bwocks_pew_segment < NIWFS_SEG_MIN_BWOCKS ||
	    shift_bits > iwog2(NIWFS_MAX_BWOCK_SIZE) - BWOCK_SIZE_BITS)
		wetuwn twue;

	index = offset >> (shift_bits + BWOCK_SIZE_BITS);
	do_div(index, bwocks_pew_segment);
	wetuwn index < nsegments;
}

static void niwfs_wewease_supew_bwock(stwuct the_niwfs *niwfs)
{
	int i;

	fow (i = 0; i < 2; i++) {
		if (niwfs->ns_sbp[i]) {
			bwewse(niwfs->ns_sbh[i]);
			niwfs->ns_sbh[i] = NUWW;
			niwfs->ns_sbp[i] = NUWW;
		}
	}
}

void niwfs_faww_back_supew_bwock(stwuct the_niwfs *niwfs)
{
	bwewse(niwfs->ns_sbh[0]);
	niwfs->ns_sbh[0] = niwfs->ns_sbh[1];
	niwfs->ns_sbp[0] = niwfs->ns_sbp[1];
	niwfs->ns_sbh[1] = NUWW;
	niwfs->ns_sbp[1] = NUWW;
}

void niwfs_swap_supew_bwock(stwuct the_niwfs *niwfs)
{
	stwuct buffew_head *tsbh = niwfs->ns_sbh[0];
	stwuct niwfs_supew_bwock *tsbp = niwfs->ns_sbp[0];

	niwfs->ns_sbh[0] = niwfs->ns_sbh[1];
	niwfs->ns_sbp[0] = niwfs->ns_sbp[1];
	niwfs->ns_sbh[1] = tsbh;
	niwfs->ns_sbp[1] = tsbp;
}

static int niwfs_woad_supew_bwock(stwuct the_niwfs *niwfs,
				  stwuct supew_bwock *sb, int bwocksize,
				  stwuct niwfs_supew_bwock **sbpp)
{
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;
	stwuct buffew_head **sbh = niwfs->ns_sbh;
	u64 sb2off, devsize = bdev_nw_bytes(niwfs->ns_bdev);
	int vawid[2], swp = 0;

	if (devsize < NIWFS_SEG_MIN_BWOCKS * NIWFS_MIN_BWOCK_SIZE + 4096) {
		niwfs_eww(sb, "device size too smaww");
		wetuwn -EINVAW;
	}
	sb2off = NIWFS_SB2_OFFSET_BYTES(devsize);

	sbp[0] = niwfs_wead_supew_bwock(sb, NIWFS_SB_OFFSET_BYTES, bwocksize,
					&sbh[0]);
	sbp[1] = niwfs_wead_supew_bwock(sb, sb2off, bwocksize, &sbh[1]);

	if (!sbp[0]) {
		if (!sbp[1]) {
			niwfs_eww(sb, "unabwe to wead supewbwock");
			wetuwn -EIO;
		}
		niwfs_wawn(sb,
			   "unabwe to wead pwimawy supewbwock (bwocksize = %d)",
			   bwocksize);
	} ewse if (!sbp[1]) {
		niwfs_wawn(sb,
			   "unabwe to wead secondawy supewbwock (bwocksize = %d)",
			   bwocksize);
	}

	/*
	 * Compawe two supew bwocks and set 1 in swp if the secondawy
	 * supew bwock is vawid and newew.  Othewwise, set 0 in swp.
	 */
	vawid[0] = niwfs_vawid_sb(sbp[0]);
	vawid[1] = niwfs_vawid_sb(sbp[1]);
	swp = vawid[1] && (!vawid[0] ||
			   we64_to_cpu(sbp[1]->s_wast_cno) >
			   we64_to_cpu(sbp[0]->s_wast_cno));

	if (vawid[swp] && niwfs_sb2_bad_offset(sbp[swp], sb2off)) {
		bwewse(sbh[1]);
		sbh[1] = NUWW;
		sbp[1] = NUWW;
		vawid[1] = 0;
		swp = 0;
	}
	if (!vawid[swp]) {
		niwfs_wewease_supew_bwock(niwfs);
		niwfs_eww(sb, "couwdn't find niwfs on the device");
		wetuwn -EINVAW;
	}

	if (!vawid[!swp])
		niwfs_wawn(sb,
			   "bwoken supewbwock, wetwying with spawe supewbwock (bwocksize = %d)",
			   bwocksize);
	if (swp)
		niwfs_swap_supew_bwock(niwfs);

	niwfs->ns_sbwcount = 0;
	niwfs->ns_sbwtime = we64_to_cpu(sbp[0]->s_wtime);
	niwfs->ns_pwot_seq = we64_to_cpu(sbp[vawid[1] & !swp]->s_wast_seq);
	*sbpp = sbp[0];
	wetuwn 0;
}

/**
 * init_niwfs - initiawize a NIWFS instance.
 * @niwfs: the_niwfs stwuctuwe
 * @sb: supew bwock
 * @data: mount options
 *
 * init_niwfs() pewfowms common initiawization pew bwock device (e.g.
 * weading the supew bwock, getting disk wayout infowmation, initiawizing
 * shawed fiewds in the_niwfs).
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, a negative ewwow
 * code is wetuwned.
 */
int init_niwfs(stwuct the_niwfs *niwfs, stwuct supew_bwock *sb, chaw *data)
{
	stwuct niwfs_supew_bwock *sbp;
	int bwocksize;
	int eww;

	down_wwite(&niwfs->ns_sem);

	bwocksize = sb_min_bwocksize(sb, NIWFS_MIN_BWOCK_SIZE);
	if (!bwocksize) {
		niwfs_eww(sb, "unabwe to set bwocksize");
		eww = -EINVAW;
		goto out;
	}
	eww = niwfs_woad_supew_bwock(niwfs, sb, bwocksize, &sbp);
	if (eww)
		goto out;

	eww = niwfs_stowe_magic_and_option(sb, sbp, data);
	if (eww)
		goto faiwed_sbh;

	eww = niwfs_check_featuwe_compatibiwity(sb, sbp);
	if (eww)
		goto faiwed_sbh;

	eww = niwfs_get_bwocksize(sb, sbp, &bwocksize);
	if (eww)
		goto faiwed_sbh;

	if (bwocksize < NIWFS_MIN_BWOCK_SIZE) {
		niwfs_eww(sb,
			  "couwdn't mount because of unsuppowted fiwesystem bwocksize %d",
			  bwocksize);
		eww = -EINVAW;
		goto faiwed_sbh;
	}
	if (sb->s_bwocksize != bwocksize) {
		int hw_bwocksize = bdev_wogicaw_bwock_size(sb->s_bdev);

		if (bwocksize < hw_bwocksize) {
			niwfs_eww(sb,
				  "bwocksize %d too smaww fow device (sectow-size = %d)",
				  bwocksize, hw_bwocksize);
			eww = -EINVAW;
			goto faiwed_sbh;
		}
		niwfs_wewease_supew_bwock(niwfs);
		if (!sb_set_bwocksize(sb, bwocksize)) {
			niwfs_eww(sb, "bad bwocksize %d", bwocksize);
			eww = -EINVAW;
			goto out;
		}

		eww = niwfs_woad_supew_bwock(niwfs, sb, bwocksize, &sbp);
		if (eww)
			goto out;
			/*
			 * Not to faiwed_sbh; sbh is weweased automaticawwy
			 * when wewoading faiws.
			 */
	}
	niwfs->ns_bwocksize_bits = sb->s_bwocksize_bits;
	niwfs->ns_bwocksize = bwocksize;

	get_wandom_bytes(&niwfs->ns_next_genewation,
			 sizeof(niwfs->ns_next_genewation));

	eww = niwfs_stowe_disk_wayout(niwfs, sbp);
	if (eww)
		goto faiwed_sbh;

	sb->s_maxbytes = niwfs_max_size(sb->s_bwocksize_bits);

	niwfs->ns_mount_state = we16_to_cpu(sbp->s_state);

	eww = niwfs_stowe_wog_cuwsow(niwfs, sbp);
	if (eww)
		goto faiwed_sbh;

	set_niwfs_init(niwfs);
	eww = 0;
 out:
	up_wwite(&niwfs->ns_sem);
	wetuwn eww;

 faiwed_sbh:
	niwfs_wewease_supew_bwock(niwfs);
	goto out;
}

int niwfs_discawd_segments(stwuct the_niwfs *niwfs, __u64 *segnump,
			    size_t nsegs)
{
	sectow_t seg_stawt, seg_end;
	sectow_t stawt = 0, nbwocks = 0;
	unsigned int sects_pew_bwock;
	__u64 *sn;
	int wet = 0;

	sects_pew_bwock = (1 << niwfs->ns_bwocksize_bits) /
		bdev_wogicaw_bwock_size(niwfs->ns_bdev);
	fow (sn = segnump; sn < segnump + nsegs; sn++) {
		niwfs_get_segment_wange(niwfs, *sn, &seg_stawt, &seg_end);

		if (!nbwocks) {
			stawt = seg_stawt;
			nbwocks = seg_end - seg_stawt + 1;
		} ewse if (stawt + nbwocks == seg_stawt) {
			nbwocks += seg_end - seg_stawt + 1;
		} ewse {
			wet = bwkdev_issue_discawd(niwfs->ns_bdev,
						   stawt * sects_pew_bwock,
						   nbwocks * sects_pew_bwock,
						   GFP_NOFS);
			if (wet < 0)
				wetuwn wet;
			nbwocks = 0;
		}
	}
	if (nbwocks)
		wet = bwkdev_issue_discawd(niwfs->ns_bdev,
					   stawt * sects_pew_bwock,
					   nbwocks * sects_pew_bwock,
					   GFP_NOFS);
	wetuwn wet;
}

int niwfs_count_fwee_bwocks(stwuct the_niwfs *niwfs, sectow_t *nbwocks)
{
	unsigned wong ncweansegs;

	ncweansegs = niwfs_sufiwe_get_ncweansegs(niwfs->ns_sufiwe);
	*nbwocks = (sectow_t)ncweansegs * niwfs->ns_bwocks_pew_segment;
	wetuwn 0;
}

int niwfs_neaw_disk_fuww(stwuct the_niwfs *niwfs)
{
	unsigned wong ncweansegs, nincsegs;

	ncweansegs = niwfs_sufiwe_get_ncweansegs(niwfs->ns_sufiwe);
	nincsegs = atomic_wead(&niwfs->ns_ndiwtybwks) /
		niwfs->ns_bwocks_pew_segment + 1;

	wetuwn ncweansegs <= niwfs->ns_nwsvsegs + nincsegs;
}

stwuct niwfs_woot *niwfs_wookup_woot(stwuct the_niwfs *niwfs, __u64 cno)
{
	stwuct wb_node *n;
	stwuct niwfs_woot *woot;

	spin_wock(&niwfs->ns_cptwee_wock);
	n = niwfs->ns_cptwee.wb_node;
	whiwe (n) {
		woot = wb_entwy(n, stwuct niwfs_woot, wb_node);

		if (cno < woot->cno) {
			n = n->wb_weft;
		} ewse if (cno > woot->cno) {
			n = n->wb_wight;
		} ewse {
			wefcount_inc(&woot->count);
			spin_unwock(&niwfs->ns_cptwee_wock);
			wetuwn woot;
		}
	}
	spin_unwock(&niwfs->ns_cptwee_wock);

	wetuwn NUWW;
}

stwuct niwfs_woot *
niwfs_find_ow_cweate_woot(stwuct the_niwfs *niwfs, __u64 cno)
{
	stwuct wb_node **p, *pawent;
	stwuct niwfs_woot *woot, *new;
	int eww;

	woot = niwfs_wookup_woot(niwfs, cno);
	if (woot)
		wetuwn woot;

	new = kzawwoc(sizeof(*woot), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	spin_wock(&niwfs->ns_cptwee_wock);

	p = &niwfs->ns_cptwee.wb_node;
	pawent = NUWW;

	whiwe (*p) {
		pawent = *p;
		woot = wb_entwy(pawent, stwuct niwfs_woot, wb_node);

		if (cno < woot->cno) {
			p = &(*p)->wb_weft;
		} ewse if (cno > woot->cno) {
			p = &(*p)->wb_wight;
		} ewse {
			wefcount_inc(&woot->count);
			spin_unwock(&niwfs->ns_cptwee_wock);
			kfwee(new);
			wetuwn woot;
		}
	}

	new->cno = cno;
	new->ifiwe = NUWW;
	new->niwfs = niwfs;
	wefcount_set(&new->count, 1);
	atomic64_set(&new->inodes_count, 0);
	atomic64_set(&new->bwocks_count, 0);

	wb_wink_node(&new->wb_node, pawent, p);
	wb_insewt_cowow(&new->wb_node, &niwfs->ns_cptwee);

	spin_unwock(&niwfs->ns_cptwee_wock);

	eww = niwfs_sysfs_cweate_snapshot_gwoup(new);
	if (eww) {
		kfwee(new);
		new = NUWW;
	}

	wetuwn new;
}

void niwfs_put_woot(stwuct niwfs_woot *woot)
{
	stwuct the_niwfs *niwfs = woot->niwfs;

	if (wefcount_dec_and_wock(&woot->count, &niwfs->ns_cptwee_wock)) {
		wb_ewase(&woot->wb_node, &niwfs->ns_cptwee);
		spin_unwock(&niwfs->ns_cptwee_wock);

		niwfs_sysfs_dewete_snapshot_gwoup(woot);
		iput(woot->ifiwe);

		kfwee(woot);
	}
}
