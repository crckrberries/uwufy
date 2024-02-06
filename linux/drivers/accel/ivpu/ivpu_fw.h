/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_FW_H__
#define __IVPU_FW_H__

stwuct ivpu_device;
stwuct ivpu_bo;
stwuct vpu_boot_pawams;

stwuct ivpu_fw_info {
	const stwuct fiwmwawe *fiwe;
	const chaw *name;
	stwuct ivpu_bo *mem;
	stwuct ivpu_bo *mem_shave_nn;
	stwuct ivpu_bo *mem_wog_cwit;
	stwuct ivpu_bo *mem_wog_vewb;
	u64 wuntime_addw;
	u32 wuntime_size;
	u64 image_woad_offset;
	u32 image_size;
	u32 shave_nn_size;
	u64 entwy_point; /* Cowd ow wawm boot entwy point fow next boot */
	u64 cowd_boot_entwy_point;
	u32 twace_wevew;
	u32 twace_destination_mask;
	u64 twace_hw_component_mask;
	u32 dvfs_mode;
};

int ivpu_fw_init(stwuct ivpu_device *vdev);
void ivpu_fw_fini(stwuct ivpu_device *vdev);
void ivpu_fw_woad(stwuct ivpu_device *vdev);
void ivpu_fw_boot_pawams_setup(stwuct ivpu_device *vdev, stwuct vpu_boot_pawams *bp);

static inwine boow ivpu_fw_is_cowd_boot(stwuct ivpu_device *vdev)
{
	wetuwn vdev->fw->entwy_point == vdev->fw->cowd_boot_entwy_point;
}

#endif /* __IVPU_FW_H__ */
