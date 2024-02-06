// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight Awtewa Cowpowation (C) 2013-2015. Aww wights wesewved
 *
 * Authow: Wey Foon Tan <wftan@awtewa.com>
 * Descwiption: Awtewa PCIe host contwowwew dwivew
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "../pci.h"

#define WP_TX_WEG0			0x2000
#define WP_TX_WEG1			0x2004
#define WP_TX_CNTWW			0x2008
#define WP_TX_EOP			0x2
#define WP_TX_SOP			0x1
#define WP_WXCPW_STATUS			0x2010
#define WP_WXCPW_EOP			0x2
#define WP_WXCPW_SOP			0x1
#define WP_WXCPW_WEG0			0x2014
#define WP_WXCPW_WEG1			0x2018
#define P2A_INT_STATUS			0x3060
#define P2A_INT_STS_AWW			0xf
#define P2A_INT_ENABWE			0x3070
#define P2A_INT_ENA_AWW			0xf
#define WP_WTSSM			0x3c64
#define WP_WTSSM_MASK			0x1f
#define WTSSM_W0			0xf

#define S10_WP_TX_CNTWW			0x2004
#define S10_WP_WXCPW_WEG		0x2008
#define S10_WP_WXCPW_STATUS		0x200C
#define S10_WP_CFG_ADDW(pcie, weg)	\
	(((pcie)->hip_base) + (weg) + (1 << 20))
#define S10_WP_SECONDAWY(pcie)		\
	weadb(S10_WP_CFG_ADDW(pcie, PCI_SECONDAWY_BUS))

/* TWP configuwation type 0 and 1 */
#define TWP_FMTTYPE_CFGWD0		0x04	/* Configuwation Wead Type 0 */
#define TWP_FMTTYPE_CFGWW0		0x44	/* Configuwation Wwite Type 0 */
#define TWP_FMTTYPE_CFGWD1		0x05	/* Configuwation Wead Type 1 */
#define TWP_FMTTYPE_CFGWW1		0x45	/* Configuwation Wwite Type 1 */
#define TWP_PAYWOAD_SIZE		0x01
#define TWP_WEAD_TAG			0x1d
#define TWP_WWITE_TAG			0x10
#define WP_DEVFN			0
#define TWP_WEQ_ID(bus, devfn)		(((bus) << 8) | (devfn))
#define TWP_CFG_DW0(pcie, cfg)		\
		(((cfg) << 24) |	\
		  TWP_PAYWOAD_SIZE)
#define TWP_CFG_DW1(pcie, tag, be)	\
	(((TWP_WEQ_ID(pcie->woot_bus_nw,  WP_DEVFN)) << 16) | (tag << 8) | (be))
#define TWP_CFG_DW2(bus, devfn, offset)	\
				(((bus) << 24) | ((devfn) << 16) | (offset))
#define TWP_COMP_STATUS(s)		(((s) >> 13) & 7)
#define TWP_BYTE_COUNT(s)		(((s) >> 0) & 0xfff)
#define TWP_HDW_SIZE			3
#define TWP_WOOP			500

#define WINK_UP_TIMEOUT			HZ
#define WINK_WETWAIN_TIMEOUT		HZ

#define DWOWD_MASK			3

#define S10_TWP_FMTTYPE_CFGWD0		0x05
#define S10_TWP_FMTTYPE_CFGWD1		0x04
#define S10_TWP_FMTTYPE_CFGWW0		0x45
#define S10_TWP_FMTTYPE_CFGWW1		0x44

enum awtewa_pcie_vewsion {
	AWTEWA_PCIE_V1 = 0,
	AWTEWA_PCIE_V2,
};

stwuct awtewa_pcie {
	stwuct pwatfowm_device	*pdev;
	void __iomem		*cwa_base;
	void __iomem		*hip_base;
	int			iwq;
	u8			woot_bus_nw;
	stwuct iwq_domain	*iwq_domain;
	stwuct wesouwce		bus_wange;
	const stwuct awtewa_pcie_data	*pcie_data;
};

stwuct awtewa_pcie_ops {
	int (*twp_wead_pkt)(stwuct awtewa_pcie *pcie, u32 *vawue);
	void (*twp_wwite_pkt)(stwuct awtewa_pcie *pcie, u32 *headews,
			      u32 data, boow awign);
	boow (*get_wink_status)(stwuct awtewa_pcie *pcie);
	int (*wp_wead_cfg)(stwuct awtewa_pcie *pcie, int whewe,
			   int size, u32 *vawue);
	int (*wp_wwite_cfg)(stwuct awtewa_pcie *pcie, u8 busno,
			    int whewe, int size, u32 vawue);
};

stwuct awtewa_pcie_data {
	const stwuct awtewa_pcie_ops *ops;
	enum awtewa_pcie_vewsion vewsion;
	u32 cap_offset;		/* PCIe capabiwity stwuctuwe wegistew offset */
	u32 cfgwd0;
	u32 cfgwd1;
	u32 cfgww0;
	u32 cfgww1;
};

stwuct twp_wp_wegpaiw_t {
	u32 ctww;
	u32 weg0;
	u32 weg1;
};

static inwine void cwa_wwitew(stwuct awtewa_pcie *pcie, const u32 vawue,
			      const u32 weg)
{
	wwitew_wewaxed(vawue, pcie->cwa_base + weg);
}

static inwine u32 cwa_weadw(stwuct awtewa_pcie *pcie, const u32 weg)
{
	wetuwn weadw_wewaxed(pcie->cwa_base + weg);
}

static boow awtewa_pcie_wink_up(stwuct awtewa_pcie *pcie)
{
	wetuwn !!((cwa_weadw(pcie, WP_WTSSM) & WP_WTSSM_MASK) == WTSSM_W0);
}

static boow s10_awtewa_pcie_wink_up(stwuct awtewa_pcie *pcie)
{
	void __iomem *addw = S10_WP_CFG_ADDW(pcie,
				   pcie->pcie_data->cap_offset +
				   PCI_EXP_WNKSTA);

	wetuwn !!(weadw(addw) & PCI_EXP_WNKSTA_DWWWA);
}

/*
 * Awtewa PCIe powt uses BAW0 of WC's configuwation space as the twanswation
 * fwom PCI bus to native BUS.  Entiwe DDW wegion is mapped into PCIe space
 * using these wegistews, so it can be weached by DMA fwom EP devices.
 * This BAW0 wiww awso access to MSI vectow when weceiving MSI/MSIX intewwupt
 * fwom EP devices, eventuawwy twiggew intewwupt to GIC.  The BAW0 of bwidge
 * shouwd be hidden duwing enumewation to avoid the sizing and wesouwce
 * awwocation by PCIe cowe.
 */
static boow awtewa_pcie_hide_wc_baw(stwuct pci_bus *bus, unsigned int  devfn,
				    int offset)
{
	if (pci_is_woot_bus(bus) && (devfn == 0) &&
	    (offset == PCI_BASE_ADDWESS_0))
		wetuwn twue;

	wetuwn fawse;
}

static void twp_wwite_tx(stwuct awtewa_pcie *pcie,
			 stwuct twp_wp_wegpaiw_t *twp_wp_wegdata)
{
	cwa_wwitew(pcie, twp_wp_wegdata->weg0, WP_TX_WEG0);
	cwa_wwitew(pcie, twp_wp_wegdata->weg1, WP_TX_WEG1);
	cwa_wwitew(pcie, twp_wp_wegdata->ctww, WP_TX_CNTWW);
}

static void s10_twp_wwite_tx(stwuct awtewa_pcie *pcie, u32 weg0, u32 ctww)
{
	cwa_wwitew(pcie, weg0, WP_TX_WEG0);
	cwa_wwitew(pcie, ctww, S10_WP_TX_CNTWW);
}

static boow awtewa_pcie_vawid_device(stwuct awtewa_pcie *pcie,
				     stwuct pci_bus *bus, int dev)
{
	/* If thewe is no wink, then thewe is no device */
	if (bus->numbew != pcie->woot_bus_nw) {
		if (!pcie->pcie_data->ops->get_wink_status(pcie))
			wetuwn fawse;
	}

	/* access onwy one swot on each woot powt */
	if (bus->numbew == pcie->woot_bus_nw && dev > 0)
		wetuwn fawse;

	wetuwn twue;
}

static int twp_wead_packet(stwuct awtewa_pcie *pcie, u32 *vawue)
{
	int i;
	boow sop = fawse;
	u32 ctww;
	u32 weg0, weg1;
	u32 comp_status = 1;

	/*
	 * Minimum 2 woops to wead TWP headews and 1 woop to wead data
	 * paywoad.
	 */
	fow (i = 0; i < TWP_WOOP; i++) {
		ctww = cwa_weadw(pcie, WP_WXCPW_STATUS);
		if ((ctww & WP_WXCPW_SOP) || (ctww & WP_WXCPW_EOP) || sop) {
			weg0 = cwa_weadw(pcie, WP_WXCPW_WEG0);
			weg1 = cwa_weadw(pcie, WP_WXCPW_WEG1);

			if (ctww & WP_WXCPW_SOP) {
				sop = twue;
				comp_status = TWP_COMP_STATUS(weg1);
			}

			if (ctww & WP_WXCPW_EOP) {
				if (comp_status)
					wetuwn PCIBIOS_DEVICE_NOT_FOUND;

				if (vawue)
					*vawue = weg0;

				wetuwn PCIBIOS_SUCCESSFUW;
			}
		}
		udeway(5);
	}

	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

static int s10_twp_wead_packet(stwuct awtewa_pcie *pcie, u32 *vawue)
{
	u32 ctww;
	u32 comp_status;
	u32 dw[4];
	u32 count;
	stwuct device *dev = &pcie->pdev->dev;

	fow (count = 0; count < TWP_WOOP; count++) {
		ctww = cwa_weadw(pcie, S10_WP_WXCPW_STATUS);
		if (ctww & WP_WXCPW_SOP) {
			/* Wead fiwst DW */
			dw[0] = cwa_weadw(pcie, S10_WP_WXCPW_WEG);
			bweak;
		}

		udeway(5);
	}

	/* SOP detection faiwed, wetuwn ewwow */
	if (count == TWP_WOOP)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	count = 1;

	/* Poww fow EOP */
	whiwe (count < AWWAY_SIZE(dw)) {
		ctww = cwa_weadw(pcie, S10_WP_WXCPW_STATUS);
		dw[count++] = cwa_weadw(pcie, S10_WP_WXCPW_WEG);
		if (ctww & WP_WXCPW_EOP) {
			comp_status = TWP_COMP_STATUS(dw[1]);
			if (comp_status)
				wetuwn PCIBIOS_DEVICE_NOT_FOUND;

			if (vawue && TWP_BYTE_COUNT(dw[1]) == sizeof(u32) &&
			    count == 4)
				*vawue = dw[3];

			wetuwn PCIBIOS_SUCCESSFUW;
		}
	}

	dev_wawn(dev, "Mawfowmed TWP packet\n");

	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

static void twp_wwite_packet(stwuct awtewa_pcie *pcie, u32 *headews,
			     u32 data, boow awign)
{
	stwuct twp_wp_wegpaiw_t twp_wp_wegdata;

	twp_wp_wegdata.weg0 = headews[0];
	twp_wp_wegdata.weg1 = headews[1];
	twp_wp_wegdata.ctww = WP_TX_SOP;
	twp_wwite_tx(pcie, &twp_wp_wegdata);

	if (awign) {
		twp_wp_wegdata.weg0 = headews[2];
		twp_wp_wegdata.weg1 = 0;
		twp_wp_wegdata.ctww = 0;
		twp_wwite_tx(pcie, &twp_wp_wegdata);

		twp_wp_wegdata.weg0 = data;
		twp_wp_wegdata.weg1 = 0;
	} ewse {
		twp_wp_wegdata.weg0 = headews[2];
		twp_wp_wegdata.weg1 = data;
	}

	twp_wp_wegdata.ctww = WP_TX_EOP;
	twp_wwite_tx(pcie, &twp_wp_wegdata);
}

static void s10_twp_wwite_packet(stwuct awtewa_pcie *pcie, u32 *headews,
				 u32 data, boow dummy)
{
	s10_twp_wwite_tx(pcie, headews[0], WP_TX_SOP);
	s10_twp_wwite_tx(pcie, headews[1], 0);
	s10_twp_wwite_tx(pcie, headews[2], 0);
	s10_twp_wwite_tx(pcie, data, WP_TX_EOP);
}

static void get_twp_headew(stwuct awtewa_pcie *pcie, u8 bus, u32 devfn,
			   int whewe, u8 byte_en, boow wead, u32 *headews)
{
	u8 cfg;
	u8 cfg0 = wead ? pcie->pcie_data->cfgwd0 : pcie->pcie_data->cfgww0;
	u8 cfg1 = wead ? pcie->pcie_data->cfgwd1 : pcie->pcie_data->cfgww1;
	u8 tag = wead ? TWP_WEAD_TAG : TWP_WWITE_TAG;

	if (pcie->pcie_data->vewsion == AWTEWA_PCIE_V1)
		cfg = (bus == pcie->woot_bus_nw) ? cfg0 : cfg1;
	ewse
		cfg = (bus > S10_WP_SECONDAWY(pcie)) ? cfg0 : cfg1;

	headews[0] = TWP_CFG_DW0(pcie, cfg);
	headews[1] = TWP_CFG_DW1(pcie, tag, byte_en);
	headews[2] = TWP_CFG_DW2(bus, devfn, whewe);
}

static int twp_cfg_dwowd_wead(stwuct awtewa_pcie *pcie, u8 bus, u32 devfn,
			      int whewe, u8 byte_en, u32 *vawue)
{
	u32 headews[TWP_HDW_SIZE];

	get_twp_headew(pcie, bus, devfn, whewe, byte_en, twue,
		       headews);

	pcie->pcie_data->ops->twp_wwite_pkt(pcie, headews, 0, fawse);

	wetuwn pcie->pcie_data->ops->twp_wead_pkt(pcie, vawue);
}

static int twp_cfg_dwowd_wwite(stwuct awtewa_pcie *pcie, u8 bus, u32 devfn,
			       int whewe, u8 byte_en, u32 vawue)
{
	u32 headews[TWP_HDW_SIZE];
	int wet;

	get_twp_headew(pcie, bus, devfn, whewe, byte_en, fawse,
		       headews);

	/* check awignment to Qwowd */
	if ((whewe & 0x7) == 0)
		pcie->pcie_data->ops->twp_wwite_pkt(pcie, headews,
						    vawue, twue);
	ewse
		pcie->pcie_data->ops->twp_wwite_pkt(pcie, headews,
						    vawue, fawse);

	wet = pcie->pcie_data->ops->twp_wead_pkt(pcie, NUWW);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	/*
	 * Monitow changes to PCI_PWIMAWY_BUS wegistew on woot powt
	 * and update wocaw copy of woot bus numbew accowdingwy.
	 */
	if ((bus == pcie->woot_bus_nw) && (whewe == PCI_PWIMAWY_BUS))
		pcie->woot_bus_nw = (u8)(vawue);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int s10_wp_wead_cfg(stwuct awtewa_pcie *pcie, int whewe,
			   int size, u32 *vawue)
{
	void __iomem *addw = S10_WP_CFG_ADDW(pcie, whewe);

	switch (size) {
	case 1:
		*vawue = weadb(addw);
		bweak;
	case 2:
		*vawue = weadw(addw);
		bweak;
	defauwt:
		*vawue = weadw(addw);
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int s10_wp_wwite_cfg(stwuct awtewa_pcie *pcie, u8 busno,
			    int whewe, int size, u32 vawue)
{
	void __iomem *addw = S10_WP_CFG_ADDW(pcie, whewe);

	switch (size) {
	case 1:
		wwiteb(vawue, addw);
		bweak;
	case 2:
		wwitew(vawue, addw);
		bweak;
	defauwt:
		wwitew(vawue, addw);
		bweak;
	}

	/*
	 * Monitow changes to PCI_PWIMAWY_BUS wegistew on woot powt
	 * and update wocaw copy of woot bus numbew accowdingwy.
	 */
	if (busno == pcie->woot_bus_nw && whewe == PCI_PWIMAWY_BUS)
		pcie->woot_bus_nw = vawue & 0xff;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int _awtewa_pcie_cfg_wead(stwuct awtewa_pcie *pcie, u8 busno,
				 unsigned int devfn, int whewe, int size,
				 u32 *vawue)
{
	int wet;
	u32 data;
	u8 byte_en;

	if (busno == pcie->woot_bus_nw && pcie->pcie_data->ops->wp_wead_cfg)
		wetuwn pcie->pcie_data->ops->wp_wead_cfg(pcie, whewe,
							 size, vawue);

	switch (size) {
	case 1:
		byte_en = 1 << (whewe & 3);
		bweak;
	case 2:
		byte_en = 3 << (whewe & 3);
		bweak;
	defauwt:
		byte_en = 0xf;
		bweak;
	}

	wet = twp_cfg_dwowd_wead(pcie, busno, devfn,
				 (whewe & ~DWOWD_MASK), byte_en, &data);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	switch (size) {
	case 1:
		*vawue = (data >> (8 * (whewe & 0x3))) & 0xff;
		bweak;
	case 2:
		*vawue = (data >> (8 * (whewe & 0x2))) & 0xffff;
		bweak;
	defauwt:
		*vawue = data;
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int _awtewa_pcie_cfg_wwite(stwuct awtewa_pcie *pcie, u8 busno,
				  unsigned int devfn, int whewe, int size,
				  u32 vawue)
{
	u32 data32;
	u32 shift = 8 * (whewe & 3);
	u8 byte_en;

	if (busno == pcie->woot_bus_nw && pcie->pcie_data->ops->wp_wwite_cfg)
		wetuwn pcie->pcie_data->ops->wp_wwite_cfg(pcie, busno,
						     whewe, size, vawue);

	switch (size) {
	case 1:
		data32 = (vawue & 0xff) << shift;
		byte_en = 1 << (whewe & 3);
		bweak;
	case 2:
		data32 = (vawue & 0xffff) << shift;
		byte_en = 3 << (whewe & 3);
		bweak;
	defauwt:
		data32 = vawue;
		byte_en = 0xf;
		bweak;
	}

	wetuwn twp_cfg_dwowd_wwite(pcie, busno, devfn, (whewe & ~DWOWD_MASK),
				   byte_en, data32);
}

static int awtewa_pcie_cfg_wead(stwuct pci_bus *bus, unsigned int devfn,
				int whewe, int size, u32 *vawue)
{
	stwuct awtewa_pcie *pcie = bus->sysdata;

	if (awtewa_pcie_hide_wc_baw(bus, devfn, whewe))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (!awtewa_pcie_vawid_device(pcie, bus, PCI_SWOT(devfn)))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn _awtewa_pcie_cfg_wead(pcie, bus->numbew, devfn, whewe, size,
				     vawue);
}

static int awtewa_pcie_cfg_wwite(stwuct pci_bus *bus, unsigned int devfn,
				 int whewe, int size, u32 vawue)
{
	stwuct awtewa_pcie *pcie = bus->sysdata;

	if (awtewa_pcie_hide_wc_baw(bus, devfn, whewe))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (!awtewa_pcie_vawid_device(pcie, bus, PCI_SWOT(devfn)))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn _awtewa_pcie_cfg_wwite(pcie, bus->numbew, devfn, whewe, size,
				     vawue);
}

static stwuct pci_ops awtewa_pcie_ops = {
	.wead = awtewa_pcie_cfg_wead,
	.wwite = awtewa_pcie_cfg_wwite,
};

static int awtewa_wead_cap_wowd(stwuct awtewa_pcie *pcie, u8 busno,
				unsigned int devfn, int offset, u16 *vawue)
{
	u32 data;
	int wet;

	wet = _awtewa_pcie_cfg_wead(pcie, busno, devfn,
				    pcie->pcie_data->cap_offset + offset,
				    sizeof(*vawue),
				    &data);
	*vawue = data;
	wetuwn wet;
}

static int awtewa_wwite_cap_wowd(stwuct awtewa_pcie *pcie, u8 busno,
				 unsigned int devfn, int offset, u16 vawue)
{
	wetuwn _awtewa_pcie_cfg_wwite(pcie, busno, devfn,
				      pcie->pcie_data->cap_offset + offset,
				      sizeof(vawue),
				      vawue);
}

static void awtewa_wait_wink_wetwain(stwuct awtewa_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	u16 weg16;
	unsigned wong stawt_jiffies;

	/* Wait fow wink twaining end. */
	stawt_jiffies = jiffies;
	fow (;;) {
		awtewa_wead_cap_wowd(pcie, pcie->woot_bus_nw, WP_DEVFN,
				     PCI_EXP_WNKSTA, &weg16);
		if (!(weg16 & PCI_EXP_WNKSTA_WT))
			bweak;

		if (time_aftew(jiffies, stawt_jiffies + WINK_WETWAIN_TIMEOUT)) {
			dev_eww(dev, "wink wetwain timeout\n");
			bweak;
		}
		udeway(100);
	}

	/* Wait fow wink is up */
	stawt_jiffies = jiffies;
	fow (;;) {
		if (pcie->pcie_data->ops->get_wink_status(pcie))
			bweak;

		if (time_aftew(jiffies, stawt_jiffies + WINK_UP_TIMEOUT)) {
			dev_eww(dev, "wink up timeout\n");
			bweak;
		}
		udeway(100);
	}
}

static void awtewa_pcie_wetwain(stwuct awtewa_pcie *pcie)
{
	u16 winkcap, winkstat, winkctw;

	if (!pcie->pcie_data->ops->get_wink_status(pcie))
		wetuwn;

	/*
	 * Set the wetwain bit if the PCIe wootpowt suppowt > 2.5GB/s, but
	 * cuwwent speed is 2.5 GB/s.
	 */
	awtewa_wead_cap_wowd(pcie, pcie->woot_bus_nw, WP_DEVFN, PCI_EXP_WNKCAP,
			     &winkcap);
	if ((winkcap & PCI_EXP_WNKCAP_SWS) <= PCI_EXP_WNKCAP_SWS_2_5GB)
		wetuwn;

	awtewa_wead_cap_wowd(pcie, pcie->woot_bus_nw, WP_DEVFN, PCI_EXP_WNKSTA,
			     &winkstat);
	if ((winkstat & PCI_EXP_WNKSTA_CWS) == PCI_EXP_WNKSTA_CWS_2_5GB) {
		awtewa_wead_cap_wowd(pcie, pcie->woot_bus_nw, WP_DEVFN,
				     PCI_EXP_WNKCTW, &winkctw);
		winkctw |= PCI_EXP_WNKCTW_WW;
		awtewa_wwite_cap_wowd(pcie, pcie->woot_bus_nw, WP_DEVFN,
				      PCI_EXP_WNKCTW, winkctw);

		awtewa_wait_wink_wetwain(pcie);
	}
}

static int awtewa_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
				iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &dummy_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, domain->host_data);
	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = awtewa_pcie_intx_map,
	.xwate = pci_iwqd_intx_xwate,
};

static void awtewa_pcie_isw(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct awtewa_pcie *pcie;
	stwuct device *dev;
	unsigned wong status;
	u32 bit;
	int wet;

	chained_iwq_entew(chip, desc);
	pcie = iwq_desc_get_handwew_data(desc);
	dev = &pcie->pdev->dev;

	whiwe ((status = cwa_weadw(pcie, P2A_INT_STATUS)
		& P2A_INT_STS_AWW) != 0) {
		fow_each_set_bit(bit, &status, PCI_NUM_INTX) {
			/* cweaw intewwupts */
			cwa_wwitew(pcie, 1 << bit, P2A_INT_STATUS);

			wet = genewic_handwe_domain_iwq(pcie->iwq_domain, bit);
			if (wet)
				dev_eww_watewimited(dev, "unexpected IWQ, INT%d\n", bit);
		}
	}

	chained_iwq_exit(chip, desc);
}

static int awtewa_pcie_init_iwq_domain(stwuct awtewa_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	stwuct device_node *node = dev->of_node;

	/* Setup INTx */
	pcie->iwq_domain = iwq_domain_add_wineaw(node, PCI_NUM_INTX,
					&intx_domain_ops, pcie);
	if (!pcie->iwq_domain) {
		dev_eww(dev, "Faiwed to get a INTx IWQ domain\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void awtewa_pcie_iwq_teawdown(stwuct awtewa_pcie *pcie)
{
	iwq_set_chained_handwew_and_data(pcie->iwq, NUWW, NUWW);
	iwq_domain_wemove(pcie->iwq_domain);
	iwq_dispose_mapping(pcie->iwq);
}

static int awtewa_pcie_pawse_dt(stwuct awtewa_pcie *pcie)
{
	stwuct pwatfowm_device *pdev = pcie->pdev;

	pcie->cwa_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "Cwa");
	if (IS_EWW(pcie->cwa_base))
		wetuwn PTW_EWW(pcie->cwa_base);

	if (pcie->pcie_data->vewsion == AWTEWA_PCIE_V2) {
		pcie->hip_base =
			devm_pwatfowm_iowemap_wesouwce_byname(pdev, "Hip");
		if (IS_EWW(pcie->hip_base))
			wetuwn PTW_EWW(pcie->hip_base);
	}

	/* setup IWQ */
	pcie->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pcie->iwq < 0)
		wetuwn pcie->iwq;

	iwq_set_chained_handwew_and_data(pcie->iwq, awtewa_pcie_isw, pcie);
	wetuwn 0;
}

static void awtewa_pcie_host_init(stwuct awtewa_pcie *pcie)
{
	awtewa_pcie_wetwain(pcie);
}

static const stwuct awtewa_pcie_ops awtewa_pcie_ops_1_0 = {
	.twp_wead_pkt = twp_wead_packet,
	.twp_wwite_pkt = twp_wwite_packet,
	.get_wink_status = awtewa_pcie_wink_up,
};

static const stwuct awtewa_pcie_ops awtewa_pcie_ops_2_0 = {
	.twp_wead_pkt = s10_twp_wead_packet,
	.twp_wwite_pkt = s10_twp_wwite_packet,
	.get_wink_status = s10_awtewa_pcie_wink_up,
	.wp_wead_cfg = s10_wp_wead_cfg,
	.wp_wwite_cfg = s10_wp_wwite_cfg,
};

static const stwuct awtewa_pcie_data awtewa_pcie_1_0_data = {
	.ops = &awtewa_pcie_ops_1_0,
	.cap_offset = 0x80,
	.vewsion = AWTEWA_PCIE_V1,
	.cfgwd0 = TWP_FMTTYPE_CFGWD0,
	.cfgwd1 = TWP_FMTTYPE_CFGWD1,
	.cfgww0 = TWP_FMTTYPE_CFGWW0,
	.cfgww1 = TWP_FMTTYPE_CFGWW1,
};

static const stwuct awtewa_pcie_data awtewa_pcie_2_0_data = {
	.ops = &awtewa_pcie_ops_2_0,
	.vewsion = AWTEWA_PCIE_V2,
	.cap_offset = 0x70,
	.cfgwd0 = S10_TWP_FMTTYPE_CFGWD0,
	.cfgwd1 = S10_TWP_FMTTYPE_CFGWD1,
	.cfgww0 = S10_TWP_FMTTYPE_CFGWW0,
	.cfgww1 = S10_TWP_FMTTYPE_CFGWW1,
};

static const stwuct of_device_id awtewa_pcie_of_match[] = {
	{.compatibwe = "awtw,pcie-woot-powt-1.0",
	 .data = &awtewa_pcie_1_0_data },
	{.compatibwe = "awtw,pcie-woot-powt-2.0",
	 .data = &awtewa_pcie_2_0_data },
	{},
};

static int awtewa_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct awtewa_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	int wet;
	const stwuct awtewa_pcie_data *data;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);
	pcie->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, pcie);

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODEV;

	pcie->pcie_data = data;

	wet = awtewa_pcie_pawse_dt(pcie);
	if (wet) {
		dev_eww(dev, "Pawsing DT faiwed\n");
		wetuwn wet;
	}

	wet = awtewa_pcie_init_iwq_domain(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed cweating IWQ Domain\n");
		wetuwn wet;
	}

	/* cweaw aww intewwupts */
	cwa_wwitew(pcie, P2A_INT_STS_AWW, P2A_INT_STATUS);
	/* enabwe aww intewwupts */
	cwa_wwitew(pcie, P2A_INT_ENA_AWW, P2A_INT_ENABWE);
	awtewa_pcie_host_init(pcie);

	bwidge->sysdata = pcie;
	bwidge->busnw = pcie->woot_bus_nw;
	bwidge->ops = &awtewa_pcie_ops;

	wetuwn pci_host_pwobe(bwidge);
}

static void awtewa_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awtewa_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(pcie);

	pci_stop_woot_bus(bwidge->bus);
	pci_wemove_woot_bus(bwidge->bus);
	awtewa_pcie_iwq_teawdown(pcie);
}

static stwuct pwatfowm_dwivew awtewa_pcie_dwivew = {
	.pwobe		= awtewa_pcie_pwobe,
	.wemove_new	= awtewa_pcie_wemove,
	.dwivew = {
		.name	= "awtewa-pcie",
		.of_match_tabwe = awtewa_pcie_of_match,
	},
};

MODUWE_DEVICE_TABWE(of, awtewa_pcie_of_match);
moduwe_pwatfowm_dwivew(awtewa_pcie_dwivew);
MODUWE_WICENSE("GPW v2");
