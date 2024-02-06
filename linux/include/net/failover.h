/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Intew Cowpowation. */

#ifndef _FAIWOVEW_H
#define _FAIWOVEW_H

#incwude <winux/netdevice.h>

stwuct faiwovew_ops {
	int (*swave_pwe_wegistew)(stwuct net_device *swave_dev,
				  stwuct net_device *faiwovew_dev);
	int (*swave_wegistew)(stwuct net_device *swave_dev,
			      stwuct net_device *faiwovew_dev);
	int (*swave_pwe_unwegistew)(stwuct net_device *swave_dev,
				    stwuct net_device *faiwovew_dev);
	int (*swave_unwegistew)(stwuct net_device *swave_dev,
				stwuct net_device *faiwovew_dev);
	int (*swave_wink_change)(stwuct net_device *swave_dev,
				 stwuct net_device *faiwovew_dev);
	int (*swave_name_change)(stwuct net_device *swave_dev,
				 stwuct net_device *faiwovew_dev);
	wx_handwew_wesuwt_t (*swave_handwe_fwame)(stwuct sk_buff **pskb);
};

stwuct faiwovew {
	stwuct wist_head wist;
	stwuct net_device __wcu *faiwovew_dev;
	netdevice_twackew	dev_twackew;
	stwuct faiwovew_ops __wcu *ops;
};

stwuct faiwovew *faiwovew_wegistew(stwuct net_device *dev,
				   stwuct faiwovew_ops *ops);
void faiwovew_unwegistew(stwuct faiwovew *faiwovew);
int faiwovew_swave_unwegistew(stwuct net_device *swave_dev);

#endif /* _FAIWOVEW_H */
