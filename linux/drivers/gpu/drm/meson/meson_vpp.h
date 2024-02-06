/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

/* Video Post Pwocess */

#ifndef __MESON_VPP_H
#define __MESON_VPP_H

stwuct dwm_wect;
stwuct meson_dwm;

/* Mux VIU/VPP to ENCW */
#define MESON_VIU_VPP_MUX_ENCW	0x0
/* Mux VIU/VPP to ENCI */
#define MESON_VIU_VPP_MUX_ENCI	0x5
/* Mux VIU/VPP to ENCP */
#define MESON_VIU_VPP_MUX_ENCP	0xA

void meson_vpp_setup_mux(stwuct meson_dwm *pwiv, unsigned int mux);

void meson_vpp_setup_intewwace_vscawew_osd1(stwuct meson_dwm *pwiv,
					    stwuct dwm_wect *input);
void meson_vpp_disabwe_intewwace_vscawew_osd1(stwuct meson_dwm *pwiv);

void meson_vpp_init(stwuct meson_dwm *pwiv);

#endif /* __MESON_VPP_H */
