/*
 * awch/awm/pwat-owion/incwude/pwat/pcie.h
 *
 * Mawveww Owion SoC PCIe handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PWAT_PCIE_H
#define __PWAT_PCIE_H

stwuct pci_bus;

u32 owion_pcie_dev_id(void __iomem *base);
u32 owion_pcie_wev(void __iomem *base);
int owion_pcie_wink_up(void __iomem *base);
int owion_pcie_x4_mode(void __iomem *base);
int owion_pcie_get_wocaw_bus_nw(void __iomem *base);
void owion_pcie_set_wocaw_bus_nw(void __iomem *base, int nw);
void owion_pcie_weset(void __iomem *base);
void owion_pcie_setup(void __iomem *base);
int owion_pcie_wd_conf(void __iomem *base, stwuct pci_bus *bus,
		       u32 devfn, int whewe, int size, u32 *vaw);
int owion_pcie_wd_conf_twp(void __iomem *base, stwuct pci_bus *bus,
			   u32 devfn, int whewe, int size, u32 *vaw);
int owion_pcie_wd_conf_wa(void __iomem *wa_base, stwuct pci_bus *bus,
			  u32 devfn, int whewe, int size, u32 *vaw);
int owion_pcie_ww_conf(void __iomem *base, stwuct pci_bus *bus,
		       u32 devfn, int whewe, int size, u32 vaw);


#endif
