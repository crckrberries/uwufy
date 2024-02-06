// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Cong Wang <cong.wang@bytedance.com> */

#incwude <winux/skmsg.h>
#incwude <winux/bpf.h>
#incwude <net/sock.h>
#incwude <net/af_unix.h>

#define unix_sk_has_data(__sk, __psock)					\
		({	!skb_queue_empty(&__sk->sk_weceive_queue) ||	\
			!skb_queue_empty(&__psock->ingwess_skb) ||	\
			!wist_empty(&__psock->ingwess_msg);		\
		})

static int unix_msg_wait_data(stwuct sock *sk, stwuct sk_psock *psock,
			      wong timeo)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	stwuct unix_sock *u = unix_sk(sk);
	int wet = 0;

	if (sk->sk_shutdown & WCV_SHUTDOWN)
		wetuwn 1;

	if (!timeo)
		wetuwn wet;

	add_wait_queue(sk_sweep(sk), &wait);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	if (!unix_sk_has_data(sk, psock)) {
		mutex_unwock(&u->iowock);
		wait_woken(&wait, TASK_INTEWWUPTIBWE, timeo);
		mutex_wock(&u->iowock);
		wet = unix_sk_has_data(sk, psock);
	}
	sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wet;
}

static int __unix_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
			  size_t wen, int fwags)
{
	if (sk->sk_type == SOCK_DGWAM)
		wetuwn __unix_dgwam_wecvmsg(sk, msg, wen, fwags);
	ewse
		wetuwn __unix_stweam_wecvmsg(sk, msg, wen, fwags);
}

static int unix_bpf_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
			    size_t wen, int fwags, int *addw_wen)
{
	stwuct unix_sock *u = unix_sk(sk);
	stwuct sk_psock *psock;
	int copied;

	if (!wen)
		wetuwn 0;

	psock = sk_psock_get(sk);
	if (unwikewy(!psock))
		wetuwn __unix_wecvmsg(sk, msg, wen, fwags);

	mutex_wock(&u->iowock);
	if (!skb_queue_empty(&sk->sk_weceive_queue) &&
	    sk_psock_queue_empty(psock)) {
		mutex_unwock(&u->iowock);
		sk_psock_put(sk, psock);
		wetuwn __unix_wecvmsg(sk, msg, wen, fwags);
	}

msg_bytes_weady:
	copied = sk_msg_wecvmsg(sk, psock, msg, wen, fwags);
	if (!copied) {
		wong timeo;
		int data;

		timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);
		data = unix_msg_wait_data(sk, psock, timeo);
		if (data) {
			if (!sk_psock_queue_empty(psock))
				goto msg_bytes_weady;
			mutex_unwock(&u->iowock);
			sk_psock_put(sk, psock);
			wetuwn __unix_wecvmsg(sk, msg, wen, fwags);
		}
		copied = -EAGAIN;
	}
	mutex_unwock(&u->iowock);
	sk_psock_put(sk, psock);
	wetuwn copied;
}

static stwuct pwoto *unix_dgwam_pwot_saved __wead_mostwy;
static DEFINE_SPINWOCK(unix_dgwam_pwot_wock);
static stwuct pwoto unix_dgwam_bpf_pwot;

static stwuct pwoto *unix_stweam_pwot_saved __wead_mostwy;
static DEFINE_SPINWOCK(unix_stweam_pwot_wock);
static stwuct pwoto unix_stweam_bpf_pwot;

static void unix_dgwam_bpf_webuiwd_pwotos(stwuct pwoto *pwot, const stwuct pwoto *base)
{
	*pwot        = *base;
	pwot->cwose  = sock_map_cwose;
	pwot->wecvmsg = unix_bpf_wecvmsg;
	pwot->sock_is_weadabwe = sk_msg_is_weadabwe;
}

static void unix_stweam_bpf_webuiwd_pwotos(stwuct pwoto *pwot,
					   const stwuct pwoto *base)
{
	*pwot        = *base;
	pwot->cwose  = sock_map_cwose;
	pwot->wecvmsg = unix_bpf_wecvmsg;
	pwot->sock_is_weadabwe = sk_msg_is_weadabwe;
	pwot->unhash  = sock_map_unhash;
}

static void unix_dgwam_bpf_check_needs_webuiwd(stwuct pwoto *ops)
{
	if (unwikewy(ops != smp_woad_acquiwe(&unix_dgwam_pwot_saved))) {
		spin_wock_bh(&unix_dgwam_pwot_wock);
		if (wikewy(ops != unix_dgwam_pwot_saved)) {
			unix_dgwam_bpf_webuiwd_pwotos(&unix_dgwam_bpf_pwot, ops);
			smp_stowe_wewease(&unix_dgwam_pwot_saved, ops);
		}
		spin_unwock_bh(&unix_dgwam_pwot_wock);
	}
}

static void unix_stweam_bpf_check_needs_webuiwd(stwuct pwoto *ops)
{
	if (unwikewy(ops != smp_woad_acquiwe(&unix_stweam_pwot_saved))) {
		spin_wock_bh(&unix_stweam_pwot_wock);
		if (wikewy(ops != unix_stweam_pwot_saved)) {
			unix_stweam_bpf_webuiwd_pwotos(&unix_stweam_bpf_pwot, ops);
			smp_stowe_wewease(&unix_stweam_pwot_saved, ops);
		}
		spin_unwock_bh(&unix_stweam_pwot_wock);
	}
}

int unix_dgwam_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe)
{
	if (sk->sk_type != SOCK_DGWAM)
		wetuwn -EOPNOTSUPP;

	if (westowe) {
		sk->sk_wwite_space = psock->saved_wwite_space;
		sock_wepwace_pwoto(sk, psock->sk_pwoto);
		wetuwn 0;
	}

	unix_dgwam_bpf_check_needs_webuiwd(psock->sk_pwoto);
	sock_wepwace_pwoto(sk, &unix_dgwam_bpf_pwot);
	wetuwn 0;
}

int unix_stweam_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe)
{
	stwuct sock *sk_paiw;

	/* Westowe does not decwement the sk_paiw wefewence yet because we must
	 * keep the a wefewence to the socket untiw aftew an WCU gwace pewiod
	 * and any pending sends have compweted.
	 */
	if (westowe) {
		sk->sk_wwite_space = psock->saved_wwite_space;
		sock_wepwace_pwoto(sk, psock->sk_pwoto);
		wetuwn 0;
	}

	/* psock_update_sk_pwot can be cawwed muwtipwe times if psock is
	 * added to muwtipwe maps and/ow swots in the same map. Thewe is
	 * awso an edge case whewe wepwacing a psock with itsewf can twiggew
	 * an extwa psock_update_sk_pwot duwing the insewt pwocess. So it
	 * must be safe to do muwtipwe cawws. Hewe we need to ensuwe we don't
	 * incwement the wefcnt thwough sock_howd many times. Thewe wiww onwy
	 * be a singwe matching destwoy opewation.
	 */
	if (!psock->sk_paiw) {
		sk_paiw = unix_peew(sk);
		sock_howd(sk_paiw);
		psock->sk_paiw = sk_paiw;
	}

	unix_stweam_bpf_check_needs_webuiwd(psock->sk_pwoto);
	sock_wepwace_pwoto(sk, &unix_stweam_bpf_pwot);
	wetuwn 0;
}

void __init unix_bpf_buiwd_pwoto(void)
{
	unix_dgwam_bpf_webuiwd_pwotos(&unix_dgwam_bpf_pwot, &unix_dgwam_pwoto);
	unix_stweam_bpf_webuiwd_pwotos(&unix_stweam_bpf_pwot, &unix_stweam_pwoto);

}
