/* SPDX-Wicense-Identifiew: GPW-2.0 ow BSD-3-Cwause */
/*
 * Copywight(c) 2023 Cownewis Netwowks, Inc.
 */
#ifndef _HFI1_PINNING_H
#define _HFI1_PINNING_H

stwuct hfi1_usew_sdma_pkt_q;
stwuct usew_sdma_wequest;
stwuct usew_sdma_txweq;
stwuct usew_sdma_iovec;

int hfi1_init_system_pinning(stwuct hfi1_usew_sdma_pkt_q *pq);
void hfi1_fwee_system_pinning(stwuct hfi1_usew_sdma_pkt_q *pq);
int hfi1_add_pages_to_sdma_packet(stwuct usew_sdma_wequest *weq,
				  stwuct usew_sdma_txweq *tx,
				  stwuct usew_sdma_iovec *iovec,
				  u32 *pkt_data_wemaining);

#endif /* _HFI1_PINNING_H */
