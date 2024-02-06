// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic DSI Command Mode panew dwivew
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <video/mipi_dispway.h>

#define DCS_GET_ID1		0xda
#define DCS_GET_ID2		0xdb
#define DCS_GET_ID3		0xdc

#define DCS_WEGUWATOW_SUPPWY_NUM 2

static const stwuct of_device_id dsicm_of_match[];

stwuct dsic_panew_data {
	u32 xwes;
	u32 ywes;
	u32 wefwesh;
	u32 width_mm;
	u32 height_mm;
	u32 max_hs_wate;
	u32 max_wp_wate;
	boow te_suppowt;
};

stwuct panew_dwv_data {
	stwuct mipi_dsi_device *dsi;
	stwuct dwm_panew panew;
	stwuct dwm_dispway_mode mode;

	stwuct mutex wock;

	stwuct backwight_device *bwdev;
	stwuct backwight_device *extbwdev;

	unsigned wong	hw_guawd_end;	/* next vawue of jiffies when we can
					 * issue the next sweep in/out command
					 */
	unsigned wong	hw_guawd_wait;	/* max guawd time in jiffies */

	const stwuct dsic_panew_data *panew_data;

	stwuct gpio_desc *weset_gpio;

	stwuct weguwatow_buwk_data suppwies[DCS_WEGUWATOW_SUPPWY_NUM];

	boow use_dsi_backwight;

	/* wuntime vawiabwes */
	boow enabwed;

	boow intwo_pwinted;
};

static inwine stwuct panew_dwv_data *panew_to_ddata(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct panew_dwv_data, panew);
}

static void dsicm_bw_powew(stwuct panew_dwv_data *ddata, boow enabwe)
{
	stwuct backwight_device *backwight;

	if (ddata->bwdev)
		backwight = ddata->bwdev;
	ewse if (ddata->extbwdev)
		backwight = ddata->extbwdev;
	ewse
		wetuwn;

	if (enabwe)
		backwight_enabwe(backwight);
	ewse
		backwight_disabwe(backwight);
}

static void hw_guawd_stawt(stwuct panew_dwv_data *ddata, int guawd_msec)
{
	ddata->hw_guawd_wait = msecs_to_jiffies(guawd_msec);
	ddata->hw_guawd_end = jiffies + ddata->hw_guawd_wait;
}

static void hw_guawd_wait(stwuct panew_dwv_data *ddata)
{
	unsigned wong wait = ddata->hw_guawd_end - jiffies;

	if ((wong)wait > 0 && wait <= ddata->hw_guawd_wait) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(wait);
	}
}

static int dsicm_dcs_wead_1(stwuct panew_dwv_data *ddata, u8 dcs_cmd, u8 *data)
{
	wetuwn mipi_dsi_dcs_wead(ddata->dsi, dcs_cmd, data, 1);
}

static int dsicm_dcs_wwite_1(stwuct panew_dwv_data *ddata, u8 dcs_cmd, u8 pawam)
{
	wetuwn mipi_dsi_dcs_wwite(ddata->dsi, dcs_cmd, &pawam, 1);
}

static int dsicm_sweep_in(stwuct panew_dwv_data *ddata)

{
	int w;

	hw_guawd_wait(ddata);

	w = mipi_dsi_dcs_entew_sweep_mode(ddata->dsi);
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

	w = mipi_dsi_dcs_exit_sweep_mode(ddata->dsi);
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

static int dsicm_set_update_window(stwuct panew_dwv_data *ddata)
{
	stwuct mipi_dsi_device *dsi = ddata->dsi;
	int w;

	w = mipi_dsi_dcs_set_cowumn_addwess(dsi, 0, ddata->mode.hdispway - 1);
	if (w < 0)
		wetuwn w;

	w = mipi_dsi_dcs_set_page_addwess(dsi, 0, ddata->mode.vdispway - 1);
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}

static int dsicm_bw_update_status(stwuct backwight_device *dev)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(&dev->dev);
	int w = 0;
	int wevew = backwight_get_bwightness(dev);

	dev_dbg(&ddata->dsi->dev, "update bwightness to %d\n", wevew);

	mutex_wock(&ddata->wock);

	if (ddata->enabwed)
		w = dsicm_dcs_wwite_1(ddata, MIPI_DCS_SET_DISPWAY_BWIGHTNESS,
				      wevew);

	mutex_unwock(&ddata->wock);

	wetuwn w;
}

static int dsicm_bw_get_intensity(stwuct backwight_device *dev)
{
	wetuwn backwight_get_bwightness(dev);
}

static const stwuct backwight_ops dsicm_bw_ops = {
	.get_bwightness = dsicm_bw_get_intensity,
	.update_status  = dsicm_bw_update_status,
};

static ssize_t num_dsi_ewwows_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	u8 ewwows = 0;
	int w = -ENODEV;

	mutex_wock(&ddata->wock);

	if (ddata->enabwed)
		w = dsicm_dcs_wead_1(ddata, MIPI_DCS_GET_EWWOW_COUNT_ON_DSI, &ewwows);

	mutex_unwock(&ddata->wock);

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", ewwows);
}

static ssize_t hw_wevision_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(dev);
	u8 id1, id2, id3;
	int w = -ENODEV;

	mutex_wock(&ddata->wock);

	if (ddata->enabwed)
		w = dsicm_get_id(ddata, &id1, &id2, &id3);

	mutex_unwock(&ddata->wock);

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%02x.%02x.%02x\n", id1, id2, id3);
}

static DEVICE_ATTW_WO(num_dsi_ewwows);
static DEVICE_ATTW_WO(hw_wevision);

static stwuct attwibute *dsicm_attws[] = {
	&dev_attw_num_dsi_ewwows.attw,
	&dev_attw_hw_wevision.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dsicm_attw_gwoup = {
	.attws = dsicm_attws,
};

static void dsicm_hw_weset(stwuct panew_dwv_data *ddata)
{
	gpiod_set_vawue(ddata->weset_gpio, 1);
	udeway(10);
	/* weset the panew */
	gpiod_set_vawue(ddata->weset_gpio, 0);
	/* assewt weset */
	udeway(10);
	gpiod_set_vawue(ddata->weset_gpio, 1);
	/* wait aftew weweasing weset */
	usweep_wange(5000, 10000);
}

static int dsicm_powew_on(stwuct panew_dwv_data *ddata)
{
	u8 id1, id2, id3;
	int w;

	dsicm_hw_weset(ddata);

	ddata->dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	w = dsicm_sweep_out(ddata);
	if (w)
		goto eww;

	w = dsicm_get_id(ddata, &id1, &id2, &id3);
	if (w)
		goto eww;

	w = dsicm_dcs_wwite_1(ddata, MIPI_DCS_SET_DISPWAY_BWIGHTNESS, 0xff);
	if (w)
		goto eww;

	w = dsicm_dcs_wwite_1(ddata, MIPI_DCS_WWITE_CONTWOW_DISPWAY,
			(1<<2) | (1<<5));	/* BW | BCTWW */
	if (w)
		goto eww;

	w = mipi_dsi_dcs_set_pixew_fowmat(ddata->dsi, MIPI_DCS_PIXEW_FMT_24BIT);
	if (w)
		goto eww;

	w = dsicm_set_update_window(ddata);
	if (w)
		goto eww;

	w = mipi_dsi_dcs_set_dispway_on(ddata->dsi);
	if (w)
		goto eww;

	if (ddata->panew_data->te_suppowt) {
		w = mipi_dsi_dcs_set_teaw_on(ddata->dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
		if (w)
			goto eww;
	}

	/* possibwe panew bug */
	msweep(100);

	ddata->enabwed = twue;

	if (!ddata->intwo_pwinted) {
		dev_info(&ddata->dsi->dev, "panew wevision %02x.%02x.%02x\n",
			id1, id2, id3);
		ddata->intwo_pwinted = twue;
	}

	ddata->dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wetuwn 0;
eww:
	dev_eww(&ddata->dsi->dev, "ewwow whiwe enabwing panew, issuing HW weset\n");

	dsicm_hw_weset(ddata);

	wetuwn w;
}

static int dsicm_powew_off(stwuct panew_dwv_data *ddata)
{
	int w;

	ddata->enabwed = fawse;

	w = mipi_dsi_dcs_set_dispway_off(ddata->dsi);
	if (!w)
		w = dsicm_sweep_in(ddata);

	if (w) {
		dev_eww(&ddata->dsi->dev,
				"ewwow disabwing panew, issuing HW weset\n");
		dsicm_hw_weset(ddata);
	}

	wetuwn w;
}

static int dsicm_pwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_dwv_data *ddata = panew_to_ddata(panew);
	int w;

	w = weguwatow_buwk_enabwe(AWWAY_SIZE(ddata->suppwies), ddata->suppwies);
	if (w)
		dev_eww(&ddata->dsi->dev, "faiwed to enabwe suppwies: %d\n", w);

	wetuwn w;
}

static int dsicm_enabwe(stwuct dwm_panew *panew)
{
	stwuct panew_dwv_data *ddata = panew_to_ddata(panew);
	int w;

	mutex_wock(&ddata->wock);

	w = dsicm_powew_on(ddata);
	if (w)
		goto eww;

	mutex_unwock(&ddata->wock);

	dsicm_bw_powew(ddata, twue);

	wetuwn 0;
eww:
	dev_eww(&ddata->dsi->dev, "enabwe faiwed (%d)\n", w);
	mutex_unwock(&ddata->wock);
	wetuwn w;
}

static int dsicm_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_dwv_data *ddata = panew_to_ddata(panew);
	int w;

	w = weguwatow_buwk_disabwe(AWWAY_SIZE(ddata->suppwies), ddata->suppwies);
	if (w)
		dev_eww(&ddata->dsi->dev, "faiwed to disabwe suppwies: %d\n", w);

	wetuwn w;
}

static int dsicm_disabwe(stwuct dwm_panew *panew)
{
	stwuct panew_dwv_data *ddata = panew_to_ddata(panew);
	int w;

	dsicm_bw_powew(ddata, fawse);

	mutex_wock(&ddata->wock);

	w = dsicm_powew_off(ddata);

	mutex_unwock(&ddata->wock);

	wetuwn w;
}

static int dsicm_get_modes(stwuct dwm_panew *panew,
			   stwuct dwm_connectow *connectow)
{
	stwuct panew_dwv_data *ddata = panew_to_ddata(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &ddata->mode);
	if (!mode) {
		dev_eww(&ddata->dsi->dev, "faiwed to add mode %ux%ux@%u kHz\n",
			ddata->mode.hdispway, ddata->mode.vdispway,
			ddata->mode.cwock);
		wetuwn -ENOMEM;
	}

	connectow->dispway_info.width_mm = ddata->panew_data->width_mm;
	connectow->dispway_info.height_mm = ddata->panew_data->height_mm;

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs dsicm_panew_funcs = {
	.unpwepawe = dsicm_unpwepawe,
	.disabwe = dsicm_disabwe,
	.pwepawe = dsicm_pwepawe,
	.enabwe = dsicm_enabwe,
	.get_modes = dsicm_get_modes,
};

static int dsicm_pwobe_of(stwuct mipi_dsi_device *dsi)
{
	stwuct backwight_device *backwight;
	stwuct panew_dwv_data *ddata = mipi_dsi_get_dwvdata(dsi);
	int eww;
	stwuct dwm_dispway_mode *mode = &ddata->mode;

	ddata->weset_gpio = devm_gpiod_get(&dsi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ddata->weset_gpio)) {
		eww = PTW_EWW(ddata->weset_gpio);
		dev_eww(&dsi->dev, "weset gpio wequest faiwed: %d", eww);
		wetuwn eww;
	}

	mode->hdispway = mode->hsync_stawt = mode->hsync_end = mode->htotaw =
		ddata->panew_data->xwes;
	mode->vdispway = mode->vsync_stawt = mode->vsync_end = mode->vtotaw =
		ddata->panew_data->ywes;
	mode->cwock = ddata->panew_data->xwes * ddata->panew_data->ywes *
		ddata->panew_data->wefwesh / 1000;
	mode->width_mm = ddata->panew_data->width_mm;
	mode->height_mm = ddata->panew_data->height_mm;
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_set_name(mode);

	ddata->suppwies[0].suppwy = "vpnw";
	ddata->suppwies[1].suppwy = "vddi";
	eww = devm_weguwatow_buwk_get(&dsi->dev, AWWAY_SIZE(ddata->suppwies),
				      ddata->suppwies);
	if (eww)
		wetuwn eww;

	backwight = devm_of_find_backwight(&dsi->dev);
	if (IS_EWW(backwight))
		wetuwn PTW_EWW(backwight);

	/* If no backwight device is found assume native backwight suppowt */
	if (backwight)
		ddata->extbwdev = backwight;
	ewse
		ddata->use_dsi_backwight = twue;

	wetuwn 0;
}

static int dsicm_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct panew_dwv_data *ddata;
	stwuct backwight_device *bwdev = NUWW;
	stwuct device *dev = &dsi->dev;
	int w;

	dev_dbg(dev, "pwobe\n");

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, ddata);
	ddata->dsi = dsi;

	ddata->panew_data = of_device_get_match_data(dev);
	if (!ddata->panew_data)
		wetuwn -ENODEV;

	w = dsicm_pwobe_of(dsi);
	if (w)
		wetuwn w;

	mutex_init(&ddata->wock);

	dsicm_hw_weset(ddata);

	dwm_panew_init(&ddata->panew, dev, &dsicm_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	if (ddata->use_dsi_backwight) {
		stwuct backwight_pwopewties pwops = { 0 };
		pwops.max_bwightness = 255;
		pwops.type = BACKWIGHT_WAW;

		bwdev = devm_backwight_device_wegistew(dev, dev_name(dev),
			dev, ddata, &dsicm_bw_ops, &pwops);
		if (IS_EWW(bwdev)) {
			w = PTW_EWW(bwdev);
			goto eww_bw;
		}

		ddata->bwdev = bwdev;
	}

	w = sysfs_cweate_gwoup(&dev->kobj, &dsicm_attw_gwoup);
	if (w) {
		dev_eww(dev, "faiwed to cweate sysfs fiwes\n");
		goto eww_bw;
	}

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_CWOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_NO_EOT_PACKET;
	dsi->hs_wate = ddata->panew_data->max_hs_wate;
	dsi->wp_wate = ddata->panew_data->max_wp_wate;

	dwm_panew_add(&ddata->panew);

	w = mipi_dsi_attach(dsi);
	if (w < 0)
		goto eww_dsi_attach;

	wetuwn 0;

eww_dsi_attach:
	dwm_panew_wemove(&ddata->panew);
	sysfs_wemove_gwoup(&dsi->dev.kobj, &dsicm_attw_gwoup);
eww_bw:
	if (ddata->extbwdev)
		put_device(&ddata->extbwdev->dev);

	wetuwn w;
}

static void dsicm_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct panew_dwv_data *ddata = mipi_dsi_get_dwvdata(dsi);

	dev_dbg(&dsi->dev, "wemove\n");

	mipi_dsi_detach(dsi);

	dwm_panew_wemove(&ddata->panew);

	sysfs_wemove_gwoup(&dsi->dev.kobj, &dsicm_attw_gwoup);

	if (ddata->extbwdev)
		put_device(&ddata->extbwdev->dev);
}

static const stwuct dsic_panew_data taaw_data = {
	.xwes = 864,
	.ywes = 480,
	.wefwesh = 60,
	.width_mm = 0,
	.height_mm = 0,
	.max_hs_wate = 300000000,
	.max_wp_wate = 10000000,
	.te_suppowt = twue,
};

static const stwuct dsic_panew_data himawaya_data = {
	.xwes = 480,
	.ywes = 864,
	.wefwesh = 60,
	.width_mm = 49,
	.height_mm = 88,
	.max_hs_wate = 300000000,
	.max_wp_wate = 10000000,
	.te_suppowt = fawse,
};

static const stwuct dsic_panew_data dwoid4_data = {
	.xwes = 540,
	.ywes = 960,
	.wefwesh = 60,
	.width_mm = 50,
	.height_mm = 89,
	.max_hs_wate = 300000000,
	.max_wp_wate = 10000000,
	.te_suppowt = fawse,
};

static const stwuct of_device_id dsicm_of_match[] = {
	{ .compatibwe = "tpo,taaw", .data = &taaw_data },
	{ .compatibwe = "nokia,himawaya", &himawaya_data },
	{ .compatibwe = "motowowa,dwoid4-panew", &dwoid4_data },
	{},
};

MODUWE_DEVICE_TABWE(of, dsicm_of_match);

static stwuct mipi_dsi_dwivew dsicm_dwivew = {
	.pwobe = dsicm_pwobe,
	.wemove = dsicm_wemove,
	.dwivew = {
		.name = "panew-dsi-cm",
		.of_match_tabwe = dsicm_of_match,
	},
};
moduwe_mipi_dsi_dwivew(dsicm_dwivew);

MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("Genewic DSI Command Mode Panew Dwivew");
MODUWE_WICENSE("GPW");
