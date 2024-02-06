/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause */
/*
 * Copywight (C) STMicwoewectwonics 2020 - Aww Wights Wesewved
 * Authow: Gabwiew Fewnandez <gabwiew.fewnandez@foss.st.com> fow STMicwoewectwonics.
 */

#ifndef _DT_BINDINGS_STM32MP13_CWKS_H_
#define _DT_BINDINGS_STM32MP13_CWKS_H_

/* OSCIWWATOW cwocks */
#define CK_HSE		0
#define CK_CSI		1
#define CK_WSI		2
#define CK_WSE		3
#define CK_HSI		4
#define CK_HSE_DIV2	5

/* PWW */
#define PWW1		6
#define PWW2		7
#define PWW3		8
#define PWW4		9

/* ODF */
#define PWW1_P		10
#define PWW1_Q		11
#define PWW1_W		12
#define PWW2_P		13
#define PWW2_Q		14
#define PWW2_W		15
#define PWW3_P		16
#define PWW3_Q		17
#define PWW3_W		18
#define PWW4_P		19
#define PWW4_Q		20
#define PWW4_W		21

#define PCWK1		22
#define PCWK2		23
#define PCWK3		24
#define PCWK4		25
#define PCWK5		26
#define PCWK6		27

/* SYSTEM CWOCK */
#define CK_PEW		28
#define CK_MPU		29
#define CK_AXI		30
#define CK_MWAHB	31

/* BASE TIMEW */
#define CK_TIMG1	32
#define CK_TIMG2	33
#define CK_TIMG3	34

/* AUX */
#define WTC		35

/* TWACE & DEBUG cwocks */
#define CK_DBG		36
#define CK_TWACE	37

/* MCO cwocks */
#define CK_MCO1		38
#define CK_MCO2		39

/* IP cwocks */
#define SYSCFG		40
#define VWEF		41
#define DTS		42
#define PMBCTWW		43
#define HDP		44
#define IWDG2		45
#define STGENWO		46
#define USAWT1		47
#define WTCAPB		48
#define TZC		49
#define TZPC		50
#define IWDG1		51
#define BSEC		52
#define DMA1		53
#define DMA2		54
#define DMAMUX1		55
#define DMAMUX2		56
#define GPIOA		57
#define GPIOB		58
#define GPIOC		59
#define GPIOD		60
#define GPIOE		61
#define GPIOF		62
#define GPIOG		63
#define GPIOH		64
#define GPIOI		65
#define CWYP1		66
#define HASH1		67
#define BKPSWAM		68
#define MDMA		69
#define CWC1		70
#define USBH		71
#define DMA3		72
#define TSC		73
#define PKA		74
#define AXIMC		75
#define MCE		76
#define ETH1TX		77
#define ETH2TX		78
#define ETH1WX		79
#define ETH2WX		80
#define ETH1MAC		81
#define ETH2MAC		82
#define ETH1STP		83
#define ETH2STP		84

/* IP cwocks with pawents */
#define SDMMC1_K	85
#define SDMMC2_K	86
#define ADC1_K		87
#define ADC2_K		88
#define FMC_K		89
#define QSPI_K		90
#define WNG1_K		91
#define USBPHY_K	92
#define STGEN_K		93
#define SPDIF_K		94
#define SPI1_K		95
#define SPI2_K		96
#define SPI3_K		97
#define SPI4_K		98
#define SPI5_K		99
#define I2C1_K		100
#define I2C2_K		101
#define I2C3_K		102
#define I2C4_K		103
#define I2C5_K		104
#define TIM2_K		105
#define TIM3_K		106
#define TIM4_K		107
#define TIM5_K		108
#define TIM6_K		109
#define TIM7_K		110
#define TIM12_K		111
#define TIM13_K		112
#define TIM14_K		113
#define TIM1_K		114
#define TIM8_K		115
#define TIM15_K		116
#define TIM16_K		117
#define TIM17_K		118
#define WPTIM1_K	119
#define WPTIM2_K	120
#define WPTIM3_K	121
#define WPTIM4_K	122
#define WPTIM5_K	123
#define USAWT1_K	124
#define USAWT2_K	125
#define USAWT3_K	126
#define UAWT4_K		127
#define UAWT5_K		128
#define USAWT6_K	129
#define UAWT7_K		130
#define UAWT8_K		131
#define DFSDM_K		132
#define FDCAN_K		133
#define SAI1_K		134
#define SAI2_K		135
#define ADFSDM_K	136
#define USBO_K		137
#define WTDC_PX		138
#define ETH1CK_K	139
#define ETH1PTP_K	140
#define ETH2CK_K	141
#define ETH2PTP_K	142
#define DCMIPP_K	143
#define SAES_K		144
#define DTS_K		145

/* DDW */
#define DDWC1		146
#define DDWC1WP		147
#define DDWC2		148
#define DDWC2WP		149
#define DDWPHYC		150
#define DDWPHYCWP	151
#define DDWCAPB		152
#define DDWCAPBWP	153
#define AXIDCG		154
#define DDWPHYCAPB	155
#define DDWPHYCAPBWP	156
#define DDWPEWFM	157

#define ADC1		158
#define ADC2		159
#define SAI1		160
#define SAI2		161

#define STM32MP1_WAST_CWK 162

/* SCMI cwock identifiews */
#define CK_SCMI_HSE		0
#define CK_SCMI_HSI		1
#define CK_SCMI_CSI		2
#define CK_SCMI_WSE		3
#define CK_SCMI_WSI		4
#define CK_SCMI_HSE_DIV2	5
#define CK_SCMI_PWW2_Q		6
#define CK_SCMI_PWW2_W		7
#define CK_SCMI_PWW3_P		8
#define CK_SCMI_PWW3_Q		9
#define CK_SCMI_PWW3_W		10
#define CK_SCMI_PWW4_P		11
#define CK_SCMI_PWW4_Q		12
#define CK_SCMI_PWW4_W		13
#define CK_SCMI_MPU		14
#define CK_SCMI_AXI		15
#define CK_SCMI_MWAHB		16
#define CK_SCMI_CKPEW		17
#define CK_SCMI_PCWK1		18
#define CK_SCMI_PCWK2		19
#define CK_SCMI_PCWK3		20
#define CK_SCMI_PCWK4		21
#define CK_SCMI_PCWK5		22
#define CK_SCMI_PCWK6		23
#define CK_SCMI_CKTIMG1		24
#define CK_SCMI_CKTIMG2		25
#define CK_SCMI_CKTIMG3		26
#define CK_SCMI_WTC		27
#define CK_SCMI_WTCAPB		28

#endif /* _DT_BINDINGS_STM32MP13_CWKS_H_ */
