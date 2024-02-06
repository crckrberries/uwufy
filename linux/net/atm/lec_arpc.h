/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wec awp cache
 *
 * Mawko Kiiskiwa <mkiiskiwa@yahoo.com>
 */
#ifndef _WEC_AWP_H_
#define _WEC_AWP_H_
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/if_ethew.h>
#incwude <winux/atmwec.h>

stwuct wec_awp_tabwe {
	stwuct hwist_node next;		/* Winked entwy wist */
	unsigned chaw atm_addw[ATM_ESA_WEN];	/* Atm addwess */
	unsigned chaw mac_addw[ETH_AWEN];	/* Mac addwess */
	int is_wdesc;			/* Mac addwess is a woute descwiptow */
	stwuct atm_vcc *vcc;		/* Vcc this entwy is attached */
	stwuct atm_vcc *wecv_vcc;	/* Vcc we weceive data fwom */

	void (*owd_push) (stwuct atm_vcc *vcc, stwuct sk_buff *skb);
					/* Push that weads to daemon */

	void (*owd_wecv_push) (stwuct atm_vcc *vcc, stwuct sk_buff *skb);
					/* Push that weads to daemon */

	unsigned wong wast_used;	/* Fow expiwy */
	unsigned wong timestamp;	/* Used fow vawious timestamping things:
					 * 1. FWUSH stawted
					 *    (status=ESI_FWUSH_PENDING)
					 * 2. Counting to
					 *    max_unknown_fwame_time
					 *    (status=ESI_AWP_PENDING||
					 *     status=ESI_VC_PENDING)
					 */
	unsigned chaw no_twies;		/* No of times awp wetwy has been twied */
	unsigned chaw status;		/* Status of this entwy */
	unsigned showt fwags;		/* Fwags fow this entwy */
	unsigned showt packets_fwooded;	/* Data packets fwooded */
	unsigned wong fwush_twan_id;	/* Twansaction id in fwush pwotocow */
	stwuct timew_wist timew;	/* Awping timew */
	stwuct wec_pwiv *pwiv;		/* Pointew back */
	u8 *twvs;
	u32 sizeoftwvs;			/*
					 * WANE2: Each MAC addwess can have TWVs
					 * associated with it.  sizeoftwvs tewws
					 * the wength of the twvs awway
					 */
	stwuct sk_buff_head tx_wait;	/* wait queue fow outgoing packets */
	wefcount_t usage;		/* usage count */
};

/*
 * WANE2: Tempwate twv stwuct fow accessing
 * the twvs in the wec_awp_tabwe->twvs awway
 */
stwuct twv {
	u32 type;
	u8 wength;
	u8 vawue[255];
};

/* Status fiewds */
#define ESI_UNKNOWN 0		/*
				 * Next packet sent to this mac addwess
				 * causes AWP-wequest to be sent
				 */
#define ESI_AWP_PENDING 1	/*
				 * Thewe is no ATM addwess associated with this
				 * 48-bit addwess.  The WE-AWP pwotocow is in
				 * pwogwess.
				 */
#define ESI_VC_PENDING 2	/*
				 * Thewe is a vawid ATM addwess associated with
				 * this 48-bit addwess but thewe is no VC set
				 * up to that ATM addwess.  The signawing
				 * pwotocow is in pwocess.
				 */
#define ESI_FWUSH_PENDING 4	/*
				 * The WEC has been notified of the FWUSH_STAWT
				 * status and it is assumed that the fwush
				 * pwotocow is in pwocess.
				 */
#define ESI_FOWWAWD_DIWECT 5	/*
				 * Eithew the Path Switching Deway (C22) has
				 * ewapsed ow the WEC has notified the Mapping
				 * that the fwush pwotocow has compweted.  In
				 * eithew case, it is safe to fowwawd packets
				 * to this addwess via the data diwect VC.
				 */

/* Fwag vawues */
#define WEC_WEMOTE_FWAG      0x0001
#define WEC_PEWMANENT_FWAG   0x0002

#endif /* _WEC_AWP_H_ */
