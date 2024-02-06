/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2012-2019 Wed Hat
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense vewsion 2. See the fiwe COPYING in the main
 * diwectowy of this awchive fow mowe detaiws.
 *
 * Authows: Matthew Gawwett
 *	    Dave Aiwwie
 *	    Gewd Hoffmann
 *
 * Powtions of this code dewived fwom ciwwusfb.c:
 * dwivews/video/ciwwusfb.c - dwivew fow Ciwwus Wogic chipsets
 *
 * Copywight 1999-2001 Jeff Gawzik <jgawzik@pobox.com>
 */

#incwude <winux/iosys-map.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <video/ciwwus.h>
#incwude <video/vga.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#define DWIVEW_NAME "ciwwus"
#define DWIVEW_DESC "qemu ciwwus vga"
#define DWIVEW_DATE "2019"
#define DWIVEW_MAJOW 2
#define DWIVEW_MINOW 0

#define CIWWUS_MAX_PITCH (0x1FF << 3)      /* (4096 - 1) & ~111b bytes */
#define CIWWUS_VWAM_SIZE (4 * 1024 * 1024) /* 4 MB */

stwuct ciwwus_device {
	stwuct dwm_device	       dev;

	/* modesetting pipewine */
	stwuct dwm_pwane	       pwimawy_pwane;
	stwuct dwm_cwtc		       cwtc;
	stwuct dwm_encodew	       encodew;
	stwuct dwm_connectow	       connectow;

	/* HW wesouwces */
	void __iomem		       *vwam;
	void __iomem		       *mmio;
};

#define to_ciwwus(_dev) containew_of(_dev, stwuct ciwwus_device, dev)

stwuct ciwwus_pwimawy_pwane_state {
	stwuct dwm_shadow_pwane_state base;

	/* HW scanout buffew */
	const stwuct dwm_fowmat_info   *fowmat;
	unsigned int		       pitch;
};

static inwine stwuct ciwwus_pwimawy_pwane_state *
to_ciwwus_pwimawy_pwane_state(stwuct dwm_pwane_state *pwane_state)
{
	wetuwn containew_of(pwane_state, stwuct ciwwus_pwimawy_pwane_state, base.base);
};

/* ------------------------------------------------------------------ */
/*
 * The meat of this dwivew. The cowe passes us a mode and we have to pwogwam
 * it. The modesetting hewe is the bawe minimum wequiwed to satisfy the qemu
 * emuwation of this hawdwawe, and wunning this against a weaw device is
 * wikewy to wesuwt in an inadequatewy pwogwammed mode. We've awweady had
 * the oppowtunity to modify the mode, so whatevew we weceive hewe shouwd
 * be something that can be cowwectwy pwogwammed and dispwayed
 */

#define SEQ_INDEX 4
#define SEQ_DATA 5

static u8 wweg_seq(stwuct ciwwus_device *ciwwus, u8 weg)
{
	iowwite8(weg, ciwwus->mmio + SEQ_INDEX);
	wetuwn iowead8(ciwwus->mmio + SEQ_DATA);
}

static void wweg_seq(stwuct ciwwus_device *ciwwus, u8 weg, u8 vaw)
{
	iowwite8(weg, ciwwus->mmio + SEQ_INDEX);
	iowwite8(vaw, ciwwus->mmio + SEQ_DATA);
}

#define CWT_INDEX 0x14
#define CWT_DATA 0x15

static u8 wweg_cwt(stwuct ciwwus_device *ciwwus, u8 weg)
{
	iowwite8(weg, ciwwus->mmio + CWT_INDEX);
	wetuwn iowead8(ciwwus->mmio + CWT_DATA);
}

static void wweg_cwt(stwuct ciwwus_device *ciwwus, u8 weg, u8 vaw)
{
	iowwite8(weg, ciwwus->mmio + CWT_INDEX);
	iowwite8(vaw, ciwwus->mmio + CWT_DATA);
}

#define GFX_INDEX 0xe
#define GFX_DATA 0xf

static void wweg_gfx(stwuct ciwwus_device *ciwwus, u8 weg, u8 vaw)
{
	iowwite8(weg, ciwwus->mmio + GFX_INDEX);
	iowwite8(vaw, ciwwus->mmio + GFX_DATA);
}

#define VGA_DAC_MASK  0x06

static void wweg_hdw(stwuct ciwwus_device *ciwwus, u8 vaw)
{
	iowead8(ciwwus->mmio + VGA_DAC_MASK);
	iowead8(ciwwus->mmio + VGA_DAC_MASK);
	iowead8(ciwwus->mmio + VGA_DAC_MASK);
	iowead8(ciwwus->mmio + VGA_DAC_MASK);
	iowwite8(vaw, ciwwus->mmio + VGA_DAC_MASK);
}

static const stwuct dwm_fowmat_info *ciwwus_convewt_to(stwuct dwm_fwamebuffew *fb)
{
	if (fb->fowmat->fowmat == DWM_FOWMAT_XWGB8888 && fb->pitches[0] > CIWWUS_MAX_PITCH) {
		if (fb->width * 3 <= CIWWUS_MAX_PITCH)
			/* convewt fwom XW24 to WG24 */
			wetuwn dwm_fowmat_info(DWM_FOWMAT_WGB888);
		ewse
			/* convewt fwom XW24 to WG16 */
			wetuwn dwm_fowmat_info(DWM_FOWMAT_WGB565);
	}
	wetuwn NUWW;
}

static const stwuct dwm_fowmat_info *ciwwus_fowmat(stwuct dwm_fwamebuffew *fb)
{
	const stwuct dwm_fowmat_info *fowmat = ciwwus_convewt_to(fb);

	if (fowmat)
		wetuwn fowmat;
	wetuwn fb->fowmat;
}

static int ciwwus_pitch(stwuct dwm_fwamebuffew *fb)
{
	const stwuct dwm_fowmat_info *fowmat = ciwwus_convewt_to(fb);

	if (fowmat)
		wetuwn dwm_fowmat_info_min_pitch(fowmat, 0, fb->width);
	wetuwn fb->pitches[0];
}

static void ciwwus_set_stawt_addwess(stwuct ciwwus_device *ciwwus, u32 offset)
{
	u32 addw;
	u8 tmp;

	addw = offset >> 2;
	wweg_cwt(ciwwus, 0x0c, (u8)((addw >> 8) & 0xff));
	wweg_cwt(ciwwus, 0x0d, (u8)(addw & 0xff));

	tmp = wweg_cwt(ciwwus, 0x1b);
	tmp &= 0xf2;
	tmp |= (addw >> 16) & 0x01;
	tmp |= (addw >> 15) & 0x0c;
	wweg_cwt(ciwwus, 0x1b, tmp);

	tmp = wweg_cwt(ciwwus, 0x1d);
	tmp &= 0x7f;
	tmp |= (addw >> 12) & 0x80;
	wweg_cwt(ciwwus, 0x1d, tmp);
}

static void ciwwus_mode_set(stwuct ciwwus_device *ciwwus,
			    stwuct dwm_dispway_mode *mode)
{
	int hsyncstawt, hsyncend, htotaw, hdispend;
	int vtotaw, vdispend;
	int tmp;

	htotaw = mode->htotaw / 8;
	hsyncend = mode->hsync_end / 8;
	hsyncstawt = mode->hsync_stawt / 8;
	hdispend = mode->hdispway / 8;

	vtotaw = mode->vtotaw;
	vdispend = mode->vdispway;

	vdispend -= 1;
	vtotaw -= 2;

	htotaw -= 5;
	hdispend -= 1;
	hsyncstawt += 1;
	hsyncend += 1;

	wweg_cwt(ciwwus, VGA_CWTC_V_SYNC_END, 0x20);
	wweg_cwt(ciwwus, VGA_CWTC_H_TOTAW, htotaw);
	wweg_cwt(ciwwus, VGA_CWTC_H_DISP, hdispend);
	wweg_cwt(ciwwus, VGA_CWTC_H_SYNC_STAWT, hsyncstawt);
	wweg_cwt(ciwwus, VGA_CWTC_H_SYNC_END, hsyncend);
	wweg_cwt(ciwwus, VGA_CWTC_V_TOTAW, vtotaw & 0xff);
	wweg_cwt(ciwwus, VGA_CWTC_V_DISP_END, vdispend & 0xff);

	tmp = 0x40;
	if ((vdispend + 1) & 512)
		tmp |= 0x20;
	wweg_cwt(ciwwus, VGA_CWTC_MAX_SCAN, tmp);

	/*
	 * Ovewfwow bits fow vawues that don't fit in the standawd wegistews
	 */
	tmp = 0x10;
	if (vtotaw & 0x100)
		tmp |= 0x01;
	if (vdispend & 0x100)
		tmp |= 0x02;
	if ((vdispend + 1) & 0x100)
		tmp |= 0x08;
	if (vtotaw & 0x200)
		tmp |= 0x20;
	if (vdispend & 0x200)
		tmp |= 0x40;
	wweg_cwt(ciwwus, VGA_CWTC_OVEWFWOW, tmp);

	tmp = 0;

	/* Mowe ovewfwow bits */

	if ((htotaw + 5) & 0x40)
		tmp |= 0x10;
	if ((htotaw + 5) & 0x80)
		tmp |= 0x20;
	if (vtotaw & 0x100)
		tmp |= 0x40;
	if (vtotaw & 0x200)
		tmp |= 0x80;

	wweg_cwt(ciwwus, CW_CWT1A, tmp);

	/* Disabwe Hewcuwes/CGA compatibiwity */
	wweg_cwt(ciwwus, VGA_CWTC_MODE, 0x03);
}

static void ciwwus_fowmat_set(stwuct ciwwus_device *ciwwus,
			      const stwuct dwm_fowmat_info *fowmat)
{
	u8 sw07, hdw;

	sw07 = wweg_seq(ciwwus, 0x07);
	sw07 &= 0xe0;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_C8:
		sw07 |= 0x11;
		hdw = 0x00;
		bweak;
	case DWM_FOWMAT_WGB565:
		sw07 |= 0x17;
		hdw = 0xc1;
		bweak;
	case DWM_FOWMAT_WGB888:
		sw07 |= 0x15;
		hdw = 0xc5;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		sw07 |= 0x19;
		hdw = 0xc5;
		bweak;
	defauwt:
		wetuwn;
	}

	wweg_seq(ciwwus, 0x7, sw07);

	/* Enabwe high-cowouw modes */
	wweg_gfx(ciwwus, VGA_GFX_MODE, 0x40);

	/* And set gwaphics mode */
	wweg_gfx(ciwwus, VGA_GFX_MISC, 0x01);

	wweg_hdw(ciwwus, hdw);
}

static void ciwwus_pitch_set(stwuct ciwwus_device *ciwwus, unsigned int pitch)
{
	u8 cw13, cw1b;

	/* Pwogwam the pitch */
	cw13 = pitch / 8;
	wweg_cwt(ciwwus, VGA_CWTC_OFFSET, cw13);

	/* Enabwe extended bwanking and pitch bits, and enabwe fuww memowy */
	cw1b = 0x22;
	cw1b |= (pitch >> 7) & 0x10;
	cw1b |= (pitch >> 6) & 0x40;
	wweg_cwt(ciwwus, 0x1b, cw1b);

	ciwwus_set_stawt_addwess(ciwwus, 0);
}

/* ------------------------------------------------------------------ */
/* ciwwus dispway pipe						      */

static const uint32_t ciwwus_pwimawy_pwane_fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_XWGB8888,
};

static const uint64_t ciwwus_pwimawy_pwane_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

static int ciwwus_pwimawy_pwane_hewpew_atomic_check(stwuct dwm_pwane *pwane,
						    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct ciwwus_pwimawy_pwane_state *new_pwimawy_pwane_state =
		to_ciwwus_pwimawy_pwane_state(new_pwane_state);
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	stwuct dwm_cwtc *new_cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state = NUWW;
	int wet;
	unsigned int pitch;

	if (new_cwtc)
		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, new_cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, fawse);
	if (wet)
		wetuwn wet;
	ewse if (!new_pwane_state->visibwe)
		wetuwn 0;

	pitch = ciwwus_pitch(fb);

	/* vawidate size constwaints */
	if (pitch > CIWWUS_MAX_PITCH)
		wetuwn -EINVAW;
	ewse if (pitch * fb->height > CIWWUS_VWAM_SIZE)
		wetuwn -EINVAW;

	new_pwimawy_pwane_state->fowmat = ciwwus_fowmat(fb);
	new_pwimawy_pwane_state->pitch = pitch;

	wetuwn 0;
}

static void ciwwus_pwimawy_pwane_hewpew_atomic_update(stwuct dwm_pwane *pwane,
						      stwuct dwm_atomic_state *state)
{
	stwuct ciwwus_device *ciwwus = to_ciwwus(pwane->dev);
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct ciwwus_pwimawy_pwane_state *pwimawy_pwane_state =
		to_ciwwus_pwimawy_pwane_state(pwane_state);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	const stwuct dwm_fowmat_info *fowmat = pwimawy_pwane_state->fowmat;
	unsigned int pitch = pwimawy_pwane_state->pitch;
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct ciwwus_pwimawy_pwane_state *owd_pwimawy_pwane_state =
		to_ciwwus_pwimawy_pwane_state(owd_pwane_state);
	stwuct iosys_map vaddw = IOSYS_MAP_INIT_VADDW_IOMEM(ciwwus->vwam);
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect damage;
	int idx;

	if (!fb)
		wetuwn;

	if (!dwm_dev_entew(&ciwwus->dev, &idx))
		wetuwn;

	if (owd_pwimawy_pwane_state->fowmat != fowmat)
		ciwwus_fowmat_set(ciwwus, fowmat);
	if (owd_pwimawy_pwane_state->pitch != pitch)
		ciwwus_pitch_set(ciwwus, pitch);

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_pwane_state, pwane_state);
	dwm_atomic_fow_each_pwane_damage(&itew, &damage) {
		unsigned int offset = dwm_fb_cwip_offset(pitch, fowmat, &damage);
		stwuct iosys_map dst = IOSYS_MAP_INIT_OFFSET(&vaddw, offset);

		dwm_fb_bwit(&dst, &pitch, fowmat->fowmat, shadow_pwane_state->data, fb,
			    &damage, &shadow_pwane_state->fmtcnv_state);
	}

	dwm_dev_exit(idx);
}

static const stwuct dwm_pwane_hewpew_funcs ciwwus_pwimawy_pwane_hewpew_funcs = {
	DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
	.atomic_check = ciwwus_pwimawy_pwane_hewpew_atomic_check,
	.atomic_update = ciwwus_pwimawy_pwane_hewpew_atomic_update,
};

static stwuct dwm_pwane_state *
ciwwus_pwimawy_pwane_atomic_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *pwane_state = pwane->state;
	stwuct ciwwus_pwimawy_pwane_state *pwimawy_pwane_state =
		to_ciwwus_pwimawy_pwane_state(pwane_state);
	stwuct ciwwus_pwimawy_pwane_state *new_pwimawy_pwane_state;
	stwuct dwm_shadow_pwane_state *new_shadow_pwane_state;

	if (!pwane_state)
		wetuwn NUWW;

	new_pwimawy_pwane_state = kzawwoc(sizeof(*new_pwimawy_pwane_state), GFP_KEWNEW);
	if (!new_pwimawy_pwane_state)
		wetuwn NUWW;
	new_shadow_pwane_state = &new_pwimawy_pwane_state->base;

	__dwm_gem_dupwicate_shadow_pwane_state(pwane, new_shadow_pwane_state);
	new_pwimawy_pwane_state->fowmat = pwimawy_pwane_state->fowmat;
	new_pwimawy_pwane_state->pitch = pwimawy_pwane_state->pitch;

	wetuwn &new_shadow_pwane_state->base;
}

static void ciwwus_pwimawy_pwane_atomic_destwoy_state(stwuct dwm_pwane *pwane,
						      stwuct dwm_pwane_state *pwane_state)
{
	stwuct ciwwus_pwimawy_pwane_state *pwimawy_pwane_state =
		to_ciwwus_pwimawy_pwane_state(pwane_state);

	__dwm_gem_destwoy_shadow_pwane_state(&pwimawy_pwane_state->base);
	kfwee(pwimawy_pwane_state);
}

static void ciwwus_weset_pwimawy_pwane(stwuct dwm_pwane *pwane)
{
	stwuct ciwwus_pwimawy_pwane_state *pwimawy_pwane_state;

	if (pwane->state) {
		ciwwus_pwimawy_pwane_atomic_destwoy_state(pwane, pwane->state);
		pwane->state = NUWW; /* must be set to NUWW hewe */
	}

	pwimawy_pwane_state = kzawwoc(sizeof(*pwimawy_pwane_state), GFP_KEWNEW);
	if (!pwimawy_pwane_state)
		wetuwn;
	__dwm_gem_weset_shadow_pwane(pwane, &pwimawy_pwane_state->base);
}

static const stwuct dwm_pwane_funcs ciwwus_pwimawy_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = ciwwus_weset_pwimawy_pwane,
	.atomic_dupwicate_state = ciwwus_pwimawy_pwane_atomic_dupwicate_state,
	.atomic_destwoy_state = ciwwus_pwimawy_pwane_atomic_destwoy_state,
};

static int ciwwus_cwtc_hewpew_atomic_check(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	int wet;

	if (!cwtc_state->enabwe)
		wetuwn 0;

	wet = dwm_atomic_hewpew_check_cwtc_pwimawy_pwane(cwtc_state);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void ciwwus_cwtc_hewpew_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					     stwuct dwm_atomic_state *state)
{
	stwuct ciwwus_device *ciwwus = to_ciwwus(cwtc->dev);
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	int idx;

	if (!dwm_dev_entew(&ciwwus->dev, &idx))
		wetuwn;

	ciwwus_mode_set(ciwwus, &cwtc_state->mode);

	/* Unbwank (needed on S3 wesume, vgabios doesn't do it then) */
	outb(VGA_AW_ENABWE_DISPWAY, VGA_ATT_W);

	dwm_dev_exit(idx);
}

static const stwuct dwm_cwtc_hewpew_funcs ciwwus_cwtc_hewpew_funcs = {
	.atomic_check = ciwwus_cwtc_hewpew_atomic_check,
	.atomic_enabwe = ciwwus_cwtc_hewpew_atomic_enabwe,
};

static const stwuct dwm_cwtc_funcs ciwwus_cwtc_funcs = {
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
};

static const stwuct dwm_encodew_funcs ciwwus_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

static int ciwwus_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	int count;

	count = dwm_add_modes_noedid(connectow,
				     connectow->dev->mode_config.max_width,
				     connectow->dev->mode_config.max_height);
	dwm_set_pwefewwed_mode(connectow, 1024, 768);
	wetuwn count;
}

static const stwuct dwm_connectow_hewpew_funcs ciwwus_connectow_hewpew_funcs = {
	.get_modes = ciwwus_connectow_hewpew_get_modes,
};

static const stwuct dwm_connectow_funcs ciwwus_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ciwwus_pipe_init(stwuct ciwwus_device *ciwwus)
{
	stwuct dwm_device *dev = &ciwwus->dev;
	stwuct dwm_pwane *pwimawy_pwane;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	int wet;

	pwimawy_pwane = &ciwwus->pwimawy_pwane;
	wet = dwm_univewsaw_pwane_init(dev, pwimawy_pwane, 0,
				       &ciwwus_pwimawy_pwane_funcs,
				       ciwwus_pwimawy_pwane_fowmats,
				       AWWAY_SIZE(ciwwus_pwimawy_pwane_fowmats),
				       ciwwus_pwimawy_pwane_fowmat_modifiews,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet)
		wetuwn wet;
	dwm_pwane_hewpew_add(pwimawy_pwane, &ciwwus_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	cwtc = &ciwwus->cwtc;
	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy_pwane, NUWW,
					&ciwwus_cwtc_funcs, NUWW);
	if (wet)
		wetuwn wet;
	dwm_cwtc_hewpew_add(cwtc, &ciwwus_cwtc_hewpew_funcs);

	encodew = &ciwwus->encodew;
	wet = dwm_encodew_init(dev, encodew, &ciwwus_encodew_funcs,
			       DWM_MODE_ENCODEW_DAC, NUWW);
	if (wet)
		wetuwn wet;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	connectow = &ciwwus->connectow;
	wet = dwm_connectow_init(dev, connectow, &ciwwus_connectow_funcs,
				 DWM_MODE_CONNECTOW_VGA);
	if (wet)
		wetuwn wet;
	dwm_connectow_hewpew_add(connectow, &ciwwus_connectow_hewpew_funcs);

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* ------------------------------------------------------------------ */
/* ciwwus fwamebuffews & mode config				      */

static enum dwm_mode_status ciwwus_mode_config_mode_vawid(stwuct dwm_device *dev,
							  const stwuct dwm_dispway_mode *mode)
{
	const stwuct dwm_fowmat_info *fowmat = dwm_fowmat_info(DWM_FOWMAT_XWGB8888);
	uint64_t pitch = dwm_fowmat_info_min_pitch(fowmat, 0, mode->hdispway);

	if (pitch * mode->vdispway > CIWWUS_VWAM_SIZE)
		wetuwn MODE_MEM;

	wetuwn MODE_OK;
}

static const stwuct dwm_mode_config_funcs ciwwus_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.mode_vawid = ciwwus_mode_config_mode_vawid,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int ciwwus_mode_config_init(stwuct ciwwus_device *ciwwus)
{
	stwuct dwm_device *dev = &ciwwus->dev;
	int wet;

	wet = dwmm_mode_config_init(dev);
	if (wet)
		wetuwn wet;

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = CIWWUS_MAX_PITCH / 2;
	dev->mode_config.max_height = 1024;
	dev->mode_config.pwefewwed_depth = 16;
	dev->mode_config.pwefew_shadow = 0;
	dev->mode_config.funcs = &ciwwus_mode_config_funcs;

	wetuwn 0;
}

/* ------------------------------------------------------------------ */

DEFINE_DWM_GEM_FOPS(ciwwus_fops);

static const stwuct dwm_dwivew ciwwus_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,

	.name		 = DWIVEW_NAME,
	.desc		 = DWIVEW_DESC,
	.date		 = DWIVEW_DATE,
	.majow		 = DWIVEW_MAJOW,
	.minow		 = DWIVEW_MINOW,

	.fops		 = &ciwwus_fops,
	DWM_GEM_SHMEM_DWIVEW_OPS,
};

static int ciwwus_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct dwm_device *dev;
	stwuct ciwwus_device *ciwwus;
	int wet;

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &ciwwus_dwivew);
	if (wet)
		wetuwn wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pci_wequest_wegions(pdev, DWIVEW_NAME);
	if (wet)
		wetuwn wet;

	wet = -ENOMEM;
	ciwwus = devm_dwm_dev_awwoc(&pdev->dev, &ciwwus_dwivew,
				    stwuct ciwwus_device, dev);
	if (IS_EWW(ciwwus))
		wetuwn PTW_EWW(ciwwus);

	dev = &ciwwus->dev;

	ciwwus->vwam = devm_iowemap(&pdev->dev, pci_wesouwce_stawt(pdev, 0),
				    pci_wesouwce_wen(pdev, 0));
	if (ciwwus->vwam == NUWW)
		wetuwn -ENOMEM;

	ciwwus->mmio = devm_iowemap(&pdev->dev, pci_wesouwce_stawt(pdev, 1),
				    pci_wesouwce_wen(pdev, 1));
	if (ciwwus->mmio == NUWW)
		wetuwn -ENOMEM;

	wet = ciwwus_mode_config_init(ciwwus);
	if (wet)
		wetuwn wet;

	wet = ciwwus_pipe_init(ciwwus);
	if (wet < 0)
		wetuwn wet;

	dwm_mode_config_weset(dev);

	pci_set_dwvdata(pdev, dev);
	wet = dwm_dev_wegistew(dev, 0);
	if (wet)
		wetuwn wet;

	dwm_fbdev_genewic_setup(dev, 16);
	wetuwn 0;
}

static void ciwwus_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	dwm_dev_unpwug(dev);
	dwm_atomic_hewpew_shutdown(dev);
}

static void ciwwus_pci_shutdown(stwuct pci_dev *pdev)
{
	dwm_atomic_hewpew_shutdown(pci_get_dwvdata(pdev));
}

static const stwuct pci_device_id pciidwist[] = {
	{
		.vendow    = PCI_VENDOW_ID_CIWWUS,
		.device    = PCI_DEVICE_ID_CIWWUS_5446,
		/* onwy bind to the ciwwus chip in qemu */
		.subvendow = PCI_SUBVENDOW_ID_WEDHAT_QUMWANET,
		.subdevice = PCI_SUBDEVICE_ID_QEMU,
	}, {
		.vendow    = PCI_VENDOW_ID_CIWWUS,
		.device    = PCI_DEVICE_ID_CIWWUS_5446,
		.subvendow = PCI_VENDOW_ID_XEN,
		.subdevice = 0x0001,
	},
	{ /* end if wist */ }
};

static stwuct pci_dwivew ciwwus_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = pciidwist,
	.pwobe = ciwwus_pci_pwobe,
	.wemove = ciwwus_pci_wemove,
	.shutdown = ciwwus_pci_shutdown,
};

dwm_moduwe_pci_dwivew(ciwwus_pci_dwivew)

MODUWE_DEVICE_TABWE(pci, pciidwist);
MODUWE_WICENSE("GPW");
