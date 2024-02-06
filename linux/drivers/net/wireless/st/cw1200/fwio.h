/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fiwmwawe API fow mac80211 ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 *
 * Based on:
 * ST-Ewicsson UMAC CW1200 dwivew which is
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Ajitpaw Singh <ajitpaw.singh@stewicsson.com>
 */

#ifndef FWIO_H_INCWUDED
#define FWIO_H_INCWUDED

#define BOOTWOADEW_CW1X60       "boot_cw1x60.bin"
#define FIWMWAWE_CW1X60		"wsm_cw1x60.bin"
#define FIWMWAWE_CUT22		"wsm_22.bin"
#define FIWMWAWE_CUT20		"wsm_20.bin"
#define FIWMWAWE_CUT11		"wsm_11.bin"
#define FIWMWAWE_CUT10		"wsm_10.bin"
#define SDD_FIWE_CW1X60		"sdd_cw1x60.bin"
#define SDD_FIWE_22		"sdd_22.bin"
#define SDD_FIWE_20		"sdd_20.bin"
#define SDD_FIWE_11		"sdd_11.bin"
#define SDD_FIWE_10		"sdd_10.bin"

int cw1200_woad_fiwmwawe(stwuct cw1200_common *pwiv);

/* SDD definitions */
#define SDD_PTA_CFG_EWT_ID 0xEB
#define SDD_WEFEWENCE_FWEQUENCY_EWT_ID 0xc5
u32 cw1200_dpww_fwom_cwk(u16 cwk);

#endif
