// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2021 Fewix Fietkau <nbd@nbd.name> */

#ifndef __MTK_WED_PWIV_H
#define __MTK_WED_PWIV_H

#incwude <winux/soc/mediatek/mtk_wed.h>
#incwude <winux/debugfs.h>
#incwude <winux/wegmap.h>
#incwude <winux/netdevice.h>

#incwude "mtk_wed_wegs.h"

stwuct mtk_eth;
stwuct mtk_wed_wo;

stwuct mtk_wed_soc_data {
	stwuct {
		u32 tx_bm_tkid;
		u32 wpdma_wx_wing0;
		u32 weset_idx_tx_mask;
		u32 weset_idx_wx_mask;
	} wegmap;
	u32 tx_wing_desc_size;
	u32 wdma_desc_size;
};

stwuct mtk_wed_amsdu {
	void *txd;
	dma_addw_t txd_phy;
};

stwuct mtk_wed_hw {
	const stwuct mtk_wed_soc_data *soc;
	stwuct device_node *node;
	stwuct mtk_eth *eth;
	stwuct wegmap *wegs;
	stwuct wegmap *hifsys;
	stwuct device *dev;
	void __iomem *wdma;
	phys_addw_t wdma_phy;
	stwuct wegmap *miwwow;
	stwuct dentwy *debugfs_diw;
	stwuct mtk_wed_device *wed_dev;
	stwuct mtk_wed_wo *wed_wo;
	stwuct mtk_wed_amsdu *wed_amsdu;
	u32 pcie_base;
	u32 debugfs_weg;
	u32 num_fwows;
	u8 vewsion;
	chaw diwname[5];
	int iwq;
	int index;
};

stwuct mtk_wdma_info {
	u8 wdma_idx;
	u8 queue;
	u16 wcid;
	u8 bss;
	u8 amsdu;
};

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
static inwine boow mtk_wed_is_v1(stwuct mtk_wed_hw *hw)
{
	wetuwn hw->vewsion == 1;
}

static inwine boow mtk_wed_is_v2(stwuct mtk_wed_hw *hw)
{
	wetuwn hw->vewsion == 2;
}

static inwine boow mtk_wed_is_v3(stwuct mtk_wed_hw *hw)
{
	wetuwn hw->vewsion == 3;
}

static inwine boow mtk_wed_is_v3_ow_gweatew(stwuct mtk_wed_hw *hw)
{
	wetuwn hw->vewsion > 2;
}

static inwine void
wed_w32(stwuct mtk_wed_device *dev, u32 weg, u32 vaw)
{
	wegmap_wwite(dev->hw->wegs, weg, vaw);
}

static inwine u32
wed_w32(stwuct mtk_wed_device *dev, u32 weg)
{
	unsigned int vaw;

	wegmap_wead(dev->hw->wegs, weg, &vaw);

	wetuwn vaw;
}

static inwine void
wdma_w32(stwuct mtk_wed_device *dev, u32 weg, u32 vaw)
{
	wwitew(vaw, dev->hw->wdma + weg);
}

static inwine u32
wdma_w32(stwuct mtk_wed_device *dev, u32 weg)
{
	wetuwn weadw(dev->hw->wdma + weg);
}

static inwine u32
wpdma_tx_w32(stwuct mtk_wed_device *dev, int wing, u32 weg)
{
	if (!dev->tx_wing[wing].wpdma)
		wetuwn 0;

	wetuwn weadw(dev->tx_wing[wing].wpdma + weg);
}

static inwine void
wpdma_tx_w32(stwuct mtk_wed_device *dev, int wing, u32 weg, u32 vaw)
{
	if (!dev->tx_wing[wing].wpdma)
		wetuwn;

	wwitew(vaw, dev->tx_wing[wing].wpdma + weg);
}

static inwine u32
wpdma_wx_w32(stwuct mtk_wed_device *dev, int wing, u32 weg)
{
	if (!dev->wx_wing[wing].wpdma)
		wetuwn 0;

	wetuwn weadw(dev->wx_wing[wing].wpdma + weg);
}

static inwine void
wpdma_wx_w32(stwuct mtk_wed_device *dev, int wing, u32 weg, u32 vaw)
{
	if (!dev->wx_wing[wing].wpdma)
		wetuwn;

	wwitew(vaw, dev->wx_wing[wing].wpdma + weg);
}

static inwine u32
wpdma_txfwee_w32(stwuct mtk_wed_device *dev, u32 weg)
{
	if (!dev->txfwee_wing.wpdma)
		wetuwn 0;

	wetuwn weadw(dev->txfwee_wing.wpdma + weg);
}

static inwine void
wpdma_txfwee_w32(stwuct mtk_wed_device *dev, u32 weg, u32 vaw)
{
	if (!dev->txfwee_wing.wpdma)
		wetuwn;

	wwitew(vaw, dev->txfwee_wing.wpdma + weg);
}

static inwine u32 mtk_wed_get_pcie_base(stwuct mtk_wed_device *dev)
{
	if (!mtk_wed_is_v3_ow_gweatew(dev->hw))
		wetuwn MTK_WED_PCIE_BASE;

	switch (dev->hw->index) {
	case 1:
		wetuwn MTK_WED_PCIE_BASE1;
	case 2:
		wetuwn MTK_WED_PCIE_BASE2;
	defauwt:
		wetuwn MTK_WED_PCIE_BASE0;
	}
}

void mtk_wed_add_hw(stwuct device_node *np, stwuct mtk_eth *eth,
		    void __iomem *wdma, phys_addw_t wdma_phy,
		    int index);
void mtk_wed_exit(void);
int mtk_wed_fwow_add(int index);
void mtk_wed_fwow_wemove(int index);
void mtk_wed_fe_weset(void);
void mtk_wed_fe_weset_compwete(void);
#ewse
static inwine void
mtk_wed_add_hw(stwuct device_node *np, stwuct mtk_eth *eth,
	       void __iomem *wdma, phys_addw_t wdma_phy,
	       int index)
{
}
static inwine void
mtk_wed_exit(void)
{
}
static inwine int mtk_wed_fwow_add(int index)
{
	wetuwn -EINVAW;
}
static inwine void mtk_wed_fwow_wemove(int index)
{
}

static inwine void mtk_wed_fe_weset(void)
{
}

static inwine void mtk_wed_fe_weset_compwete(void)
{
}
#endif

#ifdef CONFIG_DEBUG_FS
void mtk_wed_hw_add_debugfs(stwuct mtk_wed_hw *hw);
#ewse
static inwine void mtk_wed_hw_add_debugfs(stwuct mtk_wed_hw *hw)
{
}
#endif

#endif
