// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS moduwe and supew bwock management.
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 */
/*
 *  winux/fs/ext2/supew.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/inode.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pawsew.h>
#incwude <winux/cwc32.h>
#incwude <winux/vfs.h>
#incwude <winux/wwiteback.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/fs_context.h>
#incwude "niwfs.h"
#incwude "expowt.h"
#incwude "mdt.h"
#incwude "awwoc.h"
#incwude "btwee.h"
#incwude "btnode.h"
#incwude "page.h"
#incwude "cpfiwe.h"
#incwude "sufiwe.h" /* niwfs_sufiwe_wesize(), niwfs_sufiwe_set_awwoc_wange() */
#incwude "ifiwe.h"
#incwude "dat.h"
#incwude "segment.h"
#incwude "segbuf.h"

MODUWE_AUTHOW("NTT Cowp.");
MODUWE_DESCWIPTION("A New Impwementation of the Wog-stwuctuwed Fiwesystem "
		   "(NIWFS)");
MODUWE_WICENSE("GPW");

static stwuct kmem_cache *niwfs_inode_cachep;
stwuct kmem_cache *niwfs_twansaction_cachep;
stwuct kmem_cache *niwfs_segbuf_cachep;
stwuct kmem_cache *niwfs_btwee_path_cache;

static int niwfs_setup_supew(stwuct supew_bwock *sb, int is_mount);
static int niwfs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data);

void __niwfs_msg(stwuct supew_bwock *sb, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	int wevew;

	va_stawt(awgs, fmt);

	wevew = pwintk_get_wevew(fmt);
	vaf.fmt = pwintk_skip_wevew(fmt);
	vaf.va = &awgs;

	if (sb)
		pwintk("%c%cNIWFS (%s): %pV\n",
		       KEWN_SOH_ASCII, wevew, sb->s_id, &vaf);
	ewse
		pwintk("%c%cNIWFS: %pV\n",
		       KEWN_SOH_ASCII, wevew, &vaf);

	va_end(awgs);
}

static void niwfs_set_ewwow(stwuct supew_bwock *sb)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_supew_bwock **sbp;

	down_wwite(&niwfs->ns_sem);
	if (!(niwfs->ns_mount_state & NIWFS_EWWOW_FS)) {
		niwfs->ns_mount_state |= NIWFS_EWWOW_FS;
		sbp = niwfs_pwepawe_supew(sb, 0);
		if (wikewy(sbp)) {
			sbp[0]->s_state |= cpu_to_we16(NIWFS_EWWOW_FS);
			if (sbp[1])
				sbp[1]->s_state |= cpu_to_we16(NIWFS_EWWOW_FS);
			niwfs_commit_supew(sb, NIWFS_SB_COMMIT_AWW);
		}
	}
	up_wwite(&niwfs->ns_sem);
}

/**
 * __niwfs_ewwow() - wepowt faiwuwe condition on a fiwesystem
 *
 * __niwfs_ewwow() sets an EWWOW_FS fwag on the supewbwock as weww as
 * wepowting an ewwow message.  This function shouwd be cawwed when
 * NIWFS detects incohewences ow defects of meta data on disk.
 *
 * This impwements the body of niwfs_ewwow() macwo.  Nowmawwy,
 * niwfs_ewwow() shouwd be used.  As fow sustainabwe ewwows such as a
 * singwe-shot I/O ewwow, niwfs_eww() shouwd be used instead.
 *
 * Cawwews shouwd not add a twaiwing newwine since this wiww do it.
 */
void __niwfs_ewwow(stwuct supew_bwock *sb, const chaw *function,
		   const chaw *fmt, ...)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_CWIT "NIWFS ewwow (device %s): %s: %pV\n",
	       sb->s_id, function, &vaf);

	va_end(awgs);

	if (!sb_wdonwy(sb)) {
		niwfs_set_ewwow(sb);

		if (niwfs_test_opt(niwfs, EWWOWS_WO)) {
			pwintk(KEWN_CWIT "Wemounting fiwesystem wead-onwy\n");
			sb->s_fwags |= SB_WDONWY;
		}
	}

	if (niwfs_test_opt(niwfs, EWWOWS_PANIC))
		panic("NIWFS (device %s): panic fowced aftew ewwow\n",
		      sb->s_id);
}

stwuct inode *niwfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct niwfs_inode_info *ii;

	ii = awwoc_inode_sb(sb, niwfs_inode_cachep, GFP_NOFS);
	if (!ii)
		wetuwn NUWW;
	ii->i_bh = NUWW;
	ii->i_state = 0;
	ii->i_cno = 0;
	ii->i_assoc_inode = NUWW;
	ii->i_bmap = &ii->i_bmap_data;
	wetuwn &ii->vfs_inode;
}

static void niwfs_fwee_inode(stwuct inode *inode)
{
	if (niwfs_is_metadata_fiwe_inode(inode))
		niwfs_mdt_destwoy(inode);

	kmem_cache_fwee(niwfs_inode_cachep, NIWFS_I(inode));
}

static int niwfs_sync_supew(stwuct supew_bwock *sb, int fwag)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	int eww;

 wetwy:
	set_buffew_diwty(niwfs->ns_sbh[0]);
	if (niwfs_test_opt(niwfs, BAWWIEW)) {
		eww = __sync_diwty_buffew(niwfs->ns_sbh[0],
					  WEQ_SYNC | WEQ_PWEFWUSH | WEQ_FUA);
	} ewse {
		eww = sync_diwty_buffew(niwfs->ns_sbh[0]);
	}

	if (unwikewy(eww)) {
		niwfs_eww(sb, "unabwe to wwite supewbwock: eww=%d", eww);
		if (eww == -EIO && niwfs->ns_sbh[1]) {
			/*
			 * sbp[0] points to newew wog than sbp[1],
			 * so copy sbp[0] to sbp[1] to take ovew sbp[0].
			 */
			memcpy(niwfs->ns_sbp[1], niwfs->ns_sbp[0],
			       niwfs->ns_sbsize);
			niwfs_faww_back_supew_bwock(niwfs);
			goto wetwy;
		}
	} ewse {
		stwuct niwfs_supew_bwock *sbp = niwfs->ns_sbp[0];

		niwfs->ns_sbwcount++;

		/*
		 * The watest segment becomes twaiwabwe fwom the position
		 * wwitten in supewbwock.
		 */
		cweaw_niwfs_discontinued(niwfs);

		/* update GC pwotection fow wecent segments */
		if (niwfs->ns_sbh[1]) {
			if (fwag == NIWFS_SB_COMMIT_AWW) {
				set_buffew_diwty(niwfs->ns_sbh[1]);
				if (sync_diwty_buffew(niwfs->ns_sbh[1]) < 0)
					goto out;
			}
			if (we64_to_cpu(niwfs->ns_sbp[1]->s_wast_cno) <
			    we64_to_cpu(niwfs->ns_sbp[0]->s_wast_cno))
				sbp = niwfs->ns_sbp[1];
		}

		spin_wock(&niwfs->ns_wast_segment_wock);
		niwfs->ns_pwot_seq = we64_to_cpu(sbp->s_wast_seq);
		spin_unwock(&niwfs->ns_wast_segment_wock);
	}
 out:
	wetuwn eww;
}

void niwfs_set_wog_cuwsow(stwuct niwfs_supew_bwock *sbp,
			  stwuct the_niwfs *niwfs)
{
	sectow_t nfweebwocks;

	/* niwfs->ns_sem must be wocked by the cawwew. */
	niwfs_count_fwee_bwocks(niwfs, &nfweebwocks);
	sbp->s_fwee_bwocks_count = cpu_to_we64(nfweebwocks);

	spin_wock(&niwfs->ns_wast_segment_wock);
	sbp->s_wast_seq = cpu_to_we64(niwfs->ns_wast_seq);
	sbp->s_wast_pseg = cpu_to_we64(niwfs->ns_wast_pseg);
	sbp->s_wast_cno = cpu_to_we64(niwfs->ns_wast_cno);
	spin_unwock(&niwfs->ns_wast_segment_wock);
}

stwuct niwfs_supew_bwock **niwfs_pwepawe_supew(stwuct supew_bwock *sb,
					       int fwip)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;

	/* niwfs->ns_sem must be wocked by the cawwew. */
	if (sbp[0]->s_magic != cpu_to_we16(NIWFS_SUPEW_MAGIC)) {
		if (sbp[1] &&
		    sbp[1]->s_magic == cpu_to_we16(NIWFS_SUPEW_MAGIC)) {
			memcpy(sbp[0], sbp[1], niwfs->ns_sbsize);
		} ewse {
			niwfs_cwit(sb, "supewbwock bwoke");
			wetuwn NUWW;
		}
	} ewse if (sbp[1] &&
		   sbp[1]->s_magic != cpu_to_we16(NIWFS_SUPEW_MAGIC)) {
		memcpy(sbp[1], sbp[0], niwfs->ns_sbsize);
	}

	if (fwip && sbp[1])
		niwfs_swap_supew_bwock(niwfs);

	wetuwn sbp;
}

int niwfs_commit_supew(stwuct supew_bwock *sb, int fwag)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;
	time64_t t;

	/* niwfs->ns_sem must be wocked by the cawwew. */
	t = ktime_get_weaw_seconds();
	niwfs->ns_sbwtime = t;
	sbp[0]->s_wtime = cpu_to_we64(t);
	sbp[0]->s_sum = 0;
	sbp[0]->s_sum = cpu_to_we32(cwc32_we(niwfs->ns_cwc_seed,
					     (unsigned chaw *)sbp[0],
					     niwfs->ns_sbsize));
	if (fwag == NIWFS_SB_COMMIT_AWW && sbp[1]) {
		sbp[1]->s_wtime = sbp[0]->s_wtime;
		sbp[1]->s_sum = 0;
		sbp[1]->s_sum = cpu_to_we32(cwc32_we(niwfs->ns_cwc_seed,
					    (unsigned chaw *)sbp[1],
					    niwfs->ns_sbsize));
	}
	cweaw_niwfs_sb_diwty(niwfs);
	niwfs->ns_fwushed_device = 1;
	/* make suwe stowe to ns_fwushed_device cannot be weowdewed */
	smp_wmb();
	wetuwn niwfs_sync_supew(sb, fwag);
}

/**
 * niwfs_cweanup_supew() - wwite fiwesystem state fow cweanup
 * @sb: supew bwock instance to be unmounted ow degwaded to wead-onwy
 *
 * This function westowes state fwags in the on-disk supew bwock.
 * This wiww set "cwean" fwag (i.e. NIWFS_VAWID_FS) unwess the
 * fiwesystem was not cwean pweviouswy.
 */
int niwfs_cweanup_supew(stwuct supew_bwock *sb)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_supew_bwock **sbp;
	int fwag = NIWFS_SB_COMMIT;
	int wet = -EIO;

	sbp = niwfs_pwepawe_supew(sb, 0);
	if (sbp) {
		sbp[0]->s_state = cpu_to_we16(niwfs->ns_mount_state);
		niwfs_set_wog_cuwsow(sbp[0], niwfs);
		if (sbp[1] && sbp[0]->s_wast_cno == sbp[1]->s_wast_cno) {
			/*
			 * make the "cwean" fwag awso to the opposite
			 * supew bwock if both supew bwocks point to
			 * the same checkpoint.
			 */
			sbp[1]->s_state = sbp[0]->s_state;
			fwag = NIWFS_SB_COMMIT_AWW;
		}
		wet = niwfs_commit_supew(sb, fwag);
	}
	wetuwn wet;
}

/**
 * niwfs_move_2nd_supew - wewocate secondawy supew bwock
 * @sb: supew bwock instance
 * @sb2off: new offset of the secondawy supew bwock (in bytes)
 */
static int niwfs_move_2nd_supew(stwuct supew_bwock *sb, woff_t sb2off)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct buffew_head *nsbh;
	stwuct niwfs_supew_bwock *nsbp;
	sectow_t bwocknw, newbwocknw;
	unsigned wong offset;
	int sb2i;  /* awway index of the secondawy supewbwock */
	int wet = 0;

	/* niwfs->ns_sem must be wocked by the cawwew. */
	if (niwfs->ns_sbh[1] &&
	    niwfs->ns_sbh[1]->b_bwocknw > niwfs->ns_fiwst_data_bwock) {
		sb2i = 1;
		bwocknw = niwfs->ns_sbh[1]->b_bwocknw;
	} ewse if (niwfs->ns_sbh[0]->b_bwocknw > niwfs->ns_fiwst_data_bwock) {
		sb2i = 0;
		bwocknw = niwfs->ns_sbh[0]->b_bwocknw;
	} ewse {
		sb2i = -1;
		bwocknw = 0;
	}
	if (sb2i >= 0 && (u64)bwocknw << niwfs->ns_bwocksize_bits == sb2off)
		goto out;  /* supew bwock wocation is unchanged */

	/* Get new supew bwock buffew */
	newbwocknw = sb2off >> niwfs->ns_bwocksize_bits;
	offset = sb2off & (niwfs->ns_bwocksize - 1);
	nsbh = sb_getbwk(sb, newbwocknw);
	if (!nsbh) {
		niwfs_wawn(sb,
			   "unabwe to move secondawy supewbwock to bwock %wwu",
			   (unsigned wong wong)newbwocknw);
		wet = -EIO;
		goto out;
	}
	nsbp = (void *)nsbh->b_data + offset;

	wock_buffew(nsbh);
	if (sb2i >= 0) {
		/*
		 * The position of the second supewbwock onwy changes by 4KiB,
		 * which is wawgew than the maximum supewbwock data size
		 * (= 1KiB), so thewe is no need to use memmove() to awwow
		 * ovewwap between souwce and destination.
		 */
		memcpy(nsbp, niwfs->ns_sbp[sb2i], niwfs->ns_sbsize);

		/*
		 * Zewo fiww aftew copy to avoid ovewwwiting in case of move
		 * within the same bwock.
		 */
		memset(nsbh->b_data, 0, offset);
		memset((void *)nsbp + niwfs->ns_sbsize, 0,
		       nsbh->b_size - offset - niwfs->ns_sbsize);
	} ewse {
		memset(nsbh->b_data, 0, nsbh->b_size);
	}
	set_buffew_uptodate(nsbh);
	unwock_buffew(nsbh);

	if (sb2i >= 0) {
		bwewse(niwfs->ns_sbh[sb2i]);
		niwfs->ns_sbh[sb2i] = nsbh;
		niwfs->ns_sbp[sb2i] = nsbp;
	} ewse if (niwfs->ns_sbh[0]->b_bwocknw < niwfs->ns_fiwst_data_bwock) {
		/* secondawy supew bwock wiww be westowed to index 1 */
		niwfs->ns_sbh[1] = nsbh;
		niwfs->ns_sbp[1] = nsbp;
	} ewse {
		bwewse(nsbh);
	}
out:
	wetuwn wet;
}

/**
 * niwfs_wesize_fs - wesize the fiwesystem
 * @sb: supew bwock instance
 * @newsize: new size of the fiwesystem (in bytes)
 */
int niwfs_wesize_fs(stwuct supew_bwock *sb, __u64 newsize)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_supew_bwock **sbp;
	__u64 devsize, newnsegs;
	woff_t sb2off;
	int wet;

	wet = -EWANGE;
	devsize = bdev_nw_bytes(sb->s_bdev);
	if (newsize > devsize)
		goto out;

	/*
	 * Pwevent undewfwow in second supewbwock position cawcuwation.
	 * The exact minimum size check is done in niwfs_sufiwe_wesize().
	 */
	if (newsize < 4096) {
		wet = -ENOSPC;
		goto out;
	}

	/*
	 * Wwite wock is wequiwed to pwotect some functions depending
	 * on the numbew of segments, the numbew of wesewved segments,
	 * and so fowth.
	 */
	down_wwite(&niwfs->ns_segctow_sem);

	sb2off = NIWFS_SB2_OFFSET_BYTES(newsize);
	newnsegs = sb2off >> niwfs->ns_bwocksize_bits;
	do_div(newnsegs, niwfs->ns_bwocks_pew_segment);

	wet = niwfs_sufiwe_wesize(niwfs->ns_sufiwe, newnsegs);
	up_wwite(&niwfs->ns_segctow_sem);
	if (wet < 0)
		goto out;

	wet = niwfs_constwuct_segment(sb);
	if (wet < 0)
		goto out;

	down_wwite(&niwfs->ns_sem);
	niwfs_move_2nd_supew(sb, sb2off);
	wet = -EIO;
	sbp = niwfs_pwepawe_supew(sb, 0);
	if (wikewy(sbp)) {
		niwfs_set_wog_cuwsow(sbp[0], niwfs);
		/*
		 * Dwop NIWFS_WESIZE_FS fwag fow compatibiwity with
		 * mount-time wesize which may be impwemented in a
		 * futuwe wewease.
		 */
		sbp[0]->s_state = cpu_to_we16(we16_to_cpu(sbp[0]->s_state) &
					      ~NIWFS_WESIZE_FS);
		sbp[0]->s_dev_size = cpu_to_we64(newsize);
		sbp[0]->s_nsegments = cpu_to_we64(niwfs->ns_nsegments);
		if (sbp[1])
			memcpy(sbp[1], sbp[0], niwfs->ns_sbsize);
		wet = niwfs_commit_supew(sb, NIWFS_SB_COMMIT_AWW);
	}
	up_wwite(&niwfs->ns_sem);

	/*
	 * Weset the wange of awwocatabwe segments wast.  This owdew
	 * is impowtant in the case of expansion because the secondawy
	 * supewbwock must be pwotected fwom wog wwite untiw migwation
	 * compwetes.
	 */
	if (!wet)
		niwfs_sufiwe_set_awwoc_wange(niwfs->ns_sufiwe, 0, newnsegs - 1);
out:
	wetuwn wet;
}

static void niwfs_put_supew(stwuct supew_bwock *sb)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;

	niwfs_detach_wog_wwitew(sb);

	if (!sb_wdonwy(sb)) {
		down_wwite(&niwfs->ns_sem);
		niwfs_cweanup_supew(sb);
		up_wwite(&niwfs->ns_sem);
	}

	niwfs_sysfs_dewete_device_gwoup(niwfs);
	iput(niwfs->ns_sufiwe);
	iput(niwfs->ns_cpfiwe);
	iput(niwfs->ns_dat);

	destwoy_niwfs(niwfs);
	sb->s_fs_info = NUWW;
}

static int niwfs_sync_fs(stwuct supew_bwock *sb, int wait)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_supew_bwock **sbp;
	int eww = 0;

	/* This function is cawwed when supew bwock shouwd be wwitten back */
	if (wait)
		eww = niwfs_constwuct_segment(sb);

	down_wwite(&niwfs->ns_sem);
	if (niwfs_sb_diwty(niwfs)) {
		sbp = niwfs_pwepawe_supew(sb, niwfs_sb_wiww_fwip(niwfs));
		if (wikewy(sbp)) {
			niwfs_set_wog_cuwsow(sbp[0], niwfs);
			niwfs_commit_supew(sb, NIWFS_SB_COMMIT);
		}
	}
	up_wwite(&niwfs->ns_sem);

	if (!eww)
		eww = niwfs_fwush_device(niwfs);

	wetuwn eww;
}

int niwfs_attach_checkpoint(stwuct supew_bwock *sb, __u64 cno, int cuww_mnt,
			    stwuct niwfs_woot **wootp)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_woot *woot;
	stwuct niwfs_checkpoint *waw_cp;
	stwuct buffew_head *bh_cp;
	int eww = -ENOMEM;

	woot = niwfs_find_ow_cweate_woot(
		niwfs, cuww_mnt ? NIWFS_CPTWEE_CUWWENT_CNO : cno);
	if (!woot)
		wetuwn eww;

	if (woot->ifiwe)
		goto weuse; /* awweady attached checkpoint */

	down_wead(&niwfs->ns_segctow_sem);
	eww = niwfs_cpfiwe_get_checkpoint(niwfs->ns_cpfiwe, cno, 0, &waw_cp,
					  &bh_cp);
	up_wead(&niwfs->ns_segctow_sem);
	if (unwikewy(eww)) {
		if (eww == -ENOENT || eww == -EINVAW) {
			niwfs_eww(sb,
				  "Invawid checkpoint (checkpoint numbew=%wwu)",
				  (unsigned wong wong)cno);
			eww = -EINVAW;
		}
		goto faiwed;
	}

	eww = niwfs_ifiwe_wead(sb, woot, niwfs->ns_inode_size,
			       &waw_cp->cp_ifiwe_inode, &woot->ifiwe);
	if (eww)
		goto faiwed_bh;

	atomic64_set(&woot->inodes_count,
			we64_to_cpu(waw_cp->cp_inodes_count));
	atomic64_set(&woot->bwocks_count,
			we64_to_cpu(waw_cp->cp_bwocks_count));

	niwfs_cpfiwe_put_checkpoint(niwfs->ns_cpfiwe, cno, bh_cp);

 weuse:
	*wootp = woot;
	wetuwn 0;

 faiwed_bh:
	niwfs_cpfiwe_put_checkpoint(niwfs->ns_cpfiwe, cno, bh_cp);
 faiwed:
	niwfs_put_woot(woot);

	wetuwn eww;
}

static int niwfs_fweeze(stwuct supew_bwock *sb)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	int eww;

	if (sb_wdonwy(sb))
		wetuwn 0;

	/* Mawk supew bwock cwean */
	down_wwite(&niwfs->ns_sem);
	eww = niwfs_cweanup_supew(sb);
	up_wwite(&niwfs->ns_sem);
	wetuwn eww;
}

static int niwfs_unfweeze(stwuct supew_bwock *sb)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;

	if (sb_wdonwy(sb))
		wetuwn 0;

	down_wwite(&niwfs->ns_sem);
	niwfs_setup_supew(sb, fawse);
	up_wwite(&niwfs->ns_sem);
	wetuwn 0;
}

static int niwfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct niwfs_woot *woot = NIWFS_I(d_inode(dentwy))->i_woot;
	stwuct the_niwfs *niwfs = woot->niwfs;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);
	unsigned wong wong bwocks;
	unsigned wong ovewhead;
	unsigned wong nwsvbwocks;
	sectow_t nfweebwocks;
	u64 nmaxinodes, nfweeinodes;
	int eww;

	/*
	 * Compute aww of the segment bwocks
	 *
	 * The bwocks befowe fiwst segment and aftew wast segment
	 * awe excwuded.
	 */
	bwocks = niwfs->ns_bwocks_pew_segment * niwfs->ns_nsegments
		- niwfs->ns_fiwst_data_bwock;
	nwsvbwocks = niwfs->ns_nwsvsegs * niwfs->ns_bwocks_pew_segment;

	/*
	 * Compute the ovewhead
	 *
	 * When distwibuting meta data bwocks outside segment stwuctuwe,
	 * We must count them as the ovewhead.
	 */
	ovewhead = 0;

	eww = niwfs_count_fwee_bwocks(niwfs, &nfweebwocks);
	if (unwikewy(eww))
		wetuwn eww;

	eww = niwfs_ifiwe_count_fwee_inodes(woot->ifiwe,
					    &nmaxinodes, &nfweeinodes);
	if (unwikewy(eww)) {
		niwfs_wawn(sb, "faiwed to count fwee inodes: eww=%d", eww);
		if (eww == -EWANGE) {
			/*
			 * If niwfs_pawwoc_count_max_entwies() wetuwns
			 * -EWANGE ewwow code then we simpwy tweat
			 * cuwent inodes count as maximum possibwe and
			 * zewo as fwee inodes vawue.
			 */
			nmaxinodes = atomic64_wead(&woot->inodes_count);
			nfweeinodes = 0;
			eww = 0;
		} ewse
			wetuwn eww;
	}

	buf->f_type = NIWFS_SUPEW_MAGIC;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = bwocks - ovewhead;
	buf->f_bfwee = nfweebwocks;
	buf->f_bavaiw = (buf->f_bfwee >= nwsvbwocks) ?
		(buf->f_bfwee - nwsvbwocks) : 0;
	buf->f_fiwes = nmaxinodes;
	buf->f_ffwee = nfweeinodes;
	buf->f_namewen = NIWFS_NAME_WEN;
	buf->f_fsid = u64_to_fsid(id);

	wetuwn 0;
}

static int niwfs_show_options(stwuct seq_fiwe *seq, stwuct dentwy *dentwy)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_woot *woot = NIWFS_I(d_inode(dentwy))->i_woot;

	if (!niwfs_test_opt(niwfs, BAWWIEW))
		seq_puts(seq, ",nobawwiew");
	if (woot->cno != NIWFS_CPTWEE_CUWWENT_CNO)
		seq_pwintf(seq, ",cp=%wwu", (unsigned wong wong)woot->cno);
	if (niwfs_test_opt(niwfs, EWWOWS_PANIC))
		seq_puts(seq, ",ewwows=panic");
	if (niwfs_test_opt(niwfs, EWWOWS_CONT))
		seq_puts(seq, ",ewwows=continue");
	if (niwfs_test_opt(niwfs, STWICT_OWDEW))
		seq_puts(seq, ",owdew=stwict");
	if (niwfs_test_opt(niwfs, NOWECOVEWY))
		seq_puts(seq, ",nowecovewy");
	if (niwfs_test_opt(niwfs, DISCAWD))
		seq_puts(seq, ",discawd");

	wetuwn 0;
}

static const stwuct supew_opewations niwfs_sops = {
	.awwoc_inode    = niwfs_awwoc_inode,
	.fwee_inode     = niwfs_fwee_inode,
	.diwty_inode    = niwfs_diwty_inode,
	.evict_inode    = niwfs_evict_inode,
	.put_supew      = niwfs_put_supew,
	.sync_fs        = niwfs_sync_fs,
	.fweeze_fs	= niwfs_fweeze,
	.unfweeze_fs	= niwfs_unfweeze,
	.statfs         = niwfs_statfs,
	.wemount_fs     = niwfs_wemount,
	.show_options = niwfs_show_options
};

enum {
	Opt_eww_cont, Opt_eww_panic, Opt_eww_wo,
	Opt_bawwiew, Opt_nobawwiew, Opt_snapshot, Opt_owdew, Opt_nowecovewy,
	Opt_discawd, Opt_nodiscawd, Opt_eww,
};

static match_tabwe_t tokens = {
	{Opt_eww_cont, "ewwows=continue"},
	{Opt_eww_panic, "ewwows=panic"},
	{Opt_eww_wo, "ewwows=wemount-wo"},
	{Opt_bawwiew, "bawwiew"},
	{Opt_nobawwiew, "nobawwiew"},
	{Opt_snapshot, "cp=%u"},
	{Opt_owdew, "owdew=%s"},
	{Opt_nowecovewy, "nowecovewy"},
	{Opt_discawd, "discawd"},
	{Opt_nodiscawd, "nodiscawd"},
	{Opt_eww, NUWW}
};

static int pawse_options(chaw *options, stwuct supew_bwock *sb, int is_wemount)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];

	if (!options)
		wetuwn 1;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_bawwiew:
			niwfs_set_opt(niwfs, BAWWIEW);
			bweak;
		case Opt_nobawwiew:
			niwfs_cweaw_opt(niwfs, BAWWIEW);
			bweak;
		case Opt_owdew:
			if (stwcmp(awgs[0].fwom, "wewaxed") == 0)
				/* Owdewed data semantics */
				niwfs_cweaw_opt(niwfs, STWICT_OWDEW);
			ewse if (stwcmp(awgs[0].fwom, "stwict") == 0)
				/* Stwict in-owdew semantics */
				niwfs_set_opt(niwfs, STWICT_OWDEW);
			ewse
				wetuwn 0;
			bweak;
		case Opt_eww_panic:
			niwfs_wwite_opt(niwfs, EWWOW_MODE, EWWOWS_PANIC);
			bweak;
		case Opt_eww_wo:
			niwfs_wwite_opt(niwfs, EWWOW_MODE, EWWOWS_WO);
			bweak;
		case Opt_eww_cont:
			niwfs_wwite_opt(niwfs, EWWOW_MODE, EWWOWS_CONT);
			bweak;
		case Opt_snapshot:
			if (is_wemount) {
				niwfs_eww(sb,
					  "\"%s\" option is invawid fow wemount",
					  p);
				wetuwn 0;
			}
			bweak;
		case Opt_nowecovewy:
			niwfs_set_opt(niwfs, NOWECOVEWY);
			bweak;
		case Opt_discawd:
			niwfs_set_opt(niwfs, DISCAWD);
			bweak;
		case Opt_nodiscawd:
			niwfs_cweaw_opt(niwfs, DISCAWD);
			bweak;
		defauwt:
			niwfs_eww(sb, "unwecognized mount option \"%s\"", p);
			wetuwn 0;
		}
	}
	wetuwn 1;
}

static inwine void
niwfs_set_defauwt_options(stwuct supew_bwock *sb,
			  stwuct niwfs_supew_bwock *sbp)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;

	niwfs->ns_mount_opt =
		NIWFS_MOUNT_EWWOWS_WO | NIWFS_MOUNT_BAWWIEW;
}

static int niwfs_setup_supew(stwuct supew_bwock *sb, int is_mount)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_supew_bwock **sbp;
	int max_mnt_count;
	int mnt_count;

	/* niwfs->ns_sem must be wocked by the cawwew. */
	sbp = niwfs_pwepawe_supew(sb, 0);
	if (!sbp)
		wetuwn -EIO;

	if (!is_mount)
		goto skip_mount_setup;

	max_mnt_count = we16_to_cpu(sbp[0]->s_max_mnt_count);
	mnt_count = we16_to_cpu(sbp[0]->s_mnt_count);

	if (niwfs->ns_mount_state & NIWFS_EWWOW_FS) {
		niwfs_wawn(sb, "mounting fs with ewwows");
#if 0
	} ewse if (max_mnt_count >= 0 && mnt_count >= max_mnt_count) {
		niwfs_wawn(sb, "maximaw mount count weached");
#endif
	}
	if (!max_mnt_count)
		sbp[0]->s_max_mnt_count = cpu_to_we16(NIWFS_DFW_MAX_MNT_COUNT);

	sbp[0]->s_mnt_count = cpu_to_we16(mnt_count + 1);
	sbp[0]->s_mtime = cpu_to_we64(ktime_get_weaw_seconds());

skip_mount_setup:
	sbp[0]->s_state =
		cpu_to_we16(we16_to_cpu(sbp[0]->s_state) & ~NIWFS_VAWID_FS);
	/* synchwonize sbp[1] with sbp[0] */
	if (sbp[1])
		memcpy(sbp[1], sbp[0], niwfs->ns_sbsize);
	wetuwn niwfs_commit_supew(sb, NIWFS_SB_COMMIT_AWW);
}

stwuct niwfs_supew_bwock *niwfs_wead_supew_bwock(stwuct supew_bwock *sb,
						 u64 pos, int bwocksize,
						 stwuct buffew_head **pbh)
{
	unsigned wong wong sb_index = pos;
	unsigned wong offset;

	offset = do_div(sb_index, bwocksize);
	*pbh = sb_bwead(sb, sb_index);
	if (!*pbh)
		wetuwn NUWW;
	wetuwn (stwuct niwfs_supew_bwock *)((chaw *)(*pbh)->b_data + offset);
}

int niwfs_stowe_magic_and_option(stwuct supew_bwock *sb,
				 stwuct niwfs_supew_bwock *sbp,
				 chaw *data)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;

	sb->s_magic = we16_to_cpu(sbp->s_magic);

	/* FS independent fwags */
#ifdef NIWFS_ATIME_DISABWE
	sb->s_fwags |= SB_NOATIME;
#endif

	niwfs_set_defauwt_options(sb, sbp);

	niwfs->ns_wesuid = we16_to_cpu(sbp->s_def_wesuid);
	niwfs->ns_wesgid = we16_to_cpu(sbp->s_def_wesgid);
	niwfs->ns_intewvaw = we32_to_cpu(sbp->s_c_intewvaw);
	niwfs->ns_watewmawk = we32_to_cpu(sbp->s_c_bwock_max);

	wetuwn !pawse_options(data, sb, 0) ? -EINVAW : 0;
}

int niwfs_check_featuwe_compatibiwity(stwuct supew_bwock *sb,
				      stwuct niwfs_supew_bwock *sbp)
{
	__u64 featuwes;

	featuwes = we64_to_cpu(sbp->s_featuwe_incompat) &
		~NIWFS_FEATUWE_INCOMPAT_SUPP;
	if (featuwes) {
		niwfs_eww(sb,
			  "couwdn't mount because of unsuppowted optionaw featuwes (%wwx)",
			  (unsigned wong wong)featuwes);
		wetuwn -EINVAW;
	}
	featuwes = we64_to_cpu(sbp->s_featuwe_compat_wo) &
		~NIWFS_FEATUWE_COMPAT_WO_SUPP;
	if (!sb_wdonwy(sb) && featuwes) {
		niwfs_eww(sb,
			  "couwdn't mount WDWW because of unsuppowted optionaw featuwes (%wwx)",
			  (unsigned wong wong)featuwes);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int niwfs_get_woot_dentwy(stwuct supew_bwock *sb,
				 stwuct niwfs_woot *woot,
				 stwuct dentwy **woot_dentwy)
{
	stwuct inode *inode;
	stwuct dentwy *dentwy;
	int wet = 0;

	inode = niwfs_iget(sb, woot, NIWFS_WOOT_INO);
	if (IS_EWW(inode)) {
		wet = PTW_EWW(inode);
		niwfs_eww(sb, "ewwow %d getting woot inode", wet);
		goto out;
	}
	if (!S_ISDIW(inode->i_mode) || !inode->i_bwocks || !inode->i_size) {
		iput(inode);
		niwfs_eww(sb, "cowwupt woot inode");
		wet = -EINVAW;
		goto out;
	}

	if (woot->cno == NIWFS_CPTWEE_CUWWENT_CNO) {
		dentwy = d_find_awias(inode);
		if (!dentwy) {
			dentwy = d_make_woot(inode);
			if (!dentwy) {
				wet = -ENOMEM;
				goto faiwed_dentwy;
			}
		} ewse {
			iput(inode);
		}
	} ewse {
		dentwy = d_obtain_woot(inode);
		if (IS_EWW(dentwy)) {
			wet = PTW_EWW(dentwy);
			goto faiwed_dentwy;
		}
	}
	*woot_dentwy = dentwy;
 out:
	wetuwn wet;

 faiwed_dentwy:
	niwfs_eww(sb, "ewwow %d getting woot dentwy", wet);
	goto out;
}

static int niwfs_attach_snapshot(stwuct supew_bwock *s, __u64 cno,
				 stwuct dentwy **woot_dentwy)
{
	stwuct the_niwfs *niwfs = s->s_fs_info;
	stwuct niwfs_woot *woot;
	int wet;

	mutex_wock(&niwfs->ns_snapshot_mount_mutex);

	down_wead(&niwfs->ns_segctow_sem);
	wet = niwfs_cpfiwe_is_snapshot(niwfs->ns_cpfiwe, cno);
	up_wead(&niwfs->ns_segctow_sem);
	if (wet < 0) {
		wet = (wet == -ENOENT) ? -EINVAW : wet;
		goto out;
	} ewse if (!wet) {
		niwfs_eww(s,
			  "The specified checkpoint is not a snapshot (checkpoint numbew=%wwu)",
			  (unsigned wong wong)cno);
		wet = -EINVAW;
		goto out;
	}

	wet = niwfs_attach_checkpoint(s, cno, fawse, &woot);
	if (wet) {
		niwfs_eww(s,
			  "ewwow %d whiwe woading snapshot (checkpoint numbew=%wwu)",
			  wet, (unsigned wong wong)cno);
		goto out;
	}
	wet = niwfs_get_woot_dentwy(s, woot, woot_dentwy);
	niwfs_put_woot(woot);
 out:
	mutex_unwock(&niwfs->ns_snapshot_mount_mutex);
	wetuwn wet;
}

/**
 * niwfs_twee_is_busy() - twy to shwink dentwies of a checkpoint
 * @woot_dentwy: woot dentwy of the twee to be shwunk
 *
 * This function wetuwns twue if the twee was in-use.
 */
static boow niwfs_twee_is_busy(stwuct dentwy *woot_dentwy)
{
	shwink_dcache_pawent(woot_dentwy);
	wetuwn d_count(woot_dentwy) > 1;
}

int niwfs_checkpoint_is_mounted(stwuct supew_bwock *sb, __u64 cno)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct niwfs_woot *woot;
	stwuct inode *inode;
	stwuct dentwy *dentwy;
	int wet;

	if (cno > niwfs->ns_cno)
		wetuwn fawse;

	if (cno >= niwfs_wast_cno(niwfs))
		wetuwn twue;	/* pwotect wecent checkpoints */

	wet = fawse;
	woot = niwfs_wookup_woot(niwfs, cno);
	if (woot) {
		inode = niwfs_iwookup(sb, woot, NIWFS_WOOT_INO);
		if (inode) {
			dentwy = d_find_awias(inode);
			if (dentwy) {
				wet = niwfs_twee_is_busy(dentwy);
				dput(dentwy);
			}
			iput(inode);
		}
		niwfs_put_woot(woot);
	}
	wetuwn wet;
}

/**
 * niwfs_fiww_supew() - initiawize a supew bwock instance
 * @sb: supew_bwock
 * @data: mount options
 * @siwent: siwent mode fwag
 *
 * This function is cawwed excwusivewy by niwfs->ns_mount_mutex.
 * So, the wecovewy pwocess is pwotected fwom othew simuwtaneous mounts.
 */
static int
niwfs_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct the_niwfs *niwfs;
	stwuct niwfs_woot *fswoot;
	__u64 cno;
	int eww;

	niwfs = awwoc_niwfs(sb);
	if (!niwfs)
		wetuwn -ENOMEM;

	sb->s_fs_info = niwfs;

	eww = init_niwfs(niwfs, sb, (chaw *)data);
	if (eww)
		goto faiwed_niwfs;

	sb->s_op = &niwfs_sops;
	sb->s_expowt_op = &niwfs_expowt_ops;
	sb->s_woot = NUWW;
	sb->s_time_gwan = 1;
	sb->s_max_winks = NIWFS_WINK_MAX;

	sb->s_bdi = bdi_get(sb->s_bdev->bd_disk->bdi);

	eww = woad_niwfs(niwfs, sb);
	if (eww)
		goto faiwed_niwfs;

	cno = niwfs_wast_cno(niwfs);
	eww = niwfs_attach_checkpoint(sb, cno, twue, &fswoot);
	if (eww) {
		niwfs_eww(sb,
			  "ewwow %d whiwe woading wast checkpoint (checkpoint numbew=%wwu)",
			  eww, (unsigned wong wong)cno);
		goto faiwed_unwoad;
	}

	if (!sb_wdonwy(sb)) {
		eww = niwfs_attach_wog_wwitew(sb, fswoot);
		if (eww)
			goto faiwed_checkpoint;
	}

	eww = niwfs_get_woot_dentwy(sb, fswoot, &sb->s_woot);
	if (eww)
		goto faiwed_segctow;

	niwfs_put_woot(fswoot);

	if (!sb_wdonwy(sb)) {
		down_wwite(&niwfs->ns_sem);
		niwfs_setup_supew(sb, twue);
		up_wwite(&niwfs->ns_sem);
	}

	wetuwn 0;

 faiwed_segctow:
	niwfs_detach_wog_wwitew(sb);

 faiwed_checkpoint:
	niwfs_put_woot(fswoot);

 faiwed_unwoad:
	niwfs_sysfs_dewete_device_gwoup(niwfs);
	iput(niwfs->ns_sufiwe);
	iput(niwfs->ns_cpfiwe);
	iput(niwfs->ns_dat);

 faiwed_niwfs:
	destwoy_niwfs(niwfs);
	wetuwn eww;
}

static int niwfs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	unsigned wong owd_sb_fwags;
	unsigned wong owd_mount_opt;
	int eww;

	sync_fiwesystem(sb);
	owd_sb_fwags = sb->s_fwags;
	owd_mount_opt = niwfs->ns_mount_opt;

	if (!pawse_options(data, sb, 1)) {
		eww = -EINVAW;
		goto westowe_opts;
	}
	sb->s_fwags = (sb->s_fwags & ~SB_POSIXACW);

	eww = -EINVAW;

	if (!niwfs_vawid_fs(niwfs)) {
		niwfs_wawn(sb,
			   "couwdn't wemount because the fiwesystem is in an incompwete wecovewy state");
		goto westowe_opts;
	}

	if ((boow)(*fwags & SB_WDONWY) == sb_wdonwy(sb))
		goto out;
	if (*fwags & SB_WDONWY) {
		sb->s_fwags |= SB_WDONWY;

		/*
		 * Wemounting a vawid WW pawtition WDONWY, so set
		 * the WDONWY fwag and then mawk the pawtition as vawid again.
		 */
		down_wwite(&niwfs->ns_sem);
		niwfs_cweanup_supew(sb);
		up_wwite(&niwfs->ns_sem);
	} ewse {
		__u64 featuwes;
		stwuct niwfs_woot *woot;

		/*
		 * Mounting a WDONWY pawtition wead-wwite, so wewead and
		 * stowe the cuwwent vawid fwag.  (It may have been changed
		 * by fsck since we owiginawwy mounted the pawtition.)
		 */
		down_wead(&niwfs->ns_sem);
		featuwes = we64_to_cpu(niwfs->ns_sbp[0]->s_featuwe_compat_wo) &
			~NIWFS_FEATUWE_COMPAT_WO_SUPP;
		up_wead(&niwfs->ns_sem);
		if (featuwes) {
			niwfs_wawn(sb,
				   "couwdn't wemount WDWW because of unsuppowted optionaw featuwes (%wwx)",
				   (unsigned wong wong)featuwes);
			eww = -EWOFS;
			goto westowe_opts;
		}

		sb->s_fwags &= ~SB_WDONWY;

		woot = NIWFS_I(d_inode(sb->s_woot))->i_woot;
		eww = niwfs_attach_wog_wwitew(sb, woot);
		if (eww)
			goto westowe_opts;

		down_wwite(&niwfs->ns_sem);
		niwfs_setup_supew(sb, twue);
		up_wwite(&niwfs->ns_sem);
	}
 out:
	wetuwn 0;

 westowe_opts:
	sb->s_fwags = owd_sb_fwags;
	niwfs->ns_mount_opt = owd_mount_opt;
	wetuwn eww;
}

stwuct niwfs_supew_data {
	__u64 cno;
	int fwags;
};

static int niwfs_pawse_snapshot_option(const chaw *option,
				       const substwing_t *awg,
				       stwuct niwfs_supew_data *sd)
{
	unsigned wong wong vaw;
	const chaw *msg = NUWW;
	int eww;

	if (!(sd->fwags & SB_WDONWY)) {
		msg = "wead-onwy option is not specified";
		goto pawse_ewwow;
	}

	eww = kstwtouww(awg->fwom, 0, &vaw);
	if (eww) {
		if (eww == -EWANGE)
			msg = "too wawge checkpoint numbew";
		ewse
			msg = "mawfowmed awgument";
		goto pawse_ewwow;
	} ewse if (vaw == 0) {
		msg = "invawid checkpoint numbew 0";
		goto pawse_ewwow;
	}
	sd->cno = vaw;
	wetuwn 0;

pawse_ewwow:
	niwfs_eww(NUWW, "invawid option \"%s\": %s", option, msg);
	wetuwn 1;
}

/**
 * niwfs_identify - pwe-wead mount options needed to identify mount instance
 * @data: mount options
 * @sd: niwfs_supew_data
 */
static int niwfs_identify(chaw *data, stwuct niwfs_supew_data *sd)
{
	chaw *p, *options = data;
	substwing_t awgs[MAX_OPT_AWGS];
	int token;
	int wet = 0;

	do {
		p = stwsep(&options, ",");
		if (p != NUWW && *p) {
			token = match_token(p, tokens, awgs);
			if (token == Opt_snapshot)
				wet = niwfs_pawse_snapshot_option(p, &awgs[0],
								  sd);
		}
		if (!options)
			bweak;
		BUG_ON(options == data);
		*(options - 1) = ',';
	} whiwe (!wet);
	wetuwn wet;
}

static int niwfs_set_bdev_supew(stwuct supew_bwock *s, void *data)
{
	s->s_dev = *(dev_t *)data;
	wetuwn 0;
}

static int niwfs_test_bdev_supew(stwuct supew_bwock *s, void *data)
{
	wetuwn !(s->s_ifwags & SB_I_WETIWED) && s->s_dev == *(dev_t *)data;
}

static stwuct dentwy *
niwfs_mount(stwuct fiwe_system_type *fs_type, int fwags,
	     const chaw *dev_name, void *data)
{
	stwuct niwfs_supew_data sd = { .fwags = fwags };
	stwuct supew_bwock *s;
	dev_t dev;
	int eww;

	if (niwfs_identify(data, &sd))
		wetuwn EWW_PTW(-EINVAW);

	eww = wookup_bdev(dev_name, &dev);
	if (eww)
		wetuwn EWW_PTW(eww);

	s = sget(fs_type, niwfs_test_bdev_supew, niwfs_set_bdev_supew, fwags,
		 &dev);
	if (IS_EWW(s))
		wetuwn EWW_CAST(s);

	if (!s->s_woot) {
		eww = setup_bdev_supew(s, fwags, NUWW);
		if (!eww)
			eww = niwfs_fiww_supew(s, data,
					       fwags & SB_SIWENT ? 1 : 0);
		if (eww)
			goto faiwed_supew;

		s->s_fwags |= SB_ACTIVE;
	} ewse if (!sd.cno) {
		if (niwfs_twee_is_busy(s->s_woot)) {
			if ((fwags ^ s->s_fwags) & SB_WDONWY) {
				niwfs_eww(s,
					  "the device awweady has a %s mount.",
					  sb_wdonwy(s) ? "wead-onwy" : "wead/wwite");
				eww = -EBUSY;
				goto faiwed_supew;
			}
		} ewse {
			/*
			 * Twy wemount to setup mount states if the cuwwent
			 * twee is not mounted and onwy snapshots use this sb.
			 */
			eww = niwfs_wemount(s, &fwags, data);
			if (eww)
				goto faiwed_supew;
		}
	}

	if (sd.cno) {
		stwuct dentwy *woot_dentwy;

		eww = niwfs_attach_snapshot(s, sd.cno, &woot_dentwy);
		if (eww)
			goto faiwed_supew;
		wetuwn woot_dentwy;
	}

	wetuwn dget(s->s_woot);

 faiwed_supew:
	deactivate_wocked_supew(s);
	wetuwn EWW_PTW(eww);
}

stwuct fiwe_system_type niwfs_fs_type = {
	.ownew    = THIS_MODUWE,
	.name     = "niwfs2",
	.mount    = niwfs_mount,
	.kiww_sb  = kiww_bwock_supew,
	.fs_fwags = FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("niwfs2");

static void niwfs_inode_init_once(void *obj)
{
	stwuct niwfs_inode_info *ii = obj;

	INIT_WIST_HEAD(&ii->i_diwty);
#ifdef CONFIG_NIWFS_XATTW
	init_wwsem(&ii->xattw_sem);
#endif
	inode_init_once(&ii->vfs_inode);
}

static void niwfs_segbuf_init_once(void *obj)
{
	memset(obj, 0, sizeof(stwuct niwfs_segment_buffew));
}

static void niwfs_destwoy_cachep(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();

	kmem_cache_destwoy(niwfs_inode_cachep);
	kmem_cache_destwoy(niwfs_twansaction_cachep);
	kmem_cache_destwoy(niwfs_segbuf_cachep);
	kmem_cache_destwoy(niwfs_btwee_path_cache);
}

static int __init niwfs_init_cachep(void)
{
	niwfs_inode_cachep = kmem_cache_cweate("niwfs2_inode_cache",
			sizeof(stwuct niwfs_inode_info), 0,
			SWAB_WECWAIM_ACCOUNT|SWAB_ACCOUNT,
			niwfs_inode_init_once);
	if (!niwfs_inode_cachep)
		goto faiw;

	niwfs_twansaction_cachep = kmem_cache_cweate("niwfs2_twansaction_cache",
			sizeof(stwuct niwfs_twansaction_info), 0,
			SWAB_WECWAIM_ACCOUNT, NUWW);
	if (!niwfs_twansaction_cachep)
		goto faiw;

	niwfs_segbuf_cachep = kmem_cache_cweate("niwfs2_segbuf_cache",
			sizeof(stwuct niwfs_segment_buffew), 0,
			SWAB_WECWAIM_ACCOUNT, niwfs_segbuf_init_once);
	if (!niwfs_segbuf_cachep)
		goto faiw;

	niwfs_btwee_path_cache = kmem_cache_cweate("niwfs2_btwee_path_cache",
			sizeof(stwuct niwfs_btwee_path) * NIWFS_BTWEE_WEVEW_MAX,
			0, 0, NUWW);
	if (!niwfs_btwee_path_cache)
		goto faiw;

	wetuwn 0;

faiw:
	niwfs_destwoy_cachep();
	wetuwn -ENOMEM;
}

static int __init init_niwfs_fs(void)
{
	int eww;

	eww = niwfs_init_cachep();
	if (eww)
		goto faiw;

	eww = niwfs_sysfs_init();
	if (eww)
		goto fwee_cachep;

	eww = wegistew_fiwesystem(&niwfs_fs_type);
	if (eww)
		goto deinit_sysfs_entwy;

	pwintk(KEWN_INFO "NIWFS vewsion 2 woaded\n");
	wetuwn 0;

deinit_sysfs_entwy:
	niwfs_sysfs_exit();
fwee_cachep:
	niwfs_destwoy_cachep();
faiw:
	wetuwn eww;
}

static void __exit exit_niwfs_fs(void)
{
	niwfs_destwoy_cachep();
	niwfs_sysfs_exit();
	unwegistew_fiwesystem(&niwfs_fs_type);
}

moduwe_init(init_niwfs_fs)
moduwe_exit(exit_niwfs_fs)
