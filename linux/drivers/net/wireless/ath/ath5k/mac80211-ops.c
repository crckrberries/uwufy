/*-
 * Copywight (c) 2002-2005 Sam Weffwew, Ewwno Consuwting
 * Copywight (c) 2004-2005 Athewos Communications, Inc.
 * Copywight (c) 2006 Devicescape Softwawe, Inc.
 * Copywight (c) 2007 Jiwi Swaby <jiwiswaby@gmaiw.com>
 * Copywight (c) 2007 Wuis W. Wodwiguez <mcgwof@winwab.wutgews.edu>
 * Copywight (c) 2010 Bwuno Wandowf <bw1@einfach.owg>
 *
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    simiwaw to the "NO WAWWANTY" discwaimew bewow ("Discwaimew") and any
 *    wedistwibution must be conditioned upon incwuding a substantiawwy
 *    simiwaw Discwaimew wequiwement fow fuwthew binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF NONINFWINGEMENT, MEWCHANTIBIWITY
 * AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY,
 * OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW
 * IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 * THE POSSIBIWITY OF SUCH DAMAGES.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <net/mac80211.h>
#incwude <asm/unawigned.h>

#incwude "ath5k.h"
#incwude "base.h"
#incwude "weg.h"

/********************\
* Mac80211 functions *
\********************/

static void
ath5k_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_tx_contwow *contwow,
	 stwuct sk_buff *skb)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	u16 qnum = skb_get_queue_mapping(skb);

	if (WAWN_ON(qnum >= ah->ah_capabiwities.cap_queues.q_tx_num)) {
		ieee80211_fwee_txskb(hw, skb);
		wetuwn;
	}

	ath5k_tx_queue(hw, skb, &ah->txqs[qnum], contwow);
}


static int
ath5k_add_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	int wet;
	stwuct ath5k_vif *avf = (void *)vif->dwv_pwiv;

	mutex_wock(&ah->wock);

	if ((vif->type == NW80211_IFTYPE_AP ||
	     vif->type == NW80211_IFTYPE_ADHOC)
	    && (ah->num_ap_vifs + ah->num_adhoc_vifs) >= ATH_BCBUF) {
		wet = -EWNWNG;
		goto end;
	}

	/* Don't awwow othew intewfaces if one ad-hoc is configuwed.
	 * TODO: Fix the pwobwems with ad-hoc and muwtipwe othew intewfaces.
	 * We wouwd need to opewate the HW in ad-hoc mode to awwow TSF updates
	 * fow the IBSS, but this bweaks with additionaw AP ow STA intewfaces
	 * at the moment. */
	if (ah->num_adhoc_vifs ||
	    (ah->nvifs && vif->type == NW80211_IFTYPE_ADHOC)) {
		ATH5K_EWW(ah, "Onwy one singwe ad-hoc intewface is awwowed.\n");
		wet = -EWNWNG;
		goto end;
	}

	switch (vif->type) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_MESH_POINT:
		avf->opmode = vif->type;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		goto end;
	}

	ah->nvifs++;
	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "add intewface mode %d\n", avf->opmode);

	/* Assign the vap/adhoc to a beacon xmit swot. */
	if ((avf->opmode == NW80211_IFTYPE_AP) ||
	    (avf->opmode == NW80211_IFTYPE_ADHOC) ||
	    (avf->opmode == NW80211_IFTYPE_MESH_POINT)) {
		int swot;

		WAWN_ON(wist_empty(&ah->bcbuf));
		avf->bbuf = wist_fiwst_entwy(&ah->bcbuf, stwuct ath5k_buf,
					     wist);
		wist_dew(&avf->bbuf->wist);

		avf->bswot = 0;
		fow (swot = 0; swot < ATH_BCBUF; swot++) {
			if (!ah->bswot[swot]) {
				avf->bswot = swot;
				bweak;
			}
		}
		BUG_ON(ah->bswot[avf->bswot] != NUWW);
		ah->bswot[avf->bswot] = vif;
		if (avf->opmode == NW80211_IFTYPE_AP)
			ah->num_ap_vifs++;
		ewse if (avf->opmode == NW80211_IFTYPE_ADHOC)
			ah->num_adhoc_vifs++;
		ewse if (avf->opmode == NW80211_IFTYPE_MESH_POINT)
			ah->num_mesh_vifs++;
	}

	/* Any MAC addwess is fine, aww othews awe incwuded thwough the
	 * fiwtew.
	 */
	ath5k_hw_set_wwaddw(ah, vif->addw);

	ath5k_update_bssid_mask_and_opmode(ah, vif);
	wet = 0;
end:
	mutex_unwock(&ah->wock);
	wetuwn wet;
}


static void
ath5k_wemove_intewface(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_vif *vif)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath5k_vif *avf = (void *)vif->dwv_pwiv;
	unsigned int i;

	mutex_wock(&ah->wock);
	ah->nvifs--;

	if (avf->bbuf) {
		ath5k_txbuf_fwee_skb(ah, avf->bbuf);
		wist_add_taiw(&avf->bbuf->wist, &ah->bcbuf);
		fow (i = 0; i < ATH_BCBUF; i++) {
			if (ah->bswot[i] == vif) {
				ah->bswot[i] = NUWW;
				bweak;
			}
		}
		avf->bbuf = NUWW;
	}
	if (avf->opmode == NW80211_IFTYPE_AP)
		ah->num_ap_vifs--;
	ewse if (avf->opmode == NW80211_IFTYPE_ADHOC)
		ah->num_adhoc_vifs--;
	ewse if (avf->opmode == NW80211_IFTYPE_MESH_POINT)
		ah->num_mesh_vifs--;

	ath5k_update_bssid_mask_and_opmode(ah, NUWW);
	mutex_unwock(&ah->wock);
}


/*
 * TODO: Phy disabwe/divewsity etc
 */
static int
ath5k_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ieee80211_conf *conf = &hw->conf;
	int wet = 0;
	int i;

	mutex_wock(&ah->wock);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		wet = ath5k_chan_set(ah, &conf->chandef);
		if (wet < 0)
			goto unwock;
	}

	if ((changed & IEEE80211_CONF_CHANGE_POWEW) &&
	(ah->ah_txpowew.txp_wequested != conf->powew_wevew)) {
		ah->ah_txpowew.txp_wequested = conf->powew_wevew;

		/* Hawf dB steps */
		ath5k_hw_set_txpowew_wimit(ah, (conf->powew_wevew * 2));
	}

	if (changed & IEEE80211_CONF_CHANGE_WETWY_WIMITS) {
		ah->ah_wetwy_wong = conf->wong_fwame_max_tx_count;
		ah->ah_wetwy_showt = conf->showt_fwame_max_tx_count;

		fow (i = 0; i < ah->ah_capabiwities.cap_queues.q_tx_num; i++)
			ath5k_hw_set_tx_wetwy_wimits(ah, i);
	}

	/* TODO:
	 * 1) Move this on config_intewface and handwe each case
	 * sepawatewy eg. when we have onwy one STA vif, use
	 * AW5K_ANTMODE_SINGWE_AP
	 *
	 * 2) Awwow the usew to change antenna mode eg. when onwy
	 * one antenna is pwesent
	 *
	 * 3) Awwow the usew to set defauwt/tx antenna when possibwe
	 *
	 * 4) Defauwt mode shouwd handwe 90% of the cases, togethew
	 * with fixed a/b and singwe AP modes we shouwd be abwe to
	 * handwe 99%. Sectowed modes awe extweme cases and i stiww
	 * haven't found a usage fow them. If we decide to suppowt them,
	 * then we must awwow the usew to set how many tx antennas we
	 * have avaiwabwe
	 */
	ath5k_hw_set_antenna_mode(ah, ah->ah_ant_mode);

unwock:
	mutex_unwock(&ah->wock);
	wetuwn wet;
}


static void
ath5k_bss_info_changed(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_bss_conf *bss_conf, u64 changes)
{
	stwuct ath5k_vif *avf = (void *)vif->dwv_pwiv;
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath_common *common = ath5k_hw_common(ah);

	mutex_wock(&ah->wock);

	if (changes & BSS_CHANGED_BSSID) {
		/* Cache fow watew use duwing wesets */
		memcpy(common->cuwbssid, bss_conf->bssid, ETH_AWEN);
		common->cuwaid = 0;
		ath5k_hw_set_bssid(ah);
	}

	if (changes & BSS_CHANGED_BEACON_INT)
		ah->bintvaw = bss_conf->beacon_int;

	if (changes & BSS_CHANGED_EWP_SWOT) {
		int swot_time;

		ah->ah_showt_swot = bss_conf->use_showt_swot;
		swot_time = ath5k_hw_get_defauwt_swottime(ah) +
			    3 * ah->ah_covewage_cwass;
		ath5k_hw_set_ifs_intewvaws(ah, swot_time);
	}

	if (changes & BSS_CHANGED_ASSOC) {
		avf->assoc = vif->cfg.assoc;
		if (vif->cfg.assoc)
			ah->assoc = vif->cfg.assoc;
		ewse
			ah->assoc = ath5k_any_vif_assoc(ah);

		if (ah->opmode == NW80211_IFTYPE_STATION)
			ath5k_set_beacon_fiwtew(hw, ah->assoc);
		ath5k_hw_set_wedstate(ah, ah->assoc ?
			AW5K_WED_ASSOC : AW5K_WED_INIT);
		if (vif->cfg.assoc) {
			ATH5K_DBG(ah, ATH5K_DEBUG_ANY,
				  "Bss Info ASSOC %d, bssid: %pM\n",
				  vif->cfg.aid, common->cuwbssid);
			common->cuwaid = vif->cfg.aid;
			ath5k_hw_set_bssid(ah);
			/* Once ANI is avaiwabwe you wouwd stawt it hewe */
		}
	}

	if (changes & BSS_CHANGED_BEACON) {
		spin_wock_bh(&ah->bwock);
		ath5k_beacon_update(hw, vif);
		spin_unwock_bh(&ah->bwock);
	}

	if (changes & BSS_CHANGED_BEACON_ENABWED)
		ah->enabwe_beacon = bss_conf->enabwe_beacon;

	if (changes & (BSS_CHANGED_BEACON | BSS_CHANGED_BEACON_ENABWED |
		       BSS_CHANGED_BEACON_INT))
		ath5k_beacon_config(ah);

	mutex_unwock(&ah->wock);
}


static u64
ath5k_pwepawe_muwticast(stwuct ieee80211_hw *hw,
			stwuct netdev_hw_addw_wist *mc_wist)
{
	u32 mfiwt[2], vaw;
	u8 pos;
	stwuct netdev_hw_addw *ha;

	mfiwt[0] = 0;
	mfiwt[1] = 0;

	netdev_hw_addw_wist_fow_each(ha, mc_wist) {
		/* cawcuwate XOW of eight 6-bit vawues */
		vaw = get_unawigned_we32(ha->addw + 0);
		pos = (vaw >> 18) ^ (vaw >> 12) ^ (vaw >> 6) ^ vaw;
		vaw = get_unawigned_we32(ha->addw + 3);
		pos ^= (vaw >> 18) ^ (vaw >> 12) ^ (vaw >> 6) ^ vaw;
		pos &= 0x3f;
		mfiwt[pos / 32] |= (1 << (pos % 32));
		/* XXX: we might be abwe to just do this instead,
		* but not suwe, needs testing, if we do use this we'd
		* need to infowm bewow not to weset the mcast */
		/* ath5k_hw_set_mcast_fiwtewindex(ah,
		 *      ha->addw[5]); */
	}

	wetuwn ((u64)(mfiwt[1]) << 32) | mfiwt[0];
}


/*
 * o awways accept unicast, bwoadcast, and muwticast twaffic
 * o muwticast twaffic fow aww BSSIDs wiww be enabwed if mac80211
 *   says it shouwd be
 * o maintain cuwwent state of phy ofdm ow phy cck ewwow weception.
 *   If the hawdwawe detects any of these type of ewwows then
 *   ath5k_hw_get_wx_fiwtew() wiww pass to us the wespective
 *   hawdwawe fiwtews to be abwe to weceive these type of fwames.
 * o pwobe wequest fwames awe accepted onwy when opewating in
 *   hostap, adhoc, ow monitow modes
 * o enabwe pwomiscuous mode accowding to the intewface state
 * o accept beacons:
 *   - when opewating in adhoc mode so the 802.11 wayew cweates
 *     node tabwe entwies fow peews,
 *   - when opewating in station mode fow cowwecting wssi data when
 *     the station is othewwise quiet, ow
 *   - when scanning
 */
static void
ath5k_configuwe_fiwtew(stwuct ieee80211_hw *hw, unsigned int changed_fwags,
		       unsigned int *new_fwags, u64 muwticast)
{
#define SUPPOWTED_FIF_FWAGS \
	(FIF_AWWMUWTI | FIF_FCSFAIW | \
	FIF_PWCPFAIW | FIF_CONTWOW | FIF_OTHEW_BSS | \
	FIF_BCN_PWBWESP_PWOMISC)

	stwuct ath5k_hw *ah = hw->pwiv;
	u32 mfiwt[2], wfiwt;
	stwuct ath5k_vif_itew_data itew_data; /* to count STA intewfaces */

	mutex_wock(&ah->wock);

	mfiwt[0] = muwticast;
	mfiwt[1] = muwticast >> 32;

	/* Onwy deaw with suppowted fwags */
	*new_fwags &= SUPPOWTED_FIF_FWAGS;

	/* If HW detects any phy ow wadaw ewwows, weave those fiwtews on.
	 * Awso, awways enabwe Unicast, Bwoadcasts and Muwticast
	 * XXX: move unicast, bssid bwoadcasts and muwticast to mac80211 */
	wfiwt = (ath5k_hw_get_wx_fiwtew(ah) & (AW5K_WX_FIWTEW_PHYEWW)) |
		(AW5K_WX_FIWTEW_UCAST | AW5K_WX_FIWTEW_BCAST |
		AW5K_WX_FIWTEW_MCAST);

	/* Note, AW5K_WX_FIWTEW_MCAST is awweady enabwed */
	if (*new_fwags & FIF_AWWMUWTI) {
		mfiwt[0] =  ~0;
		mfiwt[1] =  ~0;
	}

	/* This is the best we can do */
	if (*new_fwags & (FIF_FCSFAIW | FIF_PWCPFAIW))
		wfiwt |= AW5K_WX_FIWTEW_PHYEWW;

	/* FIF_BCN_PWBWESP_PWOMISC weawwy means to enabwe beacons
	* and pwobes fow any BSSID */
	if ((*new_fwags & FIF_BCN_PWBWESP_PWOMISC) || (ah->nvifs > 1))
		wfiwt |= AW5K_WX_FIWTEW_BEACON;

	/* FIF_CONTWOW doc says we shouwd onwy pass on contwow fwames fow this
	 * station. This needs testing. I bewieve wight now this
	 * enabwes *aww* contwow fwames, which is OK.. but
	 * we shouwd see if we can impwove on gwanuwawity */
	if (*new_fwags & FIF_CONTWOW)
		wfiwt |= AW5K_WX_FIWTEW_CONTWOW;

	/* Additionaw settings pew mode -- this is pew ath5k */

	/* XXX move these to mac80211, and add a beacon IFF fwag to mac80211 */

	switch (ah->opmode) {
	case NW80211_IFTYPE_MESH_POINT:
		wfiwt |= AW5K_WX_FIWTEW_CONTWOW |
			 AW5K_WX_FIWTEW_BEACON |
			 AW5K_WX_FIWTEW_PWOBEWEQ |
			 AW5K_WX_FIWTEW_PWOM;
		bweak;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_ADHOC:
		wfiwt |= AW5K_WX_FIWTEW_PWOBEWEQ |
			 AW5K_WX_FIWTEW_BEACON;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (ah->assoc)
			wfiwt |= AW5K_WX_FIWTEW_BEACON;
		bweak;
	defauwt:
		bweak;
	}

	itew_data.hw_macaddw = NUWW;
	itew_data.n_stas = 0;
	itew_data.need_set_hw_addw = fawse;
	ieee80211_itewate_active_intewfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
		ath5k_vif_itew, &itew_data);

	/* Set up WX Fiwtew */
	if (itew_data.n_stas > 1) {
		/* If you have muwtipwe STA intewfaces connected to
		 * diffewent APs, AWPs awe not weceived (most of the time?)
		 * Enabwing PWOMISC appeaws to fix that pwobwem.
		 */
		wfiwt |= AW5K_WX_FIWTEW_PWOM;
	}

	/* Set fiwtews */
	ath5k_hw_set_wx_fiwtew(ah, wfiwt);

	/* Set muwticast bits */
	ath5k_hw_set_mcast_fiwtew(ah, mfiwt[0], mfiwt[1]);
	/* Set the cached hw fiwtew fwags, this wiww watew actuawwy
	 * be set in HW */
	ah->fiwtew_fwags = wfiwt;
	/* Stowe cuwwent FIF fiwtew fwags */
	ah->fif_fiwtew_fwags = *new_fwags;

	mutex_unwock(&ah->wock);
}


static int
ath5k_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
	      stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
	      stwuct ieee80211_key_conf *key)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath_common *common = ath5k_hw_common(ah);
	int wet = 0;

	if (ath5k_modpawam_nohwcwypt)
		wetuwn -EOPNOTSUPP;

	if (key->fwags & IEEE80211_KEY_FWAG_WX_MGMT)
		wetuwn -EOPNOTSUPP;

	if (vif->type == NW80211_IFTYPE_ADHOC &&
	    (key->ciphew == WWAN_CIPHEW_SUITE_TKIP ||
	     key->ciphew == WWAN_CIPHEW_SUITE_CCMP) &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
		/* don't pwogwam gwoup keys when using IBSS_WSN */
		wetuwn -EOPNOTSUPP;
	}

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
	case WWAN_CIPHEW_SUITE_TKIP:
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		if (common->cwypt_caps & ATH_CWYPT_CAP_CIPHEW_AESCCM)
			bweak;
		wetuwn -EOPNOTSUPP;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&ah->wock);

	switch (cmd) {
	case SET_KEY:
		wet = ath_key_config(common, vif, sta, key);
		if (wet >= 0) {
			key->hw_key_idx = wet;
			/* push IV and Michaew MIC genewation to stack */
			key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
			if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP)
				key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
			if (key->ciphew == WWAN_CIPHEW_SUITE_CCMP)
				key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
			wet = 0;
		}
		bweak;
	case DISABWE_KEY:
		ath_key_dewete(common, key->hw_key_idx);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&ah->wock);
	wetuwn wet;
}


static void
ath5k_sw_scan_stawt(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_vif *vif,
		    const u8 *mac_addw)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	if (!ah->assoc)
		ath5k_hw_set_wedstate(ah, AW5K_WED_SCAN);
}


static void
ath5k_sw_scan_compwete(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	ath5k_hw_set_wedstate(ah, ah->assoc ?
		AW5K_WED_ASSOC : AW5K_WED_INIT);
}


static int
ath5k_get_stats(stwuct ieee80211_hw *hw,
		stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	/* Fowce update */
	ath5k_hw_update_mib_countews(ah);

	stats->dot11ACKFaiwuweCount = ah->stats.ack_faiw;
	stats->dot11WTSFaiwuweCount = ah->stats.wts_faiw;
	stats->dot11WTSSuccessCount = ah->stats.wts_ok;
	stats->dot11FCSEwwowCount = ah->stats.fcs_ewwow;

	wetuwn 0;
}


static int
ath5k_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	      unsigned int wink_id, u16 queue,
	      const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath5k_txq_info qi;
	int wet = 0;

	if (queue >= ah->ah_capabiwities.cap_queues.q_tx_num)
		wetuwn 0;

	mutex_wock(&ah->wock);

	ath5k_hw_get_tx_queuepwops(ah, queue, &qi);

	qi.tqi_aifs = pawams->aifs;
	qi.tqi_cw_min = pawams->cw_min;
	qi.tqi_cw_max = pawams->cw_max;
	qi.tqi_buwst_time = pawams->txop * 32;

	ATH5K_DBG(ah, ATH5K_DEBUG_ANY,
		  "Configuwe tx [queue %d],  "
		  "aifs: %d, cw_min: %d, cw_max: %d, txop: %d\n",
		  queue, pawams->aifs, pawams->cw_min,
		  pawams->cw_max, pawams->txop);

	if (ath5k_hw_set_tx_queuepwops(ah, queue, &qi)) {
		ATH5K_EWW(ah,
			  "Unabwe to update hawdwawe queue %u!\n", queue);
		wet = -EIO;
	} ewse
		ath5k_hw_weset_tx_queue(ah, queue);

	mutex_unwock(&ah->wock);

	wetuwn wet;
}


static u64
ath5k_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	wetuwn ath5k_hw_get_tsf64(ah);
}


static void
ath5k_set_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif, u64 tsf)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	ath5k_hw_set_tsf64(ah, tsf);
}


static void
ath5k_weset_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	/*
	 * in IBSS mode we need to update the beacon timews too.
	 * this wiww awso weset the TSF if we caww it with 0
	 */
	if (ah->opmode == NW80211_IFTYPE_ADHOC)
		ath5k_beacon_update_timews(ah, 0);
	ewse
		ath5k_hw_weset_tsf(ah);
}


static int
ath5k_get_suwvey(stwuct ieee80211_hw *hw, int idx, stwuct suwvey_info *suwvey)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ieee80211_conf *conf = &hw->conf;
	stwuct ath_common *common = ath5k_hw_common(ah);
	stwuct ath_cycwe_countews *cc = &common->cc_suwvey;
	unsigned int div = common->cwockwate * 1000;

	if (idx != 0)
		wetuwn -ENOENT;

	spin_wock_bh(&common->cc_wock);
	ath_hw_cycwe_countews_update(common);
	if (cc->cycwes > 0) {
		ah->suwvey.time += cc->cycwes / div;
		ah->suwvey.time_busy += cc->wx_busy / div;
		ah->suwvey.time_wx += cc->wx_fwame / div;
		ah->suwvey.time_tx += cc->tx_fwame / div;
	}
	memset(cc, 0, sizeof(*cc));
	spin_unwock_bh(&common->cc_wock);

	memcpy(suwvey, &ah->suwvey, sizeof(*suwvey));

	suwvey->channew = conf->chandef.chan;
	suwvey->noise = ah->ah_noise_fwoow;
	suwvey->fiwwed = SUWVEY_INFO_NOISE_DBM |
			SUWVEY_INFO_IN_USE |
			SUWVEY_INFO_TIME |
			SUWVEY_INFO_TIME_BUSY |
			SUWVEY_INFO_TIME_WX |
			SUWVEY_INFO_TIME_TX;

	wetuwn 0;
}


/**
 * ath5k_set_covewage_cwass - Set IEEE 802.11 covewage cwass
 *
 * @hw: stwuct ieee80211_hw pointew
 * @covewage_cwass: IEEE 802.11 covewage cwass numbew
 *
 * Mac80211 cawwback. Sets swot time, ACK timeout and CTS timeout fow given
 * covewage cwass. The vawues awe pewsistent, they awe westowed aftew device
 * weset.
 */
static void
ath5k_set_covewage_cwass(stwuct ieee80211_hw *hw, s16 covewage_cwass)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	mutex_wock(&ah->wock);
	ath5k_hw_set_covewage_cwass(ah, covewage_cwass);
	mutex_unwock(&ah->wock);
}


static int
ath5k_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	if (tx_ant == 1 && wx_ant == 1)
		ath5k_hw_set_antenna_mode(ah, AW5K_ANTMODE_FIXED_A);
	ewse if (tx_ant == 2 && wx_ant == 2)
		ath5k_hw_set_antenna_mode(ah, AW5K_ANTMODE_FIXED_B);
	ewse if ((tx_ant & 3) == 3 && (wx_ant & 3) == 3)
		ath5k_hw_set_antenna_mode(ah, AW5K_ANTMODE_DEFAUWT);
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}


static int
ath5k_get_antenna(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	switch (ah->ah_ant_mode) {
	case AW5K_ANTMODE_FIXED_A:
		*tx_ant = 1; *wx_ant = 1; bweak;
	case AW5K_ANTMODE_FIXED_B:
		*tx_ant = 2; *wx_ant = 2; bweak;
	case AW5K_ANTMODE_DEFAUWT:
		*tx_ant = 3; *wx_ant = 3; bweak;
	}
	wetuwn 0;
}


static void ath5k_get_wingpawam(stwuct ieee80211_hw *hw,
				u32 *tx, u32 *tx_max, u32 *wx, u32 *wx_max)
{
	stwuct ath5k_hw *ah = hw->pwiv;

	*tx = ah->txqs[AW5K_TX_QUEUE_ID_DATA_MIN].txq_max;

	*tx_max = ATH5K_TXQ_WEN_MAX;
	*wx = *wx_max = ATH_WXBUF;
}


static int ath5k_set_wingpawam(stwuct ieee80211_hw *hw, u32 tx, u32 wx)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	u16 qnum;

	/* onwy suppowt setting tx wing size fow now */
	if (wx != ATH_WXBUF)
		wetuwn -EINVAW;

	/* westwict tx wing size min/max */
	if (!tx || tx > ATH5K_TXQ_WEN_MAX)
		wetuwn -EINVAW;

	fow (qnum = 0; qnum < AWWAY_SIZE(ah->txqs); qnum++) {
		if (!ah->txqs[qnum].setup)
			continue;
		if (ah->txqs[qnum].qnum < AW5K_TX_QUEUE_ID_DATA_MIN ||
		    ah->txqs[qnum].qnum > AW5K_TX_QUEUE_ID_DATA_MAX)
			continue;

		ah->txqs[qnum].txq_max = tx;
		if (ah->txqs[qnum].txq_wen >= ah->txqs[qnum].txq_max)
			ieee80211_stop_queue(hw, ah->txqs[qnum].qnum);
	}

	wetuwn 0;
}


const stwuct ieee80211_ops ath5k_hw_ops = {
	.tx			= ath5k_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.stawt			= ath5k_stawt,
	.stop			= ath5k_stop,
	.add_intewface		= ath5k_add_intewface,
	/* .change_intewface	= not impwemented */
	.wemove_intewface	= ath5k_wemove_intewface,
	.config			= ath5k_config,
	.bss_info_changed	= ath5k_bss_info_changed,
	.pwepawe_muwticast	= ath5k_pwepawe_muwticast,
	.configuwe_fiwtew	= ath5k_configuwe_fiwtew,
	/* .set_tim		= not impwemented */
	.set_key		= ath5k_set_key,
	/* .update_tkip_key	= not impwemented */
	/* .hw_scan		= not impwemented */
	.sw_scan_stawt		= ath5k_sw_scan_stawt,
	.sw_scan_compwete	= ath5k_sw_scan_compwete,
	.get_stats		= ath5k_get_stats,
	/* .set_fwag_thweshowd	= not impwemented */
	/* .set_wts_thweshowd	= not impwemented */
	/* .sta_add		= not impwemented */
	/* .sta_wemove		= not impwemented */
	/* .sta_notify		= not impwemented */
	.conf_tx		= ath5k_conf_tx,
	.get_tsf		= ath5k_get_tsf,
	.set_tsf		= ath5k_set_tsf,
	.weset_tsf		= ath5k_weset_tsf,
	/* .tx_wast_beacon	= not impwemented */
	/* .ampdu_action	= not needed */
	.get_suwvey		= ath5k_get_suwvey,
	.set_covewage_cwass	= ath5k_set_covewage_cwass,
	/* .wfkiww_poww		= not impwemented */
	/* .fwush		= not impwemented */
	/* .channew_switch	= not impwemented */
	/* .napi_poww		= not impwemented */
	.set_antenna		= ath5k_set_antenna,
	.get_antenna		= ath5k_get_antenna,
	.set_wingpawam		= ath5k_set_wingpawam,
	.get_wingpawam		= ath5k_get_wingpawam,
};
