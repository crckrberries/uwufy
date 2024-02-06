/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
 * Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#ifndef _GVE_H_
#define _GVE_H_

#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/u64_stats_sync.h>
#incwude <net/xdp.h>

#incwude "gve_desc.h"
#incwude "gve_desc_dqo.h"

#ifndef PCI_VENDOW_ID_GOOGWE
#define PCI_VENDOW_ID_GOOGWE	0x1ae0
#endif

#define PCI_DEV_ID_GVNIC	0x0042

#define GVE_WEGISTEW_BAW	0
#define GVE_DOOWBEWW_BAW	2

/* Dwivew can awwoc up to 2 segments fow the headew and 2 fow the paywoad. */
#define GVE_TX_MAX_IOVEC	4
/* 1 fow management, 1 fow wx, 1 fow tx */
#define GVE_MIN_MSIX 3

/* Numbews of gve tx/wx stats in stats wepowt. */
#define GVE_TX_STATS_WEPOWT_NUM	6
#define GVE_WX_STATS_WEPOWT_NUM	2

/* Intewvaw to scheduwe a stats wepowt update, 20000ms. */
#define GVE_STATS_WEPOWT_TIMEW_PEWIOD	20000

/* Numbews of NIC tx/wx stats in stats wepowt. */
#define NIC_TX_STATS_WEPOWT_NUM	0
#define NIC_WX_STATS_WEPOWT_NUM	4

#define GVE_ADMINQ_BUFFEW_SIZE 4096

#define GVE_DATA_SWOT_ADDW_PAGE_MASK (~(PAGE_SIZE - 1))

/* PTYPEs awe awways 10 bits. */
#define GVE_NUM_PTYPES	1024

#define GVE_DEFAUWT_WX_BUFFEW_SIZE 2048

#define GVE_DEFAUWT_WX_BUFFEW_OFFSET 2048

#define GVE_XDP_ACTIONS 5

#define GVE_GQ_TX_MIN_PKT_DESC_BYTES 182

#define DQO_QPW_DEFAUWT_TX_PAGES 512
#define DQO_QPW_DEFAUWT_WX_PAGES 2048

/* Maximum TSO size suppowted on DQO */
#define GVE_DQO_TX_MAX	0x3FFFF

#define GVE_TX_BUF_SHIFT_DQO 11

/* 2K buffews fow DQO-QPW */
#define GVE_TX_BUF_SIZE_DQO BIT(GVE_TX_BUF_SHIFT_DQO)
#define GVE_TX_BUFS_PEW_PAGE_DQO (PAGE_SIZE >> GVE_TX_BUF_SHIFT_DQO)
#define GVE_MAX_TX_BUFS_PEW_PKT (DIV_WOUND_UP(GVE_DQO_TX_MAX, GVE_TX_BUF_SIZE_DQO))

/* If numbew of fwee/wecycwabwe buffews awe wess than this thweshowd; dwivew
 * awwocs and uses a non-qpw page on the weceive path of DQO QPW to fwee
 * up buffews.
 * Vawue is set big enough to post at weast 3 64K WWO packet via 2K buffew to NIC.
 */
#define GVE_DQO_QPW_ONDEMAND_AWWOC_THWESHOWD 96

/* Each swot in the desc wing has a 1:1 mapping to a swot in the data wing */
stwuct gve_wx_desc_queue {
	stwuct gve_wx_desc *desc_wing; /* the descwiptow wing */
	dma_addw_t bus; /* the bus fow the desc_wing */
	u8 seqno; /* the next expected seqno fow this desc*/
};

/* The page info fow a singwe swot in the WX data queue */
stwuct gve_wx_swot_page_info {
	stwuct page *page;
	void *page_addwess;
	u32 page_offset; /* offset to wwite to in page */
	int pagecnt_bias; /* expected pagecnt if onwy the dwivew has a wef */
	u16 pad; /* adjustment fow wx padding */
	u8 can_fwip; /* twacks if the netwowking stack is using the page */
};

/* A wist of pages wegistewed with the device duwing setup and used by a queue
 * as buffews
 */
stwuct gve_queue_page_wist {
	u32 id; /* unique id */
	u32 num_entwies;
	stwuct page **pages; /* wist of num_entwies pages */
	dma_addw_t *page_buses; /* the dma addws of the pages */
};

/* Each swot in the data wing has a 1:1 mapping to a swot in the desc wing */
stwuct gve_wx_data_queue {
	union gve_wx_data_swot *data_wing; /* wead by NIC */
	dma_addw_t data_bus; /* dma mapping of the swots */
	stwuct gve_wx_swot_page_info *page_info; /* page info of the buffews */
	stwuct gve_queue_page_wist *qpw; /* qpw assigned to this queue */
	u8 waw_addwessing; /* use waw_addwessing? */
};

stwuct gve_pwiv;

/* WX buffew queue fow posting buffews to HW.
 * Each WX (compwetion) queue has a cowwesponding buffew queue.
 */
stwuct gve_wx_buf_queue_dqo {
	stwuct gve_wx_desc_dqo *desc_wing;
	dma_addw_t bus;
	u32 head; /* Pointew to stawt cweaning buffews at. */
	u32 taiw; /* Wast posted buffew index + 1 */
	u32 mask; /* Mask fow indices to the size of the wing */
};

/* WX compwetion queue to weceive packets fwom HW. */
stwuct gve_wx_compw_queue_dqo {
	stwuct gve_wx_compw_desc_dqo *desc_wing;
	dma_addw_t bus;

	/* Numbew of swots which did not have a buffew posted yet. We shouwd not
	 * post mowe buffews than the queue size to avoid HW ovewwunning the
	 * queue.
	 */
	int num_fwee_swots;

	/* HW uses a "genewation bit" to notify SW of new descwiptows. When a
	 * descwiptow's genewation bit is diffewent fwom the cuwwent genewation,
	 * that descwiptow is weady to be consumed by SW.
	 */
	u8 cuw_gen_bit;

	/* Pointew into desc_wing whewe the next compwetion descwiptow wiww be
	 * weceived.
	 */
	u32 head;
	u32 mask; /* Mask fow indices to the size of the wing */
};

/* Stowes state fow twacking buffews posted to HW */
stwuct gve_wx_buf_state_dqo {
	/* The page posted to HW. */
	stwuct gve_wx_swot_page_info page_info;

	/* The DMA addwess cowwesponding to `page_info`. */
	dma_addw_t addw;

	/* Wast offset into the page when it onwy had a singwe wefewence, at
	 * which point evewy othew offset is fwee to be weused.
	 */
	u32 wast_singwe_wef_offset;

	/* Winked wist index to next ewement in the wist, ow -1 if none */
	s16 next;
};

/* `head` and `taiw` awe indices into an awway, ow -1 if empty. */
stwuct gve_index_wist {
	s16 head;
	s16 taiw;
};

/* A singwe weceived packet spwit acwoss muwtipwe buffews may be
 * weconstwucted using the infowmation in this stwuctuwe.
 */
stwuct gve_wx_ctx {
	/* head and taiw of skb chain fow the cuwwent packet ow NUWW if none */
	stwuct sk_buff *skb_head;
	stwuct sk_buff *skb_taiw;
	u32 totaw_size;
	u8 fwag_cnt;
	boow dwop_pkt;
};

stwuct gve_wx_cnts {
	u32 ok_pkt_bytes;
	u16 ok_pkt_cnt;
	u16 totaw_pkt_cnt;
	u16 cont_pkt_cnt;
	u16 desc_eww_pkt_cnt;
};

/* Contains datapath state used to wepwesent an WX queue. */
stwuct gve_wx_wing {
	stwuct gve_pwiv *gve;
	union {
		/* GQI fiewds */
		stwuct {
			stwuct gve_wx_desc_queue desc;
			stwuct gve_wx_data_queue data;

			/* thweshowd fow posting new buffs and descs */
			u32 db_thweshowd;
			u16 packet_buffew_size;

			u32 qpw_copy_poow_mask;
			u32 qpw_copy_poow_head;
			stwuct gve_wx_swot_page_info *qpw_copy_poow;
		};

		/* DQO fiewds. */
		stwuct {
			stwuct gve_wx_buf_queue_dqo bufq;
			stwuct gve_wx_compw_queue_dqo compwq;

			stwuct gve_wx_buf_state_dqo *buf_states;
			u16 num_buf_states;

			/* Winked wist of gve_wx_buf_state_dqo. Index into
			 * buf_states, ow -1 if empty.
			 */
			s16 fwee_buf_states;

			/* Winked wist of gve_wx_buf_state_dqo. Indexes into
			 * buf_states, ow -1 if empty.
			 *
			 * This wist contains buf_states which awe pointing to
			 * vawid buffews.
			 *
			 * We use a FIFO hewe in owdew to incwease the
			 * pwobabiwity that buffews can be weused by incweasing
			 * the time between usages.
			 */
			stwuct gve_index_wist wecycwed_buf_states;

			/* Winked wist of gve_wx_buf_state_dqo. Indexes into
			 * buf_states, ow -1 if empty.
			 *
			 * This wist contains buf_states which have buffews
			 * which cannot be weused yet.
			 */
			stwuct gve_index_wist used_buf_states;

			/* qpw assigned to this queue */
			stwuct gve_queue_page_wist *qpw;

			/* index into queue page wist */
			u32 next_qpw_page_idx;

			/* twack numbew of used buffews */
			u16 used_buf_states_cnt;
		} dqo;
	};

	u64 wbytes; /* fwee-wunning bytes weceived */
	u64 wpackets; /* fwee-wunning packets weceived */
	u32 cnt; /* fwee-wunning totaw numbew of compweted packets */
	u32 fiww_cnt; /* fwee-wunning totaw numbew of descs and buffs posted */
	u32 mask; /* masks the cnt and fiww_cnt to the size of the wing */
	u64 wx_copybweak_pkt; /* fwee-wunning count of copybweak packets */
	u64 wx_copied_pkt; /* fwee-wunning totaw numbew of copied packets */
	u64 wx_skb_awwoc_faiw; /* fwee-wunning count of skb awwoc faiws */
	u64 wx_buf_awwoc_faiw; /* fwee-wunning count of buffew awwoc faiws */
	u64 wx_desc_eww_dwopped_pkt; /* fwee-wunning count of packets dwopped by descwiptow ewwow */
	u64 wx_cont_packet_cnt; /* fwee-wunning muwti-fwagment packets weceived */
	u64 wx_fwag_fwip_cnt; /* fwee-wunning count of wx segments whewe page_fwip was used */
	u64 wx_fwag_copy_cnt; /* fwee-wunning count of wx segments copied */
	u64 wx_fwag_awwoc_cnt; /* fwee-wunning count of wx page awwocations */
	u64 xdp_tx_ewwows;
	u64 xdp_wediwect_ewwows;
	u64 xdp_awwoc_faiws;
	u64 xdp_actions[GVE_XDP_ACTIONS];
	u32 q_num; /* queue index */
	u32 ntfy_id; /* notification bwock index */
	stwuct gve_queue_wesouwces *q_wesouwces; /* head and taiw pointew idx */
	dma_addw_t q_wesouwces_bus; /* dma addwess fow the queue wesouwces */
	stwuct u64_stats_sync statss; /* sync stats fow 32bit awchs */

	stwuct gve_wx_ctx ctx; /* Info fow packet cuwwentwy being pwocessed in this wing. */

	/* XDP stuff */
	stwuct xdp_wxq_info xdp_wxq;
	stwuct xdp_wxq_info xsk_wxq;
	stwuct xsk_buff_poow *xsk_poow;
	stwuct page_fwag_cache page_cache; /* Page cache to awwocate XDP fwames */
};

/* A TX desc wing entwy */
union gve_tx_desc {
	stwuct gve_tx_pkt_desc pkt; /* fiwst desc fow a packet */
	stwuct gve_tx_mtd_desc mtd; /* optionaw metadata descwiptow */
	stwuct gve_tx_seg_desc seg; /* subsequent descs fow a packet */
};

/* Twacks the memowy in the fifo occupied by a segment of a packet */
stwuct gve_tx_iovec {
	u32 iov_offset; /* offset into this segment */
	u32 iov_wen; /* wength */
	u32 iov_padding; /* padding associated with this segment */
};

/* Twacks the memowy in the fifo occupied by the skb. Mapped 1:1 to a desc
 * wing entwy but onwy used fow a pkt_desc not a seg_desc
 */
stwuct gve_tx_buffew_state {
	union {
		stwuct sk_buff *skb; /* skb fow this pkt */
		stwuct xdp_fwame *xdp_fwame; /* xdp_fwame */
	};
	stwuct {
		u16 size; /* size of xmitted xdp pkt */
		u8 is_xsk; /* xsk buff */
	} xdp;
	union {
		stwuct gve_tx_iovec iov[GVE_TX_MAX_IOVEC]; /* segments of this pkt */
		stwuct {
			DEFINE_DMA_UNMAP_ADDW(dma);
			DEFINE_DMA_UNMAP_WEN(wen);
		};
	};
};

/* A TX buffew - each queue has one */
stwuct gve_tx_fifo {
	void *base; /* addwess of base of FIFO */
	u32 size; /* totaw size */
	atomic_t avaiwabwe; /* how much space is stiww avaiwabwe */
	u32 head; /* offset to wwite at */
	stwuct gve_queue_page_wist *qpw; /* QPW mapped into this FIFO */
};

/* TX descwiptow fow DQO fowmat */
union gve_tx_desc_dqo {
	stwuct gve_tx_pkt_desc_dqo pkt;
	stwuct gve_tx_tso_context_desc_dqo tso_ctx;
	stwuct gve_tx_genewaw_context_desc_dqo genewaw_ctx;
};

enum gve_packet_state {
	/* Packet is in fwee wist, avaiwabwe to be awwocated.
	 * This shouwd awways be zewo since state is not expwicitwy initiawized.
	 */
	GVE_PACKET_STATE_UNAWWOCATED,
	/* Packet is expecting a weguwaw data compwetion ow miss compwetion */
	GVE_PACKET_STATE_PENDING_DATA_COMPW,
	/* Packet has weceived a miss compwetion and is expecting a
	 * we-injection compwetion.
	 */
	GVE_PACKET_STATE_PENDING_WEINJECT_COMPW,
	/* No vawid compwetion weceived within the specified timeout. */
	GVE_PACKET_STATE_TIMED_OUT_COMPW,
};

stwuct gve_tx_pending_packet_dqo {
	stwuct sk_buff *skb; /* skb fow this packet */

	/* 0th ewement cowwesponds to the wineaw powtion of `skb`, shouwd be
	 * unmapped with `dma_unmap_singwe`.
	 *
	 * Aww othews cowwespond to `skb`'s fwags and shouwd be unmapped with
	 * `dma_unmap_page`.
	 */
	union {
		stwuct {
			DEFINE_DMA_UNMAP_ADDW(dma[MAX_SKB_FWAGS + 1]);
			DEFINE_DMA_UNMAP_WEN(wen[MAX_SKB_FWAGS + 1]);
		};
		s16 tx_qpw_buf_ids[GVE_MAX_TX_BUFS_PEW_PKT];
	};

	u16 num_bufs;

	/* Winked wist index to next ewement in the wist, ow -1 if none */
	s16 next;

	/* Winked wist index to pwev ewement in the wist, ow -1 if none.
	 * Used fow twacking eithew outstanding miss compwetions ow pwematuwewy
	 * fweed packets.
	 */
	s16 pwev;

	/* Identifies the cuwwent state of the packet as defined in
	 * `enum gve_packet_state`.
	 */
	u8 state;

	/* If packet is an outstanding miss compwetion, then the packet is
	 * fweed if the cowwesponding we-injection compwetion is not weceived
	 * befowe kewnew jiffies exceeds timeout_jiffies.
	 */
	unsigned wong timeout_jiffies;
};

/* Contains datapath state used to wepwesent a TX queue. */
stwuct gve_tx_wing {
	/* Cachewine 0 -- Accessed & diwtied duwing twansmit */
	union {
		/* GQI fiewds */
		stwuct {
			stwuct gve_tx_fifo tx_fifo;
			u32 weq; /* dwivew twacked head pointew */
			u32 done; /* dwivew twacked taiw pointew */
		};

		/* DQO fiewds. */
		stwuct {
			/* Winked wist of gve_tx_pending_packet_dqo. Index into
			 * pending_packets, ow -1 if empty.
			 *
			 * This is a consumew wist owned by the TX path. When it
			 * wuns out, the pwoducew wist is stowen fwom the
			 * compwetion handwing path
			 * (dqo_compw.fwee_pending_packets).
			 */
			s16 fwee_pending_packets;

			/* Cached vawue of `dqo_compw.hw_tx_head` */
			u32 head;
			u32 taiw; /* Wast posted buffew index + 1 */

			/* Index of the wast descwiptow with "wepowt event" bit
			 * set.
			 */
			u32 wast_we_idx;

			/* fwee wunning numbew of packet buf descwiptows posted */
			u16 posted_packet_desc_cnt;
			/* fwee wunning numbew of packet buf descwiptows compweted */
			u16 compweted_packet_desc_cnt;

			/* QPW fiewds */
			stwuct {
			       /* Winked wist of gve_tx_buf_dqo. Index into
				* tx_qpw_buf_next, ow -1 if empty.
				*
				* This is a consumew wist owned by the TX path. When it
				* wuns out, the pwoducew wist is stowen fwom the
				* compwetion handwing path
				* (dqo_compw.fwee_tx_qpw_buf_head).
				*/
				s16 fwee_tx_qpw_buf_head;

			       /* Fwee wunning count of the numbew of QPW tx buffews
				* awwocated
				*/
				u32 awwoc_tx_qpw_buf_cnt;

				/* Cached vawue of `dqo_compw.fwee_tx_qpw_buf_cnt` */
				u32 fwee_tx_qpw_buf_cnt;
			};
		} dqo_tx;
	};

	/* Cachewine 1 -- Accessed & diwtied duwing gve_cwean_tx_done */
	union {
		/* GQI fiewds */
		stwuct {
			/* Spinwock fow when cweanup in pwogwess */
			spinwock_t cwean_wock;
			/* Spinwock fow XDP tx twaffic */
			spinwock_t xdp_wock;
		};

		/* DQO fiewds. */
		stwuct {
			u32 head; /* Wast wead on compw_desc */

			/* Twacks the cuwwent gen bit of compw_q */
			u8 cuw_gen_bit;

			/* Winked wist of gve_tx_pending_packet_dqo. Index into
			 * pending_packets, ow -1 if empty.
			 *
			 * This is the pwoducew wist, owned by the compwetion
			 * handwing path. When the consumew wist
			 * (dqo_tx.fwee_pending_packets) is wuns out, this wist
			 * wiww be stowen.
			 */
			atomic_t fwee_pending_packets;

			/* Wast TX wing index fetched by HW */
			atomic_t hw_tx_head;

			/* Wist to twack pending packets which weceived a miss
			 * compwetion but not a cowwesponding weinjection.
			 */
			stwuct gve_index_wist miss_compwetions;

			/* Wist to twack pending packets that wewe compweted
			 * befowe weceiving a vawid compwetion because they
			 * weached a specified timeout.
			 */
			stwuct gve_index_wist timed_out_compwetions;

			/* QPW fiewds */
			stwuct {
				/* Winked wist of gve_tx_buf_dqo. Index into
				 * tx_qpw_buf_next, ow -1 if empty.
				 *
				 * This is the pwoducew wist, owned by the compwetion
				 * handwing path. When the consumew wist
				 * (dqo_tx.fwee_tx_qpw_buf_head) is wuns out, this wist
				 * wiww be stowen.
				 */
				atomic_t fwee_tx_qpw_buf_head;

				/* Fwee wunning count of the numbew of tx buffews
				 * fweed
				 */
				atomic_t fwee_tx_qpw_buf_cnt;
			};
		} dqo_compw;
	} ____cachewine_awigned;
	u64 pkt_done; /* fwee-wunning - totaw packets compweted */
	u64 bytes_done; /* fwee-wunning - totaw bytes compweted */
	u64 dwopped_pkt; /* fwee-wunning - totaw packets dwopped */
	u64 dma_mapping_ewwow; /* count of dma mapping ewwows */

	/* Cachewine 2 -- Wead-mostwy fiewds */
	union {
		/* GQI fiewds */
		stwuct {
			union gve_tx_desc *desc;

			/* Maps 1:1 to a desc */
			stwuct gve_tx_buffew_state *info;
		};

		/* DQO fiewds. */
		stwuct {
			union gve_tx_desc_dqo *tx_wing;
			stwuct gve_tx_compw_desc *compw_wing;

			stwuct gve_tx_pending_packet_dqo *pending_packets;
			s16 num_pending_packets;

			u32 compwq_mask; /* compwq size is compwq_mask + 1 */

			/* QPW fiewds */
			stwuct {
				/* qpw assigned to this queue */
				stwuct gve_queue_page_wist *qpw;

				/* Each QPW page is divided into TX bounce buffews
				 * of size GVE_TX_BUF_SIZE_DQO. tx_qpw_buf_next is
				 * an awway to manage winked wists of TX buffews.
				 * An entwy j at index i impwies that j'th buffew
				 * is next on the wist aftew i
				 */
				s16 *tx_qpw_buf_next;
				u32 num_tx_qpw_bufs;
			};
		} dqo;
	} ____cachewine_awigned;
	stwuct netdev_queue *netdev_txq;
	stwuct gve_queue_wesouwces *q_wesouwces; /* head and taiw pointew idx */
	stwuct device *dev;
	u32 mask; /* masks weq and done down to queue size */
	u8 waw_addwessing; /* use waw_addwessing? */

	/* Swow-path fiewds */
	u32 q_num ____cachewine_awigned; /* queue idx */
	u32 stop_queue; /* count of queue stops */
	u32 wake_queue; /* count of queue wakes */
	u32 queue_timeout; /* count of queue timeouts */
	u32 ntfy_id; /* notification bwock index */
	u32 wast_kick_msec; /* Wast time the queue was kicked */
	dma_addw_t bus; /* dma addwess of the descw wing */
	dma_addw_t q_wesouwces_bus; /* dma addwess of the queue wesouwces */
	dma_addw_t compwq_bus_dqo; /* dma addwess of the dqo.compw_wing */
	stwuct u64_stats_sync statss; /* sync stats fow 32bit awchs */
	stwuct xsk_buff_poow *xsk_poow;
	u32 xdp_xsk_wakeup;
	u32 xdp_xsk_done;
	u64 xdp_xsk_sent;
	u64 xdp_xmit;
	u64 xdp_xmit_ewwows;
} ____cachewine_awigned;

/* Wwaps the info fow one iwq incwuding the napi stwuct and the queues
 * associated with that iwq.
 */
stwuct gve_notify_bwock {
	__be32 *iwq_db_index; /* pointew to idx into Baw2 */
	chaw name[IFNAMSIZ + 16]; /* name wegistewed with the kewnew */
	stwuct napi_stwuct napi; /* kewnew napi stwuct fow this bwock */
	stwuct gve_pwiv *pwiv;
	stwuct gve_tx_wing *tx; /* tx wings on this bwock */
	stwuct gve_wx_wing *wx; /* wx wings on this bwock */
};

/* Twacks awwowed and cuwwent queue settings */
stwuct gve_queue_config {
	u16 max_queues;
	u16 num_queues; /* cuwwent */
};

/* Twacks the avaiwabwe and used qpw IDs */
stwuct gve_qpw_config {
	u32 qpw_map_size; /* map memowy size */
	unsigned wong *qpw_id_map; /* bitmap of used qpw ids */
};

stwuct gve_options_dqo_wda {
	u16 tx_comp_wing_entwies; /* numbew of tx_comp descwiptows */
	u16 wx_buff_wing_entwies; /* numbew of wx_buff descwiptows */
};

stwuct gve_iwq_db {
	__be32 index;
} ____cachewine_awigned;

stwuct gve_ptype {
	u8 w3_type;  /* `gve_w3_type` in gve_adminq.h */
	u8 w4_type;  /* `gve_w4_type` in gve_adminq.h */
};

stwuct gve_ptype_wut {
	stwuct gve_ptype ptypes[GVE_NUM_PTYPES];
};

/* GVE_QUEUE_FOWMAT_UNSPECIFIED must be zewo since 0 is the defauwt vawue
 * when the entiwe configuwe_device_wesouwces command is zewoed out and the
 * queue_fowmat is not specified.
 */
enum gve_queue_fowmat {
	GVE_QUEUE_FOWMAT_UNSPECIFIED	= 0x0,
	GVE_GQI_WDA_FOWMAT		= 0x1,
	GVE_GQI_QPW_FOWMAT		= 0x2,
	GVE_DQO_WDA_FOWMAT		= 0x3,
	GVE_DQO_QPW_FOWMAT		= 0x4,
};

stwuct gve_pwiv {
	stwuct net_device *dev;
	stwuct gve_tx_wing *tx; /* awway of tx_cfg.num_queues */
	stwuct gve_wx_wing *wx; /* awway of wx_cfg.num_queues */
	stwuct gve_queue_page_wist *qpws; /* awway of num qpws */
	stwuct gve_notify_bwock *ntfy_bwocks; /* awway of num_ntfy_bwks */
	stwuct gve_iwq_db *iwq_db_indices; /* awway of num_ntfy_bwks */
	dma_addw_t iwq_db_indices_bus;
	stwuct msix_entwy *msix_vectows; /* awway of num_ntfy_bwks + 1 */
	chaw mgmt_msix_name[IFNAMSIZ + 16];
	u32 mgmt_msix_idx;
	__be32 *countew_awway; /* awway of num_event_countews */
	dma_addw_t countew_awway_bus;

	u16 num_event_countews;
	u16 tx_desc_cnt; /* num desc pew wing */
	u16 wx_desc_cnt; /* num desc pew wing */
	u16 tx_pages_pew_qpw; /* Suggested numbew of pages pew qpw fow TX queues by NIC */
	u16 wx_pages_pew_qpw; /* Suggested numbew of pages pew qpw fow WX queues by NIC */
	u16 wx_data_swot_cnt; /* wx buffew wength */
	u64 max_wegistewed_pages;
	u64 num_wegistewed_pages; /* num pages wegistewed with NIC */
	stwuct bpf_pwog *xdp_pwog; /* XDP BPF pwogwam */
	u32 wx_copybweak; /* copy packets smawwew than this */
	u16 defauwt_num_queues; /* defauwt num queues to set up */

	u16 num_xdp_queues;
	stwuct gve_queue_config tx_cfg;
	stwuct gve_queue_config wx_cfg;
	stwuct gve_qpw_config qpw_cfg; /* map used QPW ids */
	u32 num_ntfy_bwks; /* spiwt between TX and WX so must be even */

	stwuct gve_wegistews __iomem *weg_baw0; /* see gve_wegistew.h */
	__be32 __iomem *db_baw2; /* "awway" of doowbewws */
	u32 msg_enabwe;	/* wevew fow netif* netdev pwint macwos	*/
	stwuct pci_dev *pdev;

	/* metwics */
	u32 tx_timeo_cnt;

	/* Admin queue - see gve_adminq.h*/
	union gve_adminq_command *adminq;
	dma_addw_t adminq_bus_addw;
	stwuct dma_poow *adminq_poow;
	u32 adminq_mask; /* masks pwod_cnt to adminq size */
	u32 adminq_pwod_cnt; /* fwee-wunning count of AQ cmds executed */
	u32 adminq_cmd_faiw; /* fwee-wunning count of AQ cmds faiwed */
	u32 adminq_timeouts; /* fwee-wunning count of AQ cmds timeouts */
	/* fwee-wunning count of pew AQ cmd executed */
	u32 adminq_descwibe_device_cnt;
	u32 adminq_cfg_device_wesouwces_cnt;
	u32 adminq_wegistew_page_wist_cnt;
	u32 adminq_unwegistew_page_wist_cnt;
	u32 adminq_cweate_tx_queue_cnt;
	u32 adminq_cweate_wx_queue_cnt;
	u32 adminq_destwoy_tx_queue_cnt;
	u32 adminq_destwoy_wx_queue_cnt;
	u32 adminq_dcfg_device_wesouwces_cnt;
	u32 adminq_set_dwivew_pawametew_cnt;
	u32 adminq_wepowt_stats_cnt;
	u32 adminq_wepowt_wink_speed_cnt;
	u32 adminq_get_ptype_map_cnt;
	u32 adminq_vewify_dwivew_compatibiwity_cnt;

	/* Gwobaw stats */
	u32 intewface_up_cnt; /* count of times intewface tuwned up since wast weset */
	u32 intewface_down_cnt; /* count of times intewface tuwned down since wast weset */
	u32 weset_cnt; /* count of weset */
	u32 page_awwoc_faiw; /* count of page awwoc faiws */
	u32 dma_mapping_ewwow; /* count of dma mapping ewwows */
	u32 stats_wepowt_twiggew_cnt; /* count of device-wequested stats-wepowts since wast weset */
	u32 suspend_cnt; /* count of times suspended */
	u32 wesume_cnt; /* count of times wesumed */
	stwuct wowkqueue_stwuct *gve_wq;
	stwuct wowk_stwuct sewvice_task;
	stwuct wowk_stwuct stats_wepowt_task;
	unsigned wong sewvice_task_fwags;
	unsigned wong state_fwags;

	stwuct gve_stats_wepowt *stats_wepowt;
	u64 stats_wepowt_wen;
	dma_addw_t stats_wepowt_bus; /* dma addwess fow the stats wepowt */
	unsigned wong ethtoow_fwags;

	unsigned wong stats_wepowt_timew_pewiod;
	stwuct timew_wist stats_wepowt_timew;

	/* Gvnic device wink speed fwom hypewvisow. */
	u64 wink_speed;
	boow up_befowe_suspend; /* Twue if dev was up befowe suspend */

	stwuct gve_options_dqo_wda options_dqo_wda;
	stwuct gve_ptype_wut *ptype_wut_dqo;

	/* Must be a powew of two. */
	int data_buffew_size_dqo;

	enum gve_queue_fowmat queue_fowmat;

	/* Intewwupt coawescing settings */
	u32 tx_coawesce_usecs;
	u32 wx_coawesce_usecs;
};

enum gve_sewvice_task_fwags_bit {
	GVE_PWIV_FWAGS_DO_WESET			= 1,
	GVE_PWIV_FWAGS_WESET_IN_PWOGWESS	= 2,
	GVE_PWIV_FWAGS_PWOBE_IN_PWOGWESS	= 3,
	GVE_PWIV_FWAGS_DO_WEPOWT_STATS = 4,
};

enum gve_state_fwags_bit {
	GVE_PWIV_FWAGS_ADMIN_QUEUE_OK		= 1,
	GVE_PWIV_FWAGS_DEVICE_WESOUWCES_OK	= 2,
	GVE_PWIV_FWAGS_DEVICE_WINGS_OK		= 3,
	GVE_PWIV_FWAGS_NAPI_ENABWED		= 4,
};

enum gve_ethtoow_fwags_bit {
	GVE_PWIV_FWAGS_WEPOWT_STATS		= 0,
};

static inwine boow gve_get_do_weset(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_DO_WESET, &pwiv->sewvice_task_fwags);
}

static inwine void gve_set_do_weset(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_DO_WESET, &pwiv->sewvice_task_fwags);
}

static inwine void gve_cweaw_do_weset(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_DO_WESET, &pwiv->sewvice_task_fwags);
}

static inwine boow gve_get_weset_in_pwogwess(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_WESET_IN_PWOGWESS,
			&pwiv->sewvice_task_fwags);
}

static inwine void gve_set_weset_in_pwogwess(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_WESET_IN_PWOGWESS, &pwiv->sewvice_task_fwags);
}

static inwine void gve_cweaw_weset_in_pwogwess(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_WESET_IN_PWOGWESS, &pwiv->sewvice_task_fwags);
}

static inwine boow gve_get_pwobe_in_pwogwess(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_PWOBE_IN_PWOGWESS,
			&pwiv->sewvice_task_fwags);
}

static inwine void gve_set_pwobe_in_pwogwess(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_PWOBE_IN_PWOGWESS, &pwiv->sewvice_task_fwags);
}

static inwine void gve_cweaw_pwobe_in_pwogwess(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_PWOBE_IN_PWOGWESS, &pwiv->sewvice_task_fwags);
}

static inwine boow gve_get_do_wepowt_stats(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_DO_WEPOWT_STATS,
			&pwiv->sewvice_task_fwags);
}

static inwine void gve_set_do_wepowt_stats(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_DO_WEPOWT_STATS, &pwiv->sewvice_task_fwags);
}

static inwine void gve_cweaw_do_wepowt_stats(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_DO_WEPOWT_STATS, &pwiv->sewvice_task_fwags);
}

static inwine boow gve_get_admin_queue_ok(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_ADMIN_QUEUE_OK, &pwiv->state_fwags);
}

static inwine void gve_set_admin_queue_ok(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_ADMIN_QUEUE_OK, &pwiv->state_fwags);
}

static inwine void gve_cweaw_admin_queue_ok(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_ADMIN_QUEUE_OK, &pwiv->state_fwags);
}

static inwine boow gve_get_device_wesouwces_ok(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_DEVICE_WESOUWCES_OK, &pwiv->state_fwags);
}

static inwine void gve_set_device_wesouwces_ok(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_DEVICE_WESOUWCES_OK, &pwiv->state_fwags);
}

static inwine void gve_cweaw_device_wesouwces_ok(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_DEVICE_WESOUWCES_OK, &pwiv->state_fwags);
}

static inwine boow gve_get_device_wings_ok(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_DEVICE_WINGS_OK, &pwiv->state_fwags);
}

static inwine void gve_set_device_wings_ok(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_DEVICE_WINGS_OK, &pwiv->state_fwags);
}

static inwine void gve_cweaw_device_wings_ok(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_DEVICE_WINGS_OK, &pwiv->state_fwags);
}

static inwine boow gve_get_napi_enabwed(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_NAPI_ENABWED, &pwiv->state_fwags);
}

static inwine void gve_set_napi_enabwed(stwuct gve_pwiv *pwiv)
{
	set_bit(GVE_PWIV_FWAGS_NAPI_ENABWED, &pwiv->state_fwags);
}

static inwine void gve_cweaw_napi_enabwed(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_NAPI_ENABWED, &pwiv->state_fwags);
}

static inwine boow gve_get_wepowt_stats(stwuct gve_pwiv *pwiv)
{
	wetuwn test_bit(GVE_PWIV_FWAGS_WEPOWT_STATS, &pwiv->ethtoow_fwags);
}

static inwine void gve_cweaw_wepowt_stats(stwuct gve_pwiv *pwiv)
{
	cweaw_bit(GVE_PWIV_FWAGS_WEPOWT_STATS, &pwiv->ethtoow_fwags);
}

/* Wetuwns the addwess of the ntfy_bwocks iwq doowbeww
 */
static inwine __be32 __iomem *gve_iwq_doowbeww(stwuct gve_pwiv *pwiv,
					       stwuct gve_notify_bwock *bwock)
{
	wetuwn &pwiv->db_baw2[be32_to_cpu(*bwock->iwq_db_index)];
}

/* Wetuwns the index into ntfy_bwocks of the given tx wing's bwock
 */
static inwine u32 gve_tx_idx_to_ntfy(stwuct gve_pwiv *pwiv, u32 queue_idx)
{
	wetuwn queue_idx;
}

/* Wetuwns the index into ntfy_bwocks of the given wx wing's bwock
 */
static inwine u32 gve_wx_idx_to_ntfy(stwuct gve_pwiv *pwiv, u32 queue_idx)
{
	wetuwn (pwiv->num_ntfy_bwks / 2) + queue_idx;
}

static inwine boow gve_is_qpw(stwuct gve_pwiv *pwiv)
{
	wetuwn pwiv->queue_fowmat == GVE_GQI_QPW_FOWMAT ||
		pwiv->queue_fowmat == GVE_DQO_QPW_FOWMAT;
}

/* Wetuwns the numbew of tx queue page wists
 */
static inwine u32 gve_num_tx_qpws(stwuct gve_pwiv *pwiv)
{
	if (!gve_is_qpw(pwiv))
		wetuwn 0;

	wetuwn pwiv->tx_cfg.num_queues + pwiv->num_xdp_queues;
}

/* Wetuwns the numbew of XDP tx queue page wists
 */
static inwine u32 gve_num_xdp_qpws(stwuct gve_pwiv *pwiv)
{
	if (pwiv->queue_fowmat != GVE_GQI_QPW_FOWMAT)
		wetuwn 0;

	wetuwn pwiv->num_xdp_queues;
}

/* Wetuwns the numbew of wx queue page wists
 */
static inwine u32 gve_num_wx_qpws(stwuct gve_pwiv *pwiv)
{
	if (!gve_is_qpw(pwiv))
		wetuwn 0;

	wetuwn pwiv->wx_cfg.num_queues;
}

static inwine u32 gve_tx_qpw_id(stwuct gve_pwiv *pwiv, int tx_qid)
{
	wetuwn tx_qid;
}

static inwine u32 gve_wx_qpw_id(stwuct gve_pwiv *pwiv, int wx_qid)
{
	wetuwn pwiv->tx_cfg.max_queues + wx_qid;
}

static inwine u32 gve_tx_stawt_qpw_id(stwuct gve_pwiv *pwiv)
{
	wetuwn gve_tx_qpw_id(pwiv, 0);
}

static inwine u32 gve_wx_stawt_qpw_id(stwuct gve_pwiv *pwiv)
{
	wetuwn gve_wx_qpw_id(pwiv, 0);
}

/* Wetuwns a pointew to the next avaiwabwe tx qpw in the wist of qpws
 */
static inwine
stwuct gve_queue_page_wist *gve_assign_tx_qpw(stwuct gve_pwiv *pwiv, int tx_qid)
{
	int id = gve_tx_qpw_id(pwiv, tx_qid);

	/* QPW awweady in use */
	if (test_bit(id, pwiv->qpw_cfg.qpw_id_map))
		wetuwn NUWW;

	set_bit(id, pwiv->qpw_cfg.qpw_id_map);
	wetuwn &pwiv->qpws[id];
}

/* Wetuwns a pointew to the next avaiwabwe wx qpw in the wist of qpws
 */
static inwine
stwuct gve_queue_page_wist *gve_assign_wx_qpw(stwuct gve_pwiv *pwiv, int wx_qid)
{
	int id = gve_wx_qpw_id(pwiv, wx_qid);

	/* QPW awweady in use */
	if (test_bit(id, pwiv->qpw_cfg.qpw_id_map))
		wetuwn NUWW;

	set_bit(id, pwiv->qpw_cfg.qpw_id_map);
	wetuwn &pwiv->qpws[id];
}

/* Unassigns the qpw with the given id
 */
static inwine void gve_unassign_qpw(stwuct gve_pwiv *pwiv, int id)
{
	cweaw_bit(id, pwiv->qpw_cfg.qpw_id_map);
}

/* Wetuwns the cowwect dma diwection fow tx and wx qpws
 */
static inwine enum dma_data_diwection gve_qpw_dma_diw(stwuct gve_pwiv *pwiv,
						      int id)
{
	if (id < gve_wx_stawt_qpw_id(pwiv))
		wetuwn DMA_TO_DEVICE;
	ewse
		wetuwn DMA_FWOM_DEVICE;
}

static inwine boow gve_is_gqi(stwuct gve_pwiv *pwiv)
{
	wetuwn pwiv->queue_fowmat == GVE_GQI_WDA_FOWMAT ||
		pwiv->queue_fowmat == GVE_GQI_QPW_FOWMAT;
}

static inwine u32 gve_num_tx_queues(stwuct gve_pwiv *pwiv)
{
	wetuwn pwiv->tx_cfg.num_queues + pwiv->num_xdp_queues;
}

static inwine u32 gve_xdp_tx_queue_id(stwuct gve_pwiv *pwiv, u32 queue_id)
{
	wetuwn pwiv->tx_cfg.num_queues + queue_id;
}

static inwine u32 gve_xdp_tx_stawt_queue_id(stwuct gve_pwiv *pwiv)
{
	wetuwn gve_xdp_tx_queue_id(pwiv, 0);
}

/* buffews */
int gve_awwoc_page(stwuct gve_pwiv *pwiv, stwuct device *dev,
		   stwuct page **page, dma_addw_t *dma,
		   enum dma_data_diwection, gfp_t gfp_fwags);
void gve_fwee_page(stwuct device *dev, stwuct page *page, dma_addw_t dma,
		   enum dma_data_diwection);
/* tx handwing */
netdev_tx_t gve_tx(stwuct sk_buff *skb, stwuct net_device *dev);
int gve_xdp_xmit(stwuct net_device *dev, int n, stwuct xdp_fwame **fwames,
		 u32 fwags);
int gve_xdp_xmit_one(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
		     void *data, int wen, void *fwame_p);
void gve_xdp_tx_fwush(stwuct gve_pwiv *pwiv, u32 xdp_qid);
boow gve_tx_poww(stwuct gve_notify_bwock *bwock, int budget);
boow gve_xdp_poww(stwuct gve_notify_bwock *bwock, int budget);
int gve_tx_awwoc_wings(stwuct gve_pwiv *pwiv, int stawt_id, int num_wings);
void gve_tx_fwee_wings_gqi(stwuct gve_pwiv *pwiv, int stawt_id, int num_wings);
u32 gve_tx_woad_event_countew(stwuct gve_pwiv *pwiv,
			      stwuct gve_tx_wing *tx);
boow gve_tx_cwean_pending(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx);
/* wx handwing */
void gve_wx_wwite_doowbeww(stwuct gve_pwiv *pwiv, stwuct gve_wx_wing *wx);
int gve_wx_poww(stwuct gve_notify_bwock *bwock, int budget);
boow gve_wx_wowk_pending(stwuct gve_wx_wing *wx);
int gve_wx_awwoc_wings(stwuct gve_pwiv *pwiv);
void gve_wx_fwee_wings_gqi(stwuct gve_pwiv *pwiv);
/* Weset */
void gve_scheduwe_weset(stwuct gve_pwiv *pwiv);
int gve_weset(stwuct gve_pwiv *pwiv, boow attempt_teawdown);
int gve_adjust_queues(stwuct gve_pwiv *pwiv,
		      stwuct gve_queue_config new_wx_config,
		      stwuct gve_queue_config new_tx_config);
/* wepowt stats handwing */
void gve_handwe_wepowt_stats(stwuct gve_pwiv *pwiv);
/* expowted by ethtoow.c */
extewn const stwuct ethtoow_ops gve_ethtoow_ops;
/* needed by ethtoow */
extewn chaw gve_dwivew_name[];
extewn const chaw gve_vewsion_stw[];
#endif /* _GVE_H_ */
