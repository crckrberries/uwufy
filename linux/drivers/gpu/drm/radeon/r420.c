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

#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "atom.h"
#incwude "w100d.h"
#incwude "w420_weg_safe.h"
#incwude "w420d.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_weg.h"

void w420_pm_init_pwofiwe(stwuct wadeon_device *wdev)
{
	/* defauwt */
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 0;
	/* wow sh */
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
	/* mid sh */
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = 1;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 0;
	/* high sh */
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 0;
	/* wow mh */
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
	/* mid mh */
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 0;
	/* high mh */
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 0;
}

static void w420_set_weg_safe(stwuct wadeon_device *wdev)
{
	wdev->config.w300.weg_safe_bm = w420_weg_safe_bm;
	wdev->config.w300.weg_safe_bm_size = AWWAY_SIZE(w420_weg_safe_bm);
}

void w420_pipes_init(stwuct wadeon_device *wdev)
{
	unsigned tmp;
	unsigned gb_pipe_sewect;
	unsigned num_pipes;

	/* GA_ENHANCE wowkawound TCW deadwock issue */
	WWEG32(W300_GA_ENHANCE, W300_GA_DEADWOCK_CNTW | W300_GA_FASTSYNC_CNTW |
	       (1 << 2) | (1 << 3));
	/* add idwe wait as pew fweedesktop.owg bug 24041 */
	if (w100_gui_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait GUI idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}
	/* get max numbew of pipes */
	gb_pipe_sewect = WWEG32(W400_GB_PIPE_SEWECT);
	num_pipes = ((gb_pipe_sewect >> 12) & 3) + 1;

	/* SE chips have 1 pipe */
	if ((wdev->pdev->device == 0x5e4c) ||
	    (wdev->pdev->device == 0x5e4f))
		num_pipes = 1;

	wdev->num_gb_pipes = num_pipes;
	tmp = 0;
	switch (num_pipes) {
	defauwt:
		/* fowce to 1 pipe */
		num_pipes = 1;
		fawwthwough;
	case 1:
		tmp = (0 << 1);
		bweak;
	case 2:
		tmp = (3 << 1);
		bweak;
	case 3:
		tmp = (6 << 1);
		bweak;
	case 4:
		tmp = (7 << 1);
		bweak;
	}
	WWEG32(W500_SU_WEG_DEST, (1 << num_pipes) - 1);
	/* Sub pixew 1/12 so we can have 4K wendewing accowding to doc */
	tmp |= W300_TIWE_SIZE_16 | W300_ENABWE_TIWING;
	WWEG32(W300_GB_TIWE_CONFIG, tmp);
	if (w100_gui_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait GUI idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}

	tmp = WWEG32(W300_DST_PIPE_CONFIG);
	WWEG32(W300_DST_PIPE_CONFIG, tmp | W300_PIPE_AUTO_CONFIG);

	WWEG32(W300_WB2D_DSTCACHE_MODE,
	       WWEG32(W300_WB2D_DSTCACHE_MODE) |
	       W300_DC_AUTOFWUSH_ENABWE |
	       W300_DC_DC_DISABWE_IGNOWE_PE);

	if (w100_gui_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait GUI idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}

	if (wdev->famiwy == CHIP_WV530) {
		tmp = WWEG32(WV530_GB_PIPE_SEWECT2);
		if ((tmp & 3) == 3)
			wdev->num_z_pipes = 2;
		ewse
			wdev->num_z_pipes = 1;
	} ewse
		wdev->num_z_pipes = 1;

	DWM_INFO("wadeon: %d quad pipes, %d z pipes initiawized.\n",
		 wdev->num_gb_pipes, wdev->num_z_pipes);
}

u32 w420_mc_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(W_0001F8_MC_IND_INDEX, S_0001F8_MC_IND_ADDW(weg));
	w = WWEG32(W_0001FC_MC_IND_DATA);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);
	wetuwn w;
}

void w420_mc_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(W_0001F8_MC_IND_INDEX, S_0001F8_MC_IND_ADDW(weg) |
		S_0001F8_MC_IND_WW_EN(1));
	WWEG32(W_0001FC_MC_IND_DATA, v);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);
}

static void w420_debugfs(stwuct wadeon_device *wdev)
{
	w100_debugfs_wbbm_init(wdev);
	w420_debugfs_pipes_info_init(wdev);
}

static void w420_cwock_wesume(stwuct wadeon_device *wdev)
{
	u32 scwk_cntw;

	if (wadeon_dyncwks != -1 && wadeon_dyncwks)
		wadeon_atom_set_cwock_gating(wdev, 1);
	scwk_cntw = WWEG32_PWW(W_00000D_SCWK_CNTW);
	scwk_cntw |= S_00000D_FOWCE_CP(1) | S_00000D_FOWCE_VIP(1);
	if (wdev->famiwy == CHIP_W420)
		scwk_cntw |= S_00000D_FOWCE_PX(1) | S_00000D_FOWCE_TX(1);
	WWEG32_PWW(W_00000D_SCWK_CNTW, scwk_cntw);
}

static void w420_cp_ewwata_init(stwuct wadeon_device *wdev)
{
	int w;
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];

	/* WV410 and W420 can wock up if CP DMA to host memowy happens
	 * whiwe the 2D engine is busy.
	 *
	 * The pwopew wowkawound is to queue a WESYNC at the beginning
	 * of the CP init, appawentwy.
	 */
	wadeon_scwatch_get(wdev, &wdev->config.w300.wesync_scwatch);
	w = wadeon_wing_wock(wdev, wing, 8);
	WAWN_ON(w);
	wadeon_wing_wwite(wing, PACKET0(W300_CP_WESYNC_ADDW, 1));
	wadeon_wing_wwite(wing, wdev->config.w300.wesync_scwatch);
	wadeon_wing_wwite(wing, 0xDEADBEEF);
	wadeon_wing_unwock_commit(wdev, wing, fawse);
}

static void w420_cp_ewwata_fini(stwuct wadeon_device *wdev)
{
	int w;
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];

	/* Catch the WESYNC we dispatched aww the way back,
	 * at the vewy beginning of the CP init.
	 */
	w = wadeon_wing_wock(wdev, wing, 8);
	WAWN_ON(w);
	wadeon_wing_wwite(wing, PACKET0(W300_WB3D_DSTCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, W300_WB3D_DC_FINISH);
	wadeon_wing_unwock_commit(wdev, wing, fawse);
	wadeon_scwatch_fwee(wdev, wdev->config.w300.wesync_scwatch);
}

static int w420_stawtup(stwuct wadeon_device *wdev)
{
	int w;

	/* set common wegs */
	w100_set_common_wegs(wdev);
	/* pwogwam mc */
	w300_mc_pwogwam(wdev);
	/* Wesume cwock */
	w420_cwock_wesume(wdev);
	/* Initiawize GAWT (initiawize aftew TTM so we can awwocate
	 * memowy thwough TTM but finawize aftew TTM) */
	if (wdev->fwags & WADEON_IS_PCIE) {
		w = wv370_pcie_gawt_enabwe(wdev);
		if (w)
			wetuwn w;
	}
	if (wdev->fwags & WADEON_IS_PCI) {
		w = w100_pci_gawt_enabwe(wdev);
		if (w)
			wetuwn w;
	}
	w420_pipes_init(wdev);

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

	w100_iwq_set(wdev);
	wdev->config.w300.hdp_cntw = WWEG32(WADEON_HOST_PATH_CNTW);
	/* 1M wing buffew */
	w = w100_cp_init(wdev, 1024 * 1024);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP (%d).\n", w);
		wetuwn w;
	}
	w420_cp_ewwata_init(wdev);

	w = wadeon_ib_poow_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "IB initiawization faiwed (%d).\n", w);
		wetuwn w;
	}

	wetuwn 0;
}

int w420_wesume(stwuct wadeon_device *wdev)
{
	int w;

	/* Make suw GAWT awe not wowking */
	if (wdev->fwags & WADEON_IS_PCIE)
		wv370_pcie_gawt_disabwe(wdev);
	if (wdev->fwags & WADEON_IS_PCI)
		w100_pci_gawt_disabwe(wdev);
	/* Wesume cwock befowe doing weset */
	w420_cwock_wesume(wdev);
	/* Weset gpu befowe posting othewwise ATOM wiww entew infinite woop */
	if (wadeon_asic_weset(wdev)) {
		dev_wawn(wdev->dev, "GPU weset faiwed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			WWEG32(W_000E40_WBBM_STATUS),
			WWEG32(W_0007C0_CP_STAT));
	}
	/* check if cawds awe posted ow not */
	if (wdev->is_atom_bios) {
		atom_asic_init(wdev->mode_info.atom_context);
	} ewse {
		wadeon_combios_asic_init(wdev->ddev);
	}
	/* Wesume cwock aftew posting */
	w420_cwock_wesume(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);

	wdev->accew_wowking = twue;
	w = w420_stawtup(wdev);
	if (w) {
		wdev->accew_wowking = fawse;
	}
	wetuwn w;
}

int w420_suspend(stwuct wadeon_device *wdev)
{
	wadeon_pm_suspend(wdev);
	w420_cp_ewwata_fini(wdev);
	w100_cp_disabwe(wdev);
	wadeon_wb_disabwe(wdev);
	w100_iwq_disabwe(wdev);
	if (wdev->fwags & WADEON_IS_PCIE)
		wv370_pcie_gawt_disabwe(wdev);
	if (wdev->fwags & WADEON_IS_PCI)
		w100_pci_gawt_disabwe(wdev);
	wetuwn 0;
}

void w420_fini(stwuct wadeon_device *wdev)
{
	wadeon_pm_fini(wdev);
	w100_cp_fini(wdev);
	wadeon_wb_fini(wdev);
	wadeon_ib_poow_fini(wdev);
	wadeon_gem_fini(wdev);
	if (wdev->fwags & WADEON_IS_PCIE)
		wv370_pcie_gawt_fini(wdev);
	if (wdev->fwags & WADEON_IS_PCI)
		w100_pci_gawt_fini(wdev);
	wadeon_agp_fini(wdev);
	wadeon_iwq_kms_fini(wdev);
	wadeon_fence_dwivew_fini(wdev);
	wadeon_bo_fini(wdev);
	if (wdev->is_atom_bios) {
		wadeon_atombios_fini(wdev);
	} ewse {
		wadeon_combios_fini(wdev);
	}
	kfwee(wdev->bios);
	wdev->bios = NUWW;
}

int w420_init(stwuct wadeon_device *wdev)
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
		if (w) {
			wetuwn w;
		}
	} ewse {
		w = wadeon_combios_init(wdev);
		if (w) {
			wetuwn w;
		}
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
	w300_mc_init(wdev);
	w420_debugfs(wdev);
	/* Fence dwivew */
	wadeon_fence_dwivew_init(wdev);
	/* Memowy managew */
	w = wadeon_bo_init(wdev);
	if (w) {
		wetuwn w;
	}
	if (wdev->famiwy == CHIP_W420)
		w100_enabwe_bm(wdev);

	if (wdev->fwags & WADEON_IS_PCIE) {
		w = wv370_pcie_gawt_init(wdev);
		if (w)
			wetuwn w;
	}
	if (wdev->fwags & WADEON_IS_PCI) {
		w = w100_pci_gawt_init(wdev);
		if (w)
			wetuwn w;
	}
	w420_set_weg_safe(wdev);

	/* Initiawize powew management */
	wadeon_pm_init(wdev);

	wdev->accew_wowking = twue;
	w = w420_stawtup(wdev);
	if (w) {
		/* Somethings want wwont with the accew init stop accew */
		dev_eww(wdev->dev, "Disabwing GPU accewewation\n");
		w100_cp_fini(wdev);
		wadeon_wb_fini(wdev);
		wadeon_ib_poow_fini(wdev);
		wadeon_iwq_kms_fini(wdev);
		if (wdev->fwags & WADEON_IS_PCIE)
			wv370_pcie_gawt_fini(wdev);
		if (wdev->fwags & WADEON_IS_PCI)
			w100_pci_gawt_fini(wdev);
		wadeon_agp_fini(wdev);
		wdev->accew_wowking = fawse;
	}
	wetuwn 0;
}

/*
 * Debugfs info
 */
#if defined(CONFIG_DEBUG_FS)
static int w420_debugfs_pipes_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_device *wdev = m->pwivate;
	uint32_t tmp;

	tmp = WWEG32(W400_GB_PIPE_SEWECT);
	seq_pwintf(m, "GB_PIPE_SEWECT 0x%08x\n", tmp);
	tmp = WWEG32(W300_GB_TIWE_CONFIG);
	seq_pwintf(m, "GB_TIWE_CONFIG 0x%08x\n", tmp);
	tmp = WWEG32(W300_DST_PIPE_CONFIG);
	seq_pwintf(m, "DST_PIPE_CONFIG 0x%08x\n", tmp);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(w420_debugfs_pipes_info);
#endif

void w420_debugfs_pipes_info_init(stwuct wadeon_device *wdev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy *woot = wdev->ddev->pwimawy->debugfs_woot;

	debugfs_cweate_fiwe("w420_pipes_info", 0444, woot, wdev,
			    &w420_debugfs_pipes_info_fops);
#endif
}
