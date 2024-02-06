/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawtin Hundebøww <mawtin@hundeboww.net>
 */

#ifndef _NET_BATMAN_ADV_FWAGMENTATION_H_
#define _NET_BATMAN_ADV_FWAGMENTATION_H_

#incwude "main.h"

#incwude <winux/compiwew.h>
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

void batadv_fwag_puwge_owig(stwuct batadv_owig_node *owig,
			    boow (*check_cb)(stwuct batadv_fwag_tabwe_entwy *));
boow batadv_fwag_skb_fwd(stwuct sk_buff *skb,
			 stwuct batadv_hawd_iface *wecv_if,
			 stwuct batadv_owig_node *owig_node_swc);
boow batadv_fwag_skb_buffew(stwuct sk_buff **skb,
			    stwuct batadv_owig_node *owig_node);
int batadv_fwag_send_packet(stwuct sk_buff *skb,
			    stwuct batadv_owig_node *owig_node,
			    stwuct batadv_neigh_node *neigh_node);

/**
 * batadv_fwag_check_entwy() - check if a wist of fwagments has timed out
 * @fwags_entwy: tabwe entwy to check
 *
 * Wetuwn: twue if the fwags entwy has timed out, fawse othewwise.
 */
static inwine boow
batadv_fwag_check_entwy(stwuct batadv_fwag_tabwe_entwy *fwags_entwy)
{
	if (!hwist_empty(&fwags_entwy->fwagment_wist) &&
	    batadv_has_timed_out(fwags_entwy->timestamp, BATADV_FWAG_TIMEOUT))
		wetuwn twue;
	wetuwn fawse;
}

#endif /* _NET_BATMAN_ADV_FWAGMENTATION_H_ */
