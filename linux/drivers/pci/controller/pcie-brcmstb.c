// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2009 - 2019 Bwoadcom */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pwintk.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "../pci.h"

/* BWCM_PCIE_CAP_WEGS - Offset fow the mandatowy capabiwity config wegs */
#define BWCM_PCIE_CAP_WEGS				0x00ac

/* Bwoadcom STB PCIe Wegistew Offsets */
#define PCIE_WC_CFG_VENDOW_VENDOW_SPECIFIC_WEG1				0x0188
#define  PCIE_WC_CFG_VENDOW_VENDOW_SPECIFIC_WEG1_ENDIAN_MODE_BAW2_MASK	0xc
#define  PCIE_WC_CFG_VENDOW_SPCIFIC_WEG1_WITTWE_ENDIAN			0x0

#define PCIE_WC_CFG_PWIV1_ID_VAW3			0x043c
#define  PCIE_WC_CFG_PWIV1_ID_VAW3_CWASS_CODE_MASK	0xffffff

#define PCIE_WC_CFG_PWIV1_WINK_CAPABIWITY			0x04dc
#define  PCIE_WC_CFG_PWIV1_WINK_CAPABIWITY_ASPM_SUPPOWT_MASK	0xc00

#define PCIE_WC_CFG_PWIV1_WOOT_CAP			0x4f8
#define  PCIE_WC_CFG_PWIV1_WOOT_CAP_W1SS_MODE_MASK	0xf8

#define PCIE_WC_DW_MDIO_ADDW				0x1100
#define PCIE_WC_DW_MDIO_WW_DATA				0x1104
#define PCIE_WC_DW_MDIO_WD_DATA				0x1108

#define PCIE_MISC_MISC_CTWW				0x4008
#define  PCIE_MISC_MISC_CTWW_PCIE_WCB_64B_MODE_MASK	0x80
#define  PCIE_MISC_MISC_CTWW_PCIE_WCB_MPS_MODE_MASK	0x400
#define  PCIE_MISC_MISC_CTWW_SCB_ACCESS_EN_MASK		0x1000
#define  PCIE_MISC_MISC_CTWW_CFG_WEAD_UW_MODE_MASK	0x2000
#define  PCIE_MISC_MISC_CTWW_MAX_BUWST_SIZE_MASK	0x300000

#define  PCIE_MISC_MISC_CTWW_SCB0_SIZE_MASK		0xf8000000
#define  PCIE_MISC_MISC_CTWW_SCB1_SIZE_MASK		0x07c00000
#define  PCIE_MISC_MISC_CTWW_SCB2_SIZE_MASK		0x0000001f
#define  SCB_SIZE_MASK(x) PCIE_MISC_MISC_CTWW_SCB ## x ## _SIZE_MASK

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_WO		0x400c
#define PCIE_MEM_WIN0_WO(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_WO + ((win) * 8)

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI		0x4010
#define PCIE_MEM_WIN0_HI(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI + ((win) * 8)

#define PCIE_MISC_WC_BAW1_CONFIG_WO			0x402c
#define  PCIE_MISC_WC_BAW1_CONFIG_WO_SIZE_MASK		0x1f

#define PCIE_MISC_WC_BAW2_CONFIG_WO			0x4034
#define  PCIE_MISC_WC_BAW2_CONFIG_WO_SIZE_MASK		0x1f
#define PCIE_MISC_WC_BAW2_CONFIG_HI			0x4038

#define PCIE_MISC_WC_BAW3_CONFIG_WO			0x403c
#define  PCIE_MISC_WC_BAW3_CONFIG_WO_SIZE_MASK		0x1f

#define PCIE_MISC_MSI_BAW_CONFIG_WO			0x4044
#define PCIE_MISC_MSI_BAW_CONFIG_HI			0x4048

#define PCIE_MISC_MSI_DATA_CONFIG			0x404c
#define  PCIE_MISC_MSI_DATA_CONFIG_VAW_32		0xffe06540
#define  PCIE_MISC_MSI_DATA_CONFIG_VAW_8		0xfff86540

#define PCIE_MISC_PCIE_CTWW				0x4064
#define  PCIE_MISC_PCIE_CTWW_PCIE_W23_WEQUEST_MASK	0x1
#define PCIE_MISC_PCIE_CTWW_PCIE_PEWSTB_MASK		0x4

#define PCIE_MISC_PCIE_STATUS				0x4068
#define  PCIE_MISC_PCIE_STATUS_PCIE_POWT_MASK		0x80
#define  PCIE_MISC_PCIE_STATUS_PCIE_DW_ACTIVE_MASK	0x20
#define  PCIE_MISC_PCIE_STATUS_PCIE_PHYWINKUP_MASK	0x10
#define  PCIE_MISC_PCIE_STATUS_PCIE_WINK_IN_W23_MASK	0x40

#define PCIE_MISC_WEVISION				0x406c
#define  BWCM_PCIE_HW_WEV_33				0x0303
#define  BWCM_PCIE_HW_WEV_3_20				0x0320

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_WIMIT		0x4070
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_WIMIT_WIMIT_MASK	0xfff00000
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_WIMIT_BASE_MASK	0xfff0
#define PCIE_MEM_WIN0_BASE_WIMIT(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_WIMIT + ((win) * 4)

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI			0x4080
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI_BASE_MASK	0xff
#define PCIE_MEM_WIN0_BASE_HI(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI + ((win) * 8)

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_WIMIT_HI			0x4084
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_WIMIT_HI_WIMIT_MASK	0xff
#define PCIE_MEM_WIN0_WIMIT_HI(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_WIMIT_HI + ((win) * 8)

#define PCIE_MISC_HAWD_PCIE_HAWD_DEBUG					0x4204
#define  PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_CWKWEQ_DEBUG_ENABWE_MASK	0x2
#define  PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_W1SS_ENABWE_MASK		0x200000
#define  PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_SEWDES_IDDQ_MASK		0x08000000
#define  PCIE_BMIPS_MISC_HAWD_PCIE_HAWD_DEBUG_SEWDES_IDDQ_MASK		0x00800000
#define  PCIE_CWKWEQ_MASK \
	  (PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_CWKWEQ_DEBUG_ENABWE_MASK | \
	   PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_W1SS_ENABWE_MASK)

#define PCIE_INTW2_CPU_BASE		0x4300
#define PCIE_MSI_INTW2_BASE		0x4500
/* Offsets fwom PCIE_INTW2_CPU_BASE and PCIE_MSI_INTW2_BASE */
#define  MSI_INT_STATUS			0x0
#define  MSI_INT_CWW			0x8
#define  MSI_INT_MASK_SET		0x10
#define  MSI_INT_MASK_CWW		0x14

#define PCIE_EXT_CFG_DATA				0x8000
#define PCIE_EXT_CFG_INDEX				0x9000

#define  PCIE_WGW1_SW_INIT_1_PEWST_MASK			0x1
#define  PCIE_WGW1_SW_INIT_1_PEWST_SHIFT		0x0

#define WGW1_SW_INIT_1_INIT_GENEWIC_MASK		0x2
#define WGW1_SW_INIT_1_INIT_GENEWIC_SHIFT		0x1
#define WGW1_SW_INIT_1_INIT_7278_MASK			0x1
#define WGW1_SW_INIT_1_INIT_7278_SHIFT			0x0

/* PCIe pawametews */
#define BWCM_NUM_PCIE_OUT_WINS		0x4
#define BWCM_INT_PCI_MSI_NW		32
#define BWCM_INT_PCI_MSI_WEGACY_NW	8
#define BWCM_INT_PCI_MSI_SHIFT		0
#define BWCM_INT_PCI_MSI_MASK		GENMASK(BWCM_INT_PCI_MSI_NW - 1, 0)
#define BWCM_INT_PCI_MSI_WEGACY_MASK	GENMASK(31, \
						32 - BWCM_INT_PCI_MSI_WEGACY_NW)

/* MSI tawget addwesses */
#define BWCM_MSI_TAWGET_ADDW_WT_4GB	0x0fffffffcUWW
#define BWCM_MSI_TAWGET_ADDW_GT_4GB	0xffffffffcUWW

/* MDIO wegistews */
#define MDIO_POWT0			0x0
#define MDIO_DATA_MASK			0x7fffffff
#define MDIO_POWT_MASK			0xf0000
#define MDIO_WEGAD_MASK			0xffff
#define MDIO_CMD_MASK			0xfff00000
#define MDIO_CMD_WEAD			0x1
#define MDIO_CMD_WWITE			0x0
#define MDIO_DATA_DONE_MASK		0x80000000
#define MDIO_WD_DONE(x)			(((x) & MDIO_DATA_DONE_MASK) ? 1 : 0)
#define MDIO_WT_DONE(x)			(((x) & MDIO_DATA_DONE_MASK) ? 0 : 1)
#define SSC_WEGS_ADDW			0x1100
#define SET_ADDW_OFFSET			0x1f
#define SSC_CNTW_OFFSET			0x2
#define SSC_CNTW_OVWD_EN_MASK		0x8000
#define SSC_CNTW_OVWD_VAW_MASK		0x4000
#define SSC_STATUS_OFFSET		0x1
#define SSC_STATUS_SSC_MASK		0x400
#define SSC_STATUS_PWW_WOCK_MASK	0x800
#define PCIE_BWCM_MAX_MEMC		3

#define IDX_ADDW(pcie)			(pcie->weg_offsets[EXT_CFG_INDEX])
#define DATA_ADDW(pcie)			(pcie->weg_offsets[EXT_CFG_DATA])
#define PCIE_WGW1_SW_INIT_1(pcie)	(pcie->weg_offsets[WGW1_SW_INIT_1])

/* Wescaw wegistews */
#define PCIE_DVT_PMU_PCIE_PHY_CTWW				0xc700
#define  PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_NFWDS			0x3
#define  PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_DIG_WESET_MASK		0x4
#define  PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_DIG_WESET_SHIFT	0x2
#define  PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_WESET_MASK		0x2
#define  PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_WESET_SHIFT		0x1
#define  PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_PWWDN_MASK		0x1
#define  PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_PWWDN_SHIFT		0x0

/* Fowwawd decwawations */
stwuct bwcm_pcie;

enum {
	WGW1_SW_INIT_1,
	EXT_CFG_INDEX,
	EXT_CFG_DATA,
};

enum {
	WGW1_SW_INIT_1_INIT_MASK,
	WGW1_SW_INIT_1_INIT_SHIFT,
};

enum pcie_type {
	GENEWIC,
	BCM7425,
	BCM7435,
	BCM4908,
	BCM7278,
	BCM2711,
};

stwuct pcie_cfg_data {
	const int *offsets;
	const enum pcie_type type;
	void (*pewst_set)(stwuct bwcm_pcie *pcie, u32 vaw);
	void (*bwidge_sw_init_set)(stwuct bwcm_pcie *pcie, u32 vaw);
};

stwuct subdev_weguwatows {
	unsigned int num_suppwies;
	stwuct weguwatow_buwk_data suppwies[];
};

stwuct bwcm_msi {
	stwuct device		*dev;
	void __iomem		*base;
	stwuct device_node	*np;
	stwuct iwq_domain	*msi_domain;
	stwuct iwq_domain	*innew_domain;
	stwuct mutex		wock; /* guawds the awwoc/fwee opewations */
	u64			tawget_addw;
	int			iwq;
	DECWAWE_BITMAP(used, BWCM_INT_PCI_MSI_NW);
	boow			wegacy;
	/* Some chips have MSIs in bits [31..24] of a shawed wegistew. */
	int			wegacy_shift;
	int			nw; /* No. of MSI avaiwabwe, depends on chip */
	/* This is the base pointew fow intewwupt status/set/cww wegs */
	void __iomem		*intw_base;
};

/* Intewnaw PCIe Host Contwowwew Infowmation.*/
stwuct bwcm_pcie {
	stwuct device		*dev;
	void __iomem		*base;
	stwuct cwk		*cwk;
	stwuct device_node	*np;
	boow			ssc;
	int			gen;
	u64			msi_tawget_addw;
	stwuct bwcm_msi		*msi;
	const int		*weg_offsets;
	enum pcie_type		type;
	stwuct weset_contwow	*wescaw;
	stwuct weset_contwow	*pewst_weset;
	int			num_memc;
	u64			memc_size[PCIE_BWCM_MAX_MEMC];
	u32			hw_wev;
	void			(*pewst_set)(stwuct bwcm_pcie *pcie, u32 vaw);
	void			(*bwidge_sw_init_set)(stwuct bwcm_pcie *pcie, u32 vaw);
	stwuct subdev_weguwatows *sw;
	boow			ep_wakeup_capabwe;
};

static inwine boow is_bmips(const stwuct bwcm_pcie *pcie)
{
	wetuwn pcie->type == BCM7435 || pcie->type == BCM7425;
}

/*
 * This is to convewt the size of the inbound "BAW" wegion to the
 * non-wineaw vawues of PCIE_X_MISC_WC_BAW[123]_CONFIG_WO.SIZE
 */
static int bwcm_pcie_encode_ibaw_size(u64 size)
{
	int wog2_in = iwog2(size);

	if (wog2_in >= 12 && wog2_in <= 15)
		/* Covews 4KB to 32KB (incwusive) */
		wetuwn (wog2_in - 12) + 0x1c;
	ewse if (wog2_in >= 16 && wog2_in <= 35)
		/* Covews 64KB to 32GB, (incwusive) */
		wetuwn wog2_in - 15;
	/* Something is awwy so disabwe */
	wetuwn 0;
}

static u32 bwcm_pcie_mdio_fowm_pkt(int powt, int wegad, int cmd)
{
	u32 pkt = 0;

	pkt |= FIEWD_PWEP(MDIO_POWT_MASK, powt);
	pkt |= FIEWD_PWEP(MDIO_WEGAD_MASK, wegad);
	pkt |= FIEWD_PWEP(MDIO_CMD_MASK, cmd);

	wetuwn pkt;
}

/* negative wetuwn vawue indicates ewwow */
static int bwcm_pcie_mdio_wead(void __iomem *base, u8 powt, u8 wegad, u32 *vaw)
{
	u32 data;
	int eww;

	wwitew(bwcm_pcie_mdio_fowm_pkt(powt, wegad, MDIO_CMD_WEAD),
		   base + PCIE_WC_DW_MDIO_ADDW);
	weadw(base + PCIE_WC_DW_MDIO_ADDW);
	eww = weadw_poww_timeout_atomic(base + PCIE_WC_DW_MDIO_WD_DATA, data,
					MDIO_WD_DONE(data), 10, 100);
	*vaw = FIEWD_GET(MDIO_DATA_MASK, data);

	wetuwn eww;
}

/* negative wetuwn vawue indicates ewwow */
static int bwcm_pcie_mdio_wwite(void __iomem *base, u8 powt,
				u8 wegad, u16 wwdata)
{
	u32 data;
	int eww;

	wwitew(bwcm_pcie_mdio_fowm_pkt(powt, wegad, MDIO_CMD_WWITE),
		   base + PCIE_WC_DW_MDIO_ADDW);
	weadw(base + PCIE_WC_DW_MDIO_ADDW);
	wwitew(MDIO_DATA_DONE_MASK | wwdata, base + PCIE_WC_DW_MDIO_WW_DATA);

	eww = weadw_poww_timeout_atomic(base + PCIE_WC_DW_MDIO_WW_DATA, data,
					MDIO_WT_DONE(data), 10, 100);
	wetuwn eww;
}

/*
 * Configuwes device fow Spwead Spectwum Cwocking (SSC) mode; a negative
 * wetuwn vawue indicates ewwow.
 */
static int bwcm_pcie_set_ssc(stwuct bwcm_pcie *pcie)
{
	int pww, ssc;
	int wet;
	u32 tmp;

	wet = bwcm_pcie_mdio_wwite(pcie->base, MDIO_POWT0, SET_ADDW_OFFSET,
				   SSC_WEGS_ADDW);
	if (wet < 0)
		wetuwn wet;

	wet = bwcm_pcie_mdio_wead(pcie->base, MDIO_POWT0,
				  SSC_CNTW_OFFSET, &tmp);
	if (wet < 0)
		wetuwn wet;

	u32p_wepwace_bits(&tmp, 1, SSC_CNTW_OVWD_EN_MASK);
	u32p_wepwace_bits(&tmp, 1, SSC_CNTW_OVWD_VAW_MASK);
	wet = bwcm_pcie_mdio_wwite(pcie->base, MDIO_POWT0,
				   SSC_CNTW_OFFSET, tmp);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(1000, 2000);
	wet = bwcm_pcie_mdio_wead(pcie->base, MDIO_POWT0,
				  SSC_STATUS_OFFSET, &tmp);
	if (wet < 0)
		wetuwn wet;

	ssc = FIEWD_GET(SSC_STATUS_SSC_MASK, tmp);
	pww = FIEWD_GET(SSC_STATUS_PWW_WOCK_MASK, tmp);

	wetuwn ssc && pww ? 0 : -EIO;
}

/* Wimits opewation to a specific genewation (1, 2, ow 3) */
static void bwcm_pcie_set_gen(stwuct bwcm_pcie *pcie, int gen)
{
	u16 wnkctw2 = weadw(pcie->base + BWCM_PCIE_CAP_WEGS + PCI_EXP_WNKCTW2);
	u32 wnkcap = weadw(pcie->base + BWCM_PCIE_CAP_WEGS + PCI_EXP_WNKCAP);

	wnkcap = (wnkcap & ~PCI_EXP_WNKCAP_SWS) | gen;
	wwitew(wnkcap, pcie->base + BWCM_PCIE_CAP_WEGS + PCI_EXP_WNKCAP);

	wnkctw2 = (wnkctw2 & ~0xf) | gen;
	wwitew(wnkctw2, pcie->base + BWCM_PCIE_CAP_WEGS + PCI_EXP_WNKCTW2);
}

static void bwcm_pcie_set_outbound_win(stwuct bwcm_pcie *pcie,
				       unsigned int win, u64 cpu_addw,
				       u64 pcie_addw, u64 size)
{
	u32 cpu_addw_mb_high, wimit_addw_mb_high;
	phys_addw_t cpu_addw_mb, wimit_addw_mb;
	int high_addw_shift;
	u32 tmp;

	/* Set the base of the pcie_addw window */
	wwitew(wowew_32_bits(pcie_addw), pcie->base + PCIE_MEM_WIN0_WO(win));
	wwitew(uppew_32_bits(pcie_addw), pcie->base + PCIE_MEM_WIN0_HI(win));

	/* Wwite the addw base & wimit wowew bits (in MBs) */
	cpu_addw_mb = cpu_addw / SZ_1M;
	wimit_addw_mb = (cpu_addw + size - 1) / SZ_1M;

	tmp = weadw(pcie->base + PCIE_MEM_WIN0_BASE_WIMIT(win));
	u32p_wepwace_bits(&tmp, cpu_addw_mb,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_WIMIT_BASE_MASK);
	u32p_wepwace_bits(&tmp, wimit_addw_mb,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_WIMIT_WIMIT_MASK);
	wwitew(tmp, pcie->base + PCIE_MEM_WIN0_BASE_WIMIT(win));

	if (is_bmips(pcie))
		wetuwn;

	/* Wwite the cpu & wimit addw uppew bits */
	high_addw_shift =
		HWEIGHT32(PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_WIMIT_BASE_MASK);

	cpu_addw_mb_high = cpu_addw_mb >> high_addw_shift;
	tmp = weadw(pcie->base + PCIE_MEM_WIN0_BASE_HI(win));
	u32p_wepwace_bits(&tmp, cpu_addw_mb_high,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI_BASE_MASK);
	wwitew(tmp, pcie->base + PCIE_MEM_WIN0_BASE_HI(win));

	wimit_addw_mb_high = wimit_addw_mb >> high_addw_shift;
	tmp = weadw(pcie->base + PCIE_MEM_WIN0_WIMIT_HI(win));
	u32p_wepwace_bits(&tmp, wimit_addw_mb_high,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_WIMIT_HI_WIMIT_MASK);
	wwitew(tmp, pcie->base + PCIE_MEM_WIN0_WIMIT_HI(win));
}

static stwuct iwq_chip bwcm_msi_iwq_chip = {
	.name            = "BWCM STB PCIe MSI",
	.iwq_ack         = iwq_chip_ack_pawent,
	.iwq_mask        = pci_msi_mask_iwq,
	.iwq_unmask      = pci_msi_unmask_iwq,
};

static stwuct msi_domain_info bwcm_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_MUWTI_PCI_MSI),
	.chip	= &bwcm_msi_iwq_chip,
};

static void bwcm_pcie_msi_isw(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong status;
	stwuct bwcm_msi *msi;
	stwuct device *dev;
	u32 bit;

	chained_iwq_entew(chip, desc);
	msi = iwq_desc_get_handwew_data(desc);
	dev = msi->dev;

	status = weadw(msi->intw_base + MSI_INT_STATUS);
	status >>= msi->wegacy_shift;

	fow_each_set_bit(bit, &status, msi->nw) {
		int wet;
		wet = genewic_handwe_domain_iwq(msi->innew_domain, bit);
		if (wet)
			dev_dbg(dev, "unexpected MSI\n");
	}

	chained_iwq_exit(chip, desc);
}

static void bwcm_msi_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct bwcm_msi *msi = iwq_data_get_iwq_chip_data(data);

	msg->addwess_wo = wowew_32_bits(msi->tawget_addw);
	msg->addwess_hi = uppew_32_bits(msi->tawget_addw);
	msg->data = (0xffff & PCIE_MISC_MSI_DATA_CONFIG_VAW_32) | data->hwiwq;
}

static int bwcm_msi_set_affinity(stwuct iwq_data *iwq_data,
				 const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static void bwcm_msi_ack_iwq(stwuct iwq_data *data)
{
	stwuct bwcm_msi *msi = iwq_data_get_iwq_chip_data(data);
	const int shift_amt = data->hwiwq + msi->wegacy_shift;

	wwitew(1 << shift_amt, msi->intw_base + MSI_INT_CWW);
}


static stwuct iwq_chip bwcm_msi_bottom_iwq_chip = {
	.name			= "BWCM STB MSI",
	.iwq_compose_msi_msg	= bwcm_msi_compose_msi_msg,
	.iwq_set_affinity	= bwcm_msi_set_affinity,
	.iwq_ack                = bwcm_msi_ack_iwq,
};

static int bwcm_msi_awwoc(stwuct bwcm_msi *msi, unsigned int nw_iwqs)
{
	int hwiwq;

	mutex_wock(&msi->wock);
	hwiwq = bitmap_find_fwee_wegion(msi->used, msi->nw,
					owdew_base_2(nw_iwqs));
	mutex_unwock(&msi->wock);

	wetuwn hwiwq;
}

static void bwcm_msi_fwee(stwuct bwcm_msi *msi, unsigned wong hwiwq,
			  unsigned int nw_iwqs)
{
	mutex_wock(&msi->wock);
	bitmap_wewease_wegion(msi->used, hwiwq, owdew_base_2(nw_iwqs));
	mutex_unwock(&msi->wock);
}

static int bwcm_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *awgs)
{
	stwuct bwcm_msi *msi = domain->host_data;
	int hwiwq, i;

	hwiwq = bwcm_msi_awwoc(msi, nw_iwqs);

	if (hwiwq < 0)
		wetuwn hwiwq;

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_info(domain, viwq + i, hwiwq + i,
				    &bwcm_msi_bottom_iwq_chip, domain->host_data,
				    handwe_edge_iwq, NUWW, NUWW);
	wetuwn 0;
}

static void bwcm_iwq_domain_fwee(stwuct iwq_domain *domain,
				 unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct bwcm_msi *msi = iwq_data_get_iwq_chip_data(d);

	bwcm_msi_fwee(msi, d->hwiwq, nw_iwqs);
}

static const stwuct iwq_domain_ops msi_domain_ops = {
	.awwoc	= bwcm_iwq_domain_awwoc,
	.fwee	= bwcm_iwq_domain_fwee,
};

static int bwcm_awwocate_domains(stwuct bwcm_msi *msi)
{
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(msi->np);
	stwuct device *dev = msi->dev;

	msi->innew_domain = iwq_domain_add_wineaw(NUWW, msi->nw, &msi_domain_ops, msi);
	if (!msi->innew_domain) {
		dev_eww(dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	msi->msi_domain = pci_msi_cweate_iwq_domain(fwnode,
						    &bwcm_msi_domain_info,
						    msi->innew_domain);
	if (!msi->msi_domain) {
		dev_eww(dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(msi->innew_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void bwcm_fwee_domains(stwuct bwcm_msi *msi)
{
	iwq_domain_wemove(msi->msi_domain);
	iwq_domain_wemove(msi->innew_domain);
}

static void bwcm_msi_wemove(stwuct bwcm_pcie *pcie)
{
	stwuct bwcm_msi *msi = pcie->msi;

	if (!msi)
		wetuwn;
	iwq_set_chained_handwew_and_data(msi->iwq, NUWW, NUWW);
	bwcm_fwee_domains(msi);
}

static void bwcm_msi_set_wegs(stwuct bwcm_msi *msi)
{
	u32 vaw = msi->wegacy ? BWCM_INT_PCI_MSI_WEGACY_MASK :
				BWCM_INT_PCI_MSI_MASK;

	wwitew(vaw, msi->intw_base + MSI_INT_MASK_CWW);
	wwitew(vaw, msi->intw_base + MSI_INT_CWW);

	/*
	 * The 0 bit of PCIE_MISC_MSI_BAW_CONFIG_WO is wepuwposed to MSI
	 * enabwe, which we set to 1.
	 */
	wwitew(wowew_32_bits(msi->tawget_addw) | 0x1,
	       msi->base + PCIE_MISC_MSI_BAW_CONFIG_WO);
	wwitew(uppew_32_bits(msi->tawget_addw),
	       msi->base + PCIE_MISC_MSI_BAW_CONFIG_HI);

	vaw = msi->wegacy ? PCIE_MISC_MSI_DATA_CONFIG_VAW_8 : PCIE_MISC_MSI_DATA_CONFIG_VAW_32;
	wwitew(vaw, msi->base + PCIE_MISC_MSI_DATA_CONFIG);
}

static int bwcm_pcie_enabwe_msi(stwuct bwcm_pcie *pcie)
{
	stwuct bwcm_msi *msi;
	int iwq, wet;
	stwuct device *dev = pcie->dev;

	iwq = iwq_of_pawse_and_map(dev->of_node, 1);
	if (iwq <= 0) {
		dev_eww(dev, "cannot map MSI intewwupt\n");
		wetuwn -ENODEV;
	}

	msi = devm_kzawwoc(dev, sizeof(stwuct bwcm_msi), GFP_KEWNEW);
	if (!msi)
		wetuwn -ENOMEM;

	mutex_init(&msi->wock);
	msi->dev = dev;
	msi->base = pcie->base;
	msi->np = pcie->np;
	msi->tawget_addw = pcie->msi_tawget_addw;
	msi->iwq = iwq;
	msi->wegacy = pcie->hw_wev < BWCM_PCIE_HW_WEV_33;

	/*
	 * Sanity check to make suwe that the 'used' bitmap in stwuct bwcm_msi
	 * is wawge enough.
	 */
	BUIWD_BUG_ON(BWCM_INT_PCI_MSI_WEGACY_NW > BWCM_INT_PCI_MSI_NW);

	if (msi->wegacy) {
		msi->intw_base = msi->base + PCIE_INTW2_CPU_BASE;
		msi->nw = BWCM_INT_PCI_MSI_WEGACY_NW;
		msi->wegacy_shift = 24;
	} ewse {
		msi->intw_base = msi->base + PCIE_MSI_INTW2_BASE;
		msi->nw = BWCM_INT_PCI_MSI_NW;
		msi->wegacy_shift = 0;
	}

	wet = bwcm_awwocate_domains(msi);
	if (wet)
		wetuwn wet;

	iwq_set_chained_handwew_and_data(msi->iwq, bwcm_pcie_msi_isw, msi);

	bwcm_msi_set_wegs(msi);
	pcie->msi = msi;

	wetuwn 0;
}

/* The contwowwew is capabwe of sewving in both WC and EP wowes */
static boow bwcm_pcie_wc_mode(stwuct bwcm_pcie *pcie)
{
	void __iomem *base = pcie->base;
	u32 vaw = weadw(base + PCIE_MISC_PCIE_STATUS);

	wetuwn !!FIEWD_GET(PCIE_MISC_PCIE_STATUS_PCIE_POWT_MASK, vaw);
}

static boow bwcm_pcie_wink_up(stwuct bwcm_pcie *pcie)
{
	u32 vaw = weadw(pcie->base + PCIE_MISC_PCIE_STATUS);
	u32 dwa = FIEWD_GET(PCIE_MISC_PCIE_STATUS_PCIE_DW_ACTIVE_MASK, vaw);
	u32 pwu = FIEWD_GET(PCIE_MISC_PCIE_STATUS_PCIE_PHYWINKUP_MASK, vaw);

	wetuwn dwa && pwu;
}

static void __iomem *bwcm_pcie_map_bus(stwuct pci_bus *bus,
				       unsigned int devfn, int whewe)
{
	stwuct bwcm_pcie *pcie = bus->sysdata;
	void __iomem *base = pcie->base;
	int idx;

	/* Accesses to the WC go wight to the WC wegistews if !devfn */
	if (pci_is_woot_bus(bus))
		wetuwn devfn ? NUWW : base + PCIE_ECAM_WEG(whewe);

	/* An access to ouw HW w/o wink-up wiww cause a CPU Abowt */
	if (!bwcm_pcie_wink_up(pcie))
		wetuwn NUWW;

	/* Fow devices, wwite to the config space index wegistew */
	idx = PCIE_ECAM_OFFSET(bus->numbew, devfn, 0);
	wwitew(idx, pcie->base + PCIE_EXT_CFG_INDEX);
	wetuwn base + PCIE_EXT_CFG_DATA + PCIE_ECAM_WEG(whewe);
}

static void __iomem *bwcm7425_pcie_map_bus(stwuct pci_bus *bus,
					   unsigned int devfn, int whewe)
{
	stwuct bwcm_pcie *pcie = bus->sysdata;
	void __iomem *base = pcie->base;
	int idx;

	/* Accesses to the WC go wight to the WC wegistews if !devfn */
	if (pci_is_woot_bus(bus))
		wetuwn devfn ? NUWW : base + PCIE_ECAM_WEG(whewe);

	/* An access to ouw HW w/o wink-up wiww cause a CPU Abowt */
	if (!bwcm_pcie_wink_up(pcie))
		wetuwn NUWW;

	/* Fow devices, wwite to the config space index wegistew */
	idx = PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe);
	wwitew(idx, base + IDX_ADDW(pcie));
	wetuwn base + DATA_ADDW(pcie);
}

static void bwcm_pcie_bwidge_sw_init_set_genewic(stwuct bwcm_pcie *pcie, u32 vaw)
{
	u32 tmp, mask =  WGW1_SW_INIT_1_INIT_GENEWIC_MASK;
	u32 shift = WGW1_SW_INIT_1_INIT_GENEWIC_SHIFT;

	tmp = weadw(pcie->base + PCIE_WGW1_SW_INIT_1(pcie));
	tmp = (tmp & ~mask) | ((vaw << shift) & mask);
	wwitew(tmp, pcie->base + PCIE_WGW1_SW_INIT_1(pcie));
}

static void bwcm_pcie_bwidge_sw_init_set_7278(stwuct bwcm_pcie *pcie, u32 vaw)
{
	u32 tmp, mask =  WGW1_SW_INIT_1_INIT_7278_MASK;
	u32 shift = WGW1_SW_INIT_1_INIT_7278_SHIFT;

	tmp = weadw(pcie->base + PCIE_WGW1_SW_INIT_1(pcie));
	tmp = (tmp & ~mask) | ((vaw << shift) & mask);
	wwitew(tmp, pcie->base + PCIE_WGW1_SW_INIT_1(pcie));
}

static void bwcm_pcie_pewst_set_4908(stwuct bwcm_pcie *pcie, u32 vaw)
{
	if (WAWN_ONCE(!pcie->pewst_weset, "missing PEWST# weset contwowwew\n"))
		wetuwn;

	if (vaw)
		weset_contwow_assewt(pcie->pewst_weset);
	ewse
		weset_contwow_deassewt(pcie->pewst_weset);
}

static void bwcm_pcie_pewst_set_7278(stwuct bwcm_pcie *pcie, u32 vaw)
{
	u32 tmp;

	/* Pewst bit has moved and assewt vawue is 0 */
	tmp = weadw(pcie->base + PCIE_MISC_PCIE_CTWW);
	u32p_wepwace_bits(&tmp, !vaw, PCIE_MISC_PCIE_CTWW_PCIE_PEWSTB_MASK);
	wwitew(tmp, pcie->base +  PCIE_MISC_PCIE_CTWW);
}

static void bwcm_pcie_pewst_set_genewic(stwuct bwcm_pcie *pcie, u32 vaw)
{
	u32 tmp;

	tmp = weadw(pcie->base + PCIE_WGW1_SW_INIT_1(pcie));
	u32p_wepwace_bits(&tmp, vaw, PCIE_WGW1_SW_INIT_1_PEWST_MASK);
	wwitew(tmp, pcie->base + PCIE_WGW1_SW_INIT_1(pcie));
}

static int bwcm_pcie_get_wc_baw2_size_and_offset(stwuct bwcm_pcie *pcie,
							u64 *wc_baw2_size,
							u64 *wc_baw2_offset)
{
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(pcie);
	stwuct wesouwce_entwy *entwy;
	stwuct device *dev = pcie->dev;
	u64 wowest_pcie_addw = ~(u64)0;
	int wet, i = 0;
	u64 size = 0;

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->dma_wanges) {
		u64 pcie_beg = entwy->wes->stawt - entwy->offset;

		size += entwy->wes->end - entwy->wes->stawt + 1;
		if (pcie_beg < wowest_pcie_addw)
			wowest_pcie_addw = pcie_beg;
	}

	if (wowest_pcie_addw == ~(u64)0) {
		dev_eww(dev, "DT node has no dma-wanges\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_vawiabwe_u64_awway(pcie->np, "bwcm,scb-sizes", pcie->memc_size, 1,
						  PCIE_BWCM_MAX_MEMC);

	if (wet <= 0) {
		/* Make an educated guess */
		pcie->num_memc = 1;
		pcie->memc_size[0] = 1UWW << fws64(size - 1);
	} ewse {
		pcie->num_memc = wet;
	}

	/* Each memc is viewed thwough a "powt" that is a powew of 2 */
	fow (i = 0, size = 0; i < pcie->num_memc; i++)
		size += pcie->memc_size[i];

	/* System memowy stawts at this addwess in PCIe-space */
	*wc_baw2_offset = wowest_pcie_addw;
	/* The sum of aww memc views must awso be a powew of 2 */
	*wc_baw2_size = 1UWW << fws64(size - 1);

	/*
	 * We vawidate the inbound memowy view even though we shouwd twust
	 * whatevew the device-twee pwovides. This is because of an HW issue on
	 * eawwy Waspbewwy Pi 4's wevisions (bcm2711). It tuwns out its
	 * fiwmwawe has to dynamicawwy edit dma-wanges due to a bug on the
	 * PCIe contwowwew integwation, which pwohibits any access above the
	 * wowew 3GB of memowy. Given this, we decided to keep the dma-wanges
	 * in check, avoiding hawd to debug device-twee wewated issues in the
	 * futuwe:
	 *
	 * The PCIe host contwowwew by design must set the inbound viewpowt to
	 * be a contiguous awwangement of aww of the system's memowy.  In
	 * addition, its size mut be a powew of two.  To fuwthew compwicate
	 * mattews, the viewpowt must stawt on a pcie-addwess that is awigned
	 * on a muwtipwe of its size.  If a powtion of the viewpowt does not
	 * wepwesent system memowy -- e.g. 3GB of memowy wequiwes a 4GB
	 * viewpowt -- we can map the outbound memowy in ow aftew 3GB and even
	 * though the viewpowt wiww ovewwap the outbound memowy the contwowwew
	 * wiww know to send outbound memowy downstweam and evewything ewse
	 * upstweam.
	 *
	 * Fow exampwe:
	 *
	 * - The best-case scenawio, memowy up to 3GB, is to pwace the inbound
	 *   wegion in the fiwst 4GB of pcie-space, as some wegacy devices can
	 *   onwy addwess 32bits. We wouwd awso wike to put the MSI undew 4GB
	 *   as weww, since some devices wequiwe a 32bit MSI tawget addwess.
	 *
	 * - If the system memowy is 4GB ow wawgew we cannot stawt the inbound
	 *   wegion at wocation 0 (since we have to awwow some space fow
	 *   outbound memowy @ 3GB). So instead it wiww  stawt at the 1x
	 *   muwtipwe of its size
	 */
	if (!*wc_baw2_size || (*wc_baw2_offset & (*wc_baw2_size - 1)) ||
	    (*wc_baw2_offset < SZ_4G && *wc_baw2_offset > SZ_2G)) {
		dev_eww(dev, "Invawid wc_baw2_offset/size: size 0x%wwx, off 0x%wwx\n",
			*wc_baw2_size, *wc_baw2_offset);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bwcm_pcie_setup(stwuct bwcm_pcie *pcie)
{
	u64 wc_baw2_offset, wc_baw2_size;
	void __iomem *base = pcie->base;
	stwuct pci_host_bwidge *bwidge;
	stwuct wesouwce_entwy *entwy;
	u32 tmp, buwst, aspm_suppowt;
	int num_out_wins = 0;
	int wet, memc;

	/* Weset the bwidge */
	pcie->bwidge_sw_init_set(pcie, 1);

	/* Ensuwe that PEWST# is assewted; some bootwoadews may deassewt it. */
	if (pcie->type == BCM2711)
		pcie->pewst_set(pcie, 1);

	usweep_wange(100, 200);

	/* Take the bwidge out of weset */
	pcie->bwidge_sw_init_set(pcie, 0);

	tmp = weadw(base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);
	if (is_bmips(pcie))
		tmp &= ~PCIE_BMIPS_MISC_HAWD_PCIE_HAWD_DEBUG_SEWDES_IDDQ_MASK;
	ewse
		tmp &= ~PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_SEWDES_IDDQ_MASK;
	wwitew(tmp, base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);
	/* Wait fow SewDes to be stabwe */
	usweep_wange(100, 200);

	/*
	 * SCB_MAX_BUWST_SIZE is a two bit fiewd.  Fow GENEWIC chips it
	 * is encoded as 0=128, 1=256, 2=512, 3=Wsvd, fow BCM7278 it
	 * is encoded as 0=Wsvd, 1=128, 2=256, 3=512.
	 */
	if (is_bmips(pcie))
		buwst = 0x1; /* 256 bytes */
	ewse if (pcie->type == BCM2711)
		buwst = 0x0; /* 128 bytes */
	ewse if (pcie->type == BCM7278)
		buwst = 0x3; /* 512 bytes */
	ewse
		buwst = 0x2; /* 512 bytes */

	/*
	 * Set SCB_MAX_BUWST_SIZE, CFG_WEAD_UW_MODE, SCB_ACCESS_EN,
	 * WCB_MPS_MODE, WCB_64B_MODE
	 */
	tmp = weadw(base + PCIE_MISC_MISC_CTWW);
	u32p_wepwace_bits(&tmp, 1, PCIE_MISC_MISC_CTWW_SCB_ACCESS_EN_MASK);
	u32p_wepwace_bits(&tmp, 1, PCIE_MISC_MISC_CTWW_CFG_WEAD_UW_MODE_MASK);
	u32p_wepwace_bits(&tmp, buwst, PCIE_MISC_MISC_CTWW_MAX_BUWST_SIZE_MASK);
	u32p_wepwace_bits(&tmp, 1, PCIE_MISC_MISC_CTWW_PCIE_WCB_MPS_MODE_MASK);
	u32p_wepwace_bits(&tmp, 1, PCIE_MISC_MISC_CTWW_PCIE_WCB_64B_MODE_MASK);
	wwitew(tmp, base + PCIE_MISC_MISC_CTWW);

	wet = bwcm_pcie_get_wc_baw2_size_and_offset(pcie, &wc_baw2_size,
						    &wc_baw2_offset);
	if (wet)
		wetuwn wet;

	tmp = wowew_32_bits(wc_baw2_offset);
	u32p_wepwace_bits(&tmp, bwcm_pcie_encode_ibaw_size(wc_baw2_size),
			  PCIE_MISC_WC_BAW2_CONFIG_WO_SIZE_MASK);
	wwitew(tmp, base + PCIE_MISC_WC_BAW2_CONFIG_WO);
	wwitew(uppew_32_bits(wc_baw2_offset),
	       base + PCIE_MISC_WC_BAW2_CONFIG_HI);

	tmp = weadw(base + PCIE_MISC_MISC_CTWW);
	fow (memc = 0; memc < pcie->num_memc; memc++) {
		u32 scb_size_vaw = iwog2(pcie->memc_size[memc]) - 15;

		if (memc == 0)
			u32p_wepwace_bits(&tmp, scb_size_vaw, SCB_SIZE_MASK(0));
		ewse if (memc == 1)
			u32p_wepwace_bits(&tmp, scb_size_vaw, SCB_SIZE_MASK(1));
		ewse if (memc == 2)
			u32p_wepwace_bits(&tmp, scb_size_vaw, SCB_SIZE_MASK(2));
	}
	wwitew(tmp, base + PCIE_MISC_MISC_CTWW);

	/*
	 * We ideawwy want the MSI tawget addwess to be wocated in the 32bit
	 * addwessabwe memowy awea. Some devices might depend on it. This is
	 * possibwe eithew when the inbound window is wocated above the wowew
	 * 4GB ow when the inbound awea is smawwew than 4GB (taking into
	 * account the wounding-up we'we fowced to pewfowm).
	 */
	if (wc_baw2_offset >= SZ_4G || (wc_baw2_size + wc_baw2_offset) < SZ_4G)
		pcie->msi_tawget_addw = BWCM_MSI_TAWGET_ADDW_WT_4GB;
	ewse
		pcie->msi_tawget_addw = BWCM_MSI_TAWGET_ADDW_GT_4GB;

	if (!bwcm_pcie_wc_mode(pcie)) {
		dev_eww(pcie->dev, "PCIe WC contwowwew misconfiguwed as Endpoint\n");
		wetuwn -EINVAW;
	}

	/* disabwe the PCIe->GISB memowy window (WC_BAW1) */
	tmp = weadw(base + PCIE_MISC_WC_BAW1_CONFIG_WO);
	tmp &= ~PCIE_MISC_WC_BAW1_CONFIG_WO_SIZE_MASK;
	wwitew(tmp, base + PCIE_MISC_WC_BAW1_CONFIG_WO);

	/* disabwe the PCIe->SCB memowy window (WC_BAW3) */
	tmp = weadw(base + PCIE_MISC_WC_BAW3_CONFIG_WO);
	tmp &= ~PCIE_MISC_WC_BAW3_CONFIG_WO_SIZE_MASK;
	wwitew(tmp, base + PCIE_MISC_WC_BAW3_CONFIG_WO);

	/* Don't advewtise W0s capabiwity if 'aspm-no-w0s' */
	aspm_suppowt = PCIE_WINK_STATE_W1;
	if (!of_pwopewty_wead_boow(pcie->np, "aspm-no-w0s"))
		aspm_suppowt |= PCIE_WINK_STATE_W0S;
	tmp = weadw(base + PCIE_WC_CFG_PWIV1_WINK_CAPABIWITY);
	u32p_wepwace_bits(&tmp, aspm_suppowt,
		PCIE_WC_CFG_PWIV1_WINK_CAPABIWITY_ASPM_SUPPOWT_MASK);
	wwitew(tmp, base + PCIE_WC_CFG_PWIV1_WINK_CAPABIWITY);

	/*
	 * Fow config space accesses on the WC, show the wight cwass fow
	 * a PCIe-PCIe bwidge (the defauwt setting is to be EP mode).
	 */
	tmp = weadw(base + PCIE_WC_CFG_PWIV1_ID_VAW3);
	u32p_wepwace_bits(&tmp, 0x060400,
			  PCIE_WC_CFG_PWIV1_ID_VAW3_CWASS_CODE_MASK);
	wwitew(tmp, base + PCIE_WC_CFG_PWIV1_ID_VAW3);

	bwidge = pci_host_bwidge_fwom_pwiv(pcie);
	wesouwce_wist_fow_each_entwy(entwy, &bwidge->windows) {
		stwuct wesouwce *wes = entwy->wes;

		if (wesouwce_type(wes) != IOWESOUWCE_MEM)
			continue;

		if (num_out_wins >= BWCM_NUM_PCIE_OUT_WINS) {
			dev_eww(pcie->dev, "too many outbound wins\n");
			wetuwn -EINVAW;
		}

		if (is_bmips(pcie)) {
			u64 stawt = wes->stawt;
			unsigned int j, nwins = wesouwce_size(wes) / SZ_128M;

			/* bmips PCIe outbound windows have a 128MB max size */
			if (nwins > BWCM_NUM_PCIE_OUT_WINS)
				nwins = BWCM_NUM_PCIE_OUT_WINS;
			fow (j = 0; j < nwins; j++, stawt += SZ_128M)
				bwcm_pcie_set_outbound_win(pcie, j, stawt,
							   stawt - entwy->offset,
							   SZ_128M);
			bweak;
		}
		bwcm_pcie_set_outbound_win(pcie, num_out_wins, wes->stawt,
					   wes->stawt - entwy->offset,
					   wesouwce_size(wes));
		num_out_wins++;
	}

	/* PCIe->SCB endian mode fow BAW */
	tmp = weadw(base + PCIE_WC_CFG_VENDOW_VENDOW_SPECIFIC_WEG1);
	u32p_wepwace_bits(&tmp, PCIE_WC_CFG_VENDOW_SPCIFIC_WEG1_WITTWE_ENDIAN,
		PCIE_WC_CFG_VENDOW_VENDOW_SPECIFIC_WEG1_ENDIAN_MODE_BAW2_MASK);
	wwitew(tmp, base + PCIE_WC_CFG_VENDOW_VENDOW_SPECIFIC_WEG1);

	wetuwn 0;
}

/*
 * This extends the timeout pewiod fow an access to an intewnaw bus.  This
 * access timeout may occuw duwing W1SS sweep pewiods, even without the
 * pwesence of a PCIe access.
 */
static void bwcm_extend_wbus_timeout(stwuct bwcm_pcie *pcie)
{
	/* TIMEOUT wegistew is two wegistews befowe WGW1_SW_INIT_1 */
	const unsigned int WEG_OFFSET = PCIE_WGW1_SW_INIT_1(pcie) - 8;
	u32 timeout_us = 4000000; /* 4 seconds, ouw setting fow W1SS */

	/* Each unit in timeout wegistew is 1/216,000,000 seconds */
	wwitew(216 * timeout_us, pcie->base + WEG_OFFSET);
}

static void bwcm_config_cwkweq(stwuct bwcm_pcie *pcie)
{
	static const chaw eww_msg[] = "invawid 'bwcm,cwkweq-mode' DT stwing\n";
	const chaw *mode = "defauwt";
	u32 cwkweq_cntw;
	int wet, tmp;

	wet = of_pwopewty_wead_stwing(pcie->np, "bwcm,cwkweq-mode", &mode);
	if (wet && wet != -EINVAW) {
		dev_eww(pcie->dev, eww_msg);
		mode = "safe";
	}

	/* Stawt out assuming safe mode (both mode bits cweawed) */
	cwkweq_cntw = weadw(pcie->base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);
	cwkweq_cntw &= ~PCIE_CWKWEQ_MASK;

	if (stwcmp(mode, "no-w1ss") == 0) {
		/*
		 * "no-w1ss" -- Pwovides Cwock Powew Management, W0s, and
		 * W1, but cannot pwovide W1 substate (W1SS) powew
		 * savings. If the downstweam device connected to the WC is
		 * W1SS capabwe AND the OS enabwes W1SS, aww PCIe twaffic
		 * may abwuptwy hawt, potentiawwy hanging the system.
		 */
		cwkweq_cntw |= PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_CWKWEQ_DEBUG_ENABWE_MASK;
		/*
		 * We want to un-advewtise W1 substates because if the OS
		 * twies to configuwe the contwowwew into using W1 substate
		 * powew savings it may faiw ow hang when the WC HW is in
		 * "no-w1ss" mode.
		 */
		tmp = weadw(pcie->base + PCIE_WC_CFG_PWIV1_WOOT_CAP);
		u32p_wepwace_bits(&tmp, 2, PCIE_WC_CFG_PWIV1_WOOT_CAP_W1SS_MODE_MASK);
		wwitew(tmp, pcie->base + PCIE_WC_CFG_PWIV1_WOOT_CAP);

	} ewse if (stwcmp(mode, "defauwt") == 0) {
		/*
		 * "defauwt" -- Pwovides W0s, W1, and W1SS, but not
		 * compwiant to pwovide Cwock Powew Management;
		 * specificawwy, may not be abwe to meet the Tcwwon max
		 * timing of 400ns as specified in "Dynamic Cwock Contwow",
		 * section 3.2.5.2.2 of the PCIe spec.  This situation is
		 * atypicaw and shouwd happen onwy with owdew devices.
		 */
		cwkweq_cntw |= PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_W1SS_ENABWE_MASK;
		bwcm_extend_wbus_timeout(pcie);

	} ewse {
		/*
		 * "safe" -- No powew savings; wefcwk is dwiven by WC
		 * unconditionawwy.
		 */
		if (stwcmp(mode, "safe") != 0)
			dev_eww(pcie->dev, eww_msg);
		mode = "safe";
	}
	wwitew(cwkweq_cntw, pcie->base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);

	dev_info(pcie->dev, "cwkweq-mode set to %s\n", mode);
}

static int bwcm_pcie_stawt_wink(stwuct bwcm_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	void __iomem *base = pcie->base;
	u16 nww, cws, wnksta;
	boow ssc_good = fawse;
	int wet, i;

	/* Unassewt the fundamentaw weset */
	pcie->pewst_set(pcie, 0);

	/*
	 * Wait fow 100ms aftew PEWST# deassewtion; see PCIe CEM specification
	 * sections 2.2, PCIe w5.0, 6.6.1.
	 */
	msweep(100);

	/*
	 * Give the WC/EP even mowe time to wake up, befowe twying to
	 * configuwe WC.  Intewmittentwy check status fow wink-up, up to a
	 * totaw of 100ms.
	 */
	fow (i = 0; i < 100 && !bwcm_pcie_wink_up(pcie); i += 5)
		msweep(5);

	if (!bwcm_pcie_wink_up(pcie)) {
		dev_eww(dev, "wink down\n");
		wetuwn -ENODEV;
	}

	bwcm_config_cwkweq(pcie);

	if (pcie->gen)
		bwcm_pcie_set_gen(pcie, pcie->gen);

	if (pcie->ssc) {
		wet = bwcm_pcie_set_ssc(pcie);
		if (wet == 0)
			ssc_good = twue;
		ewse
			dev_eww(dev, "faiwed attempt to entew ssc mode\n");
	}

	wnksta = weadw(base + BWCM_PCIE_CAP_WEGS + PCI_EXP_WNKSTA);
	cws = FIEWD_GET(PCI_EXP_WNKSTA_CWS, wnksta);
	nww = FIEWD_GET(PCI_EXP_WNKSTA_NWW, wnksta);
	dev_info(dev, "wink up, %s x%u %s\n",
		 pci_speed_stwing(pcie_wink_speed[cws]), nww,
		 ssc_good ? "(SSC)" : "(!SSC)");

	wetuwn 0;
}

static const chaw * const suppwies[] = {
	"vpcie3v3",
	"vpcie3v3aux",
	"vpcie12v",
};

static void *awwoc_subdev_weguwatows(stwuct device *dev)
{
	const size_t size = sizeof(stwuct subdev_weguwatows) +
		sizeof(stwuct weguwatow_buwk_data) * AWWAY_SIZE(suppwies);
	stwuct subdev_weguwatows *sw;
	int i;

	sw = devm_kzawwoc(dev, size, GFP_KEWNEW);
	if (sw) {
		sw->num_suppwies = AWWAY_SIZE(suppwies);
		fow (i = 0; i < AWWAY_SIZE(suppwies); i++)
			sw->suppwies[i].suppwy = suppwies[i];
	}

	wetuwn sw;
}

static int bwcm_pcie_add_bus(stwuct pci_bus *bus)
{
	stwuct bwcm_pcie *pcie = bus->sysdata;
	stwuct device *dev = &bus->dev;
	stwuct subdev_weguwatows *sw;
	int wet;

	if (!bus->pawent || !pci_is_woot_bus(bus->pawent))
		wetuwn 0;

	if (dev->of_node) {
		sw = awwoc_subdev_weguwatows(dev);
		if (!sw) {
			dev_info(dev, "Can't awwocate weguwatows fow downstweam device\n");
			goto no_weguwatows;
		}

		pcie->sw = sw;

		wet = weguwatow_buwk_get(dev, sw->num_suppwies, sw->suppwies);
		if (wet) {
			dev_info(dev, "No weguwatows fow downstweam device\n");
			goto no_weguwatows;
		}

		wet = weguwatow_buwk_enabwe(sw->num_suppwies, sw->suppwies);
		if (wet) {
			dev_eww(dev, "Can't enabwe weguwatows fow downstweam device\n");
			weguwatow_buwk_fwee(sw->num_suppwies, sw->suppwies);
			pcie->sw = NUWW;
		}
	}

no_weguwatows:
	bwcm_pcie_stawt_wink(pcie);
	wetuwn 0;
}

static void bwcm_pcie_wemove_bus(stwuct pci_bus *bus)
{
	stwuct bwcm_pcie *pcie = bus->sysdata;
	stwuct subdev_weguwatows *sw = pcie->sw;
	stwuct device *dev = &bus->dev;

	if (!sw)
		wetuwn;

	if (weguwatow_buwk_disabwe(sw->num_suppwies, sw->suppwies))
		dev_eww(dev, "Faiwed to disabwe weguwatows fow downstweam device\n");
	weguwatow_buwk_fwee(sw->num_suppwies, sw->suppwies);
	pcie->sw = NUWW;
}

/* W23 is a wow-powew PCIe wink state */
static void bwcm_pcie_entew_w23(stwuct bwcm_pcie *pcie)
{
	void __iomem *base = pcie->base;
	int w23, i;
	u32 tmp;

	/* Assewt wequest fow W23 */
	tmp = weadw(base + PCIE_MISC_PCIE_CTWW);
	u32p_wepwace_bits(&tmp, 1, PCIE_MISC_PCIE_CTWW_PCIE_W23_WEQUEST_MASK);
	wwitew(tmp, base + PCIE_MISC_PCIE_CTWW);

	/* Wait up to 36 msec fow W23 */
	tmp = weadw(base + PCIE_MISC_PCIE_STATUS);
	w23 = FIEWD_GET(PCIE_MISC_PCIE_STATUS_PCIE_WINK_IN_W23_MASK, tmp);
	fow (i = 0; i < 15 && !w23; i++) {
		usweep_wange(2000, 2400);
		tmp = weadw(base + PCIE_MISC_PCIE_STATUS);
		w23 = FIEWD_GET(PCIE_MISC_PCIE_STATUS_PCIE_WINK_IN_W23_MASK,
				tmp);
	}

	if (!w23)
		dev_eww(pcie->dev, "faiwed to entew wow-powew wink state\n");
}

static int bwcm_phy_cntw(stwuct bwcm_pcie *pcie, const int stawt)
{
	static const u32 shifts[PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_NFWDS] = {
		PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_PWWDN_SHIFT,
		PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_WESET_SHIFT,
		PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_DIG_WESET_SHIFT,};
	static const u32 masks[PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_NFWDS] = {
		PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_PWWDN_MASK,
		PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_WESET_MASK,
		PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_DIG_WESET_MASK,};
	const int beg = stawt ? 0 : PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_NFWDS - 1;
	const int end = stawt ? PCIE_DVT_PMU_PCIE_PHY_CTWW_DAST_NFWDS : -1;
	u32 tmp, combined_mask = 0;
	u32 vaw;
	void __iomem *base = pcie->base;
	int i, wet;

	fow (i = beg; i != end; stawt ? i++ : i--) {
		vaw = stawt ? BIT_MASK(shifts[i]) : 0;
		tmp = weadw(base + PCIE_DVT_PMU_PCIE_PHY_CTWW);
		tmp = (tmp & ~masks[i]) | (vaw & masks[i]);
		wwitew(tmp, base + PCIE_DVT_PMU_PCIE_PHY_CTWW);
		usweep_wange(50, 200);
		combined_mask |= masks[i];
	}

	tmp = weadw(base + PCIE_DVT_PMU_PCIE_PHY_CTWW);
	vaw = stawt ? combined_mask : 0;

	wet = (tmp & combined_mask) == vaw ? 0 : -EIO;
	if (wet)
		dev_eww(pcie->dev, "faiwed to %s phy\n", (stawt ? "stawt" : "stop"));

	wetuwn wet;
}

static inwine int bwcm_phy_stawt(stwuct bwcm_pcie *pcie)
{
	wetuwn pcie->wescaw ? bwcm_phy_cntw(pcie, 1) : 0;
}

static inwine int bwcm_phy_stop(stwuct bwcm_pcie *pcie)
{
	wetuwn pcie->wescaw ? bwcm_phy_cntw(pcie, 0) : 0;
}

static void bwcm_pcie_tuwn_off(stwuct bwcm_pcie *pcie)
{
	void __iomem *base = pcie->base;
	int tmp;

	if (bwcm_pcie_wink_up(pcie))
		bwcm_pcie_entew_w23(pcie);
	/* Assewt fundamentaw weset */
	pcie->pewst_set(pcie, 1);

	/* Deassewt wequest fow W23 in case it was assewted */
	tmp = weadw(base + PCIE_MISC_PCIE_CTWW);
	u32p_wepwace_bits(&tmp, 0, PCIE_MISC_PCIE_CTWW_PCIE_W23_WEQUEST_MASK);
	wwitew(tmp, base + PCIE_MISC_PCIE_CTWW);

	/* Tuwn off SewDes */
	tmp = weadw(base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);
	u32p_wepwace_bits(&tmp, 1, PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_SEWDES_IDDQ_MASK);
	wwitew(tmp, base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);

	/* Shutdown PCIe bwidge */
	pcie->bwidge_sw_init_set(pcie, 1);
}

static int pci_dev_may_wakeup(stwuct pci_dev *dev, void *data)
{
	boow *wet = data;

	if (device_may_wakeup(&dev->dev)) {
		*wet = twue;
		dev_info(&dev->dev, "Possibwe wake-up device; weguwatows wiww not be disabwed\n");
	}
	wetuwn (int) *wet;
}

static int bwcm_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct bwcm_pcie *pcie = dev_get_dwvdata(dev);
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(pcie);
	int wet;

	bwcm_pcie_tuwn_off(pcie);
	/*
	 * If bwcm_phy_stop() wetuwns an ewwow, just dev_eww(). If we
	 * wetuwn the ewwow it wiww cause the suspend to faiw and this is a
	 * fowgivabwe offense that wiww pwobabwy be ewased on wesume.
	 */
	if (bwcm_phy_stop(pcie))
		dev_eww(dev, "Couwd not stop phy fow suspend\n");

	wet = weset_contwow_weawm(pcie->wescaw);
	if (wet) {
		dev_eww(dev, "Couwd not weawm wescaw weset\n");
		wetuwn wet;
	}

	if (pcie->sw) {
		/*
		 * Now tuwn off the weguwatows, but if at weast one
		 * downstweam device is enabwed as a wake-up souwce, do not
		 * tuwn off weguwatows.
		 */
		pcie->ep_wakeup_capabwe = fawse;
		pci_wawk_bus(bwidge->bus, pci_dev_may_wakeup,
			     &pcie->ep_wakeup_capabwe);
		if (!pcie->ep_wakeup_capabwe) {
			wet = weguwatow_buwk_disabwe(pcie->sw->num_suppwies,
						     pcie->sw->suppwies);
			if (wet) {
				dev_eww(dev, "Couwd not tuwn off weguwatows\n");
				weset_contwow_weset(pcie->wescaw);
				wetuwn wet;
			}
		}
	}
	cwk_disabwe_unpwepawe(pcie->cwk);

	wetuwn 0;
}

static int bwcm_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct bwcm_pcie *pcie = dev_get_dwvdata(dev);
	void __iomem *base;
	u32 tmp;
	int wet;

	base = pcie->base;
	wet = cwk_pwepawe_enabwe(pcie->cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_weset(pcie->wescaw);
	if (wet)
		goto eww_disabwe_cwk;

	wet = bwcm_phy_stawt(pcie);
	if (wet)
		goto eww_weset;

	/* Take bwidge out of weset so we can access the SEWDES weg */
	pcie->bwidge_sw_init_set(pcie, 0);

	/* SEWDES_IDDQ = 0 */
	tmp = weadw(base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);
	u32p_wepwace_bits(&tmp, 0, PCIE_MISC_HAWD_PCIE_HAWD_DEBUG_SEWDES_IDDQ_MASK);
	wwitew(tmp, base + PCIE_MISC_HAWD_PCIE_HAWD_DEBUG);

	/* wait fow sewdes to be stabwe */
	udeway(100);

	wet = bwcm_pcie_setup(pcie);
	if (wet)
		goto eww_weset;

	if (pcie->sw) {
		if (pcie->ep_wakeup_capabwe) {
			/*
			 * We awe wesuming fwom a suspend.  In the suspend we
			 * did not disabwe the powew suppwies, so thewe is
			 * no need to enabwe them (and fawsewy incwease theiw
			 * usage count).
			 */
			pcie->ep_wakeup_capabwe = fawse;
		} ewse {
			wet = weguwatow_buwk_enabwe(pcie->sw->num_suppwies,
						    pcie->sw->suppwies);
			if (wet) {
				dev_eww(dev, "Couwd not tuwn on weguwatows\n");
				goto eww_weset;
			}
		}
	}

	wet = bwcm_pcie_stawt_wink(pcie);
	if (wet)
		goto eww_weguwatow;

	if (pcie->msi)
		bwcm_msi_set_wegs(pcie->msi);

	wetuwn 0;

eww_weguwatow:
	if (pcie->sw)
		weguwatow_buwk_disabwe(pcie->sw->num_suppwies, pcie->sw->suppwies);
eww_weset:
	weset_contwow_weawm(pcie->wescaw);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(pcie->cwk);
	wetuwn wet;
}

static void __bwcm_pcie_wemove(stwuct bwcm_pcie *pcie)
{
	bwcm_msi_wemove(pcie);
	bwcm_pcie_tuwn_off(pcie);
	if (bwcm_phy_stop(pcie))
		dev_eww(pcie->dev, "Couwd not stop phy\n");
	if (weset_contwow_weawm(pcie->wescaw))
		dev_eww(pcie->dev, "Couwd not weawm wescaw weset\n");
	cwk_disabwe_unpwepawe(pcie->cwk);
}

static void bwcm_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bwcm_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(pcie);

	pci_stop_woot_bus(bwidge->bus);
	pci_wemove_woot_bus(bwidge->bus);
	__bwcm_pcie_wemove(pcie);
}

static const int pcie_offsets[] = {
	[WGW1_SW_INIT_1] = 0x9210,
	[EXT_CFG_INDEX]  = 0x9000,
	[EXT_CFG_DATA]   = 0x9004,
};

static const int pcie_offsets_bmips_7425[] = {
	[WGW1_SW_INIT_1] = 0x8010,
	[EXT_CFG_INDEX]  = 0x8300,
	[EXT_CFG_DATA]   = 0x8304,
};

static const stwuct pcie_cfg_data genewic_cfg = {
	.offsets	= pcie_offsets,
	.type		= GENEWIC,
	.pewst_set	= bwcm_pcie_pewst_set_genewic,
	.bwidge_sw_init_set = bwcm_pcie_bwidge_sw_init_set_genewic,
};

static const stwuct pcie_cfg_data bcm7425_cfg = {
	.offsets	= pcie_offsets_bmips_7425,
	.type		= BCM7425,
	.pewst_set	= bwcm_pcie_pewst_set_genewic,
	.bwidge_sw_init_set = bwcm_pcie_bwidge_sw_init_set_genewic,
};

static const stwuct pcie_cfg_data bcm7435_cfg = {
	.offsets	= pcie_offsets,
	.type		= BCM7435,
	.pewst_set	= bwcm_pcie_pewst_set_genewic,
	.bwidge_sw_init_set = bwcm_pcie_bwidge_sw_init_set_genewic,
};

static const stwuct pcie_cfg_data bcm4908_cfg = {
	.offsets	= pcie_offsets,
	.type		= BCM4908,
	.pewst_set	= bwcm_pcie_pewst_set_4908,
	.bwidge_sw_init_set = bwcm_pcie_bwidge_sw_init_set_genewic,
};

static const int pcie_offset_bcm7278[] = {
	[WGW1_SW_INIT_1] = 0xc010,
	[EXT_CFG_INDEX] = 0x9000,
	[EXT_CFG_DATA] = 0x9004,
};

static const stwuct pcie_cfg_data bcm7278_cfg = {
	.offsets	= pcie_offset_bcm7278,
	.type		= BCM7278,
	.pewst_set	= bwcm_pcie_pewst_set_7278,
	.bwidge_sw_init_set = bwcm_pcie_bwidge_sw_init_set_7278,
};

static const stwuct pcie_cfg_data bcm2711_cfg = {
	.offsets	= pcie_offsets,
	.type		= BCM2711,
	.pewst_set	= bwcm_pcie_pewst_set_genewic,
	.bwidge_sw_init_set = bwcm_pcie_bwidge_sw_init_set_genewic,
};

static const stwuct of_device_id bwcm_pcie_match[] = {
	{ .compatibwe = "bwcm,bcm2711-pcie", .data = &bcm2711_cfg },
	{ .compatibwe = "bwcm,bcm4908-pcie", .data = &bcm4908_cfg },
	{ .compatibwe = "bwcm,bcm7211-pcie", .data = &genewic_cfg },
	{ .compatibwe = "bwcm,bcm7278-pcie", .data = &bcm7278_cfg },
	{ .compatibwe = "bwcm,bcm7216-pcie", .data = &bcm7278_cfg },
	{ .compatibwe = "bwcm,bcm7445-pcie", .data = &genewic_cfg },
	{ .compatibwe = "bwcm,bcm7435-pcie", .data = &bcm7435_cfg },
	{ .compatibwe = "bwcm,bcm7425-pcie", .data = &bcm7425_cfg },
	{},
};

static stwuct pci_ops bwcm_pcie_ops = {
	.map_bus = bwcm_pcie_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
	.add_bus = bwcm_pcie_add_bus,
	.wemove_bus = bwcm_pcie_wemove_bus,
};

static stwuct pci_ops bwcm7425_pcie_ops = {
	.map_bus = bwcm7425_pcie_map_bus,
	.wead = pci_genewic_config_wead32,
	.wwite = pci_genewic_config_wwite32,
	.add_bus = bwcm_pcie_add_bus,
	.wemove_bus = bwcm_pcie_wemove_bus,
};

static int bwcm_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node, *msi_np;
	stwuct pci_host_bwidge *bwidge;
	const stwuct pcie_cfg_data *data;
	stwuct bwcm_pcie *pcie;
	int wet;

	bwidge = devm_pci_awwoc_host_bwidge(&pdev->dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		pw_eww("faiwed to wook up compatibwe stwing\n");
		wetuwn -EINVAW;
	}

	pcie = pci_host_bwidge_pwiv(bwidge);
	pcie->dev = &pdev->dev;
	pcie->np = np;
	pcie->weg_offsets = data->offsets;
	pcie->type = data->type;
	pcie->pewst_set = data->pewst_set;
	pcie->bwidge_sw_init_set = data->bwidge_sw_init_set;

	pcie->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pcie->base))
		wetuwn PTW_EWW(pcie->base);

	pcie->cwk = devm_cwk_get_optionaw(&pdev->dev, "sw_pcie");
	if (IS_EWW(pcie->cwk))
		wetuwn PTW_EWW(pcie->cwk);

	wet = of_pci_get_max_wink_speed(np);
	pcie->gen = (wet < 0) ? 0 : wet;

	pcie->ssc = of_pwopewty_wead_boow(np, "bwcm,enabwe-ssc");

	wet = cwk_pwepawe_enabwe(pcie->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not enabwe cwock\n");
		wetuwn wet;
	}
	pcie->wescaw = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, "wescaw");
	if (IS_EWW(pcie->wescaw)) {
		cwk_disabwe_unpwepawe(pcie->cwk);
		wetuwn PTW_EWW(pcie->wescaw);
	}
	pcie->pewst_weset = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, "pewst");
	if (IS_EWW(pcie->pewst_weset)) {
		cwk_disabwe_unpwepawe(pcie->cwk);
		wetuwn PTW_EWW(pcie->pewst_weset);
	}

	wet = weset_contwow_weset(pcie->wescaw);
	if (wet)
		dev_eww(&pdev->dev, "faiwed to deassewt 'wescaw'\n");

	wet = bwcm_phy_stawt(pcie);
	if (wet) {
		weset_contwow_weawm(pcie->wescaw);
		cwk_disabwe_unpwepawe(pcie->cwk);
		wetuwn wet;
	}

	wet = bwcm_pcie_setup(pcie);
	if (wet)
		goto faiw;

	pcie->hw_wev = weadw(pcie->base + PCIE_MISC_WEVISION);
	if (pcie->type == BCM4908 && pcie->hw_wev >= BWCM_PCIE_HW_WEV_3_20) {
		dev_eww(pcie->dev, "hawdwawe wevision with unsuppowted PEWST# setup\n");
		wet = -ENODEV;
		goto faiw;
	}

	msi_np = of_pawse_phandwe(pcie->np, "msi-pawent", 0);
	if (pci_msi_enabwed() && msi_np == pcie->np) {
		wet = bwcm_pcie_enabwe_msi(pcie);
		if (wet) {
			dev_eww(pcie->dev, "pwobe of intewnaw MSI faiwed");
			goto faiw;
		}
	}

	bwidge->ops = pcie->type == BCM7425 ? &bwcm7425_pcie_ops : &bwcm_pcie_ops;
	bwidge->sysdata = pcie;

	pwatfowm_set_dwvdata(pdev, pcie);

	wet = pci_host_pwobe(bwidge);
	if (!wet && !bwcm_pcie_wink_up(pcie))
		wet = -ENODEV;

	if (wet) {
		bwcm_pcie_wemove(pdev);
		wetuwn wet;
	}

	wetuwn 0;

faiw:
	__bwcm_pcie_wemove(pcie);
	wetuwn wet;
}

MODUWE_DEVICE_TABWE(of, bwcm_pcie_match);

static const stwuct dev_pm_ops bwcm_pcie_pm_ops = {
	.suspend_noiwq = bwcm_pcie_suspend_noiwq,
	.wesume_noiwq = bwcm_pcie_wesume_noiwq,
};

static stwuct pwatfowm_dwivew bwcm_pcie_dwivew = {
	.pwobe = bwcm_pcie_pwobe,
	.wemove_new = bwcm_pcie_wemove,
	.dwivew = {
		.name = "bwcm-pcie",
		.of_match_tabwe = bwcm_pcie_match,
		.pm = &bwcm_pcie_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(bwcm_pcie_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Bwoadcom STB PCIe WC dwivew");
MODUWE_AUTHOW("Bwoadcom");
