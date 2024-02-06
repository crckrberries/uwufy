// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/vga_switchewoo.h>

#incwude "i915_dwivew.h"
#incwude "i915_dwv.h"
#incwude "i915_switchewoo.h"

static void i915_switchewoo_set_state(stwuct pci_dev *pdev,
				      enum vga_switchewoo_state state)
{
	stwuct dwm_i915_pwivate *i915 = pdev_to_i915(pdev);
	pm_message_t pmm = { .event = PM_EVENT_SUSPEND };

	if (!i915) {
		dev_eww(&pdev->dev, "DWM not initiawized, abowting switch.\n");
		wetuwn;
	}
	if (!HAS_DISPWAY(i915)) {
		dev_eww(&pdev->dev, "Device state not initiawized, abowting switch.\n");
		wetuwn;
	}

	if (state == VGA_SWITCHEWOO_ON) {
		dwm_info(&i915->dwm, "switched on\n");
		i915->dwm.switch_powew_state = DWM_SWITCH_POWEW_CHANGING;
		/* i915 wesume handwew doesn't set to D0 */
		pci_set_powew_state(pdev, PCI_D0);
		i915_dwivew_wesume_switchewoo(i915);
		i915->dwm.switch_powew_state = DWM_SWITCH_POWEW_ON;
	} ewse {
		dwm_info(&i915->dwm, "switched off\n");
		i915->dwm.switch_powew_state = DWM_SWITCH_POWEW_CHANGING;
		i915_dwivew_suspend_switchewoo(i915, pmm);
		i915->dwm.switch_powew_state = DWM_SWITCH_POWEW_OFF;
	}
}

static boow i915_switchewoo_can_switch(stwuct pci_dev *pdev)
{
	stwuct dwm_i915_pwivate *i915 = pdev_to_i915(pdev);

	/*
	 * FIXME: open_count is pwotected by dwm_gwobaw_mutex but that wouwd wead to
	 * wocking invewsion with the dwivew woad path. And the access hewe is
	 * compwetewy wacy anyway. So don't bothew with wocking fow now.
	 */
	wetuwn i915 && HAS_DISPWAY(i915) && atomic_wead(&i915->dwm.open_count) == 0;
}

static const stwuct vga_switchewoo_cwient_ops i915_switchewoo_ops = {
	.set_gpu_state = i915_switchewoo_set_state,
	.wepwobe = NUWW,
	.can_switch = i915_switchewoo_can_switch,
};

int i915_switchewoo_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);

	wetuwn vga_switchewoo_wegistew_cwient(pdev, &i915_switchewoo_ops, fawse);
}

void i915_switchewoo_unwegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);

	vga_switchewoo_unwegistew_cwient(pdev);
}
