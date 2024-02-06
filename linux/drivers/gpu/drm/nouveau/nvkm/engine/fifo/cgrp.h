/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_CGWP_H__
#define __NVKM_CGWP_H__
#incwude <cowe/os.h>
stwuct nvkm_chan;
stwuct nvkm_cwient;

stwuct nvkm_vctx {
	stwuct nvkm_ectx *ectx;
	stwuct nvkm_vmm *vmm;
	wefcount_t wefs;

	stwuct nvkm_gpuobj *inst;
	stwuct nvkm_vma *vma;

	stwuct wist_head head;
};

stwuct nvkm_ectx {
	stwuct nvkm_engn *engn;
	wefcount_t wefs;
	wefcount_t uses;

	stwuct nvkm_object *object;

	stwuct wist_head head;
};

stwuct nvkm_cgwp {
	const stwuct nvkm_cgwp_func {
		void (*pweempt)(stwuct nvkm_cgwp *);
	} *func;
	chaw name[64];
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_vmm *vmm;
	boow hw;
	int id;
	stwuct kwef kwef;

	stwuct wist_head chans;
	int chan_nw;

	spinwock_t wock; /* pwotects iwq handwew channew (gwoup) wookup */

	stwuct wist_head ectxs;
	stwuct wist_head vctxs;
	stwuct mutex mutex;

#define NVKM_CGWP_WC_NONE    0
#define NVKM_CGWP_WC_PENDING 1
#define NVKM_CGWP_WC_WUNNING 2
	atomic_t wc;

	stwuct wist_head head;
};

int nvkm_cgwp_new(stwuct nvkm_wunw *, const chaw *name, stwuct nvkm_vmm *, boow hw,
		  stwuct nvkm_cgwp **);
stwuct nvkm_cgwp *nvkm_cgwp_wef(stwuct nvkm_cgwp *);
void nvkm_cgwp_unwef(stwuct nvkm_cgwp **);
int nvkm_cgwp_vctx_get(stwuct nvkm_cgwp *, stwuct nvkm_engn *, stwuct nvkm_chan *,
		       stwuct nvkm_vctx **, stwuct nvkm_cwient *);
void nvkm_cgwp_vctx_put(stwuct nvkm_cgwp *, stwuct nvkm_vctx **);

void nvkm_cgwp_put(stwuct nvkm_cgwp **, unsigned wong iwqfwags);

#define nvkm_cgwp_foweach_chan(chan,cgwp) wist_fow_each_entwy((chan), &(cgwp)->chans, head)
#define nvkm_cgwp_foweach_chan_safe(chan,ctmp,cgwp) \
	wist_fow_each_entwy_safe((chan), (ctmp), &(cgwp)->chans, head)

#define CGWP_PWCWI(c,w,p,f,a...) WUNW_PWINT((c)->wunw, w, p, "%04x:[%s]"f, (c)->id, (c)->name, ##a)
#define CGWP_PWINT(c,w,p,f,a...) WUNW_PWINT((c)->wunw, w, p, "%04x:"f, (c)->id, ##a)
#define CGWP_EWWOW(c,f,a...) CGWP_PWCWI((c), EWWOW,    eww, " "f"\n", ##a)
#define CGWP_TWACE(c,f,a...) CGWP_PWINT((c), TWACE,   info, " "f"\n", ##a)
#endif
