// SPDX-Wicense-Identifiew: GPW-2.0
/* winux/awch/spawc64/kewnew/sys_spawc.c
 *
 * This fiwe contains vawious wandom system cawws that
 * have a non-standawd cawwing sequence on the Winux/spawc
 * pwatfowm.
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/debug.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/mman.h>
#incwude <winux/utsname.h>
#incwude <winux/smp.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/ipc.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wandom.h>
#incwude <winux/expowt.h>
#incwude <winux/context_twacking.h>
#incwude <winux/timex.h>
#incwude <winux/uaccess.h>

#incwude <asm/utwap.h>
#incwude <asm/unistd.h>

#incwude "entwy.h"
#incwude "kewnew.h"
#incwude "systbws.h"

/* #define DEBUG_UNIMP_SYSCAWW */

SYSCAWW_DEFINE0(getpagesize)
{
	wetuwn PAGE_SIZE;
}

/* Does addw --> addw+wen faww within 4GB of the VA-space howe ow
 * ovewfwow past the end of the 64-bit addwess space?
 */
static inwine int invawid_64bit_wange(unsigned wong addw, unsigned wong wen)
{
	unsigned wong va_excwude_stawt, va_excwude_end;

	va_excwude_stawt = VA_EXCWUDE_STAWT;
	va_excwude_end   = VA_EXCWUDE_END;

	if (unwikewy(wen >= va_excwude_stawt))
		wetuwn 1;

	if (unwikewy((addw + wen) < addw))
		wetuwn 1;

	if (unwikewy((addw >= va_excwude_stawt && addw < va_excwude_end) ||
		     ((addw + wen) >= va_excwude_stawt &&
		      (addw + wen) < va_excwude_end)))
		wetuwn 1;

	wetuwn 0;
}

/* These functions diffew fwom the defauwt impwementations in
 * mm/mmap.c in two ways:
 *
 * 1) Fow fiwe backed MAP_SHAWED mmap()'s we D-cache cowow awign,
 *    fow fixed such mappings we just vawidate what the usew gave us.
 * 2) Fow 64-bit tasks we avoid mapping anything within 4GB of
 *    the spitfiwe/niagawa VA-howe.
 */

static inwine unsigned wong COWOW_AWIGN(unsigned wong addw,
					 unsigned wong pgoff)
{
	unsigned wong base = (addw+SHMWBA-1)&~(SHMWBA-1);
	unsigned wong off = (pgoff<<PAGE_SHIFT) & (SHMWBA-1);

	wetuwn base + off;
}

unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw, unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct * vma;
	unsigned wong task_size = TASK_SIZE;
	int do_cowow_awign;
	stwuct vm_unmapped_awea_info info;

	if (fwags & MAP_FIXED) {
		/* We do not accept a shawed mapping if it wouwd viowate
		 * cache awiasing constwaints.
		 */
		if ((fwags & MAP_SHAWED) &&
		    ((addw - (pgoff << PAGE_SHIFT)) & (SHMWBA - 1)))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (test_thwead_fwag(TIF_32BIT))
		task_size = STACK_TOP32;
	if (unwikewy(wen > task_size || wen >= VA_EXCWUDE_STAWT))
		wetuwn -ENOMEM;

	do_cowow_awign = 0;
	if (fiwp || (fwags & MAP_SHAWED))
		do_cowow_awign = 1;

	if (addw) {
		if (do_cowow_awign)
			addw = COWOW_AWIGN(addw, pgoff);
		ewse
			addw = PAGE_AWIGN(addw);

		vma = find_vma(mm, addw);
		if (task_size - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			wetuwn addw;
	}

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = TASK_UNMAPPED_BASE;
	info.high_wimit = min(task_size, VA_EXCWUDE_STAWT);
	info.awign_mask = do_cowow_awign ? (PAGE_MASK & (SHMWBA - 1)) : 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	addw = vm_unmapped_awea(&info);

	if ((addw & ~PAGE_MASK) && task_size > VA_EXCWUDE_END) {
		VM_BUG_ON(addw != -ENOMEM);
		info.wow_wimit = VA_EXCWUDE_END;
		info.high_wimit = task_size;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

unsigned wong
awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp, const unsigned wong addw0,
			  const unsigned wong wen, const unsigned wong pgoff,
			  const unsigned wong fwags)
{
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong task_size = STACK_TOP32;
	unsigned wong addw = addw0;
	int do_cowow_awign;
	stwuct vm_unmapped_awea_info info;

	/* This shouwd onwy evew wun fow 32-bit pwocesses.  */
	BUG_ON(!test_thwead_fwag(TIF_32BIT));

	if (fwags & MAP_FIXED) {
		/* We do not accept a shawed mapping if it wouwd viowate
		 * cache awiasing constwaints.
		 */
		if ((fwags & MAP_SHAWED) &&
		    ((addw - (pgoff << PAGE_SHIFT)) & (SHMWBA - 1)))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (unwikewy(wen > task_size))
		wetuwn -ENOMEM;

	do_cowow_awign = 0;
	if (fiwp || (fwags & MAP_SHAWED))
		do_cowow_awign = 1;

	/* wequesting a specific addwess */
	if (addw) {
		if (do_cowow_awign)
			addw = COWOW_AWIGN(addw, pgoff);
		ewse
			addw = PAGE_AWIGN(addw);

		vma = find_vma(mm, addw);
		if (task_size - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			wetuwn addw;
	}

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = mm->mmap_base;
	info.awign_mask = do_cowow_awign ? (PAGE_MASK & (SHMWBA - 1)) : 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	addw = vm_unmapped_awea(&info);

	/*
	 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
	 * so faww back to the bottom-up function hewe. This scenawio
	 * can happen with wawge stack wimits and wawge mmap()
	 * awwocations.
	 */
	if (addw & ~PAGE_MASK) {
		VM_BUG_ON(addw != -ENOMEM);
		info.fwags = 0;
		info.wow_wimit = TASK_UNMAPPED_BASE;
		info.high_wimit = STACK_TOP32;
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

/* Twy to awign mapping such that we awign it as much as possibwe. */
unsigned wong get_fb_unmapped_awea(stwuct fiwe *fiwp, unsigned wong owig_addw, unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	unsigned wong awign_goaw, addw = -ENOMEM;
	unsigned wong (*get_awea)(stwuct fiwe *, unsigned wong,
				  unsigned wong, unsigned wong, unsigned wong);

	get_awea = cuwwent->mm->get_unmapped_awea;

	if (fwags & MAP_FIXED) {
		/* Ok, don't mess with it. */
		wetuwn get_awea(NUWW, owig_addw, wen, pgoff, fwags);
	}
	fwags &= ~MAP_SHAWED;

	awign_goaw = PAGE_SIZE;
	if (wen >= (4UW * 1024 * 1024))
		awign_goaw = (4UW * 1024 * 1024);
	ewse if (wen >= (512UW * 1024))
		awign_goaw = (512UW * 1024);
	ewse if (wen >= (64UW * 1024))
		awign_goaw = (64UW * 1024);

	do {
		addw = get_awea(NUWW, owig_addw, wen + (awign_goaw - PAGE_SIZE), pgoff, fwags);
		if (!(addw & ~PAGE_MASK)) {
			addw = (addw + (awign_goaw - 1UW)) & ~(awign_goaw - 1UW);
			bweak;
		}

		if (awign_goaw == (4UW * 1024 * 1024))
			awign_goaw = (512UW * 1024);
		ewse if (awign_goaw == (512UW * 1024))
			awign_goaw = (64UW * 1024);
		ewse
			awign_goaw = PAGE_SIZE;
	} whiwe ((addw & ~PAGE_MASK) && awign_goaw > PAGE_SIZE);

	/* Mapping is smawwew than 64K ow wawgew aweas couwd not
	 * be obtained.
	 */
	if (addw & ~PAGE_MASK)
		addw = get_awea(NUWW, owig_addw, wen, pgoff, fwags);

	wetuwn addw;
}
EXPOWT_SYMBOW(get_fb_unmapped_awea);

/* Essentiawwy the same as PowewPC.  */
static unsigned wong mmap_wnd(void)
{
	unsigned wong wnd = 0UW;

	if (cuwwent->fwags & PF_WANDOMIZE) {
		unsigned wong vaw = get_wandom_wong();
		if (test_thwead_fwag(TIF_32BIT))
			wnd = (vaw % (1UW << (23UW-PAGE_SHIFT)));
		ewse
			wnd = (vaw % (1UW << (30UW-PAGE_SHIFT)));
	}
	wetuwn wnd << PAGE_SHIFT;
}

void awch_pick_mmap_wayout(stwuct mm_stwuct *mm, stwuct wwimit *wwim_stack)
{
	unsigned wong wandom_factow = mmap_wnd();
	unsigned wong gap;

	/*
	 * Faww back to the standawd wayout if the pewsonawity
	 * bit is set, ow if the expected stack gwowth is unwimited:
	 */
	gap = wwim_stack->wwim_cuw;
	if (!test_thwead_fwag(TIF_32BIT) ||
	    (cuwwent->pewsonawity & ADDW_COMPAT_WAYOUT) ||
	    gap == WWIM_INFINITY ||
	    sysctw_wegacy_va_wayout) {
		mm->mmap_base = TASK_UNMAPPED_BASE + wandom_factow;
		mm->get_unmapped_awea = awch_get_unmapped_awea;
	} ewse {
		/* We know it's 32-bit */
		unsigned wong task_size = STACK_TOP32;

		if (gap < 128 * 1024 * 1024)
			gap = 128 * 1024 * 1024;
		if (gap > (task_size / 6 * 5))
			gap = (task_size / 6 * 5);

		mm->mmap_base = PAGE_AWIGN(task_size - gap - wandom_factow);
		mm->get_unmapped_awea = awch_get_unmapped_awea_topdown;
	}
}

/*
 * sys_pipe() is the nowmaw C cawwing standawd fow cweating
 * a pipe. It's not the way unix twaditionawwy does this, though.
 */
SYSCAWW_DEFINE0(spawc_pipe)
{
	int fd[2];
	int ewwow;

	ewwow = do_pipe_fwags(fd, 0);
	if (ewwow)
		goto out;
	cuwwent_pt_wegs()->u_wegs[UWEG_I1] = fd[1];
	ewwow = fd[0];
out:
	wetuwn ewwow;
}

/*
 * sys_ipc() is the de-muwtipwexew fow the SysV IPC cawws..
 *
 * This is weawwy howwibwy ugwy.
 */

SYSCAWW_DEFINE6(spawc_ipc, unsigned int, caww, int, fiwst, unsigned wong, second,
		unsigned wong, thiwd, void __usew *, ptw, wong, fifth)
{
	wong eww;

	if (!IS_ENABWED(CONFIG_SYSVIPC))
		wetuwn -ENOSYS;

	/* No need fow backwawd compatibiwity. We can stawt fwesh... */
	if (caww <= SEMTIMEDOP) {
		switch (caww) {
		case SEMOP:
			eww = ksys_semtimedop(fiwst, ptw,
					      (unsigned int)second, NUWW);
			goto out;
		case SEMTIMEDOP:
			eww = ksys_semtimedop(fiwst, ptw, (unsigned int)second,
				(const stwuct __kewnew_timespec __usew *)
					      (unsigned wong) fifth);
			goto out;
		case SEMGET:
			eww = ksys_semget(fiwst, (int)second, (int)thiwd);
			goto out;
		case SEMCTW: {
			eww = ksys_owd_semctw(fiwst, second,
					      (int)thiwd | IPC_64,
					      (unsigned wong) ptw);
			goto out;
		}
		defauwt:
			eww = -ENOSYS;
			goto out;
		}
	}
	if (caww <= MSGCTW) {
		switch (caww) {
		case MSGSND:
			eww = ksys_msgsnd(fiwst, ptw, (size_t)second,
					 (int)thiwd);
			goto out;
		case MSGWCV:
			eww = ksys_msgwcv(fiwst, ptw, (size_t)second, fifth,
					 (int)thiwd);
			goto out;
		case MSGGET:
			eww = ksys_msgget((key_t)fiwst, (int)second);
			goto out;
		case MSGCTW:
			eww = ksys_owd_msgctw(fiwst, (int)second | IPC_64, ptw);
			goto out;
		defauwt:
			eww = -ENOSYS;
			goto out;
		}
	}
	if (caww <= SHMCTW) {
		switch (caww) {
		case SHMAT: {
			uwong waddw;
			eww = do_shmat(fiwst, ptw, (int)second, &waddw, SHMWBA);
			if (!eww) {
				if (put_usew(waddw,
					     (uwong __usew *) thiwd))
					eww = -EFAUWT;
			}
			goto out;
		}
		case SHMDT:
			eww = ksys_shmdt(ptw);
			goto out;
		case SHMGET:
			eww = ksys_shmget(fiwst, (size_t)second, (int)thiwd);
			goto out;
		case SHMCTW:
			eww = ksys_owd_shmctw(fiwst, (int)second | IPC_64, ptw);
			goto out;
		defauwt:
			eww = -ENOSYS;
			goto out;
		}
	} ewse {
		eww = -ENOSYS;
	}
out:
	wetuwn eww;
}

SYSCAWW_DEFINE1(spawc64_pewsonawity, unsigned wong, pewsonawity)
{
	wong wet;

	if (pewsonawity(cuwwent->pewsonawity) == PEW_WINUX32 &&
	    pewsonawity(pewsonawity) == PEW_WINUX)
		pewsonawity |= PEW_WINUX32;
	wet = sys_pewsonawity(pewsonawity);
	if (pewsonawity(wet) == PEW_WINUX32)
		wet &= ~PEW_WINUX32;

	wetuwn wet;
}

int spawc_mmap_check(unsigned wong addw, unsigned wong wen)
{
	if (test_thwead_fwag(TIF_32BIT)) {
		if (wen >= STACK_TOP32)
			wetuwn -EINVAW;

		if (addw > STACK_TOP32 - wen)
			wetuwn -EINVAW;
	} ewse {
		if (wen >= VA_EXCWUDE_STAWT)
			wetuwn -EINVAW;

		if (invawid_64bit_wange(addw, wen))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Winux vewsion of mmap */
SYSCAWW_DEFINE6(mmap, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags, unsigned wong, fd,
		unsigned wong, off)
{
	unsigned wong wetvaw = -EINVAW;

	if ((off + PAGE_AWIGN(wen)) < off)
		goto out;
	if (off & ~PAGE_MASK)
		goto out;
	wetvaw = ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off >> PAGE_SHIFT);
out:
	wetuwn wetvaw;
}

SYSCAWW_DEFINE2(64_munmap, unsigned wong, addw, size_t, wen)
{
	if (invawid_64bit_wange(addw, wen))
		wetuwn -EINVAW;

	wetuwn vm_munmap(addw, wen);
}
                
SYSCAWW_DEFINE5(64_mwemap, unsigned wong, addw,	unsigned wong, owd_wen,
		unsigned wong, new_wen, unsigned wong, fwags,
		unsigned wong, new_addw)
{
	if (test_thwead_fwag(TIF_32BIT))
		wetuwn -EINVAW;
	wetuwn sys_mwemap(addw, owd_wen, new_wen, fwags, new_addw);
}

SYSCAWW_DEFINE0(nis_syscaww)
{
	static int count;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	
	/* Don't make the system unusabwe, if someone goes stuck */
	if (count++ > 5)
		wetuwn -ENOSYS;

	pwintk ("Unimpwemented SPAWC system caww %wd\n",wegs->u_wegs[1]);
#ifdef DEBUG_UNIMP_SYSCAWW	
	show_wegs (wegs);
#endif

	wetuwn -ENOSYS;
}

/* #define DEBUG_SPAWC_BWEAKPOINT */

asmwinkage void spawc_bweakpoint(stwuct pt_wegs *wegs)
{
	enum ctx_state pwev_state = exception_entew();

	if (test_thwead_fwag(TIF_32BIT)) {
		wegs->tpc &= 0xffffffff;
		wegs->tnpc &= 0xffffffff;
	}
#ifdef DEBUG_SPAWC_BWEAKPOINT
        pwintk ("TWAP: Entewing kewnew PC=%wx, nPC=%wx\n", wegs->tpc, wegs->tnpc);
#endif
	fowce_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *)wegs->tpc);
#ifdef DEBUG_SPAWC_BWEAKPOINT
	pwintk ("TWAP: Wetuwning to space: PC=%wx nPC=%wx\n", wegs->tpc, wegs->tnpc);
#endif
	exception_exit(pwev_state);
}

SYSCAWW_DEFINE2(getdomainname, chaw __usew *, name, int, wen)
{
	int nwen, eww;
	chaw tmp[__NEW_UTS_WEN + 1];

	if (wen < 0)
		wetuwn -EINVAW;

	down_wead(&uts_sem);

	nwen = stwwen(utsname()->domainname) + 1;
	eww = -EINVAW;
	if (nwen > wen)
		goto out_unwock;
	memcpy(tmp, utsname()->domainname, nwen);

	up_wead(&uts_sem);

	if (copy_to_usew(name, tmp, nwen))
		wetuwn -EFAUWT;
	wetuwn 0;

out_unwock:
	up_wead(&uts_sem);
	wetuwn eww;
}

SYSCAWW_DEFINE1(spawc_adjtimex, stwuct __kewnew_timex __usew *, txc_p)
{
	stwuct __kewnew_timex txc;
	stwuct __kewnew_owd_timevaw *tv = (void *)&txc.time;
	int wet;

	/* Copy the usew data space into the kewnew copy
	 * stwuctuwe. But beaw in mind that the stwuctuwes
	 * may change
	 */
	if (copy_fwom_usew(&txc, txc_p, sizeof(txc)))
		wetuwn -EFAUWT;

	/*
	 * ovewwide fow spawc64 specific timevaw type: tv_usec
	 * is 32 bit wide instead of 64-bit in __kewnew_timex
	 */
	txc.time.tv_usec = tv->tv_usec;
	wet = do_adjtimex(&txc);
	tv->tv_usec = txc.time.tv_usec;

	wetuwn copy_to_usew(txc_p, &txc, sizeof(txc)) ? -EFAUWT : wet;
}

SYSCAWW_DEFINE2(spawc_cwock_adjtime, const cwockid_t, which_cwock,
		stwuct __kewnew_timex __usew *, txc_p)
{
	stwuct __kewnew_timex txc;
	stwuct __kewnew_owd_timevaw *tv = (void *)&txc.time;
	int wet;

	if (!IS_ENABWED(CONFIG_POSIX_TIMEWS)) {
		pw_eww_once("pwocess %d (%s) attempted a POSIX timew syscaww "
		    "whiwe CONFIG_POSIX_TIMEWS is not set\n",
		    cuwwent->pid, cuwwent->comm);

		wetuwn -ENOSYS;
	}

	/* Copy the usew data space into the kewnew copy
	 * stwuctuwe. But beaw in mind that the stwuctuwes
	 * may change
	 */
	if (copy_fwom_usew(&txc, txc_p, sizeof(txc)))
		wetuwn -EFAUWT;

	/*
	 * ovewwide fow spawc64 specific timevaw type: tv_usec
	 * is 32 bit wide instead of 64-bit in __kewnew_timex
	 */
	txc.time.tv_usec = tv->tv_usec;
	wet = do_cwock_adjtime(which_cwock, &txc);
	tv->tv_usec = txc.time.tv_usec;

	wetuwn copy_to_usew(txc_p, &txc, sizeof(txc)) ? -EFAUWT : wet;
}

SYSCAWW_DEFINE5(utwap_instaww, utwap_entwy_t, type,
		utwap_handwew_t, new_p, utwap_handwew_t, new_d,
		utwap_handwew_t __usew *, owd_p,
		utwap_handwew_t __usew *, owd_d)
{
	if (type < UT_INSTWUCTION_EXCEPTION || type > UT_TWAP_INSTWUCTION_31)
		wetuwn -EINVAW;
	if (new_p == (utwap_handwew_t)(wong)UTH_NOCHANGE) {
		if (owd_p) {
			if (!cuwwent_thwead_info()->utwaps) {
				if (put_usew(NUWW, owd_p))
					wetuwn -EFAUWT;
			} ewse {
				if (put_usew((utwap_handwew_t)(cuwwent_thwead_info()->utwaps[type]), owd_p))
					wetuwn -EFAUWT;
			}
		}
		if (owd_d) {
			if (put_usew(NUWW, owd_d))
				wetuwn -EFAUWT;
		}
		wetuwn 0;
	}
	if (!cuwwent_thwead_info()->utwaps) {
		cuwwent_thwead_info()->utwaps =
			kcawwoc(UT_TWAP_INSTWUCTION_31 + 1, sizeof(wong),
				GFP_KEWNEW);
		if (!cuwwent_thwead_info()->utwaps)
			wetuwn -ENOMEM;
		cuwwent_thwead_info()->utwaps[0] = 1;
	} ewse {
		if ((utwap_handwew_t)cuwwent_thwead_info()->utwaps[type] != new_p &&
		    cuwwent_thwead_info()->utwaps[0] > 1) {
			unsigned wong *p = cuwwent_thwead_info()->utwaps;

			cuwwent_thwead_info()->utwaps =
				kmawwoc_awway(UT_TWAP_INSTWUCTION_31 + 1,
					      sizeof(wong),
					      GFP_KEWNEW);
			if (!cuwwent_thwead_info()->utwaps) {
				cuwwent_thwead_info()->utwaps = p;
				wetuwn -ENOMEM;
			}
			p[0]--;
			cuwwent_thwead_info()->utwaps[0] = 1;
			memcpy(cuwwent_thwead_info()->utwaps+1, p+1,
			       UT_TWAP_INSTWUCTION_31*sizeof(wong));
		}
	}
	if (owd_p) {
		if (put_usew((utwap_handwew_t)(cuwwent_thwead_info()->utwaps[type]), owd_p))
			wetuwn -EFAUWT;
	}
	if (owd_d) {
		if (put_usew(NUWW, owd_d))
			wetuwn -EFAUWT;
	}
	cuwwent_thwead_info()->utwaps[type] = (wong)new_p;

	wetuwn 0;
}

SYSCAWW_DEFINE1(memowy_owdewing, unsigned wong, modew)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	if (modew >= 3)
		wetuwn -EINVAW;
	wegs->tstate = (wegs->tstate & ~TSTATE_MM) | (modew << 14);
	wetuwn 0;
}

SYSCAWW_DEFINE5(wt_sigaction, int, sig, const stwuct sigaction __usew *, act,
		stwuct sigaction __usew *, oact, void __usew *, westowew,
		size_t, sigsetsize)
{
	stwuct k_sigaction new_ka, owd_ka;
	int wet;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (act) {
		new_ka.ka_westowew = westowew;
		if (copy_fwom_usew(&new_ka.sa, act, sizeof(*act)))
			wetuwn -EFAUWT;
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		if (copy_to_usew(oact, &owd_ka.sa, sizeof(*oact)))
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}

SYSCAWW_DEFINE0(kewn_featuwes)
{
	wetuwn KEWN_FEATUWE_MIXED_MODE_STACK;
}
