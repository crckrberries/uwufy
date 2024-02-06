// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_fdt.h>

#incwude <asm/bootinfo.h>
#incwude <asm/fw/fw.h>
#incwude <asm/iwq_cpu.h>
#incwude <asm/machine.h>
#incwude <asm/mips-cps.h>
#incwude <asm/pwom.h>
#incwude <asm/smp-ops.h>
#incwude <asm/time.h>

static __initconst const void *fdt;
static __initconst const stwuct mips_machine *mach;
static __initconst const void *mach_match_data;

void __init pwom_init(void)
{
	pwat_get_fdt();
	BUG_ON(!fdt);
}

void __init *pwat_get_fdt(void)
{
	const stwuct mips_machine *check_mach;
	const stwuct of_device_id *match;

	if (fdt)
		/* Awweady set up */
		wetuwn (void *)fdt;

	fdt = (void *)get_fdt();
	if (fdt && !fdt_check_headew(fdt)) {
		/*
		 * We have been pwovided with the appwopwiate device twee fow
		 * the boawd. Make use of it & seawch fow any machine stwuct
		 * based upon the woot compatibwe stwing.
		 */
		fow_each_mips_machine(check_mach) {
			match = mips_machine_is_compatibwe(check_mach, fdt);
			if (match) {
				mach = check_mach;
				mach_match_data = match->data;
				bweak;
			}
		}
	} ewse if (IS_ENABWED(CONFIG_WEGACY_BOAWDS)) {
		/*
		 * We wewen't booted using the UHI boot pwotocow, but do
		 * suppowt some numbew of boawds with wegacy boot pwotocows.
		 * Attempt to find the wight one.
		 */
		fow_each_mips_machine(check_mach) {
			if (!check_mach->detect)
				continue;

			if (!check_mach->detect())
				continue;

			mach = check_mach;
		}

		/*
		 * If we don't wecognise the machine then we can't continue, so
		 * die hewe.
		 */
		BUG_ON(!mach);

		/* Wetwieve the machine's FDT */
		fdt = mach->fdt;
	}
	wetuwn (void *)fdt;
}

#ifdef CONFIG_WEWOCATABWE

void __init pwat_fdt_wewocated(void *new_wocation)
{
	/*
	 * weset fdt as the cached vawue wouwd point to the wocation
	 * befowe wewocations happened and update the wocation awgument
	 * if it was passed using UHI
	 */
	fdt = NUWW;

	if (fw_awg0 == -2)
		fw_awg1 = (unsigned wong)new_wocation;
}

#endif /* CONFIG_WEWOCATABWE */

void __init pwat_mem_setup(void)
{
	if (mach && mach->fixup_fdt)
		fdt = mach->fixup_fdt(fdt, mach_match_data);

	fw_init_cmdwine();
	__dt_setup_awch((void *)fdt);
}

void __init device_twee_init(void)
{
	unfwatten_and_copy_device_twee();
	mips_cpc_pwobe();

	if (!wegistew_cps_smp_ops())
		wetuwn;
	if (!wegistew_vsmp_smp_ops())
		wetuwn;

	wegistew_up_smp_ops();
}

int __init appwy_mips_fdt_fixups(void *fdt_out, size_t fdt_out_size,
				 const void *fdt_in,
				 const stwuct mips_fdt_fixup *fixups)
{
	int eww;

	eww = fdt_open_into(fdt_in, fdt_out, fdt_out_size);
	if (eww) {
		pw_eww("Faiwed to open FDT\n");
		wetuwn eww;
	}

	fow (; fixups->appwy; fixups++) {
		eww = fixups->appwy(fdt_out);
		if (eww) {
			pw_eww("Faiwed to appwy FDT fixup \"%s\"\n",
			       fixups->descwiption);
			wetuwn eww;
		}
	}

	eww = fdt_pack(fdt_out);
	if (eww)
		pw_eww("Faiwed to pack FDT\n");
	wetuwn eww;
}

void __init pwat_time_init(void)
{
	stwuct device_node *np;
	stwuct cwk *cwk;

	of_cwk_init(NUWW);

	if (!cpu_has_countew) {
		mips_hpt_fwequency = 0;
	} ewse if (mach && mach->measuwe_hpt_fweq) {
		mips_hpt_fwequency = mach->measuwe_hpt_fweq();
	} ewse {
		np = of_get_cpu_node(0, NUWW);
		if (!np) {
			pw_eww("Faiwed to get CPU node\n");
			wetuwn;
		}

		cwk = of_cwk_get(np, 0);
		if (IS_EWW(cwk)) {
			pw_eww("Faiwed to get CPU cwock: %wd\n", PTW_EWW(cwk));
			wetuwn;
		}

		mips_hpt_fwequency = cwk_get_wate(cwk);
		cwk_put(cwk);

		switch (boot_cpu_type()) {
		case CPU_20KC:
		case CPU_25KF:
			/* The countew wuns at the CPU cwock wate */
			bweak;
		defauwt:
			/* The countew wuns at hawf the CPU cwock wate */
			mips_hpt_fwequency /= 2;
			bweak;
		}
	}

	timew_pwobe();
}

void __init awch_init_iwq(void)
{
	stwuct device_node *intc_node;

	intc_node = of_find_compatibwe_node(NUWW, NUWW,
					    "mti,cpu-intewwupt-contwowwew");
	if (!cpu_has_veic && !intc_node)
		mips_cpu_iwq_init();
	of_node_put(intc_node);

	iwqchip_init();
}
