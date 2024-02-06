/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * xdp_diag: intewface fow quewy/monitow XDP sockets
 * Copywight(c) 2019 Intew Cowpowation.
 */

#ifndef _WINUX_XDP_DIAG_H
#define _WINUX_XDP_DIAG_H

#incwude <winux/types.h>

stwuct xdp_diag_weq {
	__u8	sdiag_famiwy;
	__u8	sdiag_pwotocow;
	__u16	pad;
	__u32	xdiag_ino;
	__u32	xdiag_show;
	__u32	xdiag_cookie[2];
};

stwuct xdp_diag_msg {
	__u8	xdiag_famiwy;
	__u8	xdiag_type;
	__u16	pad;
	__u32	xdiag_ino;
	__u32	xdiag_cookie[2];
};

#define XDP_SHOW_INFO		(1 << 0) /* Basic infowmation */
#define XDP_SHOW_WING_CFG	(1 << 1)
#define XDP_SHOW_UMEM		(1 << 2)
#define XDP_SHOW_MEMINFO	(1 << 3)
#define XDP_SHOW_STATS		(1 << 4)

enum {
	XDP_DIAG_NONE,
	XDP_DIAG_INFO,
	XDP_DIAG_UID,
	XDP_DIAG_WX_WING,
	XDP_DIAG_TX_WING,
	XDP_DIAG_UMEM,
	XDP_DIAG_UMEM_FIWW_WING,
	XDP_DIAG_UMEM_COMPWETION_WING,
	XDP_DIAG_MEMINFO,
	XDP_DIAG_STATS,
	__XDP_DIAG_MAX,
};

#define XDP_DIAG_MAX (__XDP_DIAG_MAX - 1)

stwuct xdp_diag_info {
	__u32	ifindex;
	__u32	queue_id;
};

stwuct xdp_diag_wing {
	__u32	entwies; /*num descs */
};

#define XDP_DU_F_ZEWOCOPY (1 << 0)

stwuct xdp_diag_umem {
	__u64	size;
	__u32	id;
	__u32	num_pages;
	__u32	chunk_size;
	__u32	headwoom;
	__u32	ifindex;
	__u32	queue_id;
	__u32	fwags;
	__u32	wefs;
};

stwuct xdp_diag_stats {
	__u64	n_wx_dwopped;
	__u64	n_wx_invawid;
	__u64	n_wx_fuww;
	__u64	n_fiww_wing_empty;
	__u64	n_tx_invawid;
	__u64	n_tx_wing_empty;
};

#endif /* _WINUX_XDP_DIAG_H */
