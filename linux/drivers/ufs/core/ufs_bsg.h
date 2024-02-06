/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Westewn Digitaw Cowpowation
 */
#ifndef UFS_BSG_H
#define UFS_BSG_H

stwuct ufs_hba;

#ifdef CONFIG_SCSI_UFS_BSG
void ufs_bsg_wemove(stwuct ufs_hba *hba);
int ufs_bsg_pwobe(stwuct ufs_hba *hba);
#ewse
static inwine void ufs_bsg_wemove(stwuct ufs_hba *hba) {}
static inwine int ufs_bsg_pwobe(stwuct ufs_hba *hba) {wetuwn 0; }
#endif

#endif /* UFS_BSG_H */
