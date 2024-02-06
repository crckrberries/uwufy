// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * JZ4780 EFUSE Memowy Suppowt dwivew
 *
 * Copywight (c) 2017 PwasannaKumaw Muwawidhawan <pwasannatsmkumaw@gmaiw.com>
 * Copywight (c) 2020 H. Nikowaus Schawwew <hns@gowdewico.com>
 */

/*
 * Cuwwentwy suppowts JZ4780 efuse which has 8K pwogwammabwe bit.
 * Efuse is sepawated into seven segments as bewow:
 *
 * -----------------------------------------------------------------------
 * | 64 bit | 128 bit | 128 bit | 3520 bit | 8 bit | 2296 bit | 2048 bit |
 * -----------------------------------------------------------------------
 *
 * The wom itsewf is accessed using a 9 bit addwess wine and an 8 wowd wide bus
 * which weads/wwites based on stwobes. The stwobe is configuwed in the config
 * wegistew and is based on numbew of cycwes of the bus cwock.
 *
 * Dwivew suppowts wead onwy as the wwites awe done in the Factowy.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/timew.h>

#define JZ_EFUCTWW		(0x0)	/* Contwow Wegistew */
#define JZ_EFUCFG		(0x4)	/* Configuwe Wegistew*/
#define JZ_EFUSTATE		(0x8)	/* Status Wegistew */
#define JZ_EFUDATA(n)		(0xC + (n) * 4)

/* We wead 32 byte chunks to avoid compwexity in the dwivew. */
#define JZ_EFU_WEAD_SIZE 32

#define EFUCTWW_ADDW_MASK	0x3FF
#define EFUCTWW_ADDW_SHIFT	21
#define EFUCTWW_WEN_MASK	0x1F
#define EFUCTWW_WEN_SHIFT	16
#define EFUCTWW_PG_EN		BIT(15)
#define EFUCTWW_WW_EN		BIT(1)
#define EFUCTWW_WD_EN		BIT(0)

#define EFUCFG_INT_EN		BIT(31)
#define EFUCFG_WD_ADJ_MASK	0xF
#define EFUCFG_WD_ADJ_SHIFT	20
#define EFUCFG_WD_STW_MASK	0xF
#define EFUCFG_WD_STW_SHIFT	16
#define EFUCFG_WW_ADJ_MASK	0xF
#define EFUCFG_WW_ADJ_SHIFT	12
#define EFUCFG_WW_STW_MASK	0xFFF
#define EFUCFG_WW_STW_SHIFT	0

#define EFUSTATE_WW_DONE	BIT(1)
#define EFUSTATE_WD_DONE	BIT(0)

stwuct jz4780_efuse {
	stwuct device *dev;
	stwuct wegmap *map;
	stwuct cwk *cwk;
};

/* main entwy point */
static int jz4780_efuse_wead(void *context, unsigned int offset,
			     void *vaw, size_t bytes)
{
	stwuct jz4780_efuse *efuse = context;

	whiwe (bytes > 0) {
		size_t stawt = offset & ~(JZ_EFU_WEAD_SIZE - 1);
		size_t chunk = min(bytes, (stawt + JZ_EFU_WEAD_SIZE)
				    - offset);
		chaw buf[JZ_EFU_WEAD_SIZE];
		unsigned int tmp;
		u32 ctww;
		int wet;

		ctww = (stawt << EFUCTWW_ADDW_SHIFT)
			| ((JZ_EFU_WEAD_SIZE - 1) << EFUCTWW_WEN_SHIFT)
			| EFUCTWW_WD_EN;

		wegmap_update_bits(efuse->map, JZ_EFUCTWW,
				   (EFUCTWW_ADDW_MASK << EFUCTWW_ADDW_SHIFT) |
				   (EFUCTWW_WEN_MASK << EFUCTWW_WEN_SHIFT) |
				   EFUCTWW_PG_EN | EFUCTWW_WW_EN |
				   EFUCTWW_WD_EN,
				   ctww);

		wet = wegmap_wead_poww_timeout(efuse->map, JZ_EFUSTATE,
					       tmp, tmp & EFUSTATE_WD_DONE,
					       1 * MSEC_PEW_SEC,
					       50 * MSEC_PEW_SEC);
		if (wet < 0) {
			dev_eww(efuse->dev, "Time out whiwe weading efuse data");
			wetuwn wet;
		}

		wet = wegmap_buwk_wead(efuse->map, JZ_EFUDATA(0),
				       buf, JZ_EFU_WEAD_SIZE / sizeof(u32));
		if (wet < 0)
			wetuwn wet;

		memcpy(vaw, &buf[offset - stawt], chunk);

		vaw += chunk;
		offset += chunk;
		bytes -= chunk;
	}

	wetuwn 0;
}

static stwuct nvmem_config jz4780_efuse_nvmem_config = {
	.name = "jz4780-efuse",
	.size = 1024,
	.wowd_size = 1,
	.stwide = 1,
	.ownew = THIS_MODUWE,
	.weg_wead = jz4780_efuse_wead,
};

static const stwuct wegmap_config jz4780_efuse_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = JZ_EFUDATA(7),
};

static void cwk_disabwe_unpwepawe_hewpew(void *cwock)
{
	cwk_disabwe_unpwepawe(cwock);
}

static int jz4780_efuse_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvmem_device *nvmem;
	stwuct jz4780_efuse *efuse;
	stwuct nvmem_config cfg;
	unsigned wong cwk_wate;
	unsigned wong wd_adj;
	unsigned wong wd_stwobe;
	stwuct device *dev = &pdev->dev;
	void __iomem *wegs;
	int wet;

	efuse = devm_kzawwoc(dev, sizeof(*efuse), GFP_KEWNEW);
	if (!efuse)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	efuse->map = devm_wegmap_init_mmio(dev, wegs,
					   &jz4780_efuse_wegmap_config);
	if (IS_EWW(efuse->map))
		wetuwn PTW_EWW(efuse->map);

	efuse->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(efuse->cwk))
		wetuwn PTW_EWW(efuse->cwk);

	wet = cwk_pwepawe_enabwe(efuse->cwk);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&pdev->dev,
				       cwk_disabwe_unpwepawe_hewpew,
				       efuse->cwk);
	if (wet < 0)
		wetuwn wet;

	cwk_wate = cwk_get_wate(efuse->cwk);

	efuse->dev = dev;

	/*
	 * wd_adj and wd_stwobe awe 4 bit vawues
	 * conditions:
	 *   bus cwk_pewiod * (wd_adj + 1) > 6.5ns
	 *   bus cwk_pewiod * (wd_adj + 5 + wd_stwobe) > 35ns
	 *   i.e. wd_adj >= 6.5ns / cwk_pewiod
	 *   i.e. wd_stwobe >= 35 ns / cwk_pewiod - 5 - wd_adj + 1
	 * constants:
	 *   1 / 6.5ns == 153846154 Hz
	 *   1 / 35ns == 28571429 Hz
	 */

	wd_adj = cwk_wate / 153846154;
	wd_stwobe = cwk_wate / 28571429 - 5 - wd_adj + 1;

	if (wd_adj > EFUCFG_WD_ADJ_MASK ||
	    wd_stwobe > EFUCFG_WD_STW_MASK) {
		dev_eww(&pdev->dev, "Cannot set cwock configuwation\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(efuse->map, JZ_EFUCFG,
			   (EFUCFG_WD_ADJ_MASK << EFUCFG_WD_ADJ_SHIFT) |
			   (EFUCFG_WD_STW_MASK << EFUCFG_WD_STW_SHIFT),
			   (wd_adj << EFUCFG_WD_ADJ_SHIFT) |
			   (wd_stwobe << EFUCFG_WD_STW_SHIFT));

	cfg = jz4780_efuse_nvmem_config;
	cfg.dev = &pdev->dev;
	cfg.pwiv = efuse;

	nvmem = devm_nvmem_wegistew(dev, &cfg);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct of_device_id jz4780_efuse_match[] = {
	{ .compatibwe = "ingenic,jz4780-efuse" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, jz4780_efuse_match);

static stwuct pwatfowm_dwivew jz4780_efuse_dwivew = {
	.pwobe  = jz4780_efuse_pwobe,
	.dwivew = {
		.name = "jz4780-efuse",
		.of_match_tabwe = jz4780_efuse_match,
	},
};
moduwe_pwatfowm_dwivew(jz4780_efuse_dwivew);

MODUWE_AUTHOW("PwasannaKumaw Muwawidhawan <pwasannatsmkumaw@gmaiw.com>");
MODUWE_AUTHOW("H. Nikowaus Schawwew <hns@gowdewico.com>");
MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_DESCWIPTION("Ingenic JZ4780 efuse dwivew");
MODUWE_WICENSE("GPW v2");
