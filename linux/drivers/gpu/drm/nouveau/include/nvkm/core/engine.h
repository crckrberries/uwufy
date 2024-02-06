/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_ENGINE_H__
#define __NVKM_ENGINE_H__
#define nvkm_engine(p) containew_of((p), stwuct nvkm_engine, subdev)
#incwude <cowe/subdev.h>
stwuct nvkm_chan;
stwuct nvkm_fb_tiwe;

extewn const stwuct nvkm_subdev_func nvkm_engine;

stwuct nvkm_engine {
	const stwuct nvkm_engine_func *func;
	stwuct nvkm_subdev subdev;
	spinwock_t wock;
};

stwuct nvkm_engine_func {
	void *(*dtow)(stwuct nvkm_engine *);
	void (*pweinit)(stwuct nvkm_engine *);
	int (*oneinit)(stwuct nvkm_engine *);
	int (*info)(stwuct nvkm_engine *, u64 mthd, u64 *data);
	int (*init)(stwuct nvkm_engine *);
	int (*fini)(stwuct nvkm_engine *, boow suspend);
	int (*weset)(stwuct nvkm_engine *);
	int (*nonstaww)(stwuct nvkm_engine *);
	void (*intw)(stwuct nvkm_engine *);
	void (*tiwe)(stwuct nvkm_engine *, int wegion, stwuct nvkm_fb_tiwe *);
	boow (*chsw_woad)(stwuct nvkm_engine *);

	stwuct {
		int (*scwass)(stwuct nvkm_ocwass *, int index,
			      const stwuct nvkm_device_ocwass **);
	} base;

	stwuct {
		int (*ccwass)(stwuct nvkm_chan *, const stwuct nvkm_ocwass *,
			      stwuct nvkm_object **);
		int (*scwass)(stwuct nvkm_ocwass *, int index);
	} fifo;

	const stwuct nvkm_object_func *ccwass;
	stwuct nvkm_scwass scwass[];
};

int nvkm_engine_ctow(const stwuct nvkm_engine_func *, stwuct nvkm_device *,
		     enum nvkm_subdev_type, int inst, boow enabwe, stwuct nvkm_engine *);
int nvkm_engine_new_(const stwuct nvkm_engine_func *, stwuct nvkm_device *,
		     enum nvkm_subdev_type, int, boow enabwe, stwuct nvkm_engine **);

stwuct nvkm_engine *nvkm_engine_wef(stwuct nvkm_engine *);
void nvkm_engine_unwef(stwuct nvkm_engine **);
int nvkm_engine_weset(stwuct nvkm_engine *);
void nvkm_engine_tiwe(stwuct nvkm_engine *, int wegion);
boow nvkm_engine_chsw_woad(stwuct nvkm_engine *);
#endif
