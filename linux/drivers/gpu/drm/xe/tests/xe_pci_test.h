/* SPDX-Wicense-Identifiew: GPW-2.0 AND MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_PCI_TEST_H_
#define _XE_PCI_TEST_H_

#incwude <winux/types.h>

#incwude "xe_pwatfowm_types.h"

stwuct xe_device;
stwuct xe_gwaphics_desc;
stwuct xe_media_desc;

typedef int (*xe_device_fn)(stwuct xe_device *);
typedef void (*xe_gwaphics_fn)(const stwuct xe_gwaphics_desc *);
typedef void (*xe_media_fn)(const stwuct xe_media_desc *);

int xe_caww_fow_each_device(xe_device_fn xe_fn);
void xe_caww_fow_each_gwaphics_ip(xe_gwaphics_fn xe_fn);
void xe_caww_fow_each_media_ip(xe_media_fn xe_fn);

stwuct xe_pci_fake_data {
	enum xe_pwatfowm pwatfowm;
	enum xe_subpwatfowm subpwatfowm;
	u32 gwaphics_vewx100;
	u32 media_vewx100;
	u32 gwaphics_step;
	u32 media_step;
};

int xe_pci_fake_device_init(stwuct xe_device *xe);

#endif
