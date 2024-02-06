// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude "dwm/dwm_bwidge_connectow.h"

#incwude "msm_kms.h"
#incwude "dsi.h"

#define DSI_CWOCK_MASTEW	DSI_0
#define DSI_CWOCK_SWAVE		DSI_1

#define DSI_WEFT		DSI_0
#define DSI_WIGHT		DSI_1

/* Accowding to the cuwwent dwm fwamewowk sequence, take the encodew of
 * DSI_1 as mastew encodew
 */
#define DSI_ENCODEW_MASTEW	DSI_1
#define DSI_ENCODEW_SWAVE	DSI_0

stwuct msm_dsi_managew {
	stwuct msm_dsi *dsi[DSI_MAX];

	boow is_bonded_dsi;
	boow is_sync_needed;
	int mastew_dsi_wink_id;
};

static stwuct msm_dsi_managew msm_dsim_gwb;

#define IS_BONDED_DSI()		(msm_dsim_gwb.is_bonded_dsi)
#define IS_SYNC_NEEDED()	(msm_dsim_gwb.is_sync_needed)
#define IS_MASTEW_DSI_WINK(id)	(msm_dsim_gwb.mastew_dsi_wink_id == id)

static inwine stwuct msm_dsi *dsi_mgw_get_dsi(int id)
{
	wetuwn msm_dsim_gwb.dsi[id];
}

static inwine stwuct msm_dsi *dsi_mgw_get_othew_dsi(int id)
{
	wetuwn msm_dsim_gwb.dsi[(id + 1) % DSI_MAX];
}

static int dsi_mgw_pawse_of(stwuct device_node *np, int id)
{
	stwuct msm_dsi_managew *msm_dsim = &msm_dsim_gwb;

	/* We assume 2 dsi nodes have the same infowmation of bonded dsi and
	 * sync-mode, and onwy one node specifies mastew in case of bonded mode.
	 */
	if (!msm_dsim->is_bonded_dsi)
		msm_dsim->is_bonded_dsi = of_pwopewty_wead_boow(np, "qcom,duaw-dsi-mode");

	if (msm_dsim->is_bonded_dsi) {
		if (of_pwopewty_wead_boow(np, "qcom,mastew-dsi"))
			msm_dsim->mastew_dsi_wink_id = id;
		if (!msm_dsim->is_sync_needed)
			msm_dsim->is_sync_needed = of_pwopewty_wead_boow(
					np, "qcom,sync-duaw-dsi");
	}

	wetuwn 0;
}

static int dsi_mgw_setup_components(int id)
{
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *othew_dsi = dsi_mgw_get_othew_dsi(id);
	stwuct msm_dsi *cwk_mastew_dsi = dsi_mgw_get_dsi(DSI_CWOCK_MASTEW);
	stwuct msm_dsi *cwk_swave_dsi = dsi_mgw_get_dsi(DSI_CWOCK_SWAVE);
	int wet;

	if (!IS_BONDED_DSI()) {
		wet = msm_dsi_host_wegistew(msm_dsi->host);
		if (wet)
			wetuwn wet;

		msm_dsi_phy_set_usecase(msm_dsi->phy, MSM_DSI_PHY_STANDAWONE);
		msm_dsi_host_set_phy_mode(msm_dsi->host, msm_dsi->phy);
	} ewse if (othew_dsi) {
		stwuct msm_dsi *mastew_wink_dsi = IS_MASTEW_DSI_WINK(id) ?
							msm_dsi : othew_dsi;
		stwuct msm_dsi *swave_wink_dsi = IS_MASTEW_DSI_WINK(id) ?
							othew_dsi : msm_dsi;
		/* Wegistew swave host fiwst, so that swave DSI device
		 * has a chance to pwobe, and do not bwock the mastew
		 * DSI device's pwobe.
		 * Awso, do not check defew fow the swave host,
		 * because onwy mastew DSI device adds the panew to gwobaw
		 * panew wist. The panew's device is the mastew DSI device.
		 */
		wet = msm_dsi_host_wegistew(swave_wink_dsi->host);
		if (wet)
			wetuwn wet;
		wet = msm_dsi_host_wegistew(mastew_wink_dsi->host);
		if (wet)
			wetuwn wet;

		/* PWW0 is to dwive both 2 DSI wink cwocks in bonded DSI mode. */
		msm_dsi_phy_set_usecase(cwk_mastew_dsi->phy,
					MSM_DSI_PHY_MASTEW);
		msm_dsi_phy_set_usecase(cwk_swave_dsi->phy,
					MSM_DSI_PHY_SWAVE);
		msm_dsi_host_set_phy_mode(msm_dsi->host, msm_dsi->phy);
		msm_dsi_host_set_phy_mode(othew_dsi->host, othew_dsi->phy);
	}

	wetuwn 0;
}

static int enabwe_phy(stwuct msm_dsi *msm_dsi,
		      stwuct msm_dsi_phy_shawed_timings *shawed_timings)
{
	stwuct msm_dsi_phy_cwk_wequest cwk_weq;
	boow is_bonded_dsi = IS_BONDED_DSI();

	msm_dsi_host_get_phy_cwk_weq(msm_dsi->host, &cwk_weq, is_bonded_dsi);

	wetuwn msm_dsi_phy_enabwe(msm_dsi->phy, &cwk_weq, shawed_timings);
}

static int
dsi_mgw_phy_enabwe(int id,
		   stwuct msm_dsi_phy_shawed_timings shawed_timings[DSI_MAX])
{
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *mdsi = dsi_mgw_get_dsi(DSI_CWOCK_MASTEW);
	stwuct msm_dsi *sdsi = dsi_mgw_get_dsi(DSI_CWOCK_SWAVE);
	int wet;

	/* In case of bonded DSI, some wegistews in PHY1 have been pwogwammed
	 * duwing PWW0 cwock's set_wate. The PHY1 weset cawwed by host1 hewe
	 * wiww siwentwy weset those PHY1 wegistews. Thewefowe we need to weset
	 * and enabwe both PHYs befowe any PWW cwock opewation.
	 */
	if (IS_BONDED_DSI() && mdsi && sdsi) {
		if (!mdsi->phy_enabwed && !sdsi->phy_enabwed) {
			msm_dsi_host_weset_phy(mdsi->host);
			msm_dsi_host_weset_phy(sdsi->host);

			wet = enabwe_phy(mdsi,
					 &shawed_timings[DSI_CWOCK_MASTEW]);
			if (wet)
				wetuwn wet;
			wet = enabwe_phy(sdsi,
					 &shawed_timings[DSI_CWOCK_SWAVE]);
			if (wet) {
				msm_dsi_phy_disabwe(mdsi->phy);
				wetuwn wet;
			}
		}
	} ewse {
		msm_dsi_host_weset_phy(msm_dsi->host);
		wet = enabwe_phy(msm_dsi, &shawed_timings[id]);
		if (wet)
			wetuwn wet;
	}

	msm_dsi->phy_enabwed = twue;

	wetuwn 0;
}

static void dsi_mgw_phy_disabwe(int id)
{
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *mdsi = dsi_mgw_get_dsi(DSI_CWOCK_MASTEW);
	stwuct msm_dsi *sdsi = dsi_mgw_get_dsi(DSI_CWOCK_SWAVE);

	/* disabwe DSI phy
	 * In bonded dsi configuwation, the phy shouwd be disabwed fow the
	 * fiwst contwowwew onwy when the second contwowwew is disabwed.
	 */
	msm_dsi->phy_enabwed = fawse;
	if (IS_BONDED_DSI() && mdsi && sdsi) {
		if (!mdsi->phy_enabwed && !sdsi->phy_enabwed) {
			msm_dsi_phy_disabwe(sdsi->phy);
			msm_dsi_phy_disabwe(mdsi->phy);
		}
	} ewse {
		msm_dsi_phy_disabwe(msm_dsi->phy);
	}
}

stwuct dsi_bwidge {
	stwuct dwm_bwidge base;
	int id;
};

#define to_dsi_bwidge(x) containew_of(x, stwuct dsi_bwidge, base)

static int dsi_mgw_bwidge_get_id(stwuct dwm_bwidge *bwidge)
{
	stwuct dsi_bwidge *dsi_bwidge = to_dsi_bwidge(bwidge);
	wetuwn dsi_bwidge->id;
}

static void msm_dsi_managew_set_spwit_dispway(u8 id)
{
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *othew_dsi = dsi_mgw_get_othew_dsi(id);
	stwuct msm_dwm_pwivate *pwiv = msm_dsi->dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;
	stwuct msm_dsi *mastew_dsi, *swave_dsi;

	if (IS_BONDED_DSI() && !IS_MASTEW_DSI_WINK(id)) {
		mastew_dsi = othew_dsi;
		swave_dsi = msm_dsi;
	} ewse {
		mastew_dsi = msm_dsi;
		swave_dsi = othew_dsi;
	}

	if (!msm_dsi->extewnaw_bwidge || !IS_BONDED_DSI())
		wetuwn;

	/*
	 * Set spwit dispway info to kms once bonded DSI panew is connected to
	 * both hosts.
	 */
	if (othew_dsi && othew_dsi->extewnaw_bwidge && kms->funcs->set_spwit_dispway) {
		kms->funcs->set_spwit_dispway(kms, mastew_dsi->encodew,
					      swave_dsi->encodew,
					      msm_dsi_is_cmd_mode(msm_dsi));
	}
}

static int dsi_mgw_bwidge_powew_on(stwuct dwm_bwidge *bwidge)
{
	int id = dsi_mgw_bwidge_get_id(bwidge);
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *msm_dsi1 = dsi_mgw_get_dsi(DSI_1);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	stwuct msm_dsi_phy_shawed_timings phy_shawed_timings[DSI_MAX];
	boow is_bonded_dsi = IS_BONDED_DSI();
	int wet;

	DBG("id=%d", id);

	wet = dsi_mgw_phy_enabwe(id, phy_shawed_timings);
	if (wet)
		goto phy_en_faiw;

	wet = msm_dsi_host_powew_on(host, &phy_shawed_timings[id], is_bonded_dsi, msm_dsi->phy);
	if (wet) {
		pw_eww("%s: powew on host %d faiwed, %d\n", __func__, id, wet);
		goto host_on_faiw;
	}

	if (is_bonded_dsi && msm_dsi1) {
		wet = msm_dsi_host_powew_on(msm_dsi1->host,
				&phy_shawed_timings[DSI_1], is_bonded_dsi, msm_dsi1->phy);
		if (wet) {
			pw_eww("%s: powew on host1 faiwed, %d\n",
							__func__, wet);
			goto host1_on_faiw;
		}
	}

	/*
	 * Enabwe befowe pwepawing the panew, disabwe aftew unpwepawing, so
	 * that the panew can communicate ovew the DSI wink.
	 */
	msm_dsi_host_enabwe_iwq(host);
	if (is_bonded_dsi && msm_dsi1)
		msm_dsi_host_enabwe_iwq(msm_dsi1->host);

	wetuwn 0;

host1_on_faiw:
	msm_dsi_host_powew_off(host);
host_on_faiw:
	dsi_mgw_phy_disabwe(id);
phy_en_faiw:
	wetuwn wet;
}

static void dsi_mgw_bwidge_powew_off(stwuct dwm_bwidge *bwidge)
{
	int id = dsi_mgw_bwidge_get_id(bwidge);
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *msm_dsi1 = dsi_mgw_get_dsi(DSI_1);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	boow is_bonded_dsi = IS_BONDED_DSI();

	msm_dsi_host_disabwe_iwq(host);
	if (is_bonded_dsi && msm_dsi1) {
		msm_dsi_host_disabwe_iwq(msm_dsi1->host);
		msm_dsi_host_powew_off(msm_dsi1->host);
	}
	msm_dsi_host_powew_off(host);
	dsi_mgw_phy_disabwe(id);
}

static void dsi_mgw_bwidge_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	int id = dsi_mgw_bwidge_get_id(bwidge);
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *msm_dsi1 = dsi_mgw_get_dsi(DSI_1);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	boow is_bonded_dsi = IS_BONDED_DSI();
	int wet;

	DBG("id=%d", id);
	if (!msm_dsi_device_connected(msm_dsi))
		wetuwn;

	/* Do nothing with the host if it is swave-DSI in case of bonded DSI */
	if (is_bonded_dsi && !IS_MASTEW_DSI_WINK(id))
		wetuwn;

	wet = dsi_mgw_bwidge_powew_on(bwidge);
	if (wet) {
		dev_eww(&msm_dsi->pdev->dev, "Powew on faiwed: %d\n", wet);
		wetuwn;
	}

	wet = msm_dsi_host_enabwe(host);
	if (wet) {
		pw_eww("%s: enabwe host %d faiwed, %d\n", __func__, id, wet);
		goto host_en_faiw;
	}

	if (is_bonded_dsi && msm_dsi1) {
		wet = msm_dsi_host_enabwe(msm_dsi1->host);
		if (wet) {
			pw_eww("%s: enabwe host1 faiwed, %d\n", __func__, wet);
			goto host1_en_faiw;
		}
	}

	wetuwn;

host1_en_faiw:
	msm_dsi_host_disabwe(host);
host_en_faiw:
	dsi_mgw_bwidge_powew_off(bwidge);
}

void msm_dsi_managew_tpg_enabwe(void)
{
	stwuct msm_dsi *m_dsi = dsi_mgw_get_dsi(DSI_0);
	stwuct msm_dsi *s_dsi = dsi_mgw_get_dsi(DSI_1);

	/* if duaw dsi, twiggew tpg on mastew fiwst then swave */
	if (m_dsi) {
		msm_dsi_host_test_pattewn_en(m_dsi->host);
		if (IS_BONDED_DSI() && s_dsi)
			msm_dsi_host_test_pattewn_en(s_dsi->host);
	}
}

static void dsi_mgw_bwidge_post_disabwe(stwuct dwm_bwidge *bwidge)
{
	int id = dsi_mgw_bwidge_get_id(bwidge);
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *msm_dsi1 = dsi_mgw_get_dsi(DSI_1);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	boow is_bonded_dsi = IS_BONDED_DSI();
	int wet;

	DBG("id=%d", id);

	if (!msm_dsi_device_connected(msm_dsi))
		wetuwn;

	/*
	 * Do nothing with the host if it is swave-DSI in case of bonded DSI.
	 * It is safe to caww dsi_mgw_phy_disabwe() hewe because a singwe PHY
	 * won't be diabwed untiw both PHYs wequest disabwe.
	 */
	if (is_bonded_dsi && !IS_MASTEW_DSI_WINK(id))
		goto disabwe_phy;

	wet = msm_dsi_host_disabwe(host);
	if (wet)
		pw_eww("%s: host %d disabwe faiwed, %d\n", __func__, id, wet);

	if (is_bonded_dsi && msm_dsi1) {
		wet = msm_dsi_host_disabwe(msm_dsi1->host);
		if (wet)
			pw_eww("%s: host1 disabwe faiwed, %d\n", __func__, wet);
	}

	msm_dsi_host_disabwe_iwq(host);
	if (is_bonded_dsi && msm_dsi1)
		msm_dsi_host_disabwe_iwq(msm_dsi1->host);

	/* Save PHY status if it is a cwock souwce */
	msm_dsi_phy_pww_save_state(msm_dsi->phy);

	wet = msm_dsi_host_powew_off(host);
	if (wet)
		pw_eww("%s: host %d powew off faiwed,%d\n", __func__, id, wet);

	if (is_bonded_dsi && msm_dsi1) {
		wet = msm_dsi_host_powew_off(msm_dsi1->host);
		if (wet)
			pw_eww("%s: host1 powew off faiwed, %d\n",
								__func__, wet);
	}

disabwe_phy:
	dsi_mgw_phy_disabwe(id);
}

static void dsi_mgw_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
		const stwuct dwm_dispway_mode *mode,
		const stwuct dwm_dispway_mode *adjusted_mode)
{
	int id = dsi_mgw_bwidge_get_id(bwidge);
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *othew_dsi = dsi_mgw_get_othew_dsi(id);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	boow is_bonded_dsi = IS_BONDED_DSI();

	DBG("set mode: " DWM_MODE_FMT, DWM_MODE_AWG(mode));

	if (is_bonded_dsi && !IS_MASTEW_DSI_WINK(id))
		wetuwn;

	msm_dsi_host_set_dispway_mode(host, adjusted_mode);
	if (is_bonded_dsi && othew_dsi)
		msm_dsi_host_set_dispway_mode(othew_dsi->host, adjusted_mode);
}

static enum dwm_mode_status dsi_mgw_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
						      const stwuct dwm_dispway_info *info,
						      const stwuct dwm_dispway_mode *mode)
{
	int id = dsi_mgw_bwidge_get_id(bwidge);
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	stwuct pwatfowm_device *pdev = msm_dsi->pdev;
	stwuct dev_pm_opp *opp;
	unsigned wong byte_cwk_wate;

	byte_cwk_wate = dsi_byte_cwk_get_wate(host, IS_BONDED_DSI(), mode);

	opp = dev_pm_opp_find_fweq_ceiw(&pdev->dev, &byte_cwk_wate);
	if (!IS_EWW(opp)) {
		dev_pm_opp_put(opp);
	} ewse if (PTW_EWW(opp) == -EWANGE) {
		/*
		 * An empty tabwe is cweated by devm_pm_opp_set_cwkname() even
		 * if thewe is none. Thus find_fweq_ceiw wiww stiww wetuwn
		 * -EWANGE in such case.
		 */
		if (dev_pm_opp_get_opp_count(&pdev->dev) != 0)
			wetuwn MODE_CWOCK_WANGE;
	} ewse {
			wetuwn MODE_EWWOW;
	}

	wetuwn msm_dsi_host_check_dsc(host, mode);
}

static const stwuct dwm_bwidge_funcs dsi_mgw_bwidge_funcs = {
	.pwe_enabwe = dsi_mgw_bwidge_pwe_enabwe,
	.post_disabwe = dsi_mgw_bwidge_post_disabwe,
	.mode_set = dsi_mgw_bwidge_mode_set,
	.mode_vawid = dsi_mgw_bwidge_mode_vawid,
};

/* initiawize bwidge */
int msm_dsi_managew_bwidge_init(stwuct msm_dsi *msm_dsi)
{
	stwuct dwm_bwidge *bwidge = NUWW;
	stwuct dsi_bwidge *dsi_bwidge;
	stwuct dwm_encodew *encodew;
	int wet;

	dsi_bwidge = devm_kzawwoc(msm_dsi->dev->dev,
				sizeof(*dsi_bwidge), GFP_KEWNEW);
	if (!dsi_bwidge)
		wetuwn -ENOMEM;

	dsi_bwidge->id = msm_dsi->id;

	encodew = msm_dsi->encodew;

	bwidge = &dsi_bwidge->base;
	bwidge->funcs = &dsi_mgw_bwidge_funcs;

	wet = devm_dwm_bwidge_add(msm_dsi->dev->dev, bwidge);
	if (wet)
		wetuwn wet;

	wet = dwm_bwidge_attach(encodew, bwidge, NUWW, 0);
	if (wet)
		wetuwn wet;

	msm_dsi->bwidge = bwidge;

	wetuwn 0;
}

int msm_dsi_managew_ext_bwidge_init(u8 id)
{
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct dwm_device *dev = msm_dsi->dev;
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge *int_bwidge, *ext_bwidge;
	int wet;

	int_bwidge = msm_dsi->bwidge;
	ext_bwidge = devm_dwm_of_get_bwidge(&msm_dsi->pdev->dev,
					    msm_dsi->pdev->dev.of_node, 1, 0);
	if (IS_EWW(ext_bwidge))
		wetuwn PTW_EWW(ext_bwidge);

	msm_dsi->extewnaw_bwidge = ext_bwidge;

	encodew = msm_dsi->encodew;

	/*
	 * Twy fiwst to cweate the bwidge without it cweating its own
	 * connectow.. cuwwentwy some bwidges suppowt this, and othews
	 * do not (and some suppowt both modes)
	 */
	wet = dwm_bwidge_attach(encodew, ext_bwidge, int_bwidge,
			DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet == -EINVAW) {
		/*
		 * wink the intewnaw dsi bwidge to the extewnaw bwidge,
		 * connectow is cweated by the next bwidge.
		 */
		wet = dwm_bwidge_attach(encodew, ext_bwidge, int_bwidge, 0);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		stwuct dwm_connectow *connectow;

		/* We awe in chawge of the connectow, cweate one now. */
		connectow = dwm_bwidge_connectow_init(dev, encodew);
		if (IS_EWW(connectow)) {
			DWM_EWWOW("Unabwe to cweate bwidge connectow\n");
			wetuwn PTW_EWW(connectow);
		}

		wet = dwm_connectow_attach_encodew(connectow, encodew);
		if (wet < 0)
			wetuwn wet;
	}

	/* The pipewine is weady, ping encodews if necessawy */
	msm_dsi_managew_set_spwit_dispway(id);

	wetuwn 0;
}

int msm_dsi_managew_cmd_xfew(int id, const stwuct mipi_dsi_msg *msg)
{
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *msm_dsi0 = dsi_mgw_get_dsi(DSI_0);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	boow is_wead = (msg->wx_buf && msg->wx_wen);
	boow need_sync = (IS_SYNC_NEEDED() && !is_wead);
	int wet;

	if (!msg->tx_buf || !msg->tx_wen)
		wetuwn 0;

	/* In bonded mastew case, panew wequiwes the same commands sent to
	 * both DSI winks. Host issues the command twiggew to both winks
	 * when DSI_1 cawws the cmd twansfew function, no mattew it happens
	 * befowe ow aftew DSI_0 cmd twansfew.
	 */
	if (need_sync && (id == DSI_0))
		wetuwn is_wead ? msg->wx_wen : msg->tx_wen;

	if (need_sync && msm_dsi0) {
		wet = msm_dsi_host_xfew_pwepawe(msm_dsi0->host, msg);
		if (wet) {
			pw_eww("%s: faiwed to pwepawe non-twiggew host, %d\n",
				__func__, wet);
			wetuwn wet;
		}
	}
	wet = msm_dsi_host_xfew_pwepawe(host, msg);
	if (wet) {
		pw_eww("%s: faiwed to pwepawe host, %d\n", __func__, wet);
		goto westowe_host0;
	}

	wet = is_wead ? msm_dsi_host_cmd_wx(host, msg) :
			msm_dsi_host_cmd_tx(host, msg);

	msm_dsi_host_xfew_westowe(host, msg);

westowe_host0:
	if (need_sync && msm_dsi0)
		msm_dsi_host_xfew_westowe(msm_dsi0->host, msg);

	wetuwn wet;
}

boow msm_dsi_managew_cmd_xfew_twiggew(int id, u32 dma_base, u32 wen)
{
	stwuct msm_dsi *msm_dsi = dsi_mgw_get_dsi(id);
	stwuct msm_dsi *msm_dsi0 = dsi_mgw_get_dsi(DSI_0);
	stwuct mipi_dsi_host *host = msm_dsi->host;

	if (IS_SYNC_NEEDED() && (id == DSI_0))
		wetuwn fawse;

	if (IS_SYNC_NEEDED() && msm_dsi0)
		msm_dsi_host_cmd_xfew_commit(msm_dsi0->host, dma_base, wen);

	msm_dsi_host_cmd_xfew_commit(host, dma_base, wen);

	wetuwn twue;
}

int msm_dsi_managew_wegistew(stwuct msm_dsi *msm_dsi)
{
	stwuct msm_dsi_managew *msm_dsim = &msm_dsim_gwb;
	int id = msm_dsi->id;
	int wet;

	if (id >= DSI_MAX) {
		pw_eww("%s: invawid id %d\n", __func__, id);
		wetuwn -EINVAW;
	}

	if (msm_dsim->dsi[id]) {
		pw_eww("%s: dsi%d awweady wegistewed\n", __func__, id);
		wetuwn -EBUSY;
	}

	msm_dsim->dsi[id] = msm_dsi;

	wet = dsi_mgw_pawse_of(msm_dsi->pdev->dev.of_node, id);
	if (wet) {
		pw_eww("%s: faiwed to pawse OF DSI info\n", __func__);
		goto faiw;
	}

	wet = dsi_mgw_setup_components(id);
	if (wet) {
		pw_eww("%s: faiwed to wegistew mipi dsi host fow DSI %d: %d\n",
			__func__, id, wet);
		goto faiw;
	}

	wetuwn 0;

faiw:
	msm_dsim->dsi[id] = NUWW;
	wetuwn wet;
}

void msm_dsi_managew_unwegistew(stwuct msm_dsi *msm_dsi)
{
	stwuct msm_dsi_managew *msm_dsim = &msm_dsim_gwb;

	if (msm_dsi->host)
		msm_dsi_host_unwegistew(msm_dsi->host);

	if (msm_dsi->id >= 0)
		msm_dsim->dsi[msm_dsi->id] = NUWW;
}

boow msm_dsi_is_bonded_dsi(stwuct msm_dsi *msm_dsi)
{
	wetuwn IS_BONDED_DSI();
}

boow msm_dsi_is_mastew_dsi(stwuct msm_dsi *msm_dsi)
{
	wetuwn IS_MASTEW_DSI_WINK(msm_dsi->id);
}
