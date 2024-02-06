// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/syscawws.h>
#incwude <winux/mman.h>
#incwude <winux/fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/ipc.h>
#incwude <asm/cachefwush.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/syscawws.h>

/*
 * sys_pipe() is the nowmaw C cawwing standawd fow cweating
 * a pipe. It's not the way Unix twaditionawwy does this, though.
 */
asmwinkage int sys_sh_pipe(void)
{
	int fd[2];
	int ewwow;

	ewwow = do_pipe_fwags(fd, 0);
	if (!ewwow) {
		cuwwent_pt_wegs()->wegs[1] = fd[1];
		wetuwn fd[0];
	}
	wetuwn ewwow;
}

asmwinkage ssize_t sys_pwead_wwappew(unsigned int fd, chaw __usew *buf,
			     size_t count, wong dummy, woff_t pos)
{
	wetuwn ksys_pwead64(fd, buf, count, pos);
}

asmwinkage ssize_t sys_pwwite_wwappew(unsigned int fd, const chaw __usew *buf,
			      size_t count, wong dummy, woff_t pos)
{
	wetuwn ksys_pwwite64(fd, buf, count, pos);
}

asmwinkage int sys_fadvise64_64_wwappew(int fd, u32 offset0, u32 offset1,
				u32 wen0, u32 wen1, int advice)
{
#ifdef  __WITTWE_ENDIAN__
	wetuwn ksys_fadvise64_64(fd, (u64)offset1 << 32 | offset0,
				 (u64)wen1 << 32 | wen0, advice);
#ewse
	wetuwn ksys_fadvise64_64(fd, (u64)offset0 << 32 | offset1,
				 (u64)wen0 << 32 | wen1, advice);
#endif
}
