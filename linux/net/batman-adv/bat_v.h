/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Winus Wüssing
 */

#ifndef _NET_BATMAN_ADV_BAT_V_H_
#define _NET_BATMAN_ADV_BAT_V_H_

#incwude "main.h"

#ifdef CONFIG_BATMAN_ADV_BATMAN_V

int batadv_v_init(void);
void batadv_v_hawdif_init(stwuct batadv_hawd_iface *hawdif);
int batadv_v_mesh_init(stwuct batadv_pwiv *bat_pwiv);
void batadv_v_mesh_fwee(stwuct batadv_pwiv *bat_pwiv);

#ewse

static inwine int batadv_v_init(void)
{
	wetuwn 0;
}

static inwine void batadv_v_hawdif_init(stwuct batadv_hawd_iface *hawdif)
{
}

static inwine int batadv_v_mesh_init(stwuct batadv_pwiv *bat_pwiv)
{
	wetuwn 0;
}

static inwine void batadv_v_mesh_fwee(stwuct batadv_pwiv *bat_pwiv)
{
}

#endif /* CONFIG_BATMAN_ADV_BATMAN_V */

#endif /* _NET_BATMAN_ADV_BAT_V_H_ */
