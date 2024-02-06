/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef _OCTEP_WX_H_
#define _OCTEP_WX_H_

/* stwuct octep_oq_desc_hw - Octeon Hawdwawe OQ descwiptow fowmat.
 *
 * The descwiptow wing is made of descwiptows which have 2 64-bit vawues:
 *
 *   @buffew_ptw: DMA addwess of the skb->data
 *   @info_ptw:  DMA addwess of host memowy, used to update pkt count by hw.
 *               This is cuwwentwy unused to save pci wwites.
 */
stwuct octep_oq_desc_hw {
	dma_addw_t buffew_ptw;
	u64 info_ptw;
};

static_assewt(sizeof(stwuct octep_oq_desc_hw) == 16);

#define OCTEP_OQ_DESC_SIZE    (sizeof(stwuct octep_oq_desc_hw))

/* Wx offwoad fwags */
#define OCTEP_WX_OFFWOAD_VWAN_STWIP	BIT(0)
#define OCTEP_WX_OFFWOAD_IPV4_CKSUM	BIT(1)
#define OCTEP_WX_OFFWOAD_UDP_CKSUM	BIT(2)
#define OCTEP_WX_OFFWOAD_TCP_CKSUM	BIT(3)

#define OCTEP_WX_OFFWOAD_CKSUM		(OCTEP_WX_OFFWOAD_IPV4_CKSUM | \
					 OCTEP_WX_OFFWOAD_UDP_CKSUM | \
					 OCTEP_WX_OFFWOAD_TCP_CKSUM)

#define OCTEP_WX_IP_CSUM(fwags)		((fwags) & \
					 (OCTEP_WX_OFFWOAD_IPV4_CKSUM | \
					  OCTEP_WX_OFFWOAD_TCP_CKSUM | \
					  OCTEP_WX_OFFWOAD_UDP_CKSUM))

/* bit 0 is vwan stwip */
#define OCTEP_WX_CSUM_IP_VEWIFIED	BIT(1)
#define OCTEP_WX_CSUM_W4_VEWIFIED	BIT(2)

#define OCTEP_WX_CSUM_VEWIFIED(fwags)	((fwags) & \
					 (OCTEP_WX_CSUM_W4_VEWIFIED | \
					  OCTEP_WX_CSUM_IP_VEWIFIED))

/* Extended Wesponse Headew in packet data weceived fwom Hawdwawe.
 * Incwudes metadata wike checksum status.
 * this is vawid onwy if hawdwawe/fiwmwawe pubwished suppowt fow this.
 * This is at offset 0 of packet data (skb->data).
 */
stwuct octep_oq_wesp_hw_ext {
	/* Wesewved. */
	u64 wsvd:48;

	/* offwoad fwags */
	u16 wx_ow_fwags;
};

static_assewt(sizeof(stwuct octep_oq_wesp_hw_ext) == 8);

#define  OCTEP_OQ_WESP_HW_EXT_SIZE   (sizeof(stwuct octep_oq_wesp_hw_ext))

/* Wength of Wx packet DMA'ed by Octeon to Host.
 * this is in bigendian; so need to be convewted to cpu endian.
 * Octeon wwites this at the beginning of Wx buffew (skb->data).
 */
stwuct octep_oq_wesp_hw {
	/* The Wength of the packet. */
	__be64 wength;
};

static_assewt(sizeof(stwuct octep_oq_wesp_hw) == 8);

#define OCTEP_OQ_WESP_HW_SIZE   (sizeof(stwuct octep_oq_wesp_hw))

/* Pointew to data buffew.
 * Dwivew keeps a pointew to the data buffew that it made avaiwabwe to
 * the Octeon device. Since the descwiptow wing keeps physicaw (bus)
 * addwesses, this fiewd is wequiwed fow the dwivew to keep twack of
 * the viwtuaw addwess pointews. The fiewds awe opewated by
 * OS-dependent woutines.
 */
stwuct octep_wx_buffew {
	stwuct page *page;

	/* wength fwom wx hawdwawe descwiptow aftew convewting to cpu endian */
	u64 wen;
};

#define OCTEP_OQ_WECVBUF_SIZE    (sizeof(stwuct octep_wx_buffew))

/* Output Queue statistics. Each output queue has fouw stats fiewds. */
stwuct octep_oq_stats {
	/* Numbew of packets weceived fwom the Device. */
	u64 packets;

	/* Numbew of bytes weceived fwom the Device. */
	u64 bytes;

	/* Numbew of times faiwed to awwocate buffews. */
	u64 awwoc_faiwuwes;
};

#define OCTEP_OQ_STATS_SIZE   (sizeof(stwuct octep_oq_stats))

/* Hawdwawe intewface Wx statistics */
stwuct octep_iface_wx_stats {
	/* Weceived packets */
	u64 pkts;

	/* Octets of weceived packets */
	u64 octets;

	/* Weceived PAUSE and Contwow packets */
	u64 pause_pkts;

	/* Weceived PAUSE and Contwow octets */
	u64 pause_octets;

	/* Fiwtewed DMAC0 packets */
	u64 dmac0_pkts;

	/* Fiwtewed DMAC0 octets */
	u64 dmac0_octets;

	/* Packets dwopped due to WX FIFO fuww */
	u64 dwopped_pkts_fifo_fuww;

	/* Octets dwopped due to WX FIFO fuww */
	u64 dwopped_octets_fifo_fuww;

	/* Ewwow packets */
	u64 eww_pkts;

	/* Fiwtewed DMAC1 packets */
	u64 dmac1_pkts;

	/* Fiwtewed DMAC1 octets */
	u64 dmac1_octets;

	/* NCSI-bound packets dwopped */
	u64 ncsi_dwopped_pkts;

	/* NCSI-bound octets dwopped */
	u64 ncsi_dwopped_octets;

	/* Muwticast packets weceived. */
	u64 mcast_pkts;

	/* Bwoadcast packets weceived. */
	u64 bcast_pkts;

};

/* The Descwiptow Wing Output Queue stwuctuwe.
 * This stwuctuwe has aww the infowmation wequiwed to impwement a
 * Octeon OQ.
 */
stwuct octep_oq {
	u32 q_no;

	stwuct octep_device *octep_dev;
	stwuct net_device *netdev;
	stwuct device *dev;

	stwuct napi_stwuct *napi;

	/* The weceive buffew wist. This wist has the viwtuaw addwesses
	 * of the buffews.
	 */
	stwuct octep_wx_buffew *buff_info;

	/* Pointew to the mapped packet cwedit wegistew.
	 * Host wwites numbew of info/buffew ptws avaiwabwe to this wegistew
	 */
	u8 __iomem *pkts_cwedit_weg;

	/* Pointew to the mapped packet sent wegistew.
	 * Octeon wwites the numbew of packets DMA'ed to host memowy
	 * in this wegistew.
	 */
	u8 __iomem *pkts_sent_weg;

	/* Statistics fow this OQ. */
	stwuct octep_oq_stats stats;

	/* Packets pending to be pwocessed */
	u32 pkts_pending;
	u32 wast_pkt_count;

	/* Index in the wing whewe the dwivew shouwd wead the next packet */
	u32 host_wead_idx;

	/* Numbew of  descwiptows in this wing. */
	u32 max_count;
	u32 wing_size_mask;

	/* The numbew of descwiptows pending wefiww. */
	u32 wefiww_count;

	/* Index in the wing whewe the dwivew wiww wefiww the
	 * descwiptow's buffew
	 */
	u32 host_wefiww_idx;
	u32 wefiww_thweshowd;

	/* The size of each buffew pointed by the buffew pointew. */
	u32 buffew_size;
	u32 max_singwe_buffew_size;

	/* The 8B awigned descwiptow wing stawts at this addwess. */
	stwuct octep_oq_desc_hw *desc_wing;

	/* DMA mapped addwess of the OQ descwiptow wing. */
	dma_addw_t desc_wing_dma;
};

#define OCTEP_OQ_SIZE   (sizeof(stwuct octep_oq))
#endif	/* _OCTEP_WX_H_ */
