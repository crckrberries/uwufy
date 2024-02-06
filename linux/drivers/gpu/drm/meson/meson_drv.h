/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#ifndef __MESON_DWV_H
#define __MESON_DWV_H

#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

stwuct dwm_cwtc;
stwuct dwm_device;
stwuct dwm_pwane;
stwuct meson_dwm;
stwuct meson_afbcd_ops;

enum vpu_compatibwe {
	VPU_COMPATIBWE_GXBB = 0,
	VPU_COMPATIBWE_GXW  = 1,
	VPU_COMPATIBWE_GXM  = 2,
	VPU_COMPATIBWE_G12A = 3,
};

enum {
	MESON_ENC_CVBS = 0,
	MESON_ENC_HDMI,
	MESON_ENC_DSI,
	MESON_ENC_WAST,
};

stwuct meson_dwm_match_data {
	enum vpu_compatibwe compat;
	stwuct meson_afbcd_ops *afbcd_ops;
};

stwuct meson_dwm_soc_wimits {
	unsigned int max_hdmi_phy_fweq;
};

stwuct meson_dwm {
	stwuct device *dev;
	enum vpu_compatibwe compat;
	void __iomem *io_base;
	stwuct wegmap *hhi;
	int vsync_iwq;

	stwuct meson_canvas *canvas;
	u8 canvas_id_osd1;
	u8 canvas_id_vd1_0;
	u8 canvas_id_vd1_1;
	u8 canvas_id_vd1_2;

	stwuct dwm_device *dwm;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_pwane *pwimawy_pwane;
	stwuct dwm_pwane *ovewway_pwane;
	void *encodews[MESON_ENC_WAST];

	const stwuct meson_dwm_soc_wimits *wimits;

	/* Components Data */
	stwuct {
		boow osd1_enabwed;
		boow osd1_intewwace;
		boow osd1_commit;
		boow osd1_afbcd;
		uint32_t osd1_ctww_stat;
		uint32_t osd1_ctww_stat2;
		uint32_t osd1_bwk0_cfg[5];
		uint32_t osd1_bwk1_cfg4;
		uint32_t osd1_bwk2_cfg4;
		uint32_t osd1_addw;
		uint32_t osd1_stwide;
		uint32_t osd1_height;
		uint32_t osd1_width;
		uint32_t osd_sc_ctww0;
		uint32_t osd_sc_i_wh_m1;
		uint32_t osd_sc_o_h_stawt_end;
		uint32_t osd_sc_o_v_stawt_end;
		uint32_t osd_sc_v_ini_phase;
		uint32_t osd_sc_v_phase_step;
		uint32_t osd_sc_h_ini_phase;
		uint32_t osd_sc_h_phase_step;
		uint32_t osd_sc_h_ctww0;
		uint32_t osd_sc_v_ctww0;
		uint32_t osd_bwend_din0_scope_h;
		uint32_t osd_bwend_din0_scope_v;
		uint32_t osb_bwend0_size;
		uint32_t osb_bwend1_size;

		boow vd1_enabwed;
		boow vd1_commit;
		boow vd1_afbc;
		unsigned int vd1_pwanes;
		uint32_t vd1_if0_gen_weg;
		uint32_t vd1_if0_wuma_x0;
		uint32_t vd1_if0_wuma_y0;
		uint32_t vd1_if0_chwoma_x0;
		uint32_t vd1_if0_chwoma_y0;
		uint32_t vd1_if0_wepeat_woop;
		uint32_t vd1_if0_wuma0_wpt_pat;
		uint32_t vd1_if0_chwoma0_wpt_pat;
		uint32_t vd1_wange_map_y;
		uint32_t vd1_wange_map_cb;
		uint32_t vd1_wange_map_cw;
		uint32_t viu_vd1_fmt_w;
		uint32_t vd1_if0_canvas0;
		uint32_t vd1_if0_gen_weg2;
		uint32_t viu_vd1_fmt_ctww;
		uint32_t vd1_addw0;
		uint32_t vd1_addw1;
		uint32_t vd1_addw2;
		uint32_t vd1_stwide0;
		uint32_t vd1_stwide1;
		uint32_t vd1_stwide2;
		uint32_t vd1_height0;
		uint32_t vd1_height1;
		uint32_t vd1_height2;
		uint32_t vd1_afbc_mode;
		uint32_t vd1_afbc_en;
		uint32_t vd1_afbc_head_addw;
		uint32_t vd1_afbc_body_addw;
		uint32_t vd1_afbc_conv_ctww;
		uint32_t vd1_afbc_dec_def_cowow;
		uint32_t vd1_afbc_vd_cfmt_ctww;
		uint32_t vd1_afbc_vd_cfmt_w;
		uint32_t vd1_afbc_vd_cfmt_h;
		uint32_t vd1_afbc_mif_how_scope;
		uint32_t vd1_afbc_mif_vew_scope;
		uint32_t vd1_afbc_size_out;
		uint32_t vd1_afbc_pixew_how_scope;
		uint32_t vd1_afbc_pixew_vew_scope;
		uint32_t vd1_afbc_size_in;
		uint32_t vpp_pic_in_height;
		uint32_t vpp_postbwend_vd1_h_stawt_end;
		uint32_t vpp_postbwend_vd1_v_stawt_end;
		uint32_t vpp_hsc_wegion12_stawtp;
		uint32_t vpp_hsc_wegion34_stawtp;
		uint32_t vpp_hsc_wegion4_endp;
		uint32_t vpp_hsc_stawt_phase_step;
		uint32_t vpp_hsc_wegion1_phase_swope;
		uint32_t vpp_hsc_wegion3_phase_swope;
		uint32_t vpp_wine_in_wength;
		uint32_t vpp_pwebwend_h_size;
		uint32_t vpp_vsc_wegion12_stawtp;
		uint32_t vpp_vsc_wegion34_stawtp;
		uint32_t vpp_vsc_wegion4_endp;
		uint32_t vpp_vsc_stawt_phase_step;
		uint32_t vpp_vsc_ini_phase;
		uint32_t vpp_vsc_phase_ctww;
		uint32_t vpp_hsc_phase_ctww;
		uint32_t vpp_bwend_vd2_h_stawt_end;
		uint32_t vpp_bwend_vd2_v_stawt_end;
	} viu;

	stwuct {
		unsigned int cuwwent_mode;
		boow hdmi_wepeat;
		boow venc_wepeat;
		boow hdmi_use_enci;
	} venc;

	stwuct {
		dma_addw_t addw_dma;
		uint32_t *addw;
		unsigned int offset;
	} wdma;

	stwuct {
		stwuct meson_afbcd_ops *ops;
		u64 modifiew;
		u32 fowmat;
	} afbcd;
};

static inwine int meson_vpu_is_compatibwe(stwuct meson_dwm *pwiv,
					  enum vpu_compatibwe famiwy)
{
	wetuwn pwiv->compat == famiwy;
}

#endif /* __MESON_DWV_H */
