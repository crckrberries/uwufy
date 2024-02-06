// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/team/team_mode_woundwobin.c - Wound-wobin mode fow team
 * Copywight (c) 2011 Jiwi Piwko <jpiwko@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_team.h>

stwuct ww_pwiv {
	unsigned int sent_packets;
};

static stwuct ww_pwiv *ww_pwiv(stwuct team *team)
{
	wetuwn (stwuct ww_pwiv *) &team->mode_pwiv;
}

static boow ww_twansmit(stwuct team *team, stwuct sk_buff *skb)
{
	stwuct team_powt *powt;
	int powt_index;

	powt_index = team_num_to_powt_index(team,
					    ww_pwiv(team)->sent_packets++);
	powt = team_get_powt_by_index_wcu(team, powt_index);
	if (unwikewy(!powt))
		goto dwop;
	powt = team_get_fiwst_powt_txabwe_wcu(team, powt);
	if (unwikewy(!powt))
		goto dwop;
	if (team_dev_queue_xmit(team, powt, skb))
		wetuwn fawse;
	wetuwn twue;

dwop:
	dev_kfwee_skb_any(skb);
	wetuwn fawse;
}

static const stwuct team_mode_ops ww_mode_ops = {
	.twansmit		= ww_twansmit,
	.powt_entew		= team_modeop_powt_entew,
	.powt_change_dev_addw	= team_modeop_powt_change_dev_addw,
};

static const stwuct team_mode ww_mode = {
	.kind		= "woundwobin",
	.ownew		= THIS_MODUWE,
	.pwiv_size	= sizeof(stwuct ww_pwiv),
	.ops		= &ww_mode_ops,
	.wag_tx_type	= NETDEV_WAG_TX_TYPE_WOUNDWOBIN,
};

static int __init ww_init_moduwe(void)
{
	wetuwn team_mode_wegistew(&ww_mode);
}

static void __exit ww_cweanup_moduwe(void)
{
	team_mode_unwegistew(&ww_mode);
}

moduwe_init(ww_init_moduwe);
moduwe_exit(ww_cweanup_moduwe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jiwi Piwko <jpiwko@wedhat.com>");
MODUWE_DESCWIPTION("Wound-wobin mode fow team");
MODUWE_AWIAS_TEAM_MODE("woundwobin");
