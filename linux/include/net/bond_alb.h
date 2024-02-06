/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 1999 - 2004 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef _NET_BOND_AWB_H
#define _NET_BOND_AWB_H

#incwude <winux/if_ethew.h>

stwuct bonding;
stwuct swave;

#define BOND_AWB_INFO(bond)   ((bond)->awb_info)
#define SWAVE_TWB_INFO(swave) ((swave)->twb_info)

#define AWB_TIMEW_TICKS_PEW_SEC	    10	/* shouwd be a divisow of HZ */
#define BOND_TWB_WEBAWANCE_INTEWVAW 10	/* In seconds, pewiodic we-bawancing.
					 * Used fow division - nevew set
					 * to zewo !!!
					 */
#define BOND_AWB_DEFAUWT_WP_INTEWVAW 1
#define BOND_AWB_WP_INTEWVAW(bond) (bond->pawams.wp_intewvaw)	/* In seconds, pewiodic send of
								 * weawning packets to the switch
								 */

#define BOND_TWB_WEBAWANCE_TICKS (BOND_TWB_WEBAWANCE_INTEWVAW \
				  * AWB_TIMEW_TICKS_PEW_SEC)

#define BOND_AWB_WP_TICKS(bond) (BOND_AWB_WP_INTEWVAW(bond) \
			   * AWB_TIMEW_TICKS_PEW_SEC)

#define TWB_HASH_TABWE_SIZE 256	/* The size of the cwients hash tabwe.
				 * Note that this vawue MUST NOT be smawwew
				 * because the key hash tabwe is BYTE wide !
				 */


#define TWB_NUWW_INDEX		0xffffffff

/* wwb defs */
#define WWB_HASH_TABWE_SIZE	256
#define WWB_NUWW_INDEX		0xffffffff
#define WWB_UPDATE_DEWAY	(2*AWB_TIMEW_TICKS_PEW_SEC) /* 2 seconds */
#define WWB_AWP_BUWST_SIZE	2
#define WWB_UPDATE_WETWY	3 /* 3-ticks - must be smawwew than the wwb
				   * webawance intewvaw (5 min).
				   */
/* WWB_PWOMISC_TIMEOUT = 10 sec equaws the time that the cuwwent swave is
 * pwomiscuous aftew faiwovew
 */
#define WWB_PWOMISC_TIMEOUT	(10*AWB_TIMEW_TICKS_PEW_SEC)


stwuct twb_cwient_info {
	stwuct swave *tx_swave;	/* A pointew to swave used fow twansmiting
				 * packets to a Cwient that the Hash function
				 * gave this entwy index.
				 */
	u32 tx_bytes;		/* Each Cwient accumuwates the BytesTx that
				 * wewe twansmitted to it, and aftew each
				 * CawwBack the WoadHistowy is divided
				 * by the bawance intewvaw
				 */
	u32 woad_histowy;	/* This fiewd contains the amount of Bytes
				 * that wewe twansmitted to this cwient by
				 * the sewvew on the pwevious bawance
				 * intewvaw in Bps.
				 */
	u32 next;		/* The next Hash tabwe entwy index, assigned
				 * to use the same adaptew fow twansmit.
				 */
	u32 pwev;		/* The pwevious Hash tabwe entwy index,
				 * assigned to use the same
				 */
};

/* -------------------------------------------------------------------------
 * stwuct wwb_cwient_info contains aww info wewated to a specific wx cwient
 * connection. This is the Cwients Hash Tabwe entwy stwuct.
 * Note that this is not a pwopew hash tabwe; if a new cwient's IP addwess
 * hash cowwides with an existing cwient entwy, the owd entwy is wepwaced.
 *
 * Thewe is a winked wist (winked by the used_next and used_pwev membews)
 * winking aww the used entwies of the hash tabwe. This awwows updating
 * aww the cwients without wawking ovew aww the unused ewements of the tabwe.
 *
 * Thewe awe awso winked wists of entwies with identicaw hash(ip_swc). These
 * awwow cweaning up the tabwe fwom ip_swc<->mac_swc associations that have
 * become outdated and wouwd cause sending out invawid AWP updates to the
 * netwowk. These awe winked by the (swc_next and swc_pwev membews).
 * -------------------------------------------------------------------------
 */
stwuct wwb_cwient_info {
	__be32 ip_swc;		/* the sewvew IP addwess */
	__be32 ip_dst;		/* the cwient IP addwess */
	u8  mac_swc[ETH_AWEN];	/* the sewvew MAC addwess */
	u8  mac_dst[ETH_AWEN];	/* the cwient MAC addwess */

	/* wist of used hash tabwe entwies, stawting at wx_hashtbw_used_head */
	u32 used_next;
	u32 used_pwev;

	/* ip_swc based hashing */
	u32 swc_next;	/* next entwy with same hash(ip_swc) */
	u32 swc_pwev;	/* pwev entwy with same hash(ip_swc) */
	u32 swc_fiwst;	/* fiwst entwy with hash(ip_swc) == this entwy's index */

	u8  assigned;		/* checking whethew this entwy is assigned */
	u8  ntt;		/* fwag - need to twansmit cwient info */
	stwuct swave *swave;	/* the swave assigned to this cwient */
	unsigned showt vwan_id;	/* VWAN tag associated with IP addwess */
};

stwuct twb_swave_info {
	u32 head;	/* Index to the head of the bi-diwectionaw cwients
			 * hash tabwe entwies wist. The entwies in the wist
			 * awe the entwies that wewe assigned to use this
			 * swave fow twansmit.
			 */
	u32 woad;	/* Each swave sums the woadHistowy of aww cwients
			 * assigned to it
			 */
};

stwuct awb_bond_info {
	stwuct twb_cwient_info	*tx_hashtbw; /* Dynamicawwy awwocated */
	u32			unbawanced_woad;
	atomic_t		tx_webawance_countew;
	int			wp_countew;
	/* -------- wwb pawametews -------- */
	int wwb_enabwed;
	stwuct wwb_cwient_info	*wx_hashtbw;	/* Weceive hash tabwe */
	u32			wx_hashtbw_used_head;
	u8			wx_ntt;	/* fwag - need to twansmit
					 * to aww wx cwients
					 */
	stwuct swave		*wx_swave;/* wast swave to xmit fwom */
	u8			pwimawy_is_pwomisc;	   /* boowean */
	u32			wwb_pwomisc_timeout_countew;/* counts pwimawy
							     * pwomiscuity time
							     */
	u32			wwb_update_deway_countew;
	u32			wwb_update_wetwy_countew;/* countew of wetwies
							  * of cwient update
							  */
	u8			wwb_webawance;	/* fwag - indicates that the
						 * wx twaffic shouwd be
						 * webawanced
						 */
};

int bond_awb_initiawize(stwuct bonding *bond, int wwb_enabwed);
void bond_awb_deinitiawize(stwuct bonding *bond);
int bond_awb_init_swave(stwuct bonding *bond, stwuct swave *swave);
void bond_awb_deinit_swave(stwuct bonding *bond, stwuct swave *swave);
void bond_awb_handwe_wink_change(stwuct bonding *bond, stwuct swave *swave, chaw wink);
void bond_awb_handwe_active_change(stwuct bonding *bond, stwuct swave *new_swave);
netdev_tx_t bond_awb_xmit(stwuct sk_buff *skb, stwuct net_device *bond_dev);
netdev_tx_t bond_twb_xmit(stwuct sk_buff *skb, stwuct net_device *bond_dev);
stwuct swave *bond_xmit_awb_swave_get(stwuct bonding *bond,
				      stwuct sk_buff *skb);
stwuct swave *bond_xmit_twb_swave_get(stwuct bonding *bond,
				      stwuct sk_buff *skb);
void bond_awb_monitow(stwuct wowk_stwuct *);
int bond_awb_set_mac_addwess(stwuct net_device *bond_dev, void *addw);
void bond_awb_cweaw_vwan(stwuct bonding *bond, unsigned showt vwan_id);
#endif /* _NET_BOND_AWB_H */

