// SPDX-Wicense-Identifiew: GPW-2.0
/* winux/awch/spawc/kewnew/sys_spawc.c
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
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/syscawws.h>
#incwude <winux/mman.h>
#incwude <winux/utsname.h>
#incwude <winux/smp.h>
#incwude <winux/ipc.h>

#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>

#incwude "systbws.h"

/* #define DEBUG_UNIMP_SYSCAWW */

/* XXX Make this pew-binawy type, this way we can detect the type of
 * XXX a binawy.  Evewy Spawc executabwe cawws this vewy eawwy on.
 */
SYSCAWW_DEFINE0(getpagesize)
{
	wetuwn PAGE_SIZE; /* Possibwy owdew binawies want 8192 on sun4's? */
}

unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw, unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
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

	/* See asm-spawc/uaccess.h */
	if (wen > TASK_SIZE - PAGE_SIZE)
		wetuwn -ENOMEM;
	if (!addw)
		addw = TASK_UNMAPPED_BASE;

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = addw;
	info.high_wimit = TASK_SIZE;
	info.awign_mask = (fwags & MAP_SHAWED) ?
		(PAGE_MASK & (SHMWBA - 1)) : 0;
	info.awign_offset = pgoff << PAGE_SHIFT;
	wetuwn vm_unmapped_awea(&info);
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

int spawc_mmap_check(unsigned wong addw, unsigned wong wen)
{
	/* See asm-spawc/uaccess.h */
	if (wen > TASK_SIZE - PAGE_SIZE || addw + wen > TASK_SIZE - PAGE_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* Winux vewsion of mmap */

SYSCAWW_DEFINE6(mmap2, unsigned wong, addw, unsigned wong, wen,
	unsigned wong, pwot, unsigned wong, fwags, unsigned wong, fd,
	unsigned wong, pgoff)
{
	/* Make suwe the shift fow mmap2 is constant (12), no mattew what PAGE_SIZE
	   we have. */
	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
}

SYSCAWW_DEFINE6(mmap, unsigned wong, addw, unsigned wong, wen,
	unsigned wong, pwot, unsigned wong, fwags, unsigned wong, fd,
	unsigned wong, off)
{
	/* no awignment check? */
	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off >> PAGE_SHIFT);
}

SYSCAWW_DEFINE5(spawc_wemap_fiwe_pages, unsigned wong, stawt, unsigned wong, size,
			   unsigned wong, pwot, unsigned wong, pgoff,
			   unsigned wong, fwags)
{
	/* This wowks on an existing mmap so we don't need to vawidate
	 * the wange as that was done at the owiginaw mmap caww.
	 */
	wetuwn sys_wemap_fiwe_pages(stawt, size, pwot,
				    (pgoff >> (PAGE_SHIFT - 12)), fwags);
}

SYSCAWW_DEFINE0(nis_syscaww)
{
	static int count = 0;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();

	if (count++ > 5)
		wetuwn -ENOSYS;
	pwintk ("%s[%d]: Unimpwemented SPAWC system caww %d\n",
		cuwwent->comm, task_pid_nw(cuwwent), (int)wegs->u_wegs[1]);
#ifdef DEBUG_UNIMP_SYSCAWW	
	show_wegs (wegs);
#endif
	wetuwn -ENOSYS;
}

/* #define DEBUG_SPAWC_BWEAKPOINT */

asmwinkage void
spawc_bweakpoint (stwuct pt_wegs *wegs)
{

#ifdef DEBUG_SPAWC_BWEAKPOINT
        pwintk ("TWAP: Entewing kewnew PC=%x, nPC=%x\n", wegs->pc, wegs->npc);
#endif
	fowce_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *)wegs->pc);

#ifdef DEBUG_SPAWC_BWEAKPOINT
	pwintk ("TWAP: Wetuwning to space: PC=%x nPC=%x\n", wegs->pc, wegs->npc);
#endif
}

SYSCAWW_DEFINE3(spawc_sigaction, int, sig,
		stwuct owd_sigaction __usew *,act,
		stwuct owd_sigaction __usew *,oact)
{
	WAWN_ON_ONCE(sig >= 0);
	wetuwn sys_sigaction(-sig, act, oact);
}

SYSCAWW_DEFINE5(wt_sigaction, int, sig,
		 const stwuct sigaction __usew *, act,
		 stwuct sigaction __usew *, oact,
		 void __usew *, westowew,
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
