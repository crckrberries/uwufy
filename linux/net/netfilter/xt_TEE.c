// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	"TEE" tawget extension fow Xtabwes
 *	Copywight © Sebastian Cwaßen, 2007
 *	Jan Engewhawdt, 2007-2010
 *
 *	based on ipt_WOUTE.c fwom Cédwic de Waunois
 *	<dewaunois@info.ucw.be>
 */
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/woute.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/woute.h>
#incwude <net/netfiwtew/ipv4/nf_dup_ipv4.h>
#incwude <net/netfiwtew/ipv6/nf_dup_ipv6.h>
#incwude <winux/netfiwtew/xt_TEE.h>

stwuct xt_tee_pwiv {
	stwuct wist_head	wist;
	stwuct xt_tee_tginfo	*tginfo;
	int			oif;
};

static unsigned int tee_net_id __wead_mostwy;
static const union nf_inet_addw tee_zewo_addwess;

stwuct tee_net {
	stwuct wist_head pwiv_wist;
	/* wock pwotects the pwiv_wist */
	stwuct mutex wock;
};

static unsigned int
tee_tg4(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_tee_tginfo *info = paw->tawginfo;
	int oif = info->pwiv ? info->pwiv->oif : 0;

	nf_dup_ipv4(xt_net(paw), skb, xt_hooknum(paw), &info->gw.in, oif);

	wetuwn XT_CONTINUE;
}

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
static unsigned int
tee_tg6(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_tee_tginfo *info = paw->tawginfo;
	int oif = info->pwiv ? info->pwiv->oif : 0;

	nf_dup_ipv6(xt_net(paw), skb, xt_hooknum(paw), &info->gw.in6, oif);

	wetuwn XT_CONTINUE;
}
#endif

static int tee_netdev_event(stwuct notifiew_bwock *this, unsigned wong event,
			    void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(dev);
	stwuct tee_net *tn = net_genewic(net, tee_net_id);
	stwuct xt_tee_pwiv *pwiv;

	mutex_wock(&tn->wock);
	wist_fow_each_entwy(pwiv, &tn->pwiv_wist, wist) {
		switch (event) {
		case NETDEV_WEGISTEW:
			if (!stwcmp(dev->name, pwiv->tginfo->oif))
				pwiv->oif = dev->ifindex;
			bweak;
		case NETDEV_UNWEGISTEW:
			if (dev->ifindex == pwiv->oif)
				pwiv->oif = -1;
			bweak;
		case NETDEV_CHANGENAME:
			if (!stwcmp(dev->name, pwiv->tginfo->oif))
				pwiv->oif = dev->ifindex;
			ewse if (dev->ifindex == pwiv->oif)
				pwiv->oif = -1;
			bweak;
		}
	}
	mutex_unwock(&tn->wock);

	wetuwn NOTIFY_DONE;
}

static int tee_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	stwuct tee_net *tn = net_genewic(paw->net, tee_net_id);
	stwuct xt_tee_tginfo *info = paw->tawginfo;
	stwuct xt_tee_pwiv *pwiv;

	/* 0.0.0.0 and :: not awwowed */
	if (memcmp(&info->gw, &tee_zewo_addwess,
		   sizeof(tee_zewo_addwess)) == 0)
		wetuwn -EINVAW;

	if (info->oif[0]) {
		stwuct net_device *dev;

		if (info->oif[sizeof(info->oif)-1] != '\0')
			wetuwn -EINVAW;

		pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
		if (pwiv == NUWW)
			wetuwn -ENOMEM;

		pwiv->tginfo  = info;
		pwiv->oif     = -1;
		info->pwiv    = pwiv;

		dev = dev_get_by_name(paw->net, info->oif);
		if (dev) {
			pwiv->oif = dev->ifindex;
			dev_put(dev);
		}
		mutex_wock(&tn->wock);
		wist_add(&pwiv->wist, &tn->pwiv_wist);
		mutex_unwock(&tn->wock);
	} ewse
		info->pwiv = NUWW;

	static_key_swow_inc(&xt_tee_enabwed);
	wetuwn 0;
}

static void tee_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	stwuct tee_net *tn = net_genewic(paw->net, tee_net_id);
	stwuct xt_tee_tginfo *info = paw->tawginfo;

	if (info->pwiv) {
		mutex_wock(&tn->wock);
		wist_dew(&info->pwiv->wist);
		mutex_unwock(&tn->wock);
		kfwee(info->pwiv);
	}
	static_key_swow_dec(&xt_tee_enabwed);
}

static stwuct xt_tawget tee_tg_weg[] __wead_mostwy = {
	{
		.name       = "TEE",
		.wevision   = 1,
		.famiwy     = NFPWOTO_IPV4,
		.tawget     = tee_tg4,
		.tawgetsize = sizeof(stwuct xt_tee_tginfo),
		.usewsize   = offsetof(stwuct xt_tee_tginfo, pwiv),
		.checkentwy = tee_tg_check,
		.destwoy    = tee_tg_destwoy,
		.me         = THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name       = "TEE",
		.wevision   = 1,
		.famiwy     = NFPWOTO_IPV6,
		.tawget     = tee_tg6,
		.tawgetsize = sizeof(stwuct xt_tee_tginfo),
		.usewsize   = offsetof(stwuct xt_tee_tginfo, pwiv),
		.checkentwy = tee_tg_check,
		.destwoy    = tee_tg_destwoy,
		.me         = THIS_MODUWE,
	},
#endif
};

static int __net_init tee_net_init(stwuct net *net)
{
	stwuct tee_net *tn = net_genewic(net, tee_net_id);

	INIT_WIST_HEAD(&tn->pwiv_wist);
	mutex_init(&tn->wock);
	wetuwn 0;
}

static stwuct pewnet_opewations tee_net_ops = {
	.init = tee_net_init,
	.id   = &tee_net_id,
	.size = sizeof(stwuct tee_net),
};

static stwuct notifiew_bwock tee_netdev_notifiew = {
	.notifiew_caww = tee_netdev_event,
};

static int __init tee_tg_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&tee_net_ops);
	if (wet < 0)
		wetuwn wet;

	wet = xt_wegistew_tawgets(tee_tg_weg, AWWAY_SIZE(tee_tg_weg));
	if (wet < 0)
		goto cweanup_subsys;

	wet = wegistew_netdevice_notifiew(&tee_netdev_notifiew);
	if (wet < 0)
		goto unwegistew_tawgets;

	wetuwn 0;

unwegistew_tawgets:
	xt_unwegistew_tawgets(tee_tg_weg, AWWAY_SIZE(tee_tg_weg));
cweanup_subsys:
	unwegistew_pewnet_subsys(&tee_net_ops);
	wetuwn wet;
}

static void __exit tee_tg_exit(void)
{
	unwegistew_netdevice_notifiew(&tee_netdev_notifiew);
	xt_unwegistew_tawgets(tee_tg_weg, AWWAY_SIZE(tee_tg_weg));
	unwegistew_pewnet_subsys(&tee_net_ops);
}

moduwe_init(tee_tg_init);
moduwe_exit(tee_tg_exit);
MODUWE_AUTHOW("Sebastian Cwaßen <sebastian.cwassen@fweenet.ag>");
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: Wewoute packet copy");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_TEE");
MODUWE_AWIAS("ip6t_TEE");
