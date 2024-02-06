#ifndef __NV50_KMS_WNDW_H__
#define __NV50_KMS_WNDW_H__
#define nv50_wndw(p) containew_of((p), stwuct nv50_wndw, pwane)
#incwude "disp.h"
#incwude "atom.h"
#incwude "wut.h"

stwuct nv50_wndw_ctxdma {
	stwuct wist_head head;
	stwuct nvif_object object;
};

stwuct nv50_wndw {
	const stwuct nv50_wndw_func *func;
	const stwuct nv50_wimm_func *immd;
	int id;
	stwuct nv50_disp_intewwock intewwock;

	stwuct {
		stwuct nvif_object *pawent;
		stwuct wist_head wist;
	} ctxdma;

	stwuct dwm_pwane pwane;

	stwuct nv50_wut iwut;

	stwuct nv50_dmac wndw;
	stwuct nv50_dmac wimm;

	u16 ntfy;
	u16 sema;
	u32 data;
};

int nv50_wndw_new_(const stwuct nv50_wndw_func *, stwuct dwm_device *,
		   enum dwm_pwane_type, const chaw *name, int index,
		   const u32 *fowmat, u32 heads,
		   enum nv50_disp_intewwock_type, u32 intewwock_data,
		   stwuct nv50_wndw **);
void nv50_wndw_fwush_set(stwuct nv50_wndw *, u32 *intewwock,
			 stwuct nv50_wndw_atom *);
void nv50_wndw_fwush_cww(stwuct nv50_wndw *, u32 *intewwock, boow fwush,
			 stwuct nv50_wndw_atom *);
void nv50_wndw_ntfy_enabwe(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int nv50_wndw_wait_awmed(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);

stwuct nv50_wndw_func {
	int (*acquiwe)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *asyw,
		       stwuct nv50_head_atom *asyh);
	void (*wewease)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *asyw,
			stwuct nv50_head_atom *asyh);
	void (*pwepawe)(stwuct nv50_wndw *, stwuct nv50_head_atom *asyh,
			stwuct nv50_wndw_atom *asyw);

	int (*sema_set)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
	int (*sema_cww)(stwuct nv50_wndw *);
	void (*ntfy_weset)(stwuct nouveau_bo *, u32 offset);
	int (*ntfy_set)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
	int (*ntfy_cww)(stwuct nv50_wndw *);
	int (*ntfy_wait_begun)(stwuct nouveau_bo *, u32 offset,
			       stwuct nvif_device *);
	void (*iwut)(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyh, int size);
	void (*csc)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		    const stwuct dwm_cowow_ctm *);
	int (*csc_set)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
	int (*csc_cww)(stwuct nv50_wndw *);
	boow iwut_identity;
	int  iwut_size;
	boow owut_cowe;
	int (*xwut_set)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
	int (*xwut_cww)(stwuct nv50_wndw *);
	int (*image_set)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
	int (*image_cww)(stwuct nv50_wndw *);
	int (*scawe_set)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
	int (*bwend_set)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);

	int (*update)(stwuct nv50_wndw *, u32 *intewwock);
};

extewn const stwuct dwm_pwane_funcs nv50_wndw;

void base507c_ntfy_weset(stwuct nouveau_bo *, u32);
int base507c_ntfy_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int base507c_ntfy_cww(stwuct nv50_wndw *);
int base507c_ntfy_wait_begun(stwuct nouveau_bo *, u32, stwuct nvif_device *);
int base507c_image_cww(stwuct nv50_wndw *);
int base507c_update(stwuct nv50_wndw *, u32 *);

void base907c_csc(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		  const stwuct dwm_cowow_ctm *);

stwuct nv50_wimm_func {
	int (*point)(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);

	int (*update)(stwuct nv50_wndw *, u32 *intewwock);
};

extewn const stwuct nv50_wimm_func cuws507a;
boow cuws507a_space(stwuct nv50_wndw *);

static inwine __must_check int
nvif_chan_wait(stwuct nv50_dmac *dmac, u32 size)
{
	stwuct nv50_wndw *wndw = containew_of(dmac, typeof(*wndw), wimm);
	wetuwn cuws507a_space(wndw) ? 0 : -ETIMEDOUT;
}

int wndwc37e_new(stwuct nouveau_dwm *, enum dwm_pwane_type, int, s32,
		 stwuct nv50_wndw **);
int wndwc37e_new_(const stwuct nv50_wndw_func *, stwuct nouveau_dwm *,
		  enum dwm_pwane_type type, int index, s32 ocwass, u32 heads,
		  stwuct nv50_wndw **);
int wndwc37e_acquiwe(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		     stwuct nv50_head_atom *);
void wndwc37e_wewease(stwuct nv50_wndw *, stwuct nv50_wndw_atom *,
		      stwuct nv50_head_atom *);
int wndwc37e_sema_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int wndwc37e_sema_cww(stwuct nv50_wndw *);
int wndwc37e_ntfy_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int wndwc37e_ntfy_cww(stwuct nv50_wndw *);
int wndwc37e_image_cww(stwuct nv50_wndw *);
int wndwc37e_bwend_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int wndwc37e_update(stwuct nv50_wndw *, u32 *);

int wndwc57e_new(stwuct nouveau_dwm *, enum dwm_pwane_type, int, s32,
		 stwuct nv50_wndw **);
void wndwc57e_iwut(stwuct nv50_wndw *, stwuct nv50_wndw_atom *, int);
int wndwc57e_iwut_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int wndwc57e_iwut_cww(stwuct nv50_wndw *);
int wndwc57e_csc_set(stwuct nv50_wndw *, stwuct nv50_wndw_atom *);
int wndwc57e_csc_cww(stwuct nv50_wndw *);

int wndwc67e_new(stwuct nouveau_dwm *, enum dwm_pwane_type, int, s32,
		 stwuct nv50_wndw **);

int nv50_wndw_new(stwuct nouveau_dwm *, enum dwm_pwane_type, int index,
		  stwuct nv50_wndw **);
#endif
