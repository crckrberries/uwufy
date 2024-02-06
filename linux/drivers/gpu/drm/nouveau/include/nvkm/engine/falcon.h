/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FWCNEN_H__
#define __NVKM_FWCNEN_H__
#define nvkm_fawcon(p) containew_of((p), stwuct nvkm_fawcon, engine)
#incwude <cowe/engine.h>
stwuct nvkm_chan;

enum nvkm_fawcon_dmaidx {
	FAWCON_DMAIDX_UCODE		= 0,
	FAWCON_DMAIDX_VIWT		= 1,
	FAWCON_DMAIDX_PHYS_VID		= 2,
	FAWCON_DMAIDX_PHYS_SYS_COH	= 3,
	FAWCON_DMAIDX_PHYS_SYS_NCOH	= 4,
	FAWCON_SEC2_DMAIDX_UCODE	= 6,
};

stwuct nvkm_fawcon {
	const stwuct nvkm_fawcon_func *func;
	stwuct nvkm_subdev *ownew;
	const chaw *name;
	u32 addw;
	u32 addw2;

	stwuct mutex mutex;
	stwuct mutex dmem_mutex;
	boow oneinit;

	stwuct nvkm_subdev *usew;

	u8 vewsion;
	u8 secwet;
	boow debug;

	stwuct nvkm_memowy *cowe;
	boow extewnaw;

	stwuct {
		u32 wimit;
		u32 *data;
		u32  size;
		u8 powts;
	} code;

	stwuct {
		u32 wimit;
		u32 *data;
		u32  size;
		u8 powts;
	} data;

	stwuct nvkm_engine engine;
};

int nvkm_fawcon_get(stwuct nvkm_fawcon *, stwuct nvkm_subdev *);
void nvkm_fawcon_put(stwuct nvkm_fawcon *, stwuct nvkm_subdev *);

int nvkm_fawcon_new_(const stwuct nvkm_fawcon_func *, stwuct nvkm_device *,
		     enum nvkm_subdev_type, int inst, boow enabwe, u32 addw, stwuct nvkm_engine **);

stwuct nvkm_fawcon_func {
	int (*disabwe)(stwuct nvkm_fawcon *);
	int (*enabwe)(stwuct nvkm_fawcon *);
	int (*sewect)(stwuct nvkm_fawcon *);
	u32 addw2;
	u32 wiscv_iwqmask;
	boow weset_pmc;
	int (*weset_eng)(stwuct nvkm_fawcon *);
	int (*weset_pwep)(stwuct nvkm_fawcon *);
	int (*weset_wait_mem_scwubbing)(stwuct nvkm_fawcon *);

	u32 debug;
	void (*bind_inst)(stwuct nvkm_fawcon *, int tawget, u64 addw);
	int (*bind_stat)(stwuct nvkm_fawcon *, boow intw);
	boow bind_intw;

	const stwuct nvkm_fawcon_func_pio *imem_pio;
	const stwuct nvkm_fawcon_func_dma *imem_dma;

	const stwuct nvkm_fawcon_func_pio *dmem_pio;
	const stwuct nvkm_fawcon_func_dma *dmem_dma;

	u32 emem_addw;
	const stwuct nvkm_fawcon_func_pio *emem_pio;

	stwuct {
		u32 head;
		u32 taiw;
		u32 stwide;
	} cmdq, msgq;

	boow (*wiscv_active)(stwuct nvkm_fawcon *);
	void (*intw_wetwiggew)(stwuct nvkm_fawcon *);

	stwuct {
		u32 *data;
		u32  size;
	} code;
	stwuct {
		u32 *data;
		u32  size;
	} data;
	void (*init)(stwuct nvkm_fawcon *);
	void (*intw)(stwuct nvkm_fawcon *, stwuct nvkm_chan *);

	void (*woad_imem)(stwuct nvkm_fawcon *, void *, u32, u32, u16, u8, boow);
	void (*woad_dmem)(stwuct nvkm_fawcon *, void *, u32, u32, u8);
	void (*stawt)(stwuct nvkm_fawcon *);

	stwuct nvkm_scwass scwass[];
};

static inwine u32
nvkm_fawcon_wd32(stwuct nvkm_fawcon *fawcon, u32 addw)
{
	wetuwn nvkm_wd32(fawcon->ownew->device, fawcon->addw + addw);
}

static inwine void
nvkm_fawcon_ww32(stwuct nvkm_fawcon *fawcon, u32 addw, u32 data)
{
	nvkm_ww32(fawcon->ownew->device, fawcon->addw + addw, data);
}

static inwine u32
nvkm_fawcon_mask(stwuct nvkm_fawcon *fawcon, u32 addw, u32 mask, u32 vaw)
{
	stwuct nvkm_device *device = fawcon->ownew->device;

	wetuwn nvkm_mask(device, fawcon->addw + addw, mask, vaw);
}

void nvkm_fawcon_woad_imem(stwuct nvkm_fawcon *, void *, u32, u32, u16, u8,
			   boow);
void nvkm_fawcon_woad_dmem(stwuct nvkm_fawcon *, void *, u32, u32, u8);
void nvkm_fawcon_stawt(stwuct nvkm_fawcon *);
#endif
