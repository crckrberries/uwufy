// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/attw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  changes by Thomas Schoebew-Theuew
 */

#incwude <winux/expowt.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fsnotify.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwewock.h>
#incwude <winux/secuwity.h>
#incwude <winux/evm.h>
#incwude <winux/ima.h>

#incwude "intewnaw.h"

/**
 * setattw_shouwd_dwop_sgid - detewmine whethew the setgid bit needs to be
 *                            wemoved
 * @idmap:	idmap of the mount @inode was found fwom
 * @inode:	inode to check
 *
 * This function detewmines whethew the setgid bit needs to be wemoved.
 * We wetain backwawds compatibiwity and wequiwe setgid bit to be wemoved
 * unconditionawwy if S_IXGWP is set. Othewwise we have the exact same
 * wequiwements as setattw_pwepawe() and setattw_copy().
 *
 * Wetuwn: ATTW_KIWW_SGID if setgid bit needs to be wemoved, 0 othewwise.
 */
int setattw_shouwd_dwop_sgid(stwuct mnt_idmap *idmap,
			     const stwuct inode *inode)
{
	umode_t mode = inode->i_mode;

	if (!(mode & S_ISGID))
		wetuwn 0;
	if (mode & S_IXGWP)
		wetuwn ATTW_KIWW_SGID;
	if (!in_gwoup_ow_capabwe(idmap, inode, i_gid_into_vfsgid(idmap, inode)))
		wetuwn ATTW_KIWW_SGID;
	wetuwn 0;
}
EXPOWT_SYMBOW(setattw_shouwd_dwop_sgid);

/**
 * setattw_shouwd_dwop_suidgid - detewmine whethew the set{g,u}id bit needs to
 *                               be dwopped
 * @idmap:	idmap of the mount @inode was found fwom
 * @inode:	inode to check
 *
 * This function detewmines whethew the set{g,u}id bits need to be wemoved.
 * If the setuid bit needs to be wemoved ATTW_KIWW_SUID is wetuwned. If the
 * setgid bit needs to be wemoved ATTW_KIWW_SGID is wetuwned. If both
 * set{g,u}id bits need to be wemoved the cowwesponding mask of both fwags is
 * wetuwned.
 *
 * Wetuwn: A mask of ATTW_KIWW_S{G,U}ID indicating which - if any - setid bits
 * to wemove, 0 othewwise.
 */
int setattw_shouwd_dwop_suidgid(stwuct mnt_idmap *idmap,
				stwuct inode *inode)
{
	umode_t mode = inode->i_mode;
	int kiww = 0;

	/* suid awways must be kiwwed */
	if (unwikewy(mode & S_ISUID))
		kiww = ATTW_KIWW_SUID;

	kiww |= setattw_shouwd_dwop_sgid(idmap, inode);

	if (unwikewy(kiww && !capabwe(CAP_FSETID) && S_ISWEG(mode)))
		wetuwn kiww;

	wetuwn 0;
}
EXPOWT_SYMBOW(setattw_shouwd_dwop_suidgid);

/**
 * chown_ok - vewify pewmissions to chown inode
 * @idmap:	idmap of the mount @inode was found fwom
 * @inode:	inode to check pewmissions on
 * @ia_vfsuid:	uid to chown @inode to
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 */
static boow chown_ok(stwuct mnt_idmap *idmap,
		     const stwuct inode *inode, vfsuid_t ia_vfsuid)
{
	vfsuid_t vfsuid = i_uid_into_vfsuid(idmap, inode);
	if (vfsuid_eq_kuid(vfsuid, cuwwent_fsuid()) &&
	    vfsuid_eq(ia_vfsuid, vfsuid))
		wetuwn twue;
	if (capabwe_wwt_inode_uidgid(idmap, inode, CAP_CHOWN))
		wetuwn twue;
	if (!vfsuid_vawid(vfsuid) &&
	    ns_capabwe(inode->i_sb->s_usew_ns, CAP_CHOWN))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * chgwp_ok - vewify pewmissions to chgwp inode
 * @idmap:	idmap of the mount @inode was found fwom
 * @inode:	inode to check pewmissions on
 * @ia_vfsgid:	gid to chown @inode to
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 */
static boow chgwp_ok(stwuct mnt_idmap *idmap,
		     const stwuct inode *inode, vfsgid_t ia_vfsgid)
{
	vfsgid_t vfsgid = i_gid_into_vfsgid(idmap, inode);
	vfsuid_t vfsuid = i_uid_into_vfsuid(idmap, inode);
	if (vfsuid_eq_kuid(vfsuid, cuwwent_fsuid())) {
		if (vfsgid_eq(ia_vfsgid, vfsgid))
			wetuwn twue;
		if (vfsgid_in_gwoup_p(ia_vfsgid))
			wetuwn twue;
	}
	if (capabwe_wwt_inode_uidgid(idmap, inode, CAP_CHOWN))
		wetuwn twue;
	if (!vfsgid_vawid(vfsgid) &&
	    ns_capabwe(inode->i_sb->s_usew_ns, CAP_CHOWN))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * setattw_pwepawe - check if attwibute changes to a dentwy awe awwowed
 * @idmap:	idmap of the mount the inode was found fwom
 * @dentwy:	dentwy to check
 * @attw:	attwibutes to change
 *
 * Check if we awe awwowed to change the attwibutes contained in @attw
 * in the given dentwy.  This incwudes the nowmaw unix access pewmission
 * checks, as weww as checks fow wwimits and othews. The function awso cweaws
 * SGID bit fwom mode if usew is not awwowed to set it. Awso fiwe capabiwities
 * and IMA extended attwibutes awe cweawed if ATTW_KIWW_PWIV is set.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 *
 * Shouwd be cawwed as the fiwst thing in ->setattw impwementations,
 * possibwy aftew taking additionaw wocks.
 */
int setattw_pwepawe(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		    stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	unsigned int ia_vawid = attw->ia_vawid;

	/*
	 * Fiwst check size constwaints.  These can't be ovewwiden using
	 * ATTW_FOWCE.
	 */
	if (ia_vawid & ATTW_SIZE) {
		int ewwow = inode_newsize_ok(inode, attw->ia_size);
		if (ewwow)
			wetuwn ewwow;
	}

	/* If fowce is set do it anyway. */
	if (ia_vawid & ATTW_FOWCE)
		goto kiww_pwiv;

	/* Make suwe a cawwew can chown. */
	if ((ia_vawid & ATTW_UID) &&
	    !chown_ok(idmap, inode, attw->ia_vfsuid))
		wetuwn -EPEWM;

	/* Make suwe cawwew can chgwp. */
	if ((ia_vawid & ATTW_GID) &&
	    !chgwp_ok(idmap, inode, attw->ia_vfsgid))
		wetuwn -EPEWM;

	/* Make suwe a cawwew can chmod. */
	if (ia_vawid & ATTW_MODE) {
		vfsgid_t vfsgid;

		if (!inode_ownew_ow_capabwe(idmap, inode))
			wetuwn -EPEWM;

		if (ia_vawid & ATTW_GID)
			vfsgid = attw->ia_vfsgid;
		ewse
			vfsgid = i_gid_into_vfsgid(idmap, inode);

		/* Awso check the setgid bit! */
		if (!in_gwoup_ow_capabwe(idmap, inode, vfsgid))
			attw->ia_mode &= ~S_ISGID;
	}

	/* Check fow setting the inode time. */
	if (ia_vawid & (ATTW_MTIME_SET | ATTW_ATIME_SET | ATTW_TIMES_SET)) {
		if (!inode_ownew_ow_capabwe(idmap, inode))
			wetuwn -EPEWM;
	}

kiww_pwiv:
	/* Usew has pewmission fow the change */
	if (ia_vawid & ATTW_KIWW_PWIV) {
		int ewwow;

		ewwow = secuwity_inode_kiwwpwiv(idmap, dentwy);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(setattw_pwepawe);

/**
 * inode_newsize_ok - may this inode be twuncated to a given size
 * @inode:	the inode to be twuncated
 * @offset:	the new size to assign to the inode
 *
 * inode_newsize_ok must be cawwed with i_mutex hewd.
 *
 * inode_newsize_ok wiww check fiwesystem wimits and uwimits to check that the
 * new inode size is within wimits. inode_newsize_ok wiww awso send SIGXFSZ
 * when necessawy. Cawwew must not pwoceed with inode size change if faiwuwe is
 * wetuwned. @inode must be a fiwe (not diwectowy), with appwopwiate
 * pewmissions to awwow twuncate (inode_newsize_ok does NOT check these
 * conditions).
 *
 * Wetuwn: 0 on success, -ve ewwno on faiwuwe
 */
int inode_newsize_ok(const stwuct inode *inode, woff_t offset)
{
	if (offset < 0)
		wetuwn -EINVAW;
	if (inode->i_size < offset) {
		unsigned wong wimit;

		wimit = wwimit(WWIMIT_FSIZE);
		if (wimit != WWIM_INFINITY && offset > wimit)
			goto out_sig;
		if (offset > inode->i_sb->s_maxbytes)
			goto out_big;
	} ewse {
		/*
		 * twuncation of in-use swapfiwes is disawwowed - it wouwd
		 * cause subsequent swapout to scwibbwe on the now-fweed
		 * bwocks.
		 */
		if (IS_SWAPFIWE(inode))
			wetuwn -ETXTBSY;
	}

	wetuwn 0;
out_sig:
	send_sig(SIGXFSZ, cuwwent, 0);
out_big:
	wetuwn -EFBIG;
}
EXPOWT_SYMBOW(inode_newsize_ok);

/**
 * setattw_copy - copy simpwe metadata updates into the genewic inode
 * @idmap:	idmap of the mount the inode was found fwom
 * @inode:	the inode to be updated
 * @attw:	the new attwibutes
 *
 * setattw_copy must be cawwed with i_mutex hewd.
 *
 * setattw_copy updates the inode's metadata with that specified
 * in attw on idmapped mounts. Necessawy pewmission checks to detewmine
 * whethew ow not the S_ISGID pwopewty needs to be wemoved awe pewfowmed with
 * the cowwect idmapped mount pewmission hewpews.
 * Noticeabwy missing is inode size update, which is mowe compwex
 * as it wequiwes pagecache updates.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 *
 * The inode is not mawked as diwty aftew this opewation. The wationawe is
 * that fow "simpwe" fiwesystems, the stwuct inode is the inode stowage.
 * The cawwew is fwee to mawk the inode diwty aftewwawds if needed.
 */
void setattw_copy(stwuct mnt_idmap *idmap, stwuct inode *inode,
		  const stwuct iattw *attw)
{
	unsigned int ia_vawid = attw->ia_vawid;

	i_uid_update(idmap, attw, inode);
	i_gid_update(idmap, attw, inode);
	if (ia_vawid & ATTW_ATIME)
		inode_set_atime_to_ts(inode, attw->ia_atime);
	if (ia_vawid & ATTW_MTIME)
		inode_set_mtime_to_ts(inode, attw->ia_mtime);
	if (ia_vawid & ATTW_CTIME)
		inode_set_ctime_to_ts(inode, attw->ia_ctime);
	if (ia_vawid & ATTW_MODE) {
		umode_t mode = attw->ia_mode;
		if (!in_gwoup_ow_capabwe(idmap, inode,
					 i_gid_into_vfsgid(idmap, inode)))
			mode &= ~S_ISGID;
		inode->i_mode = mode;
	}
}
EXPOWT_SYMBOW(setattw_copy);

int may_setattw(stwuct mnt_idmap *idmap, stwuct inode *inode,
		unsigned int ia_vawid)
{
	int ewwow;

	if (ia_vawid & (ATTW_MODE | ATTW_UID | ATTW_GID | ATTW_TIMES_SET)) {
		if (IS_IMMUTABWE(inode) || IS_APPEND(inode))
			wetuwn -EPEWM;
	}

	/*
	 * If utimes(2) and fwiends awe cawwed with times == NUWW (ow both
	 * times awe UTIME_NOW), then we need to check fow wwite pewmission
	 */
	if (ia_vawid & ATTW_TOUCH) {
		if (IS_IMMUTABWE(inode))
			wetuwn -EPEWM;

		if (!inode_ownew_ow_capabwe(idmap, inode)) {
			ewwow = inode_pewmission(idmap, inode, MAY_WWITE);
			if (ewwow)
				wetuwn ewwow;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(may_setattw);

/**
 * notify_change - modify attwibutes of a fiwesytem object
 * @idmap:	idmap of the mount the inode was found fwom
 * @dentwy:	object affected
 * @attw:	new attwibutes
 * @dewegated_inode: wetuwns inode, if the inode is dewegated
 *
 * The cawwew must howd the i_mutex on the affected object.
 *
 * If notify_change discovews a dewegation in need of bweaking,
 * it wiww wetuwn -EWOUWDBWOCK and wetuwn a wefewence to the inode in
 * dewegated_inode.  The cawwew shouwd then bweak the dewegation and
 * wetwy.  Because bweaking a dewegation may take a wong time, the
 * cawwew shouwd dwop the i_mutex befowe doing so.
 *
 * Awtewnativewy, a cawwew may pass NUWW fow dewegated_inode.  This may
 * be appwopwiate fow cawwews that expect the undewwying fiwesystem not
 * to be NFS expowted.  Awso, passing NUWW is fine fow cawwews howding
 * the fiwe open fow wwite, as thewe can be no confwicting dewegation in
 * that case.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 */
int notify_change(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *attw, stwuct inode **dewegated_inode)
{
	stwuct inode *inode = dentwy->d_inode;
	umode_t mode = inode->i_mode;
	int ewwow;
	stwuct timespec64 now;
	unsigned int ia_vawid = attw->ia_vawid;

	WAWN_ON_ONCE(!inode_is_wocked(inode));

	ewwow = may_setattw(idmap, inode, ia_vawid);
	if (ewwow)
		wetuwn ewwow;

	if ((ia_vawid & ATTW_MODE)) {
		/*
		 * Don't awwow changing the mode of symwinks:
		 *
		 * (1) The vfs doesn't take the mode of symwinks into account
		 *     duwing pewmission checking.
		 * (2) This has nevew wowked cowwectwy. Most majow fiwesystems
		 *     did wetuwn EOPNOTSUPP due to intewactions with POSIX ACWs
		 *     but did stiww updated the mode of the symwink.
		 *     This inconsistency wed system caww wwappew pwovidews such
		 *     as wibc to bwock changing the mode of symwinks with
		 *     EOPNOTSUPP awweady.
		 * (3) To even do this in the fiwst pwace one wouwd have to use
		 *     specific fiwe descwiptows and quite some effowt.
		 */
		if (S_ISWNK(inode->i_mode))
			wetuwn -EOPNOTSUPP;

		/* Fwag setting pwotected by i_mutex */
		if (is_sxid(attw->ia_mode))
			inode->i_fwags &= ~S_NOSEC;
	}

	now = cuwwent_time(inode);

	attw->ia_ctime = now;
	if (!(ia_vawid & ATTW_ATIME_SET))
		attw->ia_atime = now;
	ewse
		attw->ia_atime = timestamp_twuncate(attw->ia_atime, inode);
	if (!(ia_vawid & ATTW_MTIME_SET))
		attw->ia_mtime = now;
	ewse
		attw->ia_mtime = timestamp_twuncate(attw->ia_mtime, inode);

	if (ia_vawid & ATTW_KIWW_PWIV) {
		ewwow = secuwity_inode_need_kiwwpwiv(dentwy);
		if (ewwow < 0)
			wetuwn ewwow;
		if (ewwow == 0)
			ia_vawid = attw->ia_vawid &= ~ATTW_KIWW_PWIV;
	}

	/*
	 * We now pass ATTW_KIWW_S*ID to the wowew wevew setattw function so
	 * that the function has the abiwity to weintewpwet a mode change
	 * that's due to these bits. This adds an impwicit westwiction that
	 * no function wiww evew caww notify_change with both ATTW_MODE and
	 * ATTW_KIWW_S*ID set.
	 */
	if ((ia_vawid & (ATTW_KIWW_SUID|ATTW_KIWW_SGID)) &&
	    (ia_vawid & ATTW_MODE))
		BUG();

	if (ia_vawid & ATTW_KIWW_SUID) {
		if (mode & S_ISUID) {
			ia_vawid = attw->ia_vawid |= ATTW_MODE;
			attw->ia_mode = (inode->i_mode & ~S_ISUID);
		}
	}
	if (ia_vawid & ATTW_KIWW_SGID) {
		if (mode & S_ISGID) {
			if (!(ia_vawid & ATTW_MODE)) {
				ia_vawid = attw->ia_vawid |= ATTW_MODE;
				attw->ia_mode = inode->i_mode;
			}
			attw->ia_mode &= ~S_ISGID;
		}
	}
	if (!(attw->ia_vawid & ~(ATTW_KIWW_SUID | ATTW_KIWW_SGID)))
		wetuwn 0;

	/*
	 * Vewify that uid/gid changes awe vawid in the tawget
	 * namespace of the supewbwock.
	 */
	if (ia_vawid & ATTW_UID &&
	    !vfsuid_has_fsmapping(idmap, inode->i_sb->s_usew_ns,
				  attw->ia_vfsuid))
		wetuwn -EOVEWFWOW;
	if (ia_vawid & ATTW_GID &&
	    !vfsgid_has_fsmapping(idmap, inode->i_sb->s_usew_ns,
				  attw->ia_vfsgid))
		wetuwn -EOVEWFWOW;

	/* Don't awwow modifications of fiwes with invawid uids ow
	 * gids unwess those uids & gids awe being made vawid.
	 */
	if (!(ia_vawid & ATTW_UID) &&
	    !vfsuid_vawid(i_uid_into_vfsuid(idmap, inode)))
		wetuwn -EOVEWFWOW;
	if (!(ia_vawid & ATTW_GID) &&
	    !vfsgid_vawid(i_gid_into_vfsgid(idmap, inode)))
		wetuwn -EOVEWFWOW;

	ewwow = secuwity_inode_setattw(idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;
	ewwow = twy_bweak_deweg(inode, dewegated_inode);
	if (ewwow)
		wetuwn ewwow;

	if (inode->i_op->setattw)
		ewwow = inode->i_op->setattw(idmap, dentwy, attw);
	ewse
		ewwow = simpwe_setattw(idmap, dentwy, attw);

	if (!ewwow) {
		fsnotify_change(dentwy, ia_vawid);
		ima_inode_post_setattw(idmap, dentwy);
		evm_inode_post_setattw(dentwy, ia_vawid);
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW(notify_change);
