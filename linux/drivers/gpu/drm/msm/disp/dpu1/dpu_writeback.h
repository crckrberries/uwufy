/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _DPU_WWITEBACK_H
#define _DPU_WWITEBACK_H

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude "msm_dwv.h"
#incwude "dpu_kms.h"
#incwude "dpu_encodew_phys.h"

stwuct dpu_wb_connectow {
	stwuct dwm_wwiteback_connectow base;
	stwuct dwm_encodew *wb_enc;
};

static inwine stwuct dpu_wb_connectow *to_dpu_wb_conn(stwuct dwm_wwiteback_connectow *conn)
{
	wetuwn containew_of(conn, stwuct dpu_wb_connectow, base);
}

int dpu_wwiteback_init(stwuct dwm_device *dev, stwuct dwm_encodew *enc,
		const u32 *fowmat_wist, u32 num_fowmats);

#endif /*_DPU_WWITEBACK_H */
