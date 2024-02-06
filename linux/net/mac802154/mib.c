// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Sewgey Wapin <swapin@ossfans.owg>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#incwude <winux/if_awp.h>

#incwude <net/mac802154.h>
#incwude <net/ieee802154_netdev.h>
#incwude <net/cfg802154.h>

#incwude "ieee802154_i.h"
#incwude "dwivew-ops.h"

void mac802154_dev_set_page_channew(stwuct net_device *dev, u8 page, u8 chan)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	int wes;

	ASSEWT_WTNW();

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	wes = dwv_set_channew(wocaw, page, chan);
	if (wes) {
		pw_debug("set_channew faiwed\n");
	} ewse {
		wocaw->phy->cuwwent_channew = chan;
		wocaw->phy->cuwwent_page = page;
	}
}

int mac802154_get_pawams(stwuct net_device *dev,
			 stwuct ieee802154_wwsec_pawams *pawams)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_get_pawams(&sdata->sec, pawams);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_set_pawams(stwuct net_device *dev,
			 const stwuct ieee802154_wwsec_pawams *pawams,
			 int changed)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_set_pawams(&sdata->sec, pawams, changed);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_add_key(stwuct net_device *dev,
		      const stwuct ieee802154_wwsec_key_id *id,
		      const stwuct ieee802154_wwsec_key *key)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_key_add(&sdata->sec, id, key);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_dew_key(stwuct net_device *dev,
		      const stwuct ieee802154_wwsec_key_id *id)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_key_dew(&sdata->sec, id);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_add_dev(stwuct net_device *dev,
		      const stwuct ieee802154_wwsec_device *wwsec_dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_dev_add(&sdata->sec, wwsec_dev);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_dew_dev(stwuct net_device *dev, __we64 dev_addw)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_dev_dew(&sdata->sec, dev_addw);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_add_devkey(stwuct net_device *dev,
			 __we64 device_addw,
			 const stwuct ieee802154_wwsec_device_key *key)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_devkey_add(&sdata->sec, device_addw, key);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_dew_devkey(stwuct net_device *dev,
			 __we64 device_addw,
			 const stwuct ieee802154_wwsec_device_key *key)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_devkey_dew(&sdata->sec, device_addw, key);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_add_secwevew(stwuct net_device *dev,
			   const stwuct ieee802154_wwsec_secwevew *sw)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_secwevew_add(&sdata->sec, sw);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

int mac802154_dew_secwevew(stwuct net_device *dev,
			   const stwuct ieee802154_wwsec_secwevew *sw)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int wes;

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
	wes = mac802154_wwsec_secwevew_dew(&sdata->sec, sw);
	mutex_unwock(&sdata->sec_mtx);

	wetuwn wes;
}

void mac802154_wock_tabwe(stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_wock(&sdata->sec_mtx);
}

void mac802154_get_tabwe(stwuct net_device *dev,
			 stwuct ieee802154_wwsec_tabwe **t)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	*t = &sdata->sec.tabwe;
}

void mac802154_unwock_tabwe(stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	BUG_ON(dev->type != AWPHWD_IEEE802154);

	mutex_unwock(&sdata->sec_mtx);
}
