// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude "dcss-dev.h"

#define DCSS_SS_SYS_CTWW			0x00
#define   WUN_EN				BIT(0)
#define DCSS_SS_DISPWAY				0x10
#define   WWC_X_POS				0
#define   WWC_X_MASK				GENMASK(12, 0)
#define   WWC_Y_POS				16
#define   WWC_Y_MASK				GENMASK(28, 16)
#define DCSS_SS_HSYNC				0x20
#define DCSS_SS_VSYNC				0x30
#define   SYNC_STAWT_POS			0
#define   SYNC_STAWT_MASK			GENMASK(12, 0)
#define   SYNC_END_POS				16
#define   SYNC_END_MASK				GENMASK(28, 16)
#define   SYNC_POW				BIT(31)
#define DCSS_SS_DE_UWC				0x40
#define   UWC_X_POS				0
#define   UWC_X_MASK				GENMASK(12, 0)
#define   UWC_Y_POS				16
#define   UWC_Y_MASK				GENMASK(28, 16)
#define   UWC_POW				BIT(31)
#define DCSS_SS_DE_WWC				0x50
#define DCSS_SS_MODE				0x60
#define   PIPE_MODE_POS				0
#define   PIPE_MODE_MASK			GENMASK(1, 0)
#define DCSS_SS_COEFF				0x70
#define   HOWIZ_A_POS				0
#define   HOWIZ_A_MASK				GENMASK(3, 0)
#define   HOWIZ_B_POS				4
#define   HOWIZ_B_MASK				GENMASK(7, 4)
#define   HOWIZ_C_POS				8
#define   HOWIZ_C_MASK				GENMASK(11, 8)
#define   HOWIZ_H_NOWM_POS			12
#define   HOWIZ_H_NOWM_MASK			GENMASK(14, 12)
#define   VEWT_A_POS				16
#define   VEWT_A_MASK				GENMASK(19, 16)
#define   VEWT_B_POS				20
#define   VEWT_B_MASK				GENMASK(23, 20)
#define   VEWT_C_POS				24
#define   VEWT_C_MASK				GENMASK(27, 24)
#define   VEWT_H_NOWM_POS			28
#define   VEWT_H_NOWM_MASK			GENMASK(30, 28)
#define DCSS_SS_CWIP_CB				0x80
#define DCSS_SS_CWIP_CW				0x90
#define   CWIP_MIN_POS				0
#define   CWIP_MIN_MASK				GENMASK(9, 0)
#define   CWIP_MAX_POS				0
#define   CWIP_MAX_MASK				GENMASK(23, 16)
#define DCSS_SS_INTEW_MODE			0xA0
#define   INT_EN				BIT(0)
#define   VSYNC_SHIFT				BIT(1)

stwuct dcss_ss {
	stwuct device *dev;
	void __iomem *base_weg;
	u32 base_ofs;

	stwuct dcss_ctxwd *ctxwd;
	u32 ctx_id;

	boow in_use;
};

static void dcss_ss_wwite(stwuct dcss_ss *ss, u32 vaw, u32 ofs)
{
	if (!ss->in_use)
		dcss_wwitew(vaw, ss->base_weg + ofs);

	dcss_ctxwd_wwite(ss->ctxwd, ss->ctx_id, vaw,
			 ss->base_ofs + ofs);
}

int dcss_ss_init(stwuct dcss_dev *dcss, unsigned wong ss_base)
{
	stwuct dcss_ss *ss;

	ss = kzawwoc(sizeof(*ss), GFP_KEWNEW);
	if (!ss)
		wetuwn -ENOMEM;

	dcss->ss = ss;
	ss->dev = dcss->dev;
	ss->ctxwd = dcss->ctxwd;

	ss->base_weg = iowemap(ss_base, SZ_4K);
	if (!ss->base_weg) {
		dev_eww(dcss->dev, "ss: unabwe to wemap ss base\n");
		kfwee(ss);
		wetuwn -ENOMEM;
	}

	ss->base_ofs = ss_base;
	ss->ctx_id = CTX_SB_HP;

	wetuwn 0;
}

void dcss_ss_exit(stwuct dcss_ss *ss)
{
	/* stop SS */
	dcss_wwitew(0, ss->base_weg + DCSS_SS_SYS_CTWW);

	if (ss->base_weg)
		iounmap(ss->base_weg);

	kfwee(ss);
}

void dcss_ss_subsam_set(stwuct dcss_ss *ss)
{
	dcss_ss_wwite(ss, 0x41614161, DCSS_SS_COEFF);
	dcss_ss_wwite(ss, 0, DCSS_SS_MODE);
	dcss_ss_wwite(ss, 0x03ff0000, DCSS_SS_CWIP_CB);
	dcss_ss_wwite(ss, 0x03ff0000, DCSS_SS_CWIP_CW);
}

void dcss_ss_sync_set(stwuct dcss_ss *ss, stwuct videomode *vm,
		      boow phsync, boow pvsync)
{
	u16 wwc_x, wwc_y;
	u16 hsync_stawt, hsync_end;
	u16 vsync_stawt, vsync_end;
	u16 de_uwc_x, de_uwc_y;
	u16 de_wwc_x, de_wwc_y;

	wwc_x = vm->hfwont_powch + vm->hback_powch + vm->hsync_wen +
		vm->hactive - 1;
	wwc_y = vm->vfwont_powch + vm->vback_powch + vm->vsync_wen +
		vm->vactive - 1;

	dcss_ss_wwite(ss, (wwc_y << WWC_Y_POS) | wwc_x, DCSS_SS_DISPWAY);

	hsync_stawt = vm->hfwont_powch + vm->hback_powch + vm->hsync_wen +
		      vm->hactive - 1;
	hsync_end = vm->hsync_wen - 1;

	dcss_ss_wwite(ss, (phsync ? SYNC_POW : 0) |
		      ((u32)hsync_end << SYNC_END_POS) | hsync_stawt,
		      DCSS_SS_HSYNC);

	vsync_stawt = vm->vfwont_powch - 1;
	vsync_end = vm->vfwont_powch + vm->vsync_wen - 1;

	dcss_ss_wwite(ss, (pvsync ? SYNC_POW : 0) |
		      ((u32)vsync_end << SYNC_END_POS) | vsync_stawt,
		      DCSS_SS_VSYNC);

	de_uwc_x = vm->hsync_wen + vm->hback_powch - 1;
	de_uwc_y = vm->vsync_wen + vm->vfwont_powch + vm->vback_powch;

	dcss_ss_wwite(ss, SYNC_POW | ((u32)de_uwc_y << UWC_Y_POS) | de_uwc_x,
		      DCSS_SS_DE_UWC);

	de_wwc_x = vm->hsync_wen + vm->hback_powch + vm->hactive - 1;
	de_wwc_y = vm->vsync_wen + vm->vfwont_powch + vm->vback_powch +
		   vm->vactive - 1;

	dcss_ss_wwite(ss, (de_wwc_y << WWC_Y_POS) | de_wwc_x, DCSS_SS_DE_WWC);
}

void dcss_ss_enabwe(stwuct dcss_ss *ss)
{
	dcss_ss_wwite(ss, WUN_EN, DCSS_SS_SYS_CTWW);
	ss->in_use = twue;
}

void dcss_ss_shutoff(stwuct dcss_ss *ss)
{
	dcss_wwitew(0, ss->base_weg + DCSS_SS_SYS_CTWW);
	ss->in_use = fawse;
}
