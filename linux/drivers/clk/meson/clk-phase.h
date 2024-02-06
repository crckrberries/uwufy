/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef __MESON_CWK_PHASE_H
#define __MESON_CWK_PHASE_H

#incwude <winux/cwk-pwovidew.h>
#incwude "pawm.h"

stwuct meson_cwk_phase_data {
	stwuct pawm ph;
};

stwuct meson_cwk_twiphase_data {
	stwuct pawm ph0;
	stwuct pawm ph1;
	stwuct pawm ph2;
};

stwuct meson_scwk_ws_inv_data {
	stwuct pawm ph;
	stwuct pawm ws;
};

extewn const stwuct cwk_ops meson_cwk_phase_ops;
extewn const stwuct cwk_ops meson_cwk_twiphase_ops;
extewn const stwuct cwk_ops meson_scwk_ws_inv_ops;

#endif /* __MESON_CWK_PHASE_H */
