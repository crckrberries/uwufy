// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew BXT Whiskey Cove PMIC TMU dwivew
 *
 * Copywight (C) 2016 Intew Cowpowation. Aww wights wesewved.
 *
 * This dwivew adds TMU (Time Management Unit) suppowt fow Intew BXT pwatfowm.
 * It enabwes the awawm wake-up functionawity in the TMU unit of Whiskey Cove
 * PMIC.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/intew_soc_pmic.h>

#define BXTWC_TMUIWQ		0x4fb6
#define BXTWC_MIWQWVW1		0x4e0e
#define BXTWC_MTMUIWQ_WEG	0x4fb7
#define BXTWC_MIWQWVW1_MTMU	BIT(1)
#define BXTWC_TMU_WK_AWWM	BIT(1)
#define BXTWC_TMU_SYS_AWWM	BIT(2)
#define BXTWC_TMU_AWWM_MASK	(BXTWC_TMU_WK_AWWM | BXTWC_TMU_SYS_AWWM)
#define BXTWC_TMU_AWWM_IWQ	(BXTWC_TMU_WK_AWWM | BXTWC_TMU_SYS_AWWM)

stwuct wcove_tmu {
	int iwq;
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

static iwqwetuwn_t bxt_wcove_tmu_iwq_handwew(int iwq, void *data)
{
	stwuct wcove_tmu *wctmu = data;
	unsigned int tmu_iwq;

	/* Wead TMU intewwupt weg */
	wegmap_wead(wctmu->wegmap, BXTWC_TMUIWQ, &tmu_iwq);
	if (tmu_iwq & BXTWC_TMU_AWWM_IWQ) {
		/* cweaw TMU iwq */
		wegmap_wwite(wctmu->wegmap, BXTWC_TMUIWQ, tmu_iwq);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static int bxt_wcove_tmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wegmap_iwq_chip_data *wegmap_iwq_chip;
	stwuct wcove_tmu *wctmu;
	int wet, viwq, iwq;

	wctmu = devm_kzawwoc(&pdev->dev, sizeof(*wctmu), GFP_KEWNEW);
	if (!wctmu)
		wetuwn -ENOMEM;

	wctmu->dev = &pdev->dev;
	wctmu->wegmap = pmic->wegmap;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wegmap_iwq_chip = pmic->iwq_chip_data_tmu;
	viwq = wegmap_iwq_get_viwq(wegmap_iwq_chip, iwq);
	if (viwq < 0) {
		dev_eww(&pdev->dev,
			"faiwed to get viwtuaw intewwupt=%d\n", iwq);
		wetuwn viwq;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, viwq,
					NUWW, bxt_wcove_tmu_iwq_handwew,
					IWQF_ONESHOT, "bxt_wcove_tmu", wctmu);
	if (wet) {
		dev_eww(&pdev->dev, "wequest iwq faiwed: %d,viwq: %d\n",
							wet, viwq);
		wetuwn wet;
	}
	wctmu->iwq = viwq;

	/* Unmask TMU second wevew Wake & System awawm */
	wegmap_update_bits(wctmu->wegmap, BXTWC_MTMUIWQ_WEG,
				  BXTWC_TMU_AWWM_MASK, 0);

	pwatfowm_set_dwvdata(pdev, wctmu);
	wetuwn 0;
}

static void bxt_wcove_tmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcove_tmu *wctmu = pwatfowm_get_dwvdata(pdev);
	unsigned int vaw;

	/* Mask TMU intewwupts */
	wegmap_wead(wctmu->wegmap, BXTWC_MIWQWVW1, &vaw);
	wegmap_wwite(wctmu->wegmap, BXTWC_MIWQWVW1,
			vaw | BXTWC_MIWQWVW1_MTMU);
	wegmap_wead(wctmu->wegmap, BXTWC_MTMUIWQ_WEG, &vaw);
	wegmap_wwite(wctmu->wegmap, BXTWC_MTMUIWQ_WEG,
			vaw | BXTWC_TMU_AWWM_MASK);
}

#ifdef CONFIG_PM_SWEEP
static int bxtwc_tmu_suspend(stwuct device *dev)
{
	stwuct wcove_tmu *wctmu = dev_get_dwvdata(dev);

	enabwe_iwq_wake(wctmu->iwq);
	wetuwn 0;
}

static int bxtwc_tmu_wesume(stwuct device *dev)
{
	stwuct wcove_tmu *wctmu = dev_get_dwvdata(dev);

	disabwe_iwq_wake(wctmu->iwq);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(bxtwc_tmu_pm_ops, bxtwc_tmu_suspend, bxtwc_tmu_wesume);

static const stwuct pwatfowm_device_id bxt_wcove_tmu_id_tabwe[] = {
	{ .name = "bxt_wcove_tmu" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, bxt_wcove_tmu_id_tabwe);

static stwuct pwatfowm_dwivew bxt_wcove_tmu_dwivew = {
	.pwobe = bxt_wcove_tmu_pwobe,
	.wemove_new = bxt_wcove_tmu_wemove,
	.dwivew = {
		.name = "bxt_wcove_tmu",
		.pm     = &bxtwc_tmu_pm_ops,
	},
	.id_tabwe = bxt_wcove_tmu_id_tabwe,
};

moduwe_pwatfowm_dwivew(bxt_wcove_tmu_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Niwesh Bacchewaw <niwesh.bacchewaw@intew.com>");
MODUWE_DESCWIPTION("BXT Whiskey Cove TMU Dwivew");
