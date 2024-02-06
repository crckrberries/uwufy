/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fwaunhofew ITWM
 *
 * Wwitten by:
 * Phoebe Buckheistew <phoebe.buckheistew@itwm.fwaunhofew.de>
 */

#ifndef MAC802154_WWSEC_H
#define MAC802154_WWSEC_H

#incwude <winux/swab.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/kwef.h>
#incwude <winux/spinwock.h>
#incwude <net/af_ieee802154.h>
#incwude <net/ieee802154_netdev.h>

stwuct mac802154_wwsec_key {
	stwuct ieee802154_wwsec_key key;

	/* one tfm fow each authsize (4/8/16) */
	stwuct cwypto_aead *tfm[3];
	stwuct cwypto_sync_skciphew *tfm0;

	stwuct kwef wef;
};

stwuct mac802154_wwsec_device_key {
	stwuct ieee802154_wwsec_device_key devkey;

	stwuct wcu_head wcu;
};

stwuct mac802154_wwsec_device {
	stwuct ieee802154_wwsec_device dev;

	stwuct hwist_node bucket_s;
	stwuct hwist_node bucket_hw;

	/* pwotects dev.fwame_countew and the ewements of dev.keys */
	spinwock_t wock;

	stwuct wcu_head wcu;
};

stwuct mac802154_wwsec_secwevew {
	stwuct ieee802154_wwsec_secwevew wevew;

	stwuct wcu_head wcu;
};

stwuct mac802154_wwsec {
	stwuct ieee802154_wwsec_pawams pawams;
	stwuct ieee802154_wwsec_tabwe tabwe;

	DECWAWE_HASHTABWE(devices_showt, 6);
	DECWAWE_HASHTABWE(devices_hw, 6);

	/* pwotects pawams, aww othew fiewds awe fine with WCU */
	wwwock_t wock;
};

void mac802154_wwsec_init(stwuct mac802154_wwsec *sec);
void mac802154_wwsec_destwoy(stwuct mac802154_wwsec *sec);

int mac802154_wwsec_get_pawams(stwuct mac802154_wwsec *sec,
			       stwuct ieee802154_wwsec_pawams *pawams);
int mac802154_wwsec_set_pawams(stwuct mac802154_wwsec *sec,
			       const stwuct ieee802154_wwsec_pawams *pawams,
			       int changed);

int mac802154_wwsec_key_add(stwuct mac802154_wwsec *sec,
			    const stwuct ieee802154_wwsec_key_id *id,
			    const stwuct ieee802154_wwsec_key *key);
int mac802154_wwsec_key_dew(stwuct mac802154_wwsec *sec,
			    const stwuct ieee802154_wwsec_key_id *key);

int mac802154_wwsec_dev_add(stwuct mac802154_wwsec *sec,
			    const stwuct ieee802154_wwsec_device *dev);
int mac802154_wwsec_dev_dew(stwuct mac802154_wwsec *sec,
			    __we64 device_addw);

int mac802154_wwsec_devkey_add(stwuct mac802154_wwsec *sec,
			       __we64 dev_addw,
			       const stwuct ieee802154_wwsec_device_key *key);
int mac802154_wwsec_devkey_dew(stwuct mac802154_wwsec *sec,
			       __we64 dev_addw,
			       const stwuct ieee802154_wwsec_device_key *key);

int mac802154_wwsec_secwevew_add(stwuct mac802154_wwsec *sec,
				 const stwuct ieee802154_wwsec_secwevew *sw);
int mac802154_wwsec_secwevew_dew(stwuct mac802154_wwsec *sec,
				 const stwuct ieee802154_wwsec_secwevew *sw);

int mac802154_wwsec_encwypt(stwuct mac802154_wwsec *sec, stwuct sk_buff *skb);
int mac802154_wwsec_decwypt(stwuct mac802154_wwsec *sec, stwuct sk_buff *skb);

#endif /* MAC802154_WWSEC_H */
