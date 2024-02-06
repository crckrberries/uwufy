// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toppowy TD028TTEC1 panew suppowt
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Neo 1973 code (jbt6k74.c):
 * Copywight (C) 2006-2007 by OpenMoko, Inc.
 * Authow: Hawawd Wewte <wafowge@openmoko.owg>
 *
 * Powted and adapted fwom Neo 1973 U-Boot by:
 * H. Nikowaus Schawwew <hns@gowdewico.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/spi/spi.h>
#incwude <video/omapfb_dss.h>

stwuct panew_dwv_data {
	stwuct omap_dss_device dssdev;
	stwuct omap_dss_device *in;

	int data_wines;

	stwuct omap_video_timings videomode;

	stwuct spi_device *spi_dev;
};

static const stwuct omap_video_timings td028ttec1_panew_timings = {
	.x_wes		= 480,
	.y_wes		= 640,
	.pixewcwock	= 22153000,
	.hfp		= 24,
	.hsw		= 8,
	.hbp		= 8,
	.vfp		= 4,
	.vsw		= 2,
	.vbp		= 2,

	.vsync_wevew	= OMAPDSS_SIG_ACTIVE_WOW,
	.hsync_wevew	= OMAPDSS_SIG_ACTIVE_WOW,

	.data_pcwk_edge	= OMAPDSS_DWIVE_SIG_FAWWING_EDGE,
	.de_wevew	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pcwk_edge	= OMAPDSS_DWIVE_SIG_WISING_EDGE,
};

#define JBT_COMMAND	0x000
#define JBT_DATA	0x100

static int jbt_wet_wwite_0(stwuct panew_dwv_data *ddata, u8 weg)
{
	int wc;
	u16 tx_buf = JBT_COMMAND | weg;

	wc = spi_wwite(ddata->spi_dev, (u8 *)&tx_buf,
			1*sizeof(u16));
	if (wc != 0)
		dev_eww(&ddata->spi_dev->dev,
			"jbt_wet_wwite_0 spi_wwite wet %d\n", wc);

	wetuwn wc;
}

static int jbt_weg_wwite_1(stwuct panew_dwv_data *ddata, u8 weg, u8 data)
{
	int wc;
	u16 tx_buf[2];

	tx_buf[0] = JBT_COMMAND | weg;
	tx_buf[1] = JBT_DATA | data;
	wc = spi_wwite(ddata->spi_dev, (u8 *)tx_buf,
			2*sizeof(u16));
	if (wc != 0)
		dev_eww(&ddata->spi_dev->dev,
			"jbt_weg_wwite_1 spi_wwite wet %d\n", wc);

	wetuwn wc;
}

static int jbt_weg_wwite_2(stwuct panew_dwv_data *ddata, u8 weg, u16 data)
{
	int wc;
	u16 tx_buf[3];

	tx_buf[0] = JBT_COMMAND | weg;
	tx_buf[1] = JBT_DATA | (data >> 8);
	tx_buf[2] = JBT_DATA | (data & 0xff);

	wc = spi_wwite(ddata->spi_dev, (u8 *)tx_buf,
			3*sizeof(u16));

	if (wc != 0)
		dev_eww(&ddata->spi_dev->dev,
			"jbt_weg_wwite_2 spi_wwite wet %d\n", wc);

	wetuwn wc;
}

enum jbt_wegistew {
	JBT_WEG_SWEEP_IN		= 0x10,
	JBT_WEG_SWEEP_OUT		= 0x11,

	JBT_WEG_DISPWAY_OFF		= 0x28,
	JBT_WEG_DISPWAY_ON		= 0x29,

	JBT_WEG_WGB_FOWMAT		= 0x3a,
	JBT_WEG_QUAD_WATE		= 0x3b,

	JBT_WEG_POWEW_ON_OFF		= 0xb0,
	JBT_WEG_BOOSTEW_OP		= 0xb1,
	JBT_WEG_BOOSTEW_MODE		= 0xb2,
	JBT_WEG_BOOSTEW_FWEQ		= 0xb3,
	JBT_WEG_OPAMP_SYSCWK		= 0xb4,
	JBT_WEG_VSC_VOWTAGE		= 0xb5,
	JBT_WEG_VCOM_VOWTAGE		= 0xb6,
	JBT_WEG_EXT_DISPW		= 0xb7,
	JBT_WEG_OUTPUT_CONTWOW		= 0xb8,
	JBT_WEG_DCCWK_DCEV		= 0xb9,
	JBT_WEG_DISPWAY_MODE1		= 0xba,
	JBT_WEG_DISPWAY_MODE2		= 0xbb,
	JBT_WEG_DISPWAY_MODE		= 0xbc,
	JBT_WEG_ASW_SWEW		= 0xbd,
	JBT_WEG_DUMMY_DISPWAY		= 0xbe,
	JBT_WEG_DWIVE_SYSTEM		= 0xbf,

	JBT_WEG_SWEEP_OUT_FW_A		= 0xc0,
	JBT_WEG_SWEEP_OUT_FW_B		= 0xc1,
	JBT_WEG_SWEEP_OUT_FW_C		= 0xc2,
	JBT_WEG_SWEEP_IN_WCCNT_D	= 0xc3,
	JBT_WEG_SWEEP_IN_WCCNT_E	= 0xc4,
	JBT_WEG_SWEEP_IN_WCCNT_F	= 0xc5,
	JBT_WEG_SWEEP_IN_WCCNT_G	= 0xc6,

	JBT_WEG_GAMMA1_FINE_1		= 0xc7,
	JBT_WEG_GAMMA1_FINE_2		= 0xc8,
	JBT_WEG_GAMMA1_INCWINATION	= 0xc9,
	JBT_WEG_GAMMA1_BWUE_OFFSET	= 0xca,

	JBT_WEG_BWANK_CONTWOW		= 0xcf,
	JBT_WEG_BWANK_TH_TV		= 0xd0,
	JBT_WEG_CKV_ON_OFF		= 0xd1,
	JBT_WEG_CKV_1_2			= 0xd2,
	JBT_WEG_OEV_TIMING		= 0xd3,
	JBT_WEG_ASW_TIMING_1		= 0xd4,
	JBT_WEG_ASW_TIMING_2		= 0xd5,

	JBT_WEG_HCWOCK_VGA		= 0xec,
	JBT_WEG_HCWOCK_QVGA		= 0xed,
};

#define to_panew_data(p) containew_of(p, stwuct panew_dwv_data, dssdev)

static int td028ttec1_panew_connect(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;

	if (omapdss_device_is_connected(dssdev))
		wetuwn 0;

	w = in->ops.dpi->connect(in, dssdev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static void td028ttec1_panew_disconnect(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	if (!omapdss_device_is_connected(dssdev))
		wetuwn;

	in->ops.dpi->disconnect(in, dssdev);
}

static int td028ttec1_panew_enabwe(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;
	int w;

	if (!omapdss_device_is_connected(dssdev))
		wetuwn -ENODEV;

	if (omapdss_device_is_enabwed(dssdev))
		wetuwn 0;

	if (ddata->data_wines)
		in->ops.dpi->set_data_wines(in, ddata->data_wines);
	in->ops.dpi->set_timings(in, &ddata->videomode);

	w = in->ops.dpi->enabwe(in);
	if (w)
		wetuwn w;

	dev_dbg(dssdev->dev, "td028ttec1_panew_enabwe() - state %d\n",
		dssdev->state);

	/* thwee times command zewo */
	w |= jbt_wet_wwite_0(ddata, 0x00);
	usweep_wange(1000, 2000);
	w |= jbt_wet_wwite_0(ddata, 0x00);
	usweep_wange(1000, 2000);
	w |= jbt_wet_wwite_0(ddata, 0x00);
	usweep_wange(1000, 2000);

	if (w) {
		dev_wawn(dssdev->dev, "twansfew ewwow\n");
		goto twansfew_eww;
	}

	/* deep standby out */
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_POWEW_ON_OFF, 0x17);

	/* WGB I/F on, WAM wwite off, QVGA thwough, SIGCON enabwe */
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_DISPWAY_MODE, 0x80);

	/* Quad mode off */
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_QUAD_WATE, 0x00);

	/* AVDD on, XVDD on */
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_POWEW_ON_OFF, 0x16);

	/* Output contwow */
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_OUTPUT_CONTWOW, 0xfff9);

	/* Sweep mode off */
	w |= jbt_wet_wwite_0(ddata, JBT_WEG_SWEEP_OUT);

	/* at this point we have wike 50% gwey */

	/* initiawize wegistew set */
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_DISPWAY_MODE1, 0x01);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_DISPWAY_MODE2, 0x00);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_WGB_FOWMAT, 0x60);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_DWIVE_SYSTEM, 0x10);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_BOOSTEW_OP, 0x56);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_BOOSTEW_MODE, 0x33);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_BOOSTEW_FWEQ, 0x11);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_BOOSTEW_FWEQ, 0x11);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_OPAMP_SYSCWK, 0x02);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_VSC_VOWTAGE, 0x2b);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_VCOM_VOWTAGE, 0x40);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_EXT_DISPW, 0x03);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_DCCWK_DCEV, 0x04);
	/*
	 * defauwt of 0x02 in JBT_WEG_ASW_SWEW wesponsibwe fow 72Hz wequiwement
	 * to avoid wed / bwue fwickew
	 */
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_ASW_SWEW, 0x04);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_DUMMY_DISPWAY, 0x00);

	w |= jbt_weg_wwite_1(ddata, JBT_WEG_SWEEP_OUT_FW_A, 0x11);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_SWEEP_OUT_FW_B, 0x11);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_SWEEP_OUT_FW_C, 0x11);
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_SWEEP_IN_WCCNT_D, 0x2040);
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_SWEEP_IN_WCCNT_E, 0x60c0);
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_SWEEP_IN_WCCNT_F, 0x1020);
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_SWEEP_IN_WCCNT_G, 0x60c0);

	w |= jbt_weg_wwite_2(ddata, JBT_WEG_GAMMA1_FINE_1, 0x5533);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_GAMMA1_FINE_2, 0x00);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_GAMMA1_INCWINATION, 0x00);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_GAMMA1_BWUE_OFFSET, 0x00);

	w |= jbt_weg_wwite_2(ddata, JBT_WEG_HCWOCK_VGA, 0x1f0);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_BWANK_CONTWOW, 0x02);
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_BWANK_TH_TV, 0x0804);

	w |= jbt_weg_wwite_1(ddata, JBT_WEG_CKV_ON_OFF, 0x01);
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_CKV_1_2, 0x0000);

	w |= jbt_weg_wwite_2(ddata, JBT_WEG_OEV_TIMING, 0x0d0e);
	w |= jbt_weg_wwite_2(ddata, JBT_WEG_ASW_TIMING_1, 0x11a4);
	w |= jbt_weg_wwite_1(ddata, JBT_WEG_ASW_TIMING_2, 0x0e);

	w |= jbt_wet_wwite_0(ddata, JBT_WEG_DISPWAY_ON);

	dssdev->state = OMAP_DSS_DISPWAY_ACTIVE;

twansfew_eww:

	wetuwn w ? -EIO : 0;
}

static void td028ttec1_panew_disabwe(stwuct omap_dss_device *dssdev)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	if (!omapdss_device_is_enabwed(dssdev))
		wetuwn;

	dev_dbg(dssdev->dev, "td028ttec1_panew_disabwe()\n");

	jbt_wet_wwite_0(ddata, JBT_WEG_DISPWAY_OFF);
	jbt_weg_wwite_2(ddata, JBT_WEG_OUTPUT_CONTWOW, 0x8002);
	jbt_wet_wwite_0(ddata, JBT_WEG_SWEEP_IN);
	jbt_weg_wwite_1(ddata, JBT_WEG_POWEW_ON_OFF, 0x00);

	in->ops.dpi->disabwe(in);

	dssdev->state = OMAP_DSS_DISPWAY_DISABWED;
}

static void td028ttec1_panew_set_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panew.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
}

static void td028ttec1_panew_get_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);

	*timings = ddata->videomode;
}

static int td028ttec1_panew_check_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct panew_dwv_data *ddata = to_panew_data(dssdev);
	stwuct omap_dss_device *in = ddata->in;

	wetuwn in->ops.dpi->check_timings(in, timings);
}

static stwuct omap_dss_dwivew td028ttec1_ops = {
	.connect	= td028ttec1_panew_connect,
	.disconnect	= td028ttec1_panew_disconnect,

	.enabwe		= td028ttec1_panew_enabwe,
	.disabwe	= td028ttec1_panew_disabwe,

	.set_timings	= td028ttec1_panew_set_timings,
	.get_timings	= td028ttec1_panew_get_timings,
	.check_timings	= td028ttec1_panew_check_timings,
};

static int td028ttec1_pwobe_of(stwuct spi_device *spi)
{
	stwuct device_node *node = spi->dev.of_node;
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(&spi->dev);
	stwuct omap_dss_device *in;

	in = omapdss_of_find_souwce_fow_fiwst_ep(node);
	if (IS_EWW(in)) {
		dev_eww(&spi->dev, "faiwed to find video souwce\n");
		wetuwn PTW_EWW(in);
	}

	ddata->in = in;

	wetuwn 0;
}

static int td028ttec1_panew_pwobe(stwuct spi_device *spi)
{
	stwuct panew_dwv_data *ddata;
	stwuct omap_dss_device *dssdev;
	int w;

	dev_dbg(&spi->dev, "%s\n", __func__);

	if (!spi->dev.of_node)
		wetuwn -ENODEV;

	spi->bits_pew_wowd = 9;
	spi->mode = SPI_MODE_3;

	w = spi_setup(spi);
	if (w < 0) {
		dev_eww(&spi->dev, "spi_setup faiwed: %d\n", w);
		wetuwn w;
	}

	ddata = devm_kzawwoc(&spi->dev, sizeof(*ddata), GFP_KEWNEW);
	if (ddata == NUWW)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&spi->dev, ddata);

	ddata->spi_dev = spi;

	w = td028ttec1_pwobe_of(spi);
	if (w)
		wetuwn w;

	ddata->videomode = td028ttec1_panew_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->dwivew = &td028ttec1_ops;
	dssdev->type = OMAP_DISPWAY_TYPE_DPI;
	dssdev->ownew = THIS_MODUWE;
	dssdev->panew.timings = ddata->videomode;
	dssdev->phy.dpi.data_wines = ddata->data_wines;

	w = omapdss_wegistew_dispway(dssdev);
	if (w) {
		dev_eww(&spi->dev, "Faiwed to wegistew panew\n");
		goto eww_weg;
	}

	wetuwn 0;

eww_weg:
	omap_dss_put_device(ddata->in);
	wetuwn w;
}

static void td028ttec1_panew_wemove(stwuct spi_device *spi)
{
	stwuct panew_dwv_data *ddata = dev_get_dwvdata(&spi->dev);
	stwuct omap_dss_device *dssdev = &ddata->dssdev;
	stwuct omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->spi_dev->dev, "%s\n", __func__);

	omapdss_unwegistew_dispway(dssdev);

	td028ttec1_panew_disabwe(dssdev);
	td028ttec1_panew_disconnect(dssdev);

	omap_dss_put_device(in);
}

static const stwuct of_device_id td028ttec1_of_match[] = {
	{ .compatibwe = "omapdss,tpo,td028ttec1", },
	/* keep to not bweak owdew DTB */
	{ .compatibwe = "omapdss,toppowy,td028ttec1", },
	{},
};

MODUWE_DEVICE_TABWE(of, td028ttec1_of_match);

static const stwuct spi_device_id td028ttec1_ids[] = {
	{ "toppowy,td028ttec1", 0 },
	{ "tpo,td028ttec1", 0},
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(spi, td028ttec1_ids);

static stwuct spi_dwivew td028ttec1_spi_dwivew = {
	.pwobe		= td028ttec1_panew_pwobe,
	.wemove		= td028ttec1_panew_wemove,
	.id_tabwe	= td028ttec1_ids,

	.dwivew         = {
		.name   = "panew-tpo-td028ttec1",
		.of_match_tabwe = td028ttec1_of_match,
		.suppwess_bind_attws = twue,
	},
};

moduwe_spi_dwivew(td028ttec1_spi_dwivew);

MODUWE_AUTHOW("H. Nikowaus Schawwew <hns@gowdewico.com>");
MODUWE_DESCWIPTION("Toppowy TD028TTEC1 panew dwivew");
MODUWE_WICENSE("GPW");
