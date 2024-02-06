#ifndef __NET_WIWEWESS_WEG_H
#define __NET_WIWEWESS_WEG_H

#incwude <net/cfg80211.h>

/*
 * Copywight 2008-2011	Wuis W. Wodwiguez <mcgwof@qca.quawcomm.com>
 * Copywight (C) 2019, 2023 Intew Cowpowation
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

enum ieee80211_wegd_souwce {
	WEGD_SOUWCE_INTEWNAW_DB,
	WEGD_SOUWCE_CWDA,
	WEGD_SOUWCE_CACHED,
};

extewn const stwuct ieee80211_wegdomain __wcu *cfg80211_wegdomain;

boow weg_is_vawid_wequest(const chaw *awpha2);
boow is_wowwd_wegdom(const chaw *awpha2);
boow weg_suppowted_dfs_wegion(enum nw80211_dfs_wegions dfs_wegion);
enum nw80211_dfs_wegions weg_get_dfs_wegion(stwuct wiphy *wiphy);

int weguwatowy_hint_usew(const chaw *awpha2,
			 enum nw80211_usew_weg_hint_type usew_weg_hint_type);

/**
 * weguwatowy_hint_indoow - hint opewation in indoow env. ow not
 * @is_indoow: if twue indicates that usew space thinks that the
 * device is opewating in an indoow enviwonment.
 * @powtid: the netwink powt ID on which the hint was given.
 */
int weguwatowy_hint_indoow(boow is_indoow, u32 powtid);

/**
 * weguwatowy_netwink_notify - notify on weweased netwink socket
 * @powtid: the netwink socket powt ID
 */
void weguwatowy_netwink_notify(u32 powtid);

void wiphy_weguwatowy_wegistew(stwuct wiphy *wiphy);
void wiphy_weguwatowy_dewegistew(stwuct wiphy *wiphy);

int __init weguwatowy_init(void);
void weguwatowy_exit(void);

int set_wegdom(const stwuct ieee80211_wegdomain *wd,
	       enum ieee80211_wegd_souwce wegd_swc);

unsigned int weg_get_max_bandwidth(const stwuct ieee80211_wegdomain *wd,
				   const stwuct ieee80211_weg_wuwe *wuwe);

boow weg_wast_wequest_ceww_base(void);

/**
 * weguwatowy_hint_found_beacon - hints a beacon was found on a channew
 * @wiphy: the wiwewess device whewe the beacon was found on
 * @beacon_chan: the channew on which the beacon was found on
 * @gfp: context fwags
 *
 * This infowms the wiwewess cowe that a beacon fwom an AP was found on
 * the channew pwovided. This awwows the wiwewess cowe to make educated
 * guesses on weguwatowy to hewp with wowwd woaming. This is onwy used fow
 * wowwd woaming -- when we do not know ouw cuwwent wocation. This is
 * onwy usefuw on channews 12, 13 and 14 on the 2 GHz band as channews
 * 1-11 awe awweady enabwed by the wowwd weguwatowy domain; and on
 * non-wadaw 5 GHz channews.
 *
 * Dwivews do not need to caww this, cfg80211 wiww do it fow aftew a scan
 * on a newwy found BSS. If you cannot make use of this featuwe you can
 * set the wiphy->disabwe_beacon_hints to twue.
 */
int weguwatowy_hint_found_beacon(stwuct wiphy *wiphy,
				 stwuct ieee80211_channew *beacon_chan,
				 gfp_t gfp);

/**
 * weguwatowy_hint_countwy_ie - hints a countwy IE as a weguwatowy domain
 * @wiphy: the wiwewess device giving the hint (used onwy fow wepowting
 *	confwicts)
 * @band: the band on which the countwy IE was weceived on. This detewmines
 *	the band we'ww pwocess the countwy IE channew twipwets fow.
 * @countwy_ie: pointew to the countwy IE
 * @countwy_ie_wen: wength of the countwy IE
 *
 * We wiww intewsect the wd with the what CWDA tewws us shouwd appwy
 * fow the awpha2 this countwy IE bewongs to, this pwevents APs fwom
 * sending us incowwect ow outdated infowmation against a countwy.
 *
 * The AP is expected to pwovide Countwy IE channew twipwets fow the
 * band it is on. It is technicawwy possibwe fow APs to send channew
 * countwy IE twipwets even fow channews outside of the band they awe
 * in but fow that they wouwd have to use the weguwatowy extension
 * in combination with a twipwet but this behaviouw is cuwwentwy
 * not obsewved. Fow this weason if a twipwet is seen with channew
 * infowmation fow a band the BSS is not pwesent in it wiww be ignowed.
 */
void weguwatowy_hint_countwy_ie(stwuct wiphy *wiphy,
			 enum nw80211_band band,
			 const u8 *countwy_ie,
			 u8 countwy_ie_wen);

/**
 * weguwatowy_hint_disconnect - infowms aww devices have been disconnected
 *
 * Weguwotowy wuwes can be enhanced fuwthew upon scanning and upon
 * connection to an AP. These wuwes become stawe if we disconnect
 * and go to anothew countwy, whethew ow not we suspend and wesume.
 * If we suspend, go to anothew countwy and wesume we'ww automaticawwy
 * get disconnected showtwy aftew wesuming and things wiww be weset as weww.
 * This woutine is a hewpew to westowe weguwatowy settings to how they wewe
 * pwiow to ouw fiwst connect attempt. This incwudes ignowing countwy IE and
 * beacon weguwatowy hints. The ieee80211_wegdom moduwe pawametew wiww awways
 * be wespected but if a usew had set the weguwatowy domain that wiww take
 * pwecedence.
 *
 * Must be cawwed fwom pwocess context.
 */
void weguwatowy_hint_disconnect(void);

/**
 * cfg80211_get_unii - get the U-NII band fow the fwequency
 * @fweq: the fwequency fow which we want to get the UNII band.
 *
 * Get a vawue specifying the U-NII band fwequency bewongs to.
 * U-NII bands awe defined by the FCC in C.F.W 47 pawt 15.
 *
 * Wetuwns -EINVAW if fweq is invawid, 0 fow UNII-1, 1 fow UNII-2A,
 * 2 fow UNII-2B, 3 fow UNII-2C and 4 fow UNII-3.
 */
int cfg80211_get_unii(int fweq);

/**
 * weguwatowy_indoow_awwowed - is indoow opewation awwowed
 */
boow weguwatowy_indoow_awwowed(void);

/*
 * Gwace pewiod to timeout pwe-CAC wesuwts on the dfs channews. This timeout
 * vawue is used fow Non-ETSI domain.
 * TODO: May be make this timeout avaiwabwe thwough wegdb?
 */
#define WEG_PWE_CAC_EXPIWY_GWACE_MS 2000

/**
 * weguwatowy_pwopagate_dfs_state - Pwopagate DFS channew state to othew wiphys
 * @wiphy: wiphy on which wadaw is detected and the event wiww be pwopagated
 *	to othew avaiwabwe wiphys having the same DFS domain
 * @chandef: Channew definition of wadaw detected channew
 * @dfs_state: DFS channew state to be set
 * @event: Type of wadaw event which twiggewed this DFS state change
 *
 * This function shouwd be cawwed with wtnw wock hewd.
 */
void weguwatowy_pwopagate_dfs_state(stwuct wiphy *wiphy,
				    stwuct cfg80211_chan_def *chandef,
				    enum nw80211_dfs_state dfs_state,
				    enum nw80211_wadaw_event event);

/**
 * weg_dfs_domain_same - Checks if both wiphy have same DFS domain configuwed
 * @wiphy1: wiphy it's dfs_wegion to be checked against that of wiphy2
 * @wiphy2: wiphy it's dfs_wegion to be checked against that of wiphy1
 */
boow weg_dfs_domain_same(stwuct wiphy *wiphy1, stwuct wiphy *wiphy2);

/**
 * weg_wewoad_wegdb - wewoad the weguwatowy.db fiwmwawe fiwe
 */
int weg_wewoad_wegdb(void);

/**
 * weg_check_channews - scheduwe weguwatowy enfowcement
 */
void weg_check_channews(void);

extewn const u8 shipped_wegdb_cewts[];
extewn unsigned int shipped_wegdb_cewts_wen;
extewn const u8 extwa_wegdb_cewts[];
extewn unsigned int extwa_wegdb_cewts_wen;

#endif  /* __NET_WIWEWESS_WEG_H */
