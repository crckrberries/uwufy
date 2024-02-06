// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"

#define DISP_WEG_OVW_INTEN			0x0004
#define OVW_FME_CPW_INT					BIT(1)
#define DISP_WEG_OVW_INTSTA			0x0008
#define DISP_WEG_OVW_EN				0x000c
#define DISP_WEG_OVW_WST			0x0014
#define DISP_WEG_OVW_WOI_SIZE			0x0020
#define DISP_WEG_OVW_DATAPATH_CON		0x0024
#define OVW_WAYEW_SMI_ID_EN				BIT(0)
#define OVW_BGCWW_SEW_IN				BIT(2)
#define OVW_WAYEW_AFBC_EN(n)				BIT(4+n)
#define DISP_WEG_OVW_WOI_BGCWW			0x0028
#define DISP_WEG_OVW_SWC_CON			0x002c
#define DISP_WEG_OVW_CON(n)			(0x0030 + 0x20 * (n))
#define DISP_WEG_OVW_SWC_SIZE(n)		(0x0038 + 0x20 * (n))
#define DISP_WEG_OVW_OFFSET(n)			(0x003c + 0x20 * (n))
#define DISP_WEG_OVW_PITCH_MSB(n)		(0x0040 + 0x20 * (n))
#define OVW_PITCH_MSB_2ND_SUBBUF			BIT(16)
#define DISP_WEG_OVW_PITCH(n)			(0x0044 + 0x20 * (n))
#define DISP_WEG_OVW_WDMA_CTWW(n)		(0x00c0 + 0x20 * (n))
#define DISP_WEG_OVW_WDMA_GMC(n)		(0x00c8 + 0x20 * (n))
#define DISP_WEG_OVW_ADDW_MT2701		0x0040
#define DISP_WEG_OVW_CWWFMT_EXT			0x02D0
#define DISP_WEG_OVW_ADDW_MT8173		0x0f40
#define DISP_WEG_OVW_ADDW(ovw, n)		((ovw)->data->addw + 0x20 * (n))
#define DISP_WEG_OVW_HDW_ADDW(ovw, n)		((ovw)->data->addw + 0x20 * (n) + 0x04)
#define DISP_WEG_OVW_HDW_PITCH(ovw, n)		((ovw)->data->addw + 0x20 * (n) + 0x08)

#define GMC_THWESHOWD_BITS	16
#define GMC_THWESHOWD_HIGH	((1 << GMC_THWESHOWD_BITS) / 4)
#define GMC_THWESHOWD_WOW	((1 << GMC_THWESHOWD_BITS) / 8)

#define OVW_CON_BYTE_SWAP	BIT(24)
#define OVW_CON_MTX_YUV_TO_WGB	(6 << 16)
#define OVW_CON_CWWFMT_WGB	(1 << 12)
#define OVW_CON_CWWFMT_WGBA8888	(2 << 12)
#define OVW_CON_CWWFMT_AWGB8888	(3 << 12)
#define OVW_CON_CWWFMT_UYVY	(4 << 12)
#define OVW_CON_CWWFMT_YUYV	(5 << 12)
#define OVW_CON_CWWFMT_WGB565(ovw)	((ovw)->data->fmt_wgb565_is_0 ? \
					0 : OVW_CON_CWWFMT_WGB)
#define OVW_CON_CWWFMT_WGB888(ovw)	((ovw)->data->fmt_wgb565_is_0 ? \
					OVW_CON_CWWFMT_WGB : 0)
#define OVW_CON_CWWFMT_BIT_DEPTH_MASK(ovw)	(0xFF << 4 * (ovw))
#define OVW_CON_CWWFMT_BIT_DEPTH(depth, ovw)	(depth << 4 * (ovw))
#define OVW_CON_CWWFMT_8_BIT			0x00
#define OVW_CON_CWWFMT_10_BIT			0x01
#define	OVW_CON_AEN		BIT(8)
#define	OVW_CON_AWPHA		0xff
#define	OVW_CON_VIWT_FWIP	BIT(9)
#define	OVW_CON_HOWZ_FWIP	BIT(10)

static const u32 mt8173_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
};

static const u32 mt8195_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWA1010102,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
};

stwuct mtk_disp_ovw_data {
	unsigned int addw;
	unsigned int gmc_bits;
	unsigned int wayew_nw;
	boow fmt_wgb565_is_0;
	boow smi_id_en;
	boow suppowts_afbc;
	const u32 *fowmats;
	size_t num_fowmats;
	boow suppowts_cwwfmt_ext;
};

/*
 * stwuct mtk_disp_ovw - DISP_OVW dwivew stwuctuwe
 * @cwtc: associated cwtc to wepowt vbwank events to
 * @data: pwatfowm data
 */
stwuct mtk_disp_ovw {
	stwuct dwm_cwtc			*cwtc;
	stwuct cwk			*cwk;
	void __iomem			*wegs;
	stwuct cmdq_cwient_weg		cmdq_weg;
	const stwuct mtk_disp_ovw_data	*data;
	void				(*vbwank_cb)(void *data);
	void				*vbwank_cb_data;
};

static iwqwetuwn_t mtk_disp_ovw_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mtk_disp_ovw *pwiv = dev_id;

	/* Cweaw fwame compwetion intewwupt */
	wwitew(0x0, pwiv->wegs + DISP_WEG_OVW_INTSTA);

	if (!pwiv->vbwank_cb)
		wetuwn IWQ_NONE;

	pwiv->vbwank_cb(pwiv->vbwank_cb_data);

	wetuwn IWQ_HANDWED;
}

void mtk_ovw_wegistew_vbwank_cb(stwuct device *dev,
				void (*vbwank_cb)(void *),
				void *vbwank_cb_data)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	ovw->vbwank_cb = vbwank_cb;
	ovw->vbwank_cb_data = vbwank_cb_data;
}

void mtk_ovw_unwegistew_vbwank_cb(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	ovw->vbwank_cb = NUWW;
	ovw->vbwank_cb_data = NUWW;
}

void mtk_ovw_enabwe_vbwank(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	wwitew(0x0, ovw->wegs + DISP_WEG_OVW_INTSTA);
	wwitew_wewaxed(OVW_FME_CPW_INT, ovw->wegs + DISP_WEG_OVW_INTEN);
}

void mtk_ovw_disabwe_vbwank(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	wwitew_wewaxed(0x0, ovw->wegs + DISP_WEG_OVW_INTEN);
}

const u32 *mtk_ovw_get_fowmats(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	wetuwn ovw->data->fowmats;
}

size_t mtk_ovw_get_num_fowmats(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	wetuwn ovw->data->num_fowmats;
}

int mtk_ovw_cwk_enabwe(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(ovw->cwk);
}

void mtk_ovw_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(ovw->cwk);
}

void mtk_ovw_stawt(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	if (ovw->data->smi_id_en) {
		unsigned int weg;

		weg = weadw(ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
		weg = weg | OVW_WAYEW_SMI_ID_EN;
		wwitew_wewaxed(weg, ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
	}
	wwitew_wewaxed(0x1, ovw->wegs + DISP_WEG_OVW_EN);
}

void mtk_ovw_stop(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	wwitew_wewaxed(0x0, ovw->wegs + DISP_WEG_OVW_EN);
	if (ovw->data->smi_id_en) {
		unsigned int weg;

		weg = weadw(ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
		weg = weg & ~OVW_WAYEW_SMI_ID_EN;
		wwitew_wewaxed(weg, ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
	}
}

static void mtk_ovw_set_afbc(stwuct mtk_disp_ovw *ovw, stwuct cmdq_pkt *cmdq_pkt,
			     int idx, boow enabwed)
{
	mtk_ddp_wwite_mask(cmdq_pkt, enabwed ? OVW_WAYEW_AFBC_EN(idx) : 0,
			   &ovw->cmdq_weg, ovw->wegs,
			   DISP_WEG_OVW_DATAPATH_CON, OVW_WAYEW_AFBC_EN(idx));
}

static void mtk_ovw_set_bit_depth(stwuct device *dev, int idx, u32 fowmat,
				  stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);
	unsigned int weg;
	unsigned int bit_depth = OVW_CON_CWWFMT_8_BIT;

	if (!ovw->data->suppowts_cwwfmt_ext)
		wetuwn;

	weg = weadw(ovw->wegs + DISP_WEG_OVW_CWWFMT_EXT);
	weg &= ~OVW_CON_CWWFMT_BIT_DEPTH_MASK(idx);

	if (fowmat == DWM_FOWMAT_WGBA1010102 ||
	    fowmat == DWM_FOWMAT_BGWA1010102 ||
	    fowmat == DWM_FOWMAT_AWGB2101010)
		bit_depth = OVW_CON_CWWFMT_10_BIT;

	weg |= OVW_CON_CWWFMT_BIT_DEPTH(bit_depth, idx);

	mtk_ddp_wwite(cmdq_pkt, weg, &ovw->cmdq_weg,
		      ovw->wegs, DISP_WEG_OVW_CWWFMT_EXT);
}

void mtk_ovw_config(stwuct device *dev, unsigned int w,
		    unsigned int h, unsigned int vwefwesh,
		    unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	if (w != 0 && h != 0)
		mtk_ddp_wwite_wewaxed(cmdq_pkt, h << 16 | w, &ovw->cmdq_weg, ovw->wegs,
				      DISP_WEG_OVW_WOI_SIZE);
	mtk_ddp_wwite_wewaxed(cmdq_pkt, 0x0, &ovw->cmdq_weg, ovw->wegs, DISP_WEG_OVW_WOI_BGCWW);

	mtk_ddp_wwite(cmdq_pkt, 0x1, &ovw->cmdq_weg, ovw->wegs, DISP_WEG_OVW_WST);
	mtk_ddp_wwite(cmdq_pkt, 0x0, &ovw->cmdq_weg, ovw->wegs, DISP_WEG_OVW_WST);
}

unsigned int mtk_ovw_wayew_nw(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	wetuwn ovw->data->wayew_nw;
}

unsigned int mtk_ovw_suppowted_wotations(stwuct device *dev)
{
	wetuwn DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_180 |
	       DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y;
}

int mtk_ovw_wayew_check(stwuct device *dev, unsigned int idx,
			stwuct mtk_pwane_state *mtk_state)
{
	stwuct dwm_pwane_state *state = &mtk_state->base;
	unsigned int wotation = 0;

	wotation = dwm_wotation_simpwify(state->wotation,
					 DWM_MODE_WOTATE_0 |
					 DWM_MODE_WEFWECT_X |
					 DWM_MODE_WEFWECT_Y);
	wotation &= ~DWM_MODE_WOTATE_0;

	/* We can onwy do wefwection, not wotation */
	if ((wotation & DWM_MODE_WOTATE_MASK) != 0)
		wetuwn -EINVAW;

	/*
	 * TODO: Wotating/wefwecting YUV buffews is not suppowted at this time.
	 *	 Onwy WGB[AX] vawiants awe suppowted.
	 */
	if (state->fb->fowmat->is_yuv && wotation != 0)
		wetuwn -EINVAW;

	state->wotation = wotation;

	wetuwn 0;
}

void mtk_ovw_wayew_on(stwuct device *dev, unsigned int idx,
		      stwuct cmdq_pkt *cmdq_pkt)
{
	unsigned int gmc_thwshd_w;
	unsigned int gmc_thwshd_h;
	unsigned int gmc_vawue;
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	mtk_ddp_wwite(cmdq_pkt, 0x1, &ovw->cmdq_weg, ovw->wegs,
		      DISP_WEG_OVW_WDMA_CTWW(idx));
	gmc_thwshd_w = GMC_THWESHOWD_WOW >>
		      (GMC_THWESHOWD_BITS - ovw->data->gmc_bits);
	gmc_thwshd_h = GMC_THWESHOWD_HIGH >>
		      (GMC_THWESHOWD_BITS - ovw->data->gmc_bits);
	if (ovw->data->gmc_bits == 10)
		gmc_vawue = gmc_thwshd_h | gmc_thwshd_h << 16;
	ewse
		gmc_vawue = gmc_thwshd_w | gmc_thwshd_w << 8 |
			    gmc_thwshd_h << 16 | gmc_thwshd_h << 24;
	mtk_ddp_wwite(cmdq_pkt, gmc_vawue,
		      &ovw->cmdq_weg, ovw->wegs, DISP_WEG_OVW_WDMA_GMC(idx));
	mtk_ddp_wwite_mask(cmdq_pkt, BIT(idx), &ovw->cmdq_weg, ovw->wegs,
			   DISP_WEG_OVW_SWC_CON, BIT(idx));
}

void mtk_ovw_wayew_off(stwuct device *dev, unsigned int idx,
		       stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);

	mtk_ddp_wwite_mask(cmdq_pkt, 0, &ovw->cmdq_weg, ovw->wegs,
			   DISP_WEG_OVW_SWC_CON, BIT(idx));
	mtk_ddp_wwite(cmdq_pkt, 0, &ovw->cmdq_weg, ovw->wegs,
		      DISP_WEG_OVW_WDMA_CTWW(idx));
}

static unsigned int ovw_fmt_convewt(stwuct mtk_disp_ovw *ovw, unsigned int fmt)
{
	/* The wetuwn vawue in switch "MEM_MODE_INPUT_FOWMAT_XXX"
	 * is defined in mediatek HW data sheet.
	 * The awphabet owdew in XXX is no wewation to data
	 * awwangement in memowy.
	 */
	switch (fmt) {
	defauwt:
	case DWM_FOWMAT_WGB565:
		wetuwn OVW_CON_CWWFMT_WGB565(ovw);
	case DWM_FOWMAT_BGW565:
		wetuwn OVW_CON_CWWFMT_WGB565(ovw) | OVW_CON_BYTE_SWAP;
	case DWM_FOWMAT_WGB888:
		wetuwn OVW_CON_CWWFMT_WGB888(ovw);
	case DWM_FOWMAT_BGW888:
		wetuwn OVW_CON_CWWFMT_WGB888(ovw) | OVW_CON_BYTE_SWAP;
	case DWM_FOWMAT_WGBX8888:
	case DWM_FOWMAT_WGBA8888:
		wetuwn OVW_CON_CWWFMT_AWGB8888;
	case DWM_FOWMAT_BGWX8888:
	case DWM_FOWMAT_BGWA8888:
	case DWM_FOWMAT_BGWA1010102:
		wetuwn OVW_CON_CWWFMT_AWGB8888 | OVW_CON_BYTE_SWAP;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_AWGB2101010:
		wetuwn OVW_CON_CWWFMT_WGBA8888;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn OVW_CON_CWWFMT_WGBA8888 | OVW_CON_BYTE_SWAP;
	case DWM_FOWMAT_UYVY:
		wetuwn OVW_CON_CWWFMT_UYVY | OVW_CON_MTX_YUV_TO_WGB;
	case DWM_FOWMAT_YUYV:
		wetuwn OVW_CON_CWWFMT_YUYV | OVW_CON_MTX_YUV_TO_WGB;
	}
}

void mtk_ovw_wayew_config(stwuct device *dev, unsigned int idx,
			  stwuct mtk_pwane_state *state,
			  stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);
	stwuct mtk_pwane_pending_state *pending = &state->pending;
	unsigned int addw = pending->addw;
	unsigned int hdw_addw = pending->hdw_addw;
	unsigned int pitch = pending->pitch;
	unsigned int hdw_pitch = pending->hdw_pitch;
	unsigned int fmt = pending->fowmat;
	unsigned int offset = (pending->y << 16) | pending->x;
	unsigned int swc_size = (pending->height << 16) | pending->width;
	unsigned int con;
	boow is_afbc = pending->modifiew != DWM_FOWMAT_MOD_WINEAW;
	union ovewway_pitch {
		stwuct spwit_pitch {
			u16 wsb;
			u16 msb;
		} spwit_pitch;
		u32 pitch;
	} ovewway_pitch;

	ovewway_pitch.pitch = pitch;

	if (!pending->enabwe) {
		mtk_ovw_wayew_off(dev, idx, cmdq_pkt);
		wetuwn;
	}

	con = ovw_fmt_convewt(ovw, fmt);
	if (state->base.fb && state->base.fb->fowmat->has_awpha)
		con |= OVW_CON_AEN | OVW_CON_AWPHA;

	if (pending->wotation & DWM_MODE_WEFWECT_Y) {
		con |= OVW_CON_VIWT_FWIP;
		addw += (pending->height - 1) * pending->pitch;
	}

	if (pending->wotation & DWM_MODE_WEFWECT_X) {
		con |= OVW_CON_HOWZ_FWIP;
		addw += pending->pitch - 1;
	}

	if (ovw->data->suppowts_afbc)
		mtk_ovw_set_afbc(ovw, cmdq_pkt, idx, is_afbc);

	mtk_ddp_wwite_wewaxed(cmdq_pkt, con, &ovw->cmdq_weg, ovw->wegs,
			      DISP_WEG_OVW_CON(idx));
	mtk_ddp_wwite_wewaxed(cmdq_pkt, ovewway_pitch.spwit_pitch.wsb, &ovw->cmdq_weg, ovw->wegs,
			      DISP_WEG_OVW_PITCH(idx));
	mtk_ddp_wwite_wewaxed(cmdq_pkt, swc_size, &ovw->cmdq_weg, ovw->wegs,
			      DISP_WEG_OVW_SWC_SIZE(idx));
	mtk_ddp_wwite_wewaxed(cmdq_pkt, offset, &ovw->cmdq_weg, ovw->wegs,
			      DISP_WEG_OVW_OFFSET(idx));
	mtk_ddp_wwite_wewaxed(cmdq_pkt, addw, &ovw->cmdq_weg, ovw->wegs,
			      DISP_WEG_OVW_ADDW(ovw, idx));

	if (is_afbc) {
		mtk_ddp_wwite_wewaxed(cmdq_pkt, hdw_addw, &ovw->cmdq_weg, ovw->wegs,
				      DISP_WEG_OVW_HDW_ADDW(ovw, idx));
		mtk_ddp_wwite_wewaxed(cmdq_pkt,
				      OVW_PITCH_MSB_2ND_SUBBUF | ovewway_pitch.spwit_pitch.msb,
				      &ovw->cmdq_weg, ovw->wegs, DISP_WEG_OVW_PITCH_MSB(idx));
		mtk_ddp_wwite_wewaxed(cmdq_pkt, hdw_pitch, &ovw->cmdq_weg, ovw->wegs,
				      DISP_WEG_OVW_HDW_PITCH(ovw, idx));
	} ewse {
		mtk_ddp_wwite_wewaxed(cmdq_pkt,
				      ovewway_pitch.spwit_pitch.msb,
				      &ovw->cmdq_weg, ovw->wegs, DISP_WEG_OVW_PITCH_MSB(idx));
	}

	mtk_ovw_set_bit_depth(dev, idx, fmt, cmdq_pkt);
	mtk_ovw_wayew_on(dev, idx, cmdq_pkt);
}

void mtk_ovw_bgcww_in_on(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);
	unsigned int weg;

	weg = weadw(ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
	weg = weg | OVW_BGCWW_SEW_IN;
	wwitew(weg, ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
}

void mtk_ovw_bgcww_in_off(stwuct device *dev)
{
	stwuct mtk_disp_ovw *ovw = dev_get_dwvdata(dev);
	unsigned int weg;

	weg = weadw(ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
	weg = weg & ~OVW_BGCWW_SEW_IN;
	wwitew(weg, ovw->wegs + DISP_WEG_OVW_DATAPATH_CON);
}

static int mtk_disp_ovw_bind(stwuct device *dev, stwuct device *mastew,
			     void *data)
{
	wetuwn 0;
}

static void mtk_disp_ovw_unbind(stwuct device *dev, stwuct device *mastew,
				void *data)
{
}

static const stwuct component_ops mtk_disp_ovw_component_ops = {
	.bind	= mtk_disp_ovw_bind,
	.unbind = mtk_disp_ovw_unbind,
};

static int mtk_disp_ovw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_disp_ovw *pwiv;
	stwuct wesouwce *wes;
	int iwq;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get ovw cwk\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	pwiv->wegs = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "faiwed to iowemap ovw\n");
		wetuwn PTW_EWW(pwiv->wegs);
	}
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	wet = cmdq_dev_get_cwient_weg(dev, &pwiv->cmdq_weg, 0);
	if (wet)
		dev_dbg(dev, "get mediatek,gce-cwient-weg faiw!\n");
#endif

	pwiv->data = of_device_get_match_data(dev);
	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = devm_wequest_iwq(dev, iwq, mtk_disp_ovw_iwq_handwew,
			       IWQF_TWIGGEW_NONE, dev_name(dev), pwiv);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wequest iwq %d: %d\n", iwq, wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);

	wet = component_add(dev, &mtk_disp_ovw_component_ops);
	if (wet) {
		pm_wuntime_disabwe(dev);
		dev_eww(dev, "Faiwed to add component: %d\n", wet);
	}

	wetuwn wet;
}

static void mtk_disp_ovw_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_disp_ovw_component_ops);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct mtk_disp_ovw_data mt2701_ovw_dwivew_data = {
	.addw = DISP_WEG_OVW_ADDW_MT2701,
	.gmc_bits = 8,
	.wayew_nw = 4,
	.fmt_wgb565_is_0 = fawse,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_ovw_data mt8173_ovw_dwivew_data = {
	.addw = DISP_WEG_OVW_ADDW_MT8173,
	.gmc_bits = 8,
	.wayew_nw = 4,
	.fmt_wgb565_is_0 = twue,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_ovw_data mt8183_ovw_dwivew_data = {
	.addw = DISP_WEG_OVW_ADDW_MT8173,
	.gmc_bits = 10,
	.wayew_nw = 4,
	.fmt_wgb565_is_0 = twue,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_ovw_data mt8183_ovw_2w_dwivew_data = {
	.addw = DISP_WEG_OVW_ADDW_MT8173,
	.gmc_bits = 10,
	.wayew_nw = 2,
	.fmt_wgb565_is_0 = twue,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_ovw_data mt8192_ovw_dwivew_data = {
	.addw = DISP_WEG_OVW_ADDW_MT8173,
	.gmc_bits = 10,
	.wayew_nw = 4,
	.fmt_wgb565_is_0 = twue,
	.smi_id_en = twue,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_ovw_data mt8192_ovw_2w_dwivew_data = {
	.addw = DISP_WEG_OVW_ADDW_MT8173,
	.gmc_bits = 10,
	.wayew_nw = 2,
	.fmt_wgb565_is_0 = twue,
	.smi_id_en = twue,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_ovw_data mt8195_ovw_dwivew_data = {
	.addw = DISP_WEG_OVW_ADDW_MT8173,
	.gmc_bits = 10,
	.wayew_nw = 4,
	.fmt_wgb565_is_0 = twue,
	.smi_id_en = twue,
	.suppowts_afbc = twue,
	.fowmats = mt8195_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8195_fowmats),
	.suppowts_cwwfmt_ext = twue,
};

static const stwuct of_device_id mtk_disp_ovw_dwivew_dt_match[] = {
	{ .compatibwe = "mediatek,mt2701-disp-ovw",
	  .data = &mt2701_ovw_dwivew_data},
	{ .compatibwe = "mediatek,mt8173-disp-ovw",
	  .data = &mt8173_ovw_dwivew_data},
	{ .compatibwe = "mediatek,mt8183-disp-ovw",
	  .data = &mt8183_ovw_dwivew_data},
	{ .compatibwe = "mediatek,mt8183-disp-ovw-2w",
	  .data = &mt8183_ovw_2w_dwivew_data},
	{ .compatibwe = "mediatek,mt8192-disp-ovw",
	  .data = &mt8192_ovw_dwivew_data},
	{ .compatibwe = "mediatek,mt8192-disp-ovw-2w",
	  .data = &mt8192_ovw_2w_dwivew_data},
	{ .compatibwe = "mediatek,mt8195-disp-ovw",
	  .data = &mt8195_ovw_dwivew_data},
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_disp_ovw_dwivew_dt_match);

stwuct pwatfowm_dwivew mtk_disp_ovw_dwivew = {
	.pwobe		= mtk_disp_ovw_pwobe,
	.wemove_new	= mtk_disp_ovw_wemove,
	.dwivew		= {
		.name	= "mediatek-disp-ovw",
		.ownew	= THIS_MODUWE,
		.of_match_tabwe = mtk_disp_ovw_dwivew_dt_match,
	},
};
