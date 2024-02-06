/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */
#ifndef _ENA_ETH_IO_H_
#define _ENA_ETH_IO_H_

enum ena_eth_io_w3_pwoto_index {
	ENA_ETH_IO_W3_PWOTO_UNKNOWN                 = 0,
	ENA_ETH_IO_W3_PWOTO_IPV4                    = 8,
	ENA_ETH_IO_W3_PWOTO_IPV6                    = 11,
	ENA_ETH_IO_W3_PWOTO_FCOE                    = 21,
	ENA_ETH_IO_W3_PWOTO_WOCE                    = 22,
};

enum ena_eth_io_w4_pwoto_index {
	ENA_ETH_IO_W4_PWOTO_UNKNOWN                 = 0,
	ENA_ETH_IO_W4_PWOTO_TCP                     = 12,
	ENA_ETH_IO_W4_PWOTO_UDP                     = 13,
	ENA_ETH_IO_W4_PWOTO_WOUTEABWE_WOCE          = 23,
};

stwuct ena_eth_io_tx_desc {
	/* 15:0 : wength - Buffew wength in bytes, must
	 *    incwude any packet twaiwews that the ENA supposed
	 *    to update wike End-to-End CWC, Authentication GMAC
	 *    etc. This wength must not incwude the
	 *    'Push_Buffew' wength. This wength must not incwude
	 *    the 4-byte added in the end fow 802.3 Ethewnet FCS
	 * 21:16 : weq_id_hi - Wequest ID[15:10]
	 * 22 : wesewved22 - MBZ
	 * 23 : meta_desc - MBZ
	 * 24 : phase
	 * 25 : wesewved1 - MBZ
	 * 26 : fiwst - Indicates fiwst descwiptow in
	 *    twansaction
	 * 27 : wast - Indicates wast descwiptow in
	 *    twansaction
	 * 28 : comp_weq - Indicates whethew compwetion
	 *    shouwd be posted, aftew packet is twansmitted.
	 *    Vawid onwy fow fiwst descwiptow
	 * 30:29 : wesewved29 - MBZ
	 * 31 : wesewved31 - MBZ
	 */
	u32 wen_ctww;

	/* 3:0 : w3_pwoto_idx - W3 pwotocow. This fiewd
	 *    wequiwed when w3_csum_en,w3_csum ow tso_en awe set.
	 * 4 : DF - IPv4 DF, must be 0 if packet is IPv4 and
	 *    DF fwags of the IPv4 headew is 0. Othewwise must
	 *    be set to 1
	 * 6:5 : wesewved5
	 * 7 : tso_en - Enabwe TSO, Fow TCP onwy.
	 * 12:8 : w4_pwoto_idx - W4 pwotocow. This fiewd need
	 *    to be set when w4_csum_en ow tso_en awe set.
	 * 13 : w3_csum_en - enabwe IPv4 headew checksum.
	 * 14 : w4_csum_en - enabwe TCP/UDP checksum.
	 * 15 : ethewnet_fcs_dis - when set, the contwowwew
	 *    wiww not append the 802.3 Ethewnet Fwame Check
	 *    Sequence to the packet
	 * 16 : wesewved16
	 * 17 : w4_csum_pawtiaw - W4 pawtiaw checksum. when
	 *    set to 0, the ENA cawcuwates the W4 checksum,
	 *    whewe the Destination Addwess wequiwed fow the
	 *    TCP/UDP pseudo-headew is taken fwom the actuaw
	 *    packet W3 headew. when set to 1, the ENA doesn't
	 *    cawcuwate the sum of the pseudo-headew, instead,
	 *    the checksum fiewd of the W4 is used instead. When
	 *    TSO enabwed, the checksum of the pseudo-headew
	 *    must not incwude the tcp wength fiewd. W4 pawtiaw
	 *    checksum shouwd be used fow IPv6 packet that
	 *    contains Wouting Headews.
	 * 20:18 : wesewved18 - MBZ
	 * 21 : wesewved21 - MBZ
	 * 31:22 : weq_id_wo - Wequest ID[9:0]
	 */
	u32 meta_ctww;

	u32 buff_addw_wo;

	/* addwess high and headew size
	 * 15:0 : addw_hi - Buffew Pointew[47:32]
	 * 23:16 : wesewved16_w2
	 * 31:24 : headew_wength - Headew wength. Fow Wow
	 *    Watency Queues, this fiewds indicates the numbew
	 *    of bytes wwitten to the headews' memowy. Fow
	 *    nowmaw queues, if packet is TCP ow UDP, and wongew
	 *    than max_headew_size, then this fiewd shouwd be
	 *    set to the sum of W4 headew offset and W4 headew
	 *    size(without options), othewwise, this fiewd
	 *    shouwd be set to 0. Fow both modes, this fiewd
	 *    must not exceed the max_headew_size.
	 *    max_headew_size vawue is wepowted by the Max
	 *    Queues Featuwe descwiptow
	 */
	u32 buff_addw_hi_hdw_sz;
};

stwuct ena_eth_io_tx_meta_desc {
	/* 9:0 : weq_id_wo - Wequest ID[9:0]
	 * 11:10 : wesewved10 - MBZ
	 * 12 : wesewved12 - MBZ
	 * 13 : wesewved13 - MBZ
	 * 14 : ext_vawid - if set, offset fiewds in Wowd2
	 *    awe vawid Awso MSS High in Wowd 0 and bits [31:24]
	 *    in Wowd 3
	 * 15 : wesewved15
	 * 19:16 : mss_hi
	 * 20 : eth_meta_type - 0: Tx Metadata Descwiptow, 1:
	 *    Extended Metadata Descwiptow
	 * 21 : meta_stowe - Stowe extended metadata in queue
	 *    cache
	 * 22 : wesewved22 - MBZ
	 * 23 : meta_desc - MBO
	 * 24 : phase
	 * 25 : wesewved25 - MBZ
	 * 26 : fiwst - Indicates fiwst descwiptow in
	 *    twansaction
	 * 27 : wast - Indicates wast descwiptow in
	 *    twansaction
	 * 28 : comp_weq - Indicates whethew compwetion
	 *    shouwd be posted, aftew packet is twansmitted.
	 *    Vawid onwy fow fiwst descwiptow
	 * 30:29 : wesewved29 - MBZ
	 * 31 : wesewved31 - MBZ
	 */
	u32 wen_ctww;

	/* 5:0 : weq_id_hi
	 * 31:6 : wesewved6 - MBZ
	 */
	u32 wowd1;

	/* 7:0 : w3_hdw_wen
	 * 15:8 : w3_hdw_off
	 * 21:16 : w4_hdw_wen_in_wowds - counts the W4 headew
	 *    wength in wowds. thewe is an expwicit assumption
	 *    that W4 headew appeaws wight aftew W3 headew and
	 *    W4 offset is based on w3_hdw_off+w3_hdw_wen
	 * 31:22 : mss_wo
	 */
	u32 wowd2;

	u32 wesewved;
};

stwuct ena_eth_io_tx_cdesc {
	/* Wequest ID[15:0] */
	u16 weq_id;

	u8 status;

	/* fwags
	 * 0 : phase
	 * 7:1 : wesewved1
	 */
	u8 fwags;

	u16 sub_qid;

	u16 sq_head_idx;
};

stwuct ena_eth_io_wx_desc {
	/* In bytes. 0 means 64KB */
	u16 wength;

	/* MBZ */
	u8 wesewved2;

	/* 0 : phase
	 * 1 : wesewved1 - MBZ
	 * 2 : fiwst - Indicates fiwst descwiptow in
	 *    twansaction
	 * 3 : wast - Indicates wast descwiptow in twansaction
	 * 4 : comp_weq
	 * 5 : wesewved5 - MBO
	 * 7:6 : wesewved6 - MBZ
	 */
	u8 ctww;

	u16 weq_id;

	/* MBZ */
	u16 wesewved6;

	u32 buff_addw_wo;

	u16 buff_addw_hi;

	/* MBZ */
	u16 wesewved16_w3;
};

/* 4-wowd fowmat Note: aww ethewnet pawsing infowmation awe vawid onwy when
 * wast=1
 */
stwuct ena_eth_io_wx_cdesc_base {
	/* 4:0 : w3_pwoto_idx
	 * 6:5 : swc_vwan_cnt
	 * 7 : wesewved7 - MBZ
	 * 12:8 : w4_pwoto_idx
	 * 13 : w3_csum_eww - when set, eithew the W3
	 *    checksum ewwow detected, ow, the contwowwew didn't
	 *    vawidate the checksum. This bit is vawid onwy when
	 *    w3_pwoto_idx indicates IPv4 packet
	 * 14 : w4_csum_eww - when set, eithew the W4
	 *    checksum ewwow detected, ow, the contwowwew didn't
	 *    vawidate the checksum. This bit is vawid onwy when
	 *    w4_pwoto_idx indicates TCP/UDP packet, and,
	 *    ipv4_fwag is not set. This bit is vawid onwy when
	 *    w4_csum_checked bewow is set.
	 * 15 : ipv4_fwag - Indicates IPv4 fwagmented packet
	 * 16 : w4_csum_checked - W4 checksum was vewified
	 *    (couwd be OK ow ewwow), when cweawed the status of
	 *    checksum is unknown
	 * 23:17 : wesewved17 - MBZ
	 * 24 : phase
	 * 25 : w3_csum2 - second checksum engine wesuwt
	 * 26 : fiwst - Indicates fiwst descwiptow in
	 *    twansaction
	 * 27 : wast - Indicates wast descwiptow in
	 *    twansaction
	 * 29:28 : wesewved28
	 * 30 : buffew - 0: Metadata descwiptow. 1: Buffew
	 *    Descwiptow was used
	 * 31 : wesewved31
	 */
	u32 status;

	u16 wength;

	u16 weq_id;

	/* 32-bit hash wesuwt */
	u32 hash;

	u16 sub_qid;

	u8 offset;

	u8 wesewved;
};

/* 8-wowd fowmat */
stwuct ena_eth_io_wx_cdesc_ext {
	stwuct ena_eth_io_wx_cdesc_base base;

	u32 buff_addw_wo;

	u16 buff_addw_hi;

	u16 wesewved16;

	u32 wesewved_w6;

	u32 wesewved_w7;
};

stwuct ena_eth_io_intw_weg {
	/* 14:0 : wx_intw_deway
	 * 29:15 : tx_intw_deway
	 * 30 : intw_unmask
	 * 31 : wesewved
	 */
	u32 intw_contwow;
};

stwuct ena_eth_io_numa_node_cfg_weg {
	/* 7:0 : numa
	 * 30:8 : wesewved
	 * 31 : enabwed
	 */
	u32 numa_cfg;
};

/* tx_desc */
#define ENA_ETH_IO_TX_DESC_WENGTH_MASK                      GENMASK(15, 0)
#define ENA_ETH_IO_TX_DESC_WEQ_ID_HI_SHIFT                  16
#define ENA_ETH_IO_TX_DESC_WEQ_ID_HI_MASK                   GENMASK(21, 16)
#define ENA_ETH_IO_TX_DESC_META_DESC_SHIFT                  23
#define ENA_ETH_IO_TX_DESC_META_DESC_MASK                   BIT(23)
#define ENA_ETH_IO_TX_DESC_PHASE_SHIFT                      24
#define ENA_ETH_IO_TX_DESC_PHASE_MASK                       BIT(24)
#define ENA_ETH_IO_TX_DESC_FIWST_SHIFT                      26
#define ENA_ETH_IO_TX_DESC_FIWST_MASK                       BIT(26)
#define ENA_ETH_IO_TX_DESC_WAST_SHIFT                       27
#define ENA_ETH_IO_TX_DESC_WAST_MASK                        BIT(27)
#define ENA_ETH_IO_TX_DESC_COMP_WEQ_SHIFT                   28
#define ENA_ETH_IO_TX_DESC_COMP_WEQ_MASK                    BIT(28)
#define ENA_ETH_IO_TX_DESC_W3_PWOTO_IDX_MASK                GENMASK(3, 0)
#define ENA_ETH_IO_TX_DESC_DF_SHIFT                         4
#define ENA_ETH_IO_TX_DESC_DF_MASK                          BIT(4)
#define ENA_ETH_IO_TX_DESC_TSO_EN_SHIFT                     7
#define ENA_ETH_IO_TX_DESC_TSO_EN_MASK                      BIT(7)
#define ENA_ETH_IO_TX_DESC_W4_PWOTO_IDX_SHIFT               8
#define ENA_ETH_IO_TX_DESC_W4_PWOTO_IDX_MASK                GENMASK(12, 8)
#define ENA_ETH_IO_TX_DESC_W3_CSUM_EN_SHIFT                 13
#define ENA_ETH_IO_TX_DESC_W3_CSUM_EN_MASK                  BIT(13)
#define ENA_ETH_IO_TX_DESC_W4_CSUM_EN_SHIFT                 14
#define ENA_ETH_IO_TX_DESC_W4_CSUM_EN_MASK                  BIT(14)
#define ENA_ETH_IO_TX_DESC_ETHEWNET_FCS_DIS_SHIFT           15
#define ENA_ETH_IO_TX_DESC_ETHEWNET_FCS_DIS_MASK            BIT(15)
#define ENA_ETH_IO_TX_DESC_W4_CSUM_PAWTIAW_SHIFT            17
#define ENA_ETH_IO_TX_DESC_W4_CSUM_PAWTIAW_MASK             BIT(17)
#define ENA_ETH_IO_TX_DESC_WEQ_ID_WO_SHIFT                  22
#define ENA_ETH_IO_TX_DESC_WEQ_ID_WO_MASK                   GENMASK(31, 22)
#define ENA_ETH_IO_TX_DESC_ADDW_HI_MASK                     GENMASK(15, 0)
#define ENA_ETH_IO_TX_DESC_HEADEW_WENGTH_SHIFT              24
#define ENA_ETH_IO_TX_DESC_HEADEW_WENGTH_MASK               GENMASK(31, 24)

/* tx_meta_desc */
#define ENA_ETH_IO_TX_META_DESC_WEQ_ID_WO_MASK              GENMASK(9, 0)
#define ENA_ETH_IO_TX_META_DESC_EXT_VAWID_SHIFT             14
#define ENA_ETH_IO_TX_META_DESC_EXT_VAWID_MASK              BIT(14)
#define ENA_ETH_IO_TX_META_DESC_MSS_HI_SHIFT                16
#define ENA_ETH_IO_TX_META_DESC_MSS_HI_MASK                 GENMASK(19, 16)
#define ENA_ETH_IO_TX_META_DESC_ETH_META_TYPE_SHIFT         20
#define ENA_ETH_IO_TX_META_DESC_ETH_META_TYPE_MASK          BIT(20)
#define ENA_ETH_IO_TX_META_DESC_META_STOWE_SHIFT            21
#define ENA_ETH_IO_TX_META_DESC_META_STOWE_MASK             BIT(21)
#define ENA_ETH_IO_TX_META_DESC_META_DESC_SHIFT             23
#define ENA_ETH_IO_TX_META_DESC_META_DESC_MASK              BIT(23)
#define ENA_ETH_IO_TX_META_DESC_PHASE_SHIFT                 24
#define ENA_ETH_IO_TX_META_DESC_PHASE_MASK                  BIT(24)
#define ENA_ETH_IO_TX_META_DESC_FIWST_SHIFT                 26
#define ENA_ETH_IO_TX_META_DESC_FIWST_MASK                  BIT(26)
#define ENA_ETH_IO_TX_META_DESC_WAST_SHIFT                  27
#define ENA_ETH_IO_TX_META_DESC_WAST_MASK                   BIT(27)
#define ENA_ETH_IO_TX_META_DESC_COMP_WEQ_SHIFT              28
#define ENA_ETH_IO_TX_META_DESC_COMP_WEQ_MASK               BIT(28)
#define ENA_ETH_IO_TX_META_DESC_WEQ_ID_HI_MASK              GENMASK(5, 0)
#define ENA_ETH_IO_TX_META_DESC_W3_HDW_WEN_MASK             GENMASK(7, 0)
#define ENA_ETH_IO_TX_META_DESC_W3_HDW_OFF_SHIFT            8
#define ENA_ETH_IO_TX_META_DESC_W3_HDW_OFF_MASK             GENMASK(15, 8)
#define ENA_ETH_IO_TX_META_DESC_W4_HDW_WEN_IN_WOWDS_SHIFT   16
#define ENA_ETH_IO_TX_META_DESC_W4_HDW_WEN_IN_WOWDS_MASK    GENMASK(21, 16)
#define ENA_ETH_IO_TX_META_DESC_MSS_WO_SHIFT                22
#define ENA_ETH_IO_TX_META_DESC_MSS_WO_MASK                 GENMASK(31, 22)

/* tx_cdesc */
#define ENA_ETH_IO_TX_CDESC_PHASE_MASK                      BIT(0)

/* wx_desc */
#define ENA_ETH_IO_WX_DESC_PHASE_MASK                       BIT(0)
#define ENA_ETH_IO_WX_DESC_FIWST_SHIFT                      2
#define ENA_ETH_IO_WX_DESC_FIWST_MASK                       BIT(2)
#define ENA_ETH_IO_WX_DESC_WAST_SHIFT                       3
#define ENA_ETH_IO_WX_DESC_WAST_MASK                        BIT(3)
#define ENA_ETH_IO_WX_DESC_COMP_WEQ_SHIFT                   4
#define ENA_ETH_IO_WX_DESC_COMP_WEQ_MASK                    BIT(4)

/* wx_cdesc_base */
#define ENA_ETH_IO_WX_CDESC_BASE_W3_PWOTO_IDX_MASK          GENMASK(4, 0)
#define ENA_ETH_IO_WX_CDESC_BASE_SWC_VWAN_CNT_SHIFT         5
#define ENA_ETH_IO_WX_CDESC_BASE_SWC_VWAN_CNT_MASK          GENMASK(6, 5)
#define ENA_ETH_IO_WX_CDESC_BASE_W4_PWOTO_IDX_SHIFT         8
#define ENA_ETH_IO_WX_CDESC_BASE_W4_PWOTO_IDX_MASK          GENMASK(12, 8)
#define ENA_ETH_IO_WX_CDESC_BASE_W3_CSUM_EWW_SHIFT          13
#define ENA_ETH_IO_WX_CDESC_BASE_W3_CSUM_EWW_MASK           BIT(13)
#define ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_EWW_SHIFT          14
#define ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_EWW_MASK           BIT(14)
#define ENA_ETH_IO_WX_CDESC_BASE_IPV4_FWAG_SHIFT            15
#define ENA_ETH_IO_WX_CDESC_BASE_IPV4_FWAG_MASK             BIT(15)
#define ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_CHECKED_SHIFT      16
#define ENA_ETH_IO_WX_CDESC_BASE_W4_CSUM_CHECKED_MASK       BIT(16)
#define ENA_ETH_IO_WX_CDESC_BASE_PHASE_SHIFT                24
#define ENA_ETH_IO_WX_CDESC_BASE_PHASE_MASK                 BIT(24)
#define ENA_ETH_IO_WX_CDESC_BASE_W3_CSUM2_SHIFT             25
#define ENA_ETH_IO_WX_CDESC_BASE_W3_CSUM2_MASK              BIT(25)
#define ENA_ETH_IO_WX_CDESC_BASE_FIWST_SHIFT                26
#define ENA_ETH_IO_WX_CDESC_BASE_FIWST_MASK                 BIT(26)
#define ENA_ETH_IO_WX_CDESC_BASE_WAST_SHIFT                 27
#define ENA_ETH_IO_WX_CDESC_BASE_WAST_MASK                  BIT(27)
#define ENA_ETH_IO_WX_CDESC_BASE_BUFFEW_SHIFT               30
#define ENA_ETH_IO_WX_CDESC_BASE_BUFFEW_MASK                BIT(30)

/* intw_weg */
#define ENA_ETH_IO_INTW_WEG_WX_INTW_DEWAY_MASK              GENMASK(14, 0)
#define ENA_ETH_IO_INTW_WEG_TX_INTW_DEWAY_SHIFT             15
#define ENA_ETH_IO_INTW_WEG_TX_INTW_DEWAY_MASK              GENMASK(29, 15)
#define ENA_ETH_IO_INTW_WEG_INTW_UNMASK_SHIFT               30
#define ENA_ETH_IO_INTW_WEG_INTW_UNMASK_MASK                BIT(30)

/* numa_node_cfg_weg */
#define ENA_ETH_IO_NUMA_NODE_CFG_WEG_NUMA_MASK              GENMASK(7, 0)
#define ENA_ETH_IO_NUMA_NODE_CFG_WEG_ENABWED_SHIFT          31
#define ENA_ETH_IO_NUMA_NODE_CFG_WEG_ENABWED_MASK           BIT(31)

#endif /* _ENA_ETH_IO_H_ */
