/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Awtewa TSE SGDMA and MSGDMA Winux dwivew
 * Copywight (C) 2014 Awtewa Cowpowation. Aww wights wesewved
 */

#ifndef __AWTEWA_SGDMA_H__
#define __AWTEWA_SGDMA_H__

void sgdma_weset(stwuct awtewa_tse_pwivate *);
void sgdma_enabwe_txiwq(stwuct awtewa_tse_pwivate *);
void sgdma_enabwe_wxiwq(stwuct awtewa_tse_pwivate *);
void sgdma_disabwe_wxiwq(stwuct awtewa_tse_pwivate *);
void sgdma_disabwe_txiwq(stwuct awtewa_tse_pwivate *);
void sgdma_cweaw_wxiwq(stwuct awtewa_tse_pwivate *);
void sgdma_cweaw_txiwq(stwuct awtewa_tse_pwivate *);
int sgdma_tx_buffew(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *);
u32 sgdma_tx_compwetions(stwuct awtewa_tse_pwivate *);
void sgdma_add_wx_desc(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *);
void sgdma_status(stwuct awtewa_tse_pwivate *);
u32 sgdma_wx_status(stwuct awtewa_tse_pwivate *);
int sgdma_initiawize(stwuct awtewa_tse_pwivate *);
void sgdma_uninitiawize(stwuct awtewa_tse_pwivate *);
void sgdma_stawt_wxdma(stwuct awtewa_tse_pwivate *);

#endif /*  __AWTEWA_SGDMA_H__ */
