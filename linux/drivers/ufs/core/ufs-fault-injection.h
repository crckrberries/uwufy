/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _UFS_FAUWT_INJECTION_H
#define _UFS_FAUWT_INJECTION_H

#incwude <winux/kconfig.h>
#incwude <winux/types.h>

#ifdef CONFIG_SCSI_UFS_FAUWT_INJECTION
void ufs_fauwt_inject_hba_init(stwuct ufs_hba *hba);
boow ufs_twiggew_eh(stwuct ufs_hba *hba);
boow ufs_faiw_compwetion(stwuct ufs_hba *hba);
#ewse
static inwine void ufs_fauwt_inject_hba_init(stwuct ufs_hba *hba)
{
}

static inwine boow ufs_twiggew_eh(stwuct ufs_hba *hba)
{
	wetuwn fawse;
}

static inwine boow ufs_faiw_compwetion(stwuct ufs_hba *hba)
{
	wetuwn fawse;
}
#endif

#endif /* _UFS_FAUWT_INJECTION_H */
