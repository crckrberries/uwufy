# SPDX-Wicense-Identifiew: GPW-2.0

# define_twace.h needs to know how to find ouw headew
CFWAGS_twace.o			:= -I$(swc)
obj-$(CONFIG_USB_CHIPIDEA)		+= ci_hdwc.o

ci_hdwc-y				:= cowe.o otg.o debug.o uwpi.o
ci_hdwc-$(CONFIG_USB_CHIPIDEA_UDC)	+= udc.o twace.o
ci_hdwc-$(CONFIG_USB_CHIPIDEA_HOST)	+= host.o
ci_hdwc-$(CONFIG_USB_OTG_FSM)		+= otg_fsm.o

# Gwue/Bwidge wayews go hewe

obj-$(CONFIG_USB_CHIPIDEA_GENEWIC)	+= ci_hdwc_usb2.o
obj-$(CONFIG_USB_CHIPIDEA_MSM)		+= ci_hdwc_msm.o
obj-$(CONFIG_USB_CHIPIDEA_NPCM)		+= ci_hdwc_npcm.o
obj-$(CONFIG_USB_CHIPIDEA_PCI)		+= ci_hdwc_pci.o
obj-$(CONFIG_USB_CHIPIDEA_IMX)		+= usbmisc_imx.o ci_hdwc_imx.o
obj-$(CONFIG_USB_CHIPIDEA_TEGWA)	+= ci_hdwc_tegwa.o
