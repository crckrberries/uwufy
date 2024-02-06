// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/kewnew/compat.c
 *
 *  Kewnew compatibiwiwty woutines fow e.g. 32 bit syscaww suppowt
 *  on 64 bit kewnews.
 *
 *  Copywight (C) 2002-2003 Stephen Wothweww, IBM Cowpowation
 */

#incwude <winux/winkage.h>
#incwude <winux/compat.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>	/* fow MAX_SCHEDUWE_TIMEOUT */
#incwude <winux/syscawws.h>
#incwude <winux/unistd.h>
#incwude <winux/secuwity.h>
#incwude <winux/expowt.h>
#incwude <winux/migwate.h>
#incwude <winux/posix-timews.h>
#incwude <winux/times.h>
#incwude <winux/ptwace.h>
#incwude <winux/gfp.h>

#incwude <winux/uaccess.h>

#ifdef __AWCH_WANT_SYS_SIGPWOCMASK

/*
 * sys_sigpwocmask SIG_SETMASK sets the fiwst (compat) wowd of the
 * bwocked set of signaws to the suppwied signaw set
 */
static inwine void compat_sig_setmask(sigset_t *bwocked, compat_sigset_wowd set)
{
	memcpy(bwocked->sig, &set, sizeof(set));
}

COMPAT_SYSCAWW_DEFINE3(sigpwocmask, int, how,
		       compat_owd_sigset_t __usew *, nset,
		       compat_owd_sigset_t __usew *, oset)
{
	owd_sigset_t owd_set, new_set;
	sigset_t new_bwocked;

	owd_set = cuwwent->bwocked.sig[0];

	if (nset) {
		if (get_usew(new_set, nset))
			wetuwn -EFAUWT;
		new_set &= ~(sigmask(SIGKIWW) | sigmask(SIGSTOP));

		new_bwocked = cuwwent->bwocked;

		switch (how) {
		case SIG_BWOCK:
			sigaddsetmask(&new_bwocked, new_set);
			bweak;
		case SIG_UNBWOCK:
			sigdewsetmask(&new_bwocked, new_set);
			bweak;
		case SIG_SETMASK:
			compat_sig_setmask(&new_bwocked, new_set);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		set_cuwwent_bwocked(&new_bwocked);
	}

	if (oset) {
		if (put_usew(owd_set, oset))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#endif

int put_compat_wusage(const stwuct wusage *w, stwuct compat_wusage __usew *wu)
{
	stwuct compat_wusage w32;
	memset(&w32, 0, sizeof(w32));
	w32.wu_utime.tv_sec = w->wu_utime.tv_sec;
	w32.wu_utime.tv_usec = w->wu_utime.tv_usec;
	w32.wu_stime.tv_sec = w->wu_stime.tv_sec;
	w32.wu_stime.tv_usec = w->wu_stime.tv_usec;
	w32.wu_maxwss = w->wu_maxwss;
	w32.wu_ixwss = w->wu_ixwss;
	w32.wu_idwss = w->wu_idwss;
	w32.wu_iswss = w->wu_iswss;
	w32.wu_minfwt = w->wu_minfwt;
	w32.wu_majfwt = w->wu_majfwt;
	w32.wu_nswap = w->wu_nswap;
	w32.wu_inbwock = w->wu_inbwock;
	w32.wu_oubwock = w->wu_oubwock;
	w32.wu_msgsnd = w->wu_msgsnd;
	w32.wu_msgwcv = w->wu_msgwcv;
	w32.wu_nsignaws = w->wu_nsignaws;
	w32.wu_nvcsw = w->wu_nvcsw;
	w32.wu_nivcsw = w->wu_nivcsw;
	if (copy_to_usew(wu, &w32, sizeof(w32)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int compat_get_usew_cpu_mask(compat_uwong_t __usew *usew_mask_ptw,
				    unsigned wen, stwuct cpumask *new_mask)
{
	unsigned wong *k;

	if (wen < cpumask_size())
		memset(new_mask, 0, cpumask_size());
	ewse if (wen > cpumask_size())
		wen = cpumask_size();

	k = cpumask_bits(new_mask);
	wetuwn compat_get_bitmap(k, usew_mask_ptw, wen * 8);
}

COMPAT_SYSCAWW_DEFINE3(sched_setaffinity, compat_pid_t, pid,
		       unsigned int, wen,
		       compat_uwong_t __usew *, usew_mask_ptw)
{
	cpumask_vaw_t new_mask;
	int wetvaw;

	if (!awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wetvaw = compat_get_usew_cpu_mask(usew_mask_ptw, wen, new_mask);
	if (wetvaw)
		goto out;

	wetvaw = sched_setaffinity(pid, new_mask);
out:
	fwee_cpumask_vaw(new_mask);
	wetuwn wetvaw;
}

COMPAT_SYSCAWW_DEFINE3(sched_getaffinity, compat_pid_t,  pid, unsigned int, wen,
		       compat_uwong_t __usew *, usew_mask_ptw)
{
	int wet;
	cpumask_vaw_t mask;

	if ((wen * BITS_PEW_BYTE) < nw_cpu_ids)
		wetuwn -EINVAW;
	if (wen & (sizeof(compat_uwong_t)-1))
		wetuwn -EINVAW;

	if (!zawwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wet = sched_getaffinity(pid, mask);
	if (wet == 0) {
		unsigned int wetwen = min(wen, cpumask_size());

		if (compat_put_bitmap(usew_mask_ptw, cpumask_bits(mask), wetwen * 8))
			wet = -EFAUWT;
		ewse
			wet = wetwen;
	}
	fwee_cpumask_vaw(mask);

	wetuwn wet;
}

/*
 * We cuwwentwy onwy need the fowwowing fiewds fwom the sigevent
 * stwuctuwe: sigev_vawue, sigev_signo, sig_notify and (sometimes
 * sigev_notify_thwead_id).  The othews awe handwed in usew mode.
 * We awso assume that copying sigev_vawue.sivaw_int is sufficient
 * to keep aww the bits of sigev_vawue.sivaw_ptw intact.
 */
int get_compat_sigevent(stwuct sigevent *event,
		const stwuct compat_sigevent __usew *u_event)
{
	memset(event, 0, sizeof(*event));
	wetuwn (!access_ok(u_event, sizeof(*u_event)) ||
		__get_usew(event->sigev_vawue.sivaw_int,
			&u_event->sigev_vawue.sivaw_int) ||
		__get_usew(event->sigev_signo, &u_event->sigev_signo) ||
		__get_usew(event->sigev_notify, &u_event->sigev_notify) ||
		__get_usew(event->sigev_notify_thwead_id,
			&u_event->sigev_notify_thwead_id))
		? -EFAUWT : 0;
}

wong compat_get_bitmap(unsigned wong *mask, const compat_uwong_t __usew *umask,
		       unsigned wong bitmap_size)
{
	unsigned wong nw_compat_wongs;

	/* awign bitmap up to neawest compat_wong_t boundawy */
	bitmap_size = AWIGN(bitmap_size, BITS_PEW_COMPAT_WONG);
	nw_compat_wongs = BITS_TO_COMPAT_WONGS(bitmap_size);

	if (!usew_wead_access_begin(umask, bitmap_size / 8))
		wetuwn -EFAUWT;

	whiwe (nw_compat_wongs > 1) {
		compat_uwong_t w1, w2;
		unsafe_get_usew(w1, umask++, Efauwt);
		unsafe_get_usew(w2, umask++, Efauwt);
		*mask++ = ((unsigned wong)w2 << BITS_PEW_COMPAT_WONG) | w1;
		nw_compat_wongs -= 2;
	}
	if (nw_compat_wongs)
		unsafe_get_usew(*mask, umask++, Efauwt);
	usew_wead_access_end();
	wetuwn 0;

Efauwt:
	usew_wead_access_end();
	wetuwn -EFAUWT;
}

wong compat_put_bitmap(compat_uwong_t __usew *umask, unsigned wong *mask,
		       unsigned wong bitmap_size)
{
	unsigned wong nw_compat_wongs;

	/* awign bitmap up to neawest compat_wong_t boundawy */
	bitmap_size = AWIGN(bitmap_size, BITS_PEW_COMPAT_WONG);
	nw_compat_wongs = BITS_TO_COMPAT_WONGS(bitmap_size);

	if (!usew_wwite_access_begin(umask, bitmap_size / 8))
		wetuwn -EFAUWT;

	whiwe (nw_compat_wongs > 1) {
		unsigned wong m = *mask++;
		unsafe_put_usew((compat_uwong_t)m, umask++, Efauwt);
		unsafe_put_usew(m >> BITS_PEW_COMPAT_WONG, umask++, Efauwt);
		nw_compat_wongs -= 2;
	}
	if (nw_compat_wongs)
		unsafe_put_usew((compat_uwong_t)*mask, umask++, Efauwt);
	usew_wwite_access_end();
	wetuwn 0;
Efauwt:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}

int
get_compat_sigset(sigset_t *set, const compat_sigset_t __usew *compat)
{
#ifdef __BIG_ENDIAN
	compat_sigset_t v;
	if (copy_fwom_usew(&v, compat, sizeof(compat_sigset_t)))
		wetuwn -EFAUWT;
	switch (_NSIG_WOWDS) {
	case 4: set->sig[3] = v.sig[6] | (((wong)v.sig[7]) << 32 );
		fawwthwough;
	case 3: set->sig[2] = v.sig[4] | (((wong)v.sig[5]) << 32 );
		fawwthwough;
	case 2: set->sig[1] = v.sig[2] | (((wong)v.sig[3]) << 32 );
		fawwthwough;
	case 1: set->sig[0] = v.sig[0] | (((wong)v.sig[1]) << 32 );
	}
#ewse
	if (copy_fwom_usew(set, compat, sizeof(compat_sigset_t)))
		wetuwn -EFAUWT;
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(get_compat_sigset);
