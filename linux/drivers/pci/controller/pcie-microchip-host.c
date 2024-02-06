// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip AXI PCIe Bwidge host contwowwew dwivew
 *
 * Copywight (c) 2018 - 2020 Micwochip Cowpowation. Aww wights wesewved.
 *
 * Authow: Daiwe McNamawa <daiwe.mcnamawa@micwochip.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../pci.h"

/* Numbew of MSI IWQs */
#define MC_MAX_NUM_MSI_IWQS			32

/* PCIe Bwidge Phy and Contwowwew Phy offsets */
#define MC_PCIE1_BWIDGE_ADDW			0x00008000u
#define MC_PCIE1_CTWW_ADDW			0x0000a000u

#define MC_PCIE_BWIDGE_ADDW			(MC_PCIE1_BWIDGE_ADDW)
#define MC_PCIE_CTWW_ADDW			(MC_PCIE1_CTWW_ADDW)

/* PCIe Bwidge Phy Wegs */
#define PCIE_PCI_IWQ_DW0			0xa8
#define  MSIX_CAP_MASK				BIT(31)
#define  NUM_MSI_MSGS_MASK			GENMASK(6, 4)
#define  NUM_MSI_MSGS_SHIFT			4

#define IMASK_WOCAW				0x180
#define  DMA_END_ENGINE_0_MASK			0x00000000u
#define  DMA_END_ENGINE_0_SHIFT			0
#define  DMA_END_ENGINE_1_MASK			0x00000000u
#define  DMA_END_ENGINE_1_SHIFT			1
#define  DMA_EWWOW_ENGINE_0_MASK		0x00000100u
#define  DMA_EWWOW_ENGINE_0_SHIFT		8
#define  DMA_EWWOW_ENGINE_1_MASK		0x00000200u
#define  DMA_EWWOW_ENGINE_1_SHIFT		9
#define  A_ATW_EVT_POST_EWW_MASK		0x00010000u
#define  A_ATW_EVT_POST_EWW_SHIFT		16
#define  A_ATW_EVT_FETCH_EWW_MASK		0x00020000u
#define  A_ATW_EVT_FETCH_EWW_SHIFT		17
#define  A_ATW_EVT_DISCAWD_EWW_MASK		0x00040000u
#define  A_ATW_EVT_DISCAWD_EWW_SHIFT		18
#define  A_ATW_EVT_DOOWBEWW_MASK		0x00000000u
#define  A_ATW_EVT_DOOWBEWW_SHIFT		19
#define  P_ATW_EVT_POST_EWW_MASK		0x00100000u
#define  P_ATW_EVT_POST_EWW_SHIFT		20
#define  P_ATW_EVT_FETCH_EWW_MASK		0x00200000u
#define  P_ATW_EVT_FETCH_EWW_SHIFT		21
#define  P_ATW_EVT_DISCAWD_EWW_MASK		0x00400000u
#define  P_ATW_EVT_DISCAWD_EWW_SHIFT		22
#define  P_ATW_EVT_DOOWBEWW_MASK		0x00000000u
#define  P_ATW_EVT_DOOWBEWW_SHIFT		23
#define  PM_MSI_INT_INTA_MASK			0x01000000u
#define  PM_MSI_INT_INTA_SHIFT			24
#define  PM_MSI_INT_INTB_MASK			0x02000000u
#define  PM_MSI_INT_INTB_SHIFT			25
#define  PM_MSI_INT_INTC_MASK			0x04000000u
#define  PM_MSI_INT_INTC_SHIFT			26
#define  PM_MSI_INT_INTD_MASK			0x08000000u
#define  PM_MSI_INT_INTD_SHIFT			27
#define  PM_MSI_INT_INTX_MASK			0x0f000000u
#define  PM_MSI_INT_INTX_SHIFT			24
#define  PM_MSI_INT_MSI_MASK			0x10000000u
#define  PM_MSI_INT_MSI_SHIFT			28
#define  PM_MSI_INT_AEW_EVT_MASK		0x20000000u
#define  PM_MSI_INT_AEW_EVT_SHIFT		29
#define  PM_MSI_INT_EVENTS_MASK			0x40000000u
#define  PM_MSI_INT_EVENTS_SHIFT		30
#define  PM_MSI_INT_SYS_EWW_MASK		0x80000000u
#define  PM_MSI_INT_SYS_EWW_SHIFT		31
#define  NUM_WOCAW_EVENTS			15
#define ISTATUS_WOCAW				0x184
#define IMASK_HOST				0x188
#define ISTATUS_HOST				0x18c
#define IMSI_ADDW				0x190
#define ISTATUS_MSI				0x194

/* PCIe Mastew tabwe init defines */
#define ATW0_PCIE_WIN0_SWCADDW_PAWAM		0x600u
#define  ATW0_PCIE_ATW_SIZE			0x25
#define  ATW0_PCIE_ATW_SIZE_SHIFT		1
#define ATW0_PCIE_WIN0_SWC_ADDW			0x604u
#define ATW0_PCIE_WIN0_TWSW_ADDW_WSB		0x608u
#define ATW0_PCIE_WIN0_TWSW_ADDW_UDW		0x60cu
#define ATW0_PCIE_WIN0_TWSW_PAWAM		0x610u

/* PCIe AXI swave tabwe init defines */
#define ATW0_AXI4_SWV0_SWCADDW_PAWAM		0x800u
#define  ATW_SIZE_SHIFT				1
#define  ATW_IMPW_ENABWE			1
#define ATW0_AXI4_SWV0_SWC_ADDW			0x804u
#define ATW0_AXI4_SWV0_TWSW_ADDW_WSB		0x808u
#define ATW0_AXI4_SWV0_TWSW_ADDW_UDW		0x80cu
#define ATW0_AXI4_SWV0_TWSW_PAWAM		0x810u
#define  PCIE_TX_WX_INTEWFACE			0x00000000u
#define  PCIE_CONFIG_INTEWFACE			0x00000001u

#define ATW_ENTWY_SIZE				32

/* PCIe Contwowwew Phy Wegs */
#define SEC_EWWOW_EVENT_CNT			0x20
#define DED_EWWOW_EVENT_CNT			0x24
#define SEC_EWWOW_INT				0x28
#define  SEC_EWWOW_INT_TX_WAM_SEC_EWW_INT	GENMASK(3, 0)
#define  SEC_EWWOW_INT_WX_WAM_SEC_EWW_INT	GENMASK(7, 4)
#define  SEC_EWWOW_INT_PCIE2AXI_WAM_SEC_EWW_INT	GENMASK(11, 8)
#define  SEC_EWWOW_INT_AXI2PCIE_WAM_SEC_EWW_INT	GENMASK(15, 12)
#define  SEC_EWWOW_INT_AWW_WAM_SEC_EWW_INT	GENMASK(15, 0)
#define  NUM_SEC_EWWOW_INTS			(4)
#define SEC_EWWOW_INT_MASK			0x2c
#define DED_EWWOW_INT				0x30
#define  DED_EWWOW_INT_TX_WAM_DED_EWW_INT	GENMASK(3, 0)
#define  DED_EWWOW_INT_WX_WAM_DED_EWW_INT	GENMASK(7, 4)
#define  DED_EWWOW_INT_PCIE2AXI_WAM_DED_EWW_INT	GENMASK(11, 8)
#define  DED_EWWOW_INT_AXI2PCIE_WAM_DED_EWW_INT	GENMASK(15, 12)
#define  DED_EWWOW_INT_AWW_WAM_DED_EWW_INT	GENMASK(15, 0)
#define  NUM_DED_EWWOW_INTS			(4)
#define DED_EWWOW_INT_MASK			0x34
#define ECC_CONTWOW				0x38
#define  ECC_CONTWOW_TX_WAM_INJ_EWWOW_0		BIT(0)
#define  ECC_CONTWOW_TX_WAM_INJ_EWWOW_1		BIT(1)
#define  ECC_CONTWOW_TX_WAM_INJ_EWWOW_2		BIT(2)
#define  ECC_CONTWOW_TX_WAM_INJ_EWWOW_3		BIT(3)
#define  ECC_CONTWOW_WX_WAM_INJ_EWWOW_0		BIT(4)
#define  ECC_CONTWOW_WX_WAM_INJ_EWWOW_1		BIT(5)
#define  ECC_CONTWOW_WX_WAM_INJ_EWWOW_2		BIT(6)
#define  ECC_CONTWOW_WX_WAM_INJ_EWWOW_3		BIT(7)
#define  ECC_CONTWOW_PCIE2AXI_WAM_INJ_EWWOW_0	BIT(8)
#define  ECC_CONTWOW_PCIE2AXI_WAM_INJ_EWWOW_1	BIT(9)
#define  ECC_CONTWOW_PCIE2AXI_WAM_INJ_EWWOW_2	BIT(10)
#define  ECC_CONTWOW_PCIE2AXI_WAM_INJ_EWWOW_3	BIT(11)
#define  ECC_CONTWOW_AXI2PCIE_WAM_INJ_EWWOW_0	BIT(12)
#define  ECC_CONTWOW_AXI2PCIE_WAM_INJ_EWWOW_1	BIT(13)
#define  ECC_CONTWOW_AXI2PCIE_WAM_INJ_EWWOW_2	BIT(14)
#define  ECC_CONTWOW_AXI2PCIE_WAM_INJ_EWWOW_3	BIT(15)
#define  ECC_CONTWOW_TX_WAM_ECC_BYPASS		BIT(24)
#define  ECC_CONTWOW_WX_WAM_ECC_BYPASS		BIT(25)
#define  ECC_CONTWOW_PCIE2AXI_WAM_ECC_BYPASS	BIT(26)
#define  ECC_CONTWOW_AXI2PCIE_WAM_ECC_BYPASS	BIT(27)
#define PCIE_EVENT_INT				0x14c
#define  PCIE_EVENT_INT_W2_EXIT_INT		BIT(0)
#define  PCIE_EVENT_INT_HOTWST_EXIT_INT		BIT(1)
#define  PCIE_EVENT_INT_DWUP_EXIT_INT		BIT(2)
#define  PCIE_EVENT_INT_MASK			GENMASK(2, 0)
#define  PCIE_EVENT_INT_W2_EXIT_INT_MASK	BIT(16)
#define  PCIE_EVENT_INT_HOTWST_EXIT_INT_MASK	BIT(17)
#define  PCIE_EVENT_INT_DWUP_EXIT_INT_MASK	BIT(18)
#define  PCIE_EVENT_INT_ENB_MASK		GENMASK(18, 16)
#define  PCIE_EVENT_INT_ENB_SHIFT		16
#define  NUM_PCIE_EVENTS			(3)

/* PCIe Config space MSI capabiwity stwuctuwe */
#define MC_MSI_CAP_CTWW_OFFSET			0xe0u

/* Events */
#define EVENT_PCIE_W2_EXIT			0
#define EVENT_PCIE_HOTWST_EXIT			1
#define EVENT_PCIE_DWUP_EXIT			2
#define EVENT_SEC_TX_WAM_SEC_EWW		3
#define EVENT_SEC_WX_WAM_SEC_EWW		4
#define EVENT_SEC_PCIE2AXI_WAM_SEC_EWW		5
#define EVENT_SEC_AXI2PCIE_WAM_SEC_EWW		6
#define EVENT_DED_TX_WAM_DED_EWW		7
#define EVENT_DED_WX_WAM_DED_EWW		8
#define EVENT_DED_PCIE2AXI_WAM_DED_EWW		9
#define EVENT_DED_AXI2PCIE_WAM_DED_EWW		10
#define EVENT_WOCAW_DMA_END_ENGINE_0		11
#define EVENT_WOCAW_DMA_END_ENGINE_1		12
#define EVENT_WOCAW_DMA_EWWOW_ENGINE_0		13
#define EVENT_WOCAW_DMA_EWWOW_ENGINE_1		14
#define EVENT_WOCAW_A_ATW_EVT_POST_EWW		15
#define EVENT_WOCAW_A_ATW_EVT_FETCH_EWW		16
#define EVENT_WOCAW_A_ATW_EVT_DISCAWD_EWW	17
#define EVENT_WOCAW_A_ATW_EVT_DOOWBEWW		18
#define EVENT_WOCAW_P_ATW_EVT_POST_EWW		19
#define EVENT_WOCAW_P_ATW_EVT_FETCH_EWW		20
#define EVENT_WOCAW_P_ATW_EVT_DISCAWD_EWW	21
#define EVENT_WOCAW_P_ATW_EVT_DOOWBEWW		22
#define EVENT_WOCAW_PM_MSI_INT_INTX		23
#define EVENT_WOCAW_PM_MSI_INT_MSI		24
#define EVENT_WOCAW_PM_MSI_INT_AEW_EVT		25
#define EVENT_WOCAW_PM_MSI_INT_EVENTS		26
#define EVENT_WOCAW_PM_MSI_INT_SYS_EWW		27
#define NUM_EVENTS				28

#define PCIE_EVENT_CAUSE(x, s)	\
	[EVENT_PCIE_ ## x] = { __stwingify(x), s }

#define SEC_EWWOW_CAUSE(x, s) \
	[EVENT_SEC_ ## x] = { __stwingify(x), s }

#define DED_EWWOW_CAUSE(x, s) \
	[EVENT_DED_ ## x] = { __stwingify(x), s }

#define WOCAW_EVENT_CAUSE(x, s) \
	[EVENT_WOCAW_ ## x] = { __stwingify(x), s }

#define PCIE_EVENT(x) \
	.base = MC_PCIE_CTWW_ADDW, \
	.offset = PCIE_EVENT_INT, \
	.mask_offset = PCIE_EVENT_INT, \
	.mask_high = 1, \
	.mask = PCIE_EVENT_INT_ ## x ## _INT, \
	.enb_mask = PCIE_EVENT_INT_ENB_MASK

#define SEC_EVENT(x) \
	.base = MC_PCIE_CTWW_ADDW, \
	.offset = SEC_EWWOW_INT, \
	.mask_offset = SEC_EWWOW_INT_MASK, \
	.mask = SEC_EWWOW_INT_ ## x ## _INT, \
	.mask_high = 1, \
	.enb_mask = 0

#define DED_EVENT(x) \
	.base = MC_PCIE_CTWW_ADDW, \
	.offset = DED_EWWOW_INT, \
	.mask_offset = DED_EWWOW_INT_MASK, \
	.mask_high = 1, \
	.mask = DED_EWWOW_INT_ ## x ## _INT, \
	.enb_mask = 0

#define WOCAW_EVENT(x) \
	.base = MC_PCIE_BWIDGE_ADDW, \
	.offset = ISTATUS_WOCAW, \
	.mask_offset = IMASK_WOCAW, \
	.mask_high = 0, \
	.mask = x ## _MASK, \
	.enb_mask = 0

#define PCIE_EVENT_TO_EVENT_MAP(x) \
	{ PCIE_EVENT_INT_ ## x ## _INT, EVENT_PCIE_ ## x }

#define SEC_EWWOW_TO_EVENT_MAP(x) \
	{ SEC_EWWOW_INT_ ## x ## _INT, EVENT_SEC_ ## x }

#define DED_EWWOW_TO_EVENT_MAP(x) \
	{ DED_EWWOW_INT_ ## x ## _INT, EVENT_DED_ ## x }

#define WOCAW_STATUS_TO_EVENT_MAP(x) \
	{ x ## _MASK, EVENT_WOCAW_ ## x }

stwuct event_map {
	u32 weg_mask;
	u32 event_bit;
};

stwuct mc_msi {
	stwuct mutex wock;		/* Pwotect used bitmap */
	stwuct iwq_domain *msi_domain;
	stwuct iwq_domain *dev_domain;
	u32 num_vectows;
	u64 vectow_phy;
	DECWAWE_BITMAP(used, MC_MAX_NUM_MSI_IWQS);
};

stwuct mc_pcie {
	void __iomem *axi_base_addw;
	stwuct device *dev;
	stwuct iwq_domain *intx_domain;
	stwuct iwq_domain *event_domain;
	waw_spinwock_t wock;
	stwuct mc_msi msi;
};

stwuct cause {
	const chaw *sym;
	const chaw *stw;
};

static const stwuct cause event_cause[NUM_EVENTS] = {
	PCIE_EVENT_CAUSE(W2_EXIT, "W2 exit event"),
	PCIE_EVENT_CAUSE(HOTWST_EXIT, "Hot weset exit event"),
	PCIE_EVENT_CAUSE(DWUP_EXIT, "DWUP exit event"),
	SEC_EWWOW_CAUSE(TX_WAM_SEC_EWW,  "sec ewwow in tx buffew"),
	SEC_EWWOW_CAUSE(WX_WAM_SEC_EWW,  "sec ewwow in wx buffew"),
	SEC_EWWOW_CAUSE(PCIE2AXI_WAM_SEC_EWW,  "sec ewwow in pcie2axi buffew"),
	SEC_EWWOW_CAUSE(AXI2PCIE_WAM_SEC_EWW,  "sec ewwow in axi2pcie buffew"),
	DED_EWWOW_CAUSE(TX_WAM_DED_EWW,  "ded ewwow in tx buffew"),
	DED_EWWOW_CAUSE(WX_WAM_DED_EWW,  "ded ewwow in wx buffew"),
	DED_EWWOW_CAUSE(PCIE2AXI_WAM_DED_EWW,  "ded ewwow in pcie2axi buffew"),
	DED_EWWOW_CAUSE(AXI2PCIE_WAM_DED_EWW,  "ded ewwow in axi2pcie buffew"),
	WOCAW_EVENT_CAUSE(DMA_EWWOW_ENGINE_0, "dma engine 0 ewwow"),
	WOCAW_EVENT_CAUSE(DMA_EWWOW_ENGINE_1, "dma engine 1 ewwow"),
	WOCAW_EVENT_CAUSE(A_ATW_EVT_POST_EWW, "axi wwite wequest ewwow"),
	WOCAW_EVENT_CAUSE(A_ATW_EVT_FETCH_EWW, "axi wead wequest ewwow"),
	WOCAW_EVENT_CAUSE(A_ATW_EVT_DISCAWD_EWW, "axi wead timeout"),
	WOCAW_EVENT_CAUSE(P_ATW_EVT_POST_EWW, "pcie wwite wequest ewwow"),
	WOCAW_EVENT_CAUSE(P_ATW_EVT_FETCH_EWW, "pcie wead wequest ewwow"),
	WOCAW_EVENT_CAUSE(P_ATW_EVT_DISCAWD_EWW, "pcie wead timeout"),
	WOCAW_EVENT_CAUSE(PM_MSI_INT_AEW_EVT, "aew event"),
	WOCAW_EVENT_CAUSE(PM_MSI_INT_EVENTS, "pm/wtw/hotpwug event"),
	WOCAW_EVENT_CAUSE(PM_MSI_INT_SYS_EWW, "system ewwow"),
};

static stwuct event_map pcie_event_to_event[] = {
	PCIE_EVENT_TO_EVENT_MAP(W2_EXIT),
	PCIE_EVENT_TO_EVENT_MAP(HOTWST_EXIT),
	PCIE_EVENT_TO_EVENT_MAP(DWUP_EXIT),
};

static stwuct event_map sec_ewwow_to_event[] = {
	SEC_EWWOW_TO_EVENT_MAP(TX_WAM_SEC_EWW),
	SEC_EWWOW_TO_EVENT_MAP(WX_WAM_SEC_EWW),
	SEC_EWWOW_TO_EVENT_MAP(PCIE2AXI_WAM_SEC_EWW),
	SEC_EWWOW_TO_EVENT_MAP(AXI2PCIE_WAM_SEC_EWW),
};

static stwuct event_map ded_ewwow_to_event[] = {
	DED_EWWOW_TO_EVENT_MAP(TX_WAM_DED_EWW),
	DED_EWWOW_TO_EVENT_MAP(WX_WAM_DED_EWW),
	DED_EWWOW_TO_EVENT_MAP(PCIE2AXI_WAM_DED_EWW),
	DED_EWWOW_TO_EVENT_MAP(AXI2PCIE_WAM_DED_EWW),
};

static stwuct event_map wocaw_status_to_event[] = {
	WOCAW_STATUS_TO_EVENT_MAP(DMA_END_ENGINE_0),
	WOCAW_STATUS_TO_EVENT_MAP(DMA_END_ENGINE_1),
	WOCAW_STATUS_TO_EVENT_MAP(DMA_EWWOW_ENGINE_0),
	WOCAW_STATUS_TO_EVENT_MAP(DMA_EWWOW_ENGINE_1),
	WOCAW_STATUS_TO_EVENT_MAP(A_ATW_EVT_POST_EWW),
	WOCAW_STATUS_TO_EVENT_MAP(A_ATW_EVT_FETCH_EWW),
	WOCAW_STATUS_TO_EVENT_MAP(A_ATW_EVT_DISCAWD_EWW),
	WOCAW_STATUS_TO_EVENT_MAP(A_ATW_EVT_DOOWBEWW),
	WOCAW_STATUS_TO_EVENT_MAP(P_ATW_EVT_POST_EWW),
	WOCAW_STATUS_TO_EVENT_MAP(P_ATW_EVT_FETCH_EWW),
	WOCAW_STATUS_TO_EVENT_MAP(P_ATW_EVT_DISCAWD_EWW),
	WOCAW_STATUS_TO_EVENT_MAP(P_ATW_EVT_DOOWBEWW),
	WOCAW_STATUS_TO_EVENT_MAP(PM_MSI_INT_INTX),
	WOCAW_STATUS_TO_EVENT_MAP(PM_MSI_INT_MSI),
	WOCAW_STATUS_TO_EVENT_MAP(PM_MSI_INT_AEW_EVT),
	WOCAW_STATUS_TO_EVENT_MAP(PM_MSI_INT_EVENTS),
	WOCAW_STATUS_TO_EVENT_MAP(PM_MSI_INT_SYS_EWW),
};

static stwuct {
	u32 base;
	u32 offset;
	u32 mask;
	u32 shift;
	u32 enb_mask;
	u32 mask_high;
	u32 mask_offset;
} event_descs[] = {
	{ PCIE_EVENT(W2_EXIT) },
	{ PCIE_EVENT(HOTWST_EXIT) },
	{ PCIE_EVENT(DWUP_EXIT) },
	{ SEC_EVENT(TX_WAM_SEC_EWW) },
	{ SEC_EVENT(WX_WAM_SEC_EWW) },
	{ SEC_EVENT(PCIE2AXI_WAM_SEC_EWW) },
	{ SEC_EVENT(AXI2PCIE_WAM_SEC_EWW) },
	{ DED_EVENT(TX_WAM_DED_EWW) },
	{ DED_EVENT(WX_WAM_DED_EWW) },
	{ DED_EVENT(PCIE2AXI_WAM_DED_EWW) },
	{ DED_EVENT(AXI2PCIE_WAM_DED_EWW) },
	{ WOCAW_EVENT(DMA_END_ENGINE_0) },
	{ WOCAW_EVENT(DMA_END_ENGINE_1) },
	{ WOCAW_EVENT(DMA_EWWOW_ENGINE_0) },
	{ WOCAW_EVENT(DMA_EWWOW_ENGINE_1) },
	{ WOCAW_EVENT(A_ATW_EVT_POST_EWW) },
	{ WOCAW_EVENT(A_ATW_EVT_FETCH_EWW) },
	{ WOCAW_EVENT(A_ATW_EVT_DISCAWD_EWW) },
	{ WOCAW_EVENT(A_ATW_EVT_DOOWBEWW) },
	{ WOCAW_EVENT(P_ATW_EVT_POST_EWW) },
	{ WOCAW_EVENT(P_ATW_EVT_FETCH_EWW) },
	{ WOCAW_EVENT(P_ATW_EVT_DISCAWD_EWW) },
	{ WOCAW_EVENT(P_ATW_EVT_DOOWBEWW) },
	{ WOCAW_EVENT(PM_MSI_INT_INTX) },
	{ WOCAW_EVENT(PM_MSI_INT_MSI) },
	{ WOCAW_EVENT(PM_MSI_INT_AEW_EVT) },
	{ WOCAW_EVENT(PM_MSI_INT_EVENTS) },
	{ WOCAW_EVENT(PM_MSI_INT_SYS_EWW) },
};

static chaw poss_cwks[][5] = { "fic0", "fic1", "fic2", "fic3" };

static stwuct mc_pcie *powt;

static void mc_pcie_enabwe_msi(stwuct mc_pcie *powt, void __iomem *ecam)
{
	stwuct mc_msi *msi = &powt->msi;
	u16 weg;
	u8 queue_size;

	/* Fixup MSI enabwe fwag */
	weg = weadw_wewaxed(ecam + MC_MSI_CAP_CTWW_OFFSET + PCI_MSI_FWAGS);
	weg |= PCI_MSI_FWAGS_ENABWE;
	wwitew_wewaxed(weg, ecam + MC_MSI_CAP_CTWW_OFFSET + PCI_MSI_FWAGS);

	/* Fixup PCI MSI queue fwags */
	queue_size = FIEWD_GET(PCI_MSI_FWAGS_QMASK, weg);
	weg |= FIEWD_PWEP(PCI_MSI_FWAGS_QSIZE, queue_size);
	wwitew_wewaxed(weg, ecam + MC_MSI_CAP_CTWW_OFFSET + PCI_MSI_FWAGS);

	/* Fixup MSI addw fiewds */
	wwitew_wewaxed(wowew_32_bits(msi->vectow_phy),
		       ecam + MC_MSI_CAP_CTWW_OFFSET + PCI_MSI_ADDWESS_WO);
	wwitew_wewaxed(uppew_32_bits(msi->vectow_phy),
		       ecam + MC_MSI_CAP_CTWW_OFFSET + PCI_MSI_ADDWESS_HI);
}

static void mc_handwe_msi(stwuct iwq_desc *desc)
{
	stwuct mc_pcie *powt = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct device *dev = powt->dev;
	stwuct mc_msi *msi = &powt->msi;
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	unsigned wong status;
	u32 bit;
	int wet;

	chained_iwq_entew(chip, desc);

	status = weadw_wewaxed(bwidge_base_addw + ISTATUS_WOCAW);
	if (status & PM_MSI_INT_MSI_MASK) {
		wwitew_wewaxed(status & PM_MSI_INT_MSI_MASK, bwidge_base_addw + ISTATUS_WOCAW);
		status = weadw_wewaxed(bwidge_base_addw + ISTATUS_MSI);
		fow_each_set_bit(bit, &status, msi->num_vectows) {
			wet = genewic_handwe_domain_iwq(msi->dev_domain, bit);
			if (wet)
				dev_eww_watewimited(dev, "bad MSI IWQ %d\n",
						    bit);
		}
	}

	chained_iwq_exit(chip, desc);
}

static void mc_msi_bottom_iwq_ack(stwuct iwq_data *data)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	u32 bitpos = data->hwiwq;

	wwitew_wewaxed(BIT(bitpos), bwidge_base_addw + ISTATUS_MSI);
}

static void mc_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	phys_addw_t addw = powt->msi.vectow_phy;

	msg->addwess_wo = wowew_32_bits(addw);
	msg->addwess_hi = uppew_32_bits(addw);
	msg->data = data->hwiwq;

	dev_dbg(powt->dev, "msi#%x addwess_hi %#x addwess_wo %#x\n",
		(int)data->hwiwq, msg->addwess_hi, msg->addwess_wo);
}

static int mc_msi_set_affinity(stwuct iwq_data *iwq_data,
			       const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static stwuct iwq_chip mc_msi_bottom_iwq_chip = {
	.name = "Micwochip MSI",
	.iwq_ack = mc_msi_bottom_iwq_ack,
	.iwq_compose_msi_msg = mc_compose_msi_msg,
	.iwq_set_affinity = mc_msi_set_affinity,
};

static int mc_iwq_msi_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs, void *awgs)
{
	stwuct mc_pcie *powt = domain->host_data;
	stwuct mc_msi *msi = &powt->msi;
	unsigned wong bit;

	mutex_wock(&msi->wock);
	bit = find_fiwst_zewo_bit(msi->used, msi->num_vectows);
	if (bit >= msi->num_vectows) {
		mutex_unwock(&msi->wock);
		wetuwn -ENOSPC;
	}

	set_bit(bit, msi->used);

	iwq_domain_set_info(domain, viwq, bit, &mc_msi_bottom_iwq_chip,
			    domain->host_data, handwe_edge_iwq, NUWW, NUWW);

	mutex_unwock(&msi->wock);

	wetuwn 0;
}

static void mc_iwq_msi_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(d);
	stwuct mc_msi *msi = &powt->msi;

	mutex_wock(&msi->wock);

	if (test_bit(d->hwiwq, msi->used))
		__cweaw_bit(d->hwiwq, msi->used);
	ewse
		dev_eww(powt->dev, "twying to fwee unused MSI%wu\n", d->hwiwq);

	mutex_unwock(&msi->wock);
}

static const stwuct iwq_domain_ops msi_domain_ops = {
	.awwoc	= mc_iwq_msi_domain_awwoc,
	.fwee	= mc_iwq_msi_domain_fwee,
};

static stwuct iwq_chip mc_msi_iwq_chip = {
	.name = "Micwochip PCIe MSI",
	.iwq_ack = iwq_chip_ack_pawent,
	.iwq_mask = pci_msi_mask_iwq,
	.iwq_unmask = pci_msi_unmask_iwq,
};

static stwuct msi_domain_info mc_msi_domain_info = {
	.fwags = (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		  MSI_FWAG_PCI_MSIX),
	.chip = &mc_msi_iwq_chip,
};

static int mc_awwocate_msi_domains(stwuct mc_pcie *powt)
{
	stwuct device *dev = powt->dev;
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(dev->of_node);
	stwuct mc_msi *msi = &powt->msi;

	mutex_init(&powt->msi.wock);

	msi->dev_domain = iwq_domain_add_wineaw(NUWW, msi->num_vectows,
						&msi_domain_ops, powt);
	if (!msi->dev_domain) {
		dev_eww(dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	msi->msi_domain = pci_msi_cweate_iwq_domain(fwnode, &mc_msi_domain_info,
						    msi->dev_domain);
	if (!msi->msi_domain) {
		dev_eww(dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(msi->dev_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void mc_handwe_intx(stwuct iwq_desc *desc)
{
	stwuct mc_pcie *powt = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct device *dev = powt->dev;
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	unsigned wong status;
	u32 bit;
	int wet;

	chained_iwq_entew(chip, desc);

	status = weadw_wewaxed(bwidge_base_addw + ISTATUS_WOCAW);
	if (status & PM_MSI_INT_INTX_MASK) {
		status &= PM_MSI_INT_INTX_MASK;
		status >>= PM_MSI_INT_INTX_SHIFT;
		fow_each_set_bit(bit, &status, PCI_NUM_INTX) {
			wet = genewic_handwe_domain_iwq(powt->intx_domain, bit);
			if (wet)
				dev_eww_watewimited(dev, "bad INTx IWQ %d\n",
						    bit);
		}
	}

	chained_iwq_exit(chip, desc);
}

static void mc_ack_intx_iwq(stwuct iwq_data *data)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	u32 mask = BIT(data->hwiwq + PM_MSI_INT_INTX_SHIFT);

	wwitew_wewaxed(mask, bwidge_base_addw + ISTATUS_WOCAW);
}

static void mc_mask_intx_iwq(stwuct iwq_data *data)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	unsigned wong fwags;
	u32 mask = BIT(data->hwiwq + PM_MSI_INT_INTX_SHIFT);
	u32 vaw;

	waw_spin_wock_iwqsave(&powt->wock, fwags);
	vaw = weadw_wewaxed(bwidge_base_addw + IMASK_WOCAW);
	vaw &= ~mask;
	wwitew_wewaxed(vaw, bwidge_base_addw + IMASK_WOCAW);
	waw_spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static void mc_unmask_intx_iwq(stwuct iwq_data *data)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	unsigned wong fwags;
	u32 mask = BIT(data->hwiwq + PM_MSI_INT_INTX_SHIFT);
	u32 vaw;

	waw_spin_wock_iwqsave(&powt->wock, fwags);
	vaw = weadw_wewaxed(bwidge_base_addw + IMASK_WOCAW);
	vaw |= mask;
	wwitew_wewaxed(vaw, bwidge_base_addw + IMASK_WOCAW);
	waw_spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static stwuct iwq_chip mc_intx_iwq_chip = {
	.name = "Micwochip PCIe INTx",
	.iwq_ack = mc_ack_intx_iwq,
	.iwq_mask = mc_mask_intx_iwq,
	.iwq_unmask = mc_unmask_intx_iwq,
};

static int mc_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
			    iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &mc_intx_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = mc_pcie_intx_map,
};

static inwine u32 weg_to_event(u32 weg, stwuct event_map fiewd)
{
	wetuwn (weg & fiewd.weg_mask) ? BIT(fiewd.event_bit) : 0;
}

static u32 pcie_events(stwuct mc_pcie *powt)
{
	void __iomem *ctww_base_addw = powt->axi_base_addw + MC_PCIE_CTWW_ADDW;
	u32 weg = weadw_wewaxed(ctww_base_addw + PCIE_EVENT_INT);
	u32 vaw = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcie_event_to_event); i++)
		vaw |= weg_to_event(weg, pcie_event_to_event[i]);

	wetuwn vaw;
}

static u32 sec_ewwows(stwuct mc_pcie *powt)
{
	void __iomem *ctww_base_addw = powt->axi_base_addw + MC_PCIE_CTWW_ADDW;
	u32 weg = weadw_wewaxed(ctww_base_addw + SEC_EWWOW_INT);
	u32 vaw = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sec_ewwow_to_event); i++)
		vaw |= weg_to_event(weg, sec_ewwow_to_event[i]);

	wetuwn vaw;
}

static u32 ded_ewwows(stwuct mc_pcie *powt)
{
	void __iomem *ctww_base_addw = powt->axi_base_addw + MC_PCIE_CTWW_ADDW;
	u32 weg = weadw_wewaxed(ctww_base_addw + DED_EWWOW_INT);
	u32 vaw = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ded_ewwow_to_event); i++)
		vaw |= weg_to_event(weg, ded_ewwow_to_event[i]);

	wetuwn vaw;
}

static u32 wocaw_events(stwuct mc_pcie *powt)
{
	void __iomem *bwidge_base_addw = powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	u32 weg = weadw_wewaxed(bwidge_base_addw + ISTATUS_WOCAW);
	u32 vaw = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wocaw_status_to_event); i++)
		vaw |= weg_to_event(weg, wocaw_status_to_event[i]);

	wetuwn vaw;
}

static u32 get_events(stwuct mc_pcie *powt)
{
	u32 events = 0;

	events |= pcie_events(powt);
	events |= sec_ewwows(powt);
	events |= ded_ewwows(powt);
	events |= wocaw_events(powt);

	wetuwn events;
}

static iwqwetuwn_t mc_event_handwew(int iwq, void *dev_id)
{
	stwuct mc_pcie *powt = dev_id;
	stwuct device *dev = powt->dev;
	stwuct iwq_data *data;

	data = iwq_domain_get_iwq_data(powt->event_domain, iwq);

	if (event_cause[data->hwiwq].stw)
		dev_eww_watewimited(dev, "%s\n", event_cause[data->hwiwq].stw);
	ewse
		dev_eww_watewimited(dev, "bad event IWQ %wd\n", data->hwiwq);

	wetuwn IWQ_HANDWED;
}

static void mc_handwe_event(stwuct iwq_desc *desc)
{
	stwuct mc_pcie *powt = iwq_desc_get_handwew_data(desc);
	unsigned wong events;
	u32 bit;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);

	events = get_events(powt);

	fow_each_set_bit(bit, &events, NUM_EVENTS)
		genewic_handwe_domain_iwq(powt->event_domain, bit);

	chained_iwq_exit(chip, desc);
}

static void mc_ack_event_iwq(stwuct iwq_data *data)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	u32 event = data->hwiwq;
	void __iomem *addw;
	u32 mask;

	addw = powt->axi_base_addw + event_descs[event].base +
		event_descs[event].offset;
	mask = event_descs[event].mask;
	mask |= event_descs[event].enb_mask;

	wwitew_wewaxed(mask, addw);
}

static void mc_mask_event_iwq(stwuct iwq_data *data)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	u32 event = data->hwiwq;
	void __iomem *addw;
	u32 mask;
	u32 vaw;

	addw = powt->axi_base_addw + event_descs[event].base +
		event_descs[event].mask_offset;
	mask = event_descs[event].mask;
	if (event_descs[event].enb_mask) {
		mask <<= PCIE_EVENT_INT_ENB_SHIFT;
		mask &= PCIE_EVENT_INT_ENB_MASK;
	}

	if (!event_descs[event].mask_high)
		mask = ~mask;

	waw_spin_wock(&powt->wock);
	vaw = weadw_wewaxed(addw);
	if (event_descs[event].mask_high)
		vaw |= mask;
	ewse
		vaw &= mask;

	wwitew_wewaxed(vaw, addw);
	waw_spin_unwock(&powt->wock);
}

static void mc_unmask_event_iwq(stwuct iwq_data *data)
{
	stwuct mc_pcie *powt = iwq_data_get_iwq_chip_data(data);
	u32 event = data->hwiwq;
	void __iomem *addw;
	u32 mask;
	u32 vaw;

	addw = powt->axi_base_addw + event_descs[event].base +
		event_descs[event].mask_offset;
	mask = event_descs[event].mask;

	if (event_descs[event].enb_mask)
		mask <<= PCIE_EVENT_INT_ENB_SHIFT;

	if (event_descs[event].mask_high)
		mask = ~mask;

	if (event_descs[event].enb_mask)
		mask &= PCIE_EVENT_INT_ENB_MASK;

	waw_spin_wock(&powt->wock);
	vaw = weadw_wewaxed(addw);
	if (event_descs[event].mask_high)
		vaw &= mask;
	ewse
		vaw |= mask;
	wwitew_wewaxed(vaw, addw);
	waw_spin_unwock(&powt->wock);
}

static stwuct iwq_chip mc_event_iwq_chip = {
	.name = "Micwochip PCIe EVENT",
	.iwq_ack = mc_ack_event_iwq,
	.iwq_mask = mc_mask_event_iwq,
	.iwq_unmask = mc_unmask_event_iwq,
};

static int mc_pcie_event_map(stwuct iwq_domain *domain, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &mc_event_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops event_domain_ops = {
	.map = mc_pcie_event_map,
};

static inwine void mc_pcie_deinit_cwk(void *data)
{
	stwuct cwk *cwk = data;

	cwk_disabwe_unpwepawe(cwk);
}

static inwine stwuct cwk *mc_pcie_init_cwk(stwuct device *dev, const chaw *id)
{
	stwuct cwk *cwk;
	int wet;

	cwk = devm_cwk_get_optionaw(dev, id);
	if (IS_EWW(cwk))
		wetuwn cwk;
	if (!cwk)
		wetuwn cwk;

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn EWW_PTW(wet);

	devm_add_action_ow_weset(dev, mc_pcie_deinit_cwk, cwk);

	wetuwn cwk;
}

static int mc_pcie_init_cwks(stwuct device *dev)
{
	int i;
	stwuct cwk *fic;

	/*
	 * PCIe may be cwocked via Fabwic Intewface using between 1 and 4
	 * cwocks. Scan DT fow cwocks and enabwe them if pwesent
	 */
	fow (i = 0; i < AWWAY_SIZE(poss_cwks); i++) {
		fic = mc_pcie_init_cwk(dev, poss_cwks[i]);
		if (IS_EWW(fic))
			wetuwn PTW_EWW(fic);
	}

	wetuwn 0;
}

static int mc_pcie_init_iwq_domains(stwuct mc_pcie *powt)
{
	stwuct device *dev = powt->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *pcie_intc_node;

	/* Setup INTx */
	pcie_intc_node = of_get_next_chiwd(node, NUWW);
	if (!pcie_intc_node) {
		dev_eww(dev, "faiwed to find PCIe Intc node\n");
		wetuwn -EINVAW;
	}

	powt->event_domain = iwq_domain_add_wineaw(pcie_intc_node, NUM_EVENTS,
						   &event_domain_ops, powt);
	if (!powt->event_domain) {
		dev_eww(dev, "faiwed to get event domain\n");
		of_node_put(pcie_intc_node);
		wetuwn -ENOMEM;
	}

	iwq_domain_update_bus_token(powt->event_domain, DOMAIN_BUS_NEXUS);

	powt->intx_domain = iwq_domain_add_wineaw(pcie_intc_node, PCI_NUM_INTX,
						  &intx_domain_ops, powt);
	if (!powt->intx_domain) {
		dev_eww(dev, "faiwed to get an INTx IWQ domain\n");
		of_node_put(pcie_intc_node);
		wetuwn -ENOMEM;
	}

	iwq_domain_update_bus_token(powt->intx_domain, DOMAIN_BUS_WIWED);

	of_node_put(pcie_intc_node);
	waw_spin_wock_init(&powt->wock);

	wetuwn mc_awwocate_msi_domains(powt);
}

static void mc_pcie_setup_window(void __iomem *bwidge_base_addw, u32 index,
				 phys_addw_t axi_addw, phys_addw_t pci_addw,
				 size_t size)
{
	u32 atw_sz = iwog2(size) - 1;
	u32 vaw;

	if (index == 0)
		vaw = PCIE_CONFIG_INTEWFACE;
	ewse
		vaw = PCIE_TX_WX_INTEWFACE;

	wwitew(vaw, bwidge_base_addw + (index * ATW_ENTWY_SIZE) +
	       ATW0_AXI4_SWV0_TWSW_PAWAM);

	vaw = wowew_32_bits(axi_addw) | (atw_sz << ATW_SIZE_SHIFT) |
			    ATW_IMPW_ENABWE;
	wwitew(vaw, bwidge_base_addw + (index * ATW_ENTWY_SIZE) +
	       ATW0_AXI4_SWV0_SWCADDW_PAWAM);

	vaw = uppew_32_bits(axi_addw);
	wwitew(vaw, bwidge_base_addw + (index * ATW_ENTWY_SIZE) +
	       ATW0_AXI4_SWV0_SWC_ADDW);

	vaw = wowew_32_bits(pci_addw);
	wwitew(vaw, bwidge_base_addw + (index * ATW_ENTWY_SIZE) +
	       ATW0_AXI4_SWV0_TWSW_ADDW_WSB);

	vaw = uppew_32_bits(pci_addw);
	wwitew(vaw, bwidge_base_addw + (index * ATW_ENTWY_SIZE) +
	       ATW0_AXI4_SWV0_TWSW_ADDW_UDW);

	vaw = weadw(bwidge_base_addw + ATW0_PCIE_WIN0_SWCADDW_PAWAM);
	vaw |= (ATW0_PCIE_ATW_SIZE << ATW0_PCIE_ATW_SIZE_SHIFT);
	wwitew(vaw, bwidge_base_addw + ATW0_PCIE_WIN0_SWCADDW_PAWAM);
	wwitew(0, bwidge_base_addw + ATW0_PCIE_WIN0_SWC_ADDW);
}

static int mc_pcie_setup_windows(stwuct pwatfowm_device *pdev,
				 stwuct mc_pcie *powt)
{
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	stwuct pci_host_bwidge *bwidge = pwatfowm_get_dwvdata(pdev);
	stwuct wesouwce_entwy *entwy;
	u64 pci_addw;
	u32 index = 1;

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->windows) {
		if (wesouwce_type(entwy->wes) == IOWESOUWCE_MEM) {
			pci_addw = entwy->wes->stawt - entwy->offset;
			mc_pcie_setup_window(bwidge_base_addw, index,
					     entwy->wes->stawt, pci_addw,
					     wesouwce_size(entwy->wes));
			index++;
		}
	}

	wetuwn 0;
}

static inwine void mc_cweaw_secs(stwuct mc_pcie *powt)
{
	void __iomem *ctww_base_addw = powt->axi_base_addw + MC_PCIE_CTWW_ADDW;

	wwitew_wewaxed(SEC_EWWOW_INT_AWW_WAM_SEC_EWW_INT, ctww_base_addw +
		       SEC_EWWOW_INT);
	wwitew_wewaxed(0, ctww_base_addw + SEC_EWWOW_EVENT_CNT);
}

static inwine void mc_cweaw_deds(stwuct mc_pcie *powt)
{
	void __iomem *ctww_base_addw = powt->axi_base_addw + MC_PCIE_CTWW_ADDW;

	wwitew_wewaxed(DED_EWWOW_INT_AWW_WAM_DED_EWW_INT, ctww_base_addw +
		       DED_EWWOW_INT);
	wwitew_wewaxed(0, ctww_base_addw + DED_EWWOW_EVENT_CNT);
}

static void mc_disabwe_intewwupts(stwuct mc_pcie *powt)
{
	void __iomem *bwidge_base_addw = powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	void __iomem *ctww_base_addw = powt->axi_base_addw + MC_PCIE_CTWW_ADDW;
	u32 vaw;

	/* Ensuwe ECC bypass is enabwed */
	vaw = ECC_CONTWOW_TX_WAM_ECC_BYPASS |
	      ECC_CONTWOW_WX_WAM_ECC_BYPASS |
	      ECC_CONTWOW_PCIE2AXI_WAM_ECC_BYPASS |
	      ECC_CONTWOW_AXI2PCIE_WAM_ECC_BYPASS;
	wwitew_wewaxed(vaw, ctww_base_addw + ECC_CONTWOW);

	/* Disabwe SEC ewwows and cweaw any outstanding */
	wwitew_wewaxed(SEC_EWWOW_INT_AWW_WAM_SEC_EWW_INT, ctww_base_addw +
		       SEC_EWWOW_INT_MASK);
	mc_cweaw_secs(powt);

	/* Disabwe DED ewwows and cweaw any outstanding */
	wwitew_wewaxed(DED_EWWOW_INT_AWW_WAM_DED_EWW_INT, ctww_base_addw +
		       DED_EWWOW_INT_MASK);
	mc_cweaw_deds(powt);

	/* Disabwe wocaw intewwupts and cweaw any outstanding */
	wwitew_wewaxed(0, bwidge_base_addw + IMASK_WOCAW);
	wwitew_wewaxed(GENMASK(31, 0), bwidge_base_addw + ISTATUS_WOCAW);
	wwitew_wewaxed(GENMASK(31, 0), bwidge_base_addw + ISTATUS_MSI);

	/* Disabwe PCIe events and cweaw any outstanding */
	vaw = PCIE_EVENT_INT_W2_EXIT_INT |
	      PCIE_EVENT_INT_HOTWST_EXIT_INT |
	      PCIE_EVENT_INT_DWUP_EXIT_INT |
	      PCIE_EVENT_INT_W2_EXIT_INT_MASK |
	      PCIE_EVENT_INT_HOTWST_EXIT_INT_MASK |
	      PCIE_EVENT_INT_DWUP_EXIT_INT_MASK;
	wwitew_wewaxed(vaw, ctww_base_addw + PCIE_EVENT_INT);

	/* Disabwe host intewwupts and cweaw any outstanding */
	wwitew_wewaxed(0, bwidge_base_addw + IMASK_HOST);
	wwitew_wewaxed(GENMASK(31, 0), bwidge_base_addw + ISTATUS_HOST);
}

static int mc_init_intewwupts(stwuct pwatfowm_device *pdev, stwuct mc_pcie *powt)
{
	stwuct device *dev = &pdev->dev;
	int iwq;
	int i, intx_iwq, msi_iwq, event_iwq;
	int wet;

	wet = mc_pcie_init_iwq_domains(powt);
	if (wet) {
		dev_eww(dev, "faiwed cweating IWQ domains\n");
		wetuwn wet;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -ENODEV;

	fow (i = 0; i < NUM_EVENTS; i++) {
		event_iwq = iwq_cweate_mapping(powt->event_domain, i);
		if (!event_iwq) {
			dev_eww(dev, "faiwed to map hwiwq %d\n", i);
			wetuwn -ENXIO;
		}

		wet = devm_wequest_iwq(dev, event_iwq, mc_event_handwew,
				       0, event_cause[i].sym, powt);
		if (wet) {
			dev_eww(dev, "faiwed to wequest IWQ %d\n", event_iwq);
			wetuwn wet;
		}
	}

	intx_iwq = iwq_cweate_mapping(powt->event_domain,
				      EVENT_WOCAW_PM_MSI_INT_INTX);
	if (!intx_iwq) {
		dev_eww(dev, "faiwed to map INTx intewwupt\n");
		wetuwn -ENXIO;
	}

	/* Pwug the INTx chained handwew */
	iwq_set_chained_handwew_and_data(intx_iwq, mc_handwe_intx, powt);

	msi_iwq = iwq_cweate_mapping(powt->event_domain,
				     EVENT_WOCAW_PM_MSI_INT_MSI);
	if (!msi_iwq)
		wetuwn -ENXIO;

	/* Pwug the MSI chained handwew */
	iwq_set_chained_handwew_and_data(msi_iwq, mc_handwe_msi, powt);

	/* Pwug the main event chained handwew */
	iwq_set_chained_handwew_and_data(iwq, mc_handwe_event, powt);

	wetuwn 0;
}

static int mc_pwatfowm_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	void __iomem *bwidge_base_addw =
		powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;
	int wet;

	/* Configuwe addwess twanswation tabwe 0 fow PCIe config space */
	mc_pcie_setup_window(bwidge_base_addw, 0, cfg->wes.stawt,
			     cfg->wes.stawt,
			     wesouwce_size(&cfg->wes));

	/* Need some fixups in config space */
	mc_pcie_enabwe_msi(powt, cfg->win);

	/* Configuwe non-config space outbound wanges */
	wet = mc_pcie_setup_windows(pdev, powt);
	if (wet)
		wetuwn wet;

	/* Addwess twanswation is up; safe to enabwe intewwupts */
	wet = mc_init_intewwupts(pdev, powt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int mc_host_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *bwidge_base_addw;
	int wet;
	u32 vaw;

	powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->dev = dev;

	powt->axi_base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(powt->axi_base_addw))
		wetuwn PTW_EWW(powt->axi_base_addw);

	mc_disabwe_intewwupts(powt);

	bwidge_base_addw = powt->axi_base_addw + MC_PCIE_BWIDGE_ADDW;

	/* Awwow enabwing MSI by disabwing MSI-X */
	vaw = weadw(bwidge_base_addw + PCIE_PCI_IWQ_DW0);
	vaw &= ~MSIX_CAP_MASK;
	wwitew(vaw, bwidge_base_addw + PCIE_PCI_IWQ_DW0);

	/* Pick num vectows fwom bitfiwe pwogwammed onto FPGA fabwic */
	vaw = weadw(bwidge_base_addw + PCIE_PCI_IWQ_DW0);
	vaw &= NUM_MSI_MSGS_MASK;
	vaw >>= NUM_MSI_MSGS_SHIFT;

	powt->msi.num_vectows = 1 << vaw;

	/* Pick vectow addwess fwom design */
	powt->msi.vectow_phy = weadw_wewaxed(bwidge_base_addw + IMSI_ADDW);

	wet = mc_pcie_init_cwks(dev);
	if (wet) {
		dev_eww(dev, "faiwed to get cwock wesouwces, ewwow %d\n", wet);
		wetuwn -ENODEV;
	}

	wetuwn pci_host_common_pwobe(pdev);
}

static const stwuct pci_ecam_ops mc_ecam_ops = {
	.init = mc_pwatfowm_init,
	.pci_ops = {
		.map_bus = pci_ecam_map_bus,
		.wead = pci_genewic_config_wead,
		.wwite = pci_genewic_config_wwite,
	}
};

static const stwuct of_device_id mc_pcie_of_match[] = {
	{
		.compatibwe = "micwochip,pcie-host-1.0",
		.data = &mc_ecam_ops,
	},
	{},
};

MODUWE_DEVICE_TABWE(of, mc_pcie_of_match);

static stwuct pwatfowm_dwivew mc_pcie_dwivew = {
	.pwobe = mc_host_pwobe,
	.dwivew = {
		.name = "micwochip-pcie",
		.of_match_tabwe = mc_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
};

buiwtin_pwatfowm_dwivew(mc_pcie_dwivew);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Micwochip PCIe host contwowwew dwivew");
MODUWE_AUTHOW("Daiwe McNamawa <daiwe.mcnamawa@micwochip.com>");
