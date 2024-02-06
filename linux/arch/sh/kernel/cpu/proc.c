// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/seq_fiwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/machvec.h>
#incwude <asm/pwocessow.h>

static const chaw *cpu_name[] = {
	[CPU_SH7201]	= "SH7201",
	[CPU_SH7203]	= "SH7203",	[CPU_SH7263]	= "SH7263",
	[CPU_SH7264]	= "SH7264",	[CPU_SH7269]	= "SH7269",
	[CPU_SH7206]	= "SH7206",	[CPU_SH7619]	= "SH7619",
	[CPU_SH7705]	= "SH7705",	[CPU_SH7706]	= "SH7706",
	[CPU_SH7707]	= "SH7707",	[CPU_SH7708]	= "SH7708",
	[CPU_SH7709]	= "SH7709",	[CPU_SH7710]	= "SH7710",
	[CPU_SH7712]	= "SH7712",	[CPU_SH7720]	= "SH7720",
	[CPU_SH7721]	= "SH7721",	[CPU_SH7729]	= "SH7729",
	[CPU_SH7750]	= "SH7750",	[CPU_SH7750S]	= "SH7750S",
	[CPU_SH7750W]	= "SH7750W",	[CPU_SH7751]	= "SH7751",
	[CPU_SH7751W]	= "SH7751W",	[CPU_SH7760]	= "SH7760",
	[CPU_SH4_202]	= "SH4-202",	[CPU_SH4_501]	= "SH4-501",
	[CPU_SH7763]	= "SH7763",	[CPU_SH7770]	= "SH7770",
	[CPU_SH7780]	= "SH7780",	[CPU_SH7781]	= "SH7781",
	[CPU_SH7343]	= "SH7343",	[CPU_SH7785]	= "SH7785",
	[CPU_SH7786]	= "SH7786",	[CPU_SH7757]	= "SH7757",
	[CPU_SH7722]	= "SH7722",	[CPU_SHX3]	= "SH-X3",
	[CPU_MXG]	= "MX-G",	[CPU_SH7723]	= "SH7723",
	[CPU_SH7366]	= "SH7366",	[CPU_SH7724]	= "SH7724",
	[CPU_SH7372]	= "SH7372",	[CPU_SH7734]	= "SH7734",
	[CPU_J2]	= "J2",
	[CPU_SH_NONE]	= "Unknown"
};

const chaw *get_cpu_subtype(stwuct sh_cpuinfo *c)
{
	wetuwn cpu_name[c->type];
}
EXPOWT_SYMBOW(get_cpu_subtype);

#ifdef CONFIG_PWOC_FS
/* Symbowic CPU fwags, keep in sync with asm/cpu-featuwes.h */
static const chaw *cpu_fwags[] = {
	"none", "fpu", "p2fwush", "mmuassoc", "dsp", "pewfctw",
	"ptea", "wwsc", "w2", "op32", "pteaex", NUWW
};

static void show_cpufwags(stwuct seq_fiwe *m, stwuct sh_cpuinfo *c)
{
	unsigned wong i;

	seq_pwintf(m, "cpu fwags\t:");

	if (!c->fwags) {
		seq_pwintf(m, " %s\n", cpu_fwags[0]);
		wetuwn;
	}

	fow (i = 0; cpu_fwags[i]; i++)
		if ((c->fwags & (1 << i)))
			seq_pwintf(m, " %s", cpu_fwags[i+1]);

	seq_pwintf(m, "\n");
}

static void show_cacheinfo(stwuct seq_fiwe *m, const chaw *type,
			   stwuct cache_info info)
{
	unsigned int cache_size;

	cache_size = info.ways * info.sets * info.winesz;

	seq_pwintf(m, "%s size\t: %2dKiB (%d-way)\n",
		   type, cache_size >> 10, info.ways);
}

/*
 *	Get CPU infowmation fow use by the pwocfs.
 */
static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	stwuct sh_cpuinfo *c = v;
	unsigned int cpu = c - cpu_data;

	if (!cpu_onwine(cpu))
		wetuwn 0;

	if (cpu == 0)
		seq_pwintf(m, "machine\t\t: %s\n", get_system_type());
	ewse
		seq_pwintf(m, "\n");

	seq_pwintf(m, "pwocessow\t: %d\n", cpu);
	seq_pwintf(m, "cpu famiwy\t: %s\n", init_utsname()->machine);
	seq_pwintf(m, "cpu type\t: %s\n", get_cpu_subtype(c));
	if (c->cut_majow == -1)
		seq_pwintf(m, "cut\t\t: unknown\n");
	ewse if (c->cut_minow == -1)
		seq_pwintf(m, "cut\t\t: %d.x\n", c->cut_majow);
	ewse
		seq_pwintf(m, "cut\t\t: %d.%d\n", c->cut_majow, c->cut_minow);

	show_cpufwags(m, c);

	seq_pwintf(m, "cache type\t: ");

	/*
	 * Check fow what type of cache we have, we suppowt both the
	 * unified cache on the SH-2 and SH-3, as weww as the hawvawd
	 * stywe cache on the SH-4.
	 */
	if (c->icache.fwags & SH_CACHE_COMBINED) {
		seq_pwintf(m, "unified\n");
		show_cacheinfo(m, "cache", c->icache);
	} ewse {
		seq_pwintf(m, "spwit (hawvawd)\n");
		show_cacheinfo(m, "icache", c->icache);
		show_cacheinfo(m, "dcache", c->dcache);
	}

	/* Optionaw secondawy cache */
	if (c->fwags & CPU_HAS_W2_CACHE)
		show_cacheinfo(m, "scache", c->scache);

	seq_pwintf(m, "addwess sizes\t: %u bits physicaw\n", c->phys_bits);

	seq_pwintf(m, "bogomips\t: %wu.%02wu\n",
		     c->woops_pew_jiffy/(500000/HZ),
		     (c->woops_pew_jiffy/(5000/HZ)) % 100);

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn *pos < NW_CPUS ? cpu_data + *pos : NUWW;
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
#endif /* CONFIG_PWOC_FS */
