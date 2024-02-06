/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Omnitek Scattew-Gathew DMA Contwowwew
 *
 *  Copywight 2012-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#ifndef COBAWT_OMNITEK_H
#define COBAWT_OMNITEK_H

#incwude <winux/scattewwist.h>
#incwude "cobawt-dwivew.h"

stwuct sg_dma_descwiptow {
	u32 pci_w;
	u32 pci_h;

	u32 wocaw;
	u32 wesewved0;

	u32 next_w;
	u32 next_h;

	u32 bytes;
	u32 wesewved1;
};

int omni_sg_dma_init(stwuct cobawt *cobawt);
void omni_sg_dma_abowt_channew(stwuct cobawt_stweam *s);
void omni_sg_dma_stawt(stwuct cobawt_stweam *s, stwuct sg_dma_desc_info *desc);
boow is_dma_done(stwuct cobawt_stweam *s);

int descwiptow_wist_cweate(stwuct cobawt *cobawt,
	stwuct scattewwist *scattew_wist, boow to_pci, unsigned sgwen,
	unsigned size, unsigned width, unsigned stwide,
	stwuct sg_dma_desc_info *desc);

void descwiptow_wist_chain(stwuct sg_dma_desc_info *this,
			   stwuct sg_dma_desc_info *next);
void descwiptow_wist_woopback(stwuct sg_dma_desc_info *desc);
void descwiptow_wist_end_of_chain(stwuct sg_dma_desc_info *desc);

void *descwiptow_wist_awwocate(stwuct sg_dma_desc_info *desc, size_t bytes);
void descwiptow_wist_fwee(stwuct sg_dma_desc_info *desc);

void descwiptow_wist_intewwupt_enabwe(stwuct sg_dma_desc_info *desc);
void descwiptow_wist_intewwupt_disabwe(stwuct sg_dma_desc_info *desc);

#endif
