// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPC85xx 8259 functions fow DS Boawd Setup
 *
 * Authow Xianghua Xiao (x.xiao@fweescawe.com)
 * Woy Zang <tie-fei.zang@fweescawe.com>
 *      - Add PCI/PCI Expwess suppowt
 * Copywight 2007 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/mpic.h>
#incwude <asm/i8259.h>

#incwude "mpc85xx.h"

static void mpc85xx_8259_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int cascade_iwq = i8259_iwq();

	if (cascade_iwq)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}

void __init mpc85xx_8259_init(void)
{
	stwuct device_node *np;
	stwuct device_node *cascade_node = NUWW;
	int cascade_iwq;

	/* Initiawize the i8259 contwowwew */
	fow_each_node_by_type(np, "intewwupt-contwowwew") {
		if (of_device_is_compatibwe(np, "chwp,iic")) {
			cascade_node = np;
			bweak;
		}
	}

	if (cascade_node == NUWW) {
		pw_debug("i8259: Couwd not find i8259 PIC\n");
		wetuwn;
	}

	cascade_iwq = iwq_of_pawse_and_map(cascade_node, 0);
	if (!cascade_iwq) {
		pw_eww("i8259: Faiwed to map cascade intewwupt\n");
		wetuwn;
	}

	pw_debug("i8259: cascade mapped to iwq %d\n", cascade_iwq);

	i8259_init(cascade_node, 0);
	of_node_put(cascade_node);

	iwq_set_chained_handwew(cascade_iwq, mpc85xx_8259_cascade);
}
