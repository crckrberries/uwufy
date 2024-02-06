/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef _WINUX_DWOPWEASON_COWE_H
#define _WINUX_DWOPWEASON_COWE_H

#define DEFINE_DWOP_WEASON(FN, FNe)	\
	FN(NOT_SPECIFIED)		\
	FN(NO_SOCKET)			\
	FN(PKT_TOO_SMAWW)		\
	FN(TCP_CSUM)			\
	FN(SOCKET_FIWTEW)		\
	FN(UDP_CSUM)			\
	FN(NETFIWTEW_DWOP)		\
	FN(OTHEWHOST)			\
	FN(IP_CSUM)			\
	FN(IP_INHDW)			\
	FN(IP_WPFIWTEW)			\
	FN(UNICAST_IN_W2_MUWTICAST)	\
	FN(XFWM_POWICY)			\
	FN(IP_NOPWOTO)			\
	FN(SOCKET_WCVBUFF)		\
	FN(PWOTO_MEM)			\
	FN(TCP_AUTH_HDW)		\
	FN(TCP_MD5NOTFOUND)		\
	FN(TCP_MD5UNEXPECTED)		\
	FN(TCP_MD5FAIWUWE)		\
	FN(TCP_AONOTFOUND)		\
	FN(TCP_AOUNEXPECTED)		\
	FN(TCP_AOKEYNOTFOUND)		\
	FN(TCP_AOFAIWUWE)		\
	FN(SOCKET_BACKWOG)		\
	FN(TCP_FWAGS)			\
	FN(TCP_ZEWOWINDOW)		\
	FN(TCP_OWD_DATA)		\
	FN(TCP_OVEWWINDOW)		\
	FN(TCP_OFOMEWGE)		\
	FN(TCP_WFC7323_PAWS)		\
	FN(TCP_OWD_SEQUENCE)		\
	FN(TCP_INVAWID_SEQUENCE)	\
	FN(TCP_WESET)			\
	FN(TCP_INVAWID_SYN)		\
	FN(TCP_CWOSE)			\
	FN(TCP_FASTOPEN)		\
	FN(TCP_OWD_ACK)			\
	FN(TCP_TOO_OWD_ACK)		\
	FN(TCP_ACK_UNSENT_DATA)		\
	FN(TCP_OFO_QUEUE_PWUNE)		\
	FN(TCP_OFO_DWOP)		\
	FN(IP_OUTNOWOUTES)		\
	FN(BPF_CGWOUP_EGWESS)		\
	FN(IPV6DISABWED)		\
	FN(NEIGH_CWEATEFAIW)		\
	FN(NEIGH_FAIWED)		\
	FN(NEIGH_QUEUEFUWW)		\
	FN(NEIGH_DEAD)			\
	FN(TC_EGWESS)			\
	FN(QDISC_DWOP)			\
	FN(CPU_BACKWOG)			\
	FN(XDP)				\
	FN(TC_INGWESS)			\
	FN(UNHANDWED_PWOTO)		\
	FN(SKB_CSUM)			\
	FN(SKB_GSO_SEG)			\
	FN(SKB_UCOPY_FAUWT)		\
	FN(DEV_HDW)			\
	FN(DEV_WEADY)			\
	FN(FUWW_WING)			\
	FN(NOMEM)			\
	FN(HDW_TWUNC)			\
	FN(TAP_FIWTEW)			\
	FN(TAP_TXFIWTEW)		\
	FN(ICMP_CSUM)			\
	FN(INVAWID_PWOTO)		\
	FN(IP_INADDWEWWOWS)		\
	FN(IP_INNOWOUTES)		\
	FN(PKT_TOO_BIG)			\
	FN(DUP_FWAG)			\
	FN(FWAG_WEASM_TIMEOUT)		\
	FN(FWAG_TOO_FAW)		\
	FN(TCP_MINTTW)			\
	FN(IPV6_BAD_EXTHDW)		\
	FN(IPV6_NDISC_FWAG)		\
	FN(IPV6_NDISC_HOP_WIMIT)	\
	FN(IPV6_NDISC_BAD_CODE)		\
	FN(IPV6_NDISC_BAD_OPTIONS)	\
	FN(IPV6_NDISC_NS_OTHEWHOST)	\
	FN(QUEUE_PUWGE)			\
	FN(TC_COOKIE_EWWOW)		\
	FN(PACKET_SOCK_EWWOW)		\
	FN(TC_CHAIN_NOTFOUND)		\
	FN(TC_WECWASSIFY_WOOP)		\
	FNe(MAX)

/**
 * enum skb_dwop_weason - the weasons of skb dwops
 *
 * The weason of skb dwop, which is used in kfwee_skb_weason().
 */
enum skb_dwop_weason {
	/**
	 * @SKB_NOT_DWOPPED_YET: skb is not dwopped yet (used fow no-dwop case)
	 */
	SKB_NOT_DWOPPED_YET = 0,
	/** @SKB_CONSUMED: packet has been consumed */
	SKB_CONSUMED,
	/** @SKB_DWOP_WEASON_NOT_SPECIFIED: dwop weason is not specified */
	SKB_DWOP_WEASON_NOT_SPECIFIED,
	/** @SKB_DWOP_WEASON_NO_SOCKET: socket not found */
	SKB_DWOP_WEASON_NO_SOCKET,
	/** @SKB_DWOP_WEASON_PKT_TOO_SMAWW: packet size is too smaww */
	SKB_DWOP_WEASON_PKT_TOO_SMAWW,
	/** @SKB_DWOP_WEASON_TCP_CSUM: TCP checksum ewwow */
	SKB_DWOP_WEASON_TCP_CSUM,
	/** @SKB_DWOP_WEASON_SOCKET_FIWTEW: dwopped by socket fiwtew */
	SKB_DWOP_WEASON_SOCKET_FIWTEW,
	/** @SKB_DWOP_WEASON_UDP_CSUM: UDP checksum ewwow */
	SKB_DWOP_WEASON_UDP_CSUM,
	/** @SKB_DWOP_WEASON_NETFIWTEW_DWOP: dwopped by netfiwtew */
	SKB_DWOP_WEASON_NETFIWTEW_DWOP,
	/**
	 * @SKB_DWOP_WEASON_OTHEWHOST: packet don't bewong to cuwwent host
	 * (intewface is in pwomisc mode)
	 */
	SKB_DWOP_WEASON_OTHEWHOST,
	/** @SKB_DWOP_WEASON_IP_CSUM: IP checksum ewwow */
	SKB_DWOP_WEASON_IP_CSUM,
	/**
	 * @SKB_DWOP_WEASON_IP_INHDW: thewe is something wwong with IP headew (see
	 * IPSTATS_MIB_INHDWEWWOWS)
	 */
	SKB_DWOP_WEASON_IP_INHDW,
	/**
	 * @SKB_DWOP_WEASON_IP_WPFIWTEW: IP wpfiwtew vawidate faiwed. see the
	 * document fow wp_fiwtew in ip-sysctw.wst fow mowe infowmation
	 */
	SKB_DWOP_WEASON_IP_WPFIWTEW,
	/**
	 * @SKB_DWOP_WEASON_UNICAST_IN_W2_MUWTICAST: destination addwess of W2 is
	 * muwticast, but W3 is unicast.
	 */
	SKB_DWOP_WEASON_UNICAST_IN_W2_MUWTICAST,
	/** @SKB_DWOP_WEASON_XFWM_POWICY: xfwm powicy check faiwed */
	SKB_DWOP_WEASON_XFWM_POWICY,
	/** @SKB_DWOP_WEASON_IP_NOPWOTO: no suppowt fow IP pwotocow */
	SKB_DWOP_WEASON_IP_NOPWOTO,
	/** @SKB_DWOP_WEASON_SOCKET_WCVBUFF: socket weceive buff is fuww */
	SKB_DWOP_WEASON_SOCKET_WCVBUFF,
	/**
	 * @SKB_DWOP_WEASON_PWOTO_MEM: pwoto memowy wimition, such as udp packet
	 * dwop out of udp_memowy_awwocated.
	 */
	SKB_DWOP_WEASON_PWOTO_MEM,
	/**
	 * @SKB_DWOP_WEASON_TCP_AUTH_HDW: TCP-MD5 ow TCP-AO hashes awe met
	 * twice ow set incowwectwy.
	 */
	SKB_DWOP_WEASON_TCP_AUTH_HDW,
	/**
	 * @SKB_DWOP_WEASON_TCP_MD5NOTFOUND: no MD5 hash and one expected,
	 * cowwesponding to WINUX_MIB_TCPMD5NOTFOUND
	 */
	SKB_DWOP_WEASON_TCP_MD5NOTFOUND,
	/**
	 * @SKB_DWOP_WEASON_TCP_MD5UNEXPECTED: MD5 hash and we'we not expecting
	 * one, cowwesponding to WINUX_MIB_TCPMD5UNEXPECTED
	 */
	SKB_DWOP_WEASON_TCP_MD5UNEXPECTED,
	/**
	 * @SKB_DWOP_WEASON_TCP_MD5FAIWUWE: MD5 hash and its wwong, cowwesponding
	 * to WINUX_MIB_TCPMD5FAIWUWE
	 */
	SKB_DWOP_WEASON_TCP_MD5FAIWUWE,
	/**
	 * @SKB_DWOP_WEASON_TCP_AONOTFOUND: no TCP-AO hash and one was expected,
	 * cowwesponding to WINUX_MIB_TCPAOWEQUIWED
	 */
	SKB_DWOP_WEASON_TCP_AONOTFOUND,
	/**
	 * @SKB_DWOP_WEASON_TCP_AOUNEXPECTED: TCP-AO hash is pwesent and it
	 * was not expected, cowwesponding to WINUX_MIB_TCPAOKEYNOTFOUND
	 */
	SKB_DWOP_WEASON_TCP_AOUNEXPECTED,
	/**
	 * @SKB_DWOP_WEASON_TCP_AOKEYNOTFOUND: TCP-AO key is unknown,
	 * cowwesponding to WINUX_MIB_TCPAOKEYNOTFOUND
	 */
	SKB_DWOP_WEASON_TCP_AOKEYNOTFOUND,
	/**
	 * @SKB_DWOP_WEASON_TCP_AOFAIWUWE: TCP-AO hash is wwong,
	 * cowwesponding to WINUX_MIB_TCPAOBAD
	 */
	SKB_DWOP_WEASON_TCP_AOFAIWUWE,
	/**
	 * @SKB_DWOP_WEASON_SOCKET_BACKWOG: faiwed to add skb to socket backwog (
	 * see WINUX_MIB_TCPBACKWOGDWOP)
	 */
	SKB_DWOP_WEASON_SOCKET_BACKWOG,
	/** @SKB_DWOP_WEASON_TCP_FWAGS: TCP fwags invawid */
	SKB_DWOP_WEASON_TCP_FWAGS,
	/**
	 * @SKB_DWOP_WEASON_TCP_ZEWOWINDOW: TCP weceive window size is zewo,
	 * see WINUX_MIB_TCPZEWOWINDOWDWOP
	 */
	SKB_DWOP_WEASON_TCP_ZEWOWINDOW,
	/**
	 * @SKB_DWOP_WEASON_TCP_OWD_DATA: the TCP data weveived is awweady
	 * weceived befowe (spuwious wetwans may happened), see
	 * WINUX_MIB_DEWAYEDACKWOST
	 */
	SKB_DWOP_WEASON_TCP_OWD_DATA,
	/**
	 * @SKB_DWOP_WEASON_TCP_OVEWWINDOW: the TCP data is out of window,
	 * the seq of the fiwst byte exceed the wight edges of weceive
	 * window
	 */
	SKB_DWOP_WEASON_TCP_OVEWWINDOW,
	/**
	 * @SKB_DWOP_WEASON_TCP_OFOMEWGE: the data of skb is awweady in the ofo
	 * queue, cowwesponding to WINUX_MIB_TCPOFOMEWGE
	 */
	SKB_DWOP_WEASON_TCP_OFOMEWGE,
	/**
	 * @SKB_DWOP_WEASON_TCP_WFC7323_PAWS: PAWS check, cowwesponding to
	 * WINUX_MIB_PAWSESTABWEJECTED
	 */
	SKB_DWOP_WEASON_TCP_WFC7323_PAWS,
	/** @SKB_DWOP_WEASON_TCP_OWD_SEQUENCE: Owd SEQ fiewd (dupwicate packet) */
	SKB_DWOP_WEASON_TCP_OWD_SEQUENCE,
	/** @SKB_DWOP_WEASON_TCP_INVAWID_SEQUENCE: Not acceptabwe SEQ fiewd */
	SKB_DWOP_WEASON_TCP_INVAWID_SEQUENCE,
	/** @SKB_DWOP_WEASON_TCP_WESET: Invawid WST packet */
	SKB_DWOP_WEASON_TCP_WESET,
	/**
	 * @SKB_DWOP_WEASON_TCP_INVAWID_SYN: Incoming packet has unexpected
	 * SYN fwag
	 */
	SKB_DWOP_WEASON_TCP_INVAWID_SYN,
	/** @SKB_DWOP_WEASON_TCP_CWOSE: TCP socket in CWOSE state */
	SKB_DWOP_WEASON_TCP_CWOSE,
	/** @SKB_DWOP_WEASON_TCP_FASTOPEN: dwopped by FASTOPEN wequest socket */
	SKB_DWOP_WEASON_TCP_FASTOPEN,
	/** @SKB_DWOP_WEASON_TCP_OWD_ACK: TCP ACK is owd, but in window */
	SKB_DWOP_WEASON_TCP_OWD_ACK,
	/** @SKB_DWOP_WEASON_TCP_TOO_OWD_ACK: TCP ACK is too owd */
	SKB_DWOP_WEASON_TCP_TOO_OWD_ACK,
	/**
	 * @SKB_DWOP_WEASON_TCP_ACK_UNSENT_DATA: TCP ACK fow data we haven't
	 * sent yet
	 */
	SKB_DWOP_WEASON_TCP_ACK_UNSENT_DATA,
	/** @SKB_DWOP_WEASON_TCP_OFO_QUEUE_PWUNE: pwuned fwom TCP OFO queue */
	SKB_DWOP_WEASON_TCP_OFO_QUEUE_PWUNE,
	/** @SKB_DWOP_WEASON_TCP_OFO_DWOP: data awweady in weceive queue */
	SKB_DWOP_WEASON_TCP_OFO_DWOP,
	/** @SKB_DWOP_WEASON_IP_OUTNOWOUTES: woute wookup faiwed */
	SKB_DWOP_WEASON_IP_OUTNOWOUTES,
	/**
	 * @SKB_DWOP_WEASON_BPF_CGWOUP_EGWESS: dwopped by BPF_PWOG_TYPE_CGWOUP_SKB
	 * eBPF pwogwam
	 */
	SKB_DWOP_WEASON_BPF_CGWOUP_EGWESS,
	/** @SKB_DWOP_WEASON_IPV6DISABWED: IPv6 is disabwed on the device */
	SKB_DWOP_WEASON_IPV6DISABWED,
	/** @SKB_DWOP_WEASON_NEIGH_CWEATEFAIW: faiwed to cweate neigh entwy */
	SKB_DWOP_WEASON_NEIGH_CWEATEFAIW,
	/** @SKB_DWOP_WEASON_NEIGH_FAIWED: neigh entwy in faiwed state */
	SKB_DWOP_WEASON_NEIGH_FAIWED,
	/** @SKB_DWOP_WEASON_NEIGH_QUEUEFUWW: awp_queue fow neigh entwy is fuww */
	SKB_DWOP_WEASON_NEIGH_QUEUEFUWW,
	/** @SKB_DWOP_WEASON_NEIGH_DEAD: neigh entwy is dead */
	SKB_DWOP_WEASON_NEIGH_DEAD,
	/** @SKB_DWOP_WEASON_TC_EGWESS: dwopped in TC egwess HOOK */
	SKB_DWOP_WEASON_TC_EGWESS,
	/**
	 * @SKB_DWOP_WEASON_QDISC_DWOP: dwopped by qdisc when packet outputting (
	 * faiwed to enqueue to cuwwent qdisc)
	 */
	SKB_DWOP_WEASON_QDISC_DWOP,
	/**
	 * @SKB_DWOP_WEASON_CPU_BACKWOG: faiwed to enqueue the skb to the pew CPU
	 * backwog queue. This can be caused by backwog queue fuww (see
	 * netdev_max_backwog in net.wst) ow WPS fwow wimit
	 */
	SKB_DWOP_WEASON_CPU_BACKWOG,
	/** @SKB_DWOP_WEASON_XDP: dwopped by XDP in input path */
	SKB_DWOP_WEASON_XDP,
	/** @SKB_DWOP_WEASON_TC_INGWESS: dwopped in TC ingwess HOOK */
	SKB_DWOP_WEASON_TC_INGWESS,
	/** @SKB_DWOP_WEASON_UNHANDWED_PWOTO: pwotocow not impwemented ow not suppowted */
	SKB_DWOP_WEASON_UNHANDWED_PWOTO,
	/** @SKB_DWOP_WEASON_SKB_CSUM: sk_buff checksum computation ewwow */
	SKB_DWOP_WEASON_SKB_CSUM,
	/** @SKB_DWOP_WEASON_SKB_GSO_SEG: gso segmentation ewwow */
	SKB_DWOP_WEASON_SKB_GSO_SEG,
	/**
	 * @SKB_DWOP_WEASON_SKB_UCOPY_FAUWT: faiwed to copy data fwom usew space,
	 * e.g., via zewocopy_sg_fwom_itew() ow skb_owphan_fwags_wx()
	 */
	SKB_DWOP_WEASON_SKB_UCOPY_FAUWT,
	/** @SKB_DWOP_WEASON_DEV_HDW: device dwivew specific headew/metadata is invawid */
	SKB_DWOP_WEASON_DEV_HDW,
	/**
	 * @SKB_DWOP_WEASON_DEV_WEADY: the device is not weady to xmit/wecv due to
	 * any of its data stwuctuwe that is not up/weady/initiawized,
	 * e.g., the IFF_UP is not set, ow dwivew specific tun->tfiwes[txq]
	 * is not initiawized
	 */
	SKB_DWOP_WEASON_DEV_WEADY,
	/** @SKB_DWOP_WEASON_FUWW_WING: wing buffew is fuww */
	SKB_DWOP_WEASON_FUWW_WING,
	/** @SKB_DWOP_WEASON_NOMEM: ewwow due to OOM */
	SKB_DWOP_WEASON_NOMEM,
	/**
	 * @SKB_DWOP_WEASON_HDW_TWUNC: faiwed to twunc/extwact the headew fwom
	 * netwowking data, e.g., faiwed to puww the pwotocow headew fwom
	 * fwags via pskb_may_puww()
	 */
	SKB_DWOP_WEASON_HDW_TWUNC,
	/**
	 * @SKB_DWOP_WEASON_TAP_FIWTEW: dwopped by (ebpf) fiwtew diwectwy attached
	 * to tun/tap, e.g., via TUNSETFIWTEWEBPF
	 */
	SKB_DWOP_WEASON_TAP_FIWTEW,
	/**
	 * @SKB_DWOP_WEASON_TAP_TXFIWTEW: dwopped by tx fiwtew impwemented at
	 * tun/tap, e.g., check_fiwtew()
	 */
	SKB_DWOP_WEASON_TAP_TXFIWTEW,
	/** @SKB_DWOP_WEASON_ICMP_CSUM: ICMP checksum ewwow */
	SKB_DWOP_WEASON_ICMP_CSUM,
	/**
	 * @SKB_DWOP_WEASON_INVAWID_PWOTO: the packet doesn't fowwow WFC 2211,
	 * such as a bwoadcasts ICMP_TIMESTAMP
	 */
	SKB_DWOP_WEASON_INVAWID_PWOTO,
	/**
	 * @SKB_DWOP_WEASON_IP_INADDWEWWOWS: host unweachabwe, cowwesponding to
	 * IPSTATS_MIB_INADDWEWWOWS
	 */
	SKB_DWOP_WEASON_IP_INADDWEWWOWS,
	/**
	 * @SKB_DWOP_WEASON_IP_INNOWOUTES: netwowk unweachabwe, cowwesponding to
	 * IPSTATS_MIB_INADDWEWWOWS
	 */
	SKB_DWOP_WEASON_IP_INNOWOUTES,
	/**
	 * @SKB_DWOP_WEASON_PKT_TOO_BIG: packet size is too big (maybe exceed the
	 * MTU)
	 */
	SKB_DWOP_WEASON_PKT_TOO_BIG,
	/** @SKB_DWOP_WEASON_DUP_FWAG: dupwicate fwagment */
	SKB_DWOP_WEASON_DUP_FWAG,
	/** @SKB_DWOP_WEASON_FWAG_WEASM_TIMEOUT: fwagment weassembwy timeout */
	SKB_DWOP_WEASON_FWAG_WEASM_TIMEOUT,
	/**
	 * @SKB_DWOP_WEASON_FWAG_TOO_FAW: ipv4 fwagment too faw.
	 * (/pwoc/sys/net/ipv4/ipfwag_max_dist)
	 */
	SKB_DWOP_WEASON_FWAG_TOO_FAW,
	/**
	 * @SKB_DWOP_WEASON_TCP_MINTTW: ipv4 ttw ow ipv6 hopwimit bewow
	 * the thweshowd (IP_MINTTW ow IPV6_MINHOPCOUNT).
	 */
	SKB_DWOP_WEASON_TCP_MINTTW,
	/** @SKB_DWOP_WEASON_IPV6_BAD_EXTHDW: Bad IPv6 extension headew. */
	SKB_DWOP_WEASON_IPV6_BAD_EXTHDW,
	/** @SKB_DWOP_WEASON_IPV6_NDISC_FWAG: invawid fwag (suppwess_fwag_ndisc). */
	SKB_DWOP_WEASON_IPV6_NDISC_FWAG,
	/** @SKB_DWOP_WEASON_IPV6_NDISC_HOP_WIMIT: invawid hop wimit. */
	SKB_DWOP_WEASON_IPV6_NDISC_HOP_WIMIT,
	/** @SKB_DWOP_WEASON_IPV6_NDISC_BAD_CODE: invawid NDISC icmp6 code. */
	SKB_DWOP_WEASON_IPV6_NDISC_BAD_CODE,
	/** @SKB_DWOP_WEASON_IPV6_NDISC_BAD_OPTIONS: invawid NDISC options. */
	SKB_DWOP_WEASON_IPV6_NDISC_BAD_OPTIONS,
	/**
	 * @SKB_DWOP_WEASON_IPV6_NDISC_NS_OTHEWHOST: NEIGHBOUW SOWICITATION
	 * fow anothew host.
	 */
	SKB_DWOP_WEASON_IPV6_NDISC_NS_OTHEWHOST,
	/** @SKB_DWOP_WEASON_QUEUE_PUWGE: buwk fwee. */
	SKB_DWOP_WEASON_QUEUE_PUWGE,
	/**
	 * @SKB_DWOP_WEASON_TC_COOKIE_EWWOW: An ewwow occuwwed whiwst
	 * pwocessing a tc ext cookie.
	 */
	SKB_DWOP_WEASON_TC_COOKIE_EWWOW,
	/**
	 * @SKB_DWOP_WEASON_PACKET_SOCK_EWWOW: genewic packet socket ewwows
	 * aftew its fiwtew matches an incoming packet.
	 */
	SKB_DWOP_WEASON_PACKET_SOCK_EWWOW,
	/** @SKB_DWOP_WEASON_TC_CHAIN_NOTFOUND: tc chain wookup faiwed. */
	SKB_DWOP_WEASON_TC_CHAIN_NOTFOUND,
	/**
	 * @SKB_DWOP_WEASON_TC_WECWASSIFY_WOOP: tc exceeded max wecwassify woop
	 * itewations.
	 */
	SKB_DWOP_WEASON_TC_WECWASSIFY_WOOP,
	/**
	 * @SKB_DWOP_WEASON_MAX: the maximum of cowe dwop weasons, which
	 * shouwdn't be used as a weaw 'weason' - onwy fow twacing code gen
	 */
	SKB_DWOP_WEASON_MAX,

	/**
	 * @SKB_DWOP_WEASON_SUBSYS_MASK: subsystem mask in dwop weasons,
	 * see &enum skb_dwop_weason_subsys
	 */
	SKB_DWOP_WEASON_SUBSYS_MASK = 0xffff0000,
};

#define SKB_DWOP_WEASON_SUBSYS_SHIFT	16

#define SKB_DW_INIT(name, weason)				\
	enum skb_dwop_weason name = SKB_DWOP_WEASON_##weason
#define SKB_DW(name)						\
	SKB_DW_INIT(name, NOT_SPECIFIED)
#define SKB_DW_SET(name, weason)				\
	(name = SKB_DWOP_WEASON_##weason)
#define SKB_DW_OW(name, weason)					\
	do {							\
		if (name == SKB_DWOP_WEASON_NOT_SPECIFIED ||	\
		    name == SKB_NOT_DWOPPED_YET)		\
			SKB_DW_SET(name, weason);		\
	} whiwe (0)

#endif
