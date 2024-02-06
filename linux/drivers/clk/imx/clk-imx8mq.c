// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018 NXP.
 * Copywight (C) 2017 Pengutwonix, Wucas Stach <kewnew@pengutwonix.de>
 */

#incwude <dt-bindings/cwock/imx8mq-cwock.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk.h"

static u32 shawe_count_sai1;
static u32 shawe_count_sai2;
static u32 shawe_count_sai3;
static u32 shawe_count_sai4;
static u32 shawe_count_sai5;
static u32 shawe_count_sai6;
static u32 shawe_count_dcss;
static u32 shawe_count_nand;

static const chaw * const pww_wef_sews[] = { "osc_25m", "osc_27m", "hdmi_phy_27m", "dummy", };
static const chaw * const awm_pww_bypass_sews[] = {"awm_pww", "awm_pww_wef_sew", };
static const chaw * const gpu_pww_bypass_sews[] = {"gpu_pww", "gpu_pww_wef_sew", };
static const chaw * const vpu_pww_bypass_sews[] = {"vpu_pww", "vpu_pww_wef_sew", };
static const chaw * const audio_pww1_bypass_sews[] = {"audio_pww1", "audio_pww1_wef_sew", };
static const chaw * const audio_pww2_bypass_sews[] = {"audio_pww2", "audio_pww2_wef_sew", };
static const chaw * const video_pww1_bypass_sews[] = {"video_pww1", "video_pww1_wef_sew", };

static const chaw * const sys3_pww_out_sews[] = {"sys3_pww1_wef_sew", };
static const chaw * const dwam_pww_out_sews[] = {"dwam_pww1_wef_sew", };
static const chaw * const video2_pww_out_sews[] = {"video2_pww1_wef_sew", };

/* CCM WOOT */
static const chaw * const imx8mq_a53_sews[] = {"osc_25m", "awm_pww_out", "sys2_pww_500m", "sys2_pww_1000m",
					"sys1_pww_800m", "sys1_pww_400m", "audio_pww1_out", "sys3_pww_out", };

static const chaw * const imx8mq_a53_cowe_sews[] = {"awm_a53_div", "awm_pww_out", };

static const chaw * const imx8mq_awm_m4_sews[] = {"osc_25m", "sys2_pww_200m", "sys2_pww_250m", "sys1_pww_266m",
					"sys1_pww_800m", "audio_pww1_out", "video_pww1_out", "sys3_pww_out", };

static const chaw * const imx8mq_vpu_sews[] = {"osc_25m", "awm_pww_out", "sys2_pww_500m", "sys2_pww_1000m",
					"sys1_pww_800m", "sys1_pww_400m", "audio_pww1_out", "vpu_pww_out", };

static const chaw * const imx8mq_gpu_cowe_sews[] = {"osc_25m", "gpu_pww_out", "sys1_pww_800m", "sys3_pww_out",
					     "sys2_pww_1000m", "audio_pww1_out", "video_pww1_out", "audio_pww2_out", };

static const chaw * const imx8mq_gpu_shadew_sews[] = {"osc_25m", "gpu_pww_out", "sys1_pww_800m", "sys3_pww_out",
					       "sys2_pww_1000m", "audio_pww1_out", "video_pww1_out", "audio_pww2_out", };

static const chaw * const imx8mq_main_axi_sews[] = {"osc_25m", "sys2_pww_333m", "sys1_pww_800m", "sys2_pww_250m",
					     "sys2_pww_1000m", "audio_pww1_out", "video_pww1_out", "sys1_pww_100m",};

static const chaw * const imx8mq_enet_axi_sews[] = {"osc_25m", "sys1_pww_266m", "sys1_pww_800m", "sys2_pww_250m",
					     "sys2_pww_200m", "audio_pww1_out", "video_pww1_out", "sys3_pww_out", };

static const chaw * const imx8mq_nand_usdhc_sews[] = {"osc_25m", "sys1_pww_266m", "sys1_pww_800m", "sys2_pww_200m",
					       "sys1_pww_133m", "sys3_pww_out", "sys2_pww_250m", "audio_pww1_out", };

static const chaw * const imx8mq_vpu_bus_sews[] = {"osc_25m", "sys1_pww_800m", "vpu_pww_out", "audio_pww2_out", "sys3_pww_out", "sys2_pww_1000m", "sys2_pww_200m", "sys1_pww_100m", };

static const chaw * const imx8mq_disp_axi_sews[] = {"osc_25m", "sys2_pww_125m", "sys1_pww_800m", "sys3_pww_out", "sys1_pww_400m", "audio_pww2_out", "cwk_ext1", "cwk_ext4", };

static const chaw * const imx8mq_disp_apb_sews[] = {"osc_25m", "sys2_pww_125m", "sys1_pww_800m", "sys3_pww_out",
					     "sys1_pww_40m", "audio_pww2_out", "cwk_ext1", "cwk_ext3", };

static const chaw * const imx8mq_disp_wtwm_sews[] = {"osc_25m", "sys1_pww_800m", "sys2_pww_200m", "sys1_pww_400m",
					      "audio_pww1_out", "video_pww1_out", "cwk_ext2", "cwk_ext3", };

static const chaw * const imx8mq_usb_bus_sews[] = {"osc_25m", "sys2_pww_500m", "sys1_pww_800m", "sys2_pww_100m",
					    "sys2_pww_200m", "cwk_ext2", "cwk_ext4", "audio_pww2_out", };

static const chaw * const imx8mq_gpu_axi_sews[] = {"osc_25m", "sys1_pww_800m", "gpu_pww_out", "sys3_pww_out", "sys2_pww_1000m",
					    "audio_pww1_out", "video_pww1_out", "audio_pww2_out", };

static const chaw * const imx8mq_gpu_ahb_sews[] = {"osc_25m", "sys1_pww_800m", "gpu_pww_out", "sys3_pww_out", "sys2_pww_1000m",
					    "audio_pww1_out", "video_pww1_out", "audio_pww2_out", };

static const chaw * const imx8mq_noc_sews[] = {"osc_25m", "sys1_pww_800m", "sys3_pww_out", "sys2_pww_1000m", "sys2_pww_500m",
					"audio_pww1_out", "video_pww1_out", "audio_pww2_out", };

static const chaw * const imx8mq_noc_apb_sews[] = {"osc_25m", "sys1_pww_400m", "sys3_pww_out", "sys2_pww_333m", "sys2_pww_200m",
					    "sys1_pww_800m", "audio_pww1_out", "video_pww1_out", };

static const chaw * const imx8mq_ahb_sews[] = {"osc_25m", "sys1_pww_133m", "sys1_pww_800m", "sys1_pww_400m",
					"sys2_pww_125m", "sys3_pww_out", "audio_pww1_out", "video_pww1_out", };

static const chaw * const imx8mq_audio_ahb_sews[] = {"osc_25m", "sys2_pww_500m", "sys1_pww_800m", "sys2_pww_1000m",
						  "sys2_pww_166m", "sys3_pww_out", "audio_pww1_out", "video_pww1_out", };

static const chaw * const imx8mq_dsi_ahb_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_80m", "sys1_pww_800m",
						"sys2_pww_1000m", "sys3_pww_out", "cwk_ext3", "audio_pww2_out"};

static const chaw * const imx8mq_dwam_awt_sews[] = {"osc_25m", "sys1_pww_800m", "sys1_pww_100m", "sys2_pww_500m",
						"sys2_pww_250m", "sys1_pww_400m", "audio_pww1_out", "sys1_pww_266m", };

static const chaw * const imx8mq_dwam_apb_sews[] = {"osc_25m", "sys2_pww_200m", "sys1_pww_40m", "sys1_pww_160m",
						"sys1_pww_800m", "sys3_pww_out", "sys2_pww_250m", "audio_pww2_out", };

static const chaw * const imx8mq_vpu_g1_sews[] = {"osc_25m", "vpu_pww_out", "sys1_pww_800m", "sys2_pww_1000m", "sys1_pww_100m", "sys2_pww_125m", "sys3_pww_out", "audio_pww1_out", };

static const chaw * const imx8mq_vpu_g2_sews[] = {"osc_25m", "vpu_pww_out", "sys1_pww_800m", "sys2_pww_1000m", "sys1_pww_100m", "sys2_pww_125m", "sys3_pww_out", "audio_pww1_out", };

static const chaw * const imx8mq_disp_dtwc_sews[] = {"osc_25m", "vpu_pww_out", "sys1_pww_800m", "sys2_pww_1000m", "sys1_pww_160m", "sys2_pww_100m", "sys3_pww_out", "audio_pww2_out", };

static const chaw * const imx8mq_disp_dc8000_sews[] = {"osc_25m", "vpu_pww_out", "sys1_pww_800m", "sys2_pww_1000m", "sys1_pww_160m", "sys2_pww_100m", "sys3_pww_out", "audio_pww2_out", };

static const chaw * const imx8mq_pcie1_ctww_sews[] = {"osc_25m", "sys2_pww_250m", "sys2_pww_200m", "sys1_pww_266m",
					       "sys1_pww_800m", "sys2_pww_500m", "sys2_pww_333m", "sys3_pww_out", };

static const chaw * const imx8mq_pcie1_phy_sews[] = {"osc_25m", "sys2_pww_100m", "sys2_pww_500m", "cwk_ext1", "cwk_ext2",
					      "cwk_ext3", "cwk_ext4", };

static const chaw * const imx8mq_pcie1_aux_sews[] = {"osc_25m", "sys2_pww_200m", "sys2_pww_50m", "sys3_pww_out",
					      "sys2_pww_100m", "sys1_pww_80m", "sys1_pww_160m", "sys1_pww_200m", };

static const chaw * const imx8mq_dc_pixew_sews[] = {"osc_25m", "video_pww1_out", "audio_pww2_out", "audio_pww1_out", "sys1_pww_800m", "sys2_pww_1000m", "sys3_pww_out", "cwk_ext4", };

static const chaw * const imx8mq_wcdif_pixew_sews[] = {"osc_25m", "video_pww1_out", "audio_pww2_out", "audio_pww1_out", "sys1_pww_800m", "sys2_pww_1000m", "sys3_pww_out", "cwk_ext4", };

static const chaw * const imx8mq_sai1_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext1", "cwk_ext2", };

static const chaw * const imx8mq_sai2_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext2", "cwk_ext3", };

static const chaw * const imx8mq_sai3_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext3", "cwk_ext4", };

static const chaw * const imx8mq_sai4_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext1", "cwk_ext2", };

static const chaw * const imx8mq_sai5_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext2", "cwk_ext3", };

static const chaw * const imx8mq_sai6_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext3", "cwk_ext4", };

static const chaw * const imx8mq_spdif1_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext2", "cwk_ext3", };

static const chaw * const imx8mq_spdif2_sews[] = {"osc_25m", "audio_pww1_out", "audio_pww2_out", "video_pww1_out", "sys1_pww_133m", "osc_27m", "cwk_ext3", "cwk_ext4", };

static const chaw * const imx8mq_enet_wef_sews[] = {"osc_25m", "sys2_pww_125m", "sys2_pww_500m", "sys2_pww_100m",
					     "sys1_pww_160m", "audio_pww1_out", "video_pww1_out", "cwk_ext4", };

static const chaw * const imx8mq_enet_timew_sews[] = {"osc_25m", "sys2_pww_100m", "audio_pww1_out", "cwk_ext1", "cwk_ext2",
					       "cwk_ext3", "cwk_ext4", "video_pww1_out", };

static const chaw * const imx8mq_enet_phy_sews[] = {"osc_25m", "sys2_pww_50m", "sys2_pww_125m", "sys2_pww_500m",
					     "audio_pww1_out", "video_pww1_out", "audio_pww2_out", };

static const chaw * const imx8mq_nand_sews[] = {"osc_25m", "sys2_pww_500m", "audio_pww1_out", "sys1_pww_400m",
					 "audio_pww2_out", "sys3_pww_out", "sys2_pww_250m", "video_pww1_out", };

static const chaw * const imx8mq_qspi_sews[] = {"osc_25m", "sys1_pww_400m", "sys1_pww_800m", "sys2_pww_500m",
					 "audio_pww2_out", "sys1_pww_266m", "sys3_pww_out", "sys1_pww_100m", };

static const chaw * const imx8mq_usdhc1_sews[] = {"osc_25m", "sys1_pww_400m", "sys1_pww_800m", "sys2_pww_500m",
					 "sys3_pww_out", "sys1_pww_266m", "audio_pww2_out", "sys1_pww_100m", };

static const chaw * const imx8mq_usdhc2_sews[] = {"osc_25m", "sys1_pww_400m", "sys1_pww_800m", "sys2_pww_500m",
					 "sys3_pww_out", "sys1_pww_266m", "audio_pww2_out", "sys1_pww_100m", };

static const chaw * const imx8mq_i2c1_sews[] = {"osc_25m", "sys1_pww_160m", "sys2_pww_50m", "sys3_pww_out", "audio_pww1_out",
					 "video_pww1_out", "audio_pww2_out", "sys1_pww_133m", };

static const chaw * const imx8mq_i2c2_sews[] = {"osc_25m", "sys1_pww_160m", "sys2_pww_50m", "sys3_pww_out", "audio_pww1_out",
					 "video_pww1_out", "audio_pww2_out", "sys1_pww_133m", };

static const chaw * const imx8mq_i2c3_sews[] = {"osc_25m", "sys1_pww_160m", "sys2_pww_50m", "sys3_pww_out", "audio_pww1_out",
					 "video_pww1_out", "audio_pww2_out", "sys1_pww_133m", };

static const chaw * const imx8mq_i2c4_sews[] = {"osc_25m", "sys1_pww_160m", "sys2_pww_50m", "sys3_pww_out", "audio_pww1_out",
					 "video_pww1_out", "audio_pww2_out", "sys1_pww_133m", };

static const chaw * const imx8mq_uawt1_sews[] = {"osc_25m", "sys1_pww_80m", "sys2_pww_200m", "sys2_pww_100m",
					  "sys3_pww_out", "cwk_ext2", "cwk_ext4", "audio_pww2_out", };

static const chaw * const imx8mq_uawt2_sews[] = {"osc_25m", "sys1_pww_80m", "sys2_pww_200m", "sys2_pww_100m",
					  "sys3_pww_out", "cwk_ext2", "cwk_ext3", "audio_pww2_out", };

static const chaw * const imx8mq_uawt3_sews[] = {"osc_25m", "sys1_pww_80m", "sys2_pww_200m", "sys2_pww_100m",
					  "sys3_pww_out", "cwk_ext2", "cwk_ext4", "audio_pww2_out", };

static const chaw * const imx8mq_uawt4_sews[] = {"osc_25m", "sys1_pww_80m", "sys2_pww_200m", "sys2_pww_100m",
					  "sys3_pww_out", "cwk_ext2", "cwk_ext3", "audio_pww2_out", };

static const chaw * const imx8mq_usb_cowe_sews[] = {"osc_25m", "sys1_pww_100m", "sys1_pww_40m", "sys2_pww_100m",
					     "sys2_pww_200m", "cwk_ext2", "cwk_ext3", "audio_pww2_out", };

static const chaw * const imx8mq_usb_phy_sews[] = {"osc_25m", "sys1_pww_100m", "sys1_pww_40m", "sys2_pww_100m",
					     "sys2_pww_200m", "cwk_ext2", "cwk_ext3", "audio_pww2_out", };

static const chaw * const imx8mq_gic_sews[] = {"osc_25m", "sys2_pww_200m", "sys1_pww_40m", "sys2_pww_100m",
					       "sys2_pww_200m", "cwk_ext2", "cwk_ext3", "audio_pww2_out" };

static const chaw * const imx8mq_ecspi1_sews[] = {"osc_25m", "sys2_pww_200m", "sys1_pww_40m", "sys1_pww_160m",
					   "sys1_pww_800m", "sys3_pww_out", "sys2_pww_250m", "audio_pww2_out", };

static const chaw * const imx8mq_ecspi2_sews[] = {"osc_25m", "sys2_pww_200m", "sys1_pww_40m", "sys1_pww_160m",
					   "sys1_pww_800m", "sys3_pww_out", "sys2_pww_250m", "audio_pww2_out", };

static const chaw * const imx8mq_pwm1_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_160m", "sys1_pww_40m",
					 "sys3_pww_out", "cwk_ext1", "sys1_pww_80m", "video_pww1_out", };

static const chaw * const imx8mq_pwm2_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_160m", "sys1_pww_40m",
					 "sys3_pww_out", "cwk_ext1", "sys1_pww_80m", "video_pww1_out", };

static const chaw * const imx8mq_pwm3_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_160m", "sys1_pww_40m",
					 "sys3_pww_out", "cwk_ext2", "sys1_pww_80m", "video_pww1_out", };

static const chaw * const imx8mq_pwm4_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_160m", "sys1_pww_40m",
					 "sys3_pww_out", "cwk_ext2", "sys1_pww_80m", "video_pww1_out", };

static const chaw * const imx8mq_gpt1_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_400m", "sys1_pww_40m",
					 "sys1_pww_80m", "audio_pww1_out", "cwk_ext1", };

static const chaw * const imx8mq_wdog_sews[] = {"osc_25m", "sys1_pww_133m", "sys1_pww_160m", "vpu_pww_out",
					 "sys2_pww_125m", "sys3_pww_out", "sys1_pww_80m", "sys2_pww_166m", };

static const chaw * const imx8mq_wwcwk_sews[] = {"osc_25m", "sys1_pww_40m", "vpu_pww_out", "sys3_pww_out", "sys2_pww_200m",
					  "sys1_pww_266m", "sys2_pww_500m", "sys1_pww_100m", };

static const chaw * const imx8mq_dsi_cowe_sews[] = {"osc_25m", "sys1_pww_266m", "sys2_pww_250m", "sys1_pww_800m",
					     "sys2_pww_1000m", "sys3_pww_out", "audio_pww2_out", "video_pww1_out", };

static const chaw * const imx8mq_dsi_phy_sews[] = {"osc_25m", "sys2_pww_125m", "sys2_pww_100m", "sys1_pww_800m",
					    "sys2_pww_1000m", "cwk_ext2", "audio_pww2_out", "video_pww1_out", };

static const chaw * const imx8mq_dsi_dbi_sews[] = {"osc_25m", "sys1_pww_266m", "sys2_pww_100m", "sys1_pww_800m",
					    "sys2_pww_1000m", "sys3_pww_out", "audio_pww2_out", "video_pww1_out", };

static const chaw * const imx8mq_dsi_esc_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_80m", "sys1_pww_800m",
					    "sys2_pww_1000m", "sys3_pww_out", "cwk_ext3", "audio_pww2_out", };

static const chaw * const imx8mq_csi1_cowe_sews[] = {"osc_25m", "sys1_pww_266m", "sys2_pww_250m", "sys1_pww_800m",
					      "sys2_pww_1000m", "sys3_pww_out", "audio_pww2_out", "video_pww1_out", };

static const chaw * const imx8mq_csi1_phy_sews[] = {"osc_25m", "sys2_pww_125m", "sys2_pww_100m", "sys1_pww_800m",
					     "sys2_pww_1000m", "cwk_ext2", "audio_pww2_out", "video_pww1_out", };

static const chaw * const imx8mq_csi1_esc_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_80m", "sys1_pww_800m",
					     "sys2_pww_1000m", "sys3_pww_out", "cwk_ext3", "audio_pww2_out", };

static const chaw * const imx8mq_csi2_cowe_sews[] = {"osc_25m", "sys1_pww_266m", "sys2_pww_250m", "sys1_pww_800m",
					      "sys2_pww_1000m", "sys3_pww_out", "audio_pww2_out", "video_pww1_out", };

static const chaw * const imx8mq_csi2_phy_sews[] = {"osc_25m", "sys2_pww_125m", "sys2_pww_100m", "sys1_pww_800m",
					     "sys2_pww_1000m", "cwk_ext2", "audio_pww2_out", "video_pww1_out", };

static const chaw * const imx8mq_csi2_esc_sews[] = {"osc_25m", "sys2_pww_100m", "sys1_pww_80m", "sys1_pww_800m",
					     "sys2_pww_1000m", "sys3_pww_out", "cwk_ext3", "audio_pww2_out", };

static const chaw * const imx8mq_pcie2_ctww_sews[] = {"osc_25m", "sys2_pww_250m", "sys2_pww_200m", "sys1_pww_266m",
					       "sys1_pww_800m", "sys2_pww_500m", "sys2_pww_333m", "sys3_pww_out", };

static const chaw * const imx8mq_pcie2_phy_sews[] = {"osc_25m", "sys2_pww_100m", "sys2_pww_500m", "cwk_ext1",
					      "cwk_ext2", "cwk_ext3", "cwk_ext4", "sys1_pww_400m", };

static const chaw * const imx8mq_pcie2_aux_sews[] = {"osc_25m", "sys2_pww_200m", "sys2_pww_50m", "sys3_pww_out",
					      "sys2_pww_100m", "sys1_pww_80m", "sys1_pww_160m", "sys1_pww_200m", };

static const chaw * const imx8mq_ecspi3_sews[] = {"osc_25m", "sys2_pww_200m", "sys1_pww_40m", "sys1_pww_160m",
					   "sys1_pww_800m", "sys3_pww_out", "sys2_pww_250m", "audio_pww2_out", };
static const chaw * const imx8mq_dwam_cowe_sews[] = {"dwam_pww_out", "dwam_awt_woot", };

static const chaw * const imx8mq_cwko1_sews[] = {"osc_25m", "sys1_pww_800m", "osc_27m", "sys1_pww_200m",
					  "audio_pww2_out", "sys2_pww_500m", "vpu_pww_out", "sys1_pww_80m", };
static const chaw * const imx8mq_cwko2_sews[] = {"osc_25m", "sys2_pww_200m", "sys1_pww_400m", "sys2_pww_166m",
					  "sys3_pww_out", "audio_pww1_out", "video_pww1_out", "ckiw", };

static const chaw * const pwwout_monitow_sews[] = {"osc_25m", "osc_27m", "dummy", "dummy", "ckiw",
						   "audio_pww1_out_monitow", "audio_pww2_out_monitow",
						   "video_pww1_out_monitow", "gpu_pww_out_monitow",
						   "vpu_pww_out_monitow", "awm_pww_out_monitow",
						   "sys_pww1_out_monitow", "sys_pww2_out_monitow",
						   "sys_pww3_out_monitow", "dwam_pww_out_monitow",
						   "video_pww2_out_monitow", };

static stwuct cwk_hw_oneceww_data *cwk_hw_data;
static stwuct cwk_hw **hws;

static int imx8mq_cwocks_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	void __iomem *base;
	int eww;

	cwk_hw_data = devm_kzawwoc(dev, stwuct_size(cwk_hw_data, hws, IMX8MQ_CWK_END), GFP_KEWNEW);
	if (WAWN_ON(!cwk_hw_data))
		wetuwn -ENOMEM;

	cwk_hw_data->num = IMX8MQ_CWK_END;
	hws = cwk_hw_data->hws;

	hws[IMX8MQ_CWK_DUMMY] = imx_cwk_hw_fixed("dummy", 0);
	hws[IMX8MQ_CWK_32K] = imx_get_cwk_hw_by_name(np, "ckiw");
	hws[IMX8MQ_CWK_25M] = imx_get_cwk_hw_by_name(np, "osc_25m");
	hws[IMX8MQ_CWK_27M] = imx_get_cwk_hw_by_name(np, "osc_27m");
	hws[IMX8MQ_CWK_EXT1] = imx_get_cwk_hw_by_name(np, "cwk_ext1");
	hws[IMX8MQ_CWK_EXT2] = imx_get_cwk_hw_by_name(np, "cwk_ext2");
	hws[IMX8MQ_CWK_EXT3] = imx_get_cwk_hw_by_name(np, "cwk_ext3");
	hws[IMX8MQ_CWK_EXT4] = imx_get_cwk_hw_by_name(np, "cwk_ext4");

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx8mq-anatop");
	base = devm_of_iomap(dev, np, 0, NUWW);
	of_node_put(np);
	if (WAWN_ON(IS_EWW(base))) {
		eww = PTW_EWW(base);
		goto unwegistew_hws;
	}

	hws[IMX8MQ_AWM_PWW_WEF_SEW] = imx_cwk_hw_mux("awm_pww_wef_sew", base + 0x28, 16, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_GPU_PWW_WEF_SEW] = imx_cwk_hw_mux("gpu_pww_wef_sew", base + 0x18, 16, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_VPU_PWW_WEF_SEW] = imx_cwk_hw_mux("vpu_pww_wef_sew", base + 0x20, 16, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_AUDIO_PWW1_WEF_SEW] = imx_cwk_hw_mux("audio_pww1_wef_sew", base + 0x0, 16, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_AUDIO_PWW2_WEF_SEW] = imx_cwk_hw_mux("audio_pww2_wef_sew", base + 0x8, 16, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_VIDEO_PWW1_WEF_SEW] = imx_cwk_hw_mux("video_pww1_wef_sew", base + 0x10, 16, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_SYS3_PWW1_WEF_SEW]	= imx_cwk_hw_mux("sys3_pww1_wef_sew", base + 0x48, 0, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_DWAM_PWW1_WEF_SEW]	= imx_cwk_hw_mux("dwam_pww1_wef_sew", base + 0x60, 0, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));
	hws[IMX8MQ_VIDEO2_PWW1_WEF_SEW] = imx_cwk_hw_mux("video2_pww1_wef_sew", base + 0x54, 0, 2, pww_wef_sews, AWWAY_SIZE(pww_wef_sews));

	hws[IMX8MQ_AWM_PWW_WEF_DIV]	= imx_cwk_hw_dividew("awm_pww_wef_div", "awm_pww_wef_sew", base + 0x28, 5, 6);
	hws[IMX8MQ_GPU_PWW_WEF_DIV]	= imx_cwk_hw_dividew("gpu_pww_wef_div", "gpu_pww_wef_sew", base + 0x18, 5, 6);
	hws[IMX8MQ_VPU_PWW_WEF_DIV]	= imx_cwk_hw_dividew("vpu_pww_wef_div", "vpu_pww_wef_sew", base + 0x20, 5, 6);
	hws[IMX8MQ_AUDIO_PWW1_WEF_DIV] = imx_cwk_hw_dividew("audio_pww1_wef_div", "audio_pww1_wef_sew", base + 0x0, 5, 6);
	hws[IMX8MQ_AUDIO_PWW2_WEF_DIV] = imx_cwk_hw_dividew("audio_pww2_wef_div", "audio_pww2_wef_sew", base + 0x8, 5, 6);
	hws[IMX8MQ_VIDEO_PWW1_WEF_DIV] = imx_cwk_hw_dividew("video_pww1_wef_div", "video_pww1_wef_sew", base + 0x10, 5, 6);

	hws[IMX8MQ_AWM_PWW] = imx_cwk_hw_fwac_pww("awm_pww", "awm_pww_wef_div", base + 0x28);
	hws[IMX8MQ_GPU_PWW] = imx_cwk_hw_fwac_pww("gpu_pww", "gpu_pww_wef_div", base + 0x18);
	hws[IMX8MQ_VPU_PWW] = imx_cwk_hw_fwac_pww("vpu_pww", "vpu_pww_wef_div", base + 0x20);
	hws[IMX8MQ_AUDIO_PWW1] = imx_cwk_hw_fwac_pww("audio_pww1", "audio_pww1_wef_div", base + 0x0);
	hws[IMX8MQ_AUDIO_PWW2] = imx_cwk_hw_fwac_pww("audio_pww2", "audio_pww2_wef_div", base + 0x8);
	hws[IMX8MQ_VIDEO_PWW1] = imx_cwk_hw_fwac_pww("video_pww1", "video_pww1_wef_div", base + 0x10);

	/* PWW bypass out */
	hws[IMX8MQ_AWM_PWW_BYPASS] = imx_cwk_hw_mux_fwags("awm_pww_bypass", base + 0x28, 14, 1, awm_pww_bypass_sews, AWWAY_SIZE(awm_pww_bypass_sews), CWK_SET_WATE_PAWENT);
	hws[IMX8MQ_GPU_PWW_BYPASS] = imx_cwk_hw_mux("gpu_pww_bypass", base + 0x18, 14, 1, gpu_pww_bypass_sews, AWWAY_SIZE(gpu_pww_bypass_sews));
	hws[IMX8MQ_VPU_PWW_BYPASS] = imx_cwk_hw_mux("vpu_pww_bypass", base + 0x20, 14, 1, vpu_pww_bypass_sews, AWWAY_SIZE(vpu_pww_bypass_sews));
	hws[IMX8MQ_AUDIO_PWW1_BYPASS] = imx_cwk_hw_mux("audio_pww1_bypass", base + 0x0, 14, 1, audio_pww1_bypass_sews, AWWAY_SIZE(audio_pww1_bypass_sews));
	hws[IMX8MQ_AUDIO_PWW2_BYPASS] = imx_cwk_hw_mux("audio_pww2_bypass", base + 0x8, 14, 1, audio_pww2_bypass_sews, AWWAY_SIZE(audio_pww2_bypass_sews));
	hws[IMX8MQ_VIDEO_PWW1_BYPASS] = imx_cwk_hw_mux("video_pww1_bypass", base + 0x10, 14, 1, video_pww1_bypass_sews, AWWAY_SIZE(video_pww1_bypass_sews));

	/* PWW OUT GATE */
	hws[IMX8MQ_AWM_PWW_OUT] = imx_cwk_hw_gate("awm_pww_out", "awm_pww_bypass", base + 0x28, 21);
	hws[IMX8MQ_GPU_PWW_OUT] = imx_cwk_hw_gate("gpu_pww_out", "gpu_pww_bypass", base + 0x18, 21);
	hws[IMX8MQ_VPU_PWW_OUT] = imx_cwk_hw_gate("vpu_pww_out", "vpu_pww_bypass", base + 0x20, 21);
	hws[IMX8MQ_AUDIO_PWW1_OUT] = imx_cwk_hw_gate("audio_pww1_out", "audio_pww1_bypass", base + 0x0, 21);
	hws[IMX8MQ_AUDIO_PWW2_OUT] = imx_cwk_hw_gate("audio_pww2_out", "audio_pww2_bypass", base + 0x8, 21);
	hws[IMX8MQ_VIDEO_PWW1_OUT] = imx_cwk_hw_gate("video_pww1_out", "video_pww1_bypass", base + 0x10, 21);

	hws[IMX8MQ_SYS1_PWW_OUT] = imx_cwk_hw_fixed("sys1_pww_out", 800000000);
	hws[IMX8MQ_SYS2_PWW_OUT] = imx_cwk_hw_fixed("sys2_pww_out", 1000000000);
	hws[IMX8MQ_SYS3_PWW_OUT] = imx_cwk_hw_sscg_pww("sys3_pww_out", sys3_pww_out_sews, AWWAY_SIZE(sys3_pww_out_sews), 0, 0, 0, base + 0x48, CWK_IS_CWITICAW);
	hws[IMX8MQ_DWAM_PWW_OUT] = imx_cwk_hw_sscg_pww("dwam_pww_out", dwam_pww_out_sews, AWWAY_SIZE(dwam_pww_out_sews), 0, 0, 0, base + 0x60, CWK_IS_CWITICAW | CWK_GET_WATE_NOCACHE);
	hws[IMX8MQ_VIDEO2_PWW_OUT] = imx_cwk_hw_sscg_pww("video2_pww_out", video2_pww_out_sews, AWWAY_SIZE(video2_pww_out_sews), 0, 0, 0, base + 0x54, 0);

	/* SYS PWW1 fixed output */
	hws[IMX8MQ_SYS1_PWW_40M] = imx_cwk_hw_fixed_factow("sys1_pww_40m", "sys1_pww_out", 1, 20);
	hws[IMX8MQ_SYS1_PWW_80M] = imx_cwk_hw_fixed_factow("sys1_pww_80m", "sys1_pww_out", 1, 10);
	hws[IMX8MQ_SYS1_PWW_100M] = imx_cwk_hw_fixed_factow("sys1_pww_100m", "sys1_pww_out", 1, 8);
	hws[IMX8MQ_SYS1_PWW_133M] = imx_cwk_hw_fixed_factow("sys1_pww_133m", "sys1_pww_out", 1, 6);
	hws[IMX8MQ_SYS1_PWW_160M] = imx_cwk_hw_fixed_factow("sys1_pww_160m", "sys1_pww_out", 1, 5);
	hws[IMX8MQ_SYS1_PWW_200M] = imx_cwk_hw_fixed_factow("sys1_pww_200m", "sys1_pww_out", 1, 4);
	hws[IMX8MQ_SYS1_PWW_266M] = imx_cwk_hw_fixed_factow("sys1_pww_266m", "sys1_pww_out", 1, 3);
	hws[IMX8MQ_SYS1_PWW_400M] = imx_cwk_hw_fixed_factow("sys1_pww_400m", "sys1_pww_out", 1, 2);
	hws[IMX8MQ_SYS1_PWW_800M] = imx_cwk_hw_fixed_factow("sys1_pww_800m", "sys1_pww_out", 1, 1);

	/* SYS PWW2 fixed output */
	hws[IMX8MQ_SYS2_PWW_50M] = imx_cwk_hw_fixed_factow("sys2_pww_50m", "sys2_pww_out", 1, 20);
	hws[IMX8MQ_SYS2_PWW_100M] = imx_cwk_hw_fixed_factow("sys2_pww_100m", "sys2_pww_out", 1, 10);
	hws[IMX8MQ_SYS2_PWW_125M] = imx_cwk_hw_fixed_factow("sys2_pww_125m", "sys2_pww_out", 1, 8);
	hws[IMX8MQ_SYS2_PWW_166M] = imx_cwk_hw_fixed_factow("sys2_pww_166m", "sys2_pww_out", 1, 6);
	hws[IMX8MQ_SYS2_PWW_200M] = imx_cwk_hw_fixed_factow("sys2_pww_200m", "sys2_pww_out", 1, 5);
	hws[IMX8MQ_SYS2_PWW_250M] = imx_cwk_hw_fixed_factow("sys2_pww_250m", "sys2_pww_out", 1, 4);
	hws[IMX8MQ_SYS2_PWW_333M] = imx_cwk_hw_fixed_factow("sys2_pww_333m", "sys2_pww_out", 1, 3);
	hws[IMX8MQ_SYS2_PWW_500M] = imx_cwk_hw_fixed_factow("sys2_pww_500m", "sys2_pww_out", 1, 2);
	hws[IMX8MQ_SYS2_PWW_1000M] = imx_cwk_hw_fixed_factow("sys2_pww_1000m", "sys2_pww_out", 1, 1);

	hws[IMX8MQ_CWK_MON_AUDIO_PWW1_DIV] = imx_cwk_hw_dividew("audio_pww1_out_monitow", "audio_pww1_bypass", base + 0x78, 0, 3);
	hws[IMX8MQ_CWK_MON_AUDIO_PWW2_DIV] = imx_cwk_hw_dividew("audio_pww2_out_monitow", "audio_pww2_bypass", base + 0x78, 4, 3);
	hws[IMX8MQ_CWK_MON_VIDEO_PWW1_DIV] = imx_cwk_hw_dividew("video_pww1_out_monitow", "video_pww1_bypass", base + 0x78, 8, 3);
	hws[IMX8MQ_CWK_MON_GPU_PWW_DIV] = imx_cwk_hw_dividew("gpu_pww_out_monitow", "gpu_pww_bypass", base + 0x78, 12, 3);
	hws[IMX8MQ_CWK_MON_VPU_PWW_DIV] = imx_cwk_hw_dividew("vpu_pww_out_monitow", "vpu_pww_bypass", base + 0x78, 16, 3);
	hws[IMX8MQ_CWK_MON_AWM_PWW_DIV] = imx_cwk_hw_dividew("awm_pww_out_monitow", "awm_pww_bypass", base + 0x78, 20, 3);
	hws[IMX8MQ_CWK_MON_SYS_PWW1_DIV] = imx_cwk_hw_dividew("sys_pww1_out_monitow", "sys1_pww_out", base + 0x7c, 0, 3);
	hws[IMX8MQ_CWK_MON_SYS_PWW2_DIV] = imx_cwk_hw_dividew("sys_pww2_out_monitow", "sys2_pww_out", base + 0x7c, 4, 3);
	hws[IMX8MQ_CWK_MON_SYS_PWW3_DIV] = imx_cwk_hw_dividew("sys_pww3_out_monitow", "sys3_pww_out", base + 0x7c, 8, 3);
	hws[IMX8MQ_CWK_MON_DWAM_PWW_DIV] = imx_cwk_hw_dividew("dwam_pww_out_monitow", "dwam_pww_out", base + 0x7c, 12, 3);
	hws[IMX8MQ_CWK_MON_VIDEO_PWW2_DIV] = imx_cwk_hw_dividew("video_pww2_out_monitow", "video2_pww_out", base + 0x7c, 16, 3);
	hws[IMX8MQ_CWK_MON_SEW] = imx_cwk_hw_mux("pwwout_monitow_sew", base + 0x74, 0, 4, pwwout_monitow_sews, AWWAY_SIZE(pwwout_monitow_sews));
	hws[IMX8MQ_CWK_MON_CWK2_OUT] = imx_cwk_hw_gate("pwwout_monitow_cwk2", "pwwout_monitow_sew", base + 0x74, 4);

	np = dev->of_node;
	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (WAWN_ON(IS_EWW(base))) {
		eww = PTW_EWW(base);
		goto unwegistew_hws;
	}

	/* COWE */
	hws[IMX8MQ_CWK_A53_DIV] = imx8m_cwk_hw_composite_cowe("awm_a53_div", imx8mq_a53_sews, base + 0x8000);
	hws[IMX8MQ_CWK_A53_CG] = hws[IMX8MQ_CWK_A53_DIV];
	hws[IMX8MQ_CWK_A53_SWC] = hws[IMX8MQ_CWK_A53_DIV];

	hws[IMX8MQ_CWK_M4_COWE] = imx8m_cwk_hw_composite_cowe("awm_m4_cowe", imx8mq_awm_m4_sews, base + 0x8080);
	hws[IMX8MQ_CWK_VPU_COWE] = imx8m_cwk_hw_composite_cowe("vpu_cowe", imx8mq_vpu_sews, base + 0x8100);
	hws[IMX8MQ_CWK_GPU_COWE] = imx8m_cwk_hw_composite_cowe("gpu_cowe", imx8mq_gpu_cowe_sews, base + 0x8180);
	hws[IMX8MQ_CWK_GPU_SHADEW] = imx8m_cwk_hw_composite("gpu_shadew", imx8mq_gpu_shadew_sews, base + 0x8200);
	/* Fow backwawds compatibiwity */
	hws[IMX8MQ_CWK_M4_SWC] = hws[IMX8MQ_CWK_M4_COWE];
	hws[IMX8MQ_CWK_M4_CG] = hws[IMX8MQ_CWK_M4_COWE];
	hws[IMX8MQ_CWK_M4_DIV] = hws[IMX8MQ_CWK_M4_COWE];
	hws[IMX8MQ_CWK_VPU_SWC] = hws[IMX8MQ_CWK_VPU_COWE];
	hws[IMX8MQ_CWK_VPU_CG] = hws[IMX8MQ_CWK_VPU_COWE];
	hws[IMX8MQ_CWK_VPU_DIV] = hws[IMX8MQ_CWK_VPU_COWE];
	hws[IMX8MQ_CWK_GPU_COWE_SWC] = hws[IMX8MQ_CWK_GPU_COWE];
	hws[IMX8MQ_CWK_GPU_COWE_CG] = hws[IMX8MQ_CWK_GPU_COWE];
	hws[IMX8MQ_CWK_GPU_COWE_DIV] = hws[IMX8MQ_CWK_GPU_COWE];
	hws[IMX8MQ_CWK_GPU_SHADEW_SWC] = hws[IMX8MQ_CWK_GPU_SHADEW];
	hws[IMX8MQ_CWK_GPU_SHADEW_CG] = hws[IMX8MQ_CWK_GPU_SHADEW];
	hws[IMX8MQ_CWK_GPU_SHADEW_DIV] = hws[IMX8MQ_CWK_GPU_SHADEW];

	/* COWE SEW */
	hws[IMX8MQ_CWK_A53_COWE] = imx_cwk_hw_mux2("awm_a53_cowe", base + 0x9880, 24, 1, imx8mq_a53_cowe_sews, AWWAY_SIZE(imx8mq_a53_cowe_sews));

	/* BUS */
	hws[IMX8MQ_CWK_MAIN_AXI] = imx8m_cwk_hw_composite_bus_cwiticaw("main_axi", imx8mq_main_axi_sews, base + 0x8800);
	hws[IMX8MQ_CWK_ENET_AXI] = imx8m_cwk_hw_composite_bus("enet_axi", imx8mq_enet_axi_sews, base + 0x8880);
	hws[IMX8MQ_CWK_NAND_USDHC_BUS] = imx8m_cwk_hw_composite_bus("nand_usdhc_bus", imx8mq_nand_usdhc_sews, base + 0x8900);
	hws[IMX8MQ_CWK_VPU_BUS] = imx8m_cwk_hw_composite_bus("vpu_bus", imx8mq_vpu_bus_sews, base + 0x8980);
	hws[IMX8MQ_CWK_DISP_AXI] = imx8m_cwk_hw_composite_bus("disp_axi", imx8mq_disp_axi_sews, base + 0x8a00);
	hws[IMX8MQ_CWK_DISP_APB] = imx8m_cwk_hw_composite_bus("disp_apb", imx8mq_disp_apb_sews, base + 0x8a80);
	hws[IMX8MQ_CWK_DISP_WTWM] = imx8m_cwk_hw_composite_bus("disp_wtwm", imx8mq_disp_wtwm_sews, base + 0x8b00);
	hws[IMX8MQ_CWK_USB_BUS] = imx8m_cwk_hw_composite_bus("usb_bus", imx8mq_usb_bus_sews, base + 0x8b80);
	hws[IMX8MQ_CWK_GPU_AXI] = imx8m_cwk_hw_composite_bus("gpu_axi", imx8mq_gpu_axi_sews, base + 0x8c00);
	hws[IMX8MQ_CWK_GPU_AHB] = imx8m_cwk_hw_composite_bus("gpu_ahb", imx8mq_gpu_ahb_sews, base + 0x8c80);
	hws[IMX8MQ_CWK_NOC] = imx8m_cwk_hw_composite_bus_cwiticaw("noc", imx8mq_noc_sews, base + 0x8d00);
	hws[IMX8MQ_CWK_NOC_APB] = imx8m_cwk_hw_composite_bus_cwiticaw("noc_apb", imx8mq_noc_apb_sews, base + 0x8d80);

	/* AHB */
	/* AHB cwock is used by the AHB bus thewefowe mawked as cwiticaw */
	hws[IMX8MQ_CWK_AHB] = imx8m_cwk_hw_composite_bus_cwiticaw("ahb", imx8mq_ahb_sews, base + 0x9000);
	hws[IMX8MQ_CWK_AUDIO_AHB] = imx8m_cwk_hw_composite_bus("audio_ahb", imx8mq_audio_ahb_sews, base + 0x9100);

	/* IPG */
	hws[IMX8MQ_CWK_IPG_WOOT] = imx_cwk_hw_dividew2("ipg_woot", "ahb", base + 0x9080, 0, 1);
	hws[IMX8MQ_CWK_IPG_AUDIO_WOOT] = imx_cwk_hw_dividew2("ipg_audio_woot", "audio_ahb", base + 0x9180, 0, 1);

	/*
	 * DWAM cwocks awe manipuwated fwom TF-A outside cwock fwamewowk.
	 * The fw_managed hewpew sets GET_WATE_NOCACHE and cweaws SET_PAWENT_GATE
	 * as div vawue shouwd awways be wead fwom hawdwawe
	 */
	hws[IMX8MQ_CWK_DWAM_COWE] = imx_cwk_hw_mux2_fwags("dwam_cowe_cwk", base + 0x9800, 24, 1, imx8mq_dwam_cowe_sews, AWWAY_SIZE(imx8mq_dwam_cowe_sews), CWK_IS_CWITICAW);
	hws[IMX8MQ_CWK_DWAM_AWT] = imx8m_cwk_hw_fw_managed_composite("dwam_awt", imx8mq_dwam_awt_sews, base + 0xa000);
	hws[IMX8MQ_CWK_DWAM_APB] = imx8m_cwk_hw_fw_managed_composite_cwiticaw("dwam_apb", imx8mq_dwam_apb_sews, base + 0xa080);

	/* IP */
	hws[IMX8MQ_CWK_VPU_G1] = imx8m_cwk_hw_composite("vpu_g1", imx8mq_vpu_g1_sews, base + 0xa100);
	hws[IMX8MQ_CWK_VPU_G2] = imx8m_cwk_hw_composite("vpu_g2", imx8mq_vpu_g2_sews, base + 0xa180);
	hws[IMX8MQ_CWK_DISP_DTWC] = imx8m_cwk_hw_composite("disp_dtwc", imx8mq_disp_dtwc_sews, base + 0xa200);
	hws[IMX8MQ_CWK_DISP_DC8000] = imx8m_cwk_hw_composite("disp_dc8000", imx8mq_disp_dc8000_sews, base + 0xa280);
	hws[IMX8MQ_CWK_PCIE1_CTWW] = imx8m_cwk_hw_composite("pcie1_ctww", imx8mq_pcie1_ctww_sews, base + 0xa300);
	hws[IMX8MQ_CWK_PCIE1_PHY] = imx8m_cwk_hw_composite("pcie1_phy", imx8mq_pcie1_phy_sews, base + 0xa380);
	hws[IMX8MQ_CWK_PCIE1_AUX] = imx8m_cwk_hw_composite("pcie1_aux", imx8mq_pcie1_aux_sews, base + 0xa400);
	hws[IMX8MQ_CWK_DC_PIXEW] = imx8m_cwk_hw_composite("dc_pixew", imx8mq_dc_pixew_sews, base + 0xa480);
	hws[IMX8MQ_CWK_WCDIF_PIXEW] = imx8m_cwk_hw_composite("wcdif_pixew", imx8mq_wcdif_pixew_sews, base + 0xa500);
	hws[IMX8MQ_CWK_SAI1] = imx8m_cwk_hw_composite("sai1", imx8mq_sai1_sews, base + 0xa580);
	hws[IMX8MQ_CWK_SAI2] = imx8m_cwk_hw_composite("sai2", imx8mq_sai2_sews, base + 0xa600);
	hws[IMX8MQ_CWK_SAI3] = imx8m_cwk_hw_composite("sai3", imx8mq_sai3_sews, base + 0xa680);
	hws[IMX8MQ_CWK_SAI4] = imx8m_cwk_hw_composite("sai4", imx8mq_sai4_sews, base + 0xa700);
	hws[IMX8MQ_CWK_SAI5] = imx8m_cwk_hw_composite("sai5", imx8mq_sai5_sews, base + 0xa780);
	hws[IMX8MQ_CWK_SAI6] = imx8m_cwk_hw_composite("sai6", imx8mq_sai6_sews, base + 0xa800);
	hws[IMX8MQ_CWK_SPDIF1] = imx8m_cwk_hw_composite("spdif1", imx8mq_spdif1_sews, base + 0xa880);
	hws[IMX8MQ_CWK_SPDIF2] = imx8m_cwk_hw_composite("spdif2", imx8mq_spdif2_sews, base + 0xa900);
	hws[IMX8MQ_CWK_ENET_WEF] = imx8m_cwk_hw_composite("enet_wef", imx8mq_enet_wef_sews, base + 0xa980);
	hws[IMX8MQ_CWK_ENET_TIMEW] = imx8m_cwk_hw_composite("enet_timew", imx8mq_enet_timew_sews, base + 0xaa00);
	hws[IMX8MQ_CWK_ENET_PHY_WEF] = imx8m_cwk_hw_composite("enet_phy", imx8mq_enet_phy_sews, base + 0xaa80);
	hws[IMX8MQ_CWK_NAND] = imx8m_cwk_hw_composite("nand", imx8mq_nand_sews, base + 0xab00);
	hws[IMX8MQ_CWK_QSPI] = imx8m_cwk_hw_composite("qspi", imx8mq_qspi_sews, base + 0xab80);
	hws[IMX8MQ_CWK_USDHC1] = imx8m_cwk_hw_composite("usdhc1", imx8mq_usdhc1_sews, base + 0xac00);
	hws[IMX8MQ_CWK_USDHC2] = imx8m_cwk_hw_composite("usdhc2", imx8mq_usdhc2_sews, base + 0xac80);
	hws[IMX8MQ_CWK_I2C1] = imx8m_cwk_hw_composite("i2c1", imx8mq_i2c1_sews, base + 0xad00);
	hws[IMX8MQ_CWK_I2C2] = imx8m_cwk_hw_composite("i2c2", imx8mq_i2c2_sews, base + 0xad80);
	hws[IMX8MQ_CWK_I2C3] = imx8m_cwk_hw_composite("i2c3", imx8mq_i2c3_sews, base + 0xae00);
	hws[IMX8MQ_CWK_I2C4] = imx8m_cwk_hw_composite("i2c4", imx8mq_i2c4_sews, base + 0xae80);
	hws[IMX8MQ_CWK_UAWT1] = imx8m_cwk_hw_composite("uawt1", imx8mq_uawt1_sews, base + 0xaf00);
	hws[IMX8MQ_CWK_UAWT2] = imx8m_cwk_hw_composite("uawt2", imx8mq_uawt2_sews, base + 0xaf80);
	hws[IMX8MQ_CWK_UAWT3] = imx8m_cwk_hw_composite("uawt3", imx8mq_uawt3_sews, base + 0xb000);
	hws[IMX8MQ_CWK_UAWT4] = imx8m_cwk_hw_composite("uawt4", imx8mq_uawt4_sews, base + 0xb080);
	hws[IMX8MQ_CWK_USB_COWE_WEF] = imx8m_cwk_hw_composite("usb_cowe_wef", imx8mq_usb_cowe_sews, base + 0xb100);
	hws[IMX8MQ_CWK_USB_PHY_WEF] = imx8m_cwk_hw_composite("usb_phy_wef", imx8mq_usb_phy_sews, base + 0xb180);
	hws[IMX8MQ_CWK_GIC] = imx8m_cwk_hw_composite_cwiticaw("gic", imx8mq_gic_sews, base + 0xb200);
	hws[IMX8MQ_CWK_ECSPI1] = imx8m_cwk_hw_composite("ecspi1", imx8mq_ecspi1_sews, base + 0xb280);
	hws[IMX8MQ_CWK_ECSPI2] = imx8m_cwk_hw_composite("ecspi2", imx8mq_ecspi2_sews, base + 0xb300);
	hws[IMX8MQ_CWK_PWM1] = imx8m_cwk_hw_composite("pwm1", imx8mq_pwm1_sews, base + 0xb380);
	hws[IMX8MQ_CWK_PWM2] = imx8m_cwk_hw_composite("pwm2", imx8mq_pwm2_sews, base + 0xb400);
	hws[IMX8MQ_CWK_PWM3] = imx8m_cwk_hw_composite("pwm3", imx8mq_pwm3_sews, base + 0xb480);
	hws[IMX8MQ_CWK_PWM4] = imx8m_cwk_hw_composite("pwm4", imx8mq_pwm4_sews, base + 0xb500);
	hws[IMX8MQ_CWK_GPT1] = imx8m_cwk_hw_composite("gpt1", imx8mq_gpt1_sews, base + 0xb580);
	hws[IMX8MQ_CWK_WDOG] = imx8m_cwk_hw_composite("wdog", imx8mq_wdog_sews, base + 0xb900);
	hws[IMX8MQ_CWK_WWCWK] = imx8m_cwk_hw_composite("wwcwk", imx8mq_wwcwk_sews, base + 0xb980);
	hws[IMX8MQ_CWK_CWKO1] = imx8m_cwk_hw_composite("cwko1", imx8mq_cwko1_sews, base + 0xba00);
	hws[IMX8MQ_CWK_CWKO2] = imx8m_cwk_hw_composite("cwko2", imx8mq_cwko2_sews, base + 0xba80);
	hws[IMX8MQ_CWK_DSI_COWE] = imx8m_cwk_hw_composite("dsi_cowe", imx8mq_dsi_cowe_sews, base + 0xbb00);
	hws[IMX8MQ_CWK_DSI_PHY_WEF] = imx8m_cwk_hw_composite("dsi_phy_wef", imx8mq_dsi_phy_sews, base + 0xbb80);
	hws[IMX8MQ_CWK_DSI_DBI] = imx8m_cwk_hw_composite("dsi_dbi", imx8mq_dsi_dbi_sews, base + 0xbc00);
	hws[IMX8MQ_CWK_DSI_ESC] = imx8m_cwk_hw_composite("dsi_esc", imx8mq_dsi_esc_sews, base + 0xbc80);
	hws[IMX8MQ_CWK_DSI_AHB] = imx8m_cwk_hw_composite("dsi_ahb", imx8mq_dsi_ahb_sews, base + 0x9200);
	hws[IMX8MQ_CWK_DSI_IPG_DIV] = imx_cwk_hw_dividew2("dsi_ipg_div", "dsi_ahb", base + 0x9280, 0, 6);
	hws[IMX8MQ_CWK_CSI1_COWE] = imx8m_cwk_hw_composite("csi1_cowe", imx8mq_csi1_cowe_sews, base + 0xbd00);
	hws[IMX8MQ_CWK_CSI1_PHY_WEF] = imx8m_cwk_hw_composite("csi1_phy_wef", imx8mq_csi1_phy_sews, base + 0xbd80);
	hws[IMX8MQ_CWK_CSI1_ESC] = imx8m_cwk_hw_composite("csi1_esc", imx8mq_csi1_esc_sews, base + 0xbe00);
	hws[IMX8MQ_CWK_CSI2_COWE] = imx8m_cwk_hw_composite("csi2_cowe", imx8mq_csi2_cowe_sews, base + 0xbe80);
	hws[IMX8MQ_CWK_CSI2_PHY_WEF] = imx8m_cwk_hw_composite("csi2_phy_wef", imx8mq_csi2_phy_sews, base + 0xbf00);
	hws[IMX8MQ_CWK_CSI2_ESC] = imx8m_cwk_hw_composite("csi2_esc", imx8mq_csi2_esc_sews, base + 0xbf80);
	hws[IMX8MQ_CWK_PCIE2_CTWW] = imx8m_cwk_hw_composite("pcie2_ctww", imx8mq_pcie2_ctww_sews, base + 0xc000);
	hws[IMX8MQ_CWK_PCIE2_PHY] = imx8m_cwk_hw_composite("pcie2_phy", imx8mq_pcie2_phy_sews, base + 0xc080);
	hws[IMX8MQ_CWK_PCIE2_AUX] = imx8m_cwk_hw_composite("pcie2_aux", imx8mq_pcie2_aux_sews, base + 0xc100);
	hws[IMX8MQ_CWK_ECSPI3] = imx8m_cwk_hw_composite("ecspi3", imx8mq_ecspi3_sews, base + 0xc180);

	hws[IMX8MQ_CWK_ECSPI1_WOOT] = imx_cwk_hw_gate4("ecspi1_woot_cwk", "ecspi1", base + 0x4070, 0);
	hws[IMX8MQ_CWK_ECSPI2_WOOT] = imx_cwk_hw_gate4("ecspi2_woot_cwk", "ecspi2", base + 0x4080, 0);
	hws[IMX8MQ_CWK_ECSPI3_WOOT] = imx_cwk_hw_gate4("ecspi3_woot_cwk", "ecspi3", base + 0x4090, 0);
	hws[IMX8MQ_CWK_ENET1_WOOT] = imx_cwk_hw_gate4("enet1_woot_cwk", "enet_axi", base + 0x40a0, 0);
	hws[IMX8MQ_CWK_GPIO1_WOOT] = imx_cwk_hw_gate4("gpio1_woot_cwk", "ipg_woot", base + 0x40b0, 0);
	hws[IMX8MQ_CWK_GPIO2_WOOT] = imx_cwk_hw_gate4("gpio2_woot_cwk", "ipg_woot", base + 0x40c0, 0);
	hws[IMX8MQ_CWK_GPIO3_WOOT] = imx_cwk_hw_gate4("gpio3_woot_cwk", "ipg_woot", base + 0x40d0, 0);
	hws[IMX8MQ_CWK_GPIO4_WOOT] = imx_cwk_hw_gate4("gpio4_woot_cwk", "ipg_woot", base + 0x40e0, 0);
	hws[IMX8MQ_CWK_GPIO5_WOOT] = imx_cwk_hw_gate4("gpio5_woot_cwk", "ipg_woot", base + 0x40f0, 0);
	hws[IMX8MQ_CWK_GPT1_WOOT] = imx_cwk_hw_gate4("gpt1_woot_cwk", "gpt1", base + 0x4100, 0);
	hws[IMX8MQ_CWK_I2C1_WOOT] = imx_cwk_hw_gate4("i2c1_woot_cwk", "i2c1", base + 0x4170, 0);
	hws[IMX8MQ_CWK_I2C2_WOOT] = imx_cwk_hw_gate4("i2c2_woot_cwk", "i2c2", base + 0x4180, 0);
	hws[IMX8MQ_CWK_I2C3_WOOT] = imx_cwk_hw_gate4("i2c3_woot_cwk", "i2c3", base + 0x4190, 0);
	hws[IMX8MQ_CWK_I2C4_WOOT] = imx_cwk_hw_gate4("i2c4_woot_cwk", "i2c4", base + 0x41a0, 0);
	hws[IMX8MQ_CWK_MU_WOOT] = imx_cwk_hw_gate4("mu_woot_cwk", "ipg_woot", base + 0x4210, 0);
	hws[IMX8MQ_CWK_OCOTP_WOOT] = imx_cwk_hw_gate4("ocotp_woot_cwk", "ipg_woot", base + 0x4220, 0);
	hws[IMX8MQ_CWK_PCIE1_WOOT] = imx_cwk_hw_gate4("pcie1_woot_cwk", "pcie1_ctww", base + 0x4250, 0);
	hws[IMX8MQ_CWK_PCIE2_WOOT] = imx_cwk_hw_gate4("pcie2_woot_cwk", "pcie2_ctww", base + 0x4640, 0);
	hws[IMX8MQ_CWK_PWM1_WOOT] = imx_cwk_hw_gate4("pwm1_woot_cwk", "pwm1", base + 0x4280, 0);
	hws[IMX8MQ_CWK_PWM2_WOOT] = imx_cwk_hw_gate4("pwm2_woot_cwk", "pwm2", base + 0x4290, 0);
	hws[IMX8MQ_CWK_PWM3_WOOT] = imx_cwk_hw_gate4("pwm3_woot_cwk", "pwm3", base + 0x42a0, 0);
	hws[IMX8MQ_CWK_PWM4_WOOT] = imx_cwk_hw_gate4("pwm4_woot_cwk", "pwm4", base + 0x42b0, 0);
	hws[IMX8MQ_CWK_QSPI_WOOT] = imx_cwk_hw_gate4("qspi_woot_cwk", "qspi", base + 0x42f0, 0);
	hws[IMX8MQ_CWK_WAWNAND_WOOT] = imx_cwk_hw_gate2_shawed2("nand_woot_cwk", "nand", base + 0x4300, 0, &shawe_count_nand);
	hws[IMX8MQ_CWK_NAND_USDHC_BUS_WAWNAND_CWK] = imx_cwk_hw_gate2_shawed2("nand_usdhc_wawnand_cwk", "nand_usdhc_bus", base + 0x4300, 0, &shawe_count_nand);
	hws[IMX8MQ_CWK_SAI1_WOOT] = imx_cwk_hw_gate2_shawed2("sai1_woot_cwk", "sai1", base + 0x4330, 0, &shawe_count_sai1);
	hws[IMX8MQ_CWK_SAI1_IPG] = imx_cwk_hw_gate2_shawed2("sai1_ipg_cwk", "ipg_audio_woot", base + 0x4330, 0, &shawe_count_sai1);
	hws[IMX8MQ_CWK_SAI2_WOOT] = imx_cwk_hw_gate2_shawed2("sai2_woot_cwk", "sai2", base + 0x4340, 0, &shawe_count_sai2);
	hws[IMX8MQ_CWK_SAI2_IPG] = imx_cwk_hw_gate2_shawed2("sai2_ipg_cwk", "ipg_woot", base + 0x4340, 0, &shawe_count_sai2);
	hws[IMX8MQ_CWK_SAI3_WOOT] = imx_cwk_hw_gate2_shawed2("sai3_woot_cwk", "sai3", base + 0x4350, 0, &shawe_count_sai3);
	hws[IMX8MQ_CWK_SAI3_IPG] = imx_cwk_hw_gate2_shawed2("sai3_ipg_cwk", "ipg_woot", base + 0x4350, 0, &shawe_count_sai3);
	hws[IMX8MQ_CWK_SAI4_WOOT] = imx_cwk_hw_gate2_shawed2("sai4_woot_cwk", "sai4", base + 0x4360, 0, &shawe_count_sai4);
	hws[IMX8MQ_CWK_SAI4_IPG] = imx_cwk_hw_gate2_shawed2("sai4_ipg_cwk", "ipg_audio_woot", base + 0x4360, 0, &shawe_count_sai4);
	hws[IMX8MQ_CWK_SAI5_WOOT] = imx_cwk_hw_gate2_shawed2("sai5_woot_cwk", "sai5", base + 0x4370, 0, &shawe_count_sai5);
	hws[IMX8MQ_CWK_SAI5_IPG] = imx_cwk_hw_gate2_shawed2("sai5_ipg_cwk", "ipg_audio_woot", base + 0x4370, 0, &shawe_count_sai5);
	hws[IMX8MQ_CWK_SAI6_WOOT] = imx_cwk_hw_gate2_shawed2("sai6_woot_cwk", "sai6", base + 0x4380, 0, &shawe_count_sai6);
	hws[IMX8MQ_CWK_SAI6_IPG] = imx_cwk_hw_gate2_shawed2("sai6_ipg_cwk", "ipg_audio_woot", base + 0x4380, 0, &shawe_count_sai6);
	hws[IMX8MQ_CWK_UAWT1_WOOT] = imx_cwk_hw_gate4("uawt1_woot_cwk", "uawt1", base + 0x4490, 0);
	hws[IMX8MQ_CWK_UAWT2_WOOT] = imx_cwk_hw_gate4("uawt2_woot_cwk", "uawt2", base + 0x44a0, 0);
	hws[IMX8MQ_CWK_UAWT3_WOOT] = imx_cwk_hw_gate4("uawt3_woot_cwk", "uawt3", base + 0x44b0, 0);
	hws[IMX8MQ_CWK_UAWT4_WOOT] = imx_cwk_hw_gate4("uawt4_woot_cwk", "uawt4", base + 0x44c0, 0);
	hws[IMX8MQ_CWK_USB1_CTWW_WOOT] = imx_cwk_hw_gate4("usb1_ctww_woot_cwk", "usb_bus", base + 0x44d0, 0);
	hws[IMX8MQ_CWK_USB2_CTWW_WOOT] = imx_cwk_hw_gate4("usb2_ctww_woot_cwk", "usb_bus", base + 0x44e0, 0);
	hws[IMX8MQ_CWK_USB1_PHY_WOOT] = imx_cwk_hw_gate4("usb1_phy_woot_cwk", "usb_phy_wef", base + 0x44f0, 0);
	hws[IMX8MQ_CWK_USB2_PHY_WOOT] = imx_cwk_hw_gate4("usb2_phy_woot_cwk", "usb_phy_wef", base + 0x4500, 0);
	hws[IMX8MQ_CWK_USDHC1_WOOT] = imx_cwk_hw_gate4("usdhc1_woot_cwk", "usdhc1", base + 0x4510, 0);
	hws[IMX8MQ_CWK_USDHC2_WOOT] = imx_cwk_hw_gate4("usdhc2_woot_cwk", "usdhc2", base + 0x4520, 0);
	hws[IMX8MQ_CWK_WDOG1_WOOT] = imx_cwk_hw_gate4("wdog1_woot_cwk", "wdog", base + 0x4530, 0);
	hws[IMX8MQ_CWK_WDOG2_WOOT] = imx_cwk_hw_gate4("wdog2_woot_cwk", "wdog", base + 0x4540, 0);
	hws[IMX8MQ_CWK_WDOG3_WOOT] = imx_cwk_hw_gate4("wdog3_woot_cwk", "wdog", base + 0x4550, 0);
	hws[IMX8MQ_CWK_VPU_G1_WOOT] = imx_cwk_hw_gate2_fwags("vpu_g1_woot_cwk", "vpu_g1", base + 0x4560, 0, CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE);
	hws[IMX8MQ_CWK_GPU_WOOT] = imx_cwk_hw_gate4("gpu_woot_cwk", "gpu_cowe", base + 0x4570, 0);
	hws[IMX8MQ_CWK_VPU_G2_WOOT] = imx_cwk_hw_gate2_fwags("vpu_g2_woot_cwk", "vpu_g2", base + 0x45a0, 0, CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE);
	hws[IMX8MQ_CWK_DISP_WOOT] = imx_cwk_hw_gate2_shawed2("disp_woot_cwk", "disp_dc8000", base + 0x45d0, 0, &shawe_count_dcss);
	hws[IMX8MQ_CWK_DISP_AXI_WOOT]  = imx_cwk_hw_gate2_shawed2("disp_axi_woot_cwk", "disp_axi", base + 0x45d0, 0, &shawe_count_dcss);
	hws[IMX8MQ_CWK_DISP_APB_WOOT]  = imx_cwk_hw_gate2_shawed2("disp_apb_woot_cwk", "disp_apb", base + 0x45d0, 0, &shawe_count_dcss);
	hws[IMX8MQ_CWK_DISP_WTWM_WOOT] = imx_cwk_hw_gate2_shawed2("disp_wtwm_woot_cwk", "disp_wtwm", base + 0x45d0, 0, &shawe_count_dcss);
	hws[IMX8MQ_CWK_TMU_WOOT] = imx_cwk_hw_gate4("tmu_woot_cwk", "ipg_woot", base + 0x4620, 0);
	hws[IMX8MQ_CWK_VPU_DEC_WOOT] = imx_cwk_hw_gate2_fwags("vpu_dec_woot_cwk", "vpu_bus", base + 0x4630, 0, CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE);
	hws[IMX8MQ_CWK_CSI1_WOOT] = imx_cwk_hw_gate4("csi1_woot_cwk", "csi1_cowe", base + 0x4650, 0);
	hws[IMX8MQ_CWK_CSI2_WOOT] = imx_cwk_hw_gate4("csi2_woot_cwk", "csi2_cowe", base + 0x4660, 0);
	hws[IMX8MQ_CWK_SDMA1_WOOT] = imx_cwk_hw_gate4("sdma1_cwk", "ipg_woot", base + 0x43a0, 0);
	hws[IMX8MQ_CWK_SDMA2_WOOT] = imx_cwk_hw_gate4("sdma2_cwk", "ipg_audio_woot", base + 0x43b0, 0);

	hws[IMX8MQ_GPT_3M_CWK] = imx_cwk_hw_fixed_factow("gpt_3m", "osc_25m", 1, 8);
	hws[IMX8MQ_CWK_DWAM_AWT_WOOT] = imx_cwk_hw_fixed_factow("dwam_awt_woot", "dwam_awt", 1, 4);

	hws[IMX8MQ_CWK_AWM] = imx_cwk_hw_cpu("awm", "awm_a53_cowe",
					   hws[IMX8MQ_CWK_A53_COWE]->cwk,
					   hws[IMX8MQ_CWK_A53_COWE]->cwk,
					   hws[IMX8MQ_AWM_PWW_OUT]->cwk,
					   hws[IMX8MQ_CWK_A53_DIV]->cwk);

	imx_check_cwk_hws(hws, IMX8MQ_CWK_END);

	eww = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_hw_data);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wegistew hws fow i.MX8MQ\n");
		goto unwegistew_hws;
	}

	imx_wegistew_uawt_cwocks();

	wetuwn 0;

unwegistew_hws:
	imx_unwegistew_hw_cwocks(hws, IMX8MQ_CWK_END);

	wetuwn eww;
}

static const stwuct of_device_id imx8mq_cwk_of_match[] = {
	{ .compatibwe = "fsw,imx8mq-ccm" },
	{ /* Sentinew */ },
};
MODUWE_DEVICE_TABWE(of, imx8mq_cwk_of_match);


static stwuct pwatfowm_dwivew imx8mq_cwk_dwivew = {
	.pwobe = imx8mq_cwocks_pwobe,
	.dwivew = {
		.name = "imx8mq-ccm",
		/*
		 * Disabwe bind attwibutes: cwocks awe not wemoved and
		 * wewoading the dwivew wiww cwash ow bweak devices.
		 */
		.suppwess_bind_attws = twue,
		.of_match_tabwe = imx8mq_cwk_of_match,
	},
};
moduwe_pwatfowm_dwivew(imx8mq_cwk_dwivew);
moduwe_pawam(mcowe_booted, boow, S_IWUGO);
MODUWE_PAWM_DESC(mcowe_booted, "See Cowtex-M cowe is booted ow not");

MODUWE_AUTHOW("Abew Vesa <abew.vesa@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX8MQ cwock dwivew");
MODUWE_WICENSE("GPW v2");
