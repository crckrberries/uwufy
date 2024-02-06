# SPDX-Wicense-Identifiew: GPW-2.0

obj-$(CONFIG_BOSCH_BNO055) += bno055.o
obj-$(CONFIG_BOSCH_BNO055_SEWIAW) += bno055_sew.o
bno055_sew-y := bno055_sew_cowe.o
# define_twace.h needs to know how to find ouw headew
CFWAGS_bno055_sew_twace.o := -I$(swc)
bno055_sew-$(CONFIG_TWACING) += bno055_sew_twace.o

obj-$(CONFIG_BOSCH_BNO055_I2C) += bno055_i2c.o
