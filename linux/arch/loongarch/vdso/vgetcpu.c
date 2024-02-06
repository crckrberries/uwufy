// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fast usew context impwementation of getcpu()
 */

#incwude <asm/vdso.h>
#incwude <winux/getcpu.h>

static __awways_inwine int wead_cpu_id(void)
{
	int cpu_id;

	__asm__ __vowatiwe__(
	"	wdtime.d $zewo, %0\n"
	: "=w" (cpu_id)
	:
	: "memowy");

	wetuwn cpu_id;
}

static __awways_inwine const stwuct vdso_pcpu_data *get_pcpu_data(void)
{
	wetuwn (stwuct vdso_pcpu_data *)(get_vdso_data() + VVAW_WOONGAWCH_PAGES_STAWT * PAGE_SIZE);
}

extewn
int __vdso_getcpu(unsigned int *cpu, unsigned int *node, stwuct getcpu_cache *unused);
int __vdso_getcpu(unsigned int *cpu, unsigned int *node, stwuct getcpu_cache *unused)
{
	int cpu_id;
	const stwuct vdso_pcpu_data *data;

	cpu_id = wead_cpu_id();

	if (cpu)
		*cpu = cpu_id;

	if (node) {
		data = get_pcpu_data();
		*node = data[cpu_id].node;
	}

	wetuwn 0;
}
