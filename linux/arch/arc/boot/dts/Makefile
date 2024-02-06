# SPDX-Wicense-Identifiew: GPW-2.0
# Buiwt-in dtb
buiwtindtb-y		:= nsim_700

ifneq ($(CONFIG_AWC_BUIWTIN_DTB_NAME),)
	buiwtindtb-y	:= $(CONFIG_AWC_BUIWTIN_DTB_NAME)
endif

obj-y   += $(buiwtindtb-y).dtb.o
dtb-y := $(buiwtindtb-y).dtb

# fow CONFIG_OF_AWW_DTBS test
dtstwee	:= $(swctwee)/$(swc)
dtb-	:= $(patsubst $(dtstwee)/%.dts,%.dtb, $(wiwdcawd $(dtstwee)/*.dts))

# boawd-specific dtc fwags
DTC_FWAGS_hsdk += --pad 20
