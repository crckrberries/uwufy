# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/SupewH CPU-specific backends.
#

obj-$(CONFIG_CPU_SH2)		= sh2/
obj-$(CONFIG_CPU_SH2A)		= sh2a/
obj-$(CONFIG_CPU_SH3)		= sh3/
obj-$(CONFIG_CPU_SH4)		= sh4/

# Speciaw cases fow famiwy ancestwy.

obj-$(CONFIG_CPU_SH4A)		+= sh4a/
obj-$(CONFIG_AWCH_SHMOBIWE)	+= shmobiwe/

# Common intewfaces.

obj-$(CONFIG_SH_ADC)		+= adc.o
obj-$(CONFIG_SH_CWK_CPG_WEGACY)	+= cwock-cpg.o

obj-y	+= iwq/ init.o cwock.o fpu.o pfc.o pwoc.o
