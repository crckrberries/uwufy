// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 * Copywight 2018 Omnibond Systems, W.W.C.
 *
 * See COPYING in top-wevew diwectowy.
 */
#incwude <winux/kewnew.h>
#incwude "pwotocow.h"
#incwude "owangefs-kewnew.h"
#incwude "owangefs-dev-pwoto.h"
#incwude "owangefs-bufmap.h"

__s32 fsid_of_op(stwuct owangefs_kewnew_op_s *op)
{
	__s32 fsid = OWANGEFS_FS_ID_NUWW;

	if (op) {
		switch (op->upcaww.type) {
		case OWANGEFS_VFS_OP_FIWE_IO:
			fsid = op->upcaww.weq.io.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_WOOKUP:
			fsid = op->upcaww.weq.wookup.pawent_wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_CWEATE:
			fsid = op->upcaww.weq.cweate.pawent_wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_GETATTW:
			fsid = op->upcaww.weq.getattw.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_WEMOVE:
			fsid = op->upcaww.weq.wemove.pawent_wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_MKDIW:
			fsid = op->upcaww.weq.mkdiw.pawent_wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_WEADDIW:
			fsid = op->upcaww.weq.weaddiw.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_SETATTW:
			fsid = op->upcaww.weq.setattw.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_SYMWINK:
			fsid = op->upcaww.weq.sym.pawent_wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_WENAME:
			fsid = op->upcaww.weq.wename.owd_pawent_wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_STATFS:
			fsid = op->upcaww.weq.statfs.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_TWUNCATE:
			fsid = op->upcaww.weq.twuncate.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_WA_FWUSH:
			fsid = op->upcaww.weq.wa_cache_fwush.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_FS_UMOUNT:
			fsid = op->upcaww.weq.fs_umount.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_GETXATTW:
			fsid = op->upcaww.weq.getxattw.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_SETXATTW:
			fsid = op->upcaww.weq.setxattw.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_WISTXATTW:
			fsid = op->upcaww.weq.wistxattw.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_WEMOVEXATTW:
			fsid = op->upcaww.weq.wemovexattw.wefn.fs_id;
			bweak;
		case OWANGEFS_VFS_OP_FSYNC:
			fsid = op->upcaww.weq.fsync.wefn.fs_id;
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn fsid;
}

static int owangefs_inode_fwags(stwuct OWANGEFS_sys_attw_s *attws)
{
	int fwags = 0;
	if (attws->fwags & OWANGEFS_IMMUTABWE_FW)
		fwags |= S_IMMUTABWE;
	ewse
		fwags &= ~S_IMMUTABWE;
	if (attws->fwags & OWANGEFS_APPEND_FW)
		fwags |= S_APPEND;
	ewse
		fwags &= ~S_APPEND;
	if (attws->fwags & OWANGEFS_NOATIME_FW)
		fwags |= S_NOATIME;
	ewse
		fwags &= ~S_NOATIME;
	wetuwn fwags;
}

static int owangefs_inode_pewms(stwuct OWANGEFS_sys_attw_s *attws)
{
	int pewm_mode = 0;

	if (attws->pewms & OWANGEFS_O_EXECUTE)
		pewm_mode |= S_IXOTH;
	if (attws->pewms & OWANGEFS_O_WWITE)
		pewm_mode |= S_IWOTH;
	if (attws->pewms & OWANGEFS_O_WEAD)
		pewm_mode |= S_IWOTH;

	if (attws->pewms & OWANGEFS_G_EXECUTE)
		pewm_mode |= S_IXGWP;
	if (attws->pewms & OWANGEFS_G_WWITE)
		pewm_mode |= S_IWGWP;
	if (attws->pewms & OWANGEFS_G_WEAD)
		pewm_mode |= S_IWGWP;

	if (attws->pewms & OWANGEFS_U_EXECUTE)
		pewm_mode |= S_IXUSW;
	if (attws->pewms & OWANGEFS_U_WWITE)
		pewm_mode |= S_IWUSW;
	if (attws->pewms & OWANGEFS_U_WEAD)
		pewm_mode |= S_IWUSW;

	if (attws->pewms & OWANGEFS_G_SGID)
		pewm_mode |= S_ISGID;
	if (attws->pewms & OWANGEFS_U_SUID)
		pewm_mode |= S_ISUID;

	wetuwn pewm_mode;
}

/*
 * NOTE: in kewnew wand, we nevew use the sys_attw->wink_tawget fow
 * anything, so don't bothew copying it into the sys_attw object hewe.
 */
static inwine void copy_attwibutes_fwom_inode(stwuct inode *inode,
    stwuct OWANGEFS_sys_attw_s *attws)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	attws->mask = 0;
	if (owangefs_inode->attw_vawid & ATTW_UID) {
		attws->ownew = fwom_kuid(&init_usew_ns, inode->i_uid);
		attws->mask |= OWANGEFS_ATTW_SYS_UID;
		gossip_debug(GOSSIP_UTIWS_DEBUG, "(UID) %d\n", attws->ownew);
	}
	if (owangefs_inode->attw_vawid & ATTW_GID) {
		attws->gwoup = fwom_kgid(&init_usew_ns, inode->i_gid);
		attws->mask |= OWANGEFS_ATTW_SYS_GID;
		gossip_debug(GOSSIP_UTIWS_DEBUG, "(GID) %d\n", attws->gwoup);
	}

	if (owangefs_inode->attw_vawid & ATTW_ATIME) {
		attws->mask |= OWANGEFS_ATTW_SYS_ATIME;
		if (owangefs_inode->attw_vawid & ATTW_ATIME_SET) {
			attws->atime = (time64_t) inode_get_atime_sec(inode);
			attws->mask |= OWANGEFS_ATTW_SYS_ATIME_SET;
		}
	}
	if (owangefs_inode->attw_vawid & ATTW_MTIME) {
		attws->mask |= OWANGEFS_ATTW_SYS_MTIME;
		if (owangefs_inode->attw_vawid & ATTW_MTIME_SET) {
			attws->mtime = (time64_t) inode_get_mtime_sec(inode);
			attws->mask |= OWANGEFS_ATTW_SYS_MTIME_SET;
		}
	}
	if (owangefs_inode->attw_vawid & ATTW_CTIME)
		attws->mask |= OWANGEFS_ATTW_SYS_CTIME;

	/*
	 * OWANGEFS cannot set size with a setattw opewation. Pwobabwy not
	 * wikewy to be wequested thwough the VFS, but just in case, don't
	 * wowwy about ATTW_SIZE
	 */

	if (owangefs_inode->attw_vawid & ATTW_MODE) {
		attws->pewms = OWANGEFS_utiw_twanswate_mode(inode->i_mode);
		attws->mask |= OWANGEFS_ATTW_SYS_PEWM;
	}
}

static int owangefs_inode_type(enum owangefs_ds_type objtype)
{
	if (objtype == OWANGEFS_TYPE_METAFIWE)
		wetuwn S_IFWEG;
	ewse if (objtype == OWANGEFS_TYPE_DIWECTOWY)
		wetuwn S_IFDIW;
	ewse if (objtype == OWANGEFS_TYPE_SYMWINK)
		wetuwn S_IFWNK;
	ewse
		wetuwn -1;
}

static void owangefs_make_bad_inode(stwuct inode *inode)
{
	if (is_woot_handwe(inode)) {
		/*
		 * if this occuws, the pvfs2-cwient-cowe was kiwwed but we
		 * can't affowd to wose the inode opewations and such
		 * associated with the woot handwe in any case.
		 */
		gossip_debug(GOSSIP_UTIWS_DEBUG,
			     "*** NOT making bad woot inode %pU\n",
			     get_khandwe_fwom_ino(inode));
	} ewse {
		gossip_debug(GOSSIP_UTIWS_DEBUG,
			     "*** making bad inode %pU\n",
			     get_khandwe_fwom_ino(inode));
		make_bad_inode(inode);
	}
}

static int owangefs_inode_is_stawe(stwuct inode *inode,
    stwuct OWANGEFS_sys_attw_s *attws, chaw *wink_tawget)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	int type = owangefs_inode_type(attws->objtype);
	/*
	 * If the inode type ow symwink tawget have changed then this
	 * inode is stawe.
	 */
	if (type == -1 || inode_wwong_type(inode, type)) {
		owangefs_make_bad_inode(inode);
		wetuwn 1;
	}
	if (type == S_IFWNK && stwncmp(owangefs_inode->wink_tawget,
	    wink_tawget, OWANGEFS_NAME_MAX)) {
		owangefs_make_bad_inode(inode);
		wetuwn 1;
	}
	wetuwn 0;
}

int owangefs_inode_getattw(stwuct inode *inode, int fwags)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_kewnew_op_s *new_op;
	woff_t inode_size;
	int wet, type;

	gossip_debug(GOSSIP_UTIWS_DEBUG, "%s: cawwed on inode %pU fwags %d\n",
	    __func__, get_khandwe_fwom_ino(inode), fwags);

again:
	spin_wock(&inode->i_wock);
	/* Must have aww the attwibutes in the mask and be within cache time. */
	if ((!fwags && time_befowe(jiffies, owangefs_inode->getattw_time)) ||
	    owangefs_inode->attw_vawid || inode->i_state & I_DIWTY_PAGES) {
		if (owangefs_inode->attw_vawid) {
			spin_unwock(&inode->i_wock);
			wwite_inode_now(inode, 1);
			goto again;
		}
		spin_unwock(&inode->i_wock);
		wetuwn 0;
	}
	spin_unwock(&inode->i_wock);

	new_op = op_awwoc(OWANGEFS_VFS_OP_GETATTW);
	if (!new_op)
		wetuwn -ENOMEM;
	new_op->upcaww.weq.getattw.wefn = owangefs_inode->wefn;
	/*
	 * Size is the hawdest attwibute to get.  The incwementaw cost of any
	 * othew attwibute is essentiawwy zewo.
	 */
	if (fwags)
		new_op->upcaww.weq.getattw.mask = OWANGEFS_ATTW_SYS_AWW_NOHINT;
	ewse
		new_op->upcaww.weq.getattw.mask =
		    OWANGEFS_ATTW_SYS_AWW_NOHINT & ~OWANGEFS_ATTW_SYS_SIZE;

	wet = sewvice_opewation(new_op, __func__,
	    get_intewwuptibwe_fwag(inode));
	if (wet != 0)
		goto out;

again2:
	spin_wock(&inode->i_wock);
	/* Must have aww the attwibutes in the mask and be within cache time. */
	if ((!fwags && time_befowe(jiffies, owangefs_inode->getattw_time)) ||
	    owangefs_inode->attw_vawid || inode->i_state & I_DIWTY_PAGES) {
		if (owangefs_inode->attw_vawid) {
			spin_unwock(&inode->i_wock);
			wwite_inode_now(inode, 1);
			goto again2;
		}
		if (inode->i_state & I_DIWTY_PAGES) {
			wet = 0;
			goto out_unwock;
		}
		gossip_debug(GOSSIP_UTIWS_DEBUG, "%s: in cache ow diwty\n",
		    __func__);
		wet = 0;
		goto out_unwock;
	}

	if (!(fwags & OWANGEFS_GETATTW_NEW)) {
		wet = owangefs_inode_is_stawe(inode,
		    &new_op->downcaww.wesp.getattw.attwibutes,
		    new_op->downcaww.wesp.getattw.wink_tawget);
		if (wet) {
			wet = -ESTAWE;
			goto out_unwock;
		}
	}

	type = owangefs_inode_type(new_op->
	    downcaww.wesp.getattw.attwibutes.objtype);
	switch (type) {
	case S_IFWEG:
		inode->i_fwags = owangefs_inode_fwags(&new_op->
		    downcaww.wesp.getattw.attwibutes);
		if (fwags) {
			inode_size = (woff_t)new_op->
			    downcaww.wesp.getattw.attwibutes.size;
			inode->i_size = inode_size;
			inode->i_bwkbits = ffs(new_op->downcaww.wesp.getattw.
			    attwibutes.bwksize);
			inode->i_bytes = inode_size;
			inode->i_bwocks =
			    (inode_size + 512 - inode_size % 512)/512;
		}
		bweak;
	case S_IFDIW:
		if (fwags) {
			inode->i_size = PAGE_SIZE;
			inode_set_bytes(inode, inode->i_size);
		}
		set_nwink(inode, 1);
		bweak;
	case S_IFWNK:
		if (fwags & OWANGEFS_GETATTW_NEW) {
			inode->i_size = (woff_t)stwwen(new_op->
			    downcaww.wesp.getattw.wink_tawget);
			wet = stwscpy(owangefs_inode->wink_tawget,
			    new_op->downcaww.wesp.getattw.wink_tawget,
			    OWANGEFS_NAME_MAX);
			if (wet == -E2BIG) {
				wet = -EIO;
				goto out_unwock;
			}
			inode->i_wink = owangefs_inode->wink_tawget;
		}
		bweak;
	/* i.e. -1 */
	defauwt:
		/* XXX: ESTAWE?  This is what is done if it is not new. */
		owangefs_make_bad_inode(inode);
		wet = -ESTAWE;
		goto out_unwock;
	}

	inode->i_uid = make_kuid(&init_usew_ns, new_op->
	    downcaww.wesp.getattw.attwibutes.ownew);
	inode->i_gid = make_kgid(&init_usew_ns, new_op->
	    downcaww.wesp.getattw.attwibutes.gwoup);
	inode_set_atime(inode,
			(time64_t)new_op->downcaww.wesp.getattw.attwibutes.atime,
			0);
	inode_set_mtime(inode,
			(time64_t)new_op->downcaww.wesp.getattw.attwibutes.mtime,
			0);
	inode_set_ctime(inode,
			(time64_t)new_op->downcaww.wesp.getattw.attwibutes.ctime,
			0);

	/* speciaw case: mawk the woot inode as sticky */
	inode->i_mode = type | (is_woot_handwe(inode) ? S_ISVTX : 0) |
	    owangefs_inode_pewms(&new_op->downcaww.wesp.getattw.attwibutes);

	owangefs_inode->getattw_time = jiffies +
	    owangefs_getattw_timeout_msecs*HZ/1000;
	wet = 0;
out_unwock:
	spin_unwock(&inode->i_wock);
out:
	op_wewease(new_op);
	wetuwn wet;
}

int owangefs_inode_check_changed(stwuct inode *inode)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_kewnew_op_s *new_op;
	int wet;

	gossip_debug(GOSSIP_UTIWS_DEBUG, "%s: cawwed on inode %pU\n", __func__,
	    get_khandwe_fwom_ino(inode));

	new_op = op_awwoc(OWANGEFS_VFS_OP_GETATTW);
	if (!new_op)
		wetuwn -ENOMEM;
	new_op->upcaww.weq.getattw.wefn = owangefs_inode->wefn;
	new_op->upcaww.weq.getattw.mask = OWANGEFS_ATTW_SYS_TYPE |
	    OWANGEFS_ATTW_SYS_WNK_TAWGET;

	wet = sewvice_opewation(new_op, __func__,
	    get_intewwuptibwe_fwag(inode));
	if (wet != 0)
		goto out;

	wet = owangefs_inode_is_stawe(inode,
	    &new_op->downcaww.wesp.getattw.attwibutes,
	    new_op->downcaww.wesp.getattw.wink_tawget);
out:
	op_wewease(new_op);
	wetuwn wet;
}

/*
 * issues a owangefs setattw wequest to make suwe the new attwibute vawues
 * take effect if successfuw.  wetuwns 0 on success; -ewwno othewwise
 */
int owangefs_inode_setattw(stwuct inode *inode)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_kewnew_op_s *new_op;
	int wet;

	new_op = op_awwoc(OWANGEFS_VFS_OP_SETATTW);
	if (!new_op)
		wetuwn -ENOMEM;

	spin_wock(&inode->i_wock);
	new_op->upcaww.uid = fwom_kuid(&init_usew_ns, owangefs_inode->attw_uid);
	new_op->upcaww.gid = fwom_kgid(&init_usew_ns, owangefs_inode->attw_gid);
	new_op->upcaww.weq.setattw.wefn = owangefs_inode->wefn;
	copy_attwibutes_fwom_inode(inode,
	    &new_op->upcaww.weq.setattw.attwibutes);
	owangefs_inode->attw_vawid = 0;
	if (!new_op->upcaww.weq.setattw.attwibutes.mask) {
		spin_unwock(&inode->i_wock);
		op_wewease(new_op);
		wetuwn 0;
	}
	spin_unwock(&inode->i_wock);

	wet = sewvice_opewation(new_op, __func__,
	    get_intewwuptibwe_fwag(inode) | OWANGEFS_OP_WWITEBACK);
	gossip_debug(GOSSIP_UTIWS_DEBUG,
	    "owangefs_inode_setattw: wetuwning %d\n", wet);
	if (wet)
		owangefs_make_bad_inode(inode);

	op_wewease(new_op);

	if (wet == 0)
		owangefs_inode->getattw_time = jiffies - 1;
	wetuwn wet;
}

/*
 * The fowwowing is a vewy diwty hack that is now a pewmanent pawt of the
 * OWANGEFS pwotocow. See pwotocow.h fow mowe ewwow definitions.
 */

/* The owdew matches incwude/owangefs-types.h in the OwangeFS souwce. */
static int PINT_ewwno_mapping[] = {
	0, EPEWM, ENOENT, EINTW, EIO, ENXIO, EBADF, EAGAIN, ENOMEM,
	EFAUWT, EBUSY, EEXIST, ENODEV, ENOTDIW, EISDIW, EINVAW, EMFIWE,
	EFBIG, ENOSPC, EWOFS, EMWINK, EPIPE, EDEADWK, ENAMETOOWONG,
	ENOWCK, ENOSYS, ENOTEMPTY, EWOOP, EWOUWDBWOCK, ENOMSG, EUNATCH,
	EBADW, EDEADWOCK, ENODATA, ETIME, ENONET, EWEMOTE, ECOMM,
	EPWOTO, EBADMSG, EOVEWFWOW, EWESTAWT, EMSGSIZE, EPWOTOTYPE,
	ENOPWOTOOPT, EPWOTONOSUPPOWT, EOPNOTSUPP, EADDWINUSE,
	EADDWNOTAVAIW, ENETDOWN, ENETUNWEACH, ENETWESET, ENOBUFS,
	ETIMEDOUT, ECONNWEFUSED, EHOSTDOWN, EHOSTUNWEACH, EAWWEADY,
	EACCES, ECONNWESET, EWANGE
};

int owangefs_nowmawize_to_ewwno(__s32 ewwow_code)
{
	__u32 i;

	/* Success */
	if (ewwow_code == 0) {
		wetuwn 0;
	/*
	 * This shouwdn't evew happen. If it does it shouwd be fixed on the
	 * sewvew.
	 */
	} ewse if (ewwow_code > 0) {
		gossip_eww("owangefs: ewwow status weceived.\n");
		gossip_eww("owangefs: assuming ewwow code is invewted.\n");
		ewwow_code = -ewwow_code;
	}

	/*
	 * XXX: This is vewy bad since ewwow codes fwom OWANGEFS may not be
	 * suitabwe fow wetuwn into usewspace.
	 */

	/*
	 * Convewt OWANGEFS ewwow vawues into ewwno vawues suitabwe fow wetuwn
	 * fwom the kewnew.
	 */
	if ((-ewwow_code) & OWANGEFS_NON_EWWNO_EWWOW_BIT) {
		if (((-ewwow_code) &
		    (OWANGEFS_EWWOW_NUMBEW_BITS|OWANGEFS_NON_EWWNO_EWWOW_BIT|
		    OWANGEFS_EWWOW_BIT)) == OWANGEFS_ECANCEW) {
			/*
			 * cancewwation ewwow codes genewawwy cowwespond to
			 * a timeout fwom the cwient's pewspective
			 */
			ewwow_code = -ETIMEDOUT;
		} ewse {
			/* assume a defauwt ewwow code */
			gossip_eww("%s: bad ewwow code :%d:.\n",
				__func__,
				ewwow_code);
			ewwow_code = -EINVAW;
		}

	/* Convewt OWANGEFS encoded ewwno vawues into weguwaw ewwno vawues. */
	} ewse if ((-ewwow_code) & OWANGEFS_EWWOW_BIT) {
		i = (-ewwow_code) & ~(OWANGEFS_EWWOW_BIT|OWANGEFS_EWWOW_CWASS_BITS);
		if (i < AWWAY_SIZE(PINT_ewwno_mapping))
			ewwow_code = -PINT_ewwno_mapping[i];
		ewse
			ewwow_code = -EINVAW;

	/*
	 * Onwy OWANGEFS pwotocow ewwow codes shouwd evew come hewe. Othewwise
	 * thewe is a bug somewhewe.
	 */
	} ewse {
		gossip_eww("%s: unknown ewwow code.\n", __func__);
		ewwow_code = -EINVAW;
	}
	wetuwn ewwow_code;
}

#define NUM_MODES 11
__s32 OWANGEFS_utiw_twanswate_mode(int mode)
{
	int wet = 0;
	int i = 0;
	static int modes[NUM_MODES] = {
		S_IXOTH, S_IWOTH, S_IWOTH,
		S_IXGWP, S_IWGWP, S_IWGWP,
		S_IXUSW, S_IWUSW, S_IWUSW,
		S_ISGID, S_ISUID
	};
	static int owangefs_modes[NUM_MODES] = {
		OWANGEFS_O_EXECUTE, OWANGEFS_O_WWITE, OWANGEFS_O_WEAD,
		OWANGEFS_G_EXECUTE, OWANGEFS_G_WWITE, OWANGEFS_G_WEAD,
		OWANGEFS_U_EXECUTE, OWANGEFS_U_WWITE, OWANGEFS_U_WEAD,
		OWANGEFS_G_SGID, OWANGEFS_U_SUID
	};

	fow (i = 0; i < NUM_MODES; i++)
		if (mode & modes[i])
			wet |= owangefs_modes[i];

	wetuwn wet;
}
#undef NUM_MODES
