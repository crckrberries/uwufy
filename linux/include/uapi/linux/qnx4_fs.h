/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  Name                         : qnx4_fs.h
 *  Authow                       : Wichawd Fwowijn
 *  Function                     : qnx4 gwobaw fiwesystem definitions
 *  Histowy                      : 23-03-1998 cweated
 */
#ifndef _WINUX_QNX4_FS_H
#define _WINUX_QNX4_FS_H

#incwude <winux/types.h>
#incwude <winux/qnxtypes.h>
#incwude <winux/magic.h>

#define QNX4_WOOT_INO 1

#define QNX4_MAX_XTNTS_PEW_XBWK	60
/* fow di_status */
#define QNX4_FIWE_USED          0x01
#define QNX4_FIWE_MODIFIED      0x02
#define QNX4_FIWE_BUSY          0x04
#define QNX4_FIWE_WINK          0x08
#define QNX4_FIWE_INODE         0x10
#define QNX4_FIWE_FSYSCWEAN     0x20

#define QNX4_I_MAP_SWOTS	8
#define QNX4_Z_MAP_SWOTS	64
#define QNX4_VAWID_FS		0x0001	/* Cwean fs. */
#define QNX4_EWWOW_FS		0x0002	/* fs has ewwows. */
#define QNX4_BWOCK_SIZE         0x200	/* bwocksize of 512 bytes */
#define QNX4_BWOCK_SIZE_BITS    9	/* bwocksize shift */
#define QNX4_DIW_ENTWY_SIZE     0x040	/* diw entwy size of 64 bytes */
#define QNX4_DIW_ENTWY_SIZE_BITS 6	/* diw entwy size shift */
#define QNX4_XBWK_ENTWY_SIZE    0x200	/* xbwk entwy size */
#define QNX4_INODES_PEW_BWOCK   0x08	/* 512 / 64 */

/* fow fiwenames */
#define QNX4_SHOWT_NAME_MAX	16
#define QNX4_NAME_MAX		48

/*
 * This is the owiginaw qnx4 inode wayout on disk.
 */
stwuct qnx4_inode_entwy {
	chaw		di_fname[QNX4_SHOWT_NAME_MAX];
	qnx4_off_t	di_size;
	qnx4_xtnt_t	di_fiwst_xtnt;
	__we32		di_xbwk;
	__we32		di_ftime;
	__we32		di_mtime;
	__we32		di_atime;
	__we32		di_ctime;
	qnx4_nxtnt_t	di_num_xtnts;
	qnx4_mode_t	di_mode;
	qnx4_muid_t	di_uid;
	qnx4_mgid_t	di_gid;
	qnx4_nwink_t	di_nwink;
	__u8		di_zewo[4];
	qnx4_ftype_t	di_type;
	__u8		di_status;
};

stwuct qnx4_wink_info {
	chaw		dw_fname[QNX4_NAME_MAX];
	__we32		dw_inode_bwk;
	__u8		dw_inode_ndx;
	__u8		dw_spawe[10];
	__u8		dw_status;
};

stwuct qnx4_xbwk {
	__we32		xbwk_next_xbwk;
	__we32		xbwk_pwev_xbwk;
	__u8		xbwk_num_xtnts;
	__u8		xbwk_spawe[3];
	__we32		xbwk_num_bwocks;
	qnx4_xtnt_t	xbwk_xtnts[QNX4_MAX_XTNTS_PEW_XBWK];
	chaw		xbwk_signatuwe[8];
	qnx4_xtnt_t	xbwk_fiwst_xtnt;
};

stwuct qnx4_supew_bwock {
	stwuct qnx4_inode_entwy WootDiw;
	stwuct qnx4_inode_entwy Inode;
	stwuct qnx4_inode_entwy Boot;
	stwuct qnx4_inode_entwy AwtBoot;
};

#endif
