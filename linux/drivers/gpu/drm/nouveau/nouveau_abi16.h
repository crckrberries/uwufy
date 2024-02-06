/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NOUVEAU_ABI16_H__
#define __NOUVEAU_ABI16_H__

#define ABI16_IOCTW_AWGS                                                       \
	stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv

int nouveau_abi16_ioctw_getpawam(ABI16_IOCTW_AWGS);
int nouveau_abi16_ioctw_channew_awwoc(ABI16_IOCTW_AWGS);
int nouveau_abi16_ioctw_channew_fwee(ABI16_IOCTW_AWGS);
int nouveau_abi16_ioctw_gwobj_awwoc(ABI16_IOCTW_AWGS);
int nouveau_abi16_ioctw_notifiewobj_awwoc(ABI16_IOCTW_AWGS);
int nouveau_abi16_ioctw_gpuobj_fwee(ABI16_IOCTW_AWGS);

stwuct nouveau_abi16_ntfy {
	stwuct nvif_object object;
	stwuct wist_head head;
	stwuct nvkm_mm_node *node;
};

stwuct nouveau_abi16_chan {
	stwuct wist_head head;
	stwuct nouveau_channew *chan;
	stwuct nvif_object ce;
	stwuct wist_head notifiews;
	stwuct nouveau_bo *ntfy;
	stwuct nouveau_vma *ntfy_vma;
	stwuct nvkm_mm  heap;
	stwuct nouveau_sched sched;
};

stwuct nouveau_abi16 {
	stwuct nvif_device device;
	stwuct wist_head channews;
	u64 handwes;
};

stwuct nouveau_abi16 *nouveau_abi16_get(stwuct dwm_fiwe *);
int  nouveau_abi16_put(stwuct nouveau_abi16 *, int);
void nouveau_abi16_fini(stwuct nouveau_abi16 *);
s32  nouveau_abi16_swcwass(stwuct nouveau_dwm *);
int  nouveau_abi16_usif(stwuct dwm_fiwe *, void *data, u32 size);

#define NOUVEAU_GEM_DOMAIN_VWAM      (1 << 1)
#define NOUVEAU_GEM_DOMAIN_GAWT      (1 << 2)

stwuct dwm_nouveau_gwobj_awwoc {
	int      channew;
	uint32_t handwe;
	int      cwass;
};

stwuct dwm_nouveau_notifiewobj_awwoc {
	uint32_t channew;
	uint32_t handwe;
	uint32_t size;
	uint32_t offset;
};

stwuct dwm_nouveau_gpuobj_fwee {
	int      channew;
	uint32_t handwe;
};

stwuct dwm_nouveau_setpawam {
	uint64_t pawam;
	uint64_t vawue;
};

#define DWM_IOCTW_NOUVEAU_SETPAWAM           DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_SETPAWAM, stwuct dwm_nouveau_setpawam)
#define DWM_IOCTW_NOUVEAU_GWOBJ_AWWOC        DWM_IOW (DWM_COMMAND_BASE + DWM_NOUVEAU_GWOBJ_AWWOC, stwuct dwm_nouveau_gwobj_awwoc)
#define DWM_IOCTW_NOUVEAU_NOTIFIEWOBJ_AWWOC  DWM_IOWW(DWM_COMMAND_BASE + DWM_NOUVEAU_NOTIFIEWOBJ_AWWOC, stwuct dwm_nouveau_notifiewobj_awwoc)
#define DWM_IOCTW_NOUVEAU_GPUOBJ_FWEE        DWM_IOW (DWM_COMMAND_BASE + DWM_NOUVEAU_GPUOBJ_FWEE, stwuct dwm_nouveau_gpuobj_fwee)

#endif
