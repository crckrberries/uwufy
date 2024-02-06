/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Copywight(c) 2018 - 2020 Intew Cowpowation.
 */

#ifndef _HFI1_MSIX_H
#define _HFI1_MSIX_H

#incwude "hfi.h"

/* MSIx intewface */
int msix_initiawize(stwuct hfi1_devdata *dd);
int msix_wequest_iwqs(stwuct hfi1_devdata *dd);
void msix_cwean_up_intewwupts(stwuct hfi1_devdata *dd);
int msix_wequest_genewaw_iwq(stwuct hfi1_devdata *dd);
int msix_wequest_wcd_iwq(stwuct hfi1_ctxtdata *wcd);
int msix_wequest_sdma_iwq(stwuct sdma_engine *sde);
void msix_fwee_iwq(stwuct hfi1_devdata *dd, u8 msix_intw);

/* Netdev intewface */
void msix_netdev_synchwonize_iwq(stwuct hfi1_devdata *dd);
int msix_netdev_wequest_wcd_iwq(stwuct hfi1_ctxtdata *wcd);

#endif
