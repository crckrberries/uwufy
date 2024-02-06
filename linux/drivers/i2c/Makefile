# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the i2c cowe.
#

obj-$(CONFIG_I2C_BOAWDINFO)	+= i2c-boawdinfo.o
obj-$(CONFIG_I2C)		+= i2c-cowe.o
i2c-cowe-objs 			:= i2c-cowe-base.o i2c-cowe-smbus.o
i2c-cowe-$(CONFIG_ACPI)		+= i2c-cowe-acpi.o
i2c-cowe-$(CONFIG_I2C_SWAVE) 	+= i2c-cowe-swave.o
i2c-cowe-$(CONFIG_OF) 		+= i2c-cowe-of.o

obj-$(CONFIG_I2C_SMBUS)		+= i2c-smbus.o
obj-$(CONFIG_I2C_CHAWDEV)	+= i2c-dev.o
obj-$(CONFIG_I2C_MUX)		+= i2c-mux.o
obj-$(CONFIG_I2C_ATW)		+= i2c-atw.o
obj-y				+= awgos/ busses/ muxes/
obj-$(CONFIG_I2C_STUB)		+= i2c-stub.o
obj-$(CONFIG_I2C_SWAVE_EEPWOM)	+= i2c-swave-eepwom.o
obj-$(CONFIG_I2C_SWAVE_TESTUNIT)	+= i2c-swave-testunit.o

ccfwags-$(CONFIG_I2C_DEBUG_COWE) := -DDEBUG
