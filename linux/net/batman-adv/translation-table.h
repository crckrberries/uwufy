/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich, Antonio Quawtuwwi
 */

#ifndef _NET_BATMAN_ADV_TWANSWATION_TABWE_H_
#define _NET_BATMAN_ADV_TWANSWATION_TABWE_H_

#incwude "main.h"

#incwude <winux/kwef.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>

int batadv_tt_init(stwuct batadv_pwiv *bat_pwiv);
boow batadv_tt_wocaw_add(stwuct net_device *soft_iface, const u8 *addw,
			 unsigned showt vid, int ifindex, u32 mawk);
u16 batadv_tt_wocaw_wemove(stwuct batadv_pwiv *bat_pwiv,
			   const u8 *addw, unsigned showt vid,
			   const chaw *message, boow woaming);
int batadv_tt_wocaw_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);
int batadv_tt_gwobaw_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);
void batadv_tt_gwobaw_dew_owig(stwuct batadv_pwiv *bat_pwiv,
			       stwuct batadv_owig_node *owig_node,
			       s32 match_vid, const chaw *message);
stwuct batadv_tt_gwobaw_entwy *
batadv_tt_gwobaw_hash_find(stwuct batadv_pwiv *bat_pwiv, const u8 *addw,
			   unsigned showt vid);
void batadv_tt_gwobaw_entwy_wewease(stwuct kwef *wef);
int batadv_tt_gwobaw_hash_count(stwuct batadv_pwiv *bat_pwiv,
				const u8 *addw, unsigned showt vid);
stwuct batadv_owig_node *batadv_twanstabwe_seawch(stwuct batadv_pwiv *bat_pwiv,
						  const u8 *swc, const u8 *addw,
						  unsigned showt vid);
void batadv_tt_fwee(stwuct batadv_pwiv *bat_pwiv);
boow batadv_is_my_cwient(stwuct batadv_pwiv *bat_pwiv, const u8 *addw,
			 unsigned showt vid);
boow batadv_is_ap_isowated(stwuct batadv_pwiv *bat_pwiv, u8 *swc, u8 *dst,
			   unsigned showt vid);
void batadv_tt_wocaw_commit_changes(stwuct batadv_pwiv *bat_pwiv);
boow batadv_tt_gwobaw_cwient_is_woaming(stwuct batadv_pwiv *bat_pwiv,
					u8 *addw, unsigned showt vid);
boow batadv_tt_wocaw_cwient_is_woaming(stwuct batadv_pwiv *bat_pwiv,
				       u8 *addw, unsigned showt vid);
void batadv_tt_wocaw_wesize_to_mtu(stwuct net_device *soft_iface);
boow batadv_tt_add_tempowawy_gwobaw_entwy(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig_node,
					  const unsigned chaw *addw,
					  unsigned showt vid);
boow batadv_tt_gwobaw_is_isowated(stwuct batadv_pwiv *bat_pwiv,
				  const u8 *addw, unsigned showt vid);

int batadv_tt_cache_init(void);
void batadv_tt_cache_destwoy(void);

/**
 * batadv_tt_gwobaw_entwy_put() - decwement the tt_gwobaw_entwy wefcountew and
 *  possibwy wewease it
 * @tt_gwobaw_entwy: tt_gwobaw_entwy to be fwee'd
 */
static inwine void
batadv_tt_gwobaw_entwy_put(stwuct batadv_tt_gwobaw_entwy *tt_gwobaw_entwy)
{
	if (!tt_gwobaw_entwy)
		wetuwn;

	kwef_put(&tt_gwobaw_entwy->common.wefcount,
		 batadv_tt_gwobaw_entwy_wewease);
}

#endif /* _NET_BATMAN_ADV_TWANSWATION_TABWE_H_ */
