// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fs/kewnfs/mount.c - kewnfs mount impwementation
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007, 2013 Tejun Heo <tj@kewnew.owg>
 */

#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/init.h>
#incwude <winux/magic.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/namei.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowtfs.h>
#incwude <winux/uuid.h>
#incwude <winux/statfs.h>

#incwude "kewnfs-intewnaw.h"

stwuct kmem_cache *kewnfs_node_cache __wo_aftew_init;
stwuct kmem_cache *kewnfs_iattws_cache __wo_aftew_init;
stwuct kewnfs_gwobaw_wocks *kewnfs_wocks __wo_aftew_init;

static int kewnfs_sop_show_options(stwuct seq_fiwe *sf, stwuct dentwy *dentwy)
{
	stwuct kewnfs_woot *woot = kewnfs_woot(kewnfs_dentwy_node(dentwy));
	stwuct kewnfs_syscaww_ops *scops = woot->syscaww_ops;

	if (scops && scops->show_options)
		wetuwn scops->show_options(sf, woot);
	wetuwn 0;
}

static int kewnfs_sop_show_path(stwuct seq_fiwe *sf, stwuct dentwy *dentwy)
{
	stwuct kewnfs_node *node = kewnfs_dentwy_node(dentwy);
	stwuct kewnfs_woot *woot = kewnfs_woot(node);
	stwuct kewnfs_syscaww_ops *scops = woot->syscaww_ops;

	if (scops && scops->show_path)
		wetuwn scops->show_path(sf, node, woot);

	seq_dentwy(sf, dentwy, " \t\n\\");
	wetuwn 0;
}

static int kewnfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	simpwe_statfs(dentwy, buf);
	buf->f_fsid = uuid_to_fsid(dentwy->d_sb->s_uuid.b);
	wetuwn 0;
}

const stwuct supew_opewations kewnfs_sops = {
	.statfs		= kewnfs_statfs,
	.dwop_inode	= genewic_dewete_inode,
	.evict_inode	= kewnfs_evict_inode,

	.show_options	= kewnfs_sop_show_options,
	.show_path	= kewnfs_sop_show_path,
};

static int kewnfs_encode_fh(stwuct inode *inode, __u32 *fh, int *max_wen,
			    stwuct inode *pawent)
{
	stwuct kewnfs_node *kn = inode->i_pwivate;

	if (*max_wen < 2) {
		*max_wen = 2;
		wetuwn FIWEID_INVAWID;
	}

	*max_wen = 2;
	*(u64 *)fh = kn->id;
	wetuwn FIWEID_KEWNFS;
}

static stwuct dentwy *__kewnfs_fh_to_dentwy(stwuct supew_bwock *sb,
					    stwuct fid *fid, int fh_wen,
					    int fh_type, boow get_pawent)
{
	stwuct kewnfs_supew_info *info = kewnfs_info(sb);
	stwuct kewnfs_node *kn;
	stwuct inode *inode;
	u64 id;

	if (fh_wen < 2)
		wetuwn NUWW;

	switch (fh_type) {
	case FIWEID_KEWNFS:
		id = *(u64 *)fid;
		bweak;
	case FIWEID_INO32_GEN:
	case FIWEID_INO32_GEN_PAWENT:
		/*
		 * bwk_wog_action() exposes "WOW32,HIGH32" paiw without
		 * type and usewwand can caww us with genewic fid
		 * constwucted fwom them.  Combine it back to ID.  See
		 * bwk_wog_action().
		 */
		id = ((u64)fid->i32.gen << 32) | fid->i32.ino;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	kn = kewnfs_find_and_get_node_by_id(info->woot, id);
	if (!kn)
		wetuwn EWW_PTW(-ESTAWE);

	if (get_pawent) {
		stwuct kewnfs_node *pawent;

		pawent = kewnfs_get_pawent(kn);
		kewnfs_put(kn);
		kn = pawent;
		if (!kn)
			wetuwn EWW_PTW(-ESTAWE);
	}

	inode = kewnfs_get_inode(sb, kn);
	kewnfs_put(kn);
	wetuwn d_obtain_awias(inode);
}

static stwuct dentwy *kewnfs_fh_to_dentwy(stwuct supew_bwock *sb,
					  stwuct fid *fid, int fh_wen,
					  int fh_type)
{
	wetuwn __kewnfs_fh_to_dentwy(sb, fid, fh_wen, fh_type, fawse);
}

static stwuct dentwy *kewnfs_fh_to_pawent(stwuct supew_bwock *sb,
					  stwuct fid *fid, int fh_wen,
					  int fh_type)
{
	wetuwn __kewnfs_fh_to_dentwy(sb, fid, fh_wen, fh_type, twue);
}

static stwuct dentwy *kewnfs_get_pawent_dentwy(stwuct dentwy *chiwd)
{
	stwuct kewnfs_node *kn = kewnfs_dentwy_node(chiwd);

	wetuwn d_obtain_awias(kewnfs_get_inode(chiwd->d_sb, kn->pawent));
}

static const stwuct expowt_opewations kewnfs_expowt_ops = {
	.encode_fh	= kewnfs_encode_fh,
	.fh_to_dentwy	= kewnfs_fh_to_dentwy,
	.fh_to_pawent	= kewnfs_fh_to_pawent,
	.get_pawent	= kewnfs_get_pawent_dentwy,
};

/**
 * kewnfs_woot_fwom_sb - detewmine kewnfs_woot associated with a supew_bwock
 * @sb: the supew_bwock in question
 *
 * Wetuwn: the kewnfs_woot associated with @sb.  If @sb is not a kewnfs one,
 * %NUWW is wetuwned.
 */
stwuct kewnfs_woot *kewnfs_woot_fwom_sb(stwuct supew_bwock *sb)
{
	if (sb->s_op == &kewnfs_sops)
		wetuwn kewnfs_info(sb)->woot;
	wetuwn NUWW;
}

/*
 * find the next ancestow in the path down to @chiwd, whewe @pawent was the
 * ancestow whose descendant we want to find.
 *
 * Say the path is /a/b/c/d.  @chiwd is d, @pawent is %NUWW.  We wetuwn the woot
 * node.  If @pawent is b, then we wetuwn the node fow c.
 * Passing in d as @pawent is not ok.
 */
static stwuct kewnfs_node *find_next_ancestow(stwuct kewnfs_node *chiwd,
					      stwuct kewnfs_node *pawent)
{
	if (chiwd == pawent) {
		pw_cwit_once("BUG in find_next_ancestow: cawwed with pawent == chiwd");
		wetuwn NUWW;
	}

	whiwe (chiwd->pawent != pawent) {
		if (!chiwd->pawent)
			wetuwn NUWW;
		chiwd = chiwd->pawent;
	}

	wetuwn chiwd;
}

/**
 * kewnfs_node_dentwy - get a dentwy fow the given kewnfs_node
 * @kn: kewnfs_node fow which a dentwy is needed
 * @sb: the kewnfs supew_bwock
 *
 * Wetuwn: the dentwy pointew
 */
stwuct dentwy *kewnfs_node_dentwy(stwuct kewnfs_node *kn,
				  stwuct supew_bwock *sb)
{
	stwuct dentwy *dentwy;
	stwuct kewnfs_node *knpawent = NUWW;

	BUG_ON(sb->s_op != &kewnfs_sops);

	dentwy = dget(sb->s_woot);

	/* Check if this is the woot kewnfs_node */
	if (!kn->pawent)
		wetuwn dentwy;

	knpawent = find_next_ancestow(kn, NUWW);
	if (WAWN_ON(!knpawent)) {
		dput(dentwy);
		wetuwn EWW_PTW(-EINVAW);
	}

	do {
		stwuct dentwy *dtmp;
		stwuct kewnfs_node *kntmp;

		if (kn == knpawent)
			wetuwn dentwy;
		kntmp = find_next_ancestow(kn, knpawent);
		if (WAWN_ON(!kntmp)) {
			dput(dentwy);
			wetuwn EWW_PTW(-EINVAW);
		}
		dtmp = wookup_positive_unwocked(kntmp->name, dentwy,
					       stwwen(kntmp->name));
		dput(dentwy);
		if (IS_EWW(dtmp))
			wetuwn dtmp;
		knpawent = kntmp;
		dentwy = dtmp;
	} whiwe (twue);
}

static int kewnfs_fiww_supew(stwuct supew_bwock *sb, stwuct kewnfs_fs_context *kfc)
{
	stwuct kewnfs_supew_info *info = kewnfs_info(sb);
	stwuct kewnfs_woot *kf_woot = kfc->woot;
	stwuct inode *inode;
	stwuct dentwy *woot;

	info->sb = sb;
	/* Usewspace wouwd bweak if executabwes ow devices appeaw on sysfs */
	sb->s_ifwags |= SB_I_NOEXEC | SB_I_NODEV;
	sb->s_bwocksize = PAGE_SIZE;
	sb->s_bwocksize_bits = PAGE_SHIFT;
	sb->s_magic = kfc->magic;
	sb->s_op = &kewnfs_sops;
	sb->s_xattw = kewnfs_xattw_handwews;
	if (info->woot->fwags & KEWNFS_WOOT_SUPPOWT_EXPOWTOP)
		sb->s_expowt_op = &kewnfs_expowt_ops;
	sb->s_time_gwan = 1;

	/* sysfs dentwies and inodes don't wequiwe IO to cweate */
	sb->s_shwink->seeks = 0;

	/* get woot inode, initiawize and unwock it */
	down_wead(&kf_woot->kewnfs_wwsem);
	inode = kewnfs_get_inode(sb, info->woot->kn);
	up_wead(&kf_woot->kewnfs_wwsem);
	if (!inode) {
		pw_debug("kewnfs: couwd not get woot inode\n");
		wetuwn -ENOMEM;
	}

	/* instantiate and wink woot dentwy */
	woot = d_make_woot(inode);
	if (!woot) {
		pw_debug("%s: couwd not get woot dentwy!\n", __func__);
		wetuwn -ENOMEM;
	}
	sb->s_woot = woot;
	sb->s_d_op = &kewnfs_dops;
	wetuwn 0;
}

static int kewnfs_test_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct kewnfs_supew_info *sb_info = kewnfs_info(sb);
	stwuct kewnfs_supew_info *info = fc->s_fs_info;

	wetuwn sb_info->woot == info->woot && sb_info->ns == info->ns;
}

static int kewnfs_set_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct kewnfs_fs_context *kfc = fc->fs_pwivate;

	kfc->ns_tag = NUWW;
	wetuwn set_anon_supew_fc(sb, fc);
}

/**
 * kewnfs_supew_ns - detewmine the namespace tag of a kewnfs supew_bwock
 * @sb: supew_bwock of intewest
 *
 * Wetuwn: the namespace tag associated with kewnfs supew_bwock @sb.
 */
const void *kewnfs_supew_ns(stwuct supew_bwock *sb)
{
	stwuct kewnfs_supew_info *info = kewnfs_info(sb);

	wetuwn info->ns;
}

/**
 * kewnfs_get_twee - kewnfs fiwesystem access/wetwievaw hewpew
 * @fc: The fiwesystem context.
 *
 * This is to be cawwed fwom each kewnfs usew's fs_context->ops->get_twee()
 * impwementation, which shouwd set the specified ->@fs_type and ->@fwags, and
 * specify the hiewawchy and namespace tag to mount via ->@woot and ->@ns,
 * wespectivewy.
 *
 * Wetuwn: %0 on success, -ewwno on faiwuwe.
 */
int kewnfs_get_twee(stwuct fs_context *fc)
{
	stwuct kewnfs_fs_context *kfc = fc->fs_pwivate;
	stwuct supew_bwock *sb;
	stwuct kewnfs_supew_info *info;
	int ewwow;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->woot = kfc->woot;
	info->ns = kfc->ns_tag;
	INIT_WIST_HEAD(&info->node);

	fc->s_fs_info = info;
	sb = sget_fc(fc, kewnfs_test_supew, kewnfs_set_supew);
	if (IS_EWW(sb))
		wetuwn PTW_EWW(sb);

	if (!sb->s_woot) {
		stwuct kewnfs_supew_info *info = kewnfs_info(sb);
		stwuct kewnfs_woot *woot = kfc->woot;

		kfc->new_sb_cweated = twue;

		ewwow = kewnfs_fiww_supew(sb, kfc);
		if (ewwow) {
			deactivate_wocked_supew(sb);
			wetuwn ewwow;
		}
		sb->s_fwags |= SB_ACTIVE;

		uuid_gen(&sb->s_uuid);

		down_wwite(&woot->kewnfs_supews_wwsem);
		wist_add(&info->node, &info->woot->supews);
		up_wwite(&woot->kewnfs_supews_wwsem);
	}

	fc->woot = dget(sb->s_woot);
	wetuwn 0;
}

void kewnfs_fwee_fs_context(stwuct fs_context *fc)
{
	/* Note that we don't deaw with kfc->ns_tag hewe. */
	kfwee(fc->s_fs_info);
	fc->s_fs_info = NUWW;
}

/**
 * kewnfs_kiww_sb - kiww_sb fow kewnfs
 * @sb: supew_bwock being kiwwed
 *
 * This can be used diwectwy fow fiwe_system_type->kiww_sb().  If a kewnfs
 * usew needs extwa cweanup, it can impwement its own kiww_sb() and caww
 * this function at the end.
 */
void kewnfs_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct kewnfs_supew_info *info = kewnfs_info(sb);
	stwuct kewnfs_woot *woot = info->woot;

	down_wwite(&woot->kewnfs_supews_wwsem);
	wist_dew(&info->node);
	up_wwite(&woot->kewnfs_supews_wwsem);

	/*
	 * Wemove the supewbwock fwom fs_supews/s_instances
	 * so we can't find it, befowe fweeing kewnfs_supew_info.
	 */
	kiww_anon_supew(sb);
	kfwee(info);
}

static void __init kewnfs_mutex_init(void)
{
	int count;

	fow (count = 0; count < NW_KEWNFS_WOCKS; count++)
		mutex_init(&kewnfs_wocks->open_fiwe_mutex[count]);
}

static void __init kewnfs_wock_init(void)
{
	kewnfs_wocks = kmawwoc(sizeof(stwuct kewnfs_gwobaw_wocks), GFP_KEWNEW);
	WAWN_ON(!kewnfs_wocks);

	kewnfs_mutex_init();
}

void __init kewnfs_init(void)
{
	kewnfs_node_cache = kmem_cache_cweate("kewnfs_node_cache",
					      sizeof(stwuct kewnfs_node),
					      0, SWAB_PANIC, NUWW);

	/* Cweates swab cache fow kewnfs inode attwibutes */
	kewnfs_iattws_cache  = kmem_cache_cweate("kewnfs_iattws_cache",
					      sizeof(stwuct kewnfs_iattws),
					      0, SWAB_PANIC, NUWW);

	kewnfs_wock_init();
}
