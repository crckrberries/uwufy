// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI DA830/OMAP W137 chip specific setup
 *
 * Authow: Mawk A. Gweew <mgweew@mvista.com>
 *
 * 2009 (c) MontaVista Softwawe, Inc.
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/davinci.h>
#incwude <winux/gpio.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/iwq-davinci-cp-intc.h>

#incwude <cwocksouwce/timew-davinci.h>

#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "cputype.h"
#incwude "da8xx.h"
#incwude "iwqs.h"
#incwude "mux.h"

/* Offsets of the 8 compawe wegistews on the da830 */
#define DA830_CMP12_0		0x60
#define DA830_CMP12_1		0x64
#define DA830_CMP12_2		0x68
#define DA830_CMP12_3		0x6c
#define DA830_CMP12_4		0x70
#define DA830_CMP12_5		0x74
#define DA830_CMP12_6		0x78
#define DA830_CMP12_7		0x7c

#define DA830_WEF_FWEQ		24000000

/*
 * Device specific mux setup
 *
 *	     soc      descwiption	mux    mode    mode   mux	dbg
 *					weg   offset   mask   mode
 */
static const stwuct mux_config da830_pins[] = {
#ifdef CONFIG_DAVINCI_MUX
	MUX_CFG(DA830, GPIO7_14,	0,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, WTCK,		0,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_15,	0,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMU_0,		0,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMB_SDCKE,	0,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_CWK_GWUE,	0,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_CWK,		0,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, NEMB_CS_0,	0,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMB_CAS,	0,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMB_WAS,	0,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMB_WE,		0,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_BA_1,	1,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_BA_0,	1,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_0,		1,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_1,		1,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_2,		1,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_3,		1,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_4,		1,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_5,		1,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, GPIO7_0,		1,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_1,		1,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_2,		1,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_3,		1,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_4,		1,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_5,		1,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_6,		1,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_7,		1,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMB_A_6,		2,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_7,		2,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_8,		2,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_9,		2,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_10,	2,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_11,	2,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_A_12,	2,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_31,	2,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, GPIO7_8,		2,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_9,		2,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_10,	2,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_11,	2,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_12,	2,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO7_13,	2,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_13,	2,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMB_D_30,	3,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_29,	3,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_28,	3,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_27,	3,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_26,	3,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_25,	3,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_24,	3,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_23,	3,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_22,	4,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_21,	4,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_20,	4,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_19,	4,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_18,	4,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_17,	4,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_16,	4,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMB_WE_DQM_3,	4,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMB_WE_DQM_2,	5,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_0,		5,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_1,		5,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_2,		5,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_3,		5,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_4,		5,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_5,		5,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_6,		5,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, GPIO6_0,		5,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_1,		5,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_2,		5,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_3,		5,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_4,		5,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_5,		5,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_6,		5,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMB_D_7,		6,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_8,		6,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_9,		6,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_10,	6,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_11,	6,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_12,	6,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_13,	6,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMB_D_14,	6,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, GPIO6_7,		6,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_8,		6,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_9,		6,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_10,	6,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_11,	6,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_12,	6,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_13,	6,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO6_14,	6,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMB_D_15,	7,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMB_WE_DQM_1,	7,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMB_WE_DQM_0,	7,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, SPI0_SOMI_0,	7,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, SPI0_SIMO_0,	7,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, SPI0_CWK,	7,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, NSPI0_ENA,	7,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, NSPI0_SCS_0,	7,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, EQEP0I,		7,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, EQEP0S,		7,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, EQEP1I,		7,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, NUAWT0_CTS,	7,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, NUAWT0_WTS,	7,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, EQEP0A,		7,	24,	0xf,	4,	fawse)
	MUX_CFG(DA830, EQEP0B,		7,	28,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO6_15,	7,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_14,	7,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_15,	7,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_0,		7,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_1,		7,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_2,		7,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_3,		7,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_4,		7,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, SPI1_SOMI_0,	8,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, SPI1_SIMO_0,	8,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, SPI1_CWK,	8,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, UAWT0_WXD,	8,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, UAWT0_TXD,	8,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_10,		8,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_11,		8,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, NSPI1_ENA,	8,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, I2C1_SCW,	8,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, I2C1_SDA,	8,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, EQEP1S,		8,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, I2C0_SDA,	8,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, I2C0_SCW,	8,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, UAWT2_WXD,	8,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, TM64P0_IN12,	8,	12,	0xf,	4,	fawse)
	MUX_CFG(DA830, TM64P0_OUT12,	8,	16,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO5_5,		8,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_6,		8,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_7,		8,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_8,		8,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_9,		8,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_10,	8,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_11,	8,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO5_12,	8,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, NSPI1_SCS_0,	9,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, USB0_DWVVBUS,	9,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, AHCWKX0,		9,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, ACWKX0,		9,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, AFSX0,		9,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, AHCWKW0,		9,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, ACWKW0,		9,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, AFSW0,		9,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, UAWT2_TXD,	9,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, AHCWKX2,		9,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, ECAP0_APWM0,	9,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, WMII_MHZ_50_CWK,	9,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, ECAP1_APWM1,	9,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, USB_WEFCWKIN,	9,	8,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO5_13,	9,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_15,	9,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_11,	9,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_12,	9,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_13,	9,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_14,	9,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_15,	9,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_12,	9,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, AMUTE0,		10,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_0,		10,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_1,		10,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_2,		10,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_3,		10,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_4,		10,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_5,		10,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_6,		10,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, WMII_TXD_0,	10,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, WMII_TXD_1,	10,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, WMII_TXEN,	10,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, WMII_CWS_DV,	10,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, WMII_WXD_0,	10,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, WMII_WXD_1,	10,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, WMII_WXEW,	10,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, AFSW2,		10,	4,	0xf,	4,	fawse)
	MUX_CFG(DA830, ACWKX2,		10,	8,	0xf,	4,	fawse)
	MUX_CFG(DA830, AXW2_3,		10,	12,	0xf,	4,	fawse)
	MUX_CFG(DA830, AXW2_2,		10,	16,	0xf,	4,	fawse)
	MUX_CFG(DA830, AXW2_1,		10,	20,	0xf,	4,	fawse)
	MUX_CFG(DA830, AFSX2,		10,	24,	0xf,	4,	fawse)
	MUX_CFG(DA830, ACWKW2,		10,	28,	0xf,	4,	fawse)
	MUX_CFG(DA830, NWESETOUT,	10,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_0,		10,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_1,		10,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_2,		10,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_3,		10,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_4,		10,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_5,		10,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_6,		10,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, AXW0_7,		11,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_8,		11,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, UAWT1_WXD,	11,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, UAWT1_TXD,	11,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW0_11,		11,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, AHCWKX1,		11,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, ACWKX1,		11,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, AFSX1,		11,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, MDIO_CWK,	11,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, MDIO_D,		11,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, AXW0_9,		11,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, AXW0_10,		11,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, EPWM0B,		11,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, EPWM0A,		11,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, EPWMSYNCI,	11,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, AXW2_0,		11,	16,	0xf,	4,	fawse)
	MUX_CFG(DA830, EPWMSYNC0,	11,	28,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO3_7,		11,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_8,		11,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_9,		11,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_10,	11,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_11,	11,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_14,	11,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO3_15,	11,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_10,	11,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, AHCWKW1,		12,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, ACWKW1,		12,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, AFSW1,		12,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, AMUTE1,		12,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_0,		12,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_1,		12,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_2,		12,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_3,		12,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, ECAP2_APWM2,	12,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, EHWPWMGWUETZ,	12,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, EQEP1A,		12,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, GPIO4_11,	12,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_12,	12,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_13,	12,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_14,	12,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_0,		12,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_1,		12,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_2,		12,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_3,		12,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, AXW1_4,		13,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_5,		13,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_6,		13,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_7,		13,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_8,		13,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, AXW1_9,		13,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_0,		13,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_1,		13,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, EQEP1B,		13,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, EPWM2B,		13,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, EPWM2A,		13,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, EPWM1B,		13,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, EPWM1A,		13,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_0,	13,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_1,	13,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_0,	13,	24,	0xf,	4,	fawse)
	MUX_CFG(DA830, UHPI_HD_1,	13,	28,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO4_4,		13,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_5,		13,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_6,		13,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_7,		13,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_8,		13,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO4_9,		13,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_0,		13,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_1,		13,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMA_D_2,		14,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_3,		14,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_4,		14,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_5,		14,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_6,		14,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_7,		14,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_8,		14,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_9,		14,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_2,	14,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_3,	14,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_4,	14,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_5,	14,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_6,	14,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_DAT_7,	14,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_8,	14,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_9,	14,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_2,	14,	0,	0xf,	4,	fawse)
	MUX_CFG(DA830, UHPI_HD_3,	14,	4,	0xf,	4,	fawse)
	MUX_CFG(DA830, UHPI_HD_4,	14,	8,	0xf,	4,	fawse)
	MUX_CFG(DA830, UHPI_HD_5,	14,	12,	0xf,	4,	fawse)
	MUX_CFG(DA830, UHPI_HD_6,	14,	16,	0xf,	4,	fawse)
	MUX_CFG(DA830, UHPI_HD_7,	14,	20,	0xf,	4,	fawse)
	MUX_CFG(DA830, WCD_D_8,		14,	24,	0xf,	4,	fawse)
	MUX_CFG(DA830, WCD_D_9,		14,	28,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO0_2,		14,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_3,		14,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_4,		14,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_5,		14,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_6,		14,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_7,		14,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_8,		14,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_9,		14,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMA_D_10,	15,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_11,	15,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_12,	15,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_13,	15,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_14,	15,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_D_15,	15,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_0,		15,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_1,		15,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, UHPI_HD_10,	15,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_11,	15,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_12,	15,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_13,	15,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_14,	15,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HD_15,	15,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_7,		15,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, MMCSD_CWK,	15,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_10,	15,	0,	0xf,	4,	fawse)
	MUX_CFG(DA830, WCD_D_11,	15,	4,	0xf,	4,	fawse)
	MUX_CFG(DA830, WCD_D_12,	15,	8,	0xf,	4,	fawse)
	MUX_CFG(DA830, WCD_D_13,	15,	12,	0xf,	4,	fawse)
	MUX_CFG(DA830, WCD_D_14,	15,	16,	0xf,	4,	fawse)
	MUX_CFG(DA830, WCD_D_15,	15,	20,	0xf,	4,	fawse)
	MUX_CFG(DA830, UHPI_HCNTW0,	15,	28,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO0_10,	15,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_11,	15,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_12,	15,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_13,	15,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_14,	15,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO0_15,	15,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_0,		15,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_1,		15,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMA_A_2,		16,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_3,		16,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_4,		16,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_5,		16,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_6,		16,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_7,		16,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_8,		16,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_9,		16,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, MMCSD_CMD,	16,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_6,		16,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_3,		16,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_2,		16,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_1,		16,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_0,		16,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_PCWK,	16,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_HSYNC,	16,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HCNTW1,	16,	0,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO1_2,		16,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_3,		16,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_4,		16,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_5,		16,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_6,		16,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_7,		16,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_8,		16,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_9,		16,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMA_A_10,	17,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_11,	17,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_A_12,	17,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_BA_1,	17,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_BA_0,	17,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_CWK,		17,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, EMA_SDCKE,	17,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_CAS,	17,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, WCD_VSYNC,	17,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, NWCD_AC_ENB_CS,	17,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_MCWK,	17,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_5,		17,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, WCD_D_4,		17,	16,	0xf,	2,	fawse)
	MUX_CFG(DA830, OBSCWK,		17,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, NEMA_CS_4,	17,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HHWIW,	17,	12,	0xf,	4,	fawse)
	MUX_CFG(DA830, AHCWKW2,		17,	20,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO1_10,	17,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_11,	17,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_12,	17,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_13,	17,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_14,	17,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO1_15,	17,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_0,		17,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_1,		17,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, NEMA_WAS,	18,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_WE,		18,	4,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_CS_0,	18,	8,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_CS_2,	18,	12,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_CS_3,	18,	16,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_OE,		18,	20,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_WE_DQM_1,	18,	24,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_WE_DQM_0,	18,	28,	0xf,	1,	fawse)
	MUX_CFG(DA830, NEMA_CS_5,	18,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, UHPI_HWNW,	18,	4,	0xf,	2,	fawse)
	MUX_CFG(DA830, NUHPI_HAS,	18,	8,	0xf,	2,	fawse)
	MUX_CFG(DA830, NUHPI_HCS,	18,	12,	0xf,	2,	fawse)
	MUX_CFG(DA830, NUHPI_HDS1,	18,	20,	0xf,	2,	fawse)
	MUX_CFG(DA830, NUHPI_HDS2,	18,	24,	0xf,	2,	fawse)
	MUX_CFG(DA830, NUHPI_HINT,	18,	28,	0xf,	2,	fawse)
	MUX_CFG(DA830, AXW0_12,		18,	4,	0xf,	4,	fawse)
	MUX_CFG(DA830, AMUTE2,		18,	16,	0xf,	4,	fawse)
	MUX_CFG(DA830, AXW0_13,		18,	20,	0xf,	4,	fawse)
	MUX_CFG(DA830, AXW0_14,		18,	24,	0xf,	4,	fawse)
	MUX_CFG(DA830, AXW0_15,		18,	28,	0xf,	4,	fawse)
	MUX_CFG(DA830, GPIO2_2,		18,	0,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_3,		18,	4,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_4,		18,	8,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_5,		18,	12,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_6,		18,	16,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_7,		18,	20,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_8,		18,	24,	0xf,	8,	fawse)
	MUX_CFG(DA830, GPIO2_9,		18,	28,	0xf,	8,	fawse)
	MUX_CFG(DA830, EMA_WAIT_0,	19,	0,	0xf,	1,	fawse)
	MUX_CFG(DA830, NUHPI_HWDY,	19,	0,	0xf,	2,	fawse)
	MUX_CFG(DA830, GPIO2_10,	19,	0,	0xf,	8,	fawse)
#endif
};

static stwuct map_desc da830_io_desc[] = {
	{
		.viwtuaw	= IO_VIWT,
		.pfn		= __phys_to_pfn(IO_PHYS),
		.wength		= IO_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= DA8XX_CP_INTC_VIWT,
		.pfn		= __phys_to_pfn(DA8XX_CP_INTC_BASE),
		.wength		= DA8XX_CP_INTC_SIZE,
		.type		= MT_DEVICE
	},
};

/* Contents of JTAG ID wegistew used to identify exact cpu type */
static stwuct davinci_id da830_ids[] = {
	{
		.vawiant	= 0x0,
		.pawt_no	= 0xb7df,
		.manufactuwew	= 0x017,	/* 0x02f >> 1 */
		.cpu_id		= DAVINCI_CPU_ID_DA830,
		.name		= "da830/omap-w137 wev1.0",
	},
	{
		.vawiant	= 0x8,
		.pawt_no	= 0xb7df,
		.manufactuwew	= 0x017,
		.cpu_id		= DAVINCI_CPU_ID_DA830,
		.name		= "da830/omap-w137 wev1.1",
	},
	{
		.vawiant	= 0x9,
		.pawt_no	= 0xb7df,
		.manufactuwew	= 0x017,
		.cpu_id		= DAVINCI_CPU_ID_DA830,
		.name		= "da830/omap-w137 wev2.0",
	},
};

static const stwuct davinci_soc_info davinci_soc_info_da830 = {
	.io_desc		= da830_io_desc,
	.io_desc_num		= AWWAY_SIZE(da830_io_desc),
	.jtag_id_weg		= DA8XX_SYSCFG0_BASE + DA8XX_JTAG_ID_WEG,
	.ids			= da830_ids,
	.ids_num		= AWWAY_SIZE(da830_ids),
	.pinmux_base		= DA8XX_SYSCFG0_BASE + 0x120,
	.pinmux_pins		= da830_pins,
	.pinmux_pins_num	= AWWAY_SIZE(da830_pins),
};

void __init da830_init(void)
{
	davinci_common_init(&davinci_soc_info_da830);

	da8xx_syscfg0_base = iowemap(DA8XX_SYSCFG0_BASE, SZ_4K);
	WAWN(!da8xx_syscfg0_base, "Unabwe to map syscfg0 moduwe");
}
