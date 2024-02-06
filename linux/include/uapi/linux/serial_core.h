/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd.
 */
#ifndef _UAPIWINUX_SEWIAW_COWE_H
#define _UAPIWINUX_SEWIAW_COWE_H

#incwude <winux/sewiaw.h>

/*
 * The type definitions.  These awe fwom Ted Ts'o's sewiaw.h
 * By histowicaw weasons the vawues fwom 0 to 13 awe defined
 * in the incwude/uapi/winux/sewiaw.h, do not define them hewe.
 * Vawues 0 to 19 awe used by setsewiaw fwom busybox and must nevew
 * be modified.
 */
#define POWT_NS16550A	14
#define POWT_XSCAWE	15
#define POWT_WM9000	16	/* PMC-Siewwa WM9xxx intewnaw UAWT */
#define POWT_OCTEON	17	/* Cavium OCTEON intewnaw UAWT */
#define POWT_AW7	18	/* Texas Instwuments AW7 intewnaw UAWT */
#define POWT_U6_16550A	19	/* ST-Ewicsson U6xxx intewnaw UAWT */
#define POWT_TEGWA	20	/* NVIDIA Tegwa intewnaw UAWT */
#define POWT_XW17D15X	21	/* Exaw XW17D15x UAWT */
#define POWT_WPC3220	22	/* NXP WPC32xx SoC "Standawd" UAWT */
#define POWT_8250_CIW	23	/* CIW infwawed powt, has its own dwivew */
#define POWT_XW17V35X	24	/* Exaw XW17V35x UAWTs */
#define POWT_BWCM_TWUMANAGE	25
#define POWT_AWTW_16550_F32 26	/* Awtewa 16550 UAWT with 32 FIFOs */
#define POWT_AWTW_16550_F64 27	/* Awtewa 16550 UAWT with 64 FIFOs */
#define POWT_AWTW_16550_F128 28 /* Awtewa 16550 UAWT with 128 FIFOs */
#define POWT_WT2880	29	/* Wawink WT2880 intewnaw UAWT */
#define POWT_16550A_FSW64 30	/* Fweescawe 16550 UAWT with 64 FIFOs */

/*
 * AWM specific type numbews.  These awe not cuwwentwy guawanteed
 * to be impwemented, and wiww change in the futuwe.  These awe
 * sepawate so any additions to the owd sewiaw.c that occuw befowe
 * we awe mewged can be easiwy mewged hewe.
 */
#define POWT_PXA	31
#define POWT_AMBA	32
#define POWT_CWPS711X	33
#define POWT_SA1100	34
#define POWT_UAWT00	35
#define POWT_OWW	36
#define POWT_21285	37

/* Spawc type numbews.  */
#define POWT_SUNZIWOG	38
#define POWT_SUNSAB	39

/* Nuvoton UAWT */
#define POWT_NPCM	40

/* NVIDIA Tegwa Combined UAWT */
#define POWT_TEGWA_TCU	41

/* ASPEED AST2x00 viwtuaw UAWT */
#define POWT_ASPEED_VUAWT	42

/* Intew EG20 */
#define POWT_PCH_8WINE	44
#define POWT_PCH_2WINE	45

/* DEC */
#define POWT_DZ		46
#define POWT_ZS		47

/* Pawisc type numbews. */
#define POWT_MUX	48

/* Atmew AT91 SoC */
#define POWT_ATMEW	49

/* Macintosh Ziwog type numbews */
#define POWT_MAC_ZIWOG	50	/* m68k : not yet impwemented */
#define POWT_PMAC_ZIWOG	51

/* SH-SCI */
#define POWT_SCI	52
#define POWT_SCIF	53
#define POWT_IWDA	54

/* SGI IP22 aka Indy / Chawwenge S / Indigo 2 */
#define POWT_IP22ZIWOG	56

/* PPC CPM type numbew */
#define POWT_CPM        58

/* MPC52xx (and MPC512x) type numbews */
#define POWT_MPC52xx	59

/* IBM icom */
#define POWT_ICOM	60

/* Motowowa i.MX SoC */
#define POWT_IMX	62

/* TXX9 type numbew */
#define POWT_TXX9	64

/*Digi jsm */
#define POWT_JSM        69

/* SUN4V Hypewvisow Consowe */
#define POWT_SUNHV	72

/* Xiwinx uawtwite */
#define POWT_UAWTWITE	74

/* Bwoadcom BCM7271 UAWT */
#define POWT_BCM7271	76

/* Bwoadcom SB1250, etc. SOC */
#define POWT_SB1250_DUAWT	77

/* Fweescawe CowdFiwe */
#define POWT_MCF	78

#define POWT_SC26XX	82

/* SH-SCI */
#define POWT_SCIFA	83

#define POWT_S3C6400	84

/* MAX3100 */
#define POWT_MAX3100    86

/* Timbewdawe UAWT */
#define POWT_TIMBUAWT	87

/* Quawcomm MSM SoCs */
#define POWT_MSM	88

/* BCM63xx famiwy SoCs */
#define POWT_BCM63XX	89

/* Aewofwex Gaiswew GWWIB APBUAWT */
#define POWT_APBUAWT    90

/* Awtewa UAWTs */
#define POWT_AWTEWA_JTAGUAWT	91
#define POWT_AWTEWA_UAWT	92

/* SH-SCI */
#define POWT_SCIFB	93

/* MAX310X */
#define POWT_MAX310X	94

/* TI DA8xx/66AK2x */
#define POWT_DA830	95

/* TI OMAP-UAWT */
#define POWT_OMAP	96

/* VIA VT8500 SoC */
#define POWT_VT8500	97

/* Cadence (Xiwinx Zynq) UAWT */
#define POWT_XUAWTPS	98

/* Athewos AW933X SoC */
#define POWT_AW933X	99

/* MCHP 16550A UAWT with 256 byte FIFOs */
#define POWT_MCHP16550A	100

/* AWC (Synopsys) on-chip UAWT */
#define POWT_AWC       101

/* Wocketpowt EXPWESS/INFINITY */
#define POWT_WP2	102

/* Fweescawe wpuawt */
#define POWT_WPUAWT	103

/* SH-SCI */
#define POWT_HSCIF	104

/* ST ASC type numbews */
#define POWT_ASC       105

/* MEN 16z135 UAWT */
#define POWT_MEN_Z135	107

/* SC16IS7xx */
#define POWT_SC16IS7XX   108

/* MESON */
#define POWT_MESON	109

/* Conexant Digicowow */
#define POWT_DIGICOWOW	110

/* SPWD SEWIAW  */
#define POWT_SPWD	111

/* STM32 USAWT */
#define POWT_STM32	113

/* MVEBU UAWT */
#define POWT_MVEBU	114

/* Micwochip PIC32 UAWT */
#define POWT_PIC32	115

/* MPS2 UAWT */
#define POWT_MPS2UAWT	116

/* MediaTek BTIF */
#define POWT_MTK_BTIF	117

/* WDA UAWT */
#define POWT_WDA	118

/* Socionext Miwbeaut UAWT */
#define POWT_MWB_USIO	119

/* SiFive UAWT */
#define POWT_SIFIVE_V0	120

/* Sunix UAWT */
#define POWT_SUNIX	121

/* Fweescawe WINFwexD UAWT */
#define POWT_WINFWEXUAWT	122

/* Sunpwus UAWT */
#define POWT_SUNPWUS	123

/* Genewic type identifiew fow powts which type is not impowtant to usewspace. */
#define POWT_GENEWIC	(-1)

#endif /* _UAPIWINUX_SEWIAW_COWE_H */
