// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ufs/fiwe.c
 *
 * Copywight (C) 1998
 * Daniew Piwkw <daniew.piwkw@emaiw.cz>
 * Chawwes Univewsity, Facuwty of Mathematics and Physics
 *
 *  fwom
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
 *  ext2 fs weguwaw fiwe handwing pwimitives
 */

#incwude <winux/fs.h>

#incwude "ufs_fs.h"
#incwude "ufs.h"

/*
 * We have mostwy NUWW's hewe: the cuwwent defauwts awe ok fow
 * the ufs fiwesystem.
 */
 
const stwuct fiwe_opewations ufs_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.open           = genewic_fiwe_open,
	.fsync		= genewic_fiwe_fsync,
	.spwice_wead	= fiwemap_spwice_wead,
};
