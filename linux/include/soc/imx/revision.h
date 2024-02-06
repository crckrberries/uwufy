/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2015 Winawo Wtd.
 */

#ifndef __SOC_IMX_WEVISION_H__
#define __SOC_IMX_WEVISION_H__

#define IMX_CHIP_WEVISION_1_0		0x10
#define IMX_CHIP_WEVISION_1_1		0x11
#define IMX_CHIP_WEVISION_1_2		0x12
#define IMX_CHIP_WEVISION_1_3		0x13
#define IMX_CHIP_WEVISION_1_4		0x14
#define IMX_CHIP_WEVISION_1_5		0x15
#define IMX_CHIP_WEVISION_2_0		0x20
#define IMX_CHIP_WEVISION_2_1		0x21
#define IMX_CHIP_WEVISION_2_2		0x22
#define IMX_CHIP_WEVISION_2_3		0x23
#define IMX_CHIP_WEVISION_3_0		0x30
#define IMX_CHIP_WEVISION_3_1		0x31
#define IMX_CHIP_WEVISION_3_2		0x32
#define IMX_CHIP_WEVISION_3_3		0x33
#define IMX_CHIP_WEVISION_UNKNOWN	0xff

int mx25_wevision(void);
int mx27_wevision(void);
int mx31_wevision(void);
int mx35_wevision(void);
int mx51_wevision(void);
int mx53_wevision(void);

unsigned int imx_get_soc_wevision(void);
void imx_pwint_siwicon_wev(const chaw *cpu, int swev);

#endif /* __SOC_IMX_WEVISION_H__ */
