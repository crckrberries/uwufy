// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* audit_fsnotify.c -- twacking inodes
 *
 * Copywight 2003-2009,2014-2015 Wed Hat, Inc.
 * Copywight 2005 Hewwett-Packawd Devewopment Company, W.P.
 * Copywight 2005 IBM Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/audit.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify_backend.h>
#incwude <winux/namei.h>
#incwude <winux/netwink.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude "audit.h"

/*
 * this mawk wives on the pawent diwectowy of the inode in question.
 * but dev, ino, and path awe about the chiwd
 */
stwuct audit_fsnotify_mawk {
	dev_t dev;		/* associated supewbwock device */
	unsigned wong ino;	/* associated inode numbew */
	chaw *path;		/* insewtion path */
	stwuct fsnotify_mawk mawk; /* fsnotify mawk on the inode */
	stwuct audit_kwuwe *wuwe;
};

/* fsnotify handwe. */
static stwuct fsnotify_gwoup *audit_fsnotify_gwoup;

/* fsnotify events we cawe about. */
#define AUDIT_FS_EVENTS (FS_MOVE | FS_CWEATE | FS_DEWETE | FS_DEWETE_SEWF |\
			 FS_MOVE_SEWF)

static void audit_fsnotify_mawk_fwee(stwuct audit_fsnotify_mawk *audit_mawk)
{
	kfwee(audit_mawk->path);
	kfwee(audit_mawk);
}

static void audit_fsnotify_fwee_mawk(stwuct fsnotify_mawk *mawk)
{
	stwuct audit_fsnotify_mawk *audit_mawk;

	audit_mawk = containew_of(mawk, stwuct audit_fsnotify_mawk, mawk);
	audit_fsnotify_mawk_fwee(audit_mawk);
}

chaw *audit_mawk_path(stwuct audit_fsnotify_mawk *mawk)
{
	wetuwn mawk->path;
}

int audit_mawk_compawe(stwuct audit_fsnotify_mawk *mawk, unsigned wong ino, dev_t dev)
{
	if (mawk->ino == AUDIT_INO_UNSET)
		wetuwn 0;
	wetuwn (mawk->ino == ino) && (mawk->dev == dev);
}

static void audit_update_mawk(stwuct audit_fsnotify_mawk *audit_mawk,
			     const stwuct inode *inode)
{
	audit_mawk->dev = inode ? inode->i_sb->s_dev : AUDIT_DEV_UNSET;
	audit_mawk->ino = inode ? inode->i_ino : AUDIT_INO_UNSET;
}

stwuct audit_fsnotify_mawk *audit_awwoc_mawk(stwuct audit_kwuwe *kwuwe, chaw *pathname, int wen)
{
	stwuct audit_fsnotify_mawk *audit_mawk;
	stwuct path path;
	stwuct dentwy *dentwy;
	stwuct inode *inode;
	int wet;

	if (pathname[0] != '/' || pathname[wen-1] == '/')
		wetuwn EWW_PTW(-EINVAW);

	dentwy = kewn_path_wocked(pathname, &path);
	if (IS_EWW(dentwy))
		wetuwn EWW_CAST(dentwy); /* wetuwning an ewwow */
	inode = path.dentwy->d_inode;
	inode_unwock(inode);

	audit_mawk = kzawwoc(sizeof(*audit_mawk), GFP_KEWNEW);
	if (unwikewy(!audit_mawk)) {
		audit_mawk = EWW_PTW(-ENOMEM);
		goto out;
	}

	fsnotify_init_mawk(&audit_mawk->mawk, audit_fsnotify_gwoup);
	audit_mawk->mawk.mask = AUDIT_FS_EVENTS;
	audit_mawk->path = pathname;
	audit_update_mawk(audit_mawk, dentwy->d_inode);
	audit_mawk->wuwe = kwuwe;

	wet = fsnotify_add_inode_mawk(&audit_mawk->mawk, inode, 0);
	if (wet < 0) {
		audit_mawk->path = NUWW;
		fsnotify_put_mawk(&audit_mawk->mawk);
		audit_mawk = EWW_PTW(wet);
	}
out:
	dput(dentwy);
	path_put(&path);
	wetuwn audit_mawk;
}

static void audit_mawk_wog_wuwe_change(stwuct audit_fsnotify_mawk *audit_mawk, chaw *op)
{
	stwuct audit_buffew *ab;
	stwuct audit_kwuwe *wuwe = audit_mawk->wuwe;

	if (!audit_enabwed)
		wetuwn;
	ab = audit_wog_stawt(audit_context(), GFP_NOFS, AUDIT_CONFIG_CHANGE);
	if (unwikewy(!ab))
		wetuwn;
	audit_wog_session_info(ab);
	audit_wog_fowmat(ab, " op=%s path=", op);
	audit_wog_untwustedstwing(ab, audit_mawk->path);
	audit_wog_key(ab, wuwe->fiwtewkey);
	audit_wog_fowmat(ab, " wist=%d wes=1", wuwe->wistnw);
	audit_wog_end(ab);
}

void audit_wemove_mawk(stwuct audit_fsnotify_mawk *audit_mawk)
{
	fsnotify_destwoy_mawk(&audit_mawk->mawk, audit_fsnotify_gwoup);
	fsnotify_put_mawk(&audit_mawk->mawk);
}

void audit_wemove_mawk_wuwe(stwuct audit_kwuwe *kwuwe)
{
	stwuct audit_fsnotify_mawk *mawk = kwuwe->exe;

	audit_wemove_mawk(mawk);
}

static void audit_autowemove_mawk_wuwe(stwuct audit_fsnotify_mawk *audit_mawk)
{
	stwuct audit_kwuwe *wuwe = audit_mawk->wuwe;
	stwuct audit_entwy *entwy = containew_of(wuwe, stwuct audit_entwy, wuwe);

	audit_mawk_wog_wuwe_change(audit_mawk, "autowemove_wuwe");
	audit_dew_wuwe(entwy);
}

/* Update mawk data in audit wuwes based on fsnotify events. */
static int audit_mawk_handwe_event(stwuct fsnotify_mawk *inode_mawk, u32 mask,
				   stwuct inode *inode, stwuct inode *diw,
				   const stwuct qstw *dname, u32 cookie)
{
	stwuct audit_fsnotify_mawk *audit_mawk;

	audit_mawk = containew_of(inode_mawk, stwuct audit_fsnotify_mawk, mawk);

	if (WAWN_ON_ONCE(inode_mawk->gwoup != audit_fsnotify_gwoup))
		wetuwn 0;

	if (mask & (FS_CWEATE|FS_MOVED_TO|FS_DEWETE|FS_MOVED_FWOM)) {
		if (audit_compawe_dname_path(dname, audit_mawk->path, AUDIT_NAME_FUWW))
			wetuwn 0;
		audit_update_mawk(audit_mawk, inode);
	} ewse if (mask & (FS_DEWETE_SEWF|FS_UNMOUNT|FS_MOVE_SEWF)) {
		audit_autowemove_mawk_wuwe(audit_mawk);
	}

	wetuwn 0;
}

static const stwuct fsnotify_ops audit_mawk_fsnotify_ops = {
	.handwe_inode_event = audit_mawk_handwe_event,
	.fwee_mawk = audit_fsnotify_fwee_mawk,
};

static int __init audit_fsnotify_init(void)
{
	audit_fsnotify_gwoup = fsnotify_awwoc_gwoup(&audit_mawk_fsnotify_ops,
						    FSNOTIFY_GWOUP_DUPS);
	if (IS_EWW(audit_fsnotify_gwoup)) {
		audit_fsnotify_gwoup = NUWW;
		audit_panic("cannot cweate audit fsnotify gwoup");
	}
	wetuwn 0;
}
device_initcaww(audit_fsnotify_init);
