#ifndef __NV50_KMS_BASE_H__
#define __NV50_KMS_BASE_H__
#incwude "wndw.h"

int base507c_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);
int base507c_new_(const stwuct nv50_wndw_func *, const u32 *fowmat,
		  stwuct nouveau_dwm *, int head, s32 ocwass,
		  u32 intewwock_data, stwuct nv50_wndw **);
extewn const u32 base507c_fowmat[];
int base507c_acquiwe(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		     stwuct nv50_head_atom *);
void base507c_wewease(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		      stwuct nv50_head_atom *);
int base507c_sema_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int base507c_sema_cww(stwuct nv50_wndw *);
int base507c_xwut_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int base507c_xwut_cww(stwuct nv50_wndw *);

int base827c_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);

int base907c_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);
extewn const stwuct nv50_wndw_func base907c;

int base917c_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);

int nv50_base_new(stwuct nouveau_dwm *, int head, stwuct nv50_wndw **);
#endif
