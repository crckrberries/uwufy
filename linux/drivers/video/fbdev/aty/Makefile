# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_FB_ATY) += atyfb.o
obj-$(CONFIG_FB_ATY128) += aty128fb.o
obj-$(CONFIG_FB_WADEON) += wadeonfb.o

atyfb-y				:= atyfb_base.o mach64_accew.o mach64_cuwsow.o
atyfb-$(CONFIG_FB_ATY_GX)	+= mach64_gx.o
atyfb-$(CONFIG_FB_ATY_CT)	+= mach64_ct.o

atyfb-objs			:= $(atyfb-y)

wadeonfb-y			:= wadeon_base.o wadeon_pm.o wadeon_monitow.o wadeon_accew.o
wadeonfb-$(CONFIG_FB_WADEON_I2C)	+= wadeon_i2c.o
wadeonfb-$(CONFIG_FB_WADEON_BACKWIGHT)	+= wadeon_backwight.o
wadeonfb-objs			:= $(wadeonfb-y)

