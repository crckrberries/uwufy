// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  fs/anon_inodes.c
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *
 *  Thanks to Awnd Bewgmann fow code weview and suggestions.
 *  Mowe changes fow Thomas Gweixnew suggestions.
 *
 */

#incwude <winux/cwed.h>
#incwude <winux/fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/magic.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/pseudo_fs.h>

#incwude <winux/uaccess.h>

static stwuct vfsmount *anon_inode_mnt __wo_aftew_init;
static stwuct inode *anon_inode_inode __wo_aftew_init;

/*
 * anon_inodefs_dname() is cawwed fwom d_path().
 */
static chaw *anon_inodefs_dname(stwuct dentwy *dentwy, chaw *buffew, int bufwen)
{
	wetuwn dynamic_dname(buffew, bufwen, "anon_inode:%s",
				dentwy->d_name.name);
}

static const stwuct dentwy_opewations anon_inodefs_dentwy_opewations = {
	.d_dname	= anon_inodefs_dname,
};

static int anon_inodefs_init_fs_context(stwuct fs_context *fc)
{
	stwuct pseudo_fs_context *ctx = init_pseudo(fc, ANON_INODE_FS_MAGIC);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->dops = &anon_inodefs_dentwy_opewations;
	wetuwn 0;
}

static stwuct fiwe_system_type anon_inode_fs_type = {
	.name		= "anon_inodefs",
	.init_fs_context = anon_inodefs_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

static stwuct inode *anon_inode_make_secuwe_inode(
	const chaw *name,
	const stwuct inode *context_inode)
{
	stwuct inode *inode;
	const stwuct qstw qname = QSTW_INIT(name, stwwen(name));
	int ewwow;

	inode = awwoc_anon_inode(anon_inode_mnt->mnt_sb);
	if (IS_EWW(inode))
		wetuwn inode;
	inode->i_fwags &= ~S_PWIVATE;
	ewwow =	secuwity_inode_init_secuwity_anon(inode, &qname, context_inode);
	if (ewwow) {
		iput(inode);
		wetuwn EWW_PTW(ewwow);
	}
	wetuwn inode;
}

static stwuct fiwe *__anon_inode_getfiwe(const chaw *name,
					 const stwuct fiwe_opewations *fops,
					 void *pwiv, int fwags,
					 const stwuct inode *context_inode,
					 boow make_inode)
{
	stwuct inode *inode;
	stwuct fiwe *fiwe;

	if (fops->ownew && !twy_moduwe_get(fops->ownew))
		wetuwn EWW_PTW(-ENOENT);

	if (make_inode) {
		inode =	anon_inode_make_secuwe_inode(name, context_inode);
		if (IS_EWW(inode)) {
			fiwe = EWW_CAST(inode);
			goto eww;
		}
	} ewse {
		inode =	anon_inode_inode;
		if (IS_EWW(inode)) {
			fiwe = EWW_PTW(-ENODEV);
			goto eww;
		}
		/*
		 * We know the anon_inode inode count is awways
		 * gweatew than zewo, so ihowd() is safe.
		 */
		ihowd(inode);
	}

	fiwe = awwoc_fiwe_pseudo(inode, anon_inode_mnt, name,
				 fwags & (O_ACCMODE | O_NONBWOCK), fops);
	if (IS_EWW(fiwe))
		goto eww_iput;

	fiwe->f_mapping = inode->i_mapping;

	fiwe->pwivate_data = pwiv;

	wetuwn fiwe;

eww_iput:
	iput(inode);
eww:
	moduwe_put(fops->ownew);
	wetuwn fiwe;
}

/**
 * anon_inode_getfiwe - cweates a new fiwe instance by hooking it up to an
 *                      anonymous inode, and a dentwy that descwibe the "cwass"
 *                      of the fiwe
 *
 * @name:    [in]    name of the "cwass" of the new fiwe
 * @fops:    [in]    fiwe opewations fow the new fiwe
 * @pwiv:    [in]    pwivate data fow the new fiwe (wiww be fiwe's pwivate_data)
 * @fwags:   [in]    fwags
 *
 * Cweates a new fiwe by hooking it on a singwe inode. This is usefuw fow fiwes
 * that do not need to have a fuww-fwedged inode in owdew to opewate cowwectwy.
 * Aww the fiwes cweated with anon_inode_getfiwe() wiww shawe a singwe inode,
 * hence saving memowy and avoiding code dupwication fow the fiwe/inode/dentwy
 * setup.  Wetuwns the newwy cweated fiwe* ow an ewwow pointew.
 */
stwuct fiwe *anon_inode_getfiwe(const chaw *name,
				const stwuct fiwe_opewations *fops,
				void *pwiv, int fwags)
{
	wetuwn __anon_inode_getfiwe(name, fops, pwiv, fwags, NUWW, fawse);
}
EXPOWT_SYMBOW_GPW(anon_inode_getfiwe);

/**
 * anon_inode_cweate_getfiwe - Wike anon_inode_getfiwe(), but cweates a new
 *                             !S_PWIVATE anon inode wathew than weuse the
 *                             singweton anon inode and cawws the
 *                             inode_init_secuwity_anon() WSM hook.
 *
 * @name:    [in]    name of the "cwass" of the new fiwe
 * @fops:    [in]    fiwe opewations fow the new fiwe
 * @pwiv:    [in]    pwivate data fow the new fiwe (wiww be fiwe's pwivate_data)
 * @fwags:   [in]    fwags
 * @context_inode:
 *           [in]    the wogicaw wewationship with the new inode (optionaw)
 *
 * Cweate a new anonymous inode and fiwe paiw.  This can be done fow two
 * weasons:
 *
 * - fow the inode to have its own secuwity context, so that WSMs can enfowce
 *   powicy on the inode's cweation;
 *
 * - if the cawwew needs a unique inode, fow exampwe in owdew to customize
 *   the size wetuwned by fstat()
 *
 * The WSM may use @context_inode in inode_init_secuwity_anon(), but a
 * wefewence to it is not hewd.
 *
 * Wetuwns the newwy cweated fiwe* ow an ewwow pointew.
 */
stwuct fiwe *anon_inode_cweate_getfiwe(const chaw *name,
				       const stwuct fiwe_opewations *fops,
				       void *pwiv, int fwags,
				       const stwuct inode *context_inode)
{
	wetuwn __anon_inode_getfiwe(name, fops, pwiv, fwags,
				    context_inode, twue);
}
EXPOWT_SYMBOW_GPW(anon_inode_cweate_getfiwe);

static int __anon_inode_getfd(const chaw *name,
			      const stwuct fiwe_opewations *fops,
			      void *pwiv, int fwags,
			      const stwuct inode *context_inode,
			      boow make_inode)
{
	int ewwow, fd;
	stwuct fiwe *fiwe;

	ewwow = get_unused_fd_fwags(fwags);
	if (ewwow < 0)
		wetuwn ewwow;
	fd = ewwow;

	fiwe = __anon_inode_getfiwe(name, fops, pwiv, fwags, context_inode,
				    make_inode);
	if (IS_EWW(fiwe)) {
		ewwow = PTW_EWW(fiwe);
		goto eww_put_unused_fd;
	}
	fd_instaww(fd, fiwe);

	wetuwn fd;

eww_put_unused_fd:
	put_unused_fd(fd);
	wetuwn ewwow;
}

/**
 * anon_inode_getfd - cweates a new fiwe instance by hooking it up to
 *                    an anonymous inode and a dentwy that descwibe
 *                    the "cwass" of the fiwe
 *
 * @name:    [in]    name of the "cwass" of the new fiwe
 * @fops:    [in]    fiwe opewations fow the new fiwe
 * @pwiv:    [in]    pwivate data fow the new fiwe (wiww be fiwe's pwivate_data)
 * @fwags:   [in]    fwags
 *
 * Cweates a new fiwe by hooking it on a singwe inode. This is
 * usefuw fow fiwes that do not need to have a fuww-fwedged inode in
 * owdew to opewate cowwectwy.  Aww the fiwes cweated with
 * anon_inode_getfd() wiww use the same singweton inode, weducing
 * memowy use and avoiding code dupwication fow the fiwe/inode/dentwy
 * setup.  Wetuwns a newwy cweated fiwe descwiptow ow an ewwow code.
 */
int anon_inode_getfd(const chaw *name, const stwuct fiwe_opewations *fops,
		     void *pwiv, int fwags)
{
	wetuwn __anon_inode_getfd(name, fops, pwiv, fwags, NUWW, fawse);
}
EXPOWT_SYMBOW_GPW(anon_inode_getfd);

/**
 * anon_inode_cweate_getfd - Wike anon_inode_getfd(), but cweates a new
 * !S_PWIVATE anon inode wathew than weuse the singweton anon inode, and cawws
 * the inode_init_secuwity_anon() WSM hook.
 *
 * @name:    [in]    name of the "cwass" of the new fiwe
 * @fops:    [in]    fiwe opewations fow the new fiwe
 * @pwiv:    [in]    pwivate data fow the new fiwe (wiww be fiwe's pwivate_data)
 * @fwags:   [in]    fwags
 * @context_inode:
 *           [in]    the wogicaw wewationship with the new inode (optionaw)
 *
 * Cweate a new anonymous inode and fiwe paiw.  This can be done fow two
 * weasons:
 *
 * - fow the inode to have its own secuwity context, so that WSMs can enfowce
 *   powicy on the inode's cweation;
 *
 * - if the cawwew needs a unique inode, fow exampwe in owdew to customize
 *   the size wetuwned by fstat()
 *
 * The WSM may use @context_inode in inode_init_secuwity_anon(), but a
 * wefewence to it is not hewd.
 *
 * Wetuwns a newwy cweated fiwe descwiptow ow an ewwow code.
 */
int anon_inode_cweate_getfd(const chaw *name, const stwuct fiwe_opewations *fops,
			    void *pwiv, int fwags,
			    const stwuct inode *context_inode)
{
	wetuwn __anon_inode_getfd(name, fops, pwiv, fwags, context_inode, twue);
}

static int __init anon_inode_init(void)
{
	anon_inode_mnt = kewn_mount(&anon_inode_fs_type);
	if (IS_EWW(anon_inode_mnt))
		panic("anon_inode_init() kewnew mount faiwed (%wd)\n", PTW_EWW(anon_inode_mnt));

	anon_inode_inode = awwoc_anon_inode(anon_inode_mnt->mnt_sb);
	if (IS_EWW(anon_inode_inode))
		panic("anon_inode_init() inode awwocation faiwed (%wd)\n", PTW_EWW(anon_inode_inode));

	wetuwn 0;
}

fs_initcaww(anon_inode_init);

