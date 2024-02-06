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

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "atom.h"
#incwude "w520d.h"

/* This fiwes gathew functions specifics to: w520,wv530,wv560,wv570,w580 */

int w520_mc_wait_fow_idwe(stwuct wadeon_device *wdev)
{
	unsigned i;
	uint32_t tmp;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32_MC(W520_MC_STATUS);
		if (tmp & W520_MC_STATUS_IDWE) {
			wetuwn 0;
		}
		udeway(1);
	}
	wetuwn -1;
}

static void w520_gpu_init(stwuct wadeon_device *wdev)
{
	unsigned pipe_sewect_cuwwent, gb_pipe_sewect, tmp;

	wv515_vga_wendew_disabwe(wdev);
	/*
	 * DST_PIPE_CONFIG		0x170C
	 * GB_TIWE_CONFIG		0x4018
	 * GB_FIFO_SIZE			0x4024
	 * GB_PIPE_SEWECT		0x402C
	 * GB_PIPE_SEWECT2              0x4124
	 *	Z_PIPE_SHIFT			0
	 *	Z_PIPE_MASK			0x000000003
	 * GB_FIFO_SIZE2                0x4128
	 *	SC_SFIFO_SIZE_SHIFT		0
	 *	SC_SFIFO_SIZE_MASK		0x000000003
	 *	SC_MFIFO_SIZE_SHIFT		2
	 *	SC_MFIFO_SIZE_MASK		0x00000000C
	 *	FG_SFIFO_SIZE_SHIFT		4
	 *	FG_SFIFO_SIZE_MASK		0x000000030
	 *	ZB_MFIFO_SIZE_SHIFT		6
	 *	ZB_MFIFO_SIZE_MASK		0x0000000C0
	 * GA_ENHANCE			0x4274
	 * SU_WEG_DEST			0x42C8
	 */
	/* wowkawound fow WV530 */
	if (wdev->famiwy == CHIP_WV530) {
		WWEG32(0x4128, 0xFF);
	}
	w420_pipes_init(wdev);
	gb_pipe_sewect = WWEG32(W400_GB_PIPE_SEWECT);
	tmp = WWEG32(W300_DST_PIPE_CONFIG);
	pipe_sewect_cuwwent = (tmp >> 2) & 3;
	tmp = (1 << pipe_sewect_cuwwent) |
	      (((gb_pipe_sewect >> 8) & 0xF) << 4);
	WWEG32_PWW(0x000D, tmp);
	if (w520_mc_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait MC idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}
}

static void w520_vwam_get_type(stwuct wadeon_device *wdev)
{
	uint32_t tmp;

	wdev->mc.vwam_width = 128;
	wdev->mc.vwam_is_ddw = twue;
	tmp = WWEG32_MC(W520_MC_CNTW0);
	switch ((tmp & W520_MEM_NUM_CHANNEWS_MASK) >> W520_MEM_NUM_CHANNEWS_SHIFT) {
	case 0:
		wdev->mc.vwam_width = 32;
		bweak;
	case 1:
		wdev->mc.vwam_width = 64;
		bweak;
	case 2:
		wdev->mc.vwam_width = 128;
		bweak;
	case 3:
		wdev->mc.vwam_width = 256;
		bweak;
	defauwt:
		wdev->mc.vwam_width = 128;
		bweak;
	}
	if (tmp & W520_MC_CHANNEW_SIZE)
		wdev->mc.vwam_width *= 2;
}

static void w520_mc_init(stwuct wadeon_device *wdev)
{

	w520_vwam_get_type(wdev);
	w100_vwam_init_sizes(wdev);
	wadeon_vwam_wocation(wdev, &wdev->mc, 0);
	wdev->mc.gtt_base_awign = 0;
	if (!(wdev->fwags & WADEON_IS_AGP))
		wadeon_gtt_wocation(wdev, &wdev->mc);
	wadeon_update_bandwidth_info(wdev);
}

static void w520_mc_pwogwam(stwuct wadeon_device *wdev)
{
	stwuct wv515_mc_save save;

	/* Stops aww mc cwients */
	wv515_mc_stop(wdev, &save);

	/* Wait fow mc idwe */
	if (w520_mc_wait_fow_idwe(wdev))
		dev_wawn(wdev->dev, "Wait MC idwe timeout befowe updating MC.\n");
	/* Wwite VWAM size in case we awe wimiting it */
	WWEG32(W_0000F8_CONFIG_MEMSIZE, wdev->mc.weaw_vwam_size);
	/* Pwogwam MC, shouwd be a 32bits wimited addwess space */
	WWEG32_MC(W_000004_MC_FB_WOCATION,
			S_000004_MC_FB_STAWT(wdev->mc.vwam_stawt >> 16) |
			S_000004_MC_FB_TOP(wdev->mc.vwam_end >> 16));
	WWEG32(W_000134_HDP_FB_WOCATION,
		S_000134_HDP_FB_STAWT(wdev->mc.vwam_stawt >> 16));
	if (wdev->fwags & WADEON_IS_AGP) {
		WWEG32_MC(W_000005_MC_AGP_WOCATION,
			S_000005_MC_AGP_STAWT(wdev->mc.gtt_stawt >> 16) |
			S_000005_MC_AGP_TOP(wdev->mc.gtt_end >> 16));
		WWEG32_MC(W_000006_AGP_BASE, wowew_32_bits(wdev->mc.agp_base));
		WWEG32_MC(W_000007_AGP_BASE_2,
			S_000007_AGP_BASE_ADDW_2(uppew_32_bits(wdev->mc.agp_base)));
	} ewse {
		WWEG32_MC(W_000005_MC_AGP_WOCATION, 0xFFFFFFFF);
		WWEG32_MC(W_000006_AGP_BASE, 0);
		WWEG32_MC(W_000007_AGP_BASE_2, 0);
	}

	wv515_mc_wesume(wdev, &save);
}

static int w520_stawtup(stwuct wadeon_device *wdev)
{
	int w;

	w520_mc_pwogwam(wdev);
	/* Wesume cwock */
	wv515_cwock_stawtup(wdev);
	/* Initiawize GPU configuwation (# pipes, ...) */
	w520_gpu_init(wdev);
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

int w520_wesume(stwuct wadeon_device *wdev)
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
	w = w520_stawtup(wdev);
	if (w) {
		wdev->accew_wowking = fawse;
	}
	wetuwn w;
}

int w520_init(stwuct wadeon_device *wdev)
{
	int w;

	/* Initiawize scwatch wegistews */
	wadeon_scwatch_init(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);
	/* westowe some wegistew to sane defauwts */
	w100_westowe_sanity(wdev);
	/* TODO: disabwe VGA need to use VGA wequest */
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

	if (!wadeon_cawd_posted(wdev) && wdev->bios) {
		DWM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(wdev->mode_info.atom_context);
	}
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
	w520_mc_init(wdev);
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
	w = w520_stawtup(wdev);
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
