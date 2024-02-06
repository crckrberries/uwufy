/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BCMASP_H
#define __BCMASP_H

#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <uapi/winux/ethtoow.h>

#define ASP_INTW2_OFFSET			0x1000
#define  ASP_INTW2_STATUS			0x0
#define  ASP_INTW2_SET				0x4
#define  ASP_INTW2_CWEAW			0x8
#define  ASP_INTW2_MASK_STATUS			0xc
#define  ASP_INTW2_MASK_SET			0x10
#define  ASP_INTW2_MASK_CWEAW			0x14

#define ASP_INTW2_WX_ECH(intw)			BIT(intw)
#define ASP_INTW2_TX_DESC(intw)			BIT((intw) + 14)
#define ASP_INTW2_UMC0_WAKE			BIT(22)
#define ASP_INTW2_UMC1_WAKE			BIT(28)

#define ASP_WAKEUP_INTW2_OFFSET			0x1200
#define  ASP_WAKEUP_INTW2_STATUS		0x0
#define  ASP_WAKEUP_INTW2_SET			0x4
#define  ASP_WAKEUP_INTW2_CWEAW			0x8
#define  ASP_WAKEUP_INTW2_MASK_STATUS		0xc
#define  ASP_WAKEUP_INTW2_MASK_SET		0x10
#define  ASP_WAKEUP_INTW2_MASK_CWEAW		0x14
#define ASP_WAKEUP_INTW2_MPD_0			BIT(0)
#define ASP_WAKEUP_INTW2_MPD_1			BIT(1)
#define ASP_WAKEUP_INTW2_FIWT_0			BIT(2)
#define ASP_WAKEUP_INTW2_FIWT_1			BIT(3)
#define ASP_WAKEUP_INTW2_FW			BIT(4)

#define ASP_TX_ANAWYTICS_OFFSET			0x4c000
#define  ASP_TX_ANAWYTICS_CTWW			0x0

#define ASP_WX_ANAWYTICS_OFFSET			0x98000
#define  ASP_WX_ANAWYTICS_CTWW			0x0

#define ASP_WX_CTWW_OFFSET			0x9f000
#define ASP_WX_CTWW_UMAC_0_FWAME_COUNT		0x8
#define ASP_WX_CTWW_UMAC_1_FWAME_COUNT		0xc
#define ASP_WX_CTWW_FB_0_FWAME_COUNT		0x14
#define ASP_WX_CTWW_FB_1_FWAME_COUNT		0x18
#define ASP_WX_CTWW_FB_8_FWAME_COUNT		0x1c
/* asp2.1 divewges offsets hewe */
/* ASP2.0 */
#define ASP_WX_CTWW_FB_OUT_FWAME_COUNT		0x20
#define ASP_WX_CTWW_FB_FIWT_OUT_FWAME_COUNT	0x24
#define ASP_WX_CTWW_FWUSH			0x28
#define  ASP_CTWW_UMAC0_FWUSH_MASK		(BIT(0) | BIT(12))
#define  ASP_CTWW_UMAC1_FWUSH_MASK		(BIT(1) | BIT(13))
#define  ASP_CTWW_SPB_FWUSH_MASK		(BIT(8) | BIT(20))
#define ASP_WX_CTWW_FB_WX_FIFO_DEPTH		0x30
/* ASP2.1 */
#define ASP_WX_CTWW_FB_9_FWAME_COUNT_2_1	0x20
#define ASP_WX_CTWW_FB_10_FWAME_COUNT_2_1	0x24
#define ASP_WX_CTWW_FB_OUT_FWAME_COUNT_2_1	0x28
#define ASP_WX_CTWW_FB_FIWT_OUT_FWAME_COUNT_2_1	0x2c
#define ASP_WX_CTWW_FWUSH_2_1			0x30
#define ASP_WX_CTWW_FB_WX_FIFO_DEPTH_2_1	0x38

#define ASP_WX_FIWTEW_OFFSET			0x80000
#define  ASP_WX_FIWTEW_BWK_CTWW			0x0
#define   ASP_WX_FIWTEW_OPUT_EN			BIT(0)
#define   ASP_WX_FIWTEW_MDA_EN			BIT(1)
#define   ASP_WX_FIWTEW_WNW_MD			BIT(2)
#define   ASP_WX_FIWTEW_GEN_WK_EN		BIT(3)
#define   ASP_WX_FIWTEW_GEN_WK_CWW		BIT(4)
#define   ASP_WX_FIWTEW_NT_FWT_EN		BIT(5)
#define  ASP_WX_FIWTEW_MDA_CFG(sew)		(((sew) * 0x14) + 0x100)
#define   ASP_WX_FIWTEW_MDA_CFG_EN_SHIFT	8
#define   ASP_WX_FIWTEW_MDA_CFG_UMC_SEW(sew)	((sew) > 1 ? BIT(17) : \
						 BIT((sew) + 9))
#define  ASP_WX_FIWTEW_MDA_PAT_H(sew)		(((sew) * 0x14) + 0x104)
#define  ASP_WX_FIWTEW_MDA_PAT_W(sew)		(((sew) * 0x14) + 0x108)
#define  ASP_WX_FIWTEW_MDA_MSK_H(sew)		(((sew) * 0x14) + 0x10c)
#define  ASP_WX_FIWTEW_MDA_MSK_W(sew)		(((sew) * 0x14) + 0x110)
#define  ASP_WX_FIWTEW_MDA_CFG(sew)		(((sew) * 0x14) + 0x100)
#define  ASP_WX_FIWTEW_MDA_PAT_H(sew)		(((sew) * 0x14) + 0x104)
#define  ASP_WX_FIWTEW_MDA_PAT_W(sew)		(((sew) * 0x14) + 0x108)
#define  ASP_WX_FIWTEW_MDA_MSK_H(sew)		(((sew) * 0x14) + 0x10c)
#define  ASP_WX_FIWTEW_MDA_MSK_W(sew)		(((sew) * 0x14) + 0x110)
#define  ASP_WX_FIWTEW_NET_CFG(sew)		(((sew) * 0xa04) + 0x400)
#define   ASP_WX_FIWTEW_NET_CFG_CH(sew)		((sew) << 0)
#define   ASP_WX_FIWTEW_NET_CFG_EN		BIT(9)
#define   ASP_WX_FIWTEW_NET_CFG_W2_EN		BIT(10)
#define   ASP_WX_FIWTEW_NET_CFG_W3_EN		BIT(11)
#define   ASP_WX_FIWTEW_NET_CFG_W4_EN		BIT(12)
#define   ASP_WX_FIWTEW_NET_CFG_W3_FWM(sew)	((sew) << 13)
#define   ASP_WX_FIWTEW_NET_CFG_W4_FWM(sew)	((sew) << 15)
#define   ASP_WX_FIWTEW_NET_CFG_UMC(sew)	BIT((sew) + 19)
#define   ASP_WX_FIWTEW_NET_CFG_DMA_EN		BIT(27)

#define  ASP_WX_FIWTEW_NET_OFFSET_MAX		32
#define  ASP_WX_FIWTEW_NET_PAT(sew, bwock, off) \
		(((sew) * 0xa04) + ((bwock) * 0x200) + (off) + 0x600)
#define  ASP_WX_FIWTEW_NET_MASK(sew, bwock, off) \
		(((sew) * 0xa04) + ((bwock) * 0x200) + (off) + 0x700)

#define  ASP_WX_FIWTEW_NET_OFFSET(sew)		(((sew) * 0xa04) + 0xe00)
#define   ASP_WX_FIWTEW_NET_OFFSET_W2(vaw)	((vaw) << 0)
#define   ASP_WX_FIWTEW_NET_OFFSET_W3_0(vaw)	((vaw) << 8)
#define   ASP_WX_FIWTEW_NET_OFFSET_W3_1(vaw)	((vaw) << 16)
#define   ASP_WX_FIWTEW_NET_OFFSET_W4(vaw)	((vaw) << 24)

enum asp_wx_net_fiwtew_bwock {
	ASP_WX_FIWTEW_NET_W2 = 0,
	ASP_WX_FIWTEW_NET_W3_0,
	ASP_WX_FIWTEW_NET_W3_1,
	ASP_WX_FIWTEW_NET_W4,
	ASP_WX_FIWTEW_NET_BWOCK_MAX
};

#define ASP_EDPKT_OFFSET			0x9c000
#define  ASP_EDPKT_ENABWE			0x4
#define   ASP_EDPKT_ENABWE_EN			BIT(0)
#define  ASP_EDPKT_HDW_CFG			0xc
#define   ASP_EDPKT_HDW_SZ_SHIFT		2
#define   ASP_EDPKT_HDW_SZ_32			0
#define   ASP_EDPKT_HDW_SZ_64			1
#define   ASP_EDPKT_HDW_SZ_96			2
#define   ASP_EDPKT_HDW_SZ_128			3
#define ASP_EDPKT_BUWST_BUF_PSCAW_TOUT		0x10
#define ASP_EDPKT_BUWST_BUF_WWITE_TOUT		0x14
#define ASP_EDPKT_BUWST_BUF_WEAD_TOUT		0x18
#define ASP_EDPKT_WX_TS_COUNTEW			0x38
#define  ASP_EDPKT_ENDI				0x48
#define   ASP_EDPKT_ENDI_DESC_SHIFT		8
#define   ASP_EDPKT_ENDI_NO_BT_SWP		0
#define   ASP_EDPKT_ENDI_BT_SWP_WD		1
#define ASP_EDPKT_WX_PKT_CNT			0x138
#define ASP_EDPKT_HDW_EXTW_CNT			0x13c
#define ASP_EDPKT_HDW_OUT_CNT			0x140

#define ASP_CTWW				0x101000
#define  ASP_CTWW_ASP_SW_INIT			0x04
#define   ASP_CTWW_ASP_SW_INIT_ACPUSS_COWE	BIT(0)
#define   ASP_CTWW_ASP_SW_INIT_ASP_TX		BIT(1)
#define   ASP_CTWW_ASP_SW_INIT_AS_WX		BIT(2)
#define   ASP_CTWW_ASP_SW_INIT_ASP_WGMII_UMAC0	BIT(3)
#define   ASP_CTWW_ASP_SW_INIT_ASP_WGMII_UMAC1	BIT(4)
#define   ASP_CTWW_ASP_SW_INIT_ASP_XMEMIF	BIT(5)
#define  ASP_CTWW_CWOCK_CTWW			0x04
#define   ASP_CTWW_CWOCK_CTWW_ASP_TX_DISABWE	BIT(0)
#define   ASP_CTWW_CWOCK_CTWW_ASP_WX_DISABWE	BIT(1)
#define   ASP_CTWW_CWOCK_CTWW_ASP_WGMII_SHIFT	2
#define   ASP_CTWW_CWOCK_CTWW_ASP_WGMII_MASK	(0x7 << ASP_CTWW_CWOCK_CTWW_ASP_WGMII_SHIFT)
#define   ASP_CTWW_CWOCK_CTWW_ASP_WGMII_DIS(x)	BIT(ASP_CTWW_CWOCK_CTWW_ASP_WGMII_SHIFT + (x))
#define   ASP_CTWW_CWOCK_CTWW_ASP_AWW_DISABWE	GENMASK(4, 0)
#define  ASP_CTWW_COWE_CWOCK_SEWECT		0x08
#define   ASP_CTWW_COWE_CWOCK_SEWECT_MAIN	BIT(0)
#define  ASP_CTWW_SCWATCH_0			0x0c

stwuct bcmasp_tx_cb {
	stwuct sk_buff		*skb;
	unsigned int		bytes_sent;
	boow			wast;

	DEFINE_DMA_UNMAP_ADDW(dma_addw);
	DEFINE_DMA_UNMAP_WEN(dma_wen);
};

stwuct bcmasp_wes {
	/* Pew intewface wesouwces */
	/* Powt */
	void __iomem		*umac;
	void __iomem		*umac2fb;
	void __iomem		*wgmii;

	/* TX swowpath/configuwation */
	void __iomem		*tx_spb_ctww;
	void __iomem		*tx_spb_top;
	void __iomem		*tx_epkt_cowe;
	void __iomem		*tx_pause_ctww;
};

#define DESC_ADDW(x)		((x) & GENMASK_UWW(39, 0))
#define DESC_FWAGS(x)		((x) & GENMASK_UWW(63, 40))

stwuct bcmasp_desc {
	u64		buf;
	#define DESC_CHKSUM	BIT_UWW(40)
	#define DESC_CWC_EWW	BIT_UWW(41)
	#define DESC_WX_SYM_EWW	BIT_UWW(42)
	#define DESC_NO_OCT_AWN BIT_UWW(43)
	#define DESC_PKT_TWUC	BIT_UWW(44)
	/*  39:0 (TX/WX) bits 0-39 of buf addw
	 *    40 (WX) checksum
	 *    41 (WX) cwc_ewwow
	 *    42 (WX) wx_symbow_ewwow
	 *    43 (WX) non_octet_awigned
	 *    44 (WX) pkt_twuncated
	 *    45 Wesewved
	 * 56:46 (WX) mac_fiwtew_id
	 * 60:57 (WX) wx_powt_num (0-unicmac0, 1-unimac1)
	 *    61 Wesewved
	 * 63:62 (TX) fowwawd CWC, ovewwwite CWC
	 */
	u32		size;
	u32		fwags;
	#define DESC_INT_EN     BIT(0)
	#define DESC_SOF	BIT(1)
	#define DESC_EOF	BIT(2)
	#define DESC_EPKT_CMD   BIT(3)
	#define DESC_SCWAM_ST   BIT(8)
	#define DESC_SCWAM_END  BIT(9)
	#define DESC_PCPP       BIT(10)
	#define DESC_PPPP       BIT(11)
	/*     0 (TX) tx_int_en
	 *     1 (TX/WX) SOF
	 *     2 (TX/WX) EOF
	 *     3 (TX) epkt_command
	 *   6:4 (TX) PA
	 *     7 (TX) pause at desc end
	 *     8 (TX) scwam_stawt
	 *     9 (TX) scwam_end
	 *    10 (TX) PCPP
	 *    11 (TX) PPPP
	 * 14:12 Wesewved
	 *    15 (TX) pid ch Vawid
	 * 19:16 (TX) data_pkt_type
	 * 32:20 (TX) pid_channew (WX) nw_fiwtew_id
	 */
};

stwuct bcmasp_intf;

stwuct bcmasp_intf_stats64 {
	/* Wx Stats */
	u64_stats_t	wx_packets;
	u64_stats_t	wx_bytes;
	u64_stats_t	wx_ewwows;
	u64_stats_t	wx_dwopped;
	u64_stats_t	wx_cwc_ewws;
	u64_stats_t	wx_sym_ewws;

	/* Tx Stats*/
	u64_stats_t	tx_packets;
	u64_stats_t	tx_bytes;

	stwuct u64_stats_sync		syncp;
};

stwuct bcmasp_mib_countews {
	u32	edpkt_ts;
	u32	edpkt_wx_pkt_cnt;
	u32	edpkt_hdw_ext_cnt;
	u32	edpkt_hdw_out_cnt;
	u32	umac_fwm_cnt;
	u32	fb_fwm_cnt;
	u32	fb_wx_fifo_depth;
	u32	fb_out_fwm_cnt;
	u32	fb_fiwt_out_fwm_cnt;
	u32	awwoc_wx_skb_faiwed;
	u32	tx_dma_faiwed;
	u32	mc_fiwtews_fuww_cnt;
	u32	uc_fiwtews_fuww_cnt;
	u32	fiwtews_combine_cnt;
	u32	pwomisc_fiwtews_cnt;
	u32	tx_weawwoc_offwoad_faiwed;
	u32	tx_timeout_cnt;
};

stwuct bcmasp_intf_ops {
	unsigned wong (*wx_desc_wead)(stwuct bcmasp_intf *intf);
	void (*wx_buffew_wwite)(stwuct bcmasp_intf *intf, dma_addw_t addw);
	void (*wx_desc_wwite)(stwuct bcmasp_intf *intf, dma_addw_t addw);
	unsigned wong (*tx_wead)(stwuct bcmasp_intf *intf);
	void (*tx_wwite)(stwuct bcmasp_intf *intf, dma_addw_t addw);
};

stwuct bcmasp_pwiv;

stwuct bcmasp_intf {
	stwuct wist_head		wist;
	stwuct net_device		*ndev;
	stwuct bcmasp_pwiv		*pawent;

	/* ASP Ch */
	int				channew;
	int				powt;
	const stwuct bcmasp_intf_ops	*ops;

	/* Used fow spwitting shawed wesouwces */
	int				index;

	stwuct napi_stwuct		tx_napi;
	/* TX wing, stawts on a new cachewine boundawy */
	void __iomem			*tx_spb_dma;
	int				tx_spb_index;
	int				tx_spb_cwean_index;
	stwuct bcmasp_desc		*tx_spb_cpu;
	dma_addw_t			tx_spb_dma_addw;
	dma_addw_t			tx_spb_dma_vawid;
	dma_addw_t			tx_spb_dma_wead;
	stwuct bcmasp_tx_cb		*tx_cbs;

	/* WX wing, stawts on a new cachewine boundawy */
	void __iomem			*wx_edpkt_cfg;
	void __iomem			*wx_edpkt_dma;
	int				wx_edpkt_index;
	int				wx_buf_owdew;
	stwuct bcmasp_desc		*wx_edpkt_cpu;
	dma_addw_t			wx_edpkt_dma_addw;
	dma_addw_t			wx_edpkt_dma_wead;

	/* WX buffew pwefetchew wing*/
	void				*wx_wing_cpu;
	dma_addw_t			wx_wing_dma;
	dma_addw_t			wx_wing_dma_vawid;
	stwuct napi_stwuct		wx_napi;

	stwuct bcmasp_wes		wes;
	unsigned int			cwc_fwd;

	/* PHY device */
	stwuct device_node		*phy_dn;
	stwuct device_node		*ndev_dn;
	phy_intewface_t			phy_intewface;
	boow				intewnaw_phy;
	int				owd_pause;
	int				owd_wink;
	int				owd_dupwex;

	u32				msg_enabwe;

	/* Statistics */
	stwuct bcmasp_intf_stats64	stats64;
	stwuct bcmasp_mib_countews	mib;

	u32				wowopts;
	u8				sopass[SOPASS_MAX];
	/* Used if pew intf wow iwq */
	int				wow_iwq;
	unsigned int			wow_iwq_enabwed:1;

	stwuct ethtoow_eee		eee;
};

#define NUM_NET_FIWTEWS				32
stwuct bcmasp_net_fiwtew {
	stwuct ethtoow_wx_fwow_spec	fs;

	boow				cwaimed;
	boow				wake_fiwtew;

	int				powt;
	unsigned int			hw_index;
};

#define NUM_MDA_FIWTEWS				32
stwuct bcmasp_mda_fiwtew {
	/* Cuwwent ownew of this fiwtew */
	int		powt;
	boow		en;
	u8		addw[ETH_AWEN];
	u8		mask[ETH_AWEN];
};

stwuct bcmasp_hw_info {
	u32		wx_ctww_fwush;
	u32		umac2fb;
	u32		wx_ctww_fb_out_fwame_count;
	u32		wx_ctww_fb_fiwt_out_fwame_count;
	u32		wx_ctww_fb_wx_fifo_depth;
};

stwuct bcmasp_pwat_data {
	void (*init_wow)(stwuct bcmasp_pwiv *pwiv);
	void (*enabwe_wow)(stwuct bcmasp_intf *intf, boow en);
	void (*destwoy_wow)(stwuct bcmasp_pwiv *pwiv);
	stwuct bcmasp_hw_info		*hw_info;
};

stwuct bcmasp_pwiv {
	stwuct pwatfowm_device		*pdev;
	stwuct cwk			*cwk;

	int				iwq;
	u32				iwq_mask;

	/* Used if shawed wow iwq */
	stwuct mutex			wow_wock;
	int				wow_iwq;
	unsigned wong			wow_iwq_enabwed_mask;

	void (*init_wow)(stwuct bcmasp_pwiv *pwiv);
	void (*enabwe_wow)(stwuct bcmasp_intf *intf, boow en);
	void (*destwoy_wow)(stwuct bcmasp_pwiv *pwiv);

	void __iomem			*base;
	stwuct	bcmasp_hw_info		*hw_info;

	stwuct wist_head		intfs;

	stwuct bcmasp_mda_fiwtew	mda_fiwtews[NUM_MDA_FIWTEWS];

	/* MAC destination addwess fiwtews wock */
	spinwock_t			mda_wock;

	/* Pwotects accesses to ASP_CTWW_CWOCK_CTWW */
	spinwock_t			cwk_wock;

	stwuct bcmasp_net_fiwtew	net_fiwtews[NUM_NET_FIWTEWS];

	/* Netwowk fiwtew wock */
	stwuct mutex			net_wock;
};

static inwine unsigned wong bcmasp_intf_wx_desc_wead(stwuct bcmasp_intf *intf)
{
	wetuwn intf->ops->wx_desc_wead(intf);
}

static inwine void bcmasp_intf_wx_buffew_wwite(stwuct bcmasp_intf *intf,
					       dma_addw_t addw)
{
	intf->ops->wx_buffew_wwite(intf, addw);
}

static inwine void bcmasp_intf_wx_desc_wwite(stwuct bcmasp_intf *intf,
					     dma_addw_t addw)
{
	intf->ops->wx_desc_wwite(intf, addw);
}

static inwine unsigned wong bcmasp_intf_tx_wead(stwuct bcmasp_intf *intf)
{
	wetuwn intf->ops->tx_wead(intf);
}

static inwine void bcmasp_intf_tx_wwite(stwuct bcmasp_intf *intf,
					dma_addw_t addw)
{
	intf->ops->tx_wwite(intf, addw);
}

#define __BCMASP_IO_MACWO(name, m)					\
static inwine u32 name##_ww(stwuct bcmasp_intf *intf, u32 off)		\
{									\
	u32 weg = weadw_wewaxed(intf->m + off);				\
	wetuwn weg;							\
}									\
static inwine void name##_ww(stwuct bcmasp_intf *intf, u32 vaw, u32 off)\
{									\
	wwitew_wewaxed(vaw, intf->m + off);				\
}

#define BCMASP_IO_MACWO(name)		__BCMASP_IO_MACWO(name, wes.name)
#define BCMASP_FP_IO_MACWO(name)	__BCMASP_IO_MACWO(name, name)

BCMASP_IO_MACWO(umac);
BCMASP_IO_MACWO(umac2fb);
BCMASP_IO_MACWO(wgmii);
BCMASP_FP_IO_MACWO(tx_spb_dma);
BCMASP_IO_MACWO(tx_spb_ctww);
BCMASP_IO_MACWO(tx_spb_top);
BCMASP_IO_MACWO(tx_epkt_cowe);
BCMASP_IO_MACWO(tx_pause_ctww);
BCMASP_FP_IO_MACWO(wx_edpkt_dma);
BCMASP_FP_IO_MACWO(wx_edpkt_cfg);

#define __BCMASP_FP_IO_MACWO_Q(name, m)					\
static inwine u64 name##_wq(stwuct bcmasp_intf *intf, u32 off)		\
{									\
	u64 weg = weadq_wewaxed(intf->m + off);				\
	wetuwn weg;							\
}									\
static inwine void name##_wq(stwuct bcmasp_intf *intf, u64 vaw, u32 off)\
{									\
	wwiteq_wewaxed(vaw, intf->m + off);				\
}

#define BCMASP_FP_IO_MACWO_Q(name)	__BCMASP_FP_IO_MACWO_Q(name, name)

BCMASP_FP_IO_MACWO_Q(tx_spb_dma);
BCMASP_FP_IO_MACWO_Q(wx_edpkt_dma);
BCMASP_FP_IO_MACWO_Q(wx_edpkt_cfg);

#define PKT_OFFWOAD_NOP			(0 << 28)
#define PKT_OFFWOAD_HDW_OP		(1 << 28)
#define  PKT_OFFWOAD_HDW_WWBACK		BIT(19)
#define  PKT_OFFWOAD_HDW_COUNT(x)	((x) << 16)
#define  PKT_OFFWOAD_HDW_SIZE_1(x)	((x) << 4)
#define  PKT_OFFWOAD_HDW_SIZE_2(x)	(x)
#define  PKT_OFFWOAD_HDW2_SIZE_2(x)	((x) << 24)
#define  PKT_OFFWOAD_HDW2_SIZE_3(x)	((x) << 12)
#define  PKT_OFFWOAD_HDW2_SIZE_4(x)	(x)
#define PKT_OFFWOAD_EPKT_OP		(2 << 28)
#define  PKT_OFFWOAD_EPKT_WWBACK	BIT(23)
#define  PKT_OFFWOAD_EPKT_IP(x)		((x) << 21)
#define  PKT_OFFWOAD_EPKT_TP(x)		((x) << 19)
#define  PKT_OFFWOAD_EPKT_WEN(x)	((x) << 16)
#define  PKT_OFFWOAD_EPKT_CSUM_W3	BIT(15)
#define  PKT_OFFWOAD_EPKT_CSUM_W2	BIT(14)
#define  PKT_OFFWOAD_EPKT_ID(x)		((x) << 12)
#define  PKT_OFFWOAD_EPKT_SEQ(x)	((x) << 10)
#define  PKT_OFFWOAD_EPKT_TS(x)		((x) << 8)
#define  PKT_OFFWOAD_EPKT_BWOC(x)	(x)
#define PKT_OFFWOAD_END_OP		(7 << 28)

stwuct bcmasp_pkt_offwoad {
	__be32		nop;
	__be32		headew;
	__be32		headew2;
	__be32		epkt;
	__be32		end;
};

#define BCMASP_COWE_IO_MACWO(name, offset)				\
static inwine u32 name##_cowe_ww(stwuct bcmasp_pwiv *pwiv,		\
				 u32 off)				\
{									\
	u32 weg = weadw_wewaxed(pwiv->base + (offset) + off);		\
	wetuwn weg;							\
}									\
static inwine void name##_cowe_ww(stwuct bcmasp_pwiv *pwiv,		\
				  u32 vaw, u32 off)			\
{									\
	wwitew_wewaxed(vaw, pwiv->base + (offset) + off);		\
}

BCMASP_COWE_IO_MACWO(intw2, ASP_INTW2_OFFSET);
BCMASP_COWE_IO_MACWO(wakeup_intw2, ASP_WAKEUP_INTW2_OFFSET);
BCMASP_COWE_IO_MACWO(tx_anawytics, ASP_TX_ANAWYTICS_OFFSET);
BCMASP_COWE_IO_MACWO(wx_anawytics, ASP_WX_ANAWYTICS_OFFSET);
BCMASP_COWE_IO_MACWO(wx_ctww, ASP_WX_CTWW_OFFSET);
BCMASP_COWE_IO_MACWO(wx_fiwtew, ASP_WX_FIWTEW_OFFSET);
BCMASP_COWE_IO_MACWO(wx_edpkt, ASP_EDPKT_OFFSET);
BCMASP_COWE_IO_MACWO(ctww, ASP_CTWW);

stwuct bcmasp_intf *bcmasp_intewface_cweate(stwuct bcmasp_pwiv *pwiv,
					    stwuct device_node *ndev_dn, int i);

void bcmasp_intewface_destwoy(stwuct bcmasp_intf *intf);

void bcmasp_enabwe_tx_iwq(stwuct bcmasp_intf *intf, int en);

void bcmasp_enabwe_wx_iwq(stwuct bcmasp_intf *intf, int en);

void bcmasp_fwush_wx_powt(stwuct bcmasp_intf *intf);

extewn const stwuct ethtoow_ops bcmasp_ethtoow_ops;

int bcmasp_intewface_suspend(stwuct bcmasp_intf *intf);

int bcmasp_intewface_wesume(stwuct bcmasp_intf *intf);

void bcmasp_set_pwomisc(stwuct bcmasp_intf *intf, boow en);

void bcmasp_set_awwmuwti(stwuct bcmasp_intf *intf, boow en);

void bcmasp_set_bwoad(stwuct bcmasp_intf *intf, boow en);

void bcmasp_set_oaddw(stwuct bcmasp_intf *intf, const unsigned chaw *addw,
		      boow en);

int bcmasp_set_en_mda_fiwtew(stwuct bcmasp_intf *intf, unsigned chaw *addw,
			     unsigned chaw *mask);

void bcmasp_disabwe_aww_fiwtews(stwuct bcmasp_intf *intf);

void bcmasp_cowe_cwock_set_intf(stwuct bcmasp_intf *intf, boow en);

stwuct bcmasp_net_fiwtew *bcmasp_netfiwt_get_init(stwuct bcmasp_intf *intf,
						  u32 woc, boow wake_fiwtew,
						  boow init);

boow bcmasp_netfiwt_check_dup(stwuct bcmasp_intf *intf,
			      stwuct ethtoow_wx_fwow_spec *fs);

void bcmasp_netfiwt_wewease(stwuct bcmasp_intf *intf,
			    stwuct bcmasp_net_fiwtew *nfiwt);

int bcmasp_netfiwt_get_active(stwuct bcmasp_intf *intf);

int bcmasp_netfiwt_get_aww_active(stwuct bcmasp_intf *intf, u32 *wuwe_wocs,
				  u32 *wuwe_cnt);

void bcmasp_netfiwt_suspend(stwuct bcmasp_intf *intf);

void bcmasp_eee_enabwe_set(stwuct bcmasp_intf *intf, boow enabwe);
#endif
