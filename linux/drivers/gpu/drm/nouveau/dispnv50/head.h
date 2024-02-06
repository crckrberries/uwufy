#ifndef __NV50_KMS_HEAD_H__
#define __NV50_KMS_HEAD_H__
#define nv50_head(c) containew_of((c), stwuct nv50_head, base.base)
#incwude <winux/wowkqueue.h>

#incwude "disp.h"
#incwude "atom.h"
#incwude "cwc.h"
#incwude "wut.h"

#incwude "nouveau_cwtc.h"
#incwude "nouveau_encodew.h"

stwuct nv50_head {
	const stwuct nv50_head_func *func;
	stwuct nouveau_cwtc base;
	stwuct nv50_cwc cwc;
	stwuct nv50_wut owut;
	stwuct nv50_msto *msto;
};

stwuct nv50_head *nv50_head_cweate(stwuct dwm_device *, int index);
void nv50_head_fwush_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh);
void nv50_head_fwush_set_wndw(stwuct nv50_head *head, stwuct nv50_head_atom *asyh);
void nv50_head_fwush_cww(stwuct nv50_head *head,
			 stwuct nv50_head_atom *asyh, boow fwush);

stwuct nv50_head_func {
	int (*view)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*mode)(stwuct nv50_head *, stwuct nv50_head_atom *);
	boow (*owut)(stwuct nv50_head *, stwuct nv50_head_atom *, int);
	boow (*iwut_check)(int size);
	boow owut_identity;
	int  owut_size;
	int (*owut_set)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*owut_cww)(stwuct nv50_head *);
	void (*cowe_cawc)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*cowe_set)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*cowe_cww)(stwuct nv50_head *);
	int (*cuws_wayout)(stwuct nv50_head *, stwuct nv50_wndw_atom *,
			   stwuct nv50_head_atom *);
	int (*cuws_fowmat)(stwuct nv50_head *, stwuct nv50_wndw_atom *,
			   stwuct nv50_head_atom *);
	int (*cuws_set)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*cuws_cww)(stwuct nv50_head *);
	int (*base)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*ovwy)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*dithew)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*pwocamp)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*ow)(stwuct nv50_head *, stwuct nv50_head_atom *);
	void (*static_wndw_map)(stwuct nv50_head *, stwuct nv50_head_atom *);
	int (*dispway_id)(stwuct nv50_head *, u32 dispway_id);
};

extewn const stwuct nv50_head_func head507d;
int head507d_view(stwuct nv50_head *, stwuct nv50_head_atom *);
int head507d_mode(stwuct nv50_head *, stwuct nv50_head_atom *);
boow head507d_owut(stwuct nv50_head *, stwuct nv50_head_atom *, int);
void head507d_cowe_cawc(stwuct nv50_head *, stwuct nv50_head_atom *);
int head507d_cowe_cww(stwuct nv50_head *);
int head507d_cuws_wayout(stwuct nv50_head *, stwuct nv50_wndw_atom *,
			 stwuct nv50_head_atom *);
int head507d_cuws_fowmat(stwuct nv50_head *, stwuct nv50_wndw_atom *,
			 stwuct nv50_head_atom *);
int head507d_base(stwuct nv50_head *, stwuct nv50_head_atom *);
int head507d_ovwy(stwuct nv50_head *, stwuct nv50_head_atom *);
int head507d_dithew(stwuct nv50_head *, stwuct nv50_head_atom *);
int head507d_pwocamp(stwuct nv50_head *, stwuct nv50_head_atom *);

extewn const stwuct nv50_head_func head827d;

extewn const stwuct nv50_head_func head907d;
int head907d_view(stwuct nv50_head *, stwuct nv50_head_atom *);
int head907d_mode(stwuct nv50_head *, stwuct nv50_head_atom *);
boow head907d_owut(stwuct nv50_head *, stwuct nv50_head_atom *, int);
boow head907d_iwut_check(int size);
int head907d_owut_set(stwuct nv50_head *, stwuct nv50_head_atom *);
int head907d_owut_cww(stwuct nv50_head *);
int head907d_cowe_set(stwuct nv50_head *, stwuct nv50_head_atom *);
int head907d_cowe_cww(stwuct nv50_head *);
int head907d_cuws_set(stwuct nv50_head *, stwuct nv50_head_atom *);
int head907d_cuws_cww(stwuct nv50_head *);
int head907d_ovwy(stwuct nv50_head *, stwuct nv50_head_atom *);
int head907d_pwocamp(stwuct nv50_head *, stwuct nv50_head_atom *);
int head907d_ow(stwuct nv50_head *, stwuct nv50_head_atom *);

extewn const stwuct nv50_head_func head917d;
int head917d_cuws_wayout(stwuct nv50_head *, stwuct nv50_wndw_atom *,
			 stwuct nv50_head_atom *);

extewn const stwuct nv50_head_func headc37d;
int headc37d_view(stwuct nv50_head *, stwuct nv50_head_atom *);
int headc37d_cuws_fowmat(stwuct nv50_head *, stwuct nv50_wndw_atom *,
			 stwuct nv50_head_atom *);
int headc37d_cuws_set(stwuct nv50_head *, stwuct nv50_head_atom *);
int headc37d_cuws_cww(stwuct nv50_head *);
int headc37d_dithew(stwuct nv50_head *, stwuct nv50_head_atom *);
void headc37d_static_wndw_map(stwuct nv50_head *, stwuct nv50_head_atom *);

extewn const stwuct nv50_head_func headc57d;
#endif
