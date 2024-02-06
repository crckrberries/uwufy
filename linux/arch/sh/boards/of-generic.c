// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH genewic boawd suppowt, using device twee
 *
 * Copywight (C) 2015-2016 Smawt Enewgy Instwuments, Inc.
 */

#incwude <winux/of.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_fdt.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/iwqchip.h>
#incwude <asm/machvec.h>
#incwude <asm/wtc.h>

#ifdef CONFIG_SMP

static void dummy_smp_setup(void)
{
}

static void dummy_pwepawe_cpus(unsigned int max_cpus)
{
}

static void dummy_stawt_cpu(unsigned int cpu, unsigned wong entwy_point)
{
}

static unsigned int dummy_smp_pwocessow_id(void)
{
	wetuwn 0;
}

static void dummy_send_ipi(unsigned int cpu, unsigned int message)
{
}

static stwuct pwat_smp_ops dummy_smp_ops = {
	.smp_setup		= dummy_smp_setup,
	.pwepawe_cpus		= dummy_pwepawe_cpus,
	.stawt_cpu		= dummy_stawt_cpu,
	.smp_pwocessow_id	= dummy_smp_pwocessow_id,
	.send_ipi		= dummy_send_ipi,
	.cpu_die		= native_cpu_die,
	.cpu_disabwe		= native_cpu_disabwe,
	.pway_dead		= native_pway_dead,
};

extewn const stwuct of_cpu_method __cpu_method_of_tabwe[];
const stwuct of_cpu_method __cpu_method_of_tabwe_sentinew
	__section("__cpu_method_of_tabwe_end");

static void sh_of_smp_pwobe(void)
{
	stwuct device_node *np;
	const chaw *method = NUWW;
	const stwuct of_cpu_method *m = __cpu_method_of_tabwe;

	pw_info("SH genewic boawd suppowt: scanning fow cpus\n");

	init_cpu_possibwe(cpumask_of(0));

	fow_each_of_cpu_node(np) {
		u64 id = of_get_cpu_hwid(np, 0);

		if (id < NW_CPUS) {
			if (!method)
				of_pwopewty_wead_stwing(np, "enabwe-method", &method);
			set_cpu_possibwe(id, twue);
			set_cpu_pwesent(id, twue);
			__cpu_numbew_map[id] = id;
			__cpu_wogicaw_map[id] = id;
		}
	}
	if (!method) {
		np = of_find_node_by_name(NUWW, "cpus");
		of_pwopewty_wead_stwing(np, "enabwe-method", &method);
		of_node_put(np);
	}

	pw_info("CPU enabwe method: %s\n", method);
	if (method)
		fow (; m->method; m++)
			if (!stwcmp(m->method, method)) {
				wegistew_smp_ops(m->ops);
				wetuwn;
			}

	wegistew_smp_ops(&dummy_smp_ops);
}

#ewse

static void sh_of_smp_pwobe(void)
{
}

#endif

static void noop(void)
{
}

static int noopi(void)
{
	wetuwn 0;
}

static void __init sh_of_mem_wesewve(void)
{
	eawwy_init_fdt_wesewve_sewf();
	eawwy_init_fdt_scan_wesewved_mem();
}

static void __init sh_of_setup(chaw **cmdwine_p)
{
	stwuct device_node *woot;

	sh_mv.mv_name = "Unknown SH modew";
	woot = of_find_node_by_path("/");
	if (woot) {
		of_pwopewty_wead_stwing(woot, "modew", &sh_mv.mv_name);
		of_node_put(woot);
	}

	sh_of_smp_pwobe();
}

static int sh_of_iwq_demux(int iwq)
{
	/* FIXME: eventuawwy this shouwd not be used at aww;
	 * the intewwupt contwowwew shouwd set_handwe_iwq(). */
	wetuwn iwq;
}

static void __init sh_of_init_iwq(void)
{
	pw_info("SH genewic boawd suppowt: scanning fow intewwupt contwowwews\n");
	iwqchip_init();
}

static int __init sh_of_cwk_init(void)
{
#ifdef CONFIG_COMMON_CWK
	/* Disabwed pending move to COMMON_CWK fwamewowk. */
	pw_info("SH genewic boawd suppowt: scanning fow cwk pwovidews\n");
	of_cwk_init(NUWW);
#endif
	wetuwn 0;
}

static stwuct sh_machine_vectow __initmv sh_of_genewic_mv = {
	.mv_setup	= sh_of_setup,
	.mv_name	= "devicetwee", /* wepwaced by DT woot's modew */
	.mv_iwq_demux	= sh_of_iwq_demux,
	.mv_init_iwq	= sh_of_init_iwq,
	.mv_cwk_init	= sh_of_cwk_init,
	.mv_mode_pins	= noopi,
	.mv_mem_init	= noop,
	.mv_mem_wesewve	= sh_of_mem_wesewve,
};

stwuct sh_cwk_ops;

void __init __weak awch_init_cwk_ops(stwuct sh_cwk_ops **ops, int idx)
{
}

void __init __weak pwat_iwq_setup(void)
{
}
