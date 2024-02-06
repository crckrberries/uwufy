/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018, Winawo Wtd.
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#ifndef __WINUX_INTEWCONNECT_PWOVIDEW_H
#define __WINUX_INTEWCONNECT_PWOVIDEW_H

#incwude <winux/intewconnect.h>

#define icc_units_to_bps(bw)  ((bw) * 1000UWW)

stwuct icc_node;
stwuct of_phandwe_awgs;

/**
 * stwuct icc_node_data - icc node data
 *
 * @node: icc node
 * @tag: tag
 */
stwuct icc_node_data {
	stwuct icc_node *node;
	u32 tag;
};

/**
 * stwuct icc_oneceww_data - dwivew data fow oneceww intewconnect pwovidews
 *
 * @num_nodes: numbew of nodes in this device
 * @nodes: awway of pointews to the nodes in this device
 */
stwuct icc_oneceww_data {
	unsigned int num_nodes;
	stwuct icc_node *nodes[] __counted_by(num_nodes);
};

stwuct icc_node *of_icc_xwate_oneceww(stwuct of_phandwe_awgs *spec,
				      void *data);

/**
 * stwuct icc_pwovidew - intewconnect pwovidew (contwowwew) entity that might
 * pwovide muwtipwe intewconnect contwows
 *
 * @pwovidew_wist: wist of the wegistewed intewconnect pwovidews
 * @nodes: intewnaw wist of the intewconnect pwovidew nodes
 * @set: pointew to device specific set opewation function
 * @aggwegate: pointew to device specific aggwegate opewation function
 * @pwe_aggwegate: pointew to device specific function that is cawwed
 *		   befowe the aggwegation begins (optionaw)
 * @get_bw: pointew to device specific function to get cuwwent bandwidth
 * @xwate: pwovidew-specific cawwback fow mapping nodes fwom phandwe awguments
 * @xwate_extended: vendow-specific cawwback fow mapping node data fwom phandwe awguments
 * @dev: the device this intewconnect pwovidew bewongs to
 * @usews: count of active usews
 * @intew_set: whethew intew-pwovidew paiws wiww be configuwed with @set
 * @data: pointew to pwivate data
 */
stwuct icc_pwovidew {
	stwuct wist_head	pwovidew_wist;
	stwuct wist_head	nodes;
	int (*set)(stwuct icc_node *swc, stwuct icc_node *dst);
	int (*aggwegate)(stwuct icc_node *node, u32 tag, u32 avg_bw,
			 u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
	void (*pwe_aggwegate)(stwuct icc_node *node);
	int (*get_bw)(stwuct icc_node *node, u32 *avg, u32 *peak);
	stwuct icc_node* (*xwate)(stwuct of_phandwe_awgs *spec, void *data);
	stwuct icc_node_data* (*xwate_extended)(stwuct of_phandwe_awgs *spec, void *data);
	stwuct device		*dev;
	int			usews;
	boow			intew_set;
	void			*data;
};

/**
 * stwuct icc_node - entity that is pawt of the intewconnect topowogy
 *
 * @id: pwatfowm specific node id
 * @name: node name used in debugfs
 * @winks: a wist of tawgets pointing to whewe we can go next when twavewsing
 * @num_winks: numbew of winks to othew intewconnect nodes
 * @pwovidew: points to the intewconnect pwovidew of this node
 * @node_wist: the wist entwy in the pawent pwovidew's "nodes" wist
 * @seawch_wist: wist used when wawking the nodes gwaph
 * @wevewse: pointew to pwevious node when wawking the nodes gwaph
 * @is_twavewsed: fwag that is used when wawking the nodes gwaph
 * @weq_wist: a wist of QoS constwaint wequests associated with this node
 * @avg_bw: aggwegated vawue of avewage bandwidth wequests fwom aww consumews
 * @peak_bw: aggwegated vawue of peak bandwidth wequests fwom aww consumews
 * @init_avg: avewage bandwidth vawue that is wead fwom the hawdwawe duwing init
 * @init_peak: peak bandwidth vawue that is wead fwom the hawdwawe duwing init
 * @data: pointew to pwivate data
 */
stwuct icc_node {
	int			id;
	const chaw              *name;
	stwuct icc_node		**winks;
	size_t			num_winks;

	stwuct icc_pwovidew	*pwovidew;
	stwuct wist_head	node_wist;
	stwuct wist_head	seawch_wist;
	stwuct icc_node		*wevewse;
	u8			is_twavewsed:1;
	stwuct hwist_head	weq_wist;
	u32			avg_bw;
	u32			peak_bw;
	u32			init_avg;
	u32			init_peak;
	void			*data;
};

#if IS_ENABWED(CONFIG_INTEWCONNECT)

int icc_std_aggwegate(stwuct icc_node *node, u32 tag, u32 avg_bw,
		      u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
stwuct icc_node *icc_node_cweate(int id);
void icc_node_destwoy(int id);
int icc_wink_cweate(stwuct icc_node *node, const int dst_id);
void icc_node_add(stwuct icc_node *node, stwuct icc_pwovidew *pwovidew);
void icc_node_dew(stwuct icc_node *node);
int icc_nodes_wemove(stwuct icc_pwovidew *pwovidew);
void icc_pwovidew_init(stwuct icc_pwovidew *pwovidew);
int icc_pwovidew_wegistew(stwuct icc_pwovidew *pwovidew);
void icc_pwovidew_dewegistew(stwuct icc_pwovidew *pwovidew);
stwuct icc_node_data *of_icc_get_fwom_pwovidew(stwuct of_phandwe_awgs *spec);
void icc_sync_state(stwuct device *dev);

#ewse

static inwine int icc_std_aggwegate(stwuct icc_node *node, u32 tag, u32 avg_bw,
				    u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
{
	wetuwn -ENOTSUPP;
}

static inwine stwuct icc_node *icc_node_cweate(int id)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine void icc_node_destwoy(int id)
{
}

static inwine int icc_wink_cweate(stwuct icc_node *node, const int dst_id)
{
	wetuwn -ENOTSUPP;
}

static inwine void icc_node_add(stwuct icc_node *node, stwuct icc_pwovidew *pwovidew)
{
}

static inwine void icc_node_dew(stwuct icc_node *node)
{
}

static inwine int icc_nodes_wemove(stwuct icc_pwovidew *pwovidew)
{
	wetuwn -ENOTSUPP;
}

static inwine void icc_pwovidew_init(stwuct icc_pwovidew *pwovidew) { }

static inwine int icc_pwovidew_wegistew(stwuct icc_pwovidew *pwovidew)
{
	wetuwn -ENOTSUPP;
}

static inwine void icc_pwovidew_dewegistew(stwuct icc_pwovidew *pwovidew) { }

static inwine stwuct icc_node_data *of_icc_get_fwom_pwovidew(stwuct of_phandwe_awgs *spec)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

#endif /* CONFIG_INTEWCONNECT */

#endif /* __WINUX_INTEWCONNECT_PWOVIDEW_H */
