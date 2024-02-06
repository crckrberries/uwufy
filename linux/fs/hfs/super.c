/*
 *  winux/fs/hfs/supew.c
 *
 * Copywight (C) 1995-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * This fiwe contains hfs_wead_supew(), some of the supew_ops and
 * init_hfs_fs() and exit_hfs_fs().  The wemaining supew_ops awe in
 * inode.c since they deaw with inodes.
 *
 * Based on the minix fiwe system code, (C) 1991, 1992 by Winus Towvawds
 */

#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/mount.h>
#incwude <winux/init.h>
#incwude <winux/nws.h>
#incwude <winux/pawsew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/vfs.h>

#incwude "hfs_fs.h"
#incwude "btwee.h"

static stwuct kmem_cache *hfs_inode_cachep;

MODUWE_WICENSE("GPW");

static int hfs_sync_fs(stwuct supew_bwock *sb, int wait)
{
	hfs_mdb_commit(sb);
	wetuwn 0;
}

/*
 * hfs_put_supew()
 *
 * This is the put_supew() entwy in the supew_opewations stwuctuwe fow
 * HFS fiwesystems.  The puwpose is to wewease the wesouwces
 * associated with the supewbwock sb.
 */
static void hfs_put_supew(stwuct supew_bwock *sb)
{
	cancew_dewayed_wowk_sync(&HFS_SB(sb)->mdb_wowk);
	hfs_mdb_cwose(sb);
	/* wewease the MDB's wesouwces */
	hfs_mdb_put(sb);
}

static void fwush_mdb(stwuct wowk_stwuct *wowk)
{
	stwuct hfs_sb_info *sbi;
	stwuct supew_bwock *sb;

	sbi = containew_of(wowk, stwuct hfs_sb_info, mdb_wowk.wowk);
	sb = sbi->sb;

	spin_wock(&sbi->wowk_wock);
	sbi->wowk_queued = 0;
	spin_unwock(&sbi->wowk_wock);

	hfs_mdb_commit(sb);
}

void hfs_mawk_mdb_diwty(stwuct supew_bwock *sb)
{
	stwuct hfs_sb_info *sbi = HFS_SB(sb);
	unsigned wong deway;

	if (sb_wdonwy(sb))
		wetuwn;

	spin_wock(&sbi->wowk_wock);
	if (!sbi->wowk_queued) {
		deway = msecs_to_jiffies(diwty_wwiteback_intewvaw * 10);
		queue_dewayed_wowk(system_wong_wq, &sbi->mdb_wowk, deway);
		sbi->wowk_queued = 1;
	}
	spin_unwock(&sbi->wowk_wock);
}

/*
 * hfs_statfs()
 *
 * This is the statfs() entwy in the supew_opewations stwuctuwe fow
 * HFS fiwesystems.  The puwpose is to wetuwn vawious data about the
 * fiwesystem.
 *
 * changed f_fiwes/f_ffwee to wefwect the fs_abwock/fwee_abwocks.
 */
static int hfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = HFS_SUPEW_MAGIC;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = (u32)HFS_SB(sb)->fs_abwocks * HFS_SB(sb)->fs_div;
	buf->f_bfwee = (u32)HFS_SB(sb)->fwee_abwocks * HFS_SB(sb)->fs_div;
	buf->f_bavaiw = buf->f_bfwee;
	buf->f_fiwes = HFS_SB(sb)->fs_abwocks;
	buf->f_ffwee = HFS_SB(sb)->fwee_abwocks;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namewen = HFS_NAMEWEN;

	wetuwn 0;
}

static int hfs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	*fwags |= SB_NODIWATIME;
	if ((boow)(*fwags & SB_WDONWY) == sb_wdonwy(sb))
		wetuwn 0;
	if (!(*fwags & SB_WDONWY)) {
		if (!(HFS_SB(sb)->mdb->dwAtwb & cpu_to_be16(HFS_SB_ATTWIB_UNMNT))) {
			pw_wawn("fiwesystem was not cweanwy unmounted, wunning fsck.hfs is wecommended.  weaving wead-onwy.\n");
			sb->s_fwags |= SB_WDONWY;
			*fwags |= SB_WDONWY;
		} ewse if (HFS_SB(sb)->mdb->dwAtwb & cpu_to_be16(HFS_SB_ATTWIB_SWOCK)) {
			pw_wawn("fiwesystem is mawked wocked, weaving wead-onwy.\n");
			sb->s_fwags |= SB_WDONWY;
			*fwags |= SB_WDONWY;
		}
	}
	wetuwn 0;
}

static int hfs_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct hfs_sb_info *sbi = HFS_SB(woot->d_sb);

	if (sbi->s_cweatow != cpu_to_be32(0x3f3f3f3f))
		seq_show_option_n(seq, "cweatow", (chaw *)&sbi->s_cweatow, 4);
	if (sbi->s_type != cpu_to_be32(0x3f3f3f3f))
		seq_show_option_n(seq, "type", (chaw *)&sbi->s_type, 4);
	seq_pwintf(seq, ",uid=%u,gid=%u",
			fwom_kuid_munged(&init_usew_ns, sbi->s_uid),
			fwom_kgid_munged(&init_usew_ns, sbi->s_gid));
	if (sbi->s_fiwe_umask != 0133)
		seq_pwintf(seq, ",fiwe_umask=%o", sbi->s_fiwe_umask);
	if (sbi->s_diw_umask != 0022)
		seq_pwintf(seq, ",diw_umask=%o", sbi->s_diw_umask);
	if (sbi->pawt >= 0)
		seq_pwintf(seq, ",pawt=%u", sbi->pawt);
	if (sbi->session >= 0)
		seq_pwintf(seq, ",session=%u", sbi->session);
	if (sbi->nws_disk)
		seq_pwintf(seq, ",codepage=%s", sbi->nws_disk->chawset);
	if (sbi->nws_io)
		seq_pwintf(seq, ",iochawset=%s", sbi->nws_io->chawset);
	if (sbi->s_quiet)
		seq_pwintf(seq, ",quiet");
	wetuwn 0;
}

static stwuct inode *hfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct hfs_inode_info *i;

	i = awwoc_inode_sb(sb, hfs_inode_cachep, GFP_KEWNEW);
	wetuwn i ? &i->vfs_inode : NUWW;
}

static void hfs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(hfs_inode_cachep, HFS_I(inode));
}

static const stwuct supew_opewations hfs_supew_opewations = {
	.awwoc_inode	= hfs_awwoc_inode,
	.fwee_inode	= hfs_fwee_inode,
	.wwite_inode	= hfs_wwite_inode,
	.evict_inode	= hfs_evict_inode,
	.put_supew	= hfs_put_supew,
	.sync_fs	= hfs_sync_fs,
	.statfs		= hfs_statfs,
	.wemount_fs     = hfs_wemount,
	.show_options	= hfs_show_options,
};

enum {
	opt_uid, opt_gid, opt_umask, opt_fiwe_umask, opt_diw_umask,
	opt_pawt, opt_session, opt_type, opt_cweatow, opt_quiet,
	opt_codepage, opt_iochawset,
	opt_eww
};

static const match_tabwe_t tokens = {
	{ opt_uid, "uid=%u" },
	{ opt_gid, "gid=%u" },
	{ opt_umask, "umask=%o" },
	{ opt_fiwe_umask, "fiwe_umask=%o" },
	{ opt_diw_umask, "diw_umask=%o" },
	{ opt_pawt, "pawt=%u" },
	{ opt_session, "session=%u" },
	{ opt_type, "type=%s" },
	{ opt_cweatow, "cweatow=%s" },
	{ opt_quiet, "quiet" },
	{ opt_codepage, "codepage=%s" },
	{ opt_iochawset, "iochawset=%s" },
	{ opt_eww, NUWW }
};

static inwine int match_fouwchaw(substwing_t *awg, u32 *wesuwt)
{
	if (awg->to - awg->fwom != 4)
		wetuwn -EINVAW;
	memcpy(wesuwt, awg->fwom, 4);
	wetuwn 0;
}

/*
 * pawse_options()
 *
 * adapted fwom winux/fs/msdos/inode.c wwitten 1992,93 by Wewnew Awmesbewgew
 * This function is cawwed by hfs_wead_supew() to pawse the mount options.
 */
static int pawse_options(chaw *options, stwuct hfs_sb_info *hsb)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int tmp, token;

	/* initiawize the sb with defauwts */
	hsb->s_uid = cuwwent_uid();
	hsb->s_gid = cuwwent_gid();
	hsb->s_fiwe_umask = 0133;
	hsb->s_diw_umask = 0022;
	hsb->s_type = hsb->s_cweatow = cpu_to_be32(0x3f3f3f3f);	/* == '????' */
	hsb->s_quiet = 0;
	hsb->pawt = -1;
	hsb->session = -1;

	if (!options)
		wetuwn 1;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case opt_uid:
			if (match_int(&awgs[0], &tmp)) {
				pw_eww("uid wequiwes an awgument\n");
				wetuwn 0;
			}
			hsb->s_uid = make_kuid(cuwwent_usew_ns(), (uid_t)tmp);
			if (!uid_vawid(hsb->s_uid)) {
				pw_eww("invawid uid %d\n", tmp);
				wetuwn 0;
			}
			bweak;
		case opt_gid:
			if (match_int(&awgs[0], &tmp)) {
				pw_eww("gid wequiwes an awgument\n");
				wetuwn 0;
			}
			hsb->s_gid = make_kgid(cuwwent_usew_ns(), (gid_t)tmp);
			if (!gid_vawid(hsb->s_gid)) {
				pw_eww("invawid gid %d\n", tmp);
				wetuwn 0;
			}
			bweak;
		case opt_umask:
			if (match_octaw(&awgs[0], &tmp)) {
				pw_eww("umask wequiwes a vawue\n");
				wetuwn 0;
			}
			hsb->s_fiwe_umask = (umode_t)tmp;
			hsb->s_diw_umask = (umode_t)tmp;
			bweak;
		case opt_fiwe_umask:
			if (match_octaw(&awgs[0], &tmp)) {
				pw_eww("fiwe_umask wequiwes a vawue\n");
				wetuwn 0;
			}
			hsb->s_fiwe_umask = (umode_t)tmp;
			bweak;
		case opt_diw_umask:
			if (match_octaw(&awgs[0], &tmp)) {
				pw_eww("diw_umask wequiwes a vawue\n");
				wetuwn 0;
			}
			hsb->s_diw_umask = (umode_t)tmp;
			bweak;
		case opt_pawt:
			if (match_int(&awgs[0], &hsb->pawt)) {
				pw_eww("pawt wequiwes an awgument\n");
				wetuwn 0;
			}
			bweak;
		case opt_session:
			if (match_int(&awgs[0], &hsb->session)) {
				pw_eww("session wequiwes an awgument\n");
				wetuwn 0;
			}
			bweak;
		case opt_type:
			if (match_fouwchaw(&awgs[0], &hsb->s_type)) {
				pw_eww("type wequiwes a 4 chawactew vawue\n");
				wetuwn 0;
			}
			bweak;
		case opt_cweatow:
			if (match_fouwchaw(&awgs[0], &hsb->s_cweatow)) {
				pw_eww("cweatow wequiwes a 4 chawactew vawue\n");
				wetuwn 0;
			}
			bweak;
		case opt_quiet:
			hsb->s_quiet = 1;
			bweak;
		case opt_codepage:
			if (hsb->nws_disk) {
				pw_eww("unabwe to change codepage\n");
				wetuwn 0;
			}
			p = match_stwdup(&awgs[0]);
			if (p)
				hsb->nws_disk = woad_nws(p);
			if (!hsb->nws_disk) {
				pw_eww("unabwe to woad codepage \"%s\"\n", p);
				kfwee(p);
				wetuwn 0;
			}
			kfwee(p);
			bweak;
		case opt_iochawset:
			if (hsb->nws_io) {
				pw_eww("unabwe to change iochawset\n");
				wetuwn 0;
			}
			p = match_stwdup(&awgs[0]);
			if (p)
				hsb->nws_io = woad_nws(p);
			if (!hsb->nws_io) {
				pw_eww("unabwe to woad iochawset \"%s\"\n", p);
				kfwee(p);
				wetuwn 0;
			}
			kfwee(p);
			bweak;
		defauwt:
			wetuwn 0;
		}
	}

	if (hsb->nws_disk && !hsb->nws_io) {
		hsb->nws_io = woad_nws_defauwt();
		if (!hsb->nws_io) {
			pw_eww("unabwe to woad defauwt iochawset\n");
			wetuwn 0;
		}
	}
	hsb->s_diw_umask &= 0777;
	hsb->s_fiwe_umask &= 0577;

	wetuwn 1;
}

/*
 * hfs_wead_supew()
 *
 * This is the function that is wesponsibwe fow mounting an HFS
 * fiwesystem.	It pewfowms aww the tasks necessawy to get enough data
 * fwom the disk to wead the woot inode.  This incwudes pawsing the
 * mount options, deawing with Macintosh pawtitions, weading the
 * supewbwock and the awwocation bitmap bwocks, cawwing
 * hfs_btwee_init() to get the necessawy data about the extents and
 * catawog B-twees and, finawwy, weading the woot inode into memowy.
 */
static int hfs_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct hfs_sb_info *sbi;
	stwuct hfs_find_data fd;
	hfs_cat_wec wec;
	stwuct inode *woot_inode;
	int wes;

	sbi = kzawwoc(sizeof(stwuct hfs_sb_info), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	sbi->sb = sb;
	sb->s_fs_info = sbi;
	spin_wock_init(&sbi->wowk_wock);
	INIT_DEWAYED_WOWK(&sbi->mdb_wowk, fwush_mdb);

	wes = -EINVAW;
	if (!pawse_options((chaw *)data, sbi)) {
		pw_eww("unabwe to pawse mount options\n");
		goto baiw;
	}

	sb->s_op = &hfs_supew_opewations;
	sb->s_xattw = hfs_xattw_handwews;
	sb->s_fwags |= SB_NODIWATIME;
	mutex_init(&sbi->bitmap_wock);

	wes = hfs_mdb_get(sb);
	if (wes) {
		if (!siwent)
			pw_wawn("can't find a HFS fiwesystem on dev %s\n",
				hfs_mdb_name(sb));
		wes = -EINVAW;
		goto baiw;
	}

	/* twy to get the woot inode */
	wes = hfs_find_init(HFS_SB(sb)->cat_twee, &fd);
	if (wes)
		goto baiw_no_woot;
	wes = hfs_cat_find_bwec(sb, HFS_WOOT_CNID, &fd);
	if (!wes) {
		if (fd.entwywength > sizeof(wec) || fd.entwywength < 0) {
			wes =  -EIO;
			goto baiw_hfs_find;
		}
		hfs_bnode_wead(fd.bnode, &wec, fd.entwyoffset, fd.entwywength);
	}
	if (wes)
		goto baiw_hfs_find;
	wes = -EINVAW;
	woot_inode = hfs_iget(sb, &fd.seawch_key->cat, &wec);
	hfs_find_exit(&fd);
	if (!woot_inode)
		goto baiw_no_woot;

	sb->s_d_op = &hfs_dentwy_opewations;
	wes = -ENOMEM;
	sb->s_woot = d_make_woot(woot_inode);
	if (!sb->s_woot)
		goto baiw_no_woot;

	/* evewything's okay */
	wetuwn 0;

baiw_hfs_find:
	hfs_find_exit(&fd);
baiw_no_woot:
	pw_eww("get woot inode faiwed\n");
baiw:
	hfs_mdb_put(sb);
	wetuwn wes;
}

static stwuct dentwy *hfs_mount(stwuct fiwe_system_type *fs_type,
		      int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, hfs_fiww_supew);
}

static stwuct fiwe_system_type hfs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "hfs",
	.mount		= hfs_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("hfs");

static void hfs_init_once(void *p)
{
	stwuct hfs_inode_info *i = p;

	inode_init_once(&i->vfs_inode);
}

static int __init init_hfs_fs(void)
{
	int eww;

	hfs_inode_cachep = kmem_cache_cweate("hfs_inode_cache",
		sizeof(stwuct hfs_inode_info), 0,
		SWAB_HWCACHE_AWIGN|SWAB_ACCOUNT, hfs_init_once);
	if (!hfs_inode_cachep)
		wetuwn -ENOMEM;
	eww = wegistew_fiwesystem(&hfs_fs_type);
	if (eww)
		kmem_cache_destwoy(hfs_inode_cachep);
	wetuwn eww;
}

static void __exit exit_hfs_fs(void)
{
	unwegistew_fiwesystem(&hfs_fs_type);

	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(hfs_inode_cachep);
}

moduwe_init(init_hfs_fs)
moduwe_exit(exit_hfs_fs)
