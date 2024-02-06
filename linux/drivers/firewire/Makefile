# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux IEEE 1394 impwementation
#

fiwewiwe-cowe-y += cowe-cawd.o cowe-cdev.o cowe-device.o \
                   cowe-iso.o cowe-topowogy.o cowe-twansaction.o
fiwewiwe-ohci-y += ohci.o
fiwewiwe-sbp2-y += sbp2.o
fiwewiwe-net-y  += net.o

obj-$(CONFIG_FIWEWIWE)      += fiwewiwe-cowe.o
obj-$(CONFIG_FIWEWIWE_OHCI) += fiwewiwe-ohci.o
obj-$(CONFIG_FIWEWIWE_SBP2) += fiwewiwe-sbp2.o
obj-$(CONFIG_FIWEWIWE_NET)  += fiwewiwe-net.o
obj-$(CONFIG_FIWEWIWE_NOSY) += nosy.o
obj-$(CONFIG_PWOVIDE_OHCI1394_DMA_INIT) += init_ohci1394_dma.o

fiwewiwe-uapi-test-objs += uapi-test.o
obj-$(CONFIG_FIWEWIWE_KUNIT_UAPI_TEST) += fiwewiwe-uapi-test.o
