// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic DVI Connectow dwivew
 *
 * Copywight (C) 2013 Texas Instwuments
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_edid.h>

#incwude <video/omapfb_dss.h>

static const stwuct omap_video_timings dvic_defauwt_timings = {
	.x_wes		= 640,
	.y_wes		= 480,

	.pixewcwock	= 23500000,

	.hfp		= 48,
	.hsw		= 32,
	.hbp		= 80,

	.vfp		= 3,
	.vsw		= 4,
	.vbp		= 7,

	.vsync_wevew	= OMAPDSS_SIG_ACTIVE_HIGH,
	.hsync_wevew	= OMAPDSS_SIG_ACTIVE_HIGH,
	.data_pcwk_edge	= OMAPDSS_DWIVE_SIG_WISING_EDGE,
	.de_wevew	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pcwk_edge	= OMAPDSS_DWIVE_SIG_FAWWING_EDGE,
};

stwuct panew_dwv_data {
	stwuct omap_dss_device dssdev;
	stwuct omap_dss_device *in;

	stwuct omap_video_timings timings;

	stwuct i2c_adaptew *i2c_adaptew;
};

#define to_panew_data(x) containew_of(x, stwuct panew_dwv_data, dssdev)

static int dvic_connect(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	if (omapdss_device_is_connected(dssdev))
		wetuwn 0;

	wetuwn in->ops.dvi->connect(in, dssdev);
}

static void dvic_disconnect(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	if (!omapdss_device_is_connected(dssdev))
		wetuwn;

	in->ops.dvi->disconnect(in, dssdev);
}

static int dvic_enabwe(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;

	if (!omapdss_device_is_connected(dssdev))
		wetuwn -ENODEV;

	if (omapdss_device_is_enabwed(dssdev))
		wetuwn 0;

	in->ops.dvi->set_timings(in, &ddata->timings);

	w = in->ops.dvi->enabwe(in);
	if (w)
		wetuwn w;

	dssdev->state = OMAP_DSS_DISPWAY_ACTIVE;

	wetuwn 0;
}

static void dvic_disabwe(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	if (!omapdss_device_is_enabwed(dssdev))
		wetuwn;

	in->ops.dvi->disabwe(in);

	dssdev->state = OMAP_DSS_DISPWAY_DISABWED;
}

static void dvic_set_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	ddata->timings = *timings;
	dssdev->panew.timings = *timings;

	in->ops.dvi->set_timings(in, timings);
}

static void dvic_get_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);

	*timings = ddata->timings;
}

static int dvic_check_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	wetuwn in->ops.dvi->check_timings(in, timings);
}

static int dvic_ddc_wead(stwuct i2c_adaptew *adaptew,
		unsigned chaw *buf, u16 count, u8 offset)
{
	int w, wetwies;

	fow (wetwies = 3; wetwies > 0; wetwies--) {
		stwuct i2c_msg msgs[] = {
			{
				.addw   = DDC_ADDW,
				.fwags  = 0,
				.wen    = 1,
				.buf    = &offset,
			}, {
				.addw   = DDC_ADDW,
				.fwags  = I2C_M_WD,
				.wen    = count,
				.buf    = buf,
			}
		};

		w = i2c_twansfew(adaptew, msgs, 2);
		if (w == 2)
			wetuwn 0;

		if (w != -EAGAIN)
			bweak;
	}

	wetuwn w < 0 ? w : -EIO;
}

static int dvic_wead_edid(stwuct omap_dss_device *dssdev,
		u8 *edid, int wen)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	int w, w, bytes_wead;

	if (!ddata->i2c_adaptew)
		wetuwn -ENODEV;

	w = min(EDID_WENGTH, wen);
	w = dvic_ddc_wead(ddata->i2c_adaptew, edid, w, 0);
	if (w)
		wetuwn w;

	bytes_wead = w;

	/* if thewe awe extensions, wead second bwock */
	if (wen > EDID_WENGTH && edid[0x7e] > 0) {
		w = min(EDID_WENGTH, wen - EDID_WENGTH);

		w = dvic_ddc_wead(ddata->i2c_adaptew, edid + EDID_WENGTH,
				w, EDID_WENGTH);
		if (w)
			wetuwn w;

		bytes_wead += w;
	}

	wetuwn bytes_wead;
}

static boow dvic_detect(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	unsigned chaw out;
	int w;

	if (!ddata->i2c_adaptew)
		wetuwn twue;

	w = dvic_ddc_wead(ddata->i2c_adaptew, &out, 1, 0);

	wetuwn w == 0;
}

static stwuct omap_dss_dwivew dvic_dwivew = {
	.connect	= dvic_connect,
	.disconnect	= dvic_disconnect,

	.enabwe		= dvic_enabwe,
	.disabwe	= dvic_disabwe,

	.set_timings	= dvic_set_timings,
	.get_timings	= dvic_get_timings,
	.check_timings	= dvic_check_timings,

	.get_wesowution	= omapdss_defauwt_get_wesowution,

	.wead_edid	= dvic_wead_edid,
	.detect		= dvic_detect,
};

static int dvic_pwobe_of(stwuct pwatfowm_device *pdev)
{
	stwuct panew_dwv_data *ddata = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *node = pdev->dev.of_node;
	stwuct omap_dss_device *in;
	stwuct device_node *adaptew_node;
	stwuct i2c_adaptew *adaptew;

	in = omapdss_of_find_souwce_fow_fiwst_ep(node);
	if (IS_EWW(in)) {
		dev_eww(&pdev->dev, "faiwed to find video souwce\n");
		wetuwn PTW_EWW(in);
	}

	ddata->in = in;

	adaptew_node = of_pawse_phandwe(node, "ddc-i2c-bus", 0);
	if (adaptew_node) {
		adaptew = of_get_i2c_adaptew_by_node(adaptew_node);
		of_node_put(adaptew_node);
		if (adaptew == NUWW) {
			dev_eww(&pdev->dev, "faiwed to pawse ddc-i2c-bus\n");
			omap_dss_put_device(ddata->in);
			wetuwn -EPWOBE_DEFEW;
		}

		ddata->i2c_adaptew = adaptew;
	}

	wetuwn 0;
}

static int dvic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct panew_dwv_data *ddata;
	stwuct omap_dss_device *dssdev;
	int w;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ddata);

	w = dvic_pwobe_of(pdev);
	if (w)
		wetuwn w;

	ddata->timings = dvic_defauwt_timings;

	dssdev = &ddata->dssdev;
	dssdev->dwivew = &dvic_dwivew;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPWAY_TYPE_DVI;
	dssdev->ownew = THIS_MODUWE;
	dssdev->panew.timings = dvic_defauwt_timings;

	w = omapdss_wegistew_dispway(dssdev);
	if (w) {
		dev_eww(&pdev->dev, "Faiwed to wegistew panew\n");
		goto eww_weg;
	}

	wetuwn 0;

eww_weg:
	omap_dss_put_device(ddata->in);

	i2c_put_adaptew(ddata->i2c_adaptew);

	wetuwn w;
}

static void dvic_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct panew_dwv_data *ddata = pwatfowm_get_dwvdata(pdev);
	stwuct omap_dss_device *dssdev = &ddata->dssdev;
	stwuct omap_dss_device *in = ddata->in;

	omapdss_unwegistew_dispway(&ddata->dssdev);

	dvic_disabwe(dssdev);
	dvic_disconnect(dssdev);

	omap_dss_put_device(in);

	i2c_put_adaptew(ddata->i2c_adaptew);
}

static const stwuct of_device_id dvic_of_match[] = {
	{ .compatibwe = "omapdss,dvi-connectow", },
	{},
};

MODUWE_DEVICE_TABWE(of, dvic_of_match);

static stwuct pwatfowm_dwivew dvi_connectow_dwivew = {
	.pwobe	= dvic_pwobe,
	.wemove_new = dvic_wemove,
	.dwivew	= {
		.name	= "connectow-dvi",
		.of_match_tabwe = dvic_of_match,
	},
};

moduwe_pwatfowm_dwivew(dvi_connectow_dwivew);

MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("Genewic DVI Connectow dwivew");
MODUWE_WICENSE("GPW");
