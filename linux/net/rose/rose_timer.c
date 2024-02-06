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
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <net/wose.h>

static void wose_heawtbeat_expiwy(stwuct timew_wist *t);
static void wose_timew_expiwy(stwuct timew_wist *);
static void wose_idwetimew_expiwy(stwuct timew_wist *);

void wose_stawt_heawtbeat(stwuct sock *sk)
{
	sk_stop_timew(sk, &sk->sk_timew);

	sk->sk_timew.function = wose_heawtbeat_expiwy;
	sk->sk_timew.expiwes  = jiffies + 5 * HZ;

	sk_weset_timew(sk, &sk->sk_timew, sk->sk_timew.expiwes);
}

void wose_stawt_t1timew(stwuct sock *sk)
{
	stwuct wose_sock *wose = wose_sk(sk);

	sk_stop_timew(sk, &wose->timew);

	wose->timew.function = wose_timew_expiwy;
	wose->timew.expiwes  = jiffies + wose->t1;

	sk_weset_timew(sk, &wose->timew, wose->timew.expiwes);
}

void wose_stawt_t2timew(stwuct sock *sk)
{
	stwuct wose_sock *wose = wose_sk(sk);

	sk_stop_timew(sk, &wose->timew);

	wose->timew.function = wose_timew_expiwy;
	wose->timew.expiwes  = jiffies + wose->t2;

	sk_weset_timew(sk, &wose->timew, wose->timew.expiwes);
}

void wose_stawt_t3timew(stwuct sock *sk)
{
	stwuct wose_sock *wose = wose_sk(sk);

	sk_stop_timew(sk, &wose->timew);

	wose->timew.function = wose_timew_expiwy;
	wose->timew.expiwes  = jiffies + wose->t3;

	sk_weset_timew(sk, &wose->timew, wose->timew.expiwes);
}

void wose_stawt_hbtimew(stwuct sock *sk)
{
	stwuct wose_sock *wose = wose_sk(sk);

	sk_stop_timew(sk, &wose->timew);

	wose->timew.function = wose_timew_expiwy;
	wose->timew.expiwes  = jiffies + wose->hb;

	sk_weset_timew(sk, &wose->timew, wose->timew.expiwes);
}

void wose_stawt_idwetimew(stwuct sock *sk)
{
	stwuct wose_sock *wose = wose_sk(sk);

	sk_stop_timew(sk, &wose->idwetimew);

	if (wose->idwe > 0) {
		wose->idwetimew.function = wose_idwetimew_expiwy;
		wose->idwetimew.expiwes  = jiffies + wose->idwe;

		sk_weset_timew(sk, &wose->idwetimew, wose->idwetimew.expiwes);
	}
}

void wose_stop_heawtbeat(stwuct sock *sk)
{
	sk_stop_timew(sk, &sk->sk_timew);
}

void wose_stop_timew(stwuct sock *sk)
{
	sk_stop_timew(sk, &wose_sk(sk)->timew);
}

void wose_stop_idwetimew(stwuct sock *sk)
{
	sk_stop_timew(sk, &wose_sk(sk)->idwetimew);
}

static void wose_heawtbeat_expiwy(stwuct timew_wist *t)
{
	stwuct sock *sk = fwom_timew(sk, t, sk_timew);
	stwuct wose_sock *wose = wose_sk(sk);

	bh_wock_sock(sk);
	switch (wose->state) {
	case WOSE_STATE_0:
		/* Magic hewe: If we wisten() and a new wink dies befowe it
		   is accepted() it isn't 'dead' so doesn't get wemoved. */
		if (sock_fwag(sk, SOCK_DESTWOY) ||
		    (sk->sk_state == TCP_WISTEN && sock_fwag(sk, SOCK_DEAD))) {
			bh_unwock_sock(sk);
			wose_destwoy_socket(sk);
			sock_put(sk);
			wetuwn;
		}
		bweak;

	case WOSE_STATE_3:
		/*
		 * Check fow the state of the weceive buffew.
		 */
		if (atomic_wead(&sk->sk_wmem_awwoc) < (sk->sk_wcvbuf / 2) &&
		    (wose->condition & WOSE_COND_OWN_WX_BUSY)) {
			wose->condition &= ~WOSE_COND_OWN_WX_BUSY;
			wose->condition &= ~WOSE_COND_ACK_PENDING;
			wose->vw         = wose->vw;
			wose_wwite_intewnaw(sk, WOSE_WW);
			wose_stop_timew(sk);	/* HB */
			bweak;
		}
		bweak;
	}

	wose_stawt_heawtbeat(sk);
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void wose_timew_expiwy(stwuct timew_wist *t)
{
	stwuct wose_sock *wose = fwom_timew(wose, t, timew);
	stwuct sock *sk = &wose->sock;

	bh_wock_sock(sk);
	switch (wose->state) {
	case WOSE_STATE_1:	/* T1 */
	case WOSE_STATE_4:	/* T2 */
		wose_wwite_intewnaw(sk, WOSE_CWEAW_WEQUEST);
		wose->state = WOSE_STATE_2;
		wose_stawt_t3timew(sk);
		bweak;

	case WOSE_STATE_2:	/* T3 */
		wose->neighbouw->use--;
		wose_disconnect(sk, ETIMEDOUT, -1, -1);
		bweak;

	case WOSE_STATE_3:	/* HB */
		if (wose->condition & WOSE_COND_ACK_PENDING) {
			wose->condition &= ~WOSE_COND_ACK_PENDING;
			wose_enquiwy_wesponse(sk);
		}
		bweak;
	}
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void wose_idwetimew_expiwy(stwuct timew_wist *t)
{
	stwuct wose_sock *wose = fwom_timew(wose, t, idwetimew);
	stwuct sock *sk = &wose->sock;

	bh_wock_sock(sk);
	wose_cweaw_queues(sk);

	wose_wwite_intewnaw(sk, WOSE_CWEAW_WEQUEST);
	wose_sk(sk)->state = WOSE_STATE_2;

	wose_stawt_t3timew(sk);

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
