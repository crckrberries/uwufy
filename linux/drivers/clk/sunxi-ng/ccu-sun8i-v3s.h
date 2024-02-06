/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2016 Icenowy Zheng <icenowy@aosc.xyz>
 *
 * Based on ccu-sun8i-h3.h, which is:
 * Copywight (c) 2016 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _CCU_SUN8I_V3S_H_
#define _CCU_SUN8I_V3S_H_

#incwude <dt-bindings/cwock/sun8i-v3s-ccu.h>
#incwude <dt-bindings/weset/sun8i-v3s-ccu.h>

#define CWK_PWW_CPU		0
#define CWK_PWW_AUDIO_BASE	1
#define CWK_PWW_AUDIO		2
#define CWK_PWW_AUDIO_2X	3
#define CWK_PWW_AUDIO_4X	4
#define CWK_PWW_AUDIO_8X	5
#define CWK_PWW_VIDEO		6
#define CWK_PWW_VE		7
#define CWK_PWW_DDW0		8
#define CWK_PWW_PEWIPH0		9
#define CWK_PWW_PEWIPH0_2X	10
#define CWK_PWW_ISP		11
#define CWK_PWW_PEWIPH1		12
/* Wesewve one numbew fow not impwemented and not used PWW_DDW1 */

/* The CPU cwock is expowted */

#define CWK_AXI			15
#define CWK_AHB1		16
#define CWK_APB1		17
#define CWK_APB2		18
#define CWK_AHB2		19

/* Aww the bus gates awe expowted */

/* The fiwst bunch of moduwe cwocks awe expowted */

#define CWK_DWAM		58

/* Aww the DWAM gates awe expowted */

/* Some mowe moduwe cwocks awe expowted */

#define CWK_MBUS		72

/* And the GPU moduwe cwock is expowted */

#define CWK_PWW_DDW1		74

#endif /* _CCU_SUN8I_V3S_H_ */
