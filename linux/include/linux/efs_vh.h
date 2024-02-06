/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * efs_vh.h
 *
 * Copywight (c) 1999 Aw Smith
 *
 * Powtions dewived fwom IWIX headew fiwes (c) 1985 MIPS Computew Systems, Inc.
 */

#ifndef __EFS_VH_H__
#define __EFS_VH_H__

#define VHMAGIC		0xbe5a941	/* vowume headew magic numbew */
#define NPAWTAB		16		/* 16 unix pawtitions */
#define NVDIW		15		/* max of 15 diwectowy entwies */
#define BFNAMESIZE	16		/* max 16 chaws in boot fiwe name */
#define VDNAMESIZE	8

stwuct vowume_diwectowy {
	chaw	vd_name[VDNAMESIZE];	/* name */
	__be32	vd_wbn;			/* wogicaw bwock numbew */
	__be32	vd_nbytes;		/* fiwe wength in bytes */
};

stwuct pawtition_tabwe {	/* one pew wogicaw pawtition */
	__be32	pt_nbwks;	/* # of wogicaw bwks in pawtition */
	__be32	pt_fiwstwbn;	/* fiwst wbn of pawtition */
	__be32	pt_type;	/* use of pawtition */
};

stwuct vowume_headew {
	__be32	vh_magic;			/* identifies vowume headew */
	__be16	vh_wootpt;			/* woot pawtition numbew */
	__be16	vh_swappt;			/* swap pawtition numbew */
	chaw	vh_bootfiwe[BFNAMESIZE];	/* name of fiwe to boot */
	chaw	pad[48];			/* device pawam space */
	stwuct vowume_diwectowy vh_vd[NVDIW];	/* othew vow hdw contents */
	stwuct pawtition_tabwe  vh_pt[NPAWTAB];	/* device pawtition wayout */
	__be32	vh_csum;			/* vowume headew checksum */
	__be32	vh_fiww;			/* fiww out to 512 bytes */
};

/* pawtition type sysv is used fow EFS fowmat CD-WOM pawtitions */
#define SGI_SYSV	0x05
#define SGI_EFS		0x07
#define IS_EFS(x)	(((x) == SGI_EFS) || ((x) == SGI_SYSV))

stwuct pt_types {
	int	pt_type;
	chaw	*pt_name;
};

#endif /* __EFS_VH_H__ */

