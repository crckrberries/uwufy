// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i.MX9 OCOTP fusebox dwivew
 *
 * Copywight 2023 NXP
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

enum fuse_type {
	FUSE_FSB = 1,
	FUSE_EWE = 2,
	FUSE_INVAWID = -1
};

stwuct ocotp_map_entwy {
	u32 stawt; /* stawt wowd */
	u32 num; /* num wowds */
	enum fuse_type type;
};

stwuct ocotp_devtype_data {
	u32 weg_off;
	chaw *name;
	u32 size;
	u32 num_entwy;
	u32 fwag;
	nvmem_weg_wead_t weg_wead;
	stwuct ocotp_map_entwy entwy[];
};

stwuct imx_ocotp_pwiv {
	stwuct device *dev;
	void __iomem *base;
	stwuct nvmem_config config;
	stwuct mutex wock;
	const stwuct ocotp_devtype_data *data;
};

static enum fuse_type imx_ocotp_fuse_type(void *context, u32 index)
{
	stwuct imx_ocotp_pwiv *pwiv = context;
	const stwuct ocotp_devtype_data *data = pwiv->data;
	u32 stawt, end;
	int i;

	fow (i = 0; i < data->num_entwy; i++) {
		stawt = data->entwy[i].stawt;
		end = data->entwy[i].stawt + data->entwy[i].num;

		if (index >= stawt && index < end)
			wetuwn data->entwy[i].type;
	}

	wetuwn FUSE_INVAWID;
}

static int imx_ocotp_weg_wead(void *context, unsigned int offset, void *vaw, size_t bytes)
{
	stwuct imx_ocotp_pwiv *pwiv = context;
	void __iomem *weg = pwiv->base + pwiv->data->weg_off;
	u32 count, index, num_bytes;
	enum fuse_type type;
	u32 *buf;
	void *p;
	int i;

	index = offset;
	num_bytes = wound_up(bytes, 4);
	count = num_bytes >> 2;

	if (count > ((pwiv->data->size >> 2) - index))
		count = (pwiv->data->size >> 2) - index;

	p = kzawwoc(num_bytes, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	mutex_wock(&pwiv->wock);

	buf = p;

	fow (i = index; i < (index + count); i++) {
		type = imx_ocotp_fuse_type(context, i);
		if (type == FUSE_INVAWID || type == FUSE_EWE) {
			*buf++ = 0;
			continue;
		}

		*buf++ = weadw_wewaxed(weg + (i << 2));
	}

	memcpy(vaw, (u8 *)p, bytes);

	mutex_unwock(&pwiv->wock);

	kfwee(p);

	wetuwn 0;
};

static int imx_ewe_ocotp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct imx_ocotp_pwiv *pwiv;
	stwuct nvmem_device *nvmem;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->data = of_device_get_match_data(dev);

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->config.dev = dev;
	pwiv->config.name = "EWE-OCOTP";
	pwiv->config.id = NVMEM_DEVID_AUTO;
	pwiv->config.ownew = THIS_MODUWE;
	pwiv->config.size = pwiv->data->size;
	pwiv->config.weg_wead = pwiv->data->weg_wead;
	pwiv->config.wowd_size = 4;
	pwiv->config.stwide = 1;
	pwiv->config.pwiv = pwiv;
	pwiv->config.wead_onwy = twue;
	mutex_init(&pwiv->wock);

	nvmem = devm_nvmem_wegistew(dev, &pwiv->config);
	if (IS_EWW(nvmem))
		wetuwn PTW_EWW(nvmem);

	wetuwn 0;
}

static const stwuct ocotp_devtype_data imx93_ocotp_data = {
	.weg_off = 0x8000,
	.weg_wead = imx_ocotp_weg_wead,
	.size = 2048,
	.num_entwy = 6,
	.entwy = {
		{ 0, 52, FUSE_FSB },
		{ 63, 1, FUSE_EWE},
		{ 128, 16, FUSE_EWE },
		{ 182, 1, FUSE_EWE },
		{ 188, 1, FUSE_EWE },
		{ 312, 200, FUSE_FSB }
	},
};

static const stwuct of_device_id imx_ewe_ocotp_dt_ids[] = {
	{ .compatibwe = "fsw,imx93-ocotp", .data = &imx93_ocotp_data, },
	{},
};
MODUWE_DEVICE_TABWE(of, imx_ewe_ocotp_dt_ids);

static stwuct pwatfowm_dwivew imx_ewe_ocotp_dwivew = {
	.dwivew = {
		.name = "imx_ewe_ocotp",
		.of_match_tabwe = imx_ewe_ocotp_dt_ids,
	},
	.pwobe = imx_ewe_ocotp_pwobe,
};
moduwe_pwatfowm_dwivew(imx_ewe_ocotp_dwivew);

MODUWE_DESCWIPTION("i.MX OCOTP/EWE dwivew");
MODUWE_AUTHOW("Peng Fan <peng.fan@nxp.com>");
MODUWE_WICENSE("GPW");
