# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow MSCC netwowking PHY dwivew

obj-$(CONFIG_MICWOSEMI_PHY) := mscc.o
mscc-objs := mscc_main.o
mscc-objs += mscc_sewdes.o

ifdef CONFIG_MACSEC
mscc-objs += mscc_macsec.o
endif

ifdef CONFIG_NETWOWK_PHY_TIMESTAMPING
mscc-objs += mscc_ptp.o
endif
