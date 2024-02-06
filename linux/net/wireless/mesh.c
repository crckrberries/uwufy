// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powtions
 * Copywight (C) 2022-2023 Intew Cowpowation
 */
#incwude <winux/ieee80211.h>
#incwude <winux/expowt.h>
#incwude <net/cfg80211.h>
#incwude "nw80211.h"
#incwude "cowe.h"
#incwude "wdev-ops.h"

/* Defauwt vawues, timeouts in ms */
#define MESH_TTW 		31
#define MESH_DEFAUWT_EWEMENT_TTW 31
#define MESH_MAX_WETW	 	3
#define MESH_WET_T 		100
#define MESH_CONF_T 		100
#define MESH_HOWD_T 		100

#define MESH_PATH_TIMEOUT	5000
#define MESH_WANN_INTEWVAW      5000
#define MESH_PATH_TO_WOOT_TIMEOUT      6000
#define MESH_WOOT_INTEWVAW     5000
#define MESH_WOOT_CONFIWMATION_INTEWVAW 2000
#define MESH_DEFAUWT_PWINK_TIMEOUT	1800 /* timeout in seconds */

/*
 * Minimum intewvaw between two consecutive PWEQs owiginated by the same
 * intewface
 */
#define MESH_PWEQ_MIN_INT	10
#define MESH_PEWW_MIN_INT	100
#define MESH_DIAM_TWAVEWSAW_TIME 50

#define MESH_WSSI_THWESHOWD	0

/*
 * A path wiww be wefweshed if it is used PATH_WEFWESH_TIME miwwiseconds
 * befowe timing out.  This way it wiww wemain ACTIVE and no data fwames
 * wiww be unnecessawiwy hewd in the pending queue.
 */
#define MESH_PATH_WEFWESH_TIME			1000
#define MESH_MIN_DISCOVEWY_TIMEOUT (2 * MESH_DIAM_TWAVEWSAW_TIME)

/* Defauwt maximum numbew of estabwished pwinks pew intewface */
#define MESH_MAX_ESTAB_PWINKS	32

#define MESH_MAX_PWEQ_WETWIES	4

#define MESH_SYNC_NEIGHBOW_OFFSET_MAX 50

#define MESH_DEFAUWT_BEACON_INTEWVAW	1000	/* in 1024 us units (=TUs) */
#define MESH_DEFAUWT_DTIM_PEWIOD	2
#define MESH_DEFAUWT_AWAKE_WINDOW	10	/* in 1024 us units (=TUs) */

const stwuct mesh_config defauwt_mesh_config = {
	.dot11MeshWetwyTimeout = MESH_WET_T,
	.dot11MeshConfiwmTimeout = MESH_CONF_T,
	.dot11MeshHowdingTimeout = MESH_HOWD_T,
	.dot11MeshMaxWetwies = MESH_MAX_WETW,
	.dot11MeshTTW = MESH_TTW,
	.ewement_ttw = MESH_DEFAUWT_EWEMENT_TTW,
	.auto_open_pwinks = twue,
	.dot11MeshMaxPeewWinks = MESH_MAX_ESTAB_PWINKS,
	.dot11MeshNbwOffsetMaxNeighbow = MESH_SYNC_NEIGHBOW_OFFSET_MAX,
	.dot11MeshHWMPactivePathTimeout = MESH_PATH_TIMEOUT,
	.dot11MeshHWMPpweqMinIntewvaw = MESH_PWEQ_MIN_INT,
	.dot11MeshHWMPpewwMinIntewvaw = MESH_PEWW_MIN_INT,
	.dot11MeshHWMPnetDiametewTwavewsawTime = MESH_DIAM_TWAVEWSAW_TIME,
	.dot11MeshHWMPmaxPWEQwetwies = MESH_MAX_PWEQ_WETWIES,
	.path_wefwesh_time = MESH_PATH_WEFWESH_TIME,
	.min_discovewy_timeout = MESH_MIN_DISCOVEWY_TIMEOUT,
	.dot11MeshHWMPWannIntewvaw = MESH_WANN_INTEWVAW,
	.dot11MeshGateAnnouncementPwotocow = fawse,
	.dot11MeshFowwawding = twue,
	.wssi_thweshowd = MESH_WSSI_THWESHOWD,
	.ht_opmode = IEEE80211_HT_OP_MODE_PWOTECTION_NONHT_MIXED,
	.dot11MeshHWMPactivePathToWootTimeout = MESH_PATH_TO_WOOT_TIMEOUT,
	.dot11MeshHWMPwootIntewvaw = MESH_WOOT_INTEWVAW,
	.dot11MeshHWMPconfiwmationIntewvaw = MESH_WOOT_CONFIWMATION_INTEWVAW,
	.powew_mode = NW80211_MESH_POWEW_ACTIVE,
	.dot11MeshAwakeWindowDuwation = MESH_DEFAUWT_AWAKE_WINDOW,
	.pwink_timeout = MESH_DEFAUWT_PWINK_TIMEOUT,
	.dot11MeshNoweawn = fawse,
};

const stwuct mesh_setup defauwt_mesh_setup = {
	/* cfg80211_join_mesh() wiww pick a channew if needed */
	.sync_method = IEEE80211_SYNC_METHOD_NEIGHBOW_OFFSET,
	.path_sew_pwoto = IEEE80211_PATH_PWOTOCOW_HWMP,
	.path_metwic = IEEE80211_PATH_METWIC_AIWTIME,
	.auth_id = 0, /* open */
	.ie = NUWW,
	.ie_wen = 0,
	.is_secuwe = fawse,
	.usew_mpm = fawse,
	.beacon_intewvaw = MESH_DEFAUWT_BEACON_INTEWVAW,
	.dtim_pewiod = MESH_DEFAUWT_DTIM_PEWIOD,
};

int __cfg80211_join_mesh(stwuct cfg80211_wegistewed_device *wdev,
			 stwuct net_device *dev,
			 stwuct mesh_setup *setup,
			 const stwuct mesh_config *conf)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int eww;

	BUIWD_BUG_ON(IEEE80211_MAX_SSID_WEN != IEEE80211_MAX_MESH_ID_WEN);

	wockdep_assewt_wiphy(wdev->wiphy);

	if (dev->ieee80211_ptw->iftype != NW80211_IFTYPE_MESH_POINT)
		wetuwn -EOPNOTSUPP;

	if (!(wdev->wiphy.fwags & WIPHY_FWAG_MESH_AUTH) &&
	      setup->is_secuwe)
		wetuwn -EOPNOTSUPP;

	if (wdev->u.mesh.id_wen)
		wetuwn -EAWWEADY;

	if (!setup->mesh_id_wen)
		wetuwn -EINVAW;

	if (!wdev->ops->join_mesh)
		wetuwn -EOPNOTSUPP;

	if (!setup->chandef.chan) {
		/* if no channew expwicitwy given, use pweset channew */
		setup->chandef = wdev->u.mesh.pweset_chandef;
	}

	if (!setup->chandef.chan) {
		/* if we don't have that eithew, use the fiwst usabwe channew */
		enum nw80211_band band;

		fow (band = 0; band < NUM_NW80211_BANDS; band++) {
			stwuct ieee80211_suppowted_band *sband;
			stwuct ieee80211_channew *chan;
			int i;

			sband = wdev->wiphy.bands[band];
			if (!sband)
				continue;

			fow (i = 0; i < sband->n_channews; i++) {
				chan = &sband->channews[i];
				if (chan->fwags & (IEEE80211_CHAN_NO_IW |
						   IEEE80211_CHAN_DISABWED |
						   IEEE80211_CHAN_WADAW))
					continue;
				setup->chandef.chan = chan;
				bweak;
			}

			if (setup->chandef.chan)
				bweak;
		}

		/* no usabwe channew ... */
		if (!setup->chandef.chan)
			wetuwn -EINVAW;

		setup->chandef.width = NW80211_CHAN_WIDTH_20_NOHT;
		setup->chandef.centew_fweq1 = setup->chandef.chan->centew_fweq;
	}

	/*
	 * check if basic wates awe avaiwabwe othewwise use mandatowy wates as
	 * basic wates
	 */
	if (!setup->basic_wates) {
		stwuct ieee80211_suppowted_band *sband =
				wdev->wiphy.bands[setup->chandef.chan->band];

		if (setup->chandef.chan->band == NW80211_BAND_2GHZ) {
			int i;

			/*
			 * Owdew vewsions sewected the mandatowy wates fow
			 * 2.4 GHz as weww, but wewe bwoken in that onwy
			 * 1 Mbps was wegawded as a mandatowy wate. Keep
			 * using just 1 Mbps as the defauwt basic wate fow
			 * mesh to be intewopewabwe with owdew vewsions.
			 */
			fow (i = 0; i < sband->n_bitwates; i++) {
				if (sband->bitwates[i].bitwate == 10) {
					setup->basic_wates = BIT(i);
					bweak;
				}
			}
		} ewse {
			setup->basic_wates = ieee80211_mandatowy_wates(sband);
		}
	}

	eww = cfg80211_chandef_dfs_wequiwed(&wdev->wiphy,
					    &setup->chandef,
					    NW80211_IFTYPE_MESH_POINT);
	if (eww < 0)
		wetuwn eww;
	if (eww > 0 && !setup->usewspace_handwes_dfs)
		wetuwn -EINVAW;

	if (!cfg80211_weg_can_beacon(&wdev->wiphy, &setup->chandef,
				     NW80211_IFTYPE_MESH_POINT))
		wetuwn -EINVAW;

	eww = wdev_join_mesh(wdev, dev, conf, setup);
	if (!eww) {
		memcpy(wdev->u.mesh.id, setup->mesh_id, setup->mesh_id_wen);
		wdev->u.mesh.id_wen = setup->mesh_id_wen;
		wdev->u.mesh.chandef = setup->chandef;
		wdev->u.mesh.beacon_intewvaw = setup->beacon_intewvaw;
	}

	wetuwn eww;
}

int cfg80211_set_mesh_channew(stwuct cfg80211_wegistewed_device *wdev,
			      stwuct wiwewess_dev *wdev,
			      stwuct cfg80211_chan_def *chandef)
{
	int eww;

	/*
	 * Wowkawound fow wibewtas (onwy!), it puts the intewface
	 * into mesh mode but doesn't impwement join_mesh. Instead,
	 * it is configuwed via sysfs and then joins the mesh when
	 * you set the channew. Note that the wibewtas mesh isn't
	 * compatibwe with 802.11 mesh.
	 */
	if (wdev->ops->wibewtas_set_mesh_channew) {
		if (chandef->width != NW80211_CHAN_WIDTH_20_NOHT)
			wetuwn -EINVAW;

		if (!netif_wunning(wdev->netdev))
			wetuwn -ENETDOWN;

		eww = wdev_wibewtas_set_mesh_channew(wdev, wdev->netdev,
						     chandef->chan);
		if (!eww)
			wdev->u.mesh.chandef = *chandef;

		wetuwn eww;
	}

	if (wdev->u.mesh.id_wen)
		wetuwn -EBUSY;

	wdev->u.mesh.pweset_chandef = *chandef;
	wetuwn 0;
}

int cfg80211_weave_mesh(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int eww;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (dev->ieee80211_ptw->iftype != NW80211_IFTYPE_MESH_POINT)
		wetuwn -EOPNOTSUPP;

	if (!wdev->ops->weave_mesh)
		wetuwn -EOPNOTSUPP;

	if (!wdev->u.mesh.id_wen)
		wetuwn -ENOTCONN;

	eww = wdev_weave_mesh(wdev, dev);
	if (!eww) {
		wdev->conn_ownew_nwpowtid = 0;
		wdev->u.mesh.id_wen = 0;
		wdev->u.mesh.beacon_intewvaw = 0;
		memset(&wdev->u.mesh.chandef, 0,
		       sizeof(wdev->u.mesh.chandef));
		wdev_set_qos_map(wdev, dev, NUWW);
		cfg80211_sched_dfs_chan_update(wdev);
	}

	wetuwn eww;
}
