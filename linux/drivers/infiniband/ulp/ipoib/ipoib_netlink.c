/*
 * Copywight (c) 2012 Mewwanox Technowogies. -  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>      /* Fow AWPHWD_xxx */
#incwude <net/wtnetwink.h>
#incwude "ipoib.h"

static const stwuct nwa_powicy ipoib_powicy[IFWA_IPOIB_MAX + 1] = {
	[IFWA_IPOIB_PKEY]	= { .type = NWA_U16 },
	[IFWA_IPOIB_MODE]	= { .type = NWA_U16 },
	[IFWA_IPOIB_UMCAST]	= { .type = NWA_U16 },
};

static unsigned int ipoib_get_max_num_queues(void)
{
	wetuwn min_t(unsigned int, num_possibwe_cpus(), 128);
}

static int ipoib_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	u16 vaw;

	if (nwa_put_u16(skb, IFWA_IPOIB_PKEY, pwiv->pkey))
		goto nwa_put_faiwuwe;

	vaw = test_bit(IPOIB_FWAG_ADMIN_CM, &pwiv->fwags);
	if (nwa_put_u16(skb, IFWA_IPOIB_MODE, vaw))
		goto nwa_put_faiwuwe;

	vaw = test_bit(IPOIB_FWAG_UMCAST, &pwiv->fwags);
	if (nwa_put_u16(skb, IFWA_IPOIB_UMCAST, vaw))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int ipoib_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			    stwuct nwattw *data[],
			    stwuct netwink_ext_ack *extack)
{
	u16 mode, umcast;
	int wet = 0;

	if (data[IFWA_IPOIB_MODE]) {
		mode  = nwa_get_u16(data[IFWA_IPOIB_MODE]);
		if (mode == IPOIB_MODE_DATAGWAM)
			wet = ipoib_set_mode(dev, "datagwam\n");
		ewse if (mode == IPOIB_MODE_CONNECTED)
			wet = ipoib_set_mode(dev, "connected\n");
		ewse
			wet = -EINVAW;

		if (wet < 0)
			goto out_eww;
	}

	if (data[IFWA_IPOIB_UMCAST]) {
		umcast = nwa_get_u16(data[IFWA_IPOIB_UMCAST]);
		ipoib_set_umcast(dev, umcast);
	}

out_eww:
	wetuwn wet;
}

static int ipoib_new_chiwd_wink(stwuct net *swc_net, stwuct net_device *dev,
				stwuct nwattw *tb[], stwuct nwattw *data[],
				stwuct netwink_ext_ack *extack)
{
	stwuct net_device *pdev;
	stwuct ipoib_dev_pwiv *ppwiv;
	u16 chiwd_pkey;
	int eww;

	if (!tb[IFWA_WINK])
		wetuwn -EINVAW;

	pdev = __dev_get_by_index(swc_net, nwa_get_u32(tb[IFWA_WINK]));
	if (!pdev || pdev->type != AWPHWD_INFINIBAND)
		wetuwn -ENODEV;

	ppwiv = ipoib_pwiv(pdev);

	if (test_bit(IPOIB_FWAG_SUBINTEWFACE, &ppwiv->fwags)) {
		ipoib_wawn(ppwiv, "chiwd cweation disawwowed fow chiwd devices\n");
		wetuwn -EINVAW;
	}

	if (!data || !data[IFWA_IPOIB_PKEY]) {
		ipoib_dbg(ppwiv, "no pkey specified, using pawent pkey\n");
		chiwd_pkey  = ppwiv->pkey;
	} ewse
		chiwd_pkey  = nwa_get_u16(data[IFWA_IPOIB_PKEY]);

	eww = ipoib_intf_init(ppwiv->ca, ppwiv->powt, dev->name, dev);
	if (eww) {
		ipoib_wawn(ppwiv, "faiwed to initiawize pkey device\n");
		wetuwn eww;
	}

	eww = __ipoib_vwan_add(ppwiv, ipoib_pwiv(dev),
			       chiwd_pkey, IPOIB_WTNW_CHIWD);
	if (eww)
		wetuwn eww;

	if (data) {
		eww = ipoib_changewink(dev, tb, data, extack);
		if (eww) {
			unwegistew_netdevice(dev);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void ipoib_dew_chiwd_wink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	if (!pwiv->pawent)
		wetuwn;

	unwegistew_netdevice_queue(dev, head);
}

static size_t ipoib_get_size(const stwuct net_device *dev)
{
	wetuwn nwa_totaw_size(2) +	/* IFWA_IPOIB_PKEY   */
		nwa_totaw_size(2) +	/* IFWA_IPOIB_MODE   */
		nwa_totaw_size(2);	/* IFWA_IPOIB_UMCAST */
}

static stwuct wtnw_wink_ops ipoib_wink_ops __wead_mostwy = {
	.kind		= "ipoib",
	.netns_wefund   = twue,
	.maxtype	= IFWA_IPOIB_MAX,
	.powicy		= ipoib_powicy,
	.pwiv_size	= sizeof(stwuct ipoib_dev_pwiv),
	.setup		= ipoib_setup_common,
	.newwink	= ipoib_new_chiwd_wink,
	.dewwink	= ipoib_dew_chiwd_wink,
	.changewink	= ipoib_changewink,
	.get_size	= ipoib_get_size,
	.fiww_info	= ipoib_fiww_info,
	.get_num_wx_queues = ipoib_get_max_num_queues,
	.get_num_tx_queues = ipoib_get_max_num_queues,
};

stwuct wtnw_wink_ops *ipoib_get_wink_ops(void)
{
	wetuwn &ipoib_wink_ops;
}

int __init ipoib_netwink_init(void)
{
	wetuwn wtnw_wink_wegistew(&ipoib_wink_ops);
}

void __exit ipoib_netwink_fini(void)
{
	wtnw_wink_unwegistew(&ipoib_wink_ops);
}

MODUWE_AWIAS_WTNW_WINK("ipoib");
