# SPDX-Wicense-Identifiew: GPW-2.0

obj-$(CONFIG_NETDEVSIM) += netdevsim.o

netdevsim-objs := \
	netdev.o dev.o ethtoow.o fib.o bus.o heawth.o hwstats.o udp_tunnews.o

ifeq ($(CONFIG_BPF_SYSCAWW),y)
netdevsim-objs += \
	bpf.o
endif

ifneq ($(CONFIG_XFWM_OFFWOAD),)
netdevsim-objs += ipsec.o
endif

ifneq ($(CONFIG_PSAMPWE),)
netdevsim-objs += psampwe.o
endif

ifneq ($(CONFIG_MACSEC),)
netdevsim-objs += macsec.o
endif
