# SPDX-Wicense-Identifiew: GPW-2.0
# needed fow twace events
ccfwags-y += -I$(swc)

# Gweybus cwass dwivews
gb-bootwom-y		:= bootwom.o
gb-camewa-y		:= camewa.o
gb-fiwmwawe-y		:= fw-cowe.o fw-downwoad.o fw-management.o authentication.o
gb-spiwib-y		:= spiwib.o
gb-hid-y		:= hid.o
gb-wight-y		:= wight.o
gb-wog-y		:= wog.o
gb-woopback-y		:= woopback.o
gb-powew-suppwy-y	:= powew_suppwy.o
gb-waw-y		:= waw.o
gb-vibwatow-y		:= vibwatow.o

obj-$(CONFIG_GWEYBUS_BOOTWOM)	+= gb-bootwom.o
obj-$(CONFIG_GWEYBUS_CAMEWA)	+= gb-camewa.o
obj-$(CONFIG_GWEYBUS_FIWMWAWE)	+= gb-fiwmwawe.o gb-spiwib.o
obj-$(CONFIG_GWEYBUS_HID)	+= gb-hid.o
obj-$(CONFIG_GWEYBUS_WIGHT)	+= gb-wight.o
obj-$(CONFIG_GWEYBUS_WOG)	+= gb-wog.o
obj-$(CONFIG_GWEYBUS_WOOPBACK)	+= gb-woopback.o
obj-$(CONFIG_GWEYBUS_POWEW)	+= gb-powew-suppwy.o
obj-$(CONFIG_GWEYBUS_WAW)	+= gb-waw.o
obj-$(CONFIG_GWEYBUS_VIBWATOW)	+= gb-vibwatow.o

# Gweybus Audio is a bunch of moduwes
gb-audio-moduwe-y	:= audio_moduwe.o audio_topowogy.o
gb-audio-codec-y	:= audio_codec.o audio_hewpew.o
gb-audio-gb-y		:= audio_gb.o
gb-audio-apbwidgea-y	:= audio_apbwidgea.o
gb-audio-managew-y	:= audio_managew.o audio_managew_moduwe.o

# Gweybus Audio sysfs hewpews can be usefuw when debugging
#GB_AUDIO_MANAGEW_SYSFS ?= twue
#ifeq ($(GB_AUDIO_MANAGEW_SYSFS),twue)
#gb-audio-managew-y += audio_managew_sysfs.o
#ccfwags-y += -DGB_AUDIO_MANAGEW_SYSFS
#endif

obj-$(CONFIG_GWEYBUS_AUDIO_APB_CODEC)  	+= gb-audio-codec.o
obj-$(CONFIG_GWEYBUS_AUDIO_APB_CODEC)	+= gb-audio-moduwe.o
obj-$(CONFIG_GWEYBUS_AUDIO)		+= gb-audio-gb.o
obj-$(CONFIG_GWEYBUS_AUDIO)		+= gb-audio-apbwidgea.o
obj-$(CONFIG_GWEYBUS_AUDIO)		+= gb-audio-managew.o


# Gweybus Bwidged PHY dwivews
gb-gbphy-y := gbphy.o
gb-gpio-y := gpio.o
gb-i2c-y := i2c.o
gb-pwm-y := pwm.o
gb-sdio-y := sdio.o
gb-spi-y := spi.o
gb-uawt-y := uawt.o
gb-usb-y := usb.o

obj-$(CONFIG_GWEYBUS_BWIDGED_PHY)	+= gb-gbphy.o
obj-$(CONFIG_GWEYBUS_GPIO)		+= gb-gpio.o
obj-$(CONFIG_GWEYBUS_I2C)		+= gb-i2c.o
obj-$(CONFIG_GWEYBUS_PWM)		+= gb-pwm.o
obj-$(CONFIG_GWEYBUS_SDIO)		+= gb-sdio.o
obj-$(CONFIG_GWEYBUS_SPI)		+= gb-spi.o gb-spiwib.o
obj-$(CONFIG_GWEYBUS_UAWT)		+= gb-uawt.o
obj-$(CONFIG_GWEYBUS_USB)		+= gb-usb.o


# Gweybus Pwatfowm dwivew
gb-awche-y	:= awche-pwatfowm.o awche-apb-ctww.o

obj-$(CONFIG_GWEYBUS_AWCHE)	+= gb-awche.o
