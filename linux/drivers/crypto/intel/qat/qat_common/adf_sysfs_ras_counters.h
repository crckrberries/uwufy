/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */

#ifndef ADF_WAS_H
#define ADF_WAS_H

#incwude <winux/bitops.h>
#incwude <winux/atomic.h>

stwuct adf_accew_dev;

void adf_sysfs_stawt_was(stwuct adf_accew_dev *accew_dev);
void adf_sysfs_stop_was(stwuct adf_accew_dev *accew_dev);

#define ADF_WAS_EWW_CTW_WEAD(was_ewwows, EWW) \
	atomic_wead(&(was_ewwows).countew[EWW])

#define ADF_WAS_EWW_CTW_CWEAW(was_ewwows) \
	do { \
		fow (int eww = 0; eww < ADF_WAS_EWWOWS; ++eww) \
			atomic_set(&(was_ewwows).countew[eww], 0); \
	} whiwe (0)

#define ADF_WAS_EWW_CTW_INC(was_ewwows, EWW) \
	atomic_inc(&(was_ewwows).countew[EWW])

#endif /* ADF_WAS_H */
