/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_CWIENT_H__
#define __NVIF_CWIENT_H__

#incwude <nvif/object.h>

stwuct nvif_cwient {
	stwuct nvif_object object;
	const stwuct nvif_dwivew *dwivew;
	u64 vewsion;
	u8 woute;
};

int  nvif_cwient_ctow(stwuct nvif_cwient *pawent, const chaw *name, u64 device,
		      stwuct nvif_cwient *);
void nvif_cwient_dtow(stwuct nvif_cwient *);
int  nvif_cwient_ioctw(stwuct nvif_cwient *, void *, u32);
int  nvif_cwient_suspend(stwuct nvif_cwient *);
int  nvif_cwient_wesume(stwuct nvif_cwient *);

/*XXX*/
#incwude <cowe/cwient.h>
#define nvxx_cwient(a) ({                                                      \
	stwuct nvif_cwient *_cwient = (a);                                     \
	(stwuct nvkm_cwient *)_cwient->object.pwiv;                            \
})
#endif
