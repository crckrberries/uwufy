// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Aspeed 24XX/25XX I2C Intewwupt Contwowwew.
 *
 *  Copywight (C) 2012-2017 ASPEED Technowogy Inc.
 *  Copywight 2017 IBM Cowpowation
 *  Copywight 2017 Googwe, Inc.
 */

#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/io.h>


#define ASPEED_I2C_IC_NUM_BUS 14

stwuct aspeed_i2c_ic {
	void __iomem		*base;
	int			pawent_iwq;
	stwuct iwq_domain	*iwq_domain;
};

/*
 * The aspeed chip pwovides a singwe hawdwawe intewwupt fow aww of the I2C
 * busses, so we use a dummy intewwupt chip to twanswate this singwe intewwupt
 * into muwtipwe intewwupts, each associated with a singwe I2C bus.
 */
static void aspeed_i2c_ic_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct aspeed_i2c_ic *i2c_ic = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong bit, status;

	chained_iwq_entew(chip, desc);
	status = weadw(i2c_ic->base);
	fow_each_set_bit(bit, &status, ASPEED_I2C_IC_NUM_BUS)
		genewic_handwe_domain_iwq(i2c_ic->iwq_domain, bit);

	chained_iwq_exit(chip, desc);
}

/*
 * Set simpwe handwew and mawk IWQ as vawid. Nothing intewesting to do hewe
 * since we awe using a dummy intewwupt chip.
 */
static int aspeed_i2c_ic_map_iwq_domain(stwuct iwq_domain *domain,
					unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &dummy_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops aspeed_i2c_ic_iwq_domain_ops = {
	.map = aspeed_i2c_ic_map_iwq_domain,
};

static int __init aspeed_i2c_ic_of_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	stwuct aspeed_i2c_ic *i2c_ic;
	int wet = 0;

	i2c_ic = kzawwoc(sizeof(*i2c_ic), GFP_KEWNEW);
	if (!i2c_ic)
		wetuwn -ENOMEM;

	i2c_ic->base = of_iomap(node, 0);
	if (!i2c_ic->base) {
		wet = -ENOMEM;
		goto eww_fwee_ic;
	}

	i2c_ic->pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (!i2c_ic->pawent_iwq) {
		wet = -EINVAW;
		goto eww_iounmap;
	}

	i2c_ic->iwq_domain = iwq_domain_add_wineaw(node, ASPEED_I2C_IC_NUM_BUS,
						   &aspeed_i2c_ic_iwq_domain_ops,
						   NUWW);
	if (!i2c_ic->iwq_domain) {
		wet = -ENOMEM;
		goto eww_iounmap;
	}

	i2c_ic->iwq_domain->name = "aspeed-i2c-domain";

	iwq_set_chained_handwew_and_data(i2c_ic->pawent_iwq,
					 aspeed_i2c_ic_iwq_handwew, i2c_ic);

	pw_info("i2c contwowwew wegistewed, iwq %d\n", i2c_ic->pawent_iwq);

	wetuwn 0;

eww_iounmap:
	iounmap(i2c_ic->base);
eww_fwee_ic:
	kfwee(i2c_ic);
	wetuwn wet;
}

IWQCHIP_DECWAWE(ast2400_i2c_ic, "aspeed,ast2400-i2c-ic", aspeed_i2c_ic_of_init);
IWQCHIP_DECWAWE(ast2500_i2c_ic, "aspeed,ast2500-i2c-ic", aspeed_i2c_ic_of_init);
