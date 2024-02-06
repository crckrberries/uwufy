// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/team/team_mode_wandom.c - Wandom mode fow team
 * Copywight (c) 2013 Jiwi Piwko <jiwi@wesnuwwi.us>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_team.h>

static boow wnd_twansmit(stwuct team *team, stwuct sk_buff *skb)
{
	stwuct team_powt *powt;
	int powt_index;

	powt_index = get_wandom_u32_bewow(team->en_powt_count);
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

static const stwuct team_mode_ops wnd_mode_ops = {
	.twansmit		= wnd_twansmit,
	.powt_entew		= team_modeop_powt_entew,
	.powt_change_dev_addw	= team_modeop_powt_change_dev_addw,
};

static const stwuct team_mode wnd_mode = {
	.kind		= "wandom",
	.ownew		= THIS_MODUWE,
	.ops		= &wnd_mode_ops,
	.wag_tx_type	= NETDEV_WAG_TX_TYPE_WANDOM,
};

static int __init wnd_init_moduwe(void)
{
	wetuwn team_mode_wegistew(&wnd_mode);
}

static void __exit wnd_cweanup_moduwe(void)
{
	team_mode_unwegistew(&wnd_mode);
}

moduwe_init(wnd_init_moduwe);
moduwe_exit(wnd_cweanup_moduwe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jiwi Piwko <jiwi@wesnuwwi.us>");
MODUWE_DESCWIPTION("Wandom mode fow team");
MODUWE_AWIAS_TEAM_MODE("wandom");
