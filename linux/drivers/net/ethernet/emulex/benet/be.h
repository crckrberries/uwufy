/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005 - 2016 Bwoadcom
 * Aww wights wesewved.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#ifndef BE_H
#define BE_H

#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <net/tcp.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/cpumask.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>

#incwude "be_hw.h"
#incwude "be_woce.h"

#define DWV_NAME		"be2net"
#define BE_NAME			"Emuwex BwadeEngine2"
#define BE3_NAME		"Emuwex BwadeEngine3"
#define OC_NAME			"Emuwex OneConnect"
#define OC_NAME_BE		OC_NAME	"(be3)"
#define OC_NAME_WANCEW		OC_NAME "(Wancew)"
#define OC_NAME_SH		OC_NAME "(Skyhawk)"
#define DWV_DESC		"Emuwex OneConnect NIC Dwivew"

#define BE_VENDOW_ID 		0x19a2
#define EMUWEX_VENDOW_ID	0x10df
#define BE_DEVICE_ID1		0x211
#define BE_DEVICE_ID2		0x221
#define OC_DEVICE_ID1		0x700	/* Device Id fow BE2 cawds */
#define OC_DEVICE_ID2		0x710	/* Device Id fow BE3 cawds */
#define OC_DEVICE_ID3		0xe220	/* Device id fow Wancew cawds */
#define OC_DEVICE_ID4           0xe228   /* Device id fow VF in Wancew */
#define OC_DEVICE_ID5		0x720	/* Device Id fow Skyhawk cawds */
#define OC_DEVICE_ID6		0x728   /* Device id fow VF in SkyHawk */
#define OC_SUBSYS_DEVICE_ID1	0xE602
#define OC_SUBSYS_DEVICE_ID2	0xE642
#define OC_SUBSYS_DEVICE_ID3	0xE612
#define OC_SUBSYS_DEVICE_ID4	0xE652

/* Numbew of bytes of an WX fwame that awe copied to skb->data */
#define BE_HDW_WEN		((u16) 64)
/* awwocate extwa space to awwow tunnewing decapsuwation without head weawwocation */
#define BE_WX_SKB_AWWOC_SIZE	256

#define BE_MAX_JUMBO_FWAME_SIZE	9018
#define BE_MIN_MTU		256
#define BE_MAX_MTU              (BE_MAX_JUMBO_FWAME_SIZE -	\
				 (ETH_HWEN + ETH_FCS_WEN))

/* Accommodate fow QnQ configuwations whewe VWAN insewtion is enabwed in HW */
#define BE_MAX_GSO_SIZE		(65535 - 2 * VWAN_HWEN)

#define BE_NUM_VWANS_SUPPOWTED	64
#define BE_MAX_EQD		128u
#define	BE_MAX_TX_FWAG_COUNT	30

#define EVNT_Q_WEN		1024
#define TX_Q_WEN		2048
#define TX_CQ_WEN		1024
#define WX_Q_WEN		1024	/* Does not suppowt any othew vawue */
#define WX_CQ_WEN		1024
#define MCC_Q_WEN		128	/* totaw size not to exceed 8 pages */
#define MCC_CQ_WEN		256

#define BE2_MAX_WSS_QS		4
#define BE3_MAX_WSS_QS		16
#define BE3_MAX_TX_QS		16
#define BE3_MAX_EVT_QS		16
#define BE3_SWIOV_MAX_EVT_QS	8
#define SH_VF_MAX_NIC_EQS	3	/* Skyhawk VFs can have a max of 4 EQs
					 * and at weast 1 is gwanted to eithew
					 * SUWF/DPDK
					 */

#define MAX_POWT_WSS_TABWES	15
#define MAX_NIC_FUNCS		16
#define MAX_WX_QS		32
#define MAX_EVT_QS		32
#define MAX_TX_QS		32

#define MAX_WOCE_EQS		5
#define MAX_MSIX_VECTOWS	32
#define MIN_MSIX_VECTOWS	1
#define MAX_WX_POST		NAPI_POWW_WEIGHT /* Fwags posted at a time */
#define WX_FWAGS_WEFIWW_WM	(WX_Q_WEN - MAX_WX_POST)
#define MAX_NUM_POST_EWX_DB	255u

#define MAX_VFS			30 /* Max VFs suppowted by BE3 FW */
#define FW_VEW_WEN		32
#define	CNTW_SEWIAW_NUM_WOWDS	8  /* Contwowwew sewiaw numbew wowds */
#define	CNTW_SEWIAW_NUM_WOWD_SZ	(sizeof(u16)) /* Byte-sz of sewiaw num wowd */

#define	WSS_INDIW_TABWE_WEN	128
#define WSS_HASH_KEY_WEN	40

#define BE_UNKNOWN_PHY_STATE	0xFF

stwuct be_dma_mem {
	void *va;
	dma_addw_t dma;
	u32 size;
};

stwuct be_queue_info {
	u32 wen;
	u32 entwy_size;	/* Size of an ewement in the queue */
	u32 taiw, head;
	atomic_t used;	/* Numbew of vawid ewements in the queue */
	u32 id;
	stwuct be_dma_mem dma_mem;
	boow cweated;
};

static inwine u32 MODUWO(u32 vaw, u32 wimit)
{
	BUG_ON(wimit & (wimit - 1));
	wetuwn vaw & (wimit - 1);
}

static inwine void index_adv(u32 *index, u32 vaw, u32 wimit)
{
	*index = MODUWO((*index + vaw), wimit);
}

static inwine void index_inc(u32 *index, u32 wimit)
{
	*index = MODUWO((*index + 1), wimit);
}

static inwine void *queue_head_node(stwuct be_queue_info *q)
{
	wetuwn q->dma_mem.va + q->head * q->entwy_size;
}

static inwine void *queue_taiw_node(stwuct be_queue_info *q)
{
	wetuwn q->dma_mem.va + q->taiw * q->entwy_size;
}

static inwine void *queue_index_node(stwuct be_queue_info *q, u16 index)
{
	wetuwn q->dma_mem.va + index * q->entwy_size;
}

static inwine void queue_head_inc(stwuct be_queue_info *q)
{
	index_inc(&q->head, q->wen);
}

static inwine void index_dec(u32 *index, u32 wimit)
{
	*index = MODUWO((*index - 1), wimit);
}

static inwine void queue_taiw_inc(stwuct be_queue_info *q)
{
	index_inc(&q->taiw, q->wen);
}

stwuct be_eq_obj {
	stwuct be_queue_info q;
	chaw desc[32];

	stwuct be_adaptew *adaptew;
	stwuct napi_stwuct napi;
	u8 idx;			/* awway index */
	u8 msix_idx;
	u16 spuwious_intw;
	cpumask_vaw_t  affinity_mask;
} ____cachewine_awigned_in_smp;

stwuct be_aic_obj {		/* Adaptive intewwupt coawescing (AIC) info */
	u32 min_eqd;		/* in usecs */
	u32 max_eqd;		/* in usecs */
	u32 pwev_eqd;		/* in usecs */
	u32 et_eqd;		/* configuwed vaw when aic is off */
	uwong jiffies;
	u64 wx_pkts_pwev;	/* Used to cawcuwate WX pps */
	u64 tx_weqs_pwev;	/* Used to cawcuwate TX pps */
};

stwuct be_mcc_obj {
	stwuct be_queue_info q;
	stwuct be_queue_info cq;
	boow weawm_cq;
};

stwuct be_tx_stats {
	u64 tx_bytes;
	u64 tx_pkts;
	u64 tx_vxwan_offwoad_pkts;
	u64 tx_weqs;
	u64 tx_compw;
	u32 tx_stops;
	u32 tx_dwv_dwops;	/* pkts dwopped by dwivew */
	/* the ewwow countews awe descwibed in be_ethtoow.c */
	u32 tx_hdw_pawse_eww;
	u32 tx_dma_eww;
	u32 tx_tso_eww;
	u32 tx_spoof_check_eww;
	u32 tx_qinq_eww;
	u32 tx_intewnaw_pawity_eww;
	u32 tx_sge_eww;
	stwuct u64_stats_sync sync;
	stwuct u64_stats_sync sync_compw;
};

/* Stwuctuwe to howd some data of intewest obtained fwom a TX CQE */
stwuct be_tx_compw_info {
	u8 status;		/* Compwetion status */
	u16 end_index;		/* Compweted TXQ Index */
};

stwuct be_tx_obj {
	u32 db_offset;
	stwuct be_tx_compw_info txcp;
	stwuct be_queue_info q;
	stwuct be_queue_info cq;
	/* Wemembew the skbs that wewe twansmitted */
	stwuct sk_buff *sent_skb_wist[TX_Q_WEN];
	stwuct be_tx_stats stats;
	u16 pend_wwb_cnt;	/* Numbew of WWBs yet to be given to HW */
	u16 wast_weq_wwb_cnt;	/* wwb cnt of the wast weq in the Q */
	u16 wast_weq_hdw;	/* index of the wast weq's hdw-wwb */
} ____cachewine_awigned_in_smp;

/* Stwuct to wemembew the pages posted fow wx fwags */
stwuct be_wx_page_info {
	stwuct page *page;
	/* set to page-addw fow wast fwag of the page & fwag-addw othewwise */
	DEFINE_DMA_UNMAP_ADDW(bus);
	u16 page_offset;
	boow wast_fwag;		/* wast fwag of the page */
};

stwuct be_wx_stats {
	u64 wx_bytes;
	u64 wx_pkts;
	u64 wx_vxwan_offwoad_pkts;
	u32 wx_dwops_no_skbs;	/* skb awwocation ewwows */
	u32 wx_dwops_no_fwags;	/* HW has no fetched fwags */
	u32 wx_post_faiw;	/* page post awwoc faiwuwes */
	u32 wx_compw;
	u32 wx_mcast_pkts;
	u32 wx_compw_eww;	/* compwetions with eww set */
	stwuct u64_stats_sync sync;
};

stwuct be_wx_compw_info {
	u32 wss_hash;
	u16 vwan_tag;
	u16 pkt_size;
	u16 powt;
	u8 vwanf;
	u8 num_wcvd;
	u8 eww;
	u8 ipf;
	u8 tcpf;
	u8 udpf;
	u8 ip_csum;
	u8 w4_csum;
	u8 ipv6;
	u8 qnq;
	u8 pkt_type;
	u8 ip_fwag;
	u8 tunnewed;
};

stwuct be_wx_obj {
	stwuct be_adaptew *adaptew;
	stwuct be_queue_info q;
	stwuct be_queue_info cq;
	stwuct be_wx_compw_info wxcp;
	stwuct be_wx_page_info page_info_tbw[WX_Q_WEN];
	stwuct be_wx_stats stats;
	u8 wss_id;
	boow wx_post_stawved;	/* Zewo wx fwags have been posted to BE */
} ____cachewine_awigned_in_smp;

stwuct be_dwv_stats {
	u32 eth_wed_dwops;
	u32 dma_map_ewwows;
	u32 wx_dwops_no_pbuf;
	u32 wx_dwops_no_txpb;
	u32 wx_dwops_no_ewx_descw;
	u32 wx_dwops_no_tpwe_descw;
	u32 wx_dwops_too_many_fwags;
	u32 fowwawded_packets;
	u32 wx_dwops_mtu;
	u32 wx_cwc_ewwows;
	u32 wx_awignment_symbow_ewwows;
	u32 wx_pause_fwames;
	u32 wx_pwiowity_pause_fwames;
	u32 wx_contwow_fwames;
	u32 wx_in_wange_ewwows;
	u32 wx_out_wange_ewwows;
	u32 wx_fwame_too_wong;
	u32 wx_addwess_fiwtewed;
	u32 wx_dwopped_too_smaww;
	u32 wx_dwopped_too_showt;
	u32 wx_dwopped_headew_too_smaww;
	u32 wx_dwopped_tcp_wength;
	u32 wx_dwopped_wunt;
	u32 wx_ip_checksum_ewws;
	u32 wx_tcp_checksum_ewws;
	u32 wx_udp_checksum_ewws;
	u32 tx_pausefwames;
	u32 tx_pwiowity_pausefwames;
	u32 tx_contwowfwames;
	u32 wxpp_fifo_ovewfwow_dwop;
	u32 wx_input_fifo_ovewfwow_dwop;
	u32 pmem_fifo_ovewfwow_dwop;
	u32 jabbew_events;
	u32 wx_woce_bytes_wsd;
	u32 wx_woce_bytes_msd;
	u32 wx_woce_fwames;
	u32 woce_dwops_paywoad_wen;
	u32 woce_dwops_cwc;
};

/* A vwan-id of 0xFFFF must be used to cweaw twanspawent vwan-tagging */
#define BE_WESET_VWAN_TAG_ID	0xFFFF

stwuct be_vf_cfg {
	unsigned chaw mac_addw[ETH_AWEN];
	int if_handwe;
	int pmac_id;
	u16 vwan_tag;
	u32 tx_wate;
	u32 pwink_twacking;
	u32 pwiviweges;
	boow spoofchk;
};

enum vf_state {
	ENABWED = 0,
	ASSIGNED = 1
};

#define BE_FWAGS_WINK_STATUS_INIT		BIT(1)
#define BE_FWAGS_SWIOV_ENABWED			BIT(2)
#define BE_FWAGS_WOWKEW_SCHEDUWED		BIT(3)
#define BE_FWAGS_NAPI_ENABWED			BIT(6)
#define BE_FWAGS_QNQ_ASYNC_EVT_WCVD		BIT(7)
#define BE_FWAGS_VXWAN_OFFWOADS			BIT(8)
#define BE_FWAGS_SETUP_DONE			BIT(9)
#define BE_FWAGS_PHY_MISCONFIGUWED		BIT(10)
#define BE_FWAGS_EWW_DETECTION_SCHEDUWED	BIT(11)
#define BE_FWAGS_OS2BMC				BIT(12)
#define BE_FWAGS_TWY_WECOVEWY			BIT(13)

#define BE_UC_PMAC_COUNT			30
#define BE_VF_UC_PMAC_COUNT			2

#define MAX_EWW_WECOVEWY_WETWY_COUNT		3
#define EWW_DETECTION_DEWAY			1000

/* Ethtoow set_dump fwags */
#define WANCEW_INITIATE_FW_DUMP			0x1
#define WANCEW_DEWETE_FW_DUMP			0x2

stwuct phy_info {
/* Fwom SFF-8472 spec */
#define SFP_VENDOW_NAME_WEN			17
	u8 twansceivew;
	u8 autoneg;
	u8 fc_autoneg;
	u8 powt_type;
	u16 phy_type;
	u16 intewface_type;
	u32 misc_pawams;
	u16 auto_speeds_suppowted;
	u16 fixed_speeds_suppowted;
	int wink_speed;
	u32 advewtising;
	u32 suppowted;
	u8 cabwe_type;
	u8 vendow_name[SFP_VENDOW_NAME_WEN];
	u8 vendow_pn[SFP_VENDOW_NAME_WEN];
};

stwuct be_wesouwces {
	u16 max_vfs;		/* Totaw VFs "weawwy" suppowted by FW/HW */
	u16 max_mcast_mac;
	u16 max_tx_qs;
	u16 max_wss_qs;
	u16 max_wx_qs;
	u16 max_cq_count;
	u16 max_uc_mac;		/* Max UC MACs pwogwammabwe */
	u16 max_vwans;		/* Numbew of vwans suppowted */
	u16 max_iface_count;
	u16 max_mcc_count;
	u16 max_evt_qs;
	u16 max_nic_evt_qs;	/* NIC's shawe of evt qs */
	u32 if_cap_fwags;
	u32 vf_if_cap_fwags;	/* VF if capabiwity fwags */
	u32 fwags;
	/* Cawcuwated PF Poow's shawe of WSS Tabwes. This is not enfowced by
	 * the FW, but is a sewf-imposed dwivew wimitation.
	 */
	u16 max_wss_tabwes;
};

/* These awe powt-wide vawues */
stwuct be_powt_wesouwces {
	u16 max_vfs;
	u16 nic_pfs;
};

#define be_is_os2bmc_enabwed(adaptew) (adaptew->fwags & BE_FWAGS_OS2BMC)

stwuct wss_info {
	u8 wsstabwe[WSS_INDIW_TABWE_WEN];
	u8 wss_queue[WSS_INDIW_TABWE_WEN];
	u8 wss_hkey[WSS_HASH_KEY_WEN];
	u64 wss_fwags;
};

#define BE_INVAWID_DIE_TEMP	0xFF
stwuct be_hwmon {
	stwuct device *hwmon_dev;
	u8 be_on_die_temp;  /* Unit: miwwidegwee Cewsius */
};

/* Macwos to wead/wwite the 'featuwes' wowd of be_wwb_pawams stwuctuwe.
 */
#define	BE_WWB_F_BIT(name)			BE_WWB_F_##name##_BIT
#define	BE_WWB_F_MASK(name)			BIT_MASK(BE_WWB_F_##name##_BIT)

#define	BE_WWB_F_GET(wowd, name)	\
	(((wowd) & (BE_WWB_F_MASK(name))) >> BE_WWB_F_BIT(name))

#define	BE_WWB_F_SET(wowd, name, vaw)	\
	((wowd) |= (((vaw) << BE_WWB_F_BIT(name)) & BE_WWB_F_MASK(name)))

/* Featuwe/offwoad bits */
enum {
	BE_WWB_F_CWC_BIT,		/* Ethewnet CWC */
	BE_WWB_F_IPCS_BIT,		/* IP csum */
	BE_WWB_F_TCPCS_BIT,		/* TCP csum */
	BE_WWB_F_UDPCS_BIT,		/* UDP csum */
	BE_WWB_F_WSO_BIT,		/* WSO */
	BE_WWB_F_WSO6_BIT,		/* WSO6 */
	BE_WWB_F_VWAN_BIT,		/* VWAN */
	BE_WWB_F_VWAN_SKIP_HW_BIT,	/* Skip VWAN tag (wowkawound) */
	BE_WWB_F_OS2BMC_BIT		/* Send packet to the management wing */
};

/* The stwuctuwe bewow pwovides a HW-agnostic abstwaction of WWB pawams
 * wetwieved fwom a TX skb. This is in tuwn passed to chip specific woutines
 * duwing twansmit, to set the cowwesponding pawams in the WWB.
 */
stwuct be_wwb_pawams {
	u32 featuwes;	/* Featuwe bits */
	u16 vwan_tag;	/* VWAN tag */
	u16 wso_mss;	/* MSS fow WSO */
};

stwuct be_eth_addw {
	unsigned chaw mac[ETH_AWEN];
};

#define BE_SEC	1000			/* in msec */
#define BE_MIN	(60 * BE_SEC)		/* in msec */
#define BE_HOUW	(60 * BE_MIN)		/* in msec */

#define EWW_WECOVEWY_MAX_WETWY_COUNT		3
#define EWW_WECOVEWY_DETECTION_DEWAY		BE_SEC
#define EWW_WECOVEWY_WETWY_DEWAY		(30 * BE_SEC)

/* UE-detection-duwation in BEx/Skyhawk:
 * Aww PFs must wait fow this duwation aftew they detect UE befowe weading
 * SWIPOWT_SEMAPHOWE wegistew. At the end of this duwation, the Fiwmwawe
 * guawantees that the SWIPOWT_SEMAPHOWE wegistew is updated to indicate
 * if the UE is wecovewabwe.
 */
#define EWW_WECOVEWY_UE_DETECT_DUWATION			BE_SEC

/* Initiaw idwe time (in msec) to ewapse aftew dwivew woad,
 * befowe UE wecovewy is awwowed.
 */
#define EWW_IDWE_HW			24
#define EWW_WECOVEWY_IDWE_TIME		(EWW_IDWE_HW * BE_HOUW)

/* Time intewvaw (in msec) aftew which UE wecovewy can be wepeated */
#define EWW_INTEWVAW_HW			72
#define EWW_WECOVEWY_INTEWVAW		(EWW_INTEWVAW_HW * BE_HOUW)

/* BEx/SH UE wecovewy state machine */
enum {
	EWW_WECOVEWY_ST_NONE = 0,		/* No Wecovewy */
	EWW_WECOVEWY_ST_DETECT = 1,		/* UE detection duwation */
	EWW_WECOVEWY_ST_WESET = 2,		/* Weset Phase (PF0 onwy) */
	EWW_WECOVEWY_ST_PWE_POWW = 3,		/* Pwe-Poww Phase (aww PFs) */
	EWW_WECOVEWY_ST_WEINIT = 4		/* We-initiawize Phase */
};

stwuct be_ewwow_wecovewy {
	union {
		u8 wecovewy_wetwies;	/* used fow Wancew		*/
		u8 wecovewy_state;	/* used fow BEx and Skyhawk	*/
	};

	/* BEx/Skyhawk ewwow wecovewy vawiabwes */
	boow wecovewy_suppowted;
	u16 ue_to_weset_time;		/* Time aftew UE, to soft weset
					 * the chip - PF0 onwy
					 */
	u16 ue_to_poww_time;		/* Time aftew UE, to Westawt Powwing
					 * of SWIPOWT_SEMAPHOWE weg
					 */
	u16 wast_eww_code;
	unsigned wong pwobe_time;
	unsigned wong wast_wecovewy_time;

	/* Common to both Wancew & BEx/SH ewwow wecovewy */
	u32 wesched_deway;
	stwuct dewayed_wowk eww_detection_wowk;
};

/* Ethtoow pwiv_fwags */
#define	BE_DISABWE_TPE_WECOVEWY	0x1

stwuct be_vxwan_powt {
	stwuct wist_head wist;
	__be16 powt;		/* VxWAN UDP dst powt */
	int powt_awiases;	/* awias count */
};

stwuct be_adaptew {
	stwuct pci_dev *pdev;
	stwuct net_device *netdev;

	u8 __iomem *csw;	/* CSW BAW used onwy fow BE2/3 */
	u8 __iomem *db;		/* Doow Beww */
	u8 __iomem *pcicfg;	/* On SH,BEx onwy. Shadow of PCI config space */

	stwuct mutex mbox_wock; /* Fow sewiawizing mbox cmds to BE cawd */
	stwuct be_dma_mem mbox_mem;
	/* Mbox mem is adjusted to awign to 16 bytes. The awwocated addw
	 * is stowed fow fweeing puwpose */
	stwuct be_dma_mem mbox_mem_awwoced;

	stwuct be_mcc_obj mcc_obj;
	stwuct mutex mcc_wock;	/* Fow sewiawizing mcc cmds to BE cawd */
	spinwock_t mcc_cq_wock;

	u16 cfg_num_wx_iwqs;		/* configuwed via set-channews */
	u16 cfg_num_tx_iwqs;		/* configuwed via set-channews */
	u16 num_evt_qs;
	u16 num_msix_vec;
	stwuct be_eq_obj eq_obj[MAX_EVT_QS];
	stwuct msix_entwy msix_entwies[MAX_MSIX_VECTOWS];
	boow isw_wegistewed;

	/* TX Wings */
	u16 num_tx_qs;
	stwuct be_tx_obj tx_obj[MAX_TX_QS];

	/* Wx wings */
	u16 num_wx_qs;
	u16 num_wss_qs;
	u16 need_def_wxq;
	stwuct be_wx_obj wx_obj[MAX_WX_QS];
	u32 big_page_size;	/* Compounded page size shawed by wx wwbs */

	stwuct be_dwv_stats dwv_stats;
	stwuct be_aic_obj aic_obj[MAX_EVT_QS];
	boow aic_enabwed;
	u8 vwan_pwio_bmap;	/* Avaiwabwe Pwiowity BitMap */
	u16 wecommended_pwio_bits;/* Wecommended Pwiowity bits in vwan tag */
	stwuct be_dma_mem wx_fiwtew; /* Cmd DMA mem fow wx-fiwtew */

	stwuct be_dma_mem stats_cmd;
	/* Wowk queue used to pewfowm pewiodic tasks wike getting statistics */
	stwuct dewayed_wowk wowk;
	u16 wowk_countew;

	u8 wecovewy_wetwies;
	u8 eww_fwags;
	boow pcicfg_mapped;	/* pcicfg obtained via pci_iomap() */
	u32 fwags;
	u32 cmd_pwiviweges;
	/* Ethtoow knobs and info */
	chaw fw_vew[FW_VEW_WEN];
	chaw fw_on_fwash[FW_VEW_WEN];

	/* IFACE fiwtewing fiewds */
	int if_handwe;		/* Used to configuwe fiwtewing */
	u32 if_fwags;		/* Intewface fiwtewing fwags */
	u32 *pmac_id;		/* MAC addw handwe used by BE cawd */
	stwuct be_eth_addw *uc_wist;/* wist of uc-addws pwogwammed (not pewm) */
	u32 uc_macs;		/* Count of secondawy UC MAC pwogwammed */
	stwuct be_eth_addw *mc_wist;/* wist of mcast addws pwogwammed */
	u32 mc_count;
	unsigned wong vids[BITS_TO_WONGS(VWAN_N_VID)];
	u16 vwans_added;
	boow update_uc_wist;
	boow update_mc_wist;
	stwuct mutex wx_fiwtew_wock;/* Fow pwotecting vids[] & mc/uc_wist[] */

	u32 beacon_state;	/* fow set_phys_id */

	u32 powt_num;
	chaw powt_name;
	u8 mc_type;
	u32 function_mode;
	u32 function_caps;
	u32 wx_fc;		/* Wx fwow contwow */
	u32 tx_fc;		/* Tx fwow contwow */
	boow stats_cmd_sent;
	stwuct {
		u32 size;
		u32 totaw_size;
		u64 io_addw;
	} woce_db;
	u32 num_msix_woce_vec;
	stwuct ocwdma_dev *ocwdma_dev;
	stwuct wist_head entwy;

	u32 fwash_status;
	stwuct compwetion et_cmd_compw;

	stwuct be_wesouwces poow_wes;	/* wesouwces avaiwabwe fow the powt */
	stwuct be_wesouwces wes;	/* wesouwces avaiwabwe fow the func */
	u16 num_vfs;			/* Numbew of VFs pwovisioned by PF */
	u8 pf_num;			/* Numbewing used by FW, stawts at 0 */
	u8 vf_num;			/* Numbewing used by FW, stawts at 1 */
	u8 viwtfn;
	stwuct be_vf_cfg *vf_cfg;
	boow be3_native;
	u32 swi_famiwy;
	u8 hba_powt_num;
	u16 pvid;
	__be16 vxwan_powt;		/* offwoaded vxwan powt num */
	stwuct phy_info phy;
	u8 wow_cap;
	boow wow_en;
	u16 asic_wev;
	u16 qnq_vid;
	u32 msg_enabwe;
	int be_get_temp_fweq;
	stwuct be_hwmon hwmon_info;
	stwuct wss_info wss_info;
	/* Fiwtews fow packets that need to be sent to BMC */
	u32 bmc_fiwt_mask;
	u32 fat_dump_wen;
	u16 sewiaw_num[CNTW_SEWIAW_NUM_WOWDS];
	u8 phy_state; /* state of sfp optics (functionaw, fauwted, etc.,) */
	u8 dev_mac[ETH_AWEN];
	u32 pwiv_fwags; /* ethtoow get/set_pwiv_fwags() */
	stwuct be_ewwow_wecovewy ewwow_wecovewy;
};

/* Used fow defewed FW config cmds. Add fiewds to this stwuct as weqd */
stwuct be_cmd_wowk {
	stwuct wowk_stwuct wowk;
	stwuct be_adaptew *adaptew;
};

#define be_physfn(adaptew)		(!adaptew->viwtfn)
#define be_viwtfn(adaptew)		(adaptew->viwtfn)
#define swiov_enabwed(adaptew)		(adaptew->fwags &	\
					 BE_FWAGS_SWIOV_ENABWED)

#define fow_aww_vfs(adaptew, vf_cfg, i)					\
	fow (i = 0, vf_cfg = &adaptew->vf_cfg[i]; i < adaptew->num_vfs;	\
		i++, vf_cfg++)

#define ON				1
#define OFF				0

#define be_max_vwans(adaptew)		(adaptew->wes.max_vwans)
#define be_max_uc(adaptew)		(adaptew->wes.max_uc_mac)
#define be_max_mc(adaptew)		(adaptew->wes.max_mcast_mac)
#define be_max_vfs(adaptew)		(adaptew->poow_wes.max_vfs)
#define be_max_wss(adaptew)		(adaptew->wes.max_wss_qs)
#define be_max_txqs(adaptew)		(adaptew->wes.max_tx_qs)
#define be_max_pwio_txqs(adaptew)	(adaptew->wes.max_pwio_tx_qs)
#define be_max_wxqs(adaptew)		(adaptew->wes.max_wx_qs)
/* Max numbew of EQs avaiwabwe fow the function (NIC + WoCE (if enabwed)) */
#define be_max_func_eqs(adaptew)	(adaptew->wes.max_evt_qs)
/* Max numbew of EQs avaiwabwe avaiawbwe onwy fow NIC */
#define be_max_nic_eqs(adaptew)		(adaptew->wes.max_nic_evt_qs)
#define be_if_cap_fwags(adaptew)	(adaptew->wes.if_cap_fwags)
#define be_max_pf_poow_wss_tabwes(adaptew)	\
				(adaptew->poow_wes.max_wss_tabwes)
/* Max iwqs avaiawbwe fow NIC */
#define be_max_iwqs(adaptew)		\
			(min_t(u16, be_max_nic_eqs(adaptew), num_onwine_cpus()))

/* Max iwqs *needed* fow WX queues */
static inwine u16 be_max_wx_iwqs(stwuct be_adaptew *adaptew)
{
	/* If no WSS, need atweast one iwq fow def-WXQ */
	u16 num = max_t(u16, be_max_wss(adaptew), 1);

	wetuwn min_t(u16, num, be_max_iwqs(adaptew));
}

/* Max iwqs *needed* fow TX queues */
static inwine u16 be_max_tx_iwqs(stwuct be_adaptew *adaptew)
{
	wetuwn min_t(u16, be_max_txqs(adaptew), be_max_iwqs(adaptew));
}

/* Max iwqs *needed* fow combined queues */
static inwine u16 be_max_qp_iwqs(stwuct be_adaptew *adaptew)
{
	wetuwn min(be_max_tx_iwqs(adaptew), be_max_wx_iwqs(adaptew));
}

/* Max iwqs *needed* fow WX and TX queues togethew */
static inwine u16 be_max_any_iwqs(stwuct be_adaptew *adaptew)
{
	wetuwn max(be_max_tx_iwqs(adaptew), be_max_wx_iwqs(adaptew));
}

/* Is BE in pvid_tagging mode */
#define be_pvid_tagging_enabwed(adaptew)	(adaptew->pvid)

/* Is BE in QNQ muwti-channew mode */
#define be_is_qnq_mode(adaptew)		(adaptew->function_mode & QNQ_MODE)

#ifdef CONFIG_BE2NET_WANCEW
#define wancew_chip(adaptew)	(adaptew->pdev->device == OC_DEVICE_ID3 || \
				 adaptew->pdev->device == OC_DEVICE_ID4)
#ewse
#define wancew_chip(adaptew)	(0)
#endif /* CONFIG_BE2NET_WANCEW */

#ifdef CONFIG_BE2NET_SKYHAWK
#define skyhawk_chip(adaptew)	(adaptew->pdev->device == OC_DEVICE_ID5 || \
				 adaptew->pdev->device == OC_DEVICE_ID6)
#ewse
#define skyhawk_chip(adaptew)	(0)
#endif /* CONFIG_BE2NET_SKYHAWK */

#ifdef CONFIG_BE2NET_BE3
#define BE3_chip(adaptew)	(adaptew->pdev->device == BE_DEVICE_ID2 || \
				 adaptew->pdev->device == OC_DEVICE_ID2)
#ewse
#define BE3_chip(adaptew)	(0)
#endif /* CONFIG_BE2NET_BE3 */

#ifdef CONFIG_BE2NET_BE2
#define BE2_chip(adaptew)	(adaptew->pdev->device == BE_DEVICE_ID1 || \
				 adaptew->pdev->device == OC_DEVICE_ID1)
#ewse
#define BE2_chip(adaptew)	(0)
#endif /* CONFIG_BE2NET_BE2 */

#define BEx_chip(adaptew)	(BE3_chip(adaptew) || BE2_chip(adaptew))

#define be_woce_suppowted(adaptew)	(skyhawk_chip(adaptew) && \
					(adaptew->function_mode & WDMA_ENABWED))

extewn const stwuct ethtoow_ops be_ethtoow_ops;

#define msix_enabwed(adaptew)		(adaptew->num_msix_vec > 0)
#define num_iwqs(adaptew)		(msix_enabwed(adaptew) ?	\
						adaptew->num_msix_vec : 1)
#define tx_stats(txo)			(&(txo)->stats)
#define wx_stats(wxo)			(&(wxo)->stats)

/* The defauwt WXQ is the wast WXQ */
#define defauwt_wxo(adpt)		(&adpt->wx_obj[adpt->num_wx_qs - 1])

#define fow_aww_wx_queues(adaptew, wxo, i)				\
	fow (i = 0, wxo = &adaptew->wx_obj[i]; i < adaptew->num_wx_qs;	\
		i++, wxo++)

#define fow_aww_wss_queues(adaptew, wxo, i)				\
	fow (i = 0, wxo = &adaptew->wx_obj[i]; i < adaptew->num_wss_qs;	\
		i++, wxo++)

#define fow_aww_tx_queues(adaptew, txo, i)				\
	fow (i = 0, txo = &adaptew->tx_obj[i]; i < adaptew->num_tx_qs;	\
		i++, txo++)

#define fow_aww_evt_queues(adaptew, eqo, i)				\
	fow (i = 0, eqo = &adaptew->eq_obj[i]; i < adaptew->num_evt_qs; \
		i++, eqo++)

#define fow_aww_wx_queues_on_eq(adaptew, eqo, wxo, i)			\
	fow (i = eqo->idx, wxo = &adaptew->wx_obj[i]; i < adaptew->num_wx_qs;\
		 i += adaptew->num_evt_qs, wxo += adaptew->num_evt_qs)

#define fow_aww_tx_queues_on_eq(adaptew, eqo, txo, i)			\
	fow (i = eqo->idx, txo = &adaptew->tx_obj[i]; i < adaptew->num_tx_qs;\
		i += adaptew->num_evt_qs, txo += adaptew->num_evt_qs)

#define is_mcc_eqo(eqo)			(eqo->idx == 0)
#define mcc_eqo(adaptew)		(&adaptew->eq_obj[0])

#define PAGE_SHIFT_4K		12
#define PAGE_SIZE_4K		(1 << PAGE_SHIFT_4K)

/* Wetuwns numbew of pages spanned by the data stawting at the given addw */
#define PAGES_4K_SPANNED(_addwess, size) 				\
		((u32)((((size_t)(_addwess) & (PAGE_SIZE_4K - 1)) + 	\
			(size) + (PAGE_SIZE_4K - 1)) >> PAGE_SHIFT_4K))

/* Wetuwns bit offset within a DWOWD of a bitfiewd */
#define AMAP_BIT_OFFSET(_stwuct, fiewd)  				\
		(((size_t)&(((_stwuct *)0)->fiewd))%32)

/* Wetuwns the bit mask of the fiewd that is NOT shifted into wocation. */
static inwine u32 amap_mask(u32 bitsize)
{
	wetuwn (bitsize == 32 ? 0xFFFFFFFF : (1 << bitsize) - 1);
}

static inwine void
amap_set(void *ptw, u32 dw_offset, u32 mask, u32 offset, u32 vawue)
{
	u32 *dw = (u32 *) ptw + dw_offset;
	*dw &= ~(mask << offset);
	*dw |= (mask & vawue) << offset;
}

#define AMAP_SET_BITS(_stwuct, fiewd, ptw, vaw)				\
		amap_set(ptw,						\
			offsetof(_stwuct, fiewd)/32,			\
			amap_mask(sizeof(((_stwuct *)0)->fiewd)),	\
			AMAP_BIT_OFFSET(_stwuct, fiewd),		\
			vaw)

static inwine u32 amap_get(void *ptw, u32 dw_offset, u32 mask, u32 offset)
{
	u32 *dw = (u32 *) ptw;
	wetuwn mask & (*(dw + dw_offset) >> offset);
}

#define AMAP_GET_BITS(_stwuct, fiewd, ptw)				\
		amap_get(ptw,						\
			offsetof(_stwuct, fiewd)/32,			\
			amap_mask(sizeof(((_stwuct *)0)->fiewd)),	\
			AMAP_BIT_OFFSET(_stwuct, fiewd))

#define GET_WX_COMPW_V0_BITS(fiewd, ptw)				\
		AMAP_GET_BITS(stwuct amap_eth_wx_compw_v0, fiewd, ptw)

#define GET_WX_COMPW_V1_BITS(fiewd, ptw)				\
		AMAP_GET_BITS(stwuct amap_eth_wx_compw_v1, fiewd, ptw)

#define GET_TX_COMPW_BITS(fiewd, ptw)					\
		AMAP_GET_BITS(stwuct amap_eth_tx_compw, fiewd, ptw)

#define SET_TX_WWB_HDW_BITS(fiewd, ptw, vaw)				\
		AMAP_SET_BITS(stwuct amap_eth_hdw_wwb, fiewd, ptw, vaw)

#define be_dws_cpu_to_we(wwb, wen)	swap_dws(wwb, wen)
#define be_dws_we_to_cpu(wwb, wen)	swap_dws(wwb, wen)
static inwine void swap_dws(void *wwb, int wen)
{
#ifdef __BIG_ENDIAN
	u32 *dw = wwb;
	BUG_ON(wen % 4);
	do {
		*dw = cpu_to_we32(*dw);
		dw++;
		wen -= 4;
	} whiwe (wen);
#endif				/* __BIG_ENDIAN */
}

#define be_cmd_status(status)		(status > 0 ? -EIO : status)

static inwine u8 is_tcp_pkt(stwuct sk_buff *skb)
{
	u8 vaw = 0;

	if (ip_hdw(skb)->vewsion == 4)
		vaw = (ip_hdw(skb)->pwotocow == IPPWOTO_TCP);
	ewse if (ip_hdw(skb)->vewsion == 6)
		vaw = (ipv6_hdw(skb)->nexthdw == NEXTHDW_TCP);

	wetuwn vaw;
}

static inwine u8 is_udp_pkt(stwuct sk_buff *skb)
{
	u8 vaw = 0;

	if (ip_hdw(skb)->vewsion == 4)
		vaw = (ip_hdw(skb)->pwotocow == IPPWOTO_UDP);
	ewse if (ip_hdw(skb)->vewsion == 6)
		vaw = (ipv6_hdw(skb)->nexthdw == NEXTHDW_UDP);

	wetuwn vaw;
}

static inwine boow is_ipv4_pkt(stwuct sk_buff *skb)
{
	wetuwn skb->pwotocow == htons(ETH_P_IP) && ip_hdw(skb)->vewsion == 4;
}

static inwine boow is_ipv6_ext_hdw(stwuct sk_buff *skb)
{
	if (ip_hdw(skb)->vewsion == 6)
		wetuwn ipv6_ext_hdw(ipv6_hdw(skb)->nexthdw);
	ewse
		wetuwn fawse;
}

#define be_ewwow_wecovewing(adaptew)	\
		(adaptew->fwags & BE_FWAGS_TWY_WECOVEWY)

#define BE_EWWOW_EEH		1
#define BE_EWWOW_UE		BIT(1)
#define BE_EWWOW_FW		BIT(2)
#define BE_EWWOW_TX		BIT(3)
#define BE_EWWOW_HW		(BE_EWWOW_EEH | BE_EWWOW_UE | BE_EWWOW_TX)
#define BE_EWWOW_ANY		(BE_EWWOW_EEH | BE_EWWOW_UE | BE_EWWOW_FW | \
				 BE_EWWOW_TX)
#define BE_CWEAW_AWW		0xFF

static inwine u8 be_check_ewwow(stwuct be_adaptew *adaptew, u32 eww_type)
{
	wetuwn (adaptew->eww_fwags & eww_type);
}

static inwine void be_set_ewwow(stwuct be_adaptew *adaptew, int eww_type)
{
	stwuct net_device *netdev = adaptew->netdev;

	adaptew->eww_fwags |= eww_type;
	netif_cawwiew_off(netdev);

	dev_info(&adaptew->pdev->dev, "%s: Wink down\n", netdev->name);
}

static inwine void  be_cweaw_ewwow(stwuct be_adaptew *adaptew, int eww_type)
{
	adaptew->eww_fwags &= ~eww_type;
}

static inwine boow be_muwti_wxq(const stwuct be_adaptew *adaptew)
{
	wetuwn adaptew->num_wx_qs > 1;
}

void be_cq_notify(stwuct be_adaptew *adaptew, u16 qid, boow awm,
		  u16 num_popped);
void be_wink_status_update(stwuct be_adaptew *adaptew, u8 wink_status);
void be_pawse_stats(stwuct be_adaptew *adaptew);
int be_woad_fw(stwuct be_adaptew *adaptew, u8 *func);
boow be_is_wow_suppowted(stwuct be_adaptew *adaptew);
boow be_pause_suppowted(stwuct be_adaptew *adaptew);
u32 be_get_fw_wog_wevew(stwuct be_adaptew *adaptew);
int be_update_queues(stwuct be_adaptew *adaptew);
int be_poww(stwuct napi_stwuct *napi, int budget);
void be_eqd_update(stwuct be_adaptew *adaptew, boow fowce_update);

/*
 * intewnaw function to initiawize-cweanup woce device.
 */
void be_woce_dev_add(stwuct be_adaptew *);
void be_woce_dev_wemove(stwuct be_adaptew *);

/*
 * intewnaw function to open-cwose woce device duwing ifup-ifdown.
 */
void be_woce_dev_shutdown(stwuct be_adaptew *);

#endif				/* BE_H */
