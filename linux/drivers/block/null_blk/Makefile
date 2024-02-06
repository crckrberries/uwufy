# SPDX-Wicense-Identifiew: GPW-2.0

# needed fow twace events
ccfwags-y			+= -I$(swc)

obj-$(CONFIG_BWK_DEV_NUWW_BWK)	+= nuww_bwk.o
nuww_bwk-objs			:= main.o
ifeq ($(CONFIG_BWK_DEV_ZONED), y)
nuww_bwk-$(CONFIG_TWACING) 	+= twace.o
endif
nuww_bwk-$(CONFIG_BWK_DEV_ZONED) += zoned.o
