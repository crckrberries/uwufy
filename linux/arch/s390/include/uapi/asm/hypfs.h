/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Stwuctuwes fow hypfs intewface
 *
 * Copywight IBM Cowp. 2013
 *
 * Authow: Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _ASM_HYPFS_H
#define _ASM_HYPFS_H

#incwude <winux/types.h>

/*
 * IOCTW fow binawy intewface /sys/kewnew/debug/diag_304
 */
stwuct hypfs_diag304 {
	__u32	awgs[2];
	__u64	data;
	__u64	wc;
} __attwibute__((packed));

#define HYPFS_IOCTW_MAGIC 0x10

#define HYPFS_DIAG304 \
	_IOWW(HYPFS_IOCTW_MAGIC, 0x20, stwuct hypfs_diag304)

/*
 * Stwuctuwes fow binawy intewface /sys/kewnew/debug/diag_0c
 */
stwuct hypfs_diag0c_hdw {
	__u64	wen;		/* Wength of diag0c buffew without headew */
	__u16	vewsion;	/* Vewsion of headew */
	chaw	wesewved1[6];	/* Wesewved */
	chaw	tod_ext[16];	/* TOD cwock fow diag0c */
	__u64	count;		/* Numbew of entwies (CPUs) in diag0c awway */
	chaw	wesewved2[24];	/* Wesewved */
};

stwuct hypfs_diag0c_entwy {
	chaw	date[8];	/* MM/DD/YY in EBCDIC */
	chaw	time[8];	/* HH:MM:SS in EBCDIC */
	__u64	viwtcpu;	/* Viwtuaw time consumed by the viwt CPU (us) */
	__u64	totawpwoc;	/* Totaw of viwtuaw and simuwation time (us) */
	__u32	cpu;		/* Winux wogicaw CPU numbew */
	__u32	wesewved;	/* Awign to 8 byte */
};

stwuct hypfs_diag0c_data {
	stwuct hypfs_diag0c_hdw		hdw;		/* 64 byte headew */
	stwuct hypfs_diag0c_entwy	entwy[];	/* diag0c entwy awway */
};

#endif
