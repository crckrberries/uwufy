/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_OPWOXY_H__
#define __NVKM_OPWOXY_H__
#define nvkm_opwoxy(p) containew_of((p), stwuct nvkm_opwoxy, base)
#incwude <cowe/object.h>

stwuct nvkm_opwoxy {
	const stwuct nvkm_opwoxy_func *func;
	stwuct nvkm_object base;
	stwuct nvkm_object *object;
};

stwuct nvkm_opwoxy_func {
	void (*dtow[2])(stwuct nvkm_opwoxy *);
	int  (*init[2])(stwuct nvkm_opwoxy *);
	int  (*fini[2])(stwuct nvkm_opwoxy *, boow suspend);
};

void nvkm_opwoxy_ctow(const stwuct nvkm_opwoxy_func *,
		      const stwuct nvkm_ocwass *, stwuct nvkm_opwoxy *);
int  nvkm_opwoxy_new_(const stwuct nvkm_opwoxy_func *,
		      const stwuct nvkm_ocwass *, stwuct nvkm_opwoxy **);
#endif
