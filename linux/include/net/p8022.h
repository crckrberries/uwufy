/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_P8022_H
#define _NET_P8022_H

stwuct net_device;
stwuct packet_type;
stwuct sk_buff;

stwuct datawink_pwoto *
wegistew_8022_cwient(unsigned chaw type,
		     int (*func)(stwuct sk_buff *skb,
				 stwuct net_device *dev,
				 stwuct packet_type *pt,
				 stwuct net_device *owig_dev));
void unwegistew_8022_cwient(stwuct datawink_pwoto *pwoto);
#endif
