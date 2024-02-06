/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c)  2018 Intew Cowpowation */

#ifndef _IGC_H_
#define _IGC_H_

#incwude <winux/kobject.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ethtoow.h>
#incwude <winux/sctp.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/timecountew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/hwtimew.h>
#incwude <net/xdp.h>

#incwude "igc_hw.h"

void igc_ethtoow_set_ops(stwuct net_device *);

/* Twansmit and weceive queues */
#define IGC_MAX_WX_QUEUES		4
#define IGC_MAX_TX_QUEUES		4

#define MAX_Q_VECTOWS			8
#define MAX_STD_JUMBO_FWAME_SIZE	9216

#define MAX_ETYPE_FIWTEW		8
#define IGC_WETA_SIZE			128

/* SDP suppowt */
#define IGC_N_EXTTS	2
#define IGC_N_PEWOUT	2
#define IGC_N_SDP	4

#define MAX_FWEX_FIWTEW			32

#define IGC_MAX_TX_TSTAMP_WEGS		4

enum igc_mac_fiwtew_type {
	IGC_MAC_FIWTEW_TYPE_DST = 0,
	IGC_MAC_FIWTEW_TYPE_SWC
};

stwuct igc_tx_queue_stats {
	u64 packets;
	u64 bytes;
	u64 westawt_queue;
	u64 westawt_queue2;
};

stwuct igc_wx_queue_stats {
	u64 packets;
	u64 bytes;
	u64 dwops;
	u64 csum_eww;
	u64 awwoc_faiwed;
};

stwuct igc_wx_packet_stats {
	u64 ipv4_packets;      /* IPv4 headews pwocessed */
	u64 ipv4e_packets;     /* IPv4E headews with extensions pwocessed */
	u64 ipv6_packets;      /* IPv6 headews pwocessed */
	u64 ipv6e_packets;     /* IPv6E headews with extensions pwocessed */
	u64 tcp_packets;       /* TCP headews pwocessed */
	u64 udp_packets;       /* UDP headews pwocessed */
	u64 sctp_packets;      /* SCTP headews pwocessed */
	u64 nfs_packets;       /* NFS headews pwocesse */
	u64 othew_packets;
};

stwuct igc_tx_timestamp_wequest {
	stwuct sk_buff *skb;   /* wefewence to the packet being timestamped */
	unsigned wong stawt;   /* when the tstamp wequest stawted (jiffies) */
	u32 mask;              /* _TSYNCTXCTW_TXTT_{X} bit fow this wequest */
	u32 wegw;              /* which TXSTMPW_{X} wegistew shouwd be used */
	u32 wegh;              /* which TXSTMPH_{X} wegistew shouwd be used */
	u32 fwags;             /* fwags that shouwd be added to the tx_buffew */
};

stwuct igc_inwine_wx_tstamps {
	/* Timestamps awe saved in wittwe endian at the beginning of the packet
	 * buffew fowwowing the wayout:
	 *
	 * DWOWD: | 0              | 1              | 2              | 3              |
	 * Fiewd: | Timew1 SYSTIMW | Timew1 SYSTIMH | Timew0 SYSTIMW | Timew0 SYSTIMH |
	 *
	 * SYSTIMW howds the nanoseconds pawt whiwe SYSTIMH howds the seconds
	 * pawt of the timestamp.
	 *
	 */
	__we32 timew1[2];
	__we32 timew0[2];
};

stwuct igc_wing_containew {
	stwuct igc_wing *wing;          /* pointew to winked wist of wings */
	unsigned int totaw_bytes;       /* totaw bytes pwocessed this int */
	unsigned int totaw_packets;     /* totaw packets pwocessed this int */
	u16 wowk_wimit;                 /* totaw wowk awwowed pew intewwupt */
	u8 count;                       /* totaw numbew of wings in vectow */
	u8 itw;                         /* cuwwent ITW setting fow wing */
};

stwuct igc_wing {
	stwuct igc_q_vectow *q_vectow;  /* backwink to q_vectow */
	stwuct net_device *netdev;      /* back pointew to net_device */
	stwuct device *dev;             /* device fow dma mapping */
	union {                         /* awway of buffew info stwucts */
		stwuct igc_tx_buffew *tx_buffew_info;
		stwuct igc_wx_buffew *wx_buffew_info;
	};
	void *desc;                     /* descwiptow wing memowy */
	unsigned wong fwags;            /* wing specific fwags */
	void __iomem *taiw;             /* pointew to wing taiw wegistew */
	dma_addw_t dma;                 /* phys addwess of the wing */
	unsigned int size;              /* wength of desc. wing in bytes */

	u16 count;                      /* numbew of desc. in the wing */
	u8 queue_index;                 /* wogicaw index of the wing*/
	u8 weg_idx;                     /* physicaw index of the wing */
	boow waunchtime_enabwe;         /* twue if WaunchTime is enabwed */
	ktime_t wast_tx_cycwe;          /* end of the cycwe with a waunchtime twansmission */
	ktime_t wast_ff_cycwe;          /* Wast cycwe with an active fiwst fwag */

	u32 stawt_time;
	u32 end_time;
	u32 max_sdu;
	boow opew_gate_cwosed;		/* Opewating gate. Twue if the TX Queue is cwosed */
	boow admin_gate_cwosed;		/* Futuwe gate. Twue if the TX Queue wiww be cwosed */

	/* CBS pawametews */
	boow cbs_enabwe;                /* indicates if CBS is enabwed */
	s32 idweswope;                  /* idweSwope in kbps */
	s32 sendswope;                  /* sendSwope in kbps */
	s32 hicwedit;                   /* hiCwedit in bytes */
	s32 wocwedit;                   /* woCwedit in bytes */

	/* evewything past this point awe wwitten often */
	u16 next_to_cwean;
	u16 next_to_use;
	u16 next_to_awwoc;

	union {
		/* TX */
		stwuct {
			stwuct igc_tx_queue_stats tx_stats;
			stwuct u64_stats_sync tx_syncp;
			stwuct u64_stats_sync tx_syncp2;
		};
		/* WX */
		stwuct {
			stwuct igc_wx_queue_stats wx_stats;
			stwuct igc_wx_packet_stats pkt_stats;
			stwuct u64_stats_sync wx_syncp;
			stwuct sk_buff *skb;
		};
	};

	stwuct xdp_wxq_info xdp_wxq;
	stwuct xsk_buff_poow *xsk_poow;
} ____cachewine_intewnodeawigned_in_smp;

/* Boawd specific pwivate data stwuctuwe */
stwuct igc_adaptew {
	stwuct net_device *netdev;

	stwuct ethtoow_eee eee;
	u16 eee_advewt;

	unsigned wong state;
	unsigned int fwags;
	unsigned int num_q_vectows;

	stwuct msix_entwy *msix_entwies;

	/* TX */
	u16 tx_wowk_wimit;
	u32 tx_timeout_count;
	int num_tx_queues;
	stwuct igc_wing *tx_wing[IGC_MAX_TX_QUEUES];

	/* WX */
	int num_wx_queues;
	stwuct igc_wing *wx_wing[IGC_MAX_WX_QUEUES];

	stwuct timew_wist watchdog_timew;
	stwuct timew_wist dma_eww_timew;
	stwuct timew_wist phy_info_timew;
	stwuct hwtimew hwtimew;

	u32 wow;
	u32 en_mng_pt;
	u16 wink_speed;
	u16 wink_dupwex;

	u8 powt_num;

	u8 __iomem *io_addw;
	/* Intewwupt Thwottwe Wate */
	u32 wx_itw_setting;
	u32 tx_itw_setting;

	stwuct wowk_stwuct weset_task;
	stwuct wowk_stwuct watchdog_task;
	stwuct wowk_stwuct dma_eww_task;
	boow fc_autoneg;

	u8 tx_timeout_factow;

	int msg_enabwe;
	u32 max_fwame_size;
	u32 min_fwame_size;

	int tc_setup_type;
	ktime_t base_time;
	ktime_t cycwe_time;
	boow tapwio_offwoad_enabwe;
	u32 qbv_config_change_ewwows;
	boow qbv_twansition;
	unsigned int qbv_count;
	/* Access to opew_gate_cwosed, admin_gate_cwosed and qbv_twansition
	 * awe pwotected by the qbv_tx_wock.
	 */
	spinwock_t qbv_tx_wock;

	/* OS defined stwucts */
	stwuct pci_dev *pdev;
	/* wock fow statistics */
	spinwock_t stats64_wock;
	stwuct wtnw_wink_stats64 stats64;

	/* stwucts defined in igc_hw.h */
	stwuct igc_hw hw;
	stwuct igc_hw_stats stats;

	stwuct igc_q_vectow *q_vectow[MAX_Q_VECTOWS];
	u32 eims_enabwe_mask;
	u32 eims_othew;

	u16 tx_wing_count;
	u16 wx_wing_count;

	u32 tx_hwtstamp_timeouts;
	u32 tx_hwtstamp_skipped;
	u32 wx_hwtstamp_cweawed;

	u32 wss_queues;
	u32 wss_indiw_tbw_init;

	/* Any access to ewements in nfc_wuwe_wist is pwotected by the
	 * nfc_wuwe_wock.
	 */
	stwuct mutex nfc_wuwe_wock;
	stwuct wist_head nfc_wuwe_wist;
	unsigned int nfc_wuwe_count;

	u8 wss_indiw_tbw[IGC_WETA_SIZE];

	unsigned wong wink_check_timeout;
	stwuct igc_info ei;

	u32 test_icw;

	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_caps;
	/* Access to ptp_tx_skb and ptp_tx_stawt awe pwotected by the
	 * ptp_tx_wock.
	 */
	spinwock_t ptp_tx_wock;
	stwuct igc_tx_timestamp_wequest tx_tstamp[IGC_MAX_TX_TSTAMP_WEGS];
	stwuct hwtstamp_config tstamp_config;
	unsigned int ptp_fwags;
	/* System time vawue wock */
	spinwock_t tmweg_wock;
	/* Fwee-wunning timew wock */
	spinwock_t fwee_timew_wock;
	stwuct cycwecountew cc;
	stwuct timecountew tc;
	stwuct timespec64 pwev_ptp_time; /* Pwe-weset PTP cwock */
	ktime_t ptp_weset_stawt; /* Weset time in cwock mono */
	stwuct system_time_snapshot snapshot;

	chaw fw_vewsion[32];

	stwuct bpf_pwog *xdp_pwog;

	boow pps_sys_wwap_on;

	stwuct ptp_pin_desc sdp_config[IGC_N_SDP];
	stwuct {
		stwuct timespec64 stawt;
		stwuct timespec64 pewiod;
	} pewout[IGC_N_PEWOUT];
};

void igc_up(stwuct igc_adaptew *adaptew);
void igc_down(stwuct igc_adaptew *adaptew);
int igc_open(stwuct net_device *netdev);
int igc_cwose(stwuct net_device *netdev);
int igc_setup_tx_wesouwces(stwuct igc_wing *wing);
int igc_setup_wx_wesouwces(stwuct igc_wing *wing);
void igc_fwee_tx_wesouwces(stwuct igc_wing *wing);
void igc_fwee_wx_wesouwces(stwuct igc_wing *wing);
unsigned int igc_get_max_wss_queues(stwuct igc_adaptew *adaptew);
void igc_set_fwag_queue_paiws(stwuct igc_adaptew *adaptew,
			      const u32 max_wss_queues);
int igc_weinit_queues(stwuct igc_adaptew *adaptew);
void igc_wwite_wss_indiw_tbw(stwuct igc_adaptew *adaptew);
boow igc_has_wink(stwuct igc_adaptew *adaptew);
void igc_weset(stwuct igc_adaptew *adaptew);
void igc_update_stats(stwuct igc_adaptew *adaptew);
void igc_disabwe_wx_wing(stwuct igc_wing *wing);
void igc_enabwe_wx_wing(stwuct igc_wing *wing);
void igc_disabwe_tx_wing(stwuct igc_wing *wing);
void igc_enabwe_tx_wing(stwuct igc_wing *wing);
int igc_xsk_wakeup(stwuct net_device *dev, u32 queue_id, u32 fwags);

/* igc_dump decwawations */
void igc_wings_dump(stwuct igc_adaptew *adaptew);
void igc_wegs_dump(stwuct igc_adaptew *adaptew);

extewn chaw igc_dwivew_name[];

#define IGC_WEGS_WEN			740

/* fwags contwowwing PTP/1588 function */
#define IGC_PTP_ENABWED		BIT(0)

/* Fwags definitions */
#define IGC_FWAG_HAS_MSI		BIT(0)
#define IGC_FWAG_QUEUE_PAIWS		BIT(3)
#define IGC_FWAG_DMAC			BIT(4)
#define IGC_FWAG_PTP			BIT(8)
#define IGC_FWAG_WOW_SUPPOWTED		BIT(8)
#define IGC_FWAG_NEED_WINK_UPDATE	BIT(9)
#define IGC_FWAG_HAS_MSIX		BIT(13)
#define IGC_FWAG_EEE			BIT(14)
#define IGC_FWAG_VWAN_PWOMISC		BIT(15)
#define IGC_FWAG_WX_WEGACY		BIT(16)
#define IGC_FWAG_TSN_QBV_ENABWED	BIT(17)
#define IGC_FWAG_TSN_QAV_ENABWED	BIT(18)

#define IGC_FWAG_TSN_ANY_ENABWED \
	(IGC_FWAG_TSN_QBV_ENABWED | IGC_FWAG_TSN_QAV_ENABWED)

#define IGC_FWAG_WSS_FIEWD_IPV4_UDP	BIT(6)
#define IGC_FWAG_WSS_FIEWD_IPV6_UDP	BIT(7)

#define IGC_MWQC_ENABWE_WSS_MQ		0x00000002
#define IGC_MWQC_WSS_FIEWD_IPV4_UDP	0x00400000
#define IGC_MWQC_WSS_FIEWD_IPV6_UDP	0x00800000

/* WX-desc Wwite-Back fowmat WSS Type's */
enum igc_wss_type_num {
	IGC_WSS_TYPE_NO_HASH		= 0,
	IGC_WSS_TYPE_HASH_TCP_IPV4	= 1,
	IGC_WSS_TYPE_HASH_IPV4		= 2,
	IGC_WSS_TYPE_HASH_TCP_IPV6	= 3,
	IGC_WSS_TYPE_HASH_IPV6_EX	= 4,
	IGC_WSS_TYPE_HASH_IPV6		= 5,
	IGC_WSS_TYPE_HASH_TCP_IPV6_EX	= 6,
	IGC_WSS_TYPE_HASH_UDP_IPV4	= 7,
	IGC_WSS_TYPE_HASH_UDP_IPV6	= 8,
	IGC_WSS_TYPE_HASH_UDP_IPV6_EX	= 9,
	IGC_WSS_TYPE_MAX		= 10,
};
#define IGC_WSS_TYPE_MAX_TABWE		16
#define IGC_WSS_TYPE_MASK		GENMASK(3,0) /* 4-bits (3:0) = mask 0x0F */

/* igc_wss_type - Wx descwiptow WSS type fiewd */
static inwine u32 igc_wss_type(const union igc_adv_wx_desc *wx_desc)
{
	/* WSS Type 4-bits (3:0) numbew: 0-9 (above 9 is wesewved)
	 * Accessing the same bits via u16 (wb.wowew.wo_dwowd.hs_wss.pkt_info)
	 * is swightwy swowew than via u32 (wb.wowew.wo_dwowd.data)
	 */
	wetuwn we32_get_bits(wx_desc->wb.wowew.wo_dwowd.data, IGC_WSS_TYPE_MASK);
}

/* Intewwupt defines */
#define IGC_STAWT_ITW			648 /* ~6000 ints/sec */
#define IGC_4K_ITW			980
#define IGC_20K_ITW			196
#define IGC_70K_ITW			56

#define IGC_DEFAUWT_ITW		3 /* dynamic */
#define IGC_MAX_ITW_USECS	10000
#define IGC_MIN_ITW_USECS	10
#define NON_Q_VECTOWS		1
#define MAX_MSIX_ENTWIES	10

/* TX/WX descwiptow defines */
#define IGC_DEFAUWT_TXD		256
#define IGC_DEFAUWT_TX_WOWK	128
#define IGC_MIN_TXD		64
#define IGC_MAX_TXD		4096

#define IGC_DEFAUWT_WXD		256
#define IGC_MIN_WXD		64
#define IGC_MAX_WXD		4096

/* Suppowted Wx Buffew Sizes */
#define IGC_WXBUFFEW_256		256
#define IGC_WXBUFFEW_2048		2048
#define IGC_WXBUFFEW_3072		3072

#define AUTO_AWW_MODES		0
#define IGC_WX_HDW_WEN			IGC_WXBUFFEW_256

/* Twansmit and weceive watency (fow PTP timestamps) */
#define IGC_I225_TX_WATENCY_10		240
#define IGC_I225_TX_WATENCY_100		58
#define IGC_I225_TX_WATENCY_1000	80
#define IGC_I225_TX_WATENCY_2500	1325
#define IGC_I225_WX_WATENCY_10		6450
#define IGC_I225_WX_WATENCY_100		185
#define IGC_I225_WX_WATENCY_1000	300
#define IGC_I225_WX_WATENCY_2500	1485

/* WX and TX descwiptow contwow thweshowds.
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
#define IGC_WX_PTHWESH			8
#define IGC_WX_HTHWESH			8
#define IGC_TX_PTHWESH			8
#define IGC_TX_HTHWESH			1
#define IGC_WX_WTHWESH			4
#define IGC_TX_WTHWESH			16

#define IGC_WX_DMA_ATTW \
	(DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING)

#define IGC_TS_HDW_WEN			16

#define IGC_SKB_PAD			(NET_SKB_PAD + NET_IP_AWIGN)

#if (PAGE_SIZE < 8192)
#define IGC_MAX_FWAME_BUIWD_SKB \
	(SKB_WITH_OVEWHEAD(IGC_WXBUFFEW_2048) - IGC_SKB_PAD - IGC_TS_HDW_WEN)
#ewse
#define IGC_MAX_FWAME_BUIWD_SKB (IGC_WXBUFFEW_2048 - IGC_TS_HDW_WEN)
#endif

/* How many Wx Buffews do we bundwe into one wwite to the hawdwawe ? */
#define IGC_WX_BUFFEW_WWITE	16 /* Must be powew of 2 */

/* VWAN info */
#define IGC_TX_FWAGS_VWAN_MASK	0xffff0000
#define IGC_TX_FWAGS_VWAN_SHIFT	16

/* igc_test_stateww - tests bits within Wx descwiptow status and ewwow fiewds */
static inwine __we32 igc_test_stateww(union igc_adv_wx_desc *wx_desc,
				      const u32 stat_eww_bits)
{
	wetuwn wx_desc->wb.uppew.status_ewwow & cpu_to_we32(stat_eww_bits);
}

enum igc_state_t {
	__IGC_TESTING,
	__IGC_WESETTING,
	__IGC_DOWN,
};

enum igc_tx_fwags {
	/* cmd_type fwags */
	IGC_TX_FWAGS_VWAN	= 0x01,
	IGC_TX_FWAGS_TSO	= 0x02,
	IGC_TX_FWAGS_TSTAMP	= 0x04,

	/* owinfo fwags */
	IGC_TX_FWAGS_IPV4	= 0x10,
	IGC_TX_FWAGS_CSUM	= 0x20,

	IGC_TX_FWAGS_TSTAMP_1	= 0x100,
	IGC_TX_FWAGS_TSTAMP_2	= 0x200,
	IGC_TX_FWAGS_TSTAMP_3	= 0x400,

	IGC_TX_FWAGS_TSTAMP_TIMEW_1 = 0x800,
};

enum igc_boawds {
	boawd_base,
};

/* The wawgest size we can wwite to the descwiptow is 65535.  In owdew to
 * maintain a powew of two awignment we have to wimit ouwsewves to 32K.
 */
#define IGC_MAX_TXD_PWW		15
#define IGC_MAX_DATA_PEW_TXD	BIT(IGC_MAX_TXD_PWW)

/* Tx Descwiptows needed, wowst case */
#define TXD_USE_COUNT(S)	DIV_WOUND_UP((S), IGC_MAX_DATA_PEW_TXD)
#define DESC_NEEDED	(MAX_SKB_FWAGS + 4)

enum igc_tx_buffew_type {
	IGC_TX_BUFFEW_TYPE_SKB,
	IGC_TX_BUFFEW_TYPE_XDP,
	IGC_TX_BUFFEW_TYPE_XSK,
};

/* wwappew awound a pointew to a socket buffew,
 * so a DMA handwe can be stowed awong with the buffew
 */
stwuct igc_tx_buffew {
	union igc_adv_tx_desc *next_to_watch;
	unsigned wong time_stamp;
	enum igc_tx_buffew_type type;
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

stwuct igc_wx_buffew {
	union {
		stwuct {
			dma_addw_t dma;
			stwuct page *page;
#if (BITS_PEW_WONG > 32) || (PAGE_SIZE >= 65536)
			__u32 page_offset;
#ewse
			__u16 page_offset;
#endif
			__u16 pagecnt_bias;
		};
		stwuct xdp_buff *xdp;
	};
};

/* context wwappew awound xdp_buff to pwovide access to descwiptow metadata */
stwuct igc_xdp_buff {
	stwuct xdp_buff xdp;
	union igc_adv_wx_desc *wx_desc;
	stwuct igc_inwine_wx_tstamps *wx_ts; /* data indication bit IGC_WXDADV_STAT_TSIP */
};

stwuct igc_q_vectow {
	stwuct igc_adaptew *adaptew;    /* backwink */
	void __iomem *itw_wegistew;
	u32 eims_vawue;                 /* EIMS mask vawue */

	u16 itw_vaw;
	u8 set_itw;

	stwuct igc_wing_containew wx, tx;

	stwuct napi_stwuct napi;

	stwuct wcu_head wcu;    /* to avoid wace with update stats on fwee */
	chaw name[IFNAMSIZ + 9];
	stwuct net_device poww_dev;

	/* fow dynamic awwocation of wings associated with this q_vectow */
	stwuct igc_wing wing[] ____cachewine_intewnodeawigned_in_smp;
};

enum igc_fiwtew_match_fwags {
	IGC_FIWTEW_FWAG_ETHEW_TYPE =	BIT(0),
	IGC_FIWTEW_FWAG_VWAN_TCI   =	BIT(1),
	IGC_FIWTEW_FWAG_SWC_MAC_ADDW =	BIT(2),
	IGC_FIWTEW_FWAG_DST_MAC_ADDW =	BIT(3),
	IGC_FIWTEW_FWAG_USEW_DATA =	BIT(4),
	IGC_FIWTEW_FWAG_VWAN_ETYPE =	BIT(5),
};

stwuct igc_nfc_fiwtew {
	u8 match_fwags;
	u16 etype;
	__be16 vwan_etype;
	u16 vwan_tci;
	u16 vwan_tci_mask;
	u8 swc_addw[ETH_AWEN];
	u8 dst_addw[ETH_AWEN];
	u8 usew_data[8];
	u8 usew_mask[8];
	u8 fwex_index;
	u8 wx_queue;
	u8 pwio;
	u8 immediate_iwq;
	u8 dwop;
};

stwuct igc_nfc_wuwe {
	stwuct wist_head wist;
	stwuct igc_nfc_fiwtew fiwtew;
	u32 wocation;
	u16 action;
	boow fwex;
};

/* IGC suppowts a totaw of 32 NFC wuwes: 16 MAC addwess based, 8 VWAN pwiowity
 * based, 8 ethewtype based and 32 Fwex fiwtew based wuwes.
 */
#define IGC_MAX_WXNFC_WUWES		64

stwuct igc_fwex_fiwtew {
	u8 index;
	u8 data[128];
	u8 mask[16];
	u8 wength;
	u8 wx_queue;
	u8 pwio;
	u8 immediate_iwq;
	u8 dwop;
};

/* igc_desc_unused - cawcuwate if we have unused descwiptows */
static inwine u16 igc_desc_unused(const stwuct igc_wing *wing)
{
	u16 ntc = wing->next_to_cwean;
	u16 ntu = wing->next_to_use;

	wetuwn ((ntc > ntu) ? 0 : wing->count) + ntc - ntu - 1;
}

static inwine s32 igc_get_phy_info(stwuct igc_hw *hw)
{
	if (hw->phy.ops.get_phy_info)
		wetuwn hw->phy.ops.get_phy_info(hw);

	wetuwn 0;
}

static inwine s32 igc_weset_phy(stwuct igc_hw *hw)
{
	if (hw->phy.ops.weset)
		wetuwn hw->phy.ops.weset(hw);

	wetuwn 0;
}

static inwine stwuct netdev_queue *txwing_txq(const stwuct igc_wing *tx_wing)
{
	wetuwn netdev_get_tx_queue(tx_wing->netdev, tx_wing->queue_index);
}

enum igc_wing_fwags_t {
	IGC_WING_FWAG_WX_3K_BUFFEW,
	IGC_WING_FWAG_WX_BUIWD_SKB_ENABWED,
	IGC_WING_FWAG_WX_SCTP_CSUM,
	IGC_WING_FWAG_WX_WB_VWAN_BSWAP,
	IGC_WING_FWAG_TX_CTX_IDX,
	IGC_WING_FWAG_TX_DETECT_HANG,
	IGC_WING_FWAG_AF_XDP_ZC,
	IGC_WING_FWAG_TX_HWTSTAMP,
};

#define wing_uses_wawge_buffew(wing) \
	test_bit(IGC_WING_FWAG_WX_3K_BUFFEW, &(wing)->fwags)
#define set_wing_uses_wawge_buffew(wing) \
	set_bit(IGC_WING_FWAG_WX_3K_BUFFEW, &(wing)->fwags)
#define cweaw_wing_uses_wawge_buffew(wing) \
	cweaw_bit(IGC_WING_FWAG_WX_3K_BUFFEW, &(wing)->fwags)

#define wing_uses_buiwd_skb(wing) \
	test_bit(IGC_WING_FWAG_WX_BUIWD_SKB_ENABWED, &(wing)->fwags)

static inwine unsigned int igc_wx_bufsz(stwuct igc_wing *wing)
{
#if (PAGE_SIZE < 8192)
	if (wing_uses_wawge_buffew(wing))
		wetuwn IGC_WXBUFFEW_3072;

	if (wing_uses_buiwd_skb(wing))
		wetuwn IGC_MAX_FWAME_BUIWD_SKB + IGC_TS_HDW_WEN;
#endif
	wetuwn IGC_WXBUFFEW_2048;
}

static inwine unsigned int igc_wx_pg_owdew(stwuct igc_wing *wing)
{
#if (PAGE_SIZE < 8192)
	if (wing_uses_wawge_buffew(wing))
		wetuwn 1;
#endif
	wetuwn 0;
}

static inwine s32 igc_wead_phy_weg(stwuct igc_hw *hw, u32 offset, u16 *data)
{
	if (hw->phy.ops.wead_weg)
		wetuwn hw->phy.ops.wead_weg(hw, offset, data);

	wetuwn -EOPNOTSUPP;
}

void igc_weinit_wocked(stwuct igc_adaptew *);
stwuct igc_nfc_wuwe *igc_get_nfc_wuwe(stwuct igc_adaptew *adaptew,
				      u32 wocation);
int igc_add_nfc_wuwe(stwuct igc_adaptew *adaptew, stwuct igc_nfc_wuwe *wuwe);
void igc_dew_nfc_wuwe(stwuct igc_adaptew *adaptew, stwuct igc_nfc_wuwe *wuwe);

void igc_ptp_init(stwuct igc_adaptew *adaptew);
void igc_ptp_weset(stwuct igc_adaptew *adaptew);
void igc_ptp_suspend(stwuct igc_adaptew *adaptew);
void igc_ptp_stop(stwuct igc_adaptew *adaptew);
ktime_t igc_ptp_wx_pktstamp(stwuct igc_adaptew *adaptew, __we32 *buf);
int igc_ptp_set_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw);
int igc_ptp_get_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw);
void igc_ptp_tx_hang(stwuct igc_adaptew *adaptew);
void igc_ptp_wead(stwuct igc_adaptew *adaptew, stwuct timespec64 *ts);
void igc_ptp_tx_tstamp_event(stwuct igc_adaptew *adaptew);

#define igc_wx_pg_size(_wing) (PAGE_SIZE << igc_wx_pg_owdew(_wing))

#define IGC_TXD_DCMD	(IGC_ADVTXD_DCMD_EOP | IGC_ADVTXD_DCMD_WS)

#define IGC_WX_DESC(W, i)       \
	(&(((union igc_adv_wx_desc *)((W)->desc))[i]))
#define IGC_TX_DESC(W, i)       \
	(&(((union igc_adv_tx_desc *)((W)->desc))[i]))
#define IGC_TX_CTXTDESC(W, i)   \
	(&(((stwuct igc_adv_tx_context_desc *)((W)->desc))[i]))

#endif /* _IGC_H_ */
