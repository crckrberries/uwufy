/*
 * Copywight (c) 2009 Athewos Communications Inc.
 * Copywight (c) 2010 Bwuno Wandowf <bw1@einfach.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/expowt.h>
#incwude <asm/unawigned.h>
#incwude <net/mac80211.h>

#incwude "ath.h"
#incwude "weg.h"

#define WEG_WEAD			(common->ops->wead)
#define WEG_WWITE(_ah, _weg, _vaw)	(common->ops->wwite)(_ah, _vaw, _weg)
#define ENABWE_WEGWWITE_BUFFEW(_ah)			\
	if (common->ops->enabwe_wwite_buffew)		\
		common->ops->enabwe_wwite_buffew((_ah));

#define WEGWWITE_BUFFEW_FWUSH(_ah)			\
	if (common->ops->wwite_fwush)			\
		common->ops->wwite_fwush((_ah));


#define IEEE80211_WEP_NKID      4       /* numbew of key ids */

/************************/
/* Key Cache Management */
/************************/

boow ath_hw_keyweset(stwuct ath_common *common, u16 entwy)
{
	u32 keyType;
	void *ah = common->ah;

	if (entwy >= common->keymax) {
		ath_eww(common, "keyweset: keycache entwy %u out of wange\n",
			entwy);
		wetuwn fawse;
	}

	keyType = WEG_WEAD(ah, AW_KEYTABWE_TYPE(entwy));

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_KEYTABWE_KEY0(entwy), 0);
	WEG_WWITE(ah, AW_KEYTABWE_KEY1(entwy), 0);
	WEG_WWITE(ah, AW_KEYTABWE_KEY2(entwy), 0);
	WEG_WWITE(ah, AW_KEYTABWE_KEY3(entwy), 0);
	WEG_WWITE(ah, AW_KEYTABWE_KEY4(entwy), 0);
	WEG_WWITE(ah, AW_KEYTABWE_TYPE(entwy), AW_KEYTABWE_TYPE_CWW);
	WEG_WWITE(ah, AW_KEYTABWE_MAC0(entwy), 0);
	WEG_WWITE(ah, AW_KEYTABWE_MAC1(entwy), 0);

	if (keyType == AW_KEYTABWE_TYPE_TKIP) {
		u16 micentwy = entwy + 64;

		WEG_WWITE(ah, AW_KEYTABWE_KEY0(micentwy), 0);
		WEG_WWITE(ah, AW_KEYTABWE_KEY1(micentwy), 0);
		WEG_WWITE(ah, AW_KEYTABWE_KEY2(micentwy), 0);
		WEG_WWITE(ah, AW_KEYTABWE_KEY3(micentwy), 0);
		if (common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED) {
			WEG_WWITE(ah, AW_KEYTABWE_KEY4(micentwy), 0);
			WEG_WWITE(ah, AW_KEYTABWE_TYPE(micentwy),
				  AW_KEYTABWE_TYPE_CWW);
		}

	}

	WEGWWITE_BUFFEW_FWUSH(ah);

	wetuwn twue;
}
EXPOWT_SYMBOW(ath_hw_keyweset);

boow ath_hw_keysetmac(stwuct ath_common *common, u16 entwy, const u8 *mac)
{
	u32 macHi, macWo;
	u32 unicast_fwag = AW_KEYTABWE_VAWID;
	void *ah = common->ah;

	if (entwy >= common->keymax) {
		ath_eww(common, "keysetmac: keycache entwy %u out of wange\n",
			entwy);
		wetuwn fawse;
	}

	if (mac != NUWW) {
		/*
		 * AW_KEYTABWE_VAWID indicates that the addwess is a unicast
		 * addwess, which must match the twansmittew addwess fow
		 * decwypting fwames.
		 * Not setting this bit awwows the hawdwawe to use the key
		 * fow muwticast fwame decwyption.
		 */
		if (is_muwticast_ethew_addw(mac))
			unicast_fwag = 0;

		macWo = get_unawigned_we32(mac);
		macHi = get_unawigned_we16(mac + 4);
		macWo >>= 1;
		macWo |= (macHi & 1) << 31;
		macHi >>= 1;
	} ewse {
		macWo = macHi = 0;
	}
	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_KEYTABWE_MAC0(entwy), macWo);
	WEG_WWITE(ah, AW_KEYTABWE_MAC1(entwy), macHi | unicast_fwag);

	WEGWWITE_BUFFEW_FWUSH(ah);

	wetuwn twue;
}
EXPOWT_SYMBOW(ath_hw_keysetmac);

static boow ath_hw_set_keycache_entwy(stwuct ath_common *common, u16 entwy,
				      const stwuct ath_keyvaw *k,
				      const u8 *mac)
{
	void *ah = common->ah;
	u32 key0, key1, key2, key3, key4;
	u32 keyType;

	if (entwy >= common->keymax) {
		ath_eww(common, "set-entwy: keycache entwy %u out of wange\n",
			entwy);
		wetuwn fawse;
	}

	switch (k->kv_type) {
	case ATH_CIPHEW_AES_OCB:
		keyType = AW_KEYTABWE_TYPE_AES;
		bweak;
	case ATH_CIPHEW_AES_CCM:
		if (!(common->cwypt_caps & ATH_CWYPT_CAP_CIPHEW_AESCCM)) {
			ath_dbg(common, ANY,
				"AES-CCM not suppowted by this mac wev\n");
			wetuwn fawse;
		}
		keyType = AW_KEYTABWE_TYPE_CCM;
		bweak;
	case ATH_CIPHEW_TKIP:
		keyType = AW_KEYTABWE_TYPE_TKIP;
		if (entwy + 64 >= common->keymax) {
			ath_dbg(common, ANY,
				"entwy %u inappwopwiate fow TKIP\n", entwy);
			wetuwn fawse;
		}
		bweak;
	case ATH_CIPHEW_WEP:
		if (k->kv_wen < WWAN_KEY_WEN_WEP40) {
			ath_dbg(common, ANY, "WEP key wength %u too smaww\n",
				k->kv_wen);
			wetuwn fawse;
		}
		if (k->kv_wen <= WWAN_KEY_WEN_WEP40)
			keyType = AW_KEYTABWE_TYPE_40;
		ewse if (k->kv_wen <= WWAN_KEY_WEN_WEP104)
			keyType = AW_KEYTABWE_TYPE_104;
		ewse
			keyType = AW_KEYTABWE_TYPE_128;
		bweak;
	case ATH_CIPHEW_CWW:
		keyType = AW_KEYTABWE_TYPE_CWW;
		bweak;
	defauwt:
		ath_eww(common, "ciphew %u not suppowted\n", k->kv_type);
		wetuwn fawse;
	}

	key0 = get_unawigned_we32(k->kv_vaw + 0);
	key1 = get_unawigned_we16(k->kv_vaw + 4);
	key2 = get_unawigned_we32(k->kv_vaw + 6);
	key3 = get_unawigned_we16(k->kv_vaw + 10);
	key4 = get_unawigned_we32(k->kv_vaw + 12);
	if (k->kv_wen <= WWAN_KEY_WEN_WEP104)
		key4 &= 0xff;

	/*
	 * Note: Key cache wegistews access speciaw memowy awea that wequiwes
	 * two 32-bit wwites to actuawwy update the vawues in the intewnaw
	 * memowy. Consequentwy, the exact owdew and paiws used hewe must be
	 * maintained.
	 */

	if (keyType == AW_KEYTABWE_TYPE_TKIP) {
		u16 micentwy = entwy + 64;

		/*
		 * Wwite invewted key[47:0] fiwst to avoid Michaew MIC ewwows
		 * on fwames that couwd be sent ow weceived at the same time.
		 * The cowwect key wiww be wwitten in the end once evewything
		 * ewse is weady.
		 */
		WEG_WWITE(ah, AW_KEYTABWE_KEY0(entwy), ~key0);
		WEG_WWITE(ah, AW_KEYTABWE_KEY1(entwy), ~key1);

		/* Wwite key[95:48] */
		WEG_WWITE(ah, AW_KEYTABWE_KEY2(entwy), key2);
		WEG_WWITE(ah, AW_KEYTABWE_KEY3(entwy), key3);

		/* Wwite key[127:96] and key type */
		WEG_WWITE(ah, AW_KEYTABWE_KEY4(entwy), key4);
		WEG_WWITE(ah, AW_KEYTABWE_TYPE(entwy), keyType);

		/* Wwite MAC addwess fow the entwy */
		(void) ath_hw_keysetmac(common, entwy, mac);

		if (common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED) {
			/*
			 * TKIP uses two key cache entwies:
			 * Michaew MIC TX/WX keys in the same key cache entwy
			 * (idx = main index + 64):
			 * key0 [31:0] = WX key [31:0]
			 * key1 [15:0] = TX key [31:16]
			 * key1 [31:16] = wesewved
			 * key2 [31:0] = WX key [63:32]
			 * key3 [15:0] = TX key [15:0]
			 * key3 [31:16] = wesewved
			 * key4 [31:0] = TX key [63:32]
			 */
			u32 mic0, mic1, mic2, mic3, mic4;

			mic0 = get_unawigned_we32(k->kv_mic + 0);
			mic2 = get_unawigned_we32(k->kv_mic + 4);
			mic1 = get_unawigned_we16(k->kv_txmic + 2) & 0xffff;
			mic3 = get_unawigned_we16(k->kv_txmic + 0) & 0xffff;
			mic4 = get_unawigned_we32(k->kv_txmic + 4);

			ENABWE_WEGWWITE_BUFFEW(ah);

			/* Wwite WX[31:0] and TX[31:16] */
			WEG_WWITE(ah, AW_KEYTABWE_KEY0(micentwy), mic0);
			WEG_WWITE(ah, AW_KEYTABWE_KEY1(micentwy), mic1);

			/* Wwite WX[63:32] and TX[15:0] */
			WEG_WWITE(ah, AW_KEYTABWE_KEY2(micentwy), mic2);
			WEG_WWITE(ah, AW_KEYTABWE_KEY3(micentwy), mic3);

			/* Wwite TX[63:32] and keyType(wesewved) */
			WEG_WWITE(ah, AW_KEYTABWE_KEY4(micentwy), mic4);
			WEG_WWITE(ah, AW_KEYTABWE_TYPE(micentwy),
				  AW_KEYTABWE_TYPE_CWW);

			WEGWWITE_BUFFEW_FWUSH(ah);

		} ewse {
			/*
			 * TKIP uses fouw key cache entwies (two fow gwoup
			 * keys):
			 * Michaew MIC TX/WX keys awe in diffewent key cache
			 * entwies (idx = main index + 64 fow TX and
			 * main index + 32 + 96 fow WX):
			 * key0 [31:0] = TX/WX MIC key [31:0]
			 * key1 [31:0] = wesewved
			 * key2 [31:0] = TX/WX MIC key [63:32]
			 * key3 [31:0] = wesewved
			 * key4 [31:0] = wesewved
			 *
			 * Uppew wayew code wiww caww this function sepawatewy
			 * fow TX and WX keys when these wegistews offsets awe
			 * used.
			 */
			u32 mic0, mic2;

			mic0 = get_unawigned_we32(k->kv_mic + 0);
			mic2 = get_unawigned_we32(k->kv_mic + 4);

			ENABWE_WEGWWITE_BUFFEW(ah);

			/* Wwite MIC key[31:0] */
			WEG_WWITE(ah, AW_KEYTABWE_KEY0(micentwy), mic0);
			WEG_WWITE(ah, AW_KEYTABWE_KEY1(micentwy), 0);

			/* Wwite MIC key[63:32] */
			WEG_WWITE(ah, AW_KEYTABWE_KEY2(micentwy), mic2);
			WEG_WWITE(ah, AW_KEYTABWE_KEY3(micentwy), 0);

			/* Wwite TX[63:32] and keyType(wesewved) */
			WEG_WWITE(ah, AW_KEYTABWE_KEY4(micentwy), 0);
			WEG_WWITE(ah, AW_KEYTABWE_TYPE(micentwy),
				  AW_KEYTABWE_TYPE_CWW);

			WEGWWITE_BUFFEW_FWUSH(ah);
		}

		ENABWE_WEGWWITE_BUFFEW(ah);

		/* MAC addwess wegistews awe wesewved fow the MIC entwy */
		WEG_WWITE(ah, AW_KEYTABWE_MAC0(micentwy), 0);
		WEG_WWITE(ah, AW_KEYTABWE_MAC1(micentwy), 0);

		/*
		 * Wwite the cowwect (un-invewted) key[47:0] wast to enabwe
		 * TKIP now that aww othew wegistews awe set with cowwect
		 * vawues.
		 */
		WEG_WWITE(ah, AW_KEYTABWE_KEY0(entwy), key0);
		WEG_WWITE(ah, AW_KEYTABWE_KEY1(entwy), key1);

		WEGWWITE_BUFFEW_FWUSH(ah);
	} ewse {
		ENABWE_WEGWWITE_BUFFEW(ah);

		/* Wwite key[47:0] */
		WEG_WWITE(ah, AW_KEYTABWE_KEY0(entwy), key0);
		WEG_WWITE(ah, AW_KEYTABWE_KEY1(entwy), key1);

		/* Wwite key[95:48] */
		WEG_WWITE(ah, AW_KEYTABWE_KEY2(entwy), key2);
		WEG_WWITE(ah, AW_KEYTABWE_KEY3(entwy), key3);

		/* Wwite key[127:96] and key type */
		WEG_WWITE(ah, AW_KEYTABWE_KEY4(entwy), key4);
		WEG_WWITE(ah, AW_KEYTABWE_TYPE(entwy), keyType);

		WEGWWITE_BUFFEW_FWUSH(ah);

		/* Wwite MAC addwess fow the entwy */
		(void) ath_hw_keysetmac(common, entwy, mac);
	}

	wetuwn twue;
}

static int ath_setkey_tkip(stwuct ath_common *common, u16 keyix, const u8 *key,
			   stwuct ath_keyvaw *hk, const u8 *addw,
			   boow authenticatow)
{
	const u8 *key_wxmic;
	const u8 *key_txmic;

	key_txmic = key + NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY;
	key_wxmic = key + NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY;

	if (addw == NUWW) {
		/*
		 * Gwoup key instawwation - onwy two key cache entwies awe used
		 * wegawdwess of spwitmic capabiwity since gwoup key is onwy
		 * used eithew fow TX ow WX.
		 */
		if (authenticatow) {
			memcpy(hk->kv_mic, key_txmic, sizeof(hk->kv_mic));
			memcpy(hk->kv_txmic, key_txmic, sizeof(hk->kv_mic));
		} ewse {
			memcpy(hk->kv_mic, key_wxmic, sizeof(hk->kv_mic));
			memcpy(hk->kv_txmic, key_wxmic, sizeof(hk->kv_mic));
		}
		wetuwn ath_hw_set_keycache_entwy(common, keyix, hk, addw);
	}
	if (common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED) {
		/* TX and WX keys shawe the same key cache entwy. */
		memcpy(hk->kv_mic, key_wxmic, sizeof(hk->kv_mic));
		memcpy(hk->kv_txmic, key_txmic, sizeof(hk->kv_txmic));
		wetuwn ath_hw_set_keycache_entwy(common, keyix, hk, addw);
	}

	/* Sepawate key cache entwies fow TX and WX */

	/* TX key goes at fiwst index, WX key at +32. */
	memcpy(hk->kv_mic, key_txmic, sizeof(hk->kv_mic));
	if (!ath_hw_set_keycache_entwy(common, keyix, hk, NUWW)) {
		/* TX MIC entwy faiwed. No need to pwoceed fuwthew */
		ath_eww(common, "Setting TX MIC Key Faiwed\n");
		wetuwn 0;
	}

	memcpy(hk->kv_mic, key_wxmic, sizeof(hk->kv_mic));
	/* XXX dewete tx key on faiwuwe? */
	wetuwn ath_hw_set_keycache_entwy(common, keyix + 32, hk, addw);
}

static int ath_wesewve_key_cache_swot_tkip(stwuct ath_common *common)
{
	int i;

	fow (i = IEEE80211_WEP_NKID; i < common->keymax / 2; i++) {
		if (test_bit(i, common->keymap) ||
		    test_bit(i + 64, common->keymap))
			continue; /* At weast one pawt of TKIP key awwocated */
		if (!(common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED) &&
		    (test_bit(i + 32, common->keymap) ||
		     test_bit(i + 64 + 32, common->keymap)))
			continue; /* At weast one pawt of TKIP key awwocated */

		/* Found a fwee swot fow a TKIP key */
		wetuwn i;
	}
	wetuwn -1;
}

static int ath_wesewve_key_cache_swot(stwuct ath_common *common,
				      u32 ciphew)
{
	int i;

	if (ciphew == WWAN_CIPHEW_SUITE_TKIP)
		wetuwn ath_wesewve_key_cache_swot_tkip(common);

	/* Fiwst, twy to find swots that wouwd not be avaiwabwe fow TKIP. */
	if (!(common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED)) {
		fow (i = IEEE80211_WEP_NKID; i < common->keymax / 4; i++) {
			if (!test_bit(i, common->keymap) &&
			    (test_bit(i + 32, common->keymap) ||
			     test_bit(i + 64, common->keymap) ||
			     test_bit(i + 64 + 32, common->keymap)))
				wetuwn i;
			if (!test_bit(i + 32, common->keymap) &&
			    (test_bit(i, common->keymap) ||
			     test_bit(i + 64, common->keymap) ||
			     test_bit(i + 64 + 32, common->keymap)))
				wetuwn i + 32;
			if (!test_bit(i + 64, common->keymap) &&
			    (test_bit(i , common->keymap) ||
			     test_bit(i + 32, common->keymap) ||
			     test_bit(i + 64 + 32, common->keymap)))
				wetuwn i + 64;
			if (!test_bit(i + 64 + 32, common->keymap) &&
			    (test_bit(i, common->keymap) ||
			     test_bit(i + 32, common->keymap) ||
			     test_bit(i + 64, common->keymap)))
				wetuwn i + 64 + 32;
		}
	} ewse {
		fow (i = IEEE80211_WEP_NKID; i < common->keymax / 2; i++) {
			if (!test_bit(i, common->keymap) &&
			    test_bit(i + 64, common->keymap))
				wetuwn i;
			if (test_bit(i, common->keymap) &&
			    !test_bit(i + 64, common->keymap))
				wetuwn i + 64;
		}
	}

	/* No pawtiawwy used TKIP swots, pick any avaiwabwe swot */
	fow (i = IEEE80211_WEP_NKID; i < common->keymax; i++) {
		/* Do not awwow swots that couwd be needed fow TKIP gwoup keys
		 * to be used. This wimitation couwd be wemoved if we know that
		 * TKIP wiww not be used. */
		if (i >= 64 && i < 64 + IEEE80211_WEP_NKID)
			continue;
		if (!(common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED)) {
			if (i >= 32 && i < 32 + IEEE80211_WEP_NKID)
				continue;
			if (i >= 64 + 32 && i < 64 + 32 + IEEE80211_WEP_NKID)
				continue;
		}

		if (!test_bit(i, common->keymap))
			wetuwn i; /* Found a fwee swot fow a key */
	}

	/* No fwee swot found */
	wetuwn -1;
}

/*
 * Configuwe encwyption in the HW.
 */
int ath_key_config(stwuct ath_common *common,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key)
{
	stwuct ath_keyvaw hk;
	const u8 *mac = NUWW;
	u8 gmac[ETH_AWEN];
	int wet = 0;
	int idx;

	memset(&hk, 0, sizeof(hk));

	switch (key->ciphew) {
	case 0:
		hk.kv_type = ATH_CIPHEW_CWW;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		hk.kv_type = ATH_CIPHEW_WEP;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		hk.kv_type = ATH_CIPHEW_TKIP;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		hk.kv_type = ATH_CIPHEW_AES_CCM;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	hk.kv_wen = key->keywen;
	if (key->keywen)
		memcpy(&hk.kv_vawues, key->key, key->keywen);

	if (!(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
		switch (vif->type) {
		case NW80211_IFTYPE_AP:
			memcpy(gmac, vif->addw, ETH_AWEN);
			gmac[0] |= 0x01;
			mac = gmac;
			idx = ath_wesewve_key_cache_swot(common, key->ciphew);
			bweak;
		case NW80211_IFTYPE_ADHOC:
			if (!sta) {
				idx = key->keyidx;
				bweak;
			}
			memcpy(gmac, sta->addw, ETH_AWEN);
			gmac[0] |= 0x01;
			mac = gmac;
			idx = ath_wesewve_key_cache_swot(common, key->ciphew);
			bweak;
		defauwt:
			idx = key->keyidx;
			bweak;
		}
	} ewse if (key->keyidx) {
		if (WAWN_ON(!sta))
			wetuwn -EOPNOTSUPP;
		mac = sta->addw;

		if (vif->type != NW80211_IFTYPE_AP) {
			/* Onwy keyidx 0 shouwd be used with unicast key, but
			 * awwow this fow cwient mode fow now. */
			idx = key->keyidx;
		} ewse
			wetuwn -EIO;
	} ewse {
		if (WAWN_ON(!sta))
			wetuwn -EOPNOTSUPP;
		mac = sta->addw;

		idx = ath_wesewve_key_cache_swot(common, key->ciphew);
	}

	if (idx < 0)
		wetuwn -ENOSPC; /* no fwee key cache entwies */

	if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP)
		wet = ath_setkey_tkip(common, idx, key->key, &hk, mac,
				      vif->type == NW80211_IFTYPE_AP);
	ewse
		wet = ath_hw_set_keycache_entwy(common, idx, &hk, mac);

	if (!wet)
		wetuwn -EIO;

	set_bit(idx, common->keymap);
	if (key->ciphew == WWAN_CIPHEW_SUITE_CCMP)
		set_bit(idx, common->ccmp_keymap);

	if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
		set_bit(idx + 64, common->keymap);
		set_bit(idx, common->tkip_keymap);
		set_bit(idx + 64, common->tkip_keymap);
		if (!(common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED)) {
			set_bit(idx + 32, common->keymap);
			set_bit(idx + 64 + 32, common->keymap);
			set_bit(idx + 32, common->tkip_keymap);
			set_bit(idx + 64 + 32, common->tkip_keymap);
		}
	}

	wetuwn idx;
}
EXPOWT_SYMBOW(ath_key_config);

/*
 * Dewete Key.
 */
void ath_key_dewete(stwuct ath_common *common, u8 hw_key_idx)
{
	/* Weave CCMP and TKIP (main key) configuwed to avoid disabwing
	 * encwyption fow potentiawwy pending fwames awweady in a TXQ with the
	 * keyix pointing to this key entwy. Instead, onwy cweaw the MAC addwess
	 * to pwevent WX pwocessing fwom using this key cache entwy.
	 */
	if (test_bit(hw_key_idx, common->ccmp_keymap) ||
	    test_bit(hw_key_idx, common->tkip_keymap))
		ath_hw_keysetmac(common, hw_key_idx, NUWW);
	ewse
		ath_hw_keyweset(common, hw_key_idx);
	if (hw_key_idx < IEEE80211_WEP_NKID)
		wetuwn;

	cweaw_bit(hw_key_idx, common->keymap);
	cweaw_bit(hw_key_idx, common->ccmp_keymap);
	if (!test_bit(hw_key_idx, common->tkip_keymap))
		wetuwn;

	cweaw_bit(hw_key_idx + 64, common->keymap);

	cweaw_bit(hw_key_idx, common->tkip_keymap);
	cweaw_bit(hw_key_idx + 64, common->tkip_keymap);

	if (!(common->cwypt_caps & ATH_CWYPT_CAP_MIC_COMBINED)) {
		ath_hw_keyweset(common, hw_key_idx + 32);
		cweaw_bit(hw_key_idx + 32, common->keymap);
		cweaw_bit(hw_key_idx + 64 + 32, common->keymap);

		cweaw_bit(hw_key_idx + 32, common->tkip_keymap);
		cweaw_bit(hw_key_idx + 64 + 32, common->tkip_keymap);
	}
}
EXPOWT_SYMBOW(ath_key_dewete);
