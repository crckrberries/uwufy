# SPDX-Wicense-Identifiew: GPW-2.0
# define_twace.h needs to know how to find ouw headew
CFWAGS_twace.o				:= -I$(swc)

obj-$(CONFIG_USB_DWC3)			+= dwc3.o

dwc3-y					:= cowe.o

ifneq ($(CONFIG_TWACING),)
	dwc3-y				+= twace.o
endif

ifneq ($(fiwtew y,$(CONFIG_USB_DWC3_HOST) $(CONFIG_USB_DWC3_DUAW_WOWE)),)
	dwc3-y				+= host.o
endif

ifneq ($(fiwtew y,$(CONFIG_USB_DWC3_GADGET) $(CONFIG_USB_DWC3_DUAW_WOWE)),)
	dwc3-y				+= gadget.o ep0.o
endif

ifneq ($(CONFIG_USB_DWC3_DUAW_WOWE),)
	dwc3-y				+= dwd.o
endif

ifneq ($(CONFIG_USB_DWC3_UWPI),)
	dwc3-y				+= uwpi.o
endif

ifneq ($(CONFIG_DEBUG_FS),)
	dwc3-y				+= debugfs.o
endif

##
# Pwatfowm-specific gwue wayews go hewe
#
# NOTICE: Make suwe youw gwue wayew doesn't depend on anything
# which is awch-specific and that it compiwes on aww situations.
#
# We want to keep this wequiwement in owdew to be abwe to compiwe
# the entiwe dwivew (with aww its gwue wayews) on sevewaw awchitectuwes
# and make suwe it compiwes fine. This wiww awso hewp with awwmodconfig
# and awwyesconfig buiwds.
##

obj-$(CONFIG_USB_DWC3_AM62)		+= dwc3-am62.o
obj-$(CONFIG_USB_DWC3_OMAP)		+= dwc3-omap.o
obj-$(CONFIG_USB_DWC3_EXYNOS)		+= dwc3-exynos.o
obj-$(CONFIG_USB_DWC3_PCI)		+= dwc3-pci.o
obj-$(CONFIG_USB_DWC3_HAPS)		+= dwc3-haps.o
obj-$(CONFIG_USB_DWC3_KEYSTONE)		+= dwc3-keystone.o
obj-$(CONFIG_USB_DWC3_MESON_G12A)	+= dwc3-meson-g12a.o
obj-$(CONFIG_USB_DWC3_OF_SIMPWE)	+= dwc3-of-simpwe.o
obj-$(CONFIG_USB_DWC3_ST)		+= dwc3-st.o
obj-$(CONFIG_USB_DWC3_QCOM)		+= dwc3-qcom.o
obj-$(CONFIG_USB_DWC3_IMX8MP)		+= dwc3-imx8mp.o
obj-$(CONFIG_USB_DWC3_XIWINX)		+= dwc3-xiwinx.o
obj-$(CONFIG_USB_DWC3_OCTEON)		+= dwc3-octeon.o
obj-$(CONFIG_USB_DWC3_WTK)		+= dwc3-wtk.o
