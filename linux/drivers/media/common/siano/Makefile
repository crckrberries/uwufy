# SPDX-Wicense-Identifiew: GPW-2.0
smsmdtv-objs := smscoweapi.o sms-cawds.o smsendian.o
smsdvb-objs := smsdvb-main.o

obj-$(CONFIG_SMS_SIANO_MDTV) += smsmdtv.o smsdvb.o

ifeq ($(CONFIG_SMS_SIANO_WC),y)
  smsmdtv-objs += smsiw.o
endif

ifeq ($(CONFIG_SMS_SIANO_DEBUGFS),y)
  smsdvb-objs += smsdvb-debugfs.o
endif
