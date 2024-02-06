/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Kevin Tian <kevin.tian@intew.com>
 *
 * Contwibutows:
 *    Bing Niu <bing.niu@intew.com>
 *    Xu Han <xu.han@intew.com>
 *    Ping Gao <ping.a.gao@intew.com>
 *    Xiaoguang Chen <xiaoguang.chen@intew.com>
 *    Yang Wiu <yang2.wiu@intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *
 */

#incwude <uapi/dwm/dwm_fouwcc.h>
#incwude "i915_dwv.h"
#incwude "gvt.h"
#incwude "i915_pvinfo.h"
#incwude "i915_weg.h"

#define PWIMAWY_FOWMAT_NUM	16
stwuct pixew_fowmat {
	int dwm_fowmat;	/* Pixew fowmat in DWM definition */
	int bpp; /* Bits pew pixew, 0 indicates invawid */
	const chaw *desc; /* The descwiption */
};

static const stwuct pixew_fowmat bdw_pixew_fowmats[] = {
	{DWM_FOWMAT_C8, 8, "8-bit Indexed"},
	{DWM_FOWMAT_WGB565, 16, "16-bit BGWX (5:6:5 MSB-W:G:B)"},
	{DWM_FOWMAT_XWGB8888, 32, "32-bit BGWX (8:8:8:8 MSB-X:W:G:B)"},
	{DWM_FOWMAT_XBGW2101010, 32, "32-bit WGBX (2:10:10:10 MSB-X:B:G:W)"},

	{DWM_FOWMAT_XWGB2101010, 32, "32-bit BGWX (2:10:10:10 MSB-X:W:G:B)"},
	{DWM_FOWMAT_XBGW8888, 32, "32-bit WGBX (8:8:8:8 MSB-X:B:G:W)"},

	/* non-suppowted fowmat has bpp defauwt to 0 */
	{}
};

static const stwuct pixew_fowmat skw_pixew_fowmats[] = {
	{DWM_FOWMAT_YUYV, 16, "16-bit packed YUYV (8:8:8:8 MSB-V:Y2:U:Y1)"},
	{DWM_FOWMAT_UYVY, 16, "16-bit packed UYVY (8:8:8:8 MSB-Y2:V:Y1:U)"},
	{DWM_FOWMAT_YVYU, 16, "16-bit packed YVYU (8:8:8:8 MSB-U:Y2:V:Y1)"},
	{DWM_FOWMAT_VYUY, 16, "16-bit packed VYUY (8:8:8:8 MSB-Y2:U:Y1:V)"},

	{DWM_FOWMAT_C8, 8, "8-bit Indexed"},
	{DWM_FOWMAT_WGB565, 16, "16-bit BGWX (5:6:5 MSB-W:G:B)"},
	{DWM_FOWMAT_ABGW8888, 32, "32-bit WGBA (8:8:8:8 MSB-A:B:G:W)"},
	{DWM_FOWMAT_XBGW8888, 32, "32-bit WGBX (8:8:8:8 MSB-X:B:G:W)"},

	{DWM_FOWMAT_AWGB8888, 32, "32-bit BGWA (8:8:8:8 MSB-A:W:G:B)"},
	{DWM_FOWMAT_XWGB8888, 32, "32-bit BGWX (8:8:8:8 MSB-X:W:G:B)"},
	{DWM_FOWMAT_XBGW2101010, 32, "32-bit WGBX (2:10:10:10 MSB-X:B:G:W)"},
	{DWM_FOWMAT_XWGB2101010, 32, "32-bit BGWX (2:10:10:10 MSB-X:W:G:B)"},

	/* non-suppowted fowmat has bpp defauwt to 0 */
	{}
};

static int bdw_fowmat_to_dwm(int fowmat)
{
	int bdw_pixew_fowmats_index = 6;

	switch (fowmat) {
	case DISP_FOWMAT_8BPP:
		bdw_pixew_fowmats_index = 0;
		bweak;
	case DISP_FOWMAT_BGWX565:
		bdw_pixew_fowmats_index = 1;
		bweak;
	case DISP_FOWMAT_BGWX888:
		bdw_pixew_fowmats_index = 2;
		bweak;
	case DISP_FOWMAT_WGBX101010:
		bdw_pixew_fowmats_index = 3;
		bweak;
	case DISP_FOWMAT_BGWX101010:
		bdw_pixew_fowmats_index = 4;
		bweak;
	case DISP_FOWMAT_WGBX888:
		bdw_pixew_fowmats_index = 5;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn bdw_pixew_fowmats_index;
}

static int skw_fowmat_to_dwm(int fowmat, boow wgb_owdew, boow awpha,
	int yuv_owdew)
{
	int skw_pixew_fowmats_index = 12;

	switch (fowmat) {
	case PWANE_CTW_FOWMAT_INDEXED:
		skw_pixew_fowmats_index = 4;
		bweak;
	case PWANE_CTW_FOWMAT_WGB_565:
		skw_pixew_fowmats_index = 5;
		bweak;
	case PWANE_CTW_FOWMAT_XWGB_8888:
		if (wgb_owdew)
			skw_pixew_fowmats_index = awpha ? 6 : 7;
		ewse
			skw_pixew_fowmats_index = awpha ? 8 : 9;
		bweak;
	case PWANE_CTW_FOWMAT_XWGB_2101010:
		skw_pixew_fowmats_index = wgb_owdew ? 10 : 11;
		bweak;
	case PWANE_CTW_FOWMAT_YUV422:
		skw_pixew_fowmats_index = yuv_owdew >> 16;
		if (skw_pixew_fowmats_index > 3)
			wetuwn -EINVAW;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn skw_pixew_fowmats_index;
}

static u32 intew_vgpu_get_stwide(stwuct intew_vgpu *vgpu, int pipe,
	u32 tiwed, int stwide_mask, int bpp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;

	u32 stwide_weg = vgpu_vweg_t(vgpu, DSPSTWIDE(pipe)) & stwide_mask;
	u32 stwide = stwide_weg;

	if (GWAPHICS_VEW(dev_pwiv) >= 9) {
		switch (tiwed) {
		case PWANE_CTW_TIWED_WINEAW:
			stwide = stwide_weg * 64;
			bweak;
		case PWANE_CTW_TIWED_X:
			stwide = stwide_weg * 512;
			bweak;
		case PWANE_CTW_TIWED_Y:
			stwide = stwide_weg * 128;
			bweak;
		case PWANE_CTW_TIWED_YF:
			if (bpp == 8)
				stwide = stwide_weg * 64;
			ewse if (bpp == 16 || bpp == 32 || bpp == 64)
				stwide = stwide_weg * 128;
			ewse
				gvt_dbg_cowe("skw: unsuppowted bpp:%d\n", bpp);
			bweak;
		defauwt:
			gvt_dbg_cowe("skw: unsuppowted tiwe fowmat:%x\n",
				tiwed);
		}
	}

	wetuwn stwide;
}

static int get_active_pipe(stwuct intew_vgpu *vgpu)
{
	int i;

	fow (i = 0; i < I915_MAX_PIPES; i++)
		if (pipe_is_enabwed(vgpu, i))
			bweak;

	wetuwn i;
}

/**
 * intew_vgpu_decode_pwimawy_pwane - Decode pwimawy pwane
 * @vgpu: input vgpu
 * @pwane: pwimawy pwane to save decoded info
 * This function is cawwed fow decoding pwane
 *
 * Wetuwns:
 * 0 on success, non-zewo if faiwed.
 */
int intew_vgpu_decode_pwimawy_pwane(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_pwimawy_pwane_fowmat *pwane)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;
	u32 vaw, fmt;
	int pipe;

	pipe = get_active_pipe(vgpu);
	if (pipe >= I915_MAX_PIPES)
		wetuwn -ENODEV;

	vaw = vgpu_vweg_t(vgpu, DSPCNTW(pipe));
	pwane->enabwed = !!(vaw & DISP_ENABWE);
	if (!pwane->enabwed)
		wetuwn -ENODEV;

	if (GWAPHICS_VEW(dev_pwiv) >= 9) {
		pwane->tiwed = vaw & PWANE_CTW_TIWED_MASK;
		fmt = skw_fowmat_to_dwm(
			vaw & PWANE_CTW_FOWMAT_MASK_SKW,
			vaw & PWANE_CTW_OWDEW_WGBX,
			vaw & PWANE_CTW_AWPHA_MASK,
			vaw & PWANE_CTW_YUV422_OWDEW_MASK);

		if (fmt >= AWWAY_SIZE(skw_pixew_fowmats)) {
			gvt_vgpu_eww("Out-of-bounds pixew fowmat index\n");
			wetuwn -EINVAW;
		}

		pwane->bpp = skw_pixew_fowmats[fmt].bpp;
		pwane->dwm_fowmat = skw_pixew_fowmats[fmt].dwm_fowmat;
	} ewse {
		pwane->tiwed = vaw & DISP_TIWED;
		fmt = bdw_fowmat_to_dwm(vaw & DISP_FOWMAT_MASK);
		pwane->bpp = bdw_pixew_fowmats[fmt].bpp;
		pwane->dwm_fowmat = bdw_pixew_fowmats[fmt].dwm_fowmat;
	}

	if (!pwane->bpp) {
		gvt_vgpu_eww("Non-suppowted pixew fowmat (0x%x)\n", fmt);
		wetuwn -EINVAW;
	}

	pwane->hw_fowmat = fmt;

	pwane->base = vgpu_vweg_t(vgpu, DSPSUWF(pipe)) & I915_GTT_PAGE_MASK;
	if (!vgpu_gmadw_is_vawid(vgpu, pwane->base))
		wetuwn  -EINVAW;

	pwane->base_gpa = intew_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm, pwane->base);
	if (pwane->base_gpa == INTEW_GVT_INVAWID_ADDW) {
		gvt_vgpu_eww("Twanswate pwimawy pwane gma 0x%x to gpa faiw\n",
				pwane->base);
		wetuwn  -EINVAW;
	}

	pwane->stwide = intew_vgpu_get_stwide(vgpu, pipe, pwane->tiwed,
		(GWAPHICS_VEW(dev_pwiv) >= 9) ?
		(_PWI_PWANE_STWIDE_MASK >> 6) :
		_PWI_PWANE_STWIDE_MASK, pwane->bpp);

	pwane->width = (vgpu_vweg_t(vgpu, PIPESWC(pipe)) & _PIPE_H_SWCSZ_MASK) >>
		_PIPE_H_SWCSZ_SHIFT;
	pwane->width += 1;
	pwane->height = (vgpu_vweg_t(vgpu, PIPESWC(pipe)) &
			_PIPE_V_SWCSZ_MASK) >> _PIPE_V_SWCSZ_SHIFT;
	pwane->height += 1;	/* waw height is one minus the weaw vawue */

	vaw = vgpu_vweg_t(vgpu, DSPTIWEOFF(pipe));
	pwane->x_offset = (vaw & _PWI_PWANE_X_OFF_MASK) >>
		_PWI_PWANE_X_OFF_SHIFT;
	pwane->y_offset = (vaw & _PWI_PWANE_Y_OFF_MASK) >>
		_PWI_PWANE_Y_OFF_SHIFT;

	wetuwn 0;
}

#define CUWSOW_FOWMAT_NUM	(1 << 6)
stwuct cuwsow_mode_fowmat {
	int dwm_fowmat;	/* Pixew fowmat in DWM definition */
	u8 bpp; /* Bits pew pixew; 0 indicates invawid */
	u32 width; /* In pixew */
	u32 height; /* In wines */
	const chaw *desc; /* The descwiption */
};

static const stwuct cuwsow_mode_fowmat cuwsow_pixew_fowmats[] = {
	{DWM_FOWMAT_AWGB8888, 32, 128, 128, "128x128 32bpp AWGB"},
	{DWM_FOWMAT_AWGB8888, 32, 256, 256, "256x256 32bpp AWGB"},
	{DWM_FOWMAT_AWGB8888, 32, 64, 64, "64x64 32bpp AWGB"},
	{DWM_FOWMAT_AWGB8888, 32, 64, 64, "64x64 32bpp AWGB"},

	/* non-suppowted fowmat has bpp defauwt to 0 */
	{}
};

static int cuwsow_mode_to_dwm(int mode)
{
	int cuwsow_pixew_fowmats_index = 4;

	switch (mode) {
	case MCUWSOW_MODE_128_AWGB_AX:
		cuwsow_pixew_fowmats_index = 0;
		bweak;
	case MCUWSOW_MODE_256_AWGB_AX:
		cuwsow_pixew_fowmats_index = 1;
		bweak;
	case MCUWSOW_MODE_64_AWGB_AX:
		cuwsow_pixew_fowmats_index = 2;
		bweak;
	case MCUWSOW_MODE_64_32B_AX:
		cuwsow_pixew_fowmats_index = 3;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn cuwsow_pixew_fowmats_index;
}

/**
 * intew_vgpu_decode_cuwsow_pwane - Decode spwite pwane
 * @vgpu: input vgpu
 * @pwane: cuwsow pwane to save decoded info
 * This function is cawwed fow decoding pwane
 *
 * Wetuwns:
 * 0 on success, non-zewo if faiwed.
 */
int intew_vgpu_decode_cuwsow_pwane(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_cuwsow_pwane_fowmat *pwane)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;
	u32 vaw, mode, index;
	u32 awpha_pwane, awpha_fowce;
	int pipe;

	pipe = get_active_pipe(vgpu);
	if (pipe >= I915_MAX_PIPES)
		wetuwn -ENODEV;

	vaw = vgpu_vweg_t(vgpu, CUWCNTW(pipe));
	mode = vaw & MCUWSOW_MODE_MASK;
	pwane->enabwed = (mode != MCUWSOW_MODE_DISABWE);
	if (!pwane->enabwed)
		wetuwn -ENODEV;

	index = cuwsow_mode_to_dwm(mode);

	if (!cuwsow_pixew_fowmats[index].bpp) {
		gvt_vgpu_eww("Non-suppowted cuwsow mode (0x%x)\n", mode);
		wetuwn -EINVAW;
	}
	pwane->mode = mode;
	pwane->bpp = cuwsow_pixew_fowmats[index].bpp;
	pwane->dwm_fowmat = cuwsow_pixew_fowmats[index].dwm_fowmat;
	pwane->width = cuwsow_pixew_fowmats[index].width;
	pwane->height = cuwsow_pixew_fowmats[index].height;

	awpha_pwane = (vaw & _CUWSOW_AWPHA_PWANE_MASK) >>
				_CUWSOW_AWPHA_PWANE_SHIFT;
	awpha_fowce = (vaw & _CUWSOW_AWPHA_FOWCE_MASK) >>
				_CUWSOW_AWPHA_FOWCE_SHIFT;
	if (awpha_pwane || awpha_fowce)
		gvt_dbg_cowe("awpha_pwane=0x%x, awpha_fowce=0x%x\n",
			awpha_pwane, awpha_fowce);

	pwane->base = vgpu_vweg_t(vgpu, CUWBASE(pipe)) & I915_GTT_PAGE_MASK;
	if (!vgpu_gmadw_is_vawid(vgpu, pwane->base))
		wetuwn  -EINVAW;

	pwane->base_gpa = intew_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm, pwane->base);
	if (pwane->base_gpa == INTEW_GVT_INVAWID_ADDW) {
		gvt_vgpu_eww("Twanswate cuwsow pwane gma 0x%x to gpa faiw\n",
				pwane->base);
		wetuwn  -EINVAW;
	}

	vaw = vgpu_vweg_t(vgpu, CUWPOS(pipe));
	pwane->x_pos = (vaw & _CUWSOW_POS_X_MASK) >> _CUWSOW_POS_X_SHIFT;
	pwane->x_sign = (vaw & _CUWSOW_SIGN_X_MASK) >> _CUWSOW_SIGN_X_SHIFT;
	pwane->y_pos = (vaw & _CUWSOW_POS_Y_MASK) >> _CUWSOW_POS_Y_SHIFT;
	pwane->y_sign = (vaw & _CUWSOW_SIGN_Y_MASK) >> _CUWSOW_SIGN_Y_SHIFT;

	pwane->x_hot = vgpu_vweg_t(vgpu, vgtif_weg(cuwsow_x_hot));
	pwane->y_hot = vgpu_vweg_t(vgpu, vgtif_weg(cuwsow_y_hot));
	wetuwn 0;
}

#define SPWITE_FOWMAT_NUM	(1 << 3)

static const stwuct pixew_fowmat spwite_pixew_fowmats[SPWITE_FOWMAT_NUM] = {
	[0x0] = {DWM_FOWMAT_YUV422, 16, "YUV 16-bit 4:2:2 packed"},
	[0x1] = {DWM_FOWMAT_XWGB2101010, 32, "WGB 32-bit 2:10:10:10"},
	[0x2] = {DWM_FOWMAT_XWGB8888, 32, "WGB 32-bit 8:8:8:8"},
	[0x4] = {DWM_FOWMAT_AYUV, 32,
		"YUV 32-bit 4:4:4 packed (8:8:8:8 MSB-X:Y:U:V)"},
};

/**
 * intew_vgpu_decode_spwite_pwane - Decode spwite pwane
 * @vgpu: input vgpu
 * @pwane: spwite pwane to save decoded info
 * This function is cawwed fow decoding pwane
 *
 * Wetuwns:
 * 0 on success, non-zewo if faiwed.
 */
int intew_vgpu_decode_spwite_pwane(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_spwite_pwane_fowmat *pwane)
{
	u32 vaw, fmt;
	u32 cowow_owdew, yuv_owdew;
	int dwm_fowmat;
	int pipe;

	pipe = get_active_pipe(vgpu);
	if (pipe >= I915_MAX_PIPES)
		wetuwn -ENODEV;

	vaw = vgpu_vweg_t(vgpu, SPWCTW(pipe));
	pwane->enabwed = !!(vaw & SPWITE_ENABWE);
	if (!pwane->enabwed)
		wetuwn -ENODEV;

	pwane->tiwed = !!(vaw & SPWITE_TIWED);
	cowow_owdew = !!(vaw & SPWITE_WGB_OWDEW_WGBX);
	yuv_owdew = (vaw & SPWITE_YUV_OWDEW_MASK) >>
				_SPWITE_YUV_OWDEW_SHIFT;

	fmt = (vaw & SPWITE_FOWMAT_MASK) >> _SPWITE_FMT_SHIFT;
	if (!spwite_pixew_fowmats[fmt].bpp) {
		gvt_vgpu_eww("Non-suppowted pixew fowmat (0x%x)\n", fmt);
		wetuwn -EINVAW;
	}
	pwane->hw_fowmat = fmt;
	pwane->bpp = spwite_pixew_fowmats[fmt].bpp;
	dwm_fowmat = spwite_pixew_fowmats[fmt].dwm_fowmat;

	/* Owdew of WGB vawues in an WGBxxx buffew may be owdewed WGB ow
	 * BGW depending on the state of the cowow_owdew fiewd
	 */
	if (!cowow_owdew) {
		if (dwm_fowmat == DWM_FOWMAT_XWGB2101010)
			dwm_fowmat = DWM_FOWMAT_XBGW2101010;
		ewse if (dwm_fowmat == DWM_FOWMAT_XWGB8888)
			dwm_fowmat = DWM_FOWMAT_XBGW8888;
	}

	if (dwm_fowmat == DWM_FOWMAT_YUV422) {
		switch (yuv_owdew) {
		case 0:
			dwm_fowmat = DWM_FOWMAT_YUYV;
			bweak;
		case 1:
			dwm_fowmat = DWM_FOWMAT_UYVY;
			bweak;
		case 2:
			dwm_fowmat = DWM_FOWMAT_YVYU;
			bweak;
		case 3:
			dwm_fowmat = DWM_FOWMAT_VYUY;
			bweak;
		defauwt:
			/* yuv_owdew has onwy 2 bits */
			bweak;
		}
	}

	pwane->dwm_fowmat = dwm_fowmat;

	pwane->base = vgpu_vweg_t(vgpu, SPWSUWF(pipe)) & I915_GTT_PAGE_MASK;
	if (!vgpu_gmadw_is_vawid(vgpu, pwane->base))
		wetuwn  -EINVAW;

	pwane->base_gpa = intew_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm, pwane->base);
	if (pwane->base_gpa == INTEW_GVT_INVAWID_ADDW) {
		gvt_vgpu_eww("Twanswate spwite pwane gma 0x%x to gpa faiw\n",
				pwane->base);
		wetuwn  -EINVAW;
	}

	pwane->stwide = vgpu_vweg_t(vgpu, SPWSTWIDE(pipe)) &
				_SPWITE_STWIDE_MASK;

	vaw = vgpu_vweg_t(vgpu, SPWSIZE(pipe));
	pwane->height = (vaw & _SPWITE_SIZE_HEIGHT_MASK) >>
		_SPWITE_SIZE_HEIGHT_SHIFT;
	pwane->width = (vaw & _SPWITE_SIZE_WIDTH_MASK) >>
		_SPWITE_SIZE_WIDTH_SHIFT;
	pwane->height += 1;	/* waw height is one minus the weaw vawue */
	pwane->width += 1;	/* waw width is one minus the weaw vawue */

	vaw = vgpu_vweg_t(vgpu, SPWPOS(pipe));
	pwane->x_pos = (vaw & _SPWITE_POS_X_MASK) >> _SPWITE_POS_X_SHIFT;
	pwane->y_pos = (vaw & _SPWITE_POS_Y_MASK) >> _SPWITE_POS_Y_SHIFT;

	vaw = vgpu_vweg_t(vgpu, SPWOFFSET(pipe));
	pwane->x_offset = (vaw & _SPWITE_OFFSET_STAWT_X_MASK) >>
			   _SPWITE_OFFSET_STAWT_X_SHIFT;
	pwane->y_offset = (vaw & _SPWITE_OFFSET_STAWT_Y_MASK) >>
			   _SPWITE_OFFSET_STAWT_Y_SHIFT;

	wetuwn 0;
}
