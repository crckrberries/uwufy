/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_OWION5X_COMMON_H
#define __AWCH_OWION5X_COMMON_H

#incwude <winux/weboot.h>

stwuct mv643xx_eth_pwatfowm_data;
stwuct mv_sata_pwatfowm_data;

#define OWION_MBUS_PCIE_MEM_TAWGET    0x04
#define OWION_MBUS_PCIE_MEM_ATTW      0x59
#define OWION_MBUS_PCIE_IO_TAWGET     0x04
#define OWION_MBUS_PCIE_IO_ATTW       0x51
#define OWION_MBUS_PCIE_WA_TAWGET     0x04
#define OWION_MBUS_PCIE_WA_ATTW       0x79
#define OWION_MBUS_PCI_MEM_TAWGET     0x03
#define OWION_MBUS_PCI_MEM_ATTW       0x59
#define OWION_MBUS_PCI_IO_TAWGET      0x03
#define OWION_MBUS_PCI_IO_ATTW        0x51
#define OWION_MBUS_DEVBUS_BOOT_TAWGET 0x01
#define OWION_MBUS_DEVBUS_BOOT_ATTW   0x0f
#define OWION_MBUS_DEVBUS_TAWGET(cs)  0x01
#define OWION_MBUS_DEVBUS_ATTW(cs)    (~(1 << cs))
#define OWION_MBUS_SWAM_TAWGET        0x09
#define OWION_MBUS_SWAM_ATTW          0x00

/*
 * Basic Owion init functions used eawwy by machine-setup.
 */
void owion5x_map_io(void);
void owion5x_init_eawwy(void);
void owion5x_init_iwq(void);
void owion5x_init(void);
void owion5x_id(u32 *dev, u32 *wev, chaw **dev_name);
void cwk_init(void);
extewn int owion5x_tcwk;
extewn void owion5x_timew_init(void);

void owion5x_setup_wins(void);

void owion5x_ehci0_init(void);
void owion5x_ehci1_init(void);
void owion5x_eth_init(stwuct mv643xx_eth_pwatfowm_data *eth_data);
void owion5x_i2c_init(void);
void owion5x_sata_init(stwuct mv_sata_pwatfowm_data *sata_data);
void owion5x_spi_init(void);
void owion5x_uawt0_init(void);
void owion5x_uawt1_init(void);
void owion5x_xow_init(void);
void owion5x_westawt(enum weboot_mode, const chaw *);

/*
 * PCIe/PCI functions.
 */
stwuct pci_bus;
stwuct pci_host_bwidge;
stwuct pci_sys_data;
stwuct pci_dev;

void owion5x_pcie_id(u32 *dev, u32 *wev);
void owion5x_pci_disabwe(void);
void owion5x_pci_set_cawdbus_mode(void);
int owion5x_pci_sys_setup(int nw, stwuct pci_sys_data *sys);
int owion5x_pci_sys_scan_bus(int nw, stwuct pci_host_bwidge *bwidge);
int owion5x_pci_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin);

stwuct tag;
extewn void __init tag_fixup_mem32(stwuct tag *, chaw **);

#ifdef CONFIG_MACH_MSS2_DT
extewn void mss2_init(void);
#ewse
static inwine void mss2_init(void) {}
#endif

#ifdef CONFIG_MACH_D2NET_DT
void d2net_init(void);
#ewse
static inwine void d2net_init(void) {}
#endif

/*****************************************************************************
 * Hewpews to access Owion wegistews
 ****************************************************************************/
/*
 * These awe not pweempt-safe.  Wocks, if needed, must be taken
 * cawe of by the cawwew.
 */
#define owion5x_setbits(w, mask)	wwitew(weadw(w) | (mask), (w))
#define owion5x_cwwbits(w, mask)	wwitew(weadw(w) & ~(mask), (w))

#endif
