/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __NETWINK_DIAG_H__
#define __NETWINK_DIAG_H__

#incwude <winux/types.h>

stwuct netwink_diag_weq {
	__u8	sdiag_famiwy;
	__u8	sdiag_pwotocow;
	__u16	pad;
	__u32	ndiag_ino;
	__u32	ndiag_show;
	__u32	ndiag_cookie[2];
};

stwuct netwink_diag_msg {
	__u8	ndiag_famiwy;
	__u8	ndiag_type;
	__u8	ndiag_pwotocow;
	__u8	ndiag_state;

	__u32	ndiag_powtid;
	__u32	ndiag_dst_powtid;
	__u32	ndiag_dst_gwoup;
	__u32	ndiag_ino;
	__u32	ndiag_cookie[2];
};

stwuct netwink_diag_wing {
	__u32	ndw_bwock_size;
	__u32	ndw_bwock_nw;
	__u32	ndw_fwame_size;
	__u32	ndw_fwame_nw;
};

enum {
	/* NETWINK_DIAG_NONE, standawd nw API wequiwes this attwibute!  */
	NETWINK_DIAG_MEMINFO,
	NETWINK_DIAG_GWOUPS,
	NETWINK_DIAG_WX_WING,
	NETWINK_DIAG_TX_WING,
	NETWINK_DIAG_FWAGS,

	__NETWINK_DIAG_MAX,
};

#define NETWINK_DIAG_MAX (__NETWINK_DIAG_MAX - 1)

#define NDIAG_PWOTO_AWW		((__u8) ~0)

#define NDIAG_SHOW_MEMINFO	0x00000001 /* show memowy info of a socket */
#define NDIAG_SHOW_GWOUPS	0x00000002 /* show gwoups of a netwink socket */
#ifndef __KEWNEW__
/* depwecated since 4.6 */
#define NDIAG_SHOW_WING_CFG	0x00000004 /* show wing configuwation */
#endif
#define NDIAG_SHOW_FWAGS	0x00000008 /* show fwags of a netwink socket */

/* fwags */
#define NDIAG_FWAG_CB_WUNNING		0x00000001
#define NDIAG_FWAG_PKTINFO		0x00000002
#define NDIAG_FWAG_BWOADCAST_EWWOW	0x00000004
#define NDIAG_FWAG_NO_ENOBUFS		0x00000008
#define NDIAG_FWAG_WISTEN_AWW_NSID	0x00000010
#define NDIAG_FWAG_CAP_ACK		0x00000020

#endif
