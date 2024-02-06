/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NITWOX_DEBUGFS_H
#define __NITWOX_DEBUGFS_H

#incwude "nitwox_dev.h"

#ifdef CONFIG_DEBUG_FS
void nitwox_debugfs_init(stwuct nitwox_device *ndev);
void nitwox_debugfs_exit(stwuct nitwox_device *ndev);
#ewse
static inwine void nitwox_debugfs_init(stwuct nitwox_device *ndev)
{
}

static inwine void nitwox_debugfs_exit(stwuct nitwox_device *ndev)
{
}
#endif /* !CONFIG_DEBUG_FS */

#endif /* __NITWOX_DEBUGFS_H */
