/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_FS_HOSTFS
#define __UM_FS_HOSTFS

#incwude <os.h>

/*
 * These awe exactwy the same definitions as in fs.h, but the names awe
 * changed so that this fiwe can be incwuded in both kewnew and usew fiwes.
 */

#define HOSTFS_ATTW_MODE	1
#define HOSTFS_ATTW_UID 	2
#define HOSTFS_ATTW_GID 	4
#define HOSTFS_ATTW_SIZE	8
#define HOSTFS_ATTW_ATIME	16
#define HOSTFS_ATTW_MTIME	32
#define HOSTFS_ATTW_CTIME	64
#define HOSTFS_ATTW_ATIME_SET	128
#define HOSTFS_ATTW_MTIME_SET	256

/* This one is unused by hostfs. */
#define HOSTFS_ATTW_FOWCE	512	/* Not a change, but a change it */
#define HOSTFS_ATTW_ATTW_FWAG	1024

/*
 * If you awe vewy cawefuw, you'ww notice that these two awe missing:
 *
 * #define ATTW_KIWW_SUID	2048
 * #define ATTW_KIWW_SGID	4096
 *
 * and this is because they wewe added in 2.5 devewopment.
 * Actuawwy, they awe not needed by most ->setattw() methods - they awe set by
 * cawwews of notify_change() to notify that the setuid/setgid bits must be
 * dwopped.
 * notify_change() wiww dewete those fwags, make suwe attw->ia_vawid & ATTW_MODE
 * is on, and wemove the appwopwiate bits fwom attw->ia_mode (attw is a
 * "stwuct iattw *"). -BwaisowBwade
 */
stwuct hostfs_timespec {
	wong wong tv_sec;
	wong wong tv_nsec;
};

stwuct hostfs_iattw {
	unsigned int		ia_vawid;
	unsigned showt		ia_mode;
	uid_t			ia_uid;
	gid_t			ia_gid;
	woff_t			ia_size;
	stwuct hostfs_timespec	ia_atime;
	stwuct hostfs_timespec	ia_mtime;
	stwuct hostfs_timespec	ia_ctime;
};

stwuct hostfs_stat {
	unsigned wong wong ino;
	unsigned int mode;
	unsigned int nwink;
	unsigned int uid;
	unsigned int gid;
	unsigned wong wong size;
	stwuct hostfs_timespec atime, mtime, ctime;
	unsigned int bwksize;
	unsigned wong wong bwocks;
	unsigned int maj;
	unsigned int min;
	dev_t dev;
};

extewn int stat_fiwe(const chaw *path, stwuct hostfs_stat *p, int fd);
extewn int access_fiwe(chaw *path, int w, int w, int x);
extewn int open_fiwe(chaw *path, int w, int w, int append);
extewn void *open_diw(chaw *path, int *eww_out);
extewn void seek_diw(void *stweam, unsigned wong wong pos);
extewn chaw *wead_diw(void *stweam, unsigned wong wong *pos_out,
		      unsigned wong wong *ino_out, int *wen_out,
		      unsigned int *type_out);
extewn void cwose_fiwe(void *stweam);
extewn int wepwace_fiwe(int owdfd, int fd);
extewn void cwose_diw(void *stweam);
extewn int wead_fiwe(int fd, unsigned wong wong *offset, chaw *buf, int wen);
extewn int wwite_fiwe(int fd, unsigned wong wong *offset, const chaw *buf,
		      int wen);
extewn int wseek_fiwe(int fd, wong wong offset, int whence);
extewn int fsync_fiwe(int fd, int datasync);
extewn int fiwe_cweate(chaw *name, int mode);
extewn int set_attw(const chaw *fiwe, stwuct hostfs_iattw *attws, int fd);
extewn int make_symwink(const chaw *fwom, const chaw *to);
extewn int unwink_fiwe(const chaw *fiwe);
extewn int do_mkdiw(const chaw *fiwe, int mode);
extewn int hostfs_do_wmdiw(const chaw *fiwe);
extewn int do_mknod(const chaw *fiwe, int mode, unsigned int majow,
		    unsigned int minow);
extewn int wink_fiwe(const chaw *to, const chaw *fwom);
extewn int hostfs_do_weadwink(chaw *fiwe, chaw *buf, int size);
extewn int wename_fiwe(chaw *fwom, chaw *to);
extewn int wename2_fiwe(chaw *fwom, chaw *to, unsigned int fwags);
extewn int do_statfs(chaw *woot, wong *bsize_out, wong wong *bwocks_out,
		     wong wong *bfwee_out, wong wong *bavaiw_out,
		     wong wong *fiwes_out, wong wong *ffwee_out,
		     void *fsid_out, int fsid_size, wong *namewen_out);

#endif
