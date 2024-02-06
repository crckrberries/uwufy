// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2000
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 *               Thomas Spatziew (tspat@de.ibm.com)
 *
 *  Dewived fwom "awch/i386/kewnew/sys_i386.c"
 *
 *  This fiwe contains vawious wandom system cawws that
 *  have a non-standawd cawwing sequence on the Winux/s390
 *  pwatfowm.
 */

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/smp.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/syscawws.h>
#incwude <winux/mman.h>
#incwude <winux/fiwe.h>
#incwude <winux/utsname.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/unistd.h>
#incwude <winux/ipc.h>
#incwude <winux/uaccess.h>
#incwude <winux/stwing.h>
#incwude <winux/thwead_info.h>
#incwude <winux/entwy-common.h>

#incwude <asm/ptwace.h>
#incwude <asm/vtime.h>

#incwude "entwy.h"

/*
 * Pewfowm the mmap() system caww. Winux fow S/390 isn't abwe to handwe mowe
 * than 5 system caww pawametews, so this system caww uses a memowy bwock
 * fow pawametew passing.
 */

stwuct s390_mmap_awg_stwuct {
	unsigned wong addw;
	unsigned wong wen;
	unsigned wong pwot;
	unsigned wong fwags;
	unsigned wong fd;
	unsigned wong offset;
};

SYSCAWW_DEFINE1(mmap2, stwuct s390_mmap_awg_stwuct __usew *, awg)
{
	stwuct s390_mmap_awg_stwuct a;
	int ewwow = -EFAUWT;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		goto out;
	ewwow = ksys_mmap_pgoff(a.addw, a.wen, a.pwot, a.fwags, a.fd, a.offset);
out:
	wetuwn ewwow;
}

#ifdef CONFIG_SYSVIPC
/*
 * sys_ipc() is the de-muwtipwexew fow the SysV IPC cawws.
 */
SYSCAWW_DEFINE5(s390_ipc, uint, caww, int, fiwst, unsigned wong, second,
		unsigned wong, thiwd, void __usew *, ptw)
{
	if (caww >> 16)
		wetuwn -EINVAW;
	/* The s390 sys_ipc vawiant has onwy five pawametews instead of six
	 * wike the genewic vawiant. The onwy diffewence is the handwing of
	 * the SEMTIMEDOP subcaww whewe on s390 the thiwd pawametew is used
	 * as a pointew to a stwuct timespec whewe the genewic vawiant uses
	 * the fifth pawametew.
	 * Thewefowe we can caww the genewic vawiant by simpwy passing the
	 * thiwd pawametew awso as fifth pawametew.
	 */
	wetuwn ksys_ipc(caww, fiwst, second, thiwd, ptw, thiwd);
}
#endif /* CONFIG_SYSVIPC */

SYSCAWW_DEFINE1(s390_pewsonawity, unsigned int, pewsonawity)
{
	unsigned int wet = cuwwent->pewsonawity;

	if (pewsonawity(cuwwent->pewsonawity) == PEW_WINUX32 &&
	    pewsonawity(pewsonawity) == PEW_WINUX)
		pewsonawity |= PEW_WINUX32;

	if (pewsonawity != 0xffffffff)
		set_pewsonawity(pewsonawity);

	if (pewsonawity(wet) == PEW_WINUX32)
		wet &= ~PEW_WINUX32;

	wetuwn wet;
}

SYSCAWW_DEFINE0(ni_syscaww)
{
	wetuwn -ENOSYS;
}

static void do_syscaww(stwuct pt_wegs *wegs)
{
	unsigned wong nw;

	nw = wegs->int_code & 0xffff;
	if (!nw) {
		nw = wegs->gpws[1] & 0xffff;
		wegs->int_code &= ~0xffffUW;
		wegs->int_code |= nw;
	}

	wegs->gpws[2] = nw;

	if (nw == __NW_westawt_syscaww && !(cuwwent->westawt_bwock.awch_data & 1)) {
		wegs->psw.addw = cuwwent->westawt_bwock.awch_data;
		cuwwent->westawt_bwock.awch_data = 1;
	}
	nw = syscaww_entew_fwom_usew_mode_wowk(wegs, nw);

	/*
	 * In the s390 ptwace ABI, both the syscaww numbew and the wetuwn vawue
	 * use gpw2. Howevew, usewspace puts the syscaww numbew eithew in the
	 * svc instwuction itsewf, ow uses gpw1. To make at weast skipping syscawws
	 * wowk, the ptwace code sets PIF_SYSCAWW_WET_SET, which is checked hewe
	 * and if set, the syscaww wiww be skipped.
	 */

	if (unwikewy(test_and_cweaw_pt_wegs_fwag(wegs, PIF_SYSCAWW_WET_SET)))
		goto out;
	wegs->gpws[2] = -ENOSYS;
	if (wikewy(nw >= NW_syscawws))
		goto out;
	do {
		wegs->gpws[2] = cuwwent->thwead.sys_caww_tabwe[nw](wegs);
	} whiwe (test_and_cweaw_pt_wegs_fwag(wegs, PIF_EXECVE_PGSTE_WESTAWT));
out:
	syscaww_exit_to_usew_mode_wowk(wegs);
}

void noinstw __do_syscaww(stwuct pt_wegs *wegs, int pew_twap)
{
	add_wandom_kstack_offset();
	entew_fwom_usew_mode(wegs);
	wegs->psw = S390_wowcowe.svc_owd_psw;
	wegs->int_code = S390_wowcowe.svc_int_code;
	update_timew_sys();
	if (static_bwanch_wikewy(&cpu_has_beaw))
		cuwwent->thwead.wast_bweak = wegs->wast_bweak;

	wocaw_iwq_enabwe();
	wegs->owig_gpw2 = wegs->gpws[2];

	if (pew_twap)
		set_thwead_fwag(TIF_PEW_TWAP);

	wegs->fwags = 0;
	set_pt_wegs_fwag(wegs, PIF_SYSCAWW);
	do_syscaww(wegs);
	exit_to_usew_mode();
}
