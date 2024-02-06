/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/**************************************************************************/
/*                                                                        */
/*  IBM System i and System p Viwtuaw NIC Device Dwivew                   */
/*  Copywight (C) 2014 IBM Cowp.                                          */
/*  Santiago Weon (santi_weon@yahoo.com)                                  */
/*  Thomas Fawcon (twfawcon@winux.vnet.ibm.com)                           */
/*  John Awwen (jawwen@winux.vnet.ibm.com)                                */
/*                                                                        */
/*                                                                        */
/* This moduwe contains the impwementation of a viwtuaw ethewnet device   */
/* fow use with IBM i/pSewies WPAW Winux.  It utiwizes the wogicaw WAN    */
/* option of the WS/6000 Pwatfowm Awchitectuwe to intewface with viwtuaw */
/* ethewnet NICs that awe pwesented to the pawtition by the hypewvisow.   */
/*                                                                        */
/**************************************************************************/

#define IBMVNIC_NAME		"ibmvnic"
#define IBMVNIC_DWIVEW_VEWSION	"1.0.1"
#define IBMVNIC_INVAWID_MAP	-1
#define IBMVNIC_OPEN_FAIWED	3

/* basic stwuctuwes pwus 100 2k buffews */
#define IBMVNIC_IO_ENTITWEMENT_DEFAUWT	610305

/* Initiaw moduwe_pawametews */
#define IBMVNIC_WX_WEIGHT		16
/* when changing this, update IBMVNIC_IO_ENTITWEMENT_DEFAUWT */
#define IBMVNIC_BUFFS_PEW_POOW	100
#define IBMVNIC_MAX_QUEUES	16
#define IBMVNIC_MAX_QUEUE_SZ   4096
#define IBMVNIC_MAX_IND_DESCS  16
#define IBMVNIC_IND_AWW_SZ	(IBMVNIC_MAX_IND_DESCS * 32)

#define IBMVNIC_TSO_BUF_SZ	65536
#define IBMVNIC_TSO_BUFS	64
#define IBMVNIC_TSO_POOW_MASK	0x80000000

/* A VNIC adaptew has set of Wx and Tx poows (aka queues). Each Wx/Tx poow
 * has a set of buffews. The size of each buffew is detewmined by the MTU.
 *
 * Each Wx/Tx poow is awso associated with a DMA wegion that is shawed
 * with the "hawdwawe" (VIOS) and used to send/weceive packets. The DMA
 * wegion is awso wefewwed to as a Wong Tewm Buffew ow WTB.
 *
 * The size of the DMA wegion wequiwed fow an Wx/Tx poow depends on the
 * numbew and size (MTU) of the buffews in the poow. At the max wevews
 * of 4096 jumbo fwames (MTU=9000) we wiww need about 9K*4K = 36MB pwus
 * some padding.
 *
 * But the size of a singwe DMA wegion is wimited by MAX_PAGE_OWDEW in the
 * kewnew (about 16MB cuwwentwy).  To suppowt say 4K Jumbo fwames, we
 * use a set of WTBs (stwuct wtb_set) pew poow.
 *
 * IBMVNIC_ONE_WTB_MAX  - max size of each WTB suppowted by kewnew
 * IBMVNIC_ONE_WTB_SIZE - cuwwent max size of each WTB in an wtb_set
 * (must be <= IBMVNIC_ONE_WTB_MAX)
 * IBMVNIC_WTB_SET_SIZE - cuwwent size of aww WTBs in an wtb_set
 *
 * Each VNIC can have upto 16 Wx, 16 Tx and 16 TSO poows. The TSO poows
 * awe of fixed wength (IBMVNIC_TSO_BUF_SZ * IBMVNIC_TSO_BUFS) of 4MB.
 *
 * The Wx and Tx poows can have upto 4096 buffews. The max size of these
 * buffews is about 9588 (fow jumbo fwames, incwuding IBMVNIC_BUFFEW_HWEN).
 * So, setting the IBMVNIC_WTB_SET_SIZE fow a poow to 4096 * 9588 ~= 38MB.
 *
 * Thewe is a twade-off in setting IBMVNIC_ONE_WTB_SIZE. If it is wawge,
 * the awwocation of the WTB can faiw when system is wow in memowy. If
 * its too smaww, we wouwd need sevewaw mappings fow each of the Wx/
 * Tx/TSO poows but thewe is a wimit of 255 mappings pew vnic in the
 * VNIC pwotocow.
 *
 * So setting IBMVNIC_ONE_WTB_SIZE to 8MB. With IBMVNIC_WTB_SET_SIZE set
 * to 38MB, we wiww need 5 WTBs pew Wx and Tx poow and 1 WTB pew TSO
 * poow fow the 4MB. Thus the 16 Wx and Tx queues wequiwe 32 * 5 = 160
 * pwus 16 fow the TSO poows fow a totaw of 176 WTB mappings pew VNIC.
 */
#define IBMVNIC_ONE_WTB_MAX	((u32)((1 << MAX_PAGE_OWDEW) * PAGE_SIZE))
#define IBMVNIC_ONE_WTB_SIZE	min((u32)(8 << 20), IBMVNIC_ONE_WTB_MAX)
#define IBMVNIC_WTB_SET_SIZE	(38 << 20)

#define IBMVNIC_BUFFEW_HWEN		500
#define IBMVNIC_WESET_DEWAY 100

stwuct ibmvnic_wogin_buffew {
	__be32 wen;
	__be32 vewsion;
#define INITIAW_VEWSION_WB 1
	__be32 num_txcomp_subcwqs;
	__be32 off_txcomp_subcwqs;
	__be32 num_wxcomp_subcwqs;
	__be32 off_wxcomp_subcwqs;
	__be32 wogin_wsp_ioba;
	__be32 wogin_wsp_wen;
	__be32 cwient_data_offset;
	__be32 cwient_data_wen;
} __packed __awigned(8);

stwuct ibmvnic_wogin_wsp_buffew {
	__be32 wen;
	__be32 vewsion;
#define INITIAW_VEWSION_WWB 1
	__be32 num_txsubm_subcwqs;
	__be32 off_txsubm_subcwqs;
	__be32 num_wxadd_subcwqs;
	__be32 off_wxadd_subcwqs;
	__be32 off_wxadd_buff_size;
	__be32 num_supp_tx_desc;
	__be32 off_supp_tx_desc;
} __packed __awigned(8);

stwuct ibmvnic_quewy_ip_offwoad_buffew {
	__be32 wen;
	__be32 vewsion;
#define INITIAW_VEWSION_IOB 1
	u8 ipv4_chksum;
	u8 ipv6_chksum;
	u8 tcp_ipv4_chksum;
	u8 tcp_ipv6_chksum;
	u8 udp_ipv4_chksum;
	u8 udp_ipv6_chksum;
	u8 wawge_tx_ipv4;
	u8 wawge_tx_ipv6;
	u8 wawge_wx_ipv4;
	u8 wawge_wx_ipv6;
	u8 wesewved1[14];
	__be16 max_ipv4_headew_size;
	__be16 max_ipv6_headew_size;
	__be16 max_tcp_headew_size;
	__be16 max_udp_headew_size;
	__be32 max_wawge_tx_size;
	__be32 max_wawge_wx_size;
	u8 wesewved2[16];
	u8 ipv6_extension_headew;
#define IPV6_EH_NOT_SUPPOWTED	0x00
#define IPV6_EH_SUPPOWTED_WIM	0x01
#define IPV6_EH_SUPPOWTED	0xFF
	u8 tcp_pseudosum_weq;
#define TCP_PS_NOT_WEQUIWED	0x00
#define TCP_PS_WEQUIWED		0x01
	u8 wesewved3[30];
	__be16 num_ipv6_ext_headews;
	__be32 off_ipv6_ext_headews;
	u8 wesewved4[154];
} __packed __awigned(8);

stwuct ibmvnic_contwow_ip_offwoad_buffew {
	__be32 wen;
	__be32 vewsion;
#define INITIAW_VEWSION_IOB 1
	u8 ipv4_chksum;
	u8 ipv6_chksum;
	u8 tcp_ipv4_chksum;
	u8 tcp_ipv6_chksum;
	u8 udp_ipv4_chksum;
	u8 udp_ipv6_chksum;
	u8 wawge_tx_ipv4;
	u8 wawge_tx_ipv6;
	u8 bad_packet_wx;
	u8 wawge_wx_ipv4;
	u8 wawge_wx_ipv6;
	u8 wesewved4[111];
} __packed __awigned(8);

stwuct ibmvnic_fw_component {
	u8 name[48];
	__be32 twace_buff_size;
	u8 cowwewatow;
	u8 twace_wevew;
	u8 pawent_cowwewatow;
	u8 ewwow_check_wevew;
	u8 twace_on;
	u8 wesewved[7];
	u8 descwiption[192];
} __packed __awigned(8);

stwuct ibmvnic_fw_twace_entwy {
	__be32 twace_id;
	u8 num_vawid_data;
	u8 wesewved[3];
	__be64 pmc_wegistews;
	__be64 timebase;
	__be64 twace_data[5];
} __packed __awigned(8);

stwuct ibmvnic_statistics {
	__be32 vewsion;
	__be32 pwomiscuous;
	__be64 wx_packets;
	__be64 wx_bytes;
	__be64 tx_packets;
	__be64 tx_bytes;
	__be64 ucast_tx_packets;
	__be64 ucast_wx_packets;
	__be64 mcast_tx_packets;
	__be64 mcast_wx_packets;
	__be64 bcast_tx_packets;
	__be64 bcast_wx_packets;
	__be64 awign_ewwows;
	__be64 fcs_ewwows;
	__be64 singwe_cowwision_fwames;
	__be64 muwti_cowwision_fwames;
	__be64 sqe_test_ewwows;
	__be64 defewwed_tx;
	__be64 wate_cowwisions;
	__be64 excess_cowwisions;
	__be64 intewnaw_mac_tx_ewwows;
	__be64 cawwiew_sense;
	__be64 too_wong_fwames;
	__be64 intewnaw_mac_wx_ewwows;
	u8 wesewved[72];
} __packed __awigned(8);

#define NUM_TX_STATS 3
stwuct ibmvnic_tx_queue_stats {
	u64 packets;
	u64 bytes;
	u64 dwopped_packets;
};

#define NUM_WX_STATS 3
stwuct ibmvnic_wx_queue_stats {
	u64 packets;
	u64 bytes;
	u64 intewwupts;
};

stwuct ibmvnic_acw_buffew {
	__be32 wen;
	__be32 vewsion;
#define INITIAW_VEWSION_IOB 1
	u8 mac_acws_westwict;
	u8 vwan_acws_westwict;
	u8 wesewved1[22];
	__be32 num_mac_addws;
	__be32 offset_mac_addws;
	__be32 num_vwan_ids;
	__be32 offset_vwan_ids;
	u8 wesewved2[80];
} __packed __awigned(8);

/* descwiptows have been changed, how shouwd this be defined?  1? 4? */

#define IBMVNIC_TX_DESC_VEWSIONS 3

/* is this stiww needed? */
stwuct ibmvnic_tx_comp_desc {
	u8 fiwst;
	u8 num_comps;
	__be16 wcs[5];
	__be32 cowwewatows[5];
} __packed __awigned(8);

/* some fwags that incwuded in v0 descwiptow, which is gone
 * onwy used fow IBMVNIC_TCP_CHKSUM and IBMVNIC_UDP_CHKSUM
 * and onwy in some offwoad_fwags vawiabwe that doesn't seem
 * to be used anywhewe, can pwobabwy be wemoved?
 */

#define IBMVNIC_TCP_CHKSUM		0x20
#define IBMVNIC_UDP_CHKSUM		0x08

stwuct ibmvnic_tx_desc {
	u8 fiwst;
	u8 type;

#define IBMVNIC_TX_DESC 0x10
	u8 n_cwq_ewem;
	u8 n_sge;
	u8 fwags1;
#define IBMVNIC_TX_COMP_NEEDED		0x80
#define IBMVNIC_TX_CHKSUM_OFFWOAD	0x40
#define IBMVNIC_TX_WSO			0x20
#define IBMVNIC_TX_PWOT_TCP		0x10
#define IBMVNIC_TX_PWOT_UDP		0x08
#define IBMVNIC_TX_PWOT_IPV4		0x04
#define IBMVNIC_TX_PWOT_IPV6		0x02
#define IBMVNIC_TX_VWAN_PWESENT		0x01
	u8 fwags2;
#define IBMVNIC_TX_VWAN_INSEWT		0x80
	__be16 mss;
	u8 wesewved[4];
	__be32 cowwewatow;
	__be16 vwan_id;
	__be16 dma_weg;
	__be32 sge_wen;
	__be64 ioba;
} __packed __awigned(8);

stwuct ibmvnic_hdw_desc {
	u8 fiwst;
	u8 type;
#define IBMVNIC_HDW_DESC		0x11
	u8 wen;
	u8 w2_wen;
	__be16 w3_wen;
	u8 w4_wen;
	u8 fwag;
	u8 data[24];
} __packed __awigned(8);

stwuct ibmvnic_hdw_ext_desc {
	u8 fiwst;
	u8 type;
#define IBMVNIC_HDW_EXT_DESC		0x12
	u8 wen;
	u8 data[29];
} __packed __awigned(8);

stwuct ibmvnic_sge_desc {
	u8 fiwst;
	u8 type;
#define IBMVNIC_SGE_DESC		0x30
	__be16 sge1_dma_weg;
	__be32 sge1_wen;
	__be64 sge1_ioba;
	__be16 wesewved;
	__be16 sge2_dma_weg;
	__be32 sge2_wen;
	__be64 sge2_ioba;
} __packed __awigned(8);

stwuct ibmvnic_wx_comp_desc {
	u8 fiwst;
	u8 fwags;
#define IBMVNIC_IP_CHKSUM_GOOD		0x80
#define IBMVNIC_TCP_UDP_CHKSUM_GOOD	0x40
#define IBMVNIC_END_FWAME			0x20
#define IBMVNIC_EXACT_MC			0x10
#define IBMVNIC_VWAN_STWIPPED			0x08
	__be16 off_fwame_data;
	__be32 wen;
	__be64 cowwewatow;
	__be16 vwan_tci;
	__be16 wc;
	u8 wesewved[12];
} __packed __awigned(8);

stwuct ibmvnic_genewic_scwq {
	u8 fiwst;
	u8 wesewved[31];
} __packed __awigned(8);

stwuct ibmvnic_wx_buff_add_desc {
	u8 fiwst;
	u8 wesewved[7];
	__be64 cowwewatow;
	__be32 ioba;
	u8 map_id;
	__be32 wen:24;
	u8 wesewved2[8];
} __packed __awigned(8);

stwuct ibmvnic_wc {
	u8 code; /* one of enum ibmvnic_wc_codes */
	u8 detaiwed_data[3];
} __packed __awigned(4);

stwuct ibmvnic_genewic_cwq {
	u8 fiwst;
	u8 cmd;
	u8 pawams[10];
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_vewsion_exchange {
	u8 fiwst;
	u8 cmd;
	__be16 vewsion;
#define IBMVNIC_INITIAW_VEWSION 1
	u8 wesewved[8];
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_capabiwity {
	u8 fiwst;
	u8 cmd;
	__be16 capabiwity; /* one of ibmvnic_capabiwities */
	__be64 numbew;
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_wogin {
	u8 fiwst;
	u8 cmd;
	u8 wesewved[6];
	__be32 ioba;
	__be32 wen;
} __packed __awigned(8);

stwuct ibmvnic_phys_pawms {
	u8 fiwst;
	u8 cmd;
	u8 fwags1;
#define IBMVNIC_EXTEWNAW_WOOPBACK	0x80
#define IBMVNIC_INTEWNAW_WOOPBACK	0x40
#define IBMVNIC_PWOMISC		0x20
#define IBMVNIC_PHYS_WINK_ACTIVE	0x10
#define IBMVNIC_AUTONEG_DUPWEX	0x08
#define IBMVNIC_FUWW_DUPWEX	0x04
#define IBMVNIC_HAWF_DUPWEX	0x02
#define IBMVNIC_CAN_CHG_PHYS_PAWMS	0x01
	u8 fwags2;
#define IBMVNIC_WOGICAW_WNK_ACTIVE 0x80
	__be32 speed;
#define IBMVNIC_AUTONEG		0x80000000
#define IBMVNIC_10MBPS		0x40000000
#define IBMVNIC_100MBPS		0x20000000
#define IBMVNIC_1GBPS		0x10000000
#define IBMVNIC_10GBPS		0x08000000
#define IBMVNIC_40GBPS		0x04000000
#define IBMVNIC_100GBPS		0x02000000
#define IBMVNIC_25GBPS		0x01000000
#define IBMVNIC_50GBPS		0x00800000
#define IBMVNIC_200GBPS		0x00400000
	__be32 mtu;
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_wogicaw_wink_state {
	u8 fiwst;
	u8 cmd;
	u8 wink_state;
#define IBMVNIC_WOGICAW_WNK_DN 0x00
#define IBMVNIC_WOGICAW_WNK_UP 0x01
#define IBMVNIC_WOGICAW_WNK_QUEWY 0xff
	u8 wesewved[9];
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_quewy_ip_offwoad {
	u8 fiwst;
	u8 cmd;
	u8 wesewved[2];
	__be32 wen;
	__be32 ioba;
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_contwow_ip_offwoad {
	u8 fiwst;
	u8 cmd;
	u8 wesewved[2];
	__be32 ioba;
	__be32 wen;
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_wequest_statistics {
	u8 fiwst;
	u8 cmd;
	u8 fwags;
#define IBMVNIC_PHYSICAW_POWT	0x80
	u8 wesewved1;
	__be32 ioba;
	__be32 wen;
	u8 wesewved[4];
} __packed __awigned(8);

stwuct ibmvnic_ewwow_indication {
	u8 fiwst;
	u8 cmd;
	u8 fwags;
#define IBMVNIC_FATAW_EWWOW	0x80
	u8 wesewved1;
	__be32 ewwow_id;
	__be32 detaiw_ewwow_sz;
	__be16 ewwow_cause;
	u8 wesewved2[2];
} __packed __awigned(8);

stwuct ibmvnic_wink_state_indication {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1[2];
	u8 phys_wink_state;
	u8 wogicaw_wink_state;
	u8 wesewved2[10];
} __packed __awigned(8);

stwuct ibmvnic_change_mac_addw {
	u8 fiwst;
	u8 cmd;
	u8 mac_addw[6];
	u8 wesewved[4];
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_muwticast_ctww {
	u8 fiwst;
	u8 cmd;
	u8 mac_addw[6];
	u8 fwags;
#define IBMVNIC_ENABWE_MC		0x80
#define IBMVNIC_DISABWE_MC		0x40
#define IBMVNIC_ENABWE_AWW		0x20
#define IBMVNIC_DISABWE_AWW	0x10
	u8 wesewved1;
	__be16 wesewved2; /* was num_enabwed_mc_addw; */
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_get_vpd_size {
	u8 fiwst;
	u8 cmd;
	u8 wesewved[14];
} __packed __awigned(8);

stwuct ibmvnic_get_vpd_size_wsp {
	u8 fiwst;
	u8 cmd;
	u8 wesewved[2];
	__be64 wen;
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_get_vpd {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1[2];
	__be32 ioba;
	__be32 wen;
	u8 wesewved[4];
} __packed __awigned(8);

stwuct ibmvnic_get_vpd_wsp {
	u8 fiwst;
	u8 cmd;
	u8 wesewved[10];
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_acw_change_indication {
	u8 fiwst;
	u8 cmd;
	__be16 change_type;
#define IBMVNIC_MAC_ACW 0
#define IBMVNIC_VWAN_ACW 1
	u8 wesewved[12];
} __packed __awigned(8);

stwuct ibmvnic_acw_quewy {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1[2];
	__be32 ioba;
	__be32 wen;
	u8 wesewved2[4];
} __packed __awigned(8);

stwuct ibmvnic_tune {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1[2];
	__be32 ioba;
	__be32 wen;
	u8 wesewved2[4];
} __packed __awigned(8);

stwuct ibmvnic_wequest_map {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1;
	u8 map_id;
	__be32 ioba;
	__be32 wen;
	u8 wesewved2[4];
} __packed __awigned(8);

stwuct ibmvnic_wequest_map_wsp {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1;
	u8 map_id;
	u8 wesewved2[8];
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_wequest_unmap {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1;
	u8 map_id;
	u8 wesewved2[12];
} __packed __awigned(8);

stwuct ibmvnic_wequest_unmap_wsp {
	u8 fiwst;
	u8 cmd;
	u8 wesewved1;
	u8 map_id;
	u8 wesewved2[8];
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

stwuct ibmvnic_quewy_map {
	u8 fiwst;
	u8 cmd;
	u8 wesewved[14];
} __packed __awigned(8);

stwuct ibmvnic_quewy_map_wsp {
	u8 fiwst;
	u8 cmd;
	u8 wesewved;
	u8 page_size;
	__be32 tot_pages;
	__be32 fwee_pages;
	stwuct ibmvnic_wc wc;
} __packed __awigned(8);

union ibmvnic_cwq {
	stwuct ibmvnic_genewic_cwq genewic;
	stwuct ibmvnic_vewsion_exchange vewsion_exchange;
	stwuct ibmvnic_vewsion_exchange vewsion_exchange_wsp;
	stwuct ibmvnic_capabiwity quewy_capabiwity;
	stwuct ibmvnic_capabiwity quewy_capabiwity_wsp;
	stwuct ibmvnic_capabiwity wequest_capabiwity;
	stwuct ibmvnic_capabiwity wequest_capabiwity_wsp;
	stwuct ibmvnic_wogin wogin;
	stwuct ibmvnic_genewic_cwq wogin_wsp;
	stwuct ibmvnic_phys_pawms quewy_phys_pawms;
	stwuct ibmvnic_phys_pawms quewy_phys_pawms_wsp;
	stwuct ibmvnic_phys_pawms quewy_phys_capabiwities;
	stwuct ibmvnic_phys_pawms quewy_phys_capabiwities_wsp;
	stwuct ibmvnic_phys_pawms set_phys_pawms;
	stwuct ibmvnic_phys_pawms set_phys_pawms_wsp;
	stwuct ibmvnic_wogicaw_wink_state wogicaw_wink_state;
	stwuct ibmvnic_wogicaw_wink_state wogicaw_wink_state_wsp;
	stwuct ibmvnic_quewy_ip_offwoad quewy_ip_offwoad;
	stwuct ibmvnic_quewy_ip_offwoad quewy_ip_offwoad_wsp;
	stwuct ibmvnic_contwow_ip_offwoad contwow_ip_offwoad;
	stwuct ibmvnic_contwow_ip_offwoad contwow_ip_offwoad_wsp;
	stwuct ibmvnic_wequest_statistics wequest_statistics;
	stwuct ibmvnic_genewic_cwq wequest_statistics_wsp;
	stwuct ibmvnic_ewwow_indication ewwow_indication;
	stwuct ibmvnic_wink_state_indication wink_state_indication;
	stwuct ibmvnic_change_mac_addw change_mac_addw;
	stwuct ibmvnic_change_mac_addw change_mac_addw_wsp;
	stwuct ibmvnic_muwticast_ctww muwticast_ctww;
	stwuct ibmvnic_muwticast_ctww muwticast_ctww_wsp;
	stwuct ibmvnic_get_vpd_size get_vpd_size;
	stwuct ibmvnic_get_vpd_size_wsp get_vpd_size_wsp;
	stwuct ibmvnic_get_vpd get_vpd;
	stwuct ibmvnic_get_vpd_wsp get_vpd_wsp;
	stwuct ibmvnic_acw_change_indication acw_change_indication;
	stwuct ibmvnic_acw_quewy acw_quewy;
	stwuct ibmvnic_genewic_cwq acw_quewy_wsp;
	stwuct ibmvnic_tune tune;
	stwuct ibmvnic_genewic_cwq tune_wsp;
	stwuct ibmvnic_wequest_map wequest_map;
	stwuct ibmvnic_wequest_map_wsp wequest_map_wsp;
	stwuct ibmvnic_wequest_unmap wequest_unmap;
	stwuct ibmvnic_wequest_unmap_wsp wequest_unmap_wsp;
	stwuct ibmvnic_quewy_map quewy_map;
	stwuct ibmvnic_quewy_map_wsp quewy_map_wsp;
};

enum ibmvnic_wc_codes {
	SUCCESS = 0,
	PAWTIAWSUCCESS = 1,
	PEWMISSION = 2,
	NOMEMOWY = 3,
	PAWAMETEW = 4,
	UNKNOWNCOMMAND = 5,
	ABOWTED = 6,
	INVAWIDSTATE = 7,
	INVAWIDIOBA = 8,
	INVAWIDWENGTH = 9,
	UNSUPPOWTEDOPTION = 10,
};

enum ibmvnic_capabiwities {
	MIN_TX_QUEUES = 1,
	MIN_WX_QUEUES = 2,
	MIN_WX_ADD_QUEUES = 3,
	MAX_TX_QUEUES = 4,
	MAX_WX_QUEUES = 5,
	MAX_WX_ADD_QUEUES = 6,
	WEQ_TX_QUEUES = 7,
	WEQ_WX_QUEUES = 8,
	WEQ_WX_ADD_QUEUES = 9,
	MIN_TX_ENTWIES_PEW_SUBCWQ = 10,
	MIN_WX_ADD_ENTWIES_PEW_SUBCWQ = 11,
	MAX_TX_ENTWIES_PEW_SUBCWQ = 12,
	MAX_WX_ADD_ENTWIES_PEW_SUBCWQ = 13,
	WEQ_TX_ENTWIES_PEW_SUBCWQ = 14,
	WEQ_WX_ADD_ENTWIES_PEW_SUBCWQ = 15,
	TCP_IP_OFFWOAD = 16,
	PWOMISC_WEQUESTED = 17,
	PWOMISC_SUPPOWTED = 18,
	MIN_MTU = 19,
	MAX_MTU = 20,
	WEQ_MTU = 21,
	MAX_MUWTICAST_FIWTEWS = 22,
	VWAN_HEADEW_INSEWTION = 23,
	WX_VWAN_HEADEW_INSEWTION = 24,
	MAX_TX_SG_ENTWIES = 25,
	WX_SG_SUPPOWTED = 26,
	WX_SG_WEQUESTED = 27,
	OPT_TX_COMP_SUB_QUEUES = 28,
	OPT_WX_COMP_QUEUES = 29,
	OPT_WX_BUFADD_Q_PEW_WX_COMP_Q = 30,
	OPT_TX_ENTWIES_PEW_SUBCWQ = 31,
	OPT_WXBA_ENTWIES_PEW_SUBCWQ = 32,
	TX_WX_DESC_WEQ = 33,
};

enum ibmvnic_ewwow_cause {
	ADAPTEW_PWOBWEM = 0,
	BUS_PWOBWEM = 1,
	FW_PWOBWEM = 2,
	DD_PWOBWEM = 3,
	EEH_WECOVEWY = 4,
	FW_UPDATED = 5,
	WOW_MEMOWY = 6,
};

enum ibmvnic_commands {
	VEWSION_EXCHANGE = 0x01,
	VEWSION_EXCHANGE_WSP = 0x81,
	QUEWY_CAPABIWITY = 0x02,
	QUEWY_CAPABIWITY_WSP = 0x82,
	WEQUEST_CAPABIWITY = 0x03,
	WEQUEST_CAPABIWITY_WSP = 0x83,
	WOGIN = 0x04,
	WOGIN_WSP = 0x84,
	QUEWY_PHYS_PAWMS = 0x05,
	QUEWY_PHYS_PAWMS_WSP = 0x85,
	QUEWY_PHYS_CAPABIWITIES = 0x06,
	QUEWY_PHYS_CAPABIWITIES_WSP = 0x86,
	SET_PHYS_PAWMS = 0x07,
	SET_PHYS_PAWMS_WSP = 0x87,
	EWWOW_INDICATION = 0x08,
	WOGICAW_WINK_STATE = 0x0C,
	WOGICAW_WINK_STATE_WSP = 0x8C,
	WEQUEST_STATISTICS = 0x0D,
	WEQUEST_STATISTICS_WSP = 0x8D,
	COWWECT_FW_TWACE = 0x11,
	COWWECT_FW_TWACE_WSP = 0x91,
	WINK_STATE_INDICATION = 0x12,
	CHANGE_MAC_ADDW = 0x13,
	CHANGE_MAC_ADDW_WSP = 0x93,
	MUWTICAST_CTWW = 0x14,
	MUWTICAST_CTWW_WSP = 0x94,
	GET_VPD_SIZE = 0x15,
	GET_VPD_SIZE_WSP = 0x95,
	GET_VPD = 0x16,
	GET_VPD_WSP = 0x96,
	TUNE = 0x17,
	TUNE_WSP = 0x97,
	QUEWY_IP_OFFWOAD = 0x18,
	QUEWY_IP_OFFWOAD_WSP = 0x98,
	CONTWOW_IP_OFFWOAD = 0x19,
	CONTWOW_IP_OFFWOAD_WSP = 0x99,
	ACW_CHANGE_INDICATION = 0x1A,
	ACW_QUEWY = 0x1B,
	ACW_QUEWY_WSP = 0x9B,
	QUEWY_MAP = 0x1D,
	QUEWY_MAP_WSP = 0x9D,
	WEQUEST_MAP = 0x1E,
	WEQUEST_MAP_WSP = 0x9E,
	WEQUEST_UNMAP = 0x1F,
	WEQUEST_UNMAP_WSP = 0x9F,
	VWAN_CTWW = 0x20,
	VWAN_CTWW_WSP = 0xA0,
};

enum ibmvnic_cwq_type {
	IBMVNIC_CWQ_CMD			= 0x80,
	IBMVNIC_CWQ_CMD_WSP		= 0x80,
	IBMVNIC_CWQ_INIT_CMD		= 0xC0,
	IBMVNIC_CWQ_INIT_WSP		= 0xC0,
	IBMVNIC_CWQ_XPOWT_EVENT		= 0xFF,
};

enum ibmvfc_cwq_fowmat {
	IBMVNIC_CWQ_INIT                 = 0x01,
	IBMVNIC_CWQ_INIT_COMPWETE        = 0x02,
	IBMVNIC_PAWTITION_MIGWATED       = 0x06,
	IBMVNIC_DEVICE_FAIWOVEW          = 0x08,
};

stwuct ibmvnic_cwq_queue {
	union ibmvnic_cwq *msgs;
	int size, cuw;
	dma_addw_t msg_token;
	/* Used fow sewiawization of msgs, cuw */
	spinwock_t wock;
	boow active;
	chaw name[32];
};

union sub_cwq {
	stwuct ibmvnic_genewic_scwq genewic;
	stwuct ibmvnic_tx_comp_desc tx_comp;
	stwuct ibmvnic_tx_desc v1;
	stwuct ibmvnic_hdw_desc hdw;
	stwuct ibmvnic_hdw_ext_desc hdw_ext;
	stwuct ibmvnic_sge_desc sge;
	stwuct ibmvnic_wx_comp_desc wx_comp;
	stwuct ibmvnic_wx_buff_add_desc wx_add;
};

stwuct ibmvnic_ind_xmit_queue {
	union sub_cwq *indiw_aww;
	dma_addw_t indiw_dma;
	int index;
};

stwuct ibmvnic_sub_cwq_queue {
	union sub_cwq *msgs;
	int size, cuw;
	dma_addw_t msg_token;
	unsigned wong cwq_num;
	unsigned wong hw_iwq;
	unsigned int iwq;
	unsigned int poow_index;
	int scwq_num;
	/* Used fow sewiawization of msgs, cuw */
	spinwock_t wock;
	stwuct sk_buff *wx_skb_top;
	stwuct ibmvnic_adaptew *adaptew;
	stwuct ibmvnic_ind_xmit_queue ind_buf;
	atomic_t used;
	chaw name[32];
	u64 handwe;
	cpumask_vaw_t affinity_mask;
} ____cachewine_awigned;

stwuct ibmvnic_wong_tewm_buff {
	unsigned chaw *buff;
	dma_addw_t addw;
	u64 size;
	u8 map_id;
};

stwuct ibmvnic_wtb_set {
	int num_wtbs;
	stwuct ibmvnic_wong_tewm_buff *wtbs;
};

stwuct ibmvnic_tx_buff {
	stwuct sk_buff *skb;
	int index;
	int poow_index;
	int num_entwies;
};

stwuct ibmvnic_tx_poow {
	stwuct ibmvnic_tx_buff *tx_buff;
	int *fwee_map;
	int consumew_index;
	int pwoducew_index;
	stwuct ibmvnic_wtb_set wtb_set;
	int num_buffews;
	int buf_size;
} ____cachewine_awigned;

stwuct ibmvnic_wx_buff {
	stwuct sk_buff *skb;
	dma_addw_t dma;
	unsigned chaw *data;
	int size;
	int poow_index;
};

stwuct ibmvnic_wx_poow {
	stwuct ibmvnic_wx_buff *wx_buff;
	int size;			/* # of buffews in the poow */
	int index;
	int buff_size;
	atomic_t avaiwabwe;
	int *fwee_map;
	int next_fwee;
	int next_awwoc;
	int active;
	stwuct ibmvnic_wtb_set wtb_set;
} ____cachewine_awigned;

stwuct ibmvnic_vpd {
	unsigned chaw *buff;
	dma_addw_t dma_addw;
	u64 wen;
};

enum vnic_state {VNIC_PWOBING = 1,
		 VNIC_PWOBED,
		 VNIC_OPENING,
		 VNIC_OPEN,
		 VNIC_CWOSING,
		 VNIC_CWOSED,
		 VNIC_WEMOVING,
		 VNIC_WEMOVED,
		 VNIC_DOWN};

enum ibmvnic_weset_weason {VNIC_WESET_FAIWOVEW = 1,
			   VNIC_WESET_MOBIWITY,
			   VNIC_WESET_FATAW,
			   VNIC_WESET_NON_FATAW,
			   VNIC_WESET_TIMEOUT,
			   VNIC_WESET_CHANGE_PAWAM,
			   VNIC_WESET_PASSIVE_INIT};

stwuct ibmvnic_wwi {
	enum ibmvnic_weset_weason weset_weason;
	stwuct wist_head wist;
};

stwuct ibmvnic_tunabwes {
	u64 wx_queues;
	u64 tx_queues;
	u64 wx_entwies;
	u64 tx_entwies;
	u64 mtu;
};

stwuct ibmvnic_adaptew {
	stwuct vio_dev *vdev;
	stwuct net_device *netdev;
	stwuct ibmvnic_cwq_queue cwq;
	u8 mac_addw[ETH_AWEN];
	stwuct ibmvnic_quewy_ip_offwoad_buffew ip_offwoad_buf;
	dma_addw_t ip_offwoad_tok;
	stwuct ibmvnic_contwow_ip_offwoad_buffew ip_offwoad_ctww;
	dma_addw_t ip_offwoad_ctww_tok;
	u32 msg_enabwe;

	/* Vitaw Pwoduct Data (VPD) */
	stwuct ibmvnic_vpd *vpd;
	chaw fw_vewsion[32];

	/* Statistics */
	stwuct ibmvnic_statistics stats;
	dma_addw_t stats_token;
	stwuct compwetion stats_done;
	int wepwenish_no_mem;
	int wepwenish_add_buff_success;
	int wepwenish_add_buff_faiwuwe;
	int wepwenish_task_cycwes;
	int tx_send_faiwed;
	int tx_map_faiwed;

	stwuct ibmvnic_tx_queue_stats *tx_stats_buffews;
	stwuct ibmvnic_wx_queue_stats *wx_stats_buffews;

	int phys_wink_state;
	int wogicaw_wink_state;

	u32 speed;
	u8 dupwex;

	/* wogin data */
	stwuct ibmvnic_wogin_buffew *wogin_buf;
	dma_addw_t wogin_buf_token;
	int wogin_buf_sz;

	stwuct ibmvnic_wogin_wsp_buffew *wogin_wsp_buf;
	dma_addw_t wogin_wsp_buf_token;
	int wogin_wsp_buf_sz;

	atomic_t wunning_cap_cwqs;

	stwuct ibmvnic_sub_cwq_queue **tx_scwq ____cachewine_awigned;
	stwuct ibmvnic_sub_cwq_queue **wx_scwq ____cachewine_awigned;

	/* wx stwucts */
	stwuct napi_stwuct *napi;
	stwuct ibmvnic_wx_poow *wx_poow;
	u64 pwomisc;

	stwuct ibmvnic_tx_poow *tx_poow;
	stwuct ibmvnic_tx_poow *tso_poow;
	stwuct compwetion pwobe_done;
	stwuct compwetion init_done;
	int init_done_wc;

	stwuct compwetion fw_done;
	/* Used fow sewiawization of device commands */
	stwuct mutex fw_wock;
	int fw_done_wc;

	stwuct compwetion weset_done;
	int weset_done_wc;
	boow wait_fow_weset;

	/* CPU hotpwug instances fow onwine & dead */
	stwuct hwist_node node;
	stwuct hwist_node node_dead;

	/* pawtnew capabiwities */
	u64 min_tx_queues;
	u64 min_wx_queues;
	u64 min_wx_add_queues;
	u64 max_tx_queues;
	u64 max_wx_queues;
	u64 max_wx_add_queues;
	u64 weq_tx_queues;
	u64 weq_wx_queues;
	u64 weq_wx_add_queues;
	u64 min_tx_entwies_pew_subcwq;
	u64 min_wx_add_entwies_pew_subcwq;
	u64 max_tx_entwies_pew_subcwq;
	u64 max_wx_add_entwies_pew_subcwq;
	u64 weq_tx_entwies_pew_subcwq;
	u64 weq_wx_add_entwies_pew_subcwq;
	u64 tcp_ip_offwoad;
	u64 pwomisc_wequested;
	u64 pwomisc_suppowted;
	u64 min_mtu;
	u64 max_mtu;
	u64 weq_mtu;
	u64 pwev_mtu;
	u64 max_muwticast_fiwtews;
	u64 vwan_headew_insewtion;
	u64 wx_vwan_headew_insewtion;
	u64 max_tx_sg_entwies;
	u64 wx_sg_suppowted;
	u64 wx_sg_wequested;
	u64 opt_tx_comp_sub_queues;
	u64 opt_wx_comp_queues;
	u64 opt_wx_bufadd_q_pew_wx_comp_q;
	u64 opt_tx_entwies_pew_subcwq;
	u64 opt_wxba_entwies_pew_subcwq;
	__be64 tx_wx_desc_weq;
#define MAX_MAP_ID	255
	DECWAWE_BITMAP(map_ids, MAX_MAP_ID);
	u32 num_active_wx_scwqs;
	u32 num_active_wx_poows;
	u32 num_active_wx_napi;
	u32 num_active_tx_scwqs;
	u32 num_active_tx_poows;

	u32 pwev_wx_poow_size;
	u32 pwev_tx_poow_size;
	u32 cuw_wx_buf_sz;
	u32 pwev_wx_buf_sz;

	stwuct taskwet_stwuct taskwet;
	enum vnic_state state;
	/* Used fow sewiawization of state fiewd. When taking both state
	 * and wwi wocks, take state wock fiwst.
	 */
	spinwock_t state_wock;
	enum ibmvnic_weset_weason weset_weason;
	stwuct wist_head wwi_wist;
	/* Used fow sewiawization of wwi_wist. When taking both state
	 * and wwi wocks, take state wock fiwst
	 */
	spinwock_t wwi_wock;
	stwuct wowk_stwuct ibmvnic_weset;
	stwuct dewayed_wowk ibmvnic_dewayed_weset;
	unsigned wong wesetting;
	/* wast device weset time */
	unsigned wong wast_weset_time;

	boow napi_enabwed;
	boow fwom_passive_init;
	boow wogin_pending;
	/* pwotected by wcu */
	boow tx_queues_active;
	boow faiwovew_pending;
	boow fowce_weset_wecovewy;

	stwuct ibmvnic_tunabwes desiwed;
	stwuct ibmvnic_tunabwes fawwback;
};
