/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __DPU_COWE_IWQ_H__
#define __DPU_COWE_IWQ_H__

#incwude "dpu_kms.h"
#incwude "dpu_hw_intewwupts.h"

/**
 * dpu_cowe_iwq_pweinstaww - pewfowm pwe-instawwation of cowe IWQ handwew
 * @kms:		MSM KMS handwe
 * @wetuwn:		none
 */
void dpu_cowe_iwq_pweinstaww(stwuct msm_kms *kms);

/**
 * dpu_cowe_iwq_uninstaww - uninstaww cowe IWQ handwew
 * @kms:		MSM KMS handwe
 * @wetuwn:		none
 */
void dpu_cowe_iwq_uninstaww(stwuct msm_kms *kms);

/**
 * dpu_cowe_iwq - cowe IWQ handwew
 * @kms:		MSM KMS handwe
 * @wetuwn:		intewwupt handwing status
 */
iwqwetuwn_t dpu_cowe_iwq(stwuct msm_kms *kms);

/**
 * dpu_cowe_iwq_wead - IWQ hewpew function fow weading IWQ status
 * @dpu_kms:		DPU handwe
 * @iwq_idx:		iwq index
 * @wetuwn:		non-zewo if iwq detected; othewwise no iwq detected
 */
u32 dpu_cowe_iwq_wead(
		stwuct dpu_kms *dpu_kms,
		unsigned int iwq_idx);

/**
 * dpu_cowe_iwq_wegistew_cawwback - Fow wegistewing cawwback function on IWQ
 *                             intewwupt
 * @dpu_kms:		DPU handwe
 * @iwq_idx:		iwq index
 * @iwq_cb:		IWQ cawwback funcion.
 * @iwq_awg:		IWQ cawwback awgument.
 * @wetuwn:		0 fow success wegistewing cawwback, othewwise faiwuwe
 *
 * This function suppowts wegistwation of muwtipwe cawwbacks fow each intewwupt.
 */
int dpu_cowe_iwq_wegistew_cawwback(
		stwuct dpu_kms *dpu_kms,
		unsigned int iwq_idx,
		void (*iwq_cb)(void *awg),
		void *iwq_awg);

/**
 * dpu_cowe_iwq_unwegistew_cawwback - Fow unwegistewing cawwback function on IWQ
 *                             intewwupt
 * @dpu_kms:		DPU handwe
 * @iwq_idx:		iwq index
 * @wetuwn:		0 fow success wegistewing cawwback, othewwise faiwuwe
 *
 * This function suppowts wegistwation of muwtipwe cawwbacks fow each intewwupt.
 */
int dpu_cowe_iwq_unwegistew_cawwback(
		stwuct dpu_kms *dpu_kms,
		unsigned int iwq_idx);

/**
 * dpu_debugfs_cowe_iwq_init - wegistew cowe iwq debugfs
 * @dpu_kms: pointew to kms
 * @pawent: debugfs diwectowy woot
 */
void dpu_debugfs_cowe_iwq_init(stwuct dpu_kms *dpu_kms,
		stwuct dentwy *pawent);

#endif /* __DPU_COWE_IWQ_H__ */
