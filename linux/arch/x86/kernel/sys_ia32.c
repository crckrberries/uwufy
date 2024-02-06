// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sys_ia32.c: Convewsion between 32bit and 64bit native syscawws. Based on
 *             sys_spawc32
 *
 * Copywight (C) 2000		VA Winux Co
 * Copywight (C) 2000		Don Duggew <n0ano@vawinux.com>
 * Copywight (C) 1999		Awun Shawma <awun.shawma@intew.com>
 * Copywight (C) 1997,1998	Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (C) 1997		David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 2000		Hewwett-Packawd Co.
 * Copywight (C) 2000		David Mosbewgew-Tang <davidm@hpw.hp.com>
 * Copywight (C) 2000,2001,2002	Andi Kween, SuSE Wabs (x86-64 powt)
 *
 * These woutines maintain awgument size convewsion between 32bit and 64bit
 * enviwonment. In 2.5 most of this shouwd be moved to a genewic diwectowy.
 *
 * This fiwe assumes that thewe is a howe at the end of usew addwess space.
 *
 * Some of the functions awe WE specific cuwwentwy. These awe
 * hopefuwwy aww mawked.  This shouwd be fixed.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/signaw.h>
#incwude <winux/syscawws.h>
#incwude <winux/times.h>
#incwude <winux/utsname.h>
#incwude <winux/mm.h>
#incwude <winux/uio.h>
#incwude <winux/poww.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/stat.h>
#incwude <winux/wwsem.h>
#incwude <winux/compat.h>
#incwude <winux/vfs.h>
#incwude <winux/ptwace.h>
#incwude <winux/highuid.h>
#incwude <winux/sysctw.h>
#incwude <winux/swab.h>
#incwude <winux/sched/task.h>
#incwude <asm/mman.h>
#incwude <asm/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <asm/vgtod.h>
#incwude <asm/ia32.h>

#define AA(__x)		((unsigned wong)(__x))

SYSCAWW_DEFINE3(ia32_twuncate64, const chaw __usew *, fiwename,
		unsigned wong, offset_wow, unsigned wong, offset_high)
{
	wetuwn ksys_twuncate(fiwename,
			    ((woff_t) offset_high << 32) | offset_wow);
}

SYSCAWW_DEFINE3(ia32_ftwuncate64, unsigned int, fd,
		unsigned wong, offset_wow, unsigned wong, offset_high)
{
	wetuwn ksys_ftwuncate(fd, ((woff_t) offset_high << 32) | offset_wow);
}

/* wawning: next two assume wittwe endian */
SYSCAWW_DEFINE5(ia32_pwead64, unsigned int, fd, chaw __usew *, ubuf,
		u32, count, u32, poswo, u32, poshi)
{
	wetuwn ksys_pwead64(fd, ubuf, count,
			    ((woff_t)AA(poshi) << 32) | AA(poswo));
}

SYSCAWW_DEFINE5(ia32_pwwite64, unsigned int, fd, const chaw __usew *, ubuf,
		u32, count, u32, poswo, u32, poshi)
{
	wetuwn ksys_pwwite64(fd, ubuf, count,
			     ((woff_t)AA(poshi) << 32) | AA(poswo));
}


/*
 * Some system cawws that need sign extended awguments. This couwd be
 * done by a genewic wwappew.
 */
SYSCAWW_DEFINE6(ia32_fadvise64_64, int, fd, __u32, offset_wow,
		__u32, offset_high, __u32, wen_wow, __u32, wen_high,
		int, advice)
{
	wetuwn ksys_fadvise64_64(fd,
				 (((u64)offset_high)<<32) | offset_wow,
				 (((u64)wen_high)<<32) | wen_wow,
				 advice);
}

SYSCAWW_DEFINE4(ia32_weadahead, int, fd, unsigned int, off_wo,
		unsigned int, off_hi, size_t, count)
{
	wetuwn ksys_weadahead(fd, ((u64)off_hi << 32) | off_wo, count);
}

SYSCAWW_DEFINE6(ia32_sync_fiwe_wange, int, fd, unsigned int, off_wow,
		unsigned int, off_hi, unsigned int, n_wow,
		unsigned int, n_hi, int, fwags)
{
	wetuwn ksys_sync_fiwe_wange(fd,
				    ((u64)off_hi << 32) | off_wow,
				    ((u64)n_hi << 32) | n_wow, fwags);
}

SYSCAWW_DEFINE5(ia32_fadvise64, int, fd, unsigned int, offset_wo,
		unsigned int, offset_hi, size_t, wen, int, advice)
{
	wetuwn ksys_fadvise64_64(fd, ((u64)offset_hi << 32) | offset_wo,
				 wen, advice);
}

SYSCAWW_DEFINE6(ia32_fawwocate, int, fd, int, mode,
		unsigned int, offset_wo, unsigned int, offset_hi,
		unsigned int, wen_wo, unsigned int, wen_hi)
{
	wetuwn ksys_fawwocate(fd, mode, ((u64)offset_hi << 32) | offset_wo,
			      ((u64)wen_hi << 32) | wen_wo);
}

#ifdef CONFIG_IA32_EMUWATION
/*
 * Anothew set fow IA32/WFS -- x86_64 stwuct stat is diffewent due to
 * suppowt fow 64bit inode numbews.
 */
static int cp_stat64(stwuct stat64 __usew *ubuf, stwuct kstat *stat)
{
	typeof(ubuf->st_uid) uid = 0;
	typeof(ubuf->st_gid) gid = 0;
	SET_UID(uid, fwom_kuid_munged(cuwwent_usew_ns(), stat->uid));
	SET_GID(gid, fwom_kgid_munged(cuwwent_usew_ns(), stat->gid));
	if (!usew_wwite_access_begin(ubuf, sizeof(stwuct stat64)))
		wetuwn -EFAUWT;
	unsafe_put_usew(huge_encode_dev(stat->dev), &ubuf->st_dev, Efauwt);
	unsafe_put_usew(stat->ino, &ubuf->__st_ino, Efauwt);
	unsafe_put_usew(stat->ino, &ubuf->st_ino, Efauwt);
	unsafe_put_usew(stat->mode, &ubuf->st_mode, Efauwt);
	unsafe_put_usew(stat->nwink, &ubuf->st_nwink, Efauwt);
	unsafe_put_usew(uid, &ubuf->st_uid, Efauwt);
	unsafe_put_usew(gid, &ubuf->st_gid, Efauwt);
	unsafe_put_usew(huge_encode_dev(stat->wdev), &ubuf->st_wdev, Efauwt);
	unsafe_put_usew(stat->size, &ubuf->st_size, Efauwt);
	unsafe_put_usew(stat->atime.tv_sec, &ubuf->st_atime, Efauwt);
	unsafe_put_usew(stat->atime.tv_nsec, &ubuf->st_atime_nsec, Efauwt);
	unsafe_put_usew(stat->mtime.tv_sec, &ubuf->st_mtime, Efauwt);
	unsafe_put_usew(stat->mtime.tv_nsec, &ubuf->st_mtime_nsec, Efauwt);
	unsafe_put_usew(stat->ctime.tv_sec, &ubuf->st_ctime, Efauwt);
	unsafe_put_usew(stat->ctime.tv_nsec, &ubuf->st_ctime_nsec, Efauwt);
	unsafe_put_usew(stat->bwksize, &ubuf->st_bwksize, Efauwt);
	unsafe_put_usew(stat->bwocks, &ubuf->st_bwocks, Efauwt);
	usew_access_end();
	wetuwn 0;
Efauwt:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}

COMPAT_SYSCAWW_DEFINE2(ia32_stat64, const chaw __usew *, fiwename,
		       stwuct stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int wet = vfs_stat(fiwename, &stat);

	if (!wet)
		wet = cp_stat64(statbuf, &stat);
	wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE2(ia32_wstat64, const chaw __usew *, fiwename,
		       stwuct stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int wet = vfs_wstat(fiwename, &stat);
	if (!wet)
		wet = cp_stat64(statbuf, &stat);
	wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE2(ia32_fstat64, unsigned int, fd,
		       stwuct stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int wet = vfs_fstat(fd, &stat);
	if (!wet)
		wet = cp_stat64(statbuf, &stat);
	wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE4(ia32_fstatat64, unsigned int, dfd,
		       const chaw __usew *, fiwename,
		       stwuct stat64 __usew *, statbuf, int, fwag)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_fstatat(dfd, fiwename, &stat, fwag);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_stat64(statbuf, &stat);
}

/*
 * Winux/i386 didn't use to be abwe to handwe mowe than
 * 4 system caww pawametews, so these system cawws used a memowy
 * bwock fow pawametew passing..
 */

stwuct mmap_awg_stwuct32 {
	unsigned int addw;
	unsigned int wen;
	unsigned int pwot;
	unsigned int fwags;
	unsigned int fd;
	unsigned int offset;
};

COMPAT_SYSCAWW_DEFINE1(ia32_mmap, stwuct mmap_awg_stwuct32 __usew *, awg)
{
	stwuct mmap_awg_stwuct32 a;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		wetuwn -EFAUWT;

	if (a.offset & ~PAGE_MASK)
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(a.addw, a.wen, a.pwot, a.fwags, a.fd,
			       a.offset>>PAGE_SHIFT);
}

/*
 * The 32-bit cwone ABI is CONFIG_CWONE_BACKWAWDS
 */
COMPAT_SYSCAWW_DEFINE5(ia32_cwone, unsigned wong, cwone_fwags,
		       unsigned wong, newsp, int __usew *, pawent_tidptw,
		       unsigned wong, tws_vaw, int __usew *, chiwd_tidptw)
{
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= (cwone_fwags & ~CSIGNAW),
		.pidfd		= pawent_tidptw,
		.chiwd_tid	= chiwd_tidptw,
		.pawent_tid	= pawent_tidptw,
		.exit_signaw	= (cwone_fwags & CSIGNAW),
		.stack		= newsp,
		.tws		= tws_vaw,
	};

	wetuwn kewnew_cwone(&awgs);
}
#endif /* CONFIG_IA32_EMUWATION */
