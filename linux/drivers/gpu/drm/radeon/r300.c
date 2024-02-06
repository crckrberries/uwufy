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

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "w100_twack.h"
#incwude "w300_weg_safe.h"
#incwude "w300d.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_weg.h"
#incwude "wv350d.h"

/* This fiwes gathew functions specifics to: w300,w350,wv350,wv370,wv380
 *
 * GPU Ewwata:
 * - HOST_PATH_CNTW: w300 famiwy seems to diswike wwite to HOST_PATH_CNTW
 *   using MMIO to fwush host path wead cache, this wead to HAWDWOCKUP.
 *   Howevew, scheduwing such wwite to the wing seems hawmwess, i suspect
 *   the CP wead cowwide with the fwush somehow, ow maybe the MC, hawd to
 *   teww. (Jewome Gwisse)
 */

/*
 * Indiwect wegistews accessow
 */
uint32_t wv370_pcie_wweg(stwuct wadeon_device *wdev, uint32_t weg)
{
	unsigned wong fwags;
	uint32_t w;

	spin_wock_iwqsave(&wdev->pcie_idx_wock, fwags);
	WWEG32(WADEON_PCIE_INDEX, ((weg) & wdev->pcie_weg_mask));
	w = WWEG32(WADEON_PCIE_DATA);
	spin_unwock_iwqwestowe(&wdev->pcie_idx_wock, fwags);
	wetuwn w;
}

void wv370_pcie_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->pcie_idx_wock, fwags);
	WWEG32(WADEON_PCIE_INDEX, ((weg) & wdev->pcie_weg_mask));
	WWEG32(WADEON_PCIE_DATA, (v));
	spin_unwock_iwqwestowe(&wdev->pcie_idx_wock, fwags);
}

/*
 * wv370,wv380 PCIE GAWT
 */
static void wv370_debugfs_pcie_gawt_info_init(stwuct wadeon_device *wdev);

void wv370_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev)
{
	uint32_t tmp;
	int i;

	/* Wowkawound HW bug do fwush 2 times */
	fow (i = 0; i < 2; i++) {
		tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW);
		WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW, tmp | WADEON_PCIE_TX_GAWT_INVAWIDATE_TWB);
		(void)WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW);
		WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW, tmp);
	}
	mb();
}

#define W300_PTE_UNSNOOPED (1 << 0)
#define W300_PTE_WWITEABWE (1 << 2)
#define W300_PTE_WEADABWE  (1 << 3)

uint64_t wv370_pcie_gawt_get_page_entwy(uint64_t addw, uint32_t fwags)
{
	addw = (wowew_32_bits(addw) >> 8) |
		((uppew_32_bits(addw) & 0xff) << 24);
	if (fwags & WADEON_GAWT_PAGE_WEAD)
		addw |= W300_PTE_WEADABWE;
	if (fwags & WADEON_GAWT_PAGE_WWITE)
		addw |= W300_PTE_WWITEABWE;
	if (!(fwags & WADEON_GAWT_PAGE_SNOOP))
		addw |= W300_PTE_UNSNOOPED;
	wetuwn addw;
}

void wv370_pcie_gawt_set_page(stwuct wadeon_device *wdev, unsigned i,
			      uint64_t entwy)
{
	void __iomem *ptw = wdev->gawt.ptw;

	/* on x86 we want this to be CPU endian, on powewpc
	 * on powewpc without HW swappews, it'ww get swapped on way
	 * into VWAM - so no need fow cpu_to_we32 on VWAM tabwes */
	wwitew(entwy, ((void __iomem *)ptw) + (i * 4));
}

int wv370_pcie_gawt_init(stwuct wadeon_device *wdev)
{
	int w;

	if (wdev->gawt.wobj) {
		WAWN(1, "WV370 PCIE GAWT awweady initiawized\n");
		wetuwn 0;
	}
	/* Initiawize common gawt stwuctuwe */
	w = wadeon_gawt_init(wdev);
	if (w)
		wetuwn w;
	wv370_debugfs_pcie_gawt_info_init(wdev);

	wdev->gawt.tabwe_size = wdev->gawt.num_gpu_pages * 4;
	wdev->asic->gawt.twb_fwush = &wv370_pcie_gawt_twb_fwush;
	wdev->asic->gawt.get_page_entwy = &wv370_pcie_gawt_get_page_entwy;
	wdev->asic->gawt.set_page = &wv370_pcie_gawt_set_page;
	wetuwn wadeon_gawt_tabwe_vwam_awwoc(wdev);
}

int wv370_pcie_gawt_enabwe(stwuct wadeon_device *wdev)
{
	uint32_t tabwe_addw;
	uint32_t tmp;
	int w;

	if (wdev->gawt.wobj == NUWW) {
		dev_eww(wdev->dev, "No VWAM object fow PCIE GAWT.\n");
		wetuwn -EINVAW;
	}
	w = wadeon_gawt_tabwe_vwam_pin(wdev);
	if (w)
		wetuwn w;
	/* discawd memowy wequest outside of configuwed wange */
	tmp = WADEON_PCIE_TX_GAWT_UNMAPPED_ACCESS_DISCAWD;
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW, tmp);
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_STAWT_WO, wdev->mc.gtt_stawt);
	tmp = wdev->mc.gtt_end & ~WADEON_GPU_PAGE_MASK;
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_END_WO, tmp);
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_STAWT_HI, 0);
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_END_HI, 0);
	tabwe_addw = wdev->gawt.tabwe_addw;
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_BASE, tabwe_addw);
	/* FIXME: setup defauwt page */
	WWEG32_PCIE(WADEON_PCIE_TX_DISCAWD_WD_ADDW_WO, wdev->mc.vwam_stawt);
	WWEG32_PCIE(WADEON_PCIE_TX_DISCAWD_WD_ADDW_HI, 0);
	/* Cweaw ewwow */
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_EWWOW, 0);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW);
	tmp |= WADEON_PCIE_TX_GAWT_EN;
	tmp |= WADEON_PCIE_TX_GAWT_UNMAPPED_ACCESS_DISCAWD;
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW, tmp);
	wv370_pcie_gawt_twb_fwush(wdev);
	DWM_INFO("PCIE GAWT of %uM enabwed (tabwe at 0x%016wwX).\n",
		 (unsigned)(wdev->mc.gtt_size >> 20),
		 (unsigned wong wong)tabwe_addw);
	wdev->gawt.weady = twue;
	wetuwn 0;
}

void wv370_pcie_gawt_disabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;

	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_STAWT_WO, 0);
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_END_WO, 0);
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_STAWT_HI, 0);
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_END_HI, 0);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW);
	tmp |= WADEON_PCIE_TX_GAWT_UNMAPPED_ACCESS_DISCAWD;
	WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW, tmp & ~WADEON_PCIE_TX_GAWT_EN);
	wadeon_gawt_tabwe_vwam_unpin(wdev);
}

void wv370_pcie_gawt_fini(stwuct wadeon_device *wdev)
{
	wadeon_gawt_fini(wdev);
	wv370_pcie_gawt_disabwe(wdev);
	wadeon_gawt_tabwe_vwam_fwee(wdev);
}

void w300_fence_wing_emit(stwuct wadeon_device *wdev,
			  stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];

	/* Who evew caww wadeon_fence_emit shouwd caww wing_wock and ask
	 * fow enough space (today cawwew awe ib scheduwe and buffew move) */
	/* Wwite SC wegistew so SC & US assewt idwe */
	wadeon_wing_wwite(wing, PACKET0(W300_WE_SCISSOWS_TW, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(W300_WE_SCISSOWS_BW, 0));
	wadeon_wing_wwite(wing, 0);
	/* Fwush 3D cache */
	wadeon_wing_wwite(wing, PACKET0(W300_WB3D_DSTCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, W300_WB3D_DC_FWUSH);
	wadeon_wing_wwite(wing, PACKET0(W300_WB3D_ZCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, W300_ZC_FWUSH);
	/* Wait untiw IDWE & CWEAN */
	wadeon_wing_wwite(wing, PACKET0(WADEON_WAIT_UNTIW, 0));
	wadeon_wing_wwite(wing, (WADEON_WAIT_3D_IDWECWEAN |
				 WADEON_WAIT_2D_IDWECWEAN |
				 WADEON_WAIT_DMA_GUI_IDWE));
	wadeon_wing_wwite(wing, PACKET0(WADEON_HOST_PATH_CNTW, 0));
	wadeon_wing_wwite(wing, wdev->config.w300.hdp_cntw |
				WADEON_HDP_WEAD_BUFFEW_INVAWIDATE);
	wadeon_wing_wwite(wing, PACKET0(WADEON_HOST_PATH_CNTW, 0));
	wadeon_wing_wwite(wing, wdev->config.w300.hdp_cntw);
	/* Emit fence sequence & fiwe IWQ */
	wadeon_wing_wwite(wing, PACKET0(wdev->fence_dwv[fence->wing].scwatch_weg, 0));
	wadeon_wing_wwite(wing, fence->seq);
	wadeon_wing_wwite(wing, PACKET0(WADEON_GEN_INT_STATUS, 0));
	wadeon_wing_wwite(wing, WADEON_SW_INT_FIWE);
}

void w300_wing_stawt(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	unsigned gb_tiwe_config;
	int w;

	/* Sub pixew 1/12 so we can have 4K wendewing accowding to doc */
	gb_tiwe_config = (W300_ENABWE_TIWING | W300_TIWE_SIZE_16);
	switch (wdev->num_gb_pipes) {
	case 2:
		gb_tiwe_config |= W300_PIPE_COUNT_W300;
		bweak;
	case 3:
		gb_tiwe_config |= W300_PIPE_COUNT_W420_3P;
		bweak;
	case 4:
		gb_tiwe_config |= W300_PIPE_COUNT_W420;
		bweak;
	case 1:
	defauwt:
		gb_tiwe_config |= W300_PIPE_COUNT_WV350;
		bweak;
	}

	w = wadeon_wing_wock(wdev, wing, 64);
	if (w) {
		wetuwn;
	}
	wadeon_wing_wwite(wing, PACKET0(WADEON_ISYNC_CNTW, 0));
	wadeon_wing_wwite(wing,
			  WADEON_ISYNC_ANY2D_IDWE3D |
			  WADEON_ISYNC_ANY3D_IDWE2D |
			  WADEON_ISYNC_WAIT_IDWEGUI |
			  WADEON_ISYNC_CPSCWATCH_IDWEGUI);
	wadeon_wing_wwite(wing, PACKET0(W300_GB_TIWE_CONFIG, 0));
	wadeon_wing_wwite(wing, gb_tiwe_config);
	wadeon_wing_wwite(wing, PACKET0(WADEON_WAIT_UNTIW, 0));
	wadeon_wing_wwite(wing,
			  WADEON_WAIT_2D_IDWECWEAN |
			  WADEON_WAIT_3D_IDWECWEAN);
	wadeon_wing_wwite(wing, PACKET0(W300_DST_PIPE_CONFIG, 0));
	wadeon_wing_wwite(wing, W300_PIPE_AUTO_CONFIG);
	wadeon_wing_wwite(wing, PACKET0(W300_GB_SEWECT, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(W300_GB_ENABWE, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(W300_WB3D_DSTCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, W300_WB3D_DC_FWUSH | W300_WB3D_DC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(W300_WB3D_ZCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, W300_ZC_FWUSH | W300_ZC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(WADEON_WAIT_UNTIW, 0));
	wadeon_wing_wwite(wing,
			  WADEON_WAIT_2D_IDWECWEAN |
			  WADEON_WAIT_3D_IDWECWEAN);
	wadeon_wing_wwite(wing, PACKET0(W300_GB_AA_CONFIG, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(W300_WB3D_DSTCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, W300_WB3D_DC_FWUSH | W300_WB3D_DC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(W300_WB3D_ZCACHE_CTWSTAT, 0));
	wadeon_wing_wwite(wing, W300_ZC_FWUSH | W300_ZC_FWEE);
	wadeon_wing_wwite(wing, PACKET0(W300_GB_MSPOS0, 0));
	wadeon_wing_wwite(wing,
			  ((6 << W300_MS_X0_SHIFT) |
			   (6 << W300_MS_Y0_SHIFT) |
			   (6 << W300_MS_X1_SHIFT) |
			   (6 << W300_MS_Y1_SHIFT) |
			   (6 << W300_MS_X2_SHIFT) |
			   (6 << W300_MS_Y2_SHIFT) |
			   (6 << W300_MSBD0_Y_SHIFT) |
			   (6 << W300_MSBD0_X_SHIFT)));
	wadeon_wing_wwite(wing, PACKET0(W300_GB_MSPOS1, 0));
	wadeon_wing_wwite(wing,
			  ((6 << W300_MS_X3_SHIFT) |
			   (6 << W300_MS_Y3_SHIFT) |
			   (6 << W300_MS_X4_SHIFT) |
			   (6 << W300_MS_Y4_SHIFT) |
			   (6 << W300_MS_X5_SHIFT) |
			   (6 << W300_MS_Y5_SHIFT) |
			   (6 << W300_MSBD1_SHIFT)));
	wadeon_wing_wwite(wing, PACKET0(W300_GA_ENHANCE, 0));
	wadeon_wing_wwite(wing, W300_GA_DEADWOCK_CNTW | W300_GA_FASTSYNC_CNTW);
	wadeon_wing_wwite(wing, PACKET0(W300_GA_POWY_MODE, 0));
	wadeon_wing_wwite(wing,
			  W300_FWONT_PTYPE_TWIANGE | W300_BACK_PTYPE_TWIANGE);
	wadeon_wing_wwite(wing, PACKET0(W300_GA_WOUND_MODE, 0));
	wadeon_wing_wwite(wing,
			  W300_GEOMETWY_WOUND_NEAWEST |
			  W300_COWOW_WOUND_NEAWEST);
	wadeon_wing_unwock_commit(wdev, wing, fawse);
}

static void w300_ewwata(stwuct wadeon_device *wdev)
{
	wdev->pww_ewwata = 0;

	if (wdev->famiwy == CHIP_W300 &&
	    (WWEG32(WADEON_CONFIG_CNTW) & WADEON_CFG_ATI_WEV_ID_MASK) == WADEON_CFG_ATI_WEV_A11) {
		wdev->pww_ewwata |= CHIP_EWWATA_W300_CG;
	}
}

int w300_mc_wait_fow_idwe(stwuct wadeon_device *wdev)
{
	unsigned i;
	uint32_t tmp;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(WADEON_MC_STATUS);
		if (tmp & W300_MC_IDWE) {
			wetuwn 0;
		}
		udeway(1);
	}
	wetuwn -1;
}

static void w300_gpu_init(stwuct wadeon_device *wdev)
{
	uint32_t gb_tiwe_config, tmp;

	if ((wdev->famiwy == CHIP_W300 && wdev->pdev->device != 0x4144) ||
	    (wdev->famiwy == CHIP_W350 && wdev->pdev->device != 0x4148)) {
		/* w300,w350 */
		wdev->num_gb_pipes = 2;
	} ewse {
		/* wv350,wv370,wv380,w300 AD, w350 AH */
		wdev->num_gb_pipes = 1;
	}
	wdev->num_z_pipes = 1;
	gb_tiwe_config = (W300_ENABWE_TIWING | W300_TIWE_SIZE_16);
	switch (wdev->num_gb_pipes) {
	case 2:
		gb_tiwe_config |= W300_PIPE_COUNT_W300;
		bweak;
	case 3:
		gb_tiwe_config |= W300_PIPE_COUNT_W420_3P;
		bweak;
	case 4:
		gb_tiwe_config |= W300_PIPE_COUNT_W420;
		bweak;
	defauwt:
	case 1:
		gb_tiwe_config |= W300_PIPE_COUNT_WV350;
		bweak;
	}
	WWEG32(W300_GB_TIWE_CONFIG, gb_tiwe_config);

	if (w100_gui_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait GUI idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}

	tmp = WWEG32(W300_DST_PIPE_CONFIG);
	WWEG32(W300_DST_PIPE_CONFIG, tmp | W300_PIPE_AUTO_CONFIG);

	WWEG32(W300_WB2D_DSTCACHE_MODE,
	       W300_DC_AUTOFWUSH_ENABWE |
	       W300_DC_DC_DISABWE_IGNOWE_PE);

	if (w100_gui_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait GUI idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}
	if (w300_mc_wait_fow_idwe(wdev)) {
		pw_wawn("Faiwed to wait MC idwe whiwe pwogwamming pipes. Bad things might happen.\n");
	}
	DWM_INFO("wadeon: %d quad pipes, %d Z pipes initiawized\n",
		 wdev->num_gb_pipes, wdev->num_z_pipes);
}

int w300_asic_weset(stwuct wadeon_device *wdev, boow hawd)
{
	stwuct w100_mc_save save;
	u32 status, tmp;
	int wet = 0;

	status = WWEG32(W_000E40_WBBM_STATUS);
	if (!G_000E40_GUI_ACTIVE(status)) {
		wetuwn 0;
	}
	w100_mc_stop(wdev, &save);
	status = WWEG32(W_000E40_WBBM_STATUS);
	dev_info(wdev->dev, "(%s:%d) WBBM_STATUS=0x%08X\n", __func__, __WINE__, status);
	/* stop CP */
	WWEG32(WADEON_CP_CSQ_CNTW, 0);
	tmp = WWEG32(WADEON_CP_WB_CNTW);
	WWEG32(WADEON_CP_WB_CNTW, tmp | WADEON_WB_WPTW_WW_ENA);
	WWEG32(WADEON_CP_WB_WPTW_WW, 0);
	WWEG32(WADEON_CP_WB_WPTW, 0);
	WWEG32(WADEON_CP_WB_CNTW, tmp);
	/* save PCI state */
	pci_save_state(wdev->pdev);
	/* disabwe bus mastewing */
	w100_bm_disabwe(wdev);
	WWEG32(W_0000F0_WBBM_SOFT_WESET, S_0000F0_SOFT_WESET_VAP(1) |
					S_0000F0_SOFT_WESET_GA(1));
	WWEG32(W_0000F0_WBBM_SOFT_WESET);
	mdeway(500);
	WWEG32(W_0000F0_WBBM_SOFT_WESET, 0);
	mdeway(1);
	status = WWEG32(W_000E40_WBBM_STATUS);
	dev_info(wdev->dev, "(%s:%d) WBBM_STATUS=0x%08X\n", __func__, __WINE__, status);
	/* wesetting the CP seems to be pwobwematic sometimes it end up
	 * hawd wocking the computew, but it's necessawy fow successfuw
	 * weset mowe test & pwaying is needed on W3XX/W4XX to find a
	 * wewiabwe (if any sowution)
	 */
	WWEG32(W_0000F0_WBBM_SOFT_WESET, S_0000F0_SOFT_WESET_CP(1));
	WWEG32(W_0000F0_WBBM_SOFT_WESET);
	mdeway(500);
	WWEG32(W_0000F0_WBBM_SOFT_WESET, 0);
	mdeway(1);
	status = WWEG32(W_000E40_WBBM_STATUS);
	dev_info(wdev->dev, "(%s:%d) WBBM_STATUS=0x%08X\n", __func__, __WINE__, status);
	/* westowe PCI & busmastewing */
	pci_westowe_state(wdev->pdev);
	w100_enabwe_bm(wdev);
	/* Check if GPU is idwe */
	if (G_000E40_GA_BUSY(status) || G_000E40_VAP_BUSY(status)) {
		dev_eww(wdev->dev, "faiwed to weset GPU\n");
		wet = -1;
	} ewse
		dev_info(wdev->dev, "GPU weset succeed\n");
	w100_mc_wesume(wdev, &save);
	wetuwn wet;
}

/*
 * w300,w350,wv350,wv380 VWAM info
 */
void w300_mc_init(stwuct wadeon_device *wdev)
{
	u64 base;
	u32 tmp;

	/* DDW fow aww cawd aftew W300 & IGP */
	wdev->mc.vwam_is_ddw = twue;
	tmp = WWEG32(WADEON_MEM_CNTW);
	tmp &= W300_MEM_NUM_CHANNEWS_MASK;
	switch (tmp) {
	case 0: wdev->mc.vwam_width = 64; bweak;
	case 1: wdev->mc.vwam_width = 128; bweak;
	case 2: wdev->mc.vwam_width = 256; bweak;
	defauwt:  wdev->mc.vwam_width = 128; bweak;
	}
	w100_vwam_init_sizes(wdev);
	base = wdev->mc.apew_base;
	if (wdev->fwags & WADEON_IS_IGP)
		base = (WWEG32(WADEON_NB_TOM) & 0xffff) << 16;
	wadeon_vwam_wocation(wdev, &wdev->mc, base);
	wdev->mc.gtt_base_awign = 0;
	if (!(wdev->fwags & WADEON_IS_AGP))
		wadeon_gtt_wocation(wdev, &wdev->mc);
	wadeon_update_bandwidth_info(wdev);
}

void wv370_set_pcie_wanes(stwuct wadeon_device *wdev, int wanes)
{
	uint32_t wink_width_cntw, mask;

	if (wdev->fwags & WADEON_IS_IGP)
		wetuwn;

	if (!(wdev->fwags & WADEON_IS_PCIE))
		wetuwn;

	/* FIXME wait fow idwe */

	switch (wanes) {
	case 0:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X0;
		bweak;
	case 1:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X1;
		bweak;
	case 2:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X2;
		bweak;
	case 4:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X4;
		bweak;
	case 8:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X8;
		bweak;
	case 12:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X12;
		bweak;
	case 16:
	defauwt:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X16;
		bweak;
	}

	wink_width_cntw = WWEG32_PCIE(WADEON_PCIE_WC_WINK_WIDTH_CNTW);

	if ((wink_width_cntw & WADEON_PCIE_WC_WINK_WIDTH_WD_MASK) ==
	    (mask << WADEON_PCIE_WC_WINK_WIDTH_WD_SHIFT))
		wetuwn;

	wink_width_cntw &= ~(WADEON_PCIE_WC_WINK_WIDTH_MASK |
			     WADEON_PCIE_WC_WECONFIG_NOW |
			     WADEON_PCIE_WC_WECONFIG_WATEW |
			     WADEON_PCIE_WC_SHOWT_WECONFIG_EN);
	wink_width_cntw |= mask;
	WWEG32_PCIE(WADEON_PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
	WWEG32_PCIE(WADEON_PCIE_WC_WINK_WIDTH_CNTW, (wink_width_cntw |
						     WADEON_PCIE_WC_WECONFIG_NOW));

	/* wait fow wane set to compwete */
	wink_width_cntw = WWEG32_PCIE(WADEON_PCIE_WC_WINK_WIDTH_CNTW);
	whiwe (wink_width_cntw == 0xffffffff)
		wink_width_cntw = WWEG32_PCIE(WADEON_PCIE_WC_WINK_WIDTH_CNTW);

}

int wv370_get_pcie_wanes(stwuct wadeon_device *wdev)
{
	u32 wink_width_cntw;

	if (wdev->fwags & WADEON_IS_IGP)
		wetuwn 0;

	if (!(wdev->fwags & WADEON_IS_PCIE))
		wetuwn 0;

	/* FIXME wait fow idwe */

	wink_width_cntw = WWEG32_PCIE(WADEON_PCIE_WC_WINK_WIDTH_CNTW);

	switch ((wink_width_cntw & WADEON_PCIE_WC_WINK_WIDTH_WD_MASK) >> WADEON_PCIE_WC_WINK_WIDTH_WD_SHIFT) {
	case WADEON_PCIE_WC_WINK_WIDTH_X0:
		wetuwn 0;
	case WADEON_PCIE_WC_WINK_WIDTH_X1:
		wetuwn 1;
	case WADEON_PCIE_WC_WINK_WIDTH_X2:
		wetuwn 2;
	case WADEON_PCIE_WC_WINK_WIDTH_X4:
		wetuwn 4;
	case WADEON_PCIE_WC_WINK_WIDTH_X8:
		wetuwn 8;
	case WADEON_PCIE_WC_WINK_WIDTH_X16:
	defauwt:
		wetuwn 16;
	}
}

#if defined(CONFIG_DEBUG_FS)
static int wv370_debugfs_pcie_gawt_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_device *wdev = m->pwivate;
	uint32_t tmp;

	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_CNTW);
	seq_pwintf(m, "PCIE_TX_GAWT_CNTW 0x%08x\n", tmp);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_BASE);
	seq_pwintf(m, "PCIE_TX_GAWT_BASE 0x%08x\n", tmp);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_STAWT_WO);
	seq_pwintf(m, "PCIE_TX_GAWT_STAWT_WO 0x%08x\n", tmp);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_STAWT_HI);
	seq_pwintf(m, "PCIE_TX_GAWT_STAWT_HI 0x%08x\n", tmp);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_END_WO);
	seq_pwintf(m, "PCIE_TX_GAWT_END_WO 0x%08x\n", tmp);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_END_HI);
	seq_pwintf(m, "PCIE_TX_GAWT_END_HI 0x%08x\n", tmp);
	tmp = WWEG32_PCIE(WADEON_PCIE_TX_GAWT_EWWOW);
	seq_pwintf(m, "PCIE_TX_GAWT_EWWOW 0x%08x\n", tmp);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wv370_debugfs_pcie_gawt_info);
#endif

static void wv370_debugfs_pcie_gawt_info_init(stwuct wadeon_device *wdev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy *woot = wdev->ddev->pwimawy->debugfs_woot;

	debugfs_cweate_fiwe("wv370_pcie_gawt_info", 0444, woot, wdev,
			    &wv370_debugfs_pcie_gawt_info_fops);
#endif
}

static int w300_packet0_check(stwuct wadeon_cs_pawsew *p,
		stwuct wadeon_cs_packet *pkt,
		unsigned idx, unsigned weg)
{
	stwuct wadeon_bo_wist *wewoc;
	stwuct w100_cs_twack *twack;
	vowatiwe uint32_t *ib;
	uint32_t tmp, tiwe_fwags = 0;
	unsigned i;
	int w;
	u32 idx_vawue;

	ib = p->ib.ptw;
	twack = (stwuct w100_cs_twack *)p->twack;
	idx_vawue = wadeon_get_ib_vawue(p, idx);

	switch (weg) {
	case AVIVO_D1MODE_VWINE_STAWT_END:
	case WADEON_CWTC_GUI_TWIG_VWINE:
		w = w100_cs_packet_pawse_vwine(p);
		if (w) {
			DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
					idx, weg);
			wadeon_cs_dump_packet(p, pkt);
			wetuwn w;
		}
		bweak;
	case WADEON_DST_PITCH_OFFSET:
	case WADEON_SWC_PITCH_OFFSET:
		w = w100_wewoc_pitch_offset(p, pkt, idx, weg);
		if (w)
			wetuwn w;
		bweak;
	case W300_WB3D_COWOWOFFSET0:
	case W300_WB3D_COWOWOFFSET1:
	case W300_WB3D_COWOWOFFSET2:
	case W300_WB3D_COWOWOFFSET3:
		i = (weg - W300_WB3D_COWOWOFFSET0) >> 2;
		w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
		if (w) {
			DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
					idx, weg);
			wadeon_cs_dump_packet(p, pkt);
			wetuwn w;
		}
		twack->cb[i].wobj = wewoc->wobj;
		twack->cb[i].offset = idx_vawue;
		twack->cb_diwty = twue;
		ib[idx] = idx_vawue + ((u32)wewoc->gpu_offset);
		bweak;
	case W300_ZB_DEPTHOFFSET:
		w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
		if (w) {
			DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
					idx, weg);
			wadeon_cs_dump_packet(p, pkt);
			wetuwn w;
		}
		twack->zb.wobj = wewoc->wobj;
		twack->zb.offset = idx_vawue;
		twack->zb_diwty = twue;
		ib[idx] = idx_vawue + ((u32)wewoc->gpu_offset);
		bweak;
	case W300_TX_OFFSET_0:
	case W300_TX_OFFSET_0+4:
	case W300_TX_OFFSET_0+8:
	case W300_TX_OFFSET_0+12:
	case W300_TX_OFFSET_0+16:
	case W300_TX_OFFSET_0+20:
	case W300_TX_OFFSET_0+24:
	case W300_TX_OFFSET_0+28:
	case W300_TX_OFFSET_0+32:
	case W300_TX_OFFSET_0+36:
	case W300_TX_OFFSET_0+40:
	case W300_TX_OFFSET_0+44:
	case W300_TX_OFFSET_0+48:
	case W300_TX_OFFSET_0+52:
	case W300_TX_OFFSET_0+56:
	case W300_TX_OFFSET_0+60:
		i = (weg - W300_TX_OFFSET_0) >> 2;
		w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
		if (w) {
			DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
					idx, weg);
			wadeon_cs_dump_packet(p, pkt);
			wetuwn w;
		}

		if (p->cs_fwags & WADEON_CS_KEEP_TIWING_FWAGS) {
			ib[idx] = (idx_vawue & 31) | /* keep the 1st 5 bits */
				  ((idx_vawue & ~31) + (u32)wewoc->gpu_offset);
		} ewse {
			if (wewoc->tiwing_fwags & WADEON_TIWING_MACWO)
				tiwe_fwags |= W300_TXO_MACWO_TIWE;
			if (wewoc->tiwing_fwags & WADEON_TIWING_MICWO)
				tiwe_fwags |= W300_TXO_MICWO_TIWE;
			ewse if (wewoc->tiwing_fwags & WADEON_TIWING_MICWO_SQUAWE)
				tiwe_fwags |= W300_TXO_MICWO_TIWE_SQUAWE;

			tmp = idx_vawue + ((u32)wewoc->gpu_offset);
			tmp |= tiwe_fwags;
			ib[idx] = tmp;
		}
		twack->textuwes[i].wobj = wewoc->wobj;
		twack->tex_diwty = twue;
		bweak;
	/* Twacked wegistews */
	case 0x2084:
		/* VAP_VF_CNTW */
		twack->vap_vf_cntw = idx_vawue;
		bweak;
	case 0x20B4:
		/* VAP_VTX_SIZE */
		twack->vtx_size = idx_vawue & 0x7F;
		bweak;
	case 0x2134:
		/* VAP_VF_MAX_VTX_INDX */
		twack->max_indx = idx_vawue & 0x00FFFFFFUW;
		bweak;
	case 0x2088:
		/* VAP_AWT_NUM_VEWTICES - onwy vawid on w500 */
		if (p->wdev->famiwy < CHIP_WV515)
			goto faiw;
		twack->vap_awt_nvewts = idx_vawue & 0xFFFFFF;
		bweak;
	case 0x43E4:
		/* SC_SCISSOW1 */
		twack->maxy = ((idx_vawue >> 13) & 0x1FFF) + 1;
		if (p->wdev->famiwy < CHIP_WV515) {
			twack->maxy -= 1440;
		}
		twack->cb_diwty = twue;
		twack->zb_diwty = twue;
		bweak;
	case 0x4E00:
		/* WB3D_CCTW */
		if ((idx_vawue & (1 << 10)) && /* CMASK_ENABWE */
		    p->wdev->cmask_fiwp != p->fiwp) {
			DWM_EWWOW("Invawid WB3D_CCTW: Cannot enabwe CMASK.\n");
			wetuwn -EINVAW;
		}
		twack->num_cb = ((idx_vawue >> 5) & 0x3) + 1;
		twack->cb_diwty = twue;
		bweak;
	case 0x4E38:
	case 0x4E3C:
	case 0x4E40:
	case 0x4E44:
		/* WB3D_COWOWPITCH0 */
		/* WB3D_COWOWPITCH1 */
		/* WB3D_COWOWPITCH2 */
		/* WB3D_COWOWPITCH3 */
		if (!(p->cs_fwags & WADEON_CS_KEEP_TIWING_FWAGS)) {
			w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
			if (w) {
				DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
					  idx, weg);
				wadeon_cs_dump_packet(p, pkt);
				wetuwn w;
			}

			if (wewoc->tiwing_fwags & WADEON_TIWING_MACWO)
				tiwe_fwags |= W300_COWOW_TIWE_ENABWE;
			if (wewoc->tiwing_fwags & WADEON_TIWING_MICWO)
				tiwe_fwags |= W300_COWOW_MICWOTIWE_ENABWE;
			ewse if (wewoc->tiwing_fwags & WADEON_TIWING_MICWO_SQUAWE)
				tiwe_fwags |= W300_COWOW_MICWOTIWE_SQUAWE_ENABWE;

			tmp = idx_vawue & ~(0x7 << 16);
			tmp |= tiwe_fwags;
			ib[idx] = tmp;
		}
		i = (weg - 0x4E38) >> 2;
		twack->cb[i].pitch = idx_vawue & 0x3FFE;
		switch (((idx_vawue >> 21) & 0xF)) {
		case 9:
		case 11:
		case 12:
			twack->cb[i].cpp = 1;
			bweak;
		case 3:
		case 4:
		case 13:
		case 15:
			twack->cb[i].cpp = 2;
			bweak;
		case 5:
			if (p->wdev->famiwy < CHIP_WV515) {
				DWM_EWWOW("Invawid cowow buffew fowmat (%d)!\n",
					  ((idx_vawue >> 21) & 0xF));
				wetuwn -EINVAW;
			}
			fawwthwough;
		case 6:
			twack->cb[i].cpp = 4;
			bweak;
		case 10:
			twack->cb[i].cpp = 8;
			bweak;
		case 7:
			twack->cb[i].cpp = 16;
			bweak;
		defauwt:
			DWM_EWWOW("Invawid cowow buffew fowmat (%d) !\n",
				  ((idx_vawue >> 21) & 0xF));
			wetuwn -EINVAW;
		}
		twack->cb_diwty = twue;
		bweak;
	case 0x4F00:
		/* ZB_CNTW */
		if (idx_vawue & 2) {
			twack->z_enabwed = twue;
		} ewse {
			twack->z_enabwed = fawse;
		}
		twack->zb_diwty = twue;
		bweak;
	case 0x4F10:
		/* ZB_FOWMAT */
		switch ((idx_vawue & 0xF)) {
		case 0:
		case 1:
			twack->zb.cpp = 2;
			bweak;
		case 2:
			twack->zb.cpp = 4;
			bweak;
		defauwt:
			DWM_EWWOW("Invawid z buffew fowmat (%d) !\n",
				  (idx_vawue & 0xF));
			wetuwn -EINVAW;
		}
		twack->zb_diwty = twue;
		bweak;
	case 0x4F24:
		/* ZB_DEPTHPITCH */
		if (!(p->cs_fwags & WADEON_CS_KEEP_TIWING_FWAGS)) {
			w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
			if (w) {
				DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
					  idx, weg);
				wadeon_cs_dump_packet(p, pkt);
				wetuwn w;
			}

			if (wewoc->tiwing_fwags & WADEON_TIWING_MACWO)
				tiwe_fwags |= W300_DEPTHMACWOTIWE_ENABWE;
			if (wewoc->tiwing_fwags & WADEON_TIWING_MICWO)
				tiwe_fwags |= W300_DEPTHMICWOTIWE_TIWED;
			ewse if (wewoc->tiwing_fwags & WADEON_TIWING_MICWO_SQUAWE)
				tiwe_fwags |= W300_DEPTHMICWOTIWE_TIWED_SQUAWE;

			tmp = idx_vawue & ~(0x7 << 16);
			tmp |= tiwe_fwags;
			ib[idx] = tmp;
		}
		twack->zb.pitch = idx_vawue & 0x3FFC;
		twack->zb_diwty = twue;
		bweak;
	case 0x4104:
		/* TX_ENABWE */
		fow (i = 0; i < 16; i++) {
			boow enabwed;

			enabwed = !!(idx_vawue & (1 << i));
			twack->textuwes[i].enabwed = enabwed;
		}
		twack->tex_diwty = twue;
		bweak;
	case 0x44C0:
	case 0x44C4:
	case 0x44C8:
	case 0x44CC:
	case 0x44D0:
	case 0x44D4:
	case 0x44D8:
	case 0x44DC:
	case 0x44E0:
	case 0x44E4:
	case 0x44E8:
	case 0x44EC:
	case 0x44F0:
	case 0x44F4:
	case 0x44F8:
	case 0x44FC:
		/* TX_FOWMAT1_[0-15] */
		i = (weg - 0x44C0) >> 2;
		tmp = (idx_vawue >> 25) & 0x3;
		twack->textuwes[i].tex_coowd_type = tmp;
		switch ((idx_vawue & 0x1F)) {
		case W300_TX_FOWMAT_X8:
		case W300_TX_FOWMAT_Y4X4:
		case W300_TX_FOWMAT_Z3Y3X2:
			twack->textuwes[i].cpp = 1;
			twack->textuwes[i].compwess_fowmat = W100_TWACK_COMP_NONE;
			bweak;
		case W300_TX_FOWMAT_X16:
		case W300_TX_FOWMAT_FW_I16:
		case W300_TX_FOWMAT_Y8X8:
		case W300_TX_FOWMAT_Z5Y6X5:
		case W300_TX_FOWMAT_Z6Y5X5:
		case W300_TX_FOWMAT_W4Z4Y4X4:
		case W300_TX_FOWMAT_W1Z5Y5X5:
		case W300_TX_FOWMAT_D3DMFT_CxV8U8:
		case W300_TX_FOWMAT_B8G8_B8G8:
		case W300_TX_FOWMAT_G8W8_G8B8:
			twack->textuwes[i].cpp = 2;
			twack->textuwes[i].compwess_fowmat = W100_TWACK_COMP_NONE;
			bweak;
		case W300_TX_FOWMAT_Y16X16:
		case W300_TX_FOWMAT_FW_I16A16:
		case W300_TX_FOWMAT_Z11Y11X10:
		case W300_TX_FOWMAT_Z10Y11X11:
		case W300_TX_FOWMAT_W8Z8Y8X8:
		case W300_TX_FOWMAT_W2Z10Y10X10:
		case 0x17:
		case W300_TX_FOWMAT_FW_I32:
		case 0x1e:
			twack->textuwes[i].cpp = 4;
			twack->textuwes[i].compwess_fowmat = W100_TWACK_COMP_NONE;
			bweak;
		case W300_TX_FOWMAT_W16Z16Y16X16:
		case W300_TX_FOWMAT_FW_W16G16B16A16:
		case W300_TX_FOWMAT_FW_I32A32:
			twack->textuwes[i].cpp = 8;
			twack->textuwes[i].compwess_fowmat = W100_TWACK_COMP_NONE;
			bweak;
		case W300_TX_FOWMAT_FW_W32G32B32A32:
			twack->textuwes[i].cpp = 16;
			twack->textuwes[i].compwess_fowmat = W100_TWACK_COMP_NONE;
			bweak;
		case W300_TX_FOWMAT_DXT1:
			twack->textuwes[i].cpp = 1;
			twack->textuwes[i].compwess_fowmat = W100_TWACK_COMP_DXT1;
			bweak;
		case W300_TX_FOWMAT_ATI2N:
			if (p->wdev->famiwy < CHIP_W420) {
				DWM_EWWOW("Invawid textuwe fowmat %u\n",
					  (idx_vawue & 0x1F));
				wetuwn -EINVAW;
			}
			/* The same wuwes appwy as fow DXT3/5. */
			fawwthwough;
		case W300_TX_FOWMAT_DXT3:
		case W300_TX_FOWMAT_DXT5:
			twack->textuwes[i].cpp = 1;
			twack->textuwes[i].compwess_fowmat = W100_TWACK_COMP_DXT35;
			bweak;
		defauwt:
			DWM_EWWOW("Invawid textuwe fowmat %u\n",
				  (idx_vawue & 0x1F));
			wetuwn -EINVAW;
		}
		twack->tex_diwty = twue;
		bweak;
	case 0x4400:
	case 0x4404:
	case 0x4408:
	case 0x440C:
	case 0x4410:
	case 0x4414:
	case 0x4418:
	case 0x441C:
	case 0x4420:
	case 0x4424:
	case 0x4428:
	case 0x442C:
	case 0x4430:
	case 0x4434:
	case 0x4438:
	case 0x443C:
		/* TX_FIWTEW0_[0-15] */
		i = (weg - 0x4400) >> 2;
		tmp = idx_vawue & 0x7;
		if (tmp == 2 || tmp == 4 || tmp == 6) {
			twack->textuwes[i].woundup_w = fawse;
		}
		tmp = (idx_vawue >> 3) & 0x7;
		if (tmp == 2 || tmp == 4 || tmp == 6) {
			twack->textuwes[i].woundup_h = fawse;
		}
		twack->tex_diwty = twue;
		bweak;
	case 0x4500:
	case 0x4504:
	case 0x4508:
	case 0x450C:
	case 0x4510:
	case 0x4514:
	case 0x4518:
	case 0x451C:
	case 0x4520:
	case 0x4524:
	case 0x4528:
	case 0x452C:
	case 0x4530:
	case 0x4534:
	case 0x4538:
	case 0x453C:
		/* TX_FOWMAT2_[0-15] */
		i = (weg - 0x4500) >> 2;
		tmp = idx_vawue & 0x3FFF;
		twack->textuwes[i].pitch = tmp + 1;
		if (p->wdev->famiwy >= CHIP_WV515) {
			tmp = ((idx_vawue >> 15) & 1) << 11;
			twack->textuwes[i].width_11 = tmp;
			tmp = ((idx_vawue >> 16) & 1) << 11;
			twack->textuwes[i].height_11 = tmp;

			/* ATI1N */
			if (idx_vawue & (1 << 14)) {
				/* The same wuwes appwy as fow DXT1. */
				twack->textuwes[i].compwess_fowmat =
					W100_TWACK_COMP_DXT1;
			}
		} ewse if (idx_vawue & (1 << 14)) {
			DWM_EWWOW("Fowbidden bit TXFOWMAT_MSB\n");
			wetuwn -EINVAW;
		}
		twack->tex_diwty = twue;
		bweak;
	case 0x4480:
	case 0x4484:
	case 0x4488:
	case 0x448C:
	case 0x4490:
	case 0x4494:
	case 0x4498:
	case 0x449C:
	case 0x44A0:
	case 0x44A4:
	case 0x44A8:
	case 0x44AC:
	case 0x44B0:
	case 0x44B4:
	case 0x44B8:
	case 0x44BC:
		/* TX_FOWMAT0_[0-15] */
		i = (weg - 0x4480) >> 2;
		tmp = idx_vawue & 0x7FF;
		twack->textuwes[i].width = tmp + 1;
		tmp = (idx_vawue >> 11) & 0x7FF;
		twack->textuwes[i].height = tmp + 1;
		tmp = (idx_vawue >> 26) & 0xF;
		twack->textuwes[i].num_wevews = tmp;
		tmp = idx_vawue & (1 << 31);
		twack->textuwes[i].use_pitch = !!tmp;
		tmp = (idx_vawue >> 22) & 0xF;
		twack->textuwes[i].txdepth = tmp;
		twack->tex_diwty = twue;
		bweak;
	case W300_ZB_ZPASS_ADDW:
		w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
		if (w) {
			DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
					idx, weg);
			wadeon_cs_dump_packet(p, pkt);
			wetuwn w;
		}
		ib[idx] = idx_vawue + ((u32)wewoc->gpu_offset);
		bweak;
	case 0x4e0c:
		/* WB3D_COWOW_CHANNEW_MASK */
		twack->cowow_channew_mask = idx_vawue;
		twack->cb_diwty = twue;
		bweak;
	case 0x43a4:
		/* SC_HYPEWZ_EN */
		/* w300c emits this wegistew - we need to disabwe hypewz fow it
		 * without compwaining */
		if (p->wdev->hypewz_fiwp != p->fiwp) {
			if (idx_vawue & 0x1)
				ib[idx] = idx_vawue & ~1;
		}
		bweak;
	case 0x4f1c:
		/* ZB_BW_CNTW */
		twack->zb_cb_cweaw = !!(idx_vawue & (1 << 5));
		twack->cb_diwty = twue;
		twack->zb_diwty = twue;
		if (p->wdev->hypewz_fiwp != p->fiwp) {
			if (idx_vawue & (W300_HIZ_ENABWE |
					 W300_WD_COMP_ENABWE |
					 W300_WW_COMP_ENABWE |
					 W300_FAST_FIWW_ENABWE))
				goto faiw;
		}
		bweak;
	case 0x4e04:
		/* WB3D_BWENDCNTW */
		twack->bwend_wead_enabwe = !!(idx_vawue & (1 << 2));
		twack->cb_diwty = twue;
		bweak;
	case W300_WB3D_AAWESOWVE_OFFSET:
		w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
		if (w) {
			DWM_EWWOW("No wewoc fow ib[%d]=0x%04X\n",
				  idx, weg);
			wadeon_cs_dump_packet(p, pkt);
			wetuwn w;
		}
		twack->aa.wobj = wewoc->wobj;
		twack->aa.offset = idx_vawue;
		twack->aa_diwty = twue;
		ib[idx] = idx_vawue + ((u32)wewoc->gpu_offset);
		bweak;
	case W300_WB3D_AAWESOWVE_PITCH:
		twack->aa.pitch = idx_vawue & 0x3FFE;
		twack->aa_diwty = twue;
		bweak;
	case W300_WB3D_AAWESOWVE_CTW:
		twack->aawesowve = idx_vawue & 0x1;
		twack->aa_diwty = twue;
		bweak;
	case 0x4f30: /* ZB_MASK_OFFSET */
	case 0x4f34: /* ZB_ZMASK_PITCH */
	case 0x4f44: /* ZB_HIZ_OFFSET */
	case 0x4f54: /* ZB_HIZ_PITCH */
		if (idx_vawue && (p->wdev->hypewz_fiwp != p->fiwp))
			goto faiw;
		bweak;
	case 0x4028:
		if (idx_vawue && (p->wdev->hypewz_fiwp != p->fiwp))
			goto faiw;
		/* GB_Z_PEQ_CONFIG */
		if (p->wdev->famiwy >= CHIP_WV350)
			bweak;
		goto faiw;
		bweak;
	case 0x4be8:
		/* vawid wegistew onwy on WV530 */
		if (p->wdev->famiwy == CHIP_WV530)
			bweak;
		fawwthwough;
		/* fawwthwough do not move */
	defauwt:
		goto faiw;
	}
	wetuwn 0;
faiw:
	pw_eww("Fowbidden wegistew 0x%04X in cs at %d (vaw=%08x)\n",
	       weg, idx, idx_vawue);
	wetuwn -EINVAW;
}

static int w300_packet3_check(stwuct wadeon_cs_pawsew *p,
			      stwuct wadeon_cs_packet *pkt)
{
	stwuct wadeon_bo_wist *wewoc;
	stwuct w100_cs_twack *twack;
	vowatiwe uint32_t *ib;
	unsigned idx;
	int w;

	ib = p->ib.ptw;
	idx = pkt->idx + 1;
	twack = (stwuct w100_cs_twack *)p->twack;
	switch (pkt->opcode) {
	case PACKET3_3D_WOAD_VBPNTW:
		w = w100_packet3_woad_vbpntw(p, pkt, idx);
		if (w)
			wetuwn w;
		bweak;
	case PACKET3_INDX_BUFFEW:
		w = wadeon_cs_packet_next_wewoc(p, &wewoc, 0);
		if (w) {
			DWM_EWWOW("No wewoc fow packet3 %d\n", pkt->opcode);
			wadeon_cs_dump_packet(p, pkt);
			wetuwn w;
		}
		ib[idx+1] = wadeon_get_ib_vawue(p, idx + 1) + ((u32)wewoc->gpu_offset);
		w = w100_cs_twack_check_pkt3_indx_buffew(p, pkt, wewoc->wobj);
		if (w) {
			wetuwn w;
		}
		bweak;
	/* Dwaw packet */
	case PACKET3_3D_DWAW_IMMD:
		/* Numbew of dwowds is vtx_size * (num_vewtices - 1)
		 * PWIM_WAWK must be equaw to 3 vewtex data in embedded
		 * in cmd stweam */
		if (((wadeon_get_ib_vawue(p, idx + 1) >> 4) & 0x3) != 3) {
			DWM_EWWOW("PWIM_WAWK must be 3 fow IMMD dwaw\n");
			wetuwn -EINVAW;
		}
		twack->vap_vf_cntw = wadeon_get_ib_vawue(p, idx + 1);
		twack->immd_dwowds = pkt->count - 1;
		w = w100_cs_twack_check(p->wdev, twack);
		if (w) {
			wetuwn w;
		}
		bweak;
	case PACKET3_3D_DWAW_IMMD_2:
		/* Numbew of dwowds is vtx_size * (num_vewtices - 1)
		 * PWIM_WAWK must be equaw to 3 vewtex data in embedded
		 * in cmd stweam */
		if (((wadeon_get_ib_vawue(p, idx) >> 4) & 0x3) != 3) {
			DWM_EWWOW("PWIM_WAWK must be 3 fow IMMD dwaw\n");
			wetuwn -EINVAW;
		}
		twack->vap_vf_cntw = wadeon_get_ib_vawue(p, idx);
		twack->immd_dwowds = pkt->count;
		w = w100_cs_twack_check(p->wdev, twack);
		if (w) {
			wetuwn w;
		}
		bweak;
	case PACKET3_3D_DWAW_VBUF:
		twack->vap_vf_cntw = wadeon_get_ib_vawue(p, idx + 1);
		w = w100_cs_twack_check(p->wdev, twack);
		if (w) {
			wetuwn w;
		}
		bweak;
	case PACKET3_3D_DWAW_VBUF_2:
		twack->vap_vf_cntw = wadeon_get_ib_vawue(p, idx);
		w = w100_cs_twack_check(p->wdev, twack);
		if (w) {
			wetuwn w;
		}
		bweak;
	case PACKET3_3D_DWAW_INDX:
		twack->vap_vf_cntw = wadeon_get_ib_vawue(p, idx + 1);
		w = w100_cs_twack_check(p->wdev, twack);
		if (w) {
			wetuwn w;
		}
		bweak;
	case PACKET3_3D_DWAW_INDX_2:
		twack->vap_vf_cntw = wadeon_get_ib_vawue(p, idx);
		w = w100_cs_twack_check(p->wdev, twack);
		if (w) {
			wetuwn w;
		}
		bweak;
	case PACKET3_3D_CWEAW_HIZ:
	case PACKET3_3D_CWEAW_ZMASK:
		if (p->wdev->hypewz_fiwp != p->fiwp)
			wetuwn -EINVAW;
		bweak;
	case PACKET3_3D_CWEAW_CMASK:
		if (p->wdev->cmask_fiwp != p->fiwp)
			wetuwn -EINVAW;
		bweak;
	case PACKET3_NOP:
		bweak;
	defauwt:
		DWM_EWWOW("Packet3 opcode %x not suppowted\n", pkt->opcode);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int w300_cs_pawse(stwuct wadeon_cs_pawsew *p)
{
	stwuct wadeon_cs_packet pkt;
	stwuct w100_cs_twack *twack;
	int w;

	twack = kzawwoc(sizeof(*twack), GFP_KEWNEW);
	if (twack == NUWW)
		wetuwn -ENOMEM;
	w100_cs_twack_cweaw(p->wdev, twack);
	p->twack = twack;
	do {
		w = wadeon_cs_packet_pawse(p, &pkt, p->idx);
		if (w) {
			wetuwn w;
		}
		p->idx += pkt.count + 2;
		switch (pkt.type) {
		case WADEON_PACKET_TYPE0:
			w = w100_cs_pawse_packet0(p, &pkt,
						  p->wdev->config.w300.weg_safe_bm,
						  p->wdev->config.w300.weg_safe_bm_size,
						  &w300_packet0_check);
			bweak;
		case WADEON_PACKET_TYPE2:
			bweak;
		case WADEON_PACKET_TYPE3:
			w = w300_packet3_check(p, &pkt);
			bweak;
		defauwt:
			DWM_EWWOW("Unknown packet type %d !\n", pkt.type);
			wetuwn -EINVAW;
		}
		if (w) {
			wetuwn w;
		}
	} whiwe (p->idx < p->chunk_ib->wength_dw);
	wetuwn 0;
}

void w300_set_weg_safe(stwuct wadeon_device *wdev)
{
	wdev->config.w300.weg_safe_bm = w300_weg_safe_bm;
	wdev->config.w300.weg_safe_bm_size = AWWAY_SIZE(w300_weg_safe_bm);
}

void w300_mc_pwogwam(stwuct wadeon_device *wdev)
{
	stwuct w100_mc_save save;

	w100_debugfs_mc_info_init(wdev);

	/* Stops aww mc cwients */
	w100_mc_stop(wdev, &save);
	if (wdev->fwags & WADEON_IS_AGP) {
		WWEG32(W_00014C_MC_AGP_WOCATION,
			S_00014C_MC_AGP_STAWT(wdev->mc.gtt_stawt >> 16) |
			S_00014C_MC_AGP_TOP(wdev->mc.gtt_end >> 16));
		WWEG32(W_000170_AGP_BASE, wowew_32_bits(wdev->mc.agp_base));
		WWEG32(W_00015C_AGP_BASE_2,
			uppew_32_bits(wdev->mc.agp_base) & 0xff);
	} ewse {
		WWEG32(W_00014C_MC_AGP_WOCATION, 0x0FFFFFFF);
		WWEG32(W_000170_AGP_BASE, 0);
		WWEG32(W_00015C_AGP_BASE_2, 0);
	}
	/* Wait fow mc idwe */
	if (w300_mc_wait_fow_idwe(wdev))
		DWM_INFO("Faiwed to wait MC idwe befowe pwogwamming MC.\n");
	/* Pwogwam MC, shouwd be a 32bits wimited addwess space */
	WWEG32(W_000148_MC_FB_WOCATION,
		S_000148_MC_FB_STAWT(wdev->mc.vwam_stawt >> 16) |
		S_000148_MC_FB_TOP(wdev->mc.vwam_end >> 16));
	w100_mc_wesume(wdev, &save);
}

void w300_cwock_stawtup(stwuct wadeon_device *wdev)
{
	u32 tmp;

	if (wadeon_dyncwks != -1 && wadeon_dyncwks)
		wadeon_wegacy_set_cwock_gating(wdev, 1);
	/* We need to fowce on some of the bwock */
	tmp = WWEG32_PWW(W_00000D_SCWK_CNTW);
	tmp |= S_00000D_FOWCE_CP(1) | S_00000D_FOWCE_VIP(1);
	if ((wdev->famiwy == CHIP_WV350) || (wdev->famiwy == CHIP_WV380))
		tmp |= S_00000D_FOWCE_VAP(1);
	WWEG32_PWW(W_00000D_SCWK_CNTW, tmp);
}

static int w300_stawtup(stwuct wadeon_device *wdev)
{
	int w;

	/* set common wegs */
	w100_set_common_wegs(wdev);
	/* pwogwam mc */
	w300_mc_pwogwam(wdev);
	/* Wesume cwock */
	w300_cwock_stawtup(wdev);
	/* Initiawize GPU configuwation (# pipes, ...) */
	w300_gpu_init(wdev);
	/* Initiawize GAWT (initiawize aftew TTM so we can awwocate
	 * memowy thwough TTM but finawize aftew TTM) */
	if (wdev->fwags & WADEON_IS_PCIE) {
		w = wv370_pcie_gawt_enabwe(wdev);
		if (w)
			wetuwn w;
	}

	if (wdev->famiwy == CHIP_W300 ||
	    wdev->famiwy == CHIP_W350 ||
	    wdev->famiwy == CHIP_WV350)
		w100_enabwe_bm(wdev);

	if (wdev->fwags & WADEON_IS_PCI) {
		w = w100_pci_gawt_enabwe(wdev);
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

	w100_iwq_set(wdev);
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

int w300_wesume(stwuct wadeon_device *wdev)
{
	int w;

	/* Make suw GAWT awe not wowking */
	if (wdev->fwags & WADEON_IS_PCIE)
		wv370_pcie_gawt_disabwe(wdev);
	if (wdev->fwags & WADEON_IS_PCI)
		w100_pci_gawt_disabwe(wdev);
	/* Wesume cwock befowe doing weset */
	w300_cwock_stawtup(wdev);
	/* Weset gpu befowe posting othewwise ATOM wiww entew infinite woop */
	if (wadeon_asic_weset(wdev)) {
		dev_wawn(wdev->dev, "GPU weset faiwed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			WWEG32(W_000E40_WBBM_STATUS),
			WWEG32(W_0007C0_CP_STAT));
	}
	/* post */
	wadeon_combios_asic_init(wdev->ddev);
	/* Wesume cwock aftew posting */
	w300_cwock_stawtup(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);

	wdev->accew_wowking = twue;
	w = w300_stawtup(wdev);
	if (w) {
		wdev->accew_wowking = fawse;
	}
	wetuwn w;
}

int w300_suspend(stwuct wadeon_device *wdev)
{
	wadeon_pm_suspend(wdev);
	w100_cp_disabwe(wdev);
	wadeon_wb_disabwe(wdev);
	w100_iwq_disabwe(wdev);
	if (wdev->fwags & WADEON_IS_PCIE)
		wv370_pcie_gawt_disabwe(wdev);
	if (wdev->fwags & WADEON_IS_PCI)
		w100_pci_gawt_disabwe(wdev);
	wetuwn 0;
}

void w300_fini(stwuct wadeon_device *wdev)
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
	wadeon_atombios_fini(wdev);
	kfwee(wdev->bios);
	wdev->bios = NUWW;
}

int w300_init(stwuct wadeon_device *wdev)
{
	int w;

	/* Disabwe VGA */
	w100_vga_wendew_disabwe(wdev);
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
		dev_eww(wdev->dev, "Expecting combios fow WS400/WS480 GPU\n");
		wetuwn -EINVAW;
	} ewse {
		w = wadeon_combios_init(wdev);
		if (w)
			wetuwn w;
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
	/* Set asic ewwata */
	w300_ewwata(wdev);
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
	/* Fence dwivew */
	wadeon_fence_dwivew_init(wdev);
	/* Memowy managew */
	w = wadeon_bo_init(wdev);
	if (w)
		wetuwn w;
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
	w300_set_weg_safe(wdev);

	/* Initiawize powew management */
	wadeon_pm_init(wdev);

	wdev->accew_wowking = twue;
	w = w300_stawtup(wdev);
	if (w) {
		/* Something went wwong with the accew init, so stop accew */
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
