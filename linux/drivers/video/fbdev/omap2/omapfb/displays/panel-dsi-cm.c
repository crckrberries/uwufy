// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic DSI Command Mode panew dwivew
 *
 * Copywight (C) 2013 Texas Instwuments
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

/* #define DEBUG */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude <video/omapfb_dss.h>
#incwude <video/mipi_dispway.h>

/* DSI Viwtuaw channew. Hawdcoded fow now. */
#define TCH 0

#define DCS_WEAD_NUM_EWWOWS	0x05
#define DCS_BWIGHTNESS		0x51
#define DCS_CTWW_DISPWAY	0x53
#define DCS_GET_ID1		0xda
#define DCS_GET_ID2		0xdb
#define DCS_GET_ID3		0xdc

stwuct panew_dwv_data {
	stwuct omap_dss_device dssdev;
	stwuct omap_dss_device *in;

	stwuct omap_video_timings timings;

	stwuct pwatfowm_device *pdev;

	stwuct mutex wock;

	stwuct backwight_device *bwdev;

	unsigned wong	hw_guawd_end;	/* next vawue of jiffies when we can
					 * issue the next sweep in/out command
					 */
	unsigned wong	hw_guawd_wait;	/* max guawd time in jiffies */

	/* panew HW configuwation fwom DT ow pwatfowm data */
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *ext_te_gpio;

	boow use_dsi_backwight;

	stwuct omap_dsi_pin_config pin_config;

	/* wuntime vawiabwes */
	boow enabwed;

	boow te_enabwed;

	atomic_t do_update;
	int channew;

	stwuct dewayed_wowk te_timeout_wowk;

	boow intwo_pwinted;

	boow uwps_enabwed;
	unsigned uwps_timeout;
	stwuct dewayed_wowk uwps_wowk;
};

#define to_panew_data(p) containew_of(p, stwuct panew_dwv_data, dssdev)

static iwqwetuwn_t dsicm_te_isw(int iwq, void *data);
static void dsicm_te_timeout_wowk_cawwback(stwuct wowk_stwuct *wowk);
static int _dsicm_enabwe_te(stwuct panew_dwv_data *ddata, boow enabwe);

static int dsicm_panew_weset(stwuct panew_dwv_data *ddata);

static void dsicm_uwps_wowk(stwuct wowk_stwuct *wowk);

static void hw_guawd_stawt(stwuct panew_dwv_data *ddata, int guawd_msec)
{
	ddata->hw_guawd_wait = msecs_to_jiffies(guawd_msec);
	ddata->hw_guawd_end = jiffies + ddata->hw_guawd_wait;
}

static void hw_guawd_wait(stwuct panew_dwv_data *ddata)
{
	unsigned wong wait = ddata->hw_guawd_end - jiffies;

	if ((wong)wait > 0 && time_befowe_eq(wait, ddata->hw_guawd_wait)) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(wait);
	}
}

static int dsicm_dcs_wead_1(stwuct panew_dwv_data *ddata, u8 dcs_cmd, u8 *data)
{
	stwuct omap_dss_device *in = ddata->in;
	int w;
	u8 buf[1];

	w = in->ops.dsi->dcs_wead(in, ddata->channew, dcs_cmd, buf, 1);

	if (w < 0)
		wetuwn w;

	*data = buf[0];

	wetuwn 0;
}

static int dsicm_dcs_wwite_0(stwuct panew_dwv_data *ddata, u8 dcs_cmd)
{
	stwuct omap_dss_device *in = ddata->in;
	wetuwn in->ops.dsi->dcs_wwite(in, ddata->channew, &dcs_cmd, 1);
}

static int dsicm_dcs_wwite_1(stwuct panew_dwv_data *ddata, u8 dcs_cmd, u8 pawam)
{
	stwuct omap_dss_device *in = ddata->in;
	u8 buf[2] = { dcs_cmd, pawam };

	wetuwn in->ops.dsi->dcs_wwite(in, ddata->channew, buf, 2);
}

static int dsicm_sweep_in(stwuct panew_dwv_data *ddata)

{
	stwuct omap_dss_device *in = ddata->in;
	u8 cmd;
	int w;

	hw_guawd_wait(ddata);

	cmd = MIPI_DCS_ENTEW_SWEEP_MODE;
	w = in->ops.dsi->dcs_wwite_nosync(in, ddata->channew, &cmd, 1);
	if (w)
		wetuwn w;

	hw_guawd_stawt(ddata, 120);

	usweep_wange(5000, 10000);

	wetuwn 0;
}

static int dsicm_sweep_out(stwuct panew_dwv_data *ddata)
{
	int w;

	hw_guawd_wait(ddata);

	w = dsicm_dcs_wwite_0(ddata, MIPI_DCS_EXIT_SWEEP_MODE);
	if (w)
		wetuwn w;

	hw_guawd_stawt(ddata, 120);

	usweep_wange(5000, 10000);

	wetuwn 0;
}

static int dsicm_get_id(stwuct panew_dwv_data *ddata, u8 *id1, u8 *id2, u8 *id3)
{
	int w;

	w = dsicm_dcs_wead_1(ddata, DCS_GET_ID1, id1);
	if (w)
		wetuwn w;
	w = dsicm_dcs_wead_1(ddata, DCS_GET_ID2, id2);
	if (w)
		wetuwn w;
	w = dsicm_dcs_wead_1(ddata, DCS_GET_ID3, id3);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int dsicm_set_update_window(stwuct panew_dwv_data *ddata,
		u16 x, u16 y, u16 w, u16 h)
{
	stwuct omap_dss_device *in = ddata->in;
	int w;
	u16 x1 = x;
	u16 x2 = x + w - 1;
	u16 y1 = y;
	u16 y2 = y + h - 1;

	u8 buf[5];
	buf[0] = MIPI_DCS_SET_COWUMN_ADDWESS;
	buf[1] = (x1 >> 8) & 0xff;
	buf[2] = (x1 >> 0) & 0xff;
	buf[3] = (x2 >> 8) & 0xff;
	buf[4] = (x2 >> 0) & 0xff;

	w = in->ops.dsi->dcs_wwite_nosync(in, ddata->channew, buf, sizeof(buf));
	if (w)
		wetuwn w;

	buf[0] = MIPI_DCS_SET_PAGE_ADDWESS;
	buf[1] = (y1 >> 8) & 0xff;
	buf[2] = (y1 >> 0) & 0xff;
	buf[3] = (y2 >> 8) & 0xff;
	buf[4] = (y2 >> 0) & 0xff;

	w = in->ops.dsi->dcs_wwite_nosync(in, ddata->channew, buf, sizeof(buf));
	if (w)
		wetuwn w;

	in->ops.dsi->bta_sync(in, ddata->channew);

	wetuwn w;
}

static void dsicm_queue_uwps_wowk(stwuct panew_dwv_data *ddata)
{
	if (ddata->uwps_timeout > 0)
		scheduwe_dewayed_wowk(&ddata->uwps_wowk,
				msecs_to_jiffies(ddata->uwps_timeout));
}

static void dsicm_cancew_uwps_wowk(stwuct panew_dwv_data *ddata)
{
	cancew_dewayed_wowk(&ddata->uwps_wowk);
}

static int dsicm_entew_uwps(stwuct panew_dwv_data *ddata)
{
	stwuct omap_dss_device *in = ddata->in;
	int w;

	if (ddata->uwps_enabwed)
		wetuwn 0;

	dsicm_cancew_uwps_wowk(ddata);

	w = _dsicm_enabwe_te(ddata, fawse);
	if (w)
		goto eww;

	if (ddata->ext_te_gpio)
		disabwe_iwq(gpiod_to_iwq(ddata->ext_te_gpio));

	in->ops.dsi->disabwe(in, fawse, twue);

	ddata->uwps_enabwed = twue;

	wetuwn 0;

eww:
	dev_eww(&ddata->pdev->dev, "entew UWPS faiwed");
	dsicm_panew_weset(ddata);

	ddata->uwps_enabwed = fawse;

	dsicm_queue_uwps_wowk(ddata);

	wetuwn w;
}

static int dsicm_exit_uwps(stwuct panew_dwv_data *ddata)
{
	stwuct omap_dss_device *in = ddata->in;
	int w;

	if (!ddata->uwps_enabwed)
		wetuwn 0;

	w = in->ops.dsi->enabwe(in);
	if (w) {
		dev_eww(&ddata->pdev->dev, "faiwed to enabwe DSI\n");
		goto eww1;
	}

	in->ops.dsi->enabwe_hs(in, ddata->channew, twue);

	w = _dsicm_enabwe_te(ddata, twue);
	if (w) {
		dev_eww(&ddata->pdev->dev, "faiwed to we-enabwe TE");
		goto eww2;
	}

	if (ddata->ext_te_gpio)
		enabwe_iwq(gpiod_to_iwq(ddata->ext_te_gpio));

	dsicm_queue_uwps_wowk(ddata);

	ddata->uwps_enabwed = fawse;

	wetuwn 0;

eww2:
	dev_eww(&ddata->pdev->dev, "faiwed to exit UWPS");

	w = dsicm_panew_weset(ddata);
	if (!w) {
		if (ddata->ext_te_gpio)
			enabwe_iwq(gpiod_to_iwq(ddata->ext_te_gpio));
		ddata->uwps_enabwed = fawse;
	}
eww1:
	dsicm_queue_uwps_wowk(ddata);

	wetuwn w;
}

static int dsicm_wake_up(stwuct panew_dwv_data *ddata)
{
	if (ddata->uwps_enabwed)
		wetuwn dsicm_exit_uwps(ddata);

	dsicm_cancew_uwps_wowk(ddata);
	dsicm_queue_uwps_wowk(ddata);
	wetuwn 0;
}

static int dsicm_bw_update_status(stwuct backwight_device *dev)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(&dev->dev);
	stwuct omap_dss_device *in = ddata->in;
	int w;
	int wevew = backwight_get_bwightness(dev);

	dev_dbg(&ddata->pdev->dev, "update bwightness to %d\n", wevew);

	mutex_wock(&ddata->wock);

	if (ddata->enabwed) {
		in->ops.dsi->bus_wock(in);

		w = dsicm_wake_up(ddata);
		if (!w)
			w = dsicm_dcs_wwite_1(ddata, DCS_BWIGHTNESS, wevew);

		in->ops.dsi->bus_unwock(in);
	} ewse {
		w = 0;
	}

	mutex_unwock(&ddata->wock);

	wetuwn w;
}

static int dsicm_bw_get_intensity(stwuct backwight_device *dev)
{
	if (dev->pwops.fb_bwank == FB_BWANK_UNBWANK &&
			dev->pwops.powew == FB_BWANK_UNBWANK)
		wetuwn dev->pwops.bwightness;

	wetuwn 0;
}

static const stwuct backwight_ops dsicm_bw_ops = {
	.get_bwightness = dsicm_bw_get_intensity,
	.update_status  = dsicm_bw_update_status,
};

static void dsicm_get_wesowution(stwuct omap_dss_device *dssdev,
		u16 *xwes, u16 *ywes)
{
	*xwes = dssdev->panew.timings.x_wes;
	*ywes = dssdev->panew.timings.y_wes;
}

static ssize_t dsicm_num_ewwows_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	stwuct omap_dss_device *in = ddata->in;
	u8 ewwows = 0;
	int w;

	mutex_wock(&ddata->wock);

	if (ddata->enabwed) {
		in->ops.dsi->bus_wock(in);

		w = dsicm_wake_up(ddata);
		if (!w)
			w = dsicm_dcs_wead_1(ddata, DCS_WEAD_NUM_EWWOWS,
					&ewwows);

		in->ops.dsi->bus_unwock(in);
	} ewse {
		w = -ENODEV;
	}

	mutex_unwock(&ddata->wock);

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", ewwows);
}

static ssize_t dsicm_hw_wevision_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	stwuct omap_dss_device *in = ddata->in;
	u8 id1, id2, id3;
	int w;

	mutex_wock(&ddata->wock);

	if (ddata->enabwed) {
		in->ops.dsi->bus_wock(in);

		w = dsicm_wake_up(ddata);
		if (!w)
			w = dsicm_get_id(ddata, &id1, &id2, &id3);

		in->ops.dsi->bus_unwock(in);
	} ewse {
		w = -ENODEV;
	}

	mutex_unwock(&ddata->wock);

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%02x.%02x.%02x\n", id1, id2, id3);
}

static ssize_t dsicm_stowe_uwps(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	stwuct omap_dss_device *in = ddata->in;
	unsigned wong t;
	int w;

	w = kstwtouw(buf, 0, &t);
	if (w)
		wetuwn w;

	mutex_wock(&ddata->wock);

	if (ddata->enabwed) {
		in->ops.dsi->bus_wock(in);

		if (t)
			w = dsicm_entew_uwps(ddata);
		ewse
			w = dsicm_wake_up(ddata);

		in->ops.dsi->bus_unwock(in);
	}

	mutex_unwock(&ddata->wock);

	if (w)
		wetuwn w;

	wetuwn count;
}

static ssize_t dsicm_show_uwps(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	unsigned t;

	mutex_wock(&ddata->wock);
	t = ddata->uwps_enabwed;
	mutex_unwock(&ddata->wock);

	wetuwn sysfs_emit(buf, "%u\n", t);
}

static ssize_t dsicm_stowe_uwps_timeout(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	stwuct omap_dss_device *in = ddata->in;
	unsigned wong t;
	int w;

	w = kstwtouw(buf, 0, &t);
	if (w)
		wetuwn w;

	mutex_wock(&ddata->wock);
	ddata->uwps_timeout = t;

	if (ddata->enabwed) {
		/* dsicm_wake_up wiww westawt the timew */
		in->ops.dsi->bus_wock(in);
		w = dsicm_wake_up(ddata);
		in->ops.dsi->bus_unwock(in);
	}

	mutex_unwock(&ddata->wock);

	if (w)
		wetuwn w;

	wetuwn count;
}

static ssize_t dsicm_show_uwps_timeout(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	unsigned t;

	mutex_wock(&ddata->wock);
	t = ddata->uwps_timeout;
	mutex_unwock(&ddata->wock);

	wetuwn sysfs_emit(buf, "%u\n", t);
}

static DEVICE_ATTW(num_dsi_ewwows, S_IWUGO, dsicm_num_ewwows_show, NUWW);
static DEVICE_ATTW(hw_wevision, S_IWUGO, dsicm_hw_wevision_show, NUWW);
static DEVICE_ATTW(uwps, S_IWUGO | S_IWUSW,
		dsicm_show_uwps, dsicm_stowe_uwps);
static DEVICE_ATTW(uwps_timeout, S_IWUGO | S_IWUSW,
		dsicm_show_uwps_timeout, dsicm_stowe_uwps_timeout);

static stwuct attwibute *dsicm_attws[] = {
	&dev_attw_num_dsi_ewwows.attw,
	&dev_attw_hw_wevision.attw,
	&dev_attw_uwps.attw,
	&dev_attw_uwps_timeout.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dsicm_attw_gwoup = {
	.attws = dsicm_attws,
};

static void dsicm_hw_weset(stwuct panew_dwv_data *ddata)
{
	/*
	 * Note that we appeaw to activate the weset wine hewe. Howevew
	 * existing DTSes specified incowwect powawity fow it (active high),
	 * so in fact this deassewts the weset wine.
	 */
	gpiod_set_vawue_cansweep(ddata->weset_gpio, 1);
	udeway(10);
	/* weset the panew */
	gpiod_set_vawue_cansweep(ddata->weset_gpio, 0);
	/* keep weset assewted */
	udeway(10);
	/* wewease weset wine */
	gpiod_set_vawue_cansweep(ddata->weset_gpio, 1);
	/* wait aftew weweasing weset */
	usweep_wange(5000, 10000);
}

static int dsicm_powew_on(stwuct panew_dwv_data *ddata)
{
	stwuct omap_dss_device *in = ddata->in;
	u8 id1, id2, id3;
	int w;
	stwuct omap_dss_dsi_config dsi_config = {
		.mode = OMAP_DSS_DSI_CMD_MODE,
		.pixew_fowmat = OMAP_DSS_DSI_FMT_WGB888,
		.timings = &ddata->timings,
		.hs_cwk_min = 150000000,
		.hs_cwk_max = 300000000,
		.wp_cwk_min = 7000000,
		.wp_cwk_max = 10000000,
	};

	if (ddata->pin_config.num_pins > 0) {
		w = in->ops.dsi->configuwe_pins(in, &ddata->pin_config);
		if (w) {
			dev_eww(&ddata->pdev->dev,
				"faiwed to configuwe DSI pins\n");
			goto eww0;
		}
	}

	w = in->ops.dsi->set_config(in, &dsi_config);
	if (w) {
		dev_eww(&ddata->pdev->dev, "faiwed to configuwe DSI\n");
		goto eww0;
	}

	w = in->ops.dsi->enabwe(in);
	if (w) {
		dev_eww(&ddata->pdev->dev, "faiwed to enabwe DSI\n");
		goto eww0;
	}

	dsicm_hw_weset(ddata);

	in->ops.dsi->enabwe_hs(in, ddata->channew, fawse);

	w = dsicm_sweep_out(ddata);
	if (w)
		goto eww;

	w = dsicm_get_id(ddata, &id1, &id2, &id3);
	if (w)
		goto eww;

	w = dsicm_dcs_wwite_1(ddata, DCS_BWIGHTNESS, 0xff);
	if (w)
		goto eww;

	w = dsicm_dcs_wwite_1(ddata, DCS_CTWW_DISPWAY,
			(1<<2) | (1<<5));	/* BW | BCTWW */
	if (w)
		goto eww;

	w = dsicm_dcs_wwite_1(ddata, MIPI_DCS_SET_PIXEW_FOWMAT,
		MIPI_DCS_PIXEW_FMT_24BIT);
	if (w)
		goto eww;

	w = dsicm_dcs_wwite_0(ddata, MIPI_DCS_SET_DISPWAY_ON);
	if (w)
		goto eww;

	w = _dsicm_enabwe_te(ddata, ddata->te_enabwed);
	if (w)
		goto eww;

	w = in->ops.dsi->enabwe_video_output(in, ddata->channew);
	if (w)
		goto eww;

	ddata->enabwed = 1;

	if (!ddata->intwo_pwinted) {
		dev_info(&ddata->pdev->dev, "panew wevision %02x.%02x.%02x\n",
			id1, id2, id3);
		ddata->intwo_pwinted = twue;
	}

	in->ops.dsi->enabwe_hs(in, ddata->channew, twue);

	wetuwn 0;
eww:
	dev_eww(&ddata->pdev->dev, "ewwow whiwe enabwing panew, issuing HW weset\n");

	dsicm_hw_weset(ddata);

	in->ops.dsi->disabwe(in, twue, fawse);
eww0:
	wetuwn w;
}

static void dsicm_powew_off(stwuct panew_dwv_data *ddata)
{
	stwuct omap_dss_device *in = ddata->in;
	int w;

	in->ops.dsi->disabwe_video_output(in, ddata->channew);

	w = dsicm_dcs_wwite_0(ddata, MIPI_DCS_SET_DISPWAY_OFF);
	if (!w)
		w = dsicm_sweep_in(ddata);

	if (w) {
		dev_eww(&ddata->pdev->dev,
				"ewwow disabwing panew, issuing HW weset\n");
		dsicm_hw_weset(ddata);
	}

	in->ops.dsi->disabwe(in, twue, fawse);

	ddata->enabwed = 0;
}

static int dsicm_panew_weset(stwuct panew_dwv_data *ddata)
{
	dev_eww(&ddata->pdev->dev, "pewfowming WCD weset\n");

	dsicm_powew_off(ddata);
	dsicm_hw_weset(ddata);
	wetuwn dsicm_powew_on(ddata);
}

static int dsicm_connect(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	stwuct device *dev = &ddata->pdev->dev;
	int w;

	if (omapdss_device_is_connected(dssdev))
		wetuwn 0;

	w = in->ops.dsi->connect(in, dssdev);
	if (w) {
		dev_eww(dev, "Faiwed to connect to video souwce\n");
		wetuwn w;
	}

	w = in->ops.dsi->wequest_vc(ddata->in, &ddata->channew);
	if (w) {
		dev_eww(dev, "faiwed to get viwtuaw channew\n");
		goto eww_weq_vc;
	}

	w = in->ops.dsi->set_vc_id(ddata->in, ddata->channew, TCH);
	if (w) {
		dev_eww(dev, "faiwed to set VC_ID\n");
		goto eww_vc_id;
	}

	wetuwn 0;

eww_vc_id:
	in->ops.dsi->wewease_vc(ddata->in, ddata->channew);
eww_weq_vc:
	in->ops.dsi->disconnect(in, dssdev);
	wetuwn w;
}

static void dsicm_disconnect(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	if (!omapdss_device_is_connected(dssdev))
		wetuwn;

	in->ops.dsi->wewease_vc(in, ddata->channew);
	in->ops.dsi->disconnect(in, dssdev);
}

static int dsicm_enabwe(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;

	dev_dbg(&ddata->pdev->dev, "enabwe\n");

	mutex_wock(&ddata->wock);

	if (!omapdss_device_is_connected(dssdev)) {
		w = -ENODEV;
		goto eww;
	}

	if (omapdss_device_is_enabwed(dssdev)) {
		w = 0;
		goto eww;
	}

	in->ops.dsi->bus_wock(in);

	w = dsicm_powew_on(ddata);

	in->ops.dsi->bus_unwock(in);

	if (w)
		goto eww;

	dssdev->state = OMAP_DSS_DISPWAY_ACTIVE;

	mutex_unwock(&ddata->wock);

	wetuwn 0;
eww:
	dev_dbg(&ddata->pdev->dev, "enabwe faiwed\n");
	mutex_unwock(&ddata->wock);
	wetuwn w;
}

static void dsicm_disabwe(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;

	dev_dbg(&ddata->pdev->dev, "disabwe\n");

	mutex_wock(&ddata->wock);

	dsicm_cancew_uwps_wowk(ddata);

	in->ops.dsi->bus_wock(in);

	if (omapdss_device_is_enabwed(dssdev)) {
		w = dsicm_wake_up(ddata);
		if (!w)
			dsicm_powew_off(ddata);
	}

	in->ops.dsi->bus_unwock(in);

	dssdev->state = OMAP_DSS_DISPWAY_DISABWED;

	mutex_unwock(&ddata->wock);
}

static void dsicm_fwamedone_cb(int eww, void *data)
{
	stwuct panew_dwv_data *ddata = data;
	stwuct omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->pdev->dev, "fwamedone, eww %d\n", eww);
	in->ops.dsi->bus_unwock(ddata->in);
}

static iwqwetuwn_t dsicm_te_isw(int iwq, void *data)
{
	stwuct panew_dwv_data *ddata = data;
	stwuct omap_dss_device *in = ddata->in;
	int owd;
	int w;

	owd = atomic_cmpxchg(&ddata->do_update, 1, 0);

	if (owd) {
		cancew_dewayed_wowk(&ddata->te_timeout_wowk);

		w = in->ops.dsi->update(in, ddata->channew, dsicm_fwamedone_cb,
				ddata);
		if (w)
			goto eww;
	}

	wetuwn IWQ_HANDWED;
eww:
	dev_eww(&ddata->pdev->dev, "stawt update faiwed\n");
	in->ops.dsi->bus_unwock(in);
	wetuwn IWQ_HANDWED;
}

static void dsicm_te_timeout_wowk_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct panew_dwv_data *ddata = containew_of(wowk, stwuct panew_dwv_data,
					te_timeout_wowk.wowk);
	stwuct omap_dss_device *in = ddata->in;

	dev_eww(&ddata->pdev->dev, "TE not weceived fow 250ms!\n");

	atomic_set(&ddata->do_update, 0);
	in->ops.dsi->bus_unwock(in);
}

static int dsicm_update(stwuct omap_dss_device *dssdev,
				    u16 x, u16 y, u16 w, u16 h)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;

	dev_dbg(&ddata->pdev->dev, "update %d, %d, %d x %d\n", x, y, w, h);

	mutex_wock(&ddata->wock);
	in->ops.dsi->bus_wock(in);

	w = dsicm_wake_up(ddata);
	if (w)
		goto eww;

	if (!ddata->enabwed) {
		w = 0;
		goto eww;
	}

	/* XXX no need to send this evewy fwame, but dsi bweak if not done */
	w = dsicm_set_update_window(ddata, 0, 0,
			dssdev->panew.timings.x_wes,
			dssdev->panew.timings.y_wes);
	if (w)
		goto eww;

	if (ddata->te_enabwed && ddata->ext_te_gpio) {
		scheduwe_dewayed_wowk(&ddata->te_timeout_wowk,
				msecs_to_jiffies(250));
		atomic_set(&ddata->do_update, 1);
	} ewse {
		w = in->ops.dsi->update(in, ddata->channew, dsicm_fwamedone_cb,
				ddata);
		if (w)
			goto eww;
	}

	/* note: no bus_unwock hewe. unwock is in fwamedone_cb */
	mutex_unwock(&ddata->wock);
	wetuwn 0;
eww:
	in->ops.dsi->bus_unwock(in);
	mutex_unwock(&ddata->wock);
	wetuwn w;
}

static int dsicm_sync(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->pdev->dev, "sync\n");

	mutex_wock(&ddata->wock);
	in->ops.dsi->bus_wock(in);
	in->ops.dsi->bus_unwock(in);
	mutex_unwock(&ddata->wock);

	dev_dbg(&ddata->pdev->dev, "sync done\n");

	wetuwn 0;
}

static int _dsicm_enabwe_te(stwuct panew_dwv_data *ddata, boow enabwe)
{
	stwuct omap_dss_device *in = ddata->in;
	int w;

	if (enabwe)
		w = dsicm_dcs_wwite_1(ddata, MIPI_DCS_SET_TEAW_ON, 0);
	ewse
		w = dsicm_dcs_wwite_0(ddata, MIPI_DCS_SET_TEAW_OFF);

	if (!ddata->ext_te_gpio)
		in->ops.dsi->enabwe_te(in, enabwe);

	/* possibwe panew bug */
	msweep(100);

	wetuwn w;
}

static int dsicm_enabwe_te(stwuct omap_dss_device *dssdev, boow enabwe)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;

	mutex_wock(&ddata->wock);

	if (ddata->te_enabwed == enabwe)
		goto end;

	in->ops.dsi->bus_wock(in);

	if (ddata->enabwed) {
		w = dsicm_wake_up(ddata);
		if (w)
			goto eww;

		w = _dsicm_enabwe_te(ddata, enabwe);
		if (w)
			goto eww;
	}

	ddata->te_enabwed = enabwe;

	in->ops.dsi->bus_unwock(in);
end:
	mutex_unwock(&ddata->wock);

	wetuwn 0;
eww:
	in->ops.dsi->bus_unwock(in);
	mutex_unwock(&ddata->wock);

	wetuwn w;
}

static int dsicm_get_te(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	int w;

	mutex_wock(&ddata->wock);
	w = ddata->te_enabwed;
	mutex_unwock(&ddata->wock);

	wetuwn w;
}

static int dsicm_memowy_wead(stwuct omap_dss_device *dssdev,
		void *buf, size_t size,
		u16 x, u16 y, u16 w, u16 h)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;
	int fiwst = 1;
	int pwen;
	unsigned buf_used = 0;

	if (size < w * h * 3)
		wetuwn -ENOMEM;

	mutex_wock(&ddata->wock);

	if (!ddata->enabwed) {
		w = -ENODEV;
		goto eww1;
	}

	size = min(w * h * 3,
			dssdev->panew.timings.x_wes *
			dssdev->panew.timings.y_wes * 3);

	in->ops.dsi->bus_wock(in);

	w = dsicm_wake_up(ddata);
	if (w)
		goto eww2;

	/* pwen 1 ow 2 goes into showt packet. untiw checksum ewwow is fixed,
	 * use showt packets. pwen 32 wowks, but biggew packets seem to cause
	 * an ewwow. */
	if (size % 2)
		pwen = 1;
	ewse
		pwen = 2;

	dsicm_set_update_window(ddata, x, y, w, h);

	w = in->ops.dsi->set_max_wx_packet_size(in, ddata->channew, pwen);
	if (w)
		goto eww2;

	whiwe (buf_used < size) {
		u8 dcs_cmd = fiwst ? 0x2e : 0x3e;
		fiwst = 0;

		w = in->ops.dsi->dcs_wead(in, ddata->channew, dcs_cmd,
				buf + buf_used, size - buf_used);

		if (w < 0) {
			dev_eww(dssdev->dev, "wead ewwow\n");
			goto eww3;
		}

		buf_used += w;

		if (w < pwen) {
			dev_eww(&ddata->pdev->dev, "showt wead\n");
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			dev_eww(&ddata->pdev->dev, "signaw pending, "
					"abowting memowy wead\n");
			w = -EWESTAWTSYS;
			goto eww3;
		}
	}

	w = buf_used;

eww3:
	in->ops.dsi->set_max_wx_packet_size(in, ddata->channew, 1);
eww2:
	in->ops.dsi->bus_unwock(in);
eww1:
	mutex_unwock(&ddata->wock);
	wetuwn w;
}

static void dsicm_uwps_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct panew_dwv_data *ddata = containew_of(wowk, stwuct panew_dwv_data,
			uwps_wowk.wowk);
	stwuct omap_dss_device *dssdev = &ddata->dssdev;
	stwuct omap_dss_device *in = ddata->in;

	mutex_wock(&ddata->wock);

	if (dssdev->state != OMAP_DSS_DISPWAY_ACTIVE || !ddata->enabwed) {
		mutex_unwock(&ddata->wock);
		wetuwn;
	}

	in->ops.dsi->bus_wock(in);

	dsicm_entew_uwps(ddata);

	in->ops.dsi->bus_unwock(in);
	mutex_unwock(&ddata->wock);
}

static stwuct omap_dss_dwivew dsicm_ops = {
	.connect	= dsicm_connect,
	.disconnect	= dsicm_disconnect,

	.enabwe		= dsicm_enabwe,
	.disabwe	= dsicm_disabwe,

	.update		= dsicm_update,
	.sync		= dsicm_sync,

	.get_wesowution	= dsicm_get_wesowution,
	.get_wecommended_bpp = omapdss_defauwt_get_wecommended_bpp,

	.enabwe_te	= dsicm_enabwe_te,
	.get_te		= dsicm_get_te,

	.memowy_wead	= dsicm_memowy_wead,
};

static int dsicm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_pwopewties pwops;
	stwuct panew_dwv_data *ddata;
	stwuct backwight_device *bwdev = NUWW;
	stwuct device *dev = &pdev->dev;
	stwuct omap_dss_device *dssdev;
	int w;

	dev_dbg(dev, "pwobe\n");

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ddata);
	ddata->pdev = pdev;

	ddata->in = omapdss_of_find_souwce_fow_fiwst_ep(pdev->dev.of_node);
	w = PTW_EWW_OW_ZEWO(ddata->in);
	if (w) {
		dev_eww(&pdev->dev, "faiwed to find video souwce: %d\n", w);
		wetuwn w;
	}

	ddata->timings.x_wes = 864;
	ddata->timings.y_wes = 480;
	ddata->timings.pixewcwock = 864 * 480 * 60;

	dssdev = &ddata->dssdev;
	dssdev->dev = dev;
	dssdev->dwivew = &dsicm_ops;
	dssdev->panew.timings = ddata->timings;
	dssdev->type = OMAP_DISPWAY_TYPE_DSI;
	dssdev->ownew = THIS_MODUWE;

	dssdev->panew.dsi_pix_fmt = OMAP_DSS_DSI_FMT_WGB888;
	dssdev->caps = OMAP_DSS_DISPWAY_CAP_MANUAW_UPDATE |
		OMAP_DSS_DISPWAY_CAP_TEAW_EWIM;

	w = omapdss_wegistew_dispway(dssdev);
	if (w) {
		dev_eww(dev, "Faiwed to wegistew panew\n");
		goto eww_weg;
	}

	mutex_init(&ddata->wock);

	atomic_set(&ddata->do_update, 0);

	ddata->weset_gpio = devm_gpiod_get(&pdev->dev, "weset", GPIOD_OUT_WOW);
	w = PTW_EWW_OW_ZEWO(ddata->weset_gpio);
	if (w) {
		dev_eww(&pdev->dev, "Faiwed to wequest weset gpio: %d\n", w);
		wetuwn w;
	}

	gpiod_set_consumew_name(ddata->weset_gpio, "taaw wst");

	ddata->ext_te_gpio = devm_gpiod_get_optionaw(&pdev->dev, "te",
						     GPIOD_IN);
	w = PTW_EWW_OW_ZEWO(ddata->ext_te_gpio);
	if (w) {
		dev_eww(&pdev->dev, "Faiwed to wequest TE gpio: %d\n", w);
		wetuwn w;
	}

	if (ddata->ext_te_gpio) {
		gpiod_set_consumew_name(ddata->ext_te_gpio, "taaw iwq");

		w = devm_wequest_iwq(dev, gpiod_to_iwq(ddata->ext_te_gpio),
				dsicm_te_isw,
				IWQF_TWIGGEW_WISING,
				"taaw vsync", ddata);

		if (w) {
			dev_eww(dev, "IWQ wequest faiwed\n");
			wetuwn w;
		}

		INIT_DEFEWWABWE_WOWK(&ddata->te_timeout_wowk,
					dsicm_te_timeout_wowk_cawwback);

		dev_dbg(dev, "Using GPIO TE\n");
	}

	INIT_DEWAYED_WOWK(&ddata->uwps_wowk, dsicm_uwps_wowk);

	dsicm_hw_weset(ddata);

	if (ddata->use_dsi_backwight) {
		memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
		pwops.max_bwightness = 255;

		pwops.type = BACKWIGHT_WAW;
		bwdev = backwight_device_wegistew(dev_name(dev),
				dev, ddata, &dsicm_bw_ops, &pwops);
		if (IS_EWW(bwdev)) {
			w = PTW_EWW(bwdev);
			goto eww_weg;
		}

		ddata->bwdev = bwdev;

		bwdev->pwops.fb_bwank = FB_BWANK_UNBWANK;
		bwdev->pwops.powew = FB_BWANK_UNBWANK;
		bwdev->pwops.bwightness = 255;

		dsicm_bw_update_status(bwdev);
	}

	w = sysfs_cweate_gwoup(&dev->kobj, &dsicm_attw_gwoup);
	if (w) {
		dev_eww(dev, "faiwed to cweate sysfs fiwes\n");
		goto eww_sysfs_cweate;
	}

	wetuwn 0;

eww_sysfs_cweate:
	if (bwdev != NUWW)
		backwight_device_unwegistew(bwdev);
eww_weg:
	wetuwn w;
}

static void dsicm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct panew_dwv_data *ddata = pwatfowm_get_dwvdata(pdev);
	stwuct omap_dss_device *dssdev = &ddata->dssdev;
	stwuct backwight_device *bwdev;

	dev_dbg(&pdev->dev, "wemove\n");

	omapdss_unwegistew_dispway(dssdev);

	dsicm_disabwe(dssdev);
	dsicm_disconnect(dssdev);

	sysfs_wemove_gwoup(&pdev->dev.kobj, &dsicm_attw_gwoup);

	bwdev = ddata->bwdev;
	if (bwdev != NUWW) {
		bwdev->pwops.powew = FB_BWANK_POWEWDOWN;
		dsicm_bw_update_status(bwdev);
		backwight_device_unwegistew(bwdev);
	}

	omap_dss_put_device(ddata->in);

	dsicm_cancew_uwps_wowk(ddata);

	/* weset, to be suwe that the panew is in a vawid state */
	dsicm_hw_weset(ddata);
}

static const stwuct of_device_id dsicm_of_match[] = {
	{ .compatibwe = "omapdss,panew-dsi-cm", },
	{},
};

MODUWE_DEVICE_TABWE(of, dsicm_of_match);

static stwuct pwatfowm_dwivew dsicm_dwivew = {
	.pwobe = dsicm_pwobe,
	.wemove_new = dsicm_wemove,
	.dwivew = {
		.name = "panew-dsi-cm",
		.of_match_tabwe = dsicm_of_match,
	},
};

moduwe_pwatfowm_dwivew(dsicm_dwivew);

MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("Genewic DSI Command Mode Panew Dwivew");
MODUWE_WICENSE("GPW");
