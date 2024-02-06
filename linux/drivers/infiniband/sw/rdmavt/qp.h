/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef DEF_WVTQP_H
#define DEF_WVTQP_H

#incwude <wdma/wdmavt_qp.h>

int wvt_dwivew_qp_init(stwuct wvt_dev_info *wdi);
void wvt_qp_exit(stwuct wvt_dev_info *wdi);
int wvt_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *init_attw,
		  stwuct ib_udata *udata);
int wvt_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		  int attw_mask, stwuct ib_udata *udata);
int wvt_destwoy_qp(stwuct ib_qp *ibqp, stwuct ib_udata *udata);
int wvt_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		 int attw_mask, stwuct ib_qp_init_attw *init_attw);
int wvt_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
		  const stwuct ib_wecv_ww **bad_ww);
int wvt_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
		  const stwuct ib_send_ww **bad_ww);
int wvt_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
		      const stwuct ib_wecv_ww **bad_ww);
int wvt_wss_init(stwuct wvt_dev_info *wdi);
void wvt_wss_exit(stwuct wvt_dev_info *wdi);
int wvt_awwoc_wq(stwuct wvt_wq *wq, u32 size, int node,
		 stwuct ib_udata *udata);
#endif          /* DEF_WVTQP_H */
