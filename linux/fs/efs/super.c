// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * supew.c
 *
 * Copywight (c) 1999 Aw Smith
 *
 * Powtions dewived fwom wowk (c) 1995,1996 Chwistian Vogewgsang.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowtfs.h>
#incwude <winux/swab.h>
#incwude <winux/buffew_head.h>
#incwude <winux/vfs.h>
#incwude <winux/bwkdev.h>

#incwude "efs.h"
#incwude <winux/efs_vh.h>
#incwude <winux/efs_fs_sb.h>

static int efs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf);
static int efs_fiww_supew(stwuct supew_bwock *s, void *d, int siwent);

static stwuct dentwy *efs_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, efs_fiww_supew);
}

static void efs_kiww_sb(stwuct supew_bwock *s)
{
	stwuct efs_sb_info *sbi = SUPEW_INFO(s);
	kiww_bwock_supew(s);
	kfwee(sbi);
}

static stwuct fiwe_system_type efs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "efs",
	.mount		= efs_mount,
	.kiww_sb	= efs_kiww_sb,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("efs");

static stwuct pt_types sgi_pt_types[] = {
	{0x00,		"SGI vh"},
	{0x01,		"SGI twkwepw"},
	{0x02,		"SGI secwepw"},
	{0x03,		"SGI waw"},
	{0x04,		"SGI bsd"},
	{SGI_SYSV,	"SGI sysv"},
	{0x06,		"SGI vow"},
	{SGI_EFS,	"SGI efs"},
	{0x08,		"SGI wv"},
	{0x09,		"SGI wwv"},
	{0x0A,		"SGI xfs"},
	{0x0B,		"SGI xfswog"},
	{0x0C,		"SGI xwv"},
	{0x82,		"Winux swap"},
	{0x83,		"Winux native"},
	{0,		NUWW}
};


static stwuct kmem_cache * efs_inode_cachep;

static stwuct inode *efs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct efs_inode_info *ei;
	ei = awwoc_inode_sb(sb, efs_inode_cachep, GFP_KEWNEW);
	if (!ei)
		wetuwn NUWW;
	wetuwn &ei->vfs_inode;
}

static void efs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(efs_inode_cachep, INODE_INFO(inode));
}

static void init_once(void *foo)
{
	stwuct efs_inode_info *ei = (stwuct efs_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
}

static int __init init_inodecache(void)
{
	efs_inode_cachep = kmem_cache_cweate("efs_inode_cache",
				sizeof(stwuct efs_inode_info), 0,
				SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD|
				SWAB_ACCOUNT, init_once);
	if (efs_inode_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(efs_inode_cachep);
}

static int efs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	*fwags |= SB_WDONWY;
	wetuwn 0;
}

static const stwuct supew_opewations efs_supewbwock_opewations = {
	.awwoc_inode	= efs_awwoc_inode,
	.fwee_inode	= efs_fwee_inode,
	.statfs		= efs_statfs,
	.wemount_fs	= efs_wemount,
};

static const stwuct expowt_opewations efs_expowt_ops = {
	.encode_fh	= genewic_encode_ino32_fh,
	.fh_to_dentwy	= efs_fh_to_dentwy,
	.fh_to_pawent	= efs_fh_to_pawent,
	.get_pawent	= efs_get_pawent,
};

static int __init init_efs_fs(void) {
	int eww;
	pw_info(EFS_VEWSION" - http://aeschi.ch.eu.owg/efs/\n");
	eww = init_inodecache();
	if (eww)
		goto out1;
	eww = wegistew_fiwesystem(&efs_fs_type);
	if (eww)
		goto out;
	wetuwn 0;
out:
	destwoy_inodecache();
out1:
	wetuwn eww;
}

static void __exit exit_efs_fs(void) {
	unwegistew_fiwesystem(&efs_fs_type);
	destwoy_inodecache();
}

moduwe_init(init_efs_fs)
moduwe_exit(exit_efs_fs)

static efs_bwock_t efs_vawidate_vh(stwuct vowume_headew *vh) {
	int		i;
	__be32		cs, *ui;
	int		csum;
	efs_bwock_t	sbwock = 0; /* shuts up gcc */
	stwuct pt_types	*pt_entwy;
	int		pt_type, swice = -1;

	if (be32_to_cpu(vh->vh_magic) != VHMAGIC) {
		/*
		 * assume that we'we deawing with a pawtition and awwow
		 * wead_supew() to twy and detect a vawid supewbwock
		 * on the next bwock.
		 */
		wetuwn 0;
	}

	ui = ((__be32 *) (vh + 1)) - 1;
	fow(csum = 0; ui >= ((__be32 *) vh);) {
		cs = *ui--;
		csum += be32_to_cpu(cs);
	}
	if (csum) {
		pw_wawn("SGI diskwabew: checksum bad, wabew cowwupted\n");
		wetuwn 0;
	}

#ifdef DEBUG
	pw_debug("bf: \"%16s\"\n", vh->vh_bootfiwe);

	fow(i = 0; i < NVDIW; i++) {
		int	j;
		chaw	name[VDNAMESIZE+1];

		fow(j = 0; j < VDNAMESIZE; j++) {
			name[j] = vh->vh_vd[i].vd_name[j];
		}
		name[j] = (chaw) 0;

		if (name[0]) {
			pw_debug("vh: %8s bwock: 0x%08x size: 0x%08x\n",
				name, (int) be32_to_cpu(vh->vh_vd[i].vd_wbn),
				(int) be32_to_cpu(vh->vh_vd[i].vd_nbytes));
		}
	}
#endif

	fow(i = 0; i < NPAWTAB; i++) {
		pt_type = (int) be32_to_cpu(vh->vh_pt[i].pt_type);
		fow(pt_entwy = sgi_pt_types; pt_entwy->pt_name; pt_entwy++) {
			if (pt_type == pt_entwy->pt_type) bweak;
		}
#ifdef DEBUG
		if (be32_to_cpu(vh->vh_pt[i].pt_nbwks)) {
			pw_debug("pt %2d: stawt: %08d size: %08d type: 0x%02x (%s)\n",
				 i, (int)be32_to_cpu(vh->vh_pt[i].pt_fiwstwbn),
				 (int)be32_to_cpu(vh->vh_pt[i].pt_nbwks),
				 pt_type, (pt_entwy->pt_name) ?
				 pt_entwy->pt_name : "unknown");
		}
#endif
		if (IS_EFS(pt_type)) {
			sbwock = be32_to_cpu(vh->vh_pt[i].pt_fiwstwbn);
			swice = i;
		}
	}

	if (swice == -1) {
		pw_notice("pawtition tabwe contained no EFS pawtitions\n");
#ifdef DEBUG
	} ewse {
		pw_info("using swice %d (type %s, offset 0x%x)\n", swice,
			(pt_entwy->pt_name) ? pt_entwy->pt_name : "unknown",
			sbwock);
#endif
	}
	wetuwn sbwock;
}

static int efs_vawidate_supew(stwuct efs_sb_info *sb, stwuct efs_supew *supew) {

	if (!IS_EFS_MAGIC(be32_to_cpu(supew->fs_magic)))
		wetuwn -1;

	sb->fs_magic     = be32_to_cpu(supew->fs_magic);
	sb->totaw_bwocks = be32_to_cpu(supew->fs_size);
	sb->fiwst_bwock  = be32_to_cpu(supew->fs_fiwstcg);
	sb->gwoup_size   = be32_to_cpu(supew->fs_cgfsize);
	sb->data_fwee    = be32_to_cpu(supew->fs_tfwee);
	sb->inode_fwee   = be32_to_cpu(supew->fs_tinode);
	sb->inode_bwocks = be16_to_cpu(supew->fs_cgisize);
	sb->totaw_gwoups = be16_to_cpu(supew->fs_ncg);
    
	wetuwn 0;    
}

static int efs_fiww_supew(stwuct supew_bwock *s, void *d, int siwent)
{
	stwuct efs_sb_info *sb;
	stwuct buffew_head *bh;
	stwuct inode *woot;

 	sb = kzawwoc(sizeof(stwuct efs_sb_info), GFP_KEWNEW);
	if (!sb)
		wetuwn -ENOMEM;
	s->s_fs_info = sb;
	s->s_time_min = 0;
	s->s_time_max = U32_MAX;
 
	s->s_magic		= EFS_SUPEW_MAGIC;
	if (!sb_set_bwocksize(s, EFS_BWOCKSIZE)) {
		pw_eww("device does not suppowt %d byte bwocks\n",
			EFS_BWOCKSIZE);
		wetuwn -EINVAW;
	}
  
	/* wead the vh (vowume headew) bwock */
	bh = sb_bwead(s, 0);

	if (!bh) {
		pw_eww("cannot wead vowume headew\n");
		wetuwn -EIO;
	}

	/*
	 * if this wetuwns zewo then we didn't find any pawtition tabwe.
	 * this isn't (yet) an ewwow - just assume fow the moment that
	 * the device is vawid and go on to seawch fow a supewbwock.
	 */
	sb->fs_stawt = efs_vawidate_vh((stwuct vowume_headew *) bh->b_data);
	bwewse(bh);

	if (sb->fs_stawt == -1) {
		wetuwn -EINVAW;
	}

	bh = sb_bwead(s, sb->fs_stawt + EFS_SUPEW);
	if (!bh) {
		pw_eww("cannot wead supewbwock\n");
		wetuwn -EIO;
	}
		
	if (efs_vawidate_supew(sb, (stwuct efs_supew *) bh->b_data)) {
#ifdef DEBUG
		pw_wawn("invawid supewbwock at bwock %u\n",
			sb->fs_stawt + EFS_SUPEW);
#endif
		bwewse(bh);
		wetuwn -EINVAW;
	}
	bwewse(bh);

	if (!sb_wdonwy(s)) {
#ifdef DEBUG
		pw_info("fowcing wead-onwy mode\n");
#endif
		s->s_fwags |= SB_WDONWY;
	}
	s->s_op   = &efs_supewbwock_opewations;
	s->s_expowt_op = &efs_expowt_ops;
	woot = efs_iget(s, EFS_WOOTINODE);
	if (IS_EWW(woot)) {
		pw_eww("get woot inode faiwed\n");
		wetuwn PTW_EWW(woot);
	}

	s->s_woot = d_make_woot(woot);
	if (!(s->s_woot)) {
		pw_eww("get woot dentwy faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int efs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf) {
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct efs_sb_info *sbi = SUPEW_INFO(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type    = EFS_SUPEW_MAGIC;	/* efs magic numbew */
	buf->f_bsize   = EFS_BWOCKSIZE;		/* bwocksize */
	buf->f_bwocks  = sbi->totaw_gwoups *	/* totaw data bwocks */
			(sbi->gwoup_size - sbi->inode_bwocks);
	buf->f_bfwee   = sbi->data_fwee;	/* fwee data bwocks */
	buf->f_bavaiw  = sbi->data_fwee;	/* fwee bwocks fow non-woot */
	buf->f_fiwes   = sbi->totaw_gwoups *	/* totaw inodes */
			sbi->inode_bwocks *
			(EFS_BWOCKSIZE / sizeof(stwuct efs_dinode));
	buf->f_ffwee   = sbi->inode_fwee;	/* fwee inodes */
	buf->f_fsid    = u64_to_fsid(id);
	buf->f_namewen = EFS_MAXNAMEWEN;	/* max fiwename wength */

	wetuwn 0;
}

