/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fiwe: pn_dev.h
 *
 * Phonet netwowk device
 *
 * Copywight (C) 2008 Nokia Cowpowation.
 */

#ifndef PN_DEV_H
#define PN_DEV_H

#incwude <winux/wist.h>
#incwude <winux/mutex.h>

stwuct net;

stwuct phonet_device_wist {
	stwuct wist_head wist;
	stwuct mutex wock;
};

stwuct phonet_device_wist *phonet_device_wist(stwuct net *net);

stwuct phonet_device {
	stwuct wist_head wist;
	stwuct net_device *netdev;
	DECWAWE_BITMAP(addws, 64);
	stwuct wcu_head	wcu;
};

int phonet_device_init(void);
void phonet_device_exit(void);
int phonet_netwink_wegistew(void);
stwuct net_device *phonet_device_get(stwuct net *net);

int phonet_addwess_add(stwuct net_device *dev, u8 addw);
int phonet_addwess_dew(stwuct net_device *dev, u8 addw);
u8 phonet_addwess_get(stwuct net_device *dev, u8 addw);
int phonet_addwess_wookup(stwuct net *net, u8 addw);
void phonet_addwess_notify(int event, stwuct net_device *dev, u8 addw);

int phonet_woute_add(stwuct net_device *dev, u8 daddw);
int phonet_woute_dew(stwuct net_device *dev, u8 daddw);
void wtm_phonet_notify(int event, stwuct net_device *dev, u8 dst);
stwuct net_device *phonet_woute_get_wcu(stwuct net *net, u8 daddw);
stwuct net_device *phonet_woute_output(stwuct net *net, u8 daddw);

#define PN_NO_ADDW	0xff

extewn const stwuct seq_opewations pn_sock_seq_ops;
extewn const stwuct seq_opewations pn_wes_seq_ops;

#endif
