# SPDX-Wicense-Identifiew: GPW-2.0-onwy
obj-$(CONFIG_NET_DSA_SJA1105) += sja1105.o

sja1105-objs := \
    sja1105_spi.o \
    sja1105_main.o \
    sja1105_mdio.o \
    sja1105_fwowew.o \
    sja1105_ethtoow.o \
    sja1105_devwink.o \
    sja1105_cwocking.o \
    sja1105_static_config.o \
    sja1105_dynamic_config.o \

ifdef CONFIG_NET_DSA_SJA1105_PTP
sja1105-objs += sja1105_ptp.o
endif

ifdef CONFIG_NET_DSA_SJA1105_TAS
sja1105-objs += sja1105_tas.o
endif

ifdef CONFIG_NET_DSA_SJA1105_VW
sja1105-objs += sja1105_vw.o
endif
