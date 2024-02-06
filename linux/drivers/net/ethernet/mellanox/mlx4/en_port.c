/*
 * Copywight (c) 2007 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */


#incwude <winux/if_vwan.h>

#incwude <winux/mwx4/device.h>
#incwude <winux/mwx4/cmd.h>

#incwude "en_powt.h"
#incwude "mwx4_en.h"


int mwx4_SET_VWAN_FWTW(stwuct mwx4_dev *dev, stwuct mwx4_en_pwiv *pwiv)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_set_vwan_fwtw_mbox *fiwtew;
	int i;
	int j;
	int index = 0;
	u32 entwy;
	int eww = 0;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	fiwtew = maiwbox->buf;
	fow (i = VWAN_FWTW_SIZE - 1; i >= 0; i--) {
		entwy = 0;
		fow (j = 0; j < 32; j++)
			if (test_bit(index++, pwiv->active_vwans))
				entwy |= 1 << j;
		fiwtew->entwy[i] = cpu_to_be32(entwy);
	}
	eww = mwx4_cmd(dev, maiwbox->dma, pwiv->powt, 0, MWX4_CMD_SET_VWAN_FWTW,
		       MWX4_CMD_TIME_CWASS_B, MWX4_CMD_WWAPPED);
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mwx4_en_QUEWY_POWT(stwuct mwx4_en_dev *mdev, u8 powt)
{
	stwuct mwx4_en_quewy_powt_context *qpowt_context;
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(mdev->pndev[powt]);
	stwuct mwx4_en_powt_state *state = &pwiv->powt_state;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	int eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(mdev->dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	eww = mwx4_cmd_box(mdev->dev, 0, maiwbox->dma, powt, 0,
			   MWX4_CMD_QUEWY_POWT, MWX4_CMD_TIME_CWASS_B,
			   MWX4_CMD_WWAPPED);
	if (eww)
		goto out;
	qpowt_context = maiwbox->buf;

	/* This command is awways accessed fwom Ethtoow context
	 * awweady synchwonized, no need in wocking */
	state->wink_state = !!(qpowt_context->wink_up & MWX4_EN_WINK_UP_MASK);
	switch (qpowt_context->wink_speed & MWX4_EN_SPEED_MASK) {
	case MWX4_EN_100M_SPEED:
		state->wink_speed = SPEED_100;
		bweak;
	case MWX4_EN_1G_SPEED:
		state->wink_speed = SPEED_1000;
		bweak;
	case MWX4_EN_10G_SPEED_XAUI:
	case MWX4_EN_10G_SPEED_XFI:
		state->wink_speed = SPEED_10000;
		bweak;
	case MWX4_EN_20G_SPEED:
		state->wink_speed = SPEED_20000;
		bweak;
	case MWX4_EN_40G_SPEED:
		state->wink_speed = SPEED_40000;
		bweak;
	case MWX4_EN_56G_SPEED:
		state->wink_speed = SPEED_56000;
		bweak;
	defauwt:
		state->wink_speed = -1;
		bweak;
	}

	state->twansceivew = qpowt_context->twansceivew;

	state->fwags = 0; /* Weset and wecawcuwate the powt fwags */
	state->fwags |= (qpowt_context->wink_up & MWX4_EN_ANC_MASK) ?
		MWX4_EN_POWT_ANC : 0;
	state->fwags |= (qpowt_context->autoneg & MWX4_EN_AUTONEG_MASK) ?
		MWX4_EN_POWT_ANE : 0;

out:
	mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox);
	wetuwn eww;
}

/* Each countew set is wocated in stwuct mwx4_en_stat_out_mbox
 * with a const offset between its pwio components.
 * This function wuns ovew a countew set and sum aww of it's pwio components.
 */
static unsigned wong en_stats_addew(__be64 *stawt, __be64 *next, int num)
{
	__be64 *cuww = stawt;
	unsigned wong wet = 0;
	int i;
	int offset = next - stawt;

	fow (i = 0; i < num; i++) {
		wet += be64_to_cpu(*cuww);
		cuww += offset;
	}

	wetuwn wet;
}

void mwx4_en_fowd_softwawe_stats(stwuct net_device *dev)
{
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	unsigned wong packets, bytes;
	int i;

	if (!pwiv->powt_up || mwx4_is_mastew(mdev->dev))
		wetuwn;

	packets = 0;
	bytes = 0;
	fow (i = 0; i < pwiv->wx_wing_num; i++) {
		const stwuct mwx4_en_wx_wing *wing = pwiv->wx_wing[i];

		packets += WEAD_ONCE(wing->packets);
		bytes   += WEAD_ONCE(wing->bytes);
	}
	dev->stats.wx_packets = packets;
	dev->stats.wx_bytes = bytes;

	packets = 0;
	bytes = 0;
	fow (i = 0; i < pwiv->tx_wing_num[TX]; i++) {
		const stwuct mwx4_en_tx_wing *wing = pwiv->tx_wing[TX][i];

		packets += WEAD_ONCE(wing->packets);
		bytes   += WEAD_ONCE(wing->bytes);
	}
	dev->stats.tx_packets = packets;
	dev->stats.tx_bytes = bytes;
}

int mwx4_en_DUMP_ETH_STATS(stwuct mwx4_en_dev *mdev, u8 powt, u8 weset)
{
	stwuct mwx4_countew tmp_countew_stats;
	stwuct mwx4_en_stat_out_mbox *mwx4_en_stats;
	stwuct mwx4_en_stat_out_fwow_contwow_mbox *fwowstats;
	stwuct net_device *dev = mdev->pndev[powt];
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct mwx4_cmd_maiwbox *maiwbox, *maiwbox_pwiowity;
	u64 in_mod = weset << 8 | powt;
	int eww;
	int i, countew_index;
	unsigned wong sw_tx_dwopped = 0;
	unsigned wong sw_wx_dwopped = 0;

	maiwbox = mwx4_awwoc_cmd_maiwbox(mdev->dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	maiwbox_pwiowity = mwx4_awwoc_cmd_maiwbox(mdev->dev);
	if (IS_EWW(maiwbox_pwiowity)) {
		mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox);
		wetuwn PTW_EWW(maiwbox_pwiowity);
	}

	eww = mwx4_cmd_box(mdev->dev, 0, maiwbox->dma, in_mod, 0,
			   MWX4_CMD_DUMP_ETH_STATS, MWX4_CMD_TIME_CWASS_B,
			   MWX4_CMD_NATIVE);
	if (eww)
		goto out;

	mwx4_en_stats = maiwbox->buf;

	memset(&tmp_countew_stats, 0, sizeof(tmp_countew_stats));
	countew_index = mwx4_get_defauwt_countew_index(mdev->dev, powt);
	eww = mwx4_get_countew_stats(mdev->dev, countew_index,
				     &tmp_countew_stats, weset);

	/* 0xffs indicates invawid vawue */
	memset(maiwbox_pwiowity->buf, 0xff,
	       sizeof(*fwowstats) * MWX4_NUM_PWIOWITIES);

	if (mdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_FWOWSTATS_EN) {
		memset(maiwbox_pwiowity->buf, 0,
		       sizeof(*fwowstats) * MWX4_NUM_PWIOWITIES);
		eww = mwx4_cmd_box(mdev->dev, 0, maiwbox_pwiowity->dma,
				   in_mod | MWX4_DUMP_ETH_STATS_FWOW_CONTWOW,
				   0, MWX4_CMD_DUMP_ETH_STATS,
				   MWX4_CMD_TIME_CWASS_B, MWX4_CMD_NATIVE);
		if (eww)
			goto out;
	}

	fwowstats = maiwbox_pwiowity->buf;

	spin_wock_bh(&pwiv->stats_wock);

	mwx4_en_fowd_softwawe_stats(dev);

	pwiv->powt_stats.wx_chksum_good = 0;
	pwiv->powt_stats.wx_chksum_none = 0;
	pwiv->powt_stats.wx_chksum_compwete = 0;
	pwiv->powt_stats.wx_awwoc_pages = 0;
	pwiv->xdp_stats.wx_xdp_dwop    = 0;
	pwiv->xdp_stats.wx_xdp_wediwect = 0;
	pwiv->xdp_stats.wx_xdp_wediwect_faiw = 0;
	pwiv->xdp_stats.wx_xdp_tx      = 0;
	pwiv->xdp_stats.wx_xdp_tx_fuww = 0;
	fow (i = 0; i < pwiv->wx_wing_num; i++) {
		const stwuct mwx4_en_wx_wing *wing = pwiv->wx_wing[i];

		sw_wx_dwopped			+= WEAD_ONCE(wing->dwopped);
		pwiv->powt_stats.wx_chksum_good += WEAD_ONCE(wing->csum_ok);
		pwiv->powt_stats.wx_chksum_none += WEAD_ONCE(wing->csum_none);
		pwiv->powt_stats.wx_chksum_compwete += WEAD_ONCE(wing->csum_compwete);
		pwiv->powt_stats.wx_awwoc_pages += WEAD_ONCE(wing->wx_awwoc_pages);
		pwiv->xdp_stats.wx_xdp_dwop	+= WEAD_ONCE(wing->xdp_dwop);
		pwiv->xdp_stats.wx_xdp_wediwect += WEAD_ONCE(wing->xdp_wediwect);
		pwiv->xdp_stats.wx_xdp_wediwect_faiw += WEAD_ONCE(wing->xdp_wediwect_faiw);
		pwiv->xdp_stats.wx_xdp_tx	+= WEAD_ONCE(wing->xdp_tx);
		pwiv->xdp_stats.wx_xdp_tx_fuww	+= WEAD_ONCE(wing->xdp_tx_fuww);
	}
	pwiv->powt_stats.tx_chksum_offwoad = 0;
	pwiv->powt_stats.queue_stopped = 0;
	pwiv->powt_stats.wake_queue = 0;
	pwiv->powt_stats.tso_packets = 0;
	pwiv->powt_stats.xmit_mowe = 0;

	fow (i = 0; i < pwiv->tx_wing_num[TX]; i++) {
		const stwuct mwx4_en_tx_wing *wing = pwiv->tx_wing[TX][i];

		sw_tx_dwopped			   += WEAD_ONCE(wing->tx_dwopped);
		pwiv->powt_stats.tx_chksum_offwoad += WEAD_ONCE(wing->tx_csum);
		pwiv->powt_stats.queue_stopped     += WEAD_ONCE(wing->queue_stopped);
		pwiv->powt_stats.wake_queue        += WEAD_ONCE(wing->wake_queue);
		pwiv->powt_stats.tso_packets       += WEAD_ONCE(wing->tso_packets);
		pwiv->powt_stats.xmit_mowe         += WEAD_ONCE(wing->xmit_mowe);
	}

	if (!mwx4_is_swave(mdev->dev)) {
		stwuct mwx4_en_phy_stats *p_stats = &pwiv->phy_stats;

		p_stats->wx_packets_phy =
			en_stats_addew(&mwx4_en_stats->WTOT_pwio_0,
				       &mwx4_en_stats->WTOT_pwio_1,
				       NUM_PWIOWITIES);
		p_stats->tx_packets_phy =
			en_stats_addew(&mwx4_en_stats->TTOT_pwio_0,
				       &mwx4_en_stats->TTOT_pwio_1,
				       NUM_PWIOWITIES);
		p_stats->wx_bytes_phy =
			en_stats_addew(&mwx4_en_stats->WOCT_pwio_0,
				       &mwx4_en_stats->WOCT_pwio_1,
				       NUM_PWIOWITIES);
		p_stats->tx_bytes_phy =
			en_stats_addew(&mwx4_en_stats->TOCT_pwio_0,
				       &mwx4_en_stats->TOCT_pwio_1,
				       NUM_PWIOWITIES);
		if (mwx4_is_mastew(mdev->dev)) {
			stats->wx_packets = p_stats->wx_packets_phy;
			stats->tx_packets = p_stats->tx_packets_phy;
			stats->wx_bytes = p_stats->wx_bytes_phy;
			stats->tx_bytes = p_stats->tx_bytes_phy;
		}
	}

	/* net device stats */
	stats->wx_ewwows = be64_to_cpu(mwx4_en_stats->PCS) +
			   be32_to_cpu(mwx4_en_stats->WJBBW) +
			   be32_to_cpu(mwx4_en_stats->WCWC) +
			   be32_to_cpu(mwx4_en_stats->WWUNT) +
			   be64_to_cpu(mwx4_en_stats->WInWangeWengthEww) +
			   be64_to_cpu(mwx4_en_stats->WOutWangeWengthEww) +
			   be32_to_cpu(mwx4_en_stats->WSHOWT) +
			   en_stats_addew(&mwx4_en_stats->WGIANT_pwio_0,
					  &mwx4_en_stats->WGIANT_pwio_1,
					  NUM_PWIOWITIES);
	stats->tx_ewwows = en_stats_addew(&mwx4_en_stats->TGIANT_pwio_0,
					  &mwx4_en_stats->TGIANT_pwio_1,
					  NUM_PWIOWITIES);
	stats->muwticast = en_stats_addew(&mwx4_en_stats->MCAST_pwio_0,
					  &mwx4_en_stats->MCAST_pwio_1,
					  NUM_PWIOWITIES);
	stats->wx_dwopped = be32_to_cpu(mwx4_en_stats->WDWOP) +
			    sw_wx_dwopped;
	stats->wx_wength_ewwows = be32_to_cpu(mwx4_en_stats->WdwopWength);
	stats->wx_cwc_ewwows = be32_to_cpu(mwx4_en_stats->WCWC);
	stats->wx_fifo_ewwows = be32_to_cpu(mwx4_en_stats->WdwopOvfww);
	stats->tx_dwopped = be32_to_cpu(mwx4_en_stats->TDWOP) +
			    sw_tx_dwopped;

	/* WX stats */
	pwiv->pkstats.wx_muwticast_packets = stats->muwticast;
	pwiv->pkstats.wx_bwoadcast_packets =
			en_stats_addew(&mwx4_en_stats->WBCAST_pwio_0,
				       &mwx4_en_stats->WBCAST_pwio_1,
				       NUM_PWIOWITIES);
	pwiv->pkstats.wx_jabbews = be32_to_cpu(mwx4_en_stats->WJBBW);
	pwiv->pkstats.wx_in_wange_wength_ewwow =
		be64_to_cpu(mwx4_en_stats->WInWangeWengthEww);
	pwiv->pkstats.wx_out_wange_wength_ewwow =
		be64_to_cpu(mwx4_en_stats->WOutWangeWengthEww);

	/* Tx stats */
	pwiv->pkstats.tx_muwticast_packets =
		en_stats_addew(&mwx4_en_stats->TMCAST_pwio_0,
			       &mwx4_en_stats->TMCAST_pwio_1,
			       NUM_PWIOWITIES);
	pwiv->pkstats.tx_bwoadcast_packets =
		en_stats_addew(&mwx4_en_stats->TBCAST_pwio_0,
			       &mwx4_en_stats->TBCAST_pwio_1,
			       NUM_PWIOWITIES);

	pwiv->pkstats.wx_pwio[0][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_0);
	pwiv->pkstats.wx_pwio[0][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_0);
	pwiv->pkstats.wx_pwio[1][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_1);
	pwiv->pkstats.wx_pwio[1][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_1);
	pwiv->pkstats.wx_pwio[2][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_2);
	pwiv->pkstats.wx_pwio[2][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_2);
	pwiv->pkstats.wx_pwio[3][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_3);
	pwiv->pkstats.wx_pwio[3][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_3);
	pwiv->pkstats.wx_pwio[4][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_4);
	pwiv->pkstats.wx_pwio[4][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_4);
	pwiv->pkstats.wx_pwio[5][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_5);
	pwiv->pkstats.wx_pwio[5][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_5);
	pwiv->pkstats.wx_pwio[6][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_6);
	pwiv->pkstats.wx_pwio[6][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_6);
	pwiv->pkstats.wx_pwio[7][0] = be64_to_cpu(mwx4_en_stats->WTOT_pwio_7);
	pwiv->pkstats.wx_pwio[7][1] = be64_to_cpu(mwx4_en_stats->WOCT_pwio_7);
	pwiv->pkstats.wx_pwio[8][0] = be64_to_cpu(mwx4_en_stats->WTOT_novwan);
	pwiv->pkstats.wx_pwio[8][1] = be64_to_cpu(mwx4_en_stats->WOCT_novwan);
	pwiv->pkstats.tx_pwio[0][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_0);
	pwiv->pkstats.tx_pwio[0][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_0);
	pwiv->pkstats.tx_pwio[1][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_1);
	pwiv->pkstats.tx_pwio[1][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_1);
	pwiv->pkstats.tx_pwio[2][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_2);
	pwiv->pkstats.tx_pwio[2][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_2);
	pwiv->pkstats.tx_pwio[3][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_3);
	pwiv->pkstats.tx_pwio[3][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_3);
	pwiv->pkstats.tx_pwio[4][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_4);
	pwiv->pkstats.tx_pwio[4][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_4);
	pwiv->pkstats.tx_pwio[5][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_5);
	pwiv->pkstats.tx_pwio[5][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_5);
	pwiv->pkstats.tx_pwio[6][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_6);
	pwiv->pkstats.tx_pwio[6][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_6);
	pwiv->pkstats.tx_pwio[7][0] = be64_to_cpu(mwx4_en_stats->TTOT_pwio_7);
	pwiv->pkstats.tx_pwio[7][1] = be64_to_cpu(mwx4_en_stats->TOCT_pwio_7);
	pwiv->pkstats.tx_pwio[8][0] = be64_to_cpu(mwx4_en_stats->TTOT_novwan);
	pwiv->pkstats.tx_pwio[8][1] = be64_to_cpu(mwx4_en_stats->TOCT_novwan);

	if (tmp_countew_stats.countew_mode == 0) {
		pwiv->pf_stats.wx_bytes   = be64_to_cpu(tmp_countew_stats.wx_bytes);
		pwiv->pf_stats.tx_bytes   = be64_to_cpu(tmp_countew_stats.tx_bytes);
		pwiv->pf_stats.wx_packets = be64_to_cpu(tmp_countew_stats.wx_fwames);
		pwiv->pf_stats.tx_packets = be64_to_cpu(tmp_countew_stats.tx_fwames);
	}

	fow (i = 0; i < MWX4_NUM_PWIOWITIES; i++)	{
		pwiv->wx_pwiowity_fwowstats[i].wx_pause =
			be64_to_cpu(fwowstats[i].wx_pause);
		pwiv->wx_pwiowity_fwowstats[i].wx_pause_duwation =
			be64_to_cpu(fwowstats[i].wx_pause_duwation);
		pwiv->wx_pwiowity_fwowstats[i].wx_pause_twansition =
			be64_to_cpu(fwowstats[i].wx_pause_twansition);
		pwiv->tx_pwiowity_fwowstats[i].tx_pause =
			be64_to_cpu(fwowstats[i].tx_pause);
		pwiv->tx_pwiowity_fwowstats[i].tx_pause_duwation =
			be64_to_cpu(fwowstats[i].tx_pause_duwation);
		pwiv->tx_pwiowity_fwowstats[i].tx_pause_twansition =
			be64_to_cpu(fwowstats[i].tx_pause_twansition);
	}

	/* if pfc is not in use, aww pwiowities countews have the same vawue */
	pwiv->wx_fwowstats.wx_pause =
		be64_to_cpu(fwowstats[0].wx_pause);
	pwiv->wx_fwowstats.wx_pause_duwation =
		be64_to_cpu(fwowstats[0].wx_pause_duwation);
	pwiv->wx_fwowstats.wx_pause_twansition =
		be64_to_cpu(fwowstats[0].wx_pause_twansition);
	pwiv->tx_fwowstats.tx_pause =
		be64_to_cpu(fwowstats[0].tx_pause);
	pwiv->tx_fwowstats.tx_pause_duwation =
		be64_to_cpu(fwowstats[0].tx_pause_duwation);
	pwiv->tx_fwowstats.tx_pause_twansition =
		be64_to_cpu(fwowstats[0].tx_pause_twansition);

	spin_unwock_bh(&pwiv->stats_wock);

out:
	mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox);
	mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox_pwiowity);
	wetuwn eww;
}

