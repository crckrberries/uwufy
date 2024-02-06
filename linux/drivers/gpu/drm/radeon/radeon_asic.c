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

#incwude <winux/consowe.h>
#incwude <winux/pci.h>
#incwude <winux/vgaawb.h>

#incwude <dwm/wadeon_dwm.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_weg.h"

/*
 * Wegistews accessows functions.
 */
/**
 * wadeon_invawid_wweg - dummy weg wead function
 *
 * @wdev: wadeon device pointew
 * @weg: offset of wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 * Wetuwns the vawue in the wegistew.
 */
static uint32_t wadeon_invawid_wweg(stwuct wadeon_device *wdev, uint32_t weg)
{
	DWM_EWWOW("Invawid cawwback to wead wegistew 0x%04X\n", weg);
	BUG_ON(1);
	wetuwn 0;
}

/**
 * wadeon_invawid_wweg - dummy weg wwite function
 *
 * @wdev: wadeon device pointew
 * @weg: offset of wegistew
 * @v: vawue to wwite to the wegistew
 *
 * Dummy wegistew wead function.  Used fow wegistew bwocks
 * that cewtain asics don't have (aww asics).
 */
static void wadeon_invawid_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v)
{
	DWM_EWWOW("Invawid cawwback to wwite wegistew 0x%04X with 0x%08X\n",
		  weg, v);
	BUG_ON(1);
}

/**
 * wadeon_wegistew_accessow_init - sets up the wegistew accessow cawwbacks
 *
 * @wdev: wadeon device pointew
 *
 * Sets up the wegistew accessow cawwbacks fow vawious wegistew
 * apewtuwes.  Not aww asics have aww apewtuwes (aww asics).
 */
static void wadeon_wegistew_accessow_init(stwuct wadeon_device *wdev)
{
	wdev->mc_wweg = &wadeon_invawid_wweg;
	wdev->mc_wweg = &wadeon_invawid_wweg;
	wdev->pww_wweg = &wadeon_invawid_wweg;
	wdev->pww_wweg = &wadeon_invawid_wweg;
	wdev->pciep_wweg = &wadeon_invawid_wweg;
	wdev->pciep_wweg = &wadeon_invawid_wweg;

	/* Don't change owdew as we awe ovewwidding accessow. */
	if (wdev->famiwy < CHIP_WV515) {
		wdev->pcie_weg_mask = 0xff;
	} ewse {
		wdev->pcie_weg_mask = 0x7ff;
	}
	/* FIXME: not suwe hewe */
	if (wdev->famiwy <= CHIP_W580) {
		wdev->pww_wweg = &w100_pww_wweg;
		wdev->pww_wweg = &w100_pww_wweg;
	}
	if (wdev->famiwy >= CHIP_W420) {
		wdev->mc_wweg = &w420_mc_wweg;
		wdev->mc_wweg = &w420_mc_wweg;
	}
	if (wdev->famiwy >= CHIP_WV515) {
		wdev->mc_wweg = &wv515_mc_wweg;
		wdev->mc_wweg = &wv515_mc_wweg;
	}
	if (wdev->famiwy == CHIP_WS400 || wdev->famiwy == CHIP_WS480) {
		wdev->mc_wweg = &ws400_mc_wweg;
		wdev->mc_wweg = &ws400_mc_wweg;
	}
	if (wdev->famiwy == CHIP_WS690 || wdev->famiwy == CHIP_WS740) {
		wdev->mc_wweg = &ws690_mc_wweg;
		wdev->mc_wweg = &ws690_mc_wweg;
	}
	if (wdev->famiwy == CHIP_WS600) {
		wdev->mc_wweg = &ws600_mc_wweg;
		wdev->mc_wweg = &ws600_mc_wweg;
	}
	if (wdev->famiwy == CHIP_WS780 || wdev->famiwy == CHIP_WS880) {
		wdev->mc_wweg = &ws780_mc_wweg;
		wdev->mc_wweg = &ws780_mc_wweg;
	}

	if (wdev->famiwy >= CHIP_BONAIWE) {
		wdev->pciep_wweg = &cik_pciep_wweg;
		wdev->pciep_wweg = &cik_pciep_wweg;
	} ewse if (wdev->famiwy >= CHIP_W600) {
		wdev->pciep_wweg = &w600_pciep_wweg;
		wdev->pciep_wweg = &w600_pciep_wweg;
	}
}

static int wadeon_invawid_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
						    u32 weg, u32 *vaw)
{
	wetuwn -EINVAW;
}

/* hewpew to disabwe agp */
/**
 * wadeon_agp_disabwe - AGP disabwe hewpew function
 *
 * @wdev: wadeon device pointew
 *
 * Wemoves AGP fwags and changes the gawt cawwbacks on AGP
 * cawds when using the intewnaw gawt wathew than AGP (aww asics).
 */
void wadeon_agp_disabwe(stwuct wadeon_device *wdev)
{
	wdev->fwags &= ~WADEON_IS_AGP;
	if (wdev->famiwy >= CHIP_W600) {
		DWM_INFO("Fowcing AGP to PCIE mode\n");
		wdev->fwags |= WADEON_IS_PCIE;
	} ewse if (wdev->famiwy >= CHIP_WV515 ||
			wdev->famiwy == CHIP_WV380 ||
			wdev->famiwy == CHIP_WV410 ||
			wdev->famiwy == CHIP_W423) {
		DWM_INFO("Fowcing AGP to PCIE mode\n");
		wdev->fwags |= WADEON_IS_PCIE;
		wdev->asic->gawt.twb_fwush = &wv370_pcie_gawt_twb_fwush;
		wdev->asic->gawt.get_page_entwy = &wv370_pcie_gawt_get_page_entwy;
		wdev->asic->gawt.set_page = &wv370_pcie_gawt_set_page;
	} ewse {
		DWM_INFO("Fowcing AGP to PCI mode\n");
		wdev->fwags |= WADEON_IS_PCI;
		wdev->asic->gawt.twb_fwush = &w100_pci_gawt_twb_fwush;
		wdev->asic->gawt.get_page_entwy = &w100_pci_gawt_get_page_entwy;
		wdev->asic->gawt.set_page = &w100_pci_gawt_set_page;
	}
	wdev->mc.gtt_size = wadeon_gawt_size * 1024 * 1024;
}

/*
 * ASIC
 */

static const stwuct wadeon_asic_wing w100_gfx_wing = {
	.ib_execute = &w100_wing_ib_execute,
	.emit_fence = &w100_fence_wing_emit,
	.emit_semaphowe = &w100_semaphowe_wing_emit,
	.cs_pawse = &w100_cs_pawse,
	.wing_stawt = &w100_wing_stawt,
	.wing_test = &w100_wing_test,
	.ib_test = &w100_ib_test,
	.is_wockup = &w100_gpu_is_wockup,
	.get_wptw = &w100_gfx_get_wptw,
	.get_wptw = &w100_gfx_get_wptw,
	.set_wptw = &w100_gfx_set_wptw,
};

static stwuct wadeon_asic w100_asic = {
	.init = &w100_init,
	.fini = &w100_fini,
	.suspend = &w100_suspend,
	.wesume = &w100_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &w100_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &w100_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &w100_pci_gawt_twb_fwush,
		.get_page_entwy = &w100_pci_gawt_get_page_entwy,
		.set_page = &w100_pci_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w100_gfx_wing
	},
	.iwq = {
		.set = &w100_iwq_set,
		.pwocess = &w100_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &w100_bandwidth_update,
		.get_vbwank_countew = &w100_get_vbwank_countew,
		.wait_fow_vbwank = &w100_wait_fow_vbwank,
		.set_backwight_wevew = &wadeon_wegacy_set_backwight_wevew,
		.get_backwight_wevew = &wadeon_wegacy_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = NUWW,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w100_hpd_init,
		.fini = &w100_hpd_fini,
		.sense = &w100_hpd_sense,
		.set_powawity = &w100_hpd_set_powawity,
	},
	.pm = {
		.misc = &w100_pm_misc,
		.pwepawe = &w100_pm_pwepawe,
		.finish = &w100_pm_finish,
		.init_pwofiwe = &w100_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_wegacy_get_engine_cwock,
		.set_engine_cwock = &wadeon_wegacy_set_engine_cwock,
		.get_memowy_cwock = &wadeon_wegacy_get_memowy_cwock,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = &wadeon_wegacy_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &w100_page_fwip,
		.page_fwip_pending = &w100_page_fwip_pending,
	},
};

static stwuct wadeon_asic w200_asic = {
	.init = &w100_init,
	.fini = &w100_fini,
	.suspend = &w100_suspend,
	.wesume = &w100_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &w100_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &w100_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &w100_pci_gawt_twb_fwush,
		.get_page_entwy = &w100_pci_gawt_get_page_entwy,
		.set_page = &w100_pci_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w100_gfx_wing
	},
	.iwq = {
		.set = &w100_iwq_set,
		.pwocess = &w100_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &w100_bandwidth_update,
		.get_vbwank_countew = &w100_get_vbwank_countew,
		.wait_fow_vbwank = &w100_wait_fow_vbwank,
		.set_backwight_wevew = &wadeon_wegacy_set_backwight_wevew,
		.get_backwight_wevew = &wadeon_wegacy_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w100_hpd_init,
		.fini = &w100_hpd_fini,
		.sense = &w100_hpd_sense,
		.set_powawity = &w100_hpd_set_powawity,
	},
	.pm = {
		.misc = &w100_pm_misc,
		.pwepawe = &w100_pm_pwepawe,
		.finish = &w100_pm_finish,
		.init_pwofiwe = &w100_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_wegacy_get_engine_cwock,
		.set_engine_cwock = &wadeon_wegacy_set_engine_cwock,
		.get_memowy_cwock = &wadeon_wegacy_get_memowy_cwock,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = &wadeon_wegacy_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &w100_page_fwip,
		.page_fwip_pending = &w100_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing w300_gfx_wing = {
	.ib_execute = &w100_wing_ib_execute,
	.emit_fence = &w300_fence_wing_emit,
	.emit_semaphowe = &w100_semaphowe_wing_emit,
	.cs_pawse = &w300_cs_pawse,
	.wing_stawt = &w300_wing_stawt,
	.wing_test = &w100_wing_test,
	.ib_test = &w100_ib_test,
	.is_wockup = &w100_gpu_is_wockup,
	.get_wptw = &w100_gfx_get_wptw,
	.get_wptw = &w100_gfx_get_wptw,
	.set_wptw = &w100_gfx_set_wptw,
};

static const stwuct wadeon_asic_wing wv515_gfx_wing = {
	.ib_execute = &w100_wing_ib_execute,
	.emit_fence = &w300_fence_wing_emit,
	.emit_semaphowe = &w100_semaphowe_wing_emit,
	.cs_pawse = &w300_cs_pawse,
	.wing_stawt = &wv515_wing_stawt,
	.wing_test = &w100_wing_test,
	.ib_test = &w100_ib_test,
	.is_wockup = &w100_gpu_is_wockup,
	.get_wptw = &w100_gfx_get_wptw,
	.get_wptw = &w100_gfx_get_wptw,
	.set_wptw = &w100_gfx_set_wptw,
};

static stwuct wadeon_asic w300_asic = {
	.init = &w300_init,
	.fini = &w300_fini,
	.suspend = &w300_suspend,
	.wesume = &w300_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &w300_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &w300_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &w100_pci_gawt_twb_fwush,
		.get_page_entwy = &w100_pci_gawt_get_page_entwy,
		.set_page = &w100_pci_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w300_gfx_wing
	},
	.iwq = {
		.set = &w100_iwq_set,
		.pwocess = &w100_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &w100_bandwidth_update,
		.get_vbwank_countew = &w100_get_vbwank_countew,
		.wait_fow_vbwank = &w100_wait_fow_vbwank,
		.set_backwight_wevew = &wadeon_wegacy_set_backwight_wevew,
		.get_backwight_wevew = &wadeon_wegacy_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w100_hpd_init,
		.fini = &w100_hpd_fini,
		.sense = &w100_hpd_sense,
		.set_powawity = &w100_hpd_set_powawity,
	},
	.pm = {
		.misc = &w100_pm_misc,
		.pwepawe = &w100_pm_pwepawe,
		.finish = &w100_pm_finish,
		.init_pwofiwe = &w100_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_wegacy_get_engine_cwock,
		.set_engine_cwock = &wadeon_wegacy_set_engine_cwock,
		.get_memowy_cwock = &wadeon_wegacy_get_memowy_cwock,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = &wv370_get_pcie_wanes,
		.set_pcie_wanes = &wv370_set_pcie_wanes,
		.set_cwock_gating = &wadeon_wegacy_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &w100_page_fwip,
		.page_fwip_pending = &w100_page_fwip_pending,
	},
};

static stwuct wadeon_asic w300_asic_pcie = {
	.init = &w300_init,
	.fini = &w300_fini,
	.suspend = &w300_suspend,
	.wesume = &w300_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &w300_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &w300_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &wv370_pcie_gawt_twb_fwush,
		.get_page_entwy = &wv370_pcie_gawt_get_page_entwy,
		.set_page = &wv370_pcie_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w300_gfx_wing
	},
	.iwq = {
		.set = &w100_iwq_set,
		.pwocess = &w100_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &w100_bandwidth_update,
		.get_vbwank_countew = &w100_get_vbwank_countew,
		.wait_fow_vbwank = &w100_wait_fow_vbwank,
		.set_backwight_wevew = &wadeon_wegacy_set_backwight_wevew,
		.get_backwight_wevew = &wadeon_wegacy_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w100_hpd_init,
		.fini = &w100_hpd_fini,
		.sense = &w100_hpd_sense,
		.set_powawity = &w100_hpd_set_powawity,
	},
	.pm = {
		.misc = &w100_pm_misc,
		.pwepawe = &w100_pm_pwepawe,
		.finish = &w100_pm_finish,
		.init_pwofiwe = &w100_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_wegacy_get_engine_cwock,
		.set_engine_cwock = &wadeon_wegacy_set_engine_cwock,
		.get_memowy_cwock = &wadeon_wegacy_get_memowy_cwock,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = &wv370_get_pcie_wanes,
		.set_pcie_wanes = &wv370_set_pcie_wanes,
		.set_cwock_gating = &wadeon_wegacy_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &w100_page_fwip,
		.page_fwip_pending = &w100_page_fwip_pending,
	},
};

static stwuct wadeon_asic w420_asic = {
	.init = &w420_init,
	.fini = &w420_fini,
	.suspend = &w420_suspend,
	.wesume = &w420_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &w300_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &w300_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &wv370_pcie_gawt_twb_fwush,
		.get_page_entwy = &wv370_pcie_gawt_get_page_entwy,
		.set_page = &wv370_pcie_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w300_gfx_wing
	},
	.iwq = {
		.set = &w100_iwq_set,
		.pwocess = &w100_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &w100_bandwidth_update,
		.get_vbwank_countew = &w100_get_vbwank_countew,
		.wait_fow_vbwank = &w100_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w100_hpd_init,
		.fini = &w100_hpd_fini,
		.sense = &w100_hpd_sense,
		.set_powawity = &w100_hpd_set_powawity,
	},
	.pm = {
		.misc = &w100_pm_misc,
		.pwepawe = &w100_pm_pwepawe,
		.finish = &w100_pm_finish,
		.init_pwofiwe = &w420_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &wv370_get_pcie_wanes,
		.set_pcie_wanes = &wv370_set_pcie_wanes,
		.set_cwock_gating = &wadeon_atom_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &w100_page_fwip,
		.page_fwip_pending = &w100_page_fwip_pending,
	},
};

static stwuct wadeon_asic ws400_asic = {
	.init = &ws400_init,
	.fini = &ws400_fini,
	.suspend = &ws400_suspend,
	.wesume = &ws400_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &w300_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &ws400_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &ws400_gawt_twb_fwush,
		.get_page_entwy = &ws400_gawt_get_page_entwy,
		.set_page = &ws400_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w300_gfx_wing
	},
	.iwq = {
		.set = &w100_iwq_set,
		.pwocess = &w100_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &w100_bandwidth_update,
		.get_vbwank_countew = &w100_get_vbwank_countew,
		.wait_fow_vbwank = &w100_wait_fow_vbwank,
		.set_backwight_wevew = &wadeon_wegacy_set_backwight_wevew,
		.get_backwight_wevew = &wadeon_wegacy_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w100_hpd_init,
		.fini = &w100_hpd_fini,
		.sense = &w100_hpd_sense,
		.set_powawity = &w100_hpd_set_powawity,
	},
	.pm = {
		.misc = &w100_pm_misc,
		.pwepawe = &w100_pm_pwepawe,
		.finish = &w100_pm_finish,
		.init_pwofiwe = &w100_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_wegacy_get_engine_cwock,
		.set_engine_cwock = &wadeon_wegacy_set_engine_cwock,
		.get_memowy_cwock = &wadeon_wegacy_get_memowy_cwock,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = &wadeon_wegacy_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &w100_page_fwip,
		.page_fwip_pending = &w100_page_fwip_pending,
	},
};

static stwuct wadeon_asic ws600_asic = {
	.init = &ws600_init,
	.fini = &ws600_fini,
	.suspend = &ws600_suspend,
	.wesume = &ws600_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &ws600_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &ws600_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &ws600_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w300_gfx_wing
	},
	.iwq = {
		.set = &ws600_iwq_set,
		.pwocess = &ws600_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &ws600_bandwidth_update,
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &ws600_hpd_init,
		.fini = &ws600_hpd_fini,
		.sense = &ws600_hpd_sense,
		.set_powawity = &ws600_hpd_set_powawity,
	},
	.pm = {
		.misc = &ws600_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &w420_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = &wadeon_atom_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &ws600_page_fwip,
		.page_fwip_pending = &ws600_page_fwip_pending,
	},
};

static stwuct wadeon_asic ws690_asic = {
	.init = &ws690_init,
	.fini = &ws690_fini,
	.suspend = &ws690_suspend,
	.wesume = &ws690_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &ws600_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &ws690_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &ws400_gawt_twb_fwush,
		.get_page_entwy = &ws400_gawt_get_page_entwy,
		.set_page = &ws400_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w300_gfx_wing
	},
	.iwq = {
		.set = &ws600_iwq_set,
		.pwocess = &ws600_iwq_pwocess,
	},
	.dispway = {
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.bandwidth_update = &ws690_bandwidth_update,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w200_copy_dma,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &ws600_hpd_init,
		.fini = &ws600_hpd_fini,
		.sense = &ws600_hpd_sense,
		.set_powawity = &ws600_hpd_set_powawity,
	},
	.pm = {
		.misc = &ws600_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &w420_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = &wadeon_atom_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &ws600_page_fwip,
		.page_fwip_pending = &ws600_page_fwip_pending,
	},
};

static stwuct wadeon_asic wv515_asic = {
	.init = &wv515_init,
	.fini = &wv515_fini,
	.suspend = &wv515_suspend,
	.wesume = &wv515_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &ws600_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &wv515_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &wv370_pcie_gawt_twb_fwush,
		.get_page_entwy = &wv370_pcie_gawt_get_page_entwy,
		.set_page = &wv370_pcie_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &wv515_gfx_wing
	},
	.iwq = {
		.set = &ws600_iwq_set,
		.pwocess = &ws600_iwq_pwocess,
	},
	.dispway = {
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.bandwidth_update = &wv515_bandwidth_update,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &ws600_hpd_init,
		.fini = &ws600_hpd_fini,
		.sense = &ws600_hpd_sense,
		.set_powawity = &ws600_hpd_set_powawity,
	},
	.pm = {
		.misc = &ws600_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &w420_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &wv370_get_pcie_wanes,
		.set_pcie_wanes = &wv370_set_pcie_wanes,
		.set_cwock_gating = &wadeon_atom_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &ws600_page_fwip,
		.page_fwip_pending = &ws600_page_fwip_pending,
	},
};

static stwuct wadeon_asic w520_asic = {
	.init = &w520_init,
	.fini = &wv515_fini,
	.suspend = &wv515_suspend,
	.wesume = &w520_wesume,
	.vga_set_state = &w100_vga_set_state,
	.asic_weset = &ws600_asic_weset,
	.mmio_hdp_fwush = NUWW,
	.gui_idwe = &w100_gui_idwe,
	.mc_wait_fow_idwe = &w520_mc_wait_fow_idwe,
	.get_awwowed_info_wegistew = wadeon_invawid_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &wv370_pcie_gawt_twb_fwush,
		.get_page_entwy = &wv370_pcie_gawt_get_page_entwy,
		.set_page = &wv370_pcie_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &wv515_gfx_wing
	},
	.iwq = {
		.set = &ws600_iwq_set,
		.pwocess = &ws600_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &wv515_bandwidth_update,
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w100_copy_bwit,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w200_copy_dma,
		.dma_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.copy = &w100_copy_bwit,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w100_set_suwface_weg,
		.cweaw_weg = w100_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &ws600_hpd_init,
		.fini = &ws600_hpd_fini,
		.sense = &ws600_hpd_sense,
		.set_powawity = &ws600_hpd_set_powawity,
	},
	.pm = {
		.misc = &ws600_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &w420_pm_init_pwofiwe,
		.get_dynpm_state = &w100_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &wv370_get_pcie_wanes,
		.set_pcie_wanes = &wv370_set_pcie_wanes,
		.set_cwock_gating = &wadeon_atom_set_cwock_gating,
	},
	.pfwip = {
		.page_fwip = &ws600_page_fwip,
		.page_fwip_pending = &ws600_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing w600_gfx_wing = {
	.ib_execute = &w600_wing_ib_execute,
	.emit_fence = &w600_fence_wing_emit,
	.emit_semaphowe = &w600_semaphowe_wing_emit,
	.cs_pawse = &w600_cs_pawse,
	.wing_test = &w600_wing_test,
	.ib_test = &w600_ib_test,
	.is_wockup = &w600_gfx_is_wockup,
	.get_wptw = &w600_gfx_get_wptw,
	.get_wptw = &w600_gfx_get_wptw,
	.set_wptw = &w600_gfx_set_wptw,
};

static const stwuct wadeon_asic_wing w600_dma_wing = {
	.ib_execute = &w600_dma_wing_ib_execute,
	.emit_fence = &w600_dma_fence_wing_emit,
	.emit_semaphowe = &w600_dma_semaphowe_wing_emit,
	.cs_pawse = &w600_dma_cs_pawse,
	.wing_test = &w600_dma_wing_test,
	.ib_test = &w600_dma_ib_test,
	.is_wockup = &w600_dma_is_wockup,
	.get_wptw = &w600_dma_get_wptw,
	.get_wptw = &w600_dma_get_wptw,
	.set_wptw = &w600_dma_set_wptw,
};

static stwuct wadeon_asic w600_asic = {
	.init = &w600_init,
	.fini = &w600_fini,
	.suspend = &w600_suspend,
	.wesume = &w600_wesume,
	.vga_set_state = &w600_vga_set_state,
	.asic_weset = &w600_asic_weset,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &w600_mc_wait_fow_idwe,
	.get_xcwk = &w600_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = w600_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &w600_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w600_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &w600_dma_wing,
	},
	.iwq = {
		.set = &w600_iwq_set,
		.pwocess = &w600_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &wv515_bandwidth_update,
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w600_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &w600_copy_cpdma,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w600_hpd_init,
		.fini = &w600_hpd_fini,
		.sense = &w600_hpd_sense,
		.set_powawity = &w600_hpd_set_powawity,
	},
	.pm = {
		.misc = &w600_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &w600_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &w600_get_pcie_wanes,
		.set_pcie_wanes = &w600_set_pcie_wanes,
		.set_cwock_gating = NUWW,
		.get_tempewatuwe = &wv6xx_get_temp,
	},
	.pfwip = {
		.page_fwip = &ws600_page_fwip,
		.page_fwip_pending = &ws600_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing wv6xx_uvd_wing = {
	.ib_execute = &uvd_v1_0_ib_execute,
	.emit_fence = &uvd_v1_0_fence_emit,
	.emit_semaphowe = &uvd_v1_0_semaphowe_emit,
	.cs_pawse = &wadeon_uvd_cs_pawse,
	.wing_test = &uvd_v1_0_wing_test,
	.ib_test = &uvd_v1_0_ib_test,
	.is_wockup = &wadeon_wing_test_wockup,
	.get_wptw = &uvd_v1_0_get_wptw,
	.get_wptw = &uvd_v1_0_get_wptw,
	.set_wptw = &uvd_v1_0_set_wptw,
};

static stwuct wadeon_asic wv6xx_asic = {
	.init = &w600_init,
	.fini = &w600_fini,
	.suspend = &w600_suspend,
	.wesume = &w600_wesume,
	.vga_set_state = &w600_vga_set_state,
	.asic_weset = &w600_asic_weset,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &w600_mc_wait_fow_idwe,
	.get_xcwk = &w600_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = w600_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &w600_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w600_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &w600_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &wv6xx_uvd_wing,
	},
	.iwq = {
		.set = &w600_iwq_set,
		.pwocess = &w600_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &wv515_bandwidth_update,
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w600_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &w600_copy_cpdma,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w600_hpd_init,
		.fini = &w600_hpd_fini,
		.sense = &w600_hpd_sense,
		.set_powawity = &w600_hpd_set_powawity,
	},
	.pm = {
		.misc = &w600_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &w600_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &w600_get_pcie_wanes,
		.set_pcie_wanes = &w600_set_pcie_wanes,
		.set_cwock_gating = NUWW,
		.get_tempewatuwe = &wv6xx_get_temp,
		.set_uvd_cwocks = &w600_set_uvd_cwocks,
	},
	.dpm = {
		.init = &wv6xx_dpm_init,
		.setup_asic = &wv6xx_setup_asic,
		.enabwe = &wv6xx_dpm_enabwe,
		.wate_enabwe = &w600_dpm_wate_enabwe,
		.disabwe = &wv6xx_dpm_disabwe,
		.pwe_set_powew_state = &w600_dpm_pwe_set_powew_state,
		.set_powew_state = &wv6xx_dpm_set_powew_state,
		.post_set_powew_state = &w600_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &wv6xx_dpm_dispway_configuwation_changed,
		.fini = &wv6xx_dpm_fini,
		.get_scwk = &wv6xx_dpm_get_scwk,
		.get_mcwk = &wv6xx_dpm_get_mcwk,
		.pwint_powew_state = &wv6xx_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &wv6xx_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &wv6xx_dpm_fowce_pewfowmance_wevew,
		.get_cuwwent_scwk = &wv6xx_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &wv6xx_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &ws600_page_fwip,
		.page_fwip_pending = &ws600_page_fwip_pending,
	},
};

static stwuct wadeon_asic ws780_asic = {
	.init = &w600_init,
	.fini = &w600_fini,
	.suspend = &w600_suspend,
	.wesume = &w600_wesume,
	.vga_set_state = &w600_vga_set_state,
	.asic_weset = &w600_asic_weset,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &w600_mc_wait_fow_idwe,
	.get_xcwk = &w600_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = w600_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &w600_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w600_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &w600_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &wv6xx_uvd_wing,
	},
	.iwq = {
		.set = &w600_iwq_set,
		.pwocess = &w600_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &ws690_bandwidth_update,
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &w600_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &w600_copy_cpdma,
		.copy_wing_index = WADEON_WING_TYPE_GFX_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w600_hpd_init,
		.fini = &w600_hpd_fini,
		.sense = &w600_hpd_sense,
		.set_powawity = &w600_hpd_set_powawity,
	},
	.pm = {
		.misc = &w600_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &ws780_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = NUWW,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = NUWW,
		.get_tempewatuwe = &wv6xx_get_temp,
		.set_uvd_cwocks = &w600_set_uvd_cwocks,
	},
	.dpm = {
		.init = &ws780_dpm_init,
		.setup_asic = &ws780_dpm_setup_asic,
		.enabwe = &ws780_dpm_enabwe,
		.wate_enabwe = &w600_dpm_wate_enabwe,
		.disabwe = &ws780_dpm_disabwe,
		.pwe_set_powew_state = &w600_dpm_pwe_set_powew_state,
		.set_powew_state = &ws780_dpm_set_powew_state,
		.post_set_powew_state = &w600_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &ws780_dpm_dispway_configuwation_changed,
		.fini = &ws780_dpm_fini,
		.get_scwk = &ws780_dpm_get_scwk,
		.get_mcwk = &ws780_dpm_get_mcwk,
		.pwint_powew_state = &ws780_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &ws780_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &ws780_dpm_fowce_pewfowmance_wevew,
		.get_cuwwent_scwk = &ws780_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &ws780_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &ws600_page_fwip,
		.page_fwip_pending = &ws600_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing wv770_uvd_wing = {
	.ib_execute = &uvd_v1_0_ib_execute,
	.emit_fence = &uvd_v2_2_fence_emit,
	.emit_semaphowe = &uvd_v2_2_semaphowe_emit,
	.cs_pawse = &wadeon_uvd_cs_pawse,
	.wing_test = &uvd_v1_0_wing_test,
	.ib_test = &uvd_v1_0_ib_test,
	.is_wockup = &wadeon_wing_test_wockup,
	.get_wptw = &uvd_v1_0_get_wptw,
	.get_wptw = &uvd_v1_0_get_wptw,
	.set_wptw = &uvd_v1_0_set_wptw,
};

static stwuct wadeon_asic wv770_asic = {
	.init = &wv770_init,
	.fini = &wv770_fini,
	.suspend = &wv770_suspend,
	.wesume = &wv770_wesume,
	.asic_weset = &w600_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &w600_mc_wait_fow_idwe,
	.get_xcwk = &wv770_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = w600_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &w600_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &w600_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &w600_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &wv770_uvd_wing,
	},
	.iwq = {
		.set = &w600_iwq_set,
		.pwocess = &w600_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &wv515_bandwidth_update,
		.get_vbwank_countew = &ws600_get_vbwank_countew,
		.wait_fow_vbwank = &avivo_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &wv770_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &wv770_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &w600_hpd_init,
		.fini = &w600_hpd_fini,
		.sense = &w600_hpd_sense,
		.set_powawity = &w600_hpd_set_powawity,
	},
	.pm = {
		.misc = &wv770_pm_misc,
		.pwepawe = &ws600_pm_pwepawe,
		.finish = &ws600_pm_finish,
		.init_pwofiwe = &w600_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &w600_get_pcie_wanes,
		.set_pcie_wanes = &w600_set_pcie_wanes,
		.set_cwock_gating = &wadeon_atom_set_cwock_gating,
		.set_uvd_cwocks = &wv770_set_uvd_cwocks,
		.get_tempewatuwe = &wv770_get_temp,
	},
	.dpm = {
		.init = &wv770_dpm_init,
		.setup_asic = &wv770_dpm_setup_asic,
		.enabwe = &wv770_dpm_enabwe,
		.wate_enabwe = &wv770_dpm_wate_enabwe,
		.disabwe = &wv770_dpm_disabwe,
		.pwe_set_powew_state = &w600_dpm_pwe_set_powew_state,
		.set_powew_state = &wv770_dpm_set_powew_state,
		.post_set_powew_state = &w600_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &wv770_dpm_dispway_configuwation_changed,
		.fini = &wv770_dpm_fini,
		.get_scwk = &wv770_dpm_get_scwk,
		.get_mcwk = &wv770_dpm_get_mcwk,
		.pwint_powew_state = &wv770_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &wv770_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &wv770_dpm_fowce_pewfowmance_wevew,
		.vbwank_too_showt = &wv770_dpm_vbwank_too_showt,
		.get_cuwwent_scwk = &wv770_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &wv770_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &wv770_page_fwip,
		.page_fwip_pending = &wv770_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing evewgween_gfx_wing = {
	.ib_execute = &evewgween_wing_ib_execute,
	.emit_fence = &w600_fence_wing_emit,
	.emit_semaphowe = &w600_semaphowe_wing_emit,
	.cs_pawse = &evewgween_cs_pawse,
	.wing_test = &w600_wing_test,
	.ib_test = &w600_ib_test,
	.is_wockup = &evewgween_gfx_is_wockup,
	.get_wptw = &w600_gfx_get_wptw,
	.get_wptw = &w600_gfx_get_wptw,
	.set_wptw = &w600_gfx_set_wptw,
};

static const stwuct wadeon_asic_wing evewgween_dma_wing = {
	.ib_execute = &evewgween_dma_wing_ib_execute,
	.emit_fence = &evewgween_dma_fence_wing_emit,
	.emit_semaphowe = &w600_dma_semaphowe_wing_emit,
	.cs_pawse = &evewgween_dma_cs_pawse,
	.wing_test = &w600_dma_wing_test,
	.ib_test = &w600_dma_ib_test,
	.is_wockup = &evewgween_dma_is_wockup,
	.get_wptw = &w600_dma_get_wptw,
	.get_wptw = &w600_dma_get_wptw,
	.set_wptw = &w600_dma_set_wptw,
};

static stwuct wadeon_asic evewgween_asic = {
	.init = &evewgween_init,
	.fini = &evewgween_fini,
	.suspend = &evewgween_suspend,
	.wesume = &evewgween_wesume,
	.asic_weset = &evewgween_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &wv770_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = evewgween_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &evewgween_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &evewgween_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &evewgween_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &wv770_uvd_wing,
	},
	.iwq = {
		.set = &evewgween_iwq_set,
		.pwocess = &evewgween_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &evewgween_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &evewgween_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &evewgween_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &w600_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &w600_get_pcie_wanes,
		.set_pcie_wanes = &w600_set_pcie_wanes,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &evewgween_set_uvd_cwocks,
		.get_tempewatuwe = &evewgween_get_temp,
	},
	.dpm = {
		.init = &cypwess_dpm_init,
		.setup_asic = &cypwess_dpm_setup_asic,
		.enabwe = &cypwess_dpm_enabwe,
		.wate_enabwe = &wv770_dpm_wate_enabwe,
		.disabwe = &cypwess_dpm_disabwe,
		.pwe_set_powew_state = &w600_dpm_pwe_set_powew_state,
		.set_powew_state = &cypwess_dpm_set_powew_state,
		.post_set_powew_state = &w600_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &cypwess_dpm_dispway_configuwation_changed,
		.fini = &cypwess_dpm_fini,
		.get_scwk = &wv770_dpm_get_scwk,
		.get_mcwk = &wv770_dpm_get_mcwk,
		.pwint_powew_state = &wv770_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &wv770_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &wv770_dpm_fowce_pewfowmance_wevew,
		.vbwank_too_showt = &cypwess_dpm_vbwank_too_showt,
		.get_cuwwent_scwk = &wv770_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &wv770_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

static stwuct wadeon_asic sumo_asic = {
	.init = &evewgween_init,
	.fini = &evewgween_fini,
	.suspend = &evewgween_suspend,
	.wesume = &evewgween_wesume,
	.asic_weset = &evewgween_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &w600_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = evewgween_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &evewgween_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &evewgween_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &evewgween_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &wv770_uvd_wing,
	},
	.iwq = {
		.set = &evewgween_iwq_set,
		.pwocess = &evewgween_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &evewgween_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &evewgween_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &evewgween_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &sumo_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = NUWW,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &sumo_set_uvd_cwocks,
		.get_tempewatuwe = &sumo_get_temp,
	},
	.dpm = {
		.init = &sumo_dpm_init,
		.setup_asic = &sumo_dpm_setup_asic,
		.enabwe = &sumo_dpm_enabwe,
		.wate_enabwe = &sumo_dpm_wate_enabwe,
		.disabwe = &sumo_dpm_disabwe,
		.pwe_set_powew_state = &sumo_dpm_pwe_set_powew_state,
		.set_powew_state = &sumo_dpm_set_powew_state,
		.post_set_powew_state = &sumo_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &sumo_dpm_dispway_configuwation_changed,
		.fini = &sumo_dpm_fini,
		.get_scwk = &sumo_dpm_get_scwk,
		.get_mcwk = &sumo_dpm_get_mcwk,
		.pwint_powew_state = &sumo_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &sumo_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &sumo_dpm_fowce_pewfowmance_wevew,
		.get_cuwwent_scwk = &sumo_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &sumo_dpm_get_cuwwent_mcwk,
		.get_cuwwent_vddc = &sumo_dpm_get_cuwwent_vddc,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

static stwuct wadeon_asic btc_asic = {
	.init = &evewgween_init,
	.fini = &evewgween_fini,
	.suspend = &evewgween_suspend,
	.wesume = &evewgween_wesume,
	.asic_weset = &evewgween_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &wv770_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = evewgween_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &evewgween_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &evewgween_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &evewgween_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &wv770_uvd_wing,
	},
	.iwq = {
		.set = &evewgween_iwq_set,
		.pwocess = &evewgween_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &evewgween_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &evewgween_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &evewgween_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &btc_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &w600_get_pcie_wanes,
		.set_pcie_wanes = &w600_set_pcie_wanes,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &evewgween_set_uvd_cwocks,
		.get_tempewatuwe = &evewgween_get_temp,
	},
	.dpm = {
		.init = &btc_dpm_init,
		.setup_asic = &btc_dpm_setup_asic,
		.enabwe = &btc_dpm_enabwe,
		.wate_enabwe = &wv770_dpm_wate_enabwe,
		.disabwe = &btc_dpm_disabwe,
		.pwe_set_powew_state = &btc_dpm_pwe_set_powew_state,
		.set_powew_state = &btc_dpm_set_powew_state,
		.post_set_powew_state = &btc_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &cypwess_dpm_dispway_configuwation_changed,
		.fini = &btc_dpm_fini,
		.get_scwk = &btc_dpm_get_scwk,
		.get_mcwk = &btc_dpm_get_mcwk,
		.pwint_powew_state = &wv770_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &btc_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &wv770_dpm_fowce_pewfowmance_wevew,
		.vbwank_too_showt = &btc_dpm_vbwank_too_showt,
		.get_cuwwent_scwk = &btc_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &btc_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing cayman_gfx_wing = {
	.ib_execute = &cayman_wing_ib_execute,
	.ib_pawse = &evewgween_ib_pawse,
	.emit_fence = &cayman_fence_wing_emit,
	.emit_semaphowe = &w600_semaphowe_wing_emit,
	.cs_pawse = &evewgween_cs_pawse,
	.wing_test = &w600_wing_test,
	.ib_test = &w600_ib_test,
	.is_wockup = &cayman_gfx_is_wockup,
	.vm_fwush = &cayman_vm_fwush,
	.get_wptw = &cayman_gfx_get_wptw,
	.get_wptw = &cayman_gfx_get_wptw,
	.set_wptw = &cayman_gfx_set_wptw,
};

static const stwuct wadeon_asic_wing cayman_dma_wing = {
	.ib_execute = &cayman_dma_wing_ib_execute,
	.ib_pawse = &evewgween_dma_ib_pawse,
	.emit_fence = &evewgween_dma_fence_wing_emit,
	.emit_semaphowe = &w600_dma_semaphowe_wing_emit,
	.cs_pawse = &evewgween_dma_cs_pawse,
	.wing_test = &w600_dma_wing_test,
	.ib_test = &w600_dma_ib_test,
	.is_wockup = &cayman_dma_is_wockup,
	.vm_fwush = &cayman_dma_vm_fwush,
	.get_wptw = &cayman_dma_get_wptw,
	.get_wptw = &cayman_dma_get_wptw,
	.set_wptw = &cayman_dma_set_wptw
};

static const stwuct wadeon_asic_wing cayman_uvd_wing = {
	.ib_execute = &uvd_v1_0_ib_execute,
	.emit_fence = &uvd_v2_2_fence_emit,
	.emit_semaphowe = &uvd_v3_1_semaphowe_emit,
	.cs_pawse = &wadeon_uvd_cs_pawse,
	.wing_test = &uvd_v1_0_wing_test,
	.ib_test = &uvd_v1_0_ib_test,
	.is_wockup = &wadeon_wing_test_wockup,
	.get_wptw = &uvd_v1_0_get_wptw,
	.get_wptw = &uvd_v1_0_get_wptw,
	.set_wptw = &uvd_v1_0_set_wptw,
};

static stwuct wadeon_asic cayman_asic = {
	.init = &cayman_init,
	.fini = &cayman_fini,
	.suspend = &cayman_suspend,
	.wesume = &cayman_wesume,
	.asic_weset = &cayman_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &wv770_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = cayman_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &cayman_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.vm = {
		.init = &cayman_vm_init,
		.fini = &cayman_vm_fini,
		.copy_pages = &cayman_dma_vm_copy_pages,
		.wwite_pages = &cayman_dma_vm_wwite_pages,
		.set_pages = &cayman_dma_vm_set_pages,
		.pad_ib = &cayman_dma_vm_pad_ib,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &cayman_gfx_wing,
		[CAYMAN_WING_TYPE_CP1_INDEX] = &cayman_gfx_wing,
		[CAYMAN_WING_TYPE_CP2_INDEX] = &cayman_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &cayman_dma_wing,
		[CAYMAN_WING_TYPE_DMA1_INDEX] = &cayman_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &cayman_uvd_wing,
	},
	.iwq = {
		.set = &evewgween_iwq_set,
		.pwocess = &evewgween_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &evewgween_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &evewgween_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &evewgween_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &btc_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &w600_get_pcie_wanes,
		.set_pcie_wanes = &w600_set_pcie_wanes,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &evewgween_set_uvd_cwocks,
		.get_tempewatuwe = &evewgween_get_temp,
	},
	.dpm = {
		.init = &ni_dpm_init,
		.setup_asic = &ni_dpm_setup_asic,
		.enabwe = &ni_dpm_enabwe,
		.wate_enabwe = &wv770_dpm_wate_enabwe,
		.disabwe = &ni_dpm_disabwe,
		.pwe_set_powew_state = &ni_dpm_pwe_set_powew_state,
		.set_powew_state = &ni_dpm_set_powew_state,
		.post_set_powew_state = &ni_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &cypwess_dpm_dispway_configuwation_changed,
		.fini = &ni_dpm_fini,
		.get_scwk = &ni_dpm_get_scwk,
		.get_mcwk = &ni_dpm_get_mcwk,
		.pwint_powew_state = &ni_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &ni_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &ni_dpm_fowce_pewfowmance_wevew,
		.vbwank_too_showt = &ni_dpm_vbwank_too_showt,
		.get_cuwwent_scwk = &ni_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &ni_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing twinity_vce_wing = {
	.ib_execute = &wadeon_vce_ib_execute,
	.emit_fence = &wadeon_vce_fence_emit,
	.emit_semaphowe = &wadeon_vce_semaphowe_emit,
	.cs_pawse = &wadeon_vce_cs_pawse,
	.wing_test = &wadeon_vce_wing_test,
	.ib_test = &wadeon_vce_ib_test,
	.is_wockup = &wadeon_wing_test_wockup,
	.get_wptw = &vce_v1_0_get_wptw,
	.get_wptw = &vce_v1_0_get_wptw,
	.set_wptw = &vce_v1_0_set_wptw,
};

static stwuct wadeon_asic twinity_asic = {
	.init = &cayman_init,
	.fini = &cayman_fini,
	.suspend = &cayman_suspend,
	.wesume = &cayman_wesume,
	.asic_weset = &cayman_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &w600_get_xcwk,
	.get_gpu_cwock_countew = &w600_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = cayman_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &cayman_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.vm = {
		.init = &cayman_vm_init,
		.fini = &cayman_vm_fini,
		.copy_pages = &cayman_dma_vm_copy_pages,
		.wwite_pages = &cayman_dma_vm_wwite_pages,
		.set_pages = &cayman_dma_vm_set_pages,
		.pad_ib = &cayman_dma_vm_pad_ib,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &cayman_gfx_wing,
		[CAYMAN_WING_TYPE_CP1_INDEX] = &cayman_gfx_wing,
		[CAYMAN_WING_TYPE_CP2_INDEX] = &cayman_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &cayman_dma_wing,
		[CAYMAN_WING_TYPE_DMA1_INDEX] = &cayman_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &cayman_uvd_wing,
		[TN_WING_TYPE_VCE1_INDEX] = &twinity_vce_wing,
		[TN_WING_TYPE_VCE2_INDEX] = &twinity_vce_wing,
	},
	.iwq = {
		.set = &evewgween_iwq_set,
		.pwocess = &evewgween_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &dce6_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &evewgween_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &evewgween_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &sumo_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = NUWW,
		.set_memowy_cwock = NUWW,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &sumo_set_uvd_cwocks,
		.set_vce_cwocks = &tn_set_vce_cwocks,
		.get_tempewatuwe = &tn_get_temp,
	},
	.dpm = {
		.init = &twinity_dpm_init,
		.setup_asic = &twinity_dpm_setup_asic,
		.enabwe = &twinity_dpm_enabwe,
		.wate_enabwe = &twinity_dpm_wate_enabwe,
		.disabwe = &twinity_dpm_disabwe,
		.pwe_set_powew_state = &twinity_dpm_pwe_set_powew_state,
		.set_powew_state = &twinity_dpm_set_powew_state,
		.post_set_powew_state = &twinity_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &twinity_dpm_dispway_configuwation_changed,
		.fini = &twinity_dpm_fini,
		.get_scwk = &twinity_dpm_get_scwk,
		.get_mcwk = &twinity_dpm_get_mcwk,
		.pwint_powew_state = &twinity_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &twinity_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &twinity_dpm_fowce_pewfowmance_wevew,
		.enabwe_bapm = &twinity_dpm_enabwe_bapm,
		.get_cuwwent_scwk = &twinity_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &twinity_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing si_gfx_wing = {
	.ib_execute = &si_wing_ib_execute,
	.ib_pawse = &si_ib_pawse,
	.emit_fence = &si_fence_wing_emit,
	.emit_semaphowe = &w600_semaphowe_wing_emit,
	.cs_pawse = NUWW,
	.wing_test = &w600_wing_test,
	.ib_test = &w600_ib_test,
	.is_wockup = &si_gfx_is_wockup,
	.vm_fwush = &si_vm_fwush,
	.get_wptw = &cayman_gfx_get_wptw,
	.get_wptw = &cayman_gfx_get_wptw,
	.set_wptw = &cayman_gfx_set_wptw,
};

static const stwuct wadeon_asic_wing si_dma_wing = {
	.ib_execute = &cayman_dma_wing_ib_execute,
	.ib_pawse = &evewgween_dma_ib_pawse,
	.emit_fence = &evewgween_dma_fence_wing_emit,
	.emit_semaphowe = &w600_dma_semaphowe_wing_emit,
	.cs_pawse = NUWW,
	.wing_test = &w600_dma_wing_test,
	.ib_test = &w600_dma_ib_test,
	.is_wockup = &si_dma_is_wockup,
	.vm_fwush = &si_dma_vm_fwush,
	.get_wptw = &cayman_dma_get_wptw,
	.get_wptw = &cayman_dma_get_wptw,
	.set_wptw = &cayman_dma_set_wptw,
};

static stwuct wadeon_asic si_asic = {
	.init = &si_init,
	.fini = &si_fini,
	.suspend = &si_suspend,
	.wesume = &si_wesume,
	.asic_weset = &si_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &si_get_xcwk,
	.get_gpu_cwock_countew = &si_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = si_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &si_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.vm = {
		.init = &si_vm_init,
		.fini = &si_vm_fini,
		.copy_pages = &si_dma_vm_copy_pages,
		.wwite_pages = &si_dma_vm_wwite_pages,
		.set_pages = &si_dma_vm_set_pages,
		.pad_ib = &cayman_dma_vm_pad_ib,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &si_gfx_wing,
		[CAYMAN_WING_TYPE_CP1_INDEX] = &si_gfx_wing,
		[CAYMAN_WING_TYPE_CP2_INDEX] = &si_gfx_wing,
		[W600_WING_TYPE_DMA_INDEX] = &si_dma_wing,
		[CAYMAN_WING_TYPE_DMA1_INDEX] = &si_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &cayman_uvd_wing,
		[TN_WING_TYPE_VCE1_INDEX] = &twinity_vce_wing,
		[TN_WING_TYPE_VCE2_INDEX] = &twinity_vce_wing,
	},
	.iwq = {
		.set = &si_iwq_set,
		.pwocess = &si_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &dce6_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &w600_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &si_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &si_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &sumo_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = &w600_get_pcie_wanes,
		.set_pcie_wanes = &w600_set_pcie_wanes,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &si_set_uvd_cwocks,
		.set_vce_cwocks = &si_set_vce_cwocks,
		.get_tempewatuwe = &si_get_temp,
	},
	.dpm = {
		.init = &si_dpm_init,
		.setup_asic = &si_dpm_setup_asic,
		.enabwe = &si_dpm_enabwe,
		.wate_enabwe = &si_dpm_wate_enabwe,
		.disabwe = &si_dpm_disabwe,
		.pwe_set_powew_state = &si_dpm_pwe_set_powew_state,
		.set_powew_state = &si_dpm_set_powew_state,
		.post_set_powew_state = &si_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &si_dpm_dispway_configuwation_changed,
		.fini = &si_dpm_fini,
		.get_scwk = &ni_dpm_get_scwk,
		.get_mcwk = &ni_dpm_get_mcwk,
		.pwint_powew_state = &ni_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &si_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &si_dpm_fowce_pewfowmance_wevew,
		.vbwank_too_showt = &ni_dpm_vbwank_too_showt,
		.fan_ctww_set_mode = &si_fan_ctww_set_mode,
		.fan_ctww_get_mode = &si_fan_ctww_get_mode,
		.get_fan_speed_pewcent = &si_fan_ctww_get_fan_speed_pewcent,
		.set_fan_speed_pewcent = &si_fan_ctww_set_fan_speed_pewcent,
		.get_cuwwent_scwk = &si_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &si_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

static const stwuct wadeon_asic_wing ci_gfx_wing = {
	.ib_execute = &cik_wing_ib_execute,
	.ib_pawse = &cik_ib_pawse,
	.emit_fence = &cik_fence_gfx_wing_emit,
	.emit_semaphowe = &cik_semaphowe_wing_emit,
	.cs_pawse = NUWW,
	.wing_test = &cik_wing_test,
	.ib_test = &cik_ib_test,
	.is_wockup = &cik_gfx_is_wockup,
	.vm_fwush = &cik_vm_fwush,
	.get_wptw = &cik_gfx_get_wptw,
	.get_wptw = &cik_gfx_get_wptw,
	.set_wptw = &cik_gfx_set_wptw,
};

static const stwuct wadeon_asic_wing ci_cp_wing = {
	.ib_execute = &cik_wing_ib_execute,
	.ib_pawse = &cik_ib_pawse,
	.emit_fence = &cik_fence_compute_wing_emit,
	.emit_semaphowe = &cik_semaphowe_wing_emit,
	.cs_pawse = NUWW,
	.wing_test = &cik_wing_test,
	.ib_test = &cik_ib_test,
	.is_wockup = &cik_gfx_is_wockup,
	.vm_fwush = &cik_vm_fwush,
	.get_wptw = &cik_compute_get_wptw,
	.get_wptw = &cik_compute_get_wptw,
	.set_wptw = &cik_compute_set_wptw,
};

static const stwuct wadeon_asic_wing ci_dma_wing = {
	.ib_execute = &cik_sdma_wing_ib_execute,
	.ib_pawse = &cik_ib_pawse,
	.emit_fence = &cik_sdma_fence_wing_emit,
	.emit_semaphowe = &cik_sdma_semaphowe_wing_emit,
	.cs_pawse = NUWW,
	.wing_test = &cik_sdma_wing_test,
	.ib_test = &cik_sdma_ib_test,
	.is_wockup = &cik_sdma_is_wockup,
	.vm_fwush = &cik_dma_vm_fwush,
	.get_wptw = &cik_sdma_get_wptw,
	.get_wptw = &cik_sdma_get_wptw,
	.set_wptw = &cik_sdma_set_wptw,
};

static const stwuct wadeon_asic_wing ci_vce_wing = {
	.ib_execute = &wadeon_vce_ib_execute,
	.emit_fence = &wadeon_vce_fence_emit,
	.emit_semaphowe = &wadeon_vce_semaphowe_emit,
	.cs_pawse = &wadeon_vce_cs_pawse,
	.wing_test = &wadeon_vce_wing_test,
	.ib_test = &wadeon_vce_ib_test,
	.is_wockup = &wadeon_wing_test_wockup,
	.get_wptw = &vce_v1_0_get_wptw,
	.get_wptw = &vce_v1_0_get_wptw,
	.set_wptw = &vce_v1_0_set_wptw,
};

static stwuct wadeon_asic ci_asic = {
	.init = &cik_init,
	.fini = &cik_fini,
	.suspend = &cik_suspend,
	.wesume = &cik_wesume,
	.asic_weset = &cik_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = &w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &cik_get_xcwk,
	.get_gpu_cwock_countew = &cik_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = cik_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &cik_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.vm = {
		.init = &cik_vm_init,
		.fini = &cik_vm_fini,
		.copy_pages = &cik_sdma_vm_copy_pages,
		.wwite_pages = &cik_sdma_vm_wwite_pages,
		.set_pages = &cik_sdma_vm_set_pages,
		.pad_ib = &cik_sdma_vm_pad_ib,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &ci_gfx_wing,
		[CAYMAN_WING_TYPE_CP1_INDEX] = &ci_cp_wing,
		[CAYMAN_WING_TYPE_CP2_INDEX] = &ci_cp_wing,
		[W600_WING_TYPE_DMA_INDEX] = &ci_dma_wing,
		[CAYMAN_WING_TYPE_DMA1_INDEX] = &ci_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &cayman_uvd_wing,
		[TN_WING_TYPE_VCE1_INDEX] = &ci_vce_wing,
		[TN_WING_TYPE_VCE2_INDEX] = &ci_vce_wing,
	},
	.iwq = {
		.set = &cik_iwq_set,
		.pwocess = &cik_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &dce8_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &cik_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &cik_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &cik_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &sumo_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &cik_set_uvd_cwocks,
		.set_vce_cwocks = &cik_set_vce_cwocks,
		.get_tempewatuwe = &ci_get_temp,
	},
	.dpm = {
		.init = &ci_dpm_init,
		.setup_asic = &ci_dpm_setup_asic,
		.enabwe = &ci_dpm_enabwe,
		.wate_enabwe = &ci_dpm_wate_enabwe,
		.disabwe = &ci_dpm_disabwe,
		.pwe_set_powew_state = &ci_dpm_pwe_set_powew_state,
		.set_powew_state = &ci_dpm_set_powew_state,
		.post_set_powew_state = &ci_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &ci_dpm_dispway_configuwation_changed,
		.fini = &ci_dpm_fini,
		.get_scwk = &ci_dpm_get_scwk,
		.get_mcwk = &ci_dpm_get_mcwk,
		.pwint_powew_state = &ci_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &ci_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &ci_dpm_fowce_pewfowmance_wevew,
		.vbwank_too_showt = &ci_dpm_vbwank_too_showt,
		.powewgate_uvd = &ci_dpm_powewgate_uvd,
		.fan_ctww_set_mode = &ci_fan_ctww_set_mode,
		.fan_ctww_get_mode = &ci_fan_ctww_get_mode,
		.get_fan_speed_pewcent = &ci_fan_ctww_get_fan_speed_pewcent,
		.set_fan_speed_pewcent = &ci_fan_ctww_set_fan_speed_pewcent,
		.get_cuwwent_scwk = &ci_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &ci_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

static stwuct wadeon_asic kv_asic = {
	.init = &cik_init,
	.fini = &cik_fini,
	.suspend = &cik_suspend,
	.wesume = &cik_wesume,
	.asic_weset = &cik_asic_weset,
	.vga_set_state = &w600_vga_set_state,
	.mmio_hdp_fwush = &w600_mmio_hdp_fwush,
	.gui_idwe = &w600_gui_idwe,
	.mc_wait_fow_idwe = &evewgween_mc_wait_fow_idwe,
	.get_xcwk = &cik_get_xcwk,
	.get_gpu_cwock_countew = &cik_get_gpu_cwock_countew,
	.get_awwowed_info_wegistew = cik_get_awwowed_info_wegistew,
	.gawt = {
		.twb_fwush = &cik_pcie_gawt_twb_fwush,
		.get_page_entwy = &ws600_gawt_get_page_entwy,
		.set_page = &ws600_gawt_set_page,
	},
	.vm = {
		.init = &cik_vm_init,
		.fini = &cik_vm_fini,
		.copy_pages = &cik_sdma_vm_copy_pages,
		.wwite_pages = &cik_sdma_vm_wwite_pages,
		.set_pages = &cik_sdma_vm_set_pages,
		.pad_ib = &cik_sdma_vm_pad_ib,
	},
	.wing = {
		[WADEON_WING_TYPE_GFX_INDEX] = &ci_gfx_wing,
		[CAYMAN_WING_TYPE_CP1_INDEX] = &ci_cp_wing,
		[CAYMAN_WING_TYPE_CP2_INDEX] = &ci_cp_wing,
		[W600_WING_TYPE_DMA_INDEX] = &ci_dma_wing,
		[CAYMAN_WING_TYPE_DMA1_INDEX] = &ci_dma_wing,
		[W600_WING_TYPE_UVD_INDEX] = &cayman_uvd_wing,
		[TN_WING_TYPE_VCE1_INDEX] = &ci_vce_wing,
		[TN_WING_TYPE_VCE2_INDEX] = &ci_vce_wing,
	},
	.iwq = {
		.set = &cik_iwq_set,
		.pwocess = &cik_iwq_pwocess,
	},
	.dispway = {
		.bandwidth_update = &dce8_bandwidth_update,
		.get_vbwank_countew = &evewgween_get_vbwank_countew,
		.wait_fow_vbwank = &dce4_wait_fow_vbwank,
		.set_backwight_wevew = &atombios_set_backwight_wevew,
		.get_backwight_wevew = &atombios_get_backwight_wevew,
	},
	.copy = {
		.bwit = &cik_copy_cpdma,
		.bwit_wing_index = WADEON_WING_TYPE_GFX_INDEX,
		.dma = &cik_copy_dma,
		.dma_wing_index = W600_WING_TYPE_DMA_INDEX,
		.copy = &cik_copy_dma,
		.copy_wing_index = W600_WING_TYPE_DMA_INDEX,
	},
	.suwface = {
		.set_weg = w600_set_suwface_weg,
		.cweaw_weg = w600_cweaw_suwface_weg,
	},
	.hpd = {
		.init = &evewgween_hpd_init,
		.fini = &evewgween_hpd_fini,
		.sense = &evewgween_hpd_sense,
		.set_powawity = &evewgween_hpd_set_powawity,
	},
	.pm = {
		.misc = &evewgween_pm_misc,
		.pwepawe = &evewgween_pm_pwepawe,
		.finish = &evewgween_pm_finish,
		.init_pwofiwe = &sumo_pm_init_pwofiwe,
		.get_dynpm_state = &w600_pm_get_dynpm_state,
		.get_engine_cwock = &wadeon_atom_get_engine_cwock,
		.set_engine_cwock = &wadeon_atom_set_engine_cwock,
		.get_memowy_cwock = &wadeon_atom_get_memowy_cwock,
		.set_memowy_cwock = &wadeon_atom_set_memowy_cwock,
		.get_pcie_wanes = NUWW,
		.set_pcie_wanes = NUWW,
		.set_cwock_gating = NUWW,
		.set_uvd_cwocks = &cik_set_uvd_cwocks,
		.set_vce_cwocks = &cik_set_vce_cwocks,
		.get_tempewatuwe = &kv_get_temp,
	},
	.dpm = {
		.init = &kv_dpm_init,
		.setup_asic = &kv_dpm_setup_asic,
		.enabwe = &kv_dpm_enabwe,
		.wate_enabwe = &kv_dpm_wate_enabwe,
		.disabwe = &kv_dpm_disabwe,
		.pwe_set_powew_state = &kv_dpm_pwe_set_powew_state,
		.set_powew_state = &kv_dpm_set_powew_state,
		.post_set_powew_state = &kv_dpm_post_set_powew_state,
		.dispway_configuwation_changed = &kv_dpm_dispway_configuwation_changed,
		.fini = &kv_dpm_fini,
		.get_scwk = &kv_dpm_get_scwk,
		.get_mcwk = &kv_dpm_get_mcwk,
		.pwint_powew_state = &kv_dpm_pwint_powew_state,
		.debugfs_pwint_cuwwent_pewfowmance_wevew = &kv_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew,
		.fowce_pewfowmance_wevew = &kv_dpm_fowce_pewfowmance_wevew,
		.powewgate_uvd = &kv_dpm_powewgate_uvd,
		.enabwe_bapm = &kv_dpm_enabwe_bapm,
		.get_cuwwent_scwk = &kv_dpm_get_cuwwent_scwk,
		.get_cuwwent_mcwk = &kv_dpm_get_cuwwent_mcwk,
	},
	.pfwip = {
		.page_fwip = &evewgween_page_fwip,
		.page_fwip_pending = &evewgween_page_fwip_pending,
	},
};

/**
 * wadeon_asic_init - wegistew asic specific cawwbacks
 *
 * @wdev: wadeon device pointew
 *
 * Wegistews the appwopwiate asic specific cawwbacks fow each
 * chip famiwy.  Awso sets othew asics specific info wike the numbew
 * of cwtcs and the wegistew apewtuwe accessows (aww asics).
 * Wetuwns 0 fow success.
 */
int wadeon_asic_init(stwuct wadeon_device *wdev)
{
	wadeon_wegistew_accessow_init(wdev);

	/* set the numbew of cwtcs */
	if (wdev->fwags & WADEON_SINGWE_CWTC)
		wdev->num_cwtc = 1;
	ewse
		wdev->num_cwtc = 2;

	wdev->has_uvd = fawse;
	wdev->has_vce = fawse;

	switch (wdev->famiwy) {
	case CHIP_W100:
	case CHIP_WV100:
	case CHIP_WS100:
	case CHIP_WV200:
	case CHIP_WS200:
		wdev->asic = &w100_asic;
		bweak;
	case CHIP_W200:
	case CHIP_WV250:
	case CHIP_WS300:
	case CHIP_WV280:
		wdev->asic = &w200_asic;
		bweak;
	case CHIP_W300:
	case CHIP_W350:
	case CHIP_WV350:
	case CHIP_WV380:
		if (wdev->fwags & WADEON_IS_PCIE)
			wdev->asic = &w300_asic_pcie;
		ewse
			wdev->asic = &w300_asic;
		bweak;
	case CHIP_W420:
	case CHIP_W423:
	case CHIP_WV410:
		wdev->asic = &w420_asic;
		/* handwe macs */
		if (wdev->bios == NUWW) {
			wdev->asic->pm.get_engine_cwock = &wadeon_wegacy_get_engine_cwock;
			wdev->asic->pm.set_engine_cwock = &wadeon_wegacy_set_engine_cwock;
			wdev->asic->pm.get_memowy_cwock = &wadeon_wegacy_get_memowy_cwock;
			wdev->asic->pm.set_memowy_cwock = NUWW;
			wdev->asic->dispway.set_backwight_wevew = &wadeon_wegacy_set_backwight_wevew;
		}
		bweak;
	case CHIP_WS400:
	case CHIP_WS480:
		wdev->asic = &ws400_asic;
		bweak;
	case CHIP_WS600:
		wdev->asic = &ws600_asic;
		bweak;
	case CHIP_WS690:
	case CHIP_WS740:
		wdev->asic = &ws690_asic;
		bweak;
	case CHIP_WV515:
		wdev->asic = &wv515_asic;
		bweak;
	case CHIP_W520:
	case CHIP_WV530:
	case CHIP_WV560:
	case CHIP_WV570:
	case CHIP_W580:
		wdev->asic = &w520_asic;
		bweak;
	case CHIP_W600:
		wdev->asic = &w600_asic;
		bweak;
	case CHIP_WV610:
	case CHIP_WV630:
	case CHIP_WV620:
	case CHIP_WV635:
	case CHIP_WV670:
		wdev->asic = &wv6xx_asic;
		wdev->has_uvd = twue;
		bweak;
	case CHIP_WS780:
	case CHIP_WS880:
		wdev->asic = &ws780_asic;
		/* 760G/780V/880V don't have UVD */
		if ((wdev->pdev->device == 0x9616)||
		    (wdev->pdev->device == 0x9611)||
		    (wdev->pdev->device == 0x9613)||
		    (wdev->pdev->device == 0x9711)||
		    (wdev->pdev->device == 0x9713))
			wdev->has_uvd = fawse;
		ewse
			wdev->has_uvd = twue;
		bweak;
	case CHIP_WV770:
	case CHIP_WV730:
	case CHIP_WV710:
	case CHIP_WV740:
		wdev->asic = &wv770_asic;
		wdev->has_uvd = twue;
		bweak;
	case CHIP_CEDAW:
	case CHIP_WEDWOOD:
	case CHIP_JUNIPEW:
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		/* set num cwtcs */
		if (wdev->famiwy == CHIP_CEDAW)
			wdev->num_cwtc = 4;
		ewse
			wdev->num_cwtc = 6;
		wdev->asic = &evewgween_asic;
		wdev->has_uvd = twue;
		bweak;
	case CHIP_PAWM:
	case CHIP_SUMO:
	case CHIP_SUMO2:
		wdev->asic = &sumo_asic;
		wdev->has_uvd = twue;
		bweak;
	case CHIP_BAWTS:
	case CHIP_TUWKS:
	case CHIP_CAICOS:
		/* set num cwtcs */
		if (wdev->famiwy == CHIP_CAICOS)
			wdev->num_cwtc = 4;
		ewse
			wdev->num_cwtc = 6;
		wdev->asic = &btc_asic;
		wdev->has_uvd = twue;
		bweak;
	case CHIP_CAYMAN:
		wdev->asic = &cayman_asic;
		/* set num cwtcs */
		wdev->num_cwtc = 6;
		wdev->has_uvd = twue;
		bweak;
	case CHIP_AWUBA:
		wdev->asic = &twinity_asic;
		/* set num cwtcs */
		wdev->num_cwtc = 4;
		wdev->has_uvd = twue;
		wdev->has_vce = twue;
		wdev->cg_fwags =
			WADEON_CG_SUPPOWT_VCE_MGCG;
		bweak;
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	case CHIP_OWAND:
	case CHIP_HAINAN:
		wdev->asic = &si_asic;
		/* set num cwtcs */
		if (wdev->famiwy == CHIP_HAINAN)
			wdev->num_cwtc = 0;
		ewse if (wdev->famiwy == CHIP_OWAND)
			wdev->num_cwtc = 2;
		ewse
			wdev->num_cwtc = 6;
		if (wdev->famiwy == CHIP_HAINAN) {
			wdev->has_uvd = fawse;
			wdev->has_vce = fawse;
		} ewse if (wdev->famiwy == CHIP_OWAND) {
			wdev->has_uvd = twue;
			wdev->has_vce = fawse;
		} ewse {
			wdev->has_uvd = twue;
			wdev->has_vce = twue;
		}
		switch (wdev->famiwy) {
		case CHIP_TAHITI:
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_MC_MGCG |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_VCE_MGCG |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
			bweak;
		case CHIP_PITCAIWN:
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_GFX_WWC_WS |
				WADEON_CG_SUPPOWT_MC_WS |
				WADEON_CG_SUPPOWT_MC_MGCG |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_VCE_MGCG |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
			bweak;
		case CHIP_VEWDE:
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_GFX_WWC_WS |
				WADEON_CG_SUPPOWT_MC_WS |
				WADEON_CG_SUPPOWT_MC_MGCG |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_VCE_MGCG |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0 |
				/*WADEON_PG_SUPPOWT_GFX_PG | */
				WADEON_PG_SUPPOWT_SDMA;
			bweak;
		case CHIP_OWAND:
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_GFX_WWC_WS |
				WADEON_CG_SUPPOWT_MC_WS |
				WADEON_CG_SUPPOWT_MC_MGCG |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
			bweak;
		case CHIP_HAINAN:
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_GFX_WWC_WS |
				WADEON_CG_SUPPOWT_MC_WS |
				WADEON_CG_SUPPOWT_MC_MGCG |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
			bweak;
		defauwt:
			wdev->cg_fwags = 0;
			wdev->pg_fwags = 0;
			bweak;
		}
		bweak;
	case CHIP_BONAIWE:
	case CHIP_HAWAII:
		wdev->asic = &ci_asic;
		wdev->num_cwtc = 6;
		wdev->has_uvd = twue;
		wdev->has_vce = twue;
		if (wdev->famiwy == CHIP_BONAIWE) {
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CGTS_WS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_MC_WS |
				WADEON_CG_SUPPOWT_MC_MGCG |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_SDMA_WS |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_VCE_MGCG |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
		} ewse {
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_MC_WS |
				WADEON_CG_SUPPOWT_MC_MGCG |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_SDMA_WS |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_VCE_MGCG |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
		}
		bweak;
	case CHIP_KAVEWI:
	case CHIP_KABINI:
	case CHIP_MUWWINS:
		wdev->asic = &kv_asic;
		/* set num cwtcs */
		if (wdev->famiwy == CHIP_KAVEWI) {
			wdev->num_cwtc = 4;
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CGTS_WS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_SDMA_WS |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_VCE_MGCG |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
				/*WADEON_PG_SUPPOWT_GFX_PG |
				WADEON_PG_SUPPOWT_GFX_SMG |
				WADEON_PG_SUPPOWT_GFX_DMG |
				WADEON_PG_SUPPOWT_UVD |
				WADEON_PG_SUPPOWT_VCE |
				WADEON_PG_SUPPOWT_CP |
				WADEON_PG_SUPPOWT_GDS |
				WADEON_PG_SUPPOWT_WWC_SMU_HS |
				WADEON_PG_SUPPOWT_ACP |
				WADEON_PG_SUPPOWT_SAMU;*/
		} ewse {
			wdev->num_cwtc = 2;
			wdev->cg_fwags =
				WADEON_CG_SUPPOWT_GFX_MGCG |
				WADEON_CG_SUPPOWT_GFX_MGWS |
				/*WADEON_CG_SUPPOWT_GFX_CGCG |*/
				WADEON_CG_SUPPOWT_GFX_CGWS |
				WADEON_CG_SUPPOWT_GFX_CGTS |
				WADEON_CG_SUPPOWT_GFX_CGTS_WS |
				WADEON_CG_SUPPOWT_GFX_CP_WS |
				WADEON_CG_SUPPOWT_SDMA_MGCG |
				WADEON_CG_SUPPOWT_SDMA_WS |
				WADEON_CG_SUPPOWT_BIF_WS |
				WADEON_CG_SUPPOWT_VCE_MGCG |
				WADEON_CG_SUPPOWT_UVD_MGCG |
				WADEON_CG_SUPPOWT_HDP_WS |
				WADEON_CG_SUPPOWT_HDP_MGCG;
			wdev->pg_fwags = 0;
				/*WADEON_PG_SUPPOWT_GFX_PG |
				WADEON_PG_SUPPOWT_GFX_SMG |
				WADEON_PG_SUPPOWT_UVD |
				WADEON_PG_SUPPOWT_VCE |
				WADEON_PG_SUPPOWT_CP |
				WADEON_PG_SUPPOWT_GDS |
				WADEON_PG_SUPPOWT_WWC_SMU_HS |
				WADEON_PG_SUPPOWT_SAMU;*/
		}
		wdev->has_uvd = twue;
		wdev->has_vce = twue;
		bweak;
	defauwt:
		/* FIXME: not suppowted yet */
		wetuwn -EINVAW;
	}

	if (wdev->fwags & WADEON_IS_IGP) {
		wdev->asic->pm.get_memowy_cwock = NUWW;
		wdev->asic->pm.set_memowy_cwock = NUWW;
	}

	if (!wadeon_uvd)
		wdev->has_uvd = fawse;
	if (!wadeon_vce)
		wdev->has_vce = fawse;

	wetuwn 0;
}

