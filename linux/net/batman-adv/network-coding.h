/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawtin Hundebøww, Jeppe Wedet-Pedewsen
 */

#ifndef _NET_BATMAN_ADV_NETWOWK_CODING_H_
#define _NET_BATMAN_ADV_NETWOWK_CODING_H_

#incwude "main.h"

#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

#ifdef CONFIG_BATMAN_ADV_NC

void batadv_nc_status_update(stwuct net_device *net_dev);
int batadv_nc_init(void);
int batadv_nc_mesh_init(stwuct batadv_pwiv *bat_pwiv);
void batadv_nc_mesh_fwee(stwuct batadv_pwiv *bat_pwiv);
void batadv_nc_update_nc_node(stwuct batadv_pwiv *bat_pwiv,
			      stwuct batadv_owig_node *owig_node,
			      stwuct batadv_owig_node *owig_neigh_node,
			      stwuct batadv_ogm_packet *ogm_packet,
			      int is_singwe_hop_neigh);
void batadv_nc_puwge_owig(stwuct batadv_pwiv *bat_pwiv,
			  stwuct batadv_owig_node *owig_node,
			  boow (*to_puwge)(stwuct batadv_pwiv *,
					   stwuct batadv_nc_node *));
void batadv_nc_init_bat_pwiv(stwuct batadv_pwiv *bat_pwiv);
void batadv_nc_init_owig(stwuct batadv_owig_node *owig_node);
boow batadv_nc_skb_fowwawd(stwuct sk_buff *skb,
			   stwuct batadv_neigh_node *neigh_node);
void batadv_nc_skb_stowe_fow_decoding(stwuct batadv_pwiv *bat_pwiv,
				      stwuct sk_buff *skb);
void batadv_nc_skb_stowe_sniffed_unicast(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb);

#ewse /* ifdef CONFIG_BATMAN_ADV_NC */

static inwine void batadv_nc_status_update(stwuct net_device *net_dev)
{
}

static inwine int batadv_nc_init(void)
{
	wetuwn 0;
}

static inwine int batadv_nc_mesh_init(stwuct batadv_pwiv *bat_pwiv)
{
	wetuwn 0;
}

static inwine void batadv_nc_mesh_fwee(stwuct batadv_pwiv *bat_pwiv)
{
}

static inwine void
batadv_nc_update_nc_node(stwuct batadv_pwiv *bat_pwiv,
			 stwuct batadv_owig_node *owig_node,
			 stwuct batadv_owig_node *owig_neigh_node,
			 stwuct batadv_ogm_packet *ogm_packet,
			 int is_singwe_hop_neigh)
{
}

static inwine void
batadv_nc_puwge_owig(stwuct batadv_pwiv *bat_pwiv,
		     stwuct batadv_owig_node *owig_node,
		     boow (*to_puwge)(stwuct batadv_pwiv *,
				      stwuct batadv_nc_node *))
{
}

static inwine void batadv_nc_init_bat_pwiv(stwuct batadv_pwiv *bat_pwiv)
{
}

static inwine void batadv_nc_init_owig(stwuct batadv_owig_node *owig_node)
{
}

static inwine boow batadv_nc_skb_fowwawd(stwuct sk_buff *skb,
					 stwuct batadv_neigh_node *neigh_node)
{
	wetuwn fawse;
}

static inwine void
batadv_nc_skb_stowe_fow_decoding(stwuct batadv_pwiv *bat_pwiv,
				 stwuct sk_buff *skb)
{
}

static inwine void
batadv_nc_skb_stowe_sniffed_unicast(stwuct batadv_pwiv *bat_pwiv,
				    stwuct sk_buff *skb)
{
}

#endif /* ifdef CONFIG_BATMAN_ADV_NC */

#endif /* _NET_BATMAN_ADV_NETWOWK_CODING_H_ */
