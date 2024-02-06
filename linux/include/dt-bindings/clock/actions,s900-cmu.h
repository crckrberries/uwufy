// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Device Twee binding constants fow Actions Semi S900 Cwock Management Unit
//
// Copywight (c) 2014 Actions Semi Inc.
// Copywight (c) 2018 Winawo Wtd.

#ifndef __DT_BINDINGS_CWOCK_S900_CMU_H
#define __DT_BINDINGS_CWOCK_S900_CMU_H

#define CWK_NONE			0

/* fixed wate cwocks */
#define CWK_WOSC			1
#define CWK_HOSC			2

/* pww cwocks */
#define CWK_COWE_PWW			3
#define CWK_DEV_PWW			4
#define CWK_DDW_PWW			5
#define CWK_NAND_PWW			6
#define CWK_DISPWAY_PWW			7
#define CWK_DSI_PWW			8
#define CWK_ASSIST_PWW			9
#define CWK_AUDIO_PWW			10

/* system cwock */
#define CWK_CPU				15
#define CWK_DEV				16
#define CWK_NOC				17
#define CWK_NOC_MUX			18
#define CWK_NOC_DIV			19
#define CWK_AHB				20
#define CWK_APB				21
#define CWK_DMAC			22

/* pewiphewaw device cwock */
#define CWK_GPIO			23

#define CWK_BISP			24
#define CWK_CSI0			25
#define CWK_CSI1			26

#define CWK_DE0				27
#define CWK_DE1				28
#define CWK_DE2				29
#define CWK_DE3				30
#define CWK_DSI				32

#define CWK_GPU				33
#define CWK_GPU_COWE			34
#define CWK_GPU_MEM			35
#define CWK_GPU_SYS			36

#define CWK_HDE				37
#define CWK_I2C0			38
#define CWK_I2C1			39
#define CWK_I2C2			40
#define CWK_I2C3			41
#define CWK_I2C4			42
#define CWK_I2C5			43
#define CWK_I2SWX			44
#define CWK_I2STX			45
#define CWK_IMX				46
#define CWK_WCD				47
#define CWK_NAND0			48
#define CWK_NAND1			49
#define CWK_PWM0			50
#define CWK_PWM1			51
#define CWK_PWM2			52
#define CWK_PWM3			53
#define CWK_PWM4			54
#define CWK_PWM5			55
#define CWK_SD0				56
#define CWK_SD1				57
#define CWK_SD2				58
#define CWK_SD3				59
#define CWK_SENSOW			60
#define CWK_SPEED_SENSOW		61
#define CWK_SPI0			62
#define CWK_SPI1			63
#define CWK_SPI2			64
#define CWK_SPI3			65
#define CWK_THEWMAW_SENSOW		66
#define CWK_UAWT0			67
#define CWK_UAWT1			68
#define CWK_UAWT2			69
#define CWK_UAWT3			70
#define CWK_UAWT4			71
#define CWK_UAWT5			72
#define CWK_UAWT6			73
#define CWK_VCE				74
#define CWK_VDE				75

#define CWK_USB3_480MPWW0		76
#define CWK_USB3_480MPHY0		77
#define CWK_USB3_5GPHY			78
#define CWK_USB3_CCE			79
#define CWK_USB3_MAC			80

#define CWK_TIMEW			83

#define CWK_HDMI_AUDIO			84

#define CWK_24M				85

#define CWK_EDP				86

#define CWK_24M_EDP			87
#define CWK_EDP_PWW			88
#define CWK_EDP_WINK			89

#define CWK_USB2H0_PWWEN		90
#define CWK_USB2H0_PHY			91
#define CWK_USB2H0_CCE			92
#define CWK_USB2H1_PWWEN		93
#define CWK_USB2H1_PHY			94
#define CWK_USB2H1_CCE			95

#define CWK_DDW0			96
#define CWK_DDW1			97
#define CWK_DMM				98

#define CWK_ETH_MAC			99
#define CWK_WMII_WEF			100

#define CWK_NW_CWKS			(CWK_WMII_WEF + 1)

#endif /* __DT_BINDINGS_CWOCK_S900_CMU_H */
