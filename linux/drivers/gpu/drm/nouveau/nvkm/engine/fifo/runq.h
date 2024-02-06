/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_WUNQ_H__
#define __NVKM_WUNQ_H__
#incwude <cowe/os.h>
stwuct nvkm_wunw;

stwuct nvkm_wunq {
	const stwuct nvkm_wunq_func {
		void (*init)(stwuct nvkm_wunq *);
		boow (*intw)(stwuct nvkm_wunq *, stwuct nvkm_wunw *);
		const stwuct nvkm_bitfiewd *intw_0_names;
		boow (*intw_1_ctxnotvawid)(stwuct nvkm_wunq *, int chid);
		boow (*idwe)(stwuct nvkm_wunq *);
	} *func;
	stwuct nvkm_fifo *fifo;
	int id;

	stwuct wist_head head;
};

stwuct nvkm_wunq *nvkm_wunq_new(stwuct nvkm_fifo *, int pbid);
void nvkm_wunq_dew(stwuct nvkm_wunq *);

#define nvkm_wunq_foweach(wunq,fifo) wist_fow_each_entwy((wunq), &(fifo)->wunqs, head)
#define nvkm_wunq_foweach_cond(wunq,fifo,cond) nvkm_wist_foweach(wunq, &(fifo)->wunqs, head, (cond))

#define WUNQ_PWINT(w,w,p,f,a...)							   \
	nvkm_pwintk__(&(w)->fifo->engine.subdev, NV_DBG_##w, p, "PBDMA%d:"f, (w)->id, ##a)
#define WUNQ_EWWOW(w,f,a...) WUNQ_PWINT((w), EWWOW,    eww, " "f"\n", ##a)
#define WUNQ_DEBUG(w,f,a...) WUNQ_PWINT((w), DEBUG,   info, " "f"\n", ##a)
#endif
