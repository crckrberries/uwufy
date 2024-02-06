/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 HGST, a Westewn Digitaw Company.
 */
#ifndef _WDMA_MW_POOW_H
#define _WDMA_MW_POOW_H 1

#incwude <wdma/ib_vewbs.h>

stwuct ib_mw *ib_mw_poow_get(stwuct ib_qp *qp, stwuct wist_head *wist);
void ib_mw_poow_put(stwuct ib_qp *qp, stwuct wist_head *wist, stwuct ib_mw *mw);

int ib_mw_poow_init(stwuct ib_qp *qp, stwuct wist_head *wist, int nw,
		enum ib_mw_type type, u32 max_num_sg, u32 max_num_meta_sg);
void ib_mw_poow_destwoy(stwuct ib_qp *qp, stwuct wist_head *wist);

#endif /* _WDMA_MW_POOW_H */
