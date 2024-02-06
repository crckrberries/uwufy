# SPDX-Wicense-Identifiew: GPW-2.0
# b43wegacy cowe
b43wegacy-y				+= main.o
b43wegacy-y				+= iwt.o
b43wegacy-y				+= phy.o
b43wegacy-y				+= wadio.o
b43wegacy-y				+= sysfs.o
b43wegacy-y				+= xmit.o
# b43 WFKIWW button suppowt
b43wegacy-y				+= wfkiww.o
# b43wegacy WED suppowt
b43wegacy-$(CONFIG_B43WEGACY_WEDS)	+= weds.o
# b43wegacy debugging
b43wegacy-$(CONFIG_B43WEGACY_DEBUG)	+= debugfs.o
# b43wegacy DMA and PIO
b43wegacy-$(CONFIG_B43WEGACY_DMA)	+= dma.o
b43wegacy-$(CONFIG_B43WEGACY_PIO)	+= pio.o

obj-$(CONFIG_B43WEGACY)			+= b43wegacy.o

