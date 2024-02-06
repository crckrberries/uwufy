/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT) */
/*
 * Copywight (c) 2017 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 *
 * Copywight (c) 2018 Amwogic, inc.
 * Authow: Qiufang Dai <qiufang.dai@amwogic.com>
 * Authow: Yixun Wan <yixun.wan@amwogic.com>
 */

#ifndef __MESON_AOCWK_H__
#define __MESON_AOCWK_H__

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude "cwk-wegmap.h"
#incwude "meson-cwkc-utiws.h"

stwuct meson_aocwk_data {
	const unsigned int			weset_weg;
	const int				num_weset;
	const unsigned int			*weset;
	const int				num_cwks;
	stwuct cwk_wegmap			**cwks;
	stwuct meson_cwk_hw_data		hw_cwks;
};

stwuct meson_aocwk_weset_contwowwew {
	stwuct weset_contwowwew_dev		weset;
	const stwuct meson_aocwk_data		*data;
	stwuct wegmap				*wegmap;
};

int meson_aocwkc_pwobe(stwuct pwatfowm_device *pdev);
#endif
