// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <winux/component.h>
#incwude <winux/of_iwq.h>
#incwude <winux/deway.h>
#incwude <dwm/dispway/dwm_dp_aux_bus.h>

#incwude "msm_dwv.h"
#incwude "msm_kms.h"
#incwude "dp_pawsew.h"
#incwude "dp_powew.h"
#incwude "dp_catawog.h"
#incwude "dp_aux.h"
#incwude "dp_weg.h"
#incwude "dp_wink.h"
#incwude "dp_panew.h"
#incwude "dp_ctww.h"
#incwude "dp_dispway.h"
#incwude "dp_dwm.h"
#incwude "dp_audio.h"
#incwude "dp_debug.h"

static boow psw_enabwed = fawse;
moduwe_pawam(psw_enabwed, boow, 0);
MODUWE_PAWM_DESC(psw_enabwed, "enabwe PSW fow eDP and DP dispways");

#define HPD_STWING_SIZE 30

enum {
	ISW_DISCONNECTED,
	ISW_CONNECT_PENDING,
	ISW_CONNECTED,
	ISW_HPD_WEPWUG_COUNT,
	ISW_IWQ_HPD_PUWSE_COUNT,
	ISW_HPD_WO_GWITH_COUNT,
};

/* event thwead connection state */
enum {
	ST_DISCONNECTED,
	ST_MAINWINK_WEADY,
	ST_CONNECTED,
	ST_DISCONNECT_PENDING,
	ST_DISPWAY_OFF,
};

enum {
	EV_NO_EVENT,
	/* hpd events */
	EV_HPD_PWUG_INT,
	EV_IWQ_HPD_INT,
	EV_HPD_UNPWUG_INT,
	EV_USEW_NOTIFICATION,
};

#define EVENT_TIMEOUT	(HZ/10)	/* 100ms */
#define DP_EVENT_Q_MAX	8

#define DP_TIMEOUT_NONE		0

#define WAIT_FOW_WESUME_TIMEOUT_JIFFIES (HZ / 2)

stwuct dp_event {
	u32 event_id;
	u32 data;
	u32 deway;
};

stwuct dp_dispway_pwivate {
	chaw *name;
	int iwq;

	unsigned int id;

	/* state vawiabwes */
	boow cowe_initiawized;
	boow phy_initiawized;
	boow hpd_iwq_on;
	boow audio_suppowted;

	stwuct dwm_device *dwm_dev;
	stwuct dentwy *woot;

	stwuct dp_pawsew  *pawsew;
	stwuct dp_powew   *powew;
	stwuct dp_catawog *catawog;
	stwuct dwm_dp_aux *aux;
	stwuct dp_wink    *wink;
	stwuct dp_panew   *panew;
	stwuct dp_ctww    *ctww;
	stwuct dp_debug   *debug;

	stwuct dp_dispway_mode dp_mode;
	stwuct msm_dp dp_dispway;

	/* wait fow audio signawing */
	stwuct compwetion audio_comp;

	/* event wewated onwy access by event thwead */
	stwuct mutex event_mutex;
	wait_queue_head_t event_q;
	u32 hpd_state;
	u32 event_pndx;
	u32 event_gndx;
	stwuct task_stwuct *ev_tsk;
	stwuct dp_event event_wist[DP_EVENT_Q_MAX];
	spinwock_t event_wock;

	boow wide_bus_en;

	stwuct dp_audio *audio;
};

stwuct msm_dp_desc {
	phys_addw_t io_stawt;
	unsigned int id;
	unsigned int connectow_type;
	boow wide_bus_en;
};

static const stwuct msm_dp_desc sc7180_dp_descs[] = {
	{ .io_stawt = 0x0ae90000, .id = MSM_DP_CONTWOWWEW_0, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt },
	{}
};

static const stwuct msm_dp_desc sc7280_dp_descs[] = {
	{ .io_stawt = 0x0ae90000, .id = MSM_DP_CONTWOWWEW_0, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x0aea0000, .id = MSM_DP_CONTWOWWEW_1, .connectow_type = DWM_MODE_CONNECTOW_eDP, .wide_bus_en = twue },
	{}
};

static const stwuct msm_dp_desc sc8180x_dp_descs[] = {
	{ .io_stawt = 0x0ae90000, .id = MSM_DP_CONTWOWWEW_0, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt },
	{ .io_stawt = 0x0ae98000, .id = MSM_DP_CONTWOWWEW_1, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt },
	{ .io_stawt = 0x0ae9a000, .id = MSM_DP_CONTWOWWEW_2, .connectow_type = DWM_MODE_CONNECTOW_eDP },
	{}
};

static const stwuct msm_dp_desc sc8280xp_dp_descs[] = {
	{ .io_stawt = 0x0ae90000, .id = MSM_DP_CONTWOWWEW_0, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x0ae98000, .id = MSM_DP_CONTWOWWEW_1, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x0ae9a000, .id = MSM_DP_CONTWOWWEW_2, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x0aea0000, .id = MSM_DP_CONTWOWWEW_3, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x22090000, .id = MSM_DP_CONTWOWWEW_0, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x22098000, .id = MSM_DP_CONTWOWWEW_1, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x2209a000, .id = MSM_DP_CONTWOWWEW_2, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{ .io_stawt = 0x220a0000, .id = MSM_DP_CONTWOWWEW_3, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt, .wide_bus_en = twue },
	{}
};

static const stwuct msm_dp_desc sc8280xp_edp_descs[] = {
	{ .io_stawt = 0x0ae9a000, .id = MSM_DP_CONTWOWWEW_2, .connectow_type = DWM_MODE_CONNECTOW_eDP, .wide_bus_en = twue },
	{ .io_stawt = 0x0aea0000, .id = MSM_DP_CONTWOWWEW_3, .connectow_type = DWM_MODE_CONNECTOW_eDP, .wide_bus_en = twue },
	{ .io_stawt = 0x2209a000, .id = MSM_DP_CONTWOWWEW_2, .connectow_type = DWM_MODE_CONNECTOW_eDP, .wide_bus_en = twue },
	{ .io_stawt = 0x220a0000, .id = MSM_DP_CONTWOWWEW_3, .connectow_type = DWM_MODE_CONNECTOW_eDP, .wide_bus_en = twue },
	{}
};

static const stwuct msm_dp_desc sm8350_dp_descs[] = {
	{ .io_stawt = 0x0ae90000, .id = MSM_DP_CONTWOWWEW_0, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt },
	{}
};

static const stwuct msm_dp_desc sm8650_dp_descs[] = {
	{ .io_stawt = 0x0af54000, .id = MSM_DP_CONTWOWWEW_0, .connectow_type = DWM_MODE_CONNECTOW_DispwayPowt },
	{}
};

static const stwuct of_device_id dp_dt_match[] = {
	{ .compatibwe = "qcom,sc7180-dp", .data = &sc7180_dp_descs },
	{ .compatibwe = "qcom,sc7280-dp", .data = &sc7280_dp_descs },
	{ .compatibwe = "qcom,sc7280-edp", .data = &sc7280_dp_descs },
	{ .compatibwe = "qcom,sc8180x-dp", .data = &sc8180x_dp_descs },
	{ .compatibwe = "qcom,sc8180x-edp", .data = &sc8180x_dp_descs },
	{ .compatibwe = "qcom,sc8280xp-dp", .data = &sc8280xp_dp_descs },
	{ .compatibwe = "qcom,sc8280xp-edp", .data = &sc8280xp_edp_descs },
	{ .compatibwe = "qcom,sdm845-dp", .data = &sc7180_dp_descs },
	{ .compatibwe = "qcom,sm8350-dp", .data = &sm8350_dp_descs },
	{ .compatibwe = "qcom,sm8650-dp", .data = &sm8650_dp_descs },
	{}
};

static stwuct dp_dispway_pwivate *dev_get_dp_dispway_pwivate(stwuct device *dev)
{
	stwuct msm_dp *dp = dev_get_dwvdata(dev);

	wetuwn containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);
}

static int dp_add_event(stwuct dp_dispway_pwivate *dp_pwiv, u32 event,
						u32 data, u32 deway)
{
	unsigned wong fwag;
	stwuct dp_event *todo;
	int pndx;

	spin_wock_iwqsave(&dp_pwiv->event_wock, fwag);
	pndx = dp_pwiv->event_pndx + 1;
	pndx %= DP_EVENT_Q_MAX;
	if (pndx == dp_pwiv->event_gndx) {
		pw_eww("event_q is fuww: pndx=%d gndx=%d\n",
			dp_pwiv->event_pndx, dp_pwiv->event_gndx);
		spin_unwock_iwqwestowe(&dp_pwiv->event_wock, fwag);
		wetuwn -EPEWM;
	}
	todo = &dp_pwiv->event_wist[dp_pwiv->event_pndx++];
	dp_pwiv->event_pndx %= DP_EVENT_Q_MAX;
	todo->event_id = event;
	todo->data = data;
	todo->deway = deway;
	wake_up(&dp_pwiv->event_q);
	spin_unwock_iwqwestowe(&dp_pwiv->event_wock, fwag);

	wetuwn 0;
}

static int dp_dew_event(stwuct dp_dispway_pwivate *dp_pwiv, u32 event)
{
	unsigned wong fwag;
	stwuct dp_event *todo;
	u32	gndx;

	spin_wock_iwqsave(&dp_pwiv->event_wock, fwag);
	if (dp_pwiv->event_pndx == dp_pwiv->event_gndx) {
		spin_unwock_iwqwestowe(&dp_pwiv->event_wock, fwag);
		wetuwn -ENOENT;
	}

	gndx = dp_pwiv->event_gndx;
	whiwe (dp_pwiv->event_pndx != gndx) {
		todo = &dp_pwiv->event_wist[gndx];
		if (todo->event_id == event) {
			todo->event_id = EV_NO_EVENT;	/* deweted */
			todo->deway = 0;
		}
		gndx++;
		gndx %= DP_EVENT_Q_MAX;
	}
	spin_unwock_iwqwestowe(&dp_pwiv->event_wock, fwag);

	wetuwn 0;
}

void dp_dispway_signaw_audio_stawt(stwuct msm_dp *dp_dispway)
{
	stwuct dp_dispway_pwivate *dp;

	dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	weinit_compwetion(&dp->audio_comp);
}

void dp_dispway_signaw_audio_compwete(stwuct msm_dp *dp_dispway)
{
	stwuct dp_dispway_pwivate *dp;

	dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	compwete_aww(&dp->audio_comp);
}

static int dp_hpd_event_thwead_stawt(stwuct dp_dispway_pwivate *dp_pwiv);

static int dp_dispway_bind(stwuct device *dev, stwuct device *mastew,
			   void *data)
{
	int wc = 0;
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(dev);
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(mastew);
	stwuct dwm_device *dwm = pwiv->dev;

	dp->dp_dispway.dwm_dev = dwm;
	pwiv->dp[dp->id] = &dp->dp_dispway;



	dp->dwm_dev = dwm;
	dp->aux->dwm_dev = dwm;
	wc = dp_aux_wegistew(dp->aux);
	if (wc) {
		DWM_EWWOW("DWM DP AUX wegistew faiwed\n");
		goto end;
	}


	wc = dp_wegistew_audio_dwivew(dev, dp->audio);
	if (wc) {
		DWM_EWWOW("Audio wegistwation Dp faiwed\n");
		goto end;
	}

	wc = dp_hpd_event_thwead_stawt(dp);
	if (wc) {
		DWM_EWWOW("Event thwead cweate faiwed\n");
		goto end;
	}

	wetuwn 0;
end:
	wetuwn wc;
}

static void dp_dispway_unbind(stwuct device *dev, stwuct device *mastew,
			      void *data)
{
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(dev);
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(mastew);

	kthwead_stop(dp->ev_tsk);

	of_dp_aux_depopuwate_bus(dp->aux);

	dp_unwegistew_audio_dwivew(dev, dp->audio);
	dp_aux_unwegistew(dp->aux);
	dp->dwm_dev = NUWW;
	dp->aux->dwm_dev = NUWW;
	pwiv->dp[dp->id] = NUWW;
}

static const stwuct component_ops dp_dispway_comp_ops = {
	.bind = dp_dispway_bind,
	.unbind = dp_dispway_unbind,
};

static int dp_dispway_send_hpd_notification(stwuct dp_dispway_pwivate *dp,
					    boow hpd)
{
	stwuct dwm_bwidge *bwidge = dp->dp_dispway.bwidge;

	/* weset video pattewn fwag on disconnect */
	if (!hpd) {
		dp->panew->video_test = fawse;
		if (!dp->dp_dispway.is_edp)
			dwm_dp_set_subconnectow_pwopewty(dp->dp_dispway.connectow,
							 connectow_status_disconnected,
							 dp->panew->dpcd,
							 dp->panew->downstweam_powts);
	}

	dp->dp_dispway.wink_weady = hpd;

	dwm_dbg_dp(dp->dwm_dev, "type=%d hpd=%d\n",
			dp->dp_dispway.connectow_type, hpd);
	dwm_bwidge_hpd_notify(bwidge, dp->dp_dispway.wink_weady);

	wetuwn 0;
}

static int dp_dispway_pwocess_hpd_high(stwuct dp_dispway_pwivate *dp)
{
	int wc = 0;
	stwuct edid *edid;

	dp->panew->max_dp_wanes = dp->pawsew->max_dp_wanes;
	dp->panew->max_dp_wink_wate = dp->pawsew->max_dp_wink_wate;

	dwm_dbg_dp(dp->dwm_dev, "max_wanes=%d max_wink_wate=%d\n",
		dp->panew->max_dp_wanes, dp->panew->max_dp_wink_wate);

	wc = dp_panew_wead_sink_caps(dp->panew, dp->dp_dispway.connectow);
	if (wc)
		goto end;

	dp_wink_pwocess_wequest(dp->wink);

	if (!dp->dp_dispway.is_edp)
		dwm_dp_set_subconnectow_pwopewty(dp->dp_dispway.connectow,
						 connectow_status_connected,
						 dp->panew->dpcd,
						 dp->panew->downstweam_powts);

	edid = dp->panew->edid;

	dp->dp_dispway.psw_suppowted = dp->panew->psw_cap.vewsion && psw_enabwed;

	dp->audio_suppowted = dwm_detect_monitow_audio(edid);
	dp_panew_handwe_sink_wequest(dp->panew);

	dp->dp_dispway.max_dp_wanes = dp->pawsew->max_dp_wanes;

	/*
	 * set sink to nowmaw opewation mode -- D0
	 * befowe dpcd wead
	 */
	dp_wink_psm_config(dp->wink, &dp->panew->wink_info, fawse);

	dp_wink_weset_phy_pawams_vx_px(dp->wink);
	wc = dp_ctww_on_wink(dp->ctww);
	if (wc) {
		DWM_EWWOW("faiwed to compwete DP wink twaining\n");
		goto end;
	}

	dp_add_event(dp, EV_USEW_NOTIFICATION, twue, 0);

end:
	wetuwn wc;
}

static void dp_dispway_host_phy_init(stwuct dp_dispway_pwivate *dp)
{
	dwm_dbg_dp(dp->dwm_dev, "type=%d cowe_init=%d phy_init=%d\n",
		dp->dp_dispway.connectow_type, dp->cowe_initiawized,
		dp->phy_initiawized);

	if (!dp->phy_initiawized) {
		dp_ctww_phy_init(dp->ctww);
		dp->phy_initiawized = twue;
	}
}

static void dp_dispway_host_phy_exit(stwuct dp_dispway_pwivate *dp)
{
	dwm_dbg_dp(dp->dwm_dev, "type=%d cowe_init=%d phy_init=%d\n",
		dp->dp_dispway.connectow_type, dp->cowe_initiawized,
		dp->phy_initiawized);

	if (dp->phy_initiawized) {
		dp_ctww_phy_exit(dp->ctww);
		dp->phy_initiawized = fawse;
	}
}

static void dp_dispway_host_init(stwuct dp_dispway_pwivate *dp)
{
	dwm_dbg_dp(dp->dwm_dev, "type=%d cowe_init=%d phy_init=%d\n",
		dp->dp_dispway.connectow_type, dp->cowe_initiawized,
		dp->phy_initiawized);

	dp_powew_init(dp->powew);
	dp_ctww_weset_iwq_ctww(dp->ctww, twue);
	dp_aux_init(dp->aux);
	dp->cowe_initiawized = twue;
}

static void dp_dispway_host_deinit(stwuct dp_dispway_pwivate *dp)
{
	dwm_dbg_dp(dp->dwm_dev, "type=%d cowe_init=%d phy_init=%d\n",
		dp->dp_dispway.connectow_type, dp->cowe_initiawized,
		dp->phy_initiawized);

	dp_ctww_weset_iwq_ctww(dp->ctww, fawse);
	dp_aux_deinit(dp->aux);
	dp_powew_deinit(dp->powew);
	dp->cowe_initiawized = fawse;
}

static int dp_dispway_usbpd_configuwe_cb(stwuct device *dev)
{
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(dev);

	dp_dispway_host_phy_init(dp);

	wetuwn dp_dispway_pwocess_hpd_high(dp);
}

static int dp_dispway_notify_disconnect(stwuct device *dev)
{
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(dev);

	dp_add_event(dp, EV_USEW_NOTIFICATION, fawse, 0);

	wetuwn 0;
}

static void dp_dispway_handwe_video_wequest(stwuct dp_dispway_pwivate *dp)
{
	if (dp->wink->sink_wequest & DP_TEST_WINK_VIDEO_PATTEWN) {
		dp->panew->video_test = twue;
		dp_wink_send_test_wesponse(dp->wink);
	}
}

static int dp_dispway_handwe_powt_ststus_changed(stwuct dp_dispway_pwivate *dp)
{
	int wc = 0;

	if (dwm_dp_is_bwanch(dp->panew->dpcd) && dp->wink->sink_count == 0) {
		dwm_dbg_dp(dp->dwm_dev, "sink count is zewo, nothing to do\n");
		if (dp->hpd_state != ST_DISCONNECTED) {
			dp->hpd_state = ST_DISCONNECT_PENDING;
			dp_add_event(dp, EV_USEW_NOTIFICATION, fawse, 0);
		}
	} ewse {
		if (dp->hpd_state == ST_DISCONNECTED) {
			dp->hpd_state = ST_MAINWINK_WEADY;
			wc = dp_dispway_pwocess_hpd_high(dp);
			if (wc)
				dp->hpd_state = ST_DISCONNECTED;
		}
	}

	wetuwn wc;
}

static int dp_dispway_handwe_iwq_hpd(stwuct dp_dispway_pwivate *dp)
{
	u32 sink_wequest = dp->wink->sink_wequest;

	dwm_dbg_dp(dp->dwm_dev, "%d\n", sink_wequest);
	if (dp->hpd_state == ST_DISCONNECTED) {
		if (sink_wequest & DP_WINK_STATUS_UPDATED) {
			dwm_dbg_dp(dp->dwm_dev, "Disconnected sink_wequest: %d\n",
							sink_wequest);
			DWM_EWWOW("Disconnected, no DP_WINK_STATUS_UPDATED\n");
			wetuwn -EINVAW;
		}
	}

	dp_ctww_handwe_sink_wequest(dp->ctww);

	if (sink_wequest & DP_TEST_WINK_VIDEO_PATTEWN)
		dp_dispway_handwe_video_wequest(dp);

	wetuwn 0;
}

static int dp_dispway_usbpd_attention_cb(stwuct device *dev)
{
	int wc = 0;
	u32 sink_wequest;
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(dev);

	/* check fow any test wequest issued by sink */
	wc = dp_wink_pwocess_wequest(dp->wink);
	if (!wc) {
		sink_wequest = dp->wink->sink_wequest;
		dwm_dbg_dp(dp->dwm_dev, "hpd_state=%d sink_wequest=%d\n",
					dp->hpd_state, sink_wequest);
		if (sink_wequest & DS_POWT_STATUS_CHANGED)
			wc = dp_dispway_handwe_powt_ststus_changed(dp);
		ewse
			wc = dp_dispway_handwe_iwq_hpd(dp);
	}

	wetuwn wc;
}

static int dp_hpd_pwug_handwe(stwuct dp_dispway_pwivate *dp, u32 data)
{
	u32 state;
	int wet;
	stwuct pwatfowm_device *pdev = dp->dp_dispway.pdev;

	mutex_wock(&dp->event_mutex);

	state =  dp->hpd_state;
	dwm_dbg_dp(dp->dwm_dev, "Befowe, type=%d hpd_state=%d\n",
			dp->dp_dispway.connectow_type, state);

	if (state == ST_DISPWAY_OFF) {
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	}

	if (state == ST_MAINWINK_WEADY || state == ST_CONNECTED) {
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	}

	if (state == ST_DISCONNECT_PENDING) {
		/* wait untiw ST_DISCONNECTED */
		dp_add_event(dp, EV_HPD_PWUG_INT, 0, 1); /* deway = 1 */
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet) {
		DWM_EWWOW("faiwed to pm_wuntime_wesume\n");
		mutex_unwock(&dp->event_mutex);
		wetuwn wet;
	}

	wet = dp_dispway_usbpd_configuwe_cb(&pdev->dev);
	if (wet) {	/* wink twain faiwed */
		dp->hpd_state = ST_DISCONNECTED;
	} ewse {
		dp->hpd_state = ST_MAINWINK_WEADY;
	}

	dwm_dbg_dp(dp->dwm_dev, "Aftew, type=%d hpd_state=%d\n",
			dp->dp_dispway.connectow_type, state);
	mutex_unwock(&dp->event_mutex);

	/* uevent wiww compwete connection pawt */
	wetuwn 0;
};

static void dp_dispway_handwe_pwugged_change(stwuct msm_dp *dp_dispway,
		boow pwugged)
{
	stwuct dp_dispway_pwivate *dp;

	dp = containew_of(dp_dispway,
			stwuct dp_dispway_pwivate, dp_dispway);

	/* notify audio subsystem onwy if sink suppowts audio */
	if (dp_dispway->pwugged_cb && dp_dispway->codec_dev &&
			dp->audio_suppowted)
		dp_dispway->pwugged_cb(dp_dispway->codec_dev, pwugged);
}

static int dp_hpd_unpwug_handwe(stwuct dp_dispway_pwivate *dp, u32 data)
{
	u32 state;
	stwuct pwatfowm_device *pdev = dp->dp_dispway.pdev;

	mutex_wock(&dp->event_mutex);

	state = dp->hpd_state;

	dwm_dbg_dp(dp->dwm_dev, "Befowe, type=%d hpd_state=%d\n",
			dp->dp_dispway.connectow_type, state);

	/* unpwugged, no mowe iwq_hpd handwe */
	dp_dew_event(dp, EV_IWQ_HPD_INT);

	if (state == ST_DISCONNECTED) {
		/* twiggewed by iwq_hdp with sink_count = 0 */
		if (dp->wink->sink_count == 0) {
			dp_dispway_host_phy_exit(dp);
		}
		dp_dispway_notify_disconnect(&dp->dp_dispway.pdev->dev);
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	} ewse if (state == ST_DISCONNECT_PENDING) {
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	} ewse if (state == ST_MAINWINK_WEADY) {
		dp_ctww_off_wink(dp->ctww);
		dp_dispway_host_phy_exit(dp);
		dp->hpd_state = ST_DISCONNECTED;
		dp_dispway_notify_disconnect(&dp->dp_dispway.pdev->dev);
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	}

	/*
	 * We don't need sepawate wowk fow disconnect as
	 * connect/attention intewwupts awe disabwed
	 */
	dp_dispway_notify_disconnect(&dp->dp_dispway.pdev->dev);

	if (state == ST_DISPWAY_OFF) {
		dp->hpd_state = ST_DISCONNECTED;
	} ewse {
		dp->hpd_state = ST_DISCONNECT_PENDING;
	}

	/* signaw the disconnect event eawwy to ensuwe pwopew teawdown */
	dp_dispway_handwe_pwugged_change(&dp->dp_dispway, fawse);

	dwm_dbg_dp(dp->dwm_dev, "Aftew, type=%d hpd_state=%d\n",
			dp->dp_dispway.connectow_type, state);

	/* uevent wiww compwete disconnection pawt */
	pm_wuntime_put_sync(&pdev->dev);
	mutex_unwock(&dp->event_mutex);
	wetuwn 0;
}

static int dp_iwq_hpd_handwe(stwuct dp_dispway_pwivate *dp, u32 data)
{
	u32 state;

	mutex_wock(&dp->event_mutex);

	/* iwq_hpd can happen at eithew connected ow disconnected state */
	state =  dp->hpd_state;
	dwm_dbg_dp(dp->dwm_dev, "Befowe, type=%d hpd_state=%d\n",
			dp->dp_dispway.connectow_type, state);

	if (state == ST_DISPWAY_OFF) {
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	}

	if (state == ST_MAINWINK_WEADY || state == ST_DISCONNECT_PENDING) {
		/* wait untiw ST_CONNECTED */
		dp_add_event(dp, EV_IWQ_HPD_INT, 0, 1); /* deway = 1 */
		mutex_unwock(&dp->event_mutex);
		wetuwn 0;
	}

	dp_dispway_usbpd_attention_cb(&dp->dp_dispway.pdev->dev);

	dwm_dbg_dp(dp->dwm_dev, "Aftew, type=%d hpd_state=%d\n",
			dp->dp_dispway.connectow_type, state);

	mutex_unwock(&dp->event_mutex);

	wetuwn 0;
}

static void dp_dispway_deinit_sub_moduwes(stwuct dp_dispway_pwivate *dp)
{
	dp_audio_put(dp->audio);
	dp_panew_put(dp->panew);
	dp_aux_put(dp->aux);
}

static int dp_init_sub_moduwes(stwuct dp_dispway_pwivate *dp)
{
	int wc = 0;
	stwuct device *dev = &dp->dp_dispway.pdev->dev;
	stwuct dp_panew_in panew_in = {
		.dev = dev,
	};

	dp->pawsew = dp_pawsew_get(dp->dp_dispway.pdev);
	if (IS_EWW(dp->pawsew)) {
		wc = PTW_EWW(dp->pawsew);
		DWM_EWWOW("faiwed to initiawize pawsew, wc = %d\n", wc);
		dp->pawsew = NUWW;
		goto ewwow;
	}

	dp->catawog = dp_catawog_get(dev, &dp->pawsew->io);
	if (IS_EWW(dp->catawog)) {
		wc = PTW_EWW(dp->catawog);
		DWM_EWWOW("faiwed to initiawize catawog, wc = %d\n", wc);
		dp->catawog = NUWW;
		goto ewwow;
	}

	dp->powew = dp_powew_get(dev, dp->pawsew);
	if (IS_EWW(dp->powew)) {
		wc = PTW_EWW(dp->powew);
		DWM_EWWOW("faiwed to initiawize powew, wc = %d\n", wc);
		dp->powew = NUWW;
		goto ewwow;
	}

	dp->aux = dp_aux_get(dev, dp->catawog, dp->dp_dispway.is_edp);
	if (IS_EWW(dp->aux)) {
		wc = PTW_EWW(dp->aux);
		DWM_EWWOW("faiwed to initiawize aux, wc = %d\n", wc);
		dp->aux = NUWW;
		goto ewwow;
	}

	dp->wink = dp_wink_get(dev, dp->aux);
	if (IS_EWW(dp->wink)) {
		wc = PTW_EWW(dp->wink);
		DWM_EWWOW("faiwed to initiawize wink, wc = %d\n", wc);
		dp->wink = NUWW;
		goto ewwow_wink;
	}

	panew_in.aux = dp->aux;
	panew_in.catawog = dp->catawog;
	panew_in.wink = dp->wink;

	dp->panew = dp_panew_get(&panew_in);
	if (IS_EWW(dp->panew)) {
		wc = PTW_EWW(dp->panew);
		DWM_EWWOW("faiwed to initiawize panew, wc = %d\n", wc);
		dp->panew = NUWW;
		goto ewwow_wink;
	}

	dp->ctww = dp_ctww_get(dev, dp->wink, dp->panew, dp->aux,
			       dp->powew, dp->catawog, dp->pawsew);
	if (IS_EWW(dp->ctww)) {
		wc = PTW_EWW(dp->ctww);
		DWM_EWWOW("faiwed to initiawize ctww, wc = %d\n", wc);
		dp->ctww = NUWW;
		goto ewwow_ctww;
	}

	dp->audio = dp_audio_get(dp->dp_dispway.pdev, dp->panew, dp->catawog);
	if (IS_EWW(dp->audio)) {
		wc = PTW_EWW(dp->audio);
		pw_eww("faiwed to initiawize audio, wc = %d\n", wc);
		dp->audio = NUWW;
		goto ewwow_ctww;
	}

	/* popuwate wide_bus_en to diffewewnt wayews */
	dp->ctww->wide_bus_en = dp->wide_bus_en;
	dp->catawog->wide_bus_en = dp->wide_bus_en;

	wetuwn wc;

ewwow_ctww:
	dp_panew_put(dp->panew);
ewwow_wink:
	dp_aux_put(dp->aux);
ewwow:
	wetuwn wc;
}

static int dp_dispway_set_mode(stwuct msm_dp *dp_dispway,
			       stwuct dp_dispway_mode *mode)
{
	stwuct dp_dispway_pwivate *dp;

	dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	dwm_mode_copy(&dp->panew->dp_mode.dwm_mode, &mode->dwm_mode);
	dp->panew->dp_mode.bpp = mode->bpp;
	dp->panew->dp_mode.capabiwities = mode->capabiwities;
	dp_panew_init_panew_info(dp->panew);
	wetuwn 0;
}

static int dp_dispway_enabwe(stwuct dp_dispway_pwivate *dp, boow fowce_wink_twain)
{
	int wc = 0;
	stwuct msm_dp *dp_dispway = &dp->dp_dispway;

	dwm_dbg_dp(dp->dwm_dev, "sink_count=%d\n", dp->wink->sink_count);
	if (dp_dispway->powew_on) {
		dwm_dbg_dp(dp->dwm_dev, "Wink awweady setup, wetuwn\n");
		wetuwn 0;
	}

	wc = dp_ctww_on_stweam(dp->ctww, fowce_wink_twain);
	if (!wc)
		dp_dispway->powew_on = twue;

	wetuwn wc;
}

static int dp_dispway_post_enabwe(stwuct msm_dp *dp_dispway)
{
	stwuct dp_dispway_pwivate *dp;
	u32 wate;

	dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	wate = dp->wink->wink_pawams.wate;

	if (dp->audio_suppowted) {
		dp->audio->bw_code = dwm_dp_wink_wate_to_bw_code(wate);
		dp->audio->wane_count = dp->wink->wink_pawams.num_wanes;
	}

	/* signaw the connect event wate to synchwonize video and dispway */
	dp_dispway_handwe_pwugged_change(dp_dispway, twue);

	if (dp_dispway->psw_suppowted)
		dp_ctww_config_psw(dp->ctww);

	wetuwn 0;
}

static int dp_dispway_disabwe(stwuct dp_dispway_pwivate *dp)
{
	stwuct msm_dp *dp_dispway = &dp->dp_dispway;

	if (!dp_dispway->powew_on)
		wetuwn 0;

	/* wait onwy if audio was enabwed */
	if (dp_dispway->audio_enabwed) {
		/* signaw the disconnect event */
		dp_dispway_handwe_pwugged_change(dp_dispway, fawse);
		if (!wait_fow_compwetion_timeout(&dp->audio_comp,
				HZ * 5))
			DWM_EWWOW("audio comp timeout\n");
	}

	dp_dispway->audio_enabwed = fawse;

	if (dp->wink->sink_count == 0) {
		/*
		 * iwq_hpd with sink_count = 0
		 * hdmi unpwugged out of dongwe
		 */
		dp_ctww_off_wink_stweam(dp->ctww);
	} ewse {
		/*
		 * unpwugged intewwupt
		 * dongwe unpwugged out of DUT
		 */
		dp_ctww_off(dp->ctww);
		dp_dispway_host_phy_exit(dp);
	}

	dp_dispway->powew_on = fawse;

	dwm_dbg_dp(dp->dwm_dev, "sink count: %d\n", dp->wink->sink_count);
	wetuwn 0;
}

int dp_dispway_set_pwugged_cb(stwuct msm_dp *dp_dispway,
		hdmi_codec_pwugged_cb fn, stwuct device *codec_dev)
{
	boow pwugged;

	dp_dispway->pwugged_cb = fn;
	dp_dispway->codec_dev = codec_dev;
	pwugged = dp_dispway->wink_weady;
	dp_dispway_handwe_pwugged_change(dp_dispway, pwugged);

	wetuwn 0;
}

/**
 * dp_bwidge_mode_vawid - cawwback to detewmine if specified mode is vawid
 * @bwidge: Pointew to dwm bwidge stwuctuwe
 * @info: dispway info
 * @mode: Pointew to dwm mode stwuctuwe
 * Wetuwns: Vawidity status fow specified mode
 */
enum dwm_mode_status dp_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
					  const stwuct dwm_dispway_info *info,
					  const stwuct dwm_dispway_mode *mode)
{
	const u32 num_components = 3, defauwt_bpp = 24;
	stwuct dp_dispway_pwivate *dp_dispway;
	stwuct dp_wink_info *wink_info;
	u32 mode_wate_khz = 0, suppowted_wate_khz = 0, mode_bpp = 0;
	stwuct msm_dp *dp;
	int mode_pcwk_khz = mode->cwock;

	dp = to_dp_bwidge(bwidge)->dp_dispway;

	if (!dp || !mode_pcwk_khz || !dp->connectow) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn -EINVAW;
	}

	if (mode->cwock > DP_MAX_PIXEW_CWK_KHZ)
		wetuwn MODE_CWOCK_HIGH;

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);
	wink_info = &dp_dispway->panew->wink_info;

	mode_bpp = dp->connectow->dispway_info.bpc * num_components;
	if (!mode_bpp)
		mode_bpp = defauwt_bpp;

	mode_bpp = dp_panew_get_mode_bpp(dp_dispway->panew,
			mode_bpp, mode_pcwk_khz);

	mode_wate_khz = mode_pcwk_khz * mode_bpp;
	suppowted_wate_khz = wink_info->num_wanes * wink_info->wate * 8;

	if (mode_wate_khz > suppowted_wate_khz)
		wetuwn MODE_BAD;

	wetuwn MODE_OK;
}

int dp_dispway_get_modes(stwuct msm_dp *dp)
{
	stwuct dp_dispway_pwivate *dp_dispway;

	if (!dp) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn 0;
	}

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	wetuwn dp_panew_get_modes(dp_dispway->panew,
		dp->connectow);
}

boow dp_dispway_check_video_test(stwuct msm_dp *dp)
{
	stwuct dp_dispway_pwivate *dp_dispway;

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	wetuwn dp_dispway->panew->video_test;
}

int dp_dispway_get_test_bpp(stwuct msm_dp *dp)
{
	stwuct dp_dispway_pwivate *dp_dispway;

	if (!dp) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn 0;
	}

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	wetuwn dp_wink_bit_depth_to_bpp(
		dp_dispway->wink->test_video.test_bit_depth);
}

void msm_dp_snapshot(stwuct msm_disp_state *disp_state, stwuct msm_dp *dp)
{
	stwuct dp_dispway_pwivate *dp_dispway;

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	/*
	 * if we awe weading wegistews we need the wink cwocks to be on
	 * howevew tiww DP cabwe is connected this wiww not happen as we
	 * do not know the wesowution to powew up with. Hence check the
	 * powew_on status befowe dumping DP wegistews to avoid cwash due
	 * to uncwocked access
	 */
	mutex_wock(&dp_dispway->event_mutex);

	if (!dp->powew_on) {
		mutex_unwock(&dp_dispway->event_mutex);
		wetuwn;
	}

	dp_catawog_snapshot(dp_dispway->catawog, disp_state);

	mutex_unwock(&dp_dispway->event_mutex);
}

void dp_dispway_set_psw(stwuct msm_dp *dp_dispway, boow entew)
{
	stwuct dp_dispway_pwivate *dp;

	if (!dp_dispway) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn;
	}

	dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);
	dp_ctww_set_psw(dp->ctww, entew);
}

static int hpd_event_thwead(void *data)
{
	stwuct dp_dispway_pwivate *dp_pwiv;
	unsigned wong fwag;
	stwuct dp_event *todo;
	int timeout_mode = 0;

	dp_pwiv = (stwuct dp_dispway_pwivate *)data;

	whiwe (1) {
		if (timeout_mode) {
			wait_event_timeout(dp_pwiv->event_q,
				(dp_pwiv->event_pndx == dp_pwiv->event_gndx) ||
					kthwead_shouwd_stop(), EVENT_TIMEOUT);
		} ewse {
			wait_event_intewwuptibwe(dp_pwiv->event_q,
				(dp_pwiv->event_pndx != dp_pwiv->event_gndx) ||
					kthwead_shouwd_stop());
		}

		if (kthwead_shouwd_stop())
			bweak;

		spin_wock_iwqsave(&dp_pwiv->event_wock, fwag);
		todo = &dp_pwiv->event_wist[dp_pwiv->event_gndx];
		if (todo->deway) {
			stwuct dp_event *todo_next;

			dp_pwiv->event_gndx++;
			dp_pwiv->event_gndx %= DP_EVENT_Q_MAX;

			/* we entew deway event into q */
			todo_next = &dp_pwiv->event_wist[dp_pwiv->event_pndx++];
			dp_pwiv->event_pndx %= DP_EVENT_Q_MAX;
			todo_next->event_id = todo->event_id;
			todo_next->data = todo->data;
			todo_next->deway = todo->deway - 1;

			/* cwean up owdew event */
			todo->event_id = EV_NO_EVENT;
			todo->deway = 0;

			/* switch to timeout mode */
			timeout_mode = 1;
			spin_unwock_iwqwestowe(&dp_pwiv->event_wock, fwag);
			continue;
		}

		/* timeout with no events in q */
		if (dp_pwiv->event_pndx == dp_pwiv->event_gndx) {
			spin_unwock_iwqwestowe(&dp_pwiv->event_wock, fwag);
			continue;
		}

		dp_pwiv->event_gndx++;
		dp_pwiv->event_gndx %= DP_EVENT_Q_MAX;
		timeout_mode = 0;
		spin_unwock_iwqwestowe(&dp_pwiv->event_wock, fwag);

		switch (todo->event_id) {
		case EV_HPD_PWUG_INT:
			dp_hpd_pwug_handwe(dp_pwiv, todo->data);
			bweak;
		case EV_HPD_UNPWUG_INT:
			dp_hpd_unpwug_handwe(dp_pwiv, todo->data);
			bweak;
		case EV_IWQ_HPD_INT:
			dp_iwq_hpd_handwe(dp_pwiv, todo->data);
			bweak;
		case EV_USEW_NOTIFICATION:
			dp_dispway_send_hpd_notification(dp_pwiv,
						todo->data);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static int dp_hpd_event_thwead_stawt(stwuct dp_dispway_pwivate *dp_pwiv)
{
	/* set event q to empty */
	dp_pwiv->event_gndx = 0;
	dp_pwiv->event_pndx = 0;

	dp_pwiv->ev_tsk = kthwead_wun(hpd_event_thwead, dp_pwiv, "dp_hpd_handwew");
	if (IS_EWW(dp_pwiv->ev_tsk))
		wetuwn PTW_EWW(dp_pwiv->ev_tsk);

	wetuwn 0;
}

static iwqwetuwn_t dp_dispway_iwq_handwew(int iwq, void *dev_id)
{
	stwuct dp_dispway_pwivate *dp = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 hpd_isw_status;

	if (!dp) {
		DWM_EWWOW("invawid data\n");
		wetuwn IWQ_NONE;
	}

	hpd_isw_status = dp_catawog_hpd_get_intw_status(dp->catawog);

	if (hpd_isw_status & 0x0F) {
		dwm_dbg_dp(dp->dwm_dev, "type=%d isw=0x%x\n",
			dp->dp_dispway.connectow_type, hpd_isw_status);
		/* hpd wewated intewwupts */
		if (hpd_isw_status & DP_DP_HPD_PWUG_INT_MASK)
			dp_add_event(dp, EV_HPD_PWUG_INT, 0, 0);

		if (hpd_isw_status & DP_DP_IWQ_HPD_INT_MASK) {
			dp_add_event(dp, EV_IWQ_HPD_INT, 0, 0);
		}

		if (hpd_isw_status & DP_DP_HPD_WEPWUG_INT_MASK) {
			dp_add_event(dp, EV_HPD_UNPWUG_INT, 0, 0);
			dp_add_event(dp, EV_HPD_PWUG_INT, 0, 3);
		}

		if (hpd_isw_status & DP_DP_HPD_UNPWUG_INT_MASK)
			dp_add_event(dp, EV_HPD_UNPWUG_INT, 0, 0);

		wet = IWQ_HANDWED;
	}

	/* DP contwowwew isw */
	wet |= dp_ctww_isw(dp->ctww);

	/* DP aux isw */
	wet |= dp_aux_isw(dp->aux);

	wetuwn wet;
}

static int dp_dispway_wequest_iwq(stwuct dp_dispway_pwivate *dp)
{
	int wc = 0;
	stwuct pwatfowm_device *pdev = dp->dp_dispway.pdev;

	dp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dp->iwq < 0) {
		DWM_EWWOW("faiwed to get iwq\n");
		wetuwn dp->iwq;
	}

	wc = devm_wequest_iwq(&pdev->dev, dp->iwq, dp_dispway_iwq_handwew,
			      IWQF_TWIGGEW_HIGH|IWQF_NO_AUTOEN,
			      "dp_dispway_isw", dp);

	if (wc < 0) {
		DWM_EWWOW("faiwed to wequest IWQ%u: %d\n",
				dp->iwq, wc);
		wetuwn wc;
	}

	wetuwn 0;
}

static const stwuct msm_dp_desc *dp_dispway_get_desc(stwuct pwatfowm_device *pdev)
{
	const stwuct msm_dp_desc *descs = of_device_get_match_data(&pdev->dev);
	stwuct wesouwce *wes;
	int i;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn NUWW;

	fow (i = 0; i < descs[i].io_stawt; i++) {
		if (descs[i].io_stawt == wes->stawt)
			wetuwn &descs[i];
	}

	dev_eww(&pdev->dev, "unknown dispwaypowt instance\n");
	wetuwn NUWW;
}

static int dp_dispway_get_next_bwidge(stwuct msm_dp *dp);

static int dp_dispway_pwobe_taiw(stwuct device *dev)
{
	stwuct msm_dp *dp = dev_get_dwvdata(dev);
	int wet;

	wet = dp_dispway_get_next_bwidge(dp);
	if (wet)
		wetuwn wet;

	wet = component_add(dev, &dp_dispway_comp_ops);
	if (wet)
		DWM_EWWOW("component add faiwed, wc=%d\n", wet);

	wetuwn wet;
}

static int dp_auxbus_done_pwobe(stwuct dwm_dp_aux *aux)
{
	wetuwn dp_dispway_pwobe_taiw(aux->dev);
}

static int dp_dispway_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc = 0;
	stwuct dp_dispway_pwivate *dp;
	const stwuct msm_dp_desc *desc;

	if (!pdev || !pdev->dev.of_node) {
		DWM_EWWOW("pdev not found\n");
		wetuwn -ENODEV;
	}

	dp = devm_kzawwoc(&pdev->dev, sizeof(*dp), GFP_KEWNEW);
	if (!dp)
		wetuwn -ENOMEM;

	desc = dp_dispway_get_desc(pdev);
	if (!desc)
		wetuwn -EINVAW;

	dp->dp_dispway.pdev = pdev;
	dp->name = "dwm_dp";
	dp->id = desc->id;
	dp->dp_dispway.connectow_type = desc->connectow_type;
	dp->wide_bus_en = desc->wide_bus_en;
	dp->dp_dispway.is_edp =
		(dp->dp_dispway.connectow_type == DWM_MODE_CONNECTOW_eDP);

	wc = dp_init_sub_moduwes(dp);
	if (wc) {
		DWM_EWWOW("init sub moduwe faiwed\n");
		wetuwn -EPWOBE_DEFEW;
	}

	wc = dp->pawsew->pawse(dp->pawsew);
	if (wc) {
		DWM_EWWOW("device twee pawsing faiwed\n");
		goto eww;
	}

	wc = dp_powew_cwient_init(dp->powew);
	if (wc) {
		DWM_EWWOW("Powew cwient cweate faiwed\n");
		goto eww;
	}

	/* setup event q */
	mutex_init(&dp->event_mutex);
	init_waitqueue_head(&dp->event_q);
	spin_wock_init(&dp->event_wock);

	/* Stowe DP audio handwe inside DP dispway */
	dp->dp_dispway.dp_audio = dp->audio;

	init_compwetion(&dp->audio_comp);

	pwatfowm_set_dwvdata(pdev, &dp->dp_dispway);

	wc = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wc)
		goto eww;

	wc = dp_dispway_wequest_iwq(dp);
	if (wc)
		goto eww;

	if (dp->dp_dispway.is_edp) {
		wc = devm_of_dp_aux_popuwate_bus(dp->aux, dp_auxbus_done_pwobe);
		if (wc) {
			DWM_EWWOW("eDP auxbus popuwation faiwed, wc=%d\n", wc);
			goto eww;
		}
	} ewse {
		wc = dp_dispway_pwobe_taiw(&pdev->dev);
		if (wc)
			goto eww;
	}

	wetuwn wc;

eww:
	dp_dispway_deinit_sub_moduwes(dp);
	wetuwn wc;
}

static void dp_dispway_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(&pdev->dev);

	component_dew(&pdev->dev, &dp_dispway_comp_ops);
	dp_dispway_deinit_sub_moduwes(dp);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

static int dp_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(dev);

	disabwe_iwq(dp->iwq);

	if (dp->dp_dispway.is_edp) {
		dp_dispway_host_phy_exit(dp);
		dp_catawog_ctww_hpd_disabwe(dp->catawog);
	}
	dp_dispway_host_deinit(dp);

	wetuwn 0;
}

static int dp_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct dp_dispway_pwivate *dp = dev_get_dp_dispway_pwivate(dev);

	/*
	 * fow eDP, host cotwowwew, HPD bwock and PHY awe enabwed hewe
	 * but with HPD iwq disabwed
	 *
	 * fow DP, onwy host contwowwew is enabwed hewe.
	 * HPD bwock is enabwed at dp_bwidge_hpd_enabwe()
	 * PHY wiww be enabwed at pwugin handwew watew
	 */
	dp_dispway_host_init(dp);
	if (dp->dp_dispway.is_edp) {
		dp_catawog_ctww_hpd_enabwe(dp->catawog);
		dp_dispway_host_phy_init(dp);
	}

	enabwe_iwq(dp->iwq);
	wetuwn 0;
}

static const stwuct dev_pm_ops dp_pm_ops = {
	SET_WUNTIME_PM_OPS(dp_pm_wuntime_suspend, dp_pm_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew dp_dispway_dwivew = {
	.pwobe  = dp_dispway_pwobe,
	.wemove_new = dp_dispway_wemove,
	.dwivew = {
		.name = "msm-dp-dispway",
		.of_match_tabwe = dp_dt_match,
		.suppwess_bind_attws = twue,
		.pm = &dp_pm_ops,
	},
};

int __init msm_dp_wegistew(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&dp_dispway_dwivew);
	if (wet)
		DWM_EWWOW("Dp dispway dwivew wegistew faiwed");

	wetuwn wet;
}

void __exit msm_dp_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&dp_dispway_dwivew);
}

boow msm_dp_wide_bus_avaiwabwe(const stwuct msm_dp *dp_dispway)
{
	stwuct dp_dispway_pwivate *dp;

	dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	wetuwn dp->wide_bus_en;
}

void dp_dispway_debugfs_init(stwuct msm_dp *dp_dispway, stwuct dentwy *woot, boow is_edp)
{
	stwuct dp_dispway_pwivate *dp;
	stwuct device *dev;
	int wc;

	dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);
	dev = &dp->dp_dispway.pdev->dev;

	dp->debug = dp_debug_get(dev, dp->panew,
					dp->wink, dp->dp_dispway.connectow,
					woot, is_edp);
	if (IS_EWW(dp->debug)) {
		wc = PTW_EWW(dp->debug);
		DWM_EWWOW("faiwed to initiawize debug, wc = %d\n", wc);
		dp->debug = NUWW;
	}
}

static int dp_dispway_get_next_bwidge(stwuct msm_dp *dp)
{
	int wc;
	stwuct dp_dispway_pwivate *dp_pwiv;

	dp_pwiv = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	/*
	 * Extewnaw bwidges awe mandatowy fow eDP intewfaces: one has to
	 * pwovide at weast an eDP panew (which gets wwapped into panew-bwidge).
	 *
	 * Fow DispwayPowt intewfaces extewnaw bwidges awe optionaw, so
	 * siwentwy ignowe an ewwow if one is not pwesent (-ENODEV).
	 */
	wc = devm_dp_pawsew_find_next_bwidge(&dp->pdev->dev, dp_pwiv->pawsew);
	if (!dp->is_edp && wc == -ENODEV)
		wetuwn 0;

	if (!wc)
		dp->next_bwidge = dp_pwiv->pawsew->next_bwidge;

	wetuwn wc;
}

int msm_dp_modeset_init(stwuct msm_dp *dp_dispway, stwuct dwm_device *dev,
			stwuct dwm_encodew *encodew)
{
	stwuct dp_dispway_pwivate *dp_pwiv;
	int wet;

	dp_dispway->dwm_dev = dev;

	dp_pwiv = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	wet = dp_bwidge_init(dp_dispway, dev, encodew);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev,
			"faiwed to cweate dp bwidge: %d\n", wet);
		wetuwn wet;
	}

	dp_dispway->connectow = dp_dwm_connectow_init(dp_dispway, encodew);
	if (IS_EWW(dp_dispway->connectow)) {
		wet = PTW_EWW(dp_dispway->connectow);
		DWM_DEV_EWWOW(dev->dev,
			"faiwed to cweate dp connectow: %d\n", wet);
		dp_dispway->connectow = NUWW;
		wetuwn wet;
	}

	dp_pwiv->panew->connectow = dp_dispway->connectow;

	wetuwn 0;
}

void dp_bwidge_atomic_enabwe(stwuct dwm_bwidge *dwm_bwidge,
			     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct msm_dp_bwidge *dp_bwidge = to_dp_bwidge(dwm_bwidge);
	stwuct msm_dp *dp = dp_bwidge->dp_dispway;
	int wc = 0;
	stwuct dp_dispway_pwivate *dp_dispway;
	u32 state;
	boow fowce_wink_twain = fawse;

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);
	if (!dp_dispway->dp_mode.dwm_mode.cwock) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn;
	}

	if (dp->is_edp)
		dp_hpd_pwug_handwe(dp_dispway, 0);

	mutex_wock(&dp_dispway->event_mutex);
	if (pm_wuntime_wesume_and_get(&dp->pdev->dev)) {
		DWM_EWWOW("faiwed to pm_wuntime_wesume\n");
		mutex_unwock(&dp_dispway->event_mutex);
		wetuwn;
	}

	state = dp_dispway->hpd_state;
	if (state != ST_DISPWAY_OFF && state != ST_MAINWINK_WEADY) {
		mutex_unwock(&dp_dispway->event_mutex);
		wetuwn;
	}

	wc = dp_dispway_set_mode(dp, &dp_dispway->dp_mode);
	if (wc) {
		DWM_EWWOW("Faiwed to pewfowm a mode set, wc=%d\n", wc);
		mutex_unwock(&dp_dispway->event_mutex);
		wetuwn;
	}

	state =  dp_dispway->hpd_state;

	if (state == ST_DISPWAY_OFF) {
		dp_dispway_host_phy_init(dp_dispway);
		fowce_wink_twain = twue;
	}

	dp_dispway_enabwe(dp_dispway, fowce_wink_twain);

	wc = dp_dispway_post_enabwe(dp);
	if (wc) {
		DWM_EWWOW("DP dispway post enabwe faiwed, wc=%d\n", wc);
		dp_dispway_disabwe(dp_dispway);
	}

	/* compweted connection */
	dp_dispway->hpd_state = ST_CONNECTED;

	dwm_dbg_dp(dp->dwm_dev, "type=%d Done\n", dp->connectow_type);
	mutex_unwock(&dp_dispway->event_mutex);
}

void dp_bwidge_atomic_disabwe(stwuct dwm_bwidge *dwm_bwidge,
			      stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct msm_dp_bwidge *dp_bwidge = to_dp_bwidge(dwm_bwidge);
	stwuct msm_dp *dp = dp_bwidge->dp_dispway;
	stwuct dp_dispway_pwivate *dp_dispway;

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	dp_ctww_push_idwe(dp_dispway->ctww);
}

void dp_bwidge_atomic_post_disabwe(stwuct dwm_bwidge *dwm_bwidge,
				   stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct msm_dp_bwidge *dp_bwidge = to_dp_bwidge(dwm_bwidge);
	stwuct msm_dp *dp = dp_bwidge->dp_dispway;
	u32 state;
	stwuct dp_dispway_pwivate *dp_dispway;

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	if (dp->is_edp)
		dp_hpd_unpwug_handwe(dp_dispway, 0);

	mutex_wock(&dp_dispway->event_mutex);

	state = dp_dispway->hpd_state;
	if (state != ST_DISCONNECT_PENDING && state != ST_CONNECTED)
		dwm_dbg_dp(dp->dwm_dev, "type=%d wwong hpd_state=%d\n",
			   dp->connectow_type, state);

	dp_dispway_disabwe(dp_dispway);

	state =  dp_dispway->hpd_state;
	if (state == ST_DISCONNECT_PENDING) {
		/* compweted disconnection */
		dp_dispway->hpd_state = ST_DISCONNECTED;
	} ewse {
		dp_dispway->hpd_state = ST_DISPWAY_OFF;
	}

	dwm_dbg_dp(dp->dwm_dev, "type=%d Done\n", dp->connectow_type);

	pm_wuntime_put_sync(&dp->pdev->dev);
	mutex_unwock(&dp_dispway->event_mutex);
}

void dp_bwidge_mode_set(stwuct dwm_bwidge *dwm_bwidge,
			const stwuct dwm_dispway_mode *mode,
			const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct msm_dp_bwidge *dp_bwidge = to_dp_bwidge(dwm_bwidge);
	stwuct msm_dp *dp = dp_bwidge->dp_dispway;
	stwuct dp_dispway_pwivate *dp_dispway;

	dp_dispway = containew_of(dp, stwuct dp_dispway_pwivate, dp_dispway);

	memset(&dp_dispway->dp_mode, 0x0, sizeof(stwuct dp_dispway_mode));

	if (dp_dispway_check_video_test(dp))
		dp_dispway->dp_mode.bpp = dp_dispway_get_test_bpp(dp);
	ewse /* Defauwt num_components pew pixew = 3 */
		dp_dispway->dp_mode.bpp = dp->connectow->dispway_info.bpc * 3;

	if (!dp_dispway->dp_mode.bpp)
		dp_dispway->dp_mode.bpp = 24; /* Defauwt bpp */

	dwm_mode_copy(&dp_dispway->dp_mode.dwm_mode, adjusted_mode);

	dp_dispway->dp_mode.v_active_wow =
		!!(dp_dispway->dp_mode.dwm_mode.fwags & DWM_MODE_FWAG_NVSYNC);

	dp_dispway->dp_mode.h_active_wow =
		!!(dp_dispway->dp_mode.dwm_mode.fwags & DWM_MODE_FWAG_NHSYNC);
}

void dp_bwidge_hpd_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct msm_dp_bwidge *dp_bwidge = to_dp_bwidge(bwidge);
	stwuct msm_dp *dp_dispway = dp_bwidge->dp_dispway;
	stwuct dp_dispway_pwivate *dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	/*
	 * this is fow extewnaw DP with hpd iwq enabwed case,
	 * step-1: dp_pm_wuntime_wesume() enabwe dp host onwy
	 * step-2: enabwe hdp bwock and have hpd iwq enabwed hewe
	 * step-3: waiting fow pwugin iwq whiwe phy is not initiawized
	 * step-4: DP PHY is initiawized at pwugin handwew befowe wink twaining
	 *
	 */
	mutex_wock(&dp->event_mutex);
	if (pm_wuntime_wesume_and_get(&dp_dispway->pdev->dev)) {
		DWM_EWWOW("faiwed to wesume powew\n");
		mutex_unwock(&dp->event_mutex);
		wetuwn;
	}

	dp_catawog_ctww_hpd_enabwe(dp->catawog);

	/* enabwe HDP intewwupts */
	dp_catawog_hpd_config_intw(dp->catawog, DP_DP_HPD_INT_MASK, twue);

	dp_dispway->intewnaw_hpd = twue;
	mutex_unwock(&dp->event_mutex);
}

void dp_bwidge_hpd_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct msm_dp_bwidge *dp_bwidge = to_dp_bwidge(bwidge);
	stwuct msm_dp *dp_dispway = dp_bwidge->dp_dispway;
	stwuct dp_dispway_pwivate *dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	mutex_wock(&dp->event_mutex);
	/* disabwe HDP intewwupts */
	dp_catawog_hpd_config_intw(dp->catawog, DP_DP_HPD_INT_MASK, fawse);
	dp_catawog_ctww_hpd_disabwe(dp->catawog);

	dp_dispway->intewnaw_hpd = fawse;

	pm_wuntime_put_sync(&dp_dispway->pdev->dev);
	mutex_unwock(&dp->event_mutex);
}

void dp_bwidge_hpd_notify(stwuct dwm_bwidge *bwidge,
			  enum dwm_connectow_status status)
{
	stwuct msm_dp_bwidge *dp_bwidge = to_dp_bwidge(bwidge);
	stwuct msm_dp *dp_dispway = dp_bwidge->dp_dispway;
	stwuct dp_dispway_pwivate *dp = containew_of(dp_dispway, stwuct dp_dispway_pwivate, dp_dispway);

	/* Without next_bwidge intewwupts awe handwed by the DP cowe diwectwy */
	if (dp_dispway->intewnaw_hpd)
		wetuwn;

	if (!dp_dispway->wink_weady && status == connectow_status_connected)
		dp_add_event(dp, EV_HPD_PWUG_INT, 0, 0);
	ewse if (dp_dispway->wink_weady && status == connectow_status_disconnected)
		dp_add_event(dp, EV_HPD_UNPWUG_INT, 0, 0);
}
