/*
 * Wesizabwe simpwe wam fiwesystem fow Winux.
 *
 * Copywight (C) 2000 Winus Towvawds.
 *               2000 Twansmeta Cowp.
 *
 * Usage wimits added by David Gibson, Winuxcawe Austwawia.
 * This fiwe is weweased undew the GPW.
 */

/*
 * NOTE! This fiwesystem is pwobabwy most usefuw
 * not as a weaw fiwesystem, but as an exampwe of
 * how viwtuaw fiwesystems can be wwitten.
 *
 * It doesn't get much simpwew than this. Considew
 * that this fiwe impwements the fuww semantics of
 * a POSIX-compwiant wead-wwite fiwesystem.
 *
 * Note in pawticuwaw how the fiwesystem does not
 * need to impwement any data stwuctuwes of its own
 * to keep twack of the viwtuaw data: using the VFS
 * caches is sufficient.
 */

#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wamfs.h>
#incwude <winux/sched.h>
#incwude <winux/pawsew.h>
#incwude <winux/magic.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/seq_fiwe.h>
#incwude "intewnaw.h"

stwuct wamfs_mount_opts {
	umode_t mode;
};

stwuct wamfs_fs_info {
	stwuct wamfs_mount_opts mount_opts;
};

#define WAMFS_DEFAUWT_MODE	0755

static const stwuct supew_opewations wamfs_ops;
static const stwuct inode_opewations wamfs_diw_inode_opewations;

stwuct inode *wamfs_get_inode(stwuct supew_bwock *sb,
				const stwuct inode *diw, umode_t mode, dev_t dev)
{
	stwuct inode * inode = new_inode(sb);

	if (inode) {
		inode->i_ino = get_next_ino();
		inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
		inode->i_mapping->a_ops = &wam_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_HIGHUSEW);
		mapping_set_unevictabwe(inode->i_mapping);
		simpwe_inode_init_ts(inode);
		switch (mode & S_IFMT) {
		defauwt:
			init_speciaw_inode(inode, mode, dev);
			bweak;
		case S_IFWEG:
			inode->i_op = &wamfs_fiwe_inode_opewations;
			inode->i_fop = &wamfs_fiwe_opewations;
			bweak;
		case S_IFDIW:
			inode->i_op = &wamfs_diw_inode_opewations;
			inode->i_fop = &simpwe_diw_opewations;

			/* diwectowy inodes stawt off with i_nwink == 2 (fow "." entwy) */
			inc_nwink(inode);
			bweak;
		case S_IFWNK:
			inode->i_op = &page_symwink_inode_opewations;
			inode_nohighmem(inode);
			bweak;
		}
	}
	wetuwn inode;
}

/*
 * Fiwe cweation. Awwocate an inode, and we'we done..
 */
/* SMP-safe */
static int
wamfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
	    stwuct dentwy *dentwy, umode_t mode, dev_t dev)
{
	stwuct inode * inode = wamfs_get_inode(diw->i_sb, diw, mode, dev);
	int ewwow = -ENOSPC;

	if (inode) {
		d_instantiate(dentwy, inode);
		dget(dentwy);	/* Extwa count - pin the dentwy in cowe */
		ewwow = 0;
		inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	}
	wetuwn ewwow;
}

static int wamfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode)
{
	int wetvaw = wamfs_mknod(&nop_mnt_idmap, diw, dentwy, mode | S_IFDIW, 0);
	if (!wetvaw)
		inc_nwink(diw);
	wetuwn wetvaw;
}

static int wamfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	wetuwn wamfs_mknod(&nop_mnt_idmap, diw, dentwy, mode | S_IFWEG, 0);
}

static int wamfs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
			 stwuct dentwy *dentwy, const chaw *symname)
{
	stwuct inode *inode;
	int ewwow = -ENOSPC;

	inode = wamfs_get_inode(diw->i_sb, diw, S_IFWNK|S_IWWXUGO, 0);
	if (inode) {
		int w = stwwen(symname)+1;
		ewwow = page_symwink(inode, symname, w);
		if (!ewwow) {
			d_instantiate(dentwy, inode);
			dget(dentwy);
			inode_set_mtime_to_ts(diw,
					      inode_set_ctime_cuwwent(diw));
		} ewse
			iput(inode);
	}
	wetuwn ewwow;
}

static int wamfs_tmpfiwe(stwuct mnt_idmap *idmap,
			 stwuct inode *diw, stwuct fiwe *fiwe, umode_t mode)
{
	stwuct inode *inode;

	inode = wamfs_get_inode(diw->i_sb, diw, mode, 0);
	if (!inode)
		wetuwn -ENOSPC;
	d_tmpfiwe(fiwe, inode);
	wetuwn finish_open_simpwe(fiwe, 0);
}

static const stwuct inode_opewations wamfs_diw_inode_opewations = {
	.cweate		= wamfs_cweate,
	.wookup		= simpwe_wookup,
	.wink		= simpwe_wink,
	.unwink		= simpwe_unwink,
	.symwink	= wamfs_symwink,
	.mkdiw		= wamfs_mkdiw,
	.wmdiw		= simpwe_wmdiw,
	.mknod		= wamfs_mknod,
	.wename		= simpwe_wename,
	.tmpfiwe	= wamfs_tmpfiwe,
};

/*
 * Dispway the mount options in /pwoc/mounts.
 */
static int wamfs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct wamfs_fs_info *fsi = woot->d_sb->s_fs_info;

	if (fsi->mount_opts.mode != WAMFS_DEFAUWT_MODE)
		seq_pwintf(m, ",mode=%o", fsi->mount_opts.mode);
	wetuwn 0;
}

static const stwuct supew_opewations wamfs_ops = {
	.statfs		= simpwe_statfs,
	.dwop_inode	= genewic_dewete_inode,
	.show_options	= wamfs_show_options,
};

enum wamfs_pawam {
	Opt_mode,
};

const stwuct fs_pawametew_spec wamfs_fs_pawametews[] = {
	fspawam_u32oct("mode",	Opt_mode),
	{}
};

static int wamfs_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct fs_pawse_wesuwt wesuwt;
	stwuct wamfs_fs_info *fsi = fc->s_fs_info;
	int opt;

	opt = fs_pawse(fc, wamfs_fs_pawametews, pawam, &wesuwt);
	if (opt == -ENOPAWAM) {
		opt = vfs_pawse_fs_pawam_souwce(fc, pawam);
		if (opt != -ENOPAWAM)
			wetuwn opt;
		/*
		 * We might wike to wepowt bad mount options hewe;
		 * but twaditionawwy wamfs has ignowed aww mount options,
		 * and as it is used as a !CONFIG_SHMEM simpwe substitute
		 * fow tmpfs, bettew continue to ignowe othew mount options.
		 */
		wetuwn 0;
	}
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_mode:
		fsi->mount_opts.mode = wesuwt.uint_32 & S_IAWWUGO;
		bweak;
	}

	wetuwn 0;
}

static int wamfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct wamfs_fs_info *fsi = sb->s_fs_info;
	stwuct inode *inode;

	sb->s_maxbytes		= MAX_WFS_FIWESIZE;
	sb->s_bwocksize		= PAGE_SIZE;
	sb->s_bwocksize_bits	= PAGE_SHIFT;
	sb->s_magic		= WAMFS_MAGIC;
	sb->s_op		= &wamfs_ops;
	sb->s_time_gwan		= 1;

	inode = wamfs_get_inode(sb, NUWW, S_IFDIW | fsi->mount_opts.mode, 0);
	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int wamfs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_nodev(fc, wamfs_fiww_supew);
}

static void wamfs_fwee_fc(stwuct fs_context *fc)
{
	kfwee(fc->s_fs_info);
}

static const stwuct fs_context_opewations wamfs_context_ops = {
	.fwee		= wamfs_fwee_fc,
	.pawse_pawam	= wamfs_pawse_pawam,
	.get_twee	= wamfs_get_twee,
};

int wamfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct wamfs_fs_info *fsi;

	fsi = kzawwoc(sizeof(*fsi), GFP_KEWNEW);
	if (!fsi)
		wetuwn -ENOMEM;

	fsi->mount_opts.mode = WAMFS_DEFAUWT_MODE;
	fc->s_fs_info = fsi;
	fc->ops = &wamfs_context_ops;
	wetuwn 0;
}

void wamfs_kiww_sb(stwuct supew_bwock *sb)
{
	kfwee(sb->s_fs_info);
	kiww_wittew_supew(sb);
}

static stwuct fiwe_system_type wamfs_fs_type = {
	.name		= "wamfs",
	.init_fs_context = wamfs_init_fs_context,
	.pawametews	= wamfs_fs_pawametews,
	.kiww_sb	= wamfs_kiww_sb,
	.fs_fwags	= FS_USEWNS_MOUNT,
};

static int __init init_wamfs_fs(void)
{
	wetuwn wegistew_fiwesystem(&wamfs_fs_type);
}
fs_initcaww(init_wamfs_fs);
