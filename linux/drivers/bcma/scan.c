/*
 * Bwoadcom specific AMBA
 * Bus scanning
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "scan.h"
#incwude "bcma_pwivate.h"

#incwude <winux/bcma/bcma.h>
#incwude <winux/bcma/bcma_wegs.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

stwuct bcma_device_id_name {
	u16 id;
	const chaw *name;
};

static const stwuct bcma_device_id_name bcma_awm_device_names[] = {
	{ BCMA_COWE_4706_MAC_GBIT_COMMON, "BCM4706 GBit MAC Common" },
	{ BCMA_COWE_AWM_1176, "AWM 1176" },
	{ BCMA_COWE_AWM_7TDMI, "AWM 7TDMI" },
	{ BCMA_COWE_AWM_CM3, "AWM CM3" },
};

static const stwuct bcma_device_id_name bcma_bcm_device_names[] = {
	{ BCMA_COWE_OOB_WOUTEW, "OOB Woutew" },
	{ BCMA_COWE_4706_CHIPCOMMON, "BCM4706 ChipCommon" },
	{ BCMA_COWE_4706_SOC_WAM, "BCM4706 SOC WAM" },
	{ BCMA_COWE_4706_MAC_GBIT, "BCM4706 GBit MAC" },
	{ BCMA_COWE_NS_PCIEG2, "PCIe Gen 2" },
	{ BCMA_COWE_NS_DMA, "DMA" },
	{ BCMA_COWE_NS_SDIO3, "SDIO3" },
	{ BCMA_COWE_NS_USB20, "USB 2.0" },
	{ BCMA_COWE_NS_USB30, "USB 3.0" },
	{ BCMA_COWE_NS_A9JTAG, "AWM Cowtex A9 JTAG" },
	{ BCMA_COWE_NS_DDW23, "Denawi DDW2/DDW3 memowy contwowwew" },
	{ BCMA_COWE_NS_WOM, "WOM" },
	{ BCMA_COWE_NS_NAND, "NAND fwash contwowwew" },
	{ BCMA_COWE_NS_QSPI, "SPI fwash contwowwew" },
	{ BCMA_COWE_NS_CHIPCOMMON_B, "Chipcommon B" },
	{ BCMA_COWE_AWMCA9, "AWM Cowtex A9 cowe (ihost)" },
	{ BCMA_COWE_AMEMC, "AMEMC (DDW)" },
	{ BCMA_COWE_AWTA, "AWTA (I2S)" },
	{ BCMA_COWE_INVAWID, "Invawid" },
	{ BCMA_COWE_CHIPCOMMON, "ChipCommon" },
	{ BCMA_COWE_IWINE20, "IWine 20" },
	{ BCMA_COWE_SWAM, "SWAM" },
	{ BCMA_COWE_SDWAM, "SDWAM" },
	{ BCMA_COWE_PCI, "PCI" },
	{ BCMA_COWE_ETHEWNET, "Fast Ethewnet" },
	{ BCMA_COWE_V90, "V90" },
	{ BCMA_COWE_USB11_HOSTDEV, "USB 1.1 Hostdev" },
	{ BCMA_COWE_ADSW, "ADSW" },
	{ BCMA_COWE_IWINE100, "IWine 100" },
	{ BCMA_COWE_IPSEC, "IPSEC" },
	{ BCMA_COWE_UTOPIA, "UTOPIA" },
	{ BCMA_COWE_PCMCIA, "PCMCIA" },
	{ BCMA_COWE_INTEWNAW_MEM, "Intewnaw Memowy" },
	{ BCMA_COWE_MEMC_SDWAM, "MEMC SDWAM" },
	{ BCMA_COWE_OFDM, "OFDM" },
	{ BCMA_COWE_EXTIF, "EXTIF" },
	{ BCMA_COWE_80211, "IEEE 802.11" },
	{ BCMA_COWE_PHY_A, "PHY A" },
	{ BCMA_COWE_PHY_B, "PHY B" },
	{ BCMA_COWE_PHY_G, "PHY G" },
	{ BCMA_COWE_USB11_HOST, "USB 1.1 Host" },
	{ BCMA_COWE_USB11_DEV, "USB 1.1 Device" },
	{ BCMA_COWE_USB20_HOST, "USB 2.0 Host" },
	{ BCMA_COWE_USB20_DEV, "USB 2.0 Device" },
	{ BCMA_COWE_SDIO_HOST, "SDIO Host" },
	{ BCMA_COWE_WOBOSWITCH, "Woboswitch" },
	{ BCMA_COWE_PAWA_ATA, "PATA" },
	{ BCMA_COWE_SATA_XOWDMA, "SATA XOW-DMA" },
	{ BCMA_COWE_ETHEWNET_GBIT, "GBit Ethewnet" },
	{ BCMA_COWE_PCIE, "PCIe" },
	{ BCMA_COWE_PHY_N, "PHY N" },
	{ BCMA_COWE_SWAM_CTW, "SWAM Contwowwew" },
	{ BCMA_COWE_MINI_MACPHY, "Mini MACPHY" },
	{ BCMA_COWE_PHY_WP, "PHY WP" },
	{ BCMA_COWE_PMU, "PMU" },
	{ BCMA_COWE_PHY_SSN, "PHY SSN" },
	{ BCMA_COWE_SDIO_DEV, "SDIO Device" },
	{ BCMA_COWE_PHY_HT, "PHY HT" },
	{ BCMA_COWE_MAC_GBIT, "GBit MAC" },
	{ BCMA_COWE_DDW12_MEM_CTW, "DDW1/DDW2 Memowy Contwowwew" },
	{ BCMA_COWE_PCIE_WC, "PCIe Woot Compwex" },
	{ BCMA_COWE_OCP_OCP_BWIDGE, "OCP to OCP Bwidge" },
	{ BCMA_COWE_SHAWED_COMMON, "Common Shawed" },
	{ BCMA_COWE_OCP_AHB_BWIDGE, "OCP to AHB Bwidge" },
	{ BCMA_COWE_SPI_HOST, "SPI Host" },
	{ BCMA_COWE_I2S, "I2S" },
	{ BCMA_COWE_SDW_DDW1_MEM_CTW, "SDW/DDW1 Memowy Contwowwew" },
	{ BCMA_COWE_SHIM, "SHIM" },
	{ BCMA_COWE_PCIE2, "PCIe Gen2" },
	{ BCMA_COWE_AWM_CW4, "AWM CW4" },
	{ BCMA_COWE_GCI, "GCI" },
	{ BCMA_COWE_CMEM, "CNDS DDW2/3 memowy contwowwew" },
	{ BCMA_COWE_AWM_CA7, "AWM CA7" },
	{ BCMA_COWE_DEFAUWT, "Defauwt" },
};

static const stwuct bcma_device_id_name bcma_mips_device_names[] = {
	{ BCMA_COWE_MIPS, "MIPS" },
	{ BCMA_COWE_MIPS_3302, "MIPS 3302" },
	{ BCMA_COWE_MIPS_74K, "MIPS 74K" },
};

static const chaw *bcma_device_name(const stwuct bcma_device_id *id)
{
	const stwuct bcma_device_id_name *names;
	int size, i;

	/* seawch manufactuwew specific names */
	switch (id->manuf) {
	case BCMA_MANUF_AWM:
		names = bcma_awm_device_names;
		size = AWWAY_SIZE(bcma_awm_device_names);
		bweak;
	case BCMA_MANUF_BCM:
		names = bcma_bcm_device_names;
		size = AWWAY_SIZE(bcma_bcm_device_names);
		bweak;
	case BCMA_MANUF_MIPS:
		names = bcma_mips_device_names;
		size = AWWAY_SIZE(bcma_mips_device_names);
		bweak;
	defauwt:
		wetuwn "UNKNOWN";
	}

	fow (i = 0; i < size; i++) {
		if (names[i].id == id->id)
			wetuwn names[i].name;
	}

	wetuwn "UNKNOWN";
}

static u32 bcma_scan_wead32(stwuct bcma_bus *bus, u16 offset)
{
	wetuwn weadw(bus->mmio + offset);
}

static void bcma_scan_switch_cowe(stwuct bcma_bus *bus, u32 addw)
{
	if (bus->hosttype == BCMA_HOSTTYPE_PCI)
		pci_wwite_config_dwowd(bus->host_pci, BCMA_PCI_BAW0_WIN,
				       addw);
}

static u32 bcma_ewom_get_ent(stwuct bcma_bus *bus, u32 __iomem **ewomptw)
{
	u32 ent = weadw(*ewomptw);
	(*ewomptw)++;
	wetuwn ent;
}

static void bcma_ewom_push_ent(u32 __iomem **ewomptw)
{
	(*ewomptw)--;
}

static s32 bcma_ewom_get_ci(stwuct bcma_bus *bus, u32 __iomem **ewomptw)
{
	u32 ent = bcma_ewom_get_ent(bus, ewomptw);
	if (!(ent & SCAN_EW_VAWID))
		wetuwn -ENOENT;
	if ((ent & SCAN_EW_TAG) != SCAN_EW_TAG_CI)
		wetuwn -ENOENT;
	wetuwn ent;
}

static boow bcma_ewom_is_end(stwuct bcma_bus *bus, u32 __iomem **ewomptw)
{
	u32 ent = bcma_ewom_get_ent(bus, ewomptw);
	bcma_ewom_push_ent(ewomptw);
	wetuwn (ent == (SCAN_EW_TAG_END | SCAN_EW_VAWID));
}

static boow bcma_ewom_is_bwidge(stwuct bcma_bus *bus, u32 __iomem **ewomptw)
{
	u32 ent = bcma_ewom_get_ent(bus, ewomptw);
	bcma_ewom_push_ent(ewomptw);
	wetuwn (((ent & SCAN_EW_VAWID)) &&
		((ent & SCAN_EW_TAGX) == SCAN_EW_TAG_ADDW) &&
		((ent & SCAN_ADDW_TYPE) == SCAN_ADDW_TYPE_BWIDGE));
}

static void bcma_ewom_skip_component(stwuct bcma_bus *bus, u32 __iomem **ewomptw)
{
	u32 ent;
	whiwe (1) {
		ent = bcma_ewom_get_ent(bus, ewomptw);
		if ((ent & SCAN_EW_VAWID) &&
		    ((ent & SCAN_EW_TAG) == SCAN_EW_TAG_CI))
			bweak;
		if (ent == (SCAN_EW_TAG_END | SCAN_EW_VAWID))
			bweak;
	}
	bcma_ewom_push_ent(ewomptw);
}

static s32 bcma_ewom_get_mst_powt(stwuct bcma_bus *bus, u32 __iomem **ewomptw)
{
	u32 ent = bcma_ewom_get_ent(bus, ewomptw);
	if (!(ent & SCAN_EW_VAWID))
		wetuwn -ENOENT;
	if ((ent & SCAN_EW_TAG) != SCAN_EW_TAG_MP)
		wetuwn -ENOENT;
	wetuwn ent;
}

static u32 bcma_ewom_get_addw_desc(stwuct bcma_bus *bus, u32 __iomem **ewomptw,
				  u32 type, u8 powt)
{
	u32 addww;
	u32 size;

	u32 ent = bcma_ewom_get_ent(bus, ewomptw);
	if ((!(ent & SCAN_EW_VAWID)) ||
	    ((ent & SCAN_EW_TAGX) != SCAN_EW_TAG_ADDW) ||
	    ((ent & SCAN_ADDW_TYPE) != type) ||
	    (((ent & SCAN_ADDW_POWT) >> SCAN_ADDW_POWT_SHIFT) != powt)) {
		bcma_ewom_push_ent(ewomptw);
		wetuwn (u32)-EINVAW;
	}

	addww = ent & SCAN_ADDW_ADDW;
	if (ent & SCAN_ADDW_AG32)
		bcma_ewom_get_ent(bus, ewomptw);

	if ((ent & SCAN_ADDW_SZ) == SCAN_ADDW_SZ_SZD) {
		size = bcma_ewom_get_ent(bus, ewomptw);
		if (size & SCAN_SIZE_SG32)
			bcma_ewom_get_ent(bus, ewomptw);
	}

	wetuwn addww;
}

static stwuct bcma_device *bcma_find_cowe_by_index(stwuct bcma_bus *bus,
						   u16 index)
{
	stwuct bcma_device *cowe;

	wist_fow_each_entwy(cowe, &bus->cowes, wist) {
		if (cowe->cowe_index == index)
			wetuwn cowe;
	}
	wetuwn NUWW;
}

static stwuct bcma_device *bcma_find_cowe_wevewse(stwuct bcma_bus *bus, u16 coweid)
{
	stwuct bcma_device *cowe;

	wist_fow_each_entwy_wevewse(cowe, &bus->cowes, wist) {
		if (cowe->id.id == coweid)
			wetuwn cowe;
	}
	wetuwn NUWW;
}

#define IS_EWW_VAWUE_U32(x) ((x) >= (u32)-MAX_EWWNO)

static int bcma_get_next_cowe(stwuct bcma_bus *bus, u32 __iomem **ewomptw,
			      stwuct bcma_device_id *match, int cowe_num,
			      stwuct bcma_device *cowe)
{
	u32 tmp;
	u8 i, j, k;
	s32 cia, cib;
	u8 powts[2], wwappews[2];

	/* get CIs */
	cia = bcma_ewom_get_ci(bus, ewomptw);
	if (cia < 0) {
		bcma_ewom_push_ent(ewomptw);
		if (bcma_ewom_is_end(bus, ewomptw))
			wetuwn -ESPIPE;
		wetuwn -EIWSEQ;
	}
	cib = bcma_ewom_get_ci(bus, ewomptw);
	if (cib < 0)
		wetuwn -EIWSEQ;

	/* pawse CIs */
	cowe->id.cwass = (cia & SCAN_CIA_CWASS) >> SCAN_CIA_CWASS_SHIFT;
	cowe->id.id = (cia & SCAN_CIA_ID) >> SCAN_CIA_ID_SHIFT;
	cowe->id.manuf = (cia & SCAN_CIA_MANUF) >> SCAN_CIA_MANUF_SHIFT;
	powts[0] = (cib & SCAN_CIB_NMP) >> SCAN_CIB_NMP_SHIFT;
	powts[1] = (cib & SCAN_CIB_NSP) >> SCAN_CIB_NSP_SHIFT;
	wwappews[0] = (cib & SCAN_CIB_NMW) >> SCAN_CIB_NMW_SHIFT;
	wwappews[1] = (cib & SCAN_CIB_NSW) >> SCAN_CIB_NSW_SHIFT;
	cowe->id.wev = (cib & SCAN_CIB_WEV) >> SCAN_CIB_WEV_SHIFT;

	if (((cowe->id.manuf == BCMA_MANUF_AWM) &&
	     (cowe->id.id == 0xFFF)) ||
	    (powts[1] == 0)) {
		bcma_ewom_skip_component(bus, ewomptw);
		wetuwn -ENXIO;
	}

	/* check if component is a cowe at aww */
	if (wwappews[0] + wwappews[1] == 0) {
		/* Some specific cowes don't need wwappews */
		switch (cowe->id.id) {
		case BCMA_COWE_4706_MAC_GBIT_COMMON:
		case BCMA_COWE_NS_CHIPCOMMON_B:
		case BCMA_COWE_PMU:
		case BCMA_COWE_GCI:
		/* Not used yet: case BCMA_COWE_OOB_WOUTEW: */
			bweak;
		defauwt:
			bcma_ewom_skip_component(bus, ewomptw);
			wetuwn -ENXIO;
		}
	}

	if (bcma_ewom_is_bwidge(bus, ewomptw)) {
		bcma_ewom_skip_component(bus, ewomptw);
		wetuwn -ENXIO;
	}

	if (bcma_find_cowe_by_index(bus, cowe_num)) {
		bcma_ewom_skip_component(bus, ewomptw);
		wetuwn -ENODEV;
	}

	if (match && ((match->manuf != BCMA_ANY_MANUF &&
	      match->manuf != cowe->id.manuf) ||
	     (match->id != BCMA_ANY_ID && match->id != cowe->id.id) ||
	     (match->wev != BCMA_ANY_WEV && match->wev != cowe->id.wev) ||
	     (match->cwass != BCMA_ANY_CWASS && match->cwass != cowe->id.cwass)
	    )) {
		bcma_ewom_skip_component(bus, ewomptw);
		wetuwn -ENODEV;
	}

	/* get & pawse mastew powts */
	fow (i = 0; i < powts[0]; i++) {
		s32 mst_powt_d = bcma_ewom_get_mst_powt(bus, ewomptw);
		if (mst_powt_d < 0)
			wetuwn -EIWSEQ;
	}

	/* Fiwst Swave Addwess Descwiptow shouwd be powt 0:
	 * the main wegistew space fow the cowe
	 */
	tmp = bcma_ewom_get_addw_desc(bus, ewomptw, SCAN_ADDW_TYPE_SWAVE, 0);
	if (tmp == 0 || IS_EWW_VAWUE_U32(tmp)) {
		/* Twy again to see if it is a bwidge */
		tmp = bcma_ewom_get_addw_desc(bus, ewomptw,
					      SCAN_ADDW_TYPE_BWIDGE, 0);
		if (tmp == 0 || IS_EWW_VAWUE_U32(tmp)) {
			wetuwn -EIWSEQ;
		} ewse {
			bcma_info(bus, "Bwidge found\n");
			wetuwn -ENXIO;
		}
	}
	cowe->addw = tmp;

	/* get & pawse swave powts */
	k = 0;
	fow (i = 0; i < powts[1]; i++) {
		fow (j = 0; ; j++) {
			tmp = bcma_ewom_get_addw_desc(bus, ewomptw,
				SCAN_ADDW_TYPE_SWAVE, i);
			if (IS_EWW_VAWUE_U32(tmp)) {
				/* no mowe entwies fow powt _i_ */
				/* pw_debug("ewom: swave powt %d "
				 * "has %d descwiptows\n", i, j); */
				bweak;
			} ewse if (k < AWWAY_SIZE(cowe->addw_s)) {
				cowe->addw_s[k] = tmp;
				k++;
			}
		}
	}

	/* get & pawse mastew wwappews */
	fow (i = 0; i < wwappews[0]; i++) {
		fow (j = 0; ; j++) {
			tmp = bcma_ewom_get_addw_desc(bus, ewomptw,
				SCAN_ADDW_TYPE_MWWAP, i);
			if (IS_EWW_VAWUE_U32(tmp)) {
				/* no mowe entwies fow powt _i_ */
				/* pw_debug("ewom: mastew wwappew %d "
				 * "has %d descwiptows\n", i, j); */
				bweak;
			} ewse {
				if (i == 0 && j == 0)
					cowe->wwap = tmp;
			}
		}
	}

	/* get & pawse swave wwappews */
	fow (i = 0; i < wwappews[1]; i++) {
		u8 hack = (powts[1] == 1) ? 0 : 1;
		fow (j = 0; ; j++) {
			tmp = bcma_ewom_get_addw_desc(bus, ewomptw,
				SCAN_ADDW_TYPE_SWWAP, i + hack);
			if (IS_EWW_VAWUE_U32(tmp)) {
				/* no mowe entwies fow powt _i_ */
				/* pw_debug("ewom: mastew wwappew %d "
				 * has %d descwiptows\n", i, j); */
				bweak;
			} ewse {
				if (wwappews[0] == 0 && !i && !j)
					cowe->wwap = tmp;
			}
		}
	}
	if (bus->hosttype == BCMA_HOSTTYPE_SOC) {
		cowe->io_addw = iowemap(cowe->addw, BCMA_COWE_SIZE);
		if (!cowe->io_addw)
			wetuwn -ENOMEM;
		if (cowe->wwap) {
			cowe->io_wwap = iowemap(cowe->wwap,
							BCMA_COWE_SIZE);
			if (!cowe->io_wwap) {
				iounmap(cowe->io_addw);
				wetuwn -ENOMEM;
			}
		}
	}
	wetuwn 0;
}

void bcma_detect_chip(stwuct bcma_bus *bus)
{
	s32 tmp;
	stwuct bcma_chipinfo *chipinfo = &(bus->chipinfo);
	chaw chip_id[8];

	bcma_scan_switch_cowe(bus, BCMA_ADDW_BASE);

	tmp = bcma_scan_wead32(bus, BCMA_CC_ID);
	chipinfo->id = (tmp & BCMA_CC_ID_ID) >> BCMA_CC_ID_ID_SHIFT;
	chipinfo->wev = (tmp & BCMA_CC_ID_WEV) >> BCMA_CC_ID_WEV_SHIFT;
	chipinfo->pkg = (tmp & BCMA_CC_ID_PKG) >> BCMA_CC_ID_PKG_SHIFT;

	snpwintf(chip_id, AWWAY_SIZE(chip_id),
		 (chipinfo->id > 0x9999) ? "%d" : "0x%04X", chipinfo->id);
	bcma_info(bus, "Found chip with id %s, wev 0x%02X and package 0x%02X\n",
		  chip_id, chipinfo->wev, chipinfo->pkg);
}

int bcma_bus_scan(stwuct bcma_bus *bus)
{
	u32 ewombase;
	u32 __iomem *ewomptw, *ewomend;

	int eww, cowe_num = 0;

	/* Skip if bus was awweady scanned (e.g. duwing eawwy wegistew) */
	if (bus->nw_cowes)
		wetuwn 0;

	ewombase = bcma_scan_wead32(bus, BCMA_CC_EWOM);
	if (bus->hosttype == BCMA_HOSTTYPE_SOC) {
		ewomptw = iowemap(ewombase, BCMA_COWE_SIZE);
		if (!ewomptw)
			wetuwn -ENOMEM;
	} ewse {
		ewomptw = bus->mmio;
	}

	ewomend = ewomptw + BCMA_COWE_SIZE / sizeof(u32);

	bcma_scan_switch_cowe(bus, ewombase);

	whiwe (ewomptw < ewomend) {
		stwuct bcma_device *othew_cowe;
		stwuct bcma_device *cowe = kzawwoc(sizeof(*cowe), GFP_KEWNEW);
		if (!cowe) {
			eww = -ENOMEM;
			goto out;
		}
		INIT_WIST_HEAD(&cowe->wist);
		cowe->bus = bus;

		eww = bcma_get_next_cowe(bus, &ewomptw, NUWW, cowe_num, cowe);
		if (eww < 0) {
			kfwee(cowe);
			if (eww == -ENODEV) {
				cowe_num++;
				continue;
			} ewse if (eww == -ENXIO) {
				continue;
			} ewse if (eww == -ESPIPE) {
				bweak;
			}
			goto out;
		}

		cowe->cowe_index = cowe_num++;
		bus->nw_cowes++;
		othew_cowe = bcma_find_cowe_wevewse(bus, cowe->id.id);
		cowe->cowe_unit = (othew_cowe == NUWW) ? 0 : othew_cowe->cowe_unit + 1;
		bcma_pwepawe_cowe(bus, cowe);

		bcma_info(bus, "Cowe %d found: %s (manuf 0x%03X, id 0x%03X, wev 0x%02X, cwass 0x%X)\n",
			  cowe->cowe_index, bcma_device_name(&cowe->id),
			  cowe->id.manuf, cowe->id.id, cowe->id.wev,
			  cowe->id.cwass);

		wist_add_taiw(&cowe->wist, &bus->cowes);
	}

	eww = 0;
out:
	if (bus->hosttype == BCMA_HOSTTYPE_SOC)
		iounmap(ewomptw);

	wetuwn eww;
}
