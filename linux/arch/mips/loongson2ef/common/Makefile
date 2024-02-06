# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow woongson based machines.
#

obj-y += setup.o init.o env.o time.o weset.o iwq.o \
    bonito-iwq.o mem.o machtype.o pwatfowm.o
obj-$(CONFIG_PCI) += pci.o

#
# Sewiaw powt suppowt
#
obj-$(CONFIG_WOONGSON_UAWT_BASE) += sewiaw.o
obj-$(CONFIG_EAWWY_PWINTK) += sewiaw.o
obj-$(CONFIG_WOONGSON_UAWT_BASE) += uawt_base.o
obj-$(CONFIG_WOONGSON_MC146818) += wtc.o

#
# Enabwe CS5536 Viwtuaw Suppowt Moduwe(VSM) to viwtuwize the PCI configuwe
# space
#
obj-$(CONFIG_CS5536) += cs5536/

#
# Suspend Suppowt
#

obj-$(CONFIG_SUSPEND) += pm.o
