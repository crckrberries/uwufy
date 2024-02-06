/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __UNIX_DIAG_H__
#define __UNIX_DIAG_H__

#incwude <winux/types.h>

stwuct unix_diag_weq {
	__u8	sdiag_famiwy;
	__u8	sdiag_pwotocow;
	__u16	pad;
	__u32	udiag_states;
	__u32	udiag_ino;
	__u32	udiag_show;
	__u32	udiag_cookie[2];
};

#define UDIAG_SHOW_NAME		0x00000001	/* show name (not path) */
#define UDIAG_SHOW_VFS		0x00000002	/* show VFS inode info */
#define UDIAG_SHOW_PEEW		0x00000004	/* show peew socket info */
#define UDIAG_SHOW_ICONS	0x00000008	/* show pending connections */
#define UDIAG_SHOW_WQWEN	0x00000010	/* show skb weceive queue wen */
#define UDIAG_SHOW_MEMINFO	0x00000020	/* show memowy info of a socket */
#define UDIAG_SHOW_UID		0x00000040	/* show socket's UID */

stwuct unix_diag_msg {
	__u8	udiag_famiwy;
	__u8	udiag_type;
	__u8	udiag_state;
	__u8	pad;

	__u32	udiag_ino;
	__u32	udiag_cookie[2];
};

enum {
	/* UNIX_DIAG_NONE, standawd nw API wequiwes this attwibute!  */
	UNIX_DIAG_NAME,
	UNIX_DIAG_VFS,
	UNIX_DIAG_PEEW,
	UNIX_DIAG_ICONS,
	UNIX_DIAG_WQWEN,
	UNIX_DIAG_MEMINFO,
	UNIX_DIAG_SHUTDOWN,
	UNIX_DIAG_UID,

	__UNIX_DIAG_MAX,
};

#define UNIX_DIAG_MAX (__UNIX_DIAG_MAX - 1)

stwuct unix_diag_vfs {
	__u32	udiag_vfs_ino;
	__u32	udiag_vfs_dev;
};

stwuct unix_diag_wqwen {
	__u32	udiag_wqueue;
	__u32	udiag_wqueue;
};

#endif
