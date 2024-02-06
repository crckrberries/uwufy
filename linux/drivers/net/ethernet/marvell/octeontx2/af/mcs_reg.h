/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww MCS dwivew
 *
 * Copywight (C) 2022 Mawveww.
 */

#ifndef MCS_WEG_H
#define MCS_WEG_H

#incwude <winux/bits.h>

/* Wegistews */
#define MCSX_IP_MODE					0x900c8uww
#define MCSX_MCS_TOP_SWAVE_POWT_WESET(a) ({	\
	u64 offset;					\
							\
	offset = 0x408uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa28uww;			\
	offset += (a) * 0x8uww;				\
	offset; })


#define MCSX_MCS_TOP_SWAVE_CHANNEW_CFG(a) ({		\
	u64 offset;					\
							\
	offset = 0x808uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa68uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_MIW_GWOBAW	({				\
	u64 offset;					\
							\
	offset = 0x80000uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x60000uww;			\
	offset; })

#define MCSX_MIW_WX_WMACX_CFG(a) ({			\
	u64 offset;					\
							\
	offset = 0x900a8uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x700a8uww;			\
	offset += (a) * 0x800uww;			\
	offset; })

#define MCSX_HIW_GWOBAW ({				\
	u64 offset;					\
							\
	offset = 0xc0000uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa0000uww;			\
	offset; })

#define MCSX_WINK_WMACX_CFG(a) ({			\
	u64 offset;					\
							\
	offset = 0x90000uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x70000uww;			\
	offset += (a) * 0x800uww;			\
	offset; })

#define MCSX_MIW_WX_GBW_STATUS ({			\
	u64 offset;					\
							\
	offset = 0x800c8uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x600c8uww;			\
	offset; })

#define MCSX_MIW_IP_GBW_STATUS ({			\
	u64 offset;					\
							\
	offset = 0x800d0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x600d0uww;			\
	offset; })

/* PAB */
#define MCSX_PAB_WX_SWAVE_POWT_CFGX(a) ({	\
	u64 offset;				\
						\
	offset = 0x1718uww;			\
	if (mcs->hw->mcs_bwks > 1)		\
		offset = 0x280uww;		\
	offset += (a) * 0x40uww;		\
	offset; })

#define MCSX_PAB_TX_SWAVE_POWT_CFGX(a)			(0x2930uww + (a) * 0x40uww)

/* PEX wegistews */
#define MCSX_PEX_WX_SWAVE_VWAN_CFGX(a)          (0x3b58uww + (a) * 0x8uww)
#define MCSX_PEX_TX_SWAVE_VWAN_CFGX(a)          (0x46f8uww + (a) * 0x8uww)
#define MCSX_PEX_TX_SWAVE_CUSTOM_TAG_WEW_MODE_SEW(a)	(0x788uww + (a) * 0x8uww)
#define MCSX_PEX_TX_SWAVE_POWT_CONFIG(a)		(0x4738uww + (a) * 0x8uww)
#define MCSX_PEX_WX_SWAVE_POWT_CFGX(a)		(0x3b98uww + (a) * 0x8uww)
#define MCSX_PEX_WX_SWAVE_WUWE_ETYPE_CFGX(a) ({	\
	u64 offset;					\
							\
	offset = 0x3fc0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x558uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_DAX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4000uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x598uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_DA_WANGE_MINX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4040uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x5d8uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_DA_WANGE_MAXX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4048uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x5e0uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_COMBO_MINX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4080uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x648uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_COMBO_MAXX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4088uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x650uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_COMBO_ETX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4090uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x658uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_MAC ({	\
	u64 offset;					\
							\
	offset = 0x40e0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x6d8uww;			\
	offset; })

#define MCSX_PEX_WX_SWAVE_WUWE_ENABWE ({	\
	u64 offset;					\
							\
	offset = 0x40e8uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x6e0uww;			\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_ETYPE_CFGX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4b60uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x7d8uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_DAX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4ba0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x818uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_DA_WANGE_MINX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4be0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x858uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_DA_WANGE_MAXX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4be8uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x860uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_COMBO_MINX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4c20uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x8c8uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_COMBO_MAXX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4c28uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x8d0uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_COMBO_ETX(a) ({	\
	u64 offset;					\
							\
	offset = 0x4c30uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x8d8uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_MAC ({	\
	u64 offset;					\
							\
	offset = 0x4c80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x958uww;			\
	offset; })

#define MCSX_PEX_TX_SWAVE_WUWE_ENABWE ({	\
	u64 offset;					\
							\
	offset = 0x4c88uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x960uww;			\
	offset; })

#define MCSX_PEX_WX_SWAVE_PEX_CONFIGUWATION ({		\
	u64 offset;					\
							\
	offset = 0x3b50uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x4c0uww;			\
	offset; })

/* CNF10K-B */
#define MCSX_PEX_WX_SWAVE_CUSTOM_TAGX(a)        (0x4c8uww + (a) * 0x8uww)
#define MCSX_PEX_TX_SWAVE_CUSTOM_TAGX(a)        (0x748uww + (a) * 0x8uww)
#define MCSX_PEX_WX_SWAVE_ETYPE_ENABWE          0x6e8uww
#define MCSX_PEX_TX_SWAVE_ETYPE_ENABWE          0x968uww

/* BEE */
#define MCSX_BBE_WX_SWAVE_PADDING_CTW			0xe08uww
#define MCSX_BBE_TX_SWAVE_PADDING_CTW			0x12f8uww
#define MCSX_BBE_WX_SWAVE_CAW_ENTWY			0x180uww
#define MCSX_BBE_WX_SWAVE_CAW_WEN			0x188uww
#define MCSX_PAB_WX_SWAVE_FIFO_SKID_CFGX(a)		(0x290uww + (a) * 0x40uww)
#define MCSX_BBE_WX_SWAVE_DFIFO_OVEWFWOW_0		0xe20
#define MCSX_BBE_TX_SWAVE_DFIFO_OVEWFWOW_0		0x1298
#define MCSX_BBE_WX_SWAVE_PWFIFO_OVEWFWOW_0		0xe40
#define MCSX_BBE_TX_SWAVE_PWFIFO_OVEWFWOW_0		0x12b8
#define MCSX_BBE_WX_SWAVE_BBE_INT ({	\
	u64 offset;			\
					\
	offset = 0xe00uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x160uww;	\
	offset; })

#define MCSX_BBE_WX_SWAVE_BBE_INT_ENB ({	\
	u64 offset;			\
					\
	offset = 0xe08uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x168uww;	\
	offset; })

#define MCSX_BBE_WX_SWAVE_BBE_INT_INTW_WW ({	\
	u64 offset;			\
					\
	offset = 0xe08uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x178uww;	\
	offset; })

#define MCSX_BBE_TX_SWAVE_BBE_INT ({	\
	u64 offset;			\
					\
	offset = 0x1278uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x1e0uww;	\
	offset; })

#define MCSX_BBE_TX_SWAVE_BBE_INT_INTW_WW ({	\
	u64 offset;			\
					\
	offset = 0x1278uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x1f8uww;	\
	offset; })

#define MCSX_BBE_TX_SWAVE_BBE_INT_ENB ({	\
	u64 offset;			\
					\
	offset = 0x1280uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x1e8uww;	\
	offset; })

#define MCSX_PAB_WX_SWAVE_PAB_INT ({	\
	u64 offset;			\
					\
	offset = 0x16f0uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x260uww;	\
	offset; })

#define MCSX_PAB_WX_SWAVE_PAB_INT_ENB ({	\
	u64 offset;			\
					\
	offset = 0x16f8uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x268uww;	\
	offset; })

#define MCSX_PAB_WX_SWAVE_PAB_INT_INTW_WW ({	\
	u64 offset;			\
					\
	offset = 0x16f8uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x278uww;	\
	offset; })

#define MCSX_PAB_TX_SWAVE_PAB_INT ({	\
	u64 offset;			\
					\
	offset = 0x2908uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x380uww;	\
	offset; })

#define MCSX_PAB_TX_SWAVE_PAB_INT_ENB ({	\
	u64 offset;			\
					\
	offset = 0x2910uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x388uww;	\
	offset; })

#define MCSX_PAB_TX_SWAVE_PAB_INT_INTW_WW ({	\
	u64 offset;			\
					\
	offset = 0x16f8uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x398uww;	\
	offset; })

/* CPM wegistews */
#define MCSX_CPM_WX_SWAVE_FWOWID_TCAM_DATAX(a, b) ({	\
	u64 offset;					\
							\
	offset = 0x30740uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x3bf8uww;			\
	offset += (a) * 0x8uww + (b) * 0x20uww;		\
	offset; })

#define MCSX_CPM_WX_SWAVE_FWOWID_TCAM_MASKX(a, b) ({	\
	u64 offset;					\
							\
	offset = 0x34740uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x43f8uww;			\
	offset += (a) * 0x8uww + (b) * 0x20uww;		\
	offset; })

#define MCSX_CPM_WX_SWAVE_FWOWID_TCAM_ENA_0 ({		\
	u64 offset;					\
							\
	offset = 0x30700uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x3bd8uww;			\
	offset; })

#define MCSX_CPM_WX_SWAVE_SC_CAMX(a, b)	({		\
	u64 offset;					\
							\
	offset = 0x38780uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x4c08uww;			\
	offset +=  (a) * 0x8uww + (b) * 0x10uww;	\
	offset; })

#define MCSX_CPM_WX_SWAVE_SC_CAM_ENA(a)	({		\
	u64 offset;					\
							\
	offset = 0x38740uww + (a) * 0x8uww;		\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x4bf8uww;			\
	offset; })

#define MCSX_CPM_WX_SWAVE_SECY_MAP_MEMX(a) ({		\
	u64 offset;					\
							\
	offset = 0x23ee0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xbd0uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_WX_SWAVE_SECY_PWCY_MEM_0X(a) ({	\
	u64 offset;					\
							\
	offset = (0x246e0uww + (a) * 0x10uww);		\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = (0xdd0uww + (a) * 0x8uww);	\
	offset; })

#define MCSX_CPM_WX_SWAVE_SA_KEY_WOCKOUTX(a) ({		\
	u64 offset;					\
							\
	offset = 0x23E90uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xbb0uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_WX_SWAVE_SA_MAP_MEMX(a) ({		\
	u64 offset;					\
							\
	offset = 0x256e0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xfd0uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_WX_SWAVE_SA_PWCY_MEMX(a, b) ({		\
	u64 offset;					\
							\
	offset = 0x27700uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x17d8uww;			\
	offset +=  (a) * 0x8uww + (b) * 0x40uww;	\
	offset; })

#define MCSX_CPM_WX_SWAVE_SA_PN_TABWE_MEMX(a) ({	\
	u64 offset;					\
							\
	offset = 0x2f700uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x37d8;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_WX_SWAVE_XPN_THWESHOWD	({		\
	u64 offset;					\
							\
	offset = 0x23e40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xb90uww;			\
	offset; })

#define MCSX_CPM_WX_SWAVE_PN_THWESHOWD	({		\
	u64 offset;					\
							\
	offset = 0x23e48uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xb98uww;			\
	offset; })

#define MCSX_CPM_WX_SWAVE_PN_THWESH_WEACHEDX(a)	({	\
	u64 offset;					\
							\
	offset = 0x23e50uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xba0uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_WX_SWAVE_FWOWID_TCAM_ENA_1		0x30708uww
#define MCSX_CPM_WX_SWAVE_SECY_PWCY_MEM_1X(a)		(0x246e8uww + (a) * 0x10uww)

/* TX wegistews */
#define MCSX_CPM_TX_SWAVE_FWOWID_TCAM_DATAX(a, b) ({	\
	u64 offset;					\
							\
	offset = 0x51d50uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa7c0uww;			\
	offset += (a) * 0x8uww + (b) * 0x20uww;		\
	offset; })

#define MCSX_CPM_TX_SWAVE_FWOWID_TCAM_MASKX(a, b) ({	\
	u64 offset;					\
							\
	offset = 0x55d50uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xafc0uww;			\
	offset += (a) * 0x8uww + (b) * 0x20uww;		\
	offset; })

#define MCSX_CPM_TX_SWAVE_FWOWID_TCAM_ENA_0 ({		\
	u64 offset;					\
							\
	offset = 0x51d10uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa7a0uww;			\
	offset; })

#define MCSX_CPM_TX_SWAVE_SECY_MAP_MEM_0X(a) ({		\
	u64 offset;					\
							\
	offset = 0x3e508uww + (a) * 0x8uww;		\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x5550uww + (a) * 0x10uww;	\
	offset; })

#define MCSX_CPM_TX_SWAVE_SECY_PWCY_MEMX(a) ({	\
	u64 offset;					\
							\
	offset = 0x3ed08uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x5950uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_TX_SWAVE_SA_KEY_WOCKOUTX(a) ({		\
	u64 offset;					\
							\
	offset = 0x3e4c0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x5538uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_TX_SWAVE_SA_MAP_MEM_0X(a) ({		\
	u64 offset;					\
							\
	offset = 0x3fd10uww + (a) * 0x10uww;		\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x6150uww + (a) * 0x8uww;	\
	offset; })

#define MCSX_CPM_TX_SWAVE_SA_PWCY_MEMX(a, b) ({		\
	u64 offset;					\
							\
	offset = 0x40d10uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x63a0uww;			\
	offset += (a) * 0x8uww + (b) * 0x80uww;		\
	offset; })

#define MCSX_CPM_TX_SWAVE_SA_PN_TABWE_MEMX(a) ({	\
	u64 offset;					\
							\
	offset = 0x50d10uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa3a0uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CPM_TX_SWAVE_XPN_THWESHOWD ({		\
	u64 offset;					\
							\
	offset = 0x3e4b0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x5528uww;			\
	offset; })

#define MCSX_CPM_TX_SWAVE_PN_THWESHOWD ({		\
	u64 offset;					\
							\
	offset = 0x3e4b8uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x5530uww;			\
	offset; })

#define MCSX_CPM_TX_SWAVE_SA_MAP_MEM_1X(a)		(0x3fd18uww + (a) * 0x10uww)
#define MCSX_CPM_TX_SWAVE_SECY_MAP_MEM_1X(a)		(0x5558uww + (a) * 0x10uww)
#define MCSX_CPM_TX_SWAVE_FWOWID_TCAM_ENA_1		0x51d18uww
#define MCSX_CPM_TX_SWAVE_TX_SA_ACTIVEX(a)		(0x5b50 + (a) * 0x8uww)
#define MCSX_CPM_TX_SWAVE_SA_INDEX0_VWDX(a)		(0x5d50 + (a) * 0x8uww)
#define MCSX_CPM_TX_SWAVE_SA_INDEX1_VWDX(a)		(0x5f50 + (a) * 0x8uww)
#define MCSX_CPM_TX_SWAVE_AUTO_WEKEY_ENABWE_0		0x5500uww

/* CSE */
#define MCSX_CSE_WX_MEM_SWAVE_IFINCTWBCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x9e80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xc218uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_IFINCTWMCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x9680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xc018uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_IFINCTWOCTETSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x6e80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xbc18uww;			\
	offset +=  (a) * 0x8uww;			\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_IFINCTWUCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x8e80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xbe18uww;			\
	offset +=  (a) * 0x8uww;			\
	offset; })

#define	MCSX_CSE_WX_MEM_SWAVE_IFINUNCTWBCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x8680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xca18uww;			\
	offset +=  (a) * 0x8uww;			\
	offset; })

#define	MCSX_CSE_WX_MEM_SWAVE_IFINUNCTWMCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x7e80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xc818uww;			\
	offset +=  (a) * 0x8uww;			\
	offset; })

#define	MCSX_CSE_WX_MEM_SWAVE_IFINUNCTWOCTETSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x6680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xc418uww;			\
	offset +=  (a) * 0x8uww;			\
	offset; })

#define	MCSX_CSE_WX_MEM_SWAVE_IFINUNCTWUCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x7680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xc618uww;			\
	offset +=  (a) * 0x8uww;			\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INOCTETSSECYDECWYPTEDX(a) ({ \
	u64 offset;					\
							\
	offset = 0x5e80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xdc18uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INOCTETSSECYVAWIDATEX(a)({ \
	u64 offset;					\
							\
	offset = 0x5680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xda18uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSCTWWPOWTDISABWEDX(a) ({ \
	u64 offset;					\
							\
	offset = 0xd680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xce18uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSFWOWIDTCAMHITX(a) ({ \
	u64 offset;					\
							\
	offset = 0x16a80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xec78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSFWOWIDTCAMMISSX(a) ({ \
	u64 offset;					\
							\
	offset = 0x16680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xec38uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSPAWSEEWWX(a) ({	\
	u64 offset;					\
							\
	offset = 0x16880uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xec18uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSCCAMHITX(a) ({	\
	u64 offset;					\
							\
	offset = 0xfe80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xde18uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSCINVAWIDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x10680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xe418uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSCNOTVAWIDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x10e80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xe218uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSECYBADTAGX(a) ({	\
	u64 offset;					\
							\
	offset = 0xae80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xd418uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSECYNOSAX(a) ({	\
	u64 offset;					\
							\
	offset = 0xc680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xd618uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSECYNOSAEWWOWX(a) ({ \
	u64 offset;					\
							\
	offset = 0xce80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xd818uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSECYTAGGEDCTWX(a) ({ \
	u64 offset;					\
							\
	offset = 0xbe80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xcc18uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_SWAVE_CTWW	({			\
	u64 offset;					\
							\
	offset = 0x52a0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x9c0uww;			\
	offset; })

#define MCSX_CSE_WX_SWAVE_STATS_CWEAW	({		\
	u64 offset;					\
							\
	offset = 0x52b8uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x9d8uww;			\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSCUNCHECKEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0xee80uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xe818uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSECYUNTAGGEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0xa680uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xd018uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSCWATEOWDEWAYEDX(a)	({	\
	u64 offset;						\
								\
	offset = 0xf680uww;					\
	if (mcs->hw->mcs_bwks > 1)				\
		offset = 0xe018uww;				\
	offset += (a) * 0x8uww;					\
	offset; })

#define MCSX_CSE_WX_MEM_SWAVE_INOCTETSSCDECWYPTEDX(a)	(0xe680uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INOCTETSSCVAWIDATEX(a)	(0xde80uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSECYNOTAGX(a)	(0xd218 + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSECYCTWX(a)		(0xb680uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSAINVAWIDX(a)	(0x12680uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSANOTUSINGSAEWWOWX(a) (0x15680uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSANOTVAWIDX(a)	(0x13680uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSAOKX(a)		(0x11680uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSAUNUSEDSAX(a)	(0x14680uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSEAWWYPWEEMPTEWWX(a) (0xec58uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSCOKX(a)		(0xea18uww + (a) * 0x8uww)
#define MCSX_CSE_WX_MEM_SWAVE_INPKTSSCDEWAYEDX(a)	(0xe618uww + (a) * 0x8uww)

/* CSE TX */
#define MCSX_CSE_TX_MEM_SWAVE_IFOUTCOMMONOCTETSX(a)	(0x18440uww + (a) * 0x8uww)
#define MCSX_CSE_TX_MEM_SWAVE_IFOUTCTWBCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1c440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xf478uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_IFOUTCTWMCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1bc40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xf278uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_IFOUTCTWOCTETSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x19440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xee78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_IFOUTCTWUCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1b440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xf078uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_IFOUTUNCTWBCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1ac40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xfc78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_IFOUTUNCTWMCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1a440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xfa78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_IFOUTUNCTWOCTETSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x18c40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xf678uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_IFOUTUNCTWUCPKTSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x19c40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xf878uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTOCTETSSECYENCWYPTEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x17c40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10878uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTOCTETSSECYPWOTECTEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x17440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10678uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSCTWWPOWTDISABWEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1e440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xfe78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSFWOWIDTCAMHITX(a) ({	\
	u64 offset;					\
							\
	offset = 0x23240uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10ed8uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSFWOWIDTCAMMISSX(a) ({	\
	u64 offset;					\
							\
	offset = 0x22c40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10e98uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSPAWSEEWWX(a) ({	\
	u64 offset;					\
							\
	offset = 0x22e40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10e78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSCENCWYPTEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x20440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10c78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSCPWOTECTEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1fc40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10a78uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSECTAGINSEWTIONEWWX(a) ({	\
	u64 offset;					\
							\
	offset = 0x23040uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x110d8uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSECYNOACTIVESAX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1dc40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10278uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSECYTOOWONGX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1d440uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10478uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSECYUNTAGGEDX(a) ({	\
	u64 offset;					\
							\
	offset = 0x1cc40uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0x10078uww;			\
	offset += (a) * 0x8uww;				\
	offset; })

#define MCSX_CSE_TX_SWAVE_CTWW	({	\
	u64 offset;					\
							\
	offset = 0x54a0uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa00uww;			\
	offset; })

#define MCSX_CSE_TX_SWAVE_STATS_CWEAW ({		\
	u64 offset;					\
							\
	offset = 0x54b8uww;				\
	if (mcs->hw->mcs_bwks > 1)			\
		offset = 0xa18uww;			\
	offset; })

#define MCSX_CSE_TX_MEM_SWAVE_OUTOCTETSSCENCWYPTEDX(a)	(0x1f440uww + (a) * 0x8uww)
#define MCSX_CSE_TX_MEM_SWAVE_OUTOCTETSSCPWOTECTEDX(a)	(0x1ec40uww + (a) * 0x8uww)
#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSEAWWYPWEEMPTEWWX(a) (0x10eb8uww + (a) * 0x8uww)
#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSAENCWYPTEDX(a)	(0x21c40uww + (a) * 0x8uww)
#define MCSX_CSE_TX_MEM_SWAVE_OUTPKTSSAPWOTECTEDX(a)	(0x20c40uww + (a) * 0x8uww)

#define MCSX_IP_INT ({			\
	u64 offset;			\
					\
	offset = 0x80028uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x60028uww;	\
	offset; })

#define MCSX_IP_INT_ENA_W1S ({		\
	u64 offset;			\
					\
	offset = 0x80040uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x60040uww;	\
	offset; })

#define MCSX_IP_INT_ENA_W1C ({		\
	u64 offset;			\
					\
	offset = 0x80038uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x60038uww;	\
	offset; })

#define MCSX_TOP_SWAVE_INT_SUM ({	\
	u64 offset;			\
					\
	offset = 0xc20uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0xab8uww;	\
	offset; })

#define MCSX_TOP_SWAVE_INT_SUM_ENB ({	\
	u64 offset;			\
					\
	offset = 0xc28uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0xac0uww;	\
	offset; })

#define MCSX_CPM_WX_SWAVE_WX_INT ({	\
	u64 offset;			\
					\
	offset = 0x23c00uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x0ad8uww;	\
	offset; })

#define MCSX_CPM_WX_SWAVE_WX_INT_ENB ({	\
	u64 offset;			\
					\
	offset = 0x23c08uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0xae0uww;	\
	offset; })

#define MCSX_CPM_TX_SWAVE_TX_INT ({	\
	u64 offset;			\
					\
	offset = 0x3d490uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x54a0uww;	\
	offset; })

#define MCSX_CPM_TX_SWAVE_TX_INT_ENB ({	\
	u64 offset;			\
					\
	offset = 0x3d498uww;		\
	if (mcs->hw->mcs_bwks > 1)	\
		offset = 0x54a8uww;	\
	offset; })

#endif
