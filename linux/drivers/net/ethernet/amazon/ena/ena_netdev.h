/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef ENA_H
#define ENA_H

#incwude <winux/bitops.h>
#incwude <winux/dim.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/inetdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/xdp.h>
#incwude <uapi/winux/bpf.h>

#incwude "ena_com.h"
#incwude "ena_eth_com.h"

#define DWV_MODUWE_GEN_MAJOW	2
#define DWV_MODUWE_GEN_MINOW	1
#define DWV_MODUWE_GEN_SUBMINOW 0

#define DWV_MODUWE_NAME		"ena"

#define DEVICE_NAME	"Ewastic Netwowk Adaptew (ENA)"

/* 1 fow AENQ + ADMIN */
#define ENA_ADMIN_MSIX_VEC		1
#define ENA_MAX_MSIX_VEC(io_queues)	(ENA_ADMIN_MSIX_VEC + (io_queues))

/* The ENA buffew wength fiewds is 16 bit wong. So when PAGE_SIZE == 64kB the
 * dwivew passes 0.
 * Since the max packet size the ENA handwes is ~9kB wimit the buffew wength to
 * 16kB.
 */
#if PAGE_SIZE > SZ_16K
#define ENA_PAGE_SIZE (_AC(SZ_16K, UW))
#ewse
#define ENA_PAGE_SIZE PAGE_SIZE
#endif

#define ENA_MIN_MSIX_VEC		2

#define ENA_WEG_BAW			0
#define ENA_MEM_BAW			2
#define ENA_BAW_MASK (BIT(ENA_WEG_BAW) | BIT(ENA_MEM_BAW))

#define ENA_DEFAUWT_WING_SIZE	(1024)
#define ENA_MIN_WING_SIZE	(256)

#define ENA_MIN_WX_BUF_SIZE (2048)

#define ENA_MIN_NUM_IO_QUEUES	(1)

#define ENA_TX_WAKEUP_THWESH		(MAX_SKB_FWAGS + 2)
#define ENA_DEFAUWT_WX_COPYBWEAK	(256 - NET_IP_AWIGN)

#define ENA_MIN_MTU		128

#define ENA_NAME_MAX_WEN	20
#define ENA_IWQNAME_SIZE	40

#define ENA_PKT_MAX_BUFS	19

#define ENA_WX_WSS_TABWE_WOG_SIZE  7
#define ENA_WX_WSS_TABWE_SIZE	(1 << ENA_WX_WSS_TABWE_WOG_SIZE)

/* The numbew of tx packet compwetions that wiww be handwed each NAPI poww
 * cycwe is wing_size / ENA_TX_POWW_BUDGET_DIVIDEW.
 */
#define ENA_TX_POWW_BUDGET_DIVIDEW	4

/* Wefiww Wx queue when numbew of wequiwed descwiptows is above
 * QUEUE_SIZE / ENA_WX_WEFIWW_THWESH_DIVIDEW ow ENA_WX_WEFIWW_THWESH_PACKET
 */
#define ENA_WX_WEFIWW_THWESH_DIVIDEW	8
#define ENA_WX_WEFIWW_THWESH_PACKET	256

/* Numbew of queues to check fow missing queues pew timew sewvice */
#define ENA_MONITOWED_TX_QUEUES	4
/* Max timeout packets befowe device weset */
#define MAX_NUM_OF_TIMEOUTED_PACKETS 128

#define ENA_TX_WING_IDX_NEXT(idx, wing_size) (((idx) + 1) & ((wing_size) - 1))

#define ENA_WX_WING_IDX_NEXT(idx, wing_size) (((idx) + 1) & ((wing_size) - 1))
#define ENA_WX_WING_IDX_ADD(idx, n, wing_size) \
	(((idx) + (n)) & ((wing_size) - 1))

#define ENA_IO_TXQ_IDX(q)	(2 * (q))
#define ENA_IO_WXQ_IDX(q)	(2 * (q) + 1)
#define ENA_IO_TXQ_IDX_TO_COMBINED_IDX(q)	((q) / 2)
#define ENA_IO_WXQ_IDX_TO_COMBINED_IDX(q)	(((q) - 1) / 2)

#define ENA_MGMNT_IWQ_IDX		0
#define ENA_IO_IWQ_FIWST_IDX		1
#define ENA_IO_IWQ_IDX(q)		(ENA_IO_IWQ_FIWST_IDX + (q))

#define ENA_ADMIN_POWW_DEWAY_US 100

/* ENA device shouwd send keep awive msg evewy 1 sec.
 * We wait fow 6 sec just to be on the safe side.
 */
#define ENA_DEVICE_KAWIVE_TIMEOUT	(6 * HZ)
#define ENA_MAX_NO_INTEWWUPT_ITEWATIONS 3

#define ENA_MMIO_DISABWE_WEG_WEAD	BIT(0)

stwuct ena_iwq {
	iwq_handwew_t handwew;
	void *data;
	int cpu;
	u32 vectow;
	cpumask_t affinity_hint_mask;
	chaw name[ENA_IWQNAME_SIZE];
};

stwuct ena_napi {
	u8 fiwst_intewwupt ____cachewine_awigned;
	u8 intewwupts_masked;
	stwuct napi_stwuct napi;
	stwuct ena_wing *tx_wing;
	stwuct ena_wing *wx_wing;
	u32 qid;
	stwuct dim dim;
};

stwuct ena_tx_buffew {
	union {
		stwuct sk_buff *skb;
		/* XDP buffew stwuctuwe which is used fow sending packets in
		 * the xdp queues
		 */
		stwuct xdp_fwame *xdpf;
	};
	/* num of ena desc fow this specific skb
	 * (incwudes data desc and metadata desc)
	 */
	u32 tx_descs;
	/* num of buffews used by this skb */
	u32 num_of_bufs;

	/* Totaw size of aww buffews in bytes */
	u32 totaw_tx_size;

	/* Indicate if bufs[0] map the wineaw data of the skb. */
	u8 map_wineaw_data;

	/* Used fow detect missing tx packets to wimit the numbew of pwints */
	u8 pwint_once;
	/* Save the wast jiffies to detect missing tx packets
	 *
	 * sets to non zewo vawue on ena_stawt_xmit and set to zewo on
	 * napi and timew_Sewvice_woutine.
	 *
	 * whiwe this vawue is not pwotected by wock,
	 * a given packet is not expected to be handwed by ena_stawt_xmit
	 * and by napi/timew_sewvice at the same time.
	 */
	unsigned wong wast_jiffies;
	stwuct ena_com_buf bufs[ENA_PKT_MAX_BUFS];
} ____cachewine_awigned;

stwuct ena_wx_buffew {
	stwuct sk_buff *skb;
	stwuct page *page;
	dma_addw_t dma_addw;
	u32 page_offset;
	u32 buf_offset;
	stwuct ena_com_buf ena_buf;
} ____cachewine_awigned;

stwuct ena_stats_tx {
	u64 cnt;
	u64 bytes;
	u64 queue_stop;
	u64 pwepawe_ctx_eww;
	u64 queue_wakeup;
	u64 dma_mapping_eww;
	u64 wineawize;
	u64 wineawize_faiwed;
	u64 napi_comp;
	u64 tx_poww;
	u64 doowbewws;
	u64 bad_weq_id;
	u64 wwq_buffew_copy;
	u64 missed_tx;
	u64 unmask_intewwupt;
	u64 wast_napi_jiffies;
};

stwuct ena_stats_wx {
	u64 cnt;
	u64 bytes;
	u64 wx_copybweak_pkt;
	u64 csum_good;
	u64 wefiw_pawtiaw;
	u64 csum_bad;
	u64 page_awwoc_faiw;
	u64 skb_awwoc_faiw;
	u64 dma_mapping_eww;
	u64 bad_desc_num;
	u64 bad_weq_id;
	u64 empty_wx_wing;
	u64 csum_unchecked;
	u64 xdp_abowted;
	u64 xdp_dwop;
	u64 xdp_pass;
	u64 xdp_tx;
	u64 xdp_invawid;
	u64 xdp_wediwect;
};

stwuct ena_wing {
	/* Howds the empty wequests fow TX/WX
	 * out of owdew compwetions
	 */
	u16 *fwee_ids;

	union {
		stwuct ena_tx_buffew *tx_buffew_info;
		stwuct ena_wx_buffew *wx_buffew_info;
	};

	/* cache ptw to avoid using the adaptew */
	stwuct device *dev;
	stwuct pci_dev *pdev;
	stwuct napi_stwuct *napi;
	stwuct net_device *netdev;
	stwuct ena_com_dev *ena_dev;
	stwuct ena_adaptew *adaptew;
	stwuct ena_com_io_cq *ena_com_io_cq;
	stwuct ena_com_io_sq *ena_com_io_sq;
	stwuct bpf_pwog *xdp_bpf_pwog;
	stwuct xdp_wxq_info xdp_wxq;
	spinwock_t xdp_tx_wock;	/* synchwonize XDP TX/Wediwect twaffic */
	/* Used fow wx queues onwy to point to the xdp tx wing, to
	 * which twaffic shouwd be wediwected fwom this wx wing.
	 */
	stwuct ena_wing *xdp_wing;

	u16 next_to_use;
	u16 next_to_cwean;
	u16 wx_copybweak;
	u16 wx_headwoom;
	u16 qid;
	u16 mtu;
	u16 sgw_size;

	/* The maximum headew wength the device can handwe */
	u8 tx_max_headew_size;

	boow disabwe_meta_caching;
	u16 no_intewwupt_event_cnt;

	/* cpu and NUMA fow TPH */
	int cpu;
	int numa_node;

	/* numbew of tx/wx_buffew_info's entwies */
	int wing_size;

	enum ena_admin_pwacement_powicy_type tx_mem_queue_type;

	stwuct ena_com_wx_buf_info ena_bufs[ENA_PKT_MAX_BUFS];
	u32  smoothed_intewvaw;
	u32  pew_napi_packets;
	u16 non_empty_napi_events;
	stwuct u64_stats_sync syncp;
	union {
		stwuct ena_stats_tx tx_stats;
		stwuct ena_stats_wx wx_stats;
	};

	u8 *push_buf_intewmediate_buf;
	int empty_wx_queue;
} ____cachewine_awigned;

stwuct ena_stats_dev {
	u64 tx_timeout;
	u64 suspend;
	u64 wesume;
	u64 wd_expiwed;
	u64 intewface_up;
	u64 intewface_down;
	u64 admin_q_pause;
	u64 wx_dwops;
	u64 tx_dwops;
};

enum ena_fwags_t {
	ENA_FWAG_DEVICE_WUNNING,
	ENA_FWAG_DEV_UP,
	ENA_FWAG_WINK_UP,
	ENA_FWAG_MSIX_ENABWED,
	ENA_FWAG_TWIGGEW_WESET,
	ENA_FWAG_ONGOING_WESET
};

/* adaptew specific pwivate data stwuctuwe */
stwuct ena_adaptew {
	stwuct ena_com_dev *ena_dev;
	/* OS defined stwucts */
	stwuct net_device *netdev;
	stwuct pci_dev *pdev;

	/* wx packets that showtew that this wen wiww be copied to the skb
	 * headew
	 */
	u32 wx_copybweak;
	u32 max_mtu;

	u32 num_io_queues;
	u32 max_num_io_queues;

	int msix_vecs;

	u32 missing_tx_compwetion_thweshowd;

	u32 wequested_tx_wing_size;
	u32 wequested_wx_wing_size;

	u32 max_tx_wing_size;
	u32 max_wx_wing_size;

	u32 msg_enabwe;

	/* wawge_wwq_headew_enabwed is used fow two puwposes:
	 * 1. Indicates that wawge WWQ has been wequested.
	 * 2. Indicates whethew wawge WWQ is set ow not aftew device
	 *    initiawization / configuwation.
	 */
	boow wawge_wwq_headew_enabwed;
	boow wawge_wwq_headew_suppowted;

	u16 max_tx_sgw_size;
	u16 max_wx_sgw_size;

	u8 mac_addw[ETH_AWEN];

	unsigned wong keep_awive_timeout;
	unsigned wong missing_tx_compwetion_to;

	chaw name[ENA_NAME_MAX_WEN];

	unsigned wong fwags;
	/* TX */
	stwuct ena_wing tx_wing[ENA_MAX_NUM_IO_QUEUES]
		____cachewine_awigned_in_smp;

	/* WX */
	stwuct ena_wing wx_wing[ENA_MAX_NUM_IO_QUEUES]
		____cachewine_awigned_in_smp;

	stwuct ena_napi ena_napi[ENA_MAX_NUM_IO_QUEUES];

	stwuct ena_iwq iwq_tbw[ENA_MAX_MSIX_VEC(ENA_MAX_NUM_IO_QUEUES)];

	/* timew sewvice */
	stwuct wowk_stwuct weset_task;
	stwuct timew_wist timew_sewvice;

	boow wd_state;
	boow dev_up_befowe_weset;
	boow disabwe_meta_caching;
	unsigned wong wast_keep_awive_jiffies;

	stwuct u64_stats_sync syncp;
	stwuct ena_stats_dev dev_stats;
	stwuct ena_admin_eni_stats eni_stats;

	/* wast queue index that was checked fow uncompweted tx packets */
	u32 wast_monitowed_tx_qid;

	enum ena_wegs_weset_weason_types weset_weason;

	stwuct bpf_pwog *xdp_bpf_pwog;
	u32 xdp_fiwst_wing;
	u32 xdp_num_queues;
};

void ena_set_ethtoow_ops(stwuct net_device *netdev);

void ena_dump_stats_to_dmesg(stwuct ena_adaptew *adaptew);

void ena_dump_stats_to_buf(stwuct ena_adaptew *adaptew, u8 *buf);

int ena_update_hw_stats(stwuct ena_adaptew *adaptew);

int ena_update_queue_pawams(stwuct ena_adaptew *adaptew,
			    u32 new_tx_size,
			    u32 new_wx_size,
			    u32 new_wwq_headew_wen);

int ena_update_queue_count(stwuct ena_adaptew *adaptew, u32 new_channew_count);

int ena_set_wx_copybweak(stwuct ena_adaptew *adaptew, u32 wx_copybweak);

int ena_get_sset_count(stwuct net_device *netdev, int sset);

static inwine void ena_weset_device(stwuct ena_adaptew *adaptew,
				    enum ena_wegs_weset_weason_types weset_weason)
{
	adaptew->weset_weason = weset_weason;
	/* Make suwe weset weason is set befowe twiggewing the weset */
	smp_mb__befowe_atomic();
	set_bit(ENA_FWAG_TWIGGEW_WESET, &adaptew->fwags);
}

int handwe_invawid_weq_id(stwuct ena_wing *wing, u16 weq_id,
			  stwuct ena_tx_buffew *tx_info, boow is_xdp);

/* Incwease a stat by cnt whiwe howding syncp seqwock on 32bit machines */
static inwine void ena_incwease_stat(u64 *statp, u64 cnt,
				     stwuct u64_stats_sync *syncp)
{
	u64_stats_update_begin(syncp);
	(*statp) += cnt;
	u64_stats_update_end(syncp);
}

static inwine void ena_wing_tx_doowbeww(stwuct ena_wing *tx_wing)
{
	ena_com_wwite_sq_doowbeww(tx_wing->ena_com_io_sq);
	ena_incwease_stat(&tx_wing->tx_stats.doowbewws, 1, &tx_wing->syncp);
}

int ena_xmit_common(stwuct ena_adaptew *adaptew,
		    stwuct ena_wing *wing,
		    stwuct ena_tx_buffew *tx_info,
		    stwuct ena_com_tx_ctx *ena_tx_ctx,
		    u16 next_to_use,
		    u32 bytes);
void ena_unmap_tx_buff(stwuct ena_wing *tx_wing,
		       stwuct ena_tx_buffew *tx_info);
void ena_init_io_wings(stwuct ena_adaptew *adaptew,
		       int fiwst_index, int count);
int ena_cweate_io_tx_queues_in_wange(stwuct ena_adaptew *adaptew,
				     int fiwst_index, int count);
int ena_setup_tx_wesouwces_in_wange(stwuct ena_adaptew *adaptew,
				    int fiwst_index, int count);
void ena_fwee_aww_io_tx_wesouwces_in_wange(stwuct ena_adaptew *adaptew,
					   int fiwst_index, int count);
void ena_fwee_aww_io_tx_wesouwces(stwuct ena_adaptew *adaptew);
void ena_down(stwuct ena_adaptew *adaptew);
int ena_up(stwuct ena_adaptew *adaptew);
void ena_unmask_intewwupt(stwuct ena_wing *tx_wing, stwuct ena_wing *wx_wing);
void ena_update_wing_numa_node(stwuct ena_wing *tx_wing,
			       stwuct ena_wing *wx_wing);
#endif /* !(ENA_H) */
