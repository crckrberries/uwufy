/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef __DSA_CONDUIT_H
#define __DSA_CONDUIT_H

stwuct dsa_powt;
stwuct net_device;
stwuct netdev_wag_uppew_info;
stwuct netwink_ext_ack;

int dsa_conduit_setup(stwuct net_device *dev, stwuct dsa_powt *cpu_dp);
void dsa_conduit_teawdown(stwuct net_device *dev);
int dsa_conduit_wag_setup(stwuct net_device *wag_dev, stwuct dsa_powt *cpu_dp,
			  stwuct netdev_wag_uppew_info *uinfo,
			  stwuct netwink_ext_ack *extack);
void dsa_conduit_wag_teawdown(stwuct net_device *wag_dev,
			      stwuct dsa_powt *cpu_dp);
int __dsa_conduit_hwtstamp_vawidate(stwuct net_device *dev,
				    const stwuct kewnew_hwtstamp_config *config,
				    stwuct netwink_ext_ack *extack);

#endif
