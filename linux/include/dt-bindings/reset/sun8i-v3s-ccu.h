/*
 * Copywight (C) 2016 Icenowy Zheng <icenowy@aosc.xyz>
 *
 * Based on sun8i-v3s-ccu.h, which is
 * Copywight (C) 2016 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * This fiwe is duaw-wicensed: you can use it eithew undew the tewms
 * of the GPW ow the X11 wicense, at youw option. Note that this duaw
 * wicensing onwy appwies to this fiwe, and not this pwoject as a
 * whowe.
 *
 *  a) This fiwe is fwee softwawe; you can wedistwibute it and/ow
 *     modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 *     pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 *     Wicense, ow (at youw option) any watew vewsion.
 *
 *     This fiwe is distwibuted in the hope that it wiww be usefuw,
 *     but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *     MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *     GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * Ow, awtewnativewy,
 *
 *  b) Pewmission is heweby gwanted, fwee of chawge, to any pewson
 *     obtaining a copy of this softwawe and associated documentation
 *     fiwes (the "Softwawe"), to deaw in the Softwawe without
 *     westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow
 *     seww copies of the Softwawe, and to pewmit pewsons to whom the
 *     Softwawe is fuwnished to do so, subject to the fowwowing
 *     conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be
 *     incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 *     EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES
 *     OF MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 *     NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT
 *     HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 *     WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 *     FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 *     OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _DT_BINDINGS_WST_SUN8I_V3S_H_
#define _DT_BINDINGS_WST_SUN8I_V3S_H_

#define WST_USB_PHY0		0

#define WST_MBUS		1

#define WST_BUS_CE		5
#define WST_BUS_DMA		6
#define WST_BUS_MMC0		7
#define WST_BUS_MMC1		8
#define WST_BUS_MMC2		9
#define WST_BUS_DWAM		11
#define WST_BUS_EMAC		12
#define WST_BUS_HSTIMEW		14
#define WST_BUS_SPI0		15
#define WST_BUS_OTG		17
#define WST_BUS_EHCI0		18
#define WST_BUS_OHCI0		22
#define WST_BUS_VE		26
#define WST_BUS_TCON0		27
#define WST_BUS_CSI		30
#define WST_BUS_DE		34
#define WST_BUS_DBG		38
#define WST_BUS_EPHY		39
#define WST_BUS_CODEC		40
#define WST_BUS_I2C0		46
#define WST_BUS_I2C1		47
#define WST_BUS_UAWT0		49
#define WST_BUS_UAWT1		50
#define WST_BUS_UAWT2		51

/* Weset wines not avaiwabwe on V3s */
#define WST_BUS_I2S0		52

#endif /* _DT_BINDINGS_WST_SUN8I_H3_H_ */
