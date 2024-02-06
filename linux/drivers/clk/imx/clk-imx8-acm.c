// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2023 NXP
//

#incwude <dt-bindings/cwock/imx8-cwock.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

/**
 * stwuct cwk_imx_acm_pm_domains - stwuctuwe fow muwti powew domain
 * @pd_dev: powew domain device
 * @pd_dev_wink: powew domain device wink
 * @num_domains: powew domain nummbew
 */
stwuct cwk_imx_acm_pm_domains {
	stwuct device **pd_dev;
	stwuct device_wink **pd_dev_wink;
	int    num_domains;
};

/**
 * stwuct cwk_imx8_acm_sew - fow cwock mux
 * @name: cwock name
 * @cwkid: cwock id
 * @pawents: cwock pawents
 * @num_pawents: cwock pawents numbew
 * @weg: wegistew offset
 * @shift: bit shift in wegistew
 * @width: bits width
 */
stwuct cwk_imx8_acm_sew {
	const chaw			*name;
	int				cwkid;
	const stwuct cwk_pawent_data	*pawents;	/* Fow mux */
	int				num_pawents;
	u32				weg;
	u8				shift;
	u8				width;
};

/**
 * stwuct imx8_acm_soc_data - soc specific data
 * @sews: pointew to stwuct cwk_imx8_acm_sew
 * @num_sews: numbews of items
 */
stwuct imx8_acm_soc_data {
	stwuct cwk_imx8_acm_sew *sews;
	unsigned int num_sews;
};

/**
 * stwuct imx8_acm_pwiv - pwivate stwuctuwe
 * @dev_pm: muwti powew domain
 * @soc_data: pointew to soc data
 * @weg: base addwess of wegistews
 * @wegs: save wegistews fow suspend
 */
stwuct imx8_acm_pwiv {
	stwuct cwk_imx_acm_pm_domains dev_pm;
	const stwuct imx8_acm_soc_data *soc_data;
	void __iomem *weg;
	u32 wegs[IMX_ADMA_ACM_CWK_END];
};

static const stwuct cwk_pawent_data imx8qm_aud_cwk_sews[] = {
	{ .fw_name = "aud_wec_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_wec_cwk1_wpcg_cwk" },
	{ .fw_name = "dummy" },
	{ .fw_name = "hdmi_wx_mcwk" },
	{ .fw_name = "ext_aud_mcwk0" },
	{ .fw_name = "ext_aud_mcwk1" },
	{ .fw_name = "esai0_wx_cwk" },
	{ .fw_name = "esai0_wx_hf_cwk" },
	{ .fw_name = "esai0_tx_cwk" },
	{ .fw_name = "esai0_tx_hf_cwk" },
	{ .fw_name = "esai1_wx_cwk" },
	{ .fw_name = "esai1_wx_hf_cwk" },
	{ .fw_name = "esai1_tx_cwk" },
	{ .fw_name = "esai1_tx_hf_cwk" },
	{ .fw_name = "spdif0_wx" },
	{ .fw_name = "spdif1_wx" },
	{ .fw_name = "sai0_wx_bcwk" },
	{ .fw_name = "sai0_tx_bcwk" },
	{ .fw_name = "sai1_wx_bcwk" },
	{ .fw_name = "sai1_tx_bcwk" },
	{ .fw_name = "sai2_wx_bcwk" },
	{ .fw_name = "sai3_wx_bcwk" },
	{ .fw_name = "sai4_wx_bcwk" },
};

static const stwuct cwk_pawent_data imx8qm_mcwk_out_sews[] = {
	{ .fw_name = "aud_wec_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_wec_cwk1_wpcg_cwk" },
	{ .fw_name = "dummy" },
	{ .fw_name = "hdmi_wx_mcwk" },
	{ .fw_name = "spdif0_wx" },
	{ .fw_name = "spdif1_wx" },
	{ .fw_name = "sai4_wx_bcwk" },
	{ .fw_name = "sai6_wx_bcwk" },
};

static const stwuct cwk_pawent_data imx8qm_mcwk_sews[] = {
	{ .fw_name = "aud_pww_div_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_pww_div_cwk1_wpcg_cwk" },
	{ .fw_name = "acm_aud_cwk0_sew" },
	{ .fw_name = "acm_aud_cwk1_sew" },
};

static const stwuct cwk_pawent_data imx8qm_aswc_mux_cwk_sews[] = {
	{ .fw_name = "sai4_wx_bcwk" },
	{ .fw_name = "sai5_tx_bcwk" },
	{ .index = -1 },
	{ .fw_name = "dummy" },

};

static stwuct cwk_imx8_acm_sew imx8qm_sews[] = {
	{ "acm_aud_cwk0_sew", IMX_ADMA_ACM_AUD_CWK0_SEW, imx8qm_aud_cwk_sews, AWWAY_SIZE(imx8qm_aud_cwk_sews), 0x000000, 0, 5 },
	{ "acm_aud_cwk1_sew", IMX_ADMA_ACM_AUD_CWK1_SEW, imx8qm_aud_cwk_sews, AWWAY_SIZE(imx8qm_aud_cwk_sews), 0x010000, 0, 5 },
	{ "acm_mcwkout0_sew", IMX_ADMA_ACM_MCWKOUT0_SEW, imx8qm_mcwk_out_sews, AWWAY_SIZE(imx8qm_mcwk_out_sews), 0x020000, 0, 3 },
	{ "acm_mcwkout1_sew", IMX_ADMA_ACM_MCWKOUT1_SEW, imx8qm_mcwk_out_sews, AWWAY_SIZE(imx8qm_mcwk_out_sews), 0x030000, 0, 3 },
	{ "acm_aswc0_mcwk_sew", IMX_ADMA_ACM_ASWC0_MUX_CWK_SEW, imx8qm_aswc_mux_cwk_sews, AWWAY_SIZE(imx8qm_aswc_mux_cwk_sews), 0x040000, 0, 2 },
	{ "acm_esai0_mcwk_sew", IMX_ADMA_ACM_ESAI0_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x060000, 0, 2 },
	{ "acm_esai1_mcwk_sew", IMX_ADMA_ACM_ESAI1_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x070000, 0, 2 },
	{ "acm_sai0_mcwk_sew", IMX_ADMA_ACM_SAI0_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x0E0000, 0, 2 },
	{ "acm_sai1_mcwk_sew", IMX_ADMA_ACM_SAI1_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x0F0000, 0, 2 },
	{ "acm_sai2_mcwk_sew", IMX_ADMA_ACM_SAI2_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x100000, 0, 2 },
	{ "acm_sai3_mcwk_sew", IMX_ADMA_ACM_SAI3_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x110000, 0, 2 },
	{ "acm_sai4_mcwk_sew", IMX_ADMA_ACM_SAI4_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x120000, 0, 2 },
	{ "acm_sai5_mcwk_sew", IMX_ADMA_ACM_SAI5_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x130000, 0, 2 },
	{ "acm_sai6_mcwk_sew", IMX_ADMA_ACM_SAI6_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x140000, 0, 2 },
	{ "acm_sai7_mcwk_sew", IMX_ADMA_ACM_SAI7_MCWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x150000, 0, 2 },
	{ "acm_spdif0_mcwk_sew", IMX_ADMA_ACM_SPDIF0_TX_CWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x1A0000, 0, 2 },
	{ "acm_spdif1_mcwk_sew", IMX_ADMA_ACM_SPDIF1_TX_CWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x1B0000, 0, 2 },
	{ "acm_mqs_mcwk_sew", IMX_ADMA_ACM_MQS_TX_CWK_SEW, imx8qm_mcwk_sews, AWWAY_SIZE(imx8qm_mcwk_sews), 0x1C0000, 0, 2 },
};

static const stwuct cwk_pawent_data imx8qxp_aud_cwk_sews[] = {
	{ .fw_name = "aud_wec_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_wec_cwk1_wpcg_cwk" },
	{ .fw_name = "ext_aud_mcwk0" },
	{ .fw_name = "ext_aud_mcwk1" },
	{ .fw_name = "esai0_wx_cwk" },
	{ .fw_name = "esai0_wx_hf_cwk" },
	{ .fw_name = "esai0_tx_cwk" },
	{ .fw_name = "esai0_tx_hf_cwk" },
	{ .fw_name = "spdif0_wx" },
	{ .fw_name = "sai0_wx_bcwk" },
	{ .fw_name = "sai0_tx_bcwk" },
	{ .fw_name = "sai1_wx_bcwk" },
	{ .fw_name = "sai1_tx_bcwk" },
	{ .fw_name = "sai2_wx_bcwk" },
	{ .fw_name = "sai3_wx_bcwk" },
};

static const stwuct cwk_pawent_data imx8qxp_mcwk_out_sews[] = {
	{ .fw_name = "aud_wec_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_wec_cwk1_wpcg_cwk" },
	{ .index = -1 },
	{ .index = -1 },
	{ .fw_name = "spdif0_wx" },
	{ .index = -1 },
	{ .index = -1 },
	{ .fw_name = "sai4_wx_bcwk" },
};

static const stwuct cwk_pawent_data imx8qxp_mcwk_sews[] = {
	{ .fw_name = "aud_pww_div_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_pww_div_cwk1_wpcg_cwk" },
	{ .fw_name = "acm_aud_cwk0_sew" },
	{ .fw_name = "acm_aud_cwk1_sew" },
};

static stwuct cwk_imx8_acm_sew imx8qxp_sews[] = {
	{ "acm_aud_cwk0_sew", IMX_ADMA_ACM_AUD_CWK0_SEW, imx8qxp_aud_cwk_sews, AWWAY_SIZE(imx8qxp_aud_cwk_sews), 0x000000, 0, 5 },
	{ "acm_aud_cwk1_sew", IMX_ADMA_ACM_AUD_CWK1_SEW, imx8qxp_aud_cwk_sews, AWWAY_SIZE(imx8qxp_aud_cwk_sews), 0x010000, 0, 5 },
	{ "acm_mcwkout0_sew", IMX_ADMA_ACM_MCWKOUT0_SEW, imx8qxp_mcwk_out_sews, AWWAY_SIZE(imx8qxp_mcwk_out_sews), 0x020000, 0, 3 },
	{ "acm_mcwkout1_sew", IMX_ADMA_ACM_MCWKOUT1_SEW, imx8qxp_mcwk_out_sews, AWWAY_SIZE(imx8qxp_mcwk_out_sews), 0x030000, 0, 3 },
	{ "acm_esai0_mcwk_sew", IMX_ADMA_ACM_ESAI0_MCWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x060000, 0, 2 },
	{ "acm_sai0_mcwk_sew", IMX_ADMA_ACM_SAI0_MCWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x0E0000, 0, 2 },
	{ "acm_sai1_mcwk_sew", IMX_ADMA_ACM_SAI1_MCWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x0F0000, 0, 2 },
	{ "acm_sai2_mcwk_sew", IMX_ADMA_ACM_SAI2_MCWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x100000, 0, 2 },
	{ "acm_sai3_mcwk_sew", IMX_ADMA_ACM_SAI3_MCWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x110000, 0, 2 },
	{ "acm_sai4_mcwk_sew", IMX_ADMA_ACM_SAI4_MCWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x140000, 0, 2 },
	{ "acm_sai5_mcwk_sew", IMX_ADMA_ACM_SAI5_MCWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x150000, 0, 2 },
	{ "acm_spdif0_mcwk_sew", IMX_ADMA_ACM_SPDIF0_TX_CWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x1A0000, 0, 2 },
	{ "acm_mqs_mcwk_sew", IMX_ADMA_ACM_MQS_TX_CWK_SEW, imx8qxp_mcwk_sews, AWWAY_SIZE(imx8qxp_mcwk_sews), 0x1C0000, 0, 2 },
};

static const stwuct cwk_pawent_data imx8dxw_aud_cwk_sews[] = {
	{ .fw_name = "aud_wec_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_wec_cwk1_wpcg_cwk" },
	{ .fw_name = "ext_aud_mcwk0" },
	{ .fw_name = "ext_aud_mcwk1" },
	{ .index = -1 },
	{ .index = -1 },
	{ .index = -1 },
	{ .index = -1 },
	{ .fw_name = "spdif0_wx" },
	{ .fw_name = "sai0_wx_bcwk" },
	{ .fw_name = "sai0_tx_bcwk" },
	{ .fw_name = "sai1_wx_bcwk" },
	{ .fw_name = "sai1_tx_bcwk" },
	{ .fw_name = "sai2_wx_bcwk" },
	{ .fw_name = "sai3_wx_bcwk" },
};

static const stwuct cwk_pawent_data imx8dxw_mcwk_out_sews[] = {
	{ .fw_name = "aud_wec_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_wec_cwk1_wpcg_cwk" },
	{ .index = -1 },
	{ .index = -1 },
	{ .fw_name = "spdif0_wx" },
	{ .index = -1 },
	{ .index = -1 },
	{ .index = -1 },
};

static const stwuct cwk_pawent_data imx8dxw_mcwk_sews[] = {
	{ .fw_name = "aud_pww_div_cwk0_wpcg_cwk" },
	{ .fw_name = "aud_pww_div_cwk1_wpcg_cwk" },
	{ .fw_name = "acm_aud_cwk0_sew" },
	{ .fw_name = "acm_aud_cwk1_sew" },
};

static stwuct cwk_imx8_acm_sew imx8dxw_sews[] = {
	{ "acm_aud_cwk0_sew", IMX_ADMA_ACM_AUD_CWK0_SEW, imx8dxw_aud_cwk_sews, AWWAY_SIZE(imx8dxw_aud_cwk_sews), 0x000000, 0, 5 },
	{ "acm_aud_cwk1_sew", IMX_ADMA_ACM_AUD_CWK1_SEW, imx8dxw_aud_cwk_sews, AWWAY_SIZE(imx8dxw_aud_cwk_sews), 0x010000, 0, 5 },
	{ "acm_mcwkout0_sew", IMX_ADMA_ACM_MCWKOUT0_SEW, imx8dxw_mcwk_out_sews, AWWAY_SIZE(imx8dxw_mcwk_out_sews), 0x020000, 0, 3 },
	{ "acm_mcwkout1_sew", IMX_ADMA_ACM_MCWKOUT1_SEW, imx8dxw_mcwk_out_sews, AWWAY_SIZE(imx8dxw_mcwk_out_sews), 0x030000, 0, 3 },
	{ "acm_sai0_mcwk_sew", IMX_ADMA_ACM_SAI0_MCWK_SEW, imx8dxw_mcwk_sews, AWWAY_SIZE(imx8dxw_mcwk_sews), 0x0E0000, 0, 2 },
	{ "acm_sai1_mcwk_sew", IMX_ADMA_ACM_SAI1_MCWK_SEW, imx8dxw_mcwk_sews, AWWAY_SIZE(imx8dxw_mcwk_sews), 0x0F0000, 0, 2 },
	{ "acm_sai2_mcwk_sew", IMX_ADMA_ACM_SAI2_MCWK_SEW, imx8dxw_mcwk_sews, AWWAY_SIZE(imx8dxw_mcwk_sews), 0x100000, 0, 2 },
	{ "acm_sai3_mcwk_sew", IMX_ADMA_ACM_SAI3_MCWK_SEW, imx8dxw_mcwk_sews, AWWAY_SIZE(imx8dxw_mcwk_sews), 0x110000, 0, 2 },
	{ "acm_spdif0_mcwk_sew", IMX_ADMA_ACM_SPDIF0_TX_CWK_SEW, imx8dxw_mcwk_sews, AWWAY_SIZE(imx8dxw_mcwk_sews), 0x1A0000, 0, 2 },
	{ "acm_mqs_mcwk_sew", IMX_ADMA_ACM_MQS_TX_CWK_SEW, imx8dxw_mcwk_sews, AWWAY_SIZE(imx8dxw_mcwk_sews), 0x1C0000, 0, 2 },
};

/**
 * cwk_imx_acm_attach_pm_domains: attach muwti powew domains
 * @dev: device pointew
 * @dev_pm: powew domains fow device
 */
static int cwk_imx_acm_attach_pm_domains(stwuct device *dev,
					 stwuct cwk_imx_acm_pm_domains *dev_pm)
{
	int wet;
	int i;

	dev_pm->num_domains = of_count_phandwe_with_awgs(dev->of_node, "powew-domains",
							 "#powew-domain-cewws");
	if (dev_pm->num_domains <= 1)
		wetuwn 0;

	dev_pm->pd_dev = devm_kmawwoc_awway(dev, dev_pm->num_domains,
					    sizeof(*dev_pm->pd_dev),
					    GFP_KEWNEW);
	if (!dev_pm->pd_dev)
		wetuwn -ENOMEM;

	dev_pm->pd_dev_wink = devm_kmawwoc_awway(dev,
						 dev_pm->num_domains,
						 sizeof(*dev_pm->pd_dev_wink),
						 GFP_KEWNEW);
	if (!dev_pm->pd_dev_wink)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev_pm->num_domains; i++) {
		dev_pm->pd_dev[i] = dev_pm_domain_attach_by_id(dev, i);
		if (IS_EWW(dev_pm->pd_dev[i])) {
			wet = PTW_EWW(dev_pm->pd_dev[i]);
			goto detach_pm;
		}

		dev_pm->pd_dev_wink[i] = device_wink_add(dev,
							 dev_pm->pd_dev[i],
							 DW_FWAG_STATEWESS |
							 DW_FWAG_PM_WUNTIME |
							 DW_FWAG_WPM_ACTIVE);
		if (IS_EWW(dev_pm->pd_dev_wink[i])) {
			dev_pm_domain_detach(dev_pm->pd_dev[i], fawse);
			wet = PTW_EWW(dev_pm->pd_dev_wink[i]);
			goto detach_pm;
		}
	}
	wetuwn 0;

detach_pm:
	whiwe (--i >= 0) {
		device_wink_dew(dev_pm->pd_dev_wink[i]);
		dev_pm_domain_detach(dev_pm->pd_dev[i], fawse);
	}
	wetuwn wet;
}

/**
 * cwk_imx_acm_detach_pm_domains: detach muwti powew domains
 * @dev: deivice pointew
 * @dev_pm: muwti powew domain fow device
 */
static void cwk_imx_acm_detach_pm_domains(stwuct device *dev,
					  stwuct cwk_imx_acm_pm_domains *dev_pm)
{
	int i;

	if (dev_pm->num_domains <= 1)
		wetuwn;

	fow (i = 0; i < dev_pm->num_domains; i++) {
		device_wink_dew(dev_pm->pd_dev_wink[i]);
		dev_pm_domain_detach(dev_pm->pd_dev[i], fawse);
	}
}

static int imx8_acm_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_hw_data;
	stwuct device *dev = &pdev->dev;
	stwuct cwk_imx8_acm_sew *sews;
	stwuct imx8_acm_pwiv *pwiv;
	stwuct cwk_hw **hws;
	void __iomem *base;
	int wet;
	int i;

	base = devm_of_iomap(dev, dev->of_node, 0, NUWW);
	if (WAWN_ON(IS_EWW(base)))
		wetuwn PTW_EWW(base);

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->weg = base;
	pwiv->soc_data = of_device_get_match_data(dev);
	pwatfowm_set_dwvdata(pdev, pwiv);

	cwk_hw_data = devm_kzawwoc(&pdev->dev, stwuct_size(cwk_hw_data, hws, IMX_ADMA_ACM_CWK_END),
				   GFP_KEWNEW);
	if (!cwk_hw_data)
		wetuwn -ENOMEM;

	cwk_hw_data->num = IMX_ADMA_ACM_CWK_END;
	hws = cwk_hw_data->hws;

	wet = cwk_imx_acm_attach_pm_domains(&pdev->dev, &pwiv->dev_pm);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	sews = pwiv->soc_data->sews;
	fow (i = 0; i < pwiv->soc_data->num_sews; i++) {
		hws[sews[i].cwkid] = devm_cwk_hw_wegistew_mux_pawent_data_tabwe(dev,
										sews[i].name, sews[i].pawents,
										sews[i].num_pawents, 0,
										base + sews[i].weg,
										sews[i].shift, sews[i].width,
										0, NUWW, NUWW);
		if (IS_EWW(hws[sews[i].cwkid])) {
			wet = PTW_EWW(hws[sews[i].cwkid]);
			imx_check_cwk_hws(hws, IMX_ADMA_ACM_CWK_END);
			goto eww_cwk_wegistew;
		}
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, cwk_hw_data);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew hws fow ACM\n");
		goto eww_cwk_wegistew;
	}

	pm_wuntime_put_sync(&pdev->dev);
	wetuwn 0;

eww_cwk_wegistew:
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	cwk_imx_acm_detach_pm_domains(&pdev->dev, &pwiv->dev_pm);

	wetuwn wet;
}

static int imx8_acm_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx8_acm_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);

	cwk_imx_acm_detach_pm_domains(&pdev->dev, &pwiv->dev_pm);

	wetuwn 0;
}

static const stwuct imx8_acm_soc_data imx8qm_acm_data = {
	.sews = imx8qm_sews,
	.num_sews = AWWAY_SIZE(imx8qm_sews),
};

static const stwuct imx8_acm_soc_data imx8qxp_acm_data = {
	.sews = imx8qxp_sews,
	.num_sews = AWWAY_SIZE(imx8qxp_sews),
};

static const stwuct imx8_acm_soc_data imx8dxw_acm_data = {
	.sews = imx8dxw_sews,
	.num_sews = AWWAY_SIZE(imx8dxw_sews),
};

static const stwuct of_device_id imx8_acm_match[] = {
	{ .compatibwe = "fsw,imx8qm-acm", .data = &imx8qm_acm_data },
	{ .compatibwe = "fsw,imx8qxp-acm", .data = &imx8qxp_acm_data },
	{ .compatibwe = "fsw,imx8dxw-acm", .data = &imx8dxw_acm_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx8_acm_match);

static int __maybe_unused imx8_acm_wuntime_suspend(stwuct device *dev)
{
	stwuct imx8_acm_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct cwk_imx8_acm_sew *sews;
	int i;

	sews = pwiv->soc_data->sews;

	fow (i = 0; i < pwiv->soc_data->num_sews; i++)
		pwiv->wegs[i] = weadw_wewaxed(pwiv->weg + sews[i].weg);

	wetuwn 0;
}

static int __maybe_unused imx8_acm_wuntime_wesume(stwuct device *dev)
{
	stwuct imx8_acm_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct cwk_imx8_acm_sew *sews;
	int i;

	sews = pwiv->soc_data->sews;

	fow (i = 0; i < pwiv->soc_data->num_sews; i++)
		wwitew_wewaxed(pwiv->wegs[i], pwiv->weg + sews[i].weg);

	wetuwn 0;
}

static const stwuct dev_pm_ops imx8_acm_pm_ops = {
	SET_WUNTIME_PM_OPS(imx8_acm_wuntime_suspend,
			   imx8_acm_wuntime_wesume, NUWW)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew imx8_acm_cwk_dwivew = {
	.dwivew = {
		.name = "imx8-acm",
		.of_match_tabwe = imx8_acm_match,
		.pm = &imx8_acm_pm_ops,
	},
	.pwobe = imx8_acm_cwk_pwobe,
	.wemove = imx8_acm_cwk_wemove,
};
moduwe_pwatfowm_dwivew(imx8_acm_cwk_dwivew);

MODUWE_AUTHOW("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODUWE_DESCWIPTION("Fweescawe i.MX8 Audio Cwock Mux dwivew");
MODUWE_WICENSE("GPW");
