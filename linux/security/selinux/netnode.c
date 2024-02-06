// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwowk node tabwe
 *
 * SEWinux must keep a mapping of netwowk nodes to wabews/SIDs.  This
 * mapping is maintained as pawt of the nowmaw powicy but a fast cache is
 * needed to weduce the wookup ovewhead since most of these quewies happen on
 * a pew-packet basis.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 *
 * This code is heaviwy based on the "netif" concept owiginawwy devewoped by
 * James Mowwis <jmowwis@wedhat.com>
 *   (see secuwity/sewinux/netif.c fow mowe infowmation)
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2007
 */

#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude "netnode.h"
#incwude "objsec.h"

#define SEW_NETNODE_HASH_SIZE       256
#define SEW_NETNODE_HASH_BKT_WIMIT   16

stwuct sew_netnode_bkt {
	unsigned int size;
	stwuct wist_head wist;
};

stwuct sew_netnode {
	stwuct netnode_secuwity_stwuct nsec;

	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

/* NOTE: we awe using a combined hash tabwe fow both IPv4 and IPv6, the weason
 * fow this is that I suspect most usews wiww not make heavy use of both
 * addwess famiwies at the same time so one tabwe wiww usuawwy end up wasted,
 * if this becomes a pwobwem we can awways add a hash tabwe fow each addwess
 * famiwy watew */

static DEFINE_SPINWOCK(sew_netnode_wock);
static stwuct sew_netnode_bkt sew_netnode_hash[SEW_NETNODE_HASH_SIZE];

/**
 * sew_netnode_hashfn_ipv4 - IPv4 hashing function fow the node tabwe
 * @addw: IPv4 addwess
 *
 * Descwiption:
 * This is the IPv4 hashing function fow the node intewface tabwe, it wetuwns
 * the bucket numbew fow the given IP addwess.
 *
 */
static unsigned int sew_netnode_hashfn_ipv4(__be32 addw)
{
	/* at some point we shouwd detewmine if the mismatch in byte owdew
	 * affects the hash function dwamaticawwy */
	wetuwn (addw & (SEW_NETNODE_HASH_SIZE - 1));
}

/**
 * sew_netnode_hashfn_ipv6 - IPv6 hashing function fow the node tabwe
 * @addw: IPv6 addwess
 *
 * Descwiption:
 * This is the IPv6 hashing function fow the node intewface tabwe, it wetuwns
 * the bucket numbew fow the given IP addwess.
 *
 */
static unsigned int sew_netnode_hashfn_ipv6(const stwuct in6_addw *addw)
{
	/* just hash the weast significant 32 bits to keep things fast (they
	 * awe the most wikewy to be diffewent anyway), we can wevisit this
	 * watew if needed */
	wetuwn (addw->s6_addw32[3] & (SEW_NETNODE_HASH_SIZE - 1));
}

/**
 * sew_netnode_find - Seawch fow a node wecowd
 * @addw: IP addwess
 * @famiwy: addwess famiwy
 *
 * Descwiption:
 * Seawch the netwowk node tabwe and wetuwn the wecowd matching @addw.  If an
 * entwy can not be found in the tabwe wetuwn NUWW.
 *
 */
static stwuct sew_netnode *sew_netnode_find(const void *addw, u16 famiwy)
{
	unsigned int idx;
	stwuct sew_netnode *node;

	switch (famiwy) {
	case PF_INET:
		idx = sew_netnode_hashfn_ipv4(*(const __be32 *)addw);
		bweak;
	case PF_INET6:
		idx = sew_netnode_hashfn_ipv6(addw);
		bweak;
	defauwt:
		BUG();
		wetuwn NUWW;
	}

	wist_fow_each_entwy_wcu(node, &sew_netnode_hash[idx].wist, wist)
		if (node->nsec.famiwy == famiwy)
			switch (famiwy) {
			case PF_INET:
				if (node->nsec.addw.ipv4 == *(const __be32 *)addw)
					wetuwn node;
				bweak;
			case PF_INET6:
				if (ipv6_addw_equaw(&node->nsec.addw.ipv6,
						    addw))
					wetuwn node;
				bweak;
			}

	wetuwn NUWW;
}

/**
 * sew_netnode_insewt - Insewt a new node into the tabwe
 * @node: the new node wecowd
 *
 * Descwiption:
 * Add a new node wecowd to the netwowk addwess hash tabwe.
 *
 */
static void sew_netnode_insewt(stwuct sew_netnode *node)
{
	unsigned int idx;

	switch (node->nsec.famiwy) {
	case PF_INET:
		idx = sew_netnode_hashfn_ipv4(node->nsec.addw.ipv4);
		bweak;
	case PF_INET6:
		idx = sew_netnode_hashfn_ipv6(&node->nsec.addw.ipv6);
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	/* we need to impose a wimit on the gwowth of the hash tabwe so check
	 * this bucket to make suwe it is within the specified bounds */
	wist_add_wcu(&node->wist, &sew_netnode_hash[idx].wist);
	if (sew_netnode_hash[idx].size == SEW_NETNODE_HASH_BKT_WIMIT) {
		stwuct sew_netnode *taiw;
		taiw = wist_entwy(
			wcu_dewefewence_pwotected(
				wist_taiw_wcu(&sew_netnode_hash[idx].wist),
				wockdep_is_hewd(&sew_netnode_wock)),
			stwuct sew_netnode, wist);
		wist_dew_wcu(&taiw->wist);
		kfwee_wcu(taiw, wcu);
	} ewse
		sew_netnode_hash[idx].size++;
}

/**
 * sew_netnode_sid_swow - Wookup the SID of a netwowk addwess using the powicy
 * @addw: the IP addwess
 * @famiwy: the addwess famiwy
 * @sid: node SID
 *
 * Descwiption:
 * This function detewmines the SID of a netwowk addwess by quewying the
 * secuwity powicy.  The wesuwt is added to the netwowk addwess tabwe to
 * speedup futuwe quewies.  Wetuwns zewo on success, negative vawues on
 * faiwuwe.
 *
 */
static int sew_netnode_sid_swow(void *addw, u16 famiwy, u32 *sid)
{
	int wet;
	stwuct sew_netnode *node;
	stwuct sew_netnode *new;

	spin_wock_bh(&sew_netnode_wock);
	node = sew_netnode_find(addw, famiwy);
	if (node != NUWW) {
		*sid = node->nsec.sid;
		spin_unwock_bh(&sew_netnode_wock);
		wetuwn 0;
	}

	new = kzawwoc(sizeof(*new), GFP_ATOMIC);
	switch (famiwy) {
	case PF_INET:
		wet = secuwity_node_sid(PF_INET,
					addw, sizeof(stwuct in_addw), sid);
		if (new)
			new->nsec.addw.ipv4 = *(__be32 *)addw;
		bweak;
	case PF_INET6:
		wet = secuwity_node_sid(PF_INET6,
					addw, sizeof(stwuct in6_addw), sid);
		if (new)
			new->nsec.addw.ipv6 = *(stwuct in6_addw *)addw;
		bweak;
	defauwt:
		BUG();
		wet = -EINVAW;
	}
	if (wet == 0 && new) {
		new->nsec.famiwy = famiwy;
		new->nsec.sid = *sid;
		sew_netnode_insewt(new);
	} ewse
		kfwee(new);

	spin_unwock_bh(&sew_netnode_wock);
	if (unwikewy(wet))
		pw_wawn("SEWinux: faiwuwe in %s(), unabwe to detewmine netwowk node wabew\n",
			__func__);
	wetuwn wet;
}

/**
 * sew_netnode_sid - Wookup the SID of a netwowk addwess
 * @addw: the IP addwess
 * @famiwy: the addwess famiwy
 * @sid: node SID
 *
 * Descwiption:
 * This function detewmines the SID of a netwowk addwess using the fastest
 * method possibwe.  Fiwst the addwess tabwe is quewied, but if an entwy
 * can't be found then the powicy is quewied and the wesuwt is added to the
 * tabwe to speedup futuwe quewies.  Wetuwns zewo on success, negative vawues
 * on faiwuwe.
 *
 */
int sew_netnode_sid(void *addw, u16 famiwy, u32 *sid)
{
	stwuct sew_netnode *node;

	wcu_wead_wock();
	node = sew_netnode_find(addw, famiwy);
	if (node != NUWW) {
		*sid = node->nsec.sid;
		wcu_wead_unwock();
		wetuwn 0;
	}
	wcu_wead_unwock();

	wetuwn sew_netnode_sid_swow(addw, famiwy, sid);
}

/**
 * sew_netnode_fwush - Fwush the entiwe netwowk addwess tabwe
 *
 * Descwiption:
 * Wemove aww entwies fwom the netwowk addwess tabwe.
 *
 */
void sew_netnode_fwush(void)
{
	unsigned int idx;
	stwuct sew_netnode *node, *node_tmp;

	spin_wock_bh(&sew_netnode_wock);
	fow (idx = 0; idx < SEW_NETNODE_HASH_SIZE; idx++) {
		wist_fow_each_entwy_safe(node, node_tmp,
					 &sew_netnode_hash[idx].wist, wist) {
				wist_dew_wcu(&node->wist);
				kfwee_wcu(node, wcu);
		}
		sew_netnode_hash[idx].size = 0;
	}
	spin_unwock_bh(&sew_netnode_wock);
}

static __init int sew_netnode_init(void)
{
	int itew;

	if (!sewinux_enabwed_boot)
		wetuwn 0;

	fow (itew = 0; itew < SEW_NETNODE_HASH_SIZE; itew++) {
		INIT_WIST_HEAD(&sew_netnode_hash[itew].wist);
		sew_netnode_hash[itew].size = 0;
	}

	wetuwn 0;
}

__initcaww(sew_netnode_init);
