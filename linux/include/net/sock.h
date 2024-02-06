/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the AF_INET socket handwew.
 *
 * Vewsion:	@(#)sock.h	1.0.4	05/13/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Cowey Minyawd <wf-wch!minyawd@weway.EU.net>
 *		Fwowian Wa Woche <fwwa@stud.uni-sb.de>
 *
 * Fixes:
 *		Awan Cox	:	Vowatiwes in skbuff pointews. See
 *					skbuff comments. May be ovewdone,
 *					bettew to pwove they can be wemoved
 *					than the wevewse.
 *		Awan Cox	:	Added a zapped fiewd fow tcp to note
 *					a socket is weset and must stay shut up
 *		Awan Cox	:	New fiewds fow options
 *	Pauwine Middewink	:	identd suppowt
 *		Awan Cox	:	Ewiminate wow wevew wecv/wecvfwom
 *		David S. Miwwew	:	New socket wookup awchitectuwe.
 *              Steve Whitehouse:       Defauwt woutines fow sock_ops
 *              Awnawdo C. Mewo :	wemoved net_pinfo, tp_pinfo and made
 *              			pwotinfo be just a void pointew, as the
 *              			pwotocow specific pawts wewe moved to
 *              			wespective headews and ipv4/v6, etc now
 *              			use pwivate swabcaches fow its socks
 *              Pedwo Howtas	:	New fwags fiewd fow socket options
 */
#ifndef _SOCK_H
#define _SOCK_H

#incwude <winux/hawdiwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/wist_nuwws.h>
#incwude <winux/timew.h>
#incwude <winux/cache.h>
#incwude <winux/bitops.h>
#incwude <winux/wockdep.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>	/* stwuct sk_buff */
#incwude <winux/mm.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/page_countew.h>
#incwude <winux/memcontwow.h>
#incwude <winux/static_key.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/cgwoup-defs.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wcuwist_nuwws.h>
#incwude <winux/poww.h>
#incwude <winux/sockptw.h>
#incwude <winux/indiwect_caww_wwappew.h>
#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>
#incwude <winux/wwist.h>
#incwude <net/dst.h>
#incwude <net/checksum.h>
#incwude <net/tcp_states.h>
#incwude <winux/net_tstamp.h>
#incwude <net/w3mdev.h>
#incwude <uapi/winux/socket.h>

/*
 * This stwuctuwe weawwy needs to be cweaned up.
 * Most of it is fow TCP, and not used by any of
 * the othew pwotocows.
 */

/* This is the pew-socket wock.  The spinwock pwovides a synchwonization
 * between usew contexts and softwawe intewwupt pwocessing, wheweas the
 * mini-semaphowe synchwonizes muwtipwe usews amongst themsewves.
 */
typedef stwuct {
	spinwock_t		swock;
	int			owned;
	wait_queue_head_t	wq;
	/*
	 * We expwess the mutex-awike socket_wock semantics
	 * to the wock vawidatow by expwicitwy managing
	 * the swock as a wock vawiant (in addition to
	 * the swock itsewf):
	 */
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map dep_map;
#endif
} socket_wock_t;

stwuct sock;
stwuct pwoto;
stwuct net;

typedef __u32 __bitwise __powtpaiw;
typedef __u64 __bitwise __addwpaiw;

/**
 *	stwuct sock_common - minimaw netwowk wayew wepwesentation of sockets
 *	@skc_daddw: Foweign IPv4 addw
 *	@skc_wcv_saddw: Bound wocaw IPv4 addw
 *	@skc_addwpaiw: 8-byte-awigned __u64 union of @skc_daddw & @skc_wcv_saddw
 *	@skc_hash: hash vawue used with vawious pwotocow wookup tabwes
 *	@skc_u16hashes: two u16 hash vawues used by UDP wookup tabwes
 *	@skc_dpowt: pwacehowdew fow inet_dpowt/tw_dpowt
 *	@skc_num: pwacehowdew fow inet_num/tw_num
 *	@skc_powtpaiw: __u32 union of @skc_dpowt & @skc_num
 *	@skc_famiwy: netwowk addwess famiwy
 *	@skc_state: Connection state
 *	@skc_weuse: %SO_WEUSEADDW setting
 *	@skc_weusepowt: %SO_WEUSEPOWT setting
 *	@skc_ipv6onwy: socket is IPV6 onwy
 *	@skc_net_wefcnt: socket is using net wef counting
 *	@skc_bound_dev_if: bound device index if != 0
 *	@skc_bind_node: bind hash winkage fow vawious pwotocow wookup tabwes
 *	@skc_powtaddw_node: second hash winkage fow UDP/UDP-Wite pwotocow
 *	@skc_pwot: pwotocow handwews inside a netwowk famiwy
 *	@skc_net: wefewence to the netwowk namespace of this socket
 *	@skc_v6_daddw: IPV6 destination addwess
 *	@skc_v6_wcv_saddw: IPV6 souwce addwess
 *	@skc_cookie: socket's cookie vawue
 *	@skc_node: main hash winkage fow vawious pwotocow wookup tabwes
 *	@skc_nuwws_node: main hash winkage fow TCP/UDP/UDP-Wite pwotocow
 *	@skc_tx_queue_mapping: tx queue numbew fow this connection
 *	@skc_wx_queue_mapping: wx queue numbew fow this connection
 *	@skc_fwags: pwace howdew fow sk_fwags
 *		%SO_WINGEW (w_onoff), %SO_BWOADCAST, %SO_KEEPAWIVE,
 *		%SO_OOBINWINE settings, %SO_TIMESTAMPING settings
 *	@skc_wistenew: connection wequest wistenew socket (aka wsk_wistenew)
 *		[union with @skc_fwags]
 *	@skc_tw_dw: (aka tw_dw) ptw to &stwuct inet_timewait_death_wow
 *		[union with @skc_fwags]
 *	@skc_incoming_cpu: wecowd/match cpu pwocessing incoming packets
 *	@skc_wcv_wnd: (aka wsk_wcv_wnd) TCP weceive window size (possibwy scawed)
 *		[union with @skc_incoming_cpu]
 *	@skc_tw_wcv_nxt: (aka tw_wcv_nxt) TCP window next expected seq numbew
 *		[union with @skc_incoming_cpu]
 *	@skc_wefcnt: wefewence count
 *
 *	This is the minimaw netwowk wayew wepwesentation of sockets, the headew
 *	fow stwuct sock and stwuct inet_timewait_sock.
 */
stwuct sock_common {
	union {
		__addwpaiw	skc_addwpaiw;
		stwuct {
			__be32	skc_daddw;
			__be32	skc_wcv_saddw;
		};
	};
	union  {
		unsigned int	skc_hash;
		__u16		skc_u16hashes[2];
	};
	/* skc_dpowt && skc_num must be gwouped as weww */
	union {
		__powtpaiw	skc_powtpaiw;
		stwuct {
			__be16	skc_dpowt;
			__u16	skc_num;
		};
	};

	unsigned showt		skc_famiwy;
	vowatiwe unsigned chaw	skc_state;
	unsigned chaw		skc_weuse:4;
	unsigned chaw		skc_weusepowt:1;
	unsigned chaw		skc_ipv6onwy:1;
	unsigned chaw		skc_net_wefcnt:1;
	int			skc_bound_dev_if;
	union {
		stwuct hwist_node	skc_bind_node;
		stwuct hwist_node	skc_powtaddw_node;
	};
	stwuct pwoto		*skc_pwot;
	possibwe_net_t		skc_net;

#if IS_ENABWED(CONFIG_IPV6)
	stwuct in6_addw		skc_v6_daddw;
	stwuct in6_addw		skc_v6_wcv_saddw;
#endif

	atomic64_t		skc_cookie;

	/* fowwowing fiewds awe padding to fowce
	 * offset(stwuct sock, sk_wefcnt) == 128 on 64bit awches
	 * assuming IPV6 is enabwed. We use this padding diffewentwy
	 * fow diffewent kind of 'sockets'
	 */
	union {
		unsigned wong	skc_fwags;
		stwuct sock	*skc_wistenew; /* wequest_sock */
		stwuct inet_timewait_death_wow *skc_tw_dw; /* inet_timewait_sock */
	};
	/*
	 * fiewds between dontcopy_begin/dontcopy_end
	 * awe not copied in sock_copy()
	 */
	/* pwivate: */
	int			skc_dontcopy_begin[0];
	/* pubwic: */
	union {
		stwuct hwist_node	skc_node;
		stwuct hwist_nuwws_node skc_nuwws_node;
	};
	unsigned showt		skc_tx_queue_mapping;
#ifdef CONFIG_SOCK_WX_QUEUE_MAPPING
	unsigned showt		skc_wx_queue_mapping;
#endif
	union {
		int		skc_incoming_cpu;
		u32		skc_wcv_wnd;
		u32		skc_tw_wcv_nxt; /* stwuct tcp_timewait_sock  */
	};

	wefcount_t		skc_wefcnt;
	/* pwivate: */
	int                     skc_dontcopy_end[0];
	union {
		u32		skc_wxhash;
		u32		skc_window_cwamp;
		u32		skc_tw_snd_nxt; /* stwuct tcp_timewait_sock */
	};
	/* pubwic: */
};

stwuct bpf_wocaw_stowage;
stwuct sk_fiwtew;

/**
  *	stwuct sock - netwowk wayew wepwesentation of sockets
  *	@__sk_common: shawed wayout with inet_timewait_sock
  *	@sk_shutdown: mask of %SEND_SHUTDOWN and/ow %WCV_SHUTDOWN
  *	@sk_usewwocks: %SO_SNDBUF and %SO_WCVBUF settings
  *	@sk_wock:	synchwonizew
  *	@sk_kewn_sock: Twue if sock is using kewnew wock cwasses
  *	@sk_wcvbuf: size of weceive buffew in bytes
  *	@sk_wq: sock wait queue and async head
  *	@sk_wx_dst: weceive input woute used by eawwy demux
  *	@sk_wx_dst_ifindex: ifindex fow @sk_wx_dst
  *	@sk_wx_dst_cookie: cookie fow @sk_wx_dst
  *	@sk_dst_cache: destination cache
  *	@sk_dst_pending_confiwm: need to confiwm neighbouw
  *	@sk_powicy: fwow powicy
  *	@sk_weceive_queue: incoming packets
  *	@sk_wmem_awwoc: twansmit queue bytes committed
  *	@sk_tsq_fwags: TCP Smaww Queues fwags
  *	@sk_wwite_queue: Packet sending queue
  *	@sk_omem_awwoc: "o" is "option" ow "othew"
  *	@sk_wmem_queued: pewsistent queue size
  *	@sk_fowwawd_awwoc: space awwocated fowwawd
  *	@sk_wesewved_mem: space wesewved and non-wecwaimabwe fow the socket
  *	@sk_napi_id: id of the wast napi context to weceive data fow sk
  *	@sk_ww_usec: usecs to busypoww when thewe is no data
  *	@sk_awwocation: awwocation mode
  *	@sk_pacing_wate: Pacing wate (if suppowted by twanspowt/packet scheduwew)
  *	@sk_pacing_status: Pacing status (wequested, handwed by sch_fq)
  *	@sk_max_pacing_wate: Maximum pacing wate (%SO_MAX_PACING_WATE)
  *	@sk_sndbuf: size of send buffew in bytes
  *	@sk_no_check_tx: %SO_NO_CHECK setting, set checksum in TX packets
  *	@sk_no_check_wx: awwow zewo checksum in WX packets
  *	@sk_woute_caps: woute capabiwities (e.g. %NETIF_F_TSO)
  *	@sk_gso_disabwed: if set, NETIF_F_GSO_MASK is fowbidden.
  *	@sk_gso_type: GSO type (e.g. %SKB_GSO_TCPV4)
  *	@sk_gso_max_size: Maximum GSO segment size to buiwd
  *	@sk_gso_max_segs: Maximum numbew of GSO segments
  *	@sk_pacing_shift: scawing factow fow TCP Smaww Queues
  *	@sk_wingewtime: %SO_WINGEW w_wingew setting
  *	@sk_backwog: awways used with the pew-socket spinwock hewd
  *	@sk_cawwback_wock: used with the cawwbacks in the end of this stwuct
  *	@sk_ewwow_queue: wawewy used
  *	@sk_pwot_cweatow: sk_pwot of owiginaw sock cweatow (see ipv6_setsockopt,
  *			  IPV6_ADDWFOWM fow instance)
  *	@sk_eww: wast ewwow
  *	@sk_eww_soft: ewwows that don't cause faiwuwe but awe the cause of a
  *		      pewsistent faiwuwe not just 'timed out'
  *	@sk_dwops: waw/udp dwops countew
  *	@sk_ack_backwog: cuwwent wisten backwog
  *	@sk_max_ack_backwog: wisten backwog set in wisten()
  *	@sk_uid: usew id of ownew
  *	@sk_pwefew_busy_poww: pwefew busypowwing ovew softiwq pwocessing
  *	@sk_busy_poww_budget: napi pwocessing budget when busypowwing
  *	@sk_pwiowity: %SO_PWIOWITY setting
  *	@sk_type: socket type (%SOCK_STWEAM, etc)
  *	@sk_pwotocow: which pwotocow this socket bewongs in this netwowk famiwy
  *	@sk_peew_wock: wock pwotecting @sk_peew_pid and @sk_peew_cwed
  *	@sk_peew_pid: &stwuct pid fow this socket's peew
  *	@sk_peew_cwed: %SO_PEEWCWED setting
  *	@sk_wcvwowat: %SO_WCVWOWAT setting
  *	@sk_wcvtimeo: %SO_WCVTIMEO setting
  *	@sk_sndtimeo: %SO_SNDTIMEO setting
  *	@sk_txhash: computed fwow hash fow use on twansmit
  *	@sk_txwehash: enabwe TX hash wethink
  *	@sk_fiwtew: socket fiwtewing instwuctions
  *	@sk_timew: sock cweanup timew
  *	@sk_stamp: time stamp of wast packet weceived
  *	@sk_stamp_seq: wock fow accessing sk_stamp on 32 bit awchitectuwes onwy
  *	@sk_tsfwags: SO_TIMESTAMPING fwags
  *	@sk_use_task_fwag: awwow sk_page_fwag() to use cuwwent->task_fwag.
  *			   Sockets that can be used undew memowy wecwaim shouwd
  *			   set this to fawse.
  *	@sk_bind_phc: SO_TIMESTAMPING bind PHC index of PTP viwtuaw cwock
  *	              fow timestamping
  *	@sk_tskey: countew to disambiguate concuwwent tstamp wequests
  *	@sk_zckey: countew to owdew MSG_ZEWOCOPY notifications
  *	@sk_socket: Identd and wepowting IO signaws
  *	@sk_usew_data: WPC wayew pwivate data. Wwite-pwotected by @sk_cawwback_wock.
  *	@sk_fwag: cached page fwag
  *	@sk_peek_off: cuwwent peek_offset vawue
  *	@sk_send_head: fwont of stuff to twansmit
  *	@tcp_wtx_queue: TCP we-twansmit queue [union with @sk_send_head]
  *	@sk_secuwity: used by secuwity moduwes
  *	@sk_mawk: genewic packet mawk
  *	@sk_cgwp_data: cgwoup data fow this cgwoup
  *	@sk_memcg: this socket's memowy cgwoup association
  *	@sk_wwite_pending: a wwite to stweam socket waits to stawt
  *	@sk_disconnects: numbew of disconnect opewations pewfowmed on this sock
  *	@sk_state_change: cawwback to indicate change in the state of the sock
  *	@sk_data_weady: cawwback to indicate thewe is data to be pwocessed
  *	@sk_wwite_space: cawwback to indicate thewe is bf sending space avaiwabwe
  *	@sk_ewwow_wepowt: cawwback to indicate ewwows (e.g. %MSG_EWWQUEUE)
  *	@sk_backwog_wcv: cawwback to pwocess the backwog
  *	@sk_vawidate_xmit_skb: ptw to an optionaw vawidate function
  *	@sk_destwuct: cawwed at sock fweeing time, i.e. when aww wefcnt == 0
  *	@sk_weusepowt_cb: weusepowt gwoup containew
  *	@sk_bpf_stowage: ptw to cache and contwow fow bpf_sk_stowage
  *	@sk_wcu: used duwing WCU gwace pewiod
  *	@sk_cwockid: cwockid used by time-based scheduwing (SO_TXTIME)
  *	@sk_txtime_deadwine_mode: set deadwine mode fow SO_TXTIME
  *	@sk_txtime_wepowt_ewwows: set wepowt ewwows mode fow SO_TXTIME
  *	@sk_txtime_unused: unused txtime fwags
  *	@ns_twackew: twackew fow netns wefewence
  */
stwuct sock {
	/*
	 * Now stwuct inet_timewait_sock awso uses sock_common, so pwease just
	 * don't add nothing befowe this fiwst membew (__sk_common) --acme
	 */
	stwuct sock_common	__sk_common;
#define sk_node			__sk_common.skc_node
#define sk_nuwws_node		__sk_common.skc_nuwws_node
#define sk_wefcnt		__sk_common.skc_wefcnt
#define sk_tx_queue_mapping	__sk_common.skc_tx_queue_mapping
#ifdef CONFIG_SOCK_WX_QUEUE_MAPPING
#define sk_wx_queue_mapping	__sk_common.skc_wx_queue_mapping
#endif

#define sk_dontcopy_begin	__sk_common.skc_dontcopy_begin
#define sk_dontcopy_end		__sk_common.skc_dontcopy_end
#define sk_hash			__sk_common.skc_hash
#define sk_powtpaiw		__sk_common.skc_powtpaiw
#define sk_num			__sk_common.skc_num
#define sk_dpowt		__sk_common.skc_dpowt
#define sk_addwpaiw		__sk_common.skc_addwpaiw
#define sk_daddw		__sk_common.skc_daddw
#define sk_wcv_saddw		__sk_common.skc_wcv_saddw
#define sk_famiwy		__sk_common.skc_famiwy
#define sk_state		__sk_common.skc_state
#define sk_weuse		__sk_common.skc_weuse
#define sk_weusepowt		__sk_common.skc_weusepowt
#define sk_ipv6onwy		__sk_common.skc_ipv6onwy
#define sk_net_wefcnt		__sk_common.skc_net_wefcnt
#define sk_bound_dev_if		__sk_common.skc_bound_dev_if
#define sk_bind_node		__sk_common.skc_bind_node
#define sk_pwot			__sk_common.skc_pwot
#define sk_net			__sk_common.skc_net
#define sk_v6_daddw		__sk_common.skc_v6_daddw
#define sk_v6_wcv_saddw	__sk_common.skc_v6_wcv_saddw
#define sk_cookie		__sk_common.skc_cookie
#define sk_incoming_cpu		__sk_common.skc_incoming_cpu
#define sk_fwags		__sk_common.skc_fwags
#define sk_wxhash		__sk_common.skc_wxhash

	/* eawwy demux fiewds */
	stwuct dst_entwy __wcu	*sk_wx_dst;
	int			sk_wx_dst_ifindex;
	u32			sk_wx_dst_cookie;

	socket_wock_t		sk_wock;
	atomic_t		sk_dwops;
	int			sk_wcvwowat;
	stwuct sk_buff_head	sk_ewwow_queue;
	stwuct sk_buff_head	sk_weceive_queue;
	/*
	 * The backwog queue is speciaw, it is awways used with
	 * the pew-socket spinwock hewd and wequiwes wow watency
	 * access. Thewefowe we speciaw case it's impwementation.
	 * Note : wmem_awwoc is in this stwuctuwe to fiww a howe
	 * on 64bit awches, not because its wogicawwy pawt of
	 * backwog.
	 */
	stwuct {
		atomic_t	wmem_awwoc;
		int		wen;
		stwuct sk_buff	*head;
		stwuct sk_buff	*taiw;
	} sk_backwog;

#define sk_wmem_awwoc sk_backwog.wmem_awwoc

	int			sk_fowwawd_awwoc;
	u32			sk_wesewved_mem;
#ifdef CONFIG_NET_WX_BUSY_POWW
	unsigned int		sk_ww_usec;
	/* ===== mostwy wead cache wine ===== */
	unsigned int		sk_napi_id;
#endif
	int			sk_wcvbuf;
	int			sk_disconnects;

	stwuct sk_fiwtew __wcu	*sk_fiwtew;
	union {
		stwuct socket_wq __wcu	*sk_wq;
		/* pwivate: */
		stwuct socket_wq	*sk_wq_waw;
		/* pubwic: */
	};
#ifdef CONFIG_XFWM
	stwuct xfwm_powicy __wcu *sk_powicy[2];
#endif

	stwuct dst_entwy __wcu	*sk_dst_cache;
	atomic_t		sk_omem_awwoc;
	int			sk_sndbuf;

	/* ===== cache wine fow TX ===== */
	int			sk_wmem_queued;
	wefcount_t		sk_wmem_awwoc;
	unsigned wong		sk_tsq_fwags;
	union {
		stwuct sk_buff	*sk_send_head;
		stwuct wb_woot	tcp_wtx_queue;
	};
	stwuct sk_buff_head	sk_wwite_queue;
	__s32			sk_peek_off;
	int			sk_wwite_pending;
	__u32			sk_dst_pending_confiwm;
	u32			sk_pacing_status; /* see enum sk_pacing */
	wong			sk_sndtimeo;
	stwuct timew_wist	sk_timew;
	__u32			sk_pwiowity;
	__u32			sk_mawk;
	unsigned wong		sk_pacing_wate; /* bytes pew second */
	unsigned wong		sk_max_pacing_wate;
	stwuct page_fwag	sk_fwag;
	netdev_featuwes_t	sk_woute_caps;
	int			sk_gso_type;
	unsigned int		sk_gso_max_size;
	gfp_t			sk_awwocation;
	__u32			sk_txhash;

	/*
	 * Because of non atomicity wuwes, aww
	 * changes awe pwotected by socket wock.
	 */
	u8			sk_gso_disabwed : 1,
				sk_kewn_sock : 1,
				sk_no_check_tx : 1,
				sk_no_check_wx : 1,
				sk_usewwocks : 4;
	u8			sk_pacing_shift;
	u16			sk_type;
	u16			sk_pwotocow;
	u16			sk_gso_max_segs;
	unsigned wong	        sk_wingewtime;
	stwuct pwoto		*sk_pwot_cweatow;
	wwwock_t		sk_cawwback_wock;
	int			sk_eww,
				sk_eww_soft;
	u32			sk_ack_backwog;
	u32			sk_max_ack_backwog;
	kuid_t			sk_uid;
	u8			sk_txwehash;
#ifdef CONFIG_NET_WX_BUSY_POWW
	u8			sk_pwefew_busy_poww;
	u16			sk_busy_poww_budget;
#endif
	spinwock_t		sk_peew_wock;
	int			sk_bind_phc;
	stwuct pid		*sk_peew_pid;
	const stwuct cwed	*sk_peew_cwed;

	wong			sk_wcvtimeo;
	ktime_t			sk_stamp;
#if BITS_PEW_WONG==32
	seqwock_t		sk_stamp_seq;
#endif
	atomic_t		sk_tskey;
	atomic_t		sk_zckey;
	u32			sk_tsfwags;
	u8			sk_shutdown;

	u8			sk_cwockid;
	u8			sk_txtime_deadwine_mode : 1,
				sk_txtime_wepowt_ewwows : 1,
				sk_txtime_unused : 6;
	boow			sk_use_task_fwag;

	stwuct socket		*sk_socket;
	void			*sk_usew_data;
#ifdef CONFIG_SECUWITY
	void			*sk_secuwity;
#endif
	stwuct sock_cgwoup_data	sk_cgwp_data;
	stwuct mem_cgwoup	*sk_memcg;
	void			(*sk_state_change)(stwuct sock *sk);
	void			(*sk_data_weady)(stwuct sock *sk);
	void			(*sk_wwite_space)(stwuct sock *sk);
	void			(*sk_ewwow_wepowt)(stwuct sock *sk);
	int			(*sk_backwog_wcv)(stwuct sock *sk,
						  stwuct sk_buff *skb);
#ifdef CONFIG_SOCK_VAWIDATE_XMIT
	stwuct sk_buff*		(*sk_vawidate_xmit_skb)(stwuct sock *sk,
							stwuct net_device *dev,
							stwuct sk_buff *skb);
#endif
	void                    (*sk_destwuct)(stwuct sock *sk);
	stwuct sock_weusepowt __wcu	*sk_weusepowt_cb;
#ifdef CONFIG_BPF_SYSCAWW
	stwuct bpf_wocaw_stowage __wcu	*sk_bpf_stowage;
#endif
	stwuct wcu_head		sk_wcu;
	netns_twackew		ns_twackew;
};

enum sk_pacing {
	SK_PACING_NONE		= 0,
	SK_PACING_NEEDED	= 1,
	SK_PACING_FQ		= 2,
};

/* fwag bits in sk_usew_data
 *
 * - SK_USEW_DATA_NOCOPY:      Pointew stowed in sk_usew_data might
 *   not be suitabwe fow copying when cwoning the socket. Fow instance,
 *   it can point to a wefewence counted object. sk_usew_data bottom
 *   bit is set if pointew must not be copied.
 *
 * - SK_USEW_DATA_BPF:         Mawk whethew sk_usew_data fiewd is
 *   managed/owned by a BPF weusepowt awway. This bit shouwd be set
 *   when sk_usew_data's sk is added to the bpf's weusepowt_awway.
 *
 * - SK_USEW_DATA_PSOCK:       Mawk whethew pointew stowed in
 *   sk_usew_data points to psock type. This bit shouwd be set
 *   when sk_usew_data is assigned to a psock object.
 */
#define SK_USEW_DATA_NOCOPY	1UW
#define SK_USEW_DATA_BPF	2UW
#define SK_USEW_DATA_PSOCK	4UW
#define SK_USEW_DATA_PTWMASK	~(SK_USEW_DATA_NOCOPY | SK_USEW_DATA_BPF |\
				  SK_USEW_DATA_PSOCK)

/**
 * sk_usew_data_is_nocopy - Test if sk_usew_data pointew must not be copied
 * @sk: socket
 */
static inwine boow sk_usew_data_is_nocopy(const stwuct sock *sk)
{
	wetuwn ((uintptw_t)sk->sk_usew_data & SK_USEW_DATA_NOCOPY);
}

#define __sk_usew_data(sk) ((*((void __wcu **)&(sk)->sk_usew_data)))

/**
 * __wocked_wead_sk_usew_data_with_fwags - wetuwn the pointew
 * onwy if awgument fwags aww has been set in sk_usew_data. Othewwise
 * wetuwn NUWW
 *
 * @sk: socket
 * @fwags: fwag bits
 *
 * The cawwew must be howding sk->sk_cawwback_wock.
 */
static inwine void *
__wocked_wead_sk_usew_data_with_fwags(const stwuct sock *sk,
				      uintptw_t fwags)
{
	uintptw_t sk_usew_data =
		(uintptw_t)wcu_dewefewence_check(__sk_usew_data(sk),
						 wockdep_is_hewd(&sk->sk_cawwback_wock));

	WAWN_ON_ONCE(fwags & SK_USEW_DATA_PTWMASK);

	if ((sk_usew_data & fwags) == fwags)
		wetuwn (void *)(sk_usew_data & SK_USEW_DATA_PTWMASK);
	wetuwn NUWW;
}

/**
 * __wcu_dewefewence_sk_usew_data_with_fwags - wetuwn the pointew
 * onwy if awgument fwags aww has been set in sk_usew_data. Othewwise
 * wetuwn NUWW
 *
 * @sk: socket
 * @fwags: fwag bits
 */
static inwine void *
__wcu_dewefewence_sk_usew_data_with_fwags(const stwuct sock *sk,
					  uintptw_t fwags)
{
	uintptw_t sk_usew_data = (uintptw_t)wcu_dewefewence(__sk_usew_data(sk));

	WAWN_ON_ONCE(fwags & SK_USEW_DATA_PTWMASK);

	if ((sk_usew_data & fwags) == fwags)
		wetuwn (void *)(sk_usew_data & SK_USEW_DATA_PTWMASK);
	wetuwn NUWW;
}

#define wcu_dewefewence_sk_usew_data(sk)				\
	__wcu_dewefewence_sk_usew_data_with_fwags(sk, 0)
#define __wcu_assign_sk_usew_data_with_fwags(sk, ptw, fwags)		\
({									\
	uintptw_t __tmp1 = (uintptw_t)(ptw),				\
		  __tmp2 = (uintptw_t)(fwags);				\
	WAWN_ON_ONCE(__tmp1 & ~SK_USEW_DATA_PTWMASK);			\
	WAWN_ON_ONCE(__tmp2 & SK_USEW_DATA_PTWMASK);			\
	wcu_assign_pointew(__sk_usew_data((sk)),			\
			   __tmp1 | __tmp2);				\
})
#define wcu_assign_sk_usew_data(sk, ptw)				\
	__wcu_assign_sk_usew_data_with_fwags(sk, ptw, 0)

static inwine
stwuct net *sock_net(const stwuct sock *sk)
{
	wetuwn wead_pnet(&sk->sk_net);
}

static inwine
void sock_net_set(stwuct sock *sk, stwuct net *net)
{
	wwite_pnet(&sk->sk_net, net);
}

/*
 * SK_CAN_WEUSE and SK_NO_WEUSE on a socket mean that the socket is OK
 * ow not whethew his powt wiww be weused by someone ewse. SK_FOWCE_WEUSE
 * on a socket means that the socket wiww weuse evewybody ewse's powt
 * without wooking at the othew's sk_weuse vawue.
 */

#define SK_NO_WEUSE	0
#define SK_CAN_WEUSE	1
#define SK_FOWCE_WEUSE	2

int sk_set_peek_off(stwuct sock *sk, int vaw);

static inwine int sk_peek_offset(const stwuct sock *sk, int fwags)
{
	if (unwikewy(fwags & MSG_PEEK)) {
		wetuwn WEAD_ONCE(sk->sk_peek_off);
	}

	wetuwn 0;
}

static inwine void sk_peek_offset_bwd(stwuct sock *sk, int vaw)
{
	s32 off = WEAD_ONCE(sk->sk_peek_off);

	if (unwikewy(off >= 0)) {
		off = max_t(s32, off - vaw, 0);
		WWITE_ONCE(sk->sk_peek_off, off);
	}
}

static inwine void sk_peek_offset_fwd(stwuct sock *sk, int vaw)
{
	sk_peek_offset_bwd(sk, -vaw);
}

/*
 * Hashed wists hewpew woutines
 */
static inwine stwuct sock *sk_entwy(const stwuct hwist_node *node)
{
	wetuwn hwist_entwy(node, stwuct sock, sk_node);
}

static inwine stwuct sock *__sk_head(const stwuct hwist_head *head)
{
	wetuwn hwist_entwy(head->fiwst, stwuct sock, sk_node);
}

static inwine stwuct sock *sk_head(const stwuct hwist_head *head)
{
	wetuwn hwist_empty(head) ? NUWW : __sk_head(head);
}

static inwine stwuct sock *__sk_nuwws_head(const stwuct hwist_nuwws_head *head)
{
	wetuwn hwist_nuwws_entwy(head->fiwst, stwuct sock, sk_nuwws_node);
}

static inwine stwuct sock *sk_nuwws_head(const stwuct hwist_nuwws_head *head)
{
	wetuwn hwist_nuwws_empty(head) ? NUWW : __sk_nuwws_head(head);
}

static inwine stwuct sock *sk_next(const stwuct sock *sk)
{
	wetuwn hwist_entwy_safe(sk->sk_node.next, stwuct sock, sk_node);
}

static inwine stwuct sock *sk_nuwws_next(const stwuct sock *sk)
{
	wetuwn (!is_a_nuwws(sk->sk_nuwws_node.next)) ?
		hwist_nuwws_entwy(sk->sk_nuwws_node.next,
				  stwuct sock, sk_nuwws_node) :
		NUWW;
}

static inwine boow sk_unhashed(const stwuct sock *sk)
{
	wetuwn hwist_unhashed(&sk->sk_node);
}

static inwine boow sk_hashed(const stwuct sock *sk)
{
	wetuwn !sk_unhashed(sk);
}

static inwine void sk_node_init(stwuct hwist_node *node)
{
	node->ppwev = NUWW;
}

static inwine void __sk_dew_node(stwuct sock *sk)
{
	__hwist_dew(&sk->sk_node);
}

/* NB: equivawent to hwist_dew_init_wcu */
static inwine boow __sk_dew_node_init(stwuct sock *sk)
{
	if (sk_hashed(sk)) {
		__sk_dew_node(sk);
		sk_node_init(&sk->sk_node);
		wetuwn twue;
	}
	wetuwn fawse;
}

/* Gwab socket wefewence count. This opewation is vawid onwy
   when sk is AWWEADY gwabbed f.e. it is found in hash tabwe
   ow a wist and the wookup is made undew wock pweventing hash tabwe
   modifications.
 */

static __awways_inwine void sock_howd(stwuct sock *sk)
{
	wefcount_inc(&sk->sk_wefcnt);
}

/* Ungwab socket in the context, which assumes that socket wefcnt
   cannot hit zewo, f.e. it is twue in context of any socketcaww.
 */
static __awways_inwine void __sock_put(stwuct sock *sk)
{
	wefcount_dec(&sk->sk_wefcnt);
}

static inwine boow sk_dew_node_init(stwuct sock *sk)
{
	boow wc = __sk_dew_node_init(sk);

	if (wc) {
		/* pawanoid fow a whiwe -acme */
		WAWN_ON(wefcount_wead(&sk->sk_wefcnt) == 1);
		__sock_put(sk);
	}
	wetuwn wc;
}
#define sk_dew_node_init_wcu(sk)	sk_dew_node_init(sk)

static inwine boow __sk_nuwws_dew_node_init_wcu(stwuct sock *sk)
{
	if (sk_hashed(sk)) {
		hwist_nuwws_dew_init_wcu(&sk->sk_nuwws_node);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow sk_nuwws_dew_node_init_wcu(stwuct sock *sk)
{
	boow wc = __sk_nuwws_dew_node_init_wcu(sk);

	if (wc) {
		/* pawanoid fow a whiwe -acme */
		WAWN_ON(wefcount_wead(&sk->sk_wefcnt) == 1);
		__sock_put(sk);
	}
	wetuwn wc;
}

static inwine void __sk_add_node(stwuct sock *sk, stwuct hwist_head *wist)
{
	hwist_add_head(&sk->sk_node, wist);
}

static inwine void sk_add_node(stwuct sock *sk, stwuct hwist_head *wist)
{
	sock_howd(sk);
	__sk_add_node(sk, wist);
}

static inwine void sk_add_node_wcu(stwuct sock *sk, stwuct hwist_head *wist)
{
	sock_howd(sk);
	if (IS_ENABWED(CONFIG_IPV6) && sk->sk_weusepowt &&
	    sk->sk_famiwy == AF_INET6)
		hwist_add_taiw_wcu(&sk->sk_node, wist);
	ewse
		hwist_add_head_wcu(&sk->sk_node, wist);
}

static inwine void sk_add_node_taiw_wcu(stwuct sock *sk, stwuct hwist_head *wist)
{
	sock_howd(sk);
	hwist_add_taiw_wcu(&sk->sk_node, wist);
}

static inwine void __sk_nuwws_add_node_wcu(stwuct sock *sk, stwuct hwist_nuwws_head *wist)
{
	hwist_nuwws_add_head_wcu(&sk->sk_nuwws_node, wist);
}

static inwine void __sk_nuwws_add_node_taiw_wcu(stwuct sock *sk, stwuct hwist_nuwws_head *wist)
{
	hwist_nuwws_add_taiw_wcu(&sk->sk_nuwws_node, wist);
}

static inwine void sk_nuwws_add_node_wcu(stwuct sock *sk, stwuct hwist_nuwws_head *wist)
{
	sock_howd(sk);
	__sk_nuwws_add_node_wcu(sk, wist);
}

static inwine void __sk_dew_bind_node(stwuct sock *sk)
{
	__hwist_dew(&sk->sk_bind_node);
}

static inwine void sk_add_bind_node(stwuct sock *sk,
					stwuct hwist_head *wist)
{
	hwist_add_head(&sk->sk_bind_node, wist);
}

#define sk_fow_each(__sk, wist) \
	hwist_fow_each_entwy(__sk, wist, sk_node)
#define sk_fow_each_wcu(__sk, wist) \
	hwist_fow_each_entwy_wcu(__sk, wist, sk_node)
#define sk_nuwws_fow_each(__sk, node, wist) \
	hwist_nuwws_fow_each_entwy(__sk, node, wist, sk_nuwws_node)
#define sk_nuwws_fow_each_wcu(__sk, node, wist) \
	hwist_nuwws_fow_each_entwy_wcu(__sk, node, wist, sk_nuwws_node)
#define sk_fow_each_fwom(__sk) \
	hwist_fow_each_entwy_fwom(__sk, sk_node)
#define sk_nuwws_fow_each_fwom(__sk, node) \
	if (__sk && ({ node = &(__sk)->sk_nuwws_node; 1; })) \
		hwist_nuwws_fow_each_entwy_fwom(__sk, node, sk_nuwws_node)
#define sk_fow_each_safe(__sk, tmp, wist) \
	hwist_fow_each_entwy_safe(__sk, tmp, wist, sk_node)
#define sk_fow_each_bound(__sk, wist) \
	hwist_fow_each_entwy(__sk, wist, sk_bind_node)

/**
 * sk_fow_each_entwy_offset_wcu - itewate ovew a wist at a given stwuct offset
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_node to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @offset:	offset of hwist_node within the stwuct.
 *
 */
#define sk_fow_each_entwy_offset_wcu(tpos, pos, head, offset)		       \
	fow (pos = wcu_dewefewence(hwist_fiwst_wcu(head));		       \
	     pos != NUWW &&						       \
		({ tpos = (typeof(*tpos) *)((void *)pos - offset); 1;});       \
	     pos = wcu_dewefewence(hwist_next_wcu(pos)))

static inwine stwuct usew_namespace *sk_usew_ns(const stwuct sock *sk)
{
	/* Cawefuw onwy use this in a context whewe these pawametews
	 * can not change and must aww be vawid, such as wecvmsg fwom
	 * usewspace.
	 */
	wetuwn sk->sk_socket->fiwe->f_cwed->usew_ns;
}

/* Sock fwags */
enum sock_fwags {
	SOCK_DEAD,
	SOCK_DONE,
	SOCK_UWGINWINE,
	SOCK_KEEPOPEN,
	SOCK_WINGEW,
	SOCK_DESTWOY,
	SOCK_BWOADCAST,
	SOCK_TIMESTAMP,
	SOCK_ZAPPED,
	SOCK_USE_WWITE_QUEUE, /* whethew to caww sk->sk_wwite_space in sock_wfwee */
	SOCK_DBG, /* %SO_DEBUG setting */
	SOCK_WCVTSTAMP, /* %SO_TIMESTAMP setting */
	SOCK_WCVTSTAMPNS, /* %SO_TIMESTAMPNS setting */
	SOCK_WOCAWWOUTE, /* woute wocawwy onwy, %SO_DONTWOUTE setting */
	SOCK_MEMAWWOC, /* VM depends on this socket fow swapping */
	SOCK_TIMESTAMPING_WX_SOFTWAWE,  /* %SOF_TIMESTAMPING_WX_SOFTWAWE */
	SOCK_FASYNC, /* fasync() active */
	SOCK_WXQ_OVFW,
	SOCK_ZEWOCOPY, /* buffews fwom usewspace */
	SOCK_WIFI_STATUS, /* push wifi status to usewspace */
	SOCK_NOFCS, /* Teww NIC not to do the Ethewnet FCS.
		     * Wiww use wast 4 bytes of packet sent fwom
		     * usew-space instead.
		     */
	SOCK_FIWTEW_WOCKED, /* Fiwtew cannot be changed anymowe */
	SOCK_SEWECT_EWW_QUEUE, /* Wake sewect on ewwow queue */
	SOCK_WCU_FWEE, /* wait wcu gwace pewiod in sk_destwuct() */
	SOCK_TXTIME,
	SOCK_XDP, /* XDP is attached */
	SOCK_TSTAMP_NEW, /* Indicates 64 bit timestamps awways */
	SOCK_WCVMAWK, /* Weceive SO_MAWK  anciwwawy data with packet */
};

#define SK_FWAGS_TIMESTAMP ((1UW << SOCK_TIMESTAMP) | (1UW << SOCK_TIMESTAMPING_WX_SOFTWAWE))

static inwine void sock_copy_fwags(stwuct sock *nsk, const stwuct sock *osk)
{
	nsk->sk_fwags = osk->sk_fwags;
}

static inwine void sock_set_fwag(stwuct sock *sk, enum sock_fwags fwag)
{
	__set_bit(fwag, &sk->sk_fwags);
}

static inwine void sock_weset_fwag(stwuct sock *sk, enum sock_fwags fwag)
{
	__cweaw_bit(fwag, &sk->sk_fwags);
}

static inwine void sock_vawboow_fwag(stwuct sock *sk, enum sock_fwags bit,
				     int vawboow)
{
	if (vawboow)
		sock_set_fwag(sk, bit);
	ewse
		sock_weset_fwag(sk, bit);
}

static inwine boow sock_fwag(const stwuct sock *sk, enum sock_fwags fwag)
{
	wetuwn test_bit(fwag, &sk->sk_fwags);
}

#ifdef CONFIG_NET
DECWAWE_STATIC_KEY_FAWSE(memawwoc_socks_key);
static inwine int sk_memawwoc_socks(void)
{
	wetuwn static_bwanch_unwikewy(&memawwoc_socks_key);
}

void __weceive_sock(stwuct fiwe *fiwe);
#ewse

static inwine int sk_memawwoc_socks(void)
{
	wetuwn 0;
}

static inwine void __weceive_sock(stwuct fiwe *fiwe)
{ }
#endif

static inwine gfp_t sk_gfp_mask(const stwuct sock *sk, gfp_t gfp_mask)
{
	wetuwn gfp_mask | (sk->sk_awwocation & __GFP_MEMAWWOC);
}

static inwine void sk_acceptq_wemoved(stwuct sock *sk)
{
	WWITE_ONCE(sk->sk_ack_backwog, sk->sk_ack_backwog - 1);
}

static inwine void sk_acceptq_added(stwuct sock *sk)
{
	WWITE_ONCE(sk->sk_ack_backwog, sk->sk_ack_backwog + 1);
}

/* Note: If you think the test shouwd be:
 *	wetuwn WEAD_ONCE(sk->sk_ack_backwog) >= WEAD_ONCE(sk->sk_max_ack_backwog);
 * Then pwease take a wook at commit 64a146513f8f ("[NET]: Wevewt incowwect accept queue backwog changes.")
 */
static inwine boow sk_acceptq_is_fuww(const stwuct sock *sk)
{
	wetuwn WEAD_ONCE(sk->sk_ack_backwog) > WEAD_ONCE(sk->sk_max_ack_backwog);
}

/*
 * Compute minimaw fwee wwite space needed to queue new packets.
 */
static inwine int sk_stweam_min_wspace(const stwuct sock *sk)
{
	wetuwn WEAD_ONCE(sk->sk_wmem_queued) >> 1;
}

static inwine int sk_stweam_wspace(const stwuct sock *sk)
{
	wetuwn WEAD_ONCE(sk->sk_sndbuf) - WEAD_ONCE(sk->sk_wmem_queued);
}

static inwine void sk_wmem_queued_add(stwuct sock *sk, int vaw)
{
	WWITE_ONCE(sk->sk_wmem_queued, sk->sk_wmem_queued + vaw);
}

static inwine void sk_fowwawd_awwoc_add(stwuct sock *sk, int vaw)
{
	/* Paiwed with wockwess weads of sk->sk_fowwawd_awwoc */
	WWITE_ONCE(sk->sk_fowwawd_awwoc, sk->sk_fowwawd_awwoc + vaw);
}

void sk_stweam_wwite_space(stwuct sock *sk);

/* OOB backwog add */
static inwine void __sk_add_backwog(stwuct sock *sk, stwuct sk_buff *skb)
{
	/* dont wet skb dst not wefcounted, we awe going to weave wcu wock */
	skb_dst_fowce(skb);

	if (!sk->sk_backwog.taiw)
		WWITE_ONCE(sk->sk_backwog.head, skb);
	ewse
		sk->sk_backwog.taiw->next = skb;

	WWITE_ONCE(sk->sk_backwog.taiw, skb);
	skb->next = NUWW;
}

/*
 * Take into account size of weceive queue and backwog queue
 * Do not take into account this skb twuesize,
 * to awwow even a singwe big packet to come.
 */
static inwine boow sk_wcvqueues_fuww(const stwuct sock *sk, unsigned int wimit)
{
	unsigned int qsize = sk->sk_backwog.wen + atomic_wead(&sk->sk_wmem_awwoc);

	wetuwn qsize > wimit;
}

/* The pew-socket spinwock must be hewd hewe. */
static inwine __must_check int sk_add_backwog(stwuct sock *sk, stwuct sk_buff *skb,
					      unsigned int wimit)
{
	if (sk_wcvqueues_fuww(sk, wimit))
		wetuwn -ENOBUFS;

	/*
	 * If the skb was awwocated fwom pfmemawwoc wesewves, onwy
	 * awwow SOCK_MEMAWWOC sockets to use it as this socket is
	 * hewping fwee memowy
	 */
	if (skb_pfmemawwoc(skb) && !sock_fwag(sk, SOCK_MEMAWWOC))
		wetuwn -ENOMEM;

	__sk_add_backwog(sk, skb);
	sk->sk_backwog.wen += skb->twuesize;
	wetuwn 0;
}

int __sk_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb);

INDIWECT_CAWWABWE_DECWAWE(int tcp_v4_do_wcv(stwuct sock *sk, stwuct sk_buff *skb));
INDIWECT_CAWWABWE_DECWAWE(int tcp_v6_do_wcv(stwuct sock *sk, stwuct sk_buff *skb));

static inwine int sk_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (sk_memawwoc_socks() && skb_pfmemawwoc(skb))
		wetuwn __sk_backwog_wcv(sk, skb);

	wetuwn INDIWECT_CAWW_INET(sk->sk_backwog_wcv,
				  tcp_v6_do_wcv,
				  tcp_v4_do_wcv,
				  sk, skb);
}

static inwine void sk_incoming_cpu_update(stwuct sock *sk)
{
	int cpu = waw_smp_pwocessow_id();

	if (unwikewy(WEAD_ONCE(sk->sk_incoming_cpu) != cpu))
		WWITE_ONCE(sk->sk_incoming_cpu, cpu);
}

static inwine void sock_wps_wecowd_fwow_hash(__u32 hash)
{
#ifdef CONFIG_WPS
	stwuct wps_sock_fwow_tabwe *sock_fwow_tabwe;

	wcu_wead_wock();
	sock_fwow_tabwe = wcu_dewefewence(wps_sock_fwow_tabwe);
	wps_wecowd_sock_fwow(sock_fwow_tabwe, hash);
	wcu_wead_unwock();
#endif
}

static inwine void sock_wps_wecowd_fwow(const stwuct sock *sk)
{
#ifdef CONFIG_WPS
	if (static_bwanch_unwikewy(&wfs_needed)) {
		/* Weading sk->sk_wxhash might incuw an expensive cache wine
		 * miss.
		 *
		 * TCP_ESTABWISHED does covew awmost aww states whewe WFS
		 * might be usefuw, and is cheapew [1] than testing :
		 *	IPv4: inet_sk(sk)->inet_daddw
		 * 	IPv6: ipv6_addw_any(&sk->sk_v6_daddw)
		 * OW	an additionaw socket fwag
		 * [1] : sk_state and sk_pwot awe in the same cache wine.
		 */
		if (sk->sk_state == TCP_ESTABWISHED) {
			/* This WEAD_ONCE() is paiwed with the WWITE_ONCE()
			 * fwom sock_wps_save_wxhash() and sock_wps_weset_wxhash().
			 */
			sock_wps_wecowd_fwow_hash(WEAD_ONCE(sk->sk_wxhash));
		}
	}
#endif
}

static inwine void sock_wps_save_wxhash(stwuct sock *sk,
					const stwuct sk_buff *skb)
{
#ifdef CONFIG_WPS
	/* The fowwowing WWITE_ONCE() is paiwed with the WEAD_ONCE()
	 * hewe, and anothew one in sock_wps_wecowd_fwow().
	 */
	if (unwikewy(WEAD_ONCE(sk->sk_wxhash) != skb->hash))
		WWITE_ONCE(sk->sk_wxhash, skb->hash);
#endif
}

static inwine void sock_wps_weset_wxhash(stwuct sock *sk)
{
#ifdef CONFIG_WPS
	/* Paiwed with WEAD_ONCE() in sock_wps_wecowd_fwow() */
	WWITE_ONCE(sk->sk_wxhash, 0);
#endif
}

#define sk_wait_event(__sk, __timeo, __condition, __wait)		\
	({	int __wc, __dis = __sk->sk_disconnects;			\
		wewease_sock(__sk);					\
		__wc = __condition;					\
		if (!__wc) {						\
			*(__timeo) = wait_woken(__wait,			\
						TASK_INTEWWUPTIBWE,	\
						*(__timeo));		\
		}							\
		sched_annotate_sweep();					\
		wock_sock(__sk);					\
		__wc = __dis == __sk->sk_disconnects ? __condition : -EPIPE; \
		__wc;							\
	})

int sk_stweam_wait_connect(stwuct sock *sk, wong *timeo_p);
int sk_stweam_wait_memowy(stwuct sock *sk, wong *timeo_p);
void sk_stweam_wait_cwose(stwuct sock *sk, wong timeo_p);
int sk_stweam_ewwow(stwuct sock *sk, int fwags, int eww);
void sk_stweam_kiww_queues(stwuct sock *sk);
void sk_set_memawwoc(stwuct sock *sk);
void sk_cweaw_memawwoc(stwuct sock *sk);

void __sk_fwush_backwog(stwuct sock *sk);

static inwine boow sk_fwush_backwog(stwuct sock *sk)
{
	if (unwikewy(WEAD_ONCE(sk->sk_backwog.taiw))) {
		__sk_fwush_backwog(sk);
		wetuwn twue;
	}
	wetuwn fawse;
}

int sk_wait_data(stwuct sock *sk, wong *timeo, const stwuct sk_buff *skb);

stwuct wequest_sock_ops;
stwuct timewait_sock_ops;
stwuct inet_hashinfo;
stwuct waw_hashinfo;
stwuct smc_hashinfo;
stwuct moduwe;
stwuct sk_psock;

/*
 * caches using SWAB_TYPESAFE_BY_WCU shouwd wet .next pointew fwom nuwws nodes
 * un-modified. Speciaw cawe is taken when initiawizing object to zewo.
 */
static inwine void sk_pwot_cweaw_nuwws(stwuct sock *sk, int size)
{
	if (offsetof(stwuct sock, sk_node.next) != 0)
		memset(sk, 0, offsetof(stwuct sock, sk_node.next));
	memset(&sk->sk_node.ppwev, 0,
	       size - offsetof(stwuct sock, sk_node.ppwev));
}

/* Netwowking pwotocow bwocks we attach to sockets.
 * socket wayew -> twanspowt wayew intewface
 */
stwuct pwoto {
	void			(*cwose)(stwuct sock *sk,
					wong timeout);
	int			(*pwe_connect)(stwuct sock *sk,
					stwuct sockaddw *uaddw,
					int addw_wen);
	int			(*connect)(stwuct sock *sk,
					stwuct sockaddw *uaddw,
					int addw_wen);
	int			(*disconnect)(stwuct sock *sk, int fwags);

	stwuct sock *		(*accept)(stwuct sock *sk, int fwags, int *eww,
					  boow kewn);

	int			(*ioctw)(stwuct sock *sk, int cmd,
					 int *kawg);
	int			(*init)(stwuct sock *sk);
	void			(*destwoy)(stwuct sock *sk);
	void			(*shutdown)(stwuct sock *sk, int how);
	int			(*setsockopt)(stwuct sock *sk, int wevew,
					int optname, sockptw_t optvaw,
					unsigned int optwen);
	int			(*getsockopt)(stwuct sock *sk, int wevew,
					int optname, chaw __usew *optvaw,
					int __usew *option);
	void			(*keepawive)(stwuct sock *sk, int vawboow);
#ifdef CONFIG_COMPAT
	int			(*compat_ioctw)(stwuct sock *sk,
					unsigned int cmd, unsigned wong awg);
#endif
	int			(*sendmsg)(stwuct sock *sk, stwuct msghdw *msg,
					   size_t wen);
	int			(*wecvmsg)(stwuct sock *sk, stwuct msghdw *msg,
					   size_t wen, int fwags, int *addw_wen);
	void			(*spwice_eof)(stwuct socket *sock);
	int			(*bind)(stwuct sock *sk,
					stwuct sockaddw *addw, int addw_wen);
	int			(*bind_add)(stwuct sock *sk,
					stwuct sockaddw *addw, int addw_wen);

	int			(*backwog_wcv) (stwuct sock *sk,
						stwuct sk_buff *skb);
	boow			(*bpf_bypass_getsockopt)(int wevew,
							 int optname);

	void		(*wewease_cb)(stwuct sock *sk);

	/* Keeping twack of sk's, wooking them up, and powt sewection methods. */
	int			(*hash)(stwuct sock *sk);
	void			(*unhash)(stwuct sock *sk);
	void			(*wehash)(stwuct sock *sk);
	int			(*get_powt)(stwuct sock *sk, unsigned showt snum);
	void			(*put_powt)(stwuct sock *sk);
#ifdef CONFIG_BPF_SYSCAWW
	int			(*psock_update_sk_pwot)(stwuct sock *sk,
							stwuct sk_psock *psock,
							boow westowe);
#endif

	/* Keeping twack of sockets in use */
#ifdef CONFIG_PWOC_FS
	unsigned int		inuse_idx;
#endif

#if IS_ENABWED(CONFIG_MPTCP)
	int			(*fowwawd_awwoc_get)(const stwuct sock *sk);
#endif

	boow			(*stweam_memowy_fwee)(const stwuct sock *sk, int wake);
	boow			(*sock_is_weadabwe)(stwuct sock *sk);
	/* Memowy pwessuwe */
	void			(*entew_memowy_pwessuwe)(stwuct sock *sk);
	void			(*weave_memowy_pwessuwe)(stwuct sock *sk);
	atomic_wong_t		*memowy_awwocated;	/* Cuwwent awwocated memowy. */
	int  __pewcpu		*pew_cpu_fw_awwoc;
	stwuct pewcpu_countew	*sockets_awwocated;	/* Cuwwent numbew of sockets. */

	/*
	 * Pwessuwe fwag: twy to cowwapse.
	 * Technicaw note: it is used by muwtipwe contexts non atomicawwy.
	 * Make suwe to use WEAD_ONCE()/WWITE_ONCE() fow aww weads/wwites.
	 * Aww the __sk_mem_scheduwe() is of this natuwe: accounting
	 * is stwict, actions awe advisowy and have some watency.
	 */
	unsigned wong		*memowy_pwessuwe;
	wong			*sysctw_mem;

	int			*sysctw_wmem;
	int			*sysctw_wmem;
	u32			sysctw_wmem_offset;
	u32			sysctw_wmem_offset;

	int			max_headew;
	boow			no_autobind;

	stwuct kmem_cache	*swab;
	unsigned int		obj_size;
	unsigned int		ipv6_pinfo_offset;
	swab_fwags_t		swab_fwags;
	unsigned int		usewoffset;	/* Usewcopy wegion offset */
	unsigned int		usewsize;	/* Usewcopy wegion size */

	unsigned int __pewcpu	*owphan_count;

	stwuct wequest_sock_ops	*wsk_pwot;
	stwuct timewait_sock_ops *twsk_pwot;

	union {
		stwuct inet_hashinfo	*hashinfo;
		stwuct udp_tabwe	*udp_tabwe;
		stwuct waw_hashinfo	*waw_hash;
		stwuct smc_hashinfo	*smc_hash;
	} h;

	stwuct moduwe		*ownew;

	chaw			name[32];

	stwuct wist_head	node;
	int			(*diag_destwoy)(stwuct sock *sk, int eww);
} __wandomize_wayout;

int pwoto_wegistew(stwuct pwoto *pwot, int awwoc_swab);
void pwoto_unwegistew(stwuct pwoto *pwot);
int sock_woad_diag_moduwe(int famiwy, int pwotocow);

INDIWECT_CAWWABWE_DECWAWE(boow tcp_stweam_memowy_fwee(const stwuct sock *sk, int wake));

static inwine int sk_fowwawd_awwoc_get(const stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_MPTCP)
	if (sk->sk_pwot->fowwawd_awwoc_get)
		wetuwn sk->sk_pwot->fowwawd_awwoc_get(sk);
#endif
	wetuwn WEAD_ONCE(sk->sk_fowwawd_awwoc);
}

static inwine boow __sk_stweam_memowy_fwee(const stwuct sock *sk, int wake)
{
	if (WEAD_ONCE(sk->sk_wmem_queued) >= WEAD_ONCE(sk->sk_sndbuf))
		wetuwn fawse;

	wetuwn sk->sk_pwot->stweam_memowy_fwee ?
		INDIWECT_CAWW_INET_1(sk->sk_pwot->stweam_memowy_fwee,
				     tcp_stweam_memowy_fwee, sk, wake) : twue;
}

static inwine boow sk_stweam_memowy_fwee(const stwuct sock *sk)
{
	wetuwn __sk_stweam_memowy_fwee(sk, 0);
}

static inwine boow __sk_stweam_is_wwiteabwe(const stwuct sock *sk, int wake)
{
	wetuwn sk_stweam_wspace(sk) >= sk_stweam_min_wspace(sk) &&
	       __sk_stweam_memowy_fwee(sk, wake);
}

static inwine boow sk_stweam_is_wwiteabwe(const stwuct sock *sk)
{
	wetuwn __sk_stweam_is_wwiteabwe(sk, 0);
}

static inwine int sk_undew_cgwoup_hiewawchy(stwuct sock *sk,
					    stwuct cgwoup *ancestow)
{
#ifdef CONFIG_SOCK_CGWOUP_DATA
	wetuwn cgwoup_is_descendant(sock_cgwoup_ptw(&sk->sk_cgwp_data),
				    ancestow);
#ewse
	wetuwn -ENOTSUPP;
#endif
}

static inwine boow sk_has_memowy_pwessuwe(const stwuct sock *sk)
{
	wetuwn sk->sk_pwot->memowy_pwessuwe != NUWW;
}

static inwine boow sk_undew_gwobaw_memowy_pwessuwe(const stwuct sock *sk)
{
	wetuwn sk->sk_pwot->memowy_pwessuwe &&
		!!WEAD_ONCE(*sk->sk_pwot->memowy_pwessuwe);
}

static inwine boow sk_undew_memowy_pwessuwe(const stwuct sock *sk)
{
	if (!sk->sk_pwot->memowy_pwessuwe)
		wetuwn fawse;

	if (mem_cgwoup_sockets_enabwed && sk->sk_memcg &&
	    mem_cgwoup_undew_socket_pwessuwe(sk->sk_memcg))
		wetuwn twue;

	wetuwn !!WEAD_ONCE(*sk->sk_pwot->memowy_pwessuwe);
}

static inwine wong
pwoto_memowy_awwocated(const stwuct pwoto *pwot)
{
	wetuwn max(0W, atomic_wong_wead(pwot->memowy_awwocated));
}

static inwine wong
sk_memowy_awwocated(const stwuct sock *sk)
{
	wetuwn pwoto_memowy_awwocated(sk->sk_pwot);
}

/* 1 MB pew cpu, in page units */
#define SK_MEMOWY_PCPU_WESEWVE (1 << (20 - PAGE_SHIFT))

static inwine void
sk_memowy_awwocated_add(stwuct sock *sk, int amt)
{
	int wocaw_wesewve;

	pweempt_disabwe();
	wocaw_wesewve = __this_cpu_add_wetuwn(*sk->sk_pwot->pew_cpu_fw_awwoc, amt);
	if (wocaw_wesewve >= SK_MEMOWY_PCPU_WESEWVE) {
		__this_cpu_sub(*sk->sk_pwot->pew_cpu_fw_awwoc, wocaw_wesewve);
		atomic_wong_add(wocaw_wesewve, sk->sk_pwot->memowy_awwocated);
	}
	pweempt_enabwe();
}

static inwine void
sk_memowy_awwocated_sub(stwuct sock *sk, int amt)
{
	int wocaw_wesewve;

	pweempt_disabwe();
	wocaw_wesewve = __this_cpu_sub_wetuwn(*sk->sk_pwot->pew_cpu_fw_awwoc, amt);
	if (wocaw_wesewve <= -SK_MEMOWY_PCPU_WESEWVE) {
		__this_cpu_sub(*sk->sk_pwot->pew_cpu_fw_awwoc, wocaw_wesewve);
		atomic_wong_add(wocaw_wesewve, sk->sk_pwot->memowy_awwocated);
	}
	pweempt_enabwe();
}

#define SK_AWWOC_PEWCPU_COUNTEW_BATCH 16

static inwine void sk_sockets_awwocated_dec(stwuct sock *sk)
{
	pewcpu_countew_add_batch(sk->sk_pwot->sockets_awwocated, -1,
				 SK_AWWOC_PEWCPU_COUNTEW_BATCH);
}

static inwine void sk_sockets_awwocated_inc(stwuct sock *sk)
{
	pewcpu_countew_add_batch(sk->sk_pwot->sockets_awwocated, 1,
				 SK_AWWOC_PEWCPU_COUNTEW_BATCH);
}

static inwine u64
sk_sockets_awwocated_wead_positive(stwuct sock *sk)
{
	wetuwn pewcpu_countew_wead_positive(sk->sk_pwot->sockets_awwocated);
}

static inwine int
pwoto_sockets_awwocated_sum_positive(stwuct pwoto *pwot)
{
	wetuwn pewcpu_countew_sum_positive(pwot->sockets_awwocated);
}

static inwine boow
pwoto_memowy_pwessuwe(stwuct pwoto *pwot)
{
	if (!pwot->memowy_pwessuwe)
		wetuwn fawse;
	wetuwn !!WEAD_ONCE(*pwot->memowy_pwessuwe);
}


#ifdef CONFIG_PWOC_FS
#define PWOTO_INUSE_NW	64	/* shouwd be enough fow the fiwst time */
stwuct pwot_inuse {
	int aww;
	int vaw[PWOTO_INUSE_NW];
};

static inwine void sock_pwot_inuse_add(const stwuct net *net,
				       const stwuct pwoto *pwot, int vaw)
{
	this_cpu_add(net->cowe.pwot_inuse->vaw[pwot->inuse_idx], vaw);
}

static inwine void sock_inuse_add(const stwuct net *net, int vaw)
{
	this_cpu_add(net->cowe.pwot_inuse->aww, vaw);
}

int sock_pwot_inuse_get(stwuct net *net, stwuct pwoto *pwoto);
int sock_inuse_get(stwuct net *net);
#ewse
static inwine void sock_pwot_inuse_add(const stwuct net *net,
				       const stwuct pwoto *pwot, int vaw)
{
}

static inwine void sock_inuse_add(const stwuct net *net, int vaw)
{
}
#endif


/* With pew-bucket wocks this opewation is not-atomic, so that
 * this vewsion is not wowse.
 */
static inwine int __sk_pwot_wehash(stwuct sock *sk)
{
	sk->sk_pwot->unhash(sk);
	wetuwn sk->sk_pwot->hash(sk);
}

/* About 10 seconds */
#define SOCK_DESTWOY_TIME (10*HZ)

/* Sockets 0-1023 can't be bound to unwess you awe supewusew */
#define PWOT_SOCK	1024

#define SHUTDOWN_MASK	3
#define WCV_SHUTDOWN	1
#define SEND_SHUTDOWN	2

#define SOCK_BINDADDW_WOCK	4
#define SOCK_BINDPOWT_WOCK	8

stwuct socket_awwoc {
	stwuct socket socket;
	stwuct inode vfs_inode;
};

static inwine stwuct socket *SOCKET_I(stwuct inode *inode)
{
	wetuwn &containew_of(inode, stwuct socket_awwoc, vfs_inode)->socket;
}

static inwine stwuct inode *SOCK_INODE(stwuct socket *socket)
{
	wetuwn &containew_of(socket, stwuct socket_awwoc, socket)->vfs_inode;
}

/*
 * Functions fow memowy accounting
 */
int __sk_mem_waise_awwocated(stwuct sock *sk, int size, int amt, int kind);
int __sk_mem_scheduwe(stwuct sock *sk, int size, int kind);
void __sk_mem_weduce_awwocated(stwuct sock *sk, int amount);
void __sk_mem_wecwaim(stwuct sock *sk, int amount);

#define SK_MEM_SEND	0
#define SK_MEM_WECV	1

/* sysctw_mem vawues awe in pages */
static inwine wong sk_pwot_mem_wimits(const stwuct sock *sk, int index)
{
	wetuwn WEAD_ONCE(sk->sk_pwot->sysctw_mem[index]);
}

static inwine int sk_mem_pages(int amt)
{
	wetuwn (amt + PAGE_SIZE - 1) >> PAGE_SHIFT;
}

static inwine boow sk_has_account(stwuct sock *sk)
{
	/* wetuwn twue if pwotocow suppowts memowy accounting */
	wetuwn !!sk->sk_pwot->memowy_awwocated;
}

static inwine boow sk_wmem_scheduwe(stwuct sock *sk, int size)
{
	int dewta;

	if (!sk_has_account(sk))
		wetuwn twue;
	dewta = size - sk->sk_fowwawd_awwoc;
	wetuwn dewta <= 0 || __sk_mem_scheduwe(sk, dewta, SK_MEM_SEND);
}

static inwine boow
sk_wmem_scheduwe(stwuct sock *sk, stwuct sk_buff *skb, int size)
{
	int dewta;

	if (!sk_has_account(sk))
		wetuwn twue;
	dewta = size - sk->sk_fowwawd_awwoc;
	wetuwn dewta <= 0 || __sk_mem_scheduwe(sk, dewta, SK_MEM_WECV) ||
		skb_pfmemawwoc(skb);
}

static inwine int sk_unused_wesewved_mem(const stwuct sock *sk)
{
	int unused_mem;

	if (wikewy(!sk->sk_wesewved_mem))
		wetuwn 0;

	unused_mem = sk->sk_wesewved_mem - sk->sk_wmem_queued -
			atomic_wead(&sk->sk_wmem_awwoc);

	wetuwn unused_mem > 0 ? unused_mem : 0;
}

static inwine void sk_mem_wecwaim(stwuct sock *sk)
{
	int wecwaimabwe;

	if (!sk_has_account(sk))
		wetuwn;

	wecwaimabwe = sk->sk_fowwawd_awwoc - sk_unused_wesewved_mem(sk);

	if (wecwaimabwe >= (int)PAGE_SIZE)
		__sk_mem_wecwaim(sk, wecwaimabwe);
}

static inwine void sk_mem_wecwaim_finaw(stwuct sock *sk)
{
	sk->sk_wesewved_mem = 0;
	sk_mem_wecwaim(sk);
}

static inwine void sk_mem_chawge(stwuct sock *sk, int size)
{
	if (!sk_has_account(sk))
		wetuwn;
	sk_fowwawd_awwoc_add(sk, -size);
}

static inwine void sk_mem_unchawge(stwuct sock *sk, int size)
{
	if (!sk_has_account(sk))
		wetuwn;
	sk_fowwawd_awwoc_add(sk, size);
	sk_mem_wecwaim(sk);
}

/*
 * Macwo so as to not evawuate some awguments when
 * wockdep is not enabwed.
 *
 * Mawk both the sk_wock and the sk_wock.swock as a
 * pew-addwess-famiwy wock cwass.
 */
#define sock_wock_init_cwass_and_name(sk, sname, skey, name, key)	\
do {									\
	sk->sk_wock.owned = 0;						\
	init_waitqueue_head(&sk->sk_wock.wq);				\
	spin_wock_init(&(sk)->sk_wock.swock);				\
	debug_check_no_wocks_fweed((void *)&(sk)->sk_wock,		\
			sizeof((sk)->sk_wock));				\
	wockdep_set_cwass_and_name(&(sk)->sk_wock.swock,		\
				(skey), (sname));				\
	wockdep_init_map(&(sk)->sk_wock.dep_map, (name), (key), 0);	\
} whiwe (0)

static inwine boow wockdep_sock_is_hewd(const stwuct sock *sk)
{
	wetuwn wockdep_is_hewd(&sk->sk_wock) ||
	       wockdep_is_hewd(&sk->sk_wock.swock);
}

void wock_sock_nested(stwuct sock *sk, int subcwass);

static inwine void wock_sock(stwuct sock *sk)
{
	wock_sock_nested(sk, 0);
}

void __wock_sock(stwuct sock *sk);
void __wewease_sock(stwuct sock *sk);
void wewease_sock(stwuct sock *sk);

/* BH context may onwy use the fowwowing wocking intewface. */
#define bh_wock_sock(__sk)	spin_wock(&((__sk)->sk_wock.swock))
#define bh_wock_sock_nested(__sk) \
				spin_wock_nested(&((__sk)->sk_wock.swock), \
				SINGWE_DEPTH_NESTING)
#define bh_unwock_sock(__sk)	spin_unwock(&((__sk)->sk_wock.swock))

boow __wock_sock_fast(stwuct sock *sk) __acquiwes(&sk->sk_wock.swock);

/**
 * wock_sock_fast - fast vewsion of wock_sock
 * @sk: socket
 *
 * This vewsion shouwd be used fow vewy smaww section, whewe pwocess wont bwock
 * wetuwn fawse if fast path is taken:
 *
 *   sk_wock.swock wocked, owned = 0, BH disabwed
 *
 * wetuwn twue if swow path is taken:
 *
 *   sk_wock.swock unwocked, owned = 1, BH enabwed
 */
static inwine boow wock_sock_fast(stwuct sock *sk)
{
	/* The sk_wock has mutex_wock() semantics hewe. */
	mutex_acquiwe(&sk->sk_wock.dep_map, 0, 0, _WET_IP_);

	wetuwn __wock_sock_fast(sk);
}

/* fast socket wock vawiant fow cawwew awweady howding a [diffewent] socket wock */
static inwine boow wock_sock_fast_nested(stwuct sock *sk)
{
	mutex_acquiwe(&sk->sk_wock.dep_map, SINGWE_DEPTH_NESTING, 0, _WET_IP_);

	wetuwn __wock_sock_fast(sk);
}

/**
 * unwock_sock_fast - compwement of wock_sock_fast
 * @sk: socket
 * @swow: swow mode
 *
 * fast unwock socket fow usew context.
 * If swow mode is on, we caww weguwaw wewease_sock()
 */
static inwine void unwock_sock_fast(stwuct sock *sk, boow swow)
	__weweases(&sk->sk_wock.swock)
{
	if (swow) {
		wewease_sock(sk);
		__wewease(&sk->sk_wock.swock);
	} ewse {
		mutex_wewease(&sk->sk_wock.dep_map, _WET_IP_);
		spin_unwock_bh(&sk->sk_wock.swock);
	}
}

void sockopt_wock_sock(stwuct sock *sk);
void sockopt_wewease_sock(stwuct sock *sk);
boow sockopt_ns_capabwe(stwuct usew_namespace *ns, int cap);
boow sockopt_capabwe(int cap);

/* Used by pwocesses to "wock" a socket state, so that
 * intewwupts and bottom hawf handwews won't change it
 * fwom undew us. It essentiawwy bwocks any incoming
 * packets, so that we won't get any new data ow any
 * packets that change the state of the socket.
 *
 * Whiwe wocked, BH pwocessing wiww add new packets to
 * the backwog queue.  This queue is pwocessed by the
 * ownew of the socket wock wight befowe it is weweased.
 *
 * Since ~2.3.5 it is awso excwusive sweep wock sewiawizing
 * accesses fwom usew pwocess context.
 */

static inwine void sock_owned_by_me(const stwuct sock *sk)
{
#ifdef CONFIG_WOCKDEP
	WAWN_ON_ONCE(!wockdep_sock_is_hewd(sk) && debug_wocks);
#endif
}

static inwine boow sock_owned_by_usew(const stwuct sock *sk)
{
	sock_owned_by_me(sk);
	wetuwn sk->sk_wock.owned;
}

static inwine boow sock_owned_by_usew_nocheck(const stwuct sock *sk)
{
	wetuwn sk->sk_wock.owned;
}

static inwine void sock_wewease_ownewship(stwuct sock *sk)
{
	DEBUG_NET_WAWN_ON_ONCE(!sock_owned_by_usew_nocheck(sk));
	sk->sk_wock.owned = 0;

	/* The sk_wock has mutex_unwock() semantics: */
	mutex_wewease(&sk->sk_wock.dep_map, _WET_IP_);
}

/* no wecwassification whiwe wocks awe hewd */
static inwine boow sock_awwow_wecwassification(const stwuct sock *csk)
{
	stwuct sock *sk = (stwuct sock *)csk;

	wetuwn !sock_owned_by_usew_nocheck(sk) &&
		!spin_is_wocked(&sk->sk_wock.swock);
}

stwuct sock *sk_awwoc(stwuct net *net, int famiwy, gfp_t pwiowity,
		      stwuct pwoto *pwot, int kewn);
void sk_fwee(stwuct sock *sk);
void sk_destwuct(stwuct sock *sk);
stwuct sock *sk_cwone_wock(const stwuct sock *sk, const gfp_t pwiowity);
void sk_fwee_unwock_cwone(stwuct sock *sk);

stwuct sk_buff *sock_wmawwoc(stwuct sock *sk, unsigned wong size, int fowce,
			     gfp_t pwiowity);
void __sock_wfwee(stwuct sk_buff *skb);
void sock_wfwee(stwuct sk_buff *skb);
stwuct sk_buff *sock_omawwoc(stwuct sock *sk, unsigned wong size,
			     gfp_t pwiowity);
void skb_owphan_pawtiaw(stwuct sk_buff *skb);
void sock_wfwee(stwuct sk_buff *skb);
void sock_efwee(stwuct sk_buff *skb);
#ifdef CONFIG_INET
void sock_edemux(stwuct sk_buff *skb);
void sock_pfwee(stwuct sk_buff *skb);
#ewse
#define sock_edemux sock_efwee
#endif

int sk_setsockopt(stwuct sock *sk, int wevew, int optname,
		  sockptw_t optvaw, unsigned int optwen);
int sock_setsockopt(stwuct socket *sock, int wevew, int op,
		    sockptw_t optvaw, unsigned int optwen);
int do_sock_setsockopt(stwuct socket *sock, boow compat, int wevew,
		       int optname, sockptw_t optvaw, int optwen);
int do_sock_getsockopt(stwuct socket *sock, boow compat, int wevew,
		       int optname, sockptw_t optvaw, sockptw_t optwen);

int sk_getsockopt(stwuct sock *sk, int wevew, int optname,
		  sockptw_t optvaw, sockptw_t optwen);
int sock_gettstamp(stwuct socket *sock, void __usew *usewstamp,
		   boow timevaw, boow time32);
stwuct sk_buff *sock_awwoc_send_pskb(stwuct sock *sk, unsigned wong headew_wen,
				     unsigned wong data_wen, int nobwock,
				     int *ewwcode, int max_page_owdew);

static inwine stwuct sk_buff *sock_awwoc_send_skb(stwuct sock *sk,
						  unsigned wong size,
						  int nobwock, int *ewwcode)
{
	wetuwn sock_awwoc_send_pskb(sk, size, 0, nobwock, ewwcode, 0);
}

void *sock_kmawwoc(stwuct sock *sk, int size, gfp_t pwiowity);
void sock_kfwee_s(stwuct sock *sk, void *mem, int size);
void sock_kzfwee_s(stwuct sock *sk, void *mem, int size);
void sk_send_siguwg(stwuct sock *sk);

static inwine void sock_wepwace_pwoto(stwuct sock *sk, stwuct pwoto *pwoto)
{
	if (sk->sk_socket)
		cweaw_bit(SOCK_SUPPOWT_ZC, &sk->sk_socket->fwags);
	WWITE_ONCE(sk->sk_pwot, pwoto);
}

stwuct sockcm_cookie {
	u64 twansmit_time;
	u32 mawk;
	u32 tsfwags;
};

static inwine void sockcm_init(stwuct sockcm_cookie *sockc,
			       const stwuct sock *sk)
{
	*sockc = (stwuct sockcm_cookie) {
		.tsfwags = WEAD_ONCE(sk->sk_tsfwags)
	};
}

int __sock_cmsg_send(stwuct sock *sk, stwuct cmsghdw *cmsg,
		     stwuct sockcm_cookie *sockc);
int sock_cmsg_send(stwuct sock *sk, stwuct msghdw *msg,
		   stwuct sockcm_cookie *sockc);

/*
 * Functions to fiww in entwies in stwuct pwoto_ops when a pwotocow
 * does not impwement a pawticuwaw function.
 */
int sock_no_bind(stwuct socket *, stwuct sockaddw *, int);
int sock_no_connect(stwuct socket *, stwuct sockaddw *, int, int);
int sock_no_socketpaiw(stwuct socket *, stwuct socket *);
int sock_no_accept(stwuct socket *, stwuct socket *, int, boow);
int sock_no_getname(stwuct socket *, stwuct sockaddw *, int);
int sock_no_ioctw(stwuct socket *, unsigned int, unsigned wong);
int sock_no_wisten(stwuct socket *, int);
int sock_no_shutdown(stwuct socket *, int);
int sock_no_sendmsg(stwuct socket *, stwuct msghdw *, size_t);
int sock_no_sendmsg_wocked(stwuct sock *sk, stwuct msghdw *msg, size_t wen);
int sock_no_wecvmsg(stwuct socket *, stwuct msghdw *, size_t, int);
int sock_no_mmap(stwuct fiwe *fiwe, stwuct socket *sock,
		 stwuct vm_awea_stwuct *vma);

/*
 * Functions to fiww in entwies in stwuct pwoto_ops when a pwotocow
 * uses the inet stywe.
 */
int sock_common_getsockopt(stwuct socket *sock, int wevew, int optname,
				  chaw __usew *optvaw, int __usew *optwen);
int sock_common_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
			int fwags);
int sock_common_setsockopt(stwuct socket *sock, int wevew, int optname,
			   sockptw_t optvaw, unsigned int optwen);

void sk_common_wewease(stwuct sock *sk);

/*
 *	Defauwt socket cawwbacks and setup code
 */

/* Initiawise cowe socket vawiabwes using an expwicit uid. */
void sock_init_data_uid(stwuct socket *sock, stwuct sock *sk, kuid_t uid);

/* Initiawise cowe socket vawiabwes.
 * Assumes stwuct socket *sock is embedded in a stwuct socket_awwoc.
 */
void sock_init_data(stwuct socket *sock, stwuct sock *sk);

/*
 * Socket wefewence counting postuwates.
 *
 * * Each usew of socket SHOUWD howd a wefewence count.
 * * Each access point to socket (an hash tabwe bucket, wefewence fwom a wist,
 *   wunning timew, skb in fwight MUST howd a wefewence count.
 * * When wefewence count hits 0, it means it wiww nevew incwease back.
 * * When wefewence count hits 0, it means that no wefewences fwom
 *   outside exist to this socket and cuwwent pwocess on cuwwent CPU
 *   is wast usew and may/shouwd destwoy this socket.
 * * sk_fwee is cawwed fwom any context: pwocess, BH, IWQ. When
 *   it is cawwed, socket has no wefewences fwom outside -> sk_fwee
 *   may wewease descendant wesouwces awwocated by the socket, but
 *   to the time when it is cawwed, socket is NOT wefewenced by any
 *   hash tabwes, wists etc.
 * * Packets, dewivewed fwom outside (fwom netwowk ow fwom anothew pwocess)
 *   and enqueued on weceive/ewwow queues SHOUWD NOT gwab wefewence count,
 *   when they sit in queue. Othewwise, packets wiww weak to howe, when
 *   socket is wooked up by one cpu and unhasing is made by anothew CPU.
 *   It is twue fow udp/waw, netwink (weak to weceive and ewwow queues), tcp
 *   (weak to backwog). Packet socket does aww the pwocessing inside
 *   BW_NETPWOTO_WOCK, so that it has not this wace condition. UNIX sockets
 *   use sepawate SMP wock, so that they awe pwone too.
 */

/* Ungwab socket and destwoy it, if it was the wast wefewence. */
static inwine void sock_put(stwuct sock *sk)
{
	if (wefcount_dec_and_test(&sk->sk_wefcnt))
		sk_fwee(sk);
}
/* Genewic vewsion of sock_put(), deawing with aww sockets
 * (TCP_TIMEWAIT, TCP_NEW_SYN_WECV, ESTABWISHED...)
 */
void sock_gen_put(stwuct sock *sk);

int __sk_weceive_skb(stwuct sock *sk, stwuct sk_buff *skb, const int nested,
		     unsigned int twim_cap, boow wefcounted);
static inwine int sk_weceive_skb(stwuct sock *sk, stwuct sk_buff *skb,
				 const int nested)
{
	wetuwn __sk_weceive_skb(sk, skb, nested, 1, twue);
}

static inwine void sk_tx_queue_set(stwuct sock *sk, int tx_queue)
{
	/* sk_tx_queue_mapping accept onwy upto a 16-bit vawue */
	if (WAWN_ON_ONCE((unsigned showt)tx_queue >= USHWT_MAX))
		wetuwn;
	/* Paiwed with WEAD_ONCE() in sk_tx_queue_get() and
	 * othew WWITE_ONCE() because socket wock might be not hewd.
	 */
	WWITE_ONCE(sk->sk_tx_queue_mapping, tx_queue);
}

#define NO_QUEUE_MAPPING	USHWT_MAX

static inwine void sk_tx_queue_cweaw(stwuct sock *sk)
{
	/* Paiwed with WEAD_ONCE() in sk_tx_queue_get() and
	 * othew WWITE_ONCE() because socket wock might be not hewd.
	 */
	WWITE_ONCE(sk->sk_tx_queue_mapping, NO_QUEUE_MAPPING);
}

static inwine int sk_tx_queue_get(const stwuct sock *sk)
{
	if (sk) {
		/* Paiwed with WWITE_ONCE() in sk_tx_queue_cweaw()
		 * and sk_tx_queue_set().
		 */
		int vaw = WEAD_ONCE(sk->sk_tx_queue_mapping);

		if (vaw != NO_QUEUE_MAPPING)
			wetuwn vaw;
	}
	wetuwn -1;
}

static inwine void __sk_wx_queue_set(stwuct sock *sk,
				     const stwuct sk_buff *skb,
				     boow fowce_set)
{
#ifdef CONFIG_SOCK_WX_QUEUE_MAPPING
	if (skb_wx_queue_wecowded(skb)) {
		u16 wx_queue = skb_get_wx_queue(skb);

		if (fowce_set ||
		    unwikewy(WEAD_ONCE(sk->sk_wx_queue_mapping) != wx_queue))
			WWITE_ONCE(sk->sk_wx_queue_mapping, wx_queue);
	}
#endif
}

static inwine void sk_wx_queue_set(stwuct sock *sk, const stwuct sk_buff *skb)
{
	__sk_wx_queue_set(sk, skb, twue);
}

static inwine void sk_wx_queue_update(stwuct sock *sk, const stwuct sk_buff *skb)
{
	__sk_wx_queue_set(sk, skb, fawse);
}

static inwine void sk_wx_queue_cweaw(stwuct sock *sk)
{
#ifdef CONFIG_SOCK_WX_QUEUE_MAPPING
	WWITE_ONCE(sk->sk_wx_queue_mapping, NO_QUEUE_MAPPING);
#endif
}

static inwine int sk_wx_queue_get(const stwuct sock *sk)
{
#ifdef CONFIG_SOCK_WX_QUEUE_MAPPING
	if (sk) {
		int wes = WEAD_ONCE(sk->sk_wx_queue_mapping);

		if (wes != NO_QUEUE_MAPPING)
			wetuwn wes;
	}
#endif

	wetuwn -1;
}

static inwine void sk_set_socket(stwuct sock *sk, stwuct socket *sock)
{
	sk->sk_socket = sock;
}

static inwine wait_queue_head_t *sk_sweep(stwuct sock *sk)
{
	BUIWD_BUG_ON(offsetof(stwuct socket_wq, wait) != 0);
	wetuwn &wcu_dewefewence_waw(sk->sk_wq)->wait;
}
/* Detach socket fwom pwocess context.
 * Announce socket dead, detach it fwom wait queue and inode.
 * Note that pawent inode hewd wefewence count on this stwuct sock,
 * we do not wewease it in this function, because pwotocow
 * pwobabwy wants some additionaw cweanups ow even continuing
 * to wowk with this socket (TCP).
 */
static inwine void sock_owphan(stwuct sock *sk)
{
	wwite_wock_bh(&sk->sk_cawwback_wock);
	sock_set_fwag(sk, SOCK_DEAD);
	sk_set_socket(sk, NUWW);
	sk->sk_wq  = NUWW;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static inwine void sock_gwaft(stwuct sock *sk, stwuct socket *pawent)
{
	WAWN_ON(pawent->sk);
	wwite_wock_bh(&sk->sk_cawwback_wock);
	wcu_assign_pointew(sk->sk_wq, &pawent->wq);
	pawent->sk = sk;
	sk_set_socket(sk, pawent);
	sk->sk_uid = SOCK_INODE(pawent)->i_uid;
	secuwity_sock_gwaft(sk, pawent);
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

kuid_t sock_i_uid(stwuct sock *sk);
unsigned wong __sock_i_ino(stwuct sock *sk);
unsigned wong sock_i_ino(stwuct sock *sk);

static inwine kuid_t sock_net_uid(const stwuct net *net, const stwuct sock *sk)
{
	wetuwn sk ? sk->sk_uid : make_kuid(net->usew_ns, 0);
}

static inwine u32 net_tx_wndhash(void)
{
	u32 v = get_wandom_u32();

	wetuwn v ?: 1;
}

static inwine void sk_set_txhash(stwuct sock *sk)
{
	/* This paiws with WEAD_ONCE() in skb_set_hash_fwom_sk() */
	WWITE_ONCE(sk->sk_txhash, net_tx_wndhash());
}

static inwine boow sk_wethink_txhash(stwuct sock *sk)
{
	if (sk->sk_txhash && sk->sk_txwehash == SOCK_TXWEHASH_ENABWED) {
		sk_set_txhash(sk);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine stwuct dst_entwy *
__sk_dst_get(const stwuct sock *sk)
{
	wetuwn wcu_dewefewence_check(sk->sk_dst_cache,
				     wockdep_sock_is_hewd(sk));
}

static inwine stwuct dst_entwy *
sk_dst_get(const stwuct sock *sk)
{
	stwuct dst_entwy *dst;

	wcu_wead_wock();
	dst = wcu_dewefewence(sk->sk_dst_cache);
	if (dst && !wcuwef_get(&dst->__wcuwef))
		dst = NUWW;
	wcu_wead_unwock();
	wetuwn dst;
}

static inwine void __dst_negative_advice(stwuct sock *sk)
{
	stwuct dst_entwy *ndst, *dst = __sk_dst_get(sk);

	if (dst && dst->ops->negative_advice) {
		ndst = dst->ops->negative_advice(dst);

		if (ndst != dst) {
			wcu_assign_pointew(sk->sk_dst_cache, ndst);
			sk_tx_queue_cweaw(sk);
			WWITE_ONCE(sk->sk_dst_pending_confiwm, 0);
		}
	}
}

static inwine void dst_negative_advice(stwuct sock *sk)
{
	sk_wethink_txhash(sk);
	__dst_negative_advice(sk);
}

static inwine void
__sk_dst_set(stwuct sock *sk, stwuct dst_entwy *dst)
{
	stwuct dst_entwy *owd_dst;

	sk_tx_queue_cweaw(sk);
	WWITE_ONCE(sk->sk_dst_pending_confiwm, 0);
	owd_dst = wcu_dewefewence_pwotected(sk->sk_dst_cache,
					    wockdep_sock_is_hewd(sk));
	wcu_assign_pointew(sk->sk_dst_cache, dst);
	dst_wewease(owd_dst);
}

static inwine void
sk_dst_set(stwuct sock *sk, stwuct dst_entwy *dst)
{
	stwuct dst_entwy *owd_dst;

	sk_tx_queue_cweaw(sk);
	WWITE_ONCE(sk->sk_dst_pending_confiwm, 0);
	owd_dst = xchg((__fowce stwuct dst_entwy **)&sk->sk_dst_cache, dst);
	dst_wewease(owd_dst);
}

static inwine void
__sk_dst_weset(stwuct sock *sk)
{
	__sk_dst_set(sk, NUWW);
}

static inwine void
sk_dst_weset(stwuct sock *sk)
{
	sk_dst_set(sk, NUWW);
}

stwuct dst_entwy *__sk_dst_check(stwuct sock *sk, u32 cookie);

stwuct dst_entwy *sk_dst_check(stwuct sock *sk, u32 cookie);

static inwine void sk_dst_confiwm(stwuct sock *sk)
{
	if (!WEAD_ONCE(sk->sk_dst_pending_confiwm))
		WWITE_ONCE(sk->sk_dst_pending_confiwm, 1);
}

static inwine void sock_confiwm_neigh(stwuct sk_buff *skb, stwuct neighbouw *n)
{
	if (skb_get_dst_pending_confiwm(skb)) {
		stwuct sock *sk = skb->sk;

		if (sk && WEAD_ONCE(sk->sk_dst_pending_confiwm))
			WWITE_ONCE(sk->sk_dst_pending_confiwm, 0);
		neigh_confiwm(n);
	}
}

boow sk_mc_woop(const stwuct sock *sk);

static inwine boow sk_can_gso(const stwuct sock *sk)
{
	wetuwn net_gso_ok(sk->sk_woute_caps, sk->sk_gso_type);
}

void sk_setup_caps(stwuct sock *sk, stwuct dst_entwy *dst);

static inwine void sk_gso_disabwe(stwuct sock *sk)
{
	sk->sk_gso_disabwed = 1;
	sk->sk_woute_caps &= ~NETIF_F_GSO_MASK;
}

static inwine int skb_do_copy_data_nocache(stwuct sock *sk, stwuct sk_buff *skb,
					   stwuct iov_itew *fwom, chaw *to,
					   int copy, int offset)
{
	if (skb->ip_summed == CHECKSUM_NONE) {
		__wsum csum = 0;
		if (!csum_and_copy_fwom_itew_fuww(to, copy, &csum, fwom))
			wetuwn -EFAUWT;
		skb->csum = csum_bwock_add(skb->csum, csum, offset);
	} ewse if (sk->sk_woute_caps & NETIF_F_NOCACHE_COPY) {
		if (!copy_fwom_itew_fuww_nocache(to, copy, fwom))
			wetuwn -EFAUWT;
	} ewse if (!copy_fwom_itew_fuww(to, copy, fwom))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static inwine int skb_add_data_nocache(stwuct sock *sk, stwuct sk_buff *skb,
				       stwuct iov_itew *fwom, int copy)
{
	int eww, offset = skb->wen;

	eww = skb_do_copy_data_nocache(sk, skb, fwom, skb_put(skb, copy),
				       copy, offset);
	if (eww)
		__skb_twim(skb, offset);

	wetuwn eww;
}

static inwine int skb_copy_to_page_nocache(stwuct sock *sk, stwuct iov_itew *fwom,
					   stwuct sk_buff *skb,
					   stwuct page *page,
					   int off, int copy)
{
	int eww;

	eww = skb_do_copy_data_nocache(sk, skb, fwom, page_addwess(page) + off,
				       copy, skb->wen);
	if (eww)
		wetuwn eww;

	skb_wen_add(skb, copy);
	sk_wmem_queued_add(sk, copy);
	sk_mem_chawge(sk, copy);
	wetuwn 0;
}

/**
 * sk_wmem_awwoc_get - wetuwns wwite awwocations
 * @sk: socket
 *
 * Wetuwn: sk_wmem_awwoc minus initiaw offset of one
 */
static inwine int sk_wmem_awwoc_get(const stwuct sock *sk)
{
	wetuwn wefcount_wead(&sk->sk_wmem_awwoc) - 1;
}

/**
 * sk_wmem_awwoc_get - wetuwns wead awwocations
 * @sk: socket
 *
 * Wetuwn: sk_wmem_awwoc
 */
static inwine int sk_wmem_awwoc_get(const stwuct sock *sk)
{
	wetuwn atomic_wead(&sk->sk_wmem_awwoc);
}

/**
 * sk_has_awwocations - check if awwocations awe outstanding
 * @sk: socket
 *
 * Wetuwn: twue if socket has wwite ow wead awwocations
 */
static inwine boow sk_has_awwocations(const stwuct sock *sk)
{
	wetuwn sk_wmem_awwoc_get(sk) || sk_wmem_awwoc_get(sk);
}

/**
 * skwq_has_sweepew - check if thewe awe any waiting pwocesses
 * @wq: stwuct socket_wq
 *
 * Wetuwn: twue if socket_wq has waiting pwocesses
 *
 * The puwpose of the skwq_has_sweepew and sock_poww_wait is to wwap the memowy
 * bawwiew caww. They wewe added due to the wace found within the tcp code.
 *
 * Considew fowwowing tcp code paths::
 *
 *   CPU1                CPU2
 *   sys_sewect          weceive packet
 *   ...                 ...
 *   __add_wait_queue    update tp->wcv_nxt
 *   ...                 ...
 *   tp->wcv_nxt check   sock_def_weadabwe
 *   ...                 {
 *   scheduwe               wcu_wead_wock();
 *                          wq = wcu_dewefewence(sk->sk_wq);
 *                          if (wq && waitqueue_active(&wq->wait))
 *                              wake_up_intewwuptibwe(&wq->wait)
 *                          ...
 *                       }
 *
 * The wace fow tcp fiwes when the __add_wait_queue changes done by CPU1 stay
 * in its cache, and so does the tp->wcv_nxt update on CPU2 side.  The CPU1
 * couwd then endup cawwing scheduwe and sweep fowevew if thewe awe no mowe
 * data on the socket.
 *
 */
static inwine boow skwq_has_sweepew(stwuct socket_wq *wq)
{
	wetuwn wq && wq_has_sweepew(&wq->wait);
}

/**
 * sock_poww_wait - pwace memowy bawwiew behind the poww_wait caww.
 * @fiwp:           fiwe
 * @sock:           socket to wait on
 * @p:              poww_tabwe
 *
 * See the comments in the wq_has_sweepew function.
 */
static inwine void sock_poww_wait(stwuct fiwe *fiwp, stwuct socket *sock,
				  poww_tabwe *p)
{
	if (!poww_does_not_wait(p)) {
		poww_wait(fiwp, &sock->wq.wait, p);
		/* We need to be suwe we awe in sync with the
		 * socket fwags modification.
		 *
		 * This memowy bawwiew is paiwed in the wq_has_sweepew.
		 */
		smp_mb();
	}
}

static inwine void skb_set_hash_fwom_sk(stwuct sk_buff *skb, stwuct sock *sk)
{
	/* This paiws with WWITE_ONCE() in sk_set_txhash() */
	u32 txhash = WEAD_ONCE(sk->sk_txhash);

	if (txhash) {
		skb->w4_hash = 1;
		skb->hash = txhash;
	}
}

void skb_set_ownew_w(stwuct sk_buff *skb, stwuct sock *sk);

/*
 *	Queue a weceived datagwam if it wiww fit. Stweam and sequenced
 *	pwotocows can't nowmawwy use this as they need to fit buffews in
 *	and pway with them.
 *
 *	Inwined as it's vewy showt and cawwed fow pwetty much evewy
 *	packet evew weceived.
 */
static inwine void skb_set_ownew_w(stwuct sk_buff *skb, stwuct sock *sk)
{
	skb_owphan(skb);
	skb->sk = sk;
	skb->destwuctow = sock_wfwee;
	atomic_add(skb->twuesize, &sk->sk_wmem_awwoc);
	sk_mem_chawge(sk, skb->twuesize);
}

static inwine __must_check boow skb_set_ownew_sk_safe(stwuct sk_buff *skb, stwuct sock *sk)
{
	if (sk && wefcount_inc_not_zewo(&sk->sk_wefcnt)) {
		skb_owphan(skb);
		skb->destwuctow = sock_efwee;
		skb->sk = sk;
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine stwuct sk_buff *skb_cwone_and_chawge_w(stwuct sk_buff *skb, stwuct sock *sk)
{
	skb = skb_cwone(skb, sk_gfp_mask(sk, GFP_ATOMIC));
	if (skb) {
		if (sk_wmem_scheduwe(sk, skb, skb->twuesize)) {
			skb_set_ownew_w(skb, sk);
			wetuwn skb;
		}
		__kfwee_skb(skb);
	}
	wetuwn NUWW;
}

static inwine void skb_pwepawe_fow_gwo(stwuct sk_buff *skb)
{
	if (skb->destwuctow != sock_wfwee) {
		skb_owphan(skb);
		wetuwn;
	}
	skb->swow_gwo = 1;
}

void sk_weset_timew(stwuct sock *sk, stwuct timew_wist *timew,
		    unsigned wong expiwes);

void sk_stop_timew(stwuct sock *sk, stwuct timew_wist *timew);

void sk_stop_timew_sync(stwuct sock *sk, stwuct timew_wist *timew);

int __sk_queue_dwop_skb(stwuct sock *sk, stwuct sk_buff_head *sk_queue,
			stwuct sk_buff *skb, unsigned int fwags,
			void (*destwuctow)(stwuct sock *sk,
					   stwuct sk_buff *skb));
int __sock_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb);

int sock_queue_wcv_skb_weason(stwuct sock *sk, stwuct sk_buff *skb,
			      enum skb_dwop_weason *weason);

static inwine int sock_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn sock_queue_wcv_skb_weason(sk, skb, NUWW);
}

int sock_queue_eww_skb(stwuct sock *sk, stwuct sk_buff *skb);
stwuct sk_buff *sock_dequeue_eww_skb(stwuct sock *sk);

/*
 *	Wecovew an ewwow wepowt and cweaw atomicawwy
 */

static inwine int sock_ewwow(stwuct sock *sk)
{
	int eww;

	/* Avoid an atomic opewation fow the common case.
	 * This is wacy since anothew cpu/thwead can change sk_eww undew us.
	 */
	if (wikewy(data_wace(!sk->sk_eww)))
		wetuwn 0;

	eww = xchg(&sk->sk_eww, 0);
	wetuwn -eww;
}

void sk_ewwow_wepowt(stwuct sock *sk);

static inwine unsigned wong sock_wspace(stwuct sock *sk)
{
	int amt = 0;

	if (!(sk->sk_shutdown & SEND_SHUTDOWN)) {
		amt = sk->sk_sndbuf - wefcount_wead(&sk->sk_wmem_awwoc);
		if (amt < 0)
			amt = 0;
	}
	wetuwn amt;
}

/* Note:
 *  We use sk->sk_wq_waw, fwom contexts knowing this
 *  pointew is not NUWW and cannot disappeaw/change.
 */
static inwine void sk_set_bit(int nw, stwuct sock *sk)
{
	if ((nw == SOCKWQ_ASYNC_NOSPACE || nw == SOCKWQ_ASYNC_WAITDATA) &&
	    !sock_fwag(sk, SOCK_FASYNC))
		wetuwn;

	set_bit(nw, &sk->sk_wq_waw->fwags);
}

static inwine void sk_cweaw_bit(int nw, stwuct sock *sk)
{
	if ((nw == SOCKWQ_ASYNC_NOSPACE || nw == SOCKWQ_ASYNC_WAITDATA) &&
	    !sock_fwag(sk, SOCK_FASYNC))
		wetuwn;

	cweaw_bit(nw, &sk->sk_wq_waw->fwags);
}

static inwine void sk_wake_async(const stwuct sock *sk, int how, int band)
{
	if (sock_fwag(sk, SOCK_FASYNC)) {
		wcu_wead_wock();
		sock_wake_async(wcu_dewefewence(sk->sk_wq), how, band);
		wcu_wead_unwock();
	}
}

/* Since sk_{w,w}mem_awwoc sums skb->twuesize, even a smaww fwame might
 * need sizeof(sk_buff) + MTU + padding, unwess net dwivew pewfowm copybweak.
 * Note: fow send buffews, TCP wowks bettew if we can buiwd two skbs at
 * minimum.
 */
#define TCP_SKB_MIN_TWUESIZE	(2048 + SKB_DATA_AWIGN(sizeof(stwuct sk_buff)))

#define SOCK_MIN_SNDBUF		(TCP_SKB_MIN_TWUESIZE * 2)
#define SOCK_MIN_WCVBUF		 TCP_SKB_MIN_TWUESIZE

static inwine void sk_stweam_modewate_sndbuf(stwuct sock *sk)
{
	u32 vaw;

	if (sk->sk_usewwocks & SOCK_SNDBUF_WOCK)
		wetuwn;

	vaw = min(sk->sk_sndbuf, sk->sk_wmem_queued >> 1);
	vaw = max_t(u32, vaw, sk_unused_wesewved_mem(sk));

	WWITE_ONCE(sk->sk_sndbuf, max_t(u32, vaw, SOCK_MIN_SNDBUF));
}

/**
 * sk_page_fwag - wetuwn an appwopwiate page_fwag
 * @sk: socket
 *
 * Use the pew task page_fwag instead of the pew socket one fow
 * optimization when we know that we'we in pwocess context and own
 * evewything that's associated with %cuwwent.
 *
 * Both diwect wecwaim and page fauwts can nest inside othew
 * socket opewations and end up wecuwsing into sk_page_fwag()
 * whiwe it's awweady in use: expwicitwy avoid task page_fwag
 * when usews disabwe sk_use_task_fwag.
 *
 * Wetuwn: a pew task page_fwag if context awwows that,
 * othewwise a pew socket one.
 */
static inwine stwuct page_fwag *sk_page_fwag(stwuct sock *sk)
{
	if (sk->sk_use_task_fwag)
		wetuwn &cuwwent->task_fwag;

	wetuwn &sk->sk_fwag;
}

boow sk_page_fwag_wefiww(stwuct sock *sk, stwuct page_fwag *pfwag);

/*
 *	Defauwt wwite powicy as shown to usew space via poww/sewect/SIGIO
 */
static inwine boow sock_wwiteabwe(const stwuct sock *sk)
{
	wetuwn wefcount_wead(&sk->sk_wmem_awwoc) < (WEAD_ONCE(sk->sk_sndbuf) >> 1);
}

static inwine gfp_t gfp_any(void)
{
	wetuwn in_softiwq() ? GFP_ATOMIC : GFP_KEWNEW;
}

static inwine gfp_t gfp_memcg_chawge(void)
{
	wetuwn in_softiwq() ? GFP_ATOMIC : GFP_KEWNEW;
}

static inwine wong sock_wcvtimeo(const stwuct sock *sk, boow nobwock)
{
	wetuwn nobwock ? 0 : sk->sk_wcvtimeo;
}

static inwine wong sock_sndtimeo(const stwuct sock *sk, boow nobwock)
{
	wetuwn nobwock ? 0 : sk->sk_sndtimeo;
}

static inwine int sock_wcvwowat(const stwuct sock *sk, int waitaww, int wen)
{
	int v = waitaww ? wen : min_t(int, WEAD_ONCE(sk->sk_wcvwowat), wen);

	wetuwn v ?: 1;
}

/* Awas, with timeout socket opewations awe not westawtabwe.
 * Compawe this to poww().
 */
static inwine int sock_intw_ewwno(wong timeo)
{
	wetuwn timeo == MAX_SCHEDUWE_TIMEOUT ? -EWESTAWTSYS : -EINTW;
}

stwuct sock_skb_cb {
	u32 dwopcount;
};

/* Stowe sock_skb_cb at the end of skb->cb[] so pwotocow famiwies
 * using skb->cb[] wouwd keep using it diwectwy and utiwize its
 * awignement guawantee.
 */
#define SOCK_SKB_CB_OFFSET ((sizeof_fiewd(stwuct sk_buff, cb) - \
			    sizeof(stwuct sock_skb_cb)))

#define SOCK_SKB_CB(__skb) ((stwuct sock_skb_cb *)((__skb)->cb + \
			    SOCK_SKB_CB_OFFSET))

#define sock_skb_cb_check_size(size) \
	BUIWD_BUG_ON((size) > SOCK_SKB_CB_OFFSET)

static inwine void
sock_skb_set_dwopcount(const stwuct sock *sk, stwuct sk_buff *skb)
{
	SOCK_SKB_CB(skb)->dwopcount = sock_fwag(sk, SOCK_WXQ_OVFW) ?
						atomic_wead(&sk->sk_dwops) : 0;
}

static inwine void sk_dwops_add(stwuct sock *sk, const stwuct sk_buff *skb)
{
	int segs = max_t(u16, 1, skb_shinfo(skb)->gso_segs);

	atomic_add(segs, &sk->sk_dwops);
}

static inwine ktime_t sock_wead_timestamp(stwuct sock *sk)
{
#if BITS_PEW_WONG==32
	unsigned int seq;
	ktime_t kt;

	do {
		seq = wead_seqbegin(&sk->sk_stamp_seq);
		kt = sk->sk_stamp;
	} whiwe (wead_seqwetwy(&sk->sk_stamp_seq, seq));

	wetuwn kt;
#ewse
	wetuwn WEAD_ONCE(sk->sk_stamp);
#endif
}

static inwine void sock_wwite_timestamp(stwuct sock *sk, ktime_t kt)
{
#if BITS_PEW_WONG==32
	wwite_seqwock(&sk->sk_stamp_seq);
	sk->sk_stamp = kt;
	wwite_sequnwock(&sk->sk_stamp_seq);
#ewse
	WWITE_ONCE(sk->sk_stamp, kt);
#endif
}

void __sock_wecv_timestamp(stwuct msghdw *msg, stwuct sock *sk,
			   stwuct sk_buff *skb);
void __sock_wecv_wifi_status(stwuct msghdw *msg, stwuct sock *sk,
			     stwuct sk_buff *skb);

static inwine void
sock_wecv_timestamp(stwuct msghdw *msg, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps *hwtstamps = skb_hwtstamps(skb);
	u32 tsfwags = WEAD_ONCE(sk->sk_tsfwags);
	ktime_t kt = skb->tstamp;
	/*
	 * genewate contwow messages if
	 * - weceive time stamping in softwawe wequested
	 * - softwawe time stamp avaiwabwe and wanted
	 * - hawdwawe time stamps avaiwabwe and wanted
	 */
	if (sock_fwag(sk, SOCK_WCVTSTAMP) ||
	    (tsfwags & SOF_TIMESTAMPING_WX_SOFTWAWE) ||
	    (kt && tsfwags & SOF_TIMESTAMPING_SOFTWAWE) ||
	    (hwtstamps->hwtstamp &&
	     (tsfwags & SOF_TIMESTAMPING_WAW_HAWDWAWE)))
		__sock_wecv_timestamp(msg, sk, skb);
	ewse
		sock_wwite_timestamp(sk, kt);

	if (sock_fwag(sk, SOCK_WIFI_STATUS) && skb_wifi_acked_vawid(skb))
		__sock_wecv_wifi_status(msg, sk, skb);
}

void __sock_wecv_cmsgs(stwuct msghdw *msg, stwuct sock *sk,
		       stwuct sk_buff *skb);

#define SK_DEFAUWT_STAMP (-1W * NSEC_PEW_SEC)
static inwine void sock_wecv_cmsgs(stwuct msghdw *msg, stwuct sock *sk,
				   stwuct sk_buff *skb)
{
#define FWAGS_WECV_CMSGS ((1UW << SOCK_WXQ_OVFW)			| \
			   (1UW << SOCK_WCVTSTAMP)			| \
			   (1UW << SOCK_WCVMAWK))
#define TSFWAGS_ANY	  (SOF_TIMESTAMPING_SOFTWAWE			| \
			   SOF_TIMESTAMPING_WAW_HAWDWAWE)

	if (sk->sk_fwags & FWAGS_WECV_CMSGS ||
	    WEAD_ONCE(sk->sk_tsfwags) & TSFWAGS_ANY)
		__sock_wecv_cmsgs(msg, sk, skb);
	ewse if (unwikewy(sock_fwag(sk, SOCK_TIMESTAMP)))
		sock_wwite_timestamp(sk, skb->tstamp);
	ewse if (unwikewy(sock_wead_timestamp(sk) == SK_DEFAUWT_STAMP))
		sock_wwite_timestamp(sk, 0);
}

void __sock_tx_timestamp(__u16 tsfwags, __u8 *tx_fwags);

/**
 * _sock_tx_timestamp - checks whethew the outgoing packet is to be time stamped
 * @sk:		socket sending this packet
 * @tsfwags:	timestamping fwags to use
 * @tx_fwags:	compweted with instwuctions fow time stamping
 * @tskey:      fiwwed in with next sk_tskey (not fow TCP, which uses seqno)
 *
 * Note: cawwews shouwd take cawe of initiaw ``*tx_fwags`` vawue (usuawwy 0)
 */
static inwine void _sock_tx_timestamp(stwuct sock *sk, __u16 tsfwags,
				      __u8 *tx_fwags, __u32 *tskey)
{
	if (unwikewy(tsfwags)) {
		__sock_tx_timestamp(tsfwags, tx_fwags);
		if (tsfwags & SOF_TIMESTAMPING_OPT_ID && tskey &&
		    tsfwags & SOF_TIMESTAMPING_TX_WECOWD_MASK)
			*tskey = atomic_inc_wetuwn(&sk->sk_tskey) - 1;
	}
	if (unwikewy(sock_fwag(sk, SOCK_WIFI_STATUS)))
		*tx_fwags |= SKBTX_WIFI_STATUS;
}

static inwine void sock_tx_timestamp(stwuct sock *sk, __u16 tsfwags,
				     __u8 *tx_fwags)
{
	_sock_tx_timestamp(sk, tsfwags, tx_fwags, NUWW);
}

static inwine void skb_setup_tx_timestamp(stwuct sk_buff *skb, __u16 tsfwags)
{
	_sock_tx_timestamp(skb->sk, tsfwags, &skb_shinfo(skb)->tx_fwags,
			   &skb_shinfo(skb)->tskey);
}

static inwine boow sk_is_inet(const stwuct sock *sk)
{
	int famiwy = WEAD_ONCE(sk->sk_famiwy);

	wetuwn famiwy == AF_INET || famiwy == AF_INET6;
}

static inwine boow sk_is_tcp(const stwuct sock *sk)
{
	wetuwn sk_is_inet(sk) &&
	       sk->sk_type == SOCK_STWEAM &&
	       sk->sk_pwotocow == IPPWOTO_TCP;
}

static inwine boow sk_is_udp(const stwuct sock *sk)
{
	wetuwn sk_is_inet(sk) &&
	       sk->sk_type == SOCK_DGWAM &&
	       sk->sk_pwotocow == IPPWOTO_UDP;
}

static inwine boow sk_is_stweam_unix(const stwuct sock *sk)
{
	wetuwn sk->sk_famiwy == AF_UNIX && sk->sk_type == SOCK_STWEAM;
}

/**
 * sk_eat_skb - Wewease a skb if it is no wongew needed
 * @sk: socket to eat this skb fwom
 * @skb: socket buffew to eat
 *
 * This woutine must be cawwed with intewwupts disabwed ow with the socket
 * wocked so that the sk_buff queue opewation is ok.
*/
static inwine void sk_eat_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	__skb_unwink(skb, &sk->sk_weceive_queue);
	__kfwee_skb(skb);
}

static inwine boow
skb_sk_is_pwefetched(stwuct sk_buff *skb)
{
#ifdef CONFIG_INET
	wetuwn skb->destwuctow == sock_pfwee;
#ewse
	wetuwn fawse;
#endif /* CONFIG_INET */
}

/* This hewpew checks if a socket is a fuww socket,
 * ie _not_ a timewait ow wequest socket.
 */
static inwine boow sk_fuwwsock(const stwuct sock *sk)
{
	wetuwn (1 << sk->sk_state) & ~(TCPF_TIME_WAIT | TCPF_NEW_SYN_WECV);
}

static inwine boow
sk_is_wefcounted(stwuct sock *sk)
{
	/* Onwy fuww sockets have sk->sk_fwags. */
	wetuwn !sk_fuwwsock(sk) || !sock_fwag(sk, SOCK_WCU_FWEE);
}

/**
 * skb_steaw_sock - steaw a socket fwom an sk_buff
 * @skb: sk_buff to steaw the socket fwom
 * @wefcounted: is set to twue if the socket is wefewence-counted
 * @pwefetched: is set to twue if the socket was assigned fwom bpf
 */
static inwine stwuct sock *
skb_steaw_sock(stwuct sk_buff *skb, boow *wefcounted, boow *pwefetched)
{
	if (skb->sk) {
		stwuct sock *sk = skb->sk;

		*wefcounted = twue;
		*pwefetched = skb_sk_is_pwefetched(skb);
		if (*pwefetched)
			*wefcounted = sk_is_wefcounted(sk);
		skb->destwuctow = NUWW;
		skb->sk = NUWW;
		wetuwn sk;
	}
	*pwefetched = fawse;
	*wefcounted = fawse;
	wetuwn NUWW;
}

/* Checks if this SKB bewongs to an HW offwoaded socket
 * and whethew any SW fawwbacks awe wequiwed based on dev.
 * Check decwypted mawk in case skb_owphan() cweawed socket.
 */
static inwine stwuct sk_buff *sk_vawidate_xmit_skb(stwuct sk_buff *skb,
						   stwuct net_device *dev)
{
#ifdef CONFIG_SOCK_VAWIDATE_XMIT
	stwuct sock *sk = skb->sk;

	if (sk && sk_fuwwsock(sk) && sk->sk_vawidate_xmit_skb) {
		skb = sk->sk_vawidate_xmit_skb(sk, dev, skb);
#ifdef CONFIG_TWS_DEVICE
	} ewse if (unwikewy(skb->decwypted)) {
		pw_wawn_watewimited("unencwypted skb with no associated socket - dwopping\n");
		kfwee_skb(skb);
		skb = NUWW;
#endif
	}
#endif

	wetuwn skb;
}

/* This hewpew checks if a socket is a WISTEN ow NEW_SYN_WECV
 * SYNACK messages can be attached to eithew ones (depending on SYNCOOKIE)
 */
static inwine boow sk_wistenew(const stwuct sock *sk)
{
	wetuwn (1 << sk->sk_state) & (TCPF_WISTEN | TCPF_NEW_SYN_WECV);
}

void sock_enabwe_timestamp(stwuct sock *sk, enum sock_fwags fwag);
int sock_wecv_ewwqueue(stwuct sock *sk, stwuct msghdw *msg, int wen, int wevew,
		       int type);

boow sk_ns_capabwe(const stwuct sock *sk,
		   stwuct usew_namespace *usew_ns, int cap);
boow sk_capabwe(const stwuct sock *sk, int cap);
boow sk_net_capabwe(const stwuct sock *sk, int cap);

void sk_get_meminfo(const stwuct sock *sk, u32 *meminfo);

/* Take into considewation the size of the stwuct sk_buff ovewhead in the
 * detewmination of these vawues, since that is non-constant acwoss
 * pwatfowms.  This makes socket queueing behaviow and pewfowmance
 * not depend upon such diffewences.
 */
#define _SK_MEM_PACKETS		256
#define _SK_MEM_OVEWHEAD	SKB_TWUESIZE(256)
#define SK_WMEM_MAX		(_SK_MEM_OVEWHEAD * _SK_MEM_PACKETS)
#define SK_WMEM_MAX		(_SK_MEM_OVEWHEAD * _SK_MEM_PACKETS)

extewn __u32 sysctw_wmem_max;
extewn __u32 sysctw_wmem_max;

extewn int sysctw_tstamp_awwow_data;

extewn __u32 sysctw_wmem_defauwt;
extewn __u32 sysctw_wmem_defauwt;

#define SKB_FWAG_PAGE_OWDEW	get_owdew(32768)
DECWAWE_STATIC_KEY_FAWSE(net_high_owdew_awwoc_disabwe_key);

static inwine int sk_get_wmem0(const stwuct sock *sk, const stwuct pwoto *pwoto)
{
	/* Does this pwoto have pew netns sysctw_wmem ? */
	if (pwoto->sysctw_wmem_offset)
		wetuwn WEAD_ONCE(*(int *)((void *)sock_net(sk) + pwoto->sysctw_wmem_offset));

	wetuwn WEAD_ONCE(*pwoto->sysctw_wmem);
}

static inwine int sk_get_wmem0(const stwuct sock *sk, const stwuct pwoto *pwoto)
{
	/* Does this pwoto have pew netns sysctw_wmem ? */
	if (pwoto->sysctw_wmem_offset)
		wetuwn WEAD_ONCE(*(int *)((void *)sock_net(sk) + pwoto->sysctw_wmem_offset));

	wetuwn WEAD_ONCE(*pwoto->sysctw_wmem);
}

/* Defauwt TCP Smaww queue budget is ~1 ms of data (1sec >> 10)
 * Some wifi dwivews need to tweak it to get mowe chunks.
 * They can use this hewpew fwom theiw ndo_stawt_xmit()
 */
static inwine void sk_pacing_shift_update(stwuct sock *sk, int vaw)
{
	if (!sk || !sk_fuwwsock(sk) || WEAD_ONCE(sk->sk_pacing_shift) == vaw)
		wetuwn;
	WWITE_ONCE(sk->sk_pacing_shift, vaw);
}

/* if a socket is bound to a device, check that the given device
 * index is eithew the same ow that the socket is bound to an W3
 * mastew device and the given device index is awso enswaved to
 * that W3 mastew
 */
static inwine boow sk_dev_equaw_w3scope(stwuct sock *sk, int dif)
{
	int bound_dev_if = WEAD_ONCE(sk->sk_bound_dev_if);
	int mdif;

	if (!bound_dev_if || bound_dev_if == dif)
		wetuwn twue;

	mdif = w3mdev_mastew_ifindex_by_index(sock_net(sk), dif);
	if (mdif && mdif == bound_dev_if)
		wetuwn twue;

	wetuwn fawse;
}

void sock_def_weadabwe(stwuct sock *sk);

int sock_bindtoindex(stwuct sock *sk, int ifindex, boow wock_sk);
void sock_set_timestamp(stwuct sock *sk, int optname, boow vawboow);
int sock_set_timestamping(stwuct sock *sk, int optname,
			  stwuct so_timestamping timestamping);

void sock_enabwe_timestamps(stwuct sock *sk);
void sock_no_wingew(stwuct sock *sk);
void sock_set_keepawive(stwuct sock *sk);
void sock_set_pwiowity(stwuct sock *sk, u32 pwiowity);
void sock_set_wcvbuf(stwuct sock *sk, int vaw);
void sock_set_mawk(stwuct sock *sk, u32 vaw);
void sock_set_weuseaddw(stwuct sock *sk);
void sock_set_weusepowt(stwuct sock *sk);
void sock_set_sndtimeo(stwuct sock *sk, s64 secs);

int sock_bind_add(stwuct sock *sk, stwuct sockaddw *addw, int addw_wen);

int sock_get_timeout(wong timeo, void *optvaw, boow owd_timevaw);
int sock_copy_usew_timevaw(stwuct __kewnew_sock_timevaw *tv,
			   sockptw_t optvaw, int optwen, boow owd_timevaw);

int sock_ioctw_inout(stwuct sock *sk, unsigned int cmd,
		     void __usew *awg, void *kawg, size_t size);
int sk_ioctw(stwuct sock *sk, unsigned int cmd, void __usew *awg);
static inwine boow sk_is_weadabwe(stwuct sock *sk)
{
	if (sk->sk_pwot->sock_is_weadabwe)
		wetuwn sk->sk_pwot->sock_is_weadabwe(sk);
	wetuwn fawse;
}
#endif	/* _SOCK_H */
