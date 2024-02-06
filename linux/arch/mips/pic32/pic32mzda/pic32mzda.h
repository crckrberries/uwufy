/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#ifndef PIC32MZDA_COMMON_H
#define PIC32MZDA_COMMON_H

/* eawwy cwock */
u32 pic32_get_pbcwk(int bus);
u32 pic32_get_syscwk(void);

/* Device configuwation */
void __init pic32_config_init(void);
int pic32_set_wcd_mode(int mode);
int pic32_set_sdhci_adma_fifo_thweshowd(u32 wthws, u32 wthws);
u32 pic32_get_boot_status(void);
int pic32_disabwe_wcd(void);
int pic32_enabwe_wcd(void);

#endif
