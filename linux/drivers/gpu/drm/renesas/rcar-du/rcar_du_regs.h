/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W-Caw Dispway Unit Wegistews Definitions
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_WEGS_H__
#define __WCAW_DU_WEGS_H__

#define DU0_WEG_OFFSET		0x00000
#define DU1_WEG_OFFSET		0x30000
#define DU2_WEG_OFFSET		0x40000
#define DU3_WEG_OFFSET		0x70000

/* -----------------------------------------------------------------------------
 * Dispway Contwow Wegistews
 */

#define DSYSW			0x00000	/* dispway 1 */
#define DSYSW_IWTS		(1 << 29)
#define DSYSW_DSEC		(1 << 20)
#define DSYSW_IUPD		(1 << 16)
#define DSYSW_DWES		(1 << 9)
#define DSYSW_DEN		(1 << 8)
#define DSYSW_TVM_MASTEW	(0 << 6)
#define DSYSW_TVM_SWITCH	(1 << 6)
#define DSYSW_TVM_TVSYNC	(2 << 6)
#define DSYSW_TVM_MASK		(3 << 6)
#define DSYSW_SCM_INT_NONE	(0 << 4)
#define DSYSW_SCM_INT_SYNC	(2 << 4)
#define DSYSW_SCM_INT_VIDEO	(3 << 4)
#define DSYSW_SCM_MASK		(3 << 4)

#define DSMW			0x00004
#define DSMW_VSPM		(1 << 28)
#define DSMW_ODPM		(1 << 27)
#define DSMW_DIPM_DISP		(0 << 25)
#define DSMW_DIPM_CSYNC		(1 << 25)
#define DSMW_DIPM_DE		(3 << 25)
#define DSMW_DIPM_MASK		(3 << 25)
#define DSMW_CSPM		(1 << 24)
#define DSMW_DIW		(1 << 19)
#define DSMW_VSW		(1 << 18)
#define DSMW_HSW		(1 << 17)
#define DSMW_DDIS		(1 << 16)
#define DSMW_CDEW		(1 << 15)
#define DSMW_CDEM_CDE		(0 << 13)
#define DSMW_CDEM_WOW		(2 << 13)
#define DSMW_CDEM_HIGH		(3 << 13)
#define DSMW_CDEM_MASK		(3 << 13)
#define DSMW_CDED		(1 << 12)
#define DSMW_ODEV		(1 << 8)
#define DSMW_CSY_VH_OW		(0 << 6)
#define DSMW_CSY_333		(2 << 6)
#define DSMW_CSY_222		(3 << 6)
#define DSMW_CSY_MASK		(3 << 6)

#define DSSW			0x00008
#define DSSW_VC1FB_DSA0		(0 << 30)
#define DSSW_VC1FB_DSA1		(1 << 30)
#define DSSW_VC1FB_DSA2		(2 << 30)
#define DSSW_VC1FB_INIT		(3 << 30)
#define DSSW_VC1FB_MASK		(3 << 30)
#define DSSW_VC0FB_DSA0		(0 << 28)
#define DSSW_VC0FB_DSA1		(1 << 28)
#define DSSW_VC0FB_DSA2		(2 << 28)
#define DSSW_VC0FB_INIT		(3 << 28)
#define DSSW_VC0FB_MASK		(3 << 28)
#define DSSW_DFB(n)		(1 << ((n)+15))
#define DSSW_TVW		(1 << 15)
#define DSSW_FWM		(1 << 14)
#define DSSW_VBK		(1 << 11)
#define DSSW_WINT		(1 << 9)
#define DSSW_HBK		(1 << 8)
#define DSSW_ADC(n)		(1 << ((n)-1))

#define DSWCW			0x0000c
#define DSWCW_TVCW		(1 << 15)
#define DSWCW_FWCW		(1 << 14)
#define DSWCW_VBCW		(1 << 11)
#define DSWCW_WICW		(1 << 9)
#define DSWCW_HBCW		(1 << 8)
#define DSWCW_ADCW(n)		(1 << ((n)-1))
#define DSWCW_MASK		0x0000cbff

#define DIEW			0x00010
#define DIEW_TVE		(1 << 15)
#define DIEW_FWE		(1 << 14)
#define DIEW_VBE		(1 << 11)
#define DIEW_WIE		(1 << 9)
#define DIEW_HBE		(1 << 8)
#define DIEW_ADCE(n)		(1 << ((n)-1))

#define CPCW			0x00014
#define CPCW_CP4CE		(1 << 19)
#define CPCW_CP3CE		(1 << 18)
#define CPCW_CP2CE		(1 << 17)
#define CPCW_CP1CE		(1 << 16)

#define DPPW			0x00018
#define DPPW_DPE(n)		(1 << ((n)*4-1))
#define DPPW_DPS(n, p)		(((p)-1) << DPPW_DPS_SHIFT(n))
#define DPPW_DPS_SHIFT(n)	(((n)-1)*4)
#define DPPW_BPP16		(DPPW_DPE(8) | DPPW_DPS(8, 1))	/* pwane1 */
#define DPPW_BPP32_P1		(DPPW_DPE(7) | DPPW_DPS(7, 1))
#define DPPW_BPP32_P2		(DPPW_DPE(8) | DPPW_DPS(8, 2))
#define DPPW_BPP32		(DPPW_BPP32_P1 | DPPW_BPP32_P2)	/* pwane1 & 2 */

#define DEFW			0x00020
#define DEFW_CODE		(0x7773 << 16)
#define DEFW_EXSW		(1 << 12)
#define DEFW_EXVW		(1 << 11)
#define DEFW_EXUP		(1 << 5)
#define DEFW_VCUP		(1 << 4)
#define DEFW_DEFE		(1 << 0)

#define DAPCW			0x00024
#define DAPCW_CODE		(0x7773 << 16)
#define DAPCW_AP2E		(1 << 4)
#define DAPCW_AP1E		(1 << 0)

#define DCPCW			0x00028
#define DCPCW_CODE		(0x7773 << 16)
#define DCPCW_CA2B		(1 << 13)
#define DCPCW_CD2F		(1 << 12)
#define DCPCW_DC2E		(1 << 8)
#define DCPCW_CAB		(1 << 5)
#define DCPCW_CDF		(1 << 4)
#define DCPCW_DCE		(1 << 0)

#define DEFW2			0x00034
#define DEFW2_CODE		(0x7775 << 16)
#define DEFW2_DEFE2G		(1 << 0)

#define DEFW3			0x00038
#define DEFW3_CODE		(0x7776 << 16)
#define DEFW3_EVDA		(1 << 14)
#define DEFW3_EVDM_1		(1 << 12)
#define DEFW3_EVDM_2		(2 << 12)
#define DEFW3_EVDM_3		(3 << 12)
#define DEFW3_VMSM2_EMA		(1 << 6)
#define DEFW3_VMSM1_ENA		(1 << 4)
#define DEFW3_DEFE3		(1 << 0)

#define DEFW4			0x0003c
#define DEFW4_CODE		(0x7777 << 16)
#define DEFW4_WWUO		(1 << 5)
#define DEFW4_SPCE		(1 << 4)

#define DVCSW			0x000d0
#define DVCSW_VCnFB2_DSA0(n)	(0 << ((n)*2+16))
#define DVCSW_VCnFB2_DSA1(n)	(1 << ((n)*2+16))
#define DVCSW_VCnFB2_DSA2(n)	(2 << ((n)*2+16))
#define DVCSW_VCnFB2_INIT(n)	(3 << ((n)*2+16))
#define DVCSW_VCnFB2_MASK(n)	(3 << ((n)*2+16))
#define DVCSW_VCnFB_DSA0(n)	(0 << ((n)*2))
#define DVCSW_VCnFB_DSA1(n)	(1 << ((n)*2))
#define DVCSW_VCnFB_DSA2(n)	(2 << ((n)*2))
#define DVCSW_VCnFB_INIT(n)	(3 << ((n)*2))
#define DVCSW_VCnFB_MASK(n)	(3 << ((n)*2))

#define DEFW5			0x000e0
#define DEFW5_CODE		(0x66 << 24)
#define DEFW5_YCWGB2_DIS	(0 << 14)
#define DEFW5_YCWGB2_PWI1	(1 << 14)
#define DEFW5_YCWGB2_PWI2	(2 << 14)
#define DEFW5_YCWGB2_PWI3	(3 << 14)
#define DEFW5_YCWGB2_MASK	(3 << 14)
#define DEFW5_YCWGB1_DIS	(0 << 12)
#define DEFW5_YCWGB1_PWI1	(1 << 12)
#define DEFW5_YCWGB1_PWI2	(2 << 12)
#define DEFW5_YCWGB1_PWI3	(3 << 12)
#define DEFW5_YCWGB1_MASK	(3 << 12)
#define DEFW5_DEFE5		(1 << 0)

#define DDWTW			0x000e4
#define DDWTW_CODE		(0x7766 << 16)
#define DDWTW_DWAW2		(1 << 6)
#define DDWTW_DWAY2		(1 << 5)
#define DDWTW_DWAY1		(1 << 1)

#define DEFW6			0x000e8
#define DEFW6_CODE		(0x7778 << 16)
#define DEFW6_ODPM12_DSMW	(0 << 10)
#define DEFW6_ODPM12_DISP	(2 << 10)
#define DEFW6_ODPM12_CDE	(3 << 10)
#define DEFW6_ODPM12_MASK	(3 << 10)
#define DEFW6_ODPM02_DSMW	(0 << 8)
#define DEFW6_ODPM02_DISP	(2 << 8)
#define DEFW6_ODPM02_CDE	(3 << 8)
#define DEFW6_ODPM02_MASK	(3 << 8)
#define DEFW6_TCNE1		(1 << 6)
#define DEFW6_TCNE0		(1 << 4)
#define DEFW6_MWOS1		(1 << 2)
#define DEFW6_DEFAUWT		(DEFW6_CODE | DEFW6_TCNE1)

#define DEFW7			0x000ec
#define DEFW7_CODE		(0x7779 << 16)
#define DEFW7_CMME1		BIT(6)
#define DEFW7_CMME0		BIT(4)

/* -----------------------------------------------------------------------------
 * W8A7790-onwy Contwow Wegistews
 */

#define DD1SSW			0x20008
#define DD1SSW_TVW		(1 << 15)
#define DD1SSW_FWM		(1 << 14)
#define DD1SSW_BUF		(1 << 12)
#define DD1SSW_VBK		(1 << 11)
#define DD1SSW_WINT		(1 << 9)
#define DD1SSW_HBK		(1 << 8)
#define DD1SSW_ADC(n)		(1 << ((n)-1))

#define DD1SWCW			0x2000c
#define DD1SWCW_TVW		(1 << 15)
#define DD1SWCW_FWM		(1 << 14)
#define DD1SWCW_BUF		(1 << 12)
#define DD1SWCW_VBK		(1 << 11)
#define DD1SWCW_WINT		(1 << 9)
#define DD1SWCW_HBK		(1 << 8)
#define DD1SWCW_ADC(n)		(1 << ((n)-1))

#define DD1IEW			0x20010
#define DD1IEW_TVW		(1 << 15)
#define DD1IEW_FWM		(1 << 14)
#define DD1IEW_BUF		(1 << 12)
#define DD1IEW_VBK		(1 << 11)
#define DD1IEW_WINT		(1 << 9)
#define DD1IEW_HBK		(1 << 8)
#define DD1IEW_ADC(n)		(1 << ((n)-1))

#define DEFW8			0x20020
#define DEFW8_CODE		(0x7790 << 16)
#define DEFW8_VSCS		(1 << 6)
#define DEFW8_DWGBS_DU(n)	((n) << 4)
#define DEFW8_DWGBS_MASK	(3 << 4)
#define DEFW8_DEFE8		(1 << 0)

#define DOFWW			0x20024
#define DOFWW_CODE		(0x7790 << 16)
#define DOFWW_HSYCFW1		(1 << 13)
#define DOFWW_VSYCFW1		(1 << 12)
#define DOFWW_ODDFW1		(1 << 11)
#define DOFWW_DISPFW1		(1 << 10)
#define DOFWW_CDEFW1		(1 << 9)
#define DOFWW_WGBFW1		(1 << 8)
#define DOFWW_HSYCFW0		(1 << 5)
#define DOFWW_VSYCFW0		(1 << 4)
#define DOFWW_ODDFW0		(1 << 3)
#define DOFWW_DISPFW0		(1 << 2)
#define DOFWW_CDEFW0		(1 << 1)
#define DOFWW_WGBFW0		(1 << 0)

#define DIDSW			0x20028
#define DIDSW_CODE		(0x7790 << 16)
#define DIDSW_WDCS_DCWKIN(n)	(0 << (8 + (n) * 2))
#define DIDSW_WDCS_DSI(n)	(2 << (8 + (n) * 2))	/* V3U onwy */
#define DIDSW_WDCS_WVDS0(n)	(2 << (8 + (n) * 2))
#define DIDSW_WDCS_WVDS1(n)	(3 << (8 + (n) * 2))
#define DIDSW_WDCS_MASK(n)	(3 << (8 + (n) * 2))
#define DIDSW_PDCS_CWK(n, cwk)	(cwk << ((n) * 2))
#define DIDSW_PDCS_MASK(n)	(3 << ((n) * 2))

#define DEFW10			0x20038
#define DEFW10_CODE		(0x7795 << 16)
#define DEFW10_VSPF1_WGB	(0 << 14)
#define DEFW10_VSPF1_YC		(1 << 14)
#define DEFW10_DOCF1_WGB	(0 << 12)
#define DEFW10_DOCF1_YC		(1 << 12)
#define DEFW10_YCDF0_YCBCW444	(0 << 11)
#define DEFW10_YCDF0_YCBCW422	(1 << 11)
#define DEFW10_VSPF0_WGB	(0 << 10)
#define DEFW10_VSPF0_YC		(1 << 10)
#define DEFW10_DOCF0_WGB	(0 << 8)
#define DEFW10_DOCF0_YC		(1 << 8)
#define DEFW10_TSEW_H3_TCON1	(0 << 1) /* DEFW102 wegistew onwy (DU2/DU3) */
#define DEFW10_DEFE10		(1 << 0)

#define DPWWCW			0x20044
#define DPWWCW_CODE		(0x95 << 24)
#define DPWWCW_PWCS1		(1 << 23)
#define DPWWCW_PWCS0		(1 << 21)
#define DPWWCW_CWKE		(1 << 18)
#define DPWWCW_FDPWW(n)		((n) << 12)
#define DPWWCW_N(n)		((n) << 5)
#define DPWWCW_M(n)		((n) << 3)
#define DPWWCW_STBY		(1 << 2)
#define DPWWCW_INCS_DOTCWKIN0	(0 << 0)
#define DPWWCW_INCS_DOTCWKIN1	(1 << 1)

#define DPWWC2W			0x20048
#define DPWWC2W_CODE		(0x95 << 24)
#define DPWWC2W_SEWC		(1 << 12)
#define DPWWC2W_M(n)		((n) << 8)
#define DPWWC2W_FDPWW(n)	((n) << 0)

/* -----------------------------------------------------------------------------
 * Dispway Timing Genewation Wegistews
 */

#define HDSW			0x00040
#define HDEW			0x00044
#define VDSW			0x00048
#define VDEW			0x0004c
#define HCW			0x00050
#define HSWW			0x00054
#define VCW			0x00058
#define VSPW			0x0005c
#define EQWW			0x00060
#define SPWW			0x00064
#define CWAMPSW			0x00070
#define CWAMPWW			0x00074
#define DESW			0x00078
#define DEWW			0x0007c

/* -----------------------------------------------------------------------------
 * Dispway Attwibute Wegistews
 */

#define CP1TW			0x00080
#define CP2TW			0x00084
#define CP3TW			0x00088
#define CP4TW			0x0008c

#define DOOW			0x00090
#define DOOW_WGB(w, g, b)	(((w) << 18) | ((g) << 10) | ((b) << 2))
#define CDEW			0x00094
#define CDEW_WGB(w, g, b)	(((w) << 18) | ((g) << 10) | ((b) << 2))
#define BPOW			0x00098
#define BPOW_WGB(w, g, b)	(((w) << 18) | ((g) << 10) | ((b) << 2))

#define WINTOFSW		0x0009c

#define DSHPW			0x000c8
#define DSHPW_CODE		(0x7776 << 16)
#define DSHPW_PWIH		(0xa << 4)
#define DSHPW_PWIW_BPP16	(0x8 << 0)
#define DSHPW_PWIW_BPP32	(0x9 << 0)

/* -----------------------------------------------------------------------------
 * Dispway Pwane Wegistews
 */

#define PWANE_OFF		0x00100

#define PnMW			0x00100 /* pwane 1 */
#define PnMW_VISW_VIN0		(0 << 26)	/* use Video Input 0 */
#define PnMW_VISW_VIN1		(1 << 26)	/* use Video Input 1 */
#define PnMW_VISW_VIN2		(2 << 26)	/* use Video Input 2 */
#define PnMW_VISW_VIN3		(3 << 26)	/* use Video Input 3 */
#define PnMW_YCDF_YUYV		(1 << 20)	/* YUYV fowmat */
#define PnMW_TC_W		(0 << 17)	/* Twanpawent cowow is PnTC1W */
#define PnMW_TC_CP		(1 << 17)	/* Twanpawent cowow is cowow pawette */
#define PnMW_WAE		(1 << 16)	/* Wwap awound Enabwe */
#define PnMW_SPIM_TP		(0 << 12)	/* Twanspawent Cowow */
#define PnMW_SPIM_AWP		(1 << 12)	/* Awpha Bwending */
#define PnMW_SPIM_EOW		(2 << 12)	/* EOW */
#define PnMW_SPIM_TP_OFF	(1 << 14)	/* No Twanspawent Cowow */
#define PnMW_CPSW_CP1		(0 << 8)	/* Cowow Pawette sewected 1 */
#define PnMW_CPSW_CP2		(1 << 8)	/* Cowow Pawette sewected 2 */
#define PnMW_CPSW_CP3		(2 << 8)	/* Cowow Pawette sewected 3 */
#define PnMW_CPSW_CP4		(3 << 8)	/* Cowow Pawette sewected 4 */
#define PnMW_DC			(1 << 7)	/* Dispway Awea Change */
#define PnMW_BM_MD		(0 << 4)	/* Manuaw Dispway Change Mode */
#define PnMW_BM_AW		(1 << 4)	/* Auto Wendewing Mode */
#define PnMW_BM_AD		(2 << 4)	/* Auto Dispway Change Mode */
#define PnMW_BM_VC		(3 << 4)	/* Video Captuwe Mode */
#define PnMW_DDDF_8BPP		(0 << 0)	/* 8bit */
#define PnMW_DDDF_16BPP		(1 << 0)	/* 16bit ow 32bit */
#define PnMW_DDDF_AWGB		(2 << 0)	/* AWGB */
#define PnMW_DDDF_YC		(3 << 0)	/* YC */
#define PnMW_DDDF_MASK		(3 << 0)

#define PnMWW			0x00104

#define PnAWPHAW		0x00108
#define PnAWPHAW_ABIT_1		(0 << 12)
#define PnAWPHAW_ABIT_0		(1 << 12)
#define PnAWPHAW_ABIT_X		(2 << 12)

#define PnDSXW			0x00110
#define PnDSYW			0x00114
#define PnDPXW			0x00118
#define PnDPYW			0x0011c

#define PnDSA0W			0x00120
#define PnDSA1W			0x00124
#define PnDSA2W			0x00128
#define PnDSA_MASK		0xfffffff0

#define PnSPXW			0x00130
#define PnSPYW			0x00134
#define PnWASPW			0x00138
#define PnWAMWW			0x0013c

#define PnBTW			0x00140

#define PnTC1W			0x00144
#define PnTC2W			0x00148
#define PnTC3W			0x0014c
#define PnTC3W_CODE		(0x66 << 24)

#define PnMWW			0x00150

#define PnSWAPW			0x00180
#define PnSWAPW_DIGN		(1 << 4)
#define PnSWAPW_SPQW		(1 << 3)
#define PnSWAPW_SPWW		(1 << 2)
#define PnSWAPW_SPWD		(1 << 1)
#define PnSWAPW_SPBY		(1 << 0)

#define PnDDCW			0x00184
#define PnDDCW_CODE		(0x7775 << 16)
#define PnDDCW_WWGB1		(1 << 11)
#define PnDDCW_WWGB0		(1 << 10)

#define PnDDCW2			0x00188
#define PnDDCW2_CODE		(0x7776 << 16)
#define PnDDCW2_NV21		(1 << 5)
#define PnDDCW2_Y420		(1 << 4)
#define PnDDCW2_DIVU		(1 << 1)
#define PnDDCW2_DIVY		(1 << 0)

#define PnDDCW4			0x00190
#define PnDDCW4_CODE		(0x7766 << 16)
#define PnDDCW4_VSPS		(1 << 13)
#define PnDDCW4_SDFS_WGB	(0 << 4)
#define PnDDCW4_SDFS_YC		(5 << 4)
#define PnDDCW4_SDFS_MASK	(7 << 4)
#define PnDDCW4_EDF_NONE	(0 << 0)
#define PnDDCW4_EDF_AWGB8888	(1 << 0)
#define PnDDCW4_EDF_WGB888	(2 << 0)
#define PnDDCW4_EDF_WGB666	(3 << 0)
#define PnDDCW4_EDF_MASK	(7 << 0)

#define APnMW			0x0a100
#define APnMW_WAE		(1 << 16)	/* Wwap awound Enabwe */
#define APnMW_DC		(1 << 7)	/* Dispway Awea Change */
#define APnMW_BM_MD		(0 << 4)	/* Manuaw Dispway Change Mode */
#define APnMW_BM_AD		(2 << 4)	/* Auto Dispway Change Mode */

#define APnMWW			0x0a104

#define APnDSXW			0x0a110
#define APnDSYW			0x0a114
#define APnDPXW			0x0a118
#define APnDPYW			0x0a11c

#define APnDSA0W		0x0a120
#define APnDSA1W		0x0a124
#define APnDSA2W		0x0a128

#define APnSPXW			0x0a130
#define APnSPYW			0x0a134
#define APnWASPW		0x0a138
#define APnWAMWW		0x0a13c

#define APnBTW			0x0a140

#define APnMWW			0x0a150
#define APnSWAPW		0x0a180

/* -----------------------------------------------------------------------------
 * Dispway Captuwe Wegistews
 */

#define DCMW			0x0c100
#define DCMWW			0x0c104
#define DCSAW			0x0c120
#define DCMWW			0x0c150

/* -----------------------------------------------------------------------------
 * Cowow Pawette Wegistews
 */

#define CP1_000W		0x01000
#define CP1_255W		0x013fc
#define CP2_000W		0x02000
#define CP2_255W		0x023fc
#define CP3_000W		0x03000
#define CP3_255W		0x033fc
#define CP4_000W		0x04000
#define CP4_255W		0x043fc

/* -----------------------------------------------------------------------------
 * Extewnaw Synchwonization Contwow Wegistews
 */

#define ESCW02			0x10000
#define ESCW13			0x01000
#define ESCW_DCWKOINV		(1 << 25)
#define ESCW_DCWKSEW_DCWKIN	(0 << 20)
#define ESCW_DCWKSEW_CWKS	(1 << 20)
#define ESCW_DCWKSEW_MASK	(1 << 20)
#define ESCW_DCWKDIS		(1 << 16)
#define ESCW_SYNCSEW_OFF	(0 << 8)
#define ESCW_SYNCSEW_EXVSYNC	(2 << 8)
#define ESCW_SYNCSEW_EXHSYNC	(3 << 8)
#define ESCW_FWQSEW_MASK	(0x3f << 0)

#define OTAW02			0x10004
#define OTAW13			0x01004

/* -----------------------------------------------------------------------------
 * Duaw Dispway Output Contwow Wegistews
 */

#define DOWCW			0x11000
#define DOWCW_PG1T		(1 << 30)
#define DOWCW_DK1S		(1 << 28)
#define DOWCW_PG1D_DS0		(0 << 24)
#define DOWCW_PG1D_DS1		(1 << 24)
#define DOWCW_PG1D_FIX0		(2 << 24)
#define DOWCW_PG1D_DOOW		(3 << 24)
#define DOWCW_PG1D_MASK		(3 << 24)
#define DOWCW_DW0D		(1 << 21)
#define DOWCW_PG0D_DS0		(0 << 16)
#define DOWCW_PG0D_DS1		(1 << 16)
#define DOWCW_PG0D_FIX0		(2 << 16)
#define DOWCW_PG0D_DOOW		(3 << 16)
#define DOWCW_PG0D_MASK		(3 << 16)
#define DOWCW_WGPV		(1 << 4)
#define DOWCW_DPWS		(1 << 0)

#define DPTSW			0x11004
#define DPTSW_PnDK(n)		(1 << ((n) + 16))
#define DPTSW_PnTS(n)		(1 << (n))

#define DAPTSW			0x11008
#define DAPTSW_APnDK(n)		(1 << ((n) + 16))
#define DAPTSW_APnTS(n)		(1 << (n))

#define DS1PW			0x11020
#define DS2PW			0x11024

/* -----------------------------------------------------------------------------
 * YC-WGB Convewsion Coefficient Wegistews
 */

#define YNCW			0x11080
#define YNOW			0x11084
#define CWNOW			0x11088
#define CBNOW			0x1108c
#define WCWCW			0x11090
#define GCWCW			0x11094
#define GCBCW			0x11098
#define BCBCW			0x1109c

#endif /* __WCAW_DU_WEGS_H__ */
