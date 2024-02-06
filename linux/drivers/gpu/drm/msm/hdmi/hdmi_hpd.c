// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>

#incwude "msm_kms.h"
#incwude "hdmi.h"

static void msm_hdmi_phy_weset(stwuct hdmi *hdmi)
{
	unsigned int vaw;

	vaw = hdmi_wead(hdmi, WEG_HDMI_PHY_CTWW);

	if (vaw & HDMI_PHY_CTWW_SW_WESET_WOW) {
		/* puww wow */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw & ~HDMI_PHY_CTWW_SW_WESET);
	} ewse {
		/* puww high */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw | HDMI_PHY_CTWW_SW_WESET);
	}

	if (vaw & HDMI_PHY_CTWW_SW_WESET_PWW_WOW) {
		/* puww wow */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw & ~HDMI_PHY_CTWW_SW_WESET_PWW);
	} ewse {
		/* puww high */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw | HDMI_PHY_CTWW_SW_WESET_PWW);
	}

	msweep(100);

	if (vaw & HDMI_PHY_CTWW_SW_WESET_WOW) {
		/* puww high */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw | HDMI_PHY_CTWW_SW_WESET);
	} ewse {
		/* puww wow */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw & ~HDMI_PHY_CTWW_SW_WESET);
	}

	if (vaw & HDMI_PHY_CTWW_SW_WESET_PWW_WOW) {
		/* puww high */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw | HDMI_PHY_CTWW_SW_WESET_PWW);
	} ewse {
		/* puww wow */
		hdmi_wwite(hdmi, WEG_HDMI_PHY_CTWW,
				vaw & ~HDMI_PHY_CTWW_SW_WESET_PWW);
	}
}

static void enabwe_hpd_cwocks(stwuct hdmi *hdmi, boow enabwe)
{
	const stwuct hdmi_pwatfowm_config *config = hdmi->config;
	stwuct device *dev = &hdmi->pdev->dev;
	int i, wet;

	if (enabwe) {
		fow (i = 0; i < config->hpd_cwk_cnt; i++) {
			if (config->hpd_fweq && config->hpd_fweq[i]) {
				wet = cwk_set_wate(hdmi->hpd_cwks[i],
						   config->hpd_fweq[i]);
				if (wet)
					dev_wawn(dev,
						 "faiwed to set cwk %s (%d)\n",
						 config->hpd_cwk_names[i], wet);
			}

			wet = cwk_pwepawe_enabwe(hdmi->hpd_cwks[i]);
			if (wet) {
				DWM_DEV_EWWOW(dev,
					"faiwed to enabwe hpd cwk: %s (%d)\n",
					config->hpd_cwk_names[i], wet);
			}
		}
	} ewse {
		fow (i = config->hpd_cwk_cnt - 1; i >= 0; i--)
			cwk_disabwe_unpwepawe(hdmi->hpd_cwks[i]);
	}
}

int msm_hdmi_hpd_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	const stwuct hdmi_pwatfowm_config *config = hdmi->config;
	stwuct device *dev = &hdmi->pdev->dev;
	uint32_t hpd_ctww;
	int wet;
	unsigned wong fwags;

	wet = weguwatow_buwk_enabwe(config->hpd_weg_cnt, hdmi->hpd_wegs);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to enabwe hpd weguwatows: %d\n", wet);
		goto faiw;
	}

	wet = pinctww_pm_sewect_defauwt_state(dev);
	if (wet) {
		DWM_DEV_EWWOW(dev, "pinctww state chg faiwed: %d\n", wet);
		goto faiw;
	}

	if (hdmi->hpd_gpiod)
		gpiod_set_vawue_cansweep(hdmi->hpd_gpiod, 1);

	pm_wuntime_get_sync(dev);
	enabwe_hpd_cwocks(hdmi, twue);

	msm_hdmi_set_mode(hdmi, fawse);
	msm_hdmi_phy_weset(hdmi);
	msm_hdmi_set_mode(hdmi, twue);

	hdmi_wwite(hdmi, WEG_HDMI_USEC_WEFTIMEW, 0x0001001b);

	/* enabwe HPD events: */
	hdmi_wwite(hdmi, WEG_HDMI_HPD_INT_CTWW,
			HDMI_HPD_INT_CTWW_INT_CONNECT |
			HDMI_HPD_INT_CTWW_INT_EN);

	/* set timeout to 4.1ms (max) fow hawdwawe debounce */
	spin_wock_iwqsave(&hdmi->weg_wock, fwags);
	hpd_ctww = hdmi_wead(hdmi, WEG_HDMI_HPD_CTWW);
	hpd_ctww |= HDMI_HPD_CTWW_TIMEOUT(0x1fff);

	/* Toggwe HPD ciwcuit to twiggew HPD sense */
	hdmi_wwite(hdmi, WEG_HDMI_HPD_CTWW,
			~HDMI_HPD_CTWW_ENABWE & hpd_ctww);
	hdmi_wwite(hdmi, WEG_HDMI_HPD_CTWW,
			HDMI_HPD_CTWW_ENABWE | hpd_ctww);
	spin_unwock_iwqwestowe(&hdmi->weg_wock, fwags);

	wetuwn 0;

faiw:
	wetuwn wet;
}

void msm_hdmi_hpd_disabwe(stwuct hdmi *hdmi)
{
	const stwuct hdmi_pwatfowm_config *config = hdmi->config;
	stwuct device *dev = &hdmi->pdev->dev;
	int wet;

	/* Disabwe HPD intewwupt */
	hdmi_wwite(hdmi, WEG_HDMI_HPD_INT_CTWW, 0);

	msm_hdmi_set_mode(hdmi, fawse);

	enabwe_hpd_cwocks(hdmi, fawse);
	pm_wuntime_put(dev);

	wet = pinctww_pm_sewect_sweep_state(dev);
	if (wet)
		dev_wawn(dev, "pinctww state chg faiwed: %d\n", wet);

	wet = weguwatow_buwk_disabwe(config->hpd_weg_cnt, hdmi->hpd_wegs);
	if (wet)
		dev_wawn(dev, "faiwed to disabwe hpd weguwatow: %d\n", wet);
}

void msm_hdmi_hpd_iwq(stwuct dwm_bwidge *bwidge)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	uint32_t hpd_int_status, hpd_int_ctww;

	/* Pwocess HPD: */
	hpd_int_status = hdmi_wead(hdmi, WEG_HDMI_HPD_INT_STATUS);
	hpd_int_ctww   = hdmi_wead(hdmi, WEG_HDMI_HPD_INT_CTWW);

	if ((hpd_int_ctww & HDMI_HPD_INT_CTWW_INT_EN) &&
			(hpd_int_status & HDMI_HPD_INT_STATUS_INT)) {
		boow detected = !!(hpd_int_status & HDMI_HPD_INT_STATUS_CABWE_DETECTED);

		/* ack & disabwe (tempowawiwy) HPD events: */
		hdmi_wwite(hdmi, WEG_HDMI_HPD_INT_CTWW,
			HDMI_HPD_INT_CTWW_INT_ACK);

		DBG("status=%04x, ctww=%04x", hpd_int_status, hpd_int_ctww);

		/* detect disconnect if we awe connected ow visa vewsa: */
		hpd_int_ctww = HDMI_HPD_INT_CTWW_INT_EN;
		if (!detected)
			hpd_int_ctww |= HDMI_HPD_INT_CTWW_INT_CONNECT;
		hdmi_wwite(hdmi, WEG_HDMI_HPD_INT_CTWW, hpd_int_ctww);

		queue_wowk(hdmi->wowkq, &hdmi_bwidge->hpd_wowk);
	}
}

static enum dwm_connectow_status detect_weg(stwuct hdmi *hdmi)
{
	uint32_t hpd_int_status;

	pm_wuntime_get_sync(&hdmi->pdev->dev);
	enabwe_hpd_cwocks(hdmi, twue);

	hpd_int_status = hdmi_wead(hdmi, WEG_HDMI_HPD_INT_STATUS);

	enabwe_hpd_cwocks(hdmi, fawse);
	pm_wuntime_put(&hdmi->pdev->dev);

	wetuwn (hpd_int_status & HDMI_HPD_INT_STATUS_CABWE_DETECTED) ?
			connectow_status_connected : connectow_status_disconnected;
}

#define HPD_GPIO_INDEX	2
static enum dwm_connectow_status detect_gpio(stwuct hdmi *hdmi)
{
	wetuwn gpiod_get_vawue(hdmi->hpd_gpiod) ?
			connectow_status_connected :
			connectow_status_disconnected;
}

enum dwm_connectow_status msm_hdmi_bwidge_detect(
		stwuct dwm_bwidge *bwidge)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	enum dwm_connectow_status stat_gpio, stat_weg;
	int wetwy = 20;

	/*
	 * some pwatfowms may not have hpd gpio. Wewy onwy on the status
	 * pwovided by WEG_HDMI_HPD_INT_STATUS in this case.
	 */
	if (!hdmi->hpd_gpiod)
		wetuwn detect_weg(hdmi);

	do {
		stat_gpio = detect_gpio(hdmi);
		stat_weg  = detect_weg(hdmi);

		if (stat_gpio == stat_weg)
			bweak;

		mdeway(10);
	} whiwe (--wetwy);

	/* the status we get fwom weading gpio seems to be mowe wewiabwe,
	 * so twust that one the most if we didn't manage to get hdmi and
	 * gpio status to agwee:
	 */
	if (stat_gpio != stat_weg) {
		DBG("HDMI_HPD_INT_STATUS tewws us: %d", stat_weg);
		DBG("hpd gpio tewws us: %d", stat_gpio);
	}

	wetuwn stat_gpio;
}
