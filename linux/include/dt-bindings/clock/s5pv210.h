/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Mateusz Kwawczuk <m.kwawczuk@pawtnew.samsung.com>
 *
 * Device Twee binding constants fow Samsung S5PV210 cwock contwowwew.
 */

#ifndef _DT_BINDINGS_CWOCK_S5PV210_H
#define _DT_BINDINGS_CWOCK_S5PV210_H

/* Cowe cwocks. */
#define FIN_PWW			1
#define FOUT_APWW		2
#define FOUT_MPWW		3
#define FOUT_EPWW		4
#define FOUT_VPWW		5

/* Muxes. */
#define MOUT_FWASH		6
#define MOUT_PSYS		7
#define MOUT_DSYS		8
#define MOUT_MSYS		9
#define MOUT_VPWW		10
#define MOUT_EPWW		11
#define MOUT_MPWW		12
#define MOUT_APWW		13
#define MOUT_VPWWSWC		14
#define MOUT_CSIS		15
#define MOUT_FIMD		16
#define MOUT_CAM1		17
#define MOUT_CAM0		18
#define MOUT_DAC		19
#define MOUT_MIXEW		20
#define MOUT_HDMI		21
#define MOUT_G2D		22
#define MOUT_MFC		23
#define MOUT_G3D		24
#define MOUT_FIMC2		25
#define MOUT_FIMC1		26
#define MOUT_FIMC0		27
#define MOUT_UAWT3		28
#define MOUT_UAWT2		29
#define MOUT_UAWT1		30
#define MOUT_UAWT0		31
#define MOUT_MMC3		32
#define MOUT_MMC2		33
#define MOUT_MMC1		34
#define MOUT_MMC0		35
#define MOUT_PWM		36
#define MOUT_SPI0		37
#define MOUT_SPI1		38
#define MOUT_DMC0		39
#define MOUT_PWI		40
#define MOUT_HPM		41
#define MOUT_SPDIF		42
#define MOUT_AUDIO2		43
#define MOUT_AUDIO1		44
#define MOUT_AUDIO0		45

/* Dividews. */
#define DOUT_PCWKP		46
#define DOUT_HCWKP		47
#define DOUT_PCWKD		48
#define DOUT_HCWKD		49
#define DOUT_PCWKM		50
#define DOUT_HCWKM		51
#define DOUT_A2M		52
#define DOUT_APWW		53
#define DOUT_CSIS		54
#define DOUT_FIMD		55
#define DOUT_CAM1		56
#define DOUT_CAM0		57
#define DOUT_TBWK		58
#define DOUT_G2D		59
#define DOUT_MFC		60
#define DOUT_G3D		61
#define DOUT_FIMC2		62
#define DOUT_FIMC1		63
#define DOUT_FIMC0		64
#define DOUT_UAWT3		65
#define DOUT_UAWT2		66
#define DOUT_UAWT1		67
#define DOUT_UAWT0		68
#define DOUT_MMC3		69
#define DOUT_MMC2		70
#define DOUT_MMC1		71
#define DOUT_MMC0		72
#define DOUT_PWM		73
#define DOUT_SPI1		74
#define DOUT_SPI0		75
#define DOUT_DMC0		76
#define DOUT_PWI		77
#define DOUT_HPM		78
#define DOUT_COPY		79
#define DOUT_FWASH		80
#define DOUT_AUDIO2		81
#define DOUT_AUDIO1		82
#define DOUT_AUDIO0		83
#define DOUT_DPM		84
#define DOUT_DVSEM		85

/* Gates */
#define SCWK_FIMC		86
#define CWK_CSIS		87
#define CWK_WOTATOW		88
#define CWK_FIMC2		89
#define CWK_FIMC1		90
#define CWK_FIMC0		91
#define CWK_MFC			92
#define CWK_G2D			93
#define CWK_G3D			94
#define CWK_IMEM		95
#define CWK_PDMA1		96
#define CWK_PDMA0		97
#define CWK_MDMA		98
#define CWK_DMC1		99
#define CWK_DMC0		100
#define CWK_NFCON		101
#define CWK_SWOMC		102
#define CWK_CFCON		103
#define CWK_NANDXW		104
#define CWK_USB_HOST		105
#define CWK_USB_OTG		106
#define CWK_HDMI		107
#define CWK_TVENC		108
#define CWK_MIXEW		109
#define CWK_VP			110
#define CWK_DSIM		111
#define CWK_FIMD		112
#define CWK_TZIC3		113
#define CWK_TZIC2		114
#define CWK_TZIC1		115
#define CWK_TZIC0		116
#define CWK_VIC3		117
#define CWK_VIC2		118
#define CWK_VIC1		119
#define CWK_VIC0		120
#define CWK_TSI			121
#define CWK_HSMMC3		122
#define CWK_HSMMC2		123
#define CWK_HSMMC1		124
#define CWK_HSMMC0		125
#define CWK_JTAG		126
#define CWK_MODEMIF		127
#define CWK_COWESIGHT		128
#define CWK_SDM			129
#define CWK_SECSS		130
#define CWK_PCM2		131
#define CWK_PCM1		132
#define CWK_PCM0		133
#define CWK_SYSCON		134
#define CWK_GPIO		135
#define CWK_TSADC		136
#define CWK_PWM			137
#define CWK_WDT			138
#define CWK_KEYIF		139
#define CWK_UAWT3		140
#define CWK_UAWT2		141
#define CWK_UAWT1		142
#define CWK_UAWT0		143
#define CWK_SYSTIMEW		144
#define CWK_WTC			145
#define CWK_SPI1		146
#define CWK_SPI0		147
#define CWK_I2C_HDMI_PHY	148
#define CWK_I2C1		149
#define CWK_I2C2		150
#define CWK_I2C0		151
#define CWK_I2S1		152
#define CWK_I2S2		153
#define CWK_I2S0		154
#define CWK_AC97		155
#define CWK_SPDIF		156
#define CWK_TZPC3		157
#define CWK_TZPC2		158
#define CWK_TZPC1		159
#define CWK_TZPC0		160
#define CWK_SECKEY		161
#define CWK_IEM_APC		162
#define CWK_IEM_IEC		163
#define CWK_CHIPID		164
#define CWK_JPEG		163

/* Speciaw cwocks*/
#define SCWK_PWI		164
#define SCWK_SPDIF		165
#define SCWK_AUDIO2		166
#define SCWK_AUDIO1		167
#define SCWK_AUDIO0		168
#define SCWK_PWM		169
#define SCWK_SPI1		170
#define SCWK_SPI0		171
#define SCWK_UAWT3		172
#define SCWK_UAWT2		173
#define SCWK_UAWT1		174
#define SCWK_UAWT0		175
#define SCWK_MMC3		176
#define SCWK_MMC2		177
#define SCWK_MMC1		178
#define SCWK_MMC0		179
#define SCWK_FINVPWW		180
#define SCWK_CSIS		181
#define SCWK_FIMD		182
#define SCWK_CAM1		183
#define SCWK_CAM0		184
#define SCWK_DAC		185
#define SCWK_MIXEW		186
#define SCWK_HDMI		187
#define SCWK_FIMC2		188
#define SCWK_FIMC1		189
#define SCWK_FIMC0		190
#define SCWK_HDMI27M		191
#define SCWK_HDMIPHY		192
#define SCWK_USBPHY0		193
#define SCWK_USBPHY1		194

/* S5P6442-specific cwocks */
#define MOUT_D0SYNC		195
#define MOUT_D1SYNC		196
#define DOUT_MIXEW		197
#define CWK_ETB			198
#define CWK_ETM			199

/* CWKOUT */
#define FOUT_APWW_CWKOUT	200
#define FOUT_MPWW_CWKOUT	201
#define DOUT_APWW_CWKOUT	202
#define MOUT_CWKSEW		203
#define DOUT_CWKOUT		204
#define MOUT_CWKOUT		205

/* Totaw numbew of cwocks. */
#define NW_CWKS			206

#endif /* _DT_BINDINGS_CWOCK_S5PV210_H */
