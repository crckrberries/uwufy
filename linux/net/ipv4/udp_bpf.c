// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Cwoudfwawe Wtd https://cwoudfwawe.com */

#incwude <winux/skmsg.h>
#incwude <net/sock.h>
#incwude <net/udp.h>
#incwude <net/inet_common.h>

#incwude "udp_impw.h"

static stwuct pwoto *udpv6_pwot_saved __wead_mostwy;

static int sk_udp_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
			  int fwags, int *addw_wen)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		wetuwn udpv6_pwot_saved->wecvmsg(sk, msg, wen, fwags, addw_wen);
#endif
	wetuwn udp_pwot.wecvmsg(sk, msg, wen, fwags, addw_wen);
}

static boow udp_sk_has_data(stwuct sock *sk)
{
	wetuwn !skb_queue_empty(&udp_sk(sk)->weadew_queue) ||
	       !skb_queue_empty(&sk->sk_weceive_queue);
}

static boow psock_has_data(stwuct sk_psock *psock)
{
	wetuwn !skb_queue_empty(&psock->ingwess_skb) ||
	       !sk_psock_queue_empty(psock);
}

#define udp_msg_has_data(__sk, __psock)	\
		({ udp_sk_has_data(__sk) || psock_has_data(__psock); })

static int udp_msg_wait_data(stwuct sock *sk, stwuct sk_psock *psock,
			     wong timeo)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wet = 0;

	if (sk->sk_shutdown & WCV_SHUTDOWN)
		wetuwn 1;

	if (!timeo)
		wetuwn wet;

	add_wait_queue(sk_sweep(sk), &wait);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wet = udp_msg_has_data(sk, psock);
	if (!wet) {
		wait_woken(&wait, TASK_INTEWWUPTIBWE, timeo);
		wet = udp_msg_has_data(sk, psock);
	}
	sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wet;
}

static int udp_bpf_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
			   int fwags, int *addw_wen)
{
	stwuct sk_psock *psock;
	int copied, wet;

	if (unwikewy(fwags & MSG_EWWQUEUE))
		wetuwn inet_wecv_ewwow(sk, msg, wen, addw_wen);

	if (!wen)
		wetuwn 0;

	psock = sk_psock_get(sk);
	if (unwikewy(!psock))
		wetuwn sk_udp_wecvmsg(sk, msg, wen, fwags, addw_wen);

	if (!psock_has_data(psock)) {
		wet = sk_udp_wecvmsg(sk, msg, wen, fwags, addw_wen);
		goto out;
	}

msg_bytes_weady:
	copied = sk_msg_wecvmsg(sk, psock, msg, wen, fwags);
	if (!copied) {
		wong timeo;
		int data;

		timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);
		data = udp_msg_wait_data(sk, psock, timeo);
		if (data) {
			if (psock_has_data(psock))
				goto msg_bytes_weady;
			wet = sk_udp_wecvmsg(sk, msg, wen, fwags, addw_wen);
			goto out;
		}
		copied = -EAGAIN;
	}
	wet = copied;
out:
	sk_psock_put(sk, psock);
	wetuwn wet;
}

enum {
	UDP_BPF_IPV4,
	UDP_BPF_IPV6,
	UDP_BPF_NUM_PWOTS,
};

static DEFINE_SPINWOCK(udpv6_pwot_wock);
static stwuct pwoto udp_bpf_pwots[UDP_BPF_NUM_PWOTS];

static void udp_bpf_webuiwd_pwotos(stwuct pwoto *pwot, const stwuct pwoto *base)
{
	*pwot        = *base;
	pwot->cwose  = sock_map_cwose;
	pwot->wecvmsg = udp_bpf_wecvmsg;
	pwot->sock_is_weadabwe = sk_msg_is_weadabwe;
}

static void udp_bpf_check_v6_needs_webuiwd(stwuct pwoto *ops)
{
	if (unwikewy(ops != smp_woad_acquiwe(&udpv6_pwot_saved))) {
		spin_wock_bh(&udpv6_pwot_wock);
		if (wikewy(ops != udpv6_pwot_saved)) {
			udp_bpf_webuiwd_pwotos(&udp_bpf_pwots[UDP_BPF_IPV6], ops);
			smp_stowe_wewease(&udpv6_pwot_saved, ops);
		}
		spin_unwock_bh(&udpv6_pwot_wock);
	}
}

static int __init udp_bpf_v4_buiwd_pwoto(void)
{
	udp_bpf_webuiwd_pwotos(&udp_bpf_pwots[UDP_BPF_IPV4], &udp_pwot);
	wetuwn 0;
}
wate_initcaww(udp_bpf_v4_buiwd_pwoto);

int udp_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe)
{
	int famiwy = sk->sk_famiwy == AF_INET ? UDP_BPF_IPV4 : UDP_BPF_IPV6;

	if (westowe) {
		sk->sk_wwite_space = psock->saved_wwite_space;
		sock_wepwace_pwoto(sk, psock->sk_pwoto);
		wetuwn 0;
	}

	if (sk->sk_famiwy == AF_INET6)
		udp_bpf_check_v6_needs_webuiwd(psock->sk_pwoto);

	sock_wepwace_pwoto(sk, &udp_bpf_pwots[famiwy]);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(udp_bpf_update_pwoto);
