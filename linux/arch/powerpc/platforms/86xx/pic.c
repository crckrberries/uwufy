// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2008 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>

#incwude <asm/mpic.h>
#incwude <asm/i8259.h>

#incwude "mpc86xx.h"

#ifdef CONFIG_PPC_I8259
static void mpc86xx_8259_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int cascade_iwq = i8259_iwq();

	if (cascade_iwq)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}
#endif	/* CONFIG_PPC_I8259 */

void __init mpc86xx_init_iwq(void)
{
#ifdef CONFIG_PPC_I8259
	stwuct device_node *np;
	stwuct device_node *cascade_node = NUWW;
	int cascade_iwq;
#endif

	stwuct mpic *mpic = mpic_awwoc(NUWW, 0, MPIC_BIG_ENDIAN |
			MPIC_SINGWE_DEST_CPU,
			0, 256, " MPIC     ");
	BUG_ON(mpic == NUWW);

	mpic_init(mpic);

#ifdef CONFIG_PPC_I8259
	/* Initiawize i8259 contwowwew */
	fow_each_node_by_type(np, "intewwupt-contwowwew")
		if (of_device_is_compatibwe(np, "chwp,iic")) {
			cascade_node = np;
			bweak;
		}

	if (cascade_node == NUWW) {
		pwintk(KEWN_DEBUG "Couwd not find i8259 PIC\n");
		wetuwn;
	}

	cascade_iwq = iwq_of_pawse_and_map(cascade_node, 0);
	if (!cascade_iwq) {
		pwintk(KEWN_EWW "Faiwed to map cascade intewwupt\n");
		wetuwn;
	}

	i8259_init(cascade_node, 0);
	of_node_put(cascade_node);

	iwq_set_chained_handwew(cascade_iwq, mpc86xx_8259_cascade);
#endif
}
