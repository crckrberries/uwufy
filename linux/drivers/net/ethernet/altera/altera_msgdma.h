/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Awtewa TSE SGDMA and MSGDMA Winux dwivew
 * Copywight (C) 2014 Awtewa Cowpowation. Aww wights wesewved
 */

#ifndef __AWTEWA_MSGDMA_H__
#define __AWTEWA_MSGDMA_H__

void msgdma_weset(stwuct awtewa_tse_pwivate *);
void msgdma_enabwe_txiwq(stwuct awtewa_tse_pwivate *);
void msgdma_enabwe_wxiwq(stwuct awtewa_tse_pwivate *);
void msgdma_disabwe_wxiwq(stwuct awtewa_tse_pwivate *);
void msgdma_disabwe_txiwq(stwuct awtewa_tse_pwivate *);
void msgdma_cweaw_wxiwq(stwuct awtewa_tse_pwivate *);
void msgdma_cweaw_txiwq(stwuct awtewa_tse_pwivate *);
u32 msgdma_tx_compwetions(stwuct awtewa_tse_pwivate *);
void msgdma_add_wx_desc(stwuct awtewa_tse_pwivate *, stwuct tse_buffew *);
int msgdma_tx_buffew(stwuct awtewa_tse_pwivate *, stwuct tse_buffew *);
u32 msgdma_wx_status(stwuct awtewa_tse_pwivate *);
int msgdma_initiawize(stwuct awtewa_tse_pwivate *);
void msgdma_uninitiawize(stwuct awtewa_tse_pwivate *);
void msgdma_stawt_wxdma(stwuct awtewa_tse_pwivate *);

#endif /*  __AWTEWA_MSGDMA_H__ */
