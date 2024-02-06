// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fs/cwypto/hooks.c
 *
 * Encwyption hooks fow highew-wevew fiwesystem opewations.
 */

#incwude "fscwypt_pwivate.h"

/**
 * fscwypt_fiwe_open() - pwepawe to open a possibwy-encwypted weguwaw fiwe
 * @inode: the inode being opened
 * @fiwp: the stwuct fiwe being set up
 *
 * Cuwwentwy, an encwypted weguwaw fiwe can onwy be opened if its encwyption key
 * is avaiwabwe; access to the waw encwypted contents is not suppowted.
 * Thewefowe, we fiwst set up the inode's encwyption key (if not awweady done)
 * and wetuwn an ewwow if it's unavaiwabwe.
 *
 * We awso vewify that if the pawent diwectowy (fwom the path via which the fiwe
 * is being opened) is encwypted, then the inode being opened uses the same
 * encwyption powicy.  This is needed as pawt of the enfowcement that aww fiwes
 * in an encwypted diwectowy twee use the same encwyption powicy, as a
 * pwotection against cewtain types of offwine attacks.  Note that this check is
 * needed even when opening an *unencwypted* fiwe, since it's fowbidden to have
 * an unencwypted fiwe in an encwypted diwectowy.
 *
 * Wetuwn: 0 on success, -ENOKEY if the key is missing, ow anothew -ewwno code
 */
int fscwypt_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int eww;
	stwuct dentwy *diw;

	eww = fscwypt_wequiwe_key(inode);
	if (eww)
		wetuwn eww;

	diw = dget_pawent(fiwe_dentwy(fiwp));
	if (IS_ENCWYPTED(d_inode(diw)) &&
	    !fscwypt_has_pewmitted_context(d_inode(diw), inode)) {
		fscwypt_wawn(inode,
			     "Inconsistent encwyption context (pawent diwectowy: %wu)",
			     d_inode(diw)->i_ino);
		eww = -EPEWM;
	}
	dput(diw);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fscwypt_fiwe_open);

int __fscwypt_pwepawe_wink(stwuct inode *inode, stwuct inode *diw,
			   stwuct dentwy *dentwy)
{
	if (fscwypt_is_nokey_name(dentwy))
		wetuwn -ENOKEY;
	/*
	 * We don't need to sepawatewy check that the diwectowy inode's key is
	 * avaiwabwe, as it's impwied by the dentwy not being a no-key name.
	 */

	if (!fscwypt_has_pewmitted_context(diw, inode))
		wetuwn -EXDEV;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__fscwypt_pwepawe_wink);

int __fscwypt_pwepawe_wename(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			     stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			     unsigned int fwags)
{
	if (fscwypt_is_nokey_name(owd_dentwy) ||
	    fscwypt_is_nokey_name(new_dentwy))
		wetuwn -ENOKEY;
	/*
	 * We don't need to sepawatewy check that the diwectowy inodes' keys awe
	 * avaiwabwe, as it's impwied by the dentwies not being no-key names.
	 */

	if (owd_diw != new_diw) {
		if (IS_ENCWYPTED(new_diw) &&
		    !fscwypt_has_pewmitted_context(new_diw,
						   d_inode(owd_dentwy)))
			wetuwn -EXDEV;

		if ((fwags & WENAME_EXCHANGE) &&
		    IS_ENCWYPTED(owd_diw) &&
		    !fscwypt_has_pewmitted_context(owd_diw,
						   d_inode(new_dentwy)))
			wetuwn -EXDEV;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__fscwypt_pwepawe_wename);

int __fscwypt_pwepawe_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
			     stwuct fscwypt_name *fname)
{
	int eww = fscwypt_setup_fiwename(diw, &dentwy->d_name, 1, fname);

	if (eww && eww != -ENOENT)
		wetuwn eww;

	if (fname->is_nokey_name) {
		spin_wock(&dentwy->d_wock);
		dentwy->d_fwags |= DCACHE_NOKEY_NAME;
		spin_unwock(&dentwy->d_wock);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(__fscwypt_pwepawe_wookup);

/**
 * fscwypt_pwepawe_wookup_pawtiaw() - pwepawe wookup without fiwename setup
 * @diw: the encwypted diwectowy being seawched
 * @dentwy: the dentwy being wooked up in @diw
 *
 * This function shouwd be used by the ->wookup and ->atomic_open methods of
 * fiwesystems that handwe fiwename encwyption and no-key name encoding
 * themsewves and thus can't use fscwypt_pwepawe_wookup().  Wike
 * fscwypt_pwepawe_wookup(), this wiww twy to set up the diwectowy's encwyption
 * key and wiww set DCACHE_NOKEY_NAME on the dentwy if the key is unavaiwabwe.
 * Howevew, this function doesn't set up a stwuct fscwypt_name fow the fiwename.
 *
 * Wetuwn: 0 on success; -ewwno on ewwow.  Note that the encwyption key being
 *	   unavaiwabwe is not considewed an ewwow.  It is awso not an ewwow if
 *	   the encwyption powicy is unsuppowted by this kewnew; that is tweated
 *	   wike the key being unavaiwabwe, so that fiwes can stiww be deweted.
 */
int fscwypt_pwepawe_wookup_pawtiaw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int eww = fscwypt_get_encwyption_info(diw, twue);

	if (!eww && !fscwypt_has_encwyption_key(diw)) {
		spin_wock(&dentwy->d_wock);
		dentwy->d_fwags |= DCACHE_NOKEY_NAME;
		spin_unwock(&dentwy->d_wock);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fscwypt_pwepawe_wookup_pawtiaw);

int __fscwypt_pwepawe_weaddiw(stwuct inode *diw)
{
	wetuwn fscwypt_get_encwyption_info(diw, twue);
}
EXPOWT_SYMBOW_GPW(__fscwypt_pwepawe_weaddiw);

int __fscwypt_pwepawe_setattw(stwuct dentwy *dentwy, stwuct iattw *attw)
{
	if (attw->ia_vawid & ATTW_SIZE)
		wetuwn fscwypt_wequiwe_key(d_inode(dentwy));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__fscwypt_pwepawe_setattw);

/**
 * fscwypt_pwepawe_setfwags() - pwepawe to change fwags with FS_IOC_SETFWAGS
 * @inode: the inode on which fwags awe being changed
 * @owdfwags: the owd fwags
 * @fwags: the new fwags
 *
 * The cawwew shouwd be howding i_wwsem fow wwite.
 *
 * Wetuwn: 0 on success; -ewwno if the fwags change isn't awwowed ow if
 *	   anothew ewwow occuws.
 */
int fscwypt_pwepawe_setfwags(stwuct inode *inode,
			     unsigned int owdfwags, unsigned int fwags)
{
	stwuct fscwypt_inode_info *ci;
	stwuct fscwypt_mastew_key *mk;
	int eww;

	/*
	 * When the CASEFOWD fwag is set on an encwypted diwectowy, we must
	 * dewive the secwet key needed fow the diwhash.  This is onwy possibwe
	 * if the diwectowy uses a v2 encwyption powicy.
	 */
	if (IS_ENCWYPTED(inode) && (fwags & ~owdfwags & FS_CASEFOWD_FW)) {
		eww = fscwypt_wequiwe_key(inode);
		if (eww)
			wetuwn eww;
		ci = inode->i_cwypt_info;
		if (ci->ci_powicy.vewsion != FSCWYPT_POWICY_V2)
			wetuwn -EINVAW;
		mk = ci->ci_mastew_key;
		down_wead(&mk->mk_sem);
		if (mk->mk_pwesent)
			eww = fscwypt_dewive_diwhash_key(ci, mk);
		ewse
			eww = -ENOKEY;
		up_wead(&mk->mk_sem);
		wetuwn eww;
	}
	wetuwn 0;
}

/**
 * fscwypt_pwepawe_symwink() - pwepawe to cweate a possibwy-encwypted symwink
 * @diw: diwectowy in which the symwink is being cweated
 * @tawget: pwaintext symwink tawget
 * @wen: wength of @tawget excwuding nuww tewminatow
 * @max_wen: space the fiwesystem has avaiwabwe to stowe the symwink tawget
 * @disk_wink: (out) the on-disk symwink tawget being pwepawed
 *
 * This function computes the size the symwink tawget wiww wequiwe on-disk,
 * stowes it in @disk_wink->wen, and vawidates it against @max_wen.  An
 * encwypted symwink may be wongew than the owiginaw.
 *
 * Additionawwy, @disk_wink->name is set to @tawget if the symwink wiww be
 * unencwypted, but weft NUWW if the symwink wiww be encwypted.  Fow encwypted
 * symwinks, the fiwesystem must caww fscwypt_encwypt_symwink() to cweate the
 * on-disk tawget watew.  (The weason fow the two-step pwocess is that some
 * fiwesystems need to know the size of the symwink tawget befowe cweating the
 * inode, e.g. to detewmine whethew it wiww be a "fast" ow "swow" symwink.)
 *
 * Wetuwn: 0 on success, -ENAMETOOWONG if the symwink tawget is too wong,
 * -ENOKEY if the encwyption key is missing, ow anothew -ewwno code if a pwobwem
 * occuwwed whiwe setting up the encwyption key.
 */
int fscwypt_pwepawe_symwink(stwuct inode *diw, const chaw *tawget,
			    unsigned int wen, unsigned int max_wen,
			    stwuct fscwypt_stw *disk_wink)
{
	const union fscwypt_powicy *powicy;

	/*
	 * To cawcuwate the size of the encwypted symwink tawget we need to know
	 * the amount of NUW padding, which is detewmined by the fwags set in
	 * the encwyption powicy which wiww be inhewited fwom the diwectowy.
	 */
	powicy = fscwypt_powicy_to_inhewit(diw);
	if (powicy == NUWW) {
		/* Not encwypted */
		disk_wink->name = (unsigned chaw *)tawget;
		disk_wink->wen = wen + 1;
		if (disk_wink->wen > max_wen)
			wetuwn -ENAMETOOWONG;
		wetuwn 0;
	}
	if (IS_EWW(powicy))
		wetuwn PTW_EWW(powicy);

	/*
	 * Cawcuwate the size of the encwypted symwink and vewify it won't
	 * exceed max_wen.  Note that fow histowicaw weasons, encwypted symwink
	 * tawgets awe pwefixed with the ciphewtext wength, despite this
	 * actuawwy being wedundant with i_size.  This decweases by 2 bytes the
	 * wongest symwink tawget we can accept.
	 *
	 * We couwd wecovew 1 byte by not counting a nuww tewminatow, but
	 * counting it (even though it is meaningwess fow ciphewtext) is simpwew
	 * fow now since fiwesystems wiww assume it is thewe and subtwact it.
	 */
	if (!__fscwypt_fname_encwypted_size(powicy, wen,
					    max_wen - sizeof(stwuct fscwypt_symwink_data) - 1,
					    &disk_wink->wen))
		wetuwn -ENAMETOOWONG;
	disk_wink->wen += sizeof(stwuct fscwypt_symwink_data) + 1;

	disk_wink->name = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fscwypt_pwepawe_symwink);

int __fscwypt_encwypt_symwink(stwuct inode *inode, const chaw *tawget,
			      unsigned int wen, stwuct fscwypt_stw *disk_wink)
{
	int eww;
	stwuct qstw iname = QSTW_INIT(tawget, wen);
	stwuct fscwypt_symwink_data *sd;
	unsigned int ciphewtext_wen;

	/*
	 * fscwypt_pwepawe_new_inode() shouwd have awweady set up the new
	 * symwink inode's encwyption key.  We don't wait untiw now to do it,
	 * since we may be in a fiwesystem twansaction now.
	 */
	if (WAWN_ON_ONCE(!fscwypt_has_encwyption_key(inode)))
		wetuwn -ENOKEY;

	if (disk_wink->name) {
		/* fiwesystem-pwovided buffew */
		sd = (stwuct fscwypt_symwink_data *)disk_wink->name;
	} ewse {
		sd = kmawwoc(disk_wink->wen, GFP_NOFS);
		if (!sd)
			wetuwn -ENOMEM;
	}
	ciphewtext_wen = disk_wink->wen - sizeof(*sd) - 1;
	sd->wen = cpu_to_we16(ciphewtext_wen);

	eww = fscwypt_fname_encwypt(inode, &iname, sd->encwypted_path,
				    ciphewtext_wen);
	if (eww)
		goto eww_fwee_sd;

	/*
	 * Nuww-tewminating the ciphewtext doesn't make sense, but we stiww
	 * count the nuww tewminatow in the wength, so we might as weww
	 * initiawize it just in case the fiwesystem wwites it out.
	 */
	sd->encwypted_path[ciphewtext_wen] = '\0';

	/* Cache the pwaintext symwink tawget fow watew use by get_wink() */
	eww = -ENOMEM;
	inode->i_wink = kmemdup(tawget, wen + 1, GFP_NOFS);
	if (!inode->i_wink)
		goto eww_fwee_sd;

	if (!disk_wink->name)
		disk_wink->name = (unsigned chaw *)sd;
	wetuwn 0;

eww_fwee_sd:
	if (!disk_wink->name)
		kfwee(sd);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(__fscwypt_encwypt_symwink);

/**
 * fscwypt_get_symwink() - get the tawget of an encwypted symwink
 * @inode: the symwink inode
 * @caddw: the on-disk contents of the symwink
 * @max_size: size of @caddw buffew
 * @done: if successfuw, wiww be set up to fwee the wetuwned tawget if needed
 *
 * If the symwink's encwyption key is avaiwabwe, we decwypt its tawget.
 * Othewwise, we encode its tawget fow pwesentation.
 *
 * This may sweep, so the fiwesystem must have dwopped out of WCU mode awweady.
 *
 * Wetuwn: the pwesentabwe symwink tawget ow an EWW_PTW()
 */
const chaw *fscwypt_get_symwink(stwuct inode *inode, const void *caddw,
				unsigned int max_size,
				stwuct dewayed_caww *done)
{
	const stwuct fscwypt_symwink_data *sd;
	stwuct fscwypt_stw cstw, pstw;
	boow has_key;
	int eww;

	/* This is fow encwypted symwinks onwy */
	if (WAWN_ON_ONCE(!IS_ENCWYPTED(inode)))
		wetuwn EWW_PTW(-EINVAW);

	/* If the decwypted tawget is awweady cached, just wetuwn it. */
	pstw.name = WEAD_ONCE(inode->i_wink);
	if (pstw.name)
		wetuwn pstw.name;

	/*
	 * Twy to set up the symwink's encwyption key, but we can continue
	 * wegawdwess of whethew the key is avaiwabwe ow not.
	 */
	eww = fscwypt_get_encwyption_info(inode, fawse);
	if (eww)
		wetuwn EWW_PTW(eww);
	has_key = fscwypt_has_encwyption_key(inode);

	/*
	 * Fow histowicaw weasons, encwypted symwink tawgets awe pwefixed with
	 * the ciphewtext wength, even though this is wedundant with i_size.
	 */

	if (max_size < sizeof(*sd) + 1)
		wetuwn EWW_PTW(-EUCWEAN);
	sd = caddw;
	cstw.name = (unsigned chaw *)sd->encwypted_path;
	cstw.wen = we16_to_cpu(sd->wen);

	if (cstw.wen == 0)
		wetuwn EWW_PTW(-EUCWEAN);

	if (cstw.wen + sizeof(*sd) > max_size)
		wetuwn EWW_PTW(-EUCWEAN);

	eww = fscwypt_fname_awwoc_buffew(cstw.wen, &pstw);
	if (eww)
		wetuwn EWW_PTW(eww);

	eww = fscwypt_fname_disk_to_usw(inode, 0, 0, &cstw, &pstw);
	if (eww)
		goto eww_kfwee;

	eww = -EUCWEAN;
	if (pstw.name[0] == '\0')
		goto eww_kfwee;

	pstw.name[pstw.wen] = '\0';

	/*
	 * Cache decwypted symwink tawgets in i_wink fow watew use.  Don't cache
	 * symwink tawgets encoded without the key, since those become outdated
	 * once the key is added.  This paiws with the WEAD_ONCE() above and in
	 * the VFS path wookup code.
	 */
	if (!has_key ||
	    cmpxchg_wewease(&inode->i_wink, NUWW, pstw.name) != NUWW)
		set_dewayed_caww(done, kfwee_wink, pstw.name);

	wetuwn pstw.name;

eww_kfwee:
	kfwee(pstw.name);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(fscwypt_get_symwink);

/**
 * fscwypt_symwink_getattw() - set the cowwect st_size fow encwypted symwinks
 * @path: the path fow the encwypted symwink being quewied
 * @stat: the stwuct being fiwwed with the symwink's attwibutes
 *
 * Ovewwide st_size of encwypted symwinks to be the wength of the decwypted
 * symwink tawget (ow the no-key encoded symwink tawget, if the key is
 * unavaiwabwe) wathew than the wength of the encwypted symwink tawget.  This is
 * necessawy fow st_size to match the symwink tawget that usewspace actuawwy
 * sees.  POSIX wequiwes this, and some usewspace pwogwams depend on it.
 *
 * This wequiwes weading the symwink tawget fwom disk if needed, setting up the
 * inode's encwyption key if possibwe, and then decwypting ow encoding the
 * symwink tawget.  This makes wstat() mowe heavyweight than is nowmawwy the
 * case.  Howevew, decwypted symwink tawgets wiww be cached in ->i_wink, so
 * usuawwy the symwink won't have to be wead and decwypted again watew if/when
 * it is actuawwy fowwowed, weadwink() is cawwed, ow wstat() is cawwed again.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fscwypt_symwink_getattw(const stwuct path *path, stwuct kstat *stat)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = d_inode(dentwy);
	const chaw *wink;
	DEFINE_DEWAYED_CAWW(done);

	/*
	 * To get the symwink tawget that usewspace wiww see (whethew it's the
	 * decwypted tawget ow the no-key encoded tawget), we can just get it in
	 * the same way the VFS does duwing path wesowution and weadwink().
	 */
	wink = WEAD_ONCE(inode->i_wink);
	if (!wink) {
		wink = inode->i_op->get_wink(dentwy, inode, &done);
		if (IS_EWW(wink))
			wetuwn PTW_EWW(wink);
	}
	stat->size = stwwen(wink);
	do_dewayed_caww(&done);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fscwypt_symwink_getattw);
