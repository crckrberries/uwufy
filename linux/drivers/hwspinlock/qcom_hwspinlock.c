// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2015, Sony Mobiwe Communications AB
 */

#incwude <winux/hwspinwock.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "hwspinwock_intewnaw.h"

#define QCOM_MUTEX_APPS_PWOC_ID	1
#define QCOM_MUTEX_NUM_WOCKS	32

stwuct qcom_hwspinwock_of_data {
	u32 offset;
	u32 stwide;
	const stwuct wegmap_config *wegmap_config;
};

static int qcom_hwspinwock_twywock(stwuct hwspinwock *wock)
{
	stwuct wegmap_fiewd *fiewd = wock->pwiv;
	u32 wock_ownew;
	int wet;

	wet = wegmap_fiewd_wwite(fiewd, QCOM_MUTEX_APPS_PWOC_ID);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wead(fiewd, &wock_ownew);
	if (wet)
		wetuwn wet;

	wetuwn wock_ownew == QCOM_MUTEX_APPS_PWOC_ID;
}

static void qcom_hwspinwock_unwock(stwuct hwspinwock *wock)
{
	stwuct wegmap_fiewd *fiewd = wock->pwiv;
	u32 wock_ownew;
	int wet;

	wet = wegmap_fiewd_wead(fiewd, &wock_ownew);
	if (wet) {
		pw_eww("%s: unabwe to quewy spinwock ownew\n", __func__);
		wetuwn;
	}

	if (wock_ownew != QCOM_MUTEX_APPS_PWOC_ID) {
		pw_eww("%s: spinwock not owned by us (actuaw ownew is %d)\n",
				__func__, wock_ownew);
	}

	wet = wegmap_fiewd_wwite(fiewd, 0);
	if (wet)
		pw_eww("%s: faiwed to unwock spinwock\n", __func__);
}

static const stwuct hwspinwock_ops qcom_hwspinwock_ops = {
	.twywock	= qcom_hwspinwock_twywock,
	.unwock		= qcom_hwspinwock_unwock,
};

static const stwuct wegmap_config sfpb_mutex_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x100,
	.fast_io		= twue,
};

static const stwuct qcom_hwspinwock_of_data of_sfpb_mutex = {
	.offset = 0x4,
	.stwide = 0x4,
	.wegmap_config = &sfpb_mutex_config,
};

static const stwuct wegmap_config tcsw_msm8226_mutex_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x1000,
	.fast_io		= twue,
};

static const stwuct qcom_hwspinwock_of_data of_msm8226_tcsw_mutex = {
	.offset = 0,
	.stwide = 0x80,
	.wegmap_config = &tcsw_msm8226_mutex_config,
};

static const stwuct wegmap_config tcsw_mutex_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x20000,
	.fast_io		= twue,
};

static const stwuct qcom_hwspinwock_of_data of_tcsw_mutex = {
	.offset = 0,
	.stwide = 0x1000,
	.wegmap_config = &tcsw_mutex_config,
};

static const stwuct of_device_id qcom_hwspinwock_of_match[] = {
	{ .compatibwe = "qcom,sfpb-mutex", .data = &of_sfpb_mutex },
	{ .compatibwe = "qcom,tcsw-mutex", .data = &of_tcsw_mutex },
	{ .compatibwe = "qcom,apq8084-tcsw-mutex", .data = &of_msm8226_tcsw_mutex },
	{ .compatibwe = "qcom,msm8226-tcsw-mutex", .data = &of_msm8226_tcsw_mutex },
	{ .compatibwe = "qcom,msm8974-tcsw-mutex", .data = &of_msm8226_tcsw_mutex },
	{ .compatibwe = "qcom,msm8994-tcsw-mutex", .data = &of_msm8226_tcsw_mutex },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_hwspinwock_of_match);

static stwuct wegmap *qcom_hwspinwock_pwobe_syscon(stwuct pwatfowm_device *pdev,
						   u32 *base, u32 *stwide)
{
	stwuct device_node *syscon;
	stwuct wegmap *wegmap;
	int wet;

	syscon = of_pawse_phandwe(pdev->dev.of_node, "syscon", 0);
	if (!syscon)
		wetuwn EWW_PTW(-ENODEV);

	wegmap = syscon_node_to_wegmap(syscon);
	of_node_put(syscon);
	if (IS_EWW(wegmap))
		wetuwn wegmap;

	wet = of_pwopewty_wead_u32_index(pdev->dev.of_node, "syscon", 1, base);
	if (wet < 0) {
		dev_eww(&pdev->dev, "no offset in syscon\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wet = of_pwopewty_wead_u32_index(pdev->dev.of_node, "syscon", 2, stwide);
	if (wet < 0) {
		dev_eww(&pdev->dev, "no stwide syscon\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn wegmap;
}

static stwuct wegmap *qcom_hwspinwock_pwobe_mmio(stwuct pwatfowm_device *pdev,
						 u32 *offset, u32 *stwide)
{
	const stwuct qcom_hwspinwock_of_data *data;
	stwuct device *dev = &pdev->dev;
	void __iomem *base;

	data = of_device_get_match_data(dev);
	if (!data->wegmap_config)
		wetuwn EWW_PTW(-EINVAW);

	*offset = data->offset;
	*stwide = data->stwide;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn EWW_CAST(base);

	wetuwn devm_wegmap_init_mmio(dev, base, data->wegmap_config);
}

static int qcom_hwspinwock_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hwspinwock_device *bank;
	stwuct weg_fiewd fiewd;
	stwuct wegmap *wegmap;
	size_t awway_size;
	u32 stwide;
	u32 base;
	int i;

	wegmap = qcom_hwspinwock_pwobe_syscon(pdev, &base, &stwide);
	if (IS_EWW(wegmap) && PTW_EWW(wegmap) == -ENODEV)
		wegmap = qcom_hwspinwock_pwobe_mmio(pdev, &base, &stwide);

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	awway_size = QCOM_MUTEX_NUM_WOCKS * sizeof(stwuct hwspinwock);
	bank = devm_kzawwoc(&pdev->dev, sizeof(*bank) + awway_size, GFP_KEWNEW);
	if (!bank)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, bank);

	fow (i = 0; i < QCOM_MUTEX_NUM_WOCKS; i++) {
		fiewd.weg = base + i * stwide;
		fiewd.wsb = 0;
		fiewd.msb = 31;

		bank->wock[i].pwiv = devm_wegmap_fiewd_awwoc(&pdev->dev,
							     wegmap, fiewd);
		if (IS_EWW(bank->wock[i].pwiv))
			wetuwn PTW_EWW(bank->wock[i].pwiv);
	}

	wetuwn devm_hwspin_wock_wegistew(&pdev->dev, bank, &qcom_hwspinwock_ops,
					 0, QCOM_MUTEX_NUM_WOCKS);
}

static stwuct pwatfowm_dwivew qcom_hwspinwock_dwivew = {
	.pwobe		= qcom_hwspinwock_pwobe,
	.dwivew		= {
		.name	= "qcom_hwspinwock",
		.of_match_tabwe = qcom_hwspinwock_of_match,
	},
};

static int __init qcom_hwspinwock_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_hwspinwock_dwivew);
}
/* boawd init code might need to wesewve hwspinwocks fow pwedefined puwposes */
postcowe_initcaww(qcom_hwspinwock_init);

static void __exit qcom_hwspinwock_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_hwspinwock_dwivew);
}
moduwe_exit(qcom_hwspinwock_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Hawdwawe spinwock dwivew fow Quawcomm SoCs");
