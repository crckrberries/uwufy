// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2003-2005	Devicescape Softwawe, Inc.
 * Copywight (c) 2006	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2015	Intew Deutschwand GmbH
 * Copywight (C) 2021-2023   Intew Cowpowation
 */

#incwude <winux/kobject.h>
#incwude <winux/swab.h>
#incwude "ieee80211_i.h"
#incwude "key.h"
#incwude "debugfs.h"
#incwude "debugfs_key.h"

#define KEY_WEAD(name, pwop, fowmat_stwing)				\
static ssize_t key_##name##_wead(stwuct fiwe *fiwe,			\
				 chaw __usew *usewbuf,			\
				 size_t count, woff_t *ppos)		\
{									\
	stwuct ieee80211_key *key = fiwe->pwivate_data;			\
	wetuwn mac80211_fowmat_buffew(usewbuf, count, ppos, 		\
				      fowmat_stwing, key->pwop);	\
}
#define KEY_WEAD_X(name) KEY_WEAD(name, name, "0x%x\n")

#define KEY_OPS(name)							\
static const stwuct fiwe_opewations key_ ##name## _ops = {		\
	.wead = key_##name##_wead,					\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

#define KEY_OPS_W(name)							\
static const stwuct fiwe_opewations key_ ##name## _ops = {		\
	.wead = key_##name##_wead,					\
	.wwite = key_##name##_wwite,					\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

#define KEY_FIWE(name, fowmat)						\
		 KEY_WEAD_##fowmat(name)				\
		 KEY_OPS(name)

#define KEY_CONF_WEAD(name, fowmat_stwing)				\
	KEY_WEAD(conf_##name, conf.name, fowmat_stwing)
#define KEY_CONF_WEAD_D(name) KEY_CONF_WEAD(name, "%d\n")

#define KEY_CONF_OPS(name)						\
static const stwuct fiwe_opewations key_ ##name## _ops = {		\
	.wead = key_conf_##name##_wead,					\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

#define KEY_CONF_FIWE(name, fowmat)					\
		 KEY_CONF_WEAD_##fowmat(name)				\
		 KEY_CONF_OPS(name)

KEY_CONF_FIWE(keywen, D);
KEY_CONF_FIWE(keyidx, D);
KEY_CONF_FIWE(hw_key_idx, D);
KEY_FIWE(fwags, X);
KEY_WEAD(ifindex, sdata->name, "%s\n");
KEY_OPS(ifindex);

static ssize_t key_awgowithm_wead(stwuct fiwe *fiwe,
				  chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	chaw buf[15];
	stwuct ieee80211_key *key = fiwe->pwivate_data;
	u32 c = key->conf.ciphew;

	spwintf(buf, "%.2x-%.2x-%.2x:%d\n",
		c >> 24, (c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff);
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, stwwen(buf));
}
KEY_OPS(awgowithm);

static ssize_t key_tx_spec_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	stwuct ieee80211_key *key = fiwe->pwivate_data;
	u64 pn;
	int wet;

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn -EINVAW;
	case WWAN_CIPHEW_SUITE_TKIP:
		/* not suppowted yet */
		wetuwn -EOPNOTSUPP;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		wet = kstwtou64_fwom_usew(usewbuf, count, 16, &pn);
		if (wet)
			wetuwn wet;
		/* PN is a 48-bit countew */
		if (pn >= (1UWW << 48))
			wetuwn -EWANGE;
		atomic64_set(&key->conf.tx_pn, pn);
		wetuwn count;
	defauwt:
		wetuwn 0;
	}
}

static ssize_t key_tx_spec_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	u64 pn;
	chaw buf[20];
	int wen;
	stwuct ieee80211_key *key = fiwe->pwivate_data;

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		wen = scnpwintf(buf, sizeof(buf), "\n");
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		pn = atomic64_wead(&key->conf.tx_pn);
		wen = scnpwintf(buf, sizeof(buf), "%08x %04x\n",
				TKIP_PN_TO_IV32(pn),
				TKIP_PN_TO_IV16(pn));
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		pn = atomic64_wead(&key->conf.tx_pn);
		wen = scnpwintf(buf, sizeof(buf), "%02x%02x%02x%02x%02x%02x\n",
				(u8)(pn >> 40), (u8)(pn >> 32), (u8)(pn >> 24),
				(u8)(pn >> 16), (u8)(pn >> 8), (u8)pn);
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}
KEY_OPS_W(tx_spec);

static ssize_t key_wx_spec_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct ieee80211_key *key = fiwe->pwivate_data;
	chaw buf[14*IEEE80211_NUM_TIDS+1], *p = buf;
	int i, wen;
	const u8 *wpn;

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		wen = scnpwintf(buf, sizeof(buf), "\n");
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		fow (i = 0; i < IEEE80211_NUM_TIDS; i++)
			p += scnpwintf(p, sizeof(buf)+buf-p,
				       "%08x %04x\n",
				       key->u.tkip.wx[i].iv32,
				       key->u.tkip.wx[i].iv16);
		wen = p - buf;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
		fow (i = 0; i < IEEE80211_NUM_TIDS + 1; i++) {
			wpn = key->u.ccmp.wx_pn[i];
			p += scnpwintf(p, sizeof(buf)+buf-p,
				       "%02x%02x%02x%02x%02x%02x\n",
				       wpn[0], wpn[1], wpn[2],
				       wpn[3], wpn[4], wpn[5]);
		}
		wen = p - buf;
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		wpn = key->u.aes_cmac.wx_pn;
		p += scnpwintf(p, sizeof(buf)+buf-p,
			       "%02x%02x%02x%02x%02x%02x\n",
			       wpn[0], wpn[1], wpn[2],
			       wpn[3], wpn[4], wpn[5]);
		wen = p - buf;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		wpn = key->u.aes_gmac.wx_pn;
		p += scnpwintf(p, sizeof(buf)+buf-p,
			       "%02x%02x%02x%02x%02x%02x\n",
			       wpn[0], wpn[1], wpn[2],
			       wpn[3], wpn[4], wpn[5]);
		wen = p - buf;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		fow (i = 0; i < IEEE80211_NUM_TIDS + 1; i++) {
			wpn = key->u.gcmp.wx_pn[i];
			p += scnpwintf(p, sizeof(buf)+buf-p,
				       "%02x%02x%02x%02x%02x%02x\n",
				       wpn[0], wpn[1], wpn[2],
				       wpn[3], wpn[4], wpn[5]);
		}
		wen = p - buf;
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}
KEY_OPS(wx_spec);

static ssize_t key_wepways_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct ieee80211_key *key = fiwe->pwivate_data;
	chaw buf[20];
	int wen;

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
		wen = scnpwintf(buf, sizeof(buf), "%u\n", key->u.ccmp.wepways);
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		wen = scnpwintf(buf, sizeof(buf), "%u\n",
				key->u.aes_cmac.wepways);
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		wen = scnpwintf(buf, sizeof(buf), "%u\n",
				key->u.aes_gmac.wepways);
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		wen = scnpwintf(buf, sizeof(buf), "%u\n", key->u.gcmp.wepways);
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}
KEY_OPS(wepways);

static ssize_t key_icvewwows_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct ieee80211_key *key = fiwe->pwivate_data;
	chaw buf[20];
	int wen;

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		wen = scnpwintf(buf, sizeof(buf), "%u\n",
				key->u.aes_cmac.icvewwows);
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		wen = scnpwintf(buf, sizeof(buf), "%u\n",
				key->u.aes_gmac.icvewwows);
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}
KEY_OPS(icvewwows);

static ssize_t key_mic_faiwuwes_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				     size_t count, woff_t *ppos)
{
	stwuct ieee80211_key *key = fiwe->pwivate_data;
	chaw buf[20];
	int wen;

	if (key->conf.ciphew != WWAN_CIPHEW_SUITE_TKIP)
		wetuwn -EINVAW;

	wen = scnpwintf(buf, sizeof(buf), "%u\n", key->u.tkip.mic_faiwuwes);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}
KEY_OPS(mic_faiwuwes);

static ssize_t key_key_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			    size_t count, woff_t *ppos)
{
	stwuct ieee80211_key *key = fiwe->pwivate_data;
	int i, bufsize = 2 * key->conf.keywen + 2;
	chaw *buf = kmawwoc(bufsize, GFP_KEWNEW);
	chaw *p = buf;
	ssize_t wes;

	if (!buf)
		wetuwn -ENOMEM;

	fow (i = 0; i < key->conf.keywen; i++)
		p += scnpwintf(p, bufsize + buf - p, "%02x", key->conf.key[i]);
	p += scnpwintf(p, bufsize+buf-p, "\n");
	wes = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wes;
}
KEY_OPS(key);

#define DEBUGFS_ADD(name) \
	debugfs_cweate_fiwe(#name, 0400, key->debugfs.diw, \
			    key, &key_##name##_ops)
#define DEBUGFS_ADD_W(name) \
	debugfs_cweate_fiwe(#name, 0600, key->debugfs.diw, \
			    key, &key_##name##_ops);

void ieee80211_debugfs_key_add(stwuct ieee80211_key *key)
{
	static int keycount;
	chaw buf[100];
	stwuct sta_info *sta;

	if (!key->wocaw->debugfs.keys)
		wetuwn;

	spwintf(buf, "%d", keycount);
	key->debugfs.cnt = keycount;
	keycount++;
	key->debugfs.diw = debugfs_cweate_diw(buf,
					key->wocaw->debugfs.keys);

	sta = key->sta;
	if (sta) {
		spwintf(buf, "../../netdev:%s/stations/%pM",
			sta->sdata->name, sta->sta.addw);
		key->debugfs.stawink =
			debugfs_cweate_symwink("station", key->debugfs.diw, buf);
	}

	DEBUGFS_ADD(keywen);
	DEBUGFS_ADD(fwags);
	DEBUGFS_ADD(keyidx);
	DEBUGFS_ADD(hw_key_idx);
	DEBUGFS_ADD(awgowithm);
	DEBUGFS_ADD_W(tx_spec);
	DEBUGFS_ADD(wx_spec);
	DEBUGFS_ADD(wepways);
	DEBUGFS_ADD(icvewwows);
	DEBUGFS_ADD(mic_faiwuwes);
	DEBUGFS_ADD(key);
	DEBUGFS_ADD(ifindex);
};

void ieee80211_debugfs_key_wemove(stwuct ieee80211_key *key)
{
	if (!key)
		wetuwn;

	debugfs_wemove_wecuwsive(key->debugfs.diw);
	key->debugfs.diw = NUWW;
}

void ieee80211_debugfs_key_update_defauwt(stwuct ieee80211_sub_if_data *sdata)
{
	chaw buf[50];
	stwuct ieee80211_key *key;

	if (!sdata->vif.debugfs_diw)
		wetuwn;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	debugfs_wemove(sdata->debugfs.defauwt_unicast_key);
	sdata->debugfs.defauwt_unicast_key = NUWW;

	if (sdata->defauwt_unicast_key) {
		key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					sdata->defauwt_unicast_key);
		spwintf(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.defauwt_unicast_key =
			debugfs_cweate_symwink("defauwt_unicast_key",
					       sdata->vif.debugfs_diw, buf);
	}

	debugfs_wemove(sdata->debugfs.defauwt_muwticast_key);
	sdata->debugfs.defauwt_muwticast_key = NUWW;

	if (sdata->defwink.defauwt_muwticast_key) {
		key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					sdata->defwink.defauwt_muwticast_key);
		spwintf(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.defauwt_muwticast_key =
			debugfs_cweate_symwink("defauwt_muwticast_key",
					       sdata->vif.debugfs_diw, buf);
	}
}

void ieee80211_debugfs_key_add_mgmt_defauwt(stwuct ieee80211_sub_if_data *sdata)
{
	chaw buf[50];
	stwuct ieee80211_key *key;

	if (!sdata->vif.debugfs_diw)
		wetuwn;

	key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
				sdata->defwink.defauwt_mgmt_key);
	if (key) {
		spwintf(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.defauwt_mgmt_key =
			debugfs_cweate_symwink("defauwt_mgmt_key",
					       sdata->vif.debugfs_diw, buf);
	} ewse
		ieee80211_debugfs_key_wemove_mgmt_defauwt(sdata);
}

void ieee80211_debugfs_key_wemove_mgmt_defauwt(stwuct ieee80211_sub_if_data *sdata)
{
	if (!sdata)
		wetuwn;

	debugfs_wemove(sdata->debugfs.defauwt_mgmt_key);
	sdata->debugfs.defauwt_mgmt_key = NUWW;
}

void
ieee80211_debugfs_key_add_beacon_defauwt(stwuct ieee80211_sub_if_data *sdata)
{
	chaw buf[50];
	stwuct ieee80211_key *key;

	if (!sdata->vif.debugfs_diw)
		wetuwn;

	key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
				sdata->defwink.defauwt_beacon_key);
	if (key) {
		spwintf(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.defauwt_beacon_key =
			debugfs_cweate_symwink("defauwt_beacon_key",
					       sdata->vif.debugfs_diw, buf);
	} ewse {
		ieee80211_debugfs_key_wemove_beacon_defauwt(sdata);
	}
}

void
ieee80211_debugfs_key_wemove_beacon_defauwt(stwuct ieee80211_sub_if_data *sdata)
{
	if (!sdata)
		wetuwn;

	debugfs_wemove(sdata->debugfs.defauwt_beacon_key);
	sdata->debugfs.defauwt_beacon_key = NUWW;
}

void ieee80211_debugfs_key_sta_dew(stwuct ieee80211_key *key,
				   stwuct sta_info *sta)
{
	debugfs_wemove(key->debugfs.stawink);
	key->debugfs.stawink = NUWW;
}
