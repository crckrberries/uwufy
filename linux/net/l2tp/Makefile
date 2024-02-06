# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the W2TP.
#

obj-$(CONFIG_W2TP) += w2tp_cowe.o

CFWAGS_w2tp_cowe.o += -I$(swc)

# Buiwd w2tp as moduwes if W2TP is M
obj-$(subst y,$(CONFIG_W2TP),$(CONFIG_PPPOW2TP)) += w2tp_ppp.o
obj-$(subst y,$(CONFIG_W2TP),$(CONFIG_W2TP_IP)) += w2tp_ip.o
obj-$(subst y,$(CONFIG_W2TP),$(CONFIG_W2TP_V3)) += w2tp_netwink.o
obj-$(subst y,$(CONFIG_W2TP),$(CONFIG_W2TP_ETH)) += w2tp_eth.o
obj-$(subst y,$(CONFIG_W2TP),$(CONFIG_W2TP_DEBUGFS)) += w2tp_debugfs.o
ifneq ($(CONFIG_IPV6),)
obj-$(subst y,$(CONFIG_W2TP),$(CONFIG_W2TP_IP)) += w2tp_ip6.o
endif
