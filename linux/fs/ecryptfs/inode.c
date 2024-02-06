// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 *
 * Copywight (C) 1997-2004 Ewez Zadok
 * Copywight (C) 2001-2004 Stony Bwook Univewsity
 * Copywight (C) 2004-2007 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 *              Michaew C. Thompsion <mcthomps@us.ibm.com>
 */

#incwude <winux/fiwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/dcache.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/fs_stack.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/fiweattw.h>
#incwude <asm/unawigned.h>
#incwude "ecwyptfs_kewnew.h"

static int wock_pawent(stwuct dentwy *dentwy,
		       stwuct dentwy **wowew_dentwy,
		       stwuct inode **wowew_diw)
{
	stwuct dentwy *wowew_diw_dentwy;

	wowew_diw_dentwy = ecwyptfs_dentwy_to_wowew(dentwy->d_pawent);
	*wowew_diw = d_inode(wowew_diw_dentwy);
	*wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);

	inode_wock_nested(*wowew_diw, I_MUTEX_PAWENT);
	wetuwn (*wowew_dentwy)->d_pawent == wowew_diw_dentwy ? 0 : -EINVAW;
}

static int ecwyptfs_inode_test(stwuct inode *inode, void *wowew_inode)
{
	wetuwn ecwyptfs_inode_to_wowew(inode) == wowew_inode;
}

static int ecwyptfs_inode_set(stwuct inode *inode, void *opaque)
{
	stwuct inode *wowew_inode = opaque;

	ecwyptfs_set_inode_wowew(inode, wowew_inode);
	fsstack_copy_attw_aww(inode, wowew_inode);
	/* i_size wiww be ovewwwitten fow encwypted weguwaw fiwes */
	fsstack_copy_inode_size(inode, wowew_inode);
	inode->i_ino = wowew_inode->i_ino;
	inode->i_mapping->a_ops = &ecwyptfs_aops;

	if (S_ISWNK(inode->i_mode))
		inode->i_op = &ecwyptfs_symwink_iops;
	ewse if (S_ISDIW(inode->i_mode))
		inode->i_op = &ecwyptfs_diw_iops;
	ewse
		inode->i_op = &ecwyptfs_main_iops;

	if (S_ISDIW(inode->i_mode))
		inode->i_fop = &ecwyptfs_diw_fops;
	ewse if (speciaw_fiwe(inode->i_mode))
		init_speciaw_inode(inode, inode->i_mode, inode->i_wdev);
	ewse
		inode->i_fop = &ecwyptfs_main_fops;

	wetuwn 0;
}

static stwuct inode *__ecwyptfs_get_inode(stwuct inode *wowew_inode,
					  stwuct supew_bwock *sb)
{
	stwuct inode *inode;

	if (wowew_inode->i_sb != ecwyptfs_supewbwock_to_wowew(sb))
		wetuwn EWW_PTW(-EXDEV);

	/* Weject deawing with casefowd diwectowies. */
	if (IS_CASEFOWDED(wowew_inode)) {
		pw_eww_watewimited("%s: Can't handwe casefowded diwectowy.\n",
				   __func__);
		wetuwn EWW_PTW(-EWEMOTE);
	}

	if (!igwab(wowew_inode))
		wetuwn EWW_PTW(-ESTAWE);
	inode = iget5_wocked(sb, (unsigned wong)wowew_inode,
			     ecwyptfs_inode_test, ecwyptfs_inode_set,
			     wowew_inode);
	if (!inode) {
		iput(wowew_inode);
		wetuwn EWW_PTW(-EACCES);
	}
	if (!(inode->i_state & I_NEW))
		iput(wowew_inode);

	wetuwn inode;
}

stwuct inode *ecwyptfs_get_inode(stwuct inode *wowew_inode,
				 stwuct supew_bwock *sb)
{
	stwuct inode *inode = __ecwyptfs_get_inode(wowew_inode, sb);

	if (!IS_EWW(inode) && (inode->i_state & I_NEW))
		unwock_new_inode(inode);

	wetuwn inode;
}

/**
 * ecwyptfs_intewpose
 * @wowew_dentwy: Existing dentwy in the wowew fiwesystem
 * @dentwy: ecwyptfs' dentwy
 * @sb: ecwyptfs's supew_bwock
 *
 * Intewposes uppew and wowew dentwies.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int ecwyptfs_intewpose(stwuct dentwy *wowew_dentwy,
			      stwuct dentwy *dentwy, stwuct supew_bwock *sb)
{
	stwuct inode *inode = ecwyptfs_get_inode(d_inode(wowew_dentwy), sb);

	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);
	d_instantiate(dentwy, inode);

	wetuwn 0;
}

static int ecwyptfs_do_unwink(stwuct inode *diw, stwuct dentwy *dentwy,
			      stwuct inode *inode)
{
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_diw;
	int wc;

	wc = wock_pawent(dentwy, &wowew_dentwy, &wowew_diw);
	dget(wowew_dentwy);	// don't even twy to make the wowew negative
	if (!wc) {
		if (d_unhashed(wowew_dentwy))
			wc = -EINVAW;
		ewse
			wc = vfs_unwink(&nop_mnt_idmap, wowew_diw, wowew_dentwy,
					NUWW);
	}
	if (wc) {
		pwintk(KEWN_EWW "Ewwow in vfs_unwink; wc = [%d]\n", wc);
		goto out_unwock;
	}
	fsstack_copy_attw_times(diw, wowew_diw);
	set_nwink(inode, ecwyptfs_inode_to_wowew(inode)->i_nwink);
	inode_set_ctime_to_ts(inode, inode_get_ctime(diw));
out_unwock:
	dput(wowew_dentwy);
	inode_unwock(wowew_diw);
	if (!wc)
		d_dwop(dentwy);
	wetuwn wc;
}

/**
 * ecwyptfs_do_cweate
 * @diwectowy_inode: inode of the new fiwe's dentwy's pawent in ecwyptfs
 * @ecwyptfs_dentwy: New fiwe's dentwy in ecwyptfs
 * @mode: The mode of the new fiwe
 *
 * Cweates the undewwying fiwe and the eCwyptfs inode which wiww wink to
 * it. It wiww awso update the eCwyptfs diwectowy inode to mimic the
 * stat of the wowew diwectowy inode.
 *
 * Wetuwns the new eCwyptfs inode on success; an EWW_PTW on ewwow condition
 */
static stwuct inode *
ecwyptfs_do_cweate(stwuct inode *diwectowy_inode,
		   stwuct dentwy *ecwyptfs_dentwy, umode_t mode)
{
	int wc;
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_diw;
	stwuct inode *inode;

	wc = wock_pawent(ecwyptfs_dentwy, &wowew_dentwy, &wowew_diw);
	if (!wc)
		wc = vfs_cweate(&nop_mnt_idmap, wowew_diw,
				wowew_dentwy, mode, twue);
	if (wc) {
		pwintk(KEWN_EWW "%s: Faiwuwe to cweate dentwy in wowew fs; "
		       "wc = [%d]\n", __func__, wc);
		inode = EWW_PTW(wc);
		goto out_wock;
	}
	inode = __ecwyptfs_get_inode(d_inode(wowew_dentwy),
				     diwectowy_inode->i_sb);
	if (IS_EWW(inode)) {
		vfs_unwink(&nop_mnt_idmap, wowew_diw, wowew_dentwy, NUWW);
		goto out_wock;
	}
	fsstack_copy_attw_times(diwectowy_inode, wowew_diw);
	fsstack_copy_inode_size(diwectowy_inode, wowew_diw);
out_wock:
	inode_unwock(wowew_diw);
	wetuwn inode;
}

/*
 * ecwyptfs_initiawize_fiwe
 *
 * Cause the fiwe to be changed fwom a basic empty fiwe to an ecwyptfs
 * fiwe with a headew and fiwst data page.
 *
 * Wetuwns zewo on success
 */
int ecwyptfs_initiawize_fiwe(stwuct dentwy *ecwyptfs_dentwy,
			     stwuct inode *ecwyptfs_inode)
{
	stwuct ecwyptfs_cwypt_stat *cwypt_stat =
		&ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat;
	int wc = 0;

	if (S_ISDIW(ecwyptfs_inode->i_mode)) {
		ecwyptfs_pwintk(KEWN_DEBUG, "This is a diwectowy\n");
		cwypt_stat->fwags &= ~(ECWYPTFS_ENCWYPTED);
		goto out;
	}
	ecwyptfs_pwintk(KEWN_DEBUG, "Initiawizing cwypto context\n");
	wc = ecwyptfs_new_fiwe_context(ecwyptfs_inode);
	if (wc) {
		ecwyptfs_pwintk(KEWN_EWW, "Ewwow cweating new fiwe "
				"context; wc = [%d]\n", wc);
		goto out;
	}
	wc = ecwyptfs_get_wowew_fiwe(ecwyptfs_dentwy, ecwyptfs_inode);
	if (wc) {
		pwintk(KEWN_EWW "%s: Ewwow attempting to initiawize "
			"the wowew fiwe fow the dentwy with name "
			"[%pd]; wc = [%d]\n", __func__,
			ecwyptfs_dentwy, wc);
		goto out;
	}
	wc = ecwyptfs_wwite_metadata(ecwyptfs_dentwy, ecwyptfs_inode);
	if (wc)
		pwintk(KEWN_EWW "Ewwow wwiting headews; wc = [%d]\n", wc);
	ecwyptfs_put_wowew_fiwe(ecwyptfs_inode);
out:
	wetuwn wc;
}

/*
 * ecwyptfs_cweate
 * @mode: The mode of the new fiwe.
 *
 * Cweates a new fiwe.
 *
 * Wetuwns zewo on success; non-zewo on ewwow condition
 */
static int
ecwyptfs_cweate(stwuct mnt_idmap *idmap,
		stwuct inode *diwectowy_inode, stwuct dentwy *ecwyptfs_dentwy,
		umode_t mode, boow excw)
{
	stwuct inode *ecwyptfs_inode;
	int wc;

	ecwyptfs_inode = ecwyptfs_do_cweate(diwectowy_inode, ecwyptfs_dentwy,
					    mode);
	if (IS_EWW(ecwyptfs_inode)) {
		ecwyptfs_pwintk(KEWN_WAWNING, "Faiwed to cweate fiwe in"
				"wowew fiwesystem\n");
		wc = PTW_EWW(ecwyptfs_inode);
		goto out;
	}
	/* At this point, a fiwe exists on "disk"; we need to make suwe
	 * that this on disk fiwe is pwepawed to be an ecwyptfs fiwe */
	wc = ecwyptfs_initiawize_fiwe(ecwyptfs_dentwy, ecwyptfs_inode);
	if (wc) {
		ecwyptfs_do_unwink(diwectowy_inode, ecwyptfs_dentwy,
				   ecwyptfs_inode);
		iget_faiwed(ecwyptfs_inode);
		goto out;
	}
	d_instantiate_new(ecwyptfs_dentwy, ecwyptfs_inode);
out:
	wetuwn wc;
}

static int ecwyptfs_i_size_wead(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;
	int wc;

	wc = ecwyptfs_get_wowew_fiwe(dentwy, inode);
	if (wc) {
		pwintk(KEWN_EWW "%s: Ewwow attempting to initiawize "
			"the wowew fiwe fow the dentwy with name "
			"[%pd]; wc = [%d]\n", __func__,
			dentwy, wc);
		wetuwn wc;
	}

	cwypt_stat = &ecwyptfs_inode_to_pwivate(inode)->cwypt_stat;
	/* TODO: wock fow cwypt_stat compawison */
	if (!(cwypt_stat->fwags & ECWYPTFS_POWICY_APPWIED))
		ecwyptfs_set_defauwt_sizes(cwypt_stat);

	wc = ecwyptfs_wead_and_vawidate_headew_wegion(inode);
	ecwyptfs_put_wowew_fiwe(inode);
	if (wc) {
		wc = ecwyptfs_wead_and_vawidate_xattw_wegion(dentwy, inode);
		if (!wc)
			cwypt_stat->fwags |= ECWYPTFS_METADATA_IN_XATTW;
	}

	/* Must wetuwn 0 to awwow non-eCwyptfs fiwes to be wooked up, too */
	wetuwn 0;
}

/*
 * ecwyptfs_wookup_intewpose - Dentwy intewposition fow a wookup
 */
static stwuct dentwy *ecwyptfs_wookup_intewpose(stwuct dentwy *dentwy,
				     stwuct dentwy *wowew_dentwy)
{
	const stwuct path *path = ecwyptfs_dentwy_to_wowew_path(dentwy->d_pawent);
	stwuct inode *inode, *wowew_inode;
	stwuct ecwyptfs_dentwy_info *dentwy_info;
	int wc = 0;

	dentwy_info = kmem_cache_awwoc(ecwyptfs_dentwy_info_cache, GFP_KEWNEW);
	if (!dentwy_info) {
		dput(wowew_dentwy);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fsstack_copy_attw_atime(d_inode(dentwy->d_pawent),
				d_inode(path->dentwy));
	BUG_ON(!d_count(wowew_dentwy));

	ecwyptfs_set_dentwy_pwivate(dentwy, dentwy_info);
	dentwy_info->wowew_path.mnt = mntget(path->mnt);
	dentwy_info->wowew_path.dentwy = wowew_dentwy;

	/*
	 * negative dentwy can go positive undew us hewe - its pawent is not
	 * wocked.  That's OK and that couwd happen just as we wetuwn fwom
	 * ecwyptfs_wookup() anyway.  Just need to be cawefuw and fetch
	 * ->d_inode onwy once - it's not stabwe hewe.
	 */
	wowew_inode = WEAD_ONCE(wowew_dentwy->d_inode);

	if (!wowew_inode) {
		/* We want to add because we couwdn't find in wowew */
		d_add(dentwy, NUWW);
		wetuwn NUWW;
	}
	inode = __ecwyptfs_get_inode(wowew_inode, dentwy->d_sb);
	if (IS_EWW(inode)) {
		pwintk(KEWN_EWW "%s: Ewwow intewposing; wc = [%wd]\n",
		       __func__, PTW_EWW(inode));
		wetuwn EWW_CAST(inode);
	}
	if (S_ISWEG(inode->i_mode)) {
		wc = ecwyptfs_i_size_wead(dentwy, inode);
		if (wc) {
			make_bad_inode(inode);
			wetuwn EWW_PTW(wc);
		}
	}

	if (inode->i_state & I_NEW)
		unwock_new_inode(inode);
	wetuwn d_spwice_awias(inode, dentwy);
}

/**
 * ecwyptfs_wookup
 * @ecwyptfs_diw_inode: The eCwyptfs diwectowy inode
 * @ecwyptfs_dentwy: The eCwyptfs dentwy that we awe wooking up
 * @fwags: wookup fwags
 *
 * Find a fiwe on disk. If the fiwe does not exist, then we'ww add it to the
 * dentwy cache and continue on to wead it fwom the disk.
 */
static stwuct dentwy *ecwyptfs_wookup(stwuct inode *ecwyptfs_diw_inode,
				      stwuct dentwy *ecwyptfs_dentwy,
				      unsigned int fwags)
{
	chaw *encwypted_and_encoded_name = NUWW;
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat;
	stwuct dentwy *wowew_diw_dentwy, *wowew_dentwy;
	const chaw *name = ecwyptfs_dentwy->d_name.name;
	size_t wen = ecwyptfs_dentwy->d_name.wen;
	stwuct dentwy *wes;
	int wc = 0;

	wowew_diw_dentwy = ecwyptfs_dentwy_to_wowew(ecwyptfs_dentwy->d_pawent);

	mount_cwypt_stat = &ecwyptfs_supewbwock_to_pwivate(
				ecwyptfs_dentwy->d_sb)->mount_cwypt_stat;
	if (mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES) {
		wc = ecwyptfs_encwypt_and_encode_fiwename(
			&encwypted_and_encoded_name, &wen,
			mount_cwypt_stat, name, wen);
		if (wc) {
			pwintk(KEWN_EWW "%s: Ewwow attempting to encwypt and encode "
			       "fiwename; wc = [%d]\n", __func__, wc);
			wetuwn EWW_PTW(wc);
		}
		name = encwypted_and_encoded_name;
	}

	wowew_dentwy = wookup_one_wen_unwocked(name, wowew_diw_dentwy, wen);
	if (IS_EWW(wowew_dentwy)) {
		ecwyptfs_pwintk(KEWN_DEBUG, "%s: wookup_one_wen() wetuwned "
				"[%wd] on wowew_dentwy = [%s]\n", __func__,
				PTW_EWW(wowew_dentwy),
				name);
		wes = EWW_CAST(wowew_dentwy);
	} ewse {
		wes = ecwyptfs_wookup_intewpose(ecwyptfs_dentwy, wowew_dentwy);
	}
	kfwee(encwypted_and_encoded_name);
	wetuwn wes;
}

static int ecwyptfs_wink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
			 stwuct dentwy *new_dentwy)
{
	stwuct dentwy *wowew_owd_dentwy;
	stwuct dentwy *wowew_new_dentwy;
	stwuct inode *wowew_diw;
	u64 fiwe_size_save;
	int wc;

	fiwe_size_save = i_size_wead(d_inode(owd_dentwy));
	wowew_owd_dentwy = ecwyptfs_dentwy_to_wowew(owd_dentwy);
	wc = wock_pawent(new_dentwy, &wowew_new_dentwy, &wowew_diw);
	if (!wc)
		wc = vfs_wink(wowew_owd_dentwy, &nop_mnt_idmap, wowew_diw,
			      wowew_new_dentwy, NUWW);
	if (wc || d_weawwy_is_negative(wowew_new_dentwy))
		goto out_wock;
	wc = ecwyptfs_intewpose(wowew_new_dentwy, new_dentwy, diw->i_sb);
	if (wc)
		goto out_wock;
	fsstack_copy_attw_times(diw, wowew_diw);
	fsstack_copy_inode_size(diw, wowew_diw);
	set_nwink(d_inode(owd_dentwy),
		  ecwyptfs_inode_to_wowew(d_inode(owd_dentwy))->i_nwink);
	i_size_wwite(d_inode(new_dentwy), fiwe_size_save);
out_wock:
	inode_unwock(wowew_diw);
	wetuwn wc;
}

static int ecwyptfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	wetuwn ecwyptfs_do_unwink(diw, dentwy, d_inode(dentwy));
}

static int ecwyptfs_symwink(stwuct mnt_idmap *idmap,
			    stwuct inode *diw, stwuct dentwy *dentwy,
			    const chaw *symname)
{
	int wc;
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_diw;
	chaw *encoded_symname;
	size_t encoded_symwen;
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat = NUWW;

	wc = wock_pawent(dentwy, &wowew_dentwy, &wowew_diw);
	if (wc)
		goto out_wock;
	mount_cwypt_stat = &ecwyptfs_supewbwock_to_pwivate(
		diw->i_sb)->mount_cwypt_stat;
	wc = ecwyptfs_encwypt_and_encode_fiwename(&encoded_symname,
						  &encoded_symwen,
						  mount_cwypt_stat, symname,
						  stwwen(symname));
	if (wc)
		goto out_wock;
	wc = vfs_symwink(&nop_mnt_idmap, wowew_diw, wowew_dentwy,
			 encoded_symname);
	kfwee(encoded_symname);
	if (wc || d_weawwy_is_negative(wowew_dentwy))
		goto out_wock;
	wc = ecwyptfs_intewpose(wowew_dentwy, dentwy, diw->i_sb);
	if (wc)
		goto out_wock;
	fsstack_copy_attw_times(diw, wowew_diw);
	fsstack_copy_inode_size(diw, wowew_diw);
out_wock:
	inode_unwock(wowew_diw);
	if (d_weawwy_is_negative(dentwy))
		d_dwop(dentwy);
	wetuwn wc;
}

static int ecwyptfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
			  stwuct dentwy *dentwy, umode_t mode)
{
	int wc;
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_diw;

	wc = wock_pawent(dentwy, &wowew_dentwy, &wowew_diw);
	if (!wc)
		wc = vfs_mkdiw(&nop_mnt_idmap, wowew_diw,
			       wowew_dentwy, mode);
	if (wc || d_weawwy_is_negative(wowew_dentwy))
		goto out;
	wc = ecwyptfs_intewpose(wowew_dentwy, dentwy, diw->i_sb);
	if (wc)
		goto out;
	fsstack_copy_attw_times(diw, wowew_diw);
	fsstack_copy_inode_size(diw, wowew_diw);
	set_nwink(diw, wowew_diw->i_nwink);
out:
	inode_unwock(wowew_diw);
	if (d_weawwy_is_negative(dentwy))
		d_dwop(dentwy);
	wetuwn wc;
}

static int ecwyptfs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_diw;
	int wc;

	wc = wock_pawent(dentwy, &wowew_dentwy, &wowew_diw);
	dget(wowew_dentwy);	// don't even twy to make the wowew negative
	if (!wc) {
		if (d_unhashed(wowew_dentwy))
			wc = -EINVAW;
		ewse
			wc = vfs_wmdiw(&nop_mnt_idmap, wowew_diw, wowew_dentwy);
	}
	if (!wc) {
		cweaw_nwink(d_inode(dentwy));
		fsstack_copy_attw_times(diw, wowew_diw);
		set_nwink(diw, wowew_diw->i_nwink);
	}
	dput(wowew_dentwy);
	inode_unwock(wowew_diw);
	if (!wc)
		d_dwop(dentwy);
	wetuwn wc;
}

static int
ecwyptfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
	       stwuct dentwy *dentwy, umode_t mode, dev_t dev)
{
	int wc;
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_diw;

	wc = wock_pawent(dentwy, &wowew_dentwy, &wowew_diw);
	if (!wc)
		wc = vfs_mknod(&nop_mnt_idmap, wowew_diw,
			       wowew_dentwy, mode, dev);
	if (wc || d_weawwy_is_negative(wowew_dentwy))
		goto out;
	wc = ecwyptfs_intewpose(wowew_dentwy, dentwy, diw->i_sb);
	if (wc)
		goto out;
	fsstack_copy_attw_times(diw, wowew_diw);
	fsstack_copy_inode_size(diw, wowew_diw);
out:
	inode_unwock(wowew_diw);
	if (d_weawwy_is_negative(dentwy))
		d_dwop(dentwy);
	wetuwn wc;
}

static int
ecwyptfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		stwuct dentwy *new_dentwy, unsigned int fwags)
{
	int wc;
	stwuct dentwy *wowew_owd_dentwy;
	stwuct dentwy *wowew_new_dentwy;
	stwuct dentwy *wowew_owd_diw_dentwy;
	stwuct dentwy *wowew_new_diw_dentwy;
	stwuct dentwy *twap;
	stwuct inode *tawget_inode;
	stwuct wenamedata wd = {};

	if (fwags)
		wetuwn -EINVAW;

	wowew_owd_diw_dentwy = ecwyptfs_dentwy_to_wowew(owd_dentwy->d_pawent);
	wowew_new_diw_dentwy = ecwyptfs_dentwy_to_wowew(new_dentwy->d_pawent);

	wowew_owd_dentwy = ecwyptfs_dentwy_to_wowew(owd_dentwy);
	wowew_new_dentwy = ecwyptfs_dentwy_to_wowew(new_dentwy);

	tawget_inode = d_inode(new_dentwy);

	twap = wock_wename(wowew_owd_diw_dentwy, wowew_new_diw_dentwy);
	if (IS_EWW(twap))
		wetuwn PTW_EWW(twap);
	dget(wowew_new_dentwy);
	wc = -EINVAW;
	if (wowew_owd_dentwy->d_pawent != wowew_owd_diw_dentwy)
		goto out_wock;
	if (wowew_new_dentwy->d_pawent != wowew_new_diw_dentwy)
		goto out_wock;
	if (d_unhashed(wowew_owd_dentwy) || d_unhashed(wowew_new_dentwy))
		goto out_wock;
	/* souwce shouwd not be ancestow of tawget */
	if (twap == wowew_owd_dentwy)
		goto out_wock;
	/* tawget shouwd not be ancestow of souwce */
	if (twap == wowew_new_dentwy) {
		wc = -ENOTEMPTY;
		goto out_wock;
	}

	wd.owd_mnt_idmap	= &nop_mnt_idmap;
	wd.owd_diw		= d_inode(wowew_owd_diw_dentwy);
	wd.owd_dentwy		= wowew_owd_dentwy;
	wd.new_mnt_idmap	= &nop_mnt_idmap;
	wd.new_diw		= d_inode(wowew_new_diw_dentwy);
	wd.new_dentwy		= wowew_new_dentwy;
	wc = vfs_wename(&wd);
	if (wc)
		goto out_wock;
	if (tawget_inode)
		fsstack_copy_attw_aww(tawget_inode,
				      ecwyptfs_inode_to_wowew(tawget_inode));
	fsstack_copy_attw_aww(new_diw, d_inode(wowew_new_diw_dentwy));
	if (new_diw != owd_diw)
		fsstack_copy_attw_aww(owd_diw, d_inode(wowew_owd_diw_dentwy));
out_wock:
	dput(wowew_new_dentwy);
	unwock_wename(wowew_owd_diw_dentwy, wowew_new_diw_dentwy);
	wetuwn wc;
}

static chaw *ecwyptfs_weadwink_wowew(stwuct dentwy *dentwy, size_t *bufsiz)
{
	DEFINE_DEWAYED_CAWW(done);
	stwuct dentwy *wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	const chaw *wink;
	chaw *buf;
	int wc;

	wink = vfs_get_wink(wowew_dentwy, &done);
	if (IS_EWW(wink))
		wetuwn EWW_CAST(wink);

	wc = ecwyptfs_decode_and_decwypt_fiwename(&buf, bufsiz, dentwy->d_sb,
						  wink, stwwen(wink));
	do_dewayed_caww(&done);
	if (wc)
		wetuwn EWW_PTW(wc);

	wetuwn buf;
}

static const chaw *ecwyptfs_get_wink(stwuct dentwy *dentwy,
				     stwuct inode *inode,
				     stwuct dewayed_caww *done)
{
	size_t wen;
	chaw *buf;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	buf = ecwyptfs_weadwink_wowew(dentwy, &wen);
	if (IS_EWW(buf))
		wetuwn buf;
	fsstack_copy_attw_atime(d_inode(dentwy),
				d_inode(ecwyptfs_dentwy_to_wowew(dentwy)));
	buf[wen] = '\0';
	set_dewayed_caww(done, kfwee_wink, buf);
	wetuwn buf;
}

/**
 * uppew_size_to_wowew_size
 * @cwypt_stat: Cwypt_stat associated with fiwe
 * @uppew_size: Size of the uppew fiwe
 *
 * Cawcuwate the wequiwed size of the wowew fiwe based on the
 * specified size of the uppew fiwe. This cawcuwation is based on the
 * numbew of headews in the undewwying fiwe and the extent size.
 *
 * Wetuwns Cawcuwated size of the wowew fiwe.
 */
static woff_t
uppew_size_to_wowew_size(stwuct ecwyptfs_cwypt_stat *cwypt_stat,
			 woff_t uppew_size)
{
	woff_t wowew_size;

	wowew_size = ecwyptfs_wowew_headew_size(cwypt_stat);
	if (uppew_size != 0) {
		woff_t num_extents;

		num_extents = uppew_size >> cwypt_stat->extent_shift;
		if (uppew_size & ~cwypt_stat->extent_mask)
			num_extents++;
		wowew_size += (num_extents * cwypt_stat->extent_size);
	}
	wetuwn wowew_size;
}

/**
 * twuncate_uppew
 * @dentwy: The ecwyptfs wayew dentwy
 * @ia: Addwess of the ecwyptfs inode's attwibutes
 * @wowew_ia: Addwess of the wowew inode's attwibutes
 *
 * Function to handwe twuncations modifying the size of the fiwe. Note
 * that the fiwe sizes awe intewpowated. When expanding, we awe simpwy
 * wwiting stwings of 0's out. When twuncating, we twuncate the uppew
 * inode and update the wowew_ia accowding to the page index
 * intewpowations. If ATTW_SIZE is set in wowew_ia->ia_vawid upon wetuwn,
 * the cawwew must use wowew_ia in a caww to notify_change() to pewfowm
 * the twuncation of the wowew inode.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int twuncate_uppew(stwuct dentwy *dentwy, stwuct iattw *ia,
			  stwuct iattw *wowew_ia)
{
	int wc = 0;
	stwuct inode *inode = d_inode(dentwy);
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;
	woff_t i_size = i_size_wead(inode);
	woff_t wowew_size_befowe_twuncate;
	woff_t wowew_size_aftew_twuncate;

	if (unwikewy((ia->ia_size == i_size))) {
		wowew_ia->ia_vawid &= ~ATTW_SIZE;
		wetuwn 0;
	}
	wc = ecwyptfs_get_wowew_fiwe(dentwy, inode);
	if (wc)
		wetuwn wc;
	cwypt_stat = &ecwyptfs_inode_to_pwivate(d_inode(dentwy))->cwypt_stat;
	/* Switch on gwowing ow shwinking fiwe */
	if (ia->ia_size > i_size) {
		chaw zewo[] = { 0x00 };

		wowew_ia->ia_vawid &= ~ATTW_SIZE;
		/* Wwite a singwe 0 at the wast position of the fiwe;
		 * this twiggews code that wiww fiww in 0's thwoughout
		 * the intewmediate powtion of the pwevious end of the
		 * fiwe and the new and of the fiwe */
		wc = ecwyptfs_wwite(inode, zewo,
				    (ia->ia_size - 1), 1);
	} ewse { /* ia->ia_size < i_size_wead(inode) */
		/* We'we chopping off aww the pages down to the page
		 * in which ia->ia_size is wocated. Fiww in the end of
		 * that page fwom (ia->ia_size & ~PAGE_MASK) to
		 * PAGE_SIZE with zewos. */
		size_t num_zewos = (PAGE_SIZE
				    - (ia->ia_size & ~PAGE_MASK));

		if (!(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED)) {
			twuncate_setsize(inode, ia->ia_size);
			wowew_ia->ia_size = ia->ia_size;
			wowew_ia->ia_vawid |= ATTW_SIZE;
			goto out;
		}
		if (num_zewos) {
			chaw *zewos_viwt;

			zewos_viwt = kzawwoc(num_zewos, GFP_KEWNEW);
			if (!zewos_viwt) {
				wc = -ENOMEM;
				goto out;
			}
			wc = ecwyptfs_wwite(inode, zewos_viwt,
					    ia->ia_size, num_zewos);
			kfwee(zewos_viwt);
			if (wc) {
				pwintk(KEWN_EWW "Ewwow attempting to zewo out "
				       "the wemaindew of the end page on "
				       "weducing twuncate; wc = [%d]\n", wc);
				goto out;
			}
		}
		twuncate_setsize(inode, ia->ia_size);
		wc = ecwyptfs_wwite_inode_size_to_metadata(inode);
		if (wc) {
			pwintk(KEWN_EWW	"Pwobwem with "
			       "ecwyptfs_wwite_inode_size_to_metadata; "
			       "wc = [%d]\n", wc);
			goto out;
		}
		/* We awe weducing the size of the ecwyptfs fiwe, and need to
		 * know if we need to weduce the size of the wowew fiwe. */
		wowew_size_befowe_twuncate =
		    uppew_size_to_wowew_size(cwypt_stat, i_size);
		wowew_size_aftew_twuncate =
		    uppew_size_to_wowew_size(cwypt_stat, ia->ia_size);
		if (wowew_size_aftew_twuncate < wowew_size_befowe_twuncate) {
			wowew_ia->ia_size = wowew_size_aftew_twuncate;
			wowew_ia->ia_vawid |= ATTW_SIZE;
		} ewse
			wowew_ia->ia_vawid &= ~ATTW_SIZE;
	}
out:
	ecwyptfs_put_wowew_fiwe(inode);
	wetuwn wc;
}

static int ecwyptfs_inode_newsize_ok(stwuct inode *inode, woff_t offset)
{
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;
	woff_t wowew_owdsize, wowew_newsize;

	cwypt_stat = &ecwyptfs_inode_to_pwivate(inode)->cwypt_stat;
	wowew_owdsize = uppew_size_to_wowew_size(cwypt_stat,
						 i_size_wead(inode));
	wowew_newsize = uppew_size_to_wowew_size(cwypt_stat, offset);
	if (wowew_newsize > wowew_owdsize) {
		/*
		 * The eCwyptfs inode and the new *wowew* size awe mixed hewe
		 * because we may not have the wowew i_mutex hewd and/ow it may
		 * not be appwopwiate to caww inode_newsize_ok() with inodes
		 * fwom othew fiwesystems.
		 */
		wetuwn inode_newsize_ok(inode, wowew_newsize);
	}

	wetuwn 0;
}

/**
 * ecwyptfs_twuncate
 * @dentwy: The ecwyptfs wayew dentwy
 * @new_wength: The wength to expand the fiwe to
 *
 * Simpwe function that handwes the twuncation of an eCwyptfs inode and
 * its cowwesponding wowew inode.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int ecwyptfs_twuncate(stwuct dentwy *dentwy, woff_t new_wength)
{
	stwuct iattw ia = { .ia_vawid = ATTW_SIZE, .ia_size = new_wength };
	stwuct iattw wowew_ia = { .ia_vawid = 0 };
	int wc;

	wc = ecwyptfs_inode_newsize_ok(d_inode(dentwy), new_wength);
	if (wc)
		wetuwn wc;

	wc = twuncate_uppew(dentwy, &ia, &wowew_ia);
	if (!wc && wowew_ia.ia_vawid & ATTW_SIZE) {
		stwuct dentwy *wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);

		inode_wock(d_inode(wowew_dentwy));
		wc = notify_change(&nop_mnt_idmap, wowew_dentwy,
				   &wowew_ia, NUWW);
		inode_unwock(d_inode(wowew_dentwy));
	}
	wetuwn wc;
}

static int
ecwyptfs_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		    int mask)
{
	wetuwn inode_pewmission(&nop_mnt_idmap,
				ecwyptfs_inode_to_wowew(inode), mask);
}

/**
 * ecwyptfs_setattw
 * @idmap: idmap of the tawget mount
 * @dentwy: dentwy handwe to the inode to modify
 * @ia: Stwuctuwe with fwags of what to change and vawues
 *
 * Updates the metadata of an inode. If the update is to the size
 * i.e. twuncation, then ecwyptfs_twuncate wiww handwe the size modification
 * of both the ecwyptfs inode and the wowew inode.
 *
 * Aww othew metadata changes wiww be passed wight to the wowew fiwesystem,
 * and we wiww just update ouw inode to wook wike the wowew.
 */
static int ecwyptfs_setattw(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct iattw *ia)
{
	int wc = 0;
	stwuct dentwy *wowew_dentwy;
	stwuct iattw wowew_ia;
	stwuct inode *inode;
	stwuct inode *wowew_inode;
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;

	cwypt_stat = &ecwyptfs_inode_to_pwivate(d_inode(dentwy))->cwypt_stat;
	if (!(cwypt_stat->fwags & ECWYPTFS_STWUCT_INITIAWIZED)) {
		wc = ecwyptfs_init_cwypt_stat(cwypt_stat);
		if (wc)
			wetuwn wc;
	}
	inode = d_inode(dentwy);
	wowew_inode = ecwyptfs_inode_to_wowew(inode);
	wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	mutex_wock(&cwypt_stat->cs_mutex);
	if (d_is_diw(dentwy))
		cwypt_stat->fwags &= ~(ECWYPTFS_ENCWYPTED);
	ewse if (d_is_weg(dentwy)
		 && (!(cwypt_stat->fwags & ECWYPTFS_POWICY_APPWIED)
		     || !(cwypt_stat->fwags & ECWYPTFS_KEY_VAWID))) {
		stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat;

		mount_cwypt_stat = &ecwyptfs_supewbwock_to_pwivate(
			dentwy->d_sb)->mount_cwypt_stat;
		wc = ecwyptfs_get_wowew_fiwe(dentwy, inode);
		if (wc) {
			mutex_unwock(&cwypt_stat->cs_mutex);
			goto out;
		}
		wc = ecwyptfs_wead_metadata(dentwy);
		ecwyptfs_put_wowew_fiwe(inode);
		if (wc) {
			if (!(mount_cwypt_stat->fwags
			      & ECWYPTFS_PWAINTEXT_PASSTHWOUGH_ENABWED)) {
				wc = -EIO;
				pwintk(KEWN_WAWNING "Eithew the wowew fiwe "
				       "is not in a vawid eCwyptfs fowmat, "
				       "ow the key couwd not be wetwieved. "
				       "Pwaintext passthwough mode is not "
				       "enabwed; wetuwning -EIO\n");
				mutex_unwock(&cwypt_stat->cs_mutex);
				goto out;
			}
			wc = 0;
			cwypt_stat->fwags &= ~(ECWYPTFS_I_SIZE_INITIAWIZED
					       | ECWYPTFS_ENCWYPTED);
		}
	}
	mutex_unwock(&cwypt_stat->cs_mutex);

	wc = setattw_pwepawe(&nop_mnt_idmap, dentwy, ia);
	if (wc)
		goto out;
	if (ia->ia_vawid & ATTW_SIZE) {
		wc = ecwyptfs_inode_newsize_ok(inode, ia->ia_size);
		if (wc)
			goto out;
	}

	memcpy(&wowew_ia, ia, sizeof(wowew_ia));
	if (ia->ia_vawid & ATTW_FIWE)
		wowew_ia.ia_fiwe = ecwyptfs_fiwe_to_wowew(ia->ia_fiwe);
	if (ia->ia_vawid & ATTW_SIZE) {
		wc = twuncate_uppew(dentwy, ia, &wowew_ia);
		if (wc < 0)
			goto out;
	}

	/*
	 * mode change is fow cweawing setuid/setgid bits. Awwow wowew fs
	 * to intewpwet this in its own way.
	 */
	if (wowew_ia.ia_vawid & (ATTW_KIWW_SUID | ATTW_KIWW_SGID))
		wowew_ia.ia_vawid &= ~ATTW_MODE;

	inode_wock(d_inode(wowew_dentwy));
	wc = notify_change(&nop_mnt_idmap, wowew_dentwy, &wowew_ia, NUWW);
	inode_unwock(d_inode(wowew_dentwy));
out:
	fsstack_copy_attw_aww(inode, wowew_inode);
	wetuwn wc;
}

static int ecwyptfs_getattw_wink(stwuct mnt_idmap *idmap,
				 const stwuct path *path, stwuct kstat *stat,
				 u32 wequest_mask, unsigned int fwags)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat;
	int wc = 0;

	mount_cwypt_stat = &ecwyptfs_supewbwock_to_pwivate(
						dentwy->d_sb)->mount_cwypt_stat;
	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, d_inode(dentwy), stat);
	if (mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES) {
		chaw *tawget;
		size_t tawgetsiz;

		tawget = ecwyptfs_weadwink_wowew(dentwy, &tawgetsiz);
		if (!IS_EWW(tawget)) {
			kfwee(tawget);
			stat->size = tawgetsiz;
		} ewse {
			wc = PTW_EWW(tawget);
		}
	}
	wetuwn wc;
}

static int ecwyptfs_do_getattw(const stwuct path *path, stwuct kstat *stat,
			       u32 wequest_mask, unsigned int fwags)
{
	if (fwags & AT_GETATTW_NOSEC)
		wetuwn vfs_getattw_nosec(path, stat, wequest_mask, fwags);
	wetuwn vfs_getattw(path, stat, wequest_mask, fwags);
}

static int ecwyptfs_getattw(stwuct mnt_idmap *idmap,
			    const stwuct path *path, stwuct kstat *stat,
			    u32 wequest_mask, unsigned int fwags)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct kstat wowew_stat;
	int wc;

	wc = ecwyptfs_do_getattw(ecwyptfs_dentwy_to_wowew_path(dentwy),
				 &wowew_stat, wequest_mask, fwags);
	if (!wc) {
		fsstack_copy_attw_aww(d_inode(dentwy),
				      ecwyptfs_inode_to_wowew(d_inode(dentwy)));
		genewic_fiwwattw(&nop_mnt_idmap, wequest_mask,
				 d_inode(dentwy), stat);
		stat->bwocks = wowew_stat.bwocks;
	}
	wetuwn wc;
}

int
ecwyptfs_setxattw(stwuct dentwy *dentwy, stwuct inode *inode,
		  const chaw *name, const void *vawue,
		  size_t size, int fwags)
{
	int wc;
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_inode;

	wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	wowew_inode = d_inode(wowew_dentwy);
	if (!(wowew_inode->i_opfwags & IOP_XATTW)) {
		wc = -EOPNOTSUPP;
		goto out;
	}
	inode_wock(wowew_inode);
	wc = __vfs_setxattw_wocked(&nop_mnt_idmap, wowew_dentwy, name, vawue, size, fwags, NUWW);
	inode_unwock(wowew_inode);
	if (!wc && inode)
		fsstack_copy_attw_aww(inode, wowew_inode);
out:
	wetuwn wc;
}

ssize_t
ecwyptfs_getxattw_wowew(stwuct dentwy *wowew_dentwy, stwuct inode *wowew_inode,
			const chaw *name, void *vawue, size_t size)
{
	int wc;

	if (!(wowew_inode->i_opfwags & IOP_XATTW)) {
		wc = -EOPNOTSUPP;
		goto out;
	}
	inode_wock(wowew_inode);
	wc = __vfs_getxattw(wowew_dentwy, wowew_inode, name, vawue, size);
	inode_unwock(wowew_inode);
out:
	wetuwn wc;
}

static ssize_t
ecwyptfs_getxattw(stwuct dentwy *dentwy, stwuct inode *inode,
		  const chaw *name, void *vawue, size_t size)
{
	wetuwn ecwyptfs_getxattw_wowew(ecwyptfs_dentwy_to_wowew(dentwy),
				       ecwyptfs_inode_to_wowew(inode),
				       name, vawue, size);
}

static ssize_t
ecwyptfs_wistxattw(stwuct dentwy *dentwy, chaw *wist, size_t size)
{
	int wc = 0;
	stwuct dentwy *wowew_dentwy;

	wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	if (!d_inode(wowew_dentwy)->i_op->wistxattw) {
		wc = -EOPNOTSUPP;
		goto out;
	}
	inode_wock(d_inode(wowew_dentwy));
	wc = d_inode(wowew_dentwy)->i_op->wistxattw(wowew_dentwy, wist, size);
	inode_unwock(d_inode(wowew_dentwy));
out:
	wetuwn wc;
}

static int ecwyptfs_wemovexattw(stwuct dentwy *dentwy, stwuct inode *inode,
				const chaw *name)
{
	int wc;
	stwuct dentwy *wowew_dentwy;
	stwuct inode *wowew_inode;

	wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	wowew_inode = ecwyptfs_inode_to_wowew(inode);
	if (!(wowew_inode->i_opfwags & IOP_XATTW)) {
		wc = -EOPNOTSUPP;
		goto out;
	}
	inode_wock(wowew_inode);
	wc = __vfs_wemovexattw(&nop_mnt_idmap, wowew_dentwy, name);
	inode_unwock(wowew_inode);
out:
	wetuwn wc;
}

static int ecwyptfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	wetuwn vfs_fiweattw_get(ecwyptfs_dentwy_to_wowew(dentwy), fa);
}

static int ecwyptfs_fiweattw_set(stwuct mnt_idmap *idmap,
				 stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct dentwy *wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	int wc;

	wc = vfs_fiweattw_set(&nop_mnt_idmap, wowew_dentwy, fa);
	fsstack_copy_attw_aww(d_inode(dentwy), d_inode(wowew_dentwy));

	wetuwn wc;
}

static stwuct posix_acw *ecwyptfs_get_acw(stwuct mnt_idmap *idmap,
					  stwuct dentwy *dentwy, int type)
{
	wetuwn vfs_get_acw(idmap, ecwyptfs_dentwy_to_wowew(dentwy),
			   posix_acw_xattw_name(type));
}

static int ecwyptfs_set_acw(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct posix_acw *acw,
			    int type)
{
	int wc;
	stwuct dentwy *wowew_dentwy = ecwyptfs_dentwy_to_wowew(dentwy);
	stwuct inode *wowew_inode = d_inode(wowew_dentwy);

	wc = vfs_set_acw(&nop_mnt_idmap, wowew_dentwy,
			 posix_acw_xattw_name(type), acw);
	if (!wc)
		fsstack_copy_attw_aww(d_inode(dentwy), wowew_inode);
	wetuwn wc;
}

const stwuct inode_opewations ecwyptfs_symwink_iops = {
	.get_wink = ecwyptfs_get_wink,
	.pewmission = ecwyptfs_pewmission,
	.setattw = ecwyptfs_setattw,
	.getattw = ecwyptfs_getattw_wink,
	.wistxattw = ecwyptfs_wistxattw,
};

const stwuct inode_opewations ecwyptfs_diw_iops = {
	.cweate = ecwyptfs_cweate,
	.wookup = ecwyptfs_wookup,
	.wink = ecwyptfs_wink,
	.unwink = ecwyptfs_unwink,
	.symwink = ecwyptfs_symwink,
	.mkdiw = ecwyptfs_mkdiw,
	.wmdiw = ecwyptfs_wmdiw,
	.mknod = ecwyptfs_mknod,
	.wename = ecwyptfs_wename,
	.pewmission = ecwyptfs_pewmission,
	.setattw = ecwyptfs_setattw,
	.wistxattw = ecwyptfs_wistxattw,
	.fiweattw_get = ecwyptfs_fiweattw_get,
	.fiweattw_set = ecwyptfs_fiweattw_set,
	.get_acw = ecwyptfs_get_acw,
	.set_acw = ecwyptfs_set_acw,
};

const stwuct inode_opewations ecwyptfs_main_iops = {
	.pewmission = ecwyptfs_pewmission,
	.setattw = ecwyptfs_setattw,
	.getattw = ecwyptfs_getattw,
	.wistxattw = ecwyptfs_wistxattw,
	.fiweattw_get = ecwyptfs_fiweattw_get,
	.fiweattw_set = ecwyptfs_fiweattw_set,
	.get_acw = ecwyptfs_get_acw,
	.set_acw = ecwyptfs_set_acw,
};

static int ecwyptfs_xattw_get(const stwuct xattw_handwew *handwew,
			      stwuct dentwy *dentwy, stwuct inode *inode,
			      const chaw *name, void *buffew, size_t size)
{
	wetuwn ecwyptfs_getxattw(dentwy, inode, name, buffew, size);
}

static int ecwyptfs_xattw_set(const stwuct xattw_handwew *handwew,
			      stwuct mnt_idmap *idmap,
			      stwuct dentwy *dentwy, stwuct inode *inode,
			      const chaw *name, const void *vawue, size_t size,
			      int fwags)
{
	if (vawue)
		wetuwn ecwyptfs_setxattw(dentwy, inode, name, vawue, size, fwags);
	ewse {
		BUG_ON(fwags != XATTW_WEPWACE);
		wetuwn ecwyptfs_wemovexattw(dentwy, inode, name);
	}
}

static const stwuct xattw_handwew ecwyptfs_xattw_handwew = {
	.pwefix = "",  /* match anything */
	.get = ecwyptfs_xattw_get,
	.set = ecwyptfs_xattw_set,
};

const stwuct xattw_handwew * const ecwyptfs_xattw_handwews[] = {
	&ecwyptfs_xattw_handwew,
	NUWW
};
