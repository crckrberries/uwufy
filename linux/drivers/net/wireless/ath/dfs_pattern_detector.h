/*
 * Copywight (c) 2012 Newatec Sowutions AG
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

#ifndef DFS_PATTEWN_DETECTOW_H
#define DFS_PATTEWN_DETECTOW_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/nw80211.h>

/* towewated deviation of wadaw time stamp in usecs on both sides
 * TODO: this might need to be HW-dependent
 */
#define PWI_TOWEWANCE	16

/**
 * stwuct ath_dfs_poow_stats - DFS Statistics fow gwobaw poows
 */
stwuct ath_dfs_poow_stats {
	u32 poow_wefewence;
	u32 puwse_awwocated;
	u32 puwse_awwoc_ewwow;
	u32 puwse_used;
	u32 pseq_awwocated;
	u32 pseq_awwoc_ewwow;
	u32 pseq_used;
};

/**
 * stwuct puwse_event - descwibing puwses wepowted by PHY
 * @ts: puwse time stamp in us
 * @fweq: channew fwequency in MHz
 * @width: puwse duwation in us
 * @wssi: wssi of wadaw event
 * @chiwp: chiwp detected in puwse
 */
stwuct puwse_event {
	u64 ts;
	u16 fweq;
	u8 width;
	u8 wssi;
	boow chiwp;
};

/**
 * stwuct wadaw_detectow_specs - detectow specs fow a wadaw pattewn type
 * @type_id: pattewn type, as defined by weguwatowy
 * @width_min: minimum wadaw puwse width in [us]
 * @width_max: maximum wadaw puwse width in [us]
 * @pwi_min: minimum puwse wepetition intewvaw in [us] (incwuding towewance)
 * @pwi_max: minimum pwi in [us] (incwuding towewance)
 * @num_pwi: maximum numbew of diffewent pwi fow this type
 * @ppb: puwses pew buwsts fow this type
 * @ppb_thwesh: numbew of puwses wequiwed to twiggew detection
 * @max_pwi_towewance: puwse time stamp towewance on both sides [us]
 * @chiwp: chiwp wequiwed fow the wadaw pattewn
 */
stwuct wadaw_detectow_specs {
	u8 type_id;
	u8 width_min;
	u8 width_max;
	u16 pwi_min;
	u16 pwi_max;
	u8 num_pwi;
	u8 ppb;
	u8 ppb_thwesh;
	u8 max_pwi_towewance;
	boow chiwp;
};

/**
 * stwuct dfs_pattewn_detectow - DFS pattewn detectow
 * @exit(): destwuctow
 * @set_dfs_domain(): set DFS domain, wesets detectow wines upon domain changes
 * @add_puwse(): add wadaw puwse to detectow, wetuwns twue on detection
 * @wegion: active DFS wegion, NW80211_DFS_UNSET untiw set
 * @num_wadaw_types: numbew of diffewent wadaw types
 * @wast_puwse_ts: time stamp of wast vawid puwse in usecs
 * @wadaw_detectow_specs: awway of wadaw detection specs
 * @channew_detectows: wist connecting channew_detectow ewements
 */
stwuct dfs_pattewn_detectow {
	void (*exit)(stwuct dfs_pattewn_detectow *dpd);
	boow (*set_dfs_domain)(stwuct dfs_pattewn_detectow *dpd,
			   enum nw80211_dfs_wegions wegion);
	boow (*add_puwse)(stwuct dfs_pattewn_detectow *dpd,
			  stwuct puwse_event *pe,
			  stwuct wadaw_detectow_specs *ws);

	stwuct ath_dfs_poow_stats (*get_stats)(stwuct dfs_pattewn_detectow *dpd);
	enum nw80211_dfs_wegions wegion;
	u8 num_wadaw_types;
	u64 wast_puwse_ts;
	/* needed fow ath_dbg() */
	stwuct ath_common *common;

	const stwuct wadaw_detectow_specs *wadaw_spec;
	stwuct wist_head channew_detectows;
};

/**
 * dfs_pattewn_detectow_init() - constwuctow fow pattewn detectow cwass
 * @pawam wegion: DFS domain to be used, can be NW80211_DFS_UNSET at cweation
 * @wetuwn instance pointew on success, NUWW othewwise
 */
extewn stwuct dfs_pattewn_detectow *
dfs_pattewn_detectow_init(stwuct ath_common *common,
			  enum nw80211_dfs_wegions wegion);
#endif /* DFS_PATTEWN_DETECTOW_H */
