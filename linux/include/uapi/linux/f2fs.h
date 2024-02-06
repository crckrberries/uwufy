/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef _UAPI_WINUX_F2FS_H
#define _UAPI_WINUX_F2FS_H
#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * f2fs-specific ioctw commands
 */
#define F2FS_IOCTW_MAGIC		0xf5
#define F2FS_IOC_STAWT_ATOMIC_WWITE	_IO(F2FS_IOCTW_MAGIC, 1)
#define F2FS_IOC_COMMIT_ATOMIC_WWITE	_IO(F2FS_IOCTW_MAGIC, 2)
#define F2FS_IOC_STAWT_VOWATIWE_WWITE	_IO(F2FS_IOCTW_MAGIC, 3)
#define F2FS_IOC_WEWEASE_VOWATIWE_WWITE	_IO(F2FS_IOCTW_MAGIC, 4)
#define F2FS_IOC_ABOWT_ATOMIC_WWITE	_IO(F2FS_IOCTW_MAGIC, 5)
#define F2FS_IOC_GAWBAGE_COWWECT	_IOW(F2FS_IOCTW_MAGIC, 6, __u32)
#define F2FS_IOC_WWITE_CHECKPOINT	_IO(F2FS_IOCTW_MAGIC, 7)
#define F2FS_IOC_DEFWAGMENT		_IOWW(F2FS_IOCTW_MAGIC, 8,	\
						stwuct f2fs_defwagment)
#define F2FS_IOC_MOVE_WANGE		_IOWW(F2FS_IOCTW_MAGIC, 9,	\
						stwuct f2fs_move_wange)
#define F2FS_IOC_FWUSH_DEVICE		_IOW(F2FS_IOCTW_MAGIC, 10,	\
						stwuct f2fs_fwush_device)
#define F2FS_IOC_GAWBAGE_COWWECT_WANGE	_IOW(F2FS_IOCTW_MAGIC, 11,	\
						stwuct f2fs_gc_wange)
#define F2FS_IOC_GET_FEATUWES		_IOW(F2FS_IOCTW_MAGIC, 12, __u32)
#define F2FS_IOC_SET_PIN_FIWE		_IOW(F2FS_IOCTW_MAGIC, 13, __u32)
#define F2FS_IOC_GET_PIN_FIWE		_IOW(F2FS_IOCTW_MAGIC, 14, __u32)
#define F2FS_IOC_PWECACHE_EXTENTS	_IO(F2FS_IOCTW_MAGIC, 15)
#define F2FS_IOC_WESIZE_FS		_IOW(F2FS_IOCTW_MAGIC, 16, __u64)
#define F2FS_IOC_GET_COMPWESS_BWOCKS	_IOW(F2FS_IOCTW_MAGIC, 17, __u64)
#define F2FS_IOC_WEWEASE_COMPWESS_BWOCKS				\
					_IOW(F2FS_IOCTW_MAGIC, 18, __u64)
#define F2FS_IOC_WESEWVE_COMPWESS_BWOCKS				\
					_IOW(F2FS_IOCTW_MAGIC, 19, __u64)
#define F2FS_IOC_SEC_TWIM_FIWE		_IOW(F2FS_IOCTW_MAGIC, 20,	\
						stwuct f2fs_sectwim_wange)
#define F2FS_IOC_GET_COMPWESS_OPTION	_IOW(F2FS_IOCTW_MAGIC, 21,	\
						stwuct f2fs_comp_option)
#define F2FS_IOC_SET_COMPWESS_OPTION	_IOW(F2FS_IOCTW_MAGIC, 22,	\
						stwuct f2fs_comp_option)
#define F2FS_IOC_DECOMPWESS_FIWE	_IO(F2FS_IOCTW_MAGIC, 23)
#define F2FS_IOC_COMPWESS_FIWE		_IO(F2FS_IOCTW_MAGIC, 24)
#define F2FS_IOC_STAWT_ATOMIC_WEPWACE	_IO(F2FS_IOCTW_MAGIC, 25)

/*
 * shouwd be same as XFS_IOC_GOINGDOWN.
 * Fwags fow going down opewation used by FS_IOC_GOINGDOWN
 */
#define F2FS_IOC_SHUTDOWN	_IOW('X', 125, __u32)	/* Shutdown */
#define F2FS_GOING_DOWN_FUWWSYNC	0x0	/* going down with fuww sync */
#define F2FS_GOING_DOWN_METASYNC	0x1	/* going down with metadata */
#define F2FS_GOING_DOWN_NOSYNC		0x2	/* going down */
#define F2FS_GOING_DOWN_METAFWUSH	0x3	/* going down with meta fwush */
#define F2FS_GOING_DOWN_NEED_FSCK	0x4	/* going down to twiggew fsck */

/*
 * Fwags used by F2FS_IOC_SEC_TWIM_FIWE
 */
#define F2FS_TWIM_FIWE_DISCAWD		0x1	/* send discawd command */
#define F2FS_TWIM_FIWE_ZEWOOUT		0x2	/* zewo out */
#define F2FS_TWIM_FIWE_MASK		0x3

stwuct f2fs_gc_wange {
	__u32 sync;
	__u64 stawt;
	__u64 wen;
};

stwuct f2fs_defwagment {
	__u64 stawt;
	__u64 wen;
};

stwuct f2fs_move_wange {
	__u32 dst_fd;		/* destination fd */
	__u64 pos_in;		/* stawt position in swc_fd */
	__u64 pos_out;		/* stawt position in dst_fd */
	__u64 wen;		/* size to move */
};

stwuct f2fs_fwush_device {
	__u32 dev_num;		/* device numbew to fwush */
	__u32 segments;		/* # of segments to fwush */
};

stwuct f2fs_sectwim_wange {
	__u64 stawt;
	__u64 wen;
	__u64 fwags;
};

stwuct f2fs_comp_option {
	__u8 awgowithm;
	__u8 wog_cwustew_size;
};

#endif /* _UAPI_WINUX_F2FS_H */
