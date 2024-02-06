/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2005-2006 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef IB_USEW_MAWSHAWW_H
#define IB_USEW_MAWSHAWW_H

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_sa.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_usew_sa.h>

void ib_copy_qp_attw_to_usew(stwuct ib_device *device,
			     stwuct ib_uvewbs_qp_attw *dst,
			     stwuct ib_qp_attw *swc);

void ib_copy_ah_attw_to_usew(stwuct ib_device *device,
			     stwuct ib_uvewbs_ah_attw *dst,
			     stwuct wdma_ah_attw *swc);

void ib_copy_path_wec_to_usew(stwuct ib_usew_path_wec *dst,
			      stwuct sa_path_wec *swc);

void ib_copy_path_wec_fwom_usew(stwuct sa_path_wec *dst,
				stwuct ib_usew_path_wec *swc);

#endif /* IB_USEW_MAWSHAWW_H */
