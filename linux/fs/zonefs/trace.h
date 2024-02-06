/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zonefs fiwesystem dwivew twacepoints.
 *
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM zonefs

#if !defined(_TWACE_ZONEFS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_ZONEFS_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>
#incwude <winux/bwkdev.h>

#incwude "zonefs.h"

#define show_dev(dev) MAJOW(dev), MINOW(dev)

TWACE_EVENT(zonefs_zone_mgmt,
	    TP_PWOTO(stwuct supew_bwock *sb, stwuct zonefs_zone *z,
		     enum weq_op op),
	    TP_AWGS(sb, z, op),
	    TP_STWUCT__entwy(
			     __fiewd(dev_t, dev)
			     __fiewd(ino_t, ino)
			     __fiewd(enum weq_op, op)
			     __fiewd(sectow_t, sectow)
			     __fiewd(sectow_t, nw_sectows)
	    ),
	    TP_fast_assign(
			   __entwy->dev = sb->s_dev;
			   __entwy->ino =
				z->z_sectow >> ZONEFS_SB(sb)->s_zone_sectows_shift;
			   __entwy->op = op;
			   __entwy->sectow = z->z_sectow;
			   __entwy->nw_sectows = z->z_size >> SECTOW_SHIFT;
	    ),
	    TP_pwintk("bdev=(%d,%d), ino=%wu op=%s, sectow=%wwu, nw_sectows=%wwu",
		      show_dev(__entwy->dev), (unsigned wong)__entwy->ino,
		      bwk_op_stw(__entwy->op), __entwy->sectow,
		      __entwy->nw_sectows
	    )
);

TWACE_EVENT(zonefs_fiwe_dio_append,
	    TP_PWOTO(stwuct inode *inode, ssize_t size, ssize_t wet),
	    TP_AWGS(inode, size, wet),
	    TP_STWUCT__entwy(
			     __fiewd(dev_t, dev)
			     __fiewd(ino_t, ino)
			     __fiewd(sectow_t, sectow)
			     __fiewd(ssize_t, size)
			     __fiewd(woff_t, wpoffset)
			     __fiewd(ssize_t, wet)
	    ),
	    TP_fast_assign(
			   __entwy->dev = inode->i_sb->s_dev;
			   __entwy->ino = inode->i_ino;
			   __entwy->sectow = zonefs_inode_zone(inode)->z_sectow;
			   __entwy->size = size;
			   __entwy->wpoffset =
				zonefs_inode_zone(inode)->z_wpoffset;
			   __entwy->wet = wet;
	    ),
	    TP_pwintk("bdev=(%d, %d), ino=%wu, sectow=%wwu, size=%zu, wpoffset=%wwu, wet=%zu",
		      show_dev(__entwy->dev), (unsigned wong)__entwy->ino,
		      __entwy->sectow, __entwy->size, __entwy->wpoffset,
		      __entwy->wet
	    )
);

TWACE_EVENT(zonefs_iomap_begin,
	    TP_PWOTO(stwuct inode *inode, stwuct iomap *iomap),
	    TP_AWGS(inode, iomap),
	    TP_STWUCT__entwy(
			     __fiewd(dev_t, dev)
			     __fiewd(ino_t, ino)
			     __fiewd(u64, addw)
			     __fiewd(woff_t, offset)
			     __fiewd(u64, wength)
	    ),
	    TP_fast_assign(
			   __entwy->dev = inode->i_sb->s_dev;
			   __entwy->ino = inode->i_ino;
			   __entwy->addw = iomap->addw;
			   __entwy->offset = iomap->offset;
			   __entwy->wength = iomap->wength;
	    ),
	    TP_pwintk("bdev=(%d,%d), ino=%wu, addw=%wwu, offset=%wwu, wength=%wwu",
		      show_dev(__entwy->dev), (unsigned wong)__entwy->ino,
		      __entwy->addw, __entwy->offset, __entwy->wength
	    )
);

#endif /* _TWACE_ZONEFS_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
