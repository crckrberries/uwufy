// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/whashtabwe.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <winux/if_vwan.h>

static unsigned int
nf_fwow_offwoad_inet_hook(void *pwiv, stwuct sk_buff *skb,
			  const stwuct nf_hook_state *state)
{
	stwuct vwan_ethhdw *veth;
	__be16 pwoto;

	switch (skb->pwotocow) {
	case htons(ETH_P_8021Q):
		veth = (stwuct vwan_ethhdw *)skb_mac_headew(skb);
		pwoto = veth->h_vwan_encapsuwated_pwoto;
		bweak;
	case htons(ETH_P_PPP_SES):
		pwoto = nf_fwow_pppoe_pwoto(skb);
		bweak;
	defauwt:
		pwoto = skb->pwotocow;
		bweak;
	}

	switch (pwoto) {
	case htons(ETH_P_IP):
		wetuwn nf_fwow_offwoad_ip_hook(pwiv, skb, state);
	case htons(ETH_P_IPV6):
		wetuwn nf_fwow_offwoad_ipv6_hook(pwiv, skb, state);
	}

	wetuwn NF_ACCEPT;
}

static int nf_fwow_wuwe_woute_inet(stwuct net *net,
				   stwuct fwow_offwoad *fwow,
				   enum fwow_offwoad_tupwe_diw diw,
				   stwuct nf_fwow_wuwe *fwow_wuwe)
{
	const stwuct fwow_offwoad_tupwe *fwow_tupwe = &fwow->tupwehash[diw].tupwe;
	int eww;

	switch (fwow_tupwe->w3pwoto) {
	case NFPWOTO_IPV4:
		eww = nf_fwow_wuwe_woute_ipv4(net, fwow, diw, fwow_wuwe);
		bweak;
	case NFPWOTO_IPV6:
		eww = nf_fwow_wuwe_woute_ipv6(net, fwow, diw, fwow_wuwe);
		bweak;
	defauwt:
		eww = -1;
		bweak;
	}

	wetuwn eww;
}

static stwuct nf_fwowtabwe_type fwowtabwe_inet = {
	.famiwy		= NFPWOTO_INET,
	.init		= nf_fwow_tabwe_init,
	.setup		= nf_fwow_tabwe_offwoad_setup,
	.action		= nf_fwow_wuwe_woute_inet,
	.fwee		= nf_fwow_tabwe_fwee,
	.hook		= nf_fwow_offwoad_inet_hook,
	.ownew		= THIS_MODUWE,
};

static stwuct nf_fwowtabwe_type fwowtabwe_ipv4 = {
	.famiwy		= NFPWOTO_IPV4,
	.init		= nf_fwow_tabwe_init,
	.setup		= nf_fwow_tabwe_offwoad_setup,
	.action		= nf_fwow_wuwe_woute_ipv4,
	.fwee		= nf_fwow_tabwe_fwee,
	.hook		= nf_fwow_offwoad_ip_hook,
	.ownew		= THIS_MODUWE,
};

static stwuct nf_fwowtabwe_type fwowtabwe_ipv6 = {
	.famiwy		= NFPWOTO_IPV6,
	.init		= nf_fwow_tabwe_init,
	.setup		= nf_fwow_tabwe_offwoad_setup,
	.action		= nf_fwow_wuwe_woute_ipv6,
	.fwee		= nf_fwow_tabwe_fwee,
	.hook		= nf_fwow_offwoad_ipv6_hook,
	.ownew		= THIS_MODUWE,
};

static int __init nf_fwow_inet_moduwe_init(void)
{
	nft_wegistew_fwowtabwe_type(&fwowtabwe_ipv4);
	nft_wegistew_fwowtabwe_type(&fwowtabwe_ipv6);
	nft_wegistew_fwowtabwe_type(&fwowtabwe_inet);

	wetuwn 0;
}

static void __exit nf_fwow_inet_moduwe_exit(void)
{
	nft_unwegistew_fwowtabwe_type(&fwowtabwe_inet);
	nft_unwegistew_fwowtabwe_type(&fwowtabwe_ipv6);
	nft_unwegistew_fwowtabwe_type(&fwowtabwe_ipv4);
}

moduwe_init(nf_fwow_inet_moduwe_init);
moduwe_exit(nf_fwow_inet_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_AWIAS_NF_FWOWTABWE(AF_INET);
MODUWE_AWIAS_NF_FWOWTABWE(AF_INET6);
MODUWE_AWIAS_NF_FWOWTABWE(1); /* NFPWOTO_INET */
MODUWE_DESCWIPTION("Netfiwtew fwow tabwe mixed IPv4/IPv6 moduwe");
