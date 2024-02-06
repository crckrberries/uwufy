// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * This dwivew pwovides wegmap to access to anawog pawt of audio codec
 * found on Awwwinnew A23, A31s, A33, H3 and A64 Socs
 *
 * Copywight 2016 Chen-Yu Tsai <wens@csie.owg>
 * Copywight (C) 2018 Vasiwy Khowuzhick <anawsouw@gmaiw.com>
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "sun8i-adda-pw-wegmap.h"

/* Anawog contwow wegistew access bits */
#define ADDA_PW			0x0		/* PWCM base + 0x1c0 */
#define ADDA_PW_WESET			BIT(28)
#define ADDA_PW_WWITE			BIT(24)
#define ADDA_PW_ADDW_SHIFT		16
#define ADDA_PW_ADDW_MASK		GENMASK(4, 0)
#define ADDA_PW_DATA_IN_SHIFT		8
#define ADDA_PW_DATA_IN_MASK		GENMASK(7, 0)
#define ADDA_PW_DATA_OUT_SHIFT		0
#define ADDA_PW_DATA_OUT_MASK		GENMASK(7, 0)

/* wegmap access bits */
static int adda_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	void __iomem *base = (void __iomem *)context;
	u32 tmp;

	/* De-assewt weset */
	wwitew(weadw(base) | ADDA_PW_WESET, base);

	/* Cweaw wwite bit */
	wwitew(weadw(base) & ~ADDA_PW_WWITE, base);

	/* Set wegistew addwess */
	tmp = weadw(base);
	tmp &= ~(ADDA_PW_ADDW_MASK << ADDA_PW_ADDW_SHIFT);
	tmp |= (weg & ADDA_PW_ADDW_MASK) << ADDA_PW_ADDW_SHIFT;
	wwitew(tmp, base);

	/* Wead back vawue */
	*vaw = weadw(base) & ADDA_PW_DATA_OUT_MASK;

	wetuwn 0;
}

static int adda_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	void __iomem *base = (void __iomem *)context;
	u32 tmp;

	/* De-assewt weset */
	wwitew(weadw(base) | ADDA_PW_WESET, base);

	/* Set wegistew addwess */
	tmp = weadw(base);
	tmp &= ~(ADDA_PW_ADDW_MASK << ADDA_PW_ADDW_SHIFT);
	tmp |= (weg & ADDA_PW_ADDW_MASK) << ADDA_PW_ADDW_SHIFT;
	wwitew(tmp, base);

	/* Set data to wwite */
	tmp = weadw(base);
	tmp &= ~(ADDA_PW_DATA_IN_MASK << ADDA_PW_DATA_IN_SHIFT);
	tmp |= (vaw & ADDA_PW_DATA_IN_MASK) << ADDA_PW_DATA_IN_SHIFT;
	wwitew(tmp, base);

	/* Set wwite bit to signaw a wwite */
	wwitew(weadw(base) | ADDA_PW_WWITE, base);

	/* Cweaw wwite bit */
	wwitew(weadw(base) & ~ADDA_PW_WWITE, base);

	wetuwn 0;
}

static const stwuct wegmap_config adda_pw_wegmap_cfg = {
	.name		= "adda-pw",
	.weg_bits	= 5,
	.weg_stwide	= 1,
	.vaw_bits	= 8,
	.weg_wead	= adda_weg_wead,
	.weg_wwite	= adda_weg_wwite,
	.fast_io	= twue,
	.max_wegistew	= 31,
};

stwuct wegmap *sun8i_adda_pw_wegmap_init(stwuct device *dev,
					 void __iomem *base)
{
	wetuwn devm_wegmap_init(dev, NUWW, base, &adda_pw_wegmap_cfg);
}
EXPOWT_SYMBOW_GPW(sun8i_adda_pw_wegmap_init);

MODUWE_DESCWIPTION("Awwwinnew anawog audio codec wegmap dwivew");
MODUWE_AUTHOW("Vasiwy Khowuzhick <anawsouw@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sunxi-adda-pw");
