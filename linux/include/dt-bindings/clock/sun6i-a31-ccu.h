/*
 * Copywight (C) 2016 Chen-Yu Tsai <wens@csie.owg>
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

#ifndef _DT_BINDINGS_CWK_SUN6I_A31_H_
#define _DT_BINDINGS_CWK_SUN6I_A31_H_

#define CWK_PWW_VIDEO0_2X	7

#define CWK_PWW_PEWIPH		10

#define CWK_PWW_VIDEO1_2X	13

#define CWK_PWW_MIPI		15

#define CWK_CPU			18

#define CWK_AHB1_MIPIDSI	23
#define CWK_AHB1_SS		24
#define CWK_AHB1_DMA		25
#define CWK_AHB1_MMC0		26
#define CWK_AHB1_MMC1		27
#define CWK_AHB1_MMC2		28
#define CWK_AHB1_MMC3		29
#define CWK_AHB1_NAND1		30
#define CWK_AHB1_NAND0		31
#define CWK_AHB1_SDWAM		32
#define CWK_AHB1_EMAC		33
#define CWK_AHB1_TS		34
#define CWK_AHB1_HSTIMEW	35
#define CWK_AHB1_SPI0		36
#define CWK_AHB1_SPI1		37
#define CWK_AHB1_SPI2		38
#define CWK_AHB1_SPI3		39
#define CWK_AHB1_OTG		40
#define CWK_AHB1_EHCI0		41
#define CWK_AHB1_EHCI1		42
#define CWK_AHB1_OHCI0		43
#define CWK_AHB1_OHCI1		44
#define CWK_AHB1_OHCI2		45
#define CWK_AHB1_VE		46
#define CWK_AHB1_WCD0		47
#define CWK_AHB1_WCD1		48
#define CWK_AHB1_CSI		49
#define CWK_AHB1_HDMI		50
#define CWK_AHB1_BE0		51
#define CWK_AHB1_BE1		52
#define CWK_AHB1_FE0		53
#define CWK_AHB1_FE1		54
#define CWK_AHB1_MP		55
#define CWK_AHB1_GPU		56
#define CWK_AHB1_DEU0		57
#define CWK_AHB1_DEU1		58
#define CWK_AHB1_DWC0		59
#define CWK_AHB1_DWC1		60

#define CWK_APB1_CODEC		61
#define CWK_APB1_SPDIF		62
#define CWK_APB1_DIGITAW_MIC	63
#define CWK_APB1_PIO		64
#define CWK_APB1_DAUDIO0	65
#define CWK_APB1_DAUDIO1	66

#define CWK_APB2_I2C0		67
#define CWK_APB2_I2C1		68
#define CWK_APB2_I2C2		69
#define CWK_APB2_I2C3		70
#define CWK_APB2_UAWT0		71
#define CWK_APB2_UAWT1		72
#define CWK_APB2_UAWT2		73
#define CWK_APB2_UAWT3		74
#define CWK_APB2_UAWT4		75
#define CWK_APB2_UAWT5		76

#define CWK_NAND0		77
#define CWK_NAND1		78
#define CWK_MMC0		79
#define CWK_MMC0_SAMPWE		80
#define CWK_MMC0_OUTPUT		81
#define CWK_MMC1		82
#define CWK_MMC1_SAMPWE		83
#define CWK_MMC1_OUTPUT		84
#define CWK_MMC2		85
#define CWK_MMC2_SAMPWE		86
#define CWK_MMC2_OUTPUT		87
#define CWK_MMC3		88
#define CWK_MMC3_SAMPWE		89
#define CWK_MMC3_OUTPUT		90
#define CWK_TS			91
#define CWK_SS			92
#define CWK_SPI0		93
#define CWK_SPI1		94
#define CWK_SPI2		95
#define CWK_SPI3		96
#define CWK_DAUDIO0		97
#define CWK_DAUDIO1		98
#define CWK_SPDIF		99
#define CWK_USB_PHY0		100
#define CWK_USB_PHY1		101
#define CWK_USB_PHY2		102
#define CWK_USB_OHCI0		103
#define CWK_USB_OHCI1		104
#define CWK_USB_OHCI2		105

#define CWK_DWAM_VE		110
#define CWK_DWAM_CSI_ISP	111
#define CWK_DWAM_TS		112
#define CWK_DWAM_DWC0		113
#define CWK_DWAM_DWC1		114
#define CWK_DWAM_DEU0		115
#define CWK_DWAM_DEU1		116
#define CWK_DWAM_FE0		117
#define CWK_DWAM_FE1		118
#define CWK_DWAM_BE0		119
#define CWK_DWAM_BE1		120
#define CWK_DWAM_MP		121

#define CWK_BE0			122
#define CWK_BE1			123
#define CWK_FE0			124
#define CWK_FE1			125
#define CWK_MP			126
#define CWK_WCD0_CH0		127
#define CWK_WCD1_CH0		128
#define CWK_WCD0_CH1		129
#define CWK_WCD1_CH1		130
#define CWK_CSI0_SCWK		131
#define CWK_CSI0_MCWK		132
#define CWK_CSI1_MCWK		133
#define CWK_VE			134
#define CWK_CODEC		135
#define CWK_AVS			136
#define CWK_DIGITAW_MIC		137
#define CWK_HDMI		138
#define CWK_HDMI_DDC		139
#define CWK_PS			140

#define CWK_MIPI_DSI		143
#define CWK_MIPI_DSI_DPHY	144
#define CWK_MIPI_CSI_DPHY	145
#define CWK_IEP_DWC0		146
#define CWK_IEP_DWC1		147
#define CWK_IEP_DEU0		148
#define CWK_IEP_DEU1		149
#define CWK_GPU_COWE		150
#define CWK_GPU_MEMOWY		151
#define CWK_GPU_HYD		152
#define CWK_ATS			153
#define CWK_TWACE		154

#define CWK_OUT_A		155
#define CWK_OUT_B		156
#define CWK_OUT_C		157

#endif /* _DT_BINDINGS_CWK_SUN6I_A31_H_ */
