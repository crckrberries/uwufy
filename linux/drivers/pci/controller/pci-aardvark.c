// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Aawdvawk PCIe contwowwew, used on Mawveww Awmada
 * 3700.
 *
 * Copywight (C) 2016 Mawveww
 *
 * Authow: Hezi Shahmoon <hezi.shahmoon@mawveww.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/init.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_pci.h>

#incwude "../pci.h"
#incwude "../pci-bwidge-emuw.h"

/* PCIe cowe wegistews */
#define PCIE_COWE_DEV_ID_WEG					0x0
#define PCIE_COWE_CMD_STATUS_WEG				0x4
#define PCIE_COWE_DEV_WEV_WEG					0x8
#define PCIE_COWE_SSDEV_ID_WEG					0x2c
#define PCIE_COWE_PCIEXP_CAP					0xc0
#define PCIE_COWE_PCIEWW_CAP					0x100
#define PCIE_COWE_EWW_CAPCTW_WEG				0x118
#define     PCIE_COWE_EWW_CAPCTW_ECWC_CHK_TX			BIT(5)
#define     PCIE_COWE_EWW_CAPCTW_ECWC_CHK_TX_EN			BIT(6)
#define     PCIE_COWE_EWW_CAPCTW_ECWC_CHCK			BIT(7)
#define     PCIE_COWE_EWW_CAPCTW_ECWC_CHCK_WCV			BIT(8)
/* PIO wegistews base addwess and wegistew offsets */
#define PIO_BASE_ADDW				0x4000
#define PIO_CTWW				(PIO_BASE_ADDW + 0x0)
#define   PIO_CTWW_TYPE_MASK			GENMASK(3, 0)
#define   PIO_CTWW_ADDW_WIN_DISABWE		BIT(24)
#define PIO_STAT				(PIO_BASE_ADDW + 0x4)
#define   PIO_COMPWETION_STATUS_SHIFT		7
#define   PIO_COMPWETION_STATUS_MASK		GENMASK(9, 7)
#define   PIO_COMPWETION_STATUS_OK		0
#define   PIO_COMPWETION_STATUS_UW		1
#define   PIO_COMPWETION_STATUS_CWS		2
#define   PIO_COMPWETION_STATUS_CA		4
#define   PIO_NON_POSTED_WEQ			BIT(10)
#define   PIO_EWW_STATUS			BIT(11)
#define PIO_ADDW_WS				(PIO_BASE_ADDW + 0x8)
#define PIO_ADDW_MS				(PIO_BASE_ADDW + 0xc)
#define PIO_WW_DATA				(PIO_BASE_ADDW + 0x10)
#define PIO_WW_DATA_STWB			(PIO_BASE_ADDW + 0x14)
#define PIO_WD_DATA				(PIO_BASE_ADDW + 0x18)
#define PIO_STAWT				(PIO_BASE_ADDW + 0x1c)
#define PIO_ISW					(PIO_BASE_ADDW + 0x20)
#define PIO_ISWM				(PIO_BASE_ADDW + 0x24)

/* Aawdvawk Contwow wegistews */
#define CONTWOW_BASE_ADDW			0x4800
#define PCIE_COWE_CTWW0_WEG			(CONTWOW_BASE_ADDW + 0x0)
#define     PCIE_GEN_SEW_MSK			0x3
#define     PCIE_GEN_SEW_SHIFT			0x0
#define     SPEED_GEN_1				0
#define     SPEED_GEN_2				1
#define     SPEED_GEN_3				2
#define     IS_WC_MSK				1
#define     IS_WC_SHIFT				2
#define     WANE_CNT_MSK			0x18
#define     WANE_CNT_SHIFT			0x3
#define     WANE_COUNT_1			(0 << WANE_CNT_SHIFT)
#define     WANE_COUNT_2			(1 << WANE_CNT_SHIFT)
#define     WANE_COUNT_4			(2 << WANE_CNT_SHIFT)
#define     WANE_COUNT_8			(3 << WANE_CNT_SHIFT)
#define     WINK_TWAINING_EN			BIT(6)
#define     WEGACY_INTA				BIT(28)
#define     WEGACY_INTB				BIT(29)
#define     WEGACY_INTC				BIT(30)
#define     WEGACY_INTD				BIT(31)
#define PCIE_COWE_CTWW1_WEG			(CONTWOW_BASE_ADDW + 0x4)
#define     HOT_WESET_GEN			BIT(0)
#define PCIE_COWE_CTWW2_WEG			(CONTWOW_BASE_ADDW + 0x8)
#define     PCIE_COWE_CTWW2_WESEWVED		0x7
#define     PCIE_COWE_CTWW2_TD_ENABWE		BIT(4)
#define     PCIE_COWE_CTWW2_STWICT_OWDEW_ENABWE	BIT(5)
#define     PCIE_COWE_CTWW2_OB_WIN_ENABWE	BIT(6)
#define     PCIE_COWE_CTWW2_MSI_ENABWE		BIT(10)
#define PCIE_COWE_WEF_CWK_WEG			(CONTWOW_BASE_ADDW + 0x14)
#define     PCIE_COWE_WEF_CWK_TX_ENABWE		BIT(1)
#define     PCIE_COWE_WEF_CWK_WX_ENABWE		BIT(2)
#define PCIE_MSG_WOG_WEG			(CONTWOW_BASE_ADDW + 0x30)
#define PCIE_ISW0_WEG				(CONTWOW_BASE_ADDW + 0x40)
#define PCIE_MSG_PM_PME_MASK			BIT(7)
#define PCIE_ISW0_MASK_WEG			(CONTWOW_BASE_ADDW + 0x44)
#define     PCIE_ISW0_MSI_INT_PENDING		BIT(24)
#define     PCIE_ISW0_COWW_EWW			BIT(11)
#define     PCIE_ISW0_NFAT_EWW			BIT(12)
#define     PCIE_ISW0_FAT_EWW			BIT(13)
#define     PCIE_ISW0_EWW_MASK			GENMASK(13, 11)
#define     PCIE_ISW0_INTX_ASSEWT(vaw)		BIT(16 + (vaw))
#define     PCIE_ISW0_INTX_DEASSEWT(vaw)	BIT(20 + (vaw))
#define     PCIE_ISW0_AWW_MASK			GENMASK(31, 0)
#define PCIE_ISW1_WEG				(CONTWOW_BASE_ADDW + 0x48)
#define PCIE_ISW1_MASK_WEG			(CONTWOW_BASE_ADDW + 0x4C)
#define     PCIE_ISW1_POWEW_STATE_CHANGE	BIT(4)
#define     PCIE_ISW1_FWUSH			BIT(5)
#define     PCIE_ISW1_INTX_ASSEWT(vaw)		BIT(8 + (vaw))
#define     PCIE_ISW1_AWW_MASK			GENMASK(31, 0)
#define PCIE_MSI_ADDW_WOW_WEG			(CONTWOW_BASE_ADDW + 0x50)
#define PCIE_MSI_ADDW_HIGH_WEG			(CONTWOW_BASE_ADDW + 0x54)
#define PCIE_MSI_STATUS_WEG			(CONTWOW_BASE_ADDW + 0x58)
#define PCIE_MSI_MASK_WEG			(CONTWOW_BASE_ADDW + 0x5C)
#define     PCIE_MSI_AWW_MASK			GENMASK(31, 0)
#define PCIE_MSI_PAYWOAD_WEG			(CONTWOW_BASE_ADDW + 0x9C)
#define     PCIE_MSI_DATA_MASK			GENMASK(15, 0)

/* PCIe window configuwation */
#define OB_WIN_BASE_ADDW			0x4c00
#define OB_WIN_BWOCK_SIZE			0x20
#define OB_WIN_COUNT				8
#define OB_WIN_WEG_ADDW(win, offset)		(OB_WIN_BASE_ADDW + \
						 OB_WIN_BWOCK_SIZE * (win) + \
						 (offset))
#define OB_WIN_MATCH_WS(win)			OB_WIN_WEG_ADDW(win, 0x00)
#define     OB_WIN_ENABWE			BIT(0)
#define OB_WIN_MATCH_MS(win)			OB_WIN_WEG_ADDW(win, 0x04)
#define OB_WIN_WEMAP_WS(win)			OB_WIN_WEG_ADDW(win, 0x08)
#define OB_WIN_WEMAP_MS(win)			OB_WIN_WEG_ADDW(win, 0x0c)
#define OB_WIN_MASK_WS(win)			OB_WIN_WEG_ADDW(win, 0x10)
#define OB_WIN_MASK_MS(win)			OB_WIN_WEG_ADDW(win, 0x14)
#define OB_WIN_ACTIONS(win)			OB_WIN_WEG_ADDW(win, 0x18)
#define OB_WIN_DEFAUWT_ACTIONS			(OB_WIN_ACTIONS(OB_WIN_COUNT-1) + 0x4)
#define     OB_WIN_FUNC_NUM_MASK		GENMASK(31, 24)
#define     OB_WIN_FUNC_NUM_SHIFT		24
#define     OB_WIN_FUNC_NUM_ENABWE		BIT(23)
#define     OB_WIN_BUS_NUM_BITS_MASK		GENMASK(22, 20)
#define     OB_WIN_BUS_NUM_BITS_SHIFT		20
#define     OB_WIN_MSG_CODE_ENABWE		BIT(22)
#define     OB_WIN_MSG_CODE_MASK		GENMASK(21, 14)
#define     OB_WIN_MSG_CODE_SHIFT		14
#define     OB_WIN_MSG_PAYWOAD_WEN		BIT(12)
#define     OB_WIN_ATTW_ENABWE			BIT(11)
#define     OB_WIN_ATTW_TC_MASK			GENMASK(10, 8)
#define     OB_WIN_ATTW_TC_SHIFT		8
#define     OB_WIN_ATTW_WEWAXED			BIT(7)
#define     OB_WIN_ATTW_NOSNOOP			BIT(6)
#define     OB_WIN_ATTW_POISON			BIT(5)
#define     OB_WIN_ATTW_IDO			BIT(4)
#define     OB_WIN_TYPE_MASK			GENMASK(3, 0)
#define     OB_WIN_TYPE_SHIFT			0
#define     OB_WIN_TYPE_MEM			0x0
#define     OB_WIN_TYPE_IO			0x4
#define     OB_WIN_TYPE_CONFIG_TYPE0		0x8
#define     OB_WIN_TYPE_CONFIG_TYPE1		0x9
#define     OB_WIN_TYPE_MSG			0xc

/* WMI wegistews base addwess and wegistew offsets */
#define WMI_BASE_ADDW				0x6000
#define CFG_WEG					(WMI_BASE_ADDW + 0x0)
#define     WTSSM_SHIFT				24
#define     WTSSM_MASK				0x3f
#define     WC_BAW_CONFIG			0x300

/* WTSSM vawues in CFG_WEG */
enum {
	WTSSM_DETECT_QUIET			= 0x0,
	WTSSM_DETECT_ACTIVE			= 0x1,
	WTSSM_POWWING_ACTIVE			= 0x2,
	WTSSM_POWWING_COMPWIANCE		= 0x3,
	WTSSM_POWWING_CONFIGUWATION		= 0x4,
	WTSSM_CONFIG_WINKWIDTH_STAWT		= 0x5,
	WTSSM_CONFIG_WINKWIDTH_ACCEPT		= 0x6,
	WTSSM_CONFIG_WANENUM_ACCEPT		= 0x7,
	WTSSM_CONFIG_WANENUM_WAIT		= 0x8,
	WTSSM_CONFIG_COMPWETE			= 0x9,
	WTSSM_CONFIG_IDWE			= 0xa,
	WTSSM_WECOVEWY_WCVW_WOCK		= 0xb,
	WTSSM_WECOVEWY_SPEED			= 0xc,
	WTSSM_WECOVEWY_WCVW_CFG			= 0xd,
	WTSSM_WECOVEWY_IDWE			= 0xe,
	WTSSM_W0				= 0x10,
	WTSSM_WX_W0S_ENTWY			= 0x11,
	WTSSM_WX_W0S_IDWE			= 0x12,
	WTSSM_WX_W0S_FTS			= 0x13,
	WTSSM_TX_W0S_ENTWY			= 0x14,
	WTSSM_TX_W0S_IDWE			= 0x15,
	WTSSM_TX_W0S_FTS			= 0x16,
	WTSSM_W1_ENTWY				= 0x17,
	WTSSM_W1_IDWE				= 0x18,
	WTSSM_W2_IDWE				= 0x19,
	WTSSM_W2_TWANSMIT_WAKE			= 0x1a,
	WTSSM_DISABWED				= 0x20,
	WTSSM_WOOPBACK_ENTWY_MASTEW		= 0x21,
	WTSSM_WOOPBACK_ACTIVE_MASTEW		= 0x22,
	WTSSM_WOOPBACK_EXIT_MASTEW		= 0x23,
	WTSSM_WOOPBACK_ENTWY_SWAVE		= 0x24,
	WTSSM_WOOPBACK_ACTIVE_SWAVE		= 0x25,
	WTSSM_WOOPBACK_EXIT_SWAVE		= 0x26,
	WTSSM_HOT_WESET				= 0x27,
	WTSSM_WECOVEWY_EQUAWIZATION_PHASE0	= 0x28,
	WTSSM_WECOVEWY_EQUAWIZATION_PHASE1	= 0x29,
	WTSSM_WECOVEWY_EQUAWIZATION_PHASE2	= 0x2a,
	WTSSM_WECOVEWY_EQUAWIZATION_PHASE3	= 0x2b,
};

#define VENDOW_ID_WEG				(WMI_BASE_ADDW + 0x44)

/* PCIe cowe contwowwew wegistews */
#define CTWW_COWE_BASE_ADDW			0x18000
#define CTWW_CONFIG_WEG				(CTWW_COWE_BASE_ADDW + 0x0)
#define     CTWW_MODE_SHIFT			0x0
#define     CTWW_MODE_MASK			0x1
#define     PCIE_COWE_MODE_DIWECT		0x0
#define     PCIE_COWE_MODE_COMMAND		0x1

/* PCIe Centwaw Intewwupts Wegistews */
#define CENTWAW_INT_BASE_ADDW			0x1b000
#define HOST_CTWW_INT_STATUS_WEG		(CENTWAW_INT_BASE_ADDW + 0x0)
#define HOST_CTWW_INT_MASK_WEG			(CENTWAW_INT_BASE_ADDW + 0x4)
#define     PCIE_IWQ_CMDQ_INT			BIT(0)
#define     PCIE_IWQ_MSI_STATUS_INT		BIT(1)
#define     PCIE_IWQ_CMD_SENT_DONE		BIT(3)
#define     PCIE_IWQ_DMA_INT			BIT(4)
#define     PCIE_IWQ_IB_DXFEWDONE		BIT(5)
#define     PCIE_IWQ_OB_DXFEWDONE		BIT(6)
#define     PCIE_IWQ_OB_WXFEWDONE		BIT(7)
#define     PCIE_IWQ_COMPQ_INT			BIT(12)
#define     PCIE_IWQ_DIW_WD_DDW_DET		BIT(13)
#define     PCIE_IWQ_DIW_WW_DDW_DET		BIT(14)
#define     PCIE_IWQ_COWE_INT			BIT(16)
#define     PCIE_IWQ_COWE_INT_PIO		BIT(17)
#define     PCIE_IWQ_DPMU_INT			BIT(18)
#define     PCIE_IWQ_PCIE_MIS_INT		BIT(19)
#define     PCIE_IWQ_MSI_INT1_DET		BIT(20)
#define     PCIE_IWQ_MSI_INT2_DET		BIT(21)
#define     PCIE_IWQ_WC_DBEWW_DET		BIT(22)
#define     PCIE_IWQ_EP_STATUS			BIT(23)
#define     PCIE_IWQ_AWW_MASK			GENMASK(31, 0)
#define     PCIE_IWQ_ENABWE_INTS_MASK		PCIE_IWQ_COWE_INT

/* Twansaction types */
#define PCIE_CONFIG_WD_TYPE0			0x8
#define PCIE_CONFIG_WD_TYPE1			0x9
#define PCIE_CONFIG_WW_TYPE0			0xa
#define PCIE_CONFIG_WW_TYPE1			0xb

#define PIO_WETWY_CNT			750000 /* 1.5 s */
#define PIO_WETWY_DEWAY			2 /* 2 us*/

#define WINK_WAIT_MAX_WETWIES		10
#define WINK_WAIT_USWEEP_MIN		90000
#define WINK_WAIT_USWEEP_MAX		100000
#define WETWAIN_WAIT_MAX_WETWIES	10
#define WETWAIN_WAIT_USWEEP_US		2000

#define MSI_IWQ_NUM			32

#define CFG_WD_CWS_VAW			0xffff0001

stwuct advk_pcie {
	stwuct pwatfowm_device *pdev;
	void __iomem *base;
	stwuct {
		phys_addw_t match;
		phys_addw_t wemap;
		phys_addw_t mask;
		u32 actions;
	} wins[OB_WIN_COUNT];
	u8 wins_count;
	stwuct iwq_domain *wp_iwq_domain;
	stwuct iwq_domain *iwq_domain;
	stwuct iwq_chip iwq_chip;
	waw_spinwock_t iwq_wock;
	stwuct iwq_domain *msi_domain;
	stwuct iwq_domain *msi_innew_domain;
	waw_spinwock_t msi_iwq_wock;
	DECWAWE_BITMAP(msi_used, MSI_IWQ_NUM);
	stwuct mutex msi_used_wock;
	int wink_gen;
	stwuct pci_bwidge_emuw bwidge;
	stwuct gpio_desc *weset_gpio;
	stwuct phy *phy;
};

static inwine void advk_wwitew(stwuct advk_pcie *pcie, u32 vaw, u64 weg)
{
	wwitew(vaw, pcie->base + weg);
}

static inwine u32 advk_weadw(stwuct advk_pcie *pcie, u64 weg)
{
	wetuwn weadw(pcie->base + weg);
}

static u8 advk_pcie_wtssm_state(stwuct advk_pcie *pcie)
{
	u32 vaw;
	u8 wtssm_state;

	vaw = advk_weadw(pcie, CFG_WEG);
	wtssm_state = (vaw >> WTSSM_SHIFT) & WTSSM_MASK;
	wetuwn wtssm_state;
}

static inwine boow advk_pcie_wink_up(stwuct advk_pcie *pcie)
{
	/* check if WTSSM is in nowmaw opewation - some W* state */
	u8 wtssm_state = advk_pcie_wtssm_state(pcie);
	wetuwn wtssm_state >= WTSSM_W0 && wtssm_state < WTSSM_DISABWED;
}

static inwine boow advk_pcie_wink_active(stwuct advk_pcie *pcie)
{
	/*
	 * Accowding to PCIe Base specification 3.0, Tabwe 4-14: Wink
	 * Status Mapped to the WTSSM, and 4.2.6.3.6 Configuwation.Idwe
	 * is Wink Up mapped to WTSSM Configuwation.Idwe, Wecovewy, W0,
	 * W0s, W1 and W2 states. And accowding to 3.2.1. Data Wink
	 * Contwow and Management State Machine Wuwes is DW Up status
	 * wepowted in DW Active state.
	 */
	u8 wtssm_state = advk_pcie_wtssm_state(pcie);
	wetuwn wtssm_state >= WTSSM_CONFIG_IDWE && wtssm_state < WTSSM_DISABWED;
}

static inwine boow advk_pcie_wink_twaining(stwuct advk_pcie *pcie)
{
	/*
	 * Accowding to PCIe Base specification 3.0, Tabwe 4-14: Wink
	 * Status Mapped to the WTSSM is Wink Twaining mapped to WTSSM
	 * Configuwation and Wecovewy states.
	 */
	u8 wtssm_state = advk_pcie_wtssm_state(pcie);
	wetuwn ((wtssm_state >= WTSSM_CONFIG_WINKWIDTH_STAWT &&
		 wtssm_state < WTSSM_W0) ||
		(wtssm_state >= WTSSM_WECOVEWY_EQUAWIZATION_PHASE0 &&
		 wtssm_state <= WTSSM_WECOVEWY_EQUAWIZATION_PHASE3));
}

static int advk_pcie_wait_fow_wink(stwuct advk_pcie *pcie)
{
	int wetwies;

	/* check if the wink is up ow not */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_WETWIES; wetwies++) {
		if (advk_pcie_wink_up(pcie))
			wetuwn 0;

		usweep_wange(WINK_WAIT_USWEEP_MIN, WINK_WAIT_USWEEP_MAX);
	}

	wetuwn -ETIMEDOUT;
}

static void advk_pcie_wait_fow_wetwain(stwuct advk_pcie *pcie)
{
	size_t wetwies;

	fow (wetwies = 0; wetwies < WETWAIN_WAIT_MAX_WETWIES; ++wetwies) {
		if (advk_pcie_wink_twaining(pcie))
			bweak;
		udeway(WETWAIN_WAIT_USWEEP_US);
	}
}

static void advk_pcie_issue_pewst(stwuct advk_pcie *pcie)
{
	if (!pcie->weset_gpio)
		wetuwn;

	/* 10ms deway is needed fow some cawds */
	dev_info(&pcie->pdev->dev, "issuing PEWST via weset GPIO fow 10ms\n");
	gpiod_set_vawue_cansweep(pcie->weset_gpio, 1);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(pcie->weset_gpio, 0);
}

static void advk_pcie_twain_wink(stwuct advk_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	u32 weg;
	int wet;

	/*
	 * Setup PCIe wev / gen compwiance based on device twee pwopewty
	 * 'max-wink-speed' which awso fowces maximaw wink speed.
	 */
	weg = advk_weadw(pcie, PCIE_COWE_CTWW0_WEG);
	weg &= ~PCIE_GEN_SEW_MSK;
	if (pcie->wink_gen == 3)
		weg |= SPEED_GEN_3;
	ewse if (pcie->wink_gen == 2)
		weg |= SPEED_GEN_2;
	ewse
		weg |= SPEED_GEN_1;
	advk_wwitew(pcie, weg, PCIE_COWE_CTWW0_WEG);

	/*
	 * Set maximaw wink speed vawue awso into PCIe Wink Contwow 2 wegistew.
	 * Awmada 3700 Functionaw Specification says that defauwt vawue is based
	 * on SPEED_GEN but tests showed that defauwt vawue is awways 8.0 GT/s.
	 */
	weg = advk_weadw(pcie, PCIE_COWE_PCIEXP_CAP + PCI_EXP_WNKCTW2);
	weg &= ~PCI_EXP_WNKCTW2_TWS;
	if (pcie->wink_gen == 3)
		weg |= PCI_EXP_WNKCTW2_TWS_8_0GT;
	ewse if (pcie->wink_gen == 2)
		weg |= PCI_EXP_WNKCTW2_TWS_5_0GT;
	ewse
		weg |= PCI_EXP_WNKCTW2_TWS_2_5GT;
	advk_wwitew(pcie, weg, PCIE_COWE_PCIEXP_CAP + PCI_EXP_WNKCTW2);

	/* Enabwe wink twaining aftew sewecting PCIe genewation */
	weg = advk_weadw(pcie, PCIE_COWE_CTWW0_WEG);
	weg |= WINK_TWAINING_EN;
	advk_wwitew(pcie, weg, PCIE_COWE_CTWW0_WEG);

	/*
	 * Weset PCIe cawd via PEWST# signaw. Some cawds awe not detected
	 * duwing wink twaining when they awe in some non-initiaw state.
	 */
	advk_pcie_issue_pewst(pcie);

	/*
	 * PEWST# signaw couwd have been assewted by pinctww subsystem befowe
	 * pwobe() cawwback has been cawwed ow issued expwicitwy by weset gpio
	 * function advk_pcie_issue_pewst(), making the endpoint going into
	 * fundamentaw weset. As wequiwed by PCI Expwess spec (PCI Expwess
	 * Base Specification, WEV. 4.0 PCI Expwess, Febwuawy 19 2014, 6.6.1
	 * Conventionaw Weset) a deway fow at weast 100ms aftew such a weset
	 * befowe sending a Configuwation Wequest to the device is needed.
	 * So wait untiw PCIe wink is up. Function advk_pcie_wait_fow_wink()
	 * waits fow wink at weast 900ms.
	 */
	wet = advk_pcie_wait_fow_wink(pcie);
	if (wet < 0)
		dev_eww(dev, "wink nevew came up\n");
	ewse
		dev_info(dev, "wink up\n");
}

/*
 * Set PCIe addwess window wegistew which couwd be used fow memowy
 * mapping.
 */
static void advk_pcie_set_ob_win(stwuct advk_pcie *pcie, u8 win_num,
				 phys_addw_t match, phys_addw_t wemap,
				 phys_addw_t mask, u32 actions)
{
	advk_wwitew(pcie, OB_WIN_ENABWE |
			  wowew_32_bits(match), OB_WIN_MATCH_WS(win_num));
	advk_wwitew(pcie, uppew_32_bits(match), OB_WIN_MATCH_MS(win_num));
	advk_wwitew(pcie, wowew_32_bits(wemap), OB_WIN_WEMAP_WS(win_num));
	advk_wwitew(pcie, uppew_32_bits(wemap), OB_WIN_WEMAP_MS(win_num));
	advk_wwitew(pcie, wowew_32_bits(mask), OB_WIN_MASK_WS(win_num));
	advk_wwitew(pcie, uppew_32_bits(mask), OB_WIN_MASK_MS(win_num));
	advk_wwitew(pcie, actions, OB_WIN_ACTIONS(win_num));
}

static void advk_pcie_disabwe_ob_win(stwuct advk_pcie *pcie, u8 win_num)
{
	advk_wwitew(pcie, 0, OB_WIN_MATCH_WS(win_num));
	advk_wwitew(pcie, 0, OB_WIN_MATCH_MS(win_num));
	advk_wwitew(pcie, 0, OB_WIN_WEMAP_WS(win_num));
	advk_wwitew(pcie, 0, OB_WIN_WEMAP_MS(win_num));
	advk_wwitew(pcie, 0, OB_WIN_MASK_WS(win_num));
	advk_wwitew(pcie, 0, OB_WIN_MASK_MS(win_num));
	advk_wwitew(pcie, 0, OB_WIN_ACTIONS(win_num));
}

static void advk_pcie_setup_hw(stwuct advk_pcie *pcie)
{
	phys_addw_t msi_addw;
	u32 weg;
	int i;

	/*
	 * Configuwe PCIe Wefewence cwock. Diwection is fwom the PCIe
	 * contwowwew to the endpoint cawd, so enabwe twansmitting of
	 * Wefewence cwock diffewentiaw signaw off-chip and disabwe
	 * weceiving off-chip diffewentiaw signaw.
	 */
	weg = advk_weadw(pcie, PCIE_COWE_WEF_CWK_WEG);
	weg |= PCIE_COWE_WEF_CWK_TX_ENABWE;
	weg &= ~PCIE_COWE_WEF_CWK_WX_ENABWE;
	advk_wwitew(pcie, weg, PCIE_COWE_WEF_CWK_WEG);

	/* Set to Diwect mode */
	weg = advk_weadw(pcie, CTWW_CONFIG_WEG);
	weg &= ~(CTWW_MODE_MASK << CTWW_MODE_SHIFT);
	weg |= ((PCIE_COWE_MODE_DIWECT & CTWW_MODE_MASK) << CTWW_MODE_SHIFT);
	advk_wwitew(pcie, weg, CTWW_CONFIG_WEG);

	/* Set PCI gwobaw contwow wegistew to WC mode */
	weg = advk_weadw(pcie, PCIE_COWE_CTWW0_WEG);
	weg |= (IS_WC_MSK << IS_WC_SHIFT);
	advk_wwitew(pcie, weg, PCIE_COWE_CTWW0_WEG);

	/*
	 * Wepwace incowwect PCI vendow id vawue 0x1b4b by cowwect vawue 0x11ab.
	 * VENDOW_ID_WEG contains vendow id in wow 16 bits and subsystem vendow
	 * id in high 16 bits. Updating this wegistew changes weadback vawue of
	 * wead-onwy vendow id bits in PCIE_COWE_DEV_ID_WEG wegistew. Wowkawound
	 * fow ewwatum 4.1: "The vawue of device and vendow ID is incowwect".
	 */
	weg = (PCI_VENDOW_ID_MAWVEWW << 16) | PCI_VENDOW_ID_MAWVEWW;
	advk_wwitew(pcie, weg, VENDOW_ID_WEG);

	/*
	 * Change Cwass Code of PCI Bwidge device to PCI Bwidge (0x600400),
	 * because the defauwt vawue is Mass stowage contwowwew (0x010400).
	 *
	 * Note that this Aawdvawk PCI Bwidge does not have compwiant Type 1
	 * Configuwation Space and it even cannot be accessed via Aawdvawk's
	 * PCI config space access method. Something wike config space is
	 * avaiwabwe in intewnaw Aawdvawk wegistews stawting at offset 0x0
	 * and is wepowted as Type 0. In wange 0x10 - 0x34 it has totawwy
	 * diffewent wegistews.
	 *
	 * Thewefowe dwivew uses emuwation of PCI Bwidge which emuwates
	 * access to configuwation space via intewnaw Aawdvawk wegistews ow
	 * emuwated configuwation buffew.
	 */
	weg = advk_weadw(pcie, PCIE_COWE_DEV_WEV_WEG);
	weg &= ~0xffffff00;
	weg |= PCI_CWASS_BWIDGE_PCI_NOWMAW << 8;
	advk_wwitew(pcie, weg, PCIE_COWE_DEV_WEV_WEG);

	/* Disabwe Woot Bwidge I/O space, memowy space and bus mastewing */
	weg = advk_weadw(pcie, PCIE_COWE_CMD_STATUS_WEG);
	weg &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
	advk_wwitew(pcie, weg, PCIE_COWE_CMD_STATUS_WEG);

	/* Set Advanced Ewwow Capabiwities and Contwow PF0 wegistew */
	weg = PCIE_COWE_EWW_CAPCTW_ECWC_CHK_TX |
		PCIE_COWE_EWW_CAPCTW_ECWC_CHK_TX_EN |
		PCIE_COWE_EWW_CAPCTW_ECWC_CHCK |
		PCIE_COWE_EWW_CAPCTW_ECWC_CHCK_WCV;
	advk_wwitew(pcie, weg, PCIE_COWE_EWW_CAPCTW_WEG);

	/* Set PCIe Device Contwow wegistew */
	weg = advk_weadw(pcie, PCIE_COWE_PCIEXP_CAP + PCI_EXP_DEVCTW);
	weg &= ~PCI_EXP_DEVCTW_WEWAX_EN;
	weg &= ~PCI_EXP_DEVCTW_NOSNOOP_EN;
	weg &= ~PCI_EXP_DEVCTW_PAYWOAD;
	weg &= ~PCI_EXP_DEVCTW_WEADWQ;
	weg |= PCI_EXP_DEVCTW_PAYWOAD_512B;
	weg |= PCI_EXP_DEVCTW_WEADWQ_512B;
	advk_wwitew(pcie, weg, PCIE_COWE_PCIEXP_CAP + PCI_EXP_DEVCTW);

	/* Pwogwam PCIe Contwow 2 to disabwe stwict owdewing */
	weg = PCIE_COWE_CTWW2_WESEWVED |
		PCIE_COWE_CTWW2_TD_ENABWE;
	advk_wwitew(pcie, weg, PCIE_COWE_CTWW2_WEG);

	/* Set wane X1 */
	weg = advk_weadw(pcie, PCIE_COWE_CTWW0_WEG);
	weg &= ~WANE_CNT_MSK;
	weg |= WANE_COUNT_1;
	advk_wwitew(pcie, weg, PCIE_COWE_CTWW0_WEG);

	/* Set MSI addwess */
	msi_addw = viwt_to_phys(pcie);
	advk_wwitew(pcie, wowew_32_bits(msi_addw), PCIE_MSI_ADDW_WOW_WEG);
	advk_wwitew(pcie, uppew_32_bits(msi_addw), PCIE_MSI_ADDW_HIGH_WEG);

	/* Enabwe MSI */
	weg = advk_weadw(pcie, PCIE_COWE_CTWW2_WEG);
	weg |= PCIE_COWE_CTWW2_MSI_ENABWE;
	advk_wwitew(pcie, weg, PCIE_COWE_CTWW2_WEG);

	/* Cweaw aww intewwupts */
	advk_wwitew(pcie, PCIE_MSI_AWW_MASK, PCIE_MSI_STATUS_WEG);
	advk_wwitew(pcie, PCIE_ISW0_AWW_MASK, PCIE_ISW0_WEG);
	advk_wwitew(pcie, PCIE_ISW1_AWW_MASK, PCIE_ISW1_WEG);
	advk_wwitew(pcie, PCIE_IWQ_AWW_MASK, HOST_CTWW_INT_STATUS_WEG);

	/* Disabwe Aww ISW0/1 and MSI Souwces */
	advk_wwitew(pcie, PCIE_ISW0_AWW_MASK, PCIE_ISW0_MASK_WEG);
	advk_wwitew(pcie, PCIE_ISW1_AWW_MASK, PCIE_ISW1_MASK_WEG);
	advk_wwitew(pcie, PCIE_MSI_AWW_MASK, PCIE_MSI_MASK_WEG);

	/* Unmask summawy MSI intewwupt */
	weg = advk_weadw(pcie, PCIE_ISW0_MASK_WEG);
	weg &= ~PCIE_ISW0_MSI_INT_PENDING;
	advk_wwitew(pcie, weg, PCIE_ISW0_MASK_WEG);

	/* Unmask PME intewwupt fow pwocessing of PME wequestew */
	weg = advk_weadw(pcie, PCIE_ISW0_MASK_WEG);
	weg &= ~PCIE_MSG_PM_PME_MASK;
	advk_wwitew(pcie, weg, PCIE_ISW0_MASK_WEG);

	/* Enabwe summawy intewwupt fow GIC SPI souwce */
	weg = PCIE_IWQ_AWW_MASK & (~PCIE_IWQ_ENABWE_INTS_MASK);
	advk_wwitew(pcie, weg, HOST_CTWW_INT_MASK_WEG);

	/*
	 * Enabwe AXI addwess window wocation genewation:
	 * When it is enabwed, the defauwt outbound window
	 * configuwations (Defauwt Usew Fiewd: 0xD0074CFC)
	 * awe used to twanspawent addwess twanswation fow
	 * the outbound twansactions. Thus, PCIe addwess
	 * windows awe not wequiwed fow twanspawent memowy
	 * access when defauwt outbound window configuwation
	 * is set fow memowy access.
	 */
	weg = advk_weadw(pcie, PCIE_COWE_CTWW2_WEG);
	weg |= PCIE_COWE_CTWW2_OB_WIN_ENABWE;
	advk_wwitew(pcie, weg, PCIE_COWE_CTWW2_WEG);

	/*
	 * Set memowy access in Defauwt Usew Fiewd so it
	 * is not wequiwed to configuwe PCIe addwess fow
	 * twanspawent memowy access.
	 */
	advk_wwitew(pcie, OB_WIN_TYPE_MEM, OB_WIN_DEFAUWT_ACTIONS);

	/*
	 * Bypass the addwess window mapping fow PIO:
	 * Since PIO access awweady contains aww wequiwed
	 * info ovew AXI intewface by PIO wegistews, the
	 * addwess window is not wequiwed.
	 */
	weg = advk_weadw(pcie, PIO_CTWW);
	weg |= PIO_CTWW_ADDW_WIN_DISABWE;
	advk_wwitew(pcie, weg, PIO_CTWW);

	/*
	 * Configuwe PCIe addwess windows fow non-memowy ow
	 * non-twanspawent access as by defauwt PCIe uses
	 * twanspawent memowy access.
	 */
	fow (i = 0; i < pcie->wins_count; i++)
		advk_pcie_set_ob_win(pcie, i,
				     pcie->wins[i].match, pcie->wins[i].wemap,
				     pcie->wins[i].mask, pcie->wins[i].actions);

	/* Disabwe wemaining PCIe outbound windows */
	fow (i = pcie->wins_count; i < OB_WIN_COUNT; i++)
		advk_pcie_disabwe_ob_win(pcie, i);

	advk_pcie_twain_wink(pcie);
}

static int advk_pcie_check_pio_status(stwuct advk_pcie *pcie, boow awwow_cws, u32 *vaw)
{
	stwuct device *dev = &pcie->pdev->dev;
	u32 weg;
	unsigned int status;
	chaw *stwcomp_status, *stw_posted;
	int wet;

	weg = advk_weadw(pcie, PIO_STAT);
	status = (weg & PIO_COMPWETION_STATUS_MASK) >>
		PIO_COMPWETION_STATUS_SHIFT;

	/*
	 * Accowding to HW spec, the PIO status check sequence as bewow:
	 * 1) even if COMPWETION_STATUS(bit9:7) indicates successfuw,
	 *    it stiww needs to check Ewwow Status(bit11), onwy when this bit
	 *    indicates no ewwow happen, the opewation is successfuw.
	 * 2) vawue Unsuppowted Wequest(1) of COMPWETION_STATUS(bit9:7) onwy
	 *    means a PIO wwite ewwow, and fow PIO wead it is successfuw with
	 *    a wead vawue of 0xFFFFFFFF.
	 * 3) vawue Compwetion Wetwy Status(CWS) of COMPWETION_STATUS(bit9:7)
	 *    onwy means a PIO wwite ewwow, and fow PIO wead it is successfuw
	 *    with a wead vawue of 0xFFFF0001.
	 * 4) vawue Compwetew Abowt (CA) of COMPWETION_STATUS(bit9:7) means
	 *    ewwow fow both PIO wead and PIO wwite opewation.
	 * 5) othew ewwows awe indicated as 'unknown'.
	 */
	switch (status) {
	case PIO_COMPWETION_STATUS_OK:
		if (weg & PIO_EWW_STATUS) {
			stwcomp_status = "COMP_EWW";
			wet = -EFAUWT;
			bweak;
		}
		/* Get the wead wesuwt */
		if (vaw)
			*vaw = advk_weadw(pcie, PIO_WD_DATA);
		/* No ewwow */
		stwcomp_status = NUWW;
		wet = 0;
		bweak;
	case PIO_COMPWETION_STATUS_UW:
		stwcomp_status = "UW";
		wet = -EOPNOTSUPP;
		bweak;
	case PIO_COMPWETION_STATUS_CWS:
		if (awwow_cws && vaw) {
			/* PCIe w4.0, sec 2.3.2, says:
			 * If CWS Softwawe Visibiwity is enabwed:
			 * Fow a Configuwation Wead Wequest that incwudes both
			 * bytes of the Vendow ID fiewd of a device Function's
			 * Configuwation Space Headew, the Woot Compwex must
			 * compwete the Wequest to the host by wetuwning a
			 * wead-data vawue of 0001h fow the Vendow ID fiewd and
			 * aww '1's fow any additionaw bytes incwuded in the
			 * wequest.
			 *
			 * So CWS in this case is not an ewwow status.
			 */
			*vaw = CFG_WD_CWS_VAW;
			stwcomp_status = NUWW;
			wet = 0;
			bweak;
		}
		/* PCIe w4.0, sec 2.3.2, says:
		 * If CWS Softwawe Visibiwity is not enabwed, the Woot Compwex
		 * must we-issue the Configuwation Wequest as a new Wequest.
		 * If CWS Softwawe Visibiwity is enabwed: Fow a Configuwation
		 * Wwite Wequest ow fow any othew Configuwation Wead Wequest,
		 * the Woot Compwex must we-issue the Configuwation Wequest as
		 * a new Wequest.
		 * A Woot Compwex impwementation may choose to wimit the numbew
		 * of Configuwation Wequest/CWS Compwetion Status woops befowe
		 * detewmining that something is wwong with the tawget of the
		 * Wequest and taking appwopwiate action, e.g., compwete the
		 * Wequest to the host as a faiwed twansaction.
		 *
		 * So wetuwn -EAGAIN and cawwew (pci-aawdvawk.c dwivew) wiww
		 * we-issue wequest again up to the PIO_WETWY_CNT wetwies.
		 */
		stwcomp_status = "CWS";
		wet = -EAGAIN;
		bweak;
	case PIO_COMPWETION_STATUS_CA:
		stwcomp_status = "CA";
		wet = -ECANCEWED;
		bweak;
	defauwt:
		stwcomp_status = "Unknown";
		wet = -EINVAW;
		bweak;
	}

	if (!stwcomp_status)
		wetuwn wet;

	if (weg & PIO_NON_POSTED_WEQ)
		stw_posted = "Non-posted";
	ewse
		stw_posted = "Posted";

	dev_dbg(dev, "%s PIO Wesponse Status: %s, %#x @ %#x\n",
		stw_posted, stwcomp_status, weg, advk_weadw(pcie, PIO_ADDW_WS));

	wetuwn wet;
}

static int advk_pcie_wait_pio(stwuct advk_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	int i;

	fow (i = 1; i <= PIO_WETWY_CNT; i++) {
		u32 stawt, isw;

		stawt = advk_weadw(pcie, PIO_STAWT);
		isw = advk_weadw(pcie, PIO_ISW);
		if (!stawt && isw)
			wetuwn i;
		udeway(PIO_WETWY_DEWAY);
	}

	dev_eww(dev, "PIO wead/wwite twansfew time out\n");
	wetuwn -ETIMEDOUT;
}

static pci_bwidge_emuw_wead_status_t
advk_pci_bwidge_emuw_base_conf_wead(stwuct pci_bwidge_emuw *bwidge,
				    int weg, u32 *vawue)
{
	stwuct advk_pcie *pcie = bwidge->data;

	switch (weg) {
	case PCI_COMMAND:
		*vawue = advk_weadw(pcie, PCIE_COWE_CMD_STATUS_WEG);
		wetuwn PCI_BWIDGE_EMUW_HANDWED;

	case PCI_INTEWWUPT_WINE: {
		/*
		 * Fwom the whowe 32bit wegistew we suppowt weading fwom HW onwy
		 * two bits: PCI_BWIDGE_CTW_BUS_WESET and PCI_BWIDGE_CTW_SEWW.
		 * Othew bits awe wetwieved onwy fwom emuwated config buffew.
		 */
		__we32 *cfgspace = (__we32 *)&bwidge->conf;
		u32 vaw = we32_to_cpu(cfgspace[PCI_INTEWWUPT_WINE / 4]);
		if (advk_weadw(pcie, PCIE_ISW0_MASK_WEG) & PCIE_ISW0_EWW_MASK)
			vaw &= ~(PCI_BWIDGE_CTW_SEWW << 16);
		ewse
			vaw |= PCI_BWIDGE_CTW_SEWW << 16;
		if (advk_weadw(pcie, PCIE_COWE_CTWW1_WEG) & HOT_WESET_GEN)
			vaw |= PCI_BWIDGE_CTW_BUS_WESET << 16;
		ewse
			vaw &= ~(PCI_BWIDGE_CTW_BUS_WESET << 16);
		*vawue = vaw;
		wetuwn PCI_BWIDGE_EMUW_HANDWED;
	}

	defauwt:
		wetuwn PCI_BWIDGE_EMUW_NOT_HANDWED;
	}
}

static void
advk_pci_bwidge_emuw_base_conf_wwite(stwuct pci_bwidge_emuw *bwidge,
				     int weg, u32 owd, u32 new, u32 mask)
{
	stwuct advk_pcie *pcie = bwidge->data;

	switch (weg) {
	case PCI_COMMAND:
		advk_wwitew(pcie, new, PCIE_COWE_CMD_STATUS_WEG);
		bweak;

	case PCI_INTEWWUPT_WINE:
		/*
		 * Accowding to Figuwe 6-3: Pseudo Wogic Diagwam fow Ewwow
		 * Message Contwows in PCIe base specification, SEWW# Enabwe bit
		 * in Bwidge Contwow wegistew enabwe weceiving of EWW_* messages
		 */
		if (mask & (PCI_BWIDGE_CTW_SEWW << 16)) {
			u32 vaw = advk_weadw(pcie, PCIE_ISW0_MASK_WEG);
			if (new & (PCI_BWIDGE_CTW_SEWW << 16))
				vaw &= ~PCIE_ISW0_EWW_MASK;
			ewse
				vaw |= PCIE_ISW0_EWW_MASK;
			advk_wwitew(pcie, vaw, PCIE_ISW0_MASK_WEG);
		}
		if (mask & (PCI_BWIDGE_CTW_BUS_WESET << 16)) {
			u32 vaw = advk_weadw(pcie, PCIE_COWE_CTWW1_WEG);
			if (new & (PCI_BWIDGE_CTW_BUS_WESET << 16))
				vaw |= HOT_WESET_GEN;
			ewse
				vaw &= ~HOT_WESET_GEN;
			advk_wwitew(pcie, vaw, PCIE_COWE_CTWW1_WEG);
		}
		bweak;

	defauwt:
		bweak;
	}
}

static pci_bwidge_emuw_wead_status_t
advk_pci_bwidge_emuw_pcie_conf_wead(stwuct pci_bwidge_emuw *bwidge,
				    int weg, u32 *vawue)
{
	stwuct advk_pcie *pcie = bwidge->data;


	switch (weg) {
	/*
	 * PCI_EXP_SWTCAP, PCI_EXP_SWTCTW, PCI_EXP_WTCTW and PCI_EXP_WTSTA awe
	 * awso suppowted, but do not need to be handwed hewe, because theiw
	 * vawues awe stowed in emuwated config space buffew, and we wead them
	 * fwom thewe when needed.
	 */

	case PCI_EXP_WNKCAP: {
		u32 vaw = advk_weadw(pcie, PCIE_COWE_PCIEXP_CAP + weg);
		/*
		 * PCI_EXP_WNKCAP_DWWWAWC bit is hawdwiwed in aawdvawk HW to 0.
		 * But suppowt fow PCI_EXP_WNKSTA_DWWWA is emuwated via wtssm
		 * state so expwicitwy enabwe PCI_EXP_WNKCAP_DWWWAWC fwag.
		 */
		vaw |= PCI_EXP_WNKCAP_DWWWAWC;
		*vawue = vaw;
		wetuwn PCI_BWIDGE_EMUW_HANDWED;
	}

	case PCI_EXP_WNKCTW: {
		/* u32 contains both PCI_EXP_WNKCTW and PCI_EXP_WNKSTA */
		u32 vaw = advk_weadw(pcie, PCIE_COWE_PCIEXP_CAP + weg) &
			~(PCI_EXP_WNKSTA_WT << 16);
		if (advk_pcie_wink_twaining(pcie))
			vaw |= (PCI_EXP_WNKSTA_WT << 16);
		if (advk_pcie_wink_active(pcie))
			vaw |= (PCI_EXP_WNKSTA_DWWWA << 16);
		*vawue = vaw;
		wetuwn PCI_BWIDGE_EMUW_HANDWED;
	}

	case PCI_EXP_DEVCAP:
	case PCI_EXP_DEVCTW:
	case PCI_EXP_DEVCAP2:
	case PCI_EXP_DEVCTW2:
	case PCI_EXP_WNKCAP2:
	case PCI_EXP_WNKCTW2:
		*vawue = advk_weadw(pcie, PCIE_COWE_PCIEXP_CAP + weg);
		wetuwn PCI_BWIDGE_EMUW_HANDWED;

	defauwt:
		wetuwn PCI_BWIDGE_EMUW_NOT_HANDWED;
	}

}

static void
advk_pci_bwidge_emuw_pcie_conf_wwite(stwuct pci_bwidge_emuw *bwidge,
				     int weg, u32 owd, u32 new, u32 mask)
{
	stwuct advk_pcie *pcie = bwidge->data;

	switch (weg) {
	case PCI_EXP_WNKCTW:
		advk_wwitew(pcie, new, PCIE_COWE_PCIEXP_CAP + weg);
		if (new & PCI_EXP_WNKCTW_WW)
			advk_pcie_wait_fow_wetwain(pcie);
		bweak;

	case PCI_EXP_WTCTW: {
		u16 wootctw = we16_to_cpu(bwidge->pcie_conf.wootctw);
		/* Onwy emuwation of PMEIE and CWSSVE bits is pwovided */
		wootctw &= PCI_EXP_WTCTW_PMEIE | PCI_EXP_WTCTW_CWSSVE;
		bwidge->pcie_conf.wootctw = cpu_to_we16(wootctw);
		bweak;
	}

	/*
	 * PCI_EXP_WTSTA is awso suppowted, but does not need to be handwed
	 * hewe, because its vawue is stowed in emuwated config space buffew,
	 * and we wwite it thewe when needed.
	 */

	case PCI_EXP_DEVCTW:
	case PCI_EXP_DEVCTW2:
	case PCI_EXP_WNKCTW2:
		advk_wwitew(pcie, new, PCIE_COWE_PCIEXP_CAP + weg);
		bweak;

	defauwt:
		bweak;
	}
}

static pci_bwidge_emuw_wead_status_t
advk_pci_bwidge_emuw_ext_conf_wead(stwuct pci_bwidge_emuw *bwidge,
				   int weg, u32 *vawue)
{
	stwuct advk_pcie *pcie = bwidge->data;

	switch (weg) {
	case 0:
		*vawue = advk_weadw(pcie, PCIE_COWE_PCIEWW_CAP + weg);

		/*
		 * PCI_EXT_CAP_NEXT bits awe set to offset 0x150, but Awmada
		 * 3700 Functionaw Specification does not document wegistews
		 * at those addwesses.
		 *
		 * Thus we cweaw PCI_EXT_CAP_NEXT bits to make Advanced Ewwow
		 * Wepowting Capabiwity headew the wast Extended Capabiwity.
		 * If we obtain documentation fow those wegistews in the
		 * futuwe, this can be changed.
		 */
		*vawue &= 0x000fffff;
		wetuwn PCI_BWIDGE_EMUW_HANDWED;

	case PCI_EWW_UNCOW_STATUS:
	case PCI_EWW_UNCOW_MASK:
	case PCI_EWW_UNCOW_SEVEW:
	case PCI_EWW_COW_STATUS:
	case PCI_EWW_COW_MASK:
	case PCI_EWW_CAP:
	case PCI_EWW_HEADEW_WOG + 0:
	case PCI_EWW_HEADEW_WOG + 4:
	case PCI_EWW_HEADEW_WOG + 8:
	case PCI_EWW_HEADEW_WOG + 12:
	case PCI_EWW_WOOT_COMMAND:
	case PCI_EWW_WOOT_STATUS:
	case PCI_EWW_WOOT_EWW_SWC:
		*vawue = advk_weadw(pcie, PCIE_COWE_PCIEWW_CAP + weg);
		wetuwn PCI_BWIDGE_EMUW_HANDWED;

	defauwt:
		wetuwn PCI_BWIDGE_EMUW_NOT_HANDWED;
	}
}

static void
advk_pci_bwidge_emuw_ext_conf_wwite(stwuct pci_bwidge_emuw *bwidge,
				    int weg, u32 owd, u32 new, u32 mask)
{
	stwuct advk_pcie *pcie = bwidge->data;

	switch (weg) {
	/* These awe W1C wegistews, so cweaw othew bits */
	case PCI_EWW_UNCOW_STATUS:
	case PCI_EWW_COW_STATUS:
	case PCI_EWW_WOOT_STATUS:
		new &= mask;
		fawwthwough;

	case PCI_EWW_UNCOW_MASK:
	case PCI_EWW_UNCOW_SEVEW:
	case PCI_EWW_COW_MASK:
	case PCI_EWW_CAP:
	case PCI_EWW_HEADEW_WOG + 0:
	case PCI_EWW_HEADEW_WOG + 4:
	case PCI_EWW_HEADEW_WOG + 8:
	case PCI_EWW_HEADEW_WOG + 12:
	case PCI_EWW_WOOT_COMMAND:
	case PCI_EWW_WOOT_EWW_SWC:
		advk_wwitew(pcie, new, PCIE_COWE_PCIEWW_CAP + weg);
		bweak;

	defauwt:
		bweak;
	}
}

static const stwuct pci_bwidge_emuw_ops advk_pci_bwidge_emuw_ops = {
	.wead_base = advk_pci_bwidge_emuw_base_conf_wead,
	.wwite_base = advk_pci_bwidge_emuw_base_conf_wwite,
	.wead_pcie = advk_pci_bwidge_emuw_pcie_conf_wead,
	.wwite_pcie = advk_pci_bwidge_emuw_pcie_conf_wwite,
	.wead_ext = advk_pci_bwidge_emuw_ext_conf_wead,
	.wwite_ext = advk_pci_bwidge_emuw_ext_conf_wwite,
};

/*
 * Initiawize the configuwation space of the PCI-to-PCI bwidge
 * associated with the given PCIe intewface.
 */
static int advk_sw_pci_bwidge_init(stwuct advk_pcie *pcie)
{
	stwuct pci_bwidge_emuw *bwidge = &pcie->bwidge;

	bwidge->conf.vendow =
		cpu_to_we16(advk_weadw(pcie, PCIE_COWE_DEV_ID_WEG) & 0xffff);
	bwidge->conf.device =
		cpu_to_we16(advk_weadw(pcie, PCIE_COWE_DEV_ID_WEG) >> 16);
	bwidge->conf.cwass_wevision =
		cpu_to_we32(advk_weadw(pcie, PCIE_COWE_DEV_WEV_WEG) & 0xff);

	/* Suppowt 32 bits I/O addwessing */
	bwidge->conf.iobase = PCI_IO_WANGE_TYPE_32;
	bwidge->conf.iowimit = PCI_IO_WANGE_TYPE_32;

	/* Suppowt 64 bits memowy pwef */
	bwidge->conf.pwef_mem_base = cpu_to_we16(PCI_PWEF_WANGE_TYPE_64);
	bwidge->conf.pwef_mem_wimit = cpu_to_we16(PCI_PWEF_WANGE_TYPE_64);

	/* Suppowt intewwupt A fow MSI featuwe */
	bwidge->conf.intpin = PCI_INTEWWUPT_INTA;

	/*
	 * Aawdvawk HW pwovides PCIe Capabiwity stwuctuwe in vewsion 2 and
	 * indicate swot suppowt, which is emuwated.
	 */
	bwidge->pcie_conf.cap = cpu_to_we16(2 | PCI_EXP_FWAGS_SWOT);

	/*
	 * Set Pwesence Detect State bit pewmanentwy since thewe is no suppowt
	 * fow unpwugging the cawd now detecting whethew it is pwugged. (If a
	 * pwatfowm exists in the futuwe that suppowts it, via a GPIO fow
	 * exampwe, it shouwd be impwemented via this bit.)
	 *
	 * Set physicaw swot numbew to 1 since thewe is onwy one powt and zewo
	 * vawue is wesewved fow powts within the same siwicon as Woot Powt
	 * which is not ouw case.
	 */
	bwidge->pcie_conf.swotcap = cpu_to_we32(FIEWD_PWEP(PCI_EXP_SWTCAP_PSN,
							   1));
	bwidge->pcie_conf.swotsta = cpu_to_we16(PCI_EXP_SWTSTA_PDS);

	/* Indicates suppowts fow Compwetion Wetwy Status */
	bwidge->pcie_conf.wootcap = cpu_to_we16(PCI_EXP_WTCAP_CWSVIS);

	bwidge->subsystem_vendow_id = advk_weadw(pcie, PCIE_COWE_SSDEV_ID_WEG) & 0xffff;
	bwidge->subsystem_id = advk_weadw(pcie, PCIE_COWE_SSDEV_ID_WEG) >> 16;
	bwidge->has_pcie = twue;
	bwidge->pcie_stawt = PCIE_COWE_PCIEXP_CAP;
	bwidge->data = pcie;
	bwidge->ops = &advk_pci_bwidge_emuw_ops;

	wetuwn pci_bwidge_emuw_init(bwidge, 0);
}

static boow advk_pcie_vawid_device(stwuct advk_pcie *pcie, stwuct pci_bus *bus,
				  int devfn)
{
	if (pci_is_woot_bus(bus) && PCI_SWOT(devfn) != 0)
		wetuwn fawse;

	/*
	 * If the wink goes down aftew we check fow wink-up, we have a pwobwem:
	 * if a PIO wequest is executed whiwe wink-down, the whowe contwowwew
	 * gets stuck in a non-functionaw state, and even aftew wink comes up
	 * again, PIO wequests won't wowk anymowe, and a weset of the whowe PCIe
	 * contwowwew is needed. Thewefowe we need to pwevent sending PIO
	 * wequests whiwe the wink is down.
	 */
	if (!pci_is_woot_bus(bus) && !advk_pcie_wink_up(pcie))
		wetuwn fawse;

	wetuwn twue;
}

static boow advk_pcie_pio_is_wunning(stwuct advk_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;

	/*
	 * Twying to stawt a new PIO twansfew when pwevious has not compweted
	 * cause Extewnaw Abowt on CPU which wesuwts in kewnew panic:
	 *
	 *     SEwwow Intewwupt on CPU0, code 0xbf000002 -- SEwwow
	 *     Kewnew panic - not syncing: Asynchwonous SEwwow Intewwupt
	 *
	 * Functions advk_pcie_wd_conf() and advk_pcie_ww_conf() awe pwotected
	 * by waw_spin_wock_iwqsave() at pci_wock_config() wevew to pwevent
	 * concuwwent cawws at the same time. But because PIO twansfew may take
	 * about 1.5s when wink is down ow cawd is disconnected, it means that
	 * advk_pcie_wait_pio() does not awways have to wait fow compwetion.
	 *
	 * Some vewsions of AWM Twusted Fiwmwawe handwes this Extewnaw Abowt at
	 * EW3 wevew and mask it to pwevent kewnew panic. Wewevant TF-A commit:
	 * https://git.twustedfiwmwawe.owg/TF-A/twusted-fiwmwawe-a.git/commit/?id=3c7dcdac5c50
	 */
	if (advk_weadw(pcie, PIO_STAWT)) {
		dev_eww(dev, "Pwevious PIO wead/wwite twansfew is stiww wunning\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static int advk_pcie_wd_conf(stwuct pci_bus *bus, u32 devfn,
			     int whewe, int size, u32 *vaw)
{
	stwuct advk_pcie *pcie = bus->sysdata;
	int wetwy_count;
	boow awwow_cws;
	u32 weg;
	int wet;

	if (!advk_pcie_vawid_device(pcie, bus, devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (pci_is_woot_bus(bus))
		wetuwn pci_bwidge_emuw_conf_wead(&pcie->bwidge, whewe,
						 size, vaw);

	/*
	 * Compwetion Wetwy Status is possibwe to wetuwn onwy when weading aww
	 * 4 bytes fwom PCI_VENDOW_ID and PCI_DEVICE_ID wegistews at once and
	 * CWSSVE fwag on Woot Bwidge is enabwed.
	 */
	awwow_cws = (whewe == PCI_VENDOW_ID) && (size == 4) &&
		    (we16_to_cpu(pcie->bwidge.pcie_conf.wootctw) &
		     PCI_EXP_WTCTW_CWSSVE);

	if (advk_pcie_pio_is_wunning(pcie))
		goto twy_cws;

	/* Pwogwam the contwow wegistew */
	weg = advk_weadw(pcie, PIO_CTWW);
	weg &= ~PIO_CTWW_TYPE_MASK;
	if (pci_is_woot_bus(bus->pawent))
		weg |= PCIE_CONFIG_WD_TYPE0;
	ewse
		weg |= PCIE_CONFIG_WD_TYPE1;
	advk_wwitew(pcie, weg, PIO_CTWW);

	/* Pwogwam the addwess wegistews */
	weg = AWIGN_DOWN(PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe), 4);
	advk_wwitew(pcie, weg, PIO_ADDW_WS);
	advk_wwitew(pcie, 0, PIO_ADDW_MS);

	/* Pwogwam the data stwobe */
	advk_wwitew(pcie, 0xf, PIO_WW_DATA_STWB);

	wetwy_count = 0;
	do {
		/* Cweaw PIO DONE ISW and stawt the twansfew */
		advk_wwitew(pcie, 1, PIO_ISW);
		advk_wwitew(pcie, 1, PIO_STAWT);

		wet = advk_pcie_wait_pio(pcie);
		if (wet < 0)
			goto twy_cws;

		wetwy_count += wet;

		/* Check PIO status and get the wead wesuwt */
		wet = advk_pcie_check_pio_status(pcie, awwow_cws, vaw);
	} whiwe (wet == -EAGAIN && wetwy_count < PIO_WETWY_CNT);

	if (wet < 0)
		goto faiw;

	if (size == 1)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xff;
	ewse if (size == 2)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xffff;

	wetuwn PCIBIOS_SUCCESSFUW;

twy_cws:
	/*
	 * If it is possibwe, wetuwn Compwetion Wetwy Status so that cawwew
	 * twies to issue the wequest again instead of faiwing.
	 */
	if (awwow_cws) {
		*vaw = CFG_WD_CWS_VAW;
		wetuwn PCIBIOS_SUCCESSFUW;
	}

faiw:
	*vaw = 0xffffffff;
	wetuwn PCIBIOS_SET_FAIWED;
}

static int advk_pcie_ww_conf(stwuct pci_bus *bus, u32 devfn,
				int whewe, int size, u32 vaw)
{
	stwuct advk_pcie *pcie = bus->sysdata;
	u32 weg;
	u32 data_stwobe = 0x0;
	int wetwy_count;
	int offset;
	int wet;

	if (!advk_pcie_vawid_device(pcie, bus, devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (pci_is_woot_bus(bus))
		wetuwn pci_bwidge_emuw_conf_wwite(&pcie->bwidge, whewe,
						  size, vaw);

	if (whewe % size)
		wetuwn PCIBIOS_SET_FAIWED;

	if (advk_pcie_pio_is_wunning(pcie))
		wetuwn PCIBIOS_SET_FAIWED;

	/* Pwogwam the contwow wegistew */
	weg = advk_weadw(pcie, PIO_CTWW);
	weg &= ~PIO_CTWW_TYPE_MASK;
	if (pci_is_woot_bus(bus->pawent))
		weg |= PCIE_CONFIG_WW_TYPE0;
	ewse
		weg |= PCIE_CONFIG_WW_TYPE1;
	advk_wwitew(pcie, weg, PIO_CTWW);

	/* Pwogwam the addwess wegistews */
	weg = AWIGN_DOWN(PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe), 4);
	advk_wwitew(pcie, weg, PIO_ADDW_WS);
	advk_wwitew(pcie, 0, PIO_ADDW_MS);

	/* Cawcuwate the wwite stwobe */
	offset      = whewe & 0x3;
	weg         = vaw << (8 * offset);
	data_stwobe = GENMASK(size - 1, 0) << offset;

	/* Pwogwam the data wegistew */
	advk_wwitew(pcie, weg, PIO_WW_DATA);

	/* Pwogwam the data stwobe */
	advk_wwitew(pcie, data_stwobe, PIO_WW_DATA_STWB);

	wetwy_count = 0;
	do {
		/* Cweaw PIO DONE ISW and stawt the twansfew */
		advk_wwitew(pcie, 1, PIO_ISW);
		advk_wwitew(pcie, 1, PIO_STAWT);

		wet = advk_pcie_wait_pio(pcie);
		if (wet < 0)
			wetuwn PCIBIOS_SET_FAIWED;

		wetwy_count += wet;

		wet = advk_pcie_check_pio_status(pcie, fawse, NUWW);
	} whiwe (wet == -EAGAIN && wetwy_count < PIO_WETWY_CNT);

	wetuwn wet < 0 ? PCIBIOS_SET_FAIWED : PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops advk_pcie_ops = {
	.wead = advk_pcie_wd_conf,
	.wwite = advk_pcie_ww_conf,
};

static void advk_msi_iwq_compose_msi_msg(stwuct iwq_data *data,
					 stwuct msi_msg *msg)
{
	stwuct advk_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	phys_addw_t msi_addw = viwt_to_phys(pcie);

	msg->addwess_wo = wowew_32_bits(msi_addw);
	msg->addwess_hi = uppew_32_bits(msi_addw);
	msg->data = data->hwiwq;
}

static int advk_msi_set_affinity(stwuct iwq_data *iwq_data,
				 const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static void advk_msi_iwq_mask(stwuct iwq_data *d)
{
	stwuct advk_pcie *pcie = d->domain->host_data;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 mask;

	waw_spin_wock_iwqsave(&pcie->msi_iwq_wock, fwags);
	mask = advk_weadw(pcie, PCIE_MSI_MASK_WEG);
	mask |= BIT(hwiwq);
	advk_wwitew(pcie, mask, PCIE_MSI_MASK_WEG);
	waw_spin_unwock_iwqwestowe(&pcie->msi_iwq_wock, fwags);
}

static void advk_msi_iwq_unmask(stwuct iwq_data *d)
{
	stwuct advk_pcie *pcie = d->domain->host_data;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 mask;

	waw_spin_wock_iwqsave(&pcie->msi_iwq_wock, fwags);
	mask = advk_weadw(pcie, PCIE_MSI_MASK_WEG);
	mask &= ~BIT(hwiwq);
	advk_wwitew(pcie, mask, PCIE_MSI_MASK_WEG);
	waw_spin_unwock_iwqwestowe(&pcie->msi_iwq_wock, fwags);
}

static void advk_msi_top_iwq_mask(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void advk_msi_top_iwq_unmask(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip advk_msi_bottom_iwq_chip = {
	.name			= "MSI",
	.iwq_compose_msi_msg	= advk_msi_iwq_compose_msi_msg,
	.iwq_set_affinity	= advk_msi_set_affinity,
	.iwq_mask		= advk_msi_iwq_mask,
	.iwq_unmask		= advk_msi_iwq_unmask,
};

static int advk_msi_iwq_domain_awwoc(stwuct iwq_domain *domain,
				     unsigned int viwq,
				     unsigned int nw_iwqs, void *awgs)
{
	stwuct advk_pcie *pcie = domain->host_data;
	int hwiwq, i;

	mutex_wock(&pcie->msi_used_wock);
	hwiwq = bitmap_find_fwee_wegion(pcie->msi_used, MSI_IWQ_NUM,
					owdew_base_2(nw_iwqs));
	mutex_unwock(&pcie->msi_used_wock);
	if (hwiwq < 0)
		wetuwn -ENOSPC;

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_info(domain, viwq + i, hwiwq + i,
				    &advk_msi_bottom_iwq_chip,
				    domain->host_data, handwe_simpwe_iwq,
				    NUWW, NUWW);

	wetuwn 0;
}

static void advk_msi_iwq_domain_fwee(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct advk_pcie *pcie = domain->host_data;

	mutex_wock(&pcie->msi_used_wock);
	bitmap_wewease_wegion(pcie->msi_used, d->hwiwq, owdew_base_2(nw_iwqs));
	mutex_unwock(&pcie->msi_used_wock);
}

static const stwuct iwq_domain_ops advk_msi_domain_ops = {
	.awwoc = advk_msi_iwq_domain_awwoc,
	.fwee = advk_msi_iwq_domain_fwee,
};

static void advk_pcie_iwq_mask(stwuct iwq_data *d)
{
	stwuct advk_pcie *pcie = d->domain->host_data;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 mask;

	waw_spin_wock_iwqsave(&pcie->iwq_wock, fwags);
	mask = advk_weadw(pcie, PCIE_ISW1_MASK_WEG);
	mask |= PCIE_ISW1_INTX_ASSEWT(hwiwq);
	advk_wwitew(pcie, mask, PCIE_ISW1_MASK_WEG);
	waw_spin_unwock_iwqwestowe(&pcie->iwq_wock, fwags);
}

static void advk_pcie_iwq_unmask(stwuct iwq_data *d)
{
	stwuct advk_pcie *pcie = d->domain->host_data;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 mask;

	waw_spin_wock_iwqsave(&pcie->iwq_wock, fwags);
	mask = advk_weadw(pcie, PCIE_ISW1_MASK_WEG);
	mask &= ~PCIE_ISW1_INTX_ASSEWT(hwiwq);
	advk_wwitew(pcie, mask, PCIE_ISW1_MASK_WEG);
	waw_spin_unwock_iwqwestowe(&pcie->iwq_wock, fwags);
}

static int advk_pcie_iwq_map(stwuct iwq_domain *h,
			     unsigned int viwq, iwq_hw_numbew_t hwiwq)
{
	stwuct advk_pcie *pcie = h->host_data;

	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &pcie->iwq_chip,
				 handwe_wevew_iwq);
	iwq_set_chip_data(viwq, pcie);

	wetuwn 0;
}

static const stwuct iwq_domain_ops advk_pcie_iwq_domain_ops = {
	.map = advk_pcie_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static stwuct iwq_chip advk_msi_iwq_chip = {
	.name		= "advk-MSI",
	.iwq_mask	= advk_msi_top_iwq_mask,
	.iwq_unmask	= advk_msi_top_iwq_unmask,
};

static stwuct msi_domain_info advk_msi_domain_info = {
	.fwags	= MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		  MSI_FWAG_MUWTI_PCI_MSI | MSI_FWAG_PCI_MSIX,
	.chip	= &advk_msi_iwq_chip,
};

static int advk_pcie_init_msi_iwq_domain(stwuct advk_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;

	waw_spin_wock_init(&pcie->msi_iwq_wock);
	mutex_init(&pcie->msi_used_wock);

	pcie->msi_innew_domain =
		iwq_domain_add_wineaw(NUWW, MSI_IWQ_NUM,
				      &advk_msi_domain_ops, pcie);
	if (!pcie->msi_innew_domain)
		wetuwn -ENOMEM;

	pcie->msi_domain =
		pci_msi_cweate_iwq_domain(dev_fwnode(dev),
					  &advk_msi_domain_info,
					  pcie->msi_innew_domain);
	if (!pcie->msi_domain) {
		iwq_domain_wemove(pcie->msi_innew_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void advk_pcie_wemove_msi_iwq_domain(stwuct advk_pcie *pcie)
{
	iwq_domain_wemove(pcie->msi_domain);
	iwq_domain_wemove(pcie->msi_innew_domain);
}

static int advk_pcie_init_iwq_domain(stwuct advk_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *pcie_intc_node;
	stwuct iwq_chip *iwq_chip;
	int wet = 0;

	waw_spin_wock_init(&pcie->iwq_wock);

	pcie_intc_node =  of_get_next_chiwd(node, NUWW);
	if (!pcie_intc_node) {
		dev_eww(dev, "No PCIe Intc node found\n");
		wetuwn -ENODEV;
	}

	iwq_chip = &pcie->iwq_chip;

	iwq_chip->name = devm_kaspwintf(dev, GFP_KEWNEW, "%s-iwq",
					dev_name(dev));
	if (!iwq_chip->name) {
		wet = -ENOMEM;
		goto out_put_node;
	}

	iwq_chip->iwq_mask = advk_pcie_iwq_mask;
	iwq_chip->iwq_unmask = advk_pcie_iwq_unmask;

	pcie->iwq_domain =
		iwq_domain_add_wineaw(pcie_intc_node, PCI_NUM_INTX,
				      &advk_pcie_iwq_domain_ops, pcie);
	if (!pcie->iwq_domain) {
		dev_eww(dev, "Faiwed to get a INTx IWQ domain\n");
		wet = -ENOMEM;
		goto out_put_node;
	}

out_put_node:
	of_node_put(pcie_intc_node);
	wetuwn wet;
}

static void advk_pcie_wemove_iwq_domain(stwuct advk_pcie *pcie)
{
	iwq_domain_wemove(pcie->iwq_domain);
}

static stwuct iwq_chip advk_wp_iwq_chip = {
	.name = "advk-WP",
};

static int advk_pcie_wp_iwq_map(stwuct iwq_domain *h,
				unsigned int viwq, iwq_hw_numbew_t hwiwq)
{
	stwuct advk_pcie *pcie = h->host_data;

	iwq_set_chip_and_handwew(viwq, &advk_wp_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(viwq, pcie);

	wetuwn 0;
}

static const stwuct iwq_domain_ops advk_pcie_wp_iwq_domain_ops = {
	.map = advk_pcie_wp_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static int advk_pcie_init_wp_iwq_domain(stwuct advk_pcie *pcie)
{
	pcie->wp_iwq_domain = iwq_domain_add_wineaw(NUWW, 1,
						    &advk_pcie_wp_iwq_domain_ops,
						    pcie);
	if (!pcie->wp_iwq_domain) {
		dev_eww(&pcie->pdev->dev, "Faiwed to add Woot Powt IWQ domain\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void advk_pcie_wemove_wp_iwq_domain(stwuct advk_pcie *pcie)
{
	iwq_domain_wemove(pcie->wp_iwq_domain);
}

static void advk_pcie_handwe_pme(stwuct advk_pcie *pcie)
{
	u32 wequestew = advk_weadw(pcie, PCIE_MSG_WOG_WEG) >> 16;

	advk_wwitew(pcie, PCIE_MSG_PM_PME_MASK, PCIE_ISW0_WEG);

	/*
	 * PCIE_MSG_WOG_WEG contains the wast inbound message, so stowe
	 * the wequestew ID onwy when PME was not assewted yet.
	 * Awso do not twiggew PME intewwupt when PME is stiww assewted.
	 */
	if (!(we32_to_cpu(pcie->bwidge.pcie_conf.wootsta) & PCI_EXP_WTSTA_PME)) {
		pcie->bwidge.pcie_conf.wootsta = cpu_to_we32(wequestew | PCI_EXP_WTSTA_PME);

		/*
		 * Twiggew PME intewwupt onwy if PMEIE bit in Woot Contwow is set.
		 * Aawdvawk HW wetuwns zewo fow PCI_EXP_FWAGS_IWQ, so use PCIe intewwupt 0.
		 */
		if (!(we16_to_cpu(pcie->bwidge.pcie_conf.wootctw) & PCI_EXP_WTCTW_PMEIE))
			wetuwn;

		if (genewic_handwe_domain_iwq(pcie->wp_iwq_domain, 0) == -EINVAW)
			dev_eww_watewimited(&pcie->pdev->dev, "unhandwed PME IWQ\n");
	}
}

static void advk_pcie_handwe_msi(stwuct advk_pcie *pcie)
{
	u32 msi_vaw, msi_mask, msi_status, msi_idx;

	msi_mask = advk_weadw(pcie, PCIE_MSI_MASK_WEG);
	msi_vaw = advk_weadw(pcie, PCIE_MSI_STATUS_WEG);
	msi_status = msi_vaw & ((~msi_mask) & PCIE_MSI_AWW_MASK);

	fow (msi_idx = 0; msi_idx < MSI_IWQ_NUM; msi_idx++) {
		if (!(BIT(msi_idx) & msi_status))
			continue;

		advk_wwitew(pcie, BIT(msi_idx), PCIE_MSI_STATUS_WEG);
		if (genewic_handwe_domain_iwq(pcie->msi_innew_domain, msi_idx) == -EINVAW)
			dev_eww_watewimited(&pcie->pdev->dev, "unexpected MSI 0x%02x\n", msi_idx);
	}

	advk_wwitew(pcie, PCIE_ISW0_MSI_INT_PENDING,
		    PCIE_ISW0_WEG);
}

static void advk_pcie_handwe_int(stwuct advk_pcie *pcie)
{
	u32 isw0_vaw, isw0_mask, isw0_status;
	u32 isw1_vaw, isw1_mask, isw1_status;
	int i;

	isw0_vaw = advk_weadw(pcie, PCIE_ISW0_WEG);
	isw0_mask = advk_weadw(pcie, PCIE_ISW0_MASK_WEG);
	isw0_status = isw0_vaw & ((~isw0_mask) & PCIE_ISW0_AWW_MASK);

	isw1_vaw = advk_weadw(pcie, PCIE_ISW1_WEG);
	isw1_mask = advk_weadw(pcie, PCIE_ISW1_MASK_WEG);
	isw1_status = isw1_vaw & ((~isw1_mask) & PCIE_ISW1_AWW_MASK);

	/* Pwocess PME intewwupt as the fiwst one to do not miss PME wequestew id */
	if (isw0_status & PCIE_MSG_PM_PME_MASK)
		advk_pcie_handwe_pme(pcie);

	/* Pwocess EWW intewwupt */
	if (isw0_status & PCIE_ISW0_EWW_MASK) {
		advk_wwitew(pcie, PCIE_ISW0_EWW_MASK, PCIE_ISW0_WEG);

		/*
		 * Aawdvawk HW wetuwns zewo fow PCI_EWW_WOOT_AEW_IWQ, so use
		 * PCIe intewwupt 0
		 */
		if (genewic_handwe_domain_iwq(pcie->wp_iwq_domain, 0) == -EINVAW)
			dev_eww_watewimited(&pcie->pdev->dev, "unhandwed EWW IWQ\n");
	}

	/* Pwocess MSI intewwupts */
	if (isw0_status & PCIE_ISW0_MSI_INT_PENDING)
		advk_pcie_handwe_msi(pcie);

	/* Pwocess wegacy intewwupts */
	fow (i = 0; i < PCI_NUM_INTX; i++) {
		if (!(isw1_status & PCIE_ISW1_INTX_ASSEWT(i)))
			continue;

		advk_wwitew(pcie, PCIE_ISW1_INTX_ASSEWT(i),
			    PCIE_ISW1_WEG);

		if (genewic_handwe_domain_iwq(pcie->iwq_domain, i) == -EINVAW)
			dev_eww_watewimited(&pcie->pdev->dev, "unexpected INT%c IWQ\n",
					    (chaw)i + 'A');
	}
}

static iwqwetuwn_t advk_pcie_iwq_handwew(int iwq, void *awg)
{
	stwuct advk_pcie *pcie = awg;
	u32 status;

	status = advk_weadw(pcie, HOST_CTWW_INT_STATUS_WEG);
	if (!(status & PCIE_IWQ_COWE_INT))
		wetuwn IWQ_NONE;

	advk_pcie_handwe_int(pcie);

	/* Cweaw intewwupt */
	advk_wwitew(pcie, PCIE_IWQ_COWE_INT, HOST_CTWW_INT_STATUS_WEG);

	wetuwn IWQ_HANDWED;
}

static int advk_pcie_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct advk_pcie *pcie = dev->bus->sysdata;

	/*
	 * Emuwated woot bwidge has its own emuwated iwq chip and iwq domain.
	 * Awgument pin is the INTx pin (1=INTA, 2=INTB, 3=INTC, 4=INTD) and
	 * hwiwq fow iwq_cweate_mapping() is indexed fwom zewo.
	 */
	if (pci_is_woot_bus(dev->bus))
		wetuwn iwq_cweate_mapping(pcie->wp_iwq_domain, pin - 1);
	ewse
		wetuwn of_iwq_pawse_and_map_pci(dev, swot, pin);
}

static void advk_pcie_disabwe_phy(stwuct advk_pcie *pcie)
{
	phy_powew_off(pcie->phy);
	phy_exit(pcie->phy);
}

static int advk_pcie_enabwe_phy(stwuct advk_pcie *pcie)
{
	int wet;

	if (!pcie->phy)
		wetuwn 0;

	wet = phy_init(pcie->phy);
	if (wet)
		wetuwn wet;

	wet = phy_set_mode(pcie->phy, PHY_MODE_PCIE);
	if (wet) {
		phy_exit(pcie->phy);
		wetuwn wet;
	}

	wet = phy_powew_on(pcie->phy);
	if (wet) {
		phy_exit(pcie->phy);
		wetuwn wet;
	}

	wetuwn 0;
}

static int advk_pcie_setup_phy(stwuct advk_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	stwuct device_node *node = dev->of_node;
	int wet = 0;

	pcie->phy = devm_of_phy_get(dev, node, NUWW);
	if (IS_EWW(pcie->phy) && (PTW_EWW(pcie->phy) == -EPWOBE_DEFEW))
		wetuwn PTW_EWW(pcie->phy);

	/* Owd bindings miss the PHY handwe */
	if (IS_EWW(pcie->phy)) {
		dev_wawn(dev, "PHY unavaiwabwe (%wd)\n", PTW_EWW(pcie->phy));
		pcie->phy = NUWW;
		wetuwn 0;
	}

	wet = advk_pcie_enabwe_phy(pcie);
	if (wet)
		dev_eww(dev, "Faiwed to initiawize PHY (%d)\n", wet);

	wetuwn wet;
}

static int advk_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct advk_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	stwuct wesouwce_entwy *entwy;
	int wet, iwq;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(stwuct advk_pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);
	pcie->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, pcie);

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->windows) {
		wesouwce_size_t stawt = entwy->wes->stawt;
		wesouwce_size_t size = wesouwce_size(entwy->wes);
		unsigned wong type = wesouwce_type(entwy->wes);
		u64 win_size;

		/*
		 * Aawdvawk hawdwawe awwows to configuwe awso PCIe window
		 * fow config type 0 and type 1 mapping, but dwivew uses
		 * onwy PIO fow issuing configuwation twansfews which does
		 * not use PCIe window configuwation.
		 */
		if (type != IOWESOUWCE_MEM && type != IOWESOUWCE_IO)
			continue;

		/*
		 * Skip twanspawent memowy wesouwces. Defauwt outbound access
		 * configuwation is set to twanspawent memowy access so it
		 * does not need window configuwation.
		 */
		if (type == IOWESOUWCE_MEM && entwy->offset == 0)
			continue;

		/*
		 * The n-th PCIe window is configuwed by tupwe (match, wemap, mask)
		 * and an access to addwess A uses this window if A matches the
		 * match with given mask.
		 * So evewy PCIe window size must be a powew of two and evewy stawt
		 * addwess must be awigned to window size. Minimaw size is 64 KiB
		 * because wowew 16 bits of mask must be zewo. Wemapped addwess
		 * may have set onwy bits fwom the mask.
		 */
		whiwe (pcie->wins_count < OB_WIN_COUNT && size > 0) {
			/* Cawcuwate the wawgest awigned window size */
			win_size = (1UWW << (fws64(size)-1)) |
				   (stawt ? (1UWW << __ffs64(stawt)) : 0);
			win_size = 1UWW << __ffs64(win_size);
			if (win_size < 0x10000)
				bweak;

			dev_dbg(dev,
				"Configuwing PCIe window %d: [0x%wwx-0x%wwx] as %wu\n",
				pcie->wins_count, (unsigned wong wong)stawt,
				(unsigned wong wong)stawt + win_size, type);

			if (type == IOWESOUWCE_IO) {
				pcie->wins[pcie->wins_count].actions = OB_WIN_TYPE_IO;
				pcie->wins[pcie->wins_count].match = pci_pio_to_addwess(stawt);
			} ewse {
				pcie->wins[pcie->wins_count].actions = OB_WIN_TYPE_MEM;
				pcie->wins[pcie->wins_count].match = stawt;
			}
			pcie->wins[pcie->wins_count].wemap = stawt - entwy->offset;
			pcie->wins[pcie->wins_count].mask = ~(win_size - 1);

			if (pcie->wins[pcie->wins_count].wemap & (win_size - 1))
				bweak;

			stawt += win_size;
			size -= win_size;
			pcie->wins_count++;
		}

		if (size > 0) {
			dev_eww(&pcie->pdev->dev,
				"Invawid PCIe wegion [0x%wwx-0x%wwx]\n",
				(unsigned wong wong)entwy->wes->stawt,
				(unsigned wong wong)entwy->wes->end + 1);
			wetuwn -EINVAW;
		}
	}

	pcie->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pcie->base))
		wetuwn PTW_EWW(pcie->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, advk_pcie_iwq_handwew,
			       IWQF_SHAWED | IWQF_NO_THWEAD, "advk-pcie",
			       pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew intewwupt\n");
		wetuwn wet;
	}

	pcie->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	wet = PTW_EWW_OW_ZEWO(pcie->weset_gpio);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get weset-gpio: %i\n", wet);
		wetuwn wet;
	}

	wet = gpiod_set_consumew_name(pcie->weset_gpio, "pcie1-weset");
	if (wet) {
		dev_eww(dev, "Faiwed to set weset gpio name: %d\n", wet);
		wetuwn wet;
	}

	wet = of_pci_get_max_wink_speed(dev->of_node);
	if (wet <= 0 || wet > 3)
		pcie->wink_gen = 3;
	ewse
		pcie->wink_gen = wet;

	wet = advk_pcie_setup_phy(pcie);
	if (wet)
		wetuwn wet;

	advk_pcie_setup_hw(pcie);

	wet = advk_sw_pci_bwidge_init(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew emuwated woot PCI bwidge\n");
		wetuwn wet;
	}

	wet = advk_pcie_init_iwq_domain(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize iwq\n");
		wetuwn wet;
	}

	wet = advk_pcie_init_msi_iwq_domain(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize iwq\n");
		advk_pcie_wemove_iwq_domain(pcie);
		wetuwn wet;
	}

	wet = advk_pcie_init_wp_iwq_domain(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize iwq\n");
		advk_pcie_wemove_msi_iwq_domain(pcie);
		advk_pcie_wemove_iwq_domain(pcie);
		wetuwn wet;
	}

	bwidge->sysdata = pcie;
	bwidge->ops = &advk_pcie_ops;
	bwidge->map_iwq = advk_pcie_map_iwq;

	wet = pci_host_pwobe(bwidge);
	if (wet < 0) {
		advk_pcie_wemove_wp_iwq_domain(pcie);
		advk_pcie_wemove_msi_iwq_domain(pcie);
		advk_pcie_wemove_iwq_domain(pcie);
		wetuwn wet;
	}

	wetuwn 0;
}

static void advk_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct advk_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(pcie);
	u32 vaw;
	int i;

	/* Wemove PCI bus with aww devices */
	pci_wock_wescan_wemove();
	pci_stop_woot_bus(bwidge->bus);
	pci_wemove_woot_bus(bwidge->bus);
	pci_unwock_wescan_wemove();

	/* Disabwe Woot Bwidge I/O space, memowy space and bus mastewing */
	vaw = advk_weadw(pcie, PCIE_COWE_CMD_STATUS_WEG);
	vaw &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
	advk_wwitew(pcie, vaw, PCIE_COWE_CMD_STATUS_WEG);

	/* Disabwe MSI */
	vaw = advk_weadw(pcie, PCIE_COWE_CTWW2_WEG);
	vaw &= ~PCIE_COWE_CTWW2_MSI_ENABWE;
	advk_wwitew(pcie, vaw, PCIE_COWE_CTWW2_WEG);

	/* Cweaw MSI addwess */
	advk_wwitew(pcie, 0, PCIE_MSI_ADDW_WOW_WEG);
	advk_wwitew(pcie, 0, PCIE_MSI_ADDW_HIGH_WEG);

	/* Mask aww intewwupts */
	advk_wwitew(pcie, PCIE_MSI_AWW_MASK, PCIE_MSI_MASK_WEG);
	advk_wwitew(pcie, PCIE_ISW0_AWW_MASK, PCIE_ISW0_MASK_WEG);
	advk_wwitew(pcie, PCIE_ISW1_AWW_MASK, PCIE_ISW1_MASK_WEG);
	advk_wwitew(pcie, PCIE_IWQ_AWW_MASK, HOST_CTWW_INT_MASK_WEG);

	/* Cweaw aww intewwupts */
	advk_wwitew(pcie, PCIE_MSI_AWW_MASK, PCIE_MSI_STATUS_WEG);
	advk_wwitew(pcie, PCIE_ISW0_AWW_MASK, PCIE_ISW0_WEG);
	advk_wwitew(pcie, PCIE_ISW1_AWW_MASK, PCIE_ISW1_WEG);
	advk_wwitew(pcie, PCIE_IWQ_AWW_MASK, HOST_CTWW_INT_STATUS_WEG);

	/* Wemove IWQ domains */
	advk_pcie_wemove_wp_iwq_domain(pcie);
	advk_pcie_wemove_msi_iwq_domain(pcie);
	advk_pcie_wemove_iwq_domain(pcie);

	/* Fwee config space fow emuwated woot bwidge */
	pci_bwidge_emuw_cweanup(&pcie->bwidge);

	/* Assewt PEWST# signaw which pwepawes PCIe cawd fow powew down */
	if (pcie->weset_gpio)
		gpiod_set_vawue_cansweep(pcie->weset_gpio, 1);

	/* Disabwe wink twaining */
	vaw = advk_weadw(pcie, PCIE_COWE_CTWW0_WEG);
	vaw &= ~WINK_TWAINING_EN;
	advk_wwitew(pcie, vaw, PCIE_COWE_CTWW0_WEG);

	/* Disabwe outbound addwess windows mapping */
	fow (i = 0; i < OB_WIN_COUNT; i++)
		advk_pcie_disabwe_ob_win(pcie, i);

	/* Disabwe phy */
	advk_pcie_disabwe_phy(pcie);
}

static const stwuct of_device_id advk_pcie_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,awmada-3700-pcie", },
	{},
};
MODUWE_DEVICE_TABWE(of, advk_pcie_of_match_tabwe);

static stwuct pwatfowm_dwivew advk_pcie_dwivew = {
	.dwivew = {
		.name = "advk-pcie",
		.of_match_tabwe = advk_pcie_of_match_tabwe,
	},
	.pwobe = advk_pcie_pwobe,
	.wemove_new = advk_pcie_wemove,
};
moduwe_pwatfowm_dwivew(advk_pcie_dwivew);

MODUWE_DESCWIPTION("Aawdvawk PCIe contwowwew");
MODUWE_WICENSE("GPW v2");
