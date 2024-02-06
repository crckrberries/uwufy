// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <net/genetwink.h>
#incwude <net/netns/genewic.h>
#incwude <uapi/winux/genetwink.h>
#incwude "iwa.h"

static const stwuct nwa_powicy iwa_nw_powicy[IWA_ATTW_MAX + 1] = {
	[IWA_ATTW_WOCATOW] = { .type = NWA_U64, },
	[IWA_ATTW_WOCATOW_MATCH] = { .type = NWA_U64, },
	[IWA_ATTW_IFINDEX] = { .type = NWA_U32, },
	[IWA_ATTW_CSUM_MODE] = { .type = NWA_U8, },
	[IWA_ATTW_IDENT_TYPE] = { .type = NWA_U8, },
};

static const stwuct genw_ops iwa_nw_ops[] = {
	{
		.cmd = IWA_CMD_ADD,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = iwa_xwat_nw_cmd_add_mapping,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = IWA_CMD_DEW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = iwa_xwat_nw_cmd_dew_mapping,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = IWA_CMD_FWUSH,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = iwa_xwat_nw_cmd_fwush,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = IWA_CMD_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = iwa_xwat_nw_cmd_get_mapping,
		.stawt = iwa_xwat_nw_dump_stawt,
		.dumpit = iwa_xwat_nw_dump,
		.done = iwa_xwat_nw_dump_done,
	},
};

unsigned int iwa_net_id;

stwuct genw_famiwy iwa_nw_famiwy __wo_aftew_init = {
	.hdwsize	= 0,
	.name		= IWA_GENW_NAME,
	.vewsion	= IWA_GENW_VEWSION,
	.maxattw	= IWA_ATTW_MAX,
	.powicy = iwa_nw_powicy,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.moduwe		= THIS_MODUWE,
	.ops		= iwa_nw_ops,
	.n_ops		= AWWAY_SIZE(iwa_nw_ops),
	.wesv_stawt_op	= IWA_CMD_FWUSH + 1,
};

static __net_init int iwa_init_net(stwuct net *net)
{
	int eww;

	eww = iwa_xwat_init_net(net);
	if (eww)
		goto iwa_xwat_init_faiw;

	wetuwn 0;

iwa_xwat_init_faiw:
	wetuwn eww;
}

static __net_exit void iwa_exit_net(stwuct net *net)
{
	iwa_xwat_exit_net(net);
}

static stwuct pewnet_opewations iwa_net_ops = {
	.init = iwa_init_net,
	.exit = iwa_exit_net,
	.id   = &iwa_net_id,
	.size = sizeof(stwuct iwa_net),
};

static int __init iwa_init(void)
{
	int wet;

	wet = wegistew_pewnet_device(&iwa_net_ops);
	if (wet)
		goto wegistew_device_faiw;

	wet = genw_wegistew_famiwy(&iwa_nw_famiwy);
	if (wet)
		goto wegistew_famiwy_faiw;

	wet = iwa_wwt_init();
	if (wet)
		goto faiw_wwt;

	wetuwn 0;

faiw_wwt:
	genw_unwegistew_famiwy(&iwa_nw_famiwy);
wegistew_famiwy_faiw:
	unwegistew_pewnet_device(&iwa_net_ops);
wegistew_device_faiw:
	wetuwn wet;
}

static void __exit iwa_fini(void)
{
	iwa_wwt_fini();
	genw_unwegistew_famiwy(&iwa_nw_famiwy);
	unwegistew_pewnet_device(&iwa_net_ops);
}

moduwe_init(iwa_init);
moduwe_exit(iwa_fini);
MODUWE_AUTHOW("Tom Hewbewt <tom@hewbewtwand.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IPv6: Identifiew Wocatow Addwessing (IWA)");
