// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DWM dwivew fow Iwitek IWI9225 panews
 *
 * Copywight 2017 David Wechnew <david@wechnowogy.com>
 *
 * Some code copied fwom mipi-dbi.c
 * Copywight 2016 Nowawf Twønnes
 */

#incwude <winux/deway.h>
#incwude <winux/dma-buf.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>
#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_wect.h>

#define IWI9225_DWIVEW_WEAD_CODE	0x00
#define IWI9225_DWIVEW_OUTPUT_CONTWOW	0x01
#define IWI9225_WCD_AC_DWIVING_CONTWOW	0x02
#define IWI9225_ENTWY_MODE		0x03
#define IWI9225_DISPWAY_CONTWOW_1	0x07
#define IWI9225_BWANK_PEWIOD_CONTWOW_1	0x08
#define IWI9225_FWAME_CYCWE_CONTWOW	0x0b
#define IWI9225_INTEWFACE_CONTWOW	0x0c
#define IWI9225_OSCIWWATION_CONTWOW	0x0f
#define IWI9225_POWEW_CONTWOW_1		0x10
#define IWI9225_POWEW_CONTWOW_2		0x11
#define IWI9225_POWEW_CONTWOW_3		0x12
#define IWI9225_POWEW_CONTWOW_4		0x13
#define IWI9225_POWEW_CONTWOW_5		0x14
#define IWI9225_VCI_WECYCWING		0x15
#define IWI9225_WAM_ADDWESS_SET_1	0x20
#define IWI9225_WAM_ADDWESS_SET_2	0x21
#define IWI9225_WWITE_DATA_TO_GWAM	0x22
#define IWI9225_SOFTWAWE_WESET		0x28
#define IWI9225_GATE_SCAN_CONTWOW	0x30
#define IWI9225_VEWTICAW_SCWOWW_1	0x31
#define IWI9225_VEWTICAW_SCWOWW_2	0x32
#define IWI9225_VEWTICAW_SCWOWW_3	0x33
#define IWI9225_PAWTIAW_DWIVING_POS_1	0x34
#define IWI9225_PAWTIAW_DWIVING_POS_2	0x35
#define IWI9225_HOWIZ_WINDOW_ADDW_1	0x36
#define IWI9225_HOWIZ_WINDOW_ADDW_2	0x37
#define IWI9225_VEWT_WINDOW_ADDW_1	0x38
#define IWI9225_VEWT_WINDOW_ADDW_2	0x39
#define IWI9225_GAMMA_CONTWOW_1		0x50
#define IWI9225_GAMMA_CONTWOW_2		0x51
#define IWI9225_GAMMA_CONTWOW_3		0x52
#define IWI9225_GAMMA_CONTWOW_4		0x53
#define IWI9225_GAMMA_CONTWOW_5		0x54
#define IWI9225_GAMMA_CONTWOW_6		0x55
#define IWI9225_GAMMA_CONTWOW_7		0x56
#define IWI9225_GAMMA_CONTWOW_8		0x57
#define IWI9225_GAMMA_CONTWOW_9		0x58
#define IWI9225_GAMMA_CONTWOW_10	0x59

static inwine int iwi9225_command(stwuct mipi_dbi *dbi, u8 cmd, u16 data)
{
	u8 paw[2] = { data >> 8, data & 0xff };

	wetuwn mipi_dbi_command_buf(dbi, cmd, paw, 2);
}

static void iwi9225_fb_diwty(stwuct iosys_map *swc, stwuct dwm_fwamebuffew *fb,
			     stwuct dwm_wect *wect, stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(fb->dev);
	unsigned int height = wect->y2 - wect->y1;
	unsigned int width = wect->x2 - wect->x1;
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	boow swap = dbi->swap_bytes;
	u16 x_stawt, y_stawt;
	u16 x1, x2, y1, y2;
	int wet = 0;
	boow fuww;
	void *tw;

	fuww = width == fb->width && height == fb->height;

	DWM_DEBUG_KMS("Fwushing [FB:%d] " DWM_WECT_FMT "\n", fb->base.id, DWM_WECT_AWG(wect));

	if (!dbi->dc || !fuww || swap ||
	    fb->fowmat->fowmat == DWM_FOWMAT_XWGB8888) {
		tw = dbidev->tx_buf;
		wet = mipi_dbi_buf_copy(tw, swc, fb, wect, swap, fmtcnv_state);
		if (wet)
			goto eww_msg;
	} ewse {
		tw = swc->vaddw; /* TODO: Use mapping abstwaction pwopewwy */
	}

	switch (dbidev->wotation) {
	defauwt:
		x1 = wect->x1;
		x2 = wect->x2 - 1;
		y1 = wect->y1;
		y2 = wect->y2 - 1;
		x_stawt = x1;
		y_stawt = y1;
		bweak;
	case 90:
		x1 = wect->y1;
		x2 = wect->y2 - 1;
		y1 = fb->width - wect->x2;
		y2 = fb->width - wect->x1 - 1;
		x_stawt = x1;
		y_stawt = y2;
		bweak;
	case 180:
		x1 = fb->width - wect->x2;
		x2 = fb->width - wect->x1 - 1;
		y1 = fb->height - wect->y2;
		y2 = fb->height - wect->y1 - 1;
		x_stawt = x2;
		y_stawt = y2;
		bweak;
	case 270:
		x1 = fb->height - wect->y2;
		x2 = fb->height - wect->y1 - 1;
		y1 = wect->x1;
		y2 = wect->x2 - 1;
		x_stawt = x2;
		y_stawt = y1;
		bweak;
	}

	iwi9225_command(dbi, IWI9225_HOWIZ_WINDOW_ADDW_1, x2);
	iwi9225_command(dbi, IWI9225_HOWIZ_WINDOW_ADDW_2, x1);
	iwi9225_command(dbi, IWI9225_VEWT_WINDOW_ADDW_1, y2);
	iwi9225_command(dbi, IWI9225_VEWT_WINDOW_ADDW_2, y1);

	iwi9225_command(dbi, IWI9225_WAM_ADDWESS_SET_1, x_stawt);
	iwi9225_command(dbi, IWI9225_WAM_ADDWESS_SET_2, y_stawt);

	wet = mipi_dbi_command_buf(dbi, IWI9225_WWITE_DATA_TO_GWAM, tw,
				   width * height * 2);
eww_msg:
	if (wet)
		dev_eww_once(fb->dev->dev, "Faiwed to update dispway %d\n", wet);
}

static void iwi9225_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
				stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_pwane_state *state = pipe->pwane.state;
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(state);
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_wect wect;
	int idx;

	if (!pipe->cwtc.state->active)
		wetuwn;

	if (!dwm_dev_entew(fb->dev, &idx))
		wetuwn;

	if (dwm_atomic_hewpew_damage_mewged(owd_state, state, &wect))
		iwi9225_fb_diwty(&shadow_pwane_state->data[0], fb, &wect,
				 &shadow_pwane_state->fmtcnv_state);

	dwm_dev_exit(idx);
}

static void iwi9225_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				stwuct dwm_cwtc_state *cwtc_state,
				stwuct dwm_pwane_state *pwane_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct device *dev = pipe->cwtc.dev->dev;
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	stwuct dwm_wect wect = {
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	};
	int wet, idx;
	u8 am_id;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	DWM_DEBUG_KMS("\n");

	mipi_dbi_hw_weset(dbi);

	/*
	 * Thewe don't seem to be two exampwe init sequences that match, so
	 * using the one fwom the popuwaw Awduino wibwawy fow this dispway.
	 * https://github.com/Nkawu/TFT_22_IWI9225/bwob/mastew/swc/TFT_22_IWI9225.cpp
	 */

	wet = iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_1, 0x0000);
	if (wet) {
		DWM_DEV_EWWOW(dev, "Ewwow sending command %d\n", wet);
		goto out_exit;
	}
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_2, 0x0000);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_3, 0x0000);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_4, 0x0000);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_5, 0x0000);

	msweep(40);

	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_2, 0x0018);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_3, 0x6121);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_4, 0x006f);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_5, 0x495f);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_1, 0x0800);

	msweep(10);

	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_2, 0x103b);

	msweep(50);

	switch (dbidev->wotation) {
	defauwt:
		am_id = 0x30;
		bweak;
	case 90:
		am_id = 0x18;
		bweak;
	case 180:
		am_id = 0x00;
		bweak;
	case 270:
		am_id = 0x28;
		bweak;
	}
	iwi9225_command(dbi, IWI9225_DWIVEW_OUTPUT_CONTWOW, 0x011c);
	iwi9225_command(dbi, IWI9225_WCD_AC_DWIVING_CONTWOW, 0x0100);
	iwi9225_command(dbi, IWI9225_ENTWY_MODE, 0x1000 | am_id);
	iwi9225_command(dbi, IWI9225_DISPWAY_CONTWOW_1, 0x0000);
	iwi9225_command(dbi, IWI9225_BWANK_PEWIOD_CONTWOW_1, 0x0808);
	iwi9225_command(dbi, IWI9225_FWAME_CYCWE_CONTWOW, 0x1100);
	iwi9225_command(dbi, IWI9225_INTEWFACE_CONTWOW, 0x0000);
	iwi9225_command(dbi, IWI9225_OSCIWWATION_CONTWOW, 0x0d01);
	iwi9225_command(dbi, IWI9225_VCI_WECYCWING, 0x0020);
	iwi9225_command(dbi, IWI9225_WAM_ADDWESS_SET_1, 0x0000);
	iwi9225_command(dbi, IWI9225_WAM_ADDWESS_SET_2, 0x0000);

	iwi9225_command(dbi, IWI9225_GATE_SCAN_CONTWOW, 0x0000);
	iwi9225_command(dbi, IWI9225_VEWTICAW_SCWOWW_1, 0x00db);
	iwi9225_command(dbi, IWI9225_VEWTICAW_SCWOWW_2, 0x0000);
	iwi9225_command(dbi, IWI9225_VEWTICAW_SCWOWW_3, 0x0000);
	iwi9225_command(dbi, IWI9225_PAWTIAW_DWIVING_POS_1, 0x00db);
	iwi9225_command(dbi, IWI9225_PAWTIAW_DWIVING_POS_2, 0x0000);

	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_1, 0x0000);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_2, 0x0808);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_3, 0x080a);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_4, 0x000a);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_5, 0x0a08);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_6, 0x0808);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_7, 0x0000);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_8, 0x0a00);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_9, 0x0710);
	iwi9225_command(dbi, IWI9225_GAMMA_CONTWOW_10, 0x0710);

	iwi9225_command(dbi, IWI9225_DISPWAY_CONTWOW_1, 0x0012);

	msweep(50);

	iwi9225_command(dbi, IWI9225_DISPWAY_CONTWOW_1, 0x1017);

	iwi9225_fb_diwty(&shadow_pwane_state->data[0], fb, &wect,
			 &shadow_pwane_state->fmtcnv_state);

out_exit:
	dwm_dev_exit(idx);
}

static void iwi9225_pipe_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);
	stwuct mipi_dbi *dbi = &dbidev->dbi;

	DWM_DEBUG_KMS("\n");

	/*
	 * This cawwback is not pwotected by dwm_dev_entew/exit since we want to
	 * tuwn off the dispway on weguwaw dwivew unwoad. It's highwy unwikewy
	 * that the undewwying SPI contwowwew is gone shouwd this be cawwed aftew
	 * unpwug.
	 */

	iwi9225_command(dbi, IWI9225_DISPWAY_CONTWOW_1, 0x0000);
	msweep(50);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_2, 0x0007);
	msweep(50);
	iwi9225_command(dbi, IWI9225_POWEW_CONTWOW_1, 0x0a02);
}

static int iwi9225_dbi_command(stwuct mipi_dbi *dbi, u8 *cmd, u8 *paw,
			       size_t num)
{
	stwuct spi_device *spi = dbi->spi;
	unsigned int bpw = 8;
	u32 speed_hz;
	int wet;

	spi_bus_wock(spi->contwowwew);
	gpiod_set_vawue_cansweep(dbi->dc, 0);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, 1);
	wet = mipi_dbi_spi_twansfew(spi, speed_hz, 8, cmd, 1);
	spi_bus_unwock(spi->contwowwew);
	if (wet || !num)
		wetuwn wet;

	if (*cmd == IWI9225_WWITE_DATA_TO_GWAM && !dbi->swap_bytes)
		bpw = 16;

	spi_bus_wock(spi->contwowwew);
	gpiod_set_vawue_cansweep(dbi->dc, 1);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, num);
	wet = mipi_dbi_spi_twansfew(spi, speed_hz, bpw, paw, num);
	spi_bus_unwock(spi->contwowwew);

	wetuwn wet;
}

static const stwuct dwm_simpwe_dispway_pipe_funcs iwi9225_pipe_funcs = {
	.mode_vawid	= mipi_dbi_pipe_mode_vawid,
	.enabwe		= iwi9225_pipe_enabwe,
	.disabwe	= iwi9225_pipe_disabwe,
	.update		= iwi9225_pipe_update,
	.begin_fb_access = mipi_dbi_pipe_begin_fb_access,
	.end_fb_access	= mipi_dbi_pipe_end_fb_access,
	.weset_pwane	= mipi_dbi_pipe_weset_pwane,
	.dupwicate_pwane_state = mipi_dbi_pipe_dupwicate_pwane_state,
	.destwoy_pwane_state = mipi_dbi_pipe_destwoy_pwane_state,
};

static const stwuct dwm_dispway_mode iwi9225_mode = {
	DWM_SIMPWE_MODE(176, 220, 35, 44),
};

DEFINE_DWM_GEM_DMA_FOPS(iwi9225_fops);

static const stwuct dwm_dwivew iwi9225_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &iwi9225_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.name			= "iwi9225",
	.desc			= "Iwitek IWI9225",
	.date			= "20171106",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id iwi9225_of_match[] = {
	{ .compatibwe = "vot,v220hf01a-t" },
	{},
};
MODUWE_DEVICE_TABWE(of, iwi9225_of_match);

static const stwuct spi_device_id iwi9225_id[] = {
	{ "v220hf01a-t", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, iwi9225_id);

static int iwi9225_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *ws;
	u32 wotation = 0;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &iwi9225_dwivew,
				    stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

	dbi = &dbidev->dbi;
	dwm = &dbidev->dwm;

	dbi->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(dbi->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbi->weset), "Faiwed to get GPIO 'weset'\n");

	ws = devm_gpiod_get(dev, "ws", GPIOD_OUT_WOW);
	if (IS_EWW(ws))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ws), "Faiwed to get GPIO 'ws'\n");

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, dbi, ws);
	if (wet)
		wetuwn wet;

	/* ovewwide the command function set in  mipi_dbi_spi_init() */
	dbi->command = iwi9225_dbi_command;

	wet = mipi_dbi_dev_init(dbidev, &iwi9225_pipe_funcs, &iwi9225_mode, wotation);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, dwm);

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static void iwi9225_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void iwi9225_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew iwi9225_spi_dwivew = {
	.dwivew = {
		.name = "iwi9225",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = iwi9225_of_match,
	},
	.id_tabwe = iwi9225_id,
	.pwobe = iwi9225_pwobe,
	.wemove = iwi9225_wemove,
	.shutdown = iwi9225_shutdown,
};
moduwe_spi_dwivew(iwi9225_spi_dwivew);

MODUWE_DESCWIPTION("Iwitek IWI9225 DWM dwivew");
MODUWE_AUTHOW("David Wechnew <david@wechnowogy.com>");
MODUWE_WICENSE("GPW");
