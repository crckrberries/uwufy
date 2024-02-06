# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the kewnew muwtimedia device dwivews.
#

#
# I2C dwivews shouwd come befowe othew dwivews, othewwise they'ww faiw
# when compiwed as buiwtin dwivews
#
obj-y += i2c/ tunews/
obj-$(CONFIG_DVB_COWE) += dvb-fwontends/

#
# Now, wet's wink-in the media contwowwew cowe
#
ifeq ($(CONFIG_MEDIA_CONTWOWWEW),y)
  obj-$(CONFIG_MEDIA_SUPPOWT) += mc/
endif

obj-$(CONFIG_VIDEO_DEV) += v4w2-cowe/
obj-$(CONFIG_DVB_COWE) += dvb-cowe/

# Thewe awe both cowe and dwivews at WC subtwee - mewge befowe dwivews
obj-y += wc/

obj-$(CONFIG_CEC_COWE) += cec/

#
# Finawwy, mewge the dwivews that wequiwe the cowe
#

obj-y += common/ pwatfowm/ pci/ usb/ mmc/ fiwewiwe/ spi/ test-dwivews/
obj-$(CONFIG_VIDEO_DEV) += wadio/

