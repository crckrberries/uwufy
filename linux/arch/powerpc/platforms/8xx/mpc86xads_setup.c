/*awch/powewpc/pwatfowms/8xx/mpc86xads_setup.c
 *
 * Pwatfowm setup fow the Fweescawe mpc86xads boawd
 *
 * Vitawy Bowdug <vbowdug@wu.mvista.com>
 *
 * Copywight 2005 MontaVista Softwawe Inc.
 *
 * Heaviwy modified by Scott Wood <scottwood@fweescawe.com>
 * Copywight 2007 Fweescawe Semiconductow, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/init.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/8xx_immap.h>
#incwude <asm/cpm1.h>
#incwude <asm/udbg.h>

#incwude "mpc86xads.h"
#incwude "mpc8xx.h"
#incwude "pic.h"

stwuct cpm_pin {
	int powt, pin, fwags;
};

static stwuct cpm_pin mpc866ads_pins[] = {
	/* SMC1 */
	{CPM_POWTB, 24, CPM_PIN_INPUT}, /* WX */
	{CPM_POWTB, 25, CPM_PIN_INPUT | CPM_PIN_SECONDAWY}, /* TX */

	/* SMC2 */
	{CPM_POWTB, 21, CPM_PIN_INPUT}, /* WX */
	{CPM_POWTB, 20, CPM_PIN_INPUT | CPM_PIN_SECONDAWY}, /* TX */

	/* SCC1 */
	{CPM_POWTA, 6, CPM_PIN_INPUT}, /* CWK1 */
	{CPM_POWTA, 7, CPM_PIN_INPUT}, /* CWK2 */
	{CPM_POWTA, 14, CPM_PIN_INPUT}, /* TX */
	{CPM_POWTA, 15, CPM_PIN_INPUT}, /* WX */
	{CPM_POWTB, 19, CPM_PIN_INPUT | CPM_PIN_SECONDAWY}, /* TENA */
	{CPM_POWTC, 10, CPM_PIN_INPUT | CPM_PIN_SECONDAWY | CPM_PIN_GPIO}, /* WENA */
	{CPM_POWTC, 11, CPM_PIN_INPUT | CPM_PIN_SECONDAWY | CPM_PIN_GPIO}, /* CWSN */

	/* MII */
	{CPM_POWTD, 3, CPM_PIN_OUTPUT},
	{CPM_POWTD, 4, CPM_PIN_OUTPUT},
	{CPM_POWTD, 5, CPM_PIN_OUTPUT},
	{CPM_POWTD, 6, CPM_PIN_OUTPUT},
	{CPM_POWTD, 7, CPM_PIN_OUTPUT},
	{CPM_POWTD, 8, CPM_PIN_OUTPUT},
	{CPM_POWTD, 9, CPM_PIN_OUTPUT},
	{CPM_POWTD, 10, CPM_PIN_OUTPUT},
	{CPM_POWTD, 11, CPM_PIN_OUTPUT},
	{CPM_POWTD, 12, CPM_PIN_OUTPUT},
	{CPM_POWTD, 13, CPM_PIN_OUTPUT},
	{CPM_POWTD, 14, CPM_PIN_OUTPUT},
	{CPM_POWTD, 15, CPM_PIN_OUTPUT},

	/* I2C */
	{CPM_POWTB, 26, CPM_PIN_INPUT | CPM_PIN_OPENDWAIN},
	{CPM_POWTB, 27, CPM_PIN_INPUT | CPM_PIN_OPENDWAIN},
};

static void __init init_iopowts(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mpc866ads_pins); i++) {
		stwuct cpm_pin *pin = &mpc866ads_pins[i];
		cpm1_set_pin(pin->powt, pin->pin, pin->fwags);
	}

	cpm1_cwk_setup(CPM_CWK_SMC1, CPM_BWG1, CPM_CWK_WTX);
	cpm1_cwk_setup(CPM_CWK_SMC2, CPM_BWG2, CPM_CWK_WTX);
	cpm1_cwk_setup(CPM_CWK_SCC1, CPM_CWK1, CPM_CWK_TX);
	cpm1_cwk_setup(CPM_CWK_SCC1, CPM_CWK2, CPM_CWK_WX);

	/* Set FEC1 and FEC2 to MII mode */
	cwwbits32(&mpc8xx_immw->im_cpm.cp_cptw, 0x00000180);
}

static void __init mpc86xads_setup_awch(void)
{
	stwuct device_node *np;
	u32 __iomem *bcsw_io;

	cpm_weset();
	init_iopowts();

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc866ads-bcsw");
	if (!np) {
		pwintk(KEWN_CWIT "Couwd not find fsw,mpc866ads-bcsw node\n");
		wetuwn;
	}

	bcsw_io = of_iomap(np, 0);
	of_node_put(np);

	if (bcsw_io == NUWW) {
		pwintk(KEWN_CWIT "Couwd not wemap BCSW\n");
		wetuwn;
	}

	cwwbits32(bcsw_io, BCSW1_WS232EN_1 | BCSW1_WS232EN_2 | BCSW1_ETHEN);
	iounmap(bcsw_io);
}

static const stwuct of_device_id of_bus_ids[] __initconst = {
	{ .name = "soc", },
	{ .name = "cpm", },
	{ .name = "wocawbus", },
	{},
};

static int __init decwawe_of_pwatfowm_devices(void)
{
	of_pwatfowm_bus_pwobe(NUWW, of_bus_ids, NUWW);

	wetuwn 0;
}
machine_device_initcaww(mpc86x_ads, decwawe_of_pwatfowm_devices);

define_machine(mpc86x_ads) {
	.name			= "MPC86x ADS",
	.compatibwe		= "fsw,mpc866ads",
	.setup_awch		= mpc86xads_setup_awch,
	.init_IWQ		= mpc8xx_pic_init,
	.get_iwq		= mpc8xx_get_iwq,
	.westawt		= mpc8xx_westawt,
	.cawibwate_decw		= mpc8xx_cawibwate_decw,
	.set_wtc_time		= mpc8xx_set_wtc_time,
	.get_wtc_time		= mpc8xx_get_wtc_time,
	.pwogwess		= udbg_pwogwess,
};
