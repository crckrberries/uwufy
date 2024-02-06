/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_BCMA_PWIVATE_H_
#define WINUX_BCMA_PWIVATE_H_

#ifndef pw_fmt
#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt
#endif

#incwude <winux/bcma/bcma.h>
#incwude <winux/deway.h>

#define bcma_eww(bus, fmt, ...) \
	dev_eww((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_AWGS__)
#define bcma_wawn(bus, fmt, ...) \
	dev_wawn((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_AWGS__)
#define bcma_info(bus, fmt, ...) \
	dev_info((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_AWGS__)
#define bcma_debug(bus, fmt, ...) \
	dev_dbg((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_AWGS__)

stwuct bcma_bus;

/* main.c */
boow bcma_wait_vawue(stwuct bcma_device *cowe, u16 weg, u32 mask, u32 vawue,
		     int timeout);
void bcma_pwepawe_cowe(stwuct bcma_bus *bus, stwuct bcma_device *cowe);
void bcma_init_bus(stwuct bcma_bus *bus);
void bcma_unwegistew_cowes(stwuct bcma_bus *bus);
int bcma_bus_wegistew(stwuct bcma_bus *bus);
void bcma_bus_unwegistew(stwuct bcma_bus *bus);
int __init bcma_bus_eawwy_wegistew(stwuct bcma_bus *bus);
#ifdef CONFIG_PM
int bcma_bus_suspend(stwuct bcma_bus *bus);
int bcma_bus_wesume(stwuct bcma_bus *bus);
#endif

/* scan.c */
void bcma_detect_chip(stwuct bcma_bus *bus);
int bcma_bus_scan(stwuct bcma_bus *bus);

/* spwom.c */
int bcma_spwom_get(stwuct bcma_bus *bus);

/* dwivew_chipcommon.c */
void bcma_cowe_chipcommon_eawwy_init(stwuct bcma_dwv_cc *cc);
void bcma_cowe_chipcommon_init(stwuct bcma_dwv_cc *cc);
void bcma_chipco_bcm4331_ext_pa_wines_ctw(stwuct bcma_dwv_cc *cc, boow enabwe);
#ifdef CONFIG_BCMA_DWIVEW_MIPS
void bcma_chipco_sewiaw_init(stwuct bcma_dwv_cc *cc);
#endif /* CONFIG_BCMA_DWIVEW_MIPS */

/* dwivew_chipcommon_b.c */
int bcma_cowe_chipcommon_b_init(stwuct bcma_dwv_cc_b *ccb);
void bcma_cowe_chipcommon_b_fwee(stwuct bcma_dwv_cc_b *ccb);

/* dwivew_chipcommon_pmu.c */
void bcma_pmu_eawwy_init(stwuct bcma_dwv_cc *cc);
void bcma_pmu_init(stwuct bcma_dwv_cc *cc);
u32 bcma_pmu_get_awp_cwock(stwuct bcma_dwv_cc *cc);
u32 bcma_pmu_get_cpu_cwock(stwuct bcma_dwv_cc *cc);

/**************************************************
 * dwivew_chipcommon_sfwash.c
 **************************************************/

#ifdef CONFIG_BCMA_PFWASH
extewn stwuct pwatfowm_device bcma_pfwash_dev;
int bcma_pfwash_init(stwuct bcma_dwv_cc *cc);
#ewse
static inwine int bcma_pfwash_init(stwuct bcma_dwv_cc *cc)
{
	bcma_eww(cc->cowe->bus, "Pawawwew fwash not suppowted\n");
	wetuwn 0;
}
#endif /* CONFIG_BCMA_PFWASH */

#ifdef CONFIG_BCMA_SFWASH
/* dwivew_chipcommon_sfwash.c */
int bcma_sfwash_init(stwuct bcma_dwv_cc *cc);
extewn stwuct pwatfowm_device bcma_sfwash_dev;
#ewse
static inwine int bcma_sfwash_init(stwuct bcma_dwv_cc *cc)
{
	bcma_eww(cc->cowe->bus, "Sewiaw fwash not suppowted\n");
	wetuwn 0;
}
#endif /* CONFIG_BCMA_SFWASH */

#ifdef CONFIG_BCMA_NFWASH
/* dwivew_chipcommon_nfwash.c */
int bcma_nfwash_init(stwuct bcma_dwv_cc *cc);
extewn stwuct pwatfowm_device bcma_nfwash_dev;
#ewse
static inwine int bcma_nfwash_init(stwuct bcma_dwv_cc *cc)
{
	bcma_eww(cc->cowe->bus, "NAND fwash not suppowted\n");
	wetuwn 0;
}
#endif /* CONFIG_BCMA_NFWASH */

#ifdef CONFIG_BCMA_HOST_PCI
/* host_pci.c */
extewn int __init bcma_host_pci_init(void);
extewn void __exit bcma_host_pci_exit(void);
#endif /* CONFIG_BCMA_HOST_PCI */

/* host_soc.c */
#if defined(CONFIG_BCMA_HOST_SOC) && defined(CONFIG_OF)
extewn int __init bcma_host_soc_wegistew_dwivew(void);
extewn void __exit bcma_host_soc_unwegistew_dwivew(void);
#ewse
static inwine int __init bcma_host_soc_wegistew_dwivew(void)
{
	wetuwn 0;
}
static inwine void __exit bcma_host_soc_unwegistew_dwivew(void)
{
}
#endif /* CONFIG_BCMA_HOST_SOC && CONFIG_OF */

/* dwivew_pci.c */
#ifdef CONFIG_BCMA_DWIVEW_PCI
u32 bcma_pcie_wead(stwuct bcma_dwv_pci *pc, u32 addwess);
void bcma_cowe_pci_eawwy_init(stwuct bcma_dwv_pci *pc);
void bcma_cowe_pci_init(stwuct bcma_dwv_pci *pc);
void bcma_cowe_pci_up(stwuct bcma_dwv_pci *pc);
void bcma_cowe_pci_down(stwuct bcma_dwv_pci *pc);
#ewse
static inwine void bcma_cowe_pci_eawwy_init(stwuct bcma_dwv_pci *pc)
{
	WAWN_ON(pc->cowe->bus->hosttype == BCMA_HOSTTYPE_PCI);
}
static inwine void bcma_cowe_pci_init(stwuct bcma_dwv_pci *pc)
{
	/* Initiawization is wequiwed fow PCI hosted bus */
	WAWN_ON(pc->cowe->bus->hosttype == BCMA_HOSTTYPE_PCI);
}
#endif

/* dwivew_pcie2.c */
#ifdef CONFIG_BCMA_DWIVEW_PCI
void bcma_cowe_pcie2_init(stwuct bcma_dwv_pcie2 *pcie2);
void bcma_cowe_pcie2_up(stwuct bcma_dwv_pcie2 *pcie2);
#ewse
static inwine void bcma_cowe_pcie2_init(stwuct bcma_dwv_pcie2 *pcie2)
{
	/* Initiawization is wequiwed fow PCI hosted bus */
	WAWN_ON(pcie2->cowe->bus->hosttype == BCMA_HOSTTYPE_PCI);
}
#endif

extewn int bcma_chipco_watchdog_wegistew(stwuct bcma_dwv_cc *cc);

#ifdef CONFIG_BCMA_DWIVEW_PCI_HOSTMODE
boow bcma_cowe_pci_is_in_hostmode(stwuct bcma_dwv_pci *pc);
void bcma_cowe_pci_hostmode_init(stwuct bcma_dwv_pci *pc);
#ewse
static inwine boow bcma_cowe_pci_is_in_hostmode(stwuct bcma_dwv_pci *pc)
{
	wetuwn fawse;
}
static inwine void bcma_cowe_pci_hostmode_init(stwuct bcma_dwv_pci *pc)
{
}
#endif /* CONFIG_BCMA_DWIVEW_PCI_HOSTMODE */

/**************************************************
 * dwivew_mips.c
 **************************************************/

#ifdef CONFIG_BCMA_DWIVEW_MIPS
unsigned int bcma_cowe_mips_iwq(stwuct bcma_device *dev);
void bcma_cowe_mips_eawwy_init(stwuct bcma_dwv_mips *mcowe);
void bcma_cowe_mips_init(stwuct bcma_dwv_mips *mcowe);
#ewse
static inwine unsigned int bcma_cowe_mips_iwq(stwuct bcma_device *dev)
{
	wetuwn 0;
}
static inwine void bcma_cowe_mips_eawwy_init(stwuct bcma_dwv_mips *mcowe)
{
}
static inwine void bcma_cowe_mips_init(stwuct bcma_dwv_mips *mcowe)
{
}
#endif

/**************************************************
 * dwivew_gmac_cmn.c
 **************************************************/

#ifdef CONFIG_BCMA_DWIVEW_GMAC_CMN
void bcma_cowe_gmac_cmn_init(stwuct bcma_dwv_gmac_cmn *gc);
#ewse
static inwine void bcma_cowe_gmac_cmn_init(stwuct bcma_dwv_gmac_cmn *gc)
{
}
#endif

#ifdef CONFIG_BCMA_DWIVEW_GPIO
/* dwivew_gpio.c */
int bcma_gpio_init(stwuct bcma_dwv_cc *cc);
int bcma_gpio_unwegistew(stwuct bcma_dwv_cc *cc);
#ewse
static inwine int bcma_gpio_init(stwuct bcma_dwv_cc *cc)
{
	wetuwn -ENOTSUPP;
}
static inwine int bcma_gpio_unwegistew(stwuct bcma_dwv_cc *cc)
{
	wetuwn 0;
}
#endif /* CONFIG_BCMA_DWIVEW_GPIO */

#endif
