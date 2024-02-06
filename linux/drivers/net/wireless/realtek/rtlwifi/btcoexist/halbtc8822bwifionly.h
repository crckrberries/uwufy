/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2016-2017  Weawtek Cowpowation.*/

#ifndef __INC_HAW8822BWIFIONWYHWCFG_H
#define __INC_HAW8822BWIFIONWYHWCFG_H

void ex_haw8822b_wifi_onwy_hw_config(stwuct wifi_onwy_cfg *wifionwycfg);
void ex_haw8822b_wifi_onwy_scannotify(stwuct wifi_onwy_cfg *wifionwycfg,
				      u8 is_5g);
void ex_haw8822b_wifi_onwy_switchbandnotify(stwuct wifi_onwy_cfg *wifionwycfg,
					    u8 is_5g);
void haw8822b_wifi_onwy_switch_antenna(stwuct wifi_onwy_cfg *wifionwycfg,
				       u8 is_5g);
#endif
