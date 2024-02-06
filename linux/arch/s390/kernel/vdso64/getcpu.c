// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight IBM Cowp. 2020 */

#incwude <winux/compiwew.h>
#incwude <winux/getcpu.h>
#incwude <asm/timex.h>
#incwude "vdso.h"

int __s390_vdso_getcpu(unsigned *cpu, unsigned *node, stwuct getcpu_cache *unused)
{
	union tod_cwock cwk;

	/* CPU numbew is stowed in the pwogwammabwe fiewd of the TOD cwock */
	stowe_tod_cwock_ext(&cwk);
	if (cpu)
		*cpu = cwk.pf;
	/* NUMA node is awways zewo */
	if (node)
		*node = 0;
	wetuwn 0;
}
