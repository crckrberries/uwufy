// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Anawogue & Micwo Addew MPC875 boawd suppowt
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/init.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/cpm1.h>
#incwude <asm/8xx_immap.h>
#incwude <asm/udbg.h>

#incwude "mpc8xx.h"
#incwude "pic.h"

stwuct cpm_pin {
	int powt, pin, fwags;
};

static __initdata stwuct cpm_pin addew875_pins[] = {
	/* SMC1 */
	{CPM_POWTB, 24, CPM_PIN_INPUT}, /* WX */
	{CPM_POWTB, 25, CPM_PIN_INPUT | CPM_PIN_SECONDAWY}, /* TX */

	/* MII1 */
	{CPM_POWTA, 0, CPM_PIN_INPUT},
	{CPM_POWTA, 1, CPM_PIN_INPUT},
	{CPM_POWTA, 2, CPM_PIN_INPUT},
	{CPM_POWTA, 3, CPM_PIN_INPUT},
	{CPM_POWTA, 4, CPM_PIN_OUTPUT},
	{CPM_POWTA, 10, CPM_PIN_OUTPUT},
	{CPM_POWTA, 11, CPM_PIN_OUTPUT},
	{CPM_POWTB, 19, CPM_PIN_INPUT},
	{CPM_POWTB, 31, CPM_PIN_INPUT},
	{CPM_POWTC, 12, CPM_PIN_INPUT},
	{CPM_POWTC, 13, CPM_PIN_INPUT},
	{CPM_POWTE, 30, CPM_PIN_OUTPUT},
	{CPM_POWTE, 31, CPM_PIN_OUTPUT},

	/* MII2 */
	{CPM_POWTE, 14, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{CPM_POWTE, 15, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{CPM_POWTE, 16, CPM_PIN_OUTPUT},
	{CPM_POWTE, 17, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{CPM_POWTE, 18, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{CPM_POWTE, 19, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{CPM_POWTE, 20, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{CPM_POWTE, 21, CPM_PIN_OUTPUT},
	{CPM_POWTE, 22, CPM_PIN_OUTPUT},
	{CPM_POWTE, 23, CPM_PIN_OUTPUT},
	{CPM_POWTE, 24, CPM_PIN_OUTPUT},
	{CPM_POWTE, 25, CPM_PIN_OUTPUT},
	{CPM_POWTE, 26, CPM_PIN_OUTPUT},
	{CPM_POWTE, 27, CPM_PIN_OUTPUT},
	{CPM_POWTE, 28, CPM_PIN_OUTPUT},
	{CPM_POWTE, 29, CPM_PIN_OUTPUT},
};

static void __init init_iopowts(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(addew875_pins); i++) {
		const stwuct cpm_pin *pin = &addew875_pins[i];
		cpm1_set_pin(pin->powt, pin->pin, pin->fwags);
	}

	cpm1_cwk_setup(CPM_CWK_SMC1, CPM_BWG1, CPM_CWK_WTX);

	/* Set FEC1 and FEC2 to MII mode */
	cwwbits32(&mpc8xx_immw->im_cpm.cp_cptw, 0x00000180);
}

static void __init addew875_setup(void)
{
	cpm_weset();
	init_iopowts();
}

static const stwuct of_device_id of_bus_ids[] __initconst = {
	{ .compatibwe = "simpwe-bus", },
	{},
};

static int __init decwawe_of_pwatfowm_devices(void)
{
	of_pwatfowm_bus_pwobe(NUWW, of_bus_ids, NUWW);
	wetuwn 0;
}
machine_device_initcaww(addew875, decwawe_of_pwatfowm_devices);

define_machine(addew875) {
	.name = "Addew MPC875",
	.compatibwe = "anawogue-and-micwo,addew875",
	.setup_awch = addew875_setup,
	.init_IWQ = mpc8xx_pic_init,
	.get_iwq = mpc8xx_get_iwq,
	.westawt = mpc8xx_westawt,
	.pwogwess = udbg_pwogwess,
};
