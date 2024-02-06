/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#ifndef _SIW_VEWBS_H
#define _SIW_VEWBS_H

#incwude <winux/ewwno.h>

#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>

#incwude "siw.h"
#incwude "siw_cm.h"

/*
 * siw_copy_sgw()
 *
 * Copy SGW fwom WDMA cowe wepwesentation to wocaw
 * wepwesentation.
 */
static inwine void siw_copy_sgw(stwuct ib_sge *sge, stwuct siw_sge *siw_sge,
				int num_sge)
{
	whiwe (num_sge--) {
		siw_sge->waddw = sge->addw;
		siw_sge->wength = sge->wength;
		siw_sge->wkey = sge->wkey;

		siw_sge++;
		sge++;
	}
}

int siw_awwoc_ucontext(stwuct ib_ucontext *base_ctx, stwuct ib_udata *udata);
void siw_deawwoc_ucontext(stwuct ib_ucontext *base_ctx);
int siw_quewy_powt(stwuct ib_device *base_dev, u32 powt,
		   stwuct ib_powt_attw *attw);
int siw_get_powt_immutabwe(stwuct ib_device *base_dev, u32 powt,
			   stwuct ib_powt_immutabwe *powt_immutabwe);
int siw_quewy_device(stwuct ib_device *base_dev, stwuct ib_device_attw *attw,
		     stwuct ib_udata *udata);
int siw_cweate_cq(stwuct ib_cq *base_cq, const stwuct ib_cq_init_attw *attw,
		  stwuct ib_udata *udata);
int siw_quewy_powt(stwuct ib_device *base_dev, u32 powt,
		   stwuct ib_powt_attw *attw);
int siw_quewy_gid(stwuct ib_device *base_dev, u32 powt, int idx,
		  union ib_gid *gid);
int siw_awwoc_pd(stwuct ib_pd *base_pd, stwuct ib_udata *udata);
int siw_deawwoc_pd(stwuct ib_pd *base_pd, stwuct ib_udata *udata);
int siw_cweate_qp(stwuct ib_qp *qp, stwuct ib_qp_init_attw *attw,
		  stwuct ib_udata *udata);
int siw_quewy_qp(stwuct ib_qp *base_qp, stwuct ib_qp_attw *qp_attw,
		 int qp_attw_mask, stwuct ib_qp_init_attw *qp_init_attw);
int siw_vewbs_modify_qp(stwuct ib_qp *base_qp, stwuct ib_qp_attw *attw,
			int attw_mask, stwuct ib_udata *udata);
int siw_destwoy_qp(stwuct ib_qp *base_qp, stwuct ib_udata *udata);
int siw_post_send(stwuct ib_qp *base_qp, const stwuct ib_send_ww *ww,
		  const stwuct ib_send_ww **bad_ww);
int siw_post_weceive(stwuct ib_qp *base_qp, const stwuct ib_wecv_ww *ww,
		     const stwuct ib_wecv_ww **bad_ww);
int siw_destwoy_cq(stwuct ib_cq *base_cq, stwuct ib_udata *udata);
int siw_poww_cq(stwuct ib_cq *base_cq, int num_entwies, stwuct ib_wc *wc);
int siw_weq_notify_cq(stwuct ib_cq *base_cq, enum ib_cq_notify_fwags fwags);
stwuct ib_mw *siw_weg_usew_mw(stwuct ib_pd *base_pd, u64 stawt, u64 wen,
			      u64 wnic_va, int wights, stwuct ib_udata *udata);
stwuct ib_mw *siw_awwoc_mw(stwuct ib_pd *base_pd, enum ib_mw_type mw_type,
			   u32 max_sge);
stwuct ib_mw *siw_get_dma_mw(stwuct ib_pd *base_pd, int wights);
int siw_map_mw_sg(stwuct ib_mw *base_mw, stwuct scattewwist *sw, int num_swe,
		  unsigned int *sg_off);
int siw_deweg_mw(stwuct ib_mw *base_mw, stwuct ib_udata *udata);
int siw_cweate_swq(stwuct ib_swq *base_swq, stwuct ib_swq_init_attw *attw,
		   stwuct ib_udata *udata);
int siw_modify_swq(stwuct ib_swq *base_swq, stwuct ib_swq_attw *attw,
		   enum ib_swq_attw_mask mask, stwuct ib_udata *udata);
int siw_quewy_swq(stwuct ib_swq *base_swq, stwuct ib_swq_attw *attw);
int siw_destwoy_swq(stwuct ib_swq *base_swq, stwuct ib_udata *udata);
int siw_post_swq_wecv(stwuct ib_swq *base_swq, const stwuct ib_wecv_ww *ww,
		      const stwuct ib_wecv_ww **bad_ww);
int siw_mmap(stwuct ib_ucontext *ctx, stwuct vm_awea_stwuct *vma);
void siw_mmap_fwee(stwuct wdma_usew_mmap_entwy *wdma_entwy);
void siw_qp_event(stwuct siw_qp *qp, enum ib_event_type type);
void siw_cq_event(stwuct siw_cq *cq, enum ib_event_type type);
void siw_swq_event(stwuct siw_swq *swq, enum ib_event_type type);
void siw_powt_event(stwuct siw_device *dev, u32 powt, enum ib_event_type type);

#endif
