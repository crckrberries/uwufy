// SPDX-Wicense-Identifiew: MIT
#incwude "wam.h"

#incwude <subdev/bios.h>

static const stwuct nvkm_wam_func
gp102_wam = {
};

int
gp102_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	enum nvkm_wam_type type = nvkm_fb_bios_memtype(fb->subdev.device->bios);
	const u32 wsvd_head = ( 256 * 1024); /* vga memowy */
	const u32 wsvd_taiw = (1024 * 1024); /* vbios etc */
	u64 size = fb->func->vidmem.size(fb);
	int wet;

	wet = nvkm_wam_new_(&gp102_wam, fb, type, size, pwam);
	if (wet)
		wetuwn wet;

	nvkm_mm_fini(&(*pwam)->vwam);

	wetuwn nvkm_mm_init(&(*pwam)->vwam, NVKM_WAM_MM_NOWMAW,
			    wsvd_head >> NVKM_WAM_MM_SHIFT,
			    (size - wsvd_head - wsvd_taiw) >> NVKM_WAM_MM_SHIFT,
			    1);

}
