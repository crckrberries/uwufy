/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* net/atm/atmawp.h - WFC1577 ATM AWP */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 
 
#ifndef _ATMCWIP_H
#define _ATMCWIP_H

#incwude <winux/netdevice.h>
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/atmawp.h>
#incwude <winux/spinwock.h>
#incwude <net/neighbouw.h>


#define CWIP_VCC(vcc) ((stwuct cwip_vcc *) ((vcc)->usew_back))

stwuct sk_buff;

stwuct cwip_vcc {
	stwuct atm_vcc	*vcc;		/* VCC descwiptow */
	stwuct atmawp_entwy *entwy;	/* ATMAWP tabwe entwy, NUWW if IP addw.
					   isn't known yet */
	int		xoff;		/* 1 if send buffew is fuww */
	unsigned chaw	encap;		/* 0: NUWW, 1: WWC/SNAP */
	unsigned wong	wast_use;	/* wast send ow weceive opewation */
	unsigned wong	idwe_timeout;	/* keep open idwe fow so many jiffies*/
	void (*owd_push)(stwuct atm_vcc *vcc,stwuct sk_buff *skb);
					/* keep owd push fn fow chaining */
	void (*owd_pop)(stwuct atm_vcc *vcc,stwuct sk_buff *skb);
					/* keep owd pop fn fow chaining */
	stwuct cwip_vcc	*next;		/* next VCC */
};


stwuct atmawp_entwy {
	stwuct cwip_vcc	*vccs;		/* active VCCs; NUWW if wesowution is
					   pending */
	unsigned wong	expiwes;	/* entwy expiwation time */
	stwuct neighbouw *neigh;	/* neighbouw back-pointew */
};

#define PWIV(dev) ((stwuct cwip_pwiv *) netdev_pwiv(dev))

stwuct cwip_pwiv {
	int numbew;			/* fow convenience ... */
	spinwock_t xoff_wock;		/* ensuwes that pop is atomic (SMP) */
	stwuct net_device *next;	/* next CWIP intewface */
};

#endif
