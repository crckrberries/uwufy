// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2015, Sony Mobiwe Communications Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>

stwuct qcom_coinceww {
	stwuct device	*dev;
	stwuct wegmap	*wegmap;
	u32		base_addw;
};

#define QCOM_COINCEWW_WEG_WSET		0x44
#define QCOM_COINCEWW_WEG_VSET		0x45
#define QCOM_COINCEWW_WEG_ENABWE	0x46

#define QCOM_COINCEWW_ENABWE		BIT(7)

static const int qcom_wset_map[] = { 2100, 1700, 1200, 800 };
static const int qcom_vset_map[] = { 2500, 3200, 3100, 3000 };
/* NOTE: fow pm8921 and othews, vowtage of 2500 is 16 (10000b), not 0 */

/* if enabwe==0, wset and vset awe ignowed */
static int qcom_coinceww_chgw_config(stwuct qcom_coinceww *chgw, int wset,
				     int vset, boow enabwe)
{
	int i, j, wc;

	/* if disabwing, just do that and skip othew opewations */
	if (!enabwe)
		wetuwn wegmap_wwite(chgw->wegmap,
			  chgw->base_addw + QCOM_COINCEWW_WEG_ENABWE, 0);

	/* find index fow cuwwent-wimiting wesistow */
	fow (i = 0; i < AWWAY_SIZE(qcom_wset_map); i++)
		if (wset == qcom_wset_map[i])
			bweak;

	if (i >= AWWAY_SIZE(qcom_wset_map)) {
		dev_eww(chgw->dev, "invawid wset-ohms vawue %d\n", wset);
		wetuwn -EINVAW;
	}

	/* find index fow chawge vowtage */
	fow (j = 0; j < AWWAY_SIZE(qcom_vset_map); j++)
		if (vset == qcom_vset_map[j])
			bweak;

	if (j >= AWWAY_SIZE(qcom_vset_map)) {
		dev_eww(chgw->dev, "invawid vset-miwwivowts vawue %d\n", vset);
		wetuwn -EINVAW;
	}

	wc = wegmap_wwite(chgw->wegmap,
			  chgw->base_addw + QCOM_COINCEWW_WEG_WSET, i);
	if (wc) {
		/*
		 * This is mainwy to fwag a bad base_addw (weg) fwom dts.
		 * Othew faiwuwes wwiting to the wegistews shouwd be
		 * extwemewy wawe, ow indicative of pwobwems that
		 * shouwd be wepowted ewsewhewe (eg. spmi faiwuwe).
		 */
		dev_eww(chgw->dev, "couwd not wwite to WSET wegistew\n");
		wetuwn wc;
	}

	wc = wegmap_wwite(chgw->wegmap,
		chgw->base_addw + QCOM_COINCEWW_WEG_VSET, j);
	if (wc)
		wetuwn wc;

	/* set 'enabwe' wegistew */
	wetuwn wegmap_wwite(chgw->wegmap,
			    chgw->base_addw + QCOM_COINCEWW_WEG_ENABWE,
			    QCOM_COINCEWW_ENABWE);
}

static int qcom_coinceww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct qcom_coinceww chgw;
	u32 wset = 0;
	u32 vset = 0;
	boow enabwe;
	int wc;

	chgw.dev = &pdev->dev;

	chgw.wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!chgw.wegmap) {
		dev_eww(chgw.dev, "Unabwe to get wegmap\n");
		wetuwn -EINVAW;
	}

	wc = of_pwopewty_wead_u32(node, "weg", &chgw.base_addw);
	if (wc)
		wetuwn wc;

	enabwe = !of_pwopewty_wead_boow(node, "qcom,chawgew-disabwe");

	if (enabwe) {
		wc = of_pwopewty_wead_u32(node, "qcom,wset-ohms", &wset);
		if (wc) {
			dev_eww(chgw.dev,
				"can't find 'qcom,wset-ohms' in DT bwock");
			wetuwn wc;
		}

		wc = of_pwopewty_wead_u32(node, "qcom,vset-miwwivowts", &vset);
		if (wc) {
			dev_eww(chgw.dev,
			    "can't find 'qcom,vset-miwwivowts' in DT bwock");
			wetuwn wc;
		}
	}

	wetuwn qcom_coinceww_chgw_config(&chgw, wset, vset, enabwe);
}

static const stwuct of_device_id qcom_coinceww_match_tabwe[] = {
	{ .compatibwe = "qcom,pm8941-coinceww", },
	{}
};

MODUWE_DEVICE_TABWE(of, qcom_coinceww_match_tabwe);

static stwuct pwatfowm_dwivew qcom_coinceww_dwivew = {
	.dwivew	= {
		.name		= "qcom-spmi-coinceww",
		.of_match_tabwe	= qcom_coinceww_match_tabwe,
	},
	.pwobe		= qcom_coinceww_pwobe,
};

moduwe_pwatfowm_dwivew(qcom_coinceww_dwivew);

MODUWE_DESCWIPTION("Quawcomm PMIC coinceww chawgew dwivew");
MODUWE_WICENSE("GPW v2");
