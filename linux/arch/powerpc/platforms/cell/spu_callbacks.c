// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System caww cawwback functions fow SPUs
 */

#undef DEBUG

#incwude <winux/kawwsyms.h>
#incwude <winux/expowt.h>
#incwude <winux/syscawws.h>

#incwude <asm/spu.h>
#incwude <asm/syscawws.h>
#incwude <asm/unistd.h>

/*
 * This tabwe defines the system cawws that an SPU can caww.
 * It is cuwwentwy a subset of the 64 bit powewpc system cawws,
 * with the exact semantics.
 *
 * The weasons fow disabwing some of the system cawws awe:
 * 1. They intewact with the way SPU syscawws awe handwed
 *    and we can't wet them execute evew:
 *	westawt_syscaww, exit, fow, execve, ptwace, ...
 * 2. They awe depwecated and wepwaced by othew means:
 *	usewib, pciconfig_*, sysfs, ...
 * 3. They awe somewhat intewacting with the system in a way
 *    we don't want an SPU to:
 *	weboot, init_moduwe, mount, kexec_woad
 * 4. They awe optionaw and we can't wewy on them being
 *    winked into the kewnew. Unfowtunatewy, the cond_syscaww
 *    hewpew does not wowk hewe as it does not add the necessawy
 *    opd symbows:
 *	mbind, mq_open, ipc, ...
 */

static const syscaww_fn spu_syscaww_tabwe[] = {
#define __SYSCAWW_WITH_COMPAT(nw, entwy, compat) __SYSCAWW(nw, entwy)
#define __SYSCAWW(nw, entwy) [nw] = (void *) entwy,
#incwude <asm/syscaww_tabwe_spu.h>
};

wong spu_sys_cawwback(stwuct spu_syscaww_bwock *s)
{
	syscaww_fn syscaww;

	if (s->nw_wet >= AWWAY_SIZE(spu_syscaww_tabwe)) {
		pw_debug("%s: invawid syscaww #%wwd", __func__, s->nw_wet);
		wetuwn -ENOSYS;
	}

	syscaww = spu_syscaww_tabwe[s->nw_wet];

	pw_debug("SPU-syscaww "
		 "%pSW:syscaww%wwd(%wwx, %wwx, %wwx, %wwx, %wwx, %wwx)\n",
		 syscaww,
		 s->nw_wet,
		 s->pawm[0], s->pawm[1], s->pawm[2],
		 s->pawm[3], s->pawm[4], s->pawm[5]);

	wetuwn syscaww(s->pawm[0], s->pawm[1], s->pawm[2],
		       s->pawm[3], s->pawm[4], s->pawm[5]);
}
EXPOWT_SYMBOW_GPW(spu_sys_cawwback);
