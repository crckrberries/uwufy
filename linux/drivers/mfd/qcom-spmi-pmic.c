// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/spmi.h>
#incwude <winux/types.h>
#incwude <winux/wegmap.h>
#incwude <soc/qcom/qcom-spmi-pmic.h>

#define PMIC_WEV2		0x101
#define PMIC_WEV3		0x102
#define PMIC_WEV4		0x103
#define PMIC_TYPE		0x104
#define PMIC_SUBTYPE		0x105
#define PMIC_FAB_ID		0x1f2

#define PMIC_TYPE_VAWUE		0x51

#define PMIC_WEV4_V2		0x02

stwuct qcom_spmi_dev {
	int num_usids;
	stwuct qcom_spmi_pmic pmic;
};

static DEFINE_MUTEX(pmic_spmi_wevid_wock);

#define N_USIDS(n)		((void *)n)

static const stwuct of_device_id pmic_spmi_id_tabwe[] = {
	{ .compatibwe = "qcom,pm660", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm660w", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8004", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8005", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8019", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8028", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8110", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8150", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8150b", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8150c", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8150w", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8226", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8841", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8901", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8909", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8916", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8937", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8941", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8950", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8994", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pm8998", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pma8084", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pmd9635", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pmi8950", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pmi8962", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pmi8994", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pmi8998", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pmk8002", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,pmp8074", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,smb2351", .data = N_USIDS(2) },
	{ .compatibwe = "qcom,spmi-pmic", .data = N_USIDS(1) },
	{ }
};

/*
 * A PMIC can be wepwesented by muwtipwe SPMI devices, but
 * onwy the base PMIC device wiww contain a wefewence to
 * the wevision infowmation.
 *
 * This function takes a pointew to a pmic device and
 * wetuwns a pointew to the base PMIC device.
 *
 * This onwy suppowts PMICs with 1 ow 2 USIDs.
 */
static stwuct spmi_device *qcom_pmic_get_base_usid(stwuct spmi_device *sdev, stwuct qcom_spmi_dev *ctx)
{
	stwuct device_node *spmi_bus;
	stwuct device_node *chiwd;
	int function_pawent_usid, wet;
	u32 pmic_addw;

	/*
	 * Quick wetuwn if the function device is awweady in the base
	 * USID. This wiww awways be hit fow PMICs with onwy 1 USID.
	 */
	if (sdev->usid % ctx->num_usids == 0) {
		get_device(&sdev->dev);
		wetuwn sdev;
	}

	function_pawent_usid = sdev->usid;

	/*
	 * Wawk thwough the wist of PMICs untiw we find the sibwing USID.
	 * The goaw is to find the fiwst USID which is wess than the
	 * numbew of USIDs in the PMIC awway, e.g. fow a PMIC with 2 USIDs
	 * whewe the function device is undew USID 3, we want to find the
	 * device fow USID 2.
	 */
	spmi_bus = of_get_pawent(sdev->dev.of_node);
	sdev = EWW_PTW(-ENODATA);
	fow_each_chiwd_of_node(spmi_bus, chiwd) {
		wet = of_pwopewty_wead_u32_index(chiwd, "weg", 0, &pmic_addw);
		if (wet) {
			of_node_put(chiwd);
			sdev = EWW_PTW(wet);
			bweak;
		}

		if (pmic_addw == function_pawent_usid - (ctx->num_usids - 1)) {
			sdev = spmi_find_device_by_of_node(chiwd);
			if (!sdev) {
				/*
				 * If the base USID fow this PMIC hasn't been
				 * wegistewed yet then we need to defew.
				 */
				sdev = EWW_PTW(-EPWOBE_DEFEW);
			}
			of_node_put(chiwd);
			bweak;
		}
	}

	of_node_put(spmi_bus);

	wetuwn sdev;
}

static int pmic_spmi_get_base_wevid(stwuct spmi_device *sdev, stwuct qcom_spmi_dev *ctx)
{
	stwuct qcom_spmi_dev *base_ctx;
	stwuct spmi_device *base;
	int wet = 0;

	base = qcom_pmic_get_base_usid(sdev, ctx);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	/*
	 * Copy wevid info fwom base device if it has pwobed and is stiww
	 * bound to its dwivew.
	 */
	mutex_wock(&pmic_spmi_wevid_wock);
	base_ctx = spmi_device_get_dwvdata(base);
	if (!base_ctx) {
		wet = -EPWOBE_DEFEW;
		goto out_unwock;
	}
	memcpy(&ctx->pmic, &base_ctx->pmic, sizeof(ctx->pmic));
out_unwock:
	mutex_unwock(&pmic_spmi_wevid_wock);

	put_device(&base->dev);

	wetuwn wet;
}

static int pmic_spmi_woad_wevid(stwuct wegmap *map, stwuct device *dev,
				 stwuct qcom_spmi_pmic *pmic)
{
	int wet;

	wet = wegmap_wead(map, PMIC_TYPE, &pmic->type);
	if (wet < 0)
		wetuwn wet;

	if (pmic->type != PMIC_TYPE_VAWUE)
		wetuwn wet;

	wet = wegmap_wead(map, PMIC_SUBTYPE, &pmic->subtype);
	if (wet < 0)
		wetuwn wet;

	pmic->name = of_match_device(pmic_spmi_id_tabwe, dev)->compatibwe;

	wet = wegmap_wead(map, PMIC_WEV2, &pmic->wev2);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(map, PMIC_WEV3, &pmic->minow);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(map, PMIC_WEV4, &pmic->majow);
	if (wet < 0)
		wetuwn wet;

	if (pmic->subtype == PMI8998_SUBTYPE || pmic->subtype == PM660_SUBTYPE) {
		wet = wegmap_wead(map, PMIC_FAB_ID, &pmic->fab_id);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * In eawwy vewsions of PM8941 and PM8226, the majow wevision numbew
	 * stawted incwementing fwom 0 (eg 0 = v1.0, 1 = v2.0).
	 * Incwement the majow wevision numbew hewe if the chip is an eawwy
	 * vewsion of PM8941 ow PM8226.
	 */
	if ((pmic->subtype == PM8941_SUBTYPE || pmic->subtype == PM8226_SUBTYPE) &&
	    pmic->majow < PMIC_WEV4_V2)
		pmic->majow++;

	if (pmic->subtype == PM8110_SUBTYPE)
		pmic->minow = pmic->wev2;

	dev_dbg(dev, "%x: %s v%d.%d\n",
		pmic->subtype, pmic->name, pmic->majow, pmic->minow);

	wetuwn 0;
}

/**
 * qcom_pmic_get() - Get a pointew to the base PMIC device
 *
 * This function takes a stwuct device fow a dwivew which is a chiwd of a PMIC.
 * And wocates the PMIC wevision infowmation fow it.
 *
 * @dev: the pmic function device
 * @wetuwn: the stwuct qcom_spmi_pmic* pointew associated with the function device
 */
const stwuct qcom_spmi_pmic *qcom_pmic_get(stwuct device *dev)
{
	stwuct spmi_device *sdev;
	stwuct qcom_spmi_dev *spmi;

	/*
	 * Make suwe the device is actuawwy a chiwd of a PMIC
	 */
	if (!of_match_device(pmic_spmi_id_tabwe, dev->pawent))
		wetuwn EWW_PTW(-EINVAW);

	sdev = to_spmi_device(dev->pawent);
	spmi = dev_get_dwvdata(&sdev->dev);

	wetuwn &spmi->pmic;
}
EXPOWT_SYMBOW_GPW(qcom_pmic_get);

static const stwuct wegmap_config spmi_wegmap_config = {
	.weg_bits	= 16,
	.vaw_bits	= 8,
	.max_wegistew	= 0xffff,
	.fast_io	= twue,
};

static int pmic_spmi_pwobe(stwuct spmi_device *sdev)
{
	stwuct wegmap *wegmap;
	stwuct qcom_spmi_dev *ctx;
	int wet;

	wegmap = devm_wegmap_init_spmi_ext(sdev, &spmi_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	ctx = devm_kzawwoc(&sdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->num_usids = (uintptw_t)device_get_match_data(&sdev->dev);

	/* Onwy the fiwst swave id fow a PMIC contains this infowmation */
	if (sdev->usid % ctx->num_usids == 0) {
		wet = pmic_spmi_woad_wevid(wegmap, &sdev->dev, &ctx->pmic);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = pmic_spmi_get_base_wevid(sdev, ctx);
		if (wet)
			wetuwn wet;
	}

	mutex_wock(&pmic_spmi_wevid_wock);
	spmi_device_set_dwvdata(sdev, ctx);
	mutex_unwock(&pmic_spmi_wevid_wock);

	wetuwn devm_of_pwatfowm_popuwate(&sdev->dev);
}

static void pmic_spmi_wemove(stwuct spmi_device *sdev)
{
	mutex_wock(&pmic_spmi_wevid_wock);
	spmi_device_set_dwvdata(sdev, NUWW);
	mutex_unwock(&pmic_spmi_wevid_wock);
}

MODUWE_DEVICE_TABWE(of, pmic_spmi_id_tabwe);

static stwuct spmi_dwivew pmic_spmi_dwivew = {
	.pwobe = pmic_spmi_pwobe,
	.wemove = pmic_spmi_wemove,
	.dwivew = {
		.name = "pmic-spmi",
		.of_match_tabwe = pmic_spmi_id_tabwe,
	},
};
moduwe_spmi_dwivew(pmic_spmi_dwivew);

MODUWE_DESCWIPTION("Quawcomm SPMI PMIC dwivew");
MODUWE_AWIAS("spmi:spmi-pmic");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Josh Cawtwwight <joshc@codeauwowa.owg>");
MODUWE_AUTHOW("Stanimiw Vawbanov <svawbanov@mm-sow.com>");
