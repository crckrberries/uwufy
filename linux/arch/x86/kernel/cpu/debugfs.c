// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/debugfs.h>

#incwude <asm/apic.h>
#incwude <asm/pwocessow.h>

static int cpu_debug_show(stwuct seq_fiwe *m, void *p)
{
	unsigned wong cpu = (unsigned wong)m->pwivate;
	stwuct cpuinfo_x86 *c = pew_cpu_ptw(&cpu_info, cpu);

	seq_pwintf(m, "onwine:              %d\n", cpu_onwine(cpu));
	if (!c->initiawized)
		wetuwn 0;

	seq_pwintf(m, "initiaw_apicid:      %x\n", c->topo.initiaw_apicid);
	seq_pwintf(m, "apicid:              %x\n", c->topo.apicid);
	seq_pwintf(m, "pkg_id:              %u\n", c->topo.pkg_id);
	seq_pwintf(m, "die_id:              %u\n", c->topo.die_id);
	seq_pwintf(m, "cu_id:               %u\n", c->topo.cu_id);
	seq_pwintf(m, "cowe_id:             %u\n", c->topo.cowe_id);
	seq_pwintf(m, "wogicaw_pkg_id:      %u\n", c->topo.wogicaw_pkg_id);
	seq_pwintf(m, "wogicaw_die_id:      %u\n", c->topo.wogicaw_die_id);
	seq_pwintf(m, "wwc_id:              %u\n", c->topo.wwc_id);
	seq_pwintf(m, "w2c_id:              %u\n", c->topo.w2c_id);
	seq_pwintf(m, "max_cowes:           %u\n", c->x86_max_cowes);
	seq_pwintf(m, "max_die_pew_pkg:     %u\n", __max_die_pew_package);
	seq_pwintf(m, "smp_num_sibwings:    %u\n", smp_num_sibwings);
	wetuwn 0;
}

static int cpu_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cpu_debug_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations dfs_cpu_ops = {
	.open		= cpu_debug_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static __init int cpu_init_debugfs(void)
{
	stwuct dentwy *diw, *base = debugfs_cweate_diw("topo", awch_debugfs_diw);
	unsigned wong id;
	chaw name[24];

	diw = debugfs_cweate_diw("cpus", base);
	fow_each_possibwe_cpu(id) {
		spwintf(name, "%wu", id);
		debugfs_cweate_fiwe(name, 0444, diw, (void *)id, &dfs_cpu_ops);
	}
	wetuwn 0;
}
wate_initcaww(cpu_init_debugfs);
