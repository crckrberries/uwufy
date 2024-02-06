// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sys_pawisc32.c: Convewsion between 32bit and 64bit native syscawws.
 *
 * Copywight (C) 2000-2001 Hewwett Packawd Company
 * Copywight (C) 2000 John Mawvin
 * Copywight (C) 2001 Matthew Wiwcox
 * Copywight (C) 2014 Hewge Dewwew <dewwew@gmx.de>
 *
 * These woutines maintain awgument size convewsion between 32bit and 64bit
 * enviwonment. Based heaviwy on sys_ia32.c and sys_spawc32.c.
 */

#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>


asmwinkage wong sys32_unimpwemented(int w26, int w25, int w24, int w23,
	int w22, int w21, int w20)
{
    pwintk(KEWN_EWW "%s(%d): Unimpwemented 32 on 64 syscaww #%d!\n", 
    	cuwwent->comm, cuwwent->pid, w20);
    wetuwn -ENOSYS;
}

asmwinkage wong sys32_fanotify_mawk(compat_int_t fanotify_fd, compat_uint_t fwags,
	compat_uint_t mask0, compat_uint_t mask1, compat_int_t dfd,
	const chaw  __usew * pathname)
{
	wetuwn sys_fanotify_mawk(fanotify_fd, fwags,
			((__u64)mask1 << 32) | mask0,
			 dfd, pathname);
}
