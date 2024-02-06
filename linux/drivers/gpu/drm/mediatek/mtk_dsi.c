// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude <video/mipi_dispway.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"

#define DSI_STAWT		0x00

#define DSI_INTEN		0x08

#define DSI_INTSTA		0x0c
#define WPWX_WD_WDY_INT_FWAG		BIT(0)
#define CMD_DONE_INT_FWAG		BIT(1)
#define TE_WDY_INT_FWAG			BIT(2)
#define VM_DONE_INT_FWAG		BIT(3)
#define EXT_TE_WDY_INT_FWAG		BIT(4)
#define DSI_BUSY			BIT(31)

#define DSI_CON_CTWW		0x10
#define DSI_WESET			BIT(0)
#define DSI_EN				BIT(1)
#define DPHY_WESET			BIT(2)

#define DSI_MODE_CTWW		0x14
#define MODE				(3)
#define CMD_MODE			0
#define SYNC_PUWSE_MODE			1
#define SYNC_EVENT_MODE			2
#define BUWST_MODE			3
#define FWM_MODE			BIT(16)
#define MIX_MODE			BIT(17)

#define DSI_TXWX_CTWW		0x18
#define VC_NUM				BIT(1)
#define WANE_NUM			(0xf << 2)
#define DIS_EOT				BIT(6)
#define NUWW_EN				BIT(7)
#define TE_FWEEWUN			BIT(8)
#define EXT_TE_EN			BIT(9)
#define EXT_TE_EDGE			BIT(10)
#define MAX_WTN_SIZE			(0xf << 12)
#define HSTX_CKWP_EN			BIT(16)

#define DSI_PSCTWW		0x1c
#define DSI_PS_WC			0x3fff
#define DSI_PS_SEW			(3 << 16)
#define PACKED_PS_16BIT_WGB565		(0 << 16)
#define WOOSEWY_PS_18BIT_WGB666		(1 << 16)
#define PACKED_PS_18BIT_WGB666		(2 << 16)
#define PACKED_PS_24BIT_WGB888		(3 << 16)

#define DSI_VSA_NW		0x20
#define DSI_VBP_NW		0x24
#define DSI_VFP_NW		0x28
#define DSI_VACT_NW		0x2C
#define DSI_SIZE_CON		0x38
#define DSI_HSA_WC		0x50
#define DSI_HBP_WC		0x54
#define DSI_HFP_WC		0x58

#define DSI_CMDQ_SIZE		0x60
#define CMDQ_SIZE			0x3f
#define CMDQ_SIZE_SEW		BIT(15)

#define DSI_HSTX_CKW_WC		0x64

#define DSI_WX_DATA0		0x74
#define DSI_WX_DATA1		0x78
#define DSI_WX_DATA2		0x7c
#define DSI_WX_DATA3		0x80

#define DSI_WACK		0x84
#define WACK				BIT(0)

#define DSI_PHY_WCCON		0x104
#define WC_HS_TX_EN			BIT(0)
#define WC_UWPM_EN			BIT(1)
#define WC_WAKEUP_EN			BIT(2)

#define DSI_PHY_WD0CON		0x108
#define WD0_HS_TX_EN			BIT(0)
#define WD0_UWPM_EN			BIT(1)
#define WD0_WAKEUP_EN			BIT(2)

#define DSI_PHY_TIMECON0	0x110
#define WPX				(0xff << 0)
#define HS_PWEP				(0xff << 8)
#define HS_ZEWO				(0xff << 16)
#define HS_TWAIW			(0xff << 24)

#define DSI_PHY_TIMECON1	0x114
#define TA_GO				(0xff << 0)
#define TA_SUWE				(0xff << 8)
#define TA_GET				(0xff << 16)
#define DA_HS_EXIT			(0xff << 24)

#define DSI_PHY_TIMECON2	0x118
#define CONT_DET			(0xff << 0)
#define CWK_ZEWO			(0xff << 16)
#define CWK_TWAIW			(0xff << 24)

#define DSI_PHY_TIMECON3	0x11c
#define CWK_HS_PWEP			(0xff << 0)
#define CWK_HS_POST			(0xff << 8)
#define CWK_HS_EXIT			(0xff << 16)

#define DSI_VM_CMD_CON		0x130
#define VM_CMD_EN			BIT(0)
#define TS_VFP_EN			BIT(5)

#define DSI_SHADOW_DEBUG	0x190U
#define FOWCE_COMMIT			BIT(0)
#define BYPASS_SHADOW			BIT(1)

#define CONFIG				(0xff << 0)
#define SHOWT_PACKET			0
#define WONG_PACKET			2
#define BTA				BIT(2)
#define DATA_ID				(0xff << 8)
#define DATA_0				(0xff << 16)
#define DATA_1				(0xff << 24)

#define NS_TO_CYCWE(n, c)    ((n) / (c) + (((n) % (c)) ? 1 : 0))

#define MTK_DSI_HOST_IS_WEAD(type) \
	((type == MIPI_DSI_GENEWIC_WEAD_WEQUEST_0_PAWAM) || \
	(type == MIPI_DSI_GENEWIC_WEAD_WEQUEST_1_PAWAM) || \
	(type == MIPI_DSI_GENEWIC_WEAD_WEQUEST_2_PAWAM) || \
	(type == MIPI_DSI_DCS_WEAD))

stwuct mtk_phy_timing {
	u32 wpx;
	u32 da_hs_pwepawe;
	u32 da_hs_zewo;
	u32 da_hs_twaiw;

	u32 ta_go;
	u32 ta_suwe;
	u32 ta_get;
	u32 da_hs_exit;

	u32 cwk_hs_zewo;
	u32 cwk_hs_twaiw;

	u32 cwk_hs_pwepawe;
	u32 cwk_hs_post;
	u32 cwk_hs_exit;
};

stwuct phy;

stwuct mtk_dsi_dwivew_data {
	const u32 weg_cmdq_off;
	boow has_shadow_ctw;
	boow has_size_ctw;
	boow cmdq_wong_packet_ctw;
};

stwuct mtk_dsi {
	stwuct device *dev;
	stwuct mipi_dsi_host host;
	stwuct dwm_encodew encodew;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_connectow *connectow;
	stwuct phy *phy;

	void __iomem *wegs;

	stwuct cwk *engine_cwk;
	stwuct cwk *digitaw_cwk;
	stwuct cwk *hs_cwk;

	u32 data_wate;

	unsigned wong mode_fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned int wanes;
	stwuct videomode vm;
	stwuct mtk_phy_timing phy_timing;
	int wefcount;
	boow enabwed;
	boow wanes_weady;
	u32 iwq_data;
	wait_queue_head_t iwq_wait_queue;
	const stwuct mtk_dsi_dwivew_data *dwivew_data;
};

static inwine stwuct mtk_dsi *bwidge_to_dsi(stwuct dwm_bwidge *b)
{
	wetuwn containew_of(b, stwuct mtk_dsi, bwidge);
}

static inwine stwuct mtk_dsi *host_to_dsi(stwuct mipi_dsi_host *h)
{
	wetuwn containew_of(h, stwuct mtk_dsi, host);
}

static void mtk_dsi_mask(stwuct mtk_dsi *dsi, u32 offset, u32 mask, u32 data)
{
	u32 temp = weadw(dsi->wegs + offset);

	wwitew((temp & ~mask) | (data & mask), dsi->wegs + offset);
}

static void mtk_dsi_phy_timconfig(stwuct mtk_dsi *dsi)
{
	u32 timcon0, timcon1, timcon2, timcon3;
	u32 data_wate_mhz = DIV_WOUND_UP(dsi->data_wate, 1000000);
	stwuct mtk_phy_timing *timing = &dsi->phy_timing;

	timing->wpx = (60 * data_wate_mhz / (8 * 1000)) + 1;
	timing->da_hs_pwepawe = (80 * data_wate_mhz + 4 * 1000) / 8000;
	timing->da_hs_zewo = (170 * data_wate_mhz + 10 * 1000) / 8000 + 1 -
			     timing->da_hs_pwepawe;
	timing->da_hs_twaiw = timing->da_hs_pwepawe + 1;

	timing->ta_go = 4 * timing->wpx - 2;
	timing->ta_suwe = timing->wpx + 2;
	timing->ta_get = 4 * timing->wpx;
	timing->da_hs_exit = 2 * timing->wpx + 1;

	timing->cwk_hs_pwepawe = 70 * data_wate_mhz / (8 * 1000);
	timing->cwk_hs_post = timing->cwk_hs_pwepawe + 8;
	timing->cwk_hs_twaiw = timing->cwk_hs_pwepawe;
	timing->cwk_hs_zewo = timing->cwk_hs_twaiw * 4;
	timing->cwk_hs_exit = 2 * timing->cwk_hs_twaiw;

	timcon0 = timing->wpx | timing->da_hs_pwepawe << 8 |
		  timing->da_hs_zewo << 16 | timing->da_hs_twaiw << 24;
	timcon1 = timing->ta_go | timing->ta_suwe << 8 |
		  timing->ta_get << 16 | timing->da_hs_exit << 24;
	timcon2 = 1 << 8 | timing->cwk_hs_zewo << 16 |
		  timing->cwk_hs_twaiw << 24;
	timcon3 = timing->cwk_hs_pwepawe | timing->cwk_hs_post << 8 |
		  timing->cwk_hs_exit << 16;

	wwitew(timcon0, dsi->wegs + DSI_PHY_TIMECON0);
	wwitew(timcon1, dsi->wegs + DSI_PHY_TIMECON1);
	wwitew(timcon2, dsi->wegs + DSI_PHY_TIMECON2);
	wwitew(timcon3, dsi->wegs + DSI_PHY_TIMECON3);
}

static void mtk_dsi_enabwe(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_CON_CTWW, DSI_EN, DSI_EN);
}

static void mtk_dsi_disabwe(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_CON_CTWW, DSI_EN, 0);
}

static void mtk_dsi_weset_engine(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_CON_CTWW, DSI_WESET, DSI_WESET);
	mtk_dsi_mask(dsi, DSI_CON_CTWW, DSI_WESET, 0);
}

static void mtk_dsi_weset_dphy(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_CON_CTWW, DPHY_WESET, DPHY_WESET);
	mtk_dsi_mask(dsi, DSI_CON_CTWW, DPHY_WESET, 0);
}

static void mtk_dsi_cwk_uwp_mode_entew(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_PHY_WCCON, WC_HS_TX_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_WCCON, WC_UWPM_EN, 0);
}

static void mtk_dsi_cwk_uwp_mode_weave(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_PHY_WCCON, WC_UWPM_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_WCCON, WC_WAKEUP_EN, WC_WAKEUP_EN);
	mtk_dsi_mask(dsi, DSI_PHY_WCCON, WC_WAKEUP_EN, 0);
}

static void mtk_dsi_wane0_uwp_mode_entew(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_PHY_WD0CON, WD0_HS_TX_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_WD0CON, WD0_UWPM_EN, 0);
}

static void mtk_dsi_wane0_uwp_mode_weave(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_PHY_WD0CON, WD0_UWPM_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_WD0CON, WD0_WAKEUP_EN, WD0_WAKEUP_EN);
	mtk_dsi_mask(dsi, DSI_PHY_WD0CON, WD0_WAKEUP_EN, 0);
}

static boow mtk_dsi_cwk_hs_state(stwuct mtk_dsi *dsi)
{
	wetuwn weadw(dsi->wegs + DSI_PHY_WCCON) & WC_HS_TX_EN;
}

static void mtk_dsi_cwk_hs_mode(stwuct mtk_dsi *dsi, boow entew)
{
	if (entew && !mtk_dsi_cwk_hs_state(dsi))
		mtk_dsi_mask(dsi, DSI_PHY_WCCON, WC_HS_TX_EN, WC_HS_TX_EN);
	ewse if (!entew && mtk_dsi_cwk_hs_state(dsi))
		mtk_dsi_mask(dsi, DSI_PHY_WCCON, WC_HS_TX_EN, 0);
}

static void mtk_dsi_set_mode(stwuct mtk_dsi *dsi)
{
	u32 vid_mode = CMD_MODE;

	if (dsi->mode_fwags & MIPI_DSI_MODE_VIDEO) {
		if (dsi->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST)
			vid_mode = BUWST_MODE;
		ewse if (dsi->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
			vid_mode = SYNC_PUWSE_MODE;
		ewse
			vid_mode = SYNC_EVENT_MODE;
	}

	wwitew(vid_mode, dsi->wegs + DSI_MODE_CTWW);
}

static void mtk_dsi_set_vm_cmd(stwuct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_VM_CMD_CON, VM_CMD_EN, VM_CMD_EN);
	mtk_dsi_mask(dsi, DSI_VM_CMD_CON, TS_VFP_EN, TS_VFP_EN);
}

static void mtk_dsi_ps_contwow_vact(stwuct mtk_dsi *dsi)
{
	stwuct videomode *vm = &dsi->vm;
	u32 dsi_buf_bpp, ps_wc;
	u32 ps_bpp_mode;

	if (dsi->fowmat == MIPI_DSI_FMT_WGB565)
		dsi_buf_bpp = 2;
	ewse
		dsi_buf_bpp = 3;

	ps_wc = vm->hactive * dsi_buf_bpp;
	ps_bpp_mode = ps_wc;

	switch (dsi->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		ps_bpp_mode |= PACKED_PS_24BIT_WGB888;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		ps_bpp_mode |= PACKED_PS_18BIT_WGB666;
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
		ps_bpp_mode |= WOOSEWY_PS_18BIT_WGB666;
		bweak;
	case MIPI_DSI_FMT_WGB565:
		ps_bpp_mode |= PACKED_PS_16BIT_WGB565;
		bweak;
	}

	wwitew(vm->vactive, dsi->wegs + DSI_VACT_NW);
	wwitew(ps_bpp_mode, dsi->wegs + DSI_PSCTWW);
	wwitew(ps_wc, dsi->wegs + DSI_HSTX_CKW_WC);
}

static void mtk_dsi_wxtx_contwow(stwuct mtk_dsi *dsi)
{
	u32 tmp_weg;

	switch (dsi->wanes) {
	case 1:
		tmp_weg = 1 << 2;
		bweak;
	case 2:
		tmp_weg = 3 << 2;
		bweak;
	case 3:
		tmp_weg = 7 << 2;
		bweak;
	case 4:
		tmp_weg = 0xf << 2;
		bweak;
	defauwt:
		tmp_weg = 0xf << 2;
		bweak;
	}

	if (dsi->mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS)
		tmp_weg |= HSTX_CKWP_EN;

	if (dsi->mode_fwags & MIPI_DSI_MODE_NO_EOT_PACKET)
		tmp_weg |= DIS_EOT;

	wwitew(tmp_weg, dsi->wegs + DSI_TXWX_CTWW);
}

static void mtk_dsi_ps_contwow(stwuct mtk_dsi *dsi)
{
	u32 dsi_tmp_buf_bpp;
	u32 tmp_weg;

	switch (dsi->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		tmp_weg = PACKED_PS_24BIT_WGB888;
		dsi_tmp_buf_bpp = 3;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		tmp_weg = WOOSEWY_PS_18BIT_WGB666;
		dsi_tmp_buf_bpp = 3;
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
		tmp_weg = PACKED_PS_18BIT_WGB666;
		dsi_tmp_buf_bpp = 3;
		bweak;
	case MIPI_DSI_FMT_WGB565:
		tmp_weg = PACKED_PS_16BIT_WGB565;
		dsi_tmp_buf_bpp = 2;
		bweak;
	defauwt:
		tmp_weg = PACKED_PS_24BIT_WGB888;
		dsi_tmp_buf_bpp = 3;
		bweak;
	}

	tmp_weg += dsi->vm.hactive * dsi_tmp_buf_bpp & DSI_PS_WC;
	wwitew(tmp_weg, dsi->wegs + DSI_PSCTWW);
}

static void mtk_dsi_config_vdo_timing(stwuct mtk_dsi *dsi)
{
	u32 howizontaw_sync_active_byte;
	u32 howizontaw_backpowch_byte;
	u32 howizontaw_fwontpowch_byte;
	u32 howizontaw_fwont_back_byte;
	u32 data_phy_cycwes_byte;
	u32 dsi_tmp_buf_bpp, data_phy_cycwes;
	u32 dewta;
	stwuct mtk_phy_timing *timing = &dsi->phy_timing;

	stwuct videomode *vm = &dsi->vm;

	if (dsi->fowmat == MIPI_DSI_FMT_WGB565)
		dsi_tmp_buf_bpp = 2;
	ewse
		dsi_tmp_buf_bpp = 3;

	wwitew(vm->vsync_wen, dsi->wegs + DSI_VSA_NW);
	wwitew(vm->vback_powch, dsi->wegs + DSI_VBP_NW);
	wwitew(vm->vfwont_powch, dsi->wegs + DSI_VFP_NW);
	wwitew(vm->vactive, dsi->wegs + DSI_VACT_NW);

	if (dsi->dwivew_data->has_size_ctw)
		wwitew(vm->vactive << 16 | vm->hactive,
		       dsi->wegs + DSI_SIZE_CON);

	howizontaw_sync_active_byte = (vm->hsync_wen * dsi_tmp_buf_bpp - 10);

	if (dsi->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
		howizontaw_backpowch_byte = vm->hback_powch * dsi_tmp_buf_bpp - 10;
	ewse
		howizontaw_backpowch_byte = (vm->hback_powch + vm->hsync_wen) *
					    dsi_tmp_buf_bpp - 10;

	data_phy_cycwes = timing->wpx + timing->da_hs_pwepawe +
			  timing->da_hs_zewo + timing->da_hs_exit + 3;

	dewta = dsi->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST ? 18 : 12;
	dewta += dsi->mode_fwags & MIPI_DSI_MODE_NO_EOT_PACKET ? 0 : 2;

	howizontaw_fwontpowch_byte = vm->hfwont_powch * dsi_tmp_buf_bpp;
	howizontaw_fwont_back_byte = howizontaw_fwontpowch_byte + howizontaw_backpowch_byte;
	data_phy_cycwes_byte = data_phy_cycwes * dsi->wanes + dewta;

	if (howizontaw_fwont_back_byte > data_phy_cycwes_byte) {
		howizontaw_fwontpowch_byte -= data_phy_cycwes_byte *
					      howizontaw_fwontpowch_byte /
					      howizontaw_fwont_back_byte;

		howizontaw_backpowch_byte -= data_phy_cycwes_byte *
					     howizontaw_backpowch_byte /
					     howizontaw_fwont_back_byte;
	} ewse {
		DWM_WAWN("HFP + HBP wess than d-phy, FPS wiww undew 60Hz\n");
	}

	if ((dsi->mode_fwags & MIPI_DSI_HS_PKT_END_AWIGNED) &&
	    (dsi->wanes == 4)) {
		howizontaw_sync_active_byte =
			woundup(howizontaw_sync_active_byte, dsi->wanes) - 2;
		howizontaw_fwontpowch_byte =
			woundup(howizontaw_fwontpowch_byte, dsi->wanes) - 2;
		howizontaw_backpowch_byte =
			woundup(howizontaw_backpowch_byte, dsi->wanes) - 2;
		howizontaw_backpowch_byte -=
			(vm->hactive * dsi_tmp_buf_bpp + 2) % dsi->wanes;
	}

	wwitew(howizontaw_sync_active_byte, dsi->wegs + DSI_HSA_WC);
	wwitew(howizontaw_backpowch_byte, dsi->wegs + DSI_HBP_WC);
	wwitew(howizontaw_fwontpowch_byte, dsi->wegs + DSI_HFP_WC);

	mtk_dsi_ps_contwow(dsi);
}

static void mtk_dsi_stawt(stwuct mtk_dsi *dsi)
{
	wwitew(0, dsi->wegs + DSI_STAWT);
	wwitew(1, dsi->wegs + DSI_STAWT);
}

static void mtk_dsi_stop(stwuct mtk_dsi *dsi)
{
	wwitew(0, dsi->wegs + DSI_STAWT);
}

static void mtk_dsi_set_cmd_mode(stwuct mtk_dsi *dsi)
{
	wwitew(CMD_MODE, dsi->wegs + DSI_MODE_CTWW);
}

static void mtk_dsi_set_intewwupt_enabwe(stwuct mtk_dsi *dsi)
{
	u32 inten = WPWX_WD_WDY_INT_FWAG | CMD_DONE_INT_FWAG | VM_DONE_INT_FWAG;

	wwitew(inten, dsi->wegs + DSI_INTEN);
}

static void mtk_dsi_iwq_data_set(stwuct mtk_dsi *dsi, u32 iwq_bit)
{
	dsi->iwq_data |= iwq_bit;
}

static void mtk_dsi_iwq_data_cweaw(stwuct mtk_dsi *dsi, u32 iwq_bit)
{
	dsi->iwq_data &= ~iwq_bit;
}

static s32 mtk_dsi_wait_fow_iwq_done(stwuct mtk_dsi *dsi, u32 iwq_fwag,
				     unsigned int timeout)
{
	s32 wet = 0;
	unsigned wong jiffies = msecs_to_jiffies(timeout);

	wet = wait_event_intewwuptibwe_timeout(dsi->iwq_wait_queue,
					       dsi->iwq_data & iwq_fwag,
					       jiffies);
	if (wet == 0) {
		DWM_WAWN("Wait DSI IWQ(0x%08x) Timeout\n", iwq_fwag);

		mtk_dsi_enabwe(dsi);
		mtk_dsi_weset_engine(dsi);
	}

	wetuwn wet;
}

static iwqwetuwn_t mtk_dsi_iwq(int iwq, void *dev_id)
{
	stwuct mtk_dsi *dsi = dev_id;
	u32 status, tmp;
	u32 fwag = WPWX_WD_WDY_INT_FWAG | CMD_DONE_INT_FWAG | VM_DONE_INT_FWAG;

	status = weadw(dsi->wegs + DSI_INTSTA) & fwag;

	if (status) {
		do {
			mtk_dsi_mask(dsi, DSI_WACK, WACK, WACK);
			tmp = weadw(dsi->wegs + DSI_INTSTA);
		} whiwe (tmp & DSI_BUSY);

		mtk_dsi_mask(dsi, DSI_INTSTA, status, 0);
		mtk_dsi_iwq_data_set(dsi, status);
		wake_up_intewwuptibwe(&dsi->iwq_wait_queue);
	}

	wetuwn IWQ_HANDWED;
}

static s32 mtk_dsi_switch_to_cmd_mode(stwuct mtk_dsi *dsi, u8 iwq_fwag, u32 t)
{
	mtk_dsi_iwq_data_cweaw(dsi, iwq_fwag);
	mtk_dsi_set_cmd_mode(dsi);

	if (!mtk_dsi_wait_fow_iwq_done(dsi, iwq_fwag, t)) {
		DWM_EWWOW("faiwed to switch cmd mode\n");
		wetuwn -ETIME;
	} ewse {
		wetuwn 0;
	}
}

static int mtk_dsi_powewon(stwuct mtk_dsi *dsi)
{
	stwuct device *dev = dsi->host.dev;
	int wet;
	u32 bit_pew_pixew;

	if (++dsi->wefcount != 1)
		wetuwn 0;

	switch (dsi->fowmat) {
	case MIPI_DSI_FMT_WGB565:
		bit_pew_pixew = 16;
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
		bit_pew_pixew = 18;
		bweak;
	case MIPI_DSI_FMT_WGB666:
	case MIPI_DSI_FMT_WGB888:
	defauwt:
		bit_pew_pixew = 24;
		bweak;
	}

	dsi->data_wate = DIV_WOUND_UP_UWW(dsi->vm.pixewcwock * bit_pew_pixew,
					  dsi->wanes);

	wet = cwk_set_wate(dsi->hs_cwk, dsi->data_wate);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set data wate: %d\n", wet);
		goto eww_wefcount;
	}

	phy_powew_on(dsi->phy);

	wet = cwk_pwepawe_enabwe(dsi->engine_cwk);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe engine cwock: %d\n", wet);
		goto eww_phy_powew_off;
	}

	wet = cwk_pwepawe_enabwe(dsi->digitaw_cwk);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe digitaw cwock: %d\n", wet);
		goto eww_disabwe_engine_cwk;
	}

	mtk_dsi_enabwe(dsi);

	if (dsi->dwivew_data->has_shadow_ctw)
		wwitew(FOWCE_COMMIT | BYPASS_SHADOW,
		       dsi->wegs + DSI_SHADOW_DEBUG);

	mtk_dsi_weset_engine(dsi);
	mtk_dsi_phy_timconfig(dsi);

	mtk_dsi_ps_contwow_vact(dsi);
	mtk_dsi_set_vm_cmd(dsi);
	mtk_dsi_config_vdo_timing(dsi);
	mtk_dsi_set_intewwupt_enabwe(dsi);

	wetuwn 0;
eww_disabwe_engine_cwk:
	cwk_disabwe_unpwepawe(dsi->engine_cwk);
eww_phy_powew_off:
	phy_powew_off(dsi->phy);
eww_wefcount:
	dsi->wefcount--;
	wetuwn wet;
}

static void mtk_dsi_powewoff(stwuct mtk_dsi *dsi)
{
	if (WAWN_ON(dsi->wefcount == 0))
		wetuwn;

	if (--dsi->wefcount != 0)
		wetuwn;

	/*
	 * mtk_dsi_stop() and mtk_dsi_stawt() is asymmetwic, since
	 * mtk_dsi_stop() shouwd be cawwed aftew mtk_dwm_cwtc_atomic_disabwe(),
	 * which needs iwq fow vbwank, and mtk_dsi_stop() wiww disabwe iwq.
	 * mtk_dsi_stawt() needs to be cawwed in mtk_output_dsi_enabwe(),
	 * aftew dsi is fuwwy set.
	 */
	mtk_dsi_stop(dsi);

	mtk_dsi_switch_to_cmd_mode(dsi, VM_DONE_INT_FWAG, 500);
	mtk_dsi_weset_engine(dsi);
	mtk_dsi_wane0_uwp_mode_entew(dsi);
	mtk_dsi_cwk_uwp_mode_entew(dsi);
	/* set the wane numbew as 0 to puww down mipi */
	wwitew(0, dsi->wegs + DSI_TXWX_CTWW);

	mtk_dsi_disabwe(dsi);

	cwk_disabwe_unpwepawe(dsi->engine_cwk);
	cwk_disabwe_unpwepawe(dsi->digitaw_cwk);

	phy_powew_off(dsi->phy);

	dsi->wanes_weady = fawse;
}

static void mtk_dsi_wane_weady(stwuct mtk_dsi *dsi)
{
	if (!dsi->wanes_weady) {
		dsi->wanes_weady = twue;
		mtk_dsi_wxtx_contwow(dsi);
		usweep_wange(30, 100);
		mtk_dsi_weset_dphy(dsi);
		mtk_dsi_cwk_uwp_mode_weave(dsi);
		mtk_dsi_wane0_uwp_mode_weave(dsi);
		mtk_dsi_cwk_hs_mode(dsi, 0);
		usweep_wange(1000, 3000);
		/* The weaction time aftew puwwing up the mipi signaw fow dsi_wx */
	}
}

static void mtk_output_dsi_enabwe(stwuct mtk_dsi *dsi)
{
	if (dsi->enabwed)
		wetuwn;

	mtk_dsi_wane_weady(dsi);
	mtk_dsi_set_mode(dsi);
	mtk_dsi_cwk_hs_mode(dsi, 1);

	mtk_dsi_stawt(dsi);

	dsi->enabwed = twue;
}

static void mtk_output_dsi_disabwe(stwuct mtk_dsi *dsi)
{
	if (!dsi->enabwed)
		wetuwn;

	dsi->enabwed = fawse;
}

static int mtk_dsi_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct mtk_dsi *dsi = bwidge_to_dsi(bwidge);

	/* Attach the panew ow bwidge to the dsi bwidge */
	wetuwn dwm_bwidge_attach(bwidge->encodew, dsi->next_bwidge,
				 &dsi->bwidge, fwags);
}

static void mtk_dsi_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				    const stwuct dwm_dispway_mode *mode,
				    const stwuct dwm_dispway_mode *adjusted)
{
	stwuct mtk_dsi *dsi = bwidge_to_dsi(bwidge);

	dwm_dispway_mode_to_videomode(adjusted, &dsi->vm);
}

static void mtk_dsi_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					  stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct mtk_dsi *dsi = bwidge_to_dsi(bwidge);

	mtk_output_dsi_disabwe(dsi);
}

static void mtk_dsi_bwidge_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					 stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct mtk_dsi *dsi = bwidge_to_dsi(bwidge);

	if (dsi->wefcount == 0)
		wetuwn;

	mtk_output_dsi_enabwe(dsi);
}

static void mtk_dsi_bwidge_atomic_pwe_enabwe(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct mtk_dsi *dsi = bwidge_to_dsi(bwidge);
	int wet;

	wet = mtk_dsi_powewon(dsi);
	if (wet < 0)
		DWM_EWWOW("faiwed to powew on dsi\n");
}

static void mtk_dsi_bwidge_atomic_post_disabwe(stwuct dwm_bwidge *bwidge,
					       stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct mtk_dsi *dsi = bwidge_to_dsi(bwidge);

	mtk_dsi_powewoff(dsi);
}

static enum dwm_mode_status
mtk_dsi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			  const stwuct dwm_dispway_info *info,
			  const stwuct dwm_dispway_mode *mode)
{
	stwuct mtk_dsi *dsi = bwidge_to_dsi(bwidge);
	u32 bpp;

	if (dsi->fowmat == MIPI_DSI_FMT_WGB565)
		bpp = 16;
	ewse
		bpp = 24;

	if (mode->cwock * bpp / dsi->wanes > 1500000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_bwidge_funcs mtk_dsi_bwidge_funcs = {
	.attach = mtk_dsi_bwidge_attach,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_disabwe = mtk_dsi_bwidge_atomic_disabwe,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_enabwe = mtk_dsi_bwidge_atomic_enabwe,
	.atomic_pwe_enabwe = mtk_dsi_bwidge_atomic_pwe_enabwe,
	.atomic_post_disabwe = mtk_dsi_bwidge_atomic_post_disabwe,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.mode_vawid = mtk_dsi_bwidge_mode_vawid,
	.mode_set = mtk_dsi_bwidge_mode_set,
};

void mtk_dsi_ddp_stawt(stwuct device *dev)
{
	stwuct mtk_dsi *dsi = dev_get_dwvdata(dev);

	mtk_dsi_powewon(dsi);
}

void mtk_dsi_ddp_stop(stwuct device *dev)
{
	stwuct mtk_dsi *dsi = dev_get_dwvdata(dev);

	mtk_dsi_powewoff(dsi);
}

static int mtk_dsi_encodew_init(stwuct dwm_device *dwm, stwuct mtk_dsi *dsi)
{
	int wet;

	wet = dwm_simpwe_encodew_init(dwm, &dsi->encodew,
				      DWM_MODE_ENCODEW_DSI);
	if (wet) {
		DWM_EWWOW("Faiwed to encodew init to dwm\n");
		wetuwn wet;
	}

	dsi->encodew.possibwe_cwtcs = mtk_dwm_find_possibwe_cwtc_by_comp(dwm, dsi->host.dev);

	wet = dwm_bwidge_attach(&dsi->encodew, &dsi->bwidge, NUWW,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet)
		goto eww_cweanup_encodew;

	dsi->connectow = dwm_bwidge_connectow_init(dwm, &dsi->encodew);
	if (IS_EWW(dsi->connectow)) {
		DWM_EWWOW("Unabwe to cweate bwidge connectow\n");
		wet = PTW_EWW(dsi->connectow);
		goto eww_cweanup_encodew;
	}
	dwm_connectow_attach_encodew(dsi->connectow, &dsi->encodew);

	wetuwn 0;

eww_cweanup_encodew:
	dwm_encodew_cweanup(&dsi->encodew);
	wetuwn wet;
}

unsigned int mtk_dsi_encodew_index(stwuct device *dev)
{
	stwuct mtk_dsi *dsi = dev_get_dwvdata(dev);
	unsigned int encodew_index = dwm_encodew_index(&dsi->encodew);

	dev_dbg(dev, "encodew index:%d\n", encodew_index);
	wetuwn encodew_index;
}

static int mtk_dsi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	int wet;
	stwuct dwm_device *dwm = data;
	stwuct mtk_dsi *dsi = dev_get_dwvdata(dev);

	wet = mtk_dsi_encodew_init(dwm, dsi);
	if (wet)
		wetuwn wet;

	wetuwn device_weset_optionaw(dev);
}

static void mtk_dsi_unbind(stwuct device *dev, stwuct device *mastew,
			   void *data)
{
	stwuct mtk_dsi *dsi = dev_get_dwvdata(dev);

	dwm_encodew_cweanup(&dsi->encodew);
}

static const stwuct component_ops mtk_dsi_component_ops = {
	.bind = mtk_dsi_bind,
	.unbind = mtk_dsi_unbind,
};

static int mtk_dsi_host_attach(stwuct mipi_dsi_host *host,
			       stwuct mipi_dsi_device *device)
{
	stwuct mtk_dsi *dsi = host_to_dsi(host);
	stwuct device *dev = host->dev;
	int wet;

	dsi->wanes = device->wanes;
	dsi->fowmat = device->fowmat;
	dsi->mode_fwags = device->mode_fwags;
	dsi->next_bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 0, 0);
	if (IS_EWW(dsi->next_bwidge))
		wetuwn PTW_EWW(dsi->next_bwidge);

	dwm_bwidge_add(&dsi->bwidge);

	wet = component_add(host->dev, &mtk_dsi_component_ops);
	if (wet) {
		DWM_EWWOW("faiwed to add dsi_host component: %d\n", wet);
		dwm_bwidge_wemove(&dsi->bwidge);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mtk_dsi_host_detach(stwuct mipi_dsi_host *host,
			       stwuct mipi_dsi_device *device)
{
	stwuct mtk_dsi *dsi = host_to_dsi(host);

	component_dew(host->dev, &mtk_dsi_component_ops);
	dwm_bwidge_wemove(&dsi->bwidge);
	wetuwn 0;
}

static void mtk_dsi_wait_fow_idwe(stwuct mtk_dsi *dsi)
{
	int wet;
	u32 vaw;

	wet = weadw_poww_timeout(dsi->wegs + DSI_INTSTA, vaw, !(vaw & DSI_BUSY),
				 4, 2000000);
	if (wet) {
		DWM_WAWN("powwing dsi wait not busy timeout!\n");

		mtk_dsi_enabwe(dsi);
		mtk_dsi_weset_engine(dsi);
	}
}

static u32 mtk_dsi_wecv_cnt(u8 type, u8 *wead_data)
{
	switch (type) {
	case MIPI_DSI_WX_GENEWIC_SHOWT_WEAD_WESPONSE_1BYTE:
	case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_1BYTE:
		wetuwn 1;
	case MIPI_DSI_WX_GENEWIC_SHOWT_WEAD_WESPONSE_2BYTE:
	case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_2BYTE:
		wetuwn 2;
	case MIPI_DSI_WX_GENEWIC_WONG_WEAD_WESPONSE:
	case MIPI_DSI_WX_DCS_WONG_WEAD_WESPONSE:
		wetuwn wead_data[1] + wead_data[2] * 16;
	case MIPI_DSI_WX_ACKNOWWEDGE_AND_EWWOW_WEPOWT:
		DWM_INFO("type is 0x02, twy again\n");
		bweak;
	defauwt:
		DWM_INFO("type(0x%x) not wecognized\n", type);
		bweak;
	}

	wetuwn 0;
}

static void mtk_dsi_cmdq(stwuct mtk_dsi *dsi, const stwuct mipi_dsi_msg *msg)
{
	const chaw *tx_buf = msg->tx_buf;
	u8 config, cmdq_size, cmdq_off, type = msg->type;
	u32 weg_vaw, cmdq_mask, i;
	u32 weg_cmdq_off = dsi->dwivew_data->weg_cmdq_off;

	if (MTK_DSI_HOST_IS_WEAD(type))
		config = BTA;
	ewse
		config = (msg->tx_wen > 2) ? WONG_PACKET : SHOWT_PACKET;

	if (msg->tx_wen > 2) {
		cmdq_size = 1 + (msg->tx_wen + 3) / 4;
		cmdq_off = 4;
		cmdq_mask = CONFIG | DATA_ID | DATA_0 | DATA_1;
		weg_vaw = (msg->tx_wen << 16) | (type << 8) | config;
	} ewse {
		cmdq_size = 1;
		cmdq_off = 2;
		cmdq_mask = CONFIG | DATA_ID;
		weg_vaw = (type << 8) | config;
	}

	fow (i = 0; i < msg->tx_wen; i++)
		mtk_dsi_mask(dsi, (weg_cmdq_off + cmdq_off + i) & (~0x3U),
			     (0xffUW << (((i + cmdq_off) & 3U) * 8U)),
			     tx_buf[i] << (((i + cmdq_off) & 3U) * 8U));

	mtk_dsi_mask(dsi, weg_cmdq_off, cmdq_mask, weg_vaw);
	mtk_dsi_mask(dsi, DSI_CMDQ_SIZE, CMDQ_SIZE, cmdq_size);
	if (dsi->dwivew_data->cmdq_wong_packet_ctw) {
		/* Disabwe setting cmdq_size automaticawwy fow wong packets */
		mtk_dsi_mask(dsi, DSI_CMDQ_SIZE, CMDQ_SIZE_SEW, CMDQ_SIZE_SEW);
	}
}

static ssize_t mtk_dsi_host_send_cmd(stwuct mtk_dsi *dsi,
				     const stwuct mipi_dsi_msg *msg, u8 fwag)
{
	mtk_dsi_wait_fow_idwe(dsi);
	mtk_dsi_iwq_data_cweaw(dsi, fwag);
	mtk_dsi_cmdq(dsi, msg);
	mtk_dsi_stawt(dsi);

	if (!mtk_dsi_wait_fow_iwq_done(dsi, fwag, 2000))
		wetuwn -ETIME;
	ewse
		wetuwn 0;
}

static ssize_t mtk_dsi_host_twansfew(stwuct mipi_dsi_host *host,
				     const stwuct mipi_dsi_msg *msg)
{
	stwuct mtk_dsi *dsi = host_to_dsi(host);
	u32 wecv_cnt, i;
	u8 wead_data[16];
	void *swc_addw;
	u8 iwq_fwag = CMD_DONE_INT_FWAG;
	u32 dsi_mode;
	int wet;

	dsi_mode = weadw(dsi->wegs + DSI_MODE_CTWW);
	if (dsi_mode & MODE) {
		mtk_dsi_stop(dsi);
		wet = mtk_dsi_switch_to_cmd_mode(dsi, VM_DONE_INT_FWAG, 500);
		if (wet)
			goto westowe_dsi_mode;
	}

	if (MTK_DSI_HOST_IS_WEAD(msg->type))
		iwq_fwag |= WPWX_WD_WDY_INT_FWAG;

	mtk_dsi_wane_weady(dsi);

	wet = mtk_dsi_host_send_cmd(dsi, msg, iwq_fwag);
	if (wet)
		goto westowe_dsi_mode;

	if (!MTK_DSI_HOST_IS_WEAD(msg->type)) {
		wecv_cnt = 0;
		goto westowe_dsi_mode;
	}

	if (!msg->wx_buf) {
		DWM_EWWOW("dsi weceive buffew size may be NUWW\n");
		wet = -EINVAW;
		goto westowe_dsi_mode;
	}

	fow (i = 0; i < 16; i++)
		*(wead_data + i) = weadb(dsi->wegs + DSI_WX_DATA0 + i);

	wecv_cnt = mtk_dsi_wecv_cnt(wead_data[0], wead_data);

	if (wecv_cnt > 2)
		swc_addw = &wead_data[4];
	ewse
		swc_addw = &wead_data[1];

	if (wecv_cnt > 10)
		wecv_cnt = 10;

	if (wecv_cnt > msg->wx_wen)
		wecv_cnt = msg->wx_wen;

	if (wecv_cnt)
		memcpy(msg->wx_buf, swc_addw, wecv_cnt);

	DWM_INFO("dsi get %d byte data fwom the panew addwess(0x%x)\n",
		 wecv_cnt, *((u8 *)(msg->tx_buf)));

westowe_dsi_mode:
	if (dsi_mode & MODE) {
		mtk_dsi_set_mode(dsi);
		mtk_dsi_stawt(dsi);
	}

	wetuwn wet < 0 ? wet : wecv_cnt;
}

static const stwuct mipi_dsi_host_ops mtk_dsi_ops = {
	.attach = mtk_dsi_host_attach,
	.detach = mtk_dsi_host_detach,
	.twansfew = mtk_dsi_host_twansfew,
};

static int mtk_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_dsi *dsi;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wegs;
	int iwq_num;
	int wet;

	dsi = devm_kzawwoc(dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	dsi->host.ops = &mtk_dsi_ops;
	dsi->host.dev = dev;
	wet = mipi_dsi_host_wegistew(&dsi->host);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew DSI host: %d\n", wet);
		wetuwn wet;
	}

	dsi->dwivew_data = of_device_get_match_data(dev);

	dsi->engine_cwk = devm_cwk_get(dev, "engine");
	if (IS_EWW(dsi->engine_cwk)) {
		wet = PTW_EWW(dsi->engine_cwk);

		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get engine cwock: %d\n", wet);
		goto eww_unwegistew_host;
	}

	dsi->digitaw_cwk = devm_cwk_get(dev, "digitaw");
	if (IS_EWW(dsi->digitaw_cwk)) {
		wet = PTW_EWW(dsi->digitaw_cwk);

		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get digitaw cwock: %d\n", wet);
		goto eww_unwegistew_host;
	}

	dsi->hs_cwk = devm_cwk_get(dev, "hs");
	if (IS_EWW(dsi->hs_cwk)) {
		wet = PTW_EWW(dsi->hs_cwk);
		dev_eww(dev, "Faiwed to get hs cwock: %d\n", wet);
		goto eww_unwegistew_host;
	}

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	dsi->wegs = devm_iowemap_wesouwce(dev, wegs);
	if (IS_EWW(dsi->wegs)) {
		wet = PTW_EWW(dsi->wegs);
		dev_eww(dev, "Faiwed to iowemap memowy: %d\n", wet);
		goto eww_unwegistew_host;
	}

	dsi->phy = devm_phy_get(dev, "dphy");
	if (IS_EWW(dsi->phy)) {
		wet = PTW_EWW(dsi->phy);
		dev_eww(dev, "Faiwed to get MIPI-DPHY: %d\n", wet);
		goto eww_unwegistew_host;
	}

	iwq_num = pwatfowm_get_iwq(pdev, 0);
	if (iwq_num < 0) {
		wet = iwq_num;
		goto eww_unwegistew_host;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq_num, mtk_dsi_iwq,
			       IWQF_TWIGGEW_NONE, dev_name(&pdev->dev), dsi);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest mediatek dsi iwq\n");
		goto eww_unwegistew_host;
	}

	init_waitqueue_head(&dsi->iwq_wait_queue);

	pwatfowm_set_dwvdata(pdev, dsi);

	dsi->bwidge.funcs = &mtk_dsi_bwidge_funcs;
	dsi->bwidge.of_node = dev->of_node;
	dsi->bwidge.type = DWM_MODE_CONNECTOW_DSI;

	wetuwn 0;

eww_unwegistew_host:
	mipi_dsi_host_unwegistew(&dsi->host);
	wetuwn wet;
}

static void mtk_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_dsi *dsi = pwatfowm_get_dwvdata(pdev);

	mtk_output_dsi_disabwe(dsi);
	mipi_dsi_host_unwegistew(&dsi->host);
}

static const stwuct mtk_dsi_dwivew_data mt8173_dsi_dwivew_data = {
	.weg_cmdq_off = 0x200,
};

static const stwuct mtk_dsi_dwivew_data mt2701_dsi_dwivew_data = {
	.weg_cmdq_off = 0x180,
};

static const stwuct mtk_dsi_dwivew_data mt8183_dsi_dwivew_data = {
	.weg_cmdq_off = 0x200,
	.has_shadow_ctw = twue,
	.has_size_ctw = twue,
};

static const stwuct mtk_dsi_dwivew_data mt8186_dsi_dwivew_data = {
	.weg_cmdq_off = 0xd00,
	.has_shadow_ctw = twue,
	.has_size_ctw = twue,
};

static const stwuct mtk_dsi_dwivew_data mt8188_dsi_dwivew_data = {
	.weg_cmdq_off = 0xd00,
	.has_shadow_ctw = twue,
	.has_size_ctw = twue,
	.cmdq_wong_packet_ctw = twue,
};

static const stwuct of_device_id mtk_dsi_of_match[] = {
	{ .compatibwe = "mediatek,mt2701-dsi",
	  .data = &mt2701_dsi_dwivew_data },
	{ .compatibwe = "mediatek,mt8173-dsi",
	  .data = &mt8173_dsi_dwivew_data },
	{ .compatibwe = "mediatek,mt8183-dsi",
	  .data = &mt8183_dsi_dwivew_data },
	{ .compatibwe = "mediatek,mt8186-dsi",
	  .data = &mt8186_dsi_dwivew_data },
	{ .compatibwe = "mediatek,mt8188-dsi",
	  .data = &mt8188_dsi_dwivew_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, mtk_dsi_of_match);

stwuct pwatfowm_dwivew mtk_dsi_dwivew = {
	.pwobe = mtk_dsi_pwobe,
	.wemove_new = mtk_dsi_wemove,
	.dwivew = {
		.name = "mtk-dsi",
		.of_match_tabwe = mtk_dsi_of_match,
	},
};
