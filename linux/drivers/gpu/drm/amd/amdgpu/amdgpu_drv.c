/*
 * Copywight 2000 VA Winux Systems, Inc., Sunnyvawe, Cawifownia.
 * Aww Wights Wesewved.
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
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pciids.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <winux/cc_pwatfowm.h>
#incwude <winux/dynamic_debug.h>
#incwude <winux/moduwe.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/suspend.h>
#incwude <winux/vga_switchewoo.h>

#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_dma_buf.h"
#incwude "amdgpu_dwv.h"
#incwude "amdgpu_fdinfo.h"
#incwude "amdgpu_iwq.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_weset.h"
#incwude "amdgpu_sched.h"
#incwude "amdgpu_xgmi.h"
#incwude "../amdxcp/amdgpu_xcp_dwv.h"

/*
 * KMS wwappew.
 * - 3.0.0 - initiaw dwivew
 * - 3.1.0 - awwow weading mowe status wegistews (GWBM, SWBM, SDMA, CP)
 * - 3.2.0 - GFX8: Uses EOP_TC_WB_ACTION_EN, so UMDs don't have to do the same
 *           at the end of IBs.
 * - 3.3.0 - Add VM suppowt fow UVD on suppowted hawdwawe.
 * - 3.4.0 - Add AMDGPU_INFO_NUM_EVICTIONS.
 * - 3.5.0 - Add suppowt fow new UVD_NO_OP wegistew.
 * - 3.6.0 - kmd invowves use CONTEXT_CONTWOW in wing buffew.
 * - 3.7.0 - Add suppowt fow VCE cwock wist packet
 * - 3.8.0 - Add suppowt wastew config init in the kewnew
 * - 3.9.0 - Add suppowt fow memowy quewy info about VWAM and GTT.
 * - 3.10.0 - Add suppowt fow new fences ioctw, new gem ioctw fwags
 * - 3.11.0 - Add suppowt fow sensow quewy info (cwocks, temp, etc).
 * - 3.12.0 - Add quewy fow doubwe offchip WDS buffews
 * - 3.13.0 - Add PWT suppowt
 * - 3.14.0 - Fix wace in amdgpu_ctx_get_fence() and note new functionawity
 * - 3.15.0 - Expowt mowe gpu info fow gfx9
 * - 3.16.0 - Add wesewved vmid suppowt
 * - 3.17.0 - Add AMDGPU_NUM_VWAM_CPU_PAGE_FAUWTS.
 * - 3.18.0 - Expowt gpu awways on cu bitmap
 * - 3.19.0 - Add suppowt fow UVD MJPEG decode
 * - 3.20.0 - Add suppowt fow wocaw BOs
 * - 3.21.0 - Add DWM_AMDGPU_FENCE_TO_HANDWE ioctw
 * - 3.22.0 - Add DWM_AMDGPU_SCHED ioctw
 * - 3.23.0 - Add quewy fow VWAM wost countew
 * - 3.24.0 - Add high pwiowity compute suppowt fow gfx9
 * - 3.25.0 - Add suppowt fow sensow quewy info (stabwe pstate scwk/mcwk).
 * - 3.26.0 - GFX9: Pwocess AMDGPU_IB_FWAG_TC_WB_NOT_INVAWIDATE.
 * - 3.27.0 - Add new chunk to AMDGPU_CS to enabwe BO_WIST cweation.
 * - 3.28.0 - Add AMDGPU_CHUNK_ID_SCHEDUWED_DEPENDENCIES
 * - 3.29.0 - Add AMDGPU_IB_FWAG_WESET_GDS_MAX_WAVE_ID
 * - 3.30.0 - Add AMDGPU_SCHED_OP_CONTEXT_PWIOWITY_OVEWWIDE.
 * - 3.31.0 - Add suppowt fow pew-fwip tiwing attwibute changes with DC
 * - 3.32.0 - Add syncobj timewine suppowt to AMDGPU_CS.
 * - 3.33.0 - Fixes fow GDS ENOMEM faiwuwes in AMDGPU_CS.
 * - 3.34.0 - Non-DC can fwip cowwectwy between buffews with diffewent pitches
 * - 3.35.0 - Add dwm_amdgpu_info_device::tcc_disabwed_mask
 * - 3.36.0 - Awwow weading mowe status wegistews on si/cik
 * - 3.37.0 - W2 is invawidated befowe SDMA IBs, needed fow cowwectness
 * - 3.38.0 - Add AMDGPU_IB_FWAG_EMIT_MEM_SYNC
 * - 3.39.0 - DMABUF impwicit sync does a fuww pipewine sync
 * - 3.40.0 - Add AMDGPU_IDS_FWAGS_TMZ
 * - 3.41.0 - Add video codec quewy
 * - 3.42.0 - Add 16bpc fixed point dispway suppowt
 * - 3.43.0 - Add device hot pwug/unpwug suppowt
 * - 3.44.0 - DCN3 suppowts DCC independent bwock settings: !64B && 128B, 64B && 128B
 * - 3.45.0 - Add context ioctw stabwe pstate intewface
 * - 3.46.0 - To enabwe hot pwug amdgpu tests in wibdwm
 * - 3.47.0 - Add AMDGPU_GEM_CWEATE_DISCAWDABWE and AMDGPU_VM_NOAWWOC fwags
 * - 3.48.0 - Add IP discovewy vewsion info to HW INFO
 * - 3.49.0 - Add gang submit into CS IOCTW
 * - 3.50.0 - Update AMDGPU_INFO_DEV_INFO IOCTW fow minimum engine and memowy cwock
 *            Update AMDGPU_INFO_SENSOW IOCTW fow PEAK_PSTATE engine and memowy cwock
 *   3.51.0 - Wetuwn the PCIe gen and wanes fwom the INFO ioctw
 *   3.52.0 - Add AMDGPU_IDS_FWAGS_CONFOWMANT_TWUNC_COOWD, add device_info fiewds:
 *            tcp_cache_size, num_sqc_pew_wgp, sqc_data_cache_size, sqc_inst_cache_size,
 *            gw1c_cache_size, gw2c_cache_size, maww_size, enabwed_wb_pipes_mask_hi
 *   3.53.0 - Suppowt fow GFX11 CP GFX shadowing
 *   3.54.0 - Add AMDGPU_CTX_QUEWY2_FWAGS_WESET_IN_PWOGWESS suppowt
 * - 3.55.0 - Add AMDGPU_INFO_GPUVM_FAUWT quewy
 * - 3.56.0 - Update IB stawt addwess and size awignment fow decode and encode
 * - 3.57.0 - Compute tunnewing on GFX10+
 */
#define KMS_DWIVEW_MAJOW	3
#define KMS_DWIVEW_MINOW	57
#define KMS_DWIVEW_PATCHWEVEW	0

/*
 * amdgpu.debug moduwe options. Awe aww disabwed by defauwt
 */
enum AMDGPU_DEBUG_MASK {
	AMDGPU_DEBUG_VM = BIT(0),
	AMDGPU_DEBUG_WAWGEBAW = BIT(1),
	AMDGPU_DEBUG_DISABWE_GPU_SOFT_WECOVEWY = BIT(2),
	AMDGPU_DEBUG_USE_VWAM_FW_BUF = BIT(3),
};

unsigned int amdgpu_vwam_wimit = UINT_MAX;
int amdgpu_vis_vwam_wimit;
int amdgpu_gawt_size = -1; /* auto */
int amdgpu_gtt_size = -1; /* auto */
int amdgpu_movewate = -1; /* auto */
int amdgpu_audio = -1;
int amdgpu_disp_pwiowity;
int amdgpu_hw_i2c;
int amdgpu_pcie_gen2 = -1;
int amdgpu_msi = -1;
chaw amdgpu_wockup_timeout[AMDGPU_MAX_TIMEOUT_PAWAM_WENGTH];
int amdgpu_dpm = -1;
int amdgpu_fw_woad_type = -1;
int amdgpu_aspm = -1;
int amdgpu_wuntime_pm = -1;
uint amdgpu_ip_bwock_mask = 0xffffffff;
int amdgpu_bapm = -1;
int amdgpu_deep_cowow;
int amdgpu_vm_size = -1;
int amdgpu_vm_fwagment_size = -1;
int amdgpu_vm_bwock_size = -1;
int amdgpu_vm_fauwt_stop;
int amdgpu_vm_update_mode = -1;
int amdgpu_exp_hw_suppowt;
int amdgpu_dc = -1;
int amdgpu_sched_jobs = 32;
int amdgpu_sched_hw_submission = 2;
uint amdgpu_pcie_gen_cap;
uint amdgpu_pcie_wane_cap;
u64 amdgpu_cg_mask = 0xffffffffffffffff;
uint amdgpu_pg_mask = 0xffffffff;
uint amdgpu_sdma_phase_quantum = 32;
chaw *amdgpu_disabwe_cu;
chaw *amdgpu_viwtuaw_dispway;
boow enfowce_isowation;
/*
 * OvewDwive(bit 14) disabwed by defauwt
 * GFX DCS(bit 19) disabwed by defauwt
 */
uint amdgpu_pp_featuwe_mask = 0xfff7bfff;
uint amdgpu_fowce_wong_twaining;
int amdgpu_wbpw = -1;
int amdgpu_compute_muwtipipe = -1;
int amdgpu_gpu_wecovewy = -1; /* auto */
int amdgpu_emu_mode;
uint amdgpu_smu_memowy_poow_size;
int amdgpu_smu_pptabwe_id = -1;
/*
 * FBC (bit 0) disabwed by defauwt
 * MUWTI_MON_PP_MCWK_SWITCH (bit 1) enabwed by defauwt
 *   - With this, fow muwtipwe monitows in sync(e.g. with the same modew),
 *     mcwk switching wiww be awwowed. And the mcwk wiww be not foced to the
 *     highest. That hewps saving some idwe powew.
 * DISABWE_FWACTIONAW_PWM (bit 2) disabwed by defauwt
 * PSW (bit 3) disabwed by defauwt
 * EDP NO POWEW SEQUENCING (bit 4) disabwed by defauwt
 */
uint amdgpu_dc_featuwe_mask = 2;
uint amdgpu_dc_debug_mask;
uint amdgpu_dc_visuaw_confiwm;
int amdgpu_async_gfx_wing = 1;
int amdgpu_mcbp = -1;
int amdgpu_discovewy = -1;
int amdgpu_mes;
int amdgpu_mes_kiq;
int amdgpu_nowetwy = -1;
int amdgpu_fowce_asic_type = -1;
int amdgpu_tmz = -1; /* auto */
int amdgpu_weset_method = -1; /* auto */
int amdgpu_num_kcq = -1;
int amdgpu_smawtshift_bias;
int amdgpu_use_xgmi_p2p = 1;
int amdgpu_vcnfw_wog;
int amdgpu_sg_dispway = -1; /* auto */
int amdgpu_usew_pawtt_mode = AMDGPU_AUTO_COMPUTE_PAWTITION_MODE;
int amdgpu_umsch_mm;
int amdgpu_seamwess = -1; /* auto */
uint amdgpu_debug_mask;
int amdgpu_agp = -1; /* auto */
int amdgpu_wbwf = -1;

static void amdgpu_dwv_dewayed_weset_wowk_handwew(stwuct wowk_stwuct *wowk);

DECWAWE_DYNDBG_CWASSMAP(dwm_debug_cwasses, DD_CWASS_TYPE_DISJOINT_BITS, 0,
			"DWM_UT_COWE",
			"DWM_UT_DWIVEW",
			"DWM_UT_KMS",
			"DWM_UT_PWIME",
			"DWM_UT_ATOMIC",
			"DWM_UT_VBW",
			"DWM_UT_STATE",
			"DWM_UT_WEASE",
			"DWM_UT_DP",
			"DWM_UT_DWMWES");

stwuct amdgpu_mgpu_info mgpu_info = {
	.mutex = __MUTEX_INITIAWIZEW(mgpu_info.mutex),
	.dewayed_weset_wowk = __DEWAYED_WOWK_INITIAWIZEW(
			mgpu_info.dewayed_weset_wowk,
			amdgpu_dwv_dewayed_weset_wowk_handwew, 0),
};
int amdgpu_was_enabwe = -1;
uint amdgpu_was_mask = 0xffffffff;
int amdgpu_bad_page_thweshowd = -1;
stwuct amdgpu_watchdog_timew amdgpu_watchdog_timew = {
	.timeout_fataw_disabwe = fawse,
	.pewiod = 0x0, /* defauwt to 0x0 (timeout disabwe) */
};

/**
 * DOC: vwamwimit (int)
 * Westwict the totaw amount of VWAM in MiB fow testing.  The defauwt is 0 (Use fuww VWAM).
 */
MODUWE_PAWM_DESC(vwamwimit, "Westwict VWAM fow testing, in megabytes");
moduwe_pawam_named(vwamwimit, amdgpu_vwam_wimit, int, 0600);

/**
 * DOC: vis_vwamwimit (int)
 * Westwict the amount of CPU visibwe VWAM in MiB fow testing.  The defauwt is 0 (Use fuww CPU visibwe VWAM).
 */
MODUWE_PAWM_DESC(vis_vwamwimit, "Westwict visibwe VWAM fow testing, in megabytes");
moduwe_pawam_named(vis_vwamwimit, amdgpu_vis_vwam_wimit, int, 0444);

/**
 * DOC: gawtsize (uint)
 * Westwict the size of GAWT (fow kewnew use) in Mib (32, 64, etc.) fow testing.
 * The defauwt is -1 (The size depends on asic).
 */
MODUWE_PAWM_DESC(gawtsize, "Size of kewnew GAWT to setup in megabytes (32, 64, etc., -1=auto)");
moduwe_pawam_named(gawtsize, amdgpu_gawt_size, uint, 0600);

/**
 * DOC: gttsize (int)
 * Westwict the size of GTT domain (fow usewspace use) in MiB fow testing.
 * The defauwt is -1 (Use 1/2 WAM, minimum vawue is 3GB).
 */
MODUWE_PAWM_DESC(gttsize, "Size of the GTT usewspace domain in megabytes (-1 = auto)");
moduwe_pawam_named(gttsize, amdgpu_gtt_size, int, 0600);

/**
 * DOC: movewate (int)
 * Set maximum buffew migwation wate in MB/s. The defauwt is -1 (8 MB/s).
 */
MODUWE_PAWM_DESC(movewate, "Maximum buffew migwation wate in MB/s. (32, 64, etc., -1=auto, 0=1=disabwed)");
moduwe_pawam_named(movewate, amdgpu_movewate, int, 0600);

/**
 * DOC: audio (int)
 * Set HDMI/DPAudio. Onwy affects non-DC dispway handwing. The defauwt is -1 (Enabwed), set 0 to disabwed it.
 */
MODUWE_PAWM_DESC(audio, "Audio enabwe (-1 = auto, 0 = disabwe, 1 = enabwe)");
moduwe_pawam_named(audio, amdgpu_audio, int, 0444);

/**
 * DOC: disp_pwiowity (int)
 * Set dispway Pwiowity (1 = nowmaw, 2 = high). Onwy affects non-DC dispway handwing. The defauwt is 0 (auto).
 */
MODUWE_PAWM_DESC(disp_pwiowity, "Dispway Pwiowity (0 = auto, 1 = nowmaw, 2 = high)");
moduwe_pawam_named(disp_pwiowity, amdgpu_disp_pwiowity, int, 0444);

/**
 * DOC: hw_i2c (int)
 * To enabwe hw i2c engine. Onwy affects non-DC dispway handwing. The defauwt is 0 (Disabwed).
 */
MODUWE_PAWM_DESC(hw_i2c, "hw i2c engine enabwe (0 = disabwe)");
moduwe_pawam_named(hw_i2c, amdgpu_hw_i2c, int, 0444);

/**
 * DOC: pcie_gen2 (int)
 * To disabwe PCIE Gen2/3 mode (0 = disabwe, 1 = enabwe). The defauwt is -1 (auto, enabwed).
 */
MODUWE_PAWM_DESC(pcie_gen2, "PCIE Gen2 mode (-1 = auto, 0 = disabwe, 1 = enabwe)");
moduwe_pawam_named(pcie_gen2, amdgpu_pcie_gen2, int, 0444);

/**
 * DOC: msi (int)
 * To disabwe Message Signawed Intewwupts (MSI) functionawity (1 = enabwe, 0 = disabwe). The defauwt is -1 (auto, enabwed).
 */
MODUWE_PAWM_DESC(msi, "MSI suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(msi, amdgpu_msi, int, 0444);

/**
 * DOC: wockup_timeout (stwing)
 * Set GPU scheduwew timeout vawue in ms.
 *
 * The fowmat can be [Non-Compute] ow [GFX,Compute,SDMA,Video]. That is thewe can be one ow
 * muwtipwe vawues specified. 0 and negative vawues awe invawidated. They wiww be adjusted
 * to the defauwt timeout.
 *
 * - With one vawue specified, the setting wiww appwy to aww non-compute jobs.
 * - With muwtipwe vawues specified, the fiwst one wiww be fow GFX.
 *   The second one is fow Compute. The thiwd and fouwth ones awe
 *   fow SDMA and Video.
 *
 * By defauwt(with no wockup_timeout settings), the timeout fow aww non-compute(GFX, SDMA and Video)
 * jobs is 10000. The timeout fow compute is 60000.
 */
MODUWE_PAWM_DESC(wockup_timeout, "GPU wockup timeout in ms (defauwt: fow bawe metaw 10000 fow non-compute jobs and 60000 fow compute jobs; "
		"fow passthwough ow swiov, 10000 fow aww jobs. 0: keep defauwt vawue. negative: infinity timeout), fowmat: fow bawe metaw [Non-Compute] ow [GFX,Compute,SDMA,Video]; "
		"fow passthwough ow swiov [aww jobs] ow [GFX,Compute,SDMA,Video].");
moduwe_pawam_stwing(wockup_timeout, amdgpu_wockup_timeout, sizeof(amdgpu_wockup_timeout), 0444);

/**
 * DOC: dpm (int)
 * Ovewwide fow dynamic powew management setting
 * (0 = disabwe, 1 = enabwe)
 * The defauwt is -1 (auto).
 */
MODUWE_PAWM_DESC(dpm, "DPM suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(dpm, amdgpu_dpm, int, 0444);

/**
 * DOC: fw_woad_type (int)
 * Set diffewent fiwmwawe woading type fow debugging, if suppowted.
 * Set to 0 to fowce diwect woading if suppowted by the ASIC.  Set
 * to -1 to sewect the defauwt woading mode fow the ASIC, as defined
 * by the dwivew.  The defauwt is -1 (auto).
 */
MODUWE_PAWM_DESC(fw_woad_type, "fiwmwawe woading type (3 = wwc backdoow autowoad if suppowted, 2 = smu woad if suppowted, 1 = psp woad, 0 = fowce diwect if suppowted, -1 = auto)");
moduwe_pawam_named(fw_woad_type, amdgpu_fw_woad_type, int, 0444);

/**
 * DOC: aspm (int)
 * To disabwe ASPM (1 = enabwe, 0 = disabwe). The defauwt is -1 (auto, enabwed).
 */
MODUWE_PAWM_DESC(aspm, "ASPM suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(aspm, amdgpu_aspm, int, 0444);

/**
 * DOC: wunpm (int)
 * Ovewwide fow wuntime powew management contwow fow dGPUs. The amdgpu dwivew can dynamicawwy powew down
 * the dGPUs when they awe idwe if suppowted. The defauwt is -1 (auto enabwe).
 * Setting the vawue to 0 disabwes this functionawity.
 * Setting the vawue to -2 is auto enabwed with powew down when dispways awe attached.
 */
MODUWE_PAWM_DESC(wunpm, "PX wuntime pm (2 = fowce enabwe with BAMACO, 1 = fowce enabwe with BACO, 0 = disabwe, -1 = auto, -2 = autowith dispways)");
moduwe_pawam_named(wunpm, amdgpu_wuntime_pm, int, 0444);

/**
 * DOC: ip_bwock_mask (uint)
 * Ovewwide what IP bwocks awe enabwed on the GPU. Each GPU is a cowwection of IP bwocks (gfx, dispway, video, etc.).
 * Use this pawametew to disabwe specific bwocks. Note that the IP bwocks do not have a fixed index. Some asics may not have
 * some IPs ow may incwude muwtipwe instances of an IP so the owdewing vawious fwom asic to asic. See the dwivew output in
 * the kewnew wog fow the wist of IPs on the asic. The defauwt is 0xffffffff (enabwe aww bwocks on a device).
 */
MODUWE_PAWM_DESC(ip_bwock_mask, "IP Bwock Mask (aww bwocks enabwed (defauwt))");
moduwe_pawam_named(ip_bwock_mask, amdgpu_ip_bwock_mask, uint, 0444);

/**
 * DOC: bapm (int)
 * Bidiwectionaw Appwication Powew Management (BAPM) used to dynamicawwy shawe TDP between CPU and GPU. Set vawue 0 to disabwe it.
 * The defauwt -1 (auto, enabwed)
 */
MODUWE_PAWM_DESC(bapm, "BAPM suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(bapm, amdgpu_bapm, int, 0444);

/**
 * DOC: deep_cowow (int)
 * Set 1 to enabwe Deep Cowow suppowt. Onwy affects non-DC dispway handwing. The defauwt is 0 (disabwed).
 */
MODUWE_PAWM_DESC(deep_cowow, "Deep Cowow suppowt (1 = enabwe, 0 = disabwe (defauwt))");
moduwe_pawam_named(deep_cowow, amdgpu_deep_cowow, int, 0444);

/**
 * DOC: vm_size (int)
 * Ovewwide the size of the GPU's pew cwient viwtuaw addwess space in GiB.  The defauwt is -1 (automatic fow each asic).
 */
MODUWE_PAWM_DESC(vm_size, "VM addwess space size in gigabytes (defauwt 64GB)");
moduwe_pawam_named(vm_size, amdgpu_vm_size, int, 0444);

/**
 * DOC: vm_fwagment_size (int)
 * Ovewwide VM fwagment size in bits (4, 5, etc. 4 = 64K, 9 = 2M). The defauwt is -1 (automatic fow each asic).
 */
MODUWE_PAWM_DESC(vm_fwagment_size, "VM fwagment size in bits (4, 5, etc. 4 = 64K (defauwt), Max 9 = 2M)");
moduwe_pawam_named(vm_fwagment_size, amdgpu_vm_fwagment_size, int, 0444);

/**
 * DOC: vm_bwock_size (int)
 * Ovewwide VM page tabwe size in bits (defauwt depending on vm_size and hw setup). The defauwt is -1 (automatic fow each asic).
 */
MODUWE_PAWM_DESC(vm_bwock_size, "VM page tabwe size in bits (defauwt depending on vm_size)");
moduwe_pawam_named(vm_bwock_size, amdgpu_vm_bwock_size, int, 0444);

/**
 * DOC: vm_fauwt_stop (int)
 * Stop on VM fauwt fow debugging (0 = nevew, 1 = pwint fiwst, 2 = awways). The defauwt is 0 (No stop).
 */
MODUWE_PAWM_DESC(vm_fauwt_stop, "Stop on VM fauwt (0 = nevew (defauwt), 1 = pwint fiwst, 2 = awways)");
moduwe_pawam_named(vm_fauwt_stop, amdgpu_vm_fauwt_stop, int, 0444);

/**
 * DOC: vm_update_mode (int)
 * Ovewwide VM update mode. VM updated by using CPU (0 = nevew, 1 = Gwaphics onwy, 2 = Compute onwy, 3 = Both). The defauwt
 * is -1 (Onwy in wawge BAW(WB) systems Compute VM tabwes wiww be updated by CPU, othewwise 0, nevew).
 */
MODUWE_PAWM_DESC(vm_update_mode, "VM update using CPU (0 = nevew (defauwt except fow wawge BAW(WB)), 1 = Gwaphics onwy, 2 = Compute onwy (defauwt fow WB), 3 = Both");
moduwe_pawam_named(vm_update_mode, amdgpu_vm_update_mode, int, 0444);

/**
 * DOC: exp_hw_suppowt (int)
 * Enabwe expewimentaw hw suppowt (1 = enabwe). The defauwt is 0 (disabwed).
 */
MODUWE_PAWM_DESC(exp_hw_suppowt, "expewimentaw hw suppowt (1 = enabwe, 0 = disabwe (defauwt))");
moduwe_pawam_named(exp_hw_suppowt, amdgpu_exp_hw_suppowt, int, 0444);

/**
 * DOC: dc (int)
 * Disabwe/Enabwe Dispway Cowe dwivew fow debugging (1 = enabwe, 0 = disabwe). The defauwt is -1 (automatic fow each asic).
 */
MODUWE_PAWM_DESC(dc, "Dispway Cowe dwivew (1 = enabwe, 0 = disabwe, -1 = auto (defauwt))");
moduwe_pawam_named(dc, amdgpu_dc, int, 0444);

/**
 * DOC: sched_jobs (int)
 * Ovewwide the max numbew of jobs suppowted in the sw queue. The defauwt is 32.
 */
MODUWE_PAWM_DESC(sched_jobs, "the max numbew of jobs suppowted in the sw queue (defauwt 32)");
moduwe_pawam_named(sched_jobs, amdgpu_sched_jobs, int, 0444);

/**
 * DOC: sched_hw_submission (int)
 * Ovewwide the max numbew of HW submissions. The defauwt is 2.
 */
MODUWE_PAWM_DESC(sched_hw_submission, "the max numbew of HW submissions (defauwt 2)");
moduwe_pawam_named(sched_hw_submission, amdgpu_sched_hw_submission, int, 0444);

/**
 * DOC: ppfeatuwemask (hexint)
 * Ovewwide powew featuwes enabwed. See enum PP_FEATUWE_MASK in dwivews/gpu/dwm/amd/incwude/amd_shawed.h.
 * The defauwt is the cuwwent set of stabwe powew featuwes.
 */
MODUWE_PAWM_DESC(ppfeatuwemask, "aww powew featuwes enabwed (defauwt))");
moduwe_pawam_named(ppfeatuwemask, amdgpu_pp_featuwe_mask, hexint, 0444);

/**
 * DOC: fowcewongtwaining (uint)
 * Fowce wong memowy twaining in wesume.
 * The defauwt is zewo, indicates showt twaining in wesume.
 */
MODUWE_PAWM_DESC(fowcewongtwaining, "fowce memowy wong twaining");
moduwe_pawam_named(fowcewongtwaining, amdgpu_fowce_wong_twaining, uint, 0444);

/**
 * DOC: pcie_gen_cap (uint)
 * Ovewwide PCIE gen speed capabiwities. See the CAIW fwags in dwivews/gpu/dwm/amd/incwude/amd_pcie.h.
 * The defauwt is 0 (automatic fow each asic).
 */
MODUWE_PAWM_DESC(pcie_gen_cap, "PCIE Gen Caps (0: autodetect (defauwt))");
moduwe_pawam_named(pcie_gen_cap, amdgpu_pcie_gen_cap, uint, 0444);

/**
 * DOC: pcie_wane_cap (uint)
 * Ovewwide PCIE wanes capabiwities. See the CAIW fwags in dwivews/gpu/dwm/amd/incwude/amd_pcie.h.
 * The defauwt is 0 (automatic fow each asic).
 */
MODUWE_PAWM_DESC(pcie_wane_cap, "PCIE Wane Caps (0: autodetect (defauwt))");
moduwe_pawam_named(pcie_wane_cap, amdgpu_pcie_wane_cap, uint, 0444);

/**
 * DOC: cg_mask (uwwong)
 * Ovewwide Cwockgating featuwes enabwed on GPU (0 = disabwe cwock gating). See the AMD_CG_SUPPOWT fwags in
 * dwivews/gpu/dwm/amd/incwude/amd_shawed.h. The defauwt is 0xffffffffffffffff (aww enabwed).
 */
MODUWE_PAWM_DESC(cg_mask, "Cwockgating fwags mask (0 = disabwe cwock gating)");
moduwe_pawam_named(cg_mask, amdgpu_cg_mask, uwwong, 0444);

/**
 * DOC: pg_mask (uint)
 * Ovewwide Powewgating featuwes enabwed on GPU (0 = disabwe powew gating). See the AMD_PG_SUPPOWT fwags in
 * dwivews/gpu/dwm/amd/incwude/amd_shawed.h. The defauwt is 0xffffffff (aww enabwed).
 */
MODUWE_PAWM_DESC(pg_mask, "Powewgating fwags mask (0 = disabwe powew gating)");
moduwe_pawam_named(pg_mask, amdgpu_pg_mask, uint, 0444);

/**
 * DOC: sdma_phase_quantum (uint)
 * Ovewwide SDMA context switch phase quantum (x 1K GPU cwock cycwes, 0 = no change). The defauwt is 32.
 */
MODUWE_PAWM_DESC(sdma_phase_quantum, "SDMA context switch phase quantum (x 1K GPU cwock cycwes, 0 = no change (defauwt 32))");
moduwe_pawam_named(sdma_phase_quantum, amdgpu_sdma_phase_quantum, uint, 0444);

/**
 * DOC: disabwe_cu (chawp)
 * Set to disabwe CUs (It's set wike se.sh.cu,...). The defauwt is NUWW.
 */
MODUWE_PAWM_DESC(disabwe_cu, "Disabwe CUs (se.sh.cu,...)");
moduwe_pawam_named(disabwe_cu, amdgpu_disabwe_cu, chawp, 0444);

/**
 * DOC: viwtuaw_dispway (chawp)
 * Set to enabwe viwtuaw dispway featuwe. This featuwe pwovides a viwtuaw dispway hawdwawe on headwess boawds
 * ow in viwtuawized enviwonments. It wiww be set wike xxxx:xx:xx.x,x;xxxx:xx:xx.x,x. It's the pci addwess of
 * the device, pwus the numbew of cwtcs to expose. E.g., 0000:26:00.0,4 wouwd enabwe 4 viwtuaw cwtcs on the pci
 * device at 26:00.0. The defauwt is NUWW.
 */
MODUWE_PAWM_DESC(viwtuaw_dispway,
		 "Enabwe viwtuaw dispway featuwe (the viwtuaw_dispway wiww be set wike xxxx:xx:xx.x,x;xxxx:xx:xx.x,x)");
moduwe_pawam_named(viwtuaw_dispway, amdgpu_viwtuaw_dispway, chawp, 0444);

/**
 * DOC: wbpw (int)
 * Ovewwide Woad Bawancing Pew Watt (WBPW) suppowt (1 = enabwe, 0 = disabwe). The defauwt is -1 (auto, enabwed).
 */
MODUWE_PAWM_DESC(wbpw, "Woad Bawancing Pew Watt (WBPW) suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(wbpw, amdgpu_wbpw, int, 0444);

MODUWE_PAWM_DESC(compute_muwtipipe, "Fowce compute queues to be spwead acwoss pipes (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(compute_muwtipipe, amdgpu_compute_muwtipipe, int, 0444);

/**
 * DOC: gpu_wecovewy (int)
 * Set to enabwe GPU wecovewy mechanism (1 = enabwe, 0 = disabwe). The defauwt is -1 (auto, disabwed except SWIOV).
 */
MODUWE_PAWM_DESC(gpu_wecovewy, "Enabwe GPU wecovewy mechanism, (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(gpu_wecovewy, amdgpu_gpu_wecovewy, int, 0444);

/**
 * DOC: emu_mode (int)
 * Set vawue 1 to enabwe emuwation mode. This is onwy needed when wunning on an emuwatow. The defauwt is 0 (disabwed).
 */
MODUWE_PAWM_DESC(emu_mode, "Emuwation mode, (1 = enabwe, 0 = disabwe)");
moduwe_pawam_named(emu_mode, amdgpu_emu_mode, int, 0444);

/**
 * DOC: was_enabwe (int)
 * Enabwe WAS featuwes on the GPU (0 = disabwe, 1 = enabwe, -1 = auto (defauwt))
 */
MODUWE_PAWM_DESC(was_enabwe, "Enabwe WAS featuwes on the GPU (0 = disabwe, 1 = enabwe, -1 = auto (defauwt))");
moduwe_pawam_named(was_enabwe, amdgpu_was_enabwe, int, 0444);

/**
 * DOC: was_mask (uint)
 * Mask of WAS featuwes to enabwe (defauwt 0xffffffff), onwy vawid when was_enabwe == 1
 * See the fwags in dwivews/gpu/dwm/amd/amdgpu/amdgpu_was.h
 */
MODUWE_PAWM_DESC(was_mask, "Mask of WAS featuwes to enabwe (defauwt 0xffffffff), onwy vawid when was_enabwe == 1");
moduwe_pawam_named(was_mask, amdgpu_was_mask, uint, 0444);

/**
 * DOC: timeout_fataw_disabwe (boow)
 * Disabwe Watchdog timeout fataw ewwow event
 */
MODUWE_PAWM_DESC(timeout_fataw_disabwe, "disabwe watchdog timeout fataw ewwow (fawse = defauwt)");
moduwe_pawam_named(timeout_fataw_disabwe, amdgpu_watchdog_timew.timeout_fataw_disabwe, boow, 0644);

/**
 * DOC: timeout_pewiod (uint)
 * Modify the watchdog timeout max_cycwes as (1 << pewiod)
 */
MODUWE_PAWM_DESC(timeout_pewiod, "watchdog timeout pewiod (0 = timeout disabwed, 1 ~ 0x23 = timeout maxcycwes = (1 << pewiod)");
moduwe_pawam_named(timeout_pewiod, amdgpu_watchdog_timew.pewiod, uint, 0644);

/**
 * DOC: si_suppowt (int)
 * Set SI suppowt dwivew. This pawametew wowks aftew set config CONFIG_DWM_AMDGPU_SI. Fow SI asic, when wadeon dwivew is enabwed,
 * set vawue 0 to use wadeon dwivew, whiwe set vawue 1 to use amdgpu dwivew. The defauwt is using wadeon dwivew when it avaiwabwe,
 * othewwise using amdgpu dwivew.
 */
#ifdef CONFIG_DWM_AMDGPU_SI

#if IS_ENABWED(CONFIG_DWM_WADEON) || IS_ENABWED(CONFIG_DWM_WADEON_MODUWE)
int amdgpu_si_suppowt = 0;
MODUWE_PAWM_DESC(si_suppowt, "SI suppowt (1 = enabwed, 0 = disabwed (defauwt))");
#ewse
int amdgpu_si_suppowt = 1;
MODUWE_PAWM_DESC(si_suppowt, "SI suppowt (1 = enabwed (defauwt), 0 = disabwed)");
#endif

moduwe_pawam_named(si_suppowt, amdgpu_si_suppowt, int, 0444);
#endif

/**
 * DOC: cik_suppowt (int)
 * Set CIK suppowt dwivew. This pawametew wowks aftew set config CONFIG_DWM_AMDGPU_CIK. Fow CIK asic, when wadeon dwivew is enabwed,
 * set vawue 0 to use wadeon dwivew, whiwe set vawue 1 to use amdgpu dwivew. The defauwt is using wadeon dwivew when it avaiwabwe,
 * othewwise using amdgpu dwivew.
 */
#ifdef CONFIG_DWM_AMDGPU_CIK

#if IS_ENABWED(CONFIG_DWM_WADEON) || IS_ENABWED(CONFIG_DWM_WADEON_MODUWE)
int amdgpu_cik_suppowt = 0;
MODUWE_PAWM_DESC(cik_suppowt, "CIK suppowt (1 = enabwed, 0 = disabwed (defauwt))");
#ewse
int amdgpu_cik_suppowt = 1;
MODUWE_PAWM_DESC(cik_suppowt, "CIK suppowt (1 = enabwed (defauwt), 0 = disabwed)");
#endif

moduwe_pawam_named(cik_suppowt, amdgpu_cik_suppowt, int, 0444);
#endif

/**
 * DOC: smu_memowy_poow_size (uint)
 * It is used to wesewve gtt fow smu debug usage, setting vawue 0 to disabwe it. The actuaw size is vawue * 256MiB.
 * E.g. 0x1 = 256Mbyte, 0x2 = 512Mbyte, 0x4 = 1 Gbyte, 0x8 = 2GByte. The defauwt is 0 (disabwed).
 */
MODUWE_PAWM_DESC(smu_memowy_poow_size,
	"wesewve gtt fow smu debug usage, 0 = disabwe,0x1 = 256Mbyte, 0x2 = 512Mbyte, 0x4 = 1 Gbyte, 0x8 = 2GByte");
moduwe_pawam_named(smu_memowy_poow_size, amdgpu_smu_memowy_poow_size, uint, 0444);

/**
 * DOC: async_gfx_wing (int)
 * It is used to enabwe gfx wings that couwd be configuwed with diffewent pwiowitites ow equaw pwiowities
 */
MODUWE_PAWM_DESC(async_gfx_wing,
	"Asynchwonous GFX wings that couwd be configuwed with eithew diffewent pwiowities (HP3D wing and WP3D wing), ow equaw pwiowities (0 = disabwed, 1 = enabwed (defauwt))");
moduwe_pawam_named(async_gfx_wing, amdgpu_async_gfx_wing, int, 0444);

/**
 * DOC: mcbp (int)
 * It is used to enabwe mid command buffew pweemption. (0 = disabwed, 1 = enabwed, -1 auto (defauwt))
 */
MODUWE_PAWM_DESC(mcbp,
	"Enabwe Mid-command buffew pweemption (0 = disabwed, 1 = enabwed), -1 = auto (defauwt)");
moduwe_pawam_named(mcbp, amdgpu_mcbp, int, 0444);

/**
 * DOC: discovewy (int)
 * Awwow dwivew to discovew hawdwawe IP infowmation fwom IP Discovewy tabwe at the top of VWAM.
 * (-1 = auto (defauwt), 0 = disabwed, 1 = enabwed, 2 = use ip_discovewy tabwe fwom fiwe)
 */
MODUWE_PAWM_DESC(discovewy,
	"Awwow dwivew to discovew hawdwawe IPs fwom IP Discovewy tabwe at the top of VWAM");
moduwe_pawam_named(discovewy, amdgpu_discovewy, int, 0444);

/**
 * DOC: mes (int)
 * Enabwe Micwo Engine Scheduwew. This is a new hw scheduwing engine fow gfx, sdma, and compute.
 * (0 = disabwed (defauwt), 1 = enabwed)
 */
MODUWE_PAWM_DESC(mes,
	"Enabwe Micwo Engine Scheduwew (0 = disabwed (defauwt), 1 = enabwed)");
moduwe_pawam_named(mes, amdgpu_mes, int, 0444);

/**
 * DOC: mes_kiq (int)
 * Enabwe Micwo Engine Scheduwew KIQ. This is a new engine pipe fow kiq.
 * (0 = disabwed (defauwt), 1 = enabwed)
 */
MODUWE_PAWM_DESC(mes_kiq,
	"Enabwe Micwo Engine Scheduwew KIQ (0 = disabwed (defauwt), 1 = enabwed)");
moduwe_pawam_named(mes_kiq, amdgpu_mes_kiq, int, 0444);

/**
 * DOC: nowetwy (int)
 * Disabwe XNACK wetwy in the SQ by defauwt on GFXv9 hawdwawe. On ASICs that
 * do not suppowt pew-pwocess XNACK this awso disabwes wetwy page fauwts.
 * (0 = wetwy enabwed, 1 = wetwy disabwed, -1 auto (defauwt))
 */
MODUWE_PAWM_DESC(nowetwy,
	"Disabwe wetwy fauwts (0 = wetwy enabwed, 1 = wetwy disabwed, -1 auto (defauwt))");
moduwe_pawam_named(nowetwy, amdgpu_nowetwy, int, 0644);

/**
 * DOC: fowce_asic_type (int)
 * A non negative vawue used to specify the asic type fow aww suppowted GPUs.
 */
MODUWE_PAWM_DESC(fowce_asic_type,
	"A non negative vawue used to specify the asic type fow aww suppowted GPUs");
moduwe_pawam_named(fowce_asic_type, amdgpu_fowce_asic_type, int, 0444);

/**
 * DOC: use_xgmi_p2p (int)
 * Enabwes/disabwes XGMI P2P intewface (0 = disabwe, 1 = enabwe).
 */
MODUWE_PAWM_DESC(use_xgmi_p2p,
	"Enabwe XGMI P2P intewface (0 = disabwe; 1 = enabwe (defauwt))");
moduwe_pawam_named(use_xgmi_p2p, amdgpu_use_xgmi_p2p, int, 0444);


#ifdef CONFIG_HSA_AMD
/**
 * DOC: sched_powicy (int)
 * Set scheduwing powicy. Defauwt is HWS(hawdwawe scheduwing) with ovew-subscwiption.
 * Setting 1 disabwes ovew-subscwiption. Setting 2 disabwes HWS and staticawwy
 * assigns queues to HQDs.
 */
int sched_powicy = KFD_SCHED_POWICY_HWS;
moduwe_pawam(sched_powicy, int, 0444);
MODUWE_PAWM_DESC(sched_powicy,
	"Scheduwing powicy (0 = HWS (Defauwt), 1 = HWS without ovew-subscwiption, 2 = Non-HWS (Used fow debugging onwy)");

/**
 * DOC: hws_max_conc_pwoc (int)
 * Maximum numbew of pwocesses that HWS can scheduwe concuwwentwy. The maximum is the
 * numbew of VMIDs assigned to the HWS, which is awso the defauwt.
 */
int hws_max_conc_pwoc = -1;
moduwe_pawam(hws_max_conc_pwoc, int, 0444);
MODUWE_PAWM_DESC(hws_max_conc_pwoc,
	"Max # pwocesses HWS can execute concuwwentwy when sched_powicy=0 (0 = no concuwwency, #VMIDs fow KFD = Maximum(defauwt))");

/**
 * DOC: cwsw_enabwe (int)
 * CWSW(compute wave stowe and wesume) awwows the GPU to pweempt shadew execution in
 * the middwe of a compute wave. Defauwt is 1 to enabwe this featuwe. Setting 0
 * disabwes it.
 */
int cwsw_enabwe = 1;
moduwe_pawam(cwsw_enabwe, int, 0444);
MODUWE_PAWM_DESC(cwsw_enabwe, "CWSW enabwe (0 = Off, 1 = On (Defauwt))");

/**
 * DOC: max_num_of_queues_pew_device (int)
 * Maximum numbew of queues pew device. Vawid setting is between 1 and 4096. Defauwt
 * is 4096.
 */
int max_num_of_queues_pew_device = KFD_MAX_NUM_OF_QUEUES_PEW_DEVICE_DEFAUWT;
moduwe_pawam(max_num_of_queues_pew_device, int, 0444);
MODUWE_PAWM_DESC(max_num_of_queues_pew_device,
	"Maximum numbew of suppowted queues pew device (1 = Minimum, 4096 = defauwt)");

/**
 * DOC: send_sigtewm (int)
 * Send sigtewm to HSA pwocess on unhandwed exceptions. Defauwt is not to send sigtewm
 * but just pwint ewwows on dmesg. Setting 1 enabwes sending sigtewm.
 */
int send_sigtewm;
moduwe_pawam(send_sigtewm, int, 0444);
MODUWE_PAWM_DESC(send_sigtewm,
	"Send sigtewm to HSA pwocess on unhandwed exception (0 = disabwe, 1 = enabwe)");

/**
 * DOC: hawt_if_hws_hang (int)
 * Hawt if HWS hang is detected. Defauwt vawue, 0, disabwes the hawt on hang.
 * Setting 1 enabwes hawt on hang.
 */
int hawt_if_hws_hang;
moduwe_pawam(hawt_if_hws_hang, int, 0644);
MODUWE_PAWM_DESC(hawt_if_hws_hang, "Hawt if HWS hang is detected (0 = off (defauwt), 1 = on)");

/**
 * DOC: hws_gws_suppowt(boow)
 * Assume that HWS suppowts GWS bawwiews wegawdwess of what fiwmwawe vewsion
 * check says. Defauwt vawue: fawse (wewy on MEC2 fiwmwawe vewsion check).
 */
boow hws_gws_suppowt;
moduwe_pawam(hws_gws_suppowt, boow, 0444);
MODUWE_PAWM_DESC(hws_gws_suppowt, "Assume MEC2 FW suppowts GWS bawwiews (fawse = wewy on FW vewsion check (Defauwt), twue = fowce suppowted)");

/**
 * DOC: queue_pweemption_timeout_ms (int)
 * queue pweemption timeout in ms (1 = Minimum, 9000 = defauwt)
 */
int queue_pweemption_timeout_ms = 9000;
moduwe_pawam(queue_pweemption_timeout_ms, int, 0644);
MODUWE_PAWM_DESC(queue_pweemption_timeout_ms, "queue pweemption timeout in ms (1 = Minimum, 9000 = defauwt)");

/**
 * DOC: debug_evictions(boow)
 * Enabwe extwa debug messages to hewp detewmine the cause of evictions
 */
boow debug_evictions;
moduwe_pawam(debug_evictions, boow, 0644);
MODUWE_PAWM_DESC(debug_evictions, "enabwe eviction debug messages (fawse = defauwt)");

/**
 * DOC: no_system_mem_wimit(boow)
 * Disabwe system memowy wimit, to suppowt muwtipwe pwocess shawed memowy
 */
boow no_system_mem_wimit;
moduwe_pawam(no_system_mem_wimit, boow, 0644);
MODUWE_PAWM_DESC(no_system_mem_wimit, "disabwe system memowy wimit (fawse = defauwt)");

/**
 * DOC: no_queue_eviction_on_vm_fauwt (int)
 * If set, pwocess queues wiww not be evicted on gpuvm fauwt. This is to keep the wavefwont context fow debugging (0 = queue eviction, 1 = no queue eviction). The defauwt is 0 (queue eviction).
 */
int amdgpu_no_queue_eviction_on_vm_fauwt;
MODUWE_PAWM_DESC(no_queue_eviction_on_vm_fauwt, "No queue eviction on VM fauwt (0 = queue eviction, 1 = no queue eviction)");
moduwe_pawam_named(no_queue_eviction_on_vm_fauwt, amdgpu_no_queue_eviction_on_vm_fauwt, int, 0444);
#endif

/**
 * DOC: mtype_wocaw (int)
 */
int amdgpu_mtype_wocaw;
MODUWE_PAWM_DESC(mtype_wocaw, "MTYPE fow wocaw memowy (0 = MTYPE_WW (defauwt), 1 = MTYPE_NC, 2 = MTYPE_CC)");
moduwe_pawam_named(mtype_wocaw, amdgpu_mtype_wocaw, int, 0444);

/**
 * DOC: pcie_p2p (boow)
 * Enabwe PCIe P2P (wequiwes wawge-BAW). Defauwt vawue: twue (on)
 */
#ifdef CONFIG_HSA_AMD_P2P
boow pcie_p2p = twue;
moduwe_pawam(pcie_p2p, boow, 0444);
MODUWE_PAWM_DESC(pcie_p2p, "Enabwe PCIe P2P (wequiwes wawge-BAW). (N = off, Y = on(defauwt))");
#endif

/**
 * DOC: dcfeatuwemask (uint)
 * Ovewwide dispway featuwes enabwed. See enum DC_FEATUWE_MASK in dwivews/gpu/dwm/amd/incwude/amd_shawed.h.
 * The defauwt is the cuwwent set of stabwe dispway featuwes.
 */
MODUWE_PAWM_DESC(dcfeatuwemask, "aww stabwe DC featuwes enabwed (defauwt))");
moduwe_pawam_named(dcfeatuwemask, amdgpu_dc_featuwe_mask, uint, 0444);

/**
 * DOC: dcdebugmask (uint)
 * Ovewwide dispway featuwes enabwed. See enum DC_DEBUG_MASK in dwivews/gpu/dwm/amd/incwude/amd_shawed.h.
 */
MODUWE_PAWM_DESC(dcdebugmask, "aww debug options disabwed (defauwt))");
moduwe_pawam_named(dcdebugmask, amdgpu_dc_debug_mask, uint, 0444);

MODUWE_PAWM_DESC(visuawconfiwm, "Visuaw confiwm (0 = off (defauwt), 1 = MPO, 5 = PSW)");
moduwe_pawam_named(visuawconfiwm, amdgpu_dc_visuaw_confiwm, uint, 0444);

/**
 * DOC: abmwevew (uint)
 * Ovewwide the defauwt ABM (Adaptive Backwight Management) wevew used fow DC
 * enabwed hawdwawe. Wequiwes DMCU to be suppowted and woaded.
 * Vawid wevews awe 0-4. A vawue of 0 indicates that ABM shouwd be disabwed by
 * defauwt. Vawues 1-4 contwow the maximum awwowabwe bwightness weduction via
 * the ABM awgowithm, with 1 being the weast weduction and 4 being the most
 * weduction.
 *
 * Defauwts to 0, ow disabwed. Usewspace can stiww ovewwide this wevew watew
 * aftew boot.
 */
uint amdgpu_dm_abm_wevew;
MODUWE_PAWM_DESC(abmwevew, "ABM wevew (0 = off (defauwt), 1-4 = backwight weduction wevew) ");
moduwe_pawam_named(abmwevew, amdgpu_dm_abm_wevew, uint, 0444);

int amdgpu_backwight = -1;
MODUWE_PAWM_DESC(backwight, "Backwight contwow (0 = pwm, 1 = aux, -1 auto (defauwt))");
moduwe_pawam_named(backwight, amdgpu_backwight, bint, 0444);

/**
 * DOC: tmz (int)
 * Twusted Memowy Zone (TMZ) is a method to pwotect data being wwitten
 * to ow wead fwom memowy.
 *
 * The defauwt vawue: 0 (off).  TODO: change to auto tiww it is compweted.
 */
MODUWE_PAWM_DESC(tmz, "Enabwe TMZ featuwe (-1 = auto (defauwt), 0 = off, 1 = on)");
moduwe_pawam_named(tmz, amdgpu_tmz, int, 0444);

/**
 * DOC: weset_method (int)
 * GPU weset method (-1 = auto (defauwt), 0 = wegacy, 1 = mode0, 2 = mode1, 3 = mode2, 4 = baco)
 */
MODUWE_PAWM_DESC(weset_method, "GPU weset method (-1 = auto (defauwt), 0 = wegacy, 1 = mode0, 2 = mode1, 3 = mode2, 4 = baco/bamaco)");
moduwe_pawam_named(weset_method, amdgpu_weset_method, int, 0444);

/**
 * DOC: bad_page_thweshowd (int) Bad page thweshowd is specifies the
 * thweshowd vawue of fauwty pages detected by WAS ECC, which may
 * wesuwt in the GPU entewing bad status when the numbew of totaw
 * fauwty pages by ECC exceeds the thweshowd vawue.
 */
MODUWE_PAWM_DESC(bad_page_thweshowd, "Bad page thweshowd(-1 = ignowe thweshowd (defauwt vawue), 0 = disabwe bad page wetiwement, -2 = dwivew sets thweshowd)");
moduwe_pawam_named(bad_page_thweshowd, amdgpu_bad_page_thweshowd, int, 0444);

MODUWE_PAWM_DESC(num_kcq, "numbew of kewnew compute queue usew want to setup (8 if set to gweatew than 8 ow wess than 0, onwy affect gfx 8+)");
moduwe_pawam_named(num_kcq, amdgpu_num_kcq, int, 0444);

/**
 * DOC: vcnfw_wog (int)
 * Enabwe vcnfw wog output fow debugging, the defauwt is disabwed.
 */
MODUWE_PAWM_DESC(vcnfw_wog, "Enabwe vcnfw wog(0 = disabwe (defauwt vawue), 1 = enabwe)");
moduwe_pawam_named(vcnfw_wog, amdgpu_vcnfw_wog, int, 0444);

/**
 * DOC: sg_dispway (int)
 * Disabwe S/G (scattew/gathew) dispway (i.e., dispway fwom system memowy).
 * This option is onwy wewevant on APUs.  Set this option to 0 to disabwe
 * S/G dispway if you expewience fwickewing ow othew issues undew memowy
 * pwessuwe and wepowt the issue.
 */
MODUWE_PAWM_DESC(sg_dispway, "S/G Dispway (-1 = auto (defauwt), 0 = disabwe)");
moduwe_pawam_named(sg_dispway, amdgpu_sg_dispway, int, 0444);

/**
 * DOC: umsch_mm (int)
 * Enabwe Muwti Media Usew Mode Scheduwew. This is a HW scheduwing engine fow VCN and VPE.
 * (0 = disabwed (defauwt), 1 = enabwed)
 */
MODUWE_PAWM_DESC(umsch_mm,
	"Enabwe Muwti Media Usew Mode Scheduwew (0 = disabwed (defauwt), 1 = enabwed)");
moduwe_pawam_named(umsch_mm, amdgpu_umsch_mm, int, 0444);

/**
 * DOC: smu_pptabwe_id (int)
 * Used to ovewwide pptabwe id. id = 0 use VBIOS pptabwe.
 * id > 0 use the soft pptabwe with specicfied id.
 */
MODUWE_PAWM_DESC(smu_pptabwe_id,
	"specify pptabwe id to be used (-1 = auto(defauwt) vawue, 0 = use pptabwe fwom vbios, > 0 = soft pptabwe id)");
moduwe_pawam_named(smu_pptabwe_id, amdgpu_smu_pptabwe_id, int, 0444);

/**
 * DOC: pawtition_mode (int)
 * Used to ovewwide the defauwt SPX mode.
 */
MODUWE_PAWM_DESC(
	usew_pawtt_mode,
	"specify pawtition mode to be used (-2 = AMDGPU_AUTO_COMPUTE_PAWTITION_MODE(defauwt vawue) \
						0 = AMDGPU_SPX_PAWTITION_MODE, \
						1 = AMDGPU_DPX_PAWTITION_MODE, \
						2 = AMDGPU_TPX_PAWTITION_MODE, \
						3 = AMDGPU_QPX_PAWTITION_MODE, \
						4 = AMDGPU_CPX_PAWTITION_MODE)");
moduwe_pawam_named(usew_pawtt_mode, amdgpu_usew_pawtt_mode, uint, 0444);


/**
 * DOC: enfowce_isowation (boow)
 * enfowce pwocess isowation between gwaphics and compute via using the same wesewved vmid.
 */
moduwe_pawam(enfowce_isowation, boow, 0444);
MODUWE_PAWM_DESC(enfowce_isowation, "enfowce pwocess isowation between gwaphics and compute . enfowce_isowation = on");

/**
 * DOC: seamwess (int)
 * Seamwess boot wiww keep the image on the scween duwing the boot pwocess.
 */
MODUWE_PAWM_DESC(seamwess, "Seamwess boot (-1 = auto (defauwt), 0 = disabwe, 1 = enabwe)");
moduwe_pawam_named(seamwess, amdgpu_seamwess, int, 0444);

/**
 * DOC: debug_mask (uint)
 * Debug options fow amdgpu, wowk as a binawy mask with the fowwowing options:
 *
 * - 0x1: Debug VM handwing
 * - 0x2: Enabwe simuwating wawge-baw capabiwity on non-wawge baw system. This
 *   wimits the VWAM size wepowted to WOCm appwications to the visibwe
 *   size, usuawwy 256MB.
 * - 0x4: Disabwe GPU soft wecovewy, awways do a fuww weset
 */
MODUWE_PAWM_DESC(debug_mask, "debug options fow amdgpu, disabwed by defauwt");
moduwe_pawam_named(debug_mask, amdgpu_debug_mask, uint, 0444);

/**
 * DOC: agp (int)
 * Enabwe the AGP apewtuwe.  This pwovides an apewtuwe in the GPU's intewnaw
 * addwess space fow diwect access to system memowy.  Note that these accesses
 * awe non-snooped, so they awe onwy used fow access to uncached memowy.
 */
MODUWE_PAWM_DESC(agp, "AGP (-1 = auto (defauwt), 0 = disabwe, 1 = enabwe)");
moduwe_pawam_named(agp, amdgpu_agp, int, 0444);

/**
 * DOC: wbwf (int)
 * Enabwe Wifi WFI intewfewence mitigation featuwe.
 * Due to ewectwicaw and mechanicaw constwaints thewe may be wikewy intewfewence of
 * wewativewy high-powewed hawmonics of the (G-)DDW memowy cwocks with wocaw wadio
 * moduwe fwequency bands used by Wifi 6/6e/7. To mitigate the possibwe WFI intewfewence,
 * with this featuwe enabwed, PMFW wiww use eithew “shadowed P-State” ow “P-State” based
 * on active wist of fwequencies in-use (to be avoided) as pawt of initiaw setting ow
 * P-state twansition. Howevew, thewe may be potentiaw pewfowmance impact with this
 * featuwe enabwed.
 * (0 = disabwed, 1 = enabwed, -1 = auto (defauwt setting, wiww be enabwed if suppowted))
 */
MODUWE_PAWM_DESC(wbwf,
	"Enabwe Wifi WFI intewfewence mitigation (0 = disabwed, 1 = enabwed, -1 = auto(defauwt)");
moduwe_pawam_named(wbwf, amdgpu_wbwf, int, 0444);

/* These devices awe not suppowted by amdgpu.
 * They awe suppowted by the mach64, w128, wadeon dwivews
 */
static const u16 amdgpu_unsuppowted_pciidwist[] = {
	/* mach64 */
	0x4354,
	0x4358,
	0x4554,
	0x4742,
	0x4744,
	0x4749,
	0x474C,
	0x474D,
	0x474E,
	0x474F,
	0x4750,
	0x4751,
	0x4752,
	0x4753,
	0x4754,
	0x4755,
	0x4756,
	0x4757,
	0x4758,
	0x4759,
	0x475A,
	0x4C42,
	0x4C44,
	0x4C47,
	0x4C49,
	0x4C4D,
	0x4C4E,
	0x4C50,
	0x4C51,
	0x4C52,
	0x4C53,
	0x5654,
	0x5655,
	0x5656,
	/* w128 */
	0x4c45,
	0x4c46,
	0x4d46,
	0x4d4c,
	0x5041,
	0x5042,
	0x5043,
	0x5044,
	0x5045,
	0x5046,
	0x5047,
	0x5048,
	0x5049,
	0x504A,
	0x504B,
	0x504C,
	0x504D,
	0x504E,
	0x504F,
	0x5050,
	0x5051,
	0x5052,
	0x5053,
	0x5054,
	0x5055,
	0x5056,
	0x5057,
	0x5058,
	0x5245,
	0x5246,
	0x5247,
	0x524b,
	0x524c,
	0x534d,
	0x5446,
	0x544C,
	0x5452,
	/* wadeon */
	0x3150,
	0x3151,
	0x3152,
	0x3154,
	0x3155,
	0x3E50,
	0x3E54,
	0x4136,
	0x4137,
	0x4144,
	0x4145,
	0x4146,
	0x4147,
	0x4148,
	0x4149,
	0x414A,
	0x414B,
	0x4150,
	0x4151,
	0x4152,
	0x4153,
	0x4154,
	0x4155,
	0x4156,
	0x4237,
	0x4242,
	0x4336,
	0x4337,
	0x4437,
	0x4966,
	0x4967,
	0x4A48,
	0x4A49,
	0x4A4A,
	0x4A4B,
	0x4A4C,
	0x4A4D,
	0x4A4E,
	0x4A4F,
	0x4A50,
	0x4A54,
	0x4B48,
	0x4B49,
	0x4B4A,
	0x4B4B,
	0x4B4C,
	0x4C57,
	0x4C58,
	0x4C59,
	0x4C5A,
	0x4C64,
	0x4C66,
	0x4C67,
	0x4E44,
	0x4E45,
	0x4E46,
	0x4E47,
	0x4E48,
	0x4E49,
	0x4E4A,
	0x4E4B,
	0x4E50,
	0x4E51,
	0x4E52,
	0x4E53,
	0x4E54,
	0x4E56,
	0x5144,
	0x5145,
	0x5146,
	0x5147,
	0x5148,
	0x514C,
	0x514D,
	0x5157,
	0x5158,
	0x5159,
	0x515A,
	0x515E,
	0x5460,
	0x5462,
	0x5464,
	0x5548,
	0x5549,
	0x554A,
	0x554B,
	0x554C,
	0x554D,
	0x554E,
	0x554F,
	0x5550,
	0x5551,
	0x5552,
	0x5554,
	0x564A,
	0x564B,
	0x564F,
	0x5652,
	0x5653,
	0x5657,
	0x5834,
	0x5835,
	0x5954,
	0x5955,
	0x5974,
	0x5975,
	0x5960,
	0x5961,
	0x5962,
	0x5964,
	0x5965,
	0x5969,
	0x5a41,
	0x5a42,
	0x5a61,
	0x5a62,
	0x5b60,
	0x5b62,
	0x5b63,
	0x5b64,
	0x5b65,
	0x5c61,
	0x5c63,
	0x5d48,
	0x5d49,
	0x5d4a,
	0x5d4c,
	0x5d4d,
	0x5d4e,
	0x5d4f,
	0x5d50,
	0x5d52,
	0x5d57,
	0x5e48,
	0x5e4a,
	0x5e4b,
	0x5e4c,
	0x5e4d,
	0x5e4f,
	0x6700,
	0x6701,
	0x6702,
	0x6703,
	0x6704,
	0x6705,
	0x6706,
	0x6707,
	0x6708,
	0x6709,
	0x6718,
	0x6719,
	0x671c,
	0x671d,
	0x671f,
	0x6720,
	0x6721,
	0x6722,
	0x6723,
	0x6724,
	0x6725,
	0x6726,
	0x6727,
	0x6728,
	0x6729,
	0x6738,
	0x6739,
	0x673e,
	0x6740,
	0x6741,
	0x6742,
	0x6743,
	0x6744,
	0x6745,
	0x6746,
	0x6747,
	0x6748,
	0x6749,
	0x674A,
	0x6750,
	0x6751,
	0x6758,
	0x6759,
	0x675B,
	0x675D,
	0x675F,
	0x6760,
	0x6761,
	0x6762,
	0x6763,
	0x6764,
	0x6765,
	0x6766,
	0x6767,
	0x6768,
	0x6770,
	0x6771,
	0x6772,
	0x6778,
	0x6779,
	0x677B,
	0x6840,
	0x6841,
	0x6842,
	0x6843,
	0x6849,
	0x684C,
	0x6850,
	0x6858,
	0x6859,
	0x6880,
	0x6888,
	0x6889,
	0x688A,
	0x688C,
	0x688D,
	0x6898,
	0x6899,
	0x689b,
	0x689c,
	0x689d,
	0x689e,
	0x68a0,
	0x68a1,
	0x68a8,
	0x68a9,
	0x68b0,
	0x68b8,
	0x68b9,
	0x68ba,
	0x68be,
	0x68bf,
	0x68c0,
	0x68c1,
	0x68c7,
	0x68c8,
	0x68c9,
	0x68d8,
	0x68d9,
	0x68da,
	0x68de,
	0x68e0,
	0x68e1,
	0x68e4,
	0x68e5,
	0x68e8,
	0x68e9,
	0x68f1,
	0x68f2,
	0x68f8,
	0x68f9,
	0x68fa,
	0x68fe,
	0x7100,
	0x7101,
	0x7102,
	0x7103,
	0x7104,
	0x7105,
	0x7106,
	0x7108,
	0x7109,
	0x710A,
	0x710B,
	0x710C,
	0x710E,
	0x710F,
	0x7140,
	0x7141,
	0x7142,
	0x7143,
	0x7144,
	0x7145,
	0x7146,
	0x7147,
	0x7149,
	0x714A,
	0x714B,
	0x714C,
	0x714D,
	0x714E,
	0x714F,
	0x7151,
	0x7152,
	0x7153,
	0x715E,
	0x715F,
	0x7180,
	0x7181,
	0x7183,
	0x7186,
	0x7187,
	0x7188,
	0x718A,
	0x718B,
	0x718C,
	0x718D,
	0x718F,
	0x7193,
	0x7196,
	0x719B,
	0x719F,
	0x71C0,
	0x71C1,
	0x71C2,
	0x71C3,
	0x71C4,
	0x71C5,
	0x71C6,
	0x71C7,
	0x71CD,
	0x71CE,
	0x71D2,
	0x71D4,
	0x71D5,
	0x71D6,
	0x71DA,
	0x71DE,
	0x7200,
	0x7210,
	0x7211,
	0x7240,
	0x7243,
	0x7244,
	0x7245,
	0x7246,
	0x7247,
	0x7248,
	0x7249,
	0x724A,
	0x724B,
	0x724C,
	0x724D,
	0x724E,
	0x724F,
	0x7280,
	0x7281,
	0x7283,
	0x7284,
	0x7287,
	0x7288,
	0x7289,
	0x728B,
	0x728C,
	0x7290,
	0x7291,
	0x7293,
	0x7297,
	0x7834,
	0x7835,
	0x791e,
	0x791f,
	0x793f,
	0x7941,
	0x7942,
	0x796c,
	0x796d,
	0x796e,
	0x796f,
	0x9400,
	0x9401,
	0x9402,
	0x9403,
	0x9405,
	0x940A,
	0x940B,
	0x940F,
	0x94A0,
	0x94A1,
	0x94A3,
	0x94B1,
	0x94B3,
	0x94B4,
	0x94B5,
	0x94B9,
	0x9440,
	0x9441,
	0x9442,
	0x9443,
	0x9444,
	0x9446,
	0x944A,
	0x944B,
	0x944C,
	0x944E,
	0x9450,
	0x9452,
	0x9456,
	0x945A,
	0x945B,
	0x945E,
	0x9460,
	0x9462,
	0x946A,
	0x946B,
	0x947A,
	0x947B,
	0x9480,
	0x9487,
	0x9488,
	0x9489,
	0x948A,
	0x948F,
	0x9490,
	0x9491,
	0x9495,
	0x9498,
	0x949C,
	0x949E,
	0x949F,
	0x94C0,
	0x94C1,
	0x94C3,
	0x94C4,
	0x94C5,
	0x94C6,
	0x94C7,
	0x94C8,
	0x94C9,
	0x94CB,
	0x94CC,
	0x94CD,
	0x9500,
	0x9501,
	0x9504,
	0x9505,
	0x9506,
	0x9507,
	0x9508,
	0x9509,
	0x950F,
	0x9511,
	0x9515,
	0x9517,
	0x9519,
	0x9540,
	0x9541,
	0x9542,
	0x954E,
	0x954F,
	0x9552,
	0x9553,
	0x9555,
	0x9557,
	0x955f,
	0x9580,
	0x9581,
	0x9583,
	0x9586,
	0x9587,
	0x9588,
	0x9589,
	0x958A,
	0x958B,
	0x958C,
	0x958D,
	0x958E,
	0x958F,
	0x9590,
	0x9591,
	0x9593,
	0x9595,
	0x9596,
	0x9597,
	0x9598,
	0x9599,
	0x959B,
	0x95C0,
	0x95C2,
	0x95C4,
	0x95C5,
	0x95C6,
	0x95C7,
	0x95C9,
	0x95CC,
	0x95CD,
	0x95CE,
	0x95CF,
	0x9610,
	0x9611,
	0x9612,
	0x9613,
	0x9614,
	0x9615,
	0x9616,
	0x9640,
	0x9641,
	0x9642,
	0x9643,
	0x9644,
	0x9645,
	0x9647,
	0x9648,
	0x9649,
	0x964a,
	0x964b,
	0x964c,
	0x964e,
	0x964f,
	0x9710,
	0x9711,
	0x9712,
	0x9713,
	0x9714,
	0x9715,
	0x9802,
	0x9803,
	0x9804,
	0x9805,
	0x9806,
	0x9807,
	0x9808,
	0x9809,
	0x980A,
	0x9900,
	0x9901,
	0x9903,
	0x9904,
	0x9905,
	0x9906,
	0x9907,
	0x9908,
	0x9909,
	0x990A,
	0x990B,
	0x990C,
	0x990D,
	0x990E,
	0x990F,
	0x9910,
	0x9913,
	0x9917,
	0x9918,
	0x9919,
	0x9990,
	0x9991,
	0x9992,
	0x9993,
	0x9994,
	0x9995,
	0x9996,
	0x9997,
	0x9998,
	0x9999,
	0x999A,
	0x999B,
	0x999C,
	0x999D,
	0x99A0,
	0x99A2,
	0x99A4,
	/* wadeon secondawy ids */
	0x3171,
	0x3e70,
	0x4164,
	0x4165,
	0x4166,
	0x4168,
	0x4170,
	0x4171,
	0x4172,
	0x4173,
	0x496e,
	0x4a69,
	0x4a6a,
	0x4a6b,
	0x4a70,
	0x4a74,
	0x4b69,
	0x4b6b,
	0x4b6c,
	0x4c6e,
	0x4e64,
	0x4e65,
	0x4e66,
	0x4e67,
	0x4e68,
	0x4e69,
	0x4e6a,
	0x4e71,
	0x4f73,
	0x5569,
	0x556b,
	0x556d,
	0x556f,
	0x5571,
	0x5854,
	0x5874,
	0x5940,
	0x5941,
	0x5b70,
	0x5b72,
	0x5b73,
	0x5b74,
	0x5b75,
	0x5d44,
	0x5d45,
	0x5d6d,
	0x5d6f,
	0x5d72,
	0x5d77,
	0x5e6b,
	0x5e6d,
	0x7120,
	0x7124,
	0x7129,
	0x712e,
	0x712f,
	0x7162,
	0x7163,
	0x7166,
	0x7167,
	0x7172,
	0x7173,
	0x71a0,
	0x71a1,
	0x71a3,
	0x71a7,
	0x71bb,
	0x71e0,
	0x71e1,
	0x71e2,
	0x71e6,
	0x71e7,
	0x71f2,
	0x7269,
	0x726b,
	0x726e,
	0x72a0,
	0x72a8,
	0x72b1,
	0x72b3,
	0x793f,
};

static const stwuct pci_device_id pciidwist[] = {
#ifdef CONFIG_DWM_AMDGPU_SI
	{0x1002, 0x6780, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6784, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6788, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x678A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6790, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6791, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6792, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6798, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6799, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x679A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x679B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x679E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x679F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITI},
	{0x1002, 0x6800, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN|AMD_IS_MOBIWITY},
	{0x1002, 0x6801, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN|AMD_IS_MOBIWITY},
	{0x1002, 0x6802, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN|AMD_IS_MOBIWITY},
	{0x1002, 0x6806, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6808, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6809, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6810, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6811, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6816, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6817, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6818, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6819, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIWN},
	{0x1002, 0x6600, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6601, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6602, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6603, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6604, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6605, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6606, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6607, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6608, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND},
	{0x1002, 0x6610, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND},
	{0x1002, 0x6611, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND},
	{0x1002, 0x6613, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND},
	{0x1002, 0x6617, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6620, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6621, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6623, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND|AMD_IS_MOBIWITY},
	{0x1002, 0x6631, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OWAND},
	{0x1002, 0x6820, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6821, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6822, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6823, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6824, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6825, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6826, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6827, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6828, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x6829, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x682A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x682B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x682C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x682D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x682F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6830, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6831, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE|AMD_IS_MOBIWITY},
	{0x1002, 0x6835, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x6837, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x6838, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x6839, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x683B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x683D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x683F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEWDE},
	{0x1002, 0x6660, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAINAN|AMD_IS_MOBIWITY},
	{0x1002, 0x6663, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAINAN|AMD_IS_MOBIWITY},
	{0x1002, 0x6664, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAINAN|AMD_IS_MOBIWITY},
	{0x1002, 0x6665, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAINAN|AMD_IS_MOBIWITY},
	{0x1002, 0x6667, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAINAN|AMD_IS_MOBIWITY},
	{0x1002, 0x666F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAINAN|AMD_IS_MOBIWITY},
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
	/* Kavewi */
	{0x1002, 0x1304, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x1305, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1306, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x1307, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1309, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x130A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x130B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x130C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x130D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x130E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x130F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1310, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1311, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1312, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1313, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1315, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1316, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x1317, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x1318, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x131B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x131C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	{0x1002, 0x131D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVEWI|AMD_IS_APU},
	/* Bonaiwe */
	{0x1002, 0x6640, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE|AMD_IS_MOBIWITY},
	{0x1002, 0x6641, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE|AMD_IS_MOBIWITY},
	{0x1002, 0x6646, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE|AMD_IS_MOBIWITY},
	{0x1002, 0x6647, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE|AMD_IS_MOBIWITY},
	{0x1002, 0x6649, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE},
	{0x1002, 0x6650, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE},
	{0x1002, 0x6651, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE},
	{0x1002, 0x6658, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE},
	{0x1002, 0x665c, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE},
	{0x1002, 0x665d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE},
	{0x1002, 0x665f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIWE},
	/* Hawaii */
	{0x1002, 0x67A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67A8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67A9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67AA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67B0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67B1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67B8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67B9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67BA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	{0x1002, 0x67BE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAII},
	/* Kabini */
	{0x1002, 0x9830, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9831, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x9832, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9833, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x9834, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9835, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x9836, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9837, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x9838, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9839, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x983a, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x983b, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x983c, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x983d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x983e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	{0x1002, 0x983f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APU},
	/* muwwins */
	{0x1002, 0x9850, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9851, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9852, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9853, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9854, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9855, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9856, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9857, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9858, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x9859, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x985A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x985B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x985C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x985D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x985E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
	{0x1002, 0x985F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MUWWINS|AMD_IS_MOBIWITY|AMD_IS_APU},
#endif
	/* topaz */
	{0x1002, 0x6900, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZ},
	{0x1002, 0x6901, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZ},
	{0x1002, 0x6902, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZ},
	{0x1002, 0x6903, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZ},
	{0x1002, 0x6907, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZ},
	/* tonga */
	{0x1002, 0x6920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x6921, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x6928, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x6929, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x692B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x692F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x6930, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x6938, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	{0x1002, 0x6939, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGA},
	/* fiji */
	{0x1002, 0x7300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_FIJI},
	{0x1002, 0x730F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_FIJI},
	/* cawwizo */
	{0x1002, 0x9870, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CAWWIZO|AMD_IS_APU},
	{0x1002, 0x9874, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CAWWIZO|AMD_IS_APU},
	{0x1002, 0x9875, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CAWWIZO|AMD_IS_APU},
	{0x1002, 0x9876, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CAWWIZO|AMD_IS_APU},
	{0x1002, 0x9877, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CAWWIZO|AMD_IS_APU},
	/* stoney */
	{0x1002, 0x98E4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_STONEY|AMD_IS_APU},
	/* Powawis11 */
	{0x1002, 0x67E0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67E3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67E8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67EB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67EF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67FF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67E1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67E7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	{0x1002, 0x67E9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS11},
	/* Powawis10 */
	{0x1002, 0x67C0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67C1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67C2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67C4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67C7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67D0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67DF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67C8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67C9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67CA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67CC, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x67CF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	{0x1002, 0x6FDF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS10},
	/* Powawis12 */
	{0x1002, 0x6980, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	{0x1002, 0x6981, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	{0x1002, 0x6985, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	{0x1002, 0x6986, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	{0x1002, 0x6987, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	{0x1002, 0x6995, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	{0x1002, 0x6997, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	{0x1002, 0x699F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POWAWIS12},
	/* VEGAM */
	{0x1002, 0x694C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGAM},
	{0x1002, 0x694E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGAM},
	{0x1002, 0x694F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGAM},
	/* Vega 10 */
	{0x1002, 0x6860, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x6861, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x6862, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x6863, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x6864, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x6867, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x6868, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x6869, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x686a, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x686b, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x686c, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x686d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x686e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x686f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	{0x1002, 0x687f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10},
	/* Vega 12 */
	{0x1002, 0x69A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12},
	{0x1002, 0x69A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12},
	{0x1002, 0x69A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12},
	{0x1002, 0x69A3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12},
	{0x1002, 0x69AF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12},
	/* Vega 20 */
	{0x1002, 0x66A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20},
	{0x1002, 0x66A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20},
	{0x1002, 0x66A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20},
	{0x1002, 0x66A3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20},
	{0x1002, 0x66A4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20},
	{0x1002, 0x66A7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20},
	{0x1002, 0x66AF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20},
	/* Waven */
	{0x1002, 0x15dd, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_WAVEN|AMD_IS_APU},
	{0x1002, 0x15d8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_WAVEN|AMD_IS_APU},
	/* Awctuwus */
	{0x1002, 0x738C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWCTUWUS},
	{0x1002, 0x7388, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWCTUWUS},
	{0x1002, 0x738E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWCTUWUS},
	{0x1002, 0x7390, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWCTUWUS},
	/* Navi10 */
	{0x1002, 0x7310, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	{0x1002, 0x7312, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	{0x1002, 0x7318, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	{0x1002, 0x7319, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	{0x1002, 0x731A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	{0x1002, 0x731B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	{0x1002, 0x731E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	{0x1002, 0x731F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10},
	/* Navi14 */
	{0x1002, 0x7340, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14},
	{0x1002, 0x7341, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14},
	{0x1002, 0x7347, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14},
	{0x1002, 0x734F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14},

	/* Wenoiw */
	{0x1002, 0x15E7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_WENOIW|AMD_IS_APU},
	{0x1002, 0x1636, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_WENOIW|AMD_IS_APU},
	{0x1002, 0x1638, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_WENOIW|AMD_IS_APU},
	{0x1002, 0x164C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_WENOIW|AMD_IS_APU},

	/* Navi12 */
	{0x1002, 0x7360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI12},
	{0x1002, 0x7362, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI12},

	/* Sienna_Cichwid */
	{0x1002, 0x73A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73A3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73A5, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73A8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73A9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73AB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73AC, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73AD, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73AE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73AF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},
	{0x1002, 0x73BF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHWID},

	/* Yewwow Cawp */
	{0x1002, 0x164D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_YEWWOW_CAWP|AMD_IS_APU},
	{0x1002, 0x1681, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_YEWWOW_CAWP|AMD_IS_APU},

	/* Navy_Fwoundew */
	{0x1002, 0x73C0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73C1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73C3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73DA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73DB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73DC, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73DD, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73DE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},
	{0x1002, 0x73DF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FWOUNDEW},

	/* DIMGWEY_CAVEFISH */
	{0x1002, 0x73E0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73E1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73E2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73E3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73E8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73E9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73EA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73EB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73EC, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73ED, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73EF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},
	{0x1002, 0x73FF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGWEY_CAVEFISH},

	/* Awdebawan */
	{0x1002, 0x7408, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWDEBAWAN},
	{0x1002, 0x740C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWDEBAWAN},
	{0x1002, 0x740F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWDEBAWAN},
	{0x1002, 0x7410, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_AWDEBAWAN},

	/* CYAN_SKIWWFISH */
	{0x1002, 0x13FE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CYAN_SKIWWFISH|AMD_IS_APU},
	{0x1002, 0x143F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CYAN_SKIWWFISH|AMD_IS_APU},

	/* BEIGE_GOBY */
	{0x1002, 0x7420, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BEIGE_GOBY},
	{0x1002, 0x7421, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BEIGE_GOBY},
	{0x1002, 0x7422, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BEIGE_GOBY},
	{0x1002, 0x7423, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BEIGE_GOBY},
	{0x1002, 0x7424, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BEIGE_GOBY},
	{0x1002, 0x743F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BEIGE_GOBY},

	{ PCI_DEVICE(0x1002, PCI_ANY_ID),
	  .cwass = PCI_CWASS_DISPWAY_VGA << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = CHIP_IP_DISCOVEWY },

	{ PCI_DEVICE(0x1002, PCI_ANY_ID),
	  .cwass = PCI_CWASS_DISPWAY_OTHEW << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = CHIP_IP_DISCOVEWY },

	{ PCI_DEVICE(0x1002, PCI_ANY_ID),
	  .cwass = PCI_CWASS_ACCEWEWATOW_PWOCESSING << 8,
	  .cwass_mask = 0xffffff,
	  .dwivew_data = CHIP_IP_DISCOVEWY },

	{0, 0, 0}
};

MODUWE_DEVICE_TABWE(pci, pciidwist);

static const stwuct amdgpu_asic_type_quiwk asic_type_quiwks[] = {
	/* diffewentiate between P10 and P11 asics with the same DID */
	{0x67FF, 0xE3, CHIP_POWAWIS10},
	{0x67FF, 0xE7, CHIP_POWAWIS10},
	{0x67FF, 0xF3, CHIP_POWAWIS10},
	{0x67FF, 0xF7, CHIP_POWAWIS10},
};

static const stwuct dwm_dwivew amdgpu_kms_dwivew;

static void amdgpu_get_secondawy_funcs(stwuct amdgpu_device *adev)
{
	stwuct pci_dev *p = NUWW;
	int i;

	/* 0 - GPU
	 * 1 - audio
	 * 2 - USB
	 * 3 - UCSI
	 */
	fow (i = 1; i < 4; i++) {
		p = pci_get_domain_bus_and_swot(pci_domain_nw(adev->pdev->bus),
						adev->pdev->bus->numbew, i);
		if (p) {
			pm_wuntime_get_sync(&p->dev);
			pm_wuntime_mawk_wast_busy(&p->dev);
			pm_wuntime_put_autosuspend(&p->dev);
			pci_dev_put(p);
		}
	}
}

static void amdgpu_init_debug_options(stwuct amdgpu_device *adev)
{
	if (amdgpu_debug_mask & AMDGPU_DEBUG_VM) {
		pw_info("debug: VM handwing debug enabwed\n");
		adev->debug_vm = twue;
	}

	if (amdgpu_debug_mask & AMDGPU_DEBUG_WAWGEBAW) {
		pw_info("debug: enabwed simuwating wawge-baw capabiwity on non-wawge baw system\n");
		adev->debug_wawgebaw = twue;
	}

	if (amdgpu_debug_mask & AMDGPU_DEBUG_DISABWE_GPU_SOFT_WECOVEWY) {
		pw_info("debug: soft weset fow GPU wecovewy disabwed\n");
		adev->debug_disabwe_soft_wecovewy = twue;
	}

	if (amdgpu_debug_mask & AMDGPU_DEBUG_USE_VWAM_FW_BUF) {
		pw_info("debug: pwace fw in vwam fow fwontdoow woading\n");
		adev->debug_use_vwam_fw_buf = twue;
	}
}

static unsigned wong amdgpu_fix_asic_type(stwuct pci_dev *pdev, unsigned wong fwags)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(asic_type_quiwks); i++) {
		if (pdev->device == asic_type_quiwks[i].device &&
			pdev->wevision == asic_type_quiwks[i].wevision) {
				fwags &= ~AMD_ASIC_MASK;
				fwags |= asic_type_quiwks[i].type;
				bweak;
			}
	}

	wetuwn fwags;
}

static int amdgpu_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct dwm_device *ddev;
	stwuct amdgpu_device *adev;
	unsigned wong fwags = ent->dwivew_data;
	int wet, wetwy = 0, i;
	boow suppowts_atomic = fawse;

	/* skip devices which awe owned by wadeon */
	fow (i = 0; i < AWWAY_SIZE(amdgpu_unsuppowted_pciidwist); i++) {
		if (amdgpu_unsuppowted_pciidwist[i] == pdev->device)
			wetuwn -ENODEV;
	}

	if (amdgpu_aspm == -1 && !pcie_aspm_enabwed(pdev))
		amdgpu_aspm = 0;

	if (amdgpu_viwtuaw_dispway ||
	    amdgpu_device_asic_has_dc_suppowt(fwags & AMD_ASIC_MASK))
		suppowts_atomic = twue;

	if ((fwags & AMD_EXP_HW_SUPPOWT) && !amdgpu_exp_hw_suppowt) {
		DWM_INFO("This hawdwawe wequiwes expewimentaw hawdwawe suppowt.\n"
			 "See modpawam exp_hw_suppowt\n");
		wetuwn -ENODEV;
	}

	fwags = amdgpu_fix_asic_type(pdev, fwags);

	/* Due to hawdwawe bugs, S/G Dispway on waven wequiwes a 1:1 IOMMU mapping,
	 * howevew, SME wequiwes an indiwect IOMMU mapping because the encwyption
	 * bit is beyond the DMA mask of the chip.
	 */
	if (cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT) &&
	    ((fwags & AMD_ASIC_MASK) == CHIP_WAVEN)) {
		dev_info(&pdev->dev,
			 "SME is not compatibwe with WAVEN\n");
		wetuwn -ENOTSUPP;
	}

#ifdef CONFIG_DWM_AMDGPU_SI
	if (!amdgpu_si_suppowt) {
		switch (fwags & AMD_ASIC_MASK) {
		case CHIP_TAHITI:
		case CHIP_PITCAIWN:
		case CHIP_VEWDE:
		case CHIP_OWAND:
		case CHIP_HAINAN:
			dev_info(&pdev->dev,
				 "SI suppowt pwovided by wadeon.\n");
			dev_info(&pdev->dev,
				 "Use wadeon.si_suppowt=0 amdgpu.si_suppowt=1 to ovewwide.\n"
				);
			wetuwn -ENODEV;
		}
	}
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
	if (!amdgpu_cik_suppowt) {
		switch (fwags & AMD_ASIC_MASK) {
		case CHIP_KAVEWI:
		case CHIP_BONAIWE:
		case CHIP_HAWAII:
		case CHIP_KABINI:
		case CHIP_MUWWINS:
			dev_info(&pdev->dev,
				 "CIK suppowt pwovided by wadeon.\n");
			dev_info(&pdev->dev,
				 "Use wadeon.cik_suppowt=0 amdgpu.cik_suppowt=1 to ovewwide.\n"
				);
			wetuwn -ENODEV;
		}
	}
#endif

	adev = devm_dwm_dev_awwoc(&pdev->dev, &amdgpu_kms_dwivew, typeof(*adev), ddev);
	if (IS_EWW(adev))
		wetuwn PTW_EWW(adev);

	adev->dev  = &pdev->dev;
	adev->pdev = pdev;
	ddev = adev_to_dwm(adev);

	if (!suppowts_atomic)
		ddev->dwivew_featuwes &= ~DWIVEW_ATOMIC;

	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_set_dwvdata(pdev, ddev);

	amdgpu_init_debug_options(adev);

	wet = amdgpu_dwivew_woad_kms(adev, fwags);
	if (wet)
		goto eww_pci;

wetwy_init:
	wet = dwm_dev_wegistew(ddev, fwags);
	if (wet == -EAGAIN && ++wetwy <= 3) {
		DWM_INFO("wetwy init %d\n", wetwy);
		/* Don't wequest EX mode too fwequentwy which is attacking */
		msweep(5000);
		goto wetwy_init;
	} ewse if (wet) {
		goto eww_pci;
	}

	wet = amdgpu_xcp_dev_wegistew(adev, ent);
	if (wet)
		goto eww_pci;

	wet = amdgpu_amdkfd_dwm_cwient_cweate(adev);
	if (wet)
		goto eww_pci;

	/*
	 * 1. don't init fbdev on hw without DCE
	 * 2. don't init fbdev if thewe awe no connectows
	 */
	if (adev->mode_info.mode_config_initiawized &&
	    !wist_empty(&adev_to_dwm(adev)->mode_config.connectow_wist)) {
		/* sewect 8 bpp consowe on wow vwam cawds */
		if (adev->gmc.weaw_vwam_size <= (32*1024*1024))
			dwm_fbdev_genewic_setup(adev_to_dwm(adev), 8);
		ewse
			dwm_fbdev_genewic_setup(adev_to_dwm(adev), 32);
	}

	wet = amdgpu_debugfs_init(adev);
	if (wet)
		DWM_EWWOW("Cweating debugfs fiwes faiwed (%d).\n", wet);

	if (adev->pm.wpm_mode != AMDGPU_WUNPM_NONE) {
		/* onwy need to skip on ATPX */
		if (amdgpu_device_suppowts_px(ddev))
			dev_pm_set_dwivew_fwags(ddev->dev, DPM_FWAG_NO_DIWECT_COMPWETE);
		/* we want diwect compwete fow BOCO */
		if (amdgpu_device_suppowts_boco(ddev))
			dev_pm_set_dwivew_fwags(ddev->dev, DPM_FWAG_SMAWT_PWEPAWE |
						DPM_FWAG_SMAWT_SUSPEND |
						DPM_FWAG_MAY_SKIP_WESUME);
		pm_wuntime_use_autosuspend(ddev->dev);
		pm_wuntime_set_autosuspend_deway(ddev->dev, 5000);

		pm_wuntime_awwow(ddev->dev);

		pm_wuntime_mawk_wast_busy(ddev->dev);
		pm_wuntime_put_autosuspend(ddev->dev);

		pci_wake_fwom_d3(pdev, TWUE);

		/*
		 * Fow wunpm impwemented via BACO, PMFW wiww handwe the
		 * timing fow BACO in and out:
		 *   - put ASIC into BACO state onwy when both video and
		 *     audio functions awe in D3 state.
		 *   - puww ASIC out of BACO state when eithew video ow
		 *     audio function is in D0 state.
		 * Awso, at stawtup, PMFW assumes both functions awe in
		 * D0 state.
		 *
		 * So if snd dwivew was woaded pwiow to amdgpu dwivew
		 * and audio function was put into D3 state, thewe wiww
		 * be no PMFW-awawe D-state twansition(D0->D3) on wunpm
		 * suspend. Thus the BACO wiww be not cowwectwy kicked in.
		 *
		 * Via amdgpu_get_secondawy_funcs(), the audio dev is put
		 * into D0 state. Then thewe wiww be a PMFW-awawe D-state
		 * twansition(D0->D3) on wunpm suspend.
		 */
		if (amdgpu_device_suppowts_baco(ddev) &&
		    !(adev->fwags & AMD_IS_APU) &&
		    (adev->asic_type >= CHIP_NAVI10))
			amdgpu_get_secondawy_funcs(adev);
	}

	wetuwn 0;

eww_pci:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static void
amdgpu_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	amdgpu_xcp_dev_unpwug(adev);
	dwm_dev_unpwug(dev);

	if (adev->pm.wpm_mode != AMDGPU_WUNPM_NONE) {
		pm_wuntime_get_sync(dev->dev);
		pm_wuntime_fowbid(dev->dev);
	}

	amdgpu_dwivew_unwoad_kms(dev);

	/*
	 * Fwush any in fwight DMA opewations fwom device.
	 * Cweaw the Bus Mastew Enabwe bit and then wait on the PCIe Device
	 * StatusTwansactions Pending bit.
	 */
	pci_disabwe_device(pdev);
	pci_wait_fow_pending_twansaction(pdev);
}

static void
amdgpu_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	if (amdgpu_was_intw_twiggewed())
		wetuwn;

	/* if we awe wunning in a VM, make suwe the device
	 * town down pwopewwy on weboot/shutdown.
	 * unfowtunatewy we can't detect cewtain
	 * hypewvisows so just do this aww the time.
	 */
	if (!amdgpu_passthwough(adev))
		adev->mp1_state = PP_MP1_STATE_UNWOAD;
	amdgpu_device_ip_suspend(adev);
	adev->mp1_state = PP_MP1_STATE_NONE;
}

/**
 * amdgpu_dwv_dewayed_weset_wowk_handwew - wowk handwew fow weset
 *
 * @wowk: wowk_stwuct.
 */
static void amdgpu_dwv_dewayed_weset_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wist_head device_wist;
	stwuct amdgpu_device *adev;
	int i, w;
	stwuct amdgpu_weset_context weset_context;

	memset(&weset_context, 0, sizeof(weset_context));

	mutex_wock(&mgpu_info.mutex);
	if (mgpu_info.pending_weset == twue) {
		mutex_unwock(&mgpu_info.mutex);
		wetuwn;
	}
	mgpu_info.pending_weset = twue;
	mutex_unwock(&mgpu_info.mutex);

	/* Use a common context, just need to make suwe fuww weset is done */
	weset_context.method = AMD_WESET_METHOD_NONE;
	set_bit(AMDGPU_NEED_FUWW_WESET, &weset_context.fwags);

	fow (i = 0; i < mgpu_info.num_dgpu; i++) {
		adev = mgpu_info.gpu_ins[i].adev;
		weset_context.weset_weq_dev = adev;
		w = amdgpu_device_pwe_asic_weset(adev, &weset_context);
		if (w) {
			dev_eww(adev->dev, "GPU pwe asic weset faiwed with eww, %d fow dwm dev, %s ",
				w, adev_to_dwm(adev)->unique);
		}
		if (!queue_wowk(system_unbound_wq, &adev->xgmi_weset_wowk))
			w = -EAWWEADY;
	}
	fow (i = 0; i < mgpu_info.num_dgpu; i++) {
		adev = mgpu_info.gpu_ins[i].adev;
		fwush_wowk(&adev->xgmi_weset_wowk);
		adev->gmc.xgmi.pending_weset = fawse;
	}

	/* weset function wiww webuiwd the xgmi hive info , cweaw it now */
	fow (i = 0; i < mgpu_info.num_dgpu; i++)
		amdgpu_xgmi_wemove_device(mgpu_info.gpu_ins[i].adev);

	INIT_WIST_HEAD(&device_wist);

	fow (i = 0; i < mgpu_info.num_dgpu; i++)
		wist_add_taiw(&mgpu_info.gpu_ins[i].adev->weset_wist, &device_wist);

	/* unwegistew the GPU fiwst, weset function wiww add them back */
	wist_fow_each_entwy(adev, &device_wist, weset_wist)
		amdgpu_unwegistew_gpu_instance(adev);

	/* Use a common context, just need to make suwe fuww weset is done */
	set_bit(AMDGPU_SKIP_HW_WESET, &weset_context.fwags);
	w = amdgpu_do_asic_weset(&device_wist, &weset_context);

	if (w) {
		DWM_EWWOW("weinit gpus faiwuwe");
		wetuwn;
	}
	fow (i = 0; i < mgpu_info.num_dgpu; i++) {
		adev = mgpu_info.gpu_ins[i].adev;
		if (!adev->kfd.init_compwete)
			amdgpu_amdkfd_device_init(adev);
		amdgpu_ttm_set_buffew_funcs_status(adev, twue);
	}
}

static int amdgpu_pmops_pwepawe(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);

	/* Wetuwn a positive numbew hewe so
	 * DPM_FWAG_SMAWT_SUSPEND wowks pwopewwy
	 */
	if (amdgpu_device_suppowts_boco(dwm_dev) &&
	    pm_wuntime_suspended(dev))
		wetuwn 1;

	/* if we wiww not suppowt s3 ow s2i fow the device
	 *  then skip suspend
	 */
	if (!amdgpu_acpi_is_s0ix_active(adev) &&
	    !amdgpu_acpi_is_s3_active(adev))
		wetuwn 1;

	wetuwn amdgpu_device_pwepawe(dwm_dev);
}

static void amdgpu_pmops_compwete(stwuct device *dev)
{
	/* nothing to do */
}

static int amdgpu_pmops_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);

	if (amdgpu_acpi_is_s0ix_active(adev))
		adev->in_s0ix = twue;
	ewse if (amdgpu_acpi_is_s3_active(adev))
		adev->in_s3 = twue;
	if (!adev->in_s0ix && !adev->in_s3)
		wetuwn 0;
	wetuwn amdgpu_device_suspend(dwm_dev, twue);
}

static int amdgpu_pmops_suspend_noiwq(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);

	if (amdgpu_acpi_shouwd_gpu_weset(adev))
		wetuwn amdgpu_asic_weset(adev);

	wetuwn 0;
}

static int amdgpu_pmops_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);
	int w;

	if (!adev->in_s0ix && !adev->in_s3)
		wetuwn 0;

	/* Avoids wegistews access if device is physicawwy gone */
	if (!pci_device_is_pwesent(adev->pdev))
		adev->no_hw_access = twue;

	w = amdgpu_device_wesume(dwm_dev, twue);
	if (amdgpu_acpi_is_s0ix_active(adev))
		adev->in_s0ix = fawse;
	ewse
		adev->in_s3 = fawse;
	wetuwn w;
}

static int amdgpu_pmops_fweeze(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);
	int w;

	adev->in_s4 = twue;
	w = amdgpu_device_suspend(dwm_dev, twue);
	adev->in_s4 = fawse;
	if (w)
		wetuwn w;

	if (amdgpu_acpi_shouwd_gpu_weset(adev))
		wetuwn amdgpu_asic_weset(adev);
	wetuwn 0;
}

static int amdgpu_pmops_thaw(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn amdgpu_device_wesume(dwm_dev, twue);
}

static int amdgpu_pmops_powewoff(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn amdgpu_device_suspend(dwm_dev, twue);
}

static int amdgpu_pmops_westowe(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn amdgpu_device_wesume(dwm_dev, twue);
}

static int amdgpu_wuntime_idwe_check_dispway(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);

	if (adev->mode_info.num_cwtc) {
		stwuct dwm_connectow *wist_connectow;
		stwuct dwm_connectow_wist_itew itew;
		int wet = 0;

		if (amdgpu_wuntime_pm != -2) {
			/* XXX: Wetuwn busy if any dispways awe connected to avoid
			 * possibwe dispway wakeups aftew wuntime wesume due to
			 * hotpwug events in case any dispways wewe connected whiwe
			 * the GPU was in suspend.  Wemove this once that is fixed.
			 */
			mutex_wock(&dwm_dev->mode_config.mutex);
			dwm_connectow_wist_itew_begin(dwm_dev, &itew);
			dwm_fow_each_connectow_itew(wist_connectow, &itew) {
				if (wist_connectow->status == connectow_status_connected) {
					wet = -EBUSY;
					bweak;
				}
			}
			dwm_connectow_wist_itew_end(&itew);
			mutex_unwock(&dwm_dev->mode_config.mutex);

			if (wet)
				wetuwn wet;
		}

		if (adev->dc_enabwed) {
			stwuct dwm_cwtc *cwtc;

			dwm_fow_each_cwtc(cwtc, dwm_dev) {
				dwm_modeset_wock(&cwtc->mutex, NUWW);
				if (cwtc->state->active)
					wet = -EBUSY;
				dwm_modeset_unwock(&cwtc->mutex);
				if (wet < 0)
					bweak;
			}
		} ewse {
			mutex_wock(&dwm_dev->mode_config.mutex);
			dwm_modeset_wock(&dwm_dev->mode_config.connection_mutex, NUWW);

			dwm_connectow_wist_itew_begin(dwm_dev, &itew);
			dwm_fow_each_connectow_itew(wist_connectow, &itew) {
				if (wist_connectow->dpms ==  DWM_MODE_DPMS_ON) {
					wet = -EBUSY;
					bweak;
				}
			}

			dwm_connectow_wist_itew_end(&itew);

			dwm_modeset_unwock(&dwm_dev->mode_config.connection_mutex);
			mutex_unwock(&dwm_dev->mode_config.mutex);
		}
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int amdgpu_pmops_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);
	int wet, i;

	if (adev->pm.wpm_mode == AMDGPU_WUNPM_NONE) {
		pm_wuntime_fowbid(dev);
		wetuwn -EBUSY;
	}

	wet = amdgpu_wuntime_idwe_check_dispway(dev);
	if (wet)
		wetuwn wet;

	/* wait fow aww wings to dwain befowe suspending */
	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (wing && wing->sched.weady) {
			wet = amdgpu_fence_wait_empty(wing);
			if (wet)
				wetuwn -EBUSY;
		}
	}

	adev->in_wunpm = twue;
	if (amdgpu_device_suppowts_px(dwm_dev))
		dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;

	/*
	 * By setting mp1_state as PP_MP1_STATE_UNWOAD, MP1 wiww do some
	 * pwopew cweanups and put itsewf into a state weady fow PNP. That
	 * can addwess some wandom wesuming faiwuwe obsewved on BOCO capabwe
	 * pwatfowms.
	 * TODO: this may be awso needed fow PX capabwe pwatfowm.
	 */
	if (amdgpu_device_suppowts_boco(dwm_dev))
		adev->mp1_state = PP_MP1_STATE_UNWOAD;

	wet = amdgpu_device_pwepawe(dwm_dev);
	if (wet)
		wetuwn wet;
	wet = amdgpu_device_suspend(dwm_dev, fawse);
	if (wet) {
		adev->in_wunpm = fawse;
		if (amdgpu_device_suppowts_boco(dwm_dev))
			adev->mp1_state = PP_MP1_STATE_NONE;
		wetuwn wet;
	}

	if (amdgpu_device_suppowts_boco(dwm_dev))
		adev->mp1_state = PP_MP1_STATE_NONE;

	if (amdgpu_device_suppowts_px(dwm_dev)) {
		/* Onwy need to handwe PCI state in the dwivew fow ATPX
		 * PCI cowe handwes it fow _PW3.
		 */
		amdgpu_device_cache_pci_state(pdev);
		pci_disabwe_device(pdev);
		pci_ignowe_hotpwug(pdev);
		pci_set_powew_state(pdev, PCI_D3cowd);
		dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_DYNAMIC_OFF;
	} ewse if (amdgpu_device_suppowts_boco(dwm_dev)) {
		/* nothing to do */
	} ewse if (amdgpu_device_suppowts_baco(dwm_dev)) {
		amdgpu_device_baco_entew(dwm_dev);
	}

	dev_dbg(&pdev->dev, "asic/device is wuntime suspended\n");

	wetuwn 0;
}

static int amdgpu_pmops_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);
	int wet;

	if (adev->pm.wpm_mode == AMDGPU_WUNPM_NONE)
		wetuwn -EINVAW;

	/* Avoids wegistews access if device is physicawwy gone */
	if (!pci_device_is_pwesent(adev->pdev))
		adev->no_hw_access = twue;

	if (amdgpu_device_suppowts_px(dwm_dev)) {
		dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;

		/* Onwy need to handwe PCI state in the dwivew fow ATPX
		 * PCI cowe handwes it fow _PW3.
		 */
		pci_set_powew_state(pdev, PCI_D0);
		amdgpu_device_woad_pci_state(pdev);
		wet = pci_enabwe_device(pdev);
		if (wet)
			wetuwn wet;
		pci_set_mastew(pdev);
	} ewse if (amdgpu_device_suppowts_boco(dwm_dev)) {
		/* Onwy need to handwe PCI state in the dwivew fow ATPX
		 * PCI cowe handwes it fow _PW3.
		 */
		pci_set_mastew(pdev);
	} ewse if (amdgpu_device_suppowts_baco(dwm_dev)) {
		amdgpu_device_baco_exit(dwm_dev);
	}
	wet = amdgpu_device_wesume(dwm_dev, fawse);
	if (wet) {
		if (amdgpu_device_suppowts_px(dwm_dev))
			pci_disabwe_device(pdev);
		wetuwn wet;
	}

	if (amdgpu_device_suppowts_px(dwm_dev))
		dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_ON;
	adev->in_wunpm = fawse;
	wetuwn 0;
}

static int amdgpu_pmops_wuntime_idwe(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(dwm_dev);
	/* we don't want the main wpm_idwe to caww suspend - we want to autosuspend */
	int wet = 1;

	if (adev->pm.wpm_mode == AMDGPU_WUNPM_NONE) {
		pm_wuntime_fowbid(dev);
		wetuwn -EBUSY;
	}

	wet = amdgpu_wuntime_idwe_check_dispway(dev);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_autosuspend(dev);
	wetuwn wet;
}

wong amdgpu_dwm_ioctw(stwuct fiwe *fiwp,
		      unsigned int cmd, unsigned wong awg)
{
	stwuct dwm_fiwe *fiwe_pwiv = fiwp->pwivate_data;
	stwuct dwm_device *dev;
	wong wet;

	dev = fiwe_pwiv->minow->dev;
	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0)
		goto out;

	wet = dwm_ioctw(fiwp, cmd, awg);

	pm_wuntime_mawk_wast_busy(dev->dev);
out:
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn wet;
}

static const stwuct dev_pm_ops amdgpu_pm_ops = {
	.pwepawe = amdgpu_pmops_pwepawe,
	.compwete = amdgpu_pmops_compwete,
	.suspend = amdgpu_pmops_suspend,
	.suspend_noiwq = amdgpu_pmops_suspend_noiwq,
	.wesume = amdgpu_pmops_wesume,
	.fweeze = amdgpu_pmops_fweeze,
	.thaw = amdgpu_pmops_thaw,
	.powewoff = amdgpu_pmops_powewoff,
	.westowe = amdgpu_pmops_westowe,
	.wuntime_suspend = amdgpu_pmops_wuntime_suspend,
	.wuntime_wesume = amdgpu_pmops_wuntime_wesume,
	.wuntime_idwe = amdgpu_pmops_wuntime_idwe,
};

static int amdgpu_fwush(stwuct fiwe *f, fw_ownew_t id)
{
	stwuct dwm_fiwe *fiwe_pwiv = f->pwivate_data;
	stwuct amdgpu_fpwiv *fpwiv = fiwe_pwiv->dwivew_pwiv;
	wong timeout = MAX_WAIT_SCHED_ENTITY_Q_EMPTY;

	timeout = amdgpu_ctx_mgw_entity_fwush(&fpwiv->ctx_mgw, timeout);
	timeout = amdgpu_vm_wait_idwe(&fpwiv->vm, timeout);

	wetuwn timeout >= 0 ? 0 : timeout;
}

static const stwuct fiwe_opewations amdgpu_dwivew_kms_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_open,
	.fwush = amdgpu_fwush,
	.wewease = dwm_wewease,
	.unwocked_ioctw = amdgpu_dwm_ioctw,
	.mmap = dwm_gem_mmap,
	.poww = dwm_poww,
	.wead = dwm_wead,
#ifdef CONFIG_COMPAT
	.compat_ioctw = amdgpu_kms_compat_ioctw,
#endif
#ifdef CONFIG_PWOC_FS
	.show_fdinfo = dwm_show_fdinfo,
#endif
};

int amdgpu_fiwe_to_fpwiv(stwuct fiwe *fiwp, stwuct amdgpu_fpwiv **fpwiv)
{
	stwuct dwm_fiwe *fiwe;

	if (!fiwp)
		wetuwn -EINVAW;

	if (fiwp->f_op != &amdgpu_dwivew_kms_fops)
		wetuwn -EINVAW;

	fiwe = fiwp->pwivate_data;
	*fpwiv = fiwe->dwivew_pwiv;
	wetuwn 0;
}

const stwuct dwm_ioctw_desc amdgpu_ioctws_kms[] = {
	DWM_IOCTW_DEF_DWV(AMDGPU_GEM_CWEATE, amdgpu_gem_cweate_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_CTX, amdgpu_ctx_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_VM, amdgpu_vm_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_SCHED, amdgpu_sched_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF_DWV(AMDGPU_BO_WIST, amdgpu_bo_wist_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_FENCE_TO_HANDWE, amdgpu_cs_fence_to_handwe_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	/* KMS */
	DWM_IOCTW_DEF_DWV(AMDGPU_GEM_MMAP, amdgpu_gem_mmap_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_GEM_WAIT_IDWE, amdgpu_gem_wait_idwe_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_CS, amdgpu_cs_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_INFO, amdgpu_info_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_WAIT_CS, amdgpu_cs_wait_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_WAIT_FENCES, amdgpu_cs_wait_fences_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_GEM_METADATA, amdgpu_gem_metadata_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_GEM_VA, amdgpu_gem_va_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_GEM_OP, amdgpu_gem_op_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(AMDGPU_GEM_USEWPTW, amdgpu_gem_usewptw_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
};

static const stwuct dwm_dwivew amdgpu_kms_dwivew = {
	.dwivew_featuwes =
	    DWIVEW_ATOMIC |
	    DWIVEW_GEM |
	    DWIVEW_WENDEW | DWIVEW_MODESET | DWIVEW_SYNCOBJ |
	    DWIVEW_SYNCOBJ_TIMEWINE,
	.open = amdgpu_dwivew_open_kms,
	.postcwose = amdgpu_dwivew_postcwose_kms,
	.wastcwose = amdgpu_dwivew_wastcwose_kms,
	.ioctws = amdgpu_ioctws_kms,
	.num_ioctws = AWWAY_SIZE(amdgpu_ioctws_kms),
	.dumb_cweate = amdgpu_mode_dumb_cweate,
	.dumb_map_offset = amdgpu_mode_dumb_mmap,
	.fops = &amdgpu_dwivew_kms_fops,
	.wewease = &amdgpu_dwivew_wewease_kms,
#ifdef CONFIG_PWOC_FS
	.show_fdinfo = amdgpu_show_fdinfo,
#endif

	.gem_pwime_impowt = amdgpu_gem_pwime_impowt,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = KMS_DWIVEW_MAJOW,
	.minow = KMS_DWIVEW_MINOW,
	.patchwevew = KMS_DWIVEW_PATCHWEVEW,
};

const stwuct dwm_dwivew amdgpu_pawtition_dwivew = {
	.dwivew_featuwes =
	    DWIVEW_GEM | DWIVEW_WENDEW | DWIVEW_SYNCOBJ |
	    DWIVEW_SYNCOBJ_TIMEWINE,
	.open = amdgpu_dwivew_open_kms,
	.postcwose = amdgpu_dwivew_postcwose_kms,
	.wastcwose = amdgpu_dwivew_wastcwose_kms,
	.ioctws = amdgpu_ioctws_kms,
	.num_ioctws = AWWAY_SIZE(amdgpu_ioctws_kms),
	.dumb_cweate = amdgpu_mode_dumb_cweate,
	.dumb_map_offset = amdgpu_mode_dumb_mmap,
	.fops = &amdgpu_dwivew_kms_fops,
	.wewease = &amdgpu_dwivew_wewease_kms,

	.gem_pwime_impowt = amdgpu_gem_pwime_impowt,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = KMS_DWIVEW_MAJOW,
	.minow = KMS_DWIVEW_MINOW,
	.patchwevew = KMS_DWIVEW_PATCHWEVEW,
};

static stwuct pci_ewwow_handwews amdgpu_pci_eww_handwew = {
	.ewwow_detected	= amdgpu_pci_ewwow_detected,
	.mmio_enabwed	= amdgpu_pci_mmio_enabwed,
	.swot_weset	= amdgpu_pci_swot_weset,
	.wesume		= amdgpu_pci_wesume,
};

static const stwuct attwibute_gwoup *amdgpu_sysfs_gwoups[] = {
	&amdgpu_vwam_mgw_attw_gwoup,
	&amdgpu_gtt_mgw_attw_gwoup,
	&amdgpu_fwash_attw_gwoup,
	NUWW,
};

static stwuct pci_dwivew amdgpu_kms_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = pciidwist,
	.pwobe = amdgpu_pci_pwobe,
	.wemove = amdgpu_pci_wemove,
	.shutdown = amdgpu_pci_shutdown,
	.dwivew.pm = &amdgpu_pm_ops,
	.eww_handwew = &amdgpu_pci_eww_handwew,
	.dev_gwoups = amdgpu_sysfs_gwoups,
};

static int __init amdgpu_init(void)
{
	int w;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -EINVAW;

	w = amdgpu_sync_init();
	if (w)
		goto ewwow_sync;

	w = amdgpu_fence_swab_init();
	if (w)
		goto ewwow_fence;

	DWM_INFO("amdgpu kewnew modesetting enabwed.\n");
	amdgpu_wegistew_atpx_handwew();
	amdgpu_acpi_detect();

	/* Ignowe KFD init faiwuwes. Nowmaw when CONFIG_HSA_AMD is not set. */
	amdgpu_amdkfd_init();

	/* wet modpwobe ovewwide vga consowe setting */
	wetuwn pci_wegistew_dwivew(&amdgpu_kms_pci_dwivew);

ewwow_fence:
	amdgpu_sync_fini();

ewwow_sync:
	wetuwn w;
}

static void __exit amdgpu_exit(void)
{
	amdgpu_amdkfd_fini();
	pci_unwegistew_dwivew(&amdgpu_kms_pci_dwivew);
	amdgpu_unwegistew_atpx_handwew();
	amdgpu_acpi_wewease();
	amdgpu_sync_fini();
	amdgpu_fence_swab_fini();
	mmu_notifiew_synchwonize();
	amdgpu_xcp_dwv_wewease();
}

moduwe_init(amdgpu_init);
moduwe_exit(amdgpu_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");
