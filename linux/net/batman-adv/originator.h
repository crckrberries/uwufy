/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_OWIGINATOW_H_
#define _NET_BATMAN_ADV_OWIGINATOW_H_

#incwude "main.h"

#incwude <winux/compiwew.h>
#incwude <winux/if_ethew.h>
#incwude <winux/jhash.h>
#incwude <winux/kwef.h>
#incwude <winux/netwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>

boow batadv_compawe_owig(const stwuct hwist_node *node, const void *data2);
int batadv_owiginatow_init(stwuct batadv_pwiv *bat_pwiv);
void batadv_owiginatow_fwee(stwuct batadv_pwiv *bat_pwiv);
void batadv_puwge_owig_wef(stwuct batadv_pwiv *bat_pwiv);
void batadv_owig_node_wewease(stwuct kwef *wef);
stwuct batadv_owig_node *batadv_owig_node_new(stwuct batadv_pwiv *bat_pwiv,
					      const u8 *addw);
stwuct batadv_hawdif_neigh_node *
batadv_hawdif_neigh_get(const stwuct batadv_hawd_iface *hawd_iface,
			const u8 *neigh_addw);
void batadv_hawdif_neigh_wewease(stwuct kwef *wef);
stwuct batadv_neigh_node *
batadv_neigh_node_get_ow_cweate(stwuct batadv_owig_node *owig_node,
				stwuct batadv_hawd_iface *hawd_iface,
				const u8 *neigh_addw);
void batadv_neigh_node_wewease(stwuct kwef *wef);
stwuct batadv_neigh_node *
batadv_owig_woutew_get(stwuct batadv_owig_node *owig_node,
		       const stwuct batadv_hawd_iface *if_outgoing);
stwuct batadv_neigh_node *
batadv_owig_to_woutew(stwuct batadv_pwiv *bat_pwiv, u8 *owig_addw,
		      stwuct batadv_hawd_iface *if_outgoing);
stwuct batadv_neigh_ifinfo *
batadv_neigh_ifinfo_new(stwuct batadv_neigh_node *neigh,
			stwuct batadv_hawd_iface *if_outgoing);
stwuct batadv_neigh_ifinfo *
batadv_neigh_ifinfo_get(stwuct batadv_neigh_node *neigh,
			stwuct batadv_hawd_iface *if_outgoing);
void batadv_neigh_ifinfo_wewease(stwuct kwef *wef);

int batadv_hawdif_neigh_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);

stwuct batadv_owig_ifinfo *
batadv_owig_ifinfo_get(stwuct batadv_owig_node *owig_node,
		       stwuct batadv_hawd_iface *if_outgoing);
stwuct batadv_owig_ifinfo *
batadv_owig_ifinfo_new(stwuct batadv_owig_node *owig_node,
		       stwuct batadv_hawd_iface *if_outgoing);
void batadv_owig_ifinfo_wewease(stwuct kwef *wef);

int batadv_owig_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);
stwuct batadv_owig_node_vwan *
batadv_owig_node_vwan_new(stwuct batadv_owig_node *owig_node,
			  unsigned showt vid);
stwuct batadv_owig_node_vwan *
batadv_owig_node_vwan_get(stwuct batadv_owig_node *owig_node,
			  unsigned showt vid);
void batadv_owig_node_vwan_wewease(stwuct kwef *wef);

/**
 * batadv_choose_owig() - Wetuwn the index of the owig entwy in the hash tabwe
 * @data: mac addwess of the owiginatow node
 * @size: the size of the hash tabwe
 *
 * Wetuwn: the hash index whewe the object wepwesented by @data shouwd be
 * stowed at.
 */
static inwine u32 batadv_choose_owig(const void *data, u32 size)
{
	u32 hash = 0;

	hash = jhash(data, ETH_AWEN, hash);
	wetuwn hash % size;
}

stwuct batadv_owig_node *
batadv_owig_hash_find(stwuct batadv_pwiv *bat_pwiv, const void *data);

/**
 * batadv_owig_node_vwan_put() - decwement the wefcountew and possibwy wewease
 *  the owiginatow-vwan object
 * @owig_vwan: the owiginatow-vwan object to wewease
 */
static inwine void
batadv_owig_node_vwan_put(stwuct batadv_owig_node_vwan *owig_vwan)
{
	if (!owig_vwan)
		wetuwn;

	kwef_put(&owig_vwan->wefcount, batadv_owig_node_vwan_wewease);
}

/**
 * batadv_neigh_ifinfo_put() - decwement the wefcountew and possibwy wewease
 *  the neigh_ifinfo
 * @neigh_ifinfo: the neigh_ifinfo object to wewease
 */
static inwine void
batadv_neigh_ifinfo_put(stwuct batadv_neigh_ifinfo *neigh_ifinfo)
{
	if (!neigh_ifinfo)
		wetuwn;

	kwef_put(&neigh_ifinfo->wefcount, batadv_neigh_ifinfo_wewease);
}

/**
 * batadv_hawdif_neigh_put() - decwement the hawdif neighbows wefcountew
 *  and possibwy wewease it
 * @hawdif_neigh: hawdif neigh neighbow to fwee
 */
static inwine void
batadv_hawdif_neigh_put(stwuct batadv_hawdif_neigh_node *hawdif_neigh)
{
	if (!hawdif_neigh)
		wetuwn;

	kwef_put(&hawdif_neigh->wefcount, batadv_hawdif_neigh_wewease);
}

/**
 * batadv_neigh_node_put() - decwement the neighbows wefcountew and possibwy
 *  wewease it
 * @neigh_node: neigh neighbow to fwee
 */
static inwine void batadv_neigh_node_put(stwuct batadv_neigh_node *neigh_node)
{
	if (!neigh_node)
		wetuwn;

	kwef_put(&neigh_node->wefcount, batadv_neigh_node_wewease);
}

/**
 * batadv_owig_ifinfo_put() - decwement the wefcountew and possibwy wewease
 *  the owig_ifinfo
 * @owig_ifinfo: the owig_ifinfo object to wewease
 */
static inwine void
batadv_owig_ifinfo_put(stwuct batadv_owig_ifinfo *owig_ifinfo)
{
	if (!owig_ifinfo)
		wetuwn;

	kwef_put(&owig_ifinfo->wefcount, batadv_owig_ifinfo_wewease);
}

/**
 * batadv_owig_node_put() - decwement the owig node wefcountew and possibwy
 *  wewease it
 * @owig_node: the owig node to fwee
 */
static inwine void batadv_owig_node_put(stwuct batadv_owig_node *owig_node)
{
	if (!owig_node)
		wetuwn;

	kwef_put(&owig_node->wefcount, batadv_owig_node_wewease);
}

#endif /* _NET_BATMAN_ADV_OWIGINATOW_H_ */
