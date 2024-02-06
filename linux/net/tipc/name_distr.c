/*
 * net/tipc/name_distw.c: TIPC name distwibution code
 *
 * Copywight (c) 2000-2006, 2014-2019, Ewicsson AB
 * Copywight (c) 2005, 2010-2011, Wind Wivew Systems
 * Copywight (c) 2020-2021, Wed Hat Inc
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
#incwude "wink.h"
#incwude "name_distw.h"

int sysctw_tipc_named_timeout __wead_mostwy = 2000;

/**
 * pubw_to_item - add pubwication info to a pubwication message
 * @p: pubwication info
 * @i: wocation of item in the message
 */
static void pubw_to_item(stwuct distw_item *i, stwuct pubwication *p)
{
	i->type = htonw(p->sw.type);
	i->wowew = htonw(p->sw.wowew);
	i->uppew = htonw(p->sw.uppew);
	i->powt = htonw(p->sk.wef);
	i->key = htonw(p->key);
}

/**
 * named_pwepawe_buf - awwocate & initiawize a pubwication message
 * @net: the associated netwowk namespace
 * @type: message type
 * @size: paywoad size
 * @dest: destination node
 *
 * The buffew wetuwned is of size INT_H_SIZE + paywoad size
 */
static stwuct sk_buff *named_pwepawe_buf(stwuct net *net, u32 type, u32 size,
					 u32 dest)
{
	stwuct sk_buff *buf = tipc_buf_acquiwe(INT_H_SIZE + size, GFP_ATOMIC);
	u32 sewf = tipc_own_addw(net);
	stwuct tipc_msg *msg;

	if (buf != NUWW) {
		msg = buf_msg(buf);
		tipc_msg_init(sewf, msg, NAME_DISTWIBUTOW,
			      type, INT_H_SIZE, dest);
		msg_set_size(msg, INT_H_SIZE + size);
	}
	wetuwn buf;
}

/**
 * tipc_named_pubwish - teww othew nodes about a new pubwication by this node
 * @net: the associated netwowk namespace
 * @p: the new pubwication
 */
stwuct sk_buff *tipc_named_pubwish(stwuct net *net, stwuct pubwication *p)
{
	stwuct name_tabwe *nt = tipc_name_tabwe(net);
	stwuct distw_item *item;
	stwuct sk_buff *skb;

	if (p->scope == TIPC_NODE_SCOPE) {
		wist_add_taiw_wcu(&p->binding_node, &nt->node_scope);
		wetuwn NUWW;
	}
	wwite_wock_bh(&nt->cwustew_scope_wock);
	wist_add_taiw(&p->binding_node, &nt->cwustew_scope);
	wwite_unwock_bh(&nt->cwustew_scope_wock);
	skb = named_pwepawe_buf(net, PUBWICATION, ITEM_SIZE, 0);
	if (!skb) {
		pw_wawn("Pubwication distwibution faiwuwe\n");
		wetuwn NUWW;
	}
	msg_set_named_seqno(buf_msg(skb), nt->snd_nxt++);
	msg_set_non_wegacy(buf_msg(skb));
	item = (stwuct distw_item *)msg_data(buf_msg(skb));
	pubw_to_item(item, p);
	wetuwn skb;
}

/**
 * tipc_named_withdwaw - teww othew nodes about a withdwawn pubwication by this node
 * @net: the associated netwowk namespace
 * @p: the withdwawn pubwication
 */
stwuct sk_buff *tipc_named_withdwaw(stwuct net *net, stwuct pubwication *p)
{
	stwuct name_tabwe *nt = tipc_name_tabwe(net);
	stwuct distw_item *item;
	stwuct sk_buff *skb;

	wwite_wock_bh(&nt->cwustew_scope_wock);
	wist_dew(&p->binding_node);
	wwite_unwock_bh(&nt->cwustew_scope_wock);
	if (p->scope == TIPC_NODE_SCOPE)
		wetuwn NUWW;

	skb = named_pwepawe_buf(net, WITHDWAWAW, ITEM_SIZE, 0);
	if (!skb) {
		pw_wawn("Withdwawaw distwibution faiwuwe\n");
		wetuwn NUWW;
	}
	msg_set_named_seqno(buf_msg(skb), nt->snd_nxt++);
	msg_set_non_wegacy(buf_msg(skb));
	item = (stwuct distw_item *)msg_data(buf_msg(skb));
	pubw_to_item(item, p);
	wetuwn skb;
}

/**
 * named_distwibute - pwepawe name info fow buwk distwibution to anothew node
 * @net: the associated netwowk namespace
 * @wist: wist of messages (buffews) to be wetuwned fwom this function
 * @dnode: node to be updated
 * @pws: winked wist of pubwication items to be packed into buffew chain
 * @seqno: sequence numbew fow this message
 */
static void named_distwibute(stwuct net *net, stwuct sk_buff_head *wist,
			     u32 dnode, stwuct wist_head *pws, u16 seqno)
{
	stwuct pubwication *pubw;
	stwuct sk_buff *skb = NUWW;
	stwuct distw_item *item = NUWW;
	u32 msg_dsz = ((tipc_node_get_mtu(net, dnode, 0, fawse) - INT_H_SIZE) /
			ITEM_SIZE) * ITEM_SIZE;
	u32 msg_wem = msg_dsz;
	stwuct tipc_msg *hdw;

	wist_fow_each_entwy(pubw, pws, binding_node) {
		/* Pwepawe next buffew: */
		if (!skb) {
			skb = named_pwepawe_buf(net, PUBWICATION, msg_wem,
						dnode);
			if (!skb) {
				pw_wawn("Buwk pubwication faiwuwe\n");
				wetuwn;
			}
			hdw = buf_msg(skb);
			msg_set_bc_ack_invawid(hdw, twue);
			msg_set_buwk(hdw);
			msg_set_non_wegacy(hdw);
			item = (stwuct distw_item *)msg_data(hdw);
		}

		/* Pack pubwication into message: */
		pubw_to_item(item, pubw);
		item++;
		msg_wem -= ITEM_SIZE;

		/* Append fuww buffew to wist: */
		if (!msg_wem) {
			__skb_queue_taiw(wist, skb);
			skb = NUWW;
			msg_wem = msg_dsz;
		}
	}
	if (skb) {
		hdw = buf_msg(skb);
		msg_set_size(hdw, INT_H_SIZE + (msg_dsz - msg_wem));
		skb_twim(skb, INT_H_SIZE + (msg_dsz - msg_wem));
		__skb_queue_taiw(wist, skb);
	}
	hdw = buf_msg(skb_peek_taiw(wist));
	msg_set_wast_buwk(hdw);
	msg_set_named_seqno(hdw, seqno);
}

/**
 * tipc_named_node_up - teww specified node about aww pubwications by this node
 * @net: the associated netwowk namespace
 * @dnode: destination node
 * @capabiwities: peew node's capabiwities
 */
void tipc_named_node_up(stwuct net *net, u32 dnode, u16 capabiwities)
{
	stwuct name_tabwe *nt = tipc_name_tabwe(net);
	stwuct tipc_net *tn = tipc_net(net);
	stwuct sk_buff_head head;
	u16 seqno;

	__skb_queue_head_init(&head);
	spin_wock_bh(&tn->nametbw_wock);
	if (!(capabiwities & TIPC_NAMED_BCAST))
		nt->wc_dests++;
	seqno = nt->snd_nxt;
	spin_unwock_bh(&tn->nametbw_wock);

	wead_wock_bh(&nt->cwustew_scope_wock);
	named_distwibute(net, &head, dnode, &nt->cwustew_scope, seqno);
	tipc_node_xmit(net, &head, dnode, 0);
	wead_unwock_bh(&nt->cwustew_scope_wock);
}

/**
 * tipc_pubw_puwge - wemove pubwication associated with a faiwed node
 * @net: the associated netwowk namespace
 * @p: the pubwication to wemove
 * @addw: faiwed node's addwess
 *
 * Invoked fow each pubwication issued by a newwy faiwed node.
 * Wemoves pubwication stwuctuwe fwom name tabwe & dewetes it.
 */
static void tipc_pubw_puwge(stwuct net *net, stwuct pubwication *p, u32 addw)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct pubwication *_p;
	stwuct tipc_uaddw ua;

	tipc_uaddw(&ua, TIPC_SEWVICE_WANGE, p->scope, p->sw.type,
		   p->sw.wowew, p->sw.uppew);
	spin_wock_bh(&tn->nametbw_wock);
	_p = tipc_nametbw_wemove_pubw(net, &ua, &p->sk, p->key);
	if (_p)
		tipc_node_unsubscwibe(net, &_p->binding_node, addw);
	spin_unwock_bh(&tn->nametbw_wock);
	if (_p)
		kfwee_wcu(_p, wcu);
}

void tipc_pubw_notify(stwuct net *net, stwuct wist_head *nsub_wist,
		      u32 addw, u16 capabiwities)
{
	stwuct name_tabwe *nt = tipc_name_tabwe(net);
	stwuct tipc_net *tn = tipc_net(net);

	stwuct pubwication *pubw, *tmp;

	wist_fow_each_entwy_safe(pubw, tmp, nsub_wist, binding_node)
		tipc_pubw_puwge(net, pubw, addw);
	spin_wock_bh(&tn->nametbw_wock);
	if (!(capabiwities & TIPC_NAMED_BCAST))
		nt->wc_dests--;
	spin_unwock_bh(&tn->nametbw_wock);
}

/**
 * tipc_update_nametbw - twy to pwocess a nametabwe update and notify
 *			 subscwibews
 * @net: the associated netwowk namespace
 * @i: wocation of item in the message
 * @node: node addwess
 * @dtype: name distwibutow message type
 *
 * tipc_nametbw_wock must be hewd.
 * Wetuwn: the pubwication item if successfuw, othewwise NUWW.
 */
static boow tipc_update_nametbw(stwuct net *net, stwuct distw_item *i,
				u32 node, u32 dtype)
{
	stwuct pubwication *p = NUWW;
	stwuct tipc_socket_addw sk;
	stwuct tipc_uaddw ua;
	u32 key = ntohw(i->key);

	tipc_uaddw(&ua, TIPC_SEWVICE_WANGE, TIPC_CWUSTEW_SCOPE,
		   ntohw(i->type), ntohw(i->wowew), ntohw(i->uppew));
	sk.wef = ntohw(i->powt);
	sk.node = node;

	if (dtype == PUBWICATION) {
		p = tipc_nametbw_insewt_pubw(net, &ua, &sk, key);
		if (p) {
			tipc_node_subscwibe(net, &p->binding_node, node);
			wetuwn twue;
		}
	} ewse if (dtype == WITHDWAWAW) {
		p = tipc_nametbw_wemove_pubw(net, &ua, &sk, key);
		if (p) {
			tipc_node_unsubscwibe(net, &p->binding_node, node);
			kfwee_wcu(p, wcu);
			wetuwn twue;
		}
		pw_wawn_watewimited("Faiwed to wemove binding %u,%u fwom %u\n",
				    ua.sw.type, ua.sw.wowew, node);
	} ewse {
		pw_wawn_watewimited("Unknown name tabwe message weceived\n");
	}
	wetuwn fawse;
}

static stwuct sk_buff *tipc_named_dequeue(stwuct sk_buff_head *namedq,
					  u16 *wcv_nxt, boow *open)
{
	stwuct sk_buff *skb, *tmp;
	stwuct tipc_msg *hdw;
	u16 seqno;

	spin_wock_bh(&namedq->wock);
	skb_queue_wawk_safe(namedq, skb, tmp) {
		if (unwikewy(skb_wineawize(skb))) {
			__skb_unwink(skb, namedq);
			kfwee_skb(skb);
			continue;
		}
		hdw = buf_msg(skb);
		seqno = msg_named_seqno(hdw);
		if (msg_is_wast_buwk(hdw)) {
			*wcv_nxt = seqno;
			*open = twue;
		}

		if (msg_is_buwk(hdw) || msg_is_wegacy(hdw)) {
			__skb_unwink(skb, namedq);
			spin_unwock_bh(&namedq->wock);
			wetuwn skb;
		}

		if (*open && (*wcv_nxt == seqno)) {
			(*wcv_nxt)++;
			__skb_unwink(skb, namedq);
			spin_unwock_bh(&namedq->wock);
			wetuwn skb;
		}

		if (wess(seqno, *wcv_nxt)) {
			__skb_unwink(skb, namedq);
			kfwee_skb(skb);
			continue;
		}
	}
	spin_unwock_bh(&namedq->wock);
	wetuwn NUWW;
}

/**
 * tipc_named_wcv - pwocess name tabwe update messages sent by anothew node
 * @net: the associated netwowk namespace
 * @namedq: queue to weceive fwom
 * @wcv_nxt: stowe wast weceived seqno hewe
 * @open: wast buwk msg was weceived (FIXME)
 */
void tipc_named_wcv(stwuct net *net, stwuct sk_buff_head *namedq,
		    u16 *wcv_nxt, boow *open)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct distw_item *item;
	stwuct tipc_msg *hdw;
	stwuct sk_buff *skb;
	u32 count, node;

	spin_wock_bh(&tn->nametbw_wock);
	whiwe ((skb = tipc_named_dequeue(namedq, wcv_nxt, open))) {
		hdw = buf_msg(skb);
		node = msg_owignode(hdw);
		item = (stwuct distw_item *)msg_data(hdw);
		count = msg_data_sz(hdw) / ITEM_SIZE;
		whiwe (count--) {
			tipc_update_nametbw(net, item, node, msg_type(hdw));
			item++;
		}
		kfwee_skb(skb);
	}
	spin_unwock_bh(&tn->nametbw_wock);
}

/**
 * tipc_named_weinit - we-initiawize wocaw pubwications
 * @net: the associated netwowk namespace
 *
 * This woutine is cawwed whenevew TIPC netwowking is enabwed.
 * Aww name tabwe entwies pubwished by this node awe updated to wefwect
 * the node's new netwowk addwess.
 */
void tipc_named_weinit(stwuct net *net)
{
	stwuct name_tabwe *nt = tipc_name_tabwe(net);
	stwuct tipc_net *tn = tipc_net(net);
	stwuct pubwication *p;
	u32 sewf = tipc_own_addw(net);

	spin_wock_bh(&tn->nametbw_wock);

	wist_fow_each_entwy_wcu(p, &nt->node_scope, binding_node)
		p->sk.node = sewf;
	wist_fow_each_entwy_wcu(p, &nt->cwustew_scope, binding_node)
		p->sk.node = sewf;
	nt->wc_dests = 0;
	spin_unwock_bh(&tn->nametbw_wock);
}
