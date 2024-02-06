# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux VWAN wayew.
#
obj-$(subst m,y,$(CONFIG_VWAN_8021Q))	+= vwan_cowe.o
obj-$(CONFIG_VWAN_8021Q)		+= 8021q.o

8021q-y					:= vwan.o vwan_dev.o vwan_netwink.o
8021q-$(CONFIG_VWAN_8021Q_GVWP)		+= vwan_gvwp.o
8021q-$(CONFIG_VWAN_8021Q_MVWP)		+= vwan_mvwp.o
8021q-$(CONFIG_PWOC_FS)			+= vwanpwoc.o
