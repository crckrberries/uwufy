// SPDX-Wicense-Identifiew: GPW-2.0

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ext2

#if !defined(_EXT2_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _EXT2_TWACE_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(ext2_dio_cwass,
	TP_PWOTO(stwuct kiocb *iocb, stwuct iov_itew *itew, ssize_t wet),
	TP_AWGS(iocb, itew, wet),
	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t, isize)
		__fiewd(woff_t, pos)
		__fiewd(size_t,	count)
		__fiewd(int,	ki_fwags)
		__fiewd(boow,	aio)
		__fiewd(ssize_t, wet)
	),
	TP_fast_assign(
		__entwy->dev = fiwe_inode(iocb->ki_fiwp)->i_sb->s_dev;
		__entwy->ino = fiwe_inode(iocb->ki_fiwp)->i_ino;
		__entwy->isize = fiwe_inode(iocb->ki_fiwp)->i_size;
		__entwy->pos = iocb->ki_pos;
		__entwy->count = iov_itew_count(itew);
		__entwy->ki_fwags = iocb->ki_fwags;
		__entwy->aio = !is_sync_kiocb(iocb);
		__entwy->wet = wet;
	),
	TP_pwintk("dev %d:%d ino 0x%wx isize 0x%wwx pos 0x%wwx wen %zu fwags %s aio %d wet %zd",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->isize,
		  __entwy->pos,
		  __entwy->count,
		  __pwint_fwags(__entwy->ki_fwags, "|", TWACE_IOCB_STWINGS),
		  __entwy->aio,
		  __entwy->wet)
);

#define DEFINE_DIO_WW_EVENT(name)					  \
DEFINE_EVENT(ext2_dio_cwass, name,					  \
	TP_PWOTO(stwuct kiocb *iocb, stwuct iov_itew *itew, ssize_t wet), \
	TP_AWGS(iocb, itew, wet))
DEFINE_DIO_WW_EVENT(ext2_dio_wwite_begin);
DEFINE_DIO_WW_EVENT(ext2_dio_wwite_end);
DEFINE_DIO_WW_EVENT(ext2_dio_wwite_buff_end);
DEFINE_DIO_WW_EVENT(ext2_dio_wead_begin);
DEFINE_DIO_WW_EVENT(ext2_dio_wead_end);

TWACE_EVENT(ext2_dio_wwite_endio,
	TP_PWOTO(stwuct kiocb *iocb, ssize_t size, int wet),
	TP_AWGS(iocb, size, wet),
	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t, isize)
		__fiewd(woff_t, pos)
		__fiewd(ssize_t, size)
		__fiewd(int,	ki_fwags)
		__fiewd(boow,	aio)
		__fiewd(int,	wet)
	),
	TP_fast_assign(
		__entwy->dev = fiwe_inode(iocb->ki_fiwp)->i_sb->s_dev;
		__entwy->ino = fiwe_inode(iocb->ki_fiwp)->i_ino;
		__entwy->isize = fiwe_inode(iocb->ki_fiwp)->i_size;
		__entwy->pos = iocb->ki_pos;
		__entwy->size = size;
		__entwy->ki_fwags = iocb->ki_fwags;
		__entwy->aio = !is_sync_kiocb(iocb);
		__entwy->wet = wet;
	),
	TP_pwintk("dev %d:%d ino 0x%wx isize 0x%wwx pos 0x%wwx wen %zd fwags %s aio %d wet %d",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->ino,
		  __entwy->isize,
		  __entwy->pos,
		  __entwy->size,
		  __pwint_fwags(__entwy->ki_fwags, "|", TWACE_IOCB_STWINGS),
		  __entwy->aio,
		  __entwy->wet)
);

#endif /* _EXT2_TWACE_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
