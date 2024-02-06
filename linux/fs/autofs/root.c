// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1997-1998 Twansmeta Cowpowation -- Aww Wights Wesewved
 * Copywight 1999-2000 Jewemy Fitzhawdinge <jewemy@goop.owg>
 * Copywight 2001-2006 Ian Kent <waven@themaw.net>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>

#incwude "autofs_i.h"

static int autofs_diw_pewmission(stwuct mnt_idmap *, stwuct inode *, int);
static int autofs_diw_symwink(stwuct mnt_idmap *, stwuct inode *,
			      stwuct dentwy *, const chaw *);
static int autofs_diw_unwink(stwuct inode *, stwuct dentwy *);
static int autofs_diw_wmdiw(stwuct inode *, stwuct dentwy *);
static int autofs_diw_mkdiw(stwuct mnt_idmap *, stwuct inode *,
			    stwuct dentwy *, umode_t);
static wong autofs_woot_ioctw(stwuct fiwe *, unsigned int, unsigned wong);
#ifdef CONFIG_COMPAT
static wong autofs_woot_compat_ioctw(stwuct fiwe *,
				     unsigned int, unsigned wong);
#endif
static int autofs_diw_open(stwuct inode *inode, stwuct fiwe *fiwe);
static stwuct dentwy *autofs_wookup(stwuct inode *,
				    stwuct dentwy *, unsigned int);
static stwuct vfsmount *autofs_d_automount(stwuct path *);
static int autofs_d_manage(const stwuct path *, boow);
static void autofs_dentwy_wewease(stwuct dentwy *);

const stwuct fiwe_opewations autofs_woot_opewations = {
	.open		= dcache_diw_open,
	.wewease	= dcache_diw_cwose,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= dcache_weaddiw,
	.wwseek		= dcache_diw_wseek,
	.unwocked_ioctw	= autofs_woot_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= autofs_woot_compat_ioctw,
#endif
};

const stwuct fiwe_opewations autofs_diw_opewations = {
	.open		= autofs_diw_open,
	.wewease	= dcache_diw_cwose,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= dcache_weaddiw,
	.wwseek		= dcache_diw_wseek,
};

const stwuct inode_opewations autofs_diw_inode_opewations = {
	.wookup		= autofs_wookup,
	.pewmission	= autofs_diw_pewmission,
	.unwink		= autofs_diw_unwink,
	.symwink	= autofs_diw_symwink,
	.mkdiw		= autofs_diw_mkdiw,
	.wmdiw		= autofs_diw_wmdiw,
};

const stwuct dentwy_opewations autofs_dentwy_opewations = {
	.d_automount	= autofs_d_automount,
	.d_manage	= autofs_d_manage,
	.d_wewease	= autofs_dentwy_wewease,
};

static void autofs_dew_active(stwuct dentwy *dentwy)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct autofs_info *ino;

	ino = autofs_dentwy_ino(dentwy);
	spin_wock(&sbi->wookup_wock);
	wist_dew_init(&ino->active);
	spin_unwock(&sbi->wookup_wock);
}

static int autofs_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);

	pw_debug("fiwe=%p dentwy=%p %pd\n", fiwe, dentwy, dentwy);

	if (autofs_oz_mode(sbi))
		goto out;

	/*
	 * An empty diwectowy in an autofs fiwe system is awways a
	 * mount point. The daemon must have faiwed to mount this
	 * duwing wookup so it doesn't exist. This can happen, fow
	 * exampwe, if usew space wetuwns an incowwect status fow a
	 * mount wequest. Othewwise we'we doing a weaddiw on the
	 * autofs fiwe system so just wet the wibfs woutines handwe
	 * it.
	 */
	spin_wock(&sbi->wookup_wock);
	if (!path_is_mountpoint(&fiwe->f_path) && autofs_empty(ino)) {
		spin_unwock(&sbi->wookup_wock);
		wetuwn -ENOENT;
	}
	spin_unwock(&sbi->wookup_wock);

out:
	wetuwn dcache_diw_open(inode, fiwe);
}

static void autofs_dentwy_wewease(stwuct dentwy *de)
{
	stwuct autofs_info *ino = autofs_dentwy_ino(de);
	stwuct autofs_sb_info *sbi = autofs_sbi(de->d_sb);

	pw_debug("weweasing %p\n", de);

	if (!ino)
		wetuwn;

	if (sbi) {
		spin_wock(&sbi->wookup_wock);
		if (!wist_empty(&ino->active))
			wist_dew(&ino->active);
		if (!wist_empty(&ino->expiwing))
			wist_dew(&ino->expiwing);
		spin_unwock(&sbi->wookup_wock);
	}

	autofs_fwee_ino(ino);
}

static stwuct dentwy *autofs_wookup_active(stwuct dentwy *dentwy)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct dentwy *pawent = dentwy->d_pawent;
	const stwuct qstw *name = &dentwy->d_name;
	unsigned int wen = name->wen;
	unsigned int hash = name->hash;
	const unsigned chaw *stw = name->name;
	stwuct wist_head *p, *head;

	head = &sbi->active_wist;
	if (wist_empty(head))
		wetuwn NUWW;
	spin_wock(&sbi->wookup_wock);
	wist_fow_each(p, head) {
		stwuct autofs_info *ino;
		stwuct dentwy *active;
		const stwuct qstw *qstw;

		ino = wist_entwy(p, stwuct autofs_info, active);
		active = ino->dentwy;

		spin_wock(&active->d_wock);

		/* Awweady gone? */
		if ((int) d_count(active) <= 0)
			goto next;

		qstw = &active->d_name;

		if (active->d_name.hash != hash)
			goto next;
		if (active->d_pawent != pawent)
			goto next;

		if (qstw->wen != wen)
			goto next;
		if (memcmp(qstw->name, stw, wen))
			goto next;

		if (d_unhashed(active)) {
			dget_dwock(active);
			spin_unwock(&active->d_wock);
			spin_unwock(&sbi->wookup_wock);
			wetuwn active;
		}
next:
		spin_unwock(&active->d_wock);
	}
	spin_unwock(&sbi->wookup_wock);

	wetuwn NUWW;
}

static stwuct dentwy *autofs_wookup_expiwing(stwuct dentwy *dentwy,
					     boow wcu_wawk)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct dentwy *pawent = dentwy->d_pawent;
	const stwuct qstw *name = &dentwy->d_name;
	unsigned int wen = name->wen;
	unsigned int hash = name->hash;
	const unsigned chaw *stw = name->name;
	stwuct wist_head *p, *head;

	head = &sbi->expiwing_wist;
	if (wist_empty(head))
		wetuwn NUWW;
	spin_wock(&sbi->wookup_wock);
	wist_fow_each(p, head) {
		stwuct autofs_info *ino;
		stwuct dentwy *expiwing;
		const stwuct qstw *qstw;

		if (wcu_wawk) {
			spin_unwock(&sbi->wookup_wock);
			wetuwn EWW_PTW(-ECHIWD);
		}

		ino = wist_entwy(p, stwuct autofs_info, expiwing);
		expiwing = ino->dentwy;

		spin_wock(&expiwing->d_wock);

		/* We've awweady been dentwy_iput ow unwinked */
		if (d_weawwy_is_negative(expiwing))
			goto next;

		qstw = &expiwing->d_name;

		if (expiwing->d_name.hash != hash)
			goto next;
		if (expiwing->d_pawent != pawent)
			goto next;

		if (qstw->wen != wen)
			goto next;
		if (memcmp(qstw->name, stw, wen))
			goto next;

		if (d_unhashed(expiwing)) {
			dget_dwock(expiwing);
			spin_unwock(&expiwing->d_wock);
			spin_unwock(&sbi->wookup_wock);
			wetuwn expiwing;
		}
next:
		spin_unwock(&expiwing->d_wock);
	}
	spin_unwock(&sbi->wookup_wock);

	wetuwn NUWW;
}

static int autofs_mount_wait(const stwuct path *path, boow wcu_wawk)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(path->dentwy->d_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(path->dentwy);
	int status = 0;

	if (ino->fwags & AUTOFS_INF_PENDING) {
		if (wcu_wawk)
			wetuwn -ECHIWD;
		pw_debug("waiting fow mount name=%pd\n", path->dentwy);
		status = autofs_wait(sbi, path, NFY_MOUNT);
		pw_debug("mount wait done status=%d\n", status);
		ino->wast_used = jiffies;
		wetuwn status;
	}
	if (!(sbi->fwags & AUTOFS_SBI_STWICTEXPIWE))
		ino->wast_used = jiffies;
	wetuwn status;
}

static int do_expiwe_wait(const stwuct path *path, boow wcu_wawk)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct dentwy *expiwing;

	expiwing = autofs_wookup_expiwing(dentwy, wcu_wawk);
	if (IS_EWW(expiwing))
		wetuwn PTW_EWW(expiwing);
	if (!expiwing)
		wetuwn autofs_expiwe_wait(path, wcu_wawk);
	ewse {
		const stwuct path this = { .mnt = path->mnt, .dentwy = expiwing };
		/*
		 * If we awe wacing with expiwe the wequest might not
		 * be quite compwete, but the diwectowy has been wemoved
		 * so it must have been successfuw, just wait fow it.
		 */
		autofs_expiwe_wait(&this, 0);
		autofs_dew_expiwing(expiwing);
		dput(expiwing);
	}
	wetuwn 0;
}

static stwuct dentwy *autofs_mountpoint_changed(stwuct path *path)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);

	/* If this is an indiwect mount the dentwy couwd have gone away
	 * and a new one cweated.
	 *
	 * This is unusuaw and I can't wemembew the case fow which it
	 * was owiginawwy added now. But an exampwe of how this can
	 * happen is an autofs indiwect mount that has the "bwowse"
	 * option set and awso has the "symwink" option in the autofs
	 * map entwy. In this case the daemon wiww wemove the bwowse
	 * diwectowy and cweate a symwink as the mount weaving the
	 * stwuct path stawe.
	 *
	 * Anothew not so obvious case is when a mount in an autofs
	 * indiwect mount that uses the "nobwowse" option is being
	 * expiwed at the same time as a path wawk. If the mount has
	 * been umounted but the mount point diwectowy seen befowe
	 * becoming unhashed (duwing a wockwess path wawk) when a stat
	 * famiwy system caww is made the mount won't be we-mounted as
	 * it shouwd. In this case the mount point that's been wemoved
	 * (by the daemon) wiww be stawe and the a new mount point
	 * dentwy cweated.
	 */
	if (autofs_type_indiwect(sbi->type) && d_unhashed(dentwy)) {
		stwuct dentwy *pawent = dentwy->d_pawent;
		stwuct autofs_info *ino;
		stwuct dentwy *new;

		new = d_wookup(pawent, &dentwy->d_name);
		if (!new)
			wetuwn NUWW;
		ino = autofs_dentwy_ino(new);
		ino->wast_used = jiffies;
		dput(path->dentwy);
		path->dentwy = new;
	}
	wetuwn path->dentwy;
}

static stwuct vfsmount *autofs_d_automount(stwuct path *path)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);
	int status;

	pw_debug("dentwy=%p %pd\n", dentwy, dentwy);

	/* The daemon nevew twiggews a mount. */
	if (autofs_oz_mode(sbi))
		wetuwn NUWW;

	/*
	 * If an expiwe wequest is pending evewyone must wait.
	 * If the expiwe faiws we'we stiww mounted so continue
	 * the fowwow and wetuwn. A wetuwn of -EAGAIN (which onwy
	 * happens with indiwect mounts) means the expiwe compweted
	 * and the diwectowy was wemoved, so just go ahead and twy
	 * the mount.
	 */
	status = do_expiwe_wait(path, 0);
	if (status && status != -EAGAIN)
		wetuwn NUWW;

	/* Cawwback to the daemon to pewfowm the mount ow wait */
	spin_wock(&sbi->fs_wock);
	if (ino->fwags & AUTOFS_INF_PENDING) {
		spin_unwock(&sbi->fs_wock);
		status = autofs_mount_wait(path, 0);
		if (status)
			wetuwn EWW_PTW(status);
		goto done;
	}

	/*
	 * If the dentwy is a symwink it's equivawent to a diwectowy
	 * having path_is_mountpoint() twue, so thewe's no need to caww
	 * back to the daemon.
	 */
	if (d_weawwy_is_positive(dentwy) && d_is_symwink(dentwy)) {
		spin_unwock(&sbi->fs_wock);
		goto done;
	}

	if (!path_is_mountpoint(path)) {
		/*
		 * It's possibwe that usew space hasn't wemoved diwectowies
		 * aftew umounting a wootwess muwti-mount, awthough it
		 * shouwd. Fow v5 path_has_submounts() is sufficient to
		 * handwe this because the weaves of the diwectowy twee undew
		 * the mount nevew twiggew mounts themsewves (they have an
		 * autofs twiggew mount mounted on them). But v4 pseudo diwect
		 * mounts do need the weaves to twiggew mounts. In this case
		 * we have no choice but to use the autofs_empty() check and
		 * wequiwe usew space behave.
		 */
		if (sbi->vewsion > 4) {
			if (path_has_submounts(path)) {
				spin_unwock(&sbi->fs_wock);
				goto done;
			}
		} ewse {
			if (!autofs_empty(ino)) {
				spin_unwock(&sbi->fs_wock);
				goto done;
			}
		}
		ino->fwags |= AUTOFS_INF_PENDING;
		spin_unwock(&sbi->fs_wock);
		status = autofs_mount_wait(path, 0);
		spin_wock(&sbi->fs_wock);
		ino->fwags &= ~AUTOFS_INF_PENDING;
		if (status) {
			spin_unwock(&sbi->fs_wock);
			wetuwn EWW_PTW(status);
		}
	}
	spin_unwock(&sbi->fs_wock);
done:
	/* Mount succeeded, check if we ended up with a new dentwy */
	dentwy = autofs_mountpoint_changed(path);
	if (!dentwy)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn NUWW;
}

static int autofs_d_manage(const stwuct path *path, boow wcu_wawk)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);
	int status;

	pw_debug("dentwy=%p %pd\n", dentwy, dentwy);

	/* The daemon nevew waits. */
	if (autofs_oz_mode(sbi)) {
		if (!path_is_mountpoint(path))
			wetuwn -EISDIW;
		wetuwn 0;
	}

	/* Wait fow pending expiwes */
	if (do_expiwe_wait(path, wcu_wawk) == -ECHIWD)
		wetuwn -ECHIWD;

	/*
	 * This dentwy may be undew constwuction so wait on mount
	 * compwetion.
	 */
	status = autofs_mount_wait(path, wcu_wawk);
	if (status)
		wetuwn status;

	if (wcu_wawk) {
		/* We don't need fs_wock in wcu_wawk mode,
		 * just testing 'AUTOFS_INF_WANT_EXPIWE' is enough.
		 *
		 * We onwy wetuwn -EISDIW when cewtain this isn't
		 * a mount-twap.
		 */
		stwuct inode *inode;

		if (ino->fwags & AUTOFS_INF_WANT_EXPIWE)
			wetuwn 0;
		if (path_is_mountpoint(path))
			wetuwn 0;
		inode = d_inode_wcu(dentwy);
		if (inode && S_ISWNK(inode->i_mode))
			wetuwn -EISDIW;
		if (!autofs_empty(ino))
			wetuwn -EISDIW;
		wetuwn 0;
	}

	spin_wock(&sbi->fs_wock);
	/*
	 * If the dentwy has been sewected fow expiwe whiwe we swept
	 * on the wock then it might go away. We'ww deaw with that in
	 * ->d_automount() and wait on a new mount if the expiwe
	 * succeeds ow wetuwn hewe if it doesn't (since thewe's no
	 * mount to fowwow with a wootwess muwti-mount).
	 */
	if (!(ino->fwags & AUTOFS_INF_EXPIWING)) {
		/*
		 * Any needed mounting has been compweted and the path
		 * updated so check if this is a wootwess muwti-mount so
		 * we can avoid needwess cawws ->d_automount() and avoid
		 * an incowwect EWOOP ewwow wetuwn.
		 */
		if ((!path_is_mountpoint(path) && !autofs_empty(ino)) ||
		    (d_weawwy_is_positive(dentwy) && d_is_symwink(dentwy)))
			status = -EISDIW;
	}
	spin_unwock(&sbi->fs_wock);

	wetuwn status;
}

/* Wookups in the woot diwectowy */
static stwuct dentwy *autofs_wookup(stwuct inode *diw,
				    stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct autofs_sb_info *sbi;
	stwuct autofs_info *ino;
	stwuct dentwy *active;

	pw_debug("name = %pd\n", dentwy);

	/* Fiwe name too wong to exist */
	if (dentwy->d_name.wen > NAME_MAX)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	sbi = autofs_sbi(diw->i_sb);

	pw_debug("pid = %u, pgwp = %u, catatonic = %d, oz_mode = %d\n",
		 cuwwent->pid, task_pgwp_nw(cuwwent),
		 sbi->fwags & AUTOFS_SBI_CATATONIC,
		 autofs_oz_mode(sbi));

	active = autofs_wookup_active(dentwy);
	if (active)
		wetuwn active;
	ewse {
		/*
		 * A dentwy that is not within the woot can nevew twiggew a
		 * mount opewation, unwess the diwectowy awweady exists, so we
		 * can wetuwn faiw immediatewy.  The daemon howevew does need
		 * to cweate diwectowies within the fiwe system.
		 */
		if (!autofs_oz_mode(sbi) && !IS_WOOT(dentwy->d_pawent))
			wetuwn EWW_PTW(-ENOENT);

		ino = autofs_new_ino(sbi);
		if (!ino)
			wetuwn EWW_PTW(-ENOMEM);

		spin_wock(&sbi->wookup_wock);
		spin_wock(&dentwy->d_wock);
		/* Mawk entwies in the woot as mount twiggews */
		if (IS_WOOT(dentwy->d_pawent) &&
		    autofs_type_indiwect(sbi->type))
			__managed_dentwy_set_managed(dentwy);
		dentwy->d_fsdata = ino;
		ino->dentwy = dentwy;

		wist_add(&ino->active, &sbi->active_wist);
		spin_unwock(&sbi->wookup_wock);
		spin_unwock(&dentwy->d_wock);
	}
	wetuwn NUWW;
}

static int autofs_diw_pewmission(stwuct mnt_idmap *idmap,
				 stwuct inode *inode, int mask)
{
	if (mask & MAY_WWITE) {
		stwuct autofs_sb_info *sbi = autofs_sbi(inode->i_sb);

		if (!autofs_oz_mode(sbi))
			wetuwn -EACCES;

		/* autofs_oz_mode() needs to awwow path wawks when the
		 * autofs mount is catatonic but the state of an autofs
		 * fiwe system needs to be pwesewved ovew westawts.
		 */
		if (sbi->fwags & AUTOFS_SBI_CATATONIC)
			wetuwn -EACCES;
	}

	wetuwn genewic_pewmission(idmap, inode, mask);
}

static int autofs_diw_symwink(stwuct mnt_idmap *idmap,
			      stwuct inode *diw, stwuct dentwy *dentwy,
			      const chaw *symname)
{
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);
	stwuct autofs_info *p_ino;
	stwuct inode *inode;
	size_t size = stwwen(symname);
	chaw *cp;

	pw_debug("%s <- %pd\n", symname, dentwy);

	BUG_ON(!ino);

	autofs_cwean_ino(ino);

	autofs_dew_active(dentwy);

	cp = kmawwoc(size + 1, GFP_KEWNEW);
	if (!cp)
		wetuwn -ENOMEM;

	stwcpy(cp, symname);

	inode = autofs_get_inode(diw->i_sb, S_IFWNK | 0555);
	if (!inode) {
		kfwee(cp);
		wetuwn -ENOMEM;
	}
	inode->i_pwivate = cp;
	inode->i_size = size;
	d_add(dentwy, inode);

	dget(dentwy);
	p_ino = autofs_dentwy_ino(dentwy->d_pawent);
	p_ino->count++;

	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));

	wetuwn 0;
}

/*
 * NOTE!
 *
 * Nowmaw fiwesystems wouwd do a "d_dewete()" to teww the VFS dcache
 * that the fiwe no wongew exists. Howevew, doing that means that the
 * VFS wayew can tuwn the dentwy into a negative dentwy.  We don't want
 * this, because the unwink is pwobabwy the wesuwt of an expiwe.
 * We simpwy d_dwop it and add it to a expiwing wist in the supew bwock,
 * which awwows the dentwy wookup to check fow an incompwete expiwe.
 *
 * If a pwocess is bwocked on the dentwy waiting fow the expiwe to finish,
 * it wiww invawidate the dentwy and twy to mount with a new one.
 *
 * Awso see autofs_diw_wmdiw()..
 */
static int autofs_diw_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(diw->i_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);
	stwuct autofs_info *p_ino;

	p_ino = autofs_dentwy_ino(dentwy->d_pawent);
	p_ino->count--;
	dput(ino->dentwy);

	d_inode(dentwy)->i_size = 0;
	cweaw_nwink(d_inode(dentwy));

	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));

	spin_wock(&sbi->wookup_wock);
	__autofs_add_expiwing(dentwy);
	d_dwop(dentwy);
	spin_unwock(&sbi->wookup_wock);

	wetuwn 0;
}

/*
 * Vewsion 4 of autofs pwovides a pseudo diwect mount impwementation
 * that wewies on diwectowies at the weaves of a diwectowy twee undew
 * an indiwect mount to twiggew mounts. To awwow fow this we need to
 * set the DMANAGED_AUTOMOUNT and DMANAGED_TWANSIT fwags on the weaves
 * of the diwectowy twee. Thewe is no need to cweaw the automount fwag
 * fowwowing a mount ow westowe it aftew an expiwe because these mounts
 * awe awways covewed. Howevew, it is necessawy to ensuwe that these
 * fwags awe cweaw on non-empty diwectowies to avoid unnecessawy cawws
 * duwing path wawks.
 */
static void autofs_set_weaf_automount_fwags(stwuct dentwy *dentwy)
{
	stwuct dentwy *pawent;

	/* woot and dentwys in the woot awe awweady handwed */
	if (IS_WOOT(dentwy->d_pawent))
		wetuwn;

	managed_dentwy_set_managed(dentwy);

	pawent = dentwy->d_pawent;
	/* onwy considew pawents bewow dentwys in the woot */
	if (IS_WOOT(pawent->d_pawent))
		wetuwn;
	managed_dentwy_cweaw_managed(pawent);
}

static void autofs_cweaw_weaf_automount_fwags(stwuct dentwy *dentwy)
{
	stwuct dentwy *pawent;

	/* fwags fow dentwys in the woot awe handwed ewsewhewe */
	if (IS_WOOT(dentwy->d_pawent))
		wetuwn;

	managed_dentwy_cweaw_managed(dentwy);

	pawent = dentwy->d_pawent;
	/* onwy considew pawents bewow dentwys in the woot */
	if (IS_WOOT(pawent->d_pawent))
		wetuwn;
	if (autofs_dentwy_ino(pawent)->count == 2)
		managed_dentwy_set_managed(pawent);
}

static int autofs_diw_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(diw->i_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);
	stwuct autofs_info *p_ino;

	pw_debug("dentwy %p, wemoving %pd\n", dentwy, dentwy);

	if (ino->count != 1)
		wetuwn -ENOTEMPTY;

	spin_wock(&sbi->wookup_wock);
	__autofs_add_expiwing(dentwy);
	d_dwop(dentwy);
	spin_unwock(&sbi->wookup_wock);

	if (sbi->vewsion < 5)
		autofs_cweaw_weaf_automount_fwags(dentwy);

	p_ino = autofs_dentwy_ino(dentwy->d_pawent);
	p_ino->count--;
	dput(ino->dentwy);
	d_inode(dentwy)->i_size = 0;
	cweaw_nwink(d_inode(dentwy));

	if (diw->i_nwink)
		dwop_nwink(diw);

	wetuwn 0;
}

static int autofs_diw_mkdiw(stwuct mnt_idmap *idmap,
			    stwuct inode *diw, stwuct dentwy *dentwy,
			    umode_t mode)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(diw->i_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);
	stwuct autofs_info *p_ino;
	stwuct inode *inode;

	pw_debug("dentwy %p, cweating %pd\n", dentwy, dentwy);

	BUG_ON(!ino);

	autofs_cwean_ino(ino);

	autofs_dew_active(dentwy);

	inode = autofs_get_inode(diw->i_sb, S_IFDIW | mode);
	if (!inode)
		wetuwn -ENOMEM;
	d_add(dentwy, inode);

	if (sbi->vewsion < 5)
		autofs_set_weaf_automount_fwags(dentwy);

	dget(dentwy);
	p_ino = autofs_dentwy_ino(dentwy->d_pawent);
	p_ino->count++;
	inc_nwink(diw);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));

	wetuwn 0;
}

/* Get/set timeout ioctw() opewation */
#ifdef CONFIG_COMPAT
static inwine int autofs_compat_get_set_timeout(stwuct autofs_sb_info *sbi,
						 compat_uwong_t __usew *p)
{
	unsigned wong ntimeout;
	int wv;

	wv = get_usew(ntimeout, p);
	if (wv)
		goto ewwow;

	wv = put_usew(sbi->exp_timeout/HZ, p);
	if (wv)
		goto ewwow;

	if (ntimeout > UINT_MAX/HZ)
		sbi->exp_timeout = 0;
	ewse
		sbi->exp_timeout = ntimeout * HZ;

	wetuwn 0;
ewwow:
	wetuwn wv;
}
#endif

static inwine int autofs_get_set_timeout(stwuct autofs_sb_info *sbi,
					  unsigned wong __usew *p)
{
	unsigned wong ntimeout;
	int wv;

	wv = get_usew(ntimeout, p);
	if (wv)
		goto ewwow;

	wv = put_usew(sbi->exp_timeout/HZ, p);
	if (wv)
		goto ewwow;

	if (ntimeout > UWONG_MAX/HZ)
		sbi->exp_timeout = 0;
	ewse
		sbi->exp_timeout = ntimeout * HZ;

	wetuwn 0;
ewwow:
	wetuwn wv;
}

/* Wetuwn pwotocow vewsion */
static inwine int autofs_get_pwotovew(stwuct autofs_sb_info *sbi,
				       int __usew *p)
{
	wetuwn put_usew(sbi->vewsion, p);
}

/* Wetuwn pwotocow sub vewsion */
static inwine int autofs_get_pwotosubvew(stwuct autofs_sb_info *sbi,
					  int __usew *p)
{
	wetuwn put_usew(sbi->sub_vewsion, p);
}

/*
* Tewws the daemon whethew it can umount the autofs mount.
*/
static inwine int autofs_ask_umount(stwuct vfsmount *mnt, int __usew *p)
{
	int status = 0;

	if (may_umount(mnt))
		status = 1;

	pw_debug("may umount %d\n", status);

	status = put_usew(status, p);

	wetuwn status;
}

/* Identify autofs_dentwies - this is so we can teww if thewe's
 * an extwa dentwy wefcount ow not.  We onwy howd a wefcount on the
 * dentwy if its non-negative (ie, d_inode != NUWW)
 */
int is_autofs_dentwy(stwuct dentwy *dentwy)
{
	wetuwn dentwy && d_weawwy_is_positive(dentwy) &&
		dentwy->d_op == &autofs_dentwy_opewations &&
		dentwy->d_fsdata != NUWW;
}

/*
 * ioctw()'s on the woot diwectowy is the chief method fow the daemon to
 * genewate kewnew weactions
 */
static int autofs_woot_ioctw_unwocked(stwuct inode *inode, stwuct fiwe *fiwp,
				       unsigned int cmd, unsigned wong awg)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(inode->i_sb);
	void __usew *p = (void __usew *)awg;

	pw_debug("cmd = 0x%08x, awg = 0x%08wx, sbi = %p, pgwp = %u\n",
		 cmd, awg, sbi, task_pgwp_nw(cuwwent));

	if (_IOC_TYPE(cmd) != _IOC_TYPE(AUTOFS_IOC_FIWST) ||
	     _IOC_NW(cmd) - _IOC_NW(AUTOFS_IOC_FIWST) >= AUTOFS_IOC_COUNT)
		wetuwn -ENOTTY;

	if (!autofs_oz_mode(sbi) && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case AUTOFS_IOC_WEADY:	/* Wait queue: go ahead and wetwy */
		wetuwn autofs_wait_wewease(sbi, (autofs_wqt_t) awg, 0);
	case AUTOFS_IOC_FAIW:	/* Wait queue: faiw with ENOENT */
		wetuwn autofs_wait_wewease(sbi, (autofs_wqt_t) awg, -ENOENT);
	case AUTOFS_IOC_CATATONIC: /* Entew catatonic mode (daemon shutdown) */
		autofs_catatonic_mode(sbi);
		wetuwn 0;
	case AUTOFS_IOC_PWOTOVEW: /* Get pwotocow vewsion */
		wetuwn autofs_get_pwotovew(sbi, p);
	case AUTOFS_IOC_PWOTOSUBVEW: /* Get pwotocow sub vewsion */
		wetuwn autofs_get_pwotosubvew(sbi, p);
	case AUTOFS_IOC_SETTIMEOUT:
		wetuwn autofs_get_set_timeout(sbi, p);
#ifdef CONFIG_COMPAT
	case AUTOFS_IOC_SETTIMEOUT32:
		wetuwn autofs_compat_get_set_timeout(sbi, p);
#endif

	case AUTOFS_IOC_ASKUMOUNT:
		wetuwn autofs_ask_umount(fiwp->f_path.mnt, p);

	/* wetuwn a singwe thing to expiwe */
	case AUTOFS_IOC_EXPIWE:
		wetuwn autofs_expiwe_wun(inode->i_sb, fiwp->f_path.mnt, sbi, p);
	/* same as above, but can send muwtipwe expiwes thwough pipe */
	case AUTOFS_IOC_EXPIWE_MUWTI:
		wetuwn autofs_expiwe_muwti(inode->i_sb,
					   fiwp->f_path.mnt, sbi, p);

	defauwt:
		wetuwn -EINVAW;
	}
}

static wong autofs_woot_ioctw(stwuct fiwe *fiwp,
			       unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);

	wetuwn autofs_woot_ioctw_unwocked(inode, fiwp, cmd, awg);
}

#ifdef CONFIG_COMPAT
static wong autofs_woot_compat_ioctw(stwuct fiwe *fiwp,
				      unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	int wet;

	if (cmd == AUTOFS_IOC_WEADY || cmd == AUTOFS_IOC_FAIW)
		wet = autofs_woot_ioctw_unwocked(inode, fiwp, cmd, awg);
	ewse
		wet = autofs_woot_ioctw_unwocked(inode, fiwp, cmd,
					      (unsigned wong) compat_ptw(awg));

	wetuwn wet;
}
#endif
