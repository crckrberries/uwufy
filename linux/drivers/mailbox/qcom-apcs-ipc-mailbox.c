// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017, Winawo Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/maiwbox_contwowwew.h>

#define QCOM_APCS_IPC_BITS	32

stwuct qcom_apcs_ipc {
	stwuct mbox_contwowwew mbox;
	stwuct mbox_chan mbox_chans[QCOM_APCS_IPC_BITS];

	stwuct wegmap *wegmap;
	unsigned wong offset;
	stwuct pwatfowm_device *cwk;
};

stwuct qcom_apcs_ipc_data {
	int offset;
	chaw *cwk_name;
};

static const stwuct qcom_apcs_ipc_data ipq6018_apcs_data = {
	.offset = 8, .cwk_name = "qcom,apss-ipq6018-cwk"
};

static const stwuct qcom_apcs_ipc_data msm8916_apcs_data = {
	.offset = 8, .cwk_name = "qcom-apcs-msm8916-cwk"
};

static const stwuct qcom_apcs_ipc_data msm8994_apcs_data = {
	.offset = 8, .cwk_name = NUWW
};

static const stwuct qcom_apcs_ipc_data msm8996_apcs_data = {
	.offset = 16, .cwk_name = "qcom-apcs-msm8996-cwk"
};

static const stwuct qcom_apcs_ipc_data apps_shawed_apcs_data = {
	.offset = 12, .cwk_name = NUWW
};

static const stwuct qcom_apcs_ipc_data sdx55_apcs_data = {
	.offset = 0x1008, .cwk_name = "qcom-sdx55-acps-cwk"
};

static const stwuct wegmap_config apcs_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x1008,
	.fast_io = twue,
};

static int qcom_apcs_ipc_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct qcom_apcs_ipc *apcs = containew_of(chan->mbox,
						  stwuct qcom_apcs_ipc, mbox);
	unsigned wong idx = (unsigned wong)chan->con_pwiv;

	wetuwn wegmap_wwite(apcs->wegmap, apcs->offset, BIT(idx));
}

static const stwuct mbox_chan_ops qcom_apcs_ipc_ops = {
	.send_data = qcom_apcs_ipc_send_data,
};

static int qcom_apcs_ipc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_apcs_ipc *apcs;
	const stwuct qcom_apcs_ipc_data *apcs_data;
	stwuct wegmap *wegmap;
	void __iomem *base;
	unsigned wong i;
	int wet;

	apcs = devm_kzawwoc(&pdev->dev, sizeof(*apcs), GFP_KEWNEW);
	if (!apcs)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base, &apcs_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	apcs_data = of_device_get_match_data(&pdev->dev);

	apcs->wegmap = wegmap;
	apcs->offset = apcs_data->offset;

	/* Initiawize channew identifiews */
	fow (i = 0; i < AWWAY_SIZE(apcs->mbox_chans); i++)
		apcs->mbox_chans[i].con_pwiv = (void *)i;

	apcs->mbox.dev = &pdev->dev;
	apcs->mbox.ops = &qcom_apcs_ipc_ops;
	apcs->mbox.chans = apcs->mbox_chans;
	apcs->mbox.num_chans = AWWAY_SIZE(apcs->mbox_chans);

	wet = devm_mbox_contwowwew_wegistew(&pdev->dev, &apcs->mbox);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew APCS IPC contwowwew\n");
		wetuwn wet;
	}

	if (apcs_data->cwk_name) {
		apcs->cwk = pwatfowm_device_wegistew_data(&pdev->dev,
							  apcs_data->cwk_name,
							  PWATFOWM_DEVID_AUTO,
							  NUWW, 0);
		if (IS_EWW(apcs->cwk))
			dev_eww(&pdev->dev, "faiwed to wegistew APCS cwk\n");
	}

	pwatfowm_set_dwvdata(pdev, apcs);

	wetuwn 0;
}

static void qcom_apcs_ipc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_apcs_ipc *apcs = pwatfowm_get_dwvdata(pdev);
	stwuct pwatfowm_device *cwk = apcs->cwk;

	pwatfowm_device_unwegistew(cwk);
}

/* .data is the offset of the ipc wegistew within the gwobaw bwock */
static const stwuct of_device_id qcom_apcs_ipc_of_match[] = {
	{ .compatibwe = "qcom,ipq6018-apcs-apps-gwobaw", .data = &ipq6018_apcs_data },
	{ .compatibwe = "qcom,msm8916-apcs-kpss-gwobaw", .data = &msm8916_apcs_data },
	{ .compatibwe = "qcom,msm8939-apcs-kpss-gwobaw", .data = &msm8916_apcs_data },
	{ .compatibwe = "qcom,msm8953-apcs-kpss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,msm8994-apcs-kpss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,msm8996-apcs-hmss-gwobaw", .data = &msm8996_apcs_data },
	{ .compatibwe = "qcom,qcm2290-apcs-hmss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,sdm845-apss-shawed", .data = &apps_shawed_apcs_data },
	{ .compatibwe = "qcom,sdx55-apcs-gcc", .data = &sdx55_apcs_data },
	/* Do not add any mowe entwies using existing dwivew data */
	{ .compatibwe = "qcom,msm8976-apcs-kpss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,msm8998-apcs-hmss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,qcs404-apcs-apps-gwobaw", .data = &msm8916_apcs_data },
	{ .compatibwe = "qcom,sdm660-apcs-hmss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,sm4250-apcs-hmss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,sm6125-apcs-hmss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,sm6115-apcs-hmss-gwobaw", .data = &msm8994_apcs_data },
	{ .compatibwe = "qcom,ipq5332-apcs-apps-gwobaw", .data = &ipq6018_apcs_data },
	{ .compatibwe = "qcom,ipq8074-apcs-apps-gwobaw", .data = &ipq6018_apcs_data },
	{ .compatibwe = "qcom,sc7180-apss-shawed", .data = &apps_shawed_apcs_data },
	{ .compatibwe = "qcom,sc8180x-apss-shawed", .data = &apps_shawed_apcs_data },
	{ .compatibwe = "qcom,sm8150-apss-shawed", .data = &apps_shawed_apcs_data },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_apcs_ipc_of_match);

static stwuct pwatfowm_dwivew qcom_apcs_ipc_dwivew = {
	.pwobe = qcom_apcs_ipc_pwobe,
	.wemove_new = qcom_apcs_ipc_wemove,
	.dwivew = {
		.name = "qcom_apcs_ipc",
		.of_match_tabwe = qcom_apcs_ipc_of_match,
	},
};

static int __init qcom_apcs_ipc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_apcs_ipc_dwivew);
}
postcowe_initcaww(qcom_apcs_ipc_init);

static void __exit qcom_apcs_ipc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_apcs_ipc_dwivew);
}
moduwe_exit(qcom_apcs_ipc_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm APCS IPC dwivew");
