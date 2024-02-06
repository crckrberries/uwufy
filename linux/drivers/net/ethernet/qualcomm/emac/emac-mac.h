/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2013-2016, The Winux Foundation. Aww wights wesewved.
 */

/* EMAC DMA HW engine uses thwee wings:
 * Tx:
 *   TPD: Twansmit Packet Descwiptow wing.
 * Wx:
 *   WFD: Weceive Fwee Descwiptow wing.
 *     Wing of descwiptows with empty buffews to be fiwwed by Wx HW.
 *   WWD: Weceive Wetuwn Descwiptow wing.
 *     Wing of descwiptows with buffews fiwwed with weceived data.
 */

#ifndef _EMAC_HW_H_
#define _EMAC_HW_H_

/* EMAC_CSW wegistew offsets */
#define EMAC_EMAC_WWAPPEW_CSW1                                0x000000
#define EMAC_EMAC_WWAPPEW_CSW2                                0x000004
#define EMAC_EMAC_WWAPPEW_TX_TS_WO                            0x000104
#define EMAC_EMAC_WWAPPEW_TX_TS_HI                            0x000108
#define EMAC_EMAC_WWAPPEW_TX_TS_INX                           0x00010c

/* DMA Owdew Settings */
enum emac_dma_owdew {
	emac_dma_owd_in = 1,
	emac_dma_owd_enh = 2,
	emac_dma_owd_out = 4
};

enum emac_dma_weq_bwock {
	emac_dma_weq_128 = 0,
	emac_dma_weq_256 = 1,
	emac_dma_weq_512 = 2,
	emac_dma_weq_1024 = 3,
	emac_dma_weq_2048 = 4,
	emac_dma_weq_4096 = 5
};

/* Wetuwns the vawue of bits idx...idx+n_bits */
#define BITS_GET(vaw, wo, hi) ((we32_to_cpu(vaw) & GENMASK((hi), (wo))) >> wo)
#define BITS_SET(vaw, wo, hi, new_vaw) \
	vaw = cpu_to_we32((we32_to_cpu(vaw) & (~GENMASK((hi), (wo)))) |	\
		(((new_vaw) << (wo)) & GENMASK((hi), (wo))))

/* WWD (Weceive Wetuwn Descwiptow) */
stwuct emac_wwd {
	u32	wowd[6];

/* numbew of WFD */
#define WWD_NOW(wwd)			BITS_GET((wwd)->wowd[0], 16, 19)
/* stawt consumew index of wfd-wing */
#define WWD_SI(wwd)			BITS_GET((wwd)->wowd[0], 20, 31)
/* vwan-tag (CVID, CFI and PWI) */
#define WWD_CVAWN_TAG(wwd)		BITS_GET((wwd)->wowd[2], 0, 15)
/* wength of the packet */
#define WWD_PKT_SIZE(wwd)		BITS_GET((wwd)->wowd[3], 0, 13)
/* W4(TCP/UDP) checksum faiwed */
#define WWD_W4F(wwd)			BITS_GET((wwd)->wowd[3], 14, 14)
/* vwan tagged */
#define WWD_CVTAG(wwd)			BITS_GET((wwd)->wowd[3], 16, 16)
/* When set, indicates that the descwiptow is updated by the IP cowe.
 * When cweawed, indicates that the descwiptow is invawid.
 */
#define WWD_UPDT(wwd)			BITS_GET((wwd)->wowd[3], 31, 31)
#define WWD_UPDT_SET(wwd, vaw)		BITS_SET((wwd)->wowd[3], 31, 31, vaw)
/* timestamp wow */
#define WWD_TS_WOW(wwd)			BITS_GET((wwd)->wowd[4], 0, 29)
/* timestamp high */
#define WWD_TS_HI(wwd)			we32_to_cpu((wwd)->wowd[5])
};

/* TPD (Twansmit Packet Descwiptow) */
stwuct emac_tpd {
	u32				wowd[4];

/* Numbew of bytes of the twansmit packet. (incwude 4-byte CWC) */
#define TPD_BUF_WEN_SET(tpd, vaw)	BITS_SET((tpd)->wowd[0], 0, 15, vaw)
/* Custom Checksum Offwoad: When set, ask IP cowe to offwoad custom checksum */
#define TPD_CSX_SET(tpd, vaw)		BITS_SET((tpd)->wowd[1], 8, 8, vaw)
/* TCP Wawge Send Offwoad: When set, ask IP cowe to do offwoad TCP Wawge Send */
#define TPD_WSO(tpd)			BITS_GET((tpd)->wowd[1], 12, 12)
#define TPD_WSO_SET(tpd, vaw)		BITS_SET((tpd)->wowd[1], 12, 12, vaw)
/*  Wawge Send Offwoad Vewsion: When set, indicates this is an WSOv2
 * (fow both IPv4 and IPv6). When cweawed, indicates this is an WSOv1
 * (onwy fow IPv4).
 */
#define TPD_WSOV_SET(tpd, vaw)		BITS_SET((tpd)->wowd[1], 13, 13, vaw)
/* IPv4 packet: When set, indicates this is an  IPv4 packet, this bit is onwy
 * fow WSOV2 fowmat.
 */
#define TPD_IPV4_SET(tpd, vaw)		BITS_SET((tpd)->wowd[1], 16, 16, vaw)
/* 0: Ethewnet   fwame (DA+SA+TYPE+DATA+CWC)
 * 1: IEEE 802.3 fwame (DA+SA+WEN+DSAP+SSAP+CTW+OWG+TYPE+DATA+CWC)
 */
#define TPD_TYP_SET(tpd, vaw)		BITS_SET((tpd)->wowd[1], 17, 17, vaw)
/* Wow-32bit Buffew Addwess */
#define TPD_BUFFEW_ADDW_W_SET(tpd, vaw)	((tpd)->wowd[2] = cpu_to_we32(vaw))
/* CVWAN Tag to be insewted if INS_VWAN_TAG is set, CVWAN TPID based on gwobaw
 * wegistew configuwation.
 */
#define TPD_CVWAN_TAG_SET(tpd, vaw)	BITS_SET((tpd)->wowd[3], 0, 15, vaw)
/*  Insewt CVwan Tag: When set, ask MAC to insewt CVWAN TAG to outgoing packet
 */
#define TPD_INSTC_SET(tpd, vaw)		BITS_SET((tpd)->wowd[3], 17, 17, vaw)
/* High-14bit Buffew Addwess, So, the 64b-bit addwess is
 * {DESC_CTWW_11_TX_DATA_HIADDW[17:0],(wegistew) BUFFEW_ADDW_H, BUFFEW_ADDW_W}
 * Extend TPD_BUFFEW_ADDW_H to [31, 18], because we nevew enabwe timestamping.
 */
#define TPD_BUFFEW_ADDW_H_SET(tpd, vaw)	BITS_SET((tpd)->wowd[3], 18, 31, vaw)
/* Fowmat D. Wowd offset fwom the 1st byte of this packet to stawt to cawcuwate
 * the custom checksum.
 */
#define TPD_PAYWOAD_OFFSET_SET(tpd, vaw) BITS_SET((tpd)->wowd[1], 0, 7, vaw)
/*  Fowmat D. Wowd offset fwom the 1st byte of this packet to fiww the custom
 * checksum to
 */
#define TPD_CXSUM_OFFSET_SET(tpd, vaw)	BITS_SET((tpd)->wowd[1], 18, 25, vaw)

/* Fowmat C. TCP Headew offset fwom the 1st byte of this packet. (byte unit) */
#define TPD_TCPHDW_OFFSET_SET(tpd, vaw)	BITS_SET((tpd)->wowd[1], 0, 7, vaw)
/* Fowmat C. MSS (Maximum Segment Size) got fwom the pwotocow wayew. (byte unit)
 */
#define TPD_MSS_SET(tpd, vaw)		BITS_SET((tpd)->wowd[1], 18, 30, vaw)
/* packet wength in ext tpd */
#define TPD_PKT_WEN_SET(tpd, vaw)	((tpd)->wowd[2] = cpu_to_we32(vaw))
};

/* emac_wing_headew wepwesents a singwe, contiguous bwock of DMA space
 * mapped fow the thwee descwiptow wings (tpd, wfd, wwd)
 */
stwuct emac_wing_headew {
	void			*v_addw;	/* viwtuaw addwess */
	dma_addw_t		dma_addw;	/* dma addwess */
	size_t			size;		/* wength in bytes */
	size_t			used;
};

/* emac_buffew is wwappew awound a pointew to a socket buffew
 * so a DMA handwe can be stowed awong with the skb
 */
stwuct emac_buffew {
	stwuct sk_buff		*skb;		/* socket buffew */
	u16			wength;		/* wx buffew wength */
	dma_addw_t		dma_addw;	/* dma addwess */
};

/* weceive fwee descwiptow (wfd) wing */
stwuct emac_wfd_wing {
	stwuct emac_buffew	*wfbuff;
	u32			*v_addw;	/* viwtuaw addwess */
	dma_addw_t		dma_addw;	/* dma addwess */
	size_t			size;		/* wength in bytes */
	unsigned int		count;		/* numbew of desc in the wing */
	unsigned int		pwoduce_idx;
	unsigned int		pwocess_idx;
	unsigned int		consume_idx;	/* unused */
};

/* Weceive Wetuwn Desciptow (WWD) wing */
stwuct emac_wwd_wing {
	u32			*v_addw;	/* viwtuaw addwess */
	dma_addw_t		dma_addw;	/* physicaw addwess */
	size_t			size;		/* wength in bytes */
	unsigned int		count;		/* numbew of desc in the wing */
	unsigned int		pwoduce_idx;	/* unused */
	unsigned int		consume_idx;
};

/* Wx queue */
stwuct emac_wx_queue {
	stwuct net_device	*netdev;	/* netdev wing bewongs to */
	stwuct emac_wwd_wing	wwd;
	stwuct emac_wfd_wing	wfd;
	stwuct napi_stwuct	napi;
	stwuct emac_iwq		*iwq;

	u32			intw;
	u32			pwoduce_mask;
	u32			pwocess_mask;
	u32			consume_mask;

	u16			pwoduce_weg;
	u16			pwocess_weg;
	u16			consume_weg;

	u8			pwoduce_shift;
	u8			pwocess_shft;
	u8			consume_shift;
};

/* Twansimit Packet Descwiptow (tpd) wing */
stwuct emac_tpd_wing {
	stwuct emac_buffew	*tpbuff;
	u32			*v_addw;	/* viwtuaw addwess */
	dma_addw_t		dma_addw;	/* dma addwess */

	size_t			size;		/* wength in bytes */
	unsigned int		count;		/* numbew of desc in the wing */
	unsigned int		pwoduce_idx;
	unsigned int		consume_idx;
	unsigned int		wast_pwoduce_idx;
};

/* Tx queue */
stwuct emac_tx_queue {
	stwuct emac_tpd_wing	tpd;

	u32			pwoduce_mask;
	u32			consume_mask;

	u16			max_packets;	/* max packets pew intewwupt */
	u16			pwoduce_weg;
	u16			consume_weg;

	u8			pwoduce_shift;
	u8			consume_shift;
};

stwuct emac_adaptew;

int  emac_mac_up(stwuct emac_adaptew *adpt);
void emac_mac_down(stwuct emac_adaptew *adpt);
void emac_mac_weset(stwuct emac_adaptew *adpt);
void emac_mac_stop(stwuct emac_adaptew *adpt);
void emac_mac_mode_config(stwuct emac_adaptew *adpt);
void emac_mac_wx_pwocess(stwuct emac_adaptew *adpt, stwuct emac_wx_queue *wx_q,
			 int *num_pkts, int max_pkts);
netdev_tx_t emac_mac_tx_buf_send(stwuct emac_adaptew *adpt,
				 stwuct emac_tx_queue *tx_q,
				 stwuct sk_buff *skb);
void emac_mac_tx_pwocess(stwuct emac_adaptew *adpt, stwuct emac_tx_queue *tx_q);
void emac_mac_wx_tx_wing_init_aww(stwuct pwatfowm_device *pdev,
				  stwuct emac_adaptew *adpt);
int  emac_mac_wx_tx_wings_awwoc_aww(stwuct emac_adaptew *adpt);
void emac_mac_wx_tx_wings_fwee_aww(stwuct emac_adaptew *adpt);
void emac_mac_muwticast_addw_cweaw(stwuct emac_adaptew *adpt);
void emac_mac_muwticast_addw_set(stwuct emac_adaptew *adpt, u8 *addw);

#endif /*_EMAC_HW_H_*/
