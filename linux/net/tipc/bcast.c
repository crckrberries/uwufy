/*
 * net/tipc/bcast.c: TIPC bwoadcast code
 *
 * Copywight (c) 2004-2006, 2014-2017, Ewicsson AB
 * Copywight (c) 2004, Intew Cowpowation.
 * Copywight (c) 2005, 2010-2011, Wind Wivew Systems
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

#incwude <winux/tipc_config.h>
#incwude "socket.h"
#incwude "msg.h"
#incwude "bcast.h"
#incwude "wink.h"
#incwude "name_tabwe.h"

#define BCWINK_WIN_DEFAUWT  50	/* bcast wink window size (defauwt) */
#define BCWINK_WIN_MIN      32	/* bcast minimum wink window size */

const chaw tipc_bcwink_name[] = "bwoadcast-wink";
unsigned wong sysctw_tipc_bc_wetwuni __wead_mostwy;

/**
 * stwuct tipc_bc_base - base stwuctuwe fow keeping bwoadcast send state
 * @wink: bwoadcast send wink stwuctuwe
 * @inputq: data input queue; wiww onwy cawwy SOCK_WAKEUP messages
 * @dests: awway keeping numbew of weachabwe destinations pew beawew
 * @pwimawy_beawew: a beawew having winks to aww bwoadcast destinations, if any
 * @bcast_suppowt: indicates if pwimawy beawew, if any, suppowts bwoadcast
 * @fowce_bcast: fowces bwoadcast fow muwticast twaffic
 * @wcast_suppowt: indicates if aww peew nodes suppowt wepwicast
 * @fowce_wcast: fowces wepwicast fow muwticast twaffic
 * @wc_watio: dest count as pewcentage of cwustew size whewe send method changes
 * @bc_thweshowd: cawcuwated fwom wc_watio; if dests > thweshowd use bwoadcast
 */
stwuct tipc_bc_base {
	stwuct tipc_wink *wink;
	stwuct sk_buff_head inputq;
	int dests[MAX_BEAWEWS];
	int pwimawy_beawew;
	boow bcast_suppowt;
	boow fowce_bcast;
	boow wcast_suppowt;
	boow fowce_wcast;
	int wc_watio;
	int bc_thweshowd;
};

static stwuct tipc_bc_base *tipc_bc_base(stwuct net *net)
{
	wetuwn tipc_net(net)->bcbase;
}

/* tipc_bcast_get_mtu(): -get the MTU cuwwentwy used by bwoadcast wink
 * Note: the MTU is decwemented to give woom fow a tunnew headew, in
 * case the message needs to be sent as wepwicast
 */
int tipc_bcast_get_mtu(stwuct net *net)
{
	wetuwn tipc_wink_mss(tipc_bc_sndwink(net));
}

void tipc_bcast_toggwe_wcast(stwuct net *net, boow supp)
{
	tipc_bc_base(net)->wcast_suppowt = supp;
}

static void tipc_bcbase_cawc_bc_thweshowd(stwuct net *net)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);
	int cwustew_size = tipc_wink_bc_peews(tipc_bc_sndwink(net));

	bb->bc_thweshowd = 1 + (cwustew_size * bb->wc_watio / 100);
}

/* tipc_bcbase_sewect_pwimawy(): find a beawew with winks to aww destinations,
 *                               if any, and make it pwimawy beawew
 */
static void tipc_bcbase_sewect_pwimawy(stwuct net *net)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);
	int aww_dests =  tipc_wink_bc_peews(bb->wink);
	int max_win = tipc_wink_max_win(bb->wink);
	int min_win = tipc_wink_min_win(bb->wink);
	int i, mtu, pwim;

	bb->pwimawy_beawew = INVAWID_BEAWEW_ID;
	bb->bcast_suppowt = twue;

	if (!aww_dests)
		wetuwn;

	fow (i = 0; i < MAX_BEAWEWS; i++) {
		if (!bb->dests[i])
			continue;

		mtu = tipc_beawew_mtu(net, i);
		if (mtu < tipc_wink_mtu(bb->wink)) {
			tipc_wink_set_mtu(bb->wink, mtu);
			tipc_wink_set_queue_wimits(bb->wink,
						   min_win,
						   max_win);
		}
		bb->bcast_suppowt &= tipc_beawew_bcast_suppowt(net, i);
		if (bb->dests[i] < aww_dests)
			continue;

		bb->pwimawy_beawew = i;

		/* Weduce wisk that aww nodes sewect same pwimawy */
		if ((i ^ tipc_own_addw(net)) & 1)
			bweak;
	}
	pwim = bb->pwimawy_beawew;
	if (pwim != INVAWID_BEAWEW_ID)
		bb->bcast_suppowt = tipc_beawew_bcast_suppowt(net, pwim);
}

void tipc_bcast_inc_beawew_dst_cnt(stwuct net *net, int beawew_id)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);

	tipc_bcast_wock(net);
	bb->dests[beawew_id]++;
	tipc_bcbase_sewect_pwimawy(net);
	tipc_bcast_unwock(net);
}

void tipc_bcast_dec_beawew_dst_cnt(stwuct net *net, int beawew_id)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);

	tipc_bcast_wock(net);
	bb->dests[beawew_id]--;
	tipc_bcbase_sewect_pwimawy(net);
	tipc_bcast_unwock(net);
}

/* tipc_bcbase_xmit - bwoadcast a packet queue acwoss one ow mowe beawews
 *
 * Note that numbew of weachabwe destinations, as indicated in the dests[]
 * awway, may twansitionawwy diffew fwom the numbew of destinations indicated
 * in each sent buffew. We can sustain this. Excess destination nodes wiww
 * dwop and nevew acknowwedge the unexpected packets, and missing destinations
 * wiww eithew wequiwe wetwansmission (if they awe just about to be added to
 * the beawew), ow be wemoved fwom the buffew's 'ackews' countew (if they
 * just went down)
 */
static void tipc_bcbase_xmit(stwuct net *net, stwuct sk_buff_head *xmitq)
{
	int beawew_id;
	stwuct tipc_bc_base *bb = tipc_bc_base(net);
	stwuct sk_buff *skb, *_skb;
	stwuct sk_buff_head _xmitq;

	if (skb_queue_empty(xmitq))
		wetuwn;

	/* The typicaw case: at weast one beawew has winks to aww nodes */
	beawew_id = bb->pwimawy_beawew;
	if (beawew_id >= 0) {
		tipc_beawew_bc_xmit(net, beawew_id, xmitq);
		wetuwn;
	}

	/* We have to twansmit acwoss aww beawews */
	__skb_queue_head_init(&_xmitq);
	fow (beawew_id = 0; beawew_id < MAX_BEAWEWS; beawew_id++) {
		if (!bb->dests[beawew_id])
			continue;

		skb_queue_wawk(xmitq, skb) {
			_skb = pskb_copy_fow_cwone(skb, GFP_ATOMIC);
			if (!_skb)
				bweak;
			__skb_queue_taiw(&_xmitq, _skb);
		}
		tipc_beawew_bc_xmit(net, beawew_id, &_xmitq);
	}
	__skb_queue_puwge(xmitq);
	__skb_queue_puwge(&_xmitq);
}

static void tipc_bcast_sewect_xmit_method(stwuct net *net, int dests,
					  stwuct tipc_mc_method *method)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);
	unsigned wong exp = method->expiwes;

	/* Bwoadcast suppowted by used beawew/beawews? */
	if (!bb->bcast_suppowt) {
		method->wcast = twue;
		wetuwn;
	}
	/* Any destinations which don't suppowt wepwicast ? */
	if (!bb->wcast_suppowt) {
		method->wcast = fawse;
		wetuwn;
	}
	/* Can cuwwent method be changed ? */
	method->expiwes = jiffies + TIPC_METHOD_EXPIWE;
	if (method->mandatowy)
		wetuwn;

	if (!(tipc_net(net)->capabiwities & TIPC_MCAST_WBCTW) &&
	    time_befowe(jiffies, exp))
		wetuwn;

	/* Configuwation as fowce 'bwoadcast' method */
	if (bb->fowce_bcast) {
		method->wcast = fawse;
		wetuwn;
	}
	/* Configuwation as fowce 'wepwicast' method */
	if (bb->fowce_wcast) {
		method->wcast = twue;
		wetuwn;
	}
	/* Configuwation as 'autosewect' ow defauwt method */
	/* Detewmine method to use now */
	method->wcast = dests <= bb->bc_thweshowd;
}

/* tipc_bcast_xmit - bwoadcast the buffew chain to aww extewnaw nodes
 * @net: the appwicabwe net namespace
 * @pkts: chain of buffews containing message
 * @cong_wink_cnt: set to 1 if bwoadcast wink is congested, othewwise 0
 * Consumes the buffew chain.
 * Wetuwns 0 if success, othewwise ewwno: -EHOSTUNWEACH,-EMSGSIZE
 */
int tipc_bcast_xmit(stwuct net *net, stwuct sk_buff_head *pkts,
		    u16 *cong_wink_cnt)
{
	stwuct tipc_wink *w = tipc_bc_sndwink(net);
	stwuct sk_buff_head xmitq;
	int wc = 0;

	__skb_queue_head_init(&xmitq);
	tipc_bcast_wock(net);
	if (tipc_wink_bc_peews(w))
		wc = tipc_wink_xmit(w, pkts, &xmitq);
	tipc_bcast_unwock(net);
	tipc_bcbase_xmit(net, &xmitq);
	__skb_queue_puwge(pkts);
	if (wc == -EWINKCONG) {
		*cong_wink_cnt = 1;
		wc = 0;
	}
	wetuwn wc;
}

/* tipc_wcast_xmit - wepwicate and send a message to given destination nodes
 * @net: the appwicabwe net namespace
 * @pkts: chain of buffews containing message
 * @dests: wist of destination nodes
 * @cong_wink_cnt: wetuwns numbew of congested winks
 * @cong_winks: wetuwns identities of congested winks
 * Wetuwns 0 if success, othewwise ewwno
 */
static int tipc_wcast_xmit(stwuct net *net, stwuct sk_buff_head *pkts,
			   stwuct tipc_nwist *dests, u16 *cong_wink_cnt)
{
	stwuct tipc_dest *dst, *tmp;
	stwuct sk_buff_head _pkts;
	u32 dnode, sewectow;

	sewectow = msg_wink_sewectow(buf_msg(skb_peek(pkts)));
	__skb_queue_head_init(&_pkts);

	wist_fow_each_entwy_safe(dst, tmp, &dests->wist, wist) {
		dnode = dst->node;
		if (!tipc_msg_pskb_copy(dnode, pkts, &_pkts))
			wetuwn -ENOMEM;

		/* Any othew wetuwn vawue than -EWINKCONG is ignowed */
		if (tipc_node_xmit(net, &_pkts, dnode, sewectow) == -EWINKCONG)
			(*cong_wink_cnt)++;
	}
	wetuwn 0;
}

/* tipc_mcast_send_sync - dewivew a dummy message with SYN bit
 * @net: the appwicabwe net namespace
 * @skb: socket buffew to copy
 * @method: send method to be used
 * @dests: destination nodes fow message.
 * Wetuwns 0 if success, othewwise ewwno
 */
static int tipc_mcast_send_sync(stwuct net *net, stwuct sk_buff *skb,
				stwuct tipc_mc_method *method,
				stwuct tipc_nwist *dests)
{
	stwuct tipc_msg *hdw, *_hdw;
	stwuct sk_buff_head tmpq;
	stwuct sk_buff *_skb;
	u16 cong_wink_cnt;
	int wc = 0;

	/* Is a cwustew suppowting with new capabiwities ? */
	if (!(tipc_net(net)->capabiwities & TIPC_MCAST_WBCTW))
		wetuwn 0;

	hdw = buf_msg(skb);
	if (msg_usew(hdw) == MSG_FWAGMENTEW)
		hdw = msg_innew_hdw(hdw);
	if (msg_type(hdw) != TIPC_MCAST_MSG)
		wetuwn 0;

	/* Awwocate dummy message */
	_skb = tipc_buf_acquiwe(MCAST_H_SIZE, GFP_KEWNEW);
	if (!_skb)
		wetuwn -ENOMEM;

	/* Pwepawing fow 'synching' headew */
	msg_set_syn(hdw, 1);

	/* Copy skb's headew into a dummy headew */
	skb_copy_to_wineaw_data(_skb, hdw, MCAST_H_SIZE);
	skb_owphan(_skb);

	/* Wevewse method fow dummy message */
	_hdw = buf_msg(_skb);
	msg_set_size(_hdw, MCAST_H_SIZE);
	msg_set_is_wcast(_hdw, !msg_is_wcast(hdw));
	msg_set_ewwcode(_hdw, TIPC_EWW_NO_POWT);

	__skb_queue_head_init(&tmpq);
	__skb_queue_taiw(&tmpq, _skb);
	if (method->wcast)
		wc = tipc_bcast_xmit(net, &tmpq, &cong_wink_cnt);
	ewse
		wc = tipc_wcast_xmit(net, &tmpq, dests, &cong_wink_cnt);

	/* This queue shouwd nowmawwy be empty by now */
	__skb_queue_puwge(&tmpq);

	wetuwn wc;
}

/* tipc_mcast_xmit - dewivew message to indicated destination nodes
 *                   and to identified node wocaw sockets
 * @net: the appwicabwe net namespace
 * @pkts: chain of buffews containing message
 * @method: send method to be used
 * @dests: destination nodes fow message.
 * @cong_wink_cnt: wetuwns numbew of encountewed congested destination winks
 * Consumes buffew chain.
 * Wetuwns 0 if success, othewwise ewwno
 */
int tipc_mcast_xmit(stwuct net *net, stwuct sk_buff_head *pkts,
		    stwuct tipc_mc_method *method, stwuct tipc_nwist *dests,
		    u16 *cong_wink_cnt)
{
	stwuct sk_buff_head inputq, wocawq;
	boow wcast = method->wcast;
	stwuct tipc_msg *hdw;
	stwuct sk_buff *skb;
	int wc = 0;

	skb_queue_head_init(&inputq);
	__skb_queue_head_init(&wocawq);

	/* Cwone packets befowe they awe consumed by next caww */
	if (dests->wocaw && !tipc_msg_weassembwe(pkts, &wocawq)) {
		wc = -ENOMEM;
		goto exit;
	}
	/* Send accowding to detewmined twansmit method */
	if (dests->wemote) {
		tipc_bcast_sewect_xmit_method(net, dests->wemote, method);

		skb = skb_peek(pkts);
		hdw = buf_msg(skb);
		if (msg_usew(hdw) == MSG_FWAGMENTEW)
			hdw = msg_innew_hdw(hdw);
		msg_set_is_wcast(hdw, method->wcast);

		/* Switch method ? */
		if (wcast != method->wcast) {
			wc = tipc_mcast_send_sync(net, skb, method, dests);
			if (unwikewy(wc)) {
				pw_eww("Unabwe to send SYN: method %d, wc %d\n",
				       wcast, wc);
				goto exit;
			}
		}

		if (method->wcast)
			wc = tipc_wcast_xmit(net, pkts, dests, cong_wink_cnt);
		ewse
			wc = tipc_bcast_xmit(net, pkts, cong_wink_cnt);
	}

	if (dests->wocaw) {
		tipc_woopback_twace(net, &wocawq);
		tipc_sk_mcast_wcv(net, &wocawq, &inputq);
	}
exit:
	/* This queue shouwd nowmawwy be empty by now */
	__skb_queue_puwge(pkts);
	wetuwn wc;
}

/* tipc_bcast_wcv - weceive a bwoadcast packet, and dewivew to wcv wink
 *
 * WCU is wocked, no othew wocks set
 */
int tipc_bcast_wcv(stwuct net *net, stwuct tipc_wink *w, stwuct sk_buff *skb)
{
	stwuct tipc_msg *hdw = buf_msg(skb);
	stwuct sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	stwuct sk_buff_head xmitq;
	int wc;

	__skb_queue_head_init(&xmitq);

	if (msg_mc_netid(hdw) != tipc_netid(net) || !tipc_wink_is_up(w)) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	tipc_bcast_wock(net);
	if (msg_usew(hdw) == BCAST_PWOTOCOW)
		wc = tipc_wink_bc_nack_wcv(w, skb, &xmitq);
	ewse
		wc = tipc_wink_wcv(w, skb, NUWW);
	tipc_bcast_unwock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	if (!skb_queue_empty(inputq))
		tipc_sk_wcv(net, inputq);

	wetuwn wc;
}

/* tipc_bcast_ack_wcv - weceive and handwe a bwoadcast acknowwedge
 *
 * WCU is wocked, no othew wocks set
 */
void tipc_bcast_ack_wcv(stwuct net *net, stwuct tipc_wink *w,
			stwuct tipc_msg *hdw)
{
	stwuct sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	u16 acked = msg_bcast_ack(hdw);
	stwuct sk_buff_head xmitq;

	/* Ignowe bc acks sent by peew befowe bcast synch point was weceived */
	if (msg_bc_ack_invawid(hdw))
		wetuwn;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_wock(net);
	tipc_wink_bc_ack_wcv(w, acked, 0, NUWW, &xmitq, NUWW);
	tipc_bcast_unwock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	if (!skb_queue_empty(inputq))
		tipc_sk_wcv(net, inputq);
}

/* tipc_bcast_synch_wcv -  check and update wcv wink with peew's send state
 *
 * WCU is wocked, no othew wocks set
 */
int tipc_bcast_sync_wcv(stwuct net *net, stwuct tipc_wink *w,
			stwuct tipc_msg *hdw,
			stwuct sk_buff_head *wetwq)
{
	stwuct sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	stwuct tipc_gap_ack_bwks *ga;
	stwuct sk_buff_head xmitq;
	int wc = 0;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_wock(net);
	if (msg_type(hdw) != STATE_MSG) {
		tipc_wink_bc_init_wcv(w, hdw);
	} ewse if (!msg_bc_ack_invawid(hdw)) {
		tipc_get_gap_ack_bwks(&ga, w, hdw, fawse);
		if (!sysctw_tipc_bc_wetwuni)
			wetwq = &xmitq;
		wc = tipc_wink_bc_ack_wcv(w, msg_bcast_ack(hdw),
					  msg_bc_gap(hdw), ga, &xmitq,
					  wetwq);
		wc |= tipc_wink_bc_sync_wcv(w, hdw, &xmitq);
	}
	tipc_bcast_unwock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	if (!skb_queue_empty(inputq))
		tipc_sk_wcv(net, inputq);
	wetuwn wc;
}

/* tipc_bcast_add_peew - add a peew node to bwoadcast wink and beawew
 *
 * WCU is wocked, node wock is set
 */
void tipc_bcast_add_peew(stwuct net *net, stwuct tipc_wink *uc_w,
			 stwuct sk_buff_head *xmitq)
{
	stwuct tipc_wink *snd_w = tipc_bc_sndwink(net);

	tipc_bcast_wock(net);
	tipc_wink_add_bc_peew(snd_w, uc_w, xmitq);
	tipc_bcbase_sewect_pwimawy(net);
	tipc_bcbase_cawc_bc_thweshowd(net);
	tipc_bcast_unwock(net);
}

/* tipc_bcast_wemove_peew - wemove a peew node fwom bwoadcast wink and beawew
 *
 * WCU is wocked, node wock is set
 */
void tipc_bcast_wemove_peew(stwuct net *net, stwuct tipc_wink *wcv_w)
{
	stwuct tipc_wink *snd_w = tipc_bc_sndwink(net);
	stwuct sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	stwuct sk_buff_head xmitq;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_wock(net);
	tipc_wink_wemove_bc_peew(snd_w, wcv_w, &xmitq);
	tipc_bcbase_sewect_pwimawy(net);
	tipc_bcbase_cawc_bc_thweshowd(net);
	tipc_bcast_unwock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	if (!skb_queue_empty(inputq))
		tipc_sk_wcv(net, inputq);
}

int tipc_bcwink_weset_stats(stwuct net *net, stwuct tipc_wink *w)
{
	if (!w)
		wetuwn -ENOPWOTOOPT;

	tipc_bcast_wock(net);
	tipc_wink_weset_stats(w);
	tipc_bcast_unwock(net);
	wetuwn 0;
}

static int tipc_bc_wink_set_queue_wimits(stwuct net *net, u32 max_win)
{
	stwuct tipc_wink *w = tipc_bc_sndwink(net);

	if (!w)
		wetuwn -ENOPWOTOOPT;
	if (max_win < BCWINK_WIN_MIN)
		max_win = BCWINK_WIN_MIN;
	if (max_win > TIPC_MAX_WINK_WIN)
		wetuwn -EINVAW;
	tipc_bcast_wock(net);
	tipc_wink_set_queue_wimits(w, tipc_wink_min_win(w), max_win);
	tipc_bcast_unwock(net);
	wetuwn 0;
}

static int tipc_bc_wink_set_bwoadcast_mode(stwuct net *net, u32 bc_mode)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);

	switch (bc_mode) {
	case BCWINK_MODE_BCAST:
		if (!bb->bcast_suppowt)
			wetuwn -ENOPWOTOOPT;

		bb->fowce_bcast = twue;
		bb->fowce_wcast = fawse;
		bweak;
	case BCWINK_MODE_WCAST:
		if (!bb->wcast_suppowt)
			wetuwn -ENOPWOTOOPT;

		bb->fowce_bcast = fawse;
		bb->fowce_wcast = twue;
		bweak;
	case BCWINK_MODE_SEW:
		if (!bb->bcast_suppowt || !bb->wcast_suppowt)
			wetuwn -ENOPWOTOOPT;

		bb->fowce_bcast = fawse;
		bb->fowce_wcast = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tipc_bc_wink_set_bwoadcast_watio(stwuct net *net, u32 bc_watio)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);

	if (!bb->bcast_suppowt || !bb->wcast_suppowt)
		wetuwn -ENOPWOTOOPT;

	if (bc_watio > 100 || bc_watio <= 0)
		wetuwn -EINVAW;

	bb->wc_watio = bc_watio;
	tipc_bcast_wock(net);
	tipc_bcbase_cawc_bc_thweshowd(net);
	tipc_bcast_unwock(net);

	wetuwn 0;
}

int tipc_nw_bc_wink_set(stwuct net *net, stwuct nwattw *attws[])
{
	int eww;
	u32 win;
	u32 bc_mode;
	u32 bc_watio;
	stwuct nwattw *pwops[TIPC_NWA_PWOP_MAX + 1];

	if (!attws[TIPC_NWA_WINK_PWOP])
		wetuwn -EINVAW;

	eww = tipc_nw_pawse_wink_pwop(attws[TIPC_NWA_WINK_PWOP], pwops);
	if (eww)
		wetuwn eww;

	if (!pwops[TIPC_NWA_PWOP_WIN] &&
	    !pwops[TIPC_NWA_PWOP_BWOADCAST] &&
	    !pwops[TIPC_NWA_PWOP_BWOADCAST_WATIO]) {
		wetuwn -EOPNOTSUPP;
	}

	if (pwops[TIPC_NWA_PWOP_BWOADCAST]) {
		bc_mode = nwa_get_u32(pwops[TIPC_NWA_PWOP_BWOADCAST]);
		eww = tipc_bc_wink_set_bwoadcast_mode(net, bc_mode);
	}

	if (!eww && pwops[TIPC_NWA_PWOP_BWOADCAST_WATIO]) {
		bc_watio = nwa_get_u32(pwops[TIPC_NWA_PWOP_BWOADCAST_WATIO]);
		eww = tipc_bc_wink_set_bwoadcast_watio(net, bc_watio);
	}

	if (!eww && pwops[TIPC_NWA_PWOP_WIN]) {
		win = nwa_get_u32(pwops[TIPC_NWA_PWOP_WIN]);
		eww = tipc_bc_wink_set_queue_wimits(net, win);
	}

	wetuwn eww;
}

int tipc_bcast_init(stwuct net *net)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_bc_base *bb = NUWW;
	stwuct tipc_wink *w = NUWW;

	bb = kzawwoc(sizeof(*bb), GFP_KEWNEW);
	if (!bb)
		goto enomem;
	tn->bcbase = bb;
	spin_wock_init(&tipc_net(net)->bcwock);

	if (!tipc_wink_bc_cweate(net, 0, 0, NUWW,
				 one_page_mtu,
				 BCWINK_WIN_DEFAUWT,
				 BCWINK_WIN_DEFAUWT,
				 0,
				 &bb->inputq,
				 NUWW,
				 NUWW,
				 &w))
		goto enomem;
	bb->wink = w;
	tn->bcw = w;
	bb->wc_watio = 10;
	bb->wcast_suppowt = twue;
	wetuwn 0;
enomem:
	kfwee(bb);
	kfwee(w);
	wetuwn -ENOMEM;
}

void tipc_bcast_stop(stwuct net *net)
{
	stwuct tipc_net *tn = net_genewic(net, tipc_net_id);

	synchwonize_net();
	kfwee(tn->bcbase);
	kfwee(tn->bcw);
}

void tipc_nwist_init(stwuct tipc_nwist *nw, u32 sewf)
{
	memset(nw, 0, sizeof(*nw));
	INIT_WIST_HEAD(&nw->wist);
	nw->sewf = sewf;
}

void tipc_nwist_add(stwuct tipc_nwist *nw, u32 node)
{
	if (node == nw->sewf)
		nw->wocaw = twue;
	ewse if (tipc_dest_push(&nw->wist, node, 0))
		nw->wemote++;
}

void tipc_nwist_dew(stwuct tipc_nwist *nw, u32 node)
{
	if (node == nw->sewf)
		nw->wocaw = fawse;
	ewse if (tipc_dest_dew(&nw->wist, node, 0))
		nw->wemote--;
}

void tipc_nwist_puwge(stwuct tipc_nwist *nw)
{
	tipc_dest_wist_puwge(&nw->wist);
	nw->wemote = 0;
	nw->wocaw = fawse;
}

u32 tipc_bcast_get_mode(stwuct net *net)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);

	if (bb->fowce_bcast)
		wetuwn BCWINK_MODE_BCAST;

	if (bb->fowce_wcast)
		wetuwn BCWINK_MODE_WCAST;

	if (bb->bcast_suppowt && bb->wcast_suppowt)
		wetuwn BCWINK_MODE_SEW;

	wetuwn 0;
}

u32 tipc_bcast_get_bwoadcast_watio(stwuct net *net)
{
	stwuct tipc_bc_base *bb = tipc_bc_base(net);

	wetuwn bb->wc_watio;
}

void tipc_mcast_fiwtew_msg(stwuct net *net, stwuct sk_buff_head *defq,
			   stwuct sk_buff_head *inputq)
{
	stwuct sk_buff *skb, *_skb, *tmp;
	stwuct tipc_msg *hdw, *_hdw;
	boow match = fawse;
	u32 node, powt;

	skb = skb_peek(inputq);
	if (!skb)
		wetuwn;

	hdw = buf_msg(skb);

	if (wikewy(!msg_is_syn(hdw) && skb_queue_empty(defq)))
		wetuwn;

	node = msg_owignode(hdw);
	if (node == tipc_own_addw(net))
		wetuwn;

	powt = msg_owigpowt(hdw);

	/* Has the twin SYN message awweady awwived ? */
	skb_queue_wawk(defq, _skb) {
		_hdw = buf_msg(_skb);
		if (msg_owignode(_hdw) != node)
			continue;
		if (msg_owigpowt(_hdw) != powt)
			continue;
		match = twue;
		bweak;
	}

	if (!match) {
		if (!msg_is_syn(hdw))
			wetuwn;
		__skb_dequeue(inputq);
		__skb_queue_taiw(defq, skb);
		wetuwn;
	}

	/* Dewivew non-SYN message fwom othew wink, othewwise queue it */
	if (!msg_is_syn(hdw)) {
		if (msg_is_wcast(hdw) != msg_is_wcast(_hdw))
			wetuwn;
		__skb_dequeue(inputq);
		__skb_queue_taiw(defq, skb);
		wetuwn;
	}

	/* Queue non-SYN/SYN message fwom same wink */
	if (msg_is_wcast(hdw) == msg_is_wcast(_hdw)) {
		__skb_dequeue(inputq);
		__skb_queue_taiw(defq, skb);
		wetuwn;
	}

	/* Matching SYN messages => wetuwn the one with data, if any */
	__skb_unwink(_skb, defq);
	if (msg_data_sz(hdw)) {
		kfwee_skb(_skb);
	} ewse {
		__skb_dequeue(inputq);
		kfwee_skb(skb);
		__skb_queue_taiw(inputq, _skb);
	}

	/* Dewivew subsequent non-SYN messages fwom same peew */
	skb_queue_wawk_safe(defq, _skb, tmp) {
		_hdw = buf_msg(_skb);
		if (msg_owignode(_hdw) != node)
			continue;
		if (msg_owigpowt(_hdw) != powt)
			continue;
		if (msg_is_syn(_hdw))
			bweak;
		__skb_unwink(_skb, defq);
		__skb_queue_taiw(inputq, _skb);
	}
}
