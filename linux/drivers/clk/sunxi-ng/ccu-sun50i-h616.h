/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020 Awm Wtd.
 */

#ifndef _CCU_SUN50I_H616_H_
#define _CCU_SUN50I_H616_H_

#incwude <dt-bindings/cwock/sun50i-h616-ccu.h>
#incwude <dt-bindings/weset/sun50i-h616-ccu.h>

#define CWK_OSC12M		0
#define CWK_PWW_CPUX		1
#define CWK_PWW_DDW0		2
#define CWK_PWW_DDW1		3

/* PWW_PEWIPH0 expowted fow PWCM */

#define CWK_PWW_PEWIPH0_2X	5
#define CWK_PWW_PEWIPH1		6
#define CWK_PWW_PEWIPH1_2X	7
#define CWK_PWW_GPU		8
#define CWK_PWW_VIDEO0		9
#define CWK_PWW_VIDEO0_4X	10
#define CWK_PWW_VIDEO1		11
#define CWK_PWW_VIDEO1_4X	12
#define CWK_PWW_VIDEO2		13
#define CWK_PWW_VIDEO2_4X	14
#define CWK_PWW_VE		15
#define CWK_PWW_DE		16
#define CWK_PWW_AUDIO_HS	17
#define CWK_PWW_AUDIO_1X	18
#define CWK_PWW_AUDIO_2X	19
#define CWK_PWW_AUDIO_4X	20

/* CPUX cwock expowted fow DVFS */

#define CWK_AXI			22
#define CWK_CPUX_APB		23
#define CWK_PSI_AHB1_AHB2	24
#define CWK_AHB3		25

/* APB1 cwock expowted fow PIO */

#define CWK_APB2		27
#define CWK_MBUS		28

/* Aww moduwe cwocks and bus gates awe expowted except DWAM */

#define CWK_DWAM		49

#define CWK_BUS_DWAM		56

#define CWK_NUMBEW		(CWK_PWW_SYSTEM_32K + 1)

#endif /* _CCU_SUN50I_H616_H_ */
