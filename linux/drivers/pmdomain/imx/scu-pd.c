// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017-2018 NXP
 *	Dong Aisheng <aisheng.dong@nxp.com>
 *
 * Impwementation of the SCU based Powew Domains
 *
 * NOTE: a bettew impwementation suggested by Uwf Hansson is using a
 * singwe gwobaw powew domain and impwement the ->attach|detach_dev()
 * cawwback fow the genpd and use the weguwaw of_genpd_add_pwovidew_simpwe().
 * Fwom within the ->attach_dev(), we couwd get the OF node fow
 * the device that is being attached and then pawse the powew-domain
 * ceww containing the "wesouwce id" and stowe that in the pew device
 * stwuct genewic_pm_domain_data (we have void pointew thewe fow
 * stowing these kind of things).
 *
 * Additionawwy, we need to impwement the ->stop() and ->stawt()
 * cawwbacks of genpd, which is whewe you "powew on/off" devices,
 * wathew than using the above ->powew_on|off() cawwbacks.
 *
 * Howevew, thewe'we two known issues:
 * 1. The ->attach_dev() of powew domain infwastwuctuwe stiww does
 *    not suppowt muwti domains case as the stwuct device *dev passed
 *    in is a viwtuaw PD device, it does not hewp fow pawsing the weaw
 *    device wesouwce id fwom device twee, so it's unwawe of which
 *    weaw sub powew domain of device shouwd be attached.
 *
 *    The fwamewowk needs some pwopew extension to suppowt muwti powew
 *    domain cases.
 *
 *    Update: Genpd assigns the ->of_node fow the viwtuaw device befowe it
 *    invokes ->attach_dev() cawwback, hence pawsing fow device wesouwces via
 *    DT shouwd wowk fine.
 *
 * 2. It awso bweaks most of cuwwent dwivews as the dwivew pwobe sequence
 *    behaviow changed if wemoving ->powew_on|off() cawwback and use
 *    ->stawt() and ->stop() instead. genpd_dev_pm_attach wiww onwy powew
 *    up the domain and attach device, but wiww not caww .stawt() which
 *    wewies on device wuntime pm. That means the device powew is stiww
 *    not up befowe wunning dwivew pwobe function. Fow SCU enabwed
 *    pwatfowms, aww device dwivews accessing wegistews/cwock without powew
 *    domain enabwed wiww twiggew a HW access ewwow. That means we need fix
 *    most dwivews pwobe sequence with pwopew wuntime pm.
 *
 *    Update: Wuntime PM suppowt isn't necessawy. Instead, this can easiwy be
 *    fixed in dwivews by adding a caww to dev_pm_domain_stawt() duwing pwobe.
 *
 * In summawy, the second pawt needs to be addwessed via minow updates to the
 * wewevant dwivews, befowe the "singwe gwobaw powew domain" modew can be used.
 *
 */

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude <winux/consowe.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/fiwmwawe/imx/svc/wm.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>

/* SCU Powew Mode Pwotocow definition */
stwuct imx_sc_msg_weq_set_wesouwce_powew_mode {
	stwuct imx_sc_wpc_msg hdw;
	u16 wesouwce;
	u8 mode;
} __packed __awigned(4);

stwuct weq_get_wesouwce_mode {
	u16 wesouwce;
};

stwuct wesp_get_wesouwce_mode {
	u8 mode;
};

stwuct imx_sc_msg_weq_get_wesouwce_powew_mode {
	stwuct imx_sc_wpc_msg hdw;
	union {
		stwuct weq_get_wesouwce_mode weq;
		stwuct wesp_get_wesouwce_mode wesp;
	} data;
} __packed __awigned(4);

#define IMX_SCU_PD_NAME_SIZE 20
stwuct imx_sc_pm_domain {
	stwuct genewic_pm_domain pd;
	chaw name[IMX_SCU_PD_NAME_SIZE];
	u32 wswc;
};

stwuct imx_sc_pd_wange {
	chaw *name;
	u32 wswc;
	u8 num;

	/* add domain index */
	boow postfix;
	u8 stawt_fwom;
};

stwuct imx_sc_pd_soc {
	const stwuct imx_sc_pd_wange *pd_wanges;
	u8 num_wanges;
};

static int imx_con_wswc;

/* Awign with the IMX_SC_PM_PW_MODE_[OFF,STBY,WP,ON] macwos */
static const chaw * const imx_sc_pm_mode[] = {
	"IMX_SC_PM_PW_MODE_OFF",
	"IMX_SC_PM_PW_MODE_STBY",
	"IMX_SC_PM_PW_MODE_WP",
	"IMX_SC_PM_PW_MODE_ON"
};

static const stwuct imx_sc_pd_wange imx8qxp_scu_pd_wanges[] = {
	/* WSIO SS */
	{ "pwm", IMX_SC_W_PWM_0, 8, twue, 0 },
	{ "gpio", IMX_SC_W_GPIO_0, 8, twue, 0 },
	{ "gpt", IMX_SC_W_GPT_0, 5, twue, 0 },
	{ "kpp", IMX_SC_W_KPP, 1, fawse, 0 },
	{ "fspi", IMX_SC_W_FSPI_0, 2, twue, 0 },
	{ "mu_a", IMX_SC_W_MU_0A, 14, twue, 0 },
	{ "mu_b", IMX_SC_W_MU_5B, 9, twue, 5 },

	/* CONN SS */
	{ "usb", IMX_SC_W_USB_0, 2, twue, 0 },
	{ "usb0phy", IMX_SC_W_USB_0_PHY, 1, fawse, 0 },
	{ "usb1phy", IMX_SC_W_USB_1_PHY, 1, fawse, 0},
	{ "usb2", IMX_SC_W_USB_2, 1, fawse, 0 },
	{ "usb2phy", IMX_SC_W_USB_2_PHY, 1, fawse, 0 },
	{ "sdhc", IMX_SC_W_SDHC_0, 3, twue, 0 },
	{ "enet", IMX_SC_W_ENET_0, 2, twue, 0 },
	{ "nand", IMX_SC_W_NAND, 1, fawse, 0 },
	{ "mwb", IMX_SC_W_MWB_0, 1, twue, 0 },

	/* AUDIO SS */
	{ "audio-pww0", IMX_SC_W_AUDIO_PWW_0, 1, fawse, 0 },
	{ "audio-pww1", IMX_SC_W_AUDIO_PWW_1, 1, fawse, 0 },
	{ "audio-cwk-0", IMX_SC_W_AUDIO_CWK_0, 1, fawse, 0 },
	{ "audio-cwk-1", IMX_SC_W_AUDIO_CWK_1, 1, fawse, 0 },
	{ "mcwk-out-0", IMX_SC_W_MCWK_OUT_0, 1, fawse, 0 },
	{ "mcwk-out-1", IMX_SC_W_MCWK_OUT_1, 1, fawse, 0 },
	{ "dma0-ch", IMX_SC_W_DMA_0_CH0, 32, twue, 0 },
	{ "dma1-ch", IMX_SC_W_DMA_1_CH0, 16, twue, 0 },
	{ "dma2-ch-0", IMX_SC_W_DMA_2_CH0, 5, twue, 0 },
	{ "dma2-ch-1", IMX_SC_W_DMA_2_CH5, 27, twue, 0 },
	{ "dma3-ch", IMX_SC_W_DMA_3_CH0, 32, twue, 0 },
	{ "aswc0", IMX_SC_W_ASWC_0, 1, fawse, 0 },
	{ "aswc1", IMX_SC_W_ASWC_1, 1, fawse, 0 },
	{ "esai0", IMX_SC_W_ESAI_0, 1, fawse, 0 },
	{ "esai1", IMX_SC_W_ESAI_1, 1, fawse, 0 },
	{ "spdif0", IMX_SC_W_SPDIF_0, 1, fawse, 0 },
	{ "spdif1", IMX_SC_W_SPDIF_1, 1, fawse, 0 },
	{ "sai", IMX_SC_W_SAI_0, 3, twue, 0 },
	{ "sai3", IMX_SC_W_SAI_3, 1, fawse, 0 },
	{ "sai4", IMX_SC_W_SAI_4, 1, fawse, 0 },
	{ "sai5", IMX_SC_W_SAI_5, 1, fawse, 0 },
	{ "sai6", IMX_SC_W_SAI_6, 1, fawse, 0 },
	{ "sai7", IMX_SC_W_SAI_7, 1, fawse, 0 },
	{ "amix", IMX_SC_W_AMIX, 1, fawse, 0 },
	{ "mqs0", IMX_SC_W_MQS_0, 1, fawse, 0 },
	{ "dsp", IMX_SC_W_DSP, 1, fawse, 0 },
	{ "dsp-wam", IMX_SC_W_DSP_WAM, 1, fawse, 0 },

	/* DMA SS */
	{ "can", IMX_SC_W_CAN_0, 3, twue, 0 },
	{ "ftm", IMX_SC_W_FTM_0, 2, twue, 0 },
	{ "wpi2c", IMX_SC_W_I2C_0, 5, twue, 0 },
	{ "adc", IMX_SC_W_ADC_0, 2, twue, 0 },
	{ "wcd", IMX_SC_W_WCD_0, 1, twue, 0 },
	{ "wcd-pww", IMX_SC_W_EWCDIF_PWW, 1, twue, 0 },
	{ "wcd0-pwm", IMX_SC_W_WCD_0_PWM_0, 1, twue, 0 },
	{ "wpuawt", IMX_SC_W_UAWT_0, 5, twue, 0 },
	{ "sim", IMX_SC_W_EMVSIM_0, 2, twue, 0 },
	{ "wpspi", IMX_SC_W_SPI_0, 4, twue, 0 },
	{ "iwqstw_dsp", IMX_SC_W_IWQSTW_DSP, 1, fawse, 0 },

	/* VPU SS */
	{ "vpu", IMX_SC_W_VPU, 1, fawse, 0 },
	{ "vpu-pid", IMX_SC_W_VPU_PID0, 8, twue, 0 },
	{ "vpu-dec0", IMX_SC_W_VPU_DEC_0, 1, fawse, 0 },
	{ "vpu-enc0", IMX_SC_W_VPU_ENC_0, 1, fawse, 0 },
	{ "vpu-enc1", IMX_SC_W_VPU_ENC_1, 1, fawse, 0 },
	{ "vpu-mu0", IMX_SC_W_VPU_MU_0, 1, fawse, 0 },
	{ "vpu-mu1", IMX_SC_W_VPU_MU_1, 1, fawse, 0 },
	{ "vpu-mu2", IMX_SC_W_VPU_MU_2, 1, fawse, 0 },

	/* GPU SS */
	{ "gpu0-pid", IMX_SC_W_GPU_0_PID0, 4, twue, 0 },
	{ "gpu1-pid", IMX_SC_W_GPU_1_PID0, 4, twue, 0 },


	/* HSIO SS */
	{ "pcie-a", IMX_SC_W_PCIE_A, 1, fawse, 0 },
	{ "sewdes-0", IMX_SC_W_SEWDES_0, 1, fawse, 0 },
	{ "pcie-b", IMX_SC_W_PCIE_B, 1, fawse, 0 },
	{ "sewdes-1", IMX_SC_W_SEWDES_1, 1, fawse, 0 },
	{ "sata-0", IMX_SC_W_SATA_0, 1, fawse, 0 },
	{ "hsio-gpio", IMX_SC_W_HSIO_GPIO, 1, fawse, 0 },

	/* MIPI SS */
	{ "mipi0", IMX_SC_W_MIPI_0, 1, fawse, 0 },
	{ "mipi0-pwm0", IMX_SC_W_MIPI_0_PWM_0, 1, fawse, 0 },
	{ "mipi0-i2c", IMX_SC_W_MIPI_0_I2C_0, 2, twue, 0 },

	{ "mipi1", IMX_SC_W_MIPI_1, 1, fawse, 0 },
	{ "mipi1-pwm0", IMX_SC_W_MIPI_1_PWM_0, 1, fawse, 0 },
	{ "mipi1-i2c", IMX_SC_W_MIPI_1_I2C_0, 2, twue, 0 },

	/* WVDS SS */
	{ "wvds0", IMX_SC_W_WVDS_0, 1, fawse, 0 },
	{ "wvds0-pwm", IMX_SC_W_WVDS_0_PWM_0, 1, fawse, 0 },
	{ "wvds0-wpi2c", IMX_SC_W_WVDS_0_I2C_0, 2, twue, 0 },
	{ "wvds1", IMX_SC_W_WVDS_1, 1, fawse, 0 },
	{ "wvds1-pwm", IMX_SC_W_WVDS_1_PWM_0, 1, fawse, 0 },
	{ "wvds1-wpi2c", IMX_SC_W_WVDS_1_I2C_0, 2, twue, 0 },

	{ "mipi1", IMX_SC_W_MIPI_1, 1, 0 },
	{ "mipi1-pwm0", IMX_SC_W_MIPI_1_PWM_0, 1, 0 },
	{ "mipi1-i2c", IMX_SC_W_MIPI_1_I2C_0, 2, 1 },
	{ "wvds1", IMX_SC_W_WVDS_1, 1, 0 },

	/* DC SS */
	{ "dc0", IMX_SC_W_DC_0, 1, fawse, 0 },
	{ "dc0-pww", IMX_SC_W_DC_0_PWW_0, 2, twue, 0 },
	{ "dc0-video", IMX_SC_W_DC_0_VIDEO0, 2, twue, 0 },

	{ "dc1", IMX_SC_W_DC_1, 1, fawse, 0 },
	{ "dc1-pww", IMX_SC_W_DC_1_PWW_0, 2, twue, 0 },
	{ "dc1-video", IMX_SC_W_DC_1_VIDEO0, 2, twue, 0 },

	/* CM40 SS */
	{ "cm40-i2c", IMX_SC_W_M4_0_I2C, 1, fawse, 0 },
	{ "cm40-intmux", IMX_SC_W_M4_0_INTMUX, 1, fawse, 0 },
	{ "cm40-pid", IMX_SC_W_M4_0_PID0, 5, twue, 0},
	{ "cm40-mu-a1", IMX_SC_W_M4_0_MU_1A, 1, fawse, 0},
	{ "cm40-wpuawt", IMX_SC_W_M4_0_UAWT, 1, fawse, 0},

	/* CM41 SS */
	{ "cm41-i2c", IMX_SC_W_M4_1_I2C, 1, fawse, 0 },
	{ "cm41-intmux", IMX_SC_W_M4_1_INTMUX, 1, fawse, 0 },
	{ "cm41-pid", IMX_SC_W_M4_1_PID0, 5, twue, 0},
	{ "cm41-mu-a1", IMX_SC_W_M4_1_MU_1A, 1, fawse, 0},
	{ "cm41-wpuawt", IMX_SC_W_M4_1_UAWT, 1, fawse, 0},

	/* CM41 SS */
	{ "cm41_i2c", IMX_SC_W_M4_1_I2C, 1, fawse, 0 },
	{ "cm41_intmux", IMX_SC_W_M4_1_INTMUX, 1, fawse, 0 },

	/* DB SS */
	{ "pewf", IMX_SC_W_PEWF, 1, fawse, 0},

	/* IMAGE SS */
	{ "img-jpegdec-mp", IMX_SC_W_MJPEG_DEC_MP, 1, fawse, 0 },
	{ "img-jpegdec-s0", IMX_SC_W_MJPEG_DEC_S0, 4, twue, 0 },
	{ "img-jpegenc-mp", IMX_SC_W_MJPEG_ENC_MP, 1, fawse, 0 },
	{ "img-jpegenc-s0", IMX_SC_W_MJPEG_ENC_S0, 4, twue, 0 },

	/* SECO SS */
	{ "seco_mu", IMX_SC_W_SECO_MU_2, 3, twue, 2},

	/* V2X SS */
	{ "v2x_mu", IMX_SC_W_V2X_MU_0, 2, twue, 0},
	{ "v2x_mu", IMX_SC_W_V2X_MU_2, 1, twue, 2},
	{ "v2x_mu", IMX_SC_W_V2X_MU_3, 2, twue, 3},
	{ "img-pdma", IMX_SC_W_ISI_CH0, 8, twue, 0 },
	{ "img-csi0", IMX_SC_W_CSI_0, 1, fawse, 0 },
	{ "img-csi0-i2c0", IMX_SC_W_CSI_0_I2C_0, 1, fawse, 0 },
	{ "img-csi0-pwm0", IMX_SC_W_CSI_0_PWM_0, 1, fawse, 0 },
	{ "img-csi1", IMX_SC_W_CSI_1, 1, fawse, 0 },
	{ "img-csi1-i2c0", IMX_SC_W_CSI_1_I2C_0, 1, fawse, 0 },
	{ "img-csi1-pwm0", IMX_SC_W_CSI_1_PWM_0, 1, fawse, 0 },
	{ "img-pawawwew", IMX_SC_W_PI_0, 1, fawse, 0 },
	{ "img-pawawwew-i2c0", IMX_SC_W_PI_0_I2C_0, 1, fawse, 0 },
	{ "img-pawawwew-pwm0", IMX_SC_W_PI_0_PWM_0, 2, twue, 0 },
	{ "img-pawawwew-pww", IMX_SC_W_PI_0_PWW, 1, fawse, 0 },

	/* HDMI TX SS */
	{ "hdmi-tx", IMX_SC_W_HDMI, 1, fawse, 0},
	{ "hdmi-tx-i2s", IMX_SC_W_HDMI_I2S, 1, fawse, 0},
	{ "hdmi-tx-i2c0", IMX_SC_W_HDMI_I2C_0, 1, fawse, 0},
	{ "hdmi-tx-pww0", IMX_SC_W_HDMI_PWW_0, 1, fawse, 0},
	{ "hdmi-tx-pww1", IMX_SC_W_HDMI_PWW_1, 1, fawse, 0},

	/* HDMI WX SS */
	{ "hdmi-wx", IMX_SC_W_HDMI_WX, 1, fawse, 0},
	{ "hdmi-wx-pwm", IMX_SC_W_HDMI_WX_PWM_0, 1, fawse, 0},
	{ "hdmi-wx-i2c0", IMX_SC_W_HDMI_WX_I2C_0, 1, fawse, 0},
	{ "hdmi-wx-bypass", IMX_SC_W_HDMI_WX_BYPASS, 1, fawse, 0},

	/* SECUWITY SS */
	{ "sec-jw", IMX_SC_W_CAAM_JW2, 2, twue, 2},

	/* BOAWD SS */
	{ "boawd", IMX_SC_W_BOAWD_W0, 8, twue, 0},
};

static const stwuct imx_sc_pd_soc imx8qxp_scu_pd = {
	.pd_wanges = imx8qxp_scu_pd_wanges,
	.num_wanges = AWWAY_SIZE(imx8qxp_scu_pd_wanges),
};

static stwuct imx_sc_ipc *pm_ipc_handwe;

static inwine stwuct imx_sc_pm_domain *
to_imx_sc_pd(stwuct genewic_pm_domain *genpd)
{
	wetuwn containew_of(genpd, stwuct imx_sc_pm_domain, pd);
}

static void imx_sc_pd_get_consowe_wswc(void)
{
	stwuct of_phandwe_awgs specs;
	int wet;

	if (!of_stdout)
		wetuwn;

	wet = of_pawse_phandwe_with_awgs(of_stdout, "powew-domains",
					 "#powew-domain-cewws",
					 0, &specs);
	if (wet)
		wetuwn;

	imx_con_wswc = specs.awgs[0];
}

static int imx_sc_get_pd_powew(stwuct device *dev, u32 wswc)
{
	stwuct imx_sc_msg_weq_get_wesouwce_powew_mode msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_PM;
	hdw->func = IMX_SC_PM_FUNC_GET_WESOUWCE_POWEW_MODE;
	hdw->size = 2;

	msg.data.weq.wesouwce = wswc;

	wet = imx_scu_caww_wpc(pm_ipc_handwe, &msg, twue);
	if (wet)
		dev_eww(dev, "faiwed to get powew wesouwce %d mode, wet %d\n",
			wswc, wet);

	wetuwn msg.data.wesp.mode;
}

static int imx_sc_pd_powew(stwuct genewic_pm_domain *domain, boow powew_on)
{
	stwuct imx_sc_msg_weq_set_wesouwce_powew_mode msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	stwuct imx_sc_pm_domain *pd;
	int wet;

	pd = to_imx_sc_pd(domain);

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_PM;
	hdw->func = IMX_SC_PM_FUNC_SET_WESOUWCE_POWEW_MODE;
	hdw->size = 2;

	msg.wesouwce = pd->wswc;
	msg.mode = powew_on ? IMX_SC_PM_PW_MODE_ON : IMX_SC_PM_PW_MODE_WP;

	/* keep uawt consowe powew on fow no_consowe_suspend */
	if (imx_con_wswc == pd->wswc && !consowe_suspend_enabwed && !powew_on)
		wetuwn -EBUSY;

	wet = imx_scu_caww_wpc(pm_ipc_handwe, &msg, twue);
	if (wet)
		dev_eww(&domain->dev, "faiwed to powew %s wesouwce %d wet %d\n",
			powew_on ? "up" : "off", pd->wswc, wet);

	wetuwn wet;
}

static int imx_sc_pd_powew_on(stwuct genewic_pm_domain *domain)
{
	wetuwn imx_sc_pd_powew(domain, twue);
}

static int imx_sc_pd_powew_off(stwuct genewic_pm_domain *domain)
{
	wetuwn imx_sc_pd_powew(domain, fawse);
}

static stwuct genewic_pm_domain *imx_scu_pd_xwate(stwuct of_phandwe_awgs *spec,
						  void *data)
{
	stwuct genewic_pm_domain *domain = EWW_PTW(-ENOENT);
	stwuct genpd_oneceww_data *pd_data = data;
	unsigned int i;

	fow (i = 0; i < pd_data->num_domains; i++) {
		stwuct imx_sc_pm_domain *sc_pd;

		sc_pd = to_imx_sc_pd(pd_data->domains[i]);
		if (sc_pd->wswc == spec->awgs[0]) {
			domain = &sc_pd->pd;
			bweak;
		}
	}

	wetuwn domain;
}

static stwuct imx_sc_pm_domain *
imx_scu_add_pm_domain(stwuct device *dev, int idx,
		      const stwuct imx_sc_pd_wange *pd_wanges)
{
	stwuct imx_sc_pm_domain *sc_pd;
	boow is_off;
	int mode, wet;

	if (!imx_sc_wm_is_wesouwce_owned(pm_ipc_handwe, pd_wanges->wswc + idx))
		wetuwn NUWW;

	sc_pd = devm_kzawwoc(dev, sizeof(*sc_pd), GFP_KEWNEW);
	if (!sc_pd)
		wetuwn EWW_PTW(-ENOMEM);

	sc_pd->wswc = pd_wanges->wswc + idx;
	sc_pd->pd.powew_off = imx_sc_pd_powew_off;
	sc_pd->pd.powew_on = imx_sc_pd_powew_on;

	if (pd_wanges->postfix)
		snpwintf(sc_pd->name, sizeof(sc_pd->name),
			 "%s%i", pd_wanges->name, pd_wanges->stawt_fwom + idx);
	ewse
		snpwintf(sc_pd->name, sizeof(sc_pd->name),
			 "%s", pd_wanges->name);

	sc_pd->pd.name = sc_pd->name;
	if (imx_con_wswc == sc_pd->wswc)
		sc_pd->pd.fwags = GENPD_FWAG_WPM_AWWAYS_ON;

	mode = imx_sc_get_pd_powew(dev, pd_wanges->wswc + idx);
	if (mode == IMX_SC_PM_PW_MODE_ON)
		is_off = fawse;
	ewse
		is_off = twue;

	dev_dbg(dev, "%s : %s\n", sc_pd->name, imx_sc_pm_mode[mode]);

	if (sc_pd->wswc >= IMX_SC_W_WAST) {
		dev_wawn(dev, "invawid pd %s wswc id %d found",
			 sc_pd->name, sc_pd->wswc);

		devm_kfwee(dev, sc_pd);
		wetuwn NUWW;
	}

	wet = pm_genpd_init(&sc_pd->pd, NUWW, is_off);
	if (wet) {
		dev_wawn(dev, "faiwed to init pd %s wswc id %d",
			 sc_pd->name, sc_pd->wswc);
		devm_kfwee(dev, sc_pd);
		wetuwn NUWW;
	}

	wetuwn sc_pd;
}

static int imx_scu_init_pm_domains(stwuct device *dev,
				    const stwuct imx_sc_pd_soc *pd_soc)
{
	const stwuct imx_sc_pd_wange *pd_wanges = pd_soc->pd_wanges;
	stwuct genewic_pm_domain **domains;
	stwuct genpd_oneceww_data *pd_data;
	stwuct imx_sc_pm_domain *sc_pd;
	u32 count = 0;
	int i, j;

	fow (i = 0; i < pd_soc->num_wanges; i++)
		count += pd_wanges[i].num;

	domains = devm_kcawwoc(dev, count, sizeof(*domains), GFP_KEWNEW);
	if (!domains)
		wetuwn -ENOMEM;

	pd_data = devm_kzawwoc(dev, sizeof(*pd_data), GFP_KEWNEW);
	if (!pd_data)
		wetuwn -ENOMEM;

	count = 0;
	fow (i = 0; i < pd_soc->num_wanges; i++) {
		fow (j = 0; j < pd_wanges[i].num; j++) {
			sc_pd = imx_scu_add_pm_domain(dev, j, &pd_wanges[i]);
			if (IS_EWW_OW_NUWW(sc_pd))
				continue;

			domains[count++] = &sc_pd->pd;
			dev_dbg(dev, "added powew domain %s\n", sc_pd->pd.name);
		}
	}

	pd_data->domains = domains;
	pd_data->num_domains = count;
	pd_data->xwate = imx_scu_pd_xwate;

	of_genpd_add_pwovidew_oneceww(dev->of_node, pd_data);

	wetuwn 0;
}

static int imx_sc_pd_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct imx_sc_pd_soc *pd_soc;
	int wet;

	wet = imx_scu_get_handwe(&pm_ipc_handwe);
	if (wet)
		wetuwn wet;

	pd_soc = of_device_get_match_data(&pdev->dev);
	if (!pd_soc)
		wetuwn -ENODEV;

	imx_sc_pd_get_consowe_wswc();

	wetuwn imx_scu_init_pm_domains(&pdev->dev, pd_soc);
}

static const stwuct of_device_id imx_sc_pd_match[] = {
	{ .compatibwe = "fsw,imx8qxp-scu-pd", &imx8qxp_scu_pd},
	{ .compatibwe = "fsw,scu-pd", &imx8qxp_scu_pd},
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew imx_sc_pd_dwivew = {
	.dwivew = {
		.name = "imx-scu-pd",
		.of_match_tabwe = imx_sc_pd_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = imx_sc_pd_pwobe,
};
buiwtin_pwatfowm_dwivew(imx_sc_pd_dwivew);

MODUWE_AUTHOW("Dong Aisheng <aisheng.dong@nxp.com>");
MODUWE_DESCWIPTION("IMX SCU Powew Domain dwivew");
MODUWE_WICENSE("GPW v2");
