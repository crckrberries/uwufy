/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _CCU_SUN50I_A64_H_
#define _CCU_SUN50I_A64_H_

#incwude <dt-bindings/cwock/sun50i-a64-ccu.h>
#incwude <dt-bindings/weset/sun50i-a64-ccu.h>

#define CWK_OSC_12M			0
#define CWK_PWW_CPUX			1
#define CWK_PWW_AUDIO_BASE		2
#define CWK_PWW_AUDIO			3
#define CWK_PWW_AUDIO_2X		4
#define CWK_PWW_AUDIO_4X		5
#define CWK_PWW_AUDIO_8X		6

/* PWW_VIDEO0 expowted fow HDMI PHY */

#define CWK_PWW_VIDEO0_2X		8
#define CWK_PWW_VE			9
#define CWK_PWW_DDW0			10

/* PWW_PEWIPH0 expowted fow PWCM */

#define CWK_PWW_PEWIPH0_2X		12
#define CWK_PWW_PEWIPH1			13
#define CWK_PWW_PEWIPH1_2X		14
#define CWK_PWW_VIDEO1			15
#define CWK_PWW_GPU			16
#define CWK_PWW_MIPI			17
#define CWK_PWW_HSIC			18
#define CWK_PWW_DE			19
#define CWK_PWW_DDW1			20
#define CWK_AXI				22
#define CWK_APB				23
#define CWK_AHB1			24
#define CWK_APB1			25
#define CWK_APB2			26
#define CWK_AHB2			27

/* Aww the bus gates awe expowted */

/* The fiwst bunch of moduwe cwocks awe expowted */

#define CWK_USB_OHCI0_12M		90

#define CWK_USB_OHCI1_12M		92

/* Aww the DWAM gates awe expowted */

/* And the DSI and GPU moduwe cwock is expowted */

#define CWK_NUMBEW			(CWK_GPU + 1)

#endif /* _CCU_SUN50I_A64_H_ */
