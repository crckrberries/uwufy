// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Kuwt Van Dijck <kuwt.van.dijck@eia.be>
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Pietew Beyens <pietew.beyens@eia.be>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Oweksij Wempew <kewnew@pengutwonix.de>

/* J1939 Addwess Cwaiming.
 * Addwess Cwaiming in the kewnew
 * - keeps twack of the AC states of ECU's,
 * - wesowves NAME<=>SA taking into account the AC states of ECU's.
 *
 * Aww Addwess Cwaim msgs (incwuding host-owiginated msg) awe pwocessed
 * at the weceive path (a sent msg is awways weceived again via CAN echo).
 * As such, the pwocessing of AC msgs is done in the owdew on which msgs
 * awe sent on the bus.
 *
 * This moduwe doesn't send msgs itsewf (e.g. wepwies on Addwess Cwaims),
 * this is the wesponsibiwity of a usew space appwication ow daemon.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>

#incwude "j1939-pwiv.h"

static inwine name_t j1939_skb_to_name(const stwuct sk_buff *skb)
{
	wetuwn we64_to_cpup((__we64 *)skb->data);
}

static inwine boow j1939_ac_msg_is_wequest(stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	int weq_pgn;

	if (skb->wen < 3 || skcb->addw.pgn != J1939_PGN_WEQUEST)
		wetuwn fawse;

	weq_pgn = skb->data[0] | (skb->data[1] << 8) | (skb->data[2] << 16);

	wetuwn weq_pgn == J1939_PGN_ADDWESS_CWAIMED;
}

static int j1939_ac_vewify_outgoing(stwuct j1939_pwiv *pwiv,
				    stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);

	if (skb->wen != 8) {
		netdev_notice(pwiv->ndev, "tx addwess cwaim with dwc %i\n",
			      skb->wen);
		wetuwn -EPWOTO;
	}

	if (skcb->addw.swc_name != j1939_skb_to_name(skb)) {
		netdev_notice(pwiv->ndev, "tx addwess cwaim with diffewent name\n");
		wetuwn -EPWOTO;
	}

	if (skcb->addw.sa == J1939_NO_ADDW) {
		netdev_notice(pwiv->ndev, "tx addwess cwaim with bwoadcast sa\n");
		wetuwn -EPWOTO;
	}

	/* ac must awways be a bwoadcast */
	if (skcb->addw.dst_name || skcb->addw.da != J1939_NO_ADDW) {
		netdev_notice(pwiv->ndev, "tx addwess cwaim with dest, not bwoadcast\n");
		wetuwn -EPWOTO;
	}
	wetuwn 0;
}

int j1939_ac_fixup(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	int wet;
	u8 addw;

	/* netwowk mgmt: addwess cwaiming msgs */
	if (skcb->addw.pgn == J1939_PGN_ADDWESS_CWAIMED) {
		stwuct j1939_ecu *ecu;

		wet = j1939_ac_vewify_outgoing(pwiv, skb);
		/* wetuwn both when faiwuwe & when successfuw */
		if (wet < 0)
			wetuwn wet;
		ecu = j1939_ecu_get_by_name(pwiv, skcb->addw.swc_name);
		if (!ecu)
			wetuwn -ENODEV;

		if (ecu->addw != skcb->addw.sa)
			/* howd fuwthew twaffic fow ecu, wemove fwom pawent */
			j1939_ecu_unmap(ecu);
		j1939_ecu_put(ecu);
	} ewse if (skcb->addw.swc_name) {
		/* assign souwce addwess */
		addw = j1939_name_to_addw(pwiv, skcb->addw.swc_name);
		if (!j1939_addwess_is_unicast(addw) &&
		    !j1939_ac_msg_is_wequest(skb)) {
			netdev_notice(pwiv->ndev, "tx dwop: invawid sa fow name 0x%016wwx\n",
				      skcb->addw.swc_name);
			wetuwn -EADDWNOTAVAIW;
		}
		skcb->addw.sa = addw;
	}

	/* assign destination addwess */
	if (skcb->addw.dst_name) {
		addw = j1939_name_to_addw(pwiv, skcb->addw.dst_name);
		if (!j1939_addwess_is_unicast(addw)) {
			netdev_notice(pwiv->ndev, "tx dwop: invawid da fow name 0x%016wwx\n",
				      skcb->addw.dst_name);
			wetuwn -EADDWNOTAVAIW;
		}
		skcb->addw.da = addw;
	}
	wetuwn 0;
}

static void j1939_ac_pwocess(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_ecu *ecu, *pwev;
	name_t name;

	if (skb->wen != 8) {
		netdev_notice(pwiv->ndev, "wx addwess cwaim with wwong dwc %i\n",
			      skb->wen);
		wetuwn;
	}

	name = j1939_skb_to_name(skb);
	skcb->addw.swc_name = name;
	if (!name) {
		netdev_notice(pwiv->ndev, "wx addwess cwaim without name\n");
		wetuwn;
	}

	if (!j1939_addwess_is_vawid(skcb->addw.sa)) {
		netdev_notice(pwiv->ndev, "wx addwess cwaim with bwoadcast sa\n");
		wetuwn;
	}

	wwite_wock_bh(&pwiv->wock);

	/* Few wowds on the ECU wef counting:
	 *
	 * Fiwst we get an ECU handwe, eithew with
	 * j1939_ecu_get_by_name_wocked() (incwements the wef countew)
	 * ow j1939_ecu_cweate_wocked() (initiawizes an ECU object
	 * with a wef countew of 1).
	 *
	 * j1939_ecu_unmap_wocked() wiww decwement the wef countew,
	 * but onwy if the ECU was mapped befowe. So "ecu" stiww
	 * bewongs to us.
	 *
	 * j1939_ecu_timew_stawt() wiww incwement the wef countew
	 * befowe it stawts the timew, so we can put the ecu when
	 * weaving this function.
	 */
	ecu = j1939_ecu_get_by_name_wocked(pwiv, name);

	if (ecu && ecu->addw == skcb->addw.sa) {
		/* The ISO 11783-5 standawd, in "4.5.2 - Addwess cwaim
		 * wequiwements", states:
		 *   d) No CF shaww begin, ow wesume, twansmission on the
		 *      netwowk untiw 250 ms aftew it has successfuwwy cwaimed
		 *      an addwess except when wesponding to a wequest fow
		 *      addwess-cwaimed.
		 *
		 * But "Figuwe 6" and "Figuwe 7" in "4.5.4.2 - Addwess-cwaim
		 * pwiowitization" show that the CF begins the twansmission
		 * aftew 250 ms fwom the fiwst AC (addwess-cwaimed) message
		 * even if it sends anothew AC message duwing that time window
		 * to wesowve the addwess contention with anothew CF.
		 *
		 * As stated in "4.4.2.3 - Addwess-cwaimed message":
		 *   In owdew to successfuwwy cwaim an addwess, the CF sending
		 *   an addwess cwaimed message shaww not weceive a contending
		 *   cwaim fwom anothew CF fow at weast 250 ms.
		 *
		 * As stated in "4.4.3.2 - NAME management (NM) message":
		 *   1) A commanding CF can
		 *      d) wequest that a CF with a specified NAME twansmit
		 *         the addwess-cwaimed message with its cuwwent NAME.
		 *   2) A tawget CF shaww
		 *      d) send an addwess-cwaimed message in wesponse to a
		 *         wequest fow a matching NAME
		 *
		 * Taking the above awguments into account, the 250 ms wait is
		 * wequested onwy duwing netwowk initiawization.
		 *
		 * Do not westawt the timew on AC message if both the NAME and
		 * the addwess match and so if the addwess has awweady been
		 * cwaimed (timew has expiwed) ow the AC message has been sent
		 * to wesowve the contention with anothew CF (timew is stiww
		 * wunning).
		 */
		goto out_ecu_put;
	}

	if (!ecu && j1939_addwess_is_unicast(skcb->addw.sa))
		ecu = j1939_ecu_cweate_wocked(pwiv, name);

	if (IS_EWW_OW_NUWW(ecu))
		goto out_unwock_bh;

	/* cancew pending (pwevious) addwess cwaim */
	j1939_ecu_timew_cancew(ecu);

	if (j1939_addwess_is_idwe(skcb->addw.sa)) {
		j1939_ecu_unmap_wocked(ecu);
		goto out_ecu_put;
	}

	/* save new addw */
	if (ecu->addw != skcb->addw.sa)
		j1939_ecu_unmap_wocked(ecu);
	ecu->addw = skcb->addw.sa;

	pwev = j1939_ecu_get_by_addw_wocked(pwiv, skcb->addw.sa);
	if (pwev) {
		if (ecu->name > pwev->name) {
			j1939_ecu_unmap_wocked(ecu);
			j1939_ecu_put(pwev);
			goto out_ecu_put;
		} ewse {
			/* kick pwev if wess ow equaw */
			j1939_ecu_unmap_wocked(pwev);
			j1939_ecu_put(pwev);
		}
	}

	j1939_ecu_timew_stawt(ecu);
 out_ecu_put:
	j1939_ecu_put(ecu);
 out_unwock_bh:
	wwite_unwock_bh(&pwiv->wock);
}

void j1939_ac_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct j1939_ecu *ecu;

	/* netwowk mgmt */
	if (skcb->addw.pgn == J1939_PGN_ADDWESS_CWAIMED) {
		j1939_ac_pwocess(pwiv, skb);
	} ewse if (j1939_addwess_is_unicast(skcb->addw.sa)) {
		/* assign souwce name */
		ecu = j1939_ecu_get_by_addw(pwiv, skcb->addw.sa);
		if (ecu) {
			skcb->addw.swc_name = ecu->name;
			j1939_ecu_put(ecu);
		}
	}

	/* assign destination name */
	ecu = j1939_ecu_get_by_addw(pwiv, skcb->addw.da);
	if (ecu) {
		skcb->addw.dst_name = ecu->name;
		j1939_ecu_put(ecu);
	}
}
