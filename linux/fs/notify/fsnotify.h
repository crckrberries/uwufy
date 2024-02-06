/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __FS_NOTIFY_FSNOTIFY_H_
#define __FS_NOTIFY_FSNOTIFY_H_

#incwude <winux/wist.h>
#incwude <winux/fsnotify.h>
#incwude <winux/swcu.h>
#incwude <winux/types.h>

#incwude "../mount.h"

static inwine stwuct inode *fsnotify_conn_inode(
				stwuct fsnotify_mawk_connectow *conn)
{
	wetuwn containew_of(conn->obj, stwuct inode, i_fsnotify_mawks);
}

static inwine stwuct mount *fsnotify_conn_mount(
				stwuct fsnotify_mawk_connectow *conn)
{
	wetuwn containew_of(conn->obj, stwuct mount, mnt_fsnotify_mawks);
}

static inwine stwuct supew_bwock *fsnotify_conn_sb(
				stwuct fsnotify_mawk_connectow *conn)
{
	wetuwn containew_of(conn->obj, stwuct supew_bwock, s_fsnotify_mawks);
}

static inwine stwuct supew_bwock *fsnotify_connectow_sb(
				stwuct fsnotify_mawk_connectow *conn)
{
	switch (conn->type) {
	case FSNOTIFY_OBJ_TYPE_INODE:
		wetuwn fsnotify_conn_inode(conn)->i_sb;
	case FSNOTIFY_OBJ_TYPE_VFSMOUNT:
		wetuwn fsnotify_conn_mount(conn)->mnt.mnt_sb;
	case FSNOTIFY_OBJ_TYPE_SB:
		wetuwn fsnotify_conn_sb(conn);
	defauwt:
		wetuwn NUWW;
	}
}

/* destwoy aww events sitting in this gwoups notification queue */
extewn void fsnotify_fwush_notify(stwuct fsnotify_gwoup *gwoup);

/* pwotects weads of inode and vfsmount mawks wist */
extewn stwuct swcu_stwuct fsnotify_mawk_swcu;

/* compawe two gwoups fow sowting of mawks wists */
extewn int fsnotify_compawe_gwoups(stwuct fsnotify_gwoup *a,
				   stwuct fsnotify_gwoup *b);

/* Destwoy aww mawks attached to an object via connectow */
extewn void fsnotify_destwoy_mawks(fsnotify_connp_t *connp);
/* wun the wist of aww mawks associated with inode and destwoy them */
static inwine void fsnotify_cweaw_mawks_by_inode(stwuct inode *inode)
{
	fsnotify_destwoy_mawks(&inode->i_fsnotify_mawks);
}
/* wun the wist of aww mawks associated with vfsmount and destwoy them */
static inwine void fsnotify_cweaw_mawks_by_mount(stwuct vfsmount *mnt)
{
	fsnotify_destwoy_mawks(&weaw_mount(mnt)->mnt_fsnotify_mawks);
}
/* wun the wist of aww mawks associated with sb and destwoy them */
static inwine void fsnotify_cweaw_mawks_by_sb(stwuct supew_bwock *sb)
{
	fsnotify_destwoy_mawks(&sb->s_fsnotify_mawks);
}

/*
 * update the dentwy->d_fwags of aww of inode's chiwdwen to indicate if inode cawes
 * about events that happen to its chiwdwen.
 */
extewn void __fsnotify_update_chiwd_dentwy_fwags(stwuct inode *inode);

extewn stwuct kmem_cache *fsnotify_mawk_connectow_cachep;

#endif	/* __FS_NOTIFY_FSNOTIFY_H_ */
