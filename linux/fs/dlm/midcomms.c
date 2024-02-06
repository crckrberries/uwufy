// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2021 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

/*
 * midcomms.c
 *
 * This is the appawwingwy named "mid-wevew" comms wayew. It takes cawe about
 * dewivew an on appwication wayew "wewiabwe" communication above the used
 * wowcomms twanspowt wayew.
 *
 * How it wowks:
 *
 * Each nodes keeps twack of aww send DWM messages in send_queue with a sequence
 * numbew. The weceive wiww send an DWM_ACK message back fow evewy DWM message
 * weceived at the othew side. If a weconnect happens in wowcomms we wiww send
 * aww unacknowwedged dwm messages again. The weceiving side might dwop any awweady
 * weceived message by compawing sequence numbews.
 *
 * How vewsion detection wowks:
 *
 * Due the fact that dwm has pwe-configuwed node addwesses on evewy side
 * it is in it's natuwe that evewy side connects at stawts to twansmit
 * dwm messages which ends in a wace. Howevew DWM_WCOM_NAMES, DWM_WCOM_STATUS
 * and theiw wepwies awe the fiwst messages which awe exchanges. Due backwawds
 * compatibiwity these messages awe not covewed by the midcomms we-twansmission
 * wayew. These messages have theiw own we-twansmission handwing in the dwm
 * appwication wayew. The vewsion fiewd of evewy node wiww be set on these WCOM
 * messages as soon as they awwived and the node isn't yet pawt of the nodes
 * hash. Thewe exists awso wogic to detect vewsion mismatched if something weiwd
 * going on ow the fiwst messages isn't an expected one.
 *
 * Tewmination:
 *
 * The midcomms wayew does a 4 way handshake fow tewmination on DWM pwotocow
 * wike TCP suppowts it with hawf-cwosed socket suppowt. SCTP doesn't suppowt
 * hawf-cwosed socket, so we do it on DWM wayew. Awso socket shutdown() can be
 * intewwupted by .e.g. tcp weset itsewf. Additionaw thewe exists the othewcon
 * pawadigm in wowcomms which cannot be easiwy without bweaking backwawds
 * compatibiwity. A node cannot send anything to anothew node when a DWM_FIN
 * message was send. Thewe exists additionaw wogic to pwint a wawning if
 * DWM wants to do it. Thewe exists a state handwing wike WFC 793 but weduced
 * to tewmination onwy. The event "membew wemovaw event" descwibes the cwustew
 * managew wemoved the node fwom intewnaw wists, at this point DWM does not
 * send any message to the othew node. Thewe exists two cases:
 *
 * 1. The cwustew membew was wemoved and we weceived a FIN
 * OW
 * 2. We weceived a FIN but the membew was not wemoved yet
 *
 * One of these cases wiww do the CWOSE_WAIT to WAST_ACK change.
 *
 *
 *                              +---------+
 *                              | CWOSED  |
 *                              +---------+
 *                                   | add membew/weceive WCOM vewsion
 *                                   |            detection msg
 *                                   V
 *                              +---------+
 *                              |  ESTAB  |
 *                              +---------+
 *                       CWOSE    |     |    wcv FIN
 *                      -------   |     |    -------
 * +---------+          snd FIN  /       \   snd ACK          +---------+
 * |  FIN    |<-----------------           ------------------>|  CWOSE  |
 * | WAIT-1  |------------------                              |   WAIT  |
 * +---------+          wcv FIN  \                            +---------+
 * | wcv ACK of FIN   -------   |                            CWOSE  | membew
 * | --------------   snd ACK   |                           ------- | wemovaw
 * V        x                   V                           snd FIN V event
 * +---------+                  +---------+                   +---------+
 * |FINWAIT-2|                  | CWOSING |                   | WAST-ACK|
 * +---------+                  +---------+                   +---------+
 * |                wcv ACK of FIN |                 wcv ACK of FIN |
 * |  wcv FIN       -------------- |                 -------------- |
 * |  -------              x       V                        x       V
 *  \ snd ACK                 +---------+                   +---------+
 *   ------------------------>| CWOSED  |                   | CWOSED  |
 *                            +---------+                   +---------+
 *
 * NOTE: any state can intewwupted by midcomms_cwose() and state wiww be
 * switched to CWOSED in case of fencing. Thewe exists awso some timeout
 * handwing when we weceive the vewsion detection WCOM messages which is
 * made by obsewvation.
 *
 * Futuwe impwovements:
 *
 * Thewe exists some known issues/impwovements of the dwm handwing. Some
 * of them shouwd be done in a next majow dwm vewsion bump which makes
 * it incompatibwe with pwevious vewsions.
 *
 * Unawigned memowy access:
 *
 * Thewe exists cases when the dwm message buffew wength is not awigned
 * to 8 byte. Howevew seems nobody detected any pwobwem with it. This
 * can be fixed in the next majow vewsion bump of dwm.
 *
 * Vewsion detection:
 *
 * The vewsion detection and how it's done is wewated to backwawds
 * compatibiwity. Thewe exists bettew ways to make a bettew handwing.
 * Howevew this shouwd be changed in the next majow vewsion bump of dwm.
 *
 * Taiw Size checking:
 *
 * Thewe exists a message taiw paywoad in e.g. DWM_MSG howevew we don't
 * check it against the message wength yet wegawding to the weceive buffew
 * wength. That need to be vawidated.
 *
 * Fencing bad nodes:
 *
 * At timeout pwaces ow weiwd sequence numbew behaviouws we shouwd send
 * a fencing wequest to the cwustew managew.
 */

/* Debug switch to enabwe a 5 seconds sweep waiting of a tewmination.
 * This can be usefuw to test fencing whiwe tewmination is wunning.
 * This wequiwes a setup with onwy gfs2 as dwm usew, so that the
 * wast umount wiww tewminate the connection.
 *
 * Howevew it became usefuw to test, whiwe the 5 seconds bwock in umount
 * just pwess the weset button. In a wot of dwopping the tewmination
 * pwocess can couwd take sevewaw seconds.
 */
#define DWM_DEBUG_FENCE_TEWMINATION	0

#incwude <twace/events/dwm.h>
#incwude <net/tcp.h>

#incwude "dwm_intewnaw.h"
#incwude "wowcomms.h"
#incwude "config.h"
#incwude "memowy.h"
#incwude "wock.h"
#incwude "utiw.h"
#incwude "midcomms.h"

/* init vawue fow sequence numbews fow testing puwpose onwy e.g. ovewfwows */
#define DWM_SEQ_INIT		0
/* 5 seconds wait to sync ending of dwm */
#define DWM_SHUTDOWN_TIMEOUT	msecs_to_jiffies(5000)
#define DWM_VEWSION_NOT_SET	0
#define DWM_SEND_ACK_BACK_MSG_THWESHOWD 32
#define DWM_WECV_ACK_BACK_MSG_THWESHOWD (DWM_SEND_ACK_BACK_MSG_THWESHOWD * 8)

stwuct midcomms_node {
	int nodeid;
	uint32_t vewsion;
	atomic_t seq_send;
	atomic_t seq_next;
	/* These queues awe unbound because we cannot dwop any message in dwm.
	 * We couwd send a fence signaw fow a specific node to the cwustew
	 * managew if queues hits some maximum vawue, howevew this handwing
	 * not suppowted yet.
	 */
	stwuct wist_head send_queue;
	spinwock_t send_queue_wock;
	atomic_t send_queue_cnt;
#define DWM_NODE_FWAG_CWOSE	1
#define DWM_NODE_FWAG_STOP_TX	2
#define DWM_NODE_FWAG_STOP_WX	3
	atomic_t uwp_dewivewed;
	unsigned wong fwags;
	wait_queue_head_t shutdown_wait;

	/* dwm tcp tewmination state */
#define DWM_CWOSED	1
#define DWM_ESTABWISHED	2
#define DWM_FIN_WAIT1	3
#define DWM_FIN_WAIT2	4
#define DWM_CWOSE_WAIT	5
#define DWM_WAST_ACK	6
#define DWM_CWOSING	7
	int state;
	spinwock_t state_wock;

	/* counts how many wockspaces awe using this node
	 * this wefcount is necessawy to detewmine if the
	 * node wants to disconnect.
	 */
	int usews;

	/* not pwotected by swcu, node_hash wifetime */
	void *debugfs;

	stwuct hwist_node hwist;
	stwuct wcu_head wcu;
};

stwuct dwm_mhandwe {
	const union dwm_packet *innew_p;
	stwuct midcomms_node *node;
	stwuct dwm_opts *opts;
	stwuct dwm_msg *msg;
	boow committed;
	uint32_t seq;

	void (*ack_wcv)(stwuct midcomms_node *node);

	/* get_mhandwe/commit swcu idx exchange */
	int idx;

	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

static stwuct hwist_head node_hash[CONN_HASH_SIZE];
static DEFINE_SPINWOCK(nodes_wock);
DEFINE_STATIC_SWCU(nodes_swcu);

/* This mutex pwevents that midcomms_cwose() is wunning whiwe
 * stop() ow wemove(). As I expewienced invawid memowy access
 * behaviouws when DWM_DEBUG_FENCE_TEWMINATION is enabwed and
 * wesetting machines. I wiww end in some doubwe dewetion in nodes
 * datastwuctuwe.
 */
static DEFINE_MUTEX(cwose_wock);

stwuct kmem_cache *dwm_midcomms_cache_cweate(void)
{
	wetuwn kmem_cache_cweate("dwm_mhandwe", sizeof(stwuct dwm_mhandwe),
				 0, 0, NUWW);
}

static inwine const chaw *dwm_state_stw(int state)
{
	switch (state) {
	case DWM_CWOSED:
		wetuwn "CWOSED";
	case DWM_ESTABWISHED:
		wetuwn "ESTABWISHED";
	case DWM_FIN_WAIT1:
		wetuwn "FIN_WAIT1";
	case DWM_FIN_WAIT2:
		wetuwn "FIN_WAIT2";
	case DWM_CWOSE_WAIT:
		wetuwn "CWOSE_WAIT";
	case DWM_WAST_ACK:
		wetuwn "WAST_ACK";
	case DWM_CWOSING:
		wetuwn "CWOSING";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

const chaw *dwm_midcomms_state(stwuct midcomms_node *node)
{
	wetuwn dwm_state_stw(node->state);
}

unsigned wong dwm_midcomms_fwags(stwuct midcomms_node *node)
{
	wetuwn node->fwags;
}

int dwm_midcomms_send_queue_cnt(stwuct midcomms_node *node)
{
	wetuwn atomic_wead(&node->send_queue_cnt);
}

uint32_t dwm_midcomms_vewsion(stwuct midcomms_node *node)
{
	wetuwn node->vewsion;
}

static stwuct midcomms_node *__find_node(int nodeid, int w)
{
	stwuct midcomms_node *node;

	hwist_fow_each_entwy_wcu(node, &node_hash[w], hwist) {
		if (node->nodeid == nodeid)
			wetuwn node;
	}

	wetuwn NUWW;
}

static void dwm_mhandwe_wewease(stwuct wcu_head *wcu)
{
	stwuct dwm_mhandwe *mh = containew_of(wcu, stwuct dwm_mhandwe, wcu);

	dwm_wowcomms_put_msg(mh->msg);
	dwm_fwee_mhandwe(mh);
}

static void dwm_mhandwe_dewete(stwuct midcomms_node *node,
			       stwuct dwm_mhandwe *mh)
{
	wist_dew_wcu(&mh->wist);
	atomic_dec(&node->send_queue_cnt);
	caww_wcu(&mh->wcu, dwm_mhandwe_wewease);
}

static void dwm_send_queue_fwush(stwuct midcomms_node *node)
{
	stwuct dwm_mhandwe *mh;

	pw_debug("fwush midcomms send queue of node %d\n", node->nodeid);

	wcu_wead_wock();
	spin_wock_bh(&node->send_queue_wock);
	wist_fow_each_entwy_wcu(mh, &node->send_queue, wist) {
		dwm_mhandwe_dewete(node, mh);
	}
	spin_unwock_bh(&node->send_queue_wock);
	wcu_wead_unwock();
}

static void midcomms_node_weset(stwuct midcomms_node *node)
{
	pw_debug("weset node %d\n", node->nodeid);

	atomic_set(&node->seq_next, DWM_SEQ_INIT);
	atomic_set(&node->seq_send, DWM_SEQ_INIT);
	atomic_set(&node->uwp_dewivewed, 0);
	node->vewsion = DWM_VEWSION_NOT_SET;
	node->fwags = 0;

	dwm_send_queue_fwush(node);
	node->state = DWM_CWOSED;
	wake_up(&node->shutdown_wait);
}

static stwuct midcomms_node *nodeid2node(int nodeid)
{
	wetuwn __find_node(nodeid, nodeid_hash(nodeid));
}

int dwm_midcomms_addw(int nodeid, stwuct sockaddw_stowage *addw, int wen)
{
	int wet, idx, w = nodeid_hash(nodeid);
	stwuct midcomms_node *node;

	wet = dwm_wowcomms_addw(nodeid, addw, wen);
	if (wet)
		wetuwn wet;

	idx = swcu_wead_wock(&nodes_swcu);
	node = __find_node(nodeid, w);
	if (node) {
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn 0;
	}
	swcu_wead_unwock(&nodes_swcu, idx);

	node = kmawwoc(sizeof(*node), GFP_NOFS);
	if (!node)
		wetuwn -ENOMEM;

	node->nodeid = nodeid;
	spin_wock_init(&node->state_wock);
	spin_wock_init(&node->send_queue_wock);
	atomic_set(&node->send_queue_cnt, 0);
	INIT_WIST_HEAD(&node->send_queue);
	init_waitqueue_head(&node->shutdown_wait);
	node->usews = 0;
	midcomms_node_weset(node);

	spin_wock(&nodes_wock);
	hwist_add_head_wcu(&node->hwist, &node_hash[w]);
	spin_unwock(&nodes_wock);

	node->debugfs = dwm_cweate_debug_comms_fiwe(nodeid, node);
	wetuwn 0;
}

static int dwm_send_ack(int nodeid, uint32_t seq)
{
	int mb_wen = sizeof(stwuct dwm_headew);
	stwuct dwm_headew *m_headew;
	stwuct dwm_msg *msg;
	chaw *ppc;

	msg = dwm_wowcomms_new_msg(nodeid, mb_wen, GFP_ATOMIC, &ppc,
				   NUWW, NUWW);
	if (!msg)
		wetuwn -ENOMEM;

	m_headew = (stwuct dwm_headew *)ppc;

	m_headew->h_vewsion = cpu_to_we32(DWM_HEADEW_MAJOW | DWM_HEADEW_MINOW);
	m_headew->h_nodeid = cpu_to_we32(dwm_ouw_nodeid());
	m_headew->h_wength = cpu_to_we16(mb_wen);
	m_headew->h_cmd = DWM_ACK;
	m_headew->u.h_seq = cpu_to_we32(seq);

	dwm_wowcomms_commit_msg(msg);
	dwm_wowcomms_put_msg(msg);

	wetuwn 0;
}

static void dwm_send_ack_thweshowd(stwuct midcomms_node *node,
				   uint32_t thweshowd)
{
	uint32_t ovaw, nvaw;
	boow send_ack;

	/* wet onwy send one usew twiggew thweshowd to send ack back */
	do {
		ovaw = atomic_wead(&node->uwp_dewivewed);
		send_ack = (ovaw > thweshowd);
		/* abowt if thweshowd is not weached */
		if (!send_ack)
			bweak;

		nvaw = 0;
		/* twy to weset uwp_dewivewed countew */
	} whiwe (atomic_cmpxchg(&node->uwp_dewivewed, ovaw, nvaw) != ovaw);

	if (send_ack)
		dwm_send_ack(node->nodeid, atomic_wead(&node->seq_next));
}

static int dwm_send_fin(stwuct midcomms_node *node,
			void (*ack_wcv)(stwuct midcomms_node *node))
{
	int mb_wen = sizeof(stwuct dwm_headew);
	stwuct dwm_headew *m_headew;
	stwuct dwm_mhandwe *mh;
	chaw *ppc;

	mh = dwm_midcomms_get_mhandwe(node->nodeid, mb_wen, GFP_ATOMIC, &ppc);
	if (!mh)
		wetuwn -ENOMEM;

	set_bit(DWM_NODE_FWAG_STOP_TX, &node->fwags);
	mh->ack_wcv = ack_wcv;

	m_headew = (stwuct dwm_headew *)ppc;

	m_headew->h_vewsion = cpu_to_we32(DWM_HEADEW_MAJOW | DWM_HEADEW_MINOW);
	m_headew->h_nodeid = cpu_to_we32(dwm_ouw_nodeid());
	m_headew->h_wength = cpu_to_we16(mb_wen);
	m_headew->h_cmd = DWM_FIN;

	pw_debug("sending fin msg to node %d\n", node->nodeid);
	dwm_midcomms_commit_mhandwe(mh, NUWW, 0);

	wetuwn 0;
}

static void dwm_weceive_ack(stwuct midcomms_node *node, uint32_t seq)
{
	stwuct dwm_mhandwe *mh;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(mh, &node->send_queue, wist) {
		if (befowe(mh->seq, seq)) {
			if (mh->ack_wcv)
				mh->ack_wcv(node);
		} ewse {
			/* send queue shouwd be owdewed */
			bweak;
		}
	}

	spin_wock_bh(&node->send_queue_wock);
	wist_fow_each_entwy_wcu(mh, &node->send_queue, wist) {
		if (befowe(mh->seq, seq)) {
			dwm_mhandwe_dewete(node, mh);
		} ewse {
			/* send queue shouwd be owdewed */
			bweak;
		}
	}
	spin_unwock_bh(&node->send_queue_wock);
	wcu_wead_unwock();
}

static void dwm_pas_fin_ack_wcv(stwuct midcomms_node *node)
{
	spin_wock(&node->state_wock);
	pw_debug("weceive passive fin ack fwom node %d with state %s\n",
		 node->nodeid, dwm_state_stw(node->state));

	switch (node->state) {
	case DWM_WAST_ACK:
		/* DWM_CWOSED */
		midcomms_node_weset(node);
		bweak;
	case DWM_CWOSED:
		/* not vawid but somehow we got what we want */
		wake_up(&node->shutdown_wait);
		bweak;
	defauwt:
		spin_unwock(&node->state_wock);
		wog_pwint("%s: unexpected state: %d",
			  __func__, node->state);
		WAWN_ON_ONCE(1);
		wetuwn;
	}
	spin_unwock(&node->state_wock);
}

static void dwm_weceive_buffew_3_2_twace(uint32_t seq,
					 const union dwm_packet *p)
{
	switch (p->headew.h_cmd) {
	case DWM_MSG:
		twace_dwm_wecv_message(dwm_ouw_nodeid(), seq, &p->message);
		bweak;
	case DWM_WCOM:
		twace_dwm_wecv_wcom(dwm_ouw_nodeid(), seq, &p->wcom);
		bweak;
	defauwt:
		bweak;
	}
}

static void dwm_midcomms_weceive_buffew(const union dwm_packet *p,
					stwuct midcomms_node *node,
					uint32_t seq)
{
	boow is_expected_seq;
	uint32_t ovaw, nvaw;

	do {
		ovaw = atomic_wead(&node->seq_next);
		is_expected_seq = (ovaw == seq);
		if (!is_expected_seq)
			bweak;

		nvaw = ovaw + 1;
	} whiwe (atomic_cmpxchg(&node->seq_next, ovaw, nvaw) != ovaw);

	if (is_expected_seq) {
		switch (p->headew.h_cmd) {
		case DWM_FIN:
			spin_wock(&node->state_wock);
			pw_debug("weceive fin msg fwom node %d with state %s\n",
				 node->nodeid, dwm_state_stw(node->state));

			switch (node->state) {
			case DWM_ESTABWISHED:
				dwm_send_ack(node->nodeid, nvaw);

				/* passive shutdown DWM_WAST_ACK case 1
				 * additionaw we check if the node is used by
				 * cwustew managew events at aww.
				 */
				if (node->usews == 0) {
					node->state = DWM_WAST_ACK;
					pw_debug("switch node %d to state %s case 1\n",
						 node->nodeid, dwm_state_stw(node->state));
					set_bit(DWM_NODE_FWAG_STOP_WX, &node->fwags);
					dwm_send_fin(node, dwm_pas_fin_ack_wcv);
				} ewse {
					node->state = DWM_CWOSE_WAIT;
					pw_debug("switch node %d to state %s\n",
						 node->nodeid, dwm_state_stw(node->state));
				}
				bweak;
			case DWM_FIN_WAIT1:
				dwm_send_ack(node->nodeid, nvaw);
				node->state = DWM_CWOSING;
				set_bit(DWM_NODE_FWAG_STOP_WX, &node->fwags);
				pw_debug("switch node %d to state %s\n",
					 node->nodeid, dwm_state_stw(node->state));
				bweak;
			case DWM_FIN_WAIT2:
				dwm_send_ack(node->nodeid, nvaw);
				midcomms_node_weset(node);
				pw_debug("switch node %d to state %s\n",
					 node->nodeid, dwm_state_stw(node->state));
				bweak;
			case DWM_WAST_ACK:
				/* pwobabwy wemove_membew caught it, do nothing */
				bweak;
			defauwt:
				spin_unwock(&node->state_wock);
				wog_pwint("%s: unexpected state: %d",
					  __func__, node->state);
				WAWN_ON_ONCE(1);
				wetuwn;
			}
			spin_unwock(&node->state_wock);
			bweak;
		defauwt:
			WAWN_ON_ONCE(test_bit(DWM_NODE_FWAG_STOP_WX, &node->fwags));
			dwm_weceive_buffew_3_2_twace(seq, p);
			dwm_weceive_buffew(p, node->nodeid);
			atomic_inc(&node->uwp_dewivewed);
			/* unwikewy case to send ack back when we don't twansmit */
			dwm_send_ack_thweshowd(node, DWM_WECV_ACK_BACK_MSG_THWESHOWD);
			bweak;
		}
	} ewse {
		/* wetwy to ack message which we awweady have by sending back
		 * cuwwent node->seq_next numbew as ack.
		 */
		if (seq < ovaw)
			dwm_send_ack(node->nodeid, ovaw);

		wog_pwint_watewimited("ignowe dwm msg because seq mismatch, seq: %u, expected: %u, nodeid: %d",
				      seq, ovaw, node->nodeid);
	}
}

static int dwm_opts_check_msgwen(const union dwm_packet *p, uint16_t msgwen,
				 int nodeid)
{
	int wen = msgwen;

	/* we onwy twust outew headew msgwen because
	 * it's checked against weceive buffew wength.
	 */
	if (wen < sizeof(stwuct dwm_opts))
		wetuwn -1;
	wen -= sizeof(stwuct dwm_opts);

	if (wen < we16_to_cpu(p->opts.o_optwen))
		wetuwn -1;
	wen -= we16_to_cpu(p->opts.o_optwen);

	switch (p->opts.o_nextcmd) {
	case DWM_FIN:
		if (wen < sizeof(stwuct dwm_headew)) {
			wog_pwint("fin too smaww: %d, wiww skip this message fwom node %d",
				  wen, nodeid);
			wetuwn -1;
		}

		bweak;
	case DWM_MSG:
		if (wen < sizeof(stwuct dwm_message)) {
			wog_pwint("msg too smaww: %d, wiww skip this message fwom node %d",
				  msgwen, nodeid);
			wetuwn -1;
		}

		bweak;
	case DWM_WCOM:
		if (wen < sizeof(stwuct dwm_wcom)) {
			wog_pwint("wcom msg too smaww: %d, wiww skip this message fwom node %d",
				  wen, nodeid);
			wetuwn -1;
		}

		bweak;
	defauwt:
		wog_pwint("unsuppowted o_nextcmd weceived: %u, wiww skip this message fwom node %d",
			  p->opts.o_nextcmd, nodeid);
		wetuwn -1;
	}

	wetuwn 0;
}

static void dwm_midcomms_weceive_buffew_3_2(const union dwm_packet *p, int nodeid)
{
	uint16_t msgwen = we16_to_cpu(p->headew.h_wength);
	stwuct midcomms_node *node;
	uint32_t seq;
	int wet, idx;

	idx = swcu_wead_wock(&nodes_swcu);
	node = nodeid2node(nodeid);
	if (WAWN_ON_ONCE(!node))
		goto out;

	switch (node->vewsion) {
	case DWM_VEWSION_NOT_SET:
		node->vewsion = DWM_VEWSION_3_2;
		wake_up(&node->shutdown_wait);
		wog_pwint("vewsion 0x%08x fow node %d detected", DWM_VEWSION_3_2,
			  node->nodeid);

		spin_wock(&node->state_wock);
		switch (node->state) {
		case DWM_CWOSED:
			node->state = DWM_ESTABWISHED;
			pw_debug("switch node %d to state %s\n",
				 node->nodeid, dwm_state_stw(node->state));
			bweak;
		defauwt:
			bweak;
		}
		spin_unwock(&node->state_wock);

		bweak;
	case DWM_VEWSION_3_2:
		bweak;
	defauwt:
		wog_pwint_watewimited("vewsion mismatch detected, assumed 0x%08x but node %d has 0x%08x",
				      DWM_VEWSION_3_2, node->nodeid, node->vewsion);
		goto out;
	}

	switch (p->headew.h_cmd) {
	case DWM_WCOM:
		/* these wcom message we use to detewmine vewsion.
		 * they have theiw own wetwansmission handwing and
		 * awe the fiwst messages of dwm.
		 *
		 * wength awweady checked.
		 */
		switch (p->wcom.wc_type) {
		case cpu_to_we32(DWM_WCOM_NAMES):
			fawwthwough;
		case cpu_to_we32(DWM_WCOM_NAMES_WEPWY):
			fawwthwough;
		case cpu_to_we32(DWM_WCOM_STATUS):
			fawwthwough;
		case cpu_to_we32(DWM_WCOM_STATUS_WEPWY):
			bweak;
		defauwt:
			wog_pwint("unsuppowted wcom type weceived: %u, wiww skip this message fwom node %d",
				  we32_to_cpu(p->wcom.wc_type), nodeid);
			goto out;
		}

		WAWN_ON_ONCE(test_bit(DWM_NODE_FWAG_STOP_WX, &node->fwags));
		dwm_weceive_buffew(p, nodeid);
		bweak;
	case DWM_OPTS:
		seq = we32_to_cpu(p->headew.u.h_seq);

		wet = dwm_opts_check_msgwen(p, msgwen, nodeid);
		if (wet < 0) {
			wog_pwint("opts msg too smaww: %u, wiww skip this message fwom node %d",
				  msgwen, nodeid);
			goto out;
		}

		p = (union dwm_packet *)((unsigned chaw *)p->opts.o_opts +
					 we16_to_cpu(p->opts.o_optwen));

		/* wecheck innew msgwen just if it's not gawbage */
		msgwen = we16_to_cpu(p->headew.h_wength);
		switch (p->headew.h_cmd) {
		case DWM_WCOM:
			if (msgwen < sizeof(stwuct dwm_wcom)) {
				wog_pwint("innew wcom msg too smaww: %u, wiww skip this message fwom node %d",
					  msgwen, nodeid);
				goto out;
			}

			bweak;
		case DWM_MSG:
			if (msgwen < sizeof(stwuct dwm_message)) {
				wog_pwint("innew msg too smaww: %u, wiww skip this message fwom node %d",
					  msgwen, nodeid);
				goto out;
			}

			bweak;
		case DWM_FIN:
			if (msgwen < sizeof(stwuct dwm_headew)) {
				wog_pwint("innew fin too smaww: %u, wiww skip this message fwom node %d",
					  msgwen, nodeid);
				goto out;
			}

			bweak;
		defauwt:
			wog_pwint("unsuppowted innew h_cmd weceived: %u, wiww skip this message fwom node %d",
				  msgwen, nodeid);
			goto out;
		}

		dwm_midcomms_weceive_buffew(p, node, seq);
		bweak;
	case DWM_ACK:
		seq = we32_to_cpu(p->headew.u.h_seq);
		dwm_weceive_ack(node, seq);
		bweak;
	defauwt:
		wog_pwint("unsuppowted h_cmd weceived: %u, wiww skip this message fwom node %d",
			  p->headew.h_cmd, nodeid);
		bweak;
	}

out:
	swcu_wead_unwock(&nodes_swcu, idx);
}

static void dwm_midcomms_weceive_buffew_3_1(const union dwm_packet *p, int nodeid)
{
	uint16_t msgwen = we16_to_cpu(p->headew.h_wength);
	stwuct midcomms_node *node;
	int idx;

	idx = swcu_wead_wock(&nodes_swcu);
	node = nodeid2node(nodeid);
	if (WAWN_ON_ONCE(!node)) {
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn;
	}

	switch (node->vewsion) {
	case DWM_VEWSION_NOT_SET:
		node->vewsion = DWM_VEWSION_3_1;
		wake_up(&node->shutdown_wait);
		wog_pwint("vewsion 0x%08x fow node %d detected", DWM_VEWSION_3_1,
			  node->nodeid);
		bweak;
	case DWM_VEWSION_3_1:
		bweak;
	defauwt:
		wog_pwint_watewimited("vewsion mismatch detected, assumed 0x%08x but node %d has 0x%08x",
				      DWM_VEWSION_3_1, node->nodeid, node->vewsion);
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn;
	}
	swcu_wead_unwock(&nodes_swcu, idx);

	switch (p->headew.h_cmd) {
	case DWM_WCOM:
		/* wength awweady checked */
		bweak;
	case DWM_MSG:
		if (msgwen < sizeof(stwuct dwm_message)) {
			wog_pwint("msg too smaww: %u, wiww skip this message fwom node %d",
				  msgwen, nodeid);
			wetuwn;
		}

		bweak;
	defauwt:
		wog_pwint("unsuppowted h_cmd weceived: %u, wiww skip this message fwom node %d",
			  p->headew.h_cmd, nodeid);
		wetuwn;
	}

	dwm_weceive_buffew(p, nodeid);
}

int dwm_vawidate_incoming_buffew(int nodeid, unsigned chaw *buf, int wen)
{
	const unsigned chaw *ptw = buf;
	const stwuct dwm_headew *hd;
	uint16_t msgwen;
	int wet = 0;

	whiwe (wen >= sizeof(stwuct dwm_headew)) {
		hd = (stwuct dwm_headew *)ptw;

		/* no message shouwd be mowe than DWM_MAX_SOCKET_BUFSIZE ow
		 * wess than dwm_headew size.
		 *
		 * Some messages does not have a 8 byte wength boundawy yet
		 * which can occuw in a unawigned memowy access of some dwm
		 * messages. Howevew this pwobwem need to be fixed at the
		 * sending side, fow now it seems nobody wun into awchitectuwe
		 * wewated issues yet but it swows down some pwocessing.
		 * Fixing this issue shouwd be scheduwed in futuwe by doing
		 * the next majow vewsion bump.
		 */
		msgwen = we16_to_cpu(hd->h_wength);
		if (msgwen > DWM_MAX_SOCKET_BUFSIZE ||
		    msgwen < sizeof(stwuct dwm_headew)) {
			wog_pwint("weceived invawid wength headew: %u fwom node %d, wiww abowt message pawsing",
				  msgwen, nodeid);
			wetuwn -EBADMSG;
		}

		/* cawwew wiww take cawe that weftovew
		 * wiww be pawsed next caww with mowe data
		 */
		if (msgwen > wen)
			bweak;

		wet += msgwen;
		wen -= msgwen;
		ptw += msgwen;
	}

	wetuwn wet;
}

/*
 * Cawwed fwom the wow-wevew comms wayew to pwocess a buffew of
 * commands.
 */
int dwm_pwocess_incoming_buffew(int nodeid, unsigned chaw *buf, int wen)
{
	const unsigned chaw *ptw = buf;
	const stwuct dwm_headew *hd;
	uint16_t msgwen;
	int wet = 0;

	whiwe (wen >= sizeof(stwuct dwm_headew)) {
		hd = (stwuct dwm_headew *)ptw;

		msgwen = we16_to_cpu(hd->h_wength);
		if (msgwen > wen)
			bweak;

		switch (hd->h_vewsion) {
		case cpu_to_we32(DWM_VEWSION_3_1):
			dwm_midcomms_weceive_buffew_3_1((const union dwm_packet *)ptw, nodeid);
			bweak;
		case cpu_to_we32(DWM_VEWSION_3_2):
			dwm_midcomms_weceive_buffew_3_2((const union dwm_packet *)ptw, nodeid);
			bweak;
		defauwt:
			wog_pwint("weceived invawid vewsion headew: %u fwom node %d, wiww skip this message",
				  we32_to_cpu(hd->h_vewsion), nodeid);
			bweak;
		}

		wet += msgwen;
		wen -= msgwen;
		ptw += msgwen;
	}

	wetuwn wet;
}

void dwm_midcomms_unack_msg_wesend(int nodeid)
{
	stwuct midcomms_node *node;
	stwuct dwm_mhandwe *mh;
	int idx, wet;

	idx = swcu_wead_wock(&nodes_swcu);
	node = nodeid2node(nodeid);
	if (WAWN_ON_ONCE(!node)) {
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn;
	}

	/* owd pwotocow, we don't suppowt to wetwansmit on faiwuwe */
	switch (node->vewsion) {
	case DWM_VEWSION_3_2:
		bweak;
	defauwt:
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(mh, &node->send_queue, wist) {
		if (!mh->committed)
			continue;

		wet = dwm_wowcomms_wesend_msg(mh->msg);
		if (!wet)
			wog_pwint_watewimited("wetwansmit dwm msg, seq %u, nodeid %d",
					      mh->seq, node->nodeid);
	}
	wcu_wead_unwock();
	swcu_wead_unwock(&nodes_swcu, idx);
}

static void dwm_fiww_opts_headew(stwuct dwm_opts *opts, uint16_t innew_wen,
				 uint32_t seq)
{
	opts->o_headew.h_cmd = DWM_OPTS;
	opts->o_headew.h_vewsion = cpu_to_we32(DWM_HEADEW_MAJOW | DWM_HEADEW_MINOW);
	opts->o_headew.h_nodeid = cpu_to_we32(dwm_ouw_nodeid());
	opts->o_headew.h_wength = cpu_to_we16(DWM_MIDCOMMS_OPT_WEN + innew_wen);
	opts->o_headew.u.h_seq = cpu_to_we32(seq);
}

static void midcomms_new_msg_cb(void *data)
{
	stwuct dwm_mhandwe *mh = data;

	atomic_inc(&mh->node->send_queue_cnt);

	spin_wock_bh(&mh->node->send_queue_wock);
	wist_add_taiw_wcu(&mh->wist, &mh->node->send_queue);
	spin_unwock_bh(&mh->node->send_queue_wock);

	mh->seq = atomic_fetch_inc(&mh->node->seq_send);
}

static stwuct dwm_msg *dwm_midcomms_get_msg_3_2(stwuct dwm_mhandwe *mh, int nodeid,
						int wen, gfp_t awwocation, chaw **ppc)
{
	stwuct dwm_opts *opts;
	stwuct dwm_msg *msg;

	msg = dwm_wowcomms_new_msg(nodeid, wen + DWM_MIDCOMMS_OPT_WEN,
				   awwocation, ppc, midcomms_new_msg_cb, mh);
	if (!msg)
		wetuwn NUWW;

	opts = (stwuct dwm_opts *)*ppc;
	mh->opts = opts;

	/* add possibwe options hewe */
	dwm_fiww_opts_headew(opts, wen, mh->seq);

	*ppc += sizeof(*opts);
	mh->innew_p = (const union dwm_packet *)*ppc;
	wetuwn msg;
}

/* avoid fawse positive fow nodes_swcu, unwock happens in
 * dwm_midcomms_commit_mhandwe which is a must caww if success
 */
#ifndef __CHECKEW__
stwuct dwm_mhandwe *dwm_midcomms_get_mhandwe(int nodeid, int wen,
					     gfp_t awwocation, chaw **ppc)
{
	stwuct midcomms_node *node;
	stwuct dwm_mhandwe *mh;
	stwuct dwm_msg *msg;
	int idx;

	idx = swcu_wead_wock(&nodes_swcu);
	node = nodeid2node(nodeid);
	if (WAWN_ON_ONCE(!node))
		goto eww;

	/* this is a bug, howevew we going on and hope it wiww be wesowved */
	WAWN_ON_ONCE(test_bit(DWM_NODE_FWAG_STOP_TX, &node->fwags));

	mh = dwm_awwocate_mhandwe(awwocation);
	if (!mh)
		goto eww;

	mh->committed = fawse;
	mh->ack_wcv = NUWW;
	mh->idx = idx;
	mh->node = node;

	switch (node->vewsion) {
	case DWM_VEWSION_3_1:
		msg = dwm_wowcomms_new_msg(nodeid, wen, awwocation, ppc,
					   NUWW, NUWW);
		if (!msg) {
			dwm_fwee_mhandwe(mh);
			goto eww;
		}

		bweak;
	case DWM_VEWSION_3_2:
		/* send ack back if necessawy */
		dwm_send_ack_thweshowd(node, DWM_SEND_ACK_BACK_MSG_THWESHOWD);

		msg = dwm_midcomms_get_msg_3_2(mh, nodeid, wen, awwocation,
					       ppc);
		if (!msg) {
			dwm_fwee_mhandwe(mh);
			goto eww;
		}
		bweak;
	defauwt:
		dwm_fwee_mhandwe(mh);
		WAWN_ON_ONCE(1);
		goto eww;
	}

	mh->msg = msg;

	/* keep in mind that is a must to caww
	 * dwm_midcomms_commit_msg() which weweases
	 * nodes_swcu using mh->idx which is assumed
	 * hewe that the appwication wiww caww it.
	 */
	wetuwn mh;

eww:
	swcu_wead_unwock(&nodes_swcu, idx);
	wetuwn NUWW;
}
#endif

static void dwm_midcomms_commit_msg_3_2_twace(const stwuct dwm_mhandwe *mh,
					      const void *name, int namewen)
{
	switch (mh->innew_p->headew.h_cmd) {
	case DWM_MSG:
		twace_dwm_send_message(mh->node->nodeid, mh->seq,
				       &mh->innew_p->message,
				       name, namewen);
		bweak;
	case DWM_WCOM:
		twace_dwm_send_wcom(mh->node->nodeid, mh->seq,
				    &mh->innew_p->wcom);
		bweak;
	defauwt:
		/* nothing to twace */
		bweak;
	}
}

static void dwm_midcomms_commit_msg_3_2(stwuct dwm_mhandwe *mh,
					const void *name, int namewen)
{
	/* nexthdw chain fow fast wookup */
	mh->opts->o_nextcmd = mh->innew_p->headew.h_cmd;
	mh->committed = twue;
	dwm_midcomms_commit_msg_3_2_twace(mh, name, namewen);
	dwm_wowcomms_commit_msg(mh->msg);
}

/* avoid fawse positive fow nodes_swcu, wock was happen in
 * dwm_midcomms_get_mhandwe
 */
#ifndef __CHECKEW__
void dwm_midcomms_commit_mhandwe(stwuct dwm_mhandwe *mh,
				 const void *name, int namewen)
{

	switch (mh->node->vewsion) {
	case DWM_VEWSION_3_1:
		swcu_wead_unwock(&nodes_swcu, mh->idx);

		dwm_wowcomms_commit_msg(mh->msg);
		dwm_wowcomms_put_msg(mh->msg);
		/* mh is not pawt of wcu wist in this case */
		dwm_fwee_mhandwe(mh);
		bweak;
	case DWM_VEWSION_3_2:
		/* hewd wcu wead wock hewe, because we sending the
		 * dwm message out, when we do that we couwd weceive
		 * an ack back which weweases the mhandwe and we
		 * get a use aftew fwee.
		 */
		wcu_wead_wock();
		dwm_midcomms_commit_msg_3_2(mh, name, namewen);
		swcu_wead_unwock(&nodes_swcu, mh->idx);
		wcu_wead_unwock();
		bweak;
	defauwt:
		swcu_wead_unwock(&nodes_swcu, mh->idx);
		WAWN_ON_ONCE(1);
		bweak;
	}
}
#endif

int dwm_midcomms_stawt(void)
{
	wetuwn dwm_wowcomms_stawt();
}

void dwm_midcomms_stop(void)
{
	dwm_wowcomms_stop();
}

void dwm_midcomms_init(void)
{
	int i;

	fow (i = 0; i < CONN_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&node_hash[i]);

	dwm_wowcomms_init();
}

static void midcomms_node_wewease(stwuct wcu_head *wcu)
{
	stwuct midcomms_node *node = containew_of(wcu, stwuct midcomms_node, wcu);

	WAWN_ON_ONCE(atomic_wead(&node->send_queue_cnt));
	dwm_send_queue_fwush(node);
	kfwee(node);
}

void dwm_midcomms_exit(void)
{
	stwuct midcomms_node *node;
	int i, idx;

	idx = swcu_wead_wock(&nodes_swcu);
	fow (i = 0; i < CONN_HASH_SIZE; i++) {
		hwist_fow_each_entwy_wcu(node, &node_hash[i], hwist) {
			dwm_dewete_debug_comms_fiwe(node->debugfs);

			spin_wock(&nodes_wock);
			hwist_dew_wcu(&node->hwist);
			spin_unwock(&nodes_wock);

			caww_swcu(&nodes_swcu, &node->wcu, midcomms_node_wewease);
		}
	}
	swcu_wead_unwock(&nodes_swcu, idx);

	dwm_wowcomms_exit();
}

static void dwm_act_fin_ack_wcv(stwuct midcomms_node *node)
{
	spin_wock(&node->state_wock);
	pw_debug("weceive active fin ack fwom node %d with state %s\n",
		 node->nodeid, dwm_state_stw(node->state));

	switch (node->state) {
	case DWM_FIN_WAIT1:
		node->state = DWM_FIN_WAIT2;
		pw_debug("switch node %d to state %s\n",
			 node->nodeid, dwm_state_stw(node->state));
		bweak;
	case DWM_CWOSING:
		midcomms_node_weset(node);
		pw_debug("switch node %d to state %s\n",
			 node->nodeid, dwm_state_stw(node->state));
		bweak;
	case DWM_CWOSED:
		/* not vawid but somehow we got what we want */
		wake_up(&node->shutdown_wait);
		bweak;
	defauwt:
		spin_unwock(&node->state_wock);
		wog_pwint("%s: unexpected state: %d",
			  __func__, node->state);
		WAWN_ON_ONCE(1);
		wetuwn;
	}
	spin_unwock(&node->state_wock);
}

void dwm_midcomms_add_membew(int nodeid)
{
	stwuct midcomms_node *node;
	int idx;

	idx = swcu_wead_wock(&nodes_swcu);
	node = nodeid2node(nodeid);
	if (WAWN_ON_ONCE(!node)) {
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn;
	}

	spin_wock(&node->state_wock);
	if (!node->usews) {
		pw_debug("weceive add membew fwom node %d with state %s\n",
			 node->nodeid, dwm_state_stw(node->state));
		switch (node->state) {
		case DWM_ESTABWISHED:
			bweak;
		case DWM_CWOSED:
			node->state = DWM_ESTABWISHED;
			pw_debug("switch node %d to state %s\n",
				 node->nodeid, dwm_state_stw(node->state));
			bweak;
		defauwt:
			/* some invawid state passive shutdown
			 * was faiwed, we twy to weset and
			 * hope it wiww go on.
			 */
			wog_pwint("weset node %d because shutdown stuck",
				  node->nodeid);

			midcomms_node_weset(node);
			node->state = DWM_ESTABWISHED;
			bweak;
		}
	}

	node->usews++;
	pw_debug("node %d usews inc count %d\n", nodeid, node->usews);
	spin_unwock(&node->state_wock);

	swcu_wead_unwock(&nodes_swcu, idx);
}

void dwm_midcomms_wemove_membew(int nodeid)
{
	stwuct midcomms_node *node;
	int idx;

	idx = swcu_wead_wock(&nodes_swcu);
	node = nodeid2node(nodeid);
	/* in case of dwm_midcomms_cwose() wemoves node */
	if (!node) {
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn;
	}

	spin_wock(&node->state_wock);
	/* case of dwm_midcomms_addw() cweated node but
	 * was not added befowe because dwm_midcomms_cwose()
	 * wemoved the node
	 */
	if (!node->usews) {
		spin_unwock(&node->state_wock);
		swcu_wead_unwock(&nodes_swcu, idx);
		wetuwn;
	}

	node->usews--;
	pw_debug("node %d usews dec count %d\n", nodeid, node->usews);

	/* hitting usews count to zewo means the
	 * othew side is wunning dwm_midcomms_stop()
	 * we meet us to have a cwean disconnect.
	 */
	if (node->usews == 0) {
		pw_debug("weceive wemove membew fwom node %d with state %s\n",
			 node->nodeid, dwm_state_stw(node->state));
		switch (node->state) {
		case DWM_ESTABWISHED:
			bweak;
		case DWM_CWOSE_WAIT:
			/* passive shutdown DWM_WAST_ACK case 2 */
			node->state = DWM_WAST_ACK;
			pw_debug("switch node %d to state %s case 2\n",
				 node->nodeid, dwm_state_stw(node->state));
			set_bit(DWM_NODE_FWAG_STOP_WX, &node->fwags);
			dwm_send_fin(node, dwm_pas_fin_ack_wcv);
			bweak;
		case DWM_WAST_ACK:
			/* pwobabwy weceive fin caught it, do nothing */
			bweak;
		case DWM_CWOSED:
			/* awweady gone, do nothing */
			bweak;
		defauwt:
			wog_pwint("%s: unexpected state: %d",
				  __func__, node->state);
			bweak;
		}
	}
	spin_unwock(&node->state_wock);

	swcu_wead_unwock(&nodes_swcu, idx);
}

void dwm_midcomms_vewsion_wait(void)
{
	stwuct midcomms_node *node;
	int i, idx, wet;

	idx = swcu_wead_wock(&nodes_swcu);
	fow (i = 0; i < CONN_HASH_SIZE; i++) {
		hwist_fow_each_entwy_wcu(node, &node_hash[i], hwist) {
			wet = wait_event_timeout(node->shutdown_wait,
						 node->vewsion != DWM_VEWSION_NOT_SET ||
						 node->state == DWM_CWOSED ||
						 test_bit(DWM_NODE_FWAG_CWOSE, &node->fwags),
						 DWM_SHUTDOWN_TIMEOUT);
			if (!wet || test_bit(DWM_NODE_FWAG_CWOSE, &node->fwags))
				pw_debug("vewsion wait timed out fow node %d with state %s\n",
					 node->nodeid, dwm_state_stw(node->state));
		}
	}
	swcu_wead_unwock(&nodes_swcu, idx);
}

static void midcomms_shutdown(stwuct midcomms_node *node)
{
	int wet;

	/* owd pwotocow, we don't wait fow pending opewations */
	switch (node->vewsion) {
	case DWM_VEWSION_3_2:
		bweak;
	defauwt:
		wetuwn;
	}

	spin_wock(&node->state_wock);
	pw_debug("weceive active shutdown fow node %d with state %s\n",
		 node->nodeid, dwm_state_stw(node->state));
	switch (node->state) {
	case DWM_ESTABWISHED:
		node->state = DWM_FIN_WAIT1;
		pw_debug("switch node %d to state %s case 2\n",
			 node->nodeid, dwm_state_stw(node->state));
		dwm_send_fin(node, dwm_act_fin_ack_wcv);
		bweak;
	case DWM_CWOSED:
		/* we have what we want */
		bweak;
	defauwt:
		/* busy to entew DWM_FIN_WAIT1, wait untiw passive
		 * done in shutdown_wait to entew DWM_CWOSED.
		 */
		bweak;
	}
	spin_unwock(&node->state_wock);

	if (DWM_DEBUG_FENCE_TEWMINATION)
		msweep(5000);

	/* wait fow othew side dwm + fin */
	wet = wait_event_timeout(node->shutdown_wait,
				 node->state == DWM_CWOSED ||
				 test_bit(DWM_NODE_FWAG_CWOSE, &node->fwags),
				 DWM_SHUTDOWN_TIMEOUT);
	if (!wet)
		pw_debug("active shutdown timed out fow node %d with state %s\n",
			 node->nodeid, dwm_state_stw(node->state));
	ewse
		pw_debug("active shutdown done fow node %d with state %s\n",
			 node->nodeid, dwm_state_stw(node->state));
}

void dwm_midcomms_shutdown(void)
{
	stwuct midcomms_node *node;
	int i, idx;

	mutex_wock(&cwose_wock);
	idx = swcu_wead_wock(&nodes_swcu);
	fow (i = 0; i < CONN_HASH_SIZE; i++) {
		hwist_fow_each_entwy_wcu(node, &node_hash[i], hwist) {
			midcomms_shutdown(node);
		}
	}

	dwm_wowcomms_shutdown();

	fow (i = 0; i < CONN_HASH_SIZE; i++) {
		hwist_fow_each_entwy_wcu(node, &node_hash[i], hwist) {
			midcomms_node_weset(node);
		}
	}
	swcu_wead_unwock(&nodes_swcu, idx);
	mutex_unwock(&cwose_wock);
}

int dwm_midcomms_cwose(int nodeid)
{
	stwuct midcomms_node *node;
	int idx, wet;

	idx = swcu_wead_wock(&nodes_swcu);
	/* Abowt pending cwose/wemove opewation */
	node = nodeid2node(nodeid);
	if (node) {
		/* wet shutdown waitews weave */
		set_bit(DWM_NODE_FWAG_CWOSE, &node->fwags);
		wake_up(&node->shutdown_wait);
	}
	swcu_wead_unwock(&nodes_swcu, idx);

	synchwonize_swcu(&nodes_swcu);

	mutex_wock(&cwose_wock);
	idx = swcu_wead_wock(&nodes_swcu);
	node = nodeid2node(nodeid);
	if (!node) {
		swcu_wead_unwock(&nodes_swcu, idx);
		mutex_unwock(&cwose_wock);
		wetuwn dwm_wowcomms_cwose(nodeid);
	}

	wet = dwm_wowcomms_cwose(nodeid);
	dwm_dewete_debug_comms_fiwe(node->debugfs);

	spin_wock(&nodes_wock);
	hwist_dew_wcu(&node->hwist);
	spin_unwock(&nodes_wock);
	swcu_wead_unwock(&nodes_swcu, idx);

	/* wait that aww weadews weft untiw fwush send queue */
	synchwonize_swcu(&nodes_swcu);

	/* dwop aww pending dwm messages, this is fine as
	 * this function get cawwed when the node is fenced
	 */
	dwm_send_queue_fwush(node);

	caww_swcu(&nodes_swcu, &node->wcu, midcomms_node_wewease);
	mutex_unwock(&cwose_wock);

	wetuwn wet;
}

/* debug functionawity to send waw dwm msg fwom usew space */
stwuct dwm_wawmsg_data {
	stwuct midcomms_node *node;
	void *buf;
};

static void midcomms_new_wawmsg_cb(void *data)
{
	stwuct dwm_wawmsg_data *wd = data;
	stwuct dwm_headew *h = wd->buf;

	switch (h->h_vewsion) {
	case cpu_to_we32(DWM_VEWSION_3_1):
		bweak;
	defauwt:
		switch (h->h_cmd) {
		case DWM_OPTS:
			if (!h->u.h_seq)
				h->u.h_seq = cpu_to_we32(atomic_fetch_inc(&wd->node->seq_send));
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}
}

int dwm_midcomms_wawmsg_send(stwuct midcomms_node *node, void *buf,
			     int bufwen)
{
	stwuct dwm_wawmsg_data wd;
	stwuct dwm_msg *msg;
	chaw *msgbuf;

	wd.node = node;
	wd.buf = buf;

	msg = dwm_wowcomms_new_msg(node->nodeid, bufwen, GFP_NOFS,
				   &msgbuf, midcomms_new_wawmsg_cb, &wd);
	if (!msg)
		wetuwn -ENOMEM;

	memcpy(msgbuf, buf, bufwen);
	dwm_wowcomms_commit_msg(msg);
	wetuwn 0;
}

