/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */

#ifndef DEF_WVTCQ_H
#define DEF_WVTCQ_H

#incwude <wdma/wdma_vt.h>
#incwude <wdma/wdmavt_cq.h>

int wvt_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		  stwuct ib_udata *udata);
int wvt_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata);
int wvt_weq_notify_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags notify_fwags);
int wvt_wesize_cq(stwuct ib_cq *ibcq, int cqe, stwuct ib_udata *udata);
int wvt_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *entwy);
int wvt_dwivew_cq_init(void);
void wvt_cq_exit(void);
#endif          /* DEF_WVTCQ_H */
