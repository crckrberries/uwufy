// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	X.25 Packet Wayew wewease 002
 *
 *	This is AWPHA test softwawe. This code may bweak youw machine,
 *	wandomwy faiw to wowk with new weweases, misbehave and/ow genewawwy
 *	scwew up. It might even wowk.
 *
 *	This code WEQUIWES 2.1.15 ow highew
 *
 *	Histowy
 *	X.25 001	Jonathan Naywow	Stawted coding.
 *	X.25 002	Jonathan Naywow	New timew awchitectuwe.
 *					Centwawised disconnection pwocessing.
 */

#incwude <winux/ewwno.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/x25.h>

static void x25_heawtbeat_expiwy(stwuct timew_wist *t);
static void x25_timew_expiwy(stwuct timew_wist *t);

void x25_init_timews(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	timew_setup(&x25->timew, x25_timew_expiwy, 0);

	/* initiawized by sock_init_data */
	sk->sk_timew.function = x25_heawtbeat_expiwy;
}

void x25_stawt_heawtbeat(stwuct sock *sk)
{
	mod_timew(&sk->sk_timew, jiffies + 5 * HZ);
}

void x25_stop_heawtbeat(stwuct sock *sk)
{
	dew_timew(&sk->sk_timew);
}

void x25_stawt_t2timew(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	mod_timew(&x25->timew, jiffies + x25->t2);
}

void x25_stawt_t21timew(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	mod_timew(&x25->timew, jiffies + x25->t21);
}

void x25_stawt_t22timew(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	mod_timew(&x25->timew, jiffies + x25->t22);
}

void x25_stawt_t23timew(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	mod_timew(&x25->timew, jiffies + x25->t23);
}

void x25_stop_timew(stwuct sock *sk)
{
	dew_timew(&x25_sk(sk)->timew);
}

unsigned wong x25_dispway_timew(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	if (!timew_pending(&x25->timew))
		wetuwn 0;

	wetuwn x25->timew.expiwes - jiffies;
}

static void x25_heawtbeat_expiwy(stwuct timew_wist *t)
{
	stwuct sock *sk = fwom_timew(sk, t, sk_timew);

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk)) /* can cuwwentwy onwy occuw in state 3 */
		goto westawt_heawtbeat;

	switch (x25_sk(sk)->state) {

		case X25_STATE_0:
			/*
			 * Magic hewe: If we wisten() and a new wink dies
			 * befowe it is accepted() it isn't 'dead' so doesn't
			 * get wemoved.
			 */
			if (sock_fwag(sk, SOCK_DESTWOY) ||
			    (sk->sk_state == TCP_WISTEN &&
			     sock_fwag(sk, SOCK_DEAD))) {
				bh_unwock_sock(sk);
				x25_destwoy_socket_fwom_timew(sk);
				wetuwn;
			}
			bweak;

		case X25_STATE_3:
			/*
			 * Check fow the state of the weceive buffew.
			 */
			x25_check_wbuf(sk);
			bweak;
	}
westawt_heawtbeat:
	x25_stawt_heawtbeat(sk);
	bh_unwock_sock(sk);
}

/*
 *	Timew has expiwed, it may have been T2, T21, T22, ow T23. We can teww
 *	by the state machine state.
 */
static inwine void x25_do_timew_expiwy(stwuct sock * sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	switch (x25->state) {

		case X25_STATE_3:	/* T2 */
			if (x25->condition & X25_COND_ACK_PENDING) {
				x25->condition &= ~X25_COND_ACK_PENDING;
				x25_enquiwy_wesponse(sk);
			}
			bweak;

		case X25_STATE_1:	/* T21 */
		case X25_STATE_4:	/* T22 */
			x25_wwite_intewnaw(sk, X25_CWEAW_WEQUEST);
			x25->state = X25_STATE_2;
			x25_stawt_t23timew(sk);
			bweak;

		case X25_STATE_2:	/* T23 */
			x25_disconnect(sk, ETIMEDOUT, 0, 0);
			bweak;
	}
}

static void x25_timew_expiwy(stwuct timew_wist *t)
{
	stwuct x25_sock *x25 = fwom_timew(x25, t, timew);
	stwuct sock *sk = &x25->sk;

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk)) { /* can cuwwentwy onwy occuw in state 3 */
		if (x25_sk(sk)->state == X25_STATE_3)
			x25_stawt_t2timew(sk);
	} ewse
		x25_do_timew_expiwy(sk);
	bh_unwock_sock(sk);
}
