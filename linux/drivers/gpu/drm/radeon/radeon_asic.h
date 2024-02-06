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
#ifndef __WADEON_ASIC_H__
#define __WADEON_ASIC_H__

/*
 * common functions
 */
uint32_t wadeon_wegacy_get_engine_cwock(stwuct wadeon_device *wdev);
void wadeon_wegacy_set_engine_cwock(stwuct wadeon_device *wdev, uint32_t eng_cwock);
uint32_t wadeon_wegacy_get_memowy_cwock(stwuct wadeon_device *wdev);
void wadeon_wegacy_set_cwock_gating(stwuct wadeon_device *wdev, int enabwe);

uint32_t wadeon_atom_get_engine_cwock(stwuct wadeon_device *wdev);
void wadeon_atom_set_engine_cwock(stwuct wadeon_device *wdev, uint32_t eng_cwock);
uint32_t wadeon_atom_get_memowy_cwock(stwuct wadeon_device *wdev);
void wadeon_atom_set_memowy_cwock(stwuct wadeon_device *wdev, uint32_t mem_cwock);
void wadeon_atom_set_cwock_gating(stwuct wadeon_device *wdev, int enabwe);

void atombios_set_backwight_wevew(stwuct wadeon_encodew *wadeon_encodew, u8 wevew);
u8 atombios_get_backwight_wevew(stwuct wadeon_encodew *wadeon_encodew);
void wadeon_wegacy_set_backwight_wevew(stwuct wadeon_encodew *wadeon_encodew, u8 wevew);
u8 wadeon_wegacy_get_backwight_wevew(stwuct wadeon_encodew *wadeon_encodew);

/*
 * w100,wv100,ws100,wv200,ws200
 */
stwuct w100_mc_save {
	u32	GENMO_WT;
	u32	CWTC_EXT_CNTW;
	u32	CWTC_GEN_CNTW;
	u32	CWTC2_GEN_CNTW;
	u32	CUW_OFFSET;
	u32	CUW2_OFFSET;
};
int w100_init(stwuct wadeon_device *wdev);
void w100_fini(stwuct wadeon_device *wdev);
int w100_suspend(stwuct wadeon_device *wdev);
int w100_wesume(stwuct wadeon_device *wdev);
void w100_vga_set_state(stwuct wadeon_device *wdev, boow state);
boow w100_gpu_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
int w100_asic_weset(stwuct wadeon_device *wdev, boow hawd);
u32 w100_get_vbwank_countew(stwuct wadeon_device *wdev, int cwtc);
void w100_pci_gawt_twb_fwush(stwuct wadeon_device *wdev);
uint64_t w100_pci_gawt_get_page_entwy(uint64_t addw, uint32_t fwags);
void w100_pci_gawt_set_page(stwuct wadeon_device *wdev, unsigned i,
			    uint64_t entwy);
void w100_wing_stawt(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
int w100_iwq_set(stwuct wadeon_device *wdev);
int w100_iwq_pwocess(stwuct wadeon_device *wdev);
void w100_fence_wing_emit(stwuct wadeon_device *wdev,
			  stwuct wadeon_fence *fence);
boow w100_semaphowe_wing_emit(stwuct wadeon_device *wdev,
			      stwuct wadeon_wing *cp,
			      stwuct wadeon_semaphowe *semaphowe,
			      boow emit_wait);
int w100_cs_pawse(stwuct wadeon_cs_pawsew *p);
void w100_pww_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
uint32_t w100_pww_wweg(stwuct wadeon_device *wdev, uint32_t weg);
stwuct wadeon_fence *w100_copy_bwit(stwuct wadeon_device *wdev,
				    uint64_t swc_offset,
				    uint64_t dst_offset,
				    unsigned num_gpu_pages,
				    stwuct dma_wesv *wesv);
int w100_set_suwface_weg(stwuct wadeon_device *wdev, int weg,
			 uint32_t tiwing_fwags, uint32_t pitch,
			 uint32_t offset, uint32_t obj_size);
void w100_cweaw_suwface_weg(stwuct wadeon_device *wdev, int weg);
void w100_bandwidth_update(stwuct wadeon_device *wdev);
void w100_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
int w100_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
void w100_hpd_init(stwuct wadeon_device *wdev);
void w100_hpd_fini(stwuct wadeon_device *wdev);
boow w100_hpd_sense(stwuct wadeon_device *wdev, enum wadeon_hpd_id hpd);
void w100_hpd_set_powawity(stwuct wadeon_device *wdev,
			   enum wadeon_hpd_id hpd);
void w100_debugfs_wbbm_init(stwuct wadeon_device *wdev);
void w100_debugfs_cp_init(stwuct wadeon_device *wdev);
void w100_cp_disabwe(stwuct wadeon_device *wdev);
int w100_cp_init(stwuct wadeon_device *wdev, unsigned wing_size);
void w100_cp_fini(stwuct wadeon_device *wdev);
int w100_pci_gawt_init(stwuct wadeon_device *wdev);
void w100_pci_gawt_fini(stwuct wadeon_device *wdev);
int w100_pci_gawt_enabwe(stwuct wadeon_device *wdev);
void w100_pci_gawt_disabwe(stwuct wadeon_device *wdev);
void  w100_debugfs_mc_info_init(stwuct wadeon_device *wdev);
int w100_gui_wait_fow_idwe(stwuct wadeon_device *wdev);
int w100_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
void w100_iwq_disabwe(stwuct wadeon_device *wdev);
void w100_mc_stop(stwuct wadeon_device *wdev, stwuct w100_mc_save *save);
void w100_mc_wesume(stwuct wadeon_device *wdev, stwuct w100_mc_save *save);
void w100_vwam_init_sizes(stwuct wadeon_device *wdev);
int w100_cp_weset(stwuct wadeon_device *wdev);
void w100_vga_wendew_disabwe(stwuct wadeon_device *wdev);
void w100_westowe_sanity(stwuct wadeon_device *wdev);
int w100_cs_twack_check_pkt3_indx_buffew(stwuct wadeon_cs_pawsew *p,
					 stwuct wadeon_cs_packet *pkt,
					 stwuct wadeon_bo *wobj);
int w100_cs_pawse_packet0(stwuct wadeon_cs_pawsew *p,
			  stwuct wadeon_cs_packet *pkt,
			  const unsigned *auth, unsigned n,
			  wadeon_packet0_check_t check);
int w100_cs_packet_pawse(stwuct wadeon_cs_pawsew *p,
			 stwuct wadeon_cs_packet *pkt,
			 unsigned idx);
void w100_enabwe_bm(stwuct wadeon_device *wdev);
void w100_set_common_wegs(stwuct wadeon_device *wdev);
void w100_bm_disabwe(stwuct wadeon_device *wdev);
extewn boow w100_gui_idwe(stwuct wadeon_device *wdev);
extewn void w100_pm_misc(stwuct wadeon_device *wdev);
extewn void w100_pm_pwepawe(stwuct wadeon_device *wdev);
extewn void w100_pm_finish(stwuct wadeon_device *wdev);
extewn void w100_pm_init_pwofiwe(stwuct wadeon_device *wdev);
extewn void w100_pm_get_dynpm_state(stwuct wadeon_device *wdev);
extewn void w100_page_fwip(stwuct wadeon_device *wdev, int cwtc,
			   u64 cwtc_base, boow async);
extewn boow w100_page_fwip_pending(stwuct wadeon_device *wdev, int cwtc);
extewn void w100_wait_fow_vbwank(stwuct wadeon_device *wdev, int cwtc);
extewn int w100_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

u32 w100_gfx_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing);
u32 w100_gfx_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing);
void w100_gfx_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing);

/*
 * w200,wv250,ws300,wv280
 */
stwuct wadeon_fence *w200_copy_dma(stwuct wadeon_device *wdev,
				   uint64_t swc_offset,
				   uint64_t dst_offset,
				   unsigned num_gpu_pages,
				   stwuct dma_wesv *wesv);
void w200_set_safe_wegistews(stwuct wadeon_device *wdev);

/*
 * w300,w350,wv350,wv380
 */
extewn int w300_init(stwuct wadeon_device *wdev);
extewn void w300_fini(stwuct wadeon_device *wdev);
extewn int w300_suspend(stwuct wadeon_device *wdev);
extewn int w300_wesume(stwuct wadeon_device *wdev);
extewn int w300_asic_weset(stwuct wadeon_device *wdev, boow hawd);
extewn void w300_wing_stawt(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
extewn void w300_fence_wing_emit(stwuct wadeon_device *wdev,
				stwuct wadeon_fence *fence);
extewn int w300_cs_pawse(stwuct wadeon_cs_pawsew *p);
extewn void wv370_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev);
extewn uint64_t wv370_pcie_gawt_get_page_entwy(uint64_t addw, uint32_t fwags);
extewn void wv370_pcie_gawt_set_page(stwuct wadeon_device *wdev, unsigned i,
				     uint64_t entwy);
extewn void wv370_set_pcie_wanes(stwuct wadeon_device *wdev, int wanes);
extewn int wv370_get_pcie_wanes(stwuct wadeon_device *wdev);
extewn void w300_set_weg_safe(stwuct wadeon_device *wdev);
extewn void w300_mc_pwogwam(stwuct wadeon_device *wdev);
extewn void w300_mc_init(stwuct wadeon_device *wdev);
extewn void w300_cwock_stawtup(stwuct wadeon_device *wdev);
extewn int w300_mc_wait_fow_idwe(stwuct wadeon_device *wdev);
extewn int wv370_pcie_gawt_init(stwuct wadeon_device *wdev);
extewn void wv370_pcie_gawt_fini(stwuct wadeon_device *wdev);
extewn int wv370_pcie_gawt_enabwe(stwuct wadeon_device *wdev);
extewn void wv370_pcie_gawt_disabwe(stwuct wadeon_device *wdev);

/*
 * w420,w423,wv410
 */
extewn int w420_init(stwuct wadeon_device *wdev);
extewn void w420_fini(stwuct wadeon_device *wdev);
extewn int w420_suspend(stwuct wadeon_device *wdev);
extewn int w420_wesume(stwuct wadeon_device *wdev);
extewn void w420_pm_init_pwofiwe(stwuct wadeon_device *wdev);
extewn u32 w420_mc_wweg(stwuct wadeon_device *wdev, u32 weg);
extewn void w420_mc_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v);
extewn void w420_debugfs_pipes_info_init(stwuct wadeon_device *wdev);
extewn void w420_pipes_init(stwuct wadeon_device *wdev);

/*
 * ws400,ws480
 */
extewn int ws400_init(stwuct wadeon_device *wdev);
extewn void ws400_fini(stwuct wadeon_device *wdev);
extewn int ws400_suspend(stwuct wadeon_device *wdev);
extewn int ws400_wesume(stwuct wadeon_device *wdev);
void ws400_gawt_twb_fwush(stwuct wadeon_device *wdev);
uint64_t ws400_gawt_get_page_entwy(uint64_t addw, uint32_t fwags);
void ws400_gawt_set_page(stwuct wadeon_device *wdev, unsigned i,
			 uint64_t entwy);
uint32_t ws400_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg);
void ws400_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
int ws400_gawt_init(stwuct wadeon_device *wdev);
int ws400_gawt_enabwe(stwuct wadeon_device *wdev);
void ws400_gawt_adjust_size(stwuct wadeon_device *wdev);
void ws400_gawt_disabwe(stwuct wadeon_device *wdev);
void ws400_gawt_fini(stwuct wadeon_device *wdev);
extewn int ws400_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

/*
 * ws600.
 */
extewn int ws600_asic_weset(stwuct wadeon_device *wdev, boow hawd);
extewn int ws600_init(stwuct wadeon_device *wdev);
extewn void ws600_fini(stwuct wadeon_device *wdev);
extewn int ws600_suspend(stwuct wadeon_device *wdev);
extewn int ws600_wesume(stwuct wadeon_device *wdev);
int ws600_iwq_set(stwuct wadeon_device *wdev);
int ws600_iwq_pwocess(stwuct wadeon_device *wdev);
void ws600_iwq_disabwe(stwuct wadeon_device *wdev);
u32 ws600_get_vbwank_countew(stwuct wadeon_device *wdev, int cwtc);
void ws600_gawt_twb_fwush(stwuct wadeon_device *wdev);
uint64_t ws600_gawt_get_page_entwy(uint64_t addw, uint32_t fwags);
void ws600_gawt_set_page(stwuct wadeon_device *wdev, unsigned i,
			 uint64_t entwy);
uint32_t ws600_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg);
void ws600_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
void ws600_bandwidth_update(stwuct wadeon_device *wdev);
void ws600_hpd_init(stwuct wadeon_device *wdev);
void ws600_hpd_fini(stwuct wadeon_device *wdev);
boow ws600_hpd_sense(stwuct wadeon_device *wdev, enum wadeon_hpd_id hpd);
void ws600_hpd_set_powawity(stwuct wadeon_device *wdev,
			    enum wadeon_hpd_id hpd);
extewn void ws600_pm_misc(stwuct wadeon_device *wdev);
extewn void ws600_pm_pwepawe(stwuct wadeon_device *wdev);
extewn void ws600_pm_finish(stwuct wadeon_device *wdev);
extewn void ws600_page_fwip(stwuct wadeon_device *wdev, int cwtc,
			    u64 cwtc_base, boow async);
extewn boow ws600_page_fwip_pending(stwuct wadeon_device *wdev, int cwtc);
void ws600_set_safe_wegistews(stwuct wadeon_device *wdev);
extewn void avivo_wait_fow_vbwank(stwuct wadeon_device *wdev, int cwtc);
extewn int ws600_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

/*
 * ws690,ws740
 */
int ws690_init(stwuct wadeon_device *wdev);
void ws690_fini(stwuct wadeon_device *wdev);
int ws690_wesume(stwuct wadeon_device *wdev);
int ws690_suspend(stwuct wadeon_device *wdev);
uint32_t ws690_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg);
void ws690_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
void ws690_bandwidth_update(stwuct wadeon_device *wdev);
void ws690_wine_buffew_adjust(stwuct wadeon_device *wdev,
					stwuct dwm_dispway_mode *mode1,
					stwuct dwm_dispway_mode *mode2);
extewn int ws690_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

/*
 * wv515
 */
stwuct wv515_mc_save {
	u32 vga_wendew_contwow;
	u32 vga_hdp_contwow;
	boow cwtc_enabwed[2];
};

int wv515_init(stwuct wadeon_device *wdev);
void wv515_fini(stwuct wadeon_device *wdev);
uint32_t wv515_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg);
void wv515_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
void wv515_wing_stawt(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
void wv515_bandwidth_update(stwuct wadeon_device *wdev);
int wv515_wesume(stwuct wadeon_device *wdev);
int wv515_suspend(stwuct wadeon_device *wdev);
void wv515_bandwidth_avivo_update(stwuct wadeon_device *wdev);
void wv515_vga_wendew_disabwe(stwuct wadeon_device *wdev);
void wv515_set_safe_wegistews(stwuct wadeon_device *wdev);
void wv515_mc_stop(stwuct wadeon_device *wdev, stwuct wv515_mc_save *save);
void wv515_mc_wesume(stwuct wadeon_device *wdev, stwuct wv515_mc_save *save);
void wv515_cwock_stawtup(stwuct wadeon_device *wdev);
void wv515_debugfs(stwuct wadeon_device *wdev);
int wv515_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

/*
 * w520,wv530,wv560,wv570,w580
 */
int w520_init(stwuct wadeon_device *wdev);
int w520_wesume(stwuct wadeon_device *wdev);
int w520_mc_wait_fow_idwe(stwuct wadeon_device *wdev);

/*
 * w600,wv610,wv630,wv620,wv635,wv670,ws780,ws880
 */
int w600_init(stwuct wadeon_device *wdev);
void w600_fini(stwuct wadeon_device *wdev);
int w600_suspend(stwuct wadeon_device *wdev);
int w600_wesume(stwuct wadeon_device *wdev);
void w600_vga_set_state(stwuct wadeon_device *wdev, boow state);
int w600_wb_init(stwuct wadeon_device *wdev);
void w600_wb_fini(stwuct wadeon_device *wdev);
void w600_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev);
uint32_t w600_pciep_wweg(stwuct wadeon_device *wdev, uint32_t weg);
void w600_pciep_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
int w600_cs_pawse(stwuct wadeon_cs_pawsew *p);
int w600_dma_cs_pawse(stwuct wadeon_cs_pawsew *p);
void w600_fence_wing_emit(stwuct wadeon_device *wdev,
			  stwuct wadeon_fence *fence);
boow w600_semaphowe_wing_emit(stwuct wadeon_device *wdev,
			      stwuct wadeon_wing *cp,
			      stwuct wadeon_semaphowe *semaphowe,
			      boow emit_wait);
void w600_dma_fence_wing_emit(stwuct wadeon_device *wdev,
			      stwuct wadeon_fence *fence);
boow w600_dma_semaphowe_wing_emit(stwuct wadeon_device *wdev,
				  stwuct wadeon_wing *wing,
				  stwuct wadeon_semaphowe *semaphowe,
				  boow emit_wait);
void w600_dma_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
boow w600_dma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
boow w600_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
int w600_asic_weset(stwuct wadeon_device *wdev, boow hawd);
int w600_set_suwface_weg(stwuct wadeon_device *wdev, int weg,
			 uint32_t tiwing_fwags, uint32_t pitch,
			 uint32_t offset, uint32_t obj_size);
void w600_cweaw_suwface_weg(stwuct wadeon_device *wdev, int weg);
int w600_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
int w600_dma_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
void w600_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
int w600_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
int w600_dma_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
stwuct wadeon_fence *w600_copy_cpdma(stwuct wadeon_device *wdev,
				     uint64_t swc_offset, uint64_t dst_offset,
				     unsigned num_gpu_pages,
				     stwuct dma_wesv *wesv);
stwuct wadeon_fence *w600_copy_dma(stwuct wadeon_device *wdev,
				   uint64_t swc_offset, uint64_t dst_offset,
				   unsigned num_gpu_pages,
				   stwuct dma_wesv *wesv);
void w600_hpd_init(stwuct wadeon_device *wdev);
void w600_hpd_fini(stwuct wadeon_device *wdev);
boow w600_hpd_sense(stwuct wadeon_device *wdev, enum wadeon_hpd_id hpd);
void w600_hpd_set_powawity(stwuct wadeon_device *wdev,
			   enum wadeon_hpd_id hpd);
extewn void w600_mmio_hdp_fwush(stwuct wadeon_device *wdev);
extewn boow w600_gui_idwe(stwuct wadeon_device *wdev);
extewn void w600_pm_misc(stwuct wadeon_device *wdev);
extewn void w600_pm_init_pwofiwe(stwuct wadeon_device *wdev);
extewn void ws780_pm_init_pwofiwe(stwuct wadeon_device *wdev);
extewn uint32_t ws780_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg);
extewn void ws780_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
extewn void w600_pm_get_dynpm_state(stwuct wadeon_device *wdev);
extewn void w600_set_pcie_wanes(stwuct wadeon_device *wdev, int wanes);
extewn int w600_get_pcie_wanes(stwuct wadeon_device *wdev);
boow w600_cawd_posted(stwuct wadeon_device *wdev);
void w600_cp_stop(stwuct wadeon_device *wdev);
int w600_cp_stawt(stwuct wadeon_device *wdev);
void w600_wing_init(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp, unsigned wing_size);
int w600_cp_wesume(stwuct wadeon_device *wdev);
void w600_cp_fini(stwuct wadeon_device *wdev);
int w600_count_pipe_bits(uint32_t vaw);
int w600_mc_wait_fow_idwe(stwuct wadeon_device *wdev);
int w600_pcie_gawt_init(stwuct wadeon_device *wdev);
void w600_scwatch_init(stwuct wadeon_device *wdev);
int w600_init_micwocode(stwuct wadeon_device *wdev);
u32 w600_gfx_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing);
u32 w600_gfx_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing);
void w600_gfx_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing);
int w600_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
				   u32 weg, u32 *vaw);
/* w600 iwq */
int w600_iwq_pwocess(stwuct wadeon_device *wdev);
int w600_iwq_init(stwuct wadeon_device *wdev);
void w600_iwq_fini(stwuct wadeon_device *wdev);
void w600_ih_wing_init(stwuct wadeon_device *wdev, unsigned wing_size);
int w600_iwq_set(stwuct wadeon_device *wdev);
void w600_iwq_suspend(stwuct wadeon_device *wdev);
void w600_disabwe_intewwupts(stwuct wadeon_device *wdev);
void w600_wwc_stop(stwuct wadeon_device *wdev);
/* w600 audio */
void w600_audio_fini(stwuct wadeon_device *wdev);
void w600_audio_set_dto(stwuct dwm_encodew *encodew, u32 cwock);
void w600_hdmi_update_avi_infofwame(stwuct dwm_encodew *encodew, void *buffew,
				    size_t size);
void w600_hdmi_update_ACW(stwuct dwm_encodew *encodew, uint32_t cwock);
void w600_hdmi_audio_wowkawound(stwuct dwm_encodew *encodew);
int w600_hdmi_buffew_status_changed(stwuct dwm_encodew *encodew);
void w600_hdmi_update_audio_settings(stwuct dwm_encodew *encodew);
u32 w600_get_xcwk(stwuct wadeon_device *wdev);
uint64_t w600_get_gpu_cwock_countew(stwuct wadeon_device *wdev);
int wv6xx_get_temp(stwuct wadeon_device *wdev);
int w600_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk);
int w600_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
void w600_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
int w600_dpm_wate_enabwe(stwuct wadeon_device *wdev);
/* w600 dma */
uint32_t w600_dma_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing);
uint32_t w600_dma_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing);
void w600_dma_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing);
/* wv6xx dpm */
int wv6xx_dpm_init(stwuct wadeon_device *wdev);
int wv6xx_dpm_enabwe(stwuct wadeon_device *wdev);
void wv6xx_dpm_disabwe(stwuct wadeon_device *wdev);
int wv6xx_dpm_set_powew_state(stwuct wadeon_device *wdev);
void wv6xx_setup_asic(stwuct wadeon_device *wdev);
void wv6xx_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void wv6xx_dpm_fini(stwuct wadeon_device *wdev);
u32 wv6xx_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 wv6xx_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void wv6xx_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *ps);
void wv6xx_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						       stwuct seq_fiwe *m);
int wv6xx_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				      enum wadeon_dpm_fowced_wevew wevew);
u32 wv6xx_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 wv6xx_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);
/* ws780 dpm */
int ws780_dpm_init(stwuct wadeon_device *wdev);
int ws780_dpm_enabwe(stwuct wadeon_device *wdev);
void ws780_dpm_disabwe(stwuct wadeon_device *wdev);
int ws780_dpm_set_powew_state(stwuct wadeon_device *wdev);
void ws780_dpm_setup_asic(stwuct wadeon_device *wdev);
void ws780_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void ws780_dpm_fini(stwuct wadeon_device *wdev);
u32 ws780_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 ws780_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void ws780_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *ps);
void ws780_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						       stwuct seq_fiwe *m);
int ws780_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				      enum wadeon_dpm_fowced_wevew wevew);
u32 ws780_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 ws780_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);

/*
 * wv770,wv730,wv710,wv740
 */
int wv770_init(stwuct wadeon_device *wdev);
void wv770_fini(stwuct wadeon_device *wdev);
int wv770_suspend(stwuct wadeon_device *wdev);
int wv770_wesume(stwuct wadeon_device *wdev);
void wv770_pm_misc(stwuct wadeon_device *wdev);
void wv770_page_fwip(stwuct wadeon_device *wdev, int cwtc, u64 cwtc_base,
		     boow async);
boow wv770_page_fwip_pending(stwuct wadeon_device *wdev, int cwtc);
void w700_vwam_gtt_wocation(stwuct wadeon_device *wdev, stwuct wadeon_mc *mc);
void w700_cp_stop(stwuct wadeon_device *wdev);
void w700_cp_fini(stwuct wadeon_device *wdev);
stwuct wadeon_fence *wv770_copy_dma(stwuct wadeon_device *wdev,
				    uint64_t swc_offset, uint64_t dst_offset,
				    unsigned num_gpu_pages,
				    stwuct dma_wesv *wesv);
u32 wv770_get_xcwk(stwuct wadeon_device *wdev);
int wv770_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk);
int wv770_get_temp(stwuct wadeon_device *wdev);
/* wv7xx pm */
int wv770_dpm_init(stwuct wadeon_device *wdev);
int wv770_dpm_enabwe(stwuct wadeon_device *wdev);
int wv770_dpm_wate_enabwe(stwuct wadeon_device *wdev);
void wv770_dpm_disabwe(stwuct wadeon_device *wdev);
int wv770_dpm_set_powew_state(stwuct wadeon_device *wdev);
void wv770_dpm_setup_asic(stwuct wadeon_device *wdev);
void wv770_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void wv770_dpm_fini(stwuct wadeon_device *wdev);
u32 wv770_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 wv770_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void wv770_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *ps);
void wv770_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						       stwuct seq_fiwe *m);
int wv770_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				      enum wadeon_dpm_fowced_wevew wevew);
boow wv770_dpm_vbwank_too_showt(stwuct wadeon_device *wdev);
u32 wv770_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 wv770_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);

/*
 * evewgween
 */
stwuct evewgween_mc_save {
	u32 vga_wendew_contwow;
	u32 vga_hdp_contwow;
	boow cwtc_enabwed[WADEON_MAX_CWTCS];
};

void evewgween_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev);
int evewgween_init(stwuct wadeon_device *wdev);
void evewgween_fini(stwuct wadeon_device *wdev);
int evewgween_suspend(stwuct wadeon_device *wdev);
int evewgween_wesume(stwuct wadeon_device *wdev);
boow evewgween_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
boow evewgween_dma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
int evewgween_asic_weset(stwuct wadeon_device *wdev, boow hawd);
void evewgween_bandwidth_update(stwuct wadeon_device *wdev);
void evewgween_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
void evewgween_hpd_init(stwuct wadeon_device *wdev);
void evewgween_hpd_fini(stwuct wadeon_device *wdev);
boow evewgween_hpd_sense(stwuct wadeon_device *wdev, enum wadeon_hpd_id hpd);
void evewgween_hpd_set_powawity(stwuct wadeon_device *wdev,
				enum wadeon_hpd_id hpd);
u32 evewgween_get_vbwank_countew(stwuct wadeon_device *wdev, int cwtc);
int evewgween_iwq_set(stwuct wadeon_device *wdev);
int evewgween_iwq_pwocess(stwuct wadeon_device *wdev);
extewn int evewgween_cs_pawse(stwuct wadeon_cs_pawsew *p);
extewn int evewgween_dma_cs_pawse(stwuct wadeon_cs_pawsew *p);
extewn void evewgween_pm_misc(stwuct wadeon_device *wdev);
extewn void evewgween_pm_pwepawe(stwuct wadeon_device *wdev);
extewn void evewgween_pm_finish(stwuct wadeon_device *wdev);
extewn void sumo_pm_init_pwofiwe(stwuct wadeon_device *wdev);
extewn void btc_pm_init_pwofiwe(stwuct wadeon_device *wdev);
int sumo_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk);
int evewgween_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk);
extewn void evewgween_page_fwip(stwuct wadeon_device *wdev, int cwtc,
				u64 cwtc_base, boow async);
extewn boow evewgween_page_fwip_pending(stwuct wadeon_device *wdev, int cwtc);
extewn void dce4_wait_fow_vbwank(stwuct wadeon_device *wdev, int cwtc);
void evewgween_disabwe_intewwupt_state(stwuct wadeon_device *wdev);
int evewgween_mc_wait_fow_idwe(stwuct wadeon_device *wdev);
void evewgween_dma_fence_wing_emit(stwuct wadeon_device *wdev,
				   stwuct wadeon_fence *fence);
void evewgween_dma_wing_ib_execute(stwuct wadeon_device *wdev,
				   stwuct wadeon_ib *ib);
stwuct wadeon_fence *evewgween_copy_dma(stwuct wadeon_device *wdev,
					uint64_t swc_offset, uint64_t dst_offset,
					unsigned num_gpu_pages,
					stwuct dma_wesv *wesv);
int evewgween_get_temp(stwuct wadeon_device *wdev);
int evewgween_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
					u32 weg, u32 *vaw);
int sumo_get_temp(stwuct wadeon_device *wdev);
int tn_get_temp(stwuct wadeon_device *wdev);
int cypwess_dpm_init(stwuct wadeon_device *wdev);
void cypwess_dpm_setup_asic(stwuct wadeon_device *wdev);
int cypwess_dpm_enabwe(stwuct wadeon_device *wdev);
void cypwess_dpm_disabwe(stwuct wadeon_device *wdev);
int cypwess_dpm_set_powew_state(stwuct wadeon_device *wdev);
void cypwess_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void cypwess_dpm_fini(stwuct wadeon_device *wdev);
boow cypwess_dpm_vbwank_too_showt(stwuct wadeon_device *wdev);
int btc_dpm_init(stwuct wadeon_device *wdev);
void btc_dpm_setup_asic(stwuct wadeon_device *wdev);
int btc_dpm_enabwe(stwuct wadeon_device *wdev);
void btc_dpm_disabwe(stwuct wadeon_device *wdev);
int btc_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
int btc_dpm_set_powew_state(stwuct wadeon_device *wdev);
void btc_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
void btc_dpm_fini(stwuct wadeon_device *wdev);
u32 btc_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 btc_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
boow btc_dpm_vbwank_too_showt(stwuct wadeon_device *wdev);
void btc_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						     stwuct seq_fiwe *m);
u32 btc_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 btc_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);
int sumo_dpm_init(stwuct wadeon_device *wdev);
int sumo_dpm_enabwe(stwuct wadeon_device *wdev);
int sumo_dpm_wate_enabwe(stwuct wadeon_device *wdev);
void sumo_dpm_disabwe(stwuct wadeon_device *wdev);
int sumo_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
int sumo_dpm_set_powew_state(stwuct wadeon_device *wdev);
void sumo_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
void sumo_dpm_setup_asic(stwuct wadeon_device *wdev);
void sumo_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void sumo_dpm_fini(stwuct wadeon_device *wdev);
u32 sumo_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 sumo_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void sumo_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				stwuct wadeon_ps *ps);
void sumo_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						      stwuct seq_fiwe *m);
int sumo_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				     enum wadeon_dpm_fowced_wevew wevew);
u32 sumo_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 sumo_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);
u16 sumo_dpm_get_cuwwent_vddc(stwuct wadeon_device *wdev);

/*
 * cayman
 */
void cayman_fence_wing_emit(stwuct wadeon_device *wdev,
			    stwuct wadeon_fence *fence);
void cayman_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev);
int cayman_init(stwuct wadeon_device *wdev);
void cayman_fini(stwuct wadeon_device *wdev);
int cayman_suspend(stwuct wadeon_device *wdev);
int cayman_wesume(stwuct wadeon_device *wdev);
int cayman_asic_weset(stwuct wadeon_device *wdev, boow hawd);
void cayman_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
int cayman_vm_init(stwuct wadeon_device *wdev);
void cayman_vm_fini(stwuct wadeon_device *wdev);
void cayman_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		     unsigned vm_id, uint64_t pd_addw);
uint32_t cayman_vm_page_fwags(stwuct wadeon_device *wdev, uint32_t fwags);
int evewgween_ib_pawse(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
int evewgween_dma_ib_pawse(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
void cayman_dma_wing_ib_execute(stwuct wadeon_device *wdev,
				stwuct wadeon_ib *ib);
boow cayman_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
boow cayman_dma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);

void cayman_dma_vm_copy_pages(stwuct wadeon_device *wdev,
			      stwuct wadeon_ib *ib,
			      uint64_t pe, uint64_t swc,
			      unsigned count);
void cayman_dma_vm_wwite_pages(stwuct wadeon_device *wdev,
			       stwuct wadeon_ib *ib,
			       uint64_t pe,
			       uint64_t addw, unsigned count,
			       uint32_t incw, uint32_t fwags);
void cayman_dma_vm_set_pages(stwuct wadeon_device *wdev,
			     stwuct wadeon_ib *ib,
			     uint64_t pe,
			     uint64_t addw, unsigned count,
			     uint32_t incw, uint32_t fwags);
void cayman_dma_vm_pad_ib(stwuct wadeon_ib *ib);

void cayman_dma_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
			 unsigned vm_id, uint64_t pd_addw);

u32 cayman_gfx_get_wptw(stwuct wadeon_device *wdev,
			stwuct wadeon_wing *wing);
u32 cayman_gfx_get_wptw(stwuct wadeon_device *wdev,
			stwuct wadeon_wing *wing);
void cayman_gfx_set_wptw(stwuct wadeon_device *wdev,
			 stwuct wadeon_wing *wing);
uint32_t cayman_dma_get_wptw(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing);
uint32_t cayman_dma_get_wptw(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing);
void cayman_dma_set_wptw(stwuct wadeon_device *wdev,
			 stwuct wadeon_wing *wing);
int cayman_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
				     u32 weg, u32 *vaw);

int ni_dpm_init(stwuct wadeon_device *wdev);
void ni_dpm_setup_asic(stwuct wadeon_device *wdev);
int ni_dpm_enabwe(stwuct wadeon_device *wdev);
void ni_dpm_disabwe(stwuct wadeon_device *wdev);
int ni_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
int ni_dpm_set_powew_state(stwuct wadeon_device *wdev);
void ni_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
void ni_dpm_fini(stwuct wadeon_device *wdev);
u32 ni_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 ni_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void ni_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *ps);
void ni_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						    stwuct seq_fiwe *m);
int ni_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				   enum wadeon_dpm_fowced_wevew wevew);
boow ni_dpm_vbwank_too_showt(stwuct wadeon_device *wdev);
u32 ni_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 ni_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);
int twinity_dpm_init(stwuct wadeon_device *wdev);
int twinity_dpm_enabwe(stwuct wadeon_device *wdev);
int twinity_dpm_wate_enabwe(stwuct wadeon_device *wdev);
void twinity_dpm_disabwe(stwuct wadeon_device *wdev);
int twinity_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
int twinity_dpm_set_powew_state(stwuct wadeon_device *wdev);
void twinity_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
void twinity_dpm_setup_asic(stwuct wadeon_device *wdev);
void twinity_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void twinity_dpm_fini(stwuct wadeon_device *wdev);
u32 twinity_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 twinity_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void twinity_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
				   stwuct wadeon_ps *ps);
void twinity_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
							 stwuct seq_fiwe *m);
int twinity_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
					enum wadeon_dpm_fowced_wevew wevew);
void twinity_dpm_enabwe_bapm(stwuct wadeon_device *wdev, boow enabwe);
u32 twinity_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 twinity_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);
int tn_set_vce_cwocks(stwuct wadeon_device *wdev, u32 evcwk, u32 eccwk);

/* DCE6 - SI */
void dce6_bandwidth_update(stwuct wadeon_device *wdev);
void dce6_audio_fini(stwuct wadeon_device *wdev);

/*
 * si
 */
void si_fence_wing_emit(stwuct wadeon_device *wdev,
			stwuct wadeon_fence *fence);
void si_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev);
int si_init(stwuct wadeon_device *wdev);
void si_fini(stwuct wadeon_device *wdev);
int si_suspend(stwuct wadeon_device *wdev);
int si_wesume(stwuct wadeon_device *wdev);
boow si_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
boow si_dma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
int si_asic_weset(stwuct wadeon_device *wdev, boow hawd);
void si_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
int si_iwq_set(stwuct wadeon_device *wdev);
int si_iwq_pwocess(stwuct wadeon_device *wdev);
int si_vm_init(stwuct wadeon_device *wdev);
void si_vm_fini(stwuct wadeon_device *wdev);
void si_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		 unsigned vm_id, uint64_t pd_addw);
int si_ib_pawse(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
stwuct wadeon_fence *si_copy_dma(stwuct wadeon_device *wdev,
				 uint64_t swc_offset, uint64_t dst_offset,
				 unsigned num_gpu_pages,
				 stwuct dma_wesv *wesv);

void si_dma_vm_copy_pages(stwuct wadeon_device *wdev,
			  stwuct wadeon_ib *ib,
			  uint64_t pe, uint64_t swc,
			  unsigned count);
void si_dma_vm_wwite_pages(stwuct wadeon_device *wdev,
			   stwuct wadeon_ib *ib,
			   uint64_t pe,
			   uint64_t addw, unsigned count,
			   uint32_t incw, uint32_t fwags);
void si_dma_vm_set_pages(stwuct wadeon_device *wdev,
			 stwuct wadeon_ib *ib,
			 uint64_t pe,
			 uint64_t addw, unsigned count,
			 uint32_t incw, uint32_t fwags);

void si_dma_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		     unsigned vm_id, uint64_t pd_addw);
u32 si_get_xcwk(stwuct wadeon_device *wdev);
uint64_t si_get_gpu_cwock_countew(stwuct wadeon_device *wdev);
int si_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk);
int si_set_vce_cwocks(stwuct wadeon_device *wdev, u32 evcwk, u32 eccwk);
int si_get_temp(stwuct wadeon_device *wdev);
int si_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
				 u32 weg, u32 *vaw);
int si_dpm_init(stwuct wadeon_device *wdev);
void si_dpm_setup_asic(stwuct wadeon_device *wdev);
int si_dpm_enabwe(stwuct wadeon_device *wdev);
int si_dpm_wate_enabwe(stwuct wadeon_device *wdev);
void si_dpm_disabwe(stwuct wadeon_device *wdev);
int si_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
int si_dpm_set_powew_state(stwuct wadeon_device *wdev);
void si_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
void si_dpm_fini(stwuct wadeon_device *wdev);
void si_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void si_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						    stwuct seq_fiwe *m);
int si_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				   enum wadeon_dpm_fowced_wevew wevew);
int si_fan_ctww_get_fan_speed_pewcent(stwuct wadeon_device *wdev,
						 u32 *speed);
int si_fan_ctww_set_fan_speed_pewcent(stwuct wadeon_device *wdev,
						 u32 speed);
u32 si_fan_ctww_get_mode(stwuct wadeon_device *wdev);
void si_fan_ctww_set_mode(stwuct wadeon_device *wdev, u32 mode);
u32 si_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 si_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);

/* DCE8 - CIK */
void dce8_bandwidth_update(stwuct wadeon_device *wdev);

/*
 * cik
 */
uint64_t cik_get_gpu_cwock_countew(stwuct wadeon_device *wdev);
u32 cik_get_xcwk(stwuct wadeon_device *wdev);
uint32_t cik_pciep_wweg(stwuct wadeon_device *wdev, uint32_t weg);
void cik_pciep_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v);
int cik_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk);
int cik_set_vce_cwocks(stwuct wadeon_device *wdev, u32 evcwk, u32 eccwk);
void cik_sdma_fence_wing_emit(stwuct wadeon_device *wdev,
			      stwuct wadeon_fence *fence);
boow cik_sdma_semaphowe_wing_emit(stwuct wadeon_device *wdev,
				  stwuct wadeon_wing *wing,
				  stwuct wadeon_semaphowe *semaphowe,
				  boow emit_wait);
void cik_sdma_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
stwuct wadeon_fence *cik_copy_dma(stwuct wadeon_device *wdev,
				  uint64_t swc_offset, uint64_t dst_offset,
				  unsigned num_gpu_pages,
				  stwuct dma_wesv *wesv);
stwuct wadeon_fence *cik_copy_cpdma(stwuct wadeon_device *wdev,
				    uint64_t swc_offset, uint64_t dst_offset,
				    unsigned num_gpu_pages,
				    stwuct dma_wesv *wesv);
int cik_sdma_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
int cik_sdma_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
boow cik_sdma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
void cik_fence_gfx_wing_emit(stwuct wadeon_device *wdev,
			     stwuct wadeon_fence *fence);
void cik_fence_compute_wing_emit(stwuct wadeon_device *wdev,
				 stwuct wadeon_fence *fence);
boow cik_semaphowe_wing_emit(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *cp,
			     stwuct wadeon_semaphowe *semaphowe,
			     boow emit_wait);
void cik_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev);
int cik_init(stwuct wadeon_device *wdev);
void cik_fini(stwuct wadeon_device *wdev);
int cik_suspend(stwuct wadeon_device *wdev);
int cik_wesume(stwuct wadeon_device *wdev);
boow cik_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *cp);
int cik_asic_weset(stwuct wadeon_device *wdev, boow hawd);
void cik_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
int cik_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
int cik_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
int cik_iwq_set(stwuct wadeon_device *wdev);
int cik_iwq_pwocess(stwuct wadeon_device *wdev);
int cik_vm_init(stwuct wadeon_device *wdev);
void cik_vm_fini(stwuct wadeon_device *wdev);
void cik_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		  unsigned vm_id, uint64_t pd_addw);

void cik_sdma_vm_copy_pages(stwuct wadeon_device *wdev,
			    stwuct wadeon_ib *ib,
			    uint64_t pe, uint64_t swc,
			    unsigned count);
void cik_sdma_vm_wwite_pages(stwuct wadeon_device *wdev,
			     stwuct wadeon_ib *ib,
			     uint64_t pe,
			     uint64_t addw, unsigned count,
			     uint32_t incw, uint32_t fwags);
void cik_sdma_vm_set_pages(stwuct wadeon_device *wdev,
			   stwuct wadeon_ib *ib,
			   uint64_t pe,
			   uint64_t addw, unsigned count,
			   uint32_t incw, uint32_t fwags);
void cik_sdma_vm_pad_ib(stwuct wadeon_ib *ib);

void cik_dma_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		      unsigned vm_id, uint64_t pd_addw);
int cik_ib_pawse(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);
u32 cik_gfx_get_wptw(stwuct wadeon_device *wdev,
		     stwuct wadeon_wing *wing);
u32 cik_gfx_get_wptw(stwuct wadeon_device *wdev,
		     stwuct wadeon_wing *wing);
void cik_gfx_set_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing);
u32 cik_compute_get_wptw(stwuct wadeon_device *wdev,
			 stwuct wadeon_wing *wing);
u32 cik_compute_get_wptw(stwuct wadeon_device *wdev,
			 stwuct wadeon_wing *wing);
void cik_compute_set_wptw(stwuct wadeon_device *wdev,
			  stwuct wadeon_wing *wing);
u32 cik_sdma_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing);
u32 cik_sdma_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing);
void cik_sdma_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing);
int ci_get_temp(stwuct wadeon_device *wdev);
int kv_get_temp(stwuct wadeon_device *wdev);
int cik_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
				  u32 weg, u32 *vaw);

int ci_dpm_init(stwuct wadeon_device *wdev);
int ci_dpm_enabwe(stwuct wadeon_device *wdev);
int ci_dpm_wate_enabwe(stwuct wadeon_device *wdev);
void ci_dpm_disabwe(stwuct wadeon_device *wdev);
int ci_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
int ci_dpm_set_powew_state(stwuct wadeon_device *wdev);
void ci_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
void ci_dpm_setup_asic(stwuct wadeon_device *wdev);
void ci_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void ci_dpm_fini(stwuct wadeon_device *wdev);
u32 ci_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 ci_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void ci_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *ps);
void ci_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						    stwuct seq_fiwe *m);
int ci_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				   enum wadeon_dpm_fowced_wevew wevew);
boow ci_dpm_vbwank_too_showt(stwuct wadeon_device *wdev);
void ci_dpm_powewgate_uvd(stwuct wadeon_device *wdev, boow gate);
u32 ci_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 ci_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);

int ci_fan_ctww_get_fan_speed_pewcent(stwuct wadeon_device *wdev,
						 u32 *speed);
int ci_fan_ctww_set_fan_speed_pewcent(stwuct wadeon_device *wdev,
						 u32 speed);
u32 ci_fan_ctww_get_mode(stwuct wadeon_device *wdev);
void ci_fan_ctww_set_mode(stwuct wadeon_device *wdev, u32 mode);

int kv_dpm_init(stwuct wadeon_device *wdev);
int kv_dpm_enabwe(stwuct wadeon_device *wdev);
int kv_dpm_wate_enabwe(stwuct wadeon_device *wdev);
void kv_dpm_disabwe(stwuct wadeon_device *wdev);
int kv_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev);
int kv_dpm_set_powew_state(stwuct wadeon_device *wdev);
void kv_dpm_post_set_powew_state(stwuct wadeon_device *wdev);
void kv_dpm_setup_asic(stwuct wadeon_device *wdev);
void kv_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev);
void kv_dpm_fini(stwuct wadeon_device *wdev);
u32 kv_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow);
u32 kv_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow);
void kv_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *ps);
void kv_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						    stwuct seq_fiwe *m);
int kv_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				   enum wadeon_dpm_fowced_wevew wevew);
void kv_dpm_powewgate_uvd(stwuct wadeon_device *wdev, boow gate);
void kv_dpm_enabwe_bapm(stwuct wadeon_device *wdev, boow enabwe);
u32 kv_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev);
u32 kv_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev);

/* uvd v1.0 */
uint32_t uvd_v1_0_get_wptw(stwuct wadeon_device *wdev,
                           stwuct wadeon_wing *wing);
uint32_t uvd_v1_0_get_wptw(stwuct wadeon_device *wdev,
                           stwuct wadeon_wing *wing);
void uvd_v1_0_set_wptw(stwuct wadeon_device *wdev,
                       stwuct wadeon_wing *wing);
int uvd_v1_0_wesume(stwuct wadeon_device *wdev);

int uvd_v1_0_init(stwuct wadeon_device *wdev);
void uvd_v1_0_fini(stwuct wadeon_device *wdev);
int uvd_v1_0_stawt(stwuct wadeon_device *wdev);
void uvd_v1_0_stop(stwuct wadeon_device *wdev);

int uvd_v1_0_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
void uvd_v1_0_fence_emit(stwuct wadeon_device *wdev,
			 stwuct wadeon_fence *fence);
int uvd_v1_0_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);
boow uvd_v1_0_semaphowe_emit(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing,
			     stwuct wadeon_semaphowe *semaphowe,
			     boow emit_wait);
void uvd_v1_0_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib);

/* uvd v2.2 */
int uvd_v2_2_wesume(stwuct wadeon_device *wdev);
void uvd_v2_2_fence_emit(stwuct wadeon_device *wdev,
			 stwuct wadeon_fence *fence);
boow uvd_v2_2_semaphowe_emit(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing,
			     stwuct wadeon_semaphowe *semaphowe,
			     boow emit_wait);

/* uvd v3.1 */
boow uvd_v3_1_semaphowe_emit(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing,
			     stwuct wadeon_semaphowe *semaphowe,
			     boow emit_wait);

/* uvd v4.2 */
int uvd_v4_2_wesume(stwuct wadeon_device *wdev);

/* vce v1.0 */
uint32_t vce_v1_0_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing);
uint32_t vce_v1_0_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing);
void vce_v1_0_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing);
int vce_v1_0_woad_fw(stwuct wadeon_device *wdev, uint32_t *data);
unsigned vce_v1_0_bo_size(stwuct wadeon_device *wdev);
int vce_v1_0_wesume(stwuct wadeon_device *wdev);
int vce_v1_0_init(stwuct wadeon_device *wdev);
int vce_v1_0_stawt(stwuct wadeon_device *wdev);

/* vce v2.0 */
unsigned vce_v2_0_bo_size(stwuct wadeon_device *wdev);
int vce_v2_0_wesume(stwuct wadeon_device *wdev);

#endif
