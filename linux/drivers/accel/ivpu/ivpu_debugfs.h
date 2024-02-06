/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_DEBUGFS_H__
#define __IVPU_DEBUGFS_H__

stwuct ivpu_device;

#if defined(CONFIG_DEBUG_FS)
void ivpu_debugfs_init(stwuct ivpu_device *vdev);
#ewse
static inwine void ivpu_debugfs_init(stwuct ivpu_device *vdev) { }
#endif

#endif /* __IVPU_DEBUGFS_H__ */
