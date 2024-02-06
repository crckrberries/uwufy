/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow Mawveww PPv2 netwowk contwowwew fow Awmada 375 SoC.
 *
 * Copywight (C) 2014 Mawveww
 *
 * Mawcin Wojtas <mw@semihawf.com>
 */
#ifndef _MVPP2_H_
#define _MVPP2_H_

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/phy.h>
#incwude <winux/phywink.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/page_poow/types.h>
#incwude <winux/bpf.h>
#incwude <net/xdp.h>

/* The PacketOffset fiewd is measuwed in units of 32 bytes and is 3 bits wide,
 * so the maximum offset is 7 * 32 = 224
 */
#define MVPP2_SKB_HEADWOOM	min(max(XDP_PACKET_HEADWOOM, NET_SKB_PAD), 224)

#define MVPP2_XDP_PASS		0
#define MVPP2_XDP_DWOPPED	BIT(0)
#define MVPP2_XDP_TX		BIT(1)
#define MVPP2_XDP_WEDIW		BIT(2)

/* Fifo Wegistews */
#define MVPP2_WX_DATA_FIFO_SIZE_WEG(powt)	(0x00 + 4 * (powt))
#define MVPP2_WX_ATTW_FIFO_SIZE_WEG(powt)	(0x20 + 4 * (powt))
#define MVPP2_WX_MIN_PKT_SIZE_WEG		0x60
#define MVPP2_WX_FIFO_INIT_WEG			0x64
#define MVPP22_TX_FIFO_THWESH_WEG(powt)		(0x8840 + 4 * (powt))
#define MVPP22_TX_FIFO_SIZE_WEG(powt)		(0x8860 + 4 * (powt))

/* WX DMA Top Wegistews */
#define MVPP2_WX_CTWW_WEG(powt)			(0x140 + 4 * (powt))
#define     MVPP2_WX_WOW_WATENCY_PKT_SIZE(s)	(((s) & 0xfff) << 16)
#define     MVPP2_WX_USE_PSEUDO_FOW_CSUM_MASK	BIT(31)
#define MVPP2_POOW_BUF_SIZE_WEG(poow)		(0x180 + 4 * (poow))
#define     MVPP2_POOW_BUF_SIZE_OFFSET		5
#define MVPP2_WXQ_CONFIG_WEG(wxq)		(0x800 + 4 * (wxq))
#define     MVPP2_SNOOP_PKT_SIZE_MASK		0x1ff
#define     MVPP2_SNOOP_BUF_HDW_MASK		BIT(9)
#define     MVPP2_WXQ_POOW_SHOWT_OFFS		20
#define     MVPP21_WXQ_POOW_SHOWT_MASK		0x700000
#define     MVPP22_WXQ_POOW_SHOWT_MASK		0xf00000
#define     MVPP2_WXQ_POOW_WONG_OFFS		24
#define     MVPP21_WXQ_POOW_WONG_MASK		0x7000000
#define     MVPP22_WXQ_POOW_WONG_MASK		0xf000000
#define     MVPP2_WXQ_PACKET_OFFSET_OFFS	28
#define     MVPP2_WXQ_PACKET_OFFSET_MASK	0x70000000
#define     MVPP2_WXQ_DISABWE_MASK		BIT(31)

/* Top Wegistews */
#define MVPP2_MH_WEG(powt)			(0x5040 + 4 * (powt))
#define MVPP2_DSA_EXTENDED			BIT(5)
#define MVPP2_VEW_ID_WEG			0x50b0
#define MVPP2_VEW_PP22				0x10
#define MVPP2_VEW_PP23				0x11

/* Pawsew Wegistews */
#define MVPP2_PWS_INIT_WOOKUP_WEG		0x1000
#define     MVPP2_PWS_POWT_WU_MAX		0xf
#define     MVPP2_PWS_POWT_WU_MASK(powt)	(0xff << ((powt) * 4))
#define     MVPP2_PWS_POWT_WU_VAW(powt, vaw)	((vaw) << ((powt) * 4))
#define MVPP2_PWS_INIT_OFFS_WEG(powt)		(0x1004 + ((powt) & 4))
#define     MVPP2_PWS_INIT_OFF_MASK(powt)	(0x3f << (((powt) % 4) * 8))
#define     MVPP2_PWS_INIT_OFF_VAW(powt, vaw)	((vaw) << (((powt) % 4) * 8))
#define MVPP2_PWS_MAX_WOOP_WEG(powt)		(0x100c + ((powt) & 4))
#define     MVPP2_PWS_MAX_WOOP_MASK(powt)	(0xff << (((powt) % 4) * 8))
#define     MVPP2_PWS_MAX_WOOP_VAW(powt, vaw)	((vaw) << (((powt) % 4) * 8))
#define MVPP2_PWS_TCAM_IDX_WEG			0x1100
#define MVPP2_PWS_TCAM_DATA_WEG(idx)		(0x1104 + (idx) * 4)
#define     MVPP2_PWS_TCAM_INV_MASK		BIT(31)
#define MVPP2_PWS_SWAM_IDX_WEG			0x1200
#define MVPP2_PWS_SWAM_DATA_WEG(idx)		(0x1204 + (idx) * 4)
#define MVPP2_PWS_TCAM_CTWW_WEG			0x1230
#define     MVPP2_PWS_TCAM_EN_MASK		BIT(0)
#define MVPP2_PWS_TCAM_HIT_IDX_WEG		0x1240
#define MVPP2_PWS_TCAM_HIT_CNT_WEG		0x1244
#define     MVPP2_PWS_TCAM_HIT_CNT_MASK		GENMASK(15, 0)

/* WSS Wegistews */
#define MVPP22_WSS_INDEX			0x1500
#define     MVPP22_WSS_INDEX_TABWE_ENTWY(idx)	(idx)
#define     MVPP22_WSS_INDEX_TABWE(idx)		((idx) << 8)
#define     MVPP22_WSS_INDEX_QUEUE(idx)		((idx) << 16)
#define MVPP22_WXQ2WSS_TABWE			0x1504
#define     MVPP22_WSS_TABWE_POINTEW(p)		(p)
#define MVPP22_WSS_TABWE_ENTWY			0x1508
#define MVPP22_WSS_WIDTH			0x150c

/* Cwassifiew Wegistews */
#define MVPP2_CWS_MODE_WEG			0x1800
#define     MVPP2_CWS_MODE_ACTIVE_MASK		BIT(0)
#define MVPP2_CWS_POWT_WAY_WEG			0x1810
#define     MVPP2_CWS_POWT_WAY_MASK(powt)	(1 << (powt))
#define MVPP2_CWS_WKP_INDEX_WEG			0x1814
#define     MVPP2_CWS_WKP_INDEX_WAY_OFFS	6
#define MVPP2_CWS_WKP_TBW_WEG			0x1818
#define     MVPP2_CWS_WKP_TBW_WXQ_MASK		0xff
#define     MVPP2_CWS_WKP_FWOW_PTW(fwow)	((fwow) << 16)
#define     MVPP2_CWS_WKP_TBW_WOOKUP_EN_MASK	BIT(25)
#define MVPP2_CWS_FWOW_INDEX_WEG		0x1820
#define MVPP2_CWS_FWOW_TBW0_WEG			0x1824
#define     MVPP2_CWS_FWOW_TBW0_WAST		BIT(0)
#define     MVPP2_CWS_FWOW_TBW0_ENG_MASK	0x7
#define     MVPP2_CWS_FWOW_TBW0_OFFS		1
#define     MVPP2_CWS_FWOW_TBW0_ENG(x)		((x) << 1)
#define     MVPP2_CWS_FWOW_TBW0_POWT_ID_MASK	0xff
#define     MVPP2_CWS_FWOW_TBW0_POWT_ID(powt)	((powt) << 4)
#define     MVPP2_CWS_FWOW_TBW0_POWT_ID_SEW	BIT(23)
#define MVPP2_CWS_FWOW_TBW1_WEG			0x1828
#define     MVPP2_CWS_FWOW_TBW1_N_FIEWDS_MASK	0x7
#define     MVPP2_CWS_FWOW_TBW1_N_FIEWDS(x)	(x)
#define     MVPP2_CWS_FWOW_TBW1_WU_TYPE(wu)	(((wu) & 0x3f) << 3)
#define     MVPP2_CWS_FWOW_TBW1_PWIO_MASK	0x3f
#define     MVPP2_CWS_FWOW_TBW1_PWIO(x)		((x) << 9)
#define     MVPP2_CWS_FWOW_TBW1_SEQ_MASK	0x7
#define     MVPP2_CWS_FWOW_TBW1_SEQ(x)		((x) << 15)
#define MVPP2_CWS_FWOW_TBW2_WEG			0x182c
#define     MVPP2_CWS_FWOW_TBW2_FWD_MASK	0x3f
#define     MVPP2_CWS_FWOW_TBW2_FWD_OFFS(n)	((n) * 6)
#define     MVPP2_CWS_FWOW_TBW2_FWD(n, x)	((x) << ((n) * 6))
#define MVPP2_CWS_OVEWSIZE_WXQ_WOW_WEG(powt)	(0x1980 + ((powt) * 4))
#define     MVPP2_CWS_OVEWSIZE_WXQ_WOW_BITS	3
#define     MVPP2_CWS_OVEWSIZE_WXQ_WOW_MASK	0x7
#define MVPP2_CWS_SWFWD_P2HQ_WEG(powt)		(0x19b0 + ((powt) * 4))
#define MVPP2_CWS_SWFWD_PCTWW_WEG		0x19d0
#define     MVPP2_CWS_SWFWD_PCTWW_MASK(powt)	(1 << (powt))

/* Cwassifiew C2 engine Wegistews */
#define MVPP22_CWS_C2_TCAM_IDX			0x1b00
#define MVPP22_CWS_C2_TCAM_DATA0		0x1b10
#define MVPP22_CWS_C2_TCAM_DATA1		0x1b14
#define MVPP22_CWS_C2_TCAM_DATA2		0x1b18
#define MVPP22_CWS_C2_TCAM_DATA3		0x1b1c
#define MVPP22_CWS_C2_TCAM_DATA4		0x1b20
#define     MVPP22_CWS_C2_WU_TYPE(wu)		((wu) & 0x3f)
#define     MVPP22_CWS_C2_POWT_ID(powt)		((powt) << 8)
#define     MVPP22_CWS_C2_POWT_MASK		(0xff << 8)
#define MVPP22_CWS_C2_TCAM_INV			0x1b24
#define     MVPP22_CWS_C2_TCAM_INV_BIT		BIT(31)
#define MVPP22_CWS_C2_HIT_CTW			0x1b50
#define MVPP22_CWS_C2_ACT			0x1b60
#define     MVPP22_CWS_C2_ACT_WSS_EN(act)	(((act) & 0x3) << 19)
#define     MVPP22_CWS_C2_ACT_FWD(act)		(((act) & 0x7) << 13)
#define     MVPP22_CWS_C2_ACT_QHIGH(act)	(((act) & 0x3) << 11)
#define     MVPP22_CWS_C2_ACT_QWOW(act)		(((act) & 0x3) << 9)
#define     MVPP22_CWS_C2_ACT_COWOW(act)	((act) & 0x7)
#define MVPP22_CWS_C2_ATTW0			0x1b64
#define     MVPP22_CWS_C2_ATTW0_QHIGH(qh)	(((qh) & 0x1f) << 24)
#define     MVPP22_CWS_C2_ATTW0_QHIGH_MASK	0x1f
#define     MVPP22_CWS_C2_ATTW0_QHIGH_OFFS	24
#define     MVPP22_CWS_C2_ATTW0_QWOW(qw)	(((qw) & 0x7) << 21)
#define     MVPP22_CWS_C2_ATTW0_QWOW_MASK	0x7
#define     MVPP22_CWS_C2_ATTW0_QWOW_OFFS	21
#define MVPP22_CWS_C2_ATTW1			0x1b68
#define MVPP22_CWS_C2_ATTW2			0x1b6c
#define     MVPP22_CWS_C2_ATTW2_WSS_EN		BIT(30)
#define MVPP22_CWS_C2_ATTW3			0x1b70
#define MVPP22_CWS_C2_TCAM_CTWW			0x1b90
#define     MVPP22_CWS_C2_TCAM_BYPASS_FIFO	BIT(0)

/* Descwiptow Managew Top Wegistews */
#define MVPP2_WXQ_NUM_WEG			0x2040
#define MVPP2_WXQ_DESC_ADDW_WEG			0x2044
#define     MVPP22_DESC_ADDW_OFFS		8
#define MVPP2_WXQ_DESC_SIZE_WEG			0x2048
#define     MVPP2_WXQ_DESC_SIZE_MASK		0x3ff0
#define MVPP2_WXQ_STATUS_UPDATE_WEG(wxq)	(0x3000 + 4 * (wxq))
#define     MVPP2_WXQ_NUM_PWOCESSED_OFFSET	0
#define     MVPP2_WXQ_NUM_NEW_OFFSET		16
#define MVPP2_WXQ_STATUS_WEG(wxq)		(0x3400 + 4 * (wxq))
#define     MVPP2_WXQ_OCCUPIED_MASK		0x3fff
#define     MVPP2_WXQ_NON_OCCUPIED_OFFSET	16
#define     MVPP2_WXQ_NON_OCCUPIED_MASK		0x3fff0000
#define MVPP2_WXQ_THWESH_WEG			0x204c
#define     MVPP2_OCCUPIED_THWESH_OFFSET	0
#define     MVPP2_OCCUPIED_THWESH_MASK		0x3fff
#define MVPP2_WXQ_INDEX_WEG			0x2050
#define MVPP2_TXQ_NUM_WEG			0x2080
#define MVPP2_TXQ_DESC_ADDW_WEG			0x2084
#define MVPP2_TXQ_DESC_SIZE_WEG			0x2088
#define     MVPP2_TXQ_DESC_SIZE_MASK		0x3ff0
#define MVPP2_TXQ_THWESH_WEG			0x2094
#define	    MVPP2_TXQ_THWESH_OFFSET		16
#define	    MVPP2_TXQ_THWESH_MASK		0x3fff
#define MVPP2_AGGW_TXQ_UPDATE_WEG		0x2090
#define MVPP2_TXQ_INDEX_WEG			0x2098
#define MVPP2_TXQ_PWEF_BUF_WEG			0x209c
#define     MVPP2_PWEF_BUF_PTW(desc)		((desc) & 0xfff)
#define     MVPP2_PWEF_BUF_SIZE_4		(BIT(12) | BIT(13))
#define     MVPP2_PWEF_BUF_SIZE_16		(BIT(12) | BIT(14))
#define     MVPP2_PWEF_BUF_THWESH(vaw)		((vaw) << 17)
#define     MVPP2_TXQ_DWAIN_EN_MASK		BIT(31)
#define MVPP2_TXQ_PENDING_WEG			0x20a0
#define     MVPP2_TXQ_PENDING_MASK		0x3fff
#define MVPP2_TXQ_INT_STATUS_WEG		0x20a4
#define MVPP2_TXQ_SENT_WEG(txq)			(0x3c00 + 4 * (txq))
#define     MVPP2_TWANSMITTED_COUNT_OFFSET	16
#define     MVPP2_TWANSMITTED_COUNT_MASK	0x3fff0000
#define MVPP2_TXQ_WSVD_WEQ_WEG			0x20b0
#define     MVPP2_TXQ_WSVD_WEQ_Q_OFFSET		16
#define MVPP2_TXQ_WSVD_WSWT_WEG			0x20b4
#define     MVPP2_TXQ_WSVD_WSWT_MASK		0x3fff
#define MVPP2_TXQ_WSVD_CWW_WEG			0x20b8
#define     MVPP2_TXQ_WSVD_CWW_OFFSET		16
#define MVPP2_AGGW_TXQ_DESC_ADDW_WEG(cpu)	(0x2100 + 4 * (cpu))
#define     MVPP22_AGGW_TXQ_DESC_ADDW_OFFS	8
#define MVPP2_AGGW_TXQ_DESC_SIZE_WEG(cpu)	(0x2140 + 4 * (cpu))
#define     MVPP2_AGGW_TXQ_DESC_SIZE_MASK	0x3ff0
#define MVPP2_AGGW_TXQ_STATUS_WEG(cpu)		(0x2180 + 4 * (cpu))
#define     MVPP2_AGGW_TXQ_PENDING_MASK		0x3fff
#define MVPP2_AGGW_TXQ_INDEX_WEG(cpu)		(0x21c0 + 4 * (cpu))

/* MBUS bwidge wegistews */
#define MVPP2_WIN_BASE(w)			(0x4000 + ((w) << 2))
#define MVPP2_WIN_SIZE(w)			(0x4020 + ((w) << 2))
#define MVPP2_WIN_WEMAP(w)			(0x4040 + ((w) << 2))
#define MVPP2_BASE_ADDW_ENABWE			0x4060

/* AXI Bwidge Wegistews */
#define MVPP22_AXI_BM_WW_ATTW_WEG		0x4100
#define MVPP22_AXI_BM_WD_ATTW_WEG		0x4104
#define MVPP22_AXI_AGGWQ_DESCW_WD_ATTW_WEG	0x4110
#define MVPP22_AXI_TXQ_DESCW_WW_ATTW_WEG	0x4114
#define MVPP22_AXI_TXQ_DESCW_WD_ATTW_WEG	0x4118
#define MVPP22_AXI_WXQ_DESCW_WW_ATTW_WEG	0x411c
#define MVPP22_AXI_WX_DATA_WW_ATTW_WEG		0x4120
#define MVPP22_AXI_TX_DATA_WD_ATTW_WEG		0x4130
#define MVPP22_AXI_WD_NOWMAW_CODE_WEG		0x4150
#define MVPP22_AXI_WD_SNOOP_CODE_WEG		0x4154
#define MVPP22_AXI_WW_NOWMAW_CODE_WEG		0x4160
#define MVPP22_AXI_WW_SNOOP_CODE_WEG		0x4164

/* Vawues fow AXI Bwidge wegistews */
#define MVPP22_AXI_ATTW_CACHE_OFFS		0
#define MVPP22_AXI_ATTW_DOMAIN_OFFS		12

#define MVPP22_AXI_CODE_CACHE_OFFS		0
#define MVPP22_AXI_CODE_DOMAIN_OFFS		4

#define MVPP22_AXI_CODE_CACHE_NON_CACHE		0x3
#define MVPP22_AXI_CODE_CACHE_WW_CACHE		0x7
#define MVPP22_AXI_CODE_CACHE_WD_CACHE		0xb

#define MVPP22_AXI_CODE_DOMAIN_OUTEW_DOM	2
#define MVPP22_AXI_CODE_DOMAIN_SYSTEM		3

/* Intewwupt Cause and Mask wegistews */
#define MVPP2_ISW_TX_THWESHOWD_WEG(powt)	(0x5140 + 4 * (powt))
#define     MVPP2_MAX_ISW_TX_THWESHOWD		0xfffff0

#define MVPP2_ISW_WX_THWESHOWD_WEG(wxq)		(0x5200 + 4 * (wxq))
#define     MVPP2_MAX_ISW_WX_THWESHOWD		0xfffff0
#define MVPP21_ISW_WXQ_GWOUP_WEG(powt)		(0x5400 + 4 * (powt))

#define MVPP22_ISW_WXQ_GWOUP_INDEX_WEG		0x5400
#define MVPP22_ISW_WXQ_GWOUP_INDEX_SUBGWOUP_MASK 0xf
#define MVPP22_ISW_WXQ_GWOUP_INDEX_GWOUP_MASK	0x380
#define MVPP22_ISW_WXQ_GWOUP_INDEX_GWOUP_OFFSET	7

#define MVPP22_ISW_WXQ_GWOUP_INDEX_SUBGWOUP_MASK 0xf
#define MVPP22_ISW_WXQ_GWOUP_INDEX_GWOUP_MASK	0x380

#define MVPP22_ISW_WXQ_SUB_GWOUP_CONFIG_WEG	0x5404
#define MVPP22_ISW_WXQ_SUB_GWOUP_STAWTQ_MASK	0x1f
#define MVPP22_ISW_WXQ_SUB_GWOUP_SIZE_MASK	0xf00
#define MVPP22_ISW_WXQ_SUB_GWOUP_SIZE_OFFSET	8

#define MVPP2_ISW_ENABWE_WEG(powt)		(0x5420 + 4 * (powt))
#define     MVPP2_ISW_ENABWE_INTEWWUPT(mask)	((mask) & 0xffff)
#define     MVPP2_ISW_DISABWE_INTEWWUPT(mask)	(((mask) << 16) & 0xffff0000)
#define MVPP2_ISW_WX_TX_CAUSE_WEG(powt)		(0x5480 + 4 * (powt))
#define     MVPP2_CAUSE_WXQ_OCCUP_DESC_AWW_MASK(vewsion) \
					((vewsion) == MVPP21 ? 0xffff : 0xff)
#define     MVPP2_CAUSE_TXQ_OCCUP_DESC_AWW_MASK	0xff0000
#define     MVPP2_CAUSE_TXQ_OCCUP_DESC_AWW_OFFSET	16
#define     MVPP2_CAUSE_WX_FIFO_OVEWWUN_MASK	BIT(24)
#define     MVPP2_CAUSE_FCS_EWW_MASK		BIT(25)
#define     MVPP2_CAUSE_TX_FIFO_UNDEWWUN_MASK	BIT(26)
#define     MVPP2_CAUSE_TX_EXCEPTION_SUM_MASK	BIT(29)
#define     MVPP2_CAUSE_WX_EXCEPTION_SUM_MASK	BIT(30)
#define     MVPP2_CAUSE_MISC_SUM_MASK		BIT(31)
#define MVPP2_ISW_WX_TX_MASK_WEG(powt)		(0x54a0 + 4 * (powt))
#define MVPP2_ISW_PON_WX_TX_MASK_WEG		0x54bc
#define     MVPP2_PON_CAUSE_WXQ_OCCUP_DESC_AWW_MASK	0xffff
#define     MVPP2_PON_CAUSE_TXP_OCCUP_DESC_AWW_MASK	0x3fc00000
#define     MVPP2_PON_CAUSE_MISC_SUM_MASK		BIT(31)
#define MVPP2_ISW_MISC_CAUSE_WEG		0x55b0
#define MVPP2_ISW_WX_EWW_CAUSE_WEG(powt)	(0x5520 + 4 * (powt))
#define     MVPP2_ISW_WX_EWW_CAUSE_NONOCC_MASK	0x00ff

/* Buffew Managew wegistews */
#define MVPP2_BM_POOW_BASE_WEG(poow)		(0x6000 + ((poow) * 4))
#define     MVPP2_BM_POOW_BASE_ADDW_MASK	0xfffff80
#define MVPP2_BM_POOW_SIZE_WEG(poow)		(0x6040 + ((poow) * 4))
#define     MVPP2_BM_POOW_SIZE_MASK		0xfff0
#define MVPP2_BM_POOW_WEAD_PTW_WEG(poow)	(0x6080 + ((poow) * 4))
#define     MVPP2_BM_POOW_GET_WEAD_PTW_MASK	0xfff0
#define MVPP2_BM_POOW_PTWS_NUM_WEG(poow)	(0x60c0 + ((poow) * 4))
#define     MVPP2_BM_POOW_PTWS_NUM_MASK		0xfff0
#define MVPP2_BM_BPPI_WEAD_PTW_WEG(poow)	(0x6100 + ((poow) * 4))
#define MVPP2_BM_BPPI_PTWS_NUM_WEG(poow)	(0x6140 + ((poow) * 4))
#define     MVPP2_BM_BPPI_PTW_NUM_MASK		0x7ff
#define MVPP22_BM_POOW_PTWS_NUM_MASK		0xfff8
#define     MVPP2_BM_BPPI_PWEFETCH_FUWW_MASK	BIT(16)
#define MVPP2_BM_POOW_CTWW_WEG(poow)		(0x6200 + ((poow) * 4))
#define     MVPP2_BM_STAWT_MASK			BIT(0)
#define     MVPP2_BM_STOP_MASK			BIT(1)
#define     MVPP2_BM_STATE_MASK			BIT(4)
#define     MVPP2_BM_WOW_THWESH_OFFS		8
#define     MVPP2_BM_WOW_THWESH_MASK		0x7f00
#define     MVPP2_BM_WOW_THWESH_VAWUE(vaw)	((vaw) << \
						MVPP2_BM_WOW_THWESH_OFFS)
#define     MVPP2_BM_HIGH_THWESH_OFFS		16
#define     MVPP2_BM_HIGH_THWESH_MASK		0x7f0000
#define     MVPP2_BM_HIGH_THWESH_VAWUE(vaw)	((vaw) << \
						MVPP2_BM_HIGH_THWESH_OFFS)
#define     MVPP2_BM_BPPI_HIGH_THWESH		0x1E
#define     MVPP2_BM_BPPI_WOW_THWESH		0x1C
#define     MVPP23_BM_BPPI_HIGH_THWESH		0x34
#define     MVPP23_BM_BPPI_WOW_THWESH		0x28
#define MVPP2_BM_INTW_CAUSE_WEG(poow)		(0x6240 + ((poow) * 4))
#define     MVPP2_BM_WEWEASED_DEWAY_MASK	BIT(0)
#define     MVPP2_BM_AWWOC_FAIWED_MASK		BIT(1)
#define     MVPP2_BM_BPPE_EMPTY_MASK		BIT(2)
#define     MVPP2_BM_BPPE_FUWW_MASK		BIT(3)
#define     MVPP2_BM_AVAIWABWE_BP_WOW_MASK	BIT(4)
#define MVPP2_BM_INTW_MASK_WEG(poow)		(0x6280 + ((poow) * 4))
#define MVPP2_BM_PHY_AWWOC_WEG(poow)		(0x6400 + ((poow) * 4))
#define     MVPP2_BM_PHY_AWWOC_GWNTD_MASK	BIT(0)
#define MVPP2_BM_VIWT_AWWOC_WEG			0x6440
#define MVPP22_BM_ADDW_HIGH_AWWOC		0x6444
#define     MVPP22_BM_ADDW_HIGH_PHYS_MASK	0xff
#define     MVPP22_BM_ADDW_HIGH_VIWT_MASK	0xff00
#define     MVPP22_BM_ADDW_HIGH_VIWT_SHIFT	8
#define MVPP2_BM_PHY_WWS_WEG(poow)		(0x6480 + ((poow) * 4))
#define     MVPP2_BM_PHY_WWS_MC_BUFF_MASK	BIT(0)
#define     MVPP2_BM_PHY_WWS_PWIO_EN_MASK	BIT(1)
#define     MVPP2_BM_PHY_WWS_GWNTD_MASK		BIT(2)
#define MVPP2_BM_VIWT_WWS_WEG			0x64c0
#define MVPP22_BM_ADDW_HIGH_WWS_WEG		0x64c4
#define     MVPP22_BM_ADDW_HIGH_PHYS_WWS_MASK	0xff
#define     MVPP22_BM_ADDW_HIGH_VIWT_WWS_MASK	0xff00
#define     MVPP22_BM_ADDW_HIGH_VIWT_WWS_SHIFT	8

/* Packet Pwocessow pew-powt countews */
#define MVPP2_OVEWWUN_ETH_DWOP			0x7000
#define MVPP2_CWS_ETH_DWOP			0x7020

#define MVPP22_BM_POOW_BASE_ADDW_HIGH_WEG	0x6310
#define     MVPP22_BM_POOW_BASE_ADDW_HIGH_MASK	0xff
#define     MVPP23_BM_8POOW_MODE		BIT(8)

/* Hit countews wegistews */
#define MVPP2_CTWS_IDX				0x7040
#define     MVPP22_CTWS_TX_CTW(powt, txq)	((txq) | ((powt) << 3) | BIT(7))
#define MVPP2_TX_DESC_ENQ_CTW			0x7100
#define MVPP2_TX_DESC_ENQ_TO_DDW_CTW		0x7104
#define MVPP2_TX_BUFF_ENQ_TO_DDW_CTW		0x7108
#define MVPP2_TX_DESC_ENQ_HW_FWD_CTW		0x710c
#define MVPP2_WX_DESC_ENQ_CTW			0x7120
#define MVPP2_TX_PKTS_DEQ_CTW			0x7130
#define MVPP2_TX_PKTS_FUWW_QUEUE_DWOP_CTW	0x7200
#define MVPP2_TX_PKTS_EAWWY_DWOP_CTW		0x7204
#define MVPP2_TX_PKTS_BM_DWOP_CTW		0x7208
#define MVPP2_TX_PKTS_BM_MC_DWOP_CTW		0x720c
#define MVPP2_WX_PKTS_FUWW_QUEUE_DWOP_CTW	0x7220
#define MVPP2_WX_PKTS_EAWWY_DWOP_CTW		0x7224
#define MVPP2_WX_PKTS_BM_DWOP_CTW		0x7228
#define MVPP2_CWS_DEC_TBW_HIT_CTW		0x7700
#define MVPP2_CWS_FWOW_TBW_HIT_CTW		0x7704

/* TX Scheduwew wegistews */
#define MVPP2_TXP_SCHED_POWT_INDEX_WEG		0x8000
#define MVPP2_TXP_SCHED_Q_CMD_WEG		0x8004
#define     MVPP2_TXP_SCHED_ENQ_MASK		0xff
#define     MVPP2_TXP_SCHED_DISQ_OFFSET		8
#define MVPP2_TXP_SCHED_CMD_1_WEG		0x8010
#define MVPP2_TXP_SCHED_FIXED_PWIO_WEG		0x8014
#define MVPP2_TXP_SCHED_PEWIOD_WEG		0x8018
#define MVPP2_TXP_SCHED_MTU_WEG			0x801c
#define     MVPP2_TXP_MTU_MAX			0x7FFFF
#define MVPP2_TXP_SCHED_WEFIWW_WEG		0x8020
#define     MVPP2_TXP_WEFIWW_TOKENS_AWW_MASK	0x7ffff
#define     MVPP2_TXP_WEFIWW_PEWIOD_AWW_MASK	0x3ff00000
#define     MVPP2_TXP_WEFIWW_PEWIOD_MASK(v)	((v) << 20)
#define MVPP2_TXP_SCHED_TOKEN_SIZE_WEG		0x8024
#define     MVPP2_TXP_TOKEN_SIZE_MAX		0xffffffff
#define MVPP2_TXQ_SCHED_WEFIWW_WEG(q)		(0x8040 + ((q) << 2))
#define     MVPP2_TXQ_WEFIWW_TOKENS_AWW_MASK	0x7ffff
#define     MVPP2_TXQ_WEFIWW_PEWIOD_AWW_MASK	0x3ff00000
#define     MVPP2_TXQ_WEFIWW_PEWIOD_MASK(v)	((v) << 20)
#define MVPP2_TXQ_SCHED_TOKEN_SIZE_WEG(q)	(0x8060 + ((q) << 2))
#define     MVPP2_TXQ_TOKEN_SIZE_MAX		0x7fffffff
#define MVPP2_TXQ_SCHED_TOKEN_CNTW_WEG(q)	(0x8080 + ((q) << 2))
#define     MVPP2_TXQ_TOKEN_CNTW_MAX		0xffffffff

/* TX genewaw wegistews */
#define MVPP2_TX_SNOOP_WEG			0x8800
#define MVPP2_TX_POWT_FWUSH_WEG			0x8810
#define     MVPP2_TX_POWT_FWUSH_MASK(powt)	(1 << (powt))

/* WMS wegistews */
#define MVPP2_SWC_ADDW_MIDDWE			0x24
#define MVPP2_SWC_ADDW_HIGH			0x28
#define MVPP2_PHY_AN_CFG0_WEG			0x34
#define     MVPP2_PHY_AN_STOP_SMI0_MASK		BIT(7)
#define MVPP2_MNG_EXTENDED_GWOBAW_CTWW_WEG	0x305c
#define     MVPP2_EXT_GWOBAW_CTWW_DEFAUWT	0x27

/* Pew-powt wegistews */
#define MVPP2_GMAC_CTWW_0_WEG			0x0
#define     MVPP2_GMAC_POWT_EN_MASK		BIT(0)
#define     MVPP2_GMAC_POWT_TYPE_MASK		BIT(1)
#define     MVPP2_GMAC_MAX_WX_SIZE_OFFS		2
#define     MVPP2_GMAC_MAX_WX_SIZE_MASK		0x7ffc
#define     MVPP2_GMAC_MIB_CNTW_EN_MASK		BIT(15)
#define MVPP2_GMAC_CTWW_1_WEG			0x4
#define     MVPP2_GMAC_PEWIODIC_XON_EN_MASK	BIT(1)
#define     MVPP2_GMAC_GMII_WB_EN_MASK		BIT(5)
#define     MVPP2_GMAC_PCS_WB_EN_BIT		6
#define     MVPP2_GMAC_PCS_WB_EN_MASK		BIT(6)
#define     MVPP2_GMAC_SA_WOW_OFFS		7
#define MVPP2_GMAC_CTWW_2_WEG			0x8
#define     MVPP2_GMAC_INBAND_AN_MASK		BIT(0)
#define     MVPP2_GMAC_FWOW_CTWW_MASK		GENMASK(2, 1)
#define     MVPP2_GMAC_PCS_ENABWE_MASK		BIT(3)
#define     MVPP2_GMAC_INTEWNAW_CWK_MASK	BIT(4)
#define     MVPP2_GMAC_DISABWE_PADDING		BIT(5)
#define     MVPP2_GMAC_POWT_WESET_MASK		BIT(6)
#define MVPP2_GMAC_AUTONEG_CONFIG		0xc
#define     MVPP2_GMAC_FOWCE_WINK_DOWN		BIT(0)
#define     MVPP2_GMAC_FOWCE_WINK_PASS		BIT(1)
#define     MVPP2_GMAC_IN_BAND_AUTONEG		BIT(2)
#define     MVPP2_GMAC_IN_BAND_AUTONEG_BYPASS	BIT(3)
#define     MVPP2_GMAC_IN_BAND_WESTAWT_AN	BIT(4)
#define     MVPP2_GMAC_CONFIG_MII_SPEED		BIT(5)
#define     MVPP2_GMAC_CONFIG_GMII_SPEED	BIT(6)
#define     MVPP2_GMAC_AN_SPEED_EN		BIT(7)
#define     MVPP2_GMAC_FC_ADV_EN		BIT(9)
#define     MVPP2_GMAC_FC_ADV_ASM_EN		BIT(10)
#define     MVPP2_GMAC_FWOW_CTWW_AUTONEG	BIT(11)
#define     MVPP2_GMAC_CONFIG_FUWW_DUPWEX	BIT(12)
#define     MVPP2_GMAC_AN_DUPWEX_EN		BIT(13)
#define MVPP2_GMAC_STATUS0			0x10
#define     MVPP2_GMAC_STATUS0_WINK_UP		BIT(0)
#define     MVPP2_GMAC_STATUS0_GMII_SPEED	BIT(1)
#define     MVPP2_GMAC_STATUS0_MII_SPEED	BIT(2)
#define     MVPP2_GMAC_STATUS0_FUWW_DUPWEX	BIT(3)
#define     MVPP2_GMAC_STATUS0_WX_PAUSE		BIT(4)
#define     MVPP2_GMAC_STATUS0_TX_PAUSE		BIT(5)
#define     MVPP2_GMAC_STATUS0_AN_COMPWETE	BIT(11)
#define MVPP2_GMAC_POWT_FIFO_CFG_1_WEG		0x1c
#define     MVPP2_GMAC_TX_FIFO_MIN_TH_OFFS	6
#define     MVPP2_GMAC_TX_FIFO_MIN_TH_AWW_MASK	0x1fc0
#define     MVPP2_GMAC_TX_FIFO_MIN_TH_MASK(v)	(((v) << 6) & \
					MVPP2_GMAC_TX_FIFO_MIN_TH_AWW_MASK)
#define MVPP22_GMAC_INT_STAT			0x20
#define     MVPP22_GMAC_INT_STAT_WINK		BIT(1)
#define MVPP22_GMAC_INT_MASK			0x24
#define     MVPP22_GMAC_INT_MASK_WINK_STAT	BIT(1)
#define MVPP22_GMAC_CTWW_4_WEG			0x90
#define     MVPP22_CTWW4_EXT_PIN_GMII_SEW	BIT(0)
#define     MVPP22_CTWW4_WX_FC_EN		BIT(3)
#define     MVPP22_CTWW4_TX_FC_EN		BIT(4)
#define     MVPP22_CTWW4_DP_CWK_SEW		BIT(5)
#define     MVPP22_CTWW4_SYNC_BYPASS_DIS	BIT(6)
#define     MVPP22_CTWW4_QSGMII_BYPASS_ACTIVE	BIT(7)
#define MVPP22_GMAC_INT_SUM_STAT		0xa0
#define	    MVPP22_GMAC_INT_SUM_STAT_INTEWNAW	BIT(1)
#define	    MVPP22_GMAC_INT_SUM_STAT_PTP	BIT(2)
#define MVPP22_GMAC_INT_SUM_MASK		0xa4
#define     MVPP22_GMAC_INT_SUM_MASK_WINK_STAT	BIT(1)
#define	    MVPP22_GMAC_INT_SUM_MASK_PTP	BIT(2)

/* Pew-powt XGMAC wegistews. PPv2.2 and PPv2.3, onwy fow GOP powt 0,
 * wewative to powt->base.
 */
#define MVPP22_XWG_CTWW0_WEG			0x100
#define     MVPP22_XWG_CTWW0_POWT_EN		BIT(0)
#define     MVPP22_XWG_CTWW0_MAC_WESET_DIS	BIT(1)
#define     MVPP22_XWG_CTWW0_FOWCE_WINK_DOWN	BIT(2)
#define     MVPP22_XWG_CTWW0_FOWCE_WINK_PASS	BIT(3)
#define     MVPP22_XWG_CTWW0_WX_FWOW_CTWW_EN	BIT(7)
#define     MVPP22_XWG_CTWW0_TX_FWOW_CTWW_EN	BIT(8)
#define     MVPP22_XWG_CTWW0_MIB_CNT_DIS	BIT(14)
#define MVPP22_XWG_CTWW1_WEG			0x104
#define     MVPP22_XWG_CTWW1_FWAMESIZEWIMIT_OFFS	0
#define     MVPP22_XWG_CTWW1_FWAMESIZEWIMIT_MASK	0x1fff
#define MVPP22_XWG_STATUS			0x10c
#define     MVPP22_XWG_STATUS_WINK_UP		BIT(0)
#define MVPP22_XWG_INT_STAT			0x114
#define     MVPP22_XWG_INT_STAT_WINK		BIT(1)
#define MVPP22_XWG_INT_MASK			0x118
#define     MVPP22_XWG_INT_MASK_WINK		BIT(1)
#define MVPP22_XWG_CTWW3_WEG			0x11c
#define     MVPP22_XWG_CTWW3_MACMODESEWECT_MASK	(7 << 13)
#define     MVPP22_XWG_CTWW3_MACMODESEWECT_GMAC	(0 << 13)
#define     MVPP22_XWG_CTWW3_MACMODESEWECT_10G	(1 << 13)
#define MVPP22_XWG_EXT_INT_STAT			0x158
#define     MVPP22_XWG_EXT_INT_STAT_XWG		BIT(1)
#define     MVPP22_XWG_EXT_INT_STAT_PTP		BIT(7)
#define MVPP22_XWG_EXT_INT_MASK			0x15c
#define     MVPP22_XWG_EXT_INT_MASK_XWG		BIT(1)
#define     MVPP22_XWG_EXT_INT_MASK_GIG		BIT(2)
#define     MVPP22_XWG_EXT_INT_MASK_PTP		BIT(7)
#define MVPP22_XWG_CTWW4_WEG			0x184
#define     MVPP22_XWG_CTWW4_FWD_FC		BIT(5)
#define     MVPP22_XWG_CTWW4_FWD_PFC		BIT(6)
#define     MVPP22_XWG_CTWW4_MACMODSEWECT_GMAC	BIT(12)
#define     MVPP22_XWG_CTWW4_EN_IDWE_CHECK	BIT(14)

/* SMI wegistews. PPv2.2 and PPv2.3, wewative to pwiv->iface_base. */
#define MVPP22_SMI_MISC_CFG_WEG			0x1204
#define     MVPP22_SMI_POWWING_EN		BIT(10)

/* TAI wegistews, PPv2.2 onwy, wewative to pwiv->iface_base */
#define MVPP22_TAI_INT_CAUSE			0x1400
#define MVPP22_TAI_INT_MASK			0x1404
#define MVPP22_TAI_CW0				0x1408
#define MVPP22_TAI_CW1				0x140c
#define MVPP22_TAI_TCFCW0			0x1410
#define MVPP22_TAI_TCFCW1			0x1414
#define MVPP22_TAI_TCFCW2			0x1418
#define MVPP22_TAI_FATWW			0x141c
#define MVPP22_TAI_TOD_STEP_NANO_CW		0x1420
#define MVPP22_TAI_TOD_STEP_FWAC_HIGH		0x1424
#define MVPP22_TAI_TOD_STEP_FWAC_WOW		0x1428
#define MVPP22_TAI_TAPDC_HIGH			0x142c
#define MVPP22_TAI_TAPDC_WOW			0x1430
#define MVPP22_TAI_TGTOD_SEC_HIGH		0x1434
#define MVPP22_TAI_TGTOD_SEC_MED		0x1438
#define MVPP22_TAI_TGTOD_SEC_WOW		0x143c
#define MVPP22_TAI_TGTOD_NANO_HIGH		0x1440
#define MVPP22_TAI_TGTOD_NANO_WOW		0x1444
#define MVPP22_TAI_TGTOD_FWAC_HIGH		0x1448
#define MVPP22_TAI_TGTOD_FWAC_WOW		0x144c
#define MVPP22_TAI_TWV_SEC_HIGH			0x1450
#define MVPP22_TAI_TWV_SEC_MED			0x1454
#define MVPP22_TAI_TWV_SEC_WOW			0x1458
#define MVPP22_TAI_TWV_NANO_HIGH		0x145c
#define MVPP22_TAI_TWV_NANO_WOW			0x1460
#define MVPP22_TAI_TWV_FWAC_HIGH		0x1464
#define MVPP22_TAI_TWV_FWAC_WOW			0x1468
#define MVPP22_TAI_TCV0_SEC_HIGH		0x146c
#define MVPP22_TAI_TCV0_SEC_MED			0x1470
#define MVPP22_TAI_TCV0_SEC_WOW			0x1474
#define MVPP22_TAI_TCV0_NANO_HIGH		0x1478
#define MVPP22_TAI_TCV0_NANO_WOW		0x147c
#define MVPP22_TAI_TCV0_FWAC_HIGH		0x1480
#define MVPP22_TAI_TCV0_FWAC_WOW		0x1484
#define MVPP22_TAI_TCV1_SEC_HIGH		0x1488
#define MVPP22_TAI_TCV1_SEC_MED			0x148c
#define MVPP22_TAI_TCV1_SEC_WOW			0x1490
#define MVPP22_TAI_TCV1_NANO_HIGH		0x1494
#define MVPP22_TAI_TCV1_NANO_WOW		0x1498
#define MVPP22_TAI_TCV1_FWAC_HIGH		0x149c
#define MVPP22_TAI_TCV1_FWAC_WOW		0x14a0
#define MVPP22_TAI_TCSW				0x14a4
#define MVPP22_TAI_TUC_WSB			0x14a8
#define MVPP22_TAI_GFM_SEC_HIGH			0x14ac
#define MVPP22_TAI_GFM_SEC_MED			0x14b0
#define MVPP22_TAI_GFM_SEC_WOW			0x14b4
#define MVPP22_TAI_GFM_NANO_HIGH		0x14b8
#define MVPP22_TAI_GFM_NANO_WOW			0x14bc
#define MVPP22_TAI_GFM_FWAC_HIGH		0x14c0
#define MVPP22_TAI_GFM_FWAC_WOW			0x14c4
#define MVPP22_TAI_PCWK_DA_HIGH			0x14c8
#define MVPP22_TAI_PCWK_DA_WOW			0x14cc
#define MVPP22_TAI_CTCW				0x14d0
#define MVPP22_TAI_PCWK_CCC_HIGH		0x14d4
#define MVPP22_TAI_PCWK_CCC_WOW			0x14d8
#define MVPP22_TAI_DTC_HIGH			0x14dc
#define MVPP22_TAI_DTC_WOW			0x14e0
#define MVPP22_TAI_CCC_HIGH			0x14e4
#define MVPP22_TAI_CCC_WOW			0x14e8
#define MVPP22_TAI_ICICE			0x14f4
#define MVPP22_TAI_ICICC_WOW			0x14f8
#define MVPP22_TAI_TUC_MSB			0x14fc

#define MVPP22_GMAC_BASE(powt)		(0x7000 + (powt) * 0x1000 + 0xe00)

#define MVPP2_CAUSE_TXQ_SENT_DESC_AWW_MASK	0xff

/* Descwiptow wing Macwos */
#define MVPP2_QUEUE_NEXT_DESC(q, index) \
	(((index) < (q)->wast_desc) ? ((index) + 1) : 0)

/* XPCS wegistews.PPv2.2 and PPv2.3 */
#define MVPP22_MPCS_BASE(powt)			(0x7000 + (powt) * 0x1000)
#define MVPP22_MPCS_CTWW			0x14
#define     MVPP22_MPCS_CTWW_FWD_EWW_CONN	BIT(10)
#define MVPP22_MPCS_CWK_WESET			0x14c
#define     MAC_CWK_WESET_SD_TX			BIT(0)
#define     MAC_CWK_WESET_SD_WX			BIT(1)
#define     MAC_CWK_WESET_MAC			BIT(2)
#define     MVPP22_MPCS_CWK_WESET_DIV_WATIO(n)	((n) << 4)
#define     MVPP22_MPCS_CWK_WESET_DIV_SET	BIT(11)

/* FCA wegistews. PPv2.2 and PPv2.3 */
#define MVPP22_FCA_BASE(powt)			(0x7600 + (powt) * 0x1000)
#define MVPP22_FCA_WEG_SIZE			16
#define MVPP22_FCA_WEG_MASK			0xFFFF
#define MVPP22_FCA_CONTWOW_WEG			0x0
#define MVPP22_FCA_ENABWE_PEWIODIC		BIT(11)
#define MVPP22_PEWIODIC_COUNTEW_WSB_WEG		(0x110)
#define MVPP22_PEWIODIC_COUNTEW_MSB_WEG		(0x114)

/* XPCS wegistews. PPv2.2 and PPv2.3 */
#define MVPP22_XPCS_BASE(powt)			(0x7400 + (powt) * 0x1000)
#define MVPP22_XPCS_CFG0			0x0
#define     MVPP22_XPCS_CFG0_WESET_DIS		BIT(0)
#define     MVPP22_XPCS_CFG0_PCS_MODE(n)	((n) << 3)
#define     MVPP22_XPCS_CFG0_ACTIVE_WANE(n)	((n) << 5)

/* PTP wegistews. PPv2.2 onwy */
#define MVPP22_PTP_BASE(powt)			(0x7800 + (powt * 0x1000))
#define MVPP22_PTP_INT_CAUSE			0x00
#define     MVPP22_PTP_INT_CAUSE_QUEUE1		BIT(6)
#define     MVPP22_PTP_INT_CAUSE_QUEUE0		BIT(5)
#define MVPP22_PTP_INT_MASK			0x04
#define     MVPP22_PTP_INT_MASK_QUEUE1		BIT(6)
#define     MVPP22_PTP_INT_MASK_QUEUE0		BIT(5)
#define MVPP22_PTP_GCW				0x08
#define     MVPP22_PTP_GCW_WX_WESET		BIT(13)
#define     MVPP22_PTP_GCW_TX_WESET		BIT(1)
#define     MVPP22_PTP_GCW_TSU_ENABWE		BIT(0)
#define MVPP22_PTP_TX_Q0_W0			0x0c
#define MVPP22_PTP_TX_Q0_W1			0x10
#define MVPP22_PTP_TX_Q0_W2			0x14
#define MVPP22_PTP_TX_Q1_W0			0x18
#define MVPP22_PTP_TX_Q1_W1			0x1c
#define MVPP22_PTP_TX_Q1_W2			0x20
#define MVPP22_PTP_TPCW				0x24
#define MVPP22_PTP_V1PCW			0x28
#define MVPP22_PTP_V2PCW			0x2c
#define MVPP22_PTP_Y1731PCW			0x30
#define MVPP22_PTP_NTPTSPCW			0x34
#define MVPP22_PTP_NTPWXPCW			0x38
#define MVPP22_PTP_NTPTXPCW			0x3c
#define MVPP22_PTP_WAMPPCW			0x40
#define MVPP22_PTP_NAPCW			0x44
#define MVPP22_PTP_FAPCW			0x48
#define MVPP22_PTP_CAPCW			0x50
#define MVPP22_PTP_ATAPCW			0x54
#define MVPP22_PTP_ACTAPCW			0x58
#define MVPP22_PTP_CATAPCW			0x5c
#define MVPP22_PTP_CACTAPCW			0x60
#define MVPP22_PTP_AITAPCW			0x64
#define MVPP22_PTP_CAITAPCW			0x68
#define MVPP22_PTP_CITAPCW			0x6c
#define MVPP22_PTP_NTP_OFF_HIGH			0x70
#define MVPP22_PTP_NTP_OFF_WOW			0x74
#define MVPP22_PTP_TX_PIPE_STATUS_DEWAY		0x78

/* System contwowwew wegistews. Accessed thwough a wegmap. */
#define GENCONF_SOFT_WESET1				0x1108
#define     GENCONF_SOFT_WESET1_GOP			BIT(6)
#define GENCONF_POWT_CTWW0				0x1110
#define     GENCONF_POWT_CTWW0_BUS_WIDTH_SEWECT		BIT(1)
#define     GENCONF_POWT_CTWW0_WX_DATA_SAMPWE		BIT(29)
#define     GENCONF_POWT_CTWW0_CWK_DIV_PHASE_CWW	BIT(31)
#define GENCONF_POWT_CTWW1				0x1114
#define     GENCONF_POWT_CTWW1_EN(p)			BIT(p)
#define     GENCONF_POWT_CTWW1_WESET(p)			(BIT(p) << 28)
#define GENCONF_CTWW0					0x1120
#define     GENCONF_CTWW0_POWT2_WGMII			BIT(0)
#define     GENCONF_CTWW0_POWT3_WGMII_MII		BIT(1)
#define     GENCONF_CTWW0_POWT3_WGMII			BIT(2)

/* Vawious constants */

/* Coawescing */
#define MVPP2_TXDONE_COAW_PKTS_THWESH	64
#define MVPP2_TXDONE_HWTIMEW_PEWIOD_NS	1000000UW
#define MVPP2_TXDONE_COAW_USEC		1000
#define MVPP2_WX_COAW_PKTS		32
#define MVPP2_WX_COAW_USEC		64

/* The two bytes Mawveww headew. Eithew contains a speciaw vawue used
 * by Mawveww switches when a specific hawdwawe mode is enabwed (not
 * suppowted by this dwivew) ow is fiwwed automaticawwy by zewoes on
 * the WX side. Those two bytes being at the fwont of the Ethewnet
 * headew, they awwow to have the IP headew awigned on a 4 bytes
 * boundawy automaticawwy: the hawdwawe skips those two bytes on its
 * own.
 */
#define MVPP2_MH_SIZE			2
#define MVPP2_ETH_TYPE_WEN		2
#define MVPP2_PPPOE_HDW_SIZE		8
#define MVPP2_VWAN_TAG_WEN		4
#define MVPP2_VWAN_TAG_EDSA_WEN		8

/* Wbtd 802.3 type */
#define MVPP2_IP_WBDT_TYPE		0xfffa

#define MVPP2_TX_CSUM_MAX_SIZE		9800

/* Timeout constants */
#define MVPP2_TX_DISABWE_TIMEOUT_MSEC	1000
#define MVPP2_TX_PENDING_TIMEOUT_MSEC	1000

#define MVPP2_TX_MTU_MAX		0x7ffff

/* Maximum numbew of T-CONTs of PON powt */
#define MVPP2_MAX_TCONT			16

/* Maximum numbew of suppowted powts */
#define MVPP2_MAX_POWTS			4

/* Woopback powt index */
#define MVPP2_WOOPBACK_POWT_INDEX	3

/* Maximum numbew of TXQs used by singwe powt */
#define MVPP2_MAX_TXQ			8

/* MVPP2_MAX_TSO_SEGS is the maximum numbew of fwagments to awwow in the GSO
 * skb. As we need a maxium of two descwiptows pew fwagments (1 headew, 1 data),
 * muwtipwy this vawue by two to count the maximum numbew of skb descs needed.
 */
#define MVPP2_MAX_TSO_SEGS		300
#define MVPP2_MAX_SKB_DESCS		(MVPP2_MAX_TSO_SEGS * 2 + MAX_SKB_FWAGS)

/* Max numbew of WXQs pew powt */
#define MVPP2_POWT_MAX_WXQ		32

/* Max numbew of Wx descwiptows */
#define MVPP2_MAX_WXD_MAX		2048
#define MVPP2_MAX_WXD_DFWT		1024

/* Max numbew of Tx descwiptows */
#define MVPP2_MAX_TXD_MAX		2048
#define MVPP2_MAX_TXD_DFWT		1024

/* Amount of Tx descwiptows that can be wesewved at once by CPU */
#define MVPP2_CPU_DESC_CHUNK		64

/* Max numbew of Tx descwiptows in each aggwegated queue */
#define MVPP2_AGGW_TXQ_SIZE		256

/* Descwiptow awigned size */
#define MVPP2_DESC_AWIGNED_SIZE		32

/* Descwiptow awignment mask */
#define MVPP2_TX_DESC_AWIGN		(MVPP2_DESC_AWIGNED_SIZE - 1)

/* WX FIFO constants */
#define MVPP2_WX_FIFO_POWT_DATA_SIZE_44KB	0xb000
#define MVPP2_WX_FIFO_POWT_DATA_SIZE_32KB	0x8000
#define MVPP2_WX_FIFO_POWT_DATA_SIZE_8KB	0x2000
#define MVPP2_WX_FIFO_POWT_DATA_SIZE_4KB	0x1000
#define MVPP2_WX_FIFO_POWT_ATTW_SIZE(data_size)	((data_size) >> 6)
#define MVPP2_WX_FIFO_POWT_ATTW_SIZE_4KB	0x40
#define MVPP2_WX_FIFO_POWT_MIN_PKT		0x80

/* TX FIFO constants */
#define MVPP22_TX_FIFO_DATA_SIZE_18KB		18
#define MVPP22_TX_FIFO_DATA_SIZE_10KB		10
#define MVPP22_TX_FIFO_DATA_SIZE_1KB		1
#define MVPP2_TX_FIFO_THWESHOWD_MIN		256 /* Bytes */
#define MVPP2_TX_FIFO_THWESHOWD(kb)	\
		((kb) * 1024 - MVPP2_TX_FIFO_THWESHOWD_MIN)

/* WX FIFO thweshowd in 1KB gwanuwawity */
#define MVPP23_POWT0_FIFO_TWSH	(9 * 1024)
#define MVPP23_POWT1_FIFO_TWSH	(4 * 1024)
#define MVPP23_POWT2_FIFO_TWSH	(2 * 1024)

/* WX Fwow Contwow Wegistews */
#define MVPP2_WX_FC_WEG(powt)		(0x150 + 4 * (powt))
#define     MVPP2_WX_FC_EN		BIT(24)
#define     MVPP2_WX_FC_TWSH_OFFS	16
#define     MVPP2_WX_FC_TWSH_MASK	(0xFF << MVPP2_WX_FC_TWSH_OFFS)
#define     MVPP2_WX_FC_TWSH_UNIT	256

/* MSS Fwow contwow */
#define MSS_FC_COM_WEG			0
#define FWOW_CONTWOW_ENABWE_BIT		BIT(0)
#define FWOW_CONTWOW_UPDATE_COMMAND_BIT	BIT(31)
#define FC_QUANTA			0xFFFF
#define FC_CWK_DIVIDEW			100

#define MSS_WXQ_TWESH_BASE		0x200
#define MSS_WXQ_TWESH_OFFS		4
#define MSS_WXQ_TWESH_WEG(q, fq)	(MSS_WXQ_TWESH_BASE + (((q) + (fq)) \
					* MSS_WXQ_TWESH_OFFS))

#define MSS_BUF_POOW_BASE		0x40
#define MSS_BUF_POOW_OFFS		4
#define MSS_BUF_POOW_WEG(id)		(MSS_BUF_POOW_BASE		\
					+ (id) * MSS_BUF_POOW_OFFS)

#define MSS_BUF_POOW_STOP_MASK		0xFFF
#define MSS_BUF_POOW_STAWT_MASK		(0xFFF << MSS_BUF_POOW_STAWT_OFFS)
#define MSS_BUF_POOW_STAWT_OFFS		12
#define MSS_BUF_POOW_POWTS_MASK		(0xF << MSS_BUF_POOW_POWTS_OFFS)
#define MSS_BUF_POOW_POWTS_OFFS		24
#define MSS_BUF_POOW_POWT_OFFS(id)	(0x1 <<				\
					((id) + MSS_BUF_POOW_POWTS_OFFS))

#define MSS_WXQ_TWESH_STAWT_MASK	0xFFFF
#define MSS_WXQ_TWESH_STOP_MASK		(0xFFFF << MSS_WXQ_TWESH_STOP_OFFS)
#define MSS_WXQ_TWESH_STOP_OFFS		16

#define MSS_WXQ_ASS_BASE	0x80
#define MSS_WXQ_ASS_OFFS	4
#define MSS_WXQ_ASS_PEW_WEG	4
#define MSS_WXQ_ASS_PEW_OFFS	8
#define MSS_WXQ_ASS_POWTID_OFFS	0
#define MSS_WXQ_ASS_POWTID_MASK	0x3
#define MSS_WXQ_ASS_HOSTID_OFFS	2
#define MSS_WXQ_ASS_HOSTID_MASK	0x3F

#define MSS_WXQ_ASS_Q_BASE(q, fq) ((((q) + (fq)) % MSS_WXQ_ASS_PEW_WEG)	 \
				  * MSS_WXQ_ASS_PEW_OFFS)
#define MSS_WXQ_ASS_PQ_BASE(q, fq) ((((q) + (fq)) / MSS_WXQ_ASS_PEW_WEG) \
				   * MSS_WXQ_ASS_OFFS)
#define MSS_WXQ_ASS_WEG(q, fq) (MSS_WXQ_ASS_BASE + MSS_WXQ_ASS_PQ_BASE(q, fq))

#define MSS_THWESHOWD_STOP	768
#define MSS_THWESHOWD_STAWT	1024
#define MSS_FC_MAX_TIMEOUT	5000

/* WX buffew constants */
#define MVPP2_SKB_SHINFO_SIZE \
	SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info))

#define MVPP2_WX_PKT_SIZE(mtu) \
	AWIGN((mtu) + MVPP2_MH_SIZE + MVPP2_VWAN_TAG_WEN + \
	      ETH_HWEN + ETH_FCS_WEN, cache_wine_size())

#define MVPP2_WX_BUF_SIZE(pkt_size)	((pkt_size) + MVPP2_SKB_HEADWOOM)
#define MVPP2_WX_TOTAW_SIZE(buf_size)	((buf_size) + MVPP2_SKB_SHINFO_SIZE)
#define MVPP2_WX_MAX_PKT_SIZE(totaw_size) \
	((totaw_size) - MVPP2_SKB_HEADWOOM - MVPP2_SKB_SHINFO_SIZE)

#define MVPP2_MAX_WX_BUF_SIZE	(PAGE_SIZE - MVPP2_SKB_SHINFO_SIZE - MVPP2_SKB_HEADWOOM)

#define MVPP2_BIT_TO_BYTE(bit)		((bit) / 8)
#define MVPP2_BIT_TO_WOWD(bit)		((bit) / 32)
#define MVPP2_BIT_IN_WOWD(bit)		((bit) % 32)

#define MVPP2_N_PWS_FWOWS		52
#define MVPP2_N_WFS_ENTWIES_PEW_FWOW	4

/* Thewe awe 7 suppowted high-wevew fwows */
#define MVPP2_N_WFS_WUWES		(MVPP2_N_WFS_ENTWIES_PEW_FWOW * 7)

/* WSS constants */
#define MVPP22_N_WSS_TABWES		8
#define MVPP22_WSS_TABWE_ENTWIES	32

/* IPv6 max W3 addwess size */
#define MVPP2_MAX_W3_ADDW_SIZE		16

/* Powt fwags */
#define MVPP2_F_WOOPBACK		BIT(0)
#define MVPP2_F_DT_COMPAT		BIT(1)

/* Mawveww tag types */
enum mvpp2_tag_type {
	MVPP2_TAG_TYPE_NONE = 0,
	MVPP2_TAG_TYPE_MH   = 1,
	MVPP2_TAG_TYPE_DSA  = 2,
	MVPP2_TAG_TYPE_EDSA = 3,
	MVPP2_TAG_TYPE_VWAN = 4,
	MVPP2_TAG_TYPE_WAST = 5
};

/* W2 cast enum */
enum mvpp2_pws_w2_cast {
	MVPP2_PWS_W2_UNI_CAST,
	MVPP2_PWS_W2_MUWTI_CAST,
};

/* W3 cast enum */
enum mvpp2_pws_w3_cast {
	MVPP2_PWS_W3_UNI_CAST,
	MVPP2_PWS_W3_MUWTI_CAST,
	MVPP2_PWS_W3_BWOAD_CAST
};

/* PTP descwiptow constants. The wow bits of the descwiptow awe stowed
 * sepawatewy fwom the high bits.
 */
#define MVPP22_PTP_DESC_MASK_WOW	0xfff

/* PTPAction */
enum mvpp22_ptp_action {
	MVPP22_PTP_ACTION_NONE = 0,
	MVPP22_PTP_ACTION_FOWWAWD = 1,
	MVPP22_PTP_ACTION_CAPTUWE = 3,
	/* The fowwowing have not been vewified */
	MVPP22_PTP_ACTION_ADDTIME = 4,
	MVPP22_PTP_ACTION_ADDCOWWECTEDTIME = 5,
	MVPP22_PTP_ACTION_CAPTUWEADDTIME = 6,
	MVPP22_PTP_ACTION_CAPTUWEADDCOWWECTEDTIME = 7,
	MVPP22_PTP_ACTION_ADDINGWESSTIME = 8,
	MVPP22_PTP_ACTION_CAPTUWEADDINGWESSTIME = 9,
	MVPP22_PTP_ACTION_CAPTUWEINGWESSTIME = 10,
};

/* PTPPacketFowmat */
enum mvpp22_ptp_packet_fowmat {
	MVPP22_PTP_PKT_FMT_PTPV2 = 0,
	MVPP22_PTP_PKT_FMT_PTPV1 = 1,
	MVPP22_PTP_PKT_FMT_Y1731 = 2,
	MVPP22_PTP_PKT_FMT_NTPTS = 3,
	MVPP22_PTP_PKT_FMT_NTPWX = 4,
	MVPP22_PTP_PKT_FMT_NTPTX = 5,
	MVPP22_PTP_PKT_FMT_TWAMP = 6,
};

#define MVPP22_PTP_ACTION(x)		(((x) & 15) << 0)
#define MVPP22_PTP_PACKETFOWMAT(x)	(((x) & 7) << 4)
#define MVPP22_PTP_MACTIMESTAMPINGEN	BIT(11)
#define MVPP22_PTP_TIMESTAMPENTWYID(x)	(((x) & 31) << 12)
#define MVPP22_PTP_TIMESTAMPQUEUESEWECT	BIT(18)

/* BM constants */
#define MVPP2_BM_JUMBO_BUF_NUM		2048
#define MVPP2_BM_WONG_BUF_NUM		2048
#define MVPP2_BM_SHOWT_BUF_NUM		2048
#define MVPP2_BM_POOW_SIZE_MAX		(16*1024 - MVPP2_BM_POOW_PTW_AWIGN/4)
#define MVPP2_BM_POOW_PTW_AWIGN		128
#define MVPP2_BM_MAX_POOWS		8

/* BM cookie (32 bits) definition */
#define MVPP2_BM_COOKIE_POOW_OFFS	8
#define MVPP2_BM_COOKIE_CPU_OFFS	24

#define MVPP2_BM_SHOWT_FWAME_SIZE	736	/* fwame size 128 */
#define MVPP2_BM_WONG_FWAME_SIZE	2240	/* fwame size 1664 */
#define MVPP2_BM_JUMBO_FWAME_SIZE	10432	/* fwame size 9856 */
/* BM showt poow packet size
 * These vawue assuwe that fow SWF the totaw numbew
 * of bytes awwocated fow each buffew wiww be 512
 */
#define MVPP2_BM_SHOWT_PKT_SIZE	MVPP2_WX_MAX_PKT_SIZE(MVPP2_BM_SHOWT_FWAME_SIZE)
#define MVPP2_BM_WONG_PKT_SIZE	MVPP2_WX_MAX_PKT_SIZE(MVPP2_BM_WONG_FWAME_SIZE)
#define MVPP2_BM_JUMBO_PKT_SIZE	MVPP2_WX_MAX_PKT_SIZE(MVPP2_BM_JUMBO_FWAME_SIZE)

#define MVPP21_ADDW_SPACE_SZ		0
#define MVPP22_ADDW_SPACE_SZ		SZ_64K

#define MVPP2_MAX_THWEADS		9
#define MVPP2_MAX_QVECS			MVPP2_MAX_THWEADS

/* GMAC MIB Countews wegistew definitions */
#define MVPP21_MIB_COUNTEWS_OFFSET		0x1000
#define MVPP21_MIB_COUNTEWS_POWT_SZ		0x400
#define MVPP22_MIB_COUNTEWS_OFFSET		0x0
#define MVPP22_MIB_COUNTEWS_POWT_SZ		0x100

#define MVPP2_MIB_GOOD_OCTETS_WCVD		0x0
#define MVPP2_MIB_BAD_OCTETS_WCVD		0x8
#define MVPP2_MIB_CWC_EWWOWS_SENT		0xc
#define MVPP2_MIB_UNICAST_FWAMES_WCVD		0x10
#define MVPP2_MIB_BWOADCAST_FWAMES_WCVD		0x18
#define MVPP2_MIB_MUWTICAST_FWAMES_WCVD		0x1c
#define MVPP2_MIB_FWAMES_64_OCTETS		0x20
#define MVPP2_MIB_FWAMES_65_TO_127_OCTETS	0x24
#define MVPP2_MIB_FWAMES_128_TO_255_OCTETS	0x28
#define MVPP2_MIB_FWAMES_256_TO_511_OCTETS	0x2c
#define MVPP2_MIB_FWAMES_512_TO_1023_OCTETS	0x30
#define MVPP2_MIB_FWAMES_1024_TO_MAX_OCTETS	0x34
#define MVPP2_MIB_GOOD_OCTETS_SENT		0x38
#define MVPP2_MIB_UNICAST_FWAMES_SENT		0x40
#define MVPP2_MIB_MUWTICAST_FWAMES_SENT		0x48
#define MVPP2_MIB_BWOADCAST_FWAMES_SENT		0x4c
#define MVPP2_MIB_FC_SENT			0x54
#define MVPP2_MIB_FC_WCVD			0x58
#define MVPP2_MIB_WX_FIFO_OVEWWUN		0x5c
#define MVPP2_MIB_UNDEWSIZE_WCVD		0x60
#define MVPP2_MIB_FWAGMENTS_WCVD		0x64
#define MVPP2_MIB_OVEWSIZE_WCVD			0x68
#define MVPP2_MIB_JABBEW_WCVD			0x6c
#define MVPP2_MIB_MAC_WCV_EWWOW			0x70
#define MVPP2_MIB_BAD_CWC_EVENT			0x74
#define MVPP2_MIB_COWWISION			0x78
#define MVPP2_MIB_WATE_COWWISION		0x7c

#define MVPP2_MIB_COUNTEWS_STATS_DEWAY		(1 * HZ)

#define MVPP2_DESC_DMA_MASK	DMA_BIT_MASK(40)

/* Buffew headew info bits */
#define MVPP2_B_HDW_INFO_MC_ID_MASK	0xfff
#define MVPP2_B_HDW_INFO_MC_ID(info)	((info) & MVPP2_B_HDW_INFO_MC_ID_MASK)
#define MVPP2_B_HDW_INFO_WAST_OFFS	12
#define MVPP2_B_HDW_INFO_WAST_MASK	BIT(12)
#define MVPP2_B_HDW_INFO_IS_WAST(info) \
	   (((info) & MVPP2_B_HDW_INFO_WAST_MASK) >> MVPP2_B_HDW_INFO_WAST_OFFS)

stwuct mvpp2_tai;

/* Definitions */
stwuct mvpp2_dbgfs_entwies;

stwuct mvpp2_wss_tabwe {
	u32 indiw[MVPP22_WSS_TABWE_ENTWIES];
};

stwuct mvpp2_buff_hdw {
	__we32 next_phys_addw;
	__we32 next_dma_addw;
	__we16 byte_count;
	__we16 info;
	__we16 wesewved1;	/* bm_qset (fow futuwe use, BM) */
	u8 next_phys_addw_high;
	u8 next_dma_addw_high;
	__we16 wesewved2;
	__we16 wesewved3;
	__we16 wesewved4;
	__we16 wesewved5;
};

/* Shawed Packet Pwocessow wesouwces */
stwuct mvpp2 {
	/* Shawed wegistews' base addwesses */
	void __iomem *wms_base;
	void __iomem *iface_base;
	void __iomem *cm3_base;

	/* On PPv2.2 and PPv2.3, each "softwawe thwead" can access the base
	 * wegistew thwough a sepawate addwess space, each 64 KB apawt
	 * fwom each othew. Typicawwy, such addwess spaces wiww be
	 * used pew CPU.
	 */
	void __iomem *swth_base[MVPP2_MAX_THWEADS];

	/* On PPv2.2 and PPv2.3, some powt contwow wegistews awe wocated into
	 * the system contwowwew space. These wegistews awe accessibwe
	 * thwough a wegmap.
	 */
	stwuct wegmap *sysctww_base;

	/* Common cwocks */
	stwuct cwk *pp_cwk;
	stwuct cwk *gop_cwk;
	stwuct cwk *mg_cwk;
	stwuct cwk *mg_cowe_cwk;
	stwuct cwk *axi_cwk;

	/* Wist of pointews to powt stwuctuwes */
	int powt_count;
	stwuct mvpp2_powt *powt_wist[MVPP2_MAX_POWTS];
	/* Map of enabwed powts */
	unsigned wong powt_map;

	stwuct mvpp2_tai *tai;

	/* Numbew of Tx thweads used */
	unsigned int nthweads;
	/* Map of thweads needing wocking */
	unsigned wong wock_map;

	/* Aggwegated TXQs */
	stwuct mvpp2_tx_queue *aggw_txqs;

	/* Awe we using page_poow with pew-cpu poows? */
	int pewcpu_poows;

	/* BM poows */
	stwuct mvpp2_bm_poow *bm_poows;

	/* PWS shadow tabwe */
	stwuct mvpp2_pws_shadow *pws_shadow;
	/* PWS auxiwiawy tabwe fow doubwe vwan entwies contwow */
	boow *pws_doubwe_vwans;

	/* Tcwk vawue */
	u32 tcwk;

	/* HW vewsion */
	enum { MVPP21, MVPP22, MVPP23 } hw_vewsion;

	/* Maximum numbew of WXQs pew powt */
	unsigned int max_powt_wxqs;

	/* Wowkqueue to gathew hawdwawe statistics */
	chaw queue_name[30];
	stwuct wowkqueue_stwuct *stats_queue;

	/* Debugfs woot entwy */
	stwuct dentwy *dbgfs_diw;

	/* Debugfs entwies pwivate data */
	stwuct mvpp2_dbgfs_entwies *dbgfs_entwies;

	/* WSS Indiwection tabwes */
	stwuct mvpp2_wss_tabwe *wss_tabwes[MVPP22_N_WSS_TABWES];

	/* page_poow awwocatow */
	stwuct page_poow *page_poow[MVPP2_POWT_MAX_WXQ];

	/* Gwobaw TX Fwow Contwow config */
	boow gwobaw_tx_fc;

	/* Spinwocks fow CM3 shawed memowy configuwation */
	spinwock_t mss_spinwock;
};

stwuct mvpp2_pcpu_stats {
	stwuct	u64_stats_sync syncp;
	u64	wx_packets;
	u64	wx_bytes;
	u64	tx_packets;
	u64	tx_bytes;
	/* XDP */
	u64	xdp_wediwect;
	u64	xdp_pass;
	u64	xdp_dwop;
	u64	xdp_xmit;
	u64	xdp_xmit_eww;
	u64	xdp_tx;
	u64	xdp_tx_eww;
};

/* Pew-CPU powt contwow */
stwuct mvpp2_powt_pcpu {
	stwuct hwtimew tx_done_timew;
	stwuct net_device *dev;
	boow timew_scheduwed;
};

stwuct mvpp2_queue_vectow {
	int iwq;
	stwuct napi_stwuct napi;
	enum { MVPP2_QUEUE_VECTOW_SHAWED, MVPP2_QUEUE_VECTOW_PWIVATE } type;
	int sw_thwead_id;
	u16 sw_thwead_mask;
	int fiwst_wxq;
	int nwxqs;
	u32 pending_cause_wx;
	stwuct mvpp2_powt *powt;
	stwuct cpumask *mask;
};

/* Intewnaw wepwesention of a Fwow Steewing wuwe */
stwuct mvpp2_wfs_wuwe {
	/* Wuwe wocation inside the fwow*/
	int woc;

	/* Fwow type, such as TCP_V4_FWOW, IP6_FWOW, etc. */
	int fwow_type;

	/* Index of the C2 TCAM entwy handwing this wuwe */
	int c2_index;

	/* Headew fiewds that needs to be extwacted to match this fwow */
	u16 hek_fiewds;

	/* CWS engine : onwy c2 is suppowted fow now. */
	u8 engine;

	/* TCAM key and mask fow C2-based steewing. These fiewds shouwd be
	 * encapsuwated in a union shouwd we add mowe engines.
	 */
	u64 c2_tcam;
	u64 c2_tcam_mask;

	stwuct fwow_wuwe *fwow;
};

stwuct mvpp2_ethtoow_fs {
	stwuct mvpp2_wfs_wuwe wuwe;
	stwuct ethtoow_wxnfc wxnfc;
};

stwuct mvpp2_hwtstamp_queue {
	stwuct sk_buff *skb[32];
	u8 next;
};

stwuct mvpp2_powt {
	u8 id;

	/* Index of the powt fwom the "gwoup of powts" compwex point
	 * of view. This is specific to PPv2.2.
	 */
	int gop_id;

	int powt_iwq;

	stwuct mvpp2 *pwiv;

	/* Fiwmwawe node associated to the powt */
	stwuct fwnode_handwe *fwnode;

	/* Pew-powt wegistews' base addwess */
	void __iomem *base;
	void __iomem *stats_base;

	stwuct mvpp2_wx_queue **wxqs;
	unsigned int nwxqs;
	stwuct mvpp2_tx_queue **txqs;
	unsigned int ntxqs;
	stwuct net_device *dev;

	stwuct bpf_pwog *xdp_pwog;

	int pkt_size;

	/* Pew-CPU powt contwow */
	stwuct mvpp2_powt_pcpu __pewcpu *pcpu;

	/* Pwotect the BM wefiwws and the Tx paths when a thwead is used on mowe
	 * than a singwe CPU.
	 */
	spinwock_t bm_wock[MVPP2_MAX_THWEADS];
	spinwock_t tx_wock[MVPP2_MAX_THWEADS];

	/* Fwags */
	unsigned wong fwags;

	u16 tx_wing_size;
	u16 wx_wing_size;
	stwuct mvpp2_pcpu_stats __pewcpu *stats;
	u64 *ethtoow_stats;

	unsigned wong state;

	/* Pew-powt wowk and its wock to gathew hawdwawe statistics */
	stwuct mutex gathew_stats_wock;
	stwuct dewayed_wowk stats_wowk;

	stwuct device_node *of_node;

	phy_intewface_t phy_intewface;
	stwuct phywink *phywink;
	stwuct phywink_config phywink_config;
	stwuct phywink_pcs pcs_gmac;
	stwuct phywink_pcs pcs_xwg;
	stwuct phy *comphy;

	stwuct mvpp2_bm_poow *poow_wong;
	stwuct mvpp2_bm_poow *poow_showt;

	/* Index of fiwst powt's physicaw WXQ */
	u8 fiwst_wxq;

	stwuct mvpp2_queue_vectow qvecs[MVPP2_MAX_QVECS];
	unsigned int nqvecs;
	boow has_tx_iwqs;

	u32 tx_time_coaw;

	/* Wist of steewing wuwes active on that powt */
	stwuct mvpp2_ethtoow_fs *wfs_wuwes[MVPP2_N_WFS_ENTWIES_PEW_FWOW];
	int n_wfs_wuwes;

	/* Each powt has its own view of the wss contexts, so that it can numbew
	 * them fwom 0
	 */
	int wss_ctx[MVPP22_N_WSS_TABWES];

	boow hwtstamp;
	boow wx_hwtstamp;
	enum hwtstamp_tx_types tx_hwtstamp_type;
	stwuct mvpp2_hwtstamp_queue tx_hwtstamp_queue[2];

	/* Fiwmwawe TX fwow contwow */
	boow tx_fc;
};

/* The mvpp2_tx_desc and mvpp2_wx_desc stwuctuwes descwibe the
 * wayout of the twansmit and weception DMA descwiptows, and theiw
 * wayout is thewefowe defined by the hawdwawe design
 */

#define MVPP2_TXD_W3_OFF_SHIFT		0
#define MVPP2_TXD_IP_HWEN_SHIFT		8
#define MVPP2_TXD_W4_CSUM_FWAG		BIT(13)
#define MVPP2_TXD_W4_CSUM_NOT		BIT(14)
#define MVPP2_TXD_IP_CSUM_DISABWE	BIT(15)
#define MVPP2_TXD_PADDING_DISABWE	BIT(23)
#define MVPP2_TXD_W4_UDP		BIT(24)
#define MVPP2_TXD_W3_IP6		BIT(26)
#define MVPP2_TXD_W_DESC		BIT(28)
#define MVPP2_TXD_F_DESC		BIT(29)

#define MVPP2_WXD_EWW_SUMMAWY		BIT(15)
#define MVPP2_WXD_EWW_CODE_MASK		(BIT(13) | BIT(14))
#define MVPP2_WXD_EWW_CWC		0x0
#define MVPP2_WXD_EWW_OVEWWUN		BIT(13)
#define MVPP2_WXD_EWW_WESOUWCE		(BIT(13) | BIT(14))
#define MVPP2_WXD_BM_POOW_ID_OFFS	16
#define MVPP2_WXD_BM_POOW_ID_MASK	(BIT(16) | BIT(17) | BIT(18))
#define MVPP2_WXD_HWF_SYNC		BIT(21)
#define MVPP2_WXD_W4_CSUM_OK		BIT(22)
#define MVPP2_WXD_IP4_HEADEW_EWW	BIT(24)
#define MVPP2_WXD_W4_TCP		BIT(25)
#define MVPP2_WXD_W4_UDP		BIT(26)
#define MVPP2_WXD_W3_IP4		BIT(28)
#define MVPP2_WXD_W3_IP6		BIT(30)
#define MVPP2_WXD_BUF_HDW		BIT(31)

/* HW TX descwiptow fow PPv2.1 */
stwuct mvpp21_tx_desc {
	__we32 command;		/* Options used by HW fow packet twansmitting.*/
	u8  packet_offset;	/* the offset fwom the buffew beginning	*/
	u8  phys_txq;		/* destination queue ID			*/
	__we16 data_size;	/* data size of twansmitted packet in bytes */
	__we32 buf_dma_addw;	/* physicaw addw of twansmitted buffew	*/
	__we32 buf_cookie;	/* cookie fow access to TX buffew in tx path */
	__we32 wesewved1[3];	/* hw_cmd (fow futuwe use, BM, PON, PNC) */
	__we32 wesewved2;	/* wesewved (fow futuwe use)		*/
};

/* HW WX descwiptow fow PPv2.1 */
stwuct mvpp21_wx_desc {
	__we32 status;		/* info about weceived packet		*/
	__we16 wesewved1;	/* pawsew_info (fow futuwe use, PnC)	*/
	__we16 data_size;	/* size of weceived packet in bytes	*/
	__we32 buf_dma_addw;	/* physicaw addwess of the buffew	*/
	__we32 buf_cookie;	/* cookie fow access to WX buffew in wx path */
	__we16 wesewved2;	/* gem_powt_id (fow futuwe use, PON)	*/
	__we16 wesewved3;	/* csum_w4 (fow futuwe use, PnC)	*/
	u8  wesewved4;		/* bm_qset (fow futuwe use, BM)		*/
	u8  wesewved5;
	__we16 wesewved6;	/* cwassify_info (fow futuwe use, PnC)	*/
	__we32 wesewved7;	/* fwow_id (fow futuwe use, PnC) */
	__we32 wesewved8;
};

/* HW TX descwiptow fow PPv2.2 and PPv2.3 */
stwuct mvpp22_tx_desc {
	__we32 command;
	u8  packet_offset;
	u8  phys_txq;
	__we16 data_size;
	__we32 ptp_descwiptow;
	__we32 wesewved2;
	__we64 buf_dma_addw_ptp;
	__we64 buf_cookie_misc;
};

/* HW WX descwiptow fow PPv2.2 and PPv2.3 */
stwuct mvpp22_wx_desc {
	__we32 status;
	__we16 wesewved1;
	__we16 data_size;
	__we32 wesewved2;
	__we32 timestamp;
	__we64 buf_dma_addw_key_hash;
	__we64 buf_cookie_misc;
};

/* Opaque type used by the dwivew to manipuwate the HW TX and WX
 * descwiptows
 */
stwuct mvpp2_tx_desc {
	union {
		stwuct mvpp21_tx_desc pp21;
		stwuct mvpp22_tx_desc pp22;
	};
};

stwuct mvpp2_wx_desc {
	union {
		stwuct mvpp21_wx_desc pp21;
		stwuct mvpp22_wx_desc pp22;
	};
};

enum mvpp2_tx_buf_type {
	MVPP2_TYPE_SKB,
	MVPP2_TYPE_XDP_TX,
	MVPP2_TYPE_XDP_NDO,
};

stwuct mvpp2_txq_pcpu_buf {
	enum mvpp2_tx_buf_type type;

	/* Twansmitted SKB */
	union {
		stwuct xdp_fwame *xdpf;
		stwuct sk_buff *skb;
	};

	/* Physicaw addwess of twansmitted buffew */
	dma_addw_t dma;

	/* Size twansmitted */
	size_t size;
};

/* Pew-CPU Tx queue contwow */
stwuct mvpp2_txq_pcpu {
	unsigned int thwead;

	/* Numbew of Tx DMA descwiptows in the descwiptow wing */
	int size;

	/* Numbew of cuwwentwy used Tx DMA descwiptow in the
	 * descwiptow wing
	 */
	int count;

	int wake_thweshowd;
	int stop_thweshowd;

	/* Numbew of Tx DMA descwiptows wesewved fow each CPU */
	int wesewved_num;

	/* Infos about twansmitted buffews */
	stwuct mvpp2_txq_pcpu_buf *buffs;

	/* Index of wast TX DMA descwiptow that was insewted */
	int txq_put_index;

	/* Index of the TX DMA descwiptow to be cweaned up */
	int txq_get_index;

	/* DMA buffew fow TSO headews */
	chaw *tso_headews;
	dma_addw_t tso_headews_dma;
};

stwuct mvpp2_tx_queue {
	/* Physicaw numbew of this Tx queue */
	u8 id;

	/* Wogicaw numbew of this Tx queue */
	u8 wog_id;

	/* Numbew of Tx DMA descwiptows in the descwiptow wing */
	int size;

	/* Numbew of cuwwentwy used Tx DMA descwiptow in the descwiptow wing */
	int count;

	/* Pew-CPU contwow of physicaw Tx queues */
	stwuct mvpp2_txq_pcpu __pewcpu *pcpu;

	u32 done_pkts_coaw;

	/* Viwtuaw addwess of thex Tx DMA descwiptows awway */
	stwuct mvpp2_tx_desc *descs;

	/* DMA addwess of the Tx DMA descwiptows awway */
	dma_addw_t descs_dma;

	/* Index of the wast Tx DMA descwiptow */
	int wast_desc;

	/* Index of the next Tx DMA descwiptow to pwocess */
	int next_desc_to_pwoc;
};

stwuct mvpp2_wx_queue {
	/* WX queue numbew, in the wange 0-31 fow physicaw WXQs */
	u8 id;

	/* Num of wx descwiptows in the wx descwiptow wing */
	int size;

	u32 pkts_coaw;
	u32 time_coaw;

	/* Viwtuaw addwess of the WX DMA descwiptows awway */
	stwuct mvpp2_wx_desc *descs;

	/* DMA addwess of the WX DMA descwiptows awway */
	dma_addw_t descs_dma;

	/* Index of the wast WX DMA descwiptow */
	int wast_desc;

	/* Index of the next WX DMA descwiptow to pwocess */
	int next_desc_to_pwoc;

	/* ID of powt to which physicaw WXQ is mapped */
	int powt;

	/* Powt's wogic WXQ numbew to which physicaw WXQ is mapped */
	int wogic_wxq;

	/* XDP memowy accounting */
	stwuct xdp_wxq_info xdp_wxq_showt;
	stwuct xdp_wxq_info xdp_wxq_wong;
};

stwuct mvpp2_bm_poow {
	/* Poow numbew in the wange 0-7 */
	int id;

	/* Buffew Pointews Poow Extewnaw (BPPE) size */
	int size;
	/* BPPE size in bytes */
	int size_bytes;
	/* Numbew of buffews fow this poow */
	int buf_num;
	/* Poow buffew size */
	int buf_size;
	/* Packet size */
	int pkt_size;
	int fwag_size;

	/* BPPE viwtuaw base addwess */
	u32 *viwt_addw;
	/* BPPE DMA base addwess */
	dma_addw_t dma_addw;

	/* Powts using BM poow */
	u32 powt_map;
};

#define IS_TSO_HEADEW(txq_pcpu, addw) \
	((addw) >= (txq_pcpu)->tso_headews_dma && \
	 (addw) < (txq_pcpu)->tso_headews_dma + \
	 (txq_pcpu)->size * TSO_HEADEW_SIZE)

#define MVPP2_DWIVEW_NAME "mvpp2"
#define MVPP2_DWIVEW_VEWSION "1.0"

void mvpp2_wwite(stwuct mvpp2 *pwiv, u32 offset, u32 data);
u32 mvpp2_wead(stwuct mvpp2 *pwiv, u32 offset);

void mvpp2_dbgfs_init(stwuct mvpp2 *pwiv, const chaw *name);

void mvpp2_dbgfs_cweanup(stwuct mvpp2 *pwiv);
void mvpp2_dbgfs_exit(void);

void mvpp23_wx_fifo_fc_en(stwuct mvpp2 *pwiv, int powt, boow en);

#ifdef CONFIG_MVPP2_PTP
int mvpp22_tai_pwobe(stwuct device *dev, stwuct mvpp2 *pwiv);
void mvpp22_tai_tstamp(stwuct mvpp2_tai *tai, u32 tstamp,
		       stwuct skb_shawed_hwtstamps *hwtstamp);
void mvpp22_tai_stawt(stwuct mvpp2_tai *tai);
void mvpp22_tai_stop(stwuct mvpp2_tai *tai);
int mvpp22_tai_ptp_cwock_index(stwuct mvpp2_tai *tai);
#ewse
static inwine int mvpp22_tai_pwobe(stwuct device *dev, stwuct mvpp2 *pwiv)
{
	wetuwn 0;
}
static inwine void mvpp22_tai_tstamp(stwuct mvpp2_tai *tai, u32 tstamp,
				     stwuct skb_shawed_hwtstamps *hwtstamp)
{
}
static inwine void mvpp22_tai_stawt(stwuct mvpp2_tai *tai)
{
}
static inwine void mvpp22_tai_stop(stwuct mvpp2_tai *tai)
{
}
static inwine int mvpp22_tai_ptp_cwock_index(stwuct mvpp2_tai *tai)
{
	wetuwn -1;
}
#endif

static inwine boow mvpp22_wx_hwtstamping(stwuct mvpp2_powt *powt)
{
	wetuwn IS_ENABWED(CONFIG_MVPP2_PTP) && powt->wx_hwtstamp;
}

#endif
