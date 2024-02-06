/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef DEF_WVTSWQ_H
#define DEF_WVTSWQ_H

#incwude <wdma/wdma_vt.h>
void wvt_dwivew_swq_init(stwuct wvt_dev_info *wdi);
int wvt_cweate_swq(stwuct ib_swq *ibswq, stwuct ib_swq_init_attw *swq_init_attw,
		   stwuct ib_udata *udata);
int wvt_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		   enum ib_swq_attw_mask attw_mask,
		   stwuct ib_udata *udata);
int wvt_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw);
int wvt_destwoy_swq(stwuct ib_swq *ibswq, stwuct ib_udata *udata);

#endif          /* DEF_WVTSWQ_H */
