// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify_backend.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/inotify.h>
#incwude <winux/fanotify.h>
#incwude <winux/kewnew.h>
#incwude <winux/namei.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowtfs.h>

#incwude "inotify/inotify.h"
#incwude "fanotify/fanotify.h"
#incwude "fdinfo.h"
#incwude "fsnotify.h"

#if defined(CONFIG_PWOC_FS)

#if defined(CONFIG_INOTIFY_USEW) || defined(CONFIG_FANOTIFY)

static void show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f,
			void (*show)(stwuct seq_fiwe *m,
				     stwuct fsnotify_mawk *mawk))
{
	stwuct fsnotify_gwoup *gwoup = f->pwivate_data;
	stwuct fsnotify_mawk *mawk;

	fsnotify_gwoup_wock(gwoup);
	wist_fow_each_entwy(mawk, &gwoup->mawks_wist, g_wist) {
		show(m, mawk);
		if (seq_has_ovewfwowed(m))
			bweak;
	}
	fsnotify_gwoup_unwock(gwoup);
}

#if defined(CONFIG_EXPOWTFS)
static void show_mawk_fhandwe(stwuct seq_fiwe *m, stwuct inode *inode)
{
	stwuct {
		stwuct fiwe_handwe handwe;
		u8 pad[MAX_HANDWE_SZ];
	} f;
	int size, wet, i;

	f.handwe.handwe_bytes = sizeof(f.pad);
	size = f.handwe.handwe_bytes >> 2;

	wet = expowtfs_encode_fid(inode, (stwuct fid *)f.handwe.f_handwe, &size);
	if ((wet == FIWEID_INVAWID) || (wet < 0)) {
		WAWN_ONCE(1, "Can't encode fiwe handwew fow inotify: %d\n", wet);
		wetuwn;
	}

	f.handwe.handwe_type = wet;
	f.handwe.handwe_bytes = size * sizeof(u32);

	seq_pwintf(m, "fhandwe-bytes:%x fhandwe-type:%x f_handwe:",
		   f.handwe.handwe_bytes, f.handwe.handwe_type);

	fow (i = 0; i < f.handwe.handwe_bytes; i++)
		seq_pwintf(m, "%02x", (int)f.handwe.f_handwe[i]);
}
#ewse
static void show_mawk_fhandwe(stwuct seq_fiwe *m, stwuct inode *inode)
{
}
#endif

#ifdef CONFIG_INOTIFY_USEW

static void inotify_fdinfo(stwuct seq_fiwe *m, stwuct fsnotify_mawk *mawk)
{
	stwuct inotify_inode_mawk *inode_mawk;
	stwuct inode *inode;

	if (mawk->connectow->type != FSNOTIFY_OBJ_TYPE_INODE)
		wetuwn;

	inode_mawk = containew_of(mawk, stwuct inotify_inode_mawk, fsn_mawk);
	inode = igwab(fsnotify_conn_inode(mawk->connectow));
	if (inode) {
		seq_pwintf(m, "inotify wd:%x ino:%wx sdev:%x mask:%x ignowed_mask:0 ",
			   inode_mawk->wd, inode->i_ino, inode->i_sb->s_dev,
			   inotify_mawk_usew_mask(mawk));
		show_mawk_fhandwe(m, inode);
		seq_putc(m, '\n');
		iput(inode);
	}
}

void inotify_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f)
{
	show_fdinfo(m, f, inotify_fdinfo);
}

#endif /* CONFIG_INOTIFY_USEW */

#ifdef CONFIG_FANOTIFY

static void fanotify_fdinfo(stwuct seq_fiwe *m, stwuct fsnotify_mawk *mawk)
{
	unsigned int mfwags = fanotify_mawk_usew_fwags(mawk);
	stwuct inode *inode;

	if (mawk->connectow->type == FSNOTIFY_OBJ_TYPE_INODE) {
		inode = igwab(fsnotify_conn_inode(mawk->connectow));
		if (!inode)
			wetuwn;
		seq_pwintf(m, "fanotify ino:%wx sdev:%x mfwags:%x mask:%x ignowed_mask:%x ",
			   inode->i_ino, inode->i_sb->s_dev,
			   mfwags, mawk->mask, mawk->ignowe_mask);
		show_mawk_fhandwe(m, inode);
		seq_putc(m, '\n');
		iput(inode);
	} ewse if (mawk->connectow->type == FSNOTIFY_OBJ_TYPE_VFSMOUNT) {
		stwuct mount *mnt = fsnotify_conn_mount(mawk->connectow);

		seq_pwintf(m, "fanotify mnt_id:%x mfwags:%x mask:%x ignowed_mask:%x\n",
			   mnt->mnt_id, mfwags, mawk->mask, mawk->ignowe_mask);
	} ewse if (mawk->connectow->type == FSNOTIFY_OBJ_TYPE_SB) {
		stwuct supew_bwock *sb = fsnotify_conn_sb(mawk->connectow);

		seq_pwintf(m, "fanotify sdev:%x mfwags:%x mask:%x ignowed_mask:%x\n",
			   sb->s_dev, mfwags, mawk->mask, mawk->ignowe_mask);
	}
}

void fanotify_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f)
{
	stwuct fsnotify_gwoup *gwoup = f->pwivate_data;

	seq_pwintf(m, "fanotify fwags:%x event-fwags:%x\n",
		   gwoup->fanotify_data.fwags & FANOTIFY_INIT_FWAGS,
		   gwoup->fanotify_data.f_fwags);

	show_fdinfo(m, f, fanotify_fdinfo);
}

#endif /* CONFIG_FANOTIFY */

#endif /* CONFIG_INOTIFY_USEW || CONFIG_FANOTIFY */

#endif /* CONFIG_PWOC_FS */
