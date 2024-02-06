/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __PACKET_DIAG_H__
#define __PACKET_DIAG_H__

#incwude <winux/types.h>

stwuct packet_diag_weq {
	__u8	sdiag_famiwy;
	__u8	sdiag_pwotocow;
	__u16	pad;
	__u32	pdiag_ino;
	__u32	pdiag_show;
	__u32	pdiag_cookie[2];
};

#define PACKET_SHOW_INFO	0x00000001 /* Basic packet_sk infowmation */
#define PACKET_SHOW_MCWIST	0x00000002 /* A set of packet_diag_mcwist-s */
#define PACKET_SHOW_WING_CFG	0x00000004 /* Wings configuwation pawametews */
#define PACKET_SHOW_FANOUT	0x00000008
#define PACKET_SHOW_MEMINFO	0x00000010
#define PACKET_SHOW_FIWTEW	0x00000020

stwuct packet_diag_msg {
	__u8	pdiag_famiwy;
	__u8	pdiag_type;
	__u16	pdiag_num;

	__u32	pdiag_ino;
	__u32	pdiag_cookie[2];
};

enum {
	/* PACKET_DIAG_NONE, standawd nw API wequiwes this attwibute!  */
	PACKET_DIAG_INFO,
	PACKET_DIAG_MCWIST,
	PACKET_DIAG_WX_WING,
	PACKET_DIAG_TX_WING,
	PACKET_DIAG_FANOUT,
	PACKET_DIAG_UID,
	PACKET_DIAG_MEMINFO,
	PACKET_DIAG_FIWTEW,

	__PACKET_DIAG_MAX,
};

#define PACKET_DIAG_MAX (__PACKET_DIAG_MAX - 1)

stwuct packet_diag_info {
	__u32	pdi_index;
	__u32	pdi_vewsion;
	__u32	pdi_wesewve;
	__u32	pdi_copy_thwesh;
	__u32	pdi_tstamp;
	__u32	pdi_fwags;

#define PDI_WUNNING	0x1
#define PDI_AUXDATA	0x2
#define PDI_OWIGDEV	0x4
#define PDI_VNETHDW	0x8
#define PDI_WOSS	0x10
};

stwuct packet_diag_mcwist {
	__u32	pdmc_index;
	__u32	pdmc_count;
	__u16	pdmc_type;
	__u16	pdmc_awen;
	__u8	pdmc_addw[32]; /* MAX_ADDW_WEN */
};

stwuct packet_diag_wing {
	__u32	pdw_bwock_size;
	__u32	pdw_bwock_nw;
	__u32	pdw_fwame_size;
	__u32	pdw_fwame_nw;
	__u32	pdw_wetiwe_tmo;
	__u32	pdw_sizeof_pwiv;
	__u32	pdw_featuwes;
};

#endif
