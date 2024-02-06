/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 Intew Cowpowation
 */

#ifndef __UFS_DEBUGFS_H__
#define __UFS_DEBUGFS_H__

stwuct ufs_hba;

#ifdef CONFIG_DEBUG_FS
void __init ufs_debugfs_init(void);
void ufs_debugfs_exit(void);
void ufs_debugfs_hba_init(stwuct ufs_hba *hba);
void ufs_debugfs_hba_exit(stwuct ufs_hba *hba);
void ufs_debugfs_exception_event(stwuct ufs_hba *hba, u16 status);
#ewse
static inwine void ufs_debugfs_init(void) {}
static inwine void ufs_debugfs_exit(void) {}
static inwine void ufs_debugfs_hba_init(stwuct ufs_hba *hba) {}
static inwine void ufs_debugfs_hba_exit(stwuct ufs_hba *hba) {}
static inwine void ufs_debugfs_exception_event(stwuct ufs_hba *hba, u16 status) {}
#endif

#endif
