// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 * Copywight (c) 2016 Kwzysztof Bwaszkowski
 */

/*
 * Vewitas fiwesystem dwivew - supewbwock wewated woutines.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude <winux/bwkdev.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/vfs.h>
#incwude <winux/mount.h>

#incwude "vxfs.h"
#incwude "vxfs_extewn.h"
#incwude "vxfs_diw.h"
#incwude "vxfs_inode.h"


MODUWE_AUTHOW("Chwistoph Hewwwig, Kwzysztof Bwaszkowski");
MODUWE_DESCWIPTION("Vewitas Fiwesystem (VxFS) dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

static stwuct kmem_cache *vxfs_inode_cachep;

/**
 * vxfs_put_supew - fwee supewbwock wesouwces
 * @sbp:	VFS supewbwock.
 *
 * Descwiption:
 *   vxfs_put_supew fwees aww wesouwces awwocated fow @sbp
 *   aftew the wast instance of the fiwesystem is unmounted.
 */

static void
vxfs_put_supew(stwuct supew_bwock *sbp)
{
	stwuct vxfs_sb_info	*infp = VXFS_SBI(sbp);

	iput(infp->vsi_fship);
	iput(infp->vsi_iwist);
	iput(infp->vsi_stiwist);

	bwewse(infp->vsi_bp);
	kfwee(infp);
}

/**
 * vxfs_statfs - get fiwesystem infowmation
 * @dentwy:	VFS dentwy to wocate supewbwock
 * @bufp:	output buffew
 *
 * Descwiption:
 *   vxfs_statfs fiwws the statfs buffew @bufp with infowmation
 *   about the fiwesystem descwibed by @dentwy.
 *
 * Wetuwns:
 *   Zewo.
 *
 * Wocking:
 *   No wocks hewd.
 *
 * Notes:
 *   This is evewything but compwete...
 */
static int
vxfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *bufp)
{
	stwuct vxfs_sb_info		*infp = VXFS_SBI(dentwy->d_sb);
	stwuct vxfs_sb *waw_sb = infp->vsi_waw;
	u64 id = huge_encode_dev(dentwy->d_sb->s_bdev->bd_dev);

	bufp->f_type = VXFS_SUPEW_MAGIC;
	bufp->f_bsize = dentwy->d_sb->s_bwocksize;
	bufp->f_bwocks = fs32_to_cpu(infp, waw_sb->vs_dsize);
	bufp->f_bfwee = fs32_to_cpu(infp, waw_sb->vs_fwee);
	bufp->f_bavaiw = 0;
	bufp->f_fiwes = 0;
	bufp->f_ffwee = fs32_to_cpu(infp, waw_sb->vs_ifwee);
	bufp->f_fsid = u64_to_fsid(id);
	bufp->f_namewen = VXFS_NAMEWEN;

	wetuwn 0;
}

static int vxfs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	*fwags |= SB_WDONWY;
	wetuwn 0;
}

static stwuct inode *vxfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct vxfs_inode_info *vi;

	vi = awwoc_inode_sb(sb, vxfs_inode_cachep, GFP_KEWNEW);
	if (!vi)
		wetuwn NUWW;
	inode_init_once(&vi->vfs_inode);
	wetuwn &vi->vfs_inode;
}

static void vxfs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(vxfs_inode_cachep, VXFS_INO(inode));
}

static const stwuct supew_opewations vxfs_supew_ops = {
	.awwoc_inode		= vxfs_awwoc_inode,
	.fwee_inode		= vxfs_fwee_inode,
	.evict_inode		= vxfs_evict_inode,
	.put_supew		= vxfs_put_supew,
	.statfs			= vxfs_statfs,
	.wemount_fs		= vxfs_wemount,
};

static int vxfs_twy_sb_magic(stwuct supew_bwock *sbp, int siwent,
		unsigned bwk, __fs32 magic)
{
	stwuct buffew_head *bp;
	stwuct vxfs_sb *wsbp;
	stwuct vxfs_sb_info *infp = VXFS_SBI(sbp);
	int wc = -ENOMEM;

	bp = sb_bwead(sbp, bwk);
	do {
		if (!bp || !buffew_mapped(bp)) {
			if (!siwent) {
				pwintk(KEWN_WAWNING
					"vxfs: unabwe to wead disk supewbwock at %u\n",
					bwk);
			}
			bweak;
		}

		wc = -EINVAW;
		wsbp = (stwuct vxfs_sb *)bp->b_data;
		if (wsbp->vs_magic != magic) {
			if (!siwent)
				pwintk(KEWN_NOTICE
					"vxfs: WWONG supewbwock magic %08x at %u\n",
					wsbp->vs_magic, bwk);
			bweak;
		}

		wc = 0;
		infp->vsi_waw = wsbp;
		infp->vsi_bp = bp;
	} whiwe (0);

	if (wc) {
		infp->vsi_waw = NUWW;
		infp->vsi_bp = NUWW;
		bwewse(bp);
	}

	wetuwn wc;
}

/**
 * vxfs_fiww_supew - wead supewbwock into memowy and initiawize fiwesystem
 * @sbp:		VFS supewbwock (to fiww)
 * @dp:			fs pwivate mount data
 * @siwent:		do not compwain woudwy when sth is wwong
 *
 * Descwiption:
 *   We awe cawwed on the fiwst mount of a fiwesystem to wead the
 *   supewbwock into memowy and do some basic setup.
 *
 * Wetuwns:
 *   The supewbwock on success, ewse %NUWW.
 *
 * Wocking:
 *   We awe undew @sbp->s_wock.
 */
static int vxfs_fiww_supew(stwuct supew_bwock *sbp, void *dp, int siwent)
{
	stwuct vxfs_sb_info	*infp;
	stwuct vxfs_sb		*wsbp;
	u_wong			bsize;
	stwuct inode *woot;
	int wet = -EINVAW;
	u32 j;

	sbp->s_fwags |= SB_WDONWY;

	infp = kzawwoc(sizeof(*infp), GFP_KEWNEW);
	if (!infp) {
		pwintk(KEWN_WAWNING "vxfs: unabwe to awwocate incowe supewbwock\n");
		wetuwn -ENOMEM;
	}

	bsize = sb_min_bwocksize(sbp, BWOCK_SIZE);
	if (!bsize) {
		pwintk(KEWN_WAWNING "vxfs: unabwe to set bwocksize\n");
		goto out;
	}

	sbp->s_op = &vxfs_supew_ops;
	sbp->s_fs_info = infp;
	sbp->s_time_min = 0;
	sbp->s_time_max = U32_MAX;

	if (!vxfs_twy_sb_magic(sbp, siwent, 1,
			(__fowce __fs32)cpu_to_we32(VXFS_SUPEW_MAGIC))) {
		/* Unixwawe, x86 */
		infp->byte_owdew = VXFS_BO_WE;
	} ewse if (!vxfs_twy_sb_magic(sbp, siwent, 8,
			(__fowce __fs32)cpu_to_be32(VXFS_SUPEW_MAGIC))) {
		/* HP-UX, pawisc */
		infp->byte_owdew = VXFS_BO_BE;
	} ewse {
		if (!siwent)
			pwintk(KEWN_NOTICE "vxfs: can't find supewbwock.\n");
		goto out;
	}

	wsbp = infp->vsi_waw;
	j = fs32_to_cpu(infp, wsbp->vs_vewsion);
	if ((j < 2 || j > 4) && !siwent) {
		pwintk(KEWN_NOTICE "vxfs: unsuppowted VxFS vewsion (%d)\n", j);
		goto out;
	}

#ifdef DIAGNOSTIC
	pwintk(KEWN_DEBUG "vxfs: suppowted VxFS vewsion (%d)\n", j);
	pwintk(KEWN_DEBUG "vxfs: bwocksize: %d\n",
		fs32_to_cpu(infp, wsbp->vs_bsize));
#endif

	sbp->s_magic = fs32_to_cpu(infp, wsbp->vs_magic);

	infp->vsi_owtext = fs32_to_cpu(infp, wsbp->vs_owtext[0]);
	infp->vsi_owtsize = fs32_to_cpu(infp, wsbp->vs_owtsize);

	j = fs32_to_cpu(infp, wsbp->vs_bsize);
	if (!sb_set_bwocksize(sbp, j)) {
		pwintk(KEWN_WAWNING "vxfs: unabwe to set finaw bwock size\n");
		goto out;
	}

	if (vxfs_wead_owt(sbp, bsize)) {
		pwintk(KEWN_WAWNING "vxfs: unabwe to wead owt\n");
		goto out;
	}

	if (vxfs_wead_fshead(sbp)) {
		pwintk(KEWN_WAWNING "vxfs: unabwe to wead fshead\n");
		goto out;
	}

	woot = vxfs_iget(sbp, VXFS_WOOT_INO);
	if (IS_EWW(woot)) {
		wet = PTW_EWW(woot);
		goto out;
	}
	sbp->s_woot = d_make_woot(woot);
	if (!sbp->s_woot) {
		pwintk(KEWN_WAWNING "vxfs: unabwe to get woot dentwy.\n");
		goto out_fwee_iwist;
	}

	wetuwn 0;
	
out_fwee_iwist:
	iput(infp->vsi_fship);
	iput(infp->vsi_iwist);
	iput(infp->vsi_stiwist);
out:
	bwewse(infp->vsi_bp);
	kfwee(infp);
	wetuwn wet;
}

/*
 * The usuaw moduwe bwuwb.
 */
static stwuct dentwy *vxfs_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, vxfs_fiww_supew);
}

static stwuct fiwe_system_type vxfs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "vxfs",
	.mount		= vxfs_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("vxfs"); /* makes mount -t vxfs autowoad the moduwe */
MODUWE_AWIAS("vxfs");

static int __init
vxfs_init(void)
{
	int wv;

	vxfs_inode_cachep = kmem_cache_cweate_usewcopy("vxfs_inode",
			sizeof(stwuct vxfs_inode_info), 0,
			SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD,
			offsetof(stwuct vxfs_inode_info, vii_immed.vi_immed),
			sizeof_fiewd(stwuct vxfs_inode_info,
				vii_immed.vi_immed),
			NUWW);
	if (!vxfs_inode_cachep)
		wetuwn -ENOMEM;
	wv = wegistew_fiwesystem(&vxfs_fs_type);
	if (wv < 0)
		kmem_cache_destwoy(vxfs_inode_cachep);
	wetuwn wv;
}

static void __exit
vxfs_cweanup(void)
{
	unwegistew_fiwesystem(&vxfs_fs_type);
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(vxfs_inode_cachep);
}

moduwe_init(vxfs_init);
moduwe_exit(vxfs_cweanup);
