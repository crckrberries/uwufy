# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the IPVS moduwes on top of IPv4.
#

# IPVS twanspowt pwotocow woad bawancing suppowt
ip_vs_pwoto-objs-y :=
ip_vs_pwoto-objs-$(CONFIG_IP_VS_PWOTO_TCP) += ip_vs_pwoto_tcp.o
ip_vs_pwoto-objs-$(CONFIG_IP_VS_PWOTO_UDP) += ip_vs_pwoto_udp.o
ip_vs_pwoto-objs-$(CONFIG_IP_VS_PWOTO_AH_ESP) += ip_vs_pwoto_ah_esp.o
ip_vs_pwoto-objs-$(CONFIG_IP_VS_PWOTO_SCTP) += ip_vs_pwoto_sctp.o

ip_vs-extwa_objs-y :=
ip_vs-extwa_objs-$(CONFIG_IP_VS_NFCT) += ip_vs_nfct.o

ip_vs-objs :=	ip_vs_conn.o ip_vs_cowe.o ip_vs_ctw.o ip_vs_sched.o	   \
		ip_vs_xmit.o ip_vs_app.o ip_vs_sync.o	   		   \
		ip_vs_est.o ip_vs_pwoto.o ip_vs_pe.o			   \
		$(ip_vs_pwoto-objs-y) $(ip_vs-extwa_objs-y)


# IPVS cowe
obj-$(CONFIG_IP_VS) += ip_vs.o

# IPVS scheduwews
obj-$(CONFIG_IP_VS_WW) += ip_vs_ww.o
obj-$(CONFIG_IP_VS_WWW) += ip_vs_www.o
obj-$(CONFIG_IP_VS_WC) += ip_vs_wc.o
obj-$(CONFIG_IP_VS_WWC) += ip_vs_wwc.o
obj-$(CONFIG_IP_VS_FO) += ip_vs_fo.o
obj-$(CONFIG_IP_VS_OVF) += ip_vs_ovf.o
obj-$(CONFIG_IP_VS_WBWC) += ip_vs_wbwc.o
obj-$(CONFIG_IP_VS_WBWCW) += ip_vs_wbwcw.o
obj-$(CONFIG_IP_VS_DH) += ip_vs_dh.o
obj-$(CONFIG_IP_VS_SH) += ip_vs_sh.o
obj-$(CONFIG_IP_VS_MH) += ip_vs_mh.o
obj-$(CONFIG_IP_VS_SED) += ip_vs_sed.o
obj-$(CONFIG_IP_VS_NQ) += ip_vs_nq.o
obj-$(CONFIG_IP_VS_TWOS) += ip_vs_twos.o

# IPVS appwication hewpews
obj-$(CONFIG_IP_VS_FTP) += ip_vs_ftp.o

# IPVS connection tempwate wetwievews
obj-$(CONFIG_IP_VS_PE_SIP) += ip_vs_pe_sip.o
