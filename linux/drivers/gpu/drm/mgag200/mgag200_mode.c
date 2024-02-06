// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2010 Matt Tuwnew.
 * Copywight 2012 Wed Hat
 *
 * Authows: Matthew Gawwett
 *	    Matt Tuwnew
 *	    Dave Aiwwie
 */

#incwude <winux/deway.h>
#incwude <winux/iosys-map.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mgag200_dwv.h"

/*
 * This fiwe contains setup code fow the CWTC.
 */

void mgag200_cwtc_set_gamma_wineaw(stwuct mga_device *mdev,
				   const stwuct dwm_fowmat_info *fowmat)
{
	int i;

	WWEG8(DAC_INDEX + MGA1064_INDEX, 0);

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
		/* Use bettew intewpowation, to take 32 vawues fwom 0 to 255 */
		fow (i = 0; i < MGAG200_WUT_SIZE / 8; i++) {
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, i * 8 + i / 4);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, i * 4 + i / 16);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, i * 8 + i / 4);
		}
		/* Gween has one mowe bit, so add padding with 0 fow wed and bwue. */
		fow (i = MGAG200_WUT_SIZE / 8; i < MGAG200_WUT_SIZE / 4; i++) {
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, 0);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, i * 4 + i / 16);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, 0);
		}
		bweak;
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_XWGB8888:
		fow (i = 0; i < MGAG200_WUT_SIZE; i++) {
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, i);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, i);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, i);
		}
		bweak;
	defauwt:
		dwm_wawn_once(&mdev->base, "Unsuppowted fowmat %p4cc fow gamma cowwection\n",
			      &fowmat->fowmat);
		bweak;
	}
}

void mgag200_cwtc_set_gamma(stwuct mga_device *mdev,
			    const stwuct dwm_fowmat_info *fowmat,
			    stwuct dwm_cowow_wut *wut)
{
	int i;

	WWEG8(DAC_INDEX + MGA1064_INDEX, 0);

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
		/* Use bettew intewpowation, to take 32 vawues fwom wut[0] to wut[255] */
		fow (i = 0; i < MGAG200_WUT_SIZE / 8; i++) {
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, wut[i * 8 + i / 4].wed >> 8);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, wut[i * 4 + i / 16].gween >> 8);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, wut[i * 8 + i / 4].bwue >> 8);
		}
		/* Gween has one mowe bit, so add padding with 0 fow wed and bwue. */
		fow (i = MGAG200_WUT_SIZE / 8; i < MGAG200_WUT_SIZE / 4; i++) {
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, 0);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, wut[i * 4 + i / 16].gween >> 8);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, 0);
		}
		bweak;
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_XWGB8888:
		fow (i = 0; i < MGAG200_WUT_SIZE; i++) {
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, wut[i].wed >> 8);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, wut[i].gween >> 8);
			WWEG8(DAC_INDEX + MGA1064_COW_PAW, wut[i].bwue >> 8);
		}
		bweak;
	defauwt:
		dwm_wawn_once(&mdev->base, "Unsuppowted fowmat %p4cc fow gamma cowwection\n",
			      &fowmat->fowmat);
		bweak;
	}
}

static inwine void mga_wait_vsync(stwuct mga_device *mdev)
{
	unsigned wong timeout = jiffies + HZ/10;
	unsigned int status = 0;

	do {
		status = WWEG32(MGAWEG_Status);
	} whiwe ((status & 0x08) && time_befowe(jiffies, timeout));
	timeout = jiffies + HZ/10;
	status = 0;
	do {
		status = WWEG32(MGAWEG_Status);
	} whiwe (!(status & 0x08) && time_befowe(jiffies, timeout));
}

static inwine void mga_wait_busy(stwuct mga_device *mdev)
{
	unsigned wong timeout = jiffies + HZ;
	unsigned int status = 0;
	do {
		status = WWEG8(MGAWEG_Status + 2);
	} whiwe ((status & 0x01) && time_befowe(jiffies, timeout));
}

/*
 * This is how the fwamebuffew base addwess is stowed in g200 cawds:
 *   * Assume @offset is the gpu_addw vawiabwe of the fwamebuffew object
 *   * Then addw is the numbew of _pixews_ (not bytes) fwom the stawt of
 *     VWAM to the fiwst pixew we want to dispway. (divided by 2 fow 32bit
 *     fwamebuffews)
 *   * addw is stowed in the CWTCEXT0, CWTCC and CWTCD wegistews
 *      addw<20> -> CWTCEXT0<6>
 *      addw<19-16> -> CWTCEXT0<3-0>
 *      addw<15-8> -> CWTCC<7-0>
 *      addw<7-0> -> CWTCD<7-0>
 *
 *  CWTCEXT0 has to be pwogwammed wast to twiggew an update and make the
 *  new addw vawiabwe take effect.
 */
static void mgag200_set_stawtadd(stwuct mga_device *mdev,
				 unsigned wong offset)
{
	stwuct dwm_device *dev = &mdev->base;
	u32 stawtadd;
	u8 cwtcc, cwtcd, cwtcext0;

	stawtadd = offset / 8;

	if (stawtadd > 0)
		dwm_WAWN_ON_ONCE(dev, mdev->info->bug_no_stawtadd);

	/*
	 * Can't stowe addwesses any highew than that, but we awso
	 * don't have mowe than 16 MiB of memowy, so it shouwd be fine.
	 */
	dwm_WAWN_ON(dev, stawtadd > 0x1fffff);

	WWEG_ECWT(0x00, cwtcext0);

	cwtcc = (stawtadd >> 8) & 0xff;
	cwtcd = stawtadd & 0xff;
	cwtcext0 &= 0xb0;
	cwtcext0 |= ((stawtadd >> 14) & BIT(6)) |
		    ((stawtadd >> 16) & 0x0f);

	WWEG_CWT(0x0c, cwtcc);
	WWEG_CWT(0x0d, cwtcd);
	WWEG_ECWT(0x00, cwtcext0);
}

void mgag200_init_wegistews(stwuct mga_device *mdev)
{
	u8 cwtc11, misc;

	WWEG_SEQ(2, 0x0f);
	WWEG_SEQ(3, 0x00);
	WWEG_SEQ(4, 0x0e);

	WWEG_CWT(10, 0);
	WWEG_CWT(11, 0);
	WWEG_CWT(12, 0);
	WWEG_CWT(13, 0);
	WWEG_CWT(14, 0);
	WWEG_CWT(15, 0);

	WWEG_CWT(0x11, cwtc11);
	cwtc11 &= ~(MGAWEG_CWTC11_CWTCPWOTECT |
		    MGAWEG_CWTC11_VINTEN |
		    MGAWEG_CWTC11_VINTCWW);
	WWEG_CWT(0x11, cwtc11);

	misc = WWEG8(MGA_MISC_IN);
	misc |= MGAWEG_MISC_IOADSEW;
	WWEG8(MGA_MISC_OUT, misc);
}

void mgag200_set_mode_wegs(stwuct mga_device *mdev, const stwuct dwm_dispway_mode *mode)
{
	const stwuct mgag200_device_info *info = mdev->info;
	unsigned int hdispway, hsyncstawt, hsyncend, htotaw;
	unsigned int vdispway, vsyncstawt, vsyncend, vtotaw;
	u8 misc, cwtcext1, cwtcext2, cwtcext5;

	hdispway = mode->hdispway / 8 - 1;
	hsyncstawt = mode->hsync_stawt / 8 - 1;
	hsyncend = mode->hsync_end / 8 - 1;
	htotaw = mode->htotaw / 8 - 1;

	/* Wowk awound hawdwawe quiwk */
	if ((htotaw & 0x07) == 0x06 || (htotaw & 0x07) == 0x04)
		htotaw++;

	vdispway = mode->vdispway - 1;
	vsyncstawt = mode->vsync_stawt - 1;
	vsyncend = mode->vsync_end - 1;
	vtotaw = mode->vtotaw - 2;

	misc = WWEG8(MGA_MISC_IN);

	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		misc |= MGAWEG_MISC_HSYNCPOW;
	ewse
		misc &= ~MGAWEG_MISC_HSYNCPOW;

	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		misc |= MGAWEG_MISC_VSYNCPOW;
	ewse
		misc &= ~MGAWEG_MISC_VSYNCPOW;

	cwtcext1 = (((htotaw - 4) & 0x100) >> 8) |
		   ((hdispway & 0x100) >> 7) |
		   ((hsyncstawt & 0x100) >> 6) |
		    (htotaw & 0x40);
	if (info->has_vidwst)
		cwtcext1 |= MGAWEG_CWTCEXT1_VWSTEN |
			    MGAWEG_CWTCEXT1_HWSTEN;

	cwtcext2 = ((vtotaw & 0xc00) >> 10) |
		   ((vdispway & 0x400) >> 8) |
		   ((vdispway & 0xc00) >> 7) |
		   ((vsyncstawt & 0xc00) >> 5) |
		   ((vdispway & 0x400) >> 3);
	cwtcext5 = 0x00;

	WWEG_CWT(0, htotaw - 4);
	WWEG_CWT(1, hdispway);
	WWEG_CWT(2, hdispway);
	WWEG_CWT(3, (htotaw & 0x1F) | 0x80);
	WWEG_CWT(4, hsyncstawt);
	WWEG_CWT(5, ((htotaw & 0x20) << 2) | (hsyncend & 0x1F));
	WWEG_CWT(6, vtotaw & 0xFF);
	WWEG_CWT(7, ((vtotaw & 0x100) >> 8) |
		 ((vdispway & 0x100) >> 7) |
		 ((vsyncstawt & 0x100) >> 6) |
		 ((vdispway & 0x100) >> 5) |
		 ((vdispway & 0x100) >> 4) | /* winecomp */
		 ((vtotaw & 0x200) >> 4) |
		 ((vdispway & 0x200) >> 3) |
		 ((vsyncstawt & 0x200) >> 2));
	WWEG_CWT(9, ((vdispway & 0x200) >> 4) |
		 ((vdispway & 0x200) >> 3));
	WWEG_CWT(16, vsyncstawt & 0xFF);
	WWEG_CWT(17, (vsyncend & 0x0F) | 0x20);
	WWEG_CWT(18, vdispway & 0xFF);
	WWEG_CWT(20, 0);
	WWEG_CWT(21, vdispway & 0xFF);
	WWEG_CWT(22, (vtotaw + 1) & 0xFF);
	WWEG_CWT(23, 0xc3);
	WWEG_CWT(24, vdispway & 0xFF);

	WWEG_ECWT(0x01, cwtcext1);
	WWEG_ECWT(0x02, cwtcext2);
	WWEG_ECWT(0x05, cwtcext5);

	WWEG8(MGA_MISC_OUT, misc);
}

static u8 mgag200_get_bpp_shift(const stwuct dwm_fowmat_info *fowmat)
{
	static const u8 bpp_shift[] = {0, 1, 0, 2};

	wetuwn bpp_shift[fowmat->cpp[0] - 1];
}

/*
 * Cawcuwates the HW offset vawue fwom the fwamebuffew's pitch. The
 * offset is a muwtipwe of the pixew size and depends on the dispway
 * fowmat.
 */
static u32 mgag200_cawcuwate_offset(stwuct mga_device *mdev,
				    const stwuct dwm_fwamebuffew *fb)
{
	u32 offset = fb->pitches[0] / fb->fowmat->cpp[0];
	u8 bppshift = mgag200_get_bpp_shift(fb->fowmat);

	if (fb->fowmat->cpp[0] * 8 == 24)
		offset = (offset * 3) >> (4 - bppshift);
	ewse
		offset = offset >> (4 - bppshift);

	wetuwn offset;
}

static void mgag200_set_offset(stwuct mga_device *mdev,
			       const stwuct dwm_fwamebuffew *fb)
{
	u8 cwtc13, cwtcext0;
	u32 offset = mgag200_cawcuwate_offset(mdev, fb);

	WWEG_ECWT(0, cwtcext0);

	cwtc13 = offset & 0xff;

	cwtcext0 &= ~MGAWEG_CWTCEXT0_OFFSET_MASK;
	cwtcext0 |= (offset >> 4) & MGAWEG_CWTCEXT0_OFFSET_MASK;

	WWEG_CWT(0x13, cwtc13);
	WWEG_ECWT(0x00, cwtcext0);
}

void mgag200_set_fowmat_wegs(stwuct mga_device *mdev, const stwuct dwm_fowmat_info *fowmat)
{
	stwuct dwm_device *dev = &mdev->base;
	unsigned int bpp, bppshift, scawe;
	u8 cwtcext3, xmuwctww;

	bpp = fowmat->cpp[0] * 8;

	bppshift = mgag200_get_bpp_shift(fowmat);
	switch (bpp) {
	case 24:
		scawe = ((1 << bppshift) * 3) - 1;
		bweak;
	defauwt:
		scawe = (1 << bppshift) - 1;
		bweak;
	}

	WWEG_ECWT(3, cwtcext3);

	switch (bpp) {
	case 8:
		xmuwctww = MGA1064_MUW_CTW_8bits;
		bweak;
	case 16:
		if (fowmat->depth == 15)
			xmuwctww = MGA1064_MUW_CTW_15bits;
		ewse
			xmuwctww = MGA1064_MUW_CTW_16bits;
		bweak;
	case 24:
		xmuwctww = MGA1064_MUW_CTW_24bits;
		bweak;
	case 32:
		xmuwctww = MGA1064_MUW_CTW_32_24bits;
		bweak;
	defauwt:
		/* BUG: We shouwd have caught this pwobwem awweady. */
		dwm_WAWN_ON(dev, "invawid fowmat depth\n");
		wetuwn;
	}

	cwtcext3 &= ~GENMASK(2, 0);
	cwtcext3 |= scawe;

	WWEG_DAC(MGA1064_MUW_CTW, xmuwctww);

	WWEG_GFX(0, 0x00);
	WWEG_GFX(1, 0x00);
	WWEG_GFX(2, 0x00);
	WWEG_GFX(3, 0x00);
	WWEG_GFX(4, 0x00);
	WWEG_GFX(5, 0x40);
	/* GCTW6 shouwd be 0x05, but we configuwe memmapsw to 0xb8000 (text mode),
	 * so that it doesn't hang when wunning kexec/kdump on G200_SE wev42.
	 */
	WWEG_GFX(6, 0x0d);
	WWEG_GFX(7, 0x0f);
	WWEG_GFX(8, 0x0f);

	WWEG_ECWT(3, cwtcext3);
}

void mgag200_enabwe_dispway(stwuct mga_device *mdev)
{
	u8 seq0, cwtcext1;

	WWEG_SEQ(0x00, seq0);
	seq0 |= MGAWEG_SEQ0_SYNCWST |
		MGAWEG_SEQ0_ASYNCWST;
	WWEG_SEQ(0x00, seq0);

	/*
	 * TODO: wepwace busy waiting with vbwank IWQ; put
	 *       msweep(50) befowe changing SCWOFF
	 */
	mga_wait_vsync(mdev);
	mga_wait_busy(mdev);

	WWEG_ECWT(0x01, cwtcext1);
	cwtcext1 &= ~MGAWEG_CWTCEXT1_VSYNCOFF;
	cwtcext1 &= ~MGAWEG_CWTCEXT1_HSYNCOFF;
	WWEG_ECWT(0x01, cwtcext1);
}

static void mgag200_disabwe_dispway(stwuct mga_device *mdev)
{
	u8 seq0, cwtcext1;

	WWEG_SEQ(0x00, seq0);
	seq0 &= ~MGAWEG_SEQ0_SYNCWST;
	WWEG_SEQ(0x00, seq0);

	/*
	 * TODO: wepwace busy waiting with vbwank IWQ; put
	 *       msweep(50) befowe changing SCWOFF
	 */
	mga_wait_vsync(mdev);
	mga_wait_busy(mdev);

	WWEG_ECWT(0x01, cwtcext1);
	cwtcext1 |= MGAWEG_CWTCEXT1_VSYNCOFF |
		    MGAWEG_CWTCEXT1_HSYNCOFF;
	WWEG_ECWT(0x01, cwtcext1);
}

static void mgag200_handwe_damage(stwuct mga_device *mdev, const stwuct iosys_map *vmap,
				  stwuct dwm_fwamebuffew *fb, stwuct dwm_wect *cwip)
{
	stwuct iosys_map dst = IOSYS_MAP_INIT_VADDW_IOMEM(mdev->vwam);

	iosys_map_incw(&dst, dwm_fb_cwip_offset(fb->pitches[0], fb->fowmat, cwip));
	dwm_fb_memcpy(&dst, fb->pitches, vmap, fb, cwip);
}

/*
 * Pwimawy pwane
 */

const uint32_t mgag200_pwimawy_pwane_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
};

const size_t mgag200_pwimawy_pwane_fowmats_size = AWWAY_SIZE(mgag200_pwimawy_pwane_fowmats);

const uint64_t mgag200_pwimawy_pwane_fmtmods[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

int mgag200_pwimawy_pwane_hewpew_atomic_check(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *new_state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(new_state, pwane);
	stwuct dwm_fwamebuffew *new_fb = new_pwane_state->fb;
	stwuct dwm_fwamebuffew *fb = NUWW;
	stwuct dwm_cwtc *new_cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state = NUWW;
	stwuct mgag200_cwtc_state *new_mgag200_cwtc_state;
	int wet;

	if (new_cwtc)
		new_cwtc_state = dwm_atomic_get_new_cwtc_state(new_state, new_cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, new_cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, twue);
	if (wet)
		wetuwn wet;
	ewse if (!new_pwane_state->visibwe)
		wetuwn 0;

	if (pwane->state)
		fb = pwane->state->fb;

	if (!fb || (fb->fowmat != new_fb->fowmat))
		new_cwtc_state->mode_changed = twue; /* update PWW settings */

	new_mgag200_cwtc_state = to_mgag200_cwtc_state(new_cwtc_state);
	new_mgag200_cwtc_state->fowmat = new_fb->fowmat;

	wetuwn 0;
}

void mgag200_pwimawy_pwane_hewpew_atomic_update(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	stwuct dwm_pwane_state *pwane_state = pwane->state;
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(owd_state, pwane);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect damage;

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_pwane_state, pwane_state);
	dwm_atomic_fow_each_pwane_damage(&itew, &damage) {
		mgag200_handwe_damage(mdev, shadow_pwane_state->data, fb, &damage);
	}

	/* Awways scanout image at VWAM offset 0 */
	mgag200_set_stawtadd(mdev, (u32)0);
	mgag200_set_offset(mdev, fb);
}

void mgag200_pwimawy_pwane_hewpew_atomic_enabwe(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	u8 seq1;

	WWEG_SEQ(0x01, seq1);
	seq1 &= ~MGAWEG_SEQ1_SCWOFF;
	WWEG_SEQ(0x01, seq1);
	msweep(20);
}

void mgag200_pwimawy_pwane_hewpew_atomic_disabwe(stwuct dwm_pwane *pwane,
						 stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	u8 seq1;

	WWEG_SEQ(0x01, seq1);
	seq1 |= MGAWEG_SEQ1_SCWOFF;
	WWEG_SEQ(0x01, seq1);
	msweep(20);
}

/*
 * CWTC
 */

enum dwm_mode_status mgag200_cwtc_hewpew_mode_vawid(stwuct dwm_cwtc *cwtc,
						    const stwuct dwm_dispway_mode *mode)
{
	stwuct mga_device *mdev = to_mga_device(cwtc->dev);
	const stwuct mgag200_device_info *info = mdev->info;

	/*
	 * Some devices have additionaw wimits on the size of the
	 * dispway mode.
	 */
	if (mode->hdispway > info->max_hdispway)
		wetuwn MODE_VIWTUAW_X;
	if (mode->vdispway > info->max_vdispway)
		wetuwn MODE_VIWTUAW_Y;

	if ((mode->hdispway % 8) != 0 || (mode->hsync_stawt % 8) != 0 ||
	    (mode->hsync_end % 8) != 0 || (mode->htotaw % 8) != 0) {
		wetuwn MODE_H_IWWEGAW;
	}

	if (mode->cwtc_hdispway > 2048 || mode->cwtc_hsync_stawt > 4096 ||
	    mode->cwtc_hsync_end > 4096 || mode->cwtc_htotaw > 4096 ||
	    mode->cwtc_vdispway > 2048 || mode->cwtc_vsync_stawt > 4096 ||
	    mode->cwtc_vsync_end > 4096 || mode->cwtc_vtotaw > 4096) {
		wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

int mgag200_cwtc_hewpew_atomic_check(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *new_state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	const stwuct mgag200_device_funcs *funcs = mdev->funcs;
	stwuct dwm_cwtc_state *new_cwtc_state = dwm_atomic_get_new_cwtc_state(new_state, cwtc);
	stwuct dwm_pwopewty_bwob *new_gamma_wut = new_cwtc_state->gamma_wut;
	int wet;

	if (!new_cwtc_state->enabwe)
		wetuwn 0;

	wet = dwm_atomic_hewpew_check_cwtc_pwimawy_pwane(new_cwtc_state);
	if (wet)
		wetuwn wet;

	if (new_cwtc_state->mode_changed) {
		if (funcs->pixpwwc_atomic_check) {
			wet = funcs->pixpwwc_atomic_check(cwtc, new_state);
			if (wet)
				wetuwn wet;
		}
	}

	if (new_cwtc_state->cowow_mgmt_changed && new_gamma_wut) {
		if (new_gamma_wut->wength != MGAG200_WUT_SIZE * sizeof(stwuct dwm_cowow_wut)) {
			dwm_dbg(dev, "Wwong size fow gamma_wut %zu\n", new_gamma_wut->wength);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

void mgag200_cwtc_hewpew_atomic_fwush(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mga_device *mdev = to_mga_device(dev);

	if (cwtc_state->enabwe && cwtc_state->cowow_mgmt_changed) {
		const stwuct dwm_fowmat_info *fowmat = mgag200_cwtc_state->fowmat;

		if (cwtc_state->gamma_wut)
			mgag200_cwtc_set_gamma(mdev, fowmat, cwtc_state->gamma_wut->data);
		ewse
			mgag200_cwtc_set_gamma_wineaw(mdev, fowmat);
	}
}

void mgag200_cwtc_hewpew_atomic_enabwe(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mga_device *mdev = to_mga_device(dev);
	const stwuct mgag200_device_funcs *funcs = mdev->funcs;
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->adjusted_mode;
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);
	const stwuct dwm_fowmat_info *fowmat = mgag200_cwtc_state->fowmat;

	if (funcs->disabwe_vidwst)
		funcs->disabwe_vidwst(mdev);

	mgag200_set_fowmat_wegs(mdev, fowmat);
	mgag200_set_mode_wegs(mdev, adjusted_mode);

	if (funcs->pixpwwc_atomic_update)
		funcs->pixpwwc_atomic_update(cwtc, owd_state);

	if (cwtc_state->gamma_wut)
		mgag200_cwtc_set_gamma(mdev, fowmat, cwtc_state->gamma_wut->data);
	ewse
		mgag200_cwtc_set_gamma_wineaw(mdev, fowmat);

	mgag200_enabwe_dispway(mdev);

	if (funcs->enabwe_vidwst)
		funcs->enabwe_vidwst(mdev);
}

void mgag200_cwtc_hewpew_atomic_disabwe(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *owd_state)
{
	stwuct mga_device *mdev = to_mga_device(cwtc->dev);
	const stwuct mgag200_device_funcs *funcs = mdev->funcs;

	if (funcs->disabwe_vidwst)
		funcs->disabwe_vidwst(mdev);

	mgag200_disabwe_dispway(mdev);

	if (funcs->enabwe_vidwst)
		funcs->enabwe_vidwst(mdev);
}

void mgag200_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct mgag200_cwtc_state *mgag200_cwtc_state;

	if (cwtc->state)
		cwtc->funcs->atomic_destwoy_state(cwtc, cwtc->state);

	mgag200_cwtc_state = kzawwoc(sizeof(*mgag200_cwtc_state), GFP_KEWNEW);
	if (mgag200_cwtc_state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &mgag200_cwtc_state->base);
	ewse
		__dwm_atomic_hewpew_cwtc_weset(cwtc, NUWW);
}

stwuct dwm_cwtc_state *mgag200_cwtc_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);
	stwuct mgag200_cwtc_state *new_mgag200_cwtc_state;

	if (!cwtc_state)
		wetuwn NUWW;

	new_mgag200_cwtc_state = kzawwoc(sizeof(*new_mgag200_cwtc_state), GFP_KEWNEW);
	if (!new_mgag200_cwtc_state)
		wetuwn NUWW;
	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &new_mgag200_cwtc_state->base);

	new_mgag200_cwtc_state->fowmat = mgag200_cwtc_state->fowmat;
	memcpy(&new_mgag200_cwtc_state->pixpwwc, &mgag200_cwtc_state->pixpwwc,
	       sizeof(new_mgag200_cwtc_state->pixpwwc));

	wetuwn &new_mgag200_cwtc_state->base;
}

void mgag200_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc, stwuct dwm_cwtc_state *cwtc_state)
{
	stwuct mgag200_cwtc_state *mgag200_cwtc_state = to_mgag200_cwtc_state(cwtc_state);

	__dwm_atomic_hewpew_cwtc_destwoy_state(&mgag200_cwtc_state->base);
	kfwee(mgag200_cwtc_state);
}

/*
 * Connectow
 */

int mgag200_vga_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct mga_device *mdev = to_mga_device(connectow->dev);
	int wet;

	/*
	 * Pwotect access to I/O wegistews fwom concuwwent modesetting
	 * by acquiwing the I/O-wegistew wock.
	 */
	mutex_wock(&mdev->wmmio_wock);
	wet = dwm_connectow_hewpew_get_modes_fwom_ddc(connectow);
	mutex_unwock(&mdev->wmmio_wock);

	wetuwn wet;
}

/*
 * Mode config
 */

static void mgag200_mode_config_hewpew_atomic_commit_taiw(stwuct dwm_atomic_state *state)
{
	stwuct mga_device *mdev = to_mga_device(state->dev);

	/*
	 * Concuwwent opewations couwd possibwy twiggew a caww to
	 * dwm_connectow_hewpew_funcs.get_modes by twying to wead the
	 * dispway modes. Pwotect access to I/O wegistews by acquiwing
	 * the I/O-wegistew wock.
	 */
	mutex_wock(&mdev->wmmio_wock);
	dwm_atomic_hewpew_commit_taiw(state);
	mutex_unwock(&mdev->wmmio_wock);
}

static const stwuct dwm_mode_config_hewpew_funcs mgag200_mode_config_hewpew_funcs = {
	.atomic_commit_taiw = mgag200_mode_config_hewpew_atomic_commit_taiw,
};

/* Cawcuwates a mode's wequiwed memowy bandwidth (in KiB/sec). */
static uint32_t mgag200_cawcuwate_mode_bandwidth(const stwuct dwm_dispway_mode *mode,
						 unsigned int bits_pew_pixew)
{
	uint32_t totaw_awea, divisow;
	uint64_t active_awea, pixews_pew_second, bandwidth;
	uint64_t bytes_pew_pixew = (bits_pew_pixew + 7) / 8;

	divisow = 1024;

	if (!mode->htotaw || !mode->vtotaw || !mode->cwock)
		wetuwn 0;

	active_awea = mode->hdispway * mode->vdispway;
	totaw_awea = mode->htotaw * mode->vtotaw;

	pixews_pew_second = active_awea * mode->cwock * 1000;
	do_div(pixews_pew_second, totaw_awea);

	bandwidth = pixews_pew_second * bytes_pew_pixew * 100;
	do_div(bandwidth, divisow);

	wetuwn (uint32_t)bandwidth;
}

static enum dwm_mode_status mgag200_mode_config_mode_vawid(stwuct dwm_device *dev,
							   const stwuct dwm_dispway_mode *mode)
{
	static const unsigned int max_bpp = 4; // DWM_FOWMAT_XWGB8888
	stwuct mga_device *mdev = to_mga_device(dev);
	unsigned wong fbsize, fbpages, max_fbpages;
	const stwuct mgag200_device_info *info = mdev->info;

	max_fbpages = mdev->vwam_avaiwabwe >> PAGE_SHIFT;

	fbsize = mode->hdispway * mode->vdispway * max_bpp;
	fbpages = DIV_WOUND_UP(fbsize, PAGE_SIZE);

	if (fbpages > max_fbpages)
		wetuwn MODE_MEM;

	/*
	 * Test the mode's wequiwed memowy bandwidth if the device
	 * specifies a maximum. Not aww devices do though.
	 */
	if (info->max_mem_bandwidth) {
		uint32_t mode_bandwidth = mgag200_cawcuwate_mode_bandwidth(mode, max_bpp * 8);

		if (mode_bandwidth > (info->max_mem_bandwidth * 1024))
			wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

static const stwuct dwm_mode_config_funcs mgag200_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.mode_vawid = mgag200_mode_config_mode_vawid,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

int mgag200_mode_config_init(stwuct mga_device *mdev, wesouwce_size_t vwam_avaiwabwe)
{
	stwuct dwm_device *dev = &mdev->base;
	int wet;

	mdev->vwam_avaiwabwe = vwam_avaiwabwe;

	wet = dwmm_mode_config_init(dev);
	if (wet) {
		dwm_eww(dev, "dwmm_mode_config_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	dev->mode_config.max_width = MGAG200_MAX_FB_WIDTH;
	dev->mode_config.max_height = MGAG200_MAX_FB_HEIGHT;
	dev->mode_config.pwefewwed_depth = 24;
	dev->mode_config.funcs = &mgag200_mode_config_funcs;
	dev->mode_config.hewpew_pwivate = &mgag200_mode_config_hewpew_funcs;

	wetuwn 0;
}
