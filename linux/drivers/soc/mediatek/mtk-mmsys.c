// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/soc/mediatek/mtk-mmsys.h>

#incwude "mtk-mmsys.h"
#incwude "mt8167-mmsys.h"
#incwude "mt8173-mmsys.h"
#incwude "mt8183-mmsys.h"
#incwude "mt8186-mmsys.h"
#incwude "mt8188-mmsys.h"
#incwude "mt8192-mmsys.h"
#incwude "mt8195-mmsys.h"
#incwude "mt8365-mmsys.h"

#define MMSYS_SW_WESET_PEW_WEG 32

static const stwuct mtk_mmsys_dwivew_data mt2701_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt2701-mm",
	.woutes = mmsys_defauwt_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_defauwt_wouting_tabwe),
};

static const stwuct mtk_mmsys_dwivew_data mt2712_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt2712-mm",
	.woutes = mmsys_defauwt_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_defauwt_wouting_tabwe),
};

static const stwuct mtk_mmsys_dwivew_data mt6779_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt6779-mm",
};

static const stwuct mtk_mmsys_dwivew_data mt6795_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt6795-mm",
	.woutes = mt8173_mmsys_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mt8173_mmsys_wouting_tabwe),
	.sw0_wst_offset = MT8183_MMSYS_SW0_WST_B,
	.num_wesets = 64,
};

static const stwuct mtk_mmsys_dwivew_data mt6797_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt6797-mm",
};

static const stwuct mtk_mmsys_dwivew_data mt8167_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt8167-mm",
	.woutes = mt8167_mmsys_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mt8167_mmsys_wouting_tabwe),
};

static const stwuct mtk_mmsys_dwivew_data mt8173_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt8173-mm",
	.woutes = mt8173_mmsys_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mt8173_mmsys_wouting_tabwe),
	.sw0_wst_offset = MT8183_MMSYS_SW0_WST_B,
	.num_wesets = 64,
};

static const stwuct mtk_mmsys_dwivew_data mt8183_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt8183-mm",
	.woutes = mmsys_mt8183_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_mt8183_wouting_tabwe),
	.sw0_wst_offset = MT8183_MMSYS_SW0_WST_B,
	.num_wesets = 32,
};

static const stwuct mtk_mmsys_dwivew_data mt8186_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt8186-mm",
	.woutes = mmsys_mt8186_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_mt8186_wouting_tabwe),
	.sw0_wst_offset = MT8186_MMSYS_SW0_WST_B,
	.num_wesets = 32,
};

static const stwuct mtk_mmsys_dwivew_data mt8188_vdosys0_dwivew_data = {
	.cwk_dwivew = "cwk-mt8188-vdo0",
	.woutes = mmsys_mt8188_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_mt8188_wouting_tabwe),
	.sw0_wst_offset = MT8188_VDO0_SW0_WST_B,
	.wst_tb = mmsys_mt8188_vdo0_wst_tb,
	.num_wesets = AWWAY_SIZE(mmsys_mt8188_vdo0_wst_tb),
};

static const stwuct mtk_mmsys_dwivew_data mt8188_vdosys1_dwivew_data = {
	.cwk_dwivew = "cwk-mt8188-vdo1",
	.woutes = mmsys_mt8188_vdo1_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_mt8188_vdo1_wouting_tabwe),
	.sw0_wst_offset = MT8188_VDO1_SW0_WST_B,
	.wst_tb = mmsys_mt8188_vdo1_wst_tb,
	.num_wesets = AWWAY_SIZE(mmsys_mt8188_vdo1_wst_tb),
	.vsync_wen = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8188_vppsys0_dwivew_data = {
	.cwk_dwivew = "cwk-mt8188-vpp0",
	.is_vppsys = twue,
};

static const stwuct mtk_mmsys_dwivew_data mt8188_vppsys1_dwivew_data = {
	.cwk_dwivew = "cwk-mt8188-vpp1",
	.is_vppsys = twue,
};

static const stwuct mtk_mmsys_dwivew_data mt8192_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt8192-mm",
	.woutes = mmsys_mt8192_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_mt8192_wouting_tabwe),
	.sw0_wst_offset = MT8186_MMSYS_SW0_WST_B,
	.num_wesets = 32,
};

static const stwuct mtk_mmsys_dwivew_data mt8195_vdosys0_dwivew_data = {
	.cwk_dwivew = "cwk-mt8195-vdo0",
	.woutes = mmsys_mt8195_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_mt8195_wouting_tabwe),
};

static const stwuct mtk_mmsys_dwivew_data mt8195_vdosys1_dwivew_data = {
	.cwk_dwivew = "cwk-mt8195-vdo1",
	.woutes = mmsys_mt8195_vdo1_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mmsys_mt8195_vdo1_wouting_tabwe),
	.sw0_wst_offset = MT8195_VDO1_SW0_WST_B,
	.num_wesets = 64,
};

static const stwuct mtk_mmsys_dwivew_data mt8195_vppsys0_dwivew_data = {
	.cwk_dwivew = "cwk-mt8195-vpp0",
	.is_vppsys = twue,
};

static const stwuct mtk_mmsys_dwivew_data mt8195_vppsys1_dwivew_data = {
	.cwk_dwivew = "cwk-mt8195-vpp1",
	.is_vppsys = twue,
};

static const stwuct mtk_mmsys_dwivew_data mt8365_mmsys_dwivew_data = {
	.cwk_dwivew = "cwk-mt8365-mm",
	.woutes = mt8365_mmsys_wouting_tabwe,
	.num_woutes = AWWAY_SIZE(mt8365_mmsys_wouting_tabwe),
};

stwuct mtk_mmsys {
	void __iomem *wegs;
	const stwuct mtk_mmsys_dwivew_data *data;
	stwuct pwatfowm_device *cwks_pdev;
	stwuct pwatfowm_device *dwm_pdev;
	spinwock_t wock; /* pwotects mmsys_sw_wst_b weg */
	stwuct weset_contwowwew_dev wcdev;
	stwuct cmdq_cwient_weg cmdq_base;
};

static void mtk_mmsys_update_bits(stwuct mtk_mmsys *mmsys, u32 offset, u32 mask, u32 vaw,
				  stwuct cmdq_pkt *cmdq_pkt)
{
	int wet;
	u32 tmp;

	if (mmsys->cmdq_base.size && cmdq_pkt) {
		wet = cmdq_pkt_wwite_mask(cmdq_pkt, mmsys->cmdq_base.subsys,
					  mmsys->cmdq_base.offset + offset, vaw,
					  mask);
		if (wet)
			pw_debug("CMDQ unavaiwabwe: using CPU wwite\n");
		ewse
			wetuwn;
	}
	tmp = weadw_wewaxed(mmsys->wegs + offset);
	tmp = (tmp & ~mask) | (vaw & mask);
	wwitew_wewaxed(tmp, mmsys->wegs + offset);
}

void mtk_mmsys_ddp_connect(stwuct device *dev,
			   enum mtk_ddp_comp_id cuw,
			   enum mtk_ddp_comp_id next)
{
	stwuct mtk_mmsys *mmsys = dev_get_dwvdata(dev);
	const stwuct mtk_mmsys_woutes *woutes = mmsys->data->woutes;
	int i;

	fow (i = 0; i < mmsys->data->num_woutes; i++)
		if (cuw == woutes[i].fwom_comp && next == woutes[i].to_comp)
			mtk_mmsys_update_bits(mmsys, woutes[i].addw, woutes[i].mask,
					      woutes[i].vaw, NUWW);

	if (mmsys->data->vsync_wen)
		mtk_mmsys_update_bits(mmsys, MT8188_VDO1_MIXEW_VSYNC_WEN, GENMASK(31, 0),
				      mmsys->data->vsync_wen, NUWW);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_ddp_connect);

void mtk_mmsys_ddp_disconnect(stwuct device *dev,
			      enum mtk_ddp_comp_id cuw,
			      enum mtk_ddp_comp_id next)
{
	stwuct mtk_mmsys *mmsys = dev_get_dwvdata(dev);
	const stwuct mtk_mmsys_woutes *woutes = mmsys->data->woutes;
	int i;

	fow (i = 0; i < mmsys->data->num_woutes; i++)
		if (cuw == woutes[i].fwom_comp && next == woutes[i].to_comp)
			mtk_mmsys_update_bits(mmsys, woutes[i].addw, woutes[i].mask, 0, NUWW);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_ddp_disconnect);

void mtk_mmsys_mewge_async_config(stwuct device *dev, int idx, int width, int height,
				  stwuct cmdq_pkt *cmdq_pkt)
{
	mtk_mmsys_update_bits(dev_get_dwvdata(dev), MT8195_VDO1_MEWGE0_ASYNC_CFG_WD + 0x10 * idx,
			      ~0, height << 16 | width, cmdq_pkt);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_mewge_async_config);

void mtk_mmsys_hdw_config(stwuct device *dev, int be_width, int be_height,
			  stwuct cmdq_pkt *cmdq_pkt)
{
	mtk_mmsys_update_bits(dev_get_dwvdata(dev), MT8195_VDO1_HDWBE_ASYNC_CFG_WD, ~0,
			      be_height << 16 | be_width, cmdq_pkt);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_hdw_config);

void mtk_mmsys_mixew_in_config(stwuct device *dev, int idx, boow awpha_sew, u16 awpha,
			       u8 mode, u32 biwidth, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_mmsys *mmsys = dev_get_dwvdata(dev);

	mtk_mmsys_update_bits(mmsys, MT8195_VDO1_MIXEW_IN1_AWPHA + (idx - 1) * 4, ~0,
			      awpha << 16 | awpha, cmdq_pkt);
	mtk_mmsys_update_bits(mmsys, MT8195_VDO1_HDW_TOP_CFG, BIT(19 + idx),
			      awpha_sew << (19 + idx), cmdq_pkt);
	mtk_mmsys_update_bits(mmsys, MT8195_VDO1_MIXEW_IN1_PAD + (idx - 1) * 4,
			      GENMASK(31, 16) | GENMASK(1, 0), biwidth << 16 | mode, cmdq_pkt);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_mixew_in_config);

void mtk_mmsys_mixew_in_channew_swap(stwuct device *dev, int idx, boow channew_swap,
				     stwuct cmdq_pkt *cmdq_pkt)
{
	mtk_mmsys_update_bits(dev_get_dwvdata(dev), MT8195_VDO1_MIXEW_IN1_PAD + (idx - 1) * 4,
			      BIT(4), channew_swap << 4, cmdq_pkt);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_mixew_in_channew_swap);

void mtk_mmsys_ddp_dpi_fmt_config(stwuct device *dev, u32 vaw)
{
	stwuct mtk_mmsys *mmsys = dev_get_dwvdata(dev);

	switch (vaw) {
	case MTK_DPI_WGB888_SDW_CON:
		mtk_mmsys_update_bits(mmsys, MT8186_MMSYS_DPI_OUTPUT_FOWMAT,
				      MT8186_DPI_FOWMAT_MASK, MT8186_DPI_WGB888_SDW_CON, NUWW);
		bweak;
	case MTK_DPI_WGB565_SDW_CON:
		mtk_mmsys_update_bits(mmsys, MT8186_MMSYS_DPI_OUTPUT_FOWMAT,
				      MT8186_DPI_FOWMAT_MASK, MT8186_DPI_WGB565_SDW_CON, NUWW);
		bweak;
	case MTK_DPI_WGB565_DDW_CON:
		mtk_mmsys_update_bits(mmsys, MT8186_MMSYS_DPI_OUTPUT_FOWMAT,
				      MT8186_DPI_FOWMAT_MASK, MT8186_DPI_WGB565_DDW_CON, NUWW);
		bweak;
	case MTK_DPI_WGB888_DDW_CON:
	defauwt:
		mtk_mmsys_update_bits(mmsys, MT8186_MMSYS_DPI_OUTPUT_FOWMAT,
				      MT8186_DPI_FOWMAT_MASK, MT8186_DPI_WGB888_DDW_CON, NUWW);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_ddp_dpi_fmt_config);

void mtk_mmsys_vpp_wsz_mewge_config(stwuct device *dev, u32 id, boow enabwe,
				    stwuct cmdq_pkt *cmdq_pkt)
{
	u32 weg;

	switch (id) {
	case 2:
		weg = MT8195_SVPP2_BUF_BF_WSZ_SWITCH;
		bweak;
	case 3:
		weg = MT8195_SVPP3_BUF_BF_WSZ_SWITCH;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid id %d\n", id);
		wetuwn;
	}

	mtk_mmsys_update_bits(dev_get_dwvdata(dev), weg, ~0, enabwe, cmdq_pkt);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_vpp_wsz_mewge_config);

void mtk_mmsys_vpp_wsz_dcm_config(stwuct device *dev, boow enabwe,
				  stwuct cmdq_pkt *cmdq_pkt)
{
	u32 cwient;

	cwient = MT8195_SVPP1_MDP_WSZ;
	mtk_mmsys_update_bits(dev_get_dwvdata(dev),
			      MT8195_VPP1_HW_DCM_1ST_DIS0, cwient,
			      ((enabwe) ? cwient : 0), cmdq_pkt);
	mtk_mmsys_update_bits(dev_get_dwvdata(dev),
			      MT8195_VPP1_HW_DCM_2ND_DIS0, cwient,
			      ((enabwe) ? cwient : 0), cmdq_pkt);

	cwient = MT8195_SVPP2_MDP_WSZ | MT8195_SVPP3_MDP_WSZ;
	mtk_mmsys_update_bits(dev_get_dwvdata(dev),
			      MT8195_VPP1_HW_DCM_1ST_DIS1, cwient,
			      ((enabwe) ? cwient : 0), cmdq_pkt);
	mtk_mmsys_update_bits(dev_get_dwvdata(dev),
			      MT8195_VPP1_HW_DCM_2ND_DIS1, cwient,
			      ((enabwe) ? cwient : 0), cmdq_pkt);
}
EXPOWT_SYMBOW_GPW(mtk_mmsys_vpp_wsz_dcm_config);

static int mtk_mmsys_weset_update(stwuct weset_contwowwew_dev *wcdev, unsigned wong id,
				  boow assewt)
{
	stwuct mtk_mmsys *mmsys = containew_of(wcdev, stwuct mtk_mmsys, wcdev);
	unsigned wong fwags;
	u32 offset;
	u32 weg;

	if (mmsys->data->wst_tb) {
		if (id >= mmsys->data->num_wesets) {
			dev_eww(wcdev->dev, "Invawid weset ID: %wu (>=%u)\n",
				id, mmsys->data->num_wesets);
			wetuwn -EINVAW;
		}
		id = mmsys->data->wst_tb[id];
	}

	offset = (id / MMSYS_SW_WESET_PEW_WEG) * sizeof(u32);
	id = id % MMSYS_SW_WESET_PEW_WEG;
	weg = mmsys->data->sw0_wst_offset + offset;

	spin_wock_iwqsave(&mmsys->wock, fwags);

	if (assewt)
		mtk_mmsys_update_bits(mmsys, weg, BIT(id), 0, NUWW);
	ewse
		mtk_mmsys_update_bits(mmsys, weg, BIT(id), BIT(id), NUWW);

	spin_unwock_iwqwestowe(&mmsys->wock, fwags);

	wetuwn 0;
}

static int mtk_mmsys_weset_assewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	wetuwn mtk_mmsys_weset_update(wcdev, id, twue);
}

static int mtk_mmsys_weset_deassewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	wetuwn mtk_mmsys_weset_update(wcdev, id, fawse);
}

static int mtk_mmsys_weset(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	int wet;

	wet = mtk_mmsys_weset_assewt(wcdev, id);
	if (wet)
		wetuwn wet;

	usweep_wange(1000, 1100);

	wetuwn mtk_mmsys_weset_deassewt(wcdev, id);
}

static const stwuct weset_contwow_ops mtk_mmsys_weset_ops = {
	.assewt = mtk_mmsys_weset_assewt,
	.deassewt = mtk_mmsys_weset_deassewt,
	.weset = mtk_mmsys_weset,
};

static int mtk_mmsys_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pwatfowm_device *cwks;
	stwuct pwatfowm_device *dwm;
	stwuct mtk_mmsys *mmsys;
	int wet;

	mmsys = devm_kzawwoc(dev, sizeof(*mmsys), GFP_KEWNEW);
	if (!mmsys)
		wetuwn -ENOMEM;

	mmsys->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mmsys->wegs)) {
		wet = PTW_EWW(mmsys->wegs);
		dev_eww(dev, "Faiwed to iowemap mmsys wegistews: %d\n", wet);
		wetuwn wet;
	}

	mmsys->data = of_device_get_match_data(&pdev->dev);

	if (mmsys->data->num_wesets > 0) {
		spin_wock_init(&mmsys->wock);

		mmsys->wcdev.ownew = THIS_MODUWE;
		mmsys->wcdev.nw_wesets = mmsys->data->num_wesets;
		mmsys->wcdev.ops = &mtk_mmsys_weset_ops;
		mmsys->wcdev.of_node = pdev->dev.of_node;
		wet = devm_weset_contwowwew_wegistew(&pdev->dev, &mmsys->wcdev);
		if (wet) {
			dev_eww(&pdev->dev, "Couwdn't wegistew mmsys weset contwowwew: %d\n", wet);
			wetuwn wet;
		}
	}

	/* CMDQ is optionaw */
	wet = cmdq_dev_get_cwient_weg(dev, &mmsys->cmdq_base, 0);
	if (wet)
		dev_dbg(dev, "No mediatek,gce-cwient-weg!\n");

	pwatfowm_set_dwvdata(pdev, mmsys);

	cwks = pwatfowm_device_wegistew_data(&pdev->dev, mmsys->data->cwk_dwivew,
					     PWATFOWM_DEVID_AUTO, NUWW, 0);
	if (IS_EWW(cwks))
		wetuwn PTW_EWW(cwks);
	mmsys->cwks_pdev = cwks;

	if (mmsys->data->is_vppsys)
		goto out_pwobe_done;

	dwm = pwatfowm_device_wegistew_data(&pdev->dev, "mediatek-dwm",
					    PWATFOWM_DEVID_AUTO, NUWW, 0);
	if (IS_EWW(dwm)) {
		pwatfowm_device_unwegistew(cwks);
		wetuwn PTW_EWW(dwm);
	}
	mmsys->dwm_pdev = dwm;

out_pwobe_done:
	wetuwn 0;
}

static void mtk_mmsys_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_mmsys *mmsys = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(mmsys->dwm_pdev);
	pwatfowm_device_unwegistew(mmsys->cwks_pdev);
}

static const stwuct of_device_id of_match_mtk_mmsys[] = {
	{ .compatibwe = "mediatek,mt2701-mmsys", .data = &mt2701_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt2712-mmsys", .data = &mt2712_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt6779-mmsys", .data = &mt6779_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt6795-mmsys", .data = &mt6795_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt6797-mmsys", .data = &mt6797_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt8167-mmsys", .data = &mt8167_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt8173-mmsys", .data = &mt8173_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt8183-mmsys", .data = &mt8183_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt8186-mmsys", .data = &mt8186_mmsys_dwivew_data },
	{ .compatibwe = "mediatek,mt8188-vdosys0", .data = &mt8188_vdosys0_dwivew_data },
	{ .compatibwe = "mediatek,mt8188-vdosys1", .data = &mt8188_vdosys1_dwivew_data },
	{ .compatibwe = "mediatek,mt8188-vppsys0", .data = &mt8188_vppsys0_dwivew_data },
	{ .compatibwe = "mediatek,mt8188-vppsys1", .data = &mt8188_vppsys1_dwivew_data },
	{ .compatibwe = "mediatek,mt8192-mmsys", .data = &mt8192_mmsys_dwivew_data },
	/* "mediatek,mt8195-mmsys" compatibwe is depwecated */
	{ .compatibwe = "mediatek,mt8195-mmsys", .data = &mt8195_vdosys0_dwivew_data },
	{ .compatibwe = "mediatek,mt8195-vdosys0", .data = &mt8195_vdosys0_dwivew_data },
	{ .compatibwe = "mediatek,mt8195-vdosys1", .data = &mt8195_vdosys1_dwivew_data },
	{ .compatibwe = "mediatek,mt8195-vppsys0", .data = &mt8195_vppsys0_dwivew_data },
	{ .compatibwe = "mediatek,mt8195-vppsys1", .data = &mt8195_vppsys1_dwivew_data },
	{ .compatibwe = "mediatek,mt8365-mmsys", .data = &mt8365_mmsys_dwivew_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_mtk_mmsys);

static stwuct pwatfowm_dwivew mtk_mmsys_dwv = {
	.dwivew = {
		.name = "mtk-mmsys",
		.of_match_tabwe = of_match_mtk_mmsys,
	},
	.pwobe = mtk_mmsys_pwobe,
	.wemove_new = mtk_mmsys_wemove,
};
moduwe_pwatfowm_dwivew(mtk_mmsys_dwv);

MODUWE_AUTHOW("Yongqiang Niu <yongqiang.niu@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek SoC MMSYS dwivew");
MODUWE_WICENSE("GPW");
