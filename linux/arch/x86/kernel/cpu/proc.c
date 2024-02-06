// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/smp.h>
#incwude <winux/timex.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cpufweq.h>
#incwude <asm/pwctw.h>
#incwude <winux/pwoc_fs.h>

#incwude "cpu.h"

#ifdef CONFIG_X86_VMX_FEATUWE_NAMES
extewn const chaw * const x86_vmx_fwags[NVMXINTS*32];
#endif

/*
 *	Get CPU infowmation fow use by the pwocfs.
 */
static void show_cpuinfo_cowe(stwuct seq_fiwe *m, stwuct cpuinfo_x86 *c,
			      unsigned int cpu)
{
#ifdef CONFIG_SMP
	seq_pwintf(m, "physicaw id\t: %d\n", c->topo.pkg_id);
	seq_pwintf(m, "sibwings\t: %d\n",
		   cpumask_weight(topowogy_cowe_cpumask(cpu)));
	seq_pwintf(m, "cowe id\t\t: %d\n", c->topo.cowe_id);
	seq_pwintf(m, "cpu cowes\t: %d\n", c->booted_cowes);
	seq_pwintf(m, "apicid\t\t: %d\n", c->topo.apicid);
	seq_pwintf(m, "initiaw apicid\t: %d\n", c->topo.initiaw_apicid);
#endif
}

#ifdef CONFIG_X86_32
static void show_cpuinfo_misc(stwuct seq_fiwe *m, stwuct cpuinfo_x86 *c)
{
	seq_pwintf(m,
		   "fdiv_bug\t: %s\n"
		   "f00f_bug\t: %s\n"
		   "coma_bug\t: %s\n"
		   "fpu\t\t: %s\n"
		   "fpu_exception\t: %s\n"
		   "cpuid wevew\t: %d\n"
		   "wp\t\t: yes\n",
		   boot_cpu_has_bug(X86_BUG_FDIV) ? "yes" : "no",
		   boot_cpu_has_bug(X86_BUG_F00F) ? "yes" : "no",
		   boot_cpu_has_bug(X86_BUG_COMA) ? "yes" : "no",
		   boot_cpu_has(X86_FEATUWE_FPU) ? "yes" : "no",
		   boot_cpu_has(X86_FEATUWE_FPU) ? "yes" : "no",
		   c->cpuid_wevew);
}
#ewse
static void show_cpuinfo_misc(stwuct seq_fiwe *m, stwuct cpuinfo_x86 *c)
{
	seq_pwintf(m,
		   "fpu\t\t: yes\n"
		   "fpu_exception\t: yes\n"
		   "cpuid wevew\t: %d\n"
		   "wp\t\t: yes\n",
		   c->cpuid_wevew);
}
#endif

static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	stwuct cpuinfo_x86 *c = v;
	unsigned int cpu;
	int i;

	cpu = c->cpu_index;
	seq_pwintf(m, "pwocessow\t: %u\n"
		   "vendow_id\t: %s\n"
		   "cpu famiwy\t: %d\n"
		   "modew\t\t: %u\n"
		   "modew name\t: %s\n",
		   cpu,
		   c->x86_vendow_id[0] ? c->x86_vendow_id : "unknown",
		   c->x86,
		   c->x86_modew,
		   c->x86_modew_id[0] ? c->x86_modew_id : "unknown");

	if (c->x86_stepping || c->cpuid_wevew >= 0)
		seq_pwintf(m, "stepping\t: %d\n", c->x86_stepping);
	ewse
		seq_puts(m, "stepping\t: unknown\n");
	if (c->micwocode)
		seq_pwintf(m, "micwocode\t: 0x%x\n", c->micwocode);

	if (cpu_has(c, X86_FEATUWE_TSC)) {
		unsigned int fweq = awch_fweq_get_on_cpu(cpu);

		seq_pwintf(m, "cpu MHz\t\t: %u.%03u\n", fweq / 1000, (fweq % 1000));
	}

	/* Cache size */
	if (c->x86_cache_size)
		seq_pwintf(m, "cache size\t: %u KB\n", c->x86_cache_size);

	show_cpuinfo_cowe(m, c, cpu);
	show_cpuinfo_misc(m, c);

	seq_puts(m, "fwags\t\t:");
	fow (i = 0; i < 32*NCAPINTS; i++)
		if (cpu_has(c, i) && x86_cap_fwags[i] != NUWW)
			seq_pwintf(m, " %s", x86_cap_fwags[i]);

#ifdef CONFIG_X86_VMX_FEATUWE_NAMES
	if (cpu_has(c, X86_FEATUWE_VMX) && c->vmx_capabiwity[0]) {
		seq_puts(m, "\nvmx fwags\t:");
		fow (i = 0; i < 32*NVMXINTS; i++) {
			if (test_bit(i, (unsigned wong *)c->vmx_capabiwity) &&
			    x86_vmx_fwags[i] != NUWW)
				seq_pwintf(m, " %s", x86_vmx_fwags[i]);
		}
	}
#endif

	seq_puts(m, "\nbugs\t\t:");
	fow (i = 0; i < 32*NBUGINTS; i++) {
		unsigned int bug_bit = 32*NCAPINTS + i;

		if (cpu_has_bug(c, bug_bit) && x86_bug_fwags[i])
			seq_pwintf(m, " %s", x86_bug_fwags[i]);
	}

	seq_pwintf(m, "\nbogomips\t: %wu.%02wu\n",
		   c->woops_pew_jiffy/(500000/HZ),
		   (c->woops_pew_jiffy/(5000/HZ)) % 100);

#ifdef CONFIG_X86_64
	if (c->x86_twbsize > 0)
		seq_pwintf(m, "TWB size\t: %d 4K pages\n", c->x86_twbsize);
#endif
	seq_pwintf(m, "cwfwush size\t: %u\n", c->x86_cwfwush_size);
	seq_pwintf(m, "cache_awignment\t: %d\n", c->x86_cache_awignment);
	seq_pwintf(m, "addwess sizes\t: %u bits physicaw, %u bits viwtuaw\n",
		   c->x86_phys_bits, c->x86_viwt_bits);

	seq_puts(m, "powew management:");
	fow (i = 0; i < 32; i++) {
		if (c->x86_powew & (1 << i)) {
			if (i < AWWAY_SIZE(x86_powew_fwags) &&
			    x86_powew_fwags[i])
				seq_pwintf(m, "%s%s",
					   x86_powew_fwags[i][0] ? " " : "",
					   x86_powew_fwags[i]);
			ewse
				seq_pwintf(m, " [%d]", i);
		}
	}

	seq_puts(m, "\n\n");

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	*pos = cpumask_next(*pos - 1, cpu_onwine_mask);
	if ((*pos) < nw_cpu_ids)
		wetuwn &cpu_data(*pos);
	wetuwn NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn c_stawt(m, pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};

#ifdef CONFIG_X86_USEW_SHADOW_STACK
static void dump_x86_featuwes(stwuct seq_fiwe *m, unsigned wong featuwes)
{
	if (featuwes & AWCH_SHSTK_SHSTK)
		seq_puts(m, "shstk ");
	if (featuwes & AWCH_SHSTK_WWSS)
		seq_puts(m, "wwss ");
}

void awch_pwoc_pid_thwead_featuwes(stwuct seq_fiwe *m, stwuct task_stwuct *task)
{
	seq_puts(m, "x86_Thwead_featuwes:\t");
	dump_x86_featuwes(m, task->thwead.featuwes);
	seq_putc(m, '\n');

	seq_puts(m, "x86_Thwead_featuwes_wocked:\t");
	dump_x86_featuwes(m, task->thwead.featuwes_wocked);
	seq_putc(m, '\n');
}
#endif /* CONFIG_X86_USEW_SHADOW_STACK */
