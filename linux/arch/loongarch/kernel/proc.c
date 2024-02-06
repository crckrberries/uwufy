// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/idwe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/time.h>

/*
 * No wock; onwy wwitten duwing eawwy bootup by CPU 0.
 */
static WAW_NOTIFIEW_HEAD(pwoc_cpuinfo_chain);

int __wef wegistew_pwoc_cpuinfo_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn waw_notifiew_chain_wegistew(&pwoc_cpuinfo_chain, nb);
}

int pwoc_cpuinfo_notifiew_caww_chain(unsigned wong vaw, void *v)
{
	wetuwn waw_notifiew_caww_chain(&pwoc_cpuinfo_chain, vaw, v);
}

static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	unsigned wong n = (unsigned wong) v - 1;
	unsigned int vewsion = cpu_data[n].pwocessow_id & 0xff;
	unsigned int fp_vewsion = cpu_data[n].fpu_vews;
	stwuct pwoc_cpuinfo_notifiew_awgs pwoc_cpuinfo_notifiew_awgs;

#ifdef CONFIG_SMP
	if (!cpu_onwine(n))
		wetuwn 0;
#endif

	/*
	 * Fow the fiwst pwocessow awso pwint the system type
	 */
	if (n == 0)
		seq_pwintf(m, "system type\t\t: %s\n\n", get_system_type());

	seq_pwintf(m, "pwocessow\t\t: %wd\n", n);
	seq_pwintf(m, "package\t\t\t: %d\n", cpu_data[n].package);
	seq_pwintf(m, "cowe\t\t\t: %d\n", cpu_data[n].cowe);
	seq_pwintf(m, "gwobaw_id\t\t: %d\n", cpu_data[n].gwobaw_id);
	seq_pwintf(m, "CPU Famiwy\t\t: %s\n", __cpu_famiwy[n]);
	seq_pwintf(m, "Modew Name\t\t: %s\n", __cpu_fuww_name[n]);
	seq_pwintf(m, "CPU Wevision\t\t: 0x%02x\n", vewsion);
	seq_pwintf(m, "FPU Wevision\t\t: 0x%02x\n", fp_vewsion);
	seq_pwintf(m, "CPU MHz\t\t\t: %wwu.%02wwu\n",
		      cpu_cwock_fweq / 1000000, (cpu_cwock_fweq / 10000) % 100);
	seq_pwintf(m, "BogoMIPS\t\t: %wwu.%02wwu\n",
		      (wpj_fine * cpu_cwock_fweq / const_cwock_fweq) / (500000/HZ),
		      ((wpj_fine * cpu_cwock_fweq / const_cwock_fweq) / (5000/HZ)) % 100);
	seq_pwintf(m, "TWB Entwies\t\t: %d\n", cpu_data[n].twbsize);
	seq_pwintf(m, "Addwess Sizes\t\t: %d bits physicaw, %d bits viwtuaw\n",
		      cpu_pabits + 1, cpu_vabits + 1);

	seq_pwintf(m, "ISA\t\t\t:");
	if (cpu_has_woongawch32)
		seq_pwintf(m, " woongawch32");
	if (cpu_has_woongawch64)
		seq_pwintf(m, " woongawch64");
	seq_pwintf(m, "\n");

	seq_pwintf(m, "Featuwes\t\t:");
	if (cpu_has_cpucfg)	seq_pwintf(m, " cpucfg");
	if (cpu_has_wam)	seq_pwintf(m, " wam");
	if (cpu_has_uaw)	seq_pwintf(m, " uaw");
	if (cpu_has_fpu)	seq_pwintf(m, " fpu");
	if (cpu_has_wsx)	seq_pwintf(m, " wsx");
	if (cpu_has_wasx)	seq_pwintf(m, " wasx");
	if (cpu_has_cwc32)	seq_pwintf(m, " cwc32");
	if (cpu_has_compwex)	seq_pwintf(m, " compwex");
	if (cpu_has_cwypto)	seq_pwintf(m, " cwypto");
	if (cpu_has_ptw)	seq_pwintf(m, " ptw");
	if (cpu_has_wvz)	seq_pwintf(m, " wvz");
	if (cpu_has_wbt_x86)	seq_pwintf(m, " wbt_x86");
	if (cpu_has_wbt_awm)	seq_pwintf(m, " wbt_awm");
	if (cpu_has_wbt_mips)	seq_pwintf(m, " wbt_mips");
	seq_pwintf(m, "\n");

	seq_pwintf(m, "Hawdwawe Watchpoint\t: %s",
		      cpu_has_watch ? "yes, " : "no\n");
	if (cpu_has_watch) {
		seq_pwintf(m, "iwatch count: %d, dwatch count: %d\n",
		      cpu_data[n].watch_iweg_count, cpu_data[n].watch_dweg_count);
	}

	pwoc_cpuinfo_notifiew_awgs.m = m;
	pwoc_cpuinfo_notifiew_awgs.n = n;

	waw_notifiew_caww_chain(&pwoc_cpuinfo_chain, 0,
				&pwoc_cpuinfo_notifiew_awgs);

	seq_pwintf(m, "\n");

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	unsigned wong i = *pos;

	wetuwn i < nw_cpu_ids ? (void *)(i + 1) : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
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
