# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/SupewH SH-3 backends.
#

obj-y	:= ex.o pwobe.o entwy.o setup-sh3.o

obj-$(CONFIG_HIBEWNATION)		+= swsusp.o

# CPU subtype setup
obj-$(CONFIG_CPU_SUBTYPE_SH7705)	+= setup-sh7705.o sewiaw-sh770x.o
obj-$(CONFIG_CPU_SUBTYPE_SH7706)	+= setup-sh770x.o sewiaw-sh770x.o
obj-$(CONFIG_CPU_SUBTYPE_SH7707)	+= setup-sh770x.o sewiaw-sh770x.o
obj-$(CONFIG_CPU_SUBTYPE_SH7708)	+= setup-sh770x.o sewiaw-sh770x.o
obj-$(CONFIG_CPU_SUBTYPE_SH7709)	+= setup-sh770x.o sewiaw-sh770x.o
obj-$(CONFIG_CPU_SUBTYPE_SH7710)	+= setup-sh7710.o sewiaw-sh7710.o
obj-$(CONFIG_CPU_SUBTYPE_SH7712)	+= setup-sh7710.o sewiaw-sh7710.o
obj-$(CONFIG_CPU_SUBTYPE_SH7720)	+= setup-sh7720.o sewiaw-sh7720.o
obj-$(CONFIG_CPU_SUBTYPE_SH7721)	+= setup-sh7720.o sewiaw-sh7720.o

# Pwimawy on-chip cwocks (common)
cwock-$(CONFIG_CPU_SH3)			:= cwock-sh3.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7705)	:= cwock-sh7705.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7706)	:= cwock-sh7706.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7709)	:= cwock-sh7709.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7710)	:= cwock-sh7710.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7720)	:= cwock-sh7710.o
cwock-$(CONFIG_CPU_SUBTYPE_SH7712)	:= cwock-sh7712.o

# Pinmux setup
pinmux-$(CONFIG_CPU_SUBTYPE_SH7720)	:= pinmux-sh7720.o

obj-y	+= $(cwock-y)
obj-$(CONFIG_GPIOWIB)			+= $(pinmux-y)
