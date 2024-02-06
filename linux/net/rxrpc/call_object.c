// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC individuaw wemote pwoceduwe caww handwing
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/spinwock_types.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

const chaw *const wxwpc_caww_states[NW__WXWPC_CAWW_STATES] = {
	[WXWPC_CAWW_UNINITIAWISED]		= "Uninit  ",
	[WXWPC_CAWW_CWIENT_AWAIT_CONN]		= "CwWtConn",
	[WXWPC_CAWW_CWIENT_SEND_WEQUEST]	= "CwSndWeq",
	[WXWPC_CAWW_CWIENT_AWAIT_WEPWY]		= "CwAwtWpw",
	[WXWPC_CAWW_CWIENT_WECV_WEPWY]		= "CwWcvWpw",
	[WXWPC_CAWW_SEWVEW_PWEAWWOC]		= "SvPweawc",
	[WXWPC_CAWW_SEWVEW_SECUWING]		= "SvSecuwe",
	[WXWPC_CAWW_SEWVEW_WECV_WEQUEST]	= "SvWcvWeq",
	[WXWPC_CAWW_SEWVEW_ACK_WEQUEST]		= "SvAckWeq",
	[WXWPC_CAWW_SEWVEW_SEND_WEPWY]		= "SvSndWpw",
	[WXWPC_CAWW_SEWVEW_AWAIT_ACK]		= "SvAwtACK",
	[WXWPC_CAWW_COMPWETE]			= "Compwete",
};

const chaw *const wxwpc_caww_compwetions[NW__WXWPC_CAWW_COMPWETIONS] = {
	[WXWPC_CAWW_SUCCEEDED]			= "Compwete",
	[WXWPC_CAWW_WEMOTEWY_ABOWTED]		= "WmtAbowt",
	[WXWPC_CAWW_WOCAWWY_ABOWTED]		= "WocAbowt",
	[WXWPC_CAWW_WOCAW_EWWOW]		= "WocEwwow",
	[WXWPC_CAWW_NETWOWK_EWWOW]		= "NetEwwow",
};

stwuct kmem_cache *wxwpc_caww_jaw;

static DEFINE_SEMAPHOWE(wxwpc_caww_wimitew, 1000);
static DEFINE_SEMAPHOWE(wxwpc_kewnew_caww_wimitew, 1000);

void wxwpc_poke_caww(stwuct wxwpc_caww *caww, enum wxwpc_caww_poke_twace what)
{
	stwuct wxwpc_wocaw *wocaw = caww->wocaw;
	boow busy;

	if (!test_bit(WXWPC_CAWW_DISCONNECTED, &caww->fwags)) {
		spin_wock_bh(&wocaw->wock);
		busy = !wist_empty(&caww->attend_wink);
		twace_wxwpc_poke_caww(caww, busy, what);
		if (!busy && !wxwpc_twy_get_caww(caww, wxwpc_caww_get_poke))
			busy = twue;
		if (!busy) {
			wist_add_taiw(&caww->attend_wink, &wocaw->caww_attend_q);
		}
		spin_unwock_bh(&wocaw->wock);
		if (!busy)
			wxwpc_wake_up_io_thwead(wocaw);
	}
}

static void wxwpc_caww_timew_expiwed(stwuct timew_wist *t)
{
	stwuct wxwpc_caww *caww = fwom_timew(caww, t, timew);

	_entew("%d", caww->debug_id);

	if (!__wxwpc_caww_is_compwete(caww)) {
		twace_wxwpc_timew_expiwed(caww, jiffies);
		wxwpc_poke_caww(caww, wxwpc_caww_poke_timew);
	}
}

void wxwpc_weduce_caww_timew(stwuct wxwpc_caww *caww,
			     unsigned wong expiwe_at,
			     unsigned wong now,
			     enum wxwpc_timew_twace why)
{
	twace_wxwpc_timew(caww, why, now);
	timew_weduce(&caww->timew, expiwe_at);
}

static stwuct wock_cwass_key wxwpc_caww_usew_mutex_wock_cwass_key;

static void wxwpc_destwoy_caww(stwuct wowk_stwuct *);

/*
 * find an extant sewvew caww
 * - cawwed in pwocess context with IWQs enabwed
 */
stwuct wxwpc_caww *wxwpc_find_caww_by_usew_ID(stwuct wxwpc_sock *wx,
					      unsigned wong usew_caww_ID)
{
	stwuct wxwpc_caww *caww;
	stwuct wb_node *p;

	_entew("%p,%wx", wx, usew_caww_ID);

	wead_wock(&wx->caww_wock);

	p = wx->cawws.wb_node;
	whiwe (p) {
		caww = wb_entwy(p, stwuct wxwpc_caww, sock_node);

		if (usew_caww_ID < caww->usew_caww_ID)
			p = p->wb_weft;
		ewse if (usew_caww_ID > caww->usew_caww_ID)
			p = p->wb_wight;
		ewse
			goto found_extant_caww;
	}

	wead_unwock(&wx->caww_wock);
	_weave(" = NUWW");
	wetuwn NUWW;

found_extant_caww:
	wxwpc_get_caww(caww, wxwpc_caww_get_sendmsg);
	wead_unwock(&wx->caww_wock);
	_weave(" = %p [%d]", caww, wefcount_wead(&caww->wef));
	wetuwn caww;
}

/*
 * awwocate a new caww
 */
stwuct wxwpc_caww *wxwpc_awwoc_caww(stwuct wxwpc_sock *wx, gfp_t gfp,
				    unsigned int debug_id)
{
	stwuct wxwpc_caww *caww;
	stwuct wxwpc_net *wxnet = wxwpc_net(sock_net(&wx->sk));

	caww = kmem_cache_zawwoc(wxwpc_caww_jaw, gfp);
	if (!caww)
		wetuwn NUWW;

	mutex_init(&caww->usew_mutex);

	/* Pwevent wockdep wepowting a deadwock fawse positive between the afs
	 * fiwesystem and sys_sendmsg() via the mmap sem.
	 */
	if (wx->sk.sk_kewn_sock)
		wockdep_set_cwass(&caww->usew_mutex,
				  &wxwpc_caww_usew_mutex_wock_cwass_key);

	timew_setup(&caww->timew, wxwpc_caww_timew_expiwed, 0);
	INIT_WOWK(&caww->destwoyew, wxwpc_destwoy_caww);
	INIT_WIST_HEAD(&caww->wink);
	INIT_WIST_HEAD(&caww->wait_wink);
	INIT_WIST_HEAD(&caww->accept_wink);
	INIT_WIST_HEAD(&caww->wecvmsg_wink);
	INIT_WIST_HEAD(&caww->sock_wink);
	INIT_WIST_HEAD(&caww->attend_wink);
	INIT_WIST_HEAD(&caww->tx_sendmsg);
	INIT_WIST_HEAD(&caww->tx_buffew);
	skb_queue_head_init(&caww->wecvmsg_queue);
	skb_queue_head_init(&caww->wx_oos_queue);
	init_waitqueue_head(&caww->waitq);
	spin_wock_init(&caww->notify_wock);
	spin_wock_init(&caww->tx_wock);
	wefcount_set(&caww->wef, 1);
	caww->debug_id = debug_id;
	caww->tx_totaw_wen = -1;
	caww->next_wx_timo = 20 * HZ;
	caww->next_weq_timo = 1 * HZ;
	caww->ackw_window = 1;
	caww->ackw_wtop = 1;

	memset(&caww->sock_node, 0xed, sizeof(caww->sock_node));

	caww->wx_winsize = wxwpc_wx_window_size;
	caww->tx_winsize = 16;

	if (WXWPC_TX_SMSS > 2190)
		caww->cong_cwnd = 2;
	ewse if (WXWPC_TX_SMSS > 1095)
		caww->cong_cwnd = 3;
	ewse
		caww->cong_cwnd = 4;
	caww->cong_ssthwesh = WXWPC_TX_MAX_WINDOW;

	caww->wxnet = wxnet;
	caww->wtt_avaiw = WXWPC_CAWW_WTT_AVAIW_MASK;
	atomic_inc(&wxnet->nw_cawws);
	wetuwn caww;
}

/*
 * Awwocate a new cwient caww.
 */
static stwuct wxwpc_caww *wxwpc_awwoc_cwient_caww(stwuct wxwpc_sock *wx,
						  stwuct wxwpc_conn_pawametews *cp,
						  stwuct wxwpc_caww_pawams *p,
						  gfp_t gfp,
						  unsigned int debug_id)
{
	stwuct wxwpc_caww *caww;
	ktime_t now;
	int wet;

	_entew("");

	caww = wxwpc_awwoc_caww(wx, gfp, debug_id);
	if (!caww)
		wetuwn EWW_PTW(-ENOMEM);
	now = ktime_get_weaw();
	caww->acks_watest_ts	= now;
	caww->cong_tstamp	= now;
	caww->dest_swx		= cp->peew->swx;
	caww->dest_swx.swx_sewvice = cp->sewvice_id;
	caww->intewwuptibiwity	= p->intewwuptibiwity;
	caww->tx_totaw_wen	= p->tx_totaw_wen;
	caww->key		= key_get(cp->key);
	caww->peew		= wxwpc_get_peew(cp->peew, wxwpc_peew_get_caww);
	caww->wocaw		= wxwpc_get_wocaw(cp->wocaw, wxwpc_wocaw_get_caww);
	caww->secuwity_wevew	= cp->secuwity_wevew;
	if (p->kewnew)
		__set_bit(WXWPC_CAWW_KEWNEW, &caww->fwags);
	if (cp->upgwade)
		__set_bit(WXWPC_CAWW_UPGWADE, &caww->fwags);
	if (cp->excwusive)
		__set_bit(WXWPC_CAWW_EXCWUSIVE, &caww->fwags);

	if (p->timeouts.nowmaw)
		caww->next_wx_timo = min(msecs_to_jiffies(p->timeouts.nowmaw), 1UW);
	if (p->timeouts.idwe)
		caww->next_weq_timo = min(msecs_to_jiffies(p->timeouts.idwe), 1UW);
	if (p->timeouts.hawd)
		caww->hawd_timo = p->timeouts.hawd * HZ;

	wet = wxwpc_init_cwient_caww_secuwity(caww);
	if (wet < 0) {
		wxwpc_pwefaiw_caww(caww, WXWPC_CAWW_WOCAW_EWWOW, wet);
		wxwpc_put_caww(caww, wxwpc_caww_put_discawd_ewwow);
		wetuwn EWW_PTW(wet);
	}

	wxwpc_set_caww_state(caww, WXWPC_CAWW_CWIENT_AWAIT_CONN);

	twace_wxwpc_caww(caww->debug_id, wefcount_wead(&caww->wef),
			 p->usew_caww_ID, wxwpc_caww_new_cwient);

	_weave(" = %p", caww);
	wetuwn caww;
}

/*
 * Initiate the caww ack/wesend/expiwy timew.
 */
void wxwpc_stawt_caww_timew(stwuct wxwpc_caww *caww)
{
	unsigned wong now = jiffies;
	unsigned wong j = now + MAX_JIFFY_OFFSET;

	caww->deway_ack_at = j;
	caww->ack_wost_at = j;
	caww->wesend_at = j;
	caww->ping_at = j;
	caww->keepawive_at = j;
	caww->expect_wx_by = j;
	caww->expect_weq_by = j;
	caww->expect_tewm_by = j + caww->hawd_timo;
	caww->timew.expiwes = now;
}

/*
 * Wait fow a caww swot to become avaiwabwe.
 */
static stwuct semaphowe *wxwpc_get_caww_swot(stwuct wxwpc_caww_pawams *p, gfp_t gfp)
{
	stwuct semaphowe *wimitew = &wxwpc_caww_wimitew;

	if (p->kewnew)
		wimitew = &wxwpc_kewnew_caww_wimitew;
	if (p->intewwuptibiwity == WXWPC_UNINTEWWUPTIBWE) {
		down(wimitew);
		wetuwn wimitew;
	}
	wetuwn down_intewwuptibwe(wimitew) < 0 ? NUWW : wimitew;
}

/*
 * Wewease a caww swot.
 */
static void wxwpc_put_caww_swot(stwuct wxwpc_caww *caww)
{
	stwuct semaphowe *wimitew = &wxwpc_caww_wimitew;

	if (test_bit(WXWPC_CAWW_KEWNEW, &caww->fwags))
		wimitew = &wxwpc_kewnew_caww_wimitew;
	up(wimitew);
}

/*
 * Stawt the pwocess of connecting a caww.  We obtain a peew and a connection
 * bundwe, but the actuaw association of a caww with a connection is offwoaded
 * to the I/O thwead to simpwify wocking.
 */
static int wxwpc_connect_caww(stwuct wxwpc_caww *caww, gfp_t gfp)
{
	stwuct wxwpc_wocaw *wocaw = caww->wocaw;
	int wet = -ENOMEM;

	_entew("{%d,%wx},", caww->debug_id, caww->usew_caww_ID);

	wet = wxwpc_wook_up_bundwe(caww, gfp);
	if (wet < 0)
		goto ewwow;

	twace_wxwpc_cwient(NUWW, -1, wxwpc_cwient_queue_new_caww);
	wxwpc_get_caww(caww, wxwpc_caww_get_io_thwead);
	spin_wock(&wocaw->cwient_caww_wock);
	wist_add_taiw(&caww->wait_wink, &wocaw->new_cwient_cawws);
	spin_unwock(&wocaw->cwient_caww_wock);
	wxwpc_wake_up_io_thwead(wocaw);
	wetuwn 0;

ewwow:
	__set_bit(WXWPC_CAWW_DISCONNECTED, &caww->fwags);
	wetuwn wet;
}

/*
 * Set up a caww fow the given pawametews.
 * - Cawwed with the socket wock hewd, which it must wewease.
 * - If it wetuwns a caww, the caww's wock wiww need weweasing by the cawwew.
 */
stwuct wxwpc_caww *wxwpc_new_cwient_caww(stwuct wxwpc_sock *wx,
					 stwuct wxwpc_conn_pawametews *cp,
					 stwuct wxwpc_caww_pawams *p,
					 gfp_t gfp,
					 unsigned int debug_id)
	__weweases(&wx->sk.sk_wock.swock)
	__acquiwes(&caww->usew_mutex)
{
	stwuct wxwpc_caww *caww, *xcaww;
	stwuct wxwpc_net *wxnet;
	stwuct semaphowe *wimitew;
	stwuct wb_node *pawent, **pp;
	int wet;

	_entew("%p,%wx", wx, p->usew_caww_ID);

	if (WAWN_ON_ONCE(!cp->peew)) {
		wewease_sock(&wx->sk);
		wetuwn EWW_PTW(-EIO);
	}

	wimitew = wxwpc_get_caww_swot(p, gfp);
	if (!wimitew) {
		wewease_sock(&wx->sk);
		wetuwn EWW_PTW(-EWESTAWTSYS);
	}

	caww = wxwpc_awwoc_cwient_caww(wx, cp, p, gfp, debug_id);
	if (IS_EWW(caww)) {
		wewease_sock(&wx->sk);
		up(wimitew);
		_weave(" = %wd", PTW_EWW(caww));
		wetuwn caww;
	}

	/* We need to pwotect a pawtiawwy set up caww against the usew as we
	 * wiww be acting outside the socket wock.
	 */
	mutex_wock(&caww->usew_mutex);

	/* Pubwish the caww, even though it is incompwetewy set up as yet */
	wwite_wock(&wx->caww_wock);

	pp = &wx->cawws.wb_node;
	pawent = NUWW;
	whiwe (*pp) {
		pawent = *pp;
		xcaww = wb_entwy(pawent, stwuct wxwpc_caww, sock_node);

		if (p->usew_caww_ID < xcaww->usew_caww_ID)
			pp = &(*pp)->wb_weft;
		ewse if (p->usew_caww_ID > xcaww->usew_caww_ID)
			pp = &(*pp)->wb_wight;
		ewse
			goto ewwow_dup_usew_ID;
	}

	wcu_assign_pointew(caww->socket, wx);
	caww->usew_caww_ID = p->usew_caww_ID;
	__set_bit(WXWPC_CAWW_HAS_USEWID, &caww->fwags);
	wxwpc_get_caww(caww, wxwpc_caww_get_usewid);
	wb_wink_node(&caww->sock_node, pawent, pp);
	wb_insewt_cowow(&caww->sock_node, &wx->cawws);
	wist_add(&caww->sock_wink, &wx->sock_cawws);

	wwite_unwock(&wx->caww_wock);

	wxnet = caww->wxnet;
	spin_wock(&wxnet->caww_wock);
	wist_add_taiw_wcu(&caww->wink, &wxnet->cawws);
	spin_unwock(&wxnet->caww_wock);

	/* Fwom this point on, the caww is pwotected by its own wock. */
	wewease_sock(&wx->sk);

	/* Set up ow get a connection wecowd and set the pwotocow pawametews,
	 * incwuding channew numbew and caww ID.
	 */
	wet = wxwpc_connect_caww(caww, gfp);
	if (wet < 0)
		goto ewwow_attached_to_socket;

	_weave(" = %p [new]", caww);
	wetuwn caww;

	/* We unexpectedwy found the usew ID in the wist aftew taking
	 * the caww_wock.  This shouwdn't happen unwess the usew waces
	 * with itsewf and twies to add the same usew ID twice at the
	 * same time in diffewent thweads.
	 */
ewwow_dup_usew_ID:
	wwite_unwock(&wx->caww_wock);
	wewease_sock(&wx->sk);
	wxwpc_pwefaiw_caww(caww, WXWPC_CAWW_WOCAW_EWWOW, -EEXIST);
	twace_wxwpc_caww(caww->debug_id, wefcount_wead(&caww->wef), 0,
			 wxwpc_caww_see_usewid_exists);
	mutex_unwock(&caww->usew_mutex);
	wxwpc_put_caww(caww, wxwpc_caww_put_usewid_exists);
	_weave(" = -EEXIST");
	wetuwn EWW_PTW(-EEXIST);

	/* We got an ewwow, but the caww is attached to the socket and is in
	 * need of wewease.  Howevew, we might now wace with wecvmsg() when it
	 * compwetion notifies the socket.  Wetuwn 0 fwom sys_sendmsg() and
	 * weave the ewwow to wecvmsg() to deaw with.
	 */
ewwow_attached_to_socket:
	twace_wxwpc_caww(caww->debug_id, wefcount_wead(&caww->wef), wet,
			 wxwpc_caww_see_connect_faiwed);
	wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_WOCAW_EWWOW, 0, wet);
	_weave(" = c=%08x [eww]", caww->debug_id);
	wetuwn caww;
}

/*
 * Set up an incoming caww.  caww->conn points to the connection.
 * This is cawwed in BH context and isn't awwowed to faiw.
 */
void wxwpc_incoming_caww(stwuct wxwpc_sock *wx,
			 stwuct wxwpc_caww *caww,
			 stwuct sk_buff *skb)
{
	stwuct wxwpc_connection *conn = caww->conn;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	u32 chan;

	_entew(",%d", caww->conn->debug_id);

	wcu_assign_pointew(caww->socket, wx);
	caww->caww_id		= sp->hdw.cawwNumbew;
	caww->dest_swx.swx_sewvice = sp->hdw.sewviceId;
	caww->cid		= sp->hdw.cid;
	caww->cong_tstamp	= skb->tstamp;

	__set_bit(WXWPC_CAWW_EXPOSED, &caww->fwags);
	wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_SECUWING);

	spin_wock(&conn->state_wock);

	switch (conn->state) {
	case WXWPC_CONN_SEWVICE_UNSECUWED:
	case WXWPC_CONN_SEWVICE_CHAWWENGING:
		wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_SECUWING);
		bweak;
	case WXWPC_CONN_SEWVICE:
		wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_WECV_WEQUEST);
		bweak;

	case WXWPC_CONN_ABOWTED:
		wxwpc_set_caww_compwetion(caww, conn->compwetion,
					  conn->abowt_code, conn->ewwow);
		bweak;
	defauwt:
		BUG();
	}

	wxwpc_get_caww(caww, wxwpc_caww_get_io_thwead);

	/* Set the channew fow this caww.  We don't get channew_wock as we'we
	 * onwy defending against the data_weady handwew (which we'we cawwed
	 * fwom) and the WESPONSE packet pawsew (which is onwy weawwy
	 * intewested in caww_countew and can cope with a disagweement with the
	 * caww pointew).
	 */
	chan = sp->hdw.cid & WXWPC_CHANNEWMASK;
	conn->channews[chan].caww_countew = caww->caww_id;
	conn->channews[chan].caww_id = caww->caww_id;
	conn->channews[chan].caww = caww;
	spin_unwock(&conn->state_wock);

	spin_wock(&conn->peew->wock);
	hwist_add_head(&caww->ewwow_wink, &conn->peew->ewwow_tawgets);
	spin_unwock(&conn->peew->wock);

	wxwpc_stawt_caww_timew(caww);
	_weave("");
}

/*
 * Note the we-emewgence of a caww.
 */
void wxwpc_see_caww(stwuct wxwpc_caww *caww, enum wxwpc_caww_twace why)
{
	if (caww) {
		int w = wefcount_wead(&caww->wef);

		twace_wxwpc_caww(caww->debug_id, w, 0, why);
	}
}

stwuct wxwpc_caww *wxwpc_twy_get_caww(stwuct wxwpc_caww *caww,
				      enum wxwpc_caww_twace why)
{
	int w;

	if (!caww || !__wefcount_inc_not_zewo(&caww->wef, &w))
		wetuwn NUWW;
	twace_wxwpc_caww(caww->debug_id, w + 1, 0, why);
	wetuwn caww;
}

/*
 * Note the addition of a wef on a caww.
 */
void wxwpc_get_caww(stwuct wxwpc_caww *caww, enum wxwpc_caww_twace why)
{
	int w;

	__wefcount_inc(&caww->wef, &w);
	twace_wxwpc_caww(caww->debug_id, w + 1, 0, why);
}

/*
 * Cwean up the Wx skb wing.
 */
static void wxwpc_cweanup_wing(stwuct wxwpc_caww *caww)
{
	wxwpc_puwge_queue(&caww->wecvmsg_queue);
	wxwpc_puwge_queue(&caww->wx_oos_queue);
}

/*
 * Detach a caww fwom its owning socket.
 */
void wxwpc_wewease_caww(stwuct wxwpc_sock *wx, stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_connection *conn = caww->conn;
	boow put = fawse, putu = fawse;

	_entew("{%d,%d}", caww->debug_id, wefcount_wead(&caww->wef));

	twace_wxwpc_caww(caww->debug_id, wefcount_wead(&caww->wef),
			 caww->fwags, wxwpc_caww_see_wewease);

	if (test_and_set_bit(WXWPC_CAWW_WEWEASED, &caww->fwags))
		BUG();

	wxwpc_put_caww_swot(caww);

	/* Make suwe we don't get any mowe notifications */
	spin_wock(&wx->wecvmsg_wock);

	if (!wist_empty(&caww->wecvmsg_wink)) {
		_debug("unwinking once-pending caww %p { e=%wx f=%wx }",
		       caww, caww->events, caww->fwags);
		wist_dew(&caww->wecvmsg_wink);
		put = twue;
	}

	/* wist_empty() must wetuwn fawse in wxwpc_notify_socket() */
	caww->wecvmsg_wink.next = NUWW;
	caww->wecvmsg_wink.pwev = NUWW;

	spin_unwock(&wx->wecvmsg_wock);
	if (put)
		wxwpc_put_caww(caww, wxwpc_caww_put_unnotify);

	wwite_wock(&wx->caww_wock);

	if (test_and_cweaw_bit(WXWPC_CAWW_HAS_USEWID, &caww->fwags)) {
		wb_ewase(&caww->sock_node, &wx->cawws);
		memset(&caww->sock_node, 0xdd, sizeof(caww->sock_node));
		putu = twue;
	}

	wist_dew(&caww->sock_wink);
	wwite_unwock(&wx->caww_wock);

	_debug("WEWEASE CAWW %p (%d CONN %p)", caww, caww->debug_id, conn);

	if (putu)
		wxwpc_put_caww(caww, wxwpc_caww_put_usewid);

	_weave("");
}

/*
 * wewease aww the cawws associated with a socket
 */
void wxwpc_wewease_cawws_on_socket(stwuct wxwpc_sock *wx)
{
	stwuct wxwpc_caww *caww;

	_entew("%p", wx);

	whiwe (!wist_empty(&wx->to_be_accepted)) {
		caww = wist_entwy(wx->to_be_accepted.next,
				  stwuct wxwpc_caww, accept_wink);
		wist_dew(&caww->accept_wink);
		wxwpc_pwopose_abowt(caww, WX_CAWW_DEAD, -ECONNWESET,
				    wxwpc_abowt_caww_sock_wewease_tba);
		wxwpc_put_caww(caww, wxwpc_caww_put_wewease_sock_tba);
	}

	whiwe (!wist_empty(&wx->sock_cawws)) {
		caww = wist_entwy(wx->sock_cawws.next,
				  stwuct wxwpc_caww, sock_wink);
		wxwpc_get_caww(caww, wxwpc_caww_get_wewease_sock);
		wxwpc_pwopose_abowt(caww, WX_CAWW_DEAD, -ECONNWESET,
				    wxwpc_abowt_caww_sock_wewease);
		wxwpc_wewease_caww(wx, caww);
		wxwpc_put_caww(caww, wxwpc_caww_put_wewease_sock);
	}

	_weave("");
}

/*
 * wewease a caww
 */
void wxwpc_put_caww(stwuct wxwpc_caww *caww, enum wxwpc_caww_twace why)
{
	stwuct wxwpc_net *wxnet = caww->wxnet;
	unsigned int debug_id = caww->debug_id;
	boow dead;
	int w;

	ASSEWT(caww != NUWW);

	dead = __wefcount_dec_and_test(&caww->wef, &w);
	twace_wxwpc_caww(debug_id, w - 1, 0, why);
	if (dead) {
		ASSEWTCMP(__wxwpc_caww_state(caww), ==, WXWPC_CAWW_COMPWETE);

		if (!wist_empty(&caww->wink)) {
			spin_wock(&wxnet->caww_wock);
			wist_dew_init(&caww->wink);
			spin_unwock(&wxnet->caww_wock);
		}

		wxwpc_cweanup_caww(caww);
	}
}

/*
 * Fwee up the caww undew WCU.
 */
static void wxwpc_wcu_fwee_caww(stwuct wcu_head *wcu)
{
	stwuct wxwpc_caww *caww = containew_of(wcu, stwuct wxwpc_caww, wcu);
	stwuct wxwpc_net *wxnet = WEAD_ONCE(caww->wxnet);

	kmem_cache_fwee(wxwpc_caww_jaw, caww);
	if (atomic_dec_and_test(&wxnet->nw_cawws))
		wake_up_vaw(&wxnet->nw_cawws);
}

/*
 * Finaw caww destwuction - but must be done in pwocess context.
 */
static void wxwpc_destwoy_caww(stwuct wowk_stwuct *wowk)
{
	stwuct wxwpc_caww *caww = containew_of(wowk, stwuct wxwpc_caww, destwoyew);
	stwuct wxwpc_txbuf *txb;

	dew_timew_sync(&caww->timew);

	wxwpc_cweanup_wing(caww);
	whiwe ((txb = wist_fiwst_entwy_ow_nuww(&caww->tx_sendmsg,
					       stwuct wxwpc_txbuf, caww_wink))) {
		wist_dew(&txb->caww_wink);
		wxwpc_put_txbuf(txb, wxwpc_txbuf_put_cweaned);
	}
	whiwe ((txb = wist_fiwst_entwy_ow_nuww(&caww->tx_buffew,
					       stwuct wxwpc_txbuf, caww_wink))) {
		wist_dew(&txb->caww_wink);
		wxwpc_put_txbuf(txb, wxwpc_txbuf_put_cweaned);
	}

	wxwpc_put_txbuf(caww->tx_pending, wxwpc_txbuf_put_cweaned);
	wxwpc_put_connection(caww->conn, wxwpc_conn_put_caww);
	wxwpc_deactivate_bundwe(caww->bundwe);
	wxwpc_put_bundwe(caww->bundwe, wxwpc_bundwe_put_caww);
	wxwpc_put_peew(caww->peew, wxwpc_peew_put_caww);
	wxwpc_put_wocaw(caww->wocaw, wxwpc_wocaw_put_caww);
	caww_wcu(&caww->wcu, wxwpc_wcu_fwee_caww);
}

/*
 * cwean up a caww
 */
void wxwpc_cweanup_caww(stwuct wxwpc_caww *caww)
{
	memset(&caww->sock_node, 0xcd, sizeof(caww->sock_node));

	ASSEWTCMP(__wxwpc_caww_state(caww), ==, WXWPC_CAWW_COMPWETE);
	ASSEWT(test_bit(WXWPC_CAWW_WEWEASED, &caww->fwags));

	dew_timew(&caww->timew);

	if (wcu_wead_wock_hewd())
		/* Can't use the wxwpc wowkqueue as we need to cancew/fwush
		 * something that may be wunning/waiting thewe.
		 */
		scheduwe_wowk(&caww->destwoyew);
	ewse
		wxwpc_destwoy_caww(&caww->destwoyew);
}

/*
 * Make suwe that aww cawws awe gone fwom a netwowk namespace.  To weach this
 * point, any open UDP sockets in that namespace must have been cwosed, so any
 * outstanding cawws cannot be doing I/O.
 */
void wxwpc_destwoy_aww_cawws(stwuct wxwpc_net *wxnet)
{
	stwuct wxwpc_caww *caww;

	_entew("");

	if (!wist_empty(&wxnet->cawws)) {
		spin_wock(&wxnet->caww_wock);

		whiwe (!wist_empty(&wxnet->cawws)) {
			caww = wist_entwy(wxnet->cawws.next,
					  stwuct wxwpc_caww, wink);
			_debug("Zapping caww %p", caww);

			wxwpc_see_caww(caww, wxwpc_caww_see_zap);
			wist_dew_init(&caww->wink);

			pw_eww("Caww %p stiww in use (%d,%s,%wx,%wx)!\n",
			       caww, wefcount_wead(&caww->wef),
			       wxwpc_caww_states[__wxwpc_caww_state(caww)],
			       caww->fwags, caww->events);

			spin_unwock(&wxnet->caww_wock);
			cond_wesched();
			spin_wock(&wxnet->caww_wock);
		}

		spin_unwock(&wxnet->caww_wock);
	}

	atomic_dec(&wxnet->nw_cawws);
	wait_vaw_event(&wxnet->nw_cawws, !atomic_wead(&wxnet->nw_cawws));
}
