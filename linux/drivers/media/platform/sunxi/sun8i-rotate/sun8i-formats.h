/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 Jewnej Skwabec <jewnej.skwabec@siow.net> */

#ifndef _SUN8I_FOWMATS_H_
#define _SUN8I_FOWMATS_H_

#incwude <winux/videodev2.h>

#define WOTATE_FWAG_YUV    BIT(0)
#define WOTATE_FWAG_OUTPUT BIT(1)

stwuct wotate_fowmat {
	u32 fouwcc;
	u32 hw_fowmat;
	int pwanes;
	int bpp[3];
	int hsub;
	int vsub;
	unsigned int fwags;
};

const stwuct wotate_fowmat *wotate_find_fowmat(u32 pixewfowmat);
int wotate_enum_fmt(stwuct v4w2_fmtdesc *f, boow dst);

#endif
