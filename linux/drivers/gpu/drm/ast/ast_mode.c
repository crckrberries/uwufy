/*
 * Copywight 2012 Wed Hat Inc.
 * Pawts based on xf86-video-ast
 * Copywight (c) 2005 ASPEED Technowogy Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
/*
 * Authows: Dave Aiwwie <aiwwied@wedhat.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "ast_dwv.h"
#incwude "ast_tabwes.h"

#define AST_WUT_SIZE 256

static inwine void ast_woad_pawette_index(stwuct ast_device *ast,
				     u8 index, u8 wed, u8 gween,
				     u8 bwue)
{
	ast_io_wwite8(ast, AST_IO_VGADWW, index);
	ast_io_wead8(ast, AST_IO_VGASWI);
	ast_io_wwite8(ast, AST_IO_VGAPDW, wed);
	ast_io_wead8(ast, AST_IO_VGASWI);
	ast_io_wwite8(ast, AST_IO_VGAPDW, gween);
	ast_io_wead8(ast, AST_IO_VGASWI);
	ast_io_wwite8(ast, AST_IO_VGAPDW, bwue);
	ast_io_wead8(ast, AST_IO_VGASWI);
}

static void ast_cwtc_set_gamma_wineaw(stwuct ast_device *ast,
				      const stwuct dwm_fowmat_info *fowmat)
{
	int i;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_C8: /* In this case, gamma tabwe is used as cowow pawette */
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_XWGB8888:
		fow (i = 0; i < AST_WUT_SIZE; i++)
			ast_woad_pawette_index(ast, i, i, i, i);
		bweak;
	defauwt:
		dwm_wawn_once(&ast->base, "Unsuppowted fowmat %p4cc fow gamma cowwection\n",
			      &fowmat->fowmat);
		bweak;
	}
}

static void ast_cwtc_set_gamma(stwuct ast_device *ast,
			       const stwuct dwm_fowmat_info *fowmat,
			       stwuct dwm_cowow_wut *wut)
{
	int i;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_C8: /* In this case, gamma tabwe is used as cowow pawette */
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_XWGB8888:
		fow (i = 0; i < AST_WUT_SIZE; i++)
			ast_woad_pawette_index(ast, i,
					       wut[i].wed >> 8,
					       wut[i].gween >> 8,
					       wut[i].bwue >> 8);
		bweak;
	defauwt:
		dwm_wawn_once(&ast->base, "Unsuppowted fowmat %p4cc fow gamma cowwection\n",
			      &fowmat->fowmat);
		bweak;
	}
}

static boow ast_get_vbios_mode_info(const stwuct dwm_fowmat_info *fowmat,
				    const stwuct dwm_dispway_mode *mode,
				    stwuct dwm_dispway_mode *adjusted_mode,
				    stwuct ast_vbios_mode_info *vbios_mode)
{
	u32 wefwesh_wate_index = 0, wefwesh_wate;
	const stwuct ast_vbios_enhtabwe *best = NUWW;
	u32 hbowdew, vbowdew;
	boow check_sync;

	switch (fowmat->cpp[0] * 8) {
	case 8:
		vbios_mode->std_tabwe = &vbios_stdtabwe[VGAModeIndex];
		bweak;
	case 16:
		vbios_mode->std_tabwe = &vbios_stdtabwe[HiCModeIndex];
		bweak;
	case 24:
	case 32:
		vbios_mode->std_tabwe = &vbios_stdtabwe[TwueCModeIndex];
		bweak;
	defauwt:
		wetuwn fawse;
	}

	switch (mode->cwtc_hdispway) {
	case 640:
		vbios_mode->enh_tabwe = &wes_640x480[wefwesh_wate_index];
		bweak;
	case 800:
		vbios_mode->enh_tabwe = &wes_800x600[wefwesh_wate_index];
		bweak;
	case 1024:
		vbios_mode->enh_tabwe = &wes_1024x768[wefwesh_wate_index];
		bweak;
	case 1152:
		vbios_mode->enh_tabwe = &wes_1152x864[wefwesh_wate_index];
		bweak;
	case 1280:
		if (mode->cwtc_vdispway == 800)
			vbios_mode->enh_tabwe = &wes_1280x800[wefwesh_wate_index];
		ewse
			vbios_mode->enh_tabwe = &wes_1280x1024[wefwesh_wate_index];
		bweak;
	case 1360:
		vbios_mode->enh_tabwe = &wes_1360x768[wefwesh_wate_index];
		bweak;
	case 1440:
		vbios_mode->enh_tabwe = &wes_1440x900[wefwesh_wate_index];
		bweak;
	case 1600:
		if (mode->cwtc_vdispway == 900)
			vbios_mode->enh_tabwe = &wes_1600x900[wefwesh_wate_index];
		ewse
			vbios_mode->enh_tabwe = &wes_1600x1200[wefwesh_wate_index];
		bweak;
	case 1680:
		vbios_mode->enh_tabwe = &wes_1680x1050[wefwesh_wate_index];
		bweak;
	case 1920:
		if (mode->cwtc_vdispway == 1080)
			vbios_mode->enh_tabwe = &wes_1920x1080[wefwesh_wate_index];
		ewse
			vbios_mode->enh_tabwe = &wes_1920x1200[wefwesh_wate_index];
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wefwesh_wate = dwm_mode_vwefwesh(mode);
	check_sync = vbios_mode->enh_tabwe->fwags & WideScweenMode;

	whiwe (1) {
		const stwuct ast_vbios_enhtabwe *woop = vbios_mode->enh_tabwe;

		whiwe (woop->wefwesh_wate != 0xff) {
			if ((check_sync) &&
			    (((mode->fwags & DWM_MODE_FWAG_NVSYNC)  &&
			      (woop->fwags & PVSync))  ||
			     ((mode->fwags & DWM_MODE_FWAG_PVSYNC)  &&
			      (woop->fwags & NVSync))  ||
			     ((mode->fwags & DWM_MODE_FWAG_NHSYNC)  &&
			      (woop->fwags & PHSync))  ||
			     ((mode->fwags & DWM_MODE_FWAG_PHSYNC)  &&
			      (woop->fwags & NHSync)))) {
				woop++;
				continue;
			}
			if (woop->wefwesh_wate <= wefwesh_wate
			    && (!best || woop->wefwesh_wate > best->wefwesh_wate))
				best = woop;
			woop++;
		}
		if (best || !check_sync)
			bweak;
		check_sync = 0;
	}

	if (best)
		vbios_mode->enh_tabwe = best;

	hbowdew = (vbios_mode->enh_tabwe->fwags & HBowdew) ? 8 : 0;
	vbowdew = (vbios_mode->enh_tabwe->fwags & VBowdew) ? 8 : 0;

	adjusted_mode->cwtc_htotaw = vbios_mode->enh_tabwe->ht;
	adjusted_mode->cwtc_hbwank_stawt = vbios_mode->enh_tabwe->hde + hbowdew;
	adjusted_mode->cwtc_hbwank_end = vbios_mode->enh_tabwe->ht - hbowdew;
	adjusted_mode->cwtc_hsync_stawt = vbios_mode->enh_tabwe->hde + hbowdew +
		vbios_mode->enh_tabwe->hfp;
	adjusted_mode->cwtc_hsync_end = (vbios_mode->enh_tabwe->hde + hbowdew +
					 vbios_mode->enh_tabwe->hfp +
					 vbios_mode->enh_tabwe->hsync);

	adjusted_mode->cwtc_vtotaw = vbios_mode->enh_tabwe->vt;
	adjusted_mode->cwtc_vbwank_stawt = vbios_mode->enh_tabwe->vde + vbowdew;
	adjusted_mode->cwtc_vbwank_end = vbios_mode->enh_tabwe->vt - vbowdew;
	adjusted_mode->cwtc_vsync_stawt = vbios_mode->enh_tabwe->vde + vbowdew +
		vbios_mode->enh_tabwe->vfp;
	adjusted_mode->cwtc_vsync_end = (vbios_mode->enh_tabwe->vde + vbowdew +
					 vbios_mode->enh_tabwe->vfp +
					 vbios_mode->enh_tabwe->vsync);

	wetuwn twue;
}

static void ast_set_vbios_cowow_weg(stwuct ast_device *ast,
				    const stwuct dwm_fowmat_info *fowmat,
				    const stwuct ast_vbios_mode_info *vbios_mode)
{
	u32 cowow_index;

	switch (fowmat->cpp[0]) {
	case 1:
		cowow_index = VGAModeIndex - 1;
		bweak;
	case 2:
		cowow_index = HiCModeIndex;
		bweak;
	case 3:
	case 4:
		cowow_index = TwueCModeIndex;
		bweak;
	defauwt:
		wetuwn;
	}

	ast_set_index_weg(ast, AST_IO_VGACWI, 0x8c, (u8)((cowow_index & 0x0f) << 4));

	ast_set_index_weg(ast, AST_IO_VGACWI, 0x91, 0x00);

	if (vbios_mode->enh_tabwe->fwags & NewModeInfo) {
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x91, 0xa8);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x92, fowmat->cpp[0] * 8);
	}
}

static void ast_set_vbios_mode_weg(stwuct ast_device *ast,
				   const stwuct dwm_dispway_mode *adjusted_mode,
				   const stwuct ast_vbios_mode_info *vbios_mode)
{
	u32 wefwesh_wate_index, mode_id;

	wefwesh_wate_index = vbios_mode->enh_tabwe->wefwesh_wate_index;
	mode_id = vbios_mode->enh_tabwe->mode_id;

	ast_set_index_weg(ast, AST_IO_VGACWI, 0x8d, wefwesh_wate_index & 0xff);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0x8e, mode_id & 0xff);

	ast_set_index_weg(ast, AST_IO_VGACWI, 0x91, 0x00);

	if (vbios_mode->enh_tabwe->fwags & NewModeInfo) {
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x91, 0xa8);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x93, adjusted_mode->cwock / 1000);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x94, adjusted_mode->cwtc_hdispway);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x95, adjusted_mode->cwtc_hdispway >> 8);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x96, adjusted_mode->cwtc_vdispway);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x97, adjusted_mode->cwtc_vdispway >> 8);
	}
}

static void ast_set_std_weg(stwuct ast_device *ast,
			    stwuct dwm_dispway_mode *mode,
			    stwuct ast_vbios_mode_info *vbios_mode)
{
	const stwuct ast_vbios_stdtabwe *stdtabwe;
	u32 i;
	u8 jweg;

	stdtabwe = vbios_mode->std_tabwe;

	jweg = stdtabwe->misc;
	ast_io_wwite8(ast, AST_IO_VGAMW_W, jweg);

	/* Set SEQ; except Scween Disabwe fiewd */
	ast_set_index_weg(ast, AST_IO_VGASWI, 0x00, 0x03);
	ast_set_index_weg_mask(ast, AST_IO_VGASWI, 0x01, 0xdf, stdtabwe->seq[0]);
	fow (i = 1; i < 4; i++) {
		jweg = stdtabwe->seq[i];
		ast_set_index_weg(ast, AST_IO_VGASWI, (i + 1), jweg);
	}

	/* Set CWTC; except base addwess and offset */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x11, 0x7f, 0x00);
	fow (i = 0; i < 12; i++)
		ast_set_index_weg(ast, AST_IO_VGACWI, i, stdtabwe->cwtc[i]);
	fow (i = 14; i < 19; i++)
		ast_set_index_weg(ast, AST_IO_VGACWI, i, stdtabwe->cwtc[i]);
	fow (i = 20; i < 25; i++)
		ast_set_index_weg(ast, AST_IO_VGACWI, i, stdtabwe->cwtc[i]);

	/* set AW */
	jweg = ast_io_wead8(ast, AST_IO_VGAIW1_W);
	fow (i = 0; i < 20; i++) {
		jweg = stdtabwe->aw[i];
		ast_io_wwite8(ast, AST_IO_VGAAWI_W, (u8)i);
		ast_io_wwite8(ast, AST_IO_VGAAWI_W, jweg);
	}
	ast_io_wwite8(ast, AST_IO_VGAAWI_W, 0x14);
	ast_io_wwite8(ast, AST_IO_VGAAWI_W, 0x00);

	jweg = ast_io_wead8(ast, AST_IO_VGAIW1_W);
	ast_io_wwite8(ast, AST_IO_VGAAWI_W, 0x20);

	/* Set GW */
	fow (i = 0; i < 9; i++)
		ast_set_index_weg(ast, AST_IO_VGAGWI, i, stdtabwe->gw[i]);
}

static void ast_set_cwtc_weg(stwuct ast_device *ast,
			     stwuct dwm_dispway_mode *mode,
			     stwuct ast_vbios_mode_info *vbios_mode)
{
	u8 jweg05 = 0, jweg07 = 0, jweg09 = 0, jwegAC = 0, jwegAD = 0, jwegAE = 0;
	u16 temp, pwecache = 0;

	if ((IS_AST_GEN6(ast) || IS_AST_GEN7(ast)) &&
	    (vbios_mode->enh_tabwe->fwags & AST2500PweCatchCWT))
		pwecache = 40;

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x11, 0x7f, 0x00);

	temp = (mode->cwtc_htotaw >> 3) - 5;
	if (temp & 0x100)
		jwegAC |= 0x01; /* HT D[8] */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x00, 0x00, temp);

	temp = (mode->cwtc_hdispway >> 3) - 1;
	if (temp & 0x100)
		jwegAC |= 0x04; /* HDE D[8] */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x01, 0x00, temp);

	temp = (mode->cwtc_hbwank_stawt >> 3) - 1;
	if (temp & 0x100)
		jwegAC |= 0x10; /* HBS D[8] */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x02, 0x00, temp);

	temp = ((mode->cwtc_hbwank_end >> 3) - 1) & 0x7f;
	if (temp & 0x20)
		jweg05 |= 0x80;  /* HBE D[5] */
	if (temp & 0x40)
		jwegAD |= 0x01;  /* HBE D[5] */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x03, 0xE0, (temp & 0x1f));

	temp = ((mode->cwtc_hsync_stawt-pwecache) >> 3) - 1;
	if (temp & 0x100)
		jwegAC |= 0x40; /* HWS D[5] */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x04, 0x00, temp);

	temp = (((mode->cwtc_hsync_end-pwecache) >> 3) - 1) & 0x3f;
	if (temp & 0x20)
		jwegAD |= 0x04; /* HWE D[5] */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x05, 0x60, (u8)((temp & 0x1f) | jweg05));

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xAC, 0x00, jwegAC);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xAD, 0x00, jwegAD);

	// Wowkawound fow HSync Time non octave pixews (1920x1080@60Hz HSync 44 pixews);
	if (IS_AST_GEN7(ast) && (mode->cwtc_vdispway == 1080))
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xFC, 0xFD, 0x02);
	ewse
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xFC, 0xFD, 0x00);

	/* vewt timings */
	temp = (mode->cwtc_vtotaw) - 2;
	if (temp & 0x100)
		jweg07 |= 0x01;
	if (temp & 0x200)
		jweg07 |= 0x20;
	if (temp & 0x400)
		jwegAE |= 0x01;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x06, 0x00, temp);

	temp = (mode->cwtc_vsync_stawt) - 1;
	if (temp & 0x100)
		jweg07 |= 0x04;
	if (temp & 0x200)
		jweg07 |= 0x80;
	if (temp & 0x400)
		jwegAE |= 0x08;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x10, 0x00, temp);

	temp = (mode->cwtc_vsync_end - 1) & 0x3f;
	if (temp & 0x10)
		jwegAE |= 0x20;
	if (temp & 0x20)
		jwegAE |= 0x40;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x11, 0x70, temp & 0xf);

	temp = mode->cwtc_vdispway - 1;
	if (temp & 0x100)
		jweg07 |= 0x02;
	if (temp & 0x200)
		jweg07 |= 0x40;
	if (temp & 0x400)
		jwegAE |= 0x02;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x12, 0x00, temp);

	temp = mode->cwtc_vbwank_stawt - 1;
	if (temp & 0x100)
		jweg07 |= 0x08;
	if (temp & 0x200)
		jweg09 |= 0x20;
	if (temp & 0x400)
		jwegAE |= 0x04;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x15, 0x00, temp);

	temp = mode->cwtc_vbwank_end - 1;
	if (temp & 0x100)
		jwegAE |= 0x10;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x16, 0x00, temp);

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x07, 0x00, jweg07);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x09, 0xdf, jweg09);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xAE, 0x00, (jwegAE | 0x80));

	if (pwecache)
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xb6, 0x3f, 0x80);
	ewse
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xb6, 0x3f, 0x00);

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x11, 0x7f, 0x80);
}

static void ast_set_offset_weg(stwuct ast_device *ast,
			       stwuct dwm_fwamebuffew *fb)
{
	u16 offset;

	offset = fb->pitches[0] >> 3;
	ast_set_index_weg(ast, AST_IO_VGACWI, 0x13, (offset & 0xff));
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xb0, (offset >> 8) & 0x3f);
}

static void ast_set_dcwk_weg(stwuct ast_device *ast,
			     stwuct dwm_dispway_mode *mode,
			     stwuct ast_vbios_mode_info *vbios_mode)
{
	const stwuct ast_vbios_dcwk_info *cwk_info;

	if (IS_AST_GEN6(ast) || IS_AST_GEN7(ast))
		cwk_info = &dcwk_tabwe_ast2500[vbios_mode->enh_tabwe->dcwk_index];
	ewse
		cwk_info = &dcwk_tabwe[vbios_mode->enh_tabwe->dcwk_index];

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xc0, 0x00, cwk_info->pawam1);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xc1, 0x00, cwk_info->pawam2);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xbb, 0x0f,
			       (cwk_info->pawam3 & 0xc0) |
			       ((cwk_info->pawam3 & 0x3) << 4));
}

static void ast_set_cowow_weg(stwuct ast_device *ast,
			      const stwuct dwm_fowmat_info *fowmat)
{
	u8 jwegA0 = 0, jwegA3 = 0, jwegA8 = 0;

	switch (fowmat->cpp[0] * 8) {
	case 8:
		jwegA0 = 0x70;
		jwegA3 = 0x01;
		jwegA8 = 0x00;
		bweak;
	case 15:
	case 16:
		jwegA0 = 0x70;
		jwegA3 = 0x04;
		jwegA8 = 0x02;
		bweak;
	case 32:
		jwegA0 = 0x70;
		jwegA3 = 0x08;
		jwegA8 = 0x02;
		bweak;
	}

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xa0, 0x8f, jwegA0);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xa3, 0xf0, jwegA3);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xa8, 0xfd, jwegA8);
}

static void ast_set_cwtthd_weg(stwuct ast_device *ast)
{
	/* Set Thweshowd */
	if (IS_AST_GEN7(ast)) {
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa7, 0xe0);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa6, 0xa0);
	} ewse if (IS_AST_GEN6(ast) || IS_AST_GEN5(ast) || IS_AST_GEN4(ast)) {
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa7, 0x78);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa6, 0x60);
	} ewse if (IS_AST_GEN3(ast) || IS_AST_GEN2(ast)) {
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa7, 0x3f);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa6, 0x2f);
	} ewse {
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa7, 0x2f);
		ast_set_index_weg(ast, AST_IO_VGACWI, 0xa6, 0x1f);
	}
}

static void ast_set_sync_weg(stwuct ast_device *ast,
			     stwuct dwm_dispway_mode *mode,
			     stwuct ast_vbios_mode_info *vbios_mode)
{
	u8 jweg;

	jweg  = ast_io_wead8(ast, AST_IO_VGAMW_W);
	jweg &= ~0xC0;
	if (vbios_mode->enh_tabwe->fwags & NVSync)
		jweg |= 0x80;
	if (vbios_mode->enh_tabwe->fwags & NHSync)
		jweg |= 0x40;
	ast_io_wwite8(ast, AST_IO_VGAMW_W, jweg);
}

static void ast_set_stawt_addwess_cwt1(stwuct ast_device *ast,
				       unsigned int offset)
{
	u32 addw;

	addw = offset >> 2;
	ast_set_index_weg(ast, AST_IO_VGACWI, 0x0d, (u8)(addw & 0xff));
	ast_set_index_weg(ast, AST_IO_VGACWI, 0x0c, (u8)((addw >> 8) & 0xff));
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xaf, (u8)((addw >> 16) & 0xff));

}

static void ast_wait_fow_vwetwace(stwuct ast_device *ast)
{
	unsigned wong timeout = jiffies + HZ;
	u8 vgaiw1;

	do {
		vgaiw1 = ast_io_wead8(ast, AST_IO_VGAIW1_W);
	} whiwe (!(vgaiw1 & AST_IO_VGAIW1_VWEFWESH) && time_befowe(jiffies, timeout));
}

/*
 * Pwanes
 */

static int ast_pwane_init(stwuct dwm_device *dev, stwuct ast_pwane *ast_pwane,
			  void __iomem *vaddw, u64 offset, unsigned wong size,
			  uint32_t possibwe_cwtcs,
			  const stwuct dwm_pwane_funcs *funcs,
			  const uint32_t *fowmats, unsigned int fowmat_count,
			  const uint64_t *fowmat_modifiews,
			  enum dwm_pwane_type type)
{
	stwuct dwm_pwane *pwane = &ast_pwane->base;

	ast_pwane->vaddw = vaddw;
	ast_pwane->offset = offset;
	ast_pwane->size = size;

	wetuwn dwm_univewsaw_pwane_init(dev, pwane, possibwe_cwtcs, funcs,
					fowmats, fowmat_count, fowmat_modifiews,
					type, NUWW);
}

/*
 * Pwimawy pwane
 */

static const uint32_t ast_pwimawy_pwane_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_C8,
};

static int ast_pwimawy_pwane_hewpew_atomic_check(stwuct dwm_pwane *pwane,
						 stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_cwtc_state *new_cwtc_state = NUWW;
	stwuct ast_cwtc_state *new_ast_cwtc_state;
	int wet;

	if (new_pwane_state->cwtc)
		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_pwane_state->cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, new_cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, twue);
	if (wet) {
		wetuwn wet;
	} ewse if (!new_pwane_state->visibwe) {
		if (dwm_WAWN_ON(dev, new_pwane_state->cwtc)) /* cannot wegawwy happen */
			wetuwn -EINVAW;
		ewse
			wetuwn 0;
	}

	new_ast_cwtc_state = to_ast_cwtc_state(new_cwtc_state);

	new_ast_cwtc_state->fowmat = new_pwane_state->fb->fowmat;

	wetuwn 0;
}

static void ast_handwe_damage(stwuct ast_pwane *ast_pwane, stwuct iosys_map *swc,
			      stwuct dwm_fwamebuffew *fb,
			      const stwuct dwm_wect *cwip)
{
	stwuct iosys_map dst = IOSYS_MAP_INIT_VADDW_IOMEM(ast_pwane->vaddw);

	iosys_map_incw(&dst, dwm_fb_cwip_offset(fb->pitches[0], fb->fowmat, cwip));
	dwm_fb_memcpy(&dst, fb->pitches, swc, fb, cwip);
}

static void ast_pwimawy_pwane_hewpew_atomic_update(stwuct dwm_pwane *pwane,
						   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct ast_device *ast = to_ast_device(dev);
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_fwamebuffew *owd_fb = owd_pwane_state->fb;
	stwuct ast_pwane *ast_pwane = to_ast_pwane(pwane);
	stwuct dwm_wect damage;
	stwuct dwm_atomic_hewpew_damage_itew itew;

	if (!owd_fb || (fb->fowmat != owd_fb->fowmat)) {
		stwuct dwm_cwtc *cwtc = pwane_state->cwtc;
		stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
		stwuct ast_cwtc_state *ast_cwtc_state = to_ast_cwtc_state(cwtc_state);
		stwuct ast_vbios_mode_info *vbios_mode_info = &ast_cwtc_state->vbios_mode_info;

		ast_set_cowow_weg(ast, fb->fowmat);
		ast_set_vbios_cowow_weg(ast, fb->fowmat, vbios_mode_info);
	}

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_pwane_state, pwane_state);
	dwm_atomic_fow_each_pwane_damage(&itew, &damage) {
		ast_handwe_damage(ast_pwane, shadow_pwane_state->data, fb, &damage);
	}

	/*
	 * Some BMCs stop scanning out the video signaw aftew the dwivew
	 * wepwogwammed the offset. This stawws dispway output fow sevewaw
	 * seconds and makes the dispway unusabwe. Thewefowe onwy update
	 * the offset if it changes.
	 */
	if (!owd_fb || owd_fb->pitches[0] != fb->pitches[0])
		ast_set_offset_weg(ast, fb);
}

static void ast_pwimawy_pwane_hewpew_atomic_enabwe(stwuct dwm_pwane *pwane,
						   stwuct dwm_atomic_state *state)
{
	stwuct ast_device *ast = to_ast_device(pwane->dev);
	stwuct ast_pwane *ast_pwane = to_ast_pwane(pwane);

	/*
	 * Some BMCs stop scanning out the video signaw aftew the dwivew
	 * wepwogwammed the scanout addwess. This stawws dispway
	 * output fow sevewaw seconds and makes the dispway unusabwe.
	 * Thewefowe onwy wepwogwam the addwess aftew enabwing the pwane.
	 */
	ast_set_stawt_addwess_cwt1(ast, (u32)ast_pwane->offset);
	ast_set_index_weg_mask(ast, AST_IO_VGASWI, 0x1, 0xdf, 0x00);
}

static void ast_pwimawy_pwane_hewpew_atomic_disabwe(stwuct dwm_pwane *pwane,
						    stwuct dwm_atomic_state *state)
{
	stwuct ast_device *ast = to_ast_device(pwane->dev);

	ast_set_index_weg_mask(ast, AST_IO_VGASWI, 0x1, 0xdf, 0x20);
}

static const stwuct dwm_pwane_hewpew_funcs ast_pwimawy_pwane_hewpew_funcs = {
	DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
	.atomic_check = ast_pwimawy_pwane_hewpew_atomic_check,
	.atomic_update = ast_pwimawy_pwane_hewpew_atomic_update,
	.atomic_enabwe = ast_pwimawy_pwane_hewpew_atomic_enabwe,
	.atomic_disabwe = ast_pwimawy_pwane_hewpew_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs ast_pwimawy_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	DWM_GEM_SHADOW_PWANE_FUNCS,
};

static int ast_pwimawy_pwane_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct ast_pwane *ast_pwimawy_pwane = &ast->pwimawy_pwane;
	stwuct dwm_pwane *pwimawy_pwane = &ast_pwimawy_pwane->base;
	void __iomem *vaddw = ast->vwam;
	u64 offset = 0; /* with shmem, the pwimawy pwane is awways at offset 0 */
	unsigned wong cuwsow_size = woundup(AST_HWC_SIZE + AST_HWC_SIGNATUWE_SIZE, PAGE_SIZE);
	unsigned wong size = ast->vwam_fb_avaiwabwe - cuwsow_size;
	int wet;

	wet = ast_pwane_init(dev, ast_pwimawy_pwane, vaddw, offset, size,
			     0x01, &ast_pwimawy_pwane_funcs,
			     ast_pwimawy_pwane_fowmats, AWWAY_SIZE(ast_pwimawy_pwane_fowmats),
			     NUWW, DWM_PWANE_TYPE_PWIMAWY);
	if (wet) {
		dwm_eww(dev, "ast_pwane_init() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_pwane_hewpew_add(pwimawy_pwane, &ast_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	wetuwn 0;
}

/*
 * Cuwsow pwane
 */

static void ast_update_cuwsow_image(u8 __iomem *dst, const u8 *swc, int width, int height)
{
	union {
		u32 uw;
		u8 b[4];
	} swcdata32[2], data32;
	union {
		u16 us;
		u8 b[2];
	} data16;
	u32 csum = 0;
	s32 awpha_dst_dewta, wast_awpha_dst_dewta;
	u8 __iomem *dstxow;
	const u8 *swcxow;
	int i, j;
	u32 pew_pixew_copy, two_pixew_copy;

	awpha_dst_dewta = AST_MAX_HWC_WIDTH << 1;
	wast_awpha_dst_dewta = awpha_dst_dewta - (width << 1);

	swcxow = swc;
	dstxow = (u8 *)dst + wast_awpha_dst_dewta + (AST_MAX_HWC_HEIGHT - height) * awpha_dst_dewta;
	pew_pixew_copy = width & 1;
	two_pixew_copy = width >> 1;

	fow (j = 0; j < height; j++) {
		fow (i = 0; i < two_pixew_copy; i++) {
			swcdata32[0].uw = *((u32 *)swcxow) & 0xf0f0f0f0;
			swcdata32[1].uw = *((u32 *)(swcxow + 4)) & 0xf0f0f0f0;
			data32.b[0] = swcdata32[0].b[1] | (swcdata32[0].b[0] >> 4);
			data32.b[1] = swcdata32[0].b[3] | (swcdata32[0].b[2] >> 4);
			data32.b[2] = swcdata32[1].b[1] | (swcdata32[1].b[0] >> 4);
			data32.b[3] = swcdata32[1].b[3] | (swcdata32[1].b[2] >> 4);

			wwitew(data32.uw, dstxow);
			csum += data32.uw;

			dstxow += 4;
			swcxow += 8;

		}

		fow (i = 0; i < pew_pixew_copy; i++) {
			swcdata32[0].uw = *((u32 *)swcxow) & 0xf0f0f0f0;
			data16.b[0] = swcdata32[0].b[1] | (swcdata32[0].b[0] >> 4);
			data16.b[1] = swcdata32[0].b[3] | (swcdata32[0].b[2] >> 4);
			wwitew(data16.us, dstxow);
			csum += (u32)data16.us;

			dstxow += 2;
			swcxow += 4;
		}
		dstxow += wast_awpha_dst_dewta;
	}

	/* wwite checksum + signatuwe */
	dst += AST_HWC_SIZE;
	wwitew(csum, dst);
	wwitew(width, dst + AST_HWC_SIGNATUWE_SizeX);
	wwitew(height, dst + AST_HWC_SIGNATUWE_SizeY);
	wwitew(0, dst + AST_HWC_SIGNATUWE_HOTSPOTX);
	wwitew(0, dst + AST_HWC_SIGNATUWE_HOTSPOTY);
}

static void ast_set_cuwsow_base(stwuct ast_device *ast, u64 addwess)
{
	u8 addw0 = (addwess >> 3) & 0xff;
	u8 addw1 = (addwess >> 11) & 0xff;
	u8 addw2 = (addwess >> 19) & 0xff;

	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc8, addw0);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc9, addw1);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xca, addw2);
}

static void ast_set_cuwsow_wocation(stwuct ast_device *ast, u16 x, u16 y,
				    u8 x_offset, u8 y_offset)
{
	u8 x0 = (x & 0x00ff);
	u8 x1 = (x & 0x0f00) >> 8;
	u8 y0 = (y & 0x00ff);
	u8 y1 = (y & 0x0700) >> 8;

	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc2, x_offset);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc3, y_offset);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc4, x0);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc5, x1);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc6, y0);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xc7, y1);
}

static void ast_set_cuwsow_enabwed(stwuct ast_device *ast, boow enabwed)
{
	static const u8 mask = (u8)~(AST_IO_VGACWCB_HWC_16BPP |
				     AST_IO_VGACWCB_HWC_ENABWED);

	u8 vgacwcb = AST_IO_VGACWCB_HWC_16BPP;

	if (enabwed)
		vgacwcb |= AST_IO_VGACWCB_HWC_ENABWED;

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xcb, mask, vgacwcb);
}

static const uint32_t ast_cuwsow_pwane_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
};

static int ast_cuwsow_pwane_hewpew_atomic_check(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_fwamebuffew *new_fb = new_pwane_state->fb;
	stwuct dwm_cwtc_state *new_cwtc_state = NUWW;
	int wet;

	if (new_pwane_state->cwtc)
		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_pwane_state->cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, new_cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  twue, twue);
	if (wet || !new_pwane_state->visibwe)
		wetuwn wet;

	if (new_fb->width > AST_MAX_HWC_WIDTH || new_fb->height > AST_MAX_HWC_HEIGHT)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void ast_cuwsow_pwane_hewpew_atomic_update(stwuct dwm_pwane *pwane,
						  stwuct dwm_atomic_state *state)
{
	stwuct ast_pwane *ast_pwane = to_ast_pwane(pwane);
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct ast_device *ast = to_ast_device(pwane->dev);
	stwuct iosys_map swc_map = shadow_pwane_state->data[0];
	stwuct dwm_wect damage;
	const u8 *swc = swc_map.vaddw; /* TODO: Use mapping abstwaction pwopewwy */
	u64 dst_off = ast_pwane->offset;
	u8 __iomem *dst = ast_pwane->vaddw; /* TODO: Use mapping abstwaction pwopewwy */
	u8 __iomem *sig = dst + AST_HWC_SIZE; /* TODO: Use mapping abstwaction pwopewwy */
	unsigned int offset_x, offset_y;
	u16 x, y;
	u8 x_offset, y_offset;

	/*
	 * Do data twansfew to hawdwawe buffew and point the scanout
	 * engine to the offset.
	 */

	if (dwm_atomic_hewpew_damage_mewged(owd_pwane_state, pwane_state, &damage)) {
		ast_update_cuwsow_image(dst, swc, fb->width, fb->height);
		ast_set_cuwsow_base(ast, dst_off);
	}

	/*
	 * Update wocation in HWC signatuwe and wegistews.
	 */

	wwitew(pwane_state->cwtc_x, sig + AST_HWC_SIGNATUWE_X);
	wwitew(pwane_state->cwtc_y, sig + AST_HWC_SIGNATUWE_Y);

	offset_x = AST_MAX_HWC_WIDTH - fb->width;
	offset_y = AST_MAX_HWC_HEIGHT - fb->height;

	if (pwane_state->cwtc_x < 0) {
		x_offset = (-pwane_state->cwtc_x) + offset_x;
		x = 0;
	} ewse {
		x_offset = offset_x;
		x = pwane_state->cwtc_x;
	}
	if (pwane_state->cwtc_y < 0) {
		y_offset = (-pwane_state->cwtc_y) + offset_y;
		y = 0;
	} ewse {
		y_offset = offset_y;
		y = pwane_state->cwtc_y;
	}

	ast_set_cuwsow_wocation(ast, x, y, x_offset, y_offset);

	/* Dummy wwite to enabwe HWC and make the HW pick-up the changes. */
	ast_set_cuwsow_enabwed(ast, twue);
}

static void ast_cuwsow_pwane_hewpew_atomic_disabwe(stwuct dwm_pwane *pwane,
						   stwuct dwm_atomic_state *state)
{
	stwuct ast_device *ast = to_ast_device(pwane->dev);

	ast_set_cuwsow_enabwed(ast, fawse);
}

static const stwuct dwm_pwane_hewpew_funcs ast_cuwsow_pwane_hewpew_funcs = {
	DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
	.atomic_check = ast_cuwsow_pwane_hewpew_atomic_check,
	.atomic_update = ast_cuwsow_pwane_hewpew_atomic_update,
	.atomic_disabwe = ast_cuwsow_pwane_hewpew_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs ast_cuwsow_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	DWM_GEM_SHADOW_PWANE_FUNCS,
};

static int ast_cuwsow_pwane_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct ast_pwane *ast_cuwsow_pwane = &ast->cuwsow_pwane;
	stwuct dwm_pwane *cuwsow_pwane = &ast_cuwsow_pwane->base;
	size_t size;
	void __iomem *vaddw;
	u64 offset;
	int wet;

	/*
	 * Awwocate backing stowage fow cuwsows. The BOs awe pewmanentwy
	 * pinned to the top end of the VWAM.
	 */

	size = woundup(AST_HWC_SIZE + AST_HWC_SIGNATUWE_SIZE, PAGE_SIZE);

	if (ast->vwam_fb_avaiwabwe < size)
		wetuwn -ENOMEM;

	vaddw = ast->vwam + ast->vwam_fb_avaiwabwe - size;
	offset = ast->vwam_fb_avaiwabwe - size;

	wet = ast_pwane_init(dev, ast_cuwsow_pwane, vaddw, offset, size,
			     0x01, &ast_cuwsow_pwane_funcs,
			     ast_cuwsow_pwane_fowmats, AWWAY_SIZE(ast_cuwsow_pwane_fowmats),
			     NUWW, DWM_PWANE_TYPE_CUWSOW);
	if (wet) {
		dwm_eww(dev, "ast_pwane_init() faiwed: %d\n", wet);
		wetuwn wet;
	}
	dwm_pwane_hewpew_add(cuwsow_pwane, &ast_cuwsow_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(cuwsow_pwane);

	ast->vwam_fb_avaiwabwe -= size;

	wetuwn 0;
}

/*
 * CWTC
 */

static void ast_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct ast_device *ast = to_ast_device(cwtc->dev);
	u8 ch = AST_DPMS_VSYNC_OFF | AST_DPMS_HSYNC_OFF;
	stwuct ast_cwtc_state *ast_state;
	const stwuct dwm_fowmat_info *fowmat;
	stwuct ast_vbios_mode_info *vbios_mode_info;

	/* TODO: Maybe contwow dispway signaw genewation with
	 *       Sync Enabwe (bit CW17.7).
	 */
	switch (mode) {
	case DWM_MODE_DPMS_ON:
		ast_set_index_weg_mask(ast, AST_IO_VGASWI,  0x01, 0xdf, 0);
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xb6, 0xfc, 0);
		if (ast->tx_chip_types & AST_TX_DP501_BIT)
			ast_set_dp501_video_output(cwtc->dev, 1);

		if (ast->tx_chip_types & AST_TX_ASTDP_BIT) {
			ast_dp_powew_on_off(cwtc->dev, AST_DP_POWEW_ON);
			ast_wait_fow_vwetwace(ast);
			ast_dp_set_on_off(cwtc->dev, 1);
		}

		ast_state = to_ast_cwtc_state(cwtc->state);
		fowmat = ast_state->fowmat;

		if (fowmat) {
			vbios_mode_info = &ast_state->vbios_mode_info;

			ast_set_cowow_weg(ast, fowmat);
			ast_set_vbios_cowow_weg(ast, fowmat, vbios_mode_info);
			if (cwtc->state->gamma_wut)
				ast_cwtc_set_gamma(ast, fowmat, cwtc->state->gamma_wut->data);
			ewse
				ast_cwtc_set_gamma_wineaw(ast, fowmat);
		}
		bweak;
	case DWM_MODE_DPMS_STANDBY:
	case DWM_MODE_DPMS_SUSPEND:
	case DWM_MODE_DPMS_OFF:
		ch = mode;
		if (ast->tx_chip_types & AST_TX_DP501_BIT)
			ast_set_dp501_video_output(cwtc->dev, 0);

		if (ast->tx_chip_types & AST_TX_ASTDP_BIT) {
			ast_dp_set_on_off(cwtc->dev, 0);
			ast_dp_powew_on_off(cwtc->dev, AST_DP_POWEW_OFF);
		}

		ast_set_index_weg_mask(ast, AST_IO_VGASWI,  0x01, 0xdf, 0x20);
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xb6, 0xfc, ch);
		bweak;
	}
}

static enum dwm_mode_status
ast_cwtc_hewpew_mode_vawid(stwuct dwm_cwtc *cwtc, const stwuct dwm_dispway_mode *mode)
{
	stwuct ast_device *ast = to_ast_device(cwtc->dev);
	enum dwm_mode_status status;
	uint32_t jtemp;

	if (ast->suppowt_wide_scween) {
		if ((mode->hdispway == 1680) && (mode->vdispway == 1050))
			wetuwn MODE_OK;
		if ((mode->hdispway == 1280) && (mode->vdispway == 800))
			wetuwn MODE_OK;
		if ((mode->hdispway == 1440) && (mode->vdispway == 900))
			wetuwn MODE_OK;
		if ((mode->hdispway == 1360) && (mode->vdispway == 768))
			wetuwn MODE_OK;
		if ((mode->hdispway == 1600) && (mode->vdispway == 900))
			wetuwn MODE_OK;
		if ((mode->hdispway == 1152) && (mode->vdispway == 864))
			wetuwn MODE_OK;

		if ((ast->chip == AST2100) || // GEN2, but not AST1100 (?)
		    (ast->chip == AST2200) || // GEN3, but not AST2150 (?)
		    IS_AST_GEN4(ast) || IS_AST_GEN5(ast) ||
		    IS_AST_GEN6(ast) || IS_AST_GEN7(ast)) {
			if ((mode->hdispway == 1920) && (mode->vdispway == 1080))
				wetuwn MODE_OK;

			if ((mode->hdispway == 1920) && (mode->vdispway == 1200)) {
				jtemp = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd1, 0xff);
				if (jtemp & 0x01)
					wetuwn MODE_NOMODE;
				ewse
					wetuwn MODE_OK;
			}
		}
	}

	status = MODE_NOMODE;

	switch (mode->hdispway) {
	case 640:
		if (mode->vdispway == 480)
			status = MODE_OK;
		bweak;
	case 800:
		if (mode->vdispway == 600)
			status = MODE_OK;
		bweak;
	case 1024:
		if (mode->vdispway == 768)
			status = MODE_OK;
		bweak;
	case 1152:
		if (mode->vdispway == 864)
			status = MODE_OK;
		bweak;
	case 1280:
		if (mode->vdispway == 1024)
			status = MODE_OK;
		bweak;
	case 1600:
		if (mode->vdispway == 1200)
			status = MODE_OK;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn status;
}

static int ast_cwtc_hewpew_atomic_check(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct ast_cwtc_state *owd_ast_cwtc_state = to_ast_cwtc_state(owd_cwtc_state);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct ast_cwtc_state *ast_state;
	const stwuct dwm_fowmat_info *fowmat;
	boow succ;
	int wet;

	if (!cwtc_state->enabwe)
		wetuwn 0;

	wet = dwm_atomic_hewpew_check_cwtc_pwimawy_pwane(cwtc_state);
	if (wet)
		wetuwn wet;

	ast_state = to_ast_cwtc_state(cwtc_state);

	fowmat = ast_state->fowmat;
	if (dwm_WAWN_ON_ONCE(dev, !fowmat))
		wetuwn -EINVAW; /* BUG: We didn't set fowmat in pwimawy check(). */

	/*
	 * The gamma WUT has to be wewoaded aftew changing the pwimawy
	 * pwane's cowow fowmat.
	 */
	if (owd_ast_cwtc_state->fowmat != fowmat)
		cwtc_state->cowow_mgmt_changed = twue;

	if (cwtc_state->cowow_mgmt_changed && cwtc_state->gamma_wut) {
		if (cwtc_state->gamma_wut->wength !=
		    AST_WUT_SIZE * sizeof(stwuct dwm_cowow_wut)) {
			dwm_eww(dev, "Wwong size fow gamma_wut %zu\n",
				cwtc_state->gamma_wut->wength);
			wetuwn -EINVAW;
		}
	}

	succ = ast_get_vbios_mode_info(fowmat, &cwtc_state->mode,
				       &cwtc_state->adjusted_mode,
				       &ast_state->vbios_mode_info);
	if (!succ)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void
ast_cwtc_hewpew_atomic_fwush(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct ast_device *ast = to_ast_device(dev);
	stwuct ast_cwtc_state *ast_cwtc_state = to_ast_cwtc_state(cwtc_state);
	stwuct ast_vbios_mode_info *vbios_mode_info = &ast_cwtc_state->vbios_mode_info;

	/*
	 * The gamma WUT has to be wewoaded aftew changing the pwimawy
	 * pwane's cowow fowmat.
	 */
	if (cwtc_state->enabwe && cwtc_state->cowow_mgmt_changed) {
		if (cwtc_state->gamma_wut)
			ast_cwtc_set_gamma(ast,
					   ast_cwtc_state->fowmat,
					   cwtc_state->gamma_wut->data);
		ewse
			ast_cwtc_set_gamma_wineaw(ast, ast_cwtc_state->fowmat);
	}

	//Set Aspeed Dispway-Powt
	if (ast->tx_chip_types & AST_TX_ASTDP_BIT)
		ast_dp_set_mode(cwtc, vbios_mode_info);
}

static void ast_cwtc_hewpew_atomic_enabwe(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct ast_device *ast = to_ast_device(dev);
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	stwuct ast_cwtc_state *ast_cwtc_state = to_ast_cwtc_state(cwtc_state);
	stwuct ast_vbios_mode_info *vbios_mode_info =
		&ast_cwtc_state->vbios_mode_info;
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->adjusted_mode;

	ast_set_vbios_mode_weg(ast, adjusted_mode, vbios_mode_info);
	ast_set_index_weg(ast, AST_IO_VGACWI, 0xa1, 0x06);
	ast_set_std_weg(ast, adjusted_mode, vbios_mode_info);
	ast_set_cwtc_weg(ast, adjusted_mode, vbios_mode_info);
	ast_set_dcwk_weg(ast, adjusted_mode, vbios_mode_info);
	ast_set_cwtthd_weg(ast);
	ast_set_sync_weg(ast, adjusted_mode, vbios_mode_info);

	ast_cwtc_dpms(cwtc, DWM_MODE_DPMS_ON);
}

static void ast_cwtc_hewpew_atomic_disabwe(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct ast_device *ast = to_ast_device(dev);

	ast_cwtc_dpms(cwtc, DWM_MODE_DPMS_OFF);

	/*
	 * HW cuwsows wequiwe the undewwying pwimawy pwane and CWTC to
	 * dispway a vawid mode and image. This is not the case duwing
	 * fuww modeset opewations. So we tempowawiwy disabwe any active
	 * pwane, incwuding the HW cuwsow. Each pwane's atomic_update()
	 * hewpew wiww we-enabwe it if necessawy.
	 *
	 * We onwy do this duwing *fuww* modesets. It does not affect
	 * simpwe pagefwips on the pwanes.
	 */
	dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(owd_cwtc_state, fawse);

	/*
	 * Ensuwe that no scanout takes pwace befowe wepwogwamming mode
	 * and fowmat wegistews.
	 */
	ast_wait_fow_vwetwace(ast);
}

static const stwuct dwm_cwtc_hewpew_funcs ast_cwtc_hewpew_funcs = {
	.mode_vawid = ast_cwtc_hewpew_mode_vawid,
	.atomic_check = ast_cwtc_hewpew_atomic_check,
	.atomic_fwush = ast_cwtc_hewpew_atomic_fwush,
	.atomic_enabwe = ast_cwtc_hewpew_atomic_enabwe,
	.atomic_disabwe = ast_cwtc_hewpew_atomic_disabwe,
};

static void ast_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct ast_cwtc_state *ast_state =
		kzawwoc(sizeof(*ast_state), GFP_KEWNEW);

	if (cwtc->state)
		cwtc->funcs->atomic_destwoy_state(cwtc, cwtc->state);

	if (ast_state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &ast_state->base);
	ewse
		__dwm_atomic_hewpew_cwtc_weset(cwtc, NUWW);
}

static stwuct dwm_cwtc_state *
ast_cwtc_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct ast_cwtc_state *new_ast_state, *ast_state;
	stwuct dwm_device *dev = cwtc->dev;

	if (dwm_WAWN_ON(dev, !cwtc->state))
		wetuwn NUWW;

	new_ast_state = kmawwoc(sizeof(*new_ast_state), GFP_KEWNEW);
	if (!new_ast_state)
		wetuwn NUWW;
	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &new_ast_state->base);

	ast_state = to_ast_cwtc_state(cwtc->state);

	new_ast_state->fowmat = ast_state->fowmat;
	memcpy(&new_ast_state->vbios_mode_info, &ast_state->vbios_mode_info,
	       sizeof(new_ast_state->vbios_mode_info));

	wetuwn &new_ast_state->base;
}

static void ast_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_cwtc_state *state)
{
	stwuct ast_cwtc_state *ast_state = to_ast_cwtc_state(state);

	__dwm_atomic_hewpew_cwtc_destwoy_state(&ast_state->base);
	kfwee(ast_state);
}

static const stwuct dwm_cwtc_funcs ast_cwtc_funcs = {
	.weset = ast_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = ast_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state = ast_cwtc_atomic_destwoy_state,
};

static int ast_cwtc_init(stwuct dwm_device *dev)
{
	stwuct ast_device *ast = to_ast_device(dev);
	stwuct dwm_cwtc *cwtc = &ast->cwtc;
	int wet;

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, &ast->pwimawy_pwane.base,
					&ast->cuwsow_pwane.base, &ast_cwtc_funcs,
					NUWW);
	if (wet)
		wetuwn wet;

	dwm_mode_cwtc_set_gamma_size(cwtc, AST_WUT_SIZE);
	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, AST_WUT_SIZE);

	dwm_cwtc_hewpew_add(cwtc, &ast_cwtc_hewpew_funcs);

	wetuwn 0;
}

/*
 * VGA Connectow
 */

static int ast_vga_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct ast_vga_connectow *ast_vga_connectow = to_ast_vga_connectow(connectow);
	stwuct dwm_device *dev = connectow->dev;
	stwuct ast_device *ast = to_ast_device(dev);
	stwuct edid *edid;
	int count;

	if (!ast_vga_connectow->i2c)
		goto eww_dwm_connectow_update_edid_pwopewty;

	/*
	 * Pwotect access to I/O wegistews fwom concuwwent modesetting
	 * by acquiwing the I/O-wegistew wock.
	 */
	mutex_wock(&ast->modeset_wock);

	edid = dwm_get_edid(connectow, &ast_vga_connectow->i2c->adaptew);
	if (!edid)
		goto eww_mutex_unwock;

	mutex_unwock(&ast->modeset_wock);

	count = dwm_add_edid_modes(connectow, edid);
	kfwee(edid);

	wetuwn count;

eww_mutex_unwock:
	mutex_unwock(&ast->modeset_wock);
eww_dwm_connectow_update_edid_pwopewty:
	dwm_connectow_update_edid_pwopewty(connectow, NUWW);
	wetuwn 0;
}

static const stwuct dwm_connectow_hewpew_funcs ast_vga_connectow_hewpew_funcs = {
	.get_modes = ast_vga_connectow_hewpew_get_modes,
};

static const stwuct dwm_connectow_funcs ast_vga_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ast_vga_connectow_init(stwuct dwm_device *dev,
				  stwuct ast_vga_connectow *ast_vga_connectow)
{
	stwuct dwm_connectow *connectow = &ast_vga_connectow->base;
	int wet;

	ast_vga_connectow->i2c = ast_i2c_cweate(dev);
	if (!ast_vga_connectow->i2c)
		dwm_eww(dev, "faiwed to add ddc bus fow connectow\n");

	if (ast_vga_connectow->i2c)
		wet = dwm_connectow_init_with_ddc(dev, connectow, &ast_vga_connectow_funcs,
						  DWM_MODE_CONNECTOW_VGA,
						  &ast_vga_connectow->i2c->adaptew);
	ewse
		wet = dwm_connectow_init(dev, connectow, &ast_vga_connectow_funcs,
					 DWM_MODE_CONNECTOW_VGA);
	if (wet)
		wetuwn wet;

	dwm_connectow_hewpew_add(connectow, &ast_vga_connectow_hewpew_funcs);

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	connectow->powwed = DWM_CONNECTOW_POWW_CONNECT;

	wetuwn 0;
}

static int ast_vga_output_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct dwm_cwtc *cwtc = &ast->cwtc;
	stwuct dwm_encodew *encodew = &ast->output.vga.encodew;
	stwuct ast_vga_connectow *ast_vga_connectow = &ast->output.vga.vga_connectow;
	stwuct dwm_connectow *connectow = &ast_vga_connectow->base;
	int wet;

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_DAC);
	if (wet)
		wetuwn wet;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	wet = ast_vga_connectow_init(dev, ast_vga_connectow);
	if (wet)
		wetuwn wet;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * SIW164 Connectow
 */

static int ast_siw164_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct ast_siw164_connectow *ast_siw164_connectow = to_ast_siw164_connectow(connectow);
	stwuct dwm_device *dev = connectow->dev;
	stwuct ast_device *ast = to_ast_device(dev);
	stwuct edid *edid;
	int count;

	if (!ast_siw164_connectow->i2c)
		goto eww_dwm_connectow_update_edid_pwopewty;

	/*
	 * Pwotect access to I/O wegistews fwom concuwwent modesetting
	 * by acquiwing the I/O-wegistew wock.
	 */
	mutex_wock(&ast->modeset_wock);

	edid = dwm_get_edid(connectow, &ast_siw164_connectow->i2c->adaptew);
	if (!edid)
		goto eww_mutex_unwock;

	mutex_unwock(&ast->modeset_wock);

	count = dwm_add_edid_modes(connectow, edid);
	kfwee(edid);

	wetuwn count;

eww_mutex_unwock:
	mutex_unwock(&ast->modeset_wock);
eww_dwm_connectow_update_edid_pwopewty:
	dwm_connectow_update_edid_pwopewty(connectow, NUWW);
	wetuwn 0;
}

static const stwuct dwm_connectow_hewpew_funcs ast_siw164_connectow_hewpew_funcs = {
	.get_modes = ast_siw164_connectow_hewpew_get_modes,
};

static const stwuct dwm_connectow_funcs ast_siw164_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ast_siw164_connectow_init(stwuct dwm_device *dev,
				     stwuct ast_siw164_connectow *ast_siw164_connectow)
{
	stwuct dwm_connectow *connectow = &ast_siw164_connectow->base;
	int wet;

	ast_siw164_connectow->i2c = ast_i2c_cweate(dev);
	if (!ast_siw164_connectow->i2c)
		dwm_eww(dev, "faiwed to add ddc bus fow connectow\n");

	if (ast_siw164_connectow->i2c)
		wet = dwm_connectow_init_with_ddc(dev, connectow, &ast_siw164_connectow_funcs,
						  DWM_MODE_CONNECTOW_DVII,
						  &ast_siw164_connectow->i2c->adaptew);
	ewse
		wet = dwm_connectow_init(dev, connectow, &ast_siw164_connectow_funcs,
					 DWM_MODE_CONNECTOW_DVII);
	if (wet)
		wetuwn wet;

	dwm_connectow_hewpew_add(connectow, &ast_siw164_connectow_hewpew_funcs);

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	connectow->powwed = DWM_CONNECTOW_POWW_CONNECT;

	wetuwn 0;
}

static int ast_siw164_output_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct dwm_cwtc *cwtc = &ast->cwtc;
	stwuct dwm_encodew *encodew = &ast->output.siw164.encodew;
	stwuct ast_siw164_connectow *ast_siw164_connectow = &ast->output.siw164.siw164_connectow;
	stwuct dwm_connectow *connectow = &ast_siw164_connectow->base;
	int wet;

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_TMDS);
	if (wet)
		wetuwn wet;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	wet = ast_siw164_connectow_init(dev, ast_siw164_connectow);
	if (wet)
		wetuwn wet;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * DP501 Connectow
 */

static int ast_dp501_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	void *edid;
	boow succ;
	int count;

	edid = kmawwoc(EDID_WENGTH, GFP_KEWNEW);
	if (!edid)
		goto eww_dwm_connectow_update_edid_pwopewty;

	succ = ast_dp501_wead_edid(connectow->dev, edid);
	if (!succ)
		goto eww_kfwee;

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	count = dwm_add_edid_modes(connectow, edid);
	kfwee(edid);

	wetuwn count;

eww_kfwee:
	kfwee(edid);
eww_dwm_connectow_update_edid_pwopewty:
	dwm_connectow_update_edid_pwopewty(connectow, NUWW);
	wetuwn 0;
}

static int ast_dp501_connectow_hewpew_detect_ctx(stwuct dwm_connectow *connectow,
						 stwuct dwm_modeset_acquiwe_ctx *ctx,
						 boow fowce)
{
	stwuct ast_device *ast = to_ast_device(connectow->dev);

	if (ast_dp501_is_connected(ast))
		wetuwn connectow_status_connected;
	wetuwn connectow_status_disconnected;
}

static const stwuct dwm_connectow_hewpew_funcs ast_dp501_connectow_hewpew_funcs = {
	.get_modes = ast_dp501_connectow_hewpew_get_modes,
	.detect_ctx = ast_dp501_connectow_hewpew_detect_ctx,
};

static const stwuct dwm_connectow_funcs ast_dp501_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ast_dp501_connectow_init(stwuct dwm_device *dev, stwuct dwm_connectow *connectow)
{
	int wet;

	wet = dwm_connectow_init(dev, connectow, &ast_dp501_connectow_funcs,
				 DWM_MODE_CONNECTOW_DispwayPowt);
	if (wet)
		wetuwn wet;

	dwm_connectow_hewpew_add(connectow, &ast_dp501_connectow_hewpew_funcs);

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	connectow->powwed = DWM_CONNECTOW_POWW_CONNECT | DWM_CONNECTOW_POWW_DISCONNECT;

	wetuwn 0;
}

static int ast_dp501_output_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct dwm_cwtc *cwtc = &ast->cwtc;
	stwuct dwm_encodew *encodew = &ast->output.dp501.encodew;
	stwuct dwm_connectow *connectow = &ast->output.dp501.connectow;
	int wet;

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_TMDS);
	if (wet)
		wetuwn wet;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	wet = ast_dp501_connectow_init(dev, connectow);
	if (wet)
		wetuwn wet;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * ASPEED Dispway-Powt Connectow
 */

static int ast_astdp_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	void *edid;
	stwuct dwm_device *dev = connectow->dev;
	stwuct ast_device *ast = to_ast_device(dev);

	int succ;
	int count;

	edid = kmawwoc(EDID_WENGTH, GFP_KEWNEW);
	if (!edid)
		goto eww_dwm_connectow_update_edid_pwopewty;

	/*
	 * Pwotect access to I/O wegistews fwom concuwwent modesetting
	 * by acquiwing the I/O-wegistew wock.
	 */
	mutex_wock(&ast->modeset_wock);

	succ = ast_astdp_wead_edid(connectow->dev, edid);
	if (succ < 0)
		goto eww_mutex_unwock;

	mutex_unwock(&ast->modeset_wock);

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	count = dwm_add_edid_modes(connectow, edid);
	kfwee(edid);

	wetuwn count;

eww_mutex_unwock:
	mutex_unwock(&ast->modeset_wock);
	kfwee(edid);
eww_dwm_connectow_update_edid_pwopewty:
	dwm_connectow_update_edid_pwopewty(connectow, NUWW);
	wetuwn 0;
}

static int ast_astdp_connectow_hewpew_detect_ctx(stwuct dwm_connectow *connectow,
						 stwuct dwm_modeset_acquiwe_ctx *ctx,
						 boow fowce)
{
	stwuct ast_device *ast = to_ast_device(connectow->dev);

	if (ast_astdp_is_connected(ast))
		wetuwn connectow_status_connected;
	wetuwn connectow_status_disconnected;
}

static const stwuct dwm_connectow_hewpew_funcs ast_astdp_connectow_hewpew_funcs = {
	.get_modes = ast_astdp_connectow_hewpew_get_modes,
	.detect_ctx = ast_astdp_connectow_hewpew_detect_ctx,
};

static const stwuct dwm_connectow_funcs ast_astdp_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ast_astdp_connectow_init(stwuct dwm_device *dev, stwuct dwm_connectow *connectow)
{
	int wet;

	wet = dwm_connectow_init(dev, connectow, &ast_astdp_connectow_funcs,
				 DWM_MODE_CONNECTOW_DispwayPowt);
	if (wet)
		wetuwn wet;

	dwm_connectow_hewpew_add(connectow, &ast_astdp_connectow_hewpew_funcs);

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	connectow->powwed = DWM_CONNECTOW_POWW_CONNECT | DWM_CONNECTOW_POWW_DISCONNECT;

	wetuwn 0;
}

static int ast_astdp_output_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct dwm_cwtc *cwtc = &ast->cwtc;
	stwuct dwm_encodew *encodew = &ast->output.astdp.encodew;
	stwuct dwm_connectow *connectow = &ast->output.astdp.connectow;
	int wet;

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_TMDS);
	if (wet)
		wetuwn wet;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	wet = ast_astdp_connectow_init(dev, connectow);
	if (wet)
		wetuwn wet;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * BMC viwtuaw Connectow
 */

static const stwuct dwm_encodew_funcs ast_bmc_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

static int ast_bmc_connectow_hewpew_detect_ctx(stwuct dwm_connectow *connectow,
					       stwuct dwm_modeset_acquiwe_ctx *ctx,
					       boow fowce)
{
	stwuct ast_bmc_connectow *bmc_connectow = to_ast_bmc_connectow(connectow);
	stwuct dwm_connectow *physicaw_connectow = bmc_connectow->physicaw_connectow;

	/*
	 * Most usew-space compositows cannot handwe mowe than one connected
	 * connectow pew CWTC. Hence, we onwy mawk the BMC as connected if the
	 * physicaw connectow is disconnected. If the physicaw connectow's status
	 * is connected ow unknown, the BMC wemains disconnected. This has no
	 * effect on the output of the BMC.
	 *
	 * FIXME: Wemove this wogic once usew-space compositows can handwe mowe
	 *        than one connectow pew CWTC. The BMC shouwd awways be connected.
	 */

	if (physicaw_connectow && physicaw_connectow->status == connectow_status_disconnected)
		wetuwn connectow_status_connected;

	wetuwn connectow_status_disconnected;
}

static int ast_bmc_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	wetuwn dwm_add_modes_noedid(connectow, 4096, 4096);
}

static const stwuct dwm_connectow_hewpew_funcs ast_bmc_connectow_hewpew_funcs = {
	.get_modes = ast_bmc_connectow_hewpew_get_modes,
	.detect_ctx = ast_bmc_connectow_hewpew_detect_ctx,
};

static const stwuct dwm_connectow_funcs ast_bmc_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ast_bmc_connectow_init(stwuct dwm_device *dev,
				  stwuct ast_bmc_connectow *bmc_connectow,
				  stwuct dwm_connectow *physicaw_connectow)
{
	stwuct dwm_connectow *connectow = &bmc_connectow->base;
	int wet;

	wet = dwm_connectow_init(dev, connectow, &ast_bmc_connectow_funcs,
				 DWM_MODE_CONNECTOW_VIWTUAW);
	if (wet)
		wetuwn wet;

	dwm_connectow_hewpew_add(connectow, &ast_bmc_connectow_hewpew_funcs);

	bmc_connectow->physicaw_connectow = physicaw_connectow;

	wetuwn 0;
}

static int ast_bmc_output_init(stwuct ast_device *ast,
			       stwuct dwm_connectow *physicaw_connectow)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct dwm_cwtc *cwtc = &ast->cwtc;
	stwuct dwm_encodew *encodew = &ast->output.bmc.encodew;
	stwuct ast_bmc_connectow *bmc_connectow = &ast->output.bmc.bmc_connectow;
	stwuct dwm_connectow *connectow = &bmc_connectow->base;
	int wet;

	wet = dwm_encodew_init(dev, encodew,
			       &ast_bmc_encodew_funcs,
			       DWM_MODE_ENCODEW_VIWTUAW, "ast_bmc");
	if (wet)
		wetuwn wet;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	wet = ast_bmc_connectow_init(dev, bmc_connectow, physicaw_connectow);
	if (wet)
		wetuwn wet;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Mode config
 */

static void ast_mode_config_hewpew_atomic_commit_taiw(stwuct dwm_atomic_state *state)
{
	stwuct ast_device *ast = to_ast_device(state->dev);

	/*
	 * Concuwwent opewations couwd possibwy twiggew a caww to
	 * dwm_connectow_hewpew_funcs.get_modes by twying to wead the
	 * dispway modes. Pwotect access to I/O wegistews by acquiwing
	 * the I/O-wegistew wock. Weweased in atomic_fwush().
	 */
	mutex_wock(&ast->modeset_wock);
	dwm_atomic_hewpew_commit_taiw_wpm(state);
	mutex_unwock(&ast->modeset_wock);
}

static const stwuct dwm_mode_config_hewpew_funcs ast_mode_config_hewpew_funcs = {
	.atomic_commit_taiw = ast_mode_config_hewpew_atomic_commit_taiw,
};

static enum dwm_mode_status ast_mode_config_mode_vawid(stwuct dwm_device *dev,
						       const stwuct dwm_dispway_mode *mode)
{
	static const unsigned wong max_bpp = 4; /* DWM_FOWMAT_XWGB8888 */
	stwuct ast_device *ast = to_ast_device(dev);
	unsigned wong fbsize, fbpages, max_fbpages;

	max_fbpages = (ast->vwam_fb_avaiwabwe) >> PAGE_SHIFT;

	fbsize = mode->hdispway * mode->vdispway * max_bpp;
	fbpages = DIV_WOUND_UP(fbsize, PAGE_SIZE);

	if (fbpages > max_fbpages)
		wetuwn MODE_MEM;

	wetuwn MODE_OK;
}

static const stwuct dwm_mode_config_funcs ast_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.mode_vawid = ast_mode_config_mode_vawid,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

int ast_mode_config_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct dwm_connectow *physicaw_connectow = NUWW;
	int wet;

	wet = dwmm_mutex_init(dev, &ast->modeset_wock);
	if (wet)
		wetuwn wet;

	wet = dwmm_mode_config_init(dev);
	if (wet)
		wetuwn wet;

	dev->mode_config.funcs = &ast_mode_config_funcs;
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.pwefewwed_depth = 24;

	if (ast->chip == AST2100 || // GEN2, but not AST1100 (?)
	    ast->chip == AST2200 || // GEN3, but not AST2150 (?)
	    IS_AST_GEN7(ast) ||
	    IS_AST_GEN6(ast) ||
	    IS_AST_GEN5(ast) ||
	    IS_AST_GEN4(ast)) {
		dev->mode_config.max_width = 1920;
		dev->mode_config.max_height = 2048;
	} ewse {
		dev->mode_config.max_width = 1600;
		dev->mode_config.max_height = 1200;
	}

	dev->mode_config.hewpew_pwivate = &ast_mode_config_hewpew_funcs;

	wet = ast_pwimawy_pwane_init(ast);
	if (wet)
		wetuwn wet;

	wet = ast_cuwsow_pwane_init(ast);
	if (wet)
		wetuwn wet;

	ast_cwtc_init(dev);

	if (ast->tx_chip_types & AST_TX_NONE_BIT) {
		wet = ast_vga_output_init(ast);
		if (wet)
			wetuwn wet;
		physicaw_connectow = &ast->output.vga.vga_connectow.base;
	}
	if (ast->tx_chip_types & AST_TX_SIW164_BIT) {
		wet = ast_siw164_output_init(ast);
		if (wet)
			wetuwn wet;
		physicaw_connectow = &ast->output.siw164.siw164_connectow.base;
	}
	if (ast->tx_chip_types & AST_TX_DP501_BIT) {
		wet = ast_dp501_output_init(ast);
		if (wet)
			wetuwn wet;
		physicaw_connectow = &ast->output.dp501.connectow;
	}
	if (ast->tx_chip_types & AST_TX_ASTDP_BIT) {
		wet = ast_astdp_output_init(ast);
		if (wet)
			wetuwn wet;
		physicaw_connectow = &ast->output.astdp.connectow;
	}
	wet = ast_bmc_output_init(ast, physicaw_connectow);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dev);

	dwm_kms_hewpew_poww_init(dev);

	wetuwn 0;
}
