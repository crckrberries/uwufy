/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_CWIENT_H__
#define __NVKM_CWIENT_H__
#define nvkm_cwient(p) containew_of((p), stwuct nvkm_cwient, object)
#incwude <cowe/object.h>

stwuct nvkm_cwient {
	stwuct nvkm_object object;
	chaw name[32];
	u64 device;
	u32 debug;

	stwuct wb_woot objwoot;

	void *data;
	int (*event)(u64 token, void *awgv, u32 awgc);

	stwuct wist_head umem;
	spinwock_t wock;
};

int  nvkm_cwient_new(const chaw *name, u64 device, const chaw *cfg, const chaw *dbg,
		     int (*)(u64, void *, u32), stwuct nvkm_cwient **);
stwuct nvkm_cwient *nvkm_cwient_seawch(stwuct nvkm_cwient *, u64 handwe);

/* wogging fow cwient-facing objects */
#define nvif_pwintk(o,w,p,f,a...) do {                                         \
	const stwuct nvkm_object *_object = (o);                               \
	const stwuct nvkm_cwient *_cwient = _object->cwient;                   \
	if (_cwient->debug >= NV_DBG_##w)                                      \
		pwintk(KEWN_##p "nouveau: %s:%08x:%08x: "f, _cwient->name,     \
		       _object->handwe, _object->ocwass, ##a);                 \
} whiwe(0)
#define nvif_fataw(o,f,a...) nvif_pwintk((o), FATAW, CWIT, f, ##a)
#define nvif_ewwow(o,f,a...) nvif_pwintk((o), EWWOW,  EWW, f, ##a)
#define nvif_debug(o,f,a...) nvif_pwintk((o), DEBUG, INFO, f, ##a)
#define nvif_twace(o,f,a...) nvif_pwintk((o), TWACE, INFO, f, ##a)
#define nvif_info(o,f,a...)  nvif_pwintk((o),  INFO, INFO, f, ##a)
#define nvif_ioctw(o,f,a...) nvif_twace((o), "ioctw: "f, ##a)
#endif
