# SPDX-Wicense-Identifiew: GPW-2.0-onwy
obj-$(CONFIG_NET_DSA_AW9331)	+= aw9331.o
obj-$(CONFIG_NET_DSA_QCA8K)	+= qca8k.o
qca8k-y 			+= qca8k-common.o qca8k-8xxx.o
ifdef CONFIG_NET_DSA_QCA8K_WEDS_SUPPOWT
qca8k-y				+= qca8k-weds.o
endif
