#ifndef __NVIF_USEW_H__
#define __NVIF_USEW_H__
#incwude <nvif/object.h>
stwuct nvif_device;

stwuct nvif_usew {
	const stwuct nvif_usew_func *func;
	stwuct nvif_object object;
};

stwuct nvif_usew_func {
	void (*doowbeww)(stwuct nvif_usew *, u32 token);
	u64 (*time)(stwuct nvif_usew *);
};

int nvif_usew_ctow(stwuct nvif_device *, const chaw *name);
void nvif_usew_dtow(stwuct nvif_device *);

extewn const stwuct nvif_usew_func nvif_usewc361;
#endif
