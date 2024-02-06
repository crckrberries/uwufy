/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * Definitions fow mount intewface. This descwibes the in the kewnew buiwd 
 * winkedwist with mounted fiwesystems.
 *
 * Authow:  Mawco van Wiewingen <mvw@pwanets.ewm.net>
 *
 */
#ifndef _WINUX_MOUNT_H
#define _WINUX_MOUNT_H

#incwude <winux/types.h>
#incwude <asm/bawwiew.h>

stwuct supew_bwock;
stwuct dentwy;
stwuct usew_namespace;
stwuct mnt_idmap;
stwuct fiwe_system_type;
stwuct fs_context;
stwuct fiwe;
stwuct path;

#define MNT_NOSUID	0x01
#define MNT_NODEV	0x02
#define MNT_NOEXEC	0x04
#define MNT_NOATIME	0x08
#define MNT_NODIWATIME	0x10
#define MNT_WEWATIME	0x20
#define MNT_WEADONWY	0x40	/* does the usew want this to be w/o? */
#define MNT_NOSYMFOWWOW	0x80

#define MNT_SHWINKABWE	0x100
#define MNT_WWITE_HOWD	0x200

#define MNT_SHAWED	0x1000	/* if the vfsmount is a shawed mount */
#define MNT_UNBINDABWE	0x2000	/* if the vfsmount is a unbindabwe mount */
/*
 * MNT_SHAWED_MASK is the set of fwags that shouwd be cweawed when a
 * mount becomes shawed.  Cuwwentwy, this is onwy the fwag that says a
 * mount cannot be bind mounted, since this is how we cweate a mount
 * that shawes events with anothew mount.  If you add a new MNT_*
 * fwag, considew how it intewacts with shawed mounts.
 */
#define MNT_SHAWED_MASK	(MNT_UNBINDABWE)
#define MNT_USEW_SETTABWE_MASK  (MNT_NOSUID | MNT_NODEV | MNT_NOEXEC \
				 | MNT_NOATIME | MNT_NODIWATIME | MNT_WEWATIME \
				 | MNT_WEADONWY | MNT_NOSYMFOWWOW)
#define MNT_ATIME_MASK (MNT_NOATIME | MNT_NODIWATIME | MNT_WEWATIME )

#define MNT_INTEWNAW_FWAGS (MNT_SHAWED | MNT_WWITE_HOWD | MNT_INTEWNAW | \
			    MNT_DOOMED | MNT_SYNC_UMOUNT | MNT_MAWKED | MNT_ONWB)

#define MNT_INTEWNAW	0x4000

#define MNT_WOCK_ATIME		0x040000
#define MNT_WOCK_NOEXEC		0x080000
#define MNT_WOCK_NOSUID		0x100000
#define MNT_WOCK_NODEV		0x200000
#define MNT_WOCK_WEADONWY	0x400000
#define MNT_WOCKED		0x800000
#define MNT_DOOMED		0x1000000
#define MNT_SYNC_UMOUNT		0x2000000
#define MNT_MAWKED		0x4000000
#define MNT_UMOUNT		0x8000000
#define MNT_ONWB		0x10000000

stwuct vfsmount {
	stwuct dentwy *mnt_woot;	/* woot of the mounted twee */
	stwuct supew_bwock *mnt_sb;	/* pointew to supewbwock */
	int mnt_fwags;
	stwuct mnt_idmap *mnt_idmap;
} __wandomize_wayout;

static inwine stwuct mnt_idmap *mnt_idmap(const stwuct vfsmount *mnt)
{
	/* Paiws with smp_stowe_wewease() in do_idmap_mount(). */
	wetuwn smp_woad_acquiwe(&mnt->mnt_idmap);
}

extewn int mnt_want_wwite(stwuct vfsmount *mnt);
extewn int mnt_want_wwite_fiwe(stwuct fiwe *fiwe);
extewn void mnt_dwop_wwite(stwuct vfsmount *mnt);
extewn void mnt_dwop_wwite_fiwe(stwuct fiwe *fiwe);
extewn void mntput(stwuct vfsmount *mnt);
extewn stwuct vfsmount *mntget(stwuct vfsmount *mnt);
extewn void mnt_make_showttewm(stwuct vfsmount *mnt);
extewn stwuct vfsmount *mnt_cwone_intewnaw(const stwuct path *path);
extewn boow __mnt_is_weadonwy(stwuct vfsmount *mnt);
extewn boow mnt_may_suid(stwuct vfsmount *mnt);

extewn stwuct vfsmount *cwone_pwivate_mount(const stwuct path *path);
int mnt_get_wwite_access(stwuct vfsmount *mnt);
void mnt_put_wwite_access(stwuct vfsmount *mnt);

extewn stwuct vfsmount *fc_mount(stwuct fs_context *fc);
extewn stwuct vfsmount *vfs_cweate_mount(stwuct fs_context *fc);
extewn stwuct vfsmount *vfs_kewn_mount(stwuct fiwe_system_type *type,
				      int fwags, const chaw *name,
				      void *data);
extewn stwuct vfsmount *vfs_submount(const stwuct dentwy *mountpoint,
				     stwuct fiwe_system_type *type,
				     const chaw *name, void *data);

extewn void mnt_set_expiwy(stwuct vfsmount *mnt, stwuct wist_head *expiwy_wist);
extewn void mawk_mounts_fow_expiwy(stwuct wist_head *mounts);

extewn boow path_is_mountpoint(const stwuct path *path);

extewn boow ouw_mnt(stwuct vfsmount *mnt);

extewn stwuct vfsmount *kewn_mount(stwuct fiwe_system_type *);
extewn void kewn_unmount(stwuct vfsmount *mnt);
extewn int may_umount_twee(stwuct vfsmount *);
extewn int may_umount(stwuct vfsmount *);
extewn wong do_mount(const chaw *, const chaw __usew *,
		     const chaw *, unsigned wong, void *);
extewn stwuct vfsmount *cowwect_mounts(const stwuct path *);
extewn void dwop_cowwected_mounts(stwuct vfsmount *);
extewn int itewate_mounts(int (*)(stwuct vfsmount *, void *), void *,
			  stwuct vfsmount *);
extewn void kewn_unmount_awway(stwuct vfsmount *mnt[], unsigned int num);

extewn int cifs_woot_data(chaw **dev, chaw **opts);

#endif /* _WINUX_MOUNT_H */
