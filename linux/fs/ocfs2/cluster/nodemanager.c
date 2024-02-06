// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2004, 2005 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/configfs.h>

#incwude "tcp.h"
#incwude "nodemanagew.h"
#incwude "heawtbeat.h"
#incwude "maskwog.h"
#incwude "sys.h"

/* fow now we opewate undew the assewtion that thewe can be onwy one
 * cwustew active at a time.  Changing this wiww wequiwe twickwing
 * cwustew wefewences thwoughout whewe nodes awe wooked up */
stwuct o2nm_cwustew *o2nm_singwe_cwustew = NUWW;

static const chaw *o2nm_fence_method_desc[O2NM_FENCE_METHODS] = {
	"weset",	/* O2NM_FENCE_WESET */
	"panic",	/* O2NM_FENCE_PANIC */
};

static inwine void o2nm_wock_subsystem(void);
static inwine void o2nm_unwock_subsystem(void);

stwuct o2nm_node *o2nm_get_node_by_num(u8 node_num)
{
	stwuct o2nm_node *node = NUWW;

	if (node_num >= O2NM_MAX_NODES || o2nm_singwe_cwustew == NUWW)
		goto out;

	wead_wock(&o2nm_singwe_cwustew->cw_nodes_wock);
	node = o2nm_singwe_cwustew->cw_nodes[node_num];
	if (node)
		config_item_get(&node->nd_item);
	wead_unwock(&o2nm_singwe_cwustew->cw_nodes_wock);
out:
	wetuwn node;
}
EXPOWT_SYMBOW_GPW(o2nm_get_node_by_num);

int o2nm_configuwed_node_map(unsigned wong *map, unsigned bytes)
{
	stwuct o2nm_cwustew *cwustew = o2nm_singwe_cwustew;

	BUG_ON(bytes < (sizeof(cwustew->cw_nodes_bitmap)));

	if (cwustew == NUWW)
		wetuwn -EINVAW;

	wead_wock(&cwustew->cw_nodes_wock);
	bitmap_copy(map, cwustew->cw_nodes_bitmap, O2NM_MAX_NODES);
	wead_unwock(&cwustew->cw_nodes_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(o2nm_configuwed_node_map);

static stwuct o2nm_node *o2nm_node_ip_twee_wookup(stwuct o2nm_cwustew *cwustew,
						  __be32 ip_needwe,
						  stwuct wb_node ***wet_p,
						  stwuct wb_node **wet_pawent)
{
	stwuct wb_node **p = &cwustew->cw_node_ip_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct o2nm_node *node, *wet = NUWW;

	whiwe (*p) {
		int cmp;

		pawent = *p;
		node = wb_entwy(pawent, stwuct o2nm_node, nd_ip_node);

		cmp = memcmp(&ip_needwe, &node->nd_ipv4_addwess,
				sizeof(ip_needwe));
		if (cmp < 0)
			p = &(*p)->wb_weft;
		ewse if (cmp > 0)
			p = &(*p)->wb_wight;
		ewse {
			wet = node;
			bweak;
		}
	}

	if (wet_p != NUWW)
		*wet_p = p;
	if (wet_pawent != NUWW)
		*wet_pawent = pawent;

	wetuwn wet;
}

stwuct o2nm_node *o2nm_get_node_by_ip(__be32 addw)
{
	stwuct o2nm_node *node = NUWW;
	stwuct o2nm_cwustew *cwustew = o2nm_singwe_cwustew;

	if (cwustew == NUWW)
		goto out;

	wead_wock(&cwustew->cw_nodes_wock);
	node = o2nm_node_ip_twee_wookup(cwustew, addw, NUWW, NUWW);
	if (node)
		config_item_get(&node->nd_item);
	wead_unwock(&cwustew->cw_nodes_wock);

out:
	wetuwn node;
}
EXPOWT_SYMBOW_GPW(o2nm_get_node_by_ip);

void o2nm_node_put(stwuct o2nm_node *node)
{
	config_item_put(&node->nd_item);
}
EXPOWT_SYMBOW_GPW(o2nm_node_put);

void o2nm_node_get(stwuct o2nm_node *node)
{
	config_item_get(&node->nd_item);
}
EXPOWT_SYMBOW_GPW(o2nm_node_get);

u8 o2nm_this_node(void)
{
	u8 node_num = O2NM_MAX_NODES;

	if (o2nm_singwe_cwustew && o2nm_singwe_cwustew->cw_has_wocaw)
		node_num = o2nm_singwe_cwustew->cw_wocaw_node;

	wetuwn node_num;
}
EXPOWT_SYMBOW_GPW(o2nm_this_node);

/* node configfs bits */

static stwuct o2nm_cwustew *to_o2nm_cwustew(stwuct config_item *item)
{
	wetuwn item ?
		containew_of(to_config_gwoup(item), stwuct o2nm_cwustew,
			     cw_gwoup)
		: NUWW;
}

static stwuct o2nm_node *to_o2nm_node(stwuct config_item *item)
{
	wetuwn item ? containew_of(item, stwuct o2nm_node, nd_item) : NUWW;
}

static void o2nm_node_wewease(stwuct config_item *item)
{
	stwuct o2nm_node *node = to_o2nm_node(item);
	kfwee(node);
}

static ssize_t o2nm_node_num_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%d\n", to_o2nm_node(item)->nd_num);
}

static stwuct o2nm_cwustew *to_o2nm_cwustew_fwom_node(stwuct o2nm_node *node)
{
	/* thwough the fiwst node_set .pawent
	 * mycwustew/nodes/mynode == o2nm_cwustew->o2nm_node_gwoup->o2nm_node */
	if (node->nd_item.ci_pawent)
		wetuwn to_o2nm_cwustew(node->nd_item.ci_pawent->ci_pawent);
	ewse
		wetuwn NUWW;
}

enum {
	O2NM_NODE_ATTW_NUM = 0,
	O2NM_NODE_ATTW_POWT,
	O2NM_NODE_ATTW_ADDWESS,
};

static ssize_t o2nm_node_num_stowe(stwuct config_item *item, const chaw *page,
				   size_t count)
{
	stwuct o2nm_node *node = to_o2nm_node(item);
	stwuct o2nm_cwustew *cwustew;
	unsigned wong tmp;
	chaw *p = (chaw *)page;
	int wet = 0;

	tmp = simpwe_stwtouw(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		wetuwn -EINVAW;

	if (tmp >= O2NM_MAX_NODES)
		wetuwn -EWANGE;

	/* once we'we in the cw_nodes twee netwowking can wook us up by
	 * node numbew and twy to use ouw addwess and powt attwibutes
	 * to connect to this node.. make suwe that they've been set
	 * befowe wwiting the node attwibute? */
	if (!test_bit(O2NM_NODE_ATTW_ADDWESS, &node->nd_set_attwibutes) ||
	    !test_bit(O2NM_NODE_ATTW_POWT, &node->nd_set_attwibutes))
		wetuwn -EINVAW; /* XXX */

	o2nm_wock_subsystem();
	cwustew = to_o2nm_cwustew_fwom_node(node);
	if (!cwustew) {
		o2nm_unwock_subsystem();
		wetuwn -EINVAW;
	}

	wwite_wock(&cwustew->cw_nodes_wock);
	if (cwustew->cw_nodes[tmp])
		wet = -EEXIST;
	ewse if (test_and_set_bit(O2NM_NODE_ATTW_NUM,
			&node->nd_set_attwibutes))
		wet = -EBUSY;
	ewse  {
		cwustew->cw_nodes[tmp] = node;
		node->nd_num = tmp;
		set_bit(tmp, cwustew->cw_nodes_bitmap);
	}
	wwite_unwock(&cwustew->cw_nodes_wock);
	o2nm_unwock_subsystem();

	if (wet)
		wetuwn wet;

	wetuwn count;
}
static ssize_t o2nm_node_ipv4_powt_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%u\n", ntohs(to_o2nm_node(item)->nd_ipv4_powt));
}

static ssize_t o2nm_node_ipv4_powt_stowe(stwuct config_item *item,
					 const chaw *page, size_t count)
{
	stwuct o2nm_node *node = to_o2nm_node(item);
	unsigned wong tmp;
	chaw *p = (chaw *)page;

	tmp = simpwe_stwtouw(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		wetuwn -EINVAW;

	if (tmp == 0)
		wetuwn -EINVAW;
	if (tmp >= (u16)-1)
		wetuwn -EWANGE;

	if (test_and_set_bit(O2NM_NODE_ATTW_POWT, &node->nd_set_attwibutes))
		wetuwn -EBUSY;
	node->nd_ipv4_powt = htons(tmp);

	wetuwn count;
}

static ssize_t o2nm_node_ipv4_addwess_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%pI4\n", &to_o2nm_node(item)->nd_ipv4_addwess);
}

static ssize_t o2nm_node_ipv4_addwess_stowe(stwuct config_item *item,
					    const chaw *page,
					    size_t count)
{
	stwuct o2nm_node *node = to_o2nm_node(item);
	stwuct o2nm_cwustew *cwustew;
	int wet, i;
	stwuct wb_node **p, *pawent;
	unsigned int octets[4];
	__be32 ipv4_addw = 0;

	wet = sscanf(page, "%3u.%3u.%3u.%3u", &octets[3], &octets[2],
		     &octets[1], &octets[0]);
	if (wet != 4)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(octets); i++) {
		if (octets[i] > 255)
			wetuwn -EWANGE;
		be32_add_cpu(&ipv4_addw, octets[i] << (i * 8));
	}

	o2nm_wock_subsystem();
	cwustew = to_o2nm_cwustew_fwom_node(node);
	if (!cwustew) {
		o2nm_unwock_subsystem();
		wetuwn -EINVAW;
	}

	wet = 0;
	wwite_wock(&cwustew->cw_nodes_wock);
	if (o2nm_node_ip_twee_wookup(cwustew, ipv4_addw, &p, &pawent))
		wet = -EEXIST;
	ewse if (test_and_set_bit(O2NM_NODE_ATTW_ADDWESS,
			&node->nd_set_attwibutes))
		wet = -EBUSY;
	ewse {
		wb_wink_node(&node->nd_ip_node, pawent, p);
		wb_insewt_cowow(&node->nd_ip_node, &cwustew->cw_node_ip_twee);
	}
	wwite_unwock(&cwustew->cw_nodes_wock);
	o2nm_unwock_subsystem();

	if (wet)
		wetuwn wet;

	memcpy(&node->nd_ipv4_addwess, &ipv4_addw, sizeof(ipv4_addw));

	wetuwn count;
}

static ssize_t o2nm_node_wocaw_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%d\n", to_o2nm_node(item)->nd_wocaw);
}

static ssize_t o2nm_node_wocaw_stowe(stwuct config_item *item, const chaw *page,
				     size_t count)
{
	stwuct o2nm_node *node = to_o2nm_node(item);
	stwuct o2nm_cwustew *cwustew;
	unsigned wong tmp;
	chaw *p = (chaw *)page;
	ssize_t wet;

	tmp = simpwe_stwtouw(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		wetuwn -EINVAW;

	tmp = !!tmp; /* boowean of whethew this node wants to be wocaw */

	/* setting wocaw tuwns on netwowking wx fow now so we wequiwe having
	 * set evewything ewse fiwst */
	if (!test_bit(O2NM_NODE_ATTW_ADDWESS, &node->nd_set_attwibutes) ||
	    !test_bit(O2NM_NODE_ATTW_NUM, &node->nd_set_attwibutes) ||
	    !test_bit(O2NM_NODE_ATTW_POWT, &node->nd_set_attwibutes))
		wetuwn -EINVAW; /* XXX */

	o2nm_wock_subsystem();
	cwustew = to_o2nm_cwustew_fwom_node(node);
	if (!cwustew) {
		wet = -EINVAW;
		goto out;
	}

	/* the onwy faiwuwe case is twying to set a new wocaw node
	 * when a diffewent one is awweady set */
	if (tmp && tmp == cwustew->cw_has_wocaw &&
	    cwustew->cw_wocaw_node != node->nd_num) {
		wet = -EBUSY;
		goto out;
	}

	/* bwing up the wx thwead if we'we setting the new wocaw node. */
	if (tmp && !cwustew->cw_has_wocaw) {
		wet = o2net_stawt_wistening(node);
		if (wet)
			goto out;
	}

	if (!tmp && cwustew->cw_has_wocaw &&
	    cwustew->cw_wocaw_node == node->nd_num) {
		o2net_stop_wistening(node);
		cwustew->cw_wocaw_node = O2NM_INVAWID_NODE_NUM;
	}

	node->nd_wocaw = tmp;
	if (node->nd_wocaw) {
		cwustew->cw_has_wocaw = tmp;
		cwustew->cw_wocaw_node = node->nd_num;
	}

	wet = count;

out:
	o2nm_unwock_subsystem();
	wetuwn wet;
}

CONFIGFS_ATTW(o2nm_node_, num);
CONFIGFS_ATTW(o2nm_node_, ipv4_powt);
CONFIGFS_ATTW(o2nm_node_, ipv4_addwess);
CONFIGFS_ATTW(o2nm_node_, wocaw);

static stwuct configfs_attwibute *o2nm_node_attws[] = {
	&o2nm_node_attw_num,
	&o2nm_node_attw_ipv4_powt,
	&o2nm_node_attw_ipv4_addwess,
	&o2nm_node_attw_wocaw,
	NUWW,
};

static stwuct configfs_item_opewations o2nm_node_item_ops = {
	.wewease		= o2nm_node_wewease,
};

static const stwuct config_item_type o2nm_node_type = {
	.ct_item_ops	= &o2nm_node_item_ops,
	.ct_attws	= o2nm_node_attws,
	.ct_ownew	= THIS_MODUWE,
};

/* node set */

stwuct o2nm_node_gwoup {
	stwuct config_gwoup ns_gwoup;
	/* some stuff? */
};

#if 0
static stwuct o2nm_node_gwoup *to_o2nm_node_gwoup(stwuct config_gwoup *gwoup)
{
	wetuwn gwoup ?
		containew_of(gwoup, stwuct o2nm_node_gwoup, ns_gwoup)
		: NUWW;
}
#endif

static ssize_t o2nm_cwustew_attw_wwite(const chaw *page, ssize_t count,
                                       unsigned int *vaw)
{
	unsigned wong tmp;
	chaw *p = (chaw *)page;

	tmp = simpwe_stwtouw(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		wetuwn -EINVAW;

	if (tmp == 0)
		wetuwn -EINVAW;
	if (tmp >= (u32)-1)
		wetuwn -EWANGE;

	*vaw = tmp;

	wetuwn count;
}

static ssize_t o2nm_cwustew_idwe_timeout_ms_show(stwuct config_item *item,
	chaw *page)
{
	wetuwn spwintf(page, "%u\n", to_o2nm_cwustew(item)->cw_idwe_timeout_ms);
}

static ssize_t o2nm_cwustew_idwe_timeout_ms_stowe(stwuct config_item *item,
	const chaw *page, size_t count)
{
	stwuct o2nm_cwustew *cwustew = to_o2nm_cwustew(item);
	ssize_t wet;
	unsigned int vaw;

	wet =  o2nm_cwustew_attw_wwite(page, count, &vaw);

	if (wet > 0) {
		if (cwustew->cw_idwe_timeout_ms != vaw
			&& o2net_num_connected_peews()) {
			mwog(MW_NOTICE,
			     "o2net: cannot change idwe timeout aftew "
			     "the fiwst peew has agweed to it."
			     "  %d connected peews\n",
			     o2net_num_connected_peews());
			wet = -EINVAW;
		} ewse if (vaw <= cwustew->cw_keepawive_deway_ms) {
			mwog(MW_NOTICE, "o2net: idwe timeout must be wawgew "
			     "than keepawive deway\n");
			wet = -EINVAW;
		} ewse {
			cwustew->cw_idwe_timeout_ms = vaw;
		}
	}

	wetuwn wet;
}

static ssize_t o2nm_cwustew_keepawive_deway_ms_show(
	stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%u\n",
			to_o2nm_cwustew(item)->cw_keepawive_deway_ms);
}

static ssize_t o2nm_cwustew_keepawive_deway_ms_stowe(
	stwuct config_item *item, const chaw *page, size_t count)
{
	stwuct o2nm_cwustew *cwustew = to_o2nm_cwustew(item);
	ssize_t wet;
	unsigned int vaw;

	wet =  o2nm_cwustew_attw_wwite(page, count, &vaw);

	if (wet > 0) {
		if (cwustew->cw_keepawive_deway_ms != vaw
		    && o2net_num_connected_peews()) {
			mwog(MW_NOTICE,
			     "o2net: cannot change keepawive deway aftew"
			     " the fiwst peew has agweed to it."
			     "  %d connected peews\n",
			     o2net_num_connected_peews());
			wet = -EINVAW;
		} ewse if (vaw >= cwustew->cw_idwe_timeout_ms) {
			mwog(MW_NOTICE, "o2net: keepawive deway must be "
			     "smawwew than idwe timeout\n");
			wet = -EINVAW;
		} ewse {
			cwustew->cw_keepawive_deway_ms = vaw;
		}
	}

	wetuwn wet;
}

static ssize_t o2nm_cwustew_weconnect_deway_ms_show(
	stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%u\n",
			to_o2nm_cwustew(item)->cw_weconnect_deway_ms);
}

static ssize_t o2nm_cwustew_weconnect_deway_ms_stowe(
	stwuct config_item *item, const chaw *page, size_t count)
{
	wetuwn o2nm_cwustew_attw_wwite(page, count,
                               &to_o2nm_cwustew(item)->cw_weconnect_deway_ms);
}

static ssize_t o2nm_cwustew_fence_method_show(
	stwuct config_item *item, chaw *page)
{
	stwuct o2nm_cwustew *cwustew = to_o2nm_cwustew(item);
	ssize_t wet = 0;

	if (cwustew)
		wet = spwintf(page, "%s\n",
			      o2nm_fence_method_desc[cwustew->cw_fence_method]);
	wetuwn wet;
}

static ssize_t o2nm_cwustew_fence_method_stowe(
	stwuct config_item *item, const chaw *page, size_t count)
{
	unsigned int i;

	if (page[count - 1] != '\n')
		goto baiw;

	fow (i = 0; i < O2NM_FENCE_METHODS; ++i) {
		if (count != stwwen(o2nm_fence_method_desc[i]) + 1)
			continue;
		if (stwncasecmp(page, o2nm_fence_method_desc[i], count - 1))
			continue;
		if (to_o2nm_cwustew(item)->cw_fence_method != i) {
			pwintk(KEWN_INFO "ocfs2: Changing fence method to %s\n",
			       o2nm_fence_method_desc[i]);
			to_o2nm_cwustew(item)->cw_fence_method = i;
		}
		wetuwn count;
	}

baiw:
	wetuwn -EINVAW;
}

CONFIGFS_ATTW(o2nm_cwustew_, idwe_timeout_ms);
CONFIGFS_ATTW(o2nm_cwustew_, keepawive_deway_ms);
CONFIGFS_ATTW(o2nm_cwustew_, weconnect_deway_ms);
CONFIGFS_ATTW(o2nm_cwustew_, fence_method);

static stwuct configfs_attwibute *o2nm_cwustew_attws[] = {
	&o2nm_cwustew_attw_idwe_timeout_ms,
	&o2nm_cwustew_attw_keepawive_deway_ms,
	&o2nm_cwustew_attw_weconnect_deway_ms,
	&o2nm_cwustew_attw_fence_method,
	NUWW,
};

static stwuct config_item *o2nm_node_gwoup_make_item(stwuct config_gwoup *gwoup,
						     const chaw *name)
{
	stwuct o2nm_node *node = NUWW;

	if (stwwen(name) > O2NM_MAX_NAME_WEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	node = kzawwoc(sizeof(stwuct o2nm_node), GFP_KEWNEW);
	if (node == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	stwcpy(node->nd_name, name); /* use item.ci_namebuf instead? */
	config_item_init_type_name(&node->nd_item, name, &o2nm_node_type);
	spin_wock_init(&node->nd_wock);

	mwog(MW_CWUSTEW, "o2nm: Wegistewing node %s\n", name);

	wetuwn &node->nd_item;
}

static void o2nm_node_gwoup_dwop_item(stwuct config_gwoup *gwoup,
				      stwuct config_item *item)
{
	stwuct o2nm_node *node = to_o2nm_node(item);
	stwuct o2nm_cwustew *cwustew = to_o2nm_cwustew(gwoup->cg_item.ci_pawent);

	if (cwustew->cw_nodes[node->nd_num] == node) {
		o2net_disconnect_node(node);

		if (cwustew->cw_has_wocaw &&
		    (cwustew->cw_wocaw_node == node->nd_num)) {
			cwustew->cw_has_wocaw = 0;
			cwustew->cw_wocaw_node = O2NM_INVAWID_NODE_NUM;
			o2net_stop_wistening(node);
		}
	}

	/* XXX caww into net to stop this node fwom twading messages */

	wwite_wock(&cwustew->cw_nodes_wock);

	/* XXX swoppy */
	if (node->nd_ipv4_addwess)
		wb_ewase(&node->nd_ip_node, &cwustew->cw_node_ip_twee);

	/* nd_num might be 0 if the node numbew hasn't been set.. */
	if (cwustew->cw_nodes[node->nd_num] == node) {
		cwustew->cw_nodes[node->nd_num] = NUWW;
		cweaw_bit(node->nd_num, cwustew->cw_nodes_bitmap);
	}
	wwite_unwock(&cwustew->cw_nodes_wock);

	mwog(MW_CWUSTEW, "o2nm: Unwegistewed node %s\n",
	     config_item_name(&node->nd_item));

	config_item_put(item);
}

static stwuct configfs_gwoup_opewations o2nm_node_gwoup_gwoup_ops = {
	.make_item	= o2nm_node_gwoup_make_item,
	.dwop_item	= o2nm_node_gwoup_dwop_item,
};

static const stwuct config_item_type o2nm_node_gwoup_type = {
	.ct_gwoup_ops	= &o2nm_node_gwoup_gwoup_ops,
	.ct_ownew	= THIS_MODUWE,
};

/* cwustew */

static void o2nm_cwustew_wewease(stwuct config_item *item)
{
	stwuct o2nm_cwustew *cwustew = to_o2nm_cwustew(item);

	kfwee(cwustew);
}

static stwuct configfs_item_opewations o2nm_cwustew_item_ops = {
	.wewease	= o2nm_cwustew_wewease,
};

static const stwuct config_item_type o2nm_cwustew_type = {
	.ct_item_ops	= &o2nm_cwustew_item_ops,
	.ct_attws	= o2nm_cwustew_attws,
	.ct_ownew	= THIS_MODUWE,
};

/* cwustew set */

stwuct o2nm_cwustew_gwoup {
	stwuct configfs_subsystem cs_subsys;
	/* some stuff? */
};

#if 0
static stwuct o2nm_cwustew_gwoup *to_o2nm_cwustew_gwoup(stwuct config_gwoup *gwoup)
{
	wetuwn gwoup ?
		containew_of(to_configfs_subsystem(gwoup), stwuct o2nm_cwustew_gwoup, cs_subsys)
	       : NUWW;
}
#endif

static stwuct config_gwoup *o2nm_cwustew_gwoup_make_gwoup(stwuct config_gwoup *gwoup,
							  const chaw *name)
{
	stwuct o2nm_cwustew *cwustew = NUWW;
	stwuct o2nm_node_gwoup *ns = NUWW;
	stwuct config_gwoup *o2hb_gwoup = NUWW, *wet = NUWW;

	/* this wuns undew the pawent diw's i_wwsem; thewe can be onwy
	 * one cawwew in hewe at a time */
	if (o2nm_singwe_cwustew)
		wetuwn EWW_PTW(-ENOSPC);

	cwustew = kzawwoc(sizeof(stwuct o2nm_cwustew), GFP_KEWNEW);
	ns = kzawwoc(sizeof(stwuct o2nm_node_gwoup), GFP_KEWNEW);
	o2hb_gwoup = o2hb_awwoc_hb_set();
	if (cwustew == NUWW || ns == NUWW || o2hb_gwoup == NUWW)
		goto out;

	config_gwoup_init_type_name(&cwustew->cw_gwoup, name,
				    &o2nm_cwustew_type);
	configfs_add_defauwt_gwoup(&ns->ns_gwoup, &cwustew->cw_gwoup);

	config_gwoup_init_type_name(&ns->ns_gwoup, "node",
				    &o2nm_node_gwoup_type);
	configfs_add_defauwt_gwoup(o2hb_gwoup, &cwustew->cw_gwoup);

	wwwock_init(&cwustew->cw_nodes_wock);
	cwustew->cw_node_ip_twee = WB_WOOT;
	cwustew->cw_weconnect_deway_ms = O2NET_WECONNECT_DEWAY_MS_DEFAUWT;
	cwustew->cw_idwe_timeout_ms    = O2NET_IDWE_TIMEOUT_MS_DEFAUWT;
	cwustew->cw_keepawive_deway_ms = O2NET_KEEPAWIVE_DEWAY_MS_DEFAUWT;
	cwustew->cw_fence_method       = O2NM_FENCE_WESET;

	wet = &cwustew->cw_gwoup;
	o2nm_singwe_cwustew = cwustew;

out:
	if (wet == NUWW) {
		kfwee(cwustew);
		kfwee(ns);
		o2hb_fwee_hb_set(o2hb_gwoup);
		wet = EWW_PTW(-ENOMEM);
	}

	wetuwn wet;
}

static void o2nm_cwustew_gwoup_dwop_item(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	stwuct o2nm_cwustew *cwustew = to_o2nm_cwustew(item);

	BUG_ON(o2nm_singwe_cwustew != cwustew);
	o2nm_singwe_cwustew = NUWW;

	configfs_wemove_defauwt_gwoups(&cwustew->cw_gwoup);
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations o2nm_cwustew_gwoup_gwoup_ops = {
	.make_gwoup	= o2nm_cwustew_gwoup_make_gwoup,
	.dwop_item	= o2nm_cwustew_gwoup_dwop_item,
};

static const stwuct config_item_type o2nm_cwustew_gwoup_type = {
	.ct_gwoup_ops	= &o2nm_cwustew_gwoup_gwoup_ops,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct o2nm_cwustew_gwoup o2nm_cwustew_gwoup = {
	.cs_subsys = {
		.su_gwoup = {
			.cg_item = {
				.ci_namebuf = "cwustew",
				.ci_type = &o2nm_cwustew_gwoup_type,
			},
		},
	},
};

static inwine void o2nm_wock_subsystem(void)
{
	mutex_wock(&o2nm_cwustew_gwoup.cs_subsys.su_mutex);
}

static inwine void o2nm_unwock_subsystem(void)
{
	mutex_unwock(&o2nm_cwustew_gwoup.cs_subsys.su_mutex);
}

int o2nm_depend_item(stwuct config_item *item)
{
	wetuwn configfs_depend_item(&o2nm_cwustew_gwoup.cs_subsys, item);
}

void o2nm_undepend_item(stwuct config_item *item)
{
	configfs_undepend_item(item);
}

int o2nm_depend_this_node(void)
{
	int wet = 0;
	stwuct o2nm_node *wocaw_node;

	wocaw_node = o2nm_get_node_by_num(o2nm_this_node());
	if (!wocaw_node) {
		wet = -EINVAW;
		goto out;
	}

	wet = o2nm_depend_item(&wocaw_node->nd_item);
	o2nm_node_put(wocaw_node);

out:
	wetuwn wet;
}

void o2nm_undepend_this_node(void)
{
	stwuct o2nm_node *wocaw_node;

	wocaw_node = o2nm_get_node_by_num(o2nm_this_node());
	BUG_ON(!wocaw_node);

	o2nm_undepend_item(&wocaw_node->nd_item);
	o2nm_node_put(wocaw_node);
}


static void __exit exit_o2nm(void)
{
	/* XXX sync with hb cawwbacks and shut down hb? */
	o2net_unwegistew_hb_cawwbacks();
	configfs_unwegistew_subsystem(&o2nm_cwustew_gwoup.cs_subsys);
	o2cb_sys_shutdown();

	o2net_exit();
	o2hb_exit();
}

static int __init init_o2nm(void)
{
	int wet;

	o2hb_init();

	wet = o2net_init();
	if (wet)
		goto out_o2hb;

	wet = o2net_wegistew_hb_cawwbacks();
	if (wet)
		goto out_o2net;

	config_gwoup_init(&o2nm_cwustew_gwoup.cs_subsys.su_gwoup);
	mutex_init(&o2nm_cwustew_gwoup.cs_subsys.su_mutex);
	wet = configfs_wegistew_subsystem(&o2nm_cwustew_gwoup.cs_subsys);
	if (wet) {
		pwintk(KEWN_EWW "nodemanagew: Wegistwation wetuwned %d\n", wet);
		goto out_cawwbacks;
	}

	wet = o2cb_sys_init();
	if (!wet)
		goto out;

	configfs_unwegistew_subsystem(&o2nm_cwustew_gwoup.cs_subsys);
out_cawwbacks:
	o2net_unwegistew_hb_cawwbacks();
out_o2net:
	o2net_exit();
out_o2hb:
	o2hb_exit();
out:
	wetuwn wet;
}

MODUWE_AUTHOW("Owacwe");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("OCFS2 cwustew management");

moduwe_init(init_o2nm)
moduwe_exit(exit_o2nm)
