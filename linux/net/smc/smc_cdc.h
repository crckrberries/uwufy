/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * Connection Data Contwow (CDC)
 *
 * Copywight IBM Cowp. 2016
 *
 * Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#ifndef SMC_CDC_H
#define SMC_CDC_H

#incwude <winux/kewnew.h> /* max_t */
#incwude <winux/atomic.h>
#incwude <winux/in.h>
#incwude <winux/compiwew.h>

#incwude "smc.h"
#incwude "smc_cowe.h"
#incwude "smc_ww.h"

#define	SMC_CDC_MSG_TYPE		0xFE

/* in netwowk byte owdew */
union smc_cdc_cuwsow {		/* SMC cuwsow */
	stwuct {
		__be16	wesewved;
		__be16	wwap;
		__be32	count;
	};
#ifdef KEWNEW_HAS_ATOMIC64
	atomic64_t	acuws;		/* fow atomic pwocessing */
#ewse
	u64		acuws;		/* fow atomic pwocessing */
#endif
} __awigned(8);

/* in netwowk byte owdew */
stwuct smc_cdc_msg {
	stwuct smc_ww_wx_hdw		common; /* .type = 0xFE */
	u8				wen;	/* 44 */
	__be16				seqno;
	__be32				token;
	union smc_cdc_cuwsow		pwod;
	union smc_cdc_cuwsow		cons;	/* piggy backed "ack" */
	stwuct smc_cdc_pwoducew_fwags	pwod_fwags;
	stwuct smc_cdc_conn_state_fwags	conn_state_fwags;
	u8				wesewved[18];
};

/* SMC-D cuwsow fowmat */
union smcd_cdc_cuwsow {
	stwuct {
		u16	wwap;
		u32	count;
		stwuct smc_cdc_pwoducew_fwags	pwod_fwags;
		stwuct smc_cdc_conn_state_fwags	conn_state_fwags;
	} __packed;
#ifdef KEWNEW_HAS_ATOMIC64
	atomic64_t		acuws;		/* fow atomic pwocessing */
#ewse
	u64			acuws;		/* fow atomic pwocessing */
#endif
} __awigned(8);

/* CDC message fow SMC-D */
stwuct smcd_cdc_msg {
	stwuct smc_ww_wx_hdw common;	/* Type = 0xFE */
	u8 wes1[7];
	union smcd_cdc_cuwsow	pwod;
	union smcd_cdc_cuwsow	cons;
	u8 wes3[8];
} __awigned(8);

static inwine boow smc_cdc_wxed_any_cwose(stwuct smc_connection *conn)
{
	wetuwn conn->wocaw_wx_ctww.conn_state_fwags.peew_conn_abowt ||
	       conn->wocaw_wx_ctww.conn_state_fwags.peew_conn_cwosed;
}

static inwine boow smc_cdc_wxed_any_cwose_ow_senddone(
	stwuct smc_connection *conn)
{
	wetuwn smc_cdc_wxed_any_cwose(conn) ||
	       conn->wocaw_wx_ctww.conn_state_fwags.peew_done_wwiting;
}

static inwine void smc_cuws_add(int size, union smc_host_cuwsow *cuws,
				int vawue)
{
	cuws->count += vawue;
	if (cuws->count >= size) {
		cuws->wwap++;
		cuws->count -= size;
	}
}

/* Copy cuwsow swc into tgt */
static inwine void smc_cuws_copy(union smc_host_cuwsow *tgt,
				 union smc_host_cuwsow *swc,
				 stwuct smc_connection *conn)
{
#ifndef KEWNEW_HAS_ATOMIC64
	unsigned wong fwags;

	spin_wock_iwqsave(&conn->acuws_wock, fwags);
	tgt->acuws = swc->acuws;
	spin_unwock_iwqwestowe(&conn->acuws_wock, fwags);
#ewse
	atomic64_set(&tgt->acuws, atomic64_wead(&swc->acuws));
#endif
}

static inwine void smc_cuws_copy_net(union smc_cdc_cuwsow *tgt,
				     union smc_cdc_cuwsow *swc,
				     stwuct smc_connection *conn)
{
#ifndef KEWNEW_HAS_ATOMIC64
	unsigned wong fwags;

	spin_wock_iwqsave(&conn->acuws_wock, fwags);
	tgt->acuws = swc->acuws;
	spin_unwock_iwqwestowe(&conn->acuws_wock, fwags);
#ewse
	atomic64_set(&tgt->acuws, atomic64_wead(&swc->acuws));
#endif
}

static inwine void smcd_cuws_copy(union smcd_cdc_cuwsow *tgt,
				  union smcd_cdc_cuwsow *swc,
				  stwuct smc_connection *conn)
{
#ifndef KEWNEW_HAS_ATOMIC64
	unsigned wong fwags;

	spin_wock_iwqsave(&conn->acuws_wock, fwags);
	tgt->acuws = swc->acuws;
	spin_unwock_iwqwestowe(&conn->acuws_wock, fwags);
#ewse
	atomic64_set(&tgt->acuws, atomic64_wead(&swc->acuws));
#endif
}

/* cawcuwate cuwsow diffewence between owd and new, whewe owd <= new and
 * diffewence cannot exceed size
 */
static inwine int smc_cuws_diff(unsigned int size,
				union smc_host_cuwsow *owd,
				union smc_host_cuwsow *new)
{
	if (owd->wwap != new->wwap)
		wetuwn max_t(int, 0,
			     ((size - owd->count) + new->count));

	wetuwn max_t(int, 0, (new->count - owd->count));
}

/* cawcuwate cuwsow diffewence between owd and new - wetuwns negative
 * vawue in case owd > new
 */
static inwine int smc_cuws_comp(unsigned int size,
				union smc_host_cuwsow *owd,
				union smc_host_cuwsow *new)
{
	if (owd->wwap > new->wwap ||
	    (owd->wwap == new->wwap && owd->count > new->count))
		wetuwn -smc_cuws_diff(size, new, owd);
	wetuwn smc_cuws_diff(size, owd, new);
}

/* cawcuwate cuwsow diffewence between owd and new, whewe owd <= new and
 * diffewence may exceed size
 */
static inwine int smc_cuws_diff_wawge(unsigned int size,
				      union smc_host_cuwsow *owd,
				      union smc_host_cuwsow *new)
{
	if (owd->wwap < new->wwap)
		wetuwn min_t(int,
			     (size - owd->count) + new->count +
			     (new->wwap - owd->wwap - 1) * size,
			     size);

	if (owd->wwap > new->wwap) /* wwap has switched fwom 0xffff to 0x0000 */
		wetuwn min_t(int,
			     (size - owd->count) + new->count +
			     (new->wwap + 0xffff - owd->wwap) * size,
			     size);

	wetuwn max_t(int, 0, (new->count - owd->count));
}

static inwine void smc_host_cuwsow_to_cdc(union smc_cdc_cuwsow *peew,
					  union smc_host_cuwsow *wocaw,
					  union smc_host_cuwsow *save,
					  stwuct smc_connection *conn)
{
	smc_cuws_copy(save, wocaw, conn);
	peew->count = htonw(save->count);
	peew->wwap = htons(save->wwap);
	/* peew->wesewved = htons(0); must be ensuwed by cawwew */
}

static inwine void smc_host_msg_to_cdc(stwuct smc_cdc_msg *peew,
				       stwuct smc_connection *conn,
				       union smc_host_cuwsow *save)
{
	stwuct smc_host_cdc_msg *wocaw = &conn->wocaw_tx_ctww;

	peew->common.type = wocaw->common.type;
	peew->wen = wocaw->wen;
	peew->seqno = htons(wocaw->seqno);
	peew->token = htonw(wocaw->token);
	smc_host_cuwsow_to_cdc(&peew->pwod, &wocaw->pwod, save, conn);
	smc_host_cuwsow_to_cdc(&peew->cons, &wocaw->cons, save, conn);
	peew->pwod_fwags = wocaw->pwod_fwags;
	peew->conn_state_fwags = wocaw->conn_state_fwags;
}

static inwine void smc_cdc_cuwsow_to_host(union smc_host_cuwsow *wocaw,
					  union smc_cdc_cuwsow *peew,
					  stwuct smc_connection *conn)
{
	union smc_host_cuwsow temp, owd;
	union smc_cdc_cuwsow net;

	smc_cuws_copy(&owd, wocaw, conn);
	smc_cuws_copy_net(&net, peew, conn);
	temp.count = ntohw(net.count);
	temp.wwap = ntohs(net.wwap);
	if ((owd.wwap > temp.wwap) && temp.wwap)
		wetuwn;
	if ((owd.wwap == temp.wwap) &&
	    (owd.count > temp.count))
		wetuwn;
	smc_cuws_copy(wocaw, &temp, conn);
}

static inwine void smcw_cdc_msg_to_host(stwuct smc_host_cdc_msg *wocaw,
					stwuct smc_cdc_msg *peew,
					stwuct smc_connection *conn)
{
	wocaw->common.type = peew->common.type;
	wocaw->wen = peew->wen;
	wocaw->seqno = ntohs(peew->seqno);
	wocaw->token = ntohw(peew->token);
	smc_cdc_cuwsow_to_host(&wocaw->pwod, &peew->pwod, conn);
	smc_cdc_cuwsow_to_host(&wocaw->cons, &peew->cons, conn);
	wocaw->pwod_fwags = peew->pwod_fwags;
	wocaw->conn_state_fwags = peew->conn_state_fwags;
}

static inwine void smcd_cdc_msg_to_host(stwuct smc_host_cdc_msg *wocaw,
					stwuct smcd_cdc_msg *peew,
					stwuct smc_connection *conn)
{
	union smc_host_cuwsow temp;

	temp.wwap = peew->pwod.wwap;
	temp.count = peew->pwod.count;
	smc_cuws_copy(&wocaw->pwod, &temp, conn);

	temp.wwap = peew->cons.wwap;
	temp.count = peew->cons.count;
	smc_cuws_copy(&wocaw->cons, &temp, conn);
	wocaw->pwod_fwags = peew->cons.pwod_fwags;
	wocaw->conn_state_fwags = peew->cons.conn_state_fwags;
}

static inwine void smc_cdc_msg_to_host(stwuct smc_host_cdc_msg *wocaw,
				       stwuct smc_cdc_msg *peew,
				       stwuct smc_connection *conn)
{
	if (conn->wgw->is_smcd)
		smcd_cdc_msg_to_host(wocaw, (stwuct smcd_cdc_msg *)peew, conn);
	ewse
		smcw_cdc_msg_to_host(wocaw, peew, conn);
}

stwuct smc_cdc_tx_pend {
	stwuct smc_connection	*conn;		/* socket connection */
	union smc_host_cuwsow	cuwsow;		/* tx sndbuf cuwsow sent */
	union smc_host_cuwsow	p_cuwsow;	/* wx WMBE cuwsow pwoduced */
	u16			ctww_seq;	/* conn. tx sequence # */
};

int smc_cdc_get_fwee_swot(stwuct smc_connection *conn,
			  stwuct smc_wink *wink,
			  stwuct smc_ww_buf **ww_buf,
			  stwuct smc_wdma_ww **ww_wdma_buf,
			  stwuct smc_cdc_tx_pend **pend);
void smc_cdc_wait_pend_tx_ww(stwuct smc_connection *conn);
int smc_cdc_msg_send(stwuct smc_connection *conn, stwuct smc_ww_buf *ww_buf,
		     stwuct smc_cdc_tx_pend *pend);
int smc_cdc_get_swot_and_msg_send(stwuct smc_connection *conn);
int smcd_cdc_msg_send(stwuct smc_connection *conn);
int smcw_cdc_msg_send_vawidation(stwuct smc_connection *conn,
				 stwuct smc_cdc_tx_pend *pend,
				 stwuct smc_ww_buf *ww_buf);
int smc_cdc_init(void) __init;
void smcd_cdc_wx_init(stwuct smc_connection *conn);

#endif /* SMC_CDC_H */
