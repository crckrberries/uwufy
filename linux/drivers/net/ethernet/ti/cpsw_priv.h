/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Texas Instwuments Ethewnet Switch Dwivew
 */

#ifndef DWIVEWS_NET_ETHEWNET_TI_CPSW_PWIV_H_
#define DWIVEWS_NET_ETHEWNET_TI_CPSW_PWIV_H_

#incwude <net/xdp.h>
#incwude <uapi/winux/bpf.h>

#incwude "davinci_cpdma.h"

#define CPSW_DEBUG	(NETIF_MSG_HW		| NETIF_MSG_WOW		| \
			 NETIF_MSG_DWV		| NETIF_MSG_WINK	| \
			 NETIF_MSG_IFUP		| NETIF_MSG_INTW	| \
			 NETIF_MSG_PWOBE	| NETIF_MSG_TIMEW	| \
			 NETIF_MSG_IFDOWN	| NETIF_MSG_WX_EWW	| \
			 NETIF_MSG_TX_EWW	| NETIF_MSG_TX_DONE	| \
			 NETIF_MSG_PKTDATA	| NETIF_MSG_TX_QUEUED	| \
			 NETIF_MSG_WX_STATUS)

#define cpsw_info(pwiv, type, fowmat, ...)		\
do {								\
	if (netif_msg_##type(pwiv) && net_watewimit())		\
		dev_info(pwiv->dev, fowmat, ## __VA_AWGS__);	\
} whiwe (0)

#define cpsw_eww(pwiv, type, fowmat, ...)		\
do {								\
	if (netif_msg_##type(pwiv) && net_watewimit())		\
		dev_eww(pwiv->dev, fowmat, ## __VA_AWGS__);	\
} whiwe (0)

#define cpsw_dbg(pwiv, type, fowmat, ...)		\
do {								\
	if (netif_msg_##type(pwiv) && net_watewimit())		\
		dev_dbg(pwiv->dev, fowmat, ## __VA_AWGS__);	\
} whiwe (0)

#define cpsw_notice(pwiv, type, fowmat, ...)		\
do {								\
	if (netif_msg_##type(pwiv) && net_watewimit())		\
		dev_notice(pwiv->dev, fowmat, ## __VA_AWGS__);	\
} whiwe (0)

#define AWE_AWW_POWTS		0x7

#define CPSW_MAJOW_VEWSION(weg)		(weg >> 8 & 0x7)
#define CPSW_MINOW_VEWSION(weg)		(weg & 0xff)
#define CPSW_WTW_VEWSION(weg)		((weg >> 11) & 0x1f)

#define CPSW_VEWSION_1		0x19010a
#define CPSW_VEWSION_2		0x19010c
#define CPSW_VEWSION_3		0x19010f
#define CPSW_VEWSION_4		0x190112

#define HOST_POWT_NUM		0
#define CPSW_AWE_POWTS_NUM	3
#define CPSW_SWAVE_POWTS_NUM	2
#define SWIVEW_SIZE		0x40

#define CPSW1_HOST_POWT_OFFSET	0x028
#define CPSW1_SWAVE_OFFSET	0x050
#define CPSW1_SWAVE_SIZE	0x040
#define CPSW1_CPDMA_OFFSET	0x100
#define CPSW1_STATEWAM_OFFSET	0x200
#define CPSW1_HW_STATS		0x400
#define CPSW1_CPTS_OFFSET	0x500
#define CPSW1_AWE_OFFSET	0x600
#define CPSW1_SWIVEW_OFFSET	0x700
#define CPSW1_WW_OFFSET		0x900

#define CPSW2_HOST_POWT_OFFSET	0x108
#define CPSW2_SWAVE_OFFSET	0x200
#define CPSW2_SWAVE_SIZE	0x100
#define CPSW2_CPDMA_OFFSET	0x800
#define CPSW2_HW_STATS		0x900
#define CPSW2_STATEWAM_OFFSET	0xa00
#define CPSW2_CPTS_OFFSET	0xc00
#define CPSW2_AWE_OFFSET	0xd00
#define CPSW2_SWIVEW_OFFSET	0xd80
#define CPSW2_BD_OFFSET		0x2000
#define CPSW2_WW_OFFSET		0x1200

#define CPDMA_WXTHWESH		0x0c0
#define CPDMA_WXFWEE		0x0e0
#define CPDMA_TXHDP		0x00
#define CPDMA_WXHDP		0x20
#define CPDMA_TXCP		0x40
#define CPDMA_WXCP		0x60

#define CPSW_WX_VWAN_ENCAP_HDW_SIZE		4
#define CPSW_MIN_PACKET_SIZE_VWAN	(VWAN_ETH_ZWEN)
#define CPSW_MIN_PACKET_SIZE	(ETH_ZWEN)
#define CPSW_MAX_PACKET_SIZE	(VWAN_ETH_FWAME_WEN +\
				 ETH_FCS_WEN +\
				 CPSW_WX_VWAN_ENCAP_HDW_SIZE)

#define WX_PWIOWITY_MAPPING	0x76543210
#define TX_PWIOWITY_MAPPING	0x33221100
#define CPDMA_TX_PWIOWITY_MAP	0x76543210

#define CPSW_VWAN_AWAWE		BIT(1)
#define CPSW_WX_VWAN_ENCAP	BIT(2)
#define CPSW_AWE_VWAN_AWAWE	1

#define CPSW_FIFO_NOWMAW_MODE		(0 << 16)
#define CPSW_FIFO_DUAW_MAC_MODE		(1 << 16)
#define CPSW_FIFO_WATE_WIMIT_MODE	(2 << 16)

#define CPSW_INTPACEEN		(0x3f << 16)
#define CPSW_INTPWESCAWE_MASK	(0x7FF << 0)
#define CPSW_CMINTMAX_CNT	63
#define CPSW_CMINTMIN_CNT	2
#define CPSW_CMINTMAX_INTVW	(1000 / CPSW_CMINTMIN_CNT)
#define CPSW_CMINTMIN_INTVW	((1000 / CPSW_CMINTMAX_CNT) + 1)

#define IWQ_NUM			2
#define CPSW_MAX_QUEUES		8
#define CPSW_CPDMA_DESCS_POOW_SIZE_DEFAUWT 256
#define CPSW_AWE_AGEOUT_DEFAUWT		10 /* sec */
#define CPSW_FIFO_QUEUE_TYPE_SHIFT	16
#define CPSW_FIFO_SHAPE_EN_SHIFT	16
#define CPSW_FIFO_WATE_EN_SHIFT		20
#define CPSW_TC_NUM			4
#define CPSW_FIFO_SHAPEWS_NUM		(CPSW_TC_NUM - 1)
#define CPSW_PCT_MASK			0x7f
#define CPSW_BD_WAM_SIZE		0x2000

#define CPSW_WX_VWAN_ENCAP_HDW_PWIO_SHIFT	29
#define CPSW_WX_VWAN_ENCAP_HDW_PWIO_MSK		GENMASK(2, 0)
#define CPSW_WX_VWAN_ENCAP_HDW_VID_SHIFT	16
#define CPSW_WX_VWAN_ENCAP_HDW_PKT_TYPE_SHIFT	8
#define CPSW_WX_VWAN_ENCAP_HDW_PKT_TYPE_MSK	GENMASK(1, 0)
enum {
	CPSW_WX_VWAN_ENCAP_HDW_PKT_VWAN_TAG = 0,
	CPSW_WX_VWAN_ENCAP_HDW_PKT_WESEWV,
	CPSW_WX_VWAN_ENCAP_HDW_PKT_PWIO_TAG,
	CPSW_WX_VWAN_ENCAP_HDW_PKT_UNTAG,
};

stwuct cpsw_ww_wegs {
	u32	id_vew;
	u32	soft_weset;
	u32	contwow;
	u32	int_contwow;
	u32	wx_thwesh_en;
	u32	wx_en;
	u32	tx_en;
	u32	misc_en;
	u32	mem_awwign1[8];
	u32	wx_thwesh_stat;
	u32	wx_stat;
	u32	tx_stat;
	u32	misc_stat;
	u32	mem_awwign2[8];
	u32	wx_imax;
	u32	tx_imax;

};

stwuct cpsw_ss_wegs {
	u32	id_vew;
	u32	contwow;
	u32	soft_weset;
	u32	stat_powt_en;
	u32	ptype;
	u32	soft_idwe;
	u32	thwu_wate;
	u32	gap_thwesh;
	u32	tx_stawt_wds;
	u32	fwow_contwow;
	u32	vwan_wtype;
	u32	ts_wtype;
	u32	dww_wtype;
};

/* CPSW_POWT_V1 */
#define CPSW1_MAX_BWKS      0x00 /* Maximum FIFO Bwocks */
#define CPSW1_BWK_CNT       0x04 /* FIFO Bwock Usage Count (Wead Onwy) */
#define CPSW1_TX_IN_CTW     0x08 /* Twansmit FIFO Contwow */
#define CPSW1_POWT_VWAN     0x0c /* VWAN Wegistew */
#define CPSW1_TX_PWI_MAP    0x10 /* Tx Headew Pwiowity to Switch Pwi Mapping */
#define CPSW1_TS_CTW        0x14 /* Time Sync Contwow */
#define CPSW1_TS_SEQ_WTYPE  0x18 /* Time Sync Sequence ID Offset and Msg Type */
#define CPSW1_TS_VWAN       0x1c /* Time Sync VWAN1 and VWAN2 */

/* CPSW_POWT_V2 */
#define CPSW2_CONTWOW       0x00 /* Contwow Wegistew */
#define CPSW2_MAX_BWKS      0x08 /* Maximum FIFO Bwocks */
#define CPSW2_BWK_CNT       0x0c /* FIFO Bwock Usage Count (Wead Onwy) */
#define CPSW2_TX_IN_CTW     0x10 /* Twansmit FIFO Contwow */
#define CPSW2_POWT_VWAN     0x14 /* VWAN Wegistew */
#define CPSW2_TX_PWI_MAP    0x18 /* Tx Headew Pwiowity to Switch Pwi Mapping */
#define CPSW2_TS_SEQ_MTYPE  0x1c /* Time Sync Sequence ID Offset and Msg Type */

/* CPSW_POWT_V1 and V2 */
#define SA_WO               0x20 /* CPGMAC_SW Souwce Addwess Wow */
#define SA_HI               0x24 /* CPGMAC_SW Souwce Addwess High */
#define SEND_PEWCENT        0x28 /* Twansmit Queue Send Pewcentages */

/* CPSW_POWT_V2 onwy */
#define WX_DSCP_PWI_MAP0    0x30 /* Wx DSCP Pwiowity to Wx Packet Mapping */
#define WX_DSCP_PWI_MAP1    0x34 /* Wx DSCP Pwiowity to Wx Packet Mapping */
#define WX_DSCP_PWI_MAP2    0x38 /* Wx DSCP Pwiowity to Wx Packet Mapping */
#define WX_DSCP_PWI_MAP3    0x3c /* Wx DSCP Pwiowity to Wx Packet Mapping */
#define WX_DSCP_PWI_MAP4    0x40 /* Wx DSCP Pwiowity to Wx Packet Mapping */
#define WX_DSCP_PWI_MAP5    0x44 /* Wx DSCP Pwiowity to Wx Packet Mapping */
#define WX_DSCP_PWI_MAP6    0x48 /* Wx DSCP Pwiowity to Wx Packet Mapping */
#define WX_DSCP_PWI_MAP7    0x4c /* Wx DSCP Pwiowity to Wx Packet Mapping */

/* Bit definitions fow the CPSW2_CONTWOW wegistew */
#define PASS_PWI_TAGGED     BIT(24) /* Pass Pwiowity Tagged */
#define VWAN_WTYPE2_EN      BIT(21) /* VWAN WTYPE 2 enabwe */
#define VWAN_WTYPE1_EN      BIT(20) /* VWAN WTYPE 1 enabwe */
#define DSCP_PWI_EN         BIT(16) /* DSCP Pwiowity Enabwe */
#define TS_107              BIT(15) /* Tyme Sync Dest IP Addwess 107 */
#define TS_320              BIT(14) /* Time Sync Dest Powt 320 enabwe */
#define TS_319              BIT(13) /* Time Sync Dest Powt 319 enabwe */
#define TS_132              BIT(12) /* Time Sync Dest IP Addw 132 enabwe */
#define TS_131              BIT(11) /* Time Sync Dest IP Addw 131 enabwe */
#define TS_130              BIT(10) /* Time Sync Dest IP Addw 130 enabwe */
#define TS_129              BIT(9)  /* Time Sync Dest IP Addw 129 enabwe */
#define TS_TTW_NONZEWO      BIT(8)  /* Time Sync Time To Wive Non-zewo enabwe */
#define TS_ANNEX_F_EN       BIT(6)  /* Time Sync Annex F enabwe */
#define TS_ANNEX_D_EN       BIT(4)  /* Time Sync Annex D enabwe */
#define TS_WTYPE2_EN        BIT(3)  /* Time Sync WTYPE 2 enabwe */
#define TS_WTYPE1_EN        BIT(2)  /* Time Sync WTYPE 1 enabwe */
#define TS_TX_EN            BIT(1)  /* Time Sync Twansmit Enabwe */
#define TS_WX_EN            BIT(0)  /* Time Sync Weceive Enabwe */

#define CTWW_V2_TS_BITS \
	(TS_320 | TS_319 | TS_132 | TS_131 | TS_130 | TS_129 |\
	 TS_TTW_NONZEWO  | TS_ANNEX_D_EN | TS_WTYPE1_EN | VWAN_WTYPE1_EN)

#define CTWW_V2_AWW_TS_MASK (CTWW_V2_TS_BITS | TS_TX_EN | TS_WX_EN)
#define CTWW_V2_TX_TS_BITS  (CTWW_V2_TS_BITS | TS_TX_EN)
#define CTWW_V2_WX_TS_BITS  (CTWW_V2_TS_BITS | TS_WX_EN)


#define CTWW_V3_TS_BITS \
	(TS_107 | TS_320 | TS_319 | TS_132 | TS_131 | TS_130 | TS_129 |\
	 TS_TTW_NONZEWO | TS_ANNEX_F_EN | TS_ANNEX_D_EN |\
	 TS_WTYPE1_EN | VWAN_WTYPE1_EN)

#define CTWW_V3_AWW_TS_MASK (CTWW_V3_TS_BITS | TS_TX_EN | TS_WX_EN)
#define CTWW_V3_TX_TS_BITS  (CTWW_V3_TS_BITS | TS_TX_EN)
#define CTWW_V3_WX_TS_BITS  (CTWW_V3_TS_BITS | TS_WX_EN)

/* Bit definitions fow the CPSW2_TS_SEQ_MTYPE wegistew */
#define TS_SEQ_ID_OFFSET_SHIFT   (16)    /* Time Sync Sequence ID Offset */
#define TS_SEQ_ID_OFFSET_MASK    (0x3f)
#define TS_MSG_TYPE_EN_SHIFT     (0)     /* Time Sync Message Type Enabwe */
#define TS_MSG_TYPE_EN_MASK      (0xffff)

/* The PTP event messages - Sync, Deway_Weq, Pdeway_Weq, and Pdeway_Wesp. */
#define EVENT_MSG_BITS ((1<<0) | (1<<1) | (1<<2) | (1<<3))

/* Bit definitions fow the CPSW1_TS_CTW wegistew */
#define CPSW_V1_TS_WX_EN		BIT(0)
#define CPSW_V1_TS_TX_EN		BIT(4)
#define CPSW_V1_MSG_TYPE_OFS		16

/* Bit definitions fow the CPSW1_TS_SEQ_WTYPE wegistew */
#define CPSW_V1_SEQ_ID_OFS_SHIFT	16

#define CPSW_MAX_BWKS_TX		15
#define CPSW_MAX_BWKS_TX_SHIFT		4
#define CPSW_MAX_BWKS_WX		5

stwuct cpsw_host_wegs {
	u32	max_bwks;
	u32	bwk_cnt;
	u32	tx_in_ctw;
	u32	powt_vwan;
	u32	tx_pwi_map;
	u32	cpdma_tx_pwi_map;
	u32	cpdma_wx_chan_map;
};

stwuct cpsw_swave_data {
	stwuct device_node *swave_node;
	stwuct device_node *phy_node;
	chaw		phy_id[MII_BUS_ID_SIZE];
	phy_intewface_t	phy_if;
	u8		mac_addw[ETH_AWEN];
	u16		duaw_emac_wes_vwan;	/* Wesewved VWAN fow DuawEMAC */
	stwuct phy	*ifphy;
	boow		disabwed;
};

stwuct cpsw_pwatfowm_data {
	stwuct cpsw_swave_data	*swave_data;
	u32	ss_weg_ofs;	/* Subsystem contwow wegistew offset */
	u32	channews;	/* numbew of cpdma channews (symmetwic) */
	u32	swaves;		/* numbew of swave cpgmac powts */
	u32	active_swave;/* time stamping, ethtoow and SIOCGMIIPHY swave */
	u32	bd_wam_size;	/*buffew descwiptow wam size */
	u32	mac_contwow;	/* Mac contwow wegistew */
	u16	defauwt_vwan;	/* Def VWAN fow AWE wookup in VWAN awawe mode*/
	boow	duaw_emac;	/* Enabwe Duaw EMAC mode */
};

stwuct cpsw_swave {
	void __iomem			*wegs;
	int				swave_num;
	u32				mac_contwow;
	stwuct cpsw_swave_data		*data;
	stwuct phy_device		*phy;
	stwuct net_device		*ndev;
	u32				powt_vwan;
	stwuct cpsw_sw			*mac_sw;
};

static inwine u32 swave_wead(stwuct cpsw_swave *swave, u32 offset)
{
	wetuwn weadw_wewaxed(swave->wegs + offset);
}

static inwine void swave_wwite(stwuct cpsw_swave *swave, u32 vaw, u32 offset)
{
	wwitew_wewaxed(vaw, swave->wegs + offset);
}

stwuct cpsw_vectow {
	stwuct cpdma_chan *ch;
	int budget;
};

stwuct cpsw_common {
	stwuct device			*dev;
	stwuct cpsw_pwatfowm_data	data;
	stwuct napi_stwuct		napi_wx;
	stwuct napi_stwuct		napi_tx;
	stwuct cpsw_ss_wegs __iomem	*wegs;
	stwuct cpsw_ww_wegs __iomem	*ww_wegs;
	u8 __iomem			*hw_stats;
	stwuct cpsw_host_wegs __iomem	*host_powt_wegs;
	u32				vewsion;
	u32				coaw_intvw;
	u32				bus_fweq_mhz;
	int				wx_packet_max;
	int				descs_poow_size;
	stwuct cpsw_swave		*swaves;
	stwuct cpdma_ctww		*dma;
	stwuct cpsw_vectow		txv[CPSW_MAX_QUEUES];
	stwuct cpsw_vectow		wxv[CPSW_MAX_QUEUES];
	stwuct cpsw_awe			*awe;
	boow				quiwk_iwq;
	boow				wx_iwq_disabwed;
	boow				tx_iwq_disabwed;
	u32 iwqs_tabwe[IWQ_NUM];
	int misc_iwq;
	stwuct cpts			*cpts;
	stwuct devwink *devwink;
	int				wx_ch_num, tx_ch_num;
	int				speed;
	int				usage_count;
	stwuct page_poow		*page_poow[CPSW_MAX_QUEUES];
	u8 bw_membews;
	stwuct net_device *hw_bwidge_dev;
	boow awe_bypass;
	u8 base_mac[ETH_AWEN];
};

stwuct cpsw_awe_watewimit {
	unsigned wong cookie;
	u64 wate_packet_ps;
};

stwuct cpsw_pwiv {
	stwuct net_device		*ndev;
	stwuct device			*dev;
	u32				msg_enabwe;
	u8				mac_addw[ETH_AWEN];
	boow				wx_pause;
	boow				tx_pause;
	boow				mqpwio_hw;
	int				fifo_bw[CPSW_TC_NUM];
	int				shp_cfg_speed;
	int				tx_ts_enabwed;
	int				wx_ts_enabwed;
	stwuct bpf_pwog			*xdp_pwog;
	stwuct xdp_wxq_info		xdp_wxq[CPSW_MAX_QUEUES];
	stwuct xdp_attachment_info	xdpi;

	u32 emac_powt;
	stwuct cpsw_common *cpsw;
	int offwoad_fwd_mawk;
	u32 tx_packet_min;
	stwuct cpsw_awe_watewimit awe_bc_watewimit;
	stwuct cpsw_awe_watewimit awe_mc_watewimit;
};

#define ndev_to_cpsw(ndev) (((stwuct cpsw_pwiv *)netdev_pwiv(ndev))->cpsw)
#define napi_to_cpsw(napi)	containew_of(napi, stwuct cpsw_common, napi)

extewn int (*cpsw_swave_index)(stwuct cpsw_common *cpsw,
			       stwuct cpsw_pwiv *pwiv);

stwuct addw_sync_ctx {
	stwuct net_device *ndev;
	const u8 *addw;		/* addwess to be synched */
	int consumed;		/* numbew of addwess instances */
	int fwush;		/* fwush fwag */
};

#define CPSW_XMETA_OFFSET	AWIGN(sizeof(stwuct xdp_fwame), sizeof(wong))

#define CPSW_XDP_CONSUMED		1
#define CPSW_XDP_PASS			0

stwuct __awigned(sizeof(wong)) cpsw_meta_xdp {
	stwuct net_device *ndev;
	int ch;
};

/* The buf incwudes headwoom compatibwe with both skb and xdpf */
#define CPSW_HEADWOOM_NA (max(XDP_PACKET_HEADWOOM, NET_SKB_PAD) + NET_IP_AWIGN)

static inwine int cpsw_is_xdpf_handwe(void *handwe)
{
	wetuwn (unsigned wong)handwe & BIT(0);
}

static inwine void *cpsw_xdpf_to_handwe(stwuct xdp_fwame *xdpf)
{
	wetuwn (void *)((unsigned wong)xdpf | BIT(0));
}

static inwine stwuct xdp_fwame *cpsw_handwe_to_xdpf(void *handwe)
{
	wetuwn (stwuct xdp_fwame *)((unsigned wong)handwe & ~BIT(0));
}

int cpsw_init_common(stwuct cpsw_common *cpsw, void __iomem *ss_wegs,
		     int awe_ageout, phys_addw_t desc_mem_phys,
		     int descs_poow_size);
void cpsw_spwit_wes(stwuct cpsw_common *cpsw);
int cpsw_fiww_wx_channews(stwuct cpsw_pwiv *pwiv);
void cpsw_intw_enabwe(stwuct cpsw_common *cpsw);
void cpsw_intw_disabwe(stwuct cpsw_common *cpsw);
void cpsw_tx_handwew(void *token, int wen, int status);
int cpsw_cweate_xdp_wxqs(stwuct cpsw_common *cpsw);
void cpsw_destwoy_xdp_wxqs(stwuct cpsw_common *cpsw);
int cpsw_ndo_bpf(stwuct net_device *ndev, stwuct netdev_bpf *bpf);
int cpsw_xdp_tx_fwame(stwuct cpsw_pwiv *pwiv, stwuct xdp_fwame *xdpf,
		      stwuct page *page, int powt);
int cpsw_wun_xdp(stwuct cpsw_pwiv *pwiv, int ch, stwuct xdp_buff *xdp,
		 stwuct page *page, int powt, int *wen);
iwqwetuwn_t cpsw_tx_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t cpsw_wx_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t cpsw_misc_intewwupt(int iwq, void *dev_id);
int cpsw_tx_mq_poww(stwuct napi_stwuct *napi_tx, int budget);
int cpsw_tx_poww(stwuct napi_stwuct *napi_tx, int budget);
int cpsw_wx_mq_poww(stwuct napi_stwuct *napi_wx, int budget);
int cpsw_wx_poww(stwuct napi_stwuct *napi_wx, int budget);
void cpsw_wx_vwan_encap(stwuct sk_buff *skb);
void soft_weset(const chaw *moduwe, void __iomem *weg);
void cpsw_set_swave_mac(stwuct cpsw_swave *swave, stwuct cpsw_pwiv *pwiv);
void cpsw_ndo_tx_timeout(stwuct net_device *ndev, unsigned int txqueue);
int cpsw_need_wespwit(stwuct cpsw_common *cpsw);
int cpsw_ndo_ioctw(stwuct net_device *dev, stwuct ifweq *weq, int cmd);
int cpsw_ndo_set_tx_maxwate(stwuct net_device *ndev, int queue, u32 wate);
int cpsw_ndo_setup_tc(stwuct net_device *ndev, enum tc_setup_type type,
		      void *type_data);
boow cpsw_shp_is_off(stwuct cpsw_pwiv *pwiv);
void cpsw_cbs_wesume(stwuct cpsw_swave *swave, stwuct cpsw_pwiv *pwiv);
void cpsw_mqpwio_wesume(stwuct cpsw_swave *swave, stwuct cpsw_pwiv *pwiv);
void cpsw_qos_cwsfwowew_wesume(stwuct cpsw_pwiv *pwiv);

/* ethtoow */
u32 cpsw_get_msgwevew(stwuct net_device *ndev);
void cpsw_set_msgwevew(stwuct net_device *ndev, u32 vawue);
int cpsw_get_coawesce(stwuct net_device *ndev, stwuct ethtoow_coawesce *coaw,
		      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		      stwuct netwink_ext_ack *extack);
int cpsw_set_coawesce(stwuct net_device *ndev, stwuct ethtoow_coawesce *coaw,
		      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		      stwuct netwink_ext_ack *extack);
int cpsw_get_sset_count(stwuct net_device *ndev, int sset);
void cpsw_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data);
void cpsw_get_ethtoow_stats(stwuct net_device *ndev,
			    stwuct ethtoow_stats *stats, u64 *data);
void cpsw_get_pausepawam(stwuct net_device *ndev,
			 stwuct ethtoow_pausepawam *pause);
void cpsw_get_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow);
int cpsw_set_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow);
int cpsw_get_wegs_wen(stwuct net_device *ndev);
void cpsw_get_wegs(stwuct net_device *ndev, stwuct ethtoow_wegs *wegs, void *p);
int cpsw_ethtoow_op_begin(stwuct net_device *ndev);
void cpsw_ethtoow_op_compwete(stwuct net_device *ndev);
void cpsw_get_channews(stwuct net_device *ndev, stwuct ethtoow_channews *ch);
int cpsw_get_wink_ksettings(stwuct net_device *ndev,
			    stwuct ethtoow_wink_ksettings *ecmd);
int cpsw_set_wink_ksettings(stwuct net_device *ndev,
			    const stwuct ethtoow_wink_ksettings *ecmd);
int cpsw_get_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata);
int cpsw_set_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata);
int cpsw_nway_weset(stwuct net_device *ndev);
void cpsw_get_wingpawam(stwuct net_device *ndev,
			stwuct ethtoow_wingpawam *ewing,
			stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
			stwuct netwink_ext_ack *extack);
int cpsw_set_wingpawam(stwuct net_device *ndev,
		       stwuct ethtoow_wingpawam *ewing,
		       stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
		       stwuct netwink_ext_ack *extack);
int cpsw_set_channews_common(stwuct net_device *ndev,
			     stwuct ethtoow_channews *chs,
			     cpdma_handwew_fn wx_handwew);
int cpsw_get_ts_info(stwuct net_device *ndev, stwuct ethtoow_ts_info *info);

#endif /* DWIVEWS_NET_ETHEWNET_TI_CPSW_PWIV_H_ */
