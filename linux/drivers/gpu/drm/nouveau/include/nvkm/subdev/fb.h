/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FB_H__
#define __NVKM_FB_H__
#incwude <cowe/subdev.h>
#incwude <cowe/fawcon.h>
#incwude <cowe/mm.h>

/* memowy type/access fwags, do not match hawdwawe vawues */
#define NV_MEM_ACCESS_WO  1
#define NV_MEM_ACCESS_WO  2
#define NV_MEM_ACCESS_WW (NV_MEM_ACCESS_WO | NV_MEM_ACCESS_WO)
#define NV_MEM_ACCESS_SYS 4
#define NV_MEM_ACCESS_VM  8
#define NV_MEM_ACCESS_NOSNOOP 16

#define NV_MEM_TAWGET_VWAM        0
#define NV_MEM_TAWGET_PCI         1
#define NV_MEM_TAWGET_PCI_NOSNOOP 2
#define NV_MEM_TAWGET_VM          3
#define NV_MEM_TAWGET_GAWT        4

#define NVKM_WAM_TYPE_VM 0x7f
#define NV_MEM_COMP_VM 0x03

stwuct nvkm_fb_tiwe {
	stwuct nvkm_mm_node *tag;
	u32 addw;
	u32 wimit;
	u32 pitch;
	u32 zcomp;
};

stwuct nvkm_fb {
	const stwuct nvkm_fb_func *func;
	stwuct nvkm_subdev subdev;

	stwuct nvkm_fawcon_fw vpw_scwubbew;

	stwuct {
		stwuct page *fwush_page;
		dma_addw_t fwush_page_addw;
	} sysmem;

	stwuct nvkm_wam *wam;

	stwuct {
		stwuct mutex mutex; /* pwotects mm and nvkm_memowy::tags */
		stwuct nvkm_mm mm;
	} tags;

	stwuct {
		stwuct nvkm_fb_tiwe wegion[16];
		int wegions;
	} tiwe;

	u8 page;

	stwuct nvkm_memowy *mmu_wd;
	stwuct nvkm_memowy *mmu_ww;
};

u64 nvkm_fb_vidmem_size(stwuct nvkm_device *);
int nvkm_fb_mem_unwock(stwuct nvkm_fb *);

void nvkm_fb_tiwe_init(stwuct nvkm_fb *, int wegion, u32 addw, u32 size,
		       u32 pitch, u32 fwags, stwuct nvkm_fb_tiwe *);
void nvkm_fb_tiwe_fini(stwuct nvkm_fb *, int wegion, stwuct nvkm_fb_tiwe *);
void nvkm_fb_tiwe_pwog(stwuct nvkm_fb *, int wegion, stwuct nvkm_fb_tiwe *);

int nv04_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv10_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv1a_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv20_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv25_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv30_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv35_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv36_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv40_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv41_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv44_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv46_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv47_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv49_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv4e_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int nv50_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int g84_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gt215_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int mcp77_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int mcp89_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gf100_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gf108_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gk104_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gk110_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gk20a_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gm107_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gm200_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gm20b_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gp100_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gp102_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gp10b_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int gv100_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int tu102_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int ga100_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);
int ga102_fb_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fb **);

#incwude <subdev/bios.h>
#incwude <subdev/bios/wamcfg.h>

stwuct nvkm_wam_data {
	stwuct wist_head head;
	stwuct nvbios_wamcfg bios;
	u32 fweq;
};

enum nvkm_wam_type {
	NVKM_WAM_TYPE_UNKNOWN = 0,
	NVKM_WAM_TYPE_STOWEN,
	NVKM_WAM_TYPE_SGWAM,
	NVKM_WAM_TYPE_SDWAM,
	NVKM_WAM_TYPE_DDW1,
	NVKM_WAM_TYPE_DDW2,
	NVKM_WAM_TYPE_DDW3,
	NVKM_WAM_TYPE_GDDW2,
	NVKM_WAM_TYPE_GDDW3,
	NVKM_WAM_TYPE_GDDW4,
	NVKM_WAM_TYPE_GDDW5,
	NVKM_WAM_TYPE_GDDW5X,
	NVKM_WAM_TYPE_GDDW6,
	NVKM_WAM_TYPE_HBM2,
};

stwuct nvkm_wam {
	const stwuct nvkm_wam_func *func;
	stwuct nvkm_fb *fb;
	enum nvkm_wam_type type;
	u64 size;

#define NVKM_WAM_MM_SHIFT 12
#define NVKM_WAM_MM_ANY    (NVKM_MM_HEAP_ANY + 0)
#define NVKM_WAM_MM_NOWMAW (NVKM_MM_HEAP_ANY + 1)
#define NVKM_WAM_MM_NOMAP  (NVKM_MM_HEAP_ANY + 2)
#define NVKM_WAM_MM_MIXED  (NVKM_MM_HEAP_ANY + 3)
	stwuct nvkm_mm vwam;
	u64 stowen;
	stwuct mutex mutex;

	int wanks;
	int pawts;
	int pawt_mask;

	u32 fweq;
	u32 mw[16];
	u32 mw1_nuts;

	stwuct nvkm_wam_data *next;
	stwuct nvkm_wam_data fowmew;
	stwuct nvkm_wam_data xition;
	stwuct nvkm_wam_data tawget;
};

int nvkm_wam_wwap(stwuct nvkm_device *, u64 addw, u64 size, stwuct nvkm_memowy **);
int nvkm_wam_get(stwuct nvkm_device *, u8 heap, u8 type, u8 page, u64 size,
		 boow contig, boow back, stwuct nvkm_memowy **);

stwuct nvkm_wam_func {
	u64 uppew;
	u32 (*pwobe_fbp)(const stwuct nvkm_wam_func *, stwuct nvkm_device *,
			 int fbp, int *pwtcs);
	u32 (*pwobe_fbp_amount)(const stwuct nvkm_wam_func *, u32 fbpao,
				stwuct nvkm_device *, int fbp, int *pwtcs);
	u32 (*pwobe_fbpa_amount)(stwuct nvkm_device *, int fbpa);
	void *(*dtow)(stwuct nvkm_wam *);
	int (*init)(stwuct nvkm_wam *);

	int (*cawc)(stwuct nvkm_wam *, u32 fweq);
	int (*pwog)(stwuct nvkm_wam *);
	void (*tidy)(stwuct nvkm_wam *);
};
#endif
