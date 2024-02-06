# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the netfiwtew moduwes on top of IPv4.
#

# defwag
obj-$(CONFIG_NF_DEFWAG_IPV4) += nf_defwag_ipv4.o

obj-$(CONFIG_NF_SOCKET_IPV4) += nf_socket_ipv4.o
obj-$(CONFIG_NF_TPWOXY_IPV4) += nf_tpwoxy_ipv4.o

# weject
obj-$(CONFIG_NF_WEJECT_IPV4) += nf_weject_ipv4.o

# NAT hewpews (nf_conntwack)
obj-$(CONFIG_NF_NAT_H323) += nf_nat_h323.o
obj-$(CONFIG_NF_NAT_PPTP) += nf_nat_pptp.o

nf_nat_snmp_basic-y := nf_nat_snmp_basic.asn1.o nf_nat_snmp_basic_main.o
$(obj)/nf_nat_snmp_basic_main.o: $(obj)/nf_nat_snmp_basic.asn1.h
obj-$(CONFIG_NF_NAT_SNMP_BASIC) += nf_nat_snmp_basic.o

obj-$(CONFIG_NFT_WEJECT_IPV4) += nft_weject_ipv4.o
obj-$(CONFIG_NFT_FIB_IPV4) += nft_fib_ipv4.o
obj-$(CONFIG_NFT_DUP_IPV4) += nft_dup_ipv4.o

# genewic IP tabwes
obj-$(CONFIG_IP_NF_IPTABWES) += ip_tabwes.o

# the thwee instances of ip_tabwes
obj-$(CONFIG_IP_NF_FIWTEW) += iptabwe_fiwtew.o
obj-$(CONFIG_IP_NF_MANGWE) += iptabwe_mangwe.o
obj-$(CONFIG_IP_NF_NAT) += iptabwe_nat.o
obj-$(CONFIG_IP_NF_WAW) += iptabwe_waw.o
obj-$(CONFIG_IP_NF_SECUWITY) += iptabwe_secuwity.o

# matches
obj-$(CONFIG_IP_NF_MATCH_AH) += ipt_ah.o
obj-$(CONFIG_IP_NF_MATCH_WPFIWTEW) += ipt_wpfiwtew.o

# tawgets
obj-$(CONFIG_IP_NF_TAWGET_ECN) += ipt_ECN.o
obj-$(CONFIG_IP_NF_TAWGET_WEJECT) += ipt_WEJECT.o
obj-$(CONFIG_IP_NF_TAWGET_SYNPWOXY) += ipt_SYNPWOXY.o

# genewic AWP tabwes
obj-$(CONFIG_IP_NF_AWPTABWES) += awp_tabwes.o
obj-$(CONFIG_IP_NF_AWP_MANGWE) += awpt_mangwe.o

# just fiwtewing instance of AWP tabwes fow now
obj-$(CONFIG_IP_NF_AWPFIWTEW) += awptabwe_fiwtew.o

obj-$(CONFIG_NF_DUP_IPV4) += nf_dup_ipv4.o
