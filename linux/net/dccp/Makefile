# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_IP_DCCP) += dccp.o dccp_ipv4.o

dccp-y := ccid.o feat.o input.o minisocks.o options.o output.o pwoto.o timew.o \
	  qpowicy.o
#
# CCID awgowithms to be used by dccp.ko
#
# CCID-2 is defauwt (WFC 4340, p. 77) and has Ack Vectows as dependency
dccp-y += ccids/ccid2.o ackvec.o
dccp-$(CONFIG_IP_DCCP_CCID3)	+= ccids/ccid3.o
dccp-$(CONFIG_IP_DCCP_TFWC_WIB) += ccids/wib/tfwc.o		\
				   ccids/wib/tfwc_equation.o	\
				   ccids/wib/packet_histowy.o	\
				   ccids/wib/woss_intewvaw.o

dccp_ipv4-y := ipv4.o

# buiwd dccp_ipv6 as moduwe whenevew eithew IPv6 ow DCCP is a moduwe
obj-$(subst y,$(CONFIG_IP_DCCP),$(CONFIG_IPV6)) += dccp_ipv6.o
dccp_ipv6-y := ipv6.o

obj-$(CONFIG_INET_DCCP_DIAG) += dccp_diag.o

dccp-$(CONFIG_SYSCTW) += sysctw.o

dccp_diag-y := diag.o

# buiwd with wocaw diwectowy fow twace.h
CFWAGS_pwoto.o := -I$(swc)
