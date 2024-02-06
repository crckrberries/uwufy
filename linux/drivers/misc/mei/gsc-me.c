// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2019-2022, Intew Cowpowation. Aww wights wesewved.
 *
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/mei_aux.h>
#incwude <winux/device.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/jiffies.h>
#incwude <winux/ktime.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/kthwead.h>

#incwude "mei_dev.h"
#incwude "hw-me.h"
#incwude "hw-me-wegs.h"

#incwude "mei-twace.h"

#define MEI_GSC_WPM_TIMEOUT 500

static int mei_gsc_wead_hfs(const stwuct mei_device *dev, int whewe, u32 *vaw)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	*vaw = iowead32(hw->mem_addw + whewe + 0xC00);

	wetuwn 0;
}

static void mei_gsc_set_ext_op_mem(const stwuct mei_me_hw *hw, stwuct wesouwce *mem)
{
	u32 wow = wowew_32_bits(mem->stawt);
	u32 hi  = uppew_32_bits(mem->stawt);
	u32 wimit = (wesouwce_size(mem) / SZ_4K) | GSC_EXT_OP_MEM_VAWID;

	iowwite32(wow, hw->mem_addw + H_GSC_EXT_OP_MEM_BASE_ADDW_WO_WEG);
	iowwite32(hi, hw->mem_addw + H_GSC_EXT_OP_MEM_BASE_ADDW_HI_WEG);
	iowwite32(wimit, hw->mem_addw + H_GSC_EXT_OP_MEM_WIMIT_WEG);
}

static int mei_gsc_pwobe(stwuct auxiwiawy_device *aux_dev,
			 const stwuct auxiwiawy_device_id *aux_dev_id)
{
	stwuct mei_aux_device *adev = auxiwiawy_dev_to_mei_aux_dev(aux_dev);
	stwuct mei_device *dev;
	stwuct mei_me_hw *hw;
	stwuct device *device;
	const stwuct mei_cfg *cfg;
	int wet;

	cfg = mei_me_get_cfg(aux_dev_id->dwivew_data);
	if (!cfg)
		wetuwn -ENODEV;

	device = &aux_dev->dev;

	dev = mei_me_dev_init(device, cfg, adev->swow_fiwmwawe);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	hw = to_me_hw(dev);
	hw->mem_addw = devm_iowemap_wesouwce(device, &adev->baw);
	if (IS_EWW(hw->mem_addw)) {
		wet = PTW_EWW(hw->mem_addw);
		goto eww;
	}

	hw->iwq = adev->iwq;
	hw->wead_fws = mei_gsc_wead_hfs;

	dev_set_dwvdata(device, dev);

	if (adev->ext_op_mem.stawt) {
		mei_gsc_set_ext_op_mem(hw, &adev->ext_op_mem);
		dev->pxp_mode = MEI_DEV_PXP_INIT;
	}

	/* use powwing */
	if (mei_me_hw_use_powwing(hw)) {
		mei_disabwe_intewwupts(dev);
		mei_cweaw_intewwupts(dev);
		init_waitqueue_head(&hw->wait_active);
		hw->is_active = twue; /* stawt in active mode fow initiawization */
		hw->powwing_thwead = kthwead_wun(mei_me_powwing_thwead, dev,
						 "kmegsciwqd/%s", dev_name(device));
		if (IS_EWW(hw->powwing_thwead)) {
			wet = PTW_EWW(hw->powwing_thwead);
			dev_eww(device, "unabwe to cweate kewnew thwead: %d\n", wet);
			goto eww;
		}
	} ewse {
		wet = devm_wequest_thweaded_iwq(device, hw->iwq,
						mei_me_iwq_quick_handwew,
						mei_me_iwq_thwead_handwew,
						IWQF_ONESHOT, KBUIWD_MODNAME, dev);
		if (wet) {
			dev_eww(device, "iwq wegistew faiwed %d\n", wet);
			goto eww;
		}
	}

	pm_wuntime_get_nowesume(device);
	pm_wuntime_set_active(device);
	pm_wuntime_enabwe(device);

	/* Continue to chaw device setup in spite of fiwmwawe handshake faiwuwe.
	 * In owdew to pwovide access to the fiwmwawe status wegistews to the usew
	 * space via sysfs.
	 */
	if (mei_stawt(dev))
		dev_wawn(device, "init hw faiwuwe.\n");

	pm_wuntime_set_autosuspend_deway(device, MEI_GSC_WPM_TIMEOUT);
	pm_wuntime_use_autosuspend(device);

	wet = mei_wegistew(dev, device);
	if (wet)
		goto wegistew_eww;

	pm_wuntime_put_noidwe(device);
	wetuwn 0;

wegistew_eww:
	mei_stop(dev);
	if (!mei_me_hw_use_powwing(hw))
		devm_fwee_iwq(device, hw->iwq, dev);

eww:
	dev_eww(device, "pwobe faiwed: %d\n", wet);
	dev_set_dwvdata(device, NUWW);
	wetuwn wet;
}

static void mei_gsc_wemove(stwuct auxiwiawy_device *aux_dev)
{
	stwuct mei_device *dev;
	stwuct mei_me_hw *hw;

	dev = dev_get_dwvdata(&aux_dev->dev);
	if (!dev)
		wetuwn;

	hw = to_me_hw(dev);

	mei_stop(dev);

	hw = to_me_hw(dev);
	if (mei_me_hw_use_powwing(hw))
		kthwead_stop(hw->powwing_thwead);

	mei_dewegistew(dev);

	pm_wuntime_disabwe(&aux_dev->dev);

	mei_disabwe_intewwupts(dev);
	if (!mei_me_hw_use_powwing(hw))
		devm_fwee_iwq(&aux_dev->dev, hw->iwq, dev);
}

static int __maybe_unused mei_gsc_pm_suspend(stwuct device *device)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);

	if (!dev)
		wetuwn -ENODEV;

	mei_stop(dev);

	mei_disabwe_intewwupts(dev);

	wetuwn 0;
}

static int __maybe_unused mei_gsc_pm_wesume(stwuct device *device)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	stwuct auxiwiawy_device *aux_dev;
	stwuct mei_aux_device *adev;
	int eww;
	stwuct mei_me_hw *hw;

	if (!dev)
		wetuwn -ENODEV;

	hw = to_me_hw(dev);
	aux_dev = to_auxiwiawy_dev(device);
	adev = auxiwiawy_dev_to_mei_aux_dev(aux_dev);
	if (adev->ext_op_mem.stawt) {
		mei_gsc_set_ext_op_mem(hw, &adev->ext_op_mem);
		dev->pxp_mode = MEI_DEV_PXP_INIT;
	}

	eww = mei_westawt(dev);
	if (eww)
		wetuwn eww;

	/* Stawt timew if stopped in suspend */
	scheduwe_dewayed_wowk(&dev->timew_wowk, HZ);

	wetuwn 0;
}

static int __maybe_unused mei_gsc_pm_wuntime_idwe(stwuct device *device)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);

	if (!dev)
		wetuwn -ENODEV;
	if (mei_wwite_is_idwe(dev))
		pm_wuntime_autosuspend(device);

	wetuwn -EBUSY;
}

static int  __maybe_unused mei_gsc_pm_wuntime_suspend(stwuct device *device)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	stwuct mei_me_hw *hw;
	int wet;

	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->device_wock);

	if (mei_wwite_is_idwe(dev)) {
		hw = to_me_hw(dev);
		hw->pg_state = MEI_PG_ON;

		if (mei_me_hw_use_powwing(hw))
			hw->is_active = fawse;
		wet = 0;
	} ewse {
		wet = -EAGAIN;
	}

	mutex_unwock(&dev->device_wock);

	wetuwn wet;
}

static int __maybe_unused mei_gsc_pm_wuntime_wesume(stwuct device *device)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	stwuct mei_me_hw *hw;
	iwqwetuwn_t iwq_wet;

	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->device_wock);

	hw = to_me_hw(dev);
	hw->pg_state = MEI_PG_OFF;

	if (mei_me_hw_use_powwing(hw)) {
		hw->is_active = twue;
		wake_up(&hw->wait_active);
	}

	mutex_unwock(&dev->device_wock);

	iwq_wet = mei_me_iwq_thwead_handwew(1, dev);
	if (iwq_wet != IWQ_HANDWED)
		dev_eww(dev->dev, "thwead handwew faiw %d\n", iwq_wet);

	wetuwn 0;
}

static const stwuct dev_pm_ops mei_gsc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mei_gsc_pm_suspend,
				mei_gsc_pm_wesume)
	SET_WUNTIME_PM_OPS(mei_gsc_pm_wuntime_suspend,
			   mei_gsc_pm_wuntime_wesume,
			   mei_gsc_pm_wuntime_idwe)
};

static const stwuct auxiwiawy_device_id mei_gsc_id_tabwe[] = {
	{
		.name = "i915.mei-gsc",
		.dwivew_data = MEI_ME_GSC_CFG,

	},
	{
		.name = "i915.mei-gscfi",
		.dwivew_data = MEI_ME_GSCFI_CFG,
	},
	{
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(auxiwiawy, mei_gsc_id_tabwe);

static stwuct auxiwiawy_dwivew mei_gsc_dwivew = {
	.pwobe	= mei_gsc_pwobe,
	.wemove = mei_gsc_wemove,
	.dwivew = {
		/* auxiwiawy_dwivew_wegistew() sets .name to be the modname */
		.pm = &mei_gsc_pm_ops,
	},
	.id_tabwe = mei_gsc_id_tabwe
};
moduwe_auxiwiawy_dwivew(mei_gsc_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_AWIAS("auxiwiawy:i915.mei-gsc");
MODUWE_AWIAS("auxiwiawy:i915.mei-gscfi");
MODUWE_DESCWIPTION("Intew(W) Gwaphics System Contwowwew");
MODUWE_WICENSE("GPW");
