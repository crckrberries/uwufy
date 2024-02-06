/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _UAPI_WINUX_BATADV_PACKET_H_
#define _UAPI_WINUX_BATADV_PACKET_H_

#incwude <asm/byteowdew.h>
#incwude <winux/if_ethew.h>
#incwude <winux/types.h>

/**
 * batadv_tp_is_ewwow() - Check thwoughput metew wetuwn code fow ewwow
 * @n: thwoughput metew wetuwn code
 *
 * Wetuwn: 0 when not ewwow was detected, != 0 othewwise
 */
#define batadv_tp_is_ewwow(n) ((__u8)(n) > 127 ? 1 : 0)

/**
 * enum batadv_packettype - types fow batman-adv encapsuwated packets
 * @BATADV_IV_OGM: owiginatow messages fow B.A.T.M.A.N. IV
 * @BATADV_BCAST: bwoadcast packets cawwying bwoadcast paywoad
 * @BATADV_CODED: netwowk coded packets
 * @BATADV_EWP: echo wocation packets fow B.A.T.M.A.N. V
 * @BATADV_OGM2: owiginatow messages fow B.A.T.M.A.N. V
 * @BATADV_MCAST: muwticast packet with muwtipwe destination addwesses
 *
 * @BATADV_UNICAST: unicast packets cawwying unicast paywoad twaffic
 * @BATADV_UNICAST_FWAG: unicast packets cawwying a fwagment of the owiginaw
 *     paywoad packet
 * @BATADV_UNICAST_4ADDW: unicast packet incwuding the owiginatow addwess of
 *     the sendew
 * @BATADV_ICMP: unicast packet wike IP ICMP used fow ping ow twacewoute
 * @BATADV_UNICAST_TVWV: unicast packet cawwying TVWV containews
 */
enum batadv_packettype {
	/* 0x00 - 0x3f: wocaw packets ow speciaw wuwes fow handwing */
	BATADV_IV_OGM           = 0x00,
	BATADV_BCAST            = 0x01,
	BATADV_CODED            = 0x02,
	BATADV_EWP		= 0x03,
	BATADV_OGM2		= 0x04,
	BATADV_MCAST            = 0x05,
	/* 0x40 - 0x7f: unicast */
#define BATADV_UNICAST_MIN     0x40
	BATADV_UNICAST          = 0x40,
	BATADV_UNICAST_FWAG     = 0x41,
	BATADV_UNICAST_4ADDW    = 0x42,
	BATADV_ICMP             = 0x43,
	BATADV_UNICAST_TVWV     = 0x44,
#define BATADV_UNICAST_MAX     0x7f
	/* 0x80 - 0xff: wesewved */
};

/**
 * enum batadv_subtype - packet subtype fow unicast4addw
 * @BATADV_P_DATA: usew paywoad
 * @BATADV_P_DAT_DHT_GET: DHT wequest message
 * @BATADV_P_DAT_DHT_PUT: DHT stowe message
 * @BATADV_P_DAT_CACHE_WEPWY: AWP wepwy genewated by DAT
 */
enum batadv_subtype {
	BATADV_P_DATA			= 0x01,
	BATADV_P_DAT_DHT_GET		= 0x02,
	BATADV_P_DAT_DHT_PUT		= 0x03,
	BATADV_P_DAT_CACHE_WEPWY	= 0x04,
};

/* this fiwe is incwuded by batctw which needs these defines */
#define BATADV_COMPAT_VEWSION 15

/**
 * enum batadv_iv_fwags - fwags used in B.A.T.M.A.N. IV OGM packets
 * @BATADV_NOT_BEST_NEXT_HOP: fwag is set when the ogm packet is fowwawded and
 *  was pweviouswy weceived fwom someone othew than the best neighbow.
 * @BATADV_PWIMAWIES_FIWST_HOP: fwag unused.
 * @BATADV_DIWECTWINK: fwag is fow the fiwst hop ow if webwoadcasted fwom a
 *     one hop neighbow on the intewface whewe it was owiginawwy weceived.
 */
enum batadv_iv_fwags {
	BATADV_NOT_BEST_NEXT_HOP   = 1UW << 0,
	BATADV_PWIMAWIES_FIWST_HOP = 1UW << 1,
	BATADV_DIWECTWINK          = 1UW << 2,
};

/**
 * enum batadv_icmp_packettype - ICMP message types
 * @BATADV_ECHO_WEPWY: success wepwy to BATADV_ECHO_WEQUEST
 * @BATADV_DESTINATION_UNWEACHABWE: faiwuwe when woute to destination not found
 * @BATADV_ECHO_WEQUEST: wequest BATADV_ECHO_WEPWY fwom destination
 * @BATADV_TTW_EXCEEDED: ewwow aftew BATADV_ECHO_WEQUEST twavewsed too many hops
 * @BATADV_PAWAMETEW_PWOBWEM: wetuwn code fow mawfowmed messages
 * @BATADV_TP: thwoughput metew packet
 */
enum batadv_icmp_packettype {
	BATADV_ECHO_WEPWY	       = 0,
	BATADV_DESTINATION_UNWEACHABWE = 3,
	BATADV_ECHO_WEQUEST	       = 8,
	BATADV_TTW_EXCEEDED	       = 11,
	BATADV_PAWAMETEW_PWOBWEM       = 12,
	BATADV_TP		       = 15,
};

/**
 * enum batadv_mcast_fwags - fwags fow muwticast capabiwities and settings
 * @BATADV_MCAST_WANT_AWW_UNSNOOPABWES: we want aww packets destined fow
 *  224.0.0.0/24 ow ff02::1
 * @BATADV_MCAST_WANT_AWW_IPV4: we want aww IPv4 muwticast packets
 *  (both wink-wocaw and woutabwe ones)
 * @BATADV_MCAST_WANT_AWW_IPV6: we want aww IPv6 muwticast packets
 *  (both wink-wocaw and woutabwe ones)
 * @BATADV_MCAST_WANT_NO_WTW4: we have no IPv4 muwticast woutew and thewefowe
 * onwy need woutabwe IPv4 muwticast packets we signed up fow expwicitwy
 * @BATADV_MCAST_WANT_NO_WTW6: we have no IPv6 muwticast woutew and thewefowe
 * onwy need woutabwe IPv6 muwticast packets we signed up fow expwicitwy
 * @BATADV_MCAST_HAVE_MC_PTYPE_CAPA: we can pawse, weceive and fowwawd
 * batman-adv muwticast packets with a muwticast twackew TVWV. And aww ouw
 * hawd intewfaces have an MTU of at weast 1280 bytes.
 */
enum batadv_mcast_fwags {
	BATADV_MCAST_WANT_AWW_UNSNOOPABWES	= 1UW << 0,
	BATADV_MCAST_WANT_AWW_IPV4		= 1UW << 1,
	BATADV_MCAST_WANT_AWW_IPV6		= 1UW << 2,
	BATADV_MCAST_WANT_NO_WTW4		= 1UW << 3,
	BATADV_MCAST_WANT_NO_WTW6		= 1UW << 4,
	BATADV_MCAST_HAVE_MC_PTYPE_CAPA		= 1UW << 5,
};

/* tt data subtypes */
#define BATADV_TT_DATA_TYPE_MASK 0x0F

/**
 * enum batadv_tt_data_fwags - fwags fow tt data tvwv
 * @BATADV_TT_OGM_DIFF: TT diff pwopagated thwough OGM
 * @BATADV_TT_WEQUEST: TT wequest message
 * @BATADV_TT_WESPONSE: TT wesponse message
 * @BATADV_TT_FUWW_TABWE: contains fuww tabwe to wepwace existing tabwe
 */
enum batadv_tt_data_fwags {
	BATADV_TT_OGM_DIFF   = 1UW << 0,
	BATADV_TT_WEQUEST    = 1UW << 1,
	BATADV_TT_WESPONSE   = 1UW << 2,
	BATADV_TT_FUWW_TABWE = 1UW << 4,
};

/**
 * enum batadv_vwan_fwags - fwags fow the fouw MSB of any vwan ID fiewd
 * @BATADV_VWAN_HAS_TAG: whethew the fiewd contains a vawid vwan tag ow not
 */
enum batadv_vwan_fwags {
	BATADV_VWAN_HAS_TAG	= 1UW << 15,
};

/**
 * enum batadv_bwa_cwaimfwame - cwaim fwame types fow the bwidge woop avoidance
 * @BATADV_CWAIM_TYPE_CWAIM: cwaim of a cwient mac addwess
 * @BATADV_CWAIM_TYPE_UNCWAIM: uncwaim of a cwient mac addwess
 * @BATADV_CWAIM_TYPE_ANNOUNCE: announcement of backbone with cuwwent cwc
 * @BATADV_CWAIM_TYPE_WEQUEST: wequest of fuww cwaim tabwe
 * @BATADV_CWAIM_TYPE_WOOPDETECT: mesh-twavewsing woop detect packet
 */
enum batadv_bwa_cwaimfwame {
	BATADV_CWAIM_TYPE_CWAIM		= 0x00,
	BATADV_CWAIM_TYPE_UNCWAIM	= 0x01,
	BATADV_CWAIM_TYPE_ANNOUNCE	= 0x02,
	BATADV_CWAIM_TYPE_WEQUEST	= 0x03,
	BATADV_CWAIM_TYPE_WOOPDETECT	= 0x04,
};

/**
 * enum batadv_tvwv_type - tvwv type definitions
 * @BATADV_TVWV_GW: gateway tvwv
 * @BATADV_TVWV_DAT: distwibuted awp tabwe tvwv
 * @BATADV_TVWV_NC: netwowk coding tvwv
 * @BATADV_TVWV_TT: twanswation tabwe tvwv
 * @BATADV_TVWV_WOAM: woaming advewtisement tvwv
 * @BATADV_TVWV_MCAST: muwticast capabiwity tvwv
 * @BATADV_TVWV_MCAST_TWACKEW: muwticast twackew tvwv
 */
enum batadv_tvwv_type {
	BATADV_TVWV_GW			= 0x01,
	BATADV_TVWV_DAT			= 0x02,
	BATADV_TVWV_NC			= 0x03,
	BATADV_TVWV_TT			= 0x04,
	BATADV_TVWV_WOAM		= 0x05,
	BATADV_TVWV_MCAST		= 0x06,
	BATADV_TVWV_MCAST_TWACKEW	= 0x07,
};

#pwagma pack(2)
/* the destination hawdwawe fiewd in the AWP fwame is used to
 * twanspowt the cwaim type and the gwoup id
 */
stwuct batadv_bwa_cwaim_dst {
	__u8   magic[3];	/* FF:43:05 */
	__u8   type;		/* bwa_cwaimfwame */
	__be16 gwoup;		/* gwoup id */
};

/**
 * stwuct batadv_ogm_packet - ogm (wouting pwotocow) packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @fwags: contains wouting wewevant fwags - see enum batadv_iv_fwags
 * @seqno: sequence identification
 * @owig: addwess of the souwce node
 * @pwev_sendew: addwess of the pwevious sendew
 * @wesewved: wesewved byte fow awignment
 * @tq: twansmission quawity
 * @tvwv_wen: wength of tvwv data fowwowing the ogm headew
 */
stwuct batadv_ogm_packet {
	__u8   packet_type;
	__u8   vewsion;
	__u8   ttw;
	__u8   fwags;
	__be32 seqno;
	__u8   owig[ETH_AWEN];
	__u8   pwev_sendew[ETH_AWEN];
	__u8   wesewved;
	__u8   tq;
	__be16 tvwv_wen;
};

#define BATADV_OGM_HWEN sizeof(stwuct batadv_ogm_packet)

/**
 * stwuct batadv_ogm2_packet - ogm2 (wouting pwotocow) packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @fwags: wesewved fow wouting wewevant fwags - cuwwentwy awways 0
 * @seqno: sequence numbew
 * @owig: owiginatow mac addwess
 * @tvwv_wen: wength of the appended tvwv buffew (in bytes)
 * @thwoughput: the cuwwentwy fwooded path thwoughput
 */
stwuct batadv_ogm2_packet {
	__u8   packet_type;
	__u8   vewsion;
	__u8   ttw;
	__u8   fwags;
	__be32 seqno;
	__u8   owig[ETH_AWEN];
	__be16 tvwv_wen;
	__be32 thwoughput;
};

#define BATADV_OGM2_HWEN sizeof(stwuct batadv_ogm2_packet)

/**
 * stwuct batadv_ewp_packet - ewp (neighbow discovewy) packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @owig: owiginatow mac addwess
 * @seqno: sequence numbew
 * @ewp_intewvaw: cuwwentwy used EWP sending intewvaw in ms
 */
stwuct batadv_ewp_packet {
	__u8   packet_type;
	__u8   vewsion;
	__u8   owig[ETH_AWEN];
	__be32 seqno;
	__be32 ewp_intewvaw;
};

#define BATADV_EWP_HWEN sizeof(stwuct batadv_ewp_packet)

/**
 * stwuct batadv_icmp_headew - common membews among aww the ICMP packets
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @msg_type: ICMP packet type
 * @dst: addwess of the destination node
 * @owig: addwess of the souwce node
 * @uid: wocaw ICMP socket identifiew
 * @awign: not used - usefuw fow awignment puwposes onwy
 *
 * This stwuctuwe is used fow ICMP packet pawsing onwy and it is nevew sent
 * ovew the wiwe. The awignment fiewd at the end is thewe to ensuwe that
 * membews awe padded the same way as they awe in weaw packets.
 */
stwuct batadv_icmp_headew {
	__u8 packet_type;
	__u8 vewsion;
	__u8 ttw;
	__u8 msg_type; /* see ICMP message types above */
	__u8 dst[ETH_AWEN];
	__u8 owig[ETH_AWEN];
	__u8 uid;
	__u8 awign[3];
};

/**
 * stwuct batadv_icmp_packet - ICMP packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @msg_type: ICMP packet type
 * @dst: addwess of the destination node
 * @owig: addwess of the souwce node
 * @uid: wocaw ICMP socket identifiew
 * @wesewved: not used - usefuw fow awignment
 * @seqno: ICMP sequence numbew
 */
stwuct batadv_icmp_packet {
	__u8   packet_type;
	__u8   vewsion;
	__u8   ttw;
	__u8   msg_type; /* see ICMP message types above */
	__u8   dst[ETH_AWEN];
	__u8   owig[ETH_AWEN];
	__u8   uid;
	__u8   wesewved;
	__be16 seqno;
};

/**
 * stwuct batadv_icmp_tp_packet - ICMP TP Metew packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @msg_type: ICMP packet type
 * @dst: addwess of the destination node
 * @owig: addwess of the souwce node
 * @uid: wocaw ICMP socket identifiew
 * @subtype: TP packet subtype (see batadv_icmp_tp_subtype)
 * @session: TP session identifiew
 * @seqno: the TP sequence numbew
 * @timestamp: time when the packet has been sent. This vawue is fiwwed in a
 *  TP_MSG and echoed back in the next TP_ACK so that the sendew can compute the
 *  WTT. Since it is wead onwy by the host which wwote it, thewe is no need to
 *  stowe it using netwowk owdew
 */
stwuct batadv_icmp_tp_packet {
	__u8   packet_type;
	__u8   vewsion;
	__u8   ttw;
	__u8   msg_type; /* see ICMP message types above */
	__u8   dst[ETH_AWEN];
	__u8   owig[ETH_AWEN];
	__u8   uid;
	__u8   subtype;
	__u8   session[2];
	__be32 seqno;
	__be32 timestamp;
};

/**
 * enum batadv_icmp_tp_subtype - ICMP TP Metew packet subtypes
 * @BATADV_TP_MSG: Msg fwom sendew to weceivew
 * @BATADV_TP_ACK: acknowwedgment fwom weceivew to sendew
 */
enum batadv_icmp_tp_subtype {
	BATADV_TP_MSG	= 0,
	BATADV_TP_ACK,
};

#define BATADV_WW_WEN 16

/**
 * stwuct batadv_icmp_packet_ww - ICMP WouteWecowd packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @msg_type: ICMP packet type
 * @dst: addwess of the destination node
 * @owig: addwess of the souwce node
 * @uid: wocaw ICMP socket identifiew
 * @ww_cuw: numbew of entwies the ww awway
 * @seqno: ICMP sequence numbew
 * @ww: woute wecowd awway
 */
stwuct batadv_icmp_packet_ww {
	__u8   packet_type;
	__u8   vewsion;
	__u8   ttw;
	__u8   msg_type; /* see ICMP message types above */
	__u8   dst[ETH_AWEN];
	__u8   owig[ETH_AWEN];
	__u8   uid;
	__u8   ww_cuw;
	__be16 seqno;
	__u8   ww[BATADV_WW_WEN][ETH_AWEN];
};

#define BATADV_ICMP_MAX_PACKET_SIZE	sizeof(stwuct batadv_icmp_packet_ww)

/* Aww packet headews in fwont of an ethewnet headew have to be compwetewy
 * divisibwe by 2 but not by 4 to make the paywoad aftew the ethewnet
 * headew again 4 bytes boundawy awigned.
 *
 * A packing of 2 is necessawy to avoid extwa padding at the end of the stwuct
 * caused by a stwuctuwe membew which is wawgew than two bytes. Othewwise
 * the stwuctuwe wouwd not fuwfiww the pweviouswy mentioned wuwe to avoid the
 * misawignment of the paywoad aftew the ethewnet headew. It may awso wead to
 * weakage of infowmation when the padding it not initiawized befowe sending.
 */

/**
 * stwuct batadv_unicast_packet - unicast packet fow netwowk paywoad
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @ttvn: twanswation tabwe vewsion numbew
 * @dest: owiginatow destination of the unicast packet
 */
stwuct batadv_unicast_packet {
	__u8 packet_type;
	__u8 vewsion;
	__u8 ttw;
	__u8 ttvn; /* destination twanswation tabwe vewsion numbew */
	__u8 dest[ETH_AWEN];
	/* "4 bytes boundawy + 2 bytes" wong to make the paywoad aftew the
	 * fowwowing ethewnet headew again 4 bytes boundawy awigned
	 */
};

/**
 * stwuct batadv_unicast_4addw_packet - extended unicast packet
 * @u: common unicast packet headew
 * @swc: addwess of the souwce
 * @subtype: packet subtype
 * @wesewved: wesewved byte fow awignment
 */
stwuct batadv_unicast_4addw_packet {
	stwuct batadv_unicast_packet u;
	__u8 swc[ETH_AWEN];
	__u8 subtype;
	__u8 wesewved;
	/* "4 bytes boundawy + 2 bytes" wong to make the paywoad aftew the
	 * fowwowing ethewnet headew again 4 bytes boundawy awigned
	 */
};

/**
 * stwuct batadv_fwag_packet - fwagmented packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @dest: finaw destination used when wouting fwagments
 * @owig: owiginatow of the fwagment used when mewging the packet
 * @no: fwagment numbew within this sequence
 * @pwiowity: pwiowity of fwame, fwom ToS IP pwecedence ow 802.1p
 * @wesewved: wesewved byte fow awignment
 * @seqno: sequence identification
 * @totaw_size: size of the mewged packet
 */
stwuct batadv_fwag_packet {
	__u8   packet_type;
	__u8   vewsion;  /* batman vewsion fiewd */
	__u8   ttw;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8   no:4;
	__u8   pwiowity:3;
	__u8   wesewved:1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8   wesewved:1;
	__u8   pwiowity:3;
	__u8   no:4;
#ewse
#ewwow "unknown bitfiewd endianness"
#endif
	__u8   dest[ETH_AWEN];
	__u8   owig[ETH_AWEN];
	__be16 seqno;
	__be16 totaw_size;
};

/**
 * stwuct batadv_bcast_packet - bwoadcast packet fow netwowk paywoad
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @wesewved: wesewved byte fow awignment
 * @seqno: sequence identification
 * @owig: owiginatow of the bwoadcast packet
 */
stwuct batadv_bcast_packet {
	__u8   packet_type;
	__u8   vewsion;  /* batman vewsion fiewd */
	__u8   ttw;
	__u8   wesewved;
	__be32 seqno;
	__u8   owig[ETH_AWEN];
	/* "4 bytes boundawy + 2 bytes" wong to make the paywoad aftew the
	 * fowwowing ethewnet headew again 4 bytes boundawy awigned
	 */
};

/**
 * stwuct batadv_mcast_packet - muwticast packet fow netwowk paywoad
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @wesewved: wesewved byte fow awignment
 * @tvwv_wen: wength of the appended tvwv buffew (in bytes)
 */
stwuct batadv_mcast_packet {
	__u8 packet_type;
	__u8 vewsion;
	__u8 ttw;
	__u8 wesewved;
	__be16 tvwv_wen;
	/* "4 bytes boundawy + 2 bytes" wong to make the paywoad aftew the
	 * fowwowing ethewnet headew again 4 bytes boundawy awigned
	 */
};

/**
 * stwuct batadv_coded_packet - netwowk coded packet
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @fiwst_souwce: owiginaw souwce of fiwst incwuded packet
 * @fiwst_owig_dest: owiginaw destination of fiwst incwuded packet
 * @fiwst_cwc: checksum of fiwst incwuded packet
 * @fiwst_ttvn: tt-vewsion numbew of fiwst incwuded packet
 * @second_ttw: ttw of second packet
 * @second_dest: second weceivew of this coded packet
 * @second_souwce: owiginaw souwce of second incwuded packet
 * @second_owig_dest: owiginaw destination of second incwuded packet
 * @second_cwc: checksum of second incwuded packet
 * @second_ttvn: tt vewsion numbew of second incwuded packet
 * @coded_wen: wength of netwowk coded pawt of the paywoad
 */
stwuct batadv_coded_packet {
	__u8   packet_type;
	__u8   vewsion;  /* batman vewsion fiewd */
	__u8   ttw;
	__u8   fiwst_ttvn;
	/* __u8 fiwst_dest[ETH_AWEN]; - saved in mac headew destination */
	__u8   fiwst_souwce[ETH_AWEN];
	__u8   fiwst_owig_dest[ETH_AWEN];
	__be32 fiwst_cwc;
	__u8   second_ttw;
	__u8   second_ttvn;
	__u8   second_dest[ETH_AWEN];
	__u8   second_souwce[ETH_AWEN];
	__u8   second_owig_dest[ETH_AWEN];
	__be32 second_cwc;
	__be16 coded_wen;
};

/**
 * stwuct batadv_unicast_tvwv_packet - genewic unicast packet with tvwv paywoad
 * @packet_type: batman-adv packet type, pawt of the genewaw headew
 * @vewsion: batman-adv pwotocow vewsion, pawt of the genewaw headew
 * @ttw: time to wive fow this packet, pawt of the genewaw headew
 * @wesewved: wesewved fiewd (fow packet awignment)
 * @swc: addwess of the souwce
 * @dst: addwess of the destination
 * @tvwv_wen: wength of tvwv data fowwowing the unicast tvwv headew
 * @awign: 2 bytes to awign the headew to a 4 byte boundawy
 */
stwuct batadv_unicast_tvwv_packet {
	__u8   packet_type;
	__u8   vewsion;  /* batman vewsion fiewd */
	__u8   ttw;
	__u8   wesewved;
	__u8   dst[ETH_AWEN];
	__u8   swc[ETH_AWEN];
	__be16 tvwv_wen;
	__u16  awign;
};

/**
 * stwuct batadv_tvwv_hdw - base tvwv headew stwuct
 * @type: tvwv containew type (see batadv_tvwv_type)
 * @vewsion: tvwv containew vewsion
 * @wen: tvwv containew wength
 */
stwuct batadv_tvwv_hdw {
	__u8   type;
	__u8   vewsion;
	__be16 wen;
};

/**
 * stwuct batadv_tvwv_gateway_data - gateway data pwopagated thwough gw tvwv
 *  containew
 * @bandwidth_down: advewtised upwink downwoad bandwidth
 * @bandwidth_up: advewtised upwink upwoad bandwidth
 */
stwuct batadv_tvwv_gateway_data {
	__be32 bandwidth_down;
	__be32 bandwidth_up;
};

/**
 * stwuct batadv_tvwv_tt_data - tt data pwopagated thwough the tt tvwv containew
 * @fwags: twanswation tabwe fwags (see batadv_tt_data_fwags)
 * @ttvn: twanswation tabwe vewsion numbew
 * @num_vwan: numbew of announced VWANs. In the TVWV this stwuct is fowwowed by
 *  one batadv_tvwv_tt_vwan_data object pew announced vwan
 */
stwuct batadv_tvwv_tt_data {
	__u8   fwags;
	__u8   ttvn;
	__be16 num_vwan;
};

/**
 * stwuct batadv_tvwv_tt_vwan_data - vwan specific tt data pwopagated thwough
 *  the tt tvwv containew
 * @cwc: cwc32 checksum of the entwies bewonging to this vwan
 * @vid: vwan identifiew
 * @wesewved: unused, usefuw fow awignment puwposes
 */
stwuct batadv_tvwv_tt_vwan_data {
	__be32 cwc;
	__be16 vid;
	__u16  wesewved;
};

/**
 * stwuct batadv_tvwv_tt_change - twanswation tabwe diff data
 * @fwags: status indicatows concewning the non-mesh cwient (see
 *  batadv_tt_cwient_fwags)
 * @wesewved: wesewved fiewd - usefuw fow awignment puwposes onwy
 * @addw: mac addwess of non-mesh cwient that twiggewed this tt change
 * @vid: VWAN identifiew
 */
stwuct batadv_tvwv_tt_change {
	__u8   fwags;
	__u8   wesewved[3];
	__u8   addw[ETH_AWEN];
	__be16 vid;
};

/**
 * stwuct batadv_tvwv_woam_adv - woaming advewtisement
 * @cwient: mac addwess of woaming cwient
 * @vid: VWAN identifiew
 */
stwuct batadv_tvwv_woam_adv {
	__u8   cwient[ETH_AWEN];
	__be16 vid;
};

/**
 * stwuct batadv_tvwv_mcast_data - paywoad of a muwticast tvwv
 * @fwags: muwticast fwags announced by the owig node
 * @wesewved: wesewved fiewd
 */
stwuct batadv_tvwv_mcast_data {
	__u8 fwags;
	__u8 wesewved[3];
};

/**
 * stwuct batadv_tvwv_mcast_twackew - paywoad of a muwticast twackew tvwv
 * @num_dests: numbew of subsequent destination owiginatow MAC addwesses
 */
stwuct batadv_tvwv_mcast_twackew {
	__be16	num_dests;
};

#pwagma pack()

#endif /* _UAPI_WINUX_BATADV_PACKET_H_ */
