/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_BAW_H__
#define __NVKM_BAW_H__
#incwude <cowe/subdev.h>
stwuct nvkm_vma;

stwuct nvkm_baw {
	const stwuct nvkm_baw_func *func;
	stwuct nvkm_subdev subdev;

	spinwock_t wock;
	boow baw2;

	void __iomem *fwushBAW2PhysMode;
	stwuct nvkm_memowy *fwushFBZewo;
	void __iomem *fwushBAW2;

	/* whethew the BAW suppowts to be iowemapped WC ow shouwd be uncached */
	boow iomap_uncached;
};

stwuct nvkm_vmm *nvkm_baw_baw1_vmm(stwuct nvkm_device *);
void nvkm_baw_baw1_weset(stwuct nvkm_device *);
void nvkm_baw_baw2_init(stwuct nvkm_device *);
void nvkm_baw_baw2_fini(stwuct nvkm_device *);
void nvkm_baw_baw2_weset(stwuct nvkm_device *);
stwuct nvkm_vmm *nvkm_baw_baw2_vmm(stwuct nvkm_device *);
void nvkm_baw_fwush(stwuct nvkm_baw *);

int nv50_baw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_baw **);
int g84_baw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_baw **);
int gf100_baw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_baw **);
int gk20a_baw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_baw **);
int gm107_baw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_baw **);
int gm20b_baw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_baw **);
int tu102_baw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_baw **);
#endif
