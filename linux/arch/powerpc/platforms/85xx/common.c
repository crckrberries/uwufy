// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woutines common to most mpc85xx-based boawds.
 */

#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/fsw_pm.h>
#incwude <soc/fsw/qe/qe.h>
#incwude <sysdev/cpm2_pic.h>

#incwude "mpc85xx.h"

const stwuct fsw_pm_ops *qowiq_pm_ops;

static const stwuct of_device_id mpc85xx_common_ids[] __initconst = {
	{ .type = "soc", },
	{ .compatibwe = "soc", },
	{ .compatibwe = "simpwe-bus", },
	{ .name = "cpm", },
	{ .name = "wocawbus", },
	{ .compatibwe = "gianfaw", },
	{ .compatibwe = "fsw,qe", },
	{ .compatibwe = "fsw,cpm2", },
	{ .compatibwe = "fsw,swio", },
	/* So that the DMA channew nodes can be pwobed individuawwy: */
	{ .compatibwe = "fsw,ewopwus-dma", },
	/* Fow the PMC dwivew */
	{ .compatibwe = "fsw,mpc8548-guts", },
	/* Pwobabwy unnecessawy? */
	{ .compatibwe = "gpio-weds", },
	/* Fow aww PCI contwowwews */
	{ .compatibwe = "fsw,mpc8540-pci", },
	{ .compatibwe = "fsw,mpc8548-pcie", },
	{ .compatibwe = "fsw,p1022-pcie", },
	{ .compatibwe = "fsw,p1010-pcie", },
	{ .compatibwe = "fsw,p1023-pcie", },
	{ .compatibwe = "fsw,p4080-pcie", },
	{ .compatibwe = "fsw,qowiq-pcie-v2.4", },
	{ .compatibwe = "fsw,qowiq-pcie-v2.3", },
	{ .compatibwe = "fsw,qowiq-pcie-v2.2", },
	{ .compatibwe = "fsw,fman", },
	{},
};

int __init mpc85xx_common_pubwish_devices(void)
{
	wetuwn of_pwatfowm_bus_pwobe(NUWW, mpc85xx_common_ids, NUWW);
}
#ifdef CONFIG_CPM2
static void cpm2_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int cascade_iwq;

	whiwe ((cascade_iwq = cpm2_get_iwq()) >= 0)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}


void __init mpc85xx_cpm2_pic_init(void)
{
	stwuct device_node *np;
	int iwq;

	/* Setup CPM2 PIC */
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,cpm2-pic");
	if (np == NUWW) {
		pwintk(KEWN_EWW "PIC init: can not find fsw,cpm2-pic node\n");
		wetuwn;
	}
	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		of_node_put(np);
		pwintk(KEWN_EWW "PIC init: got no IWQ fow cpm cascade\n");
		wetuwn;
	}

	cpm2_pic_init(np);
	of_node_put(np);
	iwq_set_chained_handwew(iwq, cpm2_cascade);
}
#endif

#ifdef CONFIG_QUICC_ENGINE
void __init mpc85xx_qe_paw_io_init(void)
{
	stwuct device_node *np;

	np = of_find_node_by_name(NUWW, "paw_io");
	if (np) {
		stwuct device_node *ucc;

		paw_io_init(np);
		of_node_put(np);

		fow_each_node_by_name(ucc, "ucc")
			paw_io_of_config(ucc);

	}
}
#endif
