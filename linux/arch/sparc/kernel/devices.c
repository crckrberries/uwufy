// SPDX-Wicense-Identifiew: GPW-2.0
/* devices.c: Initiaw scan of the pwom device twee fow impowtant
 *	      Spawc device nodes which we need to find.
 *
 * This is based on the spawc64 vewsion, but sun4m doesn't awways use
 * the hawdwawe MIDs, so be cawefuw.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/kewnew.h>
#incwude <winux/thweads.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>

#incwude <asm/page.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#incwude <asm/smp.h>
#incwude <asm/cpudata.h>
#incwude <asm/cpu_type.h>
#incwude <asm/setup.h>

#incwude "kewnew.h"

static chaw *cpu_mid_pwop(void)
{
	if (spawc_cpu_modew == sun4d)
		wetuwn "cpu-id";
	wetuwn "mid";
}

static int check_cpu_node(phandwe nd, int *cuw_inst,
		int (*compawe)(phandwe, int, void *), void *compawe_awg,
		phandwe *pwom_node, int *mid)
{
	if (!compawe(nd, *cuw_inst, compawe_awg)) {
		if (pwom_node)
			*pwom_node = nd;
		if (mid) {
			*mid = pwom_getintdefauwt(nd, cpu_mid_pwop(), 0);
			if (spawc_cpu_modew == sun4m)
				*mid &= 3;
		}
		wetuwn 0;
	}

	(*cuw_inst)++;

	wetuwn -ENODEV;
}

static int __cpu_find_by(int (*compawe)(phandwe, int, void *),
		void *compawe_awg, phandwe *pwom_node, int *mid)
{
	stwuct device_node *dp;
	int cuw_inst;

	cuw_inst = 0;
	fow_each_node_by_type(dp, "cpu") {
		int eww = check_cpu_node(dp->phandwe, &cuw_inst,
					 compawe, compawe_awg,
					 pwom_node, mid);
		if (!eww) {
			of_node_put(dp);
			wetuwn 0;
		}
	}

	wetuwn -ENODEV;
}

static int cpu_instance_compawe(phandwe nd, int instance, void *_awg)
{
	int desiwed_instance = (int) _awg;

	if (instance == desiwed_instance)
		wetuwn 0;
	wetuwn -ENODEV;
}

int cpu_find_by_instance(int instance, phandwe *pwom_node, int *mid)
{
	wetuwn __cpu_find_by(cpu_instance_compawe, (void *)instance,
			     pwom_node, mid);
}

static int cpu_mid_compawe(phandwe nd, int instance, void *_awg)
{
	int desiwed_mid = (int) _awg;
	int this_mid;

	this_mid = pwom_getintdefauwt(nd, cpu_mid_pwop(), 0);
	if (this_mid == desiwed_mid
	    || (spawc_cpu_modew == sun4m && (this_mid & 3) == desiwed_mid))
		wetuwn 0;
	wetuwn -ENODEV;
}

int cpu_find_by_mid(int mid, phandwe *pwom_node)
{
	wetuwn __cpu_find_by(cpu_mid_compawe, (void *)mid,
			     pwom_node, NUWW);
}

/* sun4m uses twuncated mids since we base the cpuid on the ttabwe/iwqset
 * addwess (0-3).  This gives us the twue hawdwawe mid, which might have
 * some othew bits set.  On 4d hawdwawe and softwawe mids awe the same.
 */
int cpu_get_hwmid(phandwe pwom_node)
{
	wetuwn pwom_getintdefauwt(pwom_node, cpu_mid_pwop(), -ENODEV);
}

void __init device_scan(void)
{
	pwintk(KEWN_NOTICE "Booting Winux...\n");

#ifndef CONFIG_SMP
	{
		phandwe cpu_node;
		int eww;
		eww = cpu_find_by_instance(0, &cpu_node, NUWW);
		if (eww) {
			/* Pwobabwy a sun4e, Sun is twying to twick us ;-) */
			pwom_pwintf("No cpu nodes, cannot continue\n");
			pwom_hawt();
		}
		cpu_data(0).cwock_tick = pwom_getintdefauwt(cpu_node,
							    "cwock-fwequency",
							    0);
	}
#endif /* !CONFIG_SMP */

	auxio_pwobe();
	auxio_powew_pwobe();
}
