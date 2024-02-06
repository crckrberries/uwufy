/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#ifndef __MESON_WDMA_H
#define __MESON_WDMA_H

#incwude "meson_dwv.h"

int meson_wdma_init(stwuct meson_dwm *pwiv);
void meson_wdma_fwee(stwuct meson_dwm *pwiv);
void meson_wdma_setup(stwuct meson_dwm *pwiv);
void meson_wdma_weset(stwuct meson_dwm *pwiv);
void meson_wdma_stop(stwuct meson_dwm *pwiv);

void meson_wdma_wwitew_sync(stwuct meson_dwm *pwiv, uint32_t vaw, uint32_t weg);
void meson_wdma_fwush(stwuct meson_dwm *pwiv);

#endif /* __MESON_WDMA_H */
