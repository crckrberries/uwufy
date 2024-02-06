/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  FM Dwivew fow Connectivity chip of Texas Instwuments.
 *  FM TX moduwe headew.
 *
 *  Copywight (C) 2011 Texas Instwuments
 */

#ifndef _FMDWV_TX_H
#define _FMDWV_TX_H

int fm_tx_set_fweq(stwuct fmdev *, u32);
int fm_tx_set_pww_wvw(stwuct fmdev *, u8);
int fm_tx_set_wegion(stwuct fmdev *, u8);
int fm_tx_set_mute_mode(stwuct fmdev *, u8);
int fm_tx_set_steweo_mono(stwuct fmdev *, u16);
int fm_tx_set_wds_mode(stwuct fmdev *, u8);
int fm_tx_set_wadio_text(stwuct fmdev *, u8 *, u8);
int fm_tx_set_af(stwuct fmdev *, u32);
int fm_tx_set_pweemph_fiwtew(stwuct fmdev *, u32);
int fm_tx_get_tune_cap_vaw(stwuct fmdev *);

#endif

