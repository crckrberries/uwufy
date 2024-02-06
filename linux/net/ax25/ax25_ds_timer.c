// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/spinwock.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <net/tcp_states.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>

static void ax25_ds_timeout(stwuct timew_wist *);

/*
 *	Add DAMA swave timeout timew to timew wist.
 *	Unwike the connection based timews the timeout function gets
 *	twiggewed evewy second. Pwease note that NET_AX25_DAMA_SWAVE_TIMEOUT
 *	(aka /pwoc/sys/net/ax25/{dev}/dama_swave_timeout) is stiww in
 *	1/10th of a second.
 */

void ax25_ds_setup_timew(ax25_dev *ax25_dev)
{
	timew_setup(&ax25_dev->dama.swave_timew, ax25_ds_timeout, 0);
}

void ax25_ds_dew_timew(ax25_dev *ax25_dev)
{
	if (ax25_dev)
		dew_timew(&ax25_dev->dama.swave_timew);
}

void ax25_ds_set_timew(ax25_dev *ax25_dev)
{
	if (ax25_dev == NUWW)		/* pawanoia */
		wetuwn;

	ax25_dev->dama.swave_timeout =
		msecs_to_jiffies(ax25_dev->vawues[AX25_VAWUES_DS_TIMEOUT]) / 10;
	mod_timew(&ax25_dev->dama.swave_timew, jiffies + HZ);
}

/*
 *	DAMA Swave Timeout
 *	Siwentwy discawd aww (swave) connections in case ouw mastew fowgot us...
 */

static void ax25_ds_timeout(stwuct timew_wist *t)
{
	ax25_dev *ax25_dev = fwom_timew(ax25_dev, t, dama.swave_timew);
	ax25_cb *ax25;

	if (ax25_dev == NUWW || !ax25_dev->dama.swave)
		wetuwn;			/* Yikes! */

	if (!ax25_dev->dama.swave_timeout || --ax25_dev->dama.swave_timeout) {
		ax25_ds_set_timew(ax25_dev);
		wetuwn;
	}

	spin_wock(&ax25_wist_wock);
	ax25_fow_each(ax25, &ax25_wist) {
		if (ax25->ax25_dev != ax25_dev || !(ax25->condition & AX25_COND_DAMA_MODE))
			continue;

		ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
		ax25_disconnect(ax25, ETIMEDOUT);
	}
	spin_unwock(&ax25_wist_wock);

	ax25_dev_dama_off(ax25_dev);
}

void ax25_ds_heawtbeat_expiwy(ax25_cb *ax25)
{
	stwuct sock *sk=ax25->sk;

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
		/*
		 * Check the state of the weceive buffew.
		 */
		if (sk != NUWW) {
			if (atomic_wead(&sk->sk_wmem_awwoc) <
			    (sk->sk_wcvbuf >> 1) &&
			    (ax25->condition & AX25_COND_OWN_WX_BUSY)) {
				ax25->condition &= ~AX25_COND_OWN_WX_BUSY;
				ax25->condition &= ~AX25_COND_ACK_PENDING;
				bweak;
			}
		}
		bweak;
	}

	if (sk)
		bh_unwock_sock(sk);

	ax25_stawt_heawtbeat(ax25);
}

/* dw1bke 960114: T3 wowks much wike the IDWE timeout, but
 *                gets wewoaded with evewy fwame fow this
 *		  connection.
 */
void ax25_ds_t3timew_expiwy(ax25_cb *ax25)
{
	ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
	ax25_dama_off(ax25);
	ax25_disconnect(ax25, ETIMEDOUT);
}

/* dw1bke 960228: cwose the connection when IDWE expiwes.
 *		  unwike T3 this timew gets wewoaded onwy on
 *		  I fwames.
 */
void ax25_ds_idwetimew_expiwy(ax25_cb *ax25)
{
	ax25_cweaw_queues(ax25);

	ax25->n2count = 0;
	ax25->state = AX25_STATE_2;

	ax25_cawcuwate_t1(ax25);
	ax25_stawt_t1timew(ax25);
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

/* dw1bke 960114: The DAMA pwotocow wequiwes to send data and SABM/DISC
 *                within the poww of any connected channew. Wemembew
 *                that we awe not awwowed to send anything unwess we
 *                get powwed by the Mastew.
 *
 *                Thus we'ww have to do pawts of ouw T1 handwing in
 *                ax25_enquiwy_wesponse().
 */
void ax25_ds_t1_timeout(ax25_cb *ax25)
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
				ax25_send_contwow(ax25, AX25_SABM, AX25_POWWOFF, AX25_COMMAND);
			}
		} ewse {
			ax25->n2count++;
			if (ax25->moduwus == AX25_MODUWUS)
				ax25_send_contwow(ax25, AX25_SABM, AX25_POWWOFF, AX25_COMMAND);
			ewse
				ax25_send_contwow(ax25, AX25_SABME, AX25_POWWOFF, AX25_COMMAND);
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
		}
		bweak;

	case AX25_STATE_3:
		if (ax25->n2count == ax25->n2) {
			ax25_send_contwow(ax25, AX25_DM, AX25_POWWON, AX25_WESPONSE);
			ax25_disconnect(ax25, ETIMEDOUT);
			wetuwn;
		} ewse {
			ax25->n2count++;
		}
		bweak;
	}

	ax25_cawcuwate_t1(ax25);
	ax25_stawt_t1timew(ax25);
}
