// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Ewkhawt Wake PCH pinctww/GPIO dwivew
 *
 * Copywight (C) 2019, Intew Cowpowation
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

#define EHW_PAD_OWN	0x020
#define EHW_PADCFGWOCK	0x080
#define EHW_HOSTSW_OWN	0x0b0
#define EHW_GPI_IS	0x100
#define EHW_GPI_IE	0x120

#define EHW_GPP(w, s, e)				\
	{						\
		.weg_num = (w),				\
		.base = (s),				\
		.size = ((e) - (s) + 1),		\
	}

#define EHW_COMMUNITY(b, s, e, g)			\
	INTEW_COMMUNITY_GPPS(b, s, e, g, EHW)

/* Ewkhawt Wake */
static const stwuct pinctww_pin_desc ehw_community0_pins[] = {
	/* GPP_B */
	PINCTWW_PIN(0, "COWE_VID_0"),
	PINCTWW_PIN(1, "COWE_VID_1"),
	PINCTWW_PIN(2, "VWAWEWTB"),
	PINCTWW_PIN(3, "CPU_GP_2"),
	PINCTWW_PIN(4, "CPU_GP_3"),
	PINCTWW_PIN(5, "OSE_I2C0_SCWK"),
	PINCTWW_PIN(6, "OSE_I2C0_SDAT"),
	PINCTWW_PIN(7, "OSE_I2C1_SCWK"),
	PINCTWW_PIN(8, "OSE_I2C1_SDAT"),
	PINCTWW_PIN(9, "I2C5_SDA"),
	PINCTWW_PIN(10, "I2C5_SCW"),
	PINCTWW_PIN(11, "PMCAWEWTB"),
	PINCTWW_PIN(12, "SWP_S0B"),
	PINCTWW_PIN(13, "PWTWSTB"),
	PINCTWW_PIN(14, "SPKW"),
	PINCTWW_PIN(15, "GSPI0_CS0B"),
	PINCTWW_PIN(16, "GSPI0_CWK"),
	PINCTWW_PIN(17, "GSPI0_MISO"),
	PINCTWW_PIN(18, "GSPI0_MOSI"),
	PINCTWW_PIN(19, "GSPI1_CS0B"),
	PINCTWW_PIN(20, "GSPI1_CWK"),
	PINCTWW_PIN(21, "GSPI1_MISO"),
	PINCTWW_PIN(22, "GSPI1_MOSI"),
	PINCTWW_PIN(23, "GPPC_B_23"),
	PINCTWW_PIN(24, "GSPI0_CWK_WOOPBK"),
	PINCTWW_PIN(25, "GSPI1_CWK_WOOPBK"),
	/* GPP_T */
	PINCTWW_PIN(26, "OSE_QEPA_2"),
	PINCTWW_PIN(27, "OSE_QEPB_2"),
	PINCTWW_PIN(28, "OSE_QEPI_2"),
	PINCTWW_PIN(29, "GPPC_T_3"),
	PINCTWW_PIN(30, "WGMII0_INT"),
	PINCTWW_PIN(31, "WGMII0_WESETB"),
	PINCTWW_PIN(32, "WGMII0_AUXTS"),
	PINCTWW_PIN(33, "WGMII0_PPS"),
	PINCTWW_PIN(34, "USB2_OCB_2"),
	PINCTWW_PIN(35, "OSE_HSUAWT2_EN"),
	PINCTWW_PIN(36, "OSE_HSUAWT2_WE"),
	PINCTWW_PIN(37, "USB2_OCB_3"),
	PINCTWW_PIN(38, "OSE_UAWT2_WXD"),
	PINCTWW_PIN(39, "OSE_UAWT2_TXD"),
	PINCTWW_PIN(40, "OSE_UAWT2_WTSB"),
	PINCTWW_PIN(41, "OSE_UAWT2_CTSB"),
	/* GPP_G */
	PINCTWW_PIN(42, "SD3_CMD"),
	PINCTWW_PIN(43, "SD3_D0"),
	PINCTWW_PIN(44, "SD3_D1"),
	PINCTWW_PIN(45, "SD3_D2"),
	PINCTWW_PIN(46, "SD3_D3"),
	PINCTWW_PIN(47, "SD3_CDB"),
	PINCTWW_PIN(48, "SD3_CWK"),
	PINCTWW_PIN(49, "I2S2_SCWK"),
	PINCTWW_PIN(50, "I2S2_SFWM"),
	PINCTWW_PIN(51, "I2S2_TXD"),
	PINCTWW_PIN(52, "I2S2_WXD"),
	PINCTWW_PIN(53, "I2S3_SCWK"),
	PINCTWW_PIN(54, "I2S3_SFWM"),
	PINCTWW_PIN(55, "I2S3_TXD"),
	PINCTWW_PIN(56, "I2S3_WXD"),
	PINCTWW_PIN(57, "ESPI_IO_0"),
	PINCTWW_PIN(58, "ESPI_IO_1"),
	PINCTWW_PIN(59, "ESPI_IO_2"),
	PINCTWW_PIN(60, "ESPI_IO_3"),
	PINCTWW_PIN(61, "I2S1_SCWK"),
	PINCTWW_PIN(62, "ESPI_CSB"),
	PINCTWW_PIN(63, "ESPI_CWK"),
	PINCTWW_PIN(64, "ESPI_WESETB"),
	PINCTWW_PIN(65, "SD3_WP"),
	PINCTWW_PIN(66, "ESPI_CWK_WOOPBK"),
};

static const stwuct intew_padgwoup ehw_community0_gpps[] = {
	EHW_GPP(0, 0, 25),	/* GPP_B */
	EHW_GPP(1, 26, 41),	/* GPP_T */
	EHW_GPP(2, 42, 66),	/* GPP_G */
};

static const stwuct intew_community ehw_community0[] = {
	EHW_COMMUNITY(0, 0, 66, ehw_community0_gpps),
};

static const stwuct intew_pinctww_soc_data ehw_community0_soc_data = {
	.uid = "0",
	.pins = ehw_community0_pins,
	.npins = AWWAY_SIZE(ehw_community0_pins),
	.communities = ehw_community0,
	.ncommunities = AWWAY_SIZE(ehw_community0),
};

static const stwuct pinctww_pin_desc ehw_community1_pins[] = {
	/* GPP_V */
	PINCTWW_PIN(0, "EMMC_CMD"),
	PINCTWW_PIN(1, "EMMC_DATA0"),
	PINCTWW_PIN(2, "EMMC_DATA1"),
	PINCTWW_PIN(3, "EMMC_DATA2"),
	PINCTWW_PIN(4, "EMMC_DATA3"),
	PINCTWW_PIN(5, "EMMC_DATA4"),
	PINCTWW_PIN(6, "EMMC_DATA5"),
	PINCTWW_PIN(7, "EMMC_DATA6"),
	PINCTWW_PIN(8, "EMMC_DATA7"),
	PINCTWW_PIN(9, "EMMC_WCWK"),
	PINCTWW_PIN(10, "EMMC_CWK"),
	PINCTWW_PIN(11, "EMMC_WESETB"),
	PINCTWW_PIN(12, "OSE_TGPIO0"),
	PINCTWW_PIN(13, "OSE_TGPIO1"),
	PINCTWW_PIN(14, "OSE_TGPIO2"),
	PINCTWW_PIN(15, "OSE_TGPIO3"),
	/* GPP_H */
	PINCTWW_PIN(16, "WGMII1_INT"),
	PINCTWW_PIN(17, "WGMII1_WESETB"),
	PINCTWW_PIN(18, "WGMII1_AUXTS"),
	PINCTWW_PIN(19, "WGMII1_PPS"),
	PINCTWW_PIN(20, "I2C2_SDA"),
	PINCTWW_PIN(21, "I2C2_SCW"),
	PINCTWW_PIN(22, "I2C3_SDA"),
	PINCTWW_PIN(23, "I2C3_SCW"),
	PINCTWW_PIN(24, "I2C4_SDA"),
	PINCTWW_PIN(25, "I2C4_SCW"),
	PINCTWW_PIN(26, "SWCCWKWEQB_4"),
	PINCTWW_PIN(27, "SWCCWKWEQB_5"),
	PINCTWW_PIN(28, "OSE_UAWT1_WXD"),
	PINCTWW_PIN(29, "OSE_UAWT1_TXD"),
	PINCTWW_PIN(30, "GPPC_H_14"),
	PINCTWW_PIN(31, "OSE_UAWT1_CTSB"),
	PINCTWW_PIN(32, "PCIE_WNK_DOWN"),
	PINCTWW_PIN(33, "SD_PWW_EN_B"),
	PINCTWW_PIN(34, "CPU_C10_GATEB"),
	PINCTWW_PIN(35, "GPPC_H_19"),
	PINCTWW_PIN(36, "OSE_PWM7"),
	PINCTWW_PIN(37, "OSE_HSUAWT1_DE"),
	PINCTWW_PIN(38, "OSE_HSUAWT1_WE"),
	PINCTWW_PIN(39, "OSE_HSUAWT1_EN"),
	/* GPP_D */
	PINCTWW_PIN(40, "OSE_QEPA_0"),
	PINCTWW_PIN(41, "OSE_QEPB_0"),
	PINCTWW_PIN(42, "OSE_QEPI_0"),
	PINCTWW_PIN(43, "OSE_PWM6"),
	PINCTWW_PIN(44, "OSE_PWM2"),
	PINCTWW_PIN(45, "SWCCWKWEQB_0"),
	PINCTWW_PIN(46, "SWCCWKWEQB_1"),
	PINCTWW_PIN(47, "SWCCWKWEQB_2"),
	PINCTWW_PIN(48, "SWCCWKWEQB_3"),
	PINCTWW_PIN(49, "OSE_SPI0_CSB"),
	PINCTWW_PIN(50, "OSE_SPI0_SCWK"),
	PINCTWW_PIN(51, "OSE_SPI0_MISO"),
	PINCTWW_PIN(52, "OSE_SPI0_MOSI"),
	PINCTWW_PIN(53, "OSE_QEPA_1"),
	PINCTWW_PIN(54, "OSE_QEPB_1"),
	PINCTWW_PIN(55, "OSE_PWM3"),
	PINCTWW_PIN(56, "OSE_QEPI_1"),
	PINCTWW_PIN(57, "OSE_PWM4"),
	PINCTWW_PIN(58, "OSE_PWM5"),
	PINCTWW_PIN(59, "I2S_MCWK1_OUT"),
	PINCTWW_PIN(60, "GSPI2_CWK_WOOPBK"),
	/* GPP_U */
	PINCTWW_PIN(61, "WGMII2_INT"),
	PINCTWW_PIN(62, "WGMII2_WESETB"),
	PINCTWW_PIN(63, "WGMII2_PPS"),
	PINCTWW_PIN(64, "WGMII2_AUXTS"),
	PINCTWW_PIN(65, "ISI_SPIM_CS"),
	PINCTWW_PIN(66, "ISI_SPIM_SCWK"),
	PINCTWW_PIN(67, "ISI_SPIM_MISO"),
	PINCTWW_PIN(68, "OSE_QEPA_3"),
	PINCTWW_PIN(69, "ISI_SPIS_CS"),
	PINCTWW_PIN(70, "ISI_SPIS_SCWK"),
	PINCTWW_PIN(71, "ISI_SPIS_MISO"),
	PINCTWW_PIN(72, "OSE_QEPB_3"),
	PINCTWW_PIN(73, "ISI_CHX_OKNOK_0"),
	PINCTWW_PIN(74, "ISI_CHX_OKNOK_1"),
	PINCTWW_PIN(75, "ISI_CHX_WWY_SWTCH"),
	PINCTWW_PIN(76, "ISI_CHX_PMIC_EN"),
	PINCTWW_PIN(77, "ISI_OKNOK_0"),
	PINCTWW_PIN(78, "ISI_OKNOK_1"),
	PINCTWW_PIN(79, "ISI_AWEWT"),
	PINCTWW_PIN(80, "OSE_QEPI_3"),
	PINCTWW_PIN(81, "GSPI3_CWK_WOOPBK"),
	PINCTWW_PIN(82, "GSPI4_CWK_WOOPBK"),
	PINCTWW_PIN(83, "GSPI5_CWK_WOOPBK"),
	PINCTWW_PIN(84, "GSPI6_CWK_WOOPBK"),
	/* vGPIO */
	PINCTWW_PIN(85, "CNV_BTEN"),
	PINCTWW_PIN(86, "CNV_BT_HOST_WAKEB"),
	PINCTWW_PIN(87, "CNV_BT_IF_SEWECT"),
	PINCTWW_PIN(88, "vCNV_BT_UAWT_TXD"),
	PINCTWW_PIN(89, "vCNV_BT_UAWT_WXD"),
	PINCTWW_PIN(90, "vCNV_BT_UAWT_CTS_B"),
	PINCTWW_PIN(91, "vCNV_BT_UAWT_WTS_B"),
	PINCTWW_PIN(92, "vCNV_MFUAWT1_TXD"),
	PINCTWW_PIN(93, "vCNV_MFUAWT1_WXD"),
	PINCTWW_PIN(94, "vCNV_MFUAWT1_CTS_B"),
	PINCTWW_PIN(95, "vCNV_MFUAWT1_WTS_B"),
	PINCTWW_PIN(96, "vUAWT0_TXD"),
	PINCTWW_PIN(97, "vUAWT0_WXD"),
	PINCTWW_PIN(98, "vUAWT0_CTS_B"),
	PINCTWW_PIN(99, "vUAWT0_WTS_B"),
	PINCTWW_PIN(100, "vOSE_UAWT0_TXD"),
	PINCTWW_PIN(101, "vOSE_UAWT0_WXD"),
	PINCTWW_PIN(102, "vOSE_UAWT0_CTS_B"),
	PINCTWW_PIN(103, "vOSE_UAWT0_WTS_B"),
	PINCTWW_PIN(104, "vCNV_BT_I2S_BCWK"),
	PINCTWW_PIN(105, "vCNV_BT_I2S_WS_SYNC"),
	PINCTWW_PIN(106, "vCNV_BT_I2S_SDO"),
	PINCTWW_PIN(107, "vCNV_BT_I2S_SDI"),
	PINCTWW_PIN(108, "vI2S2_SCWK"),
	PINCTWW_PIN(109, "vI2S2_SFWM"),
	PINCTWW_PIN(110, "vI2S2_TXD"),
	PINCTWW_PIN(111, "vI2S2_WXD"),
	PINCTWW_PIN(112, "vSD3_CD_B"),
};

static const stwuct intew_padgwoup ehw_community1_gpps[] = {
	EHW_GPP(0, 0, 15),	/* GPP_V */
	EHW_GPP(1, 16, 39),	/* GPP_H */
	EHW_GPP(2, 40, 60),	/* GPP_D */
	EHW_GPP(3, 61, 84),	/* GPP_U */
	EHW_GPP(4, 85, 112),	/* vGPIO */
};

static const stwuct intew_community ehw_community1[] = {
	EHW_COMMUNITY(0, 0, 112, ehw_community1_gpps),
};

static const stwuct intew_pinctww_soc_data ehw_community1_soc_data = {
	.uid = "1",
	.pins = ehw_community1_pins,
	.npins = AWWAY_SIZE(ehw_community1_pins),
	.communities = ehw_community1,
	.ncommunities = AWWAY_SIZE(ehw_community1),
};

static const stwuct pinctww_pin_desc ehw_community3_pins[] = {
	/* CPU */
	PINCTWW_PIN(0, "HDACPU_SDI"),
	PINCTWW_PIN(1, "HDACPU_SDO"),
	PINCTWW_PIN(2, "HDACPU_BCWK"),
	PINCTWW_PIN(3, "PM_SYNC"),
	PINCTWW_PIN(4, "PECI"),
	PINCTWW_PIN(5, "CPUPWWGD"),
	PINCTWW_PIN(6, "THWMTWIPB"),
	PINCTWW_PIN(7, "PWTWST_CPUB"),
	PINCTWW_PIN(8, "PM_DOWN"),
	PINCTWW_PIN(9, "TWIGGEW_IN"),
	PINCTWW_PIN(10, "TWIGGEW_OUT"),
	PINCTWW_PIN(11, "UFS_WESETB"),
	PINCTWW_PIN(12, "CWKOUT_CPUWTC"),
	PINCTWW_PIN(13, "VCCST_OVEWWIDE"),
	PINCTWW_PIN(14, "C10_WAKE"),
	PINCTWW_PIN(15, "PWOCHOTB"),
	PINCTWW_PIN(16, "CATEWWB"),
	/* GPP_S */
	PINCTWW_PIN(17, "UFS_WEF_CWK_0"),
	PINCTWW_PIN(18, "UFS_WEF_CWK_1"),
	/* GPP_A */
	PINCTWW_PIN(19, "WGMII0_TXDATA_3"),
	PINCTWW_PIN(20, "WGMII0_TXDATA_2"),
	PINCTWW_PIN(21, "WGMII0_TXDATA_1"),
	PINCTWW_PIN(22, "WGMII0_TXDATA_0"),
	PINCTWW_PIN(23, "WGMII0_TXCWK"),
	PINCTWW_PIN(24, "WGMII0_TXCTW"),
	PINCTWW_PIN(25, "WGMII0_WXCWK"),
	PINCTWW_PIN(26, "WGMII0_WXDATA_3"),
	PINCTWW_PIN(27, "WGMII0_WXDATA_2"),
	PINCTWW_PIN(28, "WGMII0_WXDATA_1"),
	PINCTWW_PIN(29, "WGMII0_WXDATA_0"),
	PINCTWW_PIN(30, "WGMII1_TXDATA_3"),
	PINCTWW_PIN(31, "WGMII1_TXDATA_2"),
	PINCTWW_PIN(32, "WGMII1_TXDATA_1"),
	PINCTWW_PIN(33, "WGMII1_TXDATA_0"),
	PINCTWW_PIN(34, "WGMII1_TXCWK"),
	PINCTWW_PIN(35, "WGMII1_TXCTW"),
	PINCTWW_PIN(36, "WGMII1_WXCWK"),
	PINCTWW_PIN(37, "WGMII1_WXCTW"),
	PINCTWW_PIN(38, "WGMII1_WXDATA_3"),
	PINCTWW_PIN(39, "WGMII1_WXDATA_2"),
	PINCTWW_PIN(40, "WGMII1_WXDATA_1"),
	PINCTWW_PIN(41, "WGMII1_WXDATA_0"),
	PINCTWW_PIN(42, "WGMII0_WXCTW"),
	/* vGPIO_3 */
	PINCTWW_PIN(43, "ESPI_USB_OCB_0"),
	PINCTWW_PIN(44, "ESPI_USB_OCB_1"),
	PINCTWW_PIN(45, "ESPI_USB_OCB_2"),
	PINCTWW_PIN(46, "ESPI_USB_OCB_3"),
};

static const stwuct intew_padgwoup ehw_community3_gpps[] = {
	EHW_GPP(0, 0, 16),	/* CPU */
	EHW_GPP(1, 17, 18),	/* GPP_S */
	EHW_GPP(2, 19, 42),	/* GPP_A */
	EHW_GPP(3, 43, 46),	/* vGPIO_3 */
};

static const stwuct intew_community ehw_community3[] = {
	EHW_COMMUNITY(0, 0, 46, ehw_community3_gpps),
};

static const stwuct intew_pinctww_soc_data ehw_community3_soc_data = {
	.uid = "3",
	.pins = ehw_community3_pins,
	.npins = AWWAY_SIZE(ehw_community3_pins),
	.communities = ehw_community3,
	.ncommunities = AWWAY_SIZE(ehw_community3),
};

static const stwuct pinctww_pin_desc ehw_community4_pins[] = {
	/* GPP_C */
	PINCTWW_PIN(0, "SMBCWK"),
	PINCTWW_PIN(1, "SMBDATA"),
	PINCTWW_PIN(2, "OSE_PWM0"),
	PINCTWW_PIN(3, "WGMII0_MDC"),
	PINCTWW_PIN(4, "WGMII0_MDIO"),
	PINCTWW_PIN(5, "OSE_PWM1"),
	PINCTWW_PIN(6, "WGMII1_MDC"),
	PINCTWW_PIN(7, "WGMII1_MDIO"),
	PINCTWW_PIN(8, "OSE_TGPIO4"),
	PINCTWW_PIN(9, "OSE_HSUAWT0_EN"),
	PINCTWW_PIN(10, "OSE_TGPIO5"),
	PINCTWW_PIN(11, "OSE_HSUAWT0_WE"),
	PINCTWW_PIN(12, "OSE_UAWT0_WXD"),
	PINCTWW_PIN(13, "OSE_UAWT0_TXD"),
	PINCTWW_PIN(14, "OSE_UAWT0_WTSB"),
	PINCTWW_PIN(15, "OSE_UAWT0_CTSB"),
	PINCTWW_PIN(16, "WGMII2_MDIO"),
	PINCTWW_PIN(17, "WGMII2_MDC"),
	PINCTWW_PIN(18, "OSE_I2C4_SDAT"),
	PINCTWW_PIN(19, "OSE_I2C4_SCWK"),
	PINCTWW_PIN(20, "OSE_UAWT4_WXD"),
	PINCTWW_PIN(21, "OSE_UAWT4_TXD"),
	PINCTWW_PIN(22, "OSE_UAWT4_WTSB"),
	PINCTWW_PIN(23, "OSE_UAWT4_CTSB"),
	/* GPP_F */
	PINCTWW_PIN(24, "CNV_BWI_DT"),
	PINCTWW_PIN(25, "CNV_BWI_WSP"),
	PINCTWW_PIN(26, "CNV_WGI_DT"),
	PINCTWW_PIN(27, "CNV_WGI_WSP"),
	PINCTWW_PIN(28, "CNV_WF_WESET_B"),
	PINCTWW_PIN(29, "EMMC_HIP_MON"),
	PINCTWW_PIN(30, "CNV_PA_BWANKING"),
	PINCTWW_PIN(31, "OSE_I2S1_SCWK"),
	PINCTWW_PIN(32, "I2S_MCWK2_INOUT"),
	PINCTWW_PIN(33, "BOOTMPC"),
	PINCTWW_PIN(34, "OSE_I2S1_SFWM"),
	PINCTWW_PIN(35, "GPPC_F_11"),
	PINCTWW_PIN(36, "GSXDOUT"),
	PINCTWW_PIN(37, "GSXSWOAD"),
	PINCTWW_PIN(38, "GSXDIN"),
	PINCTWW_PIN(39, "GSXSWESETB"),
	PINCTWW_PIN(40, "GSXCWK"),
	PINCTWW_PIN(41, "GPPC_F_17"),
	PINCTWW_PIN(42, "OSE_I2S1_TXD"),
	PINCTWW_PIN(43, "OSE_I2S1_WXD"),
	PINCTWW_PIN(44, "EXT_PWW_GATEB"),
	PINCTWW_PIN(45, "EXT_PWW_GATE2B"),
	PINCTWW_PIN(46, "VNN_CTWW"),
	PINCTWW_PIN(47, "V1P05_CTWW"),
	PINCTWW_PIN(48, "GPPF_CWK_WOOPBACK"),
	/* HVCMOS */
	PINCTWW_PIN(49, "W_BKWTEN"),
	PINCTWW_PIN(50, "W_BKWTCTW"),
	PINCTWW_PIN(51, "W_VDDEN"),
	PINCTWW_PIN(52, "SYS_PWWOK"),
	PINCTWW_PIN(53, "SYS_WESETB"),
	PINCTWW_PIN(54, "MWK_WSTB"),
	/* GPP_E */
	PINCTWW_PIN(55, "SATA_WEDB"),
	PINCTWW_PIN(56, "GPPC_E_1"),
	PINCTWW_PIN(57, "GPPC_E_2"),
	PINCTWW_PIN(58, "DDSP_HPD_B"),
	PINCTWW_PIN(59, "SATA_DEVSWP_0"),
	PINCTWW_PIN(60, "DDPB_CTWWDATA"),
	PINCTWW_PIN(61, "GPPC_E_6"),
	PINCTWW_PIN(62, "DDPB_CTWWCWK"),
	PINCTWW_PIN(63, "GPPC_E_8"),
	PINCTWW_PIN(64, "USB2_OCB_0"),
	PINCTWW_PIN(65, "GPPC_E_10"),
	PINCTWW_PIN(66, "GPPC_E_11"),
	PINCTWW_PIN(67, "GPPC_E_12"),
	PINCTWW_PIN(68, "GPPC_E_13"),
	PINCTWW_PIN(69, "DDSP_HPD_A"),
	PINCTWW_PIN(70, "OSE_I2S0_WXD"),
	PINCTWW_PIN(71, "OSE_I2S0_TXD"),
	PINCTWW_PIN(72, "DDSP_HPD_C"),
	PINCTWW_PIN(73, "DDPA_CTWWDATA"),
	PINCTWW_PIN(74, "DDPA_CTWWCWK"),
	PINCTWW_PIN(75, "OSE_I2S0_SCWK"),
	PINCTWW_PIN(76, "OSE_I2S0_SFWM"),
	PINCTWW_PIN(77, "DDPC_CTWWDATA"),
	PINCTWW_PIN(78, "DDPC_CTWWCWK"),
	PINCTWW_PIN(79, "SPI1_CWK_WOOPBK"),
};

static const stwuct intew_padgwoup ehw_community4_gpps[] = {
	EHW_GPP(0, 0, 23),	/* GPP_C */
	EHW_GPP(1, 24, 48),	/* GPP_F */
	EHW_GPP(2, 49, 54),	/* HVCMOS */
	EHW_GPP(3, 55, 79),	/* GPP_E */
};

static const stwuct intew_community ehw_community4[] = {
	EHW_COMMUNITY(0, 0, 79, ehw_community4_gpps),
};

static const stwuct intew_pinctww_soc_data ehw_community4_soc_data = {
	.uid = "4",
	.pins = ehw_community4_pins,
	.npins = AWWAY_SIZE(ehw_community4_pins),
	.communities = ehw_community4,
	.ncommunities = AWWAY_SIZE(ehw_community4),
};

static const stwuct pinctww_pin_desc ehw_community5_pins[] = {
	/* GPP_W */
	PINCTWW_PIN(0, "HDA_BCWK"),
	PINCTWW_PIN(1, "HDA_SYNC"),
	PINCTWW_PIN(2, "HDA_SDO"),
	PINCTWW_PIN(3, "HDA_SDI_0"),
	PINCTWW_PIN(4, "HDA_WSTB"),
	PINCTWW_PIN(5, "HDA_SDI_1"),
	PINCTWW_PIN(6, "GPP_W_6"),
	PINCTWW_PIN(7, "GPP_W_7"),
};

static const stwuct intew_padgwoup ehw_community5_gpps[] = {
	EHW_GPP(0, 0, 7),	/* GPP_W */
};

static const stwuct intew_community ehw_community5[] = {
	EHW_COMMUNITY(0, 0, 7, ehw_community5_gpps),
};

static const stwuct intew_pinctww_soc_data ehw_community5_soc_data = {
	.uid = "5",
	.pins = ehw_community5_pins,
	.npins = AWWAY_SIZE(ehw_community5_pins),
	.communities = ehw_community5,
	.ncommunities = AWWAY_SIZE(ehw_community5),
};

static const stwuct intew_pinctww_soc_data *ehw_soc_data_awway[] = {
	&ehw_community0_soc_data,
	&ehw_community1_soc_data,
	&ehw_community3_soc_data,
	&ehw_community4_soc_data,
	&ehw_community5_soc_data,
	NUWW
};

static const stwuct acpi_device_id ehw_pinctww_acpi_match[] = {
	{ "INTC1020", (kewnew_uwong_t)ehw_soc_data_awway },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, ehw_pinctww_acpi_match);

static stwuct pwatfowm_dwivew ehw_pinctww_dwivew = {
	.pwobe = intew_pinctww_pwobe_by_uid,
	.dwivew = {
		.name = "ewkhawtwake-pinctww",
		.acpi_match_tabwe = ehw_pinctww_acpi_match,
		.pm = pm_sweep_ptw(&intew_pinctww_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(ehw_pinctww_dwivew);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_DESCWIPTION("Intew Ewkhawt Wake PCH pinctww/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PINCTWW_INTEW);
