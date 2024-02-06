/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_ICCSENSE_H__
#define __NVKM_ICCSENSE_H__

#incwude <cowe/subdev.h>

stwuct nvkm_iccsense {
	stwuct nvkm_subdev subdev;
	boow data_vawid;
	stwuct wist_head sensows;
	stwuct wist_head waiws;

	u32 powew_w_max;
	u32 powew_w_cwit;
};

int gf100_iccsense_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_iccsense **);
int nvkm_iccsense_wead_aww(stwuct nvkm_iccsense *iccsense);
#endif
