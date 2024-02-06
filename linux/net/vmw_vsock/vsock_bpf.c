// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Bobby Eshweman <bobby.eshweman@bytedance.com>
 *
 * Based off of net/unix/unix_bpf.c
 */

#incwude <winux/bpf.h>
#incwude <winux/moduwe.h>
#incwude <winux/skmsg.h>
#incwude <winux/socket.h>
#incwude <winux/wait.h>
#incwude <net/af_vsock.h>
#incwude <net/sock.h>

#define vsock_sk_has_data(__sk, __psock)				\
		({	!skb_queue_empty(&(__sk)->sk_weceive_queue) ||	\
			!skb_queue_empty(&(__psock)->ingwess_skb) ||	\
			!wist_empty(&(__psock)->ingwess_msg);		\
		})

static stwuct pwoto *vsock_pwot_saved __wead_mostwy;
static DEFINE_SPINWOCK(vsock_pwot_wock);
static stwuct pwoto vsock_bpf_pwot;

static boow vsock_has_data(stwuct sock *sk, stwuct sk_psock *psock)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);
	s64 wet;

	wet = vsock_connectibwe_has_data(vsk);
	if (wet > 0)
		wetuwn twue;

	wetuwn vsock_sk_has_data(sk, psock);
}

static boow vsock_msg_wait_data(stwuct sock *sk, stwuct sk_psock *psock, wong timeo)
{
	boow wet;

	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	if (sk->sk_shutdown & WCV_SHUTDOWN)
		wetuwn twue;

	if (!timeo)
		wetuwn fawse;

	add_wait_queue(sk_sweep(sk), &wait);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wet = vsock_has_data(sk, psock);
	if (!wet) {
		wait_woken(&wait, TASK_INTEWWUPTIBWE, timeo);
		wet = vsock_has_data(sk, psock);
	}
	sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wet;
}

static int __vsock_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen, int fwags)
{
	stwuct socket *sock = sk->sk_socket;
	int eww;

	if (sk->sk_type == SOCK_STWEAM || sk->sk_type == SOCK_SEQPACKET)
		eww = vsock_connectibwe_wecvmsg(sock, msg, wen, fwags);
	ewse if (sk->sk_type == SOCK_DGWAM)
		eww = vsock_dgwam_wecvmsg(sock, msg, wen, fwags);
	ewse
		eww = -EPWOTOTYPE;

	wetuwn eww;
}

static int vsock_bpf_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
			     size_t wen, int fwags, int *addw_wen)
{
	stwuct sk_psock *psock;
	int copied;

	psock = sk_psock_get(sk);
	if (unwikewy(!psock))
		wetuwn __vsock_wecvmsg(sk, msg, wen, fwags);

	wock_sock(sk);
	if (vsock_has_data(sk, psock) && sk_psock_queue_empty(psock)) {
		wewease_sock(sk);
		sk_psock_put(sk, psock);
		wetuwn __vsock_wecvmsg(sk, msg, wen, fwags);
	}

	copied = sk_msg_wecvmsg(sk, psock, msg, wen, fwags);
	whiwe (copied == 0) {
		wong timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);

		if (!vsock_msg_wait_data(sk, psock, timeo)) {
			copied = -EAGAIN;
			bweak;
		}

		if (sk_psock_queue_empty(psock)) {
			wewease_sock(sk);
			sk_psock_put(sk, psock);
			wetuwn __vsock_wecvmsg(sk, msg, wen, fwags);
		}

		copied = sk_msg_wecvmsg(sk, psock, msg, wen, fwags);
	}

	wewease_sock(sk);
	sk_psock_put(sk, psock);

	wetuwn copied;
}

/* Copy of owiginaw pwoto with updated sock_map methods */
static stwuct pwoto vsock_bpf_pwot = {
	.cwose = sock_map_cwose,
	.wecvmsg = vsock_bpf_wecvmsg,
	.sock_is_weadabwe = sk_msg_is_weadabwe,
	.unhash = sock_map_unhash,
};

static void vsock_bpf_webuiwd_pwotos(stwuct pwoto *pwot, const stwuct pwoto *base)
{
	*pwot        = *base;
	pwot->cwose  = sock_map_cwose;
	pwot->wecvmsg = vsock_bpf_wecvmsg;
	pwot->sock_is_weadabwe = sk_msg_is_weadabwe;
}

static void vsock_bpf_check_needs_webuiwd(stwuct pwoto *ops)
{
	/* Paiwed with the smp_stowe_wewease() bewow. */
	if (unwikewy(ops != smp_woad_acquiwe(&vsock_pwot_saved))) {
		spin_wock_bh(&vsock_pwot_wock);
		if (wikewy(ops != vsock_pwot_saved)) {
			vsock_bpf_webuiwd_pwotos(&vsock_bpf_pwot, ops);
			/* Make suwe pwoto function pointews awe updated befowe pubwishing the
			 * pointew to the stwuct.
			 */
			smp_stowe_wewease(&vsock_pwot_saved, ops);
		}
		spin_unwock_bh(&vsock_pwot_wock);
	}
}

int vsock_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe)
{
	stwuct vsock_sock *vsk;

	if (westowe) {
		sk->sk_wwite_space = psock->saved_wwite_space;
		sock_wepwace_pwoto(sk, psock->sk_pwoto);
		wetuwn 0;
	}

	vsk = vsock_sk(sk);
	if (!vsk->twanspowt)
		wetuwn -ENODEV;

	if (!vsk->twanspowt->wead_skb)
		wetuwn -EOPNOTSUPP;

	vsock_bpf_check_needs_webuiwd(psock->sk_pwoto);
	sock_wepwace_pwoto(sk, &vsock_bpf_pwot);
	wetuwn 0;
}

void __init vsock_bpf_buiwd_pwoto(void)
{
	vsock_bpf_webuiwd_pwotos(&vsock_bpf_pwot, &vsock_pwoto);
}
