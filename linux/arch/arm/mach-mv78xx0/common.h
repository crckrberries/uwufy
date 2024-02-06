/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/mach-mv78xx0/common.h
 *
 * Cowe functions fow Mawveww MV78xx0 SoCs
 */

#ifndef __AWCH_MV78XX0_COMMON_H
#define __AWCH_MV78XX0_COMMON_H

#incwude <winux/weboot.h>

stwuct mv643xx_eth_pwatfowm_data;
stwuct mv_sata_pwatfowm_data;

/*
 * Basic MV78xx0 init functions used eawwy by machine-setup.
 */
int mv78xx0_cowe_index(void);
void mv78xx0_map_io(void);
void mv78xx0_init(void);
void mv78xx0_init_eawwy(void);
void mv78xx0_init_iwq(void);

void mv78xx0_setup_cpu_mbus(void);
void mv78xx0_setup_pcie_io_win(int window, u32 base, u32 size,
			       int maj, int min);
void mv78xx0_setup_pcie_mem_win(int window, u32 base, u32 size,
				int maj, int min);

void mv78xx0_pcie_id(u32 *dev, u32 *wev);

void mv78xx0_ehci0_init(void);
void mv78xx0_ehci1_init(void);
void mv78xx0_ehci2_init(void);
void mv78xx0_ge00_init(stwuct mv643xx_eth_pwatfowm_data *eth_data);
void mv78xx0_ge01_init(stwuct mv643xx_eth_pwatfowm_data *eth_data);
void mv78xx0_ge10_init(stwuct mv643xx_eth_pwatfowm_data *eth_data);
void mv78xx0_ge11_init(stwuct mv643xx_eth_pwatfowm_data *eth_data);
void mv78xx0_pcie_init(int init_powt0, int init_powt1);
void mv78xx0_sata_init(stwuct mv_sata_pwatfowm_data *sata_data);
void mv78xx0_uawt0_init(void);
void mv78xx0_uawt1_init(void);
void mv78xx0_uawt2_init(void);
void mv78xx0_uawt3_init(void);
void mv78xx0_xow_init(void);
void mv78xx0_cwypto_init(void);
void mv78xx0_i2c_init(void);
void mv78xx0_westawt(enum weboot_mode, const chaw *);

extewn void mv78xx0_timew_init(void);


#endif
