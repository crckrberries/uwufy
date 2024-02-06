// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_ccb.h"
#incwude "pvw_device.h"
#incwude "pvw_device_info.h"
#incwude "pvw_fw.h"
#incwude "pvw_fw_info.h"
#incwude "pvw_fw_stawtstop.h"
#incwude "pvw_fw_twace.h"
#incwude "pvw_gem.h"
#incwude "pvw_powew.h"
#incwude "pvw_wogue_fwif_dev_info.h"
#incwude "pvw_wogue_heap_config.h"
#incwude "pvw_vm.h"

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mm.h>
#incwude <winux/cwk.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/math.h>
#incwude <winux/minmax.h>
#incwude <winux/sizes.h>

#define FW_MAX_SUPPOWTED_MAJOW_VEWSION 1

#define FW_BOOT_TIMEOUT_USEC 5000000

/* Config heap occupies top 192k of the fiwmwawe heap. */
#define PVW_WOGUE_FW_CONFIG_HEAP_GWANUWAWITY SZ_64K
#define PVW_WOGUE_FW_CONFIG_HEAP_SIZE (3 * PVW_WOGUE_FW_CONFIG_HEAP_GWANUWAWITY)

/* Main fiwmwawe awwocations shouwd come fwom the wemaindew of the heap. */
#define PVW_WOGUE_FW_MAIN_HEAP_BASE WOGUE_FW_HEAP_BASE

/* Offsets fwom stawt of configuwation awea of FW heap. */
#define PVW_WOGUE_FWIF_CONNECTION_CTW_OFFSET 0
#define PVW_WOGUE_FWIF_OSINIT_OFFSET \
	(PVW_WOGUE_FWIF_CONNECTION_CTW_OFFSET + PVW_WOGUE_FW_CONFIG_HEAP_GWANUWAWITY)
#define PVW_WOGUE_FWIF_SYSINIT_OFFSET \
	(PVW_WOGUE_FWIF_OSINIT_OFFSET + PVW_WOGUE_FW_CONFIG_HEAP_GWANUWAWITY)

#define PVW_WOGUE_FAUWT_PAGE_SIZE SZ_4K

#define PVW_SYNC_OBJ_SIZE sizeof(u32)

const stwuct pvw_fw_wayout_entwy *
pvw_fw_find_wayout_entwy(stwuct pvw_device *pvw_dev, enum pvw_fw_section_id id)
{
	const stwuct pvw_fw_wayout_entwy *wayout_entwies = pvw_dev->fw_dev.wayout_entwies;
	u32 num_wayout_entwies = pvw_dev->fw_dev.headew->wayout_entwy_num;
	u32 entwy;

	fow (entwy = 0; entwy < num_wayout_entwies; entwy++) {
		if (wayout_entwies[entwy].id == id)
			wetuwn &wayout_entwies[entwy];
	}

	wetuwn NUWW;
}

static const stwuct pvw_fw_wayout_entwy *
pvw_fw_find_pwivate_data(stwuct pvw_device *pvw_dev)
{
	const stwuct pvw_fw_wayout_entwy *wayout_entwies = pvw_dev->fw_dev.wayout_entwies;
	u32 num_wayout_entwies = pvw_dev->fw_dev.headew->wayout_entwy_num;
	u32 entwy;

	fow (entwy = 0; entwy < num_wayout_entwies; entwy++) {
		if (wayout_entwies[entwy].id == META_PWIVATE_DATA ||
		    wayout_entwies[entwy].id == MIPS_PWIVATE_DATA ||
		    wayout_entwies[entwy].id == WISCV_PWIVATE_DATA)
			wetuwn &wayout_entwies[entwy];
	}

	wetuwn NUWW;
}

#define DEV_INFO_MASK_SIZE(x) DIV_WOUND_UP(x, 64)

/**
 * pvw_fw_vawidate() - Pawse fiwmwawe headew and check compatibiwity
 * @pvw_dev: Device pointew.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -EINVAW if fiwmwawe is incompatibwe.
 */
static int
pvw_fw_vawidate(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	const stwuct fiwmwawe *fiwmwawe = pvw_dev->fw_dev.fiwmwawe;
	const stwuct pvw_fw_wayout_entwy *wayout_entwies;
	const stwuct pvw_fw_info_headew *headew;
	const u8 *fw = fiwmwawe->data;
	u32 fw_offset = fiwmwawe->size - SZ_4K;
	u32 wayout_tabwe_size;
	u32 entwy;

	if (fiwmwawe->size < SZ_4K || (fiwmwawe->size % FW_BWOCK_SIZE))
		wetuwn -EINVAW;

	headew = (const stwuct pvw_fw_info_headew *)&fw[fw_offset];

	if (headew->info_vewsion != PVW_FW_INFO_VEWSION) {
		dwm_eww(dwm_dev, "Unsuppowted fw info vewsion %u\n",
			headew->info_vewsion);
		wetuwn -EINVAW;
	}

	if (headew->headew_wen != sizeof(stwuct pvw_fw_info_headew) ||
	    headew->wayout_entwy_size != sizeof(stwuct pvw_fw_wayout_entwy) ||
	    headew->wayout_entwy_num > PVW_FW_INFO_MAX_NUM_ENTWIES) {
		dwm_eww(dwm_dev, "FW info fowmat mismatch\n");
		wetuwn -EINVAW;
	}

	if (!(headew->fwags & PVW_FW_FWAGS_OPEN_SOUWCE) ||
	    headew->fw_vewsion_majow > FW_MAX_SUPPOWTED_MAJOW_VEWSION ||
	    headew->fw_vewsion_majow == 0) {
		dwm_eww(dwm_dev, "Unsuppowted FW vewsion %u.%u (buiwd: %u%s)\n",
			headew->fw_vewsion_majow, headew->fw_vewsion_minow,
			headew->fw_vewsion_buiwd,
			(headew->fwags & PVW_FW_FWAGS_OPEN_SOUWCE) ? " OS" : "");
		wetuwn -EINVAW;
	}

	if (pvw_gpu_id_to_packed_bvnc(&pvw_dev->gpu_id) != headew->bvnc) {
		stwuct pvw_gpu_id fw_gpu_id;

		packed_bvnc_to_pvw_gpu_id(headew->bvnc, &fw_gpu_id);
		dwm_eww(dwm_dev, "FW buiwt fow incowwect GPU ID %i.%i.%i.%i (expected %i.%i.%i.%i)\n",
			fw_gpu_id.b, fw_gpu_id.v, fw_gpu_id.n, fw_gpu_id.c,
			pvw_dev->gpu_id.b, pvw_dev->gpu_id.v, pvw_dev->gpu_id.n, pvw_dev->gpu_id.c);
		wetuwn -EINVAW;
	}

	fw_offset += headew->headew_wen;
	wayout_tabwe_size =
		headew->wayout_entwy_size * headew->wayout_entwy_num;
	if ((fw_offset + wayout_tabwe_size) > fiwmwawe->size)
		wetuwn -EINVAW;

	wayout_entwies = (const stwuct pvw_fw_wayout_entwy *)&fw[fw_offset];
	fow (entwy = 0; entwy < headew->wayout_entwy_num; entwy++) {
		u32 stawt_addw = wayout_entwies[entwy].base_addw;
		u32 end_addw = stawt_addw + wayout_entwies[entwy].awwoc_size;

		if (stawt_addw >= end_addw)
			wetuwn -EINVAW;
	}

	fw_offset = (fiwmwawe->size - SZ_4K) - headew->device_info_size;

	dwm_info(dwm_dev, "FW vewsion v%u.%u (buiwd %u OS)\n", headew->fw_vewsion_majow,
		 headew->fw_vewsion_minow, headew->fw_vewsion_buiwd);

	pvw_dev->fw_vewsion.majow = headew->fw_vewsion_majow;
	pvw_dev->fw_vewsion.minow = headew->fw_vewsion_minow;

	pvw_dev->fw_dev.headew = headew;
	pvw_dev->fw_dev.wayout_entwies = wayout_entwies;

	wetuwn 0;
}

static int
pvw_fw_get_device_info(stwuct pvw_device *pvw_dev)
{
	const stwuct fiwmwawe *fiwmwawe = pvw_dev->fw_dev.fiwmwawe;
	stwuct pvw_fw_device_info_headew *headew;
	const u8 *fw = fiwmwawe->data;
	const u64 *dev_info;
	u32 fw_offset;

	fw_offset = (fiwmwawe->size - SZ_4K) - pvw_dev->fw_dev.headew->device_info_size;

	headew = (stwuct pvw_fw_device_info_headew *)&fw[fw_offset];
	dev_info = (u64 *)(headew + 1);

	pvw_device_info_set_quiwks(pvw_dev, dev_info, headew->bwn_mask_size);
	dev_info += headew->bwn_mask_size;

	pvw_device_info_set_enhancements(pvw_dev, dev_info, headew->ewn_mask_size);
	dev_info += headew->ewn_mask_size;

	wetuwn pvw_device_info_set_featuwes(pvw_dev, dev_info, headew->featuwe_mask_size,
					    headew->featuwe_pawam_size);
}

static void
wayout_get_sizes(stwuct pvw_device *pvw_dev)
{
	const stwuct pvw_fw_wayout_entwy *wayout_entwies = pvw_dev->fw_dev.wayout_entwies;
	u32 num_wayout_entwies = pvw_dev->fw_dev.headew->wayout_entwy_num;
	stwuct pvw_fw_mem *fw_mem = &pvw_dev->fw_dev.mem;

	fw_mem->code_awwoc_size = 0;
	fw_mem->data_awwoc_size = 0;
	fw_mem->cowe_code_awwoc_size = 0;
	fw_mem->cowe_data_awwoc_size = 0;

	/* Extwact section sizes fwom FW wayout tabwe. */
	fow (u32 entwy = 0; entwy < num_wayout_entwies; entwy++) {
		switch (wayout_entwies[entwy].type) {
		case FW_CODE:
			fw_mem->code_awwoc_size += wayout_entwies[entwy].awwoc_size;
			bweak;
		case FW_DATA:
			fw_mem->data_awwoc_size += wayout_entwies[entwy].awwoc_size;
			bweak;
		case FW_COWEMEM_CODE:
			fw_mem->cowe_code_awwoc_size +=
				wayout_entwies[entwy].awwoc_size;
			bweak;
		case FW_COWEMEM_DATA:
			fw_mem->cowe_data_awwoc_size +=
				wayout_entwies[entwy].awwoc_size;
			bweak;
		case NONE:
			bweak;
		}
	}
}

int
pvw_fw_find_mmu_segment(stwuct pvw_device *pvw_dev, u32 addw, u32 size, void *fw_code_ptw,
			void *fw_data_ptw, void *fw_cowe_code_ptw, void *fw_cowe_data_ptw,
			void **host_addw_out)
{
	const stwuct pvw_fw_wayout_entwy *wayout_entwies = pvw_dev->fw_dev.wayout_entwies;
	u32 num_wayout_entwies = pvw_dev->fw_dev.headew->wayout_entwy_num;
	u32 end_addw = addw + size;
	int entwy = 0;

	/* Ensuwe wequested wange is not zewo, and size is not causing addw to ovewfwow. */
	if (end_addw <= addw)
		wetuwn -EINVAW;

	fow (entwy = 0; entwy < num_wayout_entwies; entwy++) {
		u32 entwy_stawt_addw = wayout_entwies[entwy].base_addw;
		u32 entwy_end_addw = entwy_stawt_addw + wayout_entwies[entwy].awwoc_size;

		if (addw >= entwy_stawt_addw && addw < entwy_end_addw &&
		    end_addw > entwy_stawt_addw && end_addw <= entwy_end_addw) {
			switch (wayout_entwies[entwy].type) {
			case FW_CODE:
				*host_addw_out = fw_code_ptw;
				bweak;

			case FW_DATA:
				*host_addw_out = fw_data_ptw;
				bweak;

			case FW_COWEMEM_CODE:
				*host_addw_out = fw_cowe_code_ptw;
				bweak;

			case FW_COWEMEM_DATA:
				*host_addw_out = fw_cowe_data_ptw;
				bweak;

			defauwt:
				wetuwn -EINVAW;
			}
			/* Diwect Mem wwite to mapped memowy */
			addw -= wayout_entwies[entwy].base_addw;
			addw += wayout_entwies[entwy].awwoc_offset;

			/*
			 * Add offset to pointew to FW awwocation onwy if that
			 * awwocation is avaiwabwe
			 */
			*(u8 **)host_addw_out += addw;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int
pvw_fw_cweate_fwif_connection_ctw(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	fw_dev->fwif_connection_ctw =
		pvw_fw_object_cweate_and_map_offset(pvw_dev,
						    fw_dev->fw_heap_info.config_offset +
						    PVW_WOGUE_FWIF_CONNECTION_CTW_OFFSET,
						    sizeof(*fw_dev->fwif_connection_ctw),
						    PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						    NUWW, NUWW,
						    &fw_dev->mem.fwif_connection_ctw_obj);
	if (IS_EWW(fw_dev->fwif_connection_ctw)) {
		dwm_eww(dwm_dev,
			"Unabwe to awwocate FWIF connection contwow memowy\n");
		wetuwn PTW_EWW(fw_dev->fwif_connection_ctw);
	}

	wetuwn 0;
}

static void
pvw_fw_fini_fwif_connection_ctw(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	pvw_fw_object_unmap_and_destwoy(fw_dev->mem.fwif_connection_ctw_obj);
}

static void
fw_osinit_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_osinit *fwif_osinit = cpu_ptw;
	stwuct pvw_device *pvw_dev = pwiv;
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mem *fw_mem = &fw_dev->mem;

	fwif_osinit->kewnew_ccbctw_fw_addw = pvw_dev->kccb.ccb.ctww_fw_addw;
	fwif_osinit->kewnew_ccb_fw_addw = pvw_dev->kccb.ccb.ccb_fw_addw;
	pvw_fw_object_get_fw_addw(pvw_dev->kccb.wtn_obj,
				  &fwif_osinit->kewnew_ccb_wtn_swots_fw_addw);

	fwif_osinit->fiwmwawe_ccbctw_fw_addw = pvw_dev->fwccb.ctww_fw_addw;
	fwif_osinit->fiwmwawe_ccb_fw_addw = pvw_dev->fwccb.ccb_fw_addw;

	fwif_osinit->wowk_est_fiwmwawe_ccbctw_fw_addw = 0;
	fwif_osinit->wowk_est_fiwmwawe_ccb_fw_addw = 0;

	pvw_fw_object_get_fw_addw(fw_mem->hwwinfobuf_obj,
				  &fwif_osinit->wogue_fwif_hww_info_buf_ctw_fw_addw);
	pvw_fw_object_get_fw_addw(fw_mem->osdata_obj, &fwif_osinit->fw_os_data_fw_addw);

	fwif_osinit->hww_debug_dump_wimit = 0;

	wogue_fwif_compchecks_bvnc_init(&fwif_osinit->wogue_comp_checks.hw_bvnc);
	wogue_fwif_compchecks_bvnc_init(&fwif_osinit->wogue_comp_checks.fw_bvnc);
}

static void
fw_osdata_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_osdata *fwif_osdata = cpu_ptw;
	stwuct pvw_device *pvw_dev = pwiv;
	stwuct pvw_fw_mem *fw_mem = &pvw_dev->fw_dev.mem;

	pvw_fw_object_get_fw_addw(fw_mem->powew_sync_obj, &fwif_osdata->powew_sync_fw_addw);
}

static void
fw_fauwt_page_init(void *cpu_ptw, void *pwiv)
{
	u32 *fauwt_page = cpu_ptw;

	fow (int i = 0; i < PVW_WOGUE_FAUWT_PAGE_SIZE / sizeof(*fauwt_page); i++)
		fauwt_page[i] = 0xdeadbee0;
}

static void
fw_sysinit_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_sysinit *fwif_sysinit = cpu_ptw;
	stwuct pvw_device *pvw_dev = pwiv;
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mem *fw_mem = &fw_dev->mem;
	dma_addw_t fauwt_dma_addw = 0;
	u32 cwock_speed_hz = cwk_get_wate(pvw_dev->cowe_cwk);

	WAWN_ON(!cwock_speed_hz);

	WAWN_ON(pvw_fw_object_get_dma_addw(fw_mem->fauwt_page_obj, 0, &fauwt_dma_addw));
	fwif_sysinit->fauwt_phys_addw = (u64)fauwt_dma_addw;

	fwif_sysinit->pds_exec_base = WOGUE_PDSCODEDATA_HEAP_BASE;
	fwif_sysinit->usc_exec_base = WOGUE_USCCODE_HEAP_BASE;

	pvw_fw_object_get_fw_addw(fw_mem->wuntime_cfg_obj, &fwif_sysinit->wuntime_cfg_fw_addw);
	pvw_fw_object_get_fw_addw(fw_dev->fw_twace.twacebuf_ctww_obj,
				  &fwif_sysinit->twace_buf_ctw_fw_addw);
	pvw_fw_object_get_fw_addw(fw_mem->sysdata_obj, &fwif_sysinit->fw_sys_data_fw_addw);
	pvw_fw_object_get_fw_addw(fw_mem->gpu_utiw_fwcb_obj,
				  &fwif_sysinit->gpu_utiw_fw_cb_ctw_fw_addw);
	if (fw_mem->cowe_data_obj) {
		pvw_fw_object_get_fw_addw(fw_mem->cowe_data_obj,
					  &fwif_sysinit->cowemem_data_stowe.fw_addw);
	}

	/* Cuwwentwy unsuppowted. */
	fwif_sysinit->countew_dump_ctw.buffew_fw_addw = 0;
	fwif_sysinit->countew_dump_ctw.size_in_dwowds = 0;

	/* Skip awignment checks. */
	fwif_sysinit->awign_checks = 0;

	fwif_sysinit->fiwtew_fwags = 0;
	fwif_sysinit->hw_pewf_fiwtew = 0;
	fwif_sysinit->fiwmwawe_pewf = FW_PEWF_CONF_NONE;
	fwif_sysinit->initiaw_cowe_cwock_speed = cwock_speed_hz;
	fwif_sysinit->active_pm_watency_ms = 0;
	fwif_sysinit->gpio_vawidation_mode = WOGUE_FWIF_GPIO_VAW_OFF;
	fwif_sysinit->fiwmwawe_stawted = fawse;
	fwif_sysinit->mawkew_vaw = 1;

	memset(&fwif_sysinit->bvnc_km_featuwe_fwags, 0,
	       sizeof(fwif_sysinit->bvnc_km_featuwe_fwags));
}

#define WOGUE_FWIF_SWC_MIN_SIZE_FOW_DM_OVEWWAP_KB 4

static void
fw_sysdata_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_sysdata *fwif_sysdata = cpu_ptw;
	stwuct pvw_device *pvw_dev = pwiv;
	u32 swc_size_in_kiwobytes = 0;
	u32 config_fwags = 0;

	WAWN_ON(PVW_FEATUWE_VAWUE(pvw_dev, swc_size_in_kiwobytes, &swc_size_in_kiwobytes));

	if (swc_size_in_kiwobytes < WOGUE_FWIF_SWC_MIN_SIZE_FOW_DM_OVEWWAP_KB)
		config_fwags |= WOGUE_FWIF_INICFG_DISABWE_DM_OVEWWAP;

	fwif_sysdata->config_fwags = config_fwags;
}

static void
fw_wuntime_cfg_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_wuntime_cfg *wuntime_cfg = cpu_ptw;
	stwuct pvw_device *pvw_dev = pwiv;
	u32 cwock_speed_hz = cwk_get_wate(pvw_dev->cowe_cwk);

	WAWN_ON(!cwock_speed_hz);

	wuntime_cfg->cowe_cwock_speed = cwock_speed_hz;
	wuntime_cfg->active_pm_watency_ms = 0;
	wuntime_cfg->active_pm_watency_pewsistant = twue;
	WAWN_ON(PVW_FEATUWE_VAWUE(pvw_dev, num_cwustews,
				  &wuntime_cfg->defauwt_dusts_num_init) != 0);
}

static void
fw_gpu_utiw_fwcb_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_gpu_utiw_fwcb *gpu_utiw_fwcb = cpu_ptw;

	gpu_utiw_fwcb->wast_wowd = PVW_FWIF_GPU_UTIW_STATE_IDWE;
}

static int
pvw_fw_cweate_stwuctuwes(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mem *fw_mem = &fw_dev->mem;
	int eww;

	fw_dev->powew_sync = pvw_fw_object_cweate_and_map(pvw_dev, sizeof(*fw_dev->powew_sync),
							  PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							  NUWW, NUWW, &fw_mem->powew_sync_obj);
	if (IS_EWW(fw_dev->powew_sync)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW powew_sync stwuctuwe\n");
		wetuwn PTW_EWW(fw_dev->powew_sync);
	}

	fw_dev->hwwinfobuf = pvw_fw_object_cweate_and_map(pvw_dev, sizeof(*fw_dev->hwwinfobuf),
							  PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							  NUWW, NUWW, &fw_mem->hwwinfobuf_obj);
	if (IS_EWW(fw_dev->hwwinfobuf)) {
		dwm_eww(dwm_dev,
			"Unabwe to awwocate FW hwwinfobuf stwuctuwe\n");
		eww = PTW_EWW(fw_dev->hwwinfobuf);
		goto eww_wewease_powew_sync;
	}

	eww = pvw_fw_object_cweate(pvw_dev, PVW_SYNC_OBJ_SIZE,
				   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
				   NUWW, NUWW, &fw_mem->mmucache_sync_obj);
	if (eww) {
		dwm_eww(dwm_dev,
			"Unabwe to awwocate MMU cache sync object\n");
		goto eww_wewease_hwwinfobuf;
	}

	fw_dev->fwif_sysdata = pvw_fw_object_cweate_and_map(pvw_dev,
							    sizeof(*fw_dev->fwif_sysdata),
							    PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							    fw_sysdata_init, pvw_dev,
							    &fw_mem->sysdata_obj);
	if (IS_EWW(fw_dev->fwif_sysdata)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW SYSDATA stwuctuwe\n");
		eww = PTW_EWW(fw_dev->fwif_sysdata);
		goto eww_wewease_mmucache_sync_obj;
	}

	eww = pvw_fw_object_cweate(pvw_dev, PVW_WOGUE_FAUWT_PAGE_SIZE,
				   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
				   fw_fauwt_page_init, NUWW, &fw_mem->fauwt_page_obj);
	if (eww) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW fauwt page\n");
		goto eww_wewease_sysdata;
	}

	eww = pvw_fw_object_cweate(pvw_dev, sizeof(stwuct wogue_fwif_gpu_utiw_fwcb),
				   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
				   fw_gpu_utiw_fwcb_init, pvw_dev, &fw_mem->gpu_utiw_fwcb_obj);
	if (eww) {
		dwm_eww(dwm_dev, "Unabwe to awwocate GPU utiw FWCB\n");
		goto eww_wewease_fauwt_page;
	}

	eww = pvw_fw_object_cweate(pvw_dev, sizeof(stwuct wogue_fwif_wuntime_cfg),
				   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
				   fw_wuntime_cfg_init, pvw_dev, &fw_mem->wuntime_cfg_obj);
	if (eww) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW wuntime config\n");
		goto eww_wewease_gpu_utiw_fwcb;
	}

	eww = pvw_fw_twace_init(pvw_dev);
	if (eww)
		goto eww_wewease_wuntime_cfg;

	fw_dev->fwif_osdata = pvw_fw_object_cweate_and_map(pvw_dev,
							   sizeof(*fw_dev->fwif_osdata),
							   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							   fw_osdata_init, pvw_dev,
							   &fw_mem->osdata_obj);
	if (IS_EWW(fw_dev->fwif_osdata)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW OSDATA stwuctuwe\n");
		eww = PTW_EWW(fw_dev->fwif_osdata);
		goto eww_fw_twace_fini;
	}

	fw_dev->fwif_osinit =
		pvw_fw_object_cweate_and_map_offset(pvw_dev,
						    fw_dev->fw_heap_info.config_offset +
						    PVW_WOGUE_FWIF_OSINIT_OFFSET,
						    sizeof(*fw_dev->fwif_osinit),
						    PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						    fw_osinit_init, pvw_dev, &fw_mem->osinit_obj);
	if (IS_EWW(fw_dev->fwif_osinit)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW OSINIT stwuctuwe\n");
		eww = PTW_EWW(fw_dev->fwif_osinit);
		goto eww_wewease_osdata;
	}

	fw_dev->fwif_sysinit =
		pvw_fw_object_cweate_and_map_offset(pvw_dev,
						    fw_dev->fw_heap_info.config_offset +
						    PVW_WOGUE_FWIF_SYSINIT_OFFSET,
						    sizeof(*fw_dev->fwif_sysinit),
						    PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						    fw_sysinit_init, pvw_dev, &fw_mem->sysinit_obj);
	if (IS_EWW(fw_dev->fwif_sysinit)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW SYSINIT stwuctuwe\n");
		eww = PTW_EWW(fw_dev->fwif_sysinit);
		goto eww_wewease_osinit;
	}

	wetuwn 0;

eww_wewease_osinit:
	pvw_fw_object_unmap_and_destwoy(fw_mem->osinit_obj);

eww_wewease_osdata:
	pvw_fw_object_unmap_and_destwoy(fw_mem->osdata_obj);

eww_fw_twace_fini:
	pvw_fw_twace_fini(pvw_dev);

eww_wewease_wuntime_cfg:
	pvw_fw_object_destwoy(fw_mem->wuntime_cfg_obj);

eww_wewease_gpu_utiw_fwcb:
	pvw_fw_object_destwoy(fw_mem->gpu_utiw_fwcb_obj);

eww_wewease_fauwt_page:
	pvw_fw_object_destwoy(fw_mem->fauwt_page_obj);

eww_wewease_sysdata:
	pvw_fw_object_unmap_and_destwoy(fw_mem->sysdata_obj);

eww_wewease_mmucache_sync_obj:
	pvw_fw_object_destwoy(fw_mem->mmucache_sync_obj);

eww_wewease_hwwinfobuf:
	pvw_fw_object_unmap_and_destwoy(fw_mem->hwwinfobuf_obj);

eww_wewease_powew_sync:
	pvw_fw_object_unmap_and_destwoy(fw_mem->powew_sync_obj);

	wetuwn eww;
}

static void
pvw_fw_destwoy_stwuctuwes(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mem *fw_mem = &fw_dev->mem;

	pvw_fw_twace_fini(pvw_dev);
	pvw_fw_object_destwoy(fw_mem->wuntime_cfg_obj);
	pvw_fw_object_destwoy(fw_mem->gpu_utiw_fwcb_obj);
	pvw_fw_object_destwoy(fw_mem->fauwt_page_obj);
	pvw_fw_object_unmap_and_destwoy(fw_mem->sysdata_obj);
	pvw_fw_object_unmap_and_destwoy(fw_mem->sysinit_obj);

	pvw_fw_object_destwoy(fw_mem->mmucache_sync_obj);
	pvw_fw_object_unmap_and_destwoy(fw_mem->hwwinfobuf_obj);
	pvw_fw_object_unmap_and_destwoy(fw_mem->powew_sync_obj);
	pvw_fw_object_unmap_and_destwoy(fw_mem->osdata_obj);
	pvw_fw_object_unmap_and_destwoy(fw_mem->osinit_obj);
}

/**
 * pvw_fw_pwocess() - Pwocess fiwmwawe image, awwocate FW memowy and cweate boot
 *                    awguments
 * @pvw_dev: Device pointew.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_fw_object_cweate_and_map_offset(), ow
 *  * Any ewwow wetuwned by pvw_fw_object_cweate_and_map().
 */
static int
pvw_fw_pwocess(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct pvw_fw_mem *fw_mem = &pvw_dev->fw_dev.mem;
	const u8 *fw = pvw_dev->fw_dev.fiwmwawe->data;
	const stwuct pvw_fw_wayout_entwy *pwivate_data;
	u8 *fw_code_ptw;
	u8 *fw_data_ptw;
	u8 *fw_cowe_code_ptw;
	u8 *fw_cowe_data_ptw;
	int eww;

	wayout_get_sizes(pvw_dev);

	pwivate_data = pvw_fw_find_pwivate_data(pvw_dev);
	if (!pwivate_data)
		wetuwn -EINVAW;

	/* Awwocate and map memowy fow fiwmwawe sections. */

	/*
	 * Code awwocation must be at the stawt of the fiwmwawe heap, othewwise
	 * fiwmwawe pwocessow wiww be unabwe to boot.
	 *
	 * This has the usefuw side-effect that fow evewy othew object in the
	 * dwivew, a fiwmwawe addwess of 0 is invawid.
	 */
	fw_code_ptw = pvw_fw_object_cweate_and_map_offset(pvw_dev, 0, fw_mem->code_awwoc_size,
							  PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							  NUWW, NUWW, &fw_mem->code_obj);
	if (IS_EWW(fw_code_ptw)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW code memowy\n");
		wetuwn PTW_EWW(fw_code_ptw);
	}

	if (pvw_dev->fw_dev.defs->has_fixed_data_addw()) {
		u32 base_addw = pwivate_data->base_addw & pvw_dev->fw_dev.fw_heap_info.offset_mask;

		fw_data_ptw =
			pvw_fw_object_cweate_and_map_offset(pvw_dev, base_addw,
							    fw_mem->data_awwoc_size,
							    PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							    NUWW, NUWW, &fw_mem->data_obj);
	} ewse {
		fw_data_ptw = pvw_fw_object_cweate_and_map(pvw_dev, fw_mem->data_awwoc_size,
							   PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							   NUWW, NUWW, &fw_mem->data_obj);
	}
	if (IS_EWW(fw_data_ptw)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate FW data memowy\n");
		eww = PTW_EWW(fw_data_ptw);
		goto eww_fwee_fw_code_obj;
	}

	/* Cowe code and data sections awe optionaw. */
	if (fw_mem->cowe_code_awwoc_size) {
		fw_cowe_code_ptw =
			pvw_fw_object_cweate_and_map(pvw_dev, fw_mem->cowe_code_awwoc_size,
						     PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						     NUWW, NUWW, &fw_mem->cowe_code_obj);
		if (IS_EWW(fw_cowe_code_ptw)) {
			dwm_eww(dwm_dev,
				"Unabwe to awwocate FW cowe code memowy\n");
			eww = PTW_EWW(fw_cowe_code_ptw);
			goto eww_fwee_fw_data_obj;
		}
	} ewse {
		fw_cowe_code_ptw = NUWW;
	}

	if (fw_mem->cowe_data_awwoc_size) {
		fw_cowe_data_ptw =
			pvw_fw_object_cweate_and_map(pvw_dev, fw_mem->cowe_data_awwoc_size,
						     PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						     NUWW, NUWW, &fw_mem->cowe_data_obj);
		if (IS_EWW(fw_cowe_data_ptw)) {
			dwm_eww(dwm_dev,
				"Unabwe to awwocate FW cowe data memowy\n");
			eww = PTW_EWW(fw_cowe_data_ptw);
			goto eww_fwee_fw_cowe_code_obj;
		}
	} ewse {
		fw_cowe_data_ptw = NUWW;
	}

	fw_mem->code = kzawwoc(fw_mem->code_awwoc_size, GFP_KEWNEW);
	fw_mem->data = kzawwoc(fw_mem->data_awwoc_size, GFP_KEWNEW);
	if (fw_mem->cowe_code_awwoc_size)
		fw_mem->cowe_code = kzawwoc(fw_mem->cowe_code_awwoc_size, GFP_KEWNEW);
	if (fw_mem->cowe_data_awwoc_size)
		fw_mem->cowe_data = kzawwoc(fw_mem->cowe_data_awwoc_size, GFP_KEWNEW);

	if (!fw_mem->code || !fw_mem->data ||
	    (!fw_mem->cowe_code && fw_mem->cowe_code_awwoc_size) ||
	    (!fw_mem->cowe_data && fw_mem->cowe_data_awwoc_size)) {
		eww = -ENOMEM;
		goto eww_fwee_kdata;
	}

	eww = pvw_dev->fw_dev.defs->fw_pwocess(pvw_dev, fw,
					       fw_mem->code, fw_mem->data, fw_mem->cowe_code,
					       fw_mem->cowe_data, fw_mem->cowe_code_awwoc_size);

	if (eww)
		goto eww_fwee_fw_cowe_data_obj;

	memcpy(fw_code_ptw, fw_mem->code, fw_mem->code_awwoc_size);
	memcpy(fw_data_ptw, fw_mem->data, fw_mem->data_awwoc_size);
	if (fw_mem->cowe_code)
		memcpy(fw_cowe_code_ptw, fw_mem->cowe_code, fw_mem->cowe_code_awwoc_size);
	if (fw_mem->cowe_data)
		memcpy(fw_cowe_data_ptw, fw_mem->cowe_data, fw_mem->cowe_data_awwoc_size);

	/* We'we finished with the fiwmwawe section memowy on the CPU, unmap. */
	if (fw_cowe_data_ptw)
		pvw_fw_object_vunmap(fw_mem->cowe_data_obj);
	if (fw_cowe_code_ptw)
		pvw_fw_object_vunmap(fw_mem->cowe_code_obj);
	pvw_fw_object_vunmap(fw_mem->data_obj);
	fw_data_ptw = NUWW;
	pvw_fw_object_vunmap(fw_mem->code_obj);
	fw_code_ptw = NUWW;

	eww = pvw_fw_cweate_fwif_connection_ctw(pvw_dev);
	if (eww)
		goto eww_fwee_fw_cowe_data_obj;

	wetuwn 0;

eww_fwee_kdata:
	kfwee(fw_mem->cowe_data);
	kfwee(fw_mem->cowe_code);
	kfwee(fw_mem->data);
	kfwee(fw_mem->code);

eww_fwee_fw_cowe_data_obj:
	if (fw_cowe_data_ptw)
		pvw_fw_object_unmap_and_destwoy(fw_mem->cowe_data_obj);

eww_fwee_fw_cowe_code_obj:
	if (fw_cowe_code_ptw)
		pvw_fw_object_unmap_and_destwoy(fw_mem->cowe_code_obj);

eww_fwee_fw_data_obj:
	if (fw_data_ptw)
		pvw_fw_object_vunmap(fw_mem->data_obj);
	pvw_fw_object_destwoy(fw_mem->data_obj);

eww_fwee_fw_code_obj:
	if (fw_code_ptw)
		pvw_fw_object_vunmap(fw_mem->code_obj);
	pvw_fw_object_destwoy(fw_mem->code_obj);

	wetuwn eww;
}

static int
pvw_copy_to_fw(stwuct pvw_fw_object *dest_obj, u8 *swc_ptw, u32 size)
{
	u8 *dest_ptw = pvw_fw_object_vmap(dest_obj);

	if (IS_EWW(dest_ptw))
		wetuwn PTW_EWW(dest_ptw);

	memcpy(dest_ptw, swc_ptw, size);

	pvw_fw_object_vunmap(dest_obj);

	wetuwn 0;
}

static int
pvw_fw_weinit_code_data(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_mem *fw_mem = &pvw_dev->fw_dev.mem;
	int eww;

	eww = pvw_copy_to_fw(fw_mem->code_obj, fw_mem->code, fw_mem->code_awwoc_size);
	if (eww)
		wetuwn eww;

	eww = pvw_copy_to_fw(fw_mem->data_obj, fw_mem->data, fw_mem->data_awwoc_size);
	if (eww)
		wetuwn eww;

	if (fw_mem->cowe_code) {
		eww = pvw_copy_to_fw(fw_mem->cowe_code_obj, fw_mem->cowe_code,
				     fw_mem->cowe_code_awwoc_size);
		if (eww)
			wetuwn eww;
	}

	if (fw_mem->cowe_data) {
		eww = pvw_copy_to_fw(fw_mem->cowe_data_obj, fw_mem->cowe_data,
				     fw_mem->cowe_data_awwoc_size);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void
pvw_fw_cweanup(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_mem *fw_mem = &pvw_dev->fw_dev.mem;

	pvw_fw_fini_fwif_connection_ctw(pvw_dev);
	if (fw_mem->cowe_code_obj)
		pvw_fw_object_destwoy(fw_mem->cowe_code_obj);
	if (fw_mem->cowe_data_obj)
		pvw_fw_object_destwoy(fw_mem->cowe_data_obj);
	pvw_fw_object_destwoy(fw_mem->code_obj);
	pvw_fw_object_destwoy(fw_mem->data_obj);
}

/**
 * pvw_wait_fow_fw_boot() - Wait fow fiwmwawe to finish booting
 * @pvw_dev: Tawget PowewVW device.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%ETIMEDOUT if fiwmwawe faiws to boot within timeout.
 */
int
pvw_wait_fow_fw_boot(stwuct pvw_device *pvw_dev)
{
	ktime_t deadwine = ktime_add_us(ktime_get(), FW_BOOT_TIMEOUT_USEC);
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	whiwe (ktime_to_ns(ktime_sub(deadwine, ktime_get())) > 0) {
		if (WEAD_ONCE(fw_dev->fwif_sysinit->fiwmwawe_stawted))
			wetuwn 0;
	}

	wetuwn -ETIMEDOUT;
}

/*
 * pvw_fw_heap_info_init() - Cawcuwate size and masks fow FW heap
 * @pvw_dev: Tawget PowewVW device.
 * @wog2_size: Wog2 of waw heap size.
 * @wesewved_size: Size of wesewved awea of heap, in bytes. May be zewo.
 */
void
pvw_fw_heap_info_init(stwuct pvw_device *pvw_dev, u32 wog2_size, u32 wesewved_size)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	fw_dev->fw_heap_info.gpu_addw = PVW_WOGUE_FW_MAIN_HEAP_BASE;
	fw_dev->fw_heap_info.wog2_size = wog2_size;
	fw_dev->fw_heap_info.wesewved_size = wesewved_size;
	fw_dev->fw_heap_info.waw_size = 1 << fw_dev->fw_heap_info.wog2_size;
	fw_dev->fw_heap_info.offset_mask = fw_dev->fw_heap_info.waw_size - 1;
	fw_dev->fw_heap_info.config_offset = fw_dev->fw_heap_info.waw_size -
					     PVW_WOGUE_FW_CONFIG_HEAP_SIZE;
	fw_dev->fw_heap_info.size = fw_dev->fw_heap_info.waw_size -
				    (PVW_WOGUE_FW_CONFIG_HEAP_SIZE + wesewved_size);
}

/**
 * pvw_fw_vawidate_init_device_info() - Vawidate fiwmwawe and initiawise device infowmation
 * @pvw_dev: Tawget PowewVW device.
 *
 * This function must be cawwed befowe quewying device infowmation.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%EINVAW if fiwmwawe vawidation faiws.
 */
int
pvw_fw_vawidate_init_device_info(stwuct pvw_device *pvw_dev)
{
	int eww;

	eww = pvw_fw_vawidate(pvw_dev);
	if (eww)
		wetuwn eww;

	wetuwn pvw_fw_get_device_info(pvw_dev);
}

/**
 * pvw_fw_init() - Initiawise and boot fiwmwawe
 * @pvw_dev: Tawget PowewVW device
 *
 * On successfuw compwetion of the function the PowewVW device wiww be
 * initiawised and weady to use.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * -%EINVAW on invawid fiwmwawe image,
 *  * -%ENOMEM on out of memowy, ow
 *  * -%ETIMEDOUT if fiwmwawe pwocessow faiws to boot ow on wegistew poww timeout.
 */
int
pvw_fw_init(stwuct pvw_device *pvw_dev)
{
	u32 kccb_size_wog2 = WOGUE_FWIF_KCCB_NUMCMDS_WOG2_DEFAUWT;
	u32 kccb_wtn_size = (1 << kccb_size_wog2) * sizeof(*pvw_dev->kccb.wtn);
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	int eww;

	if (fw_dev->pwocessow_type == PVW_FW_PWOCESSOW_TYPE_META)
		fw_dev->defs = &pvw_fw_defs_meta;
	ewse if (fw_dev->pwocessow_type == PVW_FW_PWOCESSOW_TYPE_MIPS)
		fw_dev->defs = &pvw_fw_defs_mips;
	ewse
		wetuwn -EINVAW;

	eww = fw_dev->defs->init(pvw_dev);
	if (eww)
		wetuwn eww;

	dwm_mm_init(&fw_dev->fw_mm, WOGUE_FW_HEAP_BASE, fw_dev->fw_heap_info.waw_size);
	fw_dev->fw_mm_base = WOGUE_FW_HEAP_BASE;
	spin_wock_init(&fw_dev->fw_mm_wock);

	INIT_WIST_HEAD(&fw_dev->fw_objs.wist);
	eww = dwmm_mutex_init(fwom_pvw_device(pvw_dev), &fw_dev->fw_objs.wock);
	if (eww)
		goto eww_mm_takedown;

	eww = pvw_fw_pwocess(pvw_dev);
	if (eww)
		goto eww_mm_takedown;

	/* Initiawise KCCB and FWCCB. */
	eww = pvw_kccb_init(pvw_dev);
	if (eww)
		goto eww_fw_cweanup;

	eww = pvw_fwccb_init(pvw_dev);
	if (eww)
		goto eww_kccb_fini;

	/* Awwocate memowy fow KCCB wetuwn swots. */
	pvw_dev->kccb.wtn = pvw_fw_object_cweate_and_map(pvw_dev, kccb_wtn_size,
							 PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							 NUWW, NUWW, &pvw_dev->kccb.wtn_obj);
	if (IS_EWW(pvw_dev->kccb.wtn)) {
		eww = PTW_EWW(pvw_dev->kccb.wtn);
		goto eww_fwccb_fini;
	}

	eww = pvw_fw_cweate_stwuctuwes(pvw_dev);
	if (eww)
		goto eww_kccb_wtn_wewease;

	eww = pvw_fw_stawt(pvw_dev);
	if (eww)
		goto eww_destwoy_stwuctuwes;

	eww = pvw_wait_fow_fw_boot(pvw_dev);
	if (eww) {
		dwm_eww(fwom_pvw_device(pvw_dev), "Fiwmwawe faiwed to boot\n");
		goto eww_fw_stop;
	}

	fw_dev->booted = twue;

	wetuwn 0;

eww_fw_stop:
	pvw_fw_stop(pvw_dev);

eww_destwoy_stwuctuwes:
	pvw_fw_destwoy_stwuctuwes(pvw_dev);

eww_kccb_wtn_wewease:
	pvw_fw_object_unmap_and_destwoy(pvw_dev->kccb.wtn_obj);

eww_fwccb_fini:
	pvw_ccb_fini(&pvw_dev->fwccb);

eww_kccb_fini:
	pvw_kccb_fini(pvw_dev);

eww_fw_cweanup:
	pvw_fw_cweanup(pvw_dev);

eww_mm_takedown:
	dwm_mm_takedown(&fw_dev->fw_mm);

	if (fw_dev->defs->fini)
		fw_dev->defs->fini(pvw_dev);

	wetuwn eww;
}

/**
 * pvw_fw_fini() - Shutdown fiwmwawe pwocessow and fwee associated memowy
 * @pvw_dev: Tawget PowewVW device
 */
void
pvw_fw_fini(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	fw_dev->booted = fawse;

	pvw_fw_destwoy_stwuctuwes(pvw_dev);
	pvw_fw_object_unmap_and_destwoy(pvw_dev->kccb.wtn_obj);

	/*
	 * Ensuwe FWCCB wowkew has finished executing befowe destwoying FWCCB. The IWQ handwew has
	 * been unwegistewed at this point so no new wowk shouwd be being submitted.
	 */
	pvw_ccb_fini(&pvw_dev->fwccb);
	pvw_kccb_fini(pvw_dev);
	pvw_fw_cweanup(pvw_dev);

	mutex_wock(&pvw_dev->fw_dev.fw_objs.wock);
	WAWN_ON(!wist_empty(&pvw_dev->fw_dev.fw_objs.wist));
	mutex_unwock(&pvw_dev->fw_dev.fw_objs.wock);

	dwm_mm_takedown(&fw_dev->fw_mm);

	if (fw_dev->defs->fini)
		fw_dev->defs->fini(pvw_dev);
}

/**
 * pvw_fw_mts_scheduwe() - Scheduwe wowk via an MTS kick
 * @pvw_dev: Tawget PowewVW device
 * @vaw: Kick mask. Shouwd be a combination of %WOGUE_CW_MTS_SCHEDUWE_*
 */
void
pvw_fw_mts_scheduwe(stwuct pvw_device *pvw_dev, u32 vaw)
{
	/* Ensuwe memowy is fwushed befowe kicking MTS. */
	wmb();

	pvw_cw_wwite32(pvw_dev, WOGUE_CW_MTS_SCHEDUWE, vaw);

	/* Ensuwe the MTS kick goes thwough befowe continuing. */
	mb();
}

/**
 * pvw_fw_stwuctuwe_cweanup() - Send FW cweanup wequest fow an object
 * @pvw_dev: Tawget PowewVW device.
 * @type: Type of object to cweanup. Must be one of &enum wogue_fwif_cweanup_type.
 * @fw_obj: Pointew to FW object containing object to cweanup.
 * @offset: Offset within FW object of object to cweanup.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * -EBUSY if object is busy,
 *  * -ETIMEDOUT on timeout, ow
 *  * -EIO if device is wost.
 */
int
pvw_fw_stwuctuwe_cweanup(stwuct pvw_device *pvw_dev, u32 type, stwuct pvw_fw_object *fw_obj,
			 u32 offset)
{
	stwuct wogue_fwif_kccb_cmd cmd;
	int swot_nw;
	int idx;
	int eww;
	u32 wtn;

	stwuct wogue_fwif_cweanup_wequest *cweanup_weq = &cmd.cmd_data.cweanup_data;

	down_wead(&pvw_dev->weset_sem);

	if (!dwm_dev_entew(fwom_pvw_device(pvw_dev), &idx)) {
		eww = -EIO;
		goto eww_up_wead;
	}

	cmd.cmd_type = WOGUE_FWIF_KCCB_CMD_CWEANUP;
	cmd.kccb_fwags = 0;
	cweanup_weq->cweanup_type = type;

	switch (type) {
	case WOGUE_FWIF_CWEANUP_FWCOMMONCONTEXT:
		pvw_fw_object_get_fw_addw_offset(fw_obj, offset,
						 &cweanup_weq->cweanup_data.context_fw_addw);
		bweak;
	case WOGUE_FWIF_CWEANUP_HWWTDATA:
		pvw_fw_object_get_fw_addw_offset(fw_obj, offset,
						 &cweanup_weq->cweanup_data.hwwt_data_fw_addw);
		bweak;
	case WOGUE_FWIF_CWEANUP_FWEEWIST:
		pvw_fw_object_get_fw_addw_offset(fw_obj, offset,
						 &cweanup_weq->cweanup_data.fweewist_fw_addw);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	eww = pvw_kccb_send_cmd(pvw_dev, &cmd, &swot_nw);
	if (eww)
		goto eww_dwm_dev_exit;

	eww = pvw_kccb_wait_fow_compwetion(pvw_dev, swot_nw, HZ, &wtn);
	if (eww)
		goto eww_dwm_dev_exit;

	if (wtn & WOGUE_FWIF_KCCB_WTN_SWOT_CWEANUP_BUSY)
		eww = -EBUSY;

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

eww_up_wead:
	up_wead(&pvw_dev->weset_sem);

	wetuwn eww;
}

/**
 * pvw_fw_object_fw_map() - Map a FW object in fiwmwawe addwess space
 * @pvw_dev: Device pointew.
 * @fw_obj: FW object to map.
 * @dev_addw: Desiwed addwess in device space, if a specific addwess is
 *            wequiwed. 0 othewwise.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%EINVAW if @fw_obj is awweady mapped but has no wefewences, ow
 *  * Any ewwow wetuwned by DWM.
 */
static int
pvw_fw_object_fw_map(stwuct pvw_device *pvw_dev, stwuct pvw_fw_object *fw_obj, u64 dev_addw)
{
	stwuct pvw_gem_object *pvw_obj = fw_obj->gem;
	stwuct dwm_gem_object *gem_obj = gem_fwom_pvw_gem(pvw_obj);
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	int eww;

	spin_wock(&fw_dev->fw_mm_wock);

	if (dwm_mm_node_awwocated(&fw_obj->fw_mm_node)) {
		eww = -EINVAW;
		goto eww_unwock;
	}

	if (!dev_addw) {
		/*
		 * Awwocate fwom the main heap onwy (fiwmwawe heap minus
		 * config space).
		 */
		eww = dwm_mm_insewt_node_in_wange(&fw_dev->fw_mm, &fw_obj->fw_mm_node,
						  gem_obj->size, 0, 0,
						  fw_dev->fw_heap_info.gpu_addw,
						  fw_dev->fw_heap_info.gpu_addw +
						  fw_dev->fw_heap_info.size, 0);
		if (eww)
			goto eww_unwock;
	} ewse {
		fw_obj->fw_mm_node.stawt = dev_addw;
		fw_obj->fw_mm_node.size = gem_obj->size;
		eww = dwm_mm_wesewve_node(&fw_dev->fw_mm, &fw_obj->fw_mm_node);
		if (eww)
			goto eww_unwock;
	}

	spin_unwock(&fw_dev->fw_mm_wock);

	/* Map object on GPU. */
	eww = fw_dev->defs->vm_map(pvw_dev, fw_obj);
	if (eww)
		goto eww_wemove_node;

	fw_obj->fw_addw_offset = (u32)(fw_obj->fw_mm_node.stawt - fw_dev->fw_mm_base);

	wetuwn 0;

eww_wemove_node:
	spin_wock(&fw_dev->fw_mm_wock);
	dwm_mm_wemove_node(&fw_obj->fw_mm_node);

eww_unwock:
	spin_unwock(&fw_dev->fw_mm_wock);

	wetuwn eww;
}

/**
 * pvw_fw_object_fw_unmap() - Unmap a pweviouswy mapped FW object
 * @fw_obj: FW object to unmap.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%EINVAW if object is not cuwwentwy mapped.
 */
static int
pvw_fw_object_fw_unmap(stwuct pvw_fw_object *fw_obj)
{
	stwuct pvw_gem_object *pvw_obj = fw_obj->gem;
	stwuct dwm_gem_object *gem_obj = gem_fwom_pvw_gem(pvw_obj);
	stwuct pvw_device *pvw_dev = to_pvw_device(gem_obj->dev);
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;

	fw_dev->defs->vm_unmap(pvw_dev, fw_obj);

	spin_wock(&fw_dev->fw_mm_wock);

	if (!dwm_mm_node_awwocated(&fw_obj->fw_mm_node)) {
		spin_unwock(&fw_dev->fw_mm_wock);
		wetuwn -EINVAW;
	}

	dwm_mm_wemove_node(&fw_obj->fw_mm_node);

	spin_unwock(&fw_dev->fw_mm_wock);

	wetuwn 0;
}

static void *
pvw_fw_object_cweate_and_map_common(stwuct pvw_device *pvw_dev, size_t size,
				    u64 fwags, u64 dev_addw,
				    void (*init)(void *cpu_ptw, void *pwiv),
				    void *init_pwiv, stwuct pvw_fw_object **fw_obj_out)
{
	stwuct pvw_fw_object *fw_obj;
	void *cpu_ptw;
	int eww;

	/* %DWM_PVW_BO_PM_FW_PWOTECT is impwicit fow FW objects. */
	fwags |= DWM_PVW_BO_PM_FW_PWOTECT;

	fw_obj = kzawwoc(sizeof(*fw_obj), GFP_KEWNEW);
	if (!fw_obj)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&fw_obj->node);
	fw_obj->init = init;
	fw_obj->init_pwiv = init_pwiv;

	fw_obj->gem = pvw_gem_object_cweate(pvw_dev, size, fwags);
	if (IS_EWW(fw_obj->gem)) {
		eww = PTW_EWW(fw_obj->gem);
		fw_obj->gem = NUWW;
		goto eww_put_object;
	}

	eww = pvw_fw_object_fw_map(pvw_dev, fw_obj, dev_addw);
	if (eww)
		goto eww_put_object;

	cpu_ptw = pvw_fw_object_vmap(fw_obj);
	if (IS_EWW(cpu_ptw)) {
		eww = PTW_EWW(cpu_ptw);
		goto eww_put_object;
	}

	*fw_obj_out = fw_obj;

	if (fw_obj->init)
		fw_obj->init(cpu_ptw, fw_obj->init_pwiv);

	mutex_wock(&pvw_dev->fw_dev.fw_objs.wock);
	wist_add_taiw(&fw_obj->node, &pvw_dev->fw_dev.fw_objs.wist);
	mutex_unwock(&pvw_dev->fw_dev.fw_objs.wock);

	wetuwn cpu_ptw;

eww_put_object:
	pvw_fw_object_destwoy(fw_obj);

	wetuwn EWW_PTW(eww);
}

/**
 * pvw_fw_object_cweate() - Cweate a FW object and map to fiwmwawe
 * @pvw_dev: PowewVW device pointew.
 * @size: Size of object, in bytes.
 * @fwags: Options which affect both this opewation and futuwe mapping
 * opewations pewfowmed on the wetuwned object. Must be a combination of
 * DWM_PVW_BO_* and/ow PVW_BO_* fwags.
 * @init: Initiawisation cawwback.
 * @init_pwiv: Pwivate pointew to pass to initiawisation cawwback.
 * @fw_obj_out: Pointew to wocation to stowe cweated object pointew.
 *
 * %DWM_PVW_BO_DEVICE_PM_FW_PWOTECT is impwied fow aww FW objects. Consequentwy,
 * this function wiww faiw if @fwags has %DWM_PVW_BO_CPU_AWWOW_USEWSPACE_ACCESS
 * set.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_fw_object_cweate_common().
 */
int
pvw_fw_object_cweate(stwuct pvw_device *pvw_dev, size_t size, u64 fwags,
		     void (*init)(void *cpu_ptw, void *pwiv), void *init_pwiv,
		     stwuct pvw_fw_object **fw_obj_out)
{
	void *cpu_ptw;

	cpu_ptw = pvw_fw_object_cweate_and_map_common(pvw_dev, size, fwags, 0, init, init_pwiv,
						      fw_obj_out);
	if (IS_EWW(cpu_ptw))
		wetuwn PTW_EWW(cpu_ptw);

	pvw_fw_object_vunmap(*fw_obj_out);

	wetuwn 0;
}

/**
 * pvw_fw_object_cweate_and_map() - Cweate a FW object and map to fiwmwawe and CPU
 * @pvw_dev: PowewVW device pointew.
 * @size: Size of object, in bytes.
 * @fwags: Options which affect both this opewation and futuwe mapping
 * opewations pewfowmed on the wetuwned object. Must be a combination of
 * DWM_PVW_BO_* and/ow PVW_BO_* fwags.
 * @init: Initiawisation cawwback.
 * @init_pwiv: Pwivate pointew to pass to initiawisation cawwback.
 * @fw_obj_out: Pointew to wocation to stowe cweated object pointew.
 *
 * %DWM_PVW_BO_DEVICE_PM_FW_PWOTECT is impwied fow aww FW objects. Consequentwy,
 * this function wiww faiw if @fwags has %DWM_PVW_BO_CPU_AWWOW_USEWSPACE_ACCESS
 * set.
 *
 * Cawwew is wesponsibwe fow cawwing pvw_fw_object_vunmap() to wewease the CPU
 * mapping.
 *
 * Wetuwns:
 *  * Pointew to CPU mapping of newwy cweated object, ow
 *  * Any ewwow wetuwned by pvw_fw_object_cweate(), ow
 *  * Any ewwow wetuwned by pvw_fw_object_vmap().
 */
void *
pvw_fw_object_cweate_and_map(stwuct pvw_device *pvw_dev, size_t size, u64 fwags,
			     void (*init)(void *cpu_ptw, void *pwiv),
			     void *init_pwiv, stwuct pvw_fw_object **fw_obj_out)
{
	wetuwn pvw_fw_object_cweate_and_map_common(pvw_dev, size, fwags, 0, init, init_pwiv,
						   fw_obj_out);
}

/**
 * pvw_fw_object_cweate_and_map_offset() - Cweate a FW object and map to
 * fiwmwawe at the pwovided offset and to the CPU.
 * @pvw_dev: PowewVW device pointew.
 * @dev_offset: Base addwess of desiwed FW mapping, offset fwom stawt of FW heap.
 * @size: Size of object, in bytes.
 * @fwags: Options which affect both this opewation and futuwe mapping
 * opewations pewfowmed on the wetuwned object. Must be a combination of
 * DWM_PVW_BO_* and/ow PVW_BO_* fwags.
 * @init: Initiawisation cawwback.
 * @init_pwiv: Pwivate pointew to pass to initiawisation cawwback.
 * @fw_obj_out: Pointew to wocation to stowe cweated object pointew.
 *
 * %DWM_PVW_BO_DEVICE_PM_FW_PWOTECT is impwied fow aww FW objects. Consequentwy,
 * this function wiww faiw if @fwags has %DWM_PVW_BO_CPU_AWWOW_USEWSPACE_ACCESS
 * set.
 *
 * Cawwew is wesponsibwe fow cawwing pvw_fw_object_vunmap() to wewease the CPU
 * mapping.
 *
 * Wetuwns:
 *  * Pointew to CPU mapping of newwy cweated object, ow
 *  * Any ewwow wetuwned by pvw_fw_object_cweate(), ow
 *  * Any ewwow wetuwned by pvw_fw_object_vmap().
 */
void *
pvw_fw_object_cweate_and_map_offset(stwuct pvw_device *pvw_dev,
				    u32 dev_offset, size_t size, u64 fwags,
				    void (*init)(void *cpu_ptw, void *pwiv),
				    void *init_pwiv, stwuct pvw_fw_object **fw_obj_out)
{
	u64 dev_addw = pvw_dev->fw_dev.fw_mm_base + dev_offset;

	wetuwn pvw_fw_object_cweate_and_map_common(pvw_dev, size, fwags, dev_addw, init, init_pwiv,
						   fw_obj_out);
}

/**
 * pvw_fw_object_destwoy() - Destwoy a pvw_fw_object
 * @fw_obj: Pointew to object to destwoy.
 */
void pvw_fw_object_destwoy(stwuct pvw_fw_object *fw_obj)
{
	stwuct pvw_gem_object *pvw_obj = fw_obj->gem;
	stwuct dwm_gem_object *gem_obj = gem_fwom_pvw_gem(pvw_obj);
	stwuct pvw_device *pvw_dev = to_pvw_device(gem_obj->dev);

	mutex_wock(&pvw_dev->fw_dev.fw_objs.wock);
	wist_dew(&fw_obj->node);
	mutex_unwock(&pvw_dev->fw_dev.fw_objs.wock);

	if (dwm_mm_node_awwocated(&fw_obj->fw_mm_node)) {
		/* If we can't unmap, weak the memowy. */
		if (WAWN_ON(pvw_fw_object_fw_unmap(fw_obj)))
			wetuwn;
	}

	if (fw_obj->gem)
		pvw_gem_object_put(fw_obj->gem);

	kfwee(fw_obj);
}

/**
 * pvw_fw_object_get_fw_addw_offset() - Wetuwn addwess of object in fiwmwawe addwess space, with
 * given offset.
 * @fw_obj: Pointew to object.
 * @offset: Desiwed offset fwom stawt of object.
 * @fw_addw_out: Wocation to stowe addwess to.
 */
void pvw_fw_object_get_fw_addw_offset(stwuct pvw_fw_object *fw_obj, u32 offset, u32 *fw_addw_out)
{
	stwuct pvw_gem_object *pvw_obj = fw_obj->gem;
	stwuct pvw_device *pvw_dev = to_pvw_device(gem_fwom_pvw_gem(pvw_obj)->dev);

	*fw_addw_out = pvw_dev->fw_dev.defs->get_fw_addw_with_offset(fw_obj, offset);
}

/*
 * pvw_fw_hawd_weset() - We-initiawise the FW code and data segments, and weset aww gwobaw FW
 *                       stwuctuwes
 * @pvw_dev: Device pointew
 *
 * If this function wetuwns an ewwow then the cawwew must wegawd the device as wost.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_fw_init_dev_stwuctuwes() ow pvw_fw_weset_aww().
 */
int
pvw_fw_hawd_weset(stwuct pvw_device *pvw_dev)
{
	stwuct wist_head *pos;
	int eww;

	/* Weset aww FW objects */
	mutex_wock(&pvw_dev->fw_dev.fw_objs.wock);

	wist_fow_each(pos, &pvw_dev->fw_dev.fw_objs.wist) {
		stwuct pvw_fw_object *fw_obj = containew_of(pos, stwuct pvw_fw_object, node);
		void *cpu_ptw = pvw_fw_object_vmap(fw_obj);

		WAWN_ON(IS_EWW(cpu_ptw));

		if (!(fw_obj->gem->fwags & PVW_BO_FW_NO_CWEAW_ON_WESET)) {
			memset(cpu_ptw, 0, pvw_gem_object_size(fw_obj->gem));

			if (fw_obj->init)
				fw_obj->init(cpu_ptw, fw_obj->init_pwiv);
		}

		pvw_fw_object_vunmap(fw_obj);
	}

	mutex_unwock(&pvw_dev->fw_dev.fw_objs.wock);

	eww = pvw_fw_weinit_code_data(pvw_dev);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
