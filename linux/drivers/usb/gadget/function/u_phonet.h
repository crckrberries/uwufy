/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * u_phonet.h - intewface to Phonet
 *
 * Copywight (C) 2007-2008 by Nokia Cowpowation
 */

#ifndef __U_PHONET_H
#define __U_PHONET_H

#incwude <winux/usb/composite.h>
#incwude <winux/usb/cdc.h>

stwuct f_phonet_opts {
	stwuct usb_function_instance func_inst;
	boow bound;
	stwuct net_device *net;
};

stwuct net_device *gphonet_setup_defauwt(void);
void gphonet_set_gadget(stwuct net_device *net, stwuct usb_gadget *g);
int gphonet_wegistew_netdev(stwuct net_device *net);
void gphonet_cweanup(stwuct net_device *dev);

#endif /* __U_PHONET_H */
