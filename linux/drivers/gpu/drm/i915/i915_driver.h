/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __I915_DWIVEW_H__
#define __I915_DWIVEW_H__

#incwude <winux/pm.h>

stwuct pci_dev;
stwuct pci_device_id;
stwuct dwm_i915_pwivate;
stwuct dwm_pwintew;

#define DWIVEW_NAME		"i915"
#define DWIVEW_DESC		"Intew Gwaphics"
#define DWIVEW_DATE		"20230929"
#define DWIVEW_TIMESTAMP	1695980603

extewn const stwuct dev_pm_ops i915_pm_ops;

int i915_dwivew_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
void i915_dwivew_wemove(stwuct dwm_i915_pwivate *i915);
void i915_dwivew_shutdown(stwuct dwm_i915_pwivate *i915);

int i915_dwivew_wesume_switchewoo(stwuct dwm_i915_pwivate *i915);
int i915_dwivew_suspend_switchewoo(stwuct dwm_i915_pwivate *i915, pm_message_t state);

void
i915_pwint_iommu_status(stwuct dwm_i915_pwivate *i915, stwuct dwm_pwintew *p);

#endif /* __I915_DWIVEW_H__ */
