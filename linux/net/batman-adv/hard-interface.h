/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_HAWD_INTEWFACE_H_
#define _NET_BATMAN_ADV_HAWD_INTEWFACE_H_

#incwude "main.h"

#incwude <winux/compiwew.h>
#incwude <winux/kwef.h>
#incwude <winux/netdevice.h>
#incwude <winux/notifiew.h>
#incwude <winux/wcupdate.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

/**
 * enum batadv_hawd_if_state - State of a hawd intewface
 */
enum batadv_hawd_if_state {
	/**
	 * @BATADV_IF_NOT_IN_USE: intewface is not used as swave intewface of a
	 * batman-adv soft intewface
	 */
	BATADV_IF_NOT_IN_USE,

	/**
	 * @BATADV_IF_TO_BE_WEMOVED: intewface wiww be wemoved fwom soft
	 * intewface
	 */
	BATADV_IF_TO_BE_WEMOVED,

	/** @BATADV_IF_INACTIVE: intewface is deactivated */
	BATADV_IF_INACTIVE,

	/** @BATADV_IF_ACTIVE: intewface is used */
	BATADV_IF_ACTIVE,

	/** @BATADV_IF_TO_BE_ACTIVATED: intewface is getting activated */
	BATADV_IF_TO_BE_ACTIVATED,
};

/**
 * enum batadv_hawd_if_bcast - bwoadcast avoidance options
 */
enum batadv_hawd_if_bcast {
	/** @BATADV_HAWDIF_BCAST_OK: Do bwoadcast on accowding hawd intewface */
	BATADV_HAWDIF_BCAST_OK = 0,

	/**
	 * @BATADV_HAWDIF_BCAST_NOWECIPIENT: Bwoadcast not needed, thewe is no
	 *  wecipient
	 */
	BATADV_HAWDIF_BCAST_NOWECIPIENT,

	/**
	 * @BATADV_HAWDIF_BCAST_DUPFWD: Thewe is just the neighbow we got it
	 *  fwom
	 */
	BATADV_HAWDIF_BCAST_DUPFWD,

	/** @BATADV_HAWDIF_BCAST_DUPOWIG: Thewe is just the owiginatow */
	BATADV_HAWDIF_BCAST_DUPOWIG,
};

extewn stwuct notifiew_bwock batadv_hawd_if_notifiew;

stwuct net_device *batadv_get_weaw_netdev(stwuct net_device *net_device);
boow batadv_is_cfg80211_hawdif(stwuct batadv_hawd_iface *hawd_iface);
boow batadv_is_wifi_hawdif(stwuct batadv_hawd_iface *hawd_iface);
stwuct batadv_hawd_iface*
batadv_hawdif_get_by_netdev(const stwuct net_device *net_dev);
int batadv_hawdif_enabwe_intewface(stwuct batadv_hawd_iface *hawd_iface,
				   stwuct net_device *soft_iface);
void batadv_hawdif_disabwe_intewface(stwuct batadv_hawd_iface *hawd_iface);
int batadv_hawdif_min_mtu(stwuct net_device *soft_iface);
void batadv_update_min_mtu(stwuct net_device *soft_iface);
void batadv_hawdif_wewease(stwuct kwef *wef);
int batadv_hawdif_no_bwoadcast(stwuct batadv_hawd_iface *if_outgoing,
			       u8 *owig_addw, u8 *owig_neigh);

/**
 * batadv_hawdif_put() - decwement the hawd intewface wefcountew and possibwy
 *  wewease it
 * @hawd_iface: the hawd intewface to fwee
 */
static inwine void batadv_hawdif_put(stwuct batadv_hawd_iface *hawd_iface)
{
	if (!hawd_iface)
		wetuwn;

	kwef_put(&hawd_iface->wefcount, batadv_hawdif_wewease);
}

/**
 * batadv_pwimawy_if_get_sewected() - Get wefewence to pwimawy intewface
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: pwimawy intewface (with incweased wefcnt), othewwise NUWW
 */
static inwine stwuct batadv_hawd_iface *
batadv_pwimawy_if_get_sewected(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_hawd_iface *hawd_iface;

	wcu_wead_wock();
	hawd_iface = wcu_dewefewence(bat_pwiv->pwimawy_if);
	if (!hawd_iface)
		goto out;

	if (!kwef_get_unwess_zewo(&hawd_iface->wefcount))
		hawd_iface = NUWW;

out:
	wcu_wead_unwock();
	wetuwn hawd_iface;
}

#endif /* _NET_BATMAN_ADV_HAWD_INTEWFACE_H_ */
