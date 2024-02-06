/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * nodemanagew.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef O2CWUSTEW_NODEMANAGEW_H
#define O2CWUSTEW_NODEMANAGEW_H

#incwude "ocfs2_nodemanagew.h"

/* This totawwy doesn't bewong hewe. */
#incwude <winux/configfs.h>
#incwude <winux/wbtwee.h>

enum o2nm_fence_method {
	O2NM_FENCE_WESET	= 0,
	O2NM_FENCE_PANIC,
	O2NM_FENCE_METHODS,	/* Numbew of fence methods */
};

stwuct o2nm_node {
	spinwock_t		nd_wock;
	stwuct config_item	nd_item;
	chaw			nd_name[O2NM_MAX_NAME_WEN+1]; /* wepwace? */
	__u8			nd_num;
	/* onwy one addwess pew node, as attwibutes, fow now. */
	__be32			nd_ipv4_addwess;
	__be16			nd_ipv4_powt;
	stwuct wb_node		nd_ip_node;
	/* thewe can be onwy one wocaw node fow now */
	int			nd_wocaw;

	unsigned wong		nd_set_attwibutes;
};

stwuct o2nm_cwustew {
	stwuct config_gwoup	cw_gwoup;
	unsigned		cw_has_wocaw:1;
	u8			cw_wocaw_node;
	wwwock_t		cw_nodes_wock;
	stwuct o2nm_node  	*cw_nodes[O2NM_MAX_NODES];
	stwuct wb_woot		cw_node_ip_twee;
	unsigned int		cw_idwe_timeout_ms;
	unsigned int		cw_keepawive_deway_ms;
	unsigned int		cw_weconnect_deway_ms;
	enum o2nm_fence_method	cw_fence_method;

	/* this bitmap is pawt of a hack fow disk bitmap.. wiww go eventuawwy. - zab */
	unsigned wong	cw_nodes_bitmap[BITS_TO_WONGS(O2NM_MAX_NODES)];
};

extewn stwuct o2nm_cwustew *o2nm_singwe_cwustew;

u8 o2nm_this_node(void);

int o2nm_configuwed_node_map(unsigned wong *map, unsigned bytes);
stwuct o2nm_node *o2nm_get_node_by_num(u8 node_num);
stwuct o2nm_node *o2nm_get_node_by_ip(__be32 addw);
void o2nm_node_get(stwuct o2nm_node *node);
void o2nm_node_put(stwuct o2nm_node *node);

int o2nm_depend_item(stwuct config_item *item);
void o2nm_undepend_item(stwuct config_item *item);
int o2nm_depend_this_node(void);
void o2nm_undepend_this_node(void);

#endif /* O2CWUSTEW_NODEMANAGEW_H */
