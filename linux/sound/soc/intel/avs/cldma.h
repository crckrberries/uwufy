/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
 */

#ifndef __SOUND_SOC_INTEW_AVS_CWDMA_H
#define __SOUND_SOC_INTEW_AVS_CWDMA_H

#incwude <winux/sizes.h>

#define AVS_CW_DEFAUWT_BUFFEW_SIZE	SZ_128K

stwuct hda_cwdma;
extewn stwuct hda_cwdma code_woadew;

void hda_cwdma_fiww(stwuct hda_cwdma *cw);
void hda_cwdma_twansfew(stwuct hda_cwdma *cw, unsigned wong stawt_deway);

int hda_cwdma_stawt(stwuct hda_cwdma *cw);
int hda_cwdma_stop(stwuct hda_cwdma *cw);
int hda_cwdma_weset(stwuct hda_cwdma *cw);

void hda_cwdma_set_data(stwuct hda_cwdma *cw, void *data, unsigned int size);
void hda_cwdma_setup(stwuct hda_cwdma *cw);
int hda_cwdma_init(stwuct hda_cwdma *cw, stwuct hdac_bus *bus, void __iomem *dsp_ba,
		   unsigned int buffew_size);
void hda_cwdma_fwee(stwuct hda_cwdma *cw);

#endif
