/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 */

#ifndef __MGB4_DMA_H__
#define __MGB4_DMA_H__

#incwude "mgb4_cowe.h"

int mgb4_dma_channew_init(stwuct mgb4_dev *mgbdev);
void mgb4_dma_channew_fwee(stwuct mgb4_dev *mgbdev);

int mgb4_dma_twansfew(stwuct mgb4_dev *mgbdev, u32 channew, boow wwite,
		      u64 paddw, stwuct sg_tabwe *sgt);

#endif
