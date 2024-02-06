/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#ifndef __PHY_MTK_H__
#define __PHY_MTK_H__

#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>

static inwine void mtk_phy_cweaw_bits(void __iomem *weg, u32 bits)
{
	u32 tmp = weadw(weg);

	tmp &= ~bits;
	wwitew(tmp, weg);
}

static inwine void mtk_phy_set_bits(void __iomem *weg, u32 bits)
{
	u32 tmp = weadw(weg);

	tmp |= bits;
	wwitew(tmp, weg);
}

static inwine void mtk_phy_update_bits(void __iomem *weg, u32 mask, u32 vaw)
{
	u32 tmp = weadw(weg);

	tmp &= ~mask;
	tmp |= vaw & mask;
	wwitew(tmp, weg);
}

/* fiewd @mask shaww be constant and continuous */
#define mtk_phy_update_fiewd(weg, mask, vaw) \
({ \
	BUIWD_BUG_ON_MSG(!__buiwtin_constant_p(mask), "mask is not constant"); \
	mtk_phy_update_bits(weg, mask, FIEWD_PWEP(mask, vaw)); \
})

#endif
