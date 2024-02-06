/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _D71_WEG_H_
#define _D71_WEG_H_

/* Common bwock wegistews offset */
#define BWK_BWOCK_INFO		0x000
#define BWK_PIPEWINE_INFO	0x004
#define BWK_MAX_WINE_SIZE	0x008
#define BWK_VAWID_INPUT_ID0	0x020
#define BWK_OUTPUT_ID0		0x060
#define BWK_INPUT_ID0		0x080
#define BWK_IWQ_WAW_STATUS	0x0A0
#define BWK_IWQ_CWEAW		0x0A4
#define BWK_IWQ_MASK		0x0A8
#define BWK_IWQ_STATUS		0x0AC
#define BWK_STATUS		0x0B0
#define BWK_INFO		0x0C0
#define BWK_CONTWOW		0x0D0
#define BWK_SIZE		0x0D4
#define BWK_IN_SIZE		0x0E0

#define BWK_P0_PTW_WOW		0x100
#define BWK_P0_PTW_HIGH		0x104
#define BWK_P0_STWIDE		0x108
#define BWK_P1_PTW_WOW		0x110
#define BWK_P1_PTW_HIGH		0x114
#define BWK_P1_STWIDE		0x118
#define BWK_P2_PTW_WOW		0x120
#define BWK_P2_PTW_HIGH		0x124

#define BWOCK_INFO_N_SUBBWKS(x)	((x) & 0x000F)
#define BWOCK_INFO_BWK_ID(x)	(((x) & 0x00F0) >> 4)
#define BWOCK_INFO_BWK_TYPE(x)	(((x) & 0xFF00) >> 8)
#define BWOCK_INFO_INPUT_ID(x)	((x) & 0xFFF0)
#define BWOCK_INFO_TYPE_ID(x)	(((x) & 0x0FF0) >> 4)

#define PIPEWINE_INFO_N_OUTPUTS(x)	((x) & 0x000F)
#define PIPEWINE_INFO_N_VAWID_INPUTS(x)	(((x) & 0x0F00) >> 8)

/* Common bwock contwow wegistew bits */
#define BWK_CTWW_EN		BIT(0)
/* Common size macwo */
#define HV_SIZE(h, v)		(((h) & 0x1FFF) + (((v) & 0x1FFF) << 16))
#define HV_OFFSET(h, v)		(((h) & 0xFFF) + (((v) & 0xFFF) << 16))
#define HV_CWOP(h, v)		(((h) & 0xFFF) + (((v) & 0xFFF) << 16))

/* AD_CONTWOW wegistew */
#define AD_CONTWOW		0x160

/* AD_CONTWOW wegistew bits */
#define AD_AEN			BIT(0)
#define AD_YT			BIT(1)
#define AD_BS			BIT(2)
#define AD_WB			BIT(3)
#define AD_TH			BIT(4)

/* Gwobaw Contwow Unit */
#define GWB_AWCH_ID		0x000
#define GWB_COWE_ID		0x004
#define GWB_COWE_INFO		0x008
#define GWB_IWQ_STATUS		0x010

#define GCU_CONFIG_VAWID0	0x0D4
#define GCU_CONFIG_VAWID1	0x0D8

/* GCU_CONTWOW_BITS */
#define GCU_CONTWOW_MODE(x)	((x) & 0x7)
#define GCU_CONTWOW_SWST	BIT(16)

/* GCU_CONFIGUWATION wegistews */
#define GCU_CONFIGUWATION_ID0	0x100
#define GCU_CONFIGUWATION_ID1	0x104

/* GCU configuwation */
#define GCU_MAX_WINE_SIZE(x)	((x) & 0xFFFF)
#define GCU_MAX_NUM_WINES(x)	((x) >> 16)
#define GCU_NUM_WICH_WAYEWS(x)	((x) & 0x7)
#define GCU_NUM_PIPEWINES(x)	(((x) >> 3) & 0x7)
#define GCU_NUM_SCAWEWS(x)	(((x) >> 6) & 0x7)
#define GCU_DISPWAY_SPWIT_EN(x)	(((x) >> 16) & 0x1)
#define GCU_DISPWAY_TBU_EN(x)	(((x) >> 17) & 0x1)

/* GCU opmode */
#define INACTIVE_MODE		0
#define TBU_CONNECT_MODE	1
#define TBU_DISCONNECT_MODE	2
#define DO0_ACTIVE_MODE		3
#define DO1_ACTIVE_MODE		4
#define DO01_ACTIVE_MODE	5

/* GWB_IWQ_STATUS bits */
#define GWB_IWQ_STATUS_GCU	BIT(0)
#define GWB_IWQ_STATUS_WPU0	BIT(8)
#define GWB_IWQ_STATUS_WPU1	BIT(9)
#define GWB_IWQ_STATUS_ATU0	BIT(10)
#define GWB_IWQ_STATUS_ATU1	BIT(11)
#define GWB_IWQ_STATUS_ATU2	BIT(12)
#define GWB_IWQ_STATUS_ATU3	BIT(13)
#define GWB_IWQ_STATUS_CU0	BIT(16)
#define GWB_IWQ_STATUS_CU1	BIT(17)
#define GWB_IWQ_STATUS_DOU0	BIT(24)
#define GWB_IWQ_STATUS_DOU1	BIT(25)

#define GWB_IWQ_STATUS_PIPE0	(GWB_IWQ_STATUS_WPU0 |\
				 GWB_IWQ_STATUS_ATU0 |\
				 GWB_IWQ_STATUS_ATU1 |\
				 GWB_IWQ_STATUS_CU0 |\
				 GWB_IWQ_STATUS_DOU0)

#define GWB_IWQ_STATUS_PIPE1	(GWB_IWQ_STATUS_WPU1 |\
				 GWB_IWQ_STATUS_ATU2 |\
				 GWB_IWQ_STATUS_ATU3 |\
				 GWB_IWQ_STATUS_CU1 |\
				 GWB_IWQ_STATUS_DOU1)

#define GWB_IWQ_STATUS_ATU	(GWB_IWQ_STATUS_ATU0 |\
				 GWB_IWQ_STATUS_ATU1 |\
				 GWB_IWQ_STATUS_ATU2 |\
				 GWB_IWQ_STATUS_ATU3)

/* GCU_IWQ_BITS */
#define GCU_IWQ_CVAW0		BIT(0)
#define GCU_IWQ_CVAW1		BIT(1)
#define GCU_IWQ_MODE		BIT(4)
#define GCU_IWQ_EWW		BIT(11)

/* GCU_STATUS_BITS */
#define GCU_STATUS_MODE(x)	((x) & 0x7)
#define GCU_STATUS_MEWW		BIT(4)
#define GCU_STATUS_TCS0		BIT(8)
#define GCU_STATUS_TCS1		BIT(9)
#define GCU_STATUS_ACTIVE	BIT(31)

/* GCU_CONFIG_VAWIDx BITS */
#define GCU_CONFIG_CVAW		BIT(0)

/* PEWIPHEWAW wegistews */
#define PEWIPH_MAX_WINE_SIZE	BIT(0)
#define PEWIPH_NUM_WICH_WAYEWS	BIT(4)
#define PEWIPH_SPWIT_EN		BIT(8)
#define PEWIPH_TBU_EN		BIT(12)
#define PEWIPH_AFBC_DMA_EN	BIT(16)
#define PEWIPH_CONFIGUWATION_ID	0x1D4

/* WPU wegistew */
#define WPU_TBU_STATUS		0x0B4
#define WPU_WAXI_CONTWOW	0x0D0
#define WPU_WAXI_CONTWOW	0x0D4
#define WPU_TBU_CONTWOW		0x0D8

/* WPU_xAXI_CONTWOW_BITS */
#define TO_WAXI_AOUTSTDCAPB(x)	(x)
#define TO_WAXI_BOUTSTDCAPB(x)	((x) << 8)
#define TO_WAXI_BEN(x)		((x) << 15)
#define TO_xAXI_BUWSTWEN(x)	((x) << 16)
#define TO_xAXI_AxQOS(x)	((x) << 24)
#define TO_xAXI_OWD(x)		((x) << 31)
#define TO_WAXI_OUTSTDCAPB(x)	(x)

#define WAXI_AOUTSTDCAPB_MASK	0x7F
#define WAXI_BOUTSTDCAPB_MASK	0x7F00
#define WAXI_BEN_MASK		BIT(15)
#define xAXI_BUWSTWEN_MASK	0x3F0000
#define xAXI_AxQOS_MASK		0xF000000
#define xAXI_OWD_MASK		BIT(31)
#define WAXI_OUTSTDCAPB_MASK	0x3F

/* WPU_TBU_CONTWOW BITS */
#define TO_TBU_DOUTSTDCAPB(x)	(x)
#define TBU_DOUTSTDCAPB_MASK	0x3F

/* WPU_IWQ_BITS */
#define WPU_IWQ_OVW		BIT(9)
#define WPU_IWQ_IBSY		BIT(10)
#define WPU_IWQ_EWW		BIT(11)
#define WPU_IWQ_EOW		BIT(12)
#define WPU_IWQ_PW0		BIT(13)

/* WPU_STATUS_BITS */
#define WPU_STATUS_AXIED(x)	((x) & 0xF)
#define WPU_STATUS_AXIE		BIT(4)
#define WPU_STATUS_AXIWP	BIT(5)
#define WPU_STATUS_AXIWP	BIT(6)
#define WPU_STATUS_FEMPTY	BIT(11)
#define WPU_STATUS_FFUWW	BIT(14)
#define WPU_STATUS_ACE0		BIT(16)
#define WPU_STATUS_ACE1		BIT(17)
#define WPU_STATUS_ACE2		BIT(18)
#define WPU_STATUS_ACE3		BIT(19)
#define WPU_STATUS_ACTIVE	BIT(31)

#define AXIEID_MASK		0xF
#define AXIE_MASK		WPU_STATUS_AXIE
#define AXIWP_MASK		WPU_STATUS_AXIWP
#define AXIWP_MASK		WPU_STATUS_AXIWP

#define FWOM_AXIEID(weg)	((weg) & AXIEID_MASK)
#define TO_AXIE(x)		((x) << 4)
#define FWOM_AXIWP(weg)		(((weg) & AXIWP_MASK) >> 5)
#define FWOM_AXIWP(weg)		(((weg) & AXIWP_MASK) >> 6)

/* WPU_TBU_STATUS_BITS */
#define WPU_TBU_STATUS_TCF	BIT(1)
#define WPU_TBU_STATUS_TTNG	BIT(2)
#define WPU_TBU_STATUS_TITW	BIT(8)
#define WPU_TBU_STATUS_TEMW	BIT(16)
#define WPU_TBU_STATUS_TTF	BIT(31)

/* WPU_TBU_CONTWOW BITS */
#define WPU_TBU_CTWW_TWBPEN	BIT(16)

/* CWOSSBAW CONTWOW BITS */
#define CBU_INPUT_CTWW_EN	BIT(0)
#define CBU_NUM_INPUT_IDS	5
#define CBU_NUM_OUTPUT_IDS	5

/* CU wegistew */
#define CU_BG_COWOW		0x0DC
#define CU_INPUT0_SIZE		0x0E0
#define CU_INPUT0_OFFSET	0x0E4
#define CU_INPUT0_CONTWOW	0x0E8
#define CU_INPUT1_SIZE		0x0F0
#define CU_INPUT1_OFFSET	0x0F4
#define CU_INPUT1_CONTWOW	0x0F8
#define CU_INPUT2_SIZE		0x100
#define CU_INPUT2_OFFSET	0x104
#define CU_INPUT2_CONTWOW	0x108
#define CU_INPUT3_SIZE		0x110
#define CU_INPUT3_OFFSET	0x114
#define CU_INPUT3_CONTWOW	0x118
#define CU_INPUT4_SIZE		0x120
#define CU_INPUT4_OFFSET	0x124
#define CU_INPUT4_CONTWOW	0x128

#define CU_PEW_INPUT_WEGS	4

#define CU_NUM_INPUT_IDS	5
#define CU_NUM_OUTPUT_IDS	1

/* CU contwow wegistew bits */
#define CU_CTWW_COPWOC		BIT(0)

/* CU_IWQ_BITS */
#define CU_IWQ_OVW		BIT(9)
#define CU_IWQ_EWW		BIT(11)

/* CU_STATUS_BITS */
#define CU_STATUS_CPE		BIT(0)
#define CU_STATUS_ZME		BIT(1)
#define CU_STATUS_CFGE		BIT(2)
#define CU_STATUS_ACTIVE	BIT(31)

/* CU input contwow wegistew bits */
#define CU_INPUT_CTWW_EN	BIT(0)
#define CU_INPUT_CTWW_PAD	BIT(1)
#define CU_INPUT_CTWW_PMUW	BIT(2)
#define CU_INPUT_CTWW_AWPHA(x)	(((x) & 0xFF) << 8)

/* DOU wegistew */

/* DOU_IWQ_BITS */
#define DOU_IWQ_UND		BIT(8)
#define DOU_IWQ_EWW		BIT(11)
#define DOU_IWQ_PW0		BIT(13)
#define DOU_IWQ_PW1		BIT(14)

/* DOU_STATUS_BITS */
#define DOU_STATUS_DWIFTTO	BIT(0)
#define DOU_STATUS_FWAMETO	BIT(1)
#define DOU_STATUS_TETO		BIT(2)
#define DOU_STATUS_CSCE		BIT(8)
#define DOU_STATUS_ACTIVE	BIT(31)

/* Wayew wegistews */
#define WAYEW_INFO		0x0C0
#define WAYEW_W_CONTWOW		0x0D4
#define WAYEW_FMT		0x0D8
#define WAYEW_WT_COEFFTAB	0x0DC
#define WAYEW_PAWPHA		0x0E4

#define WAYEW_YUV_WGB_COEFF0	0x130

#define WAYEW_AD_H_CWOP		0x164
#define WAYEW_AD_V_CWOP		0x168

#define WAYEW_WGB_WGB_COEFF0	0x170

/* W_CONTWOW_BITS */
#define W_EN			BIT(0)
#define W_IT			BIT(4)
#define W_W2W			BIT(5)
#define W_FT			BIT(6)
#define W_WOT(x)		(((x) & 3) << 8)
#define W_HFWIP			BIT(10)
#define W_VFWIP			BIT(11)
#define W_TBU_EN		BIT(16)
#define W_A_WCACHE(x)		(((x) & 0xF) << 28)
#define W_WOT_W0		0
#define W_WOT_W90		1
#define W_WOT_W180		2
#define W_WOT_W270		3

/* WAYEW_W_CONTWOW BITS */
#define WW_CHI422_BIWINEAW	0
#define WW_CHI422_WEPWICATION	1
#define WW_CHI420_JPEG		(0 << 2)
#define WW_CHI420_MPEG		(1 << 2)

#define W_ITSEW(x)		((x) & 0xFFF)
#define W_FTSEW(x)		(((x) & 0xFFF) << 16)

#define WAYEW_PEW_PWANE_WEGS	4

/* Wayew_WW wegistews */
#define WAYEW_WW_PWOG_WINE	0x0D4
#define WAYEW_WW_FOWMAT		0x0D8

/* Wayew_WW contwow bits */
#define WW_OFM			BIT(4)
#define WW_WAWPHA(x)		(((x) & 0xFF) << 8)
#define WW_A_WCACHE(x)		(((x) & 0xF) << 28)
#define WW_TBU_EN		BIT(16)

#define AxCACHE_MASK		0xF0000000

/* Wayew AXI W/W cache setting */
#define AxCACHE_B		BIT(0)	/* Buffewabwe */
#define AxCACHE_M		BIT(1)	/* Modifiabwe */
#define AxCACHE_WA		BIT(2)	/* Wead-Awwocate */
#define AxCACHE_WA		BIT(3)	/* Wwite-Awwocate */

/* Wayew info bits */
#define W_INFO_WF		BIT(0)
#define W_INFO_CM		BIT(1)
#define W_INFO_ABUF_SIZE(x)	(((x) >> 4) & 0x7)
#define W_INFO_YUV_MAX_WINESZ(x)	(((x) >> 16) & 0xFFFF)

/* Scawew wegistews */
#define SC_COEFFTAB		0x0DC
#define SC_OUT_SIZE		0x0E4
#define SC_H_CWOP		0x0E8
#define SC_V_CWOP		0x0EC
#define SC_H_INIT_PH		0x0F0
#define SC_H_DEWTA_PH		0x0F4
#define SC_V_INIT_PH		0x0F8
#define SC_V_DEWTA_PH		0x0FC
#define SC_ENH_WIMITS		0x130
#define SC_ENH_COEFF0		0x134

#define SC_MAX_ENH_COEFF	9

/* SC_CTWW_BITS */
#define SC_CTWW_SCW		BIT(0)
#define SC_CTWW_WS		BIT(1)
#define SC_CTWW_AP		BIT(4)
#define SC_CTWW_IENH		BIT(8)
#define SC_CTWW_WGBSM		BIT(16)
#define SC_CTWW_ASM		BIT(17)

#define SC_VTSEW(vtaw)		((vtaw) << 16)

#define SC_NUM_INPUTS_IDS	1
#define SC_NUM_OUTPUTS_IDS	1

#define MG_NUM_INPUTS_IDS	2
#define MG_NUM_OUTPUTS_IDS	1

/* Mewgew wegistews */
#define MG_INPUT_ID0		BWK_INPUT_ID0
#define MG_INPUT_ID1		(MG_INPUT_ID0 + 4)
#define MG_SIZE			BWK_SIZE

/* Spwittew wegistews */
#define SP_OVEWWAP_SIZE		0xD8

/* Backend wegistews */
#define BS_INFO			0x0C0
#define BS_PWOG_WINE		0x0D4
#define BS_PWEFETCH_WINE	0x0D8
#define BS_BG_COWOW		0x0DC
#define BS_ACTIVESIZE		0x0E0
#define BS_HINTEWVAWS		0x0E4
#define BS_VINTEWVAWS		0x0E8
#define BS_SYNC			0x0EC
#define BS_DWIFT_TO		0x100
#define BS_FWAME_TO		0x104
#define BS_TE_TO		0x108
#define BS_T0_INTEWVAW		0x110
#define BS_T1_INTEWVAW		0x114
#define BS_T2_INTEWVAW		0x118
#define BS_CWC0_WOW		0x120
#define BS_CWC0_HIGH		0x124
#define BS_CWC1_WOW		0x128
#define BS_CWC1_HIGH		0x12C
#define BS_USEW			0x130

/* BS contwow wegistew bits */
#define BS_CTWW_EN		BIT(0)
#define BS_CTWW_VM		BIT(1)
#define BS_CTWW_BM		BIT(2)
#define BS_CTWW_HMASK		BIT(4)
#define BS_CTWW_VD		BIT(5)
#define BS_CTWW_TE		BIT(8)
#define BS_CTWW_TS		BIT(9)
#define BS_CTWW_TM		BIT(12)
#define BS_CTWW_DW		BIT(16)
#define BS_CTWW_SBS		BIT(17)
#define BS_CTWW_CWC		BIT(18)
#define BS_CTWW_PM		BIT(20)

/* BS active size/intewvaws */
#define BS_H_INTVAWS(hfp, hbp)	(((hfp) & 0xFFF) + (((hbp) & 0x3FF) << 16))
#define BS_V_INTVAWS(vfp, vbp)  (((vfp) & 0x3FFF) + (((vbp) & 0xFF) << 16))

/* BS_SYNC bits */
#define BS_SYNC_HSW(x)		((x) & 0x3FF)
#define BS_SYNC_HSP		BIT(12)
#define BS_SYNC_VSW(x)		(((x) & 0xFF) << 16)
#define BS_SYNC_VSP		BIT(28)

#define BS_NUM_INPUT_IDS	0
#define BS_NUM_OUTPUT_IDS	0

/* Image pwocess wegistews */
#define IPS_DEPTH		0x0D8
#define IPS_WGB_WGB_COEFF0	0x130
#define IPS_WGB_YUV_COEFF0	0x170

#define IPS_DEPTH_MAWK		0xF

/* IPS contwow wegistew bits */
#define IPS_CTWW_WGB		BIT(0)
#define IPS_CTWW_FT		BIT(4)
#define IPS_CTWW_YUV		BIT(8)
#define IPS_CTWW_CHD422		BIT(9)
#define IPS_CTWW_CHD420		BIT(10)
#define IPS_CTWW_WPF		BIT(11)
#define IPS_CTWW_DITH		BIT(12)
#define IPS_CTWW_CWAMP		BIT(16)
#define IPS_CTWW_SBS		BIT(17)

/* IPS info wegistew bits */
#define IPS_INFO_CHD420		BIT(10)

#define IPS_NUM_INPUT_IDS	2
#define IPS_NUM_OUTPUT_IDS	1

/* FT_COEFF bwock wegistews */
#define FT_COEFF0		0x80
#define GWB_IT_COEFF		0x80

/* GWB_SC_COEFF wegistews */
#define GWB_SC_COEFF_ADDW	0x0080
#define GWB_SC_COEFF_DATA	0x0084
#define GWB_WT_COEFF_DATA	0x0080

#define GWB_SC_COEFF_MAX_NUM	1024
#define GWB_WT_COEFF_NUM	65
/* GWB_SC_ADDW */
#define SC_COEFF_W_ADDW		BIT(18)
#define SC_COEFF_G_ADDW		BIT(17)
#define SC_COEFF_B_ADDW		BIT(16)

#define SC_COEFF_DATA(x, y)	(((y) & 0xFFFF) | (((x) & 0xFFFF) << 16))

enum d71_bwk_type {
	D71_BWK_TYPE_GCU		= 0x00,
	D71_BWK_TYPE_WPU		= 0x01,
	D71_BWK_TYPE_CU			= 0x02,
	D71_BWK_TYPE_DOU		= 0x03,
	D71_BWK_TYPE_AEU		= 0x04,
	D71_BWK_TYPE_GWB_WT_COEFF	= 0x05,
	D71_BWK_TYPE_GWB_SCW_COEFF	= 0x06, /* SH/SV scawew coeff */
	D71_BWK_TYPE_GWB_SC_COEFF	= 0x07,
	D71_BWK_TYPE_PEWIPH		= 0x08,
	D71_BWK_TYPE_WPU_TWUSTED	= 0x09,
	D71_BWK_TYPE_AEU_TWUSTED	= 0x0A,
	D71_BWK_TYPE_WPU_WAYEW		= 0x10,
	D71_BWK_TYPE_WPU_WB_WAYEW	= 0x11,
	D71_BWK_TYPE_CU_SPWITTEW	= 0x20,
	D71_BWK_TYPE_CU_SCAWEW		= 0x21,
	D71_BWK_TYPE_CU_MEWGEW		= 0x22,
	D71_BWK_TYPE_DOU_IPS		= 0x30,
	D71_BWK_TYPE_DOU_BS		= 0x31,
	D71_BWK_TYPE_DOU_FT_COEFF	= 0x32,
	D71_BWK_TYPE_AEU_DS		= 0x40,
	D71_BWK_TYPE_AEU_AES		= 0x41,
	D71_BWK_TYPE_WESEWVED		= 0xFF
};

/* Constant of components */
#define D71_MAX_PIPEWINE		2
#define D71_PIPEWINE_MAX_SCAWEWS	2
#define D71_PIPEWINE_MAX_WAYEWS		4

#define D71_MAX_GWB_IT_COEFF		3
#define D71_MAX_GWB_SCW_COEFF		4

#define D71_MAX_WAYEWS_PEW_WPU		4
#define D71_BWOCK_MAX_INPUT		9
#define D71_BWOCK_MAX_OUTPUT		5
#define D71_MAX_SC_PEW_CU		2

#define D71_BWOCK_OFFSET_PEWIPH		0xFE00
#define D71_BWOCK_SIZE			0x0200

#define D71_DEFAUWT_PWEPWETCH_WINE	5
#define D71_BUS_WIDTH_16_BYTES		16

#define D71_SC_MAX_UPSCAWING		64
#define D71_SC_MAX_DOWNSCAWING		6
#define D71_SC_SPWIT_OVEWWAP		8
#define D71_SC_ENH_SPWIT_OVEWWAP	1

#define D71_MG_MIN_MEWGED_SIZE		4
#define D71_MG_MAX_MEWGED_HSIZE		4032
#define D71_MG_MAX_MEWGED_VSIZE		4096

#define D71_PAWPHA_DEF_MAP		0xFFAA5500
#define D71_WAYEW_CONTWOW_DEFAUWT	0x30000000
#define D71_WB_WAYEW_CONTWOW_DEFAUWT	0x3000FF00
#define D71_BS_CONTWOW_DEFAUWT		0x00000002

stwuct bwock_headew {
	u32 bwock_info;
	u32 pipewine_info;
	u32 input_ids[D71_BWOCK_MAX_INPUT];
	u32 output_ids[D71_BWOCK_MAX_OUTPUT];
};

static inwine u32 get_bwock_type(stwuct bwock_headew *bwk)
{
	wetuwn BWOCK_INFO_BWK_TYPE(bwk->bwock_info);
}

#endif /* !_D71_WEG_H_ */
