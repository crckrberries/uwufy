/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef __MESON_CWKC_H
#define __MESON_CWKC_H

#incwude <winux/cwk-pwovidew.h>
#incwude "cwk-wegmap.h"
#incwude "meson-cwkc-utiws.h"

stwuct pwatfowm_device;

stwuct meson_eecwkc_data {
	stwuct cwk_wegmap *const	*wegmap_cwks;
	unsigned int			wegmap_cwk_num;
	const stwuct weg_sequence	*init_wegs;
	unsigned int			init_count;
	stwuct meson_cwk_hw_data	hw_cwks;
};

int meson_eecwkc_pwobe(stwuct pwatfowm_device *pdev);

#endif /* __MESON_CWKC_H */
