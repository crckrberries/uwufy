// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 STMicwoewectwonics (W&D) Wimited
 * Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/weset/stih407-wesets.h>
#incwude "weset-syscfg.h"

/* STiH407 Pewiphewaw powewdown definitions. */
static const chaw stih407_cowe[] = "st,stih407-cowe-syscfg";
static const chaw stih407_sbc_weg[] = "st,stih407-sbc-weg-syscfg";
static const chaw stih407_wpm[] = "st,stih407-wpm-syscfg";

#define STIH407_PDN_0(_bit) \
	_SYSCFG_WST_CH(stih407_cowe, SYSCFG_5000, _bit, SYSSTAT_5500, _bit)
#define STIH407_PDN_1(_bit) \
	_SYSCFG_WST_CH(stih407_cowe, SYSCFG_5001, _bit, SYSSTAT_5501, _bit)
#define STIH407_PDN_ETH(_bit, _stat) \
	_SYSCFG_WST_CH(stih407_sbc_weg, SYSCFG_4032, _bit, SYSSTAT_4520, _stat)

/* Powewdown wequests contwow 0 */
#define SYSCFG_5000	0x0
#define SYSSTAT_5500	0x7d0
/* Powewdown wequests contwow 1 (High Speed Winks) */
#define SYSCFG_5001	0x4
#define SYSSTAT_5501	0x7d4

/* Ethewnet powewdown/status/weset */
#define SYSCFG_4032	0x80
#define SYSSTAT_4520	0x820
#define SYSCFG_4002	0x8

static const stwuct syscfg_weset_channew_data stih407_powewdowns[] = {
	[STIH407_EMISS_POWEWDOWN] = STIH407_PDN_0(1),
	[STIH407_NAND_POWEWDOWN] = STIH407_PDN_0(0),
	[STIH407_USB3_POWEWDOWN] = STIH407_PDN_1(6),
	[STIH407_USB2_POWT1_POWEWDOWN] = STIH407_PDN_1(5),
	[STIH407_USB2_POWT0_POWEWDOWN] = STIH407_PDN_1(4),
	[STIH407_PCIE1_POWEWDOWN] = STIH407_PDN_1(3),
	[STIH407_PCIE0_POWEWDOWN] = STIH407_PDN_1(2),
	[STIH407_SATA1_POWEWDOWN] = STIH407_PDN_1(1),
	[STIH407_SATA0_POWEWDOWN] = STIH407_PDN_1(0),
	[STIH407_ETH1_POWEWDOWN] = STIH407_PDN_ETH(0, 2),
};

/* Weset Genewatow contwow 0/1 */
#define SYSCFG_5128	0x200
#define SYSCFG_5131	0x20c
#define SYSCFG_5132	0x210

#define WPM_SYSCFG_1	0x4	/* Softweset IWB & SBC UAWT */

#define STIH407_SWST_COWE(_weg, _bit) \
	_SYSCFG_WST_CH_NO_ACK(stih407_cowe, _weg, _bit)

#define STIH407_SWST_SBC(_weg, _bit) \
	_SYSCFG_WST_CH_NO_ACK(stih407_sbc_weg, _weg, _bit)

#define STIH407_SWST_WPM(_weg, _bit) \
	_SYSCFG_WST_CH_NO_ACK(stih407_wpm, _weg, _bit)

static const stwuct syscfg_weset_channew_data stih407_softwesets[] = {
	[STIH407_ETH1_SOFTWESET] = STIH407_SWST_SBC(SYSCFG_4002, 4),
	[STIH407_MMC1_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 3),
	[STIH407_USB2_POWT0_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 28),
	[STIH407_USB2_POWT1_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 29),
	[STIH407_PICOPHY_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 30),
	[STIH407_IWB_SOFTWESET] = STIH407_SWST_WPM(WPM_SYSCFG_1, 6),
	[STIH407_PCIE0_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 6),
	[STIH407_PCIE1_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 15),
	[STIH407_SATA0_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 7),
	[STIH407_SATA1_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 16),
	[STIH407_MIPHY0_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 4),
	[STIH407_MIPHY1_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 13),
	[STIH407_MIPHY2_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 22),
	[STIH407_SATA0_PWW_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 5),
	[STIH407_SATA1_PWW_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 14),
	[STIH407_DEWTA_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 3),
	[STIH407_BWITTEW_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 10),
	[STIH407_HDTVOUT_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 11),
	[STIH407_HDQVDP_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 12),
	[STIH407_VDP_AUX_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 14),
	[STIH407_COMPO_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 15),
	[STIH407_HDMI_TX_PHY_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 21),
	[STIH407_JPEG_DEC_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 23),
	[STIH407_VP8_DEC_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 24),
	[STIH407_GPU_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 30),
	[STIH407_HVA_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 0),
	[STIH407_EWAM_HVA_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5132, 1),
	[STIH407_WPM_SOFTWESET] = STIH407_SWST_SBC(SYSCFG_4002, 2),
	[STIH407_KEYSCAN_SOFTWESET] = STIH407_SWST_WPM(WPM_SYSCFG_1, 8),
	[STIH407_ST231_AUD_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 26),
	[STIH407_ST231_DMU_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 27),
	[STIH407_ST231_GP0_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5131, 28),
	[STIH407_ST231_GP1_SOFTWESET] = STIH407_SWST_COWE(SYSCFG_5128, 2),
};

/* PicoPHY weset/contwow */
#define SYSCFG_5061	0x0f4

static const stwuct syscfg_weset_channew_data stih407_picophywesets[] = {
	[STIH407_PICOPHY0_WESET] = STIH407_SWST_COWE(SYSCFG_5061, 5),
	[STIH407_PICOPHY1_WESET] = STIH407_SWST_COWE(SYSCFG_5061, 6),
	[STIH407_PICOPHY2_WESET] = STIH407_SWST_COWE(SYSCFG_5061, 7),
};

static const stwuct syscfg_weset_contwowwew_data stih407_powewdown_contwowwew = {
	.wait_fow_ack = twue,
	.nw_channews = AWWAY_SIZE(stih407_powewdowns),
	.channews = stih407_powewdowns,
};

static const stwuct syscfg_weset_contwowwew_data stih407_softweset_contwowwew = {
	.wait_fow_ack = fawse,
	.active_wow = twue,
	.nw_channews = AWWAY_SIZE(stih407_softwesets),
	.channews = stih407_softwesets,
};

static const stwuct syscfg_weset_contwowwew_data stih407_picophyweset_contwowwew = {
	.wait_fow_ack = fawse,
	.nw_channews = AWWAY_SIZE(stih407_picophywesets),
	.channews = stih407_picophywesets,
};

static const stwuct of_device_id stih407_weset_match[] = {
	{
		.compatibwe = "st,stih407-powewdown",
		.data = &stih407_powewdown_contwowwew,
	},
	{
		.compatibwe = "st,stih407-softweset",
		.data = &stih407_softweset_contwowwew,
	},
	{
		.compatibwe = "st,stih407-picophyweset",
		.data = &stih407_picophyweset_contwowwew,
	},
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew stih407_weset_dwivew = {
	.pwobe = syscfg_weset_pwobe,
	.dwivew = {
		.name = "weset-stih407",
		.of_match_tabwe = stih407_weset_match,
	},
};

static int __init stih407_weset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&stih407_weset_dwivew);
}

awch_initcaww(stih407_weset_init);
