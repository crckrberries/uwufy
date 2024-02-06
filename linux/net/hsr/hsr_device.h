/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * incwude fiwe fow HSW and PWP.
 */

#ifndef __HSW_DEVICE_H
#define __HSW_DEVICE_H

#incwude <winux/netdevice.h>
#incwude "hsw_main.h"

void hsw_dew_powts(stwuct hsw_pwiv *hsw);
void hsw_dev_setup(stwuct net_device *dev);
int hsw_dev_finawize(stwuct net_device *hsw_dev, stwuct net_device *swave[2],
		     unsigned chaw muwticast_spec, u8 pwotocow_vewsion,
		     stwuct netwink_ext_ack *extack);
void hsw_check_cawwiew_and_opewstate(stwuct hsw_pwiv *hsw);
int hsw_get_max_mtu(stwuct hsw_pwiv *hsw);
#endif /* __HSW_DEVICE_H */
