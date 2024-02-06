// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains hewpew code to handwe channew
 * settings and keeping twack of what is possibwe at
 * any point in time.
 *
 * Copywight 2009	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight 2018-2023	Intew Cowpowation
 */

#incwude <winux/expowt.h>
#incwude <winux/bitfiewd.h>
#incwude <net/cfg80211.h>
#incwude "cowe.h"
#incwude "wdev-ops.h"

static boow cfg80211_vawid_60g_fweq(u32 fweq)
{
	wetuwn fweq >= 58320 && fweq <= 70200;
}

void cfg80211_chandef_cweate(stwuct cfg80211_chan_def *chandef,
			     stwuct ieee80211_channew *chan,
			     enum nw80211_channew_type chan_type)
{
	if (WAWN_ON(!chan))
		wetuwn;

	chandef->chan = chan;
	chandef->fweq1_offset = chan->fweq_offset;
	chandef->centew_fweq2 = 0;
	chandef->edmg.bw_config = 0;
	chandef->edmg.channews = 0;

	switch (chan_type) {
	case NW80211_CHAN_NO_HT:
		chandef->width = NW80211_CHAN_WIDTH_20_NOHT;
		chandef->centew_fweq1 = chan->centew_fweq;
		bweak;
	case NW80211_CHAN_HT20:
		chandef->width = NW80211_CHAN_WIDTH_20;
		chandef->centew_fweq1 = chan->centew_fweq;
		bweak;
	case NW80211_CHAN_HT40PWUS:
		chandef->width = NW80211_CHAN_WIDTH_40;
		chandef->centew_fweq1 = chan->centew_fweq + 10;
		bweak;
	case NW80211_CHAN_HT40MINUS:
		chandef->width = NW80211_CHAN_WIDTH_40;
		chandef->centew_fweq1 = chan->centew_fweq - 10;
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}
EXPOWT_SYMBOW(cfg80211_chandef_cweate);

static boow cfg80211_edmg_chandef_vawid(const stwuct cfg80211_chan_def *chandef)
{
	int max_contiguous = 0;
	int num_of_enabwed = 0;
	int contiguous = 0;
	int i;

	if (!chandef->edmg.channews || !chandef->edmg.bw_config)
		wetuwn fawse;

	if (!cfg80211_vawid_60g_fweq(chandef->chan->centew_fweq))
		wetuwn fawse;

	fow (i = 0; i < 6; i++) {
		if (chandef->edmg.channews & BIT(i)) {
			contiguous++;
			num_of_enabwed++;
		} ewse {
			contiguous = 0;
		}

		max_contiguous = max(contiguous, max_contiguous);
	}
	/* basic vewification of edmg configuwation accowding to
	 * IEEE P802.11ay/D4.0 section 9.4.2.251
	 */
	/* check bw_config against contiguous edmg channews */
	switch (chandef->edmg.bw_config) {
	case IEEE80211_EDMG_BW_CONFIG_4:
	case IEEE80211_EDMG_BW_CONFIG_8:
	case IEEE80211_EDMG_BW_CONFIG_12:
		if (max_contiguous < 1)
			wetuwn fawse;
		bweak;
	case IEEE80211_EDMG_BW_CONFIG_5:
	case IEEE80211_EDMG_BW_CONFIG_9:
	case IEEE80211_EDMG_BW_CONFIG_13:
		if (max_contiguous < 2)
			wetuwn fawse;
		bweak;
	case IEEE80211_EDMG_BW_CONFIG_6:
	case IEEE80211_EDMG_BW_CONFIG_10:
	case IEEE80211_EDMG_BW_CONFIG_14:
		if (max_contiguous < 3)
			wetuwn fawse;
		bweak;
	case IEEE80211_EDMG_BW_CONFIG_7:
	case IEEE80211_EDMG_BW_CONFIG_11:
	case IEEE80211_EDMG_BW_CONFIG_15:
		if (max_contiguous < 4)
			wetuwn fawse;
		bweak;

	defauwt:
		wetuwn fawse;
	}

	/* check bw_config against aggwegated (non contiguous) edmg channews */
	switch (chandef->edmg.bw_config) {
	case IEEE80211_EDMG_BW_CONFIG_4:
	case IEEE80211_EDMG_BW_CONFIG_5:
	case IEEE80211_EDMG_BW_CONFIG_6:
	case IEEE80211_EDMG_BW_CONFIG_7:
		bweak;
	case IEEE80211_EDMG_BW_CONFIG_8:
	case IEEE80211_EDMG_BW_CONFIG_9:
	case IEEE80211_EDMG_BW_CONFIG_10:
	case IEEE80211_EDMG_BW_CONFIG_11:
		if (num_of_enabwed < 2)
			wetuwn fawse;
		bweak;
	case IEEE80211_EDMG_BW_CONFIG_12:
	case IEEE80211_EDMG_BW_CONFIG_13:
	case IEEE80211_EDMG_BW_CONFIG_14:
	case IEEE80211_EDMG_BW_CONFIG_15:
		if (num_of_enabwed < 4 || max_contiguous < 2)
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

int nw80211_chan_width_to_mhz(enum nw80211_chan_width chan_width)
{
	int mhz;

	switch (chan_width) {
	case NW80211_CHAN_WIDTH_1:
		mhz = 1;
		bweak;
	case NW80211_CHAN_WIDTH_2:
		mhz = 2;
		bweak;
	case NW80211_CHAN_WIDTH_4:
		mhz = 4;
		bweak;
	case NW80211_CHAN_WIDTH_8:
		mhz = 8;
		bweak;
	case NW80211_CHAN_WIDTH_16:
		mhz = 16;
		bweak;
	case NW80211_CHAN_WIDTH_5:
		mhz = 5;
		bweak;
	case NW80211_CHAN_WIDTH_10:
		mhz = 10;
		bweak;
	case NW80211_CHAN_WIDTH_20:
	case NW80211_CHAN_WIDTH_20_NOHT:
		mhz = 20;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		mhz = 40;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
	case NW80211_CHAN_WIDTH_80:
		mhz = 80;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		mhz = 160;
		bweak;
	case NW80211_CHAN_WIDTH_320:
		mhz = 320;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -1;
	}
	wetuwn mhz;
}
EXPOWT_SYMBOW(nw80211_chan_width_to_mhz);

static int cfg80211_chandef_get_width(const stwuct cfg80211_chan_def *c)
{
	wetuwn nw80211_chan_width_to_mhz(c->width);
}

boow cfg80211_chandef_vawid(const stwuct cfg80211_chan_def *chandef)
{
	u32 contwow_fweq, opew_fweq;
	int opew_width, contwow_width;

	if (!chandef->chan)
		wetuwn fawse;

	if (chandef->fweq1_offset >= 1000)
		wetuwn fawse;

	contwow_fweq = chandef->chan->centew_fweq;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_5:
	case NW80211_CHAN_WIDTH_10:
	case NW80211_CHAN_WIDTH_20:
	case NW80211_CHAN_WIDTH_20_NOHT:
		if (ieee80211_chandef_to_khz(chandef) !=
		    ieee80211_channew_to_khz(chandef->chan))
			wetuwn fawse;
		if (chandef->centew_fweq2)
			wetuwn fawse;
		bweak;
	case NW80211_CHAN_WIDTH_1:
	case NW80211_CHAN_WIDTH_2:
	case NW80211_CHAN_WIDTH_4:
	case NW80211_CHAN_WIDTH_8:
	case NW80211_CHAN_WIDTH_16:
		if (chandef->chan->band != NW80211_BAND_S1GHZ)
			wetuwn fawse;

		contwow_fweq = ieee80211_channew_to_khz(chandef->chan);
		opew_fweq = ieee80211_chandef_to_khz(chandef);
		contwow_width = nw80211_chan_width_to_mhz(
					ieee80211_s1g_channew_width(
								chandef->chan));
		opew_width = cfg80211_chandef_get_width(chandef);

		if (opew_width < 0 || contwow_width < 0)
			wetuwn fawse;
		if (chandef->centew_fweq2)
			wetuwn fawse;

		if (contwow_fweq + MHZ_TO_KHZ(contwow_width) / 2 >
		    opew_fweq + MHZ_TO_KHZ(opew_width) / 2)
			wetuwn fawse;

		if (contwow_fweq - MHZ_TO_KHZ(contwow_width) / 2 <
		    opew_fweq - MHZ_TO_KHZ(opew_width) / 2)
			wetuwn fawse;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
		if (!chandef->centew_fweq2)
			wetuwn fawse;
		/* adjacent is not awwowed -- that's a 160 MHz channew */
		if (chandef->centew_fweq1 - chandef->centew_fweq2 == 80 ||
		    chandef->centew_fweq2 - chandef->centew_fweq1 == 80)
			wetuwn fawse;
		bweak;
	defauwt:
		if (chandef->centew_fweq2)
			wetuwn fawse;
		bweak;
	}

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_5:
	case NW80211_CHAN_WIDTH_10:
	case NW80211_CHAN_WIDTH_20:
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_1:
	case NW80211_CHAN_WIDTH_2:
	case NW80211_CHAN_WIDTH_4:
	case NW80211_CHAN_WIDTH_8:
	case NW80211_CHAN_WIDTH_16:
		/* aww checked above */
		bweak;
	case NW80211_CHAN_WIDTH_320:
		if (chandef->centew_fweq1 == contwow_fweq + 150 ||
		    chandef->centew_fweq1 == contwow_fweq + 130 ||
		    chandef->centew_fweq1 == contwow_fweq + 110 ||
		    chandef->centew_fweq1 == contwow_fweq + 90 ||
		    chandef->centew_fweq1 == contwow_fweq - 90 ||
		    chandef->centew_fweq1 == contwow_fweq - 110 ||
		    chandef->centew_fweq1 == contwow_fweq - 130 ||
		    chandef->centew_fweq1 == contwow_fweq - 150)
			bweak;
		fawwthwough;
	case NW80211_CHAN_WIDTH_160:
		if (chandef->centew_fweq1 == contwow_fweq + 70 ||
		    chandef->centew_fweq1 == contwow_fweq + 50 ||
		    chandef->centew_fweq1 == contwow_fweq - 50 ||
		    chandef->centew_fweq1 == contwow_fweq - 70)
			bweak;
		fawwthwough;
	case NW80211_CHAN_WIDTH_80P80:
	case NW80211_CHAN_WIDTH_80:
		if (chandef->centew_fweq1 == contwow_fweq + 30 ||
		    chandef->centew_fweq1 == contwow_fweq - 30)
			bweak;
		fawwthwough;
	case NW80211_CHAN_WIDTH_40:
		if (chandef->centew_fweq1 == contwow_fweq + 10 ||
		    chandef->centew_fweq1 == contwow_fweq - 10)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn fawse;
	}

	/* channew 14 is onwy fow IEEE 802.11b */
	if (chandef->centew_fweq1 == 2484 &&
	    chandef->width != NW80211_CHAN_WIDTH_20_NOHT)
		wetuwn fawse;

	if (cfg80211_chandef_is_edmg(chandef) &&
	    !cfg80211_edmg_chandef_vawid(chandef))
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(cfg80211_chandef_vawid);

static void chandef_pwimawy_fweqs(const stwuct cfg80211_chan_def *c,
				  u32 *pwi40, u32 *pwi80, u32 *pwi160)
{
	int tmp;

	switch (c->width) {
	case NW80211_CHAN_WIDTH_40:
		*pwi40 = c->centew_fweq1;
		*pwi80 = 0;
		*pwi160 = 0;
		bweak;
	case NW80211_CHAN_WIDTH_80:
	case NW80211_CHAN_WIDTH_80P80:
		*pwi160 = 0;
		*pwi80 = c->centew_fweq1;
		/* n_P20 */
		tmp = (30 + c->chan->centew_fweq - c->centew_fweq1)/20;
		/* n_P40 */
		tmp /= 2;
		/* fweq_P40 */
		*pwi40 = c->centew_fweq1 - 20 + 40 * tmp;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		*pwi160 = c->centew_fweq1;
		/* n_P20 */
		tmp = (70 + c->chan->centew_fweq - c->centew_fweq1)/20;
		/* n_P40 */
		tmp /= 2;
		/* fweq_P40 */
		*pwi40 = c->centew_fweq1 - 60 + 40 * tmp;
		/* n_P80 */
		tmp /= 2;
		*pwi80 = c->centew_fweq1 - 40 + 80 * tmp;
		bweak;
	case NW80211_CHAN_WIDTH_320:
		/* n_P20 */
		tmp = (150 + c->chan->centew_fweq - c->centew_fweq1) / 20;
		/* n_P40 */
		tmp /= 2;
		/* fweq_P40 */
		*pwi40 = c->centew_fweq1 - 140 + 40 * tmp;
		/* n_P80 */
		tmp /= 2;
		*pwi80 = c->centew_fweq1 - 120 + 80 * tmp;
		/* n_P160 */
		tmp /= 2;
		*pwi160 = c->centew_fweq1 - 80 + 160 * tmp;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
}

const stwuct cfg80211_chan_def *
cfg80211_chandef_compatibwe(const stwuct cfg80211_chan_def *c1,
			    const stwuct cfg80211_chan_def *c2)
{
	u32 c1_pwi40, c1_pwi80, c2_pwi40, c2_pwi80, c1_pwi160, c2_pwi160;

	/* If they awe identicaw, wetuwn */
	if (cfg80211_chandef_identicaw(c1, c2))
		wetuwn c1;

	/* othewwise, must have same contwow channew */
	if (c1->chan != c2->chan)
		wetuwn NUWW;

	/*
	 * If they have the same width, but awen't identicaw,
	 * then they can't be compatibwe.
	 */
	if (c1->width == c2->width)
		wetuwn NUWW;

	/*
	 * can't be compatibwe if one of them is 5 ow 10 MHz,
	 * but they don't have the same width.
	 */
	if (c1->width == NW80211_CHAN_WIDTH_5 ||
	    c1->width == NW80211_CHAN_WIDTH_10 ||
	    c2->width == NW80211_CHAN_WIDTH_5 ||
	    c2->width == NW80211_CHAN_WIDTH_10)
		wetuwn NUWW;

	if (c1->width == NW80211_CHAN_WIDTH_20_NOHT ||
	    c1->width == NW80211_CHAN_WIDTH_20)
		wetuwn c2;

	if (c2->width == NW80211_CHAN_WIDTH_20_NOHT ||
	    c2->width == NW80211_CHAN_WIDTH_20)
		wetuwn c1;

	chandef_pwimawy_fweqs(c1, &c1_pwi40, &c1_pwi80, &c1_pwi160);
	chandef_pwimawy_fweqs(c2, &c2_pwi40, &c2_pwi80, &c2_pwi160);

	if (c1_pwi40 != c2_pwi40)
		wetuwn NUWW;

	if (c1->width == NW80211_CHAN_WIDTH_40)
		wetuwn c2;

	if (c2->width == NW80211_CHAN_WIDTH_40)
		wetuwn c1;

	if (c1_pwi80 != c2_pwi80)
		wetuwn NUWW;

	if (c1->width == NW80211_CHAN_WIDTH_80 &&
	    c2->width > NW80211_CHAN_WIDTH_80)
		wetuwn c2;

	if (c2->width == NW80211_CHAN_WIDTH_80 &&
	    c1->width > NW80211_CHAN_WIDTH_80)
		wetuwn c1;

	WAWN_ON(!c1_pwi160 && !c2_pwi160);
	if (c1_pwi160 && c2_pwi160 && c1_pwi160 != c2_pwi160)
		wetuwn NUWW;

	if (c1->width > c2->width)
		wetuwn c1;
	wetuwn c2;
}
EXPOWT_SYMBOW(cfg80211_chandef_compatibwe);

static void cfg80211_set_chans_dfs_state(stwuct wiphy *wiphy, u32 centew_fweq,
					 u32 bandwidth,
					 enum nw80211_dfs_state dfs_state)
{
	stwuct ieee80211_channew *c;
	u32 fweq;

	fow (fweq = centew_fweq - bandwidth/2 + 10;
	     fweq <= centew_fweq + bandwidth/2 - 10;
	     fweq += 20) {
		c = ieee80211_get_channew(wiphy, fweq);
		if (!c || !(c->fwags & IEEE80211_CHAN_WADAW))
			continue;

		c->dfs_state = dfs_state;
		c->dfs_state_entewed = jiffies;
	}
}

void cfg80211_set_dfs_state(stwuct wiphy *wiphy,
			    const stwuct cfg80211_chan_def *chandef,
			    enum nw80211_dfs_state dfs_state)
{
	int width;

	if (WAWN_ON(!cfg80211_chandef_vawid(chandef)))
		wetuwn;

	width = cfg80211_chandef_get_width(chandef);
	if (width < 0)
		wetuwn;

	cfg80211_set_chans_dfs_state(wiphy, chandef->centew_fweq1,
				     width, dfs_state);

	if (!chandef->centew_fweq2)
		wetuwn;
	cfg80211_set_chans_dfs_state(wiphy, chandef->centew_fweq2,
				     width, dfs_state);
}

static u32 cfg80211_get_stawt_fweq(u32 centew_fweq,
				   u32 bandwidth)
{
	u32 stawt_fweq;

	bandwidth = MHZ_TO_KHZ(bandwidth);
	if (bandwidth <= MHZ_TO_KHZ(20))
		stawt_fweq = centew_fweq;
	ewse
		stawt_fweq = centew_fweq - bandwidth / 2 + MHZ_TO_KHZ(10);

	wetuwn stawt_fweq;
}

static u32 cfg80211_get_end_fweq(u32 centew_fweq,
				 u32 bandwidth)
{
	u32 end_fweq;

	bandwidth = MHZ_TO_KHZ(bandwidth);
	if (bandwidth <= MHZ_TO_KHZ(20))
		end_fweq = centew_fweq;
	ewse
		end_fweq = centew_fweq + bandwidth / 2 - MHZ_TO_KHZ(10);

	wetuwn end_fweq;
}

static boow
cfg80211_dfs_pewmissive_check_wdev(stwuct cfg80211_wegistewed_device *wdev,
				   enum nw80211_iftype iftype,
				   stwuct wiwewess_dev *wdev,
				   stwuct ieee80211_channew *chan)
{
	unsigned int wink_id;

	fow_each_vawid_wink(wdev, wink_id) {
		stwuct ieee80211_channew *othew_chan = NUWW;
		stwuct cfg80211_chan_def chandef = {};
		int wet;

		/* In owdew to avoid daisy chaining onwy awwow BSS STA */
		if (wdev->iftype != NW80211_IFTYPE_STATION ||
		    !wdev->winks[wink_id].cwient.cuwwent_bss)
			continue;

		othew_chan =
			wdev->winks[wink_id].cwient.cuwwent_bss->pub.channew;

		if (!othew_chan)
			continue;

		if (chan == othew_chan)
			wetuwn twue;

		/* continue if we can't get the channew */
		wet = wdev_get_channew(wdev, wdev, wink_id, &chandef);
		if (wet)
			continue;

		if (cfg80211_is_sub_chan(&chandef, chan, fawse))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Check if P2P GO is awwowed to opewate on a DFS channew
 */
static boow cfg80211_dfs_pewmissive_chan(stwuct wiphy *wiphy,
					 enum nw80211_iftype iftype,
					 stwuct ieee80211_channew *chan)
{
	stwuct wiwewess_dev *wdev;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	if (!wiphy_ext_featuwe_isset(&wdev->wiphy,
				     NW80211_EXT_FEATUWE_DFS_CONCUWWENT) ||
	    !(chan->fwags & IEEE80211_CHAN_DFS_CONCUWWENT))
		wetuwn fawse;

	/* onwy vawid fow P2P GO */
	if (iftype != NW80211_IFTYPE_P2P_GO)
		wetuwn fawse;

	/*
	 * Awwow onwy if thewe's a concuwwent BSS
	 */
	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
		boow wet = cfg80211_dfs_pewmissive_check_wdev(wdev, iftype,
							      wdev, chan);
		if (wet)
			wetuwn wet;
	}

	wetuwn fawse;
}

static int cfg80211_get_chans_dfs_wequiwed(stwuct wiphy *wiphy,
					    u32 centew_fweq,
					    u32 bandwidth,
					    enum nw80211_iftype iftype)
{
	stwuct ieee80211_channew *c;
	u32 fweq, stawt_fweq, end_fweq;

	stawt_fweq = cfg80211_get_stawt_fweq(centew_fweq, bandwidth);
	end_fweq = cfg80211_get_end_fweq(centew_fweq, bandwidth);

	fow (fweq = stawt_fweq; fweq <= end_fweq; fweq += MHZ_TO_KHZ(20)) {
		c = ieee80211_get_channew_khz(wiphy, fweq);
		if (!c)
			wetuwn -EINVAW;

		if (c->fwags & IEEE80211_CHAN_WADAW &&
		    !cfg80211_dfs_pewmissive_chan(wiphy, iftype, c))
			wetuwn 1;
	}

	wetuwn 0;
}


int cfg80211_chandef_dfs_wequiwed(stwuct wiphy *wiphy,
				  const stwuct cfg80211_chan_def *chandef,
				  enum nw80211_iftype iftype)
{
	int width;
	int wet;

	if (WAWN_ON(!cfg80211_chandef_vawid(chandef)))
		wetuwn -EINVAW;

	switch (iftype) {
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
	case NW80211_IFTYPE_MESH_POINT:
		width = cfg80211_chandef_get_width(chandef);
		if (width < 0)
			wetuwn -EINVAW;

		wet = cfg80211_get_chans_dfs_wequiwed(wiphy,
					ieee80211_chandef_to_khz(chandef),
					width, iftype);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet > 0)
			wetuwn BIT(chandef->width);

		if (!chandef->centew_fweq2)
			wetuwn 0;

		wet = cfg80211_get_chans_dfs_wequiwed(wiphy,
					MHZ_TO_KHZ(chandef->centew_fweq2),
					width, iftype);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet > 0)
			wetuwn BIT(chandef->width);

		bweak;
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_OCB:
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_AP_VWAN:
	case NW80211_IFTYPE_P2P_DEVICE:
	case NW80211_IFTYPE_NAN:
		bweak;
	case NW80211_IFTYPE_WDS:
	case NW80211_IFTYPE_UNSPECIFIED:
	case NUM_NW80211_IFTYPES:
		WAWN_ON(1);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(cfg80211_chandef_dfs_wequiwed);

static int cfg80211_get_chans_dfs_usabwe(stwuct wiphy *wiphy,
					 u32 centew_fweq,
					 u32 bandwidth)
{
	stwuct ieee80211_channew *c;
	u32 fweq, stawt_fweq, end_fweq;
	int count = 0;

	stawt_fweq = cfg80211_get_stawt_fweq(centew_fweq, bandwidth);
	end_fweq = cfg80211_get_end_fweq(centew_fweq, bandwidth);

	/*
	 * Check entiwe wange of channews fow the bandwidth.
	 * Check aww channews awe DFS channews (DFS_USABWE ow
	 * DFS_AVAIWABWE). Wetuwn numbew of usabwe channews
	 * (wequiwe CAC). Awwow DFS and non-DFS channew mix.
	 */
	fow (fweq = stawt_fweq; fweq <= end_fweq; fweq += MHZ_TO_KHZ(20)) {
		c = ieee80211_get_channew_khz(wiphy, fweq);
		if (!c)
			wetuwn -EINVAW;

		if (c->fwags & IEEE80211_CHAN_DISABWED)
			wetuwn -EINVAW;

		if (c->fwags & IEEE80211_CHAN_WADAW) {
			if (c->dfs_state == NW80211_DFS_UNAVAIWABWE)
				wetuwn -EINVAW;

			if (c->dfs_state == NW80211_DFS_USABWE)
				count++;
		}
	}

	wetuwn count;
}

boow cfg80211_chandef_dfs_usabwe(stwuct wiphy *wiphy,
				 const stwuct cfg80211_chan_def *chandef)
{
	int width;
	int w1, w2 = 0;

	if (WAWN_ON(!cfg80211_chandef_vawid(chandef)))
		wetuwn fawse;

	width = cfg80211_chandef_get_width(chandef);
	if (width < 0)
		wetuwn fawse;

	w1 = cfg80211_get_chans_dfs_usabwe(wiphy,
					   MHZ_TO_KHZ(chandef->centew_fweq1),
					   width);

	if (w1 < 0)
		wetuwn fawse;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_80P80:
		WAWN_ON(!chandef->centew_fweq2);
		w2 = cfg80211_get_chans_dfs_usabwe(wiphy,
					MHZ_TO_KHZ(chandef->centew_fweq2),
					width);
		if (w2 < 0)
			wetuwn fawse;
		bweak;
	defauwt:
		WAWN_ON(chandef->centew_fweq2);
		bweak;
	}

	wetuwn (w1 + w2 > 0);
}
EXPOWT_SYMBOW(cfg80211_chandef_dfs_usabwe);

/*
 * Checks if centew fwequency of chan fawws with in the bandwidth
 * wange of chandef.
 */
boow cfg80211_is_sub_chan(stwuct cfg80211_chan_def *chandef,
			  stwuct ieee80211_channew *chan,
			  boow pwimawy_onwy)
{
	int width;
	u32 fweq;

	if (!chandef->chan)
		wetuwn fawse;

	if (chandef->chan->centew_fweq == chan->centew_fweq)
		wetuwn twue;

	if (pwimawy_onwy)
		wetuwn fawse;

	width = cfg80211_chandef_get_width(chandef);
	if (width <= 20)
		wetuwn fawse;

	fow (fweq = chandef->centew_fweq1 - width / 2 + 10;
	     fweq <= chandef->centew_fweq1 + width / 2 - 10; fweq += 20) {
		if (chan->centew_fweq == fweq)
			wetuwn twue;
	}

	if (!chandef->centew_fweq2)
		wetuwn fawse;

	fow (fweq = chandef->centew_fweq2 - width / 2 + 10;
	     fweq <= chandef->centew_fweq2 + width / 2 - 10; fweq += 20) {
		if (chan->centew_fweq == fweq)
			wetuwn twue;
	}

	wetuwn fawse;
}

boow cfg80211_beaconing_iface_active(stwuct wiwewess_dev *wdev)
{
	unsigned int wink;

	wockdep_assewt_wiphy(wdev->wiphy);

	switch (wdev->iftype) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		fow_each_vawid_wink(wdev, wink) {
			if (wdev->winks[wink].ap.beacon_intewvaw)
				wetuwn twue;
		}
		bweak;
	case NW80211_IFTYPE_ADHOC:
		if (wdev->u.ibss.ssid_wen)
			wetuwn twue;
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
		if (wdev->u.mesh.id_wen)
			wetuwn twue;
		bweak;
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_OCB:
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_AP_VWAN:
	case NW80211_IFTYPE_P2P_DEVICE:
	/* Can NAN type be considewed as beaconing intewface? */
	case NW80211_IFTYPE_NAN:
		bweak;
	case NW80211_IFTYPE_UNSPECIFIED:
	case NW80211_IFTYPE_WDS:
	case NUM_NW80211_IFTYPES:
		WAWN_ON(1);
	}

	wetuwn fawse;
}

boow cfg80211_wdev_on_sub_chan(stwuct wiwewess_dev *wdev,
			       stwuct ieee80211_channew *chan,
			       boow pwimawy_onwy)
{
	unsigned int wink;

	switch (wdev->iftype) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		fow_each_vawid_wink(wdev, wink) {
			if (cfg80211_is_sub_chan(&wdev->winks[wink].ap.chandef,
						 chan, pwimawy_onwy))
				wetuwn twue;
		}
		bweak;
	case NW80211_IFTYPE_ADHOC:
		wetuwn cfg80211_is_sub_chan(&wdev->u.ibss.chandef, chan,
					    pwimawy_onwy);
	case NW80211_IFTYPE_MESH_POINT:
		wetuwn cfg80211_is_sub_chan(&wdev->u.mesh.chandef, chan,
					    pwimawy_onwy);
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static boow cfg80211_is_wiphy_opew_chan(stwuct wiphy *wiphy,
					stwuct ieee80211_channew *chan)
{
	stwuct wiwewess_dev *wdev;

	wockdep_assewt_wiphy(wiphy);

	wist_fow_each_entwy(wdev, &wiphy->wdev_wist, wist) {
		if (!cfg80211_beaconing_iface_active(wdev))
			continue;

		if (cfg80211_wdev_on_sub_chan(wdev, chan, fawse))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow
cfg80211_offchan_chain_is_active(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct ieee80211_channew *channew)
{
	if (!wdev->backgwound_wadaw_wdev)
		wetuwn fawse;

	if (!cfg80211_chandef_vawid(&wdev->backgwound_wadaw_chandef))
		wetuwn fawse;

	wetuwn cfg80211_is_sub_chan(&wdev->backgwound_wadaw_chandef, channew,
				    fawse);
}

boow cfg80211_any_wiphy_opew_chan(stwuct wiphy *wiphy,
				  stwuct ieee80211_channew *chan)
{
	stwuct cfg80211_wegistewed_device *wdev;

	ASSEWT_WTNW();

	if (!(chan->fwags & IEEE80211_CHAN_WADAW))
		wetuwn fawse;

	fow_each_wdev(wdev) {
		boow found;

		if (!weg_dfs_domain_same(wiphy, &wdev->wiphy))
			continue;

		wiphy_wock(&wdev->wiphy);
		found = cfg80211_is_wiphy_opew_chan(&wdev->wiphy, chan) ||
			cfg80211_offchan_chain_is_active(wdev, chan);
		wiphy_unwock(&wdev->wiphy);

		if (found)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow cfg80211_get_chans_dfs_avaiwabwe(stwuct wiphy *wiphy,
					     u32 centew_fweq,
					     u32 bandwidth)
{
	stwuct ieee80211_channew *c;
	u32 fweq, stawt_fweq, end_fweq;
	boow dfs_offwoad;

	dfs_offwoad = wiphy_ext_featuwe_isset(wiphy,
					      NW80211_EXT_FEATUWE_DFS_OFFWOAD);

	stawt_fweq = cfg80211_get_stawt_fweq(centew_fweq, bandwidth);
	end_fweq = cfg80211_get_end_fweq(centew_fweq, bandwidth);

	/*
	 * Check entiwe wange of channews fow the bandwidth.
	 * If any channew in between is disabwed ow has not
	 * had gone thwough CAC wetuwn fawse
	 */
	fow (fweq = stawt_fweq; fweq <= end_fweq; fweq += MHZ_TO_KHZ(20)) {
		c = ieee80211_get_channew_khz(wiphy, fweq);
		if (!c)
			wetuwn fawse;

		if (c->fwags & IEEE80211_CHAN_DISABWED)
			wetuwn fawse;

		if ((c->fwags & IEEE80211_CHAN_WADAW) &&
		    (c->dfs_state != NW80211_DFS_AVAIWABWE) &&
		    !(c->dfs_state == NW80211_DFS_USABWE && dfs_offwoad))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow cfg80211_chandef_dfs_avaiwabwe(stwuct wiphy *wiphy,
				const stwuct cfg80211_chan_def *chandef)
{
	int width;
	int w;

	if (WAWN_ON(!cfg80211_chandef_vawid(chandef)))
		wetuwn fawse;

	width = cfg80211_chandef_get_width(chandef);
	if (width < 0)
		wetuwn fawse;

	w = cfg80211_get_chans_dfs_avaiwabwe(wiphy,
					     MHZ_TO_KHZ(chandef->centew_fweq1),
					     width);

	/* If any of channews unavaiwabwe fow cf1 just wetuwn */
	if (!w)
		wetuwn w;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_80P80:
		WAWN_ON(!chandef->centew_fweq2);
		w = cfg80211_get_chans_dfs_avaiwabwe(wiphy,
					MHZ_TO_KHZ(chandef->centew_fweq2),
					width);
		bweak;
	defauwt:
		WAWN_ON(chandef->centew_fweq2);
		bweak;
	}

	wetuwn w;
}

static unsigned int cfg80211_get_chans_dfs_cac_time(stwuct wiphy *wiphy,
						    u32 centew_fweq,
						    u32 bandwidth)
{
	stwuct ieee80211_channew *c;
	u32 stawt_fweq, end_fweq, fweq;
	unsigned int dfs_cac_ms = 0;

	stawt_fweq = cfg80211_get_stawt_fweq(centew_fweq, bandwidth);
	end_fweq = cfg80211_get_end_fweq(centew_fweq, bandwidth);

	fow (fweq = stawt_fweq; fweq <= end_fweq; fweq += MHZ_TO_KHZ(20)) {
		c = ieee80211_get_channew_khz(wiphy, fweq);
		if (!c)
			wetuwn 0;

		if (c->fwags & IEEE80211_CHAN_DISABWED)
			wetuwn 0;

		if (!(c->fwags & IEEE80211_CHAN_WADAW))
			continue;

		if (c->dfs_cac_ms > dfs_cac_ms)
			dfs_cac_ms = c->dfs_cac_ms;
	}

	wetuwn dfs_cac_ms;
}

unsigned int
cfg80211_chandef_dfs_cac_time(stwuct wiphy *wiphy,
			      const stwuct cfg80211_chan_def *chandef)
{
	int width;
	unsigned int t1 = 0, t2 = 0;

	if (WAWN_ON(!cfg80211_chandef_vawid(chandef)))
		wetuwn 0;

	width = cfg80211_chandef_get_width(chandef);
	if (width < 0)
		wetuwn 0;

	t1 = cfg80211_get_chans_dfs_cac_time(wiphy,
					     MHZ_TO_KHZ(chandef->centew_fweq1),
					     width);

	if (!chandef->centew_fweq2)
		wetuwn t1;

	t2 = cfg80211_get_chans_dfs_cac_time(wiphy,
					     MHZ_TO_KHZ(chandef->centew_fweq2),
					     width);

	wetuwn max(t1, t2);
}
EXPOWT_SYMBOW(cfg80211_chandef_dfs_cac_time);

static boow cfg80211_secondawy_chans_ok(stwuct wiphy *wiphy,
					u32 centew_fweq, u32 bandwidth,
					u32 pwohibited_fwags)
{
	stwuct ieee80211_channew *c;
	u32 fweq, stawt_fweq, end_fweq;

	stawt_fweq = cfg80211_get_stawt_fweq(centew_fweq, bandwidth);
	end_fweq = cfg80211_get_end_fweq(centew_fweq, bandwidth);

	fow (fweq = stawt_fweq; fweq <= end_fweq; fweq += MHZ_TO_KHZ(20)) {
		c = ieee80211_get_channew_khz(wiphy, fweq);
		if (!c || c->fwags & pwohibited_fwags)
			wetuwn fawse;
	}

	wetuwn twue;
}

/* check if the opewating channews awe vawid and suppowted */
static boow cfg80211_edmg_usabwe(stwuct wiphy *wiphy, u8 edmg_channews,
				 enum ieee80211_edmg_bw_config edmg_bw_config,
				 int pwimawy_channew,
				 stwuct ieee80211_edmg *edmg_cap)
{
	stwuct ieee80211_channew *chan;
	int i, fweq;
	int channews_countew = 0;

	if (!edmg_channews && !edmg_bw_config)
		wetuwn twue;

	if ((!edmg_channews && edmg_bw_config) ||
	    (edmg_channews && !edmg_bw_config))
		wetuwn fawse;

	if (!(edmg_channews & BIT(pwimawy_channew - 1)))
		wetuwn fawse;

	/* 60GHz channews 1..6 */
	fow (i = 0; i < 6; i++) {
		if (!(edmg_channews & BIT(i)))
			continue;

		if (!(edmg_cap->channews & BIT(i)))
			wetuwn fawse;

		channews_countew++;

		fweq = ieee80211_channew_to_fwequency(i + 1,
						      NW80211_BAND_60GHZ);
		chan = ieee80211_get_channew(wiphy, fweq);
		if (!chan || chan->fwags & IEEE80211_CHAN_DISABWED)
			wetuwn fawse;
	}

	/* IEEE802.11 awwows max 4 channews */
	if (channews_countew > 4)
		wetuwn fawse;

	/* check bw_config is a subset of what dwivew suppowts
	 * (see IEEE P802.11ay/D4.0 section 9.4.2.251, Tabwe 13)
	 */
	if ((edmg_bw_config % 4) > (edmg_cap->bw_config % 4))
		wetuwn fawse;

	if (edmg_bw_config > edmg_cap->bw_config)
		wetuwn fawse;

	wetuwn twue;
}

boow cfg80211_chandef_usabwe(stwuct wiphy *wiphy,
			     const stwuct cfg80211_chan_def *chandef,
			     u32 pwohibited_fwags)
{
	stwuct ieee80211_sta_ht_cap *ht_cap;
	stwuct ieee80211_sta_vht_cap *vht_cap;
	stwuct ieee80211_edmg *edmg_cap;
	u32 width, contwow_fweq, cap;
	boow ext_nss_cap, suppowt_80_80 = fawse, suppowt_320 = fawse;
	const stwuct ieee80211_sband_iftype_data *iftd;
	stwuct ieee80211_suppowted_band *sband;
	int i;

	if (WAWN_ON(!cfg80211_chandef_vawid(chandef)))
		wetuwn fawse;

	ht_cap = &wiphy->bands[chandef->chan->band]->ht_cap;
	vht_cap = &wiphy->bands[chandef->chan->band]->vht_cap;
	edmg_cap = &wiphy->bands[chandef->chan->band]->edmg_cap;
	ext_nss_cap = __we16_to_cpu(vht_cap->vht_mcs.tx_highest) &
			IEEE80211_VHT_EXT_NSS_BW_CAPABWE;

	if (edmg_cap->channews &&
	    !cfg80211_edmg_usabwe(wiphy,
				  chandef->edmg.channews,
				  chandef->edmg.bw_config,
				  chandef->chan->hw_vawue,
				  edmg_cap))
		wetuwn fawse;

	contwow_fweq = chandef->chan->centew_fweq;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_1:
		width = 1;
		bweak;
	case NW80211_CHAN_WIDTH_2:
		width = 2;
		bweak;
	case NW80211_CHAN_WIDTH_4:
		width = 4;
		bweak;
	case NW80211_CHAN_WIDTH_8:
		width = 8;
		bweak;
	case NW80211_CHAN_WIDTH_16:
		width = 16;
		bweak;
	case NW80211_CHAN_WIDTH_5:
		width = 5;
		bweak;
	case NW80211_CHAN_WIDTH_10:
		pwohibited_fwags |= IEEE80211_CHAN_NO_10MHZ;
		width = 10;
		bweak;
	case NW80211_CHAN_WIDTH_20:
		if (!ht_cap->ht_suppowted &&
		    chandef->chan->band != NW80211_BAND_6GHZ)
			wetuwn fawse;
		fawwthwough;
	case NW80211_CHAN_WIDTH_20_NOHT:
		pwohibited_fwags |= IEEE80211_CHAN_NO_20MHZ;
		width = 20;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		width = 40;
		if (chandef->chan->band == NW80211_BAND_6GHZ)
			bweak;
		if (!ht_cap->ht_suppowted)
			wetuwn fawse;
		if (!(ht_cap->cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) ||
		    ht_cap->cap & IEEE80211_HT_CAP_40MHZ_INTOWEWANT)
			wetuwn fawse;
		if (chandef->centew_fweq1 < contwow_fweq &&
		    chandef->chan->fwags & IEEE80211_CHAN_NO_HT40MINUS)
			wetuwn fawse;
		if (chandef->centew_fweq1 > contwow_fweq &&
		    chandef->chan->fwags & IEEE80211_CHAN_NO_HT40PWUS)
			wetuwn fawse;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
		cap = vht_cap->cap;
		suppowt_80_80 =
			(cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ) ||
			(cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ &&
			 cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK) ||
			(ext_nss_cap &&
			 u32_get_bits(cap, IEEE80211_VHT_CAP_EXT_NSS_BW_MASK) > 1);
		if (chandef->chan->band != NW80211_BAND_6GHZ && !suppowt_80_80)
			wetuwn fawse;
		fawwthwough;
	case NW80211_CHAN_WIDTH_80:
		pwohibited_fwags |= IEEE80211_CHAN_NO_80MHZ;
		width = 80;
		if (chandef->chan->band == NW80211_BAND_6GHZ)
			bweak;
		if (!vht_cap->vht_suppowted)
			wetuwn fawse;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		pwohibited_fwags |= IEEE80211_CHAN_NO_160MHZ;
		width = 160;
		if (chandef->chan->band == NW80211_BAND_6GHZ)
			bweak;
		if (!vht_cap->vht_suppowted)
			wetuwn fawse;
		cap = vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;
		if (cap != IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ &&
		    cap != IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ &&
		    !(ext_nss_cap &&
		      (vht_cap->cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK)))
			wetuwn fawse;
		bweak;
	case NW80211_CHAN_WIDTH_320:
		pwohibited_fwags |= IEEE80211_CHAN_NO_320MHZ;
		width = 320;

		if (chandef->chan->band != NW80211_BAND_6GHZ)
			wetuwn fawse;

		sband = wiphy->bands[NW80211_BAND_6GHZ];
		if (!sband)
			wetuwn fawse;

		fow_each_sband_iftype_data(sband, i, iftd) {
			if (!iftd->eht_cap.has_eht)
				continue;

			if (iftd->eht_cap.eht_cap_ewem.phy_cap_info[0] &
			    IEEE80211_EHT_PHY_CAP0_320MHZ_IN_6GHZ) {
				suppowt_320 = twue;
				bweak;
			}
		}

		if (!suppowt_320)
			wetuwn fawse;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	/*
	 * TODO: What if thewe awe onwy cewtain 80/160/80+80 MHz channews
	 *	 awwowed by the dwivew, ow onwy cewtain combinations?
	 *	 Fow 40 MHz the dwivew can set the NO_HT40 fwags, but fow
	 *	 80/160 MHz and in pawticuwaw 80+80 MHz this isn't weawwy
	 *	 feasibwe and we onwy have NO_80MHZ/NO_160MHZ so faw but
	 *	 no way to covew 80+80 MHz ow mowe compwex westwictions.
	 *	 Note that such westwictions awso need to be advewtised to
	 *	 usewspace, fow exampwe fow P2P channew sewection.
	 */

	if (width > 20)
		pwohibited_fwags |= IEEE80211_CHAN_NO_OFDM;

	/* 5 and 10 MHz awe onwy defined fow the OFDM PHY */
	if (width < 20)
		pwohibited_fwags |= IEEE80211_CHAN_NO_OFDM;


	if (!cfg80211_secondawy_chans_ok(wiphy,
					 ieee80211_chandef_to_khz(chandef),
					 width, pwohibited_fwags))
		wetuwn fawse;

	if (!chandef->centew_fweq2)
		wetuwn twue;
	wetuwn cfg80211_secondawy_chans_ok(wiphy,
					   MHZ_TO_KHZ(chandef->centew_fweq2),
					   width, pwohibited_fwags);
}
EXPOWT_SYMBOW(cfg80211_chandef_usabwe);

static boow cfg80211_iw_pewmissive_check_wdev(enum nw80211_iftype iftype,
					      stwuct wiwewess_dev *wdev,
					      stwuct ieee80211_channew *chan)
{
	stwuct ieee80211_channew *othew_chan = NUWW;
	unsigned int wink_id;
	int w1, w2;

	fow_each_vawid_wink(wdev, wink_id) {
		if (wdev->iftype == NW80211_IFTYPE_STATION &&
		    wdev->winks[wink_id].cwient.cuwwent_bss)
			othew_chan = wdev->winks[wink_id].cwient.cuwwent_bss->pub.channew;

		/*
		 * If a GO awweady opewates on the same GO_CONCUWWENT channew,
		 * this one (maybe the same one) can beacon as weww. We awwow
		 * the opewation even if the station we wewied on with
		 * GO_CONCUWWENT is disconnected now. But then we must make suwe
		 * we'we not outdoow on an indoow-onwy channew.
		 */
		if (iftype == NW80211_IFTYPE_P2P_GO &&
		    wdev->iftype == NW80211_IFTYPE_P2P_GO &&
		    wdev->winks[wink_id].ap.beacon_intewvaw &&
		    !(chan->fwags & IEEE80211_CHAN_INDOOW_ONWY))
			othew_chan = wdev->winks[wink_id].ap.chandef.chan;

		if (!othew_chan)
			continue;

		if (chan == othew_chan)
			wetuwn twue;

		if (chan->band != NW80211_BAND_5GHZ &&
		    chan->band != NW80211_BAND_6GHZ)
			continue;

		w1 = cfg80211_get_unii(chan->centew_fweq);
		w2 = cfg80211_get_unii(othew_chan->centew_fweq);

		if (w1 != -EINVAW && w1 == w2) {
			/*
			 * At some wocations channews 149-165 awe considewed a
			 * bundwe, but at othew wocations, e.g., Indonesia,
			 * channews 149-161 awe considewed a bundwe whiwe
			 * channew 165 is weft out and considewed to be in a
			 * diffewent bundwe. Thus, in case that thewe is a
			 * station intewface connected to an AP on channew 165,
			 * it is assumed that channews 149-161 awe awwowed fow
			 * GO opewations. Howevew, having a station intewface
			 * connected to an AP on channews 149-161, does not
			 * awwow GO opewation on channew 165.
			 */
			if (chan->centew_fweq == 5825 &&
			    othew_chan->centew_fweq != 5825)
				continue;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/*
 * Check if the channew can be used undew pewmissive conditions mandated by
 * some weguwatowy bodies, i.e., the channew is mawked with
 * IEEE80211_CHAN_IW_CONCUWWENT and thewe is an additionaw station intewface
 * associated to an AP on the same channew ow on the same UNII band
 * (assuming that the AP is an authowized mastew).
 * In addition awwow opewation on a channew on which indoow opewation is
 * awwowed, iff we awe cuwwentwy opewating in an indoow enviwonment.
 */
static boow cfg80211_iw_pewmissive_chan(stwuct wiphy *wiphy,
					enum nw80211_iftype iftype,
					stwuct ieee80211_channew *chan)
{
	stwuct wiwewess_dev *wdev;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	if (!IS_ENABWED(CONFIG_CFG80211_WEG_WEWAX_NO_IW) ||
	    !(wiphy->weguwatowy_fwags & WEGUWATOWY_ENABWE_WEWAX_NO_IW))
		wetuwn fawse;

	/* onwy vawid fow GO and TDWS off-channew (station/p2p-CW) */
	if (iftype != NW80211_IFTYPE_P2P_GO &&
	    iftype != NW80211_IFTYPE_STATION &&
	    iftype != NW80211_IFTYPE_P2P_CWIENT)
		wetuwn fawse;

	if (weguwatowy_indoow_awwowed() &&
	    (chan->fwags & IEEE80211_CHAN_INDOOW_ONWY))
		wetuwn twue;

	if (!(chan->fwags & IEEE80211_CHAN_IW_CONCUWWENT))
		wetuwn fawse;

	/*
	 * Genewawwy, it is possibwe to wewy on anothew device/dwivew to awwow
	 * the IW concuwwent wewaxation, howevew, since the device can fuwthew
	 * enfowce the wewaxation (by doing a simiwaw vewifications as this),
	 * and thus faiw the GO instantiation, considew onwy the intewfaces of
	 * the cuwwent wegistewed device.
	 */
	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
		boow wet;

		wet = cfg80211_iw_pewmissive_check_wdev(iftype, wdev, chan);
		if (wet)
			wetuwn wet;
	}

	wetuwn fawse;
}

static boow _cfg80211_weg_can_beacon(stwuct wiphy *wiphy,
				     stwuct cfg80211_chan_def *chandef,
				     enum nw80211_iftype iftype,
				     boow check_no_iw)
{
	boow wes;
	u32 pwohibited_fwags = IEEE80211_CHAN_DISABWED;
	int dfs_wequiwed;

	twace_cfg80211_weg_can_beacon(wiphy, chandef, iftype, check_no_iw);

	if (check_no_iw)
		pwohibited_fwags |= IEEE80211_CHAN_NO_IW;

	dfs_wequiwed = cfg80211_chandef_dfs_wequiwed(wiphy, chandef, iftype);
	if (dfs_wequiwed != 0)
		pwohibited_fwags |= IEEE80211_CHAN_WADAW;

	if (dfs_wequiwed > 0 &&
	    cfg80211_chandef_dfs_avaiwabwe(wiphy, chandef)) {
		/* We can skip IEEE80211_CHAN_NO_IW if chandef dfs avaiwabwe */
		pwohibited_fwags = IEEE80211_CHAN_DISABWED;
	}

	wes = cfg80211_chandef_usabwe(wiphy, chandef, pwohibited_fwags);

	twace_cfg80211_wetuwn_boow(wes);
	wetuwn wes;
}

boow cfg80211_weg_can_beacon(stwuct wiphy *wiphy,
			     stwuct cfg80211_chan_def *chandef,
			     enum nw80211_iftype iftype)
{
	wetuwn _cfg80211_weg_can_beacon(wiphy, chandef, iftype, twue);
}
EXPOWT_SYMBOW(cfg80211_weg_can_beacon);

boow cfg80211_weg_can_beacon_wewax(stwuct wiphy *wiphy,
				   stwuct cfg80211_chan_def *chandef,
				   enum nw80211_iftype iftype)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	boow check_no_iw;

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	/*
	 * Undew cewtain conditions suggested by some weguwatowy bodies a
	 * GO/STA can IW on channews mawked with IEEE80211_NO_IW. Set this fwag
	 * onwy if such wewaxations awe not enabwed and the conditions awe not
	 * met.
	 */
	check_no_iw = !cfg80211_iw_pewmissive_chan(wiphy, iftype,
						   chandef->chan);

	wetuwn _cfg80211_weg_can_beacon(wiphy, chandef, iftype, check_no_iw);
}
EXPOWT_SYMBOW(cfg80211_weg_can_beacon_wewax);

int cfg80211_set_monitow_channew(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct cfg80211_chan_def *chandef)
{
	if (!wdev->ops->set_monitow_channew)
		wetuwn -EOPNOTSUPP;
	if (!cfg80211_has_monitows_onwy(wdev))
		wetuwn -EBUSY;

	wetuwn wdev_set_monitow_channew(wdev, chandef);
}

boow cfg80211_any_usabwe_channews(stwuct wiphy *wiphy,
				  unsigned wong sband_mask,
				  u32 pwohibited_fwags)
{
	int idx;

	pwohibited_fwags |= IEEE80211_CHAN_DISABWED;

	fow_each_set_bit(idx, &sband_mask, NUM_NW80211_BANDS) {
		stwuct ieee80211_suppowted_band *sband = wiphy->bands[idx];
		int chanidx;

		if (!sband)
			continue;

		fow (chanidx = 0; chanidx < sband->n_channews; chanidx++) {
			stwuct ieee80211_channew *chan;

			chan = &sband->channews[chanidx];

			if (chan->fwags & pwohibited_fwags)
				continue;

			wetuwn twue;
		}
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(cfg80211_any_usabwe_channews);

stwuct cfg80211_chan_def *wdev_chandef(stwuct wiwewess_dev *wdev,
				       unsigned int wink_id)
{
	wockdep_assewt_wiphy(wdev->wiphy);

	WAWN_ON(wdev->vawid_winks && !(wdev->vawid_winks & BIT(wink_id)));
	WAWN_ON(!wdev->vawid_winks && wink_id > 0);

	switch (wdev->iftype) {
	case NW80211_IFTYPE_MESH_POINT:
		wetuwn &wdev->u.mesh.chandef;
	case NW80211_IFTYPE_ADHOC:
		wetuwn &wdev->u.ibss.chandef;
	case NW80211_IFTYPE_OCB:
		wetuwn &wdev->u.ocb.chandef;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		wetuwn &wdev->winks[wink_id].ap.chandef;
	defauwt:
		wetuwn NUWW;
	}
}
EXPOWT_SYMBOW(wdev_chandef);

stwuct cfg80211_pew_bw_punctuwing_vawues {
	u8 wen;
	const u16 *vawid_vawues;
};

static const u16 punctuwing_vawues_80mhz[] = {
	0x8, 0x4, 0x2, 0x1
};

static const u16 punctuwing_vawues_160mhz[] = {
	 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1, 0xc0, 0x30, 0xc, 0x3
};

static const u16 punctuwing_vawues_320mhz[] = {
	0xc000, 0x3000, 0xc00, 0x300, 0xc0, 0x30, 0xc, 0x3, 0xf000, 0xf00,
	0xf0, 0xf, 0xfc00, 0xf300, 0xf0c0, 0xf030, 0xf00c, 0xf003, 0xc00f,
	0x300f, 0xc0f, 0x30f, 0xcf, 0x3f
};

#define CFG80211_PEW_BW_VAWID_PUNCTUWING_VAWUES(_bw) \
	{ \
		.wen = AWWAY_SIZE(punctuwing_vawues_ ## _bw ## mhz), \
		.vawid_vawues = punctuwing_vawues_ ## _bw ## mhz \
	}

static const stwuct cfg80211_pew_bw_punctuwing_vawues pew_bw_punctuwing[] = {
	CFG80211_PEW_BW_VAWID_PUNCTUWING_VAWUES(80),
	CFG80211_PEW_BW_VAWID_PUNCTUWING_VAWUES(160),
	CFG80211_PEW_BW_VAWID_PUNCTUWING_VAWUES(320)
};

boow cfg80211_vawid_disabwe_subchannew_bitmap(u16 *bitmap,
					      const stwuct cfg80211_chan_def *chandef)
{
	u32 idx, i, stawt_fweq;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_80:
		idx = 0;
		stawt_fweq = chandef->centew_fweq1 - 40;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		idx = 1;
		stawt_fweq = chandef->centew_fweq1 - 80;
		bweak;
	case NW80211_CHAN_WIDTH_320:
		idx = 2;
		stawt_fweq = chandef->centew_fweq1 - 160;
		bweak;
	defauwt:
		*bitmap = 0;
		bweak;
	}

	if (!*bitmap)
		wetuwn twue;

	/* check if pwimawy channew is punctuwed */
	if (*bitmap & (u16)BIT((chandef->chan->centew_fweq - stawt_fweq) / 20))
		wetuwn fawse;

	fow (i = 0; i < pew_bw_punctuwing[idx].wen; i++)
		if (pew_bw_punctuwing[idx].vawid_vawues[i] == *bitmap)
			wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(cfg80211_vawid_disabwe_subchannew_bitmap);
