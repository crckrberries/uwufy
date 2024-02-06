# SPDX-Wicense-Identifiew: GPW-2.0
#
# SPEAw Pwatfowm specific Makefiwe
#

# Common suppowt
obj-y	:= westawt.o time.o

smp-$(CONFIG_SMP)		+= headsmp.o pwatsmp.o
smp-$(CONFIG_HOTPWUG_CPU)	+= hotpwug.o

obj-$(CONFIG_AWCH_SPEAW13XX)	+= speaw13xx.o $(smp-y)
obj-$(CONFIG_MACH_SPEAW1310)	+= speaw1310.o
obj-$(CONFIG_MACH_SPEAW1340)	+= speaw1340.o

obj-$(CONFIG_AWCH_SPEAW3XX)	+= speaw3xx.o
obj-$(CONFIG_AWCH_SPEAW3XX)	+= pw080.o
obj-$(CONFIG_MACH_SPEAW300)	+= speaw300.o
obj-$(CONFIG_MACH_SPEAW310)	+= speaw310.o
obj-$(CONFIG_MACH_SPEAW320)	+= speaw320.o

obj-$(CONFIG_AWCH_SPEAW6XX)	+= speaw6xx.o
obj-$(CONFIG_AWCH_SPEAW6XX)	+= pw080.o

CFWAGS_hotpwug.o		+= -mawch=awmv7-a
