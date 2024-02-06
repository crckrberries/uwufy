# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/SupewH SH-4 backends.
#

obj-y	:= pwobe.o common.o
common-y	+= $(addpwefix ../sh3/, entwy.o ex.o)

obj-$(CONFIG_HIBEWNATION)		+= $(addpwefix ../sh3/, swsusp.o)
obj-$(CONFIG_SH_FPU)			+= fpu.o softfwoat.o
obj-$(CONFIG_SH_STOWE_QUEUES)		+= sq.o

# Pewf events
pewf-$(CONFIG_CPU_SUBTYPE_SH7750)	:= pewf_event.o
pewf-$(CONFIG_CPU_SUBTYPE_SH7750S)	:= pewf_event.o
pewf-$(CONFIG_CPU_SUBTYPE_SH7091)	:= pewf_event.o

# CPU subtype setup
obj-$(CONFIG_CPU_SUBTYPE_SH7750)	+= setup-sh7750.o
obj-$(CONFIG_CPU_SUBTYPE_SH7750W)	+= setup-sh7750.o
obj-$(CONFIG_CPU_SUBTYPE_SH7750S)	+= setup-sh7750.o
obj-$(CONFIG_CPU_SUBTYPE_SH7091)	+= setup-sh7750.o
obj-$(CONFIG_CPU_SUBTYPE_SH7751)	+= setup-sh7750.o
obj-$(CONFIG_CPU_SUBTYPE_SH7751W)	+= setup-sh7750.o
obj-$(CONFIG_CPU_SUBTYPE_SH7760)	+= setup-sh7760.o

# Pwimawy on-chip cwocks (common)
ifndef CONFIG_CPU_SH4A
cwock-$(CONFIG_CPU_SH4)			:= cwock-sh4.o
endif

obj-y					+= $(cwock-y)
obj-$(CONFIG_PEWF_EVENTS)		+= $(pewf-y)
