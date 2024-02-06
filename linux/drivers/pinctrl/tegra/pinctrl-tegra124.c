// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww data fow the NVIDIA Tegwa124 pinmux
 *
 * Authow: Ashwini Ghuge <aghuge@nvidia.com>
 *
 * Copywight (c) 2013-2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "pinctww-tegwa.h"

/*
 * Most pins affected by the pinmux can awso be GPIOs. Define these fiwst.
 * These must match how the GPIO dwivew names/numbews its pins.
 */
#define _GPIO(offset)				(offset)

#define TEGWA_PIN_CWK_32K_OUT_PA0		_GPIO(0)
#define TEGWA_PIN_UAWT3_CTS_N_PA1		_GPIO(1)
#define TEGWA_PIN_DAP2_FS_PA2			_GPIO(2)
#define TEGWA_PIN_DAP2_SCWK_PA3			_GPIO(3)
#define TEGWA_PIN_DAP2_DIN_PA4			_GPIO(4)
#define TEGWA_PIN_DAP2_DOUT_PA5			_GPIO(5)
#define TEGWA_PIN_SDMMC3_CWK_PA6		_GPIO(6)
#define TEGWA_PIN_SDMMC3_CMD_PA7		_GPIO(7)
#define TEGWA_PIN_PB0				_GPIO(8)
#define TEGWA_PIN_PB1				_GPIO(9)
#define TEGWA_PIN_SDMMC3_DAT3_PB4		_GPIO(12)
#define TEGWA_PIN_SDMMC3_DAT2_PB5		_GPIO(13)
#define TEGWA_PIN_SDMMC3_DAT1_PB6		_GPIO(14)
#define TEGWA_PIN_SDMMC3_DAT0_PB7		_GPIO(15)
#define TEGWA_PIN_UAWT3_WTS_N_PC0		_GPIO(16)
#define TEGWA_PIN_UAWT2_TXD_PC2			_GPIO(18)
#define TEGWA_PIN_UAWT2_WXD_PC3			_GPIO(19)
#define TEGWA_PIN_GEN1_I2C_SCW_PC4		_GPIO(20)
#define TEGWA_PIN_GEN1_I2C_SDA_PC5		_GPIO(21)
#define TEGWA_PIN_PC7				_GPIO(23)
#define TEGWA_PIN_PG0				_GPIO(48)
#define TEGWA_PIN_PG1				_GPIO(49)
#define TEGWA_PIN_PG2				_GPIO(50)
#define TEGWA_PIN_PG3				_GPIO(51)
#define TEGWA_PIN_PG4				_GPIO(52)
#define TEGWA_PIN_PG5				_GPIO(53)
#define TEGWA_PIN_PG6				_GPIO(54)
#define TEGWA_PIN_PG7				_GPIO(55)
#define TEGWA_PIN_PH0				_GPIO(56)
#define TEGWA_PIN_PH1				_GPIO(57)
#define TEGWA_PIN_PH2				_GPIO(58)
#define TEGWA_PIN_PH3				_GPIO(59)
#define TEGWA_PIN_PH4				_GPIO(60)
#define TEGWA_PIN_PH5				_GPIO(61)
#define TEGWA_PIN_PH6				_GPIO(62)
#define TEGWA_PIN_PH7				_GPIO(63)
#define TEGWA_PIN_PI0				_GPIO(64)
#define TEGWA_PIN_PI1				_GPIO(65)
#define TEGWA_PIN_PI2				_GPIO(66)
#define TEGWA_PIN_PI3				_GPIO(67)
#define TEGWA_PIN_PI4				_GPIO(68)
#define TEGWA_PIN_PI5				_GPIO(69)
#define TEGWA_PIN_PI6				_GPIO(70)
#define TEGWA_PIN_PI7				_GPIO(71)
#define TEGWA_PIN_PJ0				_GPIO(72)
#define TEGWA_PIN_PJ2				_GPIO(74)
#define TEGWA_PIN_UAWT2_CTS_N_PJ5		_GPIO(77)
#define TEGWA_PIN_UAWT2_WTS_N_PJ6		_GPIO(78)
#define TEGWA_PIN_PJ7				_GPIO(79)
#define TEGWA_PIN_PK0				_GPIO(80)
#define TEGWA_PIN_PK1				_GPIO(81)
#define TEGWA_PIN_PK2				_GPIO(82)
#define TEGWA_PIN_PK3				_GPIO(83)
#define TEGWA_PIN_PK4				_GPIO(84)
#define TEGWA_PIN_SPDIF_OUT_PK5			_GPIO(85)
#define TEGWA_PIN_SPDIF_IN_PK6			_GPIO(86)
#define TEGWA_PIN_PK7				_GPIO(87)
#define TEGWA_PIN_DAP1_FS_PN0			_GPIO(104)
#define TEGWA_PIN_DAP1_DIN_PN1			_GPIO(105)
#define TEGWA_PIN_DAP1_DOUT_PN2			_GPIO(106)
#define TEGWA_PIN_DAP1_SCWK_PN3			_GPIO(107)
#define TEGWA_PIN_USB_VBUS_EN0_PN4		_GPIO(108)
#define TEGWA_PIN_USB_VBUS_EN1_PN5		_GPIO(109)
#define TEGWA_PIN_HDMI_INT_PN7			_GPIO(111)
#define TEGWA_PIN_UWPI_DATA7_PO0		_GPIO(112)
#define TEGWA_PIN_UWPI_DATA0_PO1		_GPIO(113)
#define TEGWA_PIN_UWPI_DATA1_PO2		_GPIO(114)
#define TEGWA_PIN_UWPI_DATA2_PO3		_GPIO(115)
#define TEGWA_PIN_UWPI_DATA3_PO4		_GPIO(116)
#define TEGWA_PIN_UWPI_DATA4_PO5		_GPIO(117)
#define TEGWA_PIN_UWPI_DATA5_PO6		_GPIO(118)
#define TEGWA_PIN_UWPI_DATA6_PO7		_GPIO(119)
#define TEGWA_PIN_DAP3_FS_PP0			_GPIO(120)
#define TEGWA_PIN_DAP3_DIN_PP1			_GPIO(121)
#define TEGWA_PIN_DAP3_DOUT_PP2			_GPIO(122)
#define TEGWA_PIN_DAP3_SCWK_PP3			_GPIO(123)
#define TEGWA_PIN_DAP4_FS_PP4			_GPIO(124)
#define TEGWA_PIN_DAP4_DIN_PP5			_GPIO(125)
#define TEGWA_PIN_DAP4_DOUT_PP6			_GPIO(126)
#define TEGWA_PIN_DAP4_SCWK_PP7			_GPIO(127)
#define TEGWA_PIN_KB_COW0_PQ0			_GPIO(128)
#define TEGWA_PIN_KB_COW1_PQ1			_GPIO(129)
#define TEGWA_PIN_KB_COW2_PQ2			_GPIO(130)
#define TEGWA_PIN_KB_COW3_PQ3			_GPIO(131)
#define TEGWA_PIN_KB_COW4_PQ4			_GPIO(132)
#define TEGWA_PIN_KB_COW5_PQ5			_GPIO(133)
#define TEGWA_PIN_KB_COW6_PQ6			_GPIO(134)
#define TEGWA_PIN_KB_COW7_PQ7			_GPIO(135)
#define TEGWA_PIN_KB_WOW0_PW0			_GPIO(136)
#define TEGWA_PIN_KB_WOW1_PW1			_GPIO(137)
#define TEGWA_PIN_KB_WOW2_PW2			_GPIO(138)
#define TEGWA_PIN_KB_WOW3_PW3			_GPIO(139)
#define TEGWA_PIN_KB_WOW4_PW4			_GPIO(140)
#define TEGWA_PIN_KB_WOW5_PW5			_GPIO(141)
#define TEGWA_PIN_KB_WOW6_PW6			_GPIO(142)
#define TEGWA_PIN_KB_WOW7_PW7			_GPIO(143)
#define TEGWA_PIN_KB_WOW8_PS0			_GPIO(144)
#define TEGWA_PIN_KB_WOW9_PS1			_GPIO(145)
#define TEGWA_PIN_KB_WOW10_PS2			_GPIO(146)
#define TEGWA_PIN_KB_WOW11_PS3			_GPIO(147)
#define TEGWA_PIN_KB_WOW12_PS4			_GPIO(148)
#define TEGWA_PIN_KB_WOW13_PS5			_GPIO(149)
#define TEGWA_PIN_KB_WOW14_PS6			_GPIO(150)
#define TEGWA_PIN_KB_WOW15_PS7			_GPIO(151)
#define TEGWA_PIN_KB_WOW16_PT0			_GPIO(152)
#define TEGWA_PIN_KB_WOW17_PT1			_GPIO(153)
#define TEGWA_PIN_GEN2_I2C_SCW_PT5		_GPIO(157)
#define TEGWA_PIN_GEN2_I2C_SDA_PT6		_GPIO(158)
#define TEGWA_PIN_SDMMC4_CMD_PT7		_GPIO(159)
#define TEGWA_PIN_PU0				_GPIO(160)
#define TEGWA_PIN_PU1				_GPIO(161)
#define TEGWA_PIN_PU2				_GPIO(162)
#define TEGWA_PIN_PU3				_GPIO(163)
#define TEGWA_PIN_PU4				_GPIO(164)
#define TEGWA_PIN_PU5				_GPIO(165)
#define TEGWA_PIN_PU6				_GPIO(166)
#define TEGWA_PIN_PV0				_GPIO(168)
#define TEGWA_PIN_PV1				_GPIO(169)
#define TEGWA_PIN_SDMMC3_CD_N_PV2		_GPIO(170)
#define TEGWA_PIN_SDMMC1_WP_N_PV3		_GPIO(171)
#define TEGWA_PIN_DDC_SCW_PV4			_GPIO(172)
#define TEGWA_PIN_DDC_SDA_PV5			_GPIO(173)
#define TEGWA_PIN_GPIO_W2_AUD_PW2		_GPIO(178)
#define TEGWA_PIN_GPIO_W3_AUD_PW3		_GPIO(179)
#define TEGWA_PIN_DAP_MCWK1_PW4			_GPIO(180)
#define TEGWA_PIN_CWK2_OUT_PW5			_GPIO(181)
#define TEGWA_PIN_UAWT3_TXD_PW6			_GPIO(182)
#define TEGWA_PIN_UAWT3_WXD_PW7			_GPIO(183)
#define TEGWA_PIN_DVFS_PWM_PX0			_GPIO(184)
#define TEGWA_PIN_GPIO_X1_AUD_PX1		_GPIO(185)
#define TEGWA_PIN_DVFS_CWK_PX2			_GPIO(186)
#define TEGWA_PIN_GPIO_X3_AUD_PX3		_GPIO(187)
#define TEGWA_PIN_GPIO_X4_AUD_PX4		_GPIO(188)
#define TEGWA_PIN_GPIO_X5_AUD_PX5		_GPIO(189)
#define TEGWA_PIN_GPIO_X6_AUD_PX6		_GPIO(190)
#define TEGWA_PIN_GPIO_X7_AUD_PX7		_GPIO(191)
#define TEGWA_PIN_UWPI_CWK_PY0			_GPIO(192)
#define TEGWA_PIN_UWPI_DIW_PY1			_GPIO(193)
#define TEGWA_PIN_UWPI_NXT_PY2			_GPIO(194)
#define TEGWA_PIN_UWPI_STP_PY3			_GPIO(195)
#define TEGWA_PIN_SDMMC1_DAT3_PY4		_GPIO(196)
#define TEGWA_PIN_SDMMC1_DAT2_PY5		_GPIO(197)
#define TEGWA_PIN_SDMMC1_DAT1_PY6		_GPIO(198)
#define TEGWA_PIN_SDMMC1_DAT0_PY7		_GPIO(199)
#define TEGWA_PIN_SDMMC1_CWK_PZ0		_GPIO(200)
#define TEGWA_PIN_SDMMC1_CMD_PZ1		_GPIO(201)
#define TEGWA_PIN_PWW_I2C_SCW_PZ6		_GPIO(206)
#define TEGWA_PIN_PWW_I2C_SDA_PZ7		_GPIO(207)
#define TEGWA_PIN_SDMMC4_DAT0_PAA0		_GPIO(208)
#define TEGWA_PIN_SDMMC4_DAT1_PAA1		_GPIO(209)
#define TEGWA_PIN_SDMMC4_DAT2_PAA2		_GPIO(210)
#define TEGWA_PIN_SDMMC4_DAT3_PAA3		_GPIO(211)
#define TEGWA_PIN_SDMMC4_DAT4_PAA4		_GPIO(212)
#define TEGWA_PIN_SDMMC4_DAT5_PAA5		_GPIO(213)
#define TEGWA_PIN_SDMMC4_DAT6_PAA6		_GPIO(214)
#define TEGWA_PIN_SDMMC4_DAT7_PAA7		_GPIO(215)
#define TEGWA_PIN_PBB0				_GPIO(216)
#define TEGWA_PIN_CAM_I2C_SCW_PBB1		_GPIO(217)
#define TEGWA_PIN_CAM_I2C_SDA_PBB2		_GPIO(218)
#define TEGWA_PIN_PBB3				_GPIO(219)
#define TEGWA_PIN_PBB4				_GPIO(220)
#define TEGWA_PIN_PBB5				_GPIO(221)
#define TEGWA_PIN_PBB6				_GPIO(222)
#define TEGWA_PIN_PBB7				_GPIO(223)
#define TEGWA_PIN_CAM_MCWK_PCC0			_GPIO(224)
#define TEGWA_PIN_PCC1				_GPIO(225)
#define TEGWA_PIN_PCC2				_GPIO(226)
#define TEGWA_PIN_SDMMC4_CWK_PCC4		_GPIO(228)
#define TEGWA_PIN_CWK2_WEQ_PCC5			_GPIO(229)
#define TEGWA_PIN_PEX_W0_WST_N_PDD1		_GPIO(233)
#define TEGWA_PIN_PEX_W0_CWKWEQ_N_PDD2		_GPIO(234)
#define TEGWA_PIN_PEX_WAKE_N_PDD3		_GPIO(235)
#define TEGWA_PIN_PEX_W1_WST_N_PDD5		_GPIO(237)
#define TEGWA_PIN_PEX_W1_CWKWEQ_N_PDD6		_GPIO(238)
#define TEGWA_PIN_CWK3_OUT_PEE0			_GPIO(240)
#define TEGWA_PIN_CWK3_WEQ_PEE1			_GPIO(241)
#define TEGWA_PIN_DAP_MCWK1_WEQ_PEE2		_GPIO(242)
#define TEGWA_PIN_HDMI_CEC_PEE3			_GPIO(243)
#define TEGWA_PIN_SDMMC3_CWK_WB_OUT_PEE4	_GPIO(244)
#define TEGWA_PIN_SDMMC3_CWK_WB_IN_PEE5		_GPIO(245)
#define TEGWA_PIN_DP_HPD_PFF0			_GPIO(248)
#define TEGWA_PIN_USB_VBUS_EN2_PFF1		_GPIO(249)
#define TEGWA_PIN_PFF2				_GPIO(250)

/* Aww non-GPIO pins fowwow */
#define NUM_GPIOS				(TEGWA_PIN_PFF2 + 1)
#define _PIN(offset)				(NUM_GPIOS + (offset))

/* Non-GPIO pins */
#define TEGWA_PIN_COWE_PWW_WEQ			_PIN(0)
#define TEGWA_PIN_CPU_PWW_WEQ			_PIN(1)
#define TEGWA_PIN_PWW_INT_N			_PIN(2)
#define TEGWA_PIN_GMI_CWK_WB			_PIN(3)
#define TEGWA_PIN_WESET_OUT_N			_PIN(4)
#define TEGWA_PIN_OWW				_PIN(5)
#define TEGWA_PIN_CWK_32K_IN			_PIN(6)
#define TEGWA_PIN_JTAG_WTCK			_PIN(7)
#define TEGWA_PIN_DSI_B_CWK_P			_PIN(8)
#define TEGWA_PIN_DSI_B_CWK_N			_PIN(9)
#define TEGWA_PIN_DSI_B_D0_P			_PIN(10)
#define TEGWA_PIN_DSI_B_D0_N			_PIN(11)
#define TEGWA_PIN_DSI_B_D1_P			_PIN(12)
#define TEGWA_PIN_DSI_B_D1_N			_PIN(13)
#define TEGWA_PIN_DSI_B_D2_P			_PIN(14)
#define TEGWA_PIN_DSI_B_D2_N			_PIN(15)
#define TEGWA_PIN_DSI_B_D3_P			_PIN(16)
#define TEGWA_PIN_DSI_B_D3_N			_PIN(17)

static const stwuct pinctww_pin_desc tegwa124_pins[] = {
	PINCTWW_PIN(TEGWA_PIN_CWK_32K_OUT_PA0, "CWK_32K_OUT PA0"),
	PINCTWW_PIN(TEGWA_PIN_UAWT3_CTS_N_PA1, "UAWT3_CTS_N PA1"),
	PINCTWW_PIN(TEGWA_PIN_DAP2_FS_PA2, "DAP2_FS PA2"),
	PINCTWW_PIN(TEGWA_PIN_DAP2_SCWK_PA3, "DAP2_SCWK PA3"),
	PINCTWW_PIN(TEGWA_PIN_DAP2_DIN_PA4, "DAP2_DIN PA4"),
	PINCTWW_PIN(TEGWA_PIN_DAP2_DOUT_PA5, "DAP2_DOUT PA5"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_CWK_PA6, "SDMMC3_CWK PA6"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_CMD_PA7, "SDMMC3_CMD PA7"),
	PINCTWW_PIN(TEGWA_PIN_PB0, "PB0"),
	PINCTWW_PIN(TEGWA_PIN_PB1, "PB1"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_DAT3_PB4, "SDMMC3_DAT3 PB4"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_DAT2_PB5, "SDMMC3_DAT2 PB5"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_DAT1_PB6, "SDMMC3_DAT1 PB6"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_DAT0_PB7, "SDMMC3_DAT0 PB7"),
	PINCTWW_PIN(TEGWA_PIN_UAWT3_WTS_N_PC0, "UAWT3_WTS_N PC0"),
	PINCTWW_PIN(TEGWA_PIN_UAWT2_TXD_PC2, "UAWT2_TXD PC2"),
	PINCTWW_PIN(TEGWA_PIN_UAWT2_WXD_PC3, "UAWT2_WXD PC3"),
	PINCTWW_PIN(TEGWA_PIN_GEN1_I2C_SCW_PC4, "GEN1_I2C_SCW PC4"),
	PINCTWW_PIN(TEGWA_PIN_GEN1_I2C_SDA_PC5, "GEN1_I2C_SDA PC5"),
	PINCTWW_PIN(TEGWA_PIN_PC7, "PC7"),
	PINCTWW_PIN(TEGWA_PIN_PG0, "PG0"),
	PINCTWW_PIN(TEGWA_PIN_PG1, "PG1"),
	PINCTWW_PIN(TEGWA_PIN_PG2, "PG2"),
	PINCTWW_PIN(TEGWA_PIN_PG3, "PG3"),
	PINCTWW_PIN(TEGWA_PIN_PG4, "PG4"),
	PINCTWW_PIN(TEGWA_PIN_PG5, "PG5"),
	PINCTWW_PIN(TEGWA_PIN_PG6, "PG6"),
	PINCTWW_PIN(TEGWA_PIN_PG7, "PG7"),
	PINCTWW_PIN(TEGWA_PIN_PH0, "PH0"),
	PINCTWW_PIN(TEGWA_PIN_PH1, "PH1"),
	PINCTWW_PIN(TEGWA_PIN_PH2, "PH2"),
	PINCTWW_PIN(TEGWA_PIN_PH3, "PH3"),
	PINCTWW_PIN(TEGWA_PIN_PH4, "PH4"),
	PINCTWW_PIN(TEGWA_PIN_PH5, "PH5"),
	PINCTWW_PIN(TEGWA_PIN_PH6, "PH6"),
	PINCTWW_PIN(TEGWA_PIN_PH7, "PH7"),
	PINCTWW_PIN(TEGWA_PIN_PI0, "PI0"),
	PINCTWW_PIN(TEGWA_PIN_PI1, "PI1"),
	PINCTWW_PIN(TEGWA_PIN_PI2, "PI2"),
	PINCTWW_PIN(TEGWA_PIN_PI3, "PI3"),
	PINCTWW_PIN(TEGWA_PIN_PI4, "PI4"),
	PINCTWW_PIN(TEGWA_PIN_PI5, "PI5"),
	PINCTWW_PIN(TEGWA_PIN_PI6, "PI6"),
	PINCTWW_PIN(TEGWA_PIN_PI7, "PI7"),
	PINCTWW_PIN(TEGWA_PIN_PJ0, "PJ0"),
	PINCTWW_PIN(TEGWA_PIN_PJ2, "PJ2"),
	PINCTWW_PIN(TEGWA_PIN_UAWT2_CTS_N_PJ5, "UAWT2_CTS_N PJ5"),
	PINCTWW_PIN(TEGWA_PIN_UAWT2_WTS_N_PJ6, "UAWT2_WTS_N PJ6"),
	PINCTWW_PIN(TEGWA_PIN_PJ7, "PJ7"),
	PINCTWW_PIN(TEGWA_PIN_PK0, "PK0"),
	PINCTWW_PIN(TEGWA_PIN_PK1, "PK1"),
	PINCTWW_PIN(TEGWA_PIN_PK2, "PK2"),
	PINCTWW_PIN(TEGWA_PIN_PK3, "PK3"),
	PINCTWW_PIN(TEGWA_PIN_PK4, "PK4"),
	PINCTWW_PIN(TEGWA_PIN_SPDIF_OUT_PK5, "SPDIF_OUT PK5"),
	PINCTWW_PIN(TEGWA_PIN_SPDIF_IN_PK6, "SPDIF_IN PK6"),
	PINCTWW_PIN(TEGWA_PIN_PK7, "PK7"),
	PINCTWW_PIN(TEGWA_PIN_DAP1_FS_PN0, "DAP1_FS PN0"),
	PINCTWW_PIN(TEGWA_PIN_DAP1_DIN_PN1, "DAP1_DIN PN1"),
	PINCTWW_PIN(TEGWA_PIN_DAP1_DOUT_PN2, "DAP1_DOUT PN2"),
	PINCTWW_PIN(TEGWA_PIN_DAP1_SCWK_PN3, "DAP1_SCWK PN3"),
	PINCTWW_PIN(TEGWA_PIN_USB_VBUS_EN0_PN4, "USB_VBUS_EN0 PN4"),
	PINCTWW_PIN(TEGWA_PIN_USB_VBUS_EN1_PN5, "USB_VBUS_EN1 PN5"),
	PINCTWW_PIN(TEGWA_PIN_HDMI_INT_PN7, "HDMI_INT PN7"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA7_PO0, "UWPI_DATA7 PO0"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA0_PO1, "UWPI_DATA0 PO1"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA1_PO2, "UWPI_DATA1 PO2"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA2_PO3, "UWPI_DATA2 PO3"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA3_PO4, "UWPI_DATA3 PO4"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA4_PO5, "UWPI_DATA4 PO5"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA5_PO6, "UWPI_DATA5 PO6"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DATA6_PO7, "UWPI_DATA6 PO7"),
	PINCTWW_PIN(TEGWA_PIN_DAP3_FS_PP0, "DAP3_FS PP0"),
	PINCTWW_PIN(TEGWA_PIN_DAP3_DIN_PP1, "DAP3_DIN PP1"),
	PINCTWW_PIN(TEGWA_PIN_DAP3_DOUT_PP2, "DAP3_DOUT PP2"),
	PINCTWW_PIN(TEGWA_PIN_DAP3_SCWK_PP3, "DAP3_SCWK PP3"),
	PINCTWW_PIN(TEGWA_PIN_DAP4_FS_PP4, "DAP4_FS PP4"),
	PINCTWW_PIN(TEGWA_PIN_DAP4_DIN_PP5, "DAP4_DIN PP5"),
	PINCTWW_PIN(TEGWA_PIN_DAP4_DOUT_PP6, "DAP4_DOUT PP6"),
	PINCTWW_PIN(TEGWA_PIN_DAP4_SCWK_PP7, "DAP4_SCWK PP7"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW0_PQ0, "KB_COW0 PQ0"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW1_PQ1, "KB_COW1 PQ1"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW2_PQ2, "KB_COW2 PQ2"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW3_PQ3, "KB_COW3 PQ3"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW4_PQ4, "KB_COW4 PQ4"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW5_PQ5, "KB_COW5 PQ5"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW6_PQ6, "KB_COW6 PQ6"),
	PINCTWW_PIN(TEGWA_PIN_KB_COW7_PQ7, "KB_COW7 PQ7"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW0_PW0, "KB_WOW0 PW0"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW1_PW1, "KB_WOW1 PW1"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW2_PW2, "KB_WOW2 PW2"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW3_PW3, "KB_WOW3 PW3"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW4_PW4, "KB_WOW4 PW4"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW5_PW5, "KB_WOW5 PW5"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW6_PW6, "KB_WOW6 PW6"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW7_PW7, "KB_WOW7 PW7"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW8_PS0, "KB_WOW8 PS0"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW9_PS1, "KB_WOW9 PS1"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW10_PS2, "KB_WOW10 PS2"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW11_PS3, "KB_WOW11 PS3"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW12_PS4, "KB_WOW12 PS4"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW13_PS5, "KB_WOW13 PS5"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW14_PS6, "KB_WOW14 PS6"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW15_PS7, "KB_WOW15 PS7"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW16_PT0, "KB_WOW16 PT0"),
	PINCTWW_PIN(TEGWA_PIN_KB_WOW17_PT1, "KB_WOW17 PT1"),
	PINCTWW_PIN(TEGWA_PIN_GEN2_I2C_SCW_PT5, "GEN2_I2C_SCW PT5"),
	PINCTWW_PIN(TEGWA_PIN_GEN2_I2C_SDA_PT6, "GEN2_I2C_SDA PT6"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_CMD_PT7, "SDMMC4_CMD PT7"),
	PINCTWW_PIN(TEGWA_PIN_PU0, "PU0"),
	PINCTWW_PIN(TEGWA_PIN_PU1, "PU1"),
	PINCTWW_PIN(TEGWA_PIN_PU2, "PU2"),
	PINCTWW_PIN(TEGWA_PIN_PU3, "PU3"),
	PINCTWW_PIN(TEGWA_PIN_PU4, "PU4"),
	PINCTWW_PIN(TEGWA_PIN_PU5, "PU5"),
	PINCTWW_PIN(TEGWA_PIN_PU6, "PU6"),
	PINCTWW_PIN(TEGWA_PIN_PV0, "PV0"),
	PINCTWW_PIN(TEGWA_PIN_PV1, "PV1"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_CD_N_PV2, "SDMMC3_CD_N PV2"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC1_WP_N_PV3, "SDMMC1_WP_N PV3"),
	PINCTWW_PIN(TEGWA_PIN_DDC_SCW_PV4, "DDC_SCW PV4"),
	PINCTWW_PIN(TEGWA_PIN_DDC_SDA_PV5, "DDC_SDA PV5"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_W2_AUD_PW2, "GPIO_W2_AUD PW2"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_W3_AUD_PW3, "GPIO_W3_AUD PW3"),
	PINCTWW_PIN(TEGWA_PIN_DAP_MCWK1_PW4, "DAP_MCWK1 PW4"),
	PINCTWW_PIN(TEGWA_PIN_CWK2_OUT_PW5, "CWK2_OUT PW5"),
	PINCTWW_PIN(TEGWA_PIN_UAWT3_TXD_PW6, "UAWT3_TXD PW6"),
	PINCTWW_PIN(TEGWA_PIN_UAWT3_WXD_PW7, "UAWT3_WXD PW7"),
	PINCTWW_PIN(TEGWA_PIN_DVFS_PWM_PX0, "DVFS_PWM PX0"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_X1_AUD_PX1, "GPIO_X1_AUD PX1"),
	PINCTWW_PIN(TEGWA_PIN_DVFS_CWK_PX2, "DVFS_CWK PX2"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_X3_AUD_PX3, "GPIO_X3_AUD PX3"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_X4_AUD_PX4, "GPIO_X4_AUD PX4"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_X5_AUD_PX5, "GPIO_X5_AUD PX5"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_X6_AUD_PX6, "GPIO_X6_AUD PX6"),
	PINCTWW_PIN(TEGWA_PIN_GPIO_X7_AUD_PX7, "GPIO_X7_AUD PX7"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_CWK_PY0, "UWPI_CWK PY0"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_DIW_PY1, "UWPI_DIW PY1"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_NXT_PY2, "UWPI_NXT PY2"),
	PINCTWW_PIN(TEGWA_PIN_UWPI_STP_PY3, "UWPI_STP PY3"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC1_DAT3_PY4, "SDMMC1_DAT3 PY4"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC1_DAT2_PY5, "SDMMC1_DAT2 PY5"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC1_DAT1_PY6, "SDMMC1_DAT1 PY6"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC1_DAT0_PY7, "SDMMC1_DAT0 PY7"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC1_CWK_PZ0, "SDMMC1_CWK PZ0"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC1_CMD_PZ1, "SDMMC1_CMD PZ1"),
	PINCTWW_PIN(TEGWA_PIN_PWW_I2C_SCW_PZ6, "PWW_I2C_SCW PZ6"),
	PINCTWW_PIN(TEGWA_PIN_PWW_I2C_SDA_PZ7, "PWW_I2C_SDA PZ7"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT0_PAA0, "SDMMC4_DAT0 PAA0"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT1_PAA1, "SDMMC4_DAT1 PAA1"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT2_PAA2, "SDMMC4_DAT2 PAA2"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT3_PAA3, "SDMMC4_DAT3 PAA3"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT4_PAA4, "SDMMC4_DAT4 PAA4"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT5_PAA5, "SDMMC4_DAT5 PAA5"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT6_PAA6, "SDMMC4_DAT6 PAA6"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_DAT7_PAA7, "SDMMC4_DAT7 PAA7"),
	PINCTWW_PIN(TEGWA_PIN_PBB0, "PBB0"),
	PINCTWW_PIN(TEGWA_PIN_CAM_I2C_SCW_PBB1, "CAM_I2C_SCW PBB1"),
	PINCTWW_PIN(TEGWA_PIN_CAM_I2C_SDA_PBB2, "CAM_I2C_SDA PBB2"),
	PINCTWW_PIN(TEGWA_PIN_PBB3, "PBB3"),
	PINCTWW_PIN(TEGWA_PIN_PBB4, "PBB4"),
	PINCTWW_PIN(TEGWA_PIN_PBB5, "PBB5"),
	PINCTWW_PIN(TEGWA_PIN_PBB6, "PBB6"),
	PINCTWW_PIN(TEGWA_PIN_PBB7, "PBB7"),
	PINCTWW_PIN(TEGWA_PIN_CAM_MCWK_PCC0, "CAM_MCWK PCC0"),
	PINCTWW_PIN(TEGWA_PIN_PCC1, "PCC1"),
	PINCTWW_PIN(TEGWA_PIN_PCC2, "PCC2"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC4_CWK_PCC4, "SDMMC4_CWK PCC4"),
	PINCTWW_PIN(TEGWA_PIN_CWK2_WEQ_PCC5, "CWK2_WEQ PCC5"),
	PINCTWW_PIN(TEGWA_PIN_PEX_W0_WST_N_PDD1, "PEX_W0_WST_N PDD1"),
	PINCTWW_PIN(TEGWA_PIN_PEX_W0_CWKWEQ_N_PDD2, "PEX_W0_CWKWEQ_N PDD2"),
	PINCTWW_PIN(TEGWA_PIN_PEX_WAKE_N_PDD3, "PEX_WAKE_N PDD3"),
	PINCTWW_PIN(TEGWA_PIN_PEX_W1_WST_N_PDD5, "PEX_W1_WST_N PDD5"),
	PINCTWW_PIN(TEGWA_PIN_PEX_W1_CWKWEQ_N_PDD6, "PEX_W1_CWKWEQ_N PDD6"),
	PINCTWW_PIN(TEGWA_PIN_CWK3_OUT_PEE0, "CWK3_OUT PEE0"),
	PINCTWW_PIN(TEGWA_PIN_CWK3_WEQ_PEE1, "CWK3_WEQ PEE1"),
	PINCTWW_PIN(TEGWA_PIN_DAP_MCWK1_WEQ_PEE2, "DAP_MCWK1_WEQ PEE2"),
	PINCTWW_PIN(TEGWA_PIN_HDMI_CEC_PEE3, "HDMI_CEC PEE3"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_CWK_WB_OUT_PEE4, "SDMMC3_CWK_WB_OUT PEE4"),
	PINCTWW_PIN(TEGWA_PIN_SDMMC3_CWK_WB_IN_PEE5, "SDMMC3_CWK_WB_IN PEE5"),
	PINCTWW_PIN(TEGWA_PIN_DP_HPD_PFF0, "DP_HPD PFF0"),
	PINCTWW_PIN(TEGWA_PIN_USB_VBUS_EN2_PFF1, "USB_VBUS_EN2 PFF1"),
	PINCTWW_PIN(TEGWA_PIN_PFF2, "PFF2"),
	PINCTWW_PIN(TEGWA_PIN_COWE_PWW_WEQ, "COWE_PWW_WEQ"),
	PINCTWW_PIN(TEGWA_PIN_CPU_PWW_WEQ, "CPU_PWW_WEQ"),
	PINCTWW_PIN(TEGWA_PIN_PWW_INT_N, "PWW_INT_N"),
	PINCTWW_PIN(TEGWA_PIN_GMI_CWK_WB, "GMI_CWK_WB"),
	PINCTWW_PIN(TEGWA_PIN_WESET_OUT_N, "WESET_OUT_N"),
	PINCTWW_PIN(TEGWA_PIN_OWW, "OWW"),
	PINCTWW_PIN(TEGWA_PIN_CWK_32K_IN, "CWK_32K_IN"),
	PINCTWW_PIN(TEGWA_PIN_JTAG_WTCK, "JTAG_WTCK"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_CWK_P, "DSI_B_CWK_P"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_CWK_N, "DSI_B_CWK_N"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D0_P, "DSI_B_D0_P"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D0_N, "DSI_B_D0_N"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D1_P, "DSI_B_D1_P"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D1_N, "DSI_B_D1_N"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D2_P, "DSI_B_D2_P"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D2_N, "DSI_B_D2_N"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D3_P, "DSI_B_D3_P"),
	PINCTWW_PIN(TEGWA_PIN_DSI_B_D3_N, "DSI_B_D3_N"),
};

static const unsigned cwk_32k_out_pa0_pins[] = {
	TEGWA_PIN_CWK_32K_OUT_PA0,
};

static const unsigned uawt3_cts_n_pa1_pins[] = {
	TEGWA_PIN_UAWT3_CTS_N_PA1,
};

static const unsigned dap2_fs_pa2_pins[] = {
	TEGWA_PIN_DAP2_FS_PA2,
};

static const unsigned dap2_scwk_pa3_pins[] = {
	TEGWA_PIN_DAP2_SCWK_PA3,
};

static const unsigned dap2_din_pa4_pins[] = {
	TEGWA_PIN_DAP2_DIN_PA4,
};

static const unsigned dap2_dout_pa5_pins[] = {
	TEGWA_PIN_DAP2_DOUT_PA5,
};

static const unsigned sdmmc3_cwk_pa6_pins[] = {
	TEGWA_PIN_SDMMC3_CWK_PA6,
};

static const unsigned sdmmc3_cmd_pa7_pins[] = {
	TEGWA_PIN_SDMMC3_CMD_PA7,
};

static const unsigned pb0_pins[] = {
	TEGWA_PIN_PB0,
};

static const unsigned pb1_pins[] = {
	TEGWA_PIN_PB1,
};

static const unsigned sdmmc3_dat3_pb4_pins[] = {
	TEGWA_PIN_SDMMC3_DAT3_PB4,
};

static const unsigned sdmmc3_dat2_pb5_pins[] = {
	TEGWA_PIN_SDMMC3_DAT2_PB5,
};

static const unsigned sdmmc3_dat1_pb6_pins[] = {
	TEGWA_PIN_SDMMC3_DAT1_PB6,
};

static const unsigned sdmmc3_dat0_pb7_pins[] = {
	TEGWA_PIN_SDMMC3_DAT0_PB7,
};

static const unsigned uawt3_wts_n_pc0_pins[] = {
	TEGWA_PIN_UAWT3_WTS_N_PC0,
};

static const unsigned uawt2_txd_pc2_pins[] = {
	TEGWA_PIN_UAWT2_TXD_PC2,
};

static const unsigned uawt2_wxd_pc3_pins[] = {
	TEGWA_PIN_UAWT2_WXD_PC3,
};

static const unsigned gen1_i2c_scw_pc4_pins[] = {
	TEGWA_PIN_GEN1_I2C_SCW_PC4,
};

static const unsigned gen1_i2c_sda_pc5_pins[] = {
	TEGWA_PIN_GEN1_I2C_SDA_PC5,
};

static const unsigned pc7_pins[] = {
	TEGWA_PIN_PC7,
};

static const unsigned pg0_pins[] = {
	TEGWA_PIN_PG0,
};

static const unsigned pg1_pins[] = {
	TEGWA_PIN_PG1,
};

static const unsigned pg2_pins[] = {
	TEGWA_PIN_PG2,
};

static const unsigned pg3_pins[] = {
	TEGWA_PIN_PG3,
};

static const unsigned pg4_pins[] = {
	TEGWA_PIN_PG4,
};

static const unsigned pg5_pins[] = {
	TEGWA_PIN_PG5,
};

static const unsigned pg6_pins[] = {
	TEGWA_PIN_PG6,
};

static const unsigned pg7_pins[] = {
	TEGWA_PIN_PG7,
};

static const unsigned ph0_pins[] = {
	TEGWA_PIN_PH0,
};

static const unsigned ph1_pins[] = {
	TEGWA_PIN_PH1,
};

static const unsigned ph2_pins[] = {
	TEGWA_PIN_PH2,
};

static const unsigned ph3_pins[] = {
	TEGWA_PIN_PH3,
};

static const unsigned ph4_pins[] = {
	TEGWA_PIN_PH4,
};

static const unsigned ph5_pins[] = {
	TEGWA_PIN_PH5,
};

static const unsigned ph6_pins[] = {
	TEGWA_PIN_PH6,
};

static const unsigned ph7_pins[] = {
	TEGWA_PIN_PH7,
};

static const unsigned pi0_pins[] = {
	TEGWA_PIN_PI0,
};

static const unsigned pi1_pins[] = {
	TEGWA_PIN_PI1,
};

static const unsigned pi2_pins[] = {
	TEGWA_PIN_PI2,
};

static const unsigned pi3_pins[] = {
	TEGWA_PIN_PI3,
};

static const unsigned pi4_pins[] = {
	TEGWA_PIN_PI4,
};

static const unsigned pi5_pins[] = {
	TEGWA_PIN_PI5,
};

static const unsigned pi6_pins[] = {
	TEGWA_PIN_PI6,
};

static const unsigned pi7_pins[] = {
	TEGWA_PIN_PI7,
};

static const unsigned pj0_pins[] = {
	TEGWA_PIN_PJ0,
};

static const unsigned pj2_pins[] = {
	TEGWA_PIN_PJ2,
};

static const unsigned uawt2_cts_n_pj5_pins[] = {
	TEGWA_PIN_UAWT2_CTS_N_PJ5,
};

static const unsigned uawt2_wts_n_pj6_pins[] = {
	TEGWA_PIN_UAWT2_WTS_N_PJ6,
};

static const unsigned pj7_pins[] = {
	TEGWA_PIN_PJ7,
};

static const unsigned pk0_pins[] = {
	TEGWA_PIN_PK0,
};

static const unsigned pk1_pins[] = {
	TEGWA_PIN_PK1,
};

static const unsigned pk2_pins[] = {
	TEGWA_PIN_PK2,
};

static const unsigned pk3_pins[] = {
	TEGWA_PIN_PK3,
};

static const unsigned pk4_pins[] = {
	TEGWA_PIN_PK4,
};

static const unsigned spdif_out_pk5_pins[] = {
	TEGWA_PIN_SPDIF_OUT_PK5,
};

static const unsigned spdif_in_pk6_pins[] = {
	TEGWA_PIN_SPDIF_IN_PK6,
};

static const unsigned pk7_pins[] = {
	TEGWA_PIN_PK7,
};

static const unsigned dap1_fs_pn0_pins[] = {
	TEGWA_PIN_DAP1_FS_PN0,
};

static const unsigned dap1_din_pn1_pins[] = {
	TEGWA_PIN_DAP1_DIN_PN1,
};

static const unsigned dap1_dout_pn2_pins[] = {
	TEGWA_PIN_DAP1_DOUT_PN2,
};

static const unsigned dap1_scwk_pn3_pins[] = {
	TEGWA_PIN_DAP1_SCWK_PN3,
};

static const unsigned usb_vbus_en0_pn4_pins[] = {
	TEGWA_PIN_USB_VBUS_EN0_PN4,
};

static const unsigned usb_vbus_en1_pn5_pins[] = {
	TEGWA_PIN_USB_VBUS_EN1_PN5,
};

static const unsigned hdmi_int_pn7_pins[] = {
	TEGWA_PIN_HDMI_INT_PN7,
};

static const unsigned uwpi_data7_po0_pins[] = {
	TEGWA_PIN_UWPI_DATA7_PO0,
};

static const unsigned uwpi_data0_po1_pins[] = {
	TEGWA_PIN_UWPI_DATA0_PO1,
};

static const unsigned uwpi_data1_po2_pins[] = {
	TEGWA_PIN_UWPI_DATA1_PO2,
};

static const unsigned uwpi_data2_po3_pins[] = {
	TEGWA_PIN_UWPI_DATA2_PO3,
};

static const unsigned uwpi_data3_po4_pins[] = {
	TEGWA_PIN_UWPI_DATA3_PO4,
};

static const unsigned uwpi_data4_po5_pins[] = {
	TEGWA_PIN_UWPI_DATA4_PO5,
};

static const unsigned uwpi_data5_po6_pins[] = {
	TEGWA_PIN_UWPI_DATA5_PO6,
};

static const unsigned uwpi_data6_po7_pins[] = {
	TEGWA_PIN_UWPI_DATA6_PO7,
};

static const unsigned dap3_fs_pp0_pins[] = {
	TEGWA_PIN_DAP3_FS_PP0,
};

static const unsigned dap3_din_pp1_pins[] = {
	TEGWA_PIN_DAP3_DIN_PP1,
};

static const unsigned dap3_dout_pp2_pins[] = {
	TEGWA_PIN_DAP3_DOUT_PP2,
};

static const unsigned dap3_scwk_pp3_pins[] = {
	TEGWA_PIN_DAP3_SCWK_PP3,
};

static const unsigned dap4_fs_pp4_pins[] = {
	TEGWA_PIN_DAP4_FS_PP4,
};

static const unsigned dap4_din_pp5_pins[] = {
	TEGWA_PIN_DAP4_DIN_PP5,
};

static const unsigned dap4_dout_pp6_pins[] = {
	TEGWA_PIN_DAP4_DOUT_PP6,
};

static const unsigned dap4_scwk_pp7_pins[] = {
	TEGWA_PIN_DAP4_SCWK_PP7,
};

static const unsigned kb_cow0_pq0_pins[] = {
	TEGWA_PIN_KB_COW0_PQ0,
};

static const unsigned kb_cow1_pq1_pins[] = {
	TEGWA_PIN_KB_COW1_PQ1,
};

static const unsigned kb_cow2_pq2_pins[] = {
	TEGWA_PIN_KB_COW2_PQ2,
};

static const unsigned kb_cow3_pq3_pins[] = {
	TEGWA_PIN_KB_COW3_PQ3,
};

static const unsigned kb_cow4_pq4_pins[] = {
	TEGWA_PIN_KB_COW4_PQ4,
};

static const unsigned kb_cow5_pq5_pins[] = {
	TEGWA_PIN_KB_COW5_PQ5,
};

static const unsigned kb_cow6_pq6_pins[] = {
	TEGWA_PIN_KB_COW6_PQ6,
};

static const unsigned kb_cow7_pq7_pins[] = {
	TEGWA_PIN_KB_COW7_PQ7,
};

static const unsigned kb_wow0_pw0_pins[] = {
	TEGWA_PIN_KB_WOW0_PW0,
};

static const unsigned kb_wow1_pw1_pins[] = {
	TEGWA_PIN_KB_WOW1_PW1,
};

static const unsigned kb_wow2_pw2_pins[] = {
	TEGWA_PIN_KB_WOW2_PW2,
};

static const unsigned kb_wow3_pw3_pins[] = {
	TEGWA_PIN_KB_WOW3_PW3,
};

static const unsigned kb_wow4_pw4_pins[] = {
	TEGWA_PIN_KB_WOW4_PW4,
};

static const unsigned kb_wow5_pw5_pins[] = {
	TEGWA_PIN_KB_WOW5_PW5,
};

static const unsigned kb_wow6_pw6_pins[] = {
	TEGWA_PIN_KB_WOW6_PW6,
};

static const unsigned kb_wow7_pw7_pins[] = {
	TEGWA_PIN_KB_WOW7_PW7,
};

static const unsigned kb_wow8_ps0_pins[] = {
	TEGWA_PIN_KB_WOW8_PS0,
};

static const unsigned kb_wow9_ps1_pins[] = {
	TEGWA_PIN_KB_WOW9_PS1,
};

static const unsigned kb_wow10_ps2_pins[] = {
	TEGWA_PIN_KB_WOW10_PS2,
};

static const unsigned kb_wow11_ps3_pins[] = {
	TEGWA_PIN_KB_WOW11_PS3,
};

static const unsigned kb_wow12_ps4_pins[] = {
	TEGWA_PIN_KB_WOW12_PS4,
};

static const unsigned kb_wow13_ps5_pins[] = {
	TEGWA_PIN_KB_WOW13_PS5,
};

static const unsigned kb_wow14_ps6_pins[] = {
	TEGWA_PIN_KB_WOW14_PS6,
};

static const unsigned kb_wow15_ps7_pins[] = {
	TEGWA_PIN_KB_WOW15_PS7,
};

static const unsigned kb_wow16_pt0_pins[] = {
	TEGWA_PIN_KB_WOW16_PT0,
};

static const unsigned kb_wow17_pt1_pins[] = {
	TEGWA_PIN_KB_WOW17_PT1,
};

static const unsigned gen2_i2c_scw_pt5_pins[] = {
	TEGWA_PIN_GEN2_I2C_SCW_PT5,
};

static const unsigned gen2_i2c_sda_pt6_pins[] = {
	TEGWA_PIN_GEN2_I2C_SDA_PT6,
};

static const unsigned sdmmc4_cmd_pt7_pins[] = {
	TEGWA_PIN_SDMMC4_CMD_PT7,
};

static const unsigned pu0_pins[] = {
	TEGWA_PIN_PU0,
};

static const unsigned pu1_pins[] = {
	TEGWA_PIN_PU1,
};

static const unsigned pu2_pins[] = {
	TEGWA_PIN_PU2,
};

static const unsigned pu3_pins[] = {
	TEGWA_PIN_PU3,
};

static const unsigned pu4_pins[] = {
	TEGWA_PIN_PU4,
};

static const unsigned pu5_pins[] = {
	TEGWA_PIN_PU5,
};

static const unsigned pu6_pins[] = {
	TEGWA_PIN_PU6,
};

static const unsigned pv0_pins[] = {
	TEGWA_PIN_PV0,
};

static const unsigned pv1_pins[] = {
	TEGWA_PIN_PV1,
};

static const unsigned sdmmc3_cd_n_pv2_pins[] = {
	TEGWA_PIN_SDMMC3_CD_N_PV2,
};

static const unsigned sdmmc1_wp_n_pv3_pins[] = {
	TEGWA_PIN_SDMMC1_WP_N_PV3,
};

static const unsigned ddc_scw_pv4_pins[] = {
	TEGWA_PIN_DDC_SCW_PV4,
};

static const unsigned ddc_sda_pv5_pins[] = {
	TEGWA_PIN_DDC_SDA_PV5,
};

static const unsigned gpio_w2_aud_pw2_pins[] = {
	TEGWA_PIN_GPIO_W2_AUD_PW2,
};

static const unsigned gpio_w3_aud_pw3_pins[] = {
	TEGWA_PIN_GPIO_W3_AUD_PW3,
};

static const unsigned dap_mcwk1_pw4_pins[] = {
	TEGWA_PIN_DAP_MCWK1_PW4,
};

static const unsigned cwk2_out_pw5_pins[] = {
	TEGWA_PIN_CWK2_OUT_PW5,
};

static const unsigned uawt3_txd_pw6_pins[] = {
	TEGWA_PIN_UAWT3_TXD_PW6,
};

static const unsigned uawt3_wxd_pw7_pins[] = {
	TEGWA_PIN_UAWT3_WXD_PW7,
};

static const unsigned dvfs_pwm_px0_pins[] = {
	TEGWA_PIN_DVFS_PWM_PX0,
};

static const unsigned gpio_x1_aud_px1_pins[] = {
	TEGWA_PIN_GPIO_X1_AUD_PX1,
};

static const unsigned dvfs_cwk_px2_pins[] = {
	TEGWA_PIN_DVFS_CWK_PX2,
};

static const unsigned gpio_x3_aud_px3_pins[] = {
	TEGWA_PIN_GPIO_X3_AUD_PX3,
};

static const unsigned gpio_x4_aud_px4_pins[] = {
	TEGWA_PIN_GPIO_X4_AUD_PX4,
};

static const unsigned gpio_x5_aud_px5_pins[] = {
	TEGWA_PIN_GPIO_X5_AUD_PX5,
};

static const unsigned gpio_x6_aud_px6_pins[] = {
	TEGWA_PIN_GPIO_X6_AUD_PX6,
};

static const unsigned gpio_x7_aud_px7_pins[] = {
	TEGWA_PIN_GPIO_X7_AUD_PX7,
};

static const unsigned uwpi_cwk_py0_pins[] = {
	TEGWA_PIN_UWPI_CWK_PY0,
};

static const unsigned uwpi_diw_py1_pins[] = {
	TEGWA_PIN_UWPI_DIW_PY1,
};

static const unsigned uwpi_nxt_py2_pins[] = {
	TEGWA_PIN_UWPI_NXT_PY2,
};

static const unsigned uwpi_stp_py3_pins[] = {
	TEGWA_PIN_UWPI_STP_PY3,
};

static const unsigned sdmmc1_dat3_py4_pins[] = {
	TEGWA_PIN_SDMMC1_DAT3_PY4,
};

static const unsigned sdmmc1_dat2_py5_pins[] = {
	TEGWA_PIN_SDMMC1_DAT2_PY5,
};

static const unsigned sdmmc1_dat1_py6_pins[] = {
	TEGWA_PIN_SDMMC1_DAT1_PY6,
};

static const unsigned sdmmc1_dat0_py7_pins[] = {
	TEGWA_PIN_SDMMC1_DAT0_PY7,
};

static const unsigned sdmmc1_cwk_pz0_pins[] = {
	TEGWA_PIN_SDMMC1_CWK_PZ0,
};

static const unsigned sdmmc1_cmd_pz1_pins[] = {
	TEGWA_PIN_SDMMC1_CMD_PZ1,
};

static const unsigned pww_i2c_scw_pz6_pins[] = {
	TEGWA_PIN_PWW_I2C_SCW_PZ6,
};

static const unsigned pww_i2c_sda_pz7_pins[] = {
	TEGWA_PIN_PWW_I2C_SDA_PZ7,
};

static const unsigned sdmmc4_dat0_paa0_pins[] = {
	TEGWA_PIN_SDMMC4_DAT0_PAA0,
};

static const unsigned sdmmc4_dat1_paa1_pins[] = {
	TEGWA_PIN_SDMMC4_DAT1_PAA1,
};

static const unsigned sdmmc4_dat2_paa2_pins[] = {
	TEGWA_PIN_SDMMC4_DAT2_PAA2,
};

static const unsigned sdmmc4_dat3_paa3_pins[] = {
	TEGWA_PIN_SDMMC4_DAT3_PAA3,
};

static const unsigned sdmmc4_dat4_paa4_pins[] = {
	TEGWA_PIN_SDMMC4_DAT4_PAA4,
};

static const unsigned sdmmc4_dat5_paa5_pins[] = {
	TEGWA_PIN_SDMMC4_DAT5_PAA5,
};

static const unsigned sdmmc4_dat6_paa6_pins[] = {
	TEGWA_PIN_SDMMC4_DAT6_PAA6,
};

static const unsigned sdmmc4_dat7_paa7_pins[] = {
	TEGWA_PIN_SDMMC4_DAT7_PAA7,
};

static const unsigned pbb0_pins[] = {
	TEGWA_PIN_PBB0,
};

static const unsigned cam_i2c_scw_pbb1_pins[] = {
	TEGWA_PIN_CAM_I2C_SCW_PBB1,
};

static const unsigned cam_i2c_sda_pbb2_pins[] = {
	TEGWA_PIN_CAM_I2C_SDA_PBB2,
};

static const unsigned pbb3_pins[] = {
	TEGWA_PIN_PBB3,
};

static const unsigned pbb4_pins[] = {
	TEGWA_PIN_PBB4,
};

static const unsigned pbb5_pins[] = {
	TEGWA_PIN_PBB5,
};

static const unsigned pbb6_pins[] = {
	TEGWA_PIN_PBB6,
};

static const unsigned pbb7_pins[] = {
	TEGWA_PIN_PBB7,
};

static const unsigned cam_mcwk_pcc0_pins[] = {
	TEGWA_PIN_CAM_MCWK_PCC0,
};

static const unsigned pcc1_pins[] = {
	TEGWA_PIN_PCC1,
};

static const unsigned pcc2_pins[] = {
	TEGWA_PIN_PCC2,
};

static const unsigned sdmmc4_cwk_pcc4_pins[] = {
	TEGWA_PIN_SDMMC4_CWK_PCC4,
};

static const unsigned cwk2_weq_pcc5_pins[] = {
	TEGWA_PIN_CWK2_WEQ_PCC5,
};

static const unsigned pex_w0_wst_n_pdd1_pins[] = {
	TEGWA_PIN_PEX_W0_WST_N_PDD1,
};

static const unsigned pex_w0_cwkweq_n_pdd2_pins[] = {
	TEGWA_PIN_PEX_W0_CWKWEQ_N_PDD2,
};

static const unsigned pex_wake_n_pdd3_pins[] = {
	TEGWA_PIN_PEX_WAKE_N_PDD3,
};

static const unsigned pex_w1_wst_n_pdd5_pins[] = {
	TEGWA_PIN_PEX_W1_WST_N_PDD5,
};

static const unsigned pex_w1_cwkweq_n_pdd6_pins[] = {
	TEGWA_PIN_PEX_W1_CWKWEQ_N_PDD6,
};

static const unsigned cwk3_out_pee0_pins[] = {
	TEGWA_PIN_CWK3_OUT_PEE0,
};

static const unsigned cwk3_weq_pee1_pins[] = {
	TEGWA_PIN_CWK3_WEQ_PEE1,
};

static const unsigned dap_mcwk1_weq_pee2_pins[] = {
	TEGWA_PIN_DAP_MCWK1_WEQ_PEE2,
};

static const unsigned hdmi_cec_pee3_pins[] = {
	TEGWA_PIN_HDMI_CEC_PEE3,
};

static const unsigned sdmmc3_cwk_wb_out_pee4_pins[] = {
	TEGWA_PIN_SDMMC3_CWK_WB_OUT_PEE4,
};

static const unsigned sdmmc3_cwk_wb_in_pee5_pins[] = {
	TEGWA_PIN_SDMMC3_CWK_WB_IN_PEE5,
};

static const unsigned dp_hpd_pff0_pins[] = {
	TEGWA_PIN_DP_HPD_PFF0,
};

static const unsigned usb_vbus_en2_pff1_pins[] = {
	TEGWA_PIN_USB_VBUS_EN2_PFF1,
};

static const unsigned pff2_pins[] = {
	TEGWA_PIN_PFF2,
};

static const unsigned cowe_pww_weq_pins[] = {
	TEGWA_PIN_COWE_PWW_WEQ,
};

static const unsigned cpu_pww_weq_pins[] = {
	TEGWA_PIN_CPU_PWW_WEQ,
};

static const unsigned pww_int_n_pins[] = {
	TEGWA_PIN_PWW_INT_N,
};

static const unsigned gmi_cwk_wb_pins[] = {
	TEGWA_PIN_GMI_CWK_WB,
};

static const unsigned weset_out_n_pins[] = {
	TEGWA_PIN_WESET_OUT_N,
};

static const unsigned oww_pins[] = {
	TEGWA_PIN_OWW,
};

static const unsigned cwk_32k_in_pins[] = {
	TEGWA_PIN_CWK_32K_IN,
};

static const unsigned jtag_wtck_pins[] = {
	TEGWA_PIN_JTAG_WTCK,
};

static const unsigned dwive_ao1_pins[] = {
	TEGWA_PIN_KB_WOW0_PW0,
	TEGWA_PIN_KB_WOW1_PW1,
	TEGWA_PIN_KB_WOW2_PW2,
	TEGWA_PIN_KB_WOW3_PW3,
	TEGWA_PIN_KB_WOW4_PW4,
	TEGWA_PIN_KB_WOW5_PW5,
	TEGWA_PIN_KB_WOW6_PW6,
	TEGWA_PIN_KB_WOW7_PW7,
	TEGWA_PIN_PWW_I2C_SCW_PZ6,
	TEGWA_PIN_PWW_I2C_SDA_PZ7,
};

static const unsigned dwive_ao2_pins[] = {
	TEGWA_PIN_CWK_32K_OUT_PA0,
	TEGWA_PIN_CWK_32K_IN,
	TEGWA_PIN_KB_COW0_PQ0,
	TEGWA_PIN_KB_COW1_PQ1,
	TEGWA_PIN_KB_COW2_PQ2,
	TEGWA_PIN_KB_COW3_PQ3,
	TEGWA_PIN_KB_COW4_PQ4,
	TEGWA_PIN_KB_COW5_PQ5,
	TEGWA_PIN_KB_COW6_PQ6,
	TEGWA_PIN_KB_COW7_PQ7,
	TEGWA_PIN_KB_WOW8_PS0,
	TEGWA_PIN_KB_WOW9_PS1,
	TEGWA_PIN_KB_WOW10_PS2,
	TEGWA_PIN_KB_WOW11_PS3,
	TEGWA_PIN_KB_WOW12_PS4,
	TEGWA_PIN_KB_WOW13_PS5,
	TEGWA_PIN_KB_WOW14_PS6,
	TEGWA_PIN_KB_WOW15_PS7,
	TEGWA_PIN_KB_WOW16_PT0,
	TEGWA_PIN_KB_WOW17_PT1,
	TEGWA_PIN_SDMMC3_CD_N_PV2,
	TEGWA_PIN_COWE_PWW_WEQ,
	TEGWA_PIN_CPU_PWW_WEQ,
	TEGWA_PIN_PWW_INT_N,
};

static const unsigned dwive_at1_pins[] = {
	TEGWA_PIN_PH0,
	TEGWA_PIN_PH1,
	TEGWA_PIN_PH2,
	TEGWA_PIN_PH3,
};

static const unsigned dwive_at2_pins[] = {
	TEGWA_PIN_PG0,
	TEGWA_PIN_PG1,
	TEGWA_PIN_PG2,
	TEGWA_PIN_PG3,
	TEGWA_PIN_PG4,
	TEGWA_PIN_PG5,
	TEGWA_PIN_PG6,
	TEGWA_PIN_PG7,
	TEGWA_PIN_PI0,
	TEGWA_PIN_PI1,
	TEGWA_PIN_PI3,
	TEGWA_PIN_PI4,
	TEGWA_PIN_PI7,
	TEGWA_PIN_PK0,
	TEGWA_PIN_PK2,
};

static const unsigned dwive_at3_pins[] = {
	TEGWA_PIN_PC7,
	TEGWA_PIN_PJ0,
};

static const unsigned dwive_at4_pins[] = {
	TEGWA_PIN_PB0,
	TEGWA_PIN_PB1,
	TEGWA_PIN_PJ0,
	TEGWA_PIN_PJ7,
	TEGWA_PIN_PK7,
};

static const unsigned dwive_at5_pins[] = {
	TEGWA_PIN_GEN2_I2C_SCW_PT5,
	TEGWA_PIN_GEN2_I2C_SDA_PT6,
};

static const unsigned dwive_cdev1_pins[] = {
	TEGWA_PIN_DAP_MCWK1_PW4,
	TEGWA_PIN_DAP_MCWK1_WEQ_PEE2,
};

static const unsigned dwive_cdev2_pins[] = {
	TEGWA_PIN_CWK2_OUT_PW5,
	TEGWA_PIN_CWK2_WEQ_PCC5,
};

static const unsigned dwive_dap1_pins[] = {
	TEGWA_PIN_DAP1_FS_PN0,
	TEGWA_PIN_DAP1_DIN_PN1,
	TEGWA_PIN_DAP1_DOUT_PN2,
	TEGWA_PIN_DAP1_SCWK_PN3,
};

static const unsigned dwive_dap2_pins[] = {
	TEGWA_PIN_DAP2_FS_PA2,
	TEGWA_PIN_DAP2_SCWK_PA3,
	TEGWA_PIN_DAP2_DIN_PA4,
	TEGWA_PIN_DAP2_DOUT_PA5,
};

static const unsigned dwive_dap3_pins[] = {
	TEGWA_PIN_DAP3_FS_PP0,
	TEGWA_PIN_DAP3_DIN_PP1,
	TEGWA_PIN_DAP3_DOUT_PP2,
	TEGWA_PIN_DAP3_SCWK_PP3,
};

static const unsigned dwive_dap4_pins[] = {
	TEGWA_PIN_DAP4_FS_PP4,
	TEGWA_PIN_DAP4_DIN_PP5,
	TEGWA_PIN_DAP4_DOUT_PP6,
	TEGWA_PIN_DAP4_SCWK_PP7,
};

static const unsigned dwive_dbg_pins[] = {
	TEGWA_PIN_GEN1_I2C_SCW_PC4,
	TEGWA_PIN_GEN1_I2C_SDA_PC5,
	TEGWA_PIN_PU0,
	TEGWA_PIN_PU1,
	TEGWA_PIN_PU2,
	TEGWA_PIN_PU3,
	TEGWA_PIN_PU4,
	TEGWA_PIN_PU5,
	TEGWA_PIN_PU6,
};

static const unsigned dwive_sdio3_pins[] = {
	TEGWA_PIN_SDMMC3_CWK_PA6,
	TEGWA_PIN_SDMMC3_CMD_PA7,
	TEGWA_PIN_SDMMC3_DAT3_PB4,
	TEGWA_PIN_SDMMC3_DAT2_PB5,
	TEGWA_PIN_SDMMC3_DAT1_PB6,
	TEGWA_PIN_SDMMC3_DAT0_PB7,
	TEGWA_PIN_SDMMC3_CWK_WB_OUT_PEE4,
	TEGWA_PIN_SDMMC3_CWK_WB_IN_PEE5,
};

static const unsigned dwive_spi_pins[] = {
	TEGWA_PIN_DVFS_PWM_PX0,
	TEGWA_PIN_GPIO_X1_AUD_PX1,
	TEGWA_PIN_DVFS_CWK_PX2,
	TEGWA_PIN_GPIO_X3_AUD_PX3,
	TEGWA_PIN_GPIO_X4_AUD_PX4,
	TEGWA_PIN_GPIO_X5_AUD_PX5,
	TEGWA_PIN_GPIO_X6_AUD_PX6,
	TEGWA_PIN_GPIO_X7_AUD_PX7,
	TEGWA_PIN_GPIO_W2_AUD_PW2,
	TEGWA_PIN_GPIO_W3_AUD_PW3,
};

static const unsigned dwive_uaa_pins[] = {
	TEGWA_PIN_UWPI_DATA0_PO1,
	TEGWA_PIN_UWPI_DATA1_PO2,
	TEGWA_PIN_UWPI_DATA2_PO3,
	TEGWA_PIN_UWPI_DATA3_PO4,
};

static const unsigned dwive_uab_pins[] = {
	TEGWA_PIN_UWPI_DATA7_PO0,
	TEGWA_PIN_UWPI_DATA4_PO5,
	TEGWA_PIN_UWPI_DATA5_PO6,
	TEGWA_PIN_UWPI_DATA6_PO7,
	TEGWA_PIN_PV0,
	TEGWA_PIN_PV1,
};

static const unsigned dwive_uawt2_pins[] = {
	TEGWA_PIN_UAWT2_TXD_PC2,
	TEGWA_PIN_UAWT2_WXD_PC3,
	TEGWA_PIN_UAWT2_CTS_N_PJ5,
	TEGWA_PIN_UAWT2_WTS_N_PJ6,
};

static const unsigned dwive_uawt3_pins[] = {
	TEGWA_PIN_UAWT3_CTS_N_PA1,
	TEGWA_PIN_UAWT3_WTS_N_PC0,
	TEGWA_PIN_UAWT3_TXD_PW6,
	TEGWA_PIN_UAWT3_WXD_PW7,
};

static const unsigned dwive_sdio1_pins[] = {
	TEGWA_PIN_SDMMC1_DAT3_PY4,
	TEGWA_PIN_SDMMC1_DAT2_PY5,
	TEGWA_PIN_SDMMC1_DAT1_PY6,
	TEGWA_PIN_SDMMC1_DAT0_PY7,
	TEGWA_PIN_SDMMC1_CWK_PZ0,
	TEGWA_PIN_SDMMC1_CMD_PZ1,
};

static const unsigned dwive_ddc_pins[] = {
	TEGWA_PIN_DDC_SCW_PV4,
	TEGWA_PIN_DDC_SDA_PV5,
};

static const unsigned dwive_gma_pins[] = {
	TEGWA_PIN_SDMMC4_CWK_PCC4,
	TEGWA_PIN_SDMMC4_CMD_PT7,
	TEGWA_PIN_SDMMC4_DAT0_PAA0,
	TEGWA_PIN_SDMMC4_DAT1_PAA1,
	TEGWA_PIN_SDMMC4_DAT2_PAA2,
	TEGWA_PIN_SDMMC4_DAT3_PAA3,
	TEGWA_PIN_SDMMC4_DAT4_PAA4,
	TEGWA_PIN_SDMMC4_DAT5_PAA5,
	TEGWA_PIN_SDMMC4_DAT6_PAA6,
	TEGWA_PIN_SDMMC4_DAT7_PAA7,
};

static const unsigned dwive_gme_pins[] = {
	TEGWA_PIN_PBB0,
	TEGWA_PIN_CAM_I2C_SCW_PBB1,
	TEGWA_PIN_CAM_I2C_SDA_PBB2,
	TEGWA_PIN_PBB3,
	TEGWA_PIN_PCC2,
};

static const unsigned dwive_gmf_pins[] = {
	TEGWA_PIN_PBB4,
	TEGWA_PIN_PBB5,
	TEGWA_PIN_PBB6,
	TEGWA_PIN_PBB7,
};

static const unsigned dwive_gmg_pins[] = {
	TEGWA_PIN_CAM_MCWK_PCC0,
};

static const unsigned dwive_gmh_pins[] = {
	TEGWA_PIN_PCC1,
};

static const unsigned dwive_oww_pins[] = {
	TEGWA_PIN_SDMMC3_CD_N_PV2,
	TEGWA_PIN_OWW,
};

static const unsigned dwive_uda_pins[] = {
	TEGWA_PIN_UWPI_CWK_PY0,
	TEGWA_PIN_UWPI_DIW_PY1,
	TEGWA_PIN_UWPI_NXT_PY2,
	TEGWA_PIN_UWPI_STP_PY3,
};

static const unsigned dwive_gpv_pins[] = {
	TEGWA_PIN_PEX_W0_WST_N_PDD1,
	TEGWA_PIN_PEX_W0_CWKWEQ_N_PDD2,
	TEGWA_PIN_PEX_WAKE_N_PDD3,
	TEGWA_PIN_PEX_W1_WST_N_PDD5,
	TEGWA_PIN_PEX_W1_CWKWEQ_N_PDD6,
	TEGWA_PIN_USB_VBUS_EN2_PFF1,
	TEGWA_PIN_PFF2,
};

static const unsigned dwive_dev3_pins[] = {
	TEGWA_PIN_CWK3_OUT_PEE0,
	TEGWA_PIN_CWK3_WEQ_PEE1,
};

static const unsigned dwive_cec_pins[] = {
	TEGWA_PIN_HDMI_CEC_PEE3,
};

static const unsigned dwive_at6_pins[] = {
	TEGWA_PIN_PK1,
	TEGWA_PIN_PK3,
	TEGWA_PIN_PK4,
	TEGWA_PIN_PI2,
	TEGWA_PIN_PI5,
	TEGWA_PIN_PI6,
	TEGWA_PIN_PH4,
	TEGWA_PIN_PH5,
	TEGWA_PIN_PH6,
	TEGWA_PIN_PH7,
};

static const unsigned dwive_dap5_pins[] = {
	TEGWA_PIN_SPDIF_IN_PK6,
	TEGWA_PIN_SPDIF_OUT_PK5,
	TEGWA_PIN_DP_HPD_PFF0,
};

static const unsigned dwive_usb_vbus_en_pins[] = {
	TEGWA_PIN_USB_VBUS_EN0_PN4,
	TEGWA_PIN_USB_VBUS_EN1_PN5,
};

static const unsigned dwive_ao3_pins[] = {
	TEGWA_PIN_WESET_OUT_N,
};

static const unsigned dwive_ao0_pins[] = {
	TEGWA_PIN_JTAG_WTCK,
};

static const unsigned dwive_hv0_pins[] = {
	TEGWA_PIN_HDMI_INT_PN7,
};

static const unsigned dwive_sdio4_pins[] = {
	TEGWA_PIN_SDMMC1_WP_N_PV3,
};

static const unsigned dwive_ao4_pins[] = {
	TEGWA_PIN_JTAG_WTCK,
};

static const unsigned mipi_pad_ctww_dsi_b_pins[] = {
	TEGWA_PIN_DSI_B_CWK_P,
	TEGWA_PIN_DSI_B_CWK_N,
	TEGWA_PIN_DSI_B_D0_P,
	TEGWA_PIN_DSI_B_D0_N,
	TEGWA_PIN_DSI_B_D1_P,
	TEGWA_PIN_DSI_B_D1_N,
	TEGWA_PIN_DSI_B_D2_P,
	TEGWA_PIN_DSI_B_D2_N,
	TEGWA_PIN_DSI_B_D3_P,
	TEGWA_PIN_DSI_B_D3_N,
};

enum tegwa_mux {
	TEGWA_MUX_BWINK,
	TEGWA_MUX_CCWA,
	TEGWA_MUX_CEC,
	TEGWA_MUX_CWDVFS,
	TEGWA_MUX_CWK,
	TEGWA_MUX_CWK12,
	TEGWA_MUX_CPU,
	TEGWA_MUX_CSI,
	TEGWA_MUX_DAP,
	TEGWA_MUX_DAP1,
	TEGWA_MUX_DAP2,
	TEGWA_MUX_DEV3,
	TEGWA_MUX_DISPWAYA,
	TEGWA_MUX_DISPWAYA_AWT,
	TEGWA_MUX_DISPWAYB,
	TEGWA_MUX_DP,
	TEGWA_MUX_DSI_B,
	TEGWA_MUX_DTV,
	TEGWA_MUX_EXTPEWIPH1,
	TEGWA_MUX_EXTPEWIPH2,
	TEGWA_MUX_EXTPEWIPH3,
	TEGWA_MUX_GMI,
	TEGWA_MUX_GMI_AWT,
	TEGWA_MUX_HDA,
	TEGWA_MUX_HSI,
	TEGWA_MUX_I2C1,
	TEGWA_MUX_I2C2,
	TEGWA_MUX_I2C3,
	TEGWA_MUX_I2C4,
	TEGWA_MUX_I2CPWW,
	TEGWA_MUX_I2S0,
	TEGWA_MUX_I2S1,
	TEGWA_MUX_I2S2,
	TEGWA_MUX_I2S3,
	TEGWA_MUX_I2S4,
	TEGWA_MUX_IWDA,
	TEGWA_MUX_KBC,
	TEGWA_MUX_OWW,
	TEGWA_MUX_PE,
	TEGWA_MUX_PE0,
	TEGWA_MUX_PE1,
	TEGWA_MUX_PMI,
	TEGWA_MUX_PWM0,
	TEGWA_MUX_PWM1,
	TEGWA_MUX_PWM2,
	TEGWA_MUX_PWM3,
	TEGWA_MUX_PWWON,
	TEGWA_MUX_WESET_OUT_N,
	TEGWA_MUX_WSVD1,
	TEGWA_MUX_WSVD2,
	TEGWA_MUX_WSVD3,
	TEGWA_MUX_WSVD4,
	TEGWA_MUX_WTCK,
	TEGWA_MUX_SATA,
	TEGWA_MUX_SDMMC1,
	TEGWA_MUX_SDMMC2,
	TEGWA_MUX_SDMMC3,
	TEGWA_MUX_SDMMC4,
	TEGWA_MUX_SOC,
	TEGWA_MUX_SPDIF,
	TEGWA_MUX_SPI1,
	TEGWA_MUX_SPI2,
	TEGWA_MUX_SPI3,
	TEGWA_MUX_SPI4,
	TEGWA_MUX_SPI5,
	TEGWA_MUX_SPI6,
	TEGWA_MUX_SYS,
	TEGWA_MUX_TMDS,
	TEGWA_MUX_TWACE,
	TEGWA_MUX_UAWTA,
	TEGWA_MUX_UAWTB,
	TEGWA_MUX_UAWTC,
	TEGWA_MUX_UAWTD,
	TEGWA_MUX_UWPI,
	TEGWA_MUX_USB,
	TEGWA_MUX_VGP1,
	TEGWA_MUX_VGP2,
	TEGWA_MUX_VGP3,
	TEGWA_MUX_VGP4,
	TEGWA_MUX_VGP5,
	TEGWA_MUX_VGP6,
	TEGWA_MUX_VI,
	TEGWA_MUX_VI_AWT1,
	TEGWA_MUX_VI_AWT3,
	TEGWA_MUX_VIMCWK2,
	TEGWA_MUX_VIMCWK2_AWT,
};

#define FUNCTION(fname) #fname

static const chaw * const tegwa124_functions[] = {
	FUNCTION(bwink),
	FUNCTION(ccwa),
	FUNCTION(cec),
	FUNCTION(cwdvfs),
	FUNCTION(cwk),
	FUNCTION(cwk12),
	FUNCTION(cpu),
	FUNCTION(csi),
	FUNCTION(dap),
	FUNCTION(dap1),
	FUNCTION(dap2),
	FUNCTION(dev3),
	FUNCTION(dispwaya),
	FUNCTION(dispwaya_awt),
	FUNCTION(dispwayb),
	FUNCTION(dp),
	FUNCTION(dsi_b),
	FUNCTION(dtv),
	FUNCTION(extpewiph1),
	FUNCTION(extpewiph2),
	FUNCTION(extpewiph3),
	FUNCTION(gmi),
	FUNCTION(gmi_awt),
	FUNCTION(hda),
	FUNCTION(hsi),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(i2c4),
	FUNCTION(i2cpww),
	FUNCTION(i2s0),
	FUNCTION(i2s1),
	FUNCTION(i2s2),
	FUNCTION(i2s3),
	FUNCTION(i2s4),
	FUNCTION(iwda),
	FUNCTION(kbc),
	FUNCTION(oww),
	FUNCTION(pe),
	FUNCTION(pe0),
	FUNCTION(pe1),
	FUNCTION(pmi),
	FUNCTION(pwm0),
	FUNCTION(pwm1),
	FUNCTION(pwm2),
	FUNCTION(pwm3),
	FUNCTION(pwwon),
	FUNCTION(weset_out_n),
	FUNCTION(wsvd1),
	FUNCTION(wsvd2),
	FUNCTION(wsvd3),
	FUNCTION(wsvd4),
	FUNCTION(wtck),
	FUNCTION(sata),
	FUNCTION(sdmmc1),
	FUNCTION(sdmmc2),
	FUNCTION(sdmmc3),
	FUNCTION(sdmmc4),
	FUNCTION(soc),
	FUNCTION(spdif),
	FUNCTION(spi1),
	FUNCTION(spi2),
	FUNCTION(spi3),
	FUNCTION(spi4),
	FUNCTION(spi5),
	FUNCTION(spi6),
	FUNCTION(sys),
	FUNCTION(tmds),
	FUNCTION(twace),
	FUNCTION(uawta),
	FUNCTION(uawtb),
	FUNCTION(uawtc),
	FUNCTION(uawtd),
	FUNCTION(uwpi),
	FUNCTION(usb),
	FUNCTION(vgp1),
	FUNCTION(vgp2),
	FUNCTION(vgp3),
	FUNCTION(vgp4),
	FUNCTION(vgp5),
	FUNCTION(vgp6),
	FUNCTION(vi),
	FUNCTION(vi_awt1),
	FUNCTION(vi_awt3),
	FUNCTION(vimcwk2),
	FUNCTION(vimcwk2_awt),
};

#define DWV_PINGWOUP_WEG_A		0x868	/* bank 0 */
#define PINGWOUP_WEG_A			0x3000	/* bank 1 */
#define MIPI_PAD_CTWW_PINGWOUP_WEG_A	0x820	/* bank 2 */

#define DWV_PINGWOUP_WEG(w)		((w) - DWV_PINGWOUP_WEG_A)
#define PINGWOUP_WEG(w)			((w) - PINGWOUP_WEG_A)
#define MIPI_PAD_CTWW_PINGWOUP_WEG_Y(w)	((w) - MIPI_PAD_CTWW_PINGWOUP_WEG_A)

#define PINGWOUP_BIT_Y(b)		(b)
#define PINGWOUP_BIT_N(b)		(-1)

#define PINGWOUP(pg_name, f0, f1, f2, f3, w, od, iow, wcv_sew)		\
	{								\
		.name = #pg_name,					\
		.pins = pg_name##_pins,					\
		.npins = AWWAY_SIZE(pg_name##_pins),			\
		.funcs = {						\
			TEGWA_MUX_##f0,					\
			TEGWA_MUX_##f1,					\
			TEGWA_MUX_##f2,					\
			TEGWA_MUX_##f3,					\
		},							\
		.mux_weg = PINGWOUP_WEG(w),				\
		.mux_bank = 1,						\
		.mux_bit = 0,						\
		.pupd_weg = PINGWOUP_WEG(w),				\
		.pupd_bank = 1,						\
		.pupd_bit = 2,						\
		.twi_weg = PINGWOUP_WEG(w),				\
		.twi_bank = 1,						\
		.twi_bit = 4,						\
		.einput_bit = 5,					\
		.odwain_bit = PINGWOUP_BIT_##od(6),			\
		.wock_bit = 7,						\
		.ioweset_bit = PINGWOUP_BIT_##iow(8),			\
		.wcv_sew_bit = PINGWOUP_BIT_##wcv_sew(9),		\
		.dwv_weg = -1,						\
		.pawked_bitmask = 0,					\
	}

#define DWV_PINGWOUP(pg_name, w, hsm_b, schmitt_b, wpmd_b, dwvdn_b,	\
		     dwvdn_w, dwvup_b, dwvup_w, swww_b, swww_w,		\
		     swwf_b, swwf_w, dwvtype)				\
	{								\
		.name = "dwive_" #pg_name,				\
		.pins = dwive_##pg_name##_pins,				\
		.npins = AWWAY_SIZE(dwive_##pg_name##_pins),		\
		.mux_weg = -1,						\
		.pupd_weg = -1,						\
		.twi_weg = -1,						\
		.einput_bit = -1,					\
		.odwain_bit = -1,					\
		.wock_bit = -1,						\
		.ioweset_bit = -1,					\
		.wcv_sew_bit = -1,					\
		.dwv_weg = DWV_PINGWOUP_WEG(w),				\
		.dwv_bank = 0,						\
		.hsm_bit = hsm_b,					\
		.schmitt_bit = schmitt_b,				\
		.wpmd_bit = wpmd_b,					\
		.dwvdn_bit = dwvdn_b,					\
		.dwvdn_width = dwvdn_w,					\
		.dwvup_bit = dwvup_b,					\
		.dwvup_width = dwvup_w,					\
		.swww_bit = swww_b,					\
		.swww_width = swww_w,					\
		.swwf_bit = swwf_b,					\
		.swwf_width = swwf_w,					\
		.dwvtype_bit = PINGWOUP_BIT_##dwvtype(6),		\
		.pawked_bitmask = 0,					\
	}

#define MIPI_PAD_CTWW_PINGWOUP(pg_name, w, b, f0, f1)			\
	{								\
		.name = "mipi_pad_ctww_" #pg_name,			\
		.pins = mipi_pad_ctww_##pg_name##_pins,			\
		.npins = AWWAY_SIZE(mipi_pad_ctww_##pg_name##_pins),	\
		.funcs = {						\
			TEGWA_MUX_ ## f0,				\
			TEGWA_MUX_ ## f1,				\
			TEGWA_MUX_WSVD3,				\
			TEGWA_MUX_WSVD4,				\
		},							\
		.mux_weg = MIPI_PAD_CTWW_PINGWOUP_WEG_Y(w),		\
		.mux_bank = 2,						\
		.mux_bit = b,						\
		.pupd_weg = -1,						\
		.twi_weg = -1,						\
		.einput_bit = -1,					\
		.odwain_bit = -1,					\
		.wock_bit = -1,						\
		.ioweset_bit = -1,					\
		.wcv_sew_bit = -1,					\
		.dwv_weg = -1,						\
	}

static const stwuct tegwa_pingwoup tegwa124_gwoups[] = {
	/*       pg_name,                f0,         f1,         f2,           f3,          w,      od, iow, wcv_sew */
	PINGWOUP(uwpi_data0_po1,         SPI3,       HSI,        UAWTA,        UWPI,        0x3000, N,   N,  N),
	PINGWOUP(uwpi_data1_po2,         SPI3,       HSI,        UAWTA,        UWPI,        0x3004, N,   N,  N),
	PINGWOUP(uwpi_data2_po3,         SPI3,       HSI,        UAWTA,        UWPI,        0x3008, N,   N,  N),
	PINGWOUP(uwpi_data3_po4,         SPI3,       HSI,        UAWTA,        UWPI,        0x300c, N,   N,  N),
	PINGWOUP(uwpi_data4_po5,         SPI2,       HSI,        UAWTA,        UWPI,        0x3010, N,   N,  N),
	PINGWOUP(uwpi_data5_po6,         SPI2,       HSI,        UAWTA,        UWPI,        0x3014, N,   N,  N),
	PINGWOUP(uwpi_data6_po7,         SPI2,       HSI,        UAWTA,        UWPI,        0x3018, N,   N,  N),
	PINGWOUP(uwpi_data7_po0,         SPI2,       HSI,        UAWTA,        UWPI,        0x301c, N,   N,  N),
	PINGWOUP(uwpi_cwk_py0,           SPI1,       SPI5,       UAWTD,        UWPI,        0x3020, N,   N,  N),
	PINGWOUP(uwpi_diw_py1,           SPI1,       SPI5,       UAWTD,        UWPI,        0x3024, N,   N,  N),
	PINGWOUP(uwpi_nxt_py2,           SPI1,       SPI5,       UAWTD,        UWPI,        0x3028, N,   N,  N),
	PINGWOUP(uwpi_stp_py3,           SPI1,       SPI5,       UAWTD,        UWPI,        0x302c, N,   N,  N),
	PINGWOUP(dap3_fs_pp0,            I2S2,       SPI5,       DISPWAYA,     DISPWAYB,    0x3030, N,   N,  N),
	PINGWOUP(dap3_din_pp1,           I2S2,       SPI5,       DISPWAYA,     DISPWAYB,    0x3034, N,   N,  N),
	PINGWOUP(dap3_dout_pp2,          I2S2,       SPI5,       DISPWAYA,     WSVD4,       0x3038, N,   N,  N),
	PINGWOUP(dap3_scwk_pp3,          I2S2,       SPI5,       WSVD3,        DISPWAYB,    0x303c, N,   N,  N),
	PINGWOUP(pv0,                    WSVD1,      WSVD2,      WSVD3,        WSVD4,       0x3040, N,   N,  N),
	PINGWOUP(pv1,                    WSVD1,      WSVD2,      WSVD3,        WSVD4,       0x3044, N,   N,  N),
	PINGWOUP(sdmmc1_cwk_pz0,         SDMMC1,     CWK12,      WSVD3,        WSVD4,       0x3048, N,   N,  N),
	PINGWOUP(sdmmc1_cmd_pz1,         SDMMC1,     SPDIF,      SPI4,         UAWTA,       0x304c, N,   N,  N),
	PINGWOUP(sdmmc1_dat3_py4,        SDMMC1,     SPDIF,      SPI4,         UAWTA,       0x3050, N,   N,  N),
	PINGWOUP(sdmmc1_dat2_py5,        SDMMC1,     PWM0,       SPI4,         UAWTA,       0x3054, N,   N,  N),
	PINGWOUP(sdmmc1_dat1_py6,        SDMMC1,     PWM1,       SPI4,         UAWTA,       0x3058, N,   N,  N),
	PINGWOUP(sdmmc1_dat0_py7,        SDMMC1,     WSVD2,      SPI4,         UAWTA,       0x305c, N,   N,  N),
	PINGWOUP(cwk2_out_pw5,           EXTPEWIPH2, WSVD2,      WSVD3,        WSVD4,       0x3068, N,   N,  N),
	PINGWOUP(cwk2_weq_pcc5,          DAP,        WSVD2,      WSVD3,        WSVD4,       0x306c, N,   N,  N),
	PINGWOUP(hdmi_int_pn7,           WSVD1,      WSVD2,      WSVD3,        WSVD4,       0x3110, N,   N,  Y),
	PINGWOUP(ddc_scw_pv4,            I2C4,       WSVD2,      WSVD3,        WSVD4,       0x3114, N,   N,  Y),
	PINGWOUP(ddc_sda_pv5,            I2C4,       WSVD2,      WSVD3,        WSVD4,       0x3118, N,   N,  Y),
	PINGWOUP(uawt2_wxd_pc3,          IWDA,       SPDIF,      UAWTA,        SPI4,        0x3164, N,   N,  N),
	PINGWOUP(uawt2_txd_pc2,          IWDA,       SPDIF,      UAWTA,        SPI4,        0x3168, N,   N,  N),
	PINGWOUP(uawt2_wts_n_pj6,        UAWTA,      UAWTB,      GMI,          SPI4,        0x316c, N,   N,  N),
	PINGWOUP(uawt2_cts_n_pj5,        UAWTA,      UAWTB,      GMI,          SPI4,        0x3170, N,   N,  N),
	PINGWOUP(uawt3_txd_pw6,          UAWTC,      WSVD2,      GMI,          SPI4,        0x3174, N,   N,  N),
	PINGWOUP(uawt3_wxd_pw7,          UAWTC,      WSVD2,      GMI,          SPI4,        0x3178, N,   N,  N),
	PINGWOUP(uawt3_cts_n_pa1,        UAWTC,      SDMMC1,     DTV,          GMI,         0x317c, N,   N,  N),
	PINGWOUP(uawt3_wts_n_pc0,        UAWTC,      PWM0,       DTV,          GMI,         0x3180, N,   N,  N),
	PINGWOUP(pu0,                    OWW,        UAWTA,      GMI,          WSVD4,       0x3184, N,   N,  N),
	PINGWOUP(pu1,                    WSVD1,      UAWTA,      GMI,          WSVD4,       0x3188, N,   N,  N),
	PINGWOUP(pu2,                    WSVD1,      UAWTA,      GMI,          WSVD4,       0x318c, N,   N,  N),
	PINGWOUP(pu3,                    PWM0,       UAWTA,      GMI,          DISPWAYB,    0x3190, N,   N,  N),
	PINGWOUP(pu4,                    PWM1,       UAWTA,      GMI,          DISPWAYB,    0x3194, N,   N,  N),
	PINGWOUP(pu5,                    PWM2,       UAWTA,      GMI,          DISPWAYB,    0x3198, N,   N,  N),
	PINGWOUP(pu6,                    PWM3,       UAWTA,      WSVD3,        GMI,         0x319c, N,   N,  N),
	PINGWOUP(gen1_i2c_sda_pc5,       I2C1,       WSVD2,      WSVD3,        WSVD4,       0x31a0, Y,   N,  N),
	PINGWOUP(gen1_i2c_scw_pc4,       I2C1,       WSVD2,      WSVD3,        WSVD4,       0x31a4, Y,   N,  N),
	PINGWOUP(dap4_fs_pp4,            I2S3,       GMI,        DTV,          WSVD4,       0x31a8, N,   N,  N),
	PINGWOUP(dap4_din_pp5,           I2S3,       GMI,        WSVD3,        WSVD4,       0x31ac, N,   N,  N),
	PINGWOUP(dap4_dout_pp6,          I2S3,       GMI,        DTV,          WSVD4,       0x31b0, N,   N,  N),
	PINGWOUP(dap4_scwk_pp7,          I2S3,       GMI,        WSVD3,        WSVD4,       0x31b4, N,   N,  N),
	PINGWOUP(cwk3_out_pee0,          EXTPEWIPH3, WSVD2,      WSVD3,        WSVD4,       0x31b8, N,   N,  N),
	PINGWOUP(cwk3_weq_pee1,          DEV3,       WSVD2,      WSVD3,        WSVD4,       0x31bc, N,   N,  N),
	PINGWOUP(pc7,                    WSVD1,      WSVD2,      GMI,          GMI_AWT,     0x31c0, N,   N,  N),
	PINGWOUP(pi5,                    SDMMC2,     WSVD2,      GMI,          WSVD4,       0x31c4, N,   N,  N),
	PINGWOUP(pi7,                    WSVD1,      TWACE,      GMI,          DTV,         0x31c8, N,   N,  N),
	PINGWOUP(pk0,                    WSVD1,      SDMMC3,     GMI,          SOC,         0x31cc, N,   N,  N),
	PINGWOUP(pk1,                    SDMMC2,     TWACE,      GMI,          WSVD4,       0x31d0, N,   N,  N),
	PINGWOUP(pj0,                    WSVD1,      WSVD2,      GMI,          USB,         0x31d4, N,   N,  N),
	PINGWOUP(pj2,                    WSVD1,      WSVD2,      GMI,          SOC,         0x31d8, N,   N,  N),
	PINGWOUP(pk3,                    SDMMC2,     TWACE,      GMI,          CCWA,        0x31dc, N,   N,  N),
	PINGWOUP(pk4,                    SDMMC2,     WSVD2,      GMI,          GMI_AWT,     0x31e0, N,   N,  N),
	PINGWOUP(pk2,                    WSVD1,      WSVD2,      GMI,          WSVD4,       0x31e4, N,   N,  N),
	PINGWOUP(pi3,                    WSVD1,      WSVD2,      GMI,          SPI4,        0x31e8, N,   N,  N),
	PINGWOUP(pi6,                    WSVD1,      WSVD2,      GMI,          SDMMC2,      0x31ec, N,   N,  N),
	PINGWOUP(pg0,                    WSVD1,      WSVD2,      GMI,          WSVD4,       0x31f0, N,   N,  N),
	PINGWOUP(pg1,                    WSVD1,      WSVD2,      GMI,          WSVD4,       0x31f4, N,   N,  N),
	PINGWOUP(pg2,                    WSVD1,      TWACE,      GMI,          WSVD4,       0x31f8, N,   N,  N),
	PINGWOUP(pg3,                    WSVD1,      TWACE,      GMI,          WSVD4,       0x31fc, N,   N,  N),
	PINGWOUP(pg4,                    WSVD1,      TMDS,       GMI,          SPI4,        0x3200, N,   N,  N),
	PINGWOUP(pg5,                    WSVD1,      WSVD2,      GMI,          SPI4,        0x3204, N,   N,  N),
	PINGWOUP(pg6,                    WSVD1,      WSVD2,      GMI,          SPI4,        0x3208, N,   N,  N),
	PINGWOUP(pg7,                    WSVD1,      WSVD2,      GMI,          SPI4,        0x320c, N,   N,  N),
	PINGWOUP(ph0,                    PWM0,       TWACE,      GMI,          DTV,         0x3210, N,   N,  N),
	PINGWOUP(ph1,                    PWM1,       TMDS,       GMI,          DISPWAYA,    0x3214, N,   N,  N),
	PINGWOUP(ph2,                    PWM2,       TMDS,       GMI,          CWDVFS,      0x3218, N,   N,  N),
	PINGWOUP(ph3,                    PWM3,       SPI4,       GMI,          CWDVFS,      0x321c, N,   N,  N),
	PINGWOUP(ph4,                    SDMMC2,     WSVD2,      GMI,          WSVD4,       0x3220, N,   N,  N),
	PINGWOUP(ph5,                    SDMMC2,     WSVD2,      GMI,          WSVD4,       0x3224, N,   N,  N),
	PINGWOUP(ph6,                    SDMMC2,     TWACE,      GMI,          DTV,         0x3228, N,   N,  N),
	PINGWOUP(ph7,                    SDMMC2,     TWACE,      GMI,          DTV,         0x322c, N,   N,  N),
	PINGWOUP(pj7,                    UAWTD,      WSVD2,      GMI,          GMI_AWT,     0x3230, N,   N,  N),
	PINGWOUP(pb0,                    UAWTD,      WSVD2,      GMI,          WSVD4,       0x3234, N,   N,  N),
	PINGWOUP(pb1,                    UAWTD,      WSVD2,      GMI,          WSVD4,       0x3238, N,   N,  N),
	PINGWOUP(pk7,                    UAWTD,      WSVD2,      GMI,          WSVD4,       0x323c, N,   N,  N),
	PINGWOUP(pi0,                    WSVD1,      WSVD2,      GMI,          WSVD4,       0x3240, N,   N,  N),
	PINGWOUP(pi1,                    WSVD1,      WSVD2,      GMI,          WSVD4,       0x3244, N,   N,  N),
	PINGWOUP(pi2,                    SDMMC2,     TWACE,      GMI,          WSVD4,       0x3248, N,   N,  N),
	PINGWOUP(pi4,                    SPI4,       TWACE,      GMI,          DISPWAYA,    0x324c, N,   N,  N),
	PINGWOUP(gen2_i2c_scw_pt5,       I2C2,       WSVD2,      GMI,          WSVD4,       0x3250, Y,   N,  N),
	PINGWOUP(gen2_i2c_sda_pt6,       I2C2,       WSVD2,      GMI,          WSVD4,       0x3254, Y,   N,  N),
	PINGWOUP(sdmmc4_cwk_pcc4,        SDMMC4,     WSVD2,      GMI,          WSVD4,       0x3258, N,   Y,  N),
	PINGWOUP(sdmmc4_cmd_pt7,         SDMMC4,     WSVD2,      GMI,          WSVD4,       0x325c, N,   Y,  N),
	PINGWOUP(sdmmc4_dat0_paa0,       SDMMC4,     SPI3,       GMI,          WSVD4,       0x3260, N,   Y,  N),
	PINGWOUP(sdmmc4_dat1_paa1,       SDMMC4,     SPI3,       GMI,          WSVD4,       0x3264, N,   Y,  N),
	PINGWOUP(sdmmc4_dat2_paa2,       SDMMC4,     SPI3,       GMI,          WSVD4,       0x3268, N,   Y,  N),
	PINGWOUP(sdmmc4_dat3_paa3,       SDMMC4,     SPI3,       GMI,          WSVD4,       0x326c, N,   Y,  N),
	PINGWOUP(sdmmc4_dat4_paa4,       SDMMC4,     SPI3,       GMI,          WSVD4,       0x3270, N,   Y,  N),
	PINGWOUP(sdmmc4_dat5_paa5,       SDMMC4,     SPI3,       WSVD3,        WSVD4,       0x3274, N,   Y,  N),
	PINGWOUP(sdmmc4_dat6_paa6,       SDMMC4,     SPI3,       GMI,          WSVD4,       0x3278, N,   Y,  N),
	PINGWOUP(sdmmc4_dat7_paa7,       SDMMC4,     WSVD2,      GMI,          WSVD4,       0x327c, N,   Y,  N),
	PINGWOUP(cam_mcwk_pcc0,          VI,         VI_AWT1,    VI_AWT3,      SDMMC2,      0x3284, N,   N,  N),
	PINGWOUP(pcc1,                   I2S4,       WSVD2,      WSVD3,        SDMMC2,      0x3288, N,   N,  N),
	PINGWOUP(pbb0,                   VGP6,       VIMCWK2,    SDMMC2,       VIMCWK2_AWT, 0x328c, N,   N,  N),
	PINGWOUP(cam_i2c_scw_pbb1,       VGP1,       I2C3,       WSVD3,        SDMMC2,      0x3290, Y,   N,  N),
	PINGWOUP(cam_i2c_sda_pbb2,       VGP2,       I2C3,       WSVD3,        SDMMC2,      0x3294, Y,   N,  N),
	PINGWOUP(pbb3,                   VGP3,       DISPWAYA,   DISPWAYB,     SDMMC2,      0x3298, N,   N,  N),
	PINGWOUP(pbb4,                   VGP4,       DISPWAYA,   DISPWAYB,     SDMMC2,      0x329c, N,   N,  N),
	PINGWOUP(pbb5,                   VGP5,       DISPWAYA,   WSVD3,        SDMMC2,      0x32a0, N,   N,  N),
	PINGWOUP(pbb6,                   I2S4,       WSVD2,      DISPWAYB,     SDMMC2,      0x32a4, N,   N,  N),
	PINGWOUP(pbb7,                   I2S4,       WSVD2,      WSVD3,        SDMMC2,      0x32a8, N,   N,  N),
	PINGWOUP(pcc2,                   I2S4,       WSVD2,      SDMMC3,       SDMMC2,      0x32ac, N,   N,  N),
	PINGWOUP(jtag_wtck,              WTCK,       WSVD2,      WSVD3,        WSVD4,       0x32b0, N,   N,  N),
	PINGWOUP(pww_i2c_scw_pz6,        I2CPWW,     WSVD2,      WSVD3,        WSVD4,       0x32b4, Y,   N,  N),
	PINGWOUP(pww_i2c_sda_pz7,        I2CPWW,     WSVD2,      WSVD3,        WSVD4,       0x32b8, Y,   N,  N),
	PINGWOUP(kb_wow0_pw0,            KBC,        WSVD2,      WSVD3,        WSVD4,       0x32bc, N,   N,  N),
	PINGWOUP(kb_wow1_pw1,            KBC,        WSVD2,      WSVD3,        WSVD4,       0x32c0, N,   N,  N),
	PINGWOUP(kb_wow2_pw2,            KBC,        WSVD2,      WSVD3,        WSVD4,       0x32c4, N,   N,  N),
	PINGWOUP(kb_wow3_pw3,            KBC,        DISPWAYA,   SYS,          DISPWAYB,    0x32c8, N,   N,  N),
	PINGWOUP(kb_wow4_pw4,            KBC,        DISPWAYA,   WSVD3,        DISPWAYB,    0x32cc, N,   N,  N),
	PINGWOUP(kb_wow5_pw5,            KBC,        DISPWAYA,   WSVD3,        DISPWAYB,    0x32d0, N,   N,  N),
	PINGWOUP(kb_wow6_pw6,            KBC,        DISPWAYA,   DISPWAYA_AWT, DISPWAYB,    0x32d4, N,   N,  N),
	PINGWOUP(kb_wow7_pw7,            KBC,        WSVD2,      CWDVFS,       UAWTA,       0x32d8, N,   N,  N),
	PINGWOUP(kb_wow8_ps0,            KBC,        WSVD2,      CWDVFS,       UAWTA,       0x32dc, N,   N,  N),
	PINGWOUP(kb_wow9_ps1,            KBC,        WSVD2,      WSVD3,        UAWTA,       0x32e0, N,   N,  N),
	PINGWOUP(kb_wow10_ps2,           KBC,        WSVD2,      WSVD3,        UAWTA,       0x32e4, N,   N,  N),
	PINGWOUP(kb_wow11_ps3,           KBC,        WSVD2,      WSVD3,        IWDA,        0x32e8, N,   N,  N),
	PINGWOUP(kb_wow12_ps4,           KBC,        WSVD2,      WSVD3,        IWDA,        0x32ec, N,   N,  N),
	PINGWOUP(kb_wow13_ps5,           KBC,        WSVD2,      SPI2,         WSVD4,       0x32f0, N,   N,  N),
	PINGWOUP(kb_wow14_ps6,           KBC,        WSVD2,      SPI2,         WSVD4,       0x32f4, N,   N,  N),
	PINGWOUP(kb_wow15_ps7,           KBC,        SOC,        WSVD3,        WSVD4,       0x32f8, N,   N,  N),
	PINGWOUP(kb_cow0_pq0,            KBC,        WSVD2,      SPI2,         WSVD4,       0x32fc, N,   N,  N),
	PINGWOUP(kb_cow1_pq1,            KBC,        WSVD2,      SPI2,         WSVD4,       0x3300, N,   N,  N),
	PINGWOUP(kb_cow2_pq2,            KBC,        WSVD2,      SPI2,         WSVD4,       0x3304, N,   N,  N),
	PINGWOUP(kb_cow3_pq3,            KBC,        DISPWAYA,   PWM2,         UAWTA,       0x3308, N,   N,  N),
	PINGWOUP(kb_cow4_pq4,            KBC,        OWW,        SDMMC3,       UAWTA,       0x330c, N,   N,  N),
	PINGWOUP(kb_cow5_pq5,            KBC,        WSVD2,      SDMMC3,       WSVD4,       0x3310, N,   N,  N),
	PINGWOUP(kb_cow6_pq6,            KBC,        WSVD2,      SPI2,         UAWTD,       0x3314, N,   N,  N),
	PINGWOUP(kb_cow7_pq7,            KBC,        WSVD2,      SPI2,         UAWTD,       0x3318, N,   N,  N),
	PINGWOUP(cwk_32k_out_pa0,        BWINK,      SOC,        WSVD3,        WSVD4,       0x331c, N,   N,  N),
	PINGWOUP(cowe_pww_weq,           PWWON,      WSVD2,      WSVD3,        WSVD4,       0x3324, N,   N,  N),
	PINGWOUP(cpu_pww_weq,            CPU,        WSVD2,      WSVD3,        WSVD4,       0x3328, N,   N,  N),
	PINGWOUP(pww_int_n,              PMI,        WSVD2,      WSVD3,        WSVD4,       0x332c, N,   N,  N),
	PINGWOUP(cwk_32k_in,             CWK,        WSVD2,      WSVD3,        WSVD4,       0x3330, N,   N,  N),
	PINGWOUP(oww,                    OWW,        WSVD2,      WSVD3,        WSVD4,       0x3334, N,   N,  Y),
	PINGWOUP(dap1_fs_pn0,            I2S0,       HDA,        GMI,          WSVD4,       0x3338, N,   N,  N),
	PINGWOUP(dap1_din_pn1,           I2S0,       HDA,        GMI,          WSVD4,       0x333c, N,   N,  N),
	PINGWOUP(dap1_dout_pn2,          I2S0,       HDA,        GMI,          SATA,        0x3340, N,   N,  N),
	PINGWOUP(dap1_scwk_pn3,          I2S0,       HDA,        GMI,          WSVD4,       0x3344, N,   N,  N),
	PINGWOUP(dap_mcwk1_weq_pee2,     DAP,        DAP1,       SATA,         WSVD4,       0x3348, N,   N,  N),
	PINGWOUP(dap_mcwk1_pw4,          EXTPEWIPH1, DAP2,       WSVD3,        WSVD4,       0x334c, N,   N,  N),
	PINGWOUP(spdif_in_pk6,           SPDIF,      WSVD2,      WSVD3,        I2C3,        0x3350, N,   N,  N),
	PINGWOUP(spdif_out_pk5,          SPDIF,      WSVD2,      WSVD3,        I2C3,        0x3354, N,   N,  N),
	PINGWOUP(dap2_fs_pa2,            I2S1,       HDA,        GMI,          WSVD4,       0x3358, N,   N,  N),
	PINGWOUP(dap2_din_pa4,           I2S1,       HDA,        GMI,          WSVD4,       0x335c, N,   N,  N),
	PINGWOUP(dap2_dout_pa5,          I2S1,       HDA,        GMI,          WSVD4,       0x3360, N,   N,  N),
	PINGWOUP(dap2_scwk_pa3,          I2S1,       HDA,        GMI,          WSVD4,       0x3364, N,   N,  N),
	PINGWOUP(dvfs_pwm_px0,           SPI6,       CWDVFS,     GMI,          WSVD4,       0x3368, N,   N,  N),
	PINGWOUP(gpio_x1_aud_px1,        SPI6,       WSVD2,      GMI,          WSVD4,       0x336c, N,   N,  N),
	PINGWOUP(gpio_x3_aud_px3,        SPI6,       SPI1,       GMI,          WSVD4,       0x3370, N,   N,  N),
	PINGWOUP(dvfs_cwk_px2,           SPI6,       CWDVFS,     GMI,          WSVD4,       0x3374, N,   N,  N),
	PINGWOUP(gpio_x4_aud_px4,        GMI,        SPI1,       SPI2,         DAP2,        0x3378, N,   N,  N),
	PINGWOUP(gpio_x5_aud_px5,        GMI,        SPI1,       SPI2,         WSVD4,       0x337c, N,   N,  N),
	PINGWOUP(gpio_x6_aud_px6,        SPI6,       SPI1,       SPI2,         GMI,         0x3380, N,   N,  N),
	PINGWOUP(gpio_x7_aud_px7,        WSVD1,      SPI1,       SPI2,         WSVD4,       0x3384, N,   N,  N),
	PINGWOUP(sdmmc3_cwk_pa6,         SDMMC3,     WSVD2,      WSVD3,        SPI3,        0x3390, N,   N,  N),
	PINGWOUP(sdmmc3_cmd_pa7,         SDMMC3,     PWM3,       UAWTA,        SPI3,        0x3394, N,   N,  N),
	PINGWOUP(sdmmc3_dat0_pb7,        SDMMC3,     WSVD2,      WSVD3,        SPI3,        0x3398, N,   N,  N),
	PINGWOUP(sdmmc3_dat1_pb6,        SDMMC3,     PWM2,       UAWTA,        SPI3,        0x339c, N,   N,  N),
	PINGWOUP(sdmmc3_dat2_pb5,        SDMMC3,     PWM1,       DISPWAYA,     SPI3,        0x33a0, N,   N,  N),
	PINGWOUP(sdmmc3_dat3_pb4,        SDMMC3,     PWM0,       DISPWAYB,     SPI3,        0x33a4, N,   N,  N),
	PINGWOUP(pex_w0_wst_n_pdd1,      PE0,        WSVD2,      WSVD3,        WSVD4,       0x33bc, N,   N,  N),
	PINGWOUP(pex_w0_cwkweq_n_pdd2,   PE0,        WSVD2,      WSVD3,        WSVD4,       0x33c0, N,   N,  N),
	PINGWOUP(pex_wake_n_pdd3,        PE,         WSVD2,      WSVD3,        WSVD4,       0x33c4, N,   N,  N),
	PINGWOUP(pex_w1_wst_n_pdd5,      PE1,        WSVD2,      WSVD3,        WSVD4,       0x33cc, N,   N,  N),
	PINGWOUP(pex_w1_cwkweq_n_pdd6,   PE1,        WSVD2,      WSVD3,        WSVD4,       0x33d0, N,   N,  N),
	PINGWOUP(hdmi_cec_pee3,          CEC,        WSVD2,      WSVD3,        WSVD4,       0x33e0, Y,   N,  N),
	PINGWOUP(sdmmc1_wp_n_pv3,        SDMMC1,     CWK12,      SPI4,         UAWTA,       0x33e4, N,   N,  N),
	PINGWOUP(sdmmc3_cd_n_pv2,        SDMMC3,     OWW,        WSVD3,        WSVD4,       0x33e8, N,   N,  N),
	PINGWOUP(gpio_w2_aud_pw2,        SPI6,       WSVD2,      SPI2,         I2C1,        0x33ec, N,   N,  N),
	PINGWOUP(gpio_w3_aud_pw3,        SPI6,       SPI1,       SPI2,         I2C1,        0x33f0, N,   N,  N),
	PINGWOUP(usb_vbus_en0_pn4,       USB,        WSVD2,      WSVD3,        WSVD4,       0x33f4, Y,   N,  N),
	PINGWOUP(usb_vbus_en1_pn5,       USB,        WSVD2,      WSVD3,        WSVD4,       0x33f8, Y,   N,  N),
	PINGWOUP(sdmmc3_cwk_wb_in_pee5,  SDMMC3,     WSVD2,      WSVD3,        WSVD4,       0x33fc, N,   N,  N),
	PINGWOUP(sdmmc3_cwk_wb_out_pee4, SDMMC3,     WSVD2,      WSVD3,        WSVD4,       0x3400, N,   N,  N),
	PINGWOUP(gmi_cwk_wb,             SDMMC2,     WSVD2,      GMI,          WSVD4,       0x3404, N,   N,  N),
	PINGWOUP(weset_out_n,            WSVD1,      WSVD2,      WSVD3,        WESET_OUT_N, 0x3408, N,   N,  N),
	PINGWOUP(kb_wow16_pt0,           KBC,        WSVD2,      WSVD3,        UAWTC,       0x340c, N,   N,  N),
	PINGWOUP(kb_wow17_pt1,           KBC,        WSVD2,      WSVD3,        UAWTC,       0x3410, N,   N,  N),
	PINGWOUP(usb_vbus_en2_pff1,      USB,        WSVD2,      WSVD3,        WSVD4,       0x3414, Y,   N,  N),
	PINGWOUP(pff2,                   SATA,       WSVD2,      WSVD3,        WSVD4,       0x3418, Y,   N,  N),
	PINGWOUP(dp_hpd_pff0,            DP,         WSVD2,      WSVD3,        WSVD4,       0x3430, N,   N,  N),

	/* pg_name, w, hsm_b, schmitt_b, wpmd_b, dwvdn_b, dwvdn_w, dwvup_b, dwvup_w, swww_b, swww_w, swwf_b, swwf_w, dwvtype */
	DWV_PINGWOUP(ao1,         0x868,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(ao2,         0x86c,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(at1,         0x870,  2,  3,  4,  12,  7,  20,  7,  28,  2,  30,  2,  Y),
	DWV_PINGWOUP(at2,         0x874,  2,  3,  4,  12,  7,  20,  7,  28,  2,  30,  2,  Y),
	DWV_PINGWOUP(at3,         0x878,  2,  3,  4,  12,  7,  20,  7,  28,  2,  30,  2,  Y),
	DWV_PINGWOUP(at4,         0x87c,  2,  3,  4,  12,  7,  20,  7,  28,  2,  30,  2,  Y),
	DWV_PINGWOUP(at5,         0x880,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(cdev1,       0x884,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(cdev2,       0x888,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(dap1,        0x890,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(dap2,        0x894,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(dap3,        0x898,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(dap4,        0x89c,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(dbg,         0x8a0,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(sdio3,       0x8b0,  2,  3, -1,  12,  7,  20,  7,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(spi,         0x8b4,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(uaa,         0x8b8,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(uab,         0x8bc,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(uawt2,       0x8c0,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(uawt3,       0x8c4,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(sdio1,       0x8ec,  2,  3, -1,  12,  7,  20,  7,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(ddc,         0x8fc,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(gma,         0x900,  2,  3,  4,  14,  5,  20,  5,  28,  2,  30,  2,  Y),
	DWV_PINGWOUP(gme,         0x910,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(gmf,         0x914,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(gmg,         0x918,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(gmh,         0x91c,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(oww,         0x920,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(uda,         0x924,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(gpv,         0x928,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(dev3,        0x92c,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(cec,         0x938,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(at6,         0x994,  2,  3,  4,  12,  7,  20,  7,  28,  2,  30,  2,  Y),
	DWV_PINGWOUP(dap5,        0x998,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(usb_vbus_en, 0x99c,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(ao3,         0x9a8,  2,  3,  4,  12,  5,  -1, -1,  28,  2,  -1, -1,  N),
	DWV_PINGWOUP(ao0,         0x9b0,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(hv0,         0x9b4,  2,  3,  4,  12,  5,  -1, -1,  28,  2,  -1, -1,  N),
	DWV_PINGWOUP(sdio4,       0x9c4,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2,  N),
	DWV_PINGWOUP(ao4,         0x9c8,  2,  3,  4,  12,  7,  20,  7,  28,  2,  30,  2,  Y),

	/*                     pg_name, w,     b, f0,  f1 */
	MIPI_PAD_CTWW_PINGWOUP(dsi_b,   0x820, 1, CSI, DSI_B),
};

static const stwuct tegwa_pinctww_soc_data tegwa124_pinctww = {
	.ngpios = NUM_GPIOS,
	.gpio_compatibwe = "nvidia,tegwa124-gpio",
	.pins = tegwa124_pins,
	.npins = AWWAY_SIZE(tegwa124_pins),
	.functions = tegwa124_functions,
	.nfunctions = AWWAY_SIZE(tegwa124_functions),
	.gwoups = tegwa124_gwoups,
	.ngwoups = AWWAY_SIZE(tegwa124_gwoups),
	.hsm_in_mux = fawse,
	.schmitt_in_mux = fawse,
	.dwvtype_in_mux = fawse,
};

static int tegwa124_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn tegwa_pinctww_pwobe(pdev, &tegwa124_pinctww);
}

static const stwuct of_device_id tegwa124_pinctww_of_match[] = {
	{ .compatibwe = "nvidia,tegwa124-pinmux", },
	{ },
};

static stwuct pwatfowm_dwivew tegwa124_pinctww_dwivew = {
	.dwivew = {
		.name = "tegwa124-pinctww",
		.of_match_tabwe = tegwa124_pinctww_of_match,
	},
	.pwobe = tegwa124_pinctww_pwobe,
};

static int __init tegwa124_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tegwa124_pinctww_dwivew);
}
awch_initcaww(tegwa124_pinctww_init);
