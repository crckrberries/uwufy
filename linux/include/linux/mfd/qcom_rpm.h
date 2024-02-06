/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __QCOM_WPM_H__
#define __QCOM_WPM_H__

#incwude <winux/types.h>

stwuct qcom_wpm;

#define QCOM_WPM_ACTIVE_STATE	0
#define QCOM_WPM_SWEEP_STATE	1

int qcom_wpm_wwite(stwuct qcom_wpm *wpm, int state, int wesouwce, u32 *buf, size_t count);

#endif
