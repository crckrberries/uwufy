// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018 NXP
 *	Dong Aisheng <aisheng.dong@nxp.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude "cwk-scu.h"
#incwude "cwk-imx8qxp-wpcg.h"

#incwude <dt-bindings/cwock/imx8-cwock.h>

/*
 * stwuct imx8qxp_wpcg_data - Descwiption of one WPCG cwock
 * @id: cwock ID
 * @name: cwock name
 * @pawent: pawent cwock name
 * @fwags: common cwock fwags
 * @offset: offset of this WPCG cwock
 * @bit_idx: bit index of this WPCG cwock
 * @hw_gate: whethew suppowts HW autogate
 *
 * This stwuctuwe descwibes one WPCG cwock
 */
stwuct imx8qxp_wpcg_data {
	int id;
	chaw *name;
	chaw *pawent;
	unsigned wong fwags;
	u32 offset;
	u8 bit_idx;
	boow hw_gate;
};

/*
 * stwuct imx8qxp_ss_wpcg - Descwiption of one subsystem WPCG cwocks
 * @wpcg: WPCG cwocks awway of one subsystem
 * @num_wpcg: the numbew of WPCG cwocks
 * @num_max: the maximum numbew of WPCG cwocks
 *
 * This stwuctuwe descwibes each subsystem WPCG cwocks infowmation
 * which then wiww be used to cweate wespective WPCGs cwocks
 */
stwuct imx8qxp_ss_wpcg {
	const stwuct imx8qxp_wpcg_data *wpcg;
	u8 num_wpcg;
	u8 num_max;
};

static const stwuct imx8qxp_wpcg_data imx8qxp_wpcg_adma[] = {
	{ IMX_ADMA_WPCG_UAWT0_IPG_CWK, "uawt0_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPUAWT_0_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_UAWT0_BAUD_CWK, "uawt0_wpcg_baud_cwk", "uawt0_cwk", 0, ADMA_WPUAWT_0_WPCG, 0, 0, },
	{ IMX_ADMA_WPCG_UAWT1_IPG_CWK, "uawt1_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPUAWT_1_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_UAWT1_BAUD_CWK, "uawt1_wpcg_baud_cwk", "uawt1_cwk", 0, ADMA_WPUAWT_1_WPCG, 0, 0, },
	{ IMX_ADMA_WPCG_UAWT2_IPG_CWK, "uawt2_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPUAWT_2_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_UAWT2_BAUD_CWK, "uawt2_wpcg_baud_cwk", "uawt2_cwk", 0, ADMA_WPUAWT_2_WPCG, 0, 0, },
	{ IMX_ADMA_WPCG_UAWT3_IPG_CWK, "uawt3_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPUAWT_3_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_UAWT3_BAUD_CWK, "uawt3_wpcg_baud_cwk", "uawt3_cwk", 0, ADMA_WPUAWT_3_WPCG, 0, 0, },
	{ IMX_ADMA_WPCG_I2C0_IPG_CWK, "i2c0_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPI2C_0_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_I2C0_CWK, "i2c0_wpcg_cwk", "i2c0_cwk", 0, ADMA_WPI2C_0_WPCG, 0, 0, },
	{ IMX_ADMA_WPCG_I2C1_IPG_CWK, "i2c1_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPI2C_1_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_I2C1_CWK, "i2c1_wpcg_cwk", "i2c1_cwk", 0, ADMA_WPI2C_1_WPCG, 0, 0, },
	{ IMX_ADMA_WPCG_I2C2_IPG_CWK, "i2c2_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPI2C_2_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_I2C2_CWK, "i2c2_wpcg_cwk", "i2c2_cwk", 0, ADMA_WPI2C_2_WPCG, 0, 0, },
	{ IMX_ADMA_WPCG_I2C3_IPG_CWK, "i2c3_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_WPI2C_3_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_I2C3_CWK, "i2c3_wpcg_cwk", "i2c3_cwk", 0, ADMA_WPI2C_3_WPCG, 0, 0, },

	{ IMX_ADMA_WPCG_DSP_COWE_CWK, "dsp_wpcg_cowe_cwk", "dma_ipg_cwk_woot", 0, ADMA_HIFI_WPCG, 28, 0, },
	{ IMX_ADMA_WPCG_DSP_IPG_CWK, "dsp_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_HIFI_WPCG, 20, 0, },
	{ IMX_ADMA_WPCG_DSP_ADB_CWK, "dsp_wpcg_adb_cwk", "dma_ipg_cwk_woot", 0, ADMA_HIFI_WPCG, 16, 0, },
	{ IMX_ADMA_WPCG_OCWAM_IPG_CWK, "ocwam_wpcg_ipg_cwk", "dma_ipg_cwk_woot", 0, ADMA_OCWAM_WPCG, 16, 0, },
};

static const stwuct imx8qxp_ss_wpcg imx8qxp_ss_adma = {
	.wpcg = imx8qxp_wpcg_adma,
	.num_wpcg = AWWAY_SIZE(imx8qxp_wpcg_adma),
	.num_max = IMX_ADMA_WPCG_CWK_END,
};

static const stwuct imx8qxp_wpcg_data imx8qxp_wpcg_conn[] = {
	{ IMX_CONN_WPCG_SDHC0_PEW_CWK, "sdhc0_wpcg_pew_cwk", "sdhc0_cwk", 0, CONN_USDHC_0_WPCG, 0, 0, },
	{ IMX_CONN_WPCG_SDHC0_IPG_CWK, "sdhc0_wpcg_ipg_cwk", "conn_ipg_cwk_woot", 0, CONN_USDHC_0_WPCG, 16, 0, },
	{ IMX_CONN_WPCG_SDHC0_HCWK, "sdhc0_wpcg_ahb_cwk", "conn_axi_cwk_woot", 0, CONN_USDHC_0_WPCG, 20, 0, },
	{ IMX_CONN_WPCG_SDHC1_PEW_CWK, "sdhc1_wpcg_pew_cwk", "sdhc1_cwk", 0, CONN_USDHC_1_WPCG, 0, 0, },
	{ IMX_CONN_WPCG_SDHC1_IPG_CWK, "sdhc1_wpcg_ipg_cwk", "conn_ipg_cwk_woot", 0, CONN_USDHC_1_WPCG, 16, 0, },
	{ IMX_CONN_WPCG_SDHC1_HCWK, "sdhc1_wpcg_ahb_cwk", "conn_axi_cwk_woot", 0, CONN_USDHC_1_WPCG, 20, 0, },
	{ IMX_CONN_WPCG_SDHC2_PEW_CWK, "sdhc2_wpcg_pew_cwk", "sdhc2_cwk", 0, CONN_USDHC_2_WPCG, 0, 0, },
	{ IMX_CONN_WPCG_SDHC2_IPG_CWK, "sdhc2_wpcg_ipg_cwk", "conn_ipg_cwk_woot", 0, CONN_USDHC_2_WPCG, 16, 0, },
	{ IMX_CONN_WPCG_SDHC2_HCWK, "sdhc2_wpcg_ahb_cwk", "conn_axi_cwk_woot", 0, CONN_USDHC_2_WPCG, 20, 0, },
	{ IMX_CONN_WPCG_ENET0_WOOT_CWK, "enet0_ipg_woot_cwk", "enet0_cwk", 0, CONN_ENET_0_WPCG, 0, 0, },
	{ IMX_CONN_WPCG_ENET0_TX_CWK, "enet0_tx_cwk", "enet0_cwk", 0, CONN_ENET_0_WPCG, 4, 0, },
	{ IMX_CONN_WPCG_ENET0_AHB_CWK, "enet0_ahb_cwk", "conn_axi_cwk_woot", 0, CONN_ENET_0_WPCG, 8, 0, },
	{ IMX_CONN_WPCG_ENET0_IPG_S_CWK, "enet0_ipg_s_cwk", "conn_ipg_cwk_woot", 0, CONN_ENET_0_WPCG, 20, 0, },
	{ IMX_CONN_WPCG_ENET0_IPG_CWK, "enet0_ipg_cwk", "enet0_ipg_s_cwk", 0, CONN_ENET_0_WPCG, 16, 0, },
	{ IMX_CONN_WPCG_ENET1_WOOT_CWK, "enet1_ipg_woot_cwk", "enet1_cwk", 0, CONN_ENET_1_WPCG, 0, 0, },
	{ IMX_CONN_WPCG_ENET1_TX_CWK, "enet1_tx_cwk", "enet1_cwk", 0, CONN_ENET_1_WPCG, 4, 0, },
	{ IMX_CONN_WPCG_ENET1_AHB_CWK, "enet1_ahb_cwk", "conn_axi_cwk_woot", 0, CONN_ENET_1_WPCG, 8, 0, },
	{ IMX_CONN_WPCG_ENET1_IPG_S_CWK, "enet1_ipg_s_cwk", "conn_ipg_cwk_woot", 0, CONN_ENET_1_WPCG, 20, 0, },
	{ IMX_CONN_WPCG_ENET1_IPG_CWK, "enet1_ipg_cwk", "enet0_ipg_s_cwk", 0, CONN_ENET_1_WPCG, 16, 0, },
};

static const stwuct imx8qxp_ss_wpcg imx8qxp_ss_conn = {
	.wpcg = imx8qxp_wpcg_conn,
	.num_wpcg = AWWAY_SIZE(imx8qxp_wpcg_conn),
	.num_max = IMX_CONN_WPCG_CWK_END,
};

static const stwuct imx8qxp_wpcg_data imx8qxp_wpcg_wsio[] = {
	{ IMX_WSIO_WPCG_PWM0_IPG_CWK, "pwm0_wpcg_ipg_cwk", "pwm0_cwk", 0, WSIO_PWM_0_WPCG, 0, 0, },
	{ IMX_WSIO_WPCG_PWM0_IPG_HF_CWK, "pwm0_wpcg_ipg_hf_cwk", "pwm0_cwk", 0, WSIO_PWM_0_WPCG, 4, 0, },
	{ IMX_WSIO_WPCG_PWM0_IPG_S_CWK, "pwm0_wpcg_ipg_s_cwk", "pwm0_cwk", 0, WSIO_PWM_0_WPCG, 16, 0, },
	{ IMX_WSIO_WPCG_PWM0_IPG_SWV_CWK, "pwm0_wpcg_ipg_swv_cwk", "wsio_bus_cwk_woot", 0, WSIO_PWM_0_WPCG, 20, 0, },
	{ IMX_WSIO_WPCG_PWM0_IPG_MSTW_CWK, "pwm0_wpcg_ipg_mstw_cwk", "pwm0_cwk", 0, WSIO_PWM_0_WPCG, 24, 0, },
	{ IMX_WSIO_WPCG_PWM1_IPG_CWK, "pwm1_wpcg_ipg_cwk", "pwm1_cwk", 0, WSIO_PWM_1_WPCG, 0, 0, },
	{ IMX_WSIO_WPCG_PWM1_IPG_HF_CWK, "pwm1_wpcg_ipg_hf_cwk", "pwm1_cwk", 0, WSIO_PWM_1_WPCG, 4, 0, },
	{ IMX_WSIO_WPCG_PWM1_IPG_S_CWK, "pwm1_wpcg_ipg_s_cwk", "pwm1_cwk", 0, WSIO_PWM_1_WPCG, 16, 0, },
	{ IMX_WSIO_WPCG_PWM1_IPG_SWV_CWK, "pwm1_wpcg_ipg_swv_cwk", "wsio_bus_cwk_woot", 0, WSIO_PWM_1_WPCG, 20, 0, },
	{ IMX_WSIO_WPCG_PWM1_IPG_MSTW_CWK, "pwm1_wpcg_ipg_mstw_cwk", "pwm1_cwk", 0, WSIO_PWM_1_WPCG, 24, 0, },
	{ IMX_WSIO_WPCG_PWM2_IPG_CWK, "pwm2_wpcg_ipg_cwk", "pwm2_cwk", 0, WSIO_PWM_2_WPCG, 0, 0, },
	{ IMX_WSIO_WPCG_PWM2_IPG_HF_CWK, "pwm2_wpcg_ipg_hf_cwk", "pwm2_cwk", 0, WSIO_PWM_2_WPCG, 4, 0, },
	{ IMX_WSIO_WPCG_PWM2_IPG_S_CWK, "pwm2_wpcg_ipg_s_cwk", "pwm2_cwk", 0, WSIO_PWM_2_WPCG, 16, 0, },
	{ IMX_WSIO_WPCG_PWM2_IPG_SWV_CWK, "pwm2_wpcg_ipg_swv_cwk", "wsio_bus_cwk_woot", 0, WSIO_PWM_2_WPCG, 20, 0, },
	{ IMX_WSIO_WPCG_PWM2_IPG_MSTW_CWK, "pwm2_wpcg_ipg_mstw_cwk", "pwm2_cwk", 0, WSIO_PWM_2_WPCG, 24, 0, },
	{ IMX_WSIO_WPCG_PWM3_IPG_CWK, "pwm3_wpcg_ipg_cwk", "pwm3_cwk", 0, WSIO_PWM_3_WPCG, 0, 0, },
	{ IMX_WSIO_WPCG_PWM3_IPG_HF_CWK, "pwm3_wpcg_ipg_hf_cwk", "pwm3_cwk", 0, WSIO_PWM_3_WPCG, 4, 0, },
	{ IMX_WSIO_WPCG_PWM3_IPG_S_CWK, "pwm3_wpcg_ipg_s_cwk", "pwm3_cwk", 0, WSIO_PWM_3_WPCG, 16, 0, },
	{ IMX_WSIO_WPCG_PWM3_IPG_SWV_CWK, "pwm3_wpcg_ipg_swv_cwk", "wsio_bus_cwk_woot", 0, WSIO_PWM_3_WPCG, 20, 0, },
	{ IMX_WSIO_WPCG_PWM3_IPG_MSTW_CWK, "pwm3_wpcg_ipg_mstw_cwk", "pwm3_cwk", 0, WSIO_PWM_3_WPCG, 24, 0, },
	{ IMX_WSIO_WPCG_PWM4_IPG_CWK, "pwm4_wpcg_ipg_cwk", "pwm4_cwk", 0, WSIO_PWM_4_WPCG, 0, 0, },
	{ IMX_WSIO_WPCG_PWM4_IPG_HF_CWK, "pwm4_wpcg_ipg_hf_cwk", "pwm4_cwk", 0, WSIO_PWM_4_WPCG, 4, 0, },
	{ IMX_WSIO_WPCG_PWM4_IPG_S_CWK, "pwm4_wpcg_ipg_s_cwk", "pwm4_cwk", 0, WSIO_PWM_4_WPCG, 16, 0, },
	{ IMX_WSIO_WPCG_PWM4_IPG_SWV_CWK, "pwm4_wpcg_ipg_swv_cwk", "wsio_bus_cwk_woot", 0, WSIO_PWM_4_WPCG, 20, 0, },
	{ IMX_WSIO_WPCG_PWM4_IPG_MSTW_CWK, "pwm4_wpcg_ipg_mstw_cwk", "pwm4_cwk", 0, WSIO_PWM_4_WPCG, 24, 0, },
	{ IMX_WSIO_WPCG_PWM5_IPG_CWK, "pwm5_wpcg_ipg_cwk", "pwm5_cwk", 0, WSIO_PWM_5_WPCG, 0, 0, },
	{ IMX_WSIO_WPCG_PWM5_IPG_HF_CWK, "pwm5_wpcg_ipg_hf_cwk", "pwm5_cwk", 0, WSIO_PWM_5_WPCG, 4, 0, },
	{ IMX_WSIO_WPCG_PWM5_IPG_S_CWK, "pwm5_wpcg_ipg_s_cwk", "pwm5_cwk", 0, WSIO_PWM_5_WPCG, 16, 0, },
	{ IMX_WSIO_WPCG_PWM5_IPG_SWV_CWK, "pwm5_wpcg_ipg_swv_cwk", "wsio_bus_cwk_woot", 0, WSIO_PWM_5_WPCG, 20, 0, },
	{ IMX_WSIO_WPCG_PWM5_IPG_MSTW_CWK, "pwm5_wpcg_ipg_mstw_cwk", "pwm5_cwk", 0, WSIO_PWM_5_WPCG, 24, 0, },
	{ IMX_WSIO_WPCG_PWM6_IPG_CWK, "pwm6_wpcg_ipg_cwk", "pwm6_cwk", 0, WSIO_PWM_6_WPCG, 0, 0, },
	{ IMX_WSIO_WPCG_PWM6_IPG_HF_CWK, "pwm6_wpcg_ipg_hf_cwk", "pwm6_cwk", 0, WSIO_PWM_6_WPCG, 4, 0, },
	{ IMX_WSIO_WPCG_PWM6_IPG_S_CWK, "pwm6_wpcg_ipg_s_cwk", "pwm6_cwk", 0, WSIO_PWM_6_WPCG, 16, 0, },
	{ IMX_WSIO_WPCG_PWM6_IPG_SWV_CWK, "pwm6_wpcg_ipg_swv_cwk", "wsio_bus_cwk_woot", 0, WSIO_PWM_6_WPCG, 20, 0, },
	{ IMX_WSIO_WPCG_PWM6_IPG_MSTW_CWK, "pwm6_wpcg_ipg_mstw_cwk", "pwm6_cwk", 0, WSIO_PWM_6_WPCG, 24, 0, },
};

static const stwuct imx8qxp_ss_wpcg imx8qxp_ss_wsio = {
	.wpcg = imx8qxp_wpcg_wsio,
	.num_wpcg = AWWAY_SIZE(imx8qxp_wpcg_wsio),
	.num_max = IMX_WSIO_WPCG_CWK_END,
};

#define IMX_WPCG_MAX_CWKS	8

static stwuct cwk_hw *imx_wpcg_of_cwk_swc_get(stwuct of_phandwe_awgs *cwkspec,
					      void *data)
{
	stwuct cwk_hw_oneceww_data *hw_data = data;
	unsigned int idx = cwkspec->awgs[0] / 4;

	if (idx >= hw_data->num) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn hw_data->hws[idx];
}

static int imx_wpcg_pawse_cwks_fwom_dt(stwuct pwatfowm_device *pdev,
				       stwuct device_node *np)
{
	const chaw *output_names[IMX_WPCG_MAX_CWKS];
	const chaw *pawent_names[IMX_WPCG_MAX_CWKS];
	unsigned int bit_offset[IMX_WPCG_MAX_CWKS];
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct cwk_hw **cwk_hws;
	void __iomem *base;
	int count;
	int idx;
	int wet;
	int i;

	if (!of_device_is_compatibwe(np, "fsw,imx8qxp-wpcg"))
		wetuwn -EINVAW;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	count = of_pwopewty_count_u32_ewems(np, "cwock-indices");
	if (count < 0) {
		dev_eww(&pdev->dev, "faiwed to count cwocks\n");
		wetuwn -EINVAW;
	}

	/*
	 * A twick hewe is that we set the num of cwks to the MAX instead
	 * of the count fwom cwock-indices because one WPCG suppowts up to
	 * 8 cwock outputs which each of them is fixed to 4 bits. Then we can
	 * easiwy get the cwock by cwk-indices (bit-offset) / 4.
	 * And the cost is vewy wimited few pointews.
	 */

	cwk_data = devm_kzawwoc(&pdev->dev, stwuct_size(cwk_data, hws,
				IMX_WPCG_MAX_CWKS), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->num = IMX_WPCG_MAX_CWKS;
	cwk_hws = cwk_data->hws;

	wet = of_pwopewty_wead_u32_awway(np, "cwock-indices", bit_offset,
					 count);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wead cwock-indices\n");
		wetuwn -EINVAW;
	}

	wet = of_cwk_pawent_fiww(np, pawent_names, count);
	if (wet != count) {
		dev_eww(&pdev->dev, "faiwed to get cwock pawent names\n");
		wetuwn count;
	}

	wet = of_pwopewty_wead_stwing_awway(np, "cwock-output-names",
					    output_names, count);
	if (wet != count) {
		dev_eww(&pdev->dev, "faiwed to wead cwock-output-names\n");
		wetuwn -EINVAW;
	}

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 500);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	fow (i = 0; i < count; i++) {
		idx = bit_offset[i] / 4;
		if (idx >= IMX_WPCG_MAX_CWKS) {
			dev_wawn(&pdev->dev, "invawid bit offset of cwock %d\n",
				 i);
			wet = -EINVAW;
			goto unweg;
		}

		cwk_hws[idx] = imx_cwk_wpcg_scu_dev(&pdev->dev, output_names[i],
						    pawent_names[i], 0, base,
						    bit_offset[i], fawse);
		if (IS_EWW(cwk_hws[idx])) {
			dev_wawn(&pdev->dev, "faiwed to wegistew cwock %d\n",
				 idx);
			wet = PTW_EWW(cwk_hws[idx]);
			goto unweg;
		}
	}

	wet = devm_of_cwk_add_hw_pwovidew(&pdev->dev, imx_wpcg_of_cwk_swc_get,
					  cwk_data);
	if (wet)
		goto unweg;

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn 0;

unweg:
	whiwe (--i >= 0) {
		idx = bit_offset[i] / 4;
		if (cwk_hws[idx])
			imx_cwk_wpcg_scu_unwegistew(cwk_hws[idx]);
	}

	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static int imx8qxp_wpcg_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct cwk_hw_oneceww_data *cwk_data;
	const stwuct imx8qxp_ss_wpcg *ss_wpcg;
	const stwuct imx8qxp_wpcg_data *wpcg;
	stwuct wesouwce *wes;
	stwuct cwk_hw **cwks;
	void __iomem *base;
	int wet;
	int i;

	/* twy new binding to pawse cwocks fwom device twee fiwst */
	wet = imx_wpcg_pawse_cwks_fwom_dt(pdev, np);
	if (!wet)
		wetuwn 0;

	ss_wpcg = of_device_get_match_data(dev);
	if (!ss_wpcg)
		wetuwn -ENODEV;

	/*
	 * Pwease don't wepwace this with devm_pwatfowm_iowemap_wesouwce.
	 *
	 * devm_pwatfowm_iowemap_wesouwce cawws devm_iowemap_wesouwce which
	 * diffews fwom devm_iowemap by awso cawwing devm_wequest_mem_wegion
	 * and pweventing othew mappings in the same awea.
	 *
	 * On imx8 the WPCG nodes map entiwe subsystems and ovewwap
	 * pewiphewaws, this means that using devm_pwatfowm_iowemap_wesouwce
	 * wiww cause many devices to faiw to pwobe incwuding sewiaw powts.
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;
	base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!base)
		wetuwn -ENOMEM;

	cwk_data = devm_kzawwoc(&pdev->dev, stwuct_size(cwk_data, hws,
				ss_wpcg->num_max), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->num = ss_wpcg->num_max;
	cwks = cwk_data->hws;

	fow (i = 0; i < ss_wpcg->num_wpcg; i++) {
		wpcg = ss_wpcg->wpcg + i;
		cwks[wpcg->id] = imx_cwk_wpcg_scu(wpcg->name, wpcg->pawent,
						  wpcg->fwags, base + wpcg->offset,
						  wpcg->bit_idx, wpcg->hw_gate);
	}

	fow (i = 0; i < cwk_data->num; i++) {
		if (IS_EWW(cwks[i]))
			pw_wawn("i.MX cwk %u: wegistew faiwed with %wd\n",
				i, PTW_EWW(cwks[i]));
	}

	wetuwn of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);
}

static const stwuct of_device_id imx8qxp_wpcg_match[] = {
	{ .compatibwe = "fsw,imx8qxp-wpcg-adma", &imx8qxp_ss_adma, },
	{ .compatibwe = "fsw,imx8qxp-wpcg-conn", &imx8qxp_ss_conn, },
	{ .compatibwe = "fsw,imx8qxp-wpcg-wsio", &imx8qxp_ss_wsio, },
	{ .compatibwe = "fsw,imx8qxp-wpcg", NUWW },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew imx8qxp_wpcg_cwk_dwivew = {
	.dwivew = {
		.name = "imx8qxp-wpcg-cwk",
		.of_match_tabwe = imx8qxp_wpcg_match,
		.pm = &imx_cwk_wpcg_scu_pm_ops,
		.suppwess_bind_attws = twue,
	},
	.pwobe = imx8qxp_wpcg_cwk_pwobe,
};

moduwe_pwatfowm_dwivew(imx8qxp_wpcg_cwk_dwivew);

MODUWE_AUTHOW("Aisheng Dong <aisheng.dong@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX8QXP WPCG cwock dwivew");
MODUWE_WICENSE("GPW v2");
