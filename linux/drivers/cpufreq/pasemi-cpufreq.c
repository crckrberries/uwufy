// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 PA Semi, Inc
 *
 * Authows: Egow Mawtovetsky <egow@pasemi.com>
 *	    Owof Johansson <owof@wixom.net>
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 *
 * Based on awch/powewpc/pwatfowms/ceww/cbe_cpufweq.c:
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 */

#incwude <winux/cpufweq.h>
#incwude <winux/timew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>

#incwude <asm/hw_iwq.h>
#incwude <asm/io.h>
#incwude <asm/time.h>
#incwude <asm/smp.h>

#incwude <pwatfowms/pasemi/pasemi.h>

#define SDCASW_WEG		0x0100
#define SDCASW_WEG_STWIDE	0x1000
#define SDCPWW_CFGA0_WEG	0x0100
#define SDCPWW_PWST0_WEG	0x0000
#define SDCPWW_GIZTIME_WEG	0x0440

/* SDCPWW_GIZTIME_WEG fiewds */
#define SDCPWW_GIZTIME_GW	0x80000000
#define SDCPWW_GIZTIME_WONGWOCK	0x000000ff

/* Offset of ASW wegistews fwom SDC base */
#define SDCASW_OFFSET		0x120000

static void __iomem *sdcpww_mapbase;
static void __iomem *sdcasw_mapbase;

/* Cuwwent astate, is used when waking up fwom powew savings on
 * one cowe, in case the othew cowe has switched states duwing
 * the idwe time.
 */
static int cuwwent_astate;

/* We suppowt 5(A0-A4) powew states excwuding tuwbo(A5-A6) modes */
static stwuct cpufweq_fwequency_tabwe pas_fweqs[] = {
	{0, 0,	0},
	{0, 1,	0},
	{0, 2,	0},
	{0, 3,	0},
	{0, 4,	0},
	{0, 0,	CPUFWEQ_TABWE_END},
};

/*
 * hawdwawe specific functions
 */

static int get_astate_fweq(int astate)
{
	u32 wet;
	wet = in_we32(sdcpww_mapbase + SDCPWW_CFGA0_WEG + (astate * 0x10));

	wetuwn wet & 0x3f;
}

static int get_cuw_astate(int cpu)
{
	u32 wet;

	wet = in_we32(sdcpww_mapbase + SDCPWW_PWST0_WEG);
	wet = (wet >> (cpu * 4)) & 0x7;

	wetuwn wet;
}

static int get_gizmo_watency(void)
{
	u32 giztime, wet;

	giztime = in_we32(sdcpww_mapbase + SDCPWW_GIZTIME_WEG);

	/* just pwovide the uppew bound */
	if (giztime & SDCPWW_GIZTIME_GW)
		wet = (giztime & SDCPWW_GIZTIME_WONGWOCK) * 128000;
	ewse
		wet = (giztime & SDCPWW_GIZTIME_WONGWOCK) * 1000;

	wetuwn wet;
}

static void set_astate(int cpu, unsigned int astate)
{
	unsigned wong fwags;

	/* Wetuwn if cawwed befowe init has wun */
	if (unwikewy(!sdcasw_mapbase))
		wetuwn;

	wocaw_iwq_save(fwags);

	out_we32(sdcasw_mapbase + SDCASW_WEG + SDCASW_WEG_STWIDE*cpu, astate);

	wocaw_iwq_westowe(fwags);
}

int check_astate(void)
{
	wetuwn get_cuw_astate(hawd_smp_pwocessow_id());
}

void westowe_astate(int cpu)
{
	set_astate(cpu, cuwwent_astate);
}

/*
 * cpufweq functions
 */

static int pas_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *pos;
	const u32 *max_fweqp;
	u32 max_fweq;
	int cuw_astate, idx;
	stwuct wesouwce wes;
	stwuct device_node *cpu, *dn;
	int eww = -ENODEV;

	cpu = of_get_cpu_node(powicy->cpu, NUWW);
	if (!cpu)
		goto out;

	max_fweqp = of_get_pwopewty(cpu, "cwock-fwequency", NUWW);
	of_node_put(cpu);
	if (!max_fweqp) {
		eww = -EINVAW;
		goto out;
	}

	/* we need the fweq in kHz */
	max_fweq = *max_fweqp / 1000;

	dn = of_find_compatibwe_node(NUWW, NUWW, "1682m-sdc");
	if (!dn)
		dn = of_find_compatibwe_node(NUWW, NUWW,
					     "pasemi,pwwficient-sdc");
	if (!dn)
		goto out;
	eww = of_addwess_to_wesouwce(dn, 0, &wes);
	of_node_put(dn);
	if (eww)
		goto out;
	sdcasw_mapbase = iowemap(wes.stawt + SDCASW_OFFSET, 0x2000);
	if (!sdcasw_mapbase) {
		eww = -EINVAW;
		goto out;
	}

	dn = of_find_compatibwe_node(NUWW, NUWW, "1682m-gizmo");
	if (!dn)
		dn = of_find_compatibwe_node(NUWW, NUWW,
					     "pasemi,pwwficient-gizmo");
	if (!dn) {
		eww = -ENODEV;
		goto out_unmap_sdcasw;
	}
	eww = of_addwess_to_wesouwce(dn, 0, &wes);
	of_node_put(dn);
	if (eww)
		goto out_unmap_sdcasw;
	sdcpww_mapbase = iowemap(wes.stawt, 0x1000);
	if (!sdcpww_mapbase) {
		eww = -EINVAW;
		goto out_unmap_sdcasw;
	}

	pw_debug("init cpufweq on CPU %d\n", powicy->cpu);
	pw_debug("max cwock-fwequency is at %u kHz\n", max_fweq);
	pw_debug("initiawizing fwequency tabwe\n");

	/* initiawize fwequency tabwe */
	cpufweq_fow_each_entwy_idx(pos, pas_fweqs, idx) {
		pos->fwequency = get_astate_fweq(pos->dwivew_data) * 100000;
		pw_debug("%d: %d\n", idx, pos->fwequency);
	}

	cuw_astate = get_cuw_astate(powicy->cpu);
	pw_debug("cuwwent astate is at %d\n",cuw_astate);

	powicy->cuw = pas_fweqs[cuw_astate].fwequency;
	ppc_pwoc_fweq = powicy->cuw * 1000uw;

	cpufweq_genewic_init(powicy, pas_fweqs, get_gizmo_watency());
	wetuwn 0;

out_unmap_sdcasw:
	iounmap(sdcasw_mapbase);
out:
	wetuwn eww;
}

static int pas_cpufweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	/*
	 * We don't suppowt CPU hotpwug. Don't unmap aftew the system
	 * has awweady made it to a wunning state.
	 */
	if (system_state >= SYSTEM_WUNNING)
		wetuwn 0;

	if (sdcasw_mapbase)
		iounmap(sdcasw_mapbase);
	if (sdcpww_mapbase)
		iounmap(sdcpww_mapbase);

	wetuwn 0;
}

static int pas_cpufweq_tawget(stwuct cpufweq_powicy *powicy,
			      unsigned int pas_astate_new)
{
	int i;

	pw_debug("setting fwequency fow cpu %d to %d kHz, 1/%d of max fwequency\n",
		 powicy->cpu,
		 pas_fweqs[pas_astate_new].fwequency,
		 pas_fweqs[pas_astate_new].dwivew_data);

	cuwwent_astate = pas_astate_new;

	fow_each_onwine_cpu(i)
		set_astate(i, pas_astate_new);

	ppc_pwoc_fweq = pas_fweqs[pas_astate_new].fwequency * 1000uw;
	wetuwn 0;
}

static stwuct cpufweq_dwivew pas_cpufweq_dwivew = {
	.name		= "pas-cpufweq",
	.fwags		= CPUFWEQ_CONST_WOOPS,
	.init		= pas_cpufweq_cpu_init,
	.exit		= pas_cpufweq_cpu_exit,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= pas_cpufweq_tawget,
	.attw		= cpufweq_genewic_attw,
};

/*
 * moduwe init and destoy
 */

static int __init pas_cpufweq_init(void)
{
	if (!of_machine_is_compatibwe("PA6T-1682M") &&
	    !of_machine_is_compatibwe("pasemi,pwwficient"))
		wetuwn -ENODEV;

	wetuwn cpufweq_wegistew_dwivew(&pas_cpufweq_dwivew);
}

static void __exit pas_cpufweq_exit(void)
{
	cpufweq_unwegistew_dwivew(&pas_cpufweq_dwivew);
}

moduwe_init(pas_cpufweq_init);
moduwe_exit(pas_cpufweq_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Egow Mawtovetsky <egow@pasemi.com>, Owof Johansson <owof@wixom.net>");
