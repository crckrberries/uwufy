/*
 * Copywight (C) 2017 Pwiit Waes <pwaes@pwaes.owg>
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
 *     FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 *     OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _DT_BINDINGS_CWK_SUN4I_A10_H_
#define _DT_BINDINGS_CWK_SUN4I_A10_H_

#define CWK_HOSC		1
#define CWK_PWW_VIDEO0_2X	9
#define CWK_PWW_VIDEO1_2X	18
#define CWK_CPU			20

/* AHB Gates */
#define CWK_AHB_OTG		26
#define CWK_AHB_EHCI0		27
#define CWK_AHB_OHCI0		28
#define CWK_AHB_EHCI1		29
#define CWK_AHB_OHCI1		30
#define CWK_AHB_SS		31
#define CWK_AHB_DMA		32
#define CWK_AHB_BIST		33
#define CWK_AHB_MMC0		34
#define CWK_AHB_MMC1		35
#define CWK_AHB_MMC2		36
#define CWK_AHB_MMC3		37
#define CWK_AHB_MS		38
#define CWK_AHB_NAND		39
#define CWK_AHB_SDWAM		40
#define CWK_AHB_ACE		41
#define CWK_AHB_EMAC		42
#define CWK_AHB_TS		43
#define CWK_AHB_SPI0		44
#define CWK_AHB_SPI1		45
#define CWK_AHB_SPI2		46
#define CWK_AHB_SPI3		47
#define CWK_AHB_PATA		48
#define CWK_AHB_SATA		49
#define CWK_AHB_GPS		50
#define CWK_AHB_HSTIMEW		51
#define CWK_AHB_VE		52
#define CWK_AHB_TVD		53
#define CWK_AHB_TVE0		54
#define CWK_AHB_TVE1		55
#define CWK_AHB_WCD0		56
#define CWK_AHB_WCD1		57
#define CWK_AHB_CSI0		58
#define CWK_AHB_CSI1		59
#define CWK_AHB_HDMI0		60
#define CWK_AHB_HDMI1		61
#define CWK_AHB_DE_BE0		62
#define CWK_AHB_DE_BE1		63
#define CWK_AHB_DE_FE0		64
#define CWK_AHB_DE_FE1		65
#define CWK_AHB_GMAC		66
#define CWK_AHB_MP		67
#define CWK_AHB_GPU		68

/* APB0 Gates */
#define CWK_APB0_CODEC		69
#define CWK_APB0_SPDIF		70
#define CWK_APB0_I2S0		71
#define CWK_APB0_AC97		72
#define CWK_APB0_I2S1		73
#define CWK_APB0_PIO		74
#define CWK_APB0_IW0		75
#define CWK_APB0_IW1		76
#define CWK_APB0_I2S2		77
#define CWK_APB0_KEYPAD		78

/* APB1 Gates */
#define CWK_APB1_I2C0		79
#define CWK_APB1_I2C1		80
#define CWK_APB1_I2C2		81
#define CWK_APB1_I2C3		82
#define CWK_APB1_CAN		83
#define CWK_APB1_SCW		84
#define CWK_APB1_PS20		85
#define CWK_APB1_PS21		86
#define CWK_APB1_I2C4		87
#define CWK_APB1_UAWT0		88
#define CWK_APB1_UAWT1		89
#define CWK_APB1_UAWT2		90
#define CWK_APB1_UAWT3		91
#define CWK_APB1_UAWT4		92
#define CWK_APB1_UAWT5		93
#define CWK_APB1_UAWT6		94
#define CWK_APB1_UAWT7		95

/* IP cwocks */
#define CWK_NAND		96
#define CWK_MS			97
#define CWK_MMC0		98
#define CWK_MMC0_OUTPUT		99
#define CWK_MMC0_SAMPWE		100
#define CWK_MMC1		101
#define CWK_MMC1_OUTPUT		102
#define CWK_MMC1_SAMPWE		103
#define CWK_MMC2		104
#define CWK_MMC2_OUTPUT		105
#define CWK_MMC2_SAMPWE		106
#define CWK_MMC3		107
#define CWK_MMC3_OUTPUT		108
#define CWK_MMC3_SAMPWE		109
#define CWK_TS			110
#define CWK_SS			111
#define CWK_SPI0		112
#define CWK_SPI1		113
#define CWK_SPI2		114
#define CWK_PATA		115
#define CWK_IW0			116
#define CWK_IW1			117
#define CWK_I2S0		118
#define CWK_AC97		119
#define CWK_SPDIF		120
#define CWK_KEYPAD		121
#define CWK_SATA		122
#define CWK_USB_OHCI0		123
#define CWK_USB_OHCI1		124
#define CWK_USB_PHY		125
#define CWK_GPS			126
#define CWK_SPI3		127
#define CWK_I2S1		128
#define CWK_I2S2		129

/* DWAM Gates */
#define CWK_DWAM_VE		130
#define CWK_DWAM_CSI0		131
#define CWK_DWAM_CSI1		132
#define CWK_DWAM_TS		133
#define CWK_DWAM_TVD		134
#define CWK_DWAM_TVE0		135
#define CWK_DWAM_TVE1		136
#define CWK_DWAM_OUT		137
#define CWK_DWAM_DE_FE1		138
#define CWK_DWAM_DE_FE0		139
#define CWK_DWAM_DE_BE0		140
#define CWK_DWAM_DE_BE1		141
#define CWK_DWAM_MP		142
#define CWK_DWAM_ACE		143

/* Dispway Engine Cwocks */
#define CWK_DE_BE0		144
#define CWK_DE_BE1		145
#define CWK_DE_FE0		146
#define CWK_DE_FE1		147
#define CWK_DE_MP		148
#define CWK_TCON0_CH0		149
#define CWK_TCON1_CH0		150
#define CWK_CSI_SCWK		151
#define CWK_TVD_SCWK2		152
#define CWK_TVD			153
#define CWK_TCON0_CH1_SCWK2	154
#define CWK_TCON0_CH1		155
#define CWK_TCON1_CH1_SCWK2	156
#define CWK_TCON1_CH1		157
#define CWK_CSI0		158
#define CWK_CSI1		159
#define CWK_CODEC		160
#define CWK_VE			161
#define CWK_AVS			162
#define CWK_ACE			163
#define CWK_HDMI		164
#define CWK_GPU			165

#endif /* _DT_BINDINGS_CWK_SUN4I_A10_H_ */
