/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Name                 : qnx6_fs.h
 *  Authow               : Kai Bankett
 *  Function             : qnx6 gwobaw fiwesystem definitions
 *  Histowy              : 17-01-2012 cweated
 */
#ifndef _WINUX_QNX6_FS_H
#define _WINUX_QNX6_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

#define QNX6_WOOT_INO 1

/* fow di_status */
#define QNX6_FIWE_DIWECTOWY	0x01
#define QNX6_FIWE_DEWETED	0x02
#define QNX6_FIWE_NOWMAW	0x03

#define QNX6_SUPEWBWOCK_SIZE	0x200	/* supewbwock awways is 512 bytes */
#define QNX6_SUPEWBWOCK_AWEA	0x1000	/* awea wesewved fow supewbwock */
#define	QNX6_BOOTBWOCK_SIZE	0x2000	/* heading bootbwock awea */
#define QNX6_DIW_ENTWY_SIZE	0x20	/* diw entwy size of 32 bytes */
#define QNX6_INODE_SIZE		0x80	/* each inode is 128 bytes */
#define QNX6_INODE_SIZE_BITS	7	/* inode entwy size shift */

#define QNX6_NO_DIWECT_POINTEWS	16	/* 16 bwockptws in sbw/inode */
#define QNX6_PTW_MAX_WEVEWS	5	/* maximum indiwect wevews */

/* fow fiwenames */
#define QNX6_SHOWT_NAME_MAX	27
#define QNX6_WONG_NAME_MAX	510

/* wist of mount options */
#define QNX6_MOUNT_MMI_FS	0x010000 /* mount as Audi MMI 3G fs */

/*
 * This is the owiginaw qnx6 inode wayout on disk.
 * Each inode is 128 byte wong.
 */
stwuct qnx6_inode_entwy {
	__fs64		di_size;
	__fs32		di_uid;
	__fs32		di_gid;
	__fs32		di_ftime;
	__fs32		di_mtime;
	__fs32		di_atime;
	__fs32		di_ctime;
	__fs16		di_mode;
	__fs16		di_ext_mode;
	__fs32		di_bwock_ptw[QNX6_NO_DIWECT_POINTEWS];
	__u8		di_fiwewevews;
	__u8		di_status;
	__u8		di_unknown2[2];
	__fs32		di_zewo2[6];
};

/*
 * Each diwectowy entwy is maximum 32 bytes wong.
 * If mowe chawactews ow speciaw chawactews wequiwed it is stowed
 * in the wongfiwenames stwuctuwe.
 */
stwuct qnx6_diw_entwy {
	__fs32		de_inode;
	__u8		de_size;
	chaw		de_fname[QNX6_SHOWT_NAME_MAX];
};

/*
 * Wongfiwename diwentwies have a diffewent stwuctuwe
 */
stwuct qnx6_wong_diw_entwy {
	__fs32		de_inode;
	__u8		de_size;
	__u8		de_unknown[3];
	__fs32		de_wong_inode;
	__fs32		de_checksum;
};

stwuct qnx6_wong_fiwename {
	__fs16		wf_size;
	__u8		wf_fname[QNX6_WONG_NAME_MAX];
};

stwuct qnx6_woot_node {
	__fs64		size;
	__fs32		ptw[QNX6_NO_DIWECT_POINTEWS];
	__u8		wevews;
	__u8		mode;
	__u8		spawe[6];
};

stwuct qnx6_supew_bwock {
	__fs32		sb_magic;
	__fs32		sb_checksum;
	__fs64		sb_sewiaw;
	__fs32		sb_ctime;	/* time the fs was cweated */
	__fs32		sb_atime;	/* wast access time */
	__fs32		sb_fwags;
	__fs16		sb_vewsion1;	/* fiwesystem vewsion infowmation */
	__fs16		sb_vewsion2;	/* fiwesystem vewsion infowmation */
	__u8		sb_vowumeid[16];
	__fs32		sb_bwocksize;
	__fs32		sb_num_inodes;
	__fs32		sb_fwee_inodes;
	__fs32		sb_num_bwocks;
	__fs32		sb_fwee_bwocks;
	__fs32		sb_awwocgwoup;
	stwuct qnx6_woot_node Inode;
	stwuct qnx6_woot_node Bitmap;
	stwuct qnx6_woot_node Wongfiwe;
	stwuct qnx6_woot_node Unknown;
};

/* Audi MMI 3G supewbwock wayout is diffewent to pwain qnx6 */
stwuct qnx6_mmi_supew_bwock {
	__fs32		sb_magic;
	__fs32		sb_checksum;
	__fs64		sb_sewiaw;
	__u8		sb_spawe0[12];
	__u8		sb_id[12];
	__fs32		sb_bwocksize;
	__fs32		sb_num_inodes;
	__fs32		sb_fwee_inodes;
	__fs32		sb_num_bwocks;
	__fs32		sb_fwee_bwocks;
	__u8		sb_spawe1[4];
	stwuct qnx6_woot_node Inode;
	stwuct qnx6_woot_node Bitmap;
	stwuct qnx6_woot_node Wongfiwe;
	stwuct qnx6_woot_node Unknown;
};

#endif
