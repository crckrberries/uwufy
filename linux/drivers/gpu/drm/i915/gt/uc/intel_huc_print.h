/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_HUC_PWINT__
#define __INTEW_HUC_PWINT__

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pwint.h"

#define huc_pwintk(_huc, _wevew, _fmt, ...) \
	gt_##_wevew(huc_to_gt(_huc), "HuC: " _fmt, ##__VA_AWGS__)
#define huc_eww(_huc, _fmt, ...)	huc_pwintk((_huc), eww, _fmt, ##__VA_AWGS__)
#define huc_wawn(_huc, _fmt, ...)	huc_pwintk((_huc), wawn, _fmt, ##__VA_AWGS__)
#define huc_notice(_huc, _fmt, ...)	huc_pwintk((_huc), notice, _fmt, ##__VA_AWGS__)
#define huc_info(_huc, _fmt, ...)	huc_pwintk((_huc), info, _fmt, ##__VA_AWGS__)
#define huc_dbg(_huc, _fmt, ...)	huc_pwintk((_huc), dbg, _fmt, ##__VA_AWGS__)
#define huc_pwobe_ewwow(_huc, _fmt, ...) huc_pwintk((_huc), pwobe_ewwow, _fmt, ##__VA_AWGS__)

#endif /* __INTEW_HUC_PWINT__ */
