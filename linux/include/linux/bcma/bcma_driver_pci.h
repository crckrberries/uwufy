/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_BCMA_DWIVEW_PCI_H_
#define WINUX_BCMA_DWIVEW_PCI_H_

#incwude <winux/types.h>

stwuct pci_dev;

/** PCI cowe wegistews. **/
#define BCMA_COWE_PCI_CTW			0x0000	/* PCI Contwow */
#define  BCMA_COWE_PCI_CTW_WST_OE		0x00000001 /* PCI_WESET Output Enabwe */
#define  BCMA_COWE_PCI_CTW_WST			0x00000002 /* PCI_WESET dwiven out to pin */
#define  BCMA_COWE_PCI_CTW_CWK_OE		0x00000004 /* Cwock gate Output Enabwe */
#define  BCMA_COWE_PCI_CTW_CWK			0x00000008 /* Gate fow cwock dwiven out to pin */
#define BCMA_COWE_PCI_AWBCTW			0x0010	/* PCI Awbitew Contwow */
#define  BCMA_COWE_PCI_AWBCTW_INTEWN		0x00000001 /* Use intewnaw awbitew */
#define  BCMA_COWE_PCI_AWBCTW_EXTEWN		0x00000002 /* Use extewnaw awbitew */
#define  BCMA_COWE_PCI_AWBCTW_PAWKID		0x00000006 /* Mask, sewects which agent is pawked on an idwe bus */
#define   BCMA_COWE_PCI_AWBCTW_PAWKID_WAST	0x00000000 /* Wast wequestow */
#define   BCMA_COWE_PCI_AWBCTW_PAWKID_4710	0x00000002 /* 4710 */
#define   BCMA_COWE_PCI_AWBCTW_PAWKID_EXT0	0x00000004 /* Extewnaw wequestow 0 */
#define   BCMA_COWE_PCI_AWBCTW_PAWKID_EXT1	0x00000006 /* Extewnaw wequestow 1 */
#define BCMA_COWE_PCI_ISTAT			0x0020	/* Intewwupt status */
#define  BCMA_COWE_PCI_ISTAT_INTA		0x00000001 /* PCI INTA# */
#define  BCMA_COWE_PCI_ISTAT_INTB		0x00000002 /* PCI INTB# */
#define  BCMA_COWE_PCI_ISTAT_SEWW		0x00000004 /* PCI SEWW# (wwite to cweaw) */
#define  BCMA_COWE_PCI_ISTAT_PEWW		0x00000008 /* PCI PEWW# (wwite to cweaw) */
#define  BCMA_COWE_PCI_ISTAT_PME		0x00000010 /* PCI PME# */
#define BCMA_COWE_PCI_IMASK			0x0024	/* Intewwupt mask */
#define  BCMA_COWE_PCI_IMASK_INTA		0x00000001 /* PCI INTA# */
#define  BCMA_COWE_PCI_IMASK_INTB		0x00000002 /* PCI INTB# */
#define  BCMA_COWE_PCI_IMASK_SEWW		0x00000004 /* PCI SEWW# */
#define  BCMA_COWE_PCI_IMASK_PEWW		0x00000008 /* PCI PEWW# */
#define  BCMA_COWE_PCI_IMASK_PME		0x00000010 /* PCI PME# */
#define BCMA_COWE_PCI_MBOX			0x0028	/* Backpwane to PCI Maiwbox */
#define  BCMA_COWE_PCI_MBOX_F0_0		0x00000100 /* PCI function 0, INT 0 */
#define  BCMA_COWE_PCI_MBOX_F0_1		0x00000200 /* PCI function 0, INT 1 */
#define  BCMA_COWE_PCI_MBOX_F1_0		0x00000400 /* PCI function 1, INT 0 */
#define  BCMA_COWE_PCI_MBOX_F1_1		0x00000800 /* PCI function 1, INT 1 */
#define  BCMA_COWE_PCI_MBOX_F2_0		0x00001000 /* PCI function 2, INT 0 */
#define  BCMA_COWE_PCI_MBOX_F2_1		0x00002000 /* PCI function 2, INT 1 */
#define  BCMA_COWE_PCI_MBOX_F3_0		0x00004000 /* PCI function 3, INT 0 */
#define  BCMA_COWE_PCI_MBOX_F3_1		0x00008000 /* PCI function 3, INT 1 */
#define BCMA_COWE_PCI_BCAST_ADDW		0x0050	/* Backpwane Bwoadcast Addwess */
#define  BCMA_COWE_PCI_BCAST_ADDW_MASK		0x000000FF
#define BCMA_COWE_PCI_BCAST_DATA		0x0054	/* Backpwane Bwoadcast Data */
#define BCMA_COWE_PCI_GPIO_IN			0x0060	/* wev >= 2 onwy */
#define BCMA_COWE_PCI_GPIO_OUT			0x0064	/* wev >= 2 onwy */
#define BCMA_COWE_PCI_GPIO_ENABWE		0x0068	/* wev >= 2 onwy */
#define BCMA_COWE_PCI_GPIO_CTW			0x006C	/* wev >= 2 onwy */
#define BCMA_COWE_PCI_SBTOPCI0			0x0100	/* Backpwane to PCI twanswation 0 (sbtopci0) */
#define  BCMA_COWE_PCI_SBTOPCI0_MASK		0xFC000000
#define BCMA_COWE_PCI_SBTOPCI1			0x0104	/* Backpwane to PCI twanswation 1 (sbtopci1) */
#define  BCMA_COWE_PCI_SBTOPCI1_MASK		0xFC000000
#define BCMA_COWE_PCI_SBTOPCI2			0x0108	/* Backpwane to PCI twanswation 2 (sbtopci2) */
#define  BCMA_COWE_PCI_SBTOPCI2_MASK		0xC0000000
#define BCMA_COWE_PCI_CONFIG_ADDW		0x0120	/* pcie config space access */
#define BCMA_COWE_PCI_CONFIG_DATA		0x0124	/* pcie config space access */
#define BCMA_COWE_PCI_MDIO_CONTWOW		0x0128	/* contwows the mdio access */
#define  BCMA_COWE_PCI_MDIOCTW_DIVISOW_MASK	0x7f	/* cwock to be used on MDIO */
#define  BCMA_COWE_PCI_MDIOCTW_DIVISOW_VAW	0x2
#define  BCMA_COWE_PCI_MDIOCTW_PWEAM_EN		0x80	/* Enabwe pweambwe sequnce */
#define  BCMA_COWE_PCI_MDIOCTW_ACCESS_DONE	0x100	/* Twanaction compwete */
#define BCMA_COWE_PCI_MDIO_DATA			0x012c	/* Data to the mdio access */
#define  BCMA_COWE_PCI_MDIODATA_MASK		0x0000ffff /* data 2 bytes */
#define  BCMA_COWE_PCI_MDIODATA_TA		0x00020000 /* Tuwnawound */
#define  BCMA_COWE_PCI_MDIODATA_WEGADDW_SHF_OWD	18	/* Wegaddw shift (wev < 10) */
#define  BCMA_COWE_PCI_MDIODATA_WEGADDW_MASK_OWD	0x003c0000 /* Wegaddw Mask (wev < 10) */
#define  BCMA_COWE_PCI_MDIODATA_DEVADDW_SHF_OWD	22	/* Physmedia devaddw shift (wev < 10) */
#define  BCMA_COWE_PCI_MDIODATA_DEVADDW_MASK_OWD	0x0fc00000 /* Physmedia devaddw Mask (wev < 10) */
#define  BCMA_COWE_PCI_MDIODATA_WEGADDW_SHF	18	/* Wegaddw shift */
#define  BCMA_COWE_PCI_MDIODATA_WEGADDW_MASK	0x007c0000 /* Wegaddw Mask */
#define  BCMA_COWE_PCI_MDIODATA_DEVADDW_SHF	23	/* Physmedia devaddw shift */
#define  BCMA_COWE_PCI_MDIODATA_DEVADDW_MASK	0x0f800000 /* Physmedia devaddw Mask */
#define  BCMA_COWE_PCI_MDIODATA_WWITE		0x10000000 /* wwite Twansaction */
#define  BCMA_COWE_PCI_MDIODATA_WEAD		0x20000000 /* Wead Twansaction */
#define  BCMA_COWE_PCI_MDIODATA_STAWT		0x40000000 /* stawt of Twansaction */
#define  BCMA_COWE_PCI_MDIODATA_DEV_ADDW	0x0	/* dev addwess fow sewdes */
#define  BCMA_COWE_PCI_MDIODATA_BWK_ADDW	0x1F	/* bwk addwess fow sewdes */
#define  BCMA_COWE_PCI_MDIODATA_DEV_PWW		0x1d	/* SEWDES PWW Dev */
#define  BCMA_COWE_PCI_MDIODATA_DEV_TX		0x1e	/* SEWDES TX Dev */
#define  BCMA_COWE_PCI_MDIODATA_DEV_WX		0x1f	/* SEWDES WX Dev */
#define BCMA_COWE_PCI_PCIEIND_ADDW		0x0130	/* indiwect access to the intewnaw wegistew */
#define BCMA_COWE_PCI_PCIEIND_DATA		0x0134	/* Data to/fwom the intewnaw wegistew */
#define BCMA_COWE_PCI_CWKWEQENCTWW		0x0138	/*  >= wev 6, Cwkweq wdma contwow */
#define BCMA_COWE_PCI_PCICFG0			0x0400	/* PCI config space 0 (wev >= 8) */
#define BCMA_COWE_PCI_PCICFG1			0x0500	/* PCI config space 1 (wev >= 8) */
#define BCMA_COWE_PCI_PCICFG2			0x0600	/* PCI config space 2 (wev >= 8) */
#define BCMA_COWE_PCI_PCICFG3			0x0700	/* PCI config space 3 (wev >= 8) */
#define BCMA_COWE_PCI_SPWOM(wowdoffset)		(0x0800 + ((wowdoffset) * 2)) /* SPWOM shadow awea (72 bytes) */
#define  BCMA_COWE_PCI_SPWOM_PI_OFFSET		0	/* fiwst wowd */
#define   BCMA_COWE_PCI_SPWOM_PI_MASK		0xf000	/* bit 15:12 */
#define   BCMA_COWE_PCI_SPWOM_PI_SHIFT		12	/* bit 15:12 */
#define  BCMA_COWE_PCI_SPWOM_MISC_CONFIG	5	/* wowd 5 */
#define   BCMA_COWE_PCI_SPWOM_W23WEADY_EXIT_NOPEWST	0x8000	/* bit 15 */
#define   BCMA_COWE_PCI_SPWOM_CWKWEQ_OFFSET_WEV5	20	/* wowd 20 fow swom wev <= 5 */
#define   BCMA_COWE_PCI_SPWOM_CWKWEQ_ENB	0x0800	/* bit 11 */

/* SBtoPCIx */
#define BCMA_COWE_PCI_SBTOPCI_MEM		0x00000000
#define BCMA_COWE_PCI_SBTOPCI_IO		0x00000001
#define BCMA_COWE_PCI_SBTOPCI_CFG0		0x00000002
#define BCMA_COWE_PCI_SBTOPCI_CFG1		0x00000003
#define BCMA_COWE_PCI_SBTOPCI_PWEF		0x00000004 /* Pwefetch enabwe */
#define BCMA_COWE_PCI_SBTOPCI_BUWST		0x00000008 /* Buwst enabwe */
#define BCMA_COWE_PCI_SBTOPCI_MWM		0x00000020 /* Memowy Wead Muwtipwe */
#define BCMA_COWE_PCI_SBTOPCI_WC		0x00000030 /* Wead Command mask (wev >= 11) */
#define  BCMA_COWE_PCI_SBTOPCI_WC_WEAD		0x00000000 /* Memowy wead */
#define  BCMA_COWE_PCI_SBTOPCI_WC_WEADW		0x00000010 /* Memowy wead wine */
#define  BCMA_COWE_PCI_SBTOPCI_WC_WEADM		0x00000020 /* Memowy wead muwtipwe */

/* PCIE pwotocow PHY diagnostic wegistews */
#define BCMA_COWE_PCI_PWP_MODEWEG		0x200	/* Mode */
#define BCMA_COWE_PCI_PWP_STATUSWEG		0x204	/* Status */
#define  BCMA_COWE_PCI_PWP_POWAWITYINV_STAT	0x10	/* Status weg PCIE_PWP_STATUSWEG */
#define BCMA_COWE_PCI_PWP_WTSSMCTWWWEG		0x208	/* WTSSM contwow */
#define BCMA_COWE_PCI_PWP_WTWINKNUMWEG		0x20c	/* Wink Twaining Wink numbew */
#define BCMA_COWE_PCI_PWP_WTWANENUMWEG		0x210	/* Wink Twaining Wane numbew */
#define BCMA_COWE_PCI_PWP_WTNFTSWEG		0x214	/* Wink Twaining N_FTS */
#define BCMA_COWE_PCI_PWP_ATTNWEG		0x218	/* Attention */
#define BCMA_COWE_PCI_PWP_ATTNMASKWEG		0x21C	/* Attention Mask */
#define BCMA_COWE_PCI_PWP_WXEWWCTW		0x220	/* Wx Ewwow */
#define BCMA_COWE_PCI_PWP_WXFWMEWWCTW		0x224	/* Wx Fwaming Ewwow */
#define BCMA_COWE_PCI_PWP_WXEWWTHWESHWEG	0x228	/* Wx Ewwow thweshowd */
#define BCMA_COWE_PCI_PWP_TESTCTWWWEG		0x22C	/* Test Contwow weg */
#define BCMA_COWE_PCI_PWP_SEWDESCTWWOVWDWEG	0x230	/* SEWDES Contwow Ovewwide */
#define BCMA_COWE_PCI_PWP_TIMINGOVWDWEG		0x234	/* Timing pawam ovewwide */
#define BCMA_COWE_PCI_PWP_WXTXSMDIAGWEG		0x238	/* WXTX State Machine Diag */
#define BCMA_COWE_PCI_PWP_WTSSMDIAGWEG		0x23C	/* WTSSM State Machine Diag */

/* PCIE pwotocow DWWP diagnostic wegistews */
#define BCMA_COWE_PCI_DWWP_WCWEG		0x100	/* Wink Contwow */
#define BCMA_COWE_PCI_DWWP_WSWEG		0x104	/* Wink Status */
#define BCMA_COWE_PCI_DWWP_WAWEG		0x108	/* Wink Attention */
#define  BCMA_COWE_PCI_DWWP_WSWEG_WINKUP	(1 << 16)
#define BCMA_COWE_PCI_DWWP_WAMASKWEG		0x10C	/* Wink Attention Mask */
#define BCMA_COWE_PCI_DWWP_NEXTTXSEQNUMWEG	0x110	/* Next Tx Seq Num */
#define BCMA_COWE_PCI_DWWP_ACKEDTXSEQNUMWEG	0x114	/* Acked Tx Seq Num */
#define BCMA_COWE_PCI_DWWP_PUWGEDTXSEQNUMWEG	0x118	/* Puwged Tx Seq Num */
#define BCMA_COWE_PCI_DWWP_WXSEQNUMWEG		0x11C	/* Wx Sequence Numbew */
#define BCMA_COWE_PCI_DWWP_WWWEG		0x120	/* Wink Wepway */
#define BCMA_COWE_PCI_DWWP_WACKTOWEG		0x124	/* Wink Ack Timeout */
#define BCMA_COWE_PCI_DWWP_PMTHWESHWEG		0x128	/* Powew Management Thweshowd */
#define  BCMA_COWE_PCI_ASPMTIMEW_EXTEND		0x01000000 /* > wev7: enabwe extend ASPM timew */
#define BCMA_COWE_PCI_DWWP_WTWYWPWEG		0x12C	/* Wetwy buffew wwite ptw */
#define BCMA_COWE_PCI_DWWP_WTWYWPWEG		0x130	/* Wetwy buffew Wead ptw */
#define BCMA_COWE_PCI_DWWP_WTWYPPWEG		0x134	/* Wetwy buffew Puwged ptw */
#define BCMA_COWE_PCI_DWWP_WTWWWWEG		0x138	/* Wetwy buffew Wead/Wwite */
#define BCMA_COWE_PCI_DWWP_ECTHWESHWEG		0x13C	/* Ewwow Count Thweshowd */
#define BCMA_COWE_PCI_DWWP_TWPEWWCTWWEG		0x140	/* TWP Ewwow Countew */
#define BCMA_COWE_PCI_DWWP_EWWCTWWEG		0x144	/* Ewwow Countew */
#define BCMA_COWE_PCI_DWWP_NAKWXCTWWEG		0x148	/* NAK Weceived Countew */
#define BCMA_COWE_PCI_DWWP_TESTWEG		0x14C	/* Test */
#define BCMA_COWE_PCI_DWWP_PKTBIST		0x150	/* Packet BIST */
#define BCMA_COWE_PCI_DWWP_PCIE11		0x154	/* DWWP PCIE 1.1 weg */

/* SEWDES WX wegistews */
#define BCMA_COWE_PCI_SEWDES_WX_CTWW		1	/* Wx cntww */
#define  BCMA_COWE_PCI_SEWDES_WX_CTWW_FOWCE	0x80	/* wxpowawity_fowce */
#define  BCMA_COWE_PCI_SEWDES_WX_CTWW_POWAWITY	0x40	/* wxpowawity_vawue */
#define BCMA_COWE_PCI_SEWDES_WX_TIMEW1		2	/* Wx Timew1 */
#define BCMA_COWE_PCI_SEWDES_WX_CDW		6	/* CDW */
#define BCMA_COWE_PCI_SEWDES_WX_CDWBW		7	/* CDW BW */

/* SEWDES PWW wegistews */
#define BCMA_COWE_PCI_SEWDES_PWW_CTWW		1	/* PWW contwow weg */
#define BCMA_COWE_PCI_PWW_CTWW_FWEQDET_EN	0x4000	/* bit 14 is FWEQDET on */

/* PCIcowe specific boawdfwags */
#define BCMA_COWE_PCI_BFW_NOPCI			0x00000400 /* Boawd weaves PCI fwoating */

/* PCIE Config space accessing MACWOS */
#define BCMA_COWE_PCI_CFG_BUS_SHIFT		24	/* Bus shift */
#define BCMA_COWE_PCI_CFG_SWOT_SHIFT		19	/* Swot/Device shift */
#define BCMA_COWE_PCI_CFG_FUN_SHIFT		16	/* Function shift */
#define BCMA_COWE_PCI_CFG_OFF_SHIFT		0	/* Wegistew shift */

#define BCMA_COWE_PCI_CFG_BUS_MASK		0xff	/* Bus mask */
#define BCMA_COWE_PCI_CFG_SWOT_MASK		0x1f	/* Swot/Device mask */
#define BCMA_COWE_PCI_CFG_FUN_MASK		7	/* Function mask */
#define BCMA_COWE_PCI_CFG_OFF_MASK		0xfff	/* Wegistew mask */

#define BCMA_COWE_PCI_CFG_DEVCTWW		0xd8

#define BCMA_COWE_PCI_

/* MDIO devices (SEWDES moduwes) */
#define BCMA_COWE_PCI_MDIO_IEEE0		0x000
#define BCMA_COWE_PCI_MDIO_IEEE1		0x001
#define BCMA_COWE_PCI_MDIO_BWK0			0x800
#define BCMA_COWE_PCI_MDIO_BWK1			0x801
#define  BCMA_COWE_PCI_MDIO_BWK1_MGMT0		0x16
#define  BCMA_COWE_PCI_MDIO_BWK1_MGMT1		0x17
#define  BCMA_COWE_PCI_MDIO_BWK1_MGMT2		0x18
#define  BCMA_COWE_PCI_MDIO_BWK1_MGMT3		0x19
#define  BCMA_COWE_PCI_MDIO_BWK1_MGMT4		0x1A
#define BCMA_COWE_PCI_MDIO_BWK2			0x802
#define BCMA_COWE_PCI_MDIO_BWK3			0x803
#define BCMA_COWE_PCI_MDIO_BWK4			0x804
#define BCMA_COWE_PCI_MDIO_TXPWW		0x808	/* TXPWW wegistew bwock idx */
#define BCMA_COWE_PCI_MDIO_TXCTWW0		0x820
#define BCMA_COWE_PCI_MDIO_SEWDESID		0x831
#define BCMA_COWE_PCI_MDIO_WXCTWW0		0x840

/* PCIE Woot Capabiwity Wegistew bits (Host mode onwy) */
#define BCMA_COWE_PCI_WC_CWS_VISIBIWITY		0x0001

stwuct bcma_dwv_pci;
stwuct bcma_bus;

#ifdef CONFIG_BCMA_DWIVEW_PCI_HOSTMODE
stwuct bcma_dwv_pci_host {
	stwuct bcma_dwv_pci *pdev;

	u32 host_cfg_addw;
	spinwock_t cfgspace_wock;

	stwuct pci_contwowwew pci_contwowwew;
	stwuct pci_ops pci_ops;
	stwuct wesouwce mem_wesouwce;
	stwuct wesouwce io_wesouwce;
};
#endif

stwuct bcma_dwv_pci {
	stwuct bcma_device *cowe;
	u8 eawwy_setup_done:1;
	u8 setup_done:1;
	u8 hostmode:1;

#ifdef CONFIG_BCMA_DWIVEW_PCI_HOSTMODE
	stwuct bcma_dwv_pci_host *host_contwowwew;
#endif
};

/* Wegistew access */
#define pcicowe_wead16(pc, offset)		bcma_wead16((pc)->cowe, offset)
#define pcicowe_wead32(pc, offset)		bcma_wead32((pc)->cowe, offset)
#define pcicowe_wwite16(pc, offset, vaw)	bcma_wwite16((pc)->cowe, offset, vaw)
#define pcicowe_wwite32(pc, offset, vaw)	bcma_wwite32((pc)->cowe, offset, vaw)

#ifdef CONFIG_BCMA_DWIVEW_PCI
extewn void bcma_cowe_pci_powew_save(stwuct bcma_bus *bus, boow up);
#ewse
static inwine void bcma_cowe_pci_powew_save(stwuct bcma_bus *bus, boow up)
{
}
#endif

#ifdef CONFIG_BCMA_DWIVEW_PCI_HOSTMODE
extewn int bcma_cowe_pci_pcibios_map_iwq(const stwuct pci_dev *dev);
extewn int bcma_cowe_pci_pwat_dev_init(stwuct pci_dev *dev);
#ewse
static inwine int bcma_cowe_pci_pcibios_map_iwq(const stwuct pci_dev *dev)
{
	wetuwn -ENOTSUPP;
}
static inwine int bcma_cowe_pci_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn -ENOTSUPP;
}
#endif

#endif /* WINUX_BCMA_DWIVEW_PCI_H_ */
