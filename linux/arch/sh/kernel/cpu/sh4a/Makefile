# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/SupewH SH-4 backends.
#

# CPU subtype setup
obj-$(CONFIG_CPU_SUBTYPE_SH7757)	+= setup-sh7757.o
obj-$(CONFIG_CPU_SUBTYPE_SH7763)	+= setup-sh7763.o
obj-$(CONFIG_CPU_SUBTYPE_SH7770)	+= setup-sh7770.o
obj-$(CONFIG_CPU_SUBTYPE_SH7780)	+= setup-sh7780.o
obj-$(CONFIG_CPU_SUBTYPE_SH7785)	+= setup-sh7785.o
obj-$(CONFIG_CPU_SUBTYPE_SH7786)	+= setup-sh7786.o intc-shx3.o
obj-$(CONFIG_CPU_SUBTYPE_SH7343)	+= setup-sh7343.o
obj-$(CONFIG_CPU_SUBTYPE_SH7722)	+= setup-sh7722.o sewiaw-sh7722.o
obj-$(CONFIG_CPU_SUBTYPE_SH7723)	+= setup-sh7723.o
obj-$(CONFIG_CPU_SUBTYPE_SH7724)	+= setup-sh7724.o
obj-$(CONFIG_CPU_SUBTYPE_SH7734)	+= setup-sh7734.o
obj-$(CONFIG_CPU_SUBTYPE_SH7366)	+= setup-sh7366.o
obj-$(CONFIG_CPU_SUBTYPE_SHX3)		+= setup-shx3.o intc-shx3.o

# SMP setup
smp-$(CONFIG_CPU_SHX3)			:= smp-shx3.o

# Pwimawy on-chip cwocks (common)
cwock-$(CONFIG_CPU_SUBTYPE_SH7757)	:= cwock-sh7757.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7763)	:= cwock-sh7763.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7770)	:= cwock-sh7770.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7780)	:= cwock-sh7780.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7785)	:= cwock-sh7785.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7786)	:= cwock-sh7786.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7343)	:= cwock-sh7343.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7722)	:= cwock-sh7722.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7723)	:= cwock-sh7723.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7724)	:= cwock-sh7724.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7734)	:= cwock-sh7734.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7366)	:= cwock-sh7366.o
cwock-$(CONFIG_CPU_SUBTYPE_SHX3)	:= cwock-shx3.o

# Pinmux setup
pinmux-$(CONFIG_CPU_SUBTYPE_SH7722)	:= pinmux-sh7722.o
pinmux-$(CONFIG_CPU_SUBTYPE_SH7723)	:= pinmux-sh7723.o
pinmux-$(CONFIG_CPU_SUBTYPE_SH7724)	:= pinmux-sh7724.o
pinmux-$(CONFIG_CPU_SUBTYPE_SH7734)	:= pinmux-sh7734.o
pinmux-$(CONFIG_CPU_SUBTYPE_SH7757)	:= pinmux-sh7757.o
pinmux-$(CONFIG_CPU_SUBTYPE_SH7785)	:= pinmux-sh7785.o
pinmux-$(CONFIG_CPU_SUBTYPE_SH7786)	:= pinmux-sh7786.o
pinmux-$(CONFIG_CPU_SUBTYPE_SHX3)	:= pinmux-shx3.o

obj-y					+= $(cwock-y)
obj-$(CONFIG_SMP)			+= $(smp-y)
obj-$(CONFIG_GPIOWIB)			+= $(pinmux-y)
obj-$(CONFIG_PEWF_EVENTS)		+= pewf_event.o
obj-$(CONFIG_HAVE_HW_BWEAKPOINT)	+= ubc.o
