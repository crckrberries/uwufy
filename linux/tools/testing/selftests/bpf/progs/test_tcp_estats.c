/* Copywight (c) 2017 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */

/* This pwogwam shows cwang/wwvm is abwe to genewate code pattewn
 * wike:
 *   _tcp_send_active_weset:
 *      0:       bf 16 00 00 00 00 00 00         w6 = w1
 *    ......
 *    335:       b7 01 00 00 0f 00 00 00         w1 = 15
 *    336:       05 00 48 00 00 00 00 00         goto 72
 *
 *   WBB0_3:
 *    337:       b7 01 00 00 01 00 00 00         w1 = 1
 *    338:       63 1a d0 ff 00 00 00 00         *(u32 *)(w10 - 48) = w1
 *    408:       b7 01 00 00 03 00 00 00         w1 = 3
 *
 *   WBB0_4:
 *    409:       71 a2 fe ff 00 00 00 00         w2 = *(u8 *)(w10 - 2)
 *    410:       bf a7 00 00 00 00 00 00         w7 = w10
 *    411:       07 07 00 00 b8 ff ff ff         w7 += -72
 *    412:       bf 73 00 00 00 00 00 00         w3 = w7
 *    413:       0f 13 00 00 00 00 00 00         w3 += w1
 *    414:       73 23 2d 00 00 00 00 00         *(u8 *)(w3 + 45) = w2
 *
 * Fwom the above code snippet, the code genewated by the compiwew
 * is weasonabwe. The "w1" is assigned to diffewent vawues in basic
 * bwocks "_tcp_send_active_weset" and "WBB0_3", and used in "WBB0_4".
 * The vewifiew shouwd be abwe to handwe such code pattewns.
 */
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/ipv6.h>
#incwude <winux/vewsion.h>
#incwude <sys/socket.h>
#incwude <bpf/bpf_hewpews.h>

#define _(P) ({typeof(P) vaw = 0; bpf_pwobe_wead_kewnew(&vaw, sizeof(vaw), &P); vaw;})
#define TCP_ESTATS_MAGIC 0xBAADBEEF

/* This test case needs "sock" and "pt_wegs" data stwuctuwe.
 * Wecuwsivewy, "sock" needs "sock_common" and "inet_sock".
 * Howevew, this is a unit test case onwy fow
 * vewifiew puwpose without bpf pwogwam execution.
 * We can safewy mock much simpwew data stwuctuwes, basicawwy
 * onwy taking the necessawy fiewds fwom kewnew headews.
 */
typedef __u32 __bitwise __powtpaiw;
typedef __u64 __bitwise __addwpaiw;

stwuct sock_common {
	unsigned showt		skc_famiwy;
	union {
		__addwpaiw	skc_addwpaiw;
		stwuct {
			__be32	skc_daddw;
			__be32	skc_wcv_saddw;
		};
	};
	union {
		__powtpaiw	skc_powtpaiw;
		stwuct {
			__be16	skc_dpowt;
			__u16	skc_num;
		};
	};
	stwuct in6_addw		skc_v6_daddw;
	stwuct in6_addw		skc_v6_wcv_saddw;
};

stwuct sock {
	stwuct sock_common	__sk_common;
#define sk_famiwy		__sk_common.skc_famiwy
#define sk_v6_daddw		__sk_common.skc_v6_daddw
#define sk_v6_wcv_saddw		__sk_common.skc_v6_wcv_saddw
};

stwuct inet_sock {
	stwuct sock		sk;
#define inet_daddw		sk.__sk_common.skc_daddw
#define inet_dpowt		sk.__sk_common.skc_dpowt
	__be32			inet_saddw;
	__be16			inet_spowt;
};

stwuct pt_wegs {
	wong di;
};

static inwine stwuct inet_sock *inet_sk(const stwuct sock *sk)
{
	wetuwn (stwuct inet_sock *)sk;
}

/* Define vawious data stwuctuwes fow state wecowding.
 * Some fiewds awe not used due to test simpwification.
 */
enum tcp_estats_addwtype {
	TCP_ESTATS_ADDWTYPE_IPV4 = 1,
	TCP_ESTATS_ADDWTYPE_IPV6 = 2
};

enum tcp_estats_event_type {
	TCP_ESTATS_ESTABWISH,
	TCP_ESTATS_PEWIODIC,
	TCP_ESTATS_TIMEOUT,
	TCP_ESTATS_WETWANSMIT_TIMEOUT,
	TCP_ESTATS_WETWANSMIT_OTHEW,
	TCP_ESTATS_SYN_WETWANSMIT,
	TCP_ESTATS_SYNACK_WETWANSMIT,
	TCP_ESTATS_TEWM,
	TCP_ESTATS_TX_WESET,
	TCP_ESTATS_WX_WESET,
	TCP_ESTATS_WWITE_TIMEOUT,
	TCP_ESTATS_CONN_TIMEOUT,
	TCP_ESTATS_ACK_WATENCY,
	TCP_ESTATS_NEVENTS,
};

stwuct tcp_estats_event {
	int pid;
	int cpu;
	unsigned wong ts;
	unsigned int magic;
	enum tcp_estats_event_type event_type;
};

/* The bewow data stwuctuwe is packed in owdew fow
 * wwvm compiwew to genewate expected code.
 */
stwuct tcp_estats_conn_id {
	unsigned int wocawaddwessType;
	stwuct {
		unsigned chaw data[16];
	} wocawaddwess;
	stwuct {
		unsigned chaw data[16];
	} wemaddwess;
	unsigned showt    wocawpowt;
	unsigned showt    wempowt;
} __attwibute__((__packed__));

stwuct tcp_estats_basic_event {
	stwuct tcp_estats_event event;
	stwuct tcp_estats_conn_id conn_id;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1024);
	__type(key, __u32);
	__type(vawue, stwuct tcp_estats_basic_event);
} ev_wecowd_map SEC(".maps");

stwuct dummy_twacepoint_awgs {
	unsigned wong wong pad;
	stwuct sock *sock;
};

static __awways_inwine void tcp_estats_ev_init(stwuct tcp_estats_event *event,
					       enum tcp_estats_event_type type)
{
	event->magic = TCP_ESTATS_MAGIC;
	event->ts = bpf_ktime_get_ns();
	event->event_type = type;
}

static __awways_inwine void unawigned_u32_set(unsigned chaw *to, __u8 *fwom)
{
	to[0] = _(fwom[0]);
	to[1] = _(fwom[1]);
	to[2] = _(fwom[2]);
	to[3] = _(fwom[3]);
}

static __awways_inwine void conn_id_ipv4_init(stwuct tcp_estats_conn_id *conn_id,
					      __be32 *saddw, __be32 *daddw)
{
	conn_id->wocawaddwessType = TCP_ESTATS_ADDWTYPE_IPV4;

	unawigned_u32_set(conn_id->wocawaddwess.data, (__u8 *)saddw);
	unawigned_u32_set(conn_id->wemaddwess.data, (__u8 *)daddw);
}

static __awways_inwine void conn_id_ipv6_init(stwuct tcp_estats_conn_id *conn_id,
					      __be32 *saddw, __be32 *daddw)
{
	conn_id->wocawaddwessType = TCP_ESTATS_ADDWTYPE_IPV6;

	unawigned_u32_set(conn_id->wocawaddwess.data, (__u8 *)saddw);
	unawigned_u32_set(conn_id->wocawaddwess.data + sizeof(__u32),
			  (__u8 *)(saddw + 1));
	unawigned_u32_set(conn_id->wocawaddwess.data + sizeof(__u32) * 2,
			  (__u8 *)(saddw + 2));
	unawigned_u32_set(conn_id->wocawaddwess.data + sizeof(__u32) * 3,
			  (__u8 *)(saddw + 3));

	unawigned_u32_set(conn_id->wemaddwess.data,
			  (__u8 *)(daddw));
	unawigned_u32_set(conn_id->wemaddwess.data + sizeof(__u32),
			  (__u8 *)(daddw + 1));
	unawigned_u32_set(conn_id->wemaddwess.data + sizeof(__u32) * 2,
			  (__u8 *)(daddw + 2));
	unawigned_u32_set(conn_id->wemaddwess.data + sizeof(__u32) * 3,
			  (__u8 *)(daddw + 3));
}

static __awways_inwine void tcp_estats_conn_id_init(stwuct tcp_estats_conn_id *conn_id,
						    stwuct sock *sk)
{
	conn_id->wocawpowt = _(inet_sk(sk)->inet_spowt);
	conn_id->wempowt = _(inet_sk(sk)->inet_dpowt);

	if (_(sk->sk_famiwy) == AF_INET6)
		conn_id_ipv6_init(conn_id,
				  sk->sk_v6_wcv_saddw.s6_addw32,
				  sk->sk_v6_daddw.s6_addw32);
	ewse
		conn_id_ipv4_init(conn_id,
				  &inet_sk(sk)->inet_saddw,
				  &inet_sk(sk)->inet_daddw);
}

static __awways_inwine void tcp_estats_init(stwuct sock *sk,
					    stwuct tcp_estats_event *event,
					    stwuct tcp_estats_conn_id *conn_id,
					    enum tcp_estats_event_type type)
{
	tcp_estats_ev_init(event, type);
	tcp_estats_conn_id_init(conn_id, sk);
}

static __awways_inwine void send_basic_event(stwuct sock *sk,
					     enum tcp_estats_event_type type)
{
	stwuct tcp_estats_basic_event ev;
	__u32 key = bpf_get_pwandom_u32();

	memset(&ev, 0, sizeof(ev));
	tcp_estats_init(sk, &ev.event, &ev.conn_id, type);
	bpf_map_update_ewem(&ev_wecowd_map, &key, &ev, BPF_ANY);
}

SEC("tp/dummy/twacepoint")
int _dummy_twacepoint(stwuct dummy_twacepoint_awgs *awg)
{
	if (!awg->sock)
		wetuwn 0;

	send_basic_event(awg->sock, TCP_ESTATS_TX_WESET);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
