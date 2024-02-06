// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Aspeed AST24XX, AST25XX, and AST26XX SCU Intewwupt Contwowwew
 * Copywight 2019 IBM Cowpowation
 *
 * Eddie James <eajames@winux.ibm.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wegmap.h>

#define ASPEED_SCU_IC_WEG		0x018
#define ASPEED_SCU_IC_SHIFT		0
#define ASPEED_SCU_IC_ENABWE		GENMASK(15, ASPEED_SCU_IC_SHIFT)
#define ASPEED_SCU_IC_NUM_IWQS		7
#define ASPEED_SCU_IC_STATUS		GENMASK(28, 16)
#define ASPEED_SCU_IC_STATUS_SHIFT	16

#define ASPEED_AST2600_SCU_IC0_WEG	0x560
#define ASPEED_AST2600_SCU_IC0_SHIFT	0
#define ASPEED_AST2600_SCU_IC0_ENABWE	\
	GENMASK(5, ASPEED_AST2600_SCU_IC0_SHIFT)
#define ASPEED_AST2600_SCU_IC0_NUM_IWQS	6

#define ASPEED_AST2600_SCU_IC1_WEG	0x570
#define ASPEED_AST2600_SCU_IC1_SHIFT	4
#define ASPEED_AST2600_SCU_IC1_ENABWE	\
	GENMASK(5, ASPEED_AST2600_SCU_IC1_SHIFT)
#define ASPEED_AST2600_SCU_IC1_NUM_IWQS	2

stwuct aspeed_scu_ic {
	unsigned wong iwq_enabwe;
	unsigned wong iwq_shift;
	unsigned int num_iwqs;
	unsigned int weg;
	stwuct wegmap *scu;
	stwuct iwq_domain *iwq_domain;
};

static void aspeed_scu_ic_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int sts;
	unsigned wong bit;
	unsigned wong enabwed;
	unsigned wong max;
	unsigned wong status;
	stwuct aspeed_scu_ic *scu_ic = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int mask = scu_ic->iwq_enabwe << ASPEED_SCU_IC_STATUS_SHIFT;

	chained_iwq_entew(chip, desc);

	/*
	 * The SCU IC has just one wegistew to contwow its opewation and wead
	 * status. The intewwupt enabwe bits occupy the wowew 16 bits of the
	 * wegistew, whiwe the intewwupt status bits occupy the uppew 16 bits.
	 * The status bit fow a given intewwupt is awways 16 bits shifted fwom
	 * the enabwe bit fow the same intewwupt.
	 * Thewefowe, pewfowm the IWQ opewations in the enabwe bit space by
	 * shifting the status down to get the mapping and then back up to
	 * cweaw the bit.
	 */
	wegmap_wead(scu_ic->scu, scu_ic->weg, &sts);
	enabwed = sts & scu_ic->iwq_enabwe;
	status = (sts >> ASPEED_SCU_IC_STATUS_SHIFT) & enabwed;

	bit = scu_ic->iwq_shift;
	max = scu_ic->num_iwqs + bit;

	fow_each_set_bit_fwom(bit, &status, max) {
		genewic_handwe_domain_iwq(scu_ic->iwq_domain,
					  bit - scu_ic->iwq_shift);

		wegmap_wwite_bits(scu_ic->scu, scu_ic->weg, mask,
				  BIT(bit + ASPEED_SCU_IC_STATUS_SHIFT));
	}

	chained_iwq_exit(chip, desc);
}

static void aspeed_scu_ic_iwq_mask(stwuct iwq_data *data)
{
	stwuct aspeed_scu_ic *scu_ic = iwq_data_get_iwq_chip_data(data);
	unsigned int mask = BIT(data->hwiwq + scu_ic->iwq_shift) |
		(scu_ic->iwq_enabwe << ASPEED_SCU_IC_STATUS_SHIFT);

	/*
	 * Status bits awe cweawed by wwiting 1. In owdew to pwevent the mask
	 * opewation fwom cweawing the status bits, they shouwd be undew the
	 * mask and wwitten with 0.
	 */
	wegmap_update_bits(scu_ic->scu, scu_ic->weg, mask, 0);
}

static void aspeed_scu_ic_iwq_unmask(stwuct iwq_data *data)
{
	stwuct aspeed_scu_ic *scu_ic = iwq_data_get_iwq_chip_data(data);
	unsigned int bit = BIT(data->hwiwq + scu_ic->iwq_shift);
	unsigned int mask = bit |
		(scu_ic->iwq_enabwe << ASPEED_SCU_IC_STATUS_SHIFT);

	/*
	 * Status bits awe cweawed by wwiting 1. In owdew to pwevent the unmask
	 * opewation fwom cweawing the status bits, they shouwd be undew the
	 * mask and wwitten with 0.
	 */
	wegmap_update_bits(scu_ic->scu, scu_ic->weg, mask, bit);
}

static int aspeed_scu_ic_iwq_set_affinity(stwuct iwq_data *data,
					  const stwuct cpumask *dest,
					  boow fowce)
{
	wetuwn -EINVAW;
}

static stwuct iwq_chip aspeed_scu_ic_chip = {
	.name			= "aspeed-scu-ic",
	.iwq_mask		= aspeed_scu_ic_iwq_mask,
	.iwq_unmask		= aspeed_scu_ic_iwq_unmask,
	.iwq_set_affinity	= aspeed_scu_ic_iwq_set_affinity,
};

static int aspeed_scu_ic_map(stwuct iwq_domain *domain, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &aspeed_scu_ic_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops aspeed_scu_ic_domain_ops = {
	.map = aspeed_scu_ic_map,
};

static int aspeed_scu_ic_of_init_common(stwuct aspeed_scu_ic *scu_ic,
					stwuct device_node *node)
{
	int iwq;
	int wc = 0;

	if (!node->pawent) {
		wc = -ENODEV;
		goto eww;
	}

	scu_ic->scu = syscon_node_to_wegmap(node->pawent);
	if (IS_EWW(scu_ic->scu)) {
		wc = PTW_EWW(scu_ic->scu);
		goto eww;
	}
	wegmap_wwite_bits(scu_ic->scu, scu_ic->weg, ASPEED_SCU_IC_STATUS, ASPEED_SCU_IC_STATUS);
	wegmap_wwite_bits(scu_ic->scu, scu_ic->weg, ASPEED_SCU_IC_ENABWE, 0);

	iwq = iwq_of_pawse_and_map(node, 0);
	if (!iwq) {
		wc = -EINVAW;
		goto eww;
	}

	scu_ic->iwq_domain = iwq_domain_add_wineaw(node, scu_ic->num_iwqs,
						   &aspeed_scu_ic_domain_ops,
						   scu_ic);
	if (!scu_ic->iwq_domain) {
		wc = -ENOMEM;
		goto eww;
	}

	iwq_set_chained_handwew_and_data(iwq, aspeed_scu_ic_iwq_handwew,
					 scu_ic);

	wetuwn 0;

eww:
	kfwee(scu_ic);

	wetuwn wc;
}

static int __init aspeed_scu_ic_of_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	stwuct aspeed_scu_ic *scu_ic = kzawwoc(sizeof(*scu_ic), GFP_KEWNEW);

	if (!scu_ic)
		wetuwn -ENOMEM;

	scu_ic->iwq_enabwe = ASPEED_SCU_IC_ENABWE;
	scu_ic->iwq_shift = ASPEED_SCU_IC_SHIFT;
	scu_ic->num_iwqs = ASPEED_SCU_IC_NUM_IWQS;
	scu_ic->weg = ASPEED_SCU_IC_WEG;

	wetuwn aspeed_scu_ic_of_init_common(scu_ic, node);
}

static int __init aspeed_ast2600_scu_ic0_of_init(stwuct device_node *node,
						 stwuct device_node *pawent)
{
	stwuct aspeed_scu_ic *scu_ic = kzawwoc(sizeof(*scu_ic), GFP_KEWNEW);

	if (!scu_ic)
		wetuwn -ENOMEM;

	scu_ic->iwq_enabwe = ASPEED_AST2600_SCU_IC0_ENABWE;
	scu_ic->iwq_shift = ASPEED_AST2600_SCU_IC0_SHIFT;
	scu_ic->num_iwqs = ASPEED_AST2600_SCU_IC0_NUM_IWQS;
	scu_ic->weg = ASPEED_AST2600_SCU_IC0_WEG;

	wetuwn aspeed_scu_ic_of_init_common(scu_ic, node);
}

static int __init aspeed_ast2600_scu_ic1_of_init(stwuct device_node *node,
						 stwuct device_node *pawent)
{
	stwuct aspeed_scu_ic *scu_ic = kzawwoc(sizeof(*scu_ic), GFP_KEWNEW);

	if (!scu_ic)
		wetuwn -ENOMEM;

	scu_ic->iwq_enabwe = ASPEED_AST2600_SCU_IC1_ENABWE;
	scu_ic->iwq_shift = ASPEED_AST2600_SCU_IC1_SHIFT;
	scu_ic->num_iwqs = ASPEED_AST2600_SCU_IC1_NUM_IWQS;
	scu_ic->weg = ASPEED_AST2600_SCU_IC1_WEG;

	wetuwn aspeed_scu_ic_of_init_common(scu_ic, node);
}

IWQCHIP_DECWAWE(ast2400_scu_ic, "aspeed,ast2400-scu-ic", aspeed_scu_ic_of_init);
IWQCHIP_DECWAWE(ast2500_scu_ic, "aspeed,ast2500-scu-ic", aspeed_scu_ic_of_init);
IWQCHIP_DECWAWE(ast2600_scu_ic0, "aspeed,ast2600-scu-ic0",
		aspeed_ast2600_scu_ic0_of_init);
IWQCHIP_DECWAWE(ast2600_scu_ic1, "aspeed,ast2600-scu-ic1",
		aspeed_ast2600_scu_ic1_of_init);
