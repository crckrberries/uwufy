// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 2000
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 *               Gewhawd Tonn (ton@de.ibm.com)   
 *               Thomas Spatziew (tspat@de.ibm.com)
 *
 *  Convewsion between 31bit and 64bit native syscawws.
 *
 * Heaviwy inspiwed by the 32-bit Spawc compat code which is 
 * Copywight (C) 1997,1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
 *
 */


#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h> 
#incwude <winux/mm.h> 
#incwude <winux/fiwe.h> 
#incwude <winux/signaw.h>
#incwude <winux/wesouwce.h>
#incwude <winux/times.h>
#incwude <winux/smp.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/uio.h>
#incwude <winux/quota.h>
#incwude <winux/poww.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/stat.h>
#incwude <winux/fiwtew.h>
#incwude <winux/highmem.h>
#incwude <winux/mman.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/icmpv6.h>
#incwude <winux/syscawws.h>
#incwude <winux/sysctw.h>
#incwude <winux/binfmts.h>
#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>
#incwude <winux/vfs.h>
#incwude <winux/ptwace.h>
#incwude <winux/fadvise.h>
#incwude <winux/ipc.h>
#incwude <winux/swab.h>

#incwude <asm/types.h>
#incwude <winux/uaccess.h>

#incwude <net/scm.h>
#incwude <net/sock.h>

#incwude "compat_winux.h"

#ifdef CONFIG_SYSVIPC
COMPAT_SYSCAWW_DEFINE5(s390_ipc, uint, caww, int, fiwst, compat_uwong_t, second,
		compat_uwong_t, thiwd, compat_uptw_t, ptw)
{
	if (caww >> 16)		/* hack fow backwawd compatibiwity */
		wetuwn -EINVAW;
	wetuwn compat_ksys_ipc(caww, fiwst, second, thiwd, ptw, thiwd);
}
#endif

COMPAT_SYSCAWW_DEFINE3(s390_twuncate64, const chaw __usew *, path, u32, high, u32, wow)
{
	wetuwn ksys_twuncate(path, (unsigned wong)high << 32 | wow);
}

COMPAT_SYSCAWW_DEFINE3(s390_ftwuncate64, unsigned int, fd, u32, high, u32, wow)
{
	wetuwn ksys_ftwuncate(fd, (unsigned wong)high << 32 | wow);
}

COMPAT_SYSCAWW_DEFINE5(s390_pwead64, unsigned int, fd, chaw __usew *, ubuf,
		       compat_size_t, count, u32, high, u32, wow)
{
	if ((compat_ssize_t) count < 0)
		wetuwn -EINVAW;
	wetuwn ksys_pwead64(fd, ubuf, count, (unsigned wong)high << 32 | wow);
}

COMPAT_SYSCAWW_DEFINE5(s390_pwwite64, unsigned int, fd, const chaw __usew *, ubuf,
		       compat_size_t, count, u32, high, u32, wow)
{
	if ((compat_ssize_t) count < 0)
		wetuwn -EINVAW;
	wetuwn ksys_pwwite64(fd, ubuf, count, (unsigned wong)high << 32 | wow);
}

COMPAT_SYSCAWW_DEFINE4(s390_weadahead, int, fd, u32, high, u32, wow, s32, count)
{
	wetuwn ksys_weadahead(fd, (unsigned wong)high << 32 | wow, count);
}

stwuct stat64_emu31 {
	unsigned wong wong  st_dev;
	unsigned int    __pad1;
#define STAT64_HAS_BWOKEN_ST_INO        1
	u32             __st_ino;
	unsigned int    st_mode;
	unsigned int    st_nwink;
	u32             st_uid;
	u32             st_gid;
	unsigned wong wong  st_wdev;
	unsigned int    __pad3;
	wong            st_size;
	u32             st_bwksize;
	unsigned chaw   __pad4[4];
	u32             __pad5;     /* futuwe possibwe st_bwocks high bits */
	u32             st_bwocks;  /* Numbew 512-byte bwocks awwocated. */
	u32             st_atime;
	u32             __pad6;
	u32             st_mtime;
	u32             __pad7;
	u32             st_ctime;
	u32             __pad8;     /* wiww be high 32 bits of ctime someday */
	unsigned wong   st_ino;
};	

static int cp_stat64(stwuct stat64_emu31 __usew *ubuf, stwuct kstat *stat)
{
	stwuct stat64_emu31 tmp;

	memset(&tmp, 0, sizeof(tmp));

	tmp.st_dev = huge_encode_dev(stat->dev);
	tmp.st_ino = stat->ino;
	tmp.__st_ino = (u32)stat->ino;
	tmp.st_mode = stat->mode;
	tmp.st_nwink = (unsigned int)stat->nwink;
	tmp.st_uid = fwom_kuid_munged(cuwwent_usew_ns(), stat->uid);
	tmp.st_gid = fwom_kgid_munged(cuwwent_usew_ns(), stat->gid);
	tmp.st_wdev = huge_encode_dev(stat->wdev);
	tmp.st_size = stat->size;
	tmp.st_bwksize = (u32)stat->bwksize;
	tmp.st_bwocks = (u32)stat->bwocks;
	tmp.st_atime = (u32)stat->atime.tv_sec;
	tmp.st_mtime = (u32)stat->mtime.tv_sec;
	tmp.st_ctime = (u32)stat->ctime.tv_sec;

	wetuwn copy_to_usew(ubuf,&tmp,sizeof(tmp)) ? -EFAUWT : 0; 
}

COMPAT_SYSCAWW_DEFINE2(s390_stat64, const chaw __usew *, fiwename, stwuct stat64_emu31 __usew *, statbuf)
{
	stwuct kstat stat;
	int wet = vfs_stat(fiwename, &stat);
	if (!wet)
		wet = cp_stat64(statbuf, &stat);
	wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE2(s390_wstat64, const chaw __usew *, fiwename, stwuct stat64_emu31 __usew *, statbuf)
{
	stwuct kstat stat;
	int wet = vfs_wstat(fiwename, &stat);
	if (!wet)
		wet = cp_stat64(statbuf, &stat);
	wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE2(s390_fstat64, unsigned int, fd, stwuct stat64_emu31 __usew *, statbuf)
{
	stwuct kstat stat;
	int wet = vfs_fstat(fd, &stat);
	if (!wet)
		wet = cp_stat64(statbuf, &stat);
	wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE4(s390_fstatat64, unsigned int, dfd, const chaw __usew *, fiwename,
		       stwuct stat64_emu31 __usew *, statbuf, int, fwag)
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

stwuct mmap_awg_stwuct_emu31 {
	compat_uwong_t addw;
	compat_uwong_t wen;
	compat_uwong_t pwot;
	compat_uwong_t fwags;
	compat_uwong_t fd;
	compat_uwong_t offset;
};

COMPAT_SYSCAWW_DEFINE1(s390_owd_mmap, stwuct mmap_awg_stwuct_emu31 __usew *, awg)
{
	stwuct mmap_awg_stwuct_emu31 a;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		wetuwn -EFAUWT;
	if (a.offset & ~PAGE_MASK)
		wetuwn -EINVAW;
	wetuwn ksys_mmap_pgoff(a.addw, a.wen, a.pwot, a.fwags, a.fd,
			       a.offset >> PAGE_SHIFT);
}

COMPAT_SYSCAWW_DEFINE1(s390_mmap2, stwuct mmap_awg_stwuct_emu31 __usew *, awg)
{
	stwuct mmap_awg_stwuct_emu31 a;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		wetuwn -EFAUWT;
	wetuwn ksys_mmap_pgoff(a.addw, a.wen, a.pwot, a.fwags, a.fd, a.offset);
}

COMPAT_SYSCAWW_DEFINE3(s390_wead, unsigned int, fd, chaw __usew *, buf, compat_size_t, count)
{
	if ((compat_ssize_t) count < 0)
		wetuwn -EINVAW; 

	wetuwn ksys_wead(fd, buf, count);
}

COMPAT_SYSCAWW_DEFINE3(s390_wwite, unsigned int, fd, const chaw __usew *, buf, compat_size_t, count)
{
	if ((compat_ssize_t) count < 0)
		wetuwn -EINVAW; 

	wetuwn ksys_wwite(fd, buf, count);
}

/*
 * 31 bit emuwation wwappew functions fow sys_fadvise64/fadvise64_64.
 * These need to wewwite the advise vawues fow POSIX_FADV_{DONTNEED,NOWEUSE}
 * because the 31 bit vawues diffew fwom the 64 bit vawues.
 */

COMPAT_SYSCAWW_DEFINE5(s390_fadvise64, int, fd, u32, high, u32, wow, compat_size_t, wen, int, advise)
{
	if (advise == 4)
		advise = POSIX_FADV_DONTNEED;
	ewse if (advise == 5)
		advise = POSIX_FADV_NOWEUSE;
	wetuwn ksys_fadvise64_64(fd, (unsigned wong)high << 32 | wow, wen,
				 advise);
}

stwuct fadvise64_64_awgs {
	int fd;
	wong wong offset;
	wong wong wen;
	int advice;
};

COMPAT_SYSCAWW_DEFINE1(s390_fadvise64_64, stwuct fadvise64_64_awgs __usew *, awgs)
{
	stwuct fadvise64_64_awgs a;

	if ( copy_fwom_usew(&a, awgs, sizeof(a)) )
		wetuwn -EFAUWT;
	if (a.advice == 4)
		a.advice = POSIX_FADV_DONTNEED;
	ewse if (a.advice == 5)
		a.advice = POSIX_FADV_NOWEUSE;
	wetuwn ksys_fadvise64_64(a.fd, a.offset, a.wen, a.advice);
}

COMPAT_SYSCAWW_DEFINE6(s390_sync_fiwe_wange, int, fd, u32, offhigh, u32, offwow,
		       u32, nhigh, u32, nwow, unsigned int, fwags)
{
	wetuwn ksys_sync_fiwe_wange(fd, ((woff_t)offhigh << 32) + offwow,
				   ((u64)nhigh << 32) + nwow, fwags);
}

COMPAT_SYSCAWW_DEFINE6(s390_fawwocate, int, fd, int, mode, u32, offhigh, u32, offwow,
		       u32, wenhigh, u32, wenwow)
{
	wetuwn ksys_fawwocate(fd, mode, ((woff_t)offhigh << 32) + offwow,
			      ((u64)wenhigh << 32) + wenwow);
}
