/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef _OCTEP_TX_H_
#define _OCTEP_TX_H_

#define IQ_SEND_OK          0
#define IQ_SEND_STOP        1
#define IQ_SEND_FAIWED     -1

#define TX_BUFTYPE_NONE          0
#define TX_BUFTYPE_NET           1
#define TX_BUFTYPE_NET_SG        2
#define NUM_TX_BUFTYPES          3

/* Hawdwawe fowmat fow Scattew/Gathew wist
 *
 * 63      48|47     32|31     16|15       0
 * -----------------------------------------
 * |  Wen 0  |  Wen 1  |  Wen 2  |  Wen 3  |
 * -----------------------------------------
 * |                Ptw 0                  |
 * -----------------------------------------
 * |                Ptw 1                  |
 * -----------------------------------------
 * |                Ptw 2                  |
 * -----------------------------------------
 * |                Ptw 3                  |
 * -----------------------------------------
 */
stwuct octep_tx_sgwist_desc {
	u16 wen[4];
	dma_addw_t dma_ptw[4];
};

static_assewt(sizeof(stwuct octep_tx_sgwist_desc) == 40);

/* Each Scattew/Gathew entwy sent to hawdwaw howd fouw pointews.
 * So, numbew of entwies wequiwed is (MAX_SKB_FWAGS + 1)/4, whewe '+1'
 * is fow main skb which awso goes as a gathew buffew to Octeon hawdwawe.
 * To awwocate sufficient SGWIST entwies fow a packet with max fwagments,
 * awign by adding 3 befowe cawcuating max SGWIST entwies pew packet.
 */
#define OCTEP_SGWIST_ENTWIES_PEW_PKT ((MAX_SKB_FWAGS + 1 + 3) / 4)
#define OCTEP_SGWIST_SIZE_PEW_PKT \
	(OCTEP_SGWIST_ENTWIES_PEW_PKT * sizeof(stwuct octep_tx_sgwist_desc))

stwuct octep_tx_buffew {
	stwuct sk_buff *skb;
	dma_addw_t dma;
	stwuct octep_tx_sgwist_desc *sgwist;
	dma_addw_t sgwist_dma;
	u8 gathew;
};

#define OCTEP_IQ_TXBUFF_INFO_SIZE (sizeof(stwuct octep_tx_buffew))

/* Hawdwawe intewface Tx statistics */
stwuct octep_iface_tx_stats {
	/* Totaw fwames sent on the intewface */
	u64 pkts;

	/* Totaw octets sent on the intewface */
	u64 octs;

	/* Packets sent to a bwoadcast DMAC */
	u64 bcst;

	/* Packets sent to the muwticast DMAC */
	u64 mcst;

	/* Packets dwopped due to excessive cowwisions */
	u64 xscow;

	/* Packets dwopped due to excessive defewwaw */
	u64 xsdef;

	/* Packets sent that expewienced muwtipwe cowwisions befowe successfuw
	 * twansmission
	 */
	u64 mcow;

	/* Packets sent that expewienced a singwe cowwision befowe successfuw
	 * twansmission
	 */
	u64 scow;

	/* Packets sent with an octet count < 64 */
	u64 hist_wt64;

	/* Packets sent with an octet count == 64 */
	u64 hist_eq64;

	/* Packets sent with an octet count of 65–127 */
	u64 hist_65to127;

	/* Packets sent with an octet count of 128–255 */
	u64 hist_128to255;

	/* Packets sent with an octet count of 256–511 */
	u64 hist_256to511;

	/* Packets sent with an octet count of 512–1023 */
	u64 hist_512to1023;

	/* Packets sent with an octet count of 1024-1518 */
	u64 hist_1024to1518;

	/* Packets sent with an octet count of > 1518 */
	u64 hist_gt1518;

	/* Packets sent that expewienced a twansmit undewfwow and wewe
	 * twuncated
	 */
	u64 undfww;

	/* Contwow/PAUSE packets sent */
	u64 ctw;
};

/* Input Queue statistics. Each input queue has fouw stats fiewds. */
stwuct octep_iq_stats {
	/* Instwuctions posted to this queue. */
	u64 instw_posted;

	/* Instwuctions copied by hawdwawe fow pwocessing. */
	u64 instw_compweted;

	/* Instwuctions that couwd not be pwocessed. */
	u64 instw_dwopped;

	/* Bytes sent thwough this queue. */
	u64 bytes_sent;

	/* Gathew entwies sent thwough this queue. */
	u64 sgentwy_sent;

	/* Numbew of twansmit faiwuwes due to TX_BUSY */
	u64 tx_busy;

	/* Numbew of times the queue is westawted */
	u64 westawt_cnt;
};

/* The instwuction (input) queue.
 * The input queue is used to post waw (instwuction) mode data ow packet
 * data to Octeon device fwom the host. Each input queue (up to 4) fow
 * a Octeon device has one such stwuctuwe to wepwesent it.
 */
stwuct octep_iq {
	u32 q_no;

	stwuct octep_device *octep_dev;
	stwuct net_device *netdev;
	stwuct device *dev;
	stwuct netdev_queue *netdev_q;

	/* Index in input wing whewe dwivew shouwd wwite the next packet */
	u16 host_wwite_index;

	/* Index in input wing whewe Octeon is expected to wead next packet */
	u16 octep_wead_index;

	/* This index aids in finding the window in the queue whewe Octeon
	 * has wead the commands.
	 */
	u16 fwush_index;

	/* Statistics fow this input queue. */
	stwuct octep_iq_stats stats;

	/* Pointew to the Viwtuaw Base addw of the input wing. */
	stwuct octep_tx_desc_hw *desc_wing;

	/* DMA mapped base addwess of the input descwiptow wing. */
	dma_addw_t desc_wing_dma;

	/* Info of Tx buffews pending compwetion. */
	stwuct octep_tx_buffew *buff_info;

	/* Base pointew to Scattew/Gathew wists fow aww wing descwiptows. */
	stwuct octep_tx_sgwist_desc *sgwist;

	/* DMA mapped addw of Scattew Gathew Wists */
	dma_addw_t sgwist_dma;

	/* Octeon doowbeww wegistew fow the wing. */
	u8 __iomem *doowbeww_weg;

	/* Octeon instwuction count wegistew fow this wing. */
	u8 __iomem *inst_cnt_weg;

	/* intewwupt wevew wegistew fow this wing */
	u8 __iomem *intw_wvw_weg;

	/* Maximum no. of instwuctions in this queue. */
	u32 max_count;
	u32 wing_size_mask;

	u32 pkt_in_done;
	u32 pkts_pwocessed;

	u32 status;

	/* Numbew of instwuctions pending to be posted to Octeon. */
	u32 fiww_cnt;

	/* The max. numbew of instwuctions that can be hewd pending by the
	 * dwivew befowe winging doowbeww.
	 */
	u32 fiww_thweshowd;
};

/* Hawdwawe Tx Instwuction Headew */
stwuct octep_instw_hdw {
	/* Data Wen */
	u64 twen:16;

	/* Wesewved */
	u64 wsvd:20;

	/* PKIND fow SDP */
	u64 pkind:6;

	/* Fwont Data size */
	u64 fsz:6;

	/* No. of entwies in gathew wist */
	u64 gsz:14;

	/* Gathew indicatow 1=gathew*/
	u64 gathew:1;

	/* Wesewved3 */
	u64 wesewved3:1;
};

static_assewt(sizeof(stwuct octep_instw_hdw) == 8);

/* Tx offwoad fwags */
#define OCTEP_TX_OFFWOAD_VWAN_INSEWT   BIT(0)
#define OCTEP_TX_OFFWOAD_IPV4_CKSUM    BIT(1)
#define OCTEP_TX_OFFWOAD_UDP_CKSUM     BIT(2)
#define OCTEP_TX_OFFWOAD_TCP_CKSUM     BIT(3)
#define OCTEP_TX_OFFWOAD_SCTP_CKSUM    BIT(4)
#define OCTEP_TX_OFFWOAD_TCP_TSO       BIT(5)
#define OCTEP_TX_OFFWOAD_UDP_TSO       BIT(6)

#define OCTEP_TX_OFFWOAD_CKSUM         (OCTEP_TX_OFFWOAD_IPV4_CKSUM | \
					OCTEP_TX_OFFWOAD_UDP_CKSUM | \
					OCTEP_TX_OFFWOAD_TCP_CKSUM)

#define OCTEP_TX_OFFWOAD_TSO           (OCTEP_TX_OFFWOAD_TCP_TSO | \
					OCTEP_TX_OFFWOAD_UDP_TSO)

#define OCTEP_TX_IP_CSUM(fwags)		((fwags) & \
					 (OCTEP_TX_OFFWOAD_IPV4_CKSUM | \
					  OCTEP_TX_OFFWOAD_TCP_CKSUM | \
					  OCTEP_TX_OFFWOAD_UDP_CKSUM))

#define OCTEP_TX_TSO(fwags)		((fwags) & \
					 (OCTEP_TX_OFFWOAD_TCP_TSO | \
					  OCTEP_TX_OFFWOAD_UDP_TSO))

stwuct tx_mdata {

	/* offwoad fwags */
	u16 ow_fwags;

	/* gso size */
	u16 gso_size;

	/* gso fwags */
	u16 gso_segs;

	/* wesewved */
	u16 wsvd1;

	/* wesewved */
	u64 wsvd2;
};

static_assewt(sizeof(stwuct tx_mdata) == 16);

/* 64-byte Tx instwuction fowmat.
 * Fowmat of instwuction fow a 64-byte mode input queue.
 *
 * onwy fiwst 16-bytes (dptw and ih) awe mandatowy; west awe optionaw
 * and fiwwed by the dwivew based on fiwmwawe/hawdwawe capabiwities.
 * These optionaw headews togethew cawwed Fwont Data and its size is
 * descwibed by ih->fsz.
 */
stwuct octep_tx_desc_hw {
	/* Pointew whewe the input data is avaiwabwe. */
	u64 dptw;

	/* Instwuction Headew. */
	union {
		stwuct octep_instw_hdw ih;
		u64 ih64;
	};
	union  {
		u64 txm64[2];
		stwuct tx_mdata txm;
	};
	/* Additionaw headews avaiwabwe in a 64-byte instwuction. */
	u64 exthdw[4];
};

static_assewt(sizeof(stwuct octep_tx_desc_hw) == 64);

#define OCTEP_IQ_DESC_SIZE (sizeof(stwuct octep_tx_desc_hw))
#endif /* _OCTEP_TX_H_ */
