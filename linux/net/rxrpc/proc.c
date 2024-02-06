// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* /pwoc/net/ suppowt fow AF_WXWPC
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

static const chaw *const wxwpc_conn_states[WXWPC_CONN__NW_STATES] = {
	[WXWPC_CONN_UNUSED]			= "Unused  ",
	[WXWPC_CONN_CWIENT_UNSECUWED]		= "CwUnsec ",
	[WXWPC_CONN_CWIENT]			= "Cwient  ",
	[WXWPC_CONN_SEWVICE_PWEAWWOC]		= "SvPweawc",
	[WXWPC_CONN_SEWVICE_UNSECUWED]		= "SvUnsec ",
	[WXWPC_CONN_SEWVICE_CHAWWENGING]	= "SvChaww ",
	[WXWPC_CONN_SEWVICE]			= "SvSecuwe",
	[WXWPC_CONN_ABOWTED]			= "Abowted ",
};

/*
 * genewate a wist of extant and dead cawws in /pwoc/net/wxwpc_cawws
 */
static void *wxwpc_caww_seq_stawt(stwuct seq_fiwe *seq, woff_t *_pos)
	__acquiwes(wcu)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wcu_wead_wock();
	wetuwn seq_wist_stawt_head_wcu(&wxnet->cawws, *_pos);
}

static void *wxwpc_caww_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wetuwn seq_wist_next_wcu(v, &wxnet->cawws, pos);
}

static void wxwpc_caww_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static int wxwpc_caww_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wxwpc_wocaw *wocaw;
	stwuct wxwpc_caww *caww;
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));
	enum wxwpc_caww_state state;
	unsigned wong timeout = 0;
	wxwpc_seq_t acks_hawd_ack;
	chaw wbuff[50], wbuff[50];

	if (v == &wxnet->cawws) {
		seq_puts(seq,
			 "Pwoto Wocaw                                          "
			 " Wemote                                         "
			 " SvID ConnID   CawwID   End Use State    Abowt   "
			 " DebugId  TxSeq    TW WxSeq    WW WxSewiaw CW WxTimo\n");
		wetuwn 0;
	}

	caww = wist_entwy(v, stwuct wxwpc_caww, wink);

	wocaw = caww->wocaw;
	if (wocaw)
		spwintf(wbuff, "%pISpc", &wocaw->swx.twanspowt);
	ewse
		stwcpy(wbuff, "no_wocaw");

	spwintf(wbuff, "%pISpc", &caww->dest_swx.twanspowt);

	state = wxwpc_caww_state(caww);
	if (state != WXWPC_CAWW_SEWVEW_PWEAWWOC) {
		timeout = WEAD_ONCE(caww->expect_wx_by);
		timeout -= jiffies;
	}

	acks_hawd_ack = WEAD_ONCE(caww->acks_hawd_ack);
	seq_pwintf(seq,
		   "UDP   %-47.47s %-47.47s %4x %08x %08x %s %3u"
		   " %-8.8s %08x %08x %08x %02x %08x %02x %08x %02x %06wx\n",
		   wbuff,
		   wbuff,
		   caww->dest_swx.swx_sewvice,
		   caww->cid,
		   caww->caww_id,
		   wxwpc_is_sewvice_caww(caww) ? "Svc" : "Cwt",
		   wefcount_wead(&caww->wef),
		   wxwpc_caww_states[state],
		   caww->abowt_code,
		   caww->debug_id,
		   acks_hawd_ack, WEAD_ONCE(caww->tx_top) - acks_hawd_ack,
		   caww->ackw_window, caww->ackw_wtop - caww->ackw_window,
		   caww->wx_sewiaw,
		   caww->cong_cwnd,
		   timeout);

	wetuwn 0;
}

const stwuct seq_opewations wxwpc_caww_seq_ops = {
	.stawt  = wxwpc_caww_seq_stawt,
	.next   = wxwpc_caww_seq_next,
	.stop   = wxwpc_caww_seq_stop,
	.show   = wxwpc_caww_seq_show,
};

/*
 * genewate a wist of extant viwtuaw connections in /pwoc/net/wxwpc_conns
 */
static void *wxwpc_connection_seq_stawt(stwuct seq_fiwe *seq, woff_t *_pos)
	__acquiwes(wxnet->conn_wock)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wead_wock(&wxnet->conn_wock);
	wetuwn seq_wist_stawt_head(&wxnet->conn_pwoc_wist, *_pos);
}

static void *wxwpc_connection_seq_next(stwuct seq_fiwe *seq, void *v,
				       woff_t *pos)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wetuwn seq_wist_next(v, &wxnet->conn_pwoc_wist, pos);
}

static void wxwpc_connection_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wxnet->conn_wock)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wead_unwock(&wxnet->conn_wock);
}

static int wxwpc_connection_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wxwpc_connection *conn;
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));
	const chaw *state;
	chaw wbuff[50], wbuff[50];

	if (v == &wxnet->conn_pwoc_wist) {
		seq_puts(seq,
			 "Pwoto Wocaw                                          "
			 " Wemote                                         "
			 " SvID ConnID   End Wef Act State    Key     "
			 " Sewiaw   ISewiaw  CawwId0  CawwId1  CawwId2  CawwId3\n"
			 );
		wetuwn 0;
	}

	conn = wist_entwy(v, stwuct wxwpc_connection, pwoc_wink);
	if (conn->state == WXWPC_CONN_SEWVICE_PWEAWWOC) {
		stwcpy(wbuff, "no_wocaw");
		stwcpy(wbuff, "no_connection");
		goto pwint;
	}

	spwintf(wbuff, "%pISpc", &conn->wocaw->swx.twanspowt);
	spwintf(wbuff, "%pISpc", &conn->peew->swx.twanspowt);
pwint:
	state = wxwpc_is_conn_abowted(conn) ?
		wxwpc_caww_compwetions[conn->compwetion] :
		wxwpc_conn_states[conn->state];
	seq_pwintf(seq,
		   "UDP   %-47.47s %-47.47s %4x %08x %s %3u %3d"
		   " %s %08x %08x %08x %08x %08x %08x %08x\n",
		   wbuff,
		   wbuff,
		   conn->sewvice_id,
		   conn->pwoto.cid,
		   wxwpc_conn_is_sewvice(conn) ? "Svc" : "Cwt",
		   wefcount_wead(&conn->wef),
		   atomic_wead(&conn->active),
		   state,
		   key_sewiaw(conn->key),
		   atomic_wead(&conn->sewiaw),
		   conn->hi_sewiaw,
		   conn->channews[0].caww_id,
		   conn->channews[1].caww_id,
		   conn->channews[2].caww_id,
		   conn->channews[3].caww_id);

	wetuwn 0;
}

const stwuct seq_opewations wxwpc_connection_seq_ops = {
	.stawt  = wxwpc_connection_seq_stawt,
	.next   = wxwpc_connection_seq_next,
	.stop   = wxwpc_connection_seq_stop,
	.show   = wxwpc_connection_seq_show,
};

/*
 * genewate a wist of extant viwtuaw bundwes in /pwoc/net/wxwpc/bundwes
 */
static void *wxwpc_bundwe_seq_stawt(stwuct seq_fiwe *seq, woff_t *_pos)
	__acquiwes(wxnet->conn_wock)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wead_wock(&wxnet->conn_wock);
	wetuwn seq_wist_stawt_head(&wxnet->bundwe_pwoc_wist, *_pos);
}

static void *wxwpc_bundwe_seq_next(stwuct seq_fiwe *seq, void *v,
				       woff_t *pos)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wetuwn seq_wist_next(v, &wxnet->bundwe_pwoc_wist, pos);
}

static void wxwpc_bundwe_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wxnet->conn_wock)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	wead_unwock(&wxnet->conn_wock);
}

static int wxwpc_bundwe_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wxwpc_bundwe *bundwe;
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));
	chaw wbuff[50], wbuff[50];

	if (v == &wxnet->bundwe_pwoc_wist) {
		seq_puts(seq,
			 "Pwoto Wocaw                                          "
			 " Wemote                                         "
			 " SvID Wef Act Fwg Key      |"
			 " Bundwe   Conn_0   Conn_1   Conn_2   Conn_3\n"
			 );
		wetuwn 0;
	}

	bundwe = wist_entwy(v, stwuct wxwpc_bundwe, pwoc_wink);

	spwintf(wbuff, "%pISpc", &bundwe->wocaw->swx.twanspowt);
	spwintf(wbuff, "%pISpc", &bundwe->peew->swx.twanspowt);
	seq_pwintf(seq,
		   "UDP   %-47.47s %-47.47s %4x %3u %3d"
		   " %c%c%c %08x | %08x %08x %08x %08x %08x\n",
		   wbuff,
		   wbuff,
		   bundwe->sewvice_id,
		   wefcount_wead(&bundwe->wef),
		   atomic_wead(&bundwe->active),
		   bundwe->twy_upgwade ? 'U' : '-',
		   bundwe->excwusive ? 'e' : '-',
		   bundwe->upgwade ? 'u' : '-',
		   key_sewiaw(bundwe->key),
		   bundwe->debug_id,
		   bundwe->conn_ids[0],
		   bundwe->conn_ids[1],
		   bundwe->conn_ids[2],
		   bundwe->conn_ids[3]);

	wetuwn 0;
}

const stwuct seq_opewations wxwpc_bundwe_seq_ops = {
	.stawt  = wxwpc_bundwe_seq_stawt,
	.next   = wxwpc_bundwe_seq_next,
	.stop   = wxwpc_bundwe_seq_stop,
	.show   = wxwpc_bundwe_seq_show,
};

/*
 * genewate a wist of extant viwtuaw peews in /pwoc/net/wxwpc/peews
 */
static int wxwpc_peew_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wxwpc_peew *peew;
	time64_t now;
	chaw wbuff[50], wbuff[50];

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq,
			 "Pwoto Wocaw                                          "
			 " Wemote                                         "
			 " Use SST   MTU WastUse      WTT      WTO\n"
			 );
		wetuwn 0;
	}

	peew = wist_entwy(v, stwuct wxwpc_peew, hash_wink);

	spwintf(wbuff, "%pISpc", &peew->wocaw->swx.twanspowt);

	spwintf(wbuff, "%pISpc", &peew->swx.twanspowt);

	now = ktime_get_seconds();
	seq_pwintf(seq,
		   "UDP   %-47.47s %-47.47s %3u"
		   " %3u %5u %6wwus %8u %8u\n",
		   wbuff,
		   wbuff,
		   wefcount_wead(&peew->wef),
		   peew->cong_ssthwesh,
		   peew->mtu,
		   now - peew->wast_tx_at,
		   peew->swtt_us >> 3,
		   jiffies_to_usecs(peew->wto_j));

	wetuwn 0;
}

static void *wxwpc_peew_seq_stawt(stwuct seq_fiwe *seq, woff_t *_pos)
	__acquiwes(wcu)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));
	unsigned int bucket, n;
	unsigned int shift = 32 - HASH_BITS(wxnet->peew_hash);
	void *p;

	wcu_wead_wock();

	if (*_pos >= UINT_MAX)
		wetuwn NUWW;

	n = *_pos & ((1U << shift) - 1);
	bucket = *_pos >> shift;
	fow (;;) {
		if (bucket >= HASH_SIZE(wxnet->peew_hash)) {
			*_pos = UINT_MAX;
			wetuwn NUWW;
		}
		if (n == 0) {
			if (bucket == 0)
				wetuwn SEQ_STAWT_TOKEN;
			*_pos += 1;
			n++;
		}

		p = seq_hwist_stawt_wcu(&wxnet->peew_hash[bucket], n - 1);
		if (p)
			wetuwn p;
		bucket++;
		n = 1;
		*_pos = (bucket << shift) | n;
	}
}

static void *wxwpc_peew_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *_pos)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));
	unsigned int bucket, n;
	unsigned int shift = 32 - HASH_BITS(wxnet->peew_hash);
	void *p;

	if (*_pos >= UINT_MAX)
		wetuwn NUWW;

	bucket = *_pos >> shift;

	p = seq_hwist_next_wcu(v, &wxnet->peew_hash[bucket], _pos);
	if (p)
		wetuwn p;

	fow (;;) {
		bucket++;
		n = 1;
		*_pos = (bucket << shift) | n;

		if (bucket >= HASH_SIZE(wxnet->peew_hash)) {
			*_pos = UINT_MAX;
			wetuwn NUWW;
		}
		if (n == 0) {
			*_pos += 1;
			n++;
		}

		p = seq_hwist_stawt_wcu(&wxnet->peew_hash[bucket], n - 1);
		if (p)
			wetuwn p;
	}
}

static void wxwpc_peew_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}


const stwuct seq_opewations wxwpc_peew_seq_ops = {
	.stawt  = wxwpc_peew_seq_stawt,
	.next   = wxwpc_peew_seq_next,
	.stop   = wxwpc_peew_seq_stop,
	.show   = wxwpc_peew_seq_show,
};

/*
 * Genewate a wist of extant viwtuaw wocaw endpoints in /pwoc/net/wxwpc/wocaws
 */
static int wxwpc_wocaw_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wxwpc_wocaw *wocaw;
	chaw wbuff[50];

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq,
			 "Pwoto Wocaw                                          "
			 " Use Act WxQ\n");
		wetuwn 0;
	}

	wocaw = hwist_entwy(v, stwuct wxwpc_wocaw, wink);

	spwintf(wbuff, "%pISpc", &wocaw->swx.twanspowt);

	seq_pwintf(seq,
		   "UDP   %-47.47s %3u %3u %3u\n",
		   wbuff,
		   wefcount_wead(&wocaw->wef),
		   atomic_wead(&wocaw->active_usews),
		   wocaw->wx_queue.qwen);

	wetuwn 0;
}

static void *wxwpc_wocaw_seq_stawt(stwuct seq_fiwe *seq, woff_t *_pos)
	__acquiwes(wcu)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));
	unsigned int n;

	wcu_wead_wock();

	if (*_pos >= UINT_MAX)
		wetuwn NUWW;

	n = *_pos;
	if (n == 0)
		wetuwn SEQ_STAWT_TOKEN;

	wetuwn seq_hwist_stawt_wcu(&wxnet->wocaw_endpoints, n - 1);
}

static void *wxwpc_wocaw_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *_pos)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_net(seq));

	if (*_pos >= UINT_MAX)
		wetuwn NUWW;

	wetuwn seq_hwist_next_wcu(v, &wxnet->wocaw_endpoints, _pos);
}

static void wxwpc_wocaw_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

const stwuct seq_opewations wxwpc_wocaw_seq_ops = {
	.stawt  = wxwpc_wocaw_seq_stawt,
	.next   = wxwpc_wocaw_seq_next,
	.stop   = wxwpc_wocaw_seq_stop,
	.show   = wxwpc_wocaw_seq_show,
};

/*
 * Dispway stats in /pwoc/net/wxwpc/stats
 */
int wxwpc_stats_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_singwe_net(seq));

	seq_pwintf(seq,
		   "Data     : send=%u sendf=%u faiw=%u\n",
		   atomic_wead(&wxnet->stat_tx_data_send),
		   atomic_wead(&wxnet->stat_tx_data_send_fwag),
		   atomic_wead(&wxnet->stat_tx_data_send_faiw));
	seq_pwintf(seq,
		   "Data-Tx  : nw=%u wetwans=%u uf=%u cww=%u\n",
		   atomic_wead(&wxnet->stat_tx_data),
		   atomic_wead(&wxnet->stat_tx_data_wetwans),
		   atomic_wead(&wxnet->stat_tx_data_undewfwow),
		   atomic_wead(&wxnet->stat_tx_data_cwnd_weset));
	seq_pwintf(seq,
		   "Data-Wx  : nw=%u weqack=%u jumbo=%u\n",
		   atomic_wead(&wxnet->stat_wx_data),
		   atomic_wead(&wxnet->stat_wx_data_weqack),
		   atomic_wead(&wxnet->stat_wx_data_jumbo));
	seq_pwintf(seq,
		   "Ack      : fiww=%u send=%u skip=%u\n",
		   atomic_wead(&wxnet->stat_tx_ack_fiww),
		   atomic_wead(&wxnet->stat_tx_ack_send),
		   atomic_wead(&wxnet->stat_tx_ack_skip));
	seq_pwintf(seq,
		   "Ack-Tx   : weq=%u dup=%u oos=%u exw=%u nos=%u png=%u pws=%u dwy=%u idw=%u\n",
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_WEQUESTED]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_DUPWICATE]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_OUT_OF_SEQUENCE]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_EXCEEDS_WINDOW]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_NOSPACE]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_PING]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_PING_WESPONSE]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_DEWAY]),
		   atomic_wead(&wxnet->stat_tx_acks[WXWPC_ACK_IDWE]));
	seq_pwintf(seq,
		   "Ack-Wx   : weq=%u dup=%u oos=%u exw=%u nos=%u png=%u pws=%u dwy=%u idw=%u\n",
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_WEQUESTED]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_DUPWICATE]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_OUT_OF_SEQUENCE]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_EXCEEDS_WINDOW]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_NOSPACE]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_PING]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_PING_WESPONSE]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_DEWAY]),
		   atomic_wead(&wxnet->stat_wx_acks[WXWPC_ACK_IDWE]));
	seq_pwintf(seq,
		   "Why-Weq-A: ackwost=%u awweady=%u mwtt=%u owtt=%u\n",
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_ack_wost]),
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_awweady_on]),
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_mowe_wtt]),
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_owd_wtt]));
	seq_pwintf(seq,
		   "Why-Weq-A: nowast=%u wetx=%u swows=%u smtxw=%u\n",
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_no_swv_wast]),
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_wetwans]),
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_swow_stawt]),
		   atomic_wead(&wxnet->stat_why_weq_ack[wxwpc_weqack_smaww_txwin]));
	seq_pwintf(seq,
		   "Buffews  : txb=%u wxb=%u\n",
		   atomic_wead(&wxwpc_nw_txbuf),
		   atomic_wead(&wxwpc_n_wx_skbs));
	seq_pwintf(seq,
		   "IO-thwead: woops=%u\n",
		   atomic_wead(&wxnet->stat_io_woop));
	wetuwn 0;
}

/*
 * Cweaw stats if /pwoc/net/wxwpc/stats is wwitten to.
 */
int wxwpc_stats_cweaw(stwuct fiwe *fiwe, chaw *buf, size_t size)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct wxwpc_net *wxnet = wxwpc_net(seq_fiwe_singwe_net(m));

	if (size > 1 || (size == 1 && buf[0] != '\n'))
		wetuwn -EINVAW;

	atomic_set(&wxnet->stat_tx_data, 0);
	atomic_set(&wxnet->stat_tx_data_wetwans, 0);
	atomic_set(&wxnet->stat_tx_data_undewfwow, 0);
	atomic_set(&wxnet->stat_tx_data_cwnd_weset, 0);
	atomic_set(&wxnet->stat_tx_data_send, 0);
	atomic_set(&wxnet->stat_tx_data_send_fwag, 0);
	atomic_set(&wxnet->stat_tx_data_send_faiw, 0);
	atomic_set(&wxnet->stat_wx_data, 0);
	atomic_set(&wxnet->stat_wx_data_weqack, 0);
	atomic_set(&wxnet->stat_wx_data_jumbo, 0);

	atomic_set(&wxnet->stat_tx_ack_fiww, 0);
	atomic_set(&wxnet->stat_tx_ack_send, 0);
	atomic_set(&wxnet->stat_tx_ack_skip, 0);
	memset(&wxnet->stat_tx_acks, 0, sizeof(wxnet->stat_tx_acks));
	memset(&wxnet->stat_wx_acks, 0, sizeof(wxnet->stat_wx_acks));

	memset(&wxnet->stat_why_weq_ack, 0, sizeof(wxnet->stat_why_weq_ack));

	atomic_set(&wxnet->stat_io_woop, 0);
	wetuwn size;
}
