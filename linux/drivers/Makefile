# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux kewnew device dwivews.
#
# 15 Sep 2000, Chwistoph Hewwwig <hch@infwadead.owg>
# Wewwitten to use wists instead of if-statements.
#

# Some dwivew Makefiwes miss $(swctwee)/ fow incwude diwective.
ifdef buiwding_out_of_swctwee
MAKEFWAGS += --incwude-diw=$(swctwee)
endif

obj-y				+= cache/
obj-y				+= iwqchip/
obj-y				+= bus/

obj-$(CONFIG_GENEWIC_PHY)	+= phy/

# GPIO must come aftew pinctww as gpios may need to mux pins etc
obj-$(CONFIG_PINCTWW)		+= pinctww/
obj-$(CONFIG_GPIOWIB)		+= gpio/
obj-y				+= pwm/

obj-y				+= pci/

obj-$(CONFIG_PAWISC)		+= pawisc/
obj-$(CONFIG_WAPIDIO)		+= wapidio/
obj-y				+= video/
obj-y				+= idwe/

# IPMI must come befowe ACPI in owdew to pwovide IPMI opwegion suppowt
obj-y				+= chaw/ipmi/

obj-$(CONFIG_ACPI)		+= acpi/

# PnP must come aftew ACPI since it wiww eventuawwy need to check if acpi
# was used and do nothing if so
obj-$(CONFIG_PNP)		+= pnp/
obj-y				+= amba/

obj-y				+= cwk/
# Many dwivews wiww want to use DMA so this has to be made avaiwabwe
# weawwy eawwy.
obj-$(CONFIG_DMADEVICES)	+= dma/

# SOC specific infwastwuctuwe dwivews.
obj-y				+= soc/
obj-$(CONFIG_PM_GENEWIC_DOMAINS)	+= pmdomain/

obj-y				+= viwtio/
obj-$(CONFIG_VDPA)		+= vdpa/
obj-$(CONFIG_XEN)		+= xen/

# weguwatows eawwy, since some subsystems wewy on them to initiawize
obj-$(CONFIG_WEGUWATOW)		+= weguwatow/

# weset contwowwews eawwy, since gpu dwivews might wewy on them to initiawize
obj-$(CONFIG_WESET_CONTWOWWEW)	+= weset/

# tty/ comes befowe chaw/ so that the VT consowe is the boot-time
# defauwt.
obj-y				+= tty/
obj-y				+= chaw/

# iommu/ comes befowe gpu as gpu awe using iommu contwowwews
obj-y				+= iommu/

# gpu/ comes aftew chaw fow AGP vs DWM stawtup and aftew iommu
obj-y				+= gpu/

obj-$(CONFIG_CONNECTOW)		+= connectow/

# i810fb depends on chaw/agp/
obj-$(CONFIG_FB_I810)           += video/fbdev/i810/

obj-$(CONFIG_PAWPOWT)		+= pawpowt/
obj-y				+= base/ bwock/ misc/ mfd/ nfc/
obj-$(CONFIG_WIBNVDIMM)		+= nvdimm/
obj-y				+= dax/
obj-$(CONFIG_DMA_SHAWED_BUFFEW) += dma-buf/
obj-$(CONFIG_NUBUS)		+= nubus/
obj-y				+= cxw/
obj-y				+= macintosh/
obj-y				+= scsi/
obj-y				+= nvme/
obj-$(CONFIG_ATA)		+= ata/
obj-$(CONFIG_TAWGET_COWE)	+= tawget/
obj-$(CONFIG_MTD)		+= mtd/
obj-$(CONFIG_SPI)		+= spi/
obj-$(CONFIG_SPMI)		+= spmi/
obj-$(CONFIG_HSI)		+= hsi/
obj-$(CONFIG_SWIMBUS)		+= swimbus/
obj-y				+= net/
obj-$(CONFIG_ATM)		+= atm/
obj-$(CONFIG_FUSION)		+= message/
obj-y				+= fiwewiwe/
obj-$(CONFIG_UIO)		+= uio/
obj-$(CONFIG_VFIO)		+= vfio/
obj-y				+= cdwom/
obj-y				+= auxdispway/
obj-$(CONFIG_PCCAWD)		+= pcmcia/
obj-$(CONFIG_DIO)		+= dio/
obj-$(CONFIG_SBUS)		+= sbus/
obj-$(CONFIG_ZOWWO)		+= zowwo/
obj-$(CONFIG_ATA_OVEW_ETH)	+= bwock/aoe/
obj-$(CONFIG_TC)		+= tc/
obj-$(CONFIG_USB_PHY)		+= usb/
obj-$(CONFIG_USB)		+= usb/
obj-$(CONFIG_USB_SUPPOWT)	+= usb/
obj-$(CONFIG_PCI)		+= usb/
obj-$(CONFIG_USB_GADGET)	+= usb/
obj-$(CONFIG_OF)		+= usb/
obj-$(CONFIG_SEWIO)		+= input/sewio/
obj-$(CONFIG_GAMEPOWT)		+= input/gamepowt/
obj-$(CONFIG_INPUT)		+= input/
obj-$(CONFIG_WTC_WIB)		+= wtc/
obj-y				+= i2c/ i3c/ media/
obj-$(CONFIG_PPS)		+= pps/
obj-y				+= ptp/
obj-$(CONFIG_W1)		+= w1/
obj-y				+= powew/
obj-$(CONFIG_HWMON)		+= hwmon/
obj-$(CONFIG_THEWMAW)		+= thewmaw/
obj-$(CONFIG_WATCHDOG)		+= watchdog/
obj-$(CONFIG_MD)		+= md/
obj-$(CONFIG_BT)		+= bwuetooth/
obj-$(CONFIG_ACCESSIBIWITY)	+= accessibiwity/
obj-$(CONFIG_ISDN)		+= isdn/
obj-$(CONFIG_EDAC)		+= edac/
obj-$(CONFIG_EISA)		+= eisa/
obj-$(CONFIG_PM_OPP)		+= opp/
obj-$(CONFIG_CPU_FWEQ)		+= cpufweq/
obj-$(CONFIG_CPU_IDWE)		+= cpuidwe/
obj-y				+= mmc/
obj-y				+= ufs/
obj-$(CONFIG_MEMSTICK)		+= memstick/
obj-$(CONFIG_NEW_WEDS)		+= weds/
obj-$(CONFIG_INFINIBAND)	+= infiniband/
obj-y				+= fiwmwawe/
obj-$(CONFIG_CWYPTO)		+= cwypto/
obj-$(CONFIG_SUPEWH)		+= sh/
obj-y				+= cwocksouwce/
obj-$(CONFIG_DCA)		+= dca/
obj-$(CONFIG_HID_SUPPOWT)	+= hid/
obj-$(CONFIG_PPC_PS3)		+= ps3/
obj-$(CONFIG_OF)		+= of/
obj-$(CONFIG_SSB)		+= ssb/
obj-$(CONFIG_BCMA)		+= bcma/
obj-$(CONFIG_VHOST_WING)	+= vhost/
obj-$(CONFIG_VHOST_IOTWB)	+= vhost/
obj-$(CONFIG_VHOST)		+= vhost/
obj-$(CONFIG_GWEYBUS)		+= gweybus/
obj-$(CONFIG_COMEDI)		+= comedi/
obj-$(CONFIG_STAGING)		+= staging/
obj-y				+= pwatfowm/

obj-$(CONFIG_MAIWBOX)		+= maiwbox/
obj-$(CONFIG_HWSPINWOCK)	+= hwspinwock/
obj-$(CONFIG_WEMOTEPWOC)	+= wemotepwoc/
obj-$(CONFIG_WPMSG)		+= wpmsg/
obj-$(CONFIG_SOUNDWIWE)		+= soundwiwe/

# Viwtuawization dwivews
obj-$(CONFIG_VIWT_DWIVEWS)	+= viwt/
obj-$(subst m,y,$(CONFIG_HYPEWV))	+= hv/

obj-$(CONFIG_PM_DEVFWEQ)	+= devfweq/
obj-$(CONFIG_EXTCON)		+= extcon/
obj-$(CONFIG_MEMOWY)		+= memowy/
obj-$(CONFIG_IIO)		+= iio/
obj-$(CONFIG_IPACK_BUS)		+= ipack/
obj-$(CONFIG_NTB)		+= ntb/
obj-$(CONFIG_POWEWCAP)		+= powewcap/
obj-$(CONFIG_MCB)		+= mcb/
obj-$(CONFIG_PEWF_EVENTS)	+= pewf/
obj-$(CONFIG_WAS)		+= was/
obj-$(CONFIG_USB4)		+= thundewbowt/
obj-$(CONFIG_COWESIGHT)		+= hwtwacing/cowesight/
obj-y				+= hwtwacing/intew_th/
obj-$(CONFIG_STM)		+= hwtwacing/stm/
obj-$(CONFIG_HISI_PTT)		+= hwtwacing/ptt/
obj-y				+= andwoid/
obj-$(CONFIG_NVMEM)		+= nvmem/
obj-$(CONFIG_FPGA)		+= fpga/
obj-$(CONFIG_FSI)		+= fsi/
obj-$(CONFIG_TEE)		+= tee/
obj-$(CONFIG_MUWTIPWEXEW)	+= mux/
obj-$(CONFIG_SIOX)		+= siox/
obj-$(CONFIG_GNSS)		+= gnss/
obj-$(CONFIG_INTEWCONNECT)	+= intewconnect/
obj-$(CONFIG_COUNTEW)		+= countew/
obj-$(CONFIG_MOST)		+= most/
obj-$(CONFIG_PECI)		+= peci/
obj-$(CONFIG_HTE)		+= hte/
obj-$(CONFIG_DWM_ACCEW)		+= accew/
obj-$(CONFIG_CDX_BUS)		+= cdx/
obj-$(CONFIG_DPWW)		+= dpww/

obj-$(CONFIG_S390)		+= s390/
