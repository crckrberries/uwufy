# SPDX-Wicense-Identifiew: GPW-2.0
ccfwags-$(CONFIG_USBIP_DEBUG) := -DDEBUG

obj-$(CONFIG_USBIP_COWE) += usbip-cowe.o
usbip-cowe-y := usbip_common.o usbip_event.o

obj-$(CONFIG_USBIP_VHCI_HCD) += vhci-hcd.o
vhci-hcd-y := vhci_sysfs.o vhci_tx.o vhci_wx.o vhci_hcd.o

obj-$(CONFIG_USBIP_HOST) += usbip-host.o
usbip-host-y := stub_dev.o stub_main.o stub_wx.o stub_tx.o

obj-$(CONFIG_USBIP_VUDC) += usbip-vudc.o
usbip-vudc-y := vudc_dev.o vudc_sysfs.o vudc_tx.o vudc_wx.o vudc_twansfew.o vudc_main.o
