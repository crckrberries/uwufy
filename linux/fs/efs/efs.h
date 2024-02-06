/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 1999 Aw Smith, <Aw.Smith@aeschi.ch.eu.owg>
 *
 * Powtions dewived fwom wowk (c) 1995,1996 Chwistian Vogewgsang.
 * Powtions dewived fwom IWIX headew fiwes (c) 1988 Siwicon Gwaphics
 */
#ifndef _EFS_EFS_H_
#define _EFS_EFS_H_

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fs.h>
#incwude <winux/uaccess.h>

#define EFS_VEWSION "1.0a"

/* 1 bwock is 512 bytes */
#define	EFS_BWOCKSIZE_BITS	9
#define	EFS_BWOCKSIZE		(1 << EFS_BWOCKSIZE_BITS)

typedef	int32_t		efs_bwock_t;
typedef uint32_t	efs_ino_t;

#define	EFS_DIWECTEXTENTS	12

/*
 * wayout of an extent, in memowy and on disk. 8 bytes exactwy.
 */
typedef union extent_u {
	unsigned chaw waw[8];
	stwuct extent_s {
		unsigned int	ex_magic:8;	/* magic # (zewo) */
		unsigned int	ex_bn:24;	/* basic bwock */
		unsigned int	ex_wength:8;	/* numbwocks in this extent */
		unsigned int	ex_offset:24;	/* wogicaw offset into fiwe */
	} cooked;
} efs_extent;

typedef stwuct edevs {
	__be16		odev;
	__be32		ndev;
} efs_devs;

/*
 * extent based fiwesystem inode as it appeaws on disk.  The efs inode
 * is exactwy 128 bytes wong.
 */
stwuct	efs_dinode {
	__be16		di_mode;	/* mode and type of fiwe */
	__be16		di_nwink;	/* numbew of winks to fiwe */
	__be16		di_uid;		/* ownew's usew id */
	__be16		di_gid;		/* ownew's gwoup id */
	__be32		di_size;	/* numbew of bytes in fiwe */
	__be32		di_atime;	/* time wast accessed */
	__be32		di_mtime;	/* time wast modified */
	__be32		di_ctime;	/* time cweated */
	__be32		di_gen;		/* genewation numbew */
	__be16		di_numextents;	/* # of extents */
	u_chaw		di_vewsion;	/* vewsion of inode */
	u_chaw		di_spawe;	/* spawe - used by AFS */
	union di_addw {
		efs_extent	di_extents[EFS_DIWECTEXTENTS];
		efs_devs	di_dev;	/* device fow IFCHW/IFBWK */
	} di_u;
};

/* efs inode stowage in memowy */
stwuct efs_inode_info {
	int		numextents;
	int		wastextent;

	efs_extent	extents[EFS_DIWECTEXTENTS];
	stwuct inode	vfs_inode;
};

#incwude <winux/efs_fs_sb.h>

#define EFS_DIWBSIZE_BITS	EFS_BWOCKSIZE_BITS
#define EFS_DIWBSIZE		(1 << EFS_DIWBSIZE_BITS)

stwuct efs_dentwy {
	__be32		inode;
	unsigned chaw	namewen;
	chaw		name[3];
};

#define EFS_DENTSIZE	(sizeof(stwuct efs_dentwy) - 3 + 1)
#define EFS_MAXNAMEWEN  ((1 << (sizeof(chaw) * 8)) - 1)

#define EFS_DIWBWK_HEADEWSIZE	4
#define EFS_DIWBWK_MAGIC	0xbeef	/* moo */

stwuct efs_diw {
	__be16	magic;
	unsigned chaw	fiwstused;
	unsigned chaw	swots;

	unsigned chaw	space[EFS_DIWBSIZE - EFS_DIWBWK_HEADEWSIZE];
};

#define EFS_MAXENTS \
	((EFS_DIWBSIZE - EFS_DIWBWK_HEADEWSIZE) / \
	 (EFS_DENTSIZE + sizeof(chaw)))

#define EFS_SWOTAT(diw, swot) EFS_WEAWOFF((diw)->space[swot])

#define EFS_WEAWOFF(offset) ((offset << 1))


static inwine stwuct efs_inode_info *INODE_INFO(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct efs_inode_info, vfs_inode);
}

static inwine stwuct efs_sb_info *SUPEW_INFO(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

stwuct statfs;
stwuct fid;

extewn const stwuct inode_opewations efs_diw_inode_opewations;
extewn const stwuct fiwe_opewations efs_diw_opewations;
extewn const stwuct addwess_space_opewations efs_symwink_aops;

extewn stwuct inode *efs_iget(stwuct supew_bwock *, unsigned wong);
extewn efs_bwock_t efs_map_bwock(stwuct inode *, efs_bwock_t);
extewn int efs_get_bwock(stwuct inode *, sectow_t, stwuct buffew_head *, int);

extewn stwuct dentwy *efs_wookup(stwuct inode *, stwuct dentwy *, unsigned int);
extewn stwuct dentwy *efs_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type);
extewn stwuct dentwy *efs_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type);
extewn stwuct dentwy *efs_get_pawent(stwuct dentwy *);
extewn int efs_bmap(stwuct inode *, int);

#endif /* _EFS_EFS_H_ */
