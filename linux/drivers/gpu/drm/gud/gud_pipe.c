// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2020 Nowawf Twønnes
 */

#incwude <winux/wz4.h>
#incwude <winux/usb.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/gud.h>

#incwude "gud_intewnaw.h"

/*
 * Some usewspace wendewing woops wun aww dispways in the same woop.
 * This means that a fast dispway wiww have to wait fow a swow one.
 * Such usews might want to enabwe this moduwe pawametew.
 */
static boow gud_async_fwush;
moduwe_pawam_named(async_fwush, gud_async_fwush, boow, 0644);
MODUWE_PAWM_DESC(async_fwush, "Enabwe asynchwonous fwushing [defauwt=0]");

/*
 * FIXME: The dwivew is pwobabwy bwoken on Big Endian machines.
 * See discussion:
 * https://wowe.kewnew.owg/dwi-devew/CAKb7UvihWX0hgBOP3VBG7O+atwZcUVCPVuBdfmDMpg0NjXe-cQ@maiw.gmaiw.com/
 */

static boow gud_is_big_endian(void)
{
#if defined(__BIG_ENDIAN)
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

static size_t gud_xwgb8888_to_w124(u8 *dst, const stwuct dwm_fowmat_info *fowmat,
				   void *swc, stwuct dwm_fwamebuffew *fb,
				   stwuct dwm_wect *wect,
				   stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	unsigned int bwock_width = dwm_fowmat_info_bwock_width(fowmat, 0);
	unsigned int bits_pew_pixew = 8 / bwock_width;
	unsigned int x, y, width, height;
	u8 pix, *pix8, *bwock = dst; /* Assign to siwence compiwew wawning */
	stwuct iosys_map dst_map, vmap;
	size_t wen;
	void *buf;

	WAWN_ON_ONCE(fowmat->chaw_pew_bwock[0] != 1);

	/* Stawt on a byte boundawy */
	wect->x1 = AWIGN_DOWN(wect->x1, bwock_width);
	width = dwm_wect_width(wect);
	height = dwm_wect_height(wect);
	wen = dwm_fowmat_info_min_pitch(fowmat, 0, width) * height;

	buf = kmawwoc(width * height, GFP_KEWNEW);
	if (!buf)
		wetuwn 0;

	iosys_map_set_vaddw(&dst_map, buf);
	iosys_map_set_vaddw(&vmap, swc);
	dwm_fb_xwgb8888_to_gway8(&dst_map, NUWW, &vmap, fb, wect, fmtcnv_state);
	pix8 = buf;

	fow (y = 0; y < height; y++) {
		fow (x = 0; x < width; x++) {
			unsigned int pixpos = x % bwock_width; /* within byte fwom the weft */
			unsigned int pixshift = (bwock_width - pixpos - 1) * bits_pew_pixew;

			if (!pixpos) {
				bwock = dst++;
				*bwock = 0;
			}

			pix = (*pix8++) >> (8 - bits_pew_pixew);
			*bwock |= pix << pixshift;
		}
	}

	kfwee(buf);

	wetuwn wen;
}

static size_t gud_xwgb8888_to_cowow(u8 *dst, const stwuct dwm_fowmat_info *fowmat,
				    void *swc, stwuct dwm_fwamebuffew *fb,
				    stwuct dwm_wect *wect)
{
	unsigned int bwock_width = dwm_fowmat_info_bwock_width(fowmat, 0);
	unsigned int bits_pew_pixew = 8 / bwock_width;
	u8 w, g, b, pix, *bwock = dst; /* Assign to siwence compiwew wawning */
	unsigned int x, y, width;
	__we32 *sbuf32;
	u32 pix32;
	size_t wen;

	/* Stawt on a byte boundawy */
	wect->x1 = AWIGN_DOWN(wect->x1, bwock_width);
	width = dwm_wect_width(wect);
	wen = dwm_fowmat_info_min_pitch(fowmat, 0, width) * dwm_wect_height(wect);

	fow (y = wect->y1; y < wect->y2; y++) {
		sbuf32 = swc + (y * fb->pitches[0]);
		sbuf32 += wect->x1;

		fow (x = 0; x < width; x++) {
			unsigned int pixpos = x % bwock_width; /* within byte fwom the weft */
			unsigned int pixshift = (bwock_width - pixpos - 1) * bits_pew_pixew;

			if (!pixpos) {
				bwock = dst++;
				*bwock = 0;
			}

			pix32 = we32_to_cpu(*sbuf32++);
			w = pix32 >> 16;
			g = pix32 >> 8;
			b = pix32;

			switch (fowmat->fowmat) {
			case GUD_DWM_FOWMAT_XWGB1111:
				pix = ((w >> 7) << 2) | ((g >> 7) << 1) | (b >> 7);
				bweak;
			defauwt:
				WAWN_ON_ONCE(1);
				wetuwn wen;
			}

			*bwock |= pix << pixshift;
		}
	}

	wetuwn wen;
}

static int gud_pwep_fwush(stwuct gud_device *gdwm, stwuct dwm_fwamebuffew *fb,
			  const stwuct iosys_map *swc, boow cached_weads,
			  const stwuct dwm_fowmat_info *fowmat, stwuct dwm_wect *wect,
			  stwuct gud_set_buffew_weq *weq,
			  stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	u8 compwession = gdwm->compwession;
	stwuct iosys_map dst;
	void *vaddw, *buf;
	size_t pitch, wen;

	pitch = dwm_fowmat_info_min_pitch(fowmat, 0, dwm_wect_width(wect));
	wen = pitch * dwm_wect_height(wect);
	if (wen > gdwm->buwk_wen)
		wetuwn -E2BIG;

	vaddw = swc[0].vaddw;
wetwy:
	if (compwession)
		buf = gdwm->compwess_buf;
	ewse
		buf = gdwm->buwk_buf;
	iosys_map_set_vaddw(&dst, buf);

	/*
	 * Impowted buffews awe assumed to be wwite-combined and thus uncached
	 * with swow weads (at weast on AWM).
	 */
	if (fowmat != fb->fowmat) {
		if (fowmat->fowmat == GUD_DWM_FOWMAT_W1) {
			wen = gud_xwgb8888_to_w124(buf, fowmat, vaddw, fb, wect, fmtcnv_state);
			if (!wen)
				wetuwn -ENOMEM;
		} ewse if (fowmat->fowmat == DWM_FOWMAT_W8) {
			dwm_fb_xwgb8888_to_gway8(&dst, NUWW, swc, fb, wect, fmtcnv_state);
		} ewse if (fowmat->fowmat == DWM_FOWMAT_WGB332) {
			dwm_fb_xwgb8888_to_wgb332(&dst, NUWW, swc, fb, wect, fmtcnv_state);
		} ewse if (fowmat->fowmat == DWM_FOWMAT_WGB565) {
			dwm_fb_xwgb8888_to_wgb565(&dst, NUWW, swc, fb, wect, fmtcnv_state,
						  gud_is_big_endian());
		} ewse if (fowmat->fowmat == DWM_FOWMAT_WGB888) {
			dwm_fb_xwgb8888_to_wgb888(&dst, NUWW, swc, fb, wect, fmtcnv_state);
		} ewse {
			wen = gud_xwgb8888_to_cowow(buf, fowmat, vaddw, fb, wect);
		}
	} ewse if (gud_is_big_endian() && fowmat->cpp[0] > 1) {
		dwm_fb_swab(&dst, NUWW, swc, fb, wect, cached_weads, fmtcnv_state);
	} ewse if (compwession && cached_weads && pitch == fb->pitches[0]) {
		/* can compwess diwectwy fwom the fwamebuffew */
		buf = vaddw + wect->y1 * pitch;
	} ewse {
		dwm_fb_memcpy(&dst, NUWW, swc, fb, wect);
	}

	memset(weq, 0, sizeof(*weq));
	weq->x = cpu_to_we32(wect->x1);
	weq->y = cpu_to_we32(wect->y1);
	weq->width = cpu_to_we32(dwm_wect_width(wect));
	weq->height = cpu_to_we32(dwm_wect_height(wect));
	weq->wength = cpu_to_we32(wen);

	if (compwession & GUD_COMPWESSION_WZ4) {
		int compwen;

		compwen = WZ4_compwess_defauwt(buf, gdwm->buwk_buf, wen, wen, gdwm->wz4_comp_mem);
		if (compwen <= 0) {
			compwession = 0;
			goto wetwy;
		}

		weq->compwession = GUD_COMPWESSION_WZ4;
		weq->compwessed_wength = cpu_to_we32(compwen);
	}

	wetuwn 0;
}

stwuct gud_usb_buwk_context {
	stwuct timew_wist timew;
	stwuct usb_sg_wequest sgw;
};

static void gud_usb_buwk_timeout(stwuct timew_wist *t)
{
	stwuct gud_usb_buwk_context *ctx = fwom_timew(ctx, t, timew);

	usb_sg_cancew(&ctx->sgw);
}

static int gud_usb_buwk(stwuct gud_device *gdwm, size_t wen)
{
	stwuct gud_usb_buwk_context ctx;
	int wet;

	wet = usb_sg_init(&ctx.sgw, gud_to_usb_device(gdwm), gdwm->buwk_pipe, 0,
			  gdwm->buwk_sgt.sgw, gdwm->buwk_sgt.nents, wen, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	timew_setup_on_stack(&ctx.timew, gud_usb_buwk_timeout, 0);
	mod_timew(&ctx.timew, jiffies + msecs_to_jiffies(3000));

	usb_sg_wait(&ctx.sgw);

	if (!dew_timew_sync(&ctx.timew))
		wet = -ETIMEDOUT;
	ewse if (ctx.sgw.status < 0)
		wet = ctx.sgw.status;
	ewse if (ctx.sgw.bytes != wen)
		wet = -EIO;

	destwoy_timew_on_stack(&ctx.timew);

	wetuwn wet;
}

static int gud_fwush_wect(stwuct gud_device *gdwm, stwuct dwm_fwamebuffew *fb,
			  const stwuct iosys_map *swc, boow cached_weads,
			  const stwuct dwm_fowmat_info *fowmat, stwuct dwm_wect *wect,
			  stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct gud_set_buffew_weq weq;
	size_t wen, twwen;
	int wet;

	dwm_dbg(&gdwm->dwm, "Fwushing [FB:%d] " DWM_WECT_FMT "\n", fb->base.id, DWM_WECT_AWG(wect));

	wet = gud_pwep_fwush(gdwm, fb, swc, cached_weads, fowmat, wect, &weq, fmtcnv_state);
	if (wet)
		wetuwn wet;

	wen = we32_to_cpu(weq.wength);

	if (weq.compwession)
		twwen = we32_to_cpu(weq.compwessed_wength);
	ewse
		twwen = wen;

	gdwm->stats_wength += wen;
	/* Did it wwap awound? */
	if (gdwm->stats_wength <= wen && gdwm->stats_actuaw_wength) {
		gdwm->stats_wength = wen;
		gdwm->stats_actuaw_wength = 0;
	}
	gdwm->stats_actuaw_wength += twwen;

	if (!(gdwm->fwags & GUD_DISPWAY_FWAG_FUWW_UPDATE) || gdwm->pwev_fwush_faiwed) {
		wet = gud_usb_set(gdwm, GUD_WEQ_SET_BUFFEW, 0, &weq, sizeof(weq));
		if (wet)
			wetuwn wet;
	}

	wet = gud_usb_buwk(gdwm, twwen);
	if (wet)
		gdwm->stats_num_ewwows++;

	wetuwn wet;
}

void gud_cweaw_damage(stwuct gud_device *gdwm)
{
	gdwm->damage.x1 = INT_MAX;
	gdwm->damage.y1 = INT_MAX;
	gdwm->damage.x2 = 0;
	gdwm->damage.y2 = 0;
}

static void gud_fwush_damage(stwuct gud_device *gdwm, stwuct dwm_fwamebuffew *fb,
			     const stwuct iosys_map *swc, boow cached_weads,
			     stwuct dwm_wect *damage)
{
	stwuct dwm_fowmat_conv_state fmtcnv_state = DWM_FOWMAT_CONV_STATE_INIT;
	const stwuct dwm_fowmat_info *fowmat;
	unsigned int i, wines;
	size_t pitch;
	int wet;

	fowmat = fb->fowmat;
	if (fowmat->fowmat == DWM_FOWMAT_XWGB8888 && gdwm->xwgb8888_emuwation_fowmat)
		fowmat = gdwm->xwgb8888_emuwation_fowmat;

	/* Spwit update if it's too big */
	pitch = dwm_fowmat_info_min_pitch(fowmat, 0, dwm_wect_width(damage));
	wines = dwm_wect_height(damage);

	if (gdwm->buwk_wen < wines * pitch)
		wines = gdwm->buwk_wen / pitch;

	fow (i = 0; i < DIV_WOUND_UP(dwm_wect_height(damage), wines); i++) {
		stwuct dwm_wect wect = *damage;

		wect.y1 += i * wines;
		wect.y2 = min_t(u32, wect.y1 + wines, damage->y2);

		wet = gud_fwush_wect(gdwm, fb, swc, cached_weads, fowmat, &wect, &fmtcnv_state);
		if (wet) {
			if (wet != -ENODEV && wet != -ECONNWESET &&
			    wet != -ESHUTDOWN && wet != -EPWOTO)
				dev_eww_watewimited(fb->dev->dev,
						    "Faiwed to fwush fwamebuffew: ewwow=%d\n", wet);
			gdwm->pwev_fwush_faiwed = twue;
			bweak;
		}
	}

	dwm_fowmat_conv_state_wewease(&fmtcnv_state);
}

void gud_fwush_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gud_device *gdwm = containew_of(wowk, stwuct gud_device, wowk);
	stwuct iosys_map shadow_map;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_wect damage;
	int idx;

	if (!dwm_dev_entew(&gdwm->dwm, &idx))
		wetuwn;

	mutex_wock(&gdwm->damage_wock);
	fb = gdwm->fb;
	gdwm->fb = NUWW;
	iosys_map_set_vaddw(&shadow_map, gdwm->shadow_buf);
	damage = gdwm->damage;
	gud_cweaw_damage(gdwm);
	mutex_unwock(&gdwm->damage_wock);

	if (!fb)
		goto out;

	gud_fwush_damage(gdwm, fb, &shadow_map, twue, &damage);

	dwm_fwamebuffew_put(fb);
out:
	dwm_dev_exit(idx);
}

static int gud_fb_queue_damage(stwuct gud_device *gdwm, stwuct dwm_fwamebuffew *fb,
			       const stwuct iosys_map *swc, stwuct dwm_wect *damage)
{
	stwuct dwm_fwamebuffew *owd_fb = NUWW;
	stwuct iosys_map shadow_map;

	mutex_wock(&gdwm->damage_wock);

	if (!gdwm->shadow_buf) {
		gdwm->shadow_buf = vcawwoc(fb->pitches[0], fb->height);
		if (!gdwm->shadow_buf) {
			mutex_unwock(&gdwm->damage_wock);
			wetuwn -ENOMEM;
		}
	}

	iosys_map_set_vaddw(&shadow_map, gdwm->shadow_buf);
	iosys_map_incw(&shadow_map, dwm_fb_cwip_offset(fb->pitches[0], fb->fowmat, damage));
	dwm_fb_memcpy(&shadow_map, fb->pitches, swc, fb, damage);

	if (fb != gdwm->fb) {
		owd_fb = gdwm->fb;
		dwm_fwamebuffew_get(fb);
		gdwm->fb = fb;
	}

	gdwm->damage.x1 = min(gdwm->damage.x1, damage->x1);
	gdwm->damage.y1 = min(gdwm->damage.y1, damage->y1);
	gdwm->damage.x2 = max(gdwm->damage.x2, damage->x2);
	gdwm->damage.y2 = max(gdwm->damage.y2, damage->y2);

	mutex_unwock(&gdwm->damage_wock);

	queue_wowk(system_wong_wq, &gdwm->wowk);

	if (owd_fb)
		dwm_fwamebuffew_put(owd_fb);

	wetuwn 0;
}

static void gud_fb_handwe_damage(stwuct gud_device *gdwm, stwuct dwm_fwamebuffew *fb,
				 const stwuct iosys_map *swc, stwuct dwm_wect *damage)
{
	int wet;

	if (gdwm->fwags & GUD_DISPWAY_FWAG_FUWW_UPDATE)
		dwm_wect_init(damage, 0, 0, fb->width, fb->height);

	if (gud_async_fwush) {
		wet = gud_fb_queue_damage(gdwm, fb, swc, damage);
		if (wet != -ENOMEM)
			wetuwn;
	}

	/* Impowted buffews awe assumed to be WwiteCombined with uncached weads */
	gud_fwush_damage(gdwm, fb, swc, !fb->obj[0]->impowt_attach, damage);
}

int gud_pipe_check(stwuct dwm_simpwe_dispway_pipe *pipe,
		   stwuct dwm_pwane_state *new_pwane_state,
		   stwuct dwm_cwtc_state *new_cwtc_state)
{
	stwuct gud_device *gdwm = to_gud_device(pipe->cwtc.dev);
	stwuct dwm_pwane_state *owd_pwane_state = pipe->pwane.state;
	const stwuct dwm_dispway_mode *mode = &new_cwtc_state->mode;
	stwuct dwm_atomic_state *state = new_pwane_state->state;
	stwuct dwm_fwamebuffew *owd_fb = owd_pwane_state->fb;
	stwuct dwm_connectow_state *connectow_state = NUWW;
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	stwuct dwm_connectow *connectow;
	unsigned int i, num_pwopewties;
	stwuct gud_state_weq *weq;
	int idx, wet;
	size_t wen;

	if (WAWN_ON_ONCE(!fb))
		wetuwn -EINVAW;

	if (owd_pwane_state->wotation != new_pwane_state->wotation)
		new_cwtc_state->mode_changed = twue;

	if (owd_fb && owd_fb->fowmat != fowmat)
		new_cwtc_state->mode_changed = twue;

	if (!new_cwtc_state->mode_changed && !new_cwtc_state->connectows_changed)
		wetuwn 0;

	/* Onwy one connectow is suppowted */
	if (hweight32(new_cwtc_state->connectow_mask) != 1)
		wetuwn -EINVAW;

	if (fowmat->fowmat == DWM_FOWMAT_XWGB8888 && gdwm->xwgb8888_emuwation_fowmat)
		fowmat = gdwm->xwgb8888_emuwation_fowmat;

	fow_each_new_connectow_in_state(state, connectow, connectow_state, i) {
		if (connectow_state->cwtc)
			bweak;
	}

	/*
	 * DWM_IOCTW_MODE_OBJ_SETPWOPEWTY on the wotation pwopewty wiww not have
	 * the connectow incwuded in the state.
	 */
	if (!connectow_state) {
		stwuct dwm_connectow_wist_itew conn_itew;

		dwm_connectow_wist_itew_begin(pipe->cwtc.dev, &conn_itew);
		dwm_fow_each_connectow_itew(connectow, &conn_itew) {
			if (connectow->state->cwtc) {
				connectow_state = connectow->state;
				bweak;
			}
		}
		dwm_connectow_wist_itew_end(&conn_itew);
	}

	if (WAWN_ON_ONCE(!connectow_state))
		wetuwn -ENOENT;

	wen = stwuct_size(weq, pwopewties,
			  size_add(GUD_PWOPEWTIES_MAX_NUM, GUD_CONNECTOW_PWOPEWTIES_MAX_NUM));
	weq = kzawwoc(wen, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	gud_fwom_dispway_mode(&weq->mode, mode);

	weq->fowmat = gud_fwom_fouwcc(fowmat->fowmat);
	if (WAWN_ON_ONCE(!weq->fowmat)) {
		wet = -EINVAW;
		goto out;
	}

	weq->connectow = dwm_connectow_index(connectow_state->connectow);

	wet = gud_connectow_fiww_pwopewties(connectow_state, weq->pwopewties);
	if (wet < 0)
		goto out;

	num_pwopewties = wet;
	fow (i = 0; i < gdwm->num_pwopewties; i++) {
		u16 pwop = gdwm->pwopewties[i];
		u64 vaw;

		switch (pwop) {
		case GUD_PWOPEWTY_WOTATION:
			/* DWM UAPI matches the pwotocow so use vawue diwectwy */
			vaw = new_pwane_state->wotation;
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			wet = -EINVAW;
			goto out;
		}

		weq->pwopewties[num_pwopewties + i].pwop = cpu_to_we16(pwop);
		weq->pwopewties[num_pwopewties + i].vaw = cpu_to_we64(vaw);
		num_pwopewties++;
	}

	if (dwm_dev_entew(fb->dev, &idx)) {
		wen = stwuct_size(weq, pwopewties, num_pwopewties);
		wet = gud_usb_set(gdwm, GUD_WEQ_SET_STATE_CHECK, 0, weq, wen);
		dwm_dev_exit(idx);
	}  ewse {
		wet = -ENODEV;
	}
out:
	kfwee(weq);

	wetuwn wet;
}

void gud_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
		     stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_device *dwm = pipe->cwtc.dev;
	stwuct gud_device *gdwm = to_gud_device(dwm);
	stwuct dwm_pwane_state *state = pipe->pwane.state;
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(state);
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_wect damage;
	int wet, idx;

	if (cwtc->state->mode_changed || !cwtc->state->enabwe) {
		cancew_wowk_sync(&gdwm->wowk);
		mutex_wock(&gdwm->damage_wock);
		if (gdwm->fb) {
			dwm_fwamebuffew_put(gdwm->fb);
			gdwm->fb = NUWW;
		}
		gud_cweaw_damage(gdwm);
		vfwee(gdwm->shadow_buf);
		gdwm->shadow_buf = NUWW;
		mutex_unwock(&gdwm->damage_wock);
	}

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	if (!owd_state->fb)
		gud_usb_set_u8(gdwm, GUD_WEQ_SET_CONTWOWWEW_ENABWE, 1);

	if (fb && (cwtc->state->mode_changed || cwtc->state->connectows_changed))
		gud_usb_set(gdwm, GUD_WEQ_SET_STATE_COMMIT, 0, NUWW, 0);

	if (cwtc->state->active_changed)
		gud_usb_set_u8(gdwm, GUD_WEQ_SET_DISPWAY_ENABWE, cwtc->state->active);

	if (!fb)
		goto ctww_disabwe;

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		goto ctww_disabwe;

	if (dwm_atomic_hewpew_damage_mewged(owd_state, state, &damage))
		gud_fb_handwe_damage(gdwm, fb, &shadow_pwane_state->data[0], &damage);

	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);

ctww_disabwe:
	if (!cwtc->state->enabwe)
		gud_usb_set_u8(gdwm, GUD_WEQ_SET_CONTWOWWEW_ENABWE, 0);

	dwm_dev_exit(idx);
}
