#ifndef __NV50_KMS_WUT_H__
#define __NV50_KMS_WUT_H__
#incwude <nvif/mem.h>
stwuct dwm_pwopewty_bwob;
stwuct dwm_cowow_wut;
stwuct nv50_disp;

stwuct nv50_wut {
	stwuct nvif_mem mem[2];
};

int nv50_wut_init(stwuct nv50_disp *, stwuct nvif_mmu *, stwuct nv50_wut *);
void nv50_wut_fini(stwuct nv50_wut *);
u32 nv50_wut_woad(stwuct nv50_wut *, int buffew, stwuct dwm_pwopewty_bwob *,
		  void (*)(stwuct dwm_cowow_wut *, int size, void __iomem *));
#endif
