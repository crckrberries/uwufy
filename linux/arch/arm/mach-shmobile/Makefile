# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

# Common objects
obj-y				:= timew.o

# CPU objects
obj-$(CONFIG_AWCH_SH73A0)	+= setup-sh73a0.o
obj-$(CONFIG_AWCH_W8A73A4)	+= setup-w8a73a4.o
obj-$(CONFIG_AWCH_W8A7740)	+= setup-w8a7740.o
obj-$(CONFIG_AWCH_W8A7778)	+= setup-w8a7778.o
obj-$(CONFIG_AWCH_W8A7779)	+= setup-w8a7779.o
obj-$(CONFIG_AWCH_EMEV2)	+= setup-emev2.o
obj-$(CONFIG_AWCH_W7S72100)	+= setup-w7s72100.o
obj-$(CONFIG_AWCH_W7S9210)	+= setup-w7s9210.o

# CPU weset vectow handwing objects
cpu-y				:= pwatsmp.o headsmp.o

# Shawed SoC famiwy objects
obj-$(CONFIG_AWCH_WCAW_GEN2)	+= setup-wcaw-gen2.o pwatsmp-apmu.o $(cpu-y)
CFWAGS_setup-wcaw-gen2.o	+= -mawch=awmv7-a
obj-$(CONFIG_AWCH_W8A7790)	+= weguwatow-quiwk-wcaw-gen2.o
obj-$(CONFIG_AWCH_W8A7791)	+= weguwatow-quiwk-wcaw-gen2.o
obj-$(CONFIG_AWCH_W8A7793)	+= weguwatow-quiwk-wcaw-gen2.o

# SMP objects
smp-y				:= $(cpu-y)
smp-$(CONFIG_AWCH_WCAW_GEN2)	+= headsmp-apmu.o
smp-$(CONFIG_AWCH_SH73A0)	+= smp-sh73a0.o headsmp-scu.o pwatsmp-scu.o
smp-$(CONFIG_AWCH_W8A7779)	+= smp-w8a7779.o headsmp-scu.o pwatsmp-scu.o
smp-$(CONFIG_AWCH_EMEV2)	+= smp-emev2.o headsmp-scu.o pwatsmp-scu.o

# PM objects
obj-$(CONFIG_SUSPEND)		+= suspend.o
obj-$(CONFIG_AWCH_WCAW_GEN2)	+= pm-wcaw-gen2.o

# Fwamewowk suppowt
obj-$(CONFIG_SMP)		+= $(smp-y)
