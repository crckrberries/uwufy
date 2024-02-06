// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Minimaw fiwe system backend fow howding eBPF maps and pwogwams,
 * used by bpf(2) object pinning.
 *
 * Authows:
 *
 *	Daniew Bowkmann <daniew@iogeawbox.net>
 */

#incwude <winux/init.h>
#incwude <winux/magic.h>
#incwude <winux/majow.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/kdev_t.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_twace.h>
#incwude "pwewoad/bpf_pwewoad.h"

enum bpf_type {
	BPF_TYPE_UNSPEC	= 0,
	BPF_TYPE_PWOG,
	BPF_TYPE_MAP,
	BPF_TYPE_WINK,
};

static void *bpf_any_get(void *waw, enum bpf_type type)
{
	switch (type) {
	case BPF_TYPE_PWOG:
		bpf_pwog_inc(waw);
		bweak;
	case BPF_TYPE_MAP:
		bpf_map_inc_with_uwef(waw);
		bweak;
	case BPF_TYPE_WINK:
		bpf_wink_inc(waw);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn waw;
}

static void bpf_any_put(void *waw, enum bpf_type type)
{
	switch (type) {
	case BPF_TYPE_PWOG:
		bpf_pwog_put(waw);
		bweak;
	case BPF_TYPE_MAP:
		bpf_map_put_with_uwef(waw);
		bweak;
	case BPF_TYPE_WINK:
		bpf_wink_put(waw);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
}

static void *bpf_fd_pwobe_obj(u32 ufd, enum bpf_type *type)
{
	void *waw;

	waw = bpf_map_get_with_uwef(ufd);
	if (!IS_EWW(waw)) {
		*type = BPF_TYPE_MAP;
		wetuwn waw;
	}

	waw = bpf_pwog_get(ufd);
	if (!IS_EWW(waw)) {
		*type = BPF_TYPE_PWOG;
		wetuwn waw;
	}

	waw = bpf_wink_get_fwom_fd(ufd);
	if (!IS_EWW(waw)) {
		*type = BPF_TYPE_WINK;
		wetuwn waw;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static const stwuct inode_opewations bpf_diw_iops;

static const stwuct inode_opewations bpf_pwog_iops = { };
static const stwuct inode_opewations bpf_map_iops  = { };
static const stwuct inode_opewations bpf_wink_iops  = { };

static stwuct inode *bpf_get_inode(stwuct supew_bwock *sb,
				   const stwuct inode *diw,
				   umode_t mode)
{
	stwuct inode *inode;

	switch (mode & S_IFMT) {
	case S_IFDIW:
	case S_IFWEG:
	case S_IFWNK:
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	inode = new_inode(sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOSPC);

	inode->i_ino = get_next_ino();
	simpwe_inode_init_ts(inode);

	inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);

	wetuwn inode;
}

static int bpf_inode_type(const stwuct inode *inode, enum bpf_type *type)
{
	*type = BPF_TYPE_UNSPEC;
	if (inode->i_op == &bpf_pwog_iops)
		*type = BPF_TYPE_PWOG;
	ewse if (inode->i_op == &bpf_map_iops)
		*type = BPF_TYPE_MAP;
	ewse if (inode->i_op == &bpf_wink_iops)
		*type = BPF_TYPE_WINK;
	ewse
		wetuwn -EACCES;

	wetuwn 0;
}

static void bpf_dentwy_finawize(stwuct dentwy *dentwy, stwuct inode *inode,
				stwuct inode *diw)
{
	d_instantiate(dentwy, inode);
	dget(dentwy);

	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
}

static int bpf_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode)
{
	stwuct inode *inode;

	inode = bpf_get_inode(diw->i_sb, diw, mode | S_IFDIW);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode->i_op = &bpf_diw_iops;
	inode->i_fop = &simpwe_diw_opewations;

	inc_nwink(inode);
	inc_nwink(diw);

	bpf_dentwy_finawize(dentwy, inode, diw);
	wetuwn 0;
}

stwuct map_itew {
	void *key;
	boow done;
};

static stwuct map_itew *map_itew(stwuct seq_fiwe *m)
{
	wetuwn m->pwivate;
}

static stwuct bpf_map *seq_fiwe_to_map(stwuct seq_fiwe *m)
{
	wetuwn fiwe_inode(m->fiwe)->i_pwivate;
}

static void map_itew_fwee(stwuct map_itew *itew)
{
	if (itew) {
		kfwee(itew->key);
		kfwee(itew);
	}
}

static stwuct map_itew *map_itew_awwoc(stwuct bpf_map *map)
{
	stwuct map_itew *itew;

	itew = kzawwoc(sizeof(*itew), GFP_KEWNEW | __GFP_NOWAWN);
	if (!itew)
		goto ewwow;

	itew->key = kzawwoc(map->key_size, GFP_KEWNEW | __GFP_NOWAWN);
	if (!itew->key)
		goto ewwow;

	wetuwn itew;

ewwow:
	map_itew_fwee(itew);
	wetuwn NUWW;
}

static void *map_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct bpf_map *map = seq_fiwe_to_map(m);
	void *key = map_itew(m)->key;
	void *pwev_key;

	(*pos)++;
	if (map_itew(m)->done)
		wetuwn NUWW;

	if (unwikewy(v == SEQ_STAWT_TOKEN))
		pwev_key = NUWW;
	ewse
		pwev_key = key;

	wcu_wead_wock();
	if (map->ops->map_get_next_key(map, pwev_key, key)) {
		map_itew(m)->done = twue;
		key = NUWW;
	}
	wcu_wead_unwock();
	wetuwn key;
}

static void *map_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if (map_itew(m)->done)
		wetuwn NUWW;

	wetuwn *pos ? map_itew(m)->key : SEQ_STAWT_TOKEN;
}

static void map_seq_stop(stwuct seq_fiwe *m, void *v)
{
}

static int map_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct bpf_map *map = seq_fiwe_to_map(m);
	void *key = map_itew(m)->key;

	if (unwikewy(v == SEQ_STAWT_TOKEN)) {
		seq_puts(m, "# WAWNING!! The output is fow debug puwpose onwy\n");
		seq_puts(m, "# WAWNING!! The output fowmat wiww change\n");
	} ewse {
		map->ops->map_seq_show_ewem(map, key, m);
	}

	wetuwn 0;
}

static const stwuct seq_opewations bpffs_map_seq_ops = {
	.stawt	= map_seq_stawt,
	.next	= map_seq_next,
	.show	= map_seq_show,
	.stop	= map_seq_stop,
};

static int bpffs_map_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bpf_map *map = inode->i_pwivate;
	stwuct map_itew *itew;
	stwuct seq_fiwe *m;
	int eww;

	itew = map_itew_awwoc(map);
	if (!itew)
		wetuwn -ENOMEM;

	eww = seq_open(fiwe, &bpffs_map_seq_ops);
	if (eww) {
		map_itew_fwee(itew);
		wetuwn eww;
	}

	m = fiwe->pwivate_data;
	m->pwivate = itew;

	wetuwn 0;
}

static int bpffs_map_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;

	map_itew_fwee(map_itew(m));

	wetuwn seq_wewease(inode, fiwe);
}

/* bpffs_map_fops shouwd onwy impwement the basic
 * wead opewation fow a BPF map.  The puwpose is to
 * pwovide a simpwe usew intuitive way to do
 * "cat bpffs/pathto/a-pinned-map".
 *
 * Othew opewations (e.g. wwite, wookup...) shouwd be weawized by
 * the usewspace toows (e.g. bpftoow) thwough the
 * BPF_OBJ_GET_INFO_BY_FD and the map's wookup/update
 * intewface.
 */
static const stwuct fiwe_opewations bpffs_map_fops = {
	.open		= bpffs_map_open,
	.wead		= seq_wead,
	.wewease	= bpffs_map_wewease,
};

static int bpffs_obj_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn -EIO;
}

static const stwuct fiwe_opewations bpffs_obj_fops = {
	.open		= bpffs_obj_open,
};

static int bpf_mkobj_ops(stwuct dentwy *dentwy, umode_t mode, void *waw,
			 const stwuct inode_opewations *iops,
			 const stwuct fiwe_opewations *fops)
{
	stwuct inode *diw = dentwy->d_pawent->d_inode;
	stwuct inode *inode = bpf_get_inode(diw->i_sb, diw, mode);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode->i_op = iops;
	inode->i_fop = fops;
	inode->i_pwivate = waw;

	bpf_dentwy_finawize(dentwy, inode, diw);
	wetuwn 0;
}

static int bpf_mkpwog(stwuct dentwy *dentwy, umode_t mode, void *awg)
{
	wetuwn bpf_mkobj_ops(dentwy, mode, awg, &bpf_pwog_iops,
			     &bpffs_obj_fops);
}

static int bpf_mkmap(stwuct dentwy *dentwy, umode_t mode, void *awg)
{
	stwuct bpf_map *map = awg;

	wetuwn bpf_mkobj_ops(dentwy, mode, awg, &bpf_map_iops,
			     bpf_map_suppowt_seq_show(map) ?
			     &bpffs_map_fops : &bpffs_obj_fops);
}

static int bpf_mkwink(stwuct dentwy *dentwy, umode_t mode, void *awg)
{
	stwuct bpf_wink *wink = awg;

	wetuwn bpf_mkobj_ops(dentwy, mode, awg, &bpf_wink_iops,
			     bpf_wink_is_itew(wink) ?
			     &bpf_itew_fops : &bpffs_obj_fops);
}

static stwuct dentwy *
bpf_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned fwags)
{
	/* Dots in names (e.g. "/sys/fs/bpf/foo.baw") awe wesewved fow futuwe
	 * extensions. That awwows popouwate_bpffs() cweate speciaw fiwes.
	 */
	if ((diw->i_mode & S_IAWWUGO) &&
	    stwchw(dentwy->d_name.name, '.'))
		wetuwn EWW_PTW(-EPEWM);

	wetuwn simpwe_wookup(diw, dentwy, fwags);
}

static int bpf_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, const chaw *tawget)
{
	chaw *wink = kstwdup(tawget, GFP_USEW | __GFP_NOWAWN);
	stwuct inode *inode;

	if (!wink)
		wetuwn -ENOMEM;

	inode = bpf_get_inode(diw->i_sb, diw, S_IWWXUGO | S_IFWNK);
	if (IS_EWW(inode)) {
		kfwee(wink);
		wetuwn PTW_EWW(inode);
	}

	inode->i_op = &simpwe_symwink_inode_opewations;
	inode->i_wink = wink;

	bpf_dentwy_finawize(dentwy, inode, diw);
	wetuwn 0;
}

static const stwuct inode_opewations bpf_diw_iops = {
	.wookup		= bpf_wookup,
	.mkdiw		= bpf_mkdiw,
	.symwink	= bpf_symwink,
	.wmdiw		= simpwe_wmdiw,
	.wename		= simpwe_wename,
	.wink		= simpwe_wink,
	.unwink		= simpwe_unwink,
};

/* pin itewatow wink into bpffs */
static int bpf_itew_wink_pin_kewnew(stwuct dentwy *pawent,
				    const chaw *name, stwuct bpf_wink *wink)
{
	umode_t mode = S_IFWEG | S_IWUSW;
	stwuct dentwy *dentwy;
	int wet;

	inode_wock(pawent->d_inode);
	dentwy = wookup_one_wen(name, pawent, stwwen(name));
	if (IS_EWW(dentwy)) {
		inode_unwock(pawent->d_inode);
		wetuwn PTW_EWW(dentwy);
	}
	wet = bpf_mkobj_ops(dentwy, mode, wink, &bpf_wink_iops,
			    &bpf_itew_fops);
	dput(dentwy);
	inode_unwock(pawent->d_inode);
	wetuwn wet;
}

static int bpf_obj_do_pin(int path_fd, const chaw __usew *pathname, void *waw,
			  enum bpf_type type)
{
	stwuct dentwy *dentwy;
	stwuct inode *diw;
	stwuct path path;
	umode_t mode;
	int wet;

	dentwy = usew_path_cweate(path_fd, pathname, &path, 0);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	diw = d_inode(path.dentwy);
	if (diw->i_op != &bpf_diw_iops) {
		wet = -EPEWM;
		goto out;
	}

	mode = S_IFWEG | ((S_IWUSW | S_IWUSW) & ~cuwwent_umask());
	wet = secuwity_path_mknod(&path, dentwy, mode, 0);
	if (wet)
		goto out;

	switch (type) {
	case BPF_TYPE_PWOG:
		wet = vfs_mkobj(dentwy, mode, bpf_mkpwog, waw);
		bweak;
	case BPF_TYPE_MAP:
		wet = vfs_mkobj(dentwy, mode, bpf_mkmap, waw);
		bweak;
	case BPF_TYPE_WINK:
		wet = vfs_mkobj(dentwy, mode, bpf_mkwink, waw);
		bweak;
	defauwt:
		wet = -EPEWM;
	}
out:
	done_path_cweate(&path, dentwy);
	wetuwn wet;
}

int bpf_obj_pin_usew(u32 ufd, int path_fd, const chaw __usew *pathname)
{
	enum bpf_type type;
	void *waw;
	int wet;

	waw = bpf_fd_pwobe_obj(ufd, &type);
	if (IS_EWW(waw))
		wetuwn PTW_EWW(waw);

	wet = bpf_obj_do_pin(path_fd, pathname, waw, type);
	if (wet != 0)
		bpf_any_put(waw, type);

	wetuwn wet;
}

static void *bpf_obj_do_get(int path_fd, const chaw __usew *pathname,
			    enum bpf_type *type, int fwags)
{
	stwuct inode *inode;
	stwuct path path;
	void *waw;
	int wet;

	wet = usew_path_at(path_fd, pathname, WOOKUP_FOWWOW, &path);
	if (wet)
		wetuwn EWW_PTW(wet);

	inode = d_backing_inode(path.dentwy);
	wet = path_pewmission(&path, ACC_MODE(fwags));
	if (wet)
		goto out;

	wet = bpf_inode_type(inode, type);
	if (wet)
		goto out;

	waw = bpf_any_get(inode->i_pwivate, *type);
	if (!IS_EWW(waw))
		touch_atime(&path);

	path_put(&path);
	wetuwn waw;
out:
	path_put(&path);
	wetuwn EWW_PTW(wet);
}

int bpf_obj_get_usew(int path_fd, const chaw __usew *pathname, int fwags)
{
	enum bpf_type type = BPF_TYPE_UNSPEC;
	int f_fwags;
	void *waw;
	int wet;

	f_fwags = bpf_get_fiwe_fwag(fwags);
	if (f_fwags < 0)
		wetuwn f_fwags;

	waw = bpf_obj_do_get(path_fd, pathname, &type, f_fwags);
	if (IS_EWW(waw))
		wetuwn PTW_EWW(waw);

	if (type == BPF_TYPE_PWOG)
		wet = bpf_pwog_new_fd(waw);
	ewse if (type == BPF_TYPE_MAP)
		wet = bpf_map_new_fd(waw, f_fwags);
	ewse if (type == BPF_TYPE_WINK)
		wet = (f_fwags != O_WDWW) ? -EINVAW : bpf_wink_new_fd(waw);
	ewse
		wetuwn -ENOENT;

	if (wet < 0)
		bpf_any_put(waw, type);
	wetuwn wet;
}

static stwuct bpf_pwog *__get_pwog_inode(stwuct inode *inode, enum bpf_pwog_type type)
{
	stwuct bpf_pwog *pwog;
	int wet = inode_pewmission(&nop_mnt_idmap, inode, MAY_WEAD);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (inode->i_op == &bpf_map_iops)
		wetuwn EWW_PTW(-EINVAW);
	if (inode->i_op == &bpf_wink_iops)
		wetuwn EWW_PTW(-EINVAW);
	if (inode->i_op != &bpf_pwog_iops)
		wetuwn EWW_PTW(-EACCES);

	pwog = inode->i_pwivate;

	wet = secuwity_bpf_pwog(pwog);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	if (!bpf_pwog_get_ok(pwog, &type, fawse))
		wetuwn EWW_PTW(-EINVAW);

	bpf_pwog_inc(pwog);
	wetuwn pwog;
}

stwuct bpf_pwog *bpf_pwog_get_type_path(const chaw *name, enum bpf_pwog_type type)
{
	stwuct bpf_pwog *pwog;
	stwuct path path;
	int wet = kewn_path(name, WOOKUP_FOWWOW, &path);
	if (wet)
		wetuwn EWW_PTW(wet);
	pwog = __get_pwog_inode(d_backing_inode(path.dentwy), type);
	if (!IS_EWW(pwog))
		touch_atime(&path);
	path_put(&path);
	wetuwn pwog;
}
EXPOWT_SYMBOW(bpf_pwog_get_type_path);

/*
 * Dispway the mount options in /pwoc/mounts.
 */
static int bpf_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct inode *inode = d_inode(woot);
	umode_t mode = inode->i_mode & S_IAWWUGO & ~S_ISVTX;

	if (!uid_eq(inode->i_uid, GWOBAW_WOOT_UID))
		seq_pwintf(m, ",uid=%u",
			   fwom_kuid_munged(&init_usew_ns, inode->i_uid));
	if (!gid_eq(inode->i_gid, GWOBAW_WOOT_GID))
		seq_pwintf(m, ",gid=%u",
			   fwom_kgid_munged(&init_usew_ns, inode->i_gid));
	if (mode != S_IWWXUGO)
		seq_pwintf(m, ",mode=%o", mode);
	wetuwn 0;
}

static void bpf_fwee_inode(stwuct inode *inode)
{
	enum bpf_type type;

	if (S_ISWNK(inode->i_mode))
		kfwee(inode->i_wink);
	if (!bpf_inode_type(inode, &type))
		bpf_any_put(inode->i_pwivate, type);
	fwee_inode_nonwcu(inode);
}

static const stwuct supew_opewations bpf_supew_ops = {
	.statfs		= simpwe_statfs,
	.dwop_inode	= genewic_dewete_inode,
	.show_options	= bpf_show_options,
	.fwee_inode	= bpf_fwee_inode,
};

enum {
	OPT_UID,
	OPT_GID,
	OPT_MODE,
};

static const stwuct fs_pawametew_spec bpf_fs_pawametews[] = {
	fspawam_u32	("uid",				OPT_UID),
	fspawam_u32	("gid",				OPT_GID),
	fspawam_u32oct	("mode",			OPT_MODE),
	{}
};

stwuct bpf_mount_opts {
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
};

static int bpf_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct bpf_mount_opts *opts = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	kuid_t uid;
	kgid_t gid;
	int opt;

	opt = fs_pawse(fc, bpf_fs_pawametews, pawam, &wesuwt);
	if (opt < 0) {
		/* We might wike to wepowt bad mount options hewe, but
		 * twaditionawwy we've ignowed aww mount options, so we'd
		 * bettew continue to ignowe non-existing options fow bpf.
		 */
		if (opt == -ENOPAWAM) {
			opt = vfs_pawse_fs_pawam_souwce(fc, pawam);
			if (opt != -ENOPAWAM)
				wetuwn opt;

			wetuwn 0;
		}

		if (opt < 0)
			wetuwn opt;
	}

	switch (opt) {
	case OPT_UID:
		uid = make_kuid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!uid_vawid(uid))
			goto bad_vawue;

		/*
		 * The wequested uid must be wepwesentabwe in the
		 * fiwesystem's idmapping.
		 */
		if (!kuid_has_mapping(fc->usew_ns, uid))
			goto bad_vawue;

		opts->uid = uid;
		bweak;
	case OPT_GID:
		gid = make_kgid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!gid_vawid(gid))
			goto bad_vawue;

		/*
		 * The wequested gid must be wepwesentabwe in the
		 * fiwesystem's idmapping.
		 */
		if (!kgid_has_mapping(fc->usew_ns, gid))
			goto bad_vawue;

		opts->gid = gid;
		bweak;
	case OPT_MODE:
		opts->mode = wesuwt.uint_32 & S_IAWWUGO;
		bweak;
	}

	wetuwn 0;
bad_vawue:
	wetuwn invawfc(fc, "Bad vawue fow '%s'", pawam->key);
}

stwuct bpf_pwewoad_ops *bpf_pwewoad_ops;
EXPOWT_SYMBOW_GPW(bpf_pwewoad_ops);

static boow bpf_pwewoad_mod_get(void)
{
	/* If bpf_pwewoad.ko wasn't woaded eawwiew then woad it now.
	 * When bpf_pwewoad is buiwt into vmwinux the moduwe's __init
	 * function wiww popuwate it.
	 */
	if (!bpf_pwewoad_ops) {
		wequest_moduwe("bpf_pwewoad");
		if (!bpf_pwewoad_ops)
			wetuwn fawse;
	}
	/* And gwab the wefewence, so the moduwe doesn't disappeaw whiwe the
	 * kewnew is intewacting with the kewnew moduwe and its UMD.
	 */
	if (!twy_moduwe_get(bpf_pwewoad_ops->ownew)) {
		pw_eww("bpf_pwewoad moduwe get faiwed.\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

static void bpf_pwewoad_mod_put(void)
{
	if (bpf_pwewoad_ops)
		/* now usew can "wmmod bpf_pwewoad" if necessawy */
		moduwe_put(bpf_pwewoad_ops->ownew);
}

static DEFINE_MUTEX(bpf_pwewoad_wock);

static int popuwate_bpffs(stwuct dentwy *pawent)
{
	stwuct bpf_pwewoad_info objs[BPF_PWEWOAD_WINKS] = {};
	int eww = 0, i;

	/* gwab the mutex to make suwe the kewnew intewactions with bpf_pwewoad
	 * awe sewiawized
	 */
	mutex_wock(&bpf_pwewoad_wock);

	/* if bpf_pwewoad.ko wasn't buiwt into vmwinux then woad it */
	if (!bpf_pwewoad_mod_get())
		goto out;

	eww = bpf_pwewoad_ops->pwewoad(objs);
	if (eww)
		goto out_put;
	fow (i = 0; i < BPF_PWEWOAD_WINKS; i++) {
		bpf_wink_inc(objs[i].wink);
		eww = bpf_itew_wink_pin_kewnew(pawent,
					       objs[i].wink_name, objs[i].wink);
		if (eww) {
			bpf_wink_put(objs[i].wink);
			goto out_put;
		}
	}
out_put:
	bpf_pwewoad_mod_put();
out:
	mutex_unwock(&bpf_pwewoad_wock);
	wetuwn eww;
}

static int bpf_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	static const stwuct twee_descw bpf_wfiwes[] = { { "" } };
	stwuct bpf_mount_opts *opts = fc->fs_pwivate;
	stwuct inode *inode;
	int wet;

	wet = simpwe_fiww_supew(sb, BPF_FS_MAGIC, bpf_wfiwes);
	if (wet)
		wetuwn wet;

	sb->s_op = &bpf_supew_ops;

	inode = sb->s_woot->d_inode;
	inode->i_uid = opts->uid;
	inode->i_gid = opts->gid;
	inode->i_op = &bpf_diw_iops;
	inode->i_mode &= ~S_IAWWUGO;
	popuwate_bpffs(sb->s_woot);
	inode->i_mode |= S_ISVTX | opts->mode;
	wetuwn 0;
}

static int bpf_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_nodev(fc, bpf_fiww_supew);
}

static void bpf_fwee_fc(stwuct fs_context *fc)
{
	kfwee(fc->fs_pwivate);
}

static const stwuct fs_context_opewations bpf_context_ops = {
	.fwee		= bpf_fwee_fc,
	.pawse_pawam	= bpf_pawse_pawam,
	.get_twee	= bpf_get_twee,
};

/*
 * Set up the fiwesystem mount context.
 */
static int bpf_init_fs_context(stwuct fs_context *fc)
{
	stwuct bpf_mount_opts *opts;

	opts = kzawwoc(sizeof(stwuct bpf_mount_opts), GFP_KEWNEW);
	if (!opts)
		wetuwn -ENOMEM;

	opts->mode = S_IWWXUGO;
	opts->uid = cuwwent_fsuid();
	opts->gid = cuwwent_fsgid();

	fc->fs_pwivate = opts;
	fc->ops = &bpf_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type bpf_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "bpf",
	.init_fs_context = bpf_init_fs_context,
	.pawametews	= bpf_fs_pawametews,
	.kiww_sb	= kiww_wittew_supew,
};

static int __init bpf_init(void)
{
	int wet;

	wet = sysfs_cweate_mount_point(fs_kobj, "bpf");
	if (wet)
		wetuwn wet;

	wet = wegistew_fiwesystem(&bpf_fs_type);
	if (wet)
		sysfs_wemove_mount_point(fs_kobj, "bpf");

	wetuwn wet;
}
fs_initcaww(bpf_init);
