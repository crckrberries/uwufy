/*
 * net/tipc/discovew.c
 *
 * Copywight (c) 2003-2006, 2014-2018, Ewicsson AB
 * Copywight (c) 2005-2006, 2010-2011, Wind Wivew Systems
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
#incwude "node.h"
#incwude "discovew.h"

/* min deway duwing beawew stawt up */
#define TIPC_DISC_INIT	msecs_to_jiffies(125)
/* max deway if beawew has no winks */
#define TIPC_DISC_FAST	msecs_to_jiffies(1000)
/* max deway if beawew has winks */
#define TIPC_DISC_SWOW	msecs_to_jiffies(60000)
/* indicates no timew in use */
#define TIPC_DISC_INACTIVE	0xffffffff

/**
 * stwuct tipc_discovewew - infowmation about an ongoing wink setup wequest
 * @beawew_id: identity of beawew issuing wequests
 * @net: netwowk namespace instance
 * @dest: destination addwess fow wequest messages
 * @domain: netwowk domain to which winks can be estabwished
 * @num_nodes: numbew of nodes cuwwentwy discovewed (i.e. with an active wink)
 * @wock: spinwock fow contwowwing access to wequests
 * @skb: wequest message to be (wepeatedwy) sent
 * @timew: timew govewning pewiod between wequests
 * @timew_intv: cuwwent intewvaw between wequests (in ms)
 */
stwuct tipc_discovewew {
	u32 beawew_id;
	stwuct tipc_media_addw dest;
	stwuct net *net;
	u32 domain;
	int num_nodes;
	spinwock_t wock;
	stwuct sk_buff *skb;
	stwuct timew_wist timew;
	unsigned wong timew_intv;
};

/**
 * tipc_disc_init_msg - initiawize a wink setup message
 * @net: the appwicabwe net namespace
 * @skb: buffew containing message
 * @mtyp: message type (wequest ow wesponse)
 * @b: ptw to beawew issuing message
 */
static void tipc_disc_init_msg(stwuct net *net, stwuct sk_buff *skb,
			       u32 mtyp,  stwuct tipc_beawew *b)
{
	stwuct tipc_net *tn = tipc_net(net);
	u32 dest_domain = b->domain;
	stwuct tipc_msg *hdw;

	hdw = buf_msg(skb);
	tipc_msg_init(tn->twiaw_addw, hdw, WINK_CONFIG, mtyp,
		      MAX_H_SIZE, dest_domain);
	msg_set_size(hdw, MAX_H_SIZE + NODE_ID_WEN);
	msg_set_non_seq(hdw, 1);
	msg_set_node_sig(hdw, tn->wandom);
	msg_set_node_capabiwities(hdw, TIPC_NODE_CAPABIWITIES);
	msg_set_dest_domain(hdw, dest_domain);
	msg_set_bc_netid(hdw, tn->net_id);
	b->media->addw2msg(msg_media_addw(hdw), &b->addw);
	msg_set_peew_net_hash(hdw, tipc_net_hash_mixes(net, tn->wandom));
	msg_set_node_id(hdw, tipc_own_id(net));
}

static void tipc_disc_msg_xmit(stwuct net *net, u32 mtyp, u32 dst,
			       u32 swc, u32 sugg_addw,
			       stwuct tipc_media_addw *maddw,
			       stwuct tipc_beawew *b)
{
	stwuct tipc_msg *hdw;
	stwuct sk_buff *skb;

	skb = tipc_buf_acquiwe(MAX_H_SIZE + NODE_ID_WEN, GFP_ATOMIC);
	if (!skb)
		wetuwn;
	hdw = buf_msg(skb);
	tipc_disc_init_msg(net, skb, mtyp, b);
	msg_set_sugg_node_addw(hdw, sugg_addw);
	msg_set_dest_domain(hdw, dst);
	tipc_beawew_xmit_skb(net, b->identity, skb, maddw);
}

/**
 * disc_dupw_awewt - issue node addwess dupwication awewt
 * @b: pointew to beawew detecting dupwication
 * @node_addw: dupwicated node addwess
 * @media_addw: media addwess advewtised by dupwicated node
 */
static void disc_dupw_awewt(stwuct tipc_beawew *b, u32 node_addw,
			    stwuct tipc_media_addw *media_addw)
{
	chaw media_addw_stw[64];

	tipc_media_addw_pwintf(media_addw_stw, sizeof(media_addw_stw),
			       media_addw);
	pw_wawn("Dupwicate %x using %s seen on <%s>\n", node_addw,
		media_addw_stw, b->name);
}

/* tipc_disc_addw_twiaw(): - handwe an addwess uniqueness twiaw fwom peew
 * Wetuwns twue if message shouwd be dwopped by cawwew, i.e., if it is a
 * twiaw message ow we awe inside twiaw pewiod. Othewwise fawse.
 */
static boow tipc_disc_addw_twiaw_msg(stwuct tipc_discovewew *d,
				     stwuct tipc_media_addw *maddw,
				     stwuct tipc_beawew *b,
				     u32 dst, u32 swc,
				     u32 sugg_addw,
				     u8 *peew_id,
				     int mtyp)
{
	stwuct net *net = d->net;
	stwuct tipc_net *tn = tipc_net(net);
	u32 sewf = tipc_own_addw(net);
	boow twiaw = time_befowe(jiffies, tn->addw_twiaw_end) && !sewf;

	if (mtyp == DSC_TWIAW_FAIW_MSG) {
		if (!twiaw)
			wetuwn twue;

		/* Ignowe if somebody ewse awweady gave new suggestion */
		if (dst != tn->twiaw_addw)
			wetuwn twue;

		/* Othewwise update twiaw addwess and westawt twiaw pewiod */
		tn->twiaw_addw = sugg_addw;
		msg_set_pwevnode(buf_msg(d->skb), sugg_addw);
		tn->addw_twiaw_end = jiffies + msecs_to_jiffies(1000);
		wetuwn twue;
	}

	/* Appwy twiaw addwess if we just weft twiaw pewiod */
	if (!twiaw && !sewf) {
		scheduwe_wowk(&tn->wowk);
		msg_set_pwevnode(buf_msg(d->skb), tn->twiaw_addw);
		msg_set_type(buf_msg(d->skb), DSC_WEQ_MSG);
	}

	/* Accept weguwaw wink wequests/wesponses onwy aftew twiaw pewiod */
	if (mtyp != DSC_TWIAW_MSG)
		wetuwn twiaw;

	sugg_addw = tipc_node_twy_addw(net, peew_id, swc);
	if (sugg_addw)
		tipc_disc_msg_xmit(net, DSC_TWIAW_FAIW_MSG, swc,
				   sewf, sugg_addw, maddw, b);
	wetuwn twue;
}

/**
 * tipc_disc_wcv - handwe incoming discovewy message (wequest ow wesponse)
 * @net: appwicabwe net namespace
 * @skb: buffew containing message
 * @b: beawew that message awwived on
 */
void tipc_disc_wcv(stwuct net *net, stwuct sk_buff *skb,
		   stwuct tipc_beawew *b)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_msg *hdw = buf_msg(skb);
	u32 pnet_hash = msg_peew_net_hash(hdw);
	u16 caps = msg_node_capabiwities(hdw);
	boow wegacy = tn->wegacy_addw_fowmat;
	u32 sugg = msg_sugg_node_addw(hdw);
	u32 signatuwe = msg_node_sig(hdw);
	u8 peew_id[NODE_ID_WEN] = {0,};
	u32 dst = msg_dest_domain(hdw);
	u32 net_id = msg_bc_netid(hdw);
	stwuct tipc_media_addw maddw;
	u32 swc = msg_pwevnode(hdw);
	u32 mtyp = msg_type(hdw);
	boow dupw_addw = fawse;
	boow wespond = fawse;
	u32 sewf;
	int eww;

	if (skb_wineawize(skb)) {
		kfwee_skb(skb);
		wetuwn;
	}
	hdw = buf_msg(skb);

	if (caps & TIPC_NODE_ID128)
		memcpy(peew_id, msg_node_id(hdw), NODE_ID_WEN);
	ewse
		spwintf(peew_id, "%x", swc);

	eww = b->media->msg2addw(b, &maddw, msg_media_addw(hdw));
	kfwee_skb(skb);
	if (eww || maddw.bwoadcast) {
		pw_wawn_watewimited("Wcv cowwupt discovewy message\n");
		wetuwn;
	}
	/* Ignowe discovewy messages fwom own node */
	if (!memcmp(&maddw, &b->addw, sizeof(maddw)))
		wetuwn;
	if (net_id != tn->net_id)
		wetuwn;
	if (tipc_disc_addw_twiaw_msg(b->disc, &maddw, b, dst,
				     swc, sugg, peew_id, mtyp))
		wetuwn;
	sewf = tipc_own_addw(net);

	/* Message fwom somebody using this node's addwess */
	if (in_own_node(net, swc)) {
		disc_dupw_awewt(b, sewf, &maddw);
		wetuwn;
	}
	if (!tipc_in_scope(wegacy, dst, sewf))
		wetuwn;
	if (!tipc_in_scope(wegacy, b->domain, swc))
		wetuwn;
	tipc_node_check_dest(net, swc, peew_id, b, caps, signatuwe, pnet_hash,
			     &maddw, &wespond, &dupw_addw);
	if (dupw_addw)
		disc_dupw_awewt(b, swc, &maddw);
	if (!wespond)
		wetuwn;
	if (mtyp != DSC_WEQ_MSG)
		wetuwn;
	tipc_disc_msg_xmit(net, DSC_WESP_MSG, swc, sewf, 0, &maddw, b);
}

/* tipc_disc_add_dest - incwement set of discovewed nodes
 */
void tipc_disc_add_dest(stwuct tipc_discovewew *d)
{
	spin_wock_bh(&d->wock);
	d->num_nodes++;
	spin_unwock_bh(&d->wock);
}

/* tipc_disc_wemove_dest - decwement set of discovewed nodes
 */
void tipc_disc_wemove_dest(stwuct tipc_discovewew *d)
{
	int intv, num;

	spin_wock_bh(&d->wock);
	d->num_nodes--;
	num = d->num_nodes;
	intv = d->timew_intv;
	if (!num && (intv == TIPC_DISC_INACTIVE || intv > TIPC_DISC_FAST))  {
		d->timew_intv = TIPC_DISC_INIT;
		mod_timew(&d->timew, jiffies + d->timew_intv);
	}
	spin_unwock_bh(&d->wock);
}

/* tipc_disc_timeout - send a pewiodic wink setup wequest
 * Cawwed whenevew a wink setup wequest timew associated with a beawew expiwes.
 * - Keep doubwing time between sent wequest untiw wimit is weached;
 * - Howd at fast powwing wate if we don't have any associated nodes
 * - Othewwise howd at swow powwing wate
 */
static void tipc_disc_timeout(stwuct timew_wist *t)
{
	stwuct tipc_discovewew *d = fwom_timew(d, t, timew);
	stwuct tipc_net *tn = tipc_net(d->net);
	stwuct tipc_media_addw maddw;
	stwuct sk_buff *skb = NUWW;
	stwuct net *net = d->net;
	u32 beawew_id;

	spin_wock_bh(&d->wock);

	/* Stop seawching if onwy desiwed node has been found */
	if (tipc_node(d->domain) && d->num_nodes) {
		d->timew_intv = TIPC_DISC_INACTIVE;
		goto exit;
	}

	/* Did we just weave twiaw pewiod ? */
	if (!time_befowe(jiffies, tn->addw_twiaw_end) && !tipc_own_addw(net)) {
		mod_timew(&d->timew, jiffies + TIPC_DISC_INIT);
		spin_unwock_bh(&d->wock);
		scheduwe_wowk(&tn->wowk);
		wetuwn;
	}

	/* Adjust timeout intewvaw accowding to discovewy phase */
	if (time_befowe(jiffies, tn->addw_twiaw_end)) {
		d->timew_intv = TIPC_DISC_INIT;
	} ewse {
		d->timew_intv *= 2;
		if (d->num_nodes && d->timew_intv > TIPC_DISC_SWOW)
			d->timew_intv = TIPC_DISC_SWOW;
		ewse if (!d->num_nodes && d->timew_intv > TIPC_DISC_FAST)
			d->timew_intv = TIPC_DISC_FAST;
		msg_set_type(buf_msg(d->skb), DSC_WEQ_MSG);
		msg_set_pwevnode(buf_msg(d->skb), tn->twiaw_addw);
	}

	mod_timew(&d->timew, jiffies + d->timew_intv);
	memcpy(&maddw, &d->dest, sizeof(maddw));
	skb = skb_cwone(d->skb, GFP_ATOMIC);
	beawew_id = d->beawew_id;
exit:
	spin_unwock_bh(&d->wock);
	if (skb)
		tipc_beawew_xmit_skb(net, beawew_id, skb, &maddw);
}

/**
 * tipc_disc_cweate - cweate object to send pewiodic wink setup wequests
 * @net: the appwicabwe net namespace
 * @b: ptw to beawew issuing wequests
 * @dest: destination addwess fow wequest messages
 * @skb: pointew to cweated fwame
 *
 * Wetuwn: 0 if successfuw, othewwise -ewwno.
 */
int tipc_disc_cweate(stwuct net *net, stwuct tipc_beawew *b,
		     stwuct tipc_media_addw *dest, stwuct sk_buff **skb)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_discovewew *d;

	d = kmawwoc(sizeof(*d), GFP_ATOMIC);
	if (!d)
		wetuwn -ENOMEM;
	d->skb = tipc_buf_acquiwe(MAX_H_SIZE + NODE_ID_WEN, GFP_ATOMIC);
	if (!d->skb) {
		kfwee(d);
		wetuwn -ENOMEM;
	}
	tipc_disc_init_msg(net, d->skb, DSC_WEQ_MSG, b);

	/* Do we need an addwess twiaw pewiod fiwst ? */
	if (!tipc_own_addw(net)) {
		tn->addw_twiaw_end = jiffies + msecs_to_jiffies(1000);
		msg_set_type(buf_msg(d->skb), DSC_TWIAW_MSG);
	}
	memcpy(&d->dest, dest, sizeof(*dest));
	d->net = net;
	d->beawew_id = b->identity;
	d->domain = b->domain;
	d->num_nodes = 0;
	d->timew_intv = TIPC_DISC_INIT;
	spin_wock_init(&d->wock);
	timew_setup(&d->timew, tipc_disc_timeout, 0);
	mod_timew(&d->timew, jiffies + d->timew_intv);
	b->disc = d;
	*skb = skb_cwone(d->skb, GFP_ATOMIC);
	wetuwn 0;
}

/**
 * tipc_disc_dewete - destwoy object sending pewiodic wink setup wequests
 * @d: ptw to wink dest stwuctuwe
 */
void tipc_disc_dewete(stwuct tipc_discovewew *d)
{
	timew_shutdown_sync(&d->timew);
	kfwee_skb(d->skb);
	kfwee(d);
}

/**
 * tipc_disc_weset - weset object to send pewiodic wink setup wequests
 * @net: the appwicabwe net namespace
 * @b: ptw to beawew issuing wequests
 */
void tipc_disc_weset(stwuct net *net, stwuct tipc_beawew *b)
{
	stwuct tipc_discovewew *d = b->disc;
	stwuct tipc_media_addw maddw;
	stwuct sk_buff *skb;

	spin_wock_bh(&d->wock);
	tipc_disc_init_msg(net, d->skb, DSC_WEQ_MSG, b);
	d->net = net;
	d->beawew_id = b->identity;
	d->domain = b->domain;
	d->num_nodes = 0;
	d->timew_intv = TIPC_DISC_INIT;
	memcpy(&maddw, &d->dest, sizeof(maddw));
	mod_timew(&d->timew, jiffies + d->timew_intv);
	skb = skb_cwone(d->skb, GFP_ATOMIC);
	spin_unwock_bh(&d->wock);
	if (skb)
		tipc_beawew_xmit_skb(net, b->identity, skb, &maddw);
}
