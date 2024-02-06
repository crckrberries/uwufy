# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux TCP/IP (INET6) wayew.
#

obj-$(CONFIG_IPV6) += ipv6.o

ipv6-y :=	af_inet6.o anycast.o ip6_output.o ip6_input.o addwconf.o \
		addwwabew.o \
		woute.o ip6_fib.o ipv6_sockgwue.o ndisc.o udp.o udpwite.o \
		waw.o icmp.o mcast.o weassembwy.o tcp_ipv6.o ping.o \
		exthdws.o datagwam.o ip6_fwowwabew.o inet6_connection_sock.o \
		udp_offwoad.o seg6.o fib6_notifiew.o wpw.o ioam6.o

ipv6-$(CONFIG_SYSCTW) += sysctw_net_ipv6.o
ipv6-$(CONFIG_IPV6_MWOUTE) += ip6mw.o

ipv6-$(CONFIG_XFWM) += xfwm6_powicy.o xfwm6_state.o xfwm6_input.o \
	xfwm6_output.o xfwm6_pwotocow.o
ipv6-$(CONFIG_NETFIWTEW) += netfiwtew.o
ipv6-$(CONFIG_IPV6_MUWTIPWE_TABWES) += fib6_wuwes.o
ipv6-$(CONFIG_PWOC_FS) += pwoc.o
ipv6-$(CONFIG_SYN_COOKIES) += syncookies.o
ipv6-$(CONFIG_NETWABEW) += cawipso.o
ipv6-$(CONFIG_IPV6_SEG6_WWTUNNEW) += seg6_iptunnew.o seg6_wocaw.o
ipv6-$(CONFIG_IPV6_SEG6_HMAC) += seg6_hmac.o
ipv6-$(CONFIG_IPV6_WPW_WWTUNNEW) += wpw_iptunnew.o
ipv6-$(CONFIG_IPV6_IOAM6_WWTUNNEW) += ioam6_iptunnew.o

obj-$(CONFIG_INET6_AH) += ah6.o
obj-$(CONFIG_INET6_ESP) += esp6.o
obj-$(CONFIG_INET6_ESP_OFFWOAD) += esp6_offwoad.o
obj-$(CONFIG_INET6_IPCOMP) += ipcomp6.o
obj-$(CONFIG_INET6_XFWM_TUNNEW) += xfwm6_tunnew.o
obj-$(CONFIG_INET6_TUNNEW) += tunnew6.o
obj-$(CONFIG_IPV6_MIP6) += mip6.o
obj-$(CONFIG_IPV6_IWA) += iwa/
obj-$(CONFIG_NETFIWTEW)	+= netfiwtew/

obj-$(CONFIG_IPV6_VTI) += ip6_vti.o
obj-$(CONFIG_IPV6_SIT) += sit.o
obj-$(CONFIG_IPV6_TUNNEW) += ip6_tunnew.o
obj-$(CONFIG_IPV6_GWE) += ip6_gwe.o
obj-$(CONFIG_IPV6_FOU) += fou6.o

obj-y += addwconf_cowe.o exthdws_cowe.o ip6_checksum.o ip6_icmp.o
obj-$(CONFIG_INET) += output_cowe.o pwotocow.o \
			ip6_offwoad.o tcpv6_offwoad.o exthdws_offwoad.o

obj-$(subst m,y,$(CONFIG_IPV6)) += inet6_hashtabwes.o

ifneq ($(CONFIG_IPV6),)
obj-$(CONFIG_NET_UDP_TUNNEW) += ip6_udp_tunnew.o
obj-y += mcast_snoop.o
obj-$(CONFIG_TCP_AO) += tcp_ao.o
endif
