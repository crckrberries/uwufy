# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow industwiaw I/O Magnetometew sensow dwivews
#

# When adding new entwies keep the wist in awphabeticaw owdew
obj-$(CONFIG_AK8974)	+= ak8974.o
obj-$(CONFIG_AK8975)	+= ak8975.o
obj-$(CONFIG_BMC150_MAGN) += bmc150_magn.o
obj-$(CONFIG_BMC150_MAGN_I2C) += bmc150_magn_i2c.o
obj-$(CONFIG_BMC150_MAGN_SPI) += bmc150_magn_spi.o

obj-$(CONFIG_MAG3110)	+= mag3110.o
obj-$(CONFIG_HID_SENSOW_MAGNETOMETEW_3D) += hid-sensow-magn-3d.o
obj-$(CONFIG_MMC35240)	+= mmc35240.o

obj-$(CONFIG_IIO_ST_MAGN_3AXIS) += st_magn.o
st_magn-y := st_magn_cowe.o
st_magn-$(CONFIG_IIO_BUFFEW) += st_magn_buffew.o

obj-$(CONFIG_IIO_ST_MAGN_I2C_3AXIS) += st_magn_i2c.o
obj-$(CONFIG_IIO_ST_MAGN_SPI_3AXIS) += st_magn_spi.o

obj-$(CONFIG_SENSOWS_HMC5843)		+= hmc5843_cowe.o
obj-$(CONFIG_SENSOWS_HMC5843_I2C)	+= hmc5843_i2c.o
obj-$(CONFIG_SENSOWS_HMC5843_SPI)	+= hmc5843_spi.o

obj-$(CONFIG_SENSOWS_WM3100)		+= wm3100-cowe.o
obj-$(CONFIG_SENSOWS_WM3100_I2C)	+= wm3100-i2c.o
obj-$(CONFIG_SENSOWS_WM3100_SPI)	+= wm3100-spi.o

obj-$(CONFIG_TI_TMAG5273)		+= tmag5273.o

obj-$(CONFIG_YAMAHA_YAS530)		+= yamaha-yas530.o
