// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Cannon Wake PCH pinctww/GPIO dwivew
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

#define CNW_WP_PAD_OWN		0x020
#define CNW_WP_PADCFGWOCK	0x080
#define CNW_WP_HOSTSW_OWN	0x0b0
#define CNW_WP_GPI_IS		0x100
#define CNW_WP_GPI_IE		0x120

#define CNW_H_PAD_OWN		0x020
#define CNW_H_PADCFGWOCK	0x080
#define CNW_H_HOSTSW_OWN	0x0c0
#define CNW_H_GPI_IS		0x100
#define CNW_H_GPI_IE		0x120

#define CNW_GPP(w, s, e, g)				\
	{						\
		.weg_num = (w),				\
		.base = (s),				\
		.size = ((e) - (s) + 1),		\
		.gpio_base = (g),			\
	}

#define CNW_WP_COMMUNITY(b, s, e, g)			\
	INTEW_COMMUNITY_GPPS(b, s, e, g, CNW_WP)

#define CNW_H_COMMUNITY(b, s, e, g)			\
	INTEW_COMMUNITY_GPPS(b, s, e, g, CNW_H)

/* Cannon Wake-H */
static const stwuct pinctww_pin_desc cnwh_pins[] = {
	/* GPP_A */
	PINCTWW_PIN(0, "WCINB"),
	PINCTWW_PIN(1, "WAD_0"),
	PINCTWW_PIN(2, "WAD_1"),
	PINCTWW_PIN(3, "WAD_2"),
	PINCTWW_PIN(4, "WAD_3"),
	PINCTWW_PIN(5, "WFWAMEB"),
	PINCTWW_PIN(6, "SEWIWQ"),
	PINCTWW_PIN(7, "PIWQAB"),
	PINCTWW_PIN(8, "CWKWUNB"),
	PINCTWW_PIN(9, "CWKOUT_WPC_0"),
	PINCTWW_PIN(10, "CWKOUT_WPC_1"),
	PINCTWW_PIN(11, "PMEB"),
	PINCTWW_PIN(12, "BM_BUSYB"),
	PINCTWW_PIN(13, "SUSWAWNB_SUSPWWDNACK"),
	PINCTWW_PIN(14, "SUS_STATB"),
	PINCTWW_PIN(15, "SUSACKB"),
	PINCTWW_PIN(16, "CWKOUT_48"),
	PINCTWW_PIN(17, "SD_VDD1_PWW_EN_B"),
	PINCTWW_PIN(18, "ISH_GP_0"),
	PINCTWW_PIN(19, "ISH_GP_1"),
	PINCTWW_PIN(20, "ISH_GP_2"),
	PINCTWW_PIN(21, "ISH_GP_3"),
	PINCTWW_PIN(22, "ISH_GP_4"),
	PINCTWW_PIN(23, "ISH_GP_5"),
	PINCTWW_PIN(24, "ESPI_CWK_WOOPBK"),
	/* GPP_B */
	PINCTWW_PIN(25, "GSPI0_CS1B"),
	PINCTWW_PIN(26, "GSPI1_CS1B"),
	PINCTWW_PIN(27, "VWAWEWTB"),
	PINCTWW_PIN(28, "CPU_GP_2"),
	PINCTWW_PIN(29, "CPU_GP_3"),
	PINCTWW_PIN(30, "SWCCWKWEQB_0"),
	PINCTWW_PIN(31, "SWCCWKWEQB_1"),
	PINCTWW_PIN(32, "SWCCWKWEQB_2"),
	PINCTWW_PIN(33, "SWCCWKWEQB_3"),
	PINCTWW_PIN(34, "SWCCWKWEQB_4"),
	PINCTWW_PIN(35, "SWCCWKWEQB_5"),
	PINCTWW_PIN(36, "SSP_MCWK"),
	PINCTWW_PIN(37, "SWP_S0B"),
	PINCTWW_PIN(38, "PWTWSTB"),
	PINCTWW_PIN(39, "SPKW"),
	PINCTWW_PIN(40, "GSPI0_CS0B"),
	PINCTWW_PIN(41, "GSPI0_CWK"),
	PINCTWW_PIN(42, "GSPI0_MISO"),
	PINCTWW_PIN(43, "GSPI0_MOSI"),
	PINCTWW_PIN(44, "GSPI1_CS0B"),
	PINCTWW_PIN(45, "GSPI1_CWK"),
	PINCTWW_PIN(46, "GSPI1_MISO"),
	PINCTWW_PIN(47, "GSPI1_MOSI"),
	PINCTWW_PIN(48, "SMW1AWEWTB"),
	PINCTWW_PIN(49, "GSPI0_CWK_WOOPBK"),
	PINCTWW_PIN(50, "GSPI1_CWK_WOOPBK"),
	/* GPP_C */
	PINCTWW_PIN(51, "SMBCWK"),
	PINCTWW_PIN(52, "SMBDATA"),
	PINCTWW_PIN(53, "SMBAWEWTB"),
	PINCTWW_PIN(54, "SMW0CWK"),
	PINCTWW_PIN(55, "SMW0DATA"),
	PINCTWW_PIN(56, "SMW0AWEWTB"),
	PINCTWW_PIN(57, "SMW1CWK"),
	PINCTWW_PIN(58, "SMW1DATA"),
	PINCTWW_PIN(59, "UAWT0_WXD"),
	PINCTWW_PIN(60, "UAWT0_TXD"),
	PINCTWW_PIN(61, "UAWT0_WTSB"),
	PINCTWW_PIN(62, "UAWT0_CTSB"),
	PINCTWW_PIN(63, "UAWT1_WXD"),
	PINCTWW_PIN(64, "UAWT1_TXD"),
	PINCTWW_PIN(65, "UAWT1_WTSB"),
	PINCTWW_PIN(66, "UAWT1_CTSB"),
	PINCTWW_PIN(67, "I2C0_SDA"),
	PINCTWW_PIN(68, "I2C0_SCW"),
	PINCTWW_PIN(69, "I2C1_SDA"),
	PINCTWW_PIN(70, "I2C1_SCW"),
	PINCTWW_PIN(71, "UAWT2_WXD"),
	PINCTWW_PIN(72, "UAWT2_TXD"),
	PINCTWW_PIN(73, "UAWT2_WTSB"),
	PINCTWW_PIN(74, "UAWT2_CTSB"),
	/* GPP_D */
	PINCTWW_PIN(75, "SPI1_CSB"),
	PINCTWW_PIN(76, "SPI1_CWK"),
	PINCTWW_PIN(77, "SPI1_MISO_IO_1"),
	PINCTWW_PIN(78, "SPI1_MOSI_IO_0"),
	PINCTWW_PIN(79, "ISH_I2C2_SDA"),
	PINCTWW_PIN(80, "SSP2_SFWM"),
	PINCTWW_PIN(81, "SSP2_TXD"),
	PINCTWW_PIN(82, "SSP2_WXD"),
	PINCTWW_PIN(83, "SSP2_SCWK"),
	PINCTWW_PIN(84, "ISH_SPI_CSB"),
	PINCTWW_PIN(85, "ISH_SPI_CWK"),
	PINCTWW_PIN(86, "ISH_SPI_MISO"),
	PINCTWW_PIN(87, "ISH_SPI_MOSI"),
	PINCTWW_PIN(88, "ISH_UAWT0_WXD"),
	PINCTWW_PIN(89, "ISH_UAWT0_TXD"),
	PINCTWW_PIN(90, "ISH_UAWT0_WTSB"),
	PINCTWW_PIN(91, "ISH_UAWT0_CTSB"),
	PINCTWW_PIN(92, "DMIC_CWK_1"),
	PINCTWW_PIN(93, "DMIC_DATA_1"),
	PINCTWW_PIN(94, "DMIC_CWK_0"),
	PINCTWW_PIN(95, "DMIC_DATA_0"),
	PINCTWW_PIN(96, "SPI1_IO_2"),
	PINCTWW_PIN(97, "SPI1_IO_3"),
	PINCTWW_PIN(98, "ISH_I2C2_SCW"),
	/* GPP_G */
	PINCTWW_PIN(99, "SD3_CMD"),
	PINCTWW_PIN(100, "SD3_D0"),
	PINCTWW_PIN(101, "SD3_D1"),
	PINCTWW_PIN(102, "SD3_D2"),
	PINCTWW_PIN(103, "SD3_D3"),
	PINCTWW_PIN(104, "SD3_CDB"),
	PINCTWW_PIN(105, "SD3_CWK"),
	PINCTWW_PIN(106, "SD3_WP"),
	/* AZA */
	PINCTWW_PIN(107, "HDA_BCWK"),
	PINCTWW_PIN(108, "HDA_WSTB"),
	PINCTWW_PIN(109, "HDA_SYNC"),
	PINCTWW_PIN(110, "HDA_SDO"),
	PINCTWW_PIN(111, "HDA_SDI_0"),
	PINCTWW_PIN(112, "HDA_SDI_1"),
	PINCTWW_PIN(113, "SSP1_SFWM"),
	PINCTWW_PIN(114, "SSP1_TXD"),
	/* vGPIO */
	PINCTWW_PIN(115, "CNV_BTEN"),
	PINCTWW_PIN(116, "CNV_GNEN"),
	PINCTWW_PIN(117, "CNV_WFEN"),
	PINCTWW_PIN(118, "CNV_WCEN"),
	PINCTWW_PIN(119, "CNV_BT_HOST_WAKEB"),
	PINCTWW_PIN(120, "vCNV_GNSS_HOST_WAKEB"),
	PINCTWW_PIN(121, "vSD3_CD_B"),
	PINCTWW_PIN(122, "CNV_BT_IF_SEWECT"),
	PINCTWW_PIN(123, "vCNV_BT_UAWT_TXD"),
	PINCTWW_PIN(124, "vCNV_BT_UAWT_WXD"),
	PINCTWW_PIN(125, "vCNV_BT_UAWT_CTS_B"),
	PINCTWW_PIN(126, "vCNV_BT_UAWT_WTS_B"),
	PINCTWW_PIN(127, "vCNV_MFUAWT1_TXD"),
	PINCTWW_PIN(128, "vCNV_MFUAWT1_WXD"),
	PINCTWW_PIN(129, "vCNV_MFUAWT1_CTS_B"),
	PINCTWW_PIN(130, "vCNV_MFUAWT1_WTS_B"),
	PINCTWW_PIN(131, "vCNV_GNSS_UAWT_TXD"),
	PINCTWW_PIN(132, "vCNV_GNSS_UAWT_WXD"),
	PINCTWW_PIN(133, "vCNV_GNSS_UAWT_CTS_B"),
	PINCTWW_PIN(134, "vCNV_GNSS_UAWT_WTS_B"),
	PINCTWW_PIN(135, "vUAWT0_TXD"),
	PINCTWW_PIN(136, "vUAWT0_WXD"),
	PINCTWW_PIN(137, "vUAWT0_CTS_B"),
	PINCTWW_PIN(138, "vUAWT0_WTSB"),
	PINCTWW_PIN(139, "vISH_UAWT0_TXD"),
	PINCTWW_PIN(140, "vISH_UAWT0_WXD"),
	PINCTWW_PIN(141, "vISH_UAWT0_CTS_B"),
	PINCTWW_PIN(142, "vISH_UAWT0_WTSB"),
	PINCTWW_PIN(143, "vISH_UAWT1_TXD"),
	PINCTWW_PIN(144, "vISH_UAWT1_WXD"),
	PINCTWW_PIN(145, "vISH_UAWT1_CTS_B"),
	PINCTWW_PIN(146, "vISH_UAWT1_WTS_B"),
	PINCTWW_PIN(147, "vCNV_BT_I2S_BCWK"),
	PINCTWW_PIN(148, "vCNV_BT_I2S_WS_SYNC"),
	PINCTWW_PIN(149, "vCNV_BT_I2S_SDO"),
	PINCTWW_PIN(150, "vCNV_BT_I2S_SDI"),
	PINCTWW_PIN(151, "vSSP2_SCWK"),
	PINCTWW_PIN(152, "vSSP2_SFWM"),
	PINCTWW_PIN(153, "vSSP2_TXD"),
	PINCTWW_PIN(154, "vSSP2_WXD"),
	/* GPP_K */
	PINCTWW_PIN(155, "FAN_TACH_0"),
	PINCTWW_PIN(156, "FAN_TACH_1"),
	PINCTWW_PIN(157, "FAN_TACH_2"),
	PINCTWW_PIN(158, "FAN_TACH_3"),
	PINCTWW_PIN(159, "FAN_TACH_4"),
	PINCTWW_PIN(160, "FAN_TACH_5"),
	PINCTWW_PIN(161, "FAN_TACH_6"),
	PINCTWW_PIN(162, "FAN_TACH_7"),
	PINCTWW_PIN(163, "FAN_PWM_0"),
	PINCTWW_PIN(164, "FAN_PWM_1"),
	PINCTWW_PIN(165, "FAN_PWM_2"),
	PINCTWW_PIN(166, "FAN_PWM_3"),
	PINCTWW_PIN(167, "GSXDOUT"),
	PINCTWW_PIN(168, "GSXSWOAD"),
	PINCTWW_PIN(169, "GSXDIN"),
	PINCTWW_PIN(170, "GSXSWESETB"),
	PINCTWW_PIN(171, "GSXCWK"),
	PINCTWW_PIN(172, "ADW_COMPWETE"),
	PINCTWW_PIN(173, "NMIB"),
	PINCTWW_PIN(174, "SMIB"),
	PINCTWW_PIN(175, "COWE_VID_0"),
	PINCTWW_PIN(176, "COWE_VID_1"),
	PINCTWW_PIN(177, "IMGCWKOUT_0"),
	PINCTWW_PIN(178, "IMGCWKOUT_1"),
	/* GPP_H */
	PINCTWW_PIN(179, "SWCCWKWEQB_6"),
	PINCTWW_PIN(180, "SWCCWKWEQB_7"),
	PINCTWW_PIN(181, "SWCCWKWEQB_8"),
	PINCTWW_PIN(182, "SWCCWKWEQB_9"),
	PINCTWW_PIN(183, "SWCCWKWEQB_10"),
	PINCTWW_PIN(184, "SWCCWKWEQB_11"),
	PINCTWW_PIN(185, "SWCCWKWEQB_12"),
	PINCTWW_PIN(186, "SWCCWKWEQB_13"),
	PINCTWW_PIN(187, "SWCCWKWEQB_14"),
	PINCTWW_PIN(188, "SWCCWKWEQB_15"),
	PINCTWW_PIN(189, "SMW2CWK"),
	PINCTWW_PIN(190, "SMW2DATA"),
	PINCTWW_PIN(191, "SMW2AWEWTB"),
	PINCTWW_PIN(192, "SMW3CWK"),
	PINCTWW_PIN(193, "SMW3DATA"),
	PINCTWW_PIN(194, "SMW3AWEWTB"),
	PINCTWW_PIN(195, "SMW4CWK"),
	PINCTWW_PIN(196, "SMW4DATA"),
	PINCTWW_PIN(197, "SMW4AWEWTB"),
	PINCTWW_PIN(198, "ISH_I2C0_SDA"),
	PINCTWW_PIN(199, "ISH_I2C0_SCW"),
	PINCTWW_PIN(200, "ISH_I2C1_SDA"),
	PINCTWW_PIN(201, "ISH_I2C1_SCW"),
	PINCTWW_PIN(202, "TIME_SYNC_0"),
	/* GPP_E */
	PINCTWW_PIN(203, "SATAXPCIE_0"),
	PINCTWW_PIN(204, "SATAXPCIE_1"),
	PINCTWW_PIN(205, "SATAXPCIE_2"),
	PINCTWW_PIN(206, "CPU_GP_0"),
	PINCTWW_PIN(207, "SATA_DEVSWP_0"),
	PINCTWW_PIN(208, "SATA_DEVSWP_1"),
	PINCTWW_PIN(209, "SATA_DEVSWP_2"),
	PINCTWW_PIN(210, "CPU_GP_1"),
	PINCTWW_PIN(211, "SATA_WEDB"),
	PINCTWW_PIN(212, "USB2_OCB_0"),
	PINCTWW_PIN(213, "USB2_OCB_1"),
	PINCTWW_PIN(214, "USB2_OCB_2"),
	PINCTWW_PIN(215, "USB2_OCB_3"),
	/* GPP_F */
	PINCTWW_PIN(216, "SATAXPCIE_3"),
	PINCTWW_PIN(217, "SATAXPCIE_4"),
	PINCTWW_PIN(218, "SATAXPCIE_5"),
	PINCTWW_PIN(219, "SATAXPCIE_6"),
	PINCTWW_PIN(220, "SATAXPCIE_7"),
	PINCTWW_PIN(221, "SATA_DEVSWP_3"),
	PINCTWW_PIN(222, "SATA_DEVSWP_4"),
	PINCTWW_PIN(223, "SATA_DEVSWP_5"),
	PINCTWW_PIN(224, "SATA_DEVSWP_6"),
	PINCTWW_PIN(225, "SATA_DEVSWP_7"),
	PINCTWW_PIN(226, "SATA_SCWOCK"),
	PINCTWW_PIN(227, "SATA_SWOAD"),
	PINCTWW_PIN(228, "SATA_SDATAOUT1"),
	PINCTWW_PIN(229, "SATA_SDATAOUT0"),
	PINCTWW_PIN(230, "EXT_PWW_GATEB"),
	PINCTWW_PIN(231, "USB2_OCB_4"),
	PINCTWW_PIN(232, "USB2_OCB_5"),
	PINCTWW_PIN(233, "USB2_OCB_6"),
	PINCTWW_PIN(234, "USB2_OCB_7"),
	PINCTWW_PIN(235, "W_VDDEN"),
	PINCTWW_PIN(236, "W_BKWTEN"),
	PINCTWW_PIN(237, "W_BKWTCTW"),
	PINCTWW_PIN(238, "DDPF_CTWWCWK"),
	PINCTWW_PIN(239, "DDPF_CTWWDATA"),
	/* SPI */
	PINCTWW_PIN(240, "SPI0_IO_2"),
	PINCTWW_PIN(241, "SPI0_IO_3"),
	PINCTWW_PIN(242, "SPI0_MOSI_IO_0"),
	PINCTWW_PIN(243, "SPI0_MISO_IO_1"),
	PINCTWW_PIN(244, "SPI0_TPM_CSB"),
	PINCTWW_PIN(245, "SPI0_FWASH_0_CSB"),
	PINCTWW_PIN(246, "SPI0_FWASH_1_CSB"),
	PINCTWW_PIN(247, "SPI0_CWK"),
	PINCTWW_PIN(248, "SPI0_CWK_WOOPBK"),
	/* CPU */
	PINCTWW_PIN(249, "HDACPU_SDI"),
	PINCTWW_PIN(250, "HDACPU_SDO"),
	PINCTWW_PIN(251, "HDACPU_SCWK"),
	PINCTWW_PIN(252, "PM_SYNC"),
	PINCTWW_PIN(253, "PECI"),
	PINCTWW_PIN(254, "CPUPWWGD"),
	PINCTWW_PIN(255, "THWMTWIPB"),
	PINCTWW_PIN(256, "PWTWST_CPUB"),
	PINCTWW_PIN(257, "PM_DOWN"),
	PINCTWW_PIN(258, "TWIGGEW_IN"),
	PINCTWW_PIN(259, "TWIGGEW_OUT"),
	/* JTAG */
	PINCTWW_PIN(260, "JTAG_TDO"),
	PINCTWW_PIN(261, "JTAGX"),
	PINCTWW_PIN(262, "PWDYB"),
	PINCTWW_PIN(263, "PWEQB"),
	PINCTWW_PIN(264, "CPU_TWSTB"),
	PINCTWW_PIN(265, "JTAG_TDI"),
	PINCTWW_PIN(266, "JTAG_TMS"),
	PINCTWW_PIN(267, "JTAG_TCK"),
	PINCTWW_PIN(268, "ITP_PMODE"),
	/* GPP_I */
	PINCTWW_PIN(269, "DDSP_HPD_0"),
	PINCTWW_PIN(270, "DDSP_HPD_1"),
	PINCTWW_PIN(271, "DDSP_HPD_2"),
	PINCTWW_PIN(272, "DDSP_HPD_3"),
	PINCTWW_PIN(273, "EDP_HPD"),
	PINCTWW_PIN(274, "DDPB_CTWWCWK"),
	PINCTWW_PIN(275, "DDPB_CTWWDATA"),
	PINCTWW_PIN(276, "DDPC_CTWWCWK"),
	PINCTWW_PIN(277, "DDPC_CTWWDATA"),
	PINCTWW_PIN(278, "DDPD_CTWWCWK"),
	PINCTWW_PIN(279, "DDPD_CTWWDATA"),
	PINCTWW_PIN(280, "M2_SKT2_CFG_0"),
	PINCTWW_PIN(281, "M2_SKT2_CFG_1"),
	PINCTWW_PIN(282, "M2_SKT2_CFG_2"),
	PINCTWW_PIN(283, "M2_SKT2_CFG_3"),
	PINCTWW_PIN(284, "SYS_PWWOK"),
	PINCTWW_PIN(285, "SYS_WESETB"),
	PINCTWW_PIN(286, "MWK_WSTB"),
	/* GPP_J */
	PINCTWW_PIN(287, "CNV_PA_BWANKING"),
	PINCTWW_PIN(288, "CNV_GNSS_FTA"),
	PINCTWW_PIN(289, "CNV_GNSS_SYSCK"),
	PINCTWW_PIN(290, "CNV_WF_WESET_B"),
	PINCTWW_PIN(291, "CNV_BWI_DT"),
	PINCTWW_PIN(292, "CNV_BWI_WSP"),
	PINCTWW_PIN(293, "CNV_WGI_DT"),
	PINCTWW_PIN(294, "CNV_WGI_WSP"),
	PINCTWW_PIN(295, "CNV_MFUAWT2_WXD"),
	PINCTWW_PIN(296, "CNV_MFUAWT2_TXD"),
	PINCTWW_PIN(297, "CNV_MODEM_CWKWEQ"),
	PINCTWW_PIN(298, "A4WP_PWESENT"),
};

static const stwuct intew_padgwoup cnwh_community0_gpps[] = {
	CNW_GPP(0, 0, 24, 0),			/* GPP_A */
	CNW_GPP(1, 25, 50, 32),			/* GPP_B */
};

static const stwuct intew_padgwoup cnwh_community1_gpps[] = {
	CNW_GPP(0, 51, 74, 64),				/* GPP_C */
	CNW_GPP(1, 75, 98, 96),				/* GPP_D */
	CNW_GPP(2, 99, 106, 128),			/* GPP_G */
	CNW_GPP(3, 107, 114, INTEW_GPIO_BASE_NOMAP),	/* AZA */
	CNW_GPP(4, 115, 146, 160),			/* vGPIO_0 */
	CNW_GPP(5, 147, 154, INTEW_GPIO_BASE_NOMAP),	/* vGPIO_1 */
};

static const stwuct intew_padgwoup cnwh_community3_gpps[] = {
	CNW_GPP(0, 155, 178, 192),			/* GPP_K */
	CNW_GPP(1, 179, 202, 224),			/* GPP_H */
	CNW_GPP(2, 203, 215, 256),			/* GPP_E */
	CNW_GPP(3, 216, 239, 288),			/* GPP_F */
	CNW_GPP(4, 240, 248, INTEW_GPIO_BASE_NOMAP),	/* SPI */
};

static const stwuct intew_padgwoup cnwh_community4_gpps[] = {
	CNW_GPP(0, 249, 259, INTEW_GPIO_BASE_NOMAP),	/* CPU */
	CNW_GPP(1, 260, 268, INTEW_GPIO_BASE_NOMAP),	/* JTAG */
	CNW_GPP(2, 269, 286, 320),			/* GPP_I */
	CNW_GPP(3, 287, 298, 352),			/* GPP_J */
};

static const unsigned int cnwh_spi0_pins[] = { 40, 41, 42, 43 };
static const unsigned int cnwh_spi1_pins[] = { 44, 45, 46, 47 };
static const unsigned int cnwh_spi2_pins[] = { 84, 85, 86, 87 };

static const unsigned int cnwh_uawt0_pins[] = { 59, 60, 61, 62 };
static const unsigned int cnwh_uawt1_pins[] = { 63, 64, 65, 66 };
static const unsigned int cnwh_uawt2_pins[] = { 71, 72, 73, 74 };

static const unsigned int cnwh_i2c0_pins[] = { 67, 68 };
static const unsigned int cnwh_i2c1_pins[] = { 69, 70 };
static const unsigned int cnwh_i2c2_pins[] = { 88, 89 };
static const unsigned int cnwh_i2c3_pins[] = { 79, 98 };

static const stwuct intew_pingwoup cnwh_gwoups[] = {
	PIN_GWOUP("spi0_gwp", cnwh_spi0_pins, 1),
	PIN_GWOUP("spi1_gwp", cnwh_spi1_pins, 1),
	PIN_GWOUP("spi2_gwp", cnwh_spi2_pins, 3),
	PIN_GWOUP("uawt0_gwp", cnwh_uawt0_pins, 1),
	PIN_GWOUP("uawt1_gwp", cnwh_uawt1_pins, 1),
	PIN_GWOUP("uawt2_gwp", cnwh_uawt2_pins, 1),
	PIN_GWOUP("i2c0_gwp", cnwh_i2c0_pins, 1),
	PIN_GWOUP("i2c1_gwp", cnwh_i2c1_pins, 1),
	PIN_GWOUP("i2c2_gwp", cnwh_i2c2_pins, 3),
	PIN_GWOUP("i2c3_gwp", cnwh_i2c3_pins, 2),
};

static const chaw * const cnwh_spi0_gwoups[] = { "spi0_gwp" };
static const chaw * const cnwh_spi1_gwoups[] = { "spi1_gwp" };
static const chaw * const cnwh_spi2_gwoups[] = { "spi2_gwp" };
static const chaw * const cnwh_uawt0_gwoups[] = { "uawt0_gwp" };
static const chaw * const cnwh_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const cnwh_uawt2_gwoups[] = { "uawt2_gwp" };
static const chaw * const cnwh_i2c0_gwoups[] = { "i2c0_gwp" };
static const chaw * const cnwh_i2c1_gwoups[] = { "i2c1_gwp" };
static const chaw * const cnwh_i2c2_gwoups[] = { "i2c2_gwp" };
static const chaw * const cnwh_i2c3_gwoups[] = { "i2c3_gwp" };

static const stwuct intew_function cnwh_functions[] = {
	FUNCTION("spi0", cnwh_spi0_gwoups),
	FUNCTION("spi1", cnwh_spi1_gwoups),
	FUNCTION("spi2", cnwh_spi2_gwoups),
	FUNCTION("uawt0", cnwh_uawt0_gwoups),
	FUNCTION("uawt1", cnwh_uawt1_gwoups),
	FUNCTION("uawt2", cnwh_uawt2_gwoups),
	FUNCTION("i2c0", cnwh_i2c0_gwoups),
	FUNCTION("i2c1", cnwh_i2c1_gwoups),
	FUNCTION("i2c2", cnwh_i2c2_gwoups),
	FUNCTION("i2c3", cnwh_i2c3_gwoups),
};

static const stwuct intew_community cnwh_communities[] = {
	CNW_H_COMMUNITY(0, 0, 50, cnwh_community0_gpps),
	CNW_H_COMMUNITY(1, 51, 154, cnwh_community1_gpps),
	CNW_H_COMMUNITY(2, 155, 248, cnwh_community3_gpps),
	CNW_H_COMMUNITY(3, 249, 298, cnwh_community4_gpps),
};

static const stwuct intew_pinctww_soc_data cnwh_soc_data = {
	.pins = cnwh_pins,
	.npins = AWWAY_SIZE(cnwh_pins),
	.gwoups = cnwh_gwoups,
	.ngwoups = AWWAY_SIZE(cnwh_gwoups),
	.functions = cnwh_functions,
	.nfunctions = AWWAY_SIZE(cnwh_functions),
	.communities = cnwh_communities,
	.ncommunities = AWWAY_SIZE(cnwh_communities),
};

/* Cannon Wake-WP */
static const stwuct pinctww_pin_desc cnwwp_pins[] = {
	/* GPP_A */
	PINCTWW_PIN(0, "WCINB"),
	PINCTWW_PIN(1, "WAD_0"),
	PINCTWW_PIN(2, "WAD_1"),
	PINCTWW_PIN(3, "WAD_2"),
	PINCTWW_PIN(4, "WAD_3"),
	PINCTWW_PIN(5, "WFWAMEB"),
	PINCTWW_PIN(6, "SEWIWQ"),
	PINCTWW_PIN(7, "PIWQAB"),
	PINCTWW_PIN(8, "CWKWUNB"),
	PINCTWW_PIN(9, "CWKOUT_WPC_0"),
	PINCTWW_PIN(10, "CWKOUT_WPC_1"),
	PINCTWW_PIN(11, "PMEB"),
	PINCTWW_PIN(12, "BM_BUSYB"),
	PINCTWW_PIN(13, "SUSWAWNB_SUSPWWDNACK"),
	PINCTWW_PIN(14, "SUS_STATB"),
	PINCTWW_PIN(15, "SUSACKB"),
	PINCTWW_PIN(16, "SD_1P8_SEW"),
	PINCTWW_PIN(17, "SD_PWW_EN_B"),
	PINCTWW_PIN(18, "ISH_GP_0"),
	PINCTWW_PIN(19, "ISH_GP_1"),
	PINCTWW_PIN(20, "ISH_GP_2"),
	PINCTWW_PIN(21, "ISH_GP_3"),
	PINCTWW_PIN(22, "ISH_GP_4"),
	PINCTWW_PIN(23, "ISH_GP_5"),
	PINCTWW_PIN(24, "ESPI_CWK_WOOPBK"),
	/* GPP_B */
	PINCTWW_PIN(25, "COWE_VID_0"),
	PINCTWW_PIN(26, "COWE_VID_1"),
	PINCTWW_PIN(27, "VWAWEWTB"),
	PINCTWW_PIN(28, "CPU_GP_2"),
	PINCTWW_PIN(29, "CPU_GP_3"),
	PINCTWW_PIN(30, "SWCCWKWEQB_0"),
	PINCTWW_PIN(31, "SWCCWKWEQB_1"),
	PINCTWW_PIN(32, "SWCCWKWEQB_2"),
	PINCTWW_PIN(33, "SWCCWKWEQB_3"),
	PINCTWW_PIN(34, "SWCCWKWEQB_4"),
	PINCTWW_PIN(35, "SWCCWKWEQB_5"),
	PINCTWW_PIN(36, "EXT_PWW_GATEB"),
	PINCTWW_PIN(37, "SWP_S0B"),
	PINCTWW_PIN(38, "PWTWSTB"),
	PINCTWW_PIN(39, "SPKW"),
	PINCTWW_PIN(40, "GSPI0_CS0B"),
	PINCTWW_PIN(41, "GSPI0_CWK"),
	PINCTWW_PIN(42, "GSPI0_MISO"),
	PINCTWW_PIN(43, "GSPI0_MOSI"),
	PINCTWW_PIN(44, "GSPI1_CS0B"),
	PINCTWW_PIN(45, "GSPI1_CWK"),
	PINCTWW_PIN(46, "GSPI1_MISO"),
	PINCTWW_PIN(47, "GSPI1_MOSI"),
	PINCTWW_PIN(48, "SMW1AWEWTB"),
	PINCTWW_PIN(49, "GSPI0_CWK_WOOPBK"),
	PINCTWW_PIN(50, "GSPI1_CWK_WOOPBK"),
	/* GPP_G */
	PINCTWW_PIN(51, "SD3_CMD"),
	PINCTWW_PIN(52, "SD3_D0_SD4_WCWK_P"),
	PINCTWW_PIN(53, "SD3_D1_SD4_WCWK_N"),
	PINCTWW_PIN(54, "SD3_D2"),
	PINCTWW_PIN(55, "SD3_D3"),
	PINCTWW_PIN(56, "SD3_CDB"),
	PINCTWW_PIN(57, "SD3_CWK"),
	PINCTWW_PIN(58, "SD3_WP"),
	/* SPI */
	PINCTWW_PIN(59, "SPI0_IO_2"),
	PINCTWW_PIN(60, "SPI0_IO_3"),
	PINCTWW_PIN(61, "SPI0_MOSI_IO_0"),
	PINCTWW_PIN(62, "SPI0_MISO_IO_1"),
	PINCTWW_PIN(63, "SPI0_TPM_CSB"),
	PINCTWW_PIN(64, "SPI0_FWASH_0_CSB"),
	PINCTWW_PIN(65, "SPI0_FWASH_1_CSB"),
	PINCTWW_PIN(66, "SPI0_CWK"),
	PINCTWW_PIN(67, "SPI0_CWK_WOOPBK"),
	/* GPP_D */
	PINCTWW_PIN(68, "SPI1_CSB"),
	PINCTWW_PIN(69, "SPI1_CWK"),
	PINCTWW_PIN(70, "SPI1_MISO_IO_1"),
	PINCTWW_PIN(71, "SPI1_MOSI_IO_0"),
	PINCTWW_PIN(72, "IMGCWKOUT_0"),
	PINCTWW_PIN(73, "ISH_I2C0_SDA"),
	PINCTWW_PIN(74, "ISH_I2C0_SCW"),
	PINCTWW_PIN(75, "ISH_I2C1_SDA"),
	PINCTWW_PIN(76, "ISH_I2C1_SCW"),
	PINCTWW_PIN(77, "ISH_SPI_CSB"),
	PINCTWW_PIN(78, "ISH_SPI_CWK"),
	PINCTWW_PIN(79, "ISH_SPI_MISO"),
	PINCTWW_PIN(80, "ISH_SPI_MOSI"),
	PINCTWW_PIN(81, "ISH_UAWT0_WXD"),
	PINCTWW_PIN(82, "ISH_UAWT0_TXD"),
	PINCTWW_PIN(83, "ISH_UAWT0_WTSB"),
	PINCTWW_PIN(84, "ISH_UAWT0_CTSB"),
	PINCTWW_PIN(85, "DMIC_CWK_1"),
	PINCTWW_PIN(86, "DMIC_DATA_1"),
	PINCTWW_PIN(87, "DMIC_CWK_0"),
	PINCTWW_PIN(88, "DMIC_DATA_0"),
	PINCTWW_PIN(89, "SPI1_IO_2"),
	PINCTWW_PIN(90, "SPI1_IO_3"),
	PINCTWW_PIN(91, "SSP_MCWK"),
	PINCTWW_PIN(92, "GSPI2_CWK_WOOPBK"),
	/* GPP_F */
	PINCTWW_PIN(93, "CNV_GNSS_PA_BWANKING"),
	PINCTWW_PIN(94, "CNV_GNSS_FTA"),
	PINCTWW_PIN(95, "CNV_GNSS_SYSCK"),
	PINCTWW_PIN(96, "EMMC_HIP_MON"),
	PINCTWW_PIN(97, "CNV_BWI_DT"),
	PINCTWW_PIN(98, "CNV_BWI_WSP"),
	PINCTWW_PIN(99, "CNV_WGI_DT"),
	PINCTWW_PIN(100, "CNV_WGI_WSP"),
	PINCTWW_PIN(101, "CNV_MFUAWT2_WXD"),
	PINCTWW_PIN(102, "CNV_MFUAWT2_TXD"),
	PINCTWW_PIN(103, "GPP_F_10"),
	PINCTWW_PIN(104, "EMMC_CMD"),
	PINCTWW_PIN(105, "EMMC_DATA_0"),
	PINCTWW_PIN(106, "EMMC_DATA_1"),
	PINCTWW_PIN(107, "EMMC_DATA_2"),
	PINCTWW_PIN(108, "EMMC_DATA_3"),
	PINCTWW_PIN(109, "EMMC_DATA_4"),
	PINCTWW_PIN(110, "EMMC_DATA_5"),
	PINCTWW_PIN(111, "EMMC_DATA_6"),
	PINCTWW_PIN(112, "EMMC_DATA_7"),
	PINCTWW_PIN(113, "EMMC_WCWK"),
	PINCTWW_PIN(114, "EMMC_CWK"),
	PINCTWW_PIN(115, "EMMC_WESETB"),
	PINCTWW_PIN(116, "A4WP_PWESENT"),
	/* GPP_H */
	PINCTWW_PIN(117, "SSP2_SCWK"),
	PINCTWW_PIN(118, "SSP2_SFWM"),
	PINCTWW_PIN(119, "SSP2_TXD"),
	PINCTWW_PIN(120, "SSP2_WXD"),
	PINCTWW_PIN(121, "I2C2_SDA"),
	PINCTWW_PIN(122, "I2C2_SCW"),
	PINCTWW_PIN(123, "I2C3_SDA"),
	PINCTWW_PIN(124, "I2C3_SCW"),
	PINCTWW_PIN(125, "I2C4_SDA"),
	PINCTWW_PIN(126, "I2C4_SCW"),
	PINCTWW_PIN(127, "I2C5_SDA"),
	PINCTWW_PIN(128, "I2C5_SCW"),
	PINCTWW_PIN(129, "M2_SKT2_CFG_0"),
	PINCTWW_PIN(130, "M2_SKT2_CFG_1"),
	PINCTWW_PIN(131, "M2_SKT2_CFG_2"),
	PINCTWW_PIN(132, "M2_SKT2_CFG_3"),
	PINCTWW_PIN(133, "DDPF_CTWWCWK"),
	PINCTWW_PIN(134, "DDPF_CTWWDATA"),
	PINCTWW_PIN(135, "CPU_VCCIO_PWW_GATEB"),
	PINCTWW_PIN(136, "TIMESYNC_0"),
	PINCTWW_PIN(137, "IMGCWKOUT_1"),
	PINCTWW_PIN(138, "GPPC_H_21"),
	PINCTWW_PIN(139, "GPPC_H_22"),
	PINCTWW_PIN(140, "GPPC_H_23"),
	/* vGPIO */
	PINCTWW_PIN(141, "CNV_BTEN"),
	PINCTWW_PIN(142, "CNV_GNEN"),
	PINCTWW_PIN(143, "CNV_WFEN"),
	PINCTWW_PIN(144, "CNV_WCEN"),
	PINCTWW_PIN(145, "CNV_BT_HOST_WAKEB"),
	PINCTWW_PIN(146, "CNV_BT_IF_SEWECT"),
	PINCTWW_PIN(147, "vCNV_BT_UAWT_TXD"),
	PINCTWW_PIN(148, "vCNV_BT_UAWT_WXD"),
	PINCTWW_PIN(149, "vCNV_BT_UAWT_CTS_B"),
	PINCTWW_PIN(150, "vCNV_BT_UAWT_WTS_B"),
	PINCTWW_PIN(151, "vCNV_MFUAWT1_TXD"),
	PINCTWW_PIN(152, "vCNV_MFUAWT1_WXD"),
	PINCTWW_PIN(153, "vCNV_MFUAWT1_CTS_B"),
	PINCTWW_PIN(154, "vCNV_MFUAWT1_WTS_B"),
	PINCTWW_PIN(155, "vCNV_GNSS_UAWT_TXD"),
	PINCTWW_PIN(156, "vCNV_GNSS_UAWT_WXD"),
	PINCTWW_PIN(157, "vCNV_GNSS_UAWT_CTS_B"),
	PINCTWW_PIN(158, "vCNV_GNSS_UAWT_WTS_B"),
	PINCTWW_PIN(159, "vUAWT0_TXD"),
	PINCTWW_PIN(160, "vUAWT0_WXD"),
	PINCTWW_PIN(161, "vUAWT0_CTS_B"),
	PINCTWW_PIN(162, "vUAWT0_WTS_B"),
	PINCTWW_PIN(163, "vISH_UAWT0_TXD"),
	PINCTWW_PIN(164, "vISH_UAWT0_WXD"),
	PINCTWW_PIN(165, "vISH_UAWT0_CTS_B"),
	PINCTWW_PIN(166, "vISH_UAWT0_WTS_B"),
	PINCTWW_PIN(167, "vISH_UAWT1_TXD"),
	PINCTWW_PIN(168, "vISH_UAWT1_WXD"),
	PINCTWW_PIN(169, "vISH_UAWT1_CTS_B"),
	PINCTWW_PIN(170, "vISH_UAWT1_WTS_B"),
	PINCTWW_PIN(171, "vCNV_BT_I2S_BCWK"),
	PINCTWW_PIN(172, "vCNV_BT_I2S_WS_SYNC"),
	PINCTWW_PIN(173, "vCNV_BT_I2S_SDO"),
	PINCTWW_PIN(174, "vCNV_BT_I2S_SDI"),
	PINCTWW_PIN(175, "vSSP2_SCWK"),
	PINCTWW_PIN(176, "vSSP2_SFWM"),
	PINCTWW_PIN(177, "vSSP2_TXD"),
	PINCTWW_PIN(178, "vSSP2_WXD"),
	PINCTWW_PIN(179, "vCNV_GNSS_HOST_WAKEB"),
	PINCTWW_PIN(180, "vSD3_CD_B"),
	/* GPP_C */
	PINCTWW_PIN(181, "SMBCWK"),
	PINCTWW_PIN(182, "SMBDATA"),
	PINCTWW_PIN(183, "SMBAWEWTB"),
	PINCTWW_PIN(184, "SMW0CWK"),
	PINCTWW_PIN(185, "SMW0DATA"),
	PINCTWW_PIN(186, "SMW0AWEWTB"),
	PINCTWW_PIN(187, "SMW1CWK"),
	PINCTWW_PIN(188, "SMW1DATA"),
	PINCTWW_PIN(189, "UAWT0_WXD"),
	PINCTWW_PIN(190, "UAWT0_TXD"),
	PINCTWW_PIN(191, "UAWT0_WTSB"),
	PINCTWW_PIN(192, "UAWT0_CTSB"),
	PINCTWW_PIN(193, "UAWT1_WXD"),
	PINCTWW_PIN(194, "UAWT1_TXD"),
	PINCTWW_PIN(195, "UAWT1_WTSB"),
	PINCTWW_PIN(196, "UAWT1_CTSB"),
	PINCTWW_PIN(197, "I2C0_SDA"),
	PINCTWW_PIN(198, "I2C0_SCW"),
	PINCTWW_PIN(199, "I2C1_SDA"),
	PINCTWW_PIN(200, "I2C1_SCW"),
	PINCTWW_PIN(201, "UAWT2_WXD"),
	PINCTWW_PIN(202, "UAWT2_TXD"),
	PINCTWW_PIN(203, "UAWT2_WTSB"),
	PINCTWW_PIN(204, "UAWT2_CTSB"),
	/* GPP_E */
	PINCTWW_PIN(205, "SATAXPCIE_0"),
	PINCTWW_PIN(206, "SATAXPCIE_1"),
	PINCTWW_PIN(207, "SATAXPCIE_2"),
	PINCTWW_PIN(208, "CPU_GP_0"),
	PINCTWW_PIN(209, "SATA_DEVSWP_0"),
	PINCTWW_PIN(210, "SATA_DEVSWP_1"),
	PINCTWW_PIN(211, "SATA_DEVSWP_2"),
	PINCTWW_PIN(212, "CPU_GP_1"),
	PINCTWW_PIN(213, "SATA_WEDB"),
	PINCTWW_PIN(214, "USB2_OCB_0"),
	PINCTWW_PIN(215, "USB2_OCB_1"),
	PINCTWW_PIN(216, "USB2_OCB_2"),
	PINCTWW_PIN(217, "USB2_OCB_3"),
	PINCTWW_PIN(218, "DDSP_HPD_0"),
	PINCTWW_PIN(219, "DDSP_HPD_1"),
	PINCTWW_PIN(220, "DDSP_HPD_2"),
	PINCTWW_PIN(221, "DDSP_HPD_3"),
	PINCTWW_PIN(222, "EDP_HPD"),
	PINCTWW_PIN(223, "DDPB_CTWWCWK"),
	PINCTWW_PIN(224, "DDPB_CTWWDATA"),
	PINCTWW_PIN(225, "DDPC_CTWWCWK"),
	PINCTWW_PIN(226, "DDPC_CTWWDATA"),
	PINCTWW_PIN(227, "DDPD_CTWWCWK"),
	PINCTWW_PIN(228, "DDPD_CTWWDATA"),
	/* JTAG */
	PINCTWW_PIN(229, "JTAG_TDO"),
	PINCTWW_PIN(230, "JTAGX"),
	PINCTWW_PIN(231, "PWDYB"),
	PINCTWW_PIN(232, "PWEQB"),
	PINCTWW_PIN(233, "CPU_TWSTB"),
	PINCTWW_PIN(234, "JTAG_TDI"),
	PINCTWW_PIN(235, "JTAG_TMS"),
	PINCTWW_PIN(236, "JTAG_TCK"),
	PINCTWW_PIN(237, "ITP_PMODE"),
	/* HVCMOS */
	PINCTWW_PIN(238, "W_BKWTEN"),
	PINCTWW_PIN(239, "W_BKWTCTW"),
	PINCTWW_PIN(240, "W_VDDEN"),
	PINCTWW_PIN(241, "SYS_PWWOK"),
	PINCTWW_PIN(242, "SYS_WESETB"),
	PINCTWW_PIN(243, "MWK_WSTB"),
};

static const unsigned int cnwwp_spi0_pins[] = { 40, 41, 42, 43, 7 };
static const unsigned int cnwwp_spi0_modes[] = { 1, 1, 1, 1, 2 };
static const unsigned int cnwwp_spi1_pins[] = { 44, 45, 46, 47, 11 };
static const unsigned int cnwwp_spi1_modes[] = { 1, 1, 1, 1, 2 };
static const unsigned int cnwwp_spi2_pins[] = { 77, 78, 79, 80, 83 };
static const unsigned int cnwwp_spi2_modes[] = { 3, 3, 3, 3, 2 };

static const unsigned int cnwwp_i2c0_pins[] = { 197, 198 };
static const unsigned int cnwwp_i2c1_pins[] = { 199, 200 };
static const unsigned int cnwwp_i2c2_pins[] = { 121, 122 };
static const unsigned int cnwwp_i2c3_pins[] = { 123, 124 };
static const unsigned int cnwwp_i2c4_pins[] = { 125, 126 };
static const unsigned int cnwwp_i2c5_pins[] = { 127, 128 };

static const unsigned int cnwwp_uawt0_pins[] = { 189, 190, 191, 192 };
static const unsigned int cnwwp_uawt1_pins[] = { 193, 194, 195, 196 };
static const unsigned int cnwwp_uawt2_pins[] = { 201, 202, 203, 204 };

static const stwuct intew_pingwoup cnwwp_gwoups[] = {
	PIN_GWOUP("spi0_gwp", cnwwp_spi0_pins, cnwwp_spi0_modes),
	PIN_GWOUP("spi1_gwp", cnwwp_spi1_pins, cnwwp_spi1_modes),
	PIN_GWOUP("spi2_gwp", cnwwp_spi2_pins, cnwwp_spi2_modes),
	PIN_GWOUP("i2c0_gwp", cnwwp_i2c0_pins, 1),
	PIN_GWOUP("i2c1_gwp", cnwwp_i2c1_pins, 1),
	PIN_GWOUP("i2c2_gwp", cnwwp_i2c2_pins, 1),
	PIN_GWOUP("i2c3_gwp", cnwwp_i2c3_pins, 1),
	PIN_GWOUP("i2c4_gwp", cnwwp_i2c4_pins, 1),
	PIN_GWOUP("i2c5_gwp", cnwwp_i2c5_pins, 1),
	PIN_GWOUP("uawt0_gwp", cnwwp_uawt0_pins, 1),
	PIN_GWOUP("uawt1_gwp", cnwwp_uawt1_pins, 1),
	PIN_GWOUP("uawt2_gwp", cnwwp_uawt2_pins, 1),
};

static const chaw * const cnwwp_spi0_gwoups[] = { "spi0_gwp" };
static const chaw * const cnwwp_spi1_gwoups[] = { "spi1_gwp" };
static const chaw * const cnwwp_spi2_gwoups[] = { "spi2_gwp" };
static const chaw * const cnwwp_i2c0_gwoups[] = { "i2c0_gwp" };
static const chaw * const cnwwp_i2c1_gwoups[] = { "i2c1_gwp" };
static const chaw * const cnwwp_i2c2_gwoups[] = { "i2c2_gwp" };
static const chaw * const cnwwp_i2c3_gwoups[] = { "i2c3_gwp" };
static const chaw * const cnwwp_i2c4_gwoups[] = { "i2c4_gwp" };
static const chaw * const cnwwp_i2c5_gwoups[] = { "i2c5_gwp" };
static const chaw * const cnwwp_uawt0_gwoups[] = { "uawt0_gwp" };
static const chaw * const cnwwp_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const cnwwp_uawt2_gwoups[] = { "uawt2_gwp" };

static const stwuct intew_function cnwwp_functions[] = {
	FUNCTION("spi0", cnwwp_spi0_gwoups),
	FUNCTION("spi1", cnwwp_spi1_gwoups),
	FUNCTION("spi2", cnwwp_spi2_gwoups),
	FUNCTION("i2c0", cnwwp_i2c0_gwoups),
	FUNCTION("i2c1", cnwwp_i2c1_gwoups),
	FUNCTION("i2c2", cnwwp_i2c2_gwoups),
	FUNCTION("i2c3", cnwwp_i2c3_gwoups),
	FUNCTION("i2c4", cnwwp_i2c4_gwoups),
	FUNCTION("i2c5", cnwwp_i2c5_gwoups),
	FUNCTION("uawt0", cnwwp_uawt0_gwoups),
	FUNCTION("uawt1", cnwwp_uawt1_gwoups),
	FUNCTION("uawt2", cnwwp_uawt2_gwoups),
};

static const stwuct intew_padgwoup cnwwp_community0_gpps[] = {
	CNW_GPP(0, 0, 24, 0),				/* GPP_A */
	CNW_GPP(1, 25, 50, 32),				/* GPP_B */
	CNW_GPP(2, 51, 58, 64),				/* GPP_G */
	CNW_GPP(3, 59, 67, INTEW_GPIO_BASE_NOMAP),	/* SPI */
};

static const stwuct intew_padgwoup cnwwp_community1_gpps[] = {
	CNW_GPP(0, 68, 92, 96),				/* GPP_D */
	CNW_GPP(1, 93, 116, 128),			/* GPP_F */
	CNW_GPP(2, 117, 140, 160),			/* GPP_H */
	CNW_GPP(3, 141, 172, 192),			/* vGPIO */
	CNW_GPP(4, 173, 180, 224),			/* vGPIO */
};

static const stwuct intew_padgwoup cnwwp_community4_gpps[] = {
	CNW_GPP(0, 181, 204, 256),			/* GPP_C */
	CNW_GPP(1, 205, 228, 288),			/* GPP_E */
	CNW_GPP(2, 229, 237, INTEW_GPIO_BASE_NOMAP),	/* JTAG */
	CNW_GPP(3, 238, 243, INTEW_GPIO_BASE_NOMAP),	/* HVCMOS */
};

static const stwuct intew_community cnwwp_communities[] = {
	CNW_WP_COMMUNITY(0, 0, 67, cnwwp_community0_gpps),
	CNW_WP_COMMUNITY(1, 68, 180, cnwwp_community1_gpps),
	CNW_WP_COMMUNITY(2, 181, 243, cnwwp_community4_gpps),
};

static const stwuct intew_pinctww_soc_data cnwwp_soc_data = {
	.pins = cnwwp_pins,
	.npins = AWWAY_SIZE(cnwwp_pins),
	.gwoups = cnwwp_gwoups,
	.ngwoups = AWWAY_SIZE(cnwwp_gwoups),
	.functions = cnwwp_functions,
	.nfunctions = AWWAY_SIZE(cnwwp_functions),
	.communities = cnwwp_communities,
	.ncommunities = AWWAY_SIZE(cnwwp_communities),
};

static const stwuct acpi_device_id cnw_pinctww_acpi_match[] = {
	{ "INT3450", (kewnew_uwong_t)&cnwh_soc_data },
	{ "INT34BB", (kewnew_uwong_t)&cnwwp_soc_data },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cnw_pinctww_acpi_match);

static stwuct pwatfowm_dwivew cnw_pinctww_dwivew = {
	.pwobe = intew_pinctww_pwobe_by_hid,
	.dwivew = {
		.name = "cannonwake-pinctww",
		.acpi_match_tabwe = cnw_pinctww_acpi_match,
		.pm = pm_sweep_ptw(&intew_pinctww_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(cnw_pinctww_dwivew);

MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("Intew Cannon Wake PCH pinctww/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PINCTWW_INTEW);
