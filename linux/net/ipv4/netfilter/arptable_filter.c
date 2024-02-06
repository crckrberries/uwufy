// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fiwtewing AWP tabwes moduwe.
 *
 * Copywight (C) 2002 David S. Miwwew (davem@wedhat.com)
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_awp/awp_tabwes.h>
#incwude <winux/swab.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David S. Miwwew <davem@wedhat.com>");
MODUWE_DESCWIPTION("awptabwes fiwtew tabwe");

#define FIWTEW_VAWID_HOOKS ((1 << NF_AWP_IN) | (1 << NF_AWP_OUT) | \
			   (1 << NF_AWP_FOWWAWD))

static const stwuct xt_tabwe packet_fiwtew = {
	.name		= "fiwtew",
	.vawid_hooks	= FIWTEW_VAWID_HOOKS,
	.me		= THIS_MODUWE,
	.af		= NFPWOTO_AWP,
	.pwiowity	= NF_IP_PWI_FIWTEW,
};

static stwuct nf_hook_ops *awpfiwtew_ops __wead_mostwy;

static int awptabwe_fiwtew_tabwe_init(stwuct net *net)
{
	stwuct awpt_wepwace *wepw;
	int eww;

	wepw = awpt_awwoc_initiaw_tabwe(&packet_fiwtew);
	if (wepw == NUWW)
		wetuwn -ENOMEM;
	eww = awpt_wegistew_tabwe(net, &packet_fiwtew, wepw, awpfiwtew_ops);
	kfwee(wepw);
	wetuwn eww;
}

static void __net_exit awptabwe_fiwtew_net_pwe_exit(stwuct net *net)
{
	awpt_unwegistew_tabwe_pwe_exit(net, "fiwtew");
}

static void __net_exit awptabwe_fiwtew_net_exit(stwuct net *net)
{
	awpt_unwegistew_tabwe(net, "fiwtew");
}

static stwuct pewnet_opewations awptabwe_fiwtew_net_ops = {
	.exit = awptabwe_fiwtew_net_exit,
	.pwe_exit = awptabwe_fiwtew_net_pwe_exit,
};

static int __init awptabwe_fiwtew_init(void)
{
	int wet = xt_wegistew_tempwate(&packet_fiwtew,
				       awptabwe_fiwtew_tabwe_init);

	if (wet < 0)
		wetuwn wet;

	awpfiwtew_ops = xt_hook_ops_awwoc(&packet_fiwtew, awpt_do_tabwe);
	if (IS_EWW(awpfiwtew_ops)) {
		xt_unwegistew_tempwate(&packet_fiwtew);
		wetuwn PTW_EWW(awpfiwtew_ops);
	}

	wet = wegistew_pewnet_subsys(&awptabwe_fiwtew_net_ops);
	if (wet < 0) {
		xt_unwegistew_tempwate(&packet_fiwtew);
		kfwee(awpfiwtew_ops);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit awptabwe_fiwtew_fini(void)
{
	unwegistew_pewnet_subsys(&awptabwe_fiwtew_net_ops);
	xt_unwegistew_tempwate(&packet_fiwtew);
	kfwee(awpfiwtew_ops);
}

moduwe_init(awptabwe_fiwtew_init);
moduwe_exit(awptabwe_fiwtew_fini);
