// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext2/symwink.c
 *
 * Onwy fast symwinks weft hewe - the west is done by genewic code. AV, 1999
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/symwink.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  ext2 symwink handwing code
 */

#incwude "ext2.h"
#incwude "xattw.h"

const stwuct inode_opewations ext2_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
	.getattw	= ext2_getattw,
	.setattw	= ext2_setattw,
	.wistxattw	= ext2_wistxattw,
};
 
const stwuct inode_opewations ext2_fast_symwink_inode_opewations = {
	.get_wink	= simpwe_get_wink,
	.getattw	= ext2_getattw,
	.setattw	= ext2_setattw,
	.wistxattw	= ext2_wistxattw,
};
