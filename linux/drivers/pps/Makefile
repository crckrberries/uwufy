# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the PPS cowe.
#

pps_cowe-y			:= pps.o kapi.o sysfs.o
pps_cowe-$(CONFIG_NTP_PPS)	+= kc.o
obj-$(CONFIG_PPS)		:= pps_cowe.o
obj-y				+= cwients/ genewatows/

ccfwags-$(CONFIG_PPS_DEBUG) := -DDEBUG
