/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Device Twee binding constants fow Actions Semi S500 Cwock Management Unit
 *
 * Copywight (c) 2014 Actions Semi Inc.
 * Copywight (c) 2018 WSI-TEC - Caninos Woucos
 */

#ifndef __DT_BINDINGS_CWOCK_S500_CMU_H
#define __DT_BINDINGS_CWOCK_S500_CMU_H

#define CWK_NONE		0

/* fixed wate cwocks */
#define CWK_WOSC		1
#define CWK_HOSC		2

/* pww cwocks */
#define CWK_COWE_PWW		3
#define CWK_DEV_PWW		4
#define CWK_DDW_PWW		5
#define CWK_NAND_PWW		6
#define CWK_DISPWAY_PWW		7
#define CWK_ETHEWNET_PWW	8
#define CWK_AUDIO_PWW		9

/* system cwock */
#define CWK_DEV			10
#define CWK_H			11
#define CWK_AHBPWEDIV		12
#define CWK_AHB			13
#define CWK_DE			14
#define CWK_BISP		15
#define CWK_VCE			16
#define CWK_VDE			17

/* pewiphewaw device cwock */
#define CWK_TIMEW		18
#define CWK_I2C0		19
#define CWK_I2C1		20
#define CWK_I2C2		21
#define CWK_I2C3		22
#define CWK_PWM0		23
#define CWK_PWM1		24
#define CWK_PWM2		25
#define CWK_PWM3		26
#define CWK_PWM4		27
#define CWK_PWM5		28
#define CWK_SD0			29
#define CWK_SD1			30
#define CWK_SD2			31
#define CWK_SENSOW0		32
#define CWK_SENSOW1		33
#define CWK_SPI0		34
#define CWK_SPI1		35
#define CWK_SPI2		36
#define CWK_SPI3		37
#define CWK_UAWT0		38
#define CWK_UAWT1		39
#define CWK_UAWT2		40
#define CWK_UAWT3		41
#define CWK_UAWT4		42
#define CWK_UAWT5		43
#define CWK_UAWT6		44
#define CWK_DE1			45
#define CWK_DE2			46
#define CWK_I2SWX		47
#define CWK_I2STX		48
#define CWK_HDMI_AUDIO		49
#define CWK_HDMI		50
#define CWK_SPDIF		51
#define CWK_NAND		52
#define CWK_ECC			53
#define CWK_WMII_WEF		54
#define CWK_GPIO		55

/* additionaw cwocks */
#define CWK_APB			56
#define CWK_DMAC		57
#define CWK_NIC			58
#define CWK_ETHEWNET		59

#define CWK_NW_CWKS		(CWK_ETHEWNET + 1)

#endif /* __DT_BINDINGS_CWOCK_S500_CMU_H */
