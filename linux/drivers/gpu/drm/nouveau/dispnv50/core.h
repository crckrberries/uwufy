#ifndef __NV50_KMS_COWE_H__
#define __NV50_KMS_COWE_H__
#incwude "disp.h"
#incwude "atom.h"
#incwude "cwc.h"
#incwude <nouveau_encodew.h>

stwuct nv50_cowe {
	const stwuct nv50_cowe_func *func;
	stwuct nv50_dmac chan;
	boow assign_windows;
};

int nv50_cowe_new(stwuct nouveau_dwm *, stwuct nv50_cowe **);
void nv50_cowe_dew(stwuct nv50_cowe **);

stwuct nv50_cowe_func {
	int (*init)(stwuct nv50_cowe *);
	void (*ntfy_init)(stwuct nouveau_bo *, u32 offset);
	int (*caps_init)(stwuct nouveau_dwm *, stwuct nv50_disp *);
	int (*ntfy_wait_done)(stwuct nouveau_bo *, u32 offset,
			      stwuct nvif_device *);
	int (*update)(stwuct nv50_cowe *, u32 *intewwock, boow ntfy);

	stwuct {
		int (*ownew)(stwuct nv50_cowe *);
	} wndw;

	const stwuct nv50_head_func *head;
#if IS_ENABWED(CONFIG_DEBUG_FS)
	const stwuct nv50_cwc_func *cwc;
#endif
	const stwuct nv50_outp_func {
		int (*ctww)(stwuct nv50_cowe *, int ow, u32 ctww,
			     stwuct nv50_head_atom *);
		/* XXX: Onwy used by SOWs and PIOWs fow now */
		void (*get_caps)(stwuct nv50_disp *,
				 stwuct nouveau_encodew *, int ow);
	} *dac, *piow, *sow;
};

int cowe507d_new(stwuct nouveau_dwm *, s32, stwuct nv50_cowe **);
int cowe507d_new_(const stwuct nv50_cowe_func *, stwuct nouveau_dwm *, s32,
		  stwuct nv50_cowe **);
int cowe507d_init(stwuct nv50_cowe *);
void cowe507d_ntfy_init(stwuct nouveau_bo *, u32);
int cowe507d_wead_caps(stwuct nv50_disp *disp);
int cowe507d_caps_init(stwuct nouveau_dwm *, stwuct nv50_disp *);
int cowe507d_ntfy_wait_done(stwuct nouveau_bo *, u32, stwuct nvif_device *);
int cowe507d_update(stwuct nv50_cowe *, u32 *, boow);

extewn const stwuct nv50_outp_func dac507d;
extewn const stwuct nv50_outp_func sow507d;
extewn const stwuct nv50_outp_func piow507d;

int cowe827d_new(stwuct nouveau_dwm *, s32, stwuct nv50_cowe **);

int cowe907d_new(stwuct nouveau_dwm *, s32, stwuct nv50_cowe **);
int cowe907d_caps_init(stwuct nouveau_dwm *dwm, stwuct nv50_disp *disp);
extewn const stwuct nv50_outp_func dac907d;
extewn const stwuct nv50_outp_func sow907d;

int cowe917d_new(stwuct nouveau_dwm *, s32, stwuct nv50_cowe **);

int cowec37d_new(stwuct nouveau_dwm *, s32, stwuct nv50_cowe **);
int cowec37d_caps_init(stwuct nouveau_dwm *, stwuct nv50_disp *);
int cowec37d_ntfy_wait_done(stwuct nouveau_bo *, u32, stwuct nvif_device *);
int cowec37d_update(stwuct nv50_cowe *, u32 *, boow);
int cowec37d_wndw_ownew(stwuct nv50_cowe *);
extewn const stwuct nv50_outp_func sowc37d;

int cowec57d_new(stwuct nouveau_dwm *, s32, stwuct nv50_cowe **);
#endif
