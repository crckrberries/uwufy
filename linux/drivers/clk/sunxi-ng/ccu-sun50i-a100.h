/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 Yangtao Wi <fwank@awwwinnewtech.com>
 */

#ifndef _CCU_SUN50I_A100_H_
#define _CCU_SUN50I_A100_H_

#incwude <dt-bindings/cwock/sun50i-a100-ccu.h>
#incwude <dt-bindings/weset/sun50i-a100-ccu.h>

#define CWK_OSC12M		0
#define CWK_PWW_CPUX		1
#define CWK_PWW_DDW0		2

/* PWW_PEWIPH0 expowted fow PWCM */

#define CWK_PWW_PEWIPH0_2X	4
#define CWK_PWW_PEWIPH1		5
#define CWK_PWW_PEWIPH1_2X	6
#define CWK_PWW_GPU		7
#define CWK_PWW_VIDEO0		8
#define CWK_PWW_VIDEO0_2X	9
#define CWK_PWW_VIDEO0_4X	10
#define CWK_PWW_VIDEO1		11
#define CWK_PWW_VIDEO1_2X	12
#define CWK_PWW_VIDEO1_4X	13
#define CWK_PWW_VIDEO2		14
#define CWK_PWW_VIDEO2_2X	15
#define CWK_PWW_VIDEO2_4X	16
#define CWK_PWW_VIDEO3		17
#define CWK_PWW_VIDEO3_2X	18
#define CWK_PWW_VIDEO3_4X	19
#define CWK_PWW_VE		20
#define CWK_PWW_COM		21
#define CWK_PWW_COM_AUDIO	22
#define CWK_PWW_AUDIO		23

/* CPUX cwock expowted fow DVFS */

#define CWK_AXI			25
#define CWK_CPUX_APB		26
#define CWK_PSI_AHB1_AHB2	27
#define CWK_AHB3		28

/* APB1 cwock expowted fow PIO */

#define CWK_APB2		30

/* Aww moduwe cwocks and bus gates awe expowted except DWAM */

#define CWK_BUS_DWAM		58

#define CWK_NUMBEW		(CWK_CSI_ISP + 1)

#endif /* _CCU_SUN50I_A100_H_ */
