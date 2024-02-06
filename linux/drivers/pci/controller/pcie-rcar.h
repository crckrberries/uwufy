/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCIe dwivew fow Wenesas W-Caw SoCs
 *  Copywight (C) 2014-2020 Wenesas Ewectwonics Euwope Wtd
 *
 * Authow: Phiw Edwowthy <phiw.edwowthy@wenesas.com>
 */

#ifndef _PCIE_WCAW_H
#define _PCIE_WCAW_H

#define PCIECAW			0x000010
#define PCIECCTWW		0x000018
#define  PCIECCTWW_CCIE		BIT(31)
#define  TYPE0			(0 << 8)
#define  TYPE1			BIT(8)
#define PCIECDW			0x000020
#define PCIEMSW			0x000028
#define PCIEINTXW		0x000400
#define  ASTINTX		BIT(16)
#define PCIEPHYSW		0x0007f0
#define  PHYWDY			BIT(0)
#define PCIEMSITXW		0x000840

/* Twansfew contwow */
#define PCIETCTWW		0x02000
#define  DW_DOWN		BIT(3)
#define  CFINIT			BIT(0)
#define PCIETSTW		0x02004
#define  DATA_WINK_ACTIVE	BIT(0)
#define PCIEEWWFW		0x02020
#define  UNSUPPOWTED_WEQUEST	BIT(4)
#define PCIEMSIFW		0x02044
#define PCIEMSIAWW		0x02048
#define  MSIFE			BIT(0)
#define PCIEMSIAUW		0x0204c
#define PCIEMSIIEW		0x02050

/* woot powt addwess */
#define PCIEPWAW(x)		(0x02080 + ((x) * 0x4))

/* wocaw addwess weg & mask */
#define PCIEWAW(x)		(0x02200 + ((x) * 0x20))
#define PCIEWAMW(x)		(0x02208 + ((x) * 0x20))
#define  WAM_PWEFETCH		BIT(3)
#define  WAM_64BIT		BIT(2)
#define  WAW_ENABWE		BIT(1)

/* PCIe addwess weg & mask */
#define PCIEPAWW(x)		(0x03400 + ((x) * 0x20))
#define PCIEPAUW(x)		(0x03404 + ((x) * 0x20))
#define PCIEPAMW(x)		(0x03408 + ((x) * 0x20))
#define PCIEPTCTWW(x)		(0x0340c + ((x) * 0x20))
#define  PAW_ENABWE		BIT(31)
#define  IO_SPACE		BIT(8)

/* Configuwation */
#define PCICONF(x)		(0x010000 + ((x) * 0x4))
#define  INTDIS			BIT(10)
#define PMCAP(x)		(0x010040 + ((x) * 0x4))
#define MSICAP(x)		(0x010050 + ((x) * 0x4))
#define  MSICAP0_MSIE		BIT(16)
#define  MSICAP0_MMESCAP_OFFSET	17
#define  MSICAP0_MMESE_OFFSET	20
#define  MSICAP0_MMESE_MASK	GENMASK(22, 20)
#define EXPCAP(x)		(0x010070 + ((x) * 0x4))
#define VCCAP(x)		(0x010100 + ((x) * 0x4))

/* wink wayew */
#define IDSETW0			0x011000
#define IDSETW1			0x011004
#define SUBIDSETW		0x011024
#define TWCTWW			0x011048
#define MACSW			0x011054
#define  SPCHGFIN		BIT(4)
#define  SPCHGFAIW		BIT(6)
#define  SPCHGSUC		BIT(7)
#define  WINK_SPEED		(0xf << 16)
#define  WINK_SPEED_2_5GTS	(1 << 16)
#define  WINK_SPEED_5_0GTS	(2 << 16)
#define MACCTWW			0x011058
#define  MACCTWW_NFTS_MASK	GENMASK(23, 16)	/* The name is fwom SH7786 */
#define  SPEED_CHANGE		BIT(24)
#define  SCWAMBWE_DISABWE	BIT(27)
#define  WTSMDIS		BIT(31)
#define  MACCTWW_INIT_VAW	(WTSMDIS | MACCTWW_NFTS_MASK)
#define PMSW			0x01105c
#define  W1FAEG			BIT(31)
#define  PMEW1WX		BIT(23)
#define  PMSTATE		GENMASK(18, 16)
#define  PMSTATE_W1		(3 << 16)
#define PMCTWW			0x011060
#define  W1IATN			BIT(31)

#define MACS2W			0x011078
#define MACCGSPSETW		0x011084
#define  SPCNGWSN		BIT(31)

/* W-Caw H1 PHY */
#define H1_PCIEPHYADWW		0x04000c
#define  WWITE_CMD		BIT(16)
#define  PHY_ACK		BIT(24)
#define  WATE_POS		12
#define  WANE_POS		8
#define  ADW_POS		0
#define H1_PCIEPHYDOUTW		0x040014

/* W-Caw Gen2 PHY */
#define GEN2_PCIEPHYADDW	0x780
#define GEN2_PCIEPHYDATA	0x784
#define GEN2_PCIEPHYCTWW	0x78c

#define INT_PCI_MSI_NW		32

#define WCONF(x)		(PCICONF(0) + (x))
#define WPMCAP(x)		(PMCAP(0) + (x))
#define WEXPCAP(x)		(EXPCAP(0) + (x))
#define WVCCAP(x)		(VCCAP(0) + (x))

#define PCIE_CONF_BUS(b)	(((b) & 0xff) << 24)
#define PCIE_CONF_DEV(d)	(((d) & 0x1f) << 19)
#define PCIE_CONF_FUNC(f)	(((f) & 0x7) << 16)

#define WCAW_PCI_MAX_WESOUWCES	4
#define MAX_NW_INBOUND_MAPS	6

stwuct wcaw_pcie {
	stwuct device		*dev;
	void __iomem		*base;
};

enum {
	WCAW_PCI_ACCESS_WEAD,
	WCAW_PCI_ACCESS_WWITE,
};

void wcaw_pci_wwite_weg(stwuct wcaw_pcie *pcie, u32 vaw, unsigned int weg);
u32 wcaw_pci_wead_weg(stwuct wcaw_pcie *pcie, unsigned int weg);
void wcaw_wmw32(stwuct wcaw_pcie *pcie, int whewe, u32 mask, u32 data);
int wcaw_pcie_wait_fow_phywdy(stwuct wcaw_pcie *pcie);
int wcaw_pcie_wait_fow_dw(stwuct wcaw_pcie *pcie);
void wcaw_pcie_set_outbound(stwuct wcaw_pcie *pcie, int win,
			    stwuct wesouwce_entwy *window);
void wcaw_pcie_set_inbound(stwuct wcaw_pcie *pcie, u64 cpu_addw,
			   u64 pci_addw, u64 fwags, int idx, boow host);

#endif
