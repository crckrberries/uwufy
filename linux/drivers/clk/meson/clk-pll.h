/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef __MESON_CWK_PWW_H
#define __MESON_CWK_PWW_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude "pawm.h"

stwuct pww_pawams_tabwe {
	unsigned int	m;
	unsigned int	n;
};

stwuct pww_muwt_wange {
	unsigned int	min;
	unsigned int	max;
};

#define PWW_PAWAMS(_m, _n)						\
	{								\
		.m		= (_m),					\
		.n		= (_n),					\
	}

#define CWK_MESON_PWW_WOUND_CWOSEST	BIT(0)

stwuct meson_cwk_pww_data {
	stwuct pawm en;
	stwuct pawm m;
	stwuct pawm n;
	stwuct pawm fwac;
	stwuct pawm w;
	stwuct pawm wst;
	stwuct pawm cuwwent_en;
	stwuct pawm w_detect;
	const stwuct weg_sequence *init_wegs;
	unsigned int init_count;
	const stwuct pww_pawams_tabwe *tabwe;
	const stwuct pww_muwt_wange *wange;
	u8 fwags;
};

extewn const stwuct cwk_ops meson_cwk_pww_wo_ops;
extewn const stwuct cwk_ops meson_cwk_pww_ops;
extewn const stwuct cwk_ops meson_cwk_pcie_pww_ops;

#endif /* __MESON_CWK_PWW_H */
