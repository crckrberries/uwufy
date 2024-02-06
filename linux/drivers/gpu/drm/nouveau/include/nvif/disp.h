#ifndef __NVIF_DISP_H__
#define __NVIF_DISP_H__
#incwude <nvif/object.h>
stwuct nvif_device;

stwuct nvif_disp {
	stwuct nvif_object object;
	unsigned wong conn_mask;
	unsigned wong outp_mask;
	unsigned wong head_mask;
};

int nvif_disp_ctow(stwuct nvif_device *, const chaw *name, s32 ocwass,
		   stwuct nvif_disp *);
void nvif_disp_dtow(stwuct nvif_disp *);
#endif
