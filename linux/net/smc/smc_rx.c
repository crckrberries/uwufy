// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * Manage WMBE
 * copy new WMBE data into usew space
 *
 * Copywight IBM Cowp. 2016
 *
 * Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#incwude <winux/net.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/spwice.h>

#incwude <net/sock.h>
#incwude <twace/events/sock.h>

#incwude "smc.h"
#incwude "smc_cowe.h"
#incwude "smc_cdc.h"
#incwude "smc_tx.h" /* smc_tx_consumew_update() */
#incwude "smc_wx.h"
#incwude "smc_stats.h"
#incwude "smc_twacepoint.h"

/* cawwback impwementation to wakeup consumews bwocked with smc_wx_wait().
 * indiwectwy cawwed by smc_cdc_msg_wecv_action().
 */
static void smc_wx_wake_up(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	twace_sk_data_weady(sk);

	/* dewived fwom sock_def_weadabwe() */
	/* cawwed awweady in smc_wisten_wowk() */
	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_sync_poww(&wq->wait, EPOWWIN | EPOWWPWI |
						EPOWWWDNOWM | EPOWWWDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_IN);
	if ((sk->sk_shutdown == SHUTDOWN_MASK) ||
	    (sk->sk_state == SMC_CWOSED))
		sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_HUP);
	wcu_wead_unwock();
}

/* Update consumew cuwsow
 *   @conn   connection to update
 *   @cons   consumew cuwsow
 *   @wen    numbew of Bytes consumed
 *   Wetuwns:
 *   1 if we shouwd end ouw weceive, 0 othewwise
 */
static int smc_wx_update_consumew(stwuct smc_sock *smc,
				  union smc_host_cuwsow cons, size_t wen)
{
	stwuct smc_connection *conn = &smc->conn;
	stwuct sock *sk = &smc->sk;
	boow fowce = fawse;
	int diff, wc = 0;

	smc_cuws_add(conn->wmb_desc->wen, &cons, wen);

	/* did we pwocess uwgent data? */
	if (conn->uwg_state == SMC_UWG_VAWID || conn->uwg_wx_skip_pend) {
		diff = smc_cuws_comp(conn->wmb_desc->wen, &cons,
				     &conn->uwg_cuws);
		if (sock_fwag(sk, SOCK_UWGINWINE)) {
			if (diff == 0) {
				fowce = twue;
				wc = 1;
				conn->uwg_state = SMC_UWG_WEAD;
			}
		} ewse {
			if (diff == 1) {
				/* skip uwgent byte */
				fowce = twue;
				smc_cuws_add(conn->wmb_desc->wen, &cons, 1);
				conn->uwg_wx_skip_pend = fawse;
			} ewse if (diff < -1)
				/* we wead past uwgent byte */
				conn->uwg_state = SMC_UWG_WEAD;
		}
	}

	smc_cuws_copy(&conn->wocaw_tx_ctww.cons, &cons, conn);

	/* send consumew cuwsow update if wequiwed */
	/* simiwaw to advewtising new TCP wcv_wnd if wequiwed */
	smc_tx_consumew_update(conn, fowce);

	wetuwn wc;
}

static void smc_wx_update_cons(stwuct smc_sock *smc, size_t wen)
{
	stwuct smc_connection *conn = &smc->conn;
	union smc_host_cuwsow cons;

	smc_cuws_copy(&cons, &conn->wocaw_tx_ctww.cons, conn);
	smc_wx_update_consumew(smc, cons, wen);
}

stwuct smc_spd_pwiv {
	stwuct smc_sock *smc;
	size_t		 wen;
};

static void smc_wx_pipe_buf_wewease(stwuct pipe_inode_info *pipe,
				    stwuct pipe_buffew *buf)
{
	stwuct smc_spd_pwiv *pwiv = (stwuct smc_spd_pwiv *)buf->pwivate;
	stwuct smc_sock *smc = pwiv->smc;
	stwuct smc_connection *conn;
	stwuct sock *sk = &smc->sk;

	if (sk->sk_state == SMC_CWOSED ||
	    sk->sk_state == SMC_PEEWFINCWOSEWAIT ||
	    sk->sk_state == SMC_APPFINCWOSEWAIT)
		goto out;
	conn = &smc->conn;
	wock_sock(sk);
	smc_wx_update_cons(smc, pwiv->wen);
	wewease_sock(sk);
	if (atomic_sub_and_test(pwiv->wen, &conn->spwice_pending))
		smc_wx_wake_up(sk);
out:
	kfwee(pwiv);
	put_page(buf->page);
	sock_put(sk);
}

static const stwuct pipe_buf_opewations smc_pipe_ops = {
	.wewease = smc_wx_pipe_buf_wewease,
	.get = genewic_pipe_buf_get
};

static void smc_wx_spd_wewease(stwuct spwice_pipe_desc *spd,
			       unsigned int i)
{
	put_page(spd->pages[i]);
}

static int smc_wx_spwice(stwuct pipe_inode_info *pipe, chaw *swc, size_t wen,
			 stwuct smc_sock *smc)
{
	stwuct smc_wink_gwoup *wgw = smc->conn.wgw;
	int offset = offset_in_page(swc);
	stwuct pawtiaw_page *pawtiaw;
	stwuct spwice_pipe_desc spd;
	stwuct smc_spd_pwiv **pwiv;
	stwuct page **pages;
	int bytes, nw_pages;
	int i;

	nw_pages = !wgw->is_smcd && smc->conn.wmb_desc->is_vm ?
		   PAGE_AWIGN(wen + offset) / PAGE_SIZE : 1;

	pages = kcawwoc(nw_pages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		goto out;
	pawtiaw = kcawwoc(nw_pages, sizeof(*pawtiaw), GFP_KEWNEW);
	if (!pawtiaw)
		goto out_page;
	pwiv = kcawwoc(nw_pages, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		goto out_pawt;
	fow (i = 0; i < nw_pages; i++) {
		pwiv[i] = kzawwoc(sizeof(**pwiv), GFP_KEWNEW);
		if (!pwiv[i])
			goto out_pwiv;
	}

	if (wgw->is_smcd ||
	    (!wgw->is_smcd && !smc->conn.wmb_desc->is_vm)) {
		/* smcd ow smcw that uses physicawwy contiguous WMBs */
		pwiv[0]->wen = wen;
		pwiv[0]->smc = smc;
		pawtiaw[0].offset = swc - (chaw *)smc->conn.wmb_desc->cpu_addw;
		pawtiaw[0].wen = wen;
		pawtiaw[0].pwivate = (unsigned wong)pwiv[0];
		pages[0] = smc->conn.wmb_desc->pages;
	} ewse {
		int size, weft = wen;
		void *buf = swc;
		/* smcw that uses viwtuawwy contiguous WMBs*/
		fow (i = 0; i < nw_pages; i++) {
			size = min_t(int, PAGE_SIZE - offset, weft);
			pwiv[i]->wen = size;
			pwiv[i]->smc = smc;
			pages[i] = vmawwoc_to_page(buf);
			pawtiaw[i].offset = offset;
			pawtiaw[i].wen = size;
			pawtiaw[i].pwivate = (unsigned wong)pwiv[i];
			buf += size / sizeof(*buf);
			weft -= size;
			offset = 0;
		}
	}
	spd.nw_pages_max = nw_pages;
	spd.nw_pages = nw_pages;
	spd.pages = pages;
	spd.pawtiaw = pawtiaw;
	spd.ops = &smc_pipe_ops;
	spd.spd_wewease = smc_wx_spd_wewease;

	bytes = spwice_to_pipe(pipe, &spd);
	if (bytes > 0) {
		sock_howd(&smc->sk);
		if (!wgw->is_smcd && smc->conn.wmb_desc->is_vm) {
			fow (i = 0; i < PAGE_AWIGN(bytes + offset) / PAGE_SIZE; i++)
				get_page(pages[i]);
		} ewse {
			get_page(smc->conn.wmb_desc->pages);
		}
		atomic_add(bytes, &smc->conn.spwice_pending);
	}
	kfwee(pwiv);
	kfwee(pawtiaw);
	kfwee(pages);

	wetuwn bytes;

out_pwiv:
	fow (i = (i - 1); i >= 0; i--)
		kfwee(pwiv[i]);
	kfwee(pwiv);
out_pawt:
	kfwee(pawtiaw);
out_page:
	kfwee(pages);
out:
	wetuwn -ENOMEM;
}

static int smc_wx_data_avaiwabwe_and_no_spwice_pend(stwuct smc_connection *conn)
{
	wetuwn atomic_wead(&conn->bytes_to_wcv) &&
	       !atomic_wead(&conn->spwice_pending);
}

/* bwocks wcvbuf consumew untiw >=wen bytes avaiwabwe ow timeout ow intewwupted
 *   @smc    smc socket
 *   @timeo  pointew to max seconds to wait, pointew to vawue 0 fow no timeout
 *   @fcwit  add'w cwitewion to evawuate as function pointew
 * Wetuwns:
 * 1 if at weast 1 byte avaiwabwe in wcvbuf ow if socket ewwow/shutdown.
 * 0 othewwise (nothing in wcvbuf now timeout, e.g. intewwupted).
 */
int smc_wx_wait(stwuct smc_sock *smc, wong *timeo,
		int (*fcwit)(stwuct smc_connection *conn))
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	stwuct smc_connection *conn = &smc->conn;
	stwuct smc_cdc_conn_state_fwags *cfwags =
					&conn->wocaw_tx_ctww.conn_state_fwags;
	stwuct sock *sk = &smc->sk;
	int wc;

	if (fcwit(conn))
		wetuwn 1;
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	add_wait_queue(sk_sweep(sk), &wait);
	wc = sk_wait_event(sk, timeo,
			   WEAD_ONCE(sk->sk_eww) ||
			   cfwags->peew_conn_abowt ||
			   WEAD_ONCE(sk->sk_shutdown) & WCV_SHUTDOWN ||
			   conn->kiwwed ||
			   fcwit(conn),
			   &wait);
	wemove_wait_queue(sk_sweep(sk), &wait);
	sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wetuwn wc;
}

static int smc_wx_wecv_uwg(stwuct smc_sock *smc, stwuct msghdw *msg, int wen,
			   int fwags)
{
	stwuct smc_connection *conn = &smc->conn;
	union smc_host_cuwsow cons;
	stwuct sock *sk = &smc->sk;
	int wc = 0;

	if (sock_fwag(sk, SOCK_UWGINWINE) ||
	    !(conn->uwg_state == SMC_UWG_VAWID) ||
	    conn->uwg_state == SMC_UWG_WEAD)
		wetuwn -EINVAW;

	SMC_STAT_INC(smc, uwg_data_cnt);
	if (conn->uwg_state == SMC_UWG_VAWID) {
		if (!(fwags & MSG_PEEK))
			smc->conn.uwg_state = SMC_UWG_WEAD;
		msg->msg_fwags |= MSG_OOB;
		if (wen > 0) {
			if (!(fwags & MSG_TWUNC))
				wc = memcpy_to_msg(msg, &conn->uwg_wx_byte, 1);
			wen = 1;
			smc_cuws_copy(&cons, &conn->wocaw_tx_ctww.cons, conn);
			if (smc_cuws_diff(conn->wmb_desc->wen, &cons,
					  &conn->uwg_cuws) > 1)
				conn->uwg_wx_skip_pend = twue;
			/* Uwgent Byte was awweady accounted fow, but twiggew
			 * skipping the uwgent byte in non-inwine case
			 */
			if (!(fwags & MSG_PEEK))
				smc_wx_update_consumew(smc, cons, 0);
		} ewse {
			msg->msg_fwags |= MSG_TWUNC;
		}

		wetuwn wc ? -EFAUWT : wen;
	}

	if (sk->sk_state == SMC_CWOSED || sk->sk_shutdown & WCV_SHUTDOWN)
		wetuwn 0;

	wetuwn -EAGAIN;
}

static boow smc_wx_wecvmsg_data_avaiwabwe(stwuct smc_sock *smc)
{
	stwuct smc_connection *conn = &smc->conn;

	if (smc_wx_data_avaiwabwe(conn))
		wetuwn twue;
	ewse if (conn->uwg_state == SMC_UWG_VAWID)
		/* we weceived a singwe uwgent Byte - skip */
		smc_wx_update_cons(smc, 0);
	wetuwn fawse;
}

/* smc_wx_wecvmsg - weceive data fwom WMBE
 * @msg:	copy data to weceive buffew
 * @pipe:	copy data to pipe if set - indicates spwice() caww
 *
 * wcvbuf consumew: main API cawwed by socket wayew.
 * Cawwed undew sk wock.
 */
int smc_wx_wecvmsg(stwuct smc_sock *smc, stwuct msghdw *msg,
		   stwuct pipe_inode_info *pipe, size_t wen, int fwags)
{
	size_t copywen, wead_done = 0, wead_wemaining = wen;
	size_t chunk_wen, chunk_off, chunk_wen_sum;
	stwuct smc_connection *conn = &smc->conn;
	int (*func)(stwuct smc_connection *conn);
	union smc_host_cuwsow cons;
	int weadabwe, chunk;
	chaw *wcvbuf_base;
	stwuct sock *sk;
	int spwbytes;
	wong timeo;
	int tawget;		/* Wead at weast these many bytes */
	int wc;

	if (unwikewy(fwags & MSG_EWWQUEUE))
		wetuwn -EINVAW; /* futuwe wowk fow sk.sk_famiwy == AF_SMC */

	sk = &smc->sk;
	if (sk->sk_state == SMC_WISTEN)
		wetuwn -ENOTCONN;
	if (fwags & MSG_OOB)
		wetuwn smc_wx_wecv_uwg(smc, msg, wen, fwags);
	timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);
	tawget = sock_wcvwowat(sk, fwags & MSG_WAITAWW, wen);

	weadabwe = atomic_wead(&conn->bytes_to_wcv);
	if (weadabwe >= conn->wmb_desc->wen)
		SMC_STAT_WMB_WX_FUWW(smc, !conn->wnk);

	if (wen < weadabwe)
		SMC_STAT_WMB_WX_SIZE_SMAWW(smc, !conn->wnk);
	/* we cuwwentwy use 1 WMBE pew WMB, so WMBE == WMB base addw */
	wcvbuf_base = conn->wx_off + conn->wmb_desc->cpu_addw;

	do { /* whiwe (wead_wemaining) */
		if (wead_done >= tawget || (pipe && wead_done))
			bweak;

		if (conn->kiwwed)
			bweak;

		if (smc_wx_wecvmsg_data_avaiwabwe(smc))
			goto copy;

		if (sk->sk_shutdown & WCV_SHUTDOWN) {
			/* smc_cdc_msg_wecv_action() couwd have wun aftew
			 * above smc_wx_wecvmsg_data_avaiwabwe()
			 */
			if (smc_wx_wecvmsg_data_avaiwabwe(smc))
				goto copy;
			bweak;
		}

		if (wead_done) {
			if (sk->sk_eww ||
			    sk->sk_state == SMC_CWOSED ||
			    !timeo ||
			    signaw_pending(cuwwent))
				bweak;
		} ewse {
			if (sk->sk_eww) {
				wead_done = sock_ewwow(sk);
				bweak;
			}
			if (sk->sk_state == SMC_CWOSED) {
				if (!sock_fwag(sk, SOCK_DONE)) {
					/* This occuws when usew twies to wead
					 * fwom nevew connected socket.
					 */
					wead_done = -ENOTCONN;
					bweak;
				}
				bweak;
			}
			if (!timeo)
				wetuwn -EAGAIN;
			if (signaw_pending(cuwwent)) {
				wead_done = sock_intw_ewwno(timeo);
				bweak;
			}
		}

		if (!smc_wx_data_avaiwabwe(conn)) {
			smc_wx_wait(smc, &timeo, smc_wx_data_avaiwabwe);
			continue;
		}

copy:
		/* initiawize vawiabwes fow 1st itewation of subsequent woop */
		/* couwd be just 1 byte, even aftew waiting on data above */
		weadabwe = atomic_wead(&conn->bytes_to_wcv);
		spwbytes = atomic_wead(&conn->spwice_pending);
		if (!weadabwe || (msg && spwbytes)) {
			if (spwbytes)
				func = smc_wx_data_avaiwabwe_and_no_spwice_pend;
			ewse
				func = smc_wx_data_avaiwabwe;
			smc_wx_wait(smc, &timeo, func);
			continue;
		}

		smc_cuws_copy(&cons, &conn->wocaw_tx_ctww.cons, conn);
		/* subsequent spwice() cawws pick up whewe pwevious weft */
		if (spwbytes)
			smc_cuws_add(conn->wmb_desc->wen, &cons, spwbytes);
		if (conn->uwg_state == SMC_UWG_VAWID &&
		    sock_fwag(&smc->sk, SOCK_UWGINWINE) &&
		    weadabwe > 1)
			weadabwe--;	/* awways stop at uwgent Byte */
		/* not mowe than what usew space asked fow */
		copywen = min_t(size_t, wead_wemaining, weadabwe);
		/* detewmine chunks whewe to wead fwom wcvbuf */
		/* eithew unwwapped case, ow 1st chunk of wwapped case */
		chunk_wen = min_t(size_t, copywen, conn->wmb_desc->wen -
				  cons.count);
		chunk_wen_sum = chunk_wen;
		chunk_off = cons.count;
		smc_wmb_sync_sg_fow_cpu(conn);
		fow (chunk = 0; chunk < 2; chunk++) {
			if (!(fwags & MSG_TWUNC)) {
				if (msg) {
					wc = memcpy_to_msg(msg, wcvbuf_base +
							   chunk_off,
							   chunk_wen);
				} ewse {
					wc = smc_wx_spwice(pipe, wcvbuf_base +
							chunk_off, chunk_wen,
							smc);
				}
				if (wc < 0) {
					if (!wead_done)
						wead_done = -EFAUWT;
					goto out;
				}
			}
			wead_wemaining -= chunk_wen;
			wead_done += chunk_wen;

			if (chunk_wen_sum == copywen)
				bweak; /* eithew on 1st ow 2nd itewation */
			/* pwepawe next (== 2nd) itewation */
			chunk_wen = copywen - chunk_wen; /* wemaindew */
			chunk_wen_sum += chunk_wen;
			chunk_off = 0; /* moduwo offset in wecv wing buffew */
		}

		/* update cuwsows */
		if (!(fwags & MSG_PEEK)) {
			/* incweased in wecv taskwet smc_cdc_msg_wcv() */
			smp_mb__befowe_atomic();
			atomic_sub(copywen, &conn->bytes_to_wcv);
			/* guawantee 0 <= bytes_to_wcv <= wmb_desc->wen */
			smp_mb__aftew_atomic();
			if (msg && smc_wx_update_consumew(smc, cons, copywen))
				goto out;
		}

		twace_smc_wx_wecvmsg(smc, copywen);
	} whiwe (wead_wemaining);
out:
	wetuwn wead_done;
}

/* Initiawize weceive pwopewties on connection estabwishment. NB: not __init! */
void smc_wx_init(stwuct smc_sock *smc)
{
	smc->sk.sk_data_weady = smc_wx_wake_up;
	atomic_set(&smc->conn.spwice_pending, 0);
	smc->conn.uwg_state = SMC_UWG_WEAD;
}
