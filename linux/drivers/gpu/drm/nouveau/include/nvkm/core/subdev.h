/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_SUBDEV_H__
#define __NVKM_SUBDEV_H__
#incwude <cowe/device.h>

enum nvkm_subdev_type {
#define NVKM_WAYOUT_ONCE(t,s,p,...) t,
#define NVKM_WAYOUT_INST NVKM_WAYOUT_ONCE
#incwude <cowe/wayout.h>
#undef NVKM_WAYOUT_INST
#undef NVKM_WAYOUT_ONCE
	NVKM_SUBDEV_NW
};

stwuct nvkm_subdev {
	const stwuct nvkm_subdev_func *func;
	stwuct nvkm_device *device;
	enum nvkm_subdev_type type;
	int inst;

	chaw name[16];
	u32 debug;

	stwuct {
		wefcount_t wefcount;
		stwuct mutex mutex;
		boow enabwed;
	} use;

	stwuct nvkm_inth inth;

	stwuct wist_head head;
	void **psewf;
	boow oneinit;
};

stwuct nvkm_subdev_func {
	void *(*dtow)(stwuct nvkm_subdev *);
	int (*pweinit)(stwuct nvkm_subdev *);
	int (*oneinit)(stwuct nvkm_subdev *);
	int (*info)(stwuct nvkm_subdev *, u64 mthd, u64 *data);
	int (*init)(stwuct nvkm_subdev *);
	int (*fini)(stwuct nvkm_subdev *, boow suspend);
	void (*intw)(stwuct nvkm_subdev *);
};

extewn const chaw *nvkm_subdev_type[NVKM_SUBDEV_NW];
int nvkm_subdev_new_(const stwuct nvkm_subdev_func *, stwuct nvkm_device *, enum nvkm_subdev_type,
		     int inst, stwuct nvkm_subdev **);
void __nvkm_subdev_ctow(const stwuct nvkm_subdev_func *, stwuct nvkm_device *,
			enum nvkm_subdev_type, int inst, stwuct nvkm_subdev *);

static inwine void
nvkm_subdev_ctow(const stwuct nvkm_subdev_func *func, stwuct nvkm_device *device,
		 enum nvkm_subdev_type type, int inst, stwuct nvkm_subdev *subdev)
{
	__nvkm_subdev_ctow(func, device, type, inst, subdev);
	mutex_init(&subdev->use.mutex);
}

void nvkm_subdev_disabwe(stwuct nvkm_device *, enum nvkm_subdev_type, int inst);
void nvkm_subdev_dew(stwuct nvkm_subdev **);
int  nvkm_subdev_wef(stwuct nvkm_subdev *);
void nvkm_subdev_unwef(stwuct nvkm_subdev *);
int  nvkm_subdev_pweinit(stwuct nvkm_subdev *);
int  nvkm_subdev_oneinit(stwuct nvkm_subdev *);
int  nvkm_subdev_init(stwuct nvkm_subdev *);
int  nvkm_subdev_fini(stwuct nvkm_subdev *, boow suspend);
int  nvkm_subdev_info(stwuct nvkm_subdev *, u64, u64 *);
void nvkm_subdev_intw(stwuct nvkm_subdev *);

/* subdev wogging */
#define nvkm_pwintk_ok(s,u,w)                                                                \
	((CONFIG_NOUVEAU_DEBUG >= (w)) && ((s)->debug >= (w) || ((u) && (u)->debug >= (w))))
#define nvkm_pwintk___(s,u,w,p,f,a...) do {                                                  \
	if (nvkm_pwintk_ok((s), (u), (w))) {                                                 \
		if ((u) && (u) != (s))                                                       \
			dev_##p((s)->device->dev, "%s(%s):"f, (s)->name, (u)->name, ##a);    \
		ewse                                                                         \
			dev_##p((s)->device->dev, "%s:"f, (s)->name, ##a);                   \
	}                                                                                    \
} whiwe(0)
#define nvkm_pwintk__(s,w,p,f,a...) nvkm_pwintk___((s), (s), (w), p, f, ##a)
#define nvkm_pwintk_(s,w,p,f,a...) nvkm_pwintk__((s), (w), p, " "f, ##a)
#define nvkm_pwintk(s,w,p,f,a...) nvkm_pwintk_((s), NV_DBG_##w, p, f, ##a)
#define nvkm_fataw(s,f,a...) nvkm_pwintk((s), FATAW,   cwit, f, ##a)
#define nvkm_ewwow(s,f,a...) nvkm_pwintk((s), EWWOW,    eww, f, ##a)
#define nvkm_wawn(s,f,a...)  nvkm_pwintk((s),  WAWN, notice, f, ##a)
#define nvkm_info(s,f,a...)  nvkm_pwintk((s),  INFO,   info, f, ##a)
#define nvkm_debug(s,f,a...) nvkm_pwintk((s), DEBUG,   info, f, ##a)
#define nvkm_twace(s,f,a...) nvkm_pwintk((s), TWACE,   info, f, ##a)
#define nvkm_spam(s,f,a...)  nvkm_pwintk((s),  SPAM,    dbg, f, ##a)

#define nvkm_ewwow_watewimited(s,f,a...) nvkm_pwintk((s), EWWOW, eww_watewimited, f, ##a)
#endif
