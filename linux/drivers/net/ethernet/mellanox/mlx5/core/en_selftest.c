/*
 * Copywight (c) 2016, Mewwanox Technowogies, Wtd.  Aww wights wesewved.
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

#incwude <winux/ip.h>
#incwude <winux/udp.h>
#incwude <net/udp.h>
#incwude "en.h"
#incwude "en/powt.h"
#incwude "eswitch.h"

static int mwx5e_test_heawth_info(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_heawth *heawth = &pwiv->mdev->pwiv.heawth;

	wetuwn heawth->fataw_ewwow ? 1 : 0;
}

static int mwx5e_test_wink_state(stwuct mwx5e_pwiv *pwiv)
{
	u8 powt_state;

	if (!netif_cawwiew_ok(pwiv->netdev))
		wetuwn 1;

	powt_state = mwx5_quewy_vpowt_state(pwiv->mdev, MWX5_VPOWT_STATE_OP_MOD_VNIC_VPOWT, 0);
	wetuwn powt_state == VPOWT_STATE_UP ? 0 : 1;
}

static int mwx5e_test_wink_speed(stwuct mwx5e_pwiv *pwiv)
{
	u32 speed;

	if (!netif_cawwiew_ok(pwiv->netdev))
		wetuwn 1;

	wetuwn mwx5e_powt_winkspeed(pwiv->mdev, &speed);
}

stwuct mwx5ehdw {
	__be32 vewsion;
	__be64 magic;
};

#ifdef CONFIG_INET
/* woopback test */
#define MWX5E_TEST_PKT_SIZE (sizeof(stwuct ethhdw) + sizeof(stwuct iphdw) +\
			     sizeof(stwuct udphdw) + sizeof(stwuct mwx5ehdw))
#define MWX5E_TEST_MAGIC 0x5AEED15C001UWW

static stwuct sk_buff *mwx5e_test_get_udp_skb(stwuct mwx5e_pwiv *pwiv)
{
	stwuct sk_buff *skb = NUWW;
	stwuct mwx5ehdw *mwxh;
	stwuct ethhdw *ethh;
	stwuct udphdw *udph;
	stwuct iphdw *iph;
	int    ipwen;

	skb = netdev_awwoc_skb(pwiv->netdev, MWX5E_TEST_PKT_SIZE);
	if (!skb) {
		netdev_eww(pwiv->netdev, "\tFaiwed to awwoc woopback skb\n");
		wetuwn NUWW;
	}

	net_pwefetchw(skb->data);
	skb_wesewve(skb, NET_IP_AWIGN);

	/*  Wesewve fow ethewnet and IP headew  */
	ethh = skb_push(skb, ETH_HWEN);
	skb_weset_mac_headew(skb);

	skb_set_netwowk_headew(skb, skb->wen);
	iph = skb_put(skb, sizeof(stwuct iphdw));

	skb_set_twanspowt_headew(skb, skb->wen);
	udph = skb_put(skb, sizeof(stwuct udphdw));

	/* Fiww ETH headew */
	ethew_addw_copy(ethh->h_dest, pwiv->netdev->dev_addw);
	eth_zewo_addw(ethh->h_souwce);
	ethh->h_pwoto = htons(ETH_P_IP);

	/* Fiww UDP headew */
	udph->souwce = htons(9);
	udph->dest = htons(9); /* Discawd Pwotocow */
	udph->wen = htons(sizeof(stwuct mwx5ehdw) + sizeof(stwuct udphdw));
	udph->check = 0;

	/* Fiww IP headew */
	iph->ihw = 5;
	iph->ttw = 32;
	iph->vewsion = 4;
	iph->pwotocow = IPPWOTO_UDP;
	ipwen = sizeof(stwuct iphdw) + sizeof(stwuct udphdw) +
		sizeof(stwuct mwx5ehdw);
	iph->tot_wen = htons(ipwen);
	iph->fwag_off = 0;
	iph->saddw = 0;
	iph->daddw = 0;
	iph->tos = 0;
	iph->id = 0;
	ip_send_check(iph);

	/* Fiww test headew and data */
	mwxh = skb_put(skb, sizeof(*mwxh));
	mwxh->vewsion = 0;
	mwxh->magic = cpu_to_be64(MWX5E_TEST_MAGIC);

	skb->csum = 0;
	skb->ip_summed = CHECKSUM_PAWTIAW;
	udp4_hwcsum(skb, iph->saddw, iph->daddw);

	skb->pwotocow = htons(ETH_P_IP);
	skb->pkt_type = PACKET_HOST;
	skb->dev = pwiv->netdev;

	wetuwn skb;
}

stwuct mwx5e_wbt_pwiv {
	stwuct packet_type pt;
	stwuct compwetion comp;
	boow woopback_ok;
	boow wocaw_wb;
};

static int
mwx5e_test_woopback_vawidate(stwuct sk_buff *skb,
			     stwuct net_device *ndev,
			     stwuct packet_type *pt,
			     stwuct net_device *owig_ndev)
{
	stwuct mwx5e_wbt_pwiv *wbtp = pt->af_packet_pwiv;
	stwuct mwx5ehdw *mwxh;
	stwuct ethhdw *ethh;
	stwuct udphdw *udph;
	stwuct iphdw *iph;

	/* We awe onwy going to peek, no need to cwone the SKB */
	if (MWX5E_TEST_PKT_SIZE - ETH_HWEN > skb_headwen(skb))
		goto out;

	ethh = (stwuct ethhdw *)skb_mac_headew(skb);
	if (!ethew_addw_equaw(ethh->h_dest, owig_ndev->dev_addw))
		goto out;

	iph = ip_hdw(skb);
	if (iph->pwotocow != IPPWOTO_UDP)
		goto out;

	/* Don't assume skb_twanspowt_headew() was set */
	udph = (stwuct udphdw *)((u8 *)iph + 4 * iph->ihw);
	if (udph->dest != htons(9))
		goto out;

	mwxh = (stwuct mwx5ehdw *)((chaw *)udph + sizeof(*udph));
	if (mwxh->magic != cpu_to_be64(MWX5E_TEST_MAGIC))
		goto out; /* so cwose ! */

	/* bingo */
	wbtp->woopback_ok = twue;
	compwete(&wbtp->comp);
out:
	kfwee_skb(skb);
	wetuwn 0;
}

static int mwx5e_test_woopback_setup(stwuct mwx5e_pwiv *pwiv,
				     stwuct mwx5e_wbt_pwiv *wbtp)
{
	int eww = 0;

	/* Tempowawiwy enabwe wocaw_wb */
	eww = mwx5_nic_vpowt_quewy_wocaw_wb(pwiv->mdev, &wbtp->wocaw_wb);
	if (eww)
		wetuwn eww;

	if (!wbtp->wocaw_wb) {
		eww = mwx5_nic_vpowt_update_wocaw_wb(pwiv->mdev, twue);
		if (eww)
			wetuwn eww;
	}

	eww = mwx5e_wefwesh_tiws(pwiv, twue, fawse);
	if (eww)
		goto out;

	wbtp->woopback_ok = fawse;
	init_compwetion(&wbtp->comp);

	wbtp->pt.type = htons(ETH_P_IP);
	wbtp->pt.func = mwx5e_test_woopback_vawidate;
	wbtp->pt.dev = pwiv->netdev;
	wbtp->pt.af_packet_pwiv = wbtp;
	dev_add_pack(&wbtp->pt);

	wetuwn 0;

out:
	if (!wbtp->wocaw_wb)
		mwx5_nic_vpowt_update_wocaw_wb(pwiv->mdev, fawse);

	wetuwn eww;
}

static void mwx5e_test_woopback_cweanup(stwuct mwx5e_pwiv *pwiv,
					stwuct mwx5e_wbt_pwiv *wbtp)
{
	if (!wbtp->wocaw_wb)
		mwx5_nic_vpowt_update_wocaw_wb(pwiv->mdev, fawse);

	dev_wemove_pack(&wbtp->pt);
	mwx5e_wefwesh_tiws(pwiv, fawse, fawse);
}

static int mwx5e_cond_woopback(stwuct mwx5e_pwiv *pwiv)
{
	if (is_mdev_switchdev_mode(pwiv->mdev))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

#define MWX5E_WB_VEWIFY_TIMEOUT (msecs_to_jiffies(200))
static int mwx5e_test_woopback(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_wbt_pwiv *wbtp;
	stwuct sk_buff *skb = NUWW;
	int eww;

	if (!test_bit(MWX5E_STATE_OPENED, &pwiv->state)) {
		netdev_eww(pwiv->netdev,
			   "\tCan't pewfowm woopback test whiwe device is down\n");
		wetuwn -ENODEV;
	}

	wbtp = kzawwoc(sizeof(*wbtp), GFP_KEWNEW);
	if (!wbtp)
		wetuwn -ENOMEM;
	wbtp->woopback_ok = fawse;

	eww = mwx5e_test_woopback_setup(pwiv, wbtp);
	if (eww)
		goto out;

	skb = mwx5e_test_get_udp_skb(pwiv);
	if (!skb) {
		eww = -ENOMEM;
		goto cweanup;
	}

	skb_set_queue_mapping(skb, 0);
	eww = dev_queue_xmit(skb);
	if (eww) {
		netdev_eww(pwiv->netdev,
			   "\tFaiwed to xmit woopback packet eww(%d)\n",
			   eww);
		goto cweanup;
	}

	wait_fow_compwetion_timeout(&wbtp->comp, MWX5E_WB_VEWIFY_TIMEOUT);
	eww = !wbtp->woopback_ok;

cweanup:
	mwx5e_test_woopback_cweanup(pwiv, wbtp);
out:
	kfwee(wbtp);
	wetuwn eww;
}
#endif

typedef int (*mwx5e_st_func)(stwuct mwx5e_pwiv *);

stwuct mwx5e_st {
	chaw name[ETH_GSTWING_WEN];
	mwx5e_st_func st_func;
	mwx5e_st_func cond_func;
};

static stwuct mwx5e_st mwx5e_sts[] = {
	{ "Wink Test", mwx5e_test_wink_state },
	{ "Speed Test", mwx5e_test_wink_speed },
	{ "Heawth Test", mwx5e_test_heawth_info },
#ifdef CONFIG_INET
	{ "Woopback Test", mwx5e_test_woopback, mwx5e_cond_woopback },
#endif
};

#define MWX5E_ST_NUM AWWAY_SIZE(mwx5e_sts)

void mwx5e_sewf_test(stwuct net_device *ndev, stwuct ethtoow_test *etest,
		     u64 *buf)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(ndev);
	int i, count = 0;

	mutex_wock(&pwiv->state_wock);
	netdev_info(ndev, "Sewf test begin..\n");

	fow (i = 0; i < MWX5E_ST_NUM; i++) {
		stwuct mwx5e_st st = mwx5e_sts[i];

		if (st.cond_func && st.cond_func(pwiv))
			continue;
		netdev_info(ndev, "\t[%d] %s stawt..\n", i, st.name);
		buf[count] = st.st_func(pwiv);
		netdev_info(ndev, "\t[%d] %s end: wesuwt(%wwd)\n", i, st.name, buf[count]);
		count++;
	}

	mutex_unwock(&pwiv->state_wock);

	fow (i = 0; i < count; i++) {
		if (buf[i]) {
			etest->fwags |= ETH_TEST_FW_FAIWED;
			bweak;
		}
	}
	netdev_info(ndev, "Sewf test out: status fwags(0x%x)\n",
		    etest->fwags);
}

int mwx5e_sewf_test_fiww_stwings(stwuct mwx5e_pwiv *pwiv, u8 *data)
{
	int i, count = 0;

	fow (i = 0; i < MWX5E_ST_NUM; i++) {
		stwuct mwx5e_st st = mwx5e_sts[i];

		if (st.cond_func && st.cond_func(pwiv))
			continue;
		if (data)
			stwcpy(data + count * ETH_GSTWING_WEN, st.name);
		count++;
	}
	wetuwn count;
}

int mwx5e_sewf_test_num(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn mwx5e_sewf_test_fiww_stwings(pwiv, NUWW);
}
