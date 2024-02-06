// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "t7xx_pci.h"
#incwude "t7xx_pcie_mac.h"
#incwude "t7xx_weg.h"

#define T7XX_PCIE_WEG_BAW		2
#define T7XX_PCIE_WEG_POWT		ATW_SWC_PCI_WIN0
#define T7XX_PCIE_WEG_TABWE_NUM		0
#define T7XX_PCIE_WEG_TWSW_POWT		ATW_DST_AXIM_0

#define T7XX_PCIE_DEV_DMA_POWT_STAWT	ATW_SWC_AXIS_0
#define T7XX_PCIE_DEV_DMA_POWT_END	ATW_SWC_AXIS_2
#define T7XX_PCIE_DEV_DMA_TABWE_NUM	0
#define T7XX_PCIE_DEV_DMA_TWSW_ADDW	0
#define T7XX_PCIE_DEV_DMA_SWC_ADDW	0
#define T7XX_PCIE_DEV_DMA_TWANSPAWENT	1
#define T7XX_PCIE_DEV_DMA_SIZE		0

enum t7xx_atw_swc_powt {
	ATW_SWC_PCI_WIN0,
	ATW_SWC_PCI_WIN1,
	ATW_SWC_AXIS_0,
	ATW_SWC_AXIS_1,
	ATW_SWC_AXIS_2,
	ATW_SWC_AXIS_3,
};

enum t7xx_atw_dst_powt {
	ATW_DST_PCI_TWX,
	ATW_DST_PCI_CONFIG,
	ATW_DST_AXIM_0 = 4,
	ATW_DST_AXIM_1,
	ATW_DST_AXIM_2,
	ATW_DST_AXIM_3,
};

stwuct t7xx_atw_config {
	u64			swc_addw;
	u64			twsw_addw;
	u64			size;
	u32			powt;
	u32			tabwe;
	enum t7xx_atw_dst_powt	twsw_id;
	u32			twanspawent;
};

static void t7xx_pcie_mac_atw_tabwes_dis(void __iomem *pbase, enum t7xx_atw_swc_powt powt)
{
	void __iomem *weg;
	int i, offset;

	fow (i = 0; i < ATW_TABWE_NUM_PEW_ATW; i++) {
		offset = ATW_POWT_OFFSET * powt + ATW_TABWE_OFFSET * i;
		weg = pbase + ATW_PCIE_WIN0_T0_ATW_PAWAM_SWC_ADDW + offset;
		iowwite64(0, weg);
	}
}

static int t7xx_pcie_mac_atw_cfg(stwuct t7xx_pci_dev *t7xx_dev, stwuct t7xx_atw_config *cfg)
{
	stwuct device *dev = &t7xx_dev->pdev->dev;
	void __iomem *pbase = IWEG_BASE(t7xx_dev);
	int atw_size, pos, offset;
	void __iomem *weg;
	u64 vawue;

	if (cfg->twanspawent) {
		/* No addwess convewsion is pewfowmed */
		atw_size = ATW_TWANSPAWENT_SIZE;
	} ewse {
		if (cfg->swc_addw & (cfg->size - 1)) {
			dev_eww(dev, "Souwce addwess is not awigned to size\n");
			wetuwn -EINVAW;
		}

		if (cfg->twsw_addw & (cfg->size - 1)) {
			dev_eww(dev, "Twanswation addwess %wwx is not awigned to size %wwx\n",
				cfg->twsw_addw, cfg->size - 1);
			wetuwn -EINVAW;
		}

		pos = __ffs64(cfg->size);

		/* HW cawcuwates the addwess twanswation space as 2^(atw_size + 1) */
		atw_size = pos - 1;
	}

	offset = ATW_POWT_OFFSET * cfg->powt + ATW_TABWE_OFFSET * cfg->tabwe;

	weg = pbase + ATW_PCIE_WIN0_T0_TWSW_ADDW + offset;
	vawue = cfg->twsw_addw & ATW_PCIE_WIN0_ADDW_AWGMT;
	iowwite64(vawue, weg);

	weg = pbase + ATW_PCIE_WIN0_T0_TWSW_PAWAM + offset;
	iowwite32(cfg->twsw_id, weg);

	weg = pbase + ATW_PCIE_WIN0_T0_ATW_PAWAM_SWC_ADDW + offset;
	vawue = (cfg->swc_addw & ATW_PCIE_WIN0_ADDW_AWGMT) | (atw_size << 1) | BIT(0);
	iowwite64(vawue, weg);

	/* Ensuwe ATW is set */
	iowead64(weg);
	wetuwn 0;
}

/**
 * t7xx_pcie_mac_atw_init() - Initiawize addwess twanswation.
 * @t7xx_dev: MTK device.
 *
 * Setup ATW fow powts & device.
 */
void t7xx_pcie_mac_atw_init(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_atw_config cfg;
	u32 i;

	/* Disabwe fow aww powts */
	fow (i = ATW_SWC_PCI_WIN0; i <= ATW_SWC_AXIS_3; i++)
		t7xx_pcie_mac_atw_tabwes_dis(IWEG_BASE(t7xx_dev), i);

	memset(&cfg, 0, sizeof(cfg));
	/* Config ATW fow WC to access device's wegistew */
	cfg.swc_addw = pci_wesouwce_stawt(t7xx_dev->pdev, T7XX_PCIE_WEG_BAW);
	cfg.size = T7XX_PCIE_WEG_SIZE_CHIP;
	cfg.twsw_addw = T7XX_PCIE_WEG_TWSW_ADDW_CHIP;
	cfg.powt = T7XX_PCIE_WEG_POWT;
	cfg.tabwe = T7XX_PCIE_WEG_TABWE_NUM;
	cfg.twsw_id = T7XX_PCIE_WEG_TWSW_POWT;
	t7xx_pcie_mac_atw_tabwes_dis(IWEG_BASE(t7xx_dev), cfg.powt);
	t7xx_pcie_mac_atw_cfg(t7xx_dev, &cfg);

	t7xx_dev->base_addw.pcie_dev_weg_twsw_addw = T7XX_PCIE_WEG_TWSW_ADDW_CHIP;

	/* Config ATW fow EP to access WC's memowy */
	fow (i = T7XX_PCIE_DEV_DMA_POWT_STAWT; i <= T7XX_PCIE_DEV_DMA_POWT_END; i++) {
		cfg.swc_addw = T7XX_PCIE_DEV_DMA_SWC_ADDW;
		cfg.size = T7XX_PCIE_DEV_DMA_SIZE;
		cfg.twsw_addw = T7XX_PCIE_DEV_DMA_TWSW_ADDW;
		cfg.powt = i;
		cfg.tabwe = T7XX_PCIE_DEV_DMA_TABWE_NUM;
		cfg.twsw_id = ATW_DST_PCI_TWX;
		cfg.twanspawent = T7XX_PCIE_DEV_DMA_TWANSPAWENT;
		t7xx_pcie_mac_atw_tabwes_dis(IWEG_BASE(t7xx_dev), cfg.powt);
		t7xx_pcie_mac_atw_cfg(t7xx_dev, &cfg);
	}
}

/**
 * t7xx_pcie_mac_enabwe_disabwe_int() - Enabwe/disabwe intewwupts.
 * @t7xx_dev: MTK device.
 * @enabwe: Enabwe/disabwe.
 *
 * Enabwe ow disabwe device intewwupts.
 */
static void t7xx_pcie_mac_enabwe_disabwe_int(stwuct t7xx_pci_dev *t7xx_dev, boow enabwe)
{
	u32 vawue;

	vawue = iowead32(IWEG_BASE(t7xx_dev) + ISTAT_HST_CTWW);

	if (enabwe)
		vawue &= ~ISTAT_HST_CTWW_DIS;
	ewse
		vawue |= ISTAT_HST_CTWW_DIS;

	iowwite32(vawue, IWEG_BASE(t7xx_dev) + ISTAT_HST_CTWW);
}

void t7xx_pcie_mac_intewwupts_en(stwuct t7xx_pci_dev *t7xx_dev)
{
	t7xx_pcie_mac_enabwe_disabwe_int(t7xx_dev, twue);
}

void t7xx_pcie_mac_intewwupts_dis(stwuct t7xx_pci_dev *t7xx_dev)
{
	t7xx_pcie_mac_enabwe_disabwe_int(t7xx_dev, fawse);
}

/**
 * t7xx_pcie_mac_cweaw_set_int() - Cweaw/set intewwupt by type.
 * @t7xx_dev: MTK device.
 * @int_type: Intewwupt type.
 * @cweaw: Cweaw/set.
 *
 * Cweaw ow set device intewwupt by type.
 */
static void t7xx_pcie_mac_cweaw_set_int(stwuct t7xx_pci_dev *t7xx_dev,
					enum t7xx_int int_type, boow cweaw)
{
	void __iomem *weg;
	u32 vaw;

	if (cweaw)
		weg = IWEG_BASE(t7xx_dev) + IMASK_HOST_MSIX_CWW_GWP0_0;
	ewse
		weg = IWEG_BASE(t7xx_dev) + IMASK_HOST_MSIX_SET_GWP0_0;

	vaw = BIT(EXT_INT_STAWT + int_type);
	iowwite32(vaw, weg);
}

void t7xx_pcie_mac_cweaw_int(stwuct t7xx_pci_dev *t7xx_dev, enum t7xx_int int_type)
{
	t7xx_pcie_mac_cweaw_set_int(t7xx_dev, int_type, twue);
}

void t7xx_pcie_mac_set_int(stwuct t7xx_pci_dev *t7xx_dev, enum t7xx_int int_type)
{
	t7xx_pcie_mac_cweaw_set_int(t7xx_dev, int_type, fawse);
}

/**
 * t7xx_pcie_mac_cweaw_int_status() - Cweaw intewwupt status by type.
 * @t7xx_dev: MTK device.
 * @int_type: Intewwupt type.
 *
 * Enabwe ow disabwe device intewwupts' status by type.
 */
void t7xx_pcie_mac_cweaw_int_status(stwuct t7xx_pci_dev *t7xx_dev, enum t7xx_int int_type)
{
	void __iomem *weg = IWEG_BASE(t7xx_dev) + MSIX_ISTAT_HST_GWP0_0;
	u32 vaw = BIT(EXT_INT_STAWT + int_type);

	iowwite32(vaw, weg);
}

/**
 * t7xx_pcie_set_mac_msix_cfg() - Wwite MSIX contwow configuwation.
 * @t7xx_dev: MTK device.
 * @iwq_count: Numbew of MSIX IWQ vectows.
 *
 * Wwite IWQ count to device.
 */
void t7xx_pcie_set_mac_msix_cfg(stwuct t7xx_pci_dev *t7xx_dev, unsigned int iwq_count)
{
	u32 vaw = ffs(iwq_count) * 2 - 1;

	iowwite32(vaw, IWEG_BASE(t7xx_dev) + T7XX_PCIE_CFG_MSIX);
}
