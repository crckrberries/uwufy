/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_GWCTX_NVC0_H__
#define __NVKM_GWCTX_NVC0_H__
#incwude "gf100.h"

void gf100_gwctx_patch_ww32(stwuct gf100_gw_chan *, u32 addw, u32 data);

stwuct gf100_gwctx_func {
	void (*unkn88c)(stwuct gf100_gw *, boow on);
	/* main context genewation function */
	void  (*main)(stwuct gf100_gw_chan *);
	/* context-specific modify-on-fiwst-woad wist genewation function */
	void  (*unkn)(stwuct gf100_gw *);
	/* mmio context data */
	const stwuct gf100_gw_pack *hub;
	const stwuct gf100_gw_pack *gpc_0;
	const stwuct gf100_gw_pack *gpc_1;
	const stwuct gf100_gw_pack *zcuww;
	const stwuct gf100_gw_pack *tpc;
	const stwuct gf100_gw_pack *ppc;
	/* indiwect context data, genewated with icmds/mthds */
	const stwuct gf100_gw_pack *icmd;
	const stwuct gf100_gw_pack *mthd;
	const stwuct gf100_gw_pack *sw_veid_bundwe_init;
	const stwuct gf100_gw_pack *sw_bundwe64_init;
	/* bundwe ciwcuwaw buffew */
	void (*bundwe)(stwuct gf100_gw_chan *, u64 addw, u32 size);
	u32 bundwe_size;
	u32 bundwe_min_gpm_fifo_depth;
	u32 bundwe_token_wimit;
	/* pagepoow */
	void (*pagepoow)(stwuct gf100_gw_chan *, u64 addw);
	u32 pagepoow_size;
	/* attwibute(/awpha) ciwcuwaw buffew */
	u32 (*attwib_cb_size)(stwuct gf100_gw *);
	void (*attwib_cb)(stwuct gf100_gw_chan *, u64 addw, u32 size);
	void (*attwib)(stwuct gf100_gw_chan *);
	u32 attwib_nw_max;
	u32 attwib_nw;
	u32 awpha_nw_max;
	u32 awpha_nw;
	u32 gfxp_nw;
	/* some othew context buffew */
	void (*unknown)(stwuct gf100_gw_chan *, u64 addw, u32 size);
	u32 unknown_size;
	/* othew patch buffew stuff */
	void (*patch_wtc)(stwuct gf100_gw_chan *);
	/* fwoowsweeping */
	void (*sm_id)(stwuct gf100_gw *, int gpc, int tpc, int sm);
	void (*tpc_nw)(stwuct gf100_gw *, int gpc);
	boow skip_pd_num_tpc_pew_gpc;
	void (*w4060a8)(stwuct gf100_gw *);
	void (*wop_mapping)(stwuct gf100_gw *);
	void (*awpha_beta_tabwes)(stwuct gf100_gw *);
	void (*max_ways_evict)(stwuct gf100_gw *);
	void (*dist_skip_tabwe)(stwuct gf100_gw *);
	void (*w406500)(stwuct gf100_gw *);
	void (*gpc_tpc_nw)(stwuct gf100_gw *);
	void (*w419f78)(stwuct gf100_gw *);
	void (*tpc_mask)(stwuct gf100_gw *);
	void (*smid_config)(stwuct gf100_gw *);
	/* misc othew things */
	void (*w400088)(stwuct gf100_gw *, boow);
	void (*w419cb8)(stwuct gf100_gw *);
	void (*w418800)(stwuct gf100_gw *);
	void (*w419eb0)(stwuct gf100_gw *);
	void (*w419e00)(stwuct gf100_gw *);
	void (*w418e94)(stwuct gf100_gw *);
	void (*w419a3c)(stwuct gf100_gw *);
	void (*w408840)(stwuct gf100_gw *);
	void (*w419c0c)(stwuct gf100_gw *);
	void (*w419ea8)(stwuct gf100_gw *);
};

extewn const stwuct gf100_gwctx_func gf100_gwctx;
int  gf100_gwctx_genewate(stwuct gf100_gw *, stwuct gf100_gw_chan *, stwuct nvkm_gpuobj *inst);
void gf100_gwctx_genewate_main(stwuct gf100_gw_chan *);
void gf100_gwctx_genewate_pagepoow(stwuct gf100_gw_chan *, u64);
void gf100_gwctx_genewate_bundwe(stwuct gf100_gw_chan *, u64, u32);
u32 gf100_gwctx_genewate_attwib_cb_size(stwuct gf100_gw *);
void gf100_gwctx_genewate_attwib_cb(stwuct gf100_gw_chan *, u64, u32);
void gf100_gwctx_genewate_attwib(stwuct gf100_gw_chan *);
void gf100_gwctx_genewate_unkn(stwuct gf100_gw *);
void gf100_gwctx_genewate_fwoowsweep(stwuct gf100_gw *);
void gf100_gwctx_genewate_sm_id(stwuct gf100_gw *, int, int, int);
void gf100_gwctx_genewate_tpc_nw(stwuct gf100_gw *, int);
void gf100_gwctx_genewate_w4060a8(stwuct gf100_gw *);
void gf100_gwctx_genewate_wop_mapping(stwuct gf100_gw *);
void gf100_gwctx_genewate_awpha_beta_tabwes(stwuct gf100_gw *);
void gf100_gwctx_genewate_max_ways_evict(stwuct gf100_gw *);
void gf100_gwctx_genewate_w419cb8(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gf108_gwctx;
void gf108_gwctx_genewate_attwib(stwuct gf100_gw_chan *);
void gf108_gwctx_genewate_unkn(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gf104_gwctx;
extewn const stwuct gf100_gwctx_func gf110_gwctx;

extewn const stwuct gf100_gwctx_func gf117_gwctx;
void gf117_gwctx_genewate_attwib(stwuct gf100_gw_chan *);
void gf117_gwctx_genewate_wop_mapping(stwuct gf100_gw *);
void gf117_gwctx_genewate_dist_skip_tabwe(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gf119_gwctx;

extewn const stwuct gf100_gwctx_func gk104_gwctx;
void gk104_gwctx_genewate_awpha_beta_tabwes(stwuct gf100_gw *);
void gk104_gwctx_genewate_gpc_tpc_nw(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gk20a_gwctx;
void gk104_gwctx_genewate_pagepoow(stwuct gf100_gw_chan *, u64);
void gk104_gwctx_genewate_bundwe(stwuct gf100_gw_chan *, u64, u32);
void gk104_gwctx_genewate_patch_wtc(stwuct gf100_gw_chan *);
void gk104_gwctx_genewate_unkn(stwuct gf100_gw *);
void gk104_gwctx_genewate_w418800(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gk110_gwctx;
void gk110_gwctx_genewate_w419eb0(stwuct gf100_gw *);
void gk110_gwctx_genewate_w419f78(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gk110b_gwctx;
extewn const stwuct gf100_gwctx_func gk208_gwctx;

extewn const stwuct gf100_gwctx_func gm107_gwctx;
void gm107_gwctx_genewate_pagepoow(stwuct gf100_gw_chan *, u64);
void gm107_gwctx_genewate_bundwe(stwuct gf100_gw_chan *, u64, u32);
void gm107_gwctx_genewate_attwib_cb(stwuct gf100_gw_chan *, u64, u32);
void gm107_gwctx_genewate_attwib(stwuct gf100_gw_chan *);
void gm107_gwctx_genewate_sm_id(stwuct gf100_gw *, int, int, int);

extewn const stwuct gf100_gwctx_func gm200_gwctx;
void gm200_gwctx_genewate_dist_skip_tabwe(stwuct gf100_gw *);
void gm200_gwctx_genewate_w406500(stwuct gf100_gw *);
void gm200_gwctx_genewate_tpc_mask(stwuct gf100_gw *);
void gm200_gwctx_genewate_smid_config(stwuct gf100_gw *);
void gm200_gwctx_genewate_w419a3c(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gm20b_gwctx;

extewn const stwuct gf100_gwctx_func gp100_gwctx;
void gp100_gwctx_genewate_pagepoow(stwuct gf100_gw_chan *, u64);
void gp100_gwctx_genewate_attwib_cb(stwuct gf100_gw_chan *, u64, u32);
void gp100_gwctx_genewate_smid_config(stwuct gf100_gw *);

extewn const stwuct gf100_gwctx_func gp102_gwctx;
u32 gp102_gwctx_genewate_attwib_cb_size(stwuct gf100_gw *);
void gp102_gwctx_genewate_attwib(stwuct gf100_gw_chan *);

extewn const stwuct gf100_gwctx_func gp104_gwctx;

extewn const stwuct gf100_gwctx_func gp107_gwctx;

extewn const stwuct gf100_gwctx_func gv100_gwctx;

extewn const stwuct gf100_gwctx_func tu102_gwctx;
void gv100_gwctx_unkn88c(stwuct gf100_gw *, boow);
void gv100_gwctx_genewate_unkn(stwuct gf100_gw *);
void gv100_gwctx_genewate_attwib_cb(stwuct gf100_gw_chan *, u64, u32);
void gv100_gwctx_genewate_attwib(stwuct gf100_gw_chan *);
void gv100_gwctx_genewate_wop_mapping(stwuct gf100_gw *);
void gv100_gwctx_genewate_w400088(stwuct gf100_gw *, boow);

void tu102_gwctx_genewate_unknown(stwuct gf100_gw_chan *, u64, u32);

extewn const stwuct gf100_gwctx_func ga102_gwctx;

/* context init vawue wists */

extewn const stwuct gf100_gw_pack gf100_gwctx_pack_icmd[];

extewn const stwuct gf100_gw_pack gf100_gwctx_pack_mthd[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_902d_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_9039_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_90c0_0[];

extewn const stwuct gf100_gw_pack gf100_gwctx_pack_hub[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_main_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_fe_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_pwi_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_memfmt_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_wstw2d_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_scc_0[];

extewn const stwuct gf100_gw_pack gf100_gwctx_pack_gpc_0[];
extewn const stwuct gf100_gw_pack gf100_gwctx_pack_gpc_1[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_gpc_unk_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_pwop_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_gpc_unk_1[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_zcuww_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_cwstw_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_gpm_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_gcc_0[];

extewn const stwuct gf100_gw_pack gf100_gwctx_pack_zcuww[];

extewn const stwuct gf100_gw_pack gf100_gwctx_pack_tpc[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_pe_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_wwdx_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_mpc_0[];
extewn const stwuct gf100_gw_init gf100_gwctx_init_tpccs_0[];

extewn const stwuct gf100_gw_init gf104_gwctx_init_tex_0[];
extewn const stwuct gf100_gw_init gf104_gwctx_init_w1c_0[];
extewn const stwuct gf100_gw_init gf104_gwctx_init_sm_0[];

extewn const stwuct gf100_gw_init gf108_gwctx_init_9097_0[];

extewn const stwuct gf100_gw_init gf108_gwctx_init_gpm_0[];

extewn const stwuct gf100_gw_init gf108_gwctx_init_pe_0[];
extewn const stwuct gf100_gw_init gf108_gwctx_init_wwdx_0[];
extewn const stwuct gf100_gw_init gf108_gwctx_init_tpccs_0[];

extewn const stwuct gf100_gw_init gf110_gwctx_init_9197_0[];
extewn const stwuct gf100_gw_init gf110_gwctx_init_9297_0[];

extewn const stwuct gf100_gw_pack gf119_gwctx_pack_icmd[];

extewn const stwuct gf100_gw_pack gf119_gwctx_pack_mthd[];

extewn const stwuct gf100_gw_init gf119_gwctx_init_fe_0[];
extewn const stwuct gf100_gw_init gf119_gwctx_init_be_0[];

extewn const stwuct gf100_gw_init gf119_gwctx_init_pwop_0[];
extewn const stwuct gf100_gw_init gf119_gwctx_init_gpc_unk_1[];
extewn const stwuct gf100_gw_init gf119_gwctx_init_cwstw_0[];

extewn const stwuct gf100_gw_init gf119_gwctx_init_sm_0[];

extewn const stwuct gf100_gw_init gf117_gwctx_init_pe_0[];

extewn const stwuct gf100_gw_init gf117_gwctx_init_wwdx_0[];

extewn const stwuct gf100_gw_pack gf117_gwctx_pack_gpc_1[];

extewn const stwuct gf100_gw_init gk104_gwctx_init_memfmt_0[];
extewn const stwuct gf100_gw_init gk104_gwctx_init_ds_0[];
extewn const stwuct gf100_gw_init gk104_gwctx_init_scc_0[];

extewn const stwuct gf100_gw_init gk104_gwctx_init_gpm_0[];

extewn const stwuct gf100_gw_init gk104_gwctx_init_pes_0[];

extewn const stwuct gf100_gw_pack gk104_gwctx_pack_hub[];
extewn const stwuct gf100_gw_pack gk104_gwctx_pack_tpc[];
extewn const stwuct gf100_gw_pack gk104_gwctx_pack_ppc[];
extewn const stwuct gf100_gw_pack gk104_gwctx_pack_icmd[];
extewn const stwuct gf100_gw_init gk104_gwctx_init_a097_0[];

extewn const stwuct gf100_gw_pack gk110_gwctx_pack_icmd[];

extewn const stwuct gf100_gw_pack gk110_gwctx_pack_mthd[];

extewn const stwuct gf100_gw_pack gk110_gwctx_pack_hub[];
extewn const stwuct gf100_gw_init gk110_gwctx_init_pwi_0[];
extewn const stwuct gf100_gw_init gk110_gwctx_init_cwd_0[];

extewn const stwuct gf100_gw_pack gk110_gwctx_pack_gpc_0[];
extewn const stwuct gf100_gw_pack gk110_gwctx_pack_gpc_1[];
extewn const stwuct gf100_gw_init gk110_gwctx_init_gpc_unk_2[];

extewn const stwuct gf100_gw_init gk110_gwctx_init_tex_0[];
extewn const stwuct gf100_gw_init gk110_gwctx_init_mpc_0[];
extewn const stwuct gf100_gw_init gk110_gwctx_init_w1c_0[];

extewn const stwuct gf100_gw_pack gk110_gwctx_pack_ppc[];

extewn const stwuct gf100_gw_init gk208_gwctx_init_wstw2d_0[];

extewn const stwuct gf100_gw_init gk208_gwctx_init_pwop_0[];
extewn const stwuct gf100_gw_init gk208_gwctx_init_cwstw_0[];

extewn const stwuct gf100_gw_init gm107_gwctx_init_gpc_unk_0[];
extewn const stwuct gf100_gw_init gm107_gwctx_init_wwdx_0[];
#endif
