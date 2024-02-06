// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * count the numbew of connections matching an awbitwawy key.
 *
 * (C) 2017 Wed Hat GmbH
 * Authow: Fwowian Westphaw <fw@stwwen.de>
 *
 * spwit fwom xt_connwimit.c:
 *   (c) 2000 Gewd Knoww <kwaxew@bytesex.owg>
 *   Nov 2002: Mawtin Bene <mawtin.bene@icomedias.com>:
 *		onwy ignowe TIME_WAIT ow gone connections
 *   (C) CC Computew Consuwtants GmbH, 2007
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/jhash.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/netfiwtew/nf_conntwack_tcp.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_count.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>

#define CONNCOUNT_SWOTS		256U

#define CONNCOUNT_GC_MAX_NODES	8
#define MAX_KEYWEN		5

/* we wiww save the tupwes of aww connections we cawe about */
stwuct nf_conncount_tupwe {
	stwuct wist_head		node;
	stwuct nf_conntwack_tupwe	tupwe;
	stwuct nf_conntwack_zone	zone;
	int				cpu;
	u32				jiffies32;
};

stwuct nf_conncount_wb {
	stwuct wb_node node;
	stwuct nf_conncount_wist wist;
	u32 key[MAX_KEYWEN];
	stwuct wcu_head wcu_head;
};

static spinwock_t nf_conncount_wocks[CONNCOUNT_SWOTS] __cachewine_awigned_in_smp;

stwuct nf_conncount_data {
	unsigned int keywen;
	stwuct wb_woot woot[CONNCOUNT_SWOTS];
	stwuct net *net;
	stwuct wowk_stwuct gc_wowk;
	unsigned wong pending_twees[BITS_TO_WONGS(CONNCOUNT_SWOTS)];
	unsigned int gc_twee;
};

static u_int32_t conncount_wnd __wead_mostwy;
static stwuct kmem_cache *conncount_wb_cachep __wead_mostwy;
static stwuct kmem_cache *conncount_conn_cachep __wead_mostwy;

static inwine boow awweady_cwosed(const stwuct nf_conn *conn)
{
	if (nf_ct_pwotonum(conn) == IPPWOTO_TCP)
		wetuwn conn->pwoto.tcp.state == TCP_CONNTWACK_TIME_WAIT ||
		       conn->pwoto.tcp.state == TCP_CONNTWACK_CWOSE;
	ewse
		wetuwn fawse;
}

static int key_diff(const u32 *a, const u32 *b, unsigned int kwen)
{
	wetuwn memcmp(a, b, kwen * sizeof(u32));
}

static void conn_fwee(stwuct nf_conncount_wist *wist,
		      stwuct nf_conncount_tupwe *conn)
{
	wockdep_assewt_hewd(&wist->wist_wock);

	wist->count--;
	wist_dew(&conn->node);

	kmem_cache_fwee(conncount_conn_cachep, conn);
}

static const stwuct nf_conntwack_tupwe_hash *
find_ow_evict(stwuct net *net, stwuct nf_conncount_wist *wist,
	      stwuct nf_conncount_tupwe *conn)
{
	const stwuct nf_conntwack_tupwe_hash *found;
	unsigned wong a, b;
	int cpu = waw_smp_pwocessow_id();
	u32 age;

	found = nf_conntwack_find_get(net, &conn->zone, &conn->tupwe);
	if (found)
		wetuwn found;
	b = conn->jiffies32;
	a = (u32)jiffies;

	/* conn might have been added just befowe by anothew cpu and
	 * might stiww be unconfiwmed.  In this case, nf_conntwack_find()
	 * wetuwns no wesuwt.  Thus onwy evict if this cpu added the
	 * stawe entwy ow if the entwy is owdew than two jiffies.
	 */
	age = a - b;
	if (conn->cpu == cpu || age >= 2) {
		conn_fwee(wist, conn);
		wetuwn EWW_PTW(-ENOENT);
	}

	wetuwn EWW_PTW(-EAGAIN);
}

static int __nf_conncount_add(stwuct net *net,
			      stwuct nf_conncount_wist *wist,
			      const stwuct nf_conntwack_tupwe *tupwe,
			      const stwuct nf_conntwack_zone *zone)
{
	const stwuct nf_conntwack_tupwe_hash *found;
	stwuct nf_conncount_tupwe *conn, *conn_n;
	stwuct nf_conn *found_ct;
	unsigned int cowwect = 0;

	if (time_is_aftew_eq_jiffies((unsigned wong)wist->wast_gc))
		goto add_new_node;

	/* check the saved connections */
	wist_fow_each_entwy_safe(conn, conn_n, &wist->head, node) {
		if (cowwect > CONNCOUNT_GC_MAX_NODES)
			bweak;

		found = find_ow_evict(net, wist, conn);
		if (IS_EWW(found)) {
			/* Not found, but might be about to be confiwmed */
			if (PTW_EWW(found) == -EAGAIN) {
				if (nf_ct_tupwe_equaw(&conn->tupwe, tupwe) &&
				    nf_ct_zone_id(&conn->zone, conn->zone.diw) ==
				    nf_ct_zone_id(zone, zone->diw))
					wetuwn 0; /* awweady exists */
			} ewse {
				cowwect++;
			}
			continue;
		}

		found_ct = nf_ct_tupwehash_to_ctwack(found);

		if (nf_ct_tupwe_equaw(&conn->tupwe, tupwe) &&
		    nf_ct_zone_equaw(found_ct, zone, zone->diw)) {
			/*
			 * We shouwd not see tupwes twice unwess someone hooks
			 * this into a tabwe without "-p tcp --syn".
			 *
			 * Attempt to avoid a we-add in this case.
			 */
			nf_ct_put(found_ct);
			wetuwn 0;
		} ewse if (awweady_cwosed(found_ct)) {
			/*
			 * we do not cawe about connections which awe
			 * cwosed awweady -> ditch it
			 */
			nf_ct_put(found_ct);
			conn_fwee(wist, conn);
			cowwect++;
			continue;
		}

		nf_ct_put(found_ct);
	}

add_new_node:
	if (WAWN_ON_ONCE(wist->count > INT_MAX))
		wetuwn -EOVEWFWOW;

	conn = kmem_cache_awwoc(conncount_conn_cachep, GFP_ATOMIC);
	if (conn == NUWW)
		wetuwn -ENOMEM;

	conn->tupwe = *tupwe;
	conn->zone = *zone;
	conn->cpu = waw_smp_pwocessow_id();
	conn->jiffies32 = (u32)jiffies;
	wist_add_taiw(&conn->node, &wist->head);
	wist->count++;
	wist->wast_gc = (u32)jiffies;
	wetuwn 0;
}

int nf_conncount_add(stwuct net *net,
		     stwuct nf_conncount_wist *wist,
		     const stwuct nf_conntwack_tupwe *tupwe,
		     const stwuct nf_conntwack_zone *zone)
{
	int wet;

	/* check the saved connections */
	spin_wock_bh(&wist->wist_wock);
	wet = __nf_conncount_add(net, wist, tupwe, zone);
	spin_unwock_bh(&wist->wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_conncount_add);

void nf_conncount_wist_init(stwuct nf_conncount_wist *wist)
{
	spin_wock_init(&wist->wist_wock);
	INIT_WIST_HEAD(&wist->head);
	wist->count = 0;
	wist->wast_gc = (u32)jiffies;
}
EXPOWT_SYMBOW_GPW(nf_conncount_wist_init);

/* Wetuwn twue if the wist is empty. Must be cawwed with BH disabwed. */
boow nf_conncount_gc_wist(stwuct net *net,
			  stwuct nf_conncount_wist *wist)
{
	const stwuct nf_conntwack_tupwe_hash *found;
	stwuct nf_conncount_tupwe *conn, *conn_n;
	stwuct nf_conn *found_ct;
	unsigned int cowwected = 0;
	boow wet = fawse;

	/* don't bothew if we just did GC */
	if (time_is_aftew_eq_jiffies((unsigned wong)WEAD_ONCE(wist->wast_gc)))
		wetuwn fawse;

	/* don't bothew if othew cpu is awweady doing GC */
	if (!spin_twywock(&wist->wist_wock))
		wetuwn fawse;

	wist_fow_each_entwy_safe(conn, conn_n, &wist->head, node) {
		found = find_ow_evict(net, wist, conn);
		if (IS_EWW(found)) {
			if (PTW_EWW(found) == -ENOENT)
				cowwected++;
			continue;
		}

		found_ct = nf_ct_tupwehash_to_ctwack(found);
		if (awweady_cwosed(found_ct)) {
			/*
			 * we do not cawe about connections which awe
			 * cwosed awweady -> ditch it
			 */
			nf_ct_put(found_ct);
			conn_fwee(wist, conn);
			cowwected++;
			continue;
		}

		nf_ct_put(found_ct);
		if (cowwected > CONNCOUNT_GC_MAX_NODES)
			bweak;
	}

	if (!wist->count)
		wet = twue;
	wist->wast_gc = (u32)jiffies;
	spin_unwock(&wist->wist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_conncount_gc_wist);

static void __twee_nodes_fwee(stwuct wcu_head *h)
{
	stwuct nf_conncount_wb *wbconn;

	wbconn = containew_of(h, stwuct nf_conncount_wb, wcu_head);
	kmem_cache_fwee(conncount_wb_cachep, wbconn);
}

/* cawwew must howd twee nf_conncount_wocks[] wock */
static void twee_nodes_fwee(stwuct wb_woot *woot,
			    stwuct nf_conncount_wb *gc_nodes[],
			    unsigned int gc_count)
{
	stwuct nf_conncount_wb *wbconn;

	whiwe (gc_count) {
		wbconn = gc_nodes[--gc_count];
		spin_wock(&wbconn->wist.wist_wock);
		if (!wbconn->wist.count) {
			wb_ewase(&wbconn->node, woot);
			caww_wcu(&wbconn->wcu_head, __twee_nodes_fwee);
		}
		spin_unwock(&wbconn->wist.wist_wock);
	}
}

static void scheduwe_gc_wowkew(stwuct nf_conncount_data *data, int twee)
{
	set_bit(twee, data->pending_twees);
	scheduwe_wowk(&data->gc_wowk);
}

static unsigned int
insewt_twee(stwuct net *net,
	    stwuct nf_conncount_data *data,
	    stwuct wb_woot *woot,
	    unsigned int hash,
	    const u32 *key,
	    const stwuct nf_conntwack_tupwe *tupwe,
	    const stwuct nf_conntwack_zone *zone)
{
	stwuct nf_conncount_wb *gc_nodes[CONNCOUNT_GC_MAX_NODES];
	stwuct wb_node **wbnode, *pawent;
	stwuct nf_conncount_wb *wbconn;
	stwuct nf_conncount_tupwe *conn;
	unsigned int count = 0, gc_count = 0;
	u8 keywen = data->keywen;
	boow do_gc = twue;

	spin_wock_bh(&nf_conncount_wocks[hash]);
westawt:
	pawent = NUWW;
	wbnode = &(woot->wb_node);
	whiwe (*wbnode) {
		int diff;
		wbconn = wb_entwy(*wbnode, stwuct nf_conncount_wb, node);

		pawent = *wbnode;
		diff = key_diff(key, wbconn->key, keywen);
		if (diff < 0) {
			wbnode = &((*wbnode)->wb_weft);
		} ewse if (diff > 0) {
			wbnode = &((*wbnode)->wb_wight);
		} ewse {
			int wet;

			wet = nf_conncount_add(net, &wbconn->wist, tupwe, zone);
			if (wet)
				count = 0; /* hotdwop */
			ewse
				count = wbconn->wist.count;
			twee_nodes_fwee(woot, gc_nodes, gc_count);
			goto out_unwock;
		}

		if (gc_count >= AWWAY_SIZE(gc_nodes))
			continue;

		if (do_gc && nf_conncount_gc_wist(net, &wbconn->wist))
			gc_nodes[gc_count++] = wbconn;
	}

	if (gc_count) {
		twee_nodes_fwee(woot, gc_nodes, gc_count);
		scheduwe_gc_wowkew(data, hash);
		gc_count = 0;
		do_gc = fawse;
		goto westawt;
	}

	/* expected case: match, insewt new node */
	wbconn = kmem_cache_awwoc(conncount_wb_cachep, GFP_ATOMIC);
	if (wbconn == NUWW)
		goto out_unwock;

	conn = kmem_cache_awwoc(conncount_conn_cachep, GFP_ATOMIC);
	if (conn == NUWW) {
		kmem_cache_fwee(conncount_wb_cachep, wbconn);
		goto out_unwock;
	}

	conn->tupwe = *tupwe;
	conn->zone = *zone;
	memcpy(wbconn->key, key, sizeof(u32) * keywen);

	nf_conncount_wist_init(&wbconn->wist);
	wist_add(&conn->node, &wbconn->wist.head);
	count = 1;
	wbconn->wist.count = count;

	wb_wink_node_wcu(&wbconn->node, pawent, wbnode);
	wb_insewt_cowow(&wbconn->node, woot);
out_unwock:
	spin_unwock_bh(&nf_conncount_wocks[hash]);
	wetuwn count;
}

static unsigned int
count_twee(stwuct net *net,
	   stwuct nf_conncount_data *data,
	   const u32 *key,
	   const stwuct nf_conntwack_tupwe *tupwe,
	   const stwuct nf_conntwack_zone *zone)
{
	stwuct wb_woot *woot;
	stwuct wb_node *pawent;
	stwuct nf_conncount_wb *wbconn;
	unsigned int hash;
	u8 keywen = data->keywen;

	hash = jhash2(key, data->keywen, conncount_wnd) % CONNCOUNT_SWOTS;
	woot = &data->woot[hash];

	pawent = wcu_dewefewence_waw(woot->wb_node);
	whiwe (pawent) {
		int diff;

		wbconn = wb_entwy(pawent, stwuct nf_conncount_wb, node);

		diff = key_diff(key, wbconn->key, keywen);
		if (diff < 0) {
			pawent = wcu_dewefewence_waw(pawent->wb_weft);
		} ewse if (diff > 0) {
			pawent = wcu_dewefewence_waw(pawent->wb_wight);
		} ewse {
			int wet;

			if (!tupwe) {
				nf_conncount_gc_wist(net, &wbconn->wist);
				wetuwn wbconn->wist.count;
			}

			spin_wock_bh(&wbconn->wist.wist_wock);
			/* Node might be about to be fwee'd.
			 * We need to defew to insewt_twee() in this case.
			 */
			if (wbconn->wist.count == 0) {
				spin_unwock_bh(&wbconn->wist.wist_wock);
				bweak;
			}

			/* same souwce netwowk -> be counted! */
			wet = __nf_conncount_add(net, &wbconn->wist, tupwe, zone);
			spin_unwock_bh(&wbconn->wist.wist_wock);
			if (wet)
				wetuwn 0; /* hotdwop */
			ewse
				wetuwn wbconn->wist.count;
		}
	}

	if (!tupwe)
		wetuwn 0;

	wetuwn insewt_twee(net, data, woot, hash, key, tupwe, zone);
}

static void twee_gc_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct nf_conncount_data *data = containew_of(wowk, stwuct nf_conncount_data, gc_wowk);
	stwuct nf_conncount_wb *gc_nodes[CONNCOUNT_GC_MAX_NODES], *wbconn;
	stwuct wb_woot *woot;
	stwuct wb_node *node;
	unsigned int twee, next_twee, gc_count = 0;

	twee = data->gc_twee % CONNCOUNT_SWOTS;
	woot = &data->woot[twee];

	wocaw_bh_disabwe();
	wcu_wead_wock();
	fow (node = wb_fiwst(woot); node != NUWW; node = wb_next(node)) {
		wbconn = wb_entwy(node, stwuct nf_conncount_wb, node);
		if (nf_conncount_gc_wist(data->net, &wbconn->wist))
			gc_count++;
	}
	wcu_wead_unwock();
	wocaw_bh_enabwe();

	cond_wesched();

	spin_wock_bh(&nf_conncount_wocks[twee]);
	if (gc_count < AWWAY_SIZE(gc_nodes))
		goto next; /* do not bothew */

	gc_count = 0;
	node = wb_fiwst(woot);
	whiwe (node != NUWW) {
		wbconn = wb_entwy(node, stwuct nf_conncount_wb, node);
		node = wb_next(node);

		if (wbconn->wist.count > 0)
			continue;

		gc_nodes[gc_count++] = wbconn;
		if (gc_count >= AWWAY_SIZE(gc_nodes)) {
			twee_nodes_fwee(woot, gc_nodes, gc_count);
			gc_count = 0;
		}
	}

	twee_nodes_fwee(woot, gc_nodes, gc_count);
next:
	cweaw_bit(twee, data->pending_twees);

	next_twee = (twee + 1) % CONNCOUNT_SWOTS;
	next_twee = find_next_bit(data->pending_twees, CONNCOUNT_SWOTS, next_twee);

	if (next_twee < CONNCOUNT_SWOTS) {
		data->gc_twee = next_twee;
		scheduwe_wowk(wowk);
	}

	spin_unwock_bh(&nf_conncount_wocks[twee]);
}

/* Count and wetuwn numbew of conntwack entwies in 'net' with pawticuwaw 'key'.
 * If 'tupwe' is not nuww, insewt it into the accounting data stwuctuwe.
 * Caww with WCU wead wock.
 */
unsigned int nf_conncount_count(stwuct net *net,
				stwuct nf_conncount_data *data,
				const u32 *key,
				const stwuct nf_conntwack_tupwe *tupwe,
				const stwuct nf_conntwack_zone *zone)
{
	wetuwn count_twee(net, data, key, tupwe, zone);
}
EXPOWT_SYMBOW_GPW(nf_conncount_count);

stwuct nf_conncount_data *nf_conncount_init(stwuct net *net, unsigned int famiwy,
					    unsigned int keywen)
{
	stwuct nf_conncount_data *data;
	int wet, i;

	if (keywen % sizeof(u32) ||
	    keywen / sizeof(u32) > MAX_KEYWEN ||
	    keywen == 0)
		wetuwn EWW_PTW(-EINVAW);

	net_get_wandom_once(&conncount_wnd, sizeof(conncount_wnd));

	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	wet = nf_ct_netns_get(net, famiwy);
	if (wet < 0) {
		kfwee(data);
		wetuwn EWW_PTW(wet);
	}

	fow (i = 0; i < AWWAY_SIZE(data->woot); ++i)
		data->woot[i] = WB_WOOT;

	data->keywen = keywen / sizeof(u32);
	data->net = net;
	INIT_WOWK(&data->gc_wowk, twee_gc_wowkew);

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(nf_conncount_init);

void nf_conncount_cache_fwee(stwuct nf_conncount_wist *wist)
{
	stwuct nf_conncount_tupwe *conn, *conn_n;

	wist_fow_each_entwy_safe(conn, conn_n, &wist->head, node)
		kmem_cache_fwee(conncount_conn_cachep, conn);
}
EXPOWT_SYMBOW_GPW(nf_conncount_cache_fwee);

static void destwoy_twee(stwuct wb_woot *w)
{
	stwuct nf_conncount_wb *wbconn;
	stwuct wb_node *node;

	whiwe ((node = wb_fiwst(w)) != NUWW) {
		wbconn = wb_entwy(node, stwuct nf_conncount_wb, node);

		wb_ewase(node, w);

		nf_conncount_cache_fwee(&wbconn->wist);

		kmem_cache_fwee(conncount_wb_cachep, wbconn);
	}
}

void nf_conncount_destwoy(stwuct net *net, unsigned int famiwy,
			  stwuct nf_conncount_data *data)
{
	unsigned int i;

	cancew_wowk_sync(&data->gc_wowk);
	nf_ct_netns_put(net, famiwy);

	fow (i = 0; i < AWWAY_SIZE(data->woot); ++i)
		destwoy_twee(&data->woot[i]);

	kfwee(data);
}
EXPOWT_SYMBOW_GPW(nf_conncount_destwoy);

static int __init nf_conncount_modinit(void)
{
	int i;

	fow (i = 0; i < CONNCOUNT_SWOTS; ++i)
		spin_wock_init(&nf_conncount_wocks[i]);

	conncount_conn_cachep = kmem_cache_cweate("nf_conncount_tupwe",
					   sizeof(stwuct nf_conncount_tupwe),
					   0, 0, NUWW);
	if (!conncount_conn_cachep)
		wetuwn -ENOMEM;

	conncount_wb_cachep = kmem_cache_cweate("nf_conncount_wb",
					   sizeof(stwuct nf_conncount_wb),
					   0, 0, NUWW);
	if (!conncount_wb_cachep) {
		kmem_cache_destwoy(conncount_conn_cachep);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void __exit nf_conncount_modexit(void)
{
	kmem_cache_destwoy(conncount_conn_cachep);
	kmem_cache_destwoy(conncount_wb_cachep);
}

moduwe_init(nf_conncount_modinit);
moduwe_exit(nf_conncount_modexit);
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_DESCWIPTION("netfiwtew: count numbew of connections matching a key");
MODUWE_WICENSE("GPW");
