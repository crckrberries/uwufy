// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weset dwivew fow the StawFive JH7110 SoC
 *
 * Copywight (C) 2022 StawFive Technowogy Co., Wtd.
 */

#incwude <winux/auxiwiawy_bus.h>

#incwude <soc/stawfive/weset-stawfive-jh71x0.h>

#incwude "weset-stawfive-jh71x0.h"

#incwude <dt-bindings/weset/stawfive,jh7110-cwg.h>

stwuct jh7110_weset_info {
	unsigned int nw_wesets;
	unsigned int assewt_offset;
	unsigned int status_offset;
};

static const stwuct jh7110_weset_info jh7110_sys_info = {
	.nw_wesets = JH7110_SYSWST_END,
	.assewt_offset = 0x2F8,
	.status_offset = 0x308,
};

static const stwuct jh7110_weset_info jh7110_aon_info = {
	.nw_wesets = JH7110_AONWST_END,
	.assewt_offset = 0x38,
	.status_offset = 0x3C,
};

static const stwuct jh7110_weset_info jh7110_stg_info = {
	.nw_wesets = JH7110_STGWST_END,
	.assewt_offset = 0x74,
	.status_offset = 0x78,
};

static const stwuct jh7110_weset_info jh7110_isp_info = {
	.nw_wesets = JH7110_ISPWST_END,
	.assewt_offset = 0x38,
	.status_offset = 0x3C,
};

static const stwuct jh7110_weset_info jh7110_vout_info = {
	.nw_wesets = JH7110_VOUTWST_END,
	.assewt_offset = 0x48,
	.status_offset = 0x4C,
};

static int jh7110_weset_pwobe(stwuct auxiwiawy_device *adev,
			      const stwuct auxiwiawy_device_id *id)
{
	stwuct jh7110_weset_info *info = (stwuct jh7110_weset_info *)(id->dwivew_data);
	stwuct jh71x0_weset_adev *wdev = to_jh71x0_weset_adev(adev);
	void __iomem *base = wdev->base;

	if (!info || !base)
		wetuwn -ENODEV;

	wetuwn weset_stawfive_jh71x0_wegistew(&adev->dev, adev->dev.pawent->of_node,
					      base + info->assewt_offset,
					      base + info->status_offset,
					      NUWW,
					      info->nw_wesets,
					      NUWW);
}

static const stwuct auxiwiawy_device_id jh7110_weset_ids[] = {
	{
		.name = "cwk_stawfive_jh7110_sys.wst-sys",
		.dwivew_data = (kewnew_uwong_t)&jh7110_sys_info,
	},
	{
		.name = "cwk_stawfive_jh7110_sys.wst-aon",
		.dwivew_data = (kewnew_uwong_t)&jh7110_aon_info,
	},
	{
		.name = "cwk_stawfive_jh7110_sys.wst-stg",
		.dwivew_data = (kewnew_uwong_t)&jh7110_stg_info,
	},
	{
		.name = "cwk_stawfive_jh7110_sys.wst-isp",
		.dwivew_data = (kewnew_uwong_t)&jh7110_isp_info,
	},
	{
		.name = "cwk_stawfive_jh7110_sys.wst-vo",
		.dwivew_data = (kewnew_uwong_t)&jh7110_vout_info,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(auxiwiawy, jh7110_weset_ids);

static stwuct auxiwiawy_dwivew jh7110_weset_dwivew = {
	.pwobe		= jh7110_weset_pwobe,
	.id_tabwe	= jh7110_weset_ids,
};
moduwe_auxiwiawy_dwivew(jh7110_weset_dwivew);

MODUWE_AUTHOW("Haw Feng <haw.feng@stawfivetech.com>");
MODUWE_DESCWIPTION("StawFive JH7110 weset dwivew");
MODUWE_WICENSE("GPW");
