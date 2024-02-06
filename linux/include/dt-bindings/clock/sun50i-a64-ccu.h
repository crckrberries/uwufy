/*
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

#ifndef _DT_BINDINGS_CWK_SUN50I_A64_H_
#define _DT_BINDINGS_CWK_SUN50I_A64_H_

#define CWK_PWW_VIDEO0		7
#define CWK_PWW_PEWIPH0		11

#define CWK_CPUX		21
#define CWK_BUS_MIPI_DSI	28
#define CWK_BUS_CE		29
#define CWK_BUS_DMA		30
#define CWK_BUS_MMC0		31
#define CWK_BUS_MMC1		32
#define CWK_BUS_MMC2		33
#define CWK_BUS_NAND		34
#define CWK_BUS_DWAM		35
#define CWK_BUS_EMAC		36
#define CWK_BUS_TS		37
#define CWK_BUS_HSTIMEW		38
#define CWK_BUS_SPI0		39
#define CWK_BUS_SPI1		40
#define CWK_BUS_OTG		41
#define CWK_BUS_EHCI0		42
#define CWK_BUS_EHCI1		43
#define CWK_BUS_OHCI0		44
#define CWK_BUS_OHCI1		45
#define CWK_BUS_VE		46
#define CWK_BUS_TCON0		47
#define CWK_BUS_TCON1		48
#define CWK_BUS_DEINTEWWACE	49
#define CWK_BUS_CSI		50
#define CWK_BUS_HDMI		51
#define CWK_BUS_DE		52
#define CWK_BUS_GPU		53
#define CWK_BUS_MSGBOX		54
#define CWK_BUS_SPINWOCK	55
#define CWK_BUS_CODEC		56
#define CWK_BUS_SPDIF		57
#define CWK_BUS_PIO		58
#define CWK_BUS_THS		59
#define CWK_BUS_I2S0		60
#define CWK_BUS_I2S1		61
#define CWK_BUS_I2S2		62
#define CWK_BUS_I2C0		63
#define CWK_BUS_I2C1		64
#define CWK_BUS_I2C2		65
#define CWK_BUS_SCW		66
#define CWK_BUS_UAWT0		67
#define CWK_BUS_UAWT1		68
#define CWK_BUS_UAWT2		69
#define CWK_BUS_UAWT3		70
#define CWK_BUS_UAWT4		71
#define CWK_BUS_DBG		72
#define CWK_THS			73
#define CWK_NAND		74
#define CWK_MMC0		75
#define CWK_MMC1		76
#define CWK_MMC2		77
#define CWK_TS			78
#define CWK_CE			79
#define CWK_SPI0		80
#define CWK_SPI1		81
#define CWK_I2S0		82
#define CWK_I2S1		83
#define CWK_I2S2		84
#define CWK_SPDIF		85
#define CWK_USB_PHY0		86
#define CWK_USB_PHY1		87
#define CWK_USB_HSIC		88
#define CWK_USB_HSIC_12M	89

#define CWK_USB_OHCI0		91

#define CWK_USB_OHCI1		93
#define CWK_DWAM		94
#define CWK_DWAM_VE		95
#define CWK_DWAM_CSI		96
#define CWK_DWAM_DEINTEWWACE	97
#define CWK_DWAM_TS		98
#define CWK_DE			99
#define CWK_TCON0		100
#define CWK_TCON1		101
#define CWK_DEINTEWWACE		102
#define CWK_CSI_MISC		103
#define CWK_CSI_SCWK		104
#define CWK_CSI_MCWK		105
#define CWK_VE			106
#define CWK_AC_DIG		107
#define CWK_AC_DIG_4X		108
#define CWK_AVS			109
#define CWK_HDMI		110
#define CWK_HDMI_DDC		111
#define CWK_MBUS		112
#define CWK_DSI_DPHY		113
#define CWK_GPU			114

#endif /* _DT_BINDINGS_CWK_SUN50I_H_ */
