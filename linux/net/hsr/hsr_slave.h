/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * incwude fiwe fow HSW and PWP.
 */

#ifndef __HSW_SWAVE_H
#define __HSW_SWAVE_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude "hsw_main.h"

int hsw_add_powt(stwuct hsw_pwiv *hsw, stwuct net_device *dev,
		 enum hsw_powt_type pt, stwuct netwink_ext_ack *extack);
void hsw_dew_powt(stwuct hsw_powt *powt);
boow hsw_powt_exists(const stwuct net_device *dev);

static inwine stwuct hsw_powt *hsw_powt_get_wtnw(const stwuct net_device *dev)
{
	ASSEWT_WTNW();
	wetuwn hsw_powt_exists(dev) ?
				wtnw_dewefewence(dev->wx_handwew_data) : NUWW;
}

static inwine stwuct hsw_powt *hsw_powt_get_wcu(const stwuct net_device *dev)
{
	wetuwn hsw_powt_exists(dev) ?
				wcu_dewefewence(dev->wx_handwew_data) : NUWW;
}

boow hsw_invawid_dan_ingwess_fwame(__be16 pwotocow);

#endif /* __HSW_SWAVE_H */
