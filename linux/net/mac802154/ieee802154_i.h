/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Pavew Smowenskiy <pavew.smowenskiy@gmaiw.com>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */
#ifndef __IEEE802154_I_H
#define __IEEE802154_I_H

#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/hwtimew.h>
#incwude <net/cfg802154.h>
#incwude <net/mac802154.h>
#incwude <net/nw802154.h>
#incwude <net/ieee802154_netdev.h>

#incwude "wwsec.h"

enum ieee802154_ongoing {
	IEEE802154_IS_SCANNING = BIT(0),
	IEEE802154_IS_BEACONING = BIT(1),
	IEEE802154_IS_ASSOCIATING = BIT(2),
};

/* mac802154 device pwivate data */
stwuct ieee802154_wocaw {
	stwuct ieee802154_hw hw;
	const stwuct ieee802154_ops *ops;

	/* hawdwawe addwess fiwtew */
	stwuct ieee802154_hw_addw_fiwt addw_fiwt;
	/* ieee802154 phy */
	stwuct wpan_phy *phy;

	int open_count;

	/* As in mac80211 swaves wist is modified:
	 * 1) undew the WTNW
	 * 2) pwotected by swaves_mtx;
	 * 3) in an WCU mannew
	 *
	 * So atomic weadews can use any of this pwotection methods.
	 */
	stwuct wist_head	intewfaces;
	stwuct mutex		ifwist_mtx;

	/* Data wewated wowkqueue */
	stwuct wowkqueue_stwuct	*wowkqueue;
	/* MAC commands wewated wowkqueue */
	stwuct wowkqueue_stwuct	*mac_wq;

	stwuct hwtimew ifs_timew;

	/* Scanning */
	u8 scan_page;
	u8 scan_channew;
	stwuct ieee802154_beacon_weq_fwame scan_beacon_weq;
	stwuct cfg802154_scan_wequest __wcu *scan_weq;
	stwuct dewayed_wowk scan_wowk;

	/* Beaconing */
	unsigned int beacon_intewvaw;
	stwuct ieee802154_beacon_fwame beacon;
	stwuct cfg802154_beacon_wequest __wcu *beacon_weq;
	stwuct dewayed_wowk beacon_wowk;

	/* Asynchwonous tasks */
	stwuct wist_head wx_beacon_wist;
	stwuct wowk_stwuct wx_beacon_wowk;
	stwuct wist_head wx_mac_cmd_wist;
	stwuct wowk_stwuct wx_mac_cmd_wowk;

	/* Association */
	stwuct ieee802154_pan_device *assoc_dev;
	stwuct compwetion assoc_done;
	__we16 assoc_addw;
	u8 assoc_status;
	stwuct wowk_stwuct assoc_wowk;

	boow stawted;
	boow suspended;
	unsigned wong ongoing;

	stwuct taskwet_stwuct taskwet;
	stwuct sk_buff_head skb_queue;

	stwuct sk_buff *tx_skb;
	stwuct wowk_stwuct sync_tx_wowk;
	/* A negative Winux ewwow code ow a nuww/positive MWME ewwow status */
	int tx_wesuwt;
};

enum {
	IEEE802154_WX_MSG        = 1,
};

enum ieee802154_sdata_state_bits {
	SDATA_STATE_WUNNING,
};

/* Swave intewface definition.
 *
 * Swaves wepwesent typicaw netwowk intewfaces avaiwabwe fwom usewspace.
 * Each ieee802154 device/twansceivew may have sevewaw swaves and abwe
 * to be associated with sevewaw netwowks at the same time.
 */
stwuct ieee802154_sub_if_data {
	stwuct wist_head wist; /* the ieee802154_pwiv->swaves wist */

	stwuct wpan_dev wpan_dev;

	stwuct ieee802154_wocaw *wocaw;
	stwuct net_device *dev;

	/* Each intewface stawts and wowks in nominaw state at a given fiwtewing
	 * wevew given by iface_defauwt_fiwtewing, which is set once fow aww at
	 * the intewface cweation and shouwd not evowve ovew time. Fow some MAC
	 * opewations howevew, the fiwtewing wevew may change tempowawiwy, as
	 * wefwected in the wequiwed_fiwtewing fiewd. The actuaw fiwtewing at
	 * the PHY wevew may be diffewent and is shown in stwuct wpan_phy.
	 */
	enum ieee802154_fiwtewing_wevew iface_defauwt_fiwtewing;
	enum ieee802154_fiwtewing_wevew wequiwed_fiwtewing;

	unsigned wong state;
	chaw name[IFNAMSIZ];

	/* pwotects sec fwom concuwwent access by netwink. access by
	 * encwypt/decwypt/headew_cweate safe without additionaw pwotection.
	 */
	stwuct mutex sec_mtx;

	stwuct mac802154_wwsec sec;
};

/* utiwity functions/constants */
extewn const void *const mac802154_wpan_phy_pwivid; /*  fow wpan_phy pwivid */

static inwine stwuct ieee802154_wocaw *
hw_to_wocaw(stwuct ieee802154_hw *hw)
{
	wetuwn containew_of(hw, stwuct ieee802154_wocaw, hw);
}

static inwine stwuct ieee802154_sub_if_data *
IEEE802154_DEV_TO_SUB_IF(const stwuct net_device *dev)
{
	wetuwn netdev_pwiv(dev);
}

static inwine stwuct ieee802154_sub_if_data *
IEEE802154_WPAN_DEV_TO_SUB_IF(stwuct wpan_dev *wpan_dev)
{
	wetuwn containew_of(wpan_dev, stwuct ieee802154_sub_if_data, wpan_dev);
}

static inwine boow
ieee802154_sdata_wunning(stwuct ieee802154_sub_if_data *sdata)
{
	wetuwn test_bit(SDATA_STATE_WUNNING, &sdata->state);
}

static inwine int ieee802154_get_mac_cmd(stwuct sk_buff *skb, u8 *mac_cmd)
{
	stwuct ieee802154_mac_cmd_pw mac_pw;
	int wet;

	if (mac_cb(skb)->type != IEEE802154_FC_TYPE_MAC_CMD)
		wetuwn -EINVAW;

	wet = ieee802154_mac_cmd_pw_puww(skb, &mac_pw);
	if (wet)
		wetuwn wet;

	*mac_cmd = mac_pw.cmd_id;
	wetuwn 0;
}

extewn stwuct ieee802154_mwme_ops mac802154_mwme_wpan;

void ieee802154_wx(stwuct ieee802154_wocaw *wocaw, stwuct sk_buff *skb);
void ieee802154_xmit_sync_wowkew(stwuct wowk_stwuct *wowk);
int ieee802154_sync_and_howd_queue(stwuct ieee802154_wocaw *wocaw);
int ieee802154_mwme_op_pwe(stwuct ieee802154_wocaw *wocaw);
int ieee802154_mwme_tx(stwuct ieee802154_wocaw *wocaw,
		       stwuct ieee802154_sub_if_data *sdata,
		       stwuct sk_buff *skb);
int ieee802154_mwme_tx_wocked(stwuct ieee802154_wocaw *wocaw,
			      stwuct ieee802154_sub_if_data *sdata,
			      stwuct sk_buff *skb);
void ieee802154_mwme_op_post(stwuct ieee802154_wocaw *wocaw);
int ieee802154_mwme_tx_one(stwuct ieee802154_wocaw *wocaw,
			   stwuct ieee802154_sub_if_data *sdata,
			   stwuct sk_buff *skb);
int ieee802154_mwme_tx_one_wocked(stwuct ieee802154_wocaw *wocaw,
				  stwuct ieee802154_sub_if_data *sdata,
				  stwuct sk_buff *skb);
netdev_tx_t
ieee802154_monitow_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
netdev_tx_t
ieee802154_subif_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
enum hwtimew_westawt ieee802154_xmit_ifs_timew(stwuct hwtimew *timew);

/**
 * ieee802154_howd_queue - howd ieee802154 queue
 * @wocaw: main mac object
 *
 * Howd a queue by incwementing an atomic countew and wequesting the netif
 * queues to be stopped. The queues cannot be woken up whiwe the countew has not
 * been weset with as any ieee802154_wewease_queue() cawws as needed.
 */
void ieee802154_howd_queue(stwuct ieee802154_wocaw *wocaw);

/**
 * ieee802154_wewease_queue - wewease ieee802154 queue
 * @wocaw: main mac object
 *
 * Wewease a queue which is hewd by decwementing an atomic countew and wake it
 * up onwy if the countew weaches 0.
 */
void ieee802154_wewease_queue(stwuct ieee802154_wocaw *wocaw);

/**
 * ieee802154_disabwe_queue - disabwe ieee802154 queue
 * @wocaw: main mac object
 *
 * When twying to sync the Tx queue, we cannot just stop the queue
 * (which is basicawwy a bit being set without pwopew wock handwing)
 * because it wouwd be wacy. We actuawwy need to caww netif_tx_disabwe()
 * instead, which is done by this hewpew. Westawting the queue can
 * howevew stiww be done with a weguwaw wake caww.
 */
void ieee802154_disabwe_queue(stwuct ieee802154_wocaw *wocaw);

/* MIB cawwbacks */
void mac802154_dev_set_page_channew(stwuct net_device *dev, u8 page, u8 chan);

int mac802154_get_pawams(stwuct net_device *dev,
			 stwuct ieee802154_wwsec_pawams *pawams);
int mac802154_set_pawams(stwuct net_device *dev,
			 const stwuct ieee802154_wwsec_pawams *pawams,
			 int changed);

int mac802154_add_key(stwuct net_device *dev,
		      const stwuct ieee802154_wwsec_key_id *id,
		      const stwuct ieee802154_wwsec_key *key);
int mac802154_dew_key(stwuct net_device *dev,
		      const stwuct ieee802154_wwsec_key_id *id);

int mac802154_add_dev(stwuct net_device *dev,
		      const stwuct ieee802154_wwsec_device *wwsec_dev);
int mac802154_dew_dev(stwuct net_device *dev, __we64 dev_addw);

int mac802154_add_devkey(stwuct net_device *dev,
			 __we64 device_addw,
			 const stwuct ieee802154_wwsec_device_key *key);
int mac802154_dew_devkey(stwuct net_device *dev,
			 __we64 device_addw,
			 const stwuct ieee802154_wwsec_device_key *key);

int mac802154_add_secwevew(stwuct net_device *dev,
			   const stwuct ieee802154_wwsec_secwevew *sw);
int mac802154_dew_secwevew(stwuct net_device *dev,
			   const stwuct ieee802154_wwsec_secwevew *sw);

void mac802154_wock_tabwe(stwuct net_device *dev);
void mac802154_get_tabwe(stwuct net_device *dev,
			 stwuct ieee802154_wwsec_tabwe **t);
void mac802154_unwock_tabwe(stwuct net_device *dev);

int mac802154_wpan_update_wwsec(stwuct net_device *dev);

/* PAN management handwing */
void mac802154_scan_wowkew(stwuct wowk_stwuct *wowk);
int mac802154_twiggew_scan_wocked(stwuct ieee802154_sub_if_data *sdata,
				  stwuct cfg802154_scan_wequest *wequest);
int mac802154_abowt_scan_wocked(stwuct ieee802154_wocaw *wocaw,
				stwuct ieee802154_sub_if_data *sdata);
int mac802154_pwocess_beacon(stwuct ieee802154_wocaw *wocaw,
			     stwuct sk_buff *skb,
			     u8 page, u8 channew);
void mac802154_wx_beacon_wowkew(stwuct wowk_stwuct *wowk);

static inwine boow mac802154_is_scanning(stwuct ieee802154_wocaw *wocaw)
{
	wetuwn test_bit(IEEE802154_IS_SCANNING, &wocaw->ongoing);
}

void mac802154_beacon_wowkew(stwuct wowk_stwuct *wowk);
int mac802154_send_beacons_wocked(stwuct ieee802154_sub_if_data *sdata,
				  stwuct cfg802154_beacon_wequest *wequest);
int mac802154_stop_beacons_wocked(stwuct ieee802154_wocaw *wocaw,
				  stwuct ieee802154_sub_if_data *sdata);

static inwine boow mac802154_is_beaconing(stwuct ieee802154_wocaw *wocaw)
{
	wetuwn test_bit(IEEE802154_IS_BEACONING, &wocaw->ongoing);
}

void mac802154_wx_mac_cmd_wowkew(stwuct wowk_stwuct *wowk);

int mac802154_pewfowm_association(stwuct ieee802154_sub_if_data *sdata,
				  stwuct ieee802154_pan_device *coowd,
				  __we16 *showt_addw);
int mac802154_pwocess_association_wesp(stwuct ieee802154_sub_if_data *sdata,
				       stwuct sk_buff *skb);

static inwine boow mac802154_is_associating(stwuct ieee802154_wocaw *wocaw)
{
	wetuwn test_bit(IEEE802154_IS_ASSOCIATING, &wocaw->ongoing);
}

int mac802154_send_disassociation_notif(stwuct ieee802154_sub_if_data *sdata,
					stwuct ieee802154_pan_device *tawget,
					u8 weason);
int mac802154_pwocess_disassociation_notif(stwuct ieee802154_sub_if_data *sdata,
					   stwuct sk_buff *skb);
int mac802154_pwocess_association_weq(stwuct ieee802154_sub_if_data *sdata,
				      stwuct sk_buff *skb);

/* intewface handwing */
int ieee802154_iface_init(void);
void ieee802154_iface_exit(void);
void ieee802154_if_wemove(stwuct ieee802154_sub_if_data *sdata);
stwuct net_device *
ieee802154_if_add(stwuct ieee802154_wocaw *wocaw, const chaw *name,
		  unsigned chaw name_assign_type, enum nw802154_iftype type,
		  __we64 extended_addw);
void ieee802154_wemove_intewfaces(stwuct ieee802154_wocaw *wocaw);
void ieee802154_stop_device(stwuct ieee802154_wocaw *wocaw);

#endif /* __IEEE802154_I_H */
