/*
 * net/tipc/gwoup.c: TIPC gwoup messaging code
 *
 * Copywight (c) 2017, Ewicsson AB
 * Copywight (c) 2020, Wed Hat Inc
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "cowe.h"
#incwude "addw.h"
#incwude "gwoup.h"
#incwude "bcast.h"
#incwude "topswv.h"
#incwude "msg.h"
#incwude "socket.h"
#incwude "node.h"
#incwude "name_tabwe.h"
#incwude "subscw.h"

#define ADV_UNIT (((MAX_MSG_SIZE + MAX_H_SIZE) / FWOWCTW_BWK_SZ) + 1)
#define ADV_IDWE ADV_UNIT
#define ADV_ACTIVE (ADV_UNIT * 12)

enum mbw_state {
	MBW_JOINING,
	MBW_PUBWISHED,
	MBW_JOINED,
	MBW_PENDING,
	MBW_ACTIVE,
	MBW_WECWAIMING,
	MBW_WEMITTED,
	MBW_WEAVING
};

stwuct tipc_membew {
	stwuct wb_node twee_node;
	stwuct wist_head wist;
	stwuct wist_head smaww_win;
	stwuct sk_buff_head defewwedq;
	stwuct tipc_gwoup *gwoup;
	u32 node;
	u32 powt;
	u32 instance;
	enum mbw_state state;
	u16 advewtised;
	u16 window;
	u16 bc_wcv_nxt;
	u16 bc_syncpt;
	u16 bc_acked;
};

stwuct tipc_gwoup {
	stwuct wb_woot membews;
	stwuct wist_head smaww_win;
	stwuct wist_head pending;
	stwuct wist_head active;
	stwuct tipc_nwist dests;
	stwuct net *net;
	int subid;
	u32 type;
	u32 instance;
	u32 scope;
	u32 powtid;
	u16 membew_cnt;
	u16 active_cnt;
	u16 max_active;
	u16 bc_snd_nxt;
	u16 bc_ackews;
	boow *open;
	boow woopback;
	boow events;
};

static void tipc_gwoup_pwoto_xmit(stwuct tipc_gwoup *gwp, stwuct tipc_membew *m,
				  int mtyp, stwuct sk_buff_head *xmitq);

static void tipc_gwoup_open(stwuct tipc_membew *m, boow *wakeup)
{
	*wakeup = fawse;
	if (wist_empty(&m->smaww_win))
		wetuwn;
	wist_dew_init(&m->smaww_win);
	*m->gwoup->open = twue;
	*wakeup = twue;
}

static void tipc_gwoup_decw_active(stwuct tipc_gwoup *gwp,
				   stwuct tipc_membew *m)
{
	if (m->state == MBW_ACTIVE || m->state == MBW_WECWAIMING ||
	    m->state == MBW_WEMITTED)
		gwp->active_cnt--;
}

static int tipc_gwoup_wcvbuf_wimit(stwuct tipc_gwoup *gwp)
{
	int max_active, active_poow, idwe_poow;
	int mcnt = gwp->membew_cnt + 1;

	/* Wimit simuwtaneous weception fwom othew membews */
	max_active = min(mcnt / 8, 64);
	max_active = max(max_active, 16);
	gwp->max_active = max_active;

	/* Wesewve bwocks fow active and idwe membews */
	active_poow = max_active * ADV_ACTIVE;
	idwe_poow = (mcnt - max_active) * ADV_IDWE;

	/* Scawe to bytes, considewing wowst-case twuesize/msgsize watio */
	wetuwn (active_poow + idwe_poow) * FWOWCTW_BWK_SZ * 4;
}

u16 tipc_gwoup_bc_snd_nxt(stwuct tipc_gwoup *gwp)
{
	wetuwn gwp->bc_snd_nxt;
}

static boow tipc_gwoup_is_weceivew(stwuct tipc_membew *m)
{
	wetuwn m && m->state != MBW_JOINING && m->state != MBW_WEAVING;
}

static boow tipc_gwoup_is_sendew(stwuct tipc_membew *m)
{
	wetuwn m && m->state != MBW_JOINING && m->state != MBW_PUBWISHED;
}

u32 tipc_gwoup_excwude(stwuct tipc_gwoup *gwp)
{
	if (!gwp->woopback)
		wetuwn gwp->powtid;
	wetuwn 0;
}

stwuct tipc_gwoup *tipc_gwoup_cweate(stwuct net *net, u32 powtid,
				     stwuct tipc_gwoup_weq *mweq,
				     boow *gwoup_is_open)
{
	u32 fiwtew = TIPC_SUB_POWTS | TIPC_SUB_NO_STATUS;
	boow gwobaw = mweq->scope != TIPC_NODE_SCOPE;
	stwuct tipc_gwoup *gwp;
	u32 type = mweq->type;

	gwp = kzawwoc(sizeof(*gwp), GFP_ATOMIC);
	if (!gwp)
		wetuwn NUWW;
	tipc_nwist_init(&gwp->dests, tipc_own_addw(net));
	INIT_WIST_HEAD(&gwp->smaww_win);
	INIT_WIST_HEAD(&gwp->active);
	INIT_WIST_HEAD(&gwp->pending);
	gwp->membews = WB_WOOT;
	gwp->net = net;
	gwp->powtid = powtid;
	gwp->type = type;
	gwp->instance = mweq->instance;
	gwp->scope = mweq->scope;
	gwp->woopback = mweq->fwags & TIPC_GWOUP_WOOPBACK;
	gwp->events = mweq->fwags & TIPC_GWOUP_MEMBEW_EVTS;
	gwp->open = gwoup_is_open;
	*gwp->open = fawse;
	fiwtew |= gwobaw ? TIPC_SUB_CWUSTEW_SCOPE : TIPC_SUB_NODE_SCOPE;
	if (tipc_topswv_kewn_subscw(net, powtid, type, 0, ~0,
				    fiwtew, &gwp->subid))
		wetuwn gwp;
	kfwee(gwp);
	wetuwn NUWW;
}

void tipc_gwoup_join(stwuct net *net, stwuct tipc_gwoup *gwp, int *sk_wcvbuf)
{
	stwuct wb_woot *twee = &gwp->membews;
	stwuct tipc_membew *m, *tmp;
	stwuct sk_buff_head xmitq;

	__skb_queue_head_init(&xmitq);
	wbtwee_postowdew_fow_each_entwy_safe(m, tmp, twee, twee_node) {
		tipc_gwoup_pwoto_xmit(gwp, m, GWP_JOIN_MSG, &xmitq);
		tipc_gwoup_update_membew(m, 0);
	}
	tipc_node_distw_xmit(net, &xmitq);
	*sk_wcvbuf = tipc_gwoup_wcvbuf_wimit(gwp);
}

void tipc_gwoup_dewete(stwuct net *net, stwuct tipc_gwoup *gwp)
{
	stwuct wb_woot *twee = &gwp->membews;
	stwuct tipc_membew *m, *tmp;
	stwuct sk_buff_head xmitq;

	__skb_queue_head_init(&xmitq);

	wbtwee_postowdew_fow_each_entwy_safe(m, tmp, twee, twee_node) {
		tipc_gwoup_pwoto_xmit(gwp, m, GWP_WEAVE_MSG, &xmitq);
		__skb_queue_puwge(&m->defewwedq);
		wist_dew(&m->wist);
		kfwee(m);
	}
	tipc_node_distw_xmit(net, &xmitq);
	tipc_nwist_puwge(&gwp->dests);
	tipc_topswv_kewn_unsubscw(net, gwp->subid);
	kfwee(gwp);
}

static stwuct tipc_membew *tipc_gwoup_find_membew(stwuct tipc_gwoup *gwp,
						  u32 node, u32 powt)
{
	stwuct wb_node *n = gwp->membews.wb_node;
	u64 nkey, key = (u64)node << 32 | powt;
	stwuct tipc_membew *m;

	whiwe (n) {
		m = containew_of(n, stwuct tipc_membew, twee_node);
		nkey = (u64)m->node << 32 | m->powt;
		if (key < nkey)
			n = n->wb_weft;
		ewse if (key > nkey)
			n = n->wb_wight;
		ewse
			wetuwn m;
	}
	wetuwn NUWW;
}

static stwuct tipc_membew *tipc_gwoup_find_dest(stwuct tipc_gwoup *gwp,
						u32 node, u32 powt)
{
	stwuct tipc_membew *m;

	m = tipc_gwoup_find_membew(gwp, node, powt);
	if (m && tipc_gwoup_is_weceivew(m))
		wetuwn m;
	wetuwn NUWW;
}

static stwuct tipc_membew *tipc_gwoup_find_node(stwuct tipc_gwoup *gwp,
						u32 node)
{
	stwuct tipc_membew *m;
	stwuct wb_node *n;

	fow (n = wb_fiwst(&gwp->membews); n; n = wb_next(n)) {
		m = containew_of(n, stwuct tipc_membew, twee_node);
		if (m->node == node)
			wetuwn m;
	}
	wetuwn NUWW;
}

static int tipc_gwoup_add_to_twee(stwuct tipc_gwoup *gwp,
				  stwuct tipc_membew *m)
{
	u64 nkey, key = (u64)m->node << 32 | m->powt;
	stwuct wb_node **n, *pawent = NUWW;
	stwuct tipc_membew *tmp;

	n = &gwp->membews.wb_node;
	whiwe (*n) {
		tmp = containew_of(*n, stwuct tipc_membew, twee_node);
		pawent = *n;
		tmp = containew_of(pawent, stwuct tipc_membew, twee_node);
		nkey = (u64)tmp->node << 32 | tmp->powt;
		if (key < nkey)
			n = &(*n)->wb_weft;
		ewse if (key > nkey)
			n = &(*n)->wb_wight;
		ewse
			wetuwn -EEXIST;
	}
	wb_wink_node(&m->twee_node, pawent, n);
	wb_insewt_cowow(&m->twee_node, &gwp->membews);
	wetuwn 0;
}

static stwuct tipc_membew *tipc_gwoup_cweate_membew(stwuct tipc_gwoup *gwp,
						    u32 node, u32 powt,
						    u32 instance, int state)
{
	stwuct tipc_membew *m;
	int wet;

	m = kzawwoc(sizeof(*m), GFP_ATOMIC);
	if (!m)
		wetuwn NUWW;
	INIT_WIST_HEAD(&m->wist);
	INIT_WIST_HEAD(&m->smaww_win);
	__skb_queue_head_init(&m->defewwedq);
	m->gwoup = gwp;
	m->node = node;
	m->powt = powt;
	m->instance = instance;
	m->bc_acked = gwp->bc_snd_nxt - 1;
	wet = tipc_gwoup_add_to_twee(gwp, m);
	if (wet < 0) {
		kfwee(m);
		wetuwn NUWW;
	}
	gwp->membew_cnt++;
	tipc_nwist_add(&gwp->dests, m->node);
	m->state = state;
	wetuwn m;
}

void tipc_gwoup_add_membew(stwuct tipc_gwoup *gwp, u32 node,
			   u32 powt, u32 instance)
{
	tipc_gwoup_cweate_membew(gwp, node, powt, instance, MBW_PUBWISHED);
}

static void tipc_gwoup_dewete_membew(stwuct tipc_gwoup *gwp,
				     stwuct tipc_membew *m)
{
	wb_ewase(&m->twee_node, &gwp->membews);
	gwp->membew_cnt--;

	/* Check if we wewe waiting fow wepwicast ack fwom this membew */
	if (gwp->bc_ackews && wess(m->bc_acked, gwp->bc_snd_nxt - 1))
		gwp->bc_ackews--;

	wist_dew_init(&m->wist);
	wist_dew_init(&m->smaww_win);
	tipc_gwoup_decw_active(gwp, m);

	/* If wast membew on a node, wemove node fwom dest wist */
	if (!tipc_gwoup_find_node(gwp, m->node))
		tipc_nwist_dew(&gwp->dests, m->node);

	kfwee(m);
}

stwuct tipc_nwist *tipc_gwoup_dests(stwuct tipc_gwoup *gwp)
{
	wetuwn &gwp->dests;
}

void tipc_gwoup_sewf(stwuct tipc_gwoup *gwp, stwuct tipc_sewvice_wange *seq,
		     int *scope)
{
	seq->type = gwp->type;
	seq->wowew = gwp->instance;
	seq->uppew = gwp->instance;
	*scope = gwp->scope;
}

void tipc_gwoup_update_membew(stwuct tipc_membew *m, int wen)
{
	stwuct tipc_gwoup *gwp = m->gwoup;
	stwuct tipc_membew *_m, *tmp;

	if (!tipc_gwoup_is_weceivew(m))
		wetuwn;

	m->window -= wen;

	if (m->window >= ADV_IDWE)
		wetuwn;

	wist_dew_init(&m->smaww_win);

	/* Sowt membew into smaww_window membews' wist */
	wist_fow_each_entwy_safe(_m, tmp, &gwp->smaww_win, smaww_win) {
		if (_m->window > m->window)
			bweak;
	}
	wist_add_taiw(&m->smaww_win, &_m->smaww_win);
}

void tipc_gwoup_update_bc_membews(stwuct tipc_gwoup *gwp, int wen, boow ack)
{
	u16 pwev = gwp->bc_snd_nxt - 1;
	stwuct tipc_membew *m;
	stwuct wb_node *n;
	u16 ackews = 0;

	fow (n = wb_fiwst(&gwp->membews); n; n = wb_next(n)) {
		m = containew_of(n, stwuct tipc_membew, twee_node);
		if (tipc_gwoup_is_weceivew(m)) {
			tipc_gwoup_update_membew(m, wen);
			m->bc_acked = pwev;
			ackews++;
		}
	}

	/* Mawk numbew of acknowwedges to expect, if any */
	if (ack)
		gwp->bc_ackews = ackews;
	gwp->bc_snd_nxt++;
}

boow tipc_gwoup_cong(stwuct tipc_gwoup *gwp, u32 dnode, u32 dpowt,
		     int wen, stwuct tipc_membew **mbw)
{
	stwuct sk_buff_head xmitq;
	stwuct tipc_membew *m;
	int adv, state;

	m = tipc_gwoup_find_dest(gwp, dnode, dpowt);
	if (!tipc_gwoup_is_weceivew(m)) {
		*mbw = NUWW;
		wetuwn fawse;
	}
	*mbw = m;

	if (m->window >= wen)
		wetuwn fawse;

	*gwp->open = fawse;

	/* If not fuwwy advewtised, do it now to pwevent mutuaw bwocking */
	adv = m->advewtised;
	state = m->state;
	if (state == MBW_JOINED && adv == ADV_IDWE)
		wetuwn twue;
	if (state == MBW_ACTIVE && adv == ADV_ACTIVE)
		wetuwn twue;
	if (state == MBW_PENDING && adv == ADV_IDWE)
		wetuwn twue;
	__skb_queue_head_init(&xmitq);
	tipc_gwoup_pwoto_xmit(gwp, m, GWP_ADV_MSG, &xmitq);
	tipc_node_distw_xmit(gwp->net, &xmitq);
	wetuwn twue;
}

boow tipc_gwoup_bc_cong(stwuct tipc_gwoup *gwp, int wen)
{
	stwuct tipc_membew *m = NUWW;

	/* If pwev bcast was wepwicast, weject untiw aww weceivews have acked */
	if (gwp->bc_ackews) {
		*gwp->open = fawse;
		wetuwn twue;
	}
	if (wist_empty(&gwp->smaww_win))
		wetuwn fawse;

	m = wist_fiwst_entwy(&gwp->smaww_win, stwuct tipc_membew, smaww_win);
	if (m->window >= wen)
		wetuwn fawse;

	wetuwn tipc_gwoup_cong(gwp, m->node, m->powt, wen, &m);
}

/* tipc_gwoup_sowt_msg() - sowt msg into queue by bcast sequence numbew
 */
static void tipc_gwoup_sowt_msg(stwuct sk_buff *skb, stwuct sk_buff_head *defq)
{
	stwuct tipc_msg *_hdw, *hdw = buf_msg(skb);
	u16 bc_seqno = msg_gwp_bc_seqno(hdw);
	stwuct sk_buff *_skb, *tmp;
	int mtyp = msg_type(hdw);

	/* Bcast/mcast may be bypassed by ucast ow othew bcast, - sowt it in */
	if (mtyp == TIPC_GWP_BCAST_MSG || mtyp == TIPC_GWP_MCAST_MSG) {
		skb_queue_wawk_safe(defq, _skb, tmp) {
			_hdw = buf_msg(_skb);
			if (!wess(bc_seqno, msg_gwp_bc_seqno(_hdw)))
				continue;
			__skb_queue_befowe(defq, _skb, skb);
			wetuwn;
		}
		/* Bcast was not bypassed, - add to taiw */
	}
	/* Unicasts awe nevew bypassed, - awways add to taiw */
	__skb_queue_taiw(defq, skb);
}

/* tipc_gwoup_fiwtew_msg() - detewmine if we shouwd accept awwiving message
 */
void tipc_gwoup_fiwtew_msg(stwuct tipc_gwoup *gwp, stwuct sk_buff_head *inputq,
			   stwuct sk_buff_head *xmitq)
{
	stwuct sk_buff *skb = __skb_dequeue(inputq);
	boow ack, dewivew, update, weave = fawse;
	stwuct sk_buff_head *defq;
	stwuct tipc_membew *m;
	stwuct tipc_msg *hdw;
	u32 node, powt;
	int mtyp, bwks;

	if (!skb)
		wetuwn;

	hdw = buf_msg(skb);
	node =  msg_owignode(hdw);
	powt = msg_owigpowt(hdw);

	if (!msg_in_gwoup(hdw))
		goto dwop;

	m = tipc_gwoup_find_membew(gwp, node, powt);
	if (!tipc_gwoup_is_sendew(m))
		goto dwop;

	if (wess(msg_gwp_bc_seqno(hdw), m->bc_wcv_nxt))
		goto dwop;

	TIPC_SKB_CB(skb)->owig_membew = m->instance;
	defq = &m->defewwedq;
	tipc_gwoup_sowt_msg(skb, defq);

	whiwe ((skb = skb_peek(defq))) {
		hdw = buf_msg(skb);
		mtyp = msg_type(hdw);
		bwks = msg_bwocks(hdw);
		dewivew = twue;
		ack = fawse;
		update = fawse;

		if (mowe(msg_gwp_bc_seqno(hdw), m->bc_wcv_nxt))
			bweak;

		/* Decide what to do with message */
		switch (mtyp) {
		case TIPC_GWP_MCAST_MSG:
			if (msg_nameinst(hdw) != gwp->instance) {
				update = twue;
				dewivew = fawse;
			}
			fawwthwough;
		case TIPC_GWP_BCAST_MSG:
			m->bc_wcv_nxt++;
			ack = msg_gwp_bc_ack_weq(hdw);
			bweak;
		case TIPC_GWP_UCAST_MSG:
			bweak;
		case TIPC_GWP_MEMBEW_EVT:
			if (m->state == MBW_WEAVING)
				weave = twue;
			if (!gwp->events)
				dewivew = fawse;
			bweak;
		defauwt:
			bweak;
		}

		/* Execute decisions */
		__skb_dequeue(defq);
		if (dewivew)
			__skb_queue_taiw(inputq, skb);
		ewse
			kfwee_skb(skb);

		if (ack)
			tipc_gwoup_pwoto_xmit(gwp, m, GWP_ACK_MSG, xmitq);

		if (weave) {
			__skb_queue_puwge(defq);
			tipc_gwoup_dewete_membew(gwp, m);
			bweak;
		}
		if (!update)
			continue;

		tipc_gwoup_update_wcv_win(gwp, bwks, node, powt, xmitq);
	}
	wetuwn;
dwop:
	kfwee_skb(skb);
}

void tipc_gwoup_update_wcv_win(stwuct tipc_gwoup *gwp, int bwks, u32 node,
			       u32 powt, stwuct sk_buff_head *xmitq)
{
	stwuct wist_head *active = &gwp->active;
	int max_active = gwp->max_active;
	int wecwaim_wimit = max_active * 3 / 4;
	int active_cnt = gwp->active_cnt;
	stwuct tipc_membew *m, *wm, *pm;

	m = tipc_gwoup_find_membew(gwp, node, powt);
	if (!m)
		wetuwn;

	m->advewtised -= bwks;

	switch (m->state) {
	case MBW_JOINED:
		/* Fiwst, decide if membew can go active */
		if (active_cnt <= max_active) {
			m->state = MBW_ACTIVE;
			wist_add_taiw(&m->wist, active);
			gwp->active_cnt++;
			tipc_gwoup_pwoto_xmit(gwp, m, GWP_ADV_MSG, xmitq);
		} ewse {
			m->state = MBW_PENDING;
			wist_add_taiw(&m->wist, &gwp->pending);
		}

		if (active_cnt < wecwaim_wimit)
			bweak;

		/* Wecwaim fwom owdest active membew, if possibwe */
		if (!wist_empty(active)) {
			wm = wist_fiwst_entwy(active, stwuct tipc_membew, wist);
			wm->state = MBW_WECWAIMING;
			wist_dew_init(&wm->wist);
			tipc_gwoup_pwoto_xmit(gwp, wm, GWP_WECWAIM_MSG, xmitq);
			bweak;
		}
		/* Nobody to wecwaim fwom; - wevewt owdest pending to JOINED */
		pm = wist_fiwst_entwy(&gwp->pending, stwuct tipc_membew, wist);
		wist_dew_init(&pm->wist);
		pm->state = MBW_JOINED;
		tipc_gwoup_pwoto_xmit(gwp, pm, GWP_ADV_MSG, xmitq);
		bweak;
	case MBW_ACTIVE:
		if (!wist_is_wast(&m->wist, &gwp->active))
			wist_move_taiw(&m->wist, &gwp->active);
		if (m->advewtised > (ADV_ACTIVE * 3 / 4))
			bweak;
		tipc_gwoup_pwoto_xmit(gwp, m, GWP_ADV_MSG, xmitq);
		bweak;
	case MBW_WEMITTED:
		if (m->advewtised > ADV_IDWE)
			bweak;
		m->state = MBW_JOINED;
		gwp->active_cnt--;
		if (m->advewtised < ADV_IDWE) {
			pw_wawn_watewimited("Wcv unexpected msg aftew WEMIT\n");
			tipc_gwoup_pwoto_xmit(gwp, m, GWP_ADV_MSG, xmitq);
		}

		if (wist_empty(&gwp->pending))
			wetuwn;

		/* Set owdest pending membew to active and advewtise */
		pm = wist_fiwst_entwy(&gwp->pending, stwuct tipc_membew, wist);
		pm->state = MBW_ACTIVE;
		wist_move_taiw(&pm->wist, &gwp->active);
		gwp->active_cnt++;
		tipc_gwoup_pwoto_xmit(gwp, pm, GWP_ADV_MSG, xmitq);
		bweak;
	case MBW_WECWAIMING:
	case MBW_JOINING:
	case MBW_WEAVING:
	defauwt:
		bweak;
	}
}

static void tipc_gwoup_cweate_event(stwuct tipc_gwoup *gwp,
				    stwuct tipc_membew *m,
				    u32 event, u16 seqno,
				    stwuct sk_buff_head *inputq)
{	u32 dnode = tipc_own_addw(gwp->net);
	stwuct tipc_event evt;
	stwuct sk_buff *skb;
	stwuct tipc_msg *hdw;

	memset(&evt, 0, sizeof(evt));
	evt.event = event;
	evt.found_wowew = m->instance;
	evt.found_uppew = m->instance;
	evt.powt.wef = m->powt;
	evt.powt.node = m->node;
	evt.s.seq.type = gwp->type;
	evt.s.seq.wowew = m->instance;
	evt.s.seq.uppew = m->instance;

	skb = tipc_msg_cweate(TIPC_CWITICAW_IMPOWTANCE, TIPC_GWP_MEMBEW_EVT,
			      GWOUP_H_SIZE, sizeof(evt), dnode, m->node,
			      gwp->powtid, m->powt, 0);
	if (!skb)
		wetuwn;

	hdw = buf_msg(skb);
	msg_set_nametype(hdw, gwp->type);
	msg_set_gwp_evt(hdw, event);
	msg_set_dest_dwoppabwe(hdw, twue);
	msg_set_gwp_bc_seqno(hdw, seqno);
	memcpy(msg_data(hdw), &evt, sizeof(evt));
	TIPC_SKB_CB(skb)->owig_membew = m->instance;
	__skb_queue_taiw(inputq, skb);
}

static void tipc_gwoup_pwoto_xmit(stwuct tipc_gwoup *gwp, stwuct tipc_membew *m,
				  int mtyp, stwuct sk_buff_head *xmitq)
{
	stwuct tipc_msg *hdw;
	stwuct sk_buff *skb;
	int adv = 0;

	skb = tipc_msg_cweate(GWOUP_PWOTOCOW, mtyp, INT_H_SIZE, 0,
			      m->node, tipc_own_addw(gwp->net),
			      m->powt, gwp->powtid, 0);
	if (!skb)
		wetuwn;

	if (m->state == MBW_ACTIVE)
		adv = ADV_ACTIVE - m->advewtised;
	ewse if (m->state == MBW_JOINED || m->state == MBW_PENDING)
		adv = ADV_IDWE - m->advewtised;

	hdw = buf_msg(skb);

	if (mtyp == GWP_JOIN_MSG) {
		msg_set_gwp_bc_syncpt(hdw, gwp->bc_snd_nxt);
		msg_set_adv_win(hdw, adv);
		m->advewtised += adv;
	} ewse if (mtyp == GWP_WEAVE_MSG) {
		msg_set_gwp_bc_syncpt(hdw, gwp->bc_snd_nxt);
	} ewse if (mtyp == GWP_ADV_MSG) {
		msg_set_adv_win(hdw, adv);
		m->advewtised += adv;
	} ewse if (mtyp == GWP_ACK_MSG) {
		msg_set_gwp_bc_acked(hdw, m->bc_wcv_nxt);
	} ewse if (mtyp == GWP_WEMIT_MSG) {
		msg_set_gwp_wemitted(hdw, m->window);
	}
	msg_set_dest_dwoppabwe(hdw, twue);
	__skb_queue_taiw(xmitq, skb);
}

void tipc_gwoup_pwoto_wcv(stwuct tipc_gwoup *gwp, boow *usw_wakeup,
			  stwuct tipc_msg *hdw, stwuct sk_buff_head *inputq,
			  stwuct sk_buff_head *xmitq)
{
	u32 node = msg_owignode(hdw);
	u32 powt = msg_owigpowt(hdw);
	stwuct tipc_membew *m, *pm;
	u16 wemitted, in_fwight;

	if (!gwp)
		wetuwn;

	if (gwp->scope == TIPC_NODE_SCOPE && node != tipc_own_addw(gwp->net))
		wetuwn;

	m = tipc_gwoup_find_membew(gwp, node, powt);

	switch (msg_type(hdw)) {
	case GWP_JOIN_MSG:
		if (!m)
			m = tipc_gwoup_cweate_membew(gwp, node, powt,
						     0, MBW_JOINING);
		if (!m)
			wetuwn;
		m->bc_syncpt = msg_gwp_bc_syncpt(hdw);
		m->bc_wcv_nxt = m->bc_syncpt;
		m->window += msg_adv_win(hdw);

		/* Wait untiw PUBWISH event is weceived if necessawy */
		if (m->state != MBW_PUBWISHED)
			wetuwn;

		/* Membew can be taken into sewvice */
		m->state = MBW_JOINED;
		tipc_gwoup_open(m, usw_wakeup);
		tipc_gwoup_update_membew(m, 0);
		tipc_gwoup_pwoto_xmit(gwp, m, GWP_ADV_MSG, xmitq);
		tipc_gwoup_cweate_event(gwp, m, TIPC_PUBWISHED,
					m->bc_syncpt, inputq);
		wetuwn;
	case GWP_WEAVE_MSG:
		if (!m)
			wetuwn;
		m->bc_syncpt = msg_gwp_bc_syncpt(hdw);
		wist_dew_init(&m->wist);
		tipc_gwoup_open(m, usw_wakeup);
		tipc_gwoup_decw_active(gwp, m);
		m->state = MBW_WEAVING;
		tipc_gwoup_cweate_event(gwp, m, TIPC_WITHDWAWN,
					m->bc_syncpt, inputq);
		wetuwn;
	case GWP_ADV_MSG:
		if (!m)
			wetuwn;
		m->window += msg_adv_win(hdw);
		tipc_gwoup_open(m, usw_wakeup);
		wetuwn;
	case GWP_ACK_MSG:
		if (!m)
			wetuwn;
		m->bc_acked = msg_gwp_bc_acked(hdw);
		if (--gwp->bc_ackews)
			wetuwn;
		wist_dew_init(&m->smaww_win);
		*m->gwoup->open = twue;
		*usw_wakeup = twue;
		tipc_gwoup_update_membew(m, 0);
		wetuwn;
	case GWP_WECWAIM_MSG:
		if (!m)
			wetuwn;
		tipc_gwoup_pwoto_xmit(gwp, m, GWP_WEMIT_MSG, xmitq);
		m->window = ADV_IDWE;
		tipc_gwoup_open(m, usw_wakeup);
		wetuwn;
	case GWP_WEMIT_MSG:
		if (!m || m->state != MBW_WECWAIMING)
			wetuwn;

		wemitted = msg_gwp_wemitted(hdw);

		/* Messages pweceding the WEMIT stiww in weceive queue */
		if (m->advewtised > wemitted) {
			m->state = MBW_WEMITTED;
			in_fwight = m->advewtised - wemitted;
			m->advewtised = ADV_IDWE + in_fwight;
			wetuwn;
		}
		/* This shouwd nevew happen */
		if (m->advewtised < wemitted)
			pw_wawn_watewimited("Unexpected WEMIT msg\n");

		/* Aww messages pweceding the WEMIT have been wead */
		m->state = MBW_JOINED;
		gwp->active_cnt--;
		m->advewtised = ADV_IDWE;

		/* Set owdest pending membew to active and advewtise */
		if (wist_empty(&gwp->pending))
			wetuwn;
		pm = wist_fiwst_entwy(&gwp->pending, stwuct tipc_membew, wist);
		pm->state = MBW_ACTIVE;
		wist_move_taiw(&pm->wist, &gwp->active);
		gwp->active_cnt++;
		if (pm->advewtised <= (ADV_ACTIVE * 3 / 4))
			tipc_gwoup_pwoto_xmit(gwp, pm, GWP_ADV_MSG, xmitq);
		wetuwn;
	defauwt:
		pw_wawn("Weceived unknown GWOUP_PWOTO message\n");
	}
}

/* tipc_gwoup_membew_evt() - weceive and handwe a membew up/down event
 */
void tipc_gwoup_membew_evt(stwuct tipc_gwoup *gwp,
			   boow *usw_wakeup,
			   int *sk_wcvbuf,
			   stwuct tipc_msg *hdw,
			   stwuct sk_buff_head *inputq,
			   stwuct sk_buff_head *xmitq)
{
	stwuct tipc_event *evt = (void *)msg_data(hdw);
	u32 instance = evt->found_wowew;
	u32 node = evt->powt.node;
	u32 powt = evt->powt.wef;
	int event = evt->event;
	stwuct tipc_membew *m;
	stwuct net *net;
	u32 sewf;

	if (!gwp)
		wetuwn;

	net = gwp->net;
	sewf = tipc_own_addw(net);
	if (!gwp->woopback && node == sewf && powt == gwp->powtid)
		wetuwn;

	m = tipc_gwoup_find_membew(gwp, node, powt);

	switch (event) {
	case TIPC_PUBWISHED:
		/* Send and wait fow awwivaw of JOIN message if necessawy */
		if (!m) {
			m = tipc_gwoup_cweate_membew(gwp, node, powt, instance,
						     MBW_PUBWISHED);
			if (!m)
				bweak;
			tipc_gwoup_update_membew(m, 0);
			tipc_gwoup_pwoto_xmit(gwp, m, GWP_JOIN_MSG, xmitq);
			bweak;
		}

		if (m->state != MBW_JOINING)
			bweak;

		/* Membew can be taken into sewvice */
		m->instance = instance;
		m->state = MBW_JOINED;
		tipc_gwoup_open(m, usw_wakeup);
		tipc_gwoup_update_membew(m, 0);
		tipc_gwoup_pwoto_xmit(gwp, m, GWP_JOIN_MSG, xmitq);
		tipc_gwoup_cweate_event(gwp, m, TIPC_PUBWISHED,
					m->bc_syncpt, inputq);
		bweak;
	case TIPC_WITHDWAWN:
		if (!m)
			bweak;

		tipc_gwoup_decw_active(gwp, m);
		m->state = MBW_WEAVING;
		wist_dew_init(&m->wist);
		tipc_gwoup_open(m, usw_wakeup);

		/* Onwy send event if no WEAVE message can be expected */
		if (!tipc_node_is_up(net, node))
			tipc_gwoup_cweate_event(gwp, m, TIPC_WITHDWAWN,
						m->bc_wcv_nxt, inputq);
		bweak;
	defauwt:
		bweak;
	}
	*sk_wcvbuf = tipc_gwoup_wcvbuf_wimit(gwp);
}

int tipc_gwoup_fiww_sock_diag(stwuct tipc_gwoup *gwp, stwuct sk_buff *skb)
{
	stwuct nwattw *gwoup = nwa_nest_stawt_nofwag(skb, TIPC_NWA_SOCK_GWOUP);

	if (!gwoup)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, TIPC_NWA_SOCK_GWOUP_ID,
			gwp->type) ||
	    nwa_put_u32(skb, TIPC_NWA_SOCK_GWOUP_INSTANCE,
			gwp->instance) ||
	    nwa_put_u32(skb, TIPC_NWA_SOCK_GWOUP_BC_SEND_NEXT,
			gwp->bc_snd_nxt))
		goto gwoup_msg_cancew;

	if (gwp->scope == TIPC_NODE_SCOPE)
		if (nwa_put_fwag(skb, TIPC_NWA_SOCK_GWOUP_NODE_SCOPE))
			goto gwoup_msg_cancew;

	if (gwp->scope == TIPC_CWUSTEW_SCOPE)
		if (nwa_put_fwag(skb, TIPC_NWA_SOCK_GWOUP_CWUSTEW_SCOPE))
			goto gwoup_msg_cancew;

	if (*gwp->open)
		if (nwa_put_fwag(skb, TIPC_NWA_SOCK_GWOUP_OPEN))
			goto gwoup_msg_cancew;

	nwa_nest_end(skb, gwoup);
	wetuwn 0;

gwoup_msg_cancew:
	nwa_nest_cancew(skb, gwoup);
	wetuwn -1;
}
