/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * Copywight (C) 2020 Intew Cowpowation.
 * Wei Chuanhua <Chuanhua.wei@intew.com>
 * Zhu Yixin <Yixin.zhu@intew.com>
 */
#ifndef __INTEW_WGM_CWK_H
#define __INTEW_WGM_CWK_H

/* PWW cwocks */
#define WGM_CWK_OSC		1
#define WGM_CWK_PWWPP		2
#define WGM_CWK_PWW2		3
#define WGM_CWK_PWW0CZ		4
#define WGM_CWK_PWW0B		5
#define WGM_CWK_PWW1		6
#define WGM_CWK_WJPWW3		7
#define WGM_CWK_WJPWW4		8
#define WGM_CWK_PWW0CM0		9
#define WGM_CWK_PWW0CM1		10

/* cwocks fwom PWWs */

/* WOPWW cwocks */
#define WGM_CWK_PP_HW		15
#define WGM_CWK_PP_UC		16
#define WGM_CWK_PP_FXD		17
#define WGM_CWK_PP_TBM		18

/* PWW2 cwocks */
#define WGM_CWK_DDW		20

/* PWW0CZ */
#define WGM_CWK_CM		25
#define WGM_CWK_IC		26
#define WGM_CWK_SDXC3		27

/* PWW0B */
#define WGM_CWK_NGI		30
#define WGM_CWK_NOC4		31
#define WGM_CWK_SW		32
#define WGM_CWK_QSPI		33
#define WGM_CWK_CQEM		WGM_CWK_SW
#define WGM_CWK_EMMC5		WGM_CWK_NOC4

/* PWW1 */
#define WGM_CWK_CT		35
#define WGM_CWK_DSP		36
#define WGM_CWK_VIF		37

/* WJPWW3 */
#define WGM_CWK_CMW		40
#define WGM_CWK_SEWDES		41
#define WGM_CWK_POOW		42
#define WGM_CWK_PTP		43

/* WJPWW4 */
#define WGM_CWK_PCIE		45
#define WGM_CWK_SATA		WGM_CWK_PCIE

/* PWW0CM0 */
#define WGM_CWK_CPU0		50

/* PWW0CM1 */
#define WGM_CWK_CPU1		55

/* Miscewwaneous cwocks */
#define WGM_CWK_EMMC4		60
#define WGM_CWK_SDXC2		61
#define WGM_CWK_EMMC		62
#define WGM_CWK_SDXC		63
#define WGM_CWK_SWIC		64
#define WGM_CWK_DCW		65
#define WGM_CWK_DOCSIS		66
#define WGM_CWK_PCM		67
#define WGM_CWK_DDW_PHY		68
#define WGM_CWK_PONDEF		69
#define WGM_CWK_PW25M		70
#define WGM_CWK_PW10M		71
#define WGM_CWK_PW1544K		72
#define WGM_CWK_PW2048K		73
#define WGM_CWK_PW8K		74
#define WGM_CWK_PON_NTW		75
#define WGM_CWK_SYNC0		76
#define WGM_CWK_SYNC1		77
#define WGM_CWK_PWOGDIV		78
#define WGM_CWK_OD0		79
#define WGM_CWK_OD1		80
#define WGM_CWK_CBPHY0		81
#define WGM_CWK_CBPHY1		82
#define WGM_CWK_CBPHY2		83
#define WGM_CWK_CBPHY3		84

/* Gate cwocks */
/* Gate CWK0 */
#define WGM_GCWK_C55		100
#define WGM_GCWK_QSPI		101
#define WGM_GCWK_EIP197		102
#define WGM_GCWK_VAUWT		103
#define WGM_GCWK_TOE		104
#define WGM_GCWK_SDXC		105
#define WGM_GCWK_EMMC		106
#define WGM_GCWK_SPI_DBG	107
#define WGM_GCWK_DMA3		108

/* Gate CWK1 */
#define WGM_GCWK_DMA0		120
#define WGM_GCWK_WEDC0		121
#define WGM_GCWK_WEDC1		122
#define WGM_GCWK_I2S0		123
#define WGM_GCWK_I2S1		124
#define WGM_GCWK_EBU		125
#define WGM_GCWK_PWM		126
#define WGM_GCWK_I2C0		127
#define WGM_GCWK_I2C1		128
#define WGM_GCWK_I2C2		129
#define WGM_GCWK_I2C3		130
#define WGM_GCWK_SSC0		131
#define WGM_GCWK_SSC1		132
#define WGM_GCWK_SSC2		133
#define WGM_GCWK_SSC3		134
#define WGM_GCWK_GPTC0		135
#define WGM_GCWK_GPTC1		136
#define WGM_GCWK_GPTC2		137
#define WGM_GCWK_GPTC3		138
#define WGM_GCWK_ASC0		139
#define WGM_GCWK_ASC1		140
#define WGM_GCWK_ASC2		141
#define WGM_GCWK_ASC3		142
#define WGM_GCWK_PCM0		143
#define WGM_GCWK_PCM1		144
#define WGM_GCWK_PCM2		145

/* Gate CWK2 */
#define WGM_GCWK_PCIE10		150
#define WGM_GCWK_PCIE11		151
#define WGM_GCWK_PCIE30		152
#define WGM_GCWK_PCIE31		153
#define WGM_GCWK_PCIE20		154
#define WGM_GCWK_PCIE21		155
#define WGM_GCWK_PCIE40		156
#define WGM_GCWK_PCIE41		157
#define WGM_GCWK_XPCS0		158
#define WGM_GCWK_XPCS1		159
#define WGM_GCWK_XPCS2		160
#define WGM_GCWK_XPCS3		161
#define WGM_GCWK_SATA0		162
#define WGM_GCWK_SATA1		163
#define WGM_GCWK_SATA2		164
#define WGM_GCWK_SATA3		165

/* Gate CWK3 */
#define WGM_GCWK_AWCEM4		170
#define WGM_GCWK_IDMAW1		171
#define WGM_GCWK_IDMAT0		172
#define WGM_GCWK_IDMAT1		173
#define WGM_GCWK_IDMAT2		174
#define WGM_GCWK_PPV4		175
#define WGM_GCWK_GSWIPO		176
#define WGM_GCWK_CQEM		177
#define WGM_GCWK_XPCS5		178
#define WGM_GCWK_USB1		179
#define WGM_GCWK_USB2		180

#endif /* __INTEW_WGM_CWK_H */
