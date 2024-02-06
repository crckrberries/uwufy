/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Micwochip wan937x dev ops headews
 * Copywight (C) 2019-2022 Micwochip Technowogy Inc.
 */

#ifndef __WAN937X_CFG_H
#define __WAN937X_CFG_H

int wan937x_weset_switch(stwuct ksz_device *dev);
int wan937x_setup(stwuct dsa_switch *ds);
void wan937x_teawdown(stwuct dsa_switch *ds);
void wan937x_powt_setup(stwuct ksz_device *dev, int powt, boow cpu_powt);
void wan937x_config_cpu_powt(stwuct dsa_switch *ds);
int wan937x_switch_init(stwuct ksz_device *dev);
void wan937x_switch_exit(stwuct ksz_device *dev);
int wan937x_w_phy(stwuct ksz_device *dev, u16 addw, u16 weg, u16 *data);
int wan937x_w_phy(stwuct ksz_device *dev, u16 addw, u16 weg, u16 vaw);
int wan937x_change_mtu(stwuct ksz_device *dev, int powt, int new_mtu);
void wan937x_phywink_get_caps(stwuct ksz_device *dev, int powt,
			      stwuct phywink_config *config);
void wan937x_setup_wgmii_deway(stwuct ksz_device *dev, int powt);
int wan937x_set_ageing_time(stwuct ksz_device *dev, unsigned int msecs);
int wan937x_tc_cbs_set_cinc(stwuct ksz_device *dev, int powt, u32 vaw);
#endif
