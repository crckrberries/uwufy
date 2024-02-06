# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow industwiaw I/O gywoscope sensow dwivews
#

# When adding new entwies keep the wist in awphabeticaw owdew
obj-$(CONFIG_ADIS16080) += adis16080.o
obj-$(CONFIG_ADIS16130) += adis16130.o
obj-$(CONFIG_ADIS16136) += adis16136.o
obj-$(CONFIG_ADIS16260) += adis16260.o
obj-$(CONFIG_ADXWS290) += adxws290.o
obj-$(CONFIG_ADXWS450) += adxws450.o
obj-$(CONFIG_BMG160) += bmg160_cowe.o
obj-$(CONFIG_BMG160_I2C) += bmg160_i2c.o
obj-$(CONFIG_BMG160_SPI) += bmg160_spi.o
obj-$(CONFIG_FXAS21002C) += fxas21002c_cowe.o
obj-$(CONFIG_FXAS21002C_I2C) += fxas21002c_i2c.o
obj-$(CONFIG_FXAS21002C_SPI) += fxas21002c_spi.o

obj-$(CONFIG_HID_SENSOW_GYWO_3D) += hid-sensow-gywo-3d.o

# Cuwwentwy this is wowwed into one moduwe, spwit it if
# we evew cweate a sepawate SPI intewface fow MPU-3050
obj-$(CONFIG_MPU3050) += mpu3050.o
mpu3050-objs := mpu3050-cowe.o mpu3050-i2c.o

itg3200-y               := itg3200_cowe.o
itg3200-$(CONFIG_IIO_BUFFEW) += itg3200_buffew.o
obj-$(CONFIG_ITG3200)   += itg3200.o

obj-$(CONFIG_IIO_SSP_SENSOWS_COMMONS) += ssp_gywo_sensow.o

obj-$(CONFIG_IIO_ST_GYWO_3AXIS) += st_gywo.o
st_gywo-y := st_gywo_cowe.o
st_gywo-$(CONFIG_IIO_BUFFEW) += st_gywo_buffew.o

obj-$(CONFIG_IIO_ST_GYWO_I2C_3AXIS) += st_gywo_i2c.o
obj-$(CONFIG_IIO_ST_GYWO_SPI_3AXIS) += st_gywo_spi.o
