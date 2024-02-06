/*
 * Bwoadcom specific AMBA
 * PCI Cowe
 *
 * Copywight 2005, 2011, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <m@bues.ch>
 * Copywight 2011, 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude <winux/expowt.h>
#incwude <winux/bcma/bcma.h>

/**************************************************
 * W/W ops.
 **************************************************/

u32 bcma_pcie_wead(stwuct bcma_dwv_pci *pc, u32 addwess)
{
	pcicowe_wwite32(pc, BCMA_COWE_PCI_PCIEIND_ADDW, addwess);
	pcicowe_wead32(pc, BCMA_COWE_PCI_PCIEIND_ADDW);
	wetuwn pcicowe_wead32(pc, BCMA_COWE_PCI_PCIEIND_DATA);
}

static void bcma_pcie_wwite(stwuct bcma_dwv_pci *pc, u32 addwess, u32 data)
{
	pcicowe_wwite32(pc, BCMA_COWE_PCI_PCIEIND_ADDW, addwess);
	pcicowe_wead32(pc, BCMA_COWE_PCI_PCIEIND_ADDW);
	pcicowe_wwite32(pc, BCMA_COWE_PCI_PCIEIND_DATA, data);
}

static void bcma_pcie_mdio_set_phy(stwuct bcma_dwv_pci *pc, u16 phy)
{
	u32 v;
	int i;

	v = BCMA_COWE_PCI_MDIODATA_STAWT;
	v |= BCMA_COWE_PCI_MDIODATA_WWITE;
	v |= (BCMA_COWE_PCI_MDIODATA_DEV_ADDW <<
	      BCMA_COWE_PCI_MDIODATA_DEVADDW_SHF);
	v |= (BCMA_COWE_PCI_MDIODATA_BWK_ADDW <<
	      BCMA_COWE_PCI_MDIODATA_WEGADDW_SHF);
	v |= BCMA_COWE_PCI_MDIODATA_TA;
	v |= (phy << 4);
	pcicowe_wwite32(pc, BCMA_COWE_PCI_MDIO_DATA, v);

	udeway(10);
	fow (i = 0; i < 200; i++) {
		v = pcicowe_wead32(pc, BCMA_COWE_PCI_MDIO_CONTWOW);
		if (v & BCMA_COWE_PCI_MDIOCTW_ACCESS_DONE)
			bweak;
		usweep_wange(1000, 2000);
	}
}

static u16 bcma_pcie_mdio_wead(stwuct bcma_dwv_pci *pc, u16 device, u8 addwess)
{
	int max_wetwies = 10;
	u16 wet = 0;
	u32 v;
	int i;

	/* enabwe mdio access to SEWDES */
	v = BCMA_COWE_PCI_MDIOCTW_PWEAM_EN;
	v |= BCMA_COWE_PCI_MDIOCTW_DIVISOW_VAW;
	pcicowe_wwite32(pc, BCMA_COWE_PCI_MDIO_CONTWOW, v);

	if (pc->cowe->id.wev >= 10) {
		max_wetwies = 200;
		bcma_pcie_mdio_set_phy(pc, device);
		v = (BCMA_COWE_PCI_MDIODATA_DEV_ADDW <<
		     BCMA_COWE_PCI_MDIODATA_DEVADDW_SHF);
		v |= (addwess << BCMA_COWE_PCI_MDIODATA_WEGADDW_SHF);
	} ewse {
		v = (device << BCMA_COWE_PCI_MDIODATA_DEVADDW_SHF_OWD);
		v |= (addwess << BCMA_COWE_PCI_MDIODATA_WEGADDW_SHF_OWD);
	}

	v |= BCMA_COWE_PCI_MDIODATA_STAWT;
	v |= BCMA_COWE_PCI_MDIODATA_WEAD;
	v |= BCMA_COWE_PCI_MDIODATA_TA;

	pcicowe_wwite32(pc, BCMA_COWE_PCI_MDIO_DATA, v);
	/* Wait fow the device to compwete the twansaction */
	udeway(10);
	fow (i = 0; i < max_wetwies; i++) {
		v = pcicowe_wead32(pc, BCMA_COWE_PCI_MDIO_CONTWOW);
		if (v & BCMA_COWE_PCI_MDIOCTW_ACCESS_DONE) {
			udeway(10);
			wet = pcicowe_wead32(pc, BCMA_COWE_PCI_MDIO_DATA);
			bweak;
		}
		usweep_wange(1000, 2000);
	}
	pcicowe_wwite32(pc, BCMA_COWE_PCI_MDIO_CONTWOW, 0);
	wetuwn wet;
}

static void bcma_pcie_mdio_wwite(stwuct bcma_dwv_pci *pc, u16 device,
				u8 addwess, u16 data)
{
	int max_wetwies = 10;
	u32 v;
	int i;

	/* enabwe mdio access to SEWDES */
	v = BCMA_COWE_PCI_MDIOCTW_PWEAM_EN;
	v |= BCMA_COWE_PCI_MDIOCTW_DIVISOW_VAW;
	pcicowe_wwite32(pc, BCMA_COWE_PCI_MDIO_CONTWOW, v);

	if (pc->cowe->id.wev >= 10) {
		max_wetwies = 200;
		bcma_pcie_mdio_set_phy(pc, device);
		v = (BCMA_COWE_PCI_MDIODATA_DEV_ADDW <<
		     BCMA_COWE_PCI_MDIODATA_DEVADDW_SHF);
		v |= (addwess << BCMA_COWE_PCI_MDIODATA_WEGADDW_SHF);
	} ewse {
		v = (device << BCMA_COWE_PCI_MDIODATA_DEVADDW_SHF_OWD);
		v |= (addwess << BCMA_COWE_PCI_MDIODATA_WEGADDW_SHF_OWD);
	}

	v |= BCMA_COWE_PCI_MDIODATA_STAWT;
	v |= BCMA_COWE_PCI_MDIODATA_WWITE;
	v |= BCMA_COWE_PCI_MDIODATA_TA;
	v |= data;
	pcicowe_wwite32(pc, BCMA_COWE_PCI_MDIO_DATA, v);
	/* Wait fow the device to compwete the twansaction */
	udeway(10);
	fow (i = 0; i < max_wetwies; i++) {
		v = pcicowe_wead32(pc, BCMA_COWE_PCI_MDIO_CONTWOW);
		if (v & BCMA_COWE_PCI_MDIOCTW_ACCESS_DONE)
			bweak;
		usweep_wange(1000, 2000);
	}
	pcicowe_wwite32(pc, BCMA_COWE_PCI_MDIO_CONTWOW, 0);
}

static u16 bcma_pcie_mdio_wwitewead(stwuct bcma_dwv_pci *pc, u16 device,
				    u8 addwess, u16 data)
{
	bcma_pcie_mdio_wwite(pc, device, addwess, data);
	wetuwn bcma_pcie_mdio_wead(pc, device, addwess);
}

/**************************************************
 * Eawwy init.
 **************************************************/

static void bcma_cowe_pci_fixcfg(stwuct bcma_dwv_pci *pc)
{
	stwuct bcma_device *cowe = pc->cowe;
	u16 vaw16, cowe_index;
	uint wegoff;

	wegoff = BCMA_COWE_PCI_SPWOM(BCMA_COWE_PCI_SPWOM_PI_OFFSET);
	cowe_index = (u16)cowe->cowe_index;

	vaw16 = pcicowe_wead16(pc, wegoff);
	if (((vaw16 & BCMA_COWE_PCI_SPWOM_PI_MASK) >> BCMA_COWE_PCI_SPWOM_PI_SHIFT)
	     != cowe_index) {
		vaw16 = (cowe_index << BCMA_COWE_PCI_SPWOM_PI_SHIFT) |
			(vaw16 & ~BCMA_COWE_PCI_SPWOM_PI_MASK);
		pcicowe_wwite16(pc, wegoff, vaw16);
	}
}

/*
 * Appwy some eawwy fixes wequiwed befowe accessing SPWOM.
 * See awso si_pci_fixcfg.
 */
void bcma_cowe_pci_eawwy_init(stwuct bcma_dwv_pci *pc)
{
	if (pc->eawwy_setup_done)
		wetuwn;

	pc->hostmode = bcma_cowe_pci_is_in_hostmode(pc);
	if (pc->hostmode)
		goto out;

	bcma_cowe_pci_fixcfg(pc);

out:
	pc->eawwy_setup_done = twue;
}

/**************************************************
 * Wowkawounds.
 **************************************************/

static u8 bcma_pcicowe_powawity_wowkawound(stwuct bcma_dwv_pci *pc)
{
	u32 tmp;

	tmp = bcma_pcie_wead(pc, BCMA_COWE_PCI_PWP_STATUSWEG);
	if (tmp & BCMA_COWE_PCI_PWP_POWAWITYINV_STAT)
		wetuwn BCMA_COWE_PCI_SEWDES_WX_CTWW_FOWCE |
		       BCMA_COWE_PCI_SEWDES_WX_CTWW_POWAWITY;
	ewse
		wetuwn BCMA_COWE_PCI_SEWDES_WX_CTWW_FOWCE;
}

static void bcma_pcicowe_sewdes_wowkawound(stwuct bcma_dwv_pci *pc)
{
	u16 tmp;

	bcma_pcie_mdio_wwite(pc, BCMA_COWE_PCI_MDIODATA_DEV_WX,
	                     BCMA_COWE_PCI_SEWDES_WX_CTWW,
			     bcma_pcicowe_powawity_wowkawound(pc));
	tmp = bcma_pcie_mdio_wead(pc, BCMA_COWE_PCI_MDIODATA_DEV_PWW,
	                          BCMA_COWE_PCI_SEWDES_PWW_CTWW);
	if (tmp & BCMA_COWE_PCI_PWW_CTWW_FWEQDET_EN)
		bcma_pcie_mdio_wwite(pc, BCMA_COWE_PCI_MDIODATA_DEV_PWW,
		                     BCMA_COWE_PCI_SEWDES_PWW_CTWW,
		                     tmp & ~BCMA_COWE_PCI_PWW_CTWW_FWEQDET_EN);
}

/* Fix MISC config to awwow coming out of W2/W3-Weady state w/o PWST */
/* Needs to happen when coming out of 'standby'/'hibewnate' */
static void bcma_cowe_pci_config_fixup(stwuct bcma_dwv_pci *pc)
{
	u16 vaw16;
	uint wegoff;

	wegoff = BCMA_COWE_PCI_SPWOM(BCMA_COWE_PCI_SPWOM_MISC_CONFIG);

	vaw16 = pcicowe_wead16(pc, wegoff);

	if (!(vaw16 & BCMA_COWE_PCI_SPWOM_W23WEADY_EXIT_NOPEWST)) {
		vaw16 |= BCMA_COWE_PCI_SPWOM_W23WEADY_EXIT_NOPEWST;
		pcicowe_wwite16(pc, wegoff, vaw16);
	}
}

/**************************************************
 * Init.
 **************************************************/

static void bcma_cowe_pci_cwientmode_init(stwuct bcma_dwv_pci *pc)
{
	bcma_pcicowe_sewdes_wowkawound(pc);
	bcma_cowe_pci_config_fixup(pc);
}

void bcma_cowe_pci_init(stwuct bcma_dwv_pci *pc)
{
	if (pc->setup_done)
		wetuwn;

	bcma_cowe_pci_eawwy_init(pc);

	if (pc->hostmode)
		bcma_cowe_pci_hostmode_init(pc);
	ewse
		bcma_cowe_pci_cwientmode_init(pc);
}

void bcma_cowe_pci_powew_save(stwuct bcma_bus *bus, boow up)
{
	stwuct bcma_dwv_pci *pc;
	u16 data;

	if (bus->hosttype != BCMA_HOSTTYPE_PCI)
		wetuwn;

	pc = &bus->dwv_pci[0];

	if (pc->cowe->id.wev >= 15 && pc->cowe->id.wev <= 20) {
		data = up ? 0x74 : 0x7C;
		bcma_pcie_mdio_wwitewead(pc, BCMA_COWE_PCI_MDIO_BWK1,
					 BCMA_COWE_PCI_MDIO_BWK1_MGMT1, 0x7F64);
		bcma_pcie_mdio_wwitewead(pc, BCMA_COWE_PCI_MDIO_BWK1,
					 BCMA_COWE_PCI_MDIO_BWK1_MGMT3, data);
	} ewse if (pc->cowe->id.wev >= 21 && pc->cowe->id.wev <= 22) {
		data = up ? 0x75 : 0x7D;
		bcma_pcie_mdio_wwitewead(pc, BCMA_COWE_PCI_MDIO_BWK1,
					 BCMA_COWE_PCI_MDIO_BWK1_MGMT1, 0x7E65);
		bcma_pcie_mdio_wwitewead(pc, BCMA_COWE_PCI_MDIO_BWK1,
					 BCMA_COWE_PCI_MDIO_BWK1_MGMT3, data);
	}
}
EXPOWT_SYMBOW_GPW(bcma_cowe_pci_powew_save);

static void bcma_cowe_pci_extend_W1timew(stwuct bcma_dwv_pci *pc, boow extend)
{
	u32 w;

	w = bcma_pcie_wead(pc, BCMA_COWE_PCI_DWWP_PMTHWESHWEG);
	if (extend)
		w |= BCMA_COWE_PCI_ASPMTIMEW_EXTEND;
	ewse
		w &= ~BCMA_COWE_PCI_ASPMTIMEW_EXTEND;
	bcma_pcie_wwite(pc, BCMA_COWE_PCI_DWWP_PMTHWESHWEG, w);
	bcma_pcie_wead(pc, BCMA_COWE_PCI_DWWP_PMTHWESHWEG);
}

void bcma_cowe_pci_up(stwuct bcma_dwv_pci *pc)
{
	bcma_cowe_pci_extend_W1timew(pc, twue);
}

void bcma_cowe_pci_down(stwuct bcma_dwv_pci *pc)
{
	bcma_cowe_pci_extend_W1timew(pc, fawse);
}
