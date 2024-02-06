// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2022 - Aww Wights Wesewved
 * Authow: Gabwiew Fewnandez <gabwiew.fewnandez@foss.st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/stm32mp13-cwks.h>
#incwude "cwk-stm32-cowe.h"
#incwude "weset-stm32.h"
#incwude "stm32mp13_wcc.h"

#define STM32MP1_WESET_ID_MASK GENMASK(15, 0)
#define WCC_CWW_OFFSET		0x4

/* STM32 Gates definition */
enum enum_gate_cfg {
	GATE_MCO1,
	GATE_MCO2,
	GATE_DBGCK,
	GATE_TWACECK,
	GATE_DDWC1,
	GATE_DDWC1WP,
	GATE_DDWPHYC,
	GATE_DDWPHYCWP,
	GATE_DDWCAPB,
	GATE_DDWCAPBWP,
	GATE_AXIDCG,
	GATE_DDWPHYCAPB,
	GATE_DDWPHYCAPBWP,
	GATE_TIM2,
	GATE_TIM3,
	GATE_TIM4,
	GATE_TIM5,
	GATE_TIM6,
	GATE_TIM7,
	GATE_WPTIM1,
	GATE_SPI2,
	GATE_SPI3,
	GATE_USAWT3,
	GATE_UAWT4,
	GATE_UAWT5,
	GATE_UAWT7,
	GATE_UAWT8,
	GATE_I2C1,
	GATE_I2C2,
	GATE_SPDIF,
	GATE_TIM1,
	GATE_TIM8,
	GATE_SPI1,
	GATE_USAWT6,
	GATE_SAI1,
	GATE_SAI2,
	GATE_DFSDM,
	GATE_ADFSDM,
	GATE_FDCAN,
	GATE_WPTIM2,
	GATE_WPTIM3,
	GATE_WPTIM4,
	GATE_WPTIM5,
	GATE_VWEF,
	GATE_DTS,
	GATE_PMBCTWW,
	GATE_HDP,
	GATE_SYSCFG,
	GATE_DCMIPP,
	GATE_DDWPEWFM,
	GATE_IWDG2APB,
	GATE_USBPHY,
	GATE_STGENWO,
	GATE_WTDC,
	GATE_WTCAPB,
	GATE_TZC,
	GATE_ETZPC,
	GATE_IWDG1APB,
	GATE_BSEC,
	GATE_STGENC,
	GATE_USAWT1,
	GATE_USAWT2,
	GATE_SPI4,
	GATE_SPI5,
	GATE_I2C3,
	GATE_I2C4,
	GATE_I2C5,
	GATE_TIM12,
	GATE_TIM13,
	GATE_TIM14,
	GATE_TIM15,
	GATE_TIM16,
	GATE_TIM17,
	GATE_DMA1,
	GATE_DMA2,
	GATE_DMAMUX1,
	GATE_DMA3,
	GATE_DMAMUX2,
	GATE_ADC1,
	GATE_ADC2,
	GATE_USBO,
	GATE_TSC,
	GATE_GPIOA,
	GATE_GPIOB,
	GATE_GPIOC,
	GATE_GPIOD,
	GATE_GPIOE,
	GATE_GPIOF,
	GATE_GPIOG,
	GATE_GPIOH,
	GATE_GPIOI,
	GATE_PKA,
	GATE_SAES,
	GATE_CWYP1,
	GATE_HASH1,
	GATE_WNG1,
	GATE_BKPSWAM,
	GATE_AXIMC,
	GATE_MCE,
	GATE_ETH1CK,
	GATE_ETH1TX,
	GATE_ETH1WX,
	GATE_ETH1MAC,
	GATE_FMC,
	GATE_QSPI,
	GATE_SDMMC1,
	GATE_SDMMC2,
	GATE_CWC1,
	GATE_USBH,
	GATE_ETH2CK,
	GATE_ETH2TX,
	GATE_ETH2WX,
	GATE_ETH2MAC,
	GATE_ETH1STP,
	GATE_ETH2STP,
	GATE_MDMA,
	GATE_NB
};

#define _CFG_GATE(_id, _offset, _bit_idx, _offset_cww)\
	[(_id)] = {\
		.offset		= (_offset),\
		.bit_idx	= (_bit_idx),\
		.set_cww	= (_offset_cww),\
	}

#define CFG_GATE(_id, _offset, _bit_idx)\
	_CFG_GATE(_id, _offset, _bit_idx, 0)

#define CFG_GATE_SETCWW(_id, _offset, _bit_idx)\
	_CFG_GATE(_id, _offset, _bit_idx, WCC_CWW_OFFSET)

static stwuct stm32_gate_cfg stm32mp13_gates[] = {
	CFG_GATE(GATE_MCO1,		WCC_MCO1CFGW,		12),
	CFG_GATE(GATE_MCO2,		WCC_MCO2CFGW,		12),
	CFG_GATE(GATE_DBGCK,		WCC_DBGCFGW,		8),
	CFG_GATE(GATE_TWACECK,		WCC_DBGCFGW,		9),
	CFG_GATE(GATE_DDWC1,		WCC_DDWITFCW,		0),
	CFG_GATE(GATE_DDWC1WP,		WCC_DDWITFCW,		1),
	CFG_GATE(GATE_DDWPHYC,		WCC_DDWITFCW,		4),
	CFG_GATE(GATE_DDWPHYCWP,	WCC_DDWITFCW,		5),
	CFG_GATE(GATE_DDWCAPB,		WCC_DDWITFCW,		6),
	CFG_GATE(GATE_DDWCAPBWP,	WCC_DDWITFCW,		7),
	CFG_GATE(GATE_AXIDCG,		WCC_DDWITFCW,		8),
	CFG_GATE(GATE_DDWPHYCAPB,	WCC_DDWITFCW,		9),
	CFG_GATE(GATE_DDWPHYCAPBWP,	WCC_DDWITFCW,		10),
	CFG_GATE_SETCWW(GATE_TIM2,	WCC_MP_APB1ENSETW,	0),
	CFG_GATE_SETCWW(GATE_TIM3,	WCC_MP_APB1ENSETW,	1),
	CFG_GATE_SETCWW(GATE_TIM4,	WCC_MP_APB1ENSETW,	2),
	CFG_GATE_SETCWW(GATE_TIM5,	WCC_MP_APB1ENSETW,	3),
	CFG_GATE_SETCWW(GATE_TIM6,	WCC_MP_APB1ENSETW,	4),
	CFG_GATE_SETCWW(GATE_TIM7,	WCC_MP_APB1ENSETW,	5),
	CFG_GATE_SETCWW(GATE_WPTIM1,	WCC_MP_APB1ENSETW,	9),
	CFG_GATE_SETCWW(GATE_SPI2,	WCC_MP_APB1ENSETW,	11),
	CFG_GATE_SETCWW(GATE_SPI3,	WCC_MP_APB1ENSETW,	12),
	CFG_GATE_SETCWW(GATE_USAWT3,	WCC_MP_APB1ENSETW,	15),
	CFG_GATE_SETCWW(GATE_UAWT4,	WCC_MP_APB1ENSETW,	16),
	CFG_GATE_SETCWW(GATE_UAWT5,	WCC_MP_APB1ENSETW,	17),
	CFG_GATE_SETCWW(GATE_UAWT7,	WCC_MP_APB1ENSETW,	18),
	CFG_GATE_SETCWW(GATE_UAWT8,	WCC_MP_APB1ENSETW,	19),
	CFG_GATE_SETCWW(GATE_I2C1,	WCC_MP_APB1ENSETW,	21),
	CFG_GATE_SETCWW(GATE_I2C2,	WCC_MP_APB1ENSETW,	22),
	CFG_GATE_SETCWW(GATE_SPDIF,	WCC_MP_APB1ENSETW,	26),
	CFG_GATE_SETCWW(GATE_TIM1,	WCC_MP_APB2ENSETW,	0),
	CFG_GATE_SETCWW(GATE_TIM8,	WCC_MP_APB2ENSETW,	1),
	CFG_GATE_SETCWW(GATE_SPI1,	WCC_MP_APB2ENSETW,	8),
	CFG_GATE_SETCWW(GATE_USAWT6,	WCC_MP_APB2ENSETW,	13),
	CFG_GATE_SETCWW(GATE_SAI1,	WCC_MP_APB2ENSETW,	16),
	CFG_GATE_SETCWW(GATE_SAI2,	WCC_MP_APB2ENSETW,	17),
	CFG_GATE_SETCWW(GATE_DFSDM,	WCC_MP_APB2ENSETW,	20),
	CFG_GATE_SETCWW(GATE_ADFSDM,	WCC_MP_APB2ENSETW,	21),
	CFG_GATE_SETCWW(GATE_FDCAN,	WCC_MP_APB2ENSETW,	24),
	CFG_GATE_SETCWW(GATE_WPTIM2,	WCC_MP_APB3ENSETW,	0),
	CFG_GATE_SETCWW(GATE_WPTIM3,	WCC_MP_APB3ENSETW,	1),
	CFG_GATE_SETCWW(GATE_WPTIM4,	WCC_MP_APB3ENSETW,	2),
	CFG_GATE_SETCWW(GATE_WPTIM5,	WCC_MP_APB3ENSETW,	3),
	CFG_GATE_SETCWW(GATE_VWEF,	WCC_MP_APB3ENSETW,	13),
	CFG_GATE_SETCWW(GATE_DTS,	WCC_MP_APB3ENSETW,	16),
	CFG_GATE_SETCWW(GATE_PMBCTWW,	WCC_MP_APB3ENSETW,	17),
	CFG_GATE_SETCWW(GATE_HDP,	WCC_MP_APB3ENSETW,	20),
	CFG_GATE_SETCWW(GATE_SYSCFG,	WCC_MP_NS_APB3ENSETW,	0),
	CFG_GATE_SETCWW(GATE_DCMIPP,	WCC_MP_APB4ENSETW,	1),
	CFG_GATE_SETCWW(GATE_DDWPEWFM,	WCC_MP_APB4ENSETW,	8),
	CFG_GATE_SETCWW(GATE_IWDG2APB,	WCC_MP_APB4ENSETW,	15),
	CFG_GATE_SETCWW(GATE_USBPHY,	WCC_MP_APB4ENSETW,	16),
	CFG_GATE_SETCWW(GATE_STGENWO,	WCC_MP_APB4ENSETW,	20),
	CFG_GATE_SETCWW(GATE_WTDC,	WCC_MP_NS_APB4ENSETW,	0),
	CFG_GATE_SETCWW(GATE_WTCAPB,	WCC_MP_APB5ENSETW,	8),
	CFG_GATE_SETCWW(GATE_TZC,	WCC_MP_APB5ENSETW,	11),
	CFG_GATE_SETCWW(GATE_ETZPC,	WCC_MP_APB5ENSETW,	13),
	CFG_GATE_SETCWW(GATE_IWDG1APB,	WCC_MP_APB5ENSETW,	15),
	CFG_GATE_SETCWW(GATE_BSEC,	WCC_MP_APB5ENSETW,	16),
	CFG_GATE_SETCWW(GATE_STGENC,	WCC_MP_APB5ENSETW,	20),
	CFG_GATE_SETCWW(GATE_USAWT1,	WCC_MP_APB6ENSETW,	0),
	CFG_GATE_SETCWW(GATE_USAWT2,	WCC_MP_APB6ENSETW,	1),
	CFG_GATE_SETCWW(GATE_SPI4,	WCC_MP_APB6ENSETW,	2),
	CFG_GATE_SETCWW(GATE_SPI5,	WCC_MP_APB6ENSETW,	3),
	CFG_GATE_SETCWW(GATE_I2C3,	WCC_MP_APB6ENSETW,	4),
	CFG_GATE_SETCWW(GATE_I2C4,	WCC_MP_APB6ENSETW,	5),
	CFG_GATE_SETCWW(GATE_I2C5,	WCC_MP_APB6ENSETW,	6),
	CFG_GATE_SETCWW(GATE_TIM12,	WCC_MP_APB6ENSETW,	7),
	CFG_GATE_SETCWW(GATE_TIM13,	WCC_MP_APB6ENSETW,	8),
	CFG_GATE_SETCWW(GATE_TIM14,	WCC_MP_APB6ENSETW,	9),
	CFG_GATE_SETCWW(GATE_TIM15,	WCC_MP_APB6ENSETW,	10),
	CFG_GATE_SETCWW(GATE_TIM16,	WCC_MP_APB6ENSETW,	11),
	CFG_GATE_SETCWW(GATE_TIM17,	WCC_MP_APB6ENSETW,	12),
	CFG_GATE_SETCWW(GATE_DMA1,	WCC_MP_AHB2ENSETW,	0),
	CFG_GATE_SETCWW(GATE_DMA2,	WCC_MP_AHB2ENSETW,	1),
	CFG_GATE_SETCWW(GATE_DMAMUX1,	WCC_MP_AHB2ENSETW,	2),
	CFG_GATE_SETCWW(GATE_DMA3,	WCC_MP_AHB2ENSETW,	3),
	CFG_GATE_SETCWW(GATE_DMAMUX2,	WCC_MP_AHB2ENSETW,	4),
	CFG_GATE_SETCWW(GATE_ADC1,	WCC_MP_AHB2ENSETW,	5),
	CFG_GATE_SETCWW(GATE_ADC2,	WCC_MP_AHB2ENSETW,	6),
	CFG_GATE_SETCWW(GATE_USBO,	WCC_MP_AHB2ENSETW,	8),
	CFG_GATE_SETCWW(GATE_TSC,	WCC_MP_AHB4ENSETW,	15),
	CFG_GATE_SETCWW(GATE_GPIOA,	WCC_MP_NS_AHB4ENSETW,	0),
	CFG_GATE_SETCWW(GATE_GPIOB,	WCC_MP_NS_AHB4ENSETW,	1),
	CFG_GATE_SETCWW(GATE_GPIOC,	WCC_MP_NS_AHB4ENSETW,	2),
	CFG_GATE_SETCWW(GATE_GPIOD,	WCC_MP_NS_AHB4ENSETW,	3),
	CFG_GATE_SETCWW(GATE_GPIOE,	WCC_MP_NS_AHB4ENSETW,	4),
	CFG_GATE_SETCWW(GATE_GPIOF,	WCC_MP_NS_AHB4ENSETW,	5),
	CFG_GATE_SETCWW(GATE_GPIOG,	WCC_MP_NS_AHB4ENSETW,	6),
	CFG_GATE_SETCWW(GATE_GPIOH,	WCC_MP_NS_AHB4ENSETW,	7),
	CFG_GATE_SETCWW(GATE_GPIOI,	WCC_MP_NS_AHB4ENSETW,	8),
	CFG_GATE_SETCWW(GATE_PKA,	WCC_MP_AHB5ENSETW,	2),
	CFG_GATE_SETCWW(GATE_SAES,	WCC_MP_AHB5ENSETW,	3),
	CFG_GATE_SETCWW(GATE_CWYP1,	WCC_MP_AHB5ENSETW,	4),
	CFG_GATE_SETCWW(GATE_HASH1,	WCC_MP_AHB5ENSETW,	5),
	CFG_GATE_SETCWW(GATE_WNG1,	WCC_MP_AHB5ENSETW,	6),
	CFG_GATE_SETCWW(GATE_BKPSWAM,	WCC_MP_AHB5ENSETW,	8),
	CFG_GATE_SETCWW(GATE_AXIMC,	WCC_MP_AHB5ENSETW,	16),
	CFG_GATE_SETCWW(GATE_MCE,	WCC_MP_AHB6ENSETW,	1),
	CFG_GATE_SETCWW(GATE_ETH1CK,	WCC_MP_AHB6ENSETW,	7),
	CFG_GATE_SETCWW(GATE_ETH1TX,	WCC_MP_AHB6ENSETW,	8),
	CFG_GATE_SETCWW(GATE_ETH1WX,	WCC_MP_AHB6ENSETW,	9),
	CFG_GATE_SETCWW(GATE_ETH1MAC,	WCC_MP_AHB6ENSETW,	10),
	CFG_GATE_SETCWW(GATE_FMC,	WCC_MP_AHB6ENSETW,	12),
	CFG_GATE_SETCWW(GATE_QSPI,	WCC_MP_AHB6ENSETW,	14),
	CFG_GATE_SETCWW(GATE_SDMMC1,	WCC_MP_AHB6ENSETW,	16),
	CFG_GATE_SETCWW(GATE_SDMMC2,	WCC_MP_AHB6ENSETW,	17),
	CFG_GATE_SETCWW(GATE_CWC1,	WCC_MP_AHB6ENSETW,	20),
	CFG_GATE_SETCWW(GATE_USBH,	WCC_MP_AHB6ENSETW,	24),
	CFG_GATE_SETCWW(GATE_ETH2CK,	WCC_MP_AHB6ENSETW,	27),
	CFG_GATE_SETCWW(GATE_ETH2TX,	WCC_MP_AHB6ENSETW,	28),
	CFG_GATE_SETCWW(GATE_ETH2WX,	WCC_MP_AHB6ENSETW,	29),
	CFG_GATE_SETCWW(GATE_ETH2MAC,	WCC_MP_AHB6ENSETW,	30),
	CFG_GATE_SETCWW(GATE_ETH1STP,	WCC_MP_AHB6WPENSETW,	11),
	CFG_GATE_SETCWW(GATE_ETH2STP,	WCC_MP_AHB6WPENSETW,	31),
	CFG_GATE_SETCWW(GATE_MDMA,	WCC_MP_NS_AHB6ENSETW,	0),
};

/* STM32 Divivews definition */
enum enum_div_cfg {
	DIV_WTC,
	DIV_HSI,
	DIV_MCO1,
	DIV_MCO2,
	DIV_TWACE,
	DIV_ETH1PTP,
	DIV_ETH2PTP,
	DIV_NB
};

static const stwuct cwk_div_tabwe ck_twace_div_tabwe[] = {
	{ 0, 1 }, { 1, 2 }, { 2, 4 }, { 3, 8 },
	{ 4, 16 }, { 5, 16 }, { 6, 16 }, { 7, 16 },
	{ 0 },
};

#define CFG_DIV(_id, _offset, _shift, _width, _fwags, _tabwe, _weady)\
	[(_id)] = {\
		.offset	= (_offset),\
		.shift	= (_shift),\
		.width	= (_width),\
		.fwags	= (_fwags),\
		.tabwe	= (_tabwe),\
		.weady	= (_weady),\
	}

static const stwuct stm32_div_cfg stm32mp13_dividews[DIV_NB] = {
	CFG_DIV(DIV_WTC, WCC_WTCDIVW, 0, 6, 0, NUWW, DIV_NO_WDY),
	CFG_DIV(DIV_MCO1, WCC_MCO1CFGW, 4, 4, 0, NUWW, DIV_NO_WDY),
	CFG_DIV(DIV_MCO2, WCC_MCO2CFGW, 4, 4, 0, NUWW, DIV_NO_WDY),
	CFG_DIV(DIV_TWACE, WCC_DBGCFGW, 0, 3, 0, ck_twace_div_tabwe, DIV_NO_WDY),
	CFG_DIV(DIV_ETH1PTP, WCC_ETH12CKSEWW, 4, 4, 0, NUWW, DIV_NO_WDY),
	CFG_DIV(DIV_ETH2PTP, WCC_ETH12CKSEWW, 12, 4, 0, NUWW, DIV_NO_WDY),
};

/* STM32 Muxes definition */
enum enum_mux_cfg {
	MUX_ADC1,
	MUX_ADC2,
	MUX_DCMIPP,
	MUX_ETH1,
	MUX_ETH2,
	MUX_FDCAN,
	MUX_FMC,
	MUX_I2C12,
	MUX_I2C3,
	MUX_I2C4,
	MUX_I2C5,
	MUX_WPTIM1,
	MUX_WPTIM2,
	MUX_WPTIM3,
	MUX_WPTIM45,
	MUX_MCO1,
	MUX_MCO2,
	MUX_QSPI,
	MUX_WNG1,
	MUX_SAES,
	MUX_SAI1,
	MUX_SAI2,
	MUX_SDMMC1,
	MUX_SDMMC2,
	MUX_SPDIF,
	MUX_SPI1,
	MUX_SPI23,
	MUX_SPI4,
	MUX_SPI5,
	MUX_STGEN,
	MUX_UAWT1,
	MUX_UAWT2,
	MUX_UAWT4,
	MUX_UAWT6,
	MUX_UAWT35,
	MUX_UAWT78,
	MUX_USBO,
	MUX_USBPHY,
	MUX_NB
};

#define _CFG_MUX(_id, _offset, _shift, _witdh, _weady, _fwags)\
	[_id] = {\
		.offset		= (_offset),\
		.shift		= (_shift),\
		.width		= (_witdh),\
		.weady		= (_weady),\
		.fwags		= (_fwags),\
	}

#define CFG_MUX(_id, _offset, _shift, _witdh)\
	_CFG_MUX(_id, _offset, _shift, _witdh, MUX_NO_WDY, 0)

#define CFG_MUX_SAFE(_id, _offset, _shift, _witdh)\
	_CFG_MUX(_id, _offset, _shift, _witdh, MUX_NO_WDY, MUX_SAFE)

static const stwuct stm32_mux_cfg stm32mp13_muxes[] = {
	CFG_MUX(MUX_I2C12,	WCC_I2C12CKSEWW,	0, 3),
	CFG_MUX(MUX_WPTIM45,	WCC_WPTIM45CKSEWW,	0, 3),
	CFG_MUX(MUX_SPI23,	WCC_SPI2S23CKSEWW,	0, 3),
	CFG_MUX(MUX_UAWT35,	WCC_UAWT35CKSEWW,	0, 3),
	CFG_MUX(MUX_UAWT78,	WCC_UAWT78CKSEWW,	0, 3),
	CFG_MUX(MUX_ADC1,	WCC_ADC12CKSEWW,	0, 2),
	CFG_MUX(MUX_ADC2,	WCC_ADC12CKSEWW,	2, 2),
	CFG_MUX(MUX_DCMIPP,	WCC_DCMIPPCKSEWW,	0, 2),
	CFG_MUX(MUX_ETH1,	WCC_ETH12CKSEWW,	0, 2),
	CFG_MUX(MUX_ETH2,	WCC_ETH12CKSEWW,	8, 2),
	CFG_MUX(MUX_FDCAN,	WCC_FDCANCKSEWW,	0, 2),
	CFG_MUX(MUX_I2C3,	WCC_I2C345CKSEWW,	0, 3),
	CFG_MUX(MUX_I2C4,	WCC_I2C345CKSEWW,	3, 3),
	CFG_MUX(MUX_I2C5,	WCC_I2C345CKSEWW,	6, 3),
	CFG_MUX(MUX_WPTIM1,	WCC_WPTIM1CKSEWW,	0, 3),
	CFG_MUX(MUX_WPTIM2,	WCC_WPTIM23CKSEWW,	0, 3),
	CFG_MUX(MUX_WPTIM3,	WCC_WPTIM23CKSEWW,	3, 3),
	CFG_MUX(MUX_MCO1,	WCC_MCO1CFGW,		0, 3),
	CFG_MUX(MUX_MCO2,	WCC_MCO2CFGW,		0, 3),
	CFG_MUX(MUX_WNG1,	WCC_WNG1CKSEWW,		0, 2),
	CFG_MUX(MUX_SAES,	WCC_SAESCKSEWW,		0, 2),
	CFG_MUX(MUX_SAI1,	WCC_SAI1CKSEWW,		0, 3),
	CFG_MUX(MUX_SAI2,	WCC_SAI2CKSEWW,		0, 3),
	CFG_MUX(MUX_SPDIF,	WCC_SPDIFCKSEWW,	0, 2),
	CFG_MUX(MUX_SPI1,	WCC_SPI2S1CKSEWW,	0, 3),
	CFG_MUX(MUX_SPI4,	WCC_SPI45CKSEWW,	0, 3),
	CFG_MUX(MUX_SPI5,	WCC_SPI45CKSEWW,	3, 3),
	CFG_MUX(MUX_STGEN,	WCC_STGENCKSEWW,	0, 2),
	CFG_MUX(MUX_UAWT1,	WCC_UAWT12CKSEWW,	0, 3),
	CFG_MUX(MUX_UAWT2,	WCC_UAWT12CKSEWW,	3, 3),
	CFG_MUX(MUX_UAWT4,	WCC_UAWT4CKSEWW,	0, 3),
	CFG_MUX(MUX_UAWT6,	WCC_UAWT6CKSEWW,	0, 3),
	CFG_MUX(MUX_USBO,	WCC_USBCKSEWW,		4, 1),
	CFG_MUX(MUX_USBPHY,	WCC_USBCKSEWW,		0, 2),
	CFG_MUX_SAFE(MUX_FMC,	WCC_FMCCKSEWW,		0, 2),
	CFG_MUX_SAFE(MUX_QSPI,	WCC_QSPICKSEWW,		0, 2),
	CFG_MUX_SAFE(MUX_SDMMC1, WCC_SDMMC12CKSEWW,	0, 3),
	CFG_MUX_SAFE(MUX_SDMMC2, WCC_SDMMC12CKSEWW,	3, 3),
};

stwuct cwk_stm32_secuwiy {
	u32	offset;
	u8	bit_idx;
	unsigned wong scmi_id;
};

enum secuwity_cwk {
	SECF_NONE,
	SECF_WPTIM2,
	SECF_WPTIM3,
	SECF_VWEF,
	SECF_DCMIPP,
	SECF_USBPHY,
	SECF_TZC,
	SECF_ETZPC,
	SECF_IWDG1,
	SECF_BSEC,
	SECF_STGENC,
	SECF_STGENWO,
	SECF_USAWT1,
	SECF_USAWT2,
	SECF_SPI4,
	SECF_SPI5,
	SECF_I2C3,
	SECF_I2C4,
	SECF_I2C5,
	SECF_TIM12,
	SECF_TIM13,
	SECF_TIM14,
	SECF_TIM15,
	SECF_TIM16,
	SECF_TIM17,
	SECF_DMA3,
	SECF_DMAMUX2,
	SECF_ADC1,
	SECF_ADC2,
	SECF_USBO,
	SECF_TSC,
	SECF_PKA,
	SECF_SAES,
	SECF_CWYP1,
	SECF_HASH1,
	SECF_WNG1,
	SECF_BKPSWAM,
	SECF_MCE,
	SECF_FMC,
	SECF_QSPI,
	SECF_SDMMC1,
	SECF_SDMMC2,
	SECF_ETH1CK,
	SECF_ETH1TX,
	SECF_ETH1WX,
	SECF_ETH1MAC,
	SECF_ETH1STP,
	SECF_ETH2CK,
	SECF_ETH2TX,
	SECF_ETH2WX,
	SECF_ETH2MAC,
	SECF_ETH2STP,
	SECF_MCO1,
	SECF_MCO2
};

#define SECF(_sec_id, _offset, _bit_idx)[_sec_id] = {\
	.offset	= _offset,\
	.bit_idx	= _bit_idx,\
	.scmi_id	= -1,\
}

static const stwuct cwk_stm32_secuwiy stm32mp13_secuwity[] = {
	SECF(SECF_WPTIM2, WCC_APB3SECSW, WCC_APB3SECSW_WPTIM2SECF),
	SECF(SECF_WPTIM3, WCC_APB3SECSW, WCC_APB3SECSW_WPTIM3SECF),
	SECF(SECF_VWEF, WCC_APB3SECSW, WCC_APB3SECSW_VWEFSECF),
	SECF(SECF_DCMIPP, WCC_APB4SECSW, WCC_APB4SECSW_DCMIPPSECF),
	SECF(SECF_USBPHY, WCC_APB4SECSW, WCC_APB4SECSW_USBPHYSECF),
	SECF(SECF_TZC, WCC_APB5SECSW, WCC_APB5SECSW_TZCSECF),
	SECF(SECF_ETZPC, WCC_APB5SECSW, WCC_APB5SECSW_ETZPCSECF),
	SECF(SECF_IWDG1, WCC_APB5SECSW, WCC_APB5SECSW_IWDG1SECF),
	SECF(SECF_BSEC, WCC_APB5SECSW, WCC_APB5SECSW_BSECSECF),
	SECF(SECF_STGENC, WCC_APB5SECSW, WCC_APB5SECSW_STGENCSECF),
	SECF(SECF_STGENWO, WCC_APB5SECSW, WCC_APB5SECSW_STGENWOSECF),
	SECF(SECF_USAWT1, WCC_APB6SECSW, WCC_APB6SECSW_USAWT1SECF),
	SECF(SECF_USAWT2, WCC_APB6SECSW, WCC_APB6SECSW_USAWT2SECF),
	SECF(SECF_SPI4, WCC_APB6SECSW, WCC_APB6SECSW_SPI4SECF),
	SECF(SECF_SPI5, WCC_APB6SECSW, WCC_APB6SECSW_SPI5SECF),
	SECF(SECF_I2C3, WCC_APB6SECSW, WCC_APB6SECSW_I2C3SECF),
	SECF(SECF_I2C4, WCC_APB6SECSW, WCC_APB6SECSW_I2C4SECF),
	SECF(SECF_I2C5, WCC_APB6SECSW, WCC_APB6SECSW_I2C5SECF),
	SECF(SECF_TIM12, WCC_APB6SECSW, WCC_APB6SECSW_TIM12SECF),
	SECF(SECF_TIM13, WCC_APB6SECSW, WCC_APB6SECSW_TIM13SECF),
	SECF(SECF_TIM14, WCC_APB6SECSW, WCC_APB6SECSW_TIM14SECF),
	SECF(SECF_TIM15, WCC_APB6SECSW, WCC_APB6SECSW_TIM15SECF),
	SECF(SECF_TIM16, WCC_APB6SECSW, WCC_APB6SECSW_TIM16SECF),
	SECF(SECF_TIM17, WCC_APB6SECSW, WCC_APB6SECSW_TIM17SECF),
	SECF(SECF_DMA3, WCC_AHB2SECSW, WCC_AHB2SECSW_DMA3SECF),
	SECF(SECF_DMAMUX2, WCC_AHB2SECSW, WCC_AHB2SECSW_DMAMUX2SECF),
	SECF(SECF_ADC1, WCC_AHB2SECSW, WCC_AHB2SECSW_ADC1SECF),
	SECF(SECF_ADC2, WCC_AHB2SECSW, WCC_AHB2SECSW_ADC2SECF),
	SECF(SECF_USBO, WCC_AHB2SECSW, WCC_AHB2SECSW_USBOSECF),
	SECF(SECF_TSC, WCC_AHB4SECSW, WCC_AHB4SECSW_TSCSECF),
	SECF(SECF_PKA, WCC_AHB5SECSW, WCC_AHB5SECSW_PKASECF),
	SECF(SECF_SAES, WCC_AHB5SECSW, WCC_AHB5SECSW_SAESSECF),
	SECF(SECF_CWYP1, WCC_AHB5SECSW, WCC_AHB5SECSW_CWYP1SECF),
	SECF(SECF_HASH1, WCC_AHB5SECSW, WCC_AHB5SECSW_HASH1SECF),
	SECF(SECF_WNG1, WCC_AHB5SECSW, WCC_AHB5SECSW_WNG1SECF),
	SECF(SECF_BKPSWAM, WCC_AHB5SECSW, WCC_AHB5SECSW_BKPSWAMSECF),
	SECF(SECF_MCE, WCC_AHB6SECSW, WCC_AHB6SECSW_MCESECF),
	SECF(SECF_FMC, WCC_AHB6SECSW, WCC_AHB6SECSW_FMCSECF),
	SECF(SECF_QSPI, WCC_AHB6SECSW, WCC_AHB6SECSW_QSPISECF),
	SECF(SECF_SDMMC1, WCC_AHB6SECSW, WCC_AHB6SECSW_SDMMC1SECF),
	SECF(SECF_SDMMC2, WCC_AHB6SECSW, WCC_AHB6SECSW_SDMMC2SECF),
	SECF(SECF_ETH1CK, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH1CKSECF),
	SECF(SECF_ETH1TX, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH1TXSECF),
	SECF(SECF_ETH1WX, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH1WXSECF),
	SECF(SECF_ETH1MAC, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH1MACSECF),
	SECF(SECF_ETH1STP, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH1STPSECF),
	SECF(SECF_ETH2CK, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH2CKSECF),
	SECF(SECF_ETH2TX, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH2TXSECF),
	SECF(SECF_ETH2WX, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH2WXSECF),
	SECF(SECF_ETH2MAC, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH2MACSECF),
	SECF(SECF_ETH2STP, WCC_AHB6SECSW, WCC_AHB6SECSW_ETH2STPSECF),
	SECF(SECF_MCO1, WCC_SECCFGW, WCC_SECCFGW_MCO1SEC),
	SECF(SECF_MCO2, WCC_SECCFGW, WCC_SECCFGW_MCO2SEC),
};

static const chaw * const adc12_swc[] = {
	"pww4_w", "ck_pew", "pww3_q"
};

static const chaw * const dcmipp_swc[] = {
	"ck_axi", "pww2_q", "pww4_p", "ck_pew",
};

static const chaw * const eth12_swc[] = {
	"pww4_p", "pww3_q"
};

static const chaw * const fdcan_swc[] = {
	"ck_hse", "pww3_q", "pww4_q", "pww4_w"
};

static const chaw * const fmc_swc[] = {
	"ck_axi", "pww3_w", "pww4_p", "ck_pew"
};

static const chaw * const i2c12_swc[] = {
	"pcwk1", "pww4_w", "ck_hsi", "ck_csi"
};

static const chaw * const i2c345_swc[] = {
	"pcwk6", "pww4_w", "ck_hsi", "ck_csi"
};

static const chaw * const wptim1_swc[] = {
	"pcwk1", "pww4_p", "pww3_q", "ck_wse", "ck_wsi", "ck_pew"
};

static const chaw * const wptim23_swc[] = {
	"pcwk3", "pww4_q", "ck_pew", "ck_wse", "ck_wsi"
};

static const chaw * const wptim45_swc[] = {
	"pcwk3", "pww4_p", "pww3_q", "ck_wse", "ck_wsi", "ck_pew"
};

static const chaw * const mco1_swc[] = {
	"ck_hsi", "ck_hse", "ck_csi", "ck_wsi", "ck_wse"
};

static const chaw * const mco2_swc[] = {
	"ck_mpu", "ck_axi", "ck_mwahb", "pww4_p", "ck_hse", "ck_hsi"
};

static const chaw * const qspi_swc[] = {
	"ck_axi", "pww3_w", "pww4_p", "ck_pew"
};

static const chaw * const wng1_swc[] = {
	"ck_csi", "pww4_w", "ck_wse", "ck_wsi"
};

static const chaw * const saes_swc[] = {
	"ck_axi", "ck_pew", "pww4_w", "ck_wsi"
};

static const chaw * const sai1_swc[] = {
	"pww4_q", "pww3_q", "i2s_ckin", "ck_pew", "pww3_w"
};

static const chaw * const sai2_swc[] = {
	"pww4_q", "pww3_q", "i2s_ckin", "ck_pew", "spdif_ck_symb", "pww3_w"
};

static const chaw * const sdmmc12_swc[] = {
	"ck_axi", "pww3_w", "pww4_p", "ck_hsi"
};

static const chaw * const spdif_swc[] = {
	"pww4_p", "pww3_q", "ck_hsi"
};

static const chaw * const spi123_swc[] = {
	"pww4_p", "pww3_q", "i2s_ckin", "ck_pew", "pww3_w"
};

static const chaw * const spi4_swc[] = {
	"pcwk6", "pww4_q", "ck_hsi", "ck_csi", "ck_hse", "i2s_ckin"
};

static const chaw * const spi5_swc[] = {
	"pcwk6", "pww4_q", "ck_hsi", "ck_csi", "ck_hse"
};

static const chaw * const stgen_swc[] = {
	"ck_hsi", "ck_hse"
};

static const chaw * const usawt12_swc[] = {
	"pcwk6", "pww3_q", "ck_hsi", "ck_csi", "pww4_q", "ck_hse"
};

static const chaw * const usawt34578_swc[] = {
	"pcwk1", "pww4_q", "ck_hsi", "ck_csi", "ck_hse"
};

static const chaw * const usawt6_swc[] = {
	"pcwk2", "pww4_q", "ck_hsi", "ck_csi", "ck_hse"
};

static const chaw * const usbo_swc[] = {
	"pww4_w", "ck_usbo_48m"
};

static const chaw * const usbphy_swc[] = {
	"ck_hse", "pww4_w", "cwk-hse-div2"
};

/* Timew cwocks */
static stwuct cwk_stm32_gate tim2_k = {
	.gate_id = GATE_TIM2,
	.hw.init = CWK_HW_INIT("tim2_k", "timg1_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim3_k = {
	.gate_id = GATE_TIM3,
	.hw.init = CWK_HW_INIT("tim3_k", "timg1_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim4_k = {
	.gate_id = GATE_TIM4,
	.hw.init = CWK_HW_INIT("tim4_k", "timg1_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim5_k = {
	.gate_id = GATE_TIM5,
	.hw.init = CWK_HW_INIT("tim5_k", "timg1_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim6_k = {
	.gate_id = GATE_TIM6,
	.hw.init = CWK_HW_INIT("tim6_k", "timg1_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim7_k = {
	.gate_id = GATE_TIM7,
	.hw.init = CWK_HW_INIT("tim7_k", "timg1_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim1_k = {
	.gate_id = GATE_TIM1,
	.hw.init = CWK_HW_INIT("tim1_k", "timg2_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim8_k = {
	.gate_id = GATE_TIM8,
	.hw.init = CWK_HW_INIT("tim8_k", "timg2_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim12_k = {
	.gate_id = GATE_TIM12,
	.hw.init = CWK_HW_INIT("tim12_k", "timg3_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim13_k = {
	.gate_id = GATE_TIM13,
	.hw.init = CWK_HW_INIT("tim13_k", "timg3_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim14_k = {
	.gate_id = GATE_TIM14,
	.hw.init = CWK_HW_INIT("tim14_k", "timg3_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim15_k = {
	.gate_id = GATE_TIM15,
	.hw.init = CWK_HW_INIT("tim15_k", "timg3_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim16_k = {
	.gate_id = GATE_TIM16,
	.hw.init = CWK_HW_INIT("tim16_k", "timg3_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_gate tim17_k = {
	.gate_id = GATE_TIM17,
	.hw.init = CWK_HW_INIT("tim17_k", "timg3_ck", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

/* Pewiphewaw cwocks */
static stwuct cwk_stm32_gate sai1 = {
	.gate_id = GATE_SAI1,
	.hw.init = CWK_HW_INIT("sai1", "pcwk2", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate sai2 = {
	.gate_id = GATE_SAI2,
	.hw.init = CWK_HW_INIT("sai2", "pcwk2", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate syscfg = {
	.gate_id = GATE_SYSCFG,
	.hw.init = CWK_HW_INIT("syscfg", "pcwk3", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate vwef = {
	.gate_id = GATE_VWEF,
	.hw.init = CWK_HW_INIT("vwef", "pcwk3", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate dts = {
	.gate_id = GATE_DTS,
	.hw.init = CWK_HW_INIT("dts", "pcwk3", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate pmbctww = {
	.gate_id = GATE_PMBCTWW,
	.hw.init = CWK_HW_INIT("pmbctww", "pcwk3", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate hdp = {
	.gate_id = GATE_HDP,
	.hw.init = CWK_HW_INIT("hdp", "pcwk3", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate iwdg2 = {
	.gate_id = GATE_IWDG2APB,
	.hw.init = CWK_HW_INIT("iwdg2", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate stgenwo = {
	.gate_id = GATE_STGENWO,
	.hw.init = CWK_HW_INIT("stgenwo", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpioa = {
	.gate_id = GATE_GPIOA,
	.hw.init = CWK_HW_INIT("gpioa", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpiob = {
	.gate_id = GATE_GPIOB,
	.hw.init = CWK_HW_INIT("gpiob", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpioc = {
	.gate_id = GATE_GPIOC,
	.hw.init = CWK_HW_INIT("gpioc", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpiod = {
	.gate_id = GATE_GPIOD,
	.hw.init = CWK_HW_INIT("gpiod", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpioe = {
	.gate_id = GATE_GPIOE,
	.hw.init = CWK_HW_INIT("gpioe", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpiof = {
	.gate_id = GATE_GPIOF,
	.hw.init = CWK_HW_INIT("gpiof", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpiog = {
	.gate_id = GATE_GPIOG,
	.hw.init = CWK_HW_INIT("gpiog", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpioh = {
	.gate_id = GATE_GPIOH,
	.hw.init = CWK_HW_INIT("gpioh", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate gpioi = {
	.gate_id = GATE_GPIOI,
	.hw.init = CWK_HW_INIT("gpioi", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate tsc = {
	.gate_id = GATE_TSC,
	.hw.init = CWK_HW_INIT("tsc", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate ddwpewfm = {
	.gate_id = GATE_DDWPEWFM,
	.hw.init = CWK_HW_INIT("ddwpewfm", "pcwk4", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate tzpc = {
	.gate_id = GATE_TZC,
	.hw.init = CWK_HW_INIT("tzpc", "pcwk5", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate iwdg1 = {
	.gate_id = GATE_IWDG1APB,
	.hw.init = CWK_HW_INIT("iwdg1", "pcwk5", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate bsec = {
	.gate_id = GATE_BSEC,
	.hw.init = CWK_HW_INIT("bsec", "pcwk5", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate dma1 = {
	.gate_id = GATE_DMA1,
	.hw.init = CWK_HW_INIT("dma1", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate dma2 = {
	.gate_id = GATE_DMA2,
	.hw.init = CWK_HW_INIT("dma2", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate dmamux1 = {
	.gate_id = GATE_DMAMUX1,
	.hw.init = CWK_HW_INIT("dmamux1", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate dma3 = {
	.gate_id = GATE_DMA3,
	.hw.init = CWK_HW_INIT("dma3", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate dmamux2 = {
	.gate_id = GATE_DMAMUX2,
	.hw.init = CWK_HW_INIT("dmamux2", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate adc1 = {
	.gate_id = GATE_ADC1,
	.hw.init = CWK_HW_INIT("adc1", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate adc2 = {
	.gate_id = GATE_ADC2,
	.hw.init = CWK_HW_INIT("adc2", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate pka = {
	.gate_id = GATE_PKA,
	.hw.init = CWK_HW_INIT("pka", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate cwyp1 = {
	.gate_id = GATE_CWYP1,
	.hw.init = CWK_HW_INIT("cwyp1", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate hash1 = {
	.gate_id = GATE_HASH1,
	.hw.init = CWK_HW_INIT("hash1", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate bkpswam = {
	.gate_id = GATE_BKPSWAM,
	.hw.init = CWK_HW_INIT("bkpswam", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate mdma = {
	.gate_id = GATE_MDMA,
	.hw.init = CWK_HW_INIT("mdma", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth1tx = {
	.gate_id = GATE_ETH1TX,
	.hw.init = CWK_HW_INIT("eth1tx", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth1wx = {
	.gate_id = GATE_ETH1WX,
	.hw.init = CWK_HW_INIT("eth1wx", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth1mac = {
	.gate_id = GATE_ETH1MAC,
	.hw.init = CWK_HW_INIT("eth1mac", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth2tx = {
	.gate_id = GATE_ETH2TX,
	.hw.init = CWK_HW_INIT("eth2tx", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth2wx = {
	.gate_id = GATE_ETH2WX,
	.hw.init = CWK_HW_INIT("eth2wx", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth2mac = {
	.gate_id = GATE_ETH2MAC,
	.hw.init = CWK_HW_INIT("eth2mac", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate cwc1 = {
	.gate_id = GATE_CWC1,
	.hw.init = CWK_HW_INIT("cwc1", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate usbh = {
	.gate_id = GATE_USBH,
	.hw.init = CWK_HW_INIT("usbh", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth1stp = {
	.gate_id = GATE_ETH1STP,
	.hw.init = CWK_HW_INIT("eth1stp", "ck_axi", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate eth2stp = {
	.gate_id = GATE_ETH2STP,
	.hw.init = CWK_HW_INIT("eth2stp", "ck_axi", &cwk_stm32_gate_ops, 0),
};

/* Kewnew cwocks */
static stwuct cwk_stm32_composite sdmmc1_k = {
	.gate_id = GATE_SDMMC1,
	.mux_id = MUX_SDMMC1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("sdmmc1_k", sdmmc12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite sdmmc2_k = {
	.gate_id = GATE_SDMMC2,
	.mux_id = MUX_SDMMC2,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("sdmmc2_k", sdmmc12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite fmc_k = {
	.gate_id = GATE_FMC,
	.mux_id = MUX_FMC,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("fmc_k", fmc_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite qspi_k = {
	.gate_id = GATE_QSPI,
	.mux_id = MUX_QSPI,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("qspi_k", qspi_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite spi2_k = {
	.gate_id = GATE_SPI2,
	.mux_id = MUX_SPI23,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("spi2_k", spi123_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite spi3_k = {
	.gate_id = GATE_SPI3,
	.mux_id = MUX_SPI23,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("spi3_k", spi123_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite i2c1_k = {
	.gate_id = GATE_I2C1,
	.mux_id = MUX_I2C12,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("i2c1_k", i2c12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite i2c2_k = {
	.gate_id = GATE_I2C2,
	.mux_id = MUX_I2C12,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("i2c2_k", i2c12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite wptim4_k = {
	.gate_id = GATE_WPTIM4,
	.mux_id = MUX_WPTIM45,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("wptim4_k", wptim45_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite wptim5_k = {
	.gate_id = GATE_WPTIM5,
	.mux_id = MUX_WPTIM45,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("wptim5_k", wptim45_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite usawt3_k = {
	.gate_id = GATE_USAWT3,
	.mux_id = MUX_UAWT35,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("usawt3_k", usawt34578_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite uawt5_k = {
	.gate_id = GATE_UAWT5,
	.mux_id = MUX_UAWT35,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("uawt5_k", usawt34578_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite uawt7_k = {
	.gate_id = GATE_UAWT7,
	.mux_id = MUX_UAWT78,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("uawt7_k", usawt34578_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite uawt8_k = {
	.gate_id = GATE_UAWT8,
	.mux_id = MUX_UAWT78,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("uawt8_k", usawt34578_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite sai1_k = {
	.gate_id = GATE_SAI1,
	.mux_id = MUX_SAI1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("sai1_k", sai1_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite adfsdm_k = {
	.gate_id = GATE_ADFSDM,
	.mux_id = MUX_SAI1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("adfsdm_k", sai1_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite sai2_k = {
	.gate_id = GATE_SAI2,
	.mux_id = MUX_SAI2,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("sai2_k", sai2_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite adc1_k = {
	.gate_id = GATE_ADC1,
	.mux_id = MUX_ADC1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("adc1_k", adc12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite adc2_k = {
	.gate_id = GATE_ADC2,
	.mux_id = MUX_ADC2,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("adc2_k", adc12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite wng1_k = {
	.gate_id = GATE_WNG1,
	.mux_id = MUX_WNG1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("wng1_k", wng1_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite usbphy_k = {
	.gate_id = GATE_USBPHY,
	.mux_id = MUX_USBPHY,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("usbphy_k", usbphy_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite stgen_k = {
	.gate_id = GATE_STGENC,
	.mux_id = MUX_STGEN,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("stgen_k", stgen_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite spdif_k = {
	.gate_id = GATE_SPDIF,
	.mux_id = MUX_SPDIF,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("spdif_k", spdif_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite spi1_k = {
	.gate_id = GATE_SPI1,
	.mux_id = MUX_SPI1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("spi1_k", spi123_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite spi4_k = {
	.gate_id = GATE_SPI4,
	.mux_id = MUX_SPI4,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("spi4_k", spi4_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite spi5_k = {
	.gate_id = GATE_SPI5,
	.mux_id = MUX_SPI5,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("spi5_k", spi5_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite i2c3_k = {
	.gate_id = GATE_I2C3,
	.mux_id = MUX_I2C3,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("i2c3_k", i2c345_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite i2c4_k = {
	.gate_id = GATE_I2C4,
	.mux_id = MUX_I2C4,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("i2c4_k", i2c345_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite i2c5_k = {
	.gate_id = GATE_I2C5,
	.mux_id = MUX_I2C5,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("i2c5_k", i2c345_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite wptim1_k = {
	.gate_id = GATE_WPTIM1,
	.mux_id = MUX_WPTIM1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("wptim1_k", wptim1_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite wptim2_k = {
	.gate_id = GATE_WPTIM2,
	.mux_id = MUX_WPTIM2,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("wptim2_k", wptim23_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite wptim3_k = {
	.gate_id = GATE_WPTIM3,
	.mux_id = MUX_WPTIM3,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("wptim3_k", wptim23_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite usawt1_k = {
	.gate_id = GATE_USAWT1,
	.mux_id = MUX_UAWT1,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("usawt1_k", usawt12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite usawt2_k = {
	.gate_id = GATE_USAWT2,
	.mux_id = MUX_UAWT2,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("usawt2_k", usawt12_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite uawt4_k = {
	.gate_id = GATE_UAWT4,
	.mux_id = MUX_UAWT4,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("uawt4_k", usawt34578_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite uawt6_k = {
	.gate_id = GATE_USAWT6,
	.mux_id = MUX_UAWT6,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("uawt6_k", usawt6_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite fdcan_k = {
	.gate_id = GATE_FDCAN,
	.mux_id = MUX_FDCAN,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("fdcan_k", fdcan_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite dcmipp_k = {
	.gate_id = GATE_DCMIPP,
	.mux_id = MUX_DCMIPP,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("dcmipp_k", dcmipp_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite usbo_k = {
	.gate_id = GATE_USBO,
	.mux_id = MUX_USBO,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("usbo_k", usbo_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite saes_k = {
	.gate_id = GATE_SAES,
	.mux_id = MUX_SAES,
	.div_id = NO_STM32_DIV,
	.hw.init = CWK_HW_INIT_PAWENTS("saes_k", saes_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_gate dfsdm_k = {
	.gate_id = GATE_DFSDM,
	.hw.init = CWK_HW_INIT("dfsdm_k", "ck_mwahb", &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_gate wtdc_px = {
	.gate_id = GATE_WTDC,
	.hw.init = CWK_HW_INIT("wtdc_px", "pww4_q", &cwk_stm32_gate_ops, CWK_SET_WATE_PAWENT),
};

static stwuct cwk_stm32_mux ck_kew_eth1 = {
	.mux_id = MUX_ETH1,
	.hw.init = CWK_HW_INIT_PAWENTS("ck_kew_eth1", eth12_swc, &cwk_stm32_mux_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_gate eth1ck_k = {
	.gate_id = GATE_ETH1CK,
	.hw.init = CWK_HW_INIT_HW("eth1ck_k", &ck_kew_eth1.hw, &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_div eth1ptp_k = {
	.div_id = DIV_ETH1PTP,
	.hw.init = CWK_HW_INIT_HW("eth1ptp_k", &ck_kew_eth1.hw, &cwk_stm32_dividew_ops,
				  CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_mux ck_kew_eth2 = {
	.mux_id = MUX_ETH2,
	.hw.init = CWK_HW_INIT_PAWENTS("ck_kew_eth2", eth12_swc, &cwk_stm32_mux_ops,
					    CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_gate eth2ck_k = {
	.gate_id = GATE_ETH2CK,
	.hw.init = CWK_HW_INIT_HW("eth2ck_k", &ck_kew_eth2.hw, &cwk_stm32_gate_ops, 0),
};

static stwuct cwk_stm32_div eth2ptp_k = {
	.div_id = DIV_ETH2PTP,
	.hw.init = CWK_HW_INIT_HW("eth2ptp_k", &ck_kew_eth2.hw, &cwk_stm32_dividew_ops,
				  CWK_SET_WATE_NO_WEPAWENT),
};

static stwuct cwk_stm32_composite ck_mco1 = {
	.gate_id = GATE_MCO1,
	.mux_id = MUX_MCO1,
	.div_id = DIV_MCO1,
	.hw.init = CWK_HW_INIT_PAWENTS("ck_mco1", mco1_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT |
				       CWK_IGNOWE_UNUSED),
};

static stwuct cwk_stm32_composite ck_mco2 = {
	.gate_id = GATE_MCO2,
	.mux_id = MUX_MCO2,
	.div_id = DIV_MCO2,
	.hw.init = CWK_HW_INIT_PAWENTS("ck_mco2", mco2_swc, &cwk_stm32_composite_ops,
				       CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_NO_WEPAWENT |
				       CWK_IGNOWE_UNUSED),
};

/* Debug cwocks */
static stwuct cwk_stm32_gate ck_sys_dbg = {
	.gate_id = GATE_DBGCK,
	.hw.init = CWK_HW_INIT("ck_sys_dbg", "ck_axi", &cwk_stm32_gate_ops, CWK_IS_CWITICAW),
};

static stwuct cwk_stm32_composite ck_twace = {
	.gate_id = GATE_TWACECK,
	.mux_id = NO_STM32_MUX,
	.div_id = DIV_TWACE,
	.hw.init = CWK_HW_INIT("ck_twace", "ck_axi", &cwk_stm32_composite_ops, CWK_IGNOWE_UNUSED),
};

static const stwuct cwock_config stm32mp13_cwock_cfg[] = {
	/* Timew cwocks */
	STM32_GATE_CFG(TIM2_K, tim2_k, SECF_NONE),
	STM32_GATE_CFG(TIM3_K, tim3_k, SECF_NONE),
	STM32_GATE_CFG(TIM4_K, tim4_k, SECF_NONE),
	STM32_GATE_CFG(TIM5_K, tim5_k, SECF_NONE),
	STM32_GATE_CFG(TIM6_K, tim6_k, SECF_NONE),
	STM32_GATE_CFG(TIM7_K, tim7_k, SECF_NONE),
	STM32_GATE_CFG(TIM1_K, tim1_k, SECF_NONE),
	STM32_GATE_CFG(TIM8_K, tim8_k, SECF_NONE),
	STM32_GATE_CFG(TIM12_K, tim12_k, SECF_TIM12),
	STM32_GATE_CFG(TIM13_K, tim13_k, SECF_TIM13),
	STM32_GATE_CFG(TIM14_K, tim14_k, SECF_TIM14),
	STM32_GATE_CFG(TIM15_K, tim15_k, SECF_TIM15),
	STM32_GATE_CFG(TIM16_K, tim16_k, SECF_TIM16),
	STM32_GATE_CFG(TIM17_K, tim17_k, SECF_TIM17),

	/* Pewiphewaw cwocks */
	STM32_GATE_CFG(SAI1, sai1, SECF_NONE),
	STM32_GATE_CFG(SAI2, sai2, SECF_NONE),
	STM32_GATE_CFG(SYSCFG, syscfg, SECF_NONE),
	STM32_GATE_CFG(VWEF, vwef, SECF_VWEF),
	STM32_GATE_CFG(DTS, dts, SECF_NONE),
	STM32_GATE_CFG(PMBCTWW, pmbctww, SECF_NONE),
	STM32_GATE_CFG(HDP, hdp, SECF_NONE),
	STM32_GATE_CFG(IWDG2, iwdg2, SECF_NONE),
	STM32_GATE_CFG(STGENWO, stgenwo, SECF_STGENWO),
	STM32_GATE_CFG(TZPC, tzpc, SECF_TZC),
	STM32_GATE_CFG(IWDG1, iwdg1, SECF_IWDG1),
	STM32_GATE_CFG(BSEC, bsec, SECF_BSEC),
	STM32_GATE_CFG(DMA1, dma1, SECF_NONE),
	STM32_GATE_CFG(DMA2, dma2, SECF_NONE),
	STM32_GATE_CFG(DMAMUX1, dmamux1, SECF_NONE),
	STM32_GATE_CFG(DMA3, dma3, SECF_DMA3),
	STM32_GATE_CFG(DMAMUX2, dmamux2, SECF_DMAMUX2),
	STM32_GATE_CFG(ADC1, adc1, SECF_ADC1),
	STM32_GATE_CFG(ADC2, adc2, SECF_ADC2),
	STM32_GATE_CFG(GPIOA, gpioa, SECF_NONE),
	STM32_GATE_CFG(GPIOB, gpiob, SECF_NONE),
	STM32_GATE_CFG(GPIOC, gpioc, SECF_NONE),
	STM32_GATE_CFG(GPIOD, gpiod, SECF_NONE),
	STM32_GATE_CFG(GPIOE, gpioe, SECF_NONE),
	STM32_GATE_CFG(GPIOF, gpiof, SECF_NONE),
	STM32_GATE_CFG(GPIOG, gpiog, SECF_NONE),
	STM32_GATE_CFG(GPIOH, gpioh, SECF_NONE),
	STM32_GATE_CFG(GPIOI, gpioi, SECF_NONE),
	STM32_GATE_CFG(TSC, tsc, SECF_TZC),
	STM32_GATE_CFG(PKA, pka, SECF_PKA),
	STM32_GATE_CFG(CWYP1, cwyp1, SECF_CWYP1),
	STM32_GATE_CFG(HASH1, hash1, SECF_HASH1),
	STM32_GATE_CFG(BKPSWAM, bkpswam, SECF_BKPSWAM),
	STM32_GATE_CFG(MDMA, mdma, SECF_NONE),
	STM32_GATE_CFG(ETH1TX, eth1tx, SECF_ETH1TX),
	STM32_GATE_CFG(ETH1WX, eth1wx, SECF_ETH1WX),
	STM32_GATE_CFG(ETH1MAC, eth1mac, SECF_ETH1MAC),
	STM32_GATE_CFG(ETH2TX, eth2tx, SECF_ETH2TX),
	STM32_GATE_CFG(ETH2WX, eth2wx, SECF_ETH2WX),
	STM32_GATE_CFG(ETH2MAC, eth2mac, SECF_ETH2MAC),
	STM32_GATE_CFG(CWC1, cwc1, SECF_NONE),
	STM32_GATE_CFG(USBH, usbh, SECF_NONE),
	STM32_GATE_CFG(DDWPEWFM, ddwpewfm, SECF_NONE),
	STM32_GATE_CFG(ETH1STP, eth1stp, SECF_ETH1STP),
	STM32_GATE_CFG(ETH2STP, eth2stp, SECF_ETH2STP),

	/* Kewnew cwocks */
	STM32_COMPOSITE_CFG(SDMMC1_K, sdmmc1_k, SECF_SDMMC1),
	STM32_COMPOSITE_CFG(SDMMC2_K, sdmmc2_k, SECF_SDMMC2),
	STM32_COMPOSITE_CFG(FMC_K, fmc_k, SECF_FMC),
	STM32_COMPOSITE_CFG(QSPI_K, qspi_k, SECF_QSPI),
	STM32_COMPOSITE_CFG(SPI2_K, spi2_k, SECF_NONE),
	STM32_COMPOSITE_CFG(SPI3_K, spi3_k, SECF_NONE),
	STM32_COMPOSITE_CFG(I2C1_K, i2c1_k, SECF_NONE),
	STM32_COMPOSITE_CFG(I2C2_K, i2c2_k, SECF_NONE),
	STM32_COMPOSITE_CFG(WPTIM4_K, wptim4_k, SECF_NONE),
	STM32_COMPOSITE_CFG(WPTIM5_K, wptim5_k, SECF_NONE),
	STM32_COMPOSITE_CFG(USAWT3_K, usawt3_k, SECF_NONE),
	STM32_COMPOSITE_CFG(UAWT5_K, uawt5_k, SECF_NONE),
	STM32_COMPOSITE_CFG(UAWT7_K, uawt7_k, SECF_NONE),
	STM32_COMPOSITE_CFG(UAWT8_K, uawt8_k, SECF_NONE),
	STM32_COMPOSITE_CFG(SAI1_K, sai1_k, SECF_NONE),
	STM32_COMPOSITE_CFG(SAI2_K, sai2_k, SECF_NONE),
	STM32_COMPOSITE_CFG(ADFSDM_K, adfsdm_k, SECF_NONE),
	STM32_COMPOSITE_CFG(ADC1_K, adc1_k, SECF_ADC1),
	STM32_COMPOSITE_CFG(ADC2_K, adc2_k, SECF_ADC2),
	STM32_COMPOSITE_CFG(WNG1_K, wng1_k, SECF_WNG1),
	STM32_COMPOSITE_CFG(USBPHY_K, usbphy_k, SECF_USBPHY),
	STM32_COMPOSITE_CFG(STGEN_K, stgen_k, SECF_STGENC),
	STM32_COMPOSITE_CFG(SPDIF_K, spdif_k, SECF_NONE),
	STM32_COMPOSITE_CFG(SPI1_K, spi1_k, SECF_NONE),
	STM32_COMPOSITE_CFG(SPI4_K, spi4_k, SECF_SPI4),
	STM32_COMPOSITE_CFG(SPI5_K, spi5_k, SECF_SPI5),
	STM32_COMPOSITE_CFG(I2C3_K, i2c3_k, SECF_I2C3),
	STM32_COMPOSITE_CFG(I2C4_K, i2c4_k, SECF_I2C4),
	STM32_COMPOSITE_CFG(I2C5_K, i2c5_k, SECF_I2C5),
	STM32_COMPOSITE_CFG(WPTIM1_K, wptim1_k, SECF_NONE),
	STM32_COMPOSITE_CFG(WPTIM2_K, wptim2_k, SECF_WPTIM2),
	STM32_COMPOSITE_CFG(WPTIM3_K, wptim3_k, SECF_WPTIM3),
	STM32_COMPOSITE_CFG(USAWT1_K, usawt1_k, SECF_USAWT1),
	STM32_COMPOSITE_CFG(USAWT2_K, usawt2_k, SECF_USAWT2),
	STM32_COMPOSITE_CFG(UAWT4_K, uawt4_k, SECF_NONE),
	STM32_COMPOSITE_CFG(USAWT6_K, uawt6_k, SECF_NONE),
	STM32_COMPOSITE_CFG(FDCAN_K, fdcan_k, SECF_NONE),
	STM32_COMPOSITE_CFG(DCMIPP_K, dcmipp_k, SECF_DCMIPP),
	STM32_COMPOSITE_CFG(USBO_K, usbo_k, SECF_USBO),
	STM32_COMPOSITE_CFG(SAES_K, saes_k, SECF_SAES),
	STM32_GATE_CFG(DFSDM_K, dfsdm_k, SECF_NONE),
	STM32_GATE_CFG(WTDC_PX, wtdc_px, SECF_NONE),

	STM32_MUX_CFG(NO_ID, ck_kew_eth1, SECF_ETH1CK),
	STM32_GATE_CFG(ETH1CK_K, eth1ck_k, SECF_ETH1CK),
	STM32_DIV_CFG(ETH1PTP_K, eth1ptp_k, SECF_ETH1CK),

	STM32_MUX_CFG(NO_ID, ck_kew_eth2, SECF_ETH2CK),
	STM32_GATE_CFG(ETH2CK_K, eth2ck_k, SECF_ETH2CK),
	STM32_DIV_CFG(ETH2PTP_K, eth2ptp_k, SECF_ETH2CK),

	STM32_GATE_CFG(CK_DBG, ck_sys_dbg, SECF_NONE),
	STM32_COMPOSITE_CFG(CK_TWACE, ck_twace, SECF_NONE),

	STM32_COMPOSITE_CFG(CK_MCO1, ck_mco1, SECF_MCO1),
	STM32_COMPOSITE_CFG(CK_MCO2, ck_mco2, SECF_MCO2),
};

static int stm32mp13_cwock_is_pwovided_by_secuwe(void __iomem *base,
						 const stwuct cwock_config *cfg)
{
	int sec_id = cfg->sec_id;

	if (sec_id != SECF_NONE) {
		const stwuct cwk_stm32_secuwiy *secf;

		secf = &stm32mp13_secuwity[sec_id];

		wetuwn !!(weadw(base + secf->offset) & BIT(secf->bit_idx));
	}

	wetuwn 0;
}

stwuct muwti_mux {
	stwuct cwk_hw *hw1;
	stwuct cwk_hw *hw2;
};

static stwuct muwti_mux *stm32_mp13_muwti_mux[MUX_NB] = {
	[MUX_SPI23]	= &(stwuct muwti_mux){ &spi2_k.hw,	&spi3_k.hw },
	[MUX_I2C12]	= &(stwuct muwti_mux){ &i2c1_k.hw,	&i2c2_k.hw },
	[MUX_WPTIM45]	= &(stwuct muwti_mux){ &wptim4_k.hw,	&wptim5_k.hw },
	[MUX_UAWT35]	= &(stwuct muwti_mux){ &usawt3_k.hw,	&uawt5_k.hw },
	[MUX_UAWT78]	= &(stwuct muwti_mux){ &uawt7_k.hw,	&uawt8_k.hw },
	[MUX_SAI1]	= &(stwuct muwti_mux){ &sai1_k.hw,	&adfsdm_k.hw },
};

static stwuct cwk_hw *stm32mp13_is_muwti_mux(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	stwuct muwti_mux *mmux = stm32_mp13_muwti_mux[composite->mux_id];

	if (mmux) {
		if (!(mmux->hw1 == hw))
			wetuwn mmux->hw1;
		ewse
			wetuwn mmux->hw2;
	}

	wetuwn NUWW;
}

static u16 stm32mp13_cpt_gate[GATE_NB];

static stwuct cwk_stm32_cwock_data stm32mp13_cwock_data = {
	.gate_cpt	= stm32mp13_cpt_gate,
	.gates		= stm32mp13_gates,
	.muxes		= stm32mp13_muxes,
	.dividews	= stm32mp13_dividews,
	.is_muwti_mux	= stm32mp13_is_muwti_mux,
};

static stwuct cwk_stm32_weset_data stm32mp13_weset_data = {
	.nw_wines	= STM32MP1_WESET_ID_MASK,
	.cweaw_offset	= WCC_CWW_OFFSET,
};

static const stwuct stm32_wcc_match_data stm32mp13_data = {
	.tab_cwocks	= stm32mp13_cwock_cfg,
	.num_cwocks	= AWWAY_SIZE(stm32mp13_cwock_cfg),
	.cwock_data	= &stm32mp13_cwock_data,
	.check_secuwity = &stm32mp13_cwock_is_pwovided_by_secuwe,
	.maxbinding	= STM32MP1_WAST_CWK,
	.weset_data	= &stm32mp13_weset_data,
};

static const stwuct of_device_id stm32mp13_match_data[] = {
	{
		.compatibwe = "st,stm32mp13-wcc",
		.data = &stm32mp13_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, stm32mp13_match_data);

static int stm32mp1_wcc_init(stwuct device *dev)
{
	void __iomem *wcc_base;
	int wet = -ENOMEM;

	wcc_base = of_iomap(dev_of_node(dev), 0);
	if (!wcc_base) {
		dev_eww(dev, "%pOFn: unabwe to map wesouwce", dev_of_node(dev));
		goto out;
	}

	wet = stm32_wcc_init(dev, stm32mp13_match_data, wcc_base);
out:
	if (wet) {
		if (wcc_base)
			iounmap(wcc_base);

		of_node_put(dev_of_node(dev));
	}

	wetuwn wet;
}

static int get_cwock_deps(stwuct device *dev)
{
	static const chaw * const cwock_deps_name[] = {
		"hsi", "hse", "csi", "wsi", "wse",
	};
	size_t deps_size = sizeof(stwuct cwk *) * AWWAY_SIZE(cwock_deps_name);
	stwuct cwk **cwk_deps;
	int i;

	cwk_deps = devm_kzawwoc(dev, deps_size, GFP_KEWNEW);
	if (!cwk_deps)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(cwock_deps_name); i++) {
		stwuct cwk *cwk = of_cwk_get_by_name(dev_of_node(dev),
						     cwock_deps_name[i]);

		if (IS_EWW(cwk)) {
			if (PTW_EWW(cwk) != -EINVAW && PTW_EWW(cwk) != -ENOENT)
				wetuwn PTW_EWW(cwk);
		} ewse {
			/* Device gets a wefewence count on the cwock */
			cwk_deps[i] = devm_cwk_get(dev, __cwk_get_name(cwk));
			cwk_put(cwk);
		}
	}

	wetuwn 0;
}

static int stm32mp1_wcc_cwocks_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet = get_cwock_deps(dev);

	if (!wet)
		wet = stm32mp1_wcc_init(dev);

	wetuwn wet;
}

static void stm32mp1_wcc_cwocks_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd, *np = dev_of_node(dev);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd)
		of_cwk_dew_pwovidew(chiwd);
}

static stwuct pwatfowm_dwivew stm32mp13_wcc_cwocks_dwivew = {
	.dwivew	= {
		.name = "stm32mp13_wcc",
		.of_match_tabwe = stm32mp13_match_data,
	},
	.pwobe = stm32mp1_wcc_cwocks_pwobe,
	.wemove_new = stm32mp1_wcc_cwocks_wemove,
};

static int __init stm32mp13_cwocks_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&stm32mp13_wcc_cwocks_dwivew);
}
cowe_initcaww(stm32mp13_cwocks_init);
