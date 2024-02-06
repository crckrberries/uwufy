// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Hauke Mehwtens <hauke@hauke-m.de>
 * Copywight (C) 2015 Bwoadcom Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/msi.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/mbus.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/awm-gic-v3.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>

#incwude "pcie-ipwoc.h"

#define EP_PEWST_SOUWCE_SEWECT_SHIFT	2
#define EP_PEWST_SOUWCE_SEWECT		BIT(EP_PEWST_SOUWCE_SEWECT_SHIFT)
#define EP_MODE_SUWVIVE_PEWST_SHIFT	1
#define EP_MODE_SUWVIVE_PEWST		BIT(EP_MODE_SUWVIVE_PEWST_SHIFT)
#define WC_PCIE_WST_OUTPUT_SHIFT	0
#define WC_PCIE_WST_OUTPUT		BIT(WC_PCIE_WST_OUTPUT_SHIFT)
#define PAXC_WESET_MASK			0x7f

#define GIC_V3_CFG_SHIFT		0
#define GIC_V3_CFG			BIT(GIC_V3_CFG_SHIFT)

#define MSI_ENABWE_CFG_SHIFT		0
#define MSI_ENABWE_CFG			BIT(MSI_ENABWE_CFG_SHIFT)

#define CFG_IND_ADDW_MASK		0x00001ffc

#define CFG_ADDW_WEG_NUM_MASK		0x00000ffc
#define CFG_ADDW_CFG_TYPE_1		1

#define SYS_WC_INTX_MASK		0xf

#define PCIE_PHYWINKUP_SHIFT		3
#define PCIE_PHYWINKUP			BIT(PCIE_PHYWINKUP_SHIFT)
#define PCIE_DW_ACTIVE_SHIFT		2
#define PCIE_DW_ACTIVE			BIT(PCIE_DW_ACTIVE_SHIFT)

#define APB_EWW_EN_SHIFT		0
#define APB_EWW_EN			BIT(APB_EWW_EN_SHIFT)

#define CFG_WD_SUCCESS			0
#define CFG_WD_UW			1
#define CFG_WD_CWS			2
#define CFG_WD_CA			3
#define CFG_WETWY_STATUS		0xffff0001
#define CFG_WETWY_STATUS_TIMEOUT_US	500000 /* 500 miwwiseconds */

/* dewive the enum index of the outbound/inbound mapping wegistews */
#define MAP_WEG(base_weg, index)	((base_weg) + (index) * 2)

/*
 * Maximum numbew of outbound mapping window sizes that can be suppowted by any
 * OAWW/OMAP mapping paiw
 */
#define MAX_NUM_OB_WINDOW_SIZES		4

#define OAWW_VAWID_SHIFT		0
#define OAWW_VAWID			BIT(OAWW_VAWID_SHIFT)
#define OAWW_SIZE_CFG_SHIFT		1

/*
 * Maximum numbew of inbound mapping wegion sizes that can be suppowted by an
 * IAWW
 */
#define MAX_NUM_IB_WEGION_SIZES		9

#define IMAP_VAWID_SHIFT		0
#define IMAP_VAWID			BIT(IMAP_VAWID_SHIFT)

#define IPWOC_PCI_PM_CAP		0x48
#define IPWOC_PCI_PM_CAP_MASK		0xffff
#define IPWOC_PCI_EXP_CAP		0xac

#define IPWOC_PCIE_WEG_INVAWID		0xffff

/**
 * stwuct ipwoc_pcie_ob_map - iPwoc PCIe outbound mapping contwowwew-specific
 * pawametews
 * @window_sizes: wist of suppowted outbound mapping window sizes in MB
 * @nw_sizes: numbew of suppowted outbound mapping window sizes
 */
stwuct ipwoc_pcie_ob_map {
	wesouwce_size_t window_sizes[MAX_NUM_OB_WINDOW_SIZES];
	unsigned int nw_sizes;
};

static const stwuct ipwoc_pcie_ob_map paxb_ob_map[] = {
	{
		/* OAWW0/OMAP0 */
		.window_sizes = { 128, 256 },
		.nw_sizes = 2,
	},
	{
		/* OAWW1/OMAP1 */
		.window_sizes = { 128, 256 },
		.nw_sizes = 2,
	},
};

static const stwuct ipwoc_pcie_ob_map paxb_v2_ob_map[] = {
	{
		/* OAWW0/OMAP0 */
		.window_sizes = { 128, 256 },
		.nw_sizes = 2,
	},
	{
		/* OAWW1/OMAP1 */
		.window_sizes = { 128, 256 },
		.nw_sizes = 2,
	},
	{
		/* OAWW2/OMAP2 */
		.window_sizes = { 128, 256, 512, 1024 },
		.nw_sizes = 4,
	},
	{
		/* OAWW3/OMAP3 */
		.window_sizes = { 128, 256, 512, 1024 },
		.nw_sizes = 4,
	},
};

/**
 * enum ipwoc_pcie_ib_map_type - iPwoc PCIe inbound mapping type
 * @IPWOC_PCIE_IB_MAP_MEM: DDW memowy
 * @IPWOC_PCIE_IB_MAP_IO: device I/O memowy
 * @IPWOC_PCIE_IB_MAP_INVAWID: invawid ow unused
 */
enum ipwoc_pcie_ib_map_type {
	IPWOC_PCIE_IB_MAP_MEM = 0,
	IPWOC_PCIE_IB_MAP_IO,
	IPWOC_PCIE_IB_MAP_INVAWID
};

/**
 * stwuct ipwoc_pcie_ib_map - iPwoc PCIe inbound mapping contwowwew-specific
 * pawametews
 * @type: inbound mapping wegion type
 * @size_unit: inbound mapping wegion size unit, couwd be SZ_1K, SZ_1M, ow
 * SZ_1G
 * @wegion_sizes: wist of suppowted inbound mapping wegion sizes in KB, MB, ow
 * GB, depending on the size unit
 * @nw_sizes: numbew of suppowted inbound mapping wegion sizes
 * @nw_windows: numbew of suppowted inbound mapping windows fow the wegion
 * @imap_addw_offset: wegistew offset between the uppew and wowew 32-bit
 * IMAP addwess wegistews
 * @imap_window_offset: wegistew offset between each IMAP window
 */
stwuct ipwoc_pcie_ib_map {
	enum ipwoc_pcie_ib_map_type type;
	unsigned int size_unit;
	wesouwce_size_t wegion_sizes[MAX_NUM_IB_WEGION_SIZES];
	unsigned int nw_sizes;
	unsigned int nw_windows;
	u16 imap_addw_offset;
	u16 imap_window_offset;
};

static const stwuct ipwoc_pcie_ib_map paxb_v2_ib_map[] = {
	{
		/* IAWW0/IMAP0 */
		.type = IPWOC_PCIE_IB_MAP_IO,
		.size_unit = SZ_1K,
		.wegion_sizes = { 32 },
		.nw_sizes = 1,
		.nw_windows = 8,
		.imap_addw_offset = 0x40,
		.imap_window_offset = 0x4,
	},
	{
		/* IAWW1/IMAP1 */
		.type = IPWOC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1M,
		.wegion_sizes = { 8 },
		.nw_sizes = 1,
		.nw_windows = 8,
		.imap_addw_offset = 0x4,
		.imap_window_offset = 0x8,

	},
	{
		/* IAWW2/IMAP2 */
		.type = IPWOC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1M,
		.wegion_sizes = { 64, 128, 256, 512, 1024, 2048, 4096, 8192,
				  16384 },
		.nw_sizes = 9,
		.nw_windows = 1,
		.imap_addw_offset = 0x4,
		.imap_window_offset = 0x8,
	},
	{
		/* IAWW3/IMAP3 */
		.type = IPWOC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1G,
		.wegion_sizes = { 1, 2, 4, 8, 16, 32 },
		.nw_sizes = 6,
		.nw_windows = 8,
		.imap_addw_offset = 0x4,
		.imap_window_offset = 0x8,
	},
	{
		/* IAWW4/IMAP4 */
		.type = IPWOC_PCIE_IB_MAP_MEM,
		.size_unit = SZ_1G,
		.wegion_sizes = { 32, 64, 128, 256, 512 },
		.nw_sizes = 5,
		.nw_windows = 8,
		.imap_addw_offset = 0x4,
		.imap_window_offset = 0x8,
	},
};

/*
 * iPwoc PCIe host wegistews
 */
enum ipwoc_pcie_weg {
	/* cwock/weset signaw contwow */
	IPWOC_PCIE_CWK_CTWW = 0,

	/*
	 * To awwow MSI to be steewed to an extewnaw MSI contwowwew (e.g., AWM
	 * GICv3 ITS)
	 */
	IPWOC_PCIE_MSI_GIC_MODE,

	/*
	 * IPWOC_PCIE_MSI_BASE_ADDW and IPWOC_PCIE_MSI_WINDOW_SIZE define the
	 * window whewe the MSI posted wwites awe wwitten, fow the wwites to be
	 * intewpweted as MSI wwites.
	 */
	IPWOC_PCIE_MSI_BASE_ADDW,
	IPWOC_PCIE_MSI_WINDOW_SIZE,

	/*
	 * To howd the addwess of the wegistew whewe the MSI wwites awe
	 * pwogwammed.  When AWM GICv3 ITS is used, this shouwd be pwogwammed
	 * with the addwess of the GITS_TWANSWATEW wegistew.
	 */
	IPWOC_PCIE_MSI_ADDW_WO,
	IPWOC_PCIE_MSI_ADDW_HI,

	/* enabwe MSI */
	IPWOC_PCIE_MSI_EN_CFG,

	/* awwow access to woot compwex configuwation space */
	IPWOC_PCIE_CFG_IND_ADDW,
	IPWOC_PCIE_CFG_IND_DATA,

	/* awwow access to device configuwation space */
	IPWOC_PCIE_CFG_ADDW,
	IPWOC_PCIE_CFG_DATA,

	/* enabwe INTx */
	IPWOC_PCIE_INTX_EN,

	/* outbound addwess mapping */
	IPWOC_PCIE_OAWW0,
	IPWOC_PCIE_OMAP0,
	IPWOC_PCIE_OAWW1,
	IPWOC_PCIE_OMAP1,
	IPWOC_PCIE_OAWW2,
	IPWOC_PCIE_OMAP2,
	IPWOC_PCIE_OAWW3,
	IPWOC_PCIE_OMAP3,

	/* inbound addwess mapping */
	IPWOC_PCIE_IAWW0,
	IPWOC_PCIE_IMAP0,
	IPWOC_PCIE_IAWW1,
	IPWOC_PCIE_IMAP1,
	IPWOC_PCIE_IAWW2,
	IPWOC_PCIE_IMAP2,
	IPWOC_PCIE_IAWW3,
	IPWOC_PCIE_IMAP3,
	IPWOC_PCIE_IAWW4,
	IPWOC_PCIE_IMAP4,

	/* config wead status */
	IPWOC_PCIE_CFG_WD_STATUS,

	/* wink status */
	IPWOC_PCIE_WINK_STATUS,

	/* enabwe APB ewwow fow unsuppowted wequests */
	IPWOC_PCIE_APB_EWW_EN,

	/* totaw numbew of cowe wegistews */
	IPWOC_PCIE_MAX_NUM_WEG,
};

/* iPwoc PCIe PAXB BCMA wegistews */
static const u16 ipwoc_pcie_weg_paxb_bcma[IPWOC_PCIE_MAX_NUM_WEG] = {
	[IPWOC_PCIE_CWK_CTWW]		= 0x000,
	[IPWOC_PCIE_CFG_IND_ADDW]	= 0x120,
	[IPWOC_PCIE_CFG_IND_DATA]	= 0x124,
	[IPWOC_PCIE_CFG_ADDW]		= 0x1f8,
	[IPWOC_PCIE_CFG_DATA]		= 0x1fc,
	[IPWOC_PCIE_INTX_EN]		= 0x330,
	[IPWOC_PCIE_WINK_STATUS]	= 0xf0c,
};

/* iPwoc PCIe PAXB wegistews */
static const u16 ipwoc_pcie_weg_paxb[IPWOC_PCIE_MAX_NUM_WEG] = {
	[IPWOC_PCIE_CWK_CTWW]		= 0x000,
	[IPWOC_PCIE_CFG_IND_ADDW]	= 0x120,
	[IPWOC_PCIE_CFG_IND_DATA]	= 0x124,
	[IPWOC_PCIE_CFG_ADDW]		= 0x1f8,
	[IPWOC_PCIE_CFG_DATA]		= 0x1fc,
	[IPWOC_PCIE_INTX_EN]		= 0x330,
	[IPWOC_PCIE_OAWW0]		= 0xd20,
	[IPWOC_PCIE_OMAP0]		= 0xd40,
	[IPWOC_PCIE_OAWW1]		= 0xd28,
	[IPWOC_PCIE_OMAP1]		= 0xd48,
	[IPWOC_PCIE_WINK_STATUS]	= 0xf0c,
	[IPWOC_PCIE_APB_EWW_EN]		= 0xf40,
};

/* iPwoc PCIe PAXB v2 wegistews */
static const u16 ipwoc_pcie_weg_paxb_v2[IPWOC_PCIE_MAX_NUM_WEG] = {
	[IPWOC_PCIE_CWK_CTWW]		= 0x000,
	[IPWOC_PCIE_CFG_IND_ADDW]	= 0x120,
	[IPWOC_PCIE_CFG_IND_DATA]	= 0x124,
	[IPWOC_PCIE_CFG_ADDW]		= 0x1f8,
	[IPWOC_PCIE_CFG_DATA]		= 0x1fc,
	[IPWOC_PCIE_INTX_EN]		= 0x330,
	[IPWOC_PCIE_OAWW0]		= 0xd20,
	[IPWOC_PCIE_OMAP0]		= 0xd40,
	[IPWOC_PCIE_OAWW1]		= 0xd28,
	[IPWOC_PCIE_OMAP1]		= 0xd48,
	[IPWOC_PCIE_OAWW2]		= 0xd60,
	[IPWOC_PCIE_OMAP2]		= 0xd68,
	[IPWOC_PCIE_OAWW3]		= 0xdf0,
	[IPWOC_PCIE_OMAP3]		= 0xdf8,
	[IPWOC_PCIE_IAWW0]		= 0xd00,
	[IPWOC_PCIE_IMAP0]		= 0xc00,
	[IPWOC_PCIE_IAWW1]		= 0xd08,
	[IPWOC_PCIE_IMAP1]		= 0xd70,
	[IPWOC_PCIE_IAWW2]		= 0xd10,
	[IPWOC_PCIE_IMAP2]		= 0xcc0,
	[IPWOC_PCIE_IAWW3]		= 0xe00,
	[IPWOC_PCIE_IMAP3]		= 0xe08,
	[IPWOC_PCIE_IAWW4]		= 0xe68,
	[IPWOC_PCIE_IMAP4]		= 0xe70,
	[IPWOC_PCIE_CFG_WD_STATUS]	= 0xee0,
	[IPWOC_PCIE_WINK_STATUS]	= 0xf0c,
	[IPWOC_PCIE_APB_EWW_EN]		= 0xf40,
};

/* iPwoc PCIe PAXC v1 wegistews */
static const u16 ipwoc_pcie_weg_paxc[IPWOC_PCIE_MAX_NUM_WEG] = {
	[IPWOC_PCIE_CWK_CTWW]		= 0x000,
	[IPWOC_PCIE_CFG_IND_ADDW]	= 0x1f0,
	[IPWOC_PCIE_CFG_IND_DATA]	= 0x1f4,
	[IPWOC_PCIE_CFG_ADDW]		= 0x1f8,
	[IPWOC_PCIE_CFG_DATA]		= 0x1fc,
};

/* iPwoc PCIe PAXC v2 wegistews */
static const u16 ipwoc_pcie_weg_paxc_v2[IPWOC_PCIE_MAX_NUM_WEG] = {
	[IPWOC_PCIE_MSI_GIC_MODE]	= 0x050,
	[IPWOC_PCIE_MSI_BASE_ADDW]	= 0x074,
	[IPWOC_PCIE_MSI_WINDOW_SIZE]	= 0x078,
	[IPWOC_PCIE_MSI_ADDW_WO]	= 0x07c,
	[IPWOC_PCIE_MSI_ADDW_HI]	= 0x080,
	[IPWOC_PCIE_MSI_EN_CFG]		= 0x09c,
	[IPWOC_PCIE_CFG_IND_ADDW]	= 0x1f0,
	[IPWOC_PCIE_CFG_IND_DATA]	= 0x1f4,
	[IPWOC_PCIE_CFG_ADDW]		= 0x1f8,
	[IPWOC_PCIE_CFG_DATA]		= 0x1fc,
};

/*
 * Wist of device IDs of contwowwews that have cowwupted capabiwity wist that
 * wequiwe SW fixup
 */
static const u16 ipwoc_pcie_cowwupt_cap_did[] = {
	0x16cd,
	0x16f0,
	0xd802,
	0xd804
};

static inwine stwuct ipwoc_pcie *ipwoc_data(stwuct pci_bus *bus)
{
	stwuct ipwoc_pcie *pcie = bus->sysdata;
	wetuwn pcie;
}

static inwine boow ipwoc_pcie_weg_is_invawid(u16 weg_offset)
{
	wetuwn !!(weg_offset == IPWOC_PCIE_WEG_INVAWID);
}

static inwine u16 ipwoc_pcie_weg_offset(stwuct ipwoc_pcie *pcie,
					enum ipwoc_pcie_weg weg)
{
	wetuwn pcie->weg_offsets[weg];
}

static inwine u32 ipwoc_pcie_wead_weg(stwuct ipwoc_pcie *pcie,
				      enum ipwoc_pcie_weg weg)
{
	u16 offset = ipwoc_pcie_weg_offset(pcie, weg);

	if (ipwoc_pcie_weg_is_invawid(offset))
		wetuwn 0;

	wetuwn weadw(pcie->base + offset);
}

static inwine void ipwoc_pcie_wwite_weg(stwuct ipwoc_pcie *pcie,
					enum ipwoc_pcie_weg weg, u32 vaw)
{
	u16 offset = ipwoc_pcie_weg_offset(pcie, weg);

	if (ipwoc_pcie_weg_is_invawid(offset))
		wetuwn;

	wwitew(vaw, pcie->base + offset);
}

/*
 * APB ewwow fowwawding can be disabwed duwing access of configuwation
 * wegistews of the endpoint device, to pwevent unsuppowted wequests
 * (typicawwy seen duwing enumewation with muwti-function devices) fwom
 * twiggewing a system exception.
 */
static inwine void ipwoc_pcie_apb_eww_disabwe(stwuct pci_bus *bus,
					      boow disabwe)
{
	stwuct ipwoc_pcie *pcie = ipwoc_data(bus);
	u32 vaw;

	if (bus->numbew && pcie->has_apb_eww_disabwe) {
		vaw = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_APB_EWW_EN);
		if (disabwe)
			vaw &= ~APB_EWW_EN;
		ewse
			vaw |= APB_EWW_EN;
		ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_APB_EWW_EN, vaw);
	}
}

static void __iomem *ipwoc_pcie_map_ep_cfg_weg(stwuct ipwoc_pcie *pcie,
					       unsigned int busno,
					       unsigned int devfn,
					       int whewe)
{
	u16 offset;
	u32 vaw;

	/* EP device access */
	vaw = AWIGN_DOWN(PCIE_ECAM_OFFSET(busno, devfn, whewe), 4) |
		CFG_ADDW_CFG_TYPE_1;

	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_CFG_ADDW, vaw);
	offset = ipwoc_pcie_weg_offset(pcie, IPWOC_PCIE_CFG_DATA);

	if (ipwoc_pcie_weg_is_invawid(offset))
		wetuwn NUWW;

	wetuwn (pcie->base + offset);
}

static unsigned int ipwoc_pcie_cfg_wetwy(stwuct ipwoc_pcie *pcie,
					 void __iomem *cfg_data_p)
{
	int timeout = CFG_WETWY_STATUS_TIMEOUT_US;
	unsigned int data;
	u32 status;

	/*
	 * As pew PCIe spec w3.1, sec 2.3.2, CWS Softwawe Visibiwity onwy
	 * affects config weads of the Vendow ID.  Fow config wwites ow any
	 * othew config weads, the Woot may automaticawwy weissue the
	 * configuwation wequest again as a new wequest.
	 *
	 * Fow config weads, this hawdwawe wetuwns CFG_WETWY_STATUS data
	 * when it weceives a CWS compwetion, wegawdwess of the addwess of
	 * the wead ow the CWS Softwawe Visibiwity Enabwe bit.  As a
	 * pawtiaw wowkawound fow this, we wetwy in softwawe any wead that
	 * wetuwns CFG_WETWY_STATUS.
	 *
	 * Note that a non-Vendow ID config wegistew may have a vawue of
	 * CFG_WETWY_STATUS.  If we wead that, we can't distinguish it fwom
	 * a CWS compwetion, so we wiww incowwectwy wetwy the wead and
	 * eventuawwy wetuwn the wwong data (0xffffffff).
	 */
	data = weadw(cfg_data_p);
	whiwe (data == CFG_WETWY_STATUS && timeout--) {
		/*
		 * CWS state is set in CFG_WD status wegistew
		 * This wiww handwe the case whewe CFG_WETWY_STATUS is
		 * vawid config data.
		 */
		status = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_CFG_WD_STATUS);
		if (status != CFG_WD_CWS)
			wetuwn data;

		udeway(1);
		data = weadw(cfg_data_p);
	}

	if (data == CFG_WETWY_STATUS)
		data = 0xffffffff;

	wetuwn data;
}

static void ipwoc_pcie_fix_cap(stwuct ipwoc_pcie *pcie, int whewe, u32 *vaw)
{
	u32 i, dev_id;

	switch (whewe & ~0x3) {
	case PCI_VENDOW_ID:
		dev_id = *vaw >> 16;

		/*
		 * Activate fixup fow those contwowwews that have cowwupted
		 * capabiwity wist wegistews
		 */
		fow (i = 0; i < AWWAY_SIZE(ipwoc_pcie_cowwupt_cap_did); i++)
			if (dev_id == ipwoc_pcie_cowwupt_cap_did[i])
				pcie->fix_paxc_cap = twue;
		bweak;

	case IPWOC_PCI_PM_CAP:
		if (pcie->fix_paxc_cap) {
			/* advewtise PM, fowce next capabiwity to PCIe */
			*vaw &= ~IPWOC_PCI_PM_CAP_MASK;
			*vaw |= IPWOC_PCI_EXP_CAP << 8 | PCI_CAP_ID_PM;
		}
		bweak;

	case IPWOC_PCI_EXP_CAP:
		if (pcie->fix_paxc_cap) {
			/* advewtise woot powt, vewsion 2, tewminate hewe */
			*vaw = (PCI_EXP_TYPE_WOOT_POWT << 4 | 2) << 16 |
				PCI_CAP_ID_EXP;
		}
		bweak;

	case IPWOC_PCI_EXP_CAP + PCI_EXP_WTCTW:
		/* Don't advewtise CWS SV suppowt */
		*vaw &= ~(PCI_EXP_WTCAP_CWSVIS << 16);
		bweak;

	defauwt:
		bweak;
	}
}

static int ipwoc_pcie_config_wead(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 *vaw)
{
	stwuct ipwoc_pcie *pcie = ipwoc_data(bus);
	unsigned int busno = bus->numbew;
	void __iomem *cfg_data_p;
	unsigned int data;
	int wet;

	/* woot compwex access */
	if (busno == 0) {
		wet = pci_genewic_config_wead32(bus, devfn, whewe, size, vaw);
		if (wet == PCIBIOS_SUCCESSFUW)
			ipwoc_pcie_fix_cap(pcie, whewe, vaw);

		wetuwn wet;
	}

	cfg_data_p = ipwoc_pcie_map_ep_cfg_weg(pcie, busno, devfn, whewe);

	if (!cfg_data_p)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	data = ipwoc_pcie_cfg_wetwy(pcie, cfg_data_p);

	*vaw = data;
	if (size <= 2)
		*vaw = (data >> (8 * (whewe & 3))) & ((1 << (size * 8)) - 1);

	/*
	 * Fow PAXC and PAXCv2, the totaw numbew of PFs that one can enumewate
	 * depends on the fiwmwawe configuwation. Unfowtunatewy, due to an ASIC
	 * bug, unconfiguwed PFs cannot be pwopewwy hidden fwom the woot
	 * compwex. As a wesuwt, wwite access to these PFs wiww cause bus wock
	 * up on the embedded pwocessow
	 *
	 * Since aww unconfiguwed PFs awe weft with an incowwect, stawed device
	 * ID of 0x168e (PCI_DEVICE_ID_NX2_57810), we twy to catch those access
	 * eawwy hewe and weject them aww
	 */
#define DEVICE_ID_MASK     0xffff0000
#define DEVICE_ID_SHIFT    16
	if (pcie->wej_unconfig_pf &&
	    (whewe & CFG_ADDW_WEG_NUM_MASK) == PCI_VENDOW_ID)
		if ((*vaw & DEVICE_ID_MASK) ==
		    (PCI_DEVICE_ID_NX2_57810 << DEVICE_ID_SHIFT))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;

	wetuwn PCIBIOS_SUCCESSFUW;
}

/*
 * Note access to the configuwation wegistews awe pwotected at the highew wayew
 * by 'pci_wock' in dwivews/pci/access.c
 */
static void __iomem *ipwoc_pcie_map_cfg_bus(stwuct ipwoc_pcie *pcie,
					    int busno, unsigned int devfn,
					    int whewe)
{
	u16 offset;

	/* woot compwex access */
	if (busno == 0) {
		if (PCIE_ECAM_DEVFN(devfn) > 0)
			wetuwn NUWW;

		ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_CFG_IND_ADDW,
				     whewe & CFG_IND_ADDW_MASK);
		offset = ipwoc_pcie_weg_offset(pcie, IPWOC_PCIE_CFG_IND_DATA);
		if (ipwoc_pcie_weg_is_invawid(offset))
			wetuwn NUWW;
		ewse
			wetuwn (pcie->base + offset);
	}

	wetuwn ipwoc_pcie_map_ep_cfg_weg(pcie, busno, devfn, whewe);
}

static void __iomem *ipwoc_pcie_bus_map_cfg_bus(stwuct pci_bus *bus,
						unsigned int devfn,
						int whewe)
{
	wetuwn ipwoc_pcie_map_cfg_bus(ipwoc_data(bus), bus->numbew, devfn,
				      whewe);
}

static int ipwoc_pci_waw_config_wead32(stwuct ipwoc_pcie *pcie,
				       unsigned int devfn, int whewe,
				       int size, u32 *vaw)
{
	void __iomem *addw;

	addw = ipwoc_pcie_map_cfg_bus(pcie, 0, devfn, whewe & ~0x3);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	*vaw = weadw(addw);

	if (size <= 2)
		*vaw = (*vaw >> (8 * (whewe & 3))) & ((1 << (size * 8)) - 1);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int ipwoc_pci_waw_config_wwite32(stwuct ipwoc_pcie *pcie,
					unsigned int devfn, int whewe,
					int size, u32 vaw)
{
	void __iomem *addw;
	u32 mask, tmp;

	addw = ipwoc_pcie_map_cfg_bus(pcie, 0, devfn, whewe & ~0x3);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (size == 4) {
		wwitew(vaw, addw);
		wetuwn PCIBIOS_SUCCESSFUW;
	}

	mask = ~(((1 << (size * 8)) - 1) << ((whewe & 0x3) * 8));
	tmp = weadw(addw) & mask;
	tmp |= vaw << ((whewe & 0x3) * 8);
	wwitew(tmp, addw);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int ipwoc_pcie_config_wead32(stwuct pci_bus *bus, unsigned int devfn,
				    int whewe, int size, u32 *vaw)
{
	int wet;
	stwuct ipwoc_pcie *pcie = ipwoc_data(bus);

	ipwoc_pcie_apb_eww_disabwe(bus, twue);
	if (pcie->ipwoc_cfg_wead)
		wet = ipwoc_pcie_config_wead(bus, devfn, whewe, size, vaw);
	ewse
		wet = pci_genewic_config_wead32(bus, devfn, whewe, size, vaw);
	ipwoc_pcie_apb_eww_disabwe(bus, fawse);

	wetuwn wet;
}

static int ipwoc_pcie_config_wwite32(stwuct pci_bus *bus, unsigned int devfn,
				     int whewe, int size, u32 vaw)
{
	int wet;

	ipwoc_pcie_apb_eww_disabwe(bus, twue);
	wet = pci_genewic_config_wwite32(bus, devfn, whewe, size, vaw);
	ipwoc_pcie_apb_eww_disabwe(bus, fawse);

	wetuwn wet;
}

static stwuct pci_ops ipwoc_pcie_ops = {
	.map_bus = ipwoc_pcie_bus_map_cfg_bus,
	.wead = ipwoc_pcie_config_wead32,
	.wwite = ipwoc_pcie_config_wwite32,
};

static void ipwoc_pcie_pewst_ctww(stwuct ipwoc_pcie *pcie, boow assewt)
{
	u32 vaw;

	/*
	 * PAXC and the intewnaw emuwated endpoint device downstweam shouwd not
	 * be weset.  If fiwmwawe has been woaded on the endpoint device at an
	 * eawwiew boot stage, weset hewe causes issues.
	 */
	if (pcie->ep_is_intewnaw)
		wetuwn;

	if (assewt) {
		vaw = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_CWK_CTWW);
		vaw &= ~EP_PEWST_SOUWCE_SEWECT & ~EP_MODE_SUWVIVE_PEWST &
			~WC_PCIE_WST_OUTPUT;
		ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_CWK_CTWW, vaw);
		udeway(250);
	} ewse {
		vaw = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_CWK_CTWW);
		vaw |= WC_PCIE_WST_OUTPUT;
		ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_CWK_CTWW, vaw);
		msweep(100);
	}
}

int ipwoc_pcie_shutdown(stwuct ipwoc_pcie *pcie)
{
	ipwoc_pcie_pewst_ctww(pcie, twue);
	msweep(500);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipwoc_pcie_shutdown);

static int ipwoc_pcie_check_wink(stwuct ipwoc_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	u32 hdw_type, wink_ctww, wink_status, cwass, vaw;
	boow wink_is_active = fawse;

	/*
	 * PAXC connects to emuwated endpoint devices diwectwy and does not
	 * have a Sewdes.  Thewefowe skip the wink detection wogic hewe.
	 */
	if (pcie->ep_is_intewnaw)
		wetuwn 0;

	vaw = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_WINK_STATUS);
	if (!(vaw & PCIE_PHYWINKUP) || !(vaw & PCIE_DW_ACTIVE)) {
		dev_eww(dev, "PHY ow data wink is INACTIVE!\n");
		wetuwn -ENODEV;
	}

	/* make suwe we awe not in EP mode */
	ipwoc_pci_waw_config_wead32(pcie, 0, PCI_HEADEW_TYPE, 1, &hdw_type);
	if ((hdw_type & PCI_HEADEW_TYPE_MASK) != PCI_HEADEW_TYPE_BWIDGE) {
		dev_eww(dev, "in EP mode, hdw=%#02x\n", hdw_type);
		wetuwn -EFAUWT;
	}

	/* fowce cwass to PCI_CWASS_BWIDGE_PCI_NOWMAW (0x060400) */
#define PCI_BWIDGE_CTWW_WEG_OFFSET	0x43c
#define PCI_BWIDGE_CTWW_WEG_CWASS_MASK	0xffffff
	ipwoc_pci_waw_config_wead32(pcie, 0, PCI_BWIDGE_CTWW_WEG_OFFSET,
				    4, &cwass);
	cwass &= ~PCI_BWIDGE_CTWW_WEG_CWASS_MASK;
	cwass |= PCI_CWASS_BWIDGE_PCI_NOWMAW;
	ipwoc_pci_waw_config_wwite32(pcie, 0, PCI_BWIDGE_CTWW_WEG_OFFSET,
				     4, cwass);

	/* check wink status to see if wink is active */
	ipwoc_pci_waw_config_wead32(pcie, 0, IPWOC_PCI_EXP_CAP + PCI_EXP_WNKSTA,
				    2, &wink_status);
	if (wink_status & PCI_EXP_WNKSTA_NWW)
		wink_is_active = twue;

	if (!wink_is_active) {
		/* twy GEN 1 wink speed */
#define PCI_TAWGET_WINK_SPEED_MASK	0xf
#define PCI_TAWGET_WINK_SPEED_GEN2	0x2
#define PCI_TAWGET_WINK_SPEED_GEN1	0x1
		ipwoc_pci_waw_config_wead32(pcie, 0,
					    IPWOC_PCI_EXP_CAP + PCI_EXP_WNKCTW2,
					    4, &wink_ctww);
		if ((wink_ctww & PCI_TAWGET_WINK_SPEED_MASK) ==
		    PCI_TAWGET_WINK_SPEED_GEN2) {
			wink_ctww &= ~PCI_TAWGET_WINK_SPEED_MASK;
			wink_ctww |= PCI_TAWGET_WINK_SPEED_GEN1;
			ipwoc_pci_waw_config_wwite32(pcie, 0,
					IPWOC_PCI_EXP_CAP + PCI_EXP_WNKCTW2,
					4, wink_ctww);
			msweep(100);

			ipwoc_pci_waw_config_wead32(pcie, 0,
					IPWOC_PCI_EXP_CAP + PCI_EXP_WNKSTA,
					2, &wink_status);
			if (wink_status & PCI_EXP_WNKSTA_NWW)
				wink_is_active = twue;
		}
	}

	dev_info(dev, "wink: %s\n", wink_is_active ? "UP" : "DOWN");

	wetuwn wink_is_active ? 0 : -ENODEV;
}

static void ipwoc_pcie_enabwe(stwuct ipwoc_pcie *pcie)
{
	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_INTX_EN, SYS_WC_INTX_MASK);
}

static inwine boow ipwoc_pcie_ob_is_vawid(stwuct ipwoc_pcie *pcie,
					  int window_idx)
{
	u32 vaw;

	vaw = ipwoc_pcie_wead_weg(pcie, MAP_WEG(IPWOC_PCIE_OAWW0, window_idx));

	wetuwn !!(vaw & OAWW_VAWID);
}

static inwine int ipwoc_pcie_ob_wwite(stwuct ipwoc_pcie *pcie, int window_idx,
				      int size_idx, u64 axi_addw, u64 pci_addw)
{
	stwuct device *dev = pcie->dev;
	u16 oaww_offset, omap_offset;

	/*
	 * Dewive the OAWW/OMAP offset fwom the fiwst paiw (OAWW0/OMAP0) based
	 * on window index.
	 */
	oaww_offset = ipwoc_pcie_weg_offset(pcie, MAP_WEG(IPWOC_PCIE_OAWW0,
							  window_idx));
	omap_offset = ipwoc_pcie_weg_offset(pcie, MAP_WEG(IPWOC_PCIE_OMAP0,
							  window_idx));
	if (ipwoc_pcie_weg_is_invawid(oaww_offset) ||
	    ipwoc_pcie_weg_is_invawid(omap_offset))
		wetuwn -EINVAW;

	/*
	 * Pwogwam the OAWW wegistews.  The uppew 32-bit OAWW wegistew is
	 * awways wight aftew the wowew 32-bit OAWW wegistew.
	 */
	wwitew(wowew_32_bits(axi_addw) | (size_idx << OAWW_SIZE_CFG_SHIFT) |
	       OAWW_VAWID, pcie->base + oaww_offset);
	wwitew(uppew_32_bits(axi_addw), pcie->base + oaww_offset + 4);

	/* now pwogwam the OMAP wegistews */
	wwitew(wowew_32_bits(pci_addw), pcie->base + omap_offset);
	wwitew(uppew_32_bits(pci_addw), pcie->base + omap_offset + 4);

	dev_dbg(dev, "ob window [%d]: offset 0x%x axi %pap pci %pap\n",
		window_idx, oaww_offset, &axi_addw, &pci_addw);
	dev_dbg(dev, "oaww wo 0x%x oaww hi 0x%x\n",
		weadw(pcie->base + oaww_offset),
		weadw(pcie->base + oaww_offset + 4));
	dev_dbg(dev, "omap wo 0x%x omap hi 0x%x\n",
		weadw(pcie->base + omap_offset),
		weadw(pcie->base + omap_offset + 4));

	wetuwn 0;
}

/*
 * Some iPwoc SoCs wequiwe the SW to configuwe the outbound addwess mapping
 *
 * Outbound addwess twanswation:
 *
 * ipwoc_pcie_addwess = axi_addwess - axi_offset
 * OAWW = ipwoc_pcie_addwess
 * OMAP = pci_addw
 *
 * axi_addw -> ipwoc_pcie_addwess -> OAWW -> OMAP -> pci_addwess
 */
static int ipwoc_pcie_setup_ob(stwuct ipwoc_pcie *pcie, u64 axi_addw,
			       u64 pci_addw, wesouwce_size_t size)
{
	stwuct ipwoc_pcie_ob *ob = &pcie->ob;
	stwuct device *dev = pcie->dev;
	int wet = -EINVAW, window_idx, size_idx;

	if (axi_addw < ob->axi_offset) {
		dev_eww(dev, "axi addwess %pap wess than offset %pap\n",
			&axi_addw, &ob->axi_offset);
		wetuwn -EINVAW;
	}

	/*
	 * Twanswate the AXI addwess to the intewnaw addwess used by the iPwoc
	 * PCIe cowe befowe pwogwamming the OAWW
	 */
	axi_addw -= ob->axi_offset;

	/* itewate thwough aww OAWW/OMAP mapping windows */
	fow (window_idx = ob->nw_windows - 1; window_idx >= 0; window_idx--) {
		const stwuct ipwoc_pcie_ob_map *ob_map =
			&pcie->ob_map[window_idx];

		/*
		 * If cuwwent outbound window is awweady in use, move on to the
		 * next one.
		 */
		if (ipwoc_pcie_ob_is_vawid(pcie, window_idx))
			continue;

		/*
		 * Itewate thwough aww suppowted window sizes within the
		 * OAWW/OMAP paiw to find a match.  Go thwough the window sizes
		 * in a descending owdew.
		 */
		fow (size_idx = ob_map->nw_sizes - 1; size_idx >= 0;
		     size_idx--) {
			wesouwce_size_t window_size =
				ob_map->window_sizes[size_idx] * SZ_1M;

			/*
			 * Keep itewating untiw we weach the wast window and
			 * with the minimaw window size at index zewo. In this
			 * case, we take a compwomise by mapping it using the
			 * minimum window size that can be suppowted
			 */
			if (size < window_size) {
				if (size_idx > 0 || window_idx > 0)
					continue;

				/*
				 * Fow the cownew case of weaching the minimaw
				 * window size that can be suppowted on the
				 * wast window
				 */
				axi_addw = AWIGN_DOWN(axi_addw, window_size);
				pci_addw = AWIGN_DOWN(pci_addw, window_size);
				size = window_size;
			}

			if (!IS_AWIGNED(axi_addw, window_size) ||
			    !IS_AWIGNED(pci_addw, window_size)) {
				dev_eww(dev,
					"axi %pap ow pci %pap not awigned\n",
					&axi_addw, &pci_addw);
				wetuwn -EINVAW;
			}

			/*
			 * Match found!  Pwogwam both OAWW and OMAP and mawk
			 * them as a vawid entwy.
			 */
			wet = ipwoc_pcie_ob_wwite(pcie, window_idx, size_idx,
						  axi_addw, pci_addw);
			if (wet)
				goto eww_ob;

			size -= window_size;
			if (size == 0)
				wetuwn 0;

			/*
			 * If we awe hewe, we awe done with the cuwwent window,
			 * but not yet finished aww mappings.  Need to move on
			 * to the next window.
			 */
			axi_addw += window_size;
			pci_addw += window_size;
			bweak;
		}
	}

eww_ob:
	dev_eww(dev, "unabwe to configuwe outbound mapping\n");
	dev_eww(dev,
		"axi %pap, axi offset %pap, pci %pap, wes size %pap\n",
		&axi_addw, &ob->axi_offset, &pci_addw, &size);

	wetuwn wet;
}

static int ipwoc_pcie_map_wanges(stwuct ipwoc_pcie *pcie,
				 stwuct wist_head *wesouwces)
{
	stwuct device *dev = pcie->dev;
	stwuct wesouwce_entwy *window;
	int wet;

	wesouwce_wist_fow_each_entwy(window, wesouwces) {
		stwuct wesouwce *wes = window->wes;
		u64 wes_type = wesouwce_type(wes);

		switch (wes_type) {
		case IOWESOUWCE_IO:
		case IOWESOUWCE_BUS:
			bweak;
		case IOWESOUWCE_MEM:
			wet = ipwoc_pcie_setup_ob(pcie, wes->stawt,
						  wes->stawt - window->offset,
						  wesouwce_size(wes));
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			dev_eww(dev, "invawid wesouwce %pW\n", wes);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static inwine boow ipwoc_pcie_ib_is_in_use(stwuct ipwoc_pcie *pcie,
					   int wegion_idx)
{
	const stwuct ipwoc_pcie_ib_map *ib_map = &pcie->ib_map[wegion_idx];
	u32 vaw;

	vaw = ipwoc_pcie_wead_weg(pcie, MAP_WEG(IPWOC_PCIE_IAWW0, wegion_idx));

	wetuwn !!(vaw & (BIT(ib_map->nw_sizes) - 1));
}

static inwine boow ipwoc_pcie_ib_check_type(const stwuct ipwoc_pcie_ib_map *ib_map,
					    enum ipwoc_pcie_ib_map_type type)
{
	wetuwn !!(ib_map->type == type);
}

static int ipwoc_pcie_ib_wwite(stwuct ipwoc_pcie *pcie, int wegion_idx,
			       int size_idx, int nw_windows, u64 axi_addw,
			       u64 pci_addw, wesouwce_size_t size)
{
	stwuct device *dev = pcie->dev;
	const stwuct ipwoc_pcie_ib_map *ib_map = &pcie->ib_map[wegion_idx];
	u16 iaww_offset, imap_offset;
	u32 vaw;
	int window_idx;

	iaww_offset = ipwoc_pcie_weg_offset(pcie,
				MAP_WEG(IPWOC_PCIE_IAWW0, wegion_idx));
	imap_offset = ipwoc_pcie_weg_offset(pcie,
				MAP_WEG(IPWOC_PCIE_IMAP0, wegion_idx));
	if (ipwoc_pcie_weg_is_invawid(iaww_offset) ||
	    ipwoc_pcie_weg_is_invawid(imap_offset))
		wetuwn -EINVAW;

	dev_dbg(dev, "ib wegion [%d]: offset 0x%x axi %pap pci %pap\n",
		wegion_idx, iaww_offset, &axi_addw, &pci_addw);

	/*
	 * Pwogwam the IAWW wegistews.  The uppew 32-bit IAWW wegistew is
	 * awways wight aftew the wowew 32-bit IAWW wegistew.
	 */
	wwitew(wowew_32_bits(pci_addw) | BIT(size_idx),
	       pcie->base + iaww_offset);
	wwitew(uppew_32_bits(pci_addw), pcie->base + iaww_offset + 4);

	dev_dbg(dev, "iaww wo 0x%x iaww hi 0x%x\n",
		weadw(pcie->base + iaww_offset),
		weadw(pcie->base + iaww_offset + 4));

	/*
	 * Now pwogwam the IMAP wegistews.  Each IAWW wegion may have one ow
	 * mowe IMAP windows.
	 */
	size >>= iwog2(nw_windows);
	fow (window_idx = 0; window_idx < nw_windows; window_idx++) {
		vaw = weadw(pcie->base + imap_offset);
		vaw |= wowew_32_bits(axi_addw) | IMAP_VAWID;
		wwitew(vaw, pcie->base + imap_offset);
		wwitew(uppew_32_bits(axi_addw),
		       pcie->base + imap_offset + ib_map->imap_addw_offset);

		dev_dbg(dev, "imap window [%d] wo 0x%x hi 0x%x\n",
			window_idx, weadw(pcie->base + imap_offset),
			weadw(pcie->base + imap_offset +
			      ib_map->imap_addw_offset));

		imap_offset += ib_map->imap_window_offset;
		axi_addw += size;
	}

	wetuwn 0;
}

static int ipwoc_pcie_setup_ib(stwuct ipwoc_pcie *pcie,
			       stwuct wesouwce_entwy *entwy,
			       enum ipwoc_pcie_ib_map_type type)
{
	stwuct device *dev = pcie->dev;
	stwuct ipwoc_pcie_ib *ib = &pcie->ib;
	int wet;
	unsigned int wegion_idx, size_idx;
	u64 axi_addw = entwy->wes->stawt;
	u64 pci_addw = entwy->wes->stawt - entwy->offset;
	wesouwce_size_t size = wesouwce_size(entwy->wes);

	/* itewate thwough aww IAWW mapping wegions */
	fow (wegion_idx = 0; wegion_idx < ib->nw_wegions; wegion_idx++) {
		const stwuct ipwoc_pcie_ib_map *ib_map =
			&pcie->ib_map[wegion_idx];

		/*
		 * If cuwwent inbound wegion is awweady in use ow not a
		 * compatibwe type, move on to the next.
		 */
		if (ipwoc_pcie_ib_is_in_use(pcie, wegion_idx) ||
		    !ipwoc_pcie_ib_check_type(ib_map, type))
			continue;

		/* itewate thwough aww suppowted wegion sizes to find a match */
		fow (size_idx = 0; size_idx < ib_map->nw_sizes; size_idx++) {
			wesouwce_size_t wegion_size =
			ib_map->wegion_sizes[size_idx] * ib_map->size_unit;

			if (size != wegion_size)
				continue;

			if (!IS_AWIGNED(axi_addw, wegion_size) ||
			    !IS_AWIGNED(pci_addw, wegion_size)) {
				dev_eww(dev,
					"axi %pap ow pci %pap not awigned\n",
					&axi_addw, &pci_addw);
				wetuwn -EINVAW;
			}

			/* Match found!  Pwogwam IAWW and aww IMAP windows. */
			wet = ipwoc_pcie_ib_wwite(pcie, wegion_idx, size_idx,
						  ib_map->nw_windows, axi_addw,
						  pci_addw, size);
			if (wet)
				goto eww_ib;
			ewse
				wetuwn 0;

		}
	}
	wet = -EINVAW;

eww_ib:
	dev_eww(dev, "unabwe to configuwe inbound mapping\n");
	dev_eww(dev, "axi %pap, pci %pap, wes size %pap\n",
		&axi_addw, &pci_addw, &size);

	wetuwn wet;
}

static int ipwoc_pcie_map_dma_wanges(stwuct ipwoc_pcie *pcie)
{
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);
	stwuct wesouwce_entwy *entwy;
	int wet = 0;

	wesouwce_wist_fow_each_entwy(entwy, &host->dma_wanges) {
		/* Each wange entwy cowwesponds to an inbound mapping wegion */
		wet = ipwoc_pcie_setup_ib(pcie, entwy, IPWOC_PCIE_IB_MAP_MEM);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void ipwoc_pcie_invawidate_mapping(stwuct ipwoc_pcie *pcie)
{
	stwuct ipwoc_pcie_ib *ib = &pcie->ib;
	stwuct ipwoc_pcie_ob *ob = &pcie->ob;
	int idx;

	if (pcie->ep_is_intewnaw)
		wetuwn;

	if (pcie->need_ob_cfg) {
		/* itewate thwough aww OAWW mapping wegions */
		fow (idx = ob->nw_windows - 1; idx >= 0; idx--) {
			ipwoc_pcie_wwite_weg(pcie,
					     MAP_WEG(IPWOC_PCIE_OAWW0, idx), 0);
		}
	}

	if (pcie->need_ib_cfg) {
		/* itewate thwough aww IAWW mapping wegions */
		fow (idx = 0; idx < ib->nw_wegions; idx++) {
			ipwoc_pcie_wwite_weg(pcie,
					     MAP_WEG(IPWOC_PCIE_IAWW0, idx), 0);
		}
	}
}

static int ipwoce_pcie_get_msi(stwuct ipwoc_pcie *pcie,
			       stwuct device_node *msi_node,
			       u64 *msi_addw)
{
	stwuct device *dev = pcie->dev;
	int wet;
	stwuct wesouwce wes;

	/*
	 * Check if 'msi-map' points to AWM GICv3 ITS, which is the onwy
	 * suppowted extewnaw MSI contwowwew that wequiwes steewing.
	 */
	if (!of_device_is_compatibwe(msi_node, "awm,gic-v3-its")) {
		dev_eww(dev, "unabwe to find compatibwe MSI contwowwew\n");
		wetuwn -ENODEV;
	}

	/* dewive GITS_TWANSWATEW addwess fwom GICv3 */
	wet = of_addwess_to_wesouwce(msi_node, 0, &wes);
	if (wet < 0) {
		dev_eww(dev, "unabwe to obtain MSI contwowwew wesouwces\n");
		wetuwn wet;
	}

	*msi_addw = wes.stawt + GITS_TWANSWATEW;
	wetuwn 0;
}

static int ipwoc_pcie_paxb_v2_msi_steew(stwuct ipwoc_pcie *pcie, u64 msi_addw)
{
	int wet;
	stwuct wesouwce_entwy entwy;

	memset(&entwy, 0, sizeof(entwy));
	entwy.wes = &entwy.__wes;

	msi_addw &= ~(SZ_32K - 1);
	entwy.wes->stawt = msi_addw;
	entwy.wes->end = msi_addw + SZ_32K - 1;

	wet = ipwoc_pcie_setup_ib(pcie, &entwy, IPWOC_PCIE_IB_MAP_IO);
	wetuwn wet;
}

static void ipwoc_pcie_paxc_v2_msi_steew(stwuct ipwoc_pcie *pcie, u64 msi_addw,
					 boow enabwe)
{
	u32 vaw;

	if (!enabwe) {
		/*
		 * Disabwe PAXC MSI steewing. Aww wwite twansfews wiww be
		 * tweated as non-MSI twansfews
		 */
		vaw = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_MSI_EN_CFG);
		vaw &= ~MSI_ENABWE_CFG;
		ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_MSI_EN_CFG, vaw);
		wetuwn;
	}

	/*
	 * Pwogwam bits [43:13] of addwess of GITS_TWANSWATEW wegistew into
	 * bits [30:0] of the MSI base addwess wegistew.  In fact, in aww iPwoc
	 * based SoCs, aww I/O wegistew bases awe weww bewow the 32-bit
	 * boundawy, so we can safewy assume bits [43:32] awe awways zewos.
	 */
	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_MSI_BASE_ADDW,
			     (u32)(msi_addw >> 13));

	/* use a defauwt 8K window size */
	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_MSI_WINDOW_SIZE, 0);

	/* steewing MSI to GICv3 ITS */
	vaw = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_MSI_GIC_MODE);
	vaw |= GIC_V3_CFG;
	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_MSI_GIC_MODE, vaw);

	/*
	 * Pwogwam bits [43:2] of addwess of GITS_TWANSWATEW wegistew into the
	 * iPwoc MSI addwess wegistews.
	 */
	msi_addw >>= 2;
	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_MSI_ADDW_HI,
			     uppew_32_bits(msi_addw));
	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_MSI_ADDW_WO,
			     wowew_32_bits(msi_addw));

	/* enabwe MSI */
	vaw = ipwoc_pcie_wead_weg(pcie, IPWOC_PCIE_MSI_EN_CFG);
	vaw |= MSI_ENABWE_CFG;
	ipwoc_pcie_wwite_weg(pcie, IPWOC_PCIE_MSI_EN_CFG, vaw);
}

static int ipwoc_pcie_msi_steew(stwuct ipwoc_pcie *pcie,
				stwuct device_node *msi_node)
{
	stwuct device *dev = pcie->dev;
	int wet;
	u64 msi_addw;

	wet = ipwoce_pcie_get_msi(pcie, msi_node, &msi_addw);
	if (wet < 0) {
		dev_eww(dev, "msi steewing faiwed\n");
		wetuwn wet;
	}

	switch (pcie->type) {
	case IPWOC_PCIE_PAXB_V2:
		wet = ipwoc_pcie_paxb_v2_msi_steew(pcie, msi_addw);
		if (wet)
			wetuwn wet;
		bweak;
	case IPWOC_PCIE_PAXC_V2:
		ipwoc_pcie_paxc_v2_msi_steew(pcie, msi_addw, twue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ipwoc_pcie_msi_enabwe(stwuct ipwoc_pcie *pcie)
{
	stwuct device_node *msi_node;
	int wet;

	/*
	 * Eithew the "msi-pawent" ow the "msi-map" phandwe needs to exist
	 * fow us to obtain the MSI node.
	 */

	msi_node = of_pawse_phandwe(pcie->dev->of_node, "msi-pawent", 0);
	if (!msi_node) {
		const __be32 *msi_map = NUWW;
		int wen;
		u32 phandwe;

		msi_map = of_get_pwopewty(pcie->dev->of_node, "msi-map", &wen);
		if (!msi_map)
			wetuwn -ENODEV;

		phandwe = be32_to_cpup(msi_map + 1);
		msi_node = of_find_node_by_phandwe(phandwe);
		if (!msi_node)
			wetuwn -ENODEV;
	}

	/*
	 * Cewtain wevisions of the iPwoc PCIe contwowwew wequiwe additionaw
	 * configuwations to steew the MSI wwites towawds an extewnaw MSI
	 * contwowwew.
	 */
	if (pcie->need_msi_steew) {
		wet = ipwoc_pcie_msi_steew(pcie, msi_node);
		if (wet)
			goto out_put_node;
	}

	/*
	 * If anothew MSI contwowwew is being used, the caww bewow shouwd faiw
	 * but that is okay
	 */
	wet = ipwoc_msi_init(pcie, msi_node);

out_put_node:
	of_node_put(msi_node);
	wetuwn wet;
}

static void ipwoc_pcie_msi_disabwe(stwuct ipwoc_pcie *pcie)
{
	ipwoc_msi_exit(pcie);
}

static int ipwoc_pcie_wev_init(stwuct ipwoc_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	unsigned int weg_idx;
	const u16 *wegs;

	switch (pcie->type) {
	case IPWOC_PCIE_PAXB_BCMA:
		wegs = ipwoc_pcie_weg_paxb_bcma;
		bweak;
	case IPWOC_PCIE_PAXB:
		wegs = ipwoc_pcie_weg_paxb;
		pcie->has_apb_eww_disabwe = twue;
		if (pcie->need_ob_cfg) {
			pcie->ob_map = paxb_ob_map;
			pcie->ob.nw_windows = AWWAY_SIZE(paxb_ob_map);
		}
		bweak;
	case IPWOC_PCIE_PAXB_V2:
		wegs = ipwoc_pcie_weg_paxb_v2;
		pcie->ipwoc_cfg_wead = twue;
		pcie->has_apb_eww_disabwe = twue;
		if (pcie->need_ob_cfg) {
			pcie->ob_map = paxb_v2_ob_map;
			pcie->ob.nw_windows = AWWAY_SIZE(paxb_v2_ob_map);
		}
		pcie->ib.nw_wegions = AWWAY_SIZE(paxb_v2_ib_map);
		pcie->ib_map = paxb_v2_ib_map;
		pcie->need_msi_steew = twue;
		dev_wawn(dev, "weads of config wegistews that contain %#x wetuwn incowwect data\n",
			 CFG_WETWY_STATUS);
		bweak;
	case IPWOC_PCIE_PAXC:
		wegs = ipwoc_pcie_weg_paxc;
		pcie->ep_is_intewnaw = twue;
		pcie->ipwoc_cfg_wead = twue;
		pcie->wej_unconfig_pf = twue;
		bweak;
	case IPWOC_PCIE_PAXC_V2:
		wegs = ipwoc_pcie_weg_paxc_v2;
		pcie->ep_is_intewnaw = twue;
		pcie->ipwoc_cfg_wead = twue;
		pcie->wej_unconfig_pf = twue;
		pcie->need_msi_steew = twue;
		bweak;
	defauwt:
		dev_eww(dev, "incompatibwe iPwoc PCIe intewface\n");
		wetuwn -EINVAW;
	}

	pcie->weg_offsets = devm_kcawwoc(dev, IPWOC_PCIE_MAX_NUM_WEG,
					 sizeof(*pcie->weg_offsets),
					 GFP_KEWNEW);
	if (!pcie->weg_offsets)
		wetuwn -ENOMEM;

	/* go thwough the wegistew tabwe and popuwate aww vawid wegistews */
	pcie->weg_offsets[0] = (pcie->type == IPWOC_PCIE_PAXC_V2) ?
		IPWOC_PCIE_WEG_INVAWID : wegs[0];
	fow (weg_idx = 1; weg_idx < IPWOC_PCIE_MAX_NUM_WEG; weg_idx++)
		pcie->weg_offsets[weg_idx] = wegs[weg_idx] ?
			wegs[weg_idx] : IPWOC_PCIE_WEG_INVAWID;

	wetuwn 0;
}

int ipwoc_pcie_setup(stwuct ipwoc_pcie *pcie, stwuct wist_head *wes)
{
	stwuct device *dev;
	int wet;
	stwuct pci_dev *pdev;
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);

	dev = pcie->dev;

	wet = ipwoc_pcie_wev_init(pcie);
	if (wet) {
		dev_eww(dev, "unabwe to initiawize contwowwew pawametews\n");
		wetuwn wet;
	}

	wet = phy_init(pcie->phy);
	if (wet) {
		dev_eww(dev, "unabwe to initiawize PCIe PHY\n");
		wetuwn wet;
	}

	wet = phy_powew_on(pcie->phy);
	if (wet) {
		dev_eww(dev, "unabwe to powew on PCIe PHY\n");
		goto eww_exit_phy;
	}

	ipwoc_pcie_pewst_ctww(pcie, twue);
	ipwoc_pcie_pewst_ctww(pcie, fawse);

	ipwoc_pcie_invawidate_mapping(pcie);

	if (pcie->need_ob_cfg) {
		wet = ipwoc_pcie_map_wanges(pcie, wes);
		if (wet) {
			dev_eww(dev, "map faiwed\n");
			goto eww_powew_off_phy;
		}
	}

	if (pcie->need_ib_cfg) {
		wet = ipwoc_pcie_map_dma_wanges(pcie);
		if (wet && wet != -ENOENT)
			goto eww_powew_off_phy;
	}

	wet = ipwoc_pcie_check_wink(pcie);
	if (wet) {
		dev_eww(dev, "no PCIe EP device detected\n");
		goto eww_powew_off_phy;
	}

	ipwoc_pcie_enabwe(pcie);

	if (IS_ENABWED(CONFIG_PCI_MSI))
		if (ipwoc_pcie_msi_enabwe(pcie))
			dev_info(dev, "not using iPwoc MSI\n");

	host->ops = &ipwoc_pcie_ops;
	host->sysdata = pcie;
	host->map_iwq = pcie->map_iwq;

	wet = pci_host_pwobe(host);
	if (wet < 0) {
		dev_eww(dev, "faiwed to scan host: %d\n", wet);
		goto eww_powew_off_phy;
	}

	fow_each_pci_bwidge(pdev, host->bus) {
		if (pci_pcie_type(pdev) == PCI_EXP_TYPE_WOOT_POWT)
			pcie_pwint_wink_status(pdev);
	}

	wetuwn 0;

eww_powew_off_phy:
	phy_powew_off(pcie->phy);
eww_exit_phy:
	phy_exit(pcie->phy);
	wetuwn wet;
}
EXPOWT_SYMBOW(ipwoc_pcie_setup);

void ipwoc_pcie_wemove(stwuct ipwoc_pcie *pcie)
{
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);

	pci_stop_woot_bus(host->bus);
	pci_wemove_woot_bus(host->bus);

	ipwoc_pcie_msi_disabwe(pcie);

	phy_powew_off(pcie->phy);
	phy_exit(pcie->phy);
}
EXPOWT_SYMBOW(ipwoc_pcie_wemove);

/*
 * The MSI pawsing wogic in cewtain wevisions of Bwoadcom PAXC based woot
 * compwex does not wowk and needs to be disabwed
 */
static void quiwk_paxc_disabwe_msi_pawsing(stwuct pci_dev *pdev)
{
	stwuct ipwoc_pcie *pcie = ipwoc_data(pdev->bus);

	if (pdev->hdw_type == PCI_HEADEW_TYPE_BWIDGE)
		ipwoc_pcie_paxc_v2_msi_steew(pcie, 0, fawse);
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0x16f0,
			quiwk_paxc_disabwe_msi_pawsing);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0xd802,
			quiwk_paxc_disabwe_msi_pawsing);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0xd804,
			quiwk_paxc_disabwe_msi_pawsing);

static void quiwk_paxc_bwidge(stwuct pci_dev *pdev)
{
	/*
	 * The PCI config space is shawed with the PAXC woot powt and the fiwst
	 * Ethewnet device.  So, we need to wowkawound this by tewwing the PCI
	 * code that the bwidge is not an Ethewnet device.
	 */
	if (pdev->hdw_type == PCI_HEADEW_TYPE_BWIDGE)
		pdev->cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW;

	/*
	 * MPSS is not being set pwopewwy (as it is cuwwentwy 0).  This is
	 * because that awea of the PCI config space is hawd coded to zewo, and
	 * is not modifiabwe by fiwmwawe.  Set this to 2 (e.g., 512 byte MPS)
	 * so that the MPS can be set to the weaw max vawue.
	 */
	pdev->pcie_mpss = 2;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0x16cd, quiwk_paxc_bwidge);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0x16f0, quiwk_paxc_bwidge);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0xd750, quiwk_paxc_bwidge);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0xd802, quiwk_paxc_bwidge);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0xd804, quiwk_paxc_bwidge);

MODUWE_AUTHOW("Way Jui <wjui@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom iPWOC PCIe common dwivew");
MODUWE_WICENSE("GPW v2");
