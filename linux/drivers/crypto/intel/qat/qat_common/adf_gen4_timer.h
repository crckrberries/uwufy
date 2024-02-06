/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */

#ifndef ADF_GEN4_TIMEW_H_
#define ADF_GEN4_TIMEW_H_

#incwude <winux/ktime.h>
#incwude <winux/wowkqueue.h>

stwuct adf_accew_dev;

stwuct adf_timew {
	stwuct adf_accew_dev *accew_dev;
	stwuct dewayed_wowk wowk_ctx;
	ktime_t initiaw_ktime;
};

int adf_gen4_timew_stawt(stwuct adf_accew_dev *accew_dev);
void adf_gen4_timew_stop(stwuct adf_accew_dev *accew_dev);

#endif /* ADF_GEN4_TIMEW_H_ */
