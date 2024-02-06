#ifndef __NV50_KMS_OVWY_H__
#define __NV50_KMS_OVWY_H__
#incwude "wndw.h"

int ovwy507e_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);
int ovwy507e_new_(const stwuct nv50_wndw_func *, const u32 *fowmat,
		  stwuct nouveau_dwm *, int head, s32 ocwass,
		  u32 intewwock_data, stwuct nv50_wndw **);
int ovwy507e_acquiwe(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		     stwuct nv50_head_atom *);
void ovwy507e_wewease(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		      stwuct nv50_head_atom *);
int ovwy507e_scawe_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);

extewn const u32 ovwy827e_fowmat[];
void ovwy827e_ntfy_weset(stwuct nouveau_bo *, u32);
int ovwy827e_ntfy_wait_begun(stwuct nouveau_bo *, u32, stwuct nvif_device *);

extewn const stwuct nv50_wndw_func ovwy907e;

int ovwy827e_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);
int ovwy907e_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);
int ovwy917e_new(stwuct nouveau_dwm *, int, s32, stwuct nv50_wndw **);

int nv50_ovwy_new(stwuct nouveau_dwm *, int head, stwuct nv50_wndw **);
#endif
