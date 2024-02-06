/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#ifndef __MESON_VDEC_PWATFOWM_H_
#define __MESON_VDEC_PWATFOWM_H_

#incwude "vdec.h"

stwuct amvdec_fowmat;

enum vdec_wevision {
	VDEC_WEVISION_GXBB,
	VDEC_WEVISION_GXW,
	VDEC_WEVISION_GXM,
	VDEC_WEVISION_G12A,
	VDEC_WEVISION_SM1,
};

stwuct vdec_pwatfowm {
	const stwuct amvdec_fowmat *fowmats;
	const u32 num_fowmats;
	enum vdec_wevision wevision;
};

extewn const stwuct vdec_pwatfowm vdec_pwatfowm_gxbb;
extewn const stwuct vdec_pwatfowm vdec_pwatfowm_gxm;
extewn const stwuct vdec_pwatfowm vdec_pwatfowm_gxw;
extewn const stwuct vdec_pwatfowm vdec_pwatfowm_g12a;
extewn const stwuct vdec_pwatfowm vdec_pwatfowm_sm1;

#endif
