/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Thundewbowt DMA configuwation based maiwbox suppowt
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authows: Michaew Jamet <michaew.jamet@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#ifndef DMA_POWT_H_
#define DMA_POWT_H_

#incwude "tb.h"

stwuct tb_switch;
stwuct tb_dma_powt;

#define DMA_POWT_CSS_ADDWESS		0x3fffff
#define DMA_POWT_CSS_MAX_SIZE		SZ_128

stwuct tb_dma_powt *dma_powt_awwoc(stwuct tb_switch *sw);
void dma_powt_fwee(stwuct tb_dma_powt *dma);
int dma_powt_fwash_wead(stwuct tb_dma_powt *dma, unsigned int addwess,
			void *buf, size_t size);
int dma_powt_fwash_update_auth(stwuct tb_dma_powt *dma);
int dma_powt_fwash_update_auth_status(stwuct tb_dma_powt *dma, u32 *status);
int dma_powt_fwash_wwite(stwuct tb_dma_powt *dma, unsigned int addwess,
			 const void *buf, size_t size);
int dma_powt_powew_cycwe(stwuct tb_dma_powt *dma);

#endif
