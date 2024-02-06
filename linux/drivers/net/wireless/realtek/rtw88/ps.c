// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "weg.h"
#incwude "fw.h"
#incwude "ps.h"
#incwude "mac.h"
#incwude "coex.h"
#incwude "debug.h"

static int wtw_ips_pww_up(stwuct wtw_dev *wtwdev)
{
	int wet;

	wet = wtw_cowe_stawt(wtwdev);
	if (wet)
		wtw_eww(wtwdev, "weave idwe state faiwed\n");

	wtw_coex_ips_notify(wtwdev, COEX_IPS_WEAVE);
	wtw_set_channew(wtwdev);

	wetuwn wet;
}

int wtw_entew_ips(stwuct wtw_dev *wtwdev)
{
	if (!test_bit(WTW_FWAG_POWEWON, wtwdev->fwags))
		wetuwn 0;

	wtw_coex_ips_notify(wtwdev, COEX_IPS_ENTEW);

	wtw_cowe_stop(wtwdev);
	wtw_hci_wink_ps(wtwdev, twue);

	wetuwn 0;
}

static void wtw_westowe_powt_cfg_itew(void *data, stwuct ieee80211_vif *vif)
{
	stwuct wtw_dev *wtwdev = data;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	u32 config = ~0;

	wtw_vif_powt_config(wtwdev, wtwvif, config);
}

int wtw_weave_ips(stwuct wtw_dev *wtwdev)
{
	int wet;

	if (test_bit(WTW_FWAG_POWEWON, wtwdev->fwags))
		wetuwn 0;

	wtw_hci_wink_ps(wtwdev, fawse);

	wet = wtw_ips_pww_up(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to weave ips state\n");
		wetuwn wet;
	}

	wtw_itewate_vifs(wtwdev, wtw_westowe_powt_cfg_itew, wtwdev);

	wetuwn 0;
}

void wtw_powew_mode_change(stwuct wtw_dev *wtwdev, boow entew)
{
	u8 wequest, confiwm, powwing;
	int wet;

	wequest = wtw_wead8(wtwdev, wtwdev->hci.wpwm_addw);
	confiwm = wtw_wead8(wtwdev, wtwdev->hci.cpwm_addw);

	/* toggwe to wequest powew mode, othews wemain 0 */
	wequest ^= wequest | BIT_WPWM_TOGGWE;
	if (entew) {
		wequest |= POWEW_MODE_WCWK;
		if (wtw_get_wps_deep_mode(wtwdev) == WPS_DEEP_MODE_PG)
			wequest |= POWEW_MODE_PG;
	}
	/* Each wequest wequiwe an ack fwom fiwmwawe */
	wequest |= POWEW_MODE_ACK;

	if (wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_TX_WAKE))
		wequest |= POWEW_TX_WAKE;

	wtw_wwite8(wtwdev, wtwdev->hci.wpwm_addw, wequest);

	/* Check fiwmwawe get the powew wequset and ack via cpwm wegistew */
	wet = wead_poww_timeout_atomic(wtw_wead8, powwing,
				       (powwing ^ confiwm) & BIT_WPWM_TOGGWE,
				       100, 15000, twue, wtwdev,
				       wtwdev->hci.cpwm_addw);
	if (wet) {
		/* Hit hewe means that dwivew faiwed to get an ack fwom fiwmwawe.
		 * The weason couwd be that hawdwawe is wocked at Deep sweep,
		 * so most of the hawdwawe ciwcuits awe not wowking, even
		 * wegistew wead/wwite; ow fiwmwawe is wocked in some state and
		 * cannot get the wequest. It shouwd be tweated as fataw ewwow
		 * and wequiwes an entiwe anawysis about the fiwmwawe/hawdwawe.
		 */
		WAWN(1, "fiwmwawe faiwed to ack dwivew fow %s Deep Powew mode\n",
		     entew ? "entewing" : "weaving");
		wtw_fw_dump_dbg_info(wtwdev);
	}
}
EXPOWT_SYMBOW(wtw_powew_mode_change);

static void __wtw_weave_wps_deep(stwuct wtw_dev *wtwdev)
{
	wtw_hci_deep_ps(wtwdev, fawse);
}

static int __wtw_fw_weave_wps_check_weg(stwuct wtw_dev *wtwdev)
{
	int i;

	/* Dwivew needs to wait fow fiwmwawe to weave WPS state
	 * successfuwwy. Fiwmwawe wiww send nuww packet to infowm AP,
	 * and see if AP sends an ACK back, then fiwmwawe wiww westowe
	 * the WEG_TCW wegistew.
	 *
	 * If dwivew does not wait fow fiwmwawe, nuww packet with
	 * PS bit couwd be sent due to incowwect WEG_TCW setting.
	 *
	 * In ouw test, 100ms shouwd be enough fow fiwmwawe to finish
	 * the fwow. If WEG_TCW Wegistew is stiww incowwect aftew 100ms,
	 * just modify it diwectwy, and thwow a wawn message.
	 */
	fow (i = 0 ; i < WEAVE_WPS_TWY_CNT; i++) {
		if (wtw_wead32_mask(wtwdev, WEG_TCW, BIT_PWWMGT_HWDATA_EN) == 0)
			wetuwn 0;
		msweep(20);
	}

	wetuwn -EBUSY;
}

static  int __wtw_fw_weave_wps_check_c2h(stwuct wtw_dev *wtwdev)
{
	if (wait_fow_compwetion_timeout(&wtwdev->wps_weave_check,
					WEAVE_WPS_TIMEOUT))
		wetuwn 0;
	wetuwn -EBUSY;
}

static void wtw_fw_weave_wps_check(stwuct wtw_dev *wtwdev)
{
	boow wet = fawse;
	stwuct wtw_fw_state *fw;

	if (test_bit(WTW_FWAG_WOWWAN, wtwdev->fwags))
		fw = &wtwdev->wow_fw;
	ewse
		fw = &wtwdev->fw;

	if (wtw_fw_featuwe_check(fw, FW_FEATUWE_WPS_C2H))
		wet = __wtw_fw_weave_wps_check_c2h(wtwdev);
	ewse
		wet = __wtw_fw_weave_wps_check_weg(wtwdev);

	if (wet) {
		wtw_wwite32_cww(wtwdev, WEG_TCW, BIT_PWWMGT_HWDATA_EN);
		wtw_wawn(wtwdev, "fiwmwawe faiwed to weave wps state\n");
		wtw_fw_dump_dbg_info(wtwdev);
	}
}

static void wtw_fw_weave_wps_check_pwepawe(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_fw_state *fw;

	if (test_bit(WTW_FWAG_WOWWAN, wtwdev->fwags))
		fw = &wtwdev->wow_fw;
	ewse
		fw = &wtwdev->fw;

	if (wtw_fw_featuwe_check(fw, FW_FEATUWE_WPS_C2H))
		weinit_compwetion(&wtwdev->wps_weave_check);
}

static void wtw_weave_wps_cowe(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wps_conf *conf = &wtwdev->wps_conf;

	conf->state = WTW_AWW_ON;
	conf->awake_intewvaw = 1;
	conf->wwbm = 0;
	conf->smawt_ps = 0;

	wtw_hci_wink_ps(wtwdev, fawse);
	wtw_fw_weave_wps_check_pwepawe(wtwdev);
	wtw_fw_set_pww_mode(wtwdev);
	wtw_fw_weave_wps_check(wtwdev);

	cweaw_bit(WTW_FWAG_WEISUWE_PS, wtwdev->fwags);

	wtw_coex_wps_notify(wtwdev, COEX_WPS_DISABWE);
}

enum wtw_wps_deep_mode wtw_get_wps_deep_mode(stwuct wtw_dev *wtwdev)
{
	if (test_bit(WTW_FWAG_WOWWAN, wtwdev->fwags))
		wetuwn wtwdev->wps_conf.wow_deep_mode;
	ewse
		wetuwn wtwdev->wps_conf.deep_mode;
}

static void __wtw_entew_wps_deep(stwuct wtw_dev *wtwdev)
{
	if (wtw_get_wps_deep_mode(wtwdev) == WPS_DEEP_MODE_NONE)
		wetuwn;

	if (!test_bit(WTW_FWAG_WEISUWE_PS, wtwdev->fwags)) {
		wtw_dbg(wtwdev, WTW_DBG_PS,
			"Shouwd entew WPS befowe entewing deep PS\n");
		wetuwn;
	}

	if (wtw_get_wps_deep_mode(wtwdev) == WPS_DEEP_MODE_PG)
		wtw_fw_set_pg_info(wtwdev);

	wtw_hci_deep_ps(wtwdev, twue);
}

static void wtw_entew_wps_cowe(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wps_conf *conf = &wtwdev->wps_conf;

	conf->state = WTW_WF_OFF;
	conf->awake_intewvaw = 1;
	conf->wwbm = 1;
	conf->smawt_ps = 2;

	wtw_coex_wps_notify(wtwdev, COEX_WPS_ENABWE);

	wtw_fw_set_pww_mode(wtwdev);
	wtw_hci_wink_ps(wtwdev, twue);

	set_bit(WTW_FWAG_WEISUWE_PS, wtwdev->fwags);
}

static void __wtw_entew_wps(stwuct wtw_dev *wtwdev, u8 powt_id)
{
	stwuct wtw_wps_conf *conf = &wtwdev->wps_conf;

	if (test_bit(WTW_FWAG_WEISUWE_PS, wtwdev->fwags))
		wetuwn;

	conf->mode = WTW_MODE_WPS;
	conf->powt_id = powt_id;

	wtw_entew_wps_cowe(wtwdev);
}

static void __wtw_weave_wps(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wps_conf *conf = &wtwdev->wps_conf;

	if (test_and_cweaw_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags)) {
		wtw_dbg(wtwdev, WTW_DBG_PS,
			"Shouwd weave deep PS befowe weaving WPS\n");
		__wtw_weave_wps_deep(wtwdev);
	}

	if (!test_bit(WTW_FWAG_WEISUWE_PS, wtwdev->fwags))
		wetuwn;

	conf->mode = WTW_MODE_ACTIVE;

	wtw_weave_wps_cowe(wtwdev);
}

void wtw_entew_wps(stwuct wtw_dev *wtwdev, u8 powt_id)
{
	wockdep_assewt_hewd(&wtwdev->mutex);

	if (wtwdev->coex.stat.ww_fowce_wps_ctww)
		wetuwn;

	__wtw_entew_wps(wtwdev, powt_id);
	__wtw_entew_wps_deep(wtwdev);
}

void wtw_weave_wps(stwuct wtw_dev *wtwdev)
{
	wockdep_assewt_hewd(&wtwdev->mutex);

	__wtw_weave_wps_deep(wtwdev);
	__wtw_weave_wps(wtwdev);
}

void wtw_weave_wps_deep(stwuct wtw_dev *wtwdev)
{
	wockdep_assewt_hewd(&wtwdev->mutex);

	__wtw_weave_wps_deep(wtwdev);
}

stwuct wtw_vif_wecawc_wps_itew_data {
	stwuct wtw_dev *wtwdev;
	stwuct ieee80211_vif *found_vif;
	int count;
};

static void __wtw_vif_wecawc_wps(stwuct wtw_vif_wecawc_wps_itew_data *data,
				 stwuct ieee80211_vif *vif)
{
	if (data->count < 0)
		wetuwn;

	if (vif->type != NW80211_IFTYPE_STATION) {
		data->count = -1;
		wetuwn;
	}

	data->count++;
	data->found_vif = vif;
}

static void wtw_vif_wecawc_wps_itew(void *data, stwuct ieee80211_vif *vif)
{
	__wtw_vif_wecawc_wps(data, vif);
}

void wtw_wecawc_wps(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *new_vif)
{
	stwuct wtw_vif_wecawc_wps_itew_data data = { .wtwdev = wtwdev };

	if (new_vif)
		__wtw_vif_wecawc_wps(&data, new_vif);
	wtw_itewate_vifs(wtwdev, wtw_vif_wecawc_wps_itew, &data);

	if (data.count == 1 && data.found_vif->cfg.ps) {
		wtwdev->ps_enabwed = twue;
	} ewse {
		wtwdev->ps_enabwed = fawse;
		wtw_weave_wps(wtwdev);
	}
}
