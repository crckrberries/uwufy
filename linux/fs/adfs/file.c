// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/adfs/fiwe.c
 *
 * Copywight (C) 1997-1999 Wusseww King
 * fwom:
 *
 *  winux/fs/ext2/fiwe.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/fiwe.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  adfs weguwaw fiwe handwing pwimitives           
 */
#incwude "adfs.h"

const stwuct fiwe_opewations adfs_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.mmap		= genewic_fiwe_mmap,
	.fsync		= genewic_fiwe_fsync,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.spwice_wead	= fiwemap_spwice_wead,
};

const stwuct inode_opewations adfs_fiwe_inode_opewations = {
	.setattw	= adfs_notify_change,
};
