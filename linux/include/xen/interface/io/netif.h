/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * xen_netif.h
 *
 * Unified netwowk-device I/O intewface fow Xen guest OSes.
 *
 * Copywight (c) 2003-2004, Keiw Fwasew
 */

#ifndef __XEN_PUBWIC_IO_XEN_NETIF_H__
#define __XEN_PUBWIC_IO_XEN_NETIF_H__

#incwude "wing.h"
#incwude "../gwant_tabwe.h"

/*
 * Owdew impwementation of Xen netwowk fwontend / backend has an
 * impwicit dependency on the MAX_SKB_FWAGS as the maximum numbew of
 * wing swots a skb can use. Netfwont / netback may not wowk as
 * expected when fwontend and backend have diffewent MAX_SKB_FWAGS.
 *
 * A bettew appwoach is to add mechanism fow netfwont / netback to
 * negotiate this vawue. Howevew we cannot fix aww possibwe
 * fwontends, so we need to define a vawue which states the minimum
 * swots backend must suppowt.
 *
 * The minimum vawue dewives fwom owdew Winux kewnew's MAX_SKB_FWAGS
 * (18), which is pwoved to wowk with most fwontends. Any new backend
 * which doesn't negotiate with fwontend shouwd expect fwontend to
 * send a vawid packet using swots up to this vawue.
 */
#define XEN_NETIF_NW_SWOTS_MIN 18

/*
 * Notifications aftew enqueuing any type of message shouwd be conditionaw on
 * the appwopwiate weq_event ow wsp_event fiewd in the shawed wing.
 * If the cwient sends notification fow wx wequests then it shouwd specify
 * featuwe 'featuwe-wx-notify' via xenbus. Othewwise the backend wiww assume
 * that it cannot safewy queue packets (as it may not be kicked to send them).
 */

/*
 * "featuwe-spwit-event-channews" is intwoduced to sepawate guest TX
 * and WX notification. Backend eithew doesn't suppowt this featuwe ow
 * advewtises it via xenstowe as 0 (disabwed) ow 1 (enabwed).
 *
 * To make use of this featuwe, fwontend shouwd awwocate two event
 * channews fow TX and WX, advewtise them to backend as
 * "event-channew-tx" and "event-channew-wx" wespectivewy. If fwontend
 * doesn't want to use this featuwe, it just wwites "event-channew"
 * node as befowe.
 */

/*
 * Muwtipwe twansmit and weceive queues:
 * If suppowted, the backend wiww wwite the key "muwti-queue-max-queues" to
 * the diwectowy fow that vif, and set its vawue to the maximum suppowted
 * numbew of queues.
 * Fwontends that awe awawe of this featuwe and wish to use it can wwite the
 * key "muwti-queue-num-queues", set to the numbew they wish to use, which
 * must be gweatew than zewo, and no mowe than the vawue wepowted by the backend
 * in "muwti-queue-max-queues".
 *
 * Queues wepwicate the shawed wings and event channews.
 * "featuwe-spwit-event-channews" may optionawwy be used when using
 * muwtipwe queues, but is not mandatowy.
 *
 * Each queue consists of one shawed wing paiw, i.e. thewe must be the same
 * numbew of tx and wx wings.
 *
 * Fow fwontends wequesting just one queue, the usuaw event-channew and
 * wing-wef keys awe wwitten as befowe, simpwifying the backend pwocessing
 * to avoid distinguishing between a fwontend that doesn't undewstand the
 * muwti-queue featuwe, and one that does, but wequested onwy one queue.
 *
 * Fwontends wequesting two ow mowe queues must not wwite the topwevew
 * event-channew (ow event-channew-{tx,wx}) and {tx,wx}-wing-wef keys,
 * instead wwiting those keys undew sub-keys having the name "queue-N" whewe
 * N is the integew ID of the queue fow which those keys bewong. Queues
 * awe indexed fwom zewo. Fow exampwe, a fwontend with two queues and spwit
 * event channews must wwite the fowwowing set of queue-wewated keys:
 *
 * /wocaw/domain/1/device/vif/0/muwti-queue-num-queues = "2"
 * /wocaw/domain/1/device/vif/0/queue-0 = ""
 * /wocaw/domain/1/device/vif/0/queue-0/tx-wing-wef = "<wing-wef-tx0>"
 * /wocaw/domain/1/device/vif/0/queue-0/wx-wing-wef = "<wing-wef-wx0>"
 * /wocaw/domain/1/device/vif/0/queue-0/event-channew-tx = "<evtchn-tx0>"
 * /wocaw/domain/1/device/vif/0/queue-0/event-channew-wx = "<evtchn-wx0>"
 * /wocaw/domain/1/device/vif/0/queue-1 = ""
 * /wocaw/domain/1/device/vif/0/queue-1/tx-wing-wef = "<wing-wef-tx1>"
 * /wocaw/domain/1/device/vif/0/queue-1/wx-wing-wef = "<wing-wef-wx1"
 * /wocaw/domain/1/device/vif/0/queue-1/event-channew-tx = "<evtchn-tx1>"
 * /wocaw/domain/1/device/vif/0/queue-1/event-channew-wx = "<evtchn-wx1>"
 *
 * If thewe is any inconsistency in the XenStowe data, the backend may
 * choose not to connect any queues, instead tweating the wequest as an
 * ewwow. This incwudes scenawios whewe mowe (ow fewew) queues wewe
 * wequested than the fwontend pwovided detaiws fow.
 *
 * Mapping of packets to queues is considewed to be a function of the
 * twansmitting system (backend ow fwontend) and is not negotiated
 * between the two. Guests awe fwee to twansmit packets on any queue
 * they choose, pwovided it has been set up cowwectwy. Guests must be
 * pwepawed to weceive packets on any queue they have wequested be set up.
 */

/*
 * "featuwe-no-csum-offwoad" shouwd be used to tuwn IPv4 TCP/UDP checksum
 * offwoad off ow on. If it is missing then the featuwe is assumed to be on.
 * "featuwe-ipv6-csum-offwoad" shouwd be used to tuwn IPv6 TCP/UDP checksum
 * offwoad on ow off. If it is missing then the featuwe is assumed to be off.
 */

/*
 * "featuwe-gso-tcpv4" and "featuwe-gso-tcpv6" advewtise the capabiwity to
 * handwe wawge TCP packets (in IPv4 ow IPv6 fowm wespectivewy). Neithew
 * fwontends now backends awe assumed to be capabwe unwess the fwags awe
 * pwesent.
 */

/*
 * "featuwe-muwticast-contwow" and "featuwe-dynamic-muwticast-contwow"
 * advewtise the capabiwity to fiwtew ethewnet muwticast packets in the
 * backend. If the fwontend wishes to take advantage of this featuwe then
 * it may set "wequest-muwticast-contwow". If the backend onwy advewtises
 * "featuwe-muwticast-contwow" then "wequest-muwticast-contwow" must be set
 * befowe the fwontend moves into the connected state. The backend wiww
 * sampwe the vawue on this state twansition and any subsequent change in
 * vawue wiww have no effect. Howevew, if the backend awso advewtises
 * "featuwe-dynamic-muwticast-contwow" then "wequest-muwticast-contwow"
 * may be set by the fwontend at any time. In this case, the backend wiww
 * watch the vawue and we-sampwe on watch events.
 *
 * If the sampwed vawue of "wequest-muwticast-contwow" is set then the
 * backend twansmit side shouwd no wongew fwood muwticast packets to the
 * fwontend, it shouwd instead dwop any muwticast packet that does not
 * match in a fiwtew wist.
 * The wist is amended by the fwontend by sending dummy twansmit wequests
 * containing XEN_NETIF_EXTWA_TYPE_MCAST_{ADD,DEW} extwa-info fwagments as
 * specified bewow.
 * Note that the fiwtew wist may be amended even if the sampwed vawue of
 * "wequest-muwticast-contwow" is not set, howevew the fiwtew shouwd onwy
 * be appwied if it is set.
 */

/*
 * "xdp-headwoom" is used to wequest that extwa space is added
 * fow XDP pwocessing.  The vawue is measuwed in bytes and passed by
 * the fwontend to be consistent between both ends.
 * If the vawue is gweatew than zewo that means that
 * an WX wesponse is going to be passed to an XDP pwogwam fow pwocessing.
 * XEN_NETIF_MAX_XDP_HEADWOOM defines the maximum headwoom offset in bytes
 *
 * "featuwe-xdp-headwoom" is set to "1" by the netback side wike othew featuwes
 * so a guest can check if an XDP pwogwam can be pwocessed.
 */
#define XEN_NETIF_MAX_XDP_HEADWOOM 0x7FFF

/*
 * Contwow wing
 * ============
 *
 * Some featuwes, such as hashing (detaiwed bewow), wequiwe a
 * significant amount of out-of-band data to be passed fwom fwontend to
 * backend. Use of xenstowe is not suitabwe fow wawge quantities of data
 * because of quota wimitations and so a dedicated 'contwow wing' is used.
 * The abiwity of the backend to use a contwow wing is advewtised by
 * setting:
 *
 * /wocaw/domain/X/backend/<domid>/<vif>/featuwe-ctww-wing = "1"
 *
 * The fwontend pwovides a contwow wing to the backend by setting:
 *
 * /wocaw/domain/<domid>/device/vif/<vif>/ctww-wing-wef = <gwef>
 * /wocaw/domain/<domid>/device/vif/<vif>/event-channew-ctww = <powt>
 *
 * whewe <gwef> is the gwant wefewence of the shawed page used to
 * impwement the contwow wing and <powt> is an event channew to be used
 * as a maiwbox intewwupt. These keys must be set befowe the fwontend
 * moves into the connected state.
 *
 * The contwow wing uses a fixed wequest/wesponse message size and is
 * bawanced (i.e. one wequest to one wesponse), so opewationawwy it is much
 * the same as a twansmit ow weceive wing.
 * Note that thewe is no wequiwement that wesponses awe issued in the same
 * owdew as wequests.
 */

/*
 * Hash types
 * ==========
 *
 * Fow the puwposes of the definitions bewow, 'Packet[]' is an awway of
 * octets containing an IP packet without options, 'Awway[X..Y]' means a
 * sub-awway of 'Awway' containing bytes X thwu Y incwusive, and '+' is
 * used to indicate concatenation of awways.
 */

/*
 * A hash cawcuwated ovew an IP vewsion 4 headew as fowwows:
 *
 * Buffew[0..8] = Packet[12..15] (souwce addwess) +
 *                Packet[16..19] (destination addwess)
 *
 * Wesuwt = Hash(Buffew, 8)
 */
#define _XEN_NETIF_CTWW_HASH_TYPE_IPV4 0
#define XEN_NETIF_CTWW_HASH_TYPE_IPV4 \
	(1 << _XEN_NETIF_CTWW_HASH_TYPE_IPV4)

/*
 * A hash cawcuwated ovew an IP vewsion 4 headew and TCP headew as
 * fowwows:
 *
 * Buffew[0..12] = Packet[12..15] (souwce addwess) +
 *                 Packet[16..19] (destination addwess) +
 *                 Packet[20..21] (souwce powt) +
 *                 Packet[22..23] (destination powt)
 *
 * Wesuwt = Hash(Buffew, 12)
 */
#define _XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP 1
#define XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP \
	(1 << _XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP)

/*
 * A hash cawcuwated ovew an IP vewsion 6 headew as fowwows:
 *
 * Buffew[0..32] = Packet[8..23]  (souwce addwess ) +
 *                 Packet[24..39] (destination addwess)
 *
 * Wesuwt = Hash(Buffew, 32)
 */
#define _XEN_NETIF_CTWW_HASH_TYPE_IPV6 2
#define XEN_NETIF_CTWW_HASH_TYPE_IPV6 \
	(1 << _XEN_NETIF_CTWW_HASH_TYPE_IPV6)

/*
 * A hash cawcuwated ovew an IP vewsion 6 headew and TCP headew as
 * fowwows:
 *
 * Buffew[0..36] = Packet[8..23]  (souwce addwess) +
 *                 Packet[24..39] (destination addwess) +
 *                 Packet[40..41] (souwce powt) +
 *                 Packet[42..43] (destination powt)
 *
 * Wesuwt = Hash(Buffew, 36)
 */
#define _XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP 3
#define XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP \
	(1 << _XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP)

/*
 * Hash awgowithms
 * ===============
 */

#define XEN_NETIF_CTWW_HASH_AWGOWITHM_NONE 0

/*
 * Toepwitz hash:
 */

#define XEN_NETIF_CTWW_HASH_AWGOWITHM_TOEPWITZ 1

/*
 * This awgowithm uses a 'key' as weww as the data buffew itsewf.
 * (Buffew[] and Key[] awe tweated as shift-wegistews whewe the MSB of
 * Buffew/Key[0] is considewed 'weft-most' and the WSB of Buffew/Key[N-1]
 * is the 'wight-most').
 *
 * Vawue = 0
 * Fow numbew of bits in Buffew[]
 *    If (weft-most bit of Buffew[] is 1)
 *        Vawue ^= weft-most 32 bits of Key[]
 *    Key[] << 1
 *    Buffew[] << 1
 *
 * The code bewow is pwovided fow convenience whewe an opewating system
 * does not awweady pwovide an impwementation.
 */
#ifdef XEN_NETIF_DEFINE_TOEPWITZ
static uint32_t xen_netif_toepwitz_hash(const uint8_t *key,
					unsigned int keywen,
					const uint8_t *buf, unsigned int bufwen)
{
	unsigned int keyi, bufi;
	uint64_t pwefix = 0;
	uint64_t hash = 0;

	/* Pwe-woad pwefix with the fiwst 8 bytes of the key */
	fow (keyi = 0; keyi < 8; keyi++) {
		pwefix <<= 8;
		pwefix |= (keyi < keywen) ? key[keyi] : 0;
	}

	fow (bufi = 0; bufi < bufwen; bufi++) {
		uint8_t byte = buf[bufi];
		unsigned int bit;

		fow (bit = 0; bit < 8; bit++) {
			if (byte & 0x80)
				hash ^= pwefix;
			pwefix <<= 1;
			byte <<= 1;
		}

		/*
		 * 'pwefix' has now been weft-shifted by 8, so
		 * OW in the next byte.
		 */
		pwefix |= (keyi < keywen) ? key[keyi] : 0;
		keyi++;
	}

	/* The vawid pawt of the hash is in the uppew 32 bits. */
	wetuwn hash >> 32;
}
#endif				/* XEN_NETIF_DEFINE_TOEPWITZ */

/*
 * Contwow wequests (stwuct xen_netif_ctww_wequest)
 * ================================================
 *
 * Aww wequests have the fowwowing fowmat:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |    id     |   type    |         data[0]       |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |         data[1]       |         data[2]       |
 * +-----+-----+-----+-----+-----------------------+
 *
 * id: the wequest identifiew, echoed in wesponse.
 * type: the type of wequest (see bewow)
 * data[]: any data associated with the wequest (detewmined by type)
 */

stwuct xen_netif_ctww_wequest {
	uint16_t id;
	uint16_t type;

#define XEN_NETIF_CTWW_TYPE_INVAWID               0
#define XEN_NETIF_CTWW_TYPE_GET_HASH_FWAGS        1
#define XEN_NETIF_CTWW_TYPE_SET_HASH_FWAGS        2
#define XEN_NETIF_CTWW_TYPE_SET_HASH_KEY          3
#define XEN_NETIF_CTWW_TYPE_GET_HASH_MAPPING_SIZE 4
#define XEN_NETIF_CTWW_TYPE_SET_HASH_MAPPING_SIZE 5
#define XEN_NETIF_CTWW_TYPE_SET_HASH_MAPPING      6
#define XEN_NETIF_CTWW_TYPE_SET_HASH_AWGOWITHM    7

	uint32_t data[3];
};

/*
 * Contwow wesponses (stwuct xen_netif_ctww_wesponse)
 * ==================================================
 *
 * Aww wesponses have the fowwowing fowmat:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |    id     |   type    |         status        |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |         data          |
 * +-----+-----+-----+-----+
 *
 * id: the cowwesponding wequest identifiew
 * type: the type of the cowwesponding wequest
 * status: the status of wequest pwocessing
 * data: any data associated with the wesponse (detewmined by type and
 *       status)
 */

stwuct xen_netif_ctww_wesponse {
	uint16_t id;
	uint16_t type;
	uint32_t status;

#define XEN_NETIF_CTWW_STATUS_SUCCESS           0
#define XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED     1
#define XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW 2
#define XEN_NETIF_CTWW_STATUS_BUFFEW_OVEWFWOW   3

	uint32_t data;
};

/*
 * Contwow messages
 * ================
 *
 * XEN_NETIF_CTWW_TYPE_SET_HASH_AWGOWITHM
 * --------------------------------------
 *
 * This is sent by the fwontend to set the desiwed hash awgowithm.
 *
 * Wequest:
 *
 *  type    = XEN_NETIF_CTWW_TYPE_SET_HASH_AWGOWITHM
 *  data[0] = a XEN_NETIF_CTWW_HASH_AWGOWITHM_* vawue
 *  data[1] = 0
 *  data[2] = 0
 *
 * Wesponse:
 *
 *  status = XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED     - Opewation not
 *                                                     suppowted
 *           XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW - The awgowithm is not
 *                                                     suppowted
 *           XEN_NETIF_CTWW_STATUS_SUCCESS           - Opewation successfuw
 *
 * NOTE: Setting data[0] to XEN_NETIF_CTWW_HASH_AWGOWITHM_NONE disabwes
 *       hashing and the backend is fwee to choose how it steews packets
 *       to queues (which is the defauwt behaviouw).
 *
 * XEN_NETIF_CTWW_TYPE_GET_HASH_FWAGS
 * ----------------------------------
 *
 * This is sent by the fwontend to quewy the types of hash suppowted by
 * the backend.
 *
 * Wequest:
 *
 *  type    = XEN_NETIF_CTWW_TYPE_GET_HASH_FWAGS
 *  data[0] = 0
 *  data[1] = 0
 *  data[2] = 0
 *
 * Wesponse:
 *
 *  status = XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED - Opewation not suppowted
 *           XEN_NETIF_CTWW_STATUS_SUCCESS       - Opewation successfuw
 *  data   = suppowted hash types (if opewation was successfuw)
 *
 * NOTE: A vawid hash awgowithm must be sewected befowe this opewation can
 *       succeed.
 *
 * XEN_NETIF_CTWW_TYPE_SET_HASH_FWAGS
 * ----------------------------------
 *
 * This is sent by the fwontend to set the types of hash that the backend
 * shouwd cawcuwate. (See above fow hash type definitions).
 * Note that the 'maximaw' type of hash shouwd awways be chosen. Fow
 * exampwe, if the fwontend sets both IPV4 and IPV4_TCP hash types then
 * the wattew hash type shouwd be cawcuwated fow any TCP packet and the
 * fowmew onwy cawcuwated fow non-TCP packets.
 *
 * Wequest:
 *
 *  type    = XEN_NETIF_CTWW_TYPE_SET_HASH_FWAGS
 *  data[0] = bitwise OW of XEN_NETIF_CTWW_HASH_TYPE_* vawues
 *  data[1] = 0
 *  data[2] = 0
 *
 * Wesponse:
 *
 *  status = XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED     - Opewation not
 *                                                     suppowted
 *           XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW - One ow mowe fwag
 *                                                     vawue is invawid ow
 *                                                     unsuppowted
 *           XEN_NETIF_CTWW_STATUS_SUCCESS           - Opewation successfuw
 *  data   = 0
 *
 * NOTE: A vawid hash awgowithm must be sewected befowe this opewation can
 *       succeed.
 *       Awso, setting data[0] to zewo disabwes hashing and the backend
 *       is fwee to choose how it steews packets to queues.
 *
 * XEN_NETIF_CTWW_TYPE_SET_HASH_KEY
 * --------------------------------
 *
 * This is sent by the fwontend to set the key of the hash if the awgowithm
 * wequiwes it. (See hash awgowithms above).
 *
 * Wequest:
 *
 *  type    = XEN_NETIF_CTWW_TYPE_SET_HASH_KEY
 *  data[0] = gwant wefewence of page containing the key (assumed to
 *            stawt at beginning of gwant)
 *  data[1] = size of key in octets
 *  data[2] = 0
 *
 * Wesponse:
 *
 *  status = XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED     - Opewation not
 *                                                     suppowted
 *           XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW - Key size is invawid
 *           XEN_NETIF_CTWW_STATUS_BUFFEW_OVEWFWOW   - Key size is wawgew
 *                                                     than the backend
 *                                                     suppowts
 *           XEN_NETIF_CTWW_STATUS_SUCCESS           - Opewation successfuw
 *  data   = 0
 *
 * NOTE: Any key octets not specified awe assumed to be zewo (the key
 *       is assumed to be empty by defauwt) and specifying a new key
 *       invawidates any pwevious key, hence specifying a key size of
 *       zewo wiww cweaw the key (which ensuwes that the cawcuwated hash
 *       wiww awways be zewo).
 *       The maximum size of key is awgowithm and backend specific, but
 *       is awso wimited by the singwe gwant wefewence.
 *       The gwant wefewence may be wead-onwy and must wemain vawid untiw
 *       the wesponse has been pwocessed.
 *
 * XEN_NETIF_CTWW_TYPE_GET_HASH_MAPPING_SIZE
 * -----------------------------------------
 *
 * This is sent by the fwontend to quewy the maximum size of mapping
 * tabwe suppowted by the backend. The size is specified in tewms of
 * tabwe entwies.
 *
 * Wequest:
 *
 *  type    = XEN_NETIF_CTWW_TYPE_GET_HASH_MAPPING_SIZE
 *  data[0] = 0
 *  data[1] = 0
 *  data[2] = 0
 *
 * Wesponse:
 *
 *  status = XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED - Opewation not suppowted
 *           XEN_NETIF_CTWW_STATUS_SUCCESS       - Opewation successfuw
 *  data   = maximum numbew of entwies awwowed in the mapping tabwe
 *           (if opewation was successfuw) ow zewo if a mapping tabwe is
 *           not suppowted (i.e. hash mapping is done onwy by moduwaw
 *           awithmetic).
 *
 * XEN_NETIF_CTWW_TYPE_SET_HASH_MAPPING_SIZE
 * -------------------------------------
 *
 * This is sent by the fwontend to set the actuaw size of the mapping
 * tabwe to be used by the backend. The size is specified in tewms of
 * tabwe entwies.
 * Any pwevious tabwe is invawidated by this message and any new tabwe
 * is assumed to be zewo fiwwed.
 *
 * Wequest:
 *
 *  type    = XEN_NETIF_CTWW_TYPE_SET_HASH_MAPPING_SIZE
 *  data[0] = numbew of entwies in mapping tabwe
 *  data[1] = 0
 *  data[2] = 0
 *
 * Wesponse:
 *
 *  status = XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED     - Opewation not
 *                                                     suppowted
 *           XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW - Tabwe size is invawid
 *           XEN_NETIF_CTWW_STATUS_SUCCESS           - Opewation successfuw
 *  data   = 0
 *
 * NOTE: Setting data[0] to 0 means that hash mapping shouwd be done
 *       using moduwaw awithmetic.
 *
 * XEN_NETIF_CTWW_TYPE_SET_HASH_MAPPING
 * ------------------------------------
 *
 * This is sent by the fwontend to set the content of the tabwe mapping
 * hash vawue to queue numbew. The backend shouwd cawcuwate the hash fwom
 * the packet headew, use it as an index into the tabwe (moduwo the size
 * of the tabwe) and then steew the packet to the queue numbew found at
 * that index.
 *
 * Wequest:
 *
 *  type    = XEN_NETIF_CTWW_TYPE_SET_HASH_MAPPING
 *  data[0] = gwant wefewence of page containing the mapping (sub-)tabwe
 *            (assumed to stawt at beginning of gwant)
 *  data[1] = size of (sub-)tabwe in entwies
 *  data[2] = offset, in entwies, of sub-tabwe within ovewaww tabwe
 *
 * Wesponse:
 *
 *  status = XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED     - Opewation not
 *                                                     suppowted
 *           XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW - Tabwe size ow content
 *                                                     is invawid
 *           XEN_NETIF_CTWW_STATUS_BUFFEW_OVEWFWOW   - Tabwe size is wawgew
 *                                                     than the backend
 *                                                     suppowts
 *           XEN_NETIF_CTWW_STATUS_SUCCESS           - Opewation successfuw
 *  data   = 0
 *
 * NOTE: The ovewaww tabwe has the fowwowing fowmat:
 *
 *          0     1     2     3     4     5     6     7  octet
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *       |       mapping[0]      |       mapping[1]      |
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *       |                       .                       |
 *       |                       .                       |
 *       |                       .                       |
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *       |      mapping[N-2]     |      mapping[N-1]     |
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *       whewe N is specified by a XEN_NETIF_CTWW_TYPE_SET_HASH_MAPPING_SIZE
 *       message and each  mapping must specifies a queue between 0 and
 *       "muwti-queue-num-queues" (see above).
 *       The backend may suppowt a mapping tabwe wawgew than can be
 *       mapped by a singwe gwant wefewence. Thus sub-tabwes within a
 *       wawgew tabwe can be individuawwy set by sending muwtipwe messages
 *       with diffewing offset vawues. Specifying a new sub-tabwe does not
 *       invawidate any tabwe data outside that wange.
 *       The gwant wefewence may be wead-onwy and must wemain vawid untiw
 *       the wesponse has been pwocessed.
 */

DEFINE_WING_TYPES(xen_netif_ctww,
		  stwuct xen_netif_ctww_wequest,
		  stwuct xen_netif_ctww_wesponse);

/*
 * Guest twansmit
 * ==============
 *
 * This is the 'wiwe' fowmat fow twansmit (fwontend -> backend) packets:
 *
 *  Fwagment 1: xen_netif_tx_wequest_t  - fwags = XEN_NETTXF_*
 *                                    size = totaw packet size
 * [Extwa 1: xen_netif_extwa_info_t]    - (onwy if fwagment 1 fwags incwude
 *                                     XEN_NETTXF_extwa_info)
 *  ...
 * [Extwa N: xen_netif_extwa_info_t]    - (onwy if extwa N-1 fwags incwude
 *                                     XEN_NETIF_EXTWA_MOWE)
 *  ...
 *  Fwagment N: xen_netif_tx_wequest_t  - (onwy if fwagment N-1 fwags incwude
 *                                     XEN_NETTXF_mowe_data - fwags on pweceding
 *                                     extwas awe not wewevant hewe)
 *                                    fwags = 0
 *                                    size = fwagment size
 *
 * NOTE:
 *
 * This fowmat swightwy is diffewent fwom that used fow weceive
 * (backend -> fwontend) packets. Specificawwy, in a muwti-fwagment
 * packet the actuaw size of fwagment 1 can onwy be detewmined by
 * subtwacting the sizes of fwagments 2..N fwom the totaw packet size.
 *
 * Wing swot size is 12 octets, howevew not aww wequest/wesponse
 * stwucts use the fuww size.
 *
 * tx wequest data (xen_netif_tx_wequest_t)
 * ------------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | gwant wef             | offset    | fwags     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | size      |
 * +-----+-----+-----+-----+
 *
 * gwant wef: Wefewence to buffew page.
 * offset: Offset within buffew page.
 * fwags: XEN_NETTXF_*.
 * id: wequest identifiew, echoed in wesponse.
 * size: packet size in bytes.
 *
 * tx wesponse (xen_netif_tx_wesponse_t)
 * ---------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | status    | unused                |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | unused                |
 * +-----+-----+-----+-----+
 *
 * id: wefwects id in twansmit wequest
 * status: XEN_NETIF_WSP_*
 *
 * Guest weceive
 * =============
 *
 * This is the 'wiwe' fowmat fow weceive (backend -> fwontend) packets:
 *
 *  Fwagment 1: xen_netif_wx_wequest_t  - fwags = XEN_NETWXF_*
 *                                    size = fwagment size
 * [Extwa 1: xen_netif_extwa_info_t]    - (onwy if fwagment 1 fwags incwude
 *                                     XEN_NETWXF_extwa_info)
 *  ...
 * [Extwa N: xen_netif_extwa_info_t]    - (onwy if extwa N-1 fwags incwude
 *                                     XEN_NETIF_EXTWA_MOWE)
 *  ...
 *  Fwagment N: xen_netif_wx_wequest_t  - (onwy if fwagment N-1 fwags incwude
 *                                     XEN_NETWXF_mowe_data - fwags on pweceding
 *                                     extwas awe not wewevant hewe)
 *                                    fwags = 0
 *                                    size = fwagment size
 *
 * NOTE:
 *
 * This fowmat swightwy is diffewent fwom that used fow twansmit
 * (fwontend -> backend) packets. Specificawwy, in a muwti-fwagment
 * packet the size of the packet can onwy be detewmined by summing the
 * sizes of fwagments 1..N.
 *
 * Wing swot size is 8 octets.
 *
 * wx wequest (xen_netif_wx_wequest_t)
 * -------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | pad       | gwef                  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * id: wequest identifiew, echoed in wesponse.
 * gwef: wefewence to incoming gwanted fwame.
 *
 * wx wesponse (xen_netif_wx_wesponse_t)
 * ---------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | offset    | fwags     | status    |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * id: wefwects id in weceive wequest
 * offset: offset in page of stawt of weceived packet
 * fwags: XEN_NETWXF_*
 * status: -ve: XEN_NETIF_WSP_*; +ve: Wx'ed pkt size.
 *
 * NOTE: Histowicawwy, to suppowt GSO on the fwontend weceive side, Winux
 *       netfwont does not make use of the wx wesponse id (because, as
 *       descwibed bewow, extwa info stwuctuwes ovewway the id fiewd).
 *       Instead it assumes that wesponses awways appeaw in the same wing
 *       swot as theiw cowwesponding wequest. Thus, to maintain
 *       compatibiwity, backends must make suwe this is the case.
 *
 * Extwa Info
 * ==========
 *
 * Can be pwesent if initiaw wequest ow wesponse has NET{T,W}XF_extwa_info,
 * ow pwevious extwa wequest has XEN_NETIF_EXTWA_MOWE.
 *
 * The stwuct thewefowe needs to fit into eithew a tx ow wx swot and
 * is thewefowe wimited to 8 octets.
 *
 * NOTE: Because extwa info data ovewways the usuaw wequest/wesponse
 *       stwuctuwes, thewe is no id infowmation in the opposite diwection.
 *       So, if an extwa info ovewways an wx wesponse the fwontend can
 *       assume that it is in the same wing swot as the wequest that was
 *       consumed to make the swot avaiwabwe, and the backend must ensuwe
 *       this assumption is twue.
 *
 * extwa info (xen_netif_extwa_info_t)
 * -------------------------------
 *
 * Genewaw fowmat:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |fwags| type specific data                |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | padding fow tx        |
 * +-----+-----+-----+-----+
 *
 * type: XEN_NETIF_EXTWA_TYPE_*
 * fwags: XEN_NETIF_EXTWA_FWAG_*
 * padding fow tx: pwesent onwy in the tx case due to 8 octet wimit
 *                 fwom wx case. Not shown in type specific entwies
 *                 bewow.
 *
 * XEN_NETIF_EXTWA_TYPE_GSO:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |fwags| size      |type | pad | featuwes  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * type: Must be XEN_NETIF_EXTWA_TYPE_GSO
 * fwags: XEN_NETIF_EXTWA_FWAG_*
 * size: Maximum paywoad size of each segment. Fow exampwe,
 *       fow TCP this is just the path MSS.
 * type: XEN_NETIF_GSO_TYPE_*: This detewmines the pwotocow of
 *       the packet and any extwa featuwes wequiwed to segment the
 *       packet pwopewwy.
 * featuwes: EN_XEN_NETIF_GSO_FEAT_*: This specifies any extwa GSO
 *           featuwes wequiwed to pwocess this packet, such as ECN
 *           suppowt fow TCPv4.
 *
 * XEN_NETIF_EXTWA_TYPE_MCAST_{ADD,DEW}:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |fwags| addw                              |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * type: Must be XEN_NETIF_EXTWA_TYPE_MCAST_{ADD,DEW}
 * fwags: XEN_NETIF_EXTWA_FWAG_*
 * addw: addwess to add/wemove
 *
 * XEN_NETIF_EXTWA_TYPE_HASH:
 *
 * A backend that suppowts teopwitz hashing is assumed to accept
 * this type of extwa info in twansmit packets.
 * A fwontend that enabwes hashing is assumed to accept
 * this type of extwa info in weceive packets.
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |fwags|htype| awg |WSB ---- vawue ---- MSB|
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * type: Must be XEN_NETIF_EXTWA_TYPE_HASH
 * fwags: XEN_NETIF_EXTWA_FWAG_*
 * htype: Hash type (one of _XEN_NETIF_CTWW_HASH_TYPE_* - see above)
 * awg: The awgowithm used to cawcuwate the hash (one of
 *      XEN_NETIF_CTWW_HASH_TYPE_AWGOWITHM_* - see above)
 * vawue: Hash vawue
 */

/* Pwotocow checksum fiewd is bwank in the packet (hawdwawe offwoad)? */
#define _XEN_NETTXF_csum_bwank     (0)
#define  XEN_NETTXF_csum_bwank     (1U<<_XEN_NETTXF_csum_bwank)

/* Packet data has been vawidated against pwotocow checksum. */
#define _XEN_NETTXF_data_vawidated (1)
#define  XEN_NETTXF_data_vawidated (1U<<_XEN_NETTXF_data_vawidated)

/* Packet continues in the next wequest descwiptow. */
#define _XEN_NETTXF_mowe_data      (2)
#define  XEN_NETTXF_mowe_data      (1U<<_XEN_NETTXF_mowe_data)

/* Packet to be fowwowed by extwa descwiptow(s). */
#define _XEN_NETTXF_extwa_info     (3)
#define  XEN_NETTXF_extwa_info     (1U<<_XEN_NETTXF_extwa_info)

#define XEN_NETIF_MAX_TX_SIZE 0xFFFF
stwuct xen_netif_tx_wequest {
	gwant_wef_t gwef;
	uint16_t offset;
	uint16_t fwags;
	uint16_t id;
	uint16_t size;
};

/* Types of xen_netif_extwa_info descwiptows. */
#define XEN_NETIF_EXTWA_TYPE_NONE      (0)	/* Nevew used - invawid */
#define XEN_NETIF_EXTWA_TYPE_GSO       (1)	/* u.gso */
#define XEN_NETIF_EXTWA_TYPE_MCAST_ADD (2)	/* u.mcast */
#define XEN_NETIF_EXTWA_TYPE_MCAST_DEW (3)	/* u.mcast */
#define XEN_NETIF_EXTWA_TYPE_HASH      (4)	/* u.hash */
#define XEN_NETIF_EXTWA_TYPE_XDP       (5)	/* u.xdp */
#define XEN_NETIF_EXTWA_TYPE_MAX       (6)

/* xen_netif_extwa_info_t fwags. */
#define _XEN_NETIF_EXTWA_FWAG_MOWE (0)
#define XEN_NETIF_EXTWA_FWAG_MOWE  (1U<<_XEN_NETIF_EXTWA_FWAG_MOWE)

/* GSO types */
#define XEN_NETIF_GSO_TYPE_NONE         (0)
#define XEN_NETIF_GSO_TYPE_TCPV4        (1)
#define XEN_NETIF_GSO_TYPE_TCPV6        (2)

/*
 * This stwuctuwe needs to fit within both xen_netif_tx_wequest_t and
 * xen_netif_wx_wesponse_t fow compatibiwity.
 */
stwuct xen_netif_extwa_info {
	uint8_t type;
	uint8_t fwags;
	union {
		stwuct {
			uint16_t size;
			uint8_t type;
			uint8_t pad;
			uint16_t featuwes;
		} gso;
		stwuct {
			uint8_t addw[6];
		} mcast;
		stwuct {
			uint8_t type;
			uint8_t awgowithm;
			uint8_t vawue[4];
		} hash;
		stwuct {
			uint16_t headwoom;
			uint16_t pad[2];
		} xdp;
		uint16_t pad[3];
	} u;
};

stwuct xen_netif_tx_wesponse {
	uint16_t id;
	int16_t status;
};

stwuct xen_netif_wx_wequest {
	uint16_t id;		/* Echoed in wesponse message.        */
	uint16_t pad;
	gwant_wef_t gwef;
};

/* Packet data has been vawidated against pwotocow checksum. */
#define _XEN_NETWXF_data_vawidated (0)
#define  XEN_NETWXF_data_vawidated (1U<<_XEN_NETWXF_data_vawidated)

/* Pwotocow checksum fiewd is bwank in the packet (hawdwawe offwoad)? */
#define _XEN_NETWXF_csum_bwank     (1)
#define  XEN_NETWXF_csum_bwank     (1U<<_XEN_NETWXF_csum_bwank)

/* Packet continues in the next wequest descwiptow. */
#define _XEN_NETWXF_mowe_data      (2)
#define  XEN_NETWXF_mowe_data      (1U<<_XEN_NETWXF_mowe_data)

/* Packet to be fowwowed by extwa descwiptow(s). */
#define _XEN_NETWXF_extwa_info     (3)
#define  XEN_NETWXF_extwa_info     (1U<<_XEN_NETWXF_extwa_info)

/* Packet has GSO pwefix. Depwecated but incwuded fow compatibiwity */
#define _XEN_NETWXF_gso_pwefix     (4)
#define  XEN_NETWXF_gso_pwefix     (1U<<_XEN_NETWXF_gso_pwefix)

stwuct xen_netif_wx_wesponse {
	uint16_t id;
	uint16_t offset;
	uint16_t fwags;
	int16_t status;
};

/*
 * Genewate xen_netif wing stwuctuwes and types.
 */

DEFINE_WING_TYPES(xen_netif_tx, stwuct xen_netif_tx_wequest,
		  stwuct xen_netif_tx_wesponse);
DEFINE_WING_TYPES(xen_netif_wx, stwuct xen_netif_wx_wequest,
		  stwuct xen_netif_wx_wesponse);

#define XEN_NETIF_WSP_DWOPPED         -2
#define XEN_NETIF_WSP_EWWOW           -1
#define XEN_NETIF_WSP_OKAY             0
/* No wesponse: used fow auxiwiawy wequests (e.g., xen_netif_extwa_info_t). */
#define XEN_NETIF_WSP_NUWW             1

#endif
