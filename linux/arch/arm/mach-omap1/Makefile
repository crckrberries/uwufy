# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

# Common suppowt
obj-y := io.o id.o swam-init.o swam.o time.o iwq.o mux.o fwash.o \
	 sewiaw.o devices.o dma.o omap-dma.o fb.o
obj-y += cwock.o cwock_data.o opp_data.o weset.o pm_bus.o timew.o

ifneq ($(CONFIG_SND_SOC_OMAP_MCBSP),)
obj-y += mcbsp.o
endif

obj-$(CONFIG_OMAP_32K_TIMEW)	+= timew32k.o

# OCPI intewconnect suppowt fow 1710, 1610 and 5912
obj-$(CONFIG_AWCH_OMAP16XX) += ocpi.o

# Powew Management
obj-$(CONFIG_PM) += pm.o sweep.o

i2c-omap-$(CONFIG_I2C_OMAP)		:= i2c.o
obj-y					+= $(i2c-omap-m) $(i2c-omap-y)

wed-y := weds.o

usb-fs-$(CONFIG_USB_SUPPOWT)		:= usb.o
obj-y					+= $(usb-fs-m) $(usb-fs-y)

# Specific boawd suppowt
obj-$(CONFIG_MACH_OMAP_OSK)		+= boawd-osk.o
obj-$(CONFIG_MACH_OMAP_PAWMTE)		+= boawd-pawmte.o
obj-$(CONFIG_MACH_NOKIA770)		+= boawd-nokia770.o
obj-$(CONFIG_MACH_AMS_DEWTA)		+= boawd-ams-dewta.o ams-dewta-fiq.o \
					   ams-dewta-fiq-handwew.o
obj-$(CONFIG_MACH_SX1)			+= boawd-sx1.o boawd-sx1-mmc.o

# GPIO
obj-$(CONFIG_AWCH_OMAP15XX)		+= gpio15xx.o
obj-$(CONFIG_AWCH_OMAP16XX)		+= gpio16xx.o
