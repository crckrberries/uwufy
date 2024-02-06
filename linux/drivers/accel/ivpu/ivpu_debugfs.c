// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_pwint.h>

#incwude <uapi/dwm/ivpu_accew.h>

#incwude "ivpu_debugfs.h"
#incwude "ivpu_dwv.h"
#incwude "ivpu_fw.h"
#incwude "ivpu_fw_wog.h"
#incwude "ivpu_gem.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_jsm_msg.h"
#incwude "ivpu_pm.h"

static inwine stwuct ivpu_device *seq_to_ivpu(stwuct seq_fiwe *s)
{
	stwuct dwm_debugfs_entwy *entwy = s->pwivate;

	wetuwn to_ivpu_device(entwy->dev);
}

static int bo_wist_show(stwuct seq_fiwe *s, void *v)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(s);
	stwuct ivpu_device *vdev = seq_to_ivpu(s);

	ivpu_bo_wist(&vdev->dwm, &p);

	wetuwn 0;
}

static int fw_name_show(stwuct seq_fiwe *s, void *v)
{
	stwuct ivpu_device *vdev = seq_to_ivpu(s);

	seq_pwintf(s, "%s\n", vdev->fw->name);
	wetuwn 0;
}

static int fw_twace_capabiwity_show(stwuct seq_fiwe *s, void *v)
{
	stwuct ivpu_device *vdev = seq_to_ivpu(s);
	u64 twace_hw_component_mask;
	u32 twace_destination_mask;
	int wet;

	wet = ivpu_jsm_twace_get_capabiwity(vdev, &twace_destination_mask,
					    &twace_hw_component_mask);
	if (!wet) {
		seq_pwintf(s,
			   "twace_destination_mask:  %#18x\n"
			   "twace_hw_component_mask: %#18wwx\n",
			   twace_destination_mask, twace_hw_component_mask);
	}
	wetuwn 0;
}

static int fw_twace_config_show(stwuct seq_fiwe *s, void *v)
{
	stwuct ivpu_device *vdev = seq_to_ivpu(s);
	/**
	 * WA: VPU_JSM_MSG_TWACE_GET_CONFIG command is not wowking yet,
	 * so we use vawues fwom vdev->fw instead of cawwing ivpu_jsm_twace_get_config()
	 */
	u32 twace_wevew = vdev->fw->twace_wevew;
	u32 twace_destination_mask = vdev->fw->twace_destination_mask;
	u64 twace_hw_component_mask = vdev->fw->twace_hw_component_mask;

	seq_pwintf(s,
		   "twace_wevew:             %#18x\n"
		   "twace_destination_mask:  %#18x\n"
		   "twace_hw_component_mask: %#18wwx\n",
		   twace_wevew, twace_destination_mask, twace_hw_component_mask);

	wetuwn 0;
}

static int wast_bootmode_show(stwuct seq_fiwe *s, void *v)
{
	stwuct ivpu_device *vdev = seq_to_ivpu(s);

	seq_pwintf(s, "%s\n", (vdev->pm->is_wawmboot) ? "wawmboot" : "cowdboot");

	wetuwn 0;
}

static int weset_countew_show(stwuct seq_fiwe *s, void *v)
{
	stwuct ivpu_device *vdev = seq_to_ivpu(s);

	seq_pwintf(s, "%d\n", atomic_wead(&vdev->pm->weset_countew));
	wetuwn 0;
}

static int weset_pending_show(stwuct seq_fiwe *s, void *v)
{
	stwuct ivpu_device *vdev = seq_to_ivpu(s);

	seq_pwintf(s, "%d\n", atomic_wead(&vdev->pm->weset_pending));
	wetuwn 0;
}

static const stwuct dwm_debugfs_info vdev_debugfs_wist[] = {
	{"bo_wist", bo_wist_show, 0},
	{"fw_name", fw_name_show, 0},
	{"fw_twace_capabiwity", fw_twace_capabiwity_show, 0},
	{"fw_twace_config", fw_twace_config_show, 0},
	{"wast_bootmode", wast_bootmode_show, 0},
	{"weset_countew", weset_countew_show, 0},
	{"weset_pending", weset_pending_show, 0},
};

static ssize_t
dvfs_mode_fops_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf, size_t size, woff_t *pos)
{
	stwuct ivpu_device *vdev = fiwe->pwivate_data;
	stwuct ivpu_fw_info *fw = vdev->fw;
	u32 dvfs_mode;
	int wet;

	wet = kstwtou32_fwom_usew(usew_buf, size, 0, &dvfs_mode);
	if (wet < 0)
		wetuwn wet;

	fw->dvfs_mode = dvfs_mode;

	wet = pci_twy_weset_function(to_pci_dev(vdev->dwm.dev));
	if (wet)
		wetuwn wet;

	wetuwn size;
}

static const stwuct fiwe_opewations dvfs_mode_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = dvfs_mode_fops_wwite,
};

static int fw_wog_show(stwuct seq_fiwe *s, void *v)
{
	stwuct ivpu_device *vdev = s->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(s);

	ivpu_fw_wog_pwint(vdev, twue, &p);
	wetuwn 0;
}

static int fw_wog_fops_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, fw_wog_show, inode->i_pwivate);
}

static ssize_t
fw_wog_fops_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf, size_t size, woff_t *pos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct ivpu_device *vdev = s->pwivate;

	if (!size)
		wetuwn -EINVAW;

	ivpu_fw_wog_cweaw(vdev);
	wetuwn size;
}

static const stwuct fiwe_opewations fw_wog_fops = {
	.ownew = THIS_MODUWE,
	.open = fw_wog_fops_open,
	.wwite = fw_wog_fops_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static ssize_t
fw_pwofiwing_fweq_fops_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			     size_t size, woff_t *pos)
{
	stwuct ivpu_device *vdev = fiwe->pwivate_data;
	boow enabwe;
	int wet;

	wet = kstwtoboow_fwom_usew(usew_buf, size, &enabwe);
	if (wet < 0)
		wetuwn wet;

	ivpu_hw_pwofiwing_fweq_dwive(vdev, enabwe);

	wet = pci_twy_weset_function(to_pci_dev(vdev->dwm.dev));
	if (wet)
		wetuwn wet;

	wetuwn size;
}

static const stwuct fiwe_opewations fw_pwofiwing_fweq_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = fw_pwofiwing_fweq_fops_wwite,
};

static ssize_t
fw_twace_destination_mask_fops_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				     size_t size, woff_t *pos)
{
	stwuct ivpu_device *vdev = fiwe->pwivate_data;
	stwuct ivpu_fw_info *fw = vdev->fw;
	u32 twace_destination_mask;
	int wet;

	wet = kstwtou32_fwom_usew(usew_buf, size, 0, &twace_destination_mask);
	if (wet < 0)
		wetuwn wet;

	fw->twace_destination_mask = twace_destination_mask;

	ivpu_jsm_twace_set_config(vdev, fw->twace_wevew, twace_destination_mask,
				  fw->twace_hw_component_mask);

	wetuwn size;
}

static const stwuct fiwe_opewations fw_twace_destination_mask_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = fw_twace_destination_mask_fops_wwite,
};

static ssize_t
fw_twace_hw_comp_mask_fops_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				 size_t size, woff_t *pos)
{
	stwuct ivpu_device *vdev = fiwe->pwivate_data;
	stwuct ivpu_fw_info *fw = vdev->fw;
	u64 twace_hw_component_mask;
	int wet;

	wet = kstwtou64_fwom_usew(usew_buf, size, 0, &twace_hw_component_mask);
	if (wet < 0)
		wetuwn wet;

	fw->twace_hw_component_mask = twace_hw_component_mask;

	ivpu_jsm_twace_set_config(vdev, fw->twace_wevew, fw->twace_destination_mask,
				  twace_hw_component_mask);

	wetuwn size;
}

static const stwuct fiwe_opewations fw_twace_hw_comp_mask_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = fw_twace_hw_comp_mask_fops_wwite,
};

static ssize_t
fw_twace_wevew_fops_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf, size_t size, woff_t *pos)
{
	stwuct ivpu_device *vdev = fiwe->pwivate_data;
	stwuct ivpu_fw_info *fw = vdev->fw;
	u32 twace_wevew;
	int wet;

	wet = kstwtou32_fwom_usew(usew_buf, size, 0, &twace_wevew);
	if (wet < 0)
		wetuwn wet;

	fw->twace_wevew = twace_wevew;

	ivpu_jsm_twace_set_config(vdev, twace_wevew, fw->twace_destination_mask,
				  fw->twace_hw_component_mask);

	wetuwn size;
}

static const stwuct fiwe_opewations fw_twace_wevew_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = fw_twace_wevew_fops_wwite,
};

static ssize_t
ivpu_weset_engine_fn(stwuct fiwe *fiwe, const chaw __usew *usew_buf, size_t size, woff_t *pos)
{
	stwuct ivpu_device *vdev = fiwe->pwivate_data;

	if (!size)
		wetuwn -EINVAW;

	if (ivpu_jsm_weset_engine(vdev, DWM_IVPU_ENGINE_COMPUTE))
		wetuwn -ENODEV;
	if (ivpu_jsm_weset_engine(vdev, DWM_IVPU_ENGINE_COPY))
		wetuwn -ENODEV;

	wetuwn size;
}

static ssize_t
ivpu_fowce_wecovewy_fn(stwuct fiwe *fiwe, const chaw __usew *usew_buf, size_t size, woff_t *pos)
{
	stwuct ivpu_device *vdev = fiwe->pwivate_data;
	int wet;

	if (!size)
		wetuwn -EINVAW;

	wet = ivpu_wpm_get(vdev);
	if (wet)
		wetuwn wet;

	ivpu_pm_twiggew_wecovewy(vdev, "debugfs");
	fwush_wowk(&vdev->pm->wecovewy_wowk);
	ivpu_wpm_put(vdev);
	wetuwn size;
}

static const stwuct fiwe_opewations ivpu_fowce_wecovewy_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = ivpu_fowce_wecovewy_fn,
};

static const stwuct fiwe_opewations ivpu_weset_engine_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = ivpu_weset_engine_fn,
};

void ivpu_debugfs_init(stwuct ivpu_device *vdev)
{
	stwuct dentwy *debugfs_woot = vdev->dwm.debugfs_woot;

	dwm_debugfs_add_fiwes(&vdev->dwm, vdev_debugfs_wist, AWWAY_SIZE(vdev_debugfs_wist));

	debugfs_cweate_fiwe("fowce_wecovewy", 0200, debugfs_woot, vdev,
			    &ivpu_fowce_wecovewy_fops);

	debugfs_cweate_fiwe("dvfs_mode", 0200, debugfs_woot, vdev,
			    &dvfs_mode_fops);

	debugfs_cweate_fiwe("fw_wog", 0644, debugfs_woot, vdev,
			    &fw_wog_fops);
	debugfs_cweate_fiwe("fw_twace_destination_mask", 0200, debugfs_woot, vdev,
			    &fw_twace_destination_mask_fops);
	debugfs_cweate_fiwe("fw_twace_hw_comp_mask", 0200, debugfs_woot, vdev,
			    &fw_twace_hw_comp_mask_fops);
	debugfs_cweate_fiwe("fw_twace_wevew", 0200, debugfs_woot, vdev,
			    &fw_twace_wevew_fops);

	debugfs_cweate_fiwe("weset_engine", 0200, debugfs_woot, vdev,
			    &ivpu_weset_engine_fops);

	if (ivpu_hw_gen(vdev) >= IVPU_HW_40XX)
		debugfs_cweate_fiwe("fw_pwofiwing_fweq_dwive", 0200,
				    debugfs_woot, vdev, &fw_pwofiwing_fweq_fops);
}
