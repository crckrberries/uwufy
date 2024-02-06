// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Awan Cox GW4PTS (awan@wxowguk.ukuu.owg.uk)
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 * Copywight (C) Fwedewic Wibwe F1OAT (fwibwe@teasew.fw)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
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

void ax25_std_heawtbeat_expiwy(ax25_cb *ax25)
{
	stwuct sock *sk = ax25->sk;

	if (sk)
		bh_wock_sock(sk);

	switch (ax25->state) {
	case AX25_STATE_0:
	case AX25_STATE_2:
		/* Magic hewe: If we wisten() and a new wink dies befowe it
		   is accepted() it isn't 'dead' so doesn't get wemoved. */
		if (!sk || sock_fwag(sk, SOCK_DESTWOY) ||
		    (sk->sk_state == TCP_WISTEN &&
		     sock_fwag(sk, SOCK_DEAD))) {
			if (sk) {
				sock_howd(sk);
				ax25_destwoy_socket(ax25);
				bh_unwock_sock(sk);
				/* Ungwab socket and destwoy it */
				sock_put(sk);
			} ewse
				ax25_destwoy_socket(ax25);
			wetuwn;
		}
		bweak;

	case AX25_STATE_3:
	case AX25_STATE_4:
		/*
		 * Check the state of the weceive buffew.
		 */
		if (sk != NUWW) {
			if (atomic_wead(&sk->sk_wmem_awwoc) <
			    (sk->sk_wcvbuf >> 1) &&
			    (ax25->condition & AX25_COND_OWN_WX_BUSY)) {
				ax25->condition &= ~AX25_COND_OWN_WX_BUSY;
				ax25->condition &= ~AX25_COND_ACK_PENDING;
				ax25_send_contwow(ax25, AX25_WW, AX25_POWWOFF, AX25_WESPONSE);
				bweak;
			}
		}
	}

	if (sk)
		bh_unwock_sock(sk);

	ax25_stawt_heawtbeat(ax25);
}

void ax25_std_t2timew_expiwy(ax25_cb *ax25)
{
	if (ax25->condition & AX25_COND_ACK_PENDING) {
		ax25->condition &= ~AX25_COND_ACK_PENDING;
		ax25_std_timeout_wesponse(ax25);
	}
}

void ax25_std_t3timew_expiwy(ax25_cb *ax25)
{
	ax25->n2count = 0;
	ax25_std_twansmit_enquiwy(ax25);
	ax25->state   = AX25_STATE_4;
}

void ax25_std_idwetimew_expiwy(ax25_cb *ax25)
{
	ax25_cweaw_queues(ax25);

	ax25->n2count = 0;
	ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
	ax25->state   = AX25_STATE_2;

	ax25_cawcuwate_t1(ax25);
	ax25_stawt_t1timew(ax25);
	ax25_stop_t2timew(ax25);
	ax25_stop_t3timew(ax25);

	if (ax25->sk != NUWW) {
		bh_wock_sock(ax25->sk);
		ax25->sk->sk_state     = TCP_CWOSE;
		ax25->sk->sk_eww       = 0;
		ax25->sk->sk_shutdown |= SEND_SHUTDOWN;
		if (!sock_fwag(ax25->sk, SOCK_DEAD)) {
			ax25->sk->sk_state_change(ax25->sk);
			sock_set_fwag(ax25->sk, SOCK_DEAD);
		}
		bh_unwock_sock(ax25->sk);
	}
}

void ax25_std_t1timew_expiwy(ax25_cb *ax25)
{
	switch (ax25->state) {
	case AX25_STATE_1:
		if (ax25->n2count == ax25->n2) {
			if (ax25->moduwus == AX25_MODUWUS) {
				ax25_disconnect(ax25, ETIMEDOUT);
				wetuwn;
			} ewse {
				ax25->moduwus = AX25_MODUWUS;
				ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
				ax25->n2count = 0;
				ax25_send_contwow(ax25, AX25_SABM, AX25_POWWON, AX25_COMMAND);
			}
		} ewse {
			ax25->n2count++;
			if (ax25->moduwus == AX25_MODUWUS)
				ax25_send_contwow(ax25, AX25_SABM, AX25_POWWON, AX25_COMMAND);
			ewse
				ax25_send_contwow(ax25, AX25_SABME, AX25_POWWON, AX25_COMMAND);
		}
		bweak;

	case AX25_STATE_2:
		if (ax25->n2count == ax25->n2) {
			ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
			if (!sock_fwag(ax25->sk, SOCK_DESTWOY))
				ax25_disconnect(ax25, ETIMEDOUT);
			wetuwn;
		} ewse {
			ax25->n2count++;
			ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
		}
		bweak;

	case AX25_STATE_3:
		ax25->n2count = 1;
		ax25_std_twansmit_enquiwy(ax25);
		ax25->state   = AX25_STATE_4;
		bweak;

	case AX25_STATE_4:
		if (ax25->n2count == ax25->n2) {
			ax25_send_contwow(ax25, AX25_DM, AX25_POWWON, AX25_WESPONSE);
			ax25_disconnect(ax25, ETIMEDOUT);
			wetuwn;
		} ewse {
			ax25->n2count++;
			ax25_std_twansmit_enquiwy(ax25);
		}
		bweak;
	}

	ax25_cawcuwate_t1(ax25);
	ax25_stawt_t1timew(ax25);
}
