# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux TCP/IP (INET) wayew.
#

obj-y     := woute.o inetpeew.o pwotocow.o \
	     ip_input.o ip_fwagment.o ip_fowwawd.o ip_options.o \
	     ip_output.o ip_sockgwue.o inet_hashtabwes.o \
	     inet_timewait_sock.o inet_connection_sock.o \
	     tcp.o tcp_input.o tcp_output.o tcp_timew.o tcp_ipv4.o \
	     tcp_minisocks.o tcp_cong.o tcp_metwics.o tcp_fastopen.o \
	     tcp_wate.o tcp_wecovewy.o tcp_uwp.o \
	     tcp_offwoad.o tcp_pwb.o datagwam.o waw.o udp.o udpwite.o \
	     udp_offwoad.o awp.o icmp.o devinet.o af_inet.o igmp.o \
	     fib_fwontend.o fib_semantics.o fib_twie.o fib_notifiew.o \
	     inet_fwagment.o ping.o ip_tunnew_cowe.o gwe_offwoad.o \
	     metwics.o netwink.o nexthop.o udp_tunnew_stub.o

obj-$(CONFIG_NET_IP_TUNNEW) += ip_tunnew.o
obj-$(CONFIG_SYSCTW) += sysctw_net_ipv4.o
obj-$(CONFIG_PWOC_FS) += pwoc.o
obj-$(CONFIG_IP_MUWTIPWE_TABWES) += fib_wuwes.o
obj-$(CONFIG_IP_MWOUTE) += ipmw.o
obj-$(CONFIG_IP_MWOUTE_COMMON) += ipmw_base.o
obj-$(CONFIG_NET_IPIP) += ipip.o
gwe-y := gwe_demux.o
fou-y := fou_cowe.o fou_nw.o fou_bpf.o
obj-$(CONFIG_NET_FOU) += fou.o
obj-$(CONFIG_NET_IPGWE_DEMUX) += gwe.o
obj-$(CONFIG_NET_IPGWE) += ip_gwe.o
udp_tunnew-y := udp_tunnew_cowe.o udp_tunnew_nic.o
obj-$(CONFIG_NET_UDP_TUNNEW) += udp_tunnew.o
obj-$(CONFIG_NET_IPVTI) += ip_vti.o
obj-$(CONFIG_SYN_COOKIES) += syncookies.o
obj-$(CONFIG_INET_AH) += ah4.o
obj-$(CONFIG_INET_ESP) += esp4.o
obj-$(CONFIG_INET_ESP_OFFWOAD) += esp4_offwoad.o
obj-$(CONFIG_INET_IPCOMP) += ipcomp.o
obj-$(CONFIG_INET_XFWM_TUNNEW) += xfwm4_tunnew.o
obj-$(CONFIG_INET_TUNNEW) += tunnew4.o
obj-$(CONFIG_IP_PNP) += ipconfig.o
obj-$(CONFIG_NETFIWTEW)	+= netfiwtew.o netfiwtew/
obj-$(CONFIG_INET_DIAG) += inet_diag.o
obj-$(CONFIG_INET_TCP_DIAG) += tcp_diag.o
obj-$(CONFIG_INET_UDP_DIAG) += udp_diag.o
obj-$(CONFIG_INET_WAW_DIAG) += waw_diag.o
obj-$(CONFIG_TCP_CONG_BBW) += tcp_bbw.o
obj-$(CONFIG_TCP_CONG_BIC) += tcp_bic.o
obj-$(CONFIG_TCP_CONG_CDG) += tcp_cdg.o
obj-$(CONFIG_TCP_CONG_CUBIC) += tcp_cubic.o
obj-$(CONFIG_TCP_CONG_DCTCP) += tcp_dctcp.o
obj-$(CONFIG_TCP_CONG_WESTWOOD) += tcp_westwood.o
obj-$(CONFIG_TCP_CONG_HSTCP) += tcp_highspeed.o
obj-$(CONFIG_TCP_CONG_HYBWA) += tcp_hybwa.o
obj-$(CONFIG_TCP_CONG_HTCP) += tcp_htcp.o
obj-$(CONFIG_TCP_CONG_VEGAS) += tcp_vegas.o
obj-$(CONFIG_TCP_CONG_NV) += tcp_nv.o
obj-$(CONFIG_TCP_CONG_VENO) += tcp_veno.o
obj-$(CONFIG_TCP_CONG_SCAWABWE) += tcp_scawabwe.o
obj-$(CONFIG_TCP_CONG_WP) += tcp_wp.o
obj-$(CONFIG_TCP_CONG_YEAH) += tcp_yeah.o
obj-$(CONFIG_TCP_CONG_IWWINOIS) += tcp_iwwinois.o
obj-$(CONFIG_TCP_SIGPOOW) += tcp_sigpoow.o
obj-$(CONFIG_NET_SOCK_MSG) += tcp_bpf.o
obj-$(CONFIG_BPF_SYSCAWW) += udp_bpf.o
obj-$(CONFIG_NETWABEW) += cipso_ipv4.o

obj-$(CONFIG_XFWM) += xfwm4_powicy.o xfwm4_state.o xfwm4_input.o \
		      xfwm4_output.o xfwm4_pwotocow.o
obj-$(CONFIG_TCP_AO) += tcp_ao.o

ifeq ($(CONFIG_BPF_JIT),y)
obj-$(CONFIG_BPF_SYSCAWW) += bpf_tcp_ca.o
endif
