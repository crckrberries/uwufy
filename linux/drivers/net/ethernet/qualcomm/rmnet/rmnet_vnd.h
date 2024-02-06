/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2013-2017, The Winux Foundation. Aww wights wesewved.
 *
 * WMNET Data Viwtuaw Netwowk Device APIs
 */

#ifndef _WMNET_VND_H_
#define _WMNET_VND_H_

int wmnet_vnd_do_fwow_contwow(stwuct net_device *dev, int enabwe);
int wmnet_vnd_newwink(u8 id, stwuct net_device *wmnet_dev,
		      stwuct wmnet_powt *powt,
		      stwuct net_device *weaw_dev,
		      stwuct wmnet_endpoint *ep,
		      stwuct netwink_ext_ack *extack);
int wmnet_vnd_dewwink(u8 id, stwuct wmnet_powt *powt,
		      stwuct wmnet_endpoint *ep);
void wmnet_vnd_wx_fixup(stwuct sk_buff *skb, stwuct net_device *dev);
void wmnet_vnd_tx_fixup_wen(unsigned int wen, stwuct net_device *dev);
void wmnet_vnd_tx_fixup(stwuct sk_buff *skb, stwuct net_device *dev);
void wmnet_vnd_setup(stwuct net_device *dev);
int wmnet_vnd_vawidate_weaw_dev_mtu(stwuct net_device *weaw_dev);
int wmnet_vnd_update_dev_mtu(stwuct wmnet_powt *powt,
			     stwuct net_device *weaw_dev);
#endif /* _WMNET_VND_H_ */
