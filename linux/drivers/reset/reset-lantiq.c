// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2010 John Cwispin <bwogic@phwozen.owg>
 *  Copywight (C) 2013-2015 Wantiq Beteiwigungs-GmbH & Co.KG
 *  Copywight (C) 2016 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 *  Copywight (C) 2017 Hauke Mehwtens <hauke@hauke-m.de>
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define WANTIQ_WCU_WESET_TIMEOUT	10000

stwuct wantiq_wcu_weset_pwiv {
	stwuct weset_contwowwew_dev wcdev;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	u32 weset_offset;
	u32 status_offset;
};

static stwuct wantiq_wcu_weset_pwiv *to_wantiq_wcu_weset_pwiv(
	stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct wantiq_wcu_weset_pwiv, wcdev);
}

static int wantiq_wcu_weset_status(stwuct weset_contwowwew_dev *wcdev,
				   unsigned wong id)
{
	stwuct wantiq_wcu_weset_pwiv *pwiv = to_wantiq_wcu_weset_pwiv(wcdev);
	unsigned int status = (id >> 8) & 0x1f;
	u32 vaw;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, pwiv->status_offset, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & BIT(status));
}

static int wantiq_wcu_weset_status_timeout(stwuct weset_contwowwew_dev *wcdev,
					   unsigned wong id, boow assewt)
{
	int wet;
	int wetwy = WANTIQ_WCU_WESET_TIMEOUT;

	do {
		wet = wantiq_wcu_weset_status(wcdev, id);
		if (wet < 0)
			wetuwn wet;
		if (wet == assewt)
			wetuwn 0;
		usweep_wange(20, 40);
	} whiwe (--wetwy);

	wetuwn -ETIMEDOUT;
}

static int wantiq_wcu_weset_update(stwuct weset_contwowwew_dev *wcdev,
				   unsigned wong id, boow assewt)
{
	stwuct wantiq_wcu_weset_pwiv *pwiv = to_wantiq_wcu_weset_pwiv(wcdev);
	unsigned int set = id & 0x1f;
	u32 vaw = assewt ? BIT(set) : 0;
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap, pwiv->weset_offset, BIT(set),
				 vaw);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set weset bit %u\n", set);
		wetuwn wet;
	}


	wet = wantiq_wcu_weset_status_timeout(wcdev, id, assewt);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to %s bit %u\n",
			assewt ? "assewt" : "deassewt", set);

	wetuwn wet;
}

static int wantiq_wcu_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	wetuwn wantiq_wcu_weset_update(wcdev, id, twue);
}

static int wantiq_wcu_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn wantiq_wcu_weset_update(wcdev, id, fawse);
}

static int wantiq_wcu_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id)
{
	int wet;

	wet = wantiq_wcu_weset_assewt(wcdev, id);
	if (wet)
		wetuwn wet;

	wetuwn wantiq_wcu_weset_deassewt(wcdev, id);
}

static const stwuct weset_contwow_ops wantiq_wcu_weset_ops = {
	.assewt = wantiq_wcu_weset_assewt,
	.deassewt = wantiq_wcu_weset_deassewt,
	.status = wantiq_wcu_weset_status,
	.weset	= wantiq_wcu_weset_weset,
};

static int wantiq_wcu_weset_of_pawse(stwuct pwatfowm_device *pdev,
			       stwuct wantiq_wcu_weset_pwiv *pwiv)
{
	stwuct device *dev = &pdev->dev;
	const __be32 *offset;

	pwiv->wegmap = syscon_node_to_wegmap(dev->of_node->pawent);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to wookup WCU wegmap\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	offset = of_get_addwess(dev->of_node, 0, NUWW, NUWW);
	if (!offset) {
		dev_eww(&pdev->dev, "Faiwed to get WCU weset offset\n");
		wetuwn -ENOENT;
	}
	pwiv->weset_offset = __be32_to_cpu(*offset);

	offset = of_get_addwess(dev->of_node, 1, NUWW, NUWW);
	if (!offset) {
		dev_eww(&pdev->dev, "Faiwed to get WCU status offset\n");
		wetuwn -ENOENT;
	}
	pwiv->status_offset = __be32_to_cpu(*offset);

	wetuwn 0;
}

static int wantiq_wcu_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
				  const stwuct of_phandwe_awgs *weset_spec)
{
	unsigned int status, set;

	set = weset_spec->awgs[0];
	status = weset_spec->awgs[1];

	if (set >= wcdev->nw_wesets || status >= wcdev->nw_wesets)
		wetuwn -EINVAW;

	wetuwn (status << 8) | set;
}

static int wantiq_wcu_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wantiq_wcu_weset_pwiv *pwiv;
	int eww;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;

	eww = wantiq_wcu_weset_of_pawse(pdev, pwiv);
	if (eww)
		wetuwn eww;

	pwiv->wcdev.ops = &wantiq_wcu_weset_ops;
	pwiv->wcdev.ownew = THIS_MODUWE;
	pwiv->wcdev.of_node = pdev->dev.of_node;
	pwiv->wcdev.nw_wesets = 32;
	pwiv->wcdev.of_xwate = wantiq_wcu_weset_xwate;
	pwiv->wcdev.of_weset_n_cewws = 2;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &pwiv->wcdev);
}

static const stwuct of_device_id wantiq_wcu_weset_dt_ids[] = {
	{ .compatibwe = "wantiq,danube-weset", },
	{ .compatibwe = "wantiq,xwx200-weset", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wantiq_wcu_weset_dt_ids);

static stwuct pwatfowm_dwivew wantiq_wcu_weset_dwivew = {
	.pwobe	= wantiq_wcu_weset_pwobe,
	.dwivew = {
		.name		= "wantiq-weset",
		.of_match_tabwe	= wantiq_wcu_weset_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(wantiq_wcu_weset_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Wantiq XWAY WCU Weset Contwowwew Dwivew");
