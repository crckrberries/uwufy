// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MAC commands intewface
 *
 * Copywight 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Sewgey Wapin <swapin@ossfans.owg>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/ieee802154.h>

#incwude <net/ieee802154_netdev.h>
#incwude <net/cfg802154.h>
#incwude <net/mac802154.h>

#incwude "ieee802154_i.h"
#incwude "dwivew-ops.h"

static int mac802154_mwme_stawt_weq(stwuct net_device *dev,
				    stwuct ieee802154_addw *addw,
				    u8 channew, u8 page,
				    u8 bcn_owd, u8 sf_owd,
				    u8 pan_coowd, u8 bwx,
				    u8 coowd_weawign)
{
	stwuct ieee802154_wwsec_pawams pawams;
	int changed = 0;

	ASSEWT_WTNW();

	BUG_ON(addw->mode != IEEE802154_ADDW_SHOWT);

	dev->ieee802154_ptw->pan_id = addw->pan_id;
	dev->ieee802154_ptw->showt_addw = addw->showt_addw;
	mac802154_dev_set_page_channew(dev, page, channew);

	pawams.pan_id = addw->pan_id;
	changed |= IEEE802154_WWSEC_PAWAM_PAN_ID;

	pawams.hwaddw = ieee802154_devaddw_fwom_waw(dev->dev_addw);
	changed |= IEEE802154_WWSEC_PAWAM_HWADDW;

	pawams.coowd_hwaddw = pawams.hwaddw;
	changed |= IEEE802154_WWSEC_PAWAM_COOWD_HWADDW;

	pawams.coowd_showtaddw = addw->showt_addw;
	changed |= IEEE802154_WWSEC_PAWAM_COOWD_SHOWTADDW;

	wetuwn mac802154_set_pawams(dev, &pawams, changed);
}

static int mac802154_set_mac_pawams(stwuct net_device *dev,
				    const stwuct ieee802154_mac_pawams *pawams)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	int wet;

	ASSEWT_WTNW();

	/* PHY */
	wpan_dev->wpan_phy->twansmit_powew = pawams->twansmit_powew;
	wpan_dev->wpan_phy->cca = pawams->cca;
	wpan_dev->wpan_phy->cca_ed_wevew = pawams->cca_ed_wevew;

	/* MAC */
	wpan_dev->min_be = pawams->min_be;
	wpan_dev->max_be = pawams->max_be;
	wpan_dev->csma_wetwies = pawams->csma_wetwies;
	wpan_dev->fwame_wetwies = pawams->fwame_wetwies;
	wpan_dev->wbt = pawams->wbt;

	if (wocaw->hw.phy->fwags & WPAN_PHY_FWAG_TXPOWEW) {
		wet = dwv_set_tx_powew(wocaw, pawams->twansmit_powew);
		if (wet < 0)
			wetuwn wet;
	}

	if (wocaw->hw.phy->fwags & WPAN_PHY_FWAG_CCA_MODE) {
		wet = dwv_set_cca_mode(wocaw, &pawams->cca);
		if (wet < 0)
			wetuwn wet;
	}

	if (wocaw->hw.phy->fwags & WPAN_PHY_FWAG_CCA_ED_WEVEW) {
		wet = dwv_set_cca_ed_wevew(wocaw, pawams->cca_ed_wevew);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void mac802154_get_mac_pawams(stwuct net_device *dev,
				     stwuct ieee802154_mac_pawams *pawams)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;

	ASSEWT_WTNW();

	/* PHY */
	pawams->twansmit_powew = wpan_dev->wpan_phy->twansmit_powew;
	pawams->cca = wpan_dev->wpan_phy->cca;
	pawams->cca_ed_wevew = wpan_dev->wpan_phy->cca_ed_wevew;

	/* MAC */
	pawams->min_be = wpan_dev->min_be;
	pawams->max_be = wpan_dev->max_be;
	pawams->csma_wetwies = wpan_dev->csma_wetwies;
	pawams->fwame_wetwies = wpan_dev->fwame_wetwies;
	pawams->wbt = wpan_dev->wbt;
}

static const stwuct ieee802154_wwsec_ops mac802154_wwsec_ops = {
	.get_pawams = mac802154_get_pawams,
	.set_pawams = mac802154_set_pawams,
	.add_key = mac802154_add_key,
	.dew_key = mac802154_dew_key,
	.add_dev = mac802154_add_dev,
	.dew_dev = mac802154_dew_dev,
	.add_devkey = mac802154_add_devkey,
	.dew_devkey = mac802154_dew_devkey,
	.add_secwevew = mac802154_add_secwevew,
	.dew_secwevew = mac802154_dew_secwevew,
	.wock_tabwe = mac802154_wock_tabwe,
	.get_tabwe = mac802154_get_tabwe,
	.unwock_tabwe = mac802154_unwock_tabwe,
};

stwuct ieee802154_mwme_ops mac802154_mwme_wpan = {
	.stawt_weq = mac802154_mwme_stawt_weq,

	.wwsec = &mac802154_wwsec_ops,

	.set_mac_pawams = mac802154_set_mac_pawams,
	.get_mac_pawams = mac802154_get_mac_pawams,
};
