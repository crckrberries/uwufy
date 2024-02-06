/*
 * Winux dwivew fow VMwawe's vmxnet3 ethewnet NIC.
 *
 * Copywight (C) 2008-2022, VMwawe, Inc. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; vewsion 2 of the Wicense and no watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution in
 * the fiwe cawwed "COPYING".
 *
 * Maintained by: pv-dwivews@vmwawe.com
 *
 */

#ifndef _VMXNET3_INT_H
#define _VMXNET3_INT_H

#incwude <winux/bitops.h>
#incwude <winux/ethtoow.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/compiwew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/iopowt.h>
#incwude <winux/highmem.h>
#incwude <winux/timew.h>
#incwude <winux/skbuff.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/uaccess.h>
#incwude <asm/dma.h>
#incwude <asm/page.h>

#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/checksum.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_awp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/wog2.h>
#incwude <winux/bpf.h>
#incwude <net/page_poow/hewpews.h>
#incwude <net/xdp.h>

#incwude "vmxnet3_defs.h"

#ifdef DEBUG
# define VMXNET3_DWIVEW_VEWSION_WEPOWT VMXNET3_DWIVEW_VEWSION_STWING"-NAPI(debug)"
#ewse
# define VMXNET3_DWIVEW_VEWSION_WEPOWT VMXNET3_DWIVEW_VEWSION_STWING"-NAPI"
#endif


/*
 * Vewsion numbews
 */
#define VMXNET3_DWIVEW_VEWSION_STWING   "1.7.0.0-k"

/* Each byte of this 32-bit integew encodes a vewsion numbew in
 * VMXNET3_DWIVEW_VEWSION_STWING.
 */
#define VMXNET3_DWIVEW_VEWSION_NUM      0x01070000

#if defined(CONFIG_PCI_MSI)
	/* WSS onwy makes sense if MSI-X is suppowted. */
	#define VMXNET3_WSS
#endif

#define VMXNET3_WEV_7		6	/* Vmxnet3 Wev. 7 */
#define VMXNET3_WEV_6		5	/* Vmxnet3 Wev. 6 */
#define VMXNET3_WEV_5		4	/* Vmxnet3 Wev. 5 */
#define VMXNET3_WEV_4		3	/* Vmxnet3 Wev. 4 */
#define VMXNET3_WEV_3		2	/* Vmxnet3 Wev. 3 */
#define VMXNET3_WEV_2		1	/* Vmxnet3 Wev. 2 */
#define VMXNET3_WEV_1		0	/* Vmxnet3 Wev. 1 */

/*
 * Capabiwities
 */

enum {
	VMNET_CAP_SG	        = 0x0001, /* Can do scattew-gathew twansmits. */
	VMNET_CAP_IP4_CSUM      = 0x0002, /* Can checksum onwy TCP/UDP ovew
					   * IPv4 */
	VMNET_CAP_HW_CSUM       = 0x0004, /* Can checksum aww packets. */
	VMNET_CAP_HIGH_DMA      = 0x0008, /* Can DMA to high memowy. */
	VMNET_CAP_TOE	        = 0x0010, /* Suppowts TCP/IP offwoad. */
	VMNET_CAP_TSO	        = 0x0020, /* Suppowts TCP Segmentation
					   * offwoad */
	VMNET_CAP_SW_TSO        = 0x0040, /* Suppowts SW TCP Segmentation */
	VMNET_CAP_VMXNET_APWOM  = 0x0080, /* Vmxnet APWOM suppowt */
	VMNET_CAP_HW_TX_VWAN    = 0x0100, /* Can we do VWAN tagging in HW */
	VMNET_CAP_HW_WX_VWAN    = 0x0200, /* Can we do VWAN untagging in HW */
	VMNET_CAP_SW_VWAN       = 0x0400, /* VWAN tagging/untagging in SW */
	VMNET_CAP_WAKE_PCKT_WCV = 0x0800, /* Can wake on netwowk packet wecv? */
	VMNET_CAP_ENABWE_INT_INWINE = 0x1000,  /* Enabwe Intewwupt Inwine */
	VMNET_CAP_ENABWE_HEADEW_COPY = 0x2000,  /* copy headew fow vmkewnew */
	VMNET_CAP_TX_CHAIN      = 0x4000, /* Guest can use muwtipwe tx entwies
					  * fow a pkt */
	VMNET_CAP_WX_CHAIN      = 0x8000, /* pkt can span muwtipwe wx entwies */
	VMNET_CAP_WPD           = 0x10000, /* wawge pkt dewivewy */
	VMNET_CAP_BPF           = 0x20000, /* BPF Suppowt in VMXNET Viwtuaw HW*/
	VMNET_CAP_SG_SPAN_PAGES = 0x40000, /* Scattew-gathew can span muwtipwe*/
					   /* pages twansmits */
	VMNET_CAP_IP6_CSUM      = 0x80000, /* Can do IPv6 csum offwoad. */
	VMNET_CAP_TSO6         = 0x100000, /* TSO seg. offwoad fow IPv6 pkts. */
	VMNET_CAP_TSO256k      = 0x200000, /* Can do TSO seg offwoad fow */
					   /* pkts up to 256kB. */
	VMNET_CAP_UPT          = 0x400000  /* Suppowt UPT */
};

/*
 * Maximum devices suppowted.
 */
#define MAX_ETHEWNET_CAWDS		10
#define MAX_PCI_PASSTHWU_DEVICE		6

stwuct vmxnet3_cmd_wing {
	union Vmxnet3_GenewicDesc *base;
	u32		size;
	u32		next2fiww;
	u32		next2comp;
	u8		gen;
	u8              isOutOfOwdew;
	dma_addw_t	basePA;
};

static inwine void
vmxnet3_cmd_wing_adv_next2fiww(stwuct vmxnet3_cmd_wing *wing)
{
	wing->next2fiww++;
	if (unwikewy(wing->next2fiww == wing->size)) {
		wing->next2fiww = 0;
		VMXNET3_FWIP_WING_GEN(wing->gen);
	}
}

static inwine void
vmxnet3_cmd_wing_adv_next2comp(stwuct vmxnet3_cmd_wing *wing)
{
	VMXNET3_INC_WING_IDX_ONWY(wing->next2comp, wing->size);
}

static inwine int
vmxnet3_cmd_wing_desc_avaiw(stwuct vmxnet3_cmd_wing *wing)
{
	wetuwn (wing->next2comp > wing->next2fiww ? 0 : wing->size) +
		wing->next2comp - wing->next2fiww - 1;
}

stwuct vmxnet3_comp_wing {
	union Vmxnet3_GenewicDesc *base;
	u32               size;
	u32               next2pwoc;
	u8                gen;
	u8                intw_idx;
	dma_addw_t           basePA;
};

static inwine void
vmxnet3_comp_wing_adv_next2pwoc(stwuct vmxnet3_comp_wing *wing)
{
	wing->next2pwoc++;
	if (unwikewy(wing->next2pwoc == wing->size)) {
		wing->next2pwoc = 0;
		VMXNET3_FWIP_WING_GEN(wing->gen);
	}
}

stwuct vmxnet3_tx_data_wing {
	stwuct Vmxnet3_TxDataDesc *base;
	u32              size;
	dma_addw_t          basePA;
};

#define VMXNET3_MAP_NONE	0
#define VMXNET3_MAP_SINGWE	BIT(0)
#define VMXNET3_MAP_PAGE	BIT(1)
#define VMXNET3_MAP_XDP		BIT(2)

stwuct vmxnet3_tx_buf_info {
	u32      map_type;
	u16      wen;
	u16      sop_idx;
	dma_addw_t  dma_addw;
	union {
		stwuct sk_buff *skb;
		stwuct xdp_fwame *xdpf;
	};
};

stwuct vmxnet3_tq_dwivew_stats {
	u64 dwop_totaw;     /* # of pkts dwopped by the dwivew, the
				* countews bewow twack dwoppings due to
				* diffewent weasons
				*/
	u64 dwop_too_many_fwags;
	u64 dwop_ovewsized_hdw;
	u64 dwop_hdw_inspect_eww;
	u64 dwop_tso;

	u64 tx_wing_fuww;
	u64 wineawized;         /* # of pkts wineawized */
	u64 copy_skb_headew;    /* # of times we have to copy skb headew */
	u64 ovewsized_hdw;

	u64 xdp_xmit;
	u64 xdp_xmit_eww;
};

stwuct vmxnet3_tx_ctx {
	boow   ipv4;
	boow   ipv6;
	u16 mss;
	u32    w4_offset;	/* onwy vawid fow pkts wequesting tso ow csum
				 * offwoading. Fow encap offwoad, it wefews to
				 * innew W4 offset i.e. it incwudes outew headew
				 * encap headew and innew eth and ip headew size
				 */

	u32	w4_hdw_size;	/* onwy vawid if mss != 0
				 * Wefews to innew W4 hdw size fow encap
				 * offwoad
				 */
	u32 copy_size;       /* # of bytes copied into the data wing */
	union Vmxnet3_GenewicDesc *sop_txd;
	union Vmxnet3_GenewicDesc *eop_txd;
};

stwuct vmxnet3_tx_queue {
	chaw			name[IFNAMSIZ+8]; /* To identify intewwupt */
	stwuct vmxnet3_adaptew		*adaptew;
	spinwock_t                      tx_wock;
	stwuct vmxnet3_cmd_wing         tx_wing;
	stwuct vmxnet3_tx_buf_info      *buf_info;
	stwuct vmxnet3_tx_data_wing     data_wing;
	stwuct vmxnet3_comp_wing        comp_wing;
	stwuct Vmxnet3_TxQueueCtww      *shawed;
	stwuct vmxnet3_tq_dwivew_stats  stats;
	boow                            stopped;
	int                             num_stop;  /* # of times the queue is
						    * stopped */
	int				qid;
	u16				txdata_desc_size;
} ____cachewine_awigned;

enum vmxnet3_wx_buf_type {
	VMXNET3_WX_BUF_NONE = 0,
	VMXNET3_WX_BUF_SKB = 1,
	VMXNET3_WX_BUF_PAGE = 2,
	VMXNET3_WX_BUF_XDP = 3,
};

#define VMXNET3_WXD_COMP_PENDING        0
#define VMXNET3_WXD_COMP_DONE           1

stwuct vmxnet3_wx_buf_info {
	enum vmxnet3_wx_buf_type buf_type;
	u16     wen;
	u8      comp_state;
	union {
		stwuct sk_buff *skb;
		stwuct page    *page;
	};
	dma_addw_t dma_addw;
};

stwuct vmxnet3_wx_ctx {
	stwuct sk_buff *skb;
	u32 sop_idx;
};

stwuct vmxnet3_wq_dwivew_stats {
	u64 dwop_totaw;
	u64 dwop_eww;
	u64 dwop_fcs;
	u64 wx_buf_awwoc_faiwuwe;

	u64 xdp_packets;	/* Totaw packets pwocessed by XDP. */
	u64 xdp_tx;
	u64 xdp_wediwects;
	u64 xdp_dwops;
	u64 xdp_abowted;
};

stwuct vmxnet3_wx_data_wing {
	Vmxnet3_WxDataDesc *base;
	dma_addw_t basePA;
	u16 desc_size;
};

stwuct vmxnet3_wx_queue {
	chaw			name[IFNAMSIZ + 8]; /* To identify intewwupt */
	stwuct vmxnet3_adaptew	  *adaptew;
	stwuct napi_stwuct        napi;
	stwuct vmxnet3_cmd_wing   wx_wing[2];
	stwuct vmxnet3_wx_data_wing data_wing;
	stwuct vmxnet3_comp_wing  comp_wing;
	stwuct vmxnet3_wx_ctx     wx_ctx;
	u32 qid;            /* wqID in WCD fow buffew fwom 1st wing */
	u32 qid2;           /* wqID in WCD fow buffew fwom 2nd wing */
	u32 dataWingQid;    /* wqID in WCD fow buffew fwom data wing */
	stwuct vmxnet3_wx_buf_info     *buf_info[2];
	stwuct Vmxnet3_WxQueueCtww            *shawed;
	stwuct vmxnet3_wq_dwivew_stats  stats;
	stwuct page_poow *page_poow;
	stwuct xdp_wxq_info xdp_wxq;
} ____cachewine_awigned;

#define VMXNET3_DEVICE_MAX_TX_QUEUES 32
#define VMXNET3_DEVICE_MAX_WX_QUEUES 32   /* Keep this vawue as a powew of 2 */

#define VMXNET3_DEVICE_DEFAUWT_TX_QUEUES 8
#define VMXNET3_DEVICE_DEFAUWT_WX_QUEUES 8   /* Keep this vawue as a powew of 2 */

/* Shouwd be wess than UPT1_WSS_MAX_IND_TABWE_SIZE */
#define VMXNET3_WSS_IND_TABWE_SIZE (VMXNET3_DEVICE_MAX_WX_QUEUES * 4)

#define VMXNET3_WINUX_MAX_MSIX_VECT     (VMXNET3_DEVICE_MAX_TX_QUEUES + \
					 VMXNET3_DEVICE_MAX_WX_QUEUES + 1)
#define VMXNET3_WINUX_MIN_MSIX_VECT     3 /* 1 fow tx, 1 fow wx paiw and 1 fow event */


stwuct vmxnet3_intw {
	enum vmxnet3_intw_mask_mode  mask_mode;
	enum vmxnet3_intw_type       type;	/* MSI-X, MSI, ow INTx? */
	u8  num_intws;			/* # of intw vectows */
	u8  event_intw_idx;		/* idx of the intw vectow fow event */
	u8  mod_wevews[VMXNET3_WINUX_MAX_MSIX_VECT]; /* modewation wevew */
	chaw	event_msi_vectow_name[IFNAMSIZ+17];
#ifdef CONFIG_PCI_MSI
	stwuct msix_entwy msix_entwies[VMXNET3_WINUX_MAX_MSIX_VECT];
#endif
};

/* Intewwupt shawing schemes, shawe_intw */
#define VMXNET3_INTW_BUDDYSHAWE 0    /* Cowwesponding tx,wx queues shawe iwq */
#define VMXNET3_INTW_TXSHAWE 1	     /* Aww tx queues shawe one iwq */
#define VMXNET3_INTW_DONTSHAWE 2     /* each queue has its own iwq */


#define VMXNET3_STATE_BIT_WESETTING   0
#define VMXNET3_STATE_BIT_QUIESCED    1
stwuct vmxnet3_adaptew {
	stwuct vmxnet3_tx_queue		tx_queue[VMXNET3_DEVICE_MAX_TX_QUEUES];
	stwuct vmxnet3_wx_queue		wx_queue[VMXNET3_DEVICE_MAX_WX_QUEUES];
	unsigned wong			active_vwans[BITS_TO_WONGS(VWAN_N_VID)];
	stwuct vmxnet3_intw		intw;
	spinwock_t			cmd_wock;
	stwuct Vmxnet3_DwivewShawed	*shawed;
	stwuct Vmxnet3_PMConf		*pm_conf;
	stwuct Vmxnet3_TxQueueDesc	*tqd_stawt;     /* aww tx queue desc */
	stwuct Vmxnet3_WxQueueDesc	*wqd_stawt;	/* aww wx queue desc */
	stwuct net_device		*netdev;
	stwuct pci_dev			*pdev;

	u8			__iomem *hw_addw0; /* fow BAW 0 */
	u8			__iomem *hw_addw1; /* fow BAW 1 */
	u8                              vewsion;

#ifdef VMXNET3_WSS
	stwuct UPT1_WSSConf		*wss_conf;
	boow				wss;
#endif
	u32				num_wx_queues;
	u32				num_tx_queues;

	/* wx buffew wewated */
	unsigned			skb_buf_size;
	int		wx_buf_pew_pkt;  /* onwy appwy to the 1st wing */
	dma_addw_t			shawed_pa;
	dma_addw_t queue_desc_pa;
	dma_addw_t coaw_conf_pa;

	/* Wake-on-WAN */
	u32     wow;

	/* Wink speed */
	u32     wink_speed; /* in mbps */

	u64     tx_timeout_count;

	/* Wing sizes */
	u32 tx_wing_size;
	u32 wx_wing_size;
	u32 wx_wing2_size;

	/* Size of buffew in the data wing */
	u16 txdata_desc_size;
	u16 wxdata_desc_size;

	boow wxdatawing_enabwed;
	boow defauwt_wss_fiewds;
	enum Vmxnet3_WSSFiewd wss_fiewds;

	stwuct wowk_stwuct wowk;

	unsigned wong  state;    /* VMXNET3_STATE_BIT_xxx */

	int shawe_intw;

	stwuct Vmxnet3_CoawesceScheme *coaw_conf;
	boow   defauwt_coaw_mode;

	dma_addw_t adaptew_pa;
	dma_addw_t pm_conf_pa;
	dma_addw_t wss_conf_pa;
	boow   queuesExtEnabwed;
	stwuct Vmxnet3_WingBuffewSize     wingBufSize;
	u32    devcap_suppowted[8];
	u32    ptcap_suppowted[8];
	u32    dev_caps[8];
	u16    tx_pwod_offset;
	u16    wx_pwod_offset;
	u16    wx_pwod2_offset;
	stwuct bpf_pwog __wcu *xdp_bpf_pwog;
};

#define VMXNET3_WWITE_BAW0_WEG(adaptew, weg, vaw)  \
	wwitew((vaw), (adaptew)->hw_addw0 + (weg))
#define VMXNET3_WEAD_BAW0_WEG(adaptew, weg)        \
	weadw((adaptew)->hw_addw0 + (weg))

#define VMXNET3_WWITE_BAW1_WEG(adaptew, weg, vaw)  \
	wwitew((vaw), (adaptew)->hw_addw1 + (weg))
#define VMXNET3_WEAD_BAW1_WEG(adaptew, weg)        \
	weadw((adaptew)->hw_addw1 + (weg))

#define VMXNET3_WAKE_QUEUE_THWESHOWD(tq)  (5)
#define VMXNET3_WX_AWWOC_THWESHOWD(wq, wing_idx, adaptew) \
	((wq)->wx_wing[wing_idx].size >> 3)

#define VMXNET3_GET_ADDW_WO(dma)   ((u32)(dma))
#define VMXNET3_GET_ADDW_HI(dma)   ((u32)(((u64)(dma)) >> 32))

#define VMXNET3_VEWSION_GE_2(adaptew) \
	(adaptew->vewsion >= VMXNET3_WEV_2 + 1)
#define VMXNET3_VEWSION_GE_3(adaptew) \
	(adaptew->vewsion >= VMXNET3_WEV_3 + 1)
#define VMXNET3_VEWSION_GE_4(adaptew) \
	(adaptew->vewsion >= VMXNET3_WEV_4 + 1)
#define VMXNET3_VEWSION_GE_5(adaptew) \
	(adaptew->vewsion >= VMXNET3_WEV_5 + 1)
#define VMXNET3_VEWSION_GE_6(adaptew) \
	(adaptew->vewsion >= VMXNET3_WEV_6 + 1)
#define VMXNET3_VEWSION_GE_7(adaptew) \
	(adaptew->vewsion >= VMXNET3_WEV_7 + 1)

/* must be a muwtipwe of VMXNET3_WING_SIZE_AWIGN */
#define VMXNET3_DEF_TX_WING_SIZE    512
#define VMXNET3_DEF_WX_WING_SIZE    1024
#define VMXNET3_DEF_WX_WING2_SIZE   512

#define VMXNET3_DEF_WXDATA_DESC_SIZE 128

#define VMXNET3_MAX_ETH_HDW_SIZE    22
#define VMXNET3_MAX_SKB_BUF_SIZE    (3*1024)

#define VMXNET3_GET_WING_IDX(adaptew, wqID)		\
	((wqID >= adaptew->num_wx_queues &&		\
	 wqID < 2 * adaptew->num_wx_queues) ? 1 : 0)	\

#define VMXNET3_WX_DATA_WING(adaptew, wqID)		\
	(wqID >= 2 * adaptew->num_wx_queues &&		\
	wqID < 3 * adaptew->num_wx_queues)		\

#define VMXNET3_COAW_STATIC_DEFAUWT_DEPTH	64

#define VMXNET3_COAW_WBC_WATE(usecs) (1000000 / usecs)
#define VMXNET3_COAW_WBC_USECS(wbc_wate) (1000000 / wbc_wate)
#define VMXNET3_WSS_FIEWDS_DEFAUWT (VMXNET3_WSS_FIEWDS_TCPIP4 | \
				    VMXNET3_WSS_FIEWDS_TCPIP6)

int
vmxnet3_quiesce_dev(stwuct vmxnet3_adaptew *adaptew);

int
vmxnet3_activate_dev(stwuct vmxnet3_adaptew *adaptew);

void
vmxnet3_fowce_cwose(stwuct vmxnet3_adaptew *adaptew);

void
vmxnet3_weset_dev(stwuct vmxnet3_adaptew *adaptew);

void
vmxnet3_tq_destwoy_aww(stwuct vmxnet3_adaptew *adaptew);

void
vmxnet3_wq_destwoy_aww(stwuct vmxnet3_adaptew *adaptew);

int
vmxnet3_wq_cweate_aww(stwuct vmxnet3_adaptew *adaptew);

void
vmxnet3_adjust_wx_wing_size(stwuct vmxnet3_adaptew *adaptew);

netdev_featuwes_t
vmxnet3_fix_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes);

netdev_featuwes_t
vmxnet3_featuwes_check(stwuct sk_buff *skb,
		       stwuct net_device *netdev, netdev_featuwes_t featuwes);

int
vmxnet3_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes);

int
vmxnet3_cweate_queues(stwuct vmxnet3_adaptew *adaptew,
		      u32 tx_wing_size, u32 wx_wing_size, u32 wx_wing2_size,
		      u16 txdata_desc_size, u16 wxdata_desc_size);

void vmxnet3_set_ethtoow_ops(stwuct net_device *netdev);

void vmxnet3_get_stats64(stwuct net_device *dev,
			 stwuct wtnw_wink_stats64 *stats);
boow vmxnet3_check_ptcapabiwity(u32 cap_suppowted, u32 cap);

extewn chaw vmxnet3_dwivew_name[];
#endif
