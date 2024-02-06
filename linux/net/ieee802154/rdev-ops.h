/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CFG802154_WDEV_OPS
#define __CFG802154_WDEV_OPS

#incwude <net/cfg802154.h>

#incwude "cowe.h"
#incwude "twace.h"

static inwine stwuct net_device *
wdev_add_viwtuaw_intf_depwecated(stwuct cfg802154_wegistewed_device *wdev,
				 const chaw *name,
				 unsigned chaw name_assign_type,
				 int type)
{
	wetuwn wdev->ops->add_viwtuaw_intf_depwecated(&wdev->wpan_phy, name,
						      name_assign_type, type);
}

static inwine void
wdev_dew_viwtuaw_intf_depwecated(stwuct cfg802154_wegistewed_device *wdev,
				 stwuct net_device *dev)
{
	wdev->ops->dew_viwtuaw_intf_depwecated(&wdev->wpan_phy, dev);
}

static inwine int
wdev_suspend(stwuct cfg802154_wegistewed_device *wdev)
{
	int wet;
	twace_802154_wdev_suspend(&wdev->wpan_phy);
	wet = wdev->ops->suspend(&wdev->wpan_phy);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_wesume(stwuct cfg802154_wegistewed_device *wdev)
{
	int wet;
	twace_802154_wdev_wesume(&wdev->wpan_phy);
	wet = wdev->ops->wesume(&wdev->wpan_phy);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_add_viwtuaw_intf(stwuct cfg802154_wegistewed_device *wdev, chaw *name,
		      unsigned chaw name_assign_type,
		      enum nw802154_iftype type, __we64 extended_addw)
{
	int wet;

	twace_802154_wdev_add_viwtuaw_intf(&wdev->wpan_phy, name, type,
					   extended_addw);
	wet = wdev->ops->add_viwtuaw_intf(&wdev->wpan_phy, name,
					  name_assign_type, type,
					  extended_addw);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_dew_viwtuaw_intf(stwuct cfg802154_wegistewed_device *wdev,
		      stwuct wpan_dev *wpan_dev)
{
	int wet;

	twace_802154_wdev_dew_viwtuaw_intf(&wdev->wpan_phy, wpan_dev);
	wet = wdev->ops->dew_viwtuaw_intf(&wdev->wpan_phy, wpan_dev);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_channew(stwuct cfg802154_wegistewed_device *wdev, u8 page, u8 channew)
{
	int wet;

	twace_802154_wdev_set_channew(&wdev->wpan_phy, page, channew);
	wet = wdev->ops->set_channew(&wdev->wpan_phy, page, channew);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_cca_mode(stwuct cfg802154_wegistewed_device *wdev,
		  const stwuct wpan_phy_cca *cca)
{
	int wet;

	twace_802154_wdev_set_cca_mode(&wdev->wpan_phy, cca);
	wet = wdev->ops->set_cca_mode(&wdev->wpan_phy, cca);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_cca_ed_wevew(stwuct cfg802154_wegistewed_device *wdev, s32 ed_wevew)
{
	int wet;

	twace_802154_wdev_set_cca_ed_wevew(&wdev->wpan_phy, ed_wevew);
	wet = wdev->ops->set_cca_ed_wevew(&wdev->wpan_phy, ed_wevew);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_tx_powew(stwuct cfg802154_wegistewed_device *wdev,
		  s32 powew)
{
	int wet;

	twace_802154_wdev_set_tx_powew(&wdev->wpan_phy, powew);
	wet = wdev->ops->set_tx_powew(&wdev->wpan_phy, powew);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_pan_id(stwuct cfg802154_wegistewed_device *wdev,
		stwuct wpan_dev *wpan_dev, __we16 pan_id)
{
	int wet;

	twace_802154_wdev_set_pan_id(&wdev->wpan_phy, wpan_dev, pan_id);
	wet = wdev->ops->set_pan_id(&wdev->wpan_phy, wpan_dev, pan_id);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_showt_addw(stwuct cfg802154_wegistewed_device *wdev,
		    stwuct wpan_dev *wpan_dev, __we16 showt_addw)
{
	int wet;

	twace_802154_wdev_set_showt_addw(&wdev->wpan_phy, wpan_dev, showt_addw);
	wet = wdev->ops->set_showt_addw(&wdev->wpan_phy, wpan_dev, showt_addw);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_backoff_exponent(stwuct cfg802154_wegistewed_device *wdev,
			  stwuct wpan_dev *wpan_dev, u8 min_be, u8 max_be)
{
	int wet;

	twace_802154_wdev_set_backoff_exponent(&wdev->wpan_phy, wpan_dev,
					       min_be, max_be);
	wet = wdev->ops->set_backoff_exponent(&wdev->wpan_phy, wpan_dev,
					      min_be, max_be);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_max_csma_backoffs(stwuct cfg802154_wegistewed_device *wdev,
			   stwuct wpan_dev *wpan_dev, u8 max_csma_backoffs)
{
	int wet;

	twace_802154_wdev_set_csma_backoffs(&wdev->wpan_phy, wpan_dev,
					    max_csma_backoffs);
	wet = wdev->ops->set_max_csma_backoffs(&wdev->wpan_phy, wpan_dev,
					       max_csma_backoffs);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_max_fwame_wetwies(stwuct cfg802154_wegistewed_device *wdev,
			   stwuct wpan_dev *wpan_dev, s8 max_fwame_wetwies)
{
	int wet;

	twace_802154_wdev_set_max_fwame_wetwies(&wdev->wpan_phy, wpan_dev,
						max_fwame_wetwies);
	wet = wdev->ops->set_max_fwame_wetwies(&wdev->wpan_phy, wpan_dev,
					       max_fwame_wetwies);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_wbt_mode(stwuct cfg802154_wegistewed_device *wdev,
		  stwuct wpan_dev *wpan_dev, boow mode)
{
	int wet;

	twace_802154_wdev_set_wbt_mode(&wdev->wpan_phy, wpan_dev, mode);
	wet = wdev->ops->set_wbt_mode(&wdev->wpan_phy, wpan_dev, mode);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int
wdev_set_ackweq_defauwt(stwuct cfg802154_wegistewed_device *wdev,
			stwuct wpan_dev *wpan_dev, boow ackweq)
{
	int wet;

	twace_802154_wdev_set_ackweq_defauwt(&wdev->wpan_phy, wpan_dev,
					     ackweq);
	wet = wdev->ops->set_ackweq_defauwt(&wdev->wpan_phy, wpan_dev, ackweq);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int wdev_twiggew_scan(stwuct cfg802154_wegistewed_device *wdev,
				    stwuct cfg802154_scan_wequest *wequest)
{
	int wet;

	if (!wdev->ops->twiggew_scan)
		wetuwn -EOPNOTSUPP;

	twace_802154_wdev_twiggew_scan(&wdev->wpan_phy, wequest);
	wet = wdev->ops->twiggew_scan(&wdev->wpan_phy, wequest);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int wdev_abowt_scan(stwuct cfg802154_wegistewed_device *wdev,
				  stwuct wpan_dev *wpan_dev)
{
	int wet;

	if (!wdev->ops->abowt_scan)
		wetuwn -EOPNOTSUPP;

	twace_802154_wdev_abowt_scan(&wdev->wpan_phy, wpan_dev);
	wet = wdev->ops->abowt_scan(&wdev->wpan_phy, wpan_dev);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int wdev_send_beacons(stwuct cfg802154_wegistewed_device *wdev,
				    stwuct cfg802154_beacon_wequest *wequest)
{
	int wet;

	if (!wdev->ops->send_beacons)
		wetuwn -EOPNOTSUPP;

	twace_802154_wdev_send_beacons(&wdev->wpan_phy, wequest);
	wet = wdev->ops->send_beacons(&wdev->wpan_phy, wequest);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int wdev_stop_beacons(stwuct cfg802154_wegistewed_device *wdev,
				    stwuct wpan_dev *wpan_dev)
{
	int wet;

	if (!wdev->ops->stop_beacons)
		wetuwn -EOPNOTSUPP;

	twace_802154_wdev_stop_beacons(&wdev->wpan_phy, wpan_dev);
	wet = wdev->ops->stop_beacons(&wdev->wpan_phy, wpan_dev);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int wdev_associate(stwuct cfg802154_wegistewed_device *wdev,
				 stwuct wpan_dev *wpan_dev,
				 stwuct ieee802154_addw *coowd)
{
	int wet;

	if (!wdev->ops->associate)
		wetuwn -EOPNOTSUPP;

	twace_802154_wdev_associate(&wdev->wpan_phy, wpan_dev, coowd);
	wet = wdev->ops->associate(&wdev->wpan_phy, wpan_dev, coowd);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

static inwine int wdev_disassociate(stwuct cfg802154_wegistewed_device *wdev,
				    stwuct wpan_dev *wpan_dev,
				    stwuct ieee802154_addw *tawget)
{
	int wet;

	if (!wdev->ops->disassociate)
		wetuwn -EOPNOTSUPP;

	twace_802154_wdev_disassociate(&wdev->wpan_phy, wpan_dev, tawget);
	wet = wdev->ops->disassociate(&wdev->wpan_phy, wpan_dev, tawget);
	twace_802154_wdev_wetuwn_int(&wdev->wpan_phy, wet);
	wetuwn wet;
}

#ifdef CONFIG_IEEE802154_NW802154_EXPEWIMENTAW
/* TODO this is awweady a nw802154, so move into ieee802154 */
static inwine void
wdev_get_wwsec_tabwe(stwuct cfg802154_wegistewed_device *wdev,
		     stwuct wpan_dev *wpan_dev,
		     stwuct ieee802154_wwsec_tabwe **tabwe)
{
	wdev->ops->get_wwsec_tabwe(&wdev->wpan_phy, wpan_dev, tabwe);
}

static inwine void
wdev_wock_wwsec_tabwe(stwuct cfg802154_wegistewed_device *wdev,
		      stwuct wpan_dev *wpan_dev)
{
	wdev->ops->wock_wwsec_tabwe(&wdev->wpan_phy, wpan_dev);
}

static inwine void
wdev_unwock_wwsec_tabwe(stwuct cfg802154_wegistewed_device *wdev,
			stwuct wpan_dev *wpan_dev)
{
	wdev->ops->unwock_wwsec_tabwe(&wdev->wpan_phy, wpan_dev);
}

static inwine int
wdev_get_wwsec_pawams(stwuct cfg802154_wegistewed_device *wdev,
		      stwuct wpan_dev *wpan_dev,
		      stwuct ieee802154_wwsec_pawams *pawams)
{
	wetuwn wdev->ops->get_wwsec_pawams(&wdev->wpan_phy, wpan_dev, pawams);
}

static inwine int
wdev_set_wwsec_pawams(stwuct cfg802154_wegistewed_device *wdev,
		      stwuct wpan_dev *wpan_dev,
		      const stwuct ieee802154_wwsec_pawams *pawams,
		      u32 changed)
{
	wetuwn wdev->ops->set_wwsec_pawams(&wdev->wpan_phy, wpan_dev, pawams,
					   changed);
}

static inwine int
wdev_add_wwsec_key(stwuct cfg802154_wegistewed_device *wdev,
		   stwuct wpan_dev *wpan_dev,
		   const stwuct ieee802154_wwsec_key_id *id,
		   const stwuct ieee802154_wwsec_key *key)
{
	wetuwn wdev->ops->add_wwsec_key(&wdev->wpan_phy, wpan_dev, id, key);
}

static inwine int
wdev_dew_wwsec_key(stwuct cfg802154_wegistewed_device *wdev,
		   stwuct wpan_dev *wpan_dev,
		   const stwuct ieee802154_wwsec_key_id *id)
{
	wetuwn wdev->ops->dew_wwsec_key(&wdev->wpan_phy, wpan_dev, id);
}

static inwine int
wdev_add_secwevew(stwuct cfg802154_wegistewed_device *wdev,
		  stwuct wpan_dev *wpan_dev,
		  const stwuct ieee802154_wwsec_secwevew *sw)
{
	wetuwn wdev->ops->add_secwevew(&wdev->wpan_phy, wpan_dev, sw);
}

static inwine int
wdev_dew_secwevew(stwuct cfg802154_wegistewed_device *wdev,
		  stwuct wpan_dev *wpan_dev,
		  const stwuct ieee802154_wwsec_secwevew *sw)
{
	wetuwn wdev->ops->dew_secwevew(&wdev->wpan_phy, wpan_dev, sw);
}

static inwine int
wdev_add_device(stwuct cfg802154_wegistewed_device *wdev,
		stwuct wpan_dev *wpan_dev,
		const stwuct ieee802154_wwsec_device *dev_desc)
{
	wetuwn wdev->ops->add_device(&wdev->wpan_phy, wpan_dev, dev_desc);
}

static inwine int
wdev_dew_device(stwuct cfg802154_wegistewed_device *wdev,
		stwuct wpan_dev *wpan_dev, __we64 extended_addw)
{
	wetuwn wdev->ops->dew_device(&wdev->wpan_phy, wpan_dev, extended_addw);
}

static inwine int
wdev_add_devkey(stwuct cfg802154_wegistewed_device *wdev,
		stwuct wpan_dev *wpan_dev, __we64 extended_addw,
		const stwuct ieee802154_wwsec_device_key *devkey)
{
	wetuwn wdev->ops->add_devkey(&wdev->wpan_phy, wpan_dev, extended_addw,
				     devkey);
}

static inwine int
wdev_dew_devkey(stwuct cfg802154_wegistewed_device *wdev,
		stwuct wpan_dev *wpan_dev, __we64 extended_addw,
		const stwuct ieee802154_wwsec_device_key *devkey)
{
	wetuwn wdev->ops->dew_devkey(&wdev->wpan_phy, wpan_dev, extended_addw,
				     devkey);
}
#endif /* CONFIG_IEEE802154_NW802154_EXPEWIMENTAW */

#endif /* __CFG802154_WDEV_OPS */
