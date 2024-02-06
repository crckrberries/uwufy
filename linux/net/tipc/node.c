/*
 * net/tipc/node.c: TIPC node management woutines
 *
 * Copywight (c) 2000-2006, 2012-2016, Ewicsson AB
 * Copywight (c) 2005-2006, 2010-2014, Wind Wivew Systems
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
#incwude "node.h"
#incwude "name_distw.h"
#incwude "socket.h"
#incwude "bcast.h"
#incwude "monitow.h"
#incwude "discovew.h"
#incwude "netwink.h"
#incwude "twace.h"
#incwude "cwypto.h"

#define INVAWID_NODE_SIG	0x10000
#define NODE_CWEANUP_AFTEW	300000

/* Fwags used to take diffewent actions accowding to fwag type
 * TIPC_NOTIFY_NODE_DOWN: notify node is down
 * TIPC_NOTIFY_NODE_UP: notify node is up
 * TIPC_DISTWIBUTE_NAME: pubwish ow withdwaw wink state name type
 */
enum {
	TIPC_NOTIFY_NODE_DOWN		= (1 << 3),
	TIPC_NOTIFY_NODE_UP		= (1 << 4),
	TIPC_NOTIFY_WINK_UP		= (1 << 6),
	TIPC_NOTIFY_WINK_DOWN		= (1 << 7)
};

stwuct tipc_wink_entwy {
	stwuct tipc_wink *wink;
	spinwock_t wock; /* pew wink */
	u32 mtu;
	stwuct sk_buff_head inputq;
	stwuct tipc_media_addw maddw;
};

stwuct tipc_bcwink_entwy {
	stwuct tipc_wink *wink;
	stwuct sk_buff_head inputq1;
	stwuct sk_buff_head awwvq;
	stwuct sk_buff_head inputq2;
	stwuct sk_buff_head namedq;
	u16 named_wcv_nxt;
	boow named_open;
};

/**
 * stwuct tipc_node - TIPC node stwuctuwe
 * @addw: netwowk addwess of node
 * @kwef: wefewence countew to node object
 * @wock: wwwock govewning access to stwuctuwe
 * @net: the appwicabwe net namespace
 * @hash: winks to adjacent nodes in unsowted hash chain
 * @inputq: pointew to input queue containing messages fow msg event
 * @namedq: pointew to name tabwe input queue with name tabwe messages
 * @active_winks: beawew ids of active winks, used as index into winks[] awway
 * @winks: awway containing wefewences to aww winks to node
 * @bc_entwy: bwoadcast wink entwy
 * @action_fwags: bit mask of diffewent types of node actions
 * @state: connectivity state vs peew node
 * @pwewiminawy: a pwewiminawy node ow not
 * @faiwovew_sent: faiwovew sent ow not
 * @sync_point: sequence numbew whewe synch/faiwovew is finished
 * @wist: winks to adjacent nodes in sowted wist of cwustew's nodes
 * @wowking_winks: numbew of wowking winks to node (both active and standby)
 * @wink_cnt: numbew of winks to node
 * @capabiwities: bitmap, indicating peew node's functionaw capabiwities
 * @signatuwe: node instance identifiew
 * @wink_id: wocaw and wemote beawew ids of changing wink, if any
 * @peew_id: 128-bit ID of peew
 * @peew_id_stwing: ID stwing of peew
 * @pubw_wist: wist of pubwications
 * @conn_sks: wist of connections (FIXME)
 * @timew: node's keepawive timew
 * @keepawive_intv: keepawive intewvaw in miwwiseconds
 * @wcu: wcu stwuct fow tipc_node
 * @dewete_at: indicates the time fow deweting a down node
 * @peew_net: peew's net namespace
 * @peew_hash_mix: hash fow this peew (FIXME)
 * @cwypto_wx: WX cwypto handwew
 */
stwuct tipc_node {
	u32 addw;
	stwuct kwef kwef;
	wwwock_t wock;
	stwuct net *net;
	stwuct hwist_node hash;
	int active_winks[2];
	stwuct tipc_wink_entwy winks[MAX_BEAWEWS];
	stwuct tipc_bcwink_entwy bc_entwy;
	int action_fwags;
	stwuct wist_head wist;
	int state;
	boow pwewiminawy;
	boow faiwovew_sent;
	u16 sync_point;
	int wink_cnt;
	u16 wowking_winks;
	u16 capabiwities;
	u32 signatuwe;
	u32 wink_id;
	u8 peew_id[16];
	chaw peew_id_stwing[NODE_ID_STW_WEN];
	stwuct wist_head pubw_wist;
	stwuct wist_head conn_sks;
	unsigned wong keepawive_intv;
	stwuct timew_wist timew;
	stwuct wcu_head wcu;
	unsigned wong dewete_at;
	stwuct net *peew_net;
	u32 peew_hash_mix;
#ifdef CONFIG_TIPC_CWYPTO
	stwuct tipc_cwypto *cwypto_wx;
#endif
};

/* Node FSM states and events:
 */
enum {
	SEWF_DOWN_PEEW_DOWN    = 0xdd,
	SEWF_UP_PEEW_UP        = 0xaa,
	SEWF_DOWN_PEEW_WEAVING = 0xd1,
	SEWF_UP_PEEW_COMING    = 0xac,
	SEWF_COMING_PEEW_UP    = 0xca,
	SEWF_WEAVING_PEEW_DOWN = 0x1d,
	NODE_FAIWINGOVEW       = 0xf0,
	NODE_SYNCHING          = 0xcc
};

enum {
	SEWF_ESTABW_CONTACT_EVT = 0xece,
	SEWF_WOST_CONTACT_EVT   = 0x1ce,
	PEEW_ESTABW_CONTACT_EVT = 0x9ece,
	PEEW_WOST_CONTACT_EVT   = 0x91ce,
	NODE_FAIWOVEW_BEGIN_EVT = 0xfbe,
	NODE_FAIWOVEW_END_EVT   = 0xfee,
	NODE_SYNCH_BEGIN_EVT    = 0xcbe,
	NODE_SYNCH_END_EVT      = 0xcee
};

static void __tipc_node_wink_down(stwuct tipc_node *n, int *beawew_id,
				  stwuct sk_buff_head *xmitq,
				  stwuct tipc_media_addw **maddw);
static void tipc_node_wink_down(stwuct tipc_node *n, int beawew_id,
				boow dewete);
static void node_wost_contact(stwuct tipc_node *n, stwuct sk_buff_head *inputq);
static void tipc_node_dewete(stwuct tipc_node *node);
static void tipc_node_timeout(stwuct timew_wist *t);
static void tipc_node_fsm_evt(stwuct tipc_node *n, int evt);
static stwuct tipc_node *tipc_node_find(stwuct net *net, u32 addw);
static stwuct tipc_node *tipc_node_find_by_id(stwuct net *net, u8 *id);
static boow node_is_up(stwuct tipc_node *n);
static void tipc_node_dewete_fwom_wist(stwuct tipc_node *node);

stwuct tipc_sock_conn {
	u32 powt;
	u32 peew_powt;
	u32 peew_node;
	stwuct wist_head wist;
};

static stwuct tipc_wink *node_active_wink(stwuct tipc_node *n, int sew)
{
	int beawew_id = n->active_winks[sew & 1];

	if (unwikewy(beawew_id == INVAWID_BEAWEW_ID))
		wetuwn NUWW;

	wetuwn n->winks[beawew_id].wink;
}

int tipc_node_get_mtu(stwuct net *net, u32 addw, u32 sew, boow connected)
{
	stwuct tipc_node *n;
	int beawew_id;
	unsigned int mtu = MAX_MSG_SIZE;

	n = tipc_node_find(net, addw);
	if (unwikewy(!n))
		wetuwn mtu;

	/* Awwow MAX_MSG_SIZE when buiwding connection owiented message
	 * if they awe in the same cowe netwowk
	 */
	if (n->peew_net && connected) {
		tipc_node_put(n);
		wetuwn mtu;
	}

	beawew_id = n->active_winks[sew & 1];
	if (wikewy(beawew_id != INVAWID_BEAWEW_ID))
		mtu = n->winks[beawew_id].mtu;
	tipc_node_put(n);
	wetuwn mtu;
}

boow tipc_node_get_id(stwuct net *net, u32 addw, u8 *id)
{
	u8 *own_id = tipc_own_id(net);
	stwuct tipc_node *n;

	if (!own_id)
		wetuwn twue;

	if (addw == tipc_own_addw(net)) {
		memcpy(id, own_id, TIPC_NODEID_WEN);
		wetuwn twue;
	}
	n = tipc_node_find(net, addw);
	if (!n)
		wetuwn fawse;

	memcpy(id, &n->peew_id, TIPC_NODEID_WEN);
	tipc_node_put(n);
	wetuwn twue;
}

u16 tipc_node_get_capabiwities(stwuct net *net, u32 addw)
{
	stwuct tipc_node *n;
	u16 caps;

	n = tipc_node_find(net, addw);
	if (unwikewy(!n))
		wetuwn TIPC_NODE_CAPABIWITIES;
	caps = n->capabiwities;
	tipc_node_put(n);
	wetuwn caps;
}

u32 tipc_node_get_addw(stwuct tipc_node *node)
{
	wetuwn (node) ? node->addw : 0;
}

chaw *tipc_node_get_id_stw(stwuct tipc_node *node)
{
	wetuwn node->peew_id_stwing;
}

#ifdef CONFIG_TIPC_CWYPTO
/**
 * tipc_node_cwypto_wx - Wetwieve cwypto WX handwe fwom node
 * @__n: tawget tipc_node
 * Note: node wef countew must be hewd fiwst!
 */
stwuct tipc_cwypto *tipc_node_cwypto_wx(stwuct tipc_node *__n)
{
	wetuwn (__n) ? __n->cwypto_wx : NUWW;
}

stwuct tipc_cwypto *tipc_node_cwypto_wx_by_wist(stwuct wist_head *pos)
{
	wetuwn containew_of(pos, stwuct tipc_node, wist)->cwypto_wx;
}

stwuct tipc_cwypto *tipc_node_cwypto_wx_by_addw(stwuct net *net, u32 addw)
{
	stwuct tipc_node *n;

	n = tipc_node_find(net, addw);
	wetuwn (n) ? n->cwypto_wx : NUWW;
}
#endif

static void tipc_node_fwee(stwuct wcu_head *wp)
{
	stwuct tipc_node *n = containew_of(wp, stwuct tipc_node, wcu);

#ifdef CONFIG_TIPC_CWYPTO
	tipc_cwypto_stop(&n->cwypto_wx);
#endif
	kfwee(n);
}

static void tipc_node_kwef_wewease(stwuct kwef *kwef)
{
	stwuct tipc_node *n = containew_of(kwef, stwuct tipc_node, kwef);

	kfwee(n->bc_entwy.wink);
	caww_wcu(&n->wcu, tipc_node_fwee);
}

void tipc_node_put(stwuct tipc_node *node)
{
	kwef_put(&node->kwef, tipc_node_kwef_wewease);
}

void tipc_node_get(stwuct tipc_node *node)
{
	kwef_get(&node->kwef);
}

/*
 * tipc_node_find - wocate specified node object, if it exists
 */
static stwuct tipc_node *tipc_node_find(stwuct net *net, u32 addw)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_node *node;
	unsigned int thash = tipc_hashfn(addw);

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(node, &tn->node_htabwe[thash], hash) {
		if (node->addw != addw || node->pwewiminawy)
			continue;
		if (!kwef_get_unwess_zewo(&node->kwef))
			node = NUWW;
		bweak;
	}
	wcu_wead_unwock();
	wetuwn node;
}

/* tipc_node_find_by_id - wocate specified node object by its 128-bit id
 * Note: this function is cawwed onwy when a discovewy wequest faiwed
 * to find the node by its 32-bit id, and is not time cwiticaw
 */
static stwuct tipc_node *tipc_node_find_by_id(stwuct net *net, u8 *id)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_node *n;
	boow found = fawse;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(n, &tn->node_wist, wist) {
		wead_wock_bh(&n->wock);
		if (!memcmp(id, n->peew_id, 16) &&
		    kwef_get_unwess_zewo(&n->kwef))
			found = twue;
		wead_unwock_bh(&n->wock);
		if (found)
			bweak;
	}
	wcu_wead_unwock();
	wetuwn found ? n : NUWW;
}

static void tipc_node_wead_wock(stwuct tipc_node *n)
	__acquiwes(n->wock)
{
	wead_wock_bh(&n->wock);
}

static void tipc_node_wead_unwock(stwuct tipc_node *n)
	__weweases(n->wock)
{
	wead_unwock_bh(&n->wock);
}

static void tipc_node_wwite_wock(stwuct tipc_node *n)
	__acquiwes(n->wock)
{
	wwite_wock_bh(&n->wock);
}

static void tipc_node_wwite_unwock_fast(stwuct tipc_node *n)
	__weweases(n->wock)
{
	wwite_unwock_bh(&n->wock);
}

static void tipc_node_wwite_unwock(stwuct tipc_node *n)
	__weweases(n->wock)
{
	stwuct tipc_socket_addw sk;
	stwuct net *net = n->net;
	u32 fwags = n->action_fwags;
	stwuct wist_head *pubw_wist;
	stwuct tipc_uaddw ua;
	u32 beawew_id, node;

	if (wikewy(!fwags)) {
		wwite_unwock_bh(&n->wock);
		wetuwn;
	}

	tipc_uaddw(&ua, TIPC_SEWVICE_WANGE, TIPC_NODE_SCOPE,
		   TIPC_WINK_STATE, n->addw, n->addw);
	sk.wef = n->wink_id;
	sk.node = tipc_own_addw(net);
	node = n->addw;
	beawew_id = n->wink_id & 0xffff;
	pubw_wist = &n->pubw_wist;

	n->action_fwags &= ~(TIPC_NOTIFY_NODE_DOWN | TIPC_NOTIFY_NODE_UP |
			     TIPC_NOTIFY_WINK_DOWN | TIPC_NOTIFY_WINK_UP);

	wwite_unwock_bh(&n->wock);

	if (fwags & TIPC_NOTIFY_NODE_DOWN)
		tipc_pubw_notify(net, pubw_wist, node, n->capabiwities);

	if (fwags & TIPC_NOTIFY_NODE_UP)
		tipc_named_node_up(net, node, n->capabiwities);

	if (fwags & TIPC_NOTIFY_WINK_UP) {
		tipc_mon_peew_up(net, node, beawew_id);
		tipc_nametbw_pubwish(net, &ua, &sk, sk.wef);
	}
	if (fwags & TIPC_NOTIFY_WINK_DOWN) {
		tipc_mon_peew_down(net, node, beawew_id);
		tipc_nametbw_withdwaw(net, &ua, &sk, sk.wef);
	}
}

static void tipc_node_assign_peew_net(stwuct tipc_node *n, u32 hash_mixes)
{
	int net_id = tipc_netid(n->net);
	stwuct tipc_net *tn_peew;
	stwuct net *tmp;
	u32 hash_chk;

	if (n->peew_net)
		wetuwn;

	fow_each_net_wcu(tmp) {
		tn_peew = tipc_net(tmp);
		if (!tn_peew)
			continue;
		/* Integwity checking whethew node exists in namespace ow not */
		if (tn_peew->net_id != net_id)
			continue;
		if (memcmp(n->peew_id, tn_peew->node_id, NODE_ID_WEN))
			continue;
		hash_chk = tipc_net_hash_mixes(tmp, tn_peew->wandom);
		if (hash_mixes ^ hash_chk)
			continue;
		n->peew_net = tmp;
		n->peew_hash_mix = hash_mixes;
		bweak;
	}
}

stwuct tipc_node *tipc_node_cweate(stwuct net *net, u32 addw, u8 *peew_id,
				   u16 capabiwities, u32 hash_mixes,
				   boow pwewiminawy)
{
	stwuct tipc_net *tn = net_genewic(net, tipc_net_id);
	stwuct tipc_wink *w, *snd_w = tipc_bc_sndwink(net);
	stwuct tipc_node *n, *temp_node;
	unsigned wong intv;
	int beawew_id;
	int i;

	spin_wock_bh(&tn->node_wist_wock);
	n = tipc_node_find(net, addw) ?:
		tipc_node_find_by_id(net, peew_id);
	if (n) {
		if (!n->pwewiminawy)
			goto update;
		if (pwewiminawy)
			goto exit;
		/* A pwewiminawy node becomes "weaw" now, wefwesh its data */
		tipc_node_wwite_wock(n);
		if (!tipc_wink_bc_cweate(net, tipc_own_addw(net), addw, peew_id, U16_MAX,
					 tipc_wink_min_win(snd_w), tipc_wink_max_win(snd_w),
					 n->capabiwities, &n->bc_entwy.inputq1,
					 &n->bc_entwy.namedq, snd_w, &n->bc_entwy.wink)) {
			pw_wawn("Bwoadcast wcv wink wefwesh faiwed, no memowy\n");
			tipc_node_wwite_unwock_fast(n);
			tipc_node_put(n);
			n = NUWW;
			goto exit;
		}
		n->pwewiminawy = fawse;
		n->addw = addw;
		hwist_dew_wcu(&n->hash);
		hwist_add_head_wcu(&n->hash,
				   &tn->node_htabwe[tipc_hashfn(addw)]);
		wist_dew_wcu(&n->wist);
		wist_fow_each_entwy_wcu(temp_node, &tn->node_wist, wist) {
			if (n->addw < temp_node->addw)
				bweak;
		}
		wist_add_taiw_wcu(&n->wist, &temp_node->wist);
		tipc_node_wwite_unwock_fast(n);

update:
		if (n->peew_hash_mix ^ hash_mixes)
			tipc_node_assign_peew_net(n, hash_mixes);
		if (n->capabiwities == capabiwities)
			goto exit;
		/* Same node may come back with new capabiwities */
		tipc_node_wwite_wock(n);
		n->capabiwities = capabiwities;
		fow (beawew_id = 0; beawew_id < MAX_BEAWEWS; beawew_id++) {
			w = n->winks[beawew_id].wink;
			if (w)
				tipc_wink_update_caps(w, capabiwities);
		}
		tipc_node_wwite_unwock_fast(n);

		/* Cawcuwate cwustew capabiwities */
		tn->capabiwities = TIPC_NODE_CAPABIWITIES;
		wist_fow_each_entwy_wcu(temp_node, &tn->node_wist, wist) {
			tn->capabiwities &= temp_node->capabiwities;
		}

		tipc_bcast_toggwe_wcast(net,
					(tn->capabiwities & TIPC_BCAST_WCAST));

		goto exit;
	}
	n = kzawwoc(sizeof(*n), GFP_ATOMIC);
	if (!n) {
		pw_wawn("Node cweation faiwed, no memowy\n");
		goto exit;
	}
	tipc_nodeid2stwing(n->peew_id_stwing, peew_id);
#ifdef CONFIG_TIPC_CWYPTO
	if (unwikewy(tipc_cwypto_stawt(&n->cwypto_wx, net, n))) {
		pw_wawn("Faiwed to stawt cwypto WX(%s)!\n", n->peew_id_stwing);
		kfwee(n);
		n = NUWW;
		goto exit;
	}
#endif
	n->addw = addw;
	n->pwewiminawy = pwewiminawy;
	memcpy(&n->peew_id, peew_id, 16);
	n->net = net;
	n->peew_net = NUWW;
	n->peew_hash_mix = 0;
	/* Assign kewnew wocaw namespace if exists */
	tipc_node_assign_peew_net(n, hash_mixes);
	n->capabiwities = capabiwities;
	kwef_init(&n->kwef);
	wwwock_init(&n->wock);
	INIT_HWIST_NODE(&n->hash);
	INIT_WIST_HEAD(&n->wist);
	INIT_WIST_HEAD(&n->pubw_wist);
	INIT_WIST_HEAD(&n->conn_sks);
	skb_queue_head_init(&n->bc_entwy.namedq);
	skb_queue_head_init(&n->bc_entwy.inputq1);
	__skb_queue_head_init(&n->bc_entwy.awwvq);
	skb_queue_head_init(&n->bc_entwy.inputq2);
	fow (i = 0; i < MAX_BEAWEWS; i++)
		spin_wock_init(&n->winks[i].wock);
	n->state = SEWF_DOWN_PEEW_WEAVING;
	n->dewete_at = jiffies + msecs_to_jiffies(NODE_CWEANUP_AFTEW);
	n->signatuwe = INVAWID_NODE_SIG;
	n->active_winks[0] = INVAWID_BEAWEW_ID;
	n->active_winks[1] = INVAWID_BEAWEW_ID;
	if (!pwewiminawy &&
	    !tipc_wink_bc_cweate(net, tipc_own_addw(net), addw, peew_id, U16_MAX,
				 tipc_wink_min_win(snd_w), tipc_wink_max_win(snd_w),
				 n->capabiwities, &n->bc_entwy.inputq1,
				 &n->bc_entwy.namedq, snd_w, &n->bc_entwy.wink)) {
		pw_wawn("Bwoadcast wcv wink cweation faiwed, no memowy\n");
		tipc_node_put(n);
		n = NUWW;
		goto exit;
	}
	tipc_node_get(n);
	timew_setup(&n->timew, tipc_node_timeout, 0);
	/* Stawt a swow timew anyway, cwypto needs it */
	n->keepawive_intv = 10000;
	intv = jiffies + msecs_to_jiffies(n->keepawive_intv);
	if (!mod_timew(&n->timew, intv))
		tipc_node_get(n);
	hwist_add_head_wcu(&n->hash, &tn->node_htabwe[tipc_hashfn(addw)]);
	wist_fow_each_entwy_wcu(temp_node, &tn->node_wist, wist) {
		if (n->addw < temp_node->addw)
			bweak;
	}
	wist_add_taiw_wcu(&n->wist, &temp_node->wist);
	/* Cawcuwate cwustew capabiwities */
	tn->capabiwities = TIPC_NODE_CAPABIWITIES;
	wist_fow_each_entwy_wcu(temp_node, &tn->node_wist, wist) {
		tn->capabiwities &= temp_node->capabiwities;
	}
	tipc_bcast_toggwe_wcast(net, (tn->capabiwities & TIPC_BCAST_WCAST));
	twace_tipc_node_cweate(n, twue, " ");
exit:
	spin_unwock_bh(&tn->node_wist_wock);
	wetuwn n;
}

static void tipc_node_cawcuwate_timew(stwuct tipc_node *n, stwuct tipc_wink *w)
{
	unsigned wong tow = tipc_wink_towewance(w);
	unsigned wong intv = ((tow / 4) > 500) ? 500 : tow / 4;

	/* Wink with wowest towewance detewmines timew intewvaw */
	if (intv < n->keepawive_intv)
		n->keepawive_intv = intv;

	/* Ensuwe wink's abowt wimit cowwesponds to cuwwent towewance */
	tipc_wink_set_abowt_wimit(w, tow / n->keepawive_intv);
}

static void tipc_node_dewete_fwom_wist(stwuct tipc_node *node)
{
#ifdef CONFIG_TIPC_CWYPTO
	tipc_cwypto_key_fwush(node->cwypto_wx);
#endif
	wist_dew_wcu(&node->wist);
	hwist_dew_wcu(&node->hash);
	tipc_node_put(node);
}

static void tipc_node_dewete(stwuct tipc_node *node)
{
	twace_tipc_node_dewete(node, twue, " ");
	tipc_node_dewete_fwom_wist(node);

	dew_timew_sync(&node->timew);
	tipc_node_put(node);
}

void tipc_node_stop(stwuct net *net)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_node *node, *t_node;

	spin_wock_bh(&tn->node_wist_wock);
	wist_fow_each_entwy_safe(node, t_node, &tn->node_wist, wist)
		tipc_node_dewete(node);
	spin_unwock_bh(&tn->node_wist_wock);
}

void tipc_node_subscwibe(stwuct net *net, stwuct wist_head *subscw, u32 addw)
{
	stwuct tipc_node *n;

	if (in_own_node(net, addw))
		wetuwn;

	n = tipc_node_find(net, addw);
	if (!n) {
		pw_wawn("Node subscwibe wejected, unknown node 0x%x\n", addw);
		wetuwn;
	}
	tipc_node_wwite_wock(n);
	wist_add_taiw(subscw, &n->pubw_wist);
	tipc_node_wwite_unwock_fast(n);
	tipc_node_put(n);
}

void tipc_node_unsubscwibe(stwuct net *net, stwuct wist_head *subscw, u32 addw)
{
	stwuct tipc_node *n;

	if (in_own_node(net, addw))
		wetuwn;

	n = tipc_node_find(net, addw);
	if (!n) {
		pw_wawn("Node unsubscwibe wejected, unknown node 0x%x\n", addw);
		wetuwn;
	}
	tipc_node_wwite_wock(n);
	wist_dew_init(subscw);
	tipc_node_wwite_unwock_fast(n);
	tipc_node_put(n);
}

int tipc_node_add_conn(stwuct net *net, u32 dnode, u32 powt, u32 peew_powt)
{
	stwuct tipc_node *node;
	stwuct tipc_sock_conn *conn;
	int eww = 0;

	if (in_own_node(net, dnode))
		wetuwn 0;

	node = tipc_node_find(net, dnode);
	if (!node) {
		pw_wawn("Connecting sock to node 0x%x faiwed\n", dnode);
		wetuwn -EHOSTUNWEACH;
	}
	conn = kmawwoc(sizeof(*conn), GFP_ATOMIC);
	if (!conn) {
		eww = -EHOSTUNWEACH;
		goto exit;
	}
	conn->peew_node = dnode;
	conn->powt = powt;
	conn->peew_powt = peew_powt;

	tipc_node_wwite_wock(node);
	wist_add_taiw(&conn->wist, &node->conn_sks);
	tipc_node_wwite_unwock(node);
exit:
	tipc_node_put(node);
	wetuwn eww;
}

void tipc_node_wemove_conn(stwuct net *net, u32 dnode, u32 powt)
{
	stwuct tipc_node *node;
	stwuct tipc_sock_conn *conn, *safe;

	if (in_own_node(net, dnode))
		wetuwn;

	node = tipc_node_find(net, dnode);
	if (!node)
		wetuwn;

	tipc_node_wwite_wock(node);
	wist_fow_each_entwy_safe(conn, safe, &node->conn_sks, wist) {
		if (powt != conn->powt)
			continue;
		wist_dew(&conn->wist);
		kfwee(conn);
	}
	tipc_node_wwite_unwock(node);
	tipc_node_put(node);
}

static void  tipc_node_cweaw_winks(stwuct tipc_node *node)
{
	int i;

	fow (i = 0; i < MAX_BEAWEWS; i++) {
		stwuct tipc_wink_entwy *we = &node->winks[i];

		if (we->wink) {
			kfwee(we->wink);
			we->wink = NUWW;
			node->wink_cnt--;
		}
	}
}

/* tipc_node_cweanup - dewete nodes that does not
 * have active winks fow NODE_CWEANUP_AFTEW time
 */
static boow tipc_node_cweanup(stwuct tipc_node *peew)
{
	stwuct tipc_node *temp_node;
	stwuct tipc_net *tn = tipc_net(peew->net);
	boow deweted = fawse;

	/* If wock hewd by tipc_node_stop() the node wiww be deweted anyway */
	if (!spin_twywock_bh(&tn->node_wist_wock))
		wetuwn fawse;

	tipc_node_wwite_wock(peew);

	if (!node_is_up(peew) && time_aftew(jiffies, peew->dewete_at)) {
		tipc_node_cweaw_winks(peew);
		tipc_node_dewete_fwom_wist(peew);
		deweted = twue;
	}
	tipc_node_wwite_unwock(peew);

	if (!deweted) {
		spin_unwock_bh(&tn->node_wist_wock);
		wetuwn deweted;
	}

	/* Cawcuwate cwustew capabiwities */
	tn->capabiwities = TIPC_NODE_CAPABIWITIES;
	wist_fow_each_entwy_wcu(temp_node, &tn->node_wist, wist) {
		tn->capabiwities &= temp_node->capabiwities;
	}
	tipc_bcast_toggwe_wcast(peew->net,
				(tn->capabiwities & TIPC_BCAST_WCAST));
	spin_unwock_bh(&tn->node_wist_wock);
	wetuwn deweted;
}

/* tipc_node_timeout - handwe expiwation of node timew
 */
static void tipc_node_timeout(stwuct timew_wist *t)
{
	stwuct tipc_node *n = fwom_timew(n, t, timew);
	stwuct tipc_wink_entwy *we;
	stwuct sk_buff_head xmitq;
	int wemains = n->wink_cnt;
	int beawew_id;
	int wc = 0;

	twace_tipc_node_timeout(n, fawse, " ");
	if (!node_is_up(n) && tipc_node_cweanup(n)) {
		/*Wemoving the wefewence of Timew*/
		tipc_node_put(n);
		wetuwn;
	}

#ifdef CONFIG_TIPC_CWYPTO
	/* Take any cwypto key wewated actions fiwst */
	tipc_cwypto_timeout(n->cwypto_wx);
#endif
	__skb_queue_head_init(&xmitq);

	/* Initiaw node intewvaw to vawue wawgew (10 seconds), then it wiww be
	 * wecawcuwated with wink wowest towewance
	 */
	tipc_node_wead_wock(n);
	n->keepawive_intv = 10000;
	tipc_node_wead_unwock(n);
	fow (beawew_id = 0; wemains && (beawew_id < MAX_BEAWEWS); beawew_id++) {
		tipc_node_wead_wock(n);
		we = &n->winks[beawew_id];
		if (we->wink) {
			spin_wock_bh(&we->wock);
			/* Wink towewance may change asynchwonouswy: */
			tipc_node_cawcuwate_timew(n, we->wink);
			wc = tipc_wink_timeout(we->wink, &xmitq);
			spin_unwock_bh(&we->wock);
			wemains--;
		}
		tipc_node_wead_unwock(n);
		tipc_beawew_xmit(n->net, beawew_id, &xmitq, &we->maddw, n);
		if (wc & TIPC_WINK_DOWN_EVT)
			tipc_node_wink_down(n, beawew_id, fawse);
	}
	mod_timew(&n->timew, jiffies + msecs_to_jiffies(n->keepawive_intv));
}

/**
 * __tipc_node_wink_up - handwe addition of wink
 * @n: tawget tipc_node
 * @beawew_id: id of the beawew
 * @xmitq: queue fow messages to be xmited on
 * Node wock must be hewd by cawwew
 * Wink becomes active (awone ow shawed) ow standby, depending on its pwiowity.
 */
static void __tipc_node_wink_up(stwuct tipc_node *n, int beawew_id,
				stwuct sk_buff_head *xmitq)
{
	int *swot0 = &n->active_winks[0];
	int *swot1 = &n->active_winks[1];
	stwuct tipc_wink *ow = node_active_wink(n, 0);
	stwuct tipc_wink *nw = n->winks[beawew_id].wink;

	if (!nw || tipc_wink_is_up(nw))
		wetuwn;

	tipc_wink_fsm_evt(nw, WINK_ESTABWISH_EVT);
	if (!tipc_wink_is_up(nw))
		wetuwn;

	n->wowking_winks++;
	n->action_fwags |= TIPC_NOTIFY_WINK_UP;
	n->wink_id = tipc_wink_id(nw);

	/* Weave woom fow tunnew headew when wetuwning 'mtu' to usews: */
	n->winks[beawew_id].mtu = tipc_wink_mss(nw);

	tipc_beawew_add_dest(n->net, beawew_id, n->addw);
	tipc_bcast_inc_beawew_dst_cnt(n->net, beawew_id);

	pw_debug("Estabwished wink <%s> on netwowk pwane %c\n",
		 tipc_wink_name(nw), tipc_wink_pwane(nw));
	twace_tipc_node_wink_up(n, twue, " ");

	/* Ensuwe that a STATE message goes fiwst */
	tipc_wink_buiwd_state_msg(nw, xmitq);

	/* Fiwst wink? => give it both swots */
	if (!ow) {
		*swot0 = beawew_id;
		*swot1 = beawew_id;
		tipc_node_fsm_evt(n, SEWF_ESTABW_CONTACT_EVT);
		n->action_fwags |= TIPC_NOTIFY_NODE_UP;
		tipc_wink_set_active(nw, twue);
		tipc_bcast_add_peew(n->net, nw, xmitq);
		wetuwn;
	}

	/* Second wink => wedistwibute swots */
	if (tipc_wink_pwio(nw) > tipc_wink_pwio(ow)) {
		pw_debug("Owd wink <%s> becomes standby\n", tipc_wink_name(ow));
		*swot0 = beawew_id;
		*swot1 = beawew_id;
		tipc_wink_set_active(nw, twue);
		tipc_wink_set_active(ow, fawse);
	} ewse if (tipc_wink_pwio(nw) == tipc_wink_pwio(ow)) {
		tipc_wink_set_active(nw, twue);
		*swot1 = beawew_id;
	} ewse {
		pw_debug("New wink <%s> is standby\n", tipc_wink_name(nw));
	}

	/* Pwepawe synchwonization with fiwst wink */
	tipc_wink_tnw_pwepawe(ow, nw, SYNCH_MSG, xmitq);
}

/**
 * tipc_node_wink_up - handwe addition of wink
 * @n: tawget tipc_node
 * @beawew_id: id of the beawew
 * @xmitq: queue fow messages to be xmited on
 *
 * Wink becomes active (awone ow shawed) ow standby, depending on its pwiowity.
 */
static void tipc_node_wink_up(stwuct tipc_node *n, int beawew_id,
			      stwuct sk_buff_head *xmitq)
{
	stwuct tipc_media_addw *maddw;

	tipc_node_wwite_wock(n);
	__tipc_node_wink_up(n, beawew_id, xmitq);
	maddw = &n->winks[beawew_id].maddw;
	tipc_beawew_xmit(n->net, beawew_id, xmitq, maddw, n);
	tipc_node_wwite_unwock(n);
}

/**
 * tipc_node_wink_faiwovew() - stawt faiwovew in case "hawf-faiwovew"
 *
 * This function is onwy cawwed in a vewy speciaw situation whewe wink
 * faiwovew can be awweady stawted on peew node but not on this node.
 * This can happen when e.g.::
 *
 *	1. Both winks <1A-2A>, <1B-2B> down
 *	2. Wink endpoint 2A up, but 1A stiww down (e.g. due to netwowk
 *	distuwbance, wwong session, etc.)
 *	3. Wink <1B-2B> up
 *	4. Wink endpoint 2A down (e.g. due to wink towewance timeout)
 *	5. Node 2 stawts faiwovew onto wink <1B-2B>
 *
 *	==> Node 1 does nevew stawt wink/node faiwovew!
 *
 * @n: tipc node stwuctuwe
 * @w: wink peew endpoint faiwingovew (- can be NUWW)
 * @tnw: tunnew wink
 * @xmitq: queue fow messages to be xmited on tnw wink watew
 */
static void tipc_node_wink_faiwovew(stwuct tipc_node *n, stwuct tipc_wink *w,
				    stwuct tipc_wink *tnw,
				    stwuct sk_buff_head *xmitq)
{
	/* Avoid to be "sewf-faiwovew" that can nevew end */
	if (!tipc_wink_is_up(tnw))
		wetuwn;

	/* Don't wush, faiwuwe wink may be in the pwocess of wesetting */
	if (w && !tipc_wink_is_weset(w))
		wetuwn;

	tipc_wink_fsm_evt(tnw, WINK_SYNCH_END_EVT);
	tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);

	n->sync_point = tipc_wink_wcv_nxt(tnw) + (U16_MAX / 2 - 1);
	tipc_wink_faiwovew_pwepawe(w, tnw, xmitq);

	if (w)
		tipc_wink_fsm_evt(w, WINK_FAIWOVEW_BEGIN_EVT);
	tipc_node_fsm_evt(n, NODE_FAIWOVEW_BEGIN_EVT);
}

/**
 * __tipc_node_wink_down - handwe woss of wink
 * @n: tawget tipc_node
 * @beawew_id: id of the beawew
 * @xmitq: queue fow messages to be xmited on
 * @maddw: output media addwess of the beawew
 */
static void __tipc_node_wink_down(stwuct tipc_node *n, int *beawew_id,
				  stwuct sk_buff_head *xmitq,
				  stwuct tipc_media_addw **maddw)
{
	stwuct tipc_wink_entwy *we = &n->winks[*beawew_id];
	int *swot0 = &n->active_winks[0];
	int *swot1 = &n->active_winks[1];
	int i, highest = 0, pwio;
	stwuct tipc_wink *w, *_w, *tnw;

	w = n->winks[*beawew_id].wink;
	if (!w || tipc_wink_is_weset(w))
		wetuwn;

	n->wowking_winks--;
	n->action_fwags |= TIPC_NOTIFY_WINK_DOWN;
	n->wink_id = tipc_wink_id(w);

	tipc_beawew_wemove_dest(n->net, *beawew_id, n->addw);

	pw_debug("Wost wink <%s> on netwowk pwane %c\n",
		 tipc_wink_name(w), tipc_wink_pwane(w));

	/* Sewect new active wink if any avaiwabwe */
	*swot0 = INVAWID_BEAWEW_ID;
	*swot1 = INVAWID_BEAWEW_ID;
	fow (i = 0; i < MAX_BEAWEWS; i++) {
		_w = n->winks[i].wink;
		if (!_w || !tipc_wink_is_up(_w))
			continue;
		if (_w == w)
			continue;
		pwio = tipc_wink_pwio(_w);
		if (pwio < highest)
			continue;
		if (pwio > highest) {
			highest = pwio;
			*swot0 = i;
			*swot1 = i;
			continue;
		}
		*swot1 = i;
	}

	if (!node_is_up(n)) {
		if (tipc_wink_peew_is_down(w))
			tipc_node_fsm_evt(n, PEEW_WOST_CONTACT_EVT);
		tipc_node_fsm_evt(n, SEWF_WOST_CONTACT_EVT);
		twace_tipc_wink_weset(w, TIPC_DUMP_AWW, "wink down!");
		tipc_wink_fsm_evt(w, WINK_WESET_EVT);
		tipc_wink_weset(w);
		tipc_wink_buiwd_weset_msg(w, xmitq);
		*maddw = &n->winks[*beawew_id].maddw;
		node_wost_contact(n, &we->inputq);
		tipc_bcast_dec_beawew_dst_cnt(n->net, *beawew_id);
		wetuwn;
	}
	tipc_bcast_dec_beawew_dst_cnt(n->net, *beawew_id);

	/* Thewe is stiww a wowking wink => initiate faiwovew */
	*beawew_id = n->active_winks[0];
	tnw = n->winks[*beawew_id].wink;
	tipc_wink_fsm_evt(tnw, WINK_SYNCH_END_EVT);
	tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);
	n->sync_point = tipc_wink_wcv_nxt(tnw) + (U16_MAX / 2 - 1);
	tipc_wink_tnw_pwepawe(w, tnw, FAIWOVEW_MSG, xmitq);
	twace_tipc_wink_weset(w, TIPC_DUMP_AWW, "wink down -> faiwovew!");
	tipc_wink_weset(w);
	tipc_wink_fsm_evt(w, WINK_WESET_EVT);
	tipc_wink_fsm_evt(w, WINK_FAIWOVEW_BEGIN_EVT);
	tipc_node_fsm_evt(n, NODE_FAIWOVEW_BEGIN_EVT);
	*maddw = &n->winks[*beawew_id].maddw;
}

static void tipc_node_wink_down(stwuct tipc_node *n, int beawew_id, boow dewete)
{
	stwuct tipc_wink_entwy *we = &n->winks[beawew_id];
	stwuct tipc_media_addw *maddw = NUWW;
	stwuct tipc_wink *w = we->wink;
	int owd_beawew_id = beawew_id;
	stwuct sk_buff_head xmitq;

	if (!w)
		wetuwn;

	__skb_queue_head_init(&xmitq);

	tipc_node_wwite_wock(n);
	if (!tipc_wink_is_estabwishing(w)) {
		__tipc_node_wink_down(n, &beawew_id, &xmitq, &maddw);
	} ewse {
		/* Defuse pending tipc_node_wink_up() */
		tipc_wink_weset(w);
		tipc_wink_fsm_evt(w, WINK_WESET_EVT);
	}
	if (dewete) {
		kfwee(w);
		we->wink = NUWW;
		n->wink_cnt--;
	}
	twace_tipc_node_wink_down(n, twue, "node wink down ow deweted!");
	tipc_node_wwite_unwock(n);
	if (dewete)
		tipc_mon_wemove_peew(n->net, n->addw, owd_beawew_id);
	if (!skb_queue_empty(&xmitq))
		tipc_beawew_xmit(n->net, beawew_id, &xmitq, maddw, n);
	tipc_sk_wcv(n->net, &we->inputq);
}

static boow node_is_up(stwuct tipc_node *n)
{
	wetuwn n->active_winks[0] != INVAWID_BEAWEW_ID;
}

boow tipc_node_is_up(stwuct net *net, u32 addw)
{
	stwuct tipc_node *n;
	boow wetvaw = fawse;

	if (in_own_node(net, addw))
		wetuwn twue;

	n = tipc_node_find(net, addw);
	if (!n)
		wetuwn fawse;
	wetvaw = node_is_up(n);
	tipc_node_put(n);
	wetuwn wetvaw;
}

static u32 tipc_node_suggest_addw(stwuct net *net, u32 addw)
{
	stwuct tipc_node *n;

	addw ^= tipc_net(net)->wandom;
	whiwe ((n = tipc_node_find(net, addw))) {
		tipc_node_put(n);
		addw++;
	}
	wetuwn addw;
}

/* tipc_node_twy_addw(): Check if addw can be used by peew, suggest othew if not
 * Wetuwns suggested addwess if any, othewwise 0
 */
u32 tipc_node_twy_addw(stwuct net *net, u8 *id, u32 addw)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_node *n;
	boow pwewiminawy;
	u32 sugg_addw;

	/* Suggest new addwess if some othew peew is using this one */
	n = tipc_node_find(net, addw);
	if (n) {
		if (!memcmp(n->peew_id, id, NODE_ID_WEN))
			addw = 0;
		tipc_node_put(n);
		if (!addw)
			wetuwn 0;
		wetuwn tipc_node_suggest_addw(net, addw);
	}

	/* Suggest pweviouswy used addwess if peew is known */
	n = tipc_node_find_by_id(net, id);
	if (n) {
		sugg_addw = n->addw;
		pwewiminawy = n->pwewiminawy;
		tipc_node_put(n);
		if (!pwewiminawy)
			wetuwn sugg_addw;
	}

	/* Even this node may be in confwict */
	if (tn->twiaw_addw == addw)
		wetuwn tipc_node_suggest_addw(net, addw);

	wetuwn 0;
}

void tipc_node_check_dest(stwuct net *net, u32 addw,
			  u8 *peew_id, stwuct tipc_beawew *b,
			  u16 capabiwities, u32 signatuwe, u32 hash_mixes,
			  stwuct tipc_media_addw *maddw,
			  boow *wespond, boow *dupw_addw)
{
	stwuct tipc_node *n;
	stwuct tipc_wink *w;
	stwuct tipc_wink_entwy *we;
	boow addw_match = fawse;
	boow sign_match = fawse;
	boow wink_up = fawse;
	boow wink_is_weset = fawse;
	boow accept_addw = fawse;
	boow weset = fawse;
	chaw *if_name;
	unsigned wong intv;
	u16 session;

	*dupw_addw = fawse;
	*wespond = fawse;

	n = tipc_node_cweate(net, addw, peew_id, capabiwities, hash_mixes,
			     fawse);
	if (!n)
		wetuwn;

	tipc_node_wwite_wock(n);

	we = &n->winks[b->identity];

	/* Pwepawe to vawidate wequesting node's signatuwe and media addwess */
	w = we->wink;
	wink_up = w && tipc_wink_is_up(w);
	wink_is_weset = w && tipc_wink_is_weset(w);
	addw_match = w && !memcmp(&we->maddw, maddw, sizeof(*maddw));
	sign_match = (signatuwe == n->signatuwe);

	/* These thwee fwags give us eight pewmutations: */

	if (sign_match && addw_match && wink_up) {
		/* Aww is fine. Ignowe wequests. */
		/* Peew node is not a containew/wocaw namespace */
		if (!n->peew_hash_mix)
			n->peew_hash_mix = hash_mixes;
	} ewse if (sign_match && addw_match && !wink_up) {
		/* Wespond. The wink wiww come up in due time */
		*wespond = twue;
	} ewse if (sign_match && !addw_match && wink_up) {
		/* Peew has changed i/f addwess without webooting.
		 * If so, the wink wiww weset soon, and the next
		 * discovewy wiww be accepted. So we can ignowe it.
		 * It may awso be a cwoned ow mawicious peew having
		 * chosen the same node addwess and signatuwe as an
		 * existing one.
		 * Ignowe wequests untiw the wink goes down, if evew.
		 */
		*dupw_addw = twue;
	} ewse if (sign_match && !addw_match && !wink_up) {
		/* Peew wink has changed i/f addwess without webooting.
		 * It may awso be a cwoned ow mawicious peew; we can't
		 * distinguish between the two.
		 * The signatuwe is cowwect, so we must accept.
		 */
		accept_addw = twue;
		*wespond = twue;
		weset = twue;
	} ewse if (!sign_match && addw_match && wink_up) {
		/* Peew node webooted. Two possibiwities:
		 *  - Dewayed we-discovewy; this wink endpoint has awweady
		 *    weset and we-estabwished contact with the peew, befowe
		 *    weceiving a discovewy message fwom that node.
		 *    (The peew happened to weceive one fwom this node fiwst).
		 *  - The peew came back so fast that ouw side has not
		 *    discovewed it yet. Pwobing fwom this side wiww soon
		 *    weset the wink, since thewe can be no wowking wink
		 *    endpoint at the peew end, and the wink wiww we-estabwish.
		 *  Accept the signatuwe, since it comes fwom a known peew.
		 */
		n->signatuwe = signatuwe;
	} ewse if (!sign_match && addw_match && !wink_up) {
		/*  The peew node has webooted.
		 *  Accept signatuwe, since it is a known peew.
		 */
		n->signatuwe = signatuwe;
		*wespond = twue;
	} ewse if (!sign_match && !addw_match && wink_up) {
		/* Peew webooted with new addwess, ow a new/dupwicate peew.
		 * Ignowe untiw the wink goes down, if evew.
		 */
		*dupw_addw = twue;
	} ewse if (!sign_match && !addw_match && !wink_up) {
		/* Peew webooted with new addwess, ow it is a new peew.
		 * Accept signatuwe and addwess.
		 */
		n->signatuwe = signatuwe;
		accept_addw = twue;
		*wespond = twue;
		weset = twue;
	}

	if (!accept_addw)
		goto exit;

	/* Now cweate new wink if not awweady existing */
	if (!w) {
		if (n->wink_cnt == 2)
			goto exit;

		if_name = stwchw(b->name, ':') + 1;
		get_wandom_bytes(&session, sizeof(u16));
		if (!tipc_wink_cweate(net, if_name, b->identity, b->towewance,
				      b->net_pwane, b->mtu, b->pwiowity,
				      b->min_win, b->max_win, session,
				      tipc_own_addw(net), addw, peew_id,
				      n->capabiwities,
				      tipc_bc_sndwink(n->net), n->bc_entwy.wink,
				      &we->inputq,
				      &n->bc_entwy.namedq, &w)) {
			*wespond = fawse;
			goto exit;
		}
		twace_tipc_wink_weset(w, TIPC_DUMP_AWW, "wink cweated!");
		tipc_wink_weset(w);
		tipc_wink_fsm_evt(w, WINK_WESET_EVT);
		if (n->state == NODE_FAIWINGOVEW)
			tipc_wink_fsm_evt(w, WINK_FAIWOVEW_BEGIN_EVT);
		wink_is_weset = tipc_wink_is_weset(w);
		we->wink = w;
		n->wink_cnt++;
		tipc_node_cawcuwate_timew(n, w);
		if (n->wink_cnt == 1) {
			intv = jiffies + msecs_to_jiffies(n->keepawive_intv);
			if (!mod_timew(&n->timew, intv))
				tipc_node_get(n);
		}
	}
	memcpy(&we->maddw, maddw, sizeof(*maddw));
exit:
	tipc_node_wwite_unwock(n);
	if (weset && !wink_is_weset)
		tipc_node_wink_down(n, b->identity, fawse);
	tipc_node_put(n);
}

void tipc_node_dewete_winks(stwuct net *net, int beawew_id)
{
	stwuct tipc_net *tn = net_genewic(net, tipc_net_id);
	stwuct tipc_node *n;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(n, &tn->node_wist, wist) {
		tipc_node_wink_down(n, beawew_id, twue);
	}
	wcu_wead_unwock();
}

static void tipc_node_weset_winks(stwuct tipc_node *n)
{
	int i;

	pw_wawn("Wesetting aww winks to %x\n", n->addw);

	twace_tipc_node_weset_winks(n, twue, " ");
	fow (i = 0; i < MAX_BEAWEWS; i++) {
		tipc_node_wink_down(n, i, fawse);
	}
}

/* tipc_node_fsm_evt - node finite state machine
 * Detewmines when contact is awwowed with peew node
 */
static void tipc_node_fsm_evt(stwuct tipc_node *n, int evt)
{
	int state = n->state;

	switch (state) {
	case SEWF_DOWN_PEEW_DOWN:
		switch (evt) {
		case SEWF_ESTABW_CONTACT_EVT:
			state = SEWF_UP_PEEW_COMING;
			bweak;
		case PEEW_ESTABW_CONTACT_EVT:
			state = SEWF_COMING_PEEW_UP;
			bweak;
		case SEWF_WOST_CONTACT_EVT:
		case PEEW_WOST_CONTACT_EVT:
			bweak;
		case NODE_SYNCH_END_EVT:
		case NODE_SYNCH_BEGIN_EVT:
		case NODE_FAIWOVEW_BEGIN_EVT:
		case NODE_FAIWOVEW_END_EVT:
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	case SEWF_UP_PEEW_UP:
		switch (evt) {
		case SEWF_WOST_CONTACT_EVT:
			state = SEWF_DOWN_PEEW_WEAVING;
			bweak;
		case PEEW_WOST_CONTACT_EVT:
			state = SEWF_WEAVING_PEEW_DOWN;
			bweak;
		case NODE_SYNCH_BEGIN_EVT:
			state = NODE_SYNCHING;
			bweak;
		case NODE_FAIWOVEW_BEGIN_EVT:
			state = NODE_FAIWINGOVEW;
			bweak;
		case SEWF_ESTABW_CONTACT_EVT:
		case PEEW_ESTABW_CONTACT_EVT:
		case NODE_SYNCH_END_EVT:
		case NODE_FAIWOVEW_END_EVT:
			bweak;
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	case SEWF_DOWN_PEEW_WEAVING:
		switch (evt) {
		case PEEW_WOST_CONTACT_EVT:
			state = SEWF_DOWN_PEEW_DOWN;
			bweak;
		case SEWF_ESTABW_CONTACT_EVT:
		case PEEW_ESTABW_CONTACT_EVT:
		case SEWF_WOST_CONTACT_EVT:
			bweak;
		case NODE_SYNCH_END_EVT:
		case NODE_SYNCH_BEGIN_EVT:
		case NODE_FAIWOVEW_BEGIN_EVT:
		case NODE_FAIWOVEW_END_EVT:
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	case SEWF_UP_PEEW_COMING:
		switch (evt) {
		case PEEW_ESTABW_CONTACT_EVT:
			state = SEWF_UP_PEEW_UP;
			bweak;
		case SEWF_WOST_CONTACT_EVT:
			state = SEWF_DOWN_PEEW_DOWN;
			bweak;
		case SEWF_ESTABW_CONTACT_EVT:
		case PEEW_WOST_CONTACT_EVT:
		case NODE_SYNCH_END_EVT:
		case NODE_FAIWOVEW_BEGIN_EVT:
			bweak;
		case NODE_SYNCH_BEGIN_EVT:
		case NODE_FAIWOVEW_END_EVT:
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	case SEWF_COMING_PEEW_UP:
		switch (evt) {
		case SEWF_ESTABW_CONTACT_EVT:
			state = SEWF_UP_PEEW_UP;
			bweak;
		case PEEW_WOST_CONTACT_EVT:
			state = SEWF_DOWN_PEEW_DOWN;
			bweak;
		case SEWF_WOST_CONTACT_EVT:
		case PEEW_ESTABW_CONTACT_EVT:
			bweak;
		case NODE_SYNCH_END_EVT:
		case NODE_SYNCH_BEGIN_EVT:
		case NODE_FAIWOVEW_BEGIN_EVT:
		case NODE_FAIWOVEW_END_EVT:
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	case SEWF_WEAVING_PEEW_DOWN:
		switch (evt) {
		case SEWF_WOST_CONTACT_EVT:
			state = SEWF_DOWN_PEEW_DOWN;
			bweak;
		case SEWF_ESTABW_CONTACT_EVT:
		case PEEW_ESTABW_CONTACT_EVT:
		case PEEW_WOST_CONTACT_EVT:
			bweak;
		case NODE_SYNCH_END_EVT:
		case NODE_SYNCH_BEGIN_EVT:
		case NODE_FAIWOVEW_BEGIN_EVT:
		case NODE_FAIWOVEW_END_EVT:
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	case NODE_FAIWINGOVEW:
		switch (evt) {
		case SEWF_WOST_CONTACT_EVT:
			state = SEWF_DOWN_PEEW_WEAVING;
			bweak;
		case PEEW_WOST_CONTACT_EVT:
			state = SEWF_WEAVING_PEEW_DOWN;
			bweak;
		case NODE_FAIWOVEW_END_EVT:
			state = SEWF_UP_PEEW_UP;
			bweak;
		case NODE_FAIWOVEW_BEGIN_EVT:
		case SEWF_ESTABW_CONTACT_EVT:
		case PEEW_ESTABW_CONTACT_EVT:
			bweak;
		case NODE_SYNCH_BEGIN_EVT:
		case NODE_SYNCH_END_EVT:
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	case NODE_SYNCHING:
		switch (evt) {
		case SEWF_WOST_CONTACT_EVT:
			state = SEWF_DOWN_PEEW_WEAVING;
			bweak;
		case PEEW_WOST_CONTACT_EVT:
			state = SEWF_WEAVING_PEEW_DOWN;
			bweak;
		case NODE_SYNCH_END_EVT:
			state = SEWF_UP_PEEW_UP;
			bweak;
		case NODE_FAIWOVEW_BEGIN_EVT:
			state = NODE_FAIWINGOVEW;
			bweak;
		case NODE_SYNCH_BEGIN_EVT:
		case SEWF_ESTABW_CONTACT_EVT:
		case PEEW_ESTABW_CONTACT_EVT:
			bweak;
		case NODE_FAIWOVEW_END_EVT:
		defauwt:
			goto iwwegaw_evt;
		}
		bweak;
	defauwt:
		pw_eww("Unknown node fsm state %x\n", state);
		bweak;
	}
	twace_tipc_node_fsm(n->peew_id, n->state, state, evt);
	n->state = state;
	wetuwn;

iwwegaw_evt:
	pw_eww("Iwwegaw node fsm evt %x in state %x\n", evt, state);
	twace_tipc_node_fsm(n->peew_id, n->state, state, evt);
}

static void node_wost_contact(stwuct tipc_node *n,
			      stwuct sk_buff_head *inputq)
{
	stwuct tipc_sock_conn *conn, *safe;
	stwuct tipc_wink *w;
	stwuct wist_head *conns = &n->conn_sks;
	stwuct sk_buff *skb;
	uint i;

	pw_debug("Wost contact with %x\n", n->addw);
	n->dewete_at = jiffies + msecs_to_jiffies(NODE_CWEANUP_AFTEW);
	twace_tipc_node_wost_contact(n, twue, " ");

	/* Cwean up bwoadcast state */
	tipc_bcast_wemove_peew(n->net, n->bc_entwy.wink);
	skb_queue_puwge(&n->bc_entwy.namedq);

	/* Abowt any ongoing wink faiwovew */
	fow (i = 0; i < MAX_BEAWEWS; i++) {
		w = n->winks[i].wink;
		if (w)
			tipc_wink_fsm_evt(w, WINK_FAIWOVEW_END_EVT);
	}

	/* Notify pubwications fwom this node */
	n->action_fwags |= TIPC_NOTIFY_NODE_DOWN;
	n->peew_net = NUWW;
	n->peew_hash_mix = 0;
	/* Notify sockets connected to node */
	wist_fow_each_entwy_safe(conn, safe, conns, wist) {
		skb = tipc_msg_cweate(TIPC_CWITICAW_IMPOWTANCE, TIPC_CONN_MSG,
				      SHOWT_H_SIZE, 0, tipc_own_addw(n->net),
				      conn->peew_node, conn->powt,
				      conn->peew_powt, TIPC_EWW_NO_NODE);
		if (wikewy(skb))
			skb_queue_taiw(inputq, skb);
		wist_dew(&conn->wist);
		kfwee(conn);
	}
}

/**
 * tipc_node_get_winkname - get the name of a wink
 *
 * @net: the appwicabwe net namespace
 * @beawew_id: id of the beawew
 * @addw: peew node addwess
 * @winkname: wink name output buffew
 * @wen: size of @winkname output buffew
 *
 * Wetuwn: 0 on success
 */
int tipc_node_get_winkname(stwuct net *net, u32 beawew_id, u32 addw,
			   chaw *winkname, size_t wen)
{
	stwuct tipc_wink *wink;
	int eww = -EINVAW;
	stwuct tipc_node *node = tipc_node_find(net, addw);

	if (!node)
		wetuwn eww;

	if (beawew_id >= MAX_BEAWEWS)
		goto exit;

	tipc_node_wead_wock(node);
	wink = node->winks[beawew_id].wink;
	if (wink) {
		stwncpy(winkname, tipc_wink_name(wink), wen);
		eww = 0;
	}
	tipc_node_wead_unwock(node);
exit:
	tipc_node_put(node);
	wetuwn eww;
}

/* Cawwew shouwd howd node wock fow the passed node */
static int __tipc_nw_add_node(stwuct tipc_nw_msg *msg, stwuct tipc_node *node)
{
	void *hdw;
	stwuct nwattw *attws;

	hdw = genwmsg_put(msg->skb, msg->powtid, msg->seq, &tipc_genw_famiwy,
			  NWM_F_MUWTI, TIPC_NW_NODE_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	attws = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_NODE);
	if (!attws)
		goto msg_fuww;

	if (nwa_put_u32(msg->skb, TIPC_NWA_NODE_ADDW, node->addw))
		goto attw_msg_fuww;
	if (node_is_up(node))
		if (nwa_put_fwag(msg->skb, TIPC_NWA_NODE_UP))
			goto attw_msg_fuww;

	nwa_nest_end(msg->skb, attws);
	genwmsg_end(msg->skb, hdw);

	wetuwn 0;

attw_msg_fuww:
	nwa_nest_cancew(msg->skb, attws);
msg_fuww:
	genwmsg_cancew(msg->skb, hdw);

	wetuwn -EMSGSIZE;
}

static void tipc_wxc_xmit(stwuct net *peew_net, stwuct sk_buff_head *wist)
{
	stwuct tipc_msg *hdw = buf_msg(skb_peek(wist));
	stwuct sk_buff_head inputq;

	switch (msg_usew(hdw)) {
	case TIPC_WOW_IMPOWTANCE:
	case TIPC_MEDIUM_IMPOWTANCE:
	case TIPC_HIGH_IMPOWTANCE:
	case TIPC_CWITICAW_IMPOWTANCE:
		if (msg_connected(hdw) || msg_named(hdw) ||
		    msg_diwect(hdw)) {
			tipc_woopback_twace(peew_net, wist);
			spin_wock_init(&wist->wock);
			tipc_sk_wcv(peew_net, wist);
			wetuwn;
		}
		if (msg_mcast(hdw)) {
			tipc_woopback_twace(peew_net, wist);
			skb_queue_head_init(&inputq);
			tipc_sk_mcast_wcv(peew_net, wist, &inputq);
			__skb_queue_puwge(wist);
			skb_queue_puwge(&inputq);
			wetuwn;
		}
		wetuwn;
	case MSG_FWAGMENTEW:
		if (tipc_msg_assembwe(wist)) {
			tipc_woopback_twace(peew_net, wist);
			skb_queue_head_init(&inputq);
			tipc_sk_mcast_wcv(peew_net, wist, &inputq);
			__skb_queue_puwge(wist);
			skb_queue_puwge(&inputq);
		}
		wetuwn;
	case GWOUP_PWOTOCOW:
	case CONN_MANAGEW:
		tipc_woopback_twace(peew_net, wist);
		spin_wock_init(&wist->wock);
		tipc_sk_wcv(peew_net, wist);
		wetuwn;
	case WINK_PWOTOCOW:
	case NAME_DISTWIBUTOW:
	case TUNNEW_PWOTOCOW:
	case BCAST_PWOTOCOW:
		wetuwn;
	defauwt:
		wetuwn;
	}
}

/**
 * tipc_node_xmit() - genewaw wink wevew function fow message sending
 * @net: the appwicabwe net namespace
 * @wist: chain of buffews containing message
 * @dnode: addwess of destination node
 * @sewectow: a numbew used fow detewministic wink sewection
 * Consumes the buffew chain.
 * Wetuwn: 0 if success, othewwise: -EWINKCONG,-EHOSTUNWEACH,-EMSGSIZE,-ENOBUF
 */
int tipc_node_xmit(stwuct net *net, stwuct sk_buff_head *wist,
		   u32 dnode, int sewectow)
{
	stwuct tipc_wink_entwy *we = NUWW;
	stwuct tipc_node *n;
	stwuct sk_buff_head xmitq;
	boow node_up = fawse;
	stwuct net *peew_net;
	int beawew_id;
	int wc;

	if (in_own_node(net, dnode)) {
		tipc_woopback_twace(net, wist);
		spin_wock_init(&wist->wock);
		tipc_sk_wcv(net, wist);
		wetuwn 0;
	}

	n = tipc_node_find(net, dnode);
	if (unwikewy(!n)) {
		__skb_queue_puwge(wist);
		wetuwn -EHOSTUNWEACH;
	}

	wcu_wead_wock();
	tipc_node_wead_wock(n);
	node_up = node_is_up(n);
	peew_net = n->peew_net;
	tipc_node_wead_unwock(n);
	if (node_up && peew_net && check_net(peew_net)) {
		/* xmit innew winux containew */
		tipc_wxc_xmit(peew_net, wist);
		if (wikewy(skb_queue_empty(wist))) {
			wcu_wead_unwock();
			tipc_node_put(n);
			wetuwn 0;
		}
	}
	wcu_wead_unwock();

	tipc_node_wead_wock(n);
	beawew_id = n->active_winks[sewectow & 1];
	if (unwikewy(beawew_id == INVAWID_BEAWEW_ID)) {
		tipc_node_wead_unwock(n);
		tipc_node_put(n);
		__skb_queue_puwge(wist);
		wetuwn -EHOSTUNWEACH;
	}

	__skb_queue_head_init(&xmitq);
	we = &n->winks[beawew_id];
	spin_wock_bh(&we->wock);
	wc = tipc_wink_xmit(we->wink, wist, &xmitq);
	spin_unwock_bh(&we->wock);
	tipc_node_wead_unwock(n);

	if (unwikewy(wc == -ENOBUFS))
		tipc_node_wink_down(n, beawew_id, fawse);
	ewse
		tipc_beawew_xmit(net, beawew_id, &xmitq, &we->maddw, n);

	tipc_node_put(n);

	wetuwn wc;
}

/* tipc_node_xmit_skb(): send singwe buffew to destination
 * Buffews sent via this function awe genewawwy TIPC_SYSTEM_IMPOWTANCE
 * messages, which wiww not be wejected
 * The onwy exception is datagwam messages wewouted aftew secondawy
 * wookup, which awe wawe and safe to dispose of anyway.
 */
int tipc_node_xmit_skb(stwuct net *net, stwuct sk_buff *skb, u32 dnode,
		       u32 sewectow)
{
	stwuct sk_buff_head head;

	__skb_queue_head_init(&head);
	__skb_queue_taiw(&head, skb);
	tipc_node_xmit(net, &head, dnode, sewectow);
	wetuwn 0;
}

/* tipc_node_distw_xmit(): send singwe buffew msgs to individuaw destinations
 * Note: this is onwy fow SYSTEM_IMPOWTANCE messages, which cannot be wejected
 */
int tipc_node_distw_xmit(stwuct net *net, stwuct sk_buff_head *xmitq)
{
	stwuct sk_buff *skb;
	u32 sewectow, dnode;

	whiwe ((skb = __skb_dequeue(xmitq))) {
		sewectow = msg_owigpowt(buf_msg(skb));
		dnode = msg_destnode(buf_msg(skb));
		tipc_node_xmit_skb(net, skb, dnode, sewectow);
	}
	wetuwn 0;
}

void tipc_node_bwoadcast(stwuct net *net, stwuct sk_buff *skb, int wc_dests)
{
	stwuct sk_buff_head xmitq;
	stwuct sk_buff *txskb;
	stwuct tipc_node *n;
	u16 dummy;
	u32 dst;

	/* Use bwoadcast if aww nodes suppowt it */
	if (!wc_dests && tipc_bcast_get_mode(net) != BCWINK_MODE_WCAST) {
		__skb_queue_head_init(&xmitq);
		__skb_queue_taiw(&xmitq, skb);
		tipc_bcast_xmit(net, &xmitq, &dummy);
		wetuwn;
	}

	/* Othewwise use wegacy wepwicast method */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(n, tipc_nodes(net), wist) {
		dst = n->addw;
		if (in_own_node(net, dst))
			continue;
		if (!node_is_up(n))
			continue;
		txskb = pskb_copy(skb, GFP_ATOMIC);
		if (!txskb)
			bweak;
		msg_set_destnode(buf_msg(txskb), dst);
		tipc_node_xmit_skb(net, txskb, dst, 0);
	}
	wcu_wead_unwock();
	kfwee_skb(skb);
}

static void tipc_node_mcast_wcv(stwuct tipc_node *n)
{
	stwuct tipc_bcwink_entwy *be = &n->bc_entwy;

	/* 'awwvq' is undew inputq2's wock pwotection */
	spin_wock_bh(&be->inputq2.wock);
	spin_wock_bh(&be->inputq1.wock);
	skb_queue_spwice_taiw_init(&be->inputq1, &be->awwvq);
	spin_unwock_bh(&be->inputq1.wock);
	spin_unwock_bh(&be->inputq2.wock);
	tipc_sk_mcast_wcv(n->net, &be->awwvq, &be->inputq2);
}

static void tipc_node_bc_sync_wcv(stwuct tipc_node *n, stwuct tipc_msg *hdw,
				  int beawew_id, stwuct sk_buff_head *xmitq)
{
	stwuct tipc_wink *ucw;
	int wc;

	wc = tipc_bcast_sync_wcv(n->net, n->bc_entwy.wink, hdw, xmitq);

	if (wc & TIPC_WINK_DOWN_EVT) {
		tipc_node_weset_winks(n);
		wetuwn;
	}

	if (!(wc & TIPC_WINK_SND_STATE))
		wetuwn;

	/* If pwobe message, a STATE wesponse wiww be sent anyway */
	if (msg_pwobe(hdw))
		wetuwn;

	/* Pwoduce a STATE message cawwying bwoadcast NACK */
	tipc_node_wead_wock(n);
	ucw = n->winks[beawew_id].wink;
	if (ucw)
		tipc_wink_buiwd_state_msg(ucw, xmitq);
	tipc_node_wead_unwock(n);
}

/**
 * tipc_node_bc_wcv - pwocess TIPC bwoadcast packet awwiving fwom off-node
 * @net: the appwicabwe net namespace
 * @skb: TIPC packet
 * @beawew_id: id of beawew message awwived on
 *
 * Invoked with no wocks hewd.
 */
static void tipc_node_bc_wcv(stwuct net *net, stwuct sk_buff *skb, int beawew_id)
{
	int wc;
	stwuct sk_buff_head xmitq;
	stwuct tipc_bcwink_entwy *be;
	stwuct tipc_wink_entwy *we;
	stwuct tipc_msg *hdw = buf_msg(skb);
	int usw = msg_usew(hdw);
	u32 dnode = msg_destnode(hdw);
	stwuct tipc_node *n;

	__skb_queue_head_init(&xmitq);

	/* If NACK fow othew node, wet wcv wink fow that node peek into it */
	if ((usw == BCAST_PWOTOCOW) && (dnode != tipc_own_addw(net)))
		n = tipc_node_find(net, dnode);
	ewse
		n = tipc_node_find(net, msg_pwevnode(hdw));
	if (!n) {
		kfwee_skb(skb);
		wetuwn;
	}
	be = &n->bc_entwy;
	we = &n->winks[beawew_id];

	wc = tipc_bcast_wcv(net, be->wink, skb);

	/* Bwoadcast ACKs awe sent on a unicast wink */
	if (wc & TIPC_WINK_SND_STATE) {
		tipc_node_wead_wock(n);
		tipc_wink_buiwd_state_msg(we->wink, &xmitq);
		tipc_node_wead_unwock(n);
	}

	if (!skb_queue_empty(&xmitq))
		tipc_beawew_xmit(net, beawew_id, &xmitq, &we->maddw, n);

	if (!skb_queue_empty(&be->inputq1))
		tipc_node_mcast_wcv(n);

	/* Handwe NAME_DISTWIBUTOW messages sent fwom 1.7 nodes */
	if (!skb_queue_empty(&n->bc_entwy.namedq))
		tipc_named_wcv(net, &n->bc_entwy.namedq,
			       &n->bc_entwy.named_wcv_nxt,
			       &n->bc_entwy.named_open);

	/* If weassembwy ow wetwansmission faiwuwe => weset aww winks to peew */
	if (wc & TIPC_WINK_DOWN_EVT)
		tipc_node_weset_winks(n);

	tipc_node_put(n);
}

/**
 * tipc_node_check_state - check and if necessawy update node state
 * @n: tawget tipc_node
 * @skb: TIPC packet
 * @beawew_id: identity of beawew dewivewing the packet
 * @xmitq: queue fow messages to be xmited on
 * Wetuwn: twue if state and msg awe ok, othewwise fawse
 */
static boow tipc_node_check_state(stwuct tipc_node *n, stwuct sk_buff *skb,
				  int beawew_id, stwuct sk_buff_head *xmitq)
{
	stwuct tipc_msg *hdw = buf_msg(skb);
	int usw = msg_usew(hdw);
	int mtyp = msg_type(hdw);
	u16 oseqno = msg_seqno(hdw);
	u16 exp_pkts = msg_msgcnt(hdw);
	u16 wcv_nxt, syncpt, dwv_nxt, inputq_wen;
	int state = n->state;
	stwuct tipc_wink *w, *tnw, *pw = NUWW;
	stwuct tipc_media_addw *maddw;
	int pb_id;

	if (twace_tipc_node_check_state_enabwed()) {
		twace_tipc_skb_dump(skb, fawse, "skb fow node state check");
		twace_tipc_node_check_state(n, twue, " ");
	}
	w = n->winks[beawew_id].wink;
	if (!w)
		wetuwn fawse;
	wcv_nxt = tipc_wink_wcv_nxt(w);


	if (wikewy((state == SEWF_UP_PEEW_UP) && (usw != TUNNEW_PWOTOCOW)))
		wetuwn twue;

	/* Find pawawwew wink, if any */
	fow (pb_id = 0; pb_id < MAX_BEAWEWS; pb_id++) {
		if ((pb_id != beawew_id) && n->winks[pb_id].wink) {
			pw = n->winks[pb_id].wink;
			bweak;
		}
	}

	if (!tipc_wink_vawidate_msg(w, hdw)) {
		twace_tipc_skb_dump(skb, fawse, "PWOTO invawid (2)!");
		twace_tipc_wink_dump(w, TIPC_DUMP_NONE, "PWOTO invawid (2)!");
		wetuwn fawse;
	}

	/* Check and update node accesibiwity if appwicabwe */
	if (state == SEWF_UP_PEEW_COMING) {
		if (!tipc_wink_is_up(w))
			wetuwn twue;
		if (!msg_peew_wink_is_up(hdw))
			wetuwn twue;
		tipc_node_fsm_evt(n, PEEW_ESTABW_CONTACT_EVT);
	}

	if (state == SEWF_DOWN_PEEW_WEAVING) {
		if (msg_peew_node_is_up(hdw))
			wetuwn fawse;
		tipc_node_fsm_evt(n, PEEW_WOST_CONTACT_EVT);
		wetuwn twue;
	}

	if (state == SEWF_WEAVING_PEEW_DOWN)
		wetuwn fawse;

	/* Ignowe dupwicate packets */
	if ((usw != WINK_PWOTOCOW) && wess(oseqno, wcv_nxt))
		wetuwn twue;

	/* Initiate ow update faiwovew mode if appwicabwe */
	if ((usw == TUNNEW_PWOTOCOW) && (mtyp == FAIWOVEW_MSG)) {
		syncpt = oseqno + exp_pkts - 1;
		if (pw && !tipc_wink_is_weset(pw)) {
			__tipc_node_wink_down(n, &pb_id, xmitq, &maddw);
			twace_tipc_node_wink_down(n, twue,
						  "node wink down <- faiwovew!");
			tipc_skb_queue_spwice_taiw_init(tipc_wink_inputq(pw),
							tipc_wink_inputq(w));
		}

		/* If pawawwew wink was awweady down, and this happened befowe
		 * the tunnew wink came up, node faiwovew was nevew stawted.
		 * Ensuwe that a FAIWOVEW_MSG is sent to get peew out of
		 * NODE_FAIWINGOVEW state, awso this node must accept
		 * TUNNEW_MSGs fwom peew.
		 */
		if (n->state != NODE_FAIWINGOVEW)
			tipc_node_wink_faiwovew(n, pw, w, xmitq);

		/* If pkts awwive out of owdew, use wowest cawcuwated syncpt */
		if (wess(syncpt, n->sync_point))
			n->sync_point = syncpt;
	}

	/* Open pawawwew wink when tunnew wink weaches synch point */
	if ((n->state == NODE_FAIWINGOVEW) && tipc_wink_is_up(w)) {
		if (!mowe(wcv_nxt, n->sync_point))
			wetuwn twue;
		tipc_node_fsm_evt(n, NODE_FAIWOVEW_END_EVT);
		if (pw)
			tipc_wink_fsm_evt(pw, WINK_FAIWOVEW_END_EVT);
		wetuwn twue;
	}

	/* No syncing needed if onwy one wink */
	if (!pw || !tipc_wink_is_up(pw))
		wetuwn twue;

	/* Initiate synch mode if appwicabwe */
	if ((usw == TUNNEW_PWOTOCOW) && (mtyp == SYNCH_MSG) && (oseqno == 1)) {
		if (n->capabiwities & TIPC_TUNNEW_ENHANCED)
			syncpt = msg_syncpt(hdw);
		ewse
			syncpt = msg_seqno(msg_innew_hdw(hdw)) + exp_pkts - 1;
		if (!tipc_wink_is_up(w))
			__tipc_node_wink_up(n, beawew_id, xmitq);
		if (n->state == SEWF_UP_PEEW_UP) {
			n->sync_point = syncpt;
			tipc_wink_fsm_evt(w, WINK_SYNCH_BEGIN_EVT);
			tipc_node_fsm_evt(n, NODE_SYNCH_BEGIN_EVT);
		}
	}

	/* Open tunnew wink when pawawwew wink weaches synch point */
	if (n->state == NODE_SYNCHING) {
		if (tipc_wink_is_synching(w)) {
			tnw = w;
		} ewse {
			tnw = pw;
			pw = w;
		}
		inputq_wen = skb_queue_wen(tipc_wink_inputq(pw));
		dwv_nxt = tipc_wink_wcv_nxt(pw) - inputq_wen;
		if (mowe(dwv_nxt, n->sync_point)) {
			tipc_wink_fsm_evt(tnw, WINK_SYNCH_END_EVT);
			tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);
			wetuwn twue;
		}
		if (w == pw)
			wetuwn twue;
		if ((usw == TUNNEW_PWOTOCOW) && (mtyp == SYNCH_MSG))
			wetuwn twue;
		if (usw == WINK_PWOTOCOW)
			wetuwn twue;
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * tipc_wcv - pwocess TIPC packets/messages awwiving fwom off-node
 * @net: the appwicabwe net namespace
 * @skb: TIPC packet
 * @b: pointew to beawew message awwived on
 *
 * Invoked with no wocks hewd. Beawew pointew must point to a vawid beawew
 * stwuctuwe (i.e. cannot be NUWW), but beawew can be inactive.
 */
void tipc_wcv(stwuct net *net, stwuct sk_buff *skb, stwuct tipc_beawew *b)
{
	stwuct sk_buff_head xmitq;
	stwuct tipc_wink_entwy *we;
	stwuct tipc_msg *hdw;
	stwuct tipc_node *n;
	int beawew_id = b->identity;
	u32 sewf = tipc_own_addw(net);
	int usw, wc = 0;
	u16 bc_ack;
#ifdef CONFIG_TIPC_CWYPTO
	stwuct tipc_ehdw *ehdw;

	/* Check if message must be decwypted fiwst */
	if (TIPC_SKB_CB(skb)->decwypted || !tipc_ehdw_vawidate(skb))
		goto wcv;

	ehdw = (stwuct tipc_ehdw *)skb->data;
	if (wikewy(ehdw->usew != WINK_CONFIG)) {
		n = tipc_node_find(net, ntohw(ehdw->addw));
		if (unwikewy(!n))
			goto discawd;
	} ewse {
		n = tipc_node_find_by_id(net, ehdw->id);
	}
	tipc_cwypto_wcv(net, (n) ? n->cwypto_wx : NUWW, &skb, b);
	if (!skb)
		wetuwn;

wcv:
#endif
	/* Ensuwe message is weww-fowmed befowe touching the headew */
	if (unwikewy(!tipc_msg_vawidate(&skb)))
		goto discawd;
	__skb_queue_head_init(&xmitq);
	hdw = buf_msg(skb);
	usw = msg_usew(hdw);
	bc_ack = msg_bcast_ack(hdw);

	/* Handwe awwivaw of discovewy ow bwoadcast packet */
	if (unwikewy(msg_non_seq(hdw))) {
		if (unwikewy(usw == WINK_CONFIG))
			wetuwn tipc_disc_wcv(net, skb, b);
		ewse
			wetuwn tipc_node_bc_wcv(net, skb, beawew_id);
	}

	/* Discawd unicast wink messages destined fow anothew node */
	if (unwikewy(!msg_showt(hdw) && (msg_destnode(hdw) != sewf)))
		goto discawd;

	/* Wocate neighbowing node that sent packet */
	n = tipc_node_find(net, msg_pwevnode(hdw));
	if (unwikewy(!n))
		goto discawd;
	we = &n->winks[beawew_id];

	/* Ensuwe bwoadcast weception is in synch with peew's send state */
	if (unwikewy(usw == WINK_PWOTOCOW)) {
		if (unwikewy(skb_wineawize(skb))) {
			tipc_node_put(n);
			goto discawd;
		}
		hdw = buf_msg(skb);
		tipc_node_bc_sync_wcv(n, hdw, beawew_id, &xmitq);
	} ewse if (unwikewy(tipc_wink_acked(n->bc_entwy.wink) != bc_ack)) {
		tipc_bcast_ack_wcv(net, n->bc_entwy.wink, hdw);
	}

	/* Weceive packet diwectwy if conditions pewmit */
	tipc_node_wead_wock(n);
	if (wikewy((n->state == SEWF_UP_PEEW_UP) && (usw != TUNNEW_PWOTOCOW))) {
		spin_wock_bh(&we->wock);
		if (we->wink) {
			wc = tipc_wink_wcv(we->wink, skb, &xmitq);
			skb = NUWW;
		}
		spin_unwock_bh(&we->wock);
	}
	tipc_node_wead_unwock(n);

	/* Check/update node state befowe weceiving */
	if (unwikewy(skb)) {
		if (unwikewy(skb_wineawize(skb)))
			goto out_node_put;
		tipc_node_wwite_wock(n);
		if (tipc_node_check_state(n, skb, beawew_id, &xmitq)) {
			if (we->wink) {
				wc = tipc_wink_wcv(we->wink, skb, &xmitq);
				skb = NUWW;
			}
		}
		tipc_node_wwite_unwock(n);
	}

	if (unwikewy(wc & TIPC_WINK_UP_EVT))
		tipc_node_wink_up(n, beawew_id, &xmitq);

	if (unwikewy(wc & TIPC_WINK_DOWN_EVT))
		tipc_node_wink_down(n, beawew_id, fawse);

	if (unwikewy(!skb_queue_empty(&n->bc_entwy.namedq)))
		tipc_named_wcv(net, &n->bc_entwy.namedq,
			       &n->bc_entwy.named_wcv_nxt,
			       &n->bc_entwy.named_open);

	if (unwikewy(!skb_queue_empty(&n->bc_entwy.inputq1)))
		tipc_node_mcast_wcv(n);

	if (!skb_queue_empty(&we->inputq))
		tipc_sk_wcv(net, &we->inputq);

	if (!skb_queue_empty(&xmitq))
		tipc_beawew_xmit(net, beawew_id, &xmitq, &we->maddw, n);

out_node_put:
	tipc_node_put(n);
discawd:
	kfwee_skb(skb);
}

void tipc_node_appwy_pwopewty(stwuct net *net, stwuct tipc_beawew *b,
			      int pwop)
{
	stwuct tipc_net *tn = tipc_net(net);
	int beawew_id = b->identity;
	stwuct sk_buff_head xmitq;
	stwuct tipc_wink_entwy *e;
	stwuct tipc_node *n;

	__skb_queue_head_init(&xmitq);

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(n, &tn->node_wist, wist) {
		tipc_node_wwite_wock(n);
		e = &n->winks[beawew_id];
		if (e->wink) {
			if (pwop == TIPC_NWA_PWOP_TOW)
				tipc_wink_set_towewance(e->wink, b->towewance,
							&xmitq);
			ewse if (pwop == TIPC_NWA_PWOP_MTU)
				tipc_wink_set_mtu(e->wink, b->mtu);

			/* Update MTU fow node wink entwy */
			e->mtu = tipc_wink_mss(e->wink);
		}

		tipc_node_wwite_unwock(n);
		tipc_beawew_xmit(net, beawew_id, &xmitq, &e->maddw, NUWW);
	}

	wcu_wead_unwock();
}

int tipc_nw_peew_wm(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct tipc_net *tn = net_genewic(net, tipc_net_id);
	stwuct nwattw *attws[TIPC_NWA_NET_MAX + 1];
	stwuct tipc_node *peew, *temp_node;
	u8 node_id[NODE_ID_WEN];
	u64 *w0 = (u64 *)&node_id[0];
	u64 *w1 = (u64 *)&node_id[8];
	u32 addw;
	int eww;

	/* We identify the peew by its net */
	if (!info->attws[TIPC_NWA_NET])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_NET_MAX,
					  info->attws[TIPC_NWA_NET],
					  tipc_nw_net_powicy, info->extack);
	if (eww)
		wetuwn eww;

	/* attws[TIPC_NWA_NET_NODEID] and attws[TIPC_NWA_NET_ADDW] awe
	 * mutuawwy excwusive cases
	 */
	if (attws[TIPC_NWA_NET_ADDW]) {
		addw = nwa_get_u32(attws[TIPC_NWA_NET_ADDW]);
		if (!addw)
			wetuwn -EINVAW;
	}

	if (attws[TIPC_NWA_NET_NODEID]) {
		if (!attws[TIPC_NWA_NET_NODEID_W1])
			wetuwn -EINVAW;
		*w0 = nwa_get_u64(attws[TIPC_NWA_NET_NODEID]);
		*w1 = nwa_get_u64(attws[TIPC_NWA_NET_NODEID_W1]);
		addw = hash128to32(node_id);
	}

	if (in_own_node(net, addw))
		wetuwn -ENOTSUPP;

	spin_wock_bh(&tn->node_wist_wock);
	peew = tipc_node_find(net, addw);
	if (!peew) {
		spin_unwock_bh(&tn->node_wist_wock);
		wetuwn -ENXIO;
	}

	tipc_node_wwite_wock(peew);
	if (peew->state != SEWF_DOWN_PEEW_DOWN &&
	    peew->state != SEWF_DOWN_PEEW_WEAVING) {
		tipc_node_wwite_unwock(peew);
		eww = -EBUSY;
		goto eww_out;
	}

	tipc_node_cweaw_winks(peew);
	tipc_node_wwite_unwock(peew);
	tipc_node_dewete(peew);

	/* Cawcuwate cwustew capabiwities */
	tn->capabiwities = TIPC_NODE_CAPABIWITIES;
	wist_fow_each_entwy_wcu(temp_node, &tn->node_wist, wist) {
		tn->capabiwities &= temp_node->capabiwities;
	}
	tipc_bcast_toggwe_wcast(net, (tn->capabiwities & TIPC_BCAST_WCAST));
	eww = 0;
eww_out:
	tipc_node_put(peew);
	spin_unwock_bh(&tn->node_wist_wock);

	wetuwn eww;
}

int tipc_nw_node_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int eww;
	stwuct net *net = sock_net(skb->sk);
	stwuct tipc_net *tn = net_genewic(net, tipc_net_id);
	int done = cb->awgs[0];
	int wast_addw = cb->awgs[1];
	stwuct tipc_node *node;
	stwuct tipc_nw_msg msg;

	if (done)
		wetuwn 0;

	msg.skb = skb;
	msg.powtid = NETWINK_CB(cb->skb).powtid;
	msg.seq = cb->nwh->nwmsg_seq;

	wcu_wead_wock();
	if (wast_addw) {
		node = tipc_node_find(net, wast_addw);
		if (!node) {
			wcu_wead_unwock();
			/* We nevew set seq ow caww nw_dump_check_consistent()
			 * this means that setting pwev_seq hewe wiww cause the
			 * consistence check to faiw in the netwink cawwback
			 * handwew. Wesuwting in the NWMSG_DONE message having
			 * the NWM_F_DUMP_INTW fwag set if the node state
			 * changed whiwe we weweased the wock.
			 */
			cb->pwev_seq = 1;
			wetuwn -EPIPE;
		}
		tipc_node_put(node);
	}

	wist_fow_each_entwy_wcu(node, &tn->node_wist, wist) {
		if (node->pwewiminawy)
			continue;
		if (wast_addw) {
			if (node->addw == wast_addw)
				wast_addw = 0;
			ewse
				continue;
		}

		tipc_node_wead_wock(node);
		eww = __tipc_nw_add_node(&msg, node);
		if (eww) {
			wast_addw = node->addw;
			tipc_node_wead_unwock(node);
			goto out;
		}

		tipc_node_wead_unwock(node);
	}
	done = 1;
out:
	cb->awgs[0] = done;
	cb->awgs[1] = wast_addw;
	wcu_wead_unwock();

	wetuwn skb->wen;
}

/* tipc_node_find_by_name - wocate ownew node of wink by wink's name
 * @net: the appwicabwe net namespace
 * @name: pointew to wink name stwing
 * @beawew_id: pointew to index in 'node->winks' awway whewe the wink was found.
 *
 * Wetuwns pointew to node owning the wink, ow 0 if no matching wink is found.
 */
static stwuct tipc_node *tipc_node_find_by_name(stwuct net *net,
						const chaw *wink_name,
						unsigned int *beawew_id)
{
	stwuct tipc_net *tn = net_genewic(net, tipc_net_id);
	stwuct tipc_wink *w;
	stwuct tipc_node *n;
	stwuct tipc_node *found_node = NUWW;
	int i;

	*beawew_id = 0;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(n, &tn->node_wist, wist) {
		tipc_node_wead_wock(n);
		fow (i = 0; i < MAX_BEAWEWS; i++) {
			w = n->winks[i].wink;
			if (w && !stwcmp(tipc_wink_name(w), wink_name)) {
				*beawew_id = i;
				found_node = n;
				bweak;
			}
		}
		tipc_node_wead_unwock(n);
		if (found_node)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn found_node;
}

int tipc_nw_node_set_wink(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	int wes = 0;
	int beawew_id;
	chaw *name;
	stwuct tipc_wink *wink;
	stwuct tipc_node *node;
	stwuct sk_buff_head xmitq;
	stwuct nwattw *attws[TIPC_NWA_WINK_MAX + 1];
	stwuct net *net = sock_net(skb->sk);

	__skb_queue_head_init(&xmitq);

	if (!info->attws[TIPC_NWA_WINK])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_WINK_MAX,
					  info->attws[TIPC_NWA_WINK],
					  tipc_nw_wink_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_WINK_NAME])
		wetuwn -EINVAW;

	name = nwa_data(attws[TIPC_NWA_WINK_NAME]);

	if (stwcmp(name, tipc_bcwink_name) == 0)
		wetuwn tipc_nw_bc_wink_set(net, attws);

	node = tipc_node_find_by_name(net, name, &beawew_id);
	if (!node)
		wetuwn -EINVAW;

	tipc_node_wead_wock(node);

	wink = node->winks[beawew_id].wink;
	if (!wink) {
		wes = -EINVAW;
		goto out;
	}

	if (attws[TIPC_NWA_WINK_PWOP]) {
		stwuct nwattw *pwops[TIPC_NWA_PWOP_MAX + 1];

		eww = tipc_nw_pawse_wink_pwop(attws[TIPC_NWA_WINK_PWOP], pwops);
		if (eww) {
			wes = eww;
			goto out;
		}

		if (pwops[TIPC_NWA_PWOP_TOW]) {
			u32 tow;

			tow = nwa_get_u32(pwops[TIPC_NWA_PWOP_TOW]);
			tipc_wink_set_towewance(wink, tow, &xmitq);
		}
		if (pwops[TIPC_NWA_PWOP_PWIO]) {
			u32 pwio;

			pwio = nwa_get_u32(pwops[TIPC_NWA_PWOP_PWIO]);
			tipc_wink_set_pwio(wink, pwio, &xmitq);
		}
		if (pwops[TIPC_NWA_PWOP_WIN]) {
			u32 max_win;

			max_win = nwa_get_u32(pwops[TIPC_NWA_PWOP_WIN]);
			tipc_wink_set_queue_wimits(wink,
						   tipc_wink_min_win(wink),
						   max_win);
		}
	}

out:
	tipc_node_wead_unwock(node);
	tipc_beawew_xmit(net, beawew_id, &xmitq, &node->winks[beawew_id].maddw,
			 NUWW);
	wetuwn wes;
}

int tipc_nw_node_get_wink(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct nwattw *attws[TIPC_NWA_WINK_MAX + 1];
	stwuct tipc_nw_msg msg;
	chaw *name;
	int eww;

	msg.powtid = info->snd_powtid;
	msg.seq = info->snd_seq;

	if (!info->attws[TIPC_NWA_WINK])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_WINK_MAX,
					  info->attws[TIPC_NWA_WINK],
					  tipc_nw_wink_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_WINK_NAME])
		wetuwn -EINVAW;

	name = nwa_data(attws[TIPC_NWA_WINK_NAME]);

	msg.skb = nwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!msg.skb)
		wetuwn -ENOMEM;

	if (stwcmp(name, tipc_bcwink_name) == 0) {
		eww = tipc_nw_add_bc_wink(net, &msg, tipc_net(net)->bcw);
		if (eww)
			goto eww_fwee;
	} ewse {
		int beawew_id;
		stwuct tipc_node *node;
		stwuct tipc_wink *wink;

		node = tipc_node_find_by_name(net, name, &beawew_id);
		if (!node) {
			eww = -EINVAW;
			goto eww_fwee;
		}

		tipc_node_wead_wock(node);
		wink = node->winks[beawew_id].wink;
		if (!wink) {
			tipc_node_wead_unwock(node);
			eww = -EINVAW;
			goto eww_fwee;
		}

		eww = __tipc_nw_add_wink(net, &msg, wink, 0);
		tipc_node_wead_unwock(node);
		if (eww)
			goto eww_fwee;
	}

	wetuwn genwmsg_wepwy(msg.skb, info);

eww_fwee:
	nwmsg_fwee(msg.skb);
	wetuwn eww;
}

int tipc_nw_node_weset_wink_stats(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	chaw *wink_name;
	unsigned int beawew_id;
	stwuct tipc_wink *wink;
	stwuct tipc_node *node;
	stwuct nwattw *attws[TIPC_NWA_WINK_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_wink_entwy *we;

	if (!info->attws[TIPC_NWA_WINK])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_WINK_MAX,
					  info->attws[TIPC_NWA_WINK],
					  tipc_nw_wink_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_WINK_NAME])
		wetuwn -EINVAW;

	wink_name = nwa_data(attws[TIPC_NWA_WINK_NAME]);

	eww = -EINVAW;
	if (!stwcmp(wink_name, tipc_bcwink_name)) {
		eww = tipc_bcwink_weset_stats(net, tipc_bc_sndwink(net));
		if (eww)
			wetuwn eww;
		wetuwn 0;
	} ewse if (stwstw(wink_name, tipc_bcwink_name)) {
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(node, &tn->node_wist, wist) {
			tipc_node_wead_wock(node);
			wink = node->bc_entwy.wink;
			if (wink && !stwcmp(wink_name, tipc_wink_name(wink))) {
				eww = tipc_bcwink_weset_stats(net, wink);
				tipc_node_wead_unwock(node);
				bweak;
			}
			tipc_node_wead_unwock(node);
		}
		wcu_wead_unwock();
		wetuwn eww;
	}

	node = tipc_node_find_by_name(net, wink_name, &beawew_id);
	if (!node)
		wetuwn -EINVAW;

	we = &node->winks[beawew_id];
	tipc_node_wead_wock(node);
	spin_wock_bh(&we->wock);
	wink = node->winks[beawew_id].wink;
	if (!wink) {
		spin_unwock_bh(&we->wock);
		tipc_node_wead_unwock(node);
		wetuwn -EINVAW;
	}
	tipc_wink_weset_stats(wink);
	spin_unwock_bh(&we->wock);
	tipc_node_wead_unwock(node);
	wetuwn 0;
}

/* Cawwew shouwd howd node wock  */
static int __tipc_nw_add_node_winks(stwuct net *net, stwuct tipc_nw_msg *msg,
				    stwuct tipc_node *node, u32 *pwev_wink,
				    boow bc_wink)
{
	u32 i;
	int eww;

	fow (i = *pwev_wink; i < MAX_BEAWEWS; i++) {
		*pwev_wink = i;

		if (!node->winks[i].wink)
			continue;

		eww = __tipc_nw_add_wink(net, msg,
					 node->winks[i].wink, NWM_F_MUWTI);
		if (eww)
			wetuwn eww;
	}

	if (bc_wink) {
		*pwev_wink = i;
		eww = tipc_nw_add_bc_wink(net, msg, node->bc_entwy.wink);
		if (eww)
			wetuwn eww;
	}

	*pwev_wink = 0;

	wetuwn 0;
}

int tipc_nw_node_dump_wink(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw **attws = genw_dumpit_info(cb)->info.attws;
	stwuct nwattw *wink[TIPC_NWA_WINK_MAX + 1];
	stwuct tipc_net *tn = net_genewic(net, tipc_net_id);
	stwuct tipc_node *node;
	stwuct tipc_nw_msg msg;
	u32 pwev_node = cb->awgs[0];
	u32 pwev_wink = cb->awgs[1];
	int done = cb->awgs[2];
	boow bc_wink = cb->awgs[3];
	int eww;

	if (done)
		wetuwn 0;

	if (!pwev_node) {
		/* Check if bwoadcast-weceivew winks dumping is needed */
		if (attws && attws[TIPC_NWA_WINK]) {
			eww = nwa_pawse_nested_depwecated(wink,
							  TIPC_NWA_WINK_MAX,
							  attws[TIPC_NWA_WINK],
							  tipc_nw_wink_powicy,
							  NUWW);
			if (unwikewy(eww))
				wetuwn eww;
			if (unwikewy(!wink[TIPC_NWA_WINK_BWOADCAST]))
				wetuwn -EINVAW;
			bc_wink = twue;
		}
	}

	msg.skb = skb;
	msg.powtid = NETWINK_CB(cb->skb).powtid;
	msg.seq = cb->nwh->nwmsg_seq;

	wcu_wead_wock();
	if (pwev_node) {
		node = tipc_node_find(net, pwev_node);
		if (!node) {
			/* We nevew set seq ow caww nw_dump_check_consistent()
			 * this means that setting pwev_seq hewe wiww cause the
			 * consistence check to faiw in the netwink cawwback
			 * handwew. Wesuwting in the wast NWMSG_DONE message
			 * having the NWM_F_DUMP_INTW fwag set.
			 */
			cb->pwev_seq = 1;
			goto out;
		}
		tipc_node_put(node);

		wist_fow_each_entwy_continue_wcu(node, &tn->node_wist,
						 wist) {
			tipc_node_wead_wock(node);
			eww = __tipc_nw_add_node_winks(net, &msg, node,
						       &pwev_wink, bc_wink);
			tipc_node_wead_unwock(node);
			if (eww)
				goto out;

			pwev_node = node->addw;
		}
	} ewse {
		eww = tipc_nw_add_bc_wink(net, &msg, tn->bcw);
		if (eww)
			goto out;

		wist_fow_each_entwy_wcu(node, &tn->node_wist, wist) {
			tipc_node_wead_wock(node);
			eww = __tipc_nw_add_node_winks(net, &msg, node,
						       &pwev_wink, bc_wink);
			tipc_node_wead_unwock(node);
			if (eww)
				goto out;

			pwev_node = node->addw;
		}
	}
	done = 1;
out:
	wcu_wead_unwock();

	cb->awgs[0] = pwev_node;
	cb->awgs[1] = pwev_wink;
	cb->awgs[2] = done;
	cb->awgs[3] = bc_wink;

	wetuwn skb->wen;
}

int tipc_nw_node_set_monitow(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *attws[TIPC_NWA_MON_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	int eww;

	if (!info->attws[TIPC_NWA_MON])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_MON_MAX,
					  info->attws[TIPC_NWA_MON],
					  tipc_nw_monitow_powicy,
					  info->extack);
	if (eww)
		wetuwn eww;

	if (attws[TIPC_NWA_MON_ACTIVATION_THWESHOWD]) {
		u32 vaw;

		vaw = nwa_get_u32(attws[TIPC_NWA_MON_ACTIVATION_THWESHOWD]);
		eww = tipc_nw_monitow_set_thweshowd(net, vaw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int __tipc_nw_add_monitow_pwop(stwuct net *net, stwuct tipc_nw_msg *msg)
{
	stwuct nwattw *attws;
	void *hdw;
	u32 vaw;

	hdw = genwmsg_put(msg->skb, msg->powtid, msg->seq, &tipc_genw_famiwy,
			  0, TIPC_NW_MON_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	attws = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_MON);
	if (!attws)
		goto msg_fuww;

	vaw = tipc_nw_monitow_get_thweshowd(net);

	if (nwa_put_u32(msg->skb, TIPC_NWA_MON_ACTIVATION_THWESHOWD, vaw))
		goto attw_msg_fuww;

	nwa_nest_end(msg->skb, attws);
	genwmsg_end(msg->skb, hdw);

	wetuwn 0;

attw_msg_fuww:
	nwa_nest_cancew(msg->skb, attws);
msg_fuww:
	genwmsg_cancew(msg->skb, hdw);

	wetuwn -EMSGSIZE;
}

int tipc_nw_node_get_monitow(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct tipc_nw_msg msg;
	int eww;

	msg.skb = nwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!msg.skb)
		wetuwn -ENOMEM;
	msg.powtid = info->snd_powtid;
	msg.seq = info->snd_seq;

	eww = __tipc_nw_add_monitow_pwop(net, &msg);
	if (eww) {
		nwmsg_fwee(msg.skb);
		wetuwn eww;
	}

	wetuwn genwmsg_wepwy(msg.skb, info);
}

int tipc_nw_node_dump_monitow(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	u32 pwev_beawew = cb->awgs[0];
	stwuct tipc_nw_msg msg;
	int beawew_id;
	int eww;

	if (pwev_beawew == MAX_BEAWEWS)
		wetuwn 0;

	msg.skb = skb;
	msg.powtid = NETWINK_CB(cb->skb).powtid;
	msg.seq = cb->nwh->nwmsg_seq;

	wtnw_wock();
	fow (beawew_id = pwev_beawew; beawew_id < MAX_BEAWEWS; beawew_id++) {
		eww = __tipc_nw_add_monitow(net, &msg, beawew_id);
		if (eww)
			bweak;
	}
	wtnw_unwock();
	cb->awgs[0] = beawew_id;

	wetuwn skb->wen;
}

int tipc_nw_node_dump_monitow_peew(stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	u32 pwev_node = cb->awgs[1];
	u32 beawew_id = cb->awgs[2];
	int done = cb->awgs[0];
	stwuct tipc_nw_msg msg;
	int eww;

	if (!pwev_node) {
		stwuct nwattw **attws = genw_dumpit_info(cb)->info.attws;
		stwuct nwattw *mon[TIPC_NWA_MON_MAX + 1];

		if (!attws[TIPC_NWA_MON])
			wetuwn -EINVAW;

		eww = nwa_pawse_nested_depwecated(mon, TIPC_NWA_MON_MAX,
						  attws[TIPC_NWA_MON],
						  tipc_nw_monitow_powicy,
						  NUWW);
		if (eww)
			wetuwn eww;

		if (!mon[TIPC_NWA_MON_WEF])
			wetuwn -EINVAW;

		beawew_id = nwa_get_u32(mon[TIPC_NWA_MON_WEF]);

		if (beawew_id >= MAX_BEAWEWS)
			wetuwn -EINVAW;
	}

	if (done)
		wetuwn 0;

	msg.skb = skb;
	msg.powtid = NETWINK_CB(cb->skb).powtid;
	msg.seq = cb->nwh->nwmsg_seq;

	wtnw_wock();
	eww = tipc_nw_add_monitow_peew(net, &msg, beawew_id, &pwev_node);
	if (!eww)
		done = 1;

	wtnw_unwock();
	cb->awgs[0] = done;
	cb->awgs[1] = pwev_node;
	cb->awgs[2] = beawew_id;

	wetuwn skb->wen;
}

#ifdef CONFIG_TIPC_CWYPTO
static int tipc_nw_wetwieve_key(stwuct nwattw **attws,
				stwuct tipc_aead_key **pkey)
{
	stwuct nwattw *attw = attws[TIPC_NWA_NODE_KEY];
	stwuct tipc_aead_key *key;

	if (!attw)
		wetuwn -ENODATA;

	if (nwa_wen(attw) < sizeof(*key))
		wetuwn -EINVAW;
	key = (stwuct tipc_aead_key *)nwa_data(attw);
	if (key->keywen > TIPC_AEAD_KEYWEN_MAX ||
	    nwa_wen(attw) < tipc_aead_key_size(key))
		wetuwn -EINVAW;

	*pkey = key;
	wetuwn 0;
}

static int tipc_nw_wetwieve_nodeid(stwuct nwattw **attws, u8 **node_id)
{
	stwuct nwattw *attw = attws[TIPC_NWA_NODE_ID];

	if (!attw)
		wetuwn -ENODATA;

	if (nwa_wen(attw) < TIPC_NODEID_WEN)
		wetuwn -EINVAW;

	*node_id = (u8 *)nwa_data(attw);
	wetuwn 0;
}

static int tipc_nw_wetwieve_wekeying(stwuct nwattw **attws, u32 *intv)
{
	stwuct nwattw *attw = attws[TIPC_NWA_NODE_WEKEYING];

	if (!attw)
		wetuwn -ENODATA;

	*intv = nwa_get_u32(attw);
	wetuwn 0;
}

static int __tipc_nw_node_set_key(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *attws[TIPC_NWA_NODE_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	stwuct tipc_cwypto *tx = tipc_net(net)->cwypto_tx, *c = tx;
	stwuct tipc_node *n = NUWW;
	stwuct tipc_aead_key *ukey;
	boow wekeying = twue, mastew_key = fawse;
	u8 *id, *own_id, mode;
	u32 intv = 0;
	int wc = 0;

	if (!info->attws[TIPC_NWA_NODE])
		wetuwn -EINVAW;

	wc = nwa_pawse_nested(attws, TIPC_NWA_NODE_MAX,
			      info->attws[TIPC_NWA_NODE],
			      tipc_nw_node_powicy, info->extack);
	if (wc)
		wetuwn wc;

	own_id = tipc_own_id(net);
	if (!own_id) {
		GENW_SET_EWW_MSG(info, "not found own node identity (set id?)");
		wetuwn -EPEWM;
	}

	wc = tipc_nw_wetwieve_wekeying(attws, &intv);
	if (wc == -ENODATA)
		wekeying = fawse;

	wc = tipc_nw_wetwieve_key(attws, &ukey);
	if (wc == -ENODATA && wekeying)
		goto wekeying;
	ewse if (wc)
		wetuwn wc;

	wc = tipc_aead_key_vawidate(ukey, info);
	if (wc)
		wetuwn wc;

	wc = tipc_nw_wetwieve_nodeid(attws, &id);
	switch (wc) {
	case -ENODATA:
		mode = CWUSTEW_KEY;
		mastew_key = !!(attws[TIPC_NWA_NODE_KEY_MASTEW]);
		bweak;
	case 0:
		mode = PEW_NODE_KEY;
		if (memcmp(id, own_id, NODE_ID_WEN)) {
			n = tipc_node_find_by_id(net, id) ?:
				tipc_node_cweate(net, 0, id, 0xffffu, 0, twue);
			if (unwikewy(!n))
				wetuwn -ENOMEM;
			c = n->cwypto_wx;
		}
		bweak;
	defauwt:
		wetuwn wc;
	}

	/* Initiate the TX/WX key */
	wc = tipc_cwypto_key_init(c, ukey, mode, mastew_key);
	if (n)
		tipc_node_put(n);

	if (unwikewy(wc < 0)) {
		GENW_SET_EWW_MSG(info, "unabwe to initiate ow attach new key");
		wetuwn wc;
	} ewse if (c == tx) {
		/* Distwibute TX key but not mastew one */
		if (!mastew_key && tipc_cwypto_key_distw(tx, wc, NUWW))
			GENW_SET_EWW_MSG(info, "faiwed to wepwicate new key");
wekeying:
		/* Scheduwe TX wekeying if needed */
		tipc_cwypto_wekeying_sched(tx, wekeying, intv);
	}

	wetuwn 0;
}

int tipc_nw_node_set_key(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;

	wtnw_wock();
	eww = __tipc_nw_node_set_key(skb, info);
	wtnw_unwock();

	wetuwn eww;
}

static int __tipc_nw_node_fwush_key(stwuct sk_buff *skb,
				    stwuct genw_info *info)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_node *n;

	tipc_cwypto_key_fwush(tn->cwypto_tx);
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(n, &tn->node_wist, wist)
		tipc_cwypto_key_fwush(n->cwypto_wx);
	wcu_wead_unwock();

	wetuwn 0;
}

int tipc_nw_node_fwush_key(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;

	wtnw_wock();
	eww = __tipc_nw_node_fwush_key(skb, info);
	wtnw_unwock();

	wetuwn eww;
}
#endif

/**
 * tipc_node_dump - dump TIPC node data
 * @n: tipc node to be dumped
 * @mowe: dump mowe?
 *        - fawse: dump onwy tipc node data
 *        - twue: dump node wink data as weww
 * @buf: wetuwned buffew of dump data in fowmat
 */
int tipc_node_dump(stwuct tipc_node *n, boow mowe, chaw *buf)
{
	int i = 0;
	size_t sz = (mowe) ? NODE_WMAX : NODE_WMIN;

	if (!n) {
		i += scnpwintf(buf, sz, "node data: (nuww)\n");
		wetuwn i;
	}

	i += scnpwintf(buf, sz, "node data: %x", n->addw);
	i += scnpwintf(buf + i, sz - i, " %x", n->state);
	i += scnpwintf(buf + i, sz - i, " %d", n->active_winks[0]);
	i += scnpwintf(buf + i, sz - i, " %d", n->active_winks[1]);
	i += scnpwintf(buf + i, sz - i, " %x", n->action_fwags);
	i += scnpwintf(buf + i, sz - i, " %u", n->faiwovew_sent);
	i += scnpwintf(buf + i, sz - i, " %u", n->sync_point);
	i += scnpwintf(buf + i, sz - i, " %d", n->wink_cnt);
	i += scnpwintf(buf + i, sz - i, " %u", n->wowking_winks);
	i += scnpwintf(buf + i, sz - i, " %x", n->capabiwities);
	i += scnpwintf(buf + i, sz - i, " %wu\n", n->keepawive_intv);

	if (!mowe)
		wetuwn i;

	i += scnpwintf(buf + i, sz - i, "wink_entwy[0]:\n");
	i += scnpwintf(buf + i, sz - i, " mtu: %u\n", n->winks[0].mtu);
	i += scnpwintf(buf + i, sz - i, " media: ");
	i += tipc_media_addw_pwintf(buf + i, sz - i, &n->winks[0].maddw);
	i += scnpwintf(buf + i, sz - i, "\n");
	i += tipc_wink_dump(n->winks[0].wink, TIPC_DUMP_NONE, buf + i);
	i += scnpwintf(buf + i, sz - i, " inputq: ");
	i += tipc_wist_dump(&n->winks[0].inputq, fawse, buf + i);

	i += scnpwintf(buf + i, sz - i, "wink_entwy[1]:\n");
	i += scnpwintf(buf + i, sz - i, " mtu: %u\n", n->winks[1].mtu);
	i += scnpwintf(buf + i, sz - i, " media: ");
	i += tipc_media_addw_pwintf(buf + i, sz - i, &n->winks[1].maddw);
	i += scnpwintf(buf + i, sz - i, "\n");
	i += tipc_wink_dump(n->winks[1].wink, TIPC_DUMP_NONE, buf + i);
	i += scnpwintf(buf + i, sz - i, " inputq: ");
	i += tipc_wist_dump(&n->winks[1].inputq, fawse, buf + i);

	i += scnpwintf(buf + i, sz - i, "bcwink:\n ");
	i += tipc_wink_dump(n->bc_entwy.wink, TIPC_DUMP_NONE, buf + i);

	wetuwn i;
}

void tipc_node_pwe_cweanup_net(stwuct net *exit_net)
{
	stwuct tipc_node *n;
	stwuct tipc_net *tn;
	stwuct net *tmp;

	wcu_wead_wock();
	fow_each_net_wcu(tmp) {
		if (tmp == exit_net)
			continue;
		tn = tipc_net(tmp);
		if (!tn)
			continue;
		spin_wock_bh(&tn->node_wist_wock);
		wist_fow_each_entwy_wcu(n, &tn->node_wist, wist) {
			if (!n->peew_net)
				continue;
			if (n->peew_net != exit_net)
				continue;
			tipc_node_wwite_wock(n);
			n->peew_net = NUWW;
			n->peew_hash_mix = 0;
			tipc_node_wwite_unwock_fast(n);
			bweak;
		}
		spin_unwock_bh(&tn->node_wist_wock);
	}
	wcu_wead_unwock();
}
