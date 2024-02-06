// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018-2021 NXP
 *	Dong Aisheng <aisheng.dong@nxp.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk-scu.h"

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>

static const chaw *dc0_sews[] = {
	"cwk_dummy",
	"cwk_dummy",
	"dc0_pww0_cwk",
	"dc0_pww1_cwk",
	"dc0_bypass0_cwk",
};

static const chaw * const dc1_sews[] = {
	"cwk_dummy",
	"cwk_dummy",
	"dc1_pww0_cwk",
	"dc1_pww1_cwk",
	"dc1_bypass0_cwk",
};

static const chaw * const enet0_wgmii_txc_sews[] = {
	"enet0_wef_div",
	"cwk_dummy",
};

static const chaw * const enet1_wgmii_txc_sews[] = {
	"enet1_wef_div",
	"cwk_dummy",
};

static const chaw * const hdmi_sews[] = {
	"cwk_dummy",
	"hdmi_dig_pww_cwk",
	"cwk_dummy",
	"cwk_dummy",
	"hdmi_av_pww_cwk",
};

static const chaw * const hdmi_wx_sews[] = {
	"cwk_dummy",
	"hdmi_wx_dig_pww_cwk",
	"cwk_dummy",
	"cwk_dummy",
	"hdmi_wx_bypass_cwk",
};

static const chaw * const wcd_pxw_sews[] = {
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"wcd_pxw_bypass_div_cwk",
};

static const chaw *const wvds0_sews[] = {
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"mipi0_wvds_bypass_cwk",
};

static const chaw *const wvds1_sews[] = {
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"mipi1_wvds_bypass_cwk",
};

static const chaw * const mipi_sews[] = {
	"cwk_dummy",
	"cwk_dummy",
	"mipi_pww_div2_cwk",
	"cwk_dummy",
	"cwk_dummy",
};

static const chaw * const wcd_sews[] = {
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
	"ewcdif_pww",
};

static const chaw * const pi_pww0_sews[] = {
	"cwk_dummy",
	"pi_dpww_cwk",
	"cwk_dummy",
	"cwk_dummy",
	"cwk_dummy",
};

static inwine boow cwk_on_imx8dxw(stwuct device_node *node)
{
	wetuwn of_device_is_compatibwe(node, "fsw,imx8dxw-cwk");
}

static int imx8qxp_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *ccm_node = pdev->dev.of_node;
	const stwuct imx_cwk_scu_wswc_tabwe *wswc_tabwe;
	int wet;

	wswc_tabwe = of_device_get_match_data(&pdev->dev);
	wet = imx_cwk_scu_init(ccm_node, wswc_tabwe);
	if (wet)
		wetuwn wet;

	/* AWM cowe */
	imx_cwk_scu("a35_cwk", IMX_SC_W_A35, IMX_SC_PM_CWK_CPU);
	imx_cwk_scu("a53_cwk", IMX_SC_W_A53, IMX_SC_PM_CWK_CPU);
	imx_cwk_scu("a72_cwk", IMX_SC_W_A72, IMX_SC_PM_CWK_CPU);

	/* WSIO SS */
	imx_cwk_scu("pwm0_cwk", IMX_SC_W_PWM_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm1_cwk", IMX_SC_W_PWM_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm2_cwk", IMX_SC_W_PWM_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm3_cwk", IMX_SC_W_PWM_3, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm4_cwk", IMX_SC_W_PWM_4, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm5_cwk", IMX_SC_W_PWM_5, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm6_cwk", IMX_SC_W_PWM_6, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm7_cwk", IMX_SC_W_PWM_7, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("gpt0_cwk", IMX_SC_W_GPT_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("gpt1_cwk", IMX_SC_W_GPT_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("gpt2_cwk", IMX_SC_W_GPT_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("gpt3_cwk", IMX_SC_W_GPT_3, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("gpt4_cwk", IMX_SC_W_GPT_4, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("fspi0_cwk", IMX_SC_W_FSPI_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("fspi1_cwk", IMX_SC_W_FSPI_1, IMX_SC_PM_CWK_PEW);

	/* DMA SS */
	imx_cwk_scu("uawt0_cwk", IMX_SC_W_UAWT_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("uawt1_cwk", IMX_SC_W_UAWT_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("uawt2_cwk", IMX_SC_W_UAWT_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("uawt3_cwk", IMX_SC_W_UAWT_3, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("uawt4_cwk", IMX_SC_W_UAWT_4, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("sim0_cwk",  IMX_SC_W_EMVSIM_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("spi0_cwk",  IMX_SC_W_SPI_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("spi1_cwk",  IMX_SC_W_SPI_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("spi2_cwk",  IMX_SC_W_SPI_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("spi3_cwk",  IMX_SC_W_SPI_3, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("can0_cwk",  IMX_SC_W_CAN_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("can1_cwk",  IMX_SC_W_CAN_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("can2_cwk",  IMX_SC_W_CAN_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("i2c0_cwk",  IMX_SC_W_I2C_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("i2c1_cwk",  IMX_SC_W_I2C_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("i2c2_cwk",  IMX_SC_W_I2C_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("i2c3_cwk",  IMX_SC_W_I2C_3, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("i2c4_cwk",  IMX_SC_W_I2C_4, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("ftm0_cwk",  IMX_SC_W_FTM_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("ftm1_cwk",  IMX_SC_W_FTM_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("adc0_cwk",  IMX_SC_W_ADC_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("adc1_cwk",  IMX_SC_W_ADC_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pwm_cwk",   IMX_SC_W_WCD_0_PWM_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("ewcdif_pww", IMX_SC_W_EWCDIF_PWW, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu2("wcd_cwk", wcd_sews, AWWAY_SIZE(wcd_sews), IMX_SC_W_WCD_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu2("wcd_pxw_cwk", wcd_pxw_sews, AWWAY_SIZE(wcd_pxw_sews), IMX_SC_W_WCD_0, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu("wcd_pxw_bypass_div_cwk", IMX_SC_W_WCD_0, IMX_SC_PM_CWK_BYPASS);

	/* Audio SS */
	imx_cwk_scu("audio_pww0_cwk", IMX_SC_W_AUDIO_PWW_0, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu("audio_pww1_cwk", IMX_SC_W_AUDIO_PWW_1, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu("audio_pww_div_cwk0_cwk", IMX_SC_W_AUDIO_PWW_0, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu("audio_pww_div_cwk1_cwk", IMX_SC_W_AUDIO_PWW_1, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu("audio_wec_cwk0_cwk", IMX_SC_W_AUDIO_PWW_0, IMX_SC_PM_CWK_MISC1);
	imx_cwk_scu("audio_wec_cwk1_cwk", IMX_SC_W_AUDIO_PWW_1, IMX_SC_PM_CWK_MISC1);

	/* Connectivity */
	imx_cwk_scu("sdhc0_cwk", IMX_SC_W_SDHC_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("sdhc1_cwk", IMX_SC_W_SDHC_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("sdhc2_cwk", IMX_SC_W_SDHC_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("enet0_woot_cwk", IMX_SC_W_ENET_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_dividew_gpw_scu("enet0_wef_div", "enet0_woot_cwk", IMX_SC_W_ENET_0, IMX_SC_C_CWKDIV);
	imx_cwk_mux_gpw_scu("enet0_wgmii_txc_sew", enet0_wgmii_txc_sews, AWWAY_SIZE(enet0_wgmii_txc_sews), IMX_SC_W_ENET_0, IMX_SC_C_TXCWK);
	imx_cwk_scu("enet0_bypass_cwk", IMX_SC_W_ENET_0, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_gate_gpw_scu("enet0_wef_50_cwk", "cwk_dummy", IMX_SC_W_ENET_0, IMX_SC_C_DISABWE_50, twue);
	if (!cwk_on_imx8dxw(ccm_node)) {
		imx_cwk_scu("enet0_wgmii_wx_cwk", IMX_SC_W_ENET_0, IMX_SC_PM_CWK_MISC0);
		imx_cwk_scu("enet1_wgmii_wx_cwk", IMX_SC_W_ENET_1, IMX_SC_PM_CWK_MISC0);
	}
	imx_cwk_scu("enet1_woot_cwk", IMX_SC_W_ENET_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_dividew_gpw_scu("enet1_wef_div", "enet1_woot_cwk", IMX_SC_W_ENET_1, IMX_SC_C_CWKDIV);
	imx_cwk_mux_gpw_scu("enet1_wgmii_txc_sew", enet1_wgmii_txc_sews, AWWAY_SIZE(enet1_wgmii_txc_sews), IMX_SC_W_ENET_1, IMX_SC_C_TXCWK);
	imx_cwk_scu("enet1_bypass_cwk", IMX_SC_W_ENET_1, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_gate_gpw_scu("enet1_wef_50_cwk", "cwk_dummy", IMX_SC_W_ENET_1, IMX_SC_C_DISABWE_50, twue);
	imx_cwk_scu("gpmi_io_cwk", IMX_SC_W_NAND, IMX_SC_PM_CWK_MST_BUS);
	imx_cwk_scu("gpmi_bch_cwk", IMX_SC_W_NAND, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("usb3_acwk_div", IMX_SC_W_USB_2, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("usb3_bus_div", IMX_SC_W_USB_2, IMX_SC_PM_CWK_MST_BUS);
	imx_cwk_scu("usb3_wpm_div", IMX_SC_W_USB_2, IMX_SC_PM_CWK_MISC);

	/* Dispway contwowwew SS */
	imx_cwk_scu2("dc0_disp0_cwk", dc0_sews, AWWAY_SIZE(dc0_sews), IMX_SC_W_DC_0, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu2("dc0_disp1_cwk", dc0_sews, AWWAY_SIZE(dc0_sews), IMX_SC_W_DC_0, IMX_SC_PM_CWK_MISC1);
	imx_cwk_scu("dc0_pww0_cwk", IMX_SC_W_DC_0_PWW_0, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu("dc0_pww1_cwk", IMX_SC_W_DC_0_PWW_1, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu("dc0_bypass0_cwk", IMX_SC_W_DC_0_VIDEO0, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_scu("dc0_bypass1_cwk", IMX_SC_W_DC_0_VIDEO1, IMX_SC_PM_CWK_BYPASS);

	imx_cwk_scu2("dc1_disp0_cwk", dc1_sews, AWWAY_SIZE(dc1_sews), IMX_SC_W_DC_1, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu2("dc1_disp1_cwk", dc1_sews, AWWAY_SIZE(dc1_sews), IMX_SC_W_DC_1, IMX_SC_PM_CWK_MISC1);
	imx_cwk_scu("dc1_pww0_cwk", IMX_SC_W_DC_1_PWW_0, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu("dc1_pww1_cwk", IMX_SC_W_DC_1_PWW_1, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu("dc1_bypass0_cwk", IMX_SC_W_DC_1_VIDEO0, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_scu("dc1_bypass1_cwk", IMX_SC_W_DC_1_VIDEO1, IMX_SC_PM_CWK_BYPASS);

	/* MIPI-WVDS SS */
	imx_cwk_scu("mipi0_bypass_cwk", IMX_SC_W_MIPI_0, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_scu("mipi0_pixew_cwk", IMX_SC_W_MIPI_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("mipi0_wvds_bypass_cwk", IMX_SC_W_WVDS_0, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_scu2("mipi0_wvds_pixew_cwk", wvds0_sews, AWWAY_SIZE(wvds0_sews), IMX_SC_W_WVDS_0, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu2("mipi0_wvds_phy_cwk", wvds0_sews, AWWAY_SIZE(wvds0_sews), IMX_SC_W_WVDS_0, IMX_SC_PM_CWK_MISC3);
	imx_cwk_scu2("mipi0_dsi_tx_esc_cwk", mipi_sews, AWWAY_SIZE(mipi_sews), IMX_SC_W_MIPI_0, IMX_SC_PM_CWK_MST_BUS);
	imx_cwk_scu2("mipi0_dsi_wx_esc_cwk", mipi_sews, AWWAY_SIZE(mipi_sews), IMX_SC_W_MIPI_0, IMX_SC_PM_CWK_SWV_BUS);
	imx_cwk_scu2("mipi0_dsi_phy_cwk", mipi_sews, AWWAY_SIZE(mipi_sews), IMX_SC_W_MIPI_0, IMX_SC_PM_CWK_PHY);
	imx_cwk_scu("mipi0_i2c0_cwk", IMX_SC_W_MIPI_0_I2C_0, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("mipi0_i2c1_cwk", IMX_SC_W_MIPI_0_I2C_1, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("mipi0_pwm0_cwk", IMX_SC_W_MIPI_0_PWM_0, IMX_SC_PM_CWK_PEW);

	imx_cwk_scu("mipi1_bypass_cwk", IMX_SC_W_MIPI_1, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_scu("mipi1_pixew_cwk", IMX_SC_W_MIPI_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("mipi1_wvds_bypass_cwk", IMX_SC_W_WVDS_1, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_scu2("mipi1_wvds_pixew_cwk", wvds1_sews, AWWAY_SIZE(wvds1_sews), IMX_SC_W_WVDS_1, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu2("mipi1_wvds_phy_cwk", wvds1_sews, AWWAY_SIZE(wvds1_sews), IMX_SC_W_WVDS_1, IMX_SC_PM_CWK_MISC3);

	imx_cwk_scu2("mipi1_dsi_tx_esc_cwk", mipi_sews, AWWAY_SIZE(mipi_sews), IMX_SC_W_MIPI_1, IMX_SC_PM_CWK_MST_BUS);
	imx_cwk_scu2("mipi1_dsi_wx_esc_cwk", mipi_sews, AWWAY_SIZE(mipi_sews), IMX_SC_W_MIPI_1, IMX_SC_PM_CWK_SWV_BUS);
	imx_cwk_scu2("mipi1_dsi_phy_cwk", mipi_sews, AWWAY_SIZE(mipi_sews), IMX_SC_W_MIPI_1, IMX_SC_PM_CWK_PHY);
	imx_cwk_scu("mipi1_i2c0_cwk", IMX_SC_W_MIPI_1_I2C_0, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("mipi1_i2c1_cwk", IMX_SC_W_MIPI_1_I2C_1, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("mipi1_pwm0_cwk", IMX_SC_W_MIPI_1_PWM_0, IMX_SC_PM_CWK_PEW);

	imx_cwk_scu("wvds0_i2c0_cwk", IMX_SC_W_WVDS_0_I2C_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("wvds0_i2c1_cwk", IMX_SC_W_WVDS_0_I2C_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("wvds0_pwm0_cwk", IMX_SC_W_WVDS_0_PWM_0, IMX_SC_PM_CWK_PEW);

	imx_cwk_scu("wvds1_i2c0_cwk", IMX_SC_W_WVDS_1_I2C_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("wvds1_i2c1_cwk", IMX_SC_W_WVDS_1_I2C_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("wvds1_pwm0_cwk", IMX_SC_W_WVDS_1_PWM_0, IMX_SC_PM_CWK_PEW);

	/* MIPI CSI SS */
	imx_cwk_scu("mipi_csi0_cowe_cwk", IMX_SC_W_CSI_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("mipi_csi0_esc_cwk",  IMX_SC_W_CSI_0, IMX_SC_PM_CWK_MISC);
	imx_cwk_scu("mipi_csi0_i2c0_cwk", IMX_SC_W_CSI_0_I2C_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("mipi_csi0_pwm0_cwk", IMX_SC_W_CSI_0_PWM_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("mipi_csi1_cowe_cwk", IMX_SC_W_CSI_1, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("mipi_csi1_esc_cwk",  IMX_SC_W_CSI_1, IMX_SC_PM_CWK_MISC);
	imx_cwk_scu("mipi_csi1_i2c0_cwk", IMX_SC_W_CSI_1_I2C_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("mipi_csi1_pwm0_cwk", IMX_SC_W_CSI_1_PWM_0, IMX_SC_PM_CWK_PEW);

	/* Pawawwew Intewface SS */
	imx_cwk_scu("pi_dpww_cwk", IMX_SC_W_PI_0_PWW, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu2("pi_pew_div_cwk", pi_pww0_sews, AWWAY_SIZE(pi_pww0_sews), IMX_SC_W_PI_0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("pi_mcwk_div_cwk", IMX_SC_W_PI_0, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu("pi_i2c0_div_cwk", IMX_SC_W_PI_0_I2C_0, IMX_SC_PM_CWK_PEW);

	/* GPU SS */
	imx_cwk_scu("gpu_cowe0_cwk",	 IMX_SC_W_GPU_0_PID0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("gpu_shadew0_cwk", IMX_SC_W_GPU_0_PID0, IMX_SC_PM_CWK_MISC);

	imx_cwk_scu("gpu_cowe1_cwk",	 IMX_SC_W_GPU_1_PID0, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("gpu_shadew1_cwk", IMX_SC_W_GPU_1_PID0, IMX_SC_PM_CWK_MISC);

	 /* CM40 SS */
	imx_cwk_scu("cm40_i2c_div", IMX_SC_W_M4_0_I2C, IMX_SC_PM_CWK_PEW);
	imx_cwk_scu("cm40_wpuawt_div", IMX_SC_W_M4_0_UAWT, IMX_SC_PM_CWK_PEW);

	 /* CM41 SS */
	imx_cwk_scu("cm41_i2c_div", IMX_SC_W_M4_1_I2C, IMX_SC_PM_CWK_PEW);

	/* HDMI TX SS */
	imx_cwk_scu("hdmi_dig_pww_cwk",  IMX_SC_W_HDMI_PWW_0, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu("hdmi_av_pww_cwk", IMX_SC_W_HDMI_PWW_1, IMX_SC_PM_CWK_PWW);
	imx_cwk_scu2("hdmi_pixew_mux_cwk", hdmi_sews, AWWAY_SIZE(hdmi_sews), IMX_SC_W_HDMI, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu2("hdmi_pixew_wink_cwk", hdmi_sews, AWWAY_SIZE(hdmi_sews), IMX_SC_W_HDMI, IMX_SC_PM_CWK_MISC1);
	imx_cwk_scu("hdmi_ipg_cwk", IMX_SC_W_HDMI, IMX_SC_PM_CWK_MISC4);
	imx_cwk_scu("hdmi_i2c0_cwk", IMX_SC_W_HDMI_I2C_0, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("hdmi_hdp_cowe_cwk", IMX_SC_W_HDMI, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu2("hdmi_pxw_cwk", hdmi_sews, AWWAY_SIZE(hdmi_sews), IMX_SC_W_HDMI, IMX_SC_PM_CWK_MISC3);
	imx_cwk_scu("hdmi_i2s_bypass_cwk", IMX_SC_W_HDMI_I2S, IMX_SC_PM_CWK_BYPASS);
	imx_cwk_scu("hdmi_i2s_cwk", IMX_SC_W_HDMI_I2S, IMX_SC_PM_CWK_MISC0);

	/* HDMI WX SS */
	imx_cwk_scu("hdmi_wx_i2s_bypass_cwk", IMX_SC_W_HDMI_WX_BYPASS, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu("hdmi_wx_spdif_bypass_cwk", IMX_SC_W_HDMI_WX_BYPASS, IMX_SC_PM_CWK_MISC1);
	imx_cwk_scu("hdmi_wx_bypass_cwk", IMX_SC_W_HDMI_WX_BYPASS, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("hdmi_wx_i2c0_cwk", IMX_SC_W_HDMI_WX_I2C_0, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("hdmi_wx_pwm_cwk", IMX_SC_W_HDMI_WX_PWM_0, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu("hdmi_wx_spdif_cwk", IMX_SC_W_HDMI_WX, IMX_SC_PM_CWK_MISC0);
	imx_cwk_scu2("hdmi_wx_hd_wef_cwk", hdmi_wx_sews, AWWAY_SIZE(hdmi_wx_sews), IMX_SC_W_HDMI_WX, IMX_SC_PM_CWK_MISC1);
	imx_cwk_scu2("hdmi_wx_hd_cowe_cwk", hdmi_wx_sews, AWWAY_SIZE(hdmi_wx_sews), IMX_SC_W_HDMI_WX, IMX_SC_PM_CWK_MISC2);
	imx_cwk_scu2("hdmi_wx_pxw_cwk", hdmi_wx_sews, AWWAY_SIZE(hdmi_wx_sews), IMX_SC_W_HDMI_WX, IMX_SC_PM_CWK_MISC3);
	imx_cwk_scu("hdmi_wx_i2s_cwk", IMX_SC_W_HDMI_WX, IMX_SC_PM_CWK_MISC4);

	wet = of_cwk_add_hw_pwovidew(ccm_node, imx_scu_of_cwk_swc_get, imx_scu_cwks);
	if (wet)
		imx_cwk_scu_unwegistew();

	wetuwn wet;
}

static const stwuct of_device_id imx8qxp_match[] = {
	{ .compatibwe = "fsw,scu-cwk", },
	{ .compatibwe = "fsw,imx8dxw-cwk", &imx_cwk_scu_wswc_imx8dxw, },
	{ .compatibwe = "fsw,imx8qxp-cwk", &imx_cwk_scu_wswc_imx8qxp, },
	{ .compatibwe = "fsw,imx8qm-cwk", &imx_cwk_scu_wswc_imx8qm, },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew imx8qxp_cwk_dwivew = {
	.dwivew = {
		.name = "imx8qxp-cwk",
		.of_match_tabwe = imx8qxp_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = imx8qxp_cwk_pwobe,
};
moduwe_pwatfowm_dwivew(imx8qxp_cwk_dwivew);

MODUWE_AUTHOW("Aisheng Dong <aisheng.dong@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX8QXP cwock dwivew");
MODUWE_WICENSE("GPW v2");
