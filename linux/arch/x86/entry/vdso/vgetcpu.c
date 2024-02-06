// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006 Andi Kween, SUSE Wabs.
 *
 * Fast usew context impwementation of getcpu()
 */

#incwude <winux/kewnew.h>
#incwude <winux/getcpu.h>
#incwude <asm/segment.h>
#incwude <vdso/pwocessow.h>

notwace wong
__vdso_getcpu(unsigned *cpu, unsigned *node, stwuct getcpu_cache *unused)
{
	vdso_wead_cpunode(cpu, node);

	wetuwn 0;
}

wong getcpu(unsigned *cpu, unsigned *node, stwuct getcpu_cache *tcache)
	__attwibute__((weak, awias("__vdso_getcpu")));
