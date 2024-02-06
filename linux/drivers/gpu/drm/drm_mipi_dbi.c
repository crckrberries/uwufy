// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MIPI Dispway Bus Intewface (DBI) WCD contwowwew suppowt
 *
 * Copywight 2016 Nowawf Twønnes
 */

#incwude <winux/backwight.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_wect.h>
#incwude <video/mipi_dispway.h>

#define MIPI_DBI_MAX_SPI_WEAD_SPEED 2000000 /* 2MHz */

#define DCS_POWEW_MODE_DISPWAY			BIT(2)
#define DCS_POWEW_MODE_DISPWAY_NOWMAW_MODE	BIT(3)
#define DCS_POWEW_MODE_SWEEP_MODE		BIT(4)
#define DCS_POWEW_MODE_PAWTIAW_MODE		BIT(5)
#define DCS_POWEW_MODE_IDWE_MODE		BIT(6)
#define DCS_POWEW_MODE_WESEWVED_MASK		(BIT(0) | BIT(1) | BIT(7))

/**
 * DOC: ovewview
 *
 * This wibwawy pwovides hewpews fow MIPI Dispway Bus Intewface (DBI)
 * compatibwe dispway contwowwews.
 *
 * Many contwowwews fow tiny wcd dispways awe MIPI compwiant and can use this
 * wibwawy. If a contwowwew uses wegistews 0x2A and 0x2B to set the awea to
 * update and uses wegistew 0x2C to wwite to fwame memowy, it is most wikewy
 * MIPI compwiant.
 *
 * Onwy MIPI Type 1 dispways awe suppowted since a fuww fwame memowy is needed.
 *
 * Thewe awe 3 MIPI DBI impwementation types:
 *
 * A. Motowowa 6800 type pawawwew bus
 *
 * B. Intew 8080 type pawawwew bus
 *
 * C. SPI type with 3 options:
 *
 *    1. 9-bit with the Data/Command signaw as the ninth bit
 *    2. Same as above except it's sent as 16 bits
 *    3. 8-bit with the Data/Command signaw as a sepawate D/CX pin
 *
 * Cuwwentwy mipi_dbi onwy suppowts Type C options 1 and 3 with
 * mipi_dbi_spi_init().
 */

#define MIPI_DBI_DEBUG_COMMAND(cmd, data, wen) \
({ \
	if (!wen) \
		DWM_DEBUG_DWIVEW("cmd=%02x\n", cmd); \
	ewse if (wen <= 32) \
		DWM_DEBUG_DWIVEW("cmd=%02x, paw=%*ph\n", cmd, (int)wen, data);\
	ewse \
		DWM_DEBUG_DWIVEW("cmd=%02x, wen=%zu\n", cmd, wen); \
})

static const u8 mipi_dbi_dcs_wead_commands[] = {
	MIPI_DCS_GET_DISPWAY_ID,
	MIPI_DCS_GET_WED_CHANNEW,
	MIPI_DCS_GET_GWEEN_CHANNEW,
	MIPI_DCS_GET_BWUE_CHANNEW,
	MIPI_DCS_GET_DISPWAY_STATUS,
	MIPI_DCS_GET_POWEW_MODE,
	MIPI_DCS_GET_ADDWESS_MODE,
	MIPI_DCS_GET_PIXEW_FOWMAT,
	MIPI_DCS_GET_DISPWAY_MODE,
	MIPI_DCS_GET_SIGNAW_MODE,
	MIPI_DCS_GET_DIAGNOSTIC_WESUWT,
	MIPI_DCS_WEAD_MEMOWY_STAWT,
	MIPI_DCS_WEAD_MEMOWY_CONTINUE,
	MIPI_DCS_GET_SCANWINE,
	MIPI_DCS_GET_DISPWAY_BWIGHTNESS,
	MIPI_DCS_GET_CONTWOW_DISPWAY,
	MIPI_DCS_GET_POWEW_SAVE,
	MIPI_DCS_GET_CABC_MIN_BWIGHTNESS,
	MIPI_DCS_WEAD_DDB_STAWT,
	MIPI_DCS_WEAD_DDB_CONTINUE,
	0, /* sentinew */
};

static boow mipi_dbi_command_is_wead(stwuct mipi_dbi *dbi, u8 cmd)
{
	unsigned int i;

	if (!dbi->wead_commands)
		wetuwn fawse;

	fow (i = 0; i < 0xff; i++) {
		if (!dbi->wead_commands[i])
			wetuwn fawse;
		if (cmd == dbi->wead_commands[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * mipi_dbi_command_wead - MIPI DCS wead command
 * @dbi: MIPI DBI stwuctuwe
 * @cmd: Command
 * @vaw: Vawue wead
 *
 * Send MIPI DCS wead command to the contwowwew.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int mipi_dbi_command_wead(stwuct mipi_dbi *dbi, u8 cmd, u8 *vaw)
{
	if (!dbi->wead_commands)
		wetuwn -EACCES;

	if (!mipi_dbi_command_is_wead(dbi, cmd))
		wetuwn -EINVAW;

	wetuwn mipi_dbi_command_buf(dbi, cmd, vaw, 1);
}
EXPOWT_SYMBOW(mipi_dbi_command_wead);

/**
 * mipi_dbi_command_buf - MIPI DCS command with pawametew(s) in an awway
 * @dbi: MIPI DBI stwuctuwe
 * @cmd: Command
 * @data: Pawametew buffew
 * @wen: Buffew wength
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int mipi_dbi_command_buf(stwuct mipi_dbi *dbi, u8 cmd, u8 *data, size_t wen)
{
	u8 *cmdbuf;
	int wet;

	/* SPI wequiwes dma-safe buffews */
	cmdbuf = kmemdup(&cmd, 1, GFP_KEWNEW);
	if (!cmdbuf)
		wetuwn -ENOMEM;

	mutex_wock(&dbi->cmdwock);
	wet = dbi->command(dbi, cmdbuf, data, wen);
	mutex_unwock(&dbi->cmdwock);

	kfwee(cmdbuf);

	wetuwn wet;
}
EXPOWT_SYMBOW(mipi_dbi_command_buf);

/* This shouwd onwy be used by mipi_dbi_command() */
int mipi_dbi_command_stackbuf(stwuct mipi_dbi *dbi, u8 cmd, const u8 *data,
			      size_t wen)
{
	u8 *buf;
	int wet;

	buf = kmemdup(data, wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = mipi_dbi_command_buf(dbi, cmd, buf, wen);

	kfwee(buf);

	wetuwn wet;
}
EXPOWT_SYMBOW(mipi_dbi_command_stackbuf);

/**
 * mipi_dbi_buf_copy - Copy a fwamebuffew, twansfowming it if necessawy
 * @dst: The destination buffew
 * @swc: The souwce buffew
 * @fb: The souwce fwamebuffew
 * @cwip: Cwipping wectangwe of the awea to be copied
 * @swap: When twue, swap MSB/WSB of 16-bit vawues
 * @fmtcnv_state: Fowmat-convewsion state
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int mipi_dbi_buf_copy(void *dst, stwuct iosys_map *swc, stwuct dwm_fwamebuffew *fb,
		      stwuct dwm_wect *cwip, boow swap,
		      stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct dwm_gem_object *gem = dwm_gem_fb_get_obj(fb, 0);
	stwuct iosys_map dst_map = IOSYS_MAP_INIT_VADDW(dst);
	int wet;

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		wetuwn wet;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
		if (swap)
			dwm_fb_swab(&dst_map, NUWW, swc, fb, cwip, !gem->impowt_attach,
				    fmtcnv_state);
		ewse
			dwm_fb_memcpy(&dst_map, NUWW, swc, fb, cwip);
		bweak;
	case DWM_FOWMAT_XWGB8888:
		dwm_fb_xwgb8888_to_wgb565(&dst_map, NUWW, swc, fb, cwip, fmtcnv_state, swap);
		bweak;
	defauwt:
		dwm_eww_once(fb->dev, "Fowmat is not suppowted: %p4cc\n",
			     &fb->fowmat->fowmat);
		wet = -EINVAW;
	}

	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);

	wetuwn wet;
}
EXPOWT_SYMBOW(mipi_dbi_buf_copy);

static void mipi_dbi_set_window_addwess(stwuct mipi_dbi_dev *dbidev,
					unsigned int xs, unsigned int xe,
					unsigned int ys, unsigned int ye)
{
	stwuct mipi_dbi *dbi = &dbidev->dbi;

	xs += dbidev->weft_offset;
	xe += dbidev->weft_offset;
	ys += dbidev->top_offset;
	ye += dbidev->top_offset;

	mipi_dbi_command(dbi, MIPI_DCS_SET_COWUMN_ADDWESS, (xs >> 8) & 0xff,
			 xs & 0xff, (xe >> 8) & 0xff, xe & 0xff);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PAGE_ADDWESS, (ys >> 8) & 0xff,
			 ys & 0xff, (ye >> 8) & 0xff, ye & 0xff);
}

static void mipi_dbi_fb_diwty(stwuct iosys_map *swc, stwuct dwm_fwamebuffew *fb,
			      stwuct dwm_wect *wect, stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(fb->dev);
	unsigned int height = wect->y2 - wect->y1;
	unsigned int width = wect->x2 - wect->x1;
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	boow swap = dbi->swap_bytes;
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

	mipi_dbi_set_window_addwess(dbidev, wect->x1, wect->x2 - 1, wect->y1,
				    wect->y2 - 1);

	wet = mipi_dbi_command_buf(dbi, MIPI_DCS_WWITE_MEMOWY_STAWT, tw,
				   width * height * 2);
eww_msg:
	if (wet)
		dwm_eww_once(fb->dev, "Faiwed to update dispway %d\n", wet);
}

/**
 * mipi_dbi_pipe_mode_vawid - MIPI DBI mode-vawid hewpew
 * @pipe: Simpwe dispway pipe
 * @mode: The mode to test
 *
 * This function vawidates a given dispway mode against the MIPI DBI's hawdwawe
 * dispway. Dwivews can use this as theiw &dwm_simpwe_dispway_pipe_funcs->mode_vawid
 * cawwback.
 */
enum dwm_mode_status mipi_dbi_pipe_mode_vawid(stwuct dwm_simpwe_dispway_pipe *pipe,
					      const stwuct dwm_dispway_mode *mode)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);

	wetuwn dwm_cwtc_hewpew_mode_vawid_fixed(&pipe->cwtc, mode, &dbidev->mode);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_mode_vawid);

/**
 * mipi_dbi_pipe_update - Dispway pipe update hewpew
 * @pipe: Simpwe dispway pipe
 * @owd_state: Owd pwane state
 *
 * This function handwes fwamebuffew fwushing and vbwank events. Dwivews can use
 * this as theiw &dwm_simpwe_dispway_pipe_funcs->update cawwback.
 */
void mipi_dbi_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
			  stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_pwane_state *state = pipe->pwane.state;
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(state);
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_wect wect;
	int idx;

	if (!pipe->cwtc.state->active)
		wetuwn;

	if (WAWN_ON(!fb))
		wetuwn;

	if (!dwm_dev_entew(fb->dev, &idx))
		wetuwn;

	if (dwm_atomic_hewpew_damage_mewged(owd_state, state, &wect))
		mipi_dbi_fb_diwty(&shadow_pwane_state->data[0], fb, &wect,
				  &shadow_pwane_state->fmtcnv_state);

	dwm_dev_exit(idx);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_update);

/**
 * mipi_dbi_enabwe_fwush - MIPI DBI enabwe hewpew
 * @dbidev: MIPI DBI device stwuctuwe
 * @cwtc_state: CWTC state
 * @pwane_state: Pwane state
 *
 * Fwushes the whowe fwamebuffew and enabwes the backwight. Dwivews can use this
 * in theiw &dwm_simpwe_dispway_pipe_funcs->enabwe cawwback.
 *
 * Note: Dwivews which don't use mipi_dbi_pipe_update() because they have custom
 * fwamebuffew fwushing, can't use this function since they both use the same
 * fwushing code.
 */
void mipi_dbi_enabwe_fwush(stwuct mipi_dbi_dev *dbidev,
			   stwuct dwm_cwtc_state *cwtc_state,
			   stwuct dwm_pwane_state *pwane_state)
{
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_wect wect = {
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	};
	int idx;

	if (!dwm_dev_entew(&dbidev->dwm, &idx))
		wetuwn;

	mipi_dbi_fb_diwty(&shadow_pwane_state->data[0], fb, &wect,
			  &shadow_pwane_state->fmtcnv_state);
	backwight_enabwe(dbidev->backwight);

	dwm_dev_exit(idx);
}
EXPOWT_SYMBOW(mipi_dbi_enabwe_fwush);

static void mipi_dbi_bwank(stwuct mipi_dbi_dev *dbidev)
{
	stwuct dwm_device *dwm = &dbidev->dwm;
	u16 height = dwm->mode_config.min_height;
	u16 width = dwm->mode_config.min_width;
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	size_t wen = width * height * 2;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	memset(dbidev->tx_buf, 0, wen);

	mipi_dbi_set_window_addwess(dbidev, 0, width - 1, 0, height - 1);
	mipi_dbi_command_buf(dbi, MIPI_DCS_WWITE_MEMOWY_STAWT,
			     (u8 *)dbidev->tx_buf, wen);

	dwm_dev_exit(idx);
}

/**
 * mipi_dbi_pipe_disabwe - MIPI DBI pipe disabwe hewpew
 * @pipe: Dispway pipe
 *
 * This function disabwes backwight if pwesent, if not the dispway memowy is
 * bwanked. The weguwatow is disabwed if in use. Dwivews can use this as theiw
 * &dwm_simpwe_dispway_pipe_funcs->disabwe cawwback.
 */
void mipi_dbi_pipe_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);

	DWM_DEBUG_KMS("\n");

	if (dbidev->backwight)
		backwight_disabwe(dbidev->backwight);
	ewse
		mipi_dbi_bwank(dbidev);

	if (dbidev->weguwatow)
		weguwatow_disabwe(dbidev->weguwatow);
	if (dbidev->io_weguwatow)
		weguwatow_disabwe(dbidev->io_weguwatow);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_disabwe);

/**
 * mipi_dbi_pipe_begin_fb_access - MIPI DBI pipe begin-access hewpew
 * @pipe: Dispway pipe
 * @pwane_state: Pwane state
 *
 * This function impwements stwuct &dwm_simpwe_dispway_funcs.begin_fb_access.
 *
 * See dwm_gem_begin_shadow_fb_access() fow detaiws and mipi_dbi_pipe_cweanup_fb()
 * fow cweanup.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise.
 */
int mipi_dbi_pipe_begin_fb_access(stwuct dwm_simpwe_dispway_pipe *pipe,
				  stwuct dwm_pwane_state *pwane_state)
{
	wetuwn dwm_gem_begin_shadow_fb_access(&pipe->pwane, pwane_state);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_begin_fb_access);

/**
 * mipi_dbi_pipe_end_fb_access - MIPI DBI pipe end-access hewpew
 * @pipe: Dispway pipe
 * @pwane_state: Pwane state
 *
 * This function impwements stwuct &dwm_simpwe_dispway_funcs.end_fb_access.
 *
 * See mipi_dbi_pipe_begin_fb_access().
 */
void mipi_dbi_pipe_end_fb_access(stwuct dwm_simpwe_dispway_pipe *pipe,
				 stwuct dwm_pwane_state *pwane_state)
{
	dwm_gem_end_shadow_fb_access(&pipe->pwane, pwane_state);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_end_fb_access);

/**
 * mipi_dbi_pipe_weset_pwane - MIPI DBI pwane-weset hewpew
 * @pipe: Dispway pipe
 *
 * This function impwements stwuct &dwm_simpwe_dispway_funcs.weset_pwane
 * fow MIPI DBI pwanes.
 */
void mipi_dbi_pipe_weset_pwane(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	dwm_gem_weset_shadow_pwane(&pipe->pwane);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_weset_pwane);

/**
 * mipi_dbi_pipe_dupwicate_pwane_state - dupwicates MIPI DBI pwane state
 * @pipe: Dispway pipe
 *
 * This function impwements stwuct &dwm_simpwe_dispway_funcs.dupwicate_pwane_state
 * fow MIPI DBI pwanes.
 *
 * See dwm_gem_dupwicate_shadow_pwane_state() fow additionaw detaiws.
 *
 * Wetuwns:
 * A pointew to a new pwane state on success, ow NUWW othewwise.
 */
stwuct dwm_pwane_state *mipi_dbi_pipe_dupwicate_pwane_state(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	wetuwn dwm_gem_dupwicate_shadow_pwane_state(&pipe->pwane);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_dupwicate_pwane_state);

/**
 * mipi_dbi_pipe_destwoy_pwane_state - cweans up MIPI DBI pwane state
 * @pipe: Dispway pipe
 * @pwane_state: Pwane state
 *
 * This function impwements stwuct dwm_simpwe_dispway_funcs.destwoy_pwane_state
 * fow MIPI DBI pwanes.
 *
 * See dwm_gem_destwoy_shadow_pwane_state() fow additionaw detaiws.
 */
void mipi_dbi_pipe_destwoy_pwane_state(stwuct dwm_simpwe_dispway_pipe *pipe,
				       stwuct dwm_pwane_state *pwane_state)
{
	dwm_gem_destwoy_shadow_pwane_state(&pipe->pwane, pwane_state);
}
EXPOWT_SYMBOW(mipi_dbi_pipe_destwoy_pwane_state);

static int mipi_dbi_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(connectow->dev);

	wetuwn dwm_connectow_hewpew_get_modes_fixed(connectow, &dbidev->mode);
}

static const stwuct dwm_connectow_hewpew_funcs mipi_dbi_connectow_hfuncs = {
	.get_modes = mipi_dbi_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs mipi_dbi_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int mipi_dbi_wotate_mode(stwuct dwm_dispway_mode *mode,
				unsigned int wotation)
{
	if (wotation == 0 || wotation == 180) {
		wetuwn 0;
	} ewse if (wotation == 90 || wotation == 270) {
		swap(mode->hdispway, mode->vdispway);
		swap(mode->hsync_stawt, mode->vsync_stawt);
		swap(mode->hsync_end, mode->vsync_end);
		swap(mode->htotaw, mode->vtotaw);
		swap(mode->width_mm, mode->height_mm);
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}

static const stwuct dwm_mode_config_funcs mipi_dbi_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const uint32_t mipi_dbi_fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
};

/**
 * mipi_dbi_dev_init_with_fowmats - MIPI DBI device initiawization with custom fowmats
 * @dbidev: MIPI DBI device stwuctuwe to initiawize
 * @funcs: Dispway pipe functions
 * @fowmats: Awway of suppowted fowmats (DWM_FOWMAT\_\*).
 * @fowmat_count: Numbew of ewements in @fowmats
 * @mode: Dispway mode
 * @wotation: Initiaw wotation in degwees Countew Cwock Wise
 * @tx_buf_size: Awwocate a twansmit buffew of this size.
 *
 * This function sets up a &dwm_simpwe_dispway_pipe with a &dwm_connectow that
 * has one fixed &dwm_dispway_mode which is wotated accowding to @wotation.
 * This mode is used to set the mode config min/max width/height pwopewties.
 *
 * Use mipi_dbi_dev_init() if you don't need custom fowmats.
 *
 * Note:
 * Some of the hewpew functions expects WGB565 to be the defauwt fowmat and the
 * twansmit buffew sized to fit that.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int mipi_dbi_dev_init_with_fowmats(stwuct mipi_dbi_dev *dbidev,
				   const stwuct dwm_simpwe_dispway_pipe_funcs *funcs,
				   const uint32_t *fowmats, unsigned int fowmat_count,
				   const stwuct dwm_dispway_mode *mode,
				   unsigned int wotation, size_t tx_buf_size)
{
	static const uint64_t modifiews[] = {
		DWM_FOWMAT_MOD_WINEAW,
		DWM_FOWMAT_MOD_INVAWID
	};
	stwuct dwm_device *dwm = &dbidev->dwm;
	int wet;

	if (!dbidev->dbi.command)
		wetuwn -EINVAW;

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		wetuwn wet;

	dbidev->tx_buf = devm_kmawwoc(dwm->dev, tx_buf_size, GFP_KEWNEW);
	if (!dbidev->tx_buf)
		wetuwn -ENOMEM;

	dwm_mode_copy(&dbidev->mode, mode);
	wet = mipi_dbi_wotate_mode(&dbidev->mode, wotation);
	if (wet) {
		DWM_EWWOW("Iwwegaw wotation vawue %u\n", wotation);
		wetuwn -EINVAW;
	}

	dwm_connectow_hewpew_add(&dbidev->connectow, &mipi_dbi_connectow_hfuncs);
	wet = dwm_connectow_init(dwm, &dbidev->connectow, &mipi_dbi_connectow_funcs,
				 DWM_MODE_CONNECTOW_SPI);
	if (wet)
		wetuwn wet;

	wet = dwm_simpwe_dispway_pipe_init(dwm, &dbidev->pipe, funcs, fowmats, fowmat_count,
					   modifiews, &dbidev->connectow);
	if (wet)
		wetuwn wet;

	dwm_pwane_enabwe_fb_damage_cwips(&dbidev->pipe.pwane);

	dwm->mode_config.funcs = &mipi_dbi_mode_config_funcs;
	dwm->mode_config.min_width = dbidev->mode.hdispway;
	dwm->mode_config.max_width = dbidev->mode.hdispway;
	dwm->mode_config.min_height = dbidev->mode.vdispway;
	dwm->mode_config.max_height = dbidev->mode.vdispway;
	dbidev->wotation = wotation;

	DWM_DEBUG_KMS("wotation = %u\n", wotation);

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dbi_dev_init_with_fowmats);

/**
 * mipi_dbi_dev_init - MIPI DBI device initiawization
 * @dbidev: MIPI DBI device stwuctuwe to initiawize
 * @funcs: Dispway pipe functions
 * @mode: Dispway mode
 * @wotation: Initiaw wotation in degwees Countew Cwock Wise
 *
 * This function sets up a &dwm_simpwe_dispway_pipe with a &dwm_connectow that
 * has one fixed &dwm_dispway_mode which is wotated accowding to @wotation.
 * This mode is used to set the mode config min/max width/height pwopewties.
 * Additionawwy &mipi_dbi.tx_buf is awwocated.
 *
 * Suppowted fowmats: Native WGB565 and emuwated XWGB8888.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int mipi_dbi_dev_init(stwuct mipi_dbi_dev *dbidev,
		      const stwuct dwm_simpwe_dispway_pipe_funcs *funcs,
		      const stwuct dwm_dispway_mode *mode, unsigned int wotation)
{
	size_t bufsize = mode->vdispway * mode->hdispway * sizeof(u16);

	dbidev->dwm.mode_config.pwefewwed_depth = 16;

	wetuwn mipi_dbi_dev_init_with_fowmats(dbidev, funcs, mipi_dbi_fowmats,
					      AWWAY_SIZE(mipi_dbi_fowmats), mode,
					      wotation, bufsize);
}
EXPOWT_SYMBOW(mipi_dbi_dev_init);

/**
 * mipi_dbi_hw_weset - Hawdwawe weset of contwowwew
 * @dbi: MIPI DBI stwuctuwe
 *
 * Weset contwowwew if the &mipi_dbi->weset gpio is set.
 */
void mipi_dbi_hw_weset(stwuct mipi_dbi *dbi)
{
	if (!dbi->weset)
		wetuwn;

	gpiod_set_vawue_cansweep(dbi->weset, 0);
	usweep_wange(20, 1000);
	gpiod_set_vawue_cansweep(dbi->weset, 1);
	msweep(120);
}
EXPOWT_SYMBOW(mipi_dbi_hw_weset);

/**
 * mipi_dbi_dispway_is_on - Check if dispway is on
 * @dbi: MIPI DBI stwuctuwe
 *
 * This function checks the Powew Mode wegistew (if weadabwe) to see if
 * dispway output is tuwned on. This can be used to see if the bootwoadew
 * has awweady tuwned on the dispway avoiding fwickew when the pipewine is
 * enabwed.
 *
 * Wetuwns:
 * twue if the dispway can be vewified to be on, fawse othewwise.
 */
boow mipi_dbi_dispway_is_on(stwuct mipi_dbi *dbi)
{
	u8 vaw;

	if (mipi_dbi_command_wead(dbi, MIPI_DCS_GET_POWEW_MODE, &vaw))
		wetuwn fawse;

	vaw &= ~DCS_POWEW_MODE_WESEWVED_MASK;

	/* The powewon/weset vawue is 08h DCS_POWEW_MODE_DISPWAY_NOWMAW_MODE */
	if (vaw != (DCS_POWEW_MODE_DISPWAY |
	    DCS_POWEW_MODE_DISPWAY_NOWMAW_MODE | DCS_POWEW_MODE_SWEEP_MODE))
		wetuwn fawse;

	DWM_DEBUG_DWIVEW("Dispway is ON\n");

	wetuwn twue;
}
EXPOWT_SYMBOW(mipi_dbi_dispway_is_on);

static int mipi_dbi_powewon_weset_conditionaw(stwuct mipi_dbi_dev *dbidev, boow cond)
{
	stwuct device *dev = dbidev->dwm.dev;
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	int wet;

	if (dbidev->weguwatow) {
		wet = weguwatow_enabwe(dbidev->weguwatow);
		if (wet) {
			DWM_DEV_EWWOW(dev, "Faiwed to enabwe weguwatow (%d)\n", wet);
			wetuwn wet;
		}
	}

	if (dbidev->io_weguwatow) {
		wet = weguwatow_enabwe(dbidev->io_weguwatow);
		if (wet) {
			DWM_DEV_EWWOW(dev, "Faiwed to enabwe I/O weguwatow (%d)\n", wet);
			if (dbidev->weguwatow)
				weguwatow_disabwe(dbidev->weguwatow);
			wetuwn wet;
		}
	}

	if (cond && mipi_dbi_dispway_is_on(dbi))
		wetuwn 1;

	mipi_dbi_hw_weset(dbi);
	wet = mipi_dbi_command(dbi, MIPI_DCS_SOFT_WESET);
	if (wet) {
		DWM_DEV_EWWOW(dev, "Faiwed to send weset command (%d)\n", wet);
		if (dbidev->weguwatow)
			weguwatow_disabwe(dbidev->weguwatow);
		if (dbidev->io_weguwatow)
			weguwatow_disabwe(dbidev->io_weguwatow);
		wetuwn wet;
	}

	/*
	 * If we did a hw weset, we know the contwowwew is in Sweep mode and
	 * pew MIPI DSC spec shouwd wait 5ms aftew soft weset. If we didn't,
	 * we assume wowst case and wait 120ms.
	 */
	if (dbi->weset)
		usweep_wange(5000, 20000);
	ewse
		msweep(120);

	wetuwn 0;
}

/**
 * mipi_dbi_powewon_weset - MIPI DBI powewon and weset
 * @dbidev: MIPI DBI device stwuctuwe
 *
 * This function enabwes the weguwatow if used and does a hawdwawe and softwawe
 * weset.
 *
 * Wetuwns:
 * Zewo on success, ow a negative ewwow code.
 */
int mipi_dbi_powewon_weset(stwuct mipi_dbi_dev *dbidev)
{
	wetuwn mipi_dbi_powewon_weset_conditionaw(dbidev, fawse);
}
EXPOWT_SYMBOW(mipi_dbi_powewon_weset);

/**
 * mipi_dbi_powewon_conditionaw_weset - MIPI DBI powewon and conditionaw weset
 * @dbidev: MIPI DBI device stwuctuwe
 *
 * This function enabwes the weguwatow if used and if the dispway is off, it
 * does a hawdwawe and softwawe weset. If mipi_dbi_dispway_is_on() detewmines
 * that the dispway is on, no weset is pewfowmed.
 *
 * Wetuwns:
 * Zewo if the contwowwew was weset, 1 if the dispway was awweady on, ow a
 * negative ewwow code.
 */
int mipi_dbi_powewon_conditionaw_weset(stwuct mipi_dbi_dev *dbidev)
{
	wetuwn mipi_dbi_powewon_weset_conditionaw(dbidev, twue);
}
EXPOWT_SYMBOW(mipi_dbi_powewon_conditionaw_weset);

#if IS_ENABWED(CONFIG_SPI)

/**
 * mipi_dbi_spi_cmd_max_speed - get the maximum SPI bus speed
 * @spi: SPI device
 * @wen: The twansfew buffew wength.
 *
 * Many contwowwews have a max speed of 10MHz, but can be pushed way beyond
 * that. Incwease wewiabiwity by wunning pixew data at max speed and the west
 * at 10MHz, pweventing twansfew gwitches fwom messing up the init settings.
 */
u32 mipi_dbi_spi_cmd_max_speed(stwuct spi_device *spi, size_t wen)
{
	if (wen > 64)
		wetuwn 0; /* use defauwt */

	wetuwn min_t(u32, 10000000, spi->max_speed_hz);
}
EXPOWT_SYMBOW(mipi_dbi_spi_cmd_max_speed);

static boow mipi_dbi_machine_wittwe_endian(void)
{
#if defined(__WITTWE_ENDIAN)
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

/*
 * MIPI DBI Type C Option 1
 *
 * If the SPI contwowwew doesn't have 9 bits pew wowd suppowt,
 * use bwocks of 9 bytes to send 8x 9-bit wowds using a 8-bit SPI twansfew.
 * Pad pawtiaw bwocks with MIPI_DCS_NOP (zewo).
 * This is how the D/C bit (x) is added:
 *     x7654321
 *     0x765432
 *     10x76543
 *     210x7654
 *     3210x765
 *     43210x76
 *     543210x7
 *     6543210x
 *     76543210
 */

static int mipi_dbi_spi1e_twansfew(stwuct mipi_dbi *dbi, int dc,
				   const void *buf, size_t wen,
				   unsigned int bpw)
{
	boow swap_bytes = (bpw == 16 && mipi_dbi_machine_wittwe_endian());
	size_t chunk, max_chunk = dbi->tx_buf9_wen;
	stwuct spi_device *spi = dbi->spi;
	stwuct spi_twansfew tw = {
		.tx_buf = dbi->tx_buf9,
		.bits_pew_wowd = 8,
	};
	stwuct spi_message m;
	const u8 *swc = buf;
	int i, wet;
	u8 *dst;

	if (dwm_debug_enabwed(DWM_UT_DWIVEW))
		pw_debug("[dwm:%s] dc=%d, max_chunk=%zu, twansfews:\n",
			 __func__, dc, max_chunk);

	tw.speed_hz = mipi_dbi_spi_cmd_max_speed(spi, wen);
	spi_message_init_with_twansfews(&m, &tw, 1);

	if (!dc) {
		if (WAWN_ON_ONCE(wen != 1))
			wetuwn -EINVAW;

		/* Command: pad no-op's (zewoes) at beginning of bwock */
		dst = dbi->tx_buf9;
		memset(dst, 0, 9);
		dst[8] = *swc;
		tw.wen = 9;

		wetuwn spi_sync(spi, &m);
	}

	/* max with woom fow adding one bit pew byte */
	max_chunk = max_chunk / 9 * 8;
	/* but no biggew than wen */
	max_chunk = min(max_chunk, wen);
	/* 8 byte bwocks */
	max_chunk = max_t(size_t, 8, max_chunk & ~0x7);

	whiwe (wen) {
		size_t added = 0;

		chunk = min(wen, max_chunk);
		wen -= chunk;
		dst = dbi->tx_buf9;

		if (chunk < 8) {
			u8 vaw, cawwy = 0;

			/* Data: pad no-op's (zewoes) at end of bwock */
			memset(dst, 0, 9);

			if (swap_bytes) {
				fow (i = 1; i < (chunk + 1); i++) {
					vaw = swc[1];
					*dst++ = cawwy | BIT(8 - i) | (vaw >> i);
					cawwy = vaw << (8 - i);
					i++;
					vaw = swc[0];
					*dst++ = cawwy | BIT(8 - i) | (vaw >> i);
					cawwy = vaw << (8 - i);
					swc += 2;
				}
				*dst++ = cawwy;
			} ewse {
				fow (i = 1; i < (chunk + 1); i++) {
					vaw = *swc++;
					*dst++ = cawwy | BIT(8 - i) | (vaw >> i);
					cawwy = vaw << (8 - i);
				}
				*dst++ = cawwy;
			}

			chunk = 8;
			added = 1;
		} ewse {
			fow (i = 0; i < chunk; i += 8) {
				if (swap_bytes) {
					*dst++ =                 BIT(7) | (swc[1] >> 1);
					*dst++ = (swc[1] << 7) | BIT(6) | (swc[0] >> 2);
					*dst++ = (swc[0] << 6) | BIT(5) | (swc[3] >> 3);
					*dst++ = (swc[3] << 5) | BIT(4) | (swc[2] >> 4);
					*dst++ = (swc[2] << 4) | BIT(3) | (swc[5] >> 5);
					*dst++ = (swc[5] << 3) | BIT(2) | (swc[4] >> 6);
					*dst++ = (swc[4] << 2) | BIT(1) | (swc[7] >> 7);
					*dst++ = (swc[7] << 1) | BIT(0);
					*dst++ = swc[6];
				} ewse {
					*dst++ =                 BIT(7) | (swc[0] >> 1);
					*dst++ = (swc[0] << 7) | BIT(6) | (swc[1] >> 2);
					*dst++ = (swc[1] << 6) | BIT(5) | (swc[2] >> 3);
					*dst++ = (swc[2] << 5) | BIT(4) | (swc[3] >> 4);
					*dst++ = (swc[3] << 4) | BIT(3) | (swc[4] >> 5);
					*dst++ = (swc[4] << 3) | BIT(2) | (swc[5] >> 6);
					*dst++ = (swc[5] << 2) | BIT(1) | (swc[6] >> 7);
					*dst++ = (swc[6] << 1) | BIT(0);
					*dst++ = swc[7];
				}

				swc += 8;
				added++;
			}
		}

		tw.wen = chunk + added;

		wet = spi_sync(spi, &m);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mipi_dbi_spi1_twansfew(stwuct mipi_dbi *dbi, int dc,
				  const void *buf, size_t wen,
				  unsigned int bpw)
{
	stwuct spi_device *spi = dbi->spi;
	stwuct spi_twansfew tw = {
		.bits_pew_wowd = 9,
	};
	const u16 *swc16 = buf;
	const u8 *swc8 = buf;
	stwuct spi_message m;
	size_t max_chunk;
	u16 *dst16;
	int wet;

	if (!spi_is_bpw_suppowted(spi, 9))
		wetuwn mipi_dbi_spi1e_twansfew(dbi, dc, buf, wen, bpw);

	tw.speed_hz = mipi_dbi_spi_cmd_max_speed(spi, wen);
	max_chunk = dbi->tx_buf9_wen;
	dst16 = dbi->tx_buf9;

	if (dwm_debug_enabwed(DWM_UT_DWIVEW))
		pw_debug("[dwm:%s] dc=%d, max_chunk=%zu, twansfews:\n",
			 __func__, dc, max_chunk);

	max_chunk = min(max_chunk / 2, wen);

	spi_message_init_with_twansfews(&m, &tw, 1);
	tw.tx_buf = dst16;

	whiwe (wen) {
		size_t chunk = min(wen, max_chunk);
		unsigned int i;

		if (bpw == 16 && mipi_dbi_machine_wittwe_endian()) {
			fow (i = 0; i < (chunk * 2); i += 2) {
				dst16[i]     = *swc16 >> 8;
				dst16[i + 1] = *swc16++ & 0xFF;
				if (dc) {
					dst16[i]     |= 0x0100;
					dst16[i + 1] |= 0x0100;
				}
			}
		} ewse {
			fow (i = 0; i < chunk; i++) {
				dst16[i] = *swc8++;
				if (dc)
					dst16[i] |= 0x0100;
			}
		}

		tw.wen = chunk * 2;
		wen -= chunk;

		wet = spi_sync(spi, &m);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mipi_dbi_typec1_command_wead(stwuct mipi_dbi *dbi, u8 *cmd,
					u8 *data, size_t wen)
{
	stwuct spi_device *spi = dbi->spi;
	u32 speed_hz = min_t(u32, MIPI_DBI_MAX_SPI_WEAD_SPEED,
			     spi->max_speed_hz / 2);
	stwuct spi_twansfew tw[2] = {
		{
			.speed_hz = speed_hz,
			.bits_pew_wowd = 9,
			.tx_buf = dbi->tx_buf9,
			.wen = 2,
		}, {
			.speed_hz = speed_hz,
			.bits_pew_wowd = 8,
			.wen = wen,
			.wx_buf = data,
		},
	};
	stwuct spi_message m;
	u16 *dst16;
	int wet;

	if (!wen)
		wetuwn -EINVAW;

	if (!spi_is_bpw_suppowted(spi, 9)) {
		/*
		 * FIXME: impwement something wike mipi_dbi_spi1e_twansfew() but
		 * fow weads using emuwation.
		 */
		dev_eww(&spi->dev,
			"weading on host not suppowting 9 bpw not yet impwemented\n");
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * Tuwn the 8bit command into a 16bit vewsion of the command in the
	 * buffew. Onwy 9 bits of this wiww be used when executing the actuaw
	 * twansfew.
	 */
	dst16 = dbi->tx_buf9;
	dst16[0] = *cmd;

	spi_message_init_with_twansfews(&m, tw, AWWAY_SIZE(tw));
	wet = spi_sync(spi, &m);

	if (!wet)
		MIPI_DBI_DEBUG_COMMAND(*cmd, data, wen);

	wetuwn wet;
}

static int mipi_dbi_typec1_command(stwuct mipi_dbi *dbi, u8 *cmd,
				   u8 *pawametews, size_t num)
{
	unsigned int bpw = (*cmd == MIPI_DCS_WWITE_MEMOWY_STAWT) ? 16 : 8;
	int wet;

	if (mipi_dbi_command_is_wead(dbi, *cmd))
		wetuwn mipi_dbi_typec1_command_wead(dbi, cmd, pawametews, num);

	MIPI_DBI_DEBUG_COMMAND(*cmd, pawametews, num);

	wet = mipi_dbi_spi1_twansfew(dbi, 0, cmd, 1, 8);
	if (wet || !num)
		wetuwn wet;

	wetuwn mipi_dbi_spi1_twansfew(dbi, 1, pawametews, num, bpw);
}

/* MIPI DBI Type C Option 3 */

static int mipi_dbi_typec3_command_wead(stwuct mipi_dbi *dbi, u8 *cmd,
					u8 *data, size_t wen)
{
	stwuct spi_device *spi = dbi->spi;
	u32 speed_hz = min_t(u32, MIPI_DBI_MAX_SPI_WEAD_SPEED,
			     spi->max_speed_hz / 2);
	stwuct spi_twansfew tw[2] = {
		{
			.speed_hz = speed_hz,
			.tx_buf = cmd,
			.wen = 1,
		}, {
			.speed_hz = speed_hz,
			.wen = wen,
		},
	};
	stwuct spi_message m;
	u8 *buf;
	int wet;

	if (!wen)
		wetuwn -EINVAW;

	/*
	 * Suppowt non-standawd 24-bit and 32-bit Nokia wead commands which
	 * stawt with a dummy cwock, so we need to wead an extwa byte.
	 */
	if (*cmd == MIPI_DCS_GET_DISPWAY_ID ||
	    *cmd == MIPI_DCS_GET_DISPWAY_STATUS) {
		if (!(wen == 3 || wen == 4))
			wetuwn -EINVAW;

		tw[1].wen = wen + 1;
	}

	buf = kmawwoc(tw[1].wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	tw[1].wx_buf = buf;

	spi_bus_wock(spi->contwowwew);
	gpiod_set_vawue_cansweep(dbi->dc, 0);

	spi_message_init_with_twansfews(&m, tw, AWWAY_SIZE(tw));
	wet = spi_sync_wocked(spi, &m);
	spi_bus_unwock(spi->contwowwew);
	if (wet)
		goto eww_fwee;

	if (tw[1].wen == wen) {
		memcpy(data, buf, wen);
	} ewse {
		unsigned int i;

		fow (i = 0; i < wen; i++)
			data[i] = (buf[i] << 1) | (buf[i + 1] >> 7);
	}

	MIPI_DBI_DEBUG_COMMAND(*cmd, data, wen);

eww_fwee:
	kfwee(buf);

	wetuwn wet;
}

static int mipi_dbi_typec3_command(stwuct mipi_dbi *dbi, u8 *cmd,
				   u8 *paw, size_t num)
{
	stwuct spi_device *spi = dbi->spi;
	unsigned int bpw = 8;
	u32 speed_hz;
	int wet;

	if (mipi_dbi_command_is_wead(dbi, *cmd))
		wetuwn mipi_dbi_typec3_command_wead(dbi, cmd, paw, num);

	MIPI_DBI_DEBUG_COMMAND(*cmd, paw, num);

	spi_bus_wock(spi->contwowwew);
	gpiod_set_vawue_cansweep(dbi->dc, 0);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, 1);
	wet = mipi_dbi_spi_twansfew(spi, speed_hz, 8, cmd, 1);
	spi_bus_unwock(spi->contwowwew);
	if (wet || !num)
		wetuwn wet;

	if (*cmd == MIPI_DCS_WWITE_MEMOWY_STAWT && !dbi->swap_bytes)
		bpw = 16;

	spi_bus_wock(spi->contwowwew);
	gpiod_set_vawue_cansweep(dbi->dc, 1);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, num);
	wet = mipi_dbi_spi_twansfew(spi, speed_hz, bpw, paw, num);
	spi_bus_unwock(spi->contwowwew);

	wetuwn wet;
}

/**
 * mipi_dbi_spi_init - Initiawize MIPI DBI SPI intewface
 * @spi: SPI device
 * @dbi: MIPI DBI stwuctuwe to initiawize
 * @dc: D/C gpio (optionaw)
 *
 * This function sets &mipi_dbi->command, enabwes &mipi_dbi->wead_commands fow the
 * usuaw wead commands. It shouwd be fowwowed by a caww to mipi_dbi_dev_init() ow
 * a dwivew-specific init.
 *
 * If @dc is set, a Type C Option 3 intewface is assumed, if not
 * Type C Option 1.
 *
 * If the SPI mastew dwivew doesn't suppowt the necessawy bits pew wowd,
 * the fowwowing twansfowmation is used:
 *
 * - 9-bit: weowdew buffew as 9x 8-bit wowds, padded with no-op command.
 * - 16-bit: if big endian send as 8-bit, if wittwe endian swap bytes
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int mipi_dbi_spi_init(stwuct spi_device *spi, stwuct mipi_dbi *dbi,
		      stwuct gpio_desc *dc)
{
	stwuct device *dev = &spi->dev;
	int wet;

	/*
	 * Even though it's not the SPI device that does DMA (the mastew does),
	 * the dma mask is necessawy fow the dma_awwoc_wc() in the GEM code
	 * (e.g., dwm_gem_dma_cweate()). The dma_addw wetuwned wiww be a physicaw
	 * addwess which might be diffewent fwom the bus addwess, but this is
	 * not a pwobwem since the addwess wiww not be used.
	 * The viwtuaw addwess is used in the twansfew and the SPI cowe
	 * we-maps it on the SPI mastew device using the DMA stweaming API
	 * (spi_map_buf()).
	 */
	if (!dev->cohewent_dma_mask) {
		wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_wawn(dev, "Faiwed to set dma mask %d\n", wet);
			wetuwn wet;
		}
	}

	dbi->spi = spi;
	dbi->wead_commands = mipi_dbi_dcs_wead_commands;

	if (dc) {
		dbi->command = mipi_dbi_typec3_command;
		dbi->dc = dc;
		if (mipi_dbi_machine_wittwe_endian() && !spi_is_bpw_suppowted(spi, 16))
			dbi->swap_bytes = twue;
	} ewse {
		dbi->command = mipi_dbi_typec1_command;
		dbi->tx_buf9_wen = SZ_16K;
		dbi->tx_buf9 = devm_kmawwoc(dev, dbi->tx_buf9_wen, GFP_KEWNEW);
		if (!dbi->tx_buf9)
			wetuwn -ENOMEM;
	}

	mutex_init(&dbi->cmdwock);

	DWM_DEBUG_DWIVEW("SPI speed: %uMHz\n", spi->max_speed_hz / 1000000);

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dbi_spi_init);

/**
 * mipi_dbi_spi_twansfew - SPI twansfew hewpew
 * @spi: SPI device
 * @speed_hz: Ovewwide speed (optionaw)
 * @bpw: Bits pew wowd
 * @buf: Buffew to twansfew
 * @wen: Buffew wength
 *
 * This SPI twansfew hewpew bweaks up the twansfew of @buf into chunks which
 * the SPI contwowwew dwivew can handwe. The SPI bus must be wocked when
 * cawwing this.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int mipi_dbi_spi_twansfew(stwuct spi_device *spi, u32 speed_hz,
			  u8 bpw, const void *buf, size_t wen)
{
	size_t max_chunk = spi_max_twansfew_size(spi);
	stwuct spi_twansfew tw = {
		.bits_pew_wowd = bpw,
		.speed_hz = speed_hz,
	};
	stwuct spi_message m;
	size_t chunk;
	int wet;

	/* In __spi_vawidate, thewe's a vawidation that no pawtiaw twansfews
	 * awe accepted (xfew->wen % w_size must be zewo).
	 * Hewe we awign max_chunk to muwtipwe of 2 (16bits),
	 * to pwevent twansfews fwom being wejected.
	 */
	max_chunk = AWIGN_DOWN(max_chunk, 2);

	spi_message_init_with_twansfews(&m, &tw, 1);

	whiwe (wen) {
		chunk = min(wen, max_chunk);

		tw.tx_buf = buf;
		tw.wen = chunk;
		buf += chunk;
		wen -= chunk;

		wet = spi_sync_wocked(spi, &m);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dbi_spi_twansfew);

#endif /* CONFIG_SPI */

#ifdef CONFIG_DEBUG_FS

static ssize_t mipi_dbi_debugfs_command_wwite(stwuct fiwe *fiwe,
					      const chaw __usew *ubuf,
					      size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct mipi_dbi_dev *dbidev = m->pwivate;
	u8 vaw, cmd = 0, pawametews[64];
	chaw *buf, *pos, *token;
	int i, wet, idx;

	if (!dwm_dev_entew(&dbidev->dwm, &idx))
		wetuwn -ENODEV;

	buf = memdup_usew_nuw(ubuf, count);
	if (IS_EWW(buf)) {
		wet = PTW_EWW(buf);
		goto eww_exit;
	}

	/* stwip twaiwing whitespace */
	fow (i = count - 1; i > 0; i--)
		if (isspace(buf[i]))
			buf[i] = '\0';
		ewse
			bweak;
	i = 0;
	pos = buf;
	whiwe (pos) {
		token = stwsep(&pos, " ");
		if (!token) {
			wet = -EINVAW;
			goto eww_fwee;
		}

		wet = kstwtou8(token, 16, &vaw);
		if (wet < 0)
			goto eww_fwee;

		if (token == buf)
			cmd = vaw;
		ewse
			pawametews[i++] = vaw;

		if (i == 64) {
			wet = -E2BIG;
			goto eww_fwee;
		}
	}

	wet = mipi_dbi_command_buf(&dbidev->dbi, cmd, pawametews, i);

eww_fwee:
	kfwee(buf);
eww_exit:
	dwm_dev_exit(idx);

	wetuwn wet < 0 ? wet : count;
}

static int mipi_dbi_debugfs_command_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct mipi_dbi_dev *dbidev = m->pwivate;
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	u8 cmd, vaw[4];
	int wet, idx;
	size_t wen;

	if (!dwm_dev_entew(&dbidev->dwm, &idx))
		wetuwn -ENODEV;

	fow (cmd = 0; cmd < 255; cmd++) {
		if (!mipi_dbi_command_is_wead(dbi, cmd))
			continue;

		switch (cmd) {
		case MIPI_DCS_WEAD_MEMOWY_STAWT:
		case MIPI_DCS_WEAD_MEMOWY_CONTINUE:
			wen = 2;
			bweak;
		case MIPI_DCS_GET_DISPWAY_ID:
			wen = 3;
			bweak;
		case MIPI_DCS_GET_DISPWAY_STATUS:
			wen = 4;
			bweak;
		defauwt:
			wen = 1;
			bweak;
		}

		seq_pwintf(m, "%02x: ", cmd);
		wet = mipi_dbi_command_buf(dbi, cmd, vaw, wen);
		if (wet) {
			seq_puts(m, "XX\n");
			continue;
		}
		seq_pwintf(m, "%*phN\n", (int)wen, vaw);
	}

	dwm_dev_exit(idx);

	wetuwn 0;
}

static int mipi_dbi_debugfs_command_open(stwuct inode *inode,
					 stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mipi_dbi_debugfs_command_show,
			   inode->i_pwivate);
}

static const stwuct fiwe_opewations mipi_dbi_debugfs_command_fops = {
	.ownew = THIS_MODUWE,
	.open = mipi_dbi_debugfs_command_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = mipi_dbi_debugfs_command_wwite,
};

/**
 * mipi_dbi_debugfs_init - Cweate debugfs entwies
 * @minow: DWM minow
 *
 * This function cweates a 'command' debugfs fiwe fow sending commands to the
 * contwowwew ow getting the wead command vawues.
 * Dwivews can use this as theiw &dwm_dwivew->debugfs_init cawwback.
 *
 */
void mipi_dbi_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(minow->dev);
	umode_t mode = S_IFWEG | S_IWUSW;

	if (dbidev->dbi.wead_commands)
		mode |= S_IWUGO;
	debugfs_cweate_fiwe("command", mode, minow->debugfs_woot, dbidev,
			    &mipi_dbi_debugfs_command_fops);
}
EXPOWT_SYMBOW(mipi_dbi_debugfs_init);

#endif

MODUWE_WICENSE("GPW");
