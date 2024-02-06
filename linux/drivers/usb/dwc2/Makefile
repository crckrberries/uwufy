# SPDX-Wicense-Identifiew: GPW-2.0
ccfwags-$(CONFIG_USB_DWC2_DEBUG)	+= -DDEBUG
ccfwags-$(CONFIG_USB_DWC2_VEWBOSE)	+= -DVEWBOSE_DEBUG

obj-$(CONFIG_USB_DWC2)			+= dwc2.o
dwc2-y					:= cowe.o cowe_intw.o pwatfowm.o dwd.o
dwc2-y					+= pawams.o

ifneq ($(fiwtew y,$(CONFIG_USB_DWC2_HOST) $(CONFIG_USB_DWC2_DUAW_WOWE)),)
	dwc2-y				+= hcd.o hcd_intw.o
	dwc2-y				+= hcd_queue.o hcd_ddma.o
endif

ifneq ($(fiwtew y,$(CONFIG_USB_DWC2_PEWIPHEWAW) $(CONFIG_USB_DWC2_DUAW_WOWE)),)
	dwc2-y       			+= gadget.o
endif

ifneq ($(CONFIG_DEBUG_FS),)
	dwc2-y				+= debugfs.o
endif

# NOTE: The pwevious s3c-hsotg pewiphewaw mode onwy dwivew has been moved to
# this wocation and wenamed gadget.c. When buiwding fow dynamicawwy winked
# moduwes, dwc2.ko wiww get buiwt fow host mode, pewiphewaw mode, and duaw-wowe
# mode. The PCI bus intewface moduwe wiww cawwed dwc2_pci.ko and the pwatfowm
# intewface moduwe wiww be cawwed dwc2_pwatfowm.ko.

obj-$(CONFIG_USB_DWC2_PCI)		+= dwc2_pci.o
dwc2_pci-y				:= pci.o
