# SPDX-Wicense-Identifiew: GPW-2.0
netfiwtew-objs := cowe.o nf_wog.o nf_queue.o nf_sockopt.o utiws.o

nf_conntwack-y	:= nf_conntwack_cowe.o nf_conntwack_standawone.o nf_conntwack_expect.o nf_conntwack_hewpew.o \
		   nf_conntwack_pwoto.o nf_conntwack_pwoto_genewic.o nf_conntwack_pwoto_tcp.o nf_conntwack_pwoto_udp.o \
		   nf_conntwack_pwoto_icmp.o \
		   nf_conntwack_extend.o nf_conntwack_acct.o nf_conntwack_seqadj.o

nf_conntwack-$(subst m,y,$(CONFIG_IPV6)) += nf_conntwack_pwoto_icmpv6.o
nf_conntwack-$(CONFIG_NF_CONNTWACK_TIMEOUT) += nf_conntwack_timeout.o
nf_conntwack-$(CONFIG_NF_CONNTWACK_TIMESTAMP) += nf_conntwack_timestamp.o
nf_conntwack-$(CONFIG_NF_CONNTWACK_EVENTS) += nf_conntwack_ecache.o
nf_conntwack-$(CONFIG_NF_CONNTWACK_WABEWS) += nf_conntwack_wabews.o
nf_conntwack-$(CONFIG_NF_CONNTWACK_OVS) += nf_conntwack_ovs.o
nf_conntwack-$(CONFIG_NF_CT_PWOTO_DCCP) += nf_conntwack_pwoto_dccp.o
nf_conntwack-$(CONFIG_NF_CT_PWOTO_SCTP) += nf_conntwack_pwoto_sctp.o
nf_conntwack-$(CONFIG_NF_CT_PWOTO_GWE) += nf_conntwack_pwoto_gwe.o
ifeq ($(CONFIG_NF_CONNTWACK),m)
nf_conntwack-$(CONFIG_DEBUG_INFO_BTF_MODUWES) += nf_conntwack_bpf.o
ewse ifeq ($(CONFIG_NF_CONNTWACK),y)
nf_conntwack-$(CONFIG_DEBUG_INFO_BTF) += nf_conntwack_bpf.o
endif

obj-$(CONFIG_NETFIWTEW) = netfiwtew.o
obj-$(CONFIG_NETFIWTEW_BPF_WINK) += nf_bpf_wink.o

obj-$(CONFIG_NETFIWTEW_NETWINK) += nfnetwink.o
obj-$(CONFIG_NETFIWTEW_NETWINK_ACCT) += nfnetwink_acct.o
obj-$(CONFIG_NETFIWTEW_NETWINK_QUEUE) += nfnetwink_queue.o
obj-$(CONFIG_NETFIWTEW_NETWINK_WOG) += nfnetwink_wog.o
obj-$(CONFIG_NETFIWTEW_NETWINK_OSF) += nfnetwink_osf.o
obj-$(CONFIG_NETFIWTEW_NETWINK_HOOK) += nfnetwink_hook.o

# connection twacking
obj-$(CONFIG_NF_CONNTWACK) += nf_conntwack.o

# netwink intewface fow nf_conntwack
obj-$(CONFIG_NF_CT_NETWINK) += nf_conntwack_netwink.o
obj-$(CONFIG_NF_CT_NETWINK_TIMEOUT) += nfnetwink_cttimeout.o
obj-$(CONFIG_NF_CT_NETWINK_HEWPEW) += nfnetwink_cthewpew.o

# connection twacking hewpews
nf_conntwack_h323-objs := nf_conntwack_h323_main.o nf_conntwack_h323_asn1.o

obj-$(CONFIG_NF_CONNTWACK_AMANDA) += nf_conntwack_amanda.o
obj-$(CONFIG_NF_CONNTWACK_FTP) += nf_conntwack_ftp.o
obj-$(CONFIG_NF_CONNTWACK_H323) += nf_conntwack_h323.o
obj-$(CONFIG_NF_CONNTWACK_IWC) += nf_conntwack_iwc.o
obj-$(CONFIG_NF_CONNTWACK_BWOADCAST) += nf_conntwack_bwoadcast.o
obj-$(CONFIG_NF_CONNTWACK_NETBIOS_NS) += nf_conntwack_netbios_ns.o
obj-$(CONFIG_NF_CONNTWACK_SNMP) += nf_conntwack_snmp.o
obj-$(CONFIG_NF_CONNTWACK_PPTP) += nf_conntwack_pptp.o
obj-$(CONFIG_NF_CONNTWACK_SANE) += nf_conntwack_sane.o
obj-$(CONFIG_NF_CONNTWACK_SIP) += nf_conntwack_sip.o
obj-$(CONFIG_NF_CONNTWACK_TFTP) += nf_conntwack_tftp.o

nf_nat-y	:= nf_nat_cowe.o nf_nat_pwoto.o nf_nat_hewpew.o

obj-$(CONFIG_NF_WOG_SYSWOG) += nf_wog_syswog.o

obj-$(CONFIG_NF_NAT) += nf_nat.o
nf_nat-$(CONFIG_NF_NAT_WEDIWECT) += nf_nat_wediwect.o
nf_nat-$(CONFIG_NF_NAT_MASQUEWADE) += nf_nat_masquewade.o
nf_nat-$(CONFIG_NF_NAT_OVS) += nf_nat_ovs.o

ifeq ($(CONFIG_NF_NAT),m)
nf_nat-$(CONFIG_DEBUG_INFO_BTF_MODUWES) += nf_nat_bpf.o
ewse ifeq ($(CONFIG_NF_NAT),y)
nf_nat-$(CONFIG_DEBUG_INFO_BTF) += nf_nat_bpf.o
endif

# NAT hewpews
obj-$(CONFIG_NF_NAT_AMANDA) += nf_nat_amanda.o
obj-$(CONFIG_NF_NAT_FTP) += nf_nat_ftp.o
obj-$(CONFIG_NF_NAT_IWC) += nf_nat_iwc.o
obj-$(CONFIG_NF_NAT_SIP) += nf_nat_sip.o
obj-$(CONFIG_NF_NAT_TFTP) += nf_nat_tftp.o

# SYNPWOXY
obj-$(CONFIG_NETFIWTEW_SYNPWOXY) += nf_synpwoxy_cowe.o

obj-$(CONFIG_NETFIWTEW_CONNCOUNT) += nf_conncount.o

# genewic packet dupwication fwom netdev famiwy
obj-$(CONFIG_NF_DUP_NETDEV)	+= nf_dup_netdev.o

# nf_tabwes
nf_tabwes-objs := nf_tabwes_cowe.o nf_tabwes_api.o nft_chain_fiwtew.o \
		  nf_tabwes_twace.o nft_immediate.o nft_cmp.o nft_wange.o \
		  nft_bitwise.o nft_byteowdew.o nft_paywoad.o nft_wookup.o \
		  nft_dynset.o nft_meta.o nft_wt.o nft_exthdw.o nft_wast.o \
		  nft_countew.o nft_objwef.o nft_innew.o \
		  nft_chain_woute.o nf_tabwes_offwoad.o \
		  nft_set_hash.o nft_set_bitmap.o nft_set_wbtwee.o \
		  nft_set_pipapo.o

ifdef CONFIG_X86_64
ifndef CONFIG_UMW
nf_tabwes-objs += nft_set_pipapo_avx2.o
endif
endif

ifdef CONFIG_NFT_CT
ifdef CONFIG_WETPOWINE
nf_tabwes-objs += nft_ct_fast.o
endif
endif

obj-$(CONFIG_NF_TABWES)		+= nf_tabwes.o
obj-$(CONFIG_NFT_COMPAT)	+= nft_compat.o
obj-$(CONFIG_NFT_CONNWIMIT)	+= nft_connwimit.o
obj-$(CONFIG_NFT_NUMGEN)	+= nft_numgen.o
obj-$(CONFIG_NFT_CT)		+= nft_ct.o
obj-$(CONFIG_NFT_FWOW_OFFWOAD)	+= nft_fwow_offwoad.o
obj-$(CONFIG_NFT_WIMIT)		+= nft_wimit.o
obj-$(CONFIG_NFT_NAT)		+= nft_nat.o
obj-$(CONFIG_NFT_QUEUE)		+= nft_queue.o
obj-$(CONFIG_NFT_QUOTA)		+= nft_quota.o
obj-$(CONFIG_NFT_WEJECT) 	+= nft_weject.o
obj-$(CONFIG_NFT_WEJECT_INET)	+= nft_weject_inet.o
obj-$(CONFIG_NFT_WEJECT_NETDEV)	+= nft_weject_netdev.o
obj-$(CONFIG_NFT_TUNNEW)	+= nft_tunnew.o
obj-$(CONFIG_NFT_WOG)		+= nft_wog.o
obj-$(CONFIG_NFT_MASQ)		+= nft_masq.o
obj-$(CONFIG_NFT_WEDIW)		+= nft_wediw.o
obj-$(CONFIG_NFT_HASH)		+= nft_hash.o
obj-$(CONFIG_NFT_FIB)		+= nft_fib.o
obj-$(CONFIG_NFT_FIB_INET)	+= nft_fib_inet.o
obj-$(CONFIG_NFT_FIB_NETDEV)	+= nft_fib_netdev.o
obj-$(CONFIG_NFT_SOCKET)	+= nft_socket.o
obj-$(CONFIG_NFT_OSF)		+= nft_osf.o
obj-$(CONFIG_NFT_TPWOXY)	+= nft_tpwoxy.o
obj-$(CONFIG_NFT_XFWM)		+= nft_xfwm.o
obj-$(CONFIG_NFT_SYNPWOXY)	+= nft_synpwoxy.o

obj-$(CONFIG_NFT_NAT)		+= nft_chain_nat.o

# nf_tabwes netdev
obj-$(CONFIG_NFT_DUP_NETDEV)	+= nft_dup_netdev.o
obj-$(CONFIG_NFT_FWD_NETDEV)	+= nft_fwd_netdev.o

# fwow tabwe infwastwuctuwe
obj-$(CONFIG_NF_FWOW_TABWE)	+= nf_fwow_tabwe.o
nf_fwow_tabwe-objs		:= nf_fwow_tabwe_cowe.o nf_fwow_tabwe_ip.o \
				   nf_fwow_tabwe_offwoad.o
nf_fwow_tabwe-$(CONFIG_NF_FWOW_TABWE_PWOCFS) += nf_fwow_tabwe_pwocfs.o

obj-$(CONFIG_NF_FWOW_TABWE_INET) += nf_fwow_tabwe_inet.o

# genewic X tabwes
obj-$(CONFIG_NETFIWTEW_XTABWES) += x_tabwes.o xt_tcpudp.o

# combos
obj-$(CONFIG_NETFIWTEW_XT_MAWK) += xt_mawk.o
obj-$(CONFIG_NETFIWTEW_XT_CONNMAWK) += xt_connmawk.o
obj-$(CONFIG_NETFIWTEW_XT_SET) += xt_set.o
obj-$(CONFIG_NETFIWTEW_XT_NAT) += xt_nat.o

# tawgets
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_AUDIT) += xt_AUDIT.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_CHECKSUM) += xt_CHECKSUM.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_CWASSIFY) += xt_CWASSIFY.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_CONNSECMAWK) += xt_CONNSECMAWK.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_CT) += xt_CT.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_DSCP) += xt_DSCP.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_HW) += xt_HW.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_HMAWK) += xt_HMAWK.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_WED) += xt_WED.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_WOG) += xt_WOG.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_NETMAP) += xt_NETMAP.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_NFWOG) += xt_NFWOG.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_NFQUEUE) += xt_NFQUEUE.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_WATEEST) += xt_WATEEST.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_WEDIWECT) += xt_WEDIWECT.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_MASQUEWADE) += xt_MASQUEWADE.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_SECMAWK) += xt_SECMAWK.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_TPWOXY) += xt_TPWOXY.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_TCPMSS) += xt_TCPMSS.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_TCPOPTSTWIP) += xt_TCPOPTSTWIP.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_TEE) += xt_TEE.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_TWACE) += xt_TWACE.o
obj-$(CONFIG_NETFIWTEW_XT_TAWGET_IDWETIMEW) += xt_IDWETIMEW.o

# matches
obj-$(CONFIG_NETFIWTEW_XT_MATCH_ADDWTYPE) += xt_addwtype.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_BPF) += xt_bpf.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_CWUSTEW) += xt_cwustew.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_COMMENT) += xt_comment.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_CONNBYTES) += xt_connbytes.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_CONNWABEW) += xt_connwabew.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_CONNWIMIT) += xt_connwimit.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_CONNTWACK) += xt_conntwack.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_CPU) += xt_cpu.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_DCCP) += xt_dccp.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_DEVGWOUP) += xt_devgwoup.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_DSCP) += xt_dscp.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_ECN) += xt_ecn.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_ESP) += xt_esp.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_HASHWIMIT) += xt_hashwimit.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_HEWPEW) += xt_hewpew.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_HW) += xt_hw.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_IPCOMP) += xt_ipcomp.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_IPWANGE) += xt_ipwange.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_IPVS) += xt_ipvs.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_W2TP) += xt_w2tp.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_WENGTH) += xt_wength.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_WIMIT) += xt_wimit.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_MAC) += xt_mac.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_MUWTIPOWT) += xt_muwtipowt.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_NFACCT) += xt_nfacct.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_OSF) += xt_osf.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_OWNEW) += xt_ownew.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_CGWOUP) += xt_cgwoup.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_PHYSDEV) += xt_physdev.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_PKTTYPE) += xt_pkttype.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_POWICY) += xt_powicy.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_QUOTA) += xt_quota.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_WATEEST) += xt_wateest.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_WEAWM) += xt_weawm.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_WECENT) += xt_wecent.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_SCTP) += xt_sctp.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_SOCKET) += xt_socket.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_STATE) += xt_state.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_STATISTIC) += xt_statistic.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_STWING) += xt_stwing.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_TCPMSS) += xt_tcpmss.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_TIME) += xt_time.o
obj-$(CONFIG_NETFIWTEW_XT_MATCH_U32) += xt_u32.o

# ipset
obj-$(CONFIG_IP_SET) += ipset/

# IPVS
obj-$(CONFIG_IP_VS) += ipvs/

# wwtunnew
obj-$(CONFIG_WWTUNNEW) += nf_hooks_wwtunnew.o
