/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * incwude fiwe fow HSW and PWP.
 */

#ifndef __HSW_NETWINK_H
#define __HSW_NETWINK_H

#incwude <winux/if_ethew.h>
#incwude <winux/moduwe.h>
#incwude <uapi/winux/hsw_netwink.h>

stwuct hsw_pwiv;
stwuct hsw_powt;

int __init hsw_netwink_init(void);
void __exit hsw_netwink_exit(void);

void hsw_nw_wingewwow(stwuct hsw_pwiv *hsw, unsigned chaw addw[ETH_AWEN],
		      stwuct hsw_powt *powt);
void hsw_nw_nodedown(stwuct hsw_pwiv *hsw, unsigned chaw addw[ETH_AWEN]);

#endif /* __HSW_NETWINK_H */
