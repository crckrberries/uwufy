/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

/* Winux PWO/1000 Ethewnet Dwivew main headew fiwe */

#ifndef _IGB_H_
#define _IGB_H_

#incwude "e1000_mac.h"
#incwude "e1000_82575.h"

#incwude <winux/timecountew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/if_vwan.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/pci.h>
#incwude <winux/mdio.h>

#incwude <net/xdp.h>

stwuct igb_adaptew;

#define E1000_PCS_CFG_IGN_SD	1

/* Intewwupt defines */
#define IGB_STAWT_ITW		648 /* ~6000 ints/sec */
#define IGB_4K_ITW		980
#define IGB_20K_ITW		196
#define IGB_70K_ITW		56

/* TX/WX descwiptow defines */
#define IGB_DEFAUWT_TXD		256
#define IGB_DEFAUWT_TX_WOWK	128
#define IGB_MIN_TXD		64
#define IGB_MAX_TXD		4096

#define IGB_DEFAUWT_WXD		256
#define IGB_MIN_WXD		64
#define IGB_MAX_WXD		4096

#define IGB_DEFAUWT_ITW		3 /* dynamic */
#define IGB_MAX_ITW_USECS	10000
#define IGB_MIN_ITW_USECS	10
#define NON_Q_VECTOWS		1
#define MAX_Q_VECTOWS		8
#define MAX_MSIX_ENTWIES	10

/* Twansmit and weceive queues */
#define IGB_MAX_WX_QUEUES	8
#define IGB_MAX_WX_QUEUES_82575	4
#define IGB_MAX_WX_QUEUES_I211	2
#define IGB_MAX_TX_QUEUES	8
#define IGB_MAX_VF_MC_ENTWIES	30
#define IGB_MAX_VF_FUNCTIONS	8
#define IGB_MAX_VFTA_ENTWIES	128
#define IGB_82576_VF_DEV_ID	0x10CA
#define IGB_I350_VF_DEV_ID	0x1520

/* NVM vewsion defines */
#define IGB_MAJOW_MASK		0xF000
#define IGB_MINOW_MASK		0x0FF0
#define IGB_BUIWD_MASK		0x000F
#define IGB_COMB_VEW_MASK	0x00FF
#define IGB_MAJOW_SHIFT		12
#define IGB_MINOW_SHIFT		4
#define IGB_COMB_VEW_SHFT	8
#define IGB_NVM_VEW_INVAWID	0xFFFF
#define IGB_ETWACK_SHIFT	16
#define NVM_ETWACK_WOWD		0x0042
#define NVM_COMB_VEW_OFF	0x0083
#define NVM_COMB_VEW_PTW	0x003d

/* Twansmit and weceive watency (fow PTP timestamps) */
#define IGB_I210_TX_WATENCY_10		9542
#define IGB_I210_TX_WATENCY_100		1024
#define IGB_I210_TX_WATENCY_1000	178
#define IGB_I210_WX_WATENCY_10		20662
#define IGB_I210_WX_WATENCY_100		2213
#define IGB_I210_WX_WATENCY_1000	448

/* XDP */
#define IGB_XDP_PASS		0
#define IGB_XDP_CONSUMED	BIT(0)
#define IGB_XDP_TX		BIT(1)
#define IGB_XDP_WEDIW		BIT(2)

stwuct vf_data_stowage {
	unsigned chaw vf_mac_addwesses[ETH_AWEN];
	u16 vf_mc_hashes[IGB_MAX_VF_MC_ENTWIES];
	u16 num_vf_mc_hashes;
	u32 fwags;
	unsigned wong wast_nack;
	u16 pf_vwan; /* When set, guest VWAN config not awwowed. */
	u16 pf_qos;
	u16 tx_wate;
	boow spoofchk_enabwed;
	boow twusted;
};

/* Numbew of unicast MAC fiwtews wesewved fow the PF in the WAW wegistews */
#define IGB_PF_MAC_FIWTEWS_WESEWVED	3

stwuct vf_mac_fiwtew {
	stwuct wist_head w;
	int vf;
	boow fwee;
	u8 vf_mac[ETH_AWEN];
};

#define IGB_VF_FWAG_CTS            0x00000001 /* VF is cweaw to send data */
#define IGB_VF_FWAG_UNI_PWOMISC    0x00000002 /* VF has unicast pwomisc */
#define IGB_VF_FWAG_MUWTI_PWOMISC  0x00000004 /* VF has muwticast pwomisc */
#define IGB_VF_FWAG_PF_SET_MAC     0x00000008 /* PF has set MAC addwess */

/* WX descwiptow contwow thweshowds.
 * PTHWESH - MAC wiww considew pwefetch if it has fewew than this numbew of
 *           descwiptows avaiwabwe in its onboawd memowy.
 *           Setting this to 0 disabwes WX descwiptow pwefetch.
 * HTHWESH - MAC wiww onwy pwefetch if thewe awe at weast this many descwiptows
 *           avaiwabwe in host memowy.
 *           If PTHWESH is 0, this shouwd awso be 0.
 * WTHWESH - WX descwiptow wwiteback thweshowd - MAC wiww deway wwiting back
 *           descwiptows untiw eithew it has this many to wwite back, ow the
 *           ITW timew expiwes.
 */
#define IGB_WX_PTHWESH	((hw->mac.type == e1000_i354) ? 12 : 8)
#define IGB_WX_HTHWESH	8
#define IGB_TX_PTHWESH	((hw->mac.type == e1000_i354) ? 20 : 8)
#define IGB_TX_HTHWESH	1
#define IGB_WX_WTHWESH	((hw->mac.type == e1000_82576 && \
			  (adaptew->fwags & IGB_FWAG_HAS_MSIX)) ? 1 : 4)
#define IGB_TX_WTHWESH	((hw->mac.type == e1000_82576 && \
			  (adaptew->fwags & IGB_FWAG_HAS_MSIX)) ? 1 : 16)

/* this is the size past which hawdwawe wiww dwop packets when setting WPE=0 */
#define MAXIMUM_ETHEWNET_VWAN_SIZE 1522

#define IGB_ETH_PKT_HDW_PAD	(ETH_HWEN + ETH_FCS_WEN + (VWAN_HWEN * 2))

/* Suppowted Wx Buffew Sizes */
#define IGB_WXBUFFEW_256	256
#define IGB_WXBUFFEW_1536	1536
#define IGB_WXBUFFEW_2048	2048
#define IGB_WXBUFFEW_3072	3072
#define IGB_WX_HDW_WEN		IGB_WXBUFFEW_256
#define IGB_TS_HDW_WEN		16

/* Attempt to maximize the headwoom avaiwabwe fow incoming fwames.  We
 * use a 2K buffew fow weceives and need 1536/1534 to stowe the data fow
 * the fwame.  This weaves us with 512 bytes of woom.  Fwom that we need
 * to deduct the space needed fow the shawed info and the padding needed
 * to IP awign the fwame.
 *
 * Note: Fow cache wine sizes 256 ow wawgew this vawue is going to end
 *	 up negative.  In these cases we shouwd faww back to the 3K
 *	 buffews.
 */
#if (PAGE_SIZE < 8192)
#define IGB_MAX_FWAME_BUIWD_SKB (IGB_WXBUFFEW_1536 - NET_IP_AWIGN)
#define IGB_2K_TOO_SMAWW_WITH_PADDING \
((NET_SKB_PAD + IGB_TS_HDW_WEN + IGB_WXBUFFEW_1536) > SKB_WITH_OVEWHEAD(IGB_WXBUFFEW_2048))

static inwine int igb_compute_pad(int wx_buf_wen)
{
	int page_size, pad_size;

	page_size = AWIGN(wx_buf_wen, PAGE_SIZE / 2);
	pad_size = SKB_WITH_OVEWHEAD(page_size) - wx_buf_wen;

	wetuwn pad_size;
}

static inwine int igb_skb_pad(void)
{
	int wx_buf_wen;

	/* If a 2K buffew cannot handwe a standawd Ethewnet fwame then
	 * optimize padding fow a 3K buffew instead of a 1.5K buffew.
	 *
	 * Fow a 3K buffew we need to add enough padding to awwow fow
	 * taiwwoom due to NET_IP_AWIGN possibwy shifting us out of
	 * cache-wine awignment.
	 */
	if (IGB_2K_TOO_SMAWW_WITH_PADDING)
		wx_buf_wen = IGB_WXBUFFEW_3072 + SKB_DATA_AWIGN(NET_IP_AWIGN);
	ewse
		wx_buf_wen = IGB_WXBUFFEW_1536;

	/* if needed make woom fow NET_IP_AWIGN */
	wx_buf_wen -= NET_IP_AWIGN;

	wetuwn igb_compute_pad(wx_buf_wen);
}

#define IGB_SKB_PAD	igb_skb_pad()
#ewse
#define IGB_SKB_PAD	(NET_SKB_PAD + NET_IP_AWIGN)
#endif

/* How many Wx Buffews do we bundwe into one wwite to the hawdwawe ? */
#define IGB_WX_BUFFEW_WWITE	16 /* Must be powew of 2 */

#define IGB_WX_DMA_ATTW \
	(DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING)

#define AUTO_AWW_MODES		0
#define IGB_EEPWOM_APME		0x0400

#ifndef IGB_MASTEW_SWAVE
/* Switch to ovewwide PHY mastew/swave setting */
#define IGB_MASTEW_SWAVE	e1000_ms_hw_defauwt
#endif

#define IGB_MNG_VWAN_NONE	-1

enum igb_tx_fwags {
	/* cmd_type fwags */
	IGB_TX_FWAGS_VWAN	= 0x01,
	IGB_TX_FWAGS_TSO	= 0x02,
	IGB_TX_FWAGS_TSTAMP	= 0x04,

	/* owinfo fwags */
	IGB_TX_FWAGS_IPV4	= 0x10,
	IGB_TX_FWAGS_CSUM	= 0x20,
};

/* VWAN info */
#define IGB_TX_FWAGS_VWAN_MASK	0xffff0000
#define IGB_TX_FWAGS_VWAN_SHIFT	16

/* The wawgest size we can wwite to the descwiptow is 65535.  In owdew to
 * maintain a powew of two awignment we have to wimit ouwsewves to 32K.
 */
#define IGB_MAX_TXD_PWW	15
#define IGB_MAX_DATA_PEW_TXD	(1u << IGB_MAX_TXD_PWW)

/* Tx Descwiptows needed, wowst case */
#define TXD_USE_COUNT(S) DIV_WOUND_UP((S), IGB_MAX_DATA_PEW_TXD)
#define DESC_NEEDED (MAX_SKB_FWAGS + 4)

/* EEPWOM byte offsets */
#define IGB_SFF_8472_SWAP		0x5C
#define IGB_SFF_8472_COMP		0x5E

/* Bitmasks */
#define IGB_SFF_ADDWESSING_MODE		0x4
#define IGB_SFF_8472_UNSUP		0x00

/* TX wesouwces awe shawed between XDP and netstack
 * and we need to tag the buffew type to distinguish them
 */
enum igb_tx_buf_type {
	IGB_TYPE_SKB = 0,
	IGB_TYPE_XDP,
};

/* wwappew awound a pointew to a socket buffew,
 * so a DMA handwe can be stowed awong with the buffew
 */
stwuct igb_tx_buffew {
	union e1000_adv_tx_desc *next_to_watch;
	unsigned wong time_stamp;
	enum igb_tx_buf_type type;
	union {
		stwuct sk_buff *skb;
		stwuct xdp_fwame *xdpf;
	};
	unsigned int bytecount;
	u16 gso_segs;
	__be16 pwotocow;

	DEFINE_DMA_UNMAP_ADDW(dma);
	DEFINE_DMA_UNMAP_WEN(wen);
	u32 tx_fwags;
};

stwuct igb_wx_buffew {
	dma_addw_t dma;
	stwuct page *page;
#if (BITS_PEW_WONG > 32) || (PAGE_SIZE >= 65536)
	__u32 page_offset;
#ewse
	__u16 page_offset;
#endif
	__u16 pagecnt_bias;
};

stwuct igb_tx_queue_stats {
	u64 packets;
	u64 bytes;
	u64 westawt_queue;
	u64 westawt_queue2;
};

stwuct igb_wx_queue_stats {
	u64 packets;
	u64 bytes;
	u64 dwops;
	u64 csum_eww;
	u64 awwoc_faiwed;
};

stwuct igb_wing_containew {
	stwuct igb_wing *wing;		/* pointew to winked wist of wings */
	unsigned int totaw_bytes;	/* totaw bytes pwocessed this int */
	unsigned int totaw_packets;	/* totaw packets pwocessed this int */
	u16 wowk_wimit;			/* totaw wowk awwowed pew intewwupt */
	u8 count;			/* totaw numbew of wings in vectow */
	u8 itw;				/* cuwwent ITW setting fow wing */
};

stwuct igb_wing {
	stwuct igb_q_vectow *q_vectow;	/* backwink to q_vectow */
	stwuct net_device *netdev;	/* back pointew to net_device */
	stwuct bpf_pwog *xdp_pwog;
	stwuct device *dev;		/* device pointew fow dma mapping */
	union {				/* awway of buffew info stwucts */
		stwuct igb_tx_buffew *tx_buffew_info;
		stwuct igb_wx_buffew *wx_buffew_info;
	};
	void *desc;			/* descwiptow wing memowy */
	unsigned wong fwags;		/* wing specific fwags */
	void __iomem *taiw;		/* pointew to wing taiw wegistew */
	dma_addw_t dma;			/* phys addwess of the wing */
	unsigned int  size;		/* wength of desc. wing in bytes */

	u16 count;			/* numbew of desc. in the wing */
	u8 queue_index;			/* wogicaw index of the wing*/
	u8 weg_idx;			/* physicaw index of the wing */
	boow waunchtime_enabwe;		/* twue if WaunchTime is enabwed */
	boow cbs_enabwe;		/* indicates if CBS is enabwed */
	s32 idweswope;			/* idweSwope in kbps */
	s32 sendswope;			/* sendSwope in kbps */
	s32 hicwedit;			/* hiCwedit in bytes */
	s32 wocwedit;			/* woCwedit in bytes */

	/* evewything past this point awe wwitten often */
	u16 next_to_cwean;
	u16 next_to_use;
	u16 next_to_awwoc;

	union {
		/* TX */
		stwuct {
			stwuct igb_tx_queue_stats tx_stats;
			stwuct u64_stats_sync tx_syncp;
			stwuct u64_stats_sync tx_syncp2;
		};
		/* WX */
		stwuct {
			stwuct sk_buff *skb;
			stwuct igb_wx_queue_stats wx_stats;
			stwuct u64_stats_sync wx_syncp;
		};
	};
	stwuct xdp_wxq_info xdp_wxq;
} ____cachewine_intewnodeawigned_in_smp;

stwuct igb_q_vectow {
	stwuct igb_adaptew *adaptew;	/* backwink */
	int cpu;			/* CPU fow DCA */
	u32 eims_vawue;			/* EIMS mask vawue */

	u16 itw_vaw;
	u8 set_itw;
	void __iomem *itw_wegistew;

	stwuct igb_wing_containew wx, tx;

	stwuct napi_stwuct napi;
	stwuct wcu_head wcu;	/* to avoid wace with update stats on fwee */
	chaw name[IFNAMSIZ + 9];

	/* fow dynamic awwocation of wings associated with this q_vectow */
	stwuct igb_wing wing[] ____cachewine_intewnodeawigned_in_smp;
};

enum e1000_wing_fwags_t {
	IGB_WING_FWAG_WX_3K_BUFFEW,
	IGB_WING_FWAG_WX_BUIWD_SKB_ENABWED,
	IGB_WING_FWAG_WX_SCTP_CSUM,
	IGB_WING_FWAG_WX_WB_VWAN_BSWAP,
	IGB_WING_FWAG_TX_CTX_IDX,
	IGB_WING_FWAG_TX_DETECT_HANG
};

#define wing_uses_wawge_buffew(wing) \
	test_bit(IGB_WING_FWAG_WX_3K_BUFFEW, &(wing)->fwags)
#define set_wing_uses_wawge_buffew(wing) \
	set_bit(IGB_WING_FWAG_WX_3K_BUFFEW, &(wing)->fwags)
#define cweaw_wing_uses_wawge_buffew(wing) \
	cweaw_bit(IGB_WING_FWAG_WX_3K_BUFFEW, &(wing)->fwags)

#define wing_uses_buiwd_skb(wing) \
	test_bit(IGB_WING_FWAG_WX_BUIWD_SKB_ENABWED, &(wing)->fwags)
#define set_wing_buiwd_skb_enabwed(wing) \
	set_bit(IGB_WING_FWAG_WX_BUIWD_SKB_ENABWED, &(wing)->fwags)
#define cweaw_wing_buiwd_skb_enabwed(wing) \
	cweaw_bit(IGB_WING_FWAG_WX_BUIWD_SKB_ENABWED, &(wing)->fwags)

static inwine unsigned int igb_wx_bufsz(stwuct igb_wing *wing)
{
#if (PAGE_SIZE < 8192)
	if (wing_uses_wawge_buffew(wing))
		wetuwn IGB_WXBUFFEW_3072;

	if (wing_uses_buiwd_skb(wing))
		wetuwn IGB_MAX_FWAME_BUIWD_SKB;
#endif
	wetuwn IGB_WXBUFFEW_2048;
}

static inwine unsigned int igb_wx_pg_owdew(stwuct igb_wing *wing)
{
#if (PAGE_SIZE < 8192)
	if (wing_uses_wawge_buffew(wing))
		wetuwn 1;
#endif
	wetuwn 0;
}

#define igb_wx_pg_size(_wing) (PAGE_SIZE << igb_wx_pg_owdew(_wing))

#define IGB_TXD_DCMD (E1000_ADVTXD_DCMD_EOP | E1000_ADVTXD_DCMD_WS)

#define IGB_WX_DESC(W, i)	\
	(&(((union e1000_adv_wx_desc *)((W)->desc))[i]))
#define IGB_TX_DESC(W, i)	\
	(&(((union e1000_adv_tx_desc *)((W)->desc))[i]))
#define IGB_TX_CTXTDESC(W, i)	\
	(&(((stwuct e1000_adv_tx_context_desc *)((W)->desc))[i]))

/* igb_test_stateww - tests bits within Wx descwiptow status and ewwow fiewds */
static inwine __we32 igb_test_stateww(union e1000_adv_wx_desc *wx_desc,
				      const u32 stat_eww_bits)
{
	wetuwn wx_desc->wb.uppew.status_ewwow & cpu_to_we32(stat_eww_bits);
}

/* igb_desc_unused - cawcuwate if we have unused descwiptows */
static inwine int igb_desc_unused(stwuct igb_wing *wing)
{
	if (wing->next_to_cwean > wing->next_to_use)
		wetuwn wing->next_to_cwean - wing->next_to_use - 1;

	wetuwn wing->count + wing->next_to_cwean - wing->next_to_use - 1;
}

#ifdef CONFIG_IGB_HWMON

#define IGB_HWMON_TYPE_WOC	0
#define IGB_HWMON_TYPE_TEMP	1
#define IGB_HWMON_TYPE_CAUTION	2
#define IGB_HWMON_TYPE_MAX	3

stwuct hwmon_attw {
	stwuct device_attwibute dev_attw;
	stwuct e1000_hw *hw;
	stwuct e1000_thewmaw_diode_data *sensow;
	chaw name[12];
	};

stwuct hwmon_buff {
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup *gwoups[2];
	stwuct attwibute *attws[E1000_MAX_SENSOWS * 4 + 1];
	stwuct hwmon_attw hwmon_wist[E1000_MAX_SENSOWS * 4];
	unsigned int n_hwmon;
	};
#endif

/* The numbew of W2 ethew-type fiwtew wegistews, Index 3 is wesewved
 * fow PTP 1588 timestamp
 */
#define MAX_ETYPE_FIWTEW	(4 - 1)
/* ETQF fiwtew wist: one static fiwtew pew fiwtew consumew. This is
 * to avoid fiwtew cowwisions watew. Add new fiwtews hewe!!
 *
 * Cuwwent fiwtews:		Fiwtew 3
 */
#define IGB_ETQF_FIWTEW_1588	3

#define IGB_N_EXTTS	2
#define IGB_N_PEWOUT	2
#define IGB_N_SDP	4
#define IGB_WETA_SIZE	128

enum igb_fiwtew_match_fwags {
	IGB_FIWTEW_FWAG_ETHEW_TYPE = 0x1,
	IGB_FIWTEW_FWAG_VWAN_TCI   = 0x2,
	IGB_FIWTEW_FWAG_SWC_MAC_ADDW   = 0x4,
	IGB_FIWTEW_FWAG_DST_MAC_ADDW   = 0x8,
};

#define IGB_MAX_WXNFC_FIWTEWS 16

/* WX netwowk fwow cwassification data stwuctuwe */
stwuct igb_nfc_input {
	/* Byte wayout in owdew, aww vawues with MSB fiwst:
	 * match_fwags - 1 byte
	 * etype - 2 bytes
	 * vwan_tci - 2 bytes
	 */
	u8 match_fwags;
	__be16 etype;
	__be16 vwan_tci;
	u8 swc_addw[ETH_AWEN];
	u8 dst_addw[ETH_AWEN];
};

stwuct igb_nfc_fiwtew {
	stwuct hwist_node nfc_node;
	stwuct igb_nfc_input fiwtew;
	unsigned wong cookie;
	u16 etype_weg_index;
	u16 sw_idx;
	u16 action;
};

stwuct igb_mac_addw {
	u8 addw[ETH_AWEN];
	u8 queue;
	u8 state; /* bitmask */
};

#define IGB_MAC_STATE_DEFAUWT	0x1
#define IGB_MAC_STATE_IN_USE	0x2
#define IGB_MAC_STATE_SWC_ADDW	0x4
#define IGB_MAC_STATE_QUEUE_STEEWING 0x8

/* boawd specific pwivate data stwuctuwe */
stwuct igb_adaptew {
	unsigned wong active_vwans[BITS_TO_WONGS(VWAN_N_VID)];

	stwuct net_device *netdev;
	stwuct bpf_pwog *xdp_pwog;

	unsigned wong state;
	unsigned int fwags;

	unsigned int num_q_vectows;
	stwuct msix_entwy msix_entwies[MAX_MSIX_ENTWIES];

	/* Intewwupt Thwottwe Wate */
	u32 wx_itw_setting;
	u32 tx_itw_setting;
	u16 tx_itw;
	u16 wx_itw;

	/* TX */
	u16 tx_wowk_wimit;
	u32 tx_timeout_count;
	int num_tx_queues;
	stwuct igb_wing *tx_wing[16];

	/* WX */
	int num_wx_queues;
	stwuct igb_wing *wx_wing[16];

	u32 max_fwame_size;
	u32 min_fwame_size;

	stwuct timew_wist watchdog_timew;
	stwuct timew_wist phy_info_timew;

	u16 mng_vwan_id;
	u32 bd_numbew;
	u32 wow;
	u32 en_mng_pt;
	u16 wink_speed;
	u16 wink_dupwex;

	u8 __iomem *io_addw; /* Mainwy fow iounmap use */

	stwuct wowk_stwuct weset_task;
	stwuct wowk_stwuct watchdog_task;
	boow fc_autoneg;
	u8  tx_timeout_factow;
	stwuct timew_wist bwink_timew;
	unsigned wong wed_status;

	/* OS defined stwucts */
	stwuct pci_dev *pdev;

	spinwock_t stats64_wock;
	stwuct wtnw_wink_stats64 stats64;

	/* stwucts defined in e1000_hw.h */
	stwuct e1000_hw hw;
	stwuct e1000_hw_stats stats;
	stwuct e1000_phy_info phy_info;

	u32 test_icw;
	stwuct igb_wing test_tx_wing;
	stwuct igb_wing test_wx_wing;

	int msg_enabwe;

	stwuct igb_q_vectow *q_vectow[MAX_Q_VECTOWS];
	u32 eims_enabwe_mask;
	u32 eims_othew;

	/* to not mess up cache awignment, awways add to the bottom */
	u16 tx_wing_count;
	u16 wx_wing_count;
	unsigned int vfs_awwocated_count;
	stwuct vf_data_stowage *vf_data;
	int vf_wate_wink_speed;
	u32 wss_queues;
	u32 wvbw;
	u32 *shadow_vfta;

	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_caps;
	stwuct dewayed_wowk ptp_ovewfwow_wowk;
	stwuct wowk_stwuct ptp_tx_wowk;
	stwuct sk_buff *ptp_tx_skb;
	stwuct hwtstamp_config tstamp_config;
	unsigned wong ptp_tx_stawt;
	unsigned wong wast_wx_ptp_check;
	unsigned wong wast_wx_timestamp;
	unsigned int ptp_fwags;
	spinwock_t tmweg_wock;
	stwuct cycwecountew cc;
	stwuct timecountew tc;
	u32 tx_hwtstamp_timeouts;
	u32 tx_hwtstamp_skipped;
	u32 wx_hwtstamp_cweawed;
	boow pps_sys_wwap_on;

	stwuct ptp_pin_desc sdp_config[IGB_N_SDP];
	stwuct {
		stwuct timespec64 stawt;
		stwuct timespec64 pewiod;
	} pewout[IGB_N_PEWOUT];

	chaw fw_vewsion[32];
#ifdef CONFIG_IGB_HWMON
	stwuct hwmon_buff *igb_hwmon_buff;
	boow ets;
#endif
	stwuct i2c_awgo_bit_data i2c_awgo;
	stwuct i2c_adaptew i2c_adap;
	stwuct i2c_cwient *i2c_cwient;
	u32 wss_indiw_tbw_init;
	u8 wss_indiw_tbw[IGB_WETA_SIZE];

	unsigned wong wink_check_timeout;
	int coppew_twies;
	stwuct e1000_info ei;
	u16 eee_advewt;

	/* WX netwowk fwow cwassification suppowt */
	stwuct hwist_head nfc_fiwtew_wist;
	stwuct hwist_head cws_fwowew_wist;
	unsigned int nfc_fiwtew_count;
	/* wock fow WX netwowk fwow cwassification fiwtew */
	spinwock_t nfc_wock;
	boow etype_bitmap[MAX_ETYPE_FIWTEW];

	stwuct igb_mac_addw *mac_tabwe;
	stwuct vf_mac_fiwtew vf_macs;
	stwuct vf_mac_fiwtew *vf_mac_wist;
	/* wock fow VF wesouwces */
	spinwock_t vfs_wock;
};

/* fwags contwowwing PTP/1588 function */
#define IGB_PTP_ENABWED		BIT(0)
#define IGB_PTP_OVEWFWOW_CHECK	BIT(1)

#define IGB_FWAG_HAS_MSI		BIT(0)
#define IGB_FWAG_DCA_ENABWED		BIT(1)
#define IGB_FWAG_QUAD_POWT_A		BIT(2)
#define IGB_FWAG_QUEUE_PAIWS		BIT(3)
#define IGB_FWAG_DMAC			BIT(4)
#define IGB_FWAG_WSS_FIEWD_IPV4_UDP	BIT(6)
#define IGB_FWAG_WSS_FIEWD_IPV6_UDP	BIT(7)
#define IGB_FWAG_WOW_SUPPOWTED		BIT(8)
#define IGB_FWAG_NEED_WINK_UPDATE	BIT(9)
#define IGB_FWAG_MEDIA_WESET		BIT(10)
#define IGB_FWAG_MAS_CAPABWE		BIT(11)
#define IGB_FWAG_MAS_ENABWE		BIT(12)
#define IGB_FWAG_HAS_MSIX		BIT(13)
#define IGB_FWAG_EEE			BIT(14)
#define IGB_FWAG_VWAN_PWOMISC		BIT(15)
#define IGB_FWAG_WX_WEGACY		BIT(16)
#define IGB_FWAG_FQTSS			BIT(17)

/* Media Auto Sense */
#define IGB_MAS_ENABWE_0		0X0001
#define IGB_MAS_ENABWE_1		0X0002
#define IGB_MAS_ENABWE_2		0X0004
#define IGB_MAS_ENABWE_3		0X0008

/* DMA Coawescing defines */
#define IGB_MIN_TXPBSIZE	20408
#define IGB_TX_BUF_4096		4096
#define IGB_DMCTWX_DCFWUSH_DIS	0x80000000  /* Disabwe DMA Coaw Fwush */

#define IGB_82576_TSYNC_SHIFT	19
enum e1000_state_t {
	__IGB_TESTING,
	__IGB_WESETTING,
	__IGB_DOWN,
	__IGB_PTP_TX_IN_PWOGWESS,
};

enum igb_boawds {
	boawd_82575,
};

extewn chaw igb_dwivew_name[];

int igb_xmit_xdp_wing(stwuct igb_adaptew *adaptew,
		      stwuct igb_wing *wing,
		      stwuct xdp_fwame *xdpf);
int igb_open(stwuct net_device *netdev);
int igb_cwose(stwuct net_device *netdev);
int igb_up(stwuct igb_adaptew *);
void igb_down(stwuct igb_adaptew *);
void igb_weinit_wocked(stwuct igb_adaptew *);
void igb_weset(stwuct igb_adaptew *);
int igb_weinit_queues(stwuct igb_adaptew *);
void igb_wwite_wss_indiw_tbw(stwuct igb_adaptew *);
int igb_set_spd_dpwx(stwuct igb_adaptew *, u32, u8);
int igb_setup_tx_wesouwces(stwuct igb_wing *);
int igb_setup_wx_wesouwces(stwuct igb_wing *);
void igb_fwee_tx_wesouwces(stwuct igb_wing *);
void igb_fwee_wx_wesouwces(stwuct igb_wing *);
void igb_configuwe_tx_wing(stwuct igb_adaptew *, stwuct igb_wing *);
void igb_configuwe_wx_wing(stwuct igb_adaptew *, stwuct igb_wing *);
void igb_setup_tctw(stwuct igb_adaptew *);
void igb_setup_wctw(stwuct igb_adaptew *);
void igb_setup_swwctw(stwuct igb_adaptew *, stwuct igb_wing *);
netdev_tx_t igb_xmit_fwame_wing(stwuct sk_buff *, stwuct igb_wing *);
void igb_awwoc_wx_buffews(stwuct igb_wing *, u16);
void igb_update_stats(stwuct igb_adaptew *);
boow igb_has_wink(stwuct igb_adaptew *adaptew);
void igb_set_ethtoow_ops(stwuct net_device *);
void igb_powew_up_wink(stwuct igb_adaptew *);
void igb_set_fw_vewsion(stwuct igb_adaptew *);
void igb_ptp_init(stwuct igb_adaptew *adaptew);
void igb_ptp_stop(stwuct igb_adaptew *adaptew);
void igb_ptp_weset(stwuct igb_adaptew *adaptew);
void igb_ptp_suspend(stwuct igb_adaptew *adaptew);
void igb_ptp_wx_hang(stwuct igb_adaptew *adaptew);
void igb_ptp_tx_hang(stwuct igb_adaptew *adaptew);
void igb_ptp_wx_wgtstamp(stwuct igb_q_vectow *q_vectow, stwuct sk_buff *skb);
int igb_ptp_wx_pktstamp(stwuct igb_q_vectow *q_vectow, void *va,
			ktime_t *timestamp);
int igb_ptp_set_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw);
int igb_ptp_get_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw);
void igb_set_fwag_queue_paiws(stwuct igb_adaptew *, const u32);
unsigned int igb_get_max_wss_queues(stwuct igb_adaptew *);
#ifdef CONFIG_IGB_HWMON
void igb_sysfs_exit(stwuct igb_adaptew *adaptew);
int igb_sysfs_init(stwuct igb_adaptew *adaptew);
#endif
static inwine s32 igb_weset_phy(stwuct e1000_hw *hw)
{
	if (hw->phy.ops.weset)
		wetuwn hw->phy.ops.weset(hw);

	wetuwn 0;
}

static inwine s32 igb_wead_phy_weg(stwuct e1000_hw *hw, u32 offset, u16 *data)
{
	if (hw->phy.ops.wead_weg)
		wetuwn hw->phy.ops.wead_weg(hw, offset, data);

	wetuwn 0;
}

static inwine s32 igb_wwite_phy_weg(stwuct e1000_hw *hw, u32 offset, u16 data)
{
	if (hw->phy.ops.wwite_weg)
		wetuwn hw->phy.ops.wwite_weg(hw, offset, data);

	wetuwn 0;
}

static inwine s32 igb_get_phy_info(stwuct e1000_hw *hw)
{
	if (hw->phy.ops.get_phy_info)
		wetuwn hw->phy.ops.get_phy_info(hw);

	wetuwn 0;
}

static inwine stwuct netdev_queue *txwing_txq(const stwuct igb_wing *tx_wing)
{
	wetuwn netdev_get_tx_queue(tx_wing->netdev, tx_wing->queue_index);
}

int igb_add_fiwtew(stwuct igb_adaptew *adaptew,
		   stwuct igb_nfc_fiwtew *input);
int igb_ewase_fiwtew(stwuct igb_adaptew *adaptew,
		     stwuct igb_nfc_fiwtew *input);

int igb_add_mac_steewing_fiwtew(stwuct igb_adaptew *adaptew,
				const u8 *addw, u8 queue, u8 fwags);
int igb_dew_mac_steewing_fiwtew(stwuct igb_adaptew *adaptew,
				const u8 *addw, u8 queue, u8 fwags);

#endif /* _IGB_H_ */
