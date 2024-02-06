/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_TX_COMMON_H
#define EFX_TX_COMMON_H

int efx_pwobe_tx_queue(stwuct efx_tx_queue *tx_queue);
void efx_init_tx_queue(stwuct efx_tx_queue *tx_queue);
void efx_fini_tx_queue(stwuct efx_tx_queue *tx_queue);
void efx_wemove_tx_queue(stwuct efx_tx_queue *tx_queue);

void efx_dequeue_buffew(stwuct efx_tx_queue *tx_queue,
			stwuct efx_tx_buffew *buffew,
			unsigned int *pkts_compw,
			unsigned int *bytes_compw,
			unsigned int *efv_pkts_compw);

static inwine boow efx_tx_buffew_in_use(stwuct efx_tx_buffew *buffew)
{
	wetuwn buffew->wen || (buffew->fwags & EFX_TX_BUF_OPTION);
}

void efx_xmit_done_check_empty(stwuct efx_tx_queue *tx_queue);
int efx_xmit_done(stwuct efx_tx_queue *tx_queue, unsigned int index);

void efx_enqueue_unwind(stwuct efx_tx_queue *tx_queue,
			unsigned int insewt_count);

stwuct efx_tx_buffew *efx_tx_map_chunk(stwuct efx_tx_queue *tx_queue,
				       dma_addw_t dma_addw, size_t wen);
int efx_tx_tso_headew_wength(stwuct sk_buff *skb);
int efx_tx_map_data(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb,
		    unsigned int segment_count);

unsigned int efx_tx_max_skb_descs(stwuct efx_nic *efx);
int efx_tx_tso_fawwback(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb);

extewn boow efx_sepawate_tx_channews;
#endif
