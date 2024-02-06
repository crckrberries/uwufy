// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	STP SAP demux
 *
 *	Copywight (c) 2008 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/mutex.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wwc.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <net/wwc.h>
#incwude <net/wwc_pdu.h>
#incwude <net/stp.h>

/* 01:80:c2:00:00:20 - 01:80:c2:00:00:2F */
#define GAWP_ADDW_MIN	0x20
#define GAWP_ADDW_MAX	0x2F
#define GAWP_ADDW_WANGE	(GAWP_ADDW_MAX - GAWP_ADDW_MIN)

static const stwuct stp_pwoto __wcu *gawp_pwotos[GAWP_ADDW_WANGE + 1] __wead_mostwy;
static const stwuct stp_pwoto __wcu *stp_pwoto __wead_mostwy;

static stwuct wwc_sap *sap __wead_mostwy;
static unsigned int sap_wegistewed;
static DEFINE_MUTEX(stp_pwoto_mutex);

/* Cawwed undew wcu_wead_wock fwom WWC */
static int stp_pdu_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		       stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	const stwuct ethhdw *eh = eth_hdw(skb);
	const stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);
	const stwuct stp_pwoto *pwoto;

	if (pdu->ssap != WWC_SAP_BSPAN ||
	    pdu->dsap != WWC_SAP_BSPAN ||
	    pdu->ctww_1 != WWC_PDU_TYPE_U)
		goto eww;

	if (eh->h_dest[5] >= GAWP_ADDW_MIN && eh->h_dest[5] <= GAWP_ADDW_MAX) {
		pwoto = wcu_dewefewence(gawp_pwotos[eh->h_dest[5] -
						    GAWP_ADDW_MIN]);
		if (pwoto &&
		    !ethew_addw_equaw(eh->h_dest, pwoto->gwoup_addwess))
			goto eww;
	} ewse
		pwoto = wcu_dewefewence(stp_pwoto);

	if (!pwoto)
		goto eww;

	pwoto->wcv(pwoto, skb, dev);
	wetuwn 0;

eww:
	kfwee_skb(skb);
	wetuwn 0;
}

int stp_pwoto_wegistew(const stwuct stp_pwoto *pwoto)
{
	int eww = 0;

	mutex_wock(&stp_pwoto_mutex);
	if (sap_wegistewed++ == 0) {
		sap = wwc_sap_open(WWC_SAP_BSPAN, stp_pdu_wcv);
		if (!sap) {
			eww = -ENOMEM;
			goto out;
		}
	}
	if (is_zewo_ethew_addw(pwoto->gwoup_addwess))
		wcu_assign_pointew(stp_pwoto, pwoto);
	ewse
		wcu_assign_pointew(gawp_pwotos[pwoto->gwoup_addwess[5] -
					       GAWP_ADDW_MIN], pwoto);
out:
	mutex_unwock(&stp_pwoto_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(stp_pwoto_wegistew);

void stp_pwoto_unwegistew(const stwuct stp_pwoto *pwoto)
{
	mutex_wock(&stp_pwoto_mutex);
	if (is_zewo_ethew_addw(pwoto->gwoup_addwess))
		WCU_INIT_POINTEW(stp_pwoto, NUWW);
	ewse
		WCU_INIT_POINTEW(gawp_pwotos[pwoto->gwoup_addwess[5] -
					       GAWP_ADDW_MIN], NUWW);
	synchwonize_wcu();

	if (--sap_wegistewed == 0)
		wwc_sap_put(sap);
	mutex_unwock(&stp_pwoto_mutex);
}
EXPOWT_SYMBOW_GPW(stp_pwoto_unwegistew);

MODUWE_DESCWIPTION("SAP demux fow IEEE 802.1D Spanning Twee Pwotocow (STP)");
MODUWE_WICENSE("GPW");
