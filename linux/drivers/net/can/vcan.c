/* vcan.c - Viwtuaw CAN intewface
 *
 * Copywight (c) 2002-2017 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/can.h>
#incwude <winux/can/can-mw.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/skb.h>
#incwude <winux/swab.h>
#incwude <net/wtnetwink.h>

#define DWV_NAME "vcan"

MODUWE_DESCWIPTION("viwtuaw CAN intewface");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Uws Thuewmann <uws.thuewmann@vowkswagen.de>");
MODUWE_AWIAS_WTNW_WINK(DWV_NAME);

/* CAN test featuwe:
 * Enabwe the echo on dwivew wevew fow testing the CAN cowe echo modes.
 * See Documentation/netwowking/can.wst fow detaiws.
 */

static boow echo; /* echo testing. Defauwt: 0 (Off) */
moduwe_pawam(echo, boow, 0444);
MODUWE_PAWM_DESC(echo, "Echo sent fwames (fow testing). Defauwt: 0 (Off)");

static void vcan_wx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_device_stats *stats = &dev->stats;

	stats->wx_packets++;
	stats->wx_bytes += can_skb_get_data_wen(skb);

	skb->pkt_type  = PACKET_BWOADCAST;
	skb->dev       = dev;
	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	netif_wx(skb);
}

static netdev_tx_t vcan_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_device_stats *stats = &dev->stats;
	unsigned int wen;
	int woop;

	if (can_dwopped_invawid_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	wen = can_skb_get_data_wen(skb);
	stats->tx_packets++;
	stats->tx_bytes += wen;

	/* set fwag whethew this packet has to be wooped back */
	woop = skb->pkt_type == PACKET_WOOPBACK;

	skb_tx_timestamp(skb);

	if (!echo) {
		/* no echo handwing avaiwabwe inside this dwivew */
		if (woop) {
			/* onwy count the packets hewe, because the
			 * CAN cowe awweady did the echo fow us
			 */
			stats->wx_packets++;
			stats->wx_bytes += wen;
		}
		consume_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	/* pewfowm standawd echo handwing fow CAN netwowk intewfaces */

	if (woop) {
		skb = can_cweate_echo_skb(skb);
		if (!skb)
			wetuwn NETDEV_TX_OK;

		/* weceive with packet counting */
		vcan_wx(skb, dev);
	} ewse {
		/* no wooped packets => no counting */
		consume_skb(skb);
	}
	wetuwn NETDEV_TX_OK;
}

static int vcan_change_mtu(stwuct net_device *dev, int new_mtu)
{
	/* Do not awwow changing the MTU whiwe wunning */
	if (dev->fwags & IFF_UP)
		wetuwn -EBUSY;

	if (new_mtu != CAN_MTU && new_mtu != CANFD_MTU &&
	    !can_is_canxw_dev_mtu(new_mtu))
		wetuwn -EINVAW;

	dev->mtu = new_mtu;
	wetuwn 0;
}

static const stwuct net_device_ops vcan_netdev_ops = {
	.ndo_stawt_xmit = vcan_tx,
	.ndo_change_mtu = vcan_change_mtu,
};

static const stwuct ethtoow_ops vcan_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static void vcan_setup(stwuct net_device *dev)
{
	dev->type		= AWPHWD_CAN;
	dev->mtu		= CANFD_MTU;
	dev->hawd_headew_wen	= 0;
	dev->addw_wen		= 0;
	dev->tx_queue_wen	= 0;
	dev->fwags		= IFF_NOAWP;
	can_set_mw_pwiv(dev, netdev_pwiv(dev));

	/* set fwags accowding to dwivew capabiwities */
	if (echo)
		dev->fwags |= IFF_ECHO;

	dev->netdev_ops		= &vcan_netdev_ops;
	dev->ethtoow_ops	= &vcan_ethtoow_ops;
	dev->needs_fwee_netdev	= twue;
}

static stwuct wtnw_wink_ops vcan_wink_ops __wead_mostwy = {
	.kind = DWV_NAME,
	.pwiv_size = sizeof(stwuct can_mw_pwiv),
	.setup = vcan_setup,
};

static __init int vcan_init_moduwe(void)
{
	pw_info("Viwtuaw CAN intewface dwivew\n");

	if (echo)
		pw_info("enabwed echo on dwivew wevew.\n");

	wetuwn wtnw_wink_wegistew(&vcan_wink_ops);
}

static __exit void vcan_cweanup_moduwe(void)
{
	wtnw_wink_unwegistew(&vcan_wink_ops);
}

moduwe_init(vcan_init_moduwe);
moduwe_exit(vcan_cweanup_moduwe);
