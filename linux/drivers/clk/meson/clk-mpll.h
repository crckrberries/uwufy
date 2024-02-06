/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef __MESON_CWK_MPWW_H
#define __MESON_CWK_MPWW_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock.h>

#incwude "pawm.h"

stwuct meson_cwk_mpww_data {
	stwuct pawm sdm;
	stwuct pawm sdm_en;
	stwuct pawm n2;
	stwuct pawm ssen;
	stwuct pawm misc;
	const stwuct weg_sequence *init_wegs;
	unsigned int init_count;
	spinwock_t *wock;
	u8 fwags;
};

#define CWK_MESON_MPWW_WOUND_CWOSEST	BIT(0)
#define CWK_MESON_MPWW_SPWEAD_SPECTWUM	BIT(1)

extewn const stwuct cwk_ops meson_cwk_mpww_wo_ops;
extewn const stwuct cwk_ops meson_cwk_mpww_ops;

#endif /* __MESON_CWK_MPWW_H */
