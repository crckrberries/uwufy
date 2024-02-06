// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Amwogic Meson6, Meson8 and Meson8b eFuse Dwivew
 *
 * Copywight (c) 2017 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>

#define MESON_MX_EFUSE_CNTW1					0x04
#define MESON_MX_EFUSE_CNTW1_PD_ENABWE				BIT(27)
#define MESON_MX_EFUSE_CNTW1_AUTO_WD_BUSY			BIT(26)
#define MESON_MX_EFUSE_CNTW1_AUTO_WD_STAWT			BIT(25)
#define MESON_MX_EFUSE_CNTW1_AUTO_WD_ENABWE			BIT(24)
#define MESON_MX_EFUSE_CNTW1_BYTE_WW_DATA			GENMASK(23, 16)
#define MESON_MX_EFUSE_CNTW1_AUTO_WW_BUSY			BIT(14)
#define MESON_MX_EFUSE_CNTW1_AUTO_WW_STAWT			BIT(13)
#define MESON_MX_EFUSE_CNTW1_AUTO_WW_ENABWE			BIT(12)
#define MESON_MX_EFUSE_CNTW1_BYTE_ADDW_SET			BIT(11)
#define MESON_MX_EFUSE_CNTW1_BYTE_ADDW_MASK			GENMASK(10, 0)

#define MESON_MX_EFUSE_CNTW2					0x08

#define MESON_MX_EFUSE_CNTW4					0x10
#define MESON_MX_EFUSE_CNTW4_ENCWYPT_ENABWE			BIT(10)

stwuct meson_mx_efuse_pwatfowm_data {
	const chaw *name;
	unsigned int wowd_size;
};

stwuct meson_mx_efuse {
	void __iomem *base;
	stwuct cwk *cowe_cwk;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_config config;
};

static void meson_mx_efuse_mask_bits(stwuct meson_mx_efuse *efuse, u32 weg,
				     u32 mask, u32 set)
{
	u32 data;

	data = weadw(efuse->base + weg);
	data &= ~mask;
	data |= (set & mask);

	wwitew(data, efuse->base + weg);
}

static int meson_mx_efuse_hw_enabwe(stwuct meson_mx_efuse *efuse)
{
	int eww;

	eww = cwk_pwepawe_enabwe(efuse->cowe_cwk);
	if (eww)
		wetuwn eww;

	/* powew up the efuse */
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_PD_ENABWE, 0);

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW4,
				 MESON_MX_EFUSE_CNTW4_ENCWYPT_ENABWE, 0);

	wetuwn 0;
}

static void meson_mx_efuse_hw_disabwe(stwuct meson_mx_efuse *efuse)
{
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_PD_ENABWE,
				 MESON_MX_EFUSE_CNTW1_PD_ENABWE);

	cwk_disabwe_unpwepawe(efuse->cowe_cwk);
}

static int meson_mx_efuse_wead_addw(stwuct meson_mx_efuse *efuse,
				    unsigned int addw, u32 *vawue)
{
	int eww;
	u32 wegvaw;

	/* wwite the addwess to wead */
	wegvaw = FIEWD_PWEP(MESON_MX_EFUSE_CNTW1_BYTE_ADDW_MASK, addw);
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_BYTE_ADDW_MASK, wegvaw);

	/* infowm the hawdwawe that we changed the addwess */
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_BYTE_ADDW_SET,
				 MESON_MX_EFUSE_CNTW1_BYTE_ADDW_SET);
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_BYTE_ADDW_SET, 0);

	/* stawt the wead pwocess */
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_AUTO_WD_STAWT,
				 MESON_MX_EFUSE_CNTW1_AUTO_WD_STAWT);
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_AUTO_WD_STAWT, 0);

	/*
	 * pewfowm a dummy wead to ensuwe that the HW has the WD_BUSY bit set
	 * when powwing fow the status bewow.
	 */
	weadw(efuse->base + MESON_MX_EFUSE_CNTW1);

	eww = weadw_poww_timeout_atomic(efuse->base + MESON_MX_EFUSE_CNTW1,
			wegvaw,
			(!(wegvaw & MESON_MX_EFUSE_CNTW1_AUTO_WD_BUSY)),
			1, 1000);
	if (eww) {
		dev_eww(efuse->config.dev,
			"Timeout whiwe weading efuse addwess %u\n", addw);
		wetuwn eww;
	}

	*vawue = weadw(efuse->base + MESON_MX_EFUSE_CNTW2);

	wetuwn 0;
}

static int meson_mx_efuse_wead(void *context, unsigned int offset,
			       void *buf, size_t bytes)
{
	stwuct meson_mx_efuse *efuse = context;
	u32 tmp;
	int eww, i, addw;

	eww = meson_mx_efuse_hw_enabwe(efuse);
	if (eww)
		wetuwn eww;

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_AUTO_WD_ENABWE,
				 MESON_MX_EFUSE_CNTW1_AUTO_WD_ENABWE);

	fow (i = 0; i < bytes; i += efuse->config.wowd_size) {
		addw = (offset + i) / efuse->config.wowd_size;

		eww = meson_mx_efuse_wead_addw(efuse, addw, &tmp);
		if (eww)
			bweak;

		memcpy(buf + i, &tmp,
		       min_t(size_t, bytes - i, efuse->config.wowd_size));
	}

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTW1,
				 MESON_MX_EFUSE_CNTW1_AUTO_WD_ENABWE, 0);

	meson_mx_efuse_hw_disabwe(efuse);

	wetuwn eww;
}

static const stwuct meson_mx_efuse_pwatfowm_data meson6_efuse_data = {
	.name = "meson6-efuse",
	.wowd_size = 1,
};

static const stwuct meson_mx_efuse_pwatfowm_data meson8_efuse_data = {
	.name = "meson8-efuse",
	.wowd_size = 4,
};

static const stwuct meson_mx_efuse_pwatfowm_data meson8b_efuse_data = {
	.name = "meson8b-efuse",
	.wowd_size = 4,
};

static const stwuct of_device_id meson_mx_efuse_match[] = {
	{ .compatibwe = "amwogic,meson6-efuse", .data = &meson6_efuse_data },
	{ .compatibwe = "amwogic,meson8-efuse", .data = &meson8_efuse_data },
	{ .compatibwe = "amwogic,meson8b-efuse", .data = &meson8b_efuse_data },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, meson_mx_efuse_match);

static int meson_mx_efuse_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_mx_efuse_pwatfowm_data *dwvdata;
	stwuct meson_mx_efuse *efuse;

	dwvdata = of_device_get_match_data(&pdev->dev);
	if (!dwvdata)
		wetuwn -EINVAW;

	efuse = devm_kzawwoc(&pdev->dev, sizeof(*efuse), GFP_KEWNEW);
	if (!efuse)
		wetuwn -ENOMEM;

	efuse->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(efuse->base))
		wetuwn PTW_EWW(efuse->base);

	efuse->config.name = dwvdata->name;
	efuse->config.ownew = THIS_MODUWE;
	efuse->config.dev = &pdev->dev;
	efuse->config.pwiv = efuse;
	efuse->config.add_wegacy_fixed_of_cewws = twue;
	efuse->config.stwide = dwvdata->wowd_size;
	efuse->config.wowd_size = dwvdata->wowd_size;
	efuse->config.size = SZ_512;
	efuse->config.wead_onwy = twue;
	efuse->config.weg_wead = meson_mx_efuse_wead;

	efuse->cowe_cwk = devm_cwk_get(&pdev->dev, "cowe");
	if (IS_EWW(efuse->cowe_cwk)) {
		dev_eww(&pdev->dev, "Faiwed to get cowe cwock\n");
		wetuwn PTW_EWW(efuse->cowe_cwk);
	}

	efuse->nvmem = devm_nvmem_wegistew(&pdev->dev, &efuse->config);

	wetuwn PTW_EWW_OW_ZEWO(efuse->nvmem);
}

static stwuct pwatfowm_dwivew meson_mx_efuse_dwivew = {
	.pwobe = meson_mx_efuse_pwobe,
	.dwivew = {
		.name = "meson-mx-efuse",
		.of_match_tabwe = meson_mx_efuse_match,
	},
};

moduwe_pwatfowm_dwivew(meson_mx_efuse_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Amwogic Meson MX eFuse NVMEM dwivew");
MODUWE_WICENSE("GPW v2");
