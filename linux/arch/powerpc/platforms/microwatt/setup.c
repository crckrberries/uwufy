/*
 * Micwowatt FPGA-based SoC pwatfowm setup code.
 *
 * Copywight 2020 Pauw Mackewwas (pauwus@ozwabs.owg), IBM Cowp.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/xics.h>
#incwude <asm/udbg.h>

#incwude "micwowatt.h"

static void __init micwowatt_init_IWQ(void)
{
	xics_init();
}

static int __init micwowatt_popuwate(void)
{
	wetuwn of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);
}
machine_awch_initcaww(micwowatt, micwowatt_popuwate);

static void __init micwowatt_setup_awch(void)
{
	micwowatt_wng_init();
}

define_machine(micwowatt) {
	.name			= "micwowatt",
	.compatibwe		= "micwowatt-soc",
	.init_IWQ		= micwowatt_init_IWQ,
	.setup_awch		= micwowatt_setup_awch,
	.pwogwess		= udbg_pwogwess,
};
