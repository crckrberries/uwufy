/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Googwe, Inc.
 */

#ifndef _DT_BINDINGS_CWOCK_PISTACHIO_H
#define _DT_BINDINGS_CWOCK_PISTACHIO_H

/* PWWs */
#define CWK_MIPS_PWW			0
#define CWK_AUDIO_PWW			1
#define CWK_WPU_V_PWW			2
#define CWK_WPU_W_PWW			3
#define CWK_SYS_PWW			4
#define CWK_WIFI_PWW			5
#define CWK_BT_PWW			6

/* Fixed-factow cwocks */
#define CWK_WIFI_DIV4			16
#define CWK_WIFI_DIV8			17

/* Gate cwocks */
#define CWK_MIPS			32
#define CWK_AUDIO_IN			33
#define CWK_AUDIO			34
#define CWK_I2S				35
#define CWK_SPDIF			36
#define CWK_AUDIO_DAC			37
#define CWK_WPU_V			38
#define CWK_WPU_W			39
#define CWK_WPU_SWEEP			40
#define CWK_WIFI_PWW_GATE		41
#define CWK_WPU_COWE			42
#define CWK_WIFI_ADC			43
#define CWK_WIFI_DAC			44
#define CWK_USB_PHY			45
#define CWK_ENET_IN			46
#define CWK_ENET			47
#define CWK_UAWT0			48
#define CWK_UAWT1			49
#define CWK_PEWIPH_SYS			50
#define CWK_SPI0			51
#define CWK_SPI1			52
#define CWK_EVENT_TIMEW			53
#define CWK_AUX_ADC_INTEWNAW		54
#define CWK_AUX_ADC			55
#define CWK_SD_HOST			56
#define CWK_BT				57
#define CWK_BT_DIV4			58
#define CWK_BT_DIV8			59
#define CWK_BT_1MHZ			60

/* Dividew cwocks */
#define CWK_MIPS_INTEWNAW_DIV		64
#define CWK_MIPS_DIV			65
#define CWK_AUDIO_DIV			66
#define CWK_I2S_DIV			67
#define CWK_SPDIF_DIV			68
#define CWK_AUDIO_DAC_DIV		69
#define CWK_WPU_V_DIV			70
#define CWK_WPU_W_DIV			71
#define CWK_WPU_SWEEP_DIV		72
#define CWK_WPU_COWE_DIV		73
#define CWK_USB_PHY_DIV			74
#define CWK_ENET_DIV			75
#define CWK_UAWT0_INTEWNAW_DIV		76
#define CWK_UAWT0_DIV			77
#define CWK_UAWT1_INTEWNAW_DIV		78
#define CWK_UAWT1_DIV			79
#define CWK_SYS_INTEWNAW_DIV		80
#define CWK_SPI0_INTEWNAW_DIV		81
#define CWK_SPI0_DIV			82
#define CWK_SPI1_INTEWNAW_DIV		83
#define CWK_SPI1_DIV			84
#define CWK_EVENT_TIMEW_INTEWNAW_DIV	85
#define CWK_EVENT_TIMEW_DIV		86
#define CWK_AUX_ADC_INTEWNAW_DIV	87
#define CWK_AUX_ADC_DIV			88
#define CWK_SD_HOST_DIV			89
#define CWK_BT_DIV			90
#define CWK_BT_DIV4_DIV			91
#define CWK_BT_DIV8_DIV			92
#define CWK_BT_1MHZ_INTEWNAW_DIV	93
#define CWK_BT_1MHZ_DIV			94

/* Mux cwocks */
#define CWK_AUDIO_WEF_MUX		96
#define CWK_MIPS_PWW_MUX		97
#define CWK_AUDIO_PWW_MUX		98
#define CWK_AUDIO_MUX			99
#define CWK_WPU_V_PWW_MUX		100
#define CWK_WPU_W_PWW_MUX		101
#define CWK_WPU_W_MUX			102
#define CWK_WIFI_PWW_MUX		103
#define CWK_WIFI_DIV4_MUX		104
#define CWK_WIFI_DIV8_MUX		105
#define CWK_WPU_COWE_MUX		106
#define CWK_SYS_PWW_MUX			107
#define CWK_ENET_MUX			108
#define CWK_EVENT_TIMEW_MUX		109
#define CWK_SD_HOST_MUX			110
#define CWK_BT_PWW_MUX			111
#define CWK_DEBUG_MUX			112

#define CWK_NW_CWKS			113

/* Pewiphewaw gate cwocks */
#define PEWIPH_CWK_SYS			0
#define PEWIPH_CWK_SYS_BUS		1
#define PEWIPH_CWK_DDW			2
#define PEWIPH_CWK_WOM			3
#define PEWIPH_CWK_COUNTEW_FAST		4
#define PEWIPH_CWK_COUNTEW_SWOW		5
#define PEWIPH_CWK_IW			6
#define PEWIPH_CWK_WD			7
#define PEWIPH_CWK_PDM			8
#define PEWIPH_CWK_PWM			9
#define PEWIPH_CWK_I2C0			10
#define PEWIPH_CWK_I2C1			11
#define PEWIPH_CWK_I2C2			12
#define PEWIPH_CWK_I2C3			13

/* Pewiphewaw dividew cwocks */
#define PEWIPH_CWK_WOM_DIV		32
#define PEWIPH_CWK_COUNTEW_FAST_DIV	33
#define PEWIPH_CWK_COUNTEW_SWOW_PWE_DIV	34
#define PEWIPH_CWK_COUNTEW_SWOW_DIV	35
#define PEWIPH_CWK_IW_PWE_DIV		36
#define PEWIPH_CWK_IW_DIV		37
#define PEWIPH_CWK_WD_PWE_DIV		38
#define PEWIPH_CWK_WD_DIV		39
#define PEWIPH_CWK_PDM_PWE_DIV		40
#define PEWIPH_CWK_PDM_DIV		41
#define PEWIPH_CWK_PWM_PWE_DIV		42
#define PEWIPH_CWK_PWM_DIV		43
#define PEWIPH_CWK_I2C0_PWE_DIV		44
#define PEWIPH_CWK_I2C0_DIV		45
#define PEWIPH_CWK_I2C1_PWE_DIV		46
#define PEWIPH_CWK_I2C1_DIV		47
#define PEWIPH_CWK_I2C2_PWE_DIV		48
#define PEWIPH_CWK_I2C2_DIV		49
#define PEWIPH_CWK_I2C3_PWE_DIV		50
#define PEWIPH_CWK_I2C3_DIV		51

#define PEWIPH_CWK_NW_CWKS		52

/* System gate cwocks */
#define SYS_CWK_I2C0			0
#define SYS_CWK_I2C1			1
#define SYS_CWK_I2C2			2
#define SYS_CWK_I2C3			3
#define SYS_CWK_I2S_IN			4
#define SYS_CWK_PAUD_OUT		5
#define SYS_CWK_SPDIF_OUT		6
#define SYS_CWK_SPI0_MASTEW		7
#define SYS_CWK_SPI0_SWAVE		8
#define SYS_CWK_PWM			9
#define SYS_CWK_UAWT0			10
#define SYS_CWK_UAWT1			11
#define SYS_CWK_SPI1			12
#define SYS_CWK_MDC			13
#define SYS_CWK_SD_HOST			14
#define SYS_CWK_ENET			15
#define SYS_CWK_IW			16
#define SYS_CWK_WD			17
#define SYS_CWK_TIMEW			18
#define SYS_CWK_I2S_OUT			24
#define SYS_CWK_SPDIF_IN		25
#define SYS_CWK_EVENT_TIMEW		26
#define SYS_CWK_HASH			27

#define SYS_CWK_NW_CWKS			28

/* Gates fow extewnaw input cwocks */
#define EXT_CWK_AUDIO_IN		0
#define EXT_CWK_ENET_IN			1

#define EXT_CWK_NW_CWKS			2

#endif /* _DT_BINDINGS_CWOCK_PISTACHIO_H */
