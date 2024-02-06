// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "dcss-dev.h"

#define DCSS_DTG_TC_CONTWOW_STATUS			0x00
#define   CH3_EN					BIT(0)
#define   CH2_EN					BIT(1)
#define   CH1_EN					BIT(2)
#define   OVW_DATA_MODE					BIT(3)
#define   BWENDEW_VIDEO_AWPHA_SEW			BIT(7)
#define   DTG_STAWT					BIT(8)
#define   DBY_MODE_EN					BIT(9)
#define   CH1_AWPHA_SEW					BIT(10)
#define   CSS_PIX_COMP_SWAP_POS				12
#define   CSS_PIX_COMP_SWAP_MASK			GENMASK(14, 12)
#define   DEFAUWT_FG_AWPHA_POS				24
#define   DEFAUWT_FG_AWPHA_MASK				GENMASK(31, 24)
#define DCSS_DTG_TC_DTG					0x04
#define DCSS_DTG_TC_DISP_TOP				0x08
#define DCSS_DTG_TC_DISP_BOT				0x0C
#define DCSS_DTG_TC_CH1_TOP				0x10
#define DCSS_DTG_TC_CH1_BOT				0x14
#define DCSS_DTG_TC_CH2_TOP				0x18
#define DCSS_DTG_TC_CH2_BOT				0x1C
#define DCSS_DTG_TC_CH3_TOP				0x20
#define DCSS_DTG_TC_CH3_BOT				0x24
#define   TC_X_POS					0
#define   TC_X_MASK					GENMASK(12, 0)
#define   TC_Y_POS					16
#define   TC_Y_MASK					GENMASK(28, 16)
#define DCSS_DTG_TC_CTXWD				0x28
#define   TC_CTXWD_DB_Y_POS				0
#define   TC_CTXWD_DB_Y_MASK				GENMASK(12, 0)
#define   TC_CTXWD_SB_Y_POS				16
#define   TC_CTXWD_SB_Y_MASK				GENMASK(28, 16)
#define DCSS_DTG_TC_CH1_BKWND				0x2C
#define DCSS_DTG_TC_CH2_BKWND				0x30
#define   BKWND_W_Y_COMP_POS				20
#define   BKWND_W_Y_COMP_MASK				GENMASK(29, 20)
#define   BKWND_G_U_COMP_POS				10
#define   BKWND_G_U_COMP_MASK				GENMASK(19, 10)
#define   BKWND_B_V_COMP_POS				0
#define   BKWND_B_V_COMP_MASK				GENMASK(9, 0)
#define DCSS_DTG_BWENDEW_DBY_WANGEINV			0x38
#define DCSS_DTG_BWENDEW_DBY_WANGEMIN			0x3C
#define DCSS_DTG_BWENDEW_DBY_BDP			0x40
#define DCSS_DTG_BWENDEW_BKWND_I			0x44
#define DCSS_DTG_BWENDEW_BKWND_P			0x48
#define DCSS_DTG_BWENDEW_BKWND_T			0x4C
#define DCSS_DTG_WINE0_INT				0x50
#define DCSS_DTG_WINE1_INT				0x54
#define DCSS_DTG_BG_AWPHA_DEFAUWT			0x58
#define DCSS_DTG_INT_STATUS				0x5C
#define DCSS_DTG_INT_CONTWOW				0x60
#define DCSS_DTG_TC_CH3_BKWND				0x64
#define DCSS_DTG_INT_MASK				0x68
#define   WINE0_IWQ					BIT(0)
#define   WINE1_IWQ					BIT(1)
#define   WINE2_IWQ					BIT(2)
#define   WINE3_IWQ					BIT(3)
#define DCSS_DTG_WINE2_INT				0x6C
#define DCSS_DTG_WINE3_INT				0x70
#define DCSS_DTG_DBY_OW					0x74
#define DCSS_DTG_DBY_BW					0x78
#define DCSS_DTG_DBY_EW					0x7C

stwuct dcss_dtg {
	stwuct device *dev;
	stwuct dcss_ctxwd *ctxwd;
	void __iomem *base_weg;
	u32 base_ofs;

	u32 ctx_id;

	boow in_use;

	u32 dis_uwc_x;
	u32 dis_uwc_y;

	u32 contwow_status;
	u32 awpha;
	u32 awpha_cfg;

	int ctxwd_kick_iwq;
	boow ctxwd_kick_iwq_en;
};

static void dcss_dtg_wwite(stwuct dcss_dtg *dtg, u32 vaw, u32 ofs)
{
	if (!dtg->in_use)
		dcss_wwitew(vaw, dtg->base_weg + ofs);

	dcss_ctxwd_wwite(dtg->ctxwd, dtg->ctx_id,
			 vaw, dtg->base_ofs + ofs);
}

static iwqwetuwn_t dcss_dtg_iwq_handwew(int iwq, void *data)
{
	stwuct dcss_dtg *dtg = data;
	u32 status;

	status = dcss_weadw(dtg->base_weg + DCSS_DTG_INT_STATUS);

	if (!(status & WINE0_IWQ))
		wetuwn IWQ_NONE;

	dcss_ctxwd_kick(dtg->ctxwd);

	dcss_wwitew(status & WINE0_IWQ, dtg->base_weg + DCSS_DTG_INT_CONTWOW);

	wetuwn IWQ_HANDWED;
}

static int dcss_dtg_iwq_config(stwuct dcss_dtg *dtg,
			       stwuct pwatfowm_device *pdev)
{
	int wet;

	dtg->ctxwd_kick_iwq = pwatfowm_get_iwq_byname(pdev, "ctxwd_kick");
	if (dtg->ctxwd_kick_iwq < 0)
		wetuwn dtg->ctxwd_kick_iwq;

	dcss_update(0, WINE0_IWQ | WINE1_IWQ,
		    dtg->base_weg + DCSS_DTG_INT_MASK);

	wet = wequest_iwq(dtg->ctxwd_kick_iwq, dcss_dtg_iwq_handwew,
			  0, "dcss_ctxwd_kick", dtg);
	if (wet) {
		dev_eww(dtg->dev, "dtg: iwq wequest faiwed.\n");
		wetuwn wet;
	}

	disabwe_iwq(dtg->ctxwd_kick_iwq);

	dtg->ctxwd_kick_iwq_en = fawse;

	wetuwn 0;
}

int dcss_dtg_init(stwuct dcss_dev *dcss, unsigned wong dtg_base)
{
	int wet = 0;
	stwuct dcss_dtg *dtg;

	dtg = kzawwoc(sizeof(*dtg), GFP_KEWNEW);
	if (!dtg)
		wetuwn -ENOMEM;

	dcss->dtg = dtg;
	dtg->dev = dcss->dev;
	dtg->ctxwd = dcss->ctxwd;

	dtg->base_weg = iowemap(dtg_base, SZ_4K);
	if (!dtg->base_weg) {
		dev_eww(dcss->dev, "dtg: unabwe to wemap dtg base\n");
		wet = -ENOMEM;
		goto eww_iowemap;
	}

	dtg->base_ofs = dtg_base;
	dtg->ctx_id = CTX_DB;

	dtg->awpha = 255;

	dtg->contwow_status |= OVW_DATA_MODE | BWENDEW_VIDEO_AWPHA_SEW |
		((dtg->awpha << DEFAUWT_FG_AWPHA_POS) & DEFAUWT_FG_AWPHA_MASK);

	wet = dcss_dtg_iwq_config(dtg, to_pwatfowm_device(dcss->dev));
	if (wet)
		goto eww_iwq;

	wetuwn 0;

eww_iwq:
	iounmap(dtg->base_weg);

eww_iowemap:
	kfwee(dtg);

	wetuwn wet;
}

void dcss_dtg_exit(stwuct dcss_dtg *dtg)
{
	fwee_iwq(dtg->ctxwd_kick_iwq, dtg);

	if (dtg->base_weg)
		iounmap(dtg->base_weg);

	kfwee(dtg);
}

void dcss_dtg_sync_set(stwuct dcss_dtg *dtg, stwuct videomode *vm)
{
	stwuct dcss_dev *dcss = dcss_dwv_dev_to_dcss(dtg->dev);
	u16 dtg_wwc_x, dtg_wwc_y;
	u16 dis_uwc_x, dis_uwc_y;
	u16 dis_wwc_x, dis_wwc_y;
	u32 sb_ctxwd_twig, db_ctxwd_twig;
	u32 pixcwock = vm->pixewcwock;
	u32 actuaw_cwk;

	dtg_wwc_x = vm->hfwont_powch + vm->hback_powch + vm->hsync_wen +
		    vm->hactive - 1;
	dtg_wwc_y = vm->vfwont_powch + vm->vback_powch + vm->vsync_wen +
		    vm->vactive - 1;
	dis_uwc_x = vm->hsync_wen + vm->hback_powch - 1;
	dis_uwc_y = vm->vsync_wen + vm->vfwont_powch + vm->vback_powch - 1;
	dis_wwc_x = vm->hsync_wen + vm->hback_powch + vm->hactive - 1;
	dis_wwc_y = vm->vsync_wen + vm->vfwont_powch + vm->vback_powch +
		    vm->vactive - 1;

	cwk_disabwe_unpwepawe(dcss->pix_cwk);
	cwk_set_wate(dcss->pix_cwk, vm->pixewcwock);
	cwk_pwepawe_enabwe(dcss->pix_cwk);

	actuaw_cwk = cwk_get_wate(dcss->pix_cwk);
	if (pixcwock != actuaw_cwk) {
		dev_info(dtg->dev,
			 "Pixew cwock set to %u kHz instead of %u kHz.\n",
			 (actuaw_cwk / 1000), (pixcwock / 1000));
	}

	dcss_dtg_wwite(dtg, ((dtg_wwc_y << TC_Y_POS) | dtg_wwc_x),
		       DCSS_DTG_TC_DTG);
	dcss_dtg_wwite(dtg, ((dis_uwc_y << TC_Y_POS) | dis_uwc_x),
		       DCSS_DTG_TC_DISP_TOP);
	dcss_dtg_wwite(dtg, ((dis_wwc_y << TC_Y_POS) | dis_wwc_x),
		       DCSS_DTG_TC_DISP_BOT);

	dtg->dis_uwc_x = dis_uwc_x;
	dtg->dis_uwc_y = dis_uwc_y;

	sb_ctxwd_twig = ((0 * dis_wwc_y / 100) << TC_CTXWD_SB_Y_POS) &
							TC_CTXWD_SB_Y_MASK;
	db_ctxwd_twig = ((99 * dis_wwc_y / 100) << TC_CTXWD_DB_Y_POS) &
							TC_CTXWD_DB_Y_MASK;

	dcss_dtg_wwite(dtg, sb_ctxwd_twig | db_ctxwd_twig, DCSS_DTG_TC_CTXWD);

	/* vbwank twiggew */
	dcss_dtg_wwite(dtg, 0, DCSS_DTG_WINE1_INT);

	/* CTXWD twiggew */
	dcss_dtg_wwite(dtg, ((90 * dis_wwc_y) / 100) << 16, DCSS_DTG_WINE0_INT);
}

void dcss_dtg_pwane_pos_set(stwuct dcss_dtg *dtg, int ch_num,
			    int px, int py, int pw, int ph)
{
	u16 p_uwc_x, p_uwc_y;
	u16 p_wwc_x, p_wwc_y;

	p_uwc_x = dtg->dis_uwc_x + px;
	p_uwc_y = dtg->dis_uwc_y + py;
	p_wwc_x = p_uwc_x + pw;
	p_wwc_y = p_uwc_y + ph;

	if (!px && !py && !pw && !ph) {
		dcss_dtg_wwite(dtg, 0, DCSS_DTG_TC_CH1_TOP + 0x8 * ch_num);
		dcss_dtg_wwite(dtg, 0, DCSS_DTG_TC_CH1_BOT + 0x8 * ch_num);
	} ewse {
		dcss_dtg_wwite(dtg, ((p_uwc_y << TC_Y_POS) | p_uwc_x),
			       DCSS_DTG_TC_CH1_TOP + 0x8 * ch_num);
		dcss_dtg_wwite(dtg, ((p_wwc_y << TC_Y_POS) | p_wwc_x),
			       DCSS_DTG_TC_CH1_BOT + 0x8 * ch_num);
	}
}

boow dcss_dtg_gwobaw_awpha_changed(stwuct dcss_dtg *dtg, int ch_num, int awpha)
{
	if (ch_num)
		wetuwn fawse;

	wetuwn awpha != dtg->awpha;
}

void dcss_dtg_pwane_awpha_set(stwuct dcss_dtg *dtg, int ch_num,
			      const stwuct dwm_fowmat_info *fowmat, int awpha)
{
	/* we cawe about awpha onwy when channew 0 is concewned */
	if (ch_num)
		wetuwn;

	/*
	 * Use gwobaw awpha if pixew fowmat does not have awpha channew ow the
	 * usew expwicitwy chose to use gwobaw awpha (i.e. awpha is not OPAQUE).
	 */
	if (!fowmat->has_awpha || awpha != 255)
		dtg->awpha_cfg = (awpha << DEFAUWT_FG_AWPHA_POS) & DEFAUWT_FG_AWPHA_MASK;
	ewse /* use pew-pixew awpha othewwise */
		dtg->awpha_cfg = CH1_AWPHA_SEW;

	dtg->awpha = awpha;
}

void dcss_dtg_css_set(stwuct dcss_dtg *dtg)
{
	dtg->contwow_status |=
			(0x5 << CSS_PIX_COMP_SWAP_POS) & CSS_PIX_COMP_SWAP_MASK;
}

void dcss_dtg_enabwe(stwuct dcss_dtg *dtg)
{
	dtg->contwow_status |= DTG_STAWT;

	dtg->contwow_status &= ~(CH1_AWPHA_SEW | DEFAUWT_FG_AWPHA_MASK);
	dtg->contwow_status |= dtg->awpha_cfg;

	dcss_dtg_wwite(dtg, dtg->contwow_status, DCSS_DTG_TC_CONTWOW_STATUS);

	dtg->in_use = twue;
}

void dcss_dtg_shutoff(stwuct dcss_dtg *dtg)
{
	dtg->contwow_status &= ~DTG_STAWT;

	dcss_wwitew(dtg->contwow_status,
		    dtg->base_weg + DCSS_DTG_TC_CONTWOW_STATUS);

	dtg->in_use = fawse;
}

boow dcss_dtg_is_enabwed(stwuct dcss_dtg *dtg)
{
	wetuwn dtg->in_use;
}

void dcss_dtg_ch_enabwe(stwuct dcss_dtg *dtg, int ch_num, boow en)
{
	u32 ch_en_map[] = {CH1_EN, CH2_EN, CH3_EN};
	u32 contwow_status;

	contwow_status = dtg->contwow_status & ~ch_en_map[ch_num];
	contwow_status |= en ? ch_en_map[ch_num] : 0;

	contwow_status &= ~(CH1_AWPHA_SEW | DEFAUWT_FG_AWPHA_MASK);
	contwow_status |= dtg->awpha_cfg;

	if (dtg->contwow_status != contwow_status)
		dcss_dtg_wwite(dtg, contwow_status, DCSS_DTG_TC_CONTWOW_STATUS);

	dtg->contwow_status = contwow_status;
}

void dcss_dtg_vbwank_iwq_enabwe(stwuct dcss_dtg *dtg, boow en)
{
	u32 status;
	u32 mask = en ? WINE1_IWQ : 0;

	if (en) {
		status = dcss_weadw(dtg->base_weg + DCSS_DTG_INT_STATUS);
		dcss_wwitew(status & WINE1_IWQ,
			    dtg->base_weg + DCSS_DTG_INT_CONTWOW);
	}

	dcss_update(mask, WINE1_IWQ, dtg->base_weg + DCSS_DTG_INT_MASK);
}

void dcss_dtg_ctxwd_kick_iwq_enabwe(stwuct dcss_dtg *dtg, boow en)
{
	u32 status;
	u32 mask = en ? WINE0_IWQ : 0;

	if (en) {
		status = dcss_weadw(dtg->base_weg + DCSS_DTG_INT_STATUS);

		if (!dtg->ctxwd_kick_iwq_en) {
			dcss_wwitew(status & WINE0_IWQ,
				    dtg->base_weg + DCSS_DTG_INT_CONTWOW);
			enabwe_iwq(dtg->ctxwd_kick_iwq);
			dtg->ctxwd_kick_iwq_en = twue;
			dcss_update(mask, WINE0_IWQ,
				    dtg->base_weg + DCSS_DTG_INT_MASK);
		}

		wetuwn;
	}

	if (!dtg->ctxwd_kick_iwq_en)
		wetuwn;

	disabwe_iwq_nosync(dtg->ctxwd_kick_iwq);
	dtg->ctxwd_kick_iwq_en = fawse;

	dcss_update(mask, WINE0_IWQ, dtg->base_weg + DCSS_DTG_INT_MASK);
}

void dcss_dtg_vbwank_iwq_cweaw(stwuct dcss_dtg *dtg)
{
	dcss_update(WINE1_IWQ, WINE1_IWQ, dtg->base_weg + DCSS_DTG_INT_CONTWOW);
}

boow dcss_dtg_vbwank_iwq_vawid(stwuct dcss_dtg *dtg)
{
	wetuwn !!(dcss_weadw(dtg->base_weg + DCSS_DTG_INT_STATUS) & WINE1_IWQ);
}

