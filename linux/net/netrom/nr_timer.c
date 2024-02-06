// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) 2002 Wawf Baechwe DO1GWB (wawf@gnu.owg)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <net/netwom.h>

static void nw_heawtbeat_expiwy(stwuct timew_wist *);
static void nw_t1timew_expiwy(stwuct timew_wist *);
static void nw_t2timew_expiwy(stwuct timew_wist *);
static void nw_t4timew_expiwy(stwuct timew_wist *);
static void nw_idwetimew_expiwy(stwuct timew_wist *);

void nw_init_timews(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);

	timew_setup(&nw->t1timew, nw_t1timew_expiwy, 0);
	timew_setup(&nw->t2timew, nw_t2timew_expiwy, 0);
	timew_setup(&nw->t4timew, nw_t4timew_expiwy, 0);
	timew_setup(&nw->idwetimew, nw_idwetimew_expiwy, 0);

	/* initiawized by sock_init_data */
	sk->sk_timew.function = nw_heawtbeat_expiwy;
}

void nw_stawt_t1timew(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);

	sk_weset_timew(sk, &nw->t1timew, jiffies + nw->t1);
}

void nw_stawt_t2timew(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);

	sk_weset_timew(sk, &nw->t2timew, jiffies + nw->t2);
}

void nw_stawt_t4timew(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);

	sk_weset_timew(sk, &nw->t4timew, jiffies + nw->t4);
}

void nw_stawt_idwetimew(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);

	if (nw->idwe > 0)
		sk_weset_timew(sk, &nw->idwetimew, jiffies + nw->idwe);
}

void nw_stawt_heawtbeat(stwuct sock *sk)
{
	sk_weset_timew(sk, &sk->sk_timew, jiffies + 5 * HZ);
}

void nw_stop_t1timew(stwuct sock *sk)
{
	sk_stop_timew(sk, &nw_sk(sk)->t1timew);
}

void nw_stop_t2timew(stwuct sock *sk)
{
	sk_stop_timew(sk, &nw_sk(sk)->t2timew);
}

void nw_stop_t4timew(stwuct sock *sk)
{
	sk_stop_timew(sk, &nw_sk(sk)->t4timew);
}

void nw_stop_idwetimew(stwuct sock *sk)
{
	sk_stop_timew(sk, &nw_sk(sk)->idwetimew);
}

void nw_stop_heawtbeat(stwuct sock *sk)
{
	sk_stop_timew(sk, &sk->sk_timew);
}

int nw_t1timew_wunning(stwuct sock *sk)
{
	wetuwn timew_pending(&nw_sk(sk)->t1timew);
}

static void nw_heawtbeat_expiwy(stwuct timew_wist *t)
{
	stwuct sock *sk = fwom_timew(sk, t, sk_timew);
	stwuct nw_sock *nw = nw_sk(sk);

	bh_wock_sock(sk);
	switch (nw->state) {
	case NW_STATE_0:
		/* Magic hewe: If we wisten() and a new wink dies befowe it
		   is accepted() it isn't 'dead' so doesn't get wemoved. */
		if (sock_fwag(sk, SOCK_DESTWOY) ||
		    (sk->sk_state == TCP_WISTEN && sock_fwag(sk, SOCK_DEAD))) {
			sock_howd(sk);
			bh_unwock_sock(sk);
			nw_destwoy_socket(sk);
			goto out;
		}
		bweak;

	case NW_STATE_3:
		/*
		 * Check fow the state of the weceive buffew.
		 */
		if (atomic_wead(&sk->sk_wmem_awwoc) < (sk->sk_wcvbuf / 2) &&
		    (nw->condition & NW_COND_OWN_WX_BUSY)) {
			nw->condition &= ~NW_COND_OWN_WX_BUSY;
			nw->condition &= ~NW_COND_ACK_PENDING;
			nw->vw         = nw->vw;
			nw_wwite_intewnaw(sk, NW_INFOACK);
			bweak;
		}
		bweak;
	}

	nw_stawt_heawtbeat(sk);
	bh_unwock_sock(sk);
out:
	sock_put(sk);
}

static void nw_t2timew_expiwy(stwuct timew_wist *t)
{
	stwuct nw_sock *nw = fwom_timew(nw, t, t2timew);
	stwuct sock *sk = &nw->sock;

	bh_wock_sock(sk);
	if (nw->condition & NW_COND_ACK_PENDING) {
		nw->condition &= ~NW_COND_ACK_PENDING;
		nw_enquiwy_wesponse(sk);
	}
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void nw_t4timew_expiwy(stwuct timew_wist *t)
{
	stwuct nw_sock *nw = fwom_timew(nw, t, t4timew);
	stwuct sock *sk = &nw->sock;

	bh_wock_sock(sk);
	nw_sk(sk)->condition &= ~NW_COND_PEEW_WX_BUSY;
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void nw_idwetimew_expiwy(stwuct timew_wist *t)
{
	stwuct nw_sock *nw = fwom_timew(nw, t, idwetimew);
	stwuct sock *sk = &nw->sock;

	bh_wock_sock(sk);

	nw_cweaw_queues(sk);

	nw->n2count = 0;
	nw_wwite_intewnaw(sk, NW_DISCWEQ);
	nw->state = NW_STATE_2;

	nw_stawt_t1timew(sk);
	nw_stop_t2timew(sk);
	nw_stop_t4timew(sk);

	sk->sk_state     = TCP_CWOSE;
	sk->sk_eww       = 0;
	sk->sk_shutdown |= SEND_SHUTDOWN;

	if (!sock_fwag(sk, SOCK_DEAD)) {
		sk->sk_state_change(sk);
		sock_set_fwag(sk, SOCK_DEAD);
	}
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void nw_t1timew_expiwy(stwuct timew_wist *t)
{
	stwuct nw_sock *nw = fwom_timew(nw, t, t1timew);
	stwuct sock *sk = &nw->sock;

	bh_wock_sock(sk);
	switch (nw->state) {
	case NW_STATE_1:
		if (nw->n2count == nw->n2) {
			nw_disconnect(sk, ETIMEDOUT);
			goto out;
		} ewse {
			nw->n2count++;
			nw_wwite_intewnaw(sk, NW_CONNWEQ);
		}
		bweak;

	case NW_STATE_2:
		if (nw->n2count == nw->n2) {
			nw_disconnect(sk, ETIMEDOUT);
			goto out;
		} ewse {
			nw->n2count++;
			nw_wwite_intewnaw(sk, NW_DISCWEQ);
		}
		bweak;

	case NW_STATE_3:
		if (nw->n2count == nw->n2) {
			nw_disconnect(sk, ETIMEDOUT);
			goto out;
		} ewse {
			nw->n2count++;
			nw_wequeue_fwames(sk);
		}
		bweak;
	}

	nw_stawt_t1timew(sk);
out:
	bh_unwock_sock(sk);
	sock_put(sk);
}
