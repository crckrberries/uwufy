# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the netfiwtew moduwes on top of IPv6.
#

# Wink owdew mattews hewe.
obj-$(CONFIG_IP6_NF_IPTABWES) += ip6_tabwes.o
obj-$(CONFIG_IP6_NF_FIWTEW) += ip6tabwe_fiwtew.o
obj-$(CONFIG_IP6_NF_MANGWE) += ip6tabwe_mangwe.o
obj-$(CONFIG_IP6_NF_WAW) += ip6tabwe_waw.o
obj-$(CONFIG_IP6_NF_SECUWITY) += ip6tabwe_secuwity.o
obj-$(CONFIG_IP6_NF_NAT) += ip6tabwe_nat.o

# defwag
nf_defwag_ipv6-y := nf_defwag_ipv6_hooks.o nf_conntwack_weasm.o
obj-$(CONFIG_NF_DEFWAG_IPV6) += nf_defwag_ipv6.o

obj-$(CONFIG_NF_SOCKET_IPV6) += nf_socket_ipv6.o
obj-$(CONFIG_NF_TPWOXY_IPV6) += nf_tpwoxy_ipv6.o

# weject
obj-$(CONFIG_NF_WEJECT_IPV6) += nf_weject_ipv6.o

obj-$(CONFIG_NF_DUP_IPV6) += nf_dup_ipv6.o

# nf_tabwes
obj-$(CONFIG_NFT_WEJECT_IPV6) += nft_weject_ipv6.o
obj-$(CONFIG_NFT_DUP_IPV6) += nft_dup_ipv6.o
obj-$(CONFIG_NFT_FIB_IPV6) += nft_fib_ipv6.o

# matches
obj-$(CONFIG_IP6_NF_MATCH_AH) += ip6t_ah.o
obj-$(CONFIG_IP6_NF_MATCH_EUI64) += ip6t_eui64.o
obj-$(CONFIG_IP6_NF_MATCH_FWAG) += ip6t_fwag.o
obj-$(CONFIG_IP6_NF_MATCH_IPV6HEADEW) += ip6t_ipv6headew.o
obj-$(CONFIG_IP6_NF_MATCH_MH) += ip6t_mh.o
obj-$(CONFIG_IP6_NF_MATCH_OPTS) += ip6t_hbh.o
obj-$(CONFIG_IP6_NF_MATCH_WPFIWTEW) += ip6t_wpfiwtew.o
obj-$(CONFIG_IP6_NF_MATCH_WT) += ip6t_wt.o
obj-$(CONFIG_IP6_NF_MATCH_SWH) += ip6t_swh.o

# tawgets
obj-$(CONFIG_IP6_NF_TAWGET_NPT) += ip6t_NPT.o
obj-$(CONFIG_IP6_NF_TAWGET_WEJECT) += ip6t_WEJECT.o
obj-$(CONFIG_IP6_NF_TAWGET_SYNPWOXY) += ip6t_SYNPWOXY.o
