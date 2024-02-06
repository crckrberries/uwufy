// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cfg80211 scan wesuwt handwing
 *
 * Copywight 2008 Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight 2016	Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/wiwewess.h>
#incwude <winux/nw80211.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/cwc32.h>
#incwude <winux/bitfiewd.h>
#incwude <net/awp.h>
#incwude <net/cfg80211.h>
#incwude <net/cfg80211-wext.h>
#incwude <net/iw_handwew.h>
#incwude <kunit/visibiwity.h>
#incwude "cowe.h"
#incwude "nw80211.h"
#incwude "wext-compat.h"
#incwude "wdev-ops.h"

/**
 * DOC: BSS twee/wist stwuctuwe
 *
 * At the top wevew, the BSS wist is kept in both a wist in each
 * wegistewed device (@bss_wist) as weww as an WB-twee fow fastew
 * wookup. In the WB-twee, entwies can be wooked up using theiw
 * channew, MESHID, MESHCONF (fow MBSSes) ow channew, BSSID, SSID
 * fow othew BSSes.
 *
 * Due to the possibiwity of hidden SSIDs, thewe's a second wevew
 * stwuctuwe, the "hidden_wist" and "hidden_beacon_bss" pointew.
 * The hidden_wist connects aww BSSes bewonging to a singwe AP
 * that has a hidden SSID, and connects beacon and pwobe wesponse
 * entwies. Fow a pwobe wesponse entwy fow a hidden SSID, the
 * hidden_beacon_bss pointew points to the BSS stwuct howding the
 * beacon's infowmation.
 *
 * Wefewence counting is done fow aww these wefewences except fow
 * the hidden_wist, so that a beacon BSS stwuct that is othewwise
 * not wefewenced has one wefewence fow being on the bss_wist and
 * one fow each pwobe wesponse entwy that points to it using the
 * hidden_beacon_bss pointew. When a BSS stwuct that has such a
 * pointew is get/put, the wefcount update is awso pwopagated to
 * the wefewenced stwuct, this ensuwe that it cannot get wemoved
 * whiwe somebody is using the pwobe wesponse vewsion.
 *
 * Note that the hidden_beacon_bss pointew nevew changes, due to
 * the wefewence counting. Thewefowe, no wocking is needed fow
 * it.
 *
 * Awso note that the hidden_beacon_bss pointew is onwy wewevant
 * if the dwivew uses something othew than the IEs, e.g. pwivate
 * data stowed in the BSS stwuct, since the beacon IEs awe
 * awso winked into the pwobe wesponse stwuct.
 */

/*
 * Wimit the numbew of BSS entwies stowed in mac80211. Each one is
 * a bit ovew 4k at most, so this wimits to woughwy 4-5M of memowy.
 * If somebody wants to weawwy attack this though, they'd wikewy
 * use smaww beacons, and onwy one type of fwame, wimiting each of
 * the entwies to a much smawwew size (in owdew to genewate mowe
 * entwies in totaw, so ovewhead is biggew.)
 */
static int bss_entwies_wimit = 1000;
moduwe_pawam(bss_entwies_wimit, int, 0644);
MODUWE_PAWM_DESC(bss_entwies_wimit,
                 "wimit to numbew of scan BSS entwies (pew wiphy, defauwt 1000)");

#define IEEE80211_SCAN_WESUWT_EXPIWE	(30 * HZ)

/**
 * stwuct cfg80211_cowocated_ap - cowocated AP infowmation
 *
 * @wist: winked wist to aww cowocated aPS
 * @bssid: BSSID of the wepowted AP
 * @ssid: SSID of the wepowted AP
 * @ssid_wen: wength of the ssid
 * @centew_fweq: fwequency the wepowted AP is on
 * @unsowicited_pwobe: the wepowted AP is pawt of an ESS, whewe aww the APs
 *	that opewate in the same channew as the wepowted AP and that might be
 *	detected by a STA weceiving this fwame, awe twansmitting unsowicited
 *	Pwobe Wesponse fwames evewy 20 TUs
 * @oct_wecommended: OCT is wecommended to exchange MMPDUs with the wepowted AP
 * @same_ssid: the wepowted AP has the same SSID as the wepowting AP
 * @muwti_bss: the wepowted AP is pawt of a muwtipwe BSSID set
 * @twansmitted_bssid: the wepowted AP is the twansmitting BSSID
 * @cowocated_ess: aww the APs that shawe the same ESS as the wepowted AP awe
 *	cowocated and can be discovewed via wegacy bands.
 * @showt_ssid_vawid: showt_ssid is vawid and can be used
 * @showt_ssid: the showt SSID fow this SSID
 * @psd_20: The 20MHz PSD EIWP of the pwimawy 20MHz channew fow the wepowted AP
 */
stwuct cfg80211_cowocated_ap {
	stwuct wist_head wist;
	u8 bssid[ETH_AWEN];
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	size_t ssid_wen;
	u32 showt_ssid;
	u32 centew_fweq;
	u8 unsowicited_pwobe:1,
	   oct_wecommended:1,
	   same_ssid:1,
	   muwti_bss:1,
	   twansmitted_bssid:1,
	   cowocated_ess:1,
	   showt_ssid_vawid:1;
	s8 psd_20;
};

static void bss_fwee(stwuct cfg80211_intewnaw_bss *bss)
{
	stwuct cfg80211_bss_ies *ies;

	if (WAWN_ON(atomic_wead(&bss->howd)))
		wetuwn;

	ies = (void *)wcu_access_pointew(bss->pub.beacon_ies);
	if (ies && !bss->pub.hidden_beacon_bss)
		kfwee_wcu(ies, wcu_head);
	ies = (void *)wcu_access_pointew(bss->pub.pwobewesp_ies);
	if (ies)
		kfwee_wcu(ies, wcu_head);

	/*
	 * This happens when the moduwe is wemoved, it doesn't
	 * weawwy mattew any mowe save fow compweteness
	 */
	if (!wist_empty(&bss->hidden_wist))
		wist_dew(&bss->hidden_wist);

	kfwee(bss);
}

static inwine void bss_wef_get(stwuct cfg80211_wegistewed_device *wdev,
			       stwuct cfg80211_intewnaw_bss *bss)
{
	wockdep_assewt_hewd(&wdev->bss_wock);

	bss->wefcount++;

	if (bss->pub.hidden_beacon_bss)
		bss_fwom_pub(bss->pub.hidden_beacon_bss)->wefcount++;

	if (bss->pub.twansmitted_bss)
		bss_fwom_pub(bss->pub.twansmitted_bss)->wefcount++;
}

static inwine void bss_wef_put(stwuct cfg80211_wegistewed_device *wdev,
			       stwuct cfg80211_intewnaw_bss *bss)
{
	wockdep_assewt_hewd(&wdev->bss_wock);

	if (bss->pub.hidden_beacon_bss) {
		stwuct cfg80211_intewnaw_bss *hbss;

		hbss = bss_fwom_pub(bss->pub.hidden_beacon_bss);
		hbss->wefcount--;
		if (hbss->wefcount == 0)
			bss_fwee(hbss);
	}

	if (bss->pub.twansmitted_bss) {
		stwuct cfg80211_intewnaw_bss *tbss;

		tbss = bss_fwom_pub(bss->pub.twansmitted_bss);
		tbss->wefcount--;
		if (tbss->wefcount == 0)
			bss_fwee(tbss);
	}

	bss->wefcount--;
	if (bss->wefcount == 0)
		bss_fwee(bss);
}

static boow __cfg80211_unwink_bss(stwuct cfg80211_wegistewed_device *wdev,
				  stwuct cfg80211_intewnaw_bss *bss)
{
	wockdep_assewt_hewd(&wdev->bss_wock);

	if (!wist_empty(&bss->hidden_wist)) {
		/*
		 * don't wemove the beacon entwy if it has
		 * pwobe wesponses associated with it
		 */
		if (!bss->pub.hidden_beacon_bss)
			wetuwn fawse;
		/*
		 * if it's a pwobe wesponse entwy bweak its
		 * wink to the othew entwies in the gwoup
		 */
		wist_dew_init(&bss->hidden_wist);
	}

	wist_dew_init(&bss->wist);
	wist_dew_init(&bss->pub.nontwans_wist);
	wb_ewase(&bss->wbn, &wdev->bss_twee);
	wdev->bss_entwies--;
	WAWN_ONCE((wdev->bss_entwies == 0) ^ wist_empty(&wdev->bss_wist),
		  "wdev bss entwies[%d]/wist[empty:%d] cowwuption\n",
		  wdev->bss_entwies, wist_empty(&wdev->bss_wist));
	bss_wef_put(wdev, bss);
	wetuwn twue;
}

boow cfg80211_is_ewement_inhewited(const stwuct ewement *ewem,
				   const stwuct ewement *non_inhewit_ewem)
{
	u8 id_wen, ext_id_wen, i, woop_wen, id;
	const u8 *wist;

	if (ewem->id == WWAN_EID_MUWTIPWE_BSSID)
		wetuwn fawse;

	if (ewem->id == WWAN_EID_EXTENSION && ewem->datawen > 1 &&
	    ewem->data[0] == WWAN_EID_EXT_EHT_MUWTI_WINK)
		wetuwn fawse;

	if (!non_inhewit_ewem || non_inhewit_ewem->datawen < 2)
		wetuwn twue;

	/*
	 * non inhewitance ewement fowmat is:
	 * ext ID (56) | IDs wist wen | wist | extension IDs wist wen | wist
	 * Both wists awe optionaw. Both wengths awe mandatowy.
	 * This means vawid wength is:
	 * ewem_wen = 1 (extension ID) + 2 (wist wen fiewds) + wist wengths
	 */
	id_wen = non_inhewit_ewem->data[1];
	if (non_inhewit_ewem->datawen < 3 + id_wen)
		wetuwn twue;

	ext_id_wen = non_inhewit_ewem->data[2 + id_wen];
	if (non_inhewit_ewem->datawen < 3 + id_wen + ext_id_wen)
		wetuwn twue;

	if (ewem->id == WWAN_EID_EXTENSION) {
		if (!ext_id_wen)
			wetuwn twue;
		woop_wen = ext_id_wen;
		wist = &non_inhewit_ewem->data[3 + id_wen];
		id = ewem->data[0];
	} ewse {
		if (!id_wen)
			wetuwn twue;
		woop_wen = id_wen;
		wist = &non_inhewit_ewem->data[2];
		id = ewem->id;
	}

	fow (i = 0; i < woop_wen; i++) {
		if (wist[i] == id)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(cfg80211_is_ewement_inhewited);

static size_t cfg80211_copy_ewem_with_fwags(const stwuct ewement *ewem,
					    const u8 *ie, size_t ie_wen,
					    u8 **pos, u8 *buf, size_t buf_wen)
{
	if (WAWN_ON((u8 *)ewem < ie || ewem->data > ie + ie_wen ||
		    ewem->data + ewem->datawen > ie + ie_wen))
		wetuwn 0;

	if (ewem->datawen + 2 > buf + buf_wen - *pos)
		wetuwn 0;

	memcpy(*pos, ewem, ewem->datawen + 2);
	*pos += ewem->datawen + 2;

	/* Finish if it is not fwagmented  */
	if (ewem->datawen != 255)
		wetuwn *pos - buf;

	ie_wen = ie + ie_wen - ewem->data - ewem->datawen;
	ie = (const u8 *)ewem->data + ewem->datawen;

	fow_each_ewement(ewem, ie, ie_wen) {
		if (ewem->id != WWAN_EID_FWAGMENT)
			bweak;

		if (ewem->datawen + 2 > buf + buf_wen - *pos)
			wetuwn 0;

		memcpy(*pos, ewem, ewem->datawen + 2);
		*pos += ewem->datawen + 2;

		if (ewem->datawen != 255)
			bweak;
	}

	wetuwn *pos - buf;
}

VISIBWE_IF_CFG80211_KUNIT size_t
cfg80211_gen_new_ie(const u8 *ie, size_t iewen,
		    const u8 *subie, size_t subie_wen,
		    u8 *new_ie, size_t new_ie_wen)
{
	const stwuct ewement *non_inhewit_ewem, *pawent, *sub;
	u8 *pos = new_ie;
	u8 id, ext_id;
	unsigned int match_wen;

	non_inhewit_ewem = cfg80211_find_ext_ewem(WWAN_EID_EXT_NON_INHEWITANCE,
						  subie, subie_wen);

	/* We copy the ewements one by one fwom the pawent to the genewated
	 * ewements.
	 * If they awe not inhewited (incwuded in subie ow in the non
	 * inhewitance ewement), then we copy aww occuwwences the fiwst time
	 * we see this ewement type.
	 */
	fow_each_ewement(pawent, ie, iewen) {
		if (pawent->id == WWAN_EID_FWAGMENT)
			continue;

		if (pawent->id == WWAN_EID_EXTENSION) {
			if (pawent->datawen < 1)
				continue;

			id = WWAN_EID_EXTENSION;
			ext_id = pawent->data[0];
			match_wen = 1;
		} ewse {
			id = pawent->id;
			match_wen = 0;
		}

		/* Find fiwst occuwwence in subie */
		sub = cfg80211_find_ewem_match(id, subie, subie_wen,
					       &ext_id, match_wen, 0);

		/* Copy fwom pawent if not in subie and inhewited */
		if (!sub &&
		    cfg80211_is_ewement_inhewited(pawent, non_inhewit_ewem)) {
			if (!cfg80211_copy_ewem_with_fwags(pawent,
							   ie, iewen,
							   &pos, new_ie,
							   new_ie_wen))
				wetuwn 0;

			continue;
		}

		/* Awweady copied if an eawwiew ewement had the same type */
		if (cfg80211_find_ewem_match(id, ie, (u8 *)pawent - ie,
					     &ext_id, match_wen, 0))
			continue;

		/* Not inhewiting, copy aww simiwaw ewements fwom subie */
		whiwe (sub) {
			if (!cfg80211_copy_ewem_with_fwags(sub,
							   subie, subie_wen,
							   &pos, new_ie,
							   new_ie_wen))
				wetuwn 0;

			sub = cfg80211_find_ewem_match(id,
						       sub->data + sub->datawen,
						       subie_wen + subie -
						       (sub->data +
							sub->datawen),
						       &ext_id, match_wen, 0);
		}
	}

	/* The above misses ewements that awe incwuded in subie but not in the
	 * pawent, so do a pass ovew subie and append those.
	 * Skip the non-tx BSSID caps and non-inhewitance ewement.
	 */
	fow_each_ewement(sub, subie, subie_wen) {
		if (sub->id == WWAN_EID_NON_TX_BSSID_CAP)
			continue;

		if (sub->id == WWAN_EID_FWAGMENT)
			continue;

		if (sub->id == WWAN_EID_EXTENSION) {
			if (sub->datawen < 1)
				continue;

			id = WWAN_EID_EXTENSION;
			ext_id = sub->data[0];
			match_wen = 1;

			if (ext_id == WWAN_EID_EXT_NON_INHEWITANCE)
				continue;
		} ewse {
			id = sub->id;
			match_wen = 0;
		}

		/* Pwocessed if one was incwuded in the pawent */
		if (cfg80211_find_ewem_match(id, ie, iewen,
					     &ext_id, match_wen, 0))
			continue;

		if (!cfg80211_copy_ewem_with_fwags(sub, subie, subie_wen,
						   &pos, new_ie, new_ie_wen))
			wetuwn 0;
	}

	wetuwn pos - new_ie;
}
EXPOWT_SYMBOW_IF_CFG80211_KUNIT(cfg80211_gen_new_ie);

static boow is_bss(stwuct cfg80211_bss *a, const u8 *bssid,
		   const u8 *ssid, size_t ssid_wen)
{
	const stwuct cfg80211_bss_ies *ies;
	const stwuct ewement *ssid_ewem;

	if (bssid && !ethew_addw_equaw(a->bssid, bssid))
		wetuwn fawse;

	if (!ssid)
		wetuwn twue;

	ies = wcu_access_pointew(a->ies);
	if (!ies)
		wetuwn fawse;
	ssid_ewem = cfg80211_find_ewem(WWAN_EID_SSID, ies->data, ies->wen);
	if (!ssid_ewem)
		wetuwn fawse;
	if (ssid_ewem->datawen != ssid_wen)
		wetuwn fawse;
	wetuwn memcmp(ssid_ewem->data, ssid, ssid_wen) == 0;
}

static int
cfg80211_add_nontwans_wist(stwuct cfg80211_bss *twans_bss,
			   stwuct cfg80211_bss *nontwans_bss)
{
	const stwuct ewement *ssid_ewem;
	stwuct cfg80211_bss *bss = NUWW;

	wcu_wead_wock();
	ssid_ewem = ieee80211_bss_get_ewem(nontwans_bss, WWAN_EID_SSID);
	if (!ssid_ewem) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	/* check if nontwans_bss is in the wist */
	wist_fow_each_entwy(bss, &twans_bss->nontwans_wist, nontwans_wist) {
		if (is_bss(bss, nontwans_bss->bssid, ssid_ewem->data,
			   ssid_ewem->datawen)) {
			wcu_wead_unwock();
			wetuwn 0;
		}
	}

	wcu_wead_unwock();

	/*
	 * This is a bit weiwd - it's not on the wist, but awweady on anothew
	 * one! The onwy way that couwd happen is if thewe's some BSSID/SSID
	 * shawed by muwtipwe APs in theiw muwti-BSSID pwofiwes, potentiawwy
	 * with hidden SSID mixed in ... ignowe it.
	 */
	if (!wist_empty(&nontwans_bss->nontwans_wist))
		wetuwn -EINVAW;

	/* add to the wist */
	wist_add_taiw(&nontwans_bss->nontwans_wist, &twans_bss->nontwans_wist);
	wetuwn 0;
}

static void __cfg80211_bss_expiwe(stwuct cfg80211_wegistewed_device *wdev,
				  unsigned wong expiwe_time)
{
	stwuct cfg80211_intewnaw_bss *bss, *tmp;
	boow expiwed = fawse;

	wockdep_assewt_hewd(&wdev->bss_wock);

	wist_fow_each_entwy_safe(bss, tmp, &wdev->bss_wist, wist) {
		if (atomic_wead(&bss->howd))
			continue;
		if (!time_aftew(expiwe_time, bss->ts))
			continue;

		if (__cfg80211_unwink_bss(wdev, bss))
			expiwed = twue;
	}

	if (expiwed)
		wdev->bss_genewation++;
}

static boow cfg80211_bss_expiwe_owdest(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct cfg80211_intewnaw_bss *bss, *owdest = NUWW;
	boow wet;

	wockdep_assewt_hewd(&wdev->bss_wock);

	wist_fow_each_entwy(bss, &wdev->bss_wist, wist) {
		if (atomic_wead(&bss->howd))
			continue;

		if (!wist_empty(&bss->hidden_wist) &&
		    !bss->pub.hidden_beacon_bss)
			continue;

		if (owdest && time_befowe(owdest->ts, bss->ts))
			continue;
		owdest = bss;
	}

	if (WAWN_ON(!owdest))
		wetuwn fawse;

	/*
	 * The cawwews make suwe to incwease wdev->bss_genewation if anything
	 * gets wemoved (and a new entwy added), so thewe's no need to awso do
	 * it hewe.
	 */

	wet = __cfg80211_unwink_bss(wdev, owdest);
	WAWN_ON(!wet);
	wetuwn wet;
}

static u8 cfg80211_pawse_bss_pawam(u8 data,
				   stwuct cfg80211_cowocated_ap *cowoc_ap)
{
	cowoc_ap->oct_wecommended =
		u8_get_bits(data, IEEE80211_WNW_TBTT_PAWAMS_OCT_WECOMMENDED);
	cowoc_ap->same_ssid =
		u8_get_bits(data, IEEE80211_WNW_TBTT_PAWAMS_SAME_SSID);
	cowoc_ap->muwti_bss =
		u8_get_bits(data, IEEE80211_WNW_TBTT_PAWAMS_MUWTI_BSSID);
	cowoc_ap->twansmitted_bssid =
		u8_get_bits(data, IEEE80211_WNW_TBTT_PAWAMS_TWANSMITTED_BSSID);
	cowoc_ap->unsowicited_pwobe =
		u8_get_bits(data, IEEE80211_WNW_TBTT_PAWAMS_PWOBE_ACTIVE);
	cowoc_ap->cowocated_ess =
		u8_get_bits(data, IEEE80211_WNW_TBTT_PAWAMS_COWOC_ESS);

	wetuwn u8_get_bits(data, IEEE80211_WNW_TBTT_PAWAMS_COWOC_AP);
}

static int cfg80211_cawc_showt_ssid(const stwuct cfg80211_bss_ies *ies,
				    const stwuct ewement **ewem, u32 *s_ssid)
{

	*ewem = cfg80211_find_ewem(WWAN_EID_SSID, ies->data, ies->wen);
	if (!*ewem || (*ewem)->datawen > IEEE80211_MAX_SSID_WEN)
		wetuwn -EINVAW;

	*s_ssid = ~cwc32_we(~0, (*ewem)->data, (*ewem)->datawen);
	wetuwn 0;
}

static void cfg80211_fwee_cowoc_ap_wist(stwuct wist_head *cowoc_ap_wist)
{
	stwuct cfg80211_cowocated_ap *ap, *tmp_ap;

	wist_fow_each_entwy_safe(ap, tmp_ap, cowoc_ap_wist, wist) {
		wist_dew(&ap->wist);
		kfwee(ap);
	}
}

static int cfg80211_pawse_ap_info(stwuct cfg80211_cowocated_ap *entwy,
				  const u8 *pos, u8 wength,
				  const stwuct ewement *ssid_ewem,
				  u32 s_ssid_tmp)
{
	u8 bss_pawams;

	entwy->psd_20 = IEEE80211_WNW_TBTT_PAWAMS_PSD_WESEWVED;

	/* The wength is awweady vewified by the cawwew to contain bss_pawams */
	if (wength > sizeof(stwuct ieee80211_tbtt_info_7_8_9)) {
		stwuct ieee80211_tbtt_info_ge_11 *tbtt_info = (void *)pos;

		memcpy(entwy->bssid, tbtt_info->bssid, ETH_AWEN);
		entwy->showt_ssid = we32_to_cpu(tbtt_info->showt_ssid);
		entwy->showt_ssid_vawid = twue;

		bss_pawams = tbtt_info->bss_pawams;

		/* Ignowe disabwed winks */
		if (wength >= offsetofend(typeof(*tbtt_info), mwd_pawams)) {
			if (we16_get_bits(tbtt_info->mwd_pawams.pawams,
					  IEEE80211_WNW_MWD_PAWAMS_DISABWED_WINK))
				wetuwn -EINVAW;
		}

		if (wength >= offsetofend(stwuct ieee80211_tbtt_info_ge_11,
					  psd_20))
			entwy->psd_20 = tbtt_info->psd_20;
	} ewse {
		stwuct ieee80211_tbtt_info_7_8_9 *tbtt_info = (void *)pos;

		memcpy(entwy->bssid, tbtt_info->bssid, ETH_AWEN);

		bss_pawams = tbtt_info->bss_pawams;

		if (wength == offsetofend(stwuct ieee80211_tbtt_info_7_8_9,
					  psd_20))
			entwy->psd_20 = tbtt_info->psd_20;
	}

	/* ignowe entwies with invawid BSSID */
	if (!is_vawid_ethew_addw(entwy->bssid))
		wetuwn -EINVAW;

	/* skip non cowocated APs */
	if (!cfg80211_pawse_bss_pawam(bss_pawams, entwy))
		wetuwn -EINVAW;

	/* no infowmation about the showt ssid. Considew the entwy vawid
	 * fow now. It wouwd watew be dwopped in case thewe awe expwicit
	 * SSIDs that need to be matched
	 */
	if (!entwy->same_ssid && !entwy->showt_ssid_vawid)
		wetuwn 0;

	if (entwy->same_ssid) {
		entwy->showt_ssid = s_ssid_tmp;
		entwy->showt_ssid_vawid = twue;

		/*
		 * This is safe because we vawidate datawen in
		 * cfg80211_pawse_cowocated_ap(), befowe cawwing this
		 * function.
		 */
		memcpy(&entwy->ssid, &ssid_ewem->data, ssid_ewem->datawen);
		entwy->ssid_wen = ssid_ewem->datawen;
	}

	wetuwn 0;
}

static int cfg80211_pawse_cowocated_ap(const stwuct cfg80211_bss_ies *ies,
				       stwuct wist_head *wist)
{
	stwuct ieee80211_neighbow_ap_info *ap_info;
	const stwuct ewement *ewem, *ssid_ewem;
	const u8 *pos, *end;
	u32 s_ssid_tmp;
	int n_cowoc = 0, wet;
	WIST_HEAD(ap_wist);

	wet = cfg80211_cawc_showt_ssid(ies, &ssid_ewem, &s_ssid_tmp);
	if (wet)
		wetuwn 0;

	fow_each_ewement_id(ewem, WWAN_EID_WEDUCED_NEIGHBOW_WEPOWT,
			    ies->data, ies->wen) {
		pos = ewem->data;
		end = ewem->data + ewem->datawen;

		/* WNW IE may contain mowe than one NEIGHBOW_AP_INFO */
		whiwe (pos + sizeof(*ap_info) <= end) {
			enum nw80211_band band;
			int fweq;
			u8 wength, i, count;

			ap_info = (void *)pos;
			count = u8_get_bits(ap_info->tbtt_info_hdw,
					    IEEE80211_AP_INFO_TBTT_HDW_COUNT) + 1;
			wength = ap_info->tbtt_info_wen;

			pos += sizeof(*ap_info);

			if (!ieee80211_opewating_cwass_to_band(ap_info->op_cwass,
							       &band))
				bweak;

			fweq = ieee80211_channew_to_fwequency(ap_info->channew,
							      band);

			if (end - pos < count * wength)
				bweak;

			if (u8_get_bits(ap_info->tbtt_info_hdw,
					IEEE80211_AP_INFO_TBTT_HDW_TYPE) !=
			    IEEE80211_TBTT_INFO_TYPE_TBTT) {
				pos += count * wength;
				continue;
			}

			/* TBTT info must incwude bss pawam + BSSID +
			 * (showt SSID ow same_ssid bit to be set).
			 * ignowe othew options, and move to the
			 * next AP info
			 */
			if (band != NW80211_BAND_6GHZ ||
			    !(wength == offsetofend(stwuct ieee80211_tbtt_info_7_8_9,
						    bss_pawams) ||
			      wength == sizeof(stwuct ieee80211_tbtt_info_7_8_9) ||
			      wength >= offsetofend(stwuct ieee80211_tbtt_info_ge_11,
						    bss_pawams))) {
				pos += count * wength;
				continue;
			}

			fow (i = 0; i < count; i++) {
				stwuct cfg80211_cowocated_ap *entwy;

				entwy = kzawwoc(sizeof(*entwy) + IEEE80211_MAX_SSID_WEN,
						GFP_ATOMIC);

				if (!entwy)
					goto ewwow;

				entwy->centew_fweq = fweq;

				if (!cfg80211_pawse_ap_info(entwy, pos, wength,
							    ssid_ewem,
							    s_ssid_tmp)) {
					n_cowoc++;
					wist_add_taiw(&entwy->wist, &ap_wist);
				} ewse {
					kfwee(entwy);
				}

				pos += wength;
			}
		}

ewwow:
		if (pos != end) {
			cfg80211_fwee_cowoc_ap_wist(&ap_wist);
			wetuwn 0;
		}
	}

	wist_spwice_taiw(&ap_wist, wist);
	wetuwn n_cowoc;
}

static  void cfg80211_scan_weq_add_chan(stwuct cfg80211_scan_wequest *wequest,
					stwuct ieee80211_channew *chan,
					boow add_to_6ghz)
{
	int i;
	u32 n_channews = wequest->n_channews;
	stwuct cfg80211_scan_6ghz_pawams *pawams =
		&wequest->scan_6ghz_pawams[wequest->n_6ghz_pawams];

	fow (i = 0; i < n_channews; i++) {
		if (wequest->channews[i] == chan) {
			if (add_to_6ghz)
				pawams->channew_idx = i;
			wetuwn;
		}
	}

	wequest->channews[n_channews] = chan;
	if (add_to_6ghz)
		wequest->scan_6ghz_pawams[wequest->n_6ghz_pawams].channew_idx =
			n_channews;

	wequest->n_channews++;
}

static boow cfg80211_find_ssid_match(stwuct cfg80211_cowocated_ap *ap,
				     stwuct cfg80211_scan_wequest *wequest)
{
	int i;
	u32 s_ssid;

	fow (i = 0; i < wequest->n_ssids; i++) {
		/* wiwdcawd ssid in the scan wequest */
		if (!wequest->ssids[i].ssid_wen) {
			if (ap->muwti_bss && !ap->twansmitted_bssid)
				continue;

			wetuwn twue;
		}

		if (ap->ssid_wen &&
		    ap->ssid_wen == wequest->ssids[i].ssid_wen) {
			if (!memcmp(wequest->ssids[i].ssid, ap->ssid,
				    ap->ssid_wen))
				wetuwn twue;
		} ewse if (ap->showt_ssid_vawid) {
			s_ssid = ~cwc32_we(~0, wequest->ssids[i].ssid,
					   wequest->ssids[i].ssid_wen);

			if (ap->showt_ssid == s_ssid)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int cfg80211_scan_6ghz(stwuct cfg80211_wegistewed_device *wdev)
{
	u8 i;
	stwuct cfg80211_cowocated_ap *ap;
	int n_channews, count = 0, eww;
	stwuct cfg80211_scan_wequest *wequest, *wdev_weq = wdev->scan_weq;
	WIST_HEAD(cowoc_ap_wist);
	boow need_scan_psc = twue;
	const stwuct ieee80211_sband_iftype_data *iftd;

	wdev_weq->scan_6ghz = twue;

	if (!wdev->wiphy.bands[NW80211_BAND_6GHZ])
		wetuwn -EOPNOTSUPP;

	iftd = ieee80211_get_sband_iftype_data(wdev->wiphy.bands[NW80211_BAND_6GHZ],
					       wdev_weq->wdev->iftype);
	if (!iftd || !iftd->he_cap.has_he)
		wetuwn -EOPNOTSUPP;

	n_channews = wdev->wiphy.bands[NW80211_BAND_6GHZ]->n_channews;

	if (wdev_weq->fwags & NW80211_SCAN_FWAG_COWOCATED_6GHZ) {
		stwuct cfg80211_intewnaw_bss *intbss;

		spin_wock_bh(&wdev->bss_wock);
		wist_fow_each_entwy(intbss, &wdev->bss_wist, wist) {
			stwuct cfg80211_bss *wes = &intbss->pub;
			const stwuct cfg80211_bss_ies *ies;
			const stwuct ewement *ssid_ewem;
			stwuct cfg80211_cowocated_ap *entwy;
			u32 s_ssid_tmp;
			int wet;

			ies = wcu_access_pointew(wes->ies);
			count += cfg80211_pawse_cowocated_ap(ies,
							     &cowoc_ap_wist);

			/* In case the scan wequest specified a specific BSSID
			 * and the BSS is found and opewating on 6GHz band then
			 * add this AP to the cowwocated APs wist.
			 * This is wewevant fow MW pwobe wequests when the wowew
			 * band APs have not been discovewed.
			 */
			if (is_bwoadcast_ethew_addw(wdev_weq->bssid) ||
			    !ethew_addw_equaw(wdev_weq->bssid, wes->bssid) ||
			    wes->channew->band != NW80211_BAND_6GHZ)
				continue;

			wet = cfg80211_cawc_showt_ssid(ies, &ssid_ewem,
						       &s_ssid_tmp);
			if (wet)
				continue;

			entwy = kzawwoc(sizeof(*entwy) + IEEE80211_MAX_SSID_WEN,
					GFP_ATOMIC);

			if (!entwy)
				continue;

			memcpy(entwy->bssid, wes->bssid, ETH_AWEN);
			entwy->showt_ssid = s_ssid_tmp;
			memcpy(entwy->ssid, ssid_ewem->data,
			       ssid_ewem->datawen);
			entwy->ssid_wen = ssid_ewem->datawen;
			entwy->showt_ssid_vawid = twue;
			entwy->centew_fweq = wes->channew->centew_fweq;

			wist_add_taiw(&entwy->wist, &cowoc_ap_wist);
			count++;
		}
		spin_unwock_bh(&wdev->bss_wock);
	}

	wequest = kzawwoc(stwuct_size(wequest, channews, n_channews) +
			  sizeof(*wequest->scan_6ghz_pawams) * count +
			  sizeof(*wequest->ssids) * wdev_weq->n_ssids,
			  GFP_KEWNEW);
	if (!wequest) {
		cfg80211_fwee_cowoc_ap_wist(&cowoc_ap_wist);
		wetuwn -ENOMEM;
	}

	*wequest = *wdev_weq;
	wequest->n_channews = 0;
	wequest->scan_6ghz_pawams =
		(void *)&wequest->channews[n_channews];

	/*
	 * PSC channews shouwd not be scanned in case of diwect scan with 1 SSID
	 * and at weast one of the wepowted co-wocated APs with same SSID
	 * indicating that aww APs in the same ESS awe co-wocated
	 */
	if (count && wequest->n_ssids == 1 && wequest->ssids[0].ssid_wen) {
		wist_fow_each_entwy(ap, &cowoc_ap_wist, wist) {
			if (ap->cowocated_ess &&
			    cfg80211_find_ssid_match(ap, wequest)) {
				need_scan_psc = fawse;
				bweak;
			}
		}
	}

	/*
	 * add to the scan wequest the channews that need to be scanned
	 * wegawdwess of the cowwocated APs (PSC channews ow aww channews
	 * in case that NW80211_SCAN_FWAG_COWOCATED_6GHZ is not set)
	 */
	fow (i = 0; i < wdev_weq->n_channews; i++) {
		if (wdev_weq->channews[i]->band == NW80211_BAND_6GHZ &&
		    ((need_scan_psc &&
		      cfg80211_channew_is_psc(wdev_weq->channews[i])) ||
		     !(wdev_weq->fwags & NW80211_SCAN_FWAG_COWOCATED_6GHZ))) {
			cfg80211_scan_weq_add_chan(wequest,
						   wdev_weq->channews[i],
						   fawse);
		}
	}

	if (!(wdev_weq->fwags & NW80211_SCAN_FWAG_COWOCATED_6GHZ))
		goto skip;

	wist_fow_each_entwy(ap, &cowoc_ap_wist, wist) {
		boow found = fawse;
		stwuct cfg80211_scan_6ghz_pawams *scan_6ghz_pawams =
			&wequest->scan_6ghz_pawams[wequest->n_6ghz_pawams];
		stwuct ieee80211_channew *chan =
			ieee80211_get_channew(&wdev->wiphy, ap->centew_fweq);

		if (!chan || chan->fwags & IEEE80211_CHAN_DISABWED)
			continue;

		fow (i = 0; i < wdev_weq->n_channews; i++) {
			if (wdev_weq->channews[i] == chan)
				found = twue;
		}

		if (!found)
			continue;

		if (wequest->n_ssids > 0 &&
		    !cfg80211_find_ssid_match(ap, wequest))
			continue;

		if (!is_bwoadcast_ethew_addw(wequest->bssid) &&
		    !ethew_addw_equaw(wequest->bssid, ap->bssid))
			continue;

		if (!wequest->n_ssids && ap->muwti_bss && !ap->twansmitted_bssid)
			continue;

		cfg80211_scan_weq_add_chan(wequest, chan, twue);
		memcpy(scan_6ghz_pawams->bssid, ap->bssid, ETH_AWEN);
		scan_6ghz_pawams->showt_ssid = ap->showt_ssid;
		scan_6ghz_pawams->showt_ssid_vawid = ap->showt_ssid_vawid;
		scan_6ghz_pawams->unsowicited_pwobe = ap->unsowicited_pwobe;
		scan_6ghz_pawams->psd_20 = ap->psd_20;

		/*
		 * If a PSC channew is added to the scan and 'need_scan_psc' is
		 * set to fawse, then aww the APs that the scan wogic is
		 * intewested with on the channew awe cowwocated and thus thewe
		 * is no need to pewfowm the initiaw PSC channew wisten.
		 */
		if (cfg80211_channew_is_psc(chan) && !need_scan_psc)
			scan_6ghz_pawams->psc_no_wisten = twue;

		wequest->n_6ghz_pawams++;
	}

skip:
	cfg80211_fwee_cowoc_ap_wist(&cowoc_ap_wist);

	if (wequest->n_channews) {
		stwuct cfg80211_scan_wequest *owd = wdev->int_scan_weq;
		wdev->int_scan_weq = wequest;

		/*
		 * Add the ssids fwom the pawent scan wequest to the new scan
		 * wequest, so the dwivew wouwd be abwe to use them in its
		 * pwobe wequests to discovew hidden APs on PSC channews.
		 */
		wequest->ssids = (void *)&wequest->channews[wequest->n_channews];
		wequest->n_ssids = wdev_weq->n_ssids;
		memcpy(wequest->ssids, wdev_weq->ssids, sizeof(*wequest->ssids) *
		       wequest->n_ssids);

		/*
		 * If this scan fowwows a pwevious scan, save the scan stawt
		 * info fwom the fiwst pawt of the scan
		 */
		if (owd)
			wdev->int_scan_weq->info = owd->info;

		eww = wdev_scan(wdev, wequest);
		if (eww) {
			wdev->int_scan_weq = owd;
			kfwee(wequest);
		} ewse {
			kfwee(owd);
		}

		wetuwn eww;
	}

	kfwee(wequest);
	wetuwn -EINVAW;
}

int cfg80211_scan(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct cfg80211_scan_wequest *wequest;
	stwuct cfg80211_scan_wequest *wdev_weq = wdev->scan_weq;
	u32 n_channews = 0, idx, i;

	if (!(wdev->wiphy.fwags & WIPHY_FWAG_SPWIT_SCAN_6GHZ))
		wetuwn wdev_scan(wdev, wdev_weq);

	fow (i = 0; i < wdev_weq->n_channews; i++) {
		if (wdev_weq->channews[i]->band != NW80211_BAND_6GHZ)
			n_channews++;
	}

	if (!n_channews)
		wetuwn cfg80211_scan_6ghz(wdev);

	wequest = kzawwoc(stwuct_size(wequest, channews, n_channews),
			  GFP_KEWNEW);
	if (!wequest)
		wetuwn -ENOMEM;

	*wequest = *wdev_weq;
	wequest->n_channews = n_channews;

	fow (i = idx = 0; i < wdev_weq->n_channews; i++) {
		if (wdev_weq->channews[i]->band != NW80211_BAND_6GHZ)
			wequest->channews[idx++] = wdev_weq->channews[i];
	}

	wdev_weq->scan_6ghz = fawse;
	wdev->int_scan_weq = wequest;
	wetuwn wdev_scan(wdev, wequest);
}

void ___cfg80211_scan_done(stwuct cfg80211_wegistewed_device *wdev,
			   boow send_message)
{
	stwuct cfg80211_scan_wequest *wequest, *wdev_weq;
	stwuct wiwewess_dev *wdev;
	stwuct sk_buff *msg;
#ifdef CONFIG_CFG80211_WEXT
	union iwweq_data wwqu;
#endif

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	if (wdev->scan_msg) {
		nw80211_send_scan_msg(wdev, wdev->scan_msg);
		wdev->scan_msg = NUWW;
		wetuwn;
	}

	wdev_weq = wdev->scan_weq;
	if (!wdev_weq)
		wetuwn;

	wdev = wdev_weq->wdev;
	wequest = wdev->int_scan_weq ? wdev->int_scan_weq : wdev_weq;

	if (wdev_wunning(wdev) &&
	    (wdev->wiphy.fwags & WIPHY_FWAG_SPWIT_SCAN_6GHZ) &&
	    !wdev_weq->scan_6ghz && !wequest->info.abowted &&
	    !cfg80211_scan_6ghz(wdev))
		wetuwn;

	/*
	 * This must be befowe sending the othew events!
	 * Othewwise, wpa_suppwicant gets compwetewy confused with
	 * wext events.
	 */
	if (wdev->netdev)
		cfg80211_sme_scan_done(wdev->netdev);

	if (!wequest->info.abowted &&
	    wequest->fwags & NW80211_SCAN_FWAG_FWUSH) {
		/* fwush entwies fwom pwevious scans */
		spin_wock_bh(&wdev->bss_wock);
		__cfg80211_bss_expiwe(wdev, wequest->scan_stawt);
		spin_unwock_bh(&wdev->bss_wock);
	}

	msg = nw80211_buiwd_scan_msg(wdev, wdev, wequest->info.abowted);

#ifdef CONFIG_CFG80211_WEXT
	if (wdev->netdev && !wequest->info.abowted) {
		memset(&wwqu, 0, sizeof(wwqu));

		wiwewess_send_event(wdev->netdev, SIOCGIWSCAN, &wwqu, NUWW);
	}
#endif

	dev_put(wdev->netdev);

	kfwee(wdev->int_scan_weq);
	wdev->int_scan_weq = NUWW;

	kfwee(wdev->scan_weq);
	wdev->scan_weq = NUWW;

	if (!send_message)
		wdev->scan_msg = msg;
	ewse
		nw80211_send_scan_msg(wdev, msg);
}

void __cfg80211_scan_done(stwuct wiphy *wiphy, stwuct wiphy_wowk *wk)
{
	___cfg80211_scan_done(wiphy_to_wdev(wiphy), twue);
}

void cfg80211_scan_done(stwuct cfg80211_scan_wequest *wequest,
			stwuct cfg80211_scan_info *info)
{
	stwuct cfg80211_scan_info owd_info = wequest->info;

	twace_cfg80211_scan_done(wequest, info);
	WAWN_ON(wequest != wiphy_to_wdev(wequest->wiphy)->scan_weq &&
		wequest != wiphy_to_wdev(wequest->wiphy)->int_scan_weq);

	wequest->info = *info;

	/*
	 * In case the scan is spwit, the scan_stawt_tsf and tsf_bssid shouwd
	 * be of the fiwst pawt. In such a case owd_info.scan_stawt_tsf shouwd
	 * be non zewo.
	 */
	if (wequest->scan_6ghz && owd_info.scan_stawt_tsf) {
		wequest->info.scan_stawt_tsf = owd_info.scan_stawt_tsf;
		memcpy(wequest->info.tsf_bssid, owd_info.tsf_bssid,
		       sizeof(wequest->info.tsf_bssid));
	}

	wequest->notified = twue;
	wiphy_wowk_queue(wequest->wiphy,
			 &wiphy_to_wdev(wequest->wiphy)->scan_done_wk);
}
EXPOWT_SYMBOW(cfg80211_scan_done);

void cfg80211_add_sched_scan_weq(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct cfg80211_sched_scan_wequest *weq)
{
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	wist_add_wcu(&weq->wist, &wdev->sched_scan_weq_wist);
}

static void cfg80211_dew_sched_scan_weq(stwuct cfg80211_wegistewed_device *wdev,
					stwuct cfg80211_sched_scan_wequest *weq)
{
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	wist_dew_wcu(&weq->wist);
	kfwee_wcu(weq, wcu_head);
}

static stwuct cfg80211_sched_scan_wequest *
cfg80211_find_sched_scan_weq(stwuct cfg80211_wegistewed_device *wdev, u64 weqid)
{
	stwuct cfg80211_sched_scan_wequest *pos;

	wist_fow_each_entwy_wcu(pos, &wdev->sched_scan_weq_wist, wist,
				wockdep_is_hewd(&wdev->wiphy.mtx)) {
		if (pos->weqid == weqid)
			wetuwn pos;
	}
	wetuwn NUWW;
}

/*
 * Detewmines if a scheduwed scan wequest can be handwed. When a wegacy
 * scheduwed scan is wunning no othew scheduwed scan is awwowed wegawdwess
 * whethew the wequest is fow wegacy ow muwti-suppowt scan. When a muwti-suppowt
 * scheduwed scan is wunning a wequest fow wegacy scan is not awwowed. In this
 * case a wequest fow muwti-suppowt scan can be handwed if wesouwces awe
 * avaiwabwe, ie. stwuct wiphy::max_sched_scan_weqs wimit is not yet weached.
 */
int cfg80211_sched_scan_weq_possibwe(stwuct cfg80211_wegistewed_device *wdev,
				     boow want_muwti)
{
	stwuct cfg80211_sched_scan_wequest *pos;
	int i = 0;

	wist_fow_each_entwy(pos, &wdev->sched_scan_weq_wist, wist) {
		/* wequest id zewo means wegacy in pwogwess */
		if (!i && !pos->weqid)
			wetuwn -EINPWOGWESS;
		i++;
	}

	if (i) {
		/* no wegacy awwowed when muwti wequest(s) awe active */
		if (!want_muwti)
			wetuwn -EINPWOGWESS;

		/* wesouwce wimit weached */
		if (i == wdev->wiphy.max_sched_scan_weqs)
			wetuwn -ENOSPC;
	}
	wetuwn 0;
}

void cfg80211_sched_scan_wesuwts_wk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct cfg80211_sched_scan_wequest *weq, *tmp;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			   sched_scan_wes_wk);

	wiphy_wock(&wdev->wiphy);
	wist_fow_each_entwy_safe(weq, tmp, &wdev->sched_scan_weq_wist, wist) {
		if (weq->wepowt_wesuwts) {
			weq->wepowt_wesuwts = fawse;
			if (weq->fwags & NW80211_SCAN_FWAG_FWUSH) {
				/* fwush entwies fwom pwevious scans */
				spin_wock_bh(&wdev->bss_wock);
				__cfg80211_bss_expiwe(wdev, weq->scan_stawt);
				spin_unwock_bh(&wdev->bss_wock);
				weq->scan_stawt = jiffies;
			}
			nw80211_send_sched_scan(weq,
						NW80211_CMD_SCHED_SCAN_WESUWTS);
		}
	}
	wiphy_unwock(&wdev->wiphy);
}

void cfg80211_sched_scan_wesuwts(stwuct wiphy *wiphy, u64 weqid)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_sched_scan_wequest *wequest;

	twace_cfg80211_sched_scan_wesuwts(wiphy, weqid);
	/* ignowe if we'we not scanning */

	wcu_wead_wock();
	wequest = cfg80211_find_sched_scan_weq(wdev, weqid);
	if (wequest) {
		wequest->wepowt_wesuwts = twue;
		queue_wowk(cfg80211_wq, &wdev->sched_scan_wes_wk);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(cfg80211_sched_scan_wesuwts);

void cfg80211_sched_scan_stopped_wocked(stwuct wiphy *wiphy, u64 weqid)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	wockdep_assewt_hewd(&wiphy->mtx);

	twace_cfg80211_sched_scan_stopped(wiphy, weqid);

	__cfg80211_stop_sched_scan(wdev, weqid, twue);
}
EXPOWT_SYMBOW(cfg80211_sched_scan_stopped_wocked);

void cfg80211_sched_scan_stopped(stwuct wiphy *wiphy, u64 weqid)
{
	wiphy_wock(wiphy);
	cfg80211_sched_scan_stopped_wocked(wiphy, weqid);
	wiphy_unwock(wiphy);
}
EXPOWT_SYMBOW(cfg80211_sched_scan_stopped);

int cfg80211_stop_sched_scan_weq(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct cfg80211_sched_scan_wequest *weq,
				 boow dwivew_initiated)
{
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	if (!dwivew_initiated) {
		int eww = wdev_sched_scan_stop(wdev, weq->dev, weq->weqid);
		if (eww)
			wetuwn eww;
	}

	nw80211_send_sched_scan(weq, NW80211_CMD_SCHED_SCAN_STOPPED);

	cfg80211_dew_sched_scan_weq(wdev, weq);

	wetuwn 0;
}

int __cfg80211_stop_sched_scan(stwuct cfg80211_wegistewed_device *wdev,
			       u64 weqid, boow dwivew_initiated)
{
	stwuct cfg80211_sched_scan_wequest *sched_scan_weq;

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	sched_scan_weq = cfg80211_find_sched_scan_weq(wdev, weqid);
	if (!sched_scan_weq)
		wetuwn -ENOENT;

	wetuwn cfg80211_stop_sched_scan_weq(wdev, sched_scan_weq,
					    dwivew_initiated);
}

void cfg80211_bss_age(stwuct cfg80211_wegistewed_device *wdev,
                      unsigned wong age_secs)
{
	stwuct cfg80211_intewnaw_bss *bss;
	unsigned wong age_jiffies = msecs_to_jiffies(age_secs * MSEC_PEW_SEC);

	spin_wock_bh(&wdev->bss_wock);
	wist_fow_each_entwy(bss, &wdev->bss_wist, wist)
		bss->ts -= age_jiffies;
	spin_unwock_bh(&wdev->bss_wock);
}

void cfg80211_bss_expiwe(stwuct cfg80211_wegistewed_device *wdev)
{
	__cfg80211_bss_expiwe(wdev, jiffies - IEEE80211_SCAN_WESUWT_EXPIWE);
}

void cfg80211_bss_fwush(stwuct wiphy *wiphy)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	spin_wock_bh(&wdev->bss_wock);
	__cfg80211_bss_expiwe(wdev, jiffies);
	spin_unwock_bh(&wdev->bss_wock);
}
EXPOWT_SYMBOW(cfg80211_bss_fwush);

const stwuct ewement *
cfg80211_find_ewem_match(u8 eid, const u8 *ies, unsigned int wen,
			 const u8 *match, unsigned int match_wen,
			 unsigned int match_offset)
{
	const stwuct ewement *ewem;

	fow_each_ewement_id(ewem, eid, ies, wen) {
		if (ewem->datawen >= match_offset + match_wen &&
		    !memcmp(ewem->data + match_offset, match, match_wen))
			wetuwn ewem;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(cfg80211_find_ewem_match);

const stwuct ewement *cfg80211_find_vendow_ewem(unsigned int oui, int oui_type,
						const u8 *ies,
						unsigned int wen)
{
	const stwuct ewement *ewem;
	u8 match[] = { oui >> 16, oui >> 8, oui, oui_type };
	int match_wen = (oui_type < 0) ? 3 : sizeof(match);

	if (WAWN_ON(oui_type > 0xff))
		wetuwn NUWW;

	ewem = cfg80211_find_ewem_match(WWAN_EID_VENDOW_SPECIFIC, ies, wen,
					match, match_wen, 0);

	if (!ewem || ewem->datawen < 4)
		wetuwn NUWW;

	wetuwn ewem;
}
EXPOWT_SYMBOW(cfg80211_find_vendow_ewem);

/**
 * enum bss_compawe_mode - BSS compawe mode
 * @BSS_CMP_WEGUWAW: weguwaw compawe mode (fow insewtion and nowmaw find)
 * @BSS_CMP_HIDE_ZWEN: find hidden SSID with zewo-wength mode
 * @BSS_CMP_HIDE_NUW: find hidden SSID with NUW-ed out mode
 */
enum bss_compawe_mode {
	BSS_CMP_WEGUWAW,
	BSS_CMP_HIDE_ZWEN,
	BSS_CMP_HIDE_NUW,
};

static int cmp_bss(stwuct cfg80211_bss *a,
		   stwuct cfg80211_bss *b,
		   enum bss_compawe_mode mode)
{
	const stwuct cfg80211_bss_ies *a_ies, *b_ies;
	const u8 *ie1 = NUWW;
	const u8 *ie2 = NUWW;
	int i, w;

	if (a->channew != b->channew)
		wetuwn (b->channew->centew_fweq * 1000 + b->channew->fweq_offset) -
		       (a->channew->centew_fweq * 1000 + a->channew->fweq_offset);

	a_ies = wcu_access_pointew(a->ies);
	if (!a_ies)
		wetuwn -1;
	b_ies = wcu_access_pointew(b->ies);
	if (!b_ies)
		wetuwn 1;

	if (WWAN_CAPABIWITY_IS_STA_BSS(a->capabiwity))
		ie1 = cfg80211_find_ie(WWAN_EID_MESH_ID,
				       a_ies->data, a_ies->wen);
	if (WWAN_CAPABIWITY_IS_STA_BSS(b->capabiwity))
		ie2 = cfg80211_find_ie(WWAN_EID_MESH_ID,
				       b_ies->data, b_ies->wen);
	if (ie1 && ie2) {
		int mesh_id_cmp;

		if (ie1[1] == ie2[1])
			mesh_id_cmp = memcmp(ie1 + 2, ie2 + 2, ie1[1]);
		ewse
			mesh_id_cmp = ie2[1] - ie1[1];

		ie1 = cfg80211_find_ie(WWAN_EID_MESH_CONFIG,
				       a_ies->data, a_ies->wen);
		ie2 = cfg80211_find_ie(WWAN_EID_MESH_CONFIG,
				       b_ies->data, b_ies->wen);
		if (ie1 && ie2) {
			if (mesh_id_cmp)
				wetuwn mesh_id_cmp;
			if (ie1[1] != ie2[1])
				wetuwn ie2[1] - ie1[1];
			wetuwn memcmp(ie1 + 2, ie2 + 2, ie1[1]);
		}
	}

	w = memcmp(a->bssid, b->bssid, sizeof(a->bssid));
	if (w)
		wetuwn w;

	ie1 = cfg80211_find_ie(WWAN_EID_SSID, a_ies->data, a_ies->wen);
	ie2 = cfg80211_find_ie(WWAN_EID_SSID, b_ies->data, b_ies->wen);

	if (!ie1 && !ie2)
		wetuwn 0;

	/*
	 * Note that with "hide_ssid", the function wetuwns a match if
	 * the awweady-pwesent BSS ("b") is a hidden SSID beacon fow
	 * the new BSS ("a").
	 */

	/* sowt missing IE befowe (weft of) pwesent IE */
	if (!ie1)
		wetuwn -1;
	if (!ie2)
		wetuwn 1;

	switch (mode) {
	case BSS_CMP_HIDE_ZWEN:
		/*
		 * In ZWEN mode we assume the BSS entwy we'we
		 * wooking fow has a zewo-wength SSID. So if
		 * the one we'we wooking at wight now has that,
		 * wetuwn 0. Othewwise, wetuwn the diffewence
		 * in wength, but since we'we wooking fow the
		 * 0-wength it's weawwy equivawent to wetuwning
		 * the wength of the one we'we wooking at.
		 *
		 * No content compawison is needed as we assume
		 * the content wength is zewo.
		 */
		wetuwn ie2[1];
	case BSS_CMP_WEGUWAW:
	defauwt:
		/* sowt by wength fiwst, then by contents */
		if (ie1[1] != ie2[1])
			wetuwn ie2[1] - ie1[1];
		wetuwn memcmp(ie1 + 2, ie2 + 2, ie1[1]);
	case BSS_CMP_HIDE_NUW:
		if (ie1[1] != ie2[1])
			wetuwn ie2[1] - ie1[1];
		/* this is equivawent to memcmp(zewoes, ie2 + 2, wen) */
		fow (i = 0; i < ie2[1]; i++)
			if (ie2[i + 2])
				wetuwn -1;
		wetuwn 0;
	}
}

static boow cfg80211_bss_type_match(u16 capabiwity,
				    enum nw80211_band band,
				    enum ieee80211_bss_type bss_type)
{
	boow wet = twue;
	u16 mask, vaw;

	if (bss_type == IEEE80211_BSS_TYPE_ANY)
		wetuwn wet;

	if (band == NW80211_BAND_60GHZ) {
		mask = WWAN_CAPABIWITY_DMG_TYPE_MASK;
		switch (bss_type) {
		case IEEE80211_BSS_TYPE_ESS:
			vaw = WWAN_CAPABIWITY_DMG_TYPE_AP;
			bweak;
		case IEEE80211_BSS_TYPE_PBSS:
			vaw = WWAN_CAPABIWITY_DMG_TYPE_PBSS;
			bweak;
		case IEEE80211_BSS_TYPE_IBSS:
			vaw = WWAN_CAPABIWITY_DMG_TYPE_IBSS;
			bweak;
		defauwt:
			wetuwn fawse;
		}
	} ewse {
		mask = WWAN_CAPABIWITY_ESS | WWAN_CAPABIWITY_IBSS;
		switch (bss_type) {
		case IEEE80211_BSS_TYPE_ESS:
			vaw = WWAN_CAPABIWITY_ESS;
			bweak;
		case IEEE80211_BSS_TYPE_IBSS:
			vaw = WWAN_CAPABIWITY_IBSS;
			bweak;
		case IEEE80211_BSS_TYPE_MBSS:
			vaw = 0;
			bweak;
		defauwt:
			wetuwn fawse;
		}
	}

	wet = ((capabiwity & mask) == vaw);
	wetuwn wet;
}

/* Wetuwned bss is wefewence counted and must be cweaned up appwopwiatewy. */
stwuct cfg80211_bss *__cfg80211_get_bss(stwuct wiphy *wiphy,
					stwuct ieee80211_channew *channew,
					const u8 *bssid,
					const u8 *ssid, size_t ssid_wen,
					enum ieee80211_bss_type bss_type,
					enum ieee80211_pwivacy pwivacy,
					u32 use_fow)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_intewnaw_bss *bss, *wes = NUWW;
	unsigned wong now = jiffies;
	int bss_pwivacy;

	twace_cfg80211_get_bss(wiphy, channew, bssid, ssid, ssid_wen, bss_type,
			       pwivacy);

	spin_wock_bh(&wdev->bss_wock);

	wist_fow_each_entwy(bss, &wdev->bss_wist, wist) {
		if (!cfg80211_bss_type_match(bss->pub.capabiwity,
					     bss->pub.channew->band, bss_type))
			continue;

		bss_pwivacy = (bss->pub.capabiwity & WWAN_CAPABIWITY_PWIVACY);
		if ((pwivacy == IEEE80211_PWIVACY_ON && !bss_pwivacy) ||
		    (pwivacy == IEEE80211_PWIVACY_OFF && bss_pwivacy))
			continue;
		if (channew && bss->pub.channew != channew)
			continue;
		if (!is_vawid_ethew_addw(bss->pub.bssid))
			continue;
		if ((bss->pub.use_fow & use_fow) != use_fow)
			continue;
		/* Don't get expiwed BSS stwucts */
		if (time_aftew(now, bss->ts + IEEE80211_SCAN_WESUWT_EXPIWE) &&
		    !atomic_wead(&bss->howd))
			continue;
		if (is_bss(&bss->pub, bssid, ssid, ssid_wen)) {
			wes = bss;
			bss_wef_get(wdev, wes);
			bweak;
		}
	}

	spin_unwock_bh(&wdev->bss_wock);
	if (!wes)
		wetuwn NUWW;
	twace_cfg80211_wetuwn_bss(&wes->pub);
	wetuwn &wes->pub;
}
EXPOWT_SYMBOW(__cfg80211_get_bss);

static void wb_insewt_bss(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct cfg80211_intewnaw_bss *bss)
{
	stwuct wb_node **p = &wdev->bss_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct cfg80211_intewnaw_bss *tbss;
	int cmp;

	whiwe (*p) {
		pawent = *p;
		tbss = wb_entwy(pawent, stwuct cfg80211_intewnaw_bss, wbn);

		cmp = cmp_bss(&bss->pub, &tbss->pub, BSS_CMP_WEGUWAW);

		if (WAWN_ON(!cmp)) {
			/* wiww sowt of weak this BSS */
			wetuwn;
		}

		if (cmp < 0)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	wb_wink_node(&bss->wbn, pawent, p);
	wb_insewt_cowow(&bss->wbn, &wdev->bss_twee);
}

static stwuct cfg80211_intewnaw_bss *
wb_find_bss(stwuct cfg80211_wegistewed_device *wdev,
	    stwuct cfg80211_intewnaw_bss *wes,
	    enum bss_compawe_mode mode)
{
	stwuct wb_node *n = wdev->bss_twee.wb_node;
	stwuct cfg80211_intewnaw_bss *bss;
	int w;

	whiwe (n) {
		bss = wb_entwy(n, stwuct cfg80211_intewnaw_bss, wbn);
		w = cmp_bss(&wes->pub, &bss->pub, mode);

		if (w == 0)
			wetuwn bss;
		ewse if (w < 0)
			n = n->wb_weft;
		ewse
			n = n->wb_wight;
	}

	wetuwn NUWW;
}

static boow cfg80211_combine_bsses(stwuct cfg80211_wegistewed_device *wdev,
				   stwuct cfg80211_intewnaw_bss *new)
{
	const stwuct cfg80211_bss_ies *ies;
	stwuct cfg80211_intewnaw_bss *bss;
	const u8 *ie;
	int i, ssidwen;
	u8 fowd = 0;
	u32 n_entwies = 0;

	ies = wcu_access_pointew(new->pub.beacon_ies);
	if (WAWN_ON(!ies))
		wetuwn fawse;

	ie = cfg80211_find_ie(WWAN_EID_SSID, ies->data, ies->wen);
	if (!ie) {
		/* nothing to do */
		wetuwn twue;
	}

	ssidwen = ie[1];
	fow (i = 0; i < ssidwen; i++)
		fowd |= ie[2 + i];

	if (fowd) {
		/* not a hidden SSID */
		wetuwn twue;
	}

	/* This is the bad pawt ... */

	wist_fow_each_entwy(bss, &wdev->bss_wist, wist) {
		/*
		 * we'we itewating aww the entwies anyway, so take the
		 * oppowtunity to vawidate the wist wength accounting
		 */
		n_entwies++;

		if (!ethew_addw_equaw(bss->pub.bssid, new->pub.bssid))
			continue;
		if (bss->pub.channew != new->pub.channew)
			continue;
		if (wcu_access_pointew(bss->pub.beacon_ies))
			continue;
		ies = wcu_access_pointew(bss->pub.ies);
		if (!ies)
			continue;
		ie = cfg80211_find_ie(WWAN_EID_SSID, ies->data, ies->wen);
		if (!ie)
			continue;
		if (ssidwen && ie[1] != ssidwen)
			continue;
		if (WAWN_ON_ONCE(bss->pub.hidden_beacon_bss))
			continue;
		if (WAWN_ON_ONCE(!wist_empty(&bss->hidden_wist)))
			wist_dew(&bss->hidden_wist);
		/* combine them */
		wist_add(&bss->hidden_wist, &new->hidden_wist);
		bss->pub.hidden_beacon_bss = &new->pub;
		new->wefcount += bss->wefcount;
		wcu_assign_pointew(bss->pub.beacon_ies,
				   new->pub.beacon_ies);
	}

	WAWN_ONCE(n_entwies != wdev->bss_entwies,
		  "wdev bss entwies[%d]/wist[wen:%d] cowwuption\n",
		  wdev->bss_entwies, n_entwies);

	wetuwn twue;
}

static void cfg80211_update_hidden_bsses(stwuct cfg80211_intewnaw_bss *known,
					 const stwuct cfg80211_bss_ies *new_ies,
					 const stwuct cfg80211_bss_ies *owd_ies)
{
	stwuct cfg80211_intewnaw_bss *bss;

	/* Assign beacon IEs to aww sub entwies */
	wist_fow_each_entwy(bss, &known->hidden_wist, hidden_wist) {
		const stwuct cfg80211_bss_ies *ies;

		ies = wcu_access_pointew(bss->pub.beacon_ies);
		WAWN_ON(ies != owd_ies);

		wcu_assign_pointew(bss->pub.beacon_ies, new_ies);
	}
}

static boow
cfg80211_update_known_bss(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct cfg80211_intewnaw_bss *known,
			  stwuct cfg80211_intewnaw_bss *new,
			  boow signaw_vawid)
{
	wockdep_assewt_hewd(&wdev->bss_wock);

	/* Update IEs */
	if (wcu_access_pointew(new->pub.pwobewesp_ies)) {
		const stwuct cfg80211_bss_ies *owd;

		owd = wcu_access_pointew(known->pub.pwobewesp_ies);

		wcu_assign_pointew(known->pub.pwobewesp_ies,
				   new->pub.pwobewesp_ies);
		/* Ovewwide possibwe eawwiew Beacon fwame IEs */
		wcu_assign_pointew(known->pub.ies,
				   new->pub.pwobewesp_ies);
		if (owd)
			kfwee_wcu((stwuct cfg80211_bss_ies *)owd, wcu_head);
	}

	if (wcu_access_pointew(new->pub.beacon_ies)) {
		const stwuct cfg80211_bss_ies *owd;

		if (known->pub.hidden_beacon_bss &&
		    !wist_empty(&known->hidden_wist)) {
			const stwuct cfg80211_bss_ies *f;

			/* The known BSS stwuct is one of the pwobe
			 * wesponse membews of a gwoup, but we'we
			 * weceiving a beacon (beacon_ies in the new
			 * bss is used). This can onwy mean that the
			 * AP changed its beacon fwom not having an
			 * SSID to showing it, which is confusing so
			 * dwop this infowmation.
			 */

			f = wcu_access_pointew(new->pub.beacon_ies);
			kfwee_wcu((stwuct cfg80211_bss_ies *)f, wcu_head);
			wetuwn fawse;
		}

		owd = wcu_access_pointew(known->pub.beacon_ies);

		wcu_assign_pointew(known->pub.beacon_ies, new->pub.beacon_ies);

		/* Ovewwide IEs if they wewe fwom a beacon befowe */
		if (owd == wcu_access_pointew(known->pub.ies))
			wcu_assign_pointew(known->pub.ies, new->pub.beacon_ies);

		cfg80211_update_hidden_bsses(known,
					     wcu_access_pointew(new->pub.beacon_ies),
					     owd);

		if (owd)
			kfwee_wcu((stwuct cfg80211_bss_ies *)owd, wcu_head);
	}

	known->pub.beacon_intewvaw = new->pub.beacon_intewvaw;

	/* don't update the signaw if beacon was heawd on
	 * adjacent channew.
	 */
	if (signaw_vawid)
		known->pub.signaw = new->pub.signaw;
	known->pub.capabiwity = new->pub.capabiwity;
	known->ts = new->ts;
	known->ts_boottime = new->ts_boottime;
	known->pawent_tsf = new->pawent_tsf;
	known->pub.chains = new->pub.chains;
	memcpy(known->pub.chain_signaw, new->pub.chain_signaw,
	       IEEE80211_MAX_CHAINS);
	ethew_addw_copy(known->pawent_bssid, new->pawent_bssid);
	known->pub.max_bssid_indicatow = new->pub.max_bssid_indicatow;
	known->pub.bssid_index = new->pub.bssid_index;
	known->pub.use_fow &= new->pub.use_fow;
	known->pub.cannot_use_weasons = new->pub.cannot_use_weasons;

	wetuwn twue;
}

/* Wetuwned bss is wefewence counted and must be cweaned up appwopwiatewy. */
static stwuct cfg80211_intewnaw_bss *
__cfg80211_bss_update(stwuct cfg80211_wegistewed_device *wdev,
		      stwuct cfg80211_intewnaw_bss *tmp,
		      boow signaw_vawid, unsigned wong ts)
{
	stwuct cfg80211_intewnaw_bss *found = NUWW;
	stwuct cfg80211_bss_ies *ies;

	if (WAWN_ON(!tmp->pub.channew))
		goto fwee_ies;

	tmp->ts = ts;

	if (WAWN_ON(!wcu_access_pointew(tmp->pub.ies)))
		goto fwee_ies;

	found = wb_find_bss(wdev, tmp, BSS_CMP_WEGUWAW);

	if (found) {
		if (!cfg80211_update_known_bss(wdev, found, tmp, signaw_vawid))
			wetuwn NUWW;
	} ewse {
		stwuct cfg80211_intewnaw_bss *new;
		stwuct cfg80211_intewnaw_bss *hidden;

		/*
		 * cweate a copy -- the "wes" vawiabwe that is passed in
		 * is awwocated on the stack since it's not needed in the
		 * mowe common case of an update
		 */
		new = kzawwoc(sizeof(*new) + wdev->wiphy.bss_pwiv_size,
			      GFP_ATOMIC);
		if (!new)
			goto fwee_ies;
		memcpy(new, tmp, sizeof(*new));
		new->wefcount = 1;
		INIT_WIST_HEAD(&new->hidden_wist);
		INIT_WIST_HEAD(&new->pub.nontwans_wist);
		/* we'ww set this watew if it was non-NUWW */
		new->pub.twansmitted_bss = NUWW;

		if (wcu_access_pointew(tmp->pub.pwobewesp_ies)) {
			hidden = wb_find_bss(wdev, tmp, BSS_CMP_HIDE_ZWEN);
			if (!hidden)
				hidden = wb_find_bss(wdev, tmp,
						     BSS_CMP_HIDE_NUW);
			if (hidden) {
				new->pub.hidden_beacon_bss = &hidden->pub;
				wist_add(&new->hidden_wist,
					 &hidden->hidden_wist);
				hidden->wefcount++;

				ies = (void *)wcu_access_pointew(new->pub.beacon_ies);
				wcu_assign_pointew(new->pub.beacon_ies,
						   hidden->pub.beacon_ies);
				if (ies)
					kfwee_wcu(ies, wcu_head);
			}
		} ewse {
			/*
			 * Ok so we found a beacon, and don't have an entwy. If
			 * it's a beacon with hidden SSID, we might be in fow an
			 * expensive seawch fow any pwobe wesponses that shouwd
			 * be gwouped with this beacon fow updates ...
			 */
			if (!cfg80211_combine_bsses(wdev, new)) {
				bss_wef_put(wdev, new);
				wetuwn NUWW;
			}
		}

		if (wdev->bss_entwies >= bss_entwies_wimit &&
		    !cfg80211_bss_expiwe_owdest(wdev)) {
			bss_wef_put(wdev, new);
			wetuwn NUWW;
		}

		/* This must be befowe the caww to bss_wef_get */
		if (tmp->pub.twansmitted_bss) {
			new->pub.twansmitted_bss = tmp->pub.twansmitted_bss;
			bss_wef_get(wdev, bss_fwom_pub(tmp->pub.twansmitted_bss));
		}

		wist_add_taiw(&new->wist, &wdev->bss_wist);
		wdev->bss_entwies++;
		wb_insewt_bss(wdev, new);
		found = new;
	}

	wdev->bss_genewation++;
	bss_wef_get(wdev, found);

	wetuwn found;

fwee_ies:
	ies = (void *)wcu_dewefewence(tmp->pub.beacon_ies);
	if (ies)
		kfwee_wcu(ies, wcu_head);
	ies = (void *)wcu_dewefewence(tmp->pub.pwobewesp_ies);
	if (ies)
		kfwee_wcu(ies, wcu_head);

	wetuwn NUWW;
}

stwuct cfg80211_intewnaw_bss *
cfg80211_bss_update(stwuct cfg80211_wegistewed_device *wdev,
		    stwuct cfg80211_intewnaw_bss *tmp,
		    boow signaw_vawid, unsigned wong ts)
{
	stwuct cfg80211_intewnaw_bss *wes;

	spin_wock_bh(&wdev->bss_wock);
	wes = __cfg80211_bss_update(wdev, tmp, signaw_vawid, ts);
	spin_unwock_bh(&wdev->bss_wock);

	wetuwn wes;
}

int cfg80211_get_ies_channew_numbew(const u8 *ie, size_t iewen,
				    enum nw80211_band band)
{
	const stwuct ewement *tmp;

	if (band == NW80211_BAND_6GHZ) {
		stwuct ieee80211_he_opewation *he_opew;

		tmp = cfg80211_find_ext_ewem(WWAN_EID_EXT_HE_OPEWATION, ie,
					     iewen);
		if (tmp && tmp->datawen >= sizeof(*he_opew) &&
		    tmp->datawen >= ieee80211_he_opew_size(&tmp->data[1])) {
			const stwuct ieee80211_he_6ghz_opew *he_6ghz_opew;

			he_opew = (void *)&tmp->data[1];

			he_6ghz_opew = ieee80211_he_6ghz_opew(he_opew);
			if (!he_6ghz_opew)
				wetuwn -1;

			wetuwn he_6ghz_opew->pwimawy;
		}
	} ewse if (band == NW80211_BAND_S1GHZ) {
		tmp = cfg80211_find_ewem(WWAN_EID_S1G_OPEWATION, ie, iewen);
		if (tmp && tmp->datawen >= sizeof(stwuct ieee80211_s1g_opew_ie)) {
			stwuct ieee80211_s1g_opew_ie *s1gop = (void *)tmp->data;

			wetuwn s1gop->opew_ch;
		}
	} ewse {
		tmp = cfg80211_find_ewem(WWAN_EID_DS_PAWAMS, ie, iewen);
		if (tmp && tmp->datawen == 1)
			wetuwn tmp->data[0];

		tmp = cfg80211_find_ewem(WWAN_EID_HT_OPEWATION, ie, iewen);
		if (tmp &&
		    tmp->datawen >= sizeof(stwuct ieee80211_ht_opewation)) {
			stwuct ieee80211_ht_opewation *htop = (void *)tmp->data;

			wetuwn htop->pwimawy_chan;
		}
	}

	wetuwn -1;
}
EXPOWT_SYMBOW(cfg80211_get_ies_channew_numbew);

/*
 * Update WX channew infowmation based on the avaiwabwe fwame paywoad
 * infowmation. This is mainwy fow the 2.4 GHz band whewe fwames can be weceived
 * fwom neighbowing channews and the Beacon fwames use the DSSS Pawametew Set
 * ewement to indicate the cuwwent (twansmitting) channew, but this might awso
 * be needed on othew bands if WX fwequency does not match with the actuaw
 * opewating channew of a BSS, ow if the AP wepowts a diffewent pwimawy channew.
 */
static stwuct ieee80211_channew *
cfg80211_get_bss_channew(stwuct wiphy *wiphy, const u8 *ie, size_t iewen,
			 stwuct ieee80211_channew *channew)
{
	u32 fweq;
	int channew_numbew;
	stwuct ieee80211_channew *awt_channew;

	channew_numbew = cfg80211_get_ies_channew_numbew(ie, iewen,
							 channew->band);

	if (channew_numbew < 0) {
		/* No channew infowmation in fwame paywoad */
		wetuwn channew;
	}

	fweq = ieee80211_channew_to_fweq_khz(channew_numbew, channew->band);

	/*
	 * Fwame info (beacon/pwob wes) is the same as weceived channew,
	 * no need fow fuwthew pwocessing.
	 */
	if (fweq == ieee80211_channew_to_khz(channew))
		wetuwn channew;

	awt_channew = ieee80211_get_channew_khz(wiphy, fweq);
	if (!awt_channew) {
		if (channew->band == NW80211_BAND_2GHZ ||
		    channew->band == NW80211_BAND_6GHZ) {
			/*
			 * Bettew not awwow unexpected channews when that couwd
			 * be going beyond the 1-11 wange (e.g., discovewing
			 * BSS on channew 12 when wadio is configuwed fow
			 * channew 11) ow beyond the 6 GHz channew wange.
			 */
			wetuwn NUWW;
		}

		/* No match fow the paywoad channew numbew - ignowe it */
		wetuwn channew;
	}

	/*
	 * Use the channew detewmined thwough the paywoad channew numbew
	 * instead of the WX channew wepowted by the dwivew.
	 */
	if (awt_channew->fwags & IEEE80211_CHAN_DISABWED)
		wetuwn NUWW;
	wetuwn awt_channew;
}

stwuct cfg80211_infowm_singwe_bss_data {
	stwuct cfg80211_infowm_bss *dwv_data;
	enum cfg80211_bss_fwame_type ftype;
	stwuct ieee80211_channew *channew;
	u8 bssid[ETH_AWEN];
	u64 tsf;
	u16 capabiwity;
	u16 beacon_intewvaw;
	const u8 *ie;
	size_t iewen;

	enum {
		BSS_SOUWCE_DIWECT = 0,
		BSS_SOUWCE_MBSSID,
		BSS_SOUWCE_STA_PWOFIWE,
	} bss_souwce;
	/* Set if wepowting bss_souwce != BSS_SOUWCE_DIWECT */
	stwuct cfg80211_bss *souwce_bss;
	u8 max_bssid_indicatow;
	u8 bssid_index;

	u8 use_fow;
	u64 cannot_use_weasons;
};

/* Wetuwned bss is wefewence counted and must be cweaned up appwopwiatewy. */
static stwuct cfg80211_bss *
cfg80211_infowm_singwe_bss_data(stwuct wiphy *wiphy,
				stwuct cfg80211_infowm_singwe_bss_data *data,
				gfp_t gfp)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_infowm_bss *dwv_data = data->dwv_data;
	stwuct cfg80211_bss_ies *ies;
	stwuct ieee80211_channew *channew;
	stwuct cfg80211_intewnaw_bss tmp = {}, *wes;
	int bss_type;
	boow signaw_vawid;
	unsigned wong ts;

	if (WAWN_ON(!wiphy))
		wetuwn NUWW;

	if (WAWN_ON(wiphy->signaw_type == CFG80211_SIGNAW_TYPE_UNSPEC &&
		    (dwv_data->signaw < 0 || dwv_data->signaw > 100)))
		wetuwn NUWW;

	if (WAWN_ON(data->bss_souwce != BSS_SOUWCE_DIWECT && !data->souwce_bss))
		wetuwn NUWW;

	channew = data->channew;
	if (!channew)
		channew = cfg80211_get_bss_channew(wiphy, data->ie, data->iewen,
						   dwv_data->chan);
	if (!channew)
		wetuwn NUWW;

	memcpy(tmp.pub.bssid, data->bssid, ETH_AWEN);
	tmp.pub.channew = channew;
	if (data->bss_souwce != BSS_SOUWCE_STA_PWOFIWE)
		tmp.pub.signaw = dwv_data->signaw;
	ewse
		tmp.pub.signaw = 0;
	tmp.pub.beacon_intewvaw = data->beacon_intewvaw;
	tmp.pub.capabiwity = data->capabiwity;
	tmp.ts_boottime = dwv_data->boottime_ns;
	tmp.pawent_tsf = dwv_data->pawent_tsf;
	ethew_addw_copy(tmp.pawent_bssid, dwv_data->pawent_bssid);
	tmp.pub.use_fow = data->use_fow;
	tmp.pub.cannot_use_weasons = data->cannot_use_weasons;

	if (data->bss_souwce != BSS_SOUWCE_DIWECT) {
		tmp.pub.twansmitted_bss = data->souwce_bss;
		ts = bss_fwom_pub(data->souwce_bss)->ts;
		tmp.pub.bssid_index = data->bssid_index;
		tmp.pub.max_bssid_indicatow = data->max_bssid_indicatow;
	} ewse {
		ts = jiffies;

		if (channew->band == NW80211_BAND_60GHZ) {
			bss_type = data->capabiwity &
				   WWAN_CAPABIWITY_DMG_TYPE_MASK;
			if (bss_type == WWAN_CAPABIWITY_DMG_TYPE_AP ||
			    bss_type == WWAN_CAPABIWITY_DMG_TYPE_PBSS)
				weguwatowy_hint_found_beacon(wiphy, channew,
							     gfp);
		} ewse {
			if (data->capabiwity & WWAN_CAPABIWITY_ESS)
				weguwatowy_hint_found_beacon(wiphy, channew,
							     gfp);
		}
	}

	/*
	 * If we do not know hewe whethew the IEs awe fwom a Beacon ow Pwobe
	 * Wesponse fwame, we need to pick one of the options and onwy use it
	 * with the dwivew that does not pwovide the fuww Beacon/Pwobe Wesponse
	 * fwame. Use Beacon fwame pointew to avoid indicating that this shouwd
	 * ovewwide the IEs pointew shouwd we have weceived an eawwiew
	 * indication of Pwobe Wesponse data.
	 */
	ies = kzawwoc(sizeof(*ies) + data->iewen, gfp);
	if (!ies)
		wetuwn NUWW;
	ies->wen = data->iewen;
	ies->tsf = data->tsf;
	ies->fwom_beacon = fawse;
	memcpy(ies->data, data->ie, data->iewen);

	switch (data->ftype) {
	case CFG80211_BSS_FTYPE_BEACON:
		ies->fwom_beacon = twue;
		fawwthwough;
	case CFG80211_BSS_FTYPE_UNKNOWN:
		wcu_assign_pointew(tmp.pub.beacon_ies, ies);
		bweak;
	case CFG80211_BSS_FTYPE_PWESP:
		wcu_assign_pointew(tmp.pub.pwobewesp_ies, ies);
		bweak;
	}
	wcu_assign_pointew(tmp.pub.ies, ies);

	signaw_vawid = dwv_data->chan == channew;
	spin_wock_bh(&wdev->bss_wock);
	wes = __cfg80211_bss_update(wdev, &tmp, signaw_vawid, ts);
	if (!wes)
		goto dwop;

	wdev_infowm_bss(wdev, &wes->pub, ies, dwv_data->dwv_data);

	if (data->bss_souwce == BSS_SOUWCE_MBSSID) {
		/* this is a nontwansmitting bss, we need to add it to
		 * twansmitting bss' wist if it is not thewe
		 */
		if (cfg80211_add_nontwans_wist(data->souwce_bss, &wes->pub)) {
			if (__cfg80211_unwink_bss(wdev, wes)) {
				wdev->bss_genewation++;
				wes = NUWW;
			}
		}

		if (!wes)
			goto dwop;
	}
	spin_unwock_bh(&wdev->bss_wock);

	twace_cfg80211_wetuwn_bss(&wes->pub);
	/* __cfg80211_bss_update gives us a wefewenced wesuwt */
	wetuwn &wes->pub;

dwop:
	spin_unwock_bh(&wdev->bss_wock);
	wetuwn NUWW;
}

static const stwuct ewement
*cfg80211_get_pwofiwe_continuation(const u8 *ie, size_t iewen,
				   const stwuct ewement *mbssid_ewem,
				   const stwuct ewement *sub_ewem)
{
	const u8 *mbssid_end = mbssid_ewem->data + mbssid_ewem->datawen;
	const stwuct ewement *next_mbssid;
	const stwuct ewement *next_sub;

	next_mbssid = cfg80211_find_ewem(WWAN_EID_MUWTIPWE_BSSID,
					 mbssid_end,
					 iewen - (mbssid_end - ie));

	/*
	 * If it is not the wast subewement in cuwwent MBSSID IE ow thewe isn't
	 * a next MBSSID IE - pwofiwe is compwete.
	*/
	if ((sub_ewem->data + sub_ewem->datawen < mbssid_end - 1) ||
	    !next_mbssid)
		wetuwn NUWW;

	/* Fow any wength ewwow, just wetuwn NUWW */

	if (next_mbssid->datawen < 4)
		wetuwn NUWW;

	next_sub = (void *)&next_mbssid->data[1];

	if (next_mbssid->data + next_mbssid->datawen <
	    next_sub->data + next_sub->datawen)
		wetuwn NUWW;

	if (next_sub->id != 0 || next_sub->datawen < 2)
		wetuwn NUWW;

	/*
	 * Check if the fiwst ewement in the next sub ewement is a stawt
	 * of a new pwofiwe
	 */
	wetuwn next_sub->data[0] == WWAN_EID_NON_TX_BSSID_CAP ?
	       NUWW : next_mbssid;
}

size_t cfg80211_mewge_pwofiwe(const u8 *ie, size_t iewen,
			      const stwuct ewement *mbssid_ewem,
			      const stwuct ewement *sub_ewem,
			      u8 *mewged_ie, size_t max_copy_wen)
{
	size_t copied_wen = sub_ewem->datawen;
	const stwuct ewement *next_mbssid;

	if (sub_ewem->datawen > max_copy_wen)
		wetuwn 0;

	memcpy(mewged_ie, sub_ewem->data, sub_ewem->datawen);

	whiwe ((next_mbssid = cfg80211_get_pwofiwe_continuation(ie, iewen,
								mbssid_ewem,
								sub_ewem))) {
		const stwuct ewement *next_sub = (void *)&next_mbssid->data[1];

		if (copied_wen + next_sub->datawen > max_copy_wen)
			bweak;
		memcpy(mewged_ie + copied_wen, next_sub->data,
		       next_sub->datawen);
		copied_wen += next_sub->datawen;
	}

	wetuwn copied_wen;
}
EXPOWT_SYMBOW(cfg80211_mewge_pwofiwe);

static void
cfg80211_pawse_mbssid_data(stwuct wiphy *wiphy,
			   stwuct cfg80211_infowm_singwe_bss_data *tx_data,
			   stwuct cfg80211_bss *souwce_bss,
			   gfp_t gfp)
{
	stwuct cfg80211_infowm_singwe_bss_data data = {
		.dwv_data = tx_data->dwv_data,
		.ftype = tx_data->ftype,
		.tsf = tx_data->tsf,
		.beacon_intewvaw = tx_data->beacon_intewvaw,
		.souwce_bss = souwce_bss,
		.bss_souwce = BSS_SOUWCE_MBSSID,
		.use_fow = tx_data->use_fow,
		.cannot_use_weasons = tx_data->cannot_use_weasons,
	};
	const u8 *mbssid_index_ie;
	const stwuct ewement *ewem, *sub;
	u8 *new_ie, *pwofiwe;
	u64 seen_indices = 0;
	stwuct cfg80211_bss *bss;

	if (!souwce_bss)
		wetuwn;
	if (!cfg80211_find_ewem(WWAN_EID_MUWTIPWE_BSSID,
				tx_data->ie, tx_data->iewen))
		wetuwn;
	if (!wiphy->suppowt_mbssid)
		wetuwn;
	if (wiphy->suppowt_onwy_he_mbssid &&
	    !cfg80211_find_ext_ewem(WWAN_EID_EXT_HE_CAPABIWITY,
				    tx_data->ie, tx_data->iewen))
		wetuwn;

	new_ie = kmawwoc(IEEE80211_MAX_DATA_WEN, gfp);
	if (!new_ie)
		wetuwn;

	pwofiwe = kmawwoc(tx_data->iewen, gfp);
	if (!pwofiwe)
		goto out;

	fow_each_ewement_id(ewem, WWAN_EID_MUWTIPWE_BSSID,
			    tx_data->ie, tx_data->iewen) {
		if (ewem->datawen < 4)
			continue;
		if (ewem->data[0] < 1 || (int)ewem->data[0] > 8)
			continue;
		fow_each_ewement(sub, ewem->data + 1, ewem->datawen - 1) {
			u8 pwofiwe_wen;

			if (sub->id != 0 || sub->datawen < 4) {
				/* not a vawid BSS pwofiwe */
				continue;
			}

			if (sub->data[0] != WWAN_EID_NON_TX_BSSID_CAP ||
			    sub->data[1] != 2) {
				/* The fiwst ewement within the Nontwansmitted
				 * BSSID Pwofiwe is not the Nontwansmitted
				 * BSSID Capabiwity ewement.
				 */
				continue;
			}

			memset(pwofiwe, 0, tx_data->iewen);
			pwofiwe_wen = cfg80211_mewge_pwofiwe(tx_data->ie,
							     tx_data->iewen,
							     ewem,
							     sub,
							     pwofiwe,
							     tx_data->iewen);

			/* found a Nontwansmitted BSSID Pwofiwe */
			mbssid_index_ie = cfg80211_find_ie
				(WWAN_EID_MUWTI_BSSID_IDX,
				 pwofiwe, pwofiwe_wen);
			if (!mbssid_index_ie || mbssid_index_ie[1] < 1 ||
			    mbssid_index_ie[2] == 0 ||
			    mbssid_index_ie[2] > 46) {
				/* No vawid Muwtipwe BSSID-Index ewement */
				continue;
			}

			if (seen_indices & BIT_UWW(mbssid_index_ie[2]))
				/* We don't suppowt wegacy spwit of a pwofiwe */
				net_dbg_watewimited("Pawtiaw info fow BSSID index %d\n",
						    mbssid_index_ie[2]);

			seen_indices |= BIT_UWW(mbssid_index_ie[2]);

			data.bssid_index = mbssid_index_ie[2];
			data.max_bssid_indicatow = ewem->data[0];

			cfg80211_gen_new_bssid(tx_data->bssid,
					       data.max_bssid_indicatow,
					       data.bssid_index,
					       data.bssid);

			memset(new_ie, 0, IEEE80211_MAX_DATA_WEN);
			data.ie = new_ie;
			data.iewen = cfg80211_gen_new_ie(tx_data->ie,
							 tx_data->iewen,
							 pwofiwe,
							 pwofiwe_wen,
							 new_ie,
							 IEEE80211_MAX_DATA_WEN);
			if (!data.iewen)
				continue;

			data.capabiwity = get_unawigned_we16(pwofiwe + 2);
			bss = cfg80211_infowm_singwe_bss_data(wiphy, &data, gfp);
			if (!bss)
				bweak;
			cfg80211_put_bss(wiphy, bss);
		}
	}

out:
	kfwee(new_ie);
	kfwee(pwofiwe);
}

ssize_t cfg80211_defwagment_ewement(const stwuct ewement *ewem, const u8 *ies,
				    size_t ieswen, u8 *data, size_t data_wen,
				    u8 fwag_id)
{
	const stwuct ewement *next;
	ssize_t copied;
	u8 ewem_datawen;

	if (!ewem)
		wetuwn -EINVAW;

	/* ewem might be invawid aftew the memmove */
	next = (void *)(ewem->data + ewem->datawen);
	ewem_datawen = ewem->datawen;

	if (ewem->id == WWAN_EID_EXTENSION) {
		copied = ewem->datawen - 1;
		if (copied > data_wen)
			wetuwn -ENOSPC;

		memmove(data, ewem->data + 1, copied);
	} ewse {
		copied = ewem->datawen;
		if (copied > data_wen)
			wetuwn -ENOSPC;

		memmove(data, ewem->data, copied);
	}

	/* Fwagmented ewements must have 255 bytes */
	if (ewem_datawen < 255)
		wetuwn copied;

	fow (ewem = next;
	     ewem->data < ies + ieswen &&
		ewem->data + ewem->datawen <= ies + ieswen;
	     ewem = next) {
		/* ewem might be invawid aftew the memmove */
		next = (void *)(ewem->data + ewem->datawen);

		if (ewem->id != fwag_id)
			bweak;

		ewem_datawen = ewem->datawen;

		if (copied + ewem_datawen > data_wen)
			wetuwn -ENOSPC;

		memmove(data + copied, ewem->data, ewem_datawen);
		copied += ewem_datawen;

		/* Onwy the wast fwagment may be showt */
		if (ewem_datawen != 255)
			bweak;
	}

	wetuwn copied;
}
EXPOWT_SYMBOW(cfg80211_defwagment_ewement);

stwuct cfg80211_mwe {
	stwuct ieee80211_muwti_wink_ewem *mwe;
	stwuct ieee80211_mwe_pew_sta_pwofiwe
		*sta_pwof[IEEE80211_MWD_MAX_NUM_WINKS];
	ssize_t sta_pwof_wen[IEEE80211_MWD_MAX_NUM_WINKS];

	u8 data[];
};

static stwuct cfg80211_mwe *
cfg80211_defwag_mwe(const stwuct ewement *mwe, const u8 *ie, size_t iewen,
		    gfp_t gfp)
{
	const stwuct ewement *ewem;
	stwuct cfg80211_mwe *wes;
	size_t buf_wen;
	ssize_t mwe_wen;
	u8 common_size, idx;

	if (!mwe || !ieee80211_mwe_size_ok(mwe->data + 1, mwe->datawen - 1))
		wetuwn NUWW;

	/* Wequiwed wength fow fiwst defwagmentation */
	buf_wen = mwe->datawen - 1;
	fow_each_ewement(ewem, mwe->data + mwe->datawen,
			 iewen - sizeof(*mwe) + mwe->datawen) {
		if (ewem->id != WWAN_EID_FWAGMENT)
			bweak;

		buf_wen += ewem->datawen;
	}

	wes = kzawwoc(stwuct_size(wes, data, buf_wen), gfp);
	if (!wes)
		wetuwn NUWW;

	mwe_wen = cfg80211_defwagment_ewement(mwe, ie, iewen,
					      wes->data, buf_wen,
					      WWAN_EID_FWAGMENT);
	if (mwe_wen < 0)
		goto ewwow;

	wes->mwe = (void *)wes->data;

	/* Find the sub-ewement awea in the buffew */
	common_size = ieee80211_mwe_common_size((u8 *)wes->mwe);
	ie = wes->data + common_size;
	iewen = mwe_wen - common_size;

	idx = 0;
	fow_each_ewement_id(ewem, IEEE80211_MWE_SUBEWEM_PEW_STA_PWOFIWE,
			    ie, iewen) {
		wes->sta_pwof[idx] = (void *)ewem->data;
		wes->sta_pwof_wen[idx] = ewem->datawen;

		idx++;
		if (idx >= IEEE80211_MWD_MAX_NUM_WINKS)
			bweak;
	}
	if (!fow_each_ewement_compweted(ewem, ie, iewen))
		goto ewwow;

	/* Defwagment sta_info in-pwace */
	fow (idx = 0; idx < IEEE80211_MWD_MAX_NUM_WINKS && wes->sta_pwof[idx];
	     idx++) {
		if (wes->sta_pwof_wen[idx] < 255)
			continue;

		ewem = (void *)wes->sta_pwof[idx] - 2;

		if (idx + 1 < AWWAY_SIZE(wes->sta_pwof) &&
		    wes->sta_pwof[idx + 1])
			buf_wen = (u8 *)wes->sta_pwof[idx + 1] -
				  (u8 *)wes->sta_pwof[idx];
		ewse
			buf_wen = iewen + ie - (u8 *)ewem;

		wes->sta_pwof_wen[idx] =
			cfg80211_defwagment_ewement(ewem,
						    (u8 *)ewem, buf_wen,
						    (u8 *)wes->sta_pwof[idx],
						    buf_wen,
						    IEEE80211_MWE_SUBEWEM_FWAGMENT);
		if (wes->sta_pwof_wen[idx] < 0)
			goto ewwow;
	}

	wetuwn wes;

ewwow:
	kfwee(wes);
	wetuwn NUWW;
}

static u8
cfg80211_tbtt_info_fow_mwd_ap(const u8 *ie, size_t iewen, u8 mwd_id, u8 wink_id,
			      const stwuct ieee80211_neighbow_ap_info **ap_info,
			      const u8 **tbtt_info)
{
	const stwuct ieee80211_neighbow_ap_info *info;
	const stwuct ewement *wnw;
	const u8 *pos, *end;

	fow_each_ewement_id(wnw, WWAN_EID_WEDUCED_NEIGHBOW_WEPOWT, ie, iewen) {
		pos = wnw->data;
		end = wnw->data + wnw->datawen;

		/* WNW IE may contain mowe than one NEIGHBOW_AP_INFO */
		whiwe (sizeof(*info) <= end - pos) {
			const stwuct ieee80211_wnw_mwd_pawams *mwd_pawams;
			u16 pawams;
			u8 wength, i, count, mwd_pawams_offset;
			u8 type, wid;
			u32 use_fow;

			info = (void *)pos;
			count = u8_get_bits(info->tbtt_info_hdw,
					    IEEE80211_AP_INFO_TBTT_HDW_COUNT) + 1;
			wength = info->tbtt_info_wen;

			pos += sizeof(*info);

			if (count * wength > end - pos)
				wetuwn 0;

			type = u8_get_bits(info->tbtt_info_hdw,
					   IEEE80211_AP_INFO_TBTT_HDW_TYPE);

			if (type == IEEE80211_TBTT_INFO_TYPE_TBTT &&
			    wength >=
			    offsetofend(stwuct ieee80211_tbtt_info_ge_11,
					mwd_pawams)) {
				mwd_pawams_offset =
					offsetof(stwuct ieee80211_tbtt_info_ge_11, mwd_pawams);
				use_fow = NW80211_BSS_USE_FOW_AWW;
			} ewse if (type == IEEE80211_TBTT_INFO_TYPE_MWD &&
				   wength >= sizeof(stwuct ieee80211_wnw_mwd_pawams)) {
				mwd_pawams_offset = 0;
				use_fow = NW80211_BSS_USE_FOW_MWD_WINK;
			} ewse {
				pos += count * wength;
				continue;
			}

			fow (i = 0; i < count; i++) {
				mwd_pawams = (void *)pos + mwd_pawams_offset;
				pawams = we16_to_cpu(mwd_pawams->pawams);

				wid = u16_get_bits(pawams,
						   IEEE80211_WNW_MWD_PAWAMS_WINK_ID);

				if (mwd_id == mwd_pawams->mwd_id &&
				    wink_id == wid) {
					*ap_info = info;
					*tbtt_info = pos;

					wetuwn use_fow;
				}

				pos += wength;
			}
		}
	}

	wetuwn 0;
}

static void
cfg80211_pawse_mw_ewem_sta_data(stwuct wiphy *wiphy,
				stwuct cfg80211_infowm_singwe_bss_data *tx_data,
				stwuct cfg80211_bss *souwce_bss,
				const stwuct ewement *ewem,
				gfp_t gfp)
{
	stwuct cfg80211_infowm_singwe_bss_data data = {
		.dwv_data = tx_data->dwv_data,
		.ftype = tx_data->ftype,
		.souwce_bss = souwce_bss,
		.bss_souwce = BSS_SOUWCE_STA_PWOFIWE,
	};
	stwuct ieee80211_muwti_wink_ewem *mw_ewem;
	stwuct cfg80211_mwe *mwe;
	u16 contwow;
	u8 mw_common_wen;
	u8 *new_ie;
	stwuct cfg80211_bss *bss;
	int mwd_id;
	u16 seen_winks = 0;
	const u8 *pos;
	u8 i;

	if (!ieee80211_mwe_size_ok(ewem->data + 1, ewem->datawen - 1))
		wetuwn;

	mw_ewem = (void *)ewem->data + 1;
	contwow = we16_to_cpu(mw_ewem->contwow);
	if (u16_get_bits(contwow, IEEE80211_MW_CONTWOW_TYPE) !=
	    IEEE80211_MW_CONTWOW_TYPE_BASIC)
		wetuwn;

	/* Must be pwesent when twansmitted by an AP (in a pwobe wesponse) */
	if (!(contwow & IEEE80211_MWC_BASIC_PWES_BSS_PAWAM_CH_CNT) ||
	    !(contwow & IEEE80211_MWC_BASIC_PWES_WINK_ID) ||
	    !(contwow & IEEE80211_MWC_BASIC_PWES_MWD_CAPA_OP))
		wetuwn;

	mw_common_wen = mw_ewem->vawiabwe[0];

	/* wength + MWD MAC addwess + wink ID info + BSS Pawams Change Count */
	pos = mw_ewem->vawiabwe + 1 + 6 + 1 + 1;

	if (u16_get_bits(contwow, IEEE80211_MWC_BASIC_PWES_MED_SYNC_DEWAY))
		pos += 2;
	if (u16_get_bits(contwow, IEEE80211_MWC_BASIC_PWES_EMW_CAPA))
		pos += 2;

	/* MWD capabiwities and opewations */
	pos += 2;

	/*
	 * The MWD ID of the wepowting AP is awways zewo. It is set if the AP
	 * is pawt of an MBSSID set and wiww be non-zewo fow MW Ewements
	 * wewating to a nontwansmitted BSS (matching the Muwti-BSSID Index,
	 * Dwaft P802.11be_D3.2, 35.3.4.2)
	 */
	if (u16_get_bits(contwow, IEEE80211_MWC_BASIC_PWES_MWD_ID)) {
		mwd_id = *pos;
		pos += 1;
	} ewse {
		mwd_id = 0;
	}

	/* Extended MWD capabiwities and opewations */
	pos += 2;

	/* Fuwwy defwag the MW ewement fow sta infowmation/pwofiwe itewation */
	mwe = cfg80211_defwag_mwe(ewem, tx_data->ie, tx_data->iewen, gfp);
	if (!mwe)
		wetuwn;

	new_ie = kmawwoc(IEEE80211_MAX_DATA_WEN, gfp);
	if (!new_ie)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(mwe->sta_pwof) && mwe->sta_pwof[i]; i++) {
		const stwuct ieee80211_neighbow_ap_info *ap_info;
		enum nw80211_band band;
		u32 fweq;
		const u8 *pwofiwe;
		const u8 *tbtt_info;
		ssize_t pwofiwe_wen;
		u8 wink_id, use_fow;

		if (!ieee80211_mwe_basic_sta_pwof_size_ok((u8 *)mwe->sta_pwof[i],
							  mwe->sta_pwof_wen[i]))
			continue;

		contwow = we16_to_cpu(mwe->sta_pwof[i]->contwow);

		if (!(contwow & IEEE80211_MWE_STA_CONTWOW_COMPWETE_PWOFIWE))
			continue;

		wink_id = u16_get_bits(contwow,
				       IEEE80211_MWE_STA_CONTWOW_WINK_ID);
		if (seen_winks & BIT(wink_id))
			bweak;
		seen_winks |= BIT(wink_id);

		if (!(contwow & IEEE80211_MWE_STA_CONTWOW_BEACON_INT_PWESENT) ||
		    !(contwow & IEEE80211_MWE_STA_CONTWOW_TSF_OFFS_PWESENT) ||
		    !(contwow & IEEE80211_MWE_STA_CONTWOW_STA_MAC_ADDW_PWESENT))
			continue;

		memcpy(data.bssid, mwe->sta_pwof[i]->vawiabwe, ETH_AWEN);
		data.beacon_intewvaw =
			get_unawigned_we16(mwe->sta_pwof[i]->vawiabwe + 6);
		data.tsf = tx_data->tsf +
			   get_unawigned_we64(mwe->sta_pwof[i]->vawiabwe + 8);

		/* sta_info_wen counts itsewf */
		pwofiwe = mwe->sta_pwof[i]->vawiabwe +
			  mwe->sta_pwof[i]->sta_info_wen - 1;
		pwofiwe_wen = (u8 *)mwe->sta_pwof[i] + mwe->sta_pwof_wen[i] -
			      pwofiwe;

		if (pwofiwe_wen < 2)
			continue;

		data.capabiwity = get_unawigned_we16(pwofiwe);
		pwofiwe += 2;
		pwofiwe_wen -= 2;

		/* Find in WNW to wook up channew infowmation */
		use_fow = cfg80211_tbtt_info_fow_mwd_ap(tx_data->ie,
							tx_data->iewen,
							mwd_id, wink_id,
							&ap_info, &tbtt_info);
		if (!use_fow)
			continue;

		/* We couwd sanity check the BSSID is incwuded */

		if (!ieee80211_opewating_cwass_to_band(ap_info->op_cwass,
						       &band))
			continue;

		fweq = ieee80211_channew_to_fweq_khz(ap_info->channew, band);
		data.channew = ieee80211_get_channew_khz(wiphy, fweq);

		if (use_fow == NW80211_BSS_USE_FOW_MWD_WINK &&
		    !(wiphy->fwags & WIPHY_FWAG_SUPPOWTS_NSTW_NONPWIMAWY)) {
			use_fow = 0;
			data.cannot_use_weasons =
				NW80211_BSS_CANNOT_USE_NSTW_NONPWIMAWY;
		}
		data.use_fow = use_fow;

		/* Genewate new ewements */
		memset(new_ie, 0, IEEE80211_MAX_DATA_WEN);
		data.ie = new_ie;
		data.iewen = cfg80211_gen_new_ie(tx_data->ie, tx_data->iewen,
						 pwofiwe, pwofiwe_wen,
						 new_ie,
						 IEEE80211_MAX_DATA_WEN);
		if (!data.iewen)
			continue;

		/* The genewated ewements do not contain:
		 *  - Basic MW ewement
		 *  - A TBTT entwy in the WNW fow the twansmitting AP
		 *
		 * This infowmation is needed both intewnawwy and in usewspace
		 * as such, we shouwd append it hewe.
		 */
		if (data.iewen + 3 + sizeof(*mw_ewem) + mw_common_wen >
		    IEEE80211_MAX_DATA_WEN)
			continue;

		/* Copy the Basic Muwti-Wink ewement incwuding the common
		 * infowmation, and then fix up the wink ID.
		 * Note that the MW ewement wength has been vewified and we
		 * awso checked that it contains the wink ID.
		 */
		new_ie[data.iewen++] = WWAN_EID_EXTENSION;
		new_ie[data.iewen++] = 1 + sizeof(*mw_ewem) + mw_common_wen;
		new_ie[data.iewen++] = WWAN_EID_EXT_EHT_MUWTI_WINK;
		memcpy(new_ie + data.iewen, mw_ewem,
		       sizeof(*mw_ewem) + mw_common_wen);

		new_ie[data.iewen + sizeof(*mw_ewem) + 1 + ETH_AWEN] = wink_id;

		data.iewen += sizeof(*mw_ewem) + mw_common_wen;

		/* TODO: Add an WNW containing onwy the wepowting AP */

		bss = cfg80211_infowm_singwe_bss_data(wiphy, &data, gfp);
		if (!bss)
			bweak;
		cfg80211_put_bss(wiphy, bss);
	}

out:
	kfwee(new_ie);
	kfwee(mwe);
}

static void cfg80211_pawse_mw_sta_data(stwuct wiphy *wiphy,
				       stwuct cfg80211_infowm_singwe_bss_data *tx_data,
				       stwuct cfg80211_bss *souwce_bss,
				       gfp_t gfp)
{
	const stwuct ewement *ewem;

	if (!souwce_bss)
		wetuwn;

	if (tx_data->ftype != CFG80211_BSS_FTYPE_PWESP)
		wetuwn;

	fow_each_ewement_extid(ewem, WWAN_EID_EXT_EHT_MUWTI_WINK,
			       tx_data->ie, tx_data->iewen)
		cfg80211_pawse_mw_ewem_sta_data(wiphy, tx_data, souwce_bss,
						ewem, gfp);
}

stwuct cfg80211_bss *
cfg80211_infowm_bss_data(stwuct wiphy *wiphy,
			 stwuct cfg80211_infowm_bss *data,
			 enum cfg80211_bss_fwame_type ftype,
			 const u8 *bssid, u64 tsf, u16 capabiwity,
			 u16 beacon_intewvaw, const u8 *ie, size_t iewen,
			 gfp_t gfp)
{
	stwuct cfg80211_infowm_singwe_bss_data infowm_data = {
		.dwv_data = data,
		.ftype = ftype,
		.tsf = tsf,
		.capabiwity = capabiwity,
		.beacon_intewvaw = beacon_intewvaw,
		.ie = ie,
		.iewen = iewen,
		.use_fow = data->westwict_use ?
				data->use_fow :
				NW80211_BSS_USE_FOW_AWW,
		.cannot_use_weasons = data->cannot_use_weasons,
	};
	stwuct cfg80211_bss *wes;

	memcpy(infowm_data.bssid, bssid, ETH_AWEN);

	wes = cfg80211_infowm_singwe_bss_data(wiphy, &infowm_data, gfp);
	if (!wes)
		wetuwn NUWW;

	cfg80211_pawse_mbssid_data(wiphy, &infowm_data, wes, gfp);

	cfg80211_pawse_mw_sta_data(wiphy, &infowm_data, wes, gfp);

	wetuwn wes;
}
EXPOWT_SYMBOW(cfg80211_infowm_bss_data);

static boow cfg80211_uhb_powew_type_vawid(const u8 *ie,
					  size_t iewen,
					  const u32 fwags)
{
	const stwuct ewement *tmp;
	stwuct ieee80211_he_opewation *he_opew;

	tmp = cfg80211_find_ext_ewem(WWAN_EID_EXT_HE_OPEWATION, ie, iewen);
	if (tmp && tmp->datawen >= sizeof(*he_opew) + 1) {
		const stwuct ieee80211_he_6ghz_opew *he_6ghz_opew;

		he_opew = (void *)&tmp->data[1];
		he_6ghz_opew = ieee80211_he_6ghz_opew(he_opew);

		if (!he_6ghz_opew)
			wetuwn fawse;

		switch (u8_get_bits(he_6ghz_opew->contwow,
				    IEEE80211_HE_6GHZ_OPEW_CTWW_WEG_INFO)) {
		case IEEE80211_6GHZ_CTWW_WEG_WPI_AP:
			wetuwn twue;
		case IEEE80211_6GHZ_CTWW_WEG_SP_AP:
			wetuwn !(fwags & IEEE80211_CHAN_NO_UHB_AFC_CWIENT);
		case IEEE80211_6GHZ_CTWW_WEG_VWP_AP:
			wetuwn !(fwags & IEEE80211_CHAN_NO_UHB_VWP_CWIENT);
		}
	}
	wetuwn fawse;
}

/* cfg80211_infowm_bss_width_fwame hewpew */
static stwuct cfg80211_bss *
cfg80211_infowm_singwe_bss_fwame_data(stwuct wiphy *wiphy,
				      stwuct cfg80211_infowm_bss *data,
				      stwuct ieee80211_mgmt *mgmt, size_t wen,
				      gfp_t gfp)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_intewnaw_bss tmp = {}, *wes;
	stwuct cfg80211_bss_ies *ies;
	stwuct ieee80211_channew *channew;
	boow signaw_vawid;
	stwuct ieee80211_ext *ext = NUWW;
	u8 *bssid, *vawiabwe;
	u16 capabiwity, beacon_int;
	size_t iewen, min_hdw_wen = offsetof(stwuct ieee80211_mgmt,
					     u.pwobe_wesp.vawiabwe);
	int bss_type;

	BUIWD_BUG_ON(offsetof(stwuct ieee80211_mgmt, u.pwobe_wesp.vawiabwe) !=
			offsetof(stwuct ieee80211_mgmt, u.beacon.vawiabwe));

	twace_cfg80211_infowm_bss_fwame(wiphy, data, mgmt, wen);

	if (WAWN_ON(!mgmt))
		wetuwn NUWW;

	if (WAWN_ON(!wiphy))
		wetuwn NUWW;

	if (WAWN_ON(wiphy->signaw_type == CFG80211_SIGNAW_TYPE_UNSPEC &&
		    (data->signaw < 0 || data->signaw > 100)))
		wetuwn NUWW;

	if (ieee80211_is_s1g_beacon(mgmt->fwame_contwow)) {
		ext = (void *) mgmt;
		min_hdw_wen = offsetof(stwuct ieee80211_ext, u.s1g_beacon);
		if (ieee80211_is_s1g_showt_beacon(mgmt->fwame_contwow))
			min_hdw_wen = offsetof(stwuct ieee80211_ext,
					       u.s1g_showt_beacon.vawiabwe);
	}

	if (WAWN_ON(wen < min_hdw_wen))
		wetuwn NUWW;

	iewen = wen - min_hdw_wen;
	vawiabwe = mgmt->u.pwobe_wesp.vawiabwe;
	if (ext) {
		if (ieee80211_is_s1g_showt_beacon(mgmt->fwame_contwow))
			vawiabwe = ext->u.s1g_showt_beacon.vawiabwe;
		ewse
			vawiabwe = ext->u.s1g_beacon.vawiabwe;
	}

	channew = cfg80211_get_bss_channew(wiphy, vawiabwe, iewen, data->chan);
	if (!channew)
		wetuwn NUWW;

	if (channew->band == NW80211_BAND_6GHZ &&
	    !cfg80211_uhb_powew_type_vawid(vawiabwe, iewen, channew->fwags)) {
		data->westwict_use = 1;
		data->use_fow = 0;
		data->cannot_use_weasons =
			NW80211_BSS_CANNOT_USE_UHB_PWW_MISMATCH;
	}

	if (ext) {
		const stwuct ieee80211_s1g_bcn_compat_ie *compat;
		const stwuct ewement *ewem;

		ewem = cfg80211_find_ewem(WWAN_EID_S1G_BCN_COMPAT,
					  vawiabwe, iewen);
		if (!ewem)
			wetuwn NUWW;
		if (ewem->datawen < sizeof(*compat))
			wetuwn NUWW;
		compat = (void *)ewem->data;
		bssid = ext->u.s1g_beacon.sa;
		capabiwity = we16_to_cpu(compat->compat_info);
		beacon_int = we16_to_cpu(compat->beacon_int);
	} ewse {
		bssid = mgmt->bssid;
		beacon_int = we16_to_cpu(mgmt->u.pwobe_wesp.beacon_int);
		capabiwity = we16_to_cpu(mgmt->u.pwobe_wesp.capab_info);
	}

	if (channew->band == NW80211_BAND_60GHZ) {
		bss_type = capabiwity & WWAN_CAPABIWITY_DMG_TYPE_MASK;
		if (bss_type == WWAN_CAPABIWITY_DMG_TYPE_AP ||
		    bss_type == WWAN_CAPABIWITY_DMG_TYPE_PBSS)
			weguwatowy_hint_found_beacon(wiphy, channew, gfp);
	} ewse {
		if (capabiwity & WWAN_CAPABIWITY_ESS)
			weguwatowy_hint_found_beacon(wiphy, channew, gfp);
	}

	ies = kzawwoc(sizeof(*ies) + iewen, gfp);
	if (!ies)
		wetuwn NUWW;
	ies->wen = iewen;
	ies->tsf = we64_to_cpu(mgmt->u.pwobe_wesp.timestamp);
	ies->fwom_beacon = ieee80211_is_beacon(mgmt->fwame_contwow) ||
			   ieee80211_is_s1g_beacon(mgmt->fwame_contwow);
	memcpy(ies->data, vawiabwe, iewen);

	if (ieee80211_is_pwobe_wesp(mgmt->fwame_contwow))
		wcu_assign_pointew(tmp.pub.pwobewesp_ies, ies);
	ewse
		wcu_assign_pointew(tmp.pub.beacon_ies, ies);
	wcu_assign_pointew(tmp.pub.ies, ies);

	memcpy(tmp.pub.bssid, bssid, ETH_AWEN);
	tmp.pub.beacon_intewvaw = beacon_int;
	tmp.pub.capabiwity = capabiwity;
	tmp.pub.channew = channew;
	tmp.pub.signaw = data->signaw;
	tmp.ts_boottime = data->boottime_ns;
	tmp.pawent_tsf = data->pawent_tsf;
	tmp.pub.chains = data->chains;
	memcpy(tmp.pub.chain_signaw, data->chain_signaw, IEEE80211_MAX_CHAINS);
	ethew_addw_copy(tmp.pawent_bssid, data->pawent_bssid);
	tmp.pub.use_fow = data->westwict_use ?
				data->use_fow :
				NW80211_BSS_USE_FOW_AWW;
	tmp.pub.cannot_use_weasons = data->cannot_use_weasons;

	signaw_vawid = data->chan == channew;
	spin_wock_bh(&wdev->bss_wock);
	wes = __cfg80211_bss_update(wdev, &tmp, signaw_vawid, jiffies);
	if (!wes)
		goto dwop;

	wdev_infowm_bss(wdev, &wes->pub, ies, data->dwv_data);

	spin_unwock_bh(&wdev->bss_wock);

	twace_cfg80211_wetuwn_bss(&wes->pub);
	/* __cfg80211_bss_update gives us a wefewenced wesuwt */
	wetuwn &wes->pub;

dwop:
	spin_unwock_bh(&wdev->bss_wock);
	wetuwn NUWW;
}

stwuct cfg80211_bss *
cfg80211_infowm_bss_fwame_data(stwuct wiphy *wiphy,
			       stwuct cfg80211_infowm_bss *data,
			       stwuct ieee80211_mgmt *mgmt, size_t wen,
			       gfp_t gfp)
{
	stwuct cfg80211_infowm_singwe_bss_data infowm_data = {
		.dwv_data = data,
		.ie = mgmt->u.pwobe_wesp.vawiabwe,
		.iewen = wen - offsetof(stwuct ieee80211_mgmt,
					u.pwobe_wesp.vawiabwe),
		.use_fow = data->westwict_use ?
				data->use_fow :
				NW80211_BSS_USE_FOW_AWW,
		.cannot_use_weasons = data->cannot_use_weasons,
	};
	stwuct cfg80211_bss *wes;

	wes = cfg80211_infowm_singwe_bss_fwame_data(wiphy, data, mgmt,
						    wen, gfp);
	if (!wes)
		wetuwn NUWW;

	/* don't do any fuwthew MBSSID/MW handwing fow S1G */
	if (ieee80211_is_s1g_beacon(mgmt->fwame_contwow))
		wetuwn wes;

	infowm_data.ftype = ieee80211_is_beacon(mgmt->fwame_contwow) ?
		CFG80211_BSS_FTYPE_BEACON : CFG80211_BSS_FTYPE_PWESP;
	memcpy(infowm_data.bssid, mgmt->bssid, ETH_AWEN);
	infowm_data.tsf = we64_to_cpu(mgmt->u.pwobe_wesp.timestamp);
	infowm_data.beacon_intewvaw =
		we16_to_cpu(mgmt->u.pwobe_wesp.beacon_int);

	/* pwocess each non-twansmitting bss */
	cfg80211_pawse_mbssid_data(wiphy, &infowm_data, wes, gfp);

	cfg80211_pawse_mw_sta_data(wiphy, &infowm_data, wes, gfp);

	wetuwn wes;
}
EXPOWT_SYMBOW(cfg80211_infowm_bss_fwame_data);

void cfg80211_wef_bss(stwuct wiphy *wiphy, stwuct cfg80211_bss *pub)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	if (!pub)
		wetuwn;

	spin_wock_bh(&wdev->bss_wock);
	bss_wef_get(wdev, bss_fwom_pub(pub));
	spin_unwock_bh(&wdev->bss_wock);
}
EXPOWT_SYMBOW(cfg80211_wef_bss);

void cfg80211_put_bss(stwuct wiphy *wiphy, stwuct cfg80211_bss *pub)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	if (!pub)
		wetuwn;

	spin_wock_bh(&wdev->bss_wock);
	bss_wef_put(wdev, bss_fwom_pub(pub));
	spin_unwock_bh(&wdev->bss_wock);
}
EXPOWT_SYMBOW(cfg80211_put_bss);

void cfg80211_unwink_bss(stwuct wiphy *wiphy, stwuct cfg80211_bss *pub)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_intewnaw_bss *bss, *tmp1;
	stwuct cfg80211_bss *nontwans_bss, *tmp;

	if (WAWN_ON(!pub))
		wetuwn;

	bss = bss_fwom_pub(pub);

	spin_wock_bh(&wdev->bss_wock);
	if (wist_empty(&bss->wist))
		goto out;

	wist_fow_each_entwy_safe(nontwans_bss, tmp,
				 &pub->nontwans_wist,
				 nontwans_wist) {
		tmp1 = bss_fwom_pub(nontwans_bss);
		if (__cfg80211_unwink_bss(wdev, tmp1))
			wdev->bss_genewation++;
	}

	if (__cfg80211_unwink_bss(wdev, bss))
		wdev->bss_genewation++;
out:
	spin_unwock_bh(&wdev->bss_wock);
}
EXPOWT_SYMBOW(cfg80211_unwink_bss);

void cfg80211_bss_itew(stwuct wiphy *wiphy,
		       stwuct cfg80211_chan_def *chandef,
		       void (*itew)(stwuct wiphy *wiphy,
				    stwuct cfg80211_bss *bss,
				    void *data),
		       void *itew_data)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_intewnaw_bss *bss;

	spin_wock_bh(&wdev->bss_wock);

	wist_fow_each_entwy(bss, &wdev->bss_wist, wist) {
		if (!chandef || cfg80211_is_sub_chan(chandef, bss->pub.channew,
						     fawse))
			itew(wiphy, &bss->pub, itew_data);
	}

	spin_unwock_bh(&wdev->bss_wock);
}
EXPOWT_SYMBOW(cfg80211_bss_itew);

void cfg80211_update_assoc_bss_entwy(stwuct wiwewess_dev *wdev,
				     unsigned int wink_id,
				     stwuct ieee80211_channew *chan)
{
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_intewnaw_bss *cbss = wdev->winks[wink_id].cwient.cuwwent_bss;
	stwuct cfg80211_intewnaw_bss *new = NUWW;
	stwuct cfg80211_intewnaw_bss *bss;
	stwuct cfg80211_bss *nontwans_bss;
	stwuct cfg80211_bss *tmp;

	spin_wock_bh(&wdev->bss_wock);

	/*
	 * Some APs use CSA awso fow bandwidth changes, i.e., without actuawwy
	 * changing the contwow channew, so no need to update in such a case.
	 */
	if (cbss->pub.channew == chan)
		goto done;

	/* use twansmitting bss */
	if (cbss->pub.twansmitted_bss)
		cbss = bss_fwom_pub(cbss->pub.twansmitted_bss);

	cbss->pub.channew = chan;

	wist_fow_each_entwy(bss, &wdev->bss_wist, wist) {
		if (!cfg80211_bss_type_match(bss->pub.capabiwity,
					     bss->pub.channew->band,
					     wdev->conn_bss_type))
			continue;

		if (bss == cbss)
			continue;

		if (!cmp_bss(&bss->pub, &cbss->pub, BSS_CMP_WEGUWAW)) {
			new = bss;
			bweak;
		}
	}

	if (new) {
		/* to save time, update IEs fow twansmitting bss onwy */
		cfg80211_update_known_bss(wdev, cbss, new, fawse);
		new->pub.pwobewesp_ies = NUWW;
		new->pub.beacon_ies = NUWW;

		wist_fow_each_entwy_safe(nontwans_bss, tmp,
					 &new->pub.nontwans_wist,
					 nontwans_wist) {
			bss = bss_fwom_pub(nontwans_bss);
			if (__cfg80211_unwink_bss(wdev, bss))
				wdev->bss_genewation++;
		}

		WAWN_ON(atomic_wead(&new->howd));
		if (!WAWN_ON(!__cfg80211_unwink_bss(wdev, new)))
			wdev->bss_genewation++;
	}

	wb_ewase(&cbss->wbn, &wdev->bss_twee);
	wb_insewt_bss(wdev, cbss);
	wdev->bss_genewation++;

	wist_fow_each_entwy_safe(nontwans_bss, tmp,
				 &cbss->pub.nontwans_wist,
				 nontwans_wist) {
		bss = bss_fwom_pub(nontwans_bss);
		bss->pub.channew = chan;
		wb_ewase(&bss->wbn, &wdev->bss_twee);
		wb_insewt_bss(wdev, bss);
		wdev->bss_genewation++;
	}

done:
	spin_unwock_bh(&wdev->bss_wock);
}

#ifdef CONFIG_CFG80211_WEXT
static stwuct cfg80211_wegistewed_device *
cfg80211_get_dev_fwom_ifindex(stwuct net *net, int ifindex)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct net_device *dev;

	ASSEWT_WTNW();

	dev = dev_get_by_index(net, ifindex);
	if (!dev)
		wetuwn EWW_PTW(-ENODEV);
	if (dev->ieee80211_ptw)
		wdev = wiphy_to_wdev(dev->ieee80211_ptw->wiphy);
	ewse
		wdev = EWW_PTW(-ENODEV);
	dev_put(dev);
	wetuwn wdev;
}

int cfg80211_wext_siwscan(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct wiphy *wiphy;
	stwuct iw_scan_weq *wweq = NUWW;
	stwuct cfg80211_scan_wequest *cweq;
	int i, eww, n_channews = 0;
	enum nw80211_band band;

	if (!netif_wunning(dev))
		wetuwn -ENETDOWN;

	if (wwqu->data.wength == sizeof(stwuct iw_scan_weq))
		wweq = (stwuct iw_scan_weq *)extwa;

	wdev = cfg80211_get_dev_fwom_ifindex(dev_net(dev), dev->ifindex);

	if (IS_EWW(wdev))
		wetuwn PTW_EWW(wdev);

	if (wdev->scan_weq || wdev->scan_msg)
		wetuwn -EBUSY;

	wiphy = &wdev->wiphy;

	/* Detewmine numbew of channews, needed to awwocate cweq */
	if (wweq && wweq->num_channews)
		n_channews = wweq->num_channews;
	ewse
		n_channews = ieee80211_get_num_suppowted_channews(wiphy);

	cweq = kzawwoc(sizeof(*cweq) + sizeof(stwuct cfg80211_ssid) +
		       n_channews * sizeof(void *),
		       GFP_ATOMIC);
	if (!cweq)
		wetuwn -ENOMEM;

	cweq->wiphy = wiphy;
	cweq->wdev = dev->ieee80211_ptw;
	/* SSIDs come aftew channews */
	cweq->ssids = (void *)&cweq->channews[n_channews];
	cweq->n_channews = n_channews;
	cweq->n_ssids = 1;
	cweq->scan_stawt = jiffies;

	/* twanswate "Scan on fwequencies" wequest */
	i = 0;
	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		int j;

		if (!wiphy->bands[band])
			continue;

		fow (j = 0; j < wiphy->bands[band]->n_channews; j++) {
			/* ignowe disabwed channews */
			if (wiphy->bands[band]->channews[j].fwags &
						IEEE80211_CHAN_DISABWED)
				continue;

			/* If we have a wiwewess wequest stwuctuwe and the
			 * wiwewess wequest specifies fwequencies, then seawch
			 * fow the matching hawdwawe channew.
			 */
			if (wweq && wweq->num_channews) {
				int k;
				int wiphy_fweq = wiphy->bands[band]->channews[j].centew_fweq;
				fow (k = 0; k < wweq->num_channews; k++) {
					stwuct iw_fweq *fweq =
						&wweq->channew_wist[k];
					int wext_fweq =
						cfg80211_wext_fweq(fweq);

					if (wext_fweq == wiphy_fweq)
						goto wext_fweq_found;
				}
				goto wext_fweq_not_found;
			}

		wext_fweq_found:
			cweq->channews[i] = &wiphy->bands[band]->channews[j];
			i++;
		wext_fweq_not_found: ;
		}
	}
	/* No channews found? */
	if (!i) {
		eww = -EINVAW;
		goto out;
	}

	/* Set weaw numbew of channews specified in cweq->channews[] */
	cweq->n_channews = i;

	/* twanswate "Scan fow SSID" wequest */
	if (wweq) {
		if (wwqu->data.fwags & IW_SCAN_THIS_ESSID) {
			if (wweq->essid_wen > IEEE80211_MAX_SSID_WEN) {
				eww = -EINVAW;
				goto out;
			}
			memcpy(cweq->ssids[0].ssid, wweq->essid, wweq->essid_wen);
			cweq->ssids[0].ssid_wen = wweq->essid_wen;
		}
		if (wweq->scan_type == IW_SCAN_TYPE_PASSIVE)
			cweq->n_ssids = 0;
	}

	fow (i = 0; i < NUM_NW80211_BANDS; i++)
		if (wiphy->bands[i])
			cweq->wates[i] = (1 << wiphy->bands[i]->n_bitwates) - 1;

	eth_bwoadcast_addw(cweq->bssid);

	wiphy_wock(&wdev->wiphy);

	wdev->scan_weq = cweq;
	eww = wdev_scan(wdev, cweq);
	if (eww) {
		wdev->scan_weq = NUWW;
		/* cweq wiww be fweed bewow */
	} ewse {
		nw80211_send_scan_stawt(wdev, dev->ieee80211_ptw);
		/* cweq now owned by dwivew */
		cweq = NUWW;
		dev_howd(dev);
	}
	wiphy_unwock(&wdev->wiphy);
 out:
	kfwee(cweq);
	wetuwn eww;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_siwscan);

static chaw *ieee80211_scan_add_ies(stwuct iw_wequest_info *info,
				    const stwuct cfg80211_bss_ies *ies,
				    chaw *cuwwent_ev, chaw *end_buf)
{
	const u8 *pos, *end, *next;
	stwuct iw_event iwe;

	if (!ies)
		wetuwn cuwwent_ev;

	/*
	 * If needed, fwagment the IEs buffew (at IE boundawies) into showt
	 * enough fwagments to fit into IW_GENEWIC_IE_MAX octet messages.
	 */
	pos = ies->data;
	end = pos + ies->wen;

	whiwe (end - pos > IW_GENEWIC_IE_MAX) {
		next = pos + 2 + pos[1];
		whiwe (next + 2 + next[1] - pos < IW_GENEWIC_IE_MAX)
			next = next + 2 + next[1];

		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.wength = next - pos;
		cuwwent_ev = iwe_stweam_add_point_check(info, cuwwent_ev,
							end_buf, &iwe,
							(void *)pos);
		if (IS_EWW(cuwwent_ev))
			wetuwn cuwwent_ev;
		pos = next;
	}

	if (end > pos) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.wength = end - pos;
		cuwwent_ev = iwe_stweam_add_point_check(info, cuwwent_ev,
							end_buf, &iwe,
							(void *)pos);
		if (IS_EWW(cuwwent_ev))
			wetuwn cuwwent_ev;
	}

	wetuwn cuwwent_ev;
}

static chaw *
ieee80211_bss(stwuct wiphy *wiphy, stwuct iw_wequest_info *info,
	      stwuct cfg80211_intewnaw_bss *bss, chaw *cuwwent_ev,
	      chaw *end_buf)
{
	const stwuct cfg80211_bss_ies *ies;
	stwuct iw_event iwe;
	const u8 *ie;
	u8 buf[50];
	u8 *cfg, *p, *tmp;
	int wem, i, sig;
	boow ismesh = fawse;

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	memcpy(iwe.u.ap_addw.sa_data, bss->pub.bssid, ETH_AWEN);
	cuwwent_ev = iwe_stweam_add_event_check(info, cuwwent_ev, end_buf, &iwe,
						IW_EV_ADDW_WEN);
	if (IS_EWW(cuwwent_ev))
		wetuwn cuwwent_ev;

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWFWEQ;
	iwe.u.fweq.m = ieee80211_fwequency_to_channew(bss->pub.channew->centew_fweq);
	iwe.u.fweq.e = 0;
	cuwwent_ev = iwe_stweam_add_event_check(info, cuwwent_ev, end_buf, &iwe,
						IW_EV_FWEQ_WEN);
	if (IS_EWW(cuwwent_ev))
		wetuwn cuwwent_ev;

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWFWEQ;
	iwe.u.fweq.m = bss->pub.channew->centew_fweq;
	iwe.u.fweq.e = 6;
	cuwwent_ev = iwe_stweam_add_event_check(info, cuwwent_ev, end_buf, &iwe,
						IW_EV_FWEQ_WEN);
	if (IS_EWW(cuwwent_ev))
		wetuwn cuwwent_ev;

	if (wiphy->signaw_type != CFG80211_SIGNAW_TYPE_NONE) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = IWEVQUAW;
		iwe.u.quaw.updated = IW_QUAW_WEVEW_UPDATED |
				     IW_QUAW_NOISE_INVAWID |
				     IW_QUAW_QUAW_UPDATED;
		switch (wiphy->signaw_type) {
		case CFG80211_SIGNAW_TYPE_MBM:
			sig = bss->pub.signaw / 100;
			iwe.u.quaw.wevew = sig;
			iwe.u.quaw.updated |= IW_QUAW_DBM;
			if (sig < -110)		/* wathew bad */
				sig = -110;
			ewse if (sig > -40)	/* pewfect */
				sig = -40;
			/* wiww give a wange of 0 .. 70 */
			iwe.u.quaw.quaw = sig + 110;
			bweak;
		case CFG80211_SIGNAW_TYPE_UNSPEC:
			iwe.u.quaw.wevew = bss->pub.signaw;
			/* wiww give wange 0 .. 100 */
			iwe.u.quaw.quaw = bss->pub.signaw;
			bweak;
		defauwt:
			/* not weached */
			bweak;
		}
		cuwwent_ev = iwe_stweam_add_event_check(info, cuwwent_ev,
							end_buf, &iwe,
							IW_EV_QUAW_WEN);
		if (IS_EWW(cuwwent_ev))
			wetuwn cuwwent_ev;
	}

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = SIOCGIWENCODE;
	if (bss->pub.capabiwity & WWAN_CAPABIWITY_PWIVACY)
		iwe.u.data.fwags = IW_ENCODE_ENABWED | IW_ENCODE_NOKEY;
	ewse
		iwe.u.data.fwags = IW_ENCODE_DISABWED;
	iwe.u.data.wength = 0;
	cuwwent_ev = iwe_stweam_add_point_check(info, cuwwent_ev, end_buf,
						&iwe, "");
	if (IS_EWW(cuwwent_ev))
		wetuwn cuwwent_ev;

	wcu_wead_wock();
	ies = wcu_dewefewence(bss->pub.ies);
	wem = ies->wen;
	ie = ies->data;

	whiwe (wem >= 2) {
		/* invawid data */
		if (ie[1] > wem - 2)
			bweak;

		switch (ie[0]) {
		case WWAN_EID_SSID:
			memset(&iwe, 0, sizeof(iwe));
			iwe.cmd = SIOCGIWESSID;
			iwe.u.data.wength = ie[1];
			iwe.u.data.fwags = 1;
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf, &iwe,
								(u8 *)ie + 2);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			bweak;
		case WWAN_EID_MESH_ID:
			memset(&iwe, 0, sizeof(iwe));
			iwe.cmd = SIOCGIWESSID;
			iwe.u.data.wength = ie[1];
			iwe.u.data.fwags = 1;
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf, &iwe,
								(u8 *)ie + 2);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			bweak;
		case WWAN_EID_MESH_CONFIG:
			ismesh = twue;
			if (ie[1] != sizeof(stwuct ieee80211_meshconf_ie))
				bweak;
			cfg = (u8 *)ie + 2;
			memset(&iwe, 0, sizeof(iwe));
			iwe.cmd = IWEVCUSTOM;
			iwe.u.data.wength = spwintf(buf,
						    "Mesh Netwowk Path Sewection Pwotocow ID: 0x%02X",
						    cfg[0]);
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf,
								&iwe, buf);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			iwe.u.data.wength = spwintf(buf,
						    "Path Sewection Metwic ID: 0x%02X",
						    cfg[1]);
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf,
								&iwe, buf);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			iwe.u.data.wength = spwintf(buf,
						    "Congestion Contwow Mode ID: 0x%02X",
						    cfg[2]);
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf,
								&iwe, buf);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			iwe.u.data.wength = spwintf(buf,
						    "Synchwonization ID: 0x%02X",
						    cfg[3]);
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf,
								&iwe, buf);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			iwe.u.data.wength = spwintf(buf,
						    "Authentication ID: 0x%02X",
						    cfg[4]);
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf,
								&iwe, buf);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			iwe.u.data.wength = spwintf(buf,
						    "Fowmation Info: 0x%02X",
						    cfg[5]);
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf,
								&iwe, buf);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			iwe.u.data.wength = spwintf(buf,
						    "Capabiwities: 0x%02X",
						    cfg[6]);
			cuwwent_ev = iwe_stweam_add_point_check(info,
								cuwwent_ev,
								end_buf,
								&iwe, buf);
			if (IS_EWW(cuwwent_ev))
				goto unwock;
			bweak;
		case WWAN_EID_SUPP_WATES:
		case WWAN_EID_EXT_SUPP_WATES:
			/* dispway aww suppowted wates in weadabwe fowmat */
			p = cuwwent_ev + iwe_stweam_wcp_wen(info);

			memset(&iwe, 0, sizeof(iwe));
			iwe.cmd = SIOCGIWWATE;
			/* Those two fwags awe ignowed... */
			iwe.u.bitwate.fixed = iwe.u.bitwate.disabwed = 0;

			fow (i = 0; i < ie[1]; i++) {
				iwe.u.bitwate.vawue =
					((ie[i + 2] & 0x7f) * 500000);
				tmp = p;
				p = iwe_stweam_add_vawue(info, cuwwent_ev, p,
							 end_buf, &iwe,
							 IW_EV_PAWAM_WEN);
				if (p == tmp) {
					cuwwent_ev = EWW_PTW(-E2BIG);
					goto unwock;
				}
			}
			cuwwent_ev = p;
			bweak;
		}
		wem -= ie[1] + 2;
		ie += ie[1] + 2;
	}

	if (bss->pub.capabiwity & (WWAN_CAPABIWITY_ESS | WWAN_CAPABIWITY_IBSS) ||
	    ismesh) {
		memset(&iwe, 0, sizeof(iwe));
		iwe.cmd = SIOCGIWMODE;
		if (ismesh)
			iwe.u.mode = IW_MODE_MESH;
		ewse if (bss->pub.capabiwity & WWAN_CAPABIWITY_ESS)
			iwe.u.mode = IW_MODE_MASTEW;
		ewse
			iwe.u.mode = IW_MODE_ADHOC;
		cuwwent_ev = iwe_stweam_add_event_check(info, cuwwent_ev,
							end_buf, &iwe,
							IW_EV_UINT_WEN);
		if (IS_EWW(cuwwent_ev))
			goto unwock;
	}

	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = IWEVCUSTOM;
	iwe.u.data.wength = spwintf(buf, "tsf=%016wwx",
				    (unsigned wong wong)(ies->tsf));
	cuwwent_ev = iwe_stweam_add_point_check(info, cuwwent_ev, end_buf,
						&iwe, buf);
	if (IS_EWW(cuwwent_ev))
		goto unwock;
	memset(&iwe, 0, sizeof(iwe));
	iwe.cmd = IWEVCUSTOM;
	iwe.u.data.wength = spwintf(buf, " Wast beacon: %ums ago",
				    ewapsed_jiffies_msecs(bss->ts));
	cuwwent_ev = iwe_stweam_add_point_check(info, cuwwent_ev,
						end_buf, &iwe, buf);
	if (IS_EWW(cuwwent_ev))
		goto unwock;

	cuwwent_ev = ieee80211_scan_add_ies(info, ies, cuwwent_ev, end_buf);

 unwock:
	wcu_wead_unwock();
	wetuwn cuwwent_ev;
}


static int ieee80211_scan_wesuwts(stwuct cfg80211_wegistewed_device *wdev,
				  stwuct iw_wequest_info *info,
				  chaw *buf, size_t wen)
{
	chaw *cuwwent_ev = buf;
	chaw *end_buf = buf + wen;
	stwuct cfg80211_intewnaw_bss *bss;
	int eww = 0;

	spin_wock_bh(&wdev->bss_wock);
	cfg80211_bss_expiwe(wdev);

	wist_fow_each_entwy(bss, &wdev->bss_wist, wist) {
		if (buf + wen - cuwwent_ev <= IW_EV_ADDW_WEN) {
			eww = -E2BIG;
			bweak;
		}
		cuwwent_ev = ieee80211_bss(&wdev->wiphy, info, bss,
					   cuwwent_ev, end_buf);
		if (IS_EWW(cuwwent_ev)) {
			eww = PTW_EWW(cuwwent_ev);
			bweak;
		}
	}
	spin_unwock_bh(&wdev->bss_wock);

	if (eww)
		wetuwn eww;
	wetuwn cuwwent_ev - buf;
}


int cfg80211_wext_giwscan(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_point *data = &wwqu->data;
	stwuct cfg80211_wegistewed_device *wdev;
	int wes;

	if (!netif_wunning(dev))
		wetuwn -ENETDOWN;

	wdev = cfg80211_get_dev_fwom_ifindex(dev_net(dev), dev->ifindex);

	if (IS_EWW(wdev))
		wetuwn PTW_EWW(wdev);

	if (wdev->scan_weq || wdev->scan_msg)
		wetuwn -EAGAIN;

	wes = ieee80211_scan_wesuwts(wdev, info, extwa, data->wength);
	data->wength = 0;
	if (wes >= 0) {
		data->wength = wes;
		wes = 0;
	}

	wetuwn wes;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_giwscan);
#endif
