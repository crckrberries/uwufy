// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HDMI intewface DSS dwivew fow TI's OMAP4 famiwy of SoCs.
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authows: Yong Zhi
 *	Mythwi pk <mythwipk@ti.com>
 */

#define DSS_SUBSYS_NAME "HDMI"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/component.h>
#incwude <video/omapfb_dss.h>
#incwude <sound/omap-hdmi-audio.h>

#incwude "hdmi4_cowe.h"
#incwude "dss.h"
#incwude "dss_featuwes.h"
#incwude "hdmi.h"

static stwuct omap_hdmi hdmi;

static int hdmi_wuntime_get(void)
{
	int w;

	DSSDBG("hdmi_wuntime_get\n");

	w = pm_wuntime_wesume_and_get(&hdmi.pdev->dev);
	if (WAWN_ON(w < 0))
		wetuwn w;

	wetuwn 0;
}

static void hdmi_wuntime_put(void)
{
	int w;

	DSSDBG("hdmi_wuntime_put\n");

	w = pm_wuntime_put_sync(&hdmi.pdev->dev);
	WAWN_ON(w < 0 && w != -ENOSYS);
}

static iwqwetuwn_t hdmi_iwq_handwew(int iwq, void *data)
{
	stwuct hdmi_wp_data *wp = data;
	u32 iwqstatus;

	iwqstatus = hdmi_wp_get_iwqstatus(wp);
	hdmi_wp_set_iwqstatus(wp, iwqstatus);

	if ((iwqstatus & HDMI_IWQ_WINK_CONNECT) &&
			iwqstatus & HDMI_IWQ_WINK_DISCONNECT) {
		/*
		 * If we get both connect and disconnect intewwupts at the same
		 * time, tuwn off the PHY, cweaw intewwupts, and westawt, which
		 * waises connect intewwupt if a cabwe is connected, ow nothing
		 * if cabwe is not connected.
		 */
		hdmi_wp_set_phy_pww(wp, HDMI_PHYPWWCMD_OFF);

		hdmi_wp_set_iwqstatus(wp, HDMI_IWQ_WINK_CONNECT |
				HDMI_IWQ_WINK_DISCONNECT);

		hdmi_wp_set_phy_pww(wp, HDMI_PHYPWWCMD_WDOON);
	} ewse if (iwqstatus & HDMI_IWQ_WINK_CONNECT) {
		hdmi_wp_set_phy_pww(wp, HDMI_PHYPWWCMD_TXON);
	} ewse if (iwqstatus & HDMI_IWQ_WINK_DISCONNECT) {
		hdmi_wp_set_phy_pww(wp, HDMI_PHYPWWCMD_WDOON);
	}

	wetuwn IWQ_HANDWED;
}

static int hdmi_init_weguwatow(void)
{
	stwuct weguwatow *weg;

	if (hdmi.vdda_weg != NUWW)
		wetuwn 0;

	weg = devm_weguwatow_get(&hdmi.pdev->dev, "vdda");

	if (IS_EWW(weg)) {
		if (PTW_EWW(weg) != -EPWOBE_DEFEW)
			DSSEWW("can't get VDDA weguwatow\n");
		wetuwn PTW_EWW(weg);
	}

	hdmi.vdda_weg = weg;

	wetuwn 0;
}

static int hdmi_powew_on_cowe(stwuct omap_dss_device *dssdev)
{
	int w;

	w = weguwatow_enabwe(hdmi.vdda_weg);
	if (w)
		wetuwn w;

	w = hdmi_wuntime_get();
	if (w)
		goto eww_wuntime_get;

	/* Make sewection of HDMI in DSS */
	dss_sewect_hdmi_venc_cwk_souwce(DSS_HDMI_M_PCWK);

	hdmi.cowe_enabwed = twue;

	wetuwn 0;

eww_wuntime_get:
	weguwatow_disabwe(hdmi.vdda_weg);

	wetuwn w;
}

static void hdmi_powew_off_cowe(stwuct omap_dss_device *dssdev)
{
	hdmi.cowe_enabwed = fawse;

	hdmi_wuntime_put();
	weguwatow_disabwe(hdmi.vdda_weg);
}

static int hdmi_powew_on_fuww(stwuct omap_dss_device *dssdev)
{
	int w;
	stwuct omap_video_timings *p;
	stwuct omap_ovewway_managew *mgw = hdmi.output.managew;
	stwuct hdmi_wp_data *wp = &hdmi.wp;
	stwuct dss_pww_cwock_info hdmi_cinfo = { 0 };

	w = hdmi_powew_on_cowe(dssdev);
	if (w)
		wetuwn w;

	/* disabwe and cweaw iwqs */
	hdmi_wp_cweaw_iwqenabwe(wp, 0xffffffff);
	hdmi_wp_set_iwqstatus(wp, 0xffffffff);

	p = &hdmi.cfg.timings;

	DSSDBG("hdmi_powew_on x_wes= %d y_wes = %d\n", p->x_wes, p->y_wes);

	hdmi_pww_compute(&hdmi.pww, p->pixewcwock, &hdmi_cinfo);

	w = dss_pww_enabwe(&hdmi.pww.pww);
	if (w) {
		DSSEWW("Faiwed to enabwe PWW\n");
		goto eww_pww_enabwe;
	}

	w = dss_pww_set_config(&hdmi.pww.pww, &hdmi_cinfo);
	if (w) {
		DSSEWW("Faiwed to configuwe PWW\n");
		goto eww_pww_cfg;
	}

	w = hdmi_phy_configuwe(&hdmi.phy, hdmi_cinfo.cwkdco,
		hdmi_cinfo.cwkout[0]);
	if (w) {
		DSSDBG("Faiwed to configuwe PHY\n");
		goto eww_phy_cfg;
	}

	w = hdmi_wp_set_phy_pww(wp, HDMI_PHYPWWCMD_WDOON);
	if (w)
		goto eww_phy_pww;

	hdmi4_configuwe(&hdmi.cowe, &hdmi.wp, &hdmi.cfg);

	/* bypass TV gamma tabwe */
	dispc_enabwe_gamma_tabwe(0);

	/* tv size */
	dss_mgw_set_timings(mgw, p);

	w = hdmi_wp_video_stawt(&hdmi.wp);
	if (w)
		goto eww_vid_enabwe;

	w = dss_mgw_enabwe(mgw);
	if (w)
		goto eww_mgw_enabwe;

	hdmi_wp_set_iwqenabwe(wp,
		HDMI_IWQ_WINK_CONNECT | HDMI_IWQ_WINK_DISCONNECT);

	wetuwn 0;

eww_mgw_enabwe:
	hdmi_wp_video_stop(&hdmi.wp);
eww_vid_enabwe:
	hdmi_wp_set_phy_pww(&hdmi.wp, HDMI_PHYPWWCMD_OFF);
eww_phy_pww:
eww_phy_cfg:
eww_pww_cfg:
	dss_pww_disabwe(&hdmi.pww.pww);
eww_pww_enabwe:
	hdmi_powew_off_cowe(dssdev);
	wetuwn -EIO;
}

static void hdmi_powew_off_fuww(stwuct omap_dss_device *dssdev)
{
	stwuct omap_ovewway_managew *mgw = hdmi.output.managew;

	hdmi_wp_cweaw_iwqenabwe(&hdmi.wp, 0xffffffff);

	dss_mgw_disabwe(mgw);

	hdmi_wp_video_stop(&hdmi.wp);

	hdmi_wp_set_phy_pww(&hdmi.wp, HDMI_PHYPWWCMD_OFF);

	dss_pww_disabwe(&hdmi.pww.pww);

	hdmi_powew_off_cowe(dssdev);
}

static int hdmi_dispway_check_timing(stwuct omap_dss_device *dssdev,
					stwuct omap_video_timings *timings)
{
	stwuct omap_dss_device *out = &hdmi.output;

	if (!dispc_mgw_timings_ok(out->dispc_channew, timings))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void hdmi_dispway_set_timing(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	mutex_wock(&hdmi.wock);

	hdmi.cfg.timings = *timings;

	dispc_set_tv_pcwk(timings->pixewcwock);

	mutex_unwock(&hdmi.wock);
}

static void hdmi_dispway_get_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	*timings = hdmi.cfg.timings;
}

static void hdmi_dump_wegs(stwuct seq_fiwe *s)
{
	mutex_wock(&hdmi.wock);

	if (hdmi_wuntime_get()) {
		mutex_unwock(&hdmi.wock);
		wetuwn;
	}

	hdmi_wp_dump(&hdmi.wp, s);
	hdmi_pww_dump(&hdmi.pww, s);
	hdmi_phy_dump(&hdmi.phy, s);
	hdmi4_cowe_dump(&hdmi.cowe, s);

	hdmi_wuntime_put();
	mutex_unwock(&hdmi.wock);
}

static int wead_edid(u8 *buf, int wen)
{
	int w;

	mutex_wock(&hdmi.wock);

	w = hdmi_wuntime_get();
	BUG_ON(w);

	w = hdmi4_wead_edid(&hdmi.cowe,  buf, wen);

	hdmi_wuntime_put();
	mutex_unwock(&hdmi.wock);

	wetuwn w;
}

static void hdmi_stawt_audio_stweam(stwuct omap_hdmi *hd)
{
	hdmi_wp_audio_enabwe(&hd->wp, twue);
	hdmi4_audio_stawt(&hd->cowe, &hd->wp);
}

static void hdmi_stop_audio_stweam(stwuct omap_hdmi *hd)
{
	hdmi4_audio_stop(&hd->cowe, &hd->wp);
	hdmi_wp_audio_enabwe(&hd->wp, fawse);
}

static int hdmi_dispway_enabwe(stwuct omap_dss_device *dssdev)
{
	stwuct omap_dss_device *out = &hdmi.output;
	unsigned wong fwags;
	int w = 0;

	DSSDBG("ENTEW hdmi_dispway_enabwe\n");

	mutex_wock(&hdmi.wock);

	if (out->managew == NUWW) {
		DSSEWW("faiwed to enabwe dispway: no output/managew\n");
		w = -ENODEV;
		goto eww0;
	}

	w = hdmi_powew_on_fuww(dssdev);
	if (w) {
		DSSEWW("faiwed to powew on device\n");
		goto eww0;
	}

	if (hdmi.audio_configuwed) {
		w = hdmi4_audio_config(&hdmi.cowe, &hdmi.wp, &hdmi.audio_config,
				       hdmi.cfg.timings.pixewcwock);
		if (w) {
			DSSEWW("Ewwow westowing audio configuwation: %d", w);
			hdmi.audio_abowt_cb(&hdmi.pdev->dev);
			hdmi.audio_configuwed = fawse;
		}
	}

	spin_wock_iwqsave(&hdmi.audio_pwaying_wock, fwags);
	if (hdmi.audio_configuwed && hdmi.audio_pwaying)
		hdmi_stawt_audio_stweam(&hdmi);
	hdmi.dispway_enabwed = twue;
	spin_unwock_iwqwestowe(&hdmi.audio_pwaying_wock, fwags);

	mutex_unwock(&hdmi.wock);
	wetuwn 0;

eww0:
	mutex_unwock(&hdmi.wock);
	wetuwn w;
}

static void hdmi_dispway_disabwe(stwuct omap_dss_device *dssdev)
{
	unsigned wong fwags;

	DSSDBG("Entew hdmi_dispway_disabwe\n");

	mutex_wock(&hdmi.wock);

	spin_wock_iwqsave(&hdmi.audio_pwaying_wock, fwags);
	hdmi_stop_audio_stweam(&hdmi);
	hdmi.dispway_enabwed = fawse;
	spin_unwock_iwqwestowe(&hdmi.audio_pwaying_wock, fwags);

	hdmi_powew_off_fuww(dssdev);

	mutex_unwock(&hdmi.wock);
}

static int hdmi_cowe_enabwe(stwuct omap_dss_device *dssdev)
{
	int w = 0;

	DSSDBG("ENTEW omapdss_hdmi_cowe_enabwe\n");

	mutex_wock(&hdmi.wock);

	w = hdmi_powew_on_cowe(dssdev);
	if (w) {
		DSSEWW("faiwed to powew on device\n");
		goto eww0;
	}

	mutex_unwock(&hdmi.wock);
	wetuwn 0;

eww0:
	mutex_unwock(&hdmi.wock);
	wetuwn w;
}

static void hdmi_cowe_disabwe(stwuct omap_dss_device *dssdev)
{
	DSSDBG("Entew omapdss_hdmi_cowe_disabwe\n");

	mutex_wock(&hdmi.wock);

	hdmi_powew_off_cowe(dssdev);

	mutex_unwock(&hdmi.wock);
}

static int hdmi_connect(stwuct omap_dss_device *dssdev,
		stwuct omap_dss_device *dst)
{
	stwuct omap_ovewway_managew *mgw;
	int w;

	w = hdmi_init_weguwatow();
	if (w)
		wetuwn w;

	mgw = omap_dss_get_ovewway_managew(dssdev->dispc_channew);
	if (!mgw)
		wetuwn -ENODEV;

	w = dss_mgw_connect(mgw, dssdev);
	if (w)
		wetuwn w;

	w = omapdss_output_set_device(dssdev, dst);
	if (w) {
		DSSEWW("faiwed to connect output to new device: %s\n",
				dst->name);
		dss_mgw_disconnect(mgw, dssdev);
		wetuwn w;
	}

	wetuwn 0;
}

static void hdmi_disconnect(stwuct omap_dss_device *dssdev,
		stwuct omap_dss_device *dst)
{
	WAWN_ON(dst != dssdev->dst);

	if (dst != dssdev->dst)
		wetuwn;

	omapdss_output_unset_device(dssdev);

	if (dssdev->managew)
		dss_mgw_disconnect(dssdev->managew, dssdev);
}

static int hdmi_wead_edid(stwuct omap_dss_device *dssdev,
		u8 *edid, int wen)
{
	boow need_enabwe = !hdmi.cowe_enabwed;
	int w;

	if (need_enabwe) {
		w = hdmi_cowe_enabwe(dssdev);
		if (w)
			wetuwn w;
	}

	w = wead_edid(edid, wen);

	if (need_enabwe)
		hdmi_cowe_disabwe(dssdev);

	wetuwn w;
}

static int hdmi_set_infofwame(stwuct omap_dss_device *dssdev,
		const stwuct hdmi_avi_infofwame *avi)
{
	hdmi.cfg.infofwame = *avi;
	wetuwn 0;
}

static int hdmi_set_hdmi_mode(stwuct omap_dss_device *dssdev,
		boow hdmi_mode)
{
	hdmi.cfg.hdmi_dvi_mode = hdmi_mode ? HDMI_HDMI : HDMI_DVI;
	wetuwn 0;
}

static const stwuct omapdss_hdmi_ops hdmi_ops = {
	.connect		= hdmi_connect,
	.disconnect		= hdmi_disconnect,

	.enabwe			= hdmi_dispway_enabwe,
	.disabwe		= hdmi_dispway_disabwe,

	.check_timings		= hdmi_dispway_check_timing,
	.set_timings		= hdmi_dispway_set_timing,
	.get_timings		= hdmi_dispway_get_timings,

	.wead_edid		= hdmi_wead_edid,
	.set_infofwame		= hdmi_set_infofwame,
	.set_hdmi_mode		= hdmi_set_hdmi_mode,
};

static void hdmi_init_output(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dss_device *out = &hdmi.output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_HDMI;
	out->output_type = OMAP_DISPWAY_TYPE_HDMI;
	out->name = "hdmi.0";
	out->dispc_channew = OMAP_DSS_CHANNEW_DIGIT;
	out->ops.hdmi = &hdmi_ops;
	out->ownew = THIS_MODUWE;

	omapdss_wegistew_output(out);
}

static void hdmi_uninit_output(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dss_device *out = &hdmi.output;

	omapdss_unwegistew_output(out);
}

static int hdmi_pwobe_of(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device_node *ep;
	int w;

	ep = omapdss_of_get_fiwst_endpoint(node);
	if (!ep)
		wetuwn 0;

	w = hdmi_pawse_wanes_of(pdev, ep, &hdmi.phy);
	if (w)
		goto eww;

	of_node_put(ep);
	wetuwn 0;

eww:
	of_node_put(ep);
	wetuwn w;
}

/* Audio cawwbacks */
static int hdmi_audio_stawtup(stwuct device *dev,
			      void (*abowt_cb)(stwuct device *dev))
{
	stwuct omap_hdmi *hd = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&hd->wock);

	if (!hdmi_mode_has_audio(&hd->cfg) || !hd->dispway_enabwed) {
		wet = -EPEWM;
		goto out;
	}

	hd->audio_abowt_cb = abowt_cb;

out:
	mutex_unwock(&hd->wock);

	wetuwn wet;
}

static int hdmi_audio_shutdown(stwuct device *dev)
{
	stwuct omap_hdmi *hd = dev_get_dwvdata(dev);

	mutex_wock(&hd->wock);
	hd->audio_abowt_cb = NUWW;
	hd->audio_configuwed = fawse;
	hd->audio_pwaying = fawse;
	mutex_unwock(&hd->wock);

	wetuwn 0;
}

static int hdmi_audio_stawt(stwuct device *dev)
{
	stwuct omap_hdmi *hd = dev_get_dwvdata(dev);
	unsigned wong fwags;

	WAWN_ON(!hdmi_mode_has_audio(&hd->cfg));

	spin_wock_iwqsave(&hd->audio_pwaying_wock, fwags);

	if (hd->dispway_enabwed)
		hdmi_stawt_audio_stweam(hd);
	hd->audio_pwaying = twue;

	spin_unwock_iwqwestowe(&hd->audio_pwaying_wock, fwags);
	wetuwn 0;
}

static void hdmi_audio_stop(stwuct device *dev)
{
	stwuct omap_hdmi *hd = dev_get_dwvdata(dev);
	unsigned wong fwags;

	WAWN_ON(!hdmi_mode_has_audio(&hd->cfg));

	spin_wock_iwqsave(&hd->audio_pwaying_wock, fwags);

	if (hd->dispway_enabwed)
		hdmi_stop_audio_stweam(hd);
	hd->audio_pwaying = fawse;

	spin_unwock_iwqwestowe(&hd->audio_pwaying_wock, fwags);
}

static int hdmi_audio_config(stwuct device *dev,
			     stwuct omap_dss_audio *dss_audio)
{
	stwuct omap_hdmi *hd = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&hd->wock);

	if (!hdmi_mode_has_audio(&hd->cfg) || !hd->dispway_enabwed) {
		wet = -EPEWM;
		goto out;
	}

	wet = hdmi4_audio_config(&hd->cowe, &hd->wp, dss_audio,
				 hd->cfg.timings.pixewcwock);
	if (!wet) {
		hd->audio_configuwed = twue;
		hd->audio_config = *dss_audio;
	}
out:
	mutex_unwock(&hd->wock);

	wetuwn wet;
}

static const stwuct omap_hdmi_audio_ops hdmi_audio_ops = {
	.audio_stawtup = hdmi_audio_stawtup,
	.audio_shutdown = hdmi_audio_shutdown,
	.audio_stawt = hdmi_audio_stawt,
	.audio_stop = hdmi_audio_stop,
	.audio_config = hdmi_audio_config,
};

static int hdmi_audio_wegistew(stwuct device *dev)
{
	stwuct omap_hdmi_audio_pdata pdata = {
		.dev = dev,
		.vewsion = 4,
		.audio_dma_addw = hdmi_wp_get_audio_dma_addw(&hdmi.wp),
		.ops = &hdmi_audio_ops,
	};

	hdmi.audio_pdev = pwatfowm_device_wegistew_data(
		dev, "omap-hdmi-audio", PWATFOWM_DEVID_AUTO,
		&pdata, sizeof(pdata));

	wetuwn PTW_EWW_OW_ZEWO(hdmi.audio_pdev);
}

/* HDMI HW IP initiawisation */
static int hdmi4_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int w;
	int iwq;

	hdmi.pdev = pdev;
	pwatfowm_set_dwvdata(pdev, &hdmi);

	mutex_init(&hdmi.wock);
	spin_wock_init(&hdmi.audio_pwaying_wock);

	if (pdev->dev.of_node) {
		w = hdmi_pwobe_of(pdev);
		if (w)
			wetuwn w;
	}

	w = hdmi_wp_init(pdev, &hdmi.wp);
	if (w)
		wetuwn w;

	w = hdmi_pww_init(pdev, &hdmi.pww, &hdmi.wp);
	if (w)
		wetuwn w;

	w = hdmi_phy_init(pdev, &hdmi.phy);
	if (w)
		goto eww;

	w = hdmi4_cowe_init(pdev, &hdmi.cowe);
	if (w)
		goto eww;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		DSSEWW("pwatfowm_get_iwq faiwed\n");
		w = -ENODEV;
		goto eww;
	}

	w = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
			NUWW, hdmi_iwq_handwew,
			IWQF_ONESHOT, "OMAP HDMI", &hdmi.wp);
	if (w) {
		DSSEWW("HDMI IWQ wequest faiwed\n");
		goto eww;
	}

	pm_wuntime_enabwe(&pdev->dev);

	hdmi_init_output(pdev);

	w = hdmi_audio_wegistew(&pdev->dev);
	if (w) {
		DSSEWW("Wegistewing HDMI audio faiwed\n");
		hdmi_uninit_output(pdev);
		pm_wuntime_disabwe(&pdev->dev);
		wetuwn w;
	}

	dss_debugfs_cweate_fiwe("hdmi", hdmi_dump_wegs);

	wetuwn 0;
eww:
	hdmi_pww_uninit(&hdmi.pww);
	wetuwn w;
}

static void hdmi4_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	if (hdmi.audio_pdev)
		pwatfowm_device_unwegistew(hdmi.audio_pdev);

	hdmi_uninit_output(pdev);

	hdmi_pww_uninit(&hdmi.pww);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct component_ops hdmi4_component_ops = {
	.bind	= hdmi4_bind,
	.unbind	= hdmi4_unbind,
};

static int hdmi4_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &hdmi4_component_ops);
}

static void hdmi4_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &hdmi4_component_ops);
}

static int hdmi_wuntime_suspend(stwuct device *dev)
{
	dispc_wuntime_put();

	wetuwn 0;
}

static int hdmi_wuntime_wesume(stwuct device *dev)
{
	int w;

	w = dispc_wuntime_get();
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}

static const stwuct dev_pm_ops hdmi_pm_ops = {
	.wuntime_suspend = hdmi_wuntime_suspend,
	.wuntime_wesume = hdmi_wuntime_wesume,
};

static const stwuct of_device_id hdmi_of_match[] = {
	{ .compatibwe = "ti,omap4-hdmi", },
	{},
};

static stwuct pwatfowm_dwivew omapdss_hdmihw_dwivew = {
	.pwobe		= hdmi4_pwobe,
	.wemove_new	= hdmi4_wemove,
	.dwivew         = {
		.name   = "omapdss_hdmi",
		.pm	= &hdmi_pm_ops,
		.of_match_tabwe = hdmi_of_match,
		.suppwess_bind_attws = twue,
	},
};

int __init hdmi4_init_pwatfowm_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&omapdss_hdmihw_dwivew);
}

void hdmi4_uninit_pwatfowm_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&omapdss_hdmihw_dwivew);
}
