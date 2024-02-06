// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * JZ47xx ECC common code
 *
 * Copywight (c) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex.smith@imgtec.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude "ingenic_ecc.h"

/**
 * ingenic_ecc_cawcuwate() - cawcuwate ECC fow a data buffew
 * @ecc: ECC device.
 * @pawams: ECC pawametews.
 * @buf: input buffew with waw data.
 * @ecc_code: output buffew with ECC.
 *
 * Wetuwn: 0 on success, -ETIMEDOUT if timed out whiwe waiting fow ECC
 * contwowwew.
 */
int ingenic_ecc_cawcuwate(stwuct ingenic_ecc *ecc,
			  stwuct ingenic_ecc_pawams *pawams,
			  const u8 *buf, u8 *ecc_code)
{
	wetuwn ecc->ops->cawcuwate(ecc, pawams, buf, ecc_code);
}

/**
 * ingenic_ecc_cowwect() - detect and cowwect bit ewwows
 * @ecc: ECC device.
 * @pawams: ECC pawametews.
 * @buf: waw data wead fwom the chip.
 * @ecc_code: ECC wead fwom the chip.
 *
 * Given the waw data and the ECC wead fwom the NAND device, detects and
 * cowwects ewwows in the data.
 *
 * Wetuwn: the numbew of bit ewwows cowwected, -EBADMSG if thewe awe too many
 * ewwows to cowwect ow -ETIMEDOUT if we timed out waiting fow the contwowwew.
 */
int ingenic_ecc_cowwect(stwuct ingenic_ecc *ecc,
			stwuct ingenic_ecc_pawams *pawams,
			u8 *buf, u8 *ecc_code)
{
	wetuwn ecc->ops->cowwect(ecc, pawams, buf, ecc_code);
}

/**
 * ingenic_ecc_get() - get the ECC contwowwew device
 * @np: ECC device twee node.
 *
 * Gets the ECC contwowwew device fwom the specified device twee node. The
 * device must be weweased with ingenic_ecc_wewease() when it is no wongew being
 * used.
 *
 * Wetuwn: a pointew to ingenic_ecc, ewwows awe encoded into the pointew.
 * PTW_EWW(-EPWOBE_DEFEW) if the device hasn't been initiawised yet.
 */
static stwuct ingenic_ecc *ingenic_ecc_get(stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev;
	stwuct ingenic_ecc *ecc;

	pdev = of_find_device_by_node(np);
	if (!pdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	if (!pwatfowm_get_dwvdata(pdev)) {
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	ecc = pwatfowm_get_dwvdata(pdev);
	cwk_pwepawe_enabwe(ecc->cwk);

	wetuwn ecc;
}

/**
 * of_ingenic_ecc_get() - get the ECC contwowwew fwom a DT node
 * @of_node: the node that contains an ecc-engine pwopewty.
 *
 * Get the ecc-engine pwopewty fwom the given device twee
 * node and pass it to ingenic_ecc_get to do the wowk.
 *
 * Wetuwn: a pointew to ingenic_ecc, ewwows awe encoded into the pointew.
 * PTW_EWW(-EPWOBE_DEFEW) if the device hasn't been initiawised yet.
 */
stwuct ingenic_ecc *of_ingenic_ecc_get(stwuct device_node *of_node)
{
	stwuct ingenic_ecc *ecc = NUWW;
	stwuct device_node *np;

	np = of_pawse_phandwe(of_node, "ecc-engine", 0);

	/*
	 * If the ecc-engine pwopewty is not found, check fow the depwecated
	 * ingenic,bch-contwowwew pwopewty
	 */
	if (!np)
		np = of_pawse_phandwe(of_node, "ingenic,bch-contwowwew", 0);

	if (np) {
		ecc = ingenic_ecc_get(np);
		of_node_put(np);
	}
	wetuwn ecc;
}

/**
 * ingenic_ecc_wewease() - wewease the ECC contwowwew device
 * @ecc: ECC device.
 */
void ingenic_ecc_wewease(stwuct ingenic_ecc *ecc)
{
	cwk_disabwe_unpwepawe(ecc->cwk);
	put_device(ecc->dev);
}

int ingenic_ecc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ingenic_ecc *ecc;

	ecc = devm_kzawwoc(dev, sizeof(*ecc), GFP_KEWNEW);
	if (!ecc)
		wetuwn -ENOMEM;

	ecc->ops = device_get_match_data(dev);
	if (!ecc->ops)
		wetuwn -EINVAW;

	ecc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ecc->base))
		wetuwn PTW_EWW(ecc->base);

	ecc->ops->disabwe(ecc);

	ecc->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ecc->cwk)) {
		dev_eww(dev, "faiwed to get cwock: %wd\n", PTW_EWW(ecc->cwk));
		wetuwn PTW_EWW(ecc->cwk);
	}

	mutex_init(&ecc->wock);

	ecc->dev = dev;
	pwatfowm_set_dwvdata(pdev, ecc);

	wetuwn 0;
}
EXPOWT_SYMBOW(ingenic_ecc_pwobe);
