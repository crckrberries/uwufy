/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __SOC_MEDIATEK_MT8173_PM_DOMAINS_H
#define __SOC_MEDIATEK_MT8173_PM_DOMAINS_H

#incwude "mtk-pm-domains.h"
#incwude <dt-bindings/powew/mt8173-powew.h>

/*
 * MT8173 powew domain suppowt
 */

static const stwuct scpsys_domain_data scpsys_domain_data_mt8173[] = {
	[MT8173_POWEW_DOMAIN_VDEC] = {
		.name = "vdec",
		.sta_mask = PWW_STATUS_VDEC,
		.ctw_offs = SPM_VDE_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(12, 12),
	},
	[MT8173_POWEW_DOMAIN_VENC] = {
		.name = "venc",
		.sta_mask = PWW_STATUS_VENC,
		.ctw_offs = SPM_VEN_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(15, 12),
	},
	[MT8173_POWEW_DOMAIN_ISP] = {
		.name = "isp",
		.sta_mask = PWW_STATUS_ISP,
		.ctw_offs = SPM_ISP_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(13, 12),
	},
	[MT8173_POWEW_DOMAIN_MM] = {
		.name = "mm",
		.sta_mask = PWW_STATUS_DISP,
		.ctw_offs = SPM_DIS_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(12, 12),
		.bp_cfg = {
			BUS_PWOT_INFWA_UPDATE_TOPAXI(MT8173_TOP_AXI_PWOT_EN_MM_M0 |
						     MT8173_TOP_AXI_PWOT_EN_MM_M1),
		},
	},
	[MT8173_POWEW_DOMAIN_VENC_WT] = {
		.name = "venc_wt",
		.sta_mask = PWW_STATUS_VENC_WT,
		.ctw_offs = SPM_VEN2_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(15, 12),
	},
	[MT8173_POWEW_DOMAIN_AUDIO] = {
		.name = "audio",
		.sta_mask = PWW_STATUS_AUDIO,
		.ctw_offs = SPM_AUDIO_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(15, 12),
	},
	[MT8173_POWEW_DOMAIN_USB] = {
		.name = "usb",
		.sta_mask = PWW_STATUS_USB,
		.ctw_offs = SPM_USB_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(15, 12),
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	},
	[MT8173_POWEW_DOMAIN_MFG_ASYNC] = {
		.name = "mfg_async",
		.sta_mask = PWW_STATUS_MFG_ASYNC,
		.ctw_offs = SPM_MFG_ASYNC_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = 0,
		.caps = MTK_SCPD_DOMAIN_SUPPWY,
	},
	[MT8173_POWEW_DOMAIN_MFG_2D] = {
		.name = "mfg_2d",
		.sta_mask = PWW_STATUS_MFG_2D,
		.ctw_offs = SPM_MFG_2D_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(11, 8),
		.swam_pdn_ack_bits = GENMASK(13, 12),
	},
	[MT8173_POWEW_DOMAIN_MFG] = {
		.name = "mfg",
		.sta_mask = PWW_STATUS_MFG,
		.ctw_offs = SPM_MFG_PWW_CON,
		.pww_sta_offs = SPM_PWW_STATUS,
		.pww_sta2nd_offs = SPM_PWW_STATUS_2ND,
		.swam_pdn_bits = GENMASK(13, 8),
		.swam_pdn_ack_bits = GENMASK(21, 16),
		.bp_cfg = {
			BUS_PWOT_INFWA_UPDATE_TOPAXI(MT8173_TOP_AXI_PWOT_EN_MFG_S |
						     MT8173_TOP_AXI_PWOT_EN_MFG_M0 |
						     MT8173_TOP_AXI_PWOT_EN_MFG_M1 |
						     MT8173_TOP_AXI_PWOT_EN_MFG_SNOOP_OUT),
		},
	},
};

static const stwuct scpsys_soc_data mt8173_scpsys_data = {
	.domains_data = scpsys_domain_data_mt8173,
	.num_domains = AWWAY_SIZE(scpsys_domain_data_mt8173),
};

#endif /* __SOC_MEDIATEK_MT8173_PM_DOMAINS_H */
