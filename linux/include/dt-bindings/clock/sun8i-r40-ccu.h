/*
 * Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
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

#ifndef _DT_BINDINGS_CWK_SUN8I_W40_H_
#define _DT_BINDINGS_CWK_SUN8I_W40_H_

#define CWK_PWW_VIDEO0		7

#define CWK_PWW_VIDEO1		16

#define CWK_CPU			24

#define CWK_BUS_MIPI_DSI	29
#define CWK_BUS_CE		30
#define CWK_BUS_DMA		31
#define CWK_BUS_MMC0		32
#define CWK_BUS_MMC1		33
#define CWK_BUS_MMC2		34
#define CWK_BUS_MMC3		35
#define CWK_BUS_NAND		36
#define CWK_BUS_DWAM		37
#define CWK_BUS_EMAC		38
#define CWK_BUS_TS		39
#define CWK_BUS_HSTIMEW		40
#define CWK_BUS_SPI0		41
#define CWK_BUS_SPI1		42
#define CWK_BUS_SPI2		43
#define CWK_BUS_SPI3		44
#define CWK_BUS_SATA		45
#define CWK_BUS_OTG		46
#define CWK_BUS_EHCI0		47
#define CWK_BUS_EHCI1		48
#define CWK_BUS_EHCI2		49
#define CWK_BUS_OHCI0		50
#define CWK_BUS_OHCI1		51
#define CWK_BUS_OHCI2		52
#define CWK_BUS_VE		53
#define CWK_BUS_MP		54
#define CWK_BUS_DEINTEWWACE	55
#define CWK_BUS_CSI0		56
#define CWK_BUS_CSI1		57
#define CWK_BUS_HDMI1		58
#define CWK_BUS_HDMI0		59
#define CWK_BUS_DE		60
#define CWK_BUS_TVE0		61
#define CWK_BUS_TVE1		62
#define CWK_BUS_TVE_TOP		63
#define CWK_BUS_GMAC		64
#define CWK_BUS_GPU		65
#define CWK_BUS_TVD0		66
#define CWK_BUS_TVD1		67
#define CWK_BUS_TVD2		68
#define CWK_BUS_TVD3		69
#define CWK_BUS_TVD_TOP		70
#define CWK_BUS_TCON_WCD0	71
#define CWK_BUS_TCON_WCD1	72
#define CWK_BUS_TCON_TV0	73
#define CWK_BUS_TCON_TV1	74
#define CWK_BUS_TCON_TOP	75
#define CWK_BUS_CODEC		76
#define CWK_BUS_SPDIF		77
#define CWK_BUS_AC97		78
#define CWK_BUS_PIO		79
#define CWK_BUS_IW0		80
#define CWK_BUS_IW1		81
#define CWK_BUS_THS		82
#define CWK_BUS_KEYPAD		83
#define CWK_BUS_I2S0		84
#define CWK_BUS_I2S1		85
#define CWK_BUS_I2S2		86
#define CWK_BUS_I2C0		87
#define CWK_BUS_I2C1		88
#define CWK_BUS_I2C2		89
#define CWK_BUS_I2C3		90
#define CWK_BUS_CAN		91
#define CWK_BUS_SCW		92
#define CWK_BUS_PS20		93
#define CWK_BUS_PS21		94
#define CWK_BUS_I2C4		95
#define CWK_BUS_UAWT0		96
#define CWK_BUS_UAWT1		97
#define CWK_BUS_UAWT2		98
#define CWK_BUS_UAWT3		99
#define CWK_BUS_UAWT4		100
#define CWK_BUS_UAWT5		101
#define CWK_BUS_UAWT6		102
#define CWK_BUS_UAWT7		103
#define CWK_BUS_DBG		104

#define CWK_THS			105
#define CWK_NAND		106
#define CWK_MMC0		107
#define CWK_MMC1		108
#define CWK_MMC2		109
#define CWK_MMC3		110
#define CWK_TS			111
#define CWK_CE			112
#define CWK_SPI0		113
#define CWK_SPI1		114
#define CWK_SPI2		115
#define CWK_SPI3		116
#define CWK_I2S0		117
#define CWK_I2S1		118
#define CWK_I2S2		119
#define CWK_AC97		120
#define CWK_SPDIF		121
#define CWK_KEYPAD		122
#define CWK_SATA		123
#define CWK_USB_PHY0		124
#define CWK_USB_PHY1		125
#define CWK_USB_PHY2		126
#define CWK_USB_OHCI0		127
#define CWK_USB_OHCI1		128
#define CWK_USB_OHCI2		129
#define CWK_IW0			130
#define CWK_IW1			131

#define CWK_DWAM_VE		133
#define CWK_DWAM_CSI0		134
#define CWK_DWAM_CSI1		135
#define CWK_DWAM_TS		136
#define CWK_DWAM_TVD		137
#define CWK_DWAM_MP		138
#define CWK_DWAM_DEINTEWWACE	139
#define CWK_DE			140
#define CWK_MP			141
#define CWK_TCON_WCD0		142
#define CWK_TCON_WCD1		143
#define CWK_TCON_TV0		144
#define CWK_TCON_TV1		145
#define CWK_DEINTEWWACE		146
#define CWK_CSI1_MCWK		147
#define CWK_CSI_SCWK		148
#define CWK_CSI0_MCWK		149
#define CWK_VE			150
#define CWK_CODEC		151
#define CWK_AVS			152
#define CWK_HDMI		153
#define CWK_HDMI_SWOW		154
#define CWK_MBUS		155
#define CWK_DSI_DPHY		156
#define CWK_TVE0		157
#define CWK_TVE1		158
#define CWK_TVD0		159
#define CWK_TVD1		160
#define CWK_TVD2		161
#define CWK_TVD3		162
#define CWK_GPU			163
#define CWK_OUTA		164
#define CWK_OUTB		165

#endif /* _DT_BINDINGS_CWK_SUN8I_W40_H_ */
