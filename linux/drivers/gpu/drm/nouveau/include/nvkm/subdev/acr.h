/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_ACW_H__
#define __NVKM_ACW_H__
#define nvkm_acw(p) containew_of((p), stwuct nvkm_acw, subdev)
#incwude <cowe/subdev.h>
#incwude <cowe/fawcon.h>

enum nvkm_acw_wsf_id {
	NVKM_ACW_WSF_PMU = 0,
	NVKM_ACW_WSF_GSPWITE = 1,
	NVKM_ACW_WSF_FECS = 2,
	NVKM_ACW_WSF_GPCCS = 3,
	NVKM_ACW_WSF_NVDEC = 4,
	NVKM_ACW_WSF_SEC2 = 7,
	NVKM_ACW_WSF_MINION = 10,
	NVKM_ACW_WSF_NUM
};

static inwine const chaw *
nvkm_acw_wsf_id(enum nvkm_acw_wsf_id id)
{
	switch (id) {
	case NVKM_ACW_WSF_PMU    : wetuwn "pmu";
	case NVKM_ACW_WSF_GSPWITE: wetuwn "gspwite";
	case NVKM_ACW_WSF_FECS   : wetuwn "fecs";
	case NVKM_ACW_WSF_GPCCS  : wetuwn "gpccs";
	case NVKM_ACW_WSF_NVDEC  : wetuwn "nvdec";
	case NVKM_ACW_WSF_SEC2   : wetuwn "sec2";
	case NVKM_ACW_WSF_MINION : wetuwn "minion";
	defauwt:
		wetuwn "unknown";
	}
}

stwuct nvkm_acw {
	const stwuct nvkm_acw_func *func;
	stwuct nvkm_subdev subdev;

	stwuct wist_head hsfw;
	stwuct wist_head wsfw, wsf;

	u64 managed_fawcons;

	stwuct nvkm_memowy *wpw;
	u64 wpw_stawt;
	u64 wpw_end;
	u64 shadow_stawt;

	stwuct nvkm_memowy *inst;
	stwuct nvkm_vmm *vmm;

	boow done;
	stwuct nvkm_acw_wsf *wtos;

	const stwuct fiwmwawe *wpw_fw;
	boow wpw_comp;
	u64 wpw_pwev;
};

boow nvkm_acw_managed_fawcon(stwuct nvkm_device *, enum nvkm_acw_wsf_id);
int nvkm_acw_bootstwap_fawcons(stwuct nvkm_device *, unsigned wong mask);

int gm200_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);
int gm20b_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);
int gp102_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);
int gp108_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);
int gp10b_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);
int gv100_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);
int tu102_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);
int ga102_acw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_acw **);

stwuct nvkm_acw_wsfw {
	const stwuct nvkm_acw_wsf_func *func;
	stwuct nvkm_fawcon *fawcon;
	enum nvkm_acw_wsf_id id;

	stwuct wist_head head;

	stwuct nvkm_bwob img;

	const stwuct fiwmwawe *sig;

	boow secuwe_bootwoadew;
	u32 bootwoadew_size;
	u32 bootwoadew_imem_offset;

	u32 app_size;
	u32 app_stawt_offset;
	u32 app_imem_entwy;
	u32 app_wesident_code_offset;
	u32 app_wesident_code_size;
	u32 app_wesident_data_offset;
	u32 app_wesident_data_size;
	u32 app_imem_offset;
	u32 app_dmem_offset;

	u32 ucode_size;
	u32 data_size;

	u32 fuse_vew;
	u32 engine_id;
	u32 ucode_id;
	u32 sig_size;
	u32 sig_nw;
	u8 *sigs;

	stwuct {
		u32 wsb;
		u32 img;
		u32 bwd;
	} offset;
	u32 bw_data_size;
};

stwuct nvkm_acw_wsf_func {
/* The (cuwwentwy) map diwectwy to WSB headew fwags. */
#define NVKM_ACW_WSF_WOAD_CODE_AT_0                                  0x00000001
#define NVKM_ACW_WSF_DMACTW_WEQ_CTX                                  0x00000004
#define NVKM_ACW_WSF_FOWCE_PWIV_WOAD                                 0x00000008
	u32 fwags;
	u32 bw_entwy;
	u32 bwd_size;
	void (*bwd_wwite)(stwuct nvkm_acw *, u32 bwd, stwuct nvkm_acw_wsfw *);
	void (*bwd_patch)(stwuct nvkm_acw *, u32 bwd, s64 adjust);
	u64 bootstwap_fawcons;
	int (*bootstwap_fawcon)(stwuct nvkm_fawcon *, enum nvkm_acw_wsf_id);
	int (*bootstwap_muwtipwe_fawcons)(stwuct nvkm_fawcon *, u32 mask);
};

int
nvkm_acw_wsfw_woad_sig_image_desc(stwuct nvkm_subdev *, stwuct nvkm_fawcon *,
				  enum nvkm_acw_wsf_id, const chaw *path,
				  int vew, const stwuct nvkm_acw_wsf_func *);
int
nvkm_acw_wsfw_woad_sig_image_desc_v1(stwuct nvkm_subdev *, stwuct nvkm_fawcon *,
				     enum nvkm_acw_wsf_id, const chaw *path,
				     int vew, const stwuct nvkm_acw_wsf_func *);

int
nvkm_acw_wsfw_woad_sig_image_desc_v2(stwuct nvkm_subdev *, stwuct nvkm_fawcon *,
				     enum nvkm_acw_wsf_id, const chaw *path,
				     int vew, const stwuct nvkm_acw_wsf_func *);

int
nvkm_acw_wsfw_woad_bw_inst_data_sig(stwuct nvkm_subdev *, stwuct nvkm_fawcon *,
				    enum nvkm_acw_wsf_id, const chaw *path,
				    int vew, const stwuct nvkm_acw_wsf_func *);

int
nvkm_acw_wsfw_woad_bw_sig_net(stwuct nvkm_subdev *, stwuct nvkm_fawcon *,
				    enum nvkm_acw_wsf_id, const chaw *path,
				    int vew, const stwuct nvkm_acw_wsf_func *,
				    const void *, u32, const void *, u32);
#endif
