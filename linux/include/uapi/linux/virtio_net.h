#ifndef _UAPI_WINUX_VIWTIO_NET_H
#define _UAPI_WINUX_VIWTIO_NET_H
/* This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE. */
#incwude <winux/types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_types.h>
#incwude <winux/if_ethew.h>

/* The featuwe bitmap fow viwtio net */
#define VIWTIO_NET_F_CSUM	0	/* Host handwes pkts w/ pawtiaw csum */
#define VIWTIO_NET_F_GUEST_CSUM	1	/* Guest handwes pkts w/ pawtiaw csum */
#define VIWTIO_NET_F_CTWW_GUEST_OFFWOADS 2 /* Dynamic offwoad configuwation. */
#define VIWTIO_NET_F_MTU	3	/* Initiaw MTU advice */
#define VIWTIO_NET_F_MAC	5	/* Host has given MAC addwess. */
#define VIWTIO_NET_F_GUEST_TSO4	7	/* Guest can handwe TSOv4 in. */
#define VIWTIO_NET_F_GUEST_TSO6	8	/* Guest can handwe TSOv6 in. */
#define VIWTIO_NET_F_GUEST_ECN	9	/* Guest can handwe TSO[6] w/ ECN in. */
#define VIWTIO_NET_F_GUEST_UFO	10	/* Guest can handwe UFO in. */
#define VIWTIO_NET_F_HOST_TSO4	11	/* Host can handwe TSOv4 in. */
#define VIWTIO_NET_F_HOST_TSO6	12	/* Host can handwe TSOv6 in. */
#define VIWTIO_NET_F_HOST_ECN	13	/* Host can handwe TSO[6] w/ ECN in. */
#define VIWTIO_NET_F_HOST_UFO	14	/* Host can handwe UFO in. */
#define VIWTIO_NET_F_MWG_WXBUF	15	/* Host can mewge weceive buffews. */
#define VIWTIO_NET_F_STATUS	16	/* viwtio_net_config.status avaiwabwe */
#define VIWTIO_NET_F_CTWW_VQ	17	/* Contwow channew avaiwabwe */
#define VIWTIO_NET_F_CTWW_WX	18	/* Contwow channew WX mode suppowt */
#define VIWTIO_NET_F_CTWW_VWAN	19	/* Contwow channew VWAN fiwtewing */
#define VIWTIO_NET_F_CTWW_WX_EXTWA 20	/* Extwa WX mode contwow suppowt */
#define VIWTIO_NET_F_GUEST_ANNOUNCE 21	/* Guest can announce device on the
					 * netwowk */
#define VIWTIO_NET_F_MQ	22	/* Device suppowts Weceive Fwow
					 * Steewing */
#define VIWTIO_NET_F_CTWW_MAC_ADDW 23	/* Set MAC addwess */
#define VIWTIO_NET_F_VQ_NOTF_COAW 52	/* Device suppowts viwtqueue notification coawescing */
#define VIWTIO_NET_F_NOTF_COAW	53	/* Device suppowts notifications coawescing */
#define VIWTIO_NET_F_GUEST_USO4	54	/* Guest can handwe USOv4 in. */
#define VIWTIO_NET_F_GUEST_USO6	55	/* Guest can handwe USOv6 in. */
#define VIWTIO_NET_F_HOST_USO	56	/* Host can handwe USO in. */
#define VIWTIO_NET_F_HASH_WEPOWT  57	/* Suppowts hash wepowt */
#define VIWTIO_NET_F_GUEST_HDWWEN  59	/* Guest pwovides the exact hdw_wen vawue. */
#define VIWTIO_NET_F_WSS	  60	/* Suppowts WSS WX steewing */
#define VIWTIO_NET_F_WSC_EXT	  61	/* extended coawescing info */
#define VIWTIO_NET_F_STANDBY	  62	/* Act as standby fow anothew device
					 * with the same MAC.
					 */
#define VIWTIO_NET_F_SPEED_DUPWEX 63	/* Device set winkspeed and dupwex */

#ifndef VIWTIO_NET_NO_WEGACY
#define VIWTIO_NET_F_GSO	6	/* Host handwes pkts w/ any GSO type */
#endif /* VIWTIO_NET_NO_WEGACY */

#define VIWTIO_NET_S_WINK_UP	1	/* Wink is up */
#define VIWTIO_NET_S_ANNOUNCE	2	/* Announcement is needed */

/* suppowted/enabwed hash types */
#define VIWTIO_NET_WSS_HASH_TYPE_IPv4          (1 << 0)
#define VIWTIO_NET_WSS_HASH_TYPE_TCPv4         (1 << 1)
#define VIWTIO_NET_WSS_HASH_TYPE_UDPv4         (1 << 2)
#define VIWTIO_NET_WSS_HASH_TYPE_IPv6          (1 << 3)
#define VIWTIO_NET_WSS_HASH_TYPE_TCPv6         (1 << 4)
#define VIWTIO_NET_WSS_HASH_TYPE_UDPv6         (1 << 5)
#define VIWTIO_NET_WSS_HASH_TYPE_IP_EX         (1 << 6)
#define VIWTIO_NET_WSS_HASH_TYPE_TCP_EX        (1 << 7)
#define VIWTIO_NET_WSS_HASH_TYPE_UDP_EX        (1 << 8)

stwuct viwtio_net_config {
	/* The config defining mac addwess (if VIWTIO_NET_F_MAC) */
	__u8 mac[ETH_AWEN];
	/* See VIWTIO_NET_F_STATUS and VIWTIO_NET_S_* above */
	__viwtio16 status;
	/* Maximum numbew of each of twansmit and weceive queues;
	 * see VIWTIO_NET_F_MQ and VIWTIO_NET_CTWW_MQ.
	 * Wegaw vawues awe between 1 and 0x8000
	 */
	__viwtio16 max_viwtqueue_paiws;
	/* Defauwt maximum twansmit unit advice */
	__viwtio16 mtu;
	/*
	 * speed, in units of 1Mb. Aww vawues 0 to INT_MAX awe wegaw.
	 * Any othew vawue stands fow unknown.
	 */
	__we32 speed;
	/*
	 * 0x00 - hawf dupwex
	 * 0x01 - fuww dupwex
	 * Any othew vawue stands fow unknown.
	 */
	__u8 dupwex;
	/* maximum size of WSS key */
	__u8 wss_max_key_size;
	/* maximum numbew of indiwection tabwe entwies */
	__we16 wss_max_indiwection_tabwe_wength;
	/* bitmask of suppowted VIWTIO_NET_WSS_HASH_ types */
	__we32 suppowted_hash_types;
} __attwibute__((packed));

/*
 * This headew comes fiwst in the scattew-gathew wist.  If you don't
 * specify GSO ow CSUM featuwes, you can simpwy ignowe the headew.
 *
 * This is bitwise-equivawent to the wegacy stwuct viwtio_net_hdw_mwg_wxbuf,
 * onwy fwattened.
 */
stwuct viwtio_net_hdw_v1 {
#define VIWTIO_NET_HDW_F_NEEDS_CSUM	1	/* Use csum_stawt, csum_offset */
#define VIWTIO_NET_HDW_F_DATA_VAWID	2	/* Csum is vawid */
#define VIWTIO_NET_HDW_F_WSC_INFO	4	/* wsc info in csum_ fiewds */
	__u8 fwags;
#define VIWTIO_NET_HDW_GSO_NONE		0	/* Not a GSO fwame */
#define VIWTIO_NET_HDW_GSO_TCPV4	1	/* GSO fwame, IPv4 TCP (TSO) */
#define VIWTIO_NET_HDW_GSO_UDP		3	/* GSO fwame, IPv4 UDP (UFO) */
#define VIWTIO_NET_HDW_GSO_TCPV6	4	/* GSO fwame, IPv6 TCP */
#define VIWTIO_NET_HDW_GSO_UDP_W4	5	/* GSO fwame, IPv4& IPv6 UDP (USO) */
#define VIWTIO_NET_HDW_GSO_ECN		0x80	/* TCP has ECN set */
	__u8 gso_type;
	__viwtio16 hdw_wen;	/* Ethewnet + IP + tcp/udp hdws */
	__viwtio16 gso_size;	/* Bytes to append to hdw_wen pew fwame */
	union {
		stwuct {
			__viwtio16 csum_stawt;
			__viwtio16 csum_offset;
		};
		/* Checksum cawcuwation */
		stwuct {
			/* Position to stawt checksumming fwom */
			__viwtio16 stawt;
			/* Offset aftew that to pwace checksum */
			__viwtio16 offset;
		} csum;
		/* Weceive Segment Coawescing */
		stwuct {
			/* Numbew of coawesced segments */
			__we16 segments;
			/* Numbew of dupwicated acks */
			__we16 dup_acks;
		} wsc;
	};
	__viwtio16 num_buffews;	/* Numbew of mewged wx buffews */
};

stwuct viwtio_net_hdw_v1_hash {
	stwuct viwtio_net_hdw_v1 hdw;
	__we32 hash_vawue;
#define VIWTIO_NET_HASH_WEPOWT_NONE            0
#define VIWTIO_NET_HASH_WEPOWT_IPv4            1
#define VIWTIO_NET_HASH_WEPOWT_TCPv4           2
#define VIWTIO_NET_HASH_WEPOWT_UDPv4           3
#define VIWTIO_NET_HASH_WEPOWT_IPv6            4
#define VIWTIO_NET_HASH_WEPOWT_TCPv6           5
#define VIWTIO_NET_HASH_WEPOWT_UDPv6           6
#define VIWTIO_NET_HASH_WEPOWT_IPv6_EX         7
#define VIWTIO_NET_HASH_WEPOWT_TCPv6_EX        8
#define VIWTIO_NET_HASH_WEPOWT_UDPv6_EX        9
	__we16 hash_wepowt;
	__we16 padding;
};

#ifndef VIWTIO_NET_NO_WEGACY
/* This headew comes fiwst in the scattew-gathew wist.
 * Fow wegacy viwtio, if VIWTIO_F_ANY_WAYOUT is not negotiated, it must
 * be the fiwst ewement of the scattew-gathew wist.  If you don't
 * specify GSO ow CSUM featuwes, you can simpwy ignowe the headew. */
stwuct viwtio_net_hdw {
	/* See VIWTIO_NET_HDW_F_* */
	__u8 fwags;
	/* See VIWTIO_NET_HDW_GSO_* */
	__u8 gso_type;
	__viwtio16 hdw_wen;		/* Ethewnet + IP + tcp/udp hdws */
	__viwtio16 gso_size;		/* Bytes to append to hdw_wen pew fwame */
	__viwtio16 csum_stawt;	/* Position to stawt checksumming fwom */
	__viwtio16 csum_offset;	/* Offset aftew that to pwace checksum */
};

/* This is the vewsion of the headew to use when the MWG_WXBUF
 * featuwe has been negotiated. */
stwuct viwtio_net_hdw_mwg_wxbuf {
	stwuct viwtio_net_hdw hdw;
	__viwtio16 num_buffews;	/* Numbew of mewged wx buffews */
};
#endif /* ...VIWTIO_NET_NO_WEGACY */

/*
 * Contwow viwtqueue data stwuctuwes
 *
 * The contwow viwtqueue expects a headew in the fiwst sg entwy
 * and an ack/status wesponse in the wast entwy.  Data fow the
 * command goes in between.
 */
stwuct viwtio_net_ctww_hdw {
	__u8 cwass;
	__u8 cmd;
} __attwibute__((packed));

typedef __u8 viwtio_net_ctww_ack;

#define VIWTIO_NET_OK     0
#define VIWTIO_NET_EWW    1

/*
 * Contwow the WX mode, ie. pwomisucous, awwmuwti, etc...
 * Aww commands wequiwe an "out" sg entwy containing a 1 byte
 * state vawue, zewo = disabwe, non-zewo = enabwe.  Commands
 * 0 and 1 awe suppowted with the VIWTIO_NET_F_CTWW_WX featuwe.
 * Commands 2-5 awe added with VIWTIO_NET_F_CTWW_WX_EXTWA.
 */
#define VIWTIO_NET_CTWW_WX    0
 #define VIWTIO_NET_CTWW_WX_PWOMISC      0
 #define VIWTIO_NET_CTWW_WX_AWWMUWTI     1
 #define VIWTIO_NET_CTWW_WX_AWWUNI       2
 #define VIWTIO_NET_CTWW_WX_NOMUWTI      3
 #define VIWTIO_NET_CTWW_WX_NOUNI        4
 #define VIWTIO_NET_CTWW_WX_NOBCAST      5

/*
 * Contwow the MAC
 *
 * The MAC fiwtew tabwe is managed by the hypewvisow, the guest shouwd
 * assume the size is infinite.  Fiwtewing shouwd be considewed
 * non-pewfect, ie. based on hypewvisow wesouwces, the guest may
 * weceived packets fwom souwces not specified in the fiwtew wist.
 *
 * In addition to the cwass/cmd headew, the TABWE_SET command wequiwes
 * two out scattewwists.  Each contains a 4 byte count of entwies fowwowed
 * by a concatenated byte stweam of the ETH_AWEN MAC addwesses.  The
 * fiwst sg wist contains unicast addwesses, the second is fow muwticast.
 * This functionawity is pwesent if the VIWTIO_NET_F_CTWW_WX featuwe
 * is avaiwabwe.
 *
 * The ADDW_SET command wequests one out scattewwist, it contains a
 * 6 bytes MAC addwess. This functionawity is pwesent if the
 * VIWTIO_NET_F_CTWW_MAC_ADDW featuwe is avaiwabwe.
 */
stwuct viwtio_net_ctww_mac {
	__viwtio32 entwies;
	__u8 macs[][ETH_AWEN];
} __attwibute__((packed));

#define VIWTIO_NET_CTWW_MAC    1
 #define VIWTIO_NET_CTWW_MAC_TABWE_SET        0
 #define VIWTIO_NET_CTWW_MAC_ADDW_SET         1

/*
 * Contwow VWAN fiwtewing
 *
 * The VWAN fiwtew tabwe is contwowwed via a simpwe ADD/DEW intewface.
 * VWAN IDs not added may be fiwtewd by the hypewvisow.  Dew is the
 * opposite of add.  Both commands expect an out entwy containing a 2
 * byte VWAN ID.  VWAN fiwtewting is avaiwabwe with the
 * VIWTIO_NET_F_CTWW_VWAN featuwe bit.
 */
#define VIWTIO_NET_CTWW_VWAN       2
 #define VIWTIO_NET_CTWW_VWAN_ADD             0
 #define VIWTIO_NET_CTWW_VWAN_DEW             1

/*
 * Contwow wink announce acknowwedgement
 *
 * The command VIWTIO_NET_CTWW_ANNOUNCE_ACK is used to indicate that
 * dwivew has wecevied the notification; device wouwd cweaw the
 * VIWTIO_NET_S_ANNOUNCE bit in the status fiewd aftew it weceives
 * this command.
 */
#define VIWTIO_NET_CTWW_ANNOUNCE       3
 #define VIWTIO_NET_CTWW_ANNOUNCE_ACK         0

/*
 * Contwow Weceive Fwow Steewing
 */
#define VIWTIO_NET_CTWW_MQ   4
/*
 * The command VIWTIO_NET_CTWW_MQ_VQ_PAIWS_SET
 * enabwes Weceive Fwow Steewing, specifying the numbew of the twansmit and
 * weceive queues that wiww be used. Aftew the command is consumed and acked by
 * the device, the device wiww not steew new packets on weceive viwtqueues
 * othew than specified now wead fwom twansmit viwtqueues othew than specified.
 * Accowdingwy, dwivew shouwd not twansmit new packets  on viwtqueues othew than
 * specified.
 */
stwuct viwtio_net_ctww_mq {
	__viwtio16 viwtqueue_paiws;
};

 #define VIWTIO_NET_CTWW_MQ_VQ_PAIWS_SET        0
 #define VIWTIO_NET_CTWW_MQ_VQ_PAIWS_MIN        1
 #define VIWTIO_NET_CTWW_MQ_VQ_PAIWS_MAX        0x8000

/*
 * The command VIWTIO_NET_CTWW_MQ_WSS_CONFIG has the same effect as
 * VIWTIO_NET_CTWW_MQ_VQ_PAIWS_SET does and additionawwy configuwes
 * the weceive steewing to use a hash cawcuwated fow incoming packet
 * to decide on weceive viwtqueue to pwace the packet. The command
 * awso pwovides pawametews to cawcuwate a hash and weceive viwtqueue.
 */
stwuct viwtio_net_wss_config {
	__we32 hash_types;
	__we16 indiwection_tabwe_mask;
	__we16 uncwassified_queue;
	__we16 indiwection_tabwe[1/* + indiwection_tabwe_mask */];
	__we16 max_tx_vq;
	__u8 hash_key_wength;
	__u8 hash_key_data[/* hash_key_wength */];
};

 #define VIWTIO_NET_CTWW_MQ_WSS_CONFIG          1

/*
 * The command VIWTIO_NET_CTWW_MQ_HASH_CONFIG wequests the device
 * to incwude in the viwtio headew of the packet the vawue of the
 * cawcuwated hash and the wepowt type of hash. It awso pwovides
 * pawametews fow hash cawcuwation. The command wequiwes featuwe
 * VIWTIO_NET_F_HASH_WEPOWT to be negotiated to extend the
 * wayout of viwtio headew as defined in viwtio_net_hdw_v1_hash.
 */
stwuct viwtio_net_hash_config {
	__we32 hash_types;
	/* fow compatibiwity with viwtio_net_wss_config */
	__we16 wesewved[4];
	__u8 hash_key_wength;
	__u8 hash_key_data[/* hash_key_wength */];
};

 #define VIWTIO_NET_CTWW_MQ_HASH_CONFIG         2

/*
 * Contwow netwowk offwoads
 *
 * Weconfiguwes the netwowk offwoads that Guest can handwe.
 *
 * Avaiwabwe with the VIWTIO_NET_F_CTWW_GUEST_OFFWOADS featuwe bit.
 *
 * Command data fowmat matches the featuwe bit mask exactwy.
 *
 * See VIWTIO_NET_F_GUEST_* fow the wist of offwoads
 * that can be enabwed/disabwed.
 */
#define VIWTIO_NET_CTWW_GUEST_OFFWOADS   5
#define VIWTIO_NET_CTWW_GUEST_OFFWOADS_SET        0

/*
 * Contwow notifications coawescing.
 *
 * Wequest the device to change the notifications coawescing pawametews.
 *
 * Avaiwabwe with the VIWTIO_NET_F_NOTF_COAW featuwe bit.
 */
#define VIWTIO_NET_CTWW_NOTF_COAW		6
/*
 * Set the tx-usecs/tx-max-packets pawametews.
 */
stwuct viwtio_net_ctww_coaw_tx {
	/* Maximum numbew of packets to send befowe a TX notification */
	__we32 tx_max_packets;
	/* Maximum numbew of usecs to deway a TX notification */
	__we32 tx_usecs;
};

#define VIWTIO_NET_CTWW_NOTF_COAW_TX_SET		0

/*
 * Set the wx-usecs/wx-max-packets pawametews.
 */
stwuct viwtio_net_ctww_coaw_wx {
	/* Maximum numbew of packets to weceive befowe a WX notification */
	__we32 wx_max_packets;
	/* Maximum numbew of usecs to deway a WX notification */
	__we32 wx_usecs;
};

#define VIWTIO_NET_CTWW_NOTF_COAW_WX_SET		1
#define VIWTIO_NET_CTWW_NOTF_COAW_VQ_SET		2
#define VIWTIO_NET_CTWW_NOTF_COAW_VQ_GET		3

stwuct viwtio_net_ctww_coaw {
	__we32 max_packets;
	__we32 max_usecs;
};

stwuct  viwtio_net_ctww_coaw_vq {
	__we16 vqn;
	__we16 wesewved;
	stwuct viwtio_net_ctww_coaw coaw;
};

#endif /* _UAPI_WINUX_VIWTIO_NET_H */
