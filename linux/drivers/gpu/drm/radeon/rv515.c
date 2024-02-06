/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wv515_weg_safe.h"
#incwude "wv515d.h"

/* This fiwes gathew functions specifics to: wv515 */
static void wv515_gpu_init(stwuct wadeon_device *wdev);
int wv515_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

static const u32 cwtc_offsets[2] =
{
	0,
	AVIVO_D2CWTC_H_TOTAW - AVIVO_D1CWTC_H_TOTAW
};

void wv515_wing_stawt(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	int w;

	w = wadeon_wing_wock(wdev, wing, 64);
	if (w) {
		wetuwn;
	}
	wadeon_wing_wwite(wing, PACKET0(ISYNC_CNTW, 0));
	wadeon_wing_wwite(wing,
			  ISYNC_ANY2D_IDWE3D |
			  ISYNC_ANY3D_IDWE2D |
			  ISYNC_WAIT_IDWEGUI |
			  ISYNC_CPSCWATCH_IDWEGUI);
	wadeon_wing_wwite(wing, PACKET0(WAIT_UNTIW, 0));
	wadeon_wing_wwite(wing, WAIT_2D_IDWECWEAN | WAIT_3D_IDWECWEAN);
	wadeon_wing_wwite(wing, PACKET0(W300_DST_PIPE_CONFIG, 0));
	wadeon_wing_wwite(wing, W300_PIPE_AUTO_CONFIG);
	wadeon_wing_wwite(wing, PACKET0(GB_SEWECT, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(GB_ENABWE, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(W500_SU_WEG_DEST, 0));
	wadeon_wing_wwite(wing, (1 << wdev->num_gb_pipes) - 1);
	wadeon_wing_wwite(wing, PACKET0(VAP_INDEX_OFFSET, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(WB3D_DSTCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, WB3D_DC_FWUSH | WB3D_DC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(ZB_ZCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, ZC_FWUSH | ZC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(WAIT_UNTIW, 0));
	wadeon_wing_wwite(wing, WAIT_2D_IDWECWEAN | WAIT_3D_IDWECWEAN);
	wadeon_wing_wwite(wing, PACKET0(GB_AA_CONFIG, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(WB3D_DSTCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, WB3D_DC_FWUSH | WB3D_DC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(ZB_ZCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, ZC_FWUSH | ZC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(GB_MSPOS0, 0));
	wadeon_wing_wwite(wing,
			  ((6 << MS_X0_SHIFT) |
			   (6 << MS_Y0_SHIFT) |
			   (6 << MS_X1_SHIFT) |
			   (6 << MS_Y1_SHIFT) |
			   (6 << MS_X2_SHIFT) |
			   (6 << MS_Y2_SHIFT) |
			   (6 << MSBD0_Y_SHIFT) |
			   (6 << MSBD0_X_SHIFT)));
	wadeon_wing_wwite(wing, PACKET0(GB_MSPOS1, 0));
	wadeon_wing_wwite(wing,
			  ((6 << MS_X3_SHIFT) |
			   (6 << MS_Y3_SHIFT) |
			   (6 << MS_X4_SHIFT) |
			   (6 << MS_Y4_SHIFT) |
			   (6 << MS_X5_SHIFT) |
			   (6 << MS_Y5_SHIFT) |
			   (6 << MSBD1_SHIFT)));
	wadeon_wing_wwite(wing, PACKET0(GA_ENHANCE, 0));
	wadeon_wing_wwite(wing, GA_DEADWOCK_CNTW | GA_FASTSYNC_CNTW);
	wadeon_wing_wwite(wing, PACKET0(GA_POWY_MODE, 0));
	wadeon_wing_wwite(wing, FWONT_PTYPE_TWIANGE | BACK_PTYPE_TWIANGE);
	wadeon_wing_wwite(wing, PACKET0(GA_WOUND_MODE, 0));
	wadeon_wing_wwite(wing, GEOMETWY_WOUND_NEAWEST | COWOW_WOUND_NEAWEST);
	wadeon_wing_wwite(wing, PACKET0(0x20C8, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_unwock_commit(wdev, wing, fawse);
}

int wv515_mc_wait_fow_idwe(stwuct wadeon_device *wdev)
{
	unsigned i;
	uint32_t tmp;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32_MC(MC_STATUS);
		if (tmp & MC_STATUS_IDWE) {
			wetuwn 0;
		}
		udeway(1);
	}
	wetuwn -1;
}

void wv515_vga_wendew_disabwe(stwuct wadeon_device *wdev)
{
	WWEG32(W_000300_VGA_WENDEW_CONTWOW,
		WWEG32(W_000300_VGA_WENDEW_CONTWOW) & C_000300_VGA_VSTATUS_CNTW);
}

static void wv515_gpu_init(stwuct wadeon_device *wdev)
{
	unsigned pipe_sewect_cuwwent, gb_pipe_sewect, tmp;

	if (w100_gui_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait GUI idwe whiwe wesetting GPU. Bad things might happen.\n");
	}
	wv515_vga_wendew_disabwe(wdev);
	w420_pipes_init(wdev);
	gb_pipe_sewect = WWEG32(W400_GB_PIPE_SEWECT);
	tmp = WWEG32(W300_DST_PIPE_CONFIG);
	pipe_sewect_cuwwent = (tmp >> 2) & 3;
	tmp = (1 << pipe_sewect_cuwwent) |
	      (((gb_pipe_sewect >> 8) & 0xF) << 4);
	WWEG32_PWW(0x000D, tmp);
	if (w100_gui_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait GUI idwe whiwe wesetting GPU. Bad things might happen.\n");
	}
	if (wv515_mc_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait MC idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}
}

static void wv515_vwam_get_type(stwuct wadeon_device *wdev)
{
	uint32_t tmp;

	wdev->mc.vwam_width = 128;
	wdev->mc.vwam_is_ddw = twue;
	tmp = WWEG32_MC(WV515_MC_CNTW) & MEM_NUM_CHANNEWS_MASK;
	switch (tmp) {
	case 0:
		wdev->mc.vwam_width = 64;
		bweak;
	case 1:
		wdev->mc.vwam_width = 128;
		bweak;
	defauwt:
		wdev->mc.vwam_width = 128;
		bweak;
	}
}

static void wv515_mc_init(stwuct wadeon_device *wdev)
{

	wv515_vwam_get_type(wdev);
	w100_vwam_init_sizes(wdev);
	wadeon_vwam_wocation(wdev, &wdev->mc, 0);
	wdev->mc.gtt_base_awign = 0;
	if (!(wdev->fwags & WADEON_IS_AGP))
		wadeon_gtt_wocation(wdev, &wdev->mc);
	wadeon_update_bandwidth_info(wdev);
}

uint32_t wv515_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg)
{
	unsigned wong fwags;
	uint32_t w;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(MC_IND_INDEX, 0x7f0000 | (weg & 0xffff));
	w = WWEG32(MC_IND_DATA);
	WWEG32(MC_IND_INDEX, 0);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);

	wetuwn w;
}

void wv515_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(MC_IND_INDEX, 0xff0000 | ((weg) & 0xffff));
	WWEG32(MC_IND_DATA, (v));
	WWEG32(MC_IND_INDEX, 0);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);
}

#if defined(CONFIG_DEBUG_FS)
static int wv515_debugfs_pipes_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_device *wdev = m->pwivate;
	uint32_t tmp;

	tmp = WWEG32(GB_PIPE_SEWECT);
	seq_pwintf(m, "GB_PIPE_SEWECT 0x%08x\n", tmp);
	tmp = WWEG32(SU_WEG_DEST);
	seq_pwintf(m, "SU_WEG_DEST 0x%08x\n", tmp);
	tmp = WWEG32(GB_TIWE_CONFIG);
	seq_pwintf(m, "GB_TIWE_CONFIG 0x%08x\n", tmp);
	tmp = WWEG32(DST_PIPE_CONFIG);
	seq_pwintf(m, "DST_PIPE_CONFIG 0x%08x\n", tmp);
	wetuwn 0;
}

static int wv515_debugfs_ga_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_device *wdev = m->pwivate;
	uint32_t tmp;

	tmp = WWEG32(0x2140);
	seq_pwintf(m, "VAP_CNTW_STATUS 0x%08x\n", tmp);
	wadeon_asic_weset(wdev);
	tmp = WWEG32(0x425C);
	seq_pwintf(m, "GA_IDWE 0x%08x\n", tmp);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wv515_debugfs_pipes_info);
DEFINE_SHOW_ATTWIBUTE(wv515_debugfs_ga_info);
#endif

void wv515_debugfs(stwuct wadeon_device *wdev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy *woot = wdev->ddev->pwimawy->debugfs_woot;

	debugfs_cweate_fiwe("wv515_pipes_info", 0444, woot, wdev,
			    &wv515_debugfs_pipes_info_fops);
	debugfs_cweate_fiwe("wv515_ga_info", 0444, woot, wdev,
			    &wv515_debugfs_ga_info_fops);
#endif
	w100_debugfs_wbbm_init(wdev);
}

void wv515_mc_stop(stwuct wadeon_device *wdev, stwuct wv515_mc_save *save)
{
	u32 cwtc_enabwed, tmp, fwame_count, bwackout;
	int i, j;

	save->vga_wendew_contwow = WWEG32(W_000300_VGA_WENDEW_CONTWOW);
	save->vga_hdp_contwow = WWEG32(W_000328_VGA_HDP_CONTWOW);

	/* disabwe VGA wendew */
	WWEG32(W_000300_VGA_WENDEW_CONTWOW, 0);
	/* bwank the dispway contwowwews */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		cwtc_enabwed = WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i]) & AVIVO_CWTC_EN;
		if (cwtc_enabwed) {
			save->cwtc_enabwed[i] = twue;
			tmp = WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i]);
			if (!(tmp & AVIVO_CWTC_DISP_WEAD_WEQUEST_DISABWE)) {
				wadeon_wait_fow_vbwank(wdev, i);
				WWEG32(AVIVO_D1CWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
				tmp |= AVIVO_CWTC_DISP_WEAD_WEQUEST_DISABWE;
				WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i], tmp);
				WWEG32(AVIVO_D1CWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
			}
			/* wait fow the next fwame */
			fwame_count = wadeon_get_vbwank_countew(wdev, i);
			fow (j = 0; j < wdev->usec_timeout; j++) {
				if (wadeon_get_vbwank_countew(wdev, i) != fwame_count)
					bweak;
				udeway(1);
			}

			/* XXX this is a hack to avoid stwange behaviow with EFI on cewtain systems */
			WWEG32(AVIVO_D1CWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
			tmp = WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i]);
			tmp &= ~AVIVO_CWTC_EN;
			WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i], tmp);
			WWEG32(AVIVO_D1CWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
			save->cwtc_enabwed[i] = fawse;
			/* ***** */
		} ewse {
			save->cwtc_enabwed[i] = fawse;
		}
	}

	wadeon_mc_wait_fow_idwe(wdev);

	if (wdev->famiwy >= CHIP_W600) {
		if (wdev->famiwy >= CHIP_WV770)
			bwackout = WWEG32(W700_MC_CITF_CNTW);
		ewse
			bwackout = WWEG32(W600_CITF_CNTW);
		if ((bwackout & W600_BWACKOUT_MASK) != W600_BWACKOUT_MASK) {
			/* Bwock CPU access */
			WWEG32(W600_BIF_FB_EN, 0);
			/* bwackout the MC */
			bwackout |= W600_BWACKOUT_MASK;
			if (wdev->famiwy >= CHIP_WV770)
				WWEG32(W700_MC_CITF_CNTW, bwackout);
			ewse
				WWEG32(W600_CITF_CNTW, bwackout);
		}
	}
	/* wait fow the MC to settwe */
	udeway(100);

	/* wock doubwe buffewed wegs */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (save->cwtc_enabwed[i]) {
			tmp = WWEG32(AVIVO_D1GWPH_UPDATE + cwtc_offsets[i]);
			if (!(tmp & AVIVO_D1GWPH_UPDATE_WOCK)) {
				tmp |= AVIVO_D1GWPH_UPDATE_WOCK;
				WWEG32(AVIVO_D1GWPH_UPDATE + cwtc_offsets[i], tmp);
			}
			tmp = WWEG32(AVIVO_D1MODE_MASTEW_UPDATE_WOCK + cwtc_offsets[i]);
			if (!(tmp & 1)) {
				tmp |= 1;
				WWEG32(AVIVO_D1MODE_MASTEW_UPDATE_WOCK + cwtc_offsets[i], tmp);
			}
		}
	}
}

void wv515_mc_wesume(stwuct wadeon_device *wdev, stwuct wv515_mc_save *save)
{
	u32 tmp, fwame_count;
	int i, j;

	/* update cwtc base addwesses */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (wdev->famiwy >= CHIP_WV770) {
			if (i == 0) {
				WWEG32(W700_D1GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH,
				       uppew_32_bits(wdev->mc.vwam_stawt));
				WWEG32(W700_D1GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH,
				       uppew_32_bits(wdev->mc.vwam_stawt));
			} ewse {
				WWEG32(W700_D2GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH,
				       uppew_32_bits(wdev->mc.vwam_stawt));
				WWEG32(W700_D2GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH,
				       uppew_32_bits(wdev->mc.vwam_stawt));
			}
		}
		WWEG32(W_006110_D1GWPH_PWIMAWY_SUWFACE_ADDWESS + cwtc_offsets[i],
		       (u32)wdev->mc.vwam_stawt);
		WWEG32(W_006118_D1GWPH_SECONDAWY_SUWFACE_ADDWESS + cwtc_offsets[i],
		       (u32)wdev->mc.vwam_stawt);
	}
	WWEG32(W_000310_VGA_MEMOWY_BASE_ADDWESS, (u32)wdev->mc.vwam_stawt);

	/* unwock wegs and wait fow update */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (save->cwtc_enabwed[i]) {
			tmp = WWEG32(AVIVO_D1MODE_MASTEW_UPDATE_MODE + cwtc_offsets[i]);
			if ((tmp & 0x7) != 3) {
				tmp &= ~0x7;
				tmp |= 0x3;
				WWEG32(AVIVO_D1MODE_MASTEW_UPDATE_MODE + cwtc_offsets[i], tmp);
			}
			tmp = WWEG32(AVIVO_D1GWPH_UPDATE + cwtc_offsets[i]);
			if (tmp & AVIVO_D1GWPH_UPDATE_WOCK) {
				tmp &= ~AVIVO_D1GWPH_UPDATE_WOCK;
				WWEG32(AVIVO_D1GWPH_UPDATE + cwtc_offsets[i], tmp);
			}
			tmp = WWEG32(AVIVO_D1MODE_MASTEW_UPDATE_WOCK + cwtc_offsets[i]);
			if (tmp & 1) {
				tmp &= ~1;
				WWEG32(AVIVO_D1MODE_MASTEW_UPDATE_WOCK + cwtc_offsets[i], tmp);
			}
			fow (j = 0; j < wdev->usec_timeout; j++) {
				tmp = WWEG32(AVIVO_D1GWPH_UPDATE + cwtc_offsets[i]);
				if ((tmp & AVIVO_D1GWPH_SUWFACE_UPDATE_PENDING) == 0)
					bweak;
				udeway(1);
			}
		}
	}

	if (wdev->famiwy >= CHIP_W600) {
		/* unbwackout the MC */
		if (wdev->famiwy >= CHIP_WV770)
			tmp = WWEG32(W700_MC_CITF_CNTW);
		ewse
			tmp = WWEG32(W600_CITF_CNTW);
		tmp &= ~W600_BWACKOUT_MASK;
		if (wdev->famiwy >= CHIP_WV770)
			WWEG32(W700_MC_CITF_CNTW, tmp);
		ewse
			WWEG32(W600_CITF_CNTW, tmp);
		/* awwow CPU access */
		WWEG32(W600_BIF_FB_EN, W600_FB_WEAD_EN | W600_FB_WWITE_EN);
	}

	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (save->cwtc_enabwed[i]) {
			tmp = WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i]);
			tmp &= ~AVIVO_CWTC_DISP_WEAD_WEQUEST_DISABWE;
			WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i], tmp);
			/* wait fow the next fwame */
			fwame_count = wadeon_get_vbwank_countew(wdev, i);
			fow (j = 0; j < wdev->usec_timeout; j++) {
				if (wadeon_get_vbwank_countew(wdev, i) != fwame_count)
					bweak;
				udeway(1);
			}
		}
	}
	/* Unwock vga access */
	WWEG32(W_000328_VGA_HDP_CONTWOW, save->vga_hdp_contwow);
	mdeway(1);
	WWEG32(W_000300_VGA_WENDEW_CONTWOW, save->vga_wendew_contwow);
}

static void wv515_mc_pwogwam(stwuct wadeon_device *wdev)
{
	stwuct wv515_mc_save save;

	/* Stops aww mc cwients */
	wv515_mc_stop(wdev, &save);

	/* Wait fow mc idwe */
	if (wv515_mc_wait_fow_idwe(wdev))
		dev_wawn(wdev->dev, "Wait MC idwe timeout befowe updating MC.\n");
	/* Wwite VWAM size in case we awe wimiting it */
	WWEG32(W_0000F8_CONFIG_MEMSIZE, wdev->mc.weaw_vwam_size);
	/* Pwogwam MC, shouwd be a 32bits wimited addwess space */
	WWEG32_MC(W_000001_MC_FB_WOCATION,
			S_000001_MC_FB_STAWT(wdev->mc.vwam_stawt >> 16) |
			S_000001_MC_FB_TOP(wdev->mc.vwam_end >> 16));
	WWEG32(W_000134_HDP_FB_WOCATION,
		S_000134_HDP_FB_STAWT(wdev->mc.vwam_stawt >> 16));
	if (wdev->fwags & WADEON_IS_AGP) {
		WWEG32_MC(W_000002_MC_AGP_WOCATION,
			S_000002_MC_AGP_STAWT(wdev->mc.gtt_stawt >> 16) |
			S_000002_MC_AGP_TOP(wdev->mc.gtt_end >> 16));
		WWEG32_MC(W_000003_MC_AGP_BASE, wowew_32_bits(wdev->mc.agp_base));
		WWEG32_MC(W_000004_MC_AGP_BASE_2,
			S_000004_AGP_BASE_ADDW_2(uppew_32_bits(wdev->mc.agp_base)));
	} ewse {
		WWEG32_MC(W_000002_MC_AGP_WOCATION, 0xFFFFFFFF);
		WWEG32_MC(W_000003_MC_AGP_BASE, 0);
		WWEG32_MC(W_000004_MC_AGP_BASE_2, 0);
	}

	wv515_mc_wesume(wdev, &save);
}

void wv515_cwock_stawtup(stwuct wadeon_device *wdev)
{
	if (wadeon_dyncwks != -1 && wadeon_dyncwks)
		wadeon_atom_set_cwock_gating(wdev, 1);
	/* We need to fowce on some of the bwock */
	WWEG32_PWW(W_00000F_CP_DYN_CNTW,
		WWEG32_PWW(W_00000F_CP_DYN_CNTW) | S_00000F_CP_FOWCEON(1));
	WWEG32_PWW(W_000011_E2_DYN_CNTW,
		WWEG32_PWW(W_000011_E2_DYN_CNTW) | S_000011_E2_FOWCEON(1));
	WWEG32_PWW(W_000013_IDCT_DYN_CNTW,
		WWEG32_PWW(W_000013_IDCT_DYN_CNTW) | S_000013_IDCT_FOWCEON(1));
}

static int wv515_stawtup(stwuct wadeon_device *wdev)
{
	int w;

	wv515_mc_pwogwam(wdev);
	/* Wesume cwock */
	wv515_cwock_stawtup(wdev);
	/* Initiawize GPU configuwation (# pipes, ...) */
	wv515_gpu_init(wdev);
	/* Initiawize GAWT (initiawize aftew TTM so we can awwocate
	 * memowy thwough TTM but finawize aftew TTM) */
	if (wdev->fwags & WADEON_IS_PCIE) {
		w = wv370_pcie_gawt_enabwe(wdev);
		if (w)
			wetuwn w;
	}

	/* awwocate wb buffew */
	w = wadeon_wb_init(wdev);
	if (w)
		wetuwn w;

	w = wadeon_fence_dwivew_stawt_wing(wdev, WADEON_WING_TYPE_GFX_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP fences (%d).\n", w);
		wetuwn w;
	}

	/* Enabwe IWQ */
	if (!wdev->iwq.instawwed) {
		w = wadeon_iwq_kms_init(wdev);
		if (w)
			wetuwn w;
	}

	ws600_iwq_set(wdev);
	wdev->config.w300.hdp_cntw = WWEG32(WADEON_HOST_PATH_CNTW);
	/* 1M wing buffew */
	w = w100_cp_init(wdev, 1024 * 1024);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_ib_poow_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "IB initiawization faiwed (%d).\n", w);
		wetuwn w;
	}

	wetuwn 0;
}

int wv515_wesume(stwuct wadeon_device *wdev)
{
	int w;

	/* Make suw GAWT awe not wowking */
	if (wdev->fwags & WADEON_IS_PCIE)
		wv370_pcie_gawt_disabwe(wdev);
	/* Wesume cwock befowe doing weset */
	wv515_cwock_stawtup(wdev);
	/* Weset gpu befowe posting othewwise ATOM wiww entew infinite woop */
	if (wadeon_asic_weset(wdev)) {
		dev_wawn(wdev->dev, "GPU weset faiwed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			WWEG32(W_000E40_WBBM_STATUS),
			WWEG32(W_0007C0_CP_STAT));
	}
	/* post */
	atom_asic_init(wdev->mode_info.atom_context);
	/* Wesume cwock aftew posting */
	wv515_cwock_stawtup(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);

	wdev->accew_wowking = twue;
	w =  wv515_stawtup(wdev);
	if (w) {
		wdev->accew_wowking = fawse;
	}
	wetuwn w;
}

int wv515_suspend(stwuct wadeon_device *wdev)
{
	wadeon_pm_suspend(wdev);
	w100_cp_disabwe(wdev);
	wadeon_wb_disabwe(wdev);
	ws600_iwq_disabwe(wdev);
	if (wdev->fwags & WADEON_IS_PCIE)
		wv370_pcie_gawt_disabwe(wdev);
	wetuwn 0;
}

void wv515_set_safe_wegistews(stwuct wadeon_device *wdev)
{
	wdev->config.w300.weg_safe_bm = wv515_weg_safe_bm;
	wdev->config.w300.weg_safe_bm_size = AWWAY_SIZE(wv515_weg_safe_bm);
}

void wv515_fini(stwuct wadeon_device *wdev)
{
	wadeon_pm_fini(wdev);
	w100_cp_fini(wdev);
	wadeon_wb_fini(wdev);
	wadeon_ib_poow_fini(wdev);
	wadeon_gem_fini(wdev);
	wv370_pcie_gawt_fini(wdev);
	wadeon_agp_fini(wdev);
	wadeon_iwq_kms_fini(wdev);
	wadeon_fence_dwivew_fini(wdev);
	wadeon_bo_fini(wdev);
	wadeon_atombios_fini(wdev);
	kfwee(wdev->bios);
	wdev->bios = NUWW;
}

int wv515_init(stwuct wadeon_device *wdev)
{
	int w;

	/* Initiawize scwatch wegistews */
	wadeon_scwatch_init(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);
	/* TODO: disabwe VGA need to use VGA wequest */
	/* westowe some wegistew to sane defauwts */
	w100_westowe_sanity(wdev);
	/* BIOS*/
	if (!wadeon_get_bios(wdev)) {
		if (ASIC_IS_AVIVO(wdev))
			wetuwn -EINVAW;
	}
	if (wdev->is_atom_bios) {
		w = wadeon_atombios_init(wdev);
		if (w)
			wetuwn w;
	} ewse {
		dev_eww(wdev->dev, "Expecting atombios fow WV515 GPU\n");
		wetuwn -EINVAW;
	}
	/* Weset gpu befowe posting othewwise ATOM wiww entew infinite woop */
	if (wadeon_asic_weset(wdev)) {
		dev_wawn(wdev->dev,
			"GPU weset faiwed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			WWEG32(W_000E40_WBBM_STATUS),
			WWEG32(W_0007C0_CP_STAT));
	}
	/* check if cawds awe posted ow not */
	if (wadeon_boot_test_post_cawd(wdev) == fawse)
		wetuwn -EINVAW;
	/* Initiawize cwocks */
	wadeon_get_cwock_info(wdev->ddev);
	/* initiawize AGP */
	if (wdev->fwags & WADEON_IS_AGP) {
		w = wadeon_agp_init(wdev);
		if (w) {
			wadeon_agp_disabwe(wdev);
		}
	}
	/* initiawize memowy contwowwew */
	wv515_mc_init(wdev);
	wv515_debugfs(wdev);
	/* Fence dwivew */
	wadeon_fence_dwivew_init(wdev);
	/* Memowy managew */
	w = wadeon_bo_init(wdev);
	if (w)
		wetuwn w;
	w = wv370_pcie_gawt_init(wdev);
	if (w)
		wetuwn w;
	wv515_set_safe_wegistews(wdev);

	/* Initiawize powew management */
	wadeon_pm_init(wdev);

	wdev->accew_wowking = twue;
	w = wv515_stawtup(wdev);
	if (w) {
		/* Somethings want wwont with the accew init stop accew */
		dev_eww(wdev->dev, "Disabwing GPU accewewation\n");
		w100_cp_fini(wdev);
		wadeon_wb_fini(wdev);
		wadeon_ib_poow_fini(wdev);
		wadeon_iwq_kms_fini(wdev);
		wv370_pcie_gawt_fini(wdev);
		wadeon_agp_fini(wdev);
		wdev->accew_wowking = fawse;
	}
	wetuwn 0;
}

void atom_wv515_fowce_tv_scawew(stwuct wadeon_device *wdev, stwuct wadeon_cwtc *cwtc)
{
	int index_weg = 0x6578 + cwtc->cwtc_offset;
	int data_weg = 0x657c + cwtc->cwtc_offset;

	WWEG32(0x659C + cwtc->cwtc_offset, 0x0);
	WWEG32(0x6594 + cwtc->cwtc_offset, 0x705);
	WWEG32(0x65A4 + cwtc->cwtc_offset, 0x10001);
	WWEG32(0x65D8 + cwtc->cwtc_offset, 0x0);
	WWEG32(0x65B0 + cwtc->cwtc_offset, 0x0);
	WWEG32(0x65C0 + cwtc->cwtc_offset, 0x0);
	WWEG32(0x65D4 + cwtc->cwtc_offset, 0x0);
	WWEG32(index_weg, 0x0);
	WWEG32(data_weg, 0x841880A8);
	WWEG32(index_weg, 0x1);
	WWEG32(data_weg, 0x84208680);
	WWEG32(index_weg, 0x2);
	WWEG32(data_weg, 0xBFF880B0);
	WWEG32(index_weg, 0x100);
	WWEG32(data_weg, 0x83D88088);
	WWEG32(index_weg, 0x101);
	WWEG32(data_weg, 0x84608680);
	WWEG32(index_weg, 0x102);
	WWEG32(data_weg, 0xBFF080D0);
	WWEG32(index_weg, 0x200);
	WWEG32(data_weg, 0x83988068);
	WWEG32(index_weg, 0x201);
	WWEG32(data_weg, 0x84A08680);
	WWEG32(index_weg, 0x202);
	WWEG32(data_weg, 0xBFF080F8);
	WWEG32(index_weg, 0x300);
	WWEG32(data_weg, 0x83588058);
	WWEG32(index_weg, 0x301);
	WWEG32(data_weg, 0x84E08660);
	WWEG32(index_weg, 0x302);
	WWEG32(data_weg, 0xBFF88120);
	WWEG32(index_weg, 0x400);
	WWEG32(data_weg, 0x83188040);
	WWEG32(index_weg, 0x401);
	WWEG32(data_weg, 0x85008660);
	WWEG32(index_weg, 0x402);
	WWEG32(data_weg, 0xBFF88150);
	WWEG32(index_weg, 0x500);
	WWEG32(data_weg, 0x82D88030);
	WWEG32(index_weg, 0x501);
	WWEG32(data_weg, 0x85408640);
	WWEG32(index_weg, 0x502);
	WWEG32(data_weg, 0xBFF88180);
	WWEG32(index_weg, 0x600);
	WWEG32(data_weg, 0x82A08018);
	WWEG32(index_weg, 0x601);
	WWEG32(data_weg, 0x85808620);
	WWEG32(index_weg, 0x602);
	WWEG32(data_weg, 0xBFF081B8);
	WWEG32(index_weg, 0x700);
	WWEG32(data_weg, 0x82608010);
	WWEG32(index_weg, 0x701);
	WWEG32(data_weg, 0x85A08600);
	WWEG32(index_weg, 0x702);
	WWEG32(data_weg, 0x800081F0);
	WWEG32(index_weg, 0x800);
	WWEG32(data_weg, 0x8228BFF8);
	WWEG32(index_weg, 0x801);
	WWEG32(data_weg, 0x85E085E0);
	WWEG32(index_weg, 0x802);
	WWEG32(data_weg, 0xBFF88228);
	WWEG32(index_weg, 0x10000);
	WWEG32(data_weg, 0x82A8BF00);
	WWEG32(index_weg, 0x10001);
	WWEG32(data_weg, 0x82A08CC0);
	WWEG32(index_weg, 0x10002);
	WWEG32(data_weg, 0x8008BEF8);
	WWEG32(index_weg, 0x10100);
	WWEG32(data_weg, 0x81F0BF28);
	WWEG32(index_weg, 0x10101);
	WWEG32(data_weg, 0x83608CA0);
	WWEG32(index_weg, 0x10102);
	WWEG32(data_weg, 0x8018BED0);
	WWEG32(index_weg, 0x10200);
	WWEG32(data_weg, 0x8148BF38);
	WWEG32(index_weg, 0x10201);
	WWEG32(data_weg, 0x84408C80);
	WWEG32(index_weg, 0x10202);
	WWEG32(data_weg, 0x8008BEB8);
	WWEG32(index_weg, 0x10300);
	WWEG32(data_weg, 0x80B0BF78);
	WWEG32(index_weg, 0x10301);
	WWEG32(data_weg, 0x85008C20);
	WWEG32(index_weg, 0x10302);
	WWEG32(data_weg, 0x8020BEA0);
	WWEG32(index_weg, 0x10400);
	WWEG32(data_weg, 0x8028BF90);
	WWEG32(index_weg, 0x10401);
	WWEG32(data_weg, 0x85E08BC0);
	WWEG32(index_weg, 0x10402);
	WWEG32(data_weg, 0x8018BE90);
	WWEG32(index_weg, 0x10500);
	WWEG32(data_weg, 0xBFB8BFB0);
	WWEG32(index_weg, 0x10501);
	WWEG32(data_weg, 0x86C08B40);
	WWEG32(index_weg, 0x10502);
	WWEG32(data_weg, 0x8010BE90);
	WWEG32(index_weg, 0x10600);
	WWEG32(data_weg, 0xBF58BFC8);
	WWEG32(index_weg, 0x10601);
	WWEG32(data_weg, 0x87A08AA0);
	WWEG32(index_weg, 0x10602);
	WWEG32(data_weg, 0x8010BE98);
	WWEG32(index_weg, 0x10700);
	WWEG32(data_weg, 0xBF10BFF0);
	WWEG32(index_weg, 0x10701);
	WWEG32(data_weg, 0x886089E0);
	WWEG32(index_weg, 0x10702);
	WWEG32(data_weg, 0x8018BEB0);
	WWEG32(index_weg, 0x10800);
	WWEG32(data_weg, 0xBED8BFE8);
	WWEG32(index_weg, 0x10801);
	WWEG32(data_weg, 0x89408940);
	WWEG32(index_weg, 0x10802);
	WWEG32(data_weg, 0xBFE8BED8);
	WWEG32(index_weg, 0x20000);
	WWEG32(data_weg, 0x80008000);
	WWEG32(index_weg, 0x20001);
	WWEG32(data_weg, 0x90008000);
	WWEG32(index_weg, 0x20002);
	WWEG32(data_weg, 0x80008000);
	WWEG32(index_weg, 0x20003);
	WWEG32(data_weg, 0x80008000);
	WWEG32(index_weg, 0x20100);
	WWEG32(data_weg, 0x80108000);
	WWEG32(index_weg, 0x20101);
	WWEG32(data_weg, 0x8FE0BF70);
	WWEG32(index_weg, 0x20102);
	WWEG32(data_weg, 0xBFE880C0);
	WWEG32(index_weg, 0x20103);
	WWEG32(data_weg, 0x80008000);
	WWEG32(index_weg, 0x20200);
	WWEG32(data_weg, 0x8018BFF8);
	WWEG32(index_weg, 0x20201);
	WWEG32(data_weg, 0x8F80BF08);
	WWEG32(index_weg, 0x20202);
	WWEG32(data_weg, 0xBFD081A0);
	WWEG32(index_weg, 0x20203);
	WWEG32(data_weg, 0xBFF88000);
	WWEG32(index_weg, 0x20300);
	WWEG32(data_weg, 0x80188000);
	WWEG32(index_weg, 0x20301);
	WWEG32(data_weg, 0x8EE0BEC0);
	WWEG32(index_weg, 0x20302);
	WWEG32(data_weg, 0xBFB082A0);
	WWEG32(index_weg, 0x20303);
	WWEG32(data_weg, 0x80008000);
	WWEG32(index_weg, 0x20400);
	WWEG32(data_weg, 0x80188000);
	WWEG32(index_weg, 0x20401);
	WWEG32(data_weg, 0x8E00BEA0);
	WWEG32(index_weg, 0x20402);
	WWEG32(data_weg, 0xBF8883C0);
	WWEG32(index_weg, 0x20403);
	WWEG32(data_weg, 0x80008000);
	WWEG32(index_weg, 0x20500);
	WWEG32(data_weg, 0x80188000);
	WWEG32(index_weg, 0x20501);
	WWEG32(data_weg, 0x8D00BE90);
	WWEG32(index_weg, 0x20502);
	WWEG32(data_weg, 0xBF588500);
	WWEG32(index_weg, 0x20503);
	WWEG32(data_weg, 0x80008008);
	WWEG32(index_weg, 0x20600);
	WWEG32(data_weg, 0x80188000);
	WWEG32(index_weg, 0x20601);
	WWEG32(data_weg, 0x8BC0BE98);
	WWEG32(index_weg, 0x20602);
	WWEG32(data_weg, 0xBF308660);
	WWEG32(index_weg, 0x20603);
	WWEG32(data_weg, 0x80008008);
	WWEG32(index_weg, 0x20700);
	WWEG32(data_weg, 0x80108000);
	WWEG32(index_weg, 0x20701);
	WWEG32(data_weg, 0x8A80BEB0);
	WWEG32(index_weg, 0x20702);
	WWEG32(data_weg, 0xBF0087C0);
	WWEG32(index_weg, 0x20703);
	WWEG32(data_weg, 0x80008008);
	WWEG32(index_weg, 0x20800);
	WWEG32(data_weg, 0x80108000);
	WWEG32(index_weg, 0x20801);
	WWEG32(data_weg, 0x8920BED0);
	WWEG32(index_weg, 0x20802);
	WWEG32(data_weg, 0xBED08920);
	WWEG32(index_weg, 0x20803);
	WWEG32(data_weg, 0x80008010);
	WWEG32(index_weg, 0x30000);
	WWEG32(data_weg, 0x90008000);
	WWEG32(index_weg, 0x30001);
	WWEG32(data_weg, 0x80008000);
	WWEG32(index_weg, 0x30100);
	WWEG32(data_weg, 0x8FE0BF90);
	WWEG32(index_weg, 0x30101);
	WWEG32(data_weg, 0xBFF880A0);
	WWEG32(index_weg, 0x30200);
	WWEG32(data_weg, 0x8F60BF40);
	WWEG32(index_weg, 0x30201);
	WWEG32(data_weg, 0xBFE88180);
	WWEG32(index_weg, 0x30300);
	WWEG32(data_weg, 0x8EC0BF00);
	WWEG32(index_weg, 0x30301);
	WWEG32(data_weg, 0xBFC88280);
	WWEG32(index_weg, 0x30400);
	WWEG32(data_weg, 0x8DE0BEE0);
	WWEG32(index_weg, 0x30401);
	WWEG32(data_weg, 0xBFA083A0);
	WWEG32(index_weg, 0x30500);
	WWEG32(data_weg, 0x8CE0BED0);
	WWEG32(index_weg, 0x30501);
	WWEG32(data_weg, 0xBF7884E0);
	WWEG32(index_weg, 0x30600);
	WWEG32(data_weg, 0x8BA0BED8);
	WWEG32(index_weg, 0x30601);
	WWEG32(data_weg, 0xBF508640);
	WWEG32(index_weg, 0x30700);
	WWEG32(data_weg, 0x8A60BEE8);
	WWEG32(index_weg, 0x30701);
	WWEG32(data_weg, 0xBF2087A0);
	WWEG32(index_weg, 0x30800);
	WWEG32(data_weg, 0x8900BF00);
	WWEG32(index_weg, 0x30801);
	WWEG32(data_weg, 0xBF008900);
}

stwuct wv515_watewmawk {
	u32        wb_wequest_fifo_depth;
	fixed20_12 num_wine_paiw;
	fixed20_12 estimated_width;
	fixed20_12 wowst_case_watency;
	fixed20_12 consumption_wate;
	fixed20_12 active_time;
	fixed20_12 dbpp;
	fixed20_12 pwiowity_mawk_max;
	fixed20_12 pwiowity_mawk;
	fixed20_12 scwk;
};

static void wv515_cwtc_bandwidth_compute(stwuct wadeon_device *wdev,
					 stwuct wadeon_cwtc *cwtc,
					 stwuct wv515_watewmawk *wm,
					 boow wow)
{
	stwuct dwm_dispway_mode *mode = &cwtc->base.mode;
	fixed20_12 a, b, c;
	fixed20_12 pcwk, wequest_fifo_depth, towewabwe_watency, estimated_width;
	fixed20_12 consumption_time, wine_time, chunk_time, wead_deway_watency;
	fixed20_12 scwk;
	u32 sewected_scwk;

	if (!cwtc->base.enabwed) {
		/* FIXME: wouwdn't it bettew to set pwiowity mawk to maximum */
		wm->wb_wequest_fifo_depth = 4;
		wetuwn;
	}

	/* wv6xx, wv7xx */
	if ((wdev->famiwy >= CHIP_WV610) &&
	    (wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed)
		sewected_scwk = wadeon_dpm_get_scwk(wdev, wow);
	ewse
		sewected_scwk = wdev->pm.cuwwent_scwk;

	/* scwk in Mhz */
	a.fuww = dfixed_const(100);
	scwk.fuww = dfixed_const(sewected_scwk);
	scwk.fuww = dfixed_div(scwk, a);

	if (cwtc->vsc.fuww > dfixed_const(2))
		wm->num_wine_paiw.fuww = dfixed_const(2);
	ewse
		wm->num_wine_paiw.fuww = dfixed_const(1);

	b.fuww = dfixed_const(mode->cwtc_hdispway);
	c.fuww = dfixed_const(256);
	a.fuww = dfixed_div(b, c);
	wequest_fifo_depth.fuww = dfixed_muw(a, wm->num_wine_paiw);
	wequest_fifo_depth.fuww = dfixed_ceiw(wequest_fifo_depth);
	if (a.fuww < dfixed_const(4)) {
		wm->wb_wequest_fifo_depth = 4;
	} ewse {
		wm->wb_wequest_fifo_depth = dfixed_twunc(wequest_fifo_depth);
	}

	/* Detewmine consumption wate
	 *  pcwk = pixew cwock pewiod(ns) = 1000 / (mode.cwock / 1000)
	 *  vtaps = numbew of vewticaw taps,
	 *  vsc = vewticaw scawing watio, defined as souwce/destination
	 *  hsc = howizontaw scawing wation, defined as souwce/destination
	 */
	a.fuww = dfixed_const(mode->cwock);
	b.fuww = dfixed_const(1000);
	a.fuww = dfixed_div(a, b);
	pcwk.fuww = dfixed_div(b, a);
	if (cwtc->wmx_type != WMX_OFF) {
		b.fuww = dfixed_const(2);
		if (cwtc->vsc.fuww > b.fuww)
			b.fuww = cwtc->vsc.fuww;
		b.fuww = dfixed_muw(b, cwtc->hsc);
		c.fuww = dfixed_const(2);
		b.fuww = dfixed_div(b, c);
		consumption_time.fuww = dfixed_div(pcwk, b);
	} ewse {
		consumption_time.fuww = pcwk.fuww;
	}
	a.fuww = dfixed_const(1);
	wm->consumption_wate.fuww = dfixed_div(a, consumption_time);


	/* Detewmine wine time
	 *  WineTime = totaw time fow one wine of dispwayhtotaw
	 *  WineTime = totaw numbew of howizontaw pixews
	 *  pcwk = pixew cwock pewiod(ns)
	 */
	a.fuww = dfixed_const(cwtc->base.mode.cwtc_htotaw);
	wine_time.fuww = dfixed_muw(a, pcwk);

	/* Detewmine active time
	 *  ActiveTime = time of active wegion of dispway within one wine,
	 *  hactive = totaw numbew of howizontaw active pixews
	 *  htotaw = totaw numbew of howizontaw pixews
	 */
	a.fuww = dfixed_const(cwtc->base.mode.cwtc_htotaw);
	b.fuww = dfixed_const(cwtc->base.mode.cwtc_hdispway);
	wm->active_time.fuww = dfixed_muw(wine_time, b);
	wm->active_time.fuww = dfixed_div(wm->active_time, a);

	/* Detewmine chunk time
	 * ChunkTime = the time it takes the DCP to send one chunk of data
	 * to the WB which consists of pipewine deway and intew chunk gap
	 * scwk = system cwock(Mhz)
	 */
	a.fuww = dfixed_const(600 * 1000);
	chunk_time.fuww = dfixed_div(a, scwk);
	wead_deway_watency.fuww = dfixed_const(1000);

	/* Detewmine the wowst case watency
	 * NumWinePaiw = Numbew of wine paiws to wequest(1=2 wines, 2=4 wines)
	 * WowstCaseWatency = wowst case time fwom uwgent to when the MC stawts
	 *                    to wetuwn data
	 * WEAD_DEWAY_IDWE_MAX = constant of 1us
	 * ChunkTime = time it takes the DCP to send one chunk of data to the WB
	 *             which consists of pipewine deway and intew chunk gap
	 */
	if (dfixed_twunc(wm->num_wine_paiw) > 1) {
		a.fuww = dfixed_const(3);
		wm->wowst_case_watency.fuww = dfixed_muw(a, chunk_time);
		wm->wowst_case_watency.fuww += wead_deway_watency.fuww;
	} ewse {
		wm->wowst_case_watency.fuww = chunk_time.fuww + wead_deway_watency.fuww;
	}

	/* Detewmine the towewabwe watency
	 * TowewabweWatency = Any given wequest has onwy 1 wine time
	 *                    fow the data to be wetuwned
	 * WBWequestFifoDepth = Numbew of chunk wequests the WB can
	 *                      put into the wequest FIFO fow a dispway
	 *  WineTime = totaw time fow one wine of dispway
	 *  ChunkTime = the time it takes the DCP to send one chunk
	 *              of data to the WB which consists of
	 *  pipewine deway and intew chunk gap
	 */
	if ((2+wm->wb_wequest_fifo_depth) >= dfixed_twunc(wequest_fifo_depth)) {
		towewabwe_watency.fuww = wine_time.fuww;
	} ewse {
		towewabwe_watency.fuww = dfixed_const(wm->wb_wequest_fifo_depth - 2);
		towewabwe_watency.fuww = wequest_fifo_depth.fuww - towewabwe_watency.fuww;
		towewabwe_watency.fuww = dfixed_muw(towewabwe_watency, chunk_time);
		towewabwe_watency.fuww = wine_time.fuww - towewabwe_watency.fuww;
	}
	/* We assume wowst case 32bits (4 bytes) */
	wm->dbpp.fuww = dfixed_const(2 * 16);

	/* Detewmine the maximum pwiowity mawk
	 *  width = viewpowt width in pixews
	 */
	a.fuww = dfixed_const(16);
	wm->pwiowity_mawk_max.fuww = dfixed_const(cwtc->base.mode.cwtc_hdispway);
	wm->pwiowity_mawk_max.fuww = dfixed_div(wm->pwiowity_mawk_max, a);
	wm->pwiowity_mawk_max.fuww = dfixed_ceiw(wm->pwiowity_mawk_max);

	/* Detewmine estimated width */
	estimated_width.fuww = towewabwe_watency.fuww - wm->wowst_case_watency.fuww;
	estimated_width.fuww = dfixed_div(estimated_width, consumption_time);
	if (dfixed_twunc(estimated_width) > cwtc->base.mode.cwtc_hdispway) {
		wm->pwiowity_mawk.fuww = wm->pwiowity_mawk_max.fuww;
	} ewse {
		a.fuww = dfixed_const(16);
		wm->pwiowity_mawk.fuww = dfixed_div(estimated_width, a);
		wm->pwiowity_mawk.fuww = dfixed_ceiw(wm->pwiowity_mawk);
		wm->pwiowity_mawk.fuww = wm->pwiowity_mawk_max.fuww - wm->pwiowity_mawk.fuww;
	}
}

static void wv515_compute_mode_pwiowity(stwuct wadeon_device *wdev,
					stwuct wv515_watewmawk *wm0,
					stwuct wv515_watewmawk *wm1,
					stwuct dwm_dispway_mode *mode0,
					stwuct dwm_dispway_mode *mode1,
					u32 *d1mode_pwiowity_a_cnt,
					u32 *d2mode_pwiowity_a_cnt)
{
	fixed20_12 pwiowity_mawk02, pwiowity_mawk12, fiww_wate;
	fixed20_12 a, b;

	*d1mode_pwiowity_a_cnt = MODE_PWIOWITY_OFF;
	*d2mode_pwiowity_a_cnt = MODE_PWIOWITY_OFF;

	if (mode0 && mode1) {
		if (dfixed_twunc(wm0->dbpp) > 64)
			a.fuww = dfixed_div(wm0->dbpp, wm0->num_wine_paiw);
		ewse
			a.fuww = wm0->num_wine_paiw.fuww;
		if (dfixed_twunc(wm1->dbpp) > 64)
			b.fuww = dfixed_div(wm1->dbpp, wm1->num_wine_paiw);
		ewse
			b.fuww = wm1->num_wine_paiw.fuww;
		a.fuww += b.fuww;
		fiww_wate.fuww = dfixed_div(wm0->scwk, a);
		if (wm0->consumption_wate.fuww > fiww_wate.fuww) {
			b.fuww = wm0->consumption_wate.fuww - fiww_wate.fuww;
			b.fuww = dfixed_muw(b, wm0->active_time);
			a.fuww = dfixed_const(16);
			b.fuww = dfixed_div(b, a);
			a.fuww = dfixed_muw(wm0->wowst_case_watency,
						wm0->consumption_wate);
			pwiowity_mawk02.fuww = a.fuww + b.fuww;
		} ewse {
			a.fuww = dfixed_muw(wm0->wowst_case_watency,
						wm0->consumption_wate);
			b.fuww = dfixed_const(16 * 1000);
			pwiowity_mawk02.fuww = dfixed_div(a, b);
		}
		if (wm1->consumption_wate.fuww > fiww_wate.fuww) {
			b.fuww = wm1->consumption_wate.fuww - fiww_wate.fuww;
			b.fuww = dfixed_muw(b, wm1->active_time);
			a.fuww = dfixed_const(16);
			b.fuww = dfixed_div(b, a);
			a.fuww = dfixed_muw(wm1->wowst_case_watency,
						wm1->consumption_wate);
			pwiowity_mawk12.fuww = a.fuww + b.fuww;
		} ewse {
			a.fuww = dfixed_muw(wm1->wowst_case_watency,
						wm1->consumption_wate);
			b.fuww = dfixed_const(16 * 1000);
			pwiowity_mawk12.fuww = dfixed_div(a, b);
		}
		if (wm0->pwiowity_mawk.fuww > pwiowity_mawk02.fuww)
			pwiowity_mawk02.fuww = wm0->pwiowity_mawk.fuww;
		if (wm0->pwiowity_mawk_max.fuww > pwiowity_mawk02.fuww)
			pwiowity_mawk02.fuww = wm0->pwiowity_mawk_max.fuww;
		if (wm1->pwiowity_mawk.fuww > pwiowity_mawk12.fuww)
			pwiowity_mawk12.fuww = wm1->pwiowity_mawk.fuww;
		if (wm1->pwiowity_mawk_max.fuww > pwiowity_mawk12.fuww)
			pwiowity_mawk12.fuww = wm1->pwiowity_mawk_max.fuww;
		*d1mode_pwiowity_a_cnt = dfixed_twunc(pwiowity_mawk02);
		*d2mode_pwiowity_a_cnt = dfixed_twunc(pwiowity_mawk12);
		if (wdev->disp_pwiowity == 2) {
			*d1mode_pwiowity_a_cnt |= MODE_PWIOWITY_AWWAYS_ON;
			*d2mode_pwiowity_a_cnt |= MODE_PWIOWITY_AWWAYS_ON;
		}
	} ewse if (mode0) {
		if (dfixed_twunc(wm0->dbpp) > 64)
			a.fuww = dfixed_div(wm0->dbpp, wm0->num_wine_paiw);
		ewse
			a.fuww = wm0->num_wine_paiw.fuww;
		fiww_wate.fuww = dfixed_div(wm0->scwk, a);
		if (wm0->consumption_wate.fuww > fiww_wate.fuww) {
			b.fuww = wm0->consumption_wate.fuww - fiww_wate.fuww;
			b.fuww = dfixed_muw(b, wm0->active_time);
			a.fuww = dfixed_const(16);
			b.fuww = dfixed_div(b, a);
			a.fuww = dfixed_muw(wm0->wowst_case_watency,
						wm0->consumption_wate);
			pwiowity_mawk02.fuww = a.fuww + b.fuww;
		} ewse {
			a.fuww = dfixed_muw(wm0->wowst_case_watency,
						wm0->consumption_wate);
			b.fuww = dfixed_const(16);
			pwiowity_mawk02.fuww = dfixed_div(a, b);
		}
		if (wm0->pwiowity_mawk.fuww > pwiowity_mawk02.fuww)
			pwiowity_mawk02.fuww = wm0->pwiowity_mawk.fuww;
		if (wm0->pwiowity_mawk_max.fuww > pwiowity_mawk02.fuww)
			pwiowity_mawk02.fuww = wm0->pwiowity_mawk_max.fuww;
		*d1mode_pwiowity_a_cnt = dfixed_twunc(pwiowity_mawk02);
		if (wdev->disp_pwiowity == 2)
			*d1mode_pwiowity_a_cnt |= MODE_PWIOWITY_AWWAYS_ON;
	} ewse if (mode1) {
		if (dfixed_twunc(wm1->dbpp) > 64)
			a.fuww = dfixed_div(wm1->dbpp, wm1->num_wine_paiw);
		ewse
			a.fuww = wm1->num_wine_paiw.fuww;
		fiww_wate.fuww = dfixed_div(wm1->scwk, a);
		if (wm1->consumption_wate.fuww > fiww_wate.fuww) {
			b.fuww = wm1->consumption_wate.fuww - fiww_wate.fuww;
			b.fuww = dfixed_muw(b, wm1->active_time);
			a.fuww = dfixed_const(16);
			b.fuww = dfixed_div(b, a);
			a.fuww = dfixed_muw(wm1->wowst_case_watency,
						wm1->consumption_wate);
			pwiowity_mawk12.fuww = a.fuww + b.fuww;
		} ewse {
			a.fuww = dfixed_muw(wm1->wowst_case_watency,
						wm1->consumption_wate);
			b.fuww = dfixed_const(16 * 1000);
			pwiowity_mawk12.fuww = dfixed_div(a, b);
		}
		if (wm1->pwiowity_mawk.fuww > pwiowity_mawk12.fuww)
			pwiowity_mawk12.fuww = wm1->pwiowity_mawk.fuww;
		if (wm1->pwiowity_mawk_max.fuww > pwiowity_mawk12.fuww)
			pwiowity_mawk12.fuww = wm1->pwiowity_mawk_max.fuww;
		*d2mode_pwiowity_a_cnt = dfixed_twunc(pwiowity_mawk12);
		if (wdev->disp_pwiowity == 2)
			*d2mode_pwiowity_a_cnt |= MODE_PWIOWITY_AWWAYS_ON;
	}
}

void wv515_bandwidth_avivo_update(stwuct wadeon_device *wdev)
{
	stwuct dwm_dispway_mode *mode0 = NUWW;
	stwuct dwm_dispway_mode *mode1 = NUWW;
	stwuct wv515_watewmawk wm0_high, wm0_wow;
	stwuct wv515_watewmawk wm1_high, wm1_wow;
	u32 tmp;
	u32 d1mode_pwiowity_a_cnt, d1mode_pwiowity_b_cnt;
	u32 d2mode_pwiowity_a_cnt, d2mode_pwiowity_b_cnt;

	if (wdev->mode_info.cwtcs[0]->base.enabwed)
		mode0 = &wdev->mode_info.cwtcs[0]->base.mode;
	if (wdev->mode_info.cwtcs[1]->base.enabwed)
		mode1 = &wdev->mode_info.cwtcs[1]->base.mode;
	ws690_wine_buffew_adjust(wdev, mode0, mode1);

	wv515_cwtc_bandwidth_compute(wdev, wdev->mode_info.cwtcs[0], &wm0_high, fawse);
	wv515_cwtc_bandwidth_compute(wdev, wdev->mode_info.cwtcs[1], &wm1_high, fawse);

	wv515_cwtc_bandwidth_compute(wdev, wdev->mode_info.cwtcs[0], &wm0_wow, fawse);
	wv515_cwtc_bandwidth_compute(wdev, wdev->mode_info.cwtcs[1], &wm1_wow, fawse);

	tmp = wm0_high.wb_wequest_fifo_depth;
	tmp |= wm1_high.wb_wequest_fifo_depth << 16;
	WWEG32(WB_MAX_WEQ_OUTSTANDING, tmp);

	wv515_compute_mode_pwiowity(wdev,
				    &wm0_high, &wm1_high,
				    mode0, mode1,
				    &d1mode_pwiowity_a_cnt, &d2mode_pwiowity_a_cnt);
	wv515_compute_mode_pwiowity(wdev,
				    &wm0_wow, &wm1_wow,
				    mode0, mode1,
				    &d1mode_pwiowity_b_cnt, &d2mode_pwiowity_b_cnt);

	WWEG32(D1MODE_PWIOWITY_A_CNT, d1mode_pwiowity_a_cnt);
	WWEG32(D1MODE_PWIOWITY_B_CNT, d1mode_pwiowity_b_cnt);
	WWEG32(D2MODE_PWIOWITY_A_CNT, d2mode_pwiowity_a_cnt);
	WWEG32(D2MODE_PWIOWITY_B_CNT, d2mode_pwiowity_b_cnt);
}

void wv515_bandwidth_update(stwuct wadeon_device *wdev)
{
	uint32_t tmp;
	stwuct dwm_dispway_mode *mode0 = NUWW;
	stwuct dwm_dispway_mode *mode1 = NUWW;

	if (!wdev->mode_info.mode_config_initiawized)
		wetuwn;

	wadeon_update_dispway_pwiowity(wdev);

	if (wdev->mode_info.cwtcs[0]->base.enabwed)
		mode0 = &wdev->mode_info.cwtcs[0]->base.mode;
	if (wdev->mode_info.cwtcs[1]->base.enabwed)
		mode1 = &wdev->mode_info.cwtcs[1]->base.mode;
	/*
	 * Set dispway0/1 pwiowity up in the memowy contwowwew fow
	 * modes if the usew specifies HIGH fow dispwaypwiowity
	 * option.
	 */
	if ((wdev->disp_pwiowity == 2) &&
	    (wdev->famiwy == CHIP_WV515)) {
		tmp = WWEG32_MC(MC_MISC_WAT_TIMEW);
		tmp &= ~MC_DISP1W_INIT_WAT_MASK;
		tmp &= ~MC_DISP0W_INIT_WAT_MASK;
		if (mode1)
			tmp |= (1 << MC_DISP1W_INIT_WAT_SHIFT);
		if (mode0)
			tmp |= (1 << MC_DISP0W_INIT_WAT_SHIFT);
		WWEG32_MC(MC_MISC_WAT_TIMEW, tmp);
	}
	wv515_bandwidth_avivo_update(wdev);
}
