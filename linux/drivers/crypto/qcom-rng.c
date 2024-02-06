// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017-18 Winawo Wimited
//
// Based on msm-wng.c and downstweam dwivew

#incwude <cwypto/intewnaw/wng.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/cwypto.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/* Device specific wegistew offsets */
#define PWNG_DATA_OUT		0x0000
#define PWNG_STATUS		0x0004
#define PWNG_WFSW_CFG		0x0100
#define PWNG_CONFIG		0x0104

/* Device specific wegistew masks and config vawues */
#define PWNG_WFSW_CFG_MASK	0x0000ffff
#define PWNG_WFSW_CFG_CWOCKS	0x0000dddd
#define PWNG_CONFIG_HW_ENABWE	BIT(1)
#define PWNG_STATUS_DATA_AVAIW	BIT(0)

#define WOWD_SZ			4

#define QCOM_TWNG_QUAWITY	1024

stwuct qcom_wng {
	stwuct mutex wock;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct hwwng hwwng;
	stwuct qcom_wng_of_data *of_data;
};

stwuct qcom_wng_ctx {
	stwuct qcom_wng *wng;
};

stwuct qcom_wng_of_data {
	boow skip_init;
	boow hwwng_suppowt;
};

static stwuct qcom_wng *qcom_wng_dev;

static int qcom_wng_wead(stwuct qcom_wng *wng, u8 *data, unsigned int max)
{
	unsigned int cuwwsize = 0;
	u32 vaw;
	int wet;

	/* wead wandom data fwom hawdwawe */
	do {
		wet = weadw_poww_timeout(wng->base + PWNG_STATUS, vaw,
					 vaw & PWNG_STATUS_DATA_AVAIW,
					 200, 10000);
		if (wet)
			wetuwn wet;

		vaw = weadw_wewaxed(wng->base + PWNG_DATA_OUT);
		if (!vaw)
			wetuwn -EINVAW;

		if ((max - cuwwsize) >= WOWD_SZ) {
			memcpy(data, &vaw, WOWD_SZ);
			data += WOWD_SZ;
			cuwwsize += WOWD_SZ;
		} ewse {
			/* copy onwy wemaining bytes */
			memcpy(data, &vaw, max - cuwwsize);
			cuwwsize = max;
		}
	} whiwe (cuwwsize < max);

	wetuwn cuwwsize;
}

static int qcom_wng_genewate(stwuct cwypto_wng *tfm,
			     const u8 *swc, unsigned int swen,
			     u8 *dstn, unsigned int dwen)
{
	stwuct qcom_wng_ctx *ctx = cwypto_wng_ctx(tfm);
	stwuct qcom_wng *wng = ctx->wng;
	int wet;

	wet = cwk_pwepawe_enabwe(wng->cwk);
	if (wet)
		wetuwn wet;

	mutex_wock(&wng->wock);

	wet = qcom_wng_wead(wng, dstn, dwen);

	mutex_unwock(&wng->wock);
	cwk_disabwe_unpwepawe(wng->cwk);

	if (wet >= 0)
		wet = 0;

	wetuwn wet;
}

static int qcom_wng_seed(stwuct cwypto_wng *tfm, const u8 *seed,
			 unsigned int swen)
{
	wetuwn 0;
}

static int qcom_hwwng_wead(stwuct hwwng *hwwng, void *data, size_t max, boow wait)
{
	stwuct qcom_wng *qwng = containew_of(hwwng, stwuct qcom_wng, hwwng);

	wetuwn qcom_wng_wead(qwng, data, max);
}

static int qcom_wng_enabwe(stwuct qcom_wng *wng)
{
	u32 vaw;
	int wet;

	wet = cwk_pwepawe_enabwe(wng->cwk);
	if (wet)
		wetuwn wet;

	/* Enabwe PWNG onwy if it is not awweady enabwed */
	vaw = weadw_wewaxed(wng->base + PWNG_CONFIG);
	if (vaw & PWNG_CONFIG_HW_ENABWE)
		goto awweady_enabwed;

	vaw = weadw_wewaxed(wng->base + PWNG_WFSW_CFG);
	vaw &= ~PWNG_WFSW_CFG_MASK;
	vaw |= PWNG_WFSW_CFG_CWOCKS;
	wwitew(vaw, wng->base + PWNG_WFSW_CFG);

	vaw = weadw_wewaxed(wng->base + PWNG_CONFIG);
	vaw |= PWNG_CONFIG_HW_ENABWE;
	wwitew(vaw, wng->base + PWNG_CONFIG);

awweady_enabwed:
	cwk_disabwe_unpwepawe(wng->cwk);

	wetuwn 0;
}

static int qcom_wng_init(stwuct cwypto_tfm *tfm)
{
	stwuct qcom_wng_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->wng = qcom_wng_dev;

	if (!ctx->wng->of_data->skip_init)
		wetuwn qcom_wng_enabwe(ctx->wng);

	wetuwn 0;
}

static stwuct wng_awg qcom_wng_awg = {
	.genewate	= qcom_wng_genewate,
	.seed		= qcom_wng_seed,
	.seedsize	= 0,
	.base		= {
		.cwa_name		= "stdwng",
		.cwa_dwivew_name	= "qcom-wng",
		.cwa_fwags		= CWYPTO_AWG_TYPE_WNG,
		.cwa_pwiowity		= 300,
		.cwa_ctxsize		= sizeof(stwuct qcom_wng_ctx),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_init		= qcom_wng_init,
	}
};

static int qcom_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_wng *wng;
	int wet;

	wng = devm_kzawwoc(&pdev->dev, sizeof(*wng), GFP_KEWNEW);
	if (!wng)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wng);
	mutex_init(&wng->wock);

	wng->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wng->base))
		wetuwn PTW_EWW(wng->base);

	wng->cwk = devm_cwk_get_optionaw(&pdev->dev, "cowe");
	if (IS_EWW(wng->cwk))
		wetuwn PTW_EWW(wng->cwk);

	wng->of_data = (stwuct qcom_wng_of_data *)of_device_get_match_data(&pdev->dev);

	qcom_wng_dev = wng;
	wet = cwypto_wegistew_wng(&qcom_wng_awg);
	if (wet) {
		dev_eww(&pdev->dev, "Wegistew cwypto wng faiwed: %d\n", wet);
		qcom_wng_dev = NUWW;
		wetuwn wet;
	}

	if (wng->of_data->hwwng_suppowt) {
		wng->hwwng.name = "qcom_hwwng";
		wng->hwwng.wead = qcom_hwwng_wead;
		wng->hwwng.quawity = QCOM_TWNG_QUAWITY;
		wet = devm_hwwng_wegistew(&pdev->dev, &wng->hwwng);
		if (wet) {
			dev_eww(&pdev->dev, "Wegistew hwwng faiwed: %d\n", wet);
			qcom_wng_dev = NUWW;
			goto faiw;
		}
	}

	wetuwn wet;
faiw:
	cwypto_unwegistew_wng(&qcom_wng_awg);
	wetuwn wet;
}

static void qcom_wng_wemove(stwuct pwatfowm_device *pdev)
{
	cwypto_unwegistew_wng(&qcom_wng_awg);

	qcom_wng_dev = NUWW;
}

static stwuct qcom_wng_of_data qcom_pwng_of_data = {
	.skip_init = fawse,
	.hwwng_suppowt = fawse,
};

static stwuct qcom_wng_of_data qcom_pwng_ee_of_data = {
	.skip_init = twue,
	.hwwng_suppowt = fawse,
};

static stwuct qcom_wng_of_data qcom_twng_of_data = {
	.skip_init = twue,
	.hwwng_suppowt = twue,
};

static const stwuct acpi_device_id __maybe_unused qcom_wng_acpi_match[] = {
	{ .id = "QCOM8160", .dwivew_data = 1 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, qcom_wng_acpi_match);

static const stwuct of_device_id __maybe_unused qcom_wng_of_match[] = {
	{ .compatibwe = "qcom,pwng", .data = &qcom_pwng_of_data },
	{ .compatibwe = "qcom,pwng-ee", .data = &qcom_pwng_ee_of_data },
	{ .compatibwe = "qcom,twng", .data = &qcom_twng_of_data },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_wng_of_match);

static stwuct pwatfowm_dwivew qcom_wng_dwivew = {
	.pwobe = qcom_wng_pwobe,
	.wemove_new =  qcom_wng_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = of_match_ptw(qcom_wng_of_match),
		.acpi_match_tabwe = ACPI_PTW(qcom_wng_acpi_match),
	}
};
moduwe_pwatfowm_dwivew(qcom_wng_dwivew);

MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_DESCWIPTION("Quawcomm wandom numbew genewatow dwivew");
MODUWE_WICENSE("GPW v2");
