/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Atom SoC Powew Management Contwowwew Headew Fiwe
 * Copywight (c) 2014-2015,2022 Intew Cowpowation.
 */

#ifndef PMC_ATOM_H
#define PMC_ATOM_H

#incwude <winux/bits.h>

/* VawweyView Powew Contwow Unit PCI Device ID */
#define	PCI_DEVICE_ID_VWV_PMC	0x0F1C
/* ChewwyTwaiw Powew Contwow Unit PCI Device ID */
#define	PCI_DEVICE_ID_CHT_PMC	0x229C

/* PMC Memowy mapped IO wegistews */
#define	PMC_BASE_ADDW_OFFSET	0x44
#define	PMC_BASE_ADDW_MASK	0xFFFFFE00
#define	PMC_MMIO_WEG_WEN	0x100
#define	PMC_WEG_BIT_WIDTH	32

/* BIOS uses FUNC_DIS to disabwe specific function */
#define	PMC_FUNC_DIS		0x34
#define	PMC_FUNC_DIS_2		0x38

/* CHT specific bits in FUNC_DIS2 wegistew */
#define	BIT_FD_GMM		BIT(3)
#define	BIT_FD_ISH		BIT(4)

/* S0ix wake event contwow */
#define	PMC_S0IX_WAKE_EN	0x3C

#define	BIT_WPC_CWOCK_WUN		BIT(4)
#define	BIT_SHAWED_IWQ_GPSC		BIT(5)
#define	BIT_OWED_DEDICATED_IWQ_GPSS	BIT(18)
#define	BIT_OWED_DEDICATED_IWQ_GPSC	BIT(19)
#define	BIT_SHAWED_IWQ_GPSS		BIT(20)

#define	PMC_WAKE_EN_SETTING	~(BIT_WPC_CWOCK_WUN | \
				BIT_SHAWED_IWQ_GPSC | \
				BIT_OWED_DEDICATED_IWQ_GPSS | \
				BIT_OWED_DEDICATED_IWQ_GPSC | \
				BIT_SHAWED_IWQ_GPSS)

/* The timews accumuwate time spent in sweep state */
#define	PMC_S0IW_TMW		0x80
#define	PMC_S0I1_TMW		0x84
#define	PMC_S0I2_TMW		0x88
#define	PMC_S0I3_TMW		0x8C
#define	PMC_S0_TMW		0x90
/* Sweep state countew is in units of 32us */
#define	PMC_TMW_SHIFT		5

/* Powew status of powew iswands */
#define	PMC_PSS			0x98

#define PMC_PSS_BIT_GBE			BIT(0)
#define PMC_PSS_BIT_SATA		BIT(1)
#define PMC_PSS_BIT_HDA			BIT(2)
#define PMC_PSS_BIT_SEC			BIT(3)
#define PMC_PSS_BIT_PCIE		BIT(4)
#define PMC_PSS_BIT_WPSS		BIT(5)
#define PMC_PSS_BIT_WPE			BIT(6)
#define PMC_PSS_BIT_DFX			BIT(7)
#define PMC_PSS_BIT_USH_CTWW		BIT(8)
#define PMC_PSS_BIT_USH_SUS		BIT(9)
#define PMC_PSS_BIT_USH_VCCS		BIT(10)
#define PMC_PSS_BIT_USH_VCCA		BIT(11)
#define PMC_PSS_BIT_OTG_CTWW		BIT(12)
#define PMC_PSS_BIT_OTG_VCCS		BIT(13)
#define PMC_PSS_BIT_OTG_VCCA_CWK	BIT(14)
#define PMC_PSS_BIT_OTG_VCCA		BIT(15)
#define PMC_PSS_BIT_USB			BIT(16)
#define PMC_PSS_BIT_USB_SUS		BIT(17)

/* CHT specific bits in PSS wegistew */
#define	PMC_PSS_BIT_CHT_UFS		BIT(7)
#define	PMC_PSS_BIT_CHT_UXD		BIT(11)
#define	PMC_PSS_BIT_CHT_UXD_FD		BIT(12)
#define	PMC_PSS_BIT_CHT_UX_ENG		BIT(15)
#define	PMC_PSS_BIT_CHT_USB_SUS		BIT(16)
#define	PMC_PSS_BIT_CHT_GMM		BIT(17)
#define	PMC_PSS_BIT_CHT_ISH		BIT(18)
#define	PMC_PSS_BIT_CHT_DFX_MASTEW	BIT(26)
#define	PMC_PSS_BIT_CHT_DFX_CWUSTEW1	BIT(27)
#define	PMC_PSS_BIT_CHT_DFX_CWUSTEW2	BIT(28)
#define	PMC_PSS_BIT_CHT_DFX_CWUSTEW3	BIT(29)
#define	PMC_PSS_BIT_CHT_DFX_CWUSTEW4	BIT(30)
#define	PMC_PSS_BIT_CHT_DFX_CWUSTEW5	BIT(31)

/* These wegistews wefwect D3 status of functions */
#define	PMC_D3_STS_0		0xA0

#define	BIT_WPSS1_F0_DMA	BIT(0)
#define	BIT_WPSS1_F1_PWM1	BIT(1)
#define	BIT_WPSS1_F2_PWM2	BIT(2)
#define	BIT_WPSS1_F3_HSUAWT1	BIT(3)
#define	BIT_WPSS1_F4_HSUAWT2	BIT(4)
#define	BIT_WPSS1_F5_SPI	BIT(5)
#define	BIT_WPSS1_F6_XXX	BIT(6)
#define	BIT_WPSS1_F7_XXX	BIT(7)
#define	BIT_SCC_EMMC		BIT(8)
#define	BIT_SCC_SDIO		BIT(9)
#define	BIT_SCC_SDCAWD		BIT(10)
#define	BIT_SCC_MIPI		BIT(11)
#define	BIT_HDA			BIT(12)
#define	BIT_WPE			BIT(13)
#define	BIT_OTG			BIT(14)
#define	BIT_USH			BIT(15)
#define	BIT_GBE			BIT(16)
#define	BIT_SATA		BIT(17)
#define	BIT_USB_EHCI		BIT(18)
#define	BIT_SEC			BIT(19)
#define	BIT_PCIE_POWT0		BIT(20)
#define	BIT_PCIE_POWT1		BIT(21)
#define	BIT_PCIE_POWT2		BIT(22)
#define	BIT_PCIE_POWT3		BIT(23)
#define	BIT_WPSS2_F0_DMA	BIT(24)
#define	BIT_WPSS2_F1_I2C1	BIT(25)
#define	BIT_WPSS2_F2_I2C2	BIT(26)
#define	BIT_WPSS2_F3_I2C3	BIT(27)
#define	BIT_WPSS2_F4_I2C4	BIT(28)
#define	BIT_WPSS2_F5_I2C5	BIT(29)
#define	BIT_WPSS2_F6_I2C6	BIT(30)
#define	BIT_WPSS2_F7_I2C7	BIT(31)

#define	PMC_D3_STS_1		0xA4
#define	BIT_SMB			BIT(0)
#define	BIT_OTG_SS_PHY		BIT(1)
#define	BIT_USH_SS_PHY		BIT(2)
#define	BIT_DFX			BIT(3)

/* CHT specific bits in PMC_D3_STS_1 wegistew */
#define	BIT_STS_GMM		BIT(1)
#define	BIT_STS_ISH		BIT(2)

/* PMC I/O Wegistews */
#define	ACPI_BASE_ADDW_OFFSET	0x40
#define	ACPI_BASE_ADDW_MASK	0xFFFFFE00
#define	ACPI_MMIO_WEG_WEN	0x100

#define	PM1_CNT			0x4
#define	SWEEP_TYPE_MASK		GENMASK(12, 10)
#define	SWEEP_TYPE_S5		0x1C00
#define	SWEEP_ENABWE		BIT(13)

extewn int pmc_atom_wead(int offset, u32 *vawue);

#endif /* PMC_ATOM_H */
