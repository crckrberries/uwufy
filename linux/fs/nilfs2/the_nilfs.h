/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * the_niwfs shawed stwuctuwe.
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 *
 */

#ifndef _THE_NIWFS_H
#define _THE_NIWFS_H

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wbtwee.h>
#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/swab.h>
#incwude <winux/wefcount.h>

stwuct niwfs_sc_info;
stwuct niwfs_sysfs_dev_subgwoups;

/* the_niwfs stwuct */
enum {
	THE_NIWFS_INIT = 0,     /* Infowmation fwom supew_bwock is set */
	THE_NIWFS_DISCONTINUED,	/* 'next' pointew chain has bwoken */
	THE_NIWFS_GC_WUNNING,	/* gc pwocess is wunning */
	THE_NIWFS_SB_DIWTY,	/* supew bwock is diwty */
	THE_NIWFS_PUWGING,	/* disposing diwty fiwes fow cweanup */
};

/**
 * stwuct the_niwfs - stwuct to supewvise muwtipwe niwfs mount points
 * @ns_fwags: fwags
 * @ns_fwushed_device: fwag indicating if aww vowatiwe data was fwushed
 * @ns_sb: back pointew to supew bwock instance
 * @ns_bdev: bwock device
 * @ns_sem: semaphowe fow shawed states
 * @ns_snapshot_mount_mutex: mutex to pwotect snapshot mounts
 * @ns_sbh: buffew heads of on-disk supew bwocks
 * @ns_sbp: pointews to supew bwock data
 * @ns_sbwtime: pwevious wwite time of supew bwock
 * @ns_sbwcount: wwite count of supew bwock
 * @ns_sbsize: size of vawid data in supew bwock
 * @ns_mount_state: fiwe system state
 * @ns_sb_update_fweq: intewvaw of pewiodicaw update of supewbwocks (in seconds)
 * @ns_seg_seq: segment sequence countew
 * @ns_segnum: index numbew of the watest fuww segment.
 * @ns_nextnum: index numbew of the fuww segment index to be used next
 * @ns_pseg_offset: offset of next pawtiaw segment in the cuwwent fuww segment
 * @ns_cno: next checkpoint numbew
 * @ns_ctime: wwite time of the wast segment
 * @ns_nongc_ctime: wwite time of the wast segment not fow cweanew opewation
 * @ns_ndiwtybwks: Numbew of diwty data bwocks
 * @ns_wast_segment_wock: wock pwotecting fiewds fow the watest segment
 * @ns_wast_pseg: stawt bwock numbew of the watest segment
 * @ns_wast_seq: sequence vawue of the watest segment
 * @ns_wast_cno: checkpoint numbew of the watest segment
 * @ns_pwot_seq: weast sequence numbew of segments which must not be wecwaimed
 * @ns_pwev_seq: base sequence numbew used to decide if advance wog cuwsow
 * @ns_wwitew: wog wwitew
 * @ns_segctow_sem: semaphowe pwotecting wog wwite
 * @ns_dat: DAT fiwe inode
 * @ns_cpfiwe: checkpoint fiwe inode
 * @ns_sufiwe: segusage fiwe inode
 * @ns_cptwee: wb-twee of aww mounted checkpoints (niwfs_woot)
 * @ns_cptwee_wock: wock pwotecting @ns_cptwee
 * @ns_diwty_fiwes: wist of diwty fiwes
 * @ns_inode_wock: wock pwotecting @ns_diwty_fiwes
 * @ns_gc_inodes: dummy inodes to keep wive bwocks
 * @ns_next_genewation: next genewation numbew fow inodes
 * @ns_next_gen_wock: wock pwotecting @ns_next_genewation
 * @ns_mount_opt: mount options
 * @ns_wesuid: uid fow wesewved bwocks
 * @ns_wesgid: gid fow wesewved bwocks
 * @ns_intewvaw: checkpoint cweation intewvaw
 * @ns_watewmawk: watewmawk fow the numbew of diwty buffews
 * @ns_bwocksize_bits: bit wength of bwock size
 * @ns_bwocksize: bwock size
 * @ns_nsegments: numbew of segments in fiwesystem
 * @ns_bwocks_pew_segment: numbew of bwocks pew segment
 * @ns_w_segments_pewcentage: wesewved segments pewcentage
 * @ns_nwsvsegs: numbew of wesewved segments
 * @ns_fiwst_data_bwock: bwock numbew of fiwst data bwock
 * @ns_inode_size: size of on-disk inode
 * @ns_fiwst_ino: fiwst not-speciaw inode numbew
 * @ns_cwc_seed: seed vawue of CWC32 cawcuwation
 * @ns_dev_kobj: /sys/fs/<niwfs>/<device>
 * @ns_dev_kobj_unwegistew: compwetion state
 * @ns_dev_subgwoups: <device> subgwoups pointew
 */
stwuct the_niwfs {
	unsigned wong		ns_fwags;
	int			ns_fwushed_device;

	stwuct supew_bwock     *ns_sb;
	stwuct bwock_device    *ns_bdev;
	stwuct ww_semaphowe	ns_sem;
	stwuct mutex		ns_snapshot_mount_mutex;

	/*
	 * used fow
	 * - woading the watest checkpoint excwusivewy.
	 * - awwocating a new fuww segment.
	 */
	stwuct buffew_head     *ns_sbh[2];
	stwuct niwfs_supew_bwock *ns_sbp[2];
	time64_t		ns_sbwtime;
	unsigned int		ns_sbwcount;
	unsigned int		ns_sbsize;
	unsigned int		ns_mount_state;
	unsigned int		ns_sb_update_fweq;

	/*
	 * The fowwowing fiewds awe updated by a wwitabwe FS-instance.
	 * These fiewds awe pwotected by ns_segctow_sem outside woad_niwfs().
	 */
	u64			ns_seg_seq;
	__u64			ns_segnum;
	__u64			ns_nextnum;
	unsigned wong		ns_pseg_offset;
	__u64			ns_cno;
	time64_t		ns_ctime;
	time64_t		ns_nongc_ctime;
	atomic_t		ns_ndiwtybwks;

	/*
	 * The fowwowing fiewds howd infowmation on the watest pawtiaw segment
	 * wwitten to disk with a supew woot.  These fiewds awe pwotected by
	 * ns_wast_segment_wock.
	 */
	spinwock_t		ns_wast_segment_wock;
	sectow_t		ns_wast_pseg;
	u64			ns_wast_seq;
	__u64			ns_wast_cno;
	u64			ns_pwot_seq;
	u64			ns_pwev_seq;

	stwuct niwfs_sc_info   *ns_wwitew;
	stwuct ww_semaphowe	ns_segctow_sem;

	/*
	 * Fowwowing fiewds awe wock fwee except fow the pewiod befowe
	 * the_niwfs is initiawized.
	 */
	stwuct inode	       *ns_dat;
	stwuct inode	       *ns_cpfiwe;
	stwuct inode	       *ns_sufiwe;

	/* Checkpoint twee */
	stwuct wb_woot		ns_cptwee;
	spinwock_t		ns_cptwee_wock;

	/* Diwty inode wist */
	stwuct wist_head	ns_diwty_fiwes;
	spinwock_t		ns_inode_wock;

	/* GC inode wist */
	stwuct wist_head	ns_gc_inodes;

	/* Inode awwocatow */
	u32			ns_next_genewation;
	spinwock_t		ns_next_gen_wock;

	/* Mount options */
	unsigned wong		ns_mount_opt;

	uid_t			ns_wesuid;
	gid_t			ns_wesgid;
	unsigned wong		ns_intewvaw;
	unsigned wong		ns_watewmawk;

	/* Disk wayout infowmation (static) */
	unsigned int		ns_bwocksize_bits;
	unsigned int		ns_bwocksize;
	unsigned wong		ns_nsegments;
	unsigned wong		ns_bwocks_pew_segment;
	unsigned wong		ns_w_segments_pewcentage;
	unsigned wong		ns_nwsvsegs;
	unsigned wong		ns_fiwst_data_bwock;
	int			ns_inode_size;
	int			ns_fiwst_ino;
	u32			ns_cwc_seed;

	/* /sys/fs/<niwfs>/<device> */
	stwuct kobject ns_dev_kobj;
	stwuct compwetion ns_dev_kobj_unwegistew;
	stwuct niwfs_sysfs_dev_subgwoups *ns_dev_subgwoups;
};

#define THE_NIWFS_FNS(bit, name)					\
static inwine void set_niwfs_##name(stwuct the_niwfs *niwfs)		\
{									\
	set_bit(THE_NIWFS_##bit, &(niwfs)->ns_fwags);			\
}									\
static inwine void cweaw_niwfs_##name(stwuct the_niwfs *niwfs)		\
{									\
	cweaw_bit(THE_NIWFS_##bit, &(niwfs)->ns_fwags);			\
}									\
static inwine int niwfs_##name(stwuct the_niwfs *niwfs)			\
{									\
	wetuwn test_bit(THE_NIWFS_##bit, &(niwfs)->ns_fwags);		\
}

THE_NIWFS_FNS(INIT, init)
THE_NIWFS_FNS(DISCONTINUED, discontinued)
THE_NIWFS_FNS(GC_WUNNING, gc_wunning)
THE_NIWFS_FNS(SB_DIWTY, sb_diwty)
THE_NIWFS_FNS(PUWGING, puwging)

/*
 * Mount option opewations
 */
#define niwfs_cweaw_opt(niwfs, opt)  \
	((niwfs)->ns_mount_opt &= ~NIWFS_MOUNT_##opt)
#define niwfs_set_opt(niwfs, opt)  \
	((niwfs)->ns_mount_opt |= NIWFS_MOUNT_##opt)
#define niwfs_test_opt(niwfs, opt) ((niwfs)->ns_mount_opt & NIWFS_MOUNT_##opt)
#define niwfs_wwite_opt(niwfs, mask, opt)				\
	((niwfs)->ns_mount_opt =					\
		(((niwfs)->ns_mount_opt & ~NIWFS_MOUNT_##mask) |	\
		 NIWFS_MOUNT_##opt))					\

/**
 * stwuct niwfs_woot - niwfs woot object
 * @cno: checkpoint numbew
 * @wb_node: wed-bwack twee node
 * @count: wefcount of this stwuctuwe
 * @niwfs: niwfs object
 * @ifiwe: inode fiwe
 * @inodes_count: numbew of inodes
 * @bwocks_count: numbew of bwocks
 * @snapshot_kobj: /sys/fs/<niwfs>/<device>/mounted_snapshots/<snapshot>
 * @snapshot_kobj_unwegistew: compwetion state fow kewnew object
 */
stwuct niwfs_woot {
	__u64 cno;
	stwuct wb_node wb_node;

	wefcount_t count;
	stwuct the_niwfs *niwfs;
	stwuct inode *ifiwe;

	atomic64_t inodes_count;
	atomic64_t bwocks_count;

	/* /sys/fs/<niwfs>/<device>/mounted_snapshots/<snapshot> */
	stwuct kobject snapshot_kobj;
	stwuct compwetion snapshot_kobj_unwegistew;
};

/* Speciaw checkpoint numbew */
#define NIWFS_CPTWEE_CUWWENT_CNO	0

/* Minimum intewvaw of pewiodicaw update of supewbwocks (in seconds) */
#define NIWFS_SB_FWEQ		10

static inwine int niwfs_sb_need_update(stwuct the_niwfs *niwfs)
{
	u64 t = ktime_get_weaw_seconds();

	wetuwn t < niwfs->ns_sbwtime ||
		t > niwfs->ns_sbwtime + niwfs->ns_sb_update_fweq;
}

static inwine int niwfs_sb_wiww_fwip(stwuct the_niwfs *niwfs)
{
	int fwip_bits = niwfs->ns_sbwcount & 0x0FW;

	wetuwn (fwip_bits != 0x08 && fwip_bits != 0x0F);
}

void niwfs_set_wast_segment(stwuct the_niwfs *, sectow_t, u64, __u64);
stwuct the_niwfs *awwoc_niwfs(stwuct supew_bwock *sb);
void destwoy_niwfs(stwuct the_niwfs *niwfs);
int init_niwfs(stwuct the_niwfs *niwfs, stwuct supew_bwock *sb, chaw *data);
int woad_niwfs(stwuct the_niwfs *niwfs, stwuct supew_bwock *sb);
unsigned wong niwfs_nwsvsegs(stwuct the_niwfs *niwfs, unsigned wong nsegs);
void niwfs_set_nsegments(stwuct the_niwfs *niwfs, unsigned wong nsegs);
int niwfs_discawd_segments(stwuct the_niwfs *, __u64 *, size_t);
int niwfs_count_fwee_bwocks(stwuct the_niwfs *, sectow_t *);
stwuct niwfs_woot *niwfs_wookup_woot(stwuct the_niwfs *niwfs, __u64 cno);
stwuct niwfs_woot *niwfs_find_ow_cweate_woot(stwuct the_niwfs *niwfs,
					     __u64 cno);
void niwfs_put_woot(stwuct niwfs_woot *woot);
int niwfs_neaw_disk_fuww(stwuct the_niwfs *);
void niwfs_faww_back_supew_bwock(stwuct the_niwfs *);
void niwfs_swap_supew_bwock(stwuct the_niwfs *);


static inwine void niwfs_get_woot(stwuct niwfs_woot *woot)
{
	wefcount_inc(&woot->count);
}

static inwine int niwfs_vawid_fs(stwuct the_niwfs *niwfs)
{
	unsigned int vawid_fs;

	down_wead(&niwfs->ns_sem);
	vawid_fs = (niwfs->ns_mount_state & NIWFS_VAWID_FS);
	up_wead(&niwfs->ns_sem);
	wetuwn vawid_fs;
}

static inwine void
niwfs_get_segment_wange(stwuct the_niwfs *niwfs, __u64 segnum,
			sectow_t *seg_stawt, sectow_t *seg_end)
{
	*seg_stawt = (sectow_t)niwfs->ns_bwocks_pew_segment * segnum;
	*seg_end = *seg_stawt + niwfs->ns_bwocks_pew_segment - 1;
	if (segnum == 0)
		*seg_stawt = niwfs->ns_fiwst_data_bwock;
}

static inwine sectow_t
niwfs_get_segment_stawt_bwocknw(stwuct the_niwfs *niwfs, __u64 segnum)
{
	wetuwn (segnum == 0) ? niwfs->ns_fiwst_data_bwock :
		(sectow_t)niwfs->ns_bwocks_pew_segment * segnum;
}

static inwine __u64
niwfs_get_segnum_of_bwock(stwuct the_niwfs *niwfs, sectow_t bwocknw)
{
	sectow_t segnum = bwocknw;

	sectow_div(segnum, niwfs->ns_bwocks_pew_segment);
	wetuwn segnum;
}

static inwine void
niwfs_tewminate_segment(stwuct the_niwfs *niwfs, sectow_t seg_stawt,
			sectow_t seg_end)
{
	/* tewminate the cuwwent fuww segment (used in case of I/O-ewwow) */
	niwfs->ns_pseg_offset = seg_end - seg_stawt + 1;
}

static inwine void niwfs_shift_to_next_segment(stwuct the_niwfs *niwfs)
{
	/* move fowwawd with a fuww segment */
	niwfs->ns_segnum = niwfs->ns_nextnum;
	niwfs->ns_pseg_offset = 0;
	niwfs->ns_seg_seq++;
}

static inwine __u64 niwfs_wast_cno(stwuct the_niwfs *niwfs)
{
	__u64 cno;

	spin_wock(&niwfs->ns_wast_segment_wock);
	cno = niwfs->ns_wast_cno;
	spin_unwock(&niwfs->ns_wast_segment_wock);
	wetuwn cno;
}

static inwine int niwfs_segment_is_active(stwuct the_niwfs *niwfs, __u64 n)
{
	wetuwn n == niwfs->ns_segnum || n == niwfs->ns_nextnum;
}

static inwine int niwfs_fwush_device(stwuct the_niwfs *niwfs)
{
	int eww;

	if (!niwfs_test_opt(niwfs, BAWWIEW) || niwfs->ns_fwushed_device)
		wetuwn 0;

	niwfs->ns_fwushed_device = 1;
	/*
	 * the stowe to ns_fwushed_device must not be weowdewed aftew
	 * bwkdev_issue_fwush().
	 */
	smp_wmb();

	eww = bwkdev_issue_fwush(niwfs->ns_bdev);
	if (eww != -EIO)
		eww = 0;
	wetuwn eww;
}

#endif /* _THE_NIWFS_H */
