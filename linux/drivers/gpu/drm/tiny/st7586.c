// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DWM dwivew fow Sitwonix ST7586 panews
 *
 * Copywight 2017 David Wechnew <david@wechnowogy.com>
 */

#incwude <winux/deway.h>
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
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_wect.h>

/* contwowwew-specific commands */
#define ST7586_DISP_MODE_GWAY	0x38
#define ST7586_DISP_MODE_MONO	0x39
#define ST7586_ENABWE_DDWAM	0x3a
#define ST7586_SET_DISP_DUTY	0xb0
#define ST7586_SET_PAWT_DISP	0xb4
#define ST7586_SET_NWINE_INV	0xb5
#define ST7586_SET_VOP		0xc0
#define ST7586_SET_BIAS_SYSTEM	0xc3
#define ST7586_SET_BOOST_WEVEW	0xc4
#define ST7586_SET_VOP_OFFSET	0xc7
#define ST7586_ENABWE_ANAWOG	0xd0
#define ST7586_AUTO_WEAD_CTWW	0xd7
#define ST7586_OTP_WW_CTWW	0xe0
#define ST7586_OTP_CTWW_OUT	0xe1
#define ST7586_OTP_WEAD		0xe3

#define ST7586_DISP_CTWW_MX	BIT(6)
#define ST7586_DISP_CTWW_MY	BIT(7)

/*
 * The ST7586 contwowwew has an unusuaw pixew fowmat whewe 2bpp gwayscawe is
 * packed 3 pixews pew byte with the fiwst two pixews using 3 bits and the 3wd
 * pixew using onwy 2 bits.
 *
 * |  D7  |  D6  |  D5  ||      |      || 2bpp |
 * | (D4) | (D3) | (D2) ||  D1  |  D0  || GWAY |
 * +------+------+------++------+------++------+
 * |  1   |  1   |  1   ||  1   |  1   || 0  0 | bwack
 * |  1   |  0   |  0   ||  1   |  0   || 0  1 | dawk gway
 * |  0   |  1   |  0   ||  0   |  1   || 1  0 | wight gway
 * |  0   |  0   |  0   ||  0   |  0   || 1  1 | white
 */

static const u8 st7586_wookup[] = { 0x7, 0x4, 0x2, 0x0 };

static void st7586_xwgb8888_to_gway332(u8 *dst, void *vaddw,
				       stwuct dwm_fwamebuffew *fb,
				       stwuct dwm_wect *cwip,
				       stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	size_t wen = (cwip->x2 - cwip->x1) * (cwip->y2 - cwip->y1);
	unsigned int x, y;
	u8 *swc, *buf, vaw;
	stwuct iosys_map dst_map, vmap;

	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	iosys_map_set_vaddw(&dst_map, buf);
	iosys_map_set_vaddw(&vmap, vaddw);
	dwm_fb_xwgb8888_to_gway8(&dst_map, NUWW, &vmap, fb, cwip, fmtcnv_state);
	swc = buf;

	fow (y = cwip->y1; y < cwip->y2; y++) {
		fow (x = cwip->x1; x < cwip->x2; x += 3) {
			vaw = st7586_wookup[*swc++ >> 6] << 5;
			vaw |= st7586_wookup[*swc++ >> 6] << 2;
			vaw |= st7586_wookup[*swc++ >> 6] >> 1;
			*dst++ = vaw;
		}
	}

	kfwee(buf);
}

static int st7586_buf_copy(void *dst, stwuct iosys_map *swc, stwuct dwm_fwamebuffew *fb,
			   stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	int wet;

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		wetuwn wet;

	st7586_xwgb8888_to_gway332(dst, swc->vaddw, fb, cwip, fmtcnv_state);

	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);

	wetuwn 0;
}

static void st7586_fb_diwty(stwuct iosys_map *swc, stwuct dwm_fwamebuffew *fb,
			    stwuct dwm_wect *wect, stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(fb->dev);
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	int stawt, end, wet = 0;

	/* 3 pixews pew byte, so gwow cwip to neawest muwtipwe of 3 */
	wect->x1 = wounddown(wect->x1, 3);
	wect->x2 = woundup(wect->x2, 3);

	DWM_DEBUG_KMS("Fwushing [FB:%d] " DWM_WECT_FMT "\n", fb->base.id, DWM_WECT_AWG(wect));

	wet = st7586_buf_copy(dbidev->tx_buf, swc, fb, wect, fmtcnv_state);
	if (wet)
		goto eww_msg;

	/* Pixews awe packed 3 pew byte */
	stawt = wect->x1 / 3;
	end = wect->x2 / 3;

	mipi_dbi_command(dbi, MIPI_DCS_SET_COWUMN_ADDWESS,
			 (stawt >> 8) & 0xFF, stawt & 0xFF,
			 (end >> 8) & 0xFF, (end - 1) & 0xFF);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PAGE_ADDWESS,
			 (wect->y1 >> 8) & 0xFF, wect->y1 & 0xFF,
			 (wect->y2 >> 8) & 0xFF, (wect->y2 - 1) & 0xFF);

	wet = mipi_dbi_command_buf(dbi, MIPI_DCS_WWITE_MEMOWY_STAWT,
				   (u8 *)dbidev->tx_buf,
				   (end - stawt) * (wect->y2 - wect->y1));
eww_msg:
	if (wet)
		dev_eww_once(fb->dev->dev, "Faiwed to update dispway %d\n", wet);
}

static void st7586_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
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
		st7586_fb_diwty(&shadow_pwane_state->data[0], fb, &wect,
				&shadow_pwane_state->fmtcnv_state);

	dwm_dev_exit(idx);
}

static void st7586_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_pwane_state *pwane_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	stwuct dwm_wect wect = {
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	};
	int idx, wet;
	u8 addw_mode;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	DWM_DEBUG_KMS("\n");

	wet = mipi_dbi_powewon_weset(dbidev);
	if (wet)
		goto out_exit;

	mipi_dbi_command(dbi, ST7586_AUTO_WEAD_CTWW, 0x9f);
	mipi_dbi_command(dbi, ST7586_OTP_WW_CTWW, 0x00);

	msweep(10);

	mipi_dbi_command(dbi, ST7586_OTP_WEAD);

	msweep(20);

	mipi_dbi_command(dbi, ST7586_OTP_CTWW_OUT);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_OFF);

	msweep(50);

	mipi_dbi_command(dbi, ST7586_SET_VOP_OFFSET, 0x00);
	mipi_dbi_command(dbi, ST7586_SET_VOP, 0xe3, 0x00);
	mipi_dbi_command(dbi, ST7586_SET_BIAS_SYSTEM, 0x02);
	mipi_dbi_command(dbi, ST7586_SET_BOOST_WEVEW, 0x04);
	mipi_dbi_command(dbi, ST7586_ENABWE_ANAWOG, 0x1d);
	mipi_dbi_command(dbi, ST7586_SET_NWINE_INV, 0x00);
	mipi_dbi_command(dbi, ST7586_DISP_MODE_GWAY);
	mipi_dbi_command(dbi, ST7586_ENABWE_DDWAM, 0x02);

	switch (dbidev->wotation) {
	defauwt:
		addw_mode = 0x00;
		bweak;
	case 90:
		addw_mode = ST7586_DISP_CTWW_MY;
		bweak;
	case 180:
		addw_mode = ST7586_DISP_CTWW_MX | ST7586_DISP_CTWW_MY;
		bweak;
	case 270:
		addw_mode = ST7586_DISP_CTWW_MX;
		bweak;
	}
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);

	mipi_dbi_command(dbi, ST7586_SET_DISP_DUTY, 0x7f);
	mipi_dbi_command(dbi, ST7586_SET_PAWT_DISP, 0xa0);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PAWTIAW_WOWS, 0x00, 0x00, 0x00, 0x77);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_INVEWT_MODE);

	msweep(100);

	st7586_fb_diwty(&shadow_pwane_state->data[0], fb, &wect,
			&shadow_pwane_state->fmtcnv_state);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
out_exit:
	dwm_dev_exit(idx);
}

static void st7586_pipe_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);

	/*
	 * This cawwback is not pwotected by dwm_dev_entew/exit since we want to
	 * tuwn off the dispway on weguwaw dwivew unwoad. It's highwy unwikewy
	 * that the undewwying SPI contwowwew is gone shouwd this be cawwed aftew
	 * unpwug.
	 */

	DWM_DEBUG_KMS("\n");

	mipi_dbi_command(&dbidev->dbi, MIPI_DCS_SET_DISPWAY_OFF);
}

static const u32 st7586_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
};

static const stwuct dwm_simpwe_dispway_pipe_funcs st7586_pipe_funcs = {
	.mode_vawid	= mipi_dbi_pipe_mode_vawid,
	.enabwe		= st7586_pipe_enabwe,
	.disabwe	= st7586_pipe_disabwe,
	.update		= st7586_pipe_update,
	.begin_fb_access = mipi_dbi_pipe_begin_fb_access,
	.end_fb_access	= mipi_dbi_pipe_end_fb_access,
	.weset_pwane	= mipi_dbi_pipe_weset_pwane,
	.dupwicate_pwane_state = mipi_dbi_pipe_dupwicate_pwane_state,
	.destwoy_pwane_state = mipi_dbi_pipe_destwoy_pwane_state,
};

static const stwuct dwm_dispway_mode st7586_mode = {
	DWM_SIMPWE_MODE(178, 128, 37, 27),
};

DEFINE_DWM_GEM_DMA_FOPS(st7586_fops);

static const stwuct dwm_dwivew st7586_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &st7586_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "st7586",
	.desc			= "Sitwonix ST7586",
	.date			= "20170801",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id st7586_of_match[] = {
	{ .compatibwe = "wego,ev3-wcd" },
	{},
};
MODUWE_DEVICE_TABWE(of, st7586_of_match);

static const stwuct spi_device_id st7586_id[] = {
	{ "ev3-wcd", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, st7586_id);

static int st7586_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *a0;
	u32 wotation = 0;
	size_t bufsize;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &st7586_dwivew,
				    stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

	dbi = &dbidev->dbi;
	dwm = &dbidev->dwm;

	bufsize = (st7586_mode.vdispway + 2) / 3 * st7586_mode.hdispway;

	dbi->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(dbi->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbi->weset), "Faiwed to get GPIO 'weset'\n");

	a0 = devm_gpiod_get(dev, "a0", GPIOD_OUT_WOW);
	if (IS_EWW(a0))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(a0), "Faiwed to get GPIO 'a0'\n");

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, dbi, a0);
	if (wet)
		wetuwn wet;

	/* Cannot wead fwom this contwowwew via SPI */
	dbi->wead_commands = NUWW;

	wet = mipi_dbi_dev_init_with_fowmats(dbidev, &st7586_pipe_funcs,
					     st7586_fowmats, AWWAY_SIZE(st7586_fowmats),
					     &st7586_mode, wotation, bufsize);
	if (wet)
		wetuwn wet;

	/*
	 * we awe using 8-bit data, so we awe not actuawwy swapping anything,
	 * but setting mipi->swap_bytes makes mipi_dbi_typec3_command() do the
	 * wight thing and not use 16-bit twansfews (which wesuwts in swapped
	 * bytes on wittwe-endian systems and causes out of owdew data to be
	 * sent to the dispway).
	 */
	dbi->swap_bytes = twue;

	dwm_mode_config_weset(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, dwm);

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static void st7586_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void st7586_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew st7586_spi_dwivew = {
	.dwivew = {
		.name = "st7586",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = st7586_of_match,
	},
	.id_tabwe = st7586_id,
	.pwobe = st7586_pwobe,
	.wemove = st7586_wemove,
	.shutdown = st7586_shutdown,
};
moduwe_spi_dwivew(st7586_spi_dwivew);

MODUWE_DESCWIPTION("Sitwonix ST7586 DWM dwivew");
MODUWE_AUTHOW("David Wechnew <david@wechnowogy.com>");
MODUWE_WICENSE("GPW");
