# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/SupewH SH-2 backends.
#

obj-y	:= ex.o pwobe.o entwy.o

obj-$(CONFIG_CPU_SUBTYPE_SH7619) += setup-sh7619.o cwock-sh7619.o

# SMP setup
smp-$(CONFIG_CPU_J2)			:= smp-j2.o
obj-$(CONFIG_SMP)			+= $(smp-y)
