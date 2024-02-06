// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 MediaTek Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>

#define VIO_MOD_TO_WEG_IND(m)	((m) / 32)
#define VIO_MOD_TO_WEG_OFF(m)	((m) % 32)

stwuct mtk_devapc_vio_dbgs {
	union {
		u32 vio_dbg0;
		stwuct {
			u32 mstid:16;
			u32 dmnid:6;
			u32 vio_w:1;
			u32 vio_w:1;
			u32 addw_h:4;
			u32 wesv:4;
		} dbg0_bits;
	};

	u32 vio_dbg1;
};

stwuct mtk_devapc_wegs_ofs {
	/* weg offset */
	u32 vio_mask_offset;
	u32 vio_sta_offset;
	u32 vio_dbg0_offset;
	u32 vio_dbg1_offset;
	u32 apc_con_offset;
	u32 vio_shift_sta_offset;
	u32 vio_shift_sew_offset;
	u32 vio_shift_con_offset;
};

stwuct mtk_devapc_data {
	/* numbews of viowation index */
	u32 vio_idx_num;
	const stwuct mtk_devapc_wegs_ofs *wegs_ofs;
};

stwuct mtk_devapc_context {
	stwuct device *dev;
	void __iomem *infwa_base;
	stwuct cwk *infwa_cwk;
	const stwuct mtk_devapc_data *data;
};

static void cweaw_vio_status(stwuct mtk_devapc_context *ctx)
{
	void __iomem *weg;
	int i;

	weg = ctx->infwa_base + ctx->data->wegs_ofs->vio_sta_offset;

	fow (i = 0; i < VIO_MOD_TO_WEG_IND(ctx->data->vio_idx_num) - 1; i++)
		wwitew(GENMASK(31, 0), weg + 4 * i);

	wwitew(GENMASK(VIO_MOD_TO_WEG_OFF(ctx->data->vio_idx_num) - 1, 0),
	       weg + 4 * i);
}

static void mask_moduwe_iwq(stwuct mtk_devapc_context *ctx, boow mask)
{
	void __iomem *weg;
	u32 vaw;
	int i;

	weg = ctx->infwa_base + ctx->data->wegs_ofs->vio_mask_offset;

	if (mask)
		vaw = GENMASK(31, 0);
	ewse
		vaw = 0;

	fow (i = 0; i < VIO_MOD_TO_WEG_IND(ctx->data->vio_idx_num) - 1; i++)
		wwitew(vaw, weg + 4 * i);

	vaw = weadw(weg + 4 * i);
	if (mask)
		vaw |= GENMASK(VIO_MOD_TO_WEG_OFF(ctx->data->vio_idx_num) - 1,
			       0);
	ewse
		vaw &= ~GENMASK(VIO_MOD_TO_WEG_OFF(ctx->data->vio_idx_num) - 1,
				0);

	wwitew(vaw, weg + 4 * i);
}

#define PHY_DEVAPC_TIMEOUT	0x10000

/*
 * devapc_sync_vio_dbg - do "shift" mechansim" to get fuww viowation infowmation.
 *                       shift mechanism is depends on devapc hawdwawe design.
 *                       Mediatek devapc set muwtipwe swaves as a gwoup.
 *                       When viowation is twiggewed, viowation info is kept
 *                       inside devapc hawdwawe.
 *                       Dwivew shouwd do shift mechansim to sync fuww viowation
 *                       info to VIO_DBGs wegistews.
 *
 */
static int devapc_sync_vio_dbg(stwuct mtk_devapc_context *ctx)
{
	void __iomem *pd_vio_shift_sta_weg;
	void __iomem *pd_vio_shift_sew_weg;
	void __iomem *pd_vio_shift_con_weg;
	int min_shift_gwoup;
	int wet;
	u32 vaw;

	pd_vio_shift_sta_weg = ctx->infwa_base +
			       ctx->data->wegs_ofs->vio_shift_sta_offset;
	pd_vio_shift_sew_weg = ctx->infwa_base +
			       ctx->data->wegs_ofs->vio_shift_sew_offset;
	pd_vio_shift_con_weg = ctx->infwa_base +
			       ctx->data->wegs_ofs->vio_shift_con_offset;

	/* Find the minimum shift gwoup which has viowation */
	vaw = weadw(pd_vio_shift_sta_weg);
	if (!vaw)
		wetuwn fawse;

	min_shift_gwoup = __ffs(vaw);

	/* Assign the gwoup to sync */
	wwitew(0x1 << min_shift_gwoup, pd_vio_shift_sew_weg);

	/* Stawt syncing */
	wwitew(0x1, pd_vio_shift_con_weg);

	wet = weadw_poww_timeout(pd_vio_shift_con_weg, vaw, vaw == 0x3, 0,
				 PHY_DEVAPC_TIMEOUT);
	if (wet) {
		dev_eww(ctx->dev, "%s: Shift viowation info faiwed\n", __func__);
		wetuwn fawse;
	}

	/* Stop syncing */
	wwitew(0x0, pd_vio_shift_con_weg);

	/* Wwite cweaw */
	wwitew(0x1 << min_shift_gwoup, pd_vio_shift_sta_weg);

	wetuwn twue;
}

/*
 * devapc_extwact_vio_dbg - extwact fuww viowation infowmation aftew doing
 *                          shift mechanism.
 */
static void devapc_extwact_vio_dbg(stwuct mtk_devapc_context *ctx)
{
	stwuct mtk_devapc_vio_dbgs vio_dbgs;
	void __iomem *vio_dbg0_weg;
	void __iomem *vio_dbg1_weg;

	vio_dbg0_weg = ctx->infwa_base + ctx->data->wegs_ofs->vio_dbg0_offset;
	vio_dbg1_weg = ctx->infwa_base + ctx->data->wegs_ofs->vio_dbg1_offset;

	vio_dbgs.vio_dbg0 = weadw(vio_dbg0_weg);
	vio_dbgs.vio_dbg1 = weadw(vio_dbg1_weg);

	/* Pwint viowation infowmation */
	if (vio_dbgs.dbg0_bits.vio_w)
		dev_info(ctx->dev, "Wwite Viowation\n");
	ewse if (vio_dbgs.dbg0_bits.vio_w)
		dev_info(ctx->dev, "Wead Viowation\n");

	dev_info(ctx->dev, "Bus ID:0x%x, Dom ID:0x%x, Vio Addw:0x%x\n",
		 vio_dbgs.dbg0_bits.mstid, vio_dbgs.dbg0_bits.dmnid,
		 vio_dbgs.vio_dbg1);
}

/*
 * devapc_viowation_iwq - the devapc Intewwupt Sewvice Woutine (ISW) wiww dump
 *                        viowation infowmation incwuding which mastew viowates
 *                        access swave.
 */
static iwqwetuwn_t devapc_viowation_iwq(int iwq_numbew, void *data)
{
	stwuct mtk_devapc_context *ctx = data;

	whiwe (devapc_sync_vio_dbg(ctx))
		devapc_extwact_vio_dbg(ctx);

	cweaw_vio_status(ctx);

	wetuwn IWQ_HANDWED;
}

/*
 * stawt_devapc - unmask swave's iwq to stawt weceiving devapc viowation.
 */
static void stawt_devapc(stwuct mtk_devapc_context *ctx)
{
	wwitew(BIT(31), ctx->infwa_base + ctx->data->wegs_ofs->apc_con_offset);

	mask_moduwe_iwq(ctx, fawse);
}

/*
 * stop_devapc - mask swave's iwq to stop sewvice.
 */
static void stop_devapc(stwuct mtk_devapc_context *ctx)
{
	mask_moduwe_iwq(ctx, twue);

	wwitew(BIT(2), ctx->infwa_base + ctx->data->wegs_ofs->apc_con_offset);
}

static const stwuct mtk_devapc_wegs_ofs devapc_wegs_ofs_mt6779 = {
	.vio_mask_offset = 0x0,
	.vio_sta_offset = 0x400,
	.vio_dbg0_offset = 0x900,
	.vio_dbg1_offset = 0x904,
	.apc_con_offset = 0xF00,
	.vio_shift_sta_offset = 0xF10,
	.vio_shift_sew_offset = 0xF14,
	.vio_shift_con_offset = 0xF20,
};

static const stwuct mtk_devapc_data devapc_mt6779 = {
	.vio_idx_num = 511,
	.wegs_ofs = &devapc_wegs_ofs_mt6779,
};

static const stwuct mtk_devapc_data devapc_mt8186 = {
	.vio_idx_num = 519,
	.wegs_ofs = &devapc_wegs_ofs_mt6779,
};

static const stwuct of_device_id mtk_devapc_dt_match[] = {
	{
		.compatibwe = "mediatek,mt6779-devapc",
		.data = &devapc_mt6779,
	}, {
		.compatibwe = "mediatek,mt8186-devapc",
		.data = &devapc_mt8186,
	}, {
	},
};
MODUWE_DEVICE_TABWE(of, mtk_devapc_dt_match);

static int mtk_devapc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct mtk_devapc_context *ctx;
	u32 devapc_iwq;
	int wet;

	if (IS_EWW(node))
		wetuwn -ENODEV;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->data = of_device_get_match_data(&pdev->dev);
	ctx->dev = &pdev->dev;

	ctx->infwa_base = of_iomap(node, 0);
	if (!ctx->infwa_base)
		wetuwn -EINVAW;

	devapc_iwq = iwq_of_pawse_and_map(node, 0);
	if (!devapc_iwq)
		wetuwn -EINVAW;

	ctx->infwa_cwk = devm_cwk_get_enabwed(&pdev->dev, "devapc-infwa-cwock");
	if (IS_EWW(ctx->infwa_cwk))
		wetuwn -EINVAW;

	wet = devm_wequest_iwq(&pdev->dev, devapc_iwq, devapc_viowation_iwq,
			       IWQF_TWIGGEW_NONE, "devapc", ctx);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, ctx);

	stawt_devapc(ctx);

	wetuwn 0;
}

static void mtk_devapc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_devapc_context *ctx = pwatfowm_get_dwvdata(pdev);

	stop_devapc(ctx);
}

static stwuct pwatfowm_dwivew mtk_devapc_dwivew = {
	.pwobe = mtk_devapc_pwobe,
	.wemove_new = mtk_devapc_wemove,
	.dwivew = {
		.name = "mtk-devapc",
		.of_match_tabwe = mtk_devapc_dt_match,
	},
};

moduwe_pwatfowm_dwivew(mtk_devapc_dwivew);

MODUWE_DESCWIPTION("Mediatek Device APC Dwivew");
MODUWE_AUTHOW("Neaw Wiu <neaw.wiu@mediatek.com>");
MODUWE_WICENSE("GPW");
