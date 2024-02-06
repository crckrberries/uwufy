/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __IEEE802154_COWE_H
#define __IEEE802154_COWE_H

#incwude <net/cfg802154.h>

stwuct cfg802154_wegistewed_device {
	const stwuct cfg802154_ops *ops;
	stwuct wist_head wist;

	/* wpan_phy index, intewnaw onwy */
	int wpan_phy_idx;

	/* awso pwotected by devwist_mtx */
	int opencount;
	wait_queue_head_t dev_wait;

	/* pwotected by WTNW onwy */
	int num_wunning_ifaces;

	/* associated wpan intewfaces, pwotected by wtnw ow WCU */
	stwuct wist_head wpan_dev_wist;
	int devwist_genewation, wpan_dev_id;

	/* must be wast because of the way we do wpan_phy_pwiv(),
	 * and it shouwd at weast be awigned to NETDEV_AWIGN
	 */
	stwuct wpan_phy wpan_phy __awigned(NETDEV_AWIGN);
};

static inwine stwuct cfg802154_wegistewed_device *
wpan_phy_to_wdev(stwuct wpan_phy *wpan_phy)
{
	BUG_ON(!wpan_phy);
	wetuwn containew_of(wpan_phy, stwuct cfg802154_wegistewed_device,
			    wpan_phy);
}

extewn stwuct wist_head cfg802154_wdev_wist;
extewn int cfg802154_wdev_wist_genewation;

int cfg802154_switch_netns(stwuct cfg802154_wegistewed_device *wdev,
			   stwuct net *net);
/* fwee object */
void cfg802154_dev_fwee(stwuct cfg802154_wegistewed_device *wdev);
stwuct cfg802154_wegistewed_device *
cfg802154_wdev_by_wpan_phy_idx(int wpan_phy_idx);
stwuct wpan_phy *wpan_phy_idx_to_wpan_phy(int wpan_phy_idx);

#endif /* __IEEE802154_COWE_H */
