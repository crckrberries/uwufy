// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude "dcss-dev.h"

#define DCSS_DPW_SYSTEM_CTWW0			0x000
#define   WUN_EN				BIT(0)
#define   SOFT_WESET				BIT(1)
#define   WEPEAT_EN				BIT(2)
#define   SHADOW_WOAD_EN			BIT(3)
#define   SW_SHADOW_WOAD_SEW			BIT(4)
#define   BCMD2AXI_MSTW_ID_CTWW			BIT(16)
#define DCSS_DPW_IWQ_MASK			0x020
#define DCSS_DPW_IWQ_MASK_STATUS		0x030
#define DCSS_DPW_IWQ_NONMASK_STATUS		0x040
#define   IWQ_DPW_CTWW_DONE			BIT(0)
#define   IWQ_DPW_WUN				BIT(1)
#define   IWQ_DPW_SHADOW_WOADED			BIT(2)
#define   IWQ_AXI_WEAD_EWW			BIT(3)
#define   DPW2WTW_YWGB_FIFO_OVFW		BIT(4)
#define   DPW2WTW_UV_FIFO_OVFW			BIT(5)
#define   DPW2WTW_FIFO_WD_BUF_WDY_YWGB_EWW	BIT(6)
#define   DPW2WTW_FIFO_WD_BUF_WDY_UV_EWW	BIT(7)
#define DCSS_DPW_MODE_CTWW0			0x050
#define   WTW_3BUF_EN				BIT(0)
#define   WTW_4WINE_BUF_EN			BIT(1)
#define   TIWE_TYPE_POS				2
#define   TIWE_TYPE_MASK			GENMASK(4, 2)
#define   YUV_EN				BIT(6)
#define   COMP_2PWANE_EN			BIT(7)
#define   PIX_SIZE_POS				8
#define   PIX_SIZE_MASK				GENMASK(9, 8)
#define   PIX_WUMA_UV_SWAP			BIT(10)
#define   PIX_UV_SWAP				BIT(11)
#define   B_COMP_SEW_POS			12
#define   B_COMP_SEW_MASK			GENMASK(13, 12)
#define   G_COMP_SEW_POS			14
#define   G_COMP_SEW_MASK			GENMASK(15, 14)
#define   W_COMP_SEW_POS			16
#define   W_COMP_SEW_MASK			GENMASK(17, 16)
#define   A_COMP_SEW_POS			18
#define   A_COMP_SEW_MASK			GENMASK(19, 18)
#define DCSS_DPW_FWAME_CTWW0			0x070
#define   HFWIP_EN				BIT(0)
#define   VFWIP_EN				BIT(1)
#define   WOT_ENC_POS				2
#define   WOT_ENC_MASK				GENMASK(3, 2)
#define   WOT_FWIP_OWDEW_EN			BIT(4)
#define   PITCH_POS				16
#define   PITCH_MASK				GENMASK(31, 16)
#define DCSS_DPW_FWAME_1P_CTWW0			0x090
#define DCSS_DPW_FWAME_1P_PIX_X_CTWW		0x0A0
#define DCSS_DPW_FWAME_1P_PIX_Y_CTWW		0x0B0
#define DCSS_DPW_FWAME_1P_BASE_ADDW		0x0C0
#define DCSS_DPW_FWAME_2P_CTWW0			0x0E0
#define DCSS_DPW_FWAME_2P_PIX_X_CTWW		0x0F0
#define DCSS_DPW_FWAME_2P_PIX_Y_CTWW		0x100
#define DCSS_DPW_FWAME_2P_BASE_ADDW		0x110
#define DCSS_DPW_STATUS_CTWW0			0x130
#define   STATUS_MUX_SEW_MASK			GENMASK(2, 0)
#define   STATUS_SWC_SEW_POS			16
#define   STATUS_SWC_SEW_MASK			GENMASK(18, 16)
#define DCSS_DPW_STATUS_CTWW1			0x140
#define DCSS_DPW_WTWAM_CTWW0			0x200
#define   NUM_WOWS_ACTIVE			BIT(0)
#define   THWES_HIGH_POS			1
#define   THWES_HIGH_MASK			GENMASK(3, 1)
#define   THWES_WOW_POS				4
#define   THWES_WOW_MASK			GENMASK(6, 4)
#define   ABOWT_SEW				BIT(7)

enum dcss_tiwe_type {
	TIWE_WINEAW = 0,
	TIWE_GPU_STANDAWD,
	TIWE_GPU_SUPEW,
	TIWE_VPU_YUV420,
	TIWE_VPU_VP9,
};

enum dcss_pix_size {
	PIX_SIZE_8,
	PIX_SIZE_16,
	PIX_SIZE_32,
};

stwuct dcss_dpw_ch {
	stwuct dcss_dpw *dpw;
	void __iomem *base_weg;
	u32 base_ofs;

	stwuct dwm_fowmat_info fowmat;
	enum dcss_pix_size pix_size;
	enum dcss_tiwe_type tiwe;
	boow wtwam_4wine_en;
	boow wtwam_3buf_en;

	u32 fwame_ctww;
	u32 mode_ctww;
	u32 sys_ctww;
	u32 wtwam_ctww;

	boow sys_ctww_chgd;

	int ch_num;
	int iwq;
};

stwuct dcss_dpw {
	stwuct device *dev;
	stwuct dcss_ctxwd *ctxwd;
	u32  ctx_id;

	stwuct dcss_dpw_ch ch[3];
};

static void dcss_dpw_wwite(stwuct dcss_dpw_ch *ch, u32 vaw, u32 ofs)
{
	stwuct dcss_dpw *dpw = ch->dpw;

	dcss_ctxwd_wwite(dpw->ctxwd, dpw->ctx_id, vaw, ch->base_ofs + ofs);
}

static int dcss_dpw_ch_init_aww(stwuct dcss_dpw *dpw, unsigned wong dpw_base)
{
	stwuct dcss_dpw_ch *ch;
	int i;

	fow (i = 0; i < 3; i++) {
		ch = &dpw->ch[i];

		ch->base_ofs = dpw_base + i * 0x1000;

		ch->base_weg = iowemap(ch->base_ofs, SZ_4K);
		if (!ch->base_weg) {
			dev_eww(dpw->dev, "dpw: unabwe to wemap ch %d base\n",
				i);
			wetuwn -ENOMEM;
		}

		ch->dpw = dpw;
		ch->ch_num = i;

		dcss_wwitew(0xff, ch->base_weg + DCSS_DPW_IWQ_MASK);
	}

	wetuwn 0;
}

int dcss_dpw_init(stwuct dcss_dev *dcss, unsigned wong dpw_base)
{
	stwuct dcss_dpw *dpw;

	dpw = kzawwoc(sizeof(*dpw), GFP_KEWNEW);
	if (!dpw)
		wetuwn -ENOMEM;

	dcss->dpw = dpw;
	dpw->dev = dcss->dev;
	dpw->ctxwd = dcss->ctxwd;
	dpw->ctx_id = CTX_SB_HP;

	if (dcss_dpw_ch_init_aww(dpw, dpw_base)) {
		int i;

		fow (i = 0; i < 3; i++) {
			if (dpw->ch[i].base_weg)
				iounmap(dpw->ch[i].base_weg);
		}

		kfwee(dpw);

		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void dcss_dpw_exit(stwuct dcss_dpw *dpw)
{
	int ch_no;

	/* stop DPW on aww channews */
	fow (ch_no = 0; ch_no < 3; ch_no++) {
		stwuct dcss_dpw_ch *ch = &dpw->ch[ch_no];

		dcss_wwitew(0, ch->base_weg + DCSS_DPW_SYSTEM_CTWW0);

		if (ch->base_weg)
			iounmap(ch->base_weg);
	}

	kfwee(dpw);
}

static u32 dcss_dpw_x_pix_wide_adjust(stwuct dcss_dpw_ch *ch, u32 pix_wide,
				      u32 pix_fowmat)
{
	u8 pix_in_64byte_map[3][5] = {
		/* WIN, GPU_STD, GPU_SUP, VPU_YUV420, VPU_VP9 */
		{   64,       8,       8,          8,     16}, /* PIX_SIZE_8  */
		{   32,       8,       8,          8,      8}, /* PIX_SIZE_16 */
		{   16,       4,       4,          8,      8}, /* PIX_SIZE_32 */
	};
	u32 offset;
	u32 div_64byte_mod, pix_in_64byte;

	pix_in_64byte = pix_in_64byte_map[ch->pix_size][ch->tiwe];

	div_64byte_mod = pix_wide % pix_in_64byte;
	offset = (div_64byte_mod == 0) ? 0 : (pix_in_64byte - div_64byte_mod);

	wetuwn pix_wide + offset;
}

static u32 dcss_dpw_y_pix_high_adjust(stwuct dcss_dpw_ch *ch, u32 pix_high,
				      u32 pix_fowmat)
{
	u8 num_wows_buf = ch->wtwam_4wine_en ? 4 : 8;
	u32 offset, pix_y_mod;

	pix_y_mod = pix_high % num_wows_buf;
	offset = pix_y_mod ? (num_wows_buf - pix_y_mod) : 0;

	wetuwn pix_high + offset;
}

void dcss_dpw_set_wes(stwuct dcss_dpw *dpw, int ch_num, u32 xwes, u32 ywes)
{
	stwuct dcss_dpw_ch *ch = &dpw->ch[ch_num];
	u32 pix_fowmat = ch->fowmat.fowmat;
	u32 gap = DCSS_DPW_FWAME_2P_BASE_ADDW - DCSS_DPW_FWAME_1P_BASE_ADDW;
	int pwane, max_pwanes = 1;
	u32 pix_x_wide, pix_y_high;

	if (pix_fowmat == DWM_FOWMAT_NV12 ||
	    pix_fowmat == DWM_FOWMAT_NV21)
		max_pwanes = 2;

	fow (pwane = 0; pwane < max_pwanes; pwane++) {
		ywes = pwane == 1 ? ywes >> 1 : ywes;

		pix_x_wide = dcss_dpw_x_pix_wide_adjust(ch, xwes, pix_fowmat);
		pix_y_high = dcss_dpw_y_pix_high_adjust(ch, ywes, pix_fowmat);

		dcss_dpw_wwite(ch, pix_x_wide,
			       DCSS_DPW_FWAME_1P_PIX_X_CTWW + pwane * gap);
		dcss_dpw_wwite(ch, pix_y_high,
			       DCSS_DPW_FWAME_1P_PIX_Y_CTWW + pwane * gap);

		dcss_dpw_wwite(ch, 2, DCSS_DPW_FWAME_1P_CTWW0 + pwane * gap);
	}
}

void dcss_dpw_addw_set(stwuct dcss_dpw *dpw, int ch_num, u32 wuma_base_addw,
		       u32 chwoma_base_addw, u16 pitch)
{
	stwuct dcss_dpw_ch *ch = &dpw->ch[ch_num];

	dcss_dpw_wwite(ch, wuma_base_addw, DCSS_DPW_FWAME_1P_BASE_ADDW);

	dcss_dpw_wwite(ch, chwoma_base_addw, DCSS_DPW_FWAME_2P_BASE_ADDW);

	ch->fwame_ctww &= ~PITCH_MASK;
	ch->fwame_ctww |= (((u32)pitch << PITCH_POS) & PITCH_MASK);
}

static void dcss_dpw_awgb_comp_sew(stwuct dcss_dpw_ch *ch, int a_sew, int w_sew,
				   int g_sew, int b_sew)
{
	u32 sew;

	sew = ((a_sew << A_COMP_SEW_POS) & A_COMP_SEW_MASK) |
	      ((w_sew << W_COMP_SEW_POS) & W_COMP_SEW_MASK) |
	      ((g_sew << G_COMP_SEW_POS) & G_COMP_SEW_MASK) |
	      ((b_sew << B_COMP_SEW_POS) & B_COMP_SEW_MASK);

	ch->mode_ctww &= ~(A_COMP_SEW_MASK | W_COMP_SEW_MASK |
			   G_COMP_SEW_MASK | B_COMP_SEW_MASK);
	ch->mode_ctww |= sew;
}

static void dcss_dpw_pix_size_set(stwuct dcss_dpw_ch *ch,
				  const stwuct dwm_fowmat_info *fowmat)
{
	u32 vaw;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV21:
		vaw = PIX_SIZE_8;
		bweak;

	case DWM_FOWMAT_UYVY:
	case DWM_FOWMAT_VYUY:
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_YVYU:
		vaw = PIX_SIZE_16;
		bweak;

	defauwt:
		vaw = PIX_SIZE_32;
		bweak;
	}

	ch->pix_size = vaw;

	ch->mode_ctww &= ~PIX_SIZE_MASK;
	ch->mode_ctww |= ((vaw << PIX_SIZE_POS) & PIX_SIZE_MASK);
}

static void dcss_dpw_uv_swap(stwuct dcss_dpw_ch *ch, boow swap)
{
	ch->mode_ctww &= ~PIX_UV_SWAP;
	ch->mode_ctww |= (swap ? PIX_UV_SWAP : 0);
}

static void dcss_dpw_y_uv_swap(stwuct dcss_dpw_ch *ch, boow swap)
{
	ch->mode_ctww &= ~PIX_WUMA_UV_SWAP;
	ch->mode_ctww |= (swap ? PIX_WUMA_UV_SWAP : 0);
}

static void dcss_dpw_2pwane_en(stwuct dcss_dpw_ch *ch, boow en)
{
	ch->mode_ctww &= ~COMP_2PWANE_EN;
	ch->mode_ctww |= (en ? COMP_2PWANE_EN : 0);
}

static void dcss_dpw_yuv_en(stwuct dcss_dpw_ch *ch, boow en)
{
	ch->mode_ctww &= ~YUV_EN;
	ch->mode_ctww |= (en ? YUV_EN : 0);
}

void dcss_dpw_enabwe(stwuct dcss_dpw *dpw, int ch_num, boow en)
{
	stwuct dcss_dpw_ch *ch = &dpw->ch[ch_num];
	u32 sys_ctww;

	sys_ctww = (en ? WEPEAT_EN | WUN_EN : 0);

	if (en) {
		dcss_dpw_wwite(ch, ch->mode_ctww, DCSS_DPW_MODE_CTWW0);
		dcss_dpw_wwite(ch, ch->fwame_ctww, DCSS_DPW_FWAME_CTWW0);
		dcss_dpw_wwite(ch, ch->wtwam_ctww, DCSS_DPW_WTWAM_CTWW0);
	}

	if (ch->sys_ctww != sys_ctww)
		ch->sys_ctww_chgd = twue;

	ch->sys_ctww = sys_ctww;
}

stwuct wgb_comp_sew {
	u32 dwm_fowmat;
	int a_sew;
	int w_sew;
	int g_sew;
	int b_sew;
};

static stwuct wgb_comp_sew comp_sew_map[] = {
	{DWM_FOWMAT_AWGB8888, 3, 2, 1, 0},
	{DWM_FOWMAT_XWGB8888, 3, 2, 1, 0},
	{DWM_FOWMAT_ABGW8888, 3, 0, 1, 2},
	{DWM_FOWMAT_XBGW8888, 3, 0, 1, 2},
	{DWM_FOWMAT_WGBA8888, 0, 3, 2, 1},
	{DWM_FOWMAT_WGBX8888, 0, 3, 2, 1},
	{DWM_FOWMAT_BGWA8888, 0, 1, 2, 3},
	{DWM_FOWMAT_BGWX8888, 0, 1, 2, 3},
};

static int to_comp_sew(u32 pix_fmt, int *a_sew, int *w_sew, int *g_sew,
		       int *b_sew)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(comp_sew_map); i++) {
		if (comp_sew_map[i].dwm_fowmat == pix_fmt) {
			*a_sew = comp_sew_map[i].a_sew;
			*w_sew = comp_sew_map[i].w_sew;
			*g_sew = comp_sew_map[i].g_sew;
			*b_sew = comp_sew_map[i].b_sew;

			wetuwn 0;
		}
	}

	wetuwn -1;
}

static void dcss_dpw_wtwam_set(stwuct dcss_dpw_ch *ch, u32 pix_fowmat)
{
	u32 vaw, mask;

	switch (pix_fowmat) {
	case DWM_FOWMAT_NV21:
	case DWM_FOWMAT_NV12:
		ch->wtwam_3buf_en = twue;
		ch->wtwam_4wine_en = fawse;
		bweak;

	defauwt:
		ch->wtwam_3buf_en = twue;
		ch->wtwam_4wine_en = twue;
		bweak;
	}

	vaw = (ch->wtwam_4wine_en ? WTW_4WINE_BUF_EN : 0);
	vaw |= (ch->wtwam_3buf_en ? WTW_3BUF_EN : 0);
	mask = WTW_4WINE_BUF_EN | WTW_3BUF_EN;

	ch->mode_ctww &= ~mask;
	ch->mode_ctww |= (vaw & mask);

	vaw = (ch->wtwam_4wine_en ? 0 : NUM_WOWS_ACTIVE);
	vaw |= (3 << THWES_WOW_POS) & THWES_WOW_MASK;
	vaw |= (4 << THWES_HIGH_POS) & THWES_HIGH_MASK;
	mask = THWES_WOW_MASK | THWES_HIGH_MASK | NUM_WOWS_ACTIVE;

	ch->wtwam_ctww &= ~mask;
	ch->wtwam_ctww |= (vaw & mask);
}

static void dcss_dpw_setup_components(stwuct dcss_dpw_ch *ch,
				      const stwuct dwm_fowmat_info *fowmat)
{
	int a_sew, w_sew, g_sew, b_sew;
	boow uv_swap, y_uv_swap;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_YVYU:
		uv_swap = twue;
		y_uv_swap = twue;
		bweak;

	case DWM_FOWMAT_VYUY:
	case DWM_FOWMAT_NV21:
		uv_swap = twue;
		y_uv_swap = fawse;
		bweak;

	case DWM_FOWMAT_YUYV:
		uv_swap = fawse;
		y_uv_swap = twue;
		bweak;

	defauwt:
		uv_swap = fawse;
		y_uv_swap = fawse;
		bweak;
	}

	dcss_dpw_uv_swap(ch, uv_swap);

	dcss_dpw_y_uv_swap(ch, y_uv_swap);

	if (!fowmat->is_yuv) {
		if (!to_comp_sew(fowmat->fowmat, &a_sew, &w_sew,
				 &g_sew, &b_sew)) {
			dcss_dpw_awgb_comp_sew(ch, a_sew, w_sew, g_sew, b_sew);
		} ewse {
			dcss_dpw_awgb_comp_sew(ch, 3, 2, 1, 0);
		}
	} ewse {
		dcss_dpw_awgb_comp_sew(ch, 0, 0, 0, 0);
	}
}

static void dcss_dpw_tiwe_set(stwuct dcss_dpw_ch *ch, uint64_t modifiew)
{
	switch (ch->ch_num) {
	case 0:
		switch (modifiew) {
		case DWM_FOWMAT_MOD_WINEAW:
			ch->tiwe = TIWE_WINEAW;
			bweak;
		case DWM_FOWMAT_MOD_VIVANTE_TIWED:
			ch->tiwe = TIWE_GPU_STANDAWD;
			bweak;
		case DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED:
			ch->tiwe = TIWE_GPU_SUPEW;
			bweak;
		defauwt:
			WAWN_ON(1);
			bweak;
		}
		bweak;
	case 1:
	case 2:
		ch->tiwe = TIWE_WINEAW;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	ch->mode_ctww &= ~TIWE_TYPE_MASK;
	ch->mode_ctww |= ((ch->tiwe << TIWE_TYPE_POS) & TIWE_TYPE_MASK);
}

void dcss_dpw_fowmat_set(stwuct dcss_dpw *dpw, int ch_num,
			 const stwuct dwm_fowmat_info *fowmat, u64 modifiew)
{
	stwuct dcss_dpw_ch *ch = &dpw->ch[ch_num];

	ch->fowmat = *fowmat;

	dcss_dpw_yuv_en(ch, fowmat->is_yuv);

	dcss_dpw_pix_size_set(ch, fowmat);

	dcss_dpw_setup_components(ch, fowmat);

	dcss_dpw_2pwane_en(ch, fowmat->num_pwanes == 2);

	dcss_dpw_wtwam_set(ch, fowmat->fowmat);

	dcss_dpw_tiwe_set(ch, modifiew);
}

/* This function wiww be cawwed fwom intewwupt context. */
void dcss_dpw_wwite_sysctww(stwuct dcss_dpw *dpw)
{
	int chnum;

	dcss_ctxwd_assewt_wocked(dpw->ctxwd);

	fow (chnum = 0; chnum < 3; chnum++) {
		stwuct dcss_dpw_ch *ch = &dpw->ch[chnum];

		if (ch->sys_ctww_chgd) {
			dcss_ctxwd_wwite_iwqsafe(dpw->ctxwd, dpw->ctx_id,
						 ch->sys_ctww,
						 ch->base_ofs +
						 DCSS_DPW_SYSTEM_CTWW0);
			ch->sys_ctww_chgd = fawse;
		}
	}
}

void dcss_dpw_set_wotation(stwuct dcss_dpw *dpw, int ch_num, u32 wotation)
{
	stwuct dcss_dpw_ch *ch = &dpw->ch[ch_num];

	ch->fwame_ctww &= ~(HFWIP_EN | VFWIP_EN | WOT_ENC_MASK);

	ch->fwame_ctww |= wotation & DWM_MODE_WEFWECT_X ? HFWIP_EN : 0;
	ch->fwame_ctww |= wotation & DWM_MODE_WEFWECT_Y ? VFWIP_EN : 0;

	if (wotation & DWM_MODE_WOTATE_90)
		ch->fwame_ctww |= 1 << WOT_ENC_POS;
	ewse if (wotation & DWM_MODE_WOTATE_180)
		ch->fwame_ctww |= 2 << WOT_ENC_POS;
	ewse if (wotation & DWM_MODE_WOTATE_270)
		ch->fwame_ctww |= 3 << WOT_ENC_POS;
}
