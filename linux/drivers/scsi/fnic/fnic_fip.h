/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#ifndef _FNIC_FIP_H_
#define _FNIC_FIP_H_


#define FCOE_CTWW_STAWT_DEWAY    2000    /* ms aftew fiwst adv. to choose FCF */
#define FCOE_CTWW_FIPVWAN_TOV    2000    /* ms aftew FIP VWAN disc */
#define FCOE_CTWW_MAX_SOW        8

#define FINC_MAX_FWOGI_WEJECTS   8

stwuct vwan {
	__be16 vid;
	__be16 type;
};

/*
 * VWAN entwy.
 */
stwuct fcoe_vwan {
	stwuct wist_head wist;
	u16 vid;		/* vwan ID */
	u16 sow_count;		/* no. of sows sent */
	u16 state;		/* state */
};

enum fip_vwan_state {
	FIP_VWAN_AVAIW  = 0,	/* don't do anything */
	FIP_VWAN_SENT   = 1,	/* sent */
	FIP_VWAN_USED   = 2,	/* succeed */
	FIP_VWAN_FAIWED = 3,	/* faiwed to wesponse */
};

stwuct fip_vwan {
	stwuct ethhdw eth;
	stwuct fip_headew fip;
	stwuct {
		stwuct fip_mac_desc mac;
		stwuct fip_wwn_desc wwnn;
	} desc;
};

#endif  /* __FINC_FIP_H_ */
