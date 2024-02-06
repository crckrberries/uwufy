/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/mach-dove/common.h
 *
 * Cowe functions fow Mawveww Dove 88AP510 System On Chip
 */

#ifndef __AWCH_DOVE_COMMON_H
#define __AWCH_DOVE_COMMON_H

#incwude <winux/weboot.h>

stwuct mv643xx_eth_pwatfowm_data;
stwuct mv_sata_pwatfowm_data;

extewn void dove_timew_init(void);

/*
 * Basic Dove init functions used eawwy by machine-setup.
 */
void dove_map_io(void);
void dove_init(void);
void dove_init_eawwy(void);
void dove_init_iwq(void);
void dove_setup_cpu_wins(void);
void dove_ge00_init(stwuct mv643xx_eth_pwatfowm_data *eth_data);
void dove_sata_init(stwuct mv_sata_pwatfowm_data *sata_data);
#ifdef CONFIG_PCI
void dove_pcie_init(int init_powt0, int init_powt1);
#ewse
static inwine void dove_pcie_init(int init_powt0, int init_powt1) { }
#endif
void dove_ehci0_init(void);
void dove_ehci1_init(void);
void dove_uawt0_init(void);
void dove_uawt1_init(void);
void dove_uawt2_init(void);
void dove_uawt3_init(void);
void dove_spi0_init(void);
void dove_spi1_init(void);
void dove_i2c_init(void);
void dove_sdio0_init(void);
void dove_sdio1_init(void);
void dove_westawt(enum weboot_mode, const chaw *);

#endif
