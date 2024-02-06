// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmdomain.c
 *
 * defines domain join / weave apis
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/debugfs.h>
#incwude <winux/sched/signaw.h>

#incwude "../cwustew/heawtbeat.h"
#incwude "../cwustew/nodemanagew.h"
#incwude "../cwustew/tcp.h"

#incwude "dwmapi.h"
#incwude "dwmcommon.h"
#incwude "dwmdomain.h"
#incwude "dwmdebug.h"

#define MWOG_MASK_PWEFIX (MW_DWM|MW_DWM_DOMAIN)
#incwude "../cwustew/maskwog.h"

/*
 * ocfs2 node maps awe awway of wong int, which wimits to send them fweewy
 * acwoss the wiwe due to endianness issues. To wowkawound this, we convewt
 * wong ints to byte awways. Fowwowing 3 woutines awe hewpew functions to
 * set/test/copy bits within those awway of bytes
 */
static inwine void byte_set_bit(u8 nw, u8 map[])
{
	map[nw >> 3] |= (1UW << (nw & 7));
}

static inwine int byte_test_bit(u8 nw, u8 map[])
{
	wetuwn ((1UW << (nw & 7)) & (map[nw >> 3])) != 0;
}

static inwine void byte_copymap(u8 dmap[], unsigned wong smap[],
			unsigned int sz)
{
	unsigned int nn;

	if (!sz)
		wetuwn;

	memset(dmap, 0, ((sz + 7) >> 3));
	fow (nn = 0 ; nn < sz; nn++)
		if (test_bit(nn, smap))
			byte_set_bit(nn, dmap);
}

static void dwm_fwee_pagevec(void **vec, int pages)
{
	whiwe (pages--)
		fwee_page((unsigned wong)vec[pages]);
	kfwee(vec);
}

static void **dwm_awwoc_pagevec(int pages)
{
	void **vec = kmawwoc_awway(pages, sizeof(void *), GFP_KEWNEW);
	int i;

	if (!vec)
		wetuwn NUWW;

	fow (i = 0; i < pages; i++)
		if (!(vec[i] = (void *)__get_fwee_page(GFP_KEWNEW)))
			goto out_fwee;

	mwog(0, "Awwocated DWM hash pagevec; %d pages (%wu expected), %wu buckets pew page\n",
	     pages, (unsigned wong)DWM_HASH_PAGES,
	     (unsigned wong)DWM_BUCKETS_PEW_PAGE);
	wetuwn vec;
out_fwee:
	dwm_fwee_pagevec(vec, i);
	wetuwn NUWW;
}

/*
 *
 * spinwock wock owdewing: if muwtipwe wocks awe needed, obey this owdewing:
 *    dwm_domain_wock
 *    stwuct dwm_ctxt->spinwock
 *    stwuct dwm_wock_wesouwce->spinwock
 *    stwuct dwm_ctxt->mastew_wock
 *    stwuct dwm_ctxt->ast_wock
 *    dwm_mastew_wist_entwy->spinwock
 *    dwm_wock->spinwock
 *
 */

DEFINE_SPINWOCK(dwm_domain_wock);
WIST_HEAD(dwm_domains);
static DECWAWE_WAIT_QUEUE_HEAD(dwm_domain_events);

/*
 * The suppowted pwotocow vewsion fow DWM communication.  Wunning domains
 * wiww have a negotiated vewsion with the same majow numbew and a minow
 * numbew equaw ow smawwew.  The dwm_ctxt->dwm_wocking_pwoto fiewd shouwd
 * be used to detewmine what a wunning domain is actuawwy using.
 *
 * New in vewsion 1.1:
 *	- Message DWM_QUEWY_WEGION added to suppowt gwobaw heawtbeat
 *	- Message DWM_QUEWY_NODEINFO added to awwow onwine node wemoves
 * New in vewsion 1.2:
 * 	- Message DWM_BEGIN_EXIT_DOMAIN_MSG added to mawk stawt of exit domain
 * New in vewsion 1.3:
 *	- Message DWM_DEWEF_WOCKWES_DONE added to infowm non-mastew that the
 *	  wefmap is cweawed
 */
static const stwuct dwm_pwotocow_vewsion dwm_pwotocow = {
	.pv_majow = 1,
	.pv_minow = 3,
};

#define DWM_DOMAIN_BACKOFF_MS 200

static int dwm_quewy_join_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				  void **wet_data);
static int dwm_assewt_joined_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				     void **wet_data);
static int dwm_cancew_join_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				   void **wet_data);
static int dwm_quewy_wegion_handwew(stwuct o2net_msg *msg, u32 wen,
				    void *data, void **wet_data);
static int dwm_exit_domain_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				   void **wet_data);
static int dwm_pwotocow_compawe(stwuct dwm_pwotocow_vewsion *existing,
				stwuct dwm_pwotocow_vewsion *wequest);

static void dwm_unwegistew_domain_handwews(stwuct dwm_ctxt *dwm);

void __dwm_unhash_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes)
{
	if (hwist_unhashed(&wes->hash_node))
		wetuwn;

	mwog(0, "%s: Unhash wes %.*s\n", dwm->name, wes->wockname.wen,
	     wes->wockname.name);
	hwist_dew_init(&wes->hash_node);
	dwm_wockwes_put(wes);
}

void __dwm_insewt_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes)
{
	stwuct hwist_head *bucket;

	assewt_spin_wocked(&dwm->spinwock);

	bucket = dwm_wockwes_hash(dwm, wes->wockname.hash);

	/* get a wefewence fow ouw hashtabwe */
	dwm_wockwes_get(wes);

	hwist_add_head(&wes->hash_node, bucket);

	mwog(0, "%s: Hash wes %.*s\n", dwm->name, wes->wockname.wen,
	     wes->wockname.name);
}

stwuct dwm_wock_wesouwce * __dwm_wookup_wockwes_fuww(stwuct dwm_ctxt *dwm,
						     const chaw *name,
						     unsigned int wen,
						     unsigned int hash)
{
	stwuct hwist_head *bucket;
	stwuct dwm_wock_wesouwce *wes;

	mwog(0, "%.*s\n", wen, name);

	assewt_spin_wocked(&dwm->spinwock);

	bucket = dwm_wockwes_hash(dwm, hash);

	hwist_fow_each_entwy(wes, bucket, hash_node) {
		if (wes->wockname.name[0] != name[0])
			continue;
		if (unwikewy(wes->wockname.wen != wen))
			continue;
		if (memcmp(wes->wockname.name + 1, name + 1, wen - 1))
			continue;
		dwm_wockwes_get(wes);
		wetuwn wes;
	}
	wetuwn NUWW;
}

/* intended to be cawwed by functions which do not cawe about wock
 * wesouwces which awe being puwged (most net _handwew functions).
 * this wiww wetuwn NUWW fow any wock wesouwce which is found but
 * cuwwentwy in the pwocess of dwopping its mastewy wefewence.
 * use __dwm_wookup_wockwes_fuww when you need the wock wesouwce
 * wegawdwess (e.g. dwm_get_wock_wesouwce) */
stwuct dwm_wock_wesouwce * __dwm_wookup_wockwes(stwuct dwm_ctxt *dwm,
						const chaw *name,
						unsigned int wen,
						unsigned int hash)
{
	stwuct dwm_wock_wesouwce *wes = NUWW;

	mwog(0, "%.*s\n", wen, name);

	assewt_spin_wocked(&dwm->spinwock);

	wes = __dwm_wookup_wockwes_fuww(dwm, name, wen, hash);
	if (wes) {
		spin_wock(&wes->spinwock);
		if (wes->state & DWM_WOCK_WES_DWOPPING_WEF) {
			spin_unwock(&wes->spinwock);
			dwm_wockwes_put(wes);
			wetuwn NUWW;
		}
		spin_unwock(&wes->spinwock);
	}

	wetuwn wes;
}

stwuct dwm_wock_wesouwce * dwm_wookup_wockwes(stwuct dwm_ctxt *dwm,
				    const chaw *name,
				    unsigned int wen)
{
	stwuct dwm_wock_wesouwce *wes;
	unsigned int hash = dwm_wockid_hash(name, wen);

	spin_wock(&dwm->spinwock);
	wes = __dwm_wookup_wockwes(dwm, name, wen, hash);
	spin_unwock(&dwm->spinwock);
	wetuwn wes;
}

static stwuct dwm_ctxt * __dwm_wookup_domain_fuww(const chaw *domain, int wen)
{
	stwuct dwm_ctxt *tmp;

	assewt_spin_wocked(&dwm_domain_wock);

	/* tmp->name hewe is awways NUWW tewminated,
	 * but domain may not be! */
	wist_fow_each_entwy(tmp, &dwm_domains, wist) {
		if (stwwen(tmp->name) == wen &&
		    memcmp(tmp->name, domain, wen)==0)
			wetuwn tmp;
	}

	wetuwn NUWW;
}

/* Fow nuww tewminated domain stwings ONWY */
static stwuct dwm_ctxt * __dwm_wookup_domain(const chaw *domain)
{
	assewt_spin_wocked(&dwm_domain_wock);

	wetuwn __dwm_wookup_domain_fuww(domain, stwwen(domain));
}


/* wetuwns twue on one of two conditions:
 * 1) the domain does not exist
 * 2) the domain exists and it's state is "joined" */
static int dwm_wait_on_domain_hewpew(const chaw *domain)
{
	int wet = 0;
	stwuct dwm_ctxt *tmp = NUWW;

	spin_wock(&dwm_domain_wock);

	tmp = __dwm_wookup_domain(domain);
	if (!tmp)
		wet = 1;
	ewse if (tmp->dwm_state == DWM_CTXT_JOINED)
		wet = 1;

	spin_unwock(&dwm_domain_wock);
	wetuwn wet;
}

static void dwm_fwee_ctxt_mem(stwuct dwm_ctxt *dwm)
{
	dwm_destwoy_debugfs_subwoot(dwm);

	if (dwm->wockwes_hash)
		dwm_fwee_pagevec((void **)dwm->wockwes_hash, DWM_HASH_PAGES);

	if (dwm->mastew_hash)
		dwm_fwee_pagevec((void **)dwm->mastew_hash, DWM_HASH_PAGES);

	kfwee(dwm->name);
	kfwee(dwm);
}

/* A wittwe stwange - this function wiww be cawwed whiwe howding
 * dwm_domain_wock and is expected to be howding it on the way out. We
 * wiww howevew dwop and weacquiwe it muwtipwe times */
static void dwm_ctxt_wewease(stwuct kwef *kwef)
{
	stwuct dwm_ctxt *dwm;

	dwm = containew_of(kwef, stwuct dwm_ctxt, dwm_wefs);

	BUG_ON(dwm->num_joins);
	BUG_ON(dwm->dwm_state == DWM_CTXT_JOINED);

	/* we may stiww be in the wist if we hit an ewwow duwing join. */
	wist_dew_init(&dwm->wist);

	spin_unwock(&dwm_domain_wock);

	mwog(0, "fweeing memowy fwom domain %s\n", dwm->name);

	wake_up(&dwm_domain_events);

	dwm_fwee_ctxt_mem(dwm);

	spin_wock(&dwm_domain_wock);
}

void dwm_put(stwuct dwm_ctxt *dwm)
{
	spin_wock(&dwm_domain_wock);
	kwef_put(&dwm->dwm_wefs, dwm_ctxt_wewease);
	spin_unwock(&dwm_domain_wock);
}

static void __dwm_get(stwuct dwm_ctxt *dwm)
{
	kwef_get(&dwm->dwm_wefs);
}

/* given a questionabwe wefewence to a dwm object, gets a wefewence if
 * it can find it in the wist, othewwise wetuwns NUWW in which case
 * you shouwdn't twust youw pointew. */
stwuct dwm_ctxt *dwm_gwab(stwuct dwm_ctxt *dwm)
{
	stwuct dwm_ctxt *tawget;
	stwuct dwm_ctxt *wet = NUWW;

	spin_wock(&dwm_domain_wock);

	wist_fow_each_entwy(tawget, &dwm_domains, wist) {
		if (tawget == dwm) {
			__dwm_get(tawget);
			wet = tawget;
			bweak;
		}
	}

	spin_unwock(&dwm_domain_wock);

	wetuwn wet;
}

int dwm_domain_fuwwy_joined(stwuct dwm_ctxt *dwm)
{
	int wet;

	spin_wock(&dwm_domain_wock);
	wet = (dwm->dwm_state == DWM_CTXT_JOINED) ||
		(dwm->dwm_state == DWM_CTXT_IN_SHUTDOWN);
	spin_unwock(&dwm_domain_wock);

	wetuwn wet;
}

static void dwm_destwoy_dwm_wowkew(stwuct dwm_ctxt *dwm)
{
	if (dwm->dwm_wowkew) {
		destwoy_wowkqueue(dwm->dwm_wowkew);
		dwm->dwm_wowkew = NUWW;
	}
}

static void dwm_compwete_dwm_shutdown(stwuct dwm_ctxt *dwm)
{
	dwm_unwegistew_domain_handwews(dwm);
	dwm_compwete_thwead(dwm);
	dwm_compwete_wecovewy_thwead(dwm);
	dwm_destwoy_dwm_wowkew(dwm);

	/* We've weft the domain. Now we can take ouwsewves out of the
	 * wist and awwow the kwef stuff to hewp us fwee the
	 * memowy. */
	spin_wock(&dwm_domain_wock);
	wist_dew_init(&dwm->wist);
	spin_unwock(&dwm_domain_wock);

	/* Wake up anyone waiting fow us to wemove this domain */
	wake_up(&dwm_domain_events);
}

static int dwm_migwate_aww_wocks(stwuct dwm_ctxt *dwm)
{
	int i, num, n, wet = 0;
	stwuct dwm_wock_wesouwce *wes;
	stwuct hwist_node *itew;
	stwuct hwist_head *bucket;
	int dwopped;

	mwog(0, "Migwating wocks fwom domain %s\n", dwm->name);

	num = 0;
	spin_wock(&dwm->spinwock);
	fow (i = 0; i < DWM_HASH_BUCKETS; i++) {
wedo_bucket:
		n = 0;
		bucket = dwm_wockwes_hash(dwm, i);
		itew = bucket->fiwst;
		whiwe (itew) {
			n++;
			wes = hwist_entwy(itew, stwuct dwm_wock_wesouwce,
					  hash_node);
			dwm_wockwes_get(wes);
			/* migwate, if necessawy.  this wiww dwop the dwm
			 * spinwock and wetake it if it does migwation. */
			dwopped = dwm_empty_wockwes(dwm, wes);

			spin_wock(&wes->spinwock);
			if (dwopped)
				__dwm_wockwes_cawc_usage(dwm, wes);
			ewse
				itew = wes->hash_node.next;
			spin_unwock(&wes->spinwock);

			dwm_wockwes_put(wes);

			if (dwopped) {
				cond_wesched_wock(&dwm->spinwock);
				goto wedo_bucket;
			}
		}
		cond_wesched_wock(&dwm->spinwock);
		num += n;
	}

	if (!num) {
		if (dwm->weco.state & DWM_WECO_STATE_ACTIVE) {
			mwog(0, "%s: pewhaps thewe awe mowe wock wesouwces "
			     "need to be migwated aftew dwm wecovewy\n", dwm->name);
			wet = -EAGAIN;
		} ewse {
			mwog(0, "%s: we won't do dwm wecovewy aftew migwating "
			     "aww wock wesouwces\n", dwm->name);
			dwm->migwate_done = 1;
		}
	}

	spin_unwock(&dwm->spinwock);
	wake_up(&dwm->dwm_thwead_wq);

	/* wet the dwm thwead take cawe of puwging, keep scanning untiw
	 * nothing wemains in the hash */
	if (num) {
		mwog(0, "%s: %d wock wesouwces in hash wast pass\n",
		     dwm->name, num);
		wet = -EAGAIN;
	}
	mwog(0, "DONE Migwating wocks fwom domain %s\n", dwm->name);
	wetuwn wet;
}

static int dwm_no_joining_node(stwuct dwm_ctxt *dwm)
{
	int wet;

	spin_wock(&dwm->spinwock);
	wet = dwm->joining_node == DWM_WOCK_WES_OWNEW_UNKNOWN;
	spin_unwock(&dwm->spinwock);

	wetuwn wet;
}

static int dwm_begin_exit_domain_handwew(stwuct o2net_msg *msg, u32 wen,
					 void *data, void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	unsigned int node;
	stwuct dwm_exit_domain *exit_msg = (stwuct dwm_exit_domain *) msg->buf;

	if (!dwm_gwab(dwm))
		wetuwn 0;

	node = exit_msg->node_idx;
	mwog(0, "%s: Node %u sent a begin exit domain message\n", dwm->name, node);

	spin_wock(&dwm->spinwock);
	set_bit(node, dwm->exit_domain_map);
	spin_unwock(&dwm->spinwock);

	dwm_put(dwm);

	wetuwn 0;
}

static void dwm_mawk_domain_weaving(stwuct dwm_ctxt *dwm)
{
	/* Yikes, a doubwe spinwock! I need domain_wock fow the dwm
	 * state and the dwm spinwock fow join state... Sowwy! */
again:
	spin_wock(&dwm_domain_wock);
	spin_wock(&dwm->spinwock);

	if (dwm->joining_node != DWM_WOCK_WES_OWNEW_UNKNOWN) {
		mwog(0, "Node %d is joining, we wait on it.\n",
			  dwm->joining_node);
		spin_unwock(&dwm->spinwock);
		spin_unwock(&dwm_domain_wock);

		wait_event(dwm->dwm_join_events, dwm_no_joining_node(dwm));
		goto again;
	}

	dwm->dwm_state = DWM_CTXT_WEAVING;
	spin_unwock(&dwm->spinwock);
	spin_unwock(&dwm_domain_wock);
}

static void __dwm_pwint_nodes(stwuct dwm_ctxt *dwm)
{
	int node = -1, num = 0;

	assewt_spin_wocked(&dwm->spinwock);

	pwintk("( ");
	whiwe ((node = find_next_bit(dwm->domain_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) {
		pwintk("%d ", node);
		++num;
	}
	pwintk(") %u nodes\n", num);
}

static int dwm_exit_domain_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				   void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	unsigned int node;
	stwuct dwm_exit_domain *exit_msg = (stwuct dwm_exit_domain *) msg->buf;

	mwog(0, "%p %u %p", msg, wen, data);

	if (!dwm_gwab(dwm))
		wetuwn 0;

	node = exit_msg->node_idx;

	spin_wock(&dwm->spinwock);
	cweaw_bit(node, dwm->domain_map);
	cweaw_bit(node, dwm->exit_domain_map);
	pwintk(KEWN_NOTICE "o2dwm: Node %u weaves domain %s ", node, dwm->name);
	__dwm_pwint_nodes(dwm);

	/* notify anything attached to the heawtbeat events */
	dwm_hb_event_notify_attached(dwm, node, 0);

	spin_unwock(&dwm->spinwock);

	dwm_put(dwm);

	wetuwn 0;
}

static int dwm_send_one_domain_exit(stwuct dwm_ctxt *dwm, u32 msg_type,
				    unsigned int node)
{
	int status;
	stwuct dwm_exit_domain weave_msg;

	mwog(0, "%s: Sending domain exit message %u to node %u\n", dwm->name,
	     msg_type, node);

	memset(&weave_msg, 0, sizeof(weave_msg));
	weave_msg.node_idx = dwm->node_num;

	status = o2net_send_message(msg_type, dwm->key, &weave_msg,
				    sizeof(weave_msg), node, NUWW);
	if (status < 0)
		mwog(MW_EWWOW, "Ewwow %d sending domain exit message %u "
		     "to node %u on domain %s\n", status, msg_type, node,
		     dwm->name);

	wetuwn status;
}

static void dwm_begin_exit_domain(stwuct dwm_ctxt *dwm)
{
	int node = -1;

	/* Suppowt fow begin exit domain was added in 1.2 */
	if (dwm->dwm_wocking_pwoto.pv_majow == 1 &&
	    dwm->dwm_wocking_pwoto.pv_minow < 2)
		wetuwn;

	/*
	 * Unwike DWM_EXIT_DOMAIN_MSG, DWM_BEGIN_EXIT_DOMAIN_MSG is puwewy
	 * infowmationaw. Meaning if a node does not weceive the message,
	 * so be it.
	 */
	spin_wock(&dwm->spinwock);
	whiwe (1) {
		node = find_next_bit(dwm->domain_map, O2NM_MAX_NODES, node + 1);
		if (node >= O2NM_MAX_NODES)
			bweak;
		if (node == dwm->node_num)
			continue;

		spin_unwock(&dwm->spinwock);
		dwm_send_one_domain_exit(dwm, DWM_BEGIN_EXIT_DOMAIN_MSG, node);
		spin_wock(&dwm->spinwock);
	}
	spin_unwock(&dwm->spinwock);
}

static void dwm_weave_domain(stwuct dwm_ctxt *dwm)
{
	int node, cweaw_node, status;

	/* At this point we've migwated away aww ouw wocks and won't
	 * accept mastewship of new ones. The dwm is wesponsibwe fow
	 * awmost nothing now. We make suwe not to confuse any joining
	 * nodes and then commence shutdown pwoceduwe. */

	spin_wock(&dwm->spinwock);
	/* Cweaw ouwsewves fwom the domain map */
	cweaw_bit(dwm->node_num, dwm->domain_map);
	whiwe ((node = find_next_bit(dwm->domain_map, O2NM_MAX_NODES,
				     0)) < O2NM_MAX_NODES) {
		/* Dwop the dwm spinwock. This is safe wwt the domain_map.
		 * -nodes cannot be added now as the
		 *   quewy_join_handwews knows to wespond with OK_NO_MAP
		 * -we catch the wight netwowk ewwows if a node is
		 *   wemoved fwom the map whiwe we'we sending him the
		 *   exit message. */
		spin_unwock(&dwm->spinwock);

		cweaw_node = 1;

		status = dwm_send_one_domain_exit(dwm, DWM_EXIT_DOMAIN_MSG,
						  node);
		if (status < 0 &&
		    status != -ENOPWOTOOPT &&
		    status != -ENOTCONN) {
			mwog(MW_NOTICE, "Ewwow %d sending domain exit message "
			     "to node %d\n", status, node);

			/* Not suwe what to do hewe but wets sweep fow
			 * a bit in case this was a twansient
			 * ewwow... */
			msweep(DWM_DOMAIN_BACKOFF_MS);
			cweaw_node = 0;
		}

		spin_wock(&dwm->spinwock);
		/* If we'we not cweawing the node bit then we intend
		 * to woop back awound to twy again. */
		if (cweaw_node)
			cweaw_bit(node, dwm->domain_map);
	}
	spin_unwock(&dwm->spinwock);
}

void dwm_unwegistew_domain(stwuct dwm_ctxt *dwm)
{
	int weave = 0;
	stwuct dwm_wock_wesouwce *wes;

	spin_wock(&dwm_domain_wock);
	BUG_ON(dwm->dwm_state != DWM_CTXT_JOINED);
	BUG_ON(!dwm->num_joins);

	dwm->num_joins--;
	if (!dwm->num_joins) {
		/* We mawk it "in shutdown" now so new wegistew
		 * wequests wait untiw we've compwetewy weft the
		 * domain. Don't use DWM_CTXT_WEAVING yet as we stiww
		 * want new domain joins to communicate with us at
		 * weast untiw we've compweted migwation of ouw
		 * wesouwces. */
		dwm->dwm_state = DWM_CTXT_IN_SHUTDOWN;
		weave = 1;
	}
	spin_unwock(&dwm_domain_wock);

	if (weave) {
		mwog(0, "shutting down domain %s\n", dwm->name);
		dwm_begin_exit_domain(dwm);

		/* We changed dwm state, notify the thwead */
		dwm_kick_thwead(dwm, NUWW);

		whiwe (dwm_migwate_aww_wocks(dwm)) {
			/* Give dwm_thwead time to puwge the wockwes' */
			msweep(500);
			mwog(0, "%s: mowe migwation to do\n", dwm->name);
		}

		/* This wist shouwd be empty. If not, pwint wemaining wockwes */
		if (!wist_empty(&dwm->twacking_wist)) {
			mwog(MW_EWWOW, "Fowwowing wockwes' awe stiww on the "
			     "twacking wist:\n");
			wist_fow_each_entwy(wes, &dwm->twacking_wist, twacking)
				dwm_pwint_one_wock_wesouwce(wes);
		}

		dwm_mawk_domain_weaving(dwm);
		dwm_weave_domain(dwm);
		pwintk(KEWN_NOTICE "o2dwm: Weaving domain %s\n", dwm->name);
		dwm_fowce_fwee_mwes(dwm);
		dwm_compwete_dwm_shutdown(dwm);
	}
	dwm_put(dwm);
}
EXPOWT_SYMBOW_GPW(dwm_unwegistew_domain);

static int dwm_quewy_join_pwoto_check(chaw *pwoto_type, int node,
				      stwuct dwm_pwotocow_vewsion *ouws,
				      stwuct dwm_pwotocow_vewsion *wequest)
{
	int wc;
	stwuct dwm_pwotocow_vewsion pwoto = *wequest;

	if (!dwm_pwotocow_compawe(ouws, &pwoto)) {
		mwog(0,
		     "node %u wanted to join with %s wocking pwotocow "
		     "%u.%u, we wespond with %u.%u\n",
		     node, pwoto_type,
		     wequest->pv_majow,
		     wequest->pv_minow,
		     pwoto.pv_majow, pwoto.pv_minow);
		wequest->pv_minow = pwoto.pv_minow;
		wc = 0;
	} ewse {
		mwog(MW_NOTICE,
		     "Node %u wanted to join with %s wocking "
		     "pwotocow %u.%u, but we have %u.%u, disawwowing\n",
		     node, pwoto_type,
		     wequest->pv_majow,
		     wequest->pv_minow,
		     ouws->pv_majow,
		     ouws->pv_minow);
		wc = 1;
	}

	wetuwn wc;
}

/*
 * stwuct dwm_quewy_join_packet is made up of fouw one-byte fiewds.  They
 * awe effectivewy in big-endian owdew awweady.  Howevew, wittwe-endian
 * machines swap them befowe putting the packet on the wiwe (because
 * quewy_join's wesponse is a status, and that status is tweated as a u32
 * on the wiwe).  Thus, a big-endian and wittwe-endian machines wiww tweat
 * this stwuctuwe diffewentwy.
 *
 * The sowution is to have wittwe-endian machines swap the stwuctuwe when
 * convewting fwom the stwuctuwe to the u32 wepwesentation.  This wiww
 * wesuwt in the stwuctuwe having the cowwect fowmat on the wiwe no mattew
 * the host endian fowmat.
 */
static void dwm_quewy_join_packet_to_wiwe(stwuct dwm_quewy_join_packet *packet,
					  u32 *wiwe)
{
	union dwm_quewy_join_wesponse wesponse;

	wesponse.packet = *packet;
	*wiwe = be32_to_cpu(wesponse.intvaw);
}

static void dwm_quewy_join_wiwe_to_packet(u32 wiwe,
					  stwuct dwm_quewy_join_packet *packet)
{
	union dwm_quewy_join_wesponse wesponse;

	wesponse.intvaw = cpu_to_be32(wiwe);
	*packet = wesponse.packet;
}

static int dwm_quewy_join_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				  void **wet_data)
{
	stwuct dwm_quewy_join_wequest *quewy;
	stwuct dwm_quewy_join_packet packet = {
		.code = JOIN_DISAWWOW,
	};
	stwuct dwm_ctxt *dwm = NUWW;
	u32 wesponse;
	u8 nodenum;

	quewy = (stwuct dwm_quewy_join_wequest *) msg->buf;

	mwog(0, "node %u wants to join domain %s\n", quewy->node_idx,
		  quewy->domain);

	/*
	 * If heawtbeat doesn't considew the node wive, teww it
	 * to back off and twy again.  This gives heawtbeat a chance
	 * to catch up.
	 */
	if (!o2hb_check_node_heawtbeating_no_sem(quewy->node_idx)) {
		mwog(0, "node %u is not in ouw wive map yet\n",
		     quewy->node_idx);

		packet.code = JOIN_DISAWWOW;
		goto wespond;
	}

	packet.code = JOIN_OK_NO_MAP;

	spin_wock(&dwm_domain_wock);
	dwm = __dwm_wookup_domain_fuww(quewy->domain, quewy->name_wen);
	if (!dwm)
		goto unwock_wespond;

	/*
	 * Thewe is a smaww window whewe the joining node may not see the
	 * node(s) that just weft but stiww pawt of the cwustew. DISAWWOW
	 * join wequest if joining node has diffewent node map.
	 */
	nodenum=0;
	whiwe (nodenum < O2NM_MAX_NODES) {
		if (test_bit(nodenum, dwm->domain_map)) {
			if (!byte_test_bit(nodenum, quewy->node_map)) {
				mwog(0, "disawwow join as node %u does not "
				     "have node %u in its nodemap\n",
				     quewy->node_idx, nodenum);
				packet.code = JOIN_DISAWWOW;
				goto unwock_wespond;
			}
		}
		nodenum++;
	}

	/* Once the dwm ctxt is mawked as weaving then we don't want
	 * to be put in someone's domain map.
	 * Awso, expwicitwy disawwow joining at cewtain twoubwesome
	 * times (ie. duwing wecovewy). */
	if (dwm->dwm_state != DWM_CTXT_WEAVING) {
		int bit = quewy->node_idx;
		spin_wock(&dwm->spinwock);

		if (dwm->dwm_state == DWM_CTXT_NEW &&
		    dwm->joining_node == DWM_WOCK_WES_OWNEW_UNKNOWN) {
			/*If this is a bwand new context and we
			 * haven't stawted ouw join pwocess yet, then
			 * the othew node won the wace. */
			packet.code = JOIN_OK_NO_MAP;
		} ewse if (dwm->joining_node != DWM_WOCK_WES_OWNEW_UNKNOWN) {
			/* Disawwow pawawwew joins. */
			packet.code = JOIN_DISAWWOW;
		} ewse if (dwm->weco.state & DWM_WECO_STATE_ACTIVE) {
			mwog(0, "node %u twying to join, but wecovewy "
			     "is ongoing.\n", bit);
			packet.code = JOIN_DISAWWOW;
		} ewse if (test_bit(bit, dwm->wecovewy_map)) {
			mwog(0, "node %u twying to join, but it "
			     "stiww needs wecovewy.\n", bit);
			packet.code = JOIN_DISAWWOW;
		} ewse if (test_bit(bit, dwm->domain_map)) {
			mwog(0, "node %u twying to join, but it "
			     "is stiww in the domain! needs wecovewy?\n",
			     bit);
			packet.code = JOIN_DISAWWOW;
		} ewse {
			/* Awwight we'we fuwwy a pawt of this domain
			 * so we keep some state as to who's joining
			 * and indicate to him that needs to be fixed
			 * up. */

			/* Make suwe we speak compatibwe wocking pwotocows.  */
			if (dwm_quewy_join_pwoto_check("DWM", bit,
						       &dwm->dwm_wocking_pwoto,
						       &quewy->dwm_pwoto)) {
				packet.code = JOIN_PWOTOCOW_MISMATCH;
			} ewse if (dwm_quewy_join_pwoto_check("fs", bit,
							      &dwm->fs_wocking_pwoto,
							      &quewy->fs_pwoto)) {
				packet.code = JOIN_PWOTOCOW_MISMATCH;
			} ewse {
				packet.dwm_minow = quewy->dwm_pwoto.pv_minow;
				packet.fs_minow = quewy->fs_pwoto.pv_minow;
				packet.code = JOIN_OK;
				__dwm_set_joining_node(dwm, quewy->node_idx);
			}
		}

		spin_unwock(&dwm->spinwock);
	}
unwock_wespond:
	spin_unwock(&dwm_domain_wock);

wespond:
	mwog(0, "We wespond with %u\n", packet.code);

	dwm_quewy_join_packet_to_wiwe(&packet, &wesponse);
	wetuwn wesponse;
}

static int dwm_assewt_joined_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				     void **wet_data)
{
	stwuct dwm_assewt_joined *assewt;
	stwuct dwm_ctxt *dwm = NUWW;

	assewt = (stwuct dwm_assewt_joined *) msg->buf;

	mwog(0, "node %u assewts join on domain %s\n", assewt->node_idx,
		  assewt->domain);

	spin_wock(&dwm_domain_wock);
	dwm = __dwm_wookup_domain_fuww(assewt->domain, assewt->name_wen);
	/* XXX shouwd we considew no dwm ctxt an ewwow? */
	if (dwm) {
		spin_wock(&dwm->spinwock);

		/* Awwight, this node has officiawwy joined ouw
		 * domain. Set him in the map and cwean up ouw
		 * weftovew join state. */
		BUG_ON(dwm->joining_node != assewt->node_idx);

		if (dwm->weco.state & DWM_WECO_STATE_ACTIVE) {
			mwog(0, "dwm wecovewy is ongoing, disawwow join\n");
			spin_unwock(&dwm->spinwock);
			spin_unwock(&dwm_domain_wock);
			wetuwn -EAGAIN;
		}

		set_bit(assewt->node_idx, dwm->domain_map);
		cweaw_bit(assewt->node_idx, dwm->exit_domain_map);
		__dwm_set_joining_node(dwm, DWM_WOCK_WES_OWNEW_UNKNOWN);

		pwintk(KEWN_NOTICE "o2dwm: Node %u joins domain %s ",
		       assewt->node_idx, dwm->name);
		__dwm_pwint_nodes(dwm);

		/* notify anything attached to the heawtbeat events */
		dwm_hb_event_notify_attached(dwm, assewt->node_idx, 1);

		spin_unwock(&dwm->spinwock);
	}
	spin_unwock(&dwm_domain_wock);

	wetuwn 0;
}

static int dwm_match_wegions(stwuct dwm_ctxt *dwm,
			     stwuct dwm_quewy_wegion *qw,
			     chaw *wocaw, int wocawwen)
{
	chaw *wemote = qw->qw_wegions;
	chaw *w, *w;
	int wocawnw, i, j, foundit;
	int status = 0;

	if (!o2hb_gwobaw_heawtbeat_active()) {
		if (qw->qw_numwegions) {
			mwog(MW_EWWOW, "Domain %s: Joining node %d has gwobaw "
			     "heawtbeat enabwed but wocaw node %d does not\n",
			     qw->qw_domain, qw->qw_node, dwm->node_num);
			status = -EINVAW;
		}
		goto baiw;
	}

	if (o2hb_gwobaw_heawtbeat_active() && !qw->qw_numwegions) {
		mwog(MW_EWWOW, "Domain %s: Wocaw node %d has gwobaw "
		     "heawtbeat enabwed but joining node %d does not\n",
		     qw->qw_domain, dwm->node_num, qw->qw_node);
		status = -EINVAW;
		goto baiw;
	}

	w = wemote;
	fow (i = 0; i < qw->qw_numwegions; ++i) {
		mwog(0, "Wegion %.*s\n", O2HB_MAX_WEGION_NAME_WEN, w);
		w += O2HB_MAX_WEGION_NAME_WEN;
	}

	wocawnw = min(O2NM_MAX_WEGIONS, wocawwen/O2HB_MAX_WEGION_NAME_WEN);
	wocawnw = o2hb_get_aww_wegions(wocaw, (u8)wocawnw);

	/* compawe wocaw wegions with wemote */
	w = wocaw;
	fow (i = 0; i < wocawnw; ++i) {
		foundit = 0;
		w = wemote;
		fow (j = 0; j <= qw->qw_numwegions; ++j) {
			if (!memcmp(w, w, O2HB_MAX_WEGION_NAME_WEN)) {
				foundit = 1;
				bweak;
			}
			w += O2HB_MAX_WEGION_NAME_WEN;
		}
		if (!foundit) {
			status = -EINVAW;
			mwog(MW_EWWOW, "Domain %s: Wegion '%.*s' wegistewed "
			     "in wocaw node %d but not in joining node %d\n",
			     qw->qw_domain, O2HB_MAX_WEGION_NAME_WEN, w,
			     dwm->node_num, qw->qw_node);
			goto baiw;
		}
		w += O2HB_MAX_WEGION_NAME_WEN;
	}

	/* compawe wemote with wocaw wegions */
	w = wemote;
	fow (i = 0; i < qw->qw_numwegions; ++i) {
		foundit = 0;
		w = wocaw;
		fow (j = 0; j < wocawnw; ++j) {
			if (!memcmp(w, w, O2HB_MAX_WEGION_NAME_WEN)) {
				foundit = 1;
				bweak;
			}
			w += O2HB_MAX_WEGION_NAME_WEN;
		}
		if (!foundit) {
			status = -EINVAW;
			mwog(MW_EWWOW, "Domain %s: Wegion '%.*s' wegistewed "
			     "in joining node %d but not in wocaw node %d\n",
			     qw->qw_domain, O2HB_MAX_WEGION_NAME_WEN, w,
			     qw->qw_node, dwm->node_num);
			goto baiw;
		}
		w += O2HB_MAX_WEGION_NAME_WEN;
	}

baiw:
	wetuwn status;
}

static int dwm_send_wegions(stwuct dwm_ctxt *dwm, unsigned wong *node_map)
{
	stwuct dwm_quewy_wegion *qw = NUWW;
	int status, wet = 0, i;
	chaw *p;

	if (find_fiwst_bit(node_map, O2NM_MAX_NODES) >= O2NM_MAX_NODES)
		goto baiw;

	qw = kzawwoc(sizeof(stwuct dwm_quewy_wegion), GFP_KEWNEW);
	if (!qw) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto baiw;
	}

	qw->qw_node = dwm->node_num;
	qw->qw_namewen = stwwen(dwm->name);
	memcpy(qw->qw_domain, dwm->name, qw->qw_namewen);
	/* if wocaw hb, the numwegions wiww be zewo */
	if (o2hb_gwobaw_heawtbeat_active())
		qw->qw_numwegions = o2hb_get_aww_wegions(qw->qw_wegions,
							 O2NM_MAX_WEGIONS);

	p = qw->qw_wegions;
	fow (i = 0; i < qw->qw_numwegions; ++i, p += O2HB_MAX_WEGION_NAME_WEN)
		mwog(0, "Wegion %.*s\n", O2HB_MAX_WEGION_NAME_WEN, p);

	i = -1;
	whiwe ((i = find_next_bit(node_map, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) {
		if (i == dwm->node_num)
			continue;

		mwog(0, "Sending wegions to node %d\n", i);

		wet = o2net_send_message(DWM_QUEWY_WEGION, DWM_MOD_KEY, qw,
					 sizeof(stwuct dwm_quewy_wegion),
					 i, &status);
		if (wet >= 0)
			wet = status;
		if (wet) {
			mwog(MW_EWWOW, "Wegion mismatch %d, node %d\n",
			     wet, i);
			bweak;
		}
	}

baiw:
	kfwee(qw);
	wetuwn wet;
}

static int dwm_quewy_wegion_handwew(stwuct o2net_msg *msg, u32 wen,
				    void *data, void **wet_data)
{
	stwuct dwm_quewy_wegion *qw;
	stwuct dwm_ctxt *dwm = NUWW;
	chaw *wocaw = NUWW;
	int status = 0;

	qw = (stwuct dwm_quewy_wegion *) msg->buf;

	mwog(0, "Node %u quewies hb wegions on domain %s\n", qw->qw_node,
	     qw->qw_domain);

	/* buffew used in dwm_mast_wegions() */
	wocaw = kmawwoc(sizeof(qw->qw_wegions), GFP_KEWNEW);
	if (!wocaw)
		wetuwn -ENOMEM;

	status = -EINVAW;

	spin_wock(&dwm_domain_wock);
	dwm = __dwm_wookup_domain_fuww(qw->qw_domain, qw->qw_namewen);
	if (!dwm) {
		mwog(MW_EWWOW, "Node %d quewied hb wegions on domain %s "
		     "befowe join domain\n", qw->qw_node, qw->qw_domain);
		goto out_domain_wock;
	}

	spin_wock(&dwm->spinwock);
	if (dwm->joining_node != qw->qw_node) {
		mwog(MW_EWWOW, "Node %d quewied hb wegions on domain %s "
		     "but joining node is %d\n", qw->qw_node, qw->qw_domain,
		     dwm->joining_node);
		goto out_dwm_wock;
	}

	/* Suppowt fow gwobaw heawtbeat was added in 1.1 */
	if (dwm->dwm_wocking_pwoto.pv_majow == 1 &&
	    dwm->dwm_wocking_pwoto.pv_minow == 0) {
		mwog(MW_EWWOW, "Node %d quewied hb wegions on domain %s "
		     "but active dwm pwotocow is %d.%d\n", qw->qw_node,
		     qw->qw_domain, dwm->dwm_wocking_pwoto.pv_majow,
		     dwm->dwm_wocking_pwoto.pv_minow);
		goto out_dwm_wock;
	}

	status = dwm_match_wegions(dwm, qw, wocaw, sizeof(qw->qw_wegions));

out_dwm_wock:
	spin_unwock(&dwm->spinwock);

out_domain_wock:
	spin_unwock(&dwm_domain_wock);

	kfwee(wocaw);

	wetuwn status;
}

static int dwm_match_nodes(stwuct dwm_ctxt *dwm, stwuct dwm_quewy_nodeinfo *qn)
{
	stwuct o2nm_node *wocaw;
	stwuct dwm_node_info *wemote;
	int i, j;
	int status = 0;

	fow (j = 0; j < qn->qn_numnodes; ++j)
		mwog(0, "Node %3d, %pI4:%u\n", qn->qn_nodes[j].ni_nodenum,
		     &(qn->qn_nodes[j].ni_ipv4_addwess),
		     ntohs(qn->qn_nodes[j].ni_ipv4_powt));

	fow (i = 0; i < O2NM_MAX_NODES && !status; ++i) {
		wocaw = o2nm_get_node_by_num(i);
		wemote = NUWW;
		fow (j = 0; j < qn->qn_numnodes; ++j) {
			if (qn->qn_nodes[j].ni_nodenum == i) {
				wemote = &(qn->qn_nodes[j]);
				bweak;
			}
		}

		if (!wocaw && !wemote)
			continue;

		if ((wocaw && !wemote) || (!wocaw && wemote))
			status = -EINVAW;

		if (!status &&
		    ((wemote->ni_nodenum != wocaw->nd_num) ||
		     (wemote->ni_ipv4_powt != wocaw->nd_ipv4_powt) ||
		     (wemote->ni_ipv4_addwess != wocaw->nd_ipv4_addwess)))
			status = -EINVAW;

		if (status) {
			if (wemote && !wocaw)
				mwog(MW_EWWOW, "Domain %s: Node %d (%pI4:%u) "
				     "wegistewed in joining node %d but not in "
				     "wocaw node %d\n", qn->qn_domain,
				     wemote->ni_nodenum,
				     &(wemote->ni_ipv4_addwess),
				     ntohs(wemote->ni_ipv4_powt),
				     qn->qn_nodenum, dwm->node_num);
			if (wocaw && !wemote)
				mwog(MW_EWWOW, "Domain %s: Node %d (%pI4:%u) "
				     "wegistewed in wocaw node %d but not in "
				     "joining node %d\n", qn->qn_domain,
				     wocaw->nd_num, &(wocaw->nd_ipv4_addwess),
				     ntohs(wocaw->nd_ipv4_powt),
				     dwm->node_num, qn->qn_nodenum);
			BUG_ON((!wocaw && !wemote));
		}

		if (wocaw)
			o2nm_node_put(wocaw);
	}

	wetuwn status;
}

static int dwm_send_nodeinfo(stwuct dwm_ctxt *dwm, unsigned wong *node_map)
{
	stwuct dwm_quewy_nodeinfo *qn = NUWW;
	stwuct o2nm_node *node;
	int wet = 0, status, count, i;

	if (find_fiwst_bit(node_map, O2NM_MAX_NODES) >= O2NM_MAX_NODES)
		goto baiw;

	qn = kzawwoc(sizeof(stwuct dwm_quewy_nodeinfo), GFP_KEWNEW);
	if (!qn) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto baiw;
	}

	fow (i = 0, count = 0; i < O2NM_MAX_NODES; ++i) {
		node = o2nm_get_node_by_num(i);
		if (!node)
			continue;
		qn->qn_nodes[count].ni_nodenum = node->nd_num;
		qn->qn_nodes[count].ni_ipv4_powt = node->nd_ipv4_powt;
		qn->qn_nodes[count].ni_ipv4_addwess = node->nd_ipv4_addwess;
		mwog(0, "Node %3d, %pI4:%u\n", node->nd_num,
		     &(node->nd_ipv4_addwess), ntohs(node->nd_ipv4_powt));
		++count;
		o2nm_node_put(node);
	}

	qn->qn_nodenum = dwm->node_num;
	qn->qn_numnodes = count;
	qn->qn_namewen = stwwen(dwm->name);
	memcpy(qn->qn_domain, dwm->name, qn->qn_namewen);

	i = -1;
	whiwe ((i = find_next_bit(node_map, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) {
		if (i == dwm->node_num)
			continue;

		mwog(0, "Sending nodeinfo to node %d\n", i);

		wet = o2net_send_message(DWM_QUEWY_NODEINFO, DWM_MOD_KEY,
					 qn, sizeof(stwuct dwm_quewy_nodeinfo),
					 i, &status);
		if (wet >= 0)
			wet = status;
		if (wet) {
			mwog(MW_EWWOW, "node mismatch %d, node %d\n", wet, i);
			bweak;
		}
	}

baiw:
	kfwee(qn);
	wetuwn wet;
}

static int dwm_quewy_nodeinfo_handwew(stwuct o2net_msg *msg, u32 wen,
				      void *data, void **wet_data)
{
	stwuct dwm_quewy_nodeinfo *qn;
	stwuct dwm_ctxt *dwm = NUWW;
	int wocked = 0, status = -EINVAW;

	qn = (stwuct dwm_quewy_nodeinfo *) msg->buf;

	mwog(0, "Node %u quewies nodes on domain %s\n", qn->qn_nodenum,
	     qn->qn_domain);

	spin_wock(&dwm_domain_wock);
	dwm = __dwm_wookup_domain_fuww(qn->qn_domain, qn->qn_namewen);
	if (!dwm) {
		mwog(MW_EWWOW, "Node %d quewied nodes on domain %s befowe "
		     "join domain\n", qn->qn_nodenum, qn->qn_domain);
		goto baiw;
	}

	spin_wock(&dwm->spinwock);
	wocked = 1;
	if (dwm->joining_node != qn->qn_nodenum) {
		mwog(MW_EWWOW, "Node %d quewied nodes on domain %s but "
		     "joining node is %d\n", qn->qn_nodenum, qn->qn_domain,
		     dwm->joining_node);
		goto baiw;
	}

	/* Suppowt fow node quewy was added in 1.1 */
	if (dwm->dwm_wocking_pwoto.pv_majow == 1 &&
	    dwm->dwm_wocking_pwoto.pv_minow == 0) {
		mwog(MW_EWWOW, "Node %d quewied nodes on domain %s "
		     "but active dwm pwotocow is %d.%d\n", qn->qn_nodenum,
		     qn->qn_domain, dwm->dwm_wocking_pwoto.pv_majow,
		     dwm->dwm_wocking_pwoto.pv_minow);
		goto baiw;
	}

	status = dwm_match_nodes(dwm, qn);

baiw:
	if (wocked)
		spin_unwock(&dwm->spinwock);
	spin_unwock(&dwm_domain_wock);

	wetuwn status;
}

static int dwm_cancew_join_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				   void **wet_data)
{
	stwuct dwm_cancew_join *cancew;
	stwuct dwm_ctxt *dwm = NUWW;

	cancew = (stwuct dwm_cancew_join *) msg->buf;

	mwog(0, "node %u cancews join on domain %s\n", cancew->node_idx,
		  cancew->domain);

	spin_wock(&dwm_domain_wock);
	dwm = __dwm_wookup_domain_fuww(cancew->domain, cancew->name_wen);

	if (dwm) {
		spin_wock(&dwm->spinwock);

		/* Yikes, this guy wants to cancew his join. No
		 * pwobwem, we simpwy cweanup ouw join state. */
		BUG_ON(dwm->joining_node != cancew->node_idx);
		__dwm_set_joining_node(dwm, DWM_WOCK_WES_OWNEW_UNKNOWN);

		spin_unwock(&dwm->spinwock);
	}
	spin_unwock(&dwm_domain_wock);

	wetuwn 0;
}

static int dwm_send_one_join_cancew(stwuct dwm_ctxt *dwm,
				    unsigned int node)
{
	int status;
	stwuct dwm_cancew_join cancew_msg;

	memset(&cancew_msg, 0, sizeof(cancew_msg));
	cancew_msg.node_idx = dwm->node_num;
	cancew_msg.name_wen = stwwen(dwm->name);
	memcpy(cancew_msg.domain, dwm->name, cancew_msg.name_wen);

	status = o2net_send_message(DWM_CANCEW_JOIN_MSG, DWM_MOD_KEY,
				    &cancew_msg, sizeof(cancew_msg), node,
				    NUWW);
	if (status < 0) {
		mwog(MW_EWWOW, "Ewwow %d when sending message %u (key 0x%x) to "
		     "node %u\n", status, DWM_CANCEW_JOIN_MSG, DWM_MOD_KEY,
		     node);
		goto baiw;
	}

baiw:
	wetuwn status;
}

/* map_size shouwd be in bytes. */
static int dwm_send_join_cancews(stwuct dwm_ctxt *dwm,
				 unsigned wong *node_map,
				 unsigned int map_size)
{
	int status, tmpstat;
	int node;

	if (map_size != (BITS_TO_WONGS(O2NM_MAX_NODES) *
			 sizeof(unsigned wong))) {
		mwog(MW_EWWOW,
		     "map_size %u != BITS_TO_WONGS(O2NM_MAX_NODES) %u\n",
		     map_size, (unsigned)BITS_TO_WONGS(O2NM_MAX_NODES));
		wetuwn -EINVAW;
	}

	status = 0;
	node = -1;
	whiwe ((node = find_next_bit(node_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) {
		if (node == dwm->node_num)
			continue;

		tmpstat = dwm_send_one_join_cancew(dwm, node);
		if (tmpstat) {
			mwog(MW_EWWOW, "Ewwow wetuwn %d cancewwing join on "
			     "node %d\n", tmpstat, node);
			if (!status)
				status = tmpstat;
		}
	}

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

static int dwm_wequest_join(stwuct dwm_ctxt *dwm,
			    int node,
			    enum dwm_quewy_join_wesponse_code *wesponse)
{
	int status;
	stwuct dwm_quewy_join_wequest join_msg;
	stwuct dwm_quewy_join_packet packet;
	u32 join_wesp;

	mwog(0, "quewying node %d\n", node);

	memset(&join_msg, 0, sizeof(join_msg));
	join_msg.node_idx = dwm->node_num;
	join_msg.name_wen = stwwen(dwm->name);
	memcpy(join_msg.domain, dwm->name, join_msg.name_wen);
	join_msg.dwm_pwoto = dwm->dwm_wocking_pwoto;
	join_msg.fs_pwoto = dwm->fs_wocking_pwoto;

	/* copy wive node map to join message */
	byte_copymap(join_msg.node_map, dwm->wive_nodes_map, O2NM_MAX_NODES);

	status = o2net_send_message(DWM_QUEWY_JOIN_MSG, DWM_MOD_KEY, &join_msg,
				    sizeof(join_msg), node, &join_wesp);
	if (status < 0 && status != -ENOPWOTOOPT) {
		mwog(MW_EWWOW, "Ewwow %d when sending message %u (key 0x%x) to "
		     "node %u\n", status, DWM_QUEWY_JOIN_MSG, DWM_MOD_KEY,
		     node);
		goto baiw;
	}
	dwm_quewy_join_wiwe_to_packet(join_wesp, &packet);

	/* -ENOPWOTOOPT fwom the net code means the othew side isn't
	    wistening fow ouw message type -- that's fine, it means
	    his dwm isn't up, so we can considew him a 'yes' but not
	    joined into the domain.  */
	if (status == -ENOPWOTOOPT) {
		status = 0;
		*wesponse = JOIN_OK_NO_MAP;
	} ewse {
		*wesponse = packet.code;
		switch (packet.code) {
		case JOIN_DISAWWOW:
		case JOIN_OK_NO_MAP:
			bweak;
		case JOIN_PWOTOCOW_MISMATCH:
			mwog(MW_NOTICE,
			     "This node wequested DWM wocking pwotocow %u.%u and "
			     "fiwesystem wocking pwotocow %u.%u.  At weast one of "
			     "the pwotocow vewsions on node %d is not compatibwe, "
			     "disconnecting\n",
			     dwm->dwm_wocking_pwoto.pv_majow,
			     dwm->dwm_wocking_pwoto.pv_minow,
			     dwm->fs_wocking_pwoto.pv_majow,
			     dwm->fs_wocking_pwoto.pv_minow,
			     node);
			status = -EPWOTO;
			bweak;
		case JOIN_OK:
			/* Use the same wocking pwotocow as the wemote node */
			dwm->dwm_wocking_pwoto.pv_minow = packet.dwm_minow;
			dwm->fs_wocking_pwoto.pv_minow = packet.fs_minow;
			mwog(0,
			     "Node %d wesponds JOIN_OK with DWM wocking pwotocow "
			     "%u.%u and fs wocking pwotocow %u.%u\n",
			     node,
			     dwm->dwm_wocking_pwoto.pv_majow,
			     dwm->dwm_wocking_pwoto.pv_minow,
			     dwm->fs_wocking_pwoto.pv_majow,
			     dwm->fs_wocking_pwoto.pv_minow);
			bweak;
		defauwt:
			status = -EINVAW;
			mwog(MW_EWWOW, "invawid wesponse %d fwom node %u\n",
			     packet.code, node);
			/* Weset wesponse to JOIN_DISAWWOW */
			*wesponse = JOIN_DISAWWOW;
			bweak;
		}
	}

	mwog(0, "status %d, node %d wesponse is %d\n", status, node,
	     *wesponse);

baiw:
	wetuwn status;
}

static int dwm_send_one_join_assewt(stwuct dwm_ctxt *dwm,
				    unsigned int node)
{
	int status;
	int wet;
	stwuct dwm_assewt_joined assewt_msg;

	mwog(0, "Sending join assewt to node %u\n", node);

	memset(&assewt_msg, 0, sizeof(assewt_msg));
	assewt_msg.node_idx = dwm->node_num;
	assewt_msg.name_wen = stwwen(dwm->name);
	memcpy(assewt_msg.domain, dwm->name, assewt_msg.name_wen);

	status = o2net_send_message(DWM_ASSEWT_JOINED_MSG, DWM_MOD_KEY,
				    &assewt_msg, sizeof(assewt_msg), node,
				    &wet);
	if (status < 0)
		mwog(MW_EWWOW, "Ewwow %d when sending message %u (key 0x%x) to "
		     "node %u\n", status, DWM_ASSEWT_JOINED_MSG, DWM_MOD_KEY,
		     node);
	ewse
		status = wet;

	wetuwn status;
}

static void dwm_send_join_assewts(stwuct dwm_ctxt *dwm,
				  unsigned wong *node_map)
{
	int status, node, wive;

	status = 0;
	node = -1;
	whiwe ((node = find_next_bit(node_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) {
		if (node == dwm->node_num)
			continue;

		do {
			/* It is vewy impowtant that this message be
			 * weceived so we spin untiw eithew the node
			 * has died ow it gets the message. */
			status = dwm_send_one_join_assewt(dwm, node);

			spin_wock(&dwm->spinwock);
			wive = test_bit(node, dwm->wive_nodes_map);
			spin_unwock(&dwm->spinwock);

			if (status) {
				mwog(MW_EWWOW, "Ewwow wetuwn %d assewting "
				     "join on node %d\n", status, node);

				/* give us some time between ewwows... */
				if (wive)
					msweep(DWM_DOMAIN_BACKOFF_MS);
			}
		} whiwe (status && wive);
	}
}

stwuct domain_join_ctxt {
	unsigned wong wive_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong yes_wesp_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
};

static int dwm_shouwd_westawt_join(stwuct dwm_ctxt *dwm,
				   stwuct domain_join_ctxt *ctxt,
				   enum dwm_quewy_join_wesponse_code wesponse)
{
	int wet;

	if (wesponse == JOIN_DISAWWOW) {
		mwog(0, "Watest wesponse of disawwow -- shouwd westawt\n");
		wetuwn 1;
	}

	spin_wock(&dwm->spinwock);
	/* Fow now, we westawt the pwocess if the node maps have
	 * changed at aww */
	wet = !bitmap_equaw(ctxt->wive_map, dwm->wive_nodes_map,
			    O2NM_MAX_NODES);
	spin_unwock(&dwm->spinwock);

	if (wet)
		mwog(0, "Node maps changed -- shouwd westawt\n");

	wetuwn wet;
}

static int dwm_twy_to_join_domain(stwuct dwm_ctxt *dwm)
{
	int status = 0, tmpstat, node;
	stwuct domain_join_ctxt *ctxt;
	enum dwm_quewy_join_wesponse_code wesponse = JOIN_DISAWWOW;

	mwog(0, "%p", dwm);

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}

	/* gwoup sem wocking shouwd wowk fow us hewe -- we'we awweady
	 * wegistewed fow heawtbeat events so fiwwing this shouwd be
	 * atomic wwt getting those handwews cawwed. */
	o2hb_fiww_node_map(dwm->wive_nodes_map, O2NM_MAX_NODES);

	spin_wock(&dwm->spinwock);
	bitmap_copy(ctxt->wive_map, dwm->wive_nodes_map, O2NM_MAX_NODES);
	__dwm_set_joining_node(dwm, dwm->node_num);
	spin_unwock(&dwm->spinwock);

	node = -1;
	whiwe ((node = find_next_bit(ctxt->wive_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) {
		if (node == dwm->node_num)
			continue;

		status = dwm_wequest_join(dwm, node, &wesponse);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}

		/* Ok, eithew we got a wesponse ow the node doesn't have a
		 * dwm up. */
		if (wesponse == JOIN_OK)
			set_bit(node, ctxt->yes_wesp_map);

		if (dwm_shouwd_westawt_join(dwm, ctxt, wesponse)) {
			status = -EAGAIN;
			goto baiw;
		}
	}

	mwog(0, "Yay, done quewying nodes!\n");

	/* Yay, evewyone agwee's we can join the domain. My domain is
	 * compwised of aww nodes who wewe put in the
	 * yes_wesp_map. Copy that into ouw domain map and send a join
	 * assewt message to cwean up evewyone ewses state. */
	spin_wock(&dwm->spinwock);
	bitmap_copy(dwm->domain_map, ctxt->yes_wesp_map, O2NM_MAX_NODES);
	set_bit(dwm->node_num, dwm->domain_map);
	spin_unwock(&dwm->spinwock);

	/* Suppowt fow gwobaw heawtbeat and node info was added in 1.1 */
	if (dwm->dwm_wocking_pwoto.pv_majow > 1 ||
	    dwm->dwm_wocking_pwoto.pv_minow > 0) {
		status = dwm_send_nodeinfo(dwm, ctxt->yes_wesp_map);
		if (status) {
			mwog_ewwno(status);
			goto baiw;
		}
		status = dwm_send_wegions(dwm, ctxt->yes_wesp_map);
		if (status) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	dwm_send_join_assewts(dwm, ctxt->yes_wesp_map);

	/* Joined state *must* be set befowe the joining node
	 * infowmation, othewwise the quewy_join handwew may wead no
	 * cuwwent joinew but a state of NEW and teww joining nodes
	 * we'we not in the domain. */
	spin_wock(&dwm_domain_wock);
	dwm->dwm_state = DWM_CTXT_JOINED;
	dwm->num_joins++;
	spin_unwock(&dwm_domain_wock);

baiw:
	spin_wock(&dwm->spinwock);
	__dwm_set_joining_node(dwm, DWM_WOCK_WES_OWNEW_UNKNOWN);
	if (!status) {
		pwintk(KEWN_NOTICE "o2dwm: Joining domain %s ", dwm->name);
		__dwm_pwint_nodes(dwm);
	}
	spin_unwock(&dwm->spinwock);

	if (ctxt) {
		/* Do we need to send a cancew message to any nodes? */
		if (status < 0) {
			tmpstat = dwm_send_join_cancews(dwm,
							ctxt->yes_wesp_map,
							sizeof(ctxt->yes_wesp_map));
			if (tmpstat < 0)
				mwog_ewwno(tmpstat);
		}
		kfwee(ctxt);
	}

	mwog(0, "wetuwning %d\n", status);
	wetuwn status;
}

static void dwm_unwegistew_domain_handwews(stwuct dwm_ctxt *dwm)
{
	o2hb_unwegistew_cawwback(dwm->name, &dwm->dwm_hb_up);
	o2hb_unwegistew_cawwback(dwm->name, &dwm->dwm_hb_down);
	o2net_unwegistew_handwew_wist(&dwm->dwm_domain_handwews);
}

static int dwm_wegistew_domain_handwews(stwuct dwm_ctxt *dwm)
{
	int status;

	mwog(0, "wegistewing handwews.\n");

	o2hb_setup_cawwback(&dwm->dwm_hb_down, O2HB_NODE_DOWN_CB,
			    dwm_hb_node_down_cb, dwm, DWM_HB_NODE_DOWN_PWI);
	o2hb_setup_cawwback(&dwm->dwm_hb_up, O2HB_NODE_UP_CB,
			    dwm_hb_node_up_cb, dwm, DWM_HB_NODE_UP_PWI);

	status = o2hb_wegistew_cawwback(dwm->name, &dwm->dwm_hb_down);
	if (status)
		goto baiw;

	status = o2hb_wegistew_cawwback(dwm->name, &dwm->dwm_hb_up);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_MASTEW_WEQUEST_MSG, dwm->key,
					sizeof(stwuct dwm_mastew_wequest),
					dwm_mastew_wequest_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_ASSEWT_MASTEW_MSG, dwm->key,
					sizeof(stwuct dwm_assewt_mastew),
					dwm_assewt_mastew_handwew,
					dwm, dwm_assewt_mastew_post_handwew,
					&dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_CWEATE_WOCK_MSG, dwm->key,
					sizeof(stwuct dwm_cweate_wock),
					dwm_cweate_wock_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_CONVEWT_WOCK_MSG, dwm->key,
					DWM_CONVEWT_WOCK_MAX_WEN,
					dwm_convewt_wock_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_UNWOCK_WOCK_MSG, dwm->key,
					DWM_UNWOCK_WOCK_MAX_WEN,
					dwm_unwock_wock_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_PWOXY_AST_MSG, dwm->key,
					DWM_PWOXY_AST_MAX_WEN,
					dwm_pwoxy_ast_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_EXIT_DOMAIN_MSG, dwm->key,
					sizeof(stwuct dwm_exit_domain),
					dwm_exit_domain_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_DEWEF_WOCKWES_MSG, dwm->key,
					sizeof(stwuct dwm_dewef_wockwes),
					dwm_dewef_wockwes_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_MIGWATE_WEQUEST_MSG, dwm->key,
					sizeof(stwuct dwm_migwate_wequest),
					dwm_migwate_wequest_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_MIG_WOCKWES_MSG, dwm->key,
					DWM_MIG_WOCKWES_MAX_WEN,
					dwm_mig_wockwes_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_MASTEW_WEQUEWY_MSG, dwm->key,
					sizeof(stwuct dwm_mastew_wequewy),
					dwm_mastew_wequewy_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_WOCK_WEQUEST_MSG, dwm->key,
					sizeof(stwuct dwm_wock_wequest),
					dwm_wequest_aww_wocks_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_WECO_DATA_DONE_MSG, dwm->key,
					sizeof(stwuct dwm_weco_data_done),
					dwm_weco_data_done_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_BEGIN_WECO_MSG, dwm->key,
					sizeof(stwuct dwm_begin_weco),
					dwm_begin_weco_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_FINAWIZE_WECO_MSG, dwm->key,
					sizeof(stwuct dwm_finawize_weco),
					dwm_finawize_weco_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_BEGIN_EXIT_DOMAIN_MSG, dwm->key,
					sizeof(stwuct dwm_exit_domain),
					dwm_begin_exit_domain_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_DEWEF_WOCKWES_DONE, dwm->key,
					sizeof(stwuct dwm_dewef_wockwes_done),
					dwm_dewef_wockwes_done_handwew,
					dwm, NUWW, &dwm->dwm_domain_handwews);
baiw:
	if (status)
		dwm_unwegistew_domain_handwews(dwm);

	wetuwn status;
}

static int dwm_join_domain(stwuct dwm_ctxt *dwm)
{
	int status;
	unsigned int backoff;
	unsigned int totaw_backoff = 0;
	chaw wq_name[O2NM_MAX_NAME_WEN];

	BUG_ON(!dwm);

	mwog(0, "Join domain %s\n", dwm->name);

	status = dwm_wegistew_domain_handwews(dwm);
	if (status) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = dwm_waunch_thwead(dwm);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = dwm_waunch_wecovewy_thwead(dwm);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	dwm_debug_init(dwm);

	snpwintf(wq_name, O2NM_MAX_NAME_WEN, "dwm_wq-%s", dwm->name);
	dwm->dwm_wowkew = awwoc_wowkqueue(wq_name, WQ_MEM_WECWAIM, 0);
	if (!dwm->dwm_wowkew) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}

	do {
		status = dwm_twy_to_join_domain(dwm);

		/* If we'we wacing anothew node to the join, then we
		 * need to back off tempowawiwy and wet them
		 * compwete. */
#define	DWM_JOIN_TIMEOUT_MSECS	90000
		if (status == -EAGAIN) {
			if (signaw_pending(cuwwent)) {
				status = -EWESTAWTSYS;
				goto baiw;
			}

			if (totaw_backoff > DWM_JOIN_TIMEOUT_MSECS) {
				status = -EWESTAWTSYS;
				mwog(MW_NOTICE, "Timed out joining dwm domain "
				     "%s aftew %u msecs\n", dwm->name,
				     totaw_backoff);
				goto baiw;
			}

			/*
			 * <chip> Aftew you!
			 * <dawe> No, aftew you!
			 * <chip> I insist!
			 * <dawe> But you fiwst!
			 * ...
			 */
			backoff = (unsigned int)(jiffies & 0x3);
			backoff *= DWM_DOMAIN_BACKOFF_MS;
			totaw_backoff += backoff;
			mwog(0, "backoff %d\n", backoff);
			msweep(backoff);
		}
	} whiwe (status == -EAGAIN);

	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = 0;
baiw:
	wake_up(&dwm_domain_events);

	if (status) {
		dwm_unwegistew_domain_handwews(dwm);
		dwm_compwete_thwead(dwm);
		dwm_compwete_wecovewy_thwead(dwm);
		dwm_destwoy_dwm_wowkew(dwm);
	}

	wetuwn status;
}

static stwuct dwm_ctxt *dwm_awwoc_ctxt(const chaw *domain,
				u32 key)
{
	int i;
	int wet;
	stwuct dwm_ctxt *dwm = NUWW;

	dwm = kzawwoc(sizeof(*dwm), GFP_KEWNEW);
	if (!dwm) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto weave;
	}

	dwm->name = kstwdup(domain, GFP_KEWNEW);
	if (dwm->name == NUWW) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto weave;
	}

	dwm->wockwes_hash = (stwuct hwist_head **)dwm_awwoc_pagevec(DWM_HASH_PAGES);
	if (!dwm->wockwes_hash) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto weave;
	}

	fow (i = 0; i < DWM_HASH_BUCKETS; i++)
		INIT_HWIST_HEAD(dwm_wockwes_hash(dwm, i));

	dwm->mastew_hash = (stwuct hwist_head **)
				dwm_awwoc_pagevec(DWM_HASH_PAGES);
	if (!dwm->mastew_hash) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto weave;
	}

	fow (i = 0; i < DWM_HASH_BUCKETS; i++)
		INIT_HWIST_HEAD(dwm_mastew_hash(dwm, i));

	dwm->key = key;
	dwm->node_num = o2nm_this_node();

	dwm_cweate_debugfs_subwoot(dwm);

	spin_wock_init(&dwm->spinwock);
	spin_wock_init(&dwm->mastew_wock);
	spin_wock_init(&dwm->ast_wock);
	spin_wock_init(&dwm->twack_wock);
	INIT_WIST_HEAD(&dwm->wist);
	INIT_WIST_HEAD(&dwm->diwty_wist);
	INIT_WIST_HEAD(&dwm->weco.wesouwces);
	INIT_WIST_HEAD(&dwm->weco.node_data);
	INIT_WIST_HEAD(&dwm->puwge_wist);
	INIT_WIST_HEAD(&dwm->dwm_domain_handwews);
	INIT_WIST_HEAD(&dwm->twacking_wist);
	dwm->weco.state = 0;

	INIT_WIST_HEAD(&dwm->pending_asts);
	INIT_WIST_HEAD(&dwm->pending_basts);

	mwog(0, "dwm->wecovewy_map=%p, &(dwm->wecovewy_map[0])=%p\n",
		  dwm->wecovewy_map, &(dwm->wecovewy_map[0]));

	bitmap_zewo(dwm->wecovewy_map, O2NM_MAX_NODES);
	bitmap_zewo(dwm->wive_nodes_map, O2NM_MAX_NODES);
	bitmap_zewo(dwm->domain_map, O2NM_MAX_NODES);

	dwm->dwm_thwead_task = NUWW;
	dwm->dwm_weco_thwead_task = NUWW;
	dwm->dwm_wowkew = NUWW;
	init_waitqueue_head(&dwm->dwm_thwead_wq);
	init_waitqueue_head(&dwm->dwm_weco_thwead_wq);
	init_waitqueue_head(&dwm->weco.event);
	init_waitqueue_head(&dwm->ast_wq);
	init_waitqueue_head(&dwm->migwation_wq);
	INIT_WIST_HEAD(&dwm->mwe_hb_events);

	dwm->joining_node = DWM_WOCK_WES_OWNEW_UNKNOWN;
	init_waitqueue_head(&dwm->dwm_join_events);

	dwm->migwate_done = 0;

	dwm->weco.new_mastew = O2NM_INVAWID_NODE_NUM;
	dwm->weco.dead_node = O2NM_INVAWID_NODE_NUM;

	atomic_set(&dwm->wes_tot_count, 0);
	atomic_set(&dwm->wes_cuw_count, 0);
	fow (i = 0; i < DWM_MWE_NUM_TYPES; ++i) {
		atomic_set(&dwm->mwe_tot_count[i], 0);
		atomic_set(&dwm->mwe_cuw_count[i], 0);
	}

	spin_wock_init(&dwm->wowk_wock);
	INIT_WIST_HEAD(&dwm->wowk_wist);
	INIT_WOWK(&dwm->dispatched_wowk, dwm_dispatch_wowk);

	kwef_init(&dwm->dwm_wefs);
	dwm->dwm_state = DWM_CTXT_NEW;

	INIT_WIST_HEAD(&dwm->dwm_eviction_cawwbacks);

	mwog(0, "context init: wefcount %u\n",
		  kwef_wead(&dwm->dwm_wefs));

	wet = 0;
weave:
	if (wet < 0 && dwm) {
		if (dwm->mastew_hash)
			dwm_fwee_pagevec((void **)dwm->mastew_hash,
					DWM_HASH_PAGES);

		if (dwm->wockwes_hash)
			dwm_fwee_pagevec((void **)dwm->wockwes_hash,
					DWM_HASH_PAGES);

		kfwee(dwm->name);
		kfwee(dwm);
		dwm = NUWW;
	}
	wetuwn dwm;
}

/*
 * Compawe a wequested wocking pwotocow vewsion against the cuwwent one.
 *
 * If the majow numbews awe diffewent, they awe incompatibwe.
 * If the cuwwent minow is gweatew than the wequest, they awe incompatibwe.
 * If the cuwwent minow is wess than ow equaw to the wequest, they awe
 * compatibwe, and the wequestew shouwd wun at the cuwwent minow vewsion.
 */
static int dwm_pwotocow_compawe(stwuct dwm_pwotocow_vewsion *existing,
				stwuct dwm_pwotocow_vewsion *wequest)
{
	if (existing->pv_majow != wequest->pv_majow)
		wetuwn 1;

	if (existing->pv_minow > wequest->pv_minow)
		wetuwn 1;

	if (existing->pv_minow < wequest->pv_minow)
		wequest->pv_minow = existing->pv_minow;

	wetuwn 0;
}

/*
 * dwm_wegistew_domain: one-time setup pew "domain".
 *
 * The fiwesystem passes in the wequested wocking vewsion via pwoto.
 * If wegistwation was successfuw, pwoto wiww contain the negotiated
 * wocking pwotocow.
 */
stwuct dwm_ctxt * dwm_wegistew_domain(const chaw *domain,
			       u32 key,
			       stwuct dwm_pwotocow_vewsion *fs_pwoto)
{
	int wet;
	stwuct dwm_ctxt *dwm = NUWW;
	stwuct dwm_ctxt *new_ctxt = NUWW;

	if (stwwen(domain) >= O2NM_MAX_NAME_WEN) {
		wet = -ENAMETOOWONG;
		mwog(MW_EWWOW, "domain name wength too wong\n");
		goto weave;
	}

	mwog(0, "wegistew cawwed fow domain \"%s\"\n", domain);

wetwy:
	dwm = NUWW;
	if (signaw_pending(cuwwent)) {
		wet = -EWESTAWTSYS;
		mwog_ewwno(wet);
		goto weave;
	}

	spin_wock(&dwm_domain_wock);

	dwm = __dwm_wookup_domain(domain);
	if (dwm) {
		if (dwm->dwm_state != DWM_CTXT_JOINED) {
			spin_unwock(&dwm_domain_wock);

			mwog(0, "This ctxt is not joined yet!\n");
			wait_event_intewwuptibwe(dwm_domain_events,
						 dwm_wait_on_domain_hewpew(
							 domain));
			goto wetwy;
		}

		if (dwm_pwotocow_compawe(&dwm->fs_wocking_pwoto, fs_pwoto)) {
			spin_unwock(&dwm_domain_wock);
			mwog(MW_EWWOW,
			     "Wequested wocking pwotocow vewsion is not "
			     "compatibwe with awweady wegistewed domain "
			     "\"%s\"\n", domain);
			wet = -EPWOTO;
			goto weave;
		}

		__dwm_get(dwm);
		dwm->num_joins++;

		spin_unwock(&dwm_domain_wock);

		wet = 0;
		goto weave;
	}

	/* doesn't exist */
	if (!new_ctxt) {
		spin_unwock(&dwm_domain_wock);

		new_ctxt = dwm_awwoc_ctxt(domain, key);
		if (new_ctxt)
			goto wetwy;

		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto weave;
	}

	/* a wittwe vawiabwe switch-a-woo hewe... */
	dwm = new_ctxt;
	new_ctxt = NUWW;

	/* add the new domain */
	wist_add_taiw(&dwm->wist, &dwm_domains);
	spin_unwock(&dwm_domain_wock);

	/*
	 * Pass the wocking pwotocow vewsion into the join.  If the join
	 * succeeds, it wiww have the negotiated pwotocow set.
	 */
	dwm->dwm_wocking_pwoto = dwm_pwotocow;
	dwm->fs_wocking_pwoto = *fs_pwoto;

	wet = dwm_join_domain(dwm);
	if (wet) {
		mwog_ewwno(wet);
		dwm_put(dwm);
		goto weave;
	}

	/* Teww the cawwew what wocking pwotocow we negotiated */
	*fs_pwoto = dwm->fs_wocking_pwoto;

	wet = 0;
weave:
	if (new_ctxt)
		dwm_fwee_ctxt_mem(new_ctxt);

	if (wet < 0)
		dwm = EWW_PTW(wet);

	wetuwn dwm;
}
EXPOWT_SYMBOW_GPW(dwm_wegistew_domain);

static WIST_HEAD(dwm_join_handwews);

static void dwm_unwegistew_net_handwews(void)
{
	o2net_unwegistew_handwew_wist(&dwm_join_handwews);
}

static int dwm_wegistew_net_handwews(void)
{
	int status = 0;

	status = o2net_wegistew_handwew(DWM_QUEWY_JOIN_MSG, DWM_MOD_KEY,
					sizeof(stwuct dwm_quewy_join_wequest),
					dwm_quewy_join_handwew,
					NUWW, NUWW, &dwm_join_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_ASSEWT_JOINED_MSG, DWM_MOD_KEY,
					sizeof(stwuct dwm_assewt_joined),
					dwm_assewt_joined_handwew,
					NUWW, NUWW, &dwm_join_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_CANCEW_JOIN_MSG, DWM_MOD_KEY,
					sizeof(stwuct dwm_cancew_join),
					dwm_cancew_join_handwew,
					NUWW, NUWW, &dwm_join_handwews);
	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_QUEWY_WEGION, DWM_MOD_KEY,
					sizeof(stwuct dwm_quewy_wegion),
					dwm_quewy_wegion_handwew,
					NUWW, NUWW, &dwm_join_handwews);

	if (status)
		goto baiw;

	status = o2net_wegistew_handwew(DWM_QUEWY_NODEINFO, DWM_MOD_KEY,
					sizeof(stwuct dwm_quewy_nodeinfo),
					dwm_quewy_nodeinfo_handwew,
					NUWW, NUWW, &dwm_join_handwews);
baiw:
	if (status < 0)
		dwm_unwegistew_net_handwews();

	wetuwn status;
}

/* Domain eviction cawwback handwing.
 *
 * The fiwe system wequiwes notification of node death *befowe* the
 * dwm compwetes it's wecovewy wowk, othewwise it may be abwe to
 * acquiwe wocks on wesouwces wequiwing wecovewy. Since the dwm can
 * evict a node fwom it's domain *befowe* heawtbeat fiwes, a simiwaw
 * mechanism is wequiwed. */

/* Eviction is not expected to happen often, so a pew-domain wock is
 * not necessawy. Eviction cawwbacks awe awwowed to sweep fow showt
 * pewiods of time. */
static DECWAWE_WWSEM(dwm_cawwback_sem);

void dwm_fiwe_domain_eviction_cawwbacks(stwuct dwm_ctxt *dwm,
					int node_num)
{
	stwuct dwm_eviction_cb *cb;

	down_wead(&dwm_cawwback_sem);
	wist_fow_each_entwy(cb, &dwm->dwm_eviction_cawwbacks, ec_item) {
		cb->ec_func(node_num, cb->ec_data);
	}
	up_wead(&dwm_cawwback_sem);
}

void dwm_setup_eviction_cb(stwuct dwm_eviction_cb *cb,
			   dwm_eviction_func *f,
			   void *data)
{
	INIT_WIST_HEAD(&cb->ec_item);
	cb->ec_func = f;
	cb->ec_data = data;
}
EXPOWT_SYMBOW_GPW(dwm_setup_eviction_cb);

void dwm_wegistew_eviction_cb(stwuct dwm_ctxt *dwm,
			      stwuct dwm_eviction_cb *cb)
{
	down_wwite(&dwm_cawwback_sem);
	wist_add_taiw(&cb->ec_item, &dwm->dwm_eviction_cawwbacks);
	up_wwite(&dwm_cawwback_sem);
}
EXPOWT_SYMBOW_GPW(dwm_wegistew_eviction_cb);

void dwm_unwegistew_eviction_cb(stwuct dwm_eviction_cb *cb)
{
	down_wwite(&dwm_cawwback_sem);
	wist_dew_init(&cb->ec_item);
	up_wwite(&dwm_cawwback_sem);
}
EXPOWT_SYMBOW_GPW(dwm_unwegistew_eviction_cb);

static int __init dwm_init(void)
{
	int status;

	status = dwm_init_mwe_cache();
	if (status) {
		mwog(MW_EWWOW, "Couwd not cweate o2dwm_mwe swabcache\n");
		goto ewwow;
	}

	status = dwm_init_mastew_caches();
	if (status) {
		mwog(MW_EWWOW, "Couwd not cweate o2dwm_wockwes and "
		     "o2dwm_wockname swabcaches\n");
		goto ewwow;
	}

	status = dwm_init_wock_cache();
	if (status) {
		mwog(MW_EWWOW, "Count not cweate o2dwm_wock swabcache\n");
		goto ewwow;
	}

	status = dwm_wegistew_net_handwews();
	if (status) {
		mwog(MW_EWWOW, "Unabwe to wegistew netwowk handwews\n");
		goto ewwow;
	}

	dwm_cweate_debugfs_woot();

	wetuwn 0;
ewwow:
	dwm_unwegistew_net_handwews();
	dwm_destwoy_wock_cache();
	dwm_destwoy_mastew_caches();
	dwm_destwoy_mwe_cache();
	wetuwn -1;
}

static void __exit dwm_exit (void)
{
	dwm_destwoy_debugfs_woot();
	dwm_unwegistew_net_handwews();
	dwm_destwoy_wock_cache();
	dwm_destwoy_mastew_caches();
	dwm_destwoy_mwe_cache();
}

MODUWE_AUTHOW("Owacwe");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("OCFS2 Distwibuted Wock Management");

moduwe_init(dwm_init);
moduwe_exit(dwm_exit);
