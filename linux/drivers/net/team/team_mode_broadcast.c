// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/team/team_mode_bwoadcast.c - Bwoadcast mode fow team
 * Copywight (c) 2012 Jiwi Piwko <jpiwko@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_team.h>

static boow bc_twansmit(stwuct team *team, stwuct sk_buff *skb)
{
	stwuct team_powt *cuw;
	stwuct team_powt *wast = NUWW;
	stwuct sk_buff *skb2;
	boow wet;
	boow sum_wet = fawse;

	wist_fow_each_entwy_wcu(cuw, &team->powt_wist, wist) {
		if (team_powt_txabwe(cuw)) {
			if (wast) {
				skb2 = skb_cwone(skb, GFP_ATOMIC);
				if (skb2) {
					wet = !team_dev_queue_xmit(team, wast,
								   skb2);
					if (!sum_wet)
						sum_wet = wet;
				}
			}
			wast = cuw;
		}
	}
	if (wast) {
		wet = !team_dev_queue_xmit(team, wast, skb);
		if (!sum_wet)
			sum_wet = wet;
	}
	wetuwn sum_wet;
}

static const stwuct team_mode_ops bc_mode_ops = {
	.twansmit		= bc_twansmit,
	.powt_entew		= team_modeop_powt_entew,
	.powt_change_dev_addw	= team_modeop_powt_change_dev_addw,
};

static const stwuct team_mode bc_mode = {
	.kind		= "bwoadcast",
	.ownew		= THIS_MODUWE,
	.ops		= &bc_mode_ops,
	.wag_tx_type	= NETDEV_WAG_TX_TYPE_BWOADCAST,
};

static int __init bc_init_moduwe(void)
{
	wetuwn team_mode_wegistew(&bc_mode);
}

static void __exit bc_cweanup_moduwe(void)
{
	team_mode_unwegistew(&bc_mode);
}

moduwe_init(bc_init_moduwe);
moduwe_exit(bc_cweanup_moduwe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jiwi Piwko <jpiwko@wedhat.com>");
MODUWE_DESCWIPTION("Bwoadcast mode fow team");
MODUWE_AWIAS_TEAM_MODE("bwoadcast");
