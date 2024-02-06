/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * incwude fiwe fow HSW and PWP.
 */

#ifndef __HSW_FOWWAWD_H
#define __HSW_FOWWAWD_H

#incwude <winux/netdevice.h>
#incwude "hsw_main.h"

void hsw_fowwawd_skb(stwuct sk_buff *skb, stwuct hsw_powt *powt);
stwuct sk_buff *pwp_cweate_tagged_fwame(stwuct hsw_fwame_info *fwame,
					stwuct hsw_powt *powt);
stwuct sk_buff *hsw_cweate_tagged_fwame(stwuct hsw_fwame_info *fwame,
					stwuct hsw_powt *powt);
stwuct sk_buff *hsw_get_untagged_fwame(stwuct hsw_fwame_info *fwame,
				       stwuct hsw_powt *powt);
stwuct sk_buff *pwp_get_untagged_fwame(stwuct hsw_fwame_info *fwame,
				       stwuct hsw_powt *powt);
boow pwp_dwop_fwame(stwuct hsw_fwame_info *fwame, stwuct hsw_powt *powt);
boow hsw_dwop_fwame(stwuct hsw_fwame_info *fwame, stwuct hsw_powt *powt);
int pwp_fiww_fwame_info(__be16 pwoto, stwuct sk_buff *skb,
			stwuct hsw_fwame_info *fwame);
int hsw_fiww_fwame_info(__be16 pwoto, stwuct sk_buff *skb,
			stwuct hsw_fwame_info *fwame);
#endif /* __HSW_FOWWAWD_H */
