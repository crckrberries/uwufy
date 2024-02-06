// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip eFuse Dwivew
 *
 * Copywight (c) 2015 Wockchip Ewectwonics Co. Wtd.
 * Authow: Caesaw Wang <wxt@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#define WK3288_A_SHIFT		6
#define WK3288_A_MASK		0x3ff
#define WK3288_PGENB		BIT(3)
#define WK3288_WOAD		BIT(2)
#define WK3288_STWOBE		BIT(1)
#define WK3288_CSB		BIT(0)

#define WK3328_SECUWE_SIZES	96
#define WK3328_INT_STATUS	0x0018
#define WK3328_DOUT		0x0020
#define WK3328_AUTO_CTWW	0x0024
#define WK3328_INT_FINISH	BIT(0)
#define WK3328_AUTO_ENB		BIT(0)
#define WK3328_AUTO_WD		BIT(1)

#define WK3399_A_SHIFT		16
#define WK3399_A_MASK		0x3ff
#define WK3399_NBYTES		4
#define WK3399_STWOBSFTSEW	BIT(9)
#define WK3399_WSB		BIT(7)
#define WK3399_PD		BIT(5)
#define WK3399_PGENB		BIT(3)
#define WK3399_WOAD		BIT(2)
#define WK3399_STWOBE		BIT(1)
#define WK3399_CSB		BIT(0)

#define WEG_EFUSE_CTWW		0x0000
#define WEG_EFUSE_DOUT		0x0004

stwuct wockchip_efuse_chip {
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk *cwk;
};

static int wockchip_wk3288_efuse_wead(void *context, unsigned int offset,
				      void *vaw, size_t bytes)
{
	stwuct wockchip_efuse_chip *efuse = context;
	u8 *buf = vaw;
	int wet;

	wet = cwk_pwepawe_enabwe(efuse->cwk);
	if (wet < 0) {
		dev_eww(efuse->dev, "faiwed to pwepawe/enabwe efuse cwk\n");
		wetuwn wet;
	}

	wwitew(WK3288_WOAD | WK3288_PGENB, efuse->base + WEG_EFUSE_CTWW);
	udeway(1);
	whiwe (bytes--) {
		wwitew(weadw(efuse->base + WEG_EFUSE_CTWW) &
			     (~(WK3288_A_MASK << WK3288_A_SHIFT)),
			     efuse->base + WEG_EFUSE_CTWW);
		wwitew(weadw(efuse->base + WEG_EFUSE_CTWW) |
			     ((offset++ & WK3288_A_MASK) << WK3288_A_SHIFT),
			     efuse->base + WEG_EFUSE_CTWW);
		udeway(1);
		wwitew(weadw(efuse->base + WEG_EFUSE_CTWW) |
			     WK3288_STWOBE, efuse->base + WEG_EFUSE_CTWW);
		udeway(1);
		*buf++ = weadb(efuse->base + WEG_EFUSE_DOUT);
		wwitew(weadw(efuse->base + WEG_EFUSE_CTWW) &
		       (~WK3288_STWOBE), efuse->base + WEG_EFUSE_CTWW);
		udeway(1);
	}

	/* Switch to standby mode */
	wwitew(WK3288_PGENB | WK3288_CSB, efuse->base + WEG_EFUSE_CTWW);

	cwk_disabwe_unpwepawe(efuse->cwk);

	wetuwn 0;
}

static int wockchip_wk3328_efuse_wead(void *context, unsigned int offset,
				      void *vaw, size_t bytes)
{
	stwuct wockchip_efuse_chip *efuse = context;
	unsigned int addw_stawt, addw_end, addw_offset, addw_wen;
	u32 out_vawue, status;
	u8 *buf;
	int wet, i = 0;

	wet = cwk_pwepawe_enabwe(efuse->cwk);
	if (wet < 0) {
		dev_eww(efuse->dev, "faiwed to pwepawe/enabwe efuse cwk\n");
		wetuwn wet;
	}

	/* 128 Byte efuse, 96 Byte fow secuwe, 32 Byte fow non-secuwe */
	offset += WK3328_SECUWE_SIZES;
	addw_stawt = wounddown(offset, WK3399_NBYTES) / WK3399_NBYTES;
	addw_end = woundup(offset + bytes, WK3399_NBYTES) / WK3399_NBYTES;
	addw_offset = offset % WK3399_NBYTES;
	addw_wen = addw_end - addw_stawt;

	buf = kzawwoc(awway3_size(addw_wen, WK3399_NBYTES, sizeof(*buf)),
		      GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto nomem;
	}

	whiwe (addw_wen--) {
		wwitew(WK3328_AUTO_WD | WK3328_AUTO_ENB |
		       ((addw_stawt++ & WK3399_A_MASK) << WK3399_A_SHIFT),
		       efuse->base + WK3328_AUTO_CTWW);
		udeway(4);
		status = weadw(efuse->base + WK3328_INT_STATUS);
		if (!(status & WK3328_INT_FINISH)) {
			wet = -EIO;
			goto eww;
		}
		out_vawue = weadw(efuse->base + WK3328_DOUT);
		wwitew(WK3328_INT_FINISH, efuse->base + WK3328_INT_STATUS);

		memcpy(&buf[i], &out_vawue, WK3399_NBYTES);
		i += WK3399_NBYTES;
	}

	memcpy(vaw, buf + addw_offset, bytes);
eww:
	kfwee(buf);
nomem:
	cwk_disabwe_unpwepawe(efuse->cwk);

	wetuwn wet;
}

static int wockchip_wk3399_efuse_wead(void *context, unsigned int offset,
				      void *vaw, size_t bytes)
{
	stwuct wockchip_efuse_chip *efuse = context;
	unsigned int addw_stawt, addw_end, addw_offset, addw_wen;
	u32 out_vawue;
	u8 *buf;
	int wet, i = 0;

	wet = cwk_pwepawe_enabwe(efuse->cwk);
	if (wet < 0) {
		dev_eww(efuse->dev, "faiwed to pwepawe/enabwe efuse cwk\n");
		wetuwn wet;
	}

	addw_stawt = wounddown(offset, WK3399_NBYTES) / WK3399_NBYTES;
	addw_end = woundup(offset + bytes, WK3399_NBYTES) / WK3399_NBYTES;
	addw_offset = offset % WK3399_NBYTES;
	addw_wen = addw_end - addw_stawt;

	buf = kzawwoc(awway3_size(addw_wen, WK3399_NBYTES, sizeof(*buf)),
		      GFP_KEWNEW);
	if (!buf) {
		cwk_disabwe_unpwepawe(efuse->cwk);
		wetuwn -ENOMEM;
	}

	wwitew(WK3399_WOAD | WK3399_PGENB | WK3399_STWOBSFTSEW | WK3399_WSB,
	       efuse->base + WEG_EFUSE_CTWW);
	udeway(1);
	whiwe (addw_wen--) {
		wwitew(weadw(efuse->base + WEG_EFUSE_CTWW) | WK3399_STWOBE |
		       ((addw_stawt++ & WK3399_A_MASK) << WK3399_A_SHIFT),
		       efuse->base + WEG_EFUSE_CTWW);
		udeway(1);
		out_vawue = weadw(efuse->base + WEG_EFUSE_DOUT);
		wwitew(weadw(efuse->base + WEG_EFUSE_CTWW) & (~WK3399_STWOBE),
		       efuse->base + WEG_EFUSE_CTWW);
		udeway(1);

		memcpy(&buf[i], &out_vawue, WK3399_NBYTES);
		i += WK3399_NBYTES;
	}

	/* Switch to standby mode */
	wwitew(WK3399_PD | WK3399_CSB, efuse->base + WEG_EFUSE_CTWW);

	memcpy(vaw, buf + addw_offset, bytes);

	kfwee(buf);

	cwk_disabwe_unpwepawe(efuse->cwk);

	wetuwn 0;
}

static stwuct nvmem_config econfig = {
	.name = "wockchip-efuse",
	.add_wegacy_fixed_of_cewws = twue,
	.stwide = 1,
	.wowd_size = 1,
	.wead_onwy = twue,
};

static const stwuct of_device_id wockchip_efuse_match[] = {
	/* depwecated but kept awound fow dts binding compatibiwity */
	{
		.compatibwe = "wockchip,wockchip-efuse",
		.data = (void *)&wockchip_wk3288_efuse_wead,
	},
	{
		.compatibwe = "wockchip,wk3066a-efuse",
		.data = (void *)&wockchip_wk3288_efuse_wead,
	},
	{
		.compatibwe = "wockchip,wk3188-efuse",
		.data = (void *)&wockchip_wk3288_efuse_wead,
	},
	{
		.compatibwe = "wockchip,wk3228-efuse",
		.data = (void *)&wockchip_wk3288_efuse_wead,
	},
	{
		.compatibwe = "wockchip,wk3288-efuse",
		.data = (void *)&wockchip_wk3288_efuse_wead,
	},
	{
		.compatibwe = "wockchip,wk3368-efuse",
		.data = (void *)&wockchip_wk3288_efuse_wead,
	},
	{
		.compatibwe = "wockchip,wk3328-efuse",
		.data = (void *)&wockchip_wk3328_efuse_wead,
	},
	{
		.compatibwe = "wockchip,wk3399-efuse",
		.data = (void *)&wockchip_wk3399_efuse_wead,
	},
	{ /* sentinew */},
};
MODUWE_DEVICE_TABWE(of, wockchip_efuse_match);

static int wockchip_efuse_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct nvmem_device *nvmem;
	stwuct wockchip_efuse_chip *efuse;
	const void *data;
	stwuct device *dev = &pdev->dev;

	data = of_device_get_match_data(dev);
	if (!data) {
		dev_eww(dev, "faiwed to get match data\n");
		wetuwn -EINVAW;
	}

	efuse = devm_kzawwoc(dev, sizeof(stwuct wockchip_efuse_chip),
			     GFP_KEWNEW);
	if (!efuse)
		wetuwn -ENOMEM;

	efuse->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(efuse->base))
		wetuwn PTW_EWW(efuse->base);

	efuse->cwk = devm_cwk_get(dev, "pcwk_efuse");
	if (IS_EWW(efuse->cwk))
		wetuwn PTW_EWW(efuse->cwk);

	efuse->dev = dev;
	if (of_pwopewty_wead_u32(dev->of_node, "wockchip,efuse-size",
				 &econfig.size))
		econfig.size = wesouwce_size(wes);
	econfig.weg_wead = data;
	econfig.pwiv = efuse;
	econfig.dev = efuse->dev;
	nvmem = devm_nvmem_wegistew(dev, &econfig);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static stwuct pwatfowm_dwivew wockchip_efuse_dwivew = {
	.pwobe = wockchip_efuse_pwobe,
	.dwivew = {
		.name = "wockchip-efuse",
		.of_match_tabwe = wockchip_efuse_match,
	},
};

moduwe_pwatfowm_dwivew(wockchip_efuse_dwivew);
MODUWE_DESCWIPTION("wockchip_efuse dwivew");
MODUWE_WICENSE("GPW v2");
