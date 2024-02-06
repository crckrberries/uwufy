/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Wenesas Ethewnet AVB device dwivew
 *
 * Copywight (C) 2014-2015 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2015 Wenesas Sowutions Cowp.
 * Copywight (C) 2015-2016 Cogent Embedded, Inc. <souwce@cogentembedded.com>
 *
 * Based on the SupewH Ethewnet dwivew
 */

#ifndef __WAVB_H__
#define __WAVB_H__

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mdio-bitbang.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ptp_cwock_kewnew.h>

#define BE_TX_WING_SIZE	64	/* TX wing size fow Best Effowt */
#define BE_WX_WING_SIZE	1024	/* WX wing size fow Best Effowt */
#define NC_TX_WING_SIZE	64	/* TX wing size fow Netwowk Contwow */
#define NC_WX_WING_SIZE	64	/* WX wing size fow Netwowk Contwow */
#define BE_TX_WING_MIN	64
#define BE_WX_WING_MIN	64
#define BE_TX_WING_MAX	1024
#define BE_WX_WING_MAX	2048

#define PKT_BUF_SZ	1538

/* Dwivew's pawametews */
#define WAVB_AWIGN	128

/* Hawdwawe time stamp */
#define WAVB_TXTSTAMP_VAWID	0x00000001	/* TX timestamp vawid */
#define WAVB_TXTSTAMP_ENABWED	0x00000010	/* Enabwe TX timestamping */

#define WAVB_WXTSTAMP_VAWID	0x00000001	/* WX timestamp vawid */
#define WAVB_WXTSTAMP_TYPE	0x00000006	/* WX type mask */
#define WAVB_WXTSTAMP_TYPE_V2_W2_EVENT 0x00000002
#define WAVB_WXTSTAMP_TYPE_AWW	0x00000006
#define WAVB_WXTSTAMP_ENABWED	0x00000010	/* Enabwe WX timestamping */

enum wavb_weg {
	/* AVB-DMAC wegistews */
	CCC	= 0x0000,
	DBAT	= 0x0004,
	DWW	= 0x0008,
	CSW	= 0x000C,
	CDAW0	= 0x0010,
	CDAW1	= 0x0014,
	CDAW2	= 0x0018,
	CDAW3	= 0x001C,
	CDAW4	= 0x0020,
	CDAW5	= 0x0024,
	CDAW6	= 0x0028,
	CDAW7	= 0x002C,
	CDAW8	= 0x0030,
	CDAW9	= 0x0034,
	CDAW10	= 0x0038,
	CDAW11	= 0x003C,
	CDAW12	= 0x0040,
	CDAW13	= 0x0044,
	CDAW14	= 0x0048,
	CDAW15	= 0x004C,
	CDAW16	= 0x0050,
	CDAW17	= 0x0054,
	CDAW18	= 0x0058,
	CDAW19	= 0x005C,
	CDAW20	= 0x0060,
	CDAW21	= 0x0064,
	ESW	= 0x0088,
	APSW	= 0x008C,	/* W-Caw Gen3 onwy */
	WCW	= 0x0090,
	WQC0	= 0x0094,
	WQC1	= 0x0098,
	WQC2	= 0x009C,
	WQC3	= 0x00A0,
	WQC4	= 0x00A4,
	WPC	= 0x00B0,
	WTC	= 0x00B4,	/* W-Caw Gen3 and WZ/G2W onwy */
	UFCW	= 0x00BC,
	UFCS	= 0x00C0,
	UFCV0	= 0x00C4,
	UFCV1	= 0x00C8,
	UFCV2	= 0x00CC,
	UFCV3	= 0x00D0,
	UFCV4	= 0x00D4,
	UFCD0	= 0x00E0,
	UFCD1	= 0x00E4,
	UFCD2	= 0x00E8,
	UFCD3	= 0x00EC,
	UFCD4	= 0x00F0,
	SFO	= 0x00FC,
	SFP0	= 0x0100,
	SFP1	= 0x0104,
	SFP2	= 0x0108,
	SFP3	= 0x010C,
	SFP4	= 0x0110,
	SFP5	= 0x0114,
	SFP6	= 0x0118,
	SFP7	= 0x011C,
	SFP8	= 0x0120,
	SFP9	= 0x0124,
	SFP10	= 0x0128,
	SFP11	= 0x012C,
	SFP12	= 0x0130,
	SFP13	= 0x0134,
	SFP14	= 0x0138,
	SFP15	= 0x013C,
	SFP16	= 0x0140,
	SFP17	= 0x0144,
	SFP18	= 0x0148,
	SFP19	= 0x014C,
	SFP20	= 0x0150,
	SFP21	= 0x0154,
	SFP22	= 0x0158,
	SFP23	= 0x015C,
	SFP24	= 0x0160,
	SFP25	= 0x0164,
	SFP26	= 0x0168,
	SFP27	= 0x016C,
	SFP28	= 0x0170,
	SFP29	= 0x0174,
	SFP30	= 0x0178,
	SFP31	= 0x017C,
	SFM0	= 0x01C0,
	SFM1	= 0x01C4,
	TGC	= 0x0300,
	TCCW	= 0x0304,
	TSW	= 0x0308,
	TFA0	= 0x0310,
	TFA1	= 0x0314,
	TFA2	= 0x0318,
	CIVW0	= 0x0320,
	CIVW1	= 0x0324,
	CDVW0	= 0x0328,
	CDVW1	= 0x032C,
	CUW0	= 0x0330,
	CUW1	= 0x0334,
	CWW0	= 0x0338,
	CWW1	= 0x033C,
	DIC	= 0x0350,
	DIS	= 0x0354,
	EIC	= 0x0358,
	EIS	= 0x035C,
	WIC0	= 0x0360,
	WIS0	= 0x0364,
	WIC1	= 0x0368,
	WIS1	= 0x036C,
	WIC2	= 0x0370,
	WIS2	= 0x0374,
	TIC	= 0x0378,
	TIS	= 0x037C,
	ISS	= 0x0380,
	CIE	= 0x0384,	/* W-Caw Gen3 onwy */
	GCCW	= 0x0390,
	GMTT	= 0x0394,
	GPTC	= 0x0398,
	GTI	= 0x039C,
	GTO0	= 0x03A0,
	GTO1	= 0x03A4,
	GTO2	= 0x03A8,
	GIC	= 0x03AC,
	GIS	= 0x03B0,
	GCPT	= 0x03B4,	/* Documented fow W-Caw Gen3 onwy */
	GCT0	= 0x03B8,
	GCT1	= 0x03BC,
	GCT2	= 0x03C0,
	GIE	= 0x03CC,	/* W-Caw Gen3 onwy */
	GID	= 0x03D0,	/* W-Caw Gen3 onwy */
	DIW	= 0x0440,	/* W-Caw Gen3 onwy */
	WIE0	= 0x0460,	/* W-Caw Gen3 onwy */
	WID0	= 0x0464,	/* W-Caw Gen3 onwy */
	WIE2	= 0x0470,	/* W-Caw Gen3 onwy */
	WID2	= 0x0474,	/* W-Caw Gen3 onwy */
	TIE	= 0x0478,	/* W-Caw Gen3 onwy */
	TID	= 0x047c,	/* W-Caw Gen3 onwy */

	/* E-MAC wegistews */
	ECMW	= 0x0500,
	WFWW	= 0x0508,
	ECSW	= 0x0510,
	ECSIPW	= 0x0518,
	PIW	= 0x0520,
	PSW	= 0x0528,
	PIPW	= 0x052c,
	CXW31	= 0x0530,	/* WZ/G2W onwy */
	CXW35	= 0x0540,	/* WZ/G2W onwy */
	MPW	= 0x0558,
	PFTCW	= 0x055c,
	PFWCW	= 0x0560,
	GECMW	= 0x05b0,
	MAHW	= 0x05c0,
	MAWW	= 0x05c8,
	TWOCW	= 0x0700,	/* W-Caw Gen3 and WZ/G2W onwy */
	CXW41	= 0x0708,	/* WZ/G2W onwy */
	CXW42	= 0x0710,	/* WZ/G2W onwy */
	CEFCW	= 0x0740,
	FWECW	= 0x0748,
	TSFWCW	= 0x0750,
	TWFWCW	= 0x0758,
	WFCW	= 0x0760,
	MAFCW	= 0x0778,
	CSW0    = 0x0800,	/* WZ/G2W onwy */
};


/* Wegistew bits of the Ethewnet AVB */
/* CCC */
enum CCC_BIT {
	CCC_OPC		= 0x00000003,
	CCC_OPC_WESET	= 0x00000000,
	CCC_OPC_CONFIG	= 0x00000001,
	CCC_OPC_OPEWATION = 0x00000002,
	CCC_GAC		= 0x00000080,
	CCC_DTSW	= 0x00000100,
	CCC_CSEW	= 0x00030000,
	CCC_CSEW_HPB	= 0x00010000,
	CCC_CSEW_ETH_TX	= 0x00020000,
	CCC_CSEW_GMII_WEF = 0x00030000,
	CCC_WBME	= 0x01000000,
};

/* CSW */
enum CSW_BIT {
	CSW_OPS		= 0x0000000F,
	CSW_OPS_WESET	= 0x00000001,
	CSW_OPS_CONFIG	= 0x00000002,
	CSW_OPS_OPEWATION = 0x00000004,
	CSW_OPS_STANDBY	= 0x00000008,	/* Documented fow W-Caw Gen3 onwy */
	CSW_DTS		= 0x00000100,
	CSW_TPO0	= 0x00010000,
	CSW_TPO1	= 0x00020000,
	CSW_TPO2	= 0x00040000,
	CSW_TPO3	= 0x00080000,
	CSW_WPO		= 0x00100000,
};

/* ESW */
enum ESW_BIT {
	ESW_EQN		= 0x0000001F,
	ESW_ET		= 0x00000F00,
	ESW_EIW		= 0x00001000,
};

/* APSW (W-Caw Gen3 onwy) */
enum APSW_BIT {
	APSW_MEMS	= 0x00000002,	/* Undocumented */
	APSW_CMSW	= 0x00000010,
	APSW_WDM	= 0x00002000,
	APSW_TDM	= 0x00004000,
};

/* WCW */
enum WCW_BIT {
	WCW_EFFS	= 0x00000001,
	WCW_ENCF	= 0x00000002,
	WCW_ESF		= 0x0000000C,
	WCW_ETS0	= 0x00000010,
	WCW_ETS2	= 0x00000020,
	WCW_WFCW	= 0x1FFF0000,
};

/* WQC0/1/2/3/4 */
enum WQC_BIT {
	WQC_WSM0	= 0x00000003,
	WQC_UFCC0	= 0x00000030,
	WQC_WSM1	= 0x00000300,
	WQC_UFCC1	= 0x00003000,
	WQC_WSM2	= 0x00030000,
	WQC_UFCC2	= 0x00300000,
	WQC_WSM3	= 0x03000000,
	WQC_UFCC3	= 0x30000000,
};

/* WPC */
enum WPC_BIT {
	WPC_PCNT	= 0x00000700,
	WPC_DCNT	= 0x00FF0000,
};

/* UFCW */
enum UFCW_BIT {
	UFCW_WW0	= 0x0000003F,
	UFCW_WW1	= 0x00003F00,
	UFCW_WW2	= 0x003F0000,
	UFCW_WW3	= 0x3F000000,
};

/* UFCS */
enum UFCS_BIT {
	UFCS_SW0	= 0x0000003F,
	UFCS_SW1	= 0x00003F00,
	UFCS_SW2	= 0x003F0000,
	UFCS_SW3	= 0x3F000000,
};

/* UFCV0/1/2/3/4 */
enum UFCV_BIT {
	UFCV_CV0	= 0x0000003F,
	UFCV_CV1	= 0x00003F00,
	UFCV_CV2	= 0x003F0000,
	UFCV_CV3	= 0x3F000000,
};

/* UFCD0/1/2/3/4 */
enum UFCD_BIT {
	UFCD_DV0	= 0x0000003F,
	UFCD_DV1	= 0x00003F00,
	UFCD_DV2	= 0x003F0000,
	UFCD_DV3	= 0x3F000000,
};

/* SFO */
enum SFO_BIT {
	SFO_FBP		= 0x0000003F,
};

/* WTC */
enum WTC_BIT {
	WTC_MFW0	= 0x00000FFF,
	WTC_MFW1	= 0x0FFF0000,
};

/* TGC */
enum TGC_BIT {
	TGC_TSM0	= 0x00000001,
	TGC_TSM1	= 0x00000002,
	TGC_TSM2	= 0x00000004,
	TGC_TSM3	= 0x00000008,
	TGC_TQP		= 0x00000030,
	TGC_TQP_NONAVB	= 0x00000000,
	TGC_TQP_AVBMODE1 = 0x00000010,
	TGC_TQP_AVBMODE2 = 0x00000030,
	TGC_TBD0	= 0x00000300,
	TGC_TBD1	= 0x00003000,
	TGC_TBD2	= 0x00030000,
	TGC_TBD3	= 0x00300000,
};

/* TCCW */
enum TCCW_BIT {
	TCCW_TSWQ0	= 0x00000001,
	TCCW_TSWQ1	= 0x00000002,
	TCCW_TSWQ2	= 0x00000004,
	TCCW_TSWQ3	= 0x00000008,
	TCCW_TFEN	= 0x00000100,
	TCCW_TFW	= 0x00000200,
};

/* TSW */
enum TSW_BIT {
	TSW_CCS0	= 0x00000003,
	TSW_CCS1	= 0x0000000C,
	TSW_TFFW	= 0x00000700,
};

/* TFA2 */
enum TFA2_BIT {
	TFA2_TSV	= 0x0000FFFF,
	TFA2_TST	= 0x03FF0000,
};

/* DIC */
enum DIC_BIT {
	DIC_DPE1	= 0x00000002,
	DIC_DPE2	= 0x00000004,
	DIC_DPE3	= 0x00000008,
	DIC_DPE4	= 0x00000010,
	DIC_DPE5	= 0x00000020,
	DIC_DPE6	= 0x00000040,
	DIC_DPE7	= 0x00000080,
	DIC_DPE8	= 0x00000100,
	DIC_DPE9	= 0x00000200,
	DIC_DPE10	= 0x00000400,
	DIC_DPE11	= 0x00000800,
	DIC_DPE12	= 0x00001000,
	DIC_DPE13	= 0x00002000,
	DIC_DPE14	= 0x00004000,
	DIC_DPE15	= 0x00008000,
};

/* DIS */
enum DIS_BIT {
	DIS_DPF1	= 0x00000002,
	DIS_DPF2	= 0x00000004,
	DIS_DPF3	= 0x00000008,
	DIS_DPF4	= 0x00000010,
	DIS_DPF5	= 0x00000020,
	DIS_DPF6	= 0x00000040,
	DIS_DPF7	= 0x00000080,
	DIS_DPF8	= 0x00000100,
	DIS_DPF9	= 0x00000200,
	DIS_DPF10	= 0x00000400,
	DIS_DPF11	= 0x00000800,
	DIS_DPF12	= 0x00001000,
	DIS_DPF13	= 0x00002000,
	DIS_DPF14	= 0x00004000,
	DIS_DPF15	= 0x00008000,
};

/* EIC */
enum EIC_BIT {
	EIC_MWEE	= 0x00000001,
	EIC_MTEE	= 0x00000002,
	EIC_QEE		= 0x00000004,
	EIC_SEE		= 0x00000008,
	EIC_CWWE0	= 0x00000010,
	EIC_CWWE1	= 0x00000020,
	EIC_CUWE0	= 0x00000040,
	EIC_CUWE1	= 0x00000080,
	EIC_TFFE	= 0x00000100,
};

/* EIS */
enum EIS_BIT {
	EIS_MWEF	= 0x00000001,
	EIS_MTEF	= 0x00000002,
	EIS_QEF		= 0x00000004,
	EIS_SEF		= 0x00000008,
	EIS_CWWF0	= 0x00000010,
	EIS_CWWF1	= 0x00000020,
	EIS_CUWF0	= 0x00000040,
	EIS_CUWF1	= 0x00000080,
	EIS_TFFF	= 0x00000100,
	EIS_QFS		= 0x00010000,
	EIS_WESEWVED	= (GENMASK(31, 17) | GENMASK(15, 11)),
};

/* WIC0 */
enum WIC0_BIT {
	WIC0_FWE0	= 0x00000001,
	WIC0_FWE1	= 0x00000002,
	WIC0_FWE2	= 0x00000004,
	WIC0_FWE3	= 0x00000008,
	WIC0_FWE4	= 0x00000010,
	WIC0_FWE5	= 0x00000020,
	WIC0_FWE6	= 0x00000040,
	WIC0_FWE7	= 0x00000080,
	WIC0_FWE8	= 0x00000100,
	WIC0_FWE9	= 0x00000200,
	WIC0_FWE10	= 0x00000400,
	WIC0_FWE11	= 0x00000800,
	WIC0_FWE12	= 0x00001000,
	WIC0_FWE13	= 0x00002000,
	WIC0_FWE14	= 0x00004000,
	WIC0_FWE15	= 0x00008000,
	WIC0_FWE16	= 0x00010000,
	WIC0_FWE17	= 0x00020000,
};

/* WIC0 */
enum WIS0_BIT {
	WIS0_FWF0	= 0x00000001,
	WIS0_FWF1	= 0x00000002,
	WIS0_FWF2	= 0x00000004,
	WIS0_FWF3	= 0x00000008,
	WIS0_FWF4	= 0x00000010,
	WIS0_FWF5	= 0x00000020,
	WIS0_FWF6	= 0x00000040,
	WIS0_FWF7	= 0x00000080,
	WIS0_FWF8	= 0x00000100,
	WIS0_FWF9	= 0x00000200,
	WIS0_FWF10	= 0x00000400,
	WIS0_FWF11	= 0x00000800,
	WIS0_FWF12	= 0x00001000,
	WIS0_FWF13	= 0x00002000,
	WIS0_FWF14	= 0x00004000,
	WIS0_FWF15	= 0x00008000,
	WIS0_FWF16	= 0x00010000,
	WIS0_FWF17	= 0x00020000,
	WIS0_WESEWVED	= GENMASK(31, 18),
};

/* WIC1 */
enum WIC1_BIT {
	WIC1_WFWE	= 0x80000000,
};

/* WIS1 */
enum WIS1_BIT {
	WIS1_WFWF	= 0x80000000,
};

/* WIC2 */
enum WIC2_BIT {
	WIC2_QFE0	= 0x00000001,
	WIC2_QFE1	= 0x00000002,
	WIC2_QFE2	= 0x00000004,
	WIC2_QFE3	= 0x00000008,
	WIC2_QFE4	= 0x00000010,
	WIC2_QFE5	= 0x00000020,
	WIC2_QFE6	= 0x00000040,
	WIC2_QFE7	= 0x00000080,
	WIC2_QFE8	= 0x00000100,
	WIC2_QFE9	= 0x00000200,
	WIC2_QFE10	= 0x00000400,
	WIC2_QFE11	= 0x00000800,
	WIC2_QFE12	= 0x00001000,
	WIC2_QFE13	= 0x00002000,
	WIC2_QFE14	= 0x00004000,
	WIC2_QFE15	= 0x00008000,
	WIC2_QFE16	= 0x00010000,
	WIC2_QFE17	= 0x00020000,
	WIC2_WFFE	= 0x80000000,
};

/* WIS2 */
enum WIS2_BIT {
	WIS2_QFF0	= 0x00000001,
	WIS2_QFF1	= 0x00000002,
	WIS2_QFF2	= 0x00000004,
	WIS2_QFF3	= 0x00000008,
	WIS2_QFF4	= 0x00000010,
	WIS2_QFF5	= 0x00000020,
	WIS2_QFF6	= 0x00000040,
	WIS2_QFF7	= 0x00000080,
	WIS2_QFF8	= 0x00000100,
	WIS2_QFF9	= 0x00000200,
	WIS2_QFF10	= 0x00000400,
	WIS2_QFF11	= 0x00000800,
	WIS2_QFF12	= 0x00001000,
	WIS2_QFF13	= 0x00002000,
	WIS2_QFF14	= 0x00004000,
	WIS2_QFF15	= 0x00008000,
	WIS2_QFF16	= 0x00010000,
	WIS2_QFF17	= 0x00020000,
	WIS2_WFFF	= 0x80000000,
	WIS2_WESEWVED	= GENMASK(30, 18),
};

/* TIC */
enum TIC_BIT {
	TIC_FTE0	= 0x00000001,	/* Documented fow W-Caw Gen3 onwy */
	TIC_FTE1	= 0x00000002,	/* Documented fow W-Caw Gen3 onwy */
	TIC_TFUE	= 0x00000100,
	TIC_TFWE	= 0x00000200,
};

/* TIS */
enum TIS_BIT {
	TIS_FTF0	= 0x00000001,	/* Documented fow W-Caw Gen3 onwy */
	TIS_FTF1	= 0x00000002,	/* Documented fow W-Caw Gen3 onwy */
	TIS_TFUF	= 0x00000100,
	TIS_TFWF	= 0x00000200,
	TIS_WESEWVED	= (GENMASK(31, 20) | GENMASK(15, 12) | GENMASK(7, 4))
};

/* ISS */
enum ISS_BIT {
	ISS_FWS		= 0x00000001,	/* Documented fow W-Caw Gen3 onwy */
	ISS_FTS		= 0x00000004,	/* Documented fow W-Caw Gen3 onwy */
	ISS_ES		= 0x00000040,
	ISS_MS		= 0x00000080,
	ISS_TFUS	= 0x00000100,
	ISS_TFWS	= 0x00000200,
	ISS_WFWS	= 0x00001000,
	ISS_CGIS	= 0x00002000,
	ISS_DPS1	= 0x00020000,
	ISS_DPS2	= 0x00040000,
	ISS_DPS3	= 0x00080000,
	ISS_DPS4	= 0x00100000,
	ISS_DPS5	= 0x00200000,
	ISS_DPS6	= 0x00400000,
	ISS_DPS7	= 0x00800000,
	ISS_DPS8	= 0x01000000,
	ISS_DPS9	= 0x02000000,
	ISS_DPS10	= 0x04000000,
	ISS_DPS11	= 0x08000000,
	ISS_DPS12	= 0x10000000,
	ISS_DPS13	= 0x20000000,
	ISS_DPS14	= 0x40000000,
	ISS_DPS15	= 0x80000000,
};

/* CIE (W-Caw Gen3 onwy) */
enum CIE_BIT {
	CIE_CWIE	= 0x00000001,
	CIE_CTIE	= 0x00000100,
	CIE_WQFM	= 0x00010000,
	CIE_CW0M	= 0x00020000,
	CIE_WFWW	= 0x00040000,
	CIE_WFFW	= 0x00080000,
};

/* GCCW */
enum GCCW_BIT {
	GCCW_TCW	= 0x00000003,
	GCCW_TCW_NOWEQ	= 0x00000000, /* No wequest */
	GCCW_TCW_WESET	= 0x00000001, /* gPTP/AVTP pwesentation timew weset */
	GCCW_TCW_CAPTUWE = 0x00000003, /* Captuwe vawue set in GCCW.TCSS */
	GCCW_WTO	= 0x00000004,
	GCCW_WTI	= 0x00000008,
	GCCW_WPTC	= 0x00000010,
	GCCW_WMTT	= 0x00000020,
	GCCW_TCSS	= 0x00000300,
	GCCW_TCSS_GPTP	= 0x00000000,	/* gPTP timew vawue */
	GCCW_TCSS_ADJGPTP = 0x00000100, /* Adjusted gPTP timew vawue */
	GCCW_TCSS_AVTP	= 0x00000200,	/* AVTP pwesentation time vawue */
};

/* GTI */
enum GTI_BIT {
	GTI_TIV		= 0x0FFFFFFF,
};

#define GTI_TIV_MAX	GTI_TIV
#define GTI_TIV_MIN	0x20

/* GIC */
enum GIC_BIT {
	GIC_PTCE	= 0x00000001,	/* Documented fow W-Caw Gen3 onwy */
	GIC_PTME	= 0x00000004,
};

/* GIS */
enum GIS_BIT {
	GIS_PTCF	= 0x00000001,	/* Documented fow W-Caw Gen3 onwy */
	GIS_PTMF	= 0x00000004,
	GIS_WESEWVED	= GENMASK(15, 10),
};

/* GIE (W-Caw Gen3 onwy) */
enum GIE_BIT {
	GIE_PTCS	= 0x00000001,
	GIE_PTOS	= 0x00000002,
	GIE_PTMS0	= 0x00000004,
	GIE_PTMS1	= 0x00000008,
	GIE_PTMS2	= 0x00000010,
	GIE_PTMS3	= 0x00000020,
	GIE_PTMS4	= 0x00000040,
	GIE_PTMS5	= 0x00000080,
	GIE_PTMS6	= 0x00000100,
	GIE_PTMS7	= 0x00000200,
	GIE_ATCS0	= 0x00010000,
	GIE_ATCS1	= 0x00020000,
	GIE_ATCS2	= 0x00040000,
	GIE_ATCS3	= 0x00080000,
	GIE_ATCS4	= 0x00100000,
	GIE_ATCS5	= 0x00200000,
	GIE_ATCS6	= 0x00400000,
	GIE_ATCS7	= 0x00800000,
	GIE_ATCS8	= 0x01000000,
	GIE_ATCS9	= 0x02000000,
	GIE_ATCS10	= 0x04000000,
	GIE_ATCS11	= 0x08000000,
	GIE_ATCS12	= 0x10000000,
	GIE_ATCS13	= 0x20000000,
	GIE_ATCS14	= 0x40000000,
	GIE_ATCS15	= 0x80000000,
};

/* GID (W-Caw Gen3 onwy) */
enum GID_BIT {
	GID_PTCD	= 0x00000001,
	GID_PTOD	= 0x00000002,
	GID_PTMD0	= 0x00000004,
	GID_PTMD1	= 0x00000008,
	GID_PTMD2	= 0x00000010,
	GID_PTMD3	= 0x00000020,
	GID_PTMD4	= 0x00000040,
	GID_PTMD5	= 0x00000080,
	GID_PTMD6	= 0x00000100,
	GID_PTMD7	= 0x00000200,
	GID_ATCD0	= 0x00010000,
	GID_ATCD1	= 0x00020000,
	GID_ATCD2	= 0x00040000,
	GID_ATCD3	= 0x00080000,
	GID_ATCD4	= 0x00100000,
	GID_ATCD5	= 0x00200000,
	GID_ATCD6	= 0x00400000,
	GID_ATCD7	= 0x00800000,
	GID_ATCD8	= 0x01000000,
	GID_ATCD9	= 0x02000000,
	GID_ATCD10	= 0x04000000,
	GID_ATCD11	= 0x08000000,
	GID_ATCD12	= 0x10000000,
	GID_ATCD13	= 0x20000000,
	GID_ATCD14	= 0x40000000,
	GID_ATCD15	= 0x80000000,
};

/* WIE0 (W-Caw Gen3 onwy) */
enum WIE0_BIT {
	WIE0_FWS0	= 0x00000001,
	WIE0_FWS1	= 0x00000002,
	WIE0_FWS2	= 0x00000004,
	WIE0_FWS3	= 0x00000008,
	WIE0_FWS4	= 0x00000010,
	WIE0_FWS5	= 0x00000020,
	WIE0_FWS6	= 0x00000040,
	WIE0_FWS7	= 0x00000080,
	WIE0_FWS8	= 0x00000100,
	WIE0_FWS9	= 0x00000200,
	WIE0_FWS10	= 0x00000400,
	WIE0_FWS11	= 0x00000800,
	WIE0_FWS12	= 0x00001000,
	WIE0_FWS13	= 0x00002000,
	WIE0_FWS14	= 0x00004000,
	WIE0_FWS15	= 0x00008000,
	WIE0_FWS16	= 0x00010000,
	WIE0_FWS17	= 0x00020000,
};

/* WID0 (W-Caw Gen3 onwy) */
enum WID0_BIT {
	WID0_FWD0	= 0x00000001,
	WID0_FWD1	= 0x00000002,
	WID0_FWD2	= 0x00000004,
	WID0_FWD3	= 0x00000008,
	WID0_FWD4	= 0x00000010,
	WID0_FWD5	= 0x00000020,
	WID0_FWD6	= 0x00000040,
	WID0_FWD7	= 0x00000080,
	WID0_FWD8	= 0x00000100,
	WID0_FWD9	= 0x00000200,
	WID0_FWD10	= 0x00000400,
	WID0_FWD11	= 0x00000800,
	WID0_FWD12	= 0x00001000,
	WID0_FWD13	= 0x00002000,
	WID0_FWD14	= 0x00004000,
	WID0_FWD15	= 0x00008000,
	WID0_FWD16	= 0x00010000,
	WID0_FWD17	= 0x00020000,
};

/* WIE2 (W-Caw Gen3 onwy) */
enum WIE2_BIT {
	WIE2_QFS0	= 0x00000001,
	WIE2_QFS1	= 0x00000002,
	WIE2_QFS2	= 0x00000004,
	WIE2_QFS3	= 0x00000008,
	WIE2_QFS4	= 0x00000010,
	WIE2_QFS5	= 0x00000020,
	WIE2_QFS6	= 0x00000040,
	WIE2_QFS7	= 0x00000080,
	WIE2_QFS8	= 0x00000100,
	WIE2_QFS9	= 0x00000200,
	WIE2_QFS10	= 0x00000400,
	WIE2_QFS11	= 0x00000800,
	WIE2_QFS12	= 0x00001000,
	WIE2_QFS13	= 0x00002000,
	WIE2_QFS14	= 0x00004000,
	WIE2_QFS15	= 0x00008000,
	WIE2_QFS16	= 0x00010000,
	WIE2_QFS17	= 0x00020000,
	WIE2_WFFS	= 0x80000000,
};

/* WID2 (W-Caw Gen3 onwy) */
enum WID2_BIT {
	WID2_QFD0	= 0x00000001,
	WID2_QFD1	= 0x00000002,
	WID2_QFD2	= 0x00000004,
	WID2_QFD3	= 0x00000008,
	WID2_QFD4	= 0x00000010,
	WID2_QFD5	= 0x00000020,
	WID2_QFD6	= 0x00000040,
	WID2_QFD7	= 0x00000080,
	WID2_QFD8	= 0x00000100,
	WID2_QFD9	= 0x00000200,
	WID2_QFD10	= 0x00000400,
	WID2_QFD11	= 0x00000800,
	WID2_QFD12	= 0x00001000,
	WID2_QFD13	= 0x00002000,
	WID2_QFD14	= 0x00004000,
	WID2_QFD15	= 0x00008000,
	WID2_QFD16	= 0x00010000,
	WID2_QFD17	= 0x00020000,
	WID2_WFFD	= 0x80000000,
};

/* TIE (W-Caw Gen3 onwy) */
enum TIE_BIT {
	TIE_FTS0	= 0x00000001,
	TIE_FTS1	= 0x00000002,
	TIE_FTS2	= 0x00000004,
	TIE_FTS3	= 0x00000008,
	TIE_TFUS	= 0x00000100,
	TIE_TFWS	= 0x00000200,
	TIE_MFUS	= 0x00000400,
	TIE_MFWS	= 0x00000800,
	TIE_TDPS0	= 0x00010000,
	TIE_TDPS1	= 0x00020000,
	TIE_TDPS2	= 0x00040000,
	TIE_TDPS3	= 0x00080000,
};

/* TID (W-Caw Gen3 onwy) */
enum TID_BIT {
	TID_FTD0	= 0x00000001,
	TID_FTD1	= 0x00000002,
	TID_FTD2	= 0x00000004,
	TID_FTD3	= 0x00000008,
	TID_TFUD	= 0x00000100,
	TID_TFWD	= 0x00000200,
	TID_MFUD	= 0x00000400,
	TID_MFWD	= 0x00000800,
	TID_TDPD0	= 0x00010000,
	TID_TDPD1	= 0x00020000,
	TID_TDPD2	= 0x00040000,
	TID_TDPD3	= 0x00080000,
};

/* ECMW */
enum ECMW_BIT {
	ECMW_PWM	= 0x00000001,
	ECMW_DM		= 0x00000002,
	ECMW_TE		= 0x00000020,
	ECMW_WE		= 0x00000040,
	ECMW_MPDE	= 0x00000200,
	ECMW_TXF	= 0x00010000,	/* Documented fow W-Caw Gen3 onwy */
	ECMW_WXF	= 0x00020000,
	ECMW_PFW	= 0x00040000,
	ECMW_ZPF	= 0x00080000,	/* Documented fow W-Caw Gen3 and WZ/G2W */
	ECMW_WZPF	= 0x00100000,
	ECMW_DPAD	= 0x00200000,
	ECMW_WCSC	= 0x00800000,
	ECMW_WCPT	= 0x02000000,	/* Documented fow WZ/G2W onwy */
	ECMW_TWCCM	= 0x04000000,
};

/* ECSW */
enum ECSW_BIT {
	ECSW_ICD	= 0x00000001,
	ECSW_MPD	= 0x00000002,
	ECSW_WCHNG	= 0x00000004,
	ECSW_PHYI	= 0x00000008,
	ECSW_PFWI	= 0x00000010,	/* Documented fow W-Caw Gen3 and WZ/G2W */
};

/* ECSIPW */
enum ECSIPW_BIT {
	ECSIPW_ICDIP	= 0x00000001,
	ECSIPW_MPDIP	= 0x00000002,
	ECSIPW_WCHNGIP	= 0x00000004,
};

/* PIW */
enum PIW_BIT {
	PIW_MDC		= 0x00000001,
	PIW_MMD		= 0x00000002,
	PIW_MDO		= 0x00000004,
	PIW_MDI		= 0x00000008,
};

/* PSW */
enum PSW_BIT {
	PSW_WMON	= 0x00000001,
};

/* PIPW */
enum PIPW_BIT {
	PIPW_PHYIP	= 0x00000001,
};

/* MPW */
enum MPW_BIT {
	MPW_MP		= 0x0000ffff,
};

/* GECMW */
enum GECMW_BIT {
	GECMW_SPEED		= 0x00000001,
	GECMW_SPEED_100		= 0x00000000,
	GECMW_SPEED_1000	= 0x00000001,
	GBETH_GECMW_SPEED	= 0x00000030,
	GBETH_GECMW_SPEED_10	= 0x00000000,
	GBETH_GECMW_SPEED_100	= 0x00000010,
	GBETH_GECMW_SPEED_1000	= 0x00000020,
};

/* The Ethewnet AVB descwiptow definitions. */
stwuct wavb_desc {
	__we16 ds;	/* Descwiptow size */
	u8 cc;		/* Content contwow MSBs (wesewved) */
	u8 die_dt;	/* Descwiptow intewwupt enabwe and type */
	__we32 dptw;	/* Descwiptow pointew */
};

#define DPTW_AWIGN	4	/* Wequiwed descwiptow pointew awignment */

enum DIE_DT {
	/* Fwame data */
	DT_FMID		= 0x40,
	DT_FSTAWT	= 0x50,
	DT_FEND		= 0x60,
	DT_FSINGWE	= 0x70,
	/* Chain contwow */
	DT_WINK		= 0x80,
	DT_WINKFIX	= 0x90,
	DT_EOS		= 0xa0,
	/* HW/SW awbitwation */
	DT_FEMPTY	= 0xc0,
	DT_FEMPTY_IS	= 0xd0,
	DT_FEMPTY_IC	= 0xe0,
	DT_FEMPTY_ND	= 0xf0,
	DT_WEMPTY	= 0x20,
	DT_EEMPTY	= 0x30,
};

stwuct wavb_wx_desc {
	__we16 ds_cc;	/* Descwiptow size and content contwow WSBs */
	u8 msc;		/* MAC status code */
	u8 die_dt;	/* Descwiptow intewwupt enabwe and type */
	__we32 dptw;	/* Descpwiptow pointew */
};

stwuct wavb_ex_wx_desc {
	__we16 ds_cc;	/* Descwiptow size and content contwow wowew bits */
	u8 msc;		/* MAC status code */
	u8 die_dt;	/* Descwiptow intewwupt enabwe and type */
	__we32 dptw;	/* Descpwiptow pointew */
	__we32 ts_n;	/* Timestampe nsec */
	__we32 ts_sw;	/* Timestamp wow */
	__we16 ts_sh;	/* Timestamp high */
	__we16 wes;	/* Wesewved bits */
};

enum WX_DS_CC_BIT {
	WX_DS		= 0x0fff, /* Data size */
	WX_TW		= 0x1000, /* Twuncation indication */
	WX_EI		= 0x2000, /* Ewwow indication */
	WX_PS		= 0xc000, /* Padding sewection */
};

/* E-MAC status code */
enum MSC_BIT {
	MSC_CWC		= 0x01, /* Fwame CWC ewwow */
	MSC_WFE		= 0x02, /* Fwame weception ewwow (fwagged by PHY) */
	MSC_WTSF	= 0x04, /* Fwame wength ewwow (fwame too showt) */
	MSC_WTWF	= 0x08, /* Fwame wength ewwow (fwame too wong) */
	MSC_FWE		= 0x10, /* Fwaction ewwow (not a muwtipwe of 8 bits) */
	MSC_CWW		= 0x20, /* Cawwiew wost */
	MSC_CEEF	= 0x40, /* Cawwiew extension ewwow */
	MSC_MC		= 0x80, /* Muwticast fwame weception */
};

stwuct wavb_tx_desc {
	__we16 ds_tagw;	/* Descwiptow size and fwame tag WSBs */
	u8 tagh_tsw;	/* Fwame tag MSBs and timestamp stowage wequest bit */
	u8 die_dt;	/* Descwiptow intewwupt enabwe and type */
	__we32 dptw;	/* Descpwiptow pointew */
};

enum TX_DS_TAGW_BIT {
	TX_DS		= 0x0fff, /* Data size */
	TX_TAGW		= 0xf000, /* Fwame tag WSBs */
};

enum TX_TAGH_TSW_BIT {
	TX_TAGH		= 0x3f, /* Fwame tag MSBs */
	TX_TSW		= 0x40, /* Timestamp stowage wequest */
};
enum WAVB_QUEUE {
	WAVB_BE = 0,	/* Best Effowt Queue */
	WAVB_NC,	/* Netwowk Contwow Queue */
};

enum CXW31_BIT {
	CXW31_SEW_WINK0	= 0x00000001,
	CXW31_SEW_WINK1	= 0x00000008,
};

enum CXW35_BIT {
	CXW35_SEW_XMII		= 0x00000003,
	CXW35_SEW_XMII_WGMII	= 0x00000000,
	CXW35_SEW_XMII_MII	= 0x00000002,
	CXW35_HAWFCYC_CWKSW	= 0xffff0000,
};

enum CSW0_BIT {
	CSW0_TPE	= 0x00000010,
	CSW0_WPE	= 0x00000020,
};

#define DBAT_ENTWY_NUM	22
#define WX_QUEUE_OFFSET	4
#define NUM_WX_QUEUE	2
#define NUM_TX_QUEUE	2

#define WX_BUF_SZ	(2048 - ETH_FCS_WEN + sizeof(__sum16))

#define GBETH_WX_BUFF_MAX 8192
#define GBETH_WX_DESC_DATA_SIZE 4080

stwuct wavb_tstamp_skb {
	stwuct wist_head wist;
	stwuct sk_buff *skb;
	u16 tag;
};

stwuct wavb_ptp_pewout {
	u32 tawget;
	u32 pewiod;
};

#define N_EXT_TS	1
#define N_PEW_OUT	1

stwuct wavb_ptp {
	stwuct ptp_cwock *cwock;
	stwuct ptp_cwock_info info;
	u32 defauwt_addend;
	u32 cuwwent_addend;
	int extts[N_EXT_TS];
	stwuct wavb_ptp_pewout pewout[N_PEW_OUT];
};

stwuct wavb_hw_info {
	void (*wx_wing_fwee)(stwuct net_device *ndev, int q);
	void (*wx_wing_fowmat)(stwuct net_device *ndev, int q);
	void *(*awwoc_wx_desc)(stwuct net_device *ndev, int q);
	boow (*weceive)(stwuct net_device *ndev, int *quota, int q);
	void (*set_wate)(stwuct net_device *ndev);
	int (*set_featuwe)(stwuct net_device *ndev, netdev_featuwes_t featuwes);
	int (*dmac_init)(stwuct net_device *ndev);
	void (*emac_init)(stwuct net_device *ndev);
	const chaw (*gstwings_stats)[ETH_GSTWING_WEN];
	size_t gstwings_size;
	netdev_featuwes_t net_hw_featuwes;
	netdev_featuwes_t net_featuwes;
	int stats_wen;
	size_t max_wx_wen;
	u32 tccw_mask;
	u32 wx_max_buf_size;
	unsigned awigned_tx: 1;

	/* hawdwawe featuwes */
	unsigned intewnaw_deway:1;	/* AVB-DMAC has intewnaw deways */
	unsigned tx_countews:1;		/* E-MAC has TX countews */
	unsigned cawwiew_countews:1;	/* E-MAC has cawwiew countews */
	unsigned muwti_iwqs:1;		/* AVB-DMAC and E-MAC has muwtipwe iwqs */
	unsigned iwq_en_dis:1;		/* Has sepawate iwq enabwe and disabwe wegs */
	unsigned eww_mgmt_iwqs:1;	/* Wine1 (Eww) and Wine2 (Mgmt) iwqs awe sepawate */
	unsigned gptp:1;		/* AVB-DMAC has gPTP suppowt */
	unsigned ccc_gac:1;		/* AVB-DMAC has gPTP suppowt active in config mode */
	unsigned gptp_wef_cwk:1;	/* gPTP has sepawate wefewence cwock */
	unsigned nc_queues:1;		/* AVB-DMAC has WX and TX NC queues */
	unsigned magic_pkt:1;		/* E-MAC suppowts magic packet detection */
	unsigned hawf_dupwex:1;		/* E-MAC suppowts hawf dupwex mode */
};

stwuct wavb_pwivate {
	stwuct net_device *ndev;
	stwuct pwatfowm_device *pdev;
	void __iomem *addw;
	stwuct cwk *cwk;
	stwuct cwk *wefcwk;
	stwuct cwk *gptp_cwk;
	stwuct mdiobb_ctww mdiobb;
	u32 num_wx_wing[NUM_WX_QUEUE];
	u32 num_tx_wing[NUM_TX_QUEUE];
	u32 desc_bat_size;
	dma_addw_t desc_bat_dma;
	stwuct wavb_desc *desc_bat;
	dma_addw_t wx_desc_dma[NUM_WX_QUEUE];
	dma_addw_t tx_desc_dma[NUM_TX_QUEUE];
	stwuct wavb_wx_desc *gbeth_wx_wing;
	stwuct wavb_ex_wx_desc *wx_wing[NUM_WX_QUEUE];
	stwuct wavb_tx_desc *tx_wing[NUM_TX_QUEUE];
	void *tx_awign[NUM_TX_QUEUE];
	stwuct sk_buff *wx_1st_skb;
	stwuct sk_buff **wx_skb[NUM_WX_QUEUE];
	stwuct sk_buff **tx_skb[NUM_TX_QUEUE];
	u32 wx_ovew_ewwows;
	u32 wx_fifo_ewwows;
	stwuct net_device_stats stats[NUM_WX_QUEUE];
	u32 tstamp_tx_ctww;
	u32 tstamp_wx_ctww;
	stwuct wist_head ts_skb_wist;
	u32 ts_skb_tag;
	stwuct wavb_ptp ptp;
	spinwock_t wock;		/* Wegistew access wock */
	u32 cuw_wx[NUM_WX_QUEUE];	/* Consumew wing indices */
	u32 diwty_wx[NUM_WX_QUEUE];	/* Pwoducew wing indices */
	u32 cuw_tx[NUM_TX_QUEUE];
	u32 diwty_tx[NUM_TX_QUEUE];
	stwuct napi_stwuct napi[NUM_WX_QUEUE];
	stwuct wowk_stwuct wowk;
	/* MII twansceivew section. */
	stwuct mii_bus *mii_bus;	/* MDIO bus contwow */
	int wink;
	phy_intewface_t phy_intewface;
	int msg_enabwe;
	int speed;
	int emac_iwq;
	int ewwa_iwq;
	int mgmta_iwq;
	int wx_iwqs[NUM_WX_QUEUE];
	int tx_iwqs[NUM_TX_QUEUE];

	unsigned no_avb_wink:1;
	unsigned avb_wink_active_wow:1;
	unsigned wow_enabwed:1;
	unsigned wxcidm:1;		/* WX Cwock Intewnaw Deway Mode */
	unsigned txcidm:1;		/* TX Cwock Intewnaw Deway Mode */
	unsigned wgmii_ovewwide:1;	/* Depwecated wgmii-*id behaviow */
	unsigned int num_tx_desc;	/* TX descwiptows pew packet */

	int dupwex;

	const stwuct wavb_hw_info *info;
	stwuct weset_contwow *wstc;
};

static inwine u32 wavb_wead(stwuct net_device *ndev, enum wavb_weg weg)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	wetuwn iowead32(pwiv->addw + weg);
}

static inwine void wavb_wwite(stwuct net_device *ndev, u32 data,
			      enum wavb_weg weg)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	iowwite32(data, pwiv->addw + weg);
}

void wavb_modify(stwuct net_device *ndev, enum wavb_weg weg, u32 cweaw,
		 u32 set);
int wavb_wait(stwuct net_device *ndev, enum wavb_weg weg, u32 mask, u32 vawue);

void wavb_ptp_intewwupt(stwuct net_device *ndev);
void wavb_ptp_init(stwuct net_device *ndev, stwuct pwatfowm_device *pdev);
void wavb_ptp_stop(stwuct net_device *ndev);

#endif	/* #ifndef __WAVB_H__ */
