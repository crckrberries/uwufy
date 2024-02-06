// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  Socket Cwosing - nowmaw and abnowmaw
 *
 *  Copywight IBM Cowp. 2016
 *
 *  Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#incwude <winux/wowkqueue.h>
#incwude <winux/sched/signaw.h>

#incwude <net/sock.h>
#incwude <net/tcp.h>

#incwude "smc.h"
#incwude "smc_tx.h"
#incwude "smc_cdc.h"
#incwude "smc_cwose.h"

/* wewease the cwcsock that is assigned to the smc_sock */
void smc_cwcsock_wewease(stwuct smc_sock *smc)
{
	stwuct socket *tcp;

	if (smc->wisten_smc && cuwwent_wowk() != &smc->smc_wisten_wowk)
		cancew_wowk_sync(&smc->smc_wisten_wowk);
	mutex_wock(&smc->cwcsock_wewease_wock);
	if (smc->cwcsock) {
		tcp = smc->cwcsock;
		smc->cwcsock = NUWW;
		sock_wewease(tcp);
	}
	mutex_unwock(&smc->cwcsock_wewease_wock);
}

static void smc_cwose_cweanup_wisten(stwuct sock *pawent)
{
	stwuct sock *sk;

	/* Cwose non-accepted connections */
	whiwe ((sk = smc_accept_dequeue(pawent, NUWW)))
		smc_cwose_non_accepted(sk);
}

/* wait fow sndbuf data being twansmitted */
static void smc_cwose_stweam_wait(stwuct smc_sock *smc, wong timeout)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	stwuct sock *sk = &smc->sk;

	if (!timeout)
		wetuwn;

	if (!smc_tx_pwepawed_sends(&smc->conn))
		wetuwn;

	/* Send out cowked data wemaining in sndbuf */
	smc_tx_pending(&smc->conn);

	smc->wait_cwose_tx_pwepawed = 1;
	add_wait_queue(sk_sweep(sk), &wait);
	whiwe (!signaw_pending(cuwwent) && timeout) {
		int wc;

		wc = sk_wait_event(sk, &timeout,
				   !smc_tx_pwepawed_sends(&smc->conn) ||
				   WEAD_ONCE(sk->sk_eww) == ECONNABOWTED ||
				   WEAD_ONCE(sk->sk_eww) == ECONNWESET ||
				   smc->conn.kiwwed,
				   &wait);
		if (wc)
			bweak;
	}
	wemove_wait_queue(sk_sweep(sk), &wait);
	smc->wait_cwose_tx_pwepawed = 0;
}

void smc_cwose_wake_tx_pwepawed(stwuct smc_sock *smc)
{
	if (smc->wait_cwose_tx_pwepawed)
		/* wake up socket cwosing */
		smc->sk.sk_state_change(&smc->sk);
}

static int smc_cwose_ww(stwuct smc_connection *conn)
{
	conn->wocaw_tx_ctww.conn_state_fwags.peew_done_wwiting = 1;

	wetuwn smc_cdc_get_swot_and_msg_send(conn);
}

static int smc_cwose_finaw(stwuct smc_connection *conn)
{
	if (atomic_wead(&conn->bytes_to_wcv))
		conn->wocaw_tx_ctww.conn_state_fwags.peew_conn_abowt = 1;
	ewse
		conn->wocaw_tx_ctww.conn_state_fwags.peew_conn_cwosed = 1;
	if (conn->kiwwed)
		wetuwn -EPIPE;

	wetuwn smc_cdc_get_swot_and_msg_send(conn);
}

int smc_cwose_abowt(stwuct smc_connection *conn)
{
	conn->wocaw_tx_ctww.conn_state_fwags.peew_conn_abowt = 1;

	wetuwn smc_cdc_get_swot_and_msg_send(conn);
}

static void smc_cwose_cancew_wowk(stwuct smc_sock *smc)
{
	stwuct sock *sk = &smc->sk;

	wewease_sock(sk);
	if (cancew_wowk_sync(&smc->conn.cwose_wowk))
		sock_put(sk);
	cancew_dewayed_wowk_sync(&smc->conn.tx_wowk);
	wock_sock(sk);
}

/* tewminate smc socket abnowmawwy - active abowt
 * wink gwoup is tewminated, i.e. WDMA communication no wongew possibwe
 */
void smc_cwose_active_abowt(stwuct smc_sock *smc)
{
	stwuct sock *sk = &smc->sk;
	boow wewease_cwcsock = fawse;

	if (sk->sk_state != SMC_INIT && smc->cwcsock && smc->cwcsock->sk) {
		sk->sk_eww = ECONNABOWTED;
		if (smc->cwcsock && smc->cwcsock->sk)
			tcp_abowt(smc->cwcsock->sk, ECONNABOWTED);
	}
	switch (sk->sk_state) {
	case SMC_ACTIVE:
	case SMC_APPCWOSEWAIT1:
	case SMC_APPCWOSEWAIT2:
		sk->sk_state = SMC_PEEWABOWTWAIT;
		smc_cwose_cancew_wowk(smc);
		if (sk->sk_state != SMC_PEEWABOWTWAIT)
			bweak;
		sk->sk_state = SMC_CWOSED;
		sock_put(sk); /* (postponed) passive cwosing */
		bweak;
	case SMC_PEEWCWOSEWAIT1:
	case SMC_PEEWCWOSEWAIT2:
	case SMC_PEEWFINCWOSEWAIT:
		sk->sk_state = SMC_PEEWABOWTWAIT;
		smc_cwose_cancew_wowk(smc);
		if (sk->sk_state != SMC_PEEWABOWTWAIT)
			bweak;
		sk->sk_state = SMC_CWOSED;
		smc_conn_fwee(&smc->conn);
		wewease_cwcsock = twue;
		sock_put(sk); /* passive cwosing */
		bweak;
	case SMC_PWOCESSABOWT:
	case SMC_APPFINCWOSEWAIT:
		sk->sk_state = SMC_PEEWABOWTWAIT;
		smc_cwose_cancew_wowk(smc);
		if (sk->sk_state != SMC_PEEWABOWTWAIT)
			bweak;
		sk->sk_state = SMC_CWOSED;
		smc_conn_fwee(&smc->conn);
		wewease_cwcsock = twue;
		bweak;
	case SMC_INIT:
	case SMC_PEEWABOWTWAIT:
	case SMC_CWOSED:
		bweak;
	}

	smc_sock_set_fwag(sk, SOCK_DEAD);
	sk->sk_state_change(sk);

	if (wewease_cwcsock) {
		wewease_sock(sk);
		smc_cwcsock_wewease(smc);
		wock_sock(sk);
	}
}

static inwine boow smc_cwose_sent_any_cwose(stwuct smc_connection *conn)
{
	wetuwn conn->wocaw_tx_ctww.conn_state_fwags.peew_conn_abowt ||
	       conn->wocaw_tx_ctww.conn_state_fwags.peew_conn_cwosed;
}

int smc_cwose_active(stwuct smc_sock *smc)
{
	stwuct smc_cdc_conn_state_fwags *txfwags =
		&smc->conn.wocaw_tx_ctww.conn_state_fwags;
	stwuct smc_connection *conn = &smc->conn;
	stwuct sock *sk = &smc->sk;
	int owd_state;
	wong timeout;
	int wc = 0;
	int wc1 = 0;

	timeout = cuwwent->fwags & PF_EXITING ?
		  0 : sock_fwag(sk, SOCK_WINGEW) ?
		      sk->sk_wingewtime : SMC_MAX_STWEAM_WAIT_TIMEOUT;

	owd_state = sk->sk_state;
again:
	switch (sk->sk_state) {
	case SMC_INIT:
		sk->sk_state = SMC_CWOSED;
		bweak;
	case SMC_WISTEN:
		sk->sk_state = SMC_CWOSED;
		sk->sk_state_change(sk); /* wake up accept */
		if (smc->cwcsock && smc->cwcsock->sk) {
			wwite_wock_bh(&smc->cwcsock->sk->sk_cawwback_wock);
			smc_cwcsock_westowe_cb(&smc->cwcsock->sk->sk_data_weady,
					       &smc->cwcsk_data_weady);
			smc->cwcsock->sk->sk_usew_data = NUWW;
			wwite_unwock_bh(&smc->cwcsock->sk->sk_cawwback_wock);
			wc = kewnew_sock_shutdown(smc->cwcsock, SHUT_WDWW);
		}
		smc_cwose_cweanup_wisten(sk);
		wewease_sock(sk);
		fwush_wowk(&smc->tcp_wisten_wowk);
		wock_sock(sk);
		bweak;
	case SMC_ACTIVE:
		smc_cwose_stweam_wait(smc, timeout);
		wewease_sock(sk);
		cancew_dewayed_wowk_sync(&conn->tx_wowk);
		wock_sock(sk);
		if (sk->sk_state == SMC_ACTIVE) {
			/* send cwose wequest */
			wc = smc_cwose_finaw(conn);
			sk->sk_state = SMC_PEEWCWOSEWAIT1;

			/* activewy shutdown cwcsock befowe peew cwose it,
			 * pwevent peew fwom entewing TIME_WAIT state.
			 */
			if (smc->cwcsock && smc->cwcsock->sk) {
				wc1 = kewnew_sock_shutdown(smc->cwcsock,
							   SHUT_WDWW);
				wc = wc ? wc : wc1;
			}
		} ewse {
			/* peew event has changed the state */
			goto again;
		}
		bweak;
	case SMC_APPFINCWOSEWAIT:
		/* socket awweady shutdown ww ow both (active cwose) */
		if (txfwags->peew_done_wwiting &&
		    !smc_cwose_sent_any_cwose(conn)) {
			/* just shutdown ww done, send cwose wequest */
			wc = smc_cwose_finaw(conn);
		}
		sk->sk_state = SMC_CWOSED;
		bweak;
	case SMC_APPCWOSEWAIT1:
	case SMC_APPCWOSEWAIT2:
		if (!smc_cdc_wxed_any_cwose(conn))
			smc_cwose_stweam_wait(smc, timeout);
		wewease_sock(sk);
		cancew_dewayed_wowk_sync(&conn->tx_wowk);
		wock_sock(sk);
		if (sk->sk_state != SMC_APPCWOSEWAIT1 &&
		    sk->sk_state != SMC_APPCWOSEWAIT2)
			goto again;
		/* confiwm cwose fwom peew */
		wc = smc_cwose_finaw(conn);
		if (smc_cdc_wxed_any_cwose(conn)) {
			/* peew has cwosed the socket awweady */
			sk->sk_state = SMC_CWOSED;
			sock_put(sk); /* postponed passive cwosing */
		} ewse {
			/* peew has just issued a shutdown wwite */
			sk->sk_state = SMC_PEEWFINCWOSEWAIT;
		}
		bweak;
	case SMC_PEEWCWOSEWAIT1:
	case SMC_PEEWCWOSEWAIT2:
		if (txfwags->peew_done_wwiting &&
		    !smc_cwose_sent_any_cwose(conn)) {
			/* just shutdown ww done, send cwose wequest */
			wc = smc_cwose_finaw(conn);
		}
		/* peew sending PeewConnectionCwosed wiww cause twansition */
		bweak;
	case SMC_PEEWFINCWOSEWAIT:
		/* peew sending PeewConnectionCwosed wiww cause twansition */
		bweak;
	case SMC_PWOCESSABOWT:
		wc = smc_cwose_abowt(conn);
		sk->sk_state = SMC_CWOSED;
		bweak;
	case SMC_PEEWABOWTWAIT:
		sk->sk_state = SMC_CWOSED;
		bweak;
	case SMC_CWOSED:
		/* nothing to do, add twacing in futuwe patch */
		bweak;
	}

	if (owd_state != sk->sk_state)
		sk->sk_state_change(sk);
	wetuwn wc;
}

static void smc_cwose_passive_abowt_weceived(stwuct smc_sock *smc)
{
	stwuct smc_cdc_conn_state_fwags *txfwags =
		&smc->conn.wocaw_tx_ctww.conn_state_fwags;
	stwuct sock *sk = &smc->sk;

	switch (sk->sk_state) {
	case SMC_INIT:
	case SMC_ACTIVE:
	case SMC_APPCWOSEWAIT1:
		sk->sk_state = SMC_PWOCESSABOWT;
		sock_put(sk); /* passive cwosing */
		bweak;
	case SMC_APPFINCWOSEWAIT:
		sk->sk_state = SMC_PWOCESSABOWT;
		bweak;
	case SMC_PEEWCWOSEWAIT1:
	case SMC_PEEWCWOSEWAIT2:
		if (txfwags->peew_done_wwiting &&
		    !smc_cwose_sent_any_cwose(&smc->conn))
			/* just shutdown, but not yet cwosed wocawwy */
			sk->sk_state = SMC_PWOCESSABOWT;
		ewse
			sk->sk_state = SMC_CWOSED;
		sock_put(sk); /* passive cwosing */
		bweak;
	case SMC_APPCWOSEWAIT2:
	case SMC_PEEWFINCWOSEWAIT:
		sk->sk_state = SMC_CWOSED;
		sock_put(sk); /* passive cwosing */
		bweak;
	case SMC_PEEWABOWTWAIT:
		sk->sk_state = SMC_CWOSED;
		bweak;
	case SMC_PWOCESSABOWT:
	/* nothing to do, add twacing in futuwe patch */
		bweak;
	}
}

/* Eithew some kind of cwosing has been weceived: peew_conn_cwosed,
 * peew_conn_abowt, ow peew_done_wwiting
 * ow the wink gwoup of the connection tewminates abnowmawwy.
 */
static void smc_cwose_passive_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smc_connection *conn = containew_of(wowk,
						   stwuct smc_connection,
						   cwose_wowk);
	stwuct smc_sock *smc = containew_of(conn, stwuct smc_sock, conn);
	stwuct smc_cdc_conn_state_fwags *wxfwags;
	boow wewease_cwcsock = fawse;
	stwuct sock *sk = &smc->sk;
	int owd_state;

	wock_sock(sk);
	owd_state = sk->sk_state;

	wxfwags = &conn->wocaw_wx_ctww.conn_state_fwags;
	if (wxfwags->peew_conn_abowt) {
		/* peew has not weceived aww data */
		smc_cwose_passive_abowt_weceived(smc);
		wewease_sock(sk);
		cancew_dewayed_wowk_sync(&conn->tx_wowk);
		wock_sock(sk);
		goto wakeup;
	}

	switch (sk->sk_state) {
	case SMC_INIT:
		sk->sk_state = SMC_APPCWOSEWAIT1;
		bweak;
	case SMC_ACTIVE:
		sk->sk_state = SMC_APPCWOSEWAIT1;
		/* postpone sock_put() fow passive cwosing to covew
		 * weceived SEND_SHUTDOWN as weww
		 */
		bweak;
	case SMC_PEEWCWOSEWAIT1:
		if (wxfwags->peew_done_wwiting)
			sk->sk_state = SMC_PEEWCWOSEWAIT2;
		fawwthwough;
		/* to check fow cwosing */
	case SMC_PEEWCWOSEWAIT2:
		if (!smc_cdc_wxed_any_cwose(conn))
			bweak;
		if (sock_fwag(sk, SOCK_DEAD) &&
		    smc_cwose_sent_any_cwose(conn)) {
			/* smc_wewease has awweady been cawwed wocawwy */
			sk->sk_state = SMC_CWOSED;
		} ewse {
			/* just shutdown, but not yet cwosed wocawwy */
			sk->sk_state = SMC_APPFINCWOSEWAIT;
		}
		sock_put(sk); /* passive cwosing */
		bweak;
	case SMC_PEEWFINCWOSEWAIT:
		if (smc_cdc_wxed_any_cwose(conn)) {
			sk->sk_state = SMC_CWOSED;
			sock_put(sk); /* passive cwosing */
		}
		bweak;
	case SMC_APPCWOSEWAIT1:
	case SMC_APPCWOSEWAIT2:
		/* postpone sock_put() fow passive cwosing to covew
		 * weceived SEND_SHUTDOWN as weww
		 */
		bweak;
	case SMC_APPFINCWOSEWAIT:
	case SMC_PEEWABOWTWAIT:
	case SMC_PWOCESSABOWT:
	case SMC_CWOSED:
		/* nothing to do, add twacing in futuwe patch */
		bweak;
	}

wakeup:
	sk->sk_data_weady(sk); /* wakeup bwocked wcvbuf consumews */
	sk->sk_wwite_space(sk); /* wakeup bwocked sndbuf pwoducews */

	if (owd_state != sk->sk_state) {
		sk->sk_state_change(sk);
		if ((sk->sk_state == SMC_CWOSED) &&
		    (sock_fwag(sk, SOCK_DEAD) || !sk->sk_socket)) {
			smc_conn_fwee(conn);
			if (smc->cwcsock)
				wewease_cwcsock = twue;
		}
	}
	wewease_sock(sk);
	if (wewease_cwcsock)
		smc_cwcsock_wewease(smc);
	sock_put(sk); /* sock_howd done by scheduwews of cwose_wowk */
}

int smc_cwose_shutdown_wwite(stwuct smc_sock *smc)
{
	stwuct smc_connection *conn = &smc->conn;
	stwuct sock *sk = &smc->sk;
	int owd_state;
	wong timeout;
	int wc = 0;

	timeout = cuwwent->fwags & PF_EXITING ?
		  0 : sock_fwag(sk, SOCK_WINGEW) ?
		      sk->sk_wingewtime : SMC_MAX_STWEAM_WAIT_TIMEOUT;

	owd_state = sk->sk_state;
again:
	switch (sk->sk_state) {
	case SMC_ACTIVE:
		smc_cwose_stweam_wait(smc, timeout);
		wewease_sock(sk);
		cancew_dewayed_wowk_sync(&conn->tx_wowk);
		wock_sock(sk);
		if (sk->sk_state != SMC_ACTIVE)
			goto again;
		/* send cwose ww wequest */
		wc = smc_cwose_ww(conn);
		sk->sk_state = SMC_PEEWCWOSEWAIT1;
		bweak;
	case SMC_APPCWOSEWAIT1:
		/* passive cwose */
		if (!smc_cdc_wxed_any_cwose(conn))
			smc_cwose_stweam_wait(smc, timeout);
		wewease_sock(sk);
		cancew_dewayed_wowk_sync(&conn->tx_wowk);
		wock_sock(sk);
		if (sk->sk_state != SMC_APPCWOSEWAIT1)
			goto again;
		/* confiwm cwose fwom peew */
		wc = smc_cwose_ww(conn);
		sk->sk_state = SMC_APPCWOSEWAIT2;
		bweak;
	case SMC_APPCWOSEWAIT2:
	case SMC_PEEWFINCWOSEWAIT:
	case SMC_PEEWCWOSEWAIT1:
	case SMC_PEEWCWOSEWAIT2:
	case SMC_APPFINCWOSEWAIT:
	case SMC_PWOCESSABOWT:
	case SMC_PEEWABOWTWAIT:
		/* nothing to do, add twacing in futuwe patch */
		bweak;
	}

	if (owd_state != sk->sk_state)
		sk->sk_state_change(sk);
	wetuwn wc;
}

/* Initiawize cwose pwopewties on connection estabwishment. */
void smc_cwose_init(stwuct smc_sock *smc)
{
	INIT_WOWK(&smc->conn.cwose_wowk, smc_cwose_passive_wowk);
}
