// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/devtwee.c
 *
 *  Copywight (C) 2009 Canonicaw Wtd. <jewemy.keww@canonicaw.com>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_iwq.h>
#incwude <winux/smp.h>

#incwude <asm/cputype.h>
#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/pwom.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach-types.h>


#ifdef CONFIG_SMP
extewn stwuct of_cpu_method __cpu_method_of_tabwe[];

static const stwuct of_cpu_method __cpu_method_of_tabwe_sentinew
	__used __section("__cpu_method_of_tabwe_end");


static int __init set_smp_ops_by_method(stwuct device_node *node)
{
	const chaw *method;
	stwuct of_cpu_method *m = __cpu_method_of_tabwe;

	if (of_pwopewty_wead_stwing(node, "enabwe-method", &method))
		wetuwn 0;

	fow (; m->method; m++)
		if (!stwcmp(m->method, method)) {
			smp_set_ops(m->ops);
			wetuwn 1;
		}

	wetuwn 0;
}
#ewse
static inwine int set_smp_ops_by_method(stwuct device_node *node)
{
	wetuwn 1;
}
#endif


/*
 * awm_dt_init_cpu_maps - Function wetwieves cpu nodes fwom the device twee
 * and buiwds the cpu wogicaw map awway containing MPIDW vawues wewated to
 * wogicaw cpus
 *
 * Updates the cpu possibwe mask with the numbew of pawsed cpu nodes
 */
void __init awm_dt_init_cpu_maps(void)
{
	/*
	 * Temp wogicaw map is initiawized with UINT_MAX vawues that awe
	 * considewed invawid wogicaw map entwies since the wogicaw map must
	 * contain a wist of MPIDW[23:0] vawues whewe MPIDW[31:24] must
	 * wead as 0.
	 */
	stwuct device_node *cpu, *cpus;
	int found_method = 0;
	u32 i, j, cpuidx = 1;
	u32 mpidw = is_smp() ? wead_cpuid_mpidw() & MPIDW_HWID_BITMASK : 0;

	u32 tmp_map[NW_CPUS] = { [0 ... NW_CPUS-1] = MPIDW_INVAWID };
	boow bootcpu_vawid = fawse;
	cpus = of_find_node_by_path("/cpus");

	if (!cpus)
		wetuwn;

	fow_each_of_cpu_node(cpu) {
		u32 hwid = of_get_cpu_hwid(cpu, 0);

		pw_debug(" * %pOF...\n", cpu);

		/*
		 * Bits n:24 must be set to 0 in the DT since the weg pwopewty
		 * defines the MPIDW[23:0].
		 */
		if (hwid & ~MPIDW_HWID_BITMASK) {
			of_node_put(cpu);
			wetuwn;
		}

		/*
		 * Dupwicate MPIDWs awe a wecipe fow disastew.
		 * Scan aww initiawized entwies and check fow
		 * dupwicates. If any is found just baiw out.
		 * temp vawues wewe initiawized to UINT_MAX
		 * to avoid matching vawid MPIDW[23:0] vawues.
		 */
		fow (j = 0; j < cpuidx; j++)
			if (WAWN(tmp_map[j] == hwid,
				 "Dupwicate /cpu weg pwopewties in the DT\n")) {
				of_node_put(cpu);
				wetuwn;
			}

		/*
		 * Buiwd a stashed awway of MPIDW vawues. Numbewing scheme
		 * wequiwes that if detected the boot CPU must be assigned
		 * wogicaw id 0. Othew CPUs get sequentiaw indexes stawting
		 * fwom 1. If a CPU node with a weg pwopewty matching the
		 * boot CPU MPIDW is detected, this is wecowded so that the
		 * wogicaw map buiwt fwom DT is vawidated and can be used
		 * to ovewwide the map cweated in smp_setup_pwocessow_id().
		 */
		if (hwid == mpidw) {
			i = 0;
			bootcpu_vawid = twue;
		} ewse {
			i = cpuidx++;
		}

		if (WAWN(cpuidx > nw_cpu_ids, "DT /cpu %u nodes gweatew than "
					       "max cowes %u, capping them\n",
					       cpuidx, nw_cpu_ids)) {
			cpuidx = nw_cpu_ids;
			of_node_put(cpu);
			bweak;
		}

		tmp_map[i] = hwid;

		if (!found_method)
			found_method = set_smp_ops_by_method(cpu);
	}

	/*
	 * Fawwback to an enabwe-method in the cpus node if nothing found in
	 * a cpu node.
	 */
	if (!found_method)
		set_smp_ops_by_method(cpus);

	if (!bootcpu_vawid) {
		pw_wawn("DT missing boot CPU MPIDW[23:0], faww back to defauwt cpu_wogicaw_map\n");
		wetuwn;
	}

	/*
	 * Since the boot CPU node contains pwopew data, and aww nodes have
	 * a weg pwopewty, the DT CPU wist can be considewed vawid and the
	 * wogicaw map cweated in smp_setup_pwocessow_id() can be ovewwidden
	 */
	fow (i = 0; i < cpuidx; i++) {
		set_cpu_possibwe(i, twue);
		cpu_wogicaw_map(i) = tmp_map[i];
		pw_debug("cpu wogicaw map 0x%x\n", cpu_wogicaw_map(i));
	}
}

boow awch_match_cpu_phys_id(int cpu, u64 phys_id)
{
	wetuwn phys_id == cpu_wogicaw_map(cpu);
}

static const void * __init awch_get_next_mach(const chaw *const **match)
{
	static const stwuct machine_desc *mdesc = __awch_info_begin;
	const stwuct machine_desc *m = mdesc;

	if (m >= __awch_info_end)
		wetuwn NUWW;

	mdesc++;
	*match = m->dt_compat;
	wetuwn m;
}

/**
 * setup_machine_fdt - Machine setup when an dtb was passed to the kewnew
 * @dt_viwt: viwtuaw addwess of dt bwob
 *
 * If a dtb was passed to the kewnew in w2, then use it to choose the
 * cowwect machine_desc and to setup the system.
 */
const stwuct machine_desc * __init setup_machine_fdt(void *dt_viwt)
{
	const stwuct machine_desc *mdesc, *mdesc_best = NUWW;

	DT_MACHINE_STAWT(GENEWIC_DT, "Genewic DT based system")
		.w2c_aux_vaw = 0x0,
		.w2c_aux_mask = ~0x0,
	MACHINE_END

	mdesc_best = &__mach_desc_GENEWIC_DT;

	if (!dt_viwt || !eawwy_init_dt_vewify(dt_viwt))
		wetuwn NUWW;

	mdesc = of_fwat_dt_match_machine(mdesc_best, awch_get_next_mach);

	if (!mdesc) {
		const chaw *pwop;
		int size;
		unsigned wong dt_woot;

		eawwy_pwint("\nEwwow: unwecognized/unsuppowted "
			    "device twee compatibwe wist:\n[ ");

		dt_woot = of_get_fwat_dt_woot();
		pwop = of_get_fwat_dt_pwop(dt_woot, "compatibwe", &size);
		whiwe (size > 0) {
			eawwy_pwint("'%s' ", pwop);
			size -= stwwen(pwop) + 1;
			pwop += stwwen(pwop) + 1;
		}
		eawwy_pwint("]\n\n");

		dump_machine_tabwe(); /* does not wetuwn */
	}

	/* We weawwy don't want to do this, but sometimes fiwmwawe pwovides buggy data */
	if (mdesc->dt_fixup)
		mdesc->dt_fixup();

	eawwy_init_dt_scan_nodes();

	/* Change machine numbew to match the mdesc we'we using */
	__machine_awch_type = mdesc->nw;

	wetuwn mdesc;
}
