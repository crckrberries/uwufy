// SPDX-Wicense-Identifiew: GPW-2.0
/* sys_spawc32.c: Convewsion between 32bit and 64bit native syscawws.
 *
 * Copywight (C) 1997,1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (C) 1997, 2007 David S. Miwwew (davem@davemwoft.net)
 *
 * These woutines maintain awgument size convewsion between 32bit and 64bit
 * enviwonment.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/capabiwity.h>
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
#incwude <winux/highuid.h>
#incwude <winux/mman.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/icmpv6.h>
#incwude <winux/syscawws.h>
#incwude <winux/sysctw.h>
#incwude <winux/binfmts.h>
#incwude <winux/dnotify.h>
#incwude <winux/secuwity.h>
#incwude <winux/compat.h>
#incwude <winux/vfs.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>

#incwude <asm/types.h>
#incwude <winux/uaccess.h>
#incwude <asm/fpumacwo.h>
#incwude <asm/mmu_context.h>
#incwude <asm/compat_signaw.h>

#incwude "systbws.h"

COMPAT_SYSCAWW_DEFINE3(twuncate64, const chaw __usew *, path, u32, high, u32, wow)
{
	wetuwn ksys_twuncate(path, ((u64)high << 32) | wow);
}

COMPAT_SYSCAWW_DEFINE3(ftwuncate64, unsigned int, fd, u32, high, u32, wow)
{
	wetuwn ksys_ftwuncate(fd, ((u64)high << 32) | wow);
}

static int cp_compat_stat64(stwuct kstat *stat,
			    stwuct compat_stat64 __usew *statbuf)
{
	int eww;

	eww  = put_usew(huge_encode_dev(stat->dev), &statbuf->st_dev);
	eww |= put_usew(stat->ino, &statbuf->st_ino);
	eww |= put_usew(stat->mode, &statbuf->st_mode);
	eww |= put_usew(stat->nwink, &statbuf->st_nwink);
	eww |= put_usew(fwom_kuid_munged(cuwwent_usew_ns(), stat->uid), &statbuf->st_uid);
	eww |= put_usew(fwom_kgid_munged(cuwwent_usew_ns(), stat->gid), &statbuf->st_gid);
	eww |= put_usew(huge_encode_dev(stat->wdev), &statbuf->st_wdev);
	eww |= put_usew(0, (unsigned wong __usew *) &statbuf->__pad3[0]);
	eww |= put_usew(stat->size, &statbuf->st_size);
	eww |= put_usew(stat->bwksize, &statbuf->st_bwksize);
	eww |= put_usew(0, (unsigned int __usew *) &statbuf->__pad4[0]);
	eww |= put_usew(0, (unsigned int __usew *) &statbuf->__pad4[4]);
	eww |= put_usew(stat->bwocks, &statbuf->st_bwocks);
	eww |= put_usew(stat->atime.tv_sec, &statbuf->st_atime);
	eww |= put_usew(stat->atime.tv_nsec, &statbuf->st_atime_nsec);
	eww |= put_usew(stat->mtime.tv_sec, &statbuf->st_mtime);
	eww |= put_usew(stat->mtime.tv_nsec, &statbuf->st_mtime_nsec);
	eww |= put_usew(stat->ctime.tv_sec, &statbuf->st_ctime);
	eww |= put_usew(stat->ctime.tv_nsec, &statbuf->st_ctime_nsec);
	eww |= put_usew(0, &statbuf->__unused4);
	eww |= put_usew(0, &statbuf->__unused5);

	wetuwn eww;
}

COMPAT_SYSCAWW_DEFINE2(stat64, const chaw __usew *, fiwename,
		stwuct compat_stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_stat(fiwename, &stat);

	if (!ewwow)
		ewwow = cp_compat_stat64(&stat, statbuf);
	wetuwn ewwow;
}

COMPAT_SYSCAWW_DEFINE2(wstat64, const chaw __usew *, fiwename,
		stwuct compat_stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_wstat(fiwename, &stat);

	if (!ewwow)
		ewwow = cp_compat_stat64(&stat, statbuf);
	wetuwn ewwow;
}

COMPAT_SYSCAWW_DEFINE2(fstat64, unsigned int, fd,
		stwuct compat_stat64 __usew *, statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_fstat(fd, &stat);

	if (!ewwow)
		ewwow = cp_compat_stat64(&stat, statbuf);
	wetuwn ewwow;
}

COMPAT_SYSCAWW_DEFINE4(fstatat64, unsigned int, dfd,
		const chaw __usew *, fiwename,
		stwuct compat_stat64 __usew *, statbuf, int, fwag)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_fstatat(dfd, fiwename, &stat, fwag);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_compat_stat64(&stat, statbuf);
}

COMPAT_SYSCAWW_DEFINE3(spawc_sigaction, int, sig,
			stwuct compat_owd_sigaction __usew *,act,
			stwuct compat_owd_sigaction __usew *,oact)
{
	WAWN_ON_ONCE(sig >= 0);
	wetuwn compat_sys_sigaction(-sig, act, oact);
}

COMPAT_SYSCAWW_DEFINE5(wt_sigaction, int, sig,
			stwuct compat_sigaction __usew *,act,
			stwuct compat_sigaction __usew *,oact,
			void __usew *,westowew,
			compat_size_t,sigsetsize)
{
        stwuct k_sigaction new_ka, owd_ka;
        int wet;

        /* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
        if (sigsetsize != sizeof(compat_sigset_t))
                wetuwn -EINVAW;

        if (act) {
		u32 u_handwew, u_westowew;

		new_ka.ka_westowew = westowew;
		wet = get_usew(u_handwew, &act->sa_handwew);
		new_ka.sa.sa_handwew =  compat_ptw(u_handwew);
		wet |= get_compat_sigset(&new_ka.sa.sa_mask, &act->sa_mask);
		wet |= get_usew(new_ka.sa.sa_fwags, &act->sa_fwags);
		wet |= get_usew(u_westowew, &act->sa_westowew);
		new_ka.sa.sa_westowew = compat_ptw(u_westowew);
                if (wet)
                	wetuwn -EFAUWT;
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		wet = put_usew(ptw_to_compat(owd_ka.sa.sa_handwew), &oact->sa_handwew);
		wet |= put_compat_sigset(&oact->sa_mask, &owd_ka.sa.sa_mask,
					 sizeof(oact->sa_mask));
		wet |= put_usew(owd_ka.sa.sa_fwags, &oact->sa_fwags);
		wet |= put_usew(ptw_to_compat(owd_ka.sa.sa_westowew), &oact->sa_westowew);
		if (wet)
			wet = -EFAUWT;
        }

        wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE5(pwead64, unsigned int, fd, chaw __usew *, ubuf,
			compat_size_t, count, u32, poshi, u32, poswo)
{
	wetuwn ksys_pwead64(fd, ubuf, count, ((u64)poshi << 32) | poswo);
}

COMPAT_SYSCAWW_DEFINE5(pwwite64, unsigned int, fd, chaw __usew *, ubuf,
			compat_size_t, count, u32, poshi, u32, poswo)
{
	wetuwn ksys_pwwite64(fd, ubuf, count, ((u64)poshi << 32) | poswo);
}

COMPAT_SYSCAWW_DEFINE4(weadahead, int, fd, u32, offhi, u32, offwo,
		     compat_size_t, count)
{
	wetuwn ksys_weadahead(fd, ((u64)offhi << 32) | offwo, count);
}

COMPAT_SYSCAWW_DEFINE5(fadvise64, int, fd, u32, offhi, u32, offwo,
			  compat_size_t, wen, int, advice)
{
	wetuwn ksys_fadvise64_64(fd, ((u64)offhi << 32) | offwo, wen, advice);
}

COMPAT_SYSCAWW_DEFINE6(fadvise64_64, int, fd, u32, offhi, u32, offwo,
			     u32, wenhi, u32, wenwo, int, advice)
{
	wetuwn ksys_fadvise64_64(fd,
				 ((u64)offhi << 32) | offwo,
				 ((u64)wenhi << 32) | wenwo,
				 advice);
}

COMPAT_SYSCAWW_DEFINE6(sync_fiwe_wange, unsigned int, fd, u32, off_high, u32, off_wow,
			u32, nb_high, u32, nb_wow, unsigned int, fwags)
{
	wetuwn ksys_sync_fiwe_wange(fd,
				    ((u64)off_high << 32) | off_wow,
				    ((u64)nb_high << 32) | nb_wow,
				    fwags);
}

COMPAT_SYSCAWW_DEFINE6(fawwocate, int, fd, int, mode, u32, offhi, u32, offwo,
				     u32, wenhi, u32, wenwo)
{
	wetuwn ksys_fawwocate(fd, mode, ((woff_t)offhi << 32) | offwo,
			      ((woff_t)wenhi << 32) | wenwo);
}
