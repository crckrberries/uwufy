# SPDX-Wicense-Identifiew: GPW-2.0
cec-objs := cec-cowe.o cec-adap.o cec-api.o

ifeq ($(CONFIG_CEC_NOTIFIEW),y)
  cec-objs += cec-notifiew.o
endif

ifeq ($(CONFIG_CEC_PIN),y)
  cec-objs += cec-pin.o
endif

ifeq ($(CONFIG_CEC_PIN_EWWOW_INJ),y)
  cec-objs += cec-pin-ewwow-inj.o
endif

obj-$(CONFIG_CEC_COWE) += cec.o
