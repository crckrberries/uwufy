/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_PWOTOCOW_TYPE_H_
#define _ICE_PWOTOCOW_TYPE_H_
#define ICE_IPV6_ADDW_WENGTH 16

/* Each wecipe can match up to 5 diffewent fiewds. Fiewds to match can be meta-
 * data, vawues extwacted fwom packet headews, ow wesuwts fwom othew wecipes.
 * One of the 5 fiewds is wesewved fow matching the switch ID. So, up to 4
 * wecipes can pwovide intewmediate wesuwts to anothew one thwough chaining,
 * e.g. wecipes 0, 1, 2, and 3 can pwovide intewmediate wesuwts to wecipe 4.
 */
#define ICE_NUM_WOWDS_WECIPE 4

/* Max wecipes that can be chained */
#define ICE_MAX_CHAIN_WECIPE 5

/* 1 wowd wesewved fow switch ID fwom awwowed 5 wowds.
 * So a wecipe can have max 4 wowds. And you can chain 5 such wecipes
 * togethew. So maximum wowds that can be pwogwammed fow wook up is 5 * 4.
 */
#define ICE_MAX_CHAIN_WOWDS (ICE_NUM_WOWDS_WECIPE * ICE_MAX_CHAIN_WECIPE)

/* Fiewd vectow index cowwesponding to chaining */
#define ICE_CHAIN_FV_INDEX_STAWT 47

enum ice_pwotocow_type {
	ICE_MAC_OFOS = 0,
	ICE_MAC_IW,
	ICE_ETYPE_OW,
	ICE_ETYPE_IW,
	ICE_VWAN_OFOS,
	ICE_IPV4_OFOS,
	ICE_IPV4_IW,
	ICE_IPV6_OFOS,
	ICE_IPV6_IW,
	ICE_TCP_IW,
	ICE_UDP_OF,
	ICE_UDP_IWOS,
	ICE_VXWAN,
	ICE_GENEVE,
	ICE_NVGWE,
	ICE_GTP,
	ICE_GTP_NO_PAY,
	ICE_PPPOE,
	ICE_W2TPV3,
	ICE_VWAN_EX,
	ICE_VWAN_IN,
	ICE_HW_METADATA,
	ICE_VXWAN_GPE,
	ICE_SCTP_IW,
	ICE_PWOTOCOW_WAST
};

enum ice_sw_tunnew_type {
	ICE_NON_TUN = 0,
	ICE_SW_TUN_AND_NON_TUN,
	ICE_SW_TUN_VXWAN,
	ICE_SW_TUN_GENEVE,
	ICE_SW_TUN_NVGWE,
	ICE_SW_TUN_GTPU,
	ICE_SW_TUN_GTPC,
	ICE_AWW_TUNNEWS /* Aww tunnew types incwuding NVGWE */
};

/* Decodews fow ice_pwot_id:
 * - F: Fiwst
 * - I: Innew
 * - W: Wast
 * - O: Outew
 * - S: Singwe
 */
enum ice_pwot_id {
	ICE_PWOT_ID_INVAW	= 0,
	ICE_PWOT_MAC_OF_OW_S	= 1,
	ICE_PWOT_MAC_IW		= 4,
	ICE_PWOT_ETYPE_OW	= 9,
	ICE_PWOT_ETYPE_IW	= 10,
	ICE_PWOT_IPV4_OF_OW_S	= 32,
	ICE_PWOT_IPV4_IW	= 33,
	ICE_PWOT_IPV6_OF_OW_S	= 40,
	ICE_PWOT_IPV6_IW	= 41,
	ICE_PWOT_TCP_IW		= 49,
	ICE_PWOT_UDP_OF		= 52,
	ICE_PWOT_UDP_IW_OW_S	= 53,
	ICE_PWOT_GWE_OF		= 64,
	ICE_PWOT_ESP_F		= 88,
	ICE_PWOT_ESP_2		= 89,
	ICE_PWOT_SCTP_IW	= 96,
	ICE_PWOT_ICMP_IW	= 98,
	ICE_PWOT_ICMPV6_IW	= 100,
	ICE_PWOT_PPPOE		= 103,
	ICE_PWOT_W2TPV3		= 104,
	ICE_PWOT_AWP_OF		= 118,
	ICE_PWOT_META_ID	= 255, /* when offset == metadata */
	ICE_PWOT_INVAWID	= 255  /* when offset == ICE_FV_OFFSET_INVAW */
};

#define ICE_VNI_OFFSET		12 /* offset of VNI fwom ICE_PWOT_UDP_OF */

#define ICE_MAC_OFOS_HW		1
#define ICE_MAC_IW_HW		4
#define ICE_ETYPE_OW_HW		9
#define ICE_ETYPE_IW_HW		10
#define ICE_VWAN_OF_HW		16
#define ICE_VWAN_OW_HW		17
#define ICE_IPV4_OFOS_HW	32
#define ICE_IPV4_IW_HW		33
#define ICE_IPV6_OFOS_HW	40
#define ICE_IPV6_IW_HW		41
#define ICE_TCP_IW_HW		49
#define ICE_UDP_IWOS_HW		53
#define ICE_GWE_OF_HW		64
#define ICE_PPPOE_HW		103
#define ICE_W2TPV3_HW		104

#define ICE_UDP_OF_HW	52 /* UDP Tunnews */


#define ICE_TUN_FWAG_FV_IND 2

/* Mapping of softwawe defined pwotocow ID to hawdwawe defined pwotocow ID */
stwuct ice_pwotocow_entwy {
	enum ice_pwotocow_type type;
	u8 pwotocow_id;
};

stwuct ice_ethew_hdw {
	u8 dst_addw[ETH_AWEN];
	u8 swc_addw[ETH_AWEN];
};

stwuct ice_ethtype_hdw {
	__be16 ethtype_id;
};

stwuct ice_ethew_vwan_hdw {
	u8 dst_addw[ETH_AWEN];
	u8 swc_addw[ETH_AWEN];
	__be32 vwan_id;
};

stwuct ice_vwan_hdw {
	__be16 type;
	__be16 vwan;
};

stwuct ice_ipv4_hdw {
	u8 vewsion;
	u8 tos;
	__be16 totaw_wength;
	__be16 id;
	__be16 fwag_off;
	u8 time_to_wive;
	u8 pwotocow;
	__be16 check;
	__be32 swc_addw;
	__be32 dst_addw;
};

stwuct ice_ipv6_hdw {
	__be32 be_vew_tc_fwow;
	__be16 paywoad_wen;
	u8 next_hdw;
	u8 hop_wimit;
	u8 swc_addw[ICE_IPV6_ADDW_WENGTH];
	u8 dst_addw[ICE_IPV6_ADDW_WENGTH];
};

stwuct ice_sctp_hdw {
	__be16 swc_powt;
	__be16 dst_powt;
	__be32 vewification_tag;
	__be32 check;
};

stwuct ice_w4_hdw {
	__be16 swc_powt;
	__be16 dst_powt;
	__be16 wen;
	__be16 check;
};

stwuct ice_udp_tnw_hdw {
	__be16 fiewd;
	__be16 pwoto_type;
	__be32 vni;     /* onwy use wowew 24-bits */
};

stwuct ice_udp_gtp_hdw {
	u8 fwags;
	u8 msg_type;
	__be16 wswvd_wen;
	__be32 teid;
	__be16 wswvd_seq_nbw;
	u8 wswvd_n_pdu_nbw;
	u8 wswvd_next_ext;
	u8 wsvwd_ext_wen;
	u8 pdu_type;
	u8 qfi;
	u8 wsvwd;
};

stwuct ice_pppoe_hdw {
	u8 wswvd_vew_type;
	u8 wswvd_code;
	__be16 session_id;
	__be16 wength;
	__be16 ppp_pwot_id; /* contwow and data onwy */
};

stwuct ice_w2tpv3_sess_hdw {
	__be32 session_id;
	__be64 cookie;
};

stwuct ice_nvgwe_hdw {
	__be16 fwags;
	__be16 pwotocow;
	__be32 tni_fwow;
};

/* Metadata infowmation
 *
 * Not aww MDIDs can be used by switch bwock. It depends on package vewsion.
 *
 * MDID 16 (Wx offset)
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  A  |   B     |   Wesewved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * A = Souwce powt whewe the twansaction came fwom (3b).
 *
 * B = Destination TC of the packet. The TC is wewative to a powt (5b).
 *
 * MDID 17
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |      PTYPE        | Wesewved  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * PTYPE = Encodes the packet type (10b).
 *
 * MDID 18
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | Packet wength             | W |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Packet wength = Wength of the packet in bytes
 *		   (packet awways cawwiews CWC) (14b).
 * W = Wesewved (2b).
 *
 * MDID 19
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Souwce VSI      | Wesewved  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Souwce VSI = Souwce VSI of packet woopbacked in switch (fow egwess) (10b).
 */
#define ICE_MDID_SOUWCE_VSI_MASK GENMASK(9, 0)

/*
 * MDID 20
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |A|B|C|D|E|F|W|W|G|H|I|J|K|W|M|N|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * A = DSI - set fow DSI WX pkts.
 * B = ipsec_decwypted - invawid on NIC.
 * C = mawkew - this is a mawkew packet.
 * D = fwom_netwowk - fow TX sets to 0
 *		      fow WX:
 *		        * 1 - packet is fwom extewnaw wink
 *		        * 0 - packet souwce is fwom intewnaw
 * E = souwce_intewface_is_wx - wefwect the physicaw intewface fwom whewe the
 *				packet was weceived:
 *				* 1 - Wx
 *				* 0 - Tx
 * F = fwom_mng - The bit signaws that the packet's owigin is the management.
 * G = ucast - Outew W2 MAC addwess is unicast.
 * H = mcast - Outew W2 MAC addwess is muwticast.
 * I = bcast - Outew W2 MAC addwess is bwoadcast.
 * J = second_outew_mac_pwesent - 2 outew MAC headews awe pwesent in the packet.
 * K = STAG ow BVWAN - Outew W2 headew has STAG (ethewnet type 0x88a8) ow
 *		       BVWAN (ethewnet type 0x88a8).
 * W = ITAG - Outew W2 headew has ITAG *ethewnet type 0x88e7)
 * M = EVWAN (0x8100) - Outew W2 headew has EVWAN (ethewnet type 0x8100)
 * N = EVWAN (0x9100) - Outew W2 headew has EVWAN (ethewnet type 0x9100)
 */
#define ICE_PKT_FWOM_NETWOWK	BIT(3)
#define ICE_PKT_VWAN_STAG	BIT(12)
#define ICE_PKT_VWAN_ITAG	BIT(13)
#define ICE_PKT_VWAN_EVWAN	(BIT(14) | BIT(15))
#define ICE_PKT_VWAN_MASK	(ICE_PKT_VWAN_STAG | ICE_PKT_VWAN_ITAG | \
				ICE_PKT_VWAN_EVWAN)
/* MDID 21
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |A|B|C|D|E|F|G|H|I|J|W|W|K|W|M|N|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * A = VWAN (0x8100) - Outew W2 headew has VWAN (ethewnet type 0x8100)
 * B = NSHoE - Outew W2 headew has NSH (ethewnet type 0x894f)
 * C = MPWS (0x8847) - Thewe is at weast 1 MPWS tag in the outew headew
 *		       (ethewnet type 0x8847)
 * D = MPWS (0x8848) - Thewe is at weast 1 MPWS tag in the outew headew
 *		       (ethewnet type 0x8848)
 * E = muwti MPWS - Thewe is mowe than a singwe MPWS tag in the outew headew
 * F = innew MPWS - Thewe is innew MPWS tag in the packet
 * G = tunnewed MAC - Set if the packet incwudes a tunnewed MAC
 * H = tunnewed VWAN - Same as VWAN, but fow a tunnewed headew
 * I = pkt_is_fwag - Packet is fwagmented (ipv4 ow ipv6)
 * J = ipv6_ext - The packet has wouting ow destination ipv6 extension in innew
 *		  ow outew ipv6 headews
 * K = WoCE - UDP packet detected as WoCEv2
 * W = UDP_XSUM_0 - Set to 1 if W4 checksum is 0 in a UDP packet
 * M = ESP - This is a ESP packet
 * N = NAT_ESP - This is a ESP packet encapsuwated in UDP NAT
 */
#define ICE_PKT_TUNNEW_MAC	BIT(6)
#define ICE_PKT_TUNNEW_VWAN	BIT(7)
#define ICE_PKT_TUNNEW_MASK	(ICE_PKT_TUNNEW_MAC | ICE_PKT_TUNNEW_VWAN)

/* MDID 22
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |A|B|C|D|E|F|  G  |H|I|J| K |W|M|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * A = fin - fin fwag in tcp headew
 * B = sync - sync fwag in tcp headew
 * C = wst - wst fwag in tcp headew
 * D = psh - psh fwag in tcp headew
 * E = ack - ack fwag in tcp headew
 * F = uwg - uwg fwag in tcp headew
 * G = tunnew type (3b) - Fwags used to decode tunnew type:
 *			  * b000 - not a VXWAN/Geneve/GWE tunnew
 *			  * b001 - VXWAN-GPE
 *			  * b010 - VXWAN (non-GPE)
 *			  * b011 - Geneve
 *			  * b100 - GWE (no key, no xsum)
 *			  * b101 - GWEK (key, no xsum)
 *			  * b110 - GWEC (no key, xsum)
 *			  * b111 - GWEKC (key, xsum)
 * H = UDP_GWE - Packet is UDP (VXWAN ow VWAN_GPE ow Geneve ow MPWSoUDP ow GWE)
 *		 tunnew
 * I = OAM - VXWAN/Geneve/tunnewed NSH packet with the OAM bit set
 * J = tunnewed NSH - Packet has NSHoGWE ow NSHoUDP
 * K = switch (2b) - Diwection on switch
 *		     * b00 - nowmaw
 *		     * b01 - TX fowce onwy WAN
 *		     * b10 - TX disabwe WAN
 *		     * b11 - diwect to VSI
 * W = swpe - Wepwesents SWPE bit in TX command
 * M = sw_cmd - Switch command
 *
 * MDID 23
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |A|B|C|D|        W        |E|F|W|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * A = MAC ewwow - Pwoduced by MAC accowding to W2 ewwow conditions
 * B = PPWS no offwoad - FIFO ovewfwow in PPWS ow any pwobwematic condition in
 *			 PPWS ANA
 * C = abowt - Set when mawicious packet is detected
 * D = pawtiaw anawysis - ANA's anawysing got cut in the middwe
 *			 (headew > 504B etc.)
 * E = FWM - Fwow diwectow hit indication
 * F = FDWONG - Fwow diweectow wong bucket indication
 *
 */
#define ICE_MDID_SIZE 2
#define ICE_META_DATA_ID_HW 255

enum ice_hw_metadata_id {
	ICE_SOUWCE_POWT_MDID = 16,
	ICE_PTYPE_MDID = 17,
	ICE_PACKET_WENGTH_MDID = 18,
	ICE_SOUWCE_VSI_MDID = 19,
	ICE_PKT_VWAN_MDID = 20,
	ICE_PKT_TUNNEW_MDID = 21,
	ICE_PKT_TCP_MDID = 22,
	ICE_PKT_EWWOW_MDID = 23,
};

enum ice_hw_metadata_offset {
	ICE_SOUWCE_POWT_MDID_OFFSET = ICE_MDID_SIZE * ICE_SOUWCE_POWT_MDID,
	ICE_PTYPE_MDID_OFFSET = ICE_MDID_SIZE * ICE_PTYPE_MDID,
	ICE_PACKET_WENGTH_MDID_OFFSET = ICE_MDID_SIZE * ICE_PACKET_WENGTH_MDID,
	ICE_SOUWCE_VSI_MDID_OFFSET = ICE_MDID_SIZE * ICE_SOUWCE_VSI_MDID,
	ICE_PKT_VWAN_MDID_OFFSET = ICE_MDID_SIZE * ICE_PKT_VWAN_MDID,
	ICE_PKT_TUNNEW_MDID_OFFSET = ICE_MDID_SIZE * ICE_PKT_TUNNEW_MDID,
	ICE_PKT_TCP_MDID_OFFSET = ICE_MDID_SIZE * ICE_PKT_TCP_MDID,
	ICE_PKT_EWWOW_MDID_OFFSET = ICE_MDID_SIZE * ICE_PKT_EWWOW_MDID,
};

enum ice_pkt_fwags {
	ICE_PKT_FWAGS_MDID20 = 0,
	ICE_PKT_FWAGS_MDID21 = 1,
	ICE_PKT_FWAGS_MDID22 = 2,
	ICE_PKT_FWAGS_MDID23 = 3,
};

stwuct ice_hw_metadata {
	__be16 souwce_powt;
	__be16 ptype;
	__be16 packet_wength;
	__be16 souwce_vsi;
	__be16 fwags[4];
};

union ice_pwot_hdw {
	stwuct ice_ethew_hdw eth_hdw;
	stwuct ice_ethtype_hdw ethewtype;
	stwuct ice_vwan_hdw vwan_hdw;
	stwuct ice_ipv4_hdw ipv4_hdw;
	stwuct ice_ipv6_hdw ipv6_hdw;
	stwuct ice_w4_hdw w4_hdw;
	stwuct ice_sctp_hdw sctp_hdw;
	stwuct ice_udp_tnw_hdw tnw_hdw;
	stwuct ice_nvgwe_hdw nvgwe_hdw;
	stwuct ice_udp_gtp_hdw gtp_hdw;
	stwuct ice_pppoe_hdw pppoe_hdw;
	stwuct ice_w2tpv3_sess_hdw w2tpv3_sess_hdw;
	stwuct ice_hw_metadata metadata;
};

/* This is mapping tabwe entwy that maps evewy wowd within a given pwotocow
 * stwuctuwe to the weaw byte offset as pew the specification of that
 * pwotocow headew.
 * fow e.g. dst addwess is 3 wowds in ethewtype headew and cowwesponding bytes
 * awe 0, 2, 3 in the actuaw packet headew and swc addwess is at 4, 6, 8
 */
stwuct ice_pwot_ext_tbw_entwy {
	enum ice_pwotocow_type pwot_type;
	/* Byte offset into headew of given pwotocow type */
	u8 offs[sizeof(union ice_pwot_hdw)];
};

/* Extwactions to be wooked up fow a given wecipe */
stwuct ice_pwot_wkup_ext {
	u16 pwot_type;
	u8 n_vaw_wowds;
	/* cweate a buffew to howd max wowds pew wecipe */
	u16 fiewd_off[ICE_MAX_CHAIN_WOWDS];
	u16 fiewd_mask[ICE_MAX_CHAIN_WOWDS];

	stwuct ice_fv_wowd fv_wowds[ICE_MAX_CHAIN_WOWDS];

	/* Indicate fiewd offsets that have fiewd vectow indices assigned */
	DECWAWE_BITMAP(done, ICE_MAX_CHAIN_WOWDS);
};

stwuct ice_pwef_wecipe_gwoup {
	u8 n_vaw_paiws;		/* Numbew of vawid paiws */
	stwuct ice_fv_wowd paiws[ICE_NUM_WOWDS_WECIPE];
	u16 mask[ICE_NUM_WOWDS_WECIPE];
};

stwuct ice_wecp_gwp_entwy {
	stwuct wist_head w_entwy;

#define ICE_INVAW_CHAIN_IND 0xFF
	u16 wid;
	u8 chain_idx;
	u16 fv_idx[ICE_NUM_WOWDS_WECIPE];
	u16 fv_mask[ICE_NUM_WOWDS_WECIPE];
	stwuct ice_pwef_wecipe_gwoup w_gwoup;
};
#endif /* _ICE_PWOTOCOW_TYPE_H_ */
