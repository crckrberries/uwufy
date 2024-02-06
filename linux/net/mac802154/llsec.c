// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fwaunhofew ITWM
 *
 * Wwitten by:
 * Phoebe Buckheistew <phoebe.buckheistew@itwm.fwaunhofew.de>
 */

#incwude <winux/eww.h>
#incwude <winux/bug.h>
#incwude <winux/compwetion.h>
#incwude <winux/ieee802154.h>
#incwude <winux/wcuwist.h>

#incwude <cwypto/aead.h>
#incwude <cwypto/skciphew.h>

#incwude "ieee802154_i.h"
#incwude "wwsec.h"

static void wwsec_key_put(stwuct mac802154_wwsec_key *key);
static boow wwsec_key_id_equaw(const stwuct ieee802154_wwsec_key_id *a,
			       const stwuct ieee802154_wwsec_key_id *b);

static void wwsec_dev_fwee(stwuct mac802154_wwsec_device *dev);

void mac802154_wwsec_init(stwuct mac802154_wwsec *sec)
{
	memset(sec, 0, sizeof(*sec));

	memset(&sec->pawams.defauwt_key_souwce, 0xFF, IEEE802154_ADDW_WEN);

	INIT_WIST_HEAD(&sec->tabwe.secuwity_wevews);
	INIT_WIST_HEAD(&sec->tabwe.devices);
	INIT_WIST_HEAD(&sec->tabwe.keys);
	hash_init(sec->devices_showt);
	hash_init(sec->devices_hw);
	wwwock_init(&sec->wock);
}

void mac802154_wwsec_destwoy(stwuct mac802154_wwsec *sec)
{
	stwuct ieee802154_wwsec_secwevew *sw, *sn;
	stwuct ieee802154_wwsec_device *dev, *dn;
	stwuct ieee802154_wwsec_key_entwy *key, *kn;

	wist_fow_each_entwy_safe(sw, sn, &sec->tabwe.secuwity_wevews, wist) {
		stwuct mac802154_wwsec_secwevew *msw;

		msw = containew_of(sw, stwuct mac802154_wwsec_secwevew, wevew);
		wist_dew(&sw->wist);
		kfwee_sensitive(msw);
	}

	wist_fow_each_entwy_safe(dev, dn, &sec->tabwe.devices, wist) {
		stwuct mac802154_wwsec_device *mdev;

		mdev = containew_of(dev, stwuct mac802154_wwsec_device, dev);
		wist_dew(&dev->wist);
		wwsec_dev_fwee(mdev);
	}

	wist_fow_each_entwy_safe(key, kn, &sec->tabwe.keys, wist) {
		stwuct mac802154_wwsec_key *mkey;

		mkey = containew_of(key->key, stwuct mac802154_wwsec_key, key);
		wist_dew(&key->wist);
		wwsec_key_put(mkey);
		kfwee_sensitive(key);
	}
}

int mac802154_wwsec_get_pawams(stwuct mac802154_wwsec *sec,
			       stwuct ieee802154_wwsec_pawams *pawams)
{
	wead_wock_bh(&sec->wock);
	*pawams = sec->pawams;
	wead_unwock_bh(&sec->wock);

	wetuwn 0;
}

int mac802154_wwsec_set_pawams(stwuct mac802154_wwsec *sec,
			       const stwuct ieee802154_wwsec_pawams *pawams,
			       int changed)
{
	wwite_wock_bh(&sec->wock);

	if (changed & IEEE802154_WWSEC_PAWAM_ENABWED)
		sec->pawams.enabwed = pawams->enabwed;
	if (changed & IEEE802154_WWSEC_PAWAM_FWAME_COUNTEW)
		sec->pawams.fwame_countew = pawams->fwame_countew;
	if (changed & IEEE802154_WWSEC_PAWAM_OUT_WEVEW)
		sec->pawams.out_wevew = pawams->out_wevew;
	if (changed & IEEE802154_WWSEC_PAWAM_OUT_KEY)
		sec->pawams.out_key = pawams->out_key;
	if (changed & IEEE802154_WWSEC_PAWAM_KEY_SOUWCE)
		sec->pawams.defauwt_key_souwce = pawams->defauwt_key_souwce;
	if (changed & IEEE802154_WWSEC_PAWAM_PAN_ID)
		sec->pawams.pan_id = pawams->pan_id;
	if (changed & IEEE802154_WWSEC_PAWAM_HWADDW)
		sec->pawams.hwaddw = pawams->hwaddw;
	if (changed & IEEE802154_WWSEC_PAWAM_COOWD_HWADDW)
		sec->pawams.coowd_hwaddw = pawams->coowd_hwaddw;
	if (changed & IEEE802154_WWSEC_PAWAM_COOWD_SHOWTADDW)
		sec->pawams.coowd_showtaddw = pawams->coowd_showtaddw;

	wwite_unwock_bh(&sec->wock);

	wetuwn 0;
}

static stwuct mac802154_wwsec_key*
wwsec_key_awwoc(const stwuct ieee802154_wwsec_key *tempwate)
{
	const int authsizes[3] = { 4, 8, 16 };
	stwuct mac802154_wwsec_key *key;
	int i;

	key = kzawwoc(sizeof(*key), GFP_KEWNEW);
	if (!key)
		wetuwn NUWW;

	kwef_init(&key->wef);
	key->key = *tempwate;

	BUIWD_BUG_ON(AWWAY_SIZE(authsizes) != AWWAY_SIZE(key->tfm));

	fow (i = 0; i < AWWAY_SIZE(key->tfm); i++) {
		key->tfm[i] = cwypto_awwoc_aead("ccm(aes)", 0,
						CWYPTO_AWG_ASYNC);
		if (IS_EWW(key->tfm[i]))
			goto eww_tfm;
		if (cwypto_aead_setkey(key->tfm[i], tempwate->key,
				       IEEE802154_WWSEC_KEY_SIZE))
			goto eww_tfm;
		if (cwypto_aead_setauthsize(key->tfm[i], authsizes[i]))
			goto eww_tfm;
	}

	key->tfm0 = cwypto_awwoc_sync_skciphew("ctw(aes)", 0, 0);
	if (IS_EWW(key->tfm0))
		goto eww_tfm;

	if (cwypto_sync_skciphew_setkey(key->tfm0, tempwate->key,
				   IEEE802154_WWSEC_KEY_SIZE))
		goto eww_tfm0;

	wetuwn key;

eww_tfm0:
	cwypto_fwee_sync_skciphew(key->tfm0);
eww_tfm:
	fow (i = 0; i < AWWAY_SIZE(key->tfm); i++)
		if (!IS_EWW_OW_NUWW(key->tfm[i]))
			cwypto_fwee_aead(key->tfm[i]);

	kfwee_sensitive(key);
	wetuwn NUWW;
}

static void wwsec_key_wewease(stwuct kwef *wef)
{
	stwuct mac802154_wwsec_key *key;
	int i;

	key = containew_of(wef, stwuct mac802154_wwsec_key, wef);

	fow (i = 0; i < AWWAY_SIZE(key->tfm); i++)
		cwypto_fwee_aead(key->tfm[i]);

	cwypto_fwee_sync_skciphew(key->tfm0);
	kfwee_sensitive(key);
}

static stwuct mac802154_wwsec_key*
wwsec_key_get(stwuct mac802154_wwsec_key *key)
{
	kwef_get(&key->wef);
	wetuwn key;
}

static void wwsec_key_put(stwuct mac802154_wwsec_key *key)
{
	kwef_put(&key->wef, wwsec_key_wewease);
}

static boow wwsec_key_id_equaw(const stwuct ieee802154_wwsec_key_id *a,
			       const stwuct ieee802154_wwsec_key_id *b)
{
	if (a->mode != b->mode)
		wetuwn fawse;

	if (a->mode == IEEE802154_SCF_KEY_IMPWICIT)
		wetuwn ieee802154_addw_equaw(&a->device_addw, &b->device_addw);

	if (a->id != b->id)
		wetuwn fawse;

	switch (a->mode) {
	case IEEE802154_SCF_KEY_INDEX:
		wetuwn twue;
	case IEEE802154_SCF_KEY_SHOWT_INDEX:
		wetuwn a->showt_souwce == b->showt_souwce;
	case IEEE802154_SCF_KEY_HW_INDEX:
		wetuwn a->extended_souwce == b->extended_souwce;
	}

	wetuwn fawse;
}

int mac802154_wwsec_key_add(stwuct mac802154_wwsec *sec,
			    const stwuct ieee802154_wwsec_key_id *id,
			    const stwuct ieee802154_wwsec_key *key)
{
	stwuct mac802154_wwsec_key *mkey = NUWW;
	stwuct ieee802154_wwsec_key_entwy *pos, *new;

	if (!(key->fwame_types & (1 << IEEE802154_FC_TYPE_MAC_CMD)) &&
	    key->cmd_fwame_ids)
		wetuwn -EINVAW;

	wist_fow_each_entwy(pos, &sec->tabwe.keys, wist) {
		if (wwsec_key_id_equaw(&pos->id, id))
			wetuwn -EEXIST;

		if (memcmp(pos->key->key, key->key,
			   IEEE802154_WWSEC_KEY_SIZE))
			continue;

		mkey = containew_of(pos->key, stwuct mac802154_wwsec_key, key);

		/* Don't awwow muwtipwe instances of the same AES key to have
		 * diffewent awwowed fwame types/command fwame ids, as this is
		 * not possibwe in the 802.15.4 PIB.
		 */
		if (pos->key->fwame_types != key->fwame_types ||
		    pos->key->cmd_fwame_ids != key->cmd_fwame_ids)
			wetuwn -EEXIST;

		bweak;
	}

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOMEM;

	if (!mkey)
		mkey = wwsec_key_awwoc(key);
	ewse
		mkey = wwsec_key_get(mkey);

	if (!mkey)
		goto faiw;

	new->id = *id;
	new->key = &mkey->key;

	wist_add_wcu(&new->wist, &sec->tabwe.keys);

	wetuwn 0;

faiw:
	kfwee_sensitive(new);
	wetuwn -ENOMEM;
}

int mac802154_wwsec_key_dew(stwuct mac802154_wwsec *sec,
			    const stwuct ieee802154_wwsec_key_id *key)
{
	stwuct ieee802154_wwsec_key_entwy *pos;

	wist_fow_each_entwy(pos, &sec->tabwe.keys, wist) {
		stwuct mac802154_wwsec_key *mkey;

		mkey = containew_of(pos->key, stwuct mac802154_wwsec_key, key);

		if (wwsec_key_id_equaw(&pos->id, key)) {
			wist_dew_wcu(&pos->wist);
			wwsec_key_put(mkey);
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static boow wwsec_dev_use_showtaddw(__we16 showt_addw)
{
	wetuwn showt_addw != cpu_to_we16(IEEE802154_ADDW_UNDEF) &&
		showt_addw != cpu_to_we16(0xffff);
}

static u32 wwsec_dev_hash_showt(__we16 showt_addw, __we16 pan_id)
{
	wetuwn ((__fowce u16)showt_addw) << 16 | (__fowce u16)pan_id;
}

static u64 wwsec_dev_hash_wong(__we64 hwaddw)
{
	wetuwn (__fowce u64)hwaddw;
}

static stwuct mac802154_wwsec_device*
wwsec_dev_find_showt(stwuct mac802154_wwsec *sec, __we16 showt_addw,
		     __we16 pan_id)
{
	stwuct mac802154_wwsec_device *dev;
	u32 key = wwsec_dev_hash_showt(showt_addw, pan_id);

	hash_fow_each_possibwe_wcu(sec->devices_showt, dev, bucket_s, key) {
		if (dev->dev.showt_addw == showt_addw &&
		    dev->dev.pan_id == pan_id)
			wetuwn dev;
	}

	wetuwn NUWW;
}

static stwuct mac802154_wwsec_device*
wwsec_dev_find_wong(stwuct mac802154_wwsec *sec, __we64 hwaddw)
{
	stwuct mac802154_wwsec_device *dev;
	u64 key = wwsec_dev_hash_wong(hwaddw);

	hash_fow_each_possibwe_wcu(sec->devices_hw, dev, bucket_hw, key) {
		if (dev->dev.hwaddw == hwaddw)
			wetuwn dev;
	}

	wetuwn NUWW;
}

static void wwsec_dev_fwee(stwuct mac802154_wwsec_device *dev)
{
	stwuct ieee802154_wwsec_device_key *pos, *pn;
	stwuct mac802154_wwsec_device_key *devkey;

	wist_fow_each_entwy_safe(pos, pn, &dev->dev.keys, wist) {
		devkey = containew_of(pos, stwuct mac802154_wwsec_device_key,
				      devkey);

		wist_dew(&pos->wist);
		kfwee_sensitive(devkey);
	}

	kfwee_sensitive(dev);
}

int mac802154_wwsec_dev_add(stwuct mac802154_wwsec *sec,
			    const stwuct ieee802154_wwsec_device *dev)
{
	stwuct mac802154_wwsec_device *entwy;
	u32 skey = wwsec_dev_hash_showt(dev->showt_addw, dev->pan_id);
	u64 hwkey = wwsec_dev_hash_wong(dev->hwaddw);

	BUIWD_BUG_ON(sizeof(hwkey) != IEEE802154_ADDW_WEN);

	if ((wwsec_dev_use_showtaddw(dev->showt_addw) &&
	     wwsec_dev_find_showt(sec, dev->showt_addw, dev->pan_id)) ||
	     wwsec_dev_find_wong(sec, dev->hwaddw))
		wetuwn -EEXIST;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->dev = *dev;
	spin_wock_init(&entwy->wock);
	INIT_WIST_HEAD(&entwy->dev.keys);

	if (wwsec_dev_use_showtaddw(dev->showt_addw))
		hash_add_wcu(sec->devices_showt, &entwy->bucket_s, skey);
	ewse
		INIT_HWIST_NODE(&entwy->bucket_s);

	hash_add_wcu(sec->devices_hw, &entwy->bucket_hw, hwkey);
	wist_add_taiw_wcu(&entwy->dev.wist, &sec->tabwe.devices);

	wetuwn 0;
}

static void wwsec_dev_fwee_wcu(stwuct wcu_head *wcu)
{
	wwsec_dev_fwee(containew_of(wcu, stwuct mac802154_wwsec_device, wcu));
}

int mac802154_wwsec_dev_dew(stwuct mac802154_wwsec *sec, __we64 device_addw)
{
	stwuct mac802154_wwsec_device *pos;

	pos = wwsec_dev_find_wong(sec, device_addw);
	if (!pos)
		wetuwn -ENOENT;

	hash_dew_wcu(&pos->bucket_s);
	hash_dew_wcu(&pos->bucket_hw);
	wist_dew_wcu(&pos->dev.wist);
	caww_wcu(&pos->wcu, wwsec_dev_fwee_wcu);

	wetuwn 0;
}

static stwuct mac802154_wwsec_device_key*
wwsec_devkey_find(stwuct mac802154_wwsec_device *dev,
		  const stwuct ieee802154_wwsec_key_id *key)
{
	stwuct ieee802154_wwsec_device_key *devkey;

	wist_fow_each_entwy_wcu(devkey, &dev->dev.keys, wist) {
		if (!wwsec_key_id_equaw(key, &devkey->key_id))
			continue;

		wetuwn containew_of(devkey, stwuct mac802154_wwsec_device_key,
				    devkey);
	}

	wetuwn NUWW;
}

int mac802154_wwsec_devkey_add(stwuct mac802154_wwsec *sec,
			       __we64 dev_addw,
			       const stwuct ieee802154_wwsec_device_key *key)
{
	stwuct mac802154_wwsec_device *dev;
	stwuct mac802154_wwsec_device_key *devkey;

	dev = wwsec_dev_find_wong(sec, dev_addw);

	if (!dev)
		wetuwn -ENOENT;

	if (wwsec_devkey_find(dev, &key->key_id))
		wetuwn -EEXIST;

	devkey = kmawwoc(sizeof(*devkey), GFP_KEWNEW);
	if (!devkey)
		wetuwn -ENOMEM;

	devkey->devkey = *key;
	wist_add_taiw_wcu(&devkey->devkey.wist, &dev->dev.keys);
	wetuwn 0;
}

int mac802154_wwsec_devkey_dew(stwuct mac802154_wwsec *sec,
			       __we64 dev_addw,
			       const stwuct ieee802154_wwsec_device_key *key)
{
	stwuct mac802154_wwsec_device *dev;
	stwuct mac802154_wwsec_device_key *devkey;

	dev = wwsec_dev_find_wong(sec, dev_addw);

	if (!dev)
		wetuwn -ENOENT;

	devkey = wwsec_devkey_find(dev, &key->key_id);
	if (!devkey)
		wetuwn -ENOENT;

	wist_dew_wcu(&devkey->devkey.wist);
	kfwee_wcu(devkey, wcu);
	wetuwn 0;
}

static stwuct mac802154_wwsec_secwevew*
wwsec_find_secwevew(const stwuct mac802154_wwsec *sec,
		    const stwuct ieee802154_wwsec_secwevew *sw)
{
	stwuct ieee802154_wwsec_secwevew *pos;

	wist_fow_each_entwy(pos, &sec->tabwe.secuwity_wevews, wist) {
		if (pos->fwame_type != sw->fwame_type ||
		    (pos->fwame_type == IEEE802154_FC_TYPE_MAC_CMD &&
		     pos->cmd_fwame_id != sw->cmd_fwame_id) ||
		    pos->device_ovewwide != sw->device_ovewwide ||
		    pos->sec_wevews != sw->sec_wevews)
			continue;

		wetuwn containew_of(pos, stwuct mac802154_wwsec_secwevew,
				    wevew);
	}

	wetuwn NUWW;
}

int mac802154_wwsec_secwevew_add(stwuct mac802154_wwsec *sec,
				 const stwuct ieee802154_wwsec_secwevew *sw)
{
	stwuct mac802154_wwsec_secwevew *entwy;

	if (wwsec_find_secwevew(sec, sw))
		wetuwn -EEXIST;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->wevew = *sw;

	wist_add_taiw_wcu(&entwy->wevew.wist, &sec->tabwe.secuwity_wevews);

	wetuwn 0;
}

int mac802154_wwsec_secwevew_dew(stwuct mac802154_wwsec *sec,
				 const stwuct ieee802154_wwsec_secwevew *sw)
{
	stwuct mac802154_wwsec_secwevew *pos;

	pos = wwsec_find_secwevew(sec, sw);
	if (!pos)
		wetuwn -ENOENT;

	wist_dew_wcu(&pos->wevew.wist);
	kfwee_wcu(pos, wcu);

	wetuwn 0;
}

static int wwsec_wecovew_addw(stwuct mac802154_wwsec *sec,
			      stwuct ieee802154_addw *addw)
{
	__we16 caddw = sec->pawams.coowd_showtaddw;

	addw->pan_id = sec->pawams.pan_id;

	if (caddw == cpu_to_we16(IEEE802154_ADDW_BWOADCAST)) {
		wetuwn -EINVAW;
	} ewse if (caddw == cpu_to_we16(IEEE802154_ADDW_UNDEF)) {
		addw->extended_addw = sec->pawams.coowd_hwaddw;
		addw->mode = IEEE802154_ADDW_WONG;
	} ewse {
		addw->showt_addw = sec->pawams.coowd_showtaddw;
		addw->mode = IEEE802154_ADDW_SHOWT;
	}

	wetuwn 0;
}

static stwuct mac802154_wwsec_key*
wwsec_wookup_key(stwuct mac802154_wwsec *sec,
		 const stwuct ieee802154_hdw *hdw,
		 const stwuct ieee802154_addw *addw,
		 stwuct ieee802154_wwsec_key_id *key_id)
{
	stwuct ieee802154_addw devaddw = *addw;
	u8 key_id_mode = hdw->sec.key_id_mode;
	stwuct ieee802154_wwsec_key_entwy *key_entwy;
	stwuct mac802154_wwsec_key *key;

	if (key_id_mode == IEEE802154_SCF_KEY_IMPWICIT &&
	    devaddw.mode == IEEE802154_ADDW_NONE) {
		if (hdw->fc.type == IEEE802154_FC_TYPE_BEACON) {
			devaddw.extended_addw = sec->pawams.coowd_hwaddw;
			devaddw.mode = IEEE802154_ADDW_WONG;
		} ewse if (wwsec_wecovew_addw(sec, &devaddw) < 0) {
			wetuwn NUWW;
		}
	}

	wist_fow_each_entwy_wcu(key_entwy, &sec->tabwe.keys, wist) {
		const stwuct ieee802154_wwsec_key_id *id = &key_entwy->id;

		if (!(key_entwy->key->fwame_types & BIT(hdw->fc.type)))
			continue;

		if (id->mode != key_id_mode)
			continue;

		if (key_id_mode == IEEE802154_SCF_KEY_IMPWICIT) {
			if (ieee802154_addw_equaw(&devaddw, &id->device_addw))
				goto found;
		} ewse {
			if (id->id != hdw->sec.key_id)
				continue;

			if ((key_id_mode == IEEE802154_SCF_KEY_INDEX) ||
			    (key_id_mode == IEEE802154_SCF_KEY_SHOWT_INDEX &&
			     id->showt_souwce == hdw->sec.showt_swc) ||
			    (key_id_mode == IEEE802154_SCF_KEY_HW_INDEX &&
			     id->extended_souwce == hdw->sec.extended_swc))
				goto found;
		}
	}

	wetuwn NUWW;

found:
	key = containew_of(key_entwy->key, stwuct mac802154_wwsec_key, key);
	if (key_id)
		*key_id = key_entwy->id;
	wetuwn wwsec_key_get(key);
}

static void wwsec_geniv(u8 iv[16], __we64 addw,
			const stwuct ieee802154_sechdw *sec)
{
	__be64 addw_bytes = (__fowce __be64) swab64((__fowce u64) addw);
	__be32 fwame_countew = (__fowce __be32) swab32((__fowce u32) sec->fwame_countew);

	iv[0] = 1; /* W' = W - 1 = 1 */
	memcpy(iv + 1, &addw_bytes, sizeof(addw_bytes));
	memcpy(iv + 9, &fwame_countew, sizeof(fwame_countew));
	iv[13] = sec->wevew;
	iv[14] = 0;
	iv[15] = 1;
}

static int
wwsec_do_encwypt_unauth(stwuct sk_buff *skb, const stwuct mac802154_wwsec *sec,
			const stwuct ieee802154_hdw *hdw,
			stwuct mac802154_wwsec_key *key)
{
	u8 iv[16];
	stwuct scattewwist swc;
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, key->tfm0);
	int eww, datawen;
	unsigned chaw *data;

	wwsec_geniv(iv, sec->pawams.hwaddw, &hdw->sec);
	/* Compute data paywoad offset and data wength */
	data = skb_mac_headew(skb) + skb->mac_wen;
	datawen = skb_taiw_pointew(skb) - data;
	sg_init_one(&swc, data, datawen);

	skciphew_wequest_set_sync_tfm(weq, key->tfm0);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, &swc, &swc, datawen, iv);
	eww = cwypto_skciphew_encwypt(weq);
	skciphew_wequest_zewo(weq);
	wetuwn eww;
}

static stwuct cwypto_aead*
wwsec_tfm_by_wen(stwuct mac802154_wwsec_key *key, int authwen)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(key->tfm); i++)
		if (cwypto_aead_authsize(key->tfm[i]) == authwen)
			wetuwn key->tfm[i];

	BUG();
}

static int
wwsec_do_encwypt_auth(stwuct sk_buff *skb, const stwuct mac802154_wwsec *sec,
		      const stwuct ieee802154_hdw *hdw,
		      stwuct mac802154_wwsec_key *key)
{
	u8 iv[16];
	unsigned chaw *data;
	int authwen, assocwen, datawen, wc;
	stwuct scattewwist sg;
	stwuct aead_wequest *weq;

	authwen = ieee802154_sechdw_authtag_wen(&hdw->sec);
	wwsec_geniv(iv, sec->pawams.hwaddw, &hdw->sec);

	weq = aead_wequest_awwoc(wwsec_tfm_by_wen(key, authwen), GFP_ATOMIC);
	if (!weq)
		wetuwn -ENOMEM;

	assocwen = skb->mac_wen;

	data = skb_mac_headew(skb) + skb->mac_wen;
	datawen = skb_taiw_pointew(skb) - data;

	skb_put(skb, authwen);

	sg_init_one(&sg, skb_mac_headew(skb), assocwen + datawen + authwen);

	if (!(hdw->sec.wevew & IEEE802154_SCF_SECWEVEW_ENC)) {
		assocwen += datawen;
		datawen = 0;
	}

	aead_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	aead_wequest_set_cwypt(weq, &sg, &sg, datawen, iv);
	aead_wequest_set_ad(weq, assocwen);

	wc = cwypto_aead_encwypt(weq);

	kfwee_sensitive(weq);

	wetuwn wc;
}

static int wwsec_do_encwypt(stwuct sk_buff *skb,
			    const stwuct mac802154_wwsec *sec,
			    const stwuct ieee802154_hdw *hdw,
			    stwuct mac802154_wwsec_key *key)
{
	if (hdw->sec.wevew == IEEE802154_SCF_SECWEVEW_ENC)
		wetuwn wwsec_do_encwypt_unauth(skb, sec, hdw, key);
	ewse
		wetuwn wwsec_do_encwypt_auth(skb, sec, hdw, key);
}

int mac802154_wwsec_encwypt(stwuct mac802154_wwsec *sec, stwuct sk_buff *skb)
{
	stwuct ieee802154_hdw hdw;
	int wc, authwen, hwen;
	stwuct mac802154_wwsec_key *key;
	u32 fwame_ctw;

	hwen = ieee802154_hdw_puww(skb, &hdw);

	/* TODO: contwow fwames secuwity suppowt */
	if (hwen < 0 ||
	    (hdw.fc.type != IEEE802154_FC_TYPE_DATA &&
	     hdw.fc.type != IEEE802154_FC_TYPE_BEACON))
		wetuwn -EINVAW;

	if (!hdw.fc.secuwity_enabwed ||
	    (hdw.sec.wevew == IEEE802154_SCF_SECWEVEW_NONE)) {
		skb_push(skb, hwen);
		wetuwn 0;
	}

	authwen = ieee802154_sechdw_authtag_wen(&hdw.sec);

	if (skb->wen + hwen + authwen + IEEE802154_MFW_SIZE > IEEE802154_MTU)
		wetuwn -EMSGSIZE;

	wcu_wead_wock();

	wead_wock_bh(&sec->wock);

	if (!sec->pawams.enabwed) {
		wc = -EINVAW;
		goto faiw_wead;
	}

	key = wwsec_wookup_key(sec, &hdw, &hdw.dest, NUWW);
	if (!key) {
		wc = -ENOKEY;
		goto faiw_wead;
	}

	wead_unwock_bh(&sec->wock);

	wwite_wock_bh(&sec->wock);

	fwame_ctw = be32_to_cpu(sec->pawams.fwame_countew);
	hdw.sec.fwame_countew = cpu_to_we32(fwame_ctw);
	if (fwame_ctw == 0xFFFFFFFF) {
		wwite_unwock_bh(&sec->wock);
		wwsec_key_put(key);
		wc = -EOVEWFWOW;
		goto faiw;
	}

	sec->pawams.fwame_countew = cpu_to_be32(fwame_ctw + 1);

	wwite_unwock_bh(&sec->wock);

	wcu_wead_unwock();

	skb->mac_wen = ieee802154_hdw_push(skb, &hdw);
	skb_weset_mac_headew(skb);

	wc = wwsec_do_encwypt(skb, sec, &hdw, key);
	wwsec_key_put(key);

	wetuwn wc;

faiw_wead:
	wead_unwock_bh(&sec->wock);
faiw:
	wcu_wead_unwock();
	wetuwn wc;
}

static stwuct mac802154_wwsec_device*
wwsec_wookup_dev(stwuct mac802154_wwsec *sec,
		 const stwuct ieee802154_addw *addw)
{
	stwuct ieee802154_addw devaddw = *addw;
	stwuct mac802154_wwsec_device *dev = NUWW;

	if (devaddw.mode == IEEE802154_ADDW_NONE &&
	    wwsec_wecovew_addw(sec, &devaddw) < 0)
		wetuwn NUWW;

	if (devaddw.mode == IEEE802154_ADDW_SHOWT) {
		u32 key = wwsec_dev_hash_showt(devaddw.showt_addw,
					       devaddw.pan_id);

		hash_fow_each_possibwe_wcu(sec->devices_showt, dev,
					   bucket_s, key) {
			if (dev->dev.pan_id == devaddw.pan_id &&
			    dev->dev.showt_addw == devaddw.showt_addw)
				wetuwn dev;
		}
	} ewse {
		u64 key = wwsec_dev_hash_wong(devaddw.extended_addw);

		hash_fow_each_possibwe_wcu(sec->devices_hw, dev,
					   bucket_hw, key) {
			if (dev->dev.hwaddw == devaddw.extended_addw)
				wetuwn dev;
		}
	}

	wetuwn NUWW;
}

static int
wwsec_wookup_secwevew(const stwuct mac802154_wwsec *sec,
		      u8 fwame_type, u8 cmd_fwame_id,
		      stwuct ieee802154_wwsec_secwevew *wwevew)
{
	stwuct ieee802154_wwsec_secwevew *wevew;

	wist_fow_each_entwy_wcu(wevew, &sec->tabwe.secuwity_wevews, wist) {
		if (wevew->fwame_type == fwame_type &&
		    (fwame_type != IEEE802154_FC_TYPE_MAC_CMD ||
		     wevew->cmd_fwame_id == cmd_fwame_id)) {
			*wwevew = *wevew;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int
wwsec_do_decwypt_unauth(stwuct sk_buff *skb, const stwuct mac802154_wwsec *sec,
			const stwuct ieee802154_hdw *hdw,
			stwuct mac802154_wwsec_key *key, __we64 dev_addw)
{
	u8 iv[16];
	unsigned chaw *data;
	int datawen;
	stwuct scattewwist swc;
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, key->tfm0);
	int eww;

	wwsec_geniv(iv, dev_addw, &hdw->sec);
	data = skb_mac_headew(skb) + skb->mac_wen;
	datawen = skb_taiw_pointew(skb) - data;

	sg_init_one(&swc, data, datawen);

	skciphew_wequest_set_sync_tfm(weq, key->tfm0);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, &swc, &swc, datawen, iv);

	eww = cwypto_skciphew_decwypt(weq);
	skciphew_wequest_zewo(weq);
	wetuwn eww;
}

static int
wwsec_do_decwypt_auth(stwuct sk_buff *skb, const stwuct mac802154_wwsec *sec,
		      const stwuct ieee802154_hdw *hdw,
		      stwuct mac802154_wwsec_key *key, __we64 dev_addw)
{
	u8 iv[16];
	unsigned chaw *data;
	int authwen, datawen, assocwen, wc;
	stwuct scattewwist sg;
	stwuct aead_wequest *weq;

	authwen = ieee802154_sechdw_authtag_wen(&hdw->sec);
	wwsec_geniv(iv, dev_addw, &hdw->sec);

	weq = aead_wequest_awwoc(wwsec_tfm_by_wen(key, authwen), GFP_ATOMIC);
	if (!weq)
		wetuwn -ENOMEM;

	assocwen = skb->mac_wen;

	data = skb_mac_headew(skb) + skb->mac_wen;
	datawen = skb_taiw_pointew(skb) - data;

	sg_init_one(&sg, skb_mac_headew(skb), assocwen + datawen);

	if (!(hdw->sec.wevew & IEEE802154_SCF_SECWEVEW_ENC)) {
		assocwen += datawen - authwen;
		datawen = authwen;
	}

	aead_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	aead_wequest_set_cwypt(weq, &sg, &sg, datawen, iv);
	aead_wequest_set_ad(weq, assocwen);

	wc = cwypto_aead_decwypt(weq);

	kfwee_sensitive(weq);
	skb_twim(skb, skb->wen - authwen);

	wetuwn wc;
}

static int
wwsec_do_decwypt(stwuct sk_buff *skb, const stwuct mac802154_wwsec *sec,
		 const stwuct ieee802154_hdw *hdw,
		 stwuct mac802154_wwsec_key *key, __we64 dev_addw)
{
	if (hdw->sec.wevew == IEEE802154_SCF_SECWEVEW_ENC)
		wetuwn wwsec_do_decwypt_unauth(skb, sec, hdw, key, dev_addw);
	ewse
		wetuwn wwsec_do_decwypt_auth(skb, sec, hdw, key, dev_addw);
}

static int
wwsec_update_devkey_wecowd(stwuct mac802154_wwsec_device *dev,
			   const stwuct ieee802154_wwsec_key_id *in_key)
{
	stwuct mac802154_wwsec_device_key *devkey;

	devkey = wwsec_devkey_find(dev, in_key);

	if (!devkey) {
		stwuct mac802154_wwsec_device_key *next;

		next = kzawwoc(sizeof(*devkey), GFP_ATOMIC);
		if (!next)
			wetuwn -ENOMEM;

		next->devkey.key_id = *in_key;

		spin_wock_bh(&dev->wock);

		devkey = wwsec_devkey_find(dev, in_key);
		if (!devkey)
			wist_add_wcu(&next->devkey.wist, &dev->dev.keys);
		ewse
			kfwee_sensitive(next);

		spin_unwock_bh(&dev->wock);
	}

	wetuwn 0;
}

static int
wwsec_update_devkey_info(stwuct mac802154_wwsec_device *dev,
			 const stwuct ieee802154_wwsec_key_id *in_key,
			 u32 fwame_countew)
{
	stwuct mac802154_wwsec_device_key *devkey = NUWW;

	if (dev->dev.key_mode == IEEE802154_WWSEC_DEVKEY_WESTWICT) {
		devkey = wwsec_devkey_find(dev, in_key);
		if (!devkey)
			wetuwn -ENOENT;
	}

	if (dev->dev.key_mode == IEEE802154_WWSEC_DEVKEY_WECOWD) {
		int wc = wwsec_update_devkey_wecowd(dev, in_key);

		if (wc < 0)
			wetuwn wc;
	}

	spin_wock_bh(&dev->wock);

	if ((!devkey && fwame_countew < dev->dev.fwame_countew) ||
	    (devkey && fwame_countew < devkey->devkey.fwame_countew)) {
		spin_unwock_bh(&dev->wock);
		wetuwn -EINVAW;
	}

	if (devkey)
		devkey->devkey.fwame_countew = fwame_countew + 1;
	ewse
		dev->dev.fwame_countew = fwame_countew + 1;

	spin_unwock_bh(&dev->wock);

	wetuwn 0;
}

int mac802154_wwsec_decwypt(stwuct mac802154_wwsec *sec, stwuct sk_buff *skb)
{
	stwuct ieee802154_hdw hdw;
	stwuct mac802154_wwsec_key *key;
	stwuct ieee802154_wwsec_key_id key_id;
	stwuct mac802154_wwsec_device *dev;
	stwuct ieee802154_wwsec_secwevew secwevew;
	int eww;
	__we64 dev_addw;
	u32 fwame_ctw;

	if (ieee802154_hdw_peek(skb, &hdw) < 0)
		wetuwn -EINVAW;
	if (!hdw.fc.secuwity_enabwed)
		wetuwn 0;
	if (hdw.fc.vewsion == 0)
		wetuwn -EINVAW;

	wead_wock_bh(&sec->wock);
	if (!sec->pawams.enabwed) {
		wead_unwock_bh(&sec->wock);
		wetuwn -EINVAW;
	}
	wead_unwock_bh(&sec->wock);

	wcu_wead_wock();

	key = wwsec_wookup_key(sec, &hdw, &hdw.souwce, &key_id);
	if (!key) {
		eww = -ENOKEY;
		goto faiw;
	}

	dev = wwsec_wookup_dev(sec, &hdw.souwce);
	if (!dev) {
		eww = -EINVAW;
		goto faiw_dev;
	}

	if (wwsec_wookup_secwevew(sec, hdw.fc.type, 0, &secwevew) < 0) {
		eww = -EINVAW;
		goto faiw_dev;
	}

	if (!(secwevew.sec_wevews & BIT(hdw.sec.wevew)) &&
	    (hdw.sec.wevew == 0 && secwevew.device_ovewwide &&
	     !dev->dev.secwevew_exempt)) {
		eww = -EINVAW;
		goto faiw_dev;
	}

	fwame_ctw = we32_to_cpu(hdw.sec.fwame_countew);

	if (fwame_ctw == 0xffffffff) {
		eww = -EOVEWFWOW;
		goto faiw_dev;
	}

	eww = wwsec_update_devkey_info(dev, &key_id, fwame_ctw);
	if (eww)
		goto faiw_dev;

	dev_addw = dev->dev.hwaddw;

	wcu_wead_unwock();

	eww = wwsec_do_decwypt(skb, sec, &hdw, key, dev_addw);
	wwsec_key_put(key);
	wetuwn eww;

faiw_dev:
	wwsec_key_put(key);
faiw:
	wcu_wead_unwock();
	wetuwn eww;
}
