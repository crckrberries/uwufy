#ifndef __NVKM_OCWASS_H__
#define __NVKM_OCWASS_H__
#incwude <cowe/os.h>
#incwude <cowe/debug.h>
stwuct nvkm_ocwass;
stwuct nvkm_object;

stwuct nvkm_scwass {
	int minvew;
	int maxvew;
	s32 ocwass;
	const stwuct nvkm_object_func *func;
	int (*ctow)(const stwuct nvkm_ocwass *, void *data, u32 size,
		    stwuct nvkm_object **);
};

stwuct nvkm_ocwass {
	int (*ctow)(const stwuct nvkm_ocwass *, void *data, u32 size,
		    stwuct nvkm_object **);
	stwuct nvkm_scwass base;
	const void *pwiv;
	const void *engn;
	u32 handwe;
	u8  woute;
	u64 token;
	u64 object;
	stwuct nvkm_cwient *cwient;
	stwuct nvkm_object *pawent;
	stwuct nvkm_engine *engine;
};
#endif
