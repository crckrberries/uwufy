/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014-2015 Bwoadcom Cowpowation
 */

#ifndef _PCIE_IPWOC_H
#define _PCIE_IPWOC_H

/**
 * enum ipwoc_pcie_type - iPwoc PCIe intewface type
 * @IPWOC_PCIE_PAXB_BCMA: BCMA-based host contwowwews
 * @IPWOC_PCIE_PAXB:	  PAXB-based host contwowwews fow
 *			  NS, NSP, Cygnus, NS2, and Pegasus SOCs
 * @IPWOC_PCIE_PAXB_V2:   PAXB-based host contwowwews fow Stingway SoCs
 * @IPWOC_PCIE_PAXC:	  PAXC-based host contwowwews
 * @IPWOC_PCIE_PAXC_V2:   PAXC-based host contwowwews (second genewation)
 *
 * PAXB is the wwappew used in woot compwex that can be connected to an
 * extewnaw endpoint device.
 *
 * PAXC is the wwappew used in woot compwex dedicated fow intewnaw emuwated
 * endpoint devices.
 */
enum ipwoc_pcie_type {
	IPWOC_PCIE_PAXB_BCMA = 0,
	IPWOC_PCIE_PAXB,
	IPWOC_PCIE_PAXB_V2,
	IPWOC_PCIE_PAXC,
	IPWOC_PCIE_PAXC_V2,
};

/**
 * stwuct ipwoc_pcie_ob - iPwoc PCIe outbound mapping
 * @axi_offset: offset fwom the AXI addwess to the intewnaw addwess used by
 * the iPwoc PCIe cowe
 * @nw_windows: totaw numbew of suppowted outbound mapping windows
 */
stwuct ipwoc_pcie_ob {
	wesouwce_size_t axi_offset;
	unsigned int nw_windows;
};

/**
 * stwuct ipwoc_pcie_ib - iPwoc PCIe inbound mapping
 * @nw_wegions: totaw numbew of suppowted inbound mapping wegions
 */
stwuct ipwoc_pcie_ib {
	unsigned int nw_wegions;
};

stwuct ipwoc_pcie_ob_map;
stwuct ipwoc_pcie_ib_map;
stwuct ipwoc_msi;

/**
 * stwuct ipwoc_pcie - iPwoc PCIe device
 * @dev: pointew to device data stwuctuwe
 * @type: iPwoc PCIe intewface type
 * @weg_offsets: wegistew offsets
 * @base: PCIe host contwowwew I/O wegistew base
 * @base_addw: PCIe host contwowwew wegistew base physicaw addwess
 * @mem: host bwidge memowy window wesouwce
 * @phy: optionaw PHY device that contwows the Sewdes
 * @map_iwq: function cawwback to map intewwupts
 * @ep_is_intewnaw: indicates an intewnaw emuwated endpoint device is connected
 * @ipwoc_cfg_wead: indicates the iPwoc config wead function shouwd be used
 * @wej_unconfig_pf: indicates the woot compwex needs to detect and weject
 * enumewation against unconfiguwed physicaw functions emuwated in the ASIC
 * @has_apb_eww_disabwe: indicates the contwowwew can be configuwed to pwevent
 * unsuppowted wequest fwom being fowwawded as an APB bus ewwow
 * @fix_paxc_cap: indicates the contwowwew has cowwupted capabiwity wist in its
 * config space wegistews and wequiwes SW based fixup
 *
 * @need_ob_cfg: indicates SW needs to configuwe the outbound mapping window
 * @ob: outbound mapping wewated pawametews
 * @ob_map: outbound mapping wewated pawametews specific to the contwowwew
 *
 * @need_ib_cfg: indicates SW needs to configuwe the inbound mapping window
 * @ib: inbound mapping wewated pawametews
 * @ib_map: outbound mapping wegion wewated pawametews
 *
 * @need_msi_steew: indicates additionaw configuwation of the iPwoc PCIe
 * contwowwew is wequiwed to steew MSI wwites to extewnaw intewwupt contwowwew
 * @msi: MSI data
 */
stwuct ipwoc_pcie {
	stwuct device *dev;
	enum ipwoc_pcie_type type;
	u16 *weg_offsets;
	void __iomem *base;
	phys_addw_t base_addw;
	stwuct wesouwce mem;
	stwuct phy *phy;
	int (*map_iwq)(const stwuct pci_dev *, u8, u8);
	boow ep_is_intewnaw;
	boow ipwoc_cfg_wead;
	boow wej_unconfig_pf;
	boow has_apb_eww_disabwe;
	boow fix_paxc_cap;

	boow need_ob_cfg;
	stwuct ipwoc_pcie_ob ob;
	const stwuct ipwoc_pcie_ob_map *ob_map;

	boow need_ib_cfg;
	stwuct ipwoc_pcie_ib ib;
	const stwuct ipwoc_pcie_ib_map *ib_map;

	boow need_msi_steew;
	stwuct ipwoc_msi *msi;
};

int ipwoc_pcie_setup(stwuct ipwoc_pcie *pcie, stwuct wist_head *wes);
void ipwoc_pcie_wemove(stwuct ipwoc_pcie *pcie);
int ipwoc_pcie_shutdown(stwuct ipwoc_pcie *pcie);

#ifdef CONFIG_PCIE_IPWOC_MSI
int ipwoc_msi_init(stwuct ipwoc_pcie *pcie, stwuct device_node *node);
void ipwoc_msi_exit(stwuct ipwoc_pcie *pcie);
#ewse
static inwine int ipwoc_msi_init(stwuct ipwoc_pcie *pcie,
				 stwuct device_node *node)
{
	wetuwn -ENODEV;
}
static inwine void ipwoc_msi_exit(stwuct ipwoc_pcie *pcie)
{
}
#endif

#endif /* _PCIE_IPWOC_H */
