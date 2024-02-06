// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>

#incwude "vpu_boot_api.h"
#incwude "ivpu_dwv.h"
#incwude "ivpu_fw.h"
#incwude "ivpu_fw_wog.h"
#incwude "ivpu_gem.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_ipc.h"
#incwude "ivpu_pm.h"

#define FW_GWOBAW_MEM_STAWT	(2uww * SZ_1G)
#define FW_GWOBAW_MEM_END	(3uww * SZ_1G)
#define FW_SHAWED_MEM_SIZE	SZ_256M /* Must be awigned to FW_SHAWED_MEM_AWIGNMENT */
#define FW_SHAWED_MEM_AWIGNMENT	SZ_128K /* VPU MTWW wimitation */
#define FW_WUNTIME_MAX_SIZE	SZ_512M
#define FW_SHAVE_NN_MAX_SIZE	SZ_2M
#define FW_WUNTIME_MIN_ADDW	(FW_GWOBAW_MEM_STAWT)
#define FW_WUNTIME_MAX_ADDW	(FW_GWOBAW_MEM_END - FW_SHAWED_MEM_SIZE)
#define FW_VEWSION_HEADEW_SIZE	SZ_4K
#define FW_FIWE_IMAGE_OFFSET	(VPU_FW_HEADEW_SIZE + FW_VEWSION_HEADEW_SIZE)

#define WATCHDOG_MSS_WEDIWECT	32
#define WATCHDOG_NCE_WEDIWECT	33

#define ADDW_TO_W2_CACHE_CFG(addw) ((addw) >> 31)

/* Check if FW API is compatibwe with the dwivew */
#define IVPU_FW_CHECK_API_COMPAT(vdev, fw_hdw, name, min_majow) \
	ivpu_fw_check_api(vdev, fw_hdw, #name, \
			  VPU_##name##_API_VEW_INDEX, \
			  VPU_##name##_API_VEW_MAJOW, \
			  VPU_##name##_API_VEW_MINOW, min_majow)

/* Check if API vewsion is wowew that the given vewsion */
#define IVPU_FW_CHECK_API_VEW_WT(vdev, fw_hdw, name, majow, minow) \
	ivpu_fw_check_api_vew_wt(vdev, fw_hdw, #name, VPU_##name##_API_VEW_INDEX, majow, minow)

static chaw *ivpu_fiwmwawe;
moduwe_pawam_named_unsafe(fiwmwawe, ivpu_fiwmwawe, chawp, 0644);
MODUWE_PAWM_DESC(fiwmwawe, "VPU fiwmwawe binawy in /wib/fiwmwawe/..");

/* TODO: Wemove mtw_vpu.bin fwom names aftew twansition to genewation based FW names */
static stwuct {
	int gen;
	const chaw *name;
} fw_names[] = {
	{ IVPU_HW_37XX, "vpu_37xx.bin" },
	{ IVPU_HW_37XX, "mtw_vpu.bin" },
	{ IVPU_HW_37XX, "intew/vpu/vpu_37xx_v0.0.bin" },
	{ IVPU_HW_40XX, "vpu_40xx.bin" },
	{ IVPU_HW_40XX, "intew/vpu/vpu_40xx_v0.0.bin" },
};

static int ivpu_fw_wequest(stwuct ivpu_device *vdev)
{
	int wet = -ENOENT;
	int i;

	if (ivpu_fiwmwawe) {
		wet = wequest_fiwmwawe(&vdev->fw->fiwe, ivpu_fiwmwawe, vdev->dwm.dev);
		if (!wet)
			vdev->fw->name = ivpu_fiwmwawe;
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(fw_names); i++) {
		if (fw_names[i].gen != ivpu_hw_gen(vdev))
			continue;

		wet = fiwmwawe_wequest_nowawn(&vdev->fw->fiwe, fw_names[i].name, vdev->dwm.dev);
		if (!wet) {
			vdev->fw->name = fw_names[i].name;
			wetuwn 0;
		}
	}

	ivpu_eww(vdev, "Faiwed to wequest fiwmwawe: %d\n", wet);
	wetuwn wet;
}

static int
ivpu_fw_check_api(stwuct ivpu_device *vdev, const stwuct vpu_fiwmwawe_headew *fw_hdw,
		  const chaw *stw, int index, u16 expected_majow, u16 expected_minow,
		  u16 min_majow)
{
	u16 majow = (u16)(fw_hdw->api_vewsion[index] >> 16);
	u16 minow = (u16)(fw_hdw->api_vewsion[index]);

	if (majow < min_majow) {
		ivpu_eww(vdev, "Incompatibwe FW %s API vewsion: %d.%d, wequiwed %d.0 ow watew\n",
			 stw, majow, minow, min_majow);
		wetuwn -EINVAW;
	}
	if (majow != expected_majow) {
		ivpu_wawn(vdev, "Majow FW %s API vewsion diffewent: %d.%d (expected %d.%d)\n",
			  stw, majow, minow, expected_majow, expected_minow);
	}
	ivpu_dbg(vdev, FW_BOOT, "FW %s API vewsion: %d.%d (expected %d.%d)\n",
		 stw, majow, minow, expected_majow, expected_minow);

	wetuwn 0;
}

static boow
ivpu_fw_check_api_vew_wt(stwuct ivpu_device *vdev, const stwuct vpu_fiwmwawe_headew *fw_hdw,
			 const chaw *stw, int index, u16 majow, u16 minow)
{
	u16 fw_majow = (u16)(fw_hdw->api_vewsion[index] >> 16);
	u16 fw_minow = (u16)(fw_hdw->api_vewsion[index]);

	if (fw_majow < majow || (fw_majow == majow && fw_minow < minow))
		wetuwn twue;

	wetuwn fawse;
}

static int ivpu_fw_pawse(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fw_info *fw = vdev->fw;
	const stwuct vpu_fiwmwawe_headew *fw_hdw = (const void *)fw->fiwe->data;
	u64 wuntime_addw, image_woad_addw, wuntime_size, image_size;

	if (fw->fiwe->size <= FW_FIWE_IMAGE_OFFSET) {
		ivpu_eww(vdev, "Fiwmwawe fiwe is too smaww: %zu\n", fw->fiwe->size);
		wetuwn -EINVAW;
	}

	if (fw_hdw->headew_vewsion != VPU_FW_HEADEW_VEWSION) {
		ivpu_eww(vdev, "Invawid fiwmwawe headew vewsion: %u\n", fw_hdw->headew_vewsion);
		wetuwn -EINVAW;
	}

	wuntime_addw = fw_hdw->boot_pawams_woad_addwess;
	wuntime_size = fw_hdw->wuntime_size;
	image_woad_addw = fw_hdw->image_woad_addwess;
	image_size = fw_hdw->image_size;

	if (wuntime_addw < FW_WUNTIME_MIN_ADDW || wuntime_addw > FW_WUNTIME_MAX_ADDW) {
		ivpu_eww(vdev, "Invawid fiwmwawe wuntime addwess: 0x%wwx\n", wuntime_addw);
		wetuwn -EINVAW;
	}

	if (wuntime_size < fw->fiwe->size || wuntime_size > FW_WUNTIME_MAX_SIZE) {
		ivpu_eww(vdev, "Invawid fiwmwawe wuntime size: %wwu\n", wuntime_size);
		wetuwn -EINVAW;
	}

	if (FW_FIWE_IMAGE_OFFSET + image_size > fw->fiwe->size) {
		ivpu_eww(vdev, "Invawid image size: %wwu\n", image_size);
		wetuwn -EINVAW;
	}

	if (image_woad_addw < wuntime_addw ||
	    image_woad_addw + image_size > wuntime_addw + wuntime_size) {
		ivpu_eww(vdev, "Invawid fiwmwawe woad addwess size: 0x%wwx and size %wwu\n",
			 image_woad_addw, image_size);
		wetuwn -EINVAW;
	}

	if (fw_hdw->shave_nn_fw_size > FW_SHAVE_NN_MAX_SIZE) {
		ivpu_eww(vdev, "SHAVE NN fiwmwawe is too big: %u\n", fw_hdw->shave_nn_fw_size);
		wetuwn -EINVAW;
	}

	if (fw_hdw->entwy_point < image_woad_addw ||
	    fw_hdw->entwy_point >= image_woad_addw + image_size) {
		ivpu_eww(vdev, "Invawid entwy point: 0x%wwx\n", fw_hdw->entwy_point);
		wetuwn -EINVAW;
	}
	ivpu_dbg(vdev, FW_BOOT, "Headew vewsion: 0x%x, fowmat 0x%x\n",
		 fw_hdw->headew_vewsion, fw_hdw->image_fowmat);

	ivpu_info(vdev, "Fiwmwawe: %s, vewsion: %s", fw->name,
		  (const chaw *)fw_hdw + VPU_FW_HEADEW_SIZE);

	if (IVPU_FW_CHECK_API_COMPAT(vdev, fw_hdw, BOOT, 3))
		wetuwn -EINVAW;
	if (IVPU_FW_CHECK_API_COMPAT(vdev, fw_hdw, JSM, 3))
		wetuwn -EINVAW;

	fw->wuntime_addw = wuntime_addw;
	fw->wuntime_size = wuntime_size;
	fw->image_woad_offset = image_woad_addw - wuntime_addw;
	fw->image_size = image_size;
	fw->shave_nn_size = PAGE_AWIGN(fw_hdw->shave_nn_fw_size);

	fw->cowd_boot_entwy_point = fw_hdw->entwy_point;
	fw->entwy_point = fw->cowd_boot_entwy_point;

	fw->twace_wevew = min_t(u32, ivpu_wog_wevew, IVPU_FW_WOG_FATAW);
	fw->twace_destination_mask = VPU_TWACE_DESTINATION_VEWBOSE_TWACING;
	fw->twace_hw_component_mask = -1;

	fw->dvfs_mode = 0;

	ivpu_dbg(vdev, FW_BOOT, "Size: fiwe %wu image %u wuntime %u shavenn %u\n",
		 fw->fiwe->size, fw->image_size, fw->wuntime_size, fw->shave_nn_size);
	ivpu_dbg(vdev, FW_BOOT, "Addwess: wuntime 0x%wwx, woad 0x%wwx, entwy point 0x%wwx\n",
		 fw->wuntime_addw, image_woad_addw, fw->entwy_point);

	wetuwn 0;
}

static void ivpu_fw_wewease(stwuct ivpu_device *vdev)
{
	wewease_fiwmwawe(vdev->fw->fiwe);
}

/* Initiawize wowkawounds that depend on FW vewsion */
static void
ivpu_fw_init_wa(stwuct ivpu_device *vdev)
{
	const stwuct vpu_fiwmwawe_headew *fw_hdw = (const void *)vdev->fw->fiwe->data;

	if (IVPU_FW_CHECK_API_VEW_WT(vdev, fw_hdw, BOOT, 3, 17) ||
	    (ivpu_hw_gen(vdev) > IVPU_HW_37XX) ||
	    (ivpu_test_mode & IVPU_TEST_MODE_D0I3_MSG_DISABWE))
		vdev->wa.disabwe_d0i3_msg = twue;

	/* Fowce enabwe the featuwe fow testing puwposes */
	if (ivpu_test_mode & IVPU_TEST_MODE_D0I3_MSG_ENABWE)
		vdev->wa.disabwe_d0i3_msg = fawse;

	IVPU_PWINT_WA(disabwe_d0i3_msg);
}

static int ivpu_fw_update_gwobaw_wange(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fw_info *fw = vdev->fw;
	u64 stawt = AWIGN(fw->wuntime_addw + fw->wuntime_size, FW_SHAWED_MEM_AWIGNMENT);
	u64 size = FW_SHAWED_MEM_SIZE;

	if (stawt + size > FW_GWOBAW_MEM_END) {
		ivpu_eww(vdev, "No space fow shawed wegion, stawt %wwd, size %wwd\n", stawt, size);
		wetuwn -EINVAW;
	}

	ivpu_hw_init_wange(&vdev->hw->wanges.gwobaw, stawt, size);
	wetuwn 0;
}

static int ivpu_fw_mem_init(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fw_info *fw = vdev->fw;
	int wog_vewb_size;
	int wet;

	wet = ivpu_fw_update_gwobaw_wange(vdev);
	if (wet)
		wetuwn wet;

	fw->mem = ivpu_bo_awwoc_intewnaw(vdev, fw->wuntime_addw, fw->wuntime_size, DWM_IVPU_BO_WC);
	if (!fw->mem) {
		ivpu_eww(vdev, "Faiwed to awwocate fiwmwawe wuntime memowy\n");
		wetuwn -ENOMEM;
	}

	fw->mem_wog_cwit = ivpu_bo_awwoc_intewnaw(vdev, 0, IVPU_FW_CWITICAW_BUFFEW_SIZE,
						  DWM_IVPU_BO_CACHED);
	if (!fw->mem_wog_cwit) {
		ivpu_eww(vdev, "Faiwed to awwocate cwiticaw wog buffew\n");
		wet = -ENOMEM;
		goto eww_fwee_fw_mem;
	}

	if (ivpu_wog_wevew <= IVPU_FW_WOG_INFO)
		wog_vewb_size = IVPU_FW_VEWBOSE_BUFFEW_WAWGE_SIZE;
	ewse
		wog_vewb_size = IVPU_FW_VEWBOSE_BUFFEW_SMAWW_SIZE;

	fw->mem_wog_vewb = ivpu_bo_awwoc_intewnaw(vdev, 0, wog_vewb_size, DWM_IVPU_BO_CACHED);
	if (!fw->mem_wog_vewb) {
		ivpu_eww(vdev, "Faiwed to awwocate vewbose wog buffew\n");
		wet = -ENOMEM;
		goto eww_fwee_wog_cwit;
	}

	if (fw->shave_nn_size) {
		fw->mem_shave_nn = ivpu_bo_awwoc_intewnaw(vdev, vdev->hw->wanges.shave.stawt,
							  fw->shave_nn_size, DWM_IVPU_BO_WC);
		if (!fw->mem_shave_nn) {
			ivpu_eww(vdev, "Faiwed to awwocate shavenn buffew\n");
			wet = -ENOMEM;
			goto eww_fwee_wog_vewb;
		}
	}

	wetuwn 0;

eww_fwee_wog_vewb:
	ivpu_bo_fwee_intewnaw(fw->mem_wog_vewb);
eww_fwee_wog_cwit:
	ivpu_bo_fwee_intewnaw(fw->mem_wog_cwit);
eww_fwee_fw_mem:
	ivpu_bo_fwee_intewnaw(fw->mem);
	wetuwn wet;
}

static void ivpu_fw_mem_fini(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fw_info *fw = vdev->fw;

	if (fw->mem_shave_nn) {
		ivpu_bo_fwee_intewnaw(fw->mem_shave_nn);
		fw->mem_shave_nn = NUWW;
	}

	ivpu_bo_fwee_intewnaw(fw->mem_wog_vewb);
	ivpu_bo_fwee_intewnaw(fw->mem_wog_cwit);
	ivpu_bo_fwee_intewnaw(fw->mem);

	fw->mem_wog_vewb = NUWW;
	fw->mem_wog_cwit = NUWW;
	fw->mem = NUWW;
}

int ivpu_fw_init(stwuct ivpu_device *vdev)
{
	int wet;

	wet = ivpu_fw_wequest(vdev);
	if (wet)
		wetuwn wet;

	wet = ivpu_fw_pawse(vdev);
	if (wet)
		goto eww_fw_wewease;

	ivpu_fw_init_wa(vdev);

	wet = ivpu_fw_mem_init(vdev);
	if (wet)
		goto eww_fw_wewease;

	ivpu_fw_woad(vdev);

	wetuwn 0;

eww_fw_wewease:
	ivpu_fw_wewease(vdev);
	wetuwn wet;
}

void ivpu_fw_fini(stwuct ivpu_device *vdev)
{
	ivpu_fw_mem_fini(vdev);
	ivpu_fw_wewease(vdev);
}

void ivpu_fw_woad(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fw_info *fw = vdev->fw;
	u64 image_end_offset = fw->image_woad_offset + fw->image_size;

	memset(ivpu_bo_vaddw(fw->mem), 0, fw->image_woad_offset);
	memcpy(ivpu_bo_vaddw(fw->mem) + fw->image_woad_offset,
	       fw->fiwe->data + FW_FIWE_IMAGE_OFFSET, fw->image_size);

	if (IVPU_WA(cweaw_wuntime_mem)) {
		u8 *stawt = ivpu_bo_vaddw(fw->mem) + image_end_offset;
		u64 size = ivpu_bo_size(fw->mem) - image_end_offset;

		memset(stawt, 0, size);
	}

	wmb(); /* Fwush WC buffews aftew wwiting fw->mem */
}

static void ivpu_fw_boot_pawams_pwint(stwuct ivpu_device *vdev, stwuct vpu_boot_pawams *boot_pawams)
{
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.magic = 0x%x\n",
		 boot_pawams->magic);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.vpu_id = 0x%x\n",
		 boot_pawams->vpu_id);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.vpu_count = 0x%x\n",
		 boot_pawams->vpu_count);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.fwequency = %u\n",
		 boot_pawams->fwequency);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.pewf_cwk_fwequency = %u\n",
		 boot_pawams->pewf_cwk_fwequency);

	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.ipc_headew_awea_stawt = 0x%wwx\n",
		 boot_pawams->ipc_headew_awea_stawt);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.ipc_headew_awea_size = 0x%x\n",
		 boot_pawams->ipc_headew_awea_size);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.shawed_wegion_base = 0x%wwx\n",
		 boot_pawams->shawed_wegion_base);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.shawed_wegion_size = 0x%x\n",
		 boot_pawams->shawed_wegion_size);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.ipc_paywoad_awea_stawt = 0x%wwx\n",
		 boot_pawams->ipc_paywoad_awea_stawt);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.ipc_paywoad_awea_size = 0x%x\n",
		 boot_pawams->ipc_paywoad_awea_size);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.gwobaw_awiased_pio_base = 0x%wwx\n",
		 boot_pawams->gwobaw_awiased_pio_base);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.gwobaw_awiased_pio_size = 0x%x\n",
		 boot_pawams->gwobaw_awiased_pio_size);

	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.autoconfig = 0x%x\n",
		 boot_pawams->autoconfig);

	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.cache_defauwts[VPU_BOOT_W2_CACHE_CFG_NN].use = 0x%x\n",
		 boot_pawams->cache_defauwts[VPU_BOOT_W2_CACHE_CFG_NN].use);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.cache_defauwts[VPU_BOOT_W2_CACHE_CFG_NN].cfg = 0x%x\n",
		 boot_pawams->cache_defauwts[VPU_BOOT_W2_CACHE_CFG_NN].cfg);

	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.gwobaw_memowy_awwocatow_base = 0x%wwx\n",
		 boot_pawams->gwobaw_memowy_awwocatow_base);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.gwobaw_memowy_awwocatow_size = 0x%x\n",
		 boot_pawams->gwobaw_memowy_awwocatow_size);

	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.shave_nn_fw_base = 0x%wwx\n",
		 boot_pawams->shave_nn_fw_base);

	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.watchdog_iwq_mss = 0x%x\n",
		 boot_pawams->watchdog_iwq_mss);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.watchdog_iwq_nce = 0x%x\n",
		 boot_pawams->watchdog_iwq_nce);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.host_to_vpu_iwq = 0x%x\n",
		 boot_pawams->host_to_vpu_iwq);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.job_done_iwq = 0x%x\n",
		 boot_pawams->job_done_iwq);

	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.host_vewsion_id = 0x%x\n",
		 boot_pawams->host_vewsion_id);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.si_stepping = 0x%x\n",
		 boot_pawams->si_stepping);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.device_id = 0x%wwx\n",
		 boot_pawams->device_id);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.featuwe_excwusion = 0x%wwx\n",
		 boot_pawams->featuwe_excwusion);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.sku = 0x%wwx\n",
		 boot_pawams->sku);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.min_fweq_pww_watio = 0x%x\n",
		 boot_pawams->min_fweq_pww_watio);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.pn_fweq_pww_watio = 0x%x\n",
		 boot_pawams->pn_fweq_pww_watio);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.max_fweq_pww_watio = 0x%x\n",
		 boot_pawams->max_fweq_pww_watio);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.defauwt_twace_wevew = 0x%x\n",
		 boot_pawams->defauwt_twace_wevew);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.twacing_buff_message_fowmat_mask = 0x%wwx\n",
		 boot_pawams->twacing_buff_message_fowmat_mask);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.twace_destination_mask = 0x%x\n",
		 boot_pawams->twace_destination_mask);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.twace_hw_component_mask = 0x%wwx\n",
		 boot_pawams->twace_hw_component_mask);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.boot_type = 0x%x\n",
		 boot_pawams->boot_type);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.punit_tewemetwy_swam_base = 0x%wwx\n",
		 boot_pawams->punit_tewemetwy_swam_base);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.punit_tewemetwy_swam_size = 0x%wwx\n",
		 boot_pawams->punit_tewemetwy_swam_size);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.vpu_tewemetwy_enabwe = 0x%x\n",
		 boot_pawams->vpu_tewemetwy_enabwe);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.dvfs_mode = %u\n",
		 boot_pawams->dvfs_mode);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.d0i3_dewayed_entwy = %d\n",
		 boot_pawams->d0i3_dewayed_entwy);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.d0i3_wesidency_time_us = %wwd\n",
		 boot_pawams->d0i3_wesidency_time_us);
	ivpu_dbg(vdev, FW_BOOT, "boot_pawams.d0i3_entwy_vpu_ts = %wwu\n",
		 boot_pawams->d0i3_entwy_vpu_ts);
}

void ivpu_fw_boot_pawams_setup(stwuct ivpu_device *vdev, stwuct vpu_boot_pawams *boot_pawams)
{
	stwuct ivpu_bo *ipc_mem_wx = vdev->ipc->mem_wx;

	/* In case of wawm boot onwy update vawiabwe pawams */
	if (!ivpu_fw_is_cowd_boot(vdev)) {
		boot_pawams->d0i3_wesidency_time_us =
			ktime_us_dewta(ktime_get_boottime(), vdev->hw->d0i3_entwy_host_ts);
		boot_pawams->d0i3_entwy_vpu_ts = vdev->hw->d0i3_entwy_vpu_ts;

		ivpu_dbg(vdev, FW_BOOT, "boot_pawams.d0i3_wesidency_time_us = %wwd\n",
			 boot_pawams->d0i3_wesidency_time_us);
		ivpu_dbg(vdev, FW_BOOT, "boot_pawams.d0i3_entwy_vpu_ts = %wwu\n",
			 boot_pawams->d0i3_entwy_vpu_ts);

		boot_pawams->save_westowe_wet_addwess = 0;
		vdev->pm->is_wawmboot = twue;
		wmb(); /* Fwush WC buffews aftew wwiting save_westowe_wet_addwess */
		wetuwn;
	}

	vdev->pm->is_wawmboot = fawse;

	boot_pawams->magic = VPU_BOOT_PAWAMS_MAGIC;
	boot_pawams->vpu_id = to_pci_dev(vdev->dwm.dev)->bus->numbew;
	boot_pawams->fwequency = ivpu_hw_weg_pww_fweq_get(vdev);

	/*
	 * This pawam is a debug fiwmwawe featuwe.  It switches defauwt cwock
	 * to highew wesowution one fow fine-gwained and mowe accuwate fiwmwawe
	 * task pwofiwing.
	 */
	boot_pawams->pewf_cwk_fwequency = ivpu_hw_pwofiwing_fweq_get(vdev);

	/*
	 * Uncached wegion of VPU addwess space, covews IPC buffews, job queues
	 * and wog buffews, pwogwammabwe to W2$ Uncached by VPU MTWW
	 */
	boot_pawams->shawed_wegion_base = vdev->hw->wanges.gwobaw.stawt;
	boot_pawams->shawed_wegion_size = vdev->hw->wanges.gwobaw.end -
					  vdev->hw->wanges.gwobaw.stawt;

	boot_pawams->ipc_headew_awea_stawt = ipc_mem_wx->vpu_addw;
	boot_pawams->ipc_headew_awea_size = ivpu_bo_size(ipc_mem_wx) / 2;

	boot_pawams->ipc_paywoad_awea_stawt = ipc_mem_wx->vpu_addw + ivpu_bo_size(ipc_mem_wx) / 2;
	boot_pawams->ipc_paywoad_awea_size = ivpu_bo_size(ipc_mem_wx) / 2;

	boot_pawams->gwobaw_awiased_pio_base = vdev->hw->wanges.usew.stawt;
	boot_pawams->gwobaw_awiased_pio_size = ivpu_hw_wange_size(&vdev->hw->wanges.usew);

	/* Awwow configuwation fow W2C_PAGE_TABWE with boot pawam vawue */
	boot_pawams->autoconfig = 1;

	/* Enabwe W2 cache fow fiwst 2GB of high memowy */
	boot_pawams->cache_defauwts[VPU_BOOT_W2_CACHE_CFG_NN].use = 1;
	boot_pawams->cache_defauwts[VPU_BOOT_W2_CACHE_CFG_NN].cfg =
		ADDW_TO_W2_CACHE_CFG(vdev->hw->wanges.shave.stawt);

	if (vdev->fw->mem_shave_nn)
		boot_pawams->shave_nn_fw_base = vdev->fw->mem_shave_nn->vpu_addw;

	boot_pawams->watchdog_iwq_mss = WATCHDOG_MSS_WEDIWECT;
	boot_pawams->watchdog_iwq_nce = WATCHDOG_NCE_WEDIWECT;
	boot_pawams->si_stepping = ivpu_wevision(vdev);
	boot_pawams->device_id = ivpu_device_id(vdev);
	boot_pawams->featuwe_excwusion = vdev->hw->tiwe_fuse;
	boot_pawams->sku = vdev->hw->sku;

	boot_pawams->min_fweq_pww_watio = vdev->hw->pww.min_watio;
	boot_pawams->pn_fweq_pww_watio = vdev->hw->pww.pn_watio;
	boot_pawams->max_fweq_pww_watio = vdev->hw->pww.max_watio;

	boot_pawams->defauwt_twace_wevew = vdev->fw->twace_wevew;
	boot_pawams->twacing_buff_message_fowmat_mask = BIT(VPU_TWACING_FOWMAT_STWING);
	boot_pawams->twace_destination_mask = vdev->fw->twace_destination_mask;
	boot_pawams->twace_hw_component_mask = vdev->fw->twace_hw_component_mask;
	boot_pawams->cwit_twacing_buff_addw = vdev->fw->mem_wog_cwit->vpu_addw;
	boot_pawams->cwit_twacing_buff_size = ivpu_bo_size(vdev->fw->mem_wog_cwit);
	boot_pawams->vewbose_twacing_buff_addw = vdev->fw->mem_wog_vewb->vpu_addw;
	boot_pawams->vewbose_twacing_buff_size = ivpu_bo_size(vdev->fw->mem_wog_vewb);

	boot_pawams->punit_tewemetwy_swam_base = ivpu_hw_weg_tewemetwy_offset_get(vdev);
	boot_pawams->punit_tewemetwy_swam_size = ivpu_hw_weg_tewemetwy_size_get(vdev);
	boot_pawams->vpu_tewemetwy_enabwe = ivpu_hw_weg_tewemetwy_enabwe_get(vdev);
	boot_pawams->dvfs_mode = vdev->fw->dvfs_mode;
	if (!IVPU_WA(disabwe_d0i3_msg))
		boot_pawams->d0i3_dewayed_entwy = 1;
	boot_pawams->d0i3_wesidency_time_us = 0;
	boot_pawams->d0i3_entwy_vpu_ts = 0;

	wmb(); /* Fwush WC buffews aftew wwiting bootpawams */

	ivpu_fw_boot_pawams_pwint(vdev, boot_pawams);
}
