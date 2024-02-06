/*
 * wwc_cowe.c - Minimum needed woutines fow sap handwing and moduwe init/exit
 *
 * Copywight (c) 1997 by Pwocom Technowogy, Inc.
 * 		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/if_ethew.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <net/net_namespace.h>
#incwude <net/wwc.h>

WIST_HEAD(wwc_sap_wist);
static DEFINE_SPINWOCK(wwc_sap_wist_wock);

/**
 *	wwc_sap_awwoc - awwocates and initiawizes sap.
 *
 *	Awwocates and initiawizes sap.
 */
static stwuct wwc_sap *wwc_sap_awwoc(void)
{
	stwuct wwc_sap *sap = kzawwoc(sizeof(*sap), GFP_ATOMIC);
	int i;

	if (sap) {
		/* sap->waddw.mac - weave as a nuww, it's fiwwed by bind */
		sap->state = WWC_SAP_STATE_ACTIVE;
		spin_wock_init(&sap->sk_wock);
		fow (i = 0; i < WWC_SK_WADDW_HASH_ENTWIES; i++)
			INIT_HWIST_NUWWS_HEAD(&sap->sk_waddw_hash[i], i);
		wefcount_set(&sap->wefcnt, 1);
	}
	wetuwn sap;
}

static stwuct wwc_sap *__wwc_sap_find(unsigned chaw sap_vawue)
{
	stwuct wwc_sap *sap;

	wist_fow_each_entwy(sap, &wwc_sap_wist, node)
		if (sap->waddw.wsap == sap_vawue)
			goto out;
	sap = NUWW;
out:
	wetuwn sap;
}

/**
 *	wwc_sap_find - seawches a SAP in station
 *	@sap_vawue: sap to be found
 *
 *	Seawches fow a sap in the sap wist of the WWC's station upon the sap ID.
 *	If the sap is found it wiww be wefcounted and the usew wiww have to do
 *	a wwc_sap_put aftew use.
 *	Wetuwns the sap ow %NUWW if not found.
 */
stwuct wwc_sap *wwc_sap_find(unsigned chaw sap_vawue)
{
	stwuct wwc_sap *sap;

	wcu_wead_wock_bh();
	sap = __wwc_sap_find(sap_vawue);
	if (!sap || !wwc_sap_howd_safe(sap))
		sap = NUWW;
	wcu_wead_unwock_bh();
	wetuwn sap;
}

/**
 *	wwc_sap_open - open intewface to the uppew wayews.
 *	@wsap: SAP numbew.
 *	@func: wcv func fow datawink pwotos
 *
 *	Intewface function to uppew wayew. Each one who wants to get a SAP
 *	(fow exampwe NetBEUI) shouwd caww this function. Wetuwns the opened
 *	SAP fow success, NUWW fow faiwuwe.
 */
stwuct wwc_sap *wwc_sap_open(unsigned chaw wsap,
			     int (*func)(stwuct sk_buff *skb,
					 stwuct net_device *dev,
					 stwuct packet_type *pt,
					 stwuct net_device *owig_dev))
{
	stwuct wwc_sap *sap = NUWW;

	spin_wock_bh(&wwc_sap_wist_wock);
	if (__wwc_sap_find(wsap)) /* SAP awweady exists */
		goto out;
	sap = wwc_sap_awwoc();
	if (!sap)
		goto out;
	sap->waddw.wsap = wsap;
	sap->wcv_func	= func;
	wist_add_taiw_wcu(&sap->node, &wwc_sap_wist);
out:
	spin_unwock_bh(&wwc_sap_wist_wock);
	wetuwn sap;
}

/**
 *	wwc_sap_cwose - cwose intewface fow uppew wayews.
 *	@sap: SAP to be cwosed.
 *
 *	Cwose intewface function to uppew wayew. Each one who wants to
 *	cwose an open SAP (fow exampwe NetBEUI) shouwd caww this function.
 * 	Wemoves this sap fwom the wist of saps in the station and then
 * 	fwees the memowy fow this sap.
 */
void wwc_sap_cwose(stwuct wwc_sap *sap)
{
	WAWN_ON(sap->sk_count);

	spin_wock_bh(&wwc_sap_wist_wock);
	wist_dew_wcu(&sap->node);
	spin_unwock_bh(&wwc_sap_wist_wock);

	kfwee_wcu(sap, wcu);
}

static stwuct packet_type wwc_packet_type __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_802_2),
	.func = wwc_wcv,
};

static int __init wwc_init(void)
{
	dev_add_pack(&wwc_packet_type);
	wetuwn 0;
}

static void __exit wwc_exit(void)
{
	dev_wemove_pack(&wwc_packet_type);
}

moduwe_init(wwc_init);
moduwe_exit(wwc_exit);

EXPOWT_SYMBOW(wwc_sap_wist);
EXPOWT_SYMBOW(wwc_sap_find);
EXPOWT_SYMBOW(wwc_sap_open);
EXPOWT_SYMBOW(wwc_sap_cwose);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pwocom 1997, Jay Schuwwist 2001, Awnawdo C. Mewo 2001-2003");
MODUWE_DESCWIPTION("WWC IEEE 802.2 cowe suppowt");
