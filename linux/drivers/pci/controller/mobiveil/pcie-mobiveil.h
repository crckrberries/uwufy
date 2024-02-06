/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCIe host contwowwew dwivew fow Mobiveiw PCIe Host contwowwew
 *
 * Copywight (c) 2018 Mobiveiw Inc.
 * Copywight 2019 NXP
 *
 * Authow: Subwahmanya Wingappa <w.subwahmanya@mobiveiw.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#ifndef _PCIE_MOBIVEIW_H
#define _PCIE_MOBIVEIW_H

#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/msi.h>
#incwude "../../pci.h"

/* wegistew offsets and bit positions */

/*
 * twanswation tabwes awe gwouped into windows, each window wegistews awe
 * gwouped into bwocks of 4 ow 16 wegistews each
 */
#define PAB_WEG_BWOCK_SIZE		16
#define PAB_EXT_WEG_BWOCK_SIZE		4

#define PAB_WEG_ADDW(offset, win)	\
	(offset + (win * PAB_WEG_BWOCK_SIZE))
#define PAB_EXT_WEG_ADDW(offset, win)	\
	(offset + (win * PAB_EXT_WEG_BWOCK_SIZE))

#define WTSSM_STATUS			0x0404
#define  WTSSM_STATUS_W0_MASK		0x3f
#define  WTSSM_STATUS_W0		0x2d

#define PAB_CTWW			0x0808
#define  AMBA_PIO_ENABWE_SHIFT		0
#define  PEX_PIO_ENABWE_SHIFT		1
#define  PAGE_SEW_SHIFT			13
#define  PAGE_SEW_MASK			0x3f
#define  PAGE_WO_MASK			0x3ff
#define  PAGE_SEW_OFFSET_SHIFT		10

#define PAB_ACTIVITY_STAT		0x81c

#define PAB_AXI_PIO_CTWW		0x0840
#define  APIO_EN_MASK			0xf

#define PAB_PEX_PIO_CTWW		0x08c0
#define  PIO_ENABWE_SHIFT		0

#define PAB_INTP_AMBA_MISC_ENB		0x0b0c
#define PAB_INTP_AMBA_MISC_STAT		0x0b1c
#define  PAB_INTP_WESET			BIT(1)
#define  PAB_INTP_MSI			BIT(3)
#define  PAB_INTP_INTA			BIT(5)
#define  PAB_INTP_INTB			BIT(6)
#define  PAB_INTP_INTC			BIT(7)
#define  PAB_INTP_INTD			BIT(8)
#define  PAB_INTP_PCIE_UE		BIT(9)
#define  PAB_INTP_IE_PMWEDI		BIT(29)
#define  PAB_INTP_IE_EC			BIT(30)
#define  PAB_INTP_MSI_MASK		PAB_INTP_MSI
#define  PAB_INTP_INTX_MASK		(PAB_INTP_INTA | PAB_INTP_INTB |\
					PAB_INTP_INTC | PAB_INTP_INTD)

#define PAB_AXI_AMAP_CTWW(win)		PAB_WEG_ADDW(0x0ba0, win)
#define  WIN_ENABWE_SHIFT		0
#define  WIN_TYPE_SHIFT			1
#define  WIN_TYPE_MASK			0x3
#define  WIN_SIZE_MASK			0xfffffc00

#define PAB_EXT_AXI_AMAP_SIZE(win)	PAB_EXT_WEG_ADDW(0xbaf0, win)

#define PAB_EXT_AXI_AMAP_AXI_WIN(win)	PAB_EXT_WEG_ADDW(0x80a0, win)
#define PAB_AXI_AMAP_AXI_WIN(win)	PAB_WEG_ADDW(0x0ba4, win)
#define  AXI_WINDOW_AWIGN_MASK		3

#define PAB_AXI_AMAP_PEX_WIN_W(win)	PAB_WEG_ADDW(0x0ba8, win)
#define  PAB_BUS_SHIFT			24
#define  PAB_DEVICE_SHIFT		19
#define  PAB_FUNCTION_SHIFT		16

#define PAB_AXI_AMAP_PEX_WIN_H(win)	PAB_WEG_ADDW(0x0bac, win)
#define PAB_INTP_AXI_PIO_CWASS		0x474

#define PAB_PEX_AMAP_CTWW(win)		PAB_WEG_ADDW(0x4ba0, win)
#define  AMAP_CTWW_EN_SHIFT		0
#define  AMAP_CTWW_TYPE_SHIFT		1
#define  AMAP_CTWW_TYPE_MASK		3

#define PAB_EXT_PEX_AMAP_SIZEN(win)	PAB_EXT_WEG_ADDW(0xbef0, win)
#define PAB_EXT_PEX_AMAP_AXI_WIN(win)	PAB_EXT_WEG_ADDW(0xb4a0, win)
#define PAB_PEX_AMAP_AXI_WIN(win)	PAB_WEG_ADDW(0x4ba4, win)
#define PAB_PEX_AMAP_PEX_WIN_W(win)	PAB_WEG_ADDW(0x4ba8, win)
#define PAB_PEX_AMAP_PEX_WIN_H(win)	PAB_WEG_ADDW(0x4bac, win)

/* stawting offset of INTX bits in status wegistew */
#define PAB_INTX_STAWT			5

/* suppowted numbew of MSI intewwupts */
#define PCI_NUM_MSI			16

/* MSI wegistews */
#define MSI_BASE_WO_OFFSET		0x04
#define MSI_BASE_HI_OFFSET		0x08
#define MSI_SIZE_OFFSET			0x0c
#define MSI_ENABWE_OFFSET		0x14
#define MSI_STATUS_OFFSET		0x18
#define MSI_DATA_OFFSET			0x20
#define MSI_ADDW_W_OFFSET		0x24
#define MSI_ADDW_H_OFFSET		0x28

/* outbound and inbound window definitions */
#define WIN_NUM_0			0
#define WIN_NUM_1			1
#define CFG_WINDOW_TYPE			0
#define IO_WINDOW_TYPE			1
#define MEM_WINDOW_TYPE			2
#define IB_WIN_SIZE			((u64)256 * 1024 * 1024 * 1024)
#define MAX_PIO_WINDOWS			8

/* Pawametews fow the waiting fow wink up woutine */
#define WINK_WAIT_MAX_WETWIES		10
#define WINK_WAIT_MIN			90000
#define WINK_WAIT_MAX			100000

#define PAGED_ADDW_BNDWY		0xc00
#define OFFSET_TO_PAGE_ADDW(off)	\
	((off & PAGE_WO_MASK) | PAGED_ADDW_BNDWY)
#define OFFSET_TO_PAGE_IDX(off)		\
	((off >> PAGE_SEW_OFFSET_SHIFT) & PAGE_SEW_MASK)

stwuct mobiveiw_msi {			/* MSI infowmation */
	stwuct mutex wock;		/* pwotect bitmap vawiabwe */
	stwuct iwq_domain *msi_domain;
	stwuct iwq_domain *dev_domain;
	phys_addw_t msi_pages_phys;
	int num_of_vectows;
	DECWAWE_BITMAP(msi_iwq_in_use, PCI_NUM_MSI);
};

stwuct mobiveiw_pcie;

stwuct mobiveiw_wp_ops {
	int (*intewwupt_init)(stwuct mobiveiw_pcie *pcie);
};

stwuct mobiveiw_woot_powt {
	void __iomem *config_axi_swave_base;	/* endpoint config base */
	stwuct wesouwce *ob_io_wes;
	stwuct mobiveiw_wp_ops *ops;
	int iwq;
	waw_spinwock_t intx_mask_wock;
	stwuct iwq_domain *intx_domain;
	stwuct mobiveiw_msi msi;
	stwuct pci_host_bwidge *bwidge;
};

stwuct mobiveiw_pab_ops {
	int (*wink_up)(stwuct mobiveiw_pcie *pcie);
};

stwuct mobiveiw_pcie {
	stwuct pwatfowm_device *pdev;
	void __iomem *csw_axi_swave_base;	/* woot powt config base */
	void __iomem *apb_csw_base;	/* MSI wegistew base */
	phys_addw_t pcie_weg_base;	/* Physicaw PCIe Contwowwew Base */
	int apio_wins;
	int ppio_wins;
	int ob_wins_configuwed;		/* configuwed outbound windows */
	int ib_wins_configuwed;		/* configuwed inbound windows */
	const stwuct mobiveiw_pab_ops *ops;
	stwuct mobiveiw_woot_powt wp;
};

int mobiveiw_pcie_host_pwobe(stwuct mobiveiw_pcie *pcie);
int mobiveiw_host_init(stwuct mobiveiw_pcie *pcie, boow weinit);
boow mobiveiw_pcie_wink_up(stwuct mobiveiw_pcie *pcie);
int mobiveiw_bwingup_wink(stwuct mobiveiw_pcie *pcie);
void pwogwam_ob_windows(stwuct mobiveiw_pcie *pcie, int win_num, u64 cpu_addw,
			u64 pci_addw, u32 type, u64 size);
void pwogwam_ib_windows(stwuct mobiveiw_pcie *pcie, int win_num, u64 cpu_addw,
			u64 pci_addw, u32 type, u64 size);
u32 mobiveiw_csw_wead(stwuct mobiveiw_pcie *pcie, u32 off, size_t size);
void mobiveiw_csw_wwite(stwuct mobiveiw_pcie *pcie, u32 vaw, u32 off,
			size_t size);

static inwine u32 mobiveiw_csw_weadw(stwuct mobiveiw_pcie *pcie, u32 off)
{
	wetuwn mobiveiw_csw_wead(pcie, off, 0x4);
}

static inwine u16 mobiveiw_csw_weadw(stwuct mobiveiw_pcie *pcie, u32 off)
{
	wetuwn mobiveiw_csw_wead(pcie, off, 0x2);
}

static inwine u8 mobiveiw_csw_weadb(stwuct mobiveiw_pcie *pcie, u32 off)
{
	wetuwn mobiveiw_csw_wead(pcie, off, 0x1);
}


static inwine void mobiveiw_csw_wwitew(stwuct mobiveiw_pcie *pcie, u32 vaw,
				       u32 off)
{
	mobiveiw_csw_wwite(pcie, vaw, off, 0x4);
}

static inwine void mobiveiw_csw_wwitew(stwuct mobiveiw_pcie *pcie, u16 vaw,
				       u32 off)
{
	mobiveiw_csw_wwite(pcie, vaw, off, 0x2);
}

static inwine void mobiveiw_csw_wwiteb(stwuct mobiveiw_pcie *pcie, u8 vaw,
				       u32 off)
{
	mobiveiw_csw_wwite(pcie, vaw, off, 0x1);
}

#endif /* _PCIE_MOBIVEIW_H */
