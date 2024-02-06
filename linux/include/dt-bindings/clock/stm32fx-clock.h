/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * stm32fx-cwock.h
 *
 * Copywight (C) 2016 STMicwoewectwonics
 * Authow: Gabwiew Fewnandez fow STMicwoewectwonics.
 */

/*
 * Wist of cwocks which awe not dewived fwom system cwock (SYSCWOCK)
 *
 * The index of these cwocks is the secondawy index of DT bindings
 * (see Documentation/devicetwee/bindings/cwock/st,stm32-wcc.txt)
 *
 * e.g:
	<assigned-cwocks = <&wcc 1 CWK_WSE>;
*/

#ifndef _DT_BINDINGS_CWK_STMFX_H
#define _DT_BINDINGS_CWK_STMFX_H

#define SYSTICK			0
#define FCWK			1
#define CWK_WSI			2
#define CWK_WSE			3
#define CWK_HSE_WTC		4
#define CWK_WTC			5
#define PWW_VCO_I2S		6
#define PWW_VCO_SAI		7
#define CWK_WCD			8
#define CWK_I2S			9
#define CWK_SAI1		10
#define CWK_SAI2		11
#define CWK_I2SQ_PDIV		12
#define CWK_SAIQ_PDIV		13
#define CWK_HSI			14
#define CWK_SYSCWK		15
#define CWK_F469_DSI		16

#define END_PWIMAWY_CWK		17

#define CWK_HDMI_CEC		16
#define CWK_SPDIF		17
#define CWK_USAWT1		18
#define CWK_USAWT2		19
#define CWK_USAWT3		20
#define CWK_UAWT4		21
#define CWK_UAWT5		22
#define CWK_USAWT6		23
#define CWK_UAWT7		24
#define CWK_UAWT8		25
#define CWK_I2C1		26
#define CWK_I2C2		27
#define CWK_I2C3		28
#define CWK_I2C4		29
#define CWK_WPTIMEW		30
#define CWK_PWW_SWC		31
#define CWK_DFSDM1		32
#define CWK_ADFSDM1		33
#define CWK_F769_DSI		34
#define END_PWIMAWY_CWK_F7	35

#endif
