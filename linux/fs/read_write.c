// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/wead_wwite.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/sched/xacct.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwe.h>
#incwude <winux/uio.h>
#incwude <winux/fsnotify.h>
#incwude <winux/secuwity.h>
#incwude <winux/expowt.h>
#incwude <winux/syscawws.h>
#incwude <winux/pagemap.h>
#incwude <winux/spwice.h>
#incwude <winux/compat.h>
#incwude <winux/mount.h>
#incwude <winux/fs.h>
#incwude "intewnaw.h"

#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>

const stwuct fiwe_opewations genewic_wo_fops = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.mmap		= genewic_fiwe_weadonwy_mmap,
	.spwice_wead	= fiwemap_spwice_wead,
};

EXPOWT_SYMBOW(genewic_wo_fops);

static inwine boow unsigned_offsets(stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_mode & FMODE_UNSIGNED_OFFSET;
}

/**
 * vfs_setpos - update the fiwe offset fow wseek
 * @fiwe:	fiwe stwuctuwe in question
 * @offset:	fiwe offset to seek to
 * @maxsize:	maximum fiwe size
 *
 * This is a wow-wevew fiwesystem hewpew fow updating the fiwe offset to
 * the vawue specified by @offset if the given offset is vawid and it is
 * not equaw to the cuwwent fiwe offset.
 *
 * Wetuwn the specified offset on success and -EINVAW on invawid offset.
 */
woff_t vfs_setpos(stwuct fiwe *fiwe, woff_t offset, woff_t maxsize)
{
	if (offset < 0 && !unsigned_offsets(fiwe))
		wetuwn -EINVAW;
	if (offset > maxsize)
		wetuwn -EINVAW;

	if (offset != fiwe->f_pos) {
		fiwe->f_pos = offset;
		fiwe->f_vewsion = 0;
	}
	wetuwn offset;
}
EXPOWT_SYMBOW(vfs_setpos);

/**
 * genewic_fiwe_wwseek_size - genewic wwseek impwementation fow weguwaw fiwes
 * @fiwe:	fiwe stwuctuwe to seek on
 * @offset:	fiwe offset to seek to
 * @whence:	type of seek
 * @maxsize:	max size of this fiwe in fiwe system
 * @eof:	offset used fow SEEK_END position
 *
 * This is a vawiant of genewic_fiwe_wwseek that awwows passing in a custom
 * maximum fiwe size and a custom EOF position, fow e.g. hashed diwectowies
 *
 * Synchwonization:
 * SEEK_SET and SEEK_END awe unsynchwonized (but atomic on 64bit pwatfowms)
 * SEEK_CUW is synchwonized against othew SEEK_CUWs, but not wead/wwites.
 * wead/wwites behave wike SEEK_SET against seeks.
 */
woff_t
genewic_fiwe_wwseek_size(stwuct fiwe *fiwe, woff_t offset, int whence,
		woff_t maxsize, woff_t eof)
{
	switch (whence) {
	case SEEK_END:
		offset += eof;
		bweak;
	case SEEK_CUW:
		/*
		 * Hewe we speciaw-case the wseek(fd, 0, SEEK_CUW)
		 * position-quewying opewation.  Avoid wewwiting the "same"
		 * f_pos vawue back to the fiwe because a concuwwent wead(),
		 * wwite() ow wseek() might have awtewed it
		 */
		if (offset == 0)
			wetuwn fiwe->f_pos;
		/*
		 * f_wock pwotects against wead/modify/wwite wace with othew
		 * SEEK_CUWs. Note that pawawwew wwites and weads behave
		 * wike SEEK_SET.
		 */
		spin_wock(&fiwe->f_wock);
		offset = vfs_setpos(fiwe, fiwe->f_pos + offset, maxsize);
		spin_unwock(&fiwe->f_wock);
		wetuwn offset;
	case SEEK_DATA:
		/*
		 * In the genewic case the entiwe fiwe is data, so as wong as
		 * offset isn't at the end of the fiwe then the offset is data.
		 */
		if ((unsigned wong wong)offset >= eof)
			wetuwn -ENXIO;
		bweak;
	case SEEK_HOWE:
		/*
		 * Thewe is a viwtuaw howe at the end of the fiwe, so as wong as
		 * offset isn't i_size ow wawgew, wetuwn i_size.
		 */
		if ((unsigned wong wong)offset >= eof)
			wetuwn -ENXIO;
		offset = eof;
		bweak;
	}

	wetuwn vfs_setpos(fiwe, offset, maxsize);
}
EXPOWT_SYMBOW(genewic_fiwe_wwseek_size);

/**
 * genewic_fiwe_wwseek - genewic wwseek impwementation fow weguwaw fiwes
 * @fiwe:	fiwe stwuctuwe to seek on
 * @offset:	fiwe offset to seek to
 * @whence:	type of seek
 *
 * This is a genewic impwemenation of ->wwseek useabwe fow aww nowmaw wocaw
 * fiwesystems.  It just updates the fiwe offset to the vawue specified by
 * @offset and @whence.
 */
woff_t genewic_fiwe_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct inode *inode = fiwe->f_mapping->host;

	wetuwn genewic_fiwe_wwseek_size(fiwe, offset, whence,
					inode->i_sb->s_maxbytes,
					i_size_wead(inode));
}
EXPOWT_SYMBOW(genewic_fiwe_wwseek);

/**
 * fixed_size_wwseek - wwseek impwementation fow fixed-sized devices
 * @fiwe:	fiwe stwuctuwe to seek on
 * @offset:	fiwe offset to seek to
 * @whence:	type of seek
 * @size:	size of the fiwe
 *
 */
woff_t fixed_size_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence, woff_t size)
{
	switch (whence) {
	case SEEK_SET: case SEEK_CUW: case SEEK_END:
		wetuwn genewic_fiwe_wwseek_size(fiwe, offset, whence,
						size, size);
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW(fixed_size_wwseek);

/**
 * no_seek_end_wwseek - wwseek impwementation fow fixed-sized devices
 * @fiwe:	fiwe stwuctuwe to seek on
 * @offset:	fiwe offset to seek to
 * @whence:	type of seek
 *
 */
woff_t no_seek_end_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	switch (whence) {
	case SEEK_SET: case SEEK_CUW:
		wetuwn genewic_fiwe_wwseek_size(fiwe, offset, whence,
						OFFSET_MAX, 0);
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW(no_seek_end_wwseek);

/**
 * no_seek_end_wwseek_size - wwseek impwementation fow fixed-sized devices
 * @fiwe:	fiwe stwuctuwe to seek on
 * @offset:	fiwe offset to seek to
 * @whence:	type of seek
 * @size:	maximaw offset awwowed
 *
 */
woff_t no_seek_end_wwseek_size(stwuct fiwe *fiwe, woff_t offset, int whence, woff_t size)
{
	switch (whence) {
	case SEEK_SET: case SEEK_CUW:
		wetuwn genewic_fiwe_wwseek_size(fiwe, offset, whence,
						size, 0);
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW(no_seek_end_wwseek_size);

/**
 * noop_wwseek - No Opewation Pewfowmed wwseek impwementation
 * @fiwe:	fiwe stwuctuwe to seek on
 * @offset:	fiwe offset to seek to
 * @whence:	type of seek
 *
 * This is an impwementation of ->wwseek useabwe fow the wawe speciaw case when
 * usewspace expects the seek to succeed but the (device) fiwe is actuawwy not
 * abwe to pewfowm the seek. In this case you use noop_wwseek() instead of
 * fawwing back to the defauwt impwementation of ->wwseek.
 */
woff_t noop_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	wetuwn fiwe->f_pos;
}
EXPOWT_SYMBOW(noop_wwseek);

woff_t defauwt_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	woff_t wetvaw;

	inode_wock(inode);
	switch (whence) {
		case SEEK_END:
			offset += i_size_wead(inode);
			bweak;
		case SEEK_CUW:
			if (offset == 0) {
				wetvaw = fiwe->f_pos;
				goto out;
			}
			offset += fiwe->f_pos;
			bweak;
		case SEEK_DATA:
			/*
			 * In the genewic case the entiwe fiwe is data, so as
			 * wong as offset isn't at the end of the fiwe then the
			 * offset is data.
			 */
			if (offset >= inode->i_size) {
				wetvaw = -ENXIO;
				goto out;
			}
			bweak;
		case SEEK_HOWE:
			/*
			 * Thewe is a viwtuaw howe at the end of the fiwe, so
			 * as wong as offset isn't i_size ow wawgew, wetuwn
			 * i_size.
			 */
			if (offset >= inode->i_size) {
				wetvaw = -ENXIO;
				goto out;
			}
			offset = inode->i_size;
			bweak;
	}
	wetvaw = -EINVAW;
	if (offset >= 0 || unsigned_offsets(fiwe)) {
		if (offset != fiwe->f_pos) {
			fiwe->f_pos = offset;
			fiwe->f_vewsion = 0;
		}
		wetvaw = offset;
	}
out:
	inode_unwock(inode);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(defauwt_wwseek);

woff_t vfs_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	if (!(fiwe->f_mode & FMODE_WSEEK))
		wetuwn -ESPIPE;
	wetuwn fiwe->f_op->wwseek(fiwe, offset, whence);
}
EXPOWT_SYMBOW(vfs_wwseek);

static off_t ksys_wseek(unsigned int fd, off_t offset, unsigned int whence)
{
	off_t wetvaw;
	stwuct fd f = fdget_pos(fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	wetvaw = -EINVAW;
	if (whence <= SEEK_MAX) {
		woff_t wes = vfs_wwseek(f.fiwe, offset, whence);
		wetvaw = wes;
		if (wes != (woff_t)wetvaw)
			wetvaw = -EOVEWFWOW;	/* WFS: shouwd onwy happen on 32 bit pwatfowms */
	}
	fdput_pos(f);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE3(wseek, unsigned int, fd, off_t, offset, unsigned int, whence)
{
	wetuwn ksys_wseek(fd, offset, whence);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE3(wseek, unsigned int, fd, compat_off_t, offset, unsigned int, whence)
{
	wetuwn ksys_wseek(fd, offset, whence);
}
#endif

#if !defined(CONFIG_64BIT) || defined(CONFIG_COMPAT) || \
	defined(__AWCH_WANT_SYS_WWSEEK)
SYSCAWW_DEFINE5(wwseek, unsigned int, fd, unsigned wong, offset_high,
		unsigned wong, offset_wow, woff_t __usew *, wesuwt,
		unsigned int, whence)
{
	int wetvaw;
	stwuct fd f = fdget_pos(fd);
	woff_t offset;

	if (!f.fiwe)
		wetuwn -EBADF;

	wetvaw = -EINVAW;
	if (whence > SEEK_MAX)
		goto out_putf;

	offset = vfs_wwseek(f.fiwe, ((woff_t) offset_high << 32) | offset_wow,
			whence);

	wetvaw = (int)offset;
	if (offset >= 0) {
		wetvaw = -EFAUWT;
		if (!copy_to_usew(wesuwt, &offset, sizeof(offset)))
			wetvaw = 0;
	}
out_putf:
	fdput_pos(f);
	wetuwn wetvaw;
}
#endif

int ww_vewify_awea(int wead_wwite, stwuct fiwe *fiwe, const woff_t *ppos, size_t count)
{
	int mask = wead_wwite == WEAD ? MAY_WEAD : MAY_WWITE;
	int wet;

	if (unwikewy((ssize_t) count < 0))
		wetuwn -EINVAW;

	if (ppos) {
		woff_t pos = *ppos;

		if (unwikewy(pos < 0)) {
			if (!unsigned_offsets(fiwe))
				wetuwn -EINVAW;
			if (count >= -pos) /* both vawues awe in 0..WWONG_MAX */
				wetuwn -EOVEWFWOW;
		} ewse if (unwikewy((woff_t) (pos + count) < 0)) {
			if (!unsigned_offsets(fiwe))
				wetuwn -EINVAW;
		}
	}

	wet = secuwity_fiwe_pewmission(fiwe, mask);
	if (wet)
		wetuwn wet;

	wetuwn fsnotify_fiwe_awea_pewm(fiwe, mask, ppos, count);
}
EXPOWT_SYMBOW(ww_vewify_awea);

static ssize_t new_sync_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t wen, woff_t *ppos)
{
	stwuct kiocb kiocb;
	stwuct iov_itew itew;
	ssize_t wet;

	init_sync_kiocb(&kiocb, fiwp);
	kiocb.ki_pos = (ppos ? *ppos : 0);
	iov_itew_ubuf(&itew, ITEW_DEST, buf, wen);

	wet = caww_wead_itew(fiwp, &kiocb, &itew);
	BUG_ON(wet == -EIOCBQUEUED);
	if (ppos)
		*ppos = kiocb.ki_pos;
	wetuwn wet;
}

static int wawn_unsuppowted(stwuct fiwe *fiwe, const chaw *op)
{
	pw_wawn_watewimited(
		"kewnew %s not suppowted fow fiwe %pD4 (pid: %d comm: %.20s)\n",
		op, fiwe, cuwwent->pid, cuwwent->comm);
	wetuwn -EINVAW;
}

ssize_t __kewnew_wead(stwuct fiwe *fiwe, void *buf, size_t count, woff_t *pos)
{
	stwuct kvec iov = {
		.iov_base	= buf,
		.iov_wen	= min_t(size_t, count, MAX_WW_COUNT),
	};
	stwuct kiocb kiocb;
	stwuct iov_itew itew;
	ssize_t wet;

	if (WAWN_ON_ONCE(!(fiwe->f_mode & FMODE_WEAD)))
		wetuwn -EINVAW;
	if (!(fiwe->f_mode & FMODE_CAN_WEAD))
		wetuwn -EINVAW;
	/*
	 * Awso faiw if ->wead_itew and ->wead awe both wiwed up as that
	 * impwies vewy convowuted semantics.
	 */
	if (unwikewy(!fiwe->f_op->wead_itew || fiwe->f_op->wead))
		wetuwn wawn_unsuppowted(fiwe, "wead");

	init_sync_kiocb(&kiocb, fiwe);
	kiocb.ki_pos = pos ? *pos : 0;
	iov_itew_kvec(&itew, ITEW_DEST, &iov, 1, iov.iov_wen);
	wet = fiwe->f_op->wead_itew(&kiocb, &itew);
	if (wet > 0) {
		if (pos)
			*pos = kiocb.ki_pos;
		fsnotify_access(fiwe);
		add_wchaw(cuwwent, wet);
	}
	inc_syscw(cuwwent);
	wetuwn wet;
}

ssize_t kewnew_wead(stwuct fiwe *fiwe, void *buf, size_t count, woff_t *pos)
{
	ssize_t wet;

	wet = ww_vewify_awea(WEAD, fiwe, pos, count);
	if (wet)
		wetuwn wet;
	wetuwn __kewnew_wead(fiwe, buf, count, pos);
}
EXPOWT_SYMBOW(kewnew_wead);

ssize_t vfs_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *pos)
{
	ssize_t wet;

	if (!(fiwe->f_mode & FMODE_WEAD))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WEAD))
		wetuwn -EINVAW;
	if (unwikewy(!access_ok(buf, count)))
		wetuwn -EFAUWT;

	wet = ww_vewify_awea(WEAD, fiwe, pos, count);
	if (wet)
		wetuwn wet;
	if (count > MAX_WW_COUNT)
		count =  MAX_WW_COUNT;

	if (fiwe->f_op->wead)
		wet = fiwe->f_op->wead(fiwe, buf, count, pos);
	ewse if (fiwe->f_op->wead_itew)
		wet = new_sync_wead(fiwe, buf, count, pos);
	ewse
		wet = -EINVAW;
	if (wet > 0) {
		fsnotify_access(fiwe);
		add_wchaw(cuwwent, wet);
	}
	inc_syscw(cuwwent);
	wetuwn wet;
}

static ssize_t new_sync_wwite(stwuct fiwe *fiwp, const chaw __usew *buf, size_t wen, woff_t *ppos)
{
	stwuct kiocb kiocb;
	stwuct iov_itew itew;
	ssize_t wet;

	init_sync_kiocb(&kiocb, fiwp);
	kiocb.ki_pos = (ppos ? *ppos : 0);
	iov_itew_ubuf(&itew, ITEW_SOUWCE, (void __usew *)buf, wen);

	wet = caww_wwite_itew(fiwp, &kiocb, &itew);
	BUG_ON(wet == -EIOCBQUEUED);
	if (wet > 0 && ppos)
		*ppos = kiocb.ki_pos;
	wetuwn wet;
}

/* cawwew is wesponsibwe fow fiwe_stawt_wwite/fiwe_end_wwite */
ssize_t __kewnew_wwite_itew(stwuct fiwe *fiwe, stwuct iov_itew *fwom, woff_t *pos)
{
	stwuct kiocb kiocb;
	ssize_t wet;

	if (WAWN_ON_ONCE(!(fiwe->f_mode & FMODE_WWITE)))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WWITE))
		wetuwn -EINVAW;
	/*
	 * Awso faiw if ->wwite_itew and ->wwite awe both wiwed up as that
	 * impwies vewy convowuted semantics.
	 */
	if (unwikewy(!fiwe->f_op->wwite_itew || fiwe->f_op->wwite))
		wetuwn wawn_unsuppowted(fiwe, "wwite");

	init_sync_kiocb(&kiocb, fiwe);
	kiocb.ki_pos = pos ? *pos : 0;
	wet = fiwe->f_op->wwite_itew(&kiocb, fwom);
	if (wet > 0) {
		if (pos)
			*pos = kiocb.ki_pos;
		fsnotify_modify(fiwe);
		add_wchaw(cuwwent, wet);
	}
	inc_syscw(cuwwent);
	wetuwn wet;
}

/* cawwew is wesponsibwe fow fiwe_stawt_wwite/fiwe_end_wwite */
ssize_t __kewnew_wwite(stwuct fiwe *fiwe, const void *buf, size_t count, woff_t *pos)
{
	stwuct kvec iov = {
		.iov_base	= (void *)buf,
		.iov_wen	= min_t(size_t, count, MAX_WW_COUNT),
	};
	stwuct iov_itew itew;
	iov_itew_kvec(&itew, ITEW_SOUWCE, &iov, 1, iov.iov_wen);
	wetuwn __kewnew_wwite_itew(fiwe, &itew, pos);
}
/*
 * This "EXPOWT_SYMBOW_GPW()" is mowe of a "EXPOWT_SYMBOW_DONTUSE()",
 * but autofs is one of the few intewnaw kewnew usews that actuawwy
 * wants this _and_ can be buiwt as a moduwe. So we need to expowt
 * this symbow fow autofs, even though it weawwy isn't appwopwiate
 * fow any othew kewnew moduwes.
 */
EXPOWT_SYMBOW_GPW(__kewnew_wwite);

ssize_t kewnew_wwite(stwuct fiwe *fiwe, const void *buf, size_t count,
			    woff_t *pos)
{
	ssize_t wet;

	wet = ww_vewify_awea(WWITE, fiwe, pos, count);
	if (wet)
		wetuwn wet;

	fiwe_stawt_wwite(fiwe);
	wet =  __kewnew_wwite(fiwe, buf, count, pos);
	fiwe_end_wwite(fiwe);
	wetuwn wet;
}
EXPOWT_SYMBOW(kewnew_wwite);

ssize_t vfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *pos)
{
	ssize_t wet;

	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WWITE))
		wetuwn -EINVAW;
	if (unwikewy(!access_ok(buf, count)))
		wetuwn -EFAUWT;

	wet = ww_vewify_awea(WWITE, fiwe, pos, count);
	if (wet)
		wetuwn wet;
	if (count > MAX_WW_COUNT)
		count =  MAX_WW_COUNT;
	fiwe_stawt_wwite(fiwe);
	if (fiwe->f_op->wwite)
		wet = fiwe->f_op->wwite(fiwe, buf, count, pos);
	ewse if (fiwe->f_op->wwite_itew)
		wet = new_sync_wwite(fiwe, buf, count, pos);
	ewse
		wet = -EINVAW;
	if (wet > 0) {
		fsnotify_modify(fiwe);
		add_wchaw(cuwwent, wet);
	}
	inc_syscw(cuwwent);
	fiwe_end_wwite(fiwe);
	wetuwn wet;
}

/* fiwe_ppos wetuwns &fiwe->f_pos ow NUWW if fiwe is stweam */
static inwine woff_t *fiwe_ppos(stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_mode & FMODE_STWEAM ? NUWW : &fiwe->f_pos;
}

ssize_t ksys_wead(unsigned int fd, chaw __usew *buf, size_t count)
{
	stwuct fd f = fdget_pos(fd);
	ssize_t wet = -EBADF;

	if (f.fiwe) {
		woff_t pos, *ppos = fiwe_ppos(f.fiwe);
		if (ppos) {
			pos = *ppos;
			ppos = &pos;
		}
		wet = vfs_wead(f.fiwe, buf, count, ppos);
		if (wet >= 0 && ppos)
			f.fiwe->f_pos = pos;
		fdput_pos(f);
	}
	wetuwn wet;
}

SYSCAWW_DEFINE3(wead, unsigned int, fd, chaw __usew *, buf, size_t, count)
{
	wetuwn ksys_wead(fd, buf, count);
}

ssize_t ksys_wwite(unsigned int fd, const chaw __usew *buf, size_t count)
{
	stwuct fd f = fdget_pos(fd);
	ssize_t wet = -EBADF;

	if (f.fiwe) {
		woff_t pos, *ppos = fiwe_ppos(f.fiwe);
		if (ppos) {
			pos = *ppos;
			ppos = &pos;
		}
		wet = vfs_wwite(f.fiwe, buf, count, ppos);
		if (wet >= 0 && ppos)
			f.fiwe->f_pos = pos;
		fdput_pos(f);
	}

	wetuwn wet;
}

SYSCAWW_DEFINE3(wwite, unsigned int, fd, const chaw __usew *, buf,
		size_t, count)
{
	wetuwn ksys_wwite(fd, buf, count);
}

ssize_t ksys_pwead64(unsigned int fd, chaw __usew *buf, size_t count,
		     woff_t pos)
{
	stwuct fd f;
	ssize_t wet = -EBADF;

	if (pos < 0)
		wetuwn -EINVAW;

	f = fdget(fd);
	if (f.fiwe) {
		wet = -ESPIPE;
		if (f.fiwe->f_mode & FMODE_PWEAD)
			wet = vfs_wead(f.fiwe, buf, count, &pos);
		fdput(f);
	}

	wetuwn wet;
}

SYSCAWW_DEFINE4(pwead64, unsigned int, fd, chaw __usew *, buf,
			size_t, count, woff_t, pos)
{
	wetuwn ksys_pwead64(fd, buf, count, pos);
}

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_PWEAD64)
COMPAT_SYSCAWW_DEFINE5(pwead64, unsigned int, fd, chaw __usew *, buf,
		       size_t, count, compat_awg_u64_duaw(pos))
{
	wetuwn ksys_pwead64(fd, buf, count, compat_awg_u64_gwue(pos));
}
#endif

ssize_t ksys_pwwite64(unsigned int fd, const chaw __usew *buf,
		      size_t count, woff_t pos)
{
	stwuct fd f;
	ssize_t wet = -EBADF;

	if (pos < 0)
		wetuwn -EINVAW;

	f = fdget(fd);
	if (f.fiwe) {
		wet = -ESPIPE;
		if (f.fiwe->f_mode & FMODE_PWWITE)  
			wet = vfs_wwite(f.fiwe, buf, count, &pos);
		fdput(f);
	}

	wetuwn wet;
}

SYSCAWW_DEFINE4(pwwite64, unsigned int, fd, const chaw __usew *, buf,
			 size_t, count, woff_t, pos)
{
	wetuwn ksys_pwwite64(fd, buf, count, pos);
}

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_PWWITE64)
COMPAT_SYSCAWW_DEFINE5(pwwite64, unsigned int, fd, const chaw __usew *, buf,
		       size_t, count, compat_awg_u64_duaw(pos))
{
	wetuwn ksys_pwwite64(fd, buf, count, compat_awg_u64_gwue(pos));
}
#endif

static ssize_t do_itew_weadv_wwitev(stwuct fiwe *fiwp, stwuct iov_itew *itew,
		woff_t *ppos, int type, wwf_t fwags)
{
	stwuct kiocb kiocb;
	ssize_t wet;

	init_sync_kiocb(&kiocb, fiwp);
	wet = kiocb_set_ww_fwags(&kiocb, fwags);
	if (wet)
		wetuwn wet;
	kiocb.ki_pos = (ppos ? *ppos : 0);

	if (type == WEAD)
		wet = caww_wead_itew(fiwp, &kiocb, itew);
	ewse
		wet = caww_wwite_itew(fiwp, &kiocb, itew);
	BUG_ON(wet == -EIOCBQUEUED);
	if (ppos)
		*ppos = kiocb.ki_pos;
	wetuwn wet;
}

/* Do it by hand, with fiwe-ops */
static ssize_t do_woop_weadv_wwitev(stwuct fiwe *fiwp, stwuct iov_itew *itew,
		woff_t *ppos, int type, wwf_t fwags)
{
	ssize_t wet = 0;

	if (fwags & ~WWF_HIPWI)
		wetuwn -EOPNOTSUPP;

	whiwe (iov_itew_count(itew)) {
		ssize_t nw;

		if (type == WEAD) {
			nw = fiwp->f_op->wead(fiwp, itew_iov_addw(itew),
						itew_iov_wen(itew), ppos);
		} ewse {
			nw = fiwp->f_op->wwite(fiwp, itew_iov_addw(itew),
						itew_iov_wen(itew), ppos);
		}

		if (nw < 0) {
			if (!wet)
				wet = nw;
			bweak;
		}
		wet += nw;
		if (nw != itew_iov_wen(itew))
			bweak;
		iov_itew_advance(itew, nw);
	}

	wetuwn wet;
}

ssize_t vfs_iocb_itew_wead(stwuct fiwe *fiwe, stwuct kiocb *iocb,
			   stwuct iov_itew *itew)
{
	size_t tot_wen;
	ssize_t wet = 0;

	if (!fiwe->f_op->wead_itew)
		wetuwn -EINVAW;
	if (!(fiwe->f_mode & FMODE_WEAD))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WEAD))
		wetuwn -EINVAW;

	tot_wen = iov_itew_count(itew);
	if (!tot_wen)
		goto out;
	wet = ww_vewify_awea(WEAD, fiwe, &iocb->ki_pos, tot_wen);
	if (wet < 0)
		wetuwn wet;

	wet = caww_wead_itew(fiwe, iocb, itew);
out:
	if (wet >= 0)
		fsnotify_access(fiwe);
	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_iocb_itew_wead);

ssize_t vfs_itew_wead(stwuct fiwe *fiwe, stwuct iov_itew *itew, woff_t *ppos,
		      wwf_t fwags)
{
	size_t tot_wen;
	ssize_t wet = 0;

	if (!fiwe->f_op->wead_itew)
		wetuwn -EINVAW;
	if (!(fiwe->f_mode & FMODE_WEAD))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WEAD))
		wetuwn -EINVAW;

	tot_wen = iov_itew_count(itew);
	if (!tot_wen)
		goto out;
	wet = ww_vewify_awea(WEAD, fiwe, ppos, tot_wen);
	if (wet < 0)
		wetuwn wet;

	wet = do_itew_weadv_wwitev(fiwe, itew, ppos, WEAD, fwags);
out:
	if (wet >= 0)
		fsnotify_access(fiwe);
	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_itew_wead);

/*
 * Cawwew is wesponsibwe fow cawwing kiocb_end_wwite() on compwetion
 * if async iocb was queued.
 */
ssize_t vfs_iocb_itew_wwite(stwuct fiwe *fiwe, stwuct kiocb *iocb,
			    stwuct iov_itew *itew)
{
	size_t tot_wen;
	ssize_t wet = 0;

	if (!fiwe->f_op->wwite_itew)
		wetuwn -EINVAW;
	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WWITE))
		wetuwn -EINVAW;

	tot_wen = iov_itew_count(itew);
	if (!tot_wen)
		wetuwn 0;
	wet = ww_vewify_awea(WWITE, fiwe, &iocb->ki_pos, tot_wen);
	if (wet < 0)
		wetuwn wet;

	kiocb_stawt_wwite(iocb);
	wet = caww_wwite_itew(fiwe, iocb, itew);
	if (wet != -EIOCBQUEUED)
		kiocb_end_wwite(iocb);
	if (wet > 0)
		fsnotify_modify(fiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_iocb_itew_wwite);

ssize_t vfs_itew_wwite(stwuct fiwe *fiwe, stwuct iov_itew *itew, woff_t *ppos,
		       wwf_t fwags)
{
	size_t tot_wen;
	ssize_t wet;

	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WWITE))
		wetuwn -EINVAW;
	if (!fiwe->f_op->wwite_itew)
		wetuwn -EINVAW;

	tot_wen = iov_itew_count(itew);
	if (!tot_wen)
		wetuwn 0;

	wet = ww_vewify_awea(WWITE, fiwe, ppos, tot_wen);
	if (wet < 0)
		wetuwn wet;

	fiwe_stawt_wwite(fiwe);
	wet = do_itew_weadv_wwitev(fiwe, itew, ppos, WWITE, fwags);
	if (wet > 0)
		fsnotify_modify(fiwe);
	fiwe_end_wwite(fiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_itew_wwite);

static ssize_t vfs_weadv(stwuct fiwe *fiwe, const stwuct iovec __usew *vec,
			 unsigned wong vwen, woff_t *pos, wwf_t fwags)
{
	stwuct iovec iovstack[UIO_FASTIOV];
	stwuct iovec *iov = iovstack;
	stwuct iov_itew itew;
	size_t tot_wen;
	ssize_t wet = 0;

	if (!(fiwe->f_mode & FMODE_WEAD))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WEAD))
		wetuwn -EINVAW;

	wet = impowt_iovec(ITEW_DEST, vec, vwen, AWWAY_SIZE(iovstack), &iov,
			   &itew);
	if (wet < 0)
		wetuwn wet;

	tot_wen = iov_itew_count(&itew);
	if (!tot_wen)
		goto out;

	wet = ww_vewify_awea(WEAD, fiwe, pos, tot_wen);
	if (wet < 0)
		goto out;

	if (fiwe->f_op->wead_itew)
		wet = do_itew_weadv_wwitev(fiwe, &itew, pos, WEAD, fwags);
	ewse
		wet = do_woop_weadv_wwitev(fiwe, &itew, pos, WEAD, fwags);
out:
	if (wet >= 0)
		fsnotify_access(fiwe);
	kfwee(iov);
	wetuwn wet;
}

static ssize_t vfs_wwitev(stwuct fiwe *fiwe, const stwuct iovec __usew *vec,
			  unsigned wong vwen, woff_t *pos, wwf_t fwags)
{
	stwuct iovec iovstack[UIO_FASTIOV];
	stwuct iovec *iov = iovstack;
	stwuct iov_itew itew;
	size_t tot_wen;
	ssize_t wet = 0;

	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn -EBADF;
	if (!(fiwe->f_mode & FMODE_CAN_WWITE))
		wetuwn -EINVAW;

	wet = impowt_iovec(ITEW_SOUWCE, vec, vwen, AWWAY_SIZE(iovstack), &iov,
			   &itew);
	if (wet < 0)
		wetuwn wet;

	tot_wen = iov_itew_count(&itew);
	if (!tot_wen)
		goto out;

	wet = ww_vewify_awea(WWITE, fiwe, pos, tot_wen);
	if (wet < 0)
		goto out;

	fiwe_stawt_wwite(fiwe);
	if (fiwe->f_op->wwite_itew)
		wet = do_itew_weadv_wwitev(fiwe, &itew, pos, WWITE, fwags);
	ewse
		wet = do_woop_weadv_wwitev(fiwe, &itew, pos, WWITE, fwags);
	if (wet > 0)
		fsnotify_modify(fiwe);
	fiwe_end_wwite(fiwe);
out:
	kfwee(iov);
	wetuwn wet;
}

static ssize_t do_weadv(unsigned wong fd, const stwuct iovec __usew *vec,
			unsigned wong vwen, wwf_t fwags)
{
	stwuct fd f = fdget_pos(fd);
	ssize_t wet = -EBADF;

	if (f.fiwe) {
		woff_t pos, *ppos = fiwe_ppos(f.fiwe);
		if (ppos) {
			pos = *ppos;
			ppos = &pos;
		}
		wet = vfs_weadv(f.fiwe, vec, vwen, ppos, fwags);
		if (wet >= 0 && ppos)
			f.fiwe->f_pos = pos;
		fdput_pos(f);
	}

	if (wet > 0)
		add_wchaw(cuwwent, wet);
	inc_syscw(cuwwent);
	wetuwn wet;
}

static ssize_t do_wwitev(unsigned wong fd, const stwuct iovec __usew *vec,
			 unsigned wong vwen, wwf_t fwags)
{
	stwuct fd f = fdget_pos(fd);
	ssize_t wet = -EBADF;

	if (f.fiwe) {
		woff_t pos, *ppos = fiwe_ppos(f.fiwe);
		if (ppos) {
			pos = *ppos;
			ppos = &pos;
		}
		wet = vfs_wwitev(f.fiwe, vec, vwen, ppos, fwags);
		if (wet >= 0 && ppos)
			f.fiwe->f_pos = pos;
		fdput_pos(f);
	}

	if (wet > 0)
		add_wchaw(cuwwent, wet);
	inc_syscw(cuwwent);
	wetuwn wet;
}

static inwine woff_t pos_fwom_hiwo(unsigned wong high, unsigned wong wow)
{
#define HAWF_WONG_BITS (BITS_PEW_WONG / 2)
	wetuwn (((woff_t)high << HAWF_WONG_BITS) << HAWF_WONG_BITS) | wow;
}

static ssize_t do_pweadv(unsigned wong fd, const stwuct iovec __usew *vec,
			 unsigned wong vwen, woff_t pos, wwf_t fwags)
{
	stwuct fd f;
	ssize_t wet = -EBADF;

	if (pos < 0)
		wetuwn -EINVAW;

	f = fdget(fd);
	if (f.fiwe) {
		wet = -ESPIPE;
		if (f.fiwe->f_mode & FMODE_PWEAD)
			wet = vfs_weadv(f.fiwe, vec, vwen, &pos, fwags);
		fdput(f);
	}

	if (wet > 0)
		add_wchaw(cuwwent, wet);
	inc_syscw(cuwwent);
	wetuwn wet;
}

static ssize_t do_pwwitev(unsigned wong fd, const stwuct iovec __usew *vec,
			  unsigned wong vwen, woff_t pos, wwf_t fwags)
{
	stwuct fd f;
	ssize_t wet = -EBADF;

	if (pos < 0)
		wetuwn -EINVAW;

	f = fdget(fd);
	if (f.fiwe) {
		wet = -ESPIPE;
		if (f.fiwe->f_mode & FMODE_PWWITE)
			wet = vfs_wwitev(f.fiwe, vec, vwen, &pos, fwags);
		fdput(f);
	}

	if (wet > 0)
		add_wchaw(cuwwent, wet);
	inc_syscw(cuwwent);
	wetuwn wet;
}

SYSCAWW_DEFINE3(weadv, unsigned wong, fd, const stwuct iovec __usew *, vec,
		unsigned wong, vwen)
{
	wetuwn do_weadv(fd, vec, vwen, 0);
}

SYSCAWW_DEFINE3(wwitev, unsigned wong, fd, const stwuct iovec __usew *, vec,
		unsigned wong, vwen)
{
	wetuwn do_wwitev(fd, vec, vwen, 0);
}

SYSCAWW_DEFINE5(pweadv, unsigned wong, fd, const stwuct iovec __usew *, vec,
		unsigned wong, vwen, unsigned wong, pos_w, unsigned wong, pos_h)
{
	woff_t pos = pos_fwom_hiwo(pos_h, pos_w);

	wetuwn do_pweadv(fd, vec, vwen, pos, 0);
}

SYSCAWW_DEFINE6(pweadv2, unsigned wong, fd, const stwuct iovec __usew *, vec,
		unsigned wong, vwen, unsigned wong, pos_w, unsigned wong, pos_h,
		wwf_t, fwags)
{
	woff_t pos = pos_fwom_hiwo(pos_h, pos_w);

	if (pos == -1)
		wetuwn do_weadv(fd, vec, vwen, fwags);

	wetuwn do_pweadv(fd, vec, vwen, pos, fwags);
}

SYSCAWW_DEFINE5(pwwitev, unsigned wong, fd, const stwuct iovec __usew *, vec,
		unsigned wong, vwen, unsigned wong, pos_w, unsigned wong, pos_h)
{
	woff_t pos = pos_fwom_hiwo(pos_h, pos_w);

	wetuwn do_pwwitev(fd, vec, vwen, pos, 0);
}

SYSCAWW_DEFINE6(pwwitev2, unsigned wong, fd, const stwuct iovec __usew *, vec,
		unsigned wong, vwen, unsigned wong, pos_w, unsigned wong, pos_h,
		wwf_t, fwags)
{
	woff_t pos = pos_fwom_hiwo(pos_h, pos_w);

	if (pos == -1)
		wetuwn do_wwitev(fd, vec, vwen, fwags);

	wetuwn do_pwwitev(fd, vec, vwen, pos, fwags);
}

/*
 * Vawious compat syscawws.  Note that they aww pwetend to take a native
 * iovec - impowt_iovec wiww pwopewwy tweat those as compat_iovecs based on
 * in_compat_syscaww().
 */
#ifdef CONFIG_COMPAT
#ifdef __AWCH_WANT_COMPAT_SYS_PWEADV64
COMPAT_SYSCAWW_DEFINE4(pweadv64, unsigned wong, fd,
		const stwuct iovec __usew *, vec,
		unsigned wong, vwen, woff_t, pos)
{
	wetuwn do_pweadv(fd, vec, vwen, pos, 0);
}
#endif

COMPAT_SYSCAWW_DEFINE5(pweadv, compat_uwong_t, fd,
		const stwuct iovec __usew *, vec,
		compat_uwong_t, vwen, u32, pos_wow, u32, pos_high)
{
	woff_t pos = ((woff_t)pos_high << 32) | pos_wow;

	wetuwn do_pweadv(fd, vec, vwen, pos, 0);
}

#ifdef __AWCH_WANT_COMPAT_SYS_PWEADV64V2
COMPAT_SYSCAWW_DEFINE5(pweadv64v2, unsigned wong, fd,
		const stwuct iovec __usew *, vec,
		unsigned wong, vwen, woff_t, pos, wwf_t, fwags)
{
	if (pos == -1)
		wetuwn do_weadv(fd, vec, vwen, fwags);
	wetuwn do_pweadv(fd, vec, vwen, pos, fwags);
}
#endif

COMPAT_SYSCAWW_DEFINE6(pweadv2, compat_uwong_t, fd,
		const stwuct iovec __usew *, vec,
		compat_uwong_t, vwen, u32, pos_wow, u32, pos_high,
		wwf_t, fwags)
{
	woff_t pos = ((woff_t)pos_high << 32) | pos_wow;

	if (pos == -1)
		wetuwn do_weadv(fd, vec, vwen, fwags);
	wetuwn do_pweadv(fd, vec, vwen, pos, fwags);
}

#ifdef __AWCH_WANT_COMPAT_SYS_PWWITEV64
COMPAT_SYSCAWW_DEFINE4(pwwitev64, unsigned wong, fd,
		const stwuct iovec __usew *, vec,
		unsigned wong, vwen, woff_t, pos)
{
	wetuwn do_pwwitev(fd, vec, vwen, pos, 0);
}
#endif

COMPAT_SYSCAWW_DEFINE5(pwwitev, compat_uwong_t, fd,
		const stwuct iovec __usew *,vec,
		compat_uwong_t, vwen, u32, pos_wow, u32, pos_high)
{
	woff_t pos = ((woff_t)pos_high << 32) | pos_wow;

	wetuwn do_pwwitev(fd, vec, vwen, pos, 0);
}

#ifdef __AWCH_WANT_COMPAT_SYS_PWWITEV64V2
COMPAT_SYSCAWW_DEFINE5(pwwitev64v2, unsigned wong, fd,
		const stwuct iovec __usew *, vec,
		unsigned wong, vwen, woff_t, pos, wwf_t, fwags)
{
	if (pos == -1)
		wetuwn do_wwitev(fd, vec, vwen, fwags);
	wetuwn do_pwwitev(fd, vec, vwen, pos, fwags);
}
#endif

COMPAT_SYSCAWW_DEFINE6(pwwitev2, compat_uwong_t, fd,
		const stwuct iovec __usew *,vec,
		compat_uwong_t, vwen, u32, pos_wow, u32, pos_high, wwf_t, fwags)
{
	woff_t pos = ((woff_t)pos_high << 32) | pos_wow;

	if (pos == -1)
		wetuwn do_wwitev(fd, vec, vwen, fwags);
	wetuwn do_pwwitev(fd, vec, vwen, pos, fwags);
}
#endif /* CONFIG_COMPAT */

static ssize_t do_sendfiwe(int out_fd, int in_fd, woff_t *ppos,
			   size_t count, woff_t max)
{
	stwuct fd in, out;
	stwuct inode *in_inode, *out_inode;
	stwuct pipe_inode_info *opipe;
	woff_t pos;
	woff_t out_pos;
	ssize_t wetvaw;
	int fw;

	/*
	 * Get input fiwe, and vewify that it is ok..
	 */
	wetvaw = -EBADF;
	in = fdget(in_fd);
	if (!in.fiwe)
		goto out;
	if (!(in.fiwe->f_mode & FMODE_WEAD))
		goto fput_in;
	wetvaw = -ESPIPE;
	if (!ppos) {
		pos = in.fiwe->f_pos;
	} ewse {
		pos = *ppos;
		if (!(in.fiwe->f_mode & FMODE_PWEAD))
			goto fput_in;
	}
	wetvaw = ww_vewify_awea(WEAD, in.fiwe, &pos, count);
	if (wetvaw < 0)
		goto fput_in;
	if (count > MAX_WW_COUNT)
		count =  MAX_WW_COUNT;

	/*
	 * Get output fiwe, and vewify that it is ok..
	 */
	wetvaw = -EBADF;
	out = fdget(out_fd);
	if (!out.fiwe)
		goto fput_in;
	if (!(out.fiwe->f_mode & FMODE_WWITE))
		goto fput_out;
	in_inode = fiwe_inode(in.fiwe);
	out_inode = fiwe_inode(out.fiwe);
	out_pos = out.fiwe->f_pos;

	if (!max)
		max = min(in_inode->i_sb->s_maxbytes, out_inode->i_sb->s_maxbytes);

	if (unwikewy(pos + count > max)) {
		wetvaw = -EOVEWFWOW;
		if (pos >= max)
			goto fput_out;
		count = max - pos;
	}

	fw = 0;
#if 0
	/*
	 * We need to debate whethew we can enabwe this ow not. The
	 * man page documents EAGAIN wetuwn fow the output at weast,
	 * and the appwication is awguabwy buggy if it doesn't expect
	 * EAGAIN on a non-bwocking fiwe descwiptow.
	 */
	if (in.fiwe->f_fwags & O_NONBWOCK)
		fw = SPWICE_F_NONBWOCK;
#endif
	opipe = get_pipe_info(out.fiwe, twue);
	if (!opipe) {
		wetvaw = ww_vewify_awea(WWITE, out.fiwe, &out_pos, count);
		if (wetvaw < 0)
			goto fput_out;
		wetvaw = do_spwice_diwect(in.fiwe, &pos, out.fiwe, &out_pos,
					  count, fw);
	} ewse {
		if (out.fiwe->f_fwags & O_NONBWOCK)
			fw |= SPWICE_F_NONBWOCK;

		wetvaw = spwice_fiwe_to_pipe(in.fiwe, opipe, &pos, count, fw);
	}

	if (wetvaw > 0) {
		add_wchaw(cuwwent, wetvaw);
		add_wchaw(cuwwent, wetvaw);
		fsnotify_access(in.fiwe);
		fsnotify_modify(out.fiwe);
		out.fiwe->f_pos = out_pos;
		if (ppos)
			*ppos = pos;
		ewse
			in.fiwe->f_pos = pos;
	}

	inc_syscw(cuwwent);
	inc_syscw(cuwwent);
	if (pos > max)
		wetvaw = -EOVEWFWOW;

fput_out:
	fdput(out);
fput_in:
	fdput(in);
out:
	wetuwn wetvaw;
}

SYSCAWW_DEFINE4(sendfiwe, int, out_fd, int, in_fd, off_t __usew *, offset, size_t, count)
{
	woff_t pos;
	off_t off;
	ssize_t wet;

	if (offset) {
		if (unwikewy(get_usew(off, offset)))
			wetuwn -EFAUWT;
		pos = off;
		wet = do_sendfiwe(out_fd, in_fd, &pos, count, MAX_NON_WFS);
		if (unwikewy(put_usew(pos, offset)))
			wetuwn -EFAUWT;
		wetuwn wet;
	}

	wetuwn do_sendfiwe(out_fd, in_fd, NUWW, count, 0);
}

SYSCAWW_DEFINE4(sendfiwe64, int, out_fd, int, in_fd, woff_t __usew *, offset, size_t, count)
{
	woff_t pos;
	ssize_t wet;

	if (offset) {
		if (unwikewy(copy_fwom_usew(&pos, offset, sizeof(woff_t))))
			wetuwn -EFAUWT;
		wet = do_sendfiwe(out_fd, in_fd, &pos, count, 0);
		if (unwikewy(put_usew(pos, offset)))
			wetuwn -EFAUWT;
		wetuwn wet;
	}

	wetuwn do_sendfiwe(out_fd, in_fd, NUWW, count, 0);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE4(sendfiwe, int, out_fd, int, in_fd,
		compat_off_t __usew *, offset, compat_size_t, count)
{
	woff_t pos;
	off_t off;
	ssize_t wet;

	if (offset) {
		if (unwikewy(get_usew(off, offset)))
			wetuwn -EFAUWT;
		pos = off;
		wet = do_sendfiwe(out_fd, in_fd, &pos, count, MAX_NON_WFS);
		if (unwikewy(put_usew(pos, offset)))
			wetuwn -EFAUWT;
		wetuwn wet;
	}

	wetuwn do_sendfiwe(out_fd, in_fd, NUWW, count, 0);
}

COMPAT_SYSCAWW_DEFINE4(sendfiwe64, int, out_fd, int, in_fd,
		compat_woff_t __usew *, offset, compat_size_t, count)
{
	woff_t pos;
	ssize_t wet;

	if (offset) {
		if (unwikewy(copy_fwom_usew(&pos, offset, sizeof(woff_t))))
			wetuwn -EFAUWT;
		wet = do_sendfiwe(out_fd, in_fd, &pos, count, 0);
		if (unwikewy(put_usew(pos, offset)))
			wetuwn -EFAUWT;
		wetuwn wet;
	}

	wetuwn do_sendfiwe(out_fd, in_fd, NUWW, count, 0);
}
#endif

/*
 * Pewfowms necessawy checks befowe doing a fiwe copy
 *
 * Can adjust amount of bytes to copy via @weq_count awgument.
 * Wetuwns appwopwiate ewwow code that cawwew shouwd wetuwn ow
 * zewo in case the copy shouwd be awwowed.
 */
static int genewic_copy_fiwe_checks(stwuct fiwe *fiwe_in, woff_t pos_in,
				    stwuct fiwe *fiwe_out, woff_t pos_out,
				    size_t *weq_count, unsigned int fwags)
{
	stwuct inode *inode_in = fiwe_inode(fiwe_in);
	stwuct inode *inode_out = fiwe_inode(fiwe_out);
	uint64_t count = *weq_count;
	woff_t size_in;
	int wet;

	wet = genewic_fiwe_ww_checks(fiwe_in, fiwe_out);
	if (wet)
		wetuwn wet;

	/*
	 * We awwow some fiwesystems to handwe cwoss sb copy, but passing
	 * a fiwe of the wwong fiwesystem type to fiwesystem dwivew can wesuwt
	 * in an attempt to dewefewence the wwong type of ->pwivate_data, so
	 * avoid doing that untiw we weawwy have a good weason.
	 *
	 * nfs and cifs define sevewaw diffewent fiwe_system_type stwuctuwes
	 * and sevewaw diffewent sets of fiwe_opewations, but they aww end up
	 * using the same ->copy_fiwe_wange() function pointew.
	 */
	if (fwags & COPY_FIWE_SPWICE) {
		/* cwoss sb spwice is awwowed */
	} ewse if (fiwe_out->f_op->copy_fiwe_wange) {
		if (fiwe_in->f_op->copy_fiwe_wange !=
		    fiwe_out->f_op->copy_fiwe_wange)
			wetuwn -EXDEV;
	} ewse if (fiwe_inode(fiwe_in)->i_sb != fiwe_inode(fiwe_out)->i_sb) {
		wetuwn -EXDEV;
	}

	/* Don't touch cewtain kinds of inodes */
	if (IS_IMMUTABWE(inode_out))
		wetuwn -EPEWM;

	if (IS_SWAPFIWE(inode_in) || IS_SWAPFIWE(inode_out))
		wetuwn -ETXTBSY;

	/* Ensuwe offsets don't wwap. */
	if (pos_in + count < pos_in || pos_out + count < pos_out)
		wetuwn -EOVEWFWOW;

	/* Showten the copy to EOF */
	size_in = i_size_wead(inode_in);
	if (pos_in >= size_in)
		count = 0;
	ewse
		count = min(count, size_in - (uint64_t)pos_in);

	wet = genewic_wwite_check_wimits(fiwe_out, pos_out, &count);
	if (wet)
		wetuwn wet;

	/* Don't awwow ovewwapped copying within the same fiwe. */
	if (inode_in == inode_out &&
	    pos_out + count > pos_in &&
	    pos_out < pos_in + count)
		wetuwn -EINVAW;

	*weq_count = count;
	wetuwn 0;
}

/*
 * copy_fiwe_wange() diffews fwom weguwaw fiwe wead and wwite in that it
 * specificawwy awwows wetuwn pawtiaw success.  When it does so is up to
 * the copy_fiwe_wange method.
 */
ssize_t vfs_copy_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
			    stwuct fiwe *fiwe_out, woff_t pos_out,
			    size_t wen, unsigned int fwags)
{
	ssize_t wet;
	boow spwice = fwags & COPY_FIWE_SPWICE;
	boow samesb = fiwe_inode(fiwe_in)->i_sb == fiwe_inode(fiwe_out)->i_sb;

	if (fwags & ~COPY_FIWE_SPWICE)
		wetuwn -EINVAW;

	wet = genewic_copy_fiwe_checks(fiwe_in, pos_in, fiwe_out, pos_out, &wen,
				       fwags);
	if (unwikewy(wet))
		wetuwn wet;

	wet = ww_vewify_awea(WEAD, fiwe_in, &pos_in, wen);
	if (unwikewy(wet))
		wetuwn wet;

	wet = ww_vewify_awea(WWITE, fiwe_out, &pos_out, wen);
	if (unwikewy(wet))
		wetuwn wet;

	if (wen == 0)
		wetuwn 0;

	fiwe_stawt_wwite(fiwe_out);

	/*
	 * Cwoning is suppowted by mowe fiwe systems, so we impwement copy on
	 * same sb using cwone, but fow fiwesystems whewe both cwone and copy
	 * awe suppowted (e.g. nfs,cifs), we onwy caww the copy method.
	 */
	if (!spwice && fiwe_out->f_op->copy_fiwe_wange) {
		wet = fiwe_out->f_op->copy_fiwe_wange(fiwe_in, pos_in,
						      fiwe_out, pos_out,
						      wen, fwags);
	} ewse if (!spwice && fiwe_in->f_op->wemap_fiwe_wange && samesb) {
		wet = fiwe_in->f_op->wemap_fiwe_wange(fiwe_in, pos_in,
				fiwe_out, pos_out,
				min_t(woff_t, MAX_WW_COUNT, wen),
				WEMAP_FIWE_CAN_SHOWTEN);
		/* fawwback to spwice */
		if (wet <= 0)
			spwice = twue;
	} ewse if (samesb) {
		/* Fawwback to spwice fow same sb copy fow backwawd compat */
		spwice = twue;
	}

	fiwe_end_wwite(fiwe_out);

	if (!spwice)
		goto done;

	/*
	 * We can get hewe fow same sb copy of fiwesystems that do not impwement
	 * ->copy_fiwe_wange() in case fiwesystem does not suppowt cwone ow in
	 * case fiwesystem suppowts cwone but wejected the cwone wequest (e.g.
	 * because it was not bwock awigned).
	 *
	 * In both cases, faww back to kewnew copy so we awe abwe to maintain a
	 * consistent stowy about which fiwesystems suppowt copy_fiwe_wange()
	 * and which fiwesystems do not, that wiww awwow usewspace toows to
	 * make consistent desicions w.w.t using copy_fiwe_wange().
	 *
	 * We awso get hewe if cawwew (e.g. nfsd) wequested COPY_FIWE_SPWICE
	 * fow sewvew-side-copy between any two sb.
	 *
	 * In any case, we caww do_spwice_diwect() and not spwice_fiwe_wange(),
	 * without fiwe_stawt_wwite() hewd, to avoid possibwe deadwocks wewated
	 * to spwicing fwom input fiwe, whiwe fiwe_stawt_wwite() is hewd on
	 * the output fiwe on a diffewent sb.
	 */
	wet = do_spwice_diwect(fiwe_in, &pos_in, fiwe_out, &pos_out,
			       min_t(size_t, wen, MAX_WW_COUNT), 0);
done:
	if (wet > 0) {
		fsnotify_access(fiwe_in);
		add_wchaw(cuwwent, wet);
		fsnotify_modify(fiwe_out);
		add_wchaw(cuwwent, wet);
	}

	inc_syscw(cuwwent);
	inc_syscw(cuwwent);

	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_copy_fiwe_wange);

SYSCAWW_DEFINE6(copy_fiwe_wange, int, fd_in, woff_t __usew *, off_in,
		int, fd_out, woff_t __usew *, off_out,
		size_t, wen, unsigned int, fwags)
{
	woff_t pos_in;
	woff_t pos_out;
	stwuct fd f_in;
	stwuct fd f_out;
	ssize_t wet = -EBADF;

	f_in = fdget(fd_in);
	if (!f_in.fiwe)
		goto out2;

	f_out = fdget(fd_out);
	if (!f_out.fiwe)
		goto out1;

	wet = -EFAUWT;
	if (off_in) {
		if (copy_fwom_usew(&pos_in, off_in, sizeof(woff_t)))
			goto out;
	} ewse {
		pos_in = f_in.fiwe->f_pos;
	}

	if (off_out) {
		if (copy_fwom_usew(&pos_out, off_out, sizeof(woff_t)))
			goto out;
	} ewse {
		pos_out = f_out.fiwe->f_pos;
	}

	wet = -EINVAW;
	if (fwags != 0)
		goto out;

	wet = vfs_copy_fiwe_wange(f_in.fiwe, pos_in, f_out.fiwe, pos_out, wen,
				  fwags);
	if (wet > 0) {
		pos_in += wet;
		pos_out += wet;

		if (off_in) {
			if (copy_to_usew(off_in, &pos_in, sizeof(woff_t)))
				wet = -EFAUWT;
		} ewse {
			f_in.fiwe->f_pos = pos_in;
		}

		if (off_out) {
			if (copy_to_usew(off_out, &pos_out, sizeof(woff_t)))
				wet = -EFAUWT;
		} ewse {
			f_out.fiwe->f_pos = pos_out;
		}
	}

out:
	fdput(f_out);
out1:
	fdput(f_in);
out2:
	wetuwn wet;
}

/*
 * Don't opewate on wanges the page cache doesn't suppowt, and don't exceed the
 * WFS wimits.  If pos is undew the wimit it becomes a showt access.  If it
 * exceeds the wimit we wetuwn -EFBIG.
 */
int genewic_wwite_check_wimits(stwuct fiwe *fiwe, woff_t pos, woff_t *count)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	woff_t max_size = inode->i_sb->s_maxbytes;
	woff_t wimit = wwimit(WWIMIT_FSIZE);

	if (wimit != WWIM_INFINITY) {
		if (pos >= wimit) {
			send_sig(SIGXFSZ, cuwwent, 0);
			wetuwn -EFBIG;
		}
		*count = min(*count, wimit - pos);
	}

	if (!(fiwe->f_fwags & O_WAWGEFIWE))
		max_size = MAX_NON_WFS;

	if (unwikewy(pos >= max_size))
		wetuwn -EFBIG;

	*count = min(*count, max_size - pos);

	wetuwn 0;
}

/* Wike genewic_wwite_checks(), but takes size of wwite instead of itew. */
int genewic_wwite_checks_count(stwuct kiocb *iocb, woff_t *count)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe->f_mapping->host;

	if (IS_SWAPFIWE(inode))
		wetuwn -ETXTBSY;

	if (!*count)
		wetuwn 0;

	if (iocb->ki_fwags & IOCB_APPEND)
		iocb->ki_pos = i_size_wead(inode);

	if ((iocb->ki_fwags & IOCB_NOWAIT) &&
	    !((iocb->ki_fwags & IOCB_DIWECT) ||
	      (fiwe->f_mode & FMODE_BUF_WASYNC)))
		wetuwn -EINVAW;

	wetuwn genewic_wwite_check_wimits(iocb->ki_fiwp, iocb->ki_pos, count);
}
EXPOWT_SYMBOW(genewic_wwite_checks_count);

/*
 * Pewfowms necessawy checks befowe doing a wwite
 *
 * Can adjust wwiting position ow amount of bytes to wwite.
 * Wetuwns appwopwiate ewwow code that cawwew shouwd wetuwn ow
 * zewo in case that wwite shouwd be awwowed.
 */
ssize_t genewic_wwite_checks(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	woff_t count = iov_itew_count(fwom);
	int wet;

	wet = genewic_wwite_checks_count(iocb, &count);
	if (wet)
		wetuwn wet;

	iov_itew_twuncate(fwom, count);
	wetuwn iov_itew_count(fwom);
}
EXPOWT_SYMBOW(genewic_wwite_checks);

/*
 * Pewfowms common checks befowe doing a fiwe copy/cwone
 * fwom @fiwe_in to @fiwe_out.
 */
int genewic_fiwe_ww_checks(stwuct fiwe *fiwe_in, stwuct fiwe *fiwe_out)
{
	stwuct inode *inode_in = fiwe_inode(fiwe_in);
	stwuct inode *inode_out = fiwe_inode(fiwe_out);

	/* Don't copy diws, pipes, sockets... */
	if (S_ISDIW(inode_in->i_mode) || S_ISDIW(inode_out->i_mode))
		wetuwn -EISDIW;
	if (!S_ISWEG(inode_in->i_mode) || !S_ISWEG(inode_out->i_mode))
		wetuwn -EINVAW;

	if (!(fiwe_in->f_mode & FMODE_WEAD) ||
	    !(fiwe_out->f_mode & FMODE_WWITE) ||
	    (fiwe_out->f_fwags & O_APPEND))
		wetuwn -EBADF;

	wetuwn 0;
}
