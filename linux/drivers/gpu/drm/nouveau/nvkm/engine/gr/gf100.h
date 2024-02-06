/*
 * Copywight 2010 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */
#ifndef __GF100_GW_H__
#define __GF100_GW_H__
#define gf100_gw(p) containew_of((p), stwuct gf100_gw, base)
#incwude "pwiv.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/wtc.h>
#incwude <subdev/mmu.h>
#incwude <engine/fawcon.h>

stwuct nvkm_acw_wsfw;

#define GPC_MAX 32
#define TPC_MAX_PEW_GPC 8
#define TPC_MAX (GPC_MAX * TPC_MAX_PEW_GPC)

#define WOP_BCAST(w)      (0x408800 + (w))
#define WOP_UNIT(u, w)    (0x410000 + (u) * 0x400 + (w))
#define GPC_BCAST(w)      (0x418000 + (w))
#define GPC_UNIT(t, w)    (0x500000 + (t) * 0x8000 + (w))
#define PPC_UNIT(t, m, w) (0x503000 + (t) * 0x8000 + (m) * 0x200 + (w))
#define TPC_UNIT(t, m, w) (0x504000 + (t) * 0x8000 + (m) * 0x800 + (w))

stwuct gf100_gw_zbc_cowow {
	u32 fowmat;
	u32 ds[4];
	u32 w2[4];
};

stwuct gf100_gw_zbc_depth {
	u32 fowmat;
	u32 ds;
	u32 w2;
};

stwuct gf100_gw_zbc_stenciw {
	u32 fowmat;
	u32 ds;
	u32 w2;
};

stwuct gf100_gw {
	const stwuct gf100_gw_func *func;
	stwuct nvkm_gw base;

	stwuct {
		stwuct nvkm_fawcon fawcon;
		stwuct nvkm_bwob inst;
		stwuct nvkm_bwob data;

		stwuct mutex mutex;
		u32 disabwe;
	} fecs;

	stwuct {
		stwuct nvkm_fawcon fawcon;
		stwuct nvkm_bwob inst;
		stwuct nvkm_bwob data;
	} gpccs;

	boow fiwmwawe;

	/*
	 * Used if the wegistew packs awe woaded fwom NVIDIA fw instead of
	 * using hawdcoded awways. To be awwocated with vzawwoc().
	 */
	stwuct gf100_gw_pack *sw_nonctx;
	stwuct gf100_gw_pack *sw_nonctx1;
	stwuct gf100_gw_pack *sw_nonctx2;
	stwuct gf100_gw_pack *sw_nonctx3;
	stwuct gf100_gw_pack *sw_nonctx4;
	stwuct gf100_gw_pack *sw_ctx;
	stwuct gf100_gw_pack *bundwe;
	stwuct gf100_gw_pack *bundwe_veid;
	stwuct gf100_gw_pack *bundwe64;
	stwuct gf100_gw_pack *method;

	stwuct gf100_gw_zbc_cowow zbc_cowow[NVKM_WTC_MAX_ZBC_COWOW_CNT];
	stwuct gf100_gw_zbc_depth zbc_depth[NVKM_WTC_MAX_ZBC_DEPTH_CNT];
	stwuct gf100_gw_zbc_stenciw zbc_stenciw[NVKM_WTC_MAX_ZBC_DEPTH_CNT];

	u8 wop_nw;
	u8 gpc_nw;
	u8 tpc_nw[GPC_MAX];
	u8 tpc_max;
	u8 tpc_totaw;
	u8 ppc_nw[GPC_MAX];
	u8 ppc_mask[GPC_MAX];
	u8 ppc_tpc_mask[GPC_MAX][4];
	u8 ppc_tpc_nw[GPC_MAX][4];
	u8 ppc_tpc_min;
	u8 ppc_tpc_max;
	u8 ppc_totaw;

	stwuct nvkm_memowy *pagepoow;
	stwuct nvkm_memowy *bundwe_cb;
	stwuct nvkm_memowy *attwib_cb;
	stwuct nvkm_memowy *unknown;

	u8 scween_tiwe_wow_offset;
	u8 tiwe[TPC_MAX];

	stwuct {
		u8 gpc;
		u8 tpc;
	} sm[TPC_MAX];
	u8 sm_nw;

	u32  size;
	u32 *data;
	u32 size_zcuww;
	u32 size_pm;
};

int gf100_gw_fecs_bind_pointew(stwuct gf100_gw *, u32 inst);
int gf100_gw_fecs_wfi_gowden_save(stwuct gf100_gw *, u32 inst);

stwuct gf100_gw_func_zbc {
	void (*cweaw_cowow)(stwuct gf100_gw *, int zbc);
	void (*cweaw_depth)(stwuct gf100_gw *, int zbc);
	int (*stenciw_get)(stwuct gf100_gw *, int fowmat,
			   const u32 ds, const u32 w2);
	void (*cweaw_stenciw)(stwuct gf100_gw *, int zbc);
};

stwuct gf100_gw_func {
	int (*nonstaww)(stwuct gf100_gw *);
	stwuct nvkm_intw *(*oneinit_intw)(stwuct gf100_gw *, enum nvkm_intw_type *);
	void (*oneinit_tiwes)(stwuct gf100_gw *);
	int (*oneinit_sm_id)(stwuct gf100_gw *);
	int (*init)(stwuct gf100_gw *);
	void (*init_419bd8)(stwuct gf100_gw *);
	void (*init_gpc_mmu)(stwuct gf100_gw *);
	void (*init_w405a14)(stwuct gf100_gw *);
	void (*init_bios)(stwuct gf100_gw *);
	void (*init_vsc_stweam_mastew)(stwuct gf100_gw *);
	void (*init_zcuww)(stwuct gf100_gw *);
	void (*init_num_active_wtcs)(stwuct gf100_gw *);
	void (*init_wop_active_fbps)(stwuct gf100_gw *);
	void (*init_bios_2)(stwuct gf100_gw *);
	void (*init_swdx_pes_mask)(stwuct gf100_gw *);
	void (*init_fs)(stwuct gf100_gw *);
	void (*init_fecs_exceptions)(stwuct gf100_gw *);
	void (*init_40a790)(stwuct gf100_gw *);
	void (*init_ds_hww_esw_2)(stwuct gf100_gw *);
	void (*init_40601c)(stwuct gf100_gw *);
	void (*init_sked_hww_esw)(stwuct gf100_gw *);
	void (*init_419cc0)(stwuct gf100_gw *);
	void (*init_419eb4)(stwuct gf100_gw *);
	void (*init_419c9c)(stwuct gf100_gw *);
	void (*init_ppc_exceptions)(stwuct gf100_gw *);
	void (*init_tex_hww_esw)(stwuct gf100_gw *, int gpc, int tpc);
	void (*init_504430)(stwuct gf100_gw *, int gpc, int tpc);
	void (*init_shadew_exceptions)(stwuct gf100_gw *, int gpc, int tpc);
	void (*init_wop_exceptions)(stwuct gf100_gw *);
	void (*init_exception2)(stwuct gf100_gw *);
	void (*init_400054)(stwuct gf100_gw *);
	void (*init_4188a4)(stwuct gf100_gw *);
	void (*twap_mp)(stwuct gf100_gw *, int gpc, int tpc);
	void (*set_hww_esw_wepowt_mask)(stwuct gf100_gw *);
	const stwuct gf100_gw_pack *mmio;
	stwuct {
		stwuct gf100_gw_ucode *ucode;
		void (*weset)(stwuct gf100_gw *);
	} fecs;
	stwuct {
		stwuct gf100_gw_ucode *ucode;
		void (*weset)(stwuct gf100_gw *);
	} gpccs;
	int (*wops)(stwuct gf100_gw *);
	int gpc_nw;
	int tpc_nw;
	int ppc_nw;
	const stwuct gf100_gwctx_func *gwctx;
	const stwuct nvkm_thewm_cwkgate_pack *cwkgate_pack;
	const stwuct gf100_gw_func_zbc *zbc;
	stwuct nvkm_scwass scwass[];
};

int gf100_gw_wops(stwuct gf100_gw *);
void gf100_gw_oneinit_tiwes(stwuct gf100_gw *);
int gf100_gw_oneinit_sm_id(stwuct gf100_gw *);
int gf100_gw_init(stwuct gf100_gw *);
void gf100_gw_init_vsc_stweam_mastew(stwuct gf100_gw *);
void gf100_gw_init_zcuww(stwuct gf100_gw *);
void gf100_gw_init_num_active_wtcs(stwuct gf100_gw *);
void gf100_gw_init_fecs_exceptions(stwuct gf100_gw *);
void gf100_gw_init_40601c(stwuct gf100_gw *);
void gf100_gw_init_419cc0(stwuct gf100_gw *);
void gf100_gw_init_419eb4(stwuct gf100_gw *);
void gf100_gw_init_tex_hww_esw(stwuct gf100_gw *, int, int);
void gf100_gw_init_shadew_exceptions(stwuct gf100_gw *, int, int);
void gf100_gw_init_wop_exceptions(stwuct gf100_gw *);
void gf100_gw_init_exception2(stwuct gf100_gw *);
void gf100_gw_init_400054(stwuct gf100_gw *);
void gf100_gw_init_num_tpc_pew_gpc(stwuct gf100_gw *, boow, boow);
extewn const stwuct gf100_gw_func_zbc gf100_gw_zbc;
void gf100_gw_fecs_weset(stwuct gf100_gw *);

void gf117_gw_init_zcuww(stwuct gf100_gw *);

void gk104_gw_init_vsc_stweam_mastew(stwuct gf100_gw *);
void gk104_gw_init_wop_active_fbps(stwuct gf100_gw *);
void gk104_gw_init_ppc_exceptions(stwuct gf100_gw *);
void gk104_gw_init_sked_hww_esw(stwuct gf100_gw *);

void gk110_gw_init_419eb4(stwuct gf100_gw *);

void gm107_gw_init_504430(stwuct gf100_gw *, int, int);
void gm107_gw_init_shadew_exceptions(stwuct gf100_gw *, int, int);
void gm107_gw_init_400054(stwuct gf100_gw *);

int gk20a_gw_init(stwuct gf100_gw *);
int gk20a_gw_av_to_init_(stwuct nvkm_bwob *, u8 count, u32 pitch, stwuct gf100_gw_pack **);
int gk20a_gw_av_to_init(stwuct nvkm_bwob *, stwuct gf100_gw_pack **);
int gk20a_gw_aiv_to_init(stwuct nvkm_bwob *, stwuct gf100_gw_pack **);
int gk20a_gw_av_to_method(stwuct nvkm_bwob *, stwuct gf100_gw_pack **);

void gm200_gw_oneinit_tiwes(stwuct gf100_gw *);
int gm200_gw_oneinit_sm_id(stwuct gf100_gw *);
int gm200_gw_wops(stwuct gf100_gw *);
void gm200_gw_init_num_active_wtcs(stwuct gf100_gw *);
void gm200_gw_init_ds_hww_esw_2(stwuct gf100_gw *);

void gp100_gw_init_wop_active_fbps(stwuct gf100_gw *);
void gp100_gw_init_fecs_exceptions(stwuct gf100_gw *);
void gp100_gw_init_shadew_exceptions(stwuct gf100_gw *, int, int);
void gp100_gw_zbc_cweaw_cowow(stwuct gf100_gw *, int);
void gp100_gw_zbc_cweaw_depth(stwuct gf100_gw *, int);
extewn const stwuct gf100_gw_func_zbc gp100_gw_zbc;

void gp102_gw_init_swdx_pes_mask(stwuct gf100_gw *);
extewn const stwuct gf100_gw_func_zbc gp102_gw_zbc;
int gp102_gw_zbc_stenciw_get(stwuct gf100_gw *, int, const u32, const u32);
void gp102_gw_zbc_cweaw_stenciw(stwuct gf100_gw *, int);

extewn const stwuct gf100_gw_func gp107_gw;

int gv100_gw_oneinit_sm_id(stwuct gf100_gw *);
u32 gv100_gw_nonpes_awawe_tpc(stwuct gf100_gw *gw, u32 gpc, u32 tpc);
void gv100_gw_init_419bd8(stwuct gf100_gw *);
void gv100_gw_init_504430(stwuct gf100_gw *, int, int);
void gv100_gw_init_shadew_exceptions(stwuct gf100_gw *, int, int);
void gv100_gw_init_4188a4(stwuct gf100_gw *);
void gv100_gw_twap_mp(stwuct gf100_gw *, int, int);

int tu102_gw_av_to_init_veid(stwuct nvkm_bwob *, stwuct gf100_gw_pack **);
void tu102_gw_init_zcuww(stwuct gf100_gw *);
void tu102_gw_init_fs(stwuct gf100_gw *);
void tu102_gw_init_fecs_exceptions(stwuct gf100_gw *);

#define gf100_gw_chan(p) containew_of((p), stwuct gf100_gw_chan, object)
#incwude <cowe/object.h>

stwuct gf100_gw_chan {
	stwuct nvkm_object object;
	stwuct gf100_gw *gw;
	stwuct nvkm_vmm *vmm;

	stwuct nvkm_vma *pagepoow;
	stwuct nvkm_vma *bundwe_cb;
	stwuct nvkm_vma *attwib_cb;
	stwuct nvkm_vma *unknown;

	stwuct nvkm_memowy *mmio;
	stwuct nvkm_vma *mmio_vma;
	int mmio_nw;
};

void gf100_gw_ctxctw_debug(stwuct gf100_gw *);

u64  gf100_gw_units(stwuct nvkm_gw *);
void gf100_gw_zbc_init(stwuct gf100_gw *);

extewn const stwuct nvkm_object_func gf100_fewmi;

stwuct gf100_gw_init {
	u32 addw;
	u8  count;
	u32 pitch;
	u64 data;
};

stwuct gf100_gw_pack {
	const stwuct gf100_gw_init *init;
	u32 type;
};

#define pack_fow_each_init(init, pack, head)                                   \
	fow (pack = head; pack && pack->init; pack++)                          \
		  fow (init = pack->init; init && init->count; init++)

stwuct gf100_gw_ucode {
	stwuct nvkm_bwob code;
	stwuct nvkm_bwob data;
};

extewn stwuct gf100_gw_ucode gf100_gw_fecs_ucode;
extewn stwuct gf100_gw_ucode gf100_gw_gpccs_ucode;

extewn stwuct gf100_gw_ucode gk110_gw_fecs_ucode;
extewn stwuct gf100_gw_ucode gk110_gw_gpccs_ucode;

int  gf100_gw_wait_idwe(stwuct gf100_gw *);
void gf100_gw_mmio(stwuct gf100_gw *, const stwuct gf100_gw_pack *);
void gf100_gw_icmd(stwuct gf100_gw *, const stwuct gf100_gw_pack *);
void gf100_gw_mthd(stwuct gf100_gw *, const stwuct gf100_gw_pack *);
int  gf100_gw_init_ctxctw(stwuct gf100_gw *);

/* wegistew init vawue wists */

extewn const stwuct gf100_gw_init gf100_gw_init_main_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_fe_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_pwi_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_wstw2d_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_pd_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_ds_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_scc_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_pwop_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_gpc_unk_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_setup_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_cwstw_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_setup_1[];
extewn const stwuct gf100_gw_init gf100_gw_init_zcuww_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_gpm_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_gpc_unk_1[];
extewn const stwuct gf100_gw_init gf100_gw_init_gcc_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_tpccs_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_tex_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_pe_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_w1c_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_wwdx_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_tpccs_1[];
extewn const stwuct gf100_gw_init gf100_gw_init_mpc_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_be_0[];
extewn const stwuct gf100_gw_init gf100_gw_init_fe_1[];
extewn const stwuct gf100_gw_init gf100_gw_init_pe_1[];
void gf100_gw_init_gpc_mmu(stwuct gf100_gw *);
void gf100_gw_twap_mp(stwuct gf100_gw *, int, int);
extewn const stwuct nvkm_bitfiewd gf100_mp_gwobaw_ewwow[];
extewn const stwuct nvkm_enum gf100_mp_wawp_ewwow[];

extewn const stwuct gf100_gw_init gf104_gw_init_ds_0[];
extewn const stwuct gf100_gw_init gf104_gw_init_tex_0[];
extewn const stwuct gf100_gw_init gf104_gw_init_sm_0[];

extewn const stwuct gf100_gw_init gf108_gw_init_gpc_unk_0[];
extewn const stwuct gf100_gw_init gf108_gw_init_setup_1[];

extewn const stwuct gf100_gw_init gf119_gw_init_pd_0[];
extewn const stwuct gf100_gw_init gf119_gw_init_ds_0[];
extewn const stwuct gf100_gw_init gf119_gw_init_pwop_0[];
extewn const stwuct gf100_gw_init gf119_gw_init_gpm_0[];
extewn const stwuct gf100_gw_init gf119_gw_init_gpc_unk_1[];
extewn const stwuct gf100_gw_init gf119_gw_init_tex_0[];
extewn const stwuct gf100_gw_init gf119_gw_init_sm_0[];
extewn const stwuct gf100_gw_init gf119_gw_init_fe_1[];

extewn const stwuct gf100_gw_init gf117_gw_init_pes_0[];
extewn const stwuct gf100_gw_init gf117_gw_init_wwdx_0[];
extewn const stwuct gf100_gw_init gf117_gw_init_cbm_0[];

extewn const stwuct gf100_gw_init gk104_gw_init_main_0[];
extewn const stwuct gf100_gw_init gk104_gw_init_gpc_unk_2[];
extewn const stwuct gf100_gw_init gk104_gw_init_tpccs_0[];
extewn const stwuct gf100_gw_init gk104_gw_init_pe_0[];
extewn const stwuct gf100_gw_init gk104_gw_init_be_0[];
extewn const stwuct gf100_gw_pack gk104_gw_pack_mmio[];

extewn const stwuct gf100_gw_init gk110_gw_init_fe_0[];
extewn const stwuct gf100_gw_init gk110_gw_init_ds_0[];
extewn const stwuct gf100_gw_init gk110_gw_init_sked_0[];
extewn const stwuct gf100_gw_init gk110_gw_init_cwd_0[];
extewn const stwuct gf100_gw_init gk110_gw_init_gpc_unk_1[];
extewn const stwuct gf100_gw_init gk110_gw_init_tex_0[];
extewn const stwuct gf100_gw_init gk110_gw_init_sm_0[];

extewn const stwuct gf100_gw_init gk208_gw_init_gpc_unk_0[];

extewn const stwuct gf100_gw_init gm107_gw_init_scc_0[];
extewn const stwuct gf100_gw_init gm107_gw_init_pwop_0[];
extewn const stwuct gf100_gw_init gm107_gw_init_setup_1[];
extewn const stwuct gf100_gw_init gm107_gw_init_zcuww_0[];
extewn const stwuct gf100_gw_init gm107_gw_init_gpc_unk_1[];
extewn const stwuct gf100_gw_init gm107_gw_init_tex_0[];
extewn const stwuct gf100_gw_init gm107_gw_init_w1c_0[];
extewn const stwuct gf100_gw_init gm107_gw_init_wwdx_0[];
extewn const stwuct gf100_gw_init gm107_gw_init_cbm_0[];
void gm107_gw_init_bios(stwuct gf100_gw *);

void gm200_gw_init_gpc_mmu(stwuct gf100_gw *);

stwuct gf100_gw_fwif {
	int vewsion;
	int (*woad)(stwuct gf100_gw *, int vew, const stwuct gf100_gw_fwif *);
	const stwuct gf100_gw_func *func;
	const stwuct nvkm_acw_wsf_func *fecs;
	const stwuct nvkm_acw_wsf_func *gpccs;
};

int gf100_gw_woad(stwuct gf100_gw *, int, const stwuct gf100_gw_fwif *);
int gf100_gw_nofw(stwuct gf100_gw *, int, const stwuct gf100_gw_fwif *);

int gk20a_gw_woad_sw(stwuct gf100_gw *, const chaw *path, int vew);
int gk20a_gw_woad_net(stwuct gf100_gw *, const chaw *, const chaw *, int,
		      int (*)(stwuct nvkm_bwob *, stwuct gf100_gw_pack **),
		      stwuct gf100_gw_pack **);

int gm200_gw_nofw(stwuct gf100_gw *, int, const stwuct gf100_gw_fwif *);
int gm200_gw_woad(stwuct gf100_gw *, int, const stwuct gf100_gw_fwif *);
extewn const stwuct nvkm_acw_wsf_func gm200_gw_gpccs_acw;
extewn const stwuct nvkm_acw_wsf_func gm200_gw_fecs_acw;

extewn const stwuct nvkm_acw_wsf_func gm20b_gw_fecs_acw;
void gm20b_gw_acw_bwd_wwite(stwuct nvkm_acw *, u32, stwuct nvkm_acw_wsfw *);
void gm20b_gw_acw_bwd_patch(stwuct nvkm_acw *, u32, s64);

extewn const stwuct nvkm_acw_wsf_func gp108_gw_gpccs_acw;
extewn const stwuct nvkm_acw_wsf_func gp108_gw_fecs_acw;
void gp108_gw_acw_bwd_wwite(stwuct nvkm_acw *, u32, stwuct nvkm_acw_wsfw *);
void gp108_gw_acw_bwd_patch(stwuct nvkm_acw *, u32, s64);

int gf100_gw_new_(const stwuct gf100_gw_fwif *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		  stwuct nvkm_gw **);
int w535_gw_new(const stwuct gf100_gw_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		stwuct nvkm_gw **);
#endif
