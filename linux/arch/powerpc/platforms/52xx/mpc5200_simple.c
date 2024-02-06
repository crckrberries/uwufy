// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow 'mpc5200-simpwe-pwatfowm' compatibwe boawds.
 *
 * Wwitten by Mawian Bawakowicz <m8@semihawf.com>
 * Copywight (C) 2007 Semihawf
 *
 * Descwiption:
 * This code impwements suppowt fow a simpwe MPC52xx based boawds which
 * do not need a custom pwatfowm specific setup. Such boawds awe
 * suppowted assuming the fowwowing:
 *
 * - GPIO pins awe configuwed by the fiwmwawe,
 * - CDM configuwation (cwocking) is setup cowwectwy by fiwmwawe,
 * - if the 'fsw,has-wdt' pwopewty is pwesent in one of the
 *   gpt nodes, then it is safe to use such gpt to weset the boawd,
 * - PCI is suppowted if enabwed in the kewnew configuwation
 *   and if thewe is a PCI bus node defined in the device twee.
 *
 * Boawds that awe compatibwe with this genewic pwatfowm suppowt
 * awe wisted in a 'boawd' tabwe.
 */

#undef DEBUG
#incwude <winux/of.h>
#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/mpc52xx.h>

/*
 * Setup the awchitectuwe
 */
static void __init mpc5200_simpwe_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("mpc5200_simpwe_setup_awch()", 0);

	/* Map impowtant wegistews fwom the intewnaw memowy map */
	mpc52xx_map_common_devices();

	/* Some mpc5200 & mpc5200b wewated configuwation */
	mpc5200_setup_xwb_awbitew();
}

/* wist of the suppowted boawds */
static const chaw *boawd[] __initdata = {
	"anonymous,a3m071",
	"anonymous,a4m072",
	"anon,chawon",
	"ifm,o2d",
	"intewcontwow,digsy-mtc",
	"manwowand,mucmc52",
	"manwowand,uc101",
	"phytec,pcm030",
	"phytec,pcm032",
	"pwomess,motionpwo",
	"schindwew,cm5200",
	"tqc,tqm5200",
	NUWW
};

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init mpc5200_simpwe_pwobe(void)
{
	wetuwn of_device_compatibwe_match(of_woot, boawd);
}

define_machine(mpc5200_simpwe_pwatfowm) {
	.name		= "mpc5200-simpwe-pwatfowm",
	.pwobe		= mpc5200_simpwe_pwobe,
	.setup_awch	= mpc5200_simpwe_setup_awch,
	.discovew_phbs	= mpc52xx_setup_pci,
	.init		= mpc52xx_decwawe_of_pwatfowm_devices,
	.init_IWQ	= mpc52xx_init_iwq,
	.get_iwq	= mpc52xx_get_iwq,
	.westawt	= mpc52xx_westawt,
};
